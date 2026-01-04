#include "pch.h"
#include "features/esp.h"
#include "gui/menu.h"
#include "game/entities.h"

namespace Features {
	namespace ESP {
		void Initialize() {
			printf("[ESP] Initialized\n");
		}

		bool WorldToScreen(const Unity::Vector3& world, Unity::Vector2& screen) {
			auto player = Game::Player::GetLocalPlayer();
			if (!player) return false;

			auto camera = player->GetCamera();
			if (!camera) return false;

			Unity::Vector3 screenPos = Game::WorldToScreen(camera, world);

			// Check if behind camera (z < 0)
			if (screenPos.z < 0.0f) return false;

			// Get screen dimensions
			ImGuiIO& io = ImGui::GetIO();
			float screenWidth = io.DisplaySize.x;
			float screenHeight = io.DisplaySize.y;

			// Check if on screen
			if (screenPos.x < 0 || screenPos.x > screenWidth ||
				screenPos.y < 0 || screenPos.y > screenHeight) {
				return false;
			}

			screen.x = screenPos.x;
			screen.y = screenPos.y;
			return true;
		}

		void DrawBox(const Unity::Vector3& worldPos, const Unity::Vector3& screenPos, const Unity::Color& color) {
			// Simple 2D box
			float boxSize = 20.0f;
			ImVec2 min(screenPos.x - boxSize, screenPos.y - boxSize);
			ImVec2 max(screenPos.x + boxSize, screenPos.y + boxSize);

			ImGui::GetBackgroundDrawList()->AddRect(
				min, max,
				IM_COL32(
					(int)(color.r * 255),
					(int)(color.g * 255),
					(int)(color.b * 255),
					(int)(color.a * 255)
				),
				0.0f, 0, 2.0f
			);
		}

		void DrawLine(const Unity::Vector2& from, const Unity::Vector2& to, const Unity::Color& color) {
			ImGui::GetBackgroundDrawList()->AddLine(
				ImVec2(from.x, from.y),
				ImVec2(to.x, to.y),
				IM_COL32(
					(int)(color.r * 255),
					(int)(color.g * 255),
					(int)(color.b * 255),
					(int)(color.a * 255)
				),
				2.0f
			);
		}

		void DrawText(const Unity::Vector2& pos, const std::string& text, const Unity::Color& color) {
			ImGui::GetBackgroundDrawList()->AddText(
				ImVec2(pos.x, pos.y),
				IM_COL32(
					(int)(color.r * 255),
					(int)(color.g * 255),
					(int)(color.b * 255),
					(int)(color.a * 255)
				),
				text.c_str()
			);
		}

		void Render() {
			if (!Menu::Features::g_ESP) return;

			auto player = Game::Player::GetLocalPlayer();
			if (!player) return;

			// Get screen center for snaplines
			ImGuiIO& io = ImGui::GetIO();
			Unity::Vector2 screenCenter(io.DisplaySize.x / 2.0f, io.DisplaySize.y);

			// Draw finish panel
			if (Menu::Features::g_ESPFinish) {
				// TODO: Find FinishPanel instance
				// For now, example with dummy position
				// auto panels = Game::GetAllPanels();
				// for (auto panel : panels) {
				//     Unity::Vector3 worldPos = panel->GetPosition();
				//     Unity::Vector2 screenPos;
				//     if (WorldToScreen(worldPos, screenPos)) {
				//         DrawBox(worldPos, Unity::Vector3(screenPos.x, screenPos.y, 0), Unity::Color(0, 1, 0, 1));
				//         DrawText(screenPos, "FINISH", Unity::Color(0, 1, 0, 1));
				//     }
				// }
			}

			// Draw targets
			if (Menu::Features::g_ESPTargets) {
				// TODO: Find all target/sphere objects
				// Same pattern as above
			}

			// Draw activation buttons
			if (Menu::Features::g_ESPButtons) {
				// TODO: Find button panels
			}
		}

		void Shutdown() {
			printf("[ESP] Shut down\n");
		}
	}
}
