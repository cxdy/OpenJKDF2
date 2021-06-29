#include "jkGUIMain.h"

#include "General/stdBitmap.h"
#include "General/stdFont.h"
#include "Engine/rdMaterial.h" // TODO move stdVBuffer
#include "stdPlatform.h"
#include "jk.h"
#include "Gui/jkGUIRend.h"
#include "Gui/jkGUI.h"
#include "World/jkPlayer.h"
#include "Main/jkStrings.h"
#include "General/stdFnames.h"
#include "General/Darray.h"
#include "Gui/jkGUITitle.h"
#include "Gui/jkGUISingleplayer.h"
#include "Gui/jkGUIMultiplayer.h"
#include "Gui/jkGUIDialog.h"
#include "Gui/jkGUIPlayer.h"
#include "Gui/jkGUINet.h"
#include "Gui/jkGUISetup.h"
#include "Win95/sithDplay.h"
#include "Win95/stdGdi.h"
#include "Win95/Windows.h"
#include "Main/Main.h"
#include "Main/jkMain.h"
#include "Main/jkRes.h"
#include "General/stdString.h"
#include "General/util.h"
#include "General/stdFnames.h"
#include "stdPlatform.h"

static int jkGuiMain_bIdk = 1;
static int jkGuiCutscenes_initted;

static uint32_t jkGuiMain_listboxIdk[2] = {0xd, 0xe};

static jkGuiElement jkGuiMain_cutscenesElements[5] = {
    {ELEMENT_TEXT, 0, 5, "GUI_VIEWCUTSCENES", 3, {0, 50, 640, 60}, 1, 0, 0, 0, 0, 0, {0}, 0},
    {ELEMENT_LISTBOX, 1, 2, 0, 0, {160, 135, 320, 240}, 1, 0, 0, 0, 0, jkGuiMain_listboxIdk, {0}, 0},
    {ELEMENT_TEXTBUTTON, 1, 2, "GUI_OK", 3, {340, 400, 140, 40}, 1, 0, 0, 0, 0, 0, {0}, 0},
    {ELEMENT_TEXTBUTTON, -1, 2, "GUI_CANCEL", 3, {150, 400, 180, 40}, 1, 0, 0, 0, 0, 0, {0}, 0},
    {ELEMENT_END, 0, 0, 0, 0, {0}, 0, 0, 0, 0, 0, 0, {0}, 0}
};

static jkGuiMenu jkGuiMain_cutscenesMenu = {jkGuiMain_cutscenesElements, 0xFFFFFFFF, 0xFFFF, 0xFFFF, 0xF, 0, 0, jkGui_stdBitmaps, jkGui_stdFonts, 0, 0, "thermloop01.wav", "thrmlpu2.wav", 0, 0, 0, 0, 0, 0};

static jkGuiElement jkGuiMain_elements[8] = {
    {ELEMENT_TEXTBUTTON, 10, 5, "GUI_SINGLEPLAYER", 3, {0, 0xA0, 0x280, 0x3C}, 1, 0, 0, 0, 0, 0, {0}, 0},
    {ELEMENT_TEXTBUTTON, 11, 5, "GUI_MULTIPLAYER", 3, {0, 0xDC, 0x280, 0x3C}, 1, 0, 0, 0, 0, 0, {0}, 0},
    {ELEMENT_TEXTBUTTON, 12, 5, "GUI_QUIT", 3, {0, 0x118, 0x280, 0x3C}, 1, 0, 0, 0, 0, 0, {0}, 0},
    {ELEMENT_TEXTBUTTON, 14, 2, "GUI_CHOOSEPLAYER", 3, {0x14, 0x17C, 0x96, 0x28}, 1, 0, 0, 0, 0, 0, {0}, 0},
    {ELEMENT_TEXTBUTTON, 15, 2, "GUI_VIEWCUTSCENES", 3, {0xFA, 0x17C, 0x96, 0x28}, 1, 0, 0, 0, 0, 0, {0}, 0},
    {ELEMENT_TEXTBUTTON, 13, 2, "GUI_SETUP", 3, {0x1D6, 0x17C, 0x96, 0x28}, 1, 0, 0, 0, 0, 0, {0}, 0},
    {ELEMENT_TEXTBUTTON, 16, 2, "GUI_CREDITS", 3, {0xFA, 0x1A4, 0x96, 0x28}, 1, 0, 0, 0, 0, 0, {0}, 0},
    {ELEMENT_END, 0, 0, 0, 0, {0}, 0, 0, 0, 0, 0, 0, {0}, 0}
};

static jkGuiMenu jkGuiMain_menu = {jkGuiMain_elements, 0xFFFFFFFF, 0xFFFF, 0xFFFF, 0xF, 0, 0, jkGui_stdBitmaps, jkGui_stdFonts, 0, 0, "thermloop01.wav", "thrmlpu2.wav", 0, 0, 0, 0, 0, 0};

