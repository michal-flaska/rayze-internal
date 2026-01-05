#include "pch.h"
#include "utils/memory.h"

namespace Memory {
	uintptr_t PatternScan(const char* moduleName, const char* pattern, const char* mask) {
		HMODULE module = GetModuleHandleA(moduleName);
		if (!module) return 0;

		MODULEINFO moduleInfo;
		GetModuleInformation(GetCurrentProcess(), module, &moduleInfo, sizeof(MODULEINFO));

		return PatternScan((uintptr_t)module, moduleInfo.SizeOfImage, pattern, mask);
	}

	uintptr_t PatternScan(uintptr_t start, size_t size, const char* pattern, const char* mask) {
		size_t patternLen = strlen(mask);

		for (uintptr_t i = 0; i < size - patternLen; i++) {
			bool found = true;
			for (size_t j = 0; j < patternLen; j++) {
				if (mask[j] != '?' && pattern[j] != *(char*)(start + i + j)) {
					found = false;
					break;
				}
			}
			if (found) {
				return start + i;
			}
		}

		return 0;
	}
}
