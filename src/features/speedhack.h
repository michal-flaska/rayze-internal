#pragma once
#include "pch.h"

namespace Features {
	namespace Speedhack {
		void Initialize();
		void Update();
		void Shutdown();
		void SetSpeed(float multiplier);
		float GetCurrentSpeed();
	}
}
