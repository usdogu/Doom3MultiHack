// dllmain.cpp : DLL uygulamasının giriş noktasını tanımlar.
#include "pch.h"
#include "mem.h"

DWORD WINAPI HackThread(HMODULE hModule)
{
    AllocConsole();
    FILE* f;
    freopen_s(&f, "CONOUT$", "w", stdout);
    std::cout << "Hack Started" << std::endl;
    const auto moduleBase = (uintptr_t)GetModuleHandle(L"Doom3BFG.exe");
    bool bHealth = false, bArmor = false, bAmmo = false;
    while (true)
    {
        if (GetAsyncKeyState(VK_END) & 1) {
            break;
        }
        if (GetAsyncKeyState(VK_NUMPAD1) & 1) {
            bHealth = !bHealth;
        }
        if (GetAsyncKeyState(VK_NUMPAD2) & 1) {
            bArmor = !bArmor;

        }
        if (GetAsyncKeyState(VK_NUMPAD3) & 1) {
            bAmmo = !bAmmo;
            
        }
        if (bAmmo)
        {
            mem::Nop((BYTE*)moduleBase + 0x32689B, 2);
        }
        else
        {
            mem::Patch((BYTE*)moduleBase + 0x32689B, (BYTE*)"\x29\x0e", 2);
        }
        Sleep(5);
    }
    fclose(f);
    FreeConsole();
    FreeLibraryAndExitThread(hModule, 0);
    return 0;
}


BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        CloseHandle(CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)HackThread, hModule, 0, nullptr));
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

