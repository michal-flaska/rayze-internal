#include "pch.h"
#include "features/speedhack.h"
#include "sdk/offsets.h"
#include "gui/menu.h"

namespace Features {
	namespace Speedhack {
		void Update() {
			if (!Menu::Features::g_Speedhack) {
				// Reset to normal speed
				static bool wasEnabled = false;
				if (wasEnabled) {
					SetSpeed(1.0f);
					wasEnabled = false;
				}
				return;
			}

			SetSpeed(Menu::Features::g_SpeedhackMultiplier);
		}

		void SetSpeed(float multiplier) {
			// Call TimeManager.SetTimeScale(multiplier)
			using SetTimeScale_t = void(__fastcall*)(float);
			static auto fn = reinterpret_cast<SetTimeScale_t>(
				(uintptr_t)GetModuleHandleA("GameAssembly.dll") + Offsets::TimeManager::SetTimeScale
				);

			fn(multiplier);
		}

		float GetCurrentSpeed() {
			// Call TimeManager.get_CurrentTimeScale()
			using GetTimeScale_t = float(__fastcall*)();
			static auto fn = reinterpret_cast<GetTimeScale_t>(
				(uintptr_t)GetModuleHandleA("GameAssembly.dll") + Offsets::TimeManager::get_CurrentTimeScale
				);

			return fn();
		}
	}
}
