#include "stdafx.h"
#include "stdio.h"
#include <windows.h>
#include "..\includes\injector\injector.hpp"
#include <cstdint>
#include "..\includes\IniReader.h"

DWORD WINAPI Thing(LPVOID);

unsigned char MinimumLap, MaximumLap, KOLap, MinimumCPU, MaximumCPU, KOCPU, MinimumLapLANC, MinimumLapLAND, MinimumLapLANS, MaximumLapLAN, MaximumPlayersLAN, MaximumDriftX;
bool DriftPlus, DriftMultiply, UnlockRegionals, UnlockAll, UnlockTracks, EnableTrackSelectForFreeRun, AnyTrackInAnyMode, RemoveRaceBarriers, RemoveLockedAreaBarriers;

float SplashScreenTimeLimit, NeonBrightness;
bool MorePaint, MoreVinyls, nlgzrgnTakeOver, EnableCameras, ShowOnline, ShowOutrun, EnableTrackSelectForOutrun, once1, once2, ShowSubtitles, EnableTrackNameHook, UnfreezeKO, CarbonStyleRaceStatus;
int DriftMutliplierThresholdPoints[] = { 350, 1400, 4200, 11200, 22400, 38080, 57120, 85680, 300, 1200, 3600, 9600, 19200, 32640, 48960, 73440, 250, 1000, 3000, 8000, 16000, 27200, 40800, 61200, 200, 800, 2400, 6400, 12800, 21760, 32640, 48960};
int hotkeyAnyTrackInAnyMode, hotkeyUnlockAllTracks;
DWORD Strings;

DWORD PaintCategoryCodeCaveExit = 0x55D270;
DWORD PaintCategoryCodeCaveExit2 = 0x55D0F6;
DWORD PaintCategoryCodeCaveJump1 = 0x55D112;
DWORD PaintCategoryCodeCaveJump2 = 0x55D238;
DWORD VinylCategoryCodeCaveCall = 0x545920;
DWORD VinylCategoryCodeCaveCall2 = 0x505450;
DWORD VinylCategoryCodeCaveExit = 0x546265;
DWORD DriftMultiplierCodeCaveExit = 0x56DB59;
DWORD BarrierCodeCaveExit = 0x578077;

void __declspec(naked) PaintCategoryCodeCave()
{
	_asm
	{
		ColorTypeIncrementCodeCave: // Add Powder Coat and High Heat to the Paint Category Increment (Right Arrow)
			je powder
			cmp eax, 0x0016BDCE
			je highht
			cmp eax, 0x066350F0
			jne jump1
			jmp PaintCategoryCodeCaveExit

		powder : // Change current paint category to Powder Coat
			mov dword ptr [esi + 0x174], 0x0016BDCE
			jmp PaintCategoryCodeCaveJump1

		highht : // Change current paint category to High Heat
			mov dword ptr [esi + 0x174], 0x066350F0
			jmp PaintCategoryCodeCaveJump1

		jump1:
			jmp PaintCategoryCodeCaveJump1
	}
}

void __declspec(naked) PaintCategoryCodeCave2()
{
	_asm
	{
		ColorTypeDecrementCodeCave : // Add Powder Coat and High Heat to the Paint Category Decrement (Left Arrow)
			je powder
			cmp eax, 0x066350F0
			je highht
			cmp eax, 0x0016BDCE
			je jump2
			jmp PaintCategoryCodeCaveExit2

		powder : // Change current paint category to Powder Coat
			mov dword ptr[esi + 0x174], 0x066350F0
			jmp PaintCategoryCodeCaveJump1

		highht : // Change current paint category to High Heat
			mov dword ptr[esi + 0x174], 0x0016BDCE
			jmp PaintCategoryCodeCaveJump1

		jump2:
			jmp PaintCategoryCodeCaveJump2
	}
}

