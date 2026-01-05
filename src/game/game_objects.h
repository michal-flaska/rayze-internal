#pragma once
#include "pch.h"
#include "sdk/unity.h"
#include "sdk/il2cpp.h"

namespace Game {
	// Object finding utilities
	class Objects {
	public:
		static void Initialize();

		// Find objects by class
		template<typename T>
		static std::vector<T*> FindObjectsOfType(const char* namespaze, const char* className);

		// Find single object
		template<typename T>
		static T* FindObjectOfType(const char* namespaze, const char* className);

		// Cached instances
		static void* playerClass;
		static void* panelClass;
		static void* finishPanelClass;
		static void* transformClass;
		static void* cameraClass;

	private:
		static void* GetObjectsOfType(void* klass);
	};

	// Player wrapper
	class Player {
	private:
		void* instance;

	public:
		Player(void* inst) : instance(inst) {}

		static Player* GetLocalPlayer();

		void* GetInstance() { return instance; }
		bool IsValid() { return instance != nullptr; }

		Unity::Camera* GetCamera();
		Unity::Transform* GetCameraTransform();
		Unity::Transform* GetTransform();
		Unity::Vector3 GetPosition();
		Unity::Vector3 GetCameraPosition();
		Unity::Quaternion GetCameraRotation();
		void SetCameraRotation(const Unity::Quaternion& rot);
		bool IsActive();
		float GetCurrentSpeed();
	};

	// Panel wrapper
	class Panel {
	private:
		void* instance;

	public:
		Panel(void* inst) : instance(inst) {}

		void* GetInstance() { return instance; }
		bool IsValid() { return instance != nullptr; }

		Unity::Transform* GetTransform();
		Unity::Vector3 GetPosition();
		bool IsActive(); // Returns true if panel hasn't been hit yet
	};

	// Helper functions
	Unity::Vector3 WorldToScreen(Unity::Camera* camera, const Unity::Vector3& worldPos);
	bool IsOnScreen(const Unity::Vector3& screenPos);
}
