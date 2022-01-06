#include "stdio.h"
#include <windows.h>
#include "..\includes\injector\injector.hpp"
#include "..\includes\IniReader.h"

bool once2, IsOnFocus, AutoDrive;
DWORD TheGameFlowManager;
HWND windowHandle;

void Thing()
{
	_asm pushad;

	TheGameFlowManager = *(DWORD*)_TheGameFlowManager; // 3 = FE, 4&5 = Loading screen, 6 = Gameplay
	windowHandle = *(HWND*)_hWnd;
	IsOnFocus = !(*(bool*)_IsLostFocus);
	
	// Windowed Mode Related Fixes
	if (WindowedMode && windowHandle && !once2)
	{
		RECT o_cRect, n_cRect, n_wRect;
		GetClientRect(windowHandle, &o_cRect);

		DWORD wStyle = GetWindowLongPtr(windowHandle, GWL_STYLE);

		switch (WindowedMode)
		{
		case 1: wStyle &= ~(WS_CAPTION | WS_THICKFRAME | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_SYSMENU); break;
		case 2: default: wStyle |= (WS_VISIBLE | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_OVERLAPPEDWINDOW); break;
		}

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

		HWND hDesktop = GetDesktopWindow();
		RECT desktop;
		GetWindowRect(hDesktop, &desktop);

		int newXPos = ((desktop.right - desktop.left) - newWidth) / 2;
		int newYPos = ((desktop.bottom - desktop.top) - newHeight) / 2;

		SetWindowPos(windowHandle, NULL, newXPos, newYPos, newWidth, newHeight, SWP_NOZORDER | SWP_NOACTIVATE);

		once2 = 1;
	}

	if ((GetAsyncKeyState(hotkeyAnyTrackInAnyMode) & 1) && IsOnFocus) // When pressed "Any Track in Any Mode" key
	{
		CIniReader iniReader("NFSU2ExtraOptionsSettings.ini");
		AnyTrackInAnyMode = !AnyTrackInAnyMode;
		iniReader.WriteInteger("Menu", "AnyTrackInAnyRaceMode", AnyTrackInAnyMode);

		if (AnyTrackInAnyMode)
		{
			injector::MakeCALL(0x4cdef5, UIQRTrackSelect_IsAvailable, true);
		}

		else
		{
			injector::MakeCALL(0x4cdef5, UIQRTrackSelect_IsAvailable_Game, true);
		}
	}

	// Drunk Driver
	if ((GetAsyncKeyState(hotkeyAutoDrive) & 1) && (TheGameFlowManager == 6) && IsOnFocus) // When pressed "Drunk Driver" key
	{
		AutoDrive = !AutoDrive;

		DWORD PlayerThing = *(DWORD*)_PlayersByNumber;

		if (PlayerThing)
		{
			if (AutoDrive)
			{
				Player_AutoPilotOn((DWORD*)PlayerThing);
			}
			else
			{
				Player_AutoPilotOff((DWORD*)PlayerThing);
				Player_SetInputMode((void*)PlayerThing, 2);
			}
		}
	}

	// Freeze Camera
	if ((GetAsyncKeyState(hotkeyFreezeCamera) & 1) && (TheGameFlowManager == 6) && IsOnFocus)
	{
		static BOOL isCameraFrozen = FALSE;
		static const int call_near_size = 5;
		static BYTE call_backup[call_near_size]; // in case of someone already placed hook there
		static void* const call_SetCameraMatrix = (void*)0x453BF3;
		if (isCameraFrozen) 
		{
			injector::WriteMemoryRaw(call_SetCameraMatrix, call_backup, call_near_size, true);
		}
		else 
		{
			memcpy(call_backup, call_SetCameraMatrix, call_near_size);
			injector::MakeNOP(call_SetCameraMatrix, call_near_size);
		}
		isCameraFrozen ^= 1; // isCameraFrozen = !isCameraFrozen
	}

	if ((GetAsyncKeyState(hotkeyUnlockAllThings) & 1) && IsOnFocus) // Unlock All Things
	{
		CIniReader iniReader("NFSU2ExtraOptionsSettings.ini");
		UnlockAllThings = !UnlockAllThings;
		iniReader.WriteInteger("Gameplay", "UnlockAllThings", UnlockAllThings);

		if (UnlockAllThings)
		{
			injector::WriteMemory<unsigned char>(_UnlockAllThings, 1, true);
			injector::MakeNOP(0x50F0D8, 2, true); // Fix individual performance parts
		}

		else
		{
			injector::WriteMemory<unsigned char>(_UnlockAllThings, 0, true);
			injector::WriteMemory<WORD>(0x50F0D8, 0x1675, true); // Fix individual performance parts
		}
	}

	// Headlights
	if ((GetAsyncKeyState(hotkeyToggleHeadlights) & 1) && (TheGameFlowManager == 6) && IsOnFocus) // When pressed "Toggle Head Lights" key
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
	}

	// Save & Load Hot Position
	if ((TheGameFlowManager == 6) && EnableSaveLoadHotPos && IsOnFocus)
	{
		if (GetAsyncKeyState(VK_LSHIFT) & GetAsyncKeyState(49) & 0x8000) // save
		{
			injector::WriteMemory<unsigned char>(_SaveHotPosition, 1, true);
		}

		if (GetAsyncKeyState(VK_LCONTROL) & GetAsyncKeyState(49) & 0x8000) // load
		{
			injector::WriteMemory<unsigned char>(_JumpToHotPosition, 1, true);
		}
	}

	_asm popad;
}
