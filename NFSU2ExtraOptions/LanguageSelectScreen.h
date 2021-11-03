#include "stdio.h"
#include <windows.h>
#include "InGameFunctions.h"

void __fastcall ChooseLanguage_React(DWORD* IconOption, void* EDX_Unused, char const* FEPackageName, unsigned int Data, DWORD* FEObject, unsigned int Param1, unsigned int Param2)
{
    if (Data == 0xC407210)
    {
        SetCurrentLanguage(IconOption[9]);
        ChangeToNextBootFlowScreen(FEPackageName, Param1);
    }
}

DWORD ChooseLanguage_vtable[2] = {
    0x4AEB70, // free
    (DWORD)ChooseLanguage_React
};

void __fastcall LanguageSelectScreen_Setup(DWORD* LanguageSelectScreen, void* EDX_Unused)
{
    DWORD* TheIconOption;

    char const* PackageName = (const char*)LanguageSelectScreen[1];
    /*
    DWORD* HeaderTextObject = FEngFindString(PackageName, 0x47FF4E7C);
    FEngSetLanguageHash(HeaderTextObject, 0x6C839FBE);
    */

    if (bFileExists("Languages\\English.bin"))
    {
        TheIconOption = (DWORD*)j__malloc(72);
        if (TheIconOption)
        {
            IconOption_Create(TheIconOption, bStringHash("LANG_ENGLISH"), bStringHash("LANG_ENGLISH"), 0);
            TheIconOption[0] = (DWORD)ChooseLanguage_vtable;
            TheIconOption[9] = 0;
        }
        else
        {
            TheIconOption = 0;
        }
        (*(void(__thiscall**)(DWORD*, DWORD*))(*LanguageSelectScreen + 24))(LanguageSelectScreen, TheIconOption); // IconScrollerMenu::AddOption
    }

    if (bFileExists("Languages\\French.bin"))
    {
        TheIconOption = (DWORD*)j__malloc(72);
        if (TheIconOption)
        {
            IconOption_Create(TheIconOption, bStringHash("LANG_FRENCH"), bStringHash("LANG_FRENCH"), 0);
            TheIconOption[0] = (DWORD)ChooseLanguage_vtable;
            TheIconOption[9] = 1;
        }
        else
        {
            TheIconOption = 0;
        }
        (*(void(__thiscall**)(DWORD*, DWORD*))(*LanguageSelectScreen + 24))(LanguageSelectScreen, TheIconOption); // IconScrollerMenu::AddOption
    }

    if (bFileExists("Languages\\German.bin"))
    {
        TheIconOption = (DWORD*)j__malloc(72);
        if (TheIconOption)
        {
            IconOption_Create(TheIconOption, bStringHash("LANG_GERMAN"), bStringHash("LANG_GERMAN"), 0);
            TheIconOption[0] = (DWORD)ChooseLanguage_vtable;
            TheIconOption[9] = 2;
        }
        else
        {
            TheIconOption = 0;
        }
        (*(void(__thiscall**)(DWORD*, DWORD*))(*LanguageSelectScreen + 24))(LanguageSelectScreen, TheIconOption); // IconScrollerMenu::AddOption
    }

    if (bFileExists("Languages\\Italian.bin"))
    {
        TheIconOption = (DWORD*)j__malloc(72);
        if (TheIconOption)
        {
            IconOption_Create(TheIconOption, bStringHash("LANG_ITALIAN"), bStringHash("LANG_ITALIAN"), 0);
            TheIconOption[0] = (DWORD)ChooseLanguage_vtable;
            TheIconOption[9] = 3;
        }
        else
        {
            TheIconOption = 0;
        }
        (*(void(__thiscall**)(DWORD*, DWORD*))(*LanguageSelectScreen + 24))(LanguageSelectScreen, TheIconOption); // IconScrollerMenu::AddOption
    }

    if (bFileExists("Languages\\Spanish.bin"))
    {
        TheIconOption = (DWORD*)j__malloc(72);
        if (TheIconOption)
        {
            IconOption_Create(TheIconOption, bStringHash("LANG_SPANISH"), bStringHash("LANG_SPANISH"), 0);
            TheIconOption[0] = (DWORD)ChooseLanguage_vtable;
            TheIconOption[9] = 4;
        }
        else
        {
            TheIconOption = 0;
        }
        (*(void(__thiscall**)(DWORD*, DWORD*))(*LanguageSelectScreen + 24))(LanguageSelectScreen, TheIconOption); // IconScrollerMenu::AddOption
    }

    if (bFileExists("Languages\\Dutch.bin"))
    {
        TheIconOption = (DWORD*)j__malloc(72);
        if (TheIconOption)
        {
            IconOption_Create(TheIconOption, bStringHash("LANG_DUTCH"), bStringHash("LANG_DUTCH"), 0);
            TheIconOption[0] = (DWORD)ChooseLanguage_vtable;
            TheIconOption[9] = 5;
        }
        else
        {
            TheIconOption = 0;
        }
        (*(void(__thiscall**)(DWORD*, DWORD*))(*LanguageSelectScreen + 24))(LanguageSelectScreen, TheIconOption); // IconScrollerMenu::AddOption
    }

    if (bFileExists("Languages\\Swedish.bin"))
    {
        TheIconOption = (DWORD*)j__malloc(72);
        if (TheIconOption)
        {
            IconOption_Create(TheIconOption, bStringHash("LANG_SWEDISH"), bStringHash("LANG_SWEDISH"), 0);
            TheIconOption[0] = (DWORD)ChooseLanguage_vtable;
            TheIconOption[9] = 6;
        }
        else
        {
            TheIconOption = 0;
        }
        (*(void(__thiscall**)(DWORD*, DWORD*))(*LanguageSelectScreen + 24))(LanguageSelectScreen, TheIconOption); // IconScrollerMenu::AddOption
    }

    if (bFileExists("Languages\\Danish.bin"))
    {
        TheIconOption = (DWORD*)j__malloc(72);
        if (TheIconOption)
        {
            IconOption_Create(TheIconOption, bStringHash("LANG_DANISH"), bStringHash("LANG_DANISH"), 0);
            TheIconOption[0] = (DWORD)ChooseLanguage_vtable;
            TheIconOption[9] = 7;
        }
        else
        {
            TheIconOption = 0;
        }
        (*(void(__thiscall**)(DWORD*, DWORD*))(*LanguageSelectScreen + 24))(LanguageSelectScreen, TheIconOption); // IconScrollerMenu::AddOption
    }

    if (bFileExists("Languages\\Korean.bin"))
    {
        TheIconOption = (DWORD*)j__malloc(72);
        if (TheIconOption)
        {
            IconOption_Create(TheIconOption, bStringHash("LANG_KOREAN"), bStringHash("LANG_KOREAN"), 0);
            TheIconOption[0] = (DWORD)ChooseLanguage_vtable;
            TheIconOption[9] = 8;
        }
        else
        {
            TheIconOption = 0;
        }
        (*(void(__thiscall**)(DWORD*, DWORD*))(*LanguageSelectScreen + 24))(LanguageSelectScreen, TheIconOption); // IconScrollerMenu::AddOption
    }

    if (bFileExists("Languages\\Chinese.bin"))
    {
        TheIconOption = (DWORD*)j__malloc(72);
        if (TheIconOption)
        {
            IconOption_Create(TheIconOption, bStringHash("LANG_CHINESE"), bStringHash("LANG_CHINESE"), 0);
            TheIconOption[0] = (DWORD)ChooseLanguage_vtable;
            TheIconOption[9] = 9;
        }
        else
        {
            TheIconOption = 0;
        }
        (*(void(__thiscall**)(DWORD*, DWORD*))(*LanguageSelectScreen + 24))(LanguageSelectScreen, TheIconOption); // IconScrollerMenu::AddOption
    }

    if (bFileExists("Languages\\Japanese.bin"))
    {
        TheIconOption = (DWORD*)j__malloc(72);
        if (TheIconOption)
        {
            IconOption_Create(TheIconOption, bStringHash("LANG_JAPANESE"), bStringHash("LANG_JAPANESE"), 0);
            TheIconOption[0] = (DWORD)ChooseLanguage_vtable;
            TheIconOption[9] = 10;
        }
        else
        {
            TheIconOption = 0;
        }
        (*(void(__thiscall**)(DWORD*, DWORD*))(*LanguageSelectScreen + 24))(LanguageSelectScreen, TheIconOption); // IconScrollerMenu::AddOption
    }

    FEngSetLastButton(PackageName, 0);
    DWORD* IconScroller = (DWORD*)LanguageSelectScreen[19];
    (*(void(__thiscall**)(DWORD*, int))(IconScroller + 8))(LanguageSelectScreen + 19, FEngGetLastButton(PackageName)); // IconScroller::SetInitialPos
    (*(void(__thiscall**)(DWORD*))(IconScroller + 1))(LanguageSelectScreen + 19); // IconScroller::Update
    (*(void(__thiscall**)(DWORD*))(*LanguageSelectScreen + 16))(LanguageSelectScreen); // IconScrollerMenu_RefreshHeader
}

