#include "pch.h"
#include "game/game_objects.h"

namespace Game {
	// Static members
	void* Objects::playerClass = nullptr;
	void* Objects::panelClass = nullptr;
	void* Objects::finishPanelClass = nullptr;
	void* Objects::transformClass = nullptr;
	void* Objects::cameraClass = nullptr;

	void Objects::Initialize() {
		printf("[GameObjects] Initializing...\n");

		playerClass = IL2CPP::GetClassFromName("Hyperstrange.WARPZ", "Player");
		panelClass = IL2CPP::GetClassFromName("Hyperstrange.WARPZ", "Panel");
		finishPanelClass = IL2CPP::GetClassFromName("Hyperstrange.WARPZ", "FinishPanel");
		transformClass = IL2CPP::GetClassFromName("UnityEngine", "Transform");
		cameraClass = IL2CPP::GetClassFromName("UnityEngine", "Camera");

		if (!playerClass) printf("[!] Failed to find Player class\n");
		if (!panelClass) printf("[!] Failed to find Panel class\n");
		if (!finishPanelClass) printf("[!] Failed to find FinishPanel class\n");

		printf("[GameObjects] Initialized\n");
	}

	void* Objects::GetObjectsOfType(void* klass) {
		if (!klass) return nullptr;

		// Use Unity's Object.FindObjectsOfType
		// This is an internal Unity function we need to call via IL2CPP
		using FindObjectsOfType_t = void* (__fastcall*)(void*, bool);
		static auto findObjects = reinterpret_cast<FindObjectsOfType_t>(
			IL2CPP::resolve_icall("UnityEngine.Object::FindObjectsOfType(System.Type,System.Boolean)")
			);

		if (!findObjects) {
			printf("[!] Failed to resolve FindObjectsOfType\n");
			return nullptr;
		}

		// Call with includeInactive = false
		return findObjects(klass, false);
	}

	template<typename T>
	std::vector<T*> Objects::FindObjectsOfType(const char* namespaze, const char* className) {
		std::vector<T*> result;

		void* klass = IL2CPP::GetClassFromName(namespaze, className);
		if (!klass) return result;

		void* objArray = GetObjectsOfType(klass);
		if (!objArray) return result;

		// Cast to Il2CppArray
		auto* arr = reinterpret_cast<Unity::Il2CppArray<void*>*>(objArray);

		for (size_t i = 0; i < arr->max_length; i++) {
			if (arr->items[i]) {
				result.push_back(reinterpret_cast<T*>(arr->items[i]));
			}
		}

		return result;
	}

	template<typename T>
	T* Objects::FindObjectOfType(const char* namespaze, const char* className) {
		auto objects = FindObjectsOfType<T>(namespaze, className);
		return objects.empty() ? nullptr : objects[0];
	}

	// Explicit template instantiations
	template std::vector<void*> Objects::FindObjectsOfType<void>(const char*, const char*);
	template void* Objects::FindObjectOfType<void>(const char*, const char*);

	// Player implementation
	static Player* g_cachedPlayer = nullptr;

	Player* Player::GetLocalPlayer() {
		// Try cached first
		if (g_cachedPlayer && g_cachedPlayer->IsValid()) {
			return g_cachedPlayer;
		}

		// Find new instance
		void* playerInst = Objects::FindObjectOfType<void>("Hyperstrange.WARPZ", "Player");
		if (playerInst) {
			g_cachedPlayer = new Player(playerInst);
			return g_cachedPlayer;
		}

		return nullptr;
	}

	Unity::Camera* Player::GetCamera() {
		if (!instance) return nullptr;
		return *reinterpret_cast<Unity::Camera**>((uintptr_t)instance + Offsets::Player::Camera);
	}

	Unity::Transform* Player::GetCameraTransform() {
		if (!instance) return nullptr;
		return *reinterpret_cast<Unity::Transform**>((uintptr_t)instance + Offsets::Player::_cameraTransform);
	}

	Unity::Transform* Player::GetTransform() {
		if (!instance) return nullptr;
		// Component base class has transform at 0x10
		return *reinterpret_cast<Unity::Transform**>((uintptr_t)instance + 0x10);
	}

