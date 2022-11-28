#include <iostream>
#include <shlwapi.h>
#include "Hooks.h"
#include "Keyboard.h"
#include "Filesystem.h"

#pragma comment (lib, "Shlwapi.lib")

void create_console()
{
	AllocConsole();

	FILE* console_stream{};

	freopen_s(&console_stream, "CONOUT$", "w", stderr);
}

void install()
{
	if (GetPrivateProfileInt("OPTIONS", "WARNING_WINDOW", 0, Filesystem::CONFIG_PATH.c_str()) == 1)
		MessageBox(NULL, "Do you know that DLL are very simmular to exe files ? They also can execute whatever code they want, only difference is that their main function executes only when you load it into memory region of other program. There are no viruses here but I just wanted you to think about your computer knowlages and Dunning–Kruger effect that may allow you to launch untrusted code from unknown source on your machine. (If you launch this on VM, I praise you, but that doesn't meant that now you see that nothing happened and you can launch it on your main machine (Again, this program do not contain malicious code, I just want to write this because I want people to learn a bit more about DLL, because for me it was like a magic a long time, and I think many people don't have a clue that it can be dangerous too (everyone known about exe,but not everyone about DLL)))\nTo disable this window, change WARNING_WINDOW in [OPTIONS] section of pkSeedKeys.ini to 0 and place file into the game folder.", "Think about", MB_OK | MB_ICONWARNING);
	//SHMessageBoxCheck(NULL,"Do you know that DLL are very simmular to exe files ? They also can execute whatever code they want, only difference is that their main function executes only when you load it into memory region of other program. There are no viruses here but I just wanted you to think about your computer knowlages and Dunning–Kruger effect that may allow you to launch untrusted code from unknown source on your machine. (If you launch this on VM, I praise you, but that doesn't meant that now you see that nothing happened and you can launch it on your main machine (Again, this program do not contain malicious code, I just want to write this because I want people to learn a bit more about DLL, because for me it was like a magic a long time, and I think many people don't have a clue that it can be dangerous too (everyone known about exe,but not everyone about DLL)))\nTo disable this window change WARNING_WINDOW in pkSeedKeys.ini to 0","Think about",MB_OK,IDYES, "{d9530153-9a61-4398-bfbc-b0582385918a}"); Keyboard_Storages::Utils::initialize_heys_storages();
	Keyboard_Storages::Utils::initialize_keys_storages();
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