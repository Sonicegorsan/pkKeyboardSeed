#include "Memory work.h"

std::ostream& operator<< (std::ostream& out, const Memory::Hex_bytes& arr)
{
    if (!arr.empty())
    {
        out << '[';
        for (int i{}; i < arr.size(); ++i)
        {
            out << ' ';
            out << std::hex << "0x" << arr.at(i);
            if (i != arr.size() - 1)
                out << ','; 
            out << ' ';
        }
        out << ']';
    }
    return out;
}

uintptr_t Memory::aob_scan(BYTE* module_base, const Memory::Hex_bytes& bytes)
{
    DWORD old_memory_protection{};
    while (true)
    {
        bool scan_match{ true };
        try {
            VirtualProtect(module_base, bytes.size(), PAGE_EXECUTE_READWRITE, &old_memory_protection);

            for (int i{}; i < bytes.size(); ++i)
            {
                if (*module_base != bytes.at(i) and bytes.at(i) != AOB_SKIP)
                {
                    scan_match = false;
                    module_base -= i;
                    break;
                }
                ++module_base;
            }

            VirtualProtect(module_base, bytes.size(), old_memory_protection, NULL);

            if (scan_match)
            {
                VirtualProtect(module_base - bytes.size(), bytes.size(), old_memory_protection, NULL);
                return (uintptr_t)module_base - bytes.size();
            }
            ++module_base;
        }
        catch (...)
        {
            std::cerr << "AOB scan failed.\n";
            return (uintptr_t)nullptr;
        }
    }
}

uintptr_t Memory::dereference_multilevel_pointer(uintptr_t* base_address,const Memory::Hex_bytes offsets)
{
    
    base_address = (uintptr_t*)*base_address;
    try
    {
        for (int i{}; i < offsets.size() - 1; ++i)
        {
            base_address = (uintptr_t*)((uintptr_t)base_address + offsets.at(i));
            base_address = (uintptr_t*)*base_address;
        }
        return (uintptr_t)base_address + offsets.at(offsets.size() - 1);
    }
    catch (...)
    {
        return (uintptr_t)nullptr;
    }
}

Memory::Hex_bytes Memory::nop(BYTE* address, int size)
{
    Memory::Hex_bytes old_bytes(size);

    DWORD old_memory_protection{};
    VirtualProtect(address,size, PAGE_EXECUTE_READWRITE,&old_memory_protection);

    for (int i{};i<size;++i)
    {
        old_bytes.at(i) = *address;
        *address = 0x90;
        ++address;
    }

    VirtualProtect(address, size, old_memory_protection, NULL);

    return old_bytes;
}

void Memory::byte_patch(BYTE* address,const Memory::Hex_bytes& bytes)
{
    DWORD old_memory_protection{};
    VirtualProtect(address,bytes.size(), PAGE_EXECUTE_READWRITE, &old_memory_protection);

    for (int i{}; i < bytes.size(); ++i)
    {
        *address = bytes.at(i);
        ++address;
    }

    VirtualProtect(address, bytes.size(), old_memory_protection, NULL);
}

//Return detour return address
uintptr_t Memory::create_hook(uintptr_t hook_address, uintptr_t detour_address,bool call_hook) 
{
    DWORD old_memory_protection{};
    VirtualProtect((void*)hook_address, 5, PAGE_EXECUTE_READWRITE, &old_memory_protection);
    uintptr_t relativeAddress = detour_address - hook_address - 5;
    *(uintptr_t*)(hook_address + 1) = relativeAddress;

    if (call_hook)
    {

		Memory::byte_patch((BYTE*)hook_address, { 0xE8 }); // Call hook
        VirtualProtect((void*)hook_address, 5, old_memory_protection, NULL);
        return 0;
    }
    else
    {
		Memory::byte_patch((BYTE*)hook_address, { 0xE9 }); // Jmp hook
        VirtualProtect((void*)hook_address, 5, old_memory_protection, NULL);
        return hook_address + 5;
    }

}
