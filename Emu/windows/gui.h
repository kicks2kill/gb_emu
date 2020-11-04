/*
   Nintendo Game boy Emulator
   Copyright (C) 2020 Orin
*/


#ifndef GUI_H
#define GUI_H
#include "./imgui/imgui.h"

enum guiShortCutEvents
{
    guiSCOpenROM = 0,
    guiSCReset,
    guiSCPause,
    guiSCFFWD,
    guiSCSaveState,
    guiSCLoadState,
    guiSCDebugStep,
    guiSCDebugContinue,
    guiSCDebugNext,
    guiSCDebugBreak,
    guiSCDebugRunToCursor
};

bool guiUsed;
ImFont* guiDefaultFont;
ImFont* guiRobotoFont;

void guiInit(void);
void guiDestroy(void);
void guiRender(void);
void guiShortcut(guiShortCutEvents event);
void guiLoadRom(const char* path);


#endif