	Unity::Vector3 Player::GetPosition() {
		auto transform = GetTransform();
		if (!transform) return Unity::Vector3();

		using GetPosition_t = Unity::Vector3(__fastcall*)(Unity::Transform*);
		static auto fn = reinterpret_cast<GetPosition_t>(
			(uintptr_t)GetModuleHandleA("GameAssembly.dll") + Offsets::Transform::get_position
			);

		return fn(transform);
	}

	Unity::Vector3 Player::GetCameraPosition() {
		auto transform = GetCameraTransform();
		if (!transform) return Unity::Vector3();

		using GetPosition_t = Unity::Vector3(__fastcall*)(Unity::Transform*);
		static auto fn = reinterpret_cast<GetPosition_t>(
			(uintptr_t)GetModuleHandleA("GameAssembly.dll") + Offsets::Transform::get_position
			);

		return fn(transform);
	}

	Unity::Quaternion Player::GetCameraRotation() {
		auto transform = GetCameraTransform();
		if (!transform) return Unity::Quaternion();

		using GetRotation_t = Unity::Quaternion(__fastcall*)(Unity::Transform*);
		static auto fn = reinterpret_cast<GetRotation_t>(
			(uintptr_t)GetModuleHandleA("GameAssembly.dll") + Offsets::Transform::get_rotation
			);

		return fn(transform);
	}

	void Player::SetCameraRotation(const Unity::Quaternion& rot) {
		auto transform = GetCameraTransform();
		if (!transform) return;

		using SetRotation_t = void(__fastcall*)(Unity::Transform*, Unity::Quaternion);
		static auto fn = reinterpret_cast<SetRotation_t>(
			(uintptr_t)GetModuleHandleA("GameAssembly.dll") + Offsets::Transform::set_rotation
			);

		fn(transform, rot);
	}

	bool Player::IsActive() {
		if (!instance) return false;
		return *reinterpret_cast<bool*>((uintptr_t)instance + Offsets::Player::IsActive);
	}

	float Player::GetCurrentSpeed() {
		if (!instance) return 0.0f;
		// ObscuredFloat - we'll just read raw value for now
		// TODO: Decrypt ObscuredFloat properly
		uintptr_t speedPtr = (uintptr_t)instance + Offsets::Player::CurrentSpeed;
		return *reinterpret_cast<float*>(speedPtr);
	}

	// Panel implementation
	Unity::Transform* Panel::GetTransform() {
		if (!instance) return nullptr;
		return *reinterpret_cast<Unity::Transform**>((uintptr_t)instance + 0x10);
	}

	Unity::Vector3 Panel::GetPosition() {
		auto transform = GetTransform();
		if (!transform) return Unity::Vector3();

		using GetPosition_t = Unity::Vector3(__fastcall*)(Unity::Transform*);
		static auto fn = reinterpret_cast<GetPosition_t>(
			(uintptr_t)GetModuleHandleA("GameAssembly.dll") + Offsets::Transform::get_position
			);

		return fn(transform);
	}

	// Helper functions
	Unity::Vector3 WorldToScreen(Unity::Camera* camera, const Unity::Vector3& worldPos) {
		if (!camera) return Unity::Vector3();

		using WorldToScreenPoint_t = Unity::Vector3(__fastcall*)(Unity::Camera*, Unity::Vector3, int);
		static auto fn = reinterpret_cast<WorldToScreenPoint_t>(
			(uintptr_t)GetModuleHandleA("GameAssembly.dll") + Offsets::Camera::WorldToScreenPoint
			);

		return fn(camera, worldPos, 0); // MonoOrStereoscopicEye = 0
	}

	bool IsOnScreen(const Unity::Vector3& screenPos) {
		if (screenPos.z < 0.0f) return false;

		ImGuiIO& io = ImGui::GetIO();
		float w = io.DisplaySize.x;
		float h = io.DisplaySize.y;

		return screenPos.x >= 0 && screenPos.x <= w &&
			screenPos.y >= 0 && screenPos.y <= h;
	}
}
