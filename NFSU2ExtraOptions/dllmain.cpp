#include "stdafx.h"
#include "stdio.h"
#include <windows.h>
#include "..\includes\injector\injector.hpp"
#include <cstdint>
#include "..\includes\IniReader.h"
#include <d3d9.h>

DWORD WINAPI Thing(LPVOID);

unsigned char MinimumLap, MaximumLap, KOLap, MinimumCPU, MaximumCPU, KOCPU, MinimumLapLANC, MinimumLapLAND, MinimumLapLANS, MaximumLapLAN, MaximumPlayersLAN, MaximumDriftX, HeadlightsMode, WindowedMode, WheelFix, ExperimentalSplitScreenFix, EnableDebugWorldCamera, GameRegion;
bool DriftPlus, DriftMultiply, UnlockRegionals, UnlockAllThings, EnableTrackSelectForFreeRun, AnyTrackInAnyMode, RemoveRaceBarriers, RemoveLockedAreaBarriers, GarageCameraHacks, ShowMoreCustomizationOptions, MoreVinyls, ExOptsTeamTakeOver, EnableCameras, ShowOnline, ShowOutrun, EnableTrackSelectForOutrun, once1, once2, ShowSubtitles, UnfreezeKO, CarbonStyleRaceStatus, AlwaysRain, EnableLANSwitcher, LANSwitcherMode, ShowMoreRaceOptions, ShowDebugCarCustomize, EnableSaveLoadHotPos, IsOnFocus, SkipMovies, EnableSound, EnableMusic, AutoDrive, HoodDecalsFix, CabinNeonFix, AllowLongerProfileNames, ShowDebugEventID, AllowMultipleInstances;
float SplashScreenTimeLimit, NeonBrightness, WorldAnimationSpeed, GameSpeed, HeadlightsAmount, GeneralRainAmount, RainXing, RainFallSpeed, RainGravity, LowBeamAmount, HighBeamAmount, RoadReflection, RainIntensity, FallingRainSize;
int DriftMutliplierThresholdPoints[] = { 350, 1400, 4200, 11200, 22400, 38080, 57120, 85680, 300, 1200, 3600, 9600, 19200, 32640, 48960, 73440, 250, 1000, 3000, 8000, 16000, 27200, 40800, 61200, 200, 800, 2400, 6400, 12800, 21760, 32640, 48960};
int hotkeyAnyTrackInAnyMode, hotkeyUnlockAllThings, hotkeyFreezeCamera, hotkeyToggleHeadlights, hotkeyAutoDrive, StartingCash, ThreadDelay, NosTrailRepeatCount, DebugEventID;
DWORD GameState;
HWND windowHandle;

char* StringBuffer1 = "© 2004 Electronic Arts Inc. All rights reserved.^NFSU2 Extra Options - © 2020 ExOpts Team. No rights reserved.";
DWORD _181419E5_New = (DWORD)StringBuffer1;

char* aMagazine = "Magazine";
char* aDVD = "DVD";

DWORD PaintCategoryCodeCaveExit = 0x55D270;
DWORD PaintCategoryCodeCaveExit2 = 0x55D0F6;
DWORD PaintCategoryCodeCaveJump1 = 0x55D112;
DWORD PaintCategoryCodeCaveJump2 = 0x55D238;
DWORD VinylCategoryCodeCaveExit = 0x546265;
DWORD DriftMultiplierCodeCaveExit = 0x56DB59;
DWORD BarrierCodeCaveExit = 0x578077;
DWORD StringReplacementCodeCaveExit = 0x4FFA1F;
DWORD StartingCashCodeCaveExit = 0x532913;
DWORD DebugCarCustomizeCodeCaveExit = 0x520F51;
DWORD HoodDecalsCodeCaveExit = 0x546B81;
DWORD CabinNeonCodeCaveExit = 0x54804F;

