/*
   Nintendo Game boy Emulator
   Copyright (C) 2020 Orin
*/

#ifndef COMMONMEMORYRULE_H
#define COMMONMEMORYRULE_H

#include "definitions.h"
#include <vector>

class Memory;
class Cartridge;
class Audio;
class Processor;

class CommonMemoryRule
{
public:
    CommonMemoryRule( Processor* pProcessor, Memory* pMemory,
                    Cartridge* pCartridge, Audio* pAudio);
    virtual ~CommonMemoryRule();
    virtual uint8_t PerformRead(uint16_t addr) = 0;
    virtual void PerformWrite(uint16_t addr, uint8_t value) = 0;
    virtual void Reset(bool bCGB) = 0;
    virtual void SaveRAM(std::ostream &file);
    virtual bool LoadRAM(std::istream &file, int32_t fileSize);
    virtual void SetRamChanged(RamChangedCallback callback);
    virtual size_t GetRamSize();
    virtual size_t GetRTCSize();
    virtual uint8_t* GetRAMBanks();
    virtual uint8_t* GetCurrentRamBank();
    virtual int GetCurrentRAMBankIndex();
    virtual int GetCurrentROMBankIndex();
    virtual uint8_t* GetROMBank0();
    virtual int GetCurrentROMBank0Index();
    virtual uint8_t* GetROMBank1();
    virtual int GetCurrentROMBank1Index();
    virtual uint8_t* GetRTCMemory();
    virtual void SaveState(std::ostream& stream);
    virtual void LoadState(std::istream& stream);

protected:
    Memory* m_pMemory;
    Processor* m_pProcessor;
    Cartridge* m_pCartridge;
    Audio* m_pAudio;
    bool m_bCGB;
    RamChangedCallback m_pRamChangedCallback;
};

#endif