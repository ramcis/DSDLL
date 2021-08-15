// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"
#include <Windows.h>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <locale>
#include "proc.cpp"


typedef void(__fastcall* _AddSoulsFunc)(int souls);
typedef void(__fastcall* _applyEffectFunc)(int effect);
typedef void(__fastcall* _NetPacketSend)(int packetID);
typedef void(__fastcall* _SaveRequest)();

void __fastcall RebirthFunc(void);
void __fastcall LevelUpFunc(void);
void __stdcall  EffectCall(long);
void __fastcall introMovieCall(void);
void __fastcall AddSoulsCall(long, unsigned int);
void __fastcall YoelMenuCall(void);
void __fastcall AllotEstusCall(void);
void __fastcall BonefireMenuCall();
void __fastcall ArenaMenuCall();
void __fastcall StorageBoxMenuCall();
void __fastcall luaCallSOS(uintptr_t , int32_t );


uintptr_t moduleBase = (uintptr_t)GetModuleHandle("DarkSoulsIII.exe");

void __fastcall RebirthFunc(void)
{
    typedef void(__fastcall* pFunctionAddress)();
    pFunctionAddress pWinFunction = (pFunctionAddress)(0x140EEC9D0); //Our new address 140EEC9D0 0xEEC9D0
    pWinFunction(); 
}

void __fastcall LevelUpFunc(void)
{
    typedef void(__fastcall* pFunctionAddress)();
    pFunctionAddress pWinFunction = (pFunctionAddress)(0x140EEC870);
    pWinFunction();
}

void __fastcall YoelMenuCall(void)
{
    typedef void(__fastcall* pFunctionAddress)();
    pFunctionAddress pWinFunction = (pFunctionAddress)(0x140EEC300); //Our new address 140EEC9D0 0xEEC9D0
    pWinFunction();
}

void __fastcall AllotEstusCall(void)
{
    typedef void(__fastcall* pFunctionAddress)();
    pFunctionAddress pWinFunction = (pFunctionAddress)(0x140EEC360); //Our new address 140EEC9D0 0xEEC9D0
    pWinFunction();
}

void __fastcall BonefireMenuCall()
{
    typedef void(__fastcall* pFunctionAddress)();
    pFunctionAddress pWinFunction = (pFunctionAddress)(0x140EECA90);
    pWinFunction();
}

void __fastcall StorageBoxMenuCall()
{
    typedef void(__fastcall* pFunctionAddress)();
    pFunctionAddress pWinFunction = (pFunctionAddress)(0x140EEC8D0);
    pWinFunction();
}

void __fastcall ArenaMenuCall()
{
    typedef void(__fastcall* pFunctionAddress)();
    pFunctionAddress pWinFunction = (pFunctionAddress)(0x140EEC6F0);
    pWinFunction();

}

void __fastcall introMovieCall(void)
{
    typedef void(__fastcall* pFunctionAddress)();
    pFunctionAddress pWinFunction = (pFunctionAddress)(0x140ADE740);
    pWinFunction();
}


void __fastcall AddSoulsCall(long baseAdr,unsigned int amount)
{

    typedef void(__fastcall* psFunctionAddress)(long, unsigned int);
    psFunctionAddress psWinFunction = (psFunctionAddress)(0x14047D54D);
    psWinFunction(baseAdr,amount);
}


void __fastcall EffectCall(long bonfire)
{
    typedef void(__fastcall* p2FunctionAddress)(long);
    p2FunctionAddress p2WinFunction = (p2FunctionAddress)(moduleBase + 0xAE69A0); //Our new address
    p2WinFunction(bonfire);
}
void __fastcall luaCallSOS(uintptr_t chrIns, int32_t sosFlag)
{
     void(*CallSOS)(...);
    *(uintptr_t*)&CallSOS = 0x1408B0BE0;
    CallSOS(chrIns, sosFlag);
}

_AddSoulsFunc AddSoulsFunc;
_applyEffectFunc applyEffectFunc;
_NetPacketSend NetPacketSend;


