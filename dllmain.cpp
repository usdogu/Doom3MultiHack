#include "pch.h"
#include "hacks.h"
#include "mem.h"

typedef BOOL(__stdcall* twglSwapBuffers) (HDC hDc);

twglSwapBuffers owglSwapBuffers;

const auto moduleBase = (uintptr_t)GetModuleHandle(L"Doom3BFG.exe");
bool bHealth = false, bArmor = false, bAmmo = false;

BOOL __stdcall hkwglSwapBuffers(HDC hDc)
{
    if (GetAsyncKeyState(VK_NUMPAD1) & 1) {
        bHealth = !bHealth;
        HealthHack(moduleBase, bHealth);
    }
    if (GetAsyncKeyState(VK_NUMPAD2) & 1) {
        bArmor = !bArmor;
        ArmorHack(moduleBase, bArmor);

    }
    if (GetAsyncKeyState(VK_NUMPAD3) & 1) {
        bAmmo = !bAmmo;
        AmmoHack(moduleBase, bAmmo);
    }
    return owglSwapBuffers(hDc);
}


DWORD WINAPI HackThread(HMODULE hModule)
{
    AllocConsole();
    FILE* f;
    freopen_s(&f, "CONOUT$", "w", stdout);
    std::cout << "Hack Started" << std::endl;
    
    owglSwapBuffers = (twglSwapBuffers)GetProcAddress(GetModuleHandle(L"opengl32.dll"), "wglSwapBuffers");
    owglSwapBuffers = (twglSwapBuffers)mem::TrampHook32((BYTE*)owglSwapBuffers, (BYTE*)hkwglSwapBuffers, 5);
	
    fclose(f);
    FreeConsole();
    //FreeLibraryAndExitThread(hModule, 0);
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

