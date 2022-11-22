#include <iostream>
#include "Hooks.h"
#include "Keyboard.h"

void create_console()
{
	AllocConsole();

	FILE* console_stream{};

	freopen_s(&console_stream, "CONOUT$", "w", stderr);
}

void install()
{
	Keyboard_Storages::Utils::initialize_heys_storages();
	Hooks_T::Utils::install();
}

DWORD WINAPI HackThread(HMODULE hModule)
{
	//create_console();
		
	install();

	
	while (true)
	{
		Sleep(100);
	}

	//FreeConsole();
	FreeLibraryAndExitThread(hModule, 0);
	return 0;
}

BOOL APIENTRY DllMain(HMODULE hModule,
	DWORD  ul_reason_for_call,
	LPVOID lpReserved
)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		CloseHandle(CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)HackThread, hModule, 0, nullptr));
		break;
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}