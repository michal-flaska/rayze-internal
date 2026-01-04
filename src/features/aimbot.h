#pragma once
#include "pch.h"
#include "sdk/unity.h"

namespace Features {
	namespace Aimbot {
		void Initialize();
		void Update();
		void Shutdown();

		struct Target {
			Unity::Vector3 worldPos;
			Unity::Vector2 screenPos;
			float distance;
			float fovDistance;
			bool isVisible;
		};

		std::vector<Target> GetTargetsInFOV();
		Target* GetBestTarget();
		void AimAtTarget(const Target& target);
	}
}