void __declspec(naked) VinylCategoryCodeCave()
{
	_asm
	{
			push 0xE79A53F8 // Debug String Hash
			push 0x93EC1CE9 // NFSU2 Icon Hash
			push 0x1C // Hidden vinyl category
			mov ecx, esi
			call VinylCategoryCodeCaveCall
			mov eax, [esi + 0x04]
			push eax
			call VinylCategoryCodeCaveCall2
			jmp VinylCategoryCodeCaveExit
	}
}

void __declspec(naked) DriftMultiplierCodeCave()
{
	_asm
	{
			fmul dword ptr ds:[0x925100]
			fstp dword ptr[esp + 0x40]
			mov edx, [esp + 0x70]
			jmp DriftMultiplierCodeCaveExit
	}

}

void __declspec(naked) BarrierCodeCave()
{
	_asm
	{
			movsx eax, word ptr [eax + 0x8A]
			cmp eax, 4600
			jge fixbarriers
			cmp eax, 4300
			jge drifttrack
			jmp removebarriers

		drifttrack:
			cmp eax, 4399
			jle fixbarriers
			jmp removebarriers

		fixbarriers:
			mov byte ptr ds : [0x7a078b], 73
			mov byte ptr ds : [0x7a0798], 73
			jmp BarrierCodeCaveExit

		removebarriers:
			mov byte ptr ds : [0x7a078b], 77
			mov byte ptr ds : [0x7a0798], 77
			jmp BarrierCodeCaveExit
	}

}

