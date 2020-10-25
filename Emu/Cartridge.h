/*
   Nintendo Game boy Emulator
   Copyright (C) 2020 Orin
*/

#ifndef CARTRIDGE_H
#define CARTRIDGE_H

#include <list>
#include "definitions.h"

class Cartridge {
public:
    enum CartridgeTypes
    {
        CartridgeNoMBC,
        CartridgeMBC1,
        CartridgeMBC2,
        CartridgeMBC3,
        CartridgeMBC5,
        CartridgeMBC1Multi,
        CartridgeNotSupported
    };

    struct GameGenieCode
    {
        int address;
        uint8_t old_value;
    };

public:
    Cartridge();
    ~Cartridge();
    void Init();
    void Reset();
    bool IsValidRom() const;
    bool IsLoadedRom() const;
    CartridgeTypes GetType() const;
    int GetRAMSize() const;
    int GetROMSize() const;
    int GetROMBankCount() const;
    int GetRAMBankCount() const;
    const char* GetName() const;
    const char* GetFilePath() const;
    const char* GetFileName() const;
    int GetTotalSize() const;
    bool IfBattery() const;
    uint8_t* GetRom() const;
    bool LoadFromFile(const char* path);
    bool LoadFromFile(const char* path);
    bool LoadFromBuffer(const uint8_t* buf, int size);
    int GetVersion() const;
    bool IsSGB() const;
    bool IsCGB() const;
    void UpdateCurrentRTC() const;
    long long GetCurrentRTC();
    bool isRTCPresent() const;
    bool IsRumblePresent() const;
    void SetGameGenieCheat(const char* szOfCheat);
    void ClearGameGenie();
private:
    unsigned int PowerCeil(unsigned int n);
    bool GatherMetaData();
    bool LoadFromZip(const uint8_t* buf, int sz);
    void CheckCartridgeType(int type);

private:
    uint8_t* m_ROM;
    int m_TotalSize;
    char m_szName[16];
    int m_ROMSize;
    int m_RAMSize;
    CartridgeTypes m_Type;
    bool m_bValidROM;
    bool m_bCGB;
    bool m_bSGB;
    int m_Version;
    bool m_bLoaded;
    long long m_RTCCurrentTime;
    bool m_bBattery;
    char m_szFilePath[512];
    char m_szFileName[512];
    bool m_bRTCPresent;
    bool m_bRumblePresent;
    int m_RAMBankCount;
    int m_ROMBankCount;
    std::list<GameGenieCode> m_GameGenieList;
};
#endif