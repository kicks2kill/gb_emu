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

        if((i >= 0x8000) && (i < 0xA000)) //32768 and 40960
        {
            m_pMap[i] = 0x00;
            m_pLCDRAMBank1[i - 0x8000] = 0x00;
        }
        else if((i >= 0xC000) && (i < 0xE000))  //49152 and 57344
        { 
            //perform some check here
        }
    }
    if(m_bCGB)
    {
       for(int i =0; i < 5; i++)
       {
           m_HDMA[i] = m_pMap[0xFF51 + i];
       }
       uint8_t hdma1 = m_HDMA[0];
       uint8_t hdma2 = m_HDMA[1];
       uint8_t hdma3 = m_HDMA[2];
       uint8_t hdma4 = m_HDMA[3];

       if(hdma1 > 0x7f && hdma1 < 0xF0) //127 and less than 240
            hdma1 = 0;

        m_HDMASource = (hdma1 << 8) | (hdma2 & 0xF0);
        m_HDMADest = ((hdma3 & 0x1F) << 8) | (hdma4 & 0xF0); //31 bit shifted by 8, or ANDd by 240
        m_HDMADest |= 0x8000; //32768
    }

}

void Memory::SetProcessor(Processor* pProcessor)
{
    m_pProcessor = pProcessor;
}

void Memory::SetVideo(Video* pVideo)
{
    m_pVideo = pVideo;
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

void Memory::MemoryDump(const char* szFilePath)
{
    using namespace std;

    ofstream myFile(szFilePath, ios::out | ios::trunc);

    if(myFile.is_open())
    {
        for(int i = 0; i < 65536; i++)
        {
            if(m_pDisassembledMap[i].name[0] != 0)
            {
                myFile << "0x" << hex << i << "\t " << m_pDisassembledMap[i].name << "\n";
                i += (m_pDisassembledMap[i].sz -1);
            }
            else 
            {
                myFile << "0x"<< hex << i << "\t [0x" << hex << (int)m_pMap[i] << "]\n";
            }
        }
        myFile.close();
    }
}

void Memory::LoadBank0and1FromROM(uint8_t* pTheROM)
{
    //load in the first 32kB only. 
    for(int i =0; i < 0x8000; i++)
    {
        m_pMap[i] = pTheROM[i];
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
