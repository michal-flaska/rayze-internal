#include "pch.h"
#include "features/noclip.h"
#include "gui/menu.h"
#include "game/game_objects.h"

namespace Features {
	namespace Noclip {
		void Initialize() {
			printf("[Noclip] Initialized (debug mode - uses Player.DebugNoClip)\n");
		}

		void Update() {
			// RAYZE has built-in debug noclip we can enable
			// Check Player class - it has OnDebugNoClipChanged event and DebugNoClip property

			auto player = Game::Player::GetLocalPlayer();
			if (!player || !player->IsValid()) return;

			// For now, this is a placeholder
			// You'd need to find the debug component and set the noclip flag
			// Or hook movement/collision methods
		}

		void Shutdown() {
			printf("[Noclip] Shut down\n");
		}
	}
}
