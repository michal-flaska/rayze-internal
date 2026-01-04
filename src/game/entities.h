#pragma once
#include "pch.h"
#include "sdk/unity.h"
#include "sdk/offsets.h"

namespace Game {
	class Player {
	public:
		static Player* GetLocalPlayer() {
			// TODO: Find player instance (singleton pattern or FindObjectOfType)
			return nullptr;
		}

		Unity::Camera* GetCamera() {
			return *reinterpret_cast<Unity::Camera**>((uintptr_t)this + Offsets::Player::Camera);
		}

		Unity::Transform* GetCameraTransform() {
			auto cam = GetCamera();
			if (!cam) return nullptr;

			// Camera inherits from Component which has transform
			return *reinterpret_cast<Unity::Transform**>((uintptr_t)cam + 0x10);
		}

		Unity::Transform* GetTransform() {
			// Component base class has transform at 0x10
			return *reinterpret_cast<Unity::Transform**>((uintptr_t)this + 0x10);
		}

		Unity::Vector3 GetPosition() {
			auto transform = GetTransform();
			if (!transform) return Unity::Vector3();

			// Call Transform.get_position
			using GetPosition_t = Unity::Vector3(__fastcall*)(Unity::Transform*);
			static auto fn = reinterpret_cast<GetPosition_t>(
				(uintptr_t)GetModuleHandleA("GameAssembly.dll") + Offsets::Transform::get_position
				);

			return fn(transform);
		}

		bool IsActive() {
			return *reinterpret_cast<bool*>((uintptr_t)this + Offsets::Player::IsActive);
		}

		float GetCurrentSpeed() {
			// ObscuredFloat is at offset, but we need to decrypt it
			// For now, just read the raw value
			uintptr_t speedPtr = (uintptr_t)this + Offsets::Player::CurrentSpeed;
			return *reinterpret_cast<float*>(speedPtr);
		}
	};

	class Panel {
	public:
		Unity::Transform* GetTransform() {
			return *reinterpret_cast<Unity::Transform**>((uintptr_t)this + 0x10);
		}

		Unity::Vector3 GetPosition() {
			auto transform = GetTransform();
			if (!transform) return Unity::Vector3();

			using GetPosition_t = Unity::Vector3(__fastcall*)(Unity::Transform*);
			static auto fn = reinterpret_cast<GetPosition_t>(
				(uintptr_t)GetModuleHandleA("GameAssembly.dll") + Offsets::Transform::get_position
				);

			return fn(transform);
		}
	};

	// Helper to call Camera.WorldToScreenPoint
	inline Unity::Vector3 WorldToScreen(Unity::Camera* camera, Unity::Vector3 worldPos) {
		if (!camera) return Unity::Vector3();

		using WorldToScreenPoint_t = Unity::Vector3(__fastcall*)(Unity::Camera*, Unity::Vector3, int);
		static auto fn = reinterpret_cast<WorldToScreenPoint_t>(
			(uintptr_t)GetModuleHandleA("GameAssembly.dll") + Offsets::Camera::WorldToScreenPoint
			);

		// MonoOrStereoscopicEye = 0 (Mono)
		return fn(camera, worldPos, 0);
	}
}
