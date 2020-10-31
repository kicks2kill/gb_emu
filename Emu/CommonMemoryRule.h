/*
   Nintendo Game boy Emulator
   Copyright (C) 2020 Orin
*/

#ifndef COMMONMEMORYRULE_H
#define COMMONMEMORYRULE_H

#include "definitions.h"
#include <vector>

class Memory;

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
    virtual void SaveState(std::ostream& stream);
    virtual void LoadState(std::istream& stream);

protected:
    Memory* m_pMemory;
    bool m_bCGB;
    RamChangedCallback m_pRamChangedCallback;
};



inline uint8_t CommonMemoryRule::PerformRead(uint16_t address)
{
    if(m_bCGB)
    {
        switch(address & 0xE000)
        {
            case 0x8000:
            {
                return m_pMemory->ReadCGBLCDRAM(address,false);
            }
            case 0xC000:
            {
                return m_pMemory->ReadCGBWRAM(address);
            }
        }
    }
    else if(address >= 0xFEA0 && address < 0xFF00)
    {
        return (((address + ((address >> 4) - 0x0FEA)) >> 2) & 1) ? 0x00 : 0xFF);
    }
    return m_pMemory->Retrieve(address);
}
//  // work on this method
inline void CommonMemoryRule::PerformWrite(uint16_t address, uint8_t value)
{
    switch(address & 0xE000)
    {
        case 0x8000:
        {
            if(m_bCGB)
                m_pMemory->WriteCGBLCDRAM(address,value);
            else
                m_pMemory->Load(address, value);
            break;
        }
        case 0xC000:
        {
            if(address < 0xDE00)
            {
                if(m_bCGB)
                    m_pMemory->WriteCGBLCDRAM(address,value);
                else
                    m_pMemory->Load(address, value);
                m_pMemory->Load(address + 0x2000, value);
            }
            else if(m_bCGB)
            {   //define this
                //m_pMemory->WriteCGBWRAM(address,value);
            }
            else
            {
                m_pMemory->Load(address,value);
            }
            break;
        }
    }
}
#endif