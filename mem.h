#pragma once
#include <vector>

namespace mem
{
	void Patch(BYTE* dst, const BYTE* src, unsigned size);
	void Nop(BYTE* dst, const unsigned int size);
	uintptr_t FindDMAaddy(const uintptr_t ptr, const std::vector<unsigned int>& offsets);
	bool Detour32(BYTE* src, BYTE* dst, const uintptr_t len);
	BYTE* TrampHook32(BYTE* src, BYTE* dst, const uintptr_t len);

}

