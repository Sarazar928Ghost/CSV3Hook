// dllmain.cpp : Defines the entry point for the DLL application.
#include "stdafx.h"

extern void csv3_init(HMODULE hModule);

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:

		// Patch limiteur FPS - LEA EDX,[ECX+19] → LEA EDX,[ECX+7]
		{
			DWORD dwOld1;
			PBYTE fpsAddr1 = (PBYTE)0x005DF751;
			VirtualProtect(fpsAddr1, 3, PAGE_EXECUTE_READWRITE, &dwOld1);
			fpsAddr1[2] = 0x07;
			VirtualProtect(fpsAddr1, 3, dwOld1, &dwOld1);
		}

		// Patch limiteur FPS - ADD ECX,19 → ADD ECX,7
		{
			DWORD dwOld2;
			PBYTE fpsAddr2 = (PBYTE)0x005DF75A;
			VirtualProtect(fpsAddr2, 3, PAGE_EXECUTE_READWRITE, &dwOld2);
			fpsAddr2[2] = 0x07;
			VirtualProtect(fpsAddr2, 3, dwOld2, &dwOld2);
		}

		/*
		// Patch couleur items au sol - JE -> JMP
		{
			DWORD dwOld;
			PBYTE colorAddr = (PBYTE)0x00645495;
			VirtualProtect(colorAddr, 2, PAGE_EXECUTE_READWRITE, &dwOld);
			colorAddr[0] = 0xEB; // JMP court
			colorAddr[1] = 0x00; // offset 0 = saute juste après
			VirtualProtect(colorAddr, 2, dwOld, &dwOld);
		}
		*/
		/*
		// Patch couleur item rareté 9 (Super)
		{
			DWORD dwOld;
			PBYTE colorAddr = (PBYTE)0x0070A25C;
			VirtualProtect(colorAddr, 6, PAGE_EXECUTE_READWRITE, &dwOld);
			// BB XX XX XX XX = MOV EBX, valeur (5 octets)
			// colorAddr[0] = 0xBB déjà correct
			colorAddr[1] = 0x13;
			colorAddr[2] = 0x3A;
			colorAddr[3] = 0xFF;
			colorAddr[4] = 0xFF;
			VirtualProtect(colorAddr, 6, dwOld, &dwOld);
		}
		*/
		// Patch distance Chebyshev ( 0x12 -> 0x16 ) ( 18 -> 22 )
		{
			DWORD dwOld;
			PBYTE distance = (PBYTE)0x0061E865;
			VirtualProtect(distance, 3, PAGE_EXECUTE_READWRITE, &dwOld);
			distance[2] = 0x16;
			VirtualProtect(distance, 3, dwOld, &dwOld);
		}
		// Patch distance Chebyshev ( 0x12 -> 0x16 ) ( 18 -> 22 )
		{
			DWORD dwOld;
			PBYTE distance = (PBYTE)0x0061E879;
			VirtualProtect(distance, 3, PAGE_EXECUTE_READWRITE, &dwOld);
			distance[2] = 0x16;
			VirtualProtect(distance, 3, dwOld, &dwOld);
		}
		// On change le mov en xor afin de mettre esi a 0 pour bypass le packet nécessaire pour SaintCloudJar's
		{
			DWORD dwOld;
			PBYTE distance = (PBYTE)0x005AC347;
			VirtualProtect(distance, 2, PAGE_EXECUTE_READWRITE, &dwOld);
			distance[0] = 0x31;
			distance[1] = 0xF6;
			VirtualProtect(distance, 2, dwOld, &dwOld);
		}
		// sub to add for SaintCloudJar's. C'est pour savoir combien de monstre est tué actuellement
		{
			DWORD dwOld;
			PBYTE distance = (PBYTE)0x005AC36B;
			VirtualProtect(distance, 2, PAGE_EXECUTE_READWRITE, &dwOld);
			distance[0] = 0x03;
			distance[1] = 0xF0;
			VirtualProtect(distance, 2, dwOld, &dwOld);
		}

		csv3_init(hModule);
		break;
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}

