#include "pch.h"
#include "features/aimbot.h"
#include "gui/menu.h"
#include "game/game_objects.h"
#include <algorithm>

namespace Features {
	namespace Aimbot {
		static std::vector<Game::Panel*> cachedTargets;
		static DWORD lastTargetUpdate = 0;

		void Initialize() {
			printf("[Aimbot] Initialized\n");
		}

		void UpdateTargetCache() {
			DWORD now = GetTickCount();
			if (now - lastTargetUpdate < 500) return; // Update every 500ms

			cachedTargets.clear();

			auto targetObjects = Game::Objects::FindObjectsOfType<void>("Hyperstrange.WARPZ", "Panel");
			for (auto obj : targetObjects) {
				cachedTargets.push_back(new Game::Panel(obj));
			}

			lastTargetUpdate = now;
		}

		std::vector<Target> GetTargetsInFOV() {
			std::vector<Target> targets;

			auto player = Game::Player::GetLocalPlayer();
			if (!player || !player->IsValid()) return targets;

			auto camera = player->GetCamera();
			if (!camera) return targets;

			UpdateTargetCache();

			ImGuiIO& io = ImGui::GetIO();
			Unity::Vector2 screenCenter(io.DisplaySize.x / 2.0f, io.DisplaySize.y / 2.0f);

			for (auto targetObj : cachedTargets) {
				if (!targetObj || !targetObj->IsValid()) continue;

				Unity::Vector3 worldPos = targetObj->GetPosition();
				Unity::Vector3 screenPos3D = Game::WorldToScreen(camera, worldPos);

				if (screenPos3D.z < 0) continue; // Behind camera

				Unity::Vector2 screenPos(screenPos3D.x, screenPos3D.y);

				// Calculate FOV distance
				float dx = screenPos.x - screenCenter.x;
				float dy = screenPos.y - screenCenter.y;
				float fovDist = sqrtf(dx * dx + dy * dy);

				if (fovDist > Menu::Features::g_AimbotFOV) continue;

				Target t;
				t.worldPos = worldPos;
				t.screenPos = screenPos;
				t.distance = worldPos.Distance(player->GetPosition());
				t.fovDistance = fovDist;
				t.isVisible = true; // TODO: Implement raycast visibility check

				targets.push_back(t);
			}

			return targets;
		}

		Target* GetBestTarget() {
			static std::vector<Target> targets;
			targets = GetTargetsInFOV();

			if (targets.empty()) return nullptr;

			// Sort by FOV distance (closest to crosshair)
			std::sort(targets.begin(), targets.end(), [](const Target& a, const Target& b) {
				return a.fovDistance < b.fovDistance;
				});

			if (Menu::Features::g_AimbotVisibleOnly) {
				for (auto& target : targets) {
					if (target.isVisible) {
						return &target;
					}
				}
				return nullptr;
			}

			return &targets[0];
		}

		void AimAtTarget(const Target& target) {
			auto player = Game::Player::GetLocalPlayer();
			if (!player || !player->IsValid()) return;

			Unity::Vector3 cameraPos = player->GetCameraPosition();
			Unity::Vector3 direction = target.worldPos - cameraPos;

			float distance = sqrtf(direction.x * direction.x + direction.y * direction.y + direction.z * direction.z);
			if (distance < 0.001f) return;

			// Normalize
			direction.x /= distance;
			direction.y /= distance;
			direction.z /= distance;

			// Calculate target angles
			float pitch = asinf(-direction.y) * (180.0f / 3.14159265359f);
			float yaw = atan2f(direction.x, direction.z) * (180.0f / 3.14159265359f);

			// Convert to quaternion
			Unity::Quaternion targetRot = Unity::EulerToQuaternion(pitch, yaw, 0);

			// Get current rotation
			Unity::Quaternion currentRot = player->GetCameraRotation();

			// Apply smoothing
			float smoothFactor = 1.0f / Menu::Features::g_AimbotSmooth;
			Unity::Quaternion smoothedRot = Unity::Slerp(currentRot, targetRot, smoothFactor);

			// Set rotation
			player->SetCameraRotation(smoothedRot);
		}

		void Update() {
			if (!Menu::Features::g_Aimbot) return;

			// Bind to right mouse button (you can change this)
			if (GetAsyncKeyState(VK_RBUTTON) & 0x8000) {
				Target* target = GetBestTarget();
				if (target) {
					AimAtTarget(*target);
				}
			}
		}

		void Shutdown() {
			for (auto target : cachedTargets) {
				delete target;
			}
			cachedTargets.clear();
			printf("[Aimbot] Shut down\n");
		}
	}
}
