#include "Hooks.h"
#include "Keyboard.h"
void __declspec(naked) __stdcall grab_tool_wrapper(int object_type, Game* game)
{
	__asm {
		push        ebp
		mov         ebp, esp
		sub         esp, __LOCAL_SIZE
		push eax
		push ebx
		push ecx
		push edx
		push esi
		push edi
		mov ebx, game
		mov edx, object_type
		sub edx, 3
		call Hooks_T::Addresses::grab_tool.address
		pop edi
		pop esi
		pop edx
		pop ecx
		pop ebx
		pop eax
		mov         esp, ebp
		pop         ebp
		ret
	}
}

void __cdecl handle_virtual_keys_hook(unsigned int VK_Key)
{
	using namespace Keyboard_Storages;

	Seed_packet* tmp = ((Seed_packet*)Memory::dereference_multilevel_pointer((uintptr_t*)(Hooks_T::Addresses::module_base + 0x002A71A8), { 0x68,0x768,0x144,0x28 }));
	Game* game = ((tmp != nullptr) ? tmp->game : nullptr);
	if (game == nullptr or game->bIsGamePaused == 1)
		goto end;
	switch (game->game_params->additional_levels_id)
	{
	case Addition_Levels_ID::Zen_Garden:
	{
		int action{ Utils::get_action_id(Utils::get_vk_action_name(Zen_Garden::zen_garden_keys, VK_Key)) };
		if (action != -1)
			grab_tool_wrapper(action, game);
		break;
	}
	case Addition_Levels_ID::Wisdom_Tree:
	{
		int action{ Utils::get_action_id(Utils::get_vk_action_name(Wisdom_Tree::wisdom_tree_keys, VK_Key)) };
		if (action != -1)
			grab_tool_wrapper(action, game);
		break;
	}
	default:
		const std::string& action_name{ Utils::get_vk_action_name(Seeds::seed_keys,VK_Key) };
		if (game->game_field->HoldingObjectType_or_isHoldingSmth != 0)
			((Hooks_T::Release_Seed_Function)Hooks_T::Addresses::release_seed.address)(-1, 0, game, 0, 0); // Drops the packet so the previosly selected seed packet could be reset to it's original state

		if (action_name == Seeds::Strings::SHOVEL)
			grab_tool_wrapper(Map_Keys::Tools::SHOVEL + 2, game); // there is ingame enums typecast, so in their enum shovel == 5
		else
		{
			unsigned int offset{ Utils::get_index_of_vk(Seeds::seed_keys, VK_Key) };
			if (offset == -1) break;
			Seed_packet* seed_slot_address = (Seed_packet*)Memory::dereference_multilevel_pointer((uintptr_t*)(Hooks_T::Addresses::module_base + 0x002A71A8), { 0x68,0x768,0x144,0x28 + 0x50 * offset });
			if (seed_slot_address != nullptr and seed_slot_address->game->bIsGamePaused != 1)
				((Hooks_T::Choose_Seed_Function)Hooks_T::Addresses::choose_seed.address)((DWORD*)seed_slot_address);
		}
		break;
	}
	end:
	;
}


void __declspec(naked) handle_virtual_keys_hook_wrapper()
{
	__asm {
		xchg eax, ecx
		push ecx
		push edx
		push eax
		call handle_virtual_keys_hook
		pop eax
		pop edx
		pop ecx
		xchg eax, ecx
		call Hooks_T::Addresses::handle_virtual_keys.address
		ret
	}
}

Hook_Object::Hook_Object(const Memory::Hex_bytes& aob_bytes)
	: aob_bytes{ aob_bytes }, address{}
{
}

Hook_Object::Hook_Object(uintptr_t address)
	: address{address}
{
}

[[nodiscard]] std::thread Hook_Object::find_address(uintptr_t module_base)
{
	if (aob_bytes.empty())
		return std::thread{};
	using namespace Hooks_T::Addresses;
	auto aob_scan_wrapper = [](uintptr_t& return_value, BYTE* module_base, const Memory::Hex_bytes& bytes)
	{
		return_value = Memory::aob_scan(module_base, bytes);
	};
	std::thread thread(aob_scan_wrapper, std::ref(address), (BYTE*)module_base, std::ref(Hook_Object::aob_bytes));
	return thread;
}

