/*
   Nintendo Game boy Emulator
   Copyright (C) 2020 Orin
*/

#ifndef MBC2MEMORY_H
#define MBC2MEMORY_H


#include "MemoryRules.h"

/*
    MBC2 - (max 2MByte ROM and/or 32KByte RAM)
*/
class MBC2Memory : public MemoryRules
{
public:
    MBC2Memory(Processor* pProcessor, Memory* pMemory, 
                Cartridge* pCartridge, Audio* pAudio);
    virtual ~MBC2Memory();
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
    virtual void SaveState(std::ostream &stream);
    virtual void LoadState(std::istream &stream);

private:
    int m_iCurrentROMBank;
    bool m_bRAMEnabled;
    int m_CurrentROMAddr;
};



#endif