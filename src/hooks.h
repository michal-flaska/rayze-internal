#pragma once
#include "pch.h"

namespace Hooks {
	bool Init();
	void Shutdown();

	// DirectX hooks
	namespace D3D11 {
		typedef HRESULT(__stdcall* Present_t)(IDXGISwapChain*, UINT, UINT);
		typedef HRESULT(__stdcall* ResizeBuffers_t)(IDXGISwapChain*, UINT, UINT, UINT, DXGI_FORMAT, UINT);

		inline Present_t oPresent = nullptr;
		inline ResizeBuffers_t oResizeBuffers = nullptr;

		HRESULT __stdcall hkPresent(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags);
		HRESULT __stdcall hkResizeBuffers(IDXGISwapChain* pSwapChain, UINT BufferCount, UINT Width, UINT Height, DXGI_FORMAT NewFormat, UINT SwapChainFlags);
	}

	// WndProc hook
	namespace WndProc {
		inline WNDPROC oWndProc = nullptr;
		LRESULT CALLBACK hkWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	}

	// Game hooks - we'll add these after analyzing dump.cs
	namespace Game {
		// Example: Hook Camera.WorldToScreenPoint or similar
		// We'll populate these based on what we find in dump.cs
	}
}
