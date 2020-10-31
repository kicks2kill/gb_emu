/*
   Nintendo Game boy Emulator
   Copyright (C) 2020 Orin
*/

#ifndef ROM_ONLY_MEMORY_H
#define ROM_ONLY_MEMORY_H

#include "MemoryRules.h"

class RomOnlyMemory : public MemoryRules
{
public:
    RomOnlyMemory(Processor* pProcessor, Memory* pMemory, Cartridge* pCartridge, Audio* pAudio);
    virtual ~RomOnlyMemory();
    virtual uint8_t PerformRead(uint16_t address);
    virtual void PerformWrite(uint16_t address, uint8_t value);
    virtual void Reset(bool bCGB);
    virtual void SaveRAM(std::ostream &file);
    virtual bool LoadRAM(std::istream &file, int32_t fileSize);
    virtual size_t GetRAMSize();
    virtual uint8_t* GetRAMBanks();
    virtual uint8_t* GetCurrentRAMBank();
    virtual int GetCurrentRAMBankIndex();
    virtual uint8_t* GetROMBank0();
    virtual int GetCurrentROMBank0Index();
    virtual uint8_t* GetCurrentROMBank1();
    virtual int GetCurrentROMBank1Index();
};

#endif