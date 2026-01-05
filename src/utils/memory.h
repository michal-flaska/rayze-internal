#pragma once
#include "pch.h"

namespace Memory {
	uintptr_t PatternScan(const char* moduleName, const char* pattern, const char* mask);
	uintptr_t PatternScan(uintptr_t start, size_t size, const char* pattern, const char* mask);

	template<typename T>
	inline T Read(uintptr_t address) {
		return *(T*)address;
	}

	template<typename T>
	inline void Write(uintptr_t address, T value) {
		DWORD oldProtect;
		VirtualProtect((void*)address, sizeof(T), PAGE_EXECUTE_READWRITE, &oldProtect);
		*(T*)address = value;
		VirtualProtect((void*)address, sizeof(T), oldProtect, &oldProtect);
	}

	template<typename T>
	inline T ReadPointer(uintptr_t base, std::vector<uintptr_t> offsets) {
		uintptr_t addr = base;
		for (size_t i = 0; i < offsets.size() - 1; i++) {
			addr = Read<uintptr_t>(addr + offsets[i]);
			if (!addr) return T();
		}
		return Read<T>(addr + offsets.back());
	}
}
