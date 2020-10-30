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
        //reset ROMMAP data 
    }

}

void Memory::SetProcessor(Processor* pProcessor)
{
    m_pProcessor = pProcessor;
}

uint8_t* Memory::GetRAM()
{
    return m_pCurrentMemoryRule->GetCurrentRamBank();
}

std::vector<Memory::stDisassembleRecord*>* Memory::GetBreakpoints()
{
    return &m_BreakpointsInMap;
}

Memory::stDisassembleRecord* Memory::GetRunToBreakpoint()
{
    return m_pRunToBreakpoint;
}