#define _LanguageSelectScreen_vtbl 0x797CF8

void __fastcall LanguageSelectScreen_NotificationMessage(DWORD* LanguageSelectScreen, void* EDX_Unused, unsigned int MessageHash, unsigned int FEObject, int Arg1, int Arg2)
{
    IconScrollerMenu_NotificationMessage(LanguageSelectScreen, MessageHash, FEObject, Arg1, Arg2);
    //if (MessageHash == 0xC98356BA && (*(float*)_RealTimer - (float)LanguageSelectScreen[83] * 0.00025000001 > 3.0))
        ChangeToNextBootFlowScreen((char const*)LanguageSelectScreen[1], Arg1);
}

void CreateLanguageSelectScreen(DWORD* ScreenConstructorData)
{
    DWORD* LanguageSelectScreen; // esi

    LanguageSelectScreen = (DWORD*)j__malloc(336);
    if (LanguageSelectScreen)
    {
        IconScrollerMenu_Create(LanguageSelectScreen, ScreenConstructorData);
        LanguageSelectScreen[0] = _LanguageSelectScreen_vtbl;
        LanguageSelectScreen_Setup(LanguageSelectScreen, 0);

        /*
        char const* PackageName = (const char*)LanguageSelectScreen[1];
        int ControlMask = FEngMapPortToControlMask(*(DWORD*)0x83A9D8);
        FEngSetControlMask(PackageName, ControlMask);
        sub_504820((DWORD*)ScreenConstructorData[1], 0);
        */
        LanguageSelectScreen[83] = *(float*)_RealTimer;

    }
}