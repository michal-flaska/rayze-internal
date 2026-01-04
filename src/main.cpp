#include "pch.h"
#include "hooks.h"

DWORD WINAPI MainThread(LPVOID param) {
	AllocConsole();
	FILE* f;
	freopen_s(&f, "CONOUT$", "w", stdout);

	if (MH_Initialize() != MH_OK) {
		MessageBoxA(NULL, "Failed to initialize MinHook", "Error", MB_OK);
		return 1;
	}

	// Initialize hooks
	Hooks::Init();

	// Wait for unload
	while (!GetAsyncKeyState(VK_END)) {
		Sleep(100);
	}

	// Cleanup
	Hooks::Shutdown();
	MH_Uninitialize();

	if (f) fclose(f);
	FreeConsole();
	FreeLibraryAndExitThread((HMODULE)param, 0);
	return 0;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD reason, LPVOID reserved) {
	if (reason == DLL_PROCESS_ATTACH) {
		DisableThreadLibraryCalls(hModule);
		CreateThread(nullptr, 0, MainThread, hModule, 0, nullptr);
	}
	return TRUE;
}