void jkGuiMain_Show()
{
    int v1; // esi
    wchar_t *v2; // eax
    wchar_t *v4; // [esp-4h] [ebp-Ch]

    jkGui_SetModeMenu(jkGui_stdBitmaps[0]->palette);
    if ( !jkGuiMain_bIdk || (jkGuiMain_bIdk = 0, jkGuiPlayer_ShowNewPlayer(1), !sithDplay_idk) || jkGuiNet_Show() != 1 )
    {
        do
        {
            jkGuiRend_SetDisplayingStruct(&jkGuiMain_menu, &jkGuiMain_elements[2]);
            v1 = jkGuiRend_DisplayAndReturnClicked(&jkGuiMain_menu);
            switch ( v1 )
            {
                case 10:
                    v1 = jkGuiSingleplayer_Show();
                    break;
                case 11:
                    v1 = jkGuiMultiplayer_Show();
                    break;
                case 12:
                    v4 = jkStrings_GetText("GUI_QUITCONFIRM_Q");
                    v2 = jkStrings_GetText("GUI_QUITCONFIRM");
                    if ( !jkGuiDialog_YesNoDialog(v2, v4) )
                        goto LABEL_12;

                    // TODO proper shutdown?
#ifdef WIN32
                    jk_PostMessageA(stdGdi_GetHwnd(), 16, 0, 0);
#else
                    exit(0);
#endif
                    break;
                case 13:
                    jkGuiSetup_Show();
                    v1 = -1;
                    break;
                case 14:
                    jkGuiPlayer_ShowNewPlayer(0);
LABEL_12:
                    v1 = -1;
                    break;
                case 15:
                    jkMain_SwitchTo12();
                    break;
                case 16:
                    jkMain_SwitchTo13();
                    break;
                default:
                    break;
            }
        }
        while ( v1 == -1 );
    }
    jkGui_SetModeGame();
}

void jkGuiMain_ShowCutscenes()
{
    char *v0; // ebx
    char *v1; // ebp
    char *v2; // edx
    wchar_t *v3; // eax
    int v4; // eax
    const char *v5; // eax
    const char *v6; // eax
    int v7; // esi
    void *i; // eax
    int v9; // [esp+10h] [ebp-15Ch]
    Darray darray; // [esp+14h] [ebp-158h] BYREF
    char v11[64]; // [esp+2Ch] [ebp-140h] BYREF
    char v12[256]; // [esp+6Ch] [ebp-100h] BYREF

    if ( !jkGuiCutscenes_initted )
        jkGui_InitMenu(&jkGuiMain_cutscenesMenu, jkGui_stdBitmaps[3]);
    jkGuiCutscenes_initted = 1;
    jkGui_SetModeMenu(jkGui_stdBitmaps[0]->palette);
    jkGuiRend_DarrayNewStr(&darray, 32, 1);
    if ( !jkPlayer_ReadConf(jkPlayer_playerShortName) )
    {
        stdString_WcharToChar(v11, jkPlayer_playerShortName, 31);
        v11[31] = 0;
        Windows_ErrorMsgboxWide("ERR_CANNOT_SET_PLAYER %s", v11);
    }
    
    jkGuiMain_PopulateCutscenes(&darray, &jkGuiMain_cutscenesElements[1]);
    do
    {
        while ( 1 )
        {
            jkGuiRend_MenuSetLastElement(&jkGuiMain_cutscenesMenu, &jkGuiMain_cutscenesElements[2]);
            jkGuiRend_SetDisplayingStruct(&jkGuiMain_cutscenesMenu, &jkGuiMain_cutscenesElements[3]);
            v4 = jkGuiRend_DisplayAndReturnClicked(&jkGuiMain_cutscenesMenu);
            if ( v4 != 1 )
                break;
            if ( jkRes_LoadCD(jkPlayer_aCutsceneVal[jkGuiMain_cutscenesElements[1].selectedTextEntry]) )
            {
                v5 = (const char *)jkGuiRend_GetId(&darray, jkGuiMain_cutscenesElements[1].selectedTextEntry);
                sprintf(v12, "video%c%s", 92, v5);
                if ( util_FileExists(v12) )
                {
                    jkMain_SwitchTo4(v12);
                    goto LABEL_17;
                }
                v6 = (const char *)jkGuiRend_GetId(&darray, jkGuiMain_cutscenesElements[1].selectedTextEntry);
                stdPrintf(pHS->errorPrint, ".\\Gui\\jkGUIMain.c", 297, "Cannot find cutscene '%s'.\n", v6);
            }
        }
    }
    while ( v4 != -1 );
    jkMain_MenuReturn();
LABEL_17:
    v7 = 0;
    for ( i = (void *)jkGuiRend_GetId(&darray, 0); i; i = (void *)jkGuiRend_GetId(&darray, v7) )
    {
        pHS->free(i);
        ++v7;
    }
    jkGui_SetModeGame();
}

void jkGuiMain_Initialize()
{
    jkGui_InitMenu(&jkGuiMain_menu, jkGui_stdBitmaps[0]);
}

void jkGuiMain_Shutdown()
{
    ;
}

void jkGuiMain_PopulateCutscenes(Darray *list, jkGuiElement *element)
{
    char* v2;
    char *v3; // ebx
    wchar_t *v5; // eax
    int v6; // [esp+4h] [ebp-44h]
    char key[64]; // [esp+8h] [ebp-40h] BYREF

    v6 = 0;
    if ( jkPlayer_setNumCutscenes > 0 )
    {
        v2 = jkPlayer_cutscenePath;
        do
        {
            v3 = _strcpy((char *)pHS->alloc(_strlen(v2) + 1), v2);
            stdFnames_CopyShortName(key, 64, v3); // TODO aaaaaaa ??? disassembly was wrong?
            jkGuiTitle_sub_4189A0(key);
            v5 = jkStrings_GetText2(key);
            jkGuiRend_DarrayReallocStr(list, v5, (int)v3);
            v2 += 32;
            ++v6;
        }
        while ( v6 < jkPlayer_setNumCutscenes );
    }
    jkGuiRend_AddStringEntry(list, 0, 0);
    jkGuiRend_SetClickableString(element, list);
    element->selectedTextEntry = 0;
}

void jkGuiMain_FreeCutscenes(Darray *a1)
{
    int v1; // esi
    void *i; // eax

    v1 = 0;
    for ( i = (void *)jkGuiRend_GetId(a1, 0); i; i = (void *)jkGuiRend_GetId(a1, v1) )
    {
        pHS->free(i);
        ++v1;
    }
}