bool Hook_Object::install(uintptr_t hook_address,bool call_hook)
{
	if (!original_bytes.empty() or !address)
		return false;
	Memory::create_hook(hook_address, address, call_hook);

	return true;
}

bool Hook_Object::uninstall()
{
	if (original_bytes.empty())
		return false;
	return true;
}



namespace Hooks_T
{
	namespace Utils
	{
		bool find_addresses()
		{
			using namespace Hooks_T::Addresses;
			module_base = (uintptr_t)GetModuleHandle(NULL);
			std::vector<std::thread> threads;
			threads.push_back(handle_virtual_keys_call.find_address(module_base));
			threads.push_back(choose_seed.find_address(module_base));
			threads.push_back(release_seed.find_address(module_base));
			threads.push_back(handle_virtual_keys.find_address(module_base));
			threads.push_back(grab_tool.find_address(module_base));

			for (auto& thread : threads)
			{
				if (thread.joinable())
					thread.join();
			}
			return true;
		}

		bool install()
		{
			if (!find_addresses()) return false;
			Memory::create_hook(Addresses::handle_virtual_keys_call.address, (uintptr_t)handle_virtual_keys_hook_wrapper, true);
			return true;
		}

		bool uninstall()
		{

			return true;
		}
	}

	namespace Addresses
	{
		extern uintptr_t module_base{};
		extern Hook_Object handle_virtual_keys_call{{ 0xE8, Memory::AOB_SKIP, Memory::AOB_SKIP, Memory::AOB_SKIP, Memory::AOB_SKIP, 0xE9, Memory::AOB_SKIP, Memory::AOB_SKIP, Memory::AOB_SKIP, Memory::AOB_SKIP, 0x8B, 0x83, Memory::AOB_SKIP, Memory::AOB_SKIP, Memory::AOB_SKIP, Memory::AOB_SKIP, 0x8B, 0x4C, 0x24, Memory::AOB_SKIP }}; //0x0055040F
		extern Hook_Object choose_seed{{ 0x6A, 0xFF, 0x64, 0xA1, Memory::AOB_SKIP, Memory::AOB_SKIP, Memory::AOB_SKIP, Memory::AOB_SKIP, 0x68, Memory::AOB_SKIP, Memory::AOB_SKIP, Memory::AOB_SKIP, Memory::AOB_SKIP, 0x50, 0x64, 0x89, 0x25, Memory::AOB_SKIP, Memory::AOB_SKIP, Memory::AOB_SKIP, Memory::AOB_SKIP, 0x83, 0xEC, 0x54, 0x53, 0x55, 0x8B, 0x6C, 0x24, 0x6C }}; //0x00488590
		extern Hook_Object release_seed{{ 0x6A, 0xFF, 0x68, Memory::AOB_SKIP, Memory::AOB_SKIP, Memory::AOB_SKIP, Memory::AOB_SKIP, 0x64, 0xA1, Memory::AOB_SKIP, Memory::AOB_SKIP, Memory::AOB_SKIP, Memory::AOB_SKIP, 0x50, 0x64, 0x89, 0x25, Memory::AOB_SKIP, Memory::AOB_SKIP, Memory::AOB_SKIP, Memory::AOB_SKIP, 0x81, 0xEC, Memory::AOB_SKIP, Memory::AOB_SKIP, Memory::AOB_SKIP, Memory::AOB_SKIP, 0x85, 0xC9 }}; //0x0040FD30
		extern Hook_Object handle_virtual_keys{{0x81, 0xF9, Memory::AOB_SKIP, Memory::AOB_SKIP, Memory::AOB_SKIP, Memory::AOB_SKIP, 0x8B, 0x50, Memory::AOB_SKIP, 0x89, 0x90, Memory::AOB_SKIP, Memory::AOB_SKIP, Memory::AOB_SKIP, Memory::AOB_SKIP, 0x77, 0x08, 0xC6, 0x84, 0x01, Memory::AOB_SKIP, Memory::AOB_SKIP, Memory::AOB_SKIP, Memory::AOB_SKIP, Memory::AOB_SKIP, 0x8B, 0x80, Memory::AOB_SKIP, Memory::AOB_SKIP, Memory::AOB_SKIP, Memory::AOB_SKIP }}; //0x00539660
		extern Hook_Object grab_tool{ 0x00411C10 }; //0x00411C10

	}

	//namespace Wrappers
	//{

	//}
}

