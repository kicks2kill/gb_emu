/*
   Nintendo Game boy Emulator
   Copyright (C) 2020 Orin
*/


#ifndef MEMORY_INLINED_H
#define MEMORY_INLINED_H

#include "CommonMemoryRule.h"
#include "MemoryRules.h"

inline uint8_t Memory::Read(uint16_t address)
{
    switch (address & 0xE000)
    {
        case 0x0000:
        case 0x2000:
        case 0x4000:
        case 0x6000:
        {
            return m_pCurrentMemoryRule->PerformRead(address);
        }
        case 0x8000:
        {
            return m_pCommonMemoryRule->PerformRead(address);
        }
        case 0xA000:
        {
            return m_pCurrentMemoryRule->PerformRead(address);
        }
        case 0xC0000:
        case 0xE0000:
        {
            if(address < 0xFF00)
                return m_pCommonMemoryRule->PerformRead(address);
            // else
                // return m_pIORegistersMemoryRule->PerformRead(address);
        }
        default:
            return Retrieve(address);

    }
}

inline void Memory::Write(uint16_t address, uint8_t value)
{
    switch(address & 0xE000)
    {
        case 0x0000:
        case 0x2000:
        case 0x4000:
        case 0x6000:
        {
            return m_pCurrentMemoryRule->PerformWrite(address,value);
        }
        case 0x8000:
        {
            return m_pCommonMemoryRule->PerformWrite(address,value);
        }
        case 0xA000:
        {
            return m_pCurrentMemoryRule->PerformWrite(address,value);
        }
        case 0xC0000:
        case 0xE0000:
        {
            if(address < 0xFF00)
                return m_pCommonMemoryRule->PerformWrite(address,value);
            // else
                // return m_pIORegistersMemoryRule->PerformRead(address);
        }
        default:
        {
            Load(address,value);
            break;
        }
    }
}

inline void Memory::WriteCGBWRAM(uint16_t address, uint8_t value)
{
    if(address < 0xD000)
        m_pWRAMBanks[(address - 0xC000)] = value;
    else
        m_pWRAMBanks[(address - 0xD000) + (0x1000 * m_iCurrentWRAMBank)] = value;
}

inline uint8_t Memory::ReadCGBWRAM(uint16_t address)
{
     if(address < 0xD000)
        return m_pWRAMBanks[(address - 0xC000)];
    else
        return m_pWRAMBanks[(address - 0xD000) + (0x1000 * m_iCurrentWRAMBank)];
}


inline Memory::stDisassembleRecord* Memory::GetDisassembledMemoryMap()
{
    return m_pDisassembledMap;
}

inline Memory::stDisassembleRecord* Memory::GetDisassembledROMMemoryMap()
{
    return m_pDisassembledROMMap;
}

inline uint8_t Memory::Retrieve(uint16_t address)
{
    return m_pMap[address];
}

inline void Memory::Load(uint16_t address, uint8_t value)
{
    m_pMap[address] = value;
}

#endif