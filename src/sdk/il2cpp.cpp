#include "pch.h"
#include "sdk/il2cpp.h"

namespace IL2CPP {
	bool Initialize() {
		HMODULE gameAssembly = GetModuleHandleA("GameAssembly.dll");
		if (!gameAssembly) {
			MessageBoxA(NULL, "GameAssembly.dll not found", "Error", MB_OK);
			return false;
		}

		// Resolve IL2CPP API functions
		domain_get = reinterpret_cast<decltype(domain_get)>(GetProcAddress(gameAssembly, "il2cpp_domain_get"));
		domain_get_assemblies = reinterpret_cast<decltype(domain_get_assemblies)>(GetProcAddress(gameAssembly, "il2cpp_domain_get_assemblies"));
		assembly_get_image = reinterpret_cast<decltype(assembly_get_image)>(GetProcAddress(gameAssembly, "il2cpp_assembly_get_image"));
		class_from_name = reinterpret_cast<decltype(class_from_name)>(GetProcAddress(gameAssembly, "il2cpp_class_from_name"));
		class_get_methods = reinterpret_cast<decltype(class_get_methods)>(GetProcAddress(gameAssembly, "il2cpp_class_get_methods"));
		class_get_method_from_name = reinterpret_cast<decltype(class_get_method_from_name)>(GetProcAddress(gameAssembly, "il2cpp_class_get_method_from_name"));
		class_get_field_from_name = reinterpret_cast<decltype(class_get_field_from_name)>(GetProcAddress(gameAssembly, "il2cpp_class_get_field_from_name"));
		method_get_name = reinterpret_cast<decltype(method_get_name)>(GetProcAddress(gameAssembly, "il2cpp_method_get_name"));
		method_get_class = reinterpret_cast<decltype(method_get_class)>(GetProcAddress(gameAssembly, "il2cpp_method_get_class"));
		class_get_name = reinterpret_cast<decltype(class_get_name)>(GetProcAddress(gameAssembly, "il2cpp_class_get_name"));
		object_new = reinterpret_cast<decltype(object_new)>(GetProcAddress(gameAssembly, "il2cpp_object_new"));
		resolve_icall = reinterpret_cast<decltype(resolve_icall)>(GetProcAddress(gameAssembly, "il2cpp_resolve_icall"));

		if (!domain_get || !class_from_name) {
			MessageBoxA(NULL, "Failed to resolve IL2CPP functions", "Error", MB_OK);
			return false;
		}

		printf("[IL2CPP] Initialized successfully\n");
		return true;
	}

	void* GetClassFromName(const char* namespaze, const char* className) {
		void* domain = domain_get();
		size_t assemblyCount = 0;
		void** assemblies = domain_get_assemblies(domain, &assemblyCount);

		for (size_t i = 0; i < assemblyCount; i++) {
			void* image = assembly_get_image(assemblies[i]);
			void* klass = class_from_name(image, namespaze, className);
			if (klass) {
				printf("[IL2CPP] Found class: %s.%s\n", namespaze, className);
				return klass;
			}
		}

		printf("[IL2CPP] Failed to find class: %s.%s\n", namespaze, className);
		return nullptr;
	}

	void* GetMethodFromName(void* klass, const char* methodName, int argCount) {
		if (!klass) return nullptr;

		void* method = class_get_method_from_name(klass, methodName, argCount);
		if (method) {
			printf("[IL2CPP] Found method: %s\n", methodName);
		}
		else {
			printf("[IL2CPP] Failed to find method: %s\n", methodName);
		}
		return method;
	}

	uintptr_t GetFieldOffset(void* klass, const char* fieldName) {
		if (!klass) return 0;

		void* field = class_get_field_from_name(klass, fieldName);
		if (!field) {
			printf("[IL2CPP] Failed to find field: %s\n", fieldName);
			return 0;
		}

		// Field offset is at +0x18 in the field structure
		uintptr_t offset = *(uintptr_t*)((uintptr_t)field + 0x18);
		printf("[IL2CPP] Found field: %s at offset 0x%llX\n", fieldName, offset);
		return offset;
	}
}
