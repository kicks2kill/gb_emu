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
    SafeDeleteArray(m_ROM);
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
    m_GameGenieList.clear();
}

bool Cartridge::IsValidRom() const 
{
    return m_bValidROM;
}

bool Cartridge::IsLoadedRom() const 
{
    return m_bLoaded;
}

Cartridge::CartridgeTypes Cartridge::GetType() const 
{
    return m_Type;
}

int Cartridge::GetRAMSize() const 
{
    return m_RAMSize;
}

int Cartridge::GetROMSize() const
{
    return m_ROMSize;
}

int Cartridge::GetROMBankCount() const 
{
    return m_ROMBankCount;
}

int Cartridge::GetRAMBankCount() const 
{
    return m_RAMBankCount;
}

const char* Cartridge::GetName() const 
{
    return m_szName;
}

const char* Cartridge::GetFilePath() const
{
    return m_szFilePath;
}

const char* Cartridge::GetFileName() const 
{
    return m_szFileName;
}

int Cartridge::GetTotalSize() const
{
    return m_TotalSize;
}

bool Cartridge::IfBattery() const
{
    return m_bBattery;
}

uint8_t* Cartridge::GetRom() const 
{
    return m_ROM;
}

//Define loadFromZip


bool Cartridge::LoadFromFile(const char* path)
{
    
    Log('Loading %s...', path);

    Reset();

    strcpy(m_szFilePath, path);

    std::string pathstr(path);
    std::string filename;

    size_t pos = pathstr.find_last_of("\\");
    if (pos != std::string::npos)
    {
        filename.assign(pathstr.begin() + pos + 1, pathstr.end());
    }
    else
    {
        pos = pathstr.find_last_of("/");
        if(pos != std::string::npos)
        {
            filename.assign(pathstr.begin() + pos + 1, pathstr.end());
        }
        else 
        {
            filename = pathstr;
        }
    }
    strcpy(m_szFileName, filename.c_str());

    std::ifstream file(path, std::ios::in | std::ios::binary | std::ios::ate);

    //add if logic for if file is open or not... 
    // here
    return m_bLoaded;
}