void Init()
{
	// Read values from .ini
	CIniReader iniReader("NFSU2ExtraOptionsSettings.ini");

	// Hotkeys
	hotkeyUnlockAllTracks = iniReader.ReadInteger("Hotkeys", "UnlockAllTracks", 116); // F5
	hotkeyAnyTrackInAnyMode = iniReader.ReadInteger("Hotkeys", "AnyTrackInAnyMode", 36); // HOME
	
	// LapControllers
	MinimumLap = iniReader.ReadInteger("LapControllers", "Minimum", 0);
	MaximumLap = iniReader.ReadInteger("LapControllers", "Maximum", 127);
	KOLap = iniReader.ReadInteger("LapControllers", "KOEnabled", 5);
	UnfreezeKO = iniReader.ReadInteger("LapControllers", "UnfreezeKO", 0) == 1;

	// OpponentControllers
	MinimumCPU = iniReader.ReadInteger("OpponentControllers", "Minimum", 0);
	MaximumCPU = iniReader.ReadInteger("OpponentControllers", "Maximum", 5);
	KOCPU = iniReader.ReadInteger("OpponentControllers", "KOEnabled", 5);

	// LAN
	MinimumLapLANC = iniReader.ReadInteger("LAN", "MinimumLapsCircuit", 0);
	MinimumLapLAND = iniReader.ReadInteger("LAN", "MinimumLapsDrift", 0);
	MinimumLapLANS = iniReader.ReadInteger("LAN", "MinimumLapsStreetX", 0);
	MaximumLapLAN = iniReader.ReadInteger("LAN", "MaximumLaps", 127);
	MaximumPlayersLAN = iniReader.ReadInteger("LAN", "MaximumPlayers", 6);

	// Drift
	MaximumDriftX = iniReader.ReadInteger("Drift", "MaximumMultiplier", 9);
	DriftPlus = iniReader.ReadInteger("Drift", "PlusSign", 0) == 1;
	DriftMultiply = iniReader.ReadInteger("Drift", "ShowWithoutMultiplying", 0) == 1;

	// Menu
	ShowOnline = iniReader.ReadInteger("Menu", "ShowOnline", 1) == 1;
	ShowOutrun = iniReader.ReadInteger("Menu", "ShowOutrun", 1) == 1;
	ShowSubtitles = iniReader.ReadInteger("Menu", "ShowSubtitles", 1) == 1;
	EnableTrackSelectForFreeRun = iniReader.ReadInteger("Menu", "FreeRunTrackSelect", 1) == 1;
	EnableTrackSelectForOutrun = iniReader.ReadInteger("Menu", "OutrunTrackSelect", 1) == 1;
	AnyTrackInAnyMode = iniReader.ReadInteger("Menu", "AnyTrackInAnyRaceMode", 1) == 1;
	MorePaint = iniReader.ReadInteger("Menu", "MorePaintTypes", 1) == 1;
	MoreVinyls = iniReader.ReadInteger("Menu", "ShowDebugVinylCategory", 1) == 1;
	SplashScreenTimeLimit = iniReader.ReadFloat("Menu", "SplashScreenTimeLimit", 30.0f);
	nlgzrgnTakeOver = iniReader.ReadInteger("Menu", "DisableTakeover", 0) == 0;

	// Gameplay
	EnableCameras = iniReader.ReadInteger("Gameplay", "EnableHiddenCameraModes", 1) == 1;
	UnlockRegionals = iniReader.ReadInteger("Gameplay", "Unlock106AndCorsa", 1) == 1;
	UnlockAll = iniReader.ReadInteger("Gameplay", "UnlockAllCars", 0) == 1;
	UnlockTracks = iniReader.ReadInteger("Gameplay", "UnlockAllTracks", 1) == 1;
	RemoveRaceBarriers = iniReader.ReadInteger("Gameplay", "RemoveRaceBarriers", 0) == 1;
	RemoveLockedAreaBarriers = iniReader.ReadInteger("Gameplay", "RemoveLockedAreaBarriers", 1) == 1;
	NeonBrightness = iniReader.ReadFloat("Gameplay", "NeonBrightness", 1.0f);
	CarbonStyleRaceStatus = iniReader.ReadInteger("Gameplay", "ShowPercentOn1LapRaces", 0) == 1;

	// Restrictions
	if (MinimumLap < 0 || MinimumLap > 127) MinimumLap = 1;
	if (MaximumLap < 0 || MaximumLap > 127) MaximumLap = 10;
	if (KOLap < 0 || KOLap > 127) KOLap = 3;

	if (MinimumCPU < 0 || MinimumCPU > 5) MinimumCPU = 0;
	if (MaximumCPU < 0 || MaximumCPU > 5) MaximumCPU = 3;
	if (KOCPU < 0 || KOCPU > 5) KOCPU = 3;

	if (MinimumLapLANC < 0 || MinimumLapLANC > 127) MinimumLapLANC = 1;
	if (MinimumLapLAND < 0 || MinimumLapLAND > 127) MinimumLapLAND = 1;
	if (MinimumLapLANS < 0 || MinimumLapLANS > 127) MinimumLapLANS = 1;
	if (MaximumLapLAN < 0 || MaximumLapLAN > 127) MaximumLapLAN = 10;
	if (MaximumPlayersLAN < 2 || MaximumPlayersLAN > 6) MaximumPlayersLAN = 6;

	if (MaximumDriftX < 1 || MaximumDriftX > 9) MaximumDriftX = 5;


	// Main Code - Apply all the settings
	injector::WriteMemory<unsigned char>(0x4B3D82, MinimumLap, true);		// Minimum Lap Controller For Decrement
	injector::WriteMemory<unsigned char>(0x4B3D9B, MinimumLap, true);		// Minimum Lap Controller For Increment
	injector::WriteMemory<unsigned char>(0x4B3D86, MaximumLap, true);		// Maximum Lap Controller For Decrement
	injector::WriteMemory<unsigned char>(0x4B3D97, MaximumLap, true);		// Maximum Lap Controller For Increment
	injector::WriteMemory<unsigned char>(0x4B407F, KOLap, true);			// Amount of Laps when KO Enabled

	injector::MakeNOP(0x4b3867, 4, true);									// Enable minimum opponent controller
	injector::WriteMemory<unsigned char>(0x4b3863, MinimumCPU, true);		// Minimum Opponent Controller
	injector::MakeNOP(0x4b382b, 6, true);									// Fix Maximum Opponent Controller (No +2 for URL)
	injector::WriteMemory<unsigned char>(0x4b3834, MaximumCPU, true);		// Maximum Opponent Controller
	injector::WriteMemory<unsigned char>(0x4B4075, KOCPU, true);			// Amount of Opponents when KO Enabled

	injector::WriteMemory<unsigned char>(0x4B3E7A, MinimumLapLANC, true);	// Minimum Lap Controller For LAN Circuit & URL
	injector::WriteMemory<unsigned char>(0x4B3EE4, MinimumLapLAND, true);	// Minimum Lap Controller For LAN Drift
	injector::WriteMemory<unsigned char>(0x4B3E9E, MinimumLapLANS, true);	// Minimum Lap Controller For LAN Street X
	injector::WriteMemory<unsigned char>(0x4B3F30, MaximumLapLAN, true);	// Maximum Lap Controller For Decrement (Lan)
	injector::WriteMemory<unsigned char>(0x4B3F41, MaximumLapLAN, true);	// Maximum Lap Controller For Increment (Lan)
	injector::WriteMemory<unsigned char>(0x4B31AA, 0xB0, true);				// Maximum Players Fix - lea to mov al,X
	injector::WriteMemory<unsigned char>(0x4B31AB, MaximumPlayersLAN, true);// Maximum Players Controller (LAN)
	injector::MakeNOP(0x4B31AC, 2, true);									// Maximum Players Fix - nop remaining bytes from lea

	// Fix "insert disc 2" bug for PCs with No Optical Drive
	injector::WriteMemory<unsigned char>(0x5C0D3F, 0x78, true);
	injector::WriteMemory<unsigned char>(0x5C0D54, 0x00, true);

	// Show drift as AxB hack
	if (DriftMultiply) 
	{
		injector::WriteMemory<unsigned char>(0x4AB792, 0xb0, true);
		injector::WriteMemory<unsigned char>(0x4AB793, 0x01, true);
		injector::WriteMemory<unsigned char>(0x4AB794, 0x90, true);
	}

	// Add a + before drift point
	if (DriftPlus) 
	{
		injector::WriteMemory<unsigned char>(0x4AB7DB, 0x74, true);
	}

	injector::WriteMemory<unsigned char>(0x56CC98, 0xCF, true); // Change Threshold array sizes from 4(x5) to 8(x9).
	injector::WriteMemory<unsigned char>(0x56CC9C, 0x00, true); // Change the address of Drift multiplier threshold points arrays
	injector::WriteMemory<unsigned char>(0x56CC9D, 0x50, true); // Change the address of Drift multiplier threshold points arrays
	injector::WriteMemory<unsigned char>(0x56CC9E, 0x92, true); // Change the address of Drift multiplier threshold points arrays
	for (int i = 0; i < 36; i++) injector::WriteMemory(0x925004 + 4 * i, DriftMutliplierThresholdPoints[i], true);
	injector::WriteMemory<unsigned char>(0x56CC58, MaximumDriftX, true); // Maximum Drift Level Controller (Main)
	injector::WriteMemory<unsigned char>(0x56CC90, MaximumDriftX, true); // Maximum Drift Level Controller (To Show threshold points)

	// Buff/Nerf Static Scores for Sprint Drift
	injector::WriteMemory<float>(0x925100, ((float)MaximumDriftX / 5.0f), true);
	injector::MakeNOP(0x56DB51, DriftMultiplierCodeCaveExit - 0x56DB51, true);
	injector::MakeJMP(0x56DB51, DriftMultiplierCodeCave, true);

	// Remove Region Car Lock
	if (UnlockRegionals) 
	{
		/* Old Method
		injector::MakeNOP(0x4e237e, 2, true); // Customize
		injector::MakeNOP(0x4DFA8D, 6, true); // Car Lot*/

		// Unlock 106 and Corsa for Car List
		injector::WriteMemory<unsigned char>(0x7F7C48, 0xFF, true); // CORSA
		injector::WriteMemory<unsigned char>(0x7F7C4C, 0xFF, true); // PEUGOT106

		// Unlock them as AI opponents
		injector::WriteMemory<unsigned char>(0x4FEB9D, 0x1C, true); // Extend array by 2
		injector::WriteMemory<unsigned char>(0x7F6DBE, 0x07, true); // CORSA
		injector::WriteMemory<unsigned char>(0x7F6DBF, 0x06, true); // PEUGOT106
	}

	// Unlock All Cars
	if (UnlockAll) 
	{
		injector::MakeNOP(0x4e23a2, 2, true); // Customize
		injector::MakeNOP(0x4DFAB4, 2, true); // Car Lot
	}

	// Unlock All Tracks
	if (UnlockTracks) 
	{
		injector::MakeNOP(0x5156fa, 2, true);
	}

	// Enable Track Selection Screen for Free Run (9) Game Mode
	if (EnableTrackSelectForFreeRun) 
	{
		injector::MakeNOP(0x4B2AE3, 2, true);
	}

	// Remove Neon Route Indicator Barriers from Races
	if (RemoveRaceBarriers) 
	{
		injector::WriteMemory<unsigned char>(0x7A078B, 77, true);
		injector::WriteMemory<unsigned char>(0x7A0798, 77, true);

		injector::MakeJMP(0x578070, BarrierCodeCave, true);
	}

	// Remove Neon Locked Area Indicator Barriers from Career Mode
	if (RemoveLockedAreaBarriers) 
	{
		injector::WriteMemory<unsigned char>(0x7A073C, 77, true);
	}

	// Splash screen time limit
	injector::WriteMemory<float>(0x784478, SplashScreenTimeLimit, true);

	// Enable Drift Camera For All
	if (EnableCameras)
	{
		injector::MakeNOP(0x50256A, 2, true);
		injector::MakeNOP(0x502572, 2, true);
	}

	// Enable Outrun Track Select
	if (EnableTrackSelectForOutrun)
	{
		injector::MakeNOP(0x4B2AA0, 2, true);
	}

	// Show Outrun at Quick Race Menu
	if (ShowOutrun)
	{
		injector::MakeNOP(0x4B2F3E, 2, true);
	}

	// Remove Online Option from Main Menu
	if (!ShowOnline)
	{
		injector::WriteMemory<unsigned char>(0x4AEEDF, 0xEB, true);
	}

	// Show Subtitles
	if (ShowSubtitles)
	{
		injector::MakeNOP(0x4A8BA0, 2, true);
		injector::MakeNOP(0x553A65, 2, true);
		injector::MakeNOP(0x55B061, 2, true);
	}

	// Add Powder Coat and High Heat categories to Body Paint
	if (MorePaint)
	{
		injector::MakeNOP(0x55D26A, PaintCategoryCodeCaveExit - 0x55D26A, true);
		injector::MakeJMP(0x55D26A, PaintCategoryCodeCave, true);
		injector::MakeNOP(0x55D0F0, PaintCategoryCodeCaveExit2 - 0x55D0F0, true);
		injector::MakeJMP(0x55D0F0, PaintCategoryCodeCave2, true);
		
	}

	// Add Debug Vinyls to menu
	if (MoreVinyls)
	{
		injector::MakeNOP(0x54625C, VinylCategoryCodeCaveExit - 0x54625C, true);
		injector::MakeJMP(0x54625C, VinylCategoryCodeCave, true);
	}

	// Unfreeze lap and opponent controllers for KO
	if (UnfreezeKO)
	{
		injector::WriteMemory<unsigned char>(0x4b4068, 0xEB, true); // Don't copy static numbers
		injector::WriteMemory<unsigned char>(0x4B3E14, 0xEB, true); // Don't freeze laps
		injector::WriteMemory<unsigned char>(0x4B3903, 0xEB, true); // Don't freeze opponents
	}

	// Carbon-Style Race Status
	if (CarbonStyleRaceStatus)
	{
		injector::WriteMemory<unsigned char>(0x4AA27F, 0xBC, true); // Read lap count instead of game mode

		injector::WriteMemory<unsigned char>(0x4AA283, 0x3C, true); // If lap count
		injector::WriteMemory<unsigned char>(0x4AA284, 0x01, true); // is not 01
		injector::WriteMemory<unsigned char>(0x4AA286, 0x85, true); // Jump to lap x/x
	}

	// Neon Brightness
	injector::WriteMemory<float>(0x60d8d0, NeonBrightness, true);

	// Other things
	CreateThread(0, 0, (LPTHREAD_START_ROUTINE)&Thing, NULL, 0, NULL);
}

