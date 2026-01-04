#include "pch.h"
#include "features/noclip.h"
#include "gui/menu.h"
#include "game/entities.h"

namespace Features {
	namespace Noclip {
		// Hook CharacterController or Rigidbody collision
		// For Unity IL2CPP, we need to hook the collision detection

		typedef bool(__fastcall* OnControllerColliderHit_t)(void*, void*);
		static OnControllerColliderHit_t oOnControllerColliderHit = nullptr;

		bool __fastcall hkOnControllerColliderHit(void* thisPtr, void* hit) {
			if (Menu::Features::g_Noclip) {
				// Block collision
				return false;
			}
			return oOnControllerColliderHit(thisPtr, hit);
		}

		void Initialize() {
			// TODO: Find and hook CharacterController collision methods
			// This requires finding the vtable or method address
			printf("[Noclip] Initialized\n");
		}

		void Update() {
			if (!Menu::Features::g_Noclip) return;

			// Alternative approach: Disable collider directly
			auto player = Game::Player::GetLocalPlayer();
			if (!player) return;

			// Method 1: Set player position directly (teleport through walls)
			// Method 2: Disable physics layers
			// Method 3: Hook collision detection (implemented above)
		}

		void Shutdown() {
			if (oOnControllerColliderHit) {
				MH_DisableHook((void*)oOnControllerColliderHit);
			}
		}
	}
}
