#include "stdio.h"
#include <windows.h>
#include "..\includes\injector\injector.hpp"
#include "..\includes\IniReader.h"

void __declspec(naked) VinylCategoryCodeCave()
{
	_asm
	{
		push 0xE79A53F8 // Debug String Hash
		push 0x93EC1CE9 // NFSU2 Icon Hash
		push 0x1C // Hidden vinyl category
		mov ecx, esi
		call AddCustomElementToMenu
		mov eax, [esi + 0x04]
		push eax
		call FEHashUpper
		push 0x546265
		retn
	}
}

void __declspec(naked) DriftMultiplierCodeCave()
{
	_asm
	{
		fmul dword ptr ds : [0x925100]
		fstp dword ptr[esp + 0x40]
		mov edx, [esp + 0x70]
		push 0x56DB59
		retn
	}

}

void __declspec(naked) BarrierCodeCave()
{
	_asm
	{
		movsx eax, word ptr[eax + 0x8A]
		cmp eax, 4600
		jge fixbarriers
		cmp eax, 4300
		jge drifttrack
		jmp removebarriers

		drifttrack :
			cmp eax, 4399
			jle fixbarriers
			jmp removebarriers

		fixbarriers :
			mov byte ptr ds : [0x7a078b] , 73
			mov byte ptr ds : [0x7a0798] , 73
			jmp BarrierCodeCaveExit

		removebarriers :
			mov byte ptr ds : [0x7a078b] , 77
			mov byte ptr ds : [0x7a0798] , 77
			jmp BarrierCodeCaveExit

		BarrierCodeCaveExit:
			push 0x578077
			retn
	}

}

void __declspec(naked) StartingCashCodeCave()
{
	_asm
	{
		push eax
		mov eax, StartingCash
		mov dword ptr ds : [esi + 0x7134] , eax
		pop eax
		push 0x532913
		retn
	}
}

void __declspec(naked) DebugCarCustomizeCodeCave()
{
	_asm
	{
		mov edx, [edi]
		push eax
		mov ecx, edi
		call dword ptr ds : [edx + 0x18]
		push 0x4C
		call j__malloc
		add esp, 4
		cmp eax, ebx
		je DCCJump1
		push ebx
		push 0xE79A53F8 // "Debug"
		push 0x74CE8C0B // UI_ICON_DEBUG
		push 0x04 // 4 = UI_DebugCarCustomize.fng
		mov ecx, eax
		call AddElementToMenuWithStateID
		jmp DCCJump2

		DCCJump1 :
		xor eax, eax

			DCCJump2 :
		mov edx, [edi]
			push eax
			mov ecx, edi

			push 0x520F51
			retn
	}
}

bool __cdecl RegionLockHook(int CarID)
{
	return 1;
}

void __declspec(naked) ProfileNameFilterCodeCave()
{
	_asm
	{
		push aDVD
		push ebx
		call _strstr // If it's a DVD cover
		add esp, 8
		test al, al
		jnz SkipThisProfile

		push aMagazine
		push ebx
		call _strstr // If it's a Magazine cover
		add esp, 8
		test al, al
		jnz SkipThisProfile

		originalcode :
			mov eax, [esi + 0x48]
			mov ecx, [esi + 0x4C]
			push 0x4E9122
			retn

		SkipThisProfile :
			push 0x4E9130
			retn
	}
}

void __declspec(naked) ShowDebugEventIDLearnCodeCave()
{
	_asm
	{
		mov DebugEventID, ecx
		call SelectableTrack_CalcLanguageHash
		push 0x4CE19D
		retn
	}
}

void __declspec(naked) ShowDebugEventIDPrintCodeCave()
{
	_asm
	{
		call FEngSetVisible
		mov eax, DebugEventID
		push eax
		push 0x007880C0 // "Track %d"
		push 0x53C956C4 // Debug Event ID object hash
		push edi // FNG name
		call FEPrintf
		add esp, 0x10
		push 0x4CE1C9
		retn
	}
}

void __declspec(naked) FixMenuProfileNameLengthCodeCave()
{
	_asm
	{
		push ebx
		mov ebx, eax
		push 0xEB406FEC // Profile Name
		push 0x790000 // UI_PC_Help_Bar.fng
		call FEngFindObject
		mov[eax + 0x68], 0x10 // String length
		add esp, 8
		mov eax, ebx
		pop ebx
		push 0x83A9E0 // Profile Name
		push 0x54E74B
		retn
	}
}

void __declspec(naked) MegalowPartsFixCodeCave()
{
	__asm
	{

		xor al, al
		mov ecx, 0x1A
		mov[ebx + 0xB4], ecx
		push 0x46B405
		retn

	}
}
