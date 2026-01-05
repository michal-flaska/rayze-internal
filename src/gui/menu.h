#pragma once
#include "pch.h"

namespace Menu {
	void Render();

	// Menu state
	inline bool g_ShowMenu = true;
	inline bool g_ShowDemo = false;

	// Feature toggles
	namespace Features {
		inline bool g_Aimbot = false;
		inline float g_AimbotFOV = 100.0f;
		inline float g_AimbotSmooth = 5.0f;
		inline bool g_AimbotVisibleOnly = true;

		inline bool g_ESP = false;
		inline bool g_ESPTargets = true;
		inline bool g_ESPFinish = true;
		inline bool g_ESPButtons = true;
		inline bool g_ESPBoxes = false;
		inline bool g_ESPSnaplines = false;

		inline bool g_Speedhack = false;
		inline float g_SpeedhackMultiplier = 2.0f;

		inline bool g_Noclip = false;
	}
}
