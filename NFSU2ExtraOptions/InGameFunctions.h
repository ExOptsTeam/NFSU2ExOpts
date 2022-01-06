#pragma once

#include "stdio.h"
#include <windows.h>
#include "GlobalVariables.h"

// Function pointers
DWORD(*bStringHash)(char const* StringToHash) = (DWORD(*)(char const*))0x43DB50;
DWORD(*bStringHash2)(char const* StringToHash, int PartialHash) = (DWORD(*)(char const*, int))0x43DB80;
char* (__cdecl* _strstr)(char const*, char const*) = (char* (__cdecl*)(char const*, char const*))0x75F140;
void*(__cdecl* j__malloc)(size_t a1) = (void*(__cdecl*)(size_t))0x575620;
int(__thiscall* AddElementToMenuWithStateID)(int _this, int a2, int a3, int a4, int a5) = (int(__thiscall*)(int, int, int, int, int))0x520CB0;
void* (__thiscall* AddCustomElementToMenu)(void* _this, int a2, int a3, int a4) = (void* (__thiscall*)(void*, int, int, int))0x545920;
int(__cdecl* FEHashUpper)(char const* a1) = (int(__cdecl*)(char const*))0x505450;
int(__thiscall* ChooseRimBrand_AddRimCategory)(DWORD* _this, int RimBrandName, int RimBrandIcon, int RimBrandHash) = (int(__thiscall*)(DWORD*, int, int, int))0x5463B0;
int(__thiscall* Player_AutoPilotOn)(DWORD* _Player) = (int(__thiscall*)(DWORD*))0x5FAE20;
int(__thiscall* Player_AutoPilotOff)(DWORD* _Player) = (int(__thiscall*)(DWORD*))0x5FAF10;
int(__thiscall* ChooseDecalCategory_AddCategoryOptionLock)(void* _this, int LayoutID, bool isDecalSelection, int TextureHash, int StringHash) = (int(__thiscall*)(void*, int, bool, int, int))0x52FF60;
int(__thiscall* CustomizeNeonMenu_AddSelection)(void* _this, int CAR_SLOT_ID, int TextureHash, int StringHash, int CarAnimLocation) = (int(__thiscall*)(void*, int, int, int, int))0x53BC90;
int(__cdecl* SelectableTrack_CalcLanguageHash)(int EventID, int IsReverse) = (int(__cdecl*)(int, int))0x516280;
int(__cdecl* FEngSetVisible)(DWORD* FEObject) = (int(__cdecl*)(DWORD*))0x50CA50;
void(__cdecl* FEngSetCenter)(DWORD* FEObject, float x, float y) = (void(__cdecl*)(DWORD*, float, float))0x51D4D0;
int(*FEPrintf)(char const*, int, char const*, ...) = (int(*)(char const*, int, char const*, ...))0x537B80;
DWORD*(__cdecl* FEngFindObject)(char const* pkg_name, DWORD obj_hash) = (DWORD*(__cdecl*)(char const*, DWORD))0x5379C0;
DWORD _ftol2 = 0x75BED4;
bool(__stdcall* UIQRTrackSelect_IsAvailable_Game)(int TrackInfoBlock, int eTrackDirection) = (bool(__stdcall*)(int, int))0x4987C0;
void (__thiscall* IconOption_Create)(DWORD* IconOption, DWORD TextureHash, DWORD StringHash, DWORD Unk) = (void (__thiscall*)(DWORD*, DWORD, DWORD, DWORD))0x51F670;
bool(*bFileExists)(char const* FileName) = (bool(*)(char const*))0x57CAC0;
void(* ChangeToNextBootFlowScreen)(char const* ScreenName, int Unk) = (void(*)(char const*, int))0x4C4F50;
void(__cdecl* SetCurrentLanguage)(int eLanguages) = (void(__cdecl*)(int))0x512360;
int(__cdecl* FEngGetLastButton)(const char* pkg_name) = (int(__cdecl*)(const char*))0x50B8A0;
void(__cdecl* FEngSetLastButton)(const char* pkg_name, DWORD Button) = (void(__cdecl*)(const char*, DWORD))0x50B8C0;
void(__cdecl* FEngSetCurrentButton)(const char* pkg_name, DWORD Button) = (void(__cdecl*)(const char*, DWORD))0x52CEA0;
void(__thiscall* IconScrollerMenu_Create)(DWORD* MenuScreen, DWORD* ScreenConstructorData) = (void(__thiscall*)(DWORD*, DWORD*))0x552330;
void(__thiscall* IconScrollerMenu_RefreshHeader)(DWORD* MenuScreen) = (void(__thiscall*)(DWORD*))0x50DA50;
void(__thiscall* IconScrollerMenu_StartInput)(DWORD* MenuScreen) = (void(__thiscall*)(DWORD*))0x52FBA0;
int(__cdecl* FEngMapPortToControlMask)(int JoystickPort) = (int(__cdecl*)(int))0x50D2D0;
void(__cdecl* FEngSetControlMask)(const char* pkg_name, int ControlMask) = (void(__cdecl*)(const char*, int))0x537950;
void(__thiscall* ThumbnailScroller_SnapToItem)(DWORD* ThumbnailScroller, unsigned int btn) = (void(__thiscall*)(DWORD*, unsigned int))0x538700;
void(__thiscall* IconScrollerMenu_NotificationMessage)(DWORD* IconScrollerMenu, unsigned int MessageHash, unsigned int FEObject, int Arg1, int Arg2) = (void(__thiscall*)(DWORD*, unsigned int, unsigned int, int, int))0x543D40;
void(*FEngSendMessageToPackage)(unsigned int Message, char const* PackageName) = (void(*)(unsigned int, char const*))0x55DDA0;
void(*FEngSetScript)(char const* PackageName, unsigned int ObjectHash, char const* ScriptName, bool) = (void(*)(char const*, unsigned int, char const*, bool))0x537C00;
DWORD*(__cdecl* FEngFindPackage)(const char* pkg_name) = (DWORD*(__cdecl*)(const char*))0x52CEF0;
DWORD*(__cdecl* FEngFindString)(const char* pkg_name, DWORD ObjectHash) = (DWORD*(__cdecl*)(const char*, DWORD))0x537A10;
void(__cdecl* FEngSetLanguageHash)(DWORD* FEString, DWORD LanguageHash) = (void(__cdecl*)(DWORD*, DWORD))0x50C900;
void(__thiscall* sub_504820)(DWORD* Unk, BYTE something) = (void(__thiscall*)(DWORD*, BYTE))0x504820;
void(__thiscall* Player_SetInputMode)(void* Player, int InputMode) = (void(__thiscall*)(void*, int))0x605C70;

// Functions which has odd calling conventions (using UserCalls.h to wrap them)
// none
