#include "pch.h"
#include "gui/menu.h"

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

namespace Menu {
	void Render() {
		// Toggle menu with INSERT key
		if (GetAsyncKeyState(VK_INSERT) & 1) {
			g_ShowMenu = !g_ShowMenu;
		}

		if (!g_ShowMenu) return;

		ImGui::SetNextWindowSize(ImVec2(600, 400), ImGuiCond_FirstUseEver);
		ImGui::Begin("RAYZE Internal", &g_ShowMenu, ImGuiWindowFlags_NoCollapse);

		if (ImGui::BeginTabBar("MainTabBar")) {
			if (ImGui::BeginTabItem("Aimbot")) {
				ImGui::Checkbox("Enable Aimbot", &Features::g_Aimbot);

				if (Features::g_Aimbot) {
					ImGui::Separator();
					ImGui::SliderFloat("FOV", &Features::g_AimbotFOV, 10.0f, 360.0f, "%.1f");
					ImGui::SliderFloat("Smooth", &Features::g_AimbotSmooth, 1.0f, 20.0f, "%.1f");
					ImGui::Checkbox("Visible Only", &Features::g_AimbotVisibleOnly);
				}

				ImGui::EndTabItem();
			}

			if (ImGui::BeginTabItem("ESP")) {
				ImGui::Checkbox("Enable ESP", &Features::g_ESP);

				if (Features::g_ESP) {
					ImGui::Separator();
					ImGui::Text("Show:");
					ImGui::Checkbox("Targets", &Features::g_ESPTargets);
					ImGui::Checkbox("Finish", &Features::g_ESPFinish);
					ImGui::Checkbox("Activation Buttons", &Features::g_ESPButtons);

					ImGui::Separator();
					ImGui::Text("Style:");
					ImGui::Checkbox("Boxes", &Features::g_ESPBoxes);
					ImGui::Checkbox("Snaplines", &Features::g_ESPSnaplines);
				}

				ImGui::EndTabItem();
			}

			if (ImGui::BeginTabItem("Misc")) {
				ImGui::Checkbox("Speedhack", &Features::g_Speedhack);
				if (Features::g_Speedhack) {
					ImGui::SliderFloat("Speed Multiplier", &Features::g_SpeedhackMultiplier, 0.1f, 10.0f, "%.1fx");
				}

				ImGui::Separator();
				ImGui::Checkbox("Noclip", &Features::g_Noclip);

				ImGui::EndTabItem();
			}

			if (ImGui::BeginTabItem("Debug")) {
				ImGui::Checkbox("Show ImGui Demo", &g_ShowDemo);
				ImGui::Separator();
				ImGui::Text("FPS: %.1f", ImGui::GetIO().Framerate);
				ImGui::Text("Frame Time: %.3f ms", 1000.0f / ImGui::GetIO().Framerate);
				ImGui::EndTabItem();
			}

			ImGui::EndTabBar();
		}

		ImGui::End();

		if (g_ShowDemo) {
			ImGui::ShowDemoWindow(&g_ShowDemo);
		}
	}
}
