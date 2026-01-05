#include "pch.h"
#include "features/esp.h"
#include "gui/menu.h"
#include "game/game_objects.h"
#include <algorithm>

namespace Features {
	namespace ESP {
		static std::vector<Game::Panel*> cachedPanels;
		static DWORD lastPanelUpdate = 0;

		void Initialize() {
			printf("[ESP] Initialized\n");
		}

		void UpdatePanelCache() {
			DWORD now = GetTickCount();
			if (now - lastPanelUpdate < 1000) return; // Update every 1 second

			cachedPanels.clear();

			// Find all panels
			auto panelObjects = Game::Objects::FindObjectsOfType<void>("Hyperstrange.WARPZ", "Panel");
			for (auto obj : panelObjects) {
				cachedPanels.push_back(new Game::Panel(obj));
			}

			lastPanelUpdate = now;
			printf("[ESP] Found %zu panels\n", cachedPanels.size());
		}

		bool WorldToScreen(const Unity::Vector3& world, Unity::Vector2& screen) {
			auto player = Game::Player::GetLocalPlayer();
			if (!player || !player->IsValid()) return false;

			auto camera = player->GetCamera();
			if (!camera) return false;

			Unity::Vector3 screenPos = Game::WorldToScreen(camera, world);

			if (!Game::IsOnScreen(screenPos)) return false;

			screen.x = screenPos.x;
			screen.y = screenPos.y;
			return true;
		}

		void DrawBox(const Unity::Vector2& screenPos, float size, const Unity::Color& color) {
			ImVec2 min(screenPos.x - size, screenPos.y - size);
			ImVec2 max(screenPos.x + size, screenPos.y + size);

			ImGui::GetBackgroundDrawList()->AddRect(
				min, max,
				IM_COL32((int)(color.r * 255), (int)(color.g * 255), (int)(color.b * 255), (int)(color.a * 255)),
				0.0f, 0, 2.0f
			);
		}

		void DrawLine(const Unity::Vector2& from, const Unity::Vector2& to, const Unity::Color& color) {
			ImGui::GetBackgroundDrawList()->AddLine(
				ImVec2(from.x, from.y),
				ImVec2(to.x, to.y),
				IM_COL32((int)(color.r * 255), (int)(color.g * 255), (int)(color.b * 255), (int)(color.a * 255)),
				2.0f
			);
		}

		void DrawText(const Unity::Vector2& pos, const std::string& text, const Unity::Color& color) {
			ImGui::GetBackgroundDrawList()->AddText(
				ImVec2(pos.x, pos.y),
				IM_COL32((int)(color.r * 255), (int)(color.g * 255), (int)(color.b * 255), (int)(color.a * 255)),
				text.c_str()
			);
		}

		void Render() {
			if (!Menu::Features::g_ESP) return;

			auto player = Game::Player::GetLocalPlayer();
			if (!player || !player->IsValid()) return;

			// Update panel cache
			UpdatePanelCache();

			ImGuiIO& io = ImGui::GetIO();
			Unity::Vector2 screenCenter(io.DisplaySize.x / 2.0f, io.DisplaySize.y);

			// Draw panels
			for (auto panel : cachedPanels) {
				if (!panel || !panel->IsValid()) continue;

				Unity::Vector3 worldPos = panel->GetPosition();
				Unity::Vector2 screenPos;

				if (!WorldToScreen(worldPos, screenPos)) continue;

				// Determine panel type by checking class name or other properties
				// For now, draw all panels as potential targets
				Unity::Color color(1.0f, 0.0f, 0.0f, 1.0f); // Red

				if (Menu::Features::g_ESPBoxes) {
					DrawBox(screenPos, 20.0f, color);
				}

				if (Menu::Features::g_ESPSnaplines) {
					DrawLine(screenCenter, screenPos, color);
				}

				// Draw distance
				float dist = worldPos.Distance(player->GetPosition());
				std::string distText = std::to_string((int)dist) + "m";
				DrawText(Unity::Vector2(screenPos.x, screenPos.y - 25), distText, color);
			}
		}

		void Shutdown() {
			for (auto panel : cachedPanels) {
				delete panel;
			}
			cachedPanels.clear();
			printf("[ESP] Shut down\n");
		}
	}
}
