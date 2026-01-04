#include "pch.h"
#include "hooks.h"
#include "sdk/il2cpp.h"
#include "game/game_objects.h"
#include "features/speedhack.h"
#include "features/noclip.h"
#include "features/esp.h"
#include "features/aimbot.h"

DWORD WINAPI MainThread(LPVOID param) {
	AllocConsole();
	FILE* f;
	freopen_s(&f, "CONOUT$", "w", stdout);

	printf("========================================\n");
	printf("  RAYZE Internal - Educational Only\n");
	printf("========================================\n");

	if (MH_Initialize() != MH_OK) {
		printf("[!] Failed to initialize MinHook\n");
		MessageBoxA(NULL, "Failed to initialize MinHook", "Error", MB_OK);
		return 1;
	}

	// Wait for GameAssembly
	printf("[*] Waiting for GameAssembly.dll...\n");
	while (!GetModuleHandleA("GameAssembly.dll")) {
		Sleep(100);
	}
	printf("[+] GameAssembly.dll loaded\n");

	// Initialize IL2CPP
	if (!IL2CPP::Initialize()) {
		printf("[!] Failed to initialize IL2CPP\n");
		return 1;
	}

	// Initialize game objects
	Game::Objects::Initialize();

	// Initialize hooks
	if (!Hooks::Init()) {
		printf("[!] Failed to initialize hooks\n");
		return 1;
	}

	// Initialize features
	Features::Speedhack::Initialize();
	Features::Noclip::Initialize();
	Features::ESP::Initialize();
	Features::Aimbot::Initialize();

	printf("\n========================================\n");
	printf("  Cheat loaded successfully!\n");
	printf("  INSERT - Toggle menu\n");
	printf("  END - Unload cheat\n");
	printf("========================================\n\n");

	// Main loop
	while (!(GetAsyncKeyState(VK_END) & 1)) {
		Features::Speedhack::Update();
		Features::Noclip::Update();
		Features::Aimbot::Update();

		Sleep(10);
	}

	printf("\n[*] Unloading...\n");

	// Cleanup
	Features::Aimbot::Shutdown();
	Features::ESP::Shutdown();
	Features::Noclip::Shutdown();
	Features::Speedhack::Shutdown();
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
