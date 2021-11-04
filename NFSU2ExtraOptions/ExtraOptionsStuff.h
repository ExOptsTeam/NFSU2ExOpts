#include "stdio.h"
#include <windows.h>
#include "..\includes\injector\injector.hpp"
#include "..\includes\IniReader.h"

#include "GlobalVariables.h"
#include "InGameFunctions.h"
//#include "UserCalls.h"

BYTE MinimumLap, MaximumLap, KOLap, MinimumCPU, MaximumCPU, KOCPU, MinimumLapLANC, MinimumLapLAND, MinimumLapLANS, MaximumLapLAN, MaximumPlayersLAN, MaximumDriftX, HeadlightsMode, WindowedMode, WheelFix, ExperimentalSplitScreenFix, EnableDebugWorldCamera, GameRegion, ShowMoreRaceOptions;
bool DriftPlus, DriftMultiply, UnlockRegionals, UnlockAllThings, EnableTrackSelectForFreeRun, AnyTrackInAnyMode, RemoveRaceBarriers, RemoveLockedAreaBarriers, GarageCameraHacks, ShowMoreCustomizationOptions, MoreVinyls, ExOptsTeamTakeOver, EnableCameras, ShowOnline, ShowOutrun, EnableTrackSelectForOutrun, once1, ShowSubtitles, UnfreezeKO, CarbonStyleRaceStatus, AlwaysRain, EnableLANSwitcher, LANSwitcherMode, ShowDebugCarCustomize, EnableSaveLoadHotPos, SkipMovies, EnableSound, EnableMusic, HoodDecalsFix, CabinNeonFix, AllowLongerProfileNames, ShowDebugEventID, AllowMultipleInstances, HideNiftyDriftMessages, DamageFix, MegalowPartsFix, ShowLanguageSelectScreen;
float SplashScreenTimeLimit, NeonBrightness, WorldAnimationSpeed, GameSpeed, HeadlightsAmount, GeneralRainAmount, RainXing, RainFallSpeed, RainGravity, LowBeamAmount, HighBeamAmount, RoadReflection, RainIntensity, FallingRainSize;
int DriftMutliplierThresholdPoints[] = { 350, 1400, 4200, 11200, 22400, 38080, 57120, 85680, 300, 1200, 3600, 9600, 19200, 32640, 48960, 73440, 250, 1000, 3000, 8000, 16000, 27200, 40800, 61200, 200, 800, 2400, 6400, 12800, 21760, 32640, 48960 };
int hotkeyAnyTrackInAnyMode, hotkeyUnlockAllThings, hotkeyFreezeCamera, hotkeyToggleHeadlights, hotkeyAutoDrive, StartingCash, NosTrailRepeatCount, DebugEventID;

char* aMagazine = " Magazine ";
char* aDVD = " DVD ";

#include "SplashScreen.h"
#include "UIQRTrackSelect.h"
#include "Player.h"
#include "LanguageSelectScreen.h"

#include "Helpers.h"
#include "CodeCaves.h"
#include "HotkeyStuff.h"

