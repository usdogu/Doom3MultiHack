#include "pch.h"
#include "mem.h"
void mem::Patch(BYTE* dst, const BYTE* src, const unsigned size)
{
	DWORD oldProtect;
	VirtualProtect(dst, size, PAGE_EXECUTE_READWRITE, &oldProtect);
	memcpy(dst, src, size);
	VirtualProtect(dst, size, oldProtect, &oldProtect);
}

void mem::Nop(BYTE* dst, const unsigned int size)
{
	DWORD oldProtect;
	VirtualProtect(dst, size, PAGE_EXECUTE_READWRITE, &oldProtect);
	memset(dst, 0x90, size);
	VirtualProtect(dst, size, oldProtect, &oldProtect);
}

uintptr_t mem::FindDMAaddy(const uintptr_t ptr, const std::vector<unsigned int>& offsets)
{
	uintptr_t addr = ptr;
	for (const unsigned int offset : offsets)
	{
		addr = *(uintptr_t*)addr;
		addr += offset;
	}
	return addr;
}
