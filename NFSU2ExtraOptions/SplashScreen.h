#include "stdio.h"
#include <windows.h>
#include "InGameFunctions.h"

char* TakeoverString = "NFSU2 Extra Options - © 2022 ExOpts Team. No rights reserved.";

// 0x4A91B6
void __declspec(naked) SplashScreenCodeCave()
{
	_asm
	{
		// Make License thing visible
		call FEngSetVisible
		mov eax, [esi + 4] // package name
		push TakeoverString
		push 0x4B98C4B9 // "LICENSEBLURB"
		push eax
		call FEPrintf
		add esp, 0xC

		// Move Copyright a bit up
		mov eax, [esi + 4] // package name
		push 0xC70CCFC7
		push eax
		call FEngFindObject
		add esp, 8

		push 0x433A0000 // 186.0f
		push 0
		push eax
		call FEngSetCenter
		add esp, 0xC

		// Move LicenseBlurb under the copyright
		mov eax, [esi + 4] // package name
		push 0x4B98C4B9 // "LICENSEBLURB"
		push eax
		call FEngFindObject
		add esp, 8

		push 0x434C0000 // 204.0f
		push 0
		push eax
		call FEngSetCenter
		add esp, 0xC

		push 0x4A91BB
		retn
	}
}