char* (__cdecl* _strstr)(char const*, char const*) = (char* (__cdecl*)(char const*, char const*))0x75F140;
void(__cdecl *j__malloc)(size_t a1) = (void(__cdecl*)(size_t))0x575620;
int(__thiscall *AddElementToMenuWithStateID)(int _this, int a2, int a3, int a4, int a5) = (int(__thiscall*)(int, int, int, int, int))0x520CB0;
void *(__thiscall *AddCustomElementToMenu)(void *_this, int a2, int a3, int a4) = (void*(__thiscall*)(void*, int, int, int))0x545920;
int(__cdecl *FEHashUpper)(unsigned __int8 *a1) = (int(__cdecl*)(unsigned __int8*))0x505450;
int(__thiscall *ChooseRimBrand_AddRimCategory)(DWORD *_this, int RimBrandName, int RimBrandIcon, int RimBrandHash) = (int(__thiscall*)(DWORD *, int, int, int))0x5463B0;
int(__thiscall *Player_AutoPilotOn)(DWORD *_Player) = (int(__thiscall*)(DWORD*))0x5FAE20;
int(__thiscall *Player_AutoPilotOff)(DWORD *_Player) = (int(__thiscall*)(DWORD*))0x5FAF10;
int(__thiscall* ChooseDecalCategory_AddCategoryOptionLock)(void* _this, int LayoutID, bool isDecalSelection, int TextureHash, int StringHash) = (int(__thiscall*)(void*, int, bool, int, int))0x52FF60;
int(__thiscall* CustomizeNeonMenu_AddSelection)(void* _this, int CAR_SLOT_ID, int TextureHash, int StringHash, int CarAnimLocation) = (int(__thiscall*)(void*, int, int, int, int))0x53BC90;
int(__cdecl* SelectableTrack_CalcLanguageHash)(int EventID, int IsReverse) = (int(__cdecl*)(int, int))0x516280;
int(__cdecl* FEngSetVisible)(DWORD* FEObject) = (int(__cdecl*)(DWORD*))0x50CA50;
int(*FEPrintf)(char const*, int, char const*, ...) = (int(*)(char const*, int, char const*, ...))0x537B80;
DWORD(__cdecl* FEngFindObject)(char const* pkg_name, DWORD obj_hash) = (DWORD(__cdecl*)(char const*, DWORD))0x5379C0;

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
			call AddCustomElementToMenu
			mov eax, [esi + 0x04]
			push eax
			call FEHashUpper
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

void __declspec(naked) StringReplacementCodeCave()
{
	_asm
	{
		mov ecx, dword ptr ds : [ebx + eax * 0x08]

		cmp ecx, 0x181419E5
		je ReplaceCopyrightString
		// cmp ecx, AnotherStringHashHere
		// je ReplaceAnotherString
		jmp continuee

		ReplaceCopyrightString :
			cmp ExOptsTeamTakeOver, 0x01
			jne continuee
			cmp once1, 0x01
			je continuee
			
			push ecx
			mov ecx, _181419E5_New
			mov dword ptr ds : [ebx + eax * 0x08 + 0x04], ecx
			mov once1, 0x01
			pop ecx
			//jmp continuee

		continuee :
			cmp ecx, edx
			jmp StringReplacementCodeCaveExit

	}
}

void __declspec(naked) StartingCashCodeCave()
{
	_asm
	{
		push eax
		mov eax, StartingCash
		mov dword ptr ds: [esi + 0x7134], eax
		pop eax
		jmp StartingCashCodeCaveExit
	}
}

void __declspec(naked) DebugCarCustomizeCodeCave()
{
	_asm
	{
		mov edx, [edi]
		push eax
		mov ecx, edi
		call dword ptr ds: [edx + 0x18]
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

		jmp DebugCarCustomizeCodeCaveExit
	}
}

void __declspec(naked) NewRimsCodeCave()
{
	_asm
	{
		call ChooseRimBrand_AddRimCategory

		push 0x055AD46B // SPONSOR_YOKOHAMA (There is no ADVAN string in NFSU2)
		push 0x0F3990B6 // VISUAL_RIMS_BRAND_STOCK (No ADVAN icon)
		push 0x0269D069 // ADVAN
		mov ecx, ebx
		call ChooseRimBrand_AddRimCategory

		push 0x30B938BE // RIMS_BRAND_OASIS
		push 0x0EE6D551 // VISUAL_RIMS_BRAND_OASIS
		push 0x0365769E // OASIS
		mov ecx, ebx
		call ChooseRimBrand_AddRimCategory

		push 0x546764
		ret
	}
}

bool __stdcall CheckRaceModeHook(int TrackInfoBlock, int NoDragAndDriftRaces)
{
	bool result;
	__int16 TrackID;
	bool ZeroFlag;

	if (!TrackInfoBlock) return 0; // If block failed to load

	TrackID = *(WORD*)(TrackInfoBlock + 138);
	
	if (TrackID == 1001 || TrackID == 1002 || TrackID == 1003 || TrackID == 1099 || TrackID == 1102 || TrackID == 3001
		|| TrackID == 4200 || TrackID == 4300 || TrackID == 4400 || TrackID == 4600 || TrackID == 4700 || TrackID == 4800 || TrackID == 4900) return 0; // If one of crashy tracks

	return 1; // For all other races
}

bool __cdecl RegionLockHook(int CarID)
{
	return 1;
}

void __declspec(naked) HoodDecalsCodeCave()
{
	_asm
	{
		push 0x8E52365C // string
		push 0x8E52365C // icon
		push 0x00 // 0 = select layout, 1 = select decal
		push 0x00010005 // layout id
		mov ecx, esi
		call ChooseDecalCategory_AddCategoryOptionLock

		push 0xDA88B711
		jmp HoodDecalsCodeCaveExit
	}
}

bool DoesFileExist(char const* _path) {

	std::ifstream ifile(_path);
	return (bool)ifile;
}

