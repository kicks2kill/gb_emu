/*
   Nintendo Game boy Emulator
   Copyright (C) 2020 Orin
*/

#include <string>
#include <algorithm>
#include <ctype.h>
#include "Cartridge.h"

Cartridge::Cartridge()
{
    InitPointer(m_ROM);
    m_TotalSize = 0;
    m_szName[0] = 0;
    m_ROMSize = 0;
    m_RAMSize = 0;
    m_Type = CartridgeNotSupported;
    m_bValidROM = false;
    m_bCGB = false;
    m_Version = 0;
    m_bLoaded = false;
    m_RTCCurrentTime = 0;
    m_bBattery = false;
    m_szFilePath[0] = 0;
    m_szFileName[0] = 0;
    m_bRTCPresent = false;
    m_bRumblePresent = false;
    m_RAMBankCount = 0;
    m_ROMBankCount = 0;
}

Cartridge::~Cartridge()
{
    SafeDeleteArray(m_ROM);
}

void Cartridge::Init()
{
    Reset();
}

void Cartridge::Reset()
{
    //TODO
}