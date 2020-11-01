/*
   Nintendo Game boy Emulator
   Copyright (C) 2020 Orin
*/

#ifndef MBC1MEMORY_H
#define MBC1MEMORY_H


#include "MemoryRules.h"

/*
    MBC1 - (max 2MByte ROM and/or 32KByte RAM)
*/
class MBC1Memory : public MemoryRules
{
public:
    MBC1Memory(Processor* pProcessor, Memory* pMemory, 
                Cartridge* pCartridge, Audio* pAudio);
    virtual ~MBC1Memory();
    virtual uint8_t PerformRead(uint16_t address);
    virtual void PerformWrite(uint16_t address, uint8_t value);
    virtual void Reset(bool bCGB);
    virtual void SaveRAM(std::ostream &file);
    virtual bool LoadRAM(std::istream &file);
    virtual size_t GetRAMSize();
    virtual uint8_t* GetRAMBanks();
    virtual uint8_t* GetCurrentRAMBank();
    virtual int GetCurrentRAMBankIndex();
    virtual uint8_t* GetROMBank0();
    virtual int GetCurrentROMBank0Index();
    virtual uint8_t* GetCurrentROMBank1();
    virtual int GetCurrentROMBankIndex();
    virtual void SaveState(std::ostream &stream);
    virtual void LoadState(std::istream &stream);

private:
    int m_iMode;
    int m_iCurrentRAMBank;
    int m_iCurrentROMBank;
    bool m_bRAMEnabled;
    uint8_t m_HigherROMBankBits;
    uint8_t* m_pRAMBanks;
    int m_CurrentROMAddr;
    int m_CurrentRAMAddr;
};



#endif