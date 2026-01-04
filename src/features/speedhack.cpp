#include "pch.h"
#include "features/speedhack.h"
#include "sdk/offsets.h"
#include "gui/menu.h"

namespace Features {
	namespace Speedhack {
		static bool wasEnabled = false;

		void Initialize() {
			printf("[Speedhack] Initialized\n");
		}

		void Update() {
			if (!Menu::Features::g_Speedhack) {
				if (wasEnabled) {
					SetSpeed(1.0f);
					wasEnabled = false;
				}
				return;
			}

			SetSpeed(Menu::Features::g_SpeedhackMultiplier);
			wasEnabled = true;
		}

		void SetSpeed(float multiplier) {
			using SetTimeScale_t = void(__fastcall*)(float);
			static auto fn = reinterpret_cast<SetTimeScale_t>(
				(uintptr_t)GetModuleHandleA("GameAssembly.dll") + Offsets::TimeManager::SetTimeScale
				);

			if (fn) {
				fn(multiplier);
			}
		}

		float GetCurrentSpeed() {
			using GetTimeScale_t = float(__fastcall*)();
			static auto fn = reinterpret_cast<GetTimeScale_t>(
				(uintptr_t)GetModuleHandleA("GameAssembly.dll") + Offsets::TimeManager::get_CurrentTimeScale
				);

			return fn ? fn() : 1.0f;
		}

		void Shutdown() {
			SetSpeed(1.0f);
			printf("[Speedhack] Shut down\n");
		}
	}
}
