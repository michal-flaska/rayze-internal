#include "pch.h"
#include "hooks.h"
#include "sdk/il2cpp.h"

DWORD WINAPI MainThread(LPVOID param) {
	AllocConsole();
	FILE* f;
	freopen_s(&f, "CONOUT$", "w", stdout);

	printf("[RAYZE Internal] Initializing...\n");

	// Initialize MinHook
	if (MH_Initialize() != MH_OK) {
		printf("[!] Failed to initialize MinHook\n");
		MessageBoxA(NULL, "Failed to initialize MinHook", "Error", MB_OK);
		return 1;
	}

	// Wait for GameAssembly to load
	while (!GetModuleHandleA("GameAssembly.dll")) {
		Sleep(100);
	}

	// Initialize IL2CPP
	if (!IL2CPP::Initialize()) {
		printf("[!] Failed to initialize IL2CPP\n");
		return 1;
	}

	// Initialize hooks
	if (!Hooks::Init()) {
		printf("[!] Failed to initialize hooks\n");
		return 1;
	}

	printf("[+] Initialized successfully! Press END to unload\n");

	// Wait for unload
	while (!GetAsyncKeyState(VK_END)) {
		Sleep(100);
	}

	printf("[*] Unloading...\n");

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
