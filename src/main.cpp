#include "pch.h"
#include "hooks.h"
#include "sdk/il2cpp.h"
#include "features/speedhack.h"
#include "features/noclip.h"
#include "features/esp.h"
#include "features/aimbot.h"

DWORD WINAPI MainThread(LPVOID param) {
	AllocConsole();
	FILE* f;
	freopen_s(&f, "CONOUT$", "w", stdout);

	printf("[RAYZE Internal] Initializing...\n");

	if (MH_Initialize() != MH_OK) {
		printf("[!] Failed to initialize MinHook\n");
		MessageBoxA(NULL, "Failed to initialize MinHook", "Error", MB_OK);
		return 1;
	}

	// Wait for GameAssembly
	while (!GetModuleHandleA("GameAssembly.dll")) {
		Sleep(100);
	}

	if (!IL2CPP::Initialize()) {
		printf("[!] Failed to initialize IL2CPP\n");
		return 1;
	}

	// Initialize features
	Features::Speedhack::Initialize();
	Features::Noclip::Initialize();
	Features::ESP::Initialize();
	Features::Aimbot::Initialize();

	if (!Hooks::Init()) {
		printf("[!] Failed to initialize hooks\n");
		return 1;
	}

	printf("[+] Initialized successfully! Press END to unload\n");

	// Main loop for features that need updates
	while (!GetAsyncKeyState(VK_END)) {
		Features::Speedhack::Update();
		Features::Noclip::Update();
		Features::Aimbot::Update();
		// ESP renders in Present hook

		Sleep(10); // ~100 FPS update rate
	}

	printf("[*] Unloading...\n");

	// Cleanup
	Features::Speedhack::Shutdown();
	Features::Noclip::Shutdown();
	Features::ESP::Shutdown();
	Features::Aimbot::Shutdown();

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
