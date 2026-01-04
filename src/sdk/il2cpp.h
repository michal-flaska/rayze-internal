#pragma once
#include "pch.h"

// the dumpers il2cpp.h stays in il2cpp-dumper/ -> we will reference it for offsets/signatures

namespace IL2CPP {
	// IL2CPP API function pointers
	inline void* (*domain_get)();
	inline void** (*domain_get_assemblies)(void* domain, size_t* size);
	inline void* (*assembly_get_image)(void* assembly);
	inline void* (*class_from_name)(void* image, const char* namespaze, const char* name);
	inline void* (*class_get_methods)(void* klass, void** iter);
	inline void* (*class_get_method_from_name)(void* klass, const char* name, int argsCount);
	inline void* (*class_get_field_from_name)(void* klass, const char* name);
	inline const char* (*method_get_name)(void* method);
	inline void* (*method_get_class)(void* method);
	inline const char* (*class_get_name)(void* klass);
	inline void* (*object_new)(void* klass);
	inline void* (*resolve_icall)(const char* name);

	bool Initialize();
	void* GetClassFromName(const char* namespaze, const char* className);
	void* GetMethodFromName(void* klass, const char* methodName, int argCount = -1);
	uintptr_t GetFieldOffset(void* klass, const char* fieldName);

	template<typename T>
	T GetStaticFieldValue(void* klass, const char* fieldName) {
		void* field = class_get_field_from_name(klass, fieldName);
		if (!field) return T();

		// Get static field value - offset 0x10 in field structure typically
		void* staticData = *(void**)((uintptr_t)klass + 0xB8);
		uintptr_t fieldOffset = *(uintptr_t*)((uintptr_t)field + 0x18);
		return *(T*)((uintptr_t)staticData + fieldOffset);
	}
}
