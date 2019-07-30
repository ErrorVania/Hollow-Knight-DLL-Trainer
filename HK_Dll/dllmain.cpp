#include "stdafx.h"
#include <iostream>
#include <string>
#include <Windows.h>
#include <TlHelp32.h>
#include <tchar.h>

#define HEALTH_OFFSET 0xE4
#define SOUL_OFFSET 0x120
#define GEO_OFFSET 0x118
#define USED_NOTCHES 0x420
#define invinciTest 0xb49
#define infiniteAirJump 0xb48

/*DWORD getBasefromMono(DWORD mono_address) {
	//I have no clue how i would do this with pointers. Sorry.
	
	/*ReadProcessMemory(handle, (LPCVOID)(mono_address + 0x001F50AC), &e, sizeof(DWORD), NULL);
	ReadProcessMemory(handle, (LPCVOID)(e + 0x3B4), &e, sizeof(DWORD), NULL);
	ReadProcessMemory(handle, (LPCVOID)(e + 0xC), &e, sizeof(DWORD), NULL);
	ReadProcessMemory(handle, (LPCVOID)(e + 0x20), &e, sizeof(DWORD), NULL);
	ReadProcessMemory(handle, (LPCVOID)(e + 0x2C), &e, sizeof(DWORD), NULL);

	//turns out i do. neat
	/*DWORD* stage1 = (DWORD*)(mono_address + 0x001F50AC);
	DWORD* stage2 = (DWORD*)(*stage1 + 0x3B4);
	DWORD* stage3 = (DWORD*)(*stage2 + 0xC);
	DWORD* stage4 = (DWORD*)(*stage3 + 0x20);
	DWORD* stage5 = (DWORD*)(*stage4 + 0x2C);


	//shortened
	DWORD* stage5 = (DWORD*)(*(DWORD*)(*(DWORD*)(*(DWORD*)(*(DWORD*)(mono_address + 0x001F50AC) + 0x3B4) + 0xC) + 0x20) + 0x2C);

	return *stage5;
}*/



DWORD WINAPI run(LPVOID lpParam) {
	FILE *fDummy;
	DWORD mono, base, *health_addr, *soul_addr, *geo_addr, *used_notches_addr, *invincibilityTest_addr, *infiniteAirJumps_addr;
	BOOL infsoul = false, infnotches = false, godmode = false, infjump = false;

	mono = (DWORD)GetModuleHandleA("mono.dll");
	base = (*(DWORD*)(*(DWORD*)(*(DWORD*)(*(DWORD*)(mono + 0x001F50AC) + 0x3B4) + 0xC) + 0x20) + 0x2C);

	health_addr = (DWORD*)(base + HEALTH_OFFSET);
	soul_addr = (DWORD*)(base + SOUL_OFFSET);
	geo_addr = (DWORD*)(base + GEO_OFFSET);
	used_notches_addr = (DWORD*)(base + USED_NOTCHES);
	invincibilityTest_addr = (DWORD*)(base + invinciTest);
	infiniteAirJumps_addr = (DWORD*)(base + infiniteAirJump);


	AllocConsole();
	freopen_s(&fDummy, "CONOUT$", "w", stdout);

	std::cout << "Mono.dll Address -> 0x" << std::hex << mono << std::endl;
	std::cout << "Base Address -> 0x" << std::hex << base << std::endl;
	std::cout << "DBG_Feature1 Address -> 0x" << std::hex << invincibilityTest_addr << std::endl;
	std::cout << "DBG_Feature2 -> 0x" << std::hex << infiniteAirJumps_addr << std::endl; 
	std::cout << "Health Address -> 0x" << std::hex << health_addr << std::endl;
	std::cout << "Soul Address -> 0x" << std::hex << soul_addr << std::endl; 
	std::cout << "Geo Address -> 0x" << std::hex << geo_addr << std::endl;
	std::cout << "Used Notches Address -> 0x" << std::hex << used_notches_addr << std::endl;
	std::cout << "Press F1 to toggle godmode" << std::endl
		<< "Press F2 to toggle infinite soul mode" << std::endl
		<< "Press F3 to toggle infinite jump mode" << std::endl
		<< "Press F4 to toggle infinite notches mode" << std::endl;
	while (1) {
		if (GetAsyncKeyState(VK_F1) & 0x8000) {
			godmode = !godmode;
			std::cout << "Godmode -> " << godmode << std::endl;
		}
		if (GetAsyncKeyState(VK_F2) & 0x8000) {
			infsoul = !infsoul;
			std::cout << "Infsoul -> " << infsoul << std::endl;
		}
		if (GetAsyncKeyState(VK_F3) & 0x8000) {
			infjump = !infjump;
			std::cout << "Infinite Jumps -> " << infjump << std::endl;
		}
		if (GetAsyncKeyState(VK_F4) & 0x8000) {
			infnotches = !infnotches;
			std::cout << "(Unequip all notches before disabling!)Infinite notches -> " << infnotches << std::endl;
		}




		*invincibilityTest_addr = godmode;
		*infiniteAirJumps_addr = infjump;
		if (infsoul) 
			*soul_addr = 99;
		if (infnotches) 
			*used_notches_addr = 1;
		Sleep(200);
	}
	return 0;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
		CreateThread(NULL, 0, &run, NULL, 0, NULL);
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}