void __declspec(naked) CabinNeonCodeCave()
{
	_asm
	{
		push 0xFF
		push 0x20E7F018 // "Cabin Neon"
		push 0x745EE753 // Cabin Neon icon
		push 0x9C // Cabin Neon
		mov ecx, esi
		call CustomizeNeonMenu_AddSelection

		push 0xFF
		push 0x20E7F018 // "Cabin Neon"
		push 0xE82189F4 // Cabin Neon Configure icon
		push 0x9E // Cabin Neon Style
		mov ecx, esi
		call CustomizeNeonMenu_AddSelection

		push 0xFF
		push 0x2225348F
		jmp CabinNeonCodeCaveExit
	}
}

void __declspec(naked) ProfileNameFilterCodeCave()
{
	_asm
	{
		push aDVD
		push ebx
		call _strstr // If it's a DVD cover
		add esp,8
		test al,al
		jnz SkipThisProfile

		push aMagazine
		push ebx
		call _strstr // If it's a Magazine cover
		add esp, 8
		test al, al
		jnz SkipThisProfile

		originalcode:
			mov eax,[esi+0x48]
			mov ecx,[esi+0x4C]
			push 0x4E9122
			retn

		SkipThisProfile:
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
		mov ebx,eax
		push 0xEB406FEC // Profile Name
		push 0x790000 // UI_PC_Help_Bar.fng
		call FEngFindObject
		mov [eax+0x68], 0x10 // String length
		add esp,8
		mov eax, ebx
		pop ebx
		push 0x83A9E0 // Profile Name
		push 0x54E74B
		retn
	}
}

