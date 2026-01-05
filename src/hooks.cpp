#include "pch.h"
#include "hooks.h"
#include "gui/menu.h"
#include <dxgi.h>
#include "features/esp.h"

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

namespace Hooks {
	namespace D3D11 {
		// ImGui state
		static bool g_ImGuiInitialized = false;
		static ID3D11Device* g_pd3dDevice = nullptr;
		static ID3D11DeviceContext* g_pd3dDeviceContext = nullptr;
		static ID3D11RenderTargetView* g_mainRenderTargetView = nullptr;
		static HWND g_hWnd = nullptr;

		void CleanupRenderTarget() {
			if (g_mainRenderTargetView) {
				g_mainRenderTargetView->Release();
				g_mainRenderTargetView = nullptr;
			}
		}

		void CreateRenderTarget(IDXGISwapChain* pSwapChain) {
			ID3D11Texture2D* pBackBuffer = nullptr;
			pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
			if (pBackBuffer) {
				g_pd3dDevice->CreateRenderTargetView(pBackBuffer, nullptr, &g_mainRenderTargetView);
				pBackBuffer->Release();
			}
		}

		HRESULT __stdcall hkPresent(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags) {
			if (!g_ImGuiInitialized) {
				if (SUCCEEDED(pSwapChain->GetDevice(__uuidof(ID3D11Device), (void**)&g_pd3dDevice))) {
					g_pd3dDevice->GetImmediateContext(&g_pd3dDeviceContext);

					// Get window from swap chain
					DXGI_SWAP_CHAIN_DESC sd;
					pSwapChain->GetDesc(&sd);
					g_hWnd = sd.OutputWindow;

					// Initialize ImGui
					ImGui::CreateContext();
					ImGuiIO& io = ImGui::GetIO();
					io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

					ImGui_ImplWin32_Init(g_hWnd);
					ImGui_ImplDX11_Init(g_pd3dDevice, g_pd3dDeviceContext);

					CreateRenderTarget(pSwapChain);

					// Hook WndProc
					WndProc::oWndProc = (WNDPROC)SetWindowLongPtr(g_hWnd, GWLP_WNDPROC, (LONG_PTR)WndProc::hkWndProc);

					g_ImGuiInitialized = true;
					printf("[+] ImGui initialized\n");
				}
			}

			if (g_ImGuiInitialized) {
				ImGui_ImplDX11_NewFrame();
				ImGui_ImplWin32_NewFrame();

				//newframe
				ImGui::NewFrame();

				// Render menu
				Menu::Render();

				// Render ESP
				Features::ESP::Render();

				ImGui::Render();

				g_pd3dDeviceContext->OMSetRenderTargets(1, &g_mainRenderTargetView, nullptr);
				ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
			}

			return oPresent(pSwapChain, SyncInterval, Flags);
		}

		HRESULT __stdcall hkResizeBuffers(IDXGISwapChain* pSwapChain, UINT BufferCount, UINT Width, UINT Height, DXGI_FORMAT NewFormat, UINT SwapChainFlags) {
			CleanupRenderTarget();
			HRESULT result = oResizeBuffers(pSwapChain, BufferCount, Width, Height, NewFormat, SwapChainFlags);
			CreateRenderTarget(pSwapChain);
			return result;
		}
	}

	namespace WndProc {
		LRESULT CALLBACK hkWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
			// Forward to ImGui first
			if (ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam))
				return true;

			// Call original WndProc
			return CallWindowProc(oWndProc, hWnd, uMsg, wParam, lParam);
		}
	}

	bool Init() {
		printf("[*] Initializing hooks...\n");

		// Create dummy D3D11 device to find vtable
		DXGI_SWAP_CHAIN_DESC sd = {};
		sd.BufferCount = 1;
		sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		sd.OutputWindow = GetForegroundWindow();
		sd.SampleDesc.Count = 1;
		sd.Windowed = TRUE;
		sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

		IDXGISwapChain* pSwapChain = nullptr;
		ID3D11Device* pDevice = nullptr;
		ID3D11DeviceContext* pContext = nullptr;

		D3D_FEATURE_LEVEL featureLevel = D3D_FEATURE_LEVEL_11_0;
		if (FAILED(D3D11CreateDeviceAndSwapChain(
			nullptr,
			D3D_DRIVER_TYPE_HARDWARE,
			nullptr,
			0,
			&featureLevel,
			1,
			D3D11_SDK_VERSION,
			&sd,
			&pSwapChain,
			&pDevice,
			nullptr,
			&pContext
		))) {
			printf("[!] Failed to create dummy D3D11 device\n");
			return false;
		}

		// Get vtable
		void** pSwapChainVtable = *(void***)pSwapChain;

		// Hook Present (index 8) and ResizeBuffers (index 13)
		if (MH_CreateHook(pSwapChainVtable[8], &D3D11::hkPresent, (void**)&D3D11::oPresent) != MH_OK) {
			printf("[!] Failed to hook Present\n");
			return false;
		}

		if (MH_CreateHook(pSwapChainVtable[13], &D3D11::hkResizeBuffers, (void**)&D3D11::oResizeBuffers) != MH_OK) {
			printf("[!] Failed to hook ResizeBuffers\n");
			return false;
		}

		if (MH_EnableHook(MH_ALL_HOOKS) != MH_OK) {
			printf("[!] Failed to enable hooks\n");
			return false;
		}

		// Cleanup dummy device
		pSwapChain->Release();
		pDevice->Release();
		pContext->Release();

		printf("[+] Hooks initialized\n");
		return true;
	}

	void Shutdown() {
		printf("[*] Shutting down hooks...\n");

		MH_DisableHook(MH_ALL_HOOKS);
		MH_RemoveHook(MH_ALL_HOOKS);

		if (D3D11::g_ImGuiInitialized) {
			// Restore original WndProc
			if (WndProc::oWndProc && D3D11::g_hWnd) {
				SetWindowLongPtr(D3D11::g_hWnd, GWLP_WNDPROC, (LONG_PTR)WndProc::oWndProc);
			}

			ImGui_ImplDX11_Shutdown();
			ImGui_ImplWin32_Shutdown();
			ImGui::DestroyContext();

			D3D11::CleanupRenderTarget();

			if (D3D11::g_pd3dDeviceContext) {
				D3D11::g_pd3dDeviceContext->Release();
				D3D11::g_pd3dDeviceContext = nullptr;
			}
			if (D3D11::g_pd3dDevice) {
				D3D11::g_pd3dDevice->Release();
				D3D11::g_pd3dDevice = nullptr;
			}
		}

		printf("[+] Hooks shut down\n");
	}
}
