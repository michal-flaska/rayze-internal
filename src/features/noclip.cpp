#include "pch.h"
#include "features/noclip.h"
#include "gui/menu.h"
#include "game/game_objects.h"

namespace Features {
	namespace Noclip {
		void Initialize() {
			printf("[Noclip] Initialized (debug mode - uses Player.DebugNoClip)\n");
		}

		static bool wasEnabled = false;

		void Update() {
			if (!Menu::Features::g_Noclip) {
				if (wasEnabled) {
					printf("[Noclip] Disabled\n");
					wasEnabled = false;
				}
				return;
			}

			auto player = Game::Player::GetLocalPlayer();
			if (!player || !player->IsValid()) {
				if (wasEnabled) {
					printf("[Noclip] Player not found\n");
					wasEnabled = false;
				}
				return;
			}

			if (!wasEnabled) {
				printf("[Noclip] Enabled (debug mode)\n");
				wasEnabled = true;
			}

			// TODO: Actually implement noclip - need to find debug component or hook collision
		}

		void Shutdown() {
			printf("[Noclip] Shut down\n");
		}
	}
}