void Init()
{
	// Read values from .ini
	CIniReader iniReader("NFSU2ExtraOptionsSettings.ini");

	// Hotkeys
	hotkeyAnyTrackInAnyMode = iniReader.ReadInteger("Hotkeys", "AnyTrackInAnyMode", 36); // HOME
	hotkeyToggleHeadlights = iniReader.ReadInteger("Hotkeys", "Headlights", 72); // H
	hotkeyFreezeCamera = iniReader.ReadInteger("Hotkeys", "FreezeCamera", 19); // Pause/Break
	hotkeyUnlockAllThings = iniReader.ReadInteger("Hotkeys", "UnlockAllThings", 116); // F5
	hotkeyAutoDrive = iniReader.ReadInteger("Hotkeys", "AutoDrive", 117); //F6
	EnableSaveLoadHotPos = iniReader.ReadInteger("Hotkeys", "EnableSaveLoadHotPos", 0) == 1;

	// LapControllers
	MinimumLap = iniReader.ReadInteger("LapControllers", "Minimum", 0);
	MaximumLap = iniReader.ReadInteger("LapControllers", "Maximum", 127);
	KOLap = iniReader.ReadInteger("LapControllers", "KOEnabled", 5);

	// OpponentControllers
	MinimumCPU = iniReader.ReadInteger("OpponentControllers", "Minimum", 0);
	MaximumCPU = iniReader.ReadInteger("OpponentControllers", "Maximum", 5);
	KOCPU = iniReader.ReadInteger("OpponentControllers", "KOEnabled", 5);
	MaximumPlayersLAN = iniReader.ReadInteger("OpponentControllers", "MaximumLANPlayers", 6);

	// Drift
	MaximumDriftX = iniReader.ReadInteger("Drift", "MaximumMultiplier", 9);
	DriftPlus = iniReader.ReadInteger("Drift", "PlusSign", 0) == 1;
	DriftMultiply = iniReader.ReadInteger("Drift", "ShowWithoutMultiplying", 0) == 1;

	// Menu
	ShowOutrun = iniReader.ReadInteger("Menu", "ShowOutrun", 1) == 1;
	ShowMoreRaceOptions = iniReader.ReadInteger("Menu", "ShowMoreRaceOptions", 1) == 1;
	ShowOnline = iniReader.ReadInteger("Menu", "ShowOnline", 1) == 1;
	ShowSubtitles = iniReader.ReadInteger("Menu", "ShowSubs", 1) == 1;
	ShowMoreCustomizationOptions = iniReader.ReadInteger("Menu", "ShowMoreCustomizationOptions", 1) == 1;
	MoreVinyls = iniReader.ReadInteger("Menu", "ShowSpecialVinyls", 1) == 1;
	ShowDebugCarCustomize = iniReader.ReadInteger("Menu", "ShowDebugCarCustomize", 0) == 1;
	ShowDebugEventID = iniReader.ReadInteger("Menu", "ShowDebugEventID", 0) == 1;
	AnyTrackInAnyMode = iniReader.ReadInteger("Menu", "AnyTrackInAnyRaceMode", 1) == 1;
	EnableTrackSelectForFreeRun = iniReader.ReadInteger("Menu", "FreeRunTrackSelect", 1) == 1;
	EnableTrackSelectForOutrun = iniReader.ReadInteger("Menu", "OutrunTrackSelect", 1) == 1;
	SplashScreenTimeLimit = iniReader.ReadFloat("Menu", "SplashScreenTimeLimit", 30.0f);
	GarageCameraHacks = iniReader.ReadInteger("Menu", "ShowcaseCamInfiniteYRotation", 0) == 1;
	AllowLongerProfileNames = iniReader.ReadInteger("Menu", "AllowLongerProfileNames", 0) == 1;
	ExOptsTeamTakeOver = iniReader.ReadInteger("Menu", "DisableTakeover", 0) == 0;

	// Gameplay
	EnableCameras = iniReader.ReadInteger("Gameplay", "EnableHiddenCameraModes", 1) == 1;
	EnableDebugWorldCamera = iniReader.ReadInteger("Gameplay", "EnableDebugCamera", 0) == 1;
	GameSpeed = iniReader.ReadFloat("Gameplay", "GameSpeed", 1.0f);
	WorldAnimationSpeed = iniReader.ReadFloat("Gameplay", "WorldAnimationSpeed", 45.0f);
	HeadlightsMode = iniReader.ReadInteger("Gameplay", "HeadlightsMode", 2);
	LowBeamAmount = iniReader.ReadFloat("Gameplay", "LowBeamBrightness", 0.75f);
	HighBeamAmount = iniReader.ReadFloat("Gameplay", "HighBeamBrightness", 1.00f);
	RemoveRaceBarriers = iniReader.ReadInteger("Gameplay", "RemoveRaceBarriers", 0) == 1;
	RemoveLockedAreaBarriers = iniReader.ReadInteger("Gameplay", "RemoveLockedAreaBarriers", 1) == 1;
	CarbonStyleRaceStatus = iniReader.ReadInteger("Gameplay", "ShowPercentOn1LapRaces", 0) == 1;
	GameRegion = iniReader.ReadInteger("Gameplay", "GameRegion", 0);
	StartingCash = iniReader.ReadInteger("Gameplay", "StartingCash", 0);
	UnlockRegionals = iniReader.ReadInteger("Gameplay", "UnlockRegionalCars", 1) == 1;
	UnlockAllThings = iniReader.ReadInteger("Gameplay", "UnlockAllThings", 1) == 1;
	NeonBrightness = iniReader.ReadFloat("Gameplay", "NeonBrightness", 1.0f);
	NosTrailRepeatCount = iniReader.ReadInteger("Gameplay", "NosTrailRepeatCount", 8);

	// Weather
	AlwaysRain = iniReader.ReadInteger("Weather", "AlwaysRain", 0) == 1;
	GeneralRainAmount = iniReader.ReadFloat("Weather", "GeneralRainAmount", 1.0f);
	RoadReflection = iniReader.ReadFloat("Weather", "RoadReflectionAmount", 1.0f);
	FallingRainSize = iniReader.ReadFloat("Weather", "RainSize", 0.03f);
	RainIntensity = iniReader.ReadFloat("Weather", "RainIntensity", 0.7f);
	RainXing = iniReader.ReadFloat("Weather", "RainCrossing", 0.02f);
	RainFallSpeed = iniReader.ReadFloat("Weather", "RainSpeed", 0.03f);
	RainGravity = iniReader.ReadFloat("Weather", "RainGravity", 0.45f);

	// Fixes
	WheelFix = iniReader.ReadInteger("Fixes", "DisappearingWheelsFix", 1) == 1;
	ExperimentalSplitScreenFix = iniReader.ReadInteger("Fixes", "ExperimentalSplitScreenFix", 0) == 1;
	HoodDecalsFix = iniReader.ReadInteger("Fixes", "HoodDecalsFix", 1) == 1;
	CabinNeonFix = iniReader.ReadInteger("Fixes", "CabinNeonFix", 1) == 1;

	// Misc
	WindowedMode = iniReader.ReadInteger("Misc", "WindowedMode", 0);
	SkipMovies = iniReader.ReadInteger("Misc", "SkipMovies", 0) == 1;
	EnableSound = iniReader.ReadInteger("Misc", "EnableSound", 1) == 1;
	EnableMusic = iniReader.ReadInteger("Misc", "EnableMusic", 1) == 1;
	AllowMultipleInstances = iniReader.ReadInteger("Misc", "AllowMultipleInstances", 0) == 1;
	ThreadDelay = iniReader.ReadInteger("Misc", "ThreadDelay", 5);

	// Restrictions
	MinimumLap %= 128;
	MaximumLap %= 128;
	KOLap %= 128;

	MinimumCPU %= 6;
	MaximumCPU %= 6;
	KOCPU %= 6;

	GameRegion %= 13;

	MaximumPlayersLAN %= 7;
	if (MaximumPlayersLAN < 2) MaximumPlayersLAN = 2;

	MaximumDriftX %= 10;
	if (MaximumDriftX == 0) MaximumDriftX = 1;

	// Allow Multiple Instances
	if (AllowMultipleInstances)
	{
		injector::WriteMemory<unsigned char>(0x580E11, 0xEB, true);
	}

	// Lap and opponent controllers
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

	injector::WriteMemory<unsigned char>(0x4B3E7A, MinimumLap, true);	// Minimum Lap Controller For LAN Circuit & URL
	injector::WriteMemory<unsigned char>(0x4B3EE4, MinimumLap, true);	// Minimum Lap Controller For LAN Drift
	injector::WriteMemory<unsigned char>(0x4B3E9E, MinimumLap, true);	// Minimum Lap Controller For LAN Street X
	injector::WriteMemory<unsigned char>(0x4B3F30, MaximumLap, true);	// Maximum Lap Controller For Decrement (Lan)
	injector::WriteMemory<unsigned char>(0x4B3F41, MaximumLap, true);	// Maximum Lap Controller For Increment (Lan)
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
	for (int i = 0; i < 32; i++) injector::WriteMemory(0x925004 + 4 * i, DriftMutliplierThresholdPoints[i], true);
	injector::WriteMemory<unsigned char>(0x56CC58, MaximumDriftX, true); // Maximum Drift Level Controller (Main)
	injector::WriteMemory<unsigned char>(0x56CC90, MaximumDriftX, true); // Maximum Drift Level Controller (To Show threshold points)

	// Buff/Nerf Static Scores for Sprint Drift
	injector::WriteMemory<float>(0x925100, ((float)MaximumDriftX / 5.0f), true);
	injector::MakeNOP(0x56DB51, DriftMultiplierCodeCaveExit - 0x56DB51, true);
	injector::MakeJMP(0x56DB51, DriftMultiplierCodeCave, true);

	// Remove Region Car Lock
	if (UnlockRegionals 
		&& DoesFileExist("..\\CARS\\CORSA\\TEXTURES.BIN")
		&& DoesFileExist("..\\CARS\\PEUGOT106\\TEXTURES.BIN")
		&& DoesFileExist("..\\CARS\\CORSA\\GEOMETRY.BIN")
		&& DoesFileExist("..\\CARS\\PEUGOT106\\GEOMETRY.BIN"))
	{
		/* Old Method
		injector::MakeNOP(0x4e237e, 2, true); // Customize
		injector::MakeNOP(0x4DFA8D, 6, true); // Car Lot*/

		// Unlock 106 and Corsa for Car List
		injector::WriteMemory<unsigned char>(0x7F7C48, 0xFF, true); // CORSA
		injector::WriteMemory<unsigned char>(0x7F7C4C, 0xFF, true); // PEUGOT106

		// Fix Civic and RSX for other regions
		injector::WriteMemory<unsigned char>(0x7F7C50, 0xFF, true); // CIVIC
		injector::WriteMemory<unsigned char>(0x7F7C54, 0xFF, true); // RSX

		// Hook region lock to return always true
		injector::MakeCALL(0x4DFA83, RegionLockHook, true);
		injector::MakeCALL(0x4E2374, RegionLockHook, true);

		// Unlock them as AI opponents
		injector::WriteMemory<unsigned char>(0x4FEB9D, 0x1C, true); // Extend array by 2
		injector::WriteMemory<unsigned char>(0x7F6DBE, 0x07, true); // CORSA
		injector::WriteMemory<unsigned char>(0x7F6DBF, 0x06, true); // PEUGOT106
	}

	// Set Game Region
	injector::WriteMemory<unsigned char>(0x864F24, GameRegion, true);

	// Unlock All Things - Load preference
	if (UnlockAllThings) 
	{
		injector::WriteMemory<unsigned char>(0x838464, 1, true);
		injector::MakeNOP(0x50F0D8, 2, true); // Fix individual performance parts
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

	// Starting Cash
	injector::MakeRangedNOP(0x53290D, StartingCashCodeCaveExit, true);
	injector::MakeJMP(0x53290D, StartingCashCodeCave, true);

	// Enable Drift Camera For All
	if (EnableCameras)
	{
		injector::MakeNOP(0x50256A, 2, true);
		injector::MakeNOP(0x502572, 2, true);
	}

	// Show More Race Options
	if (ShowMoreRaceOptions)
	{
		// Opponents in Sprint Drift Races
		injector::MakeNOP(0x4CD8D8, 2, true); // Menu
		injector::WriteMemory<unsigned char>(0x53F8B0, 0xEB, true); // Fix 0 overwrite
		injector::WriteMemory<unsigned char>(0x56DA0C, 0xA0, true); // eax 0 = Autoscores, 1-5 = ai opponents
		injector::MakeRangedNOP(0x56D9F1, 0x56DA0C, true); // 0 = Autoscores for all tracks
		injector::WriteMemory<DWORD>(0x56DA0D, 0x83AB01, true); // ai count
		injector::MakeRangedNOP(0x56DA11, 0x56DA16, true);

		// Unfreeze KO
		injector::WriteMemory<unsigned char>(0x4b4068, 0xEB, true); // Don't copy static numbers
		injector::WriteMemory<unsigned char>(0x4B3E14, 0xEB, true); // Don't freeze laps
		injector::WriteMemory<unsigned char>(0x4B3903, 0xEB, true); // Don't freeze opponents
	}

	// Enable Outrun Track Select
	if (EnableTrackSelectForOutrun)
	{
		injector::MakeNOP(0x4B2AA0, 2, true);
		injector::MakeNOP(0x5268F8, 2, true); // Disable random outrun tracks
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

	if (ShowDebugCarCustomize)
	{
		injector::MakeRangedNOP(0x520F4C, DebugCarCustomizeCodeCaveExit, true);
		injector::MakeJMP(0x520F4C, DebugCarCustomizeCodeCave, true);
	}

	// Show Any Track in Any Mode
	if (AnyTrackInAnyMode)
	{
		injector::MakeCALL(0x4cdef5, CheckRaceModeHook, true);
	}

	// Takeover
	injector::MakeJMP(0x4FFA1A, StringReplacementCodeCave, true);

	// Show Subtitles
	if (ShowSubtitles)
	{
		injector::MakeNOP(0x4A8BA0, 2, true);
		injector::MakeNOP(0x553A65, 2, true);
		injector::MakeNOP(0x55B061, 2, true);
	}

	// More Customization Options
	if (ShowMoreCustomizationOptions)
	{
		// Add Powder Coat and High Heat categories to Body Paint
		injector::MakeNOP(0x55D26A, PaintCategoryCodeCaveExit - 0x55D26A, true);
		injector::MakeJMP(0x55D26A, PaintCategoryCodeCave, true);
		injector::MakeNOP(0x55D0F0, PaintCategoryCodeCaveExit2 - 0x55D0F0, true);
		injector::MakeJMP(0x55D0F0, PaintCategoryCodeCave2, true);

		// Advan (Yokohama) and Oasis Rims
		injector::MakeJMP(0x54675F, NewRimsCodeCave, true);

		// Hood Decals
		injector::MakeJMP(0x546B7C, HoodDecalsCodeCave, true);

		// Cabin Neons
		injector::MakeJMP(0x548048, CabinNeonCodeCave, true);
	}

	// Fix Hood Decals
	if (HoodDecalsFix)
	{
		injector::WriteMemory<unsigned char>(0x631D27, 0xEB, true);
	}

	// Fix Cabin Neon
	if (CabinNeonFix)
	{
		injector::WriteMemory<unsigned char>(0x635BBC, 0x70, true);
	}

	// Add Debug Vinyls to menu
	if (MoreVinyls)
	{
		injector::MakeNOP(0x54625C, VinylCategoryCodeCaveExit - 0x54625C, true);
		injector::MakeJMP(0x54625C, VinylCategoryCodeCave, true);
	}

	// Carbon-Style Race Status
	if (CarbonStyleRaceStatus)
	{
		injector::WriteMemory<unsigned char>(0x4AA27F, 0xBC, true); // Read lap count instead of game mode

		injector::WriteMemory<unsigned char>(0x4AA283, 0x3C, true); // If lap count
		injector::WriteMemory<unsigned char>(0x4AA284, 0x01, true); // is not 01
		injector::WriteMemory<unsigned char>(0x4AA286, 0x85, true); // Jump to lap x/x
	}

	// Load Headlights preferences
	switch (HeadlightsMode)
	{
	case 0:
		injector::WriteMemory<float>(0x615950, 0, true); // HeadLight
		injector::WriteMemory<unsigned char>(0x7A3658, 0x00, true); //Remove flare
		break;
	case 1:
		injector::WriteMemory<float>(0x615950, LowBeamAmount, true); // HeadLight
		injector::WriteMemory<unsigned char>(0x7A3658, 'H', true);
		break;
	case 2: default:
		injector::WriteMemory<float>(0x615950, HighBeamAmount, true); // HeadLight
		injector::WriteMemory<unsigned char>(0x7A3658, 'H', true);
		break;
	}

	// Neon Brightness
	injector::WriteMemory<float>(0x60d8d0, NeonBrightness, true);

	// World Animation Speed
	injector::WriteMemory<float>(0x803A7C, WorldAnimationSpeed, true);
	injector::MakeNOP(0x61F1F2, 6, true); // Fix animation stops when VSync = Off

	// Game Speed
	injector::WriteMemory<float>(0x7A5730, GameSpeed, true);

	// NOS Trail Repeat Count
	injector::WriteMemory<int>(0x802920, NosTrailRepeatCount, true);

	// Fix Outrun Mode Black Screen
	if (ExperimentalSplitScreenFix)
	{
		injector::WriteMemory<unsigned char>(0x5DACDB, 0xEB, true);
		injector::MakeNOP(0x5C23A9, 2, true);
	}

	// Fix Invisible Wheels
	if (WheelFix)
	{
		injector::WriteMemory<unsigned char>(0x60c5a9, 0x01, true);
	}
	
	// Debug World Camera
	if (EnableDebugWorldCamera)
	{
		injector::WriteMemory<unsigned char>(0x865098, 0x01, true);
	}

	// Garage Hack
	if (GarageCameraHacks)
	{
		injector::MakeNOP(0x44CE63, 5, true);
		injector::WriteMemory<unsigned char>(0x44CE63, 0xB0, true);
		injector::WriteMemory<unsigned char>(0x44CE64, 0x01, true);
	}

	// Rain
	if (AlwaysRain)
	{
		injector::WriteMemory<unsigned char>(0x8A1D38, 0x01, true);
	}
	injector::WriteMemory<float>(0x803968, GeneralRainAmount, true);
	injector::WriteMemory<float>(0x803AC8, RoadReflection, true);
	injector::WriteMemory<float>(0x8039DC, FallingRainSize, true);
	injector::WriteMemory<float>(0x8039E0, RainIntensity, true);
	injector::WriteMemory<float>(0x803970, RainXing, true);
	injector::WriteMemory<float>(0x803974, RainFallSpeed, true);
	injector::WriteMemory<float>(0x803978, RainGravity, true);

	// Allow Longer Save Game Names
	if (AllowLongerProfileNames)
	{
		injector::WriteMemory<unsigned char>(0x556517, 15, true); // UIProfileMenu::ShowKeyboard - Input Limit on Save Game Creation
		injector::WriteMemory<unsigned char>(0x55651B, 0, true); // UIProfileMenu::ShowKeyboard - Allow every character
		injector::WriteMemory<unsigned char>(0x4E910A, 16, true); // FEPkgMemcardList::NotificationMessage - Include Longer Names in the Load Save list
		injector::WriteMemory<unsigned char>(0x4E910E, '/', true); // FEPkgMemcardList::NotificationMessage - Ignore saves with this character
		injector::MakeJMP(0x4E911C, ProfileNameFilterCodeCave, true); // Filters DVD and Magazine covers
		injector::MakeJMP(0x54E746, FixMenuProfileNameLengthCodeCave, true); // Fix the last character
	}

	// Show Debug Event ID
	if (ShowDebugEventID)
	{
		injector::MakeJMP(0x4CE198, ShowDebugEventIDLearnCodeCave, true); // Get event id before hashing
		injector::MakeJMP(0x4CE1C4, ShowDebugEventIDPrintCodeCave, true); // Print it to the debug id object
	}

	// Windowed Mode
	if (WindowedMode != 0)
	{
		injector::WriteMemory<unsigned char>(0x87098C, 1, true);
	}

	if (SkipMovies)
	{
		injector::WriteMemory<unsigned char>(0x8650A8, SkipMovies, true);
	}

	if (!EnableSound)
	{
		injector::WriteMemory<unsigned char>(0x7FAAA8, EnableSound, true);
	}

	if (!EnableMusic)
	{
		injector::WriteMemory<unsigned char>(0x7FAAAC, EnableMusic, true);
	}

	// Other things
	CreateThread(0, 0, (LPTHREAD_START_ROUTINE)&Thing, NULL, 0, NULL);
}

DWORD WINAPI Thing(LPVOID)
{
	while (true)
	{
		Sleep(ThreadDelay);
		GameState = *(DWORD*)0x8654A4; // 3 = FE, 4&5 = Loading screen, 6 = Gameplay
		windowHandle = *(HWND*)0x870990;
		IsOnFocus = !(*(bool*)0x8709E0);
		
		// Windowed Mode Related Fixes
		if (WindowedMode == 2 && windowHandle && !once2)
		{
			RECT o_cRect, n_cRect, n_wRect;
			GetClientRect(windowHandle, &o_cRect);

			DWORD wStyle = GetWindowLongPtr(windowHandle, GWL_STYLE) | WS_VISIBLE | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_OVERLAPPEDWINDOW;
			SetWindowLongPtr(windowHandle, GWL_STYLE, wStyle);

			// make window change style
			SetWindowPos(windowHandle, NULL, 0, 0, 0, 0, SWP_NOZORDER | SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE | SWP_DRAWFRAME);

			GetWindowRect(windowHandle, &n_wRect);
			GetClientRect(windowHandle, &n_cRect);
			int n_wWidth = n_wRect.right - n_wRect.left;
			int n_wHeight = n_wRect.bottom - n_wRect.top;
			int dif_wWidth = o_cRect.right - n_cRect.right;
			int dif_wHeight = o_cRect.bottom - n_cRect.bottom;
			int newWidth = n_wWidth + dif_wWidth;
			int newHeight = n_wHeight + dif_wHeight;

			SetWindowPos(windowHandle, NULL, 0, 0, newWidth, newHeight, SWP_NOZORDER | SWP_NOMOVE | SWP_NOACTIVATE);
			
			once2 = 1;
		}

		if ((GetAsyncKeyState(hotkeyAnyTrackInAnyMode) & 1) && IsOnFocus) // When pressed "Any Track in Any Mode" key
		{
			CIniReader iniReader("NFSU2ExtraOptionsSettings.ini");
			AnyTrackInAnyMode = !AnyTrackInAnyMode;
			iniReader.WriteInteger("Menu", "AnyTrackInAnyRaceMode", AnyTrackInAnyMode);

			if (AnyTrackInAnyMode)
			{
				injector::MakeCALL(0x4cdef5, CheckRaceModeHook, true);
			}

			else
			{
				injector::MakeCALL(0x4cdef5, 0x4987C0, true);
			}

			while ((GetAsyncKeyState(hotkeyAnyTrackInAnyMode) & 0x8000) > 0) { Sleep(ThreadDelay); }
		}

		// Drunk Driver
		if ((GetAsyncKeyState(hotkeyAutoDrive) & 1) && (GameState == 6) && IsOnFocus) // When pressed "Drunk Driver" key
		{
			AutoDrive = !AutoDrive;

			DWORD PlayerThing = *(DWORD*)0x8900AC;

			if (PlayerThing)
			{
				if (AutoDrive)
				{
					Player_AutoPilotOn((DWORD*)PlayerThing);
				}
				else
				{
					Player_AutoPilotOff((DWORD*)PlayerThing);
				}
			}
			
			while ((GetAsyncKeyState(hotkeyAutoDrive) & 0x8000) > 0) { Sleep(ThreadDelay); }
		}

		// Freeze Camera
		if ((GetAsyncKeyState(hotkeyFreezeCamera) & 1) && (GameState == 6) && IsOnFocus)
		{
			*(bool*)0x828640 = !(*(bool*)0x828640);

			while ((GetAsyncKeyState(hotkeyFreezeCamera) & 0x8000) > 0) { Sleep(ThreadDelay); }
		}

		if ((GetAsyncKeyState(hotkeyUnlockAllThings) & 1) && IsOnFocus) // Unlock All Things
		{
			CIniReader iniReader("NFSU2ExtraOptionsSettings.ini");
			UnlockAllThings = !UnlockAllThings;
			iniReader.WriteInteger("Gameplay", "UnlockAllThings", UnlockAllThings);

			if (UnlockAllThings)
			{
				injector::WriteMemory<unsigned char>(0x838464, 1, true);
				injector::MakeNOP(0x50F0D8, 2, true); // Fix individual performance parts
			}

			else
			{
				injector::WriteMemory<unsigned char>(0x838464, 0, true);
				injector::WriteMemory<WORD>(0x50F0D8, 0x1675, true); // Fix individual performance parts
			}

			while ((GetAsyncKeyState(hotkeyUnlockAllThings) & 0x8000) > 0) { Sleep(ThreadDelay); }
		}

		// Headlights
		if ((GetAsyncKeyState(hotkeyToggleHeadlights) & 1) && (GameState == 6) && IsOnFocus) // When pressed "Toggle Head Lights" key
		{
			HeadlightsMode = (HeadlightsMode + 1) % 3; // 0, 1 or 2
			CIniReader iniReader("NFSU2ExtraOptionsSettings.ini");
			iniReader.WriteInteger("Gameplay", "HeadlightsMode", HeadlightsMode);

			switch (HeadlightsMode)
			{
			case 0:
				injector::WriteMemory<float>(0x615950, 0, true); // HeadLight
				injector::WriteMemory<unsigned char>(0x7A3658, 0x00, true); //Remove flare
				break;
			case 1:
				injector::WriteMemory<float>(0x615950, LowBeamAmount, true); // HeadLight
				injector::WriteMemory<unsigned char>(0x7A3658, 'H', true);
				break;
			case 2: default:
				injector::WriteMemory<float>(0x615950, HighBeamAmount, true); // HeadLight
				injector::WriteMemory<unsigned char>(0x7A3658, 'H', true);
				break;
			}

			while ((GetAsyncKeyState(hotkeyToggleHeadlights) & 0x8000) > 0) { Sleep(ThreadDelay); }
		}

		// Save & Load Hot Position
		if ((GameState == 6) && EnableSaveLoadHotPos && IsOnFocus)
		{
			if (GetAsyncKeyState(VK_LSHIFT) & GetAsyncKeyState(49) & 0x8000) // save
			{
				injector::WriteMemory<unsigned char>(0x8900CC, 1, true);
			}

			if (GetAsyncKeyState(VK_LCONTROL) & GetAsyncKeyState(49) & 0x8000) // load
			{
				injector::WriteMemory<unsigned char>(0x8900CD, 1, true);
			}
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

