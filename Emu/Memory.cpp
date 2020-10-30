/*
   Nintendo Game boy Emulator
   Copyright (C) 2020 Orin
*/

#include <iostream>
#include <fstream>
#include "Memory.h"
#include "Processor.h"
#include "Video.h"

Memory::Memory()
{
    InitPointer(m_pProcessor);
    //TODO
}

void Memory::Init()
{
    m_pMap = new uint8_t[65536];
    m_pWRAMBanks = new uint8_t[0x8000];
    m_pLCDRAMBank1 = new uint8_t[0x2000];
    m_pDisassembledMap = new stDisassembleRecord[65536];
    m_pDisassembledROMMap = new stDisassembleRecord[MAX_ROM_SIZE];
    m_BreakpointsInMap.clear();
    InitPointer(m_pRunToBreakpoint);
    Reset(false);
}

void Memory::Reset(bool bCGB)
{
    m_bCGB = bCGB;
    InitPointer(m_pCommonMemoryRule);
    InitPointer(m_pCurrentMemoryRule);
    m_iCurrentWRAMBank = 1;
    m_iCurrentLCDRAMBank = 0;

    for (int i = 0; i < MAX_ROM_SIZE; i++)
    {
        m_pDisassembledROMMap[i].address = i & 0x3FFF;
        m_pDisassembledROMMap[i].bank = i >> 14;
        m_pDisassembledROMMap[i].name[0] = 0;
        m_pDisassembledROMMap[i].bytes[0] = 0;
        m_pDisassembledROMMap[i].sz = 0;
    }

    for( int i = 0; i < 65536; i++)
    {
        m_pMap[i] = 0x00;
        m_pDisassembledMap[i].address = 0;
        m_pDisassembledMap[i].bank = 0;
        m_pDisassembledMap[i].name[0] = 0;
        m_pDisassembledMap[i].bytes[0] = 0;
        m_pDisassembledMap[i].sz = 0;

        //if i >= and < ... ?
    }
    if(m_bCGB)
    {
        //HDMA stuff?
    }

}

void Memory::SetProcessor(Processor* pProcessor)
{
    m_pProcessor = pProcessor;
}

void Memory::MemoryDump(const char* szFilePath)
{
    std::ofstream myFile(szFilePath, std::ios::out | std::ios::trunc);

    if(myFile.is_open())
    {
        for(int i = 0; i < 65536; i++)
        {
            if(m_pDisassembledMap[i].name[0] != 0)
            {
                myFile << "0x" << std::hex << i << "\t" << m_pDisassembledMap[i].name << std::endl;
                i += (m_pDisassembledMap[i].sz - 1);
            }
            else 
            {
                myFile << "0x" << std::hex << i << "\t [0x" << std::hex << (int)m_pMap[i] << "]" << std::endl;
            }
        }
        myFile.close();
    }
}

uint8_t* Memory::GetROM0()
{
    return m_pCurrentMemoryRule->GetROMBank0();
}

uint8_t* Memory::GetROM1()
{
    return m_pCurrentMemoryRule->GetROMBank1();
}

uint8_t* Memory::GetVRAM()
{
    if(m_bCGB)
        return (m_iCurrentLCDRAMBank == 1) ? m_pLCDRAMBank1 : m_pMap + 0x8000;
    else
        return m_pMap + 0x8000;
}

uint8_t* Memory::GetRAM()
{
    return m_pCurrentMemoryRule->GetCurrentRamBank();
}

uint8_t* Memory::GetWRAM0()
{
    return m_bCGB ? m_pWRAMBanks : m_pMap + 0xC000;
}

uint8_t* Memory::GetWRAM1()
{
    return m_bCGB ? m_pWRAMBanks + (0x1000 * m_iCurrentWRAMBank) : m_pMap + 0xD000;
}

std::vector<Memory::stDisassembleRecord*>* Memory::GetBreakpoints()
{
    return &m_BreakpointsInMap;
}

Memory::stDisassembleRecord* Memory::GetRunToBreakpoint()
{
    return m_pRunToBreakpoint;
}

void Memory::SetRunToBreakpoint(Memory::stDisassembleRecord* pBreakpoint)
{
    m_pRunToBreakpoint = pBreakpoint;
}
