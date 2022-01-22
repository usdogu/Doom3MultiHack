#include "pch.h"
#include "mem.h"
#include "hacks.h"
void HealthHack(const uintptr_t moduleBase, const bool state)
{
    if (state)
    {
        mem::Nop((BYTE*)moduleBase + 0x2F96C5, 6);
    }
    else
    {
        // mov [esi + 000000D8], eax
        mem::Patch((BYTE*)moduleBase + 0x2F96C5, (BYTE*)"\x89\x86\xD8\x00\x00\x00", 6);
    }
}

void ArmorHack(const uintptr_t moduleBase, const bool state)
{
    if (state)
    {
        mem::Nop((BYTE*)moduleBase + 0x2F9BD3, 6);
    }
    else
    {
        // sub [esi+000017FC],eax
        mem::Patch((BYTE*)moduleBase + 0x2F9BD3, (BYTE*)"\x29\x86\xFC\x17\x00\x00", 6);
    }
}

void AmmoHack(const uintptr_t moduleBase, const bool state)
{
    if (state)
    {
        mem::Nop((BYTE*)moduleBase + 0x32689B, 2);
    }
    else
    {
        // sub [esi],ecx
        mem::Patch((BYTE*)moduleBase + 0x32689B, (BYTE*)"\x29\x0e", 2);
    }
}