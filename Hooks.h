#ifndef HOOKS_H
#define HOOKS_H

#include <thread>
#include "Memory work.h"
#include "IDA_Stuff.h"

class Hook_Object
{
public:
	Hook_Object(const Memory::Hex_bytes& aob_bytes);

	Hook_Object(uintptr_t address);

	[[nodiscard]] std::thread find_address(uintptr_t module_base);

	bool install(uintptr_t hook_address, bool call_hook);

	bool uninstall();

	uintptr_t address;

private:
	const Memory::Hex_bytes aob_bytes;

	Memory::Hex_bytes original_bytes;

};

namespace Hooks_T
{
	using Choose_Seed_Function = void(__stdcall*)(DWORD*);
	using Release_Seed_Function = int(__fastcall*)(int, int, Game*, int, int);
	using Handle_Virtual_Keys = char (*)(unsigned int, DWORD*);
	using Grab_Tool = void (_fastcall*)();
	namespace Utils
	{
		bool find_addresses();

		bool install();

		bool uninstall_hooks();
	}


	namespace Addresses
	{
		extern uintptr_t module_base;
		extern Hook_Object handle_virtual_keys_call; //0x0055040F
		extern Hook_Object choose_seed; //0x00488590
		extern Hook_Object release_seed; //0x0040FD30
		extern Hook_Object handle_virtual_keys; //0x00539660
		extern Hook_Object grab_tool; //0x00411C10
	}
	//namespace Wrappers
	//{
	//	
	//}

}

#endif // !HOOKS_H