DWORD WINAPI HackThread(HMODULE hModule)
{
    AllocConsole();
    FILE* f;
    freopen_s(&f, "CONOUT$", "w", stdout);

    std::cout << "Hello there, we are injected!\n";
    uintptr_t moduleBase = (uintptr_t)GetModuleHandle("DarkSoulsIII.exe");

 /*   int hooklength = 5;
    DWORD hookAddrr = 0xEEC9D2;
    jmpBackAddy = hookAddrr + hooklength;
    DetourFunction64((void*)hookAddrr, ourFunc, hooklength);*/
    DWORD procId = GetProcId(L"DarkSoulsIII.exe");
    HANDLE hProcess = 0;
    hProcess = OpenProcess(PROCESS_ALL_ACCESS, NULL, procId);
    std::vector<unsigned int> ammoOffsets = { 0x80, 0x1FA0 };
    DWORD ammoptr = FindDMAAddy(hProcess, 0x144768E78, ammoOffsets);

    AddSoulsFunc = (_AddSoulsFunc)(moduleBase + 0x8B8ED5);
    NetPacketSend = (_NetPacketSend)(moduleBase + 0x8A7194);

    uintptr_t dynamicPtrBaseAddr = 0x144768E78;
   // std::vector<unsigned int> ammoOffsets = { 0x80, 0x1F90, 0x18, 0xD8 };
    std::vector<unsigned int> playerOffsets = { 0x80 };
   // uintptr_t ammoAddr = FindDMAAddy(hProcess, dynamicPtrBaseAddr, ammoOffsets);
    //HANDLE hProcess = 0;
    uintptr_t playerAddr = FindDMAAddy(hProcess, dynamicPtrBaseAddr, playerOffsets);
    std::cout << "ammoAddr = " << "0x" << std::hex << playerAddr << std::endl;
    while (true)
    {
   
        if (GetAsyncKeyState(VK_NUMPAD1) & 1)
        {
            luaCallSOS(0x144768ef8,2);
          //  RebirthFunc();
        }
        if (GetAsyncKeyState(VK_NUMPAD2) & 1)
        {  
            //EffectCall(4002950);
            LevelUpFunc();
        }
        if (GetAsyncKeyState(VK_NUMPAD3) & 1)
        {
            introMovieCall();
            // AddSoulsCall(0x14476AE98,25);
        }
        if (GetAsyncKeyState(VK_NUMPAD4) & 1)
        {
            YoelMenuCall();
        }
        if (GetAsyncKeyState(VK_NUMPAD5) & 1)
        {
            AllotEstusCall();
        }
        if (GetAsyncKeyState(VK_NUMPAD6) & 1)
        {
            ArenaMenuCall();
        }
        if (GetAsyncKeyState(VK_NUMPAD7) & 1)
        {
            StorageBoxMenuCall();
        }
        Sleep(100);
    }
    //FreeLibraryAndExitThread((HMODULE)param, 0);
    fclose(f);
    FreeConsole();
    FreeLibraryAndExitThread(hModule, 0);
    return TRUE;
}

void* DetourFunction64(void* pSource, void* pDestination, int dwLen)
{
    DWORD MinLen = 14;

    if (dwLen < MinLen) return NULL;

    BYTE stub[] = {
    0xFF, 0x25, 0x00, 0x00, 0x00, 0x00, // jmp qword ptr [$+6]
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 // ptr
    };

    void* pTrampoline = VirtualAlloc(0, dwLen + sizeof(stub), MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);

    DWORD dwOld = 0;
    VirtualProtect(pSource, dwLen, PAGE_EXECUTE_READWRITE, &dwOld);

    DWORD64 retto = (DWORD64)pSource + dwLen;

    // trampoline
    memcpy(stub + 6, &retto, 8);
    memcpy((void*)((DWORD_PTR)pTrampoline), pSource, dwLen);
    memcpy((void*)((DWORD_PTR)pTrampoline + dwLen), stub, sizeof(stub));

    // orig
    memcpy(stub + 6, &pDestination, 8);
    memcpy(pSource, stub, sizeof(stub));

    for (int i = MinLen; i < dwLen; i++)
    {
        *(BYTE*)((DWORD_PTR)pSource + i) = 0x90;
    }

    VirtualProtect(pSource, dwLen, dwOld, &dwOld);
    return (void*)((DWORD_PTR)pTrampoline);
}

bool Hook(void* toHook, void* ourFunct, int len) {
    if (len < 5) {
        return false;
    }

    DWORD curProtection;
    VirtualProtect(toHook, len, PAGE_EXECUTE_READWRITE, &curProtection);

    memset(toHook, 0x90, len);

    DWORD relativeAddress = ((DWORD)ourFunct - (DWORD)toHook) - 5;

    *(BYTE*)toHook = 0xE9;
    *(DWORD*)((DWORD)toHook + 1) = relativeAddress;

    DWORD temp;
    VirtualProtect(toHook, len, curProtection, &temp);

    return true;
}

//DWORD jmpBackAddy;
//void __declspec(naked) ourFunc() {
//    __asm {
//        sub rsp, 28
//        mov edx, 000005DC
//        call DarkSoulsIII.exe + 846190
//        add rsp, 28
//        ret
//        jump [jmpBackAddy]
//    }
//}
//BOOL APIENTRY DllMain(HMODULE hModule,
//    DWORD  ul_reason_for_call,
//    LPVOID lpReserved
//)
//{
//    switch (ul_reason_for_call)
//    {
//    case DLL_PROCESS_ATTACH:
//        DisableThreadLibraryCalls(hModule);
//        CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)HackThread, hModule, 0, NULL);
//        break;
//    case DLL_PROCESS_DETACH:
//        break;
//    }
//    return TRUE;
//}
BOOL APIENTRY DllMain(HMODULE hModule,
    DWORD  ul_reason_for_call,
    LPVOID lpReserved
)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    {
        CloseHandle(CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)HackThread, hModule, 0, nullptr));
    }
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}
