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
		if (!arr) return result;

		// Validate array before accessing
		if (arr->max_length > 10000) {
			printf("[!] Suspicious array length: %zu\n", arr->max_length);
			return result;
		}

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

		// Clear invalid cached player
		if (g_cachedPlayer) {
			delete g_cachedPlayer;
			g_cachedPlayer = nullptr;
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

		__try {
			Unity::Camera* cam = *reinterpret_cast<Unity::Camera**>((uintptr_t)instance + Offsets::Player::Camerak__BackingField);
			// Basic validation - check if pointer seems reasonable
			if ((uintptr_t)cam < 0x10000 || (uintptr_t)cam > 0x7FFFFFFFFFFF) {
				return nullptr;
			}
			return cam;
		}
		__except (EXCEPTION_EXECUTE_HANDLER) {
			return nullptr;
		}
	}

	Unity::Transform* Player::GetCameraTransform() {
		if (!instance) return nullptr;

		__try {
			Unity::Transform* transform = *reinterpret_cast<Unity::Transform**>((uintptr_t)instance + Offsets::Player::_cameraTransform);
			// Basic validation
			if ((uintptr_t)transform < 0x10000 || (uintptr_t)transform > 0x7FFFFFFFFFFF) {
				return nullptr;
			}
			return transform;
		}
		__except (EXCEPTION_EXECUTE_HANDLER) {
			return nullptr;
		}
	}

	Unity::Transform* Player::GetTransform() {
		if (!instance) return nullptr;

		__try {
			// Component base class has transform at 0x10
			Unity::Transform* transform = *reinterpret_cast<Unity::Transform**>((uintptr_t)instance + 0x10);
			// Basic validation
			if ((uintptr_t)transform < 0x10000 || (uintptr_t)transform > 0x7FFFFFFFFFFF) {
				return nullptr;
			}
			return transform;
		}
		__except (EXCEPTION_EXECUTE_HANDLER) {
			return nullptr;
		}
	}

	Unity::Vector3 Player::GetPosition() {
		auto transform = GetTransform();
		if (!transform) return Unity::Vector3();

		__try {
			using GetPosition_t = Unity::Vector3(__fastcall*)(Unity::Transform*);
			static auto fn = reinterpret_cast<GetPosition_t>(
				(uintptr_t)GetModuleHandleA("GameAssembly.dll") + Offsets::Unity::Transform_get_position
				);

			if (!fn) return Unity::Vector3();

			return fn(transform);
		}
		__except (EXCEPTION_EXECUTE_HANDLER) {
			return Unity::Vector3();
		}
	}

	Unity::Vector3 Player::GetCameraPosition() {
		auto transform = GetCameraTransform();
		if (!transform) return Unity::Vector3();

		__try {
			using GetPosition_t = Unity::Vector3(__fastcall*)(Unity::Transform*);
			static auto fn = reinterpret_cast<GetPosition_t>(
				(uintptr_t)GetModuleHandleA("GameAssembly.dll") + Offsets::Unity::Transform_get_position
				);

			if (!fn) return Unity::Vector3();

			return fn(transform);
		}
		__except (EXCEPTION_EXECUTE_HANDLER) {
			return Unity::Vector3();
		}
	}

	Unity::Quaternion Player::GetCameraRotation() {
		auto transform = GetCameraTransform();
		if (!transform) return Unity::Quaternion();

		__try {
			using GetRotation_t = Unity::Quaternion(__fastcall*)(Unity::Transform*);
			static auto fn = reinterpret_cast<GetRotation_t>(
				(uintptr_t)GetModuleHandleA("GameAssembly.dll") + Offsets::Unity::Transform_get_rotation
				);

			if (!fn) return Unity::Quaternion();

			return fn(transform);
		}
		__except (EXCEPTION_EXECUTE_HANDLER) {
			return Unity::Quaternion();
		}
	}

	void Player::SetCameraRotation(const Unity::Quaternion& rot) {
		auto transform = GetCameraTransform();
		if (!transform) return;

		__try {
			using SetRotation_t = void(__fastcall*)(Unity::Transform*, Unity::Quaternion);
			static auto fn = reinterpret_cast<SetRotation_t>(
				(uintptr_t)GetModuleHandleA("GameAssembly.dll") + Offsets::Unity::Transform_set_rotation
				);

			if (!fn) return;

			fn(transform, rot);
		}
		__except (EXCEPTION_EXECUTE_HANDLER) {
			printf("[!] Exception in SetCameraRotation\n");
		}
	}

	bool Player::IsActive() {
		if (!instance) return false;
		return *reinterpret_cast<bool*>((uintptr_t)instance + Offsets::Player::IsActivek__BackingField);
	}

	float Player::GetCurrentSpeed() {
		if (!instance) return 0.0f;

		// Get the movement component
		void* movementComponent = *reinterpret_cast<void**>((uintptr_t)instance + Offsets::Player::_movementComponent);
		if (!movementComponent) return 0.0f;

		// Read _currentAcceleration which is a plain float (not obfuscated)
		uintptr_t speedFieldPtr = (uintptr_t)movementComponent + Offsets::PlayerMovementComponent::_currentAcceleration;
		return *reinterpret_cast<float*>(speedFieldPtr);
	}

	// Panel implementation
	Unity::Transform* Panel::GetTransform() {
		if (!instance) return nullptr;

		__try {
			Unity::Transform* transform = *reinterpret_cast<Unity::Transform**>((uintptr_t)instance + 0x10);
			// Basic validation
			if ((uintptr_t)transform < 0x10000 || (uintptr_t)transform > 0x7FFFFFFFFFFF) {
				return nullptr;
			}
			return transform;
		}
		__except (EXCEPTION_EXECUTE_HANDLER) {
			return nullptr;
		}
	}

	bool Panel::IsActive() {
		if (!instance) return false;

		__try {
			// Call the virtual get_IsActive() function at RVA 0x3FBFA0
			using GetIsActive_t = bool(__fastcall*)(void*);
			static auto fn = reinterpret_cast<GetIsActive_t>(
				(uintptr_t)GetModuleHandleA("GameAssembly.dll") + 0x3FBFA0
			);

			if (!fn) return false;
			return fn(instance);
		}
		__except (EXCEPTION_EXECUTE_HANDLER) {
			return false;
		}
	}

	Unity::Vector3 Panel::GetPosition() {
		auto transform = GetTransform();
		if (!transform) return Unity::Vector3();

		__try {
			using GetPosition_t = Unity::Vector3(__fastcall*)(Unity::Transform*);
			static auto fn = reinterpret_cast<GetPosition_t>(
				(uintptr_t)GetModuleHandleA("GameAssembly.dll") + Offsets::Unity::Transform_get_position
				);

			if (!fn) return Unity::Vector3();

			return fn(transform);
		}
		__except (EXCEPTION_EXECUTE_HANDLER) {
			return Unity::Vector3();
		}
	}

	// Helper functions
	Unity::Vector3 WorldToScreen(Unity::Camera* camera, const Unity::Vector3& worldPos) {
		if (!camera) return Unity::Vector3();

		__try {
			using WorldToScreenPoint_t = Unity::Vector3(__fastcall*)(Unity::Camera*, Unity::Vector3, int);
			static auto fn = reinterpret_cast<WorldToScreenPoint_t>(
				(uintptr_t)GetModuleHandleA("GameAssembly.dll") + Offsets::Unity::Camera_WorldToScreenPoint
				);

			if (!fn) return Unity::Vector3();

			return fn(camera, worldPos, 0); // MonoOrStereoscopicEye = 0
		}
		__except (EXCEPTION_EXECUTE_HANDLER) {
			return Unity::Vector3();
		}
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