void Init()
{
	// Read values from .ini
	CIniReader iniReader("NFSU2ExtraOptionsSettings.ini");

	// Hotkeys
	hotkeyAnyTrackInAnyMode = iniReader.ReadInteger("Hotkeys", "AnyTrackInAnyMode", 36); // HOME
	hotkeyToggleHeadlights = iniReader.ReadInteger("Hotkeys", "Headlights", 71); // G
	hotkeyFreezeCamera = iniReader.ReadInteger("Hotkeys", "FreezeCamera", 19); // Pause/Break
	hotkeyUnlockAllThings = iniReader.ReadInteger("Hotkeys", "UnlockAllThings", 116); // F5
	hotkeyAutoDrive = iniReader.ReadInteger("Hotkeys", "AutoDrive", 117); //F6
	EnableSaveLoadHotPos = iniReader.ReadInteger("Hotkeys", "EnableSaveLoadHotPos", 0) != 0;

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
	MaximumDriftX = iniReader.ReadInteger("Drift", "MaximumMultiplier", 5);
	DriftPlus = iniReader.ReadInteger("Drift", "PlusSign", 0) != 0;
	DriftMultiply = iniReader.ReadInteger("Drift", "ShowWithoutMultiplying", 0) != 0;
	HideNiftyDriftMessages = iniReader.ReadInteger("Drift", "HideNiftyDriftMessages", 0) != 0;

	// Menu
	ShowOutrun = iniReader.ReadInteger("Menu", "ShowOutrun", 1) != 0;
	ShowMoreRaceOptions = iniReader.ReadInteger("Menu", "ShowMoreRaceOptions", 1) != 0;
	ShowLanguageSelectScreen = iniReader.ReadInteger("Menu", "ShowLanguageSelectScreen", 0) != 0;
	ShowOnline = iniReader.ReadInteger("Menu", "ShowOnline", 1) != 0;
	ShowSubtitles = iniReader.ReadInteger("Menu", "ShowSubs", 1) != 0;
	MoreVinyls = iniReader.ReadInteger("Menu", "ShowSpecialVinyls", 1) != 0;
	ShowDebugCarCustomize = iniReader.ReadInteger("Menu", "ShowDebugCarCustomize", 0) != 0;
	ShowDebugEventID = iniReader.ReadInteger("Menu", "ShowDebugEventID", 0) != 0;
	AnyTrackInAnyMode = iniReader.ReadInteger("Menu", "AnyTrackInAnyRaceMode", 1) != 0;
	EnableTrackSelectForFreeRun = iniReader.ReadInteger("Menu", "FreeRunTrackSelect", 1) != 0;
	EnableTrackSelectForOutrun = iniReader.ReadInteger("Menu", "OutrunTrackSelect", 1) != 0;
	SplashScreenTimeLimit = iniReader.ReadFloat("Menu", "SplashScreenTimeLimit", 30.0f);
	GarageCameraHacks = iniReader.ReadInteger("Menu", "ShowcaseCamInfiniteYRotation", 0) != 0;
	AllowLongerProfileNames = iniReader.ReadInteger("Menu", "AllowLongerProfileNames", 0) != 0;
	ExOptsTeamTakeOver = iniReader.ReadInteger("Menu", "DisableTakeover", 0) == 0;

	// Gameplay
	EnableCameras = iniReader.ReadInteger("Gameplay", "EnableHiddenCameraModes", 1) != 0;
	EnableDebugWorldCamera = iniReader.ReadInteger("Gameplay", "EnableDebugCamera", 0) != 0;
	GameSpeed = iniReader.ReadFloat("Gameplay", "GameSpeed", 1.0f);
	WorldAnimationSpeed = iniReader.ReadFloat("Gameplay", "WorldAnimationSpeed", 45.0f);
	HeadlightsMode = iniReader.ReadInteger("Gameplay", "HeadlightsMode", 2);
	LowBeamAmount = iniReader.ReadFloat("Gameplay", "LowBeamBrightness", 0.75f);
	HighBeamAmount = iniReader.ReadFloat("Gameplay", "HighBeamBrightness", 1.00f);
	RemoveRaceBarriers = iniReader.ReadInteger("Gameplay", "RemoveRaceBarriers", 0) != 0;
	RemoveLockedAreaBarriers = iniReader.ReadInteger("Gameplay", "RemoveLockedAreaBarriers", 1) != 0;
	CarbonStyleRaceStatus = iniReader.ReadInteger("Gameplay", "ShowPercentOn1LapRaces", 0) != 0;
	GameRegion = iniReader.ReadInteger("Gameplay", "GameRegion", 0);
	StartingCash = iniReader.ReadInteger("Gameplay", "StartingCash", 0);
	UnlockRegionals = iniReader.ReadInteger("Gameplay", "UnlockRegionalCars", 1) != 0;
	UnlockAllThings = iniReader.ReadInteger("Gameplay", "UnlockAllThings", 1) != 0;
	NeonBrightness = iniReader.ReadFloat("Gameplay", "NeonBrightness", 1.0f);
	NosTrailRepeatCount = iniReader.ReadInteger("Gameplay", "NosTrailRepeatCount", 8);

	// Weather
	AlwaysRain = iniReader.ReadInteger("Weather", "AlwaysRain", 0) != 0;
	GeneralRainAmount = iniReader.ReadFloat("Weather", "GeneralRainAmount", 1.0f);
	RoadReflection = iniReader.ReadFloat("Weather", "RoadReflectionAmount", 1.0f);
	FallingRainSize = iniReader.ReadFloat("Weather", "RainSize", 0.03f);
	RainIntensity = iniReader.ReadFloat("Weather", "RainIntensity", 0.7f);
	RainXing = iniReader.ReadFloat("Weather", "RainCrossing", 0.02f);
	RainFallSpeed = iniReader.ReadFloat("Weather", "RainSpeed", 0.03f);
	RainGravity = iniReader.ReadFloat("Weather", "RainGravity", 0.45f);

	// Fixes
	WheelFix = iniReader.ReadInteger("Fixes", "DisappearingWheelsFix", 1) != 0;
	ExperimentalSplitScreenFix = iniReader.ReadInteger("Fixes", "ExperimentalSplitScreenFix", 0) != 0;
	DamageFix = iniReader.ReadInteger("Fixes", "DamageFix", 1) != 0;
	MegalowPartsFix = iniReader.ReadInteger("Fixes", "MegalowPartsFix", 1) != 0;

	// Misc
	WindowedMode = iniReader.ReadInteger("Misc", "WindowedMode", 0);
	SkipMovies = iniReader.ReadInteger("Misc", "SkipMovies", 0) != 0;
	EnableSound = iniReader.ReadInteger("Misc", "EnableSound", 1) != 0;
	EnableMusic = iniReader.ReadInteger("Misc", "EnableMusic", 1) != 0;
	AllowMultipleInstances = iniReader.ReadInteger("Misc", "AllowMultipleInstances", 0) != 0;

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
		injector::WriteMemory<BYTE>(0x580E11, 0xEB, true); // main
	}

	// Lap and opponent controllers
	injector::WriteMemory<BYTE>(0x4B3D82, MinimumLap, true);		// TONumLaps::Act, Minimum Lap Controller For Decrement
	injector::WriteMemory<BYTE>(0x4B3D9B, MinimumLap, true);		// TONumLaps::Act, Minimum Lap Controller For Increment
	injector::WriteMemory<BYTE>(0x4B3D86, MaximumLap, true);		// TONumLaps::Act, Maximum Lap Controller For Decrement
	injector::WriteMemory<BYTE>(0x4B3D97, MaximumLap, true);		// TONumLaps::Act, Maximum Lap Controller For Increment
	injector::WriteMemory<BYTE>(0x4B407F, KOLap, true);				// TOLapKO::Act, Amount of Laps when KO Enabled

	injector::MakeNOP(0x4b3867, 4, true);							// MO_QR_NumOpponents::Act, Enable minimum opponent controller
	injector::WriteMemory<BYTE>(0x4b3863, MinimumCPU, true);		// MO_QR_NumOpponents::Act, Minimum Opponent Controller
	injector::MakeNOP(0x4b382b, 6, true);							// MO_QR_NumOpponents::Act, Fix Maximum Opponent Controller (No +2 for URL)
	injector::WriteMemory<BYTE>(0x4b3834, MaximumCPU, true);		// MO_QR_NumOpponents::Act, Maximum Opponent Controller
	injector::WriteMemory<BYTE>(0x4B4075, KOCPU, true);				// TOLapKO::Act, Amount of Opponents when KO Enabled

	injector::WriteMemory<BYTE>(0x4B3E7A, MinimumLap, true);		// TO_OL_NumLaps::TO_OL_NumLaps, Minimum Lap Controller For LAN Circuit & URL
	injector::WriteMemory<BYTE>(0x4B3EE4, MinimumLap, true);		// TO_OL_NumLaps::TO_OL_NumLaps, Minimum Lap Controller For LAN Drift
	injector::WriteMemory<BYTE>(0x4B3E9E, MinimumLap, true);		// TO_OL_NumLaps::TO_OL_NumLaps, Minimum Lap Controller For LAN Street X
	injector::WriteMemory<BYTE>(0x4B3F30, MaximumLap, true);		// TO_OL_NumLaps::Act, Maximum Lap Controller For Decrement (Lan)
	injector::WriteMemory<BYTE>(0x4B3F41, MaximumLap, true);		// TO_OL_NumLaps::Act, Maximum Lap Controller For Increment (Lan)
	injector::WriteMemory<BYTE>(0x4B31AA, 0xB0, true);				// MO_OL_NumPlayers::Act, Maximum Players Fix - lea to mov al,X
	injector::WriteMemory<BYTE>(0x4B31AB, MaximumPlayersLAN, true);	// MO_OL_NumPlayers::Act, Maximum Players Controller (LAN)
	injector::MakeNOP(0x4B31AC, 2, true);							// MO_OL_NumPlayers::Act, Maximum Players Fix - nop remaining bytes from lea

	// Fix "insert disc 2" bug for PCs with No Optical Drive
	injector::WriteMemory<BYTE>(0x5C0D3F, 0x78, true); // sub_5C0D30
	injector::WriteMemory<BYTE>(0x5C0D54, 0x00, true);

	// Show drift as AxB hack
	if (DriftMultiply)
	{
		injector::WriteMemory<BYTE>(0x4AB792, 0xb0, true); // sub_4AB780
		injector::WriteMemory<BYTE>(0x4AB793, 0x01, true);
		injector::WriteMemory<BYTE>(0x4AB794, 0x90, true);
	}

	// Add a + before drift point
	if (DriftPlus)
	{
		injector::WriteMemory<BYTE>(0x4AB7DB, 0x74, true); // sub_4AB780
	}

	// Hide "Good Drift", "Insane Drift", etc.
	if (HideNiftyDriftMessages)
	{
		injector::WriteMemory<BYTE>(0x4AC136, 0xEB, true); // FEngHud::ShowNiftyDriftyMessage
	}

	injector::WriteMemory<BYTE>(0x56CC98, 0xCF, true); // sub_56CB50, Change Threshold array sizes from 4(x5) to 8(x9).
	injector::WriteMemory<BYTE>(0x56CC9C, 0x00, true); // sub_56CB50, Change the address of Drift multiplier threshold points arrays
	injector::WriteMemory<BYTE>(0x56CC9D, 0x50, true);
	injector::WriteMemory<BYTE>(0x56CC9E, 0x92, true);
	for (int i = 0; i < 32; i++) injector::WriteMemory(0x925004 + 4 * i, DriftMutliplierThresholdPoints[i], true);
	injector::WriteMemory<BYTE>(0x56CC58, MaximumDriftX, true); // sub_56CB50, Maximum Drift Level Controller (Main)
	injector::WriteMemory<BYTE>(0x56CC90, MaximumDriftX, true); // sub_56CB50, Maximum Drift Level Controller (To Show threshold points)

	// Buff/Nerf Static Scores for Sprint Drift
	injector::WriteMemory<float>(0x925100, ((float)MaximumDriftX / 5.0f), true);
	injector::MakeRangedNOP(0x56DB51, 0x56DB59, true); // DriftManager::BuildLeaderBoard
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

		// Unlock 106 and Corsa for Car List, EUExclusiveCars
		injector::WriteMemory<BYTE>(0x7F7C48, 0xFF, true); // CORSA
		injector::WriteMemory<BYTE>(0x7F7C4C, 0xFF, true); // PEUGOT106

		// Fix Civic and RSX for other regions, USExclusiveCars
		injector::WriteMemory<BYTE>(0x7F7C50, 0xFF, true); // CIVIC
		injector::WriteMemory<BYTE>(0x7F7C54, 0xFF, true); // RSX

		// Hook region lock to return always true
		injector::MakeCALL(0x4DFA83, RegionLockHook, true); // UICareerCarLot::BuildCarList
		injector::MakeCALL(0x4E2374, RegionLockHook, true); // UIQRCarSelect::BuildCarList

		// Unlock them as AI opponents
		injector::WriteMemory<BYTE>(0x4FEB9D, 0x1C, true); // PickRandomCarsOfSomeSort, Extend array by 2
		injector::WriteMemory<BYTE>(0x7F6DBE, 0x07, true); // RandomlyChooseableCarConfigsNorthAmerica, CORSA
		injector::WriteMemory<BYTE>(0x7F6DBF, 0x06, true); // PEUGOT106
	}

	// Set Game Region
	injector::WriteMemory<BYTE>(_BuildRegion, GameRegion, true);

	// Unlock All Things - Load preference
	if (UnlockAllThings)
	{
		injector::WriteMemory<BYTE>(_UnlockAllThings, 1, true);
		injector::MakeNOP(0x50F0D8, 2, true); // CarCustomizeManager::GetPartUnlockFilter, Fix individual performance parts
	}

	// Enable Track Selection Screen for Free Run (9) Game Mode
	if (EnableTrackSelectForFreeRun)
	{
		injector::MakeNOP(0x4B2AE3, 2, true); // sub_4B2A80
	}

	// Remove Neon Route Indicator Barriers from Races
	if (RemoveRaceBarriers)
	{
		injector::WriteMemory<BYTE>(0x7A078B, 77, true); // "PLAYER_BARRIERS_%d"
		injector::WriteMemory<BYTE>(0x7A0798, 77, true); // "BARRIERS_%d"

		injector::MakeJMP(0x578070, BarrierCodeCave, true); // sub_578060
	}

	// Remove Neon Locked Area Indicator Barriers from Career Mode
	if (RemoveLockedAreaBarriers)
	{
		injector::WriteMemory<BYTE>(0x7A073C, 77, true); // "BARRIERS_CAREER%d"
	}

	// Splash screen time limit
	injector::WriteMemory<float>(0x784478, SplashScreenTimeLimit, true);

	// Starting Cash
	injector::MakeRangedNOP(0x53290D, 0x532913, true); // PlayerCareerState::Default
	injector::MakeJMP(0x53290D, StartingCashCodeCave, true);

	// Enable Drift and Driver Camera For All
	if (EnableCameras)
	{
		// Increase number of selectable camera angles to 5
		injector::WriteMemory<int>(0x50254E, 5, true); // PlayerSettings::ScrollDriveCam
		injector::WriteMemory<int>(0x502575, 5, true);

		// Make driver camera selectable
		injector::MakeJMP(0x502500, GetPOVTypeFromPlayerCamera, true); // 6 references
	}

	// Show More Race Options
	if (ShowMoreRaceOptions)
	{
		if (ShowMoreRaceOptions >= 2)
		{
			// Opponents in Sprint Drift Races
			injector::MakeNOP(0x4CD8D8, 2, true); // UIQRModeOptions::SetupDrift
			injector::WriteMemory<BYTE>(0x53F8B0, 0xEB, true); // RaceStarter::SetupDriftRace, Fix 0 overwrite

			injector::WriteMemory<BYTE>(0x56DA0C, 0xA0, true); // DriftManager::BuildLeaderBoard, eax 0 = Autoscores, 1-5 = ai opponents
			injector::MakeRangedNOP(0x56D9F1, 0x56DA0C, true); // 0 = Autoscores for all tracks
			injector::WriteMemory<DWORD>(0x56DA0D, 0x83AB01, true); // ai count
			injector::MakeRangedNOP(0x56DA11, 0x56DA16, true);
		}
		
		// Unfreeze KO
		injector::WriteMemory<BYTE>(0x4b4068, 0xEB, true); // Don't copy static numbers
		injector::WriteMemory<BYTE>(0x4B3E14, 0xEB, true); // Don't freeze laps
		injector::WriteMemory<BYTE>(0x4B3903, 0xEB, true); // Don't freeze opponents
	}

	// Enable Outrun Track Select
	if (EnableTrackSelectForOutrun)
	{
		injector::MakeNOP(0x4B2AA0, 2, true); // sub_4B2A80
		injector::MakeNOP(0x5268F8, 2, true); // RaceStarter::SetupOutrun, Disable random outrun tracks
	}

	// Show Outrun at Quick Race Menu
	if (ShowOutrun)
	{
		injector::MakeNOP(0x4B2F3E, 2, true); // UIQRModeSelect::Setup
	}

	// Remove Online Option from Main Menu
	if (!ShowOnline)
	{
		injector::WriteMemory<BYTE>(0x4AEEDF, 0xEB, true); // UIMain::Setup
	}

	// Show Debug Car Customize
	if (ShowDebugCarCustomize)
	{
		injector::MakeRangedNOP(0x520F4C, 0x520F51, true);
		injector::MakeJMP(0x520F4C, DebugCarCustomizeCodeCave, true); // ChooseCustomizeCategory::Setup
	}

	// Show Language Select Screen at boot
	if (ShowLanguageSelectScreen)
	{
		injector::WriteMemory(0x7F662C, 0x7999A8, true); // BootFlowPAL, "LS_LangSelect.fng"
		injector::WriteMemory(0x7F65F4, 0x7999A8, true); // BootFlowNTSC, "LS_LangSelect.fng"
		injector::WriteMemory(0x797D00, &LanguageSelectScreen_NotificationMessage, true); // LanguageSelectScreen::`vtbl'
		injector::WriteMemory(0x797D0C, &LanguageSelectScreen_Setup, true); // LanguageSelectScreen::`vtbl'
		injector::WriteMemory(0x7F8C20, &CreateLanguageSelectScreen, true); // ScreenFactoryData
	}

	// Show Any Track in Any Mode
	if (AnyTrackInAnyMode)
	{
		injector::MakeCALL(0x4cdef5, UIQRTrackSelect_IsAvailable, true); // UIQRTrackSelect::BuildPresetTrackList
	}

	// Takeover
	if (ExOptsTeamTakeOver)
	{
		injector::MakeJMP(0x4A91B6, SplashScreenCodeCave, true); // SplashScreen::SplashScreen
	}

	// Show Subtitles
	if (ShowSubtitles)
	{
		injector::MakeNOP(0x4A8BA0, 2, true); // PSAMovieScreen::PSAMovieScreen
		injector::MakeNOP(0x553A65, 2, true); // InGamePlayMovie::InGamePlayMovie
		injector::MakeNOP(0x55B061, 2, true); // InGamePlayMovie::NotificationMessage
	}

	// Fix damage
	if (DamageFix)
	{
		injector::WriteMemory<BYTE>(0x59FC13, 0xEB, true); // Collision::CheckForWildCollision
	}

	// Add Debug Vinyls to menu
	if (MoreVinyls)
	{
		injector::MakeRangedNOP(0x54625C, 0x546265, true); // PartSelectionScreen::SetupVinyls
		injector::MakeJMP(0x54625C, VinylCategoryCodeCave, true);
	}

	// Carbon-Style Race Status
	if (CarbonStyleRaceStatus)
	{
		// LapCounter::Update
		injector::WriteMemory<BYTE>(0x4AA27F, 0xBC, true); // Read lap count instead of game mode
		injector::WriteMemory<BYTE>(0x4AA283, 0x3C, true); // If lap count
		injector::WriteMemory<BYTE>(0x4AA284, 0x01, true); // is not 01
		injector::WriteMemory<BYTE>(0x4AA286, 0x85, true); // Jump to lap x/x
	}

	// Load Headlights preferences
	switch (HeadlightsMode)
	{
	case 0:
		injector::WriteMemory<float>(0x615950, 0, true); // HeadLight
		injector::WriteMemory<BYTE>(0x7A3658, 0x00, true); //Remove flare
		break;
	case 1:
		injector::WriteMemory<float>(0x615950, LowBeamAmount, true); // HeadLight
		injector::WriteMemory<BYTE>(0x7A3658, 'H', true);
		break;
	case 2: default:
		injector::WriteMemory<float>(0x615950, HighBeamAmount, true); // HeadLight
		injector::WriteMemory<BYTE>(0x7A3658, 'H', true);
		break;
	}

	// Neon Brightness
	injector::WriteMemory<float>(0x60d8d0, NeonBrightness, true); // CarRenderInfo::RenderNeon

	// World Animation Speed
	injector::WriteMemory<float>(_wspeed, WorldAnimationSpeed, true);
	injector::MakeNOP(0x61F1F2, 6, true); // Rain::UpdateAndRender, Fix animation stops when VSync = Off

	// Game Speed
	injector::WriteMemory<float>(_Tweak_GameSpeed, GameSpeed, true);

	// NOS Trail Repeat Count
	injector::WriteMemory<int>(_FlareDiv, NosTrailRepeatCount, true);

	// Fix Outrun Mode Black Screen
	if (ExperimentalSplitScreenFix)
	{
		injector::WriteMemory<BYTE>(0x5DACDB, 0xEB, true); // sub_5DACB0
		injector::MakeNOP(0x5C23A9, 2, true); // sub_5C21E0
	}

	// Fix Invisible Wheels
	if (WheelFix)
	{
		injector::WriteMemory<BYTE>(0x60c5a9, 0x01, true); // CarPartCuller::CullParts
	}

	// Debug World Camera
	if (EnableDebugWorldCamera)
	{
		injector::WriteMemory<BYTE>(_DebugCamerasEnabled, 0x01, true);
	}

	// Garage Hack
	if (GarageCameraHacks)
	{
		injector::MakeNOP(0x44CE63, 5, true); // SelectCarCameraMover::Update
		injector::WriteMemory<BYTE>(0x44CE63, 0xB0, true);
		injector::WriteMemory<BYTE>(0x44CE64, 0x01, true);
	}

	// Rain
	if (AlwaysRain)
	{
		injector::WriteMemory<BYTE>(_precipDEBUG, 0x01, true);
	}
	injector::WriteMemory<float>(_precipPERCENT, GeneralRainAmount, true);
	injector::WriteMemory<float>(_BaseDampness, RoadReflection, true);
	injector::WriteMemory<float>(_RAINRadiusX, FallingRainSize, true);
	injector::WriteMemory<float>(_RAINRadiusY, RainIntensity, true);
	injector::WriteMemory<float>(_RAINY, RainXing, true);
	injector::WriteMemory<float>(_RAINZ, RainFallSpeed, true);
	injector::WriteMemory<float>(_RAINZconstant, RainGravity, true);

	// Allow Longer Save Game Names
	if (AllowLongerProfileNames)
	{
		injector::WriteMemory<BYTE>(0x556517, 15, true); // UIProfileMenu::ShowKeyboard - Input Limit on Save Game Creation
		injector::WriteMemory<BYTE>(0x55651B, 0, true); // UIProfileMenu::ShowKeyboard - Allow every character
		injector::WriteMemory<BYTE>(0x4E910A, 16, true); // FEPkgMemcardList::NotificationMessage - Include Longer Names in the Load Save list
		injector::WriteMemory<BYTE>(0x4E910E, '/', true); // FEPkgMemcardList::NotificationMessage - Ignore saves with this character
		injector::MakeJMP(0x4E911C, ProfileNameFilterCodeCave, true); // Filters DVD and Magazine covers
		injector::MakeJMP(0x54E746, FixMenuProfileNameLengthCodeCave, true); // Fix the last character
	}

	// Show Debug Event ID
	if (ShowDebugEventID)
	{
		// UIQRTrackSelect::RefreshHeader
		injector::MakeJMP(0x4CE198, ShowDebugEventIDLearnCodeCave, true); // Get event id before hashing
		injector::MakeJMP(0x4CE1C4, ShowDebugEventIDPrintCodeCave, true); // Print it to the debug id object
	}

	// Megalow Parts Fix
	if (MegalowPartsFix)
	{
		injector::MakeJMP(0x46B3F9, MegalowPartsFixCodeCave, true); // EAXS_PFController::GetAmbientZone
		injector::WriteMemory<int>(0x4C4D87, -1, true); // LoadingTips::CalcGameTipToSee
		injector::WriteMemory<int>(0x52442A, -1, true);
		injector::WriteMemory<int>(0x53043A, -1, true);
		injector::WriteMemory<int>(0x54163B, -1, true);
		injector::WriteMemory<int>(0x556F1D, -1, true);
		injector::WriteMemory<int>(0x5627BD, -1, true);
	}

	// Windowed Mode
	if (WindowedMode != 0)
	{
		injector::WriteMemory<BYTE>(_WindowedMode, 1, true);
	}

	if (SkipMovies)
	{
		injector::WriteMemory<BYTE>(_SkipMovies, SkipMovies, true);
	}

	if (!EnableSound)
	{
		injector::WriteMemory<BYTE>(_IsSoundEnabled, EnableSound, true);
	}

	if (!EnableMusic)
	{
		injector::WriteMemory<BYTE>(_IsAudioStreamingEnabled, EnableMusic, true);
	}

	// Other things
	injector::MakeCALL(0x581470, Thing, true); // Hook the hotkey detection to the main loop
}
