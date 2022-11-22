#ifndef MEMORY_WORK_H
#define MEMORY_WORK_H

#include <iostream>
#include <vector>
#include <Windows.h>

namespace Memory
{
	const unsigned int AOB_SKIP{ 0xFFFF };

	using Hex_bytes = std::vector<unsigned int>;

	uintptr_t aob_scan(BYTE* module_base,const Hex_bytes& bytes);

	uintptr_t dereference_multilevel_pointer(uintptr_t* base_address,const  Memory::Hex_bytes offsets);

	Hex_bytes nop(BYTE* address, int size);

	void byte_patch(BYTE* address,const  Hex_bytes& bytes);

	uintptr_t create_hook(uintptr_t hook_address, uintptr_t detour_address, bool call_hook);
}; 

std::ostream& operator<< (std::ostream& out, const Memory::Hex_bytes& arr);

#endif // !MEMORY_WORK_H