DWORD WINAPI Thing(LPVOID)
{
	while (true)
	{
		Sleep(1);
		//CIniReader TrackiniReader("NFSU2ExtraOptionsTracks.ini");
		
		Strings = *(DWORD*)0x8383D8; // String Table Pointer

		if ((GetAsyncKeyState(hotkeyAnyTrackInAnyMode) & 1)) // When pressed "Any Track in Any Mode" key
		{
			CIniReader iniReader("NFSU2ExtraOptionsSettings.ini");
			AnyTrackInAnyMode = !AnyTrackInAnyMode;
			iniReader.WriteInteger("Menu", "AnyTrackInAnyRaceMode", AnyTrackInAnyMode);

			if (AnyTrackInAnyMode)
			{
				injector::MakeNOP(0x4cdefc, 2, true);
			}

			else
			{
				injector::WriteMemory<WORD>(0x4cdefc, 0x0874 ,true);
			}

			while ((GetAsyncKeyState(hotkeyAnyTrackInAnyMode) & 0x8000) > 0) { Sleep(0); }
		}
		
		if (Strings && nlgzrgnTakeOver && !once2) // Indicate if ExOpts is Loaded at splash screen (If nlgzrgnTakeOver enabled)
		{
			DWORD CopyrightAddr = (Strings + 0xb9c);
			char* Copyright = *(char**)CopyrightAddr;
			char* Append = "^NFSU2 Extra Options - © 2016 nlgzrgn. No rights reserved.";
			char* Tookover = strcat(Copyright, Append);
			injector::WriteMemory<DWORD>(CopyrightAddr, (DWORD)Tookover, true);
			once2 = 1;
		}

		if ((GetAsyncKeyState(hotkeyUnlockAllTracks) & 1)) // When pressed "Any Track in Any Mode" key
		{
			CIniReader iniReader("NFSU2ExtraOptionsSettings.ini");
			UnlockTracks = !UnlockTracks;
			iniReader.WriteInteger("Gameplay", "UnlockAllTracks", UnlockTracks);

			if (UnlockTracks)
			{
				injector::MakeNOP(0x5156fa, 2, true);
			}

			else
			{
				injector::WriteMemory<WORD>(0x5156fa, 0x0474, true);
			}

			while ((GetAsyncKeyState(hotkeyUnlockAllTracks) & 0x8000) > 0) { Sleep(0); }
		}
	}
	return 0;
}

BOOL APIENTRY DllMain(HMODULE /*hModule*/, DWORD reason, LPVOID /*lpReserved*/)
{
	if (reason == DLL_PROCESS_ATTACH)
	{
		uintptr_t base = (uintptr_t)GetModuleHandleA(NULL);
		IMAGE_DOS_HEADER* dos = (IMAGE_DOS_HEADER*)(base);
		IMAGE_NT_HEADERS* nt = (IMAGE_NT_HEADERS*)(base + dos->e_lfanew);

		if ((base + nt->OptionalHeader.AddressOfEntryPoint + (0x400000 - base)) == 0x75BCC7) // Check if .exe file is compatible - Thanks to thelink2012 and MWisBest
			Init();

		else
		{
			MessageBoxA(NULL, "This .exe is not supported.\nPlease use v1.2 NTSC speed2.exe (4,57 MB (4.800.512 bytes)).", "NFSU2 Extra Options", MB_ICONERROR);
			return FALSE;
		}
	}
	return TRUE;
	
}

