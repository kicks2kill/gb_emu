/*
   Nintendo Game boy Emulator
   Copyright (C) 2020 Orin
*/

#include "MBC2Memory.h"
#include "Video.h"
#include "Memory.h"
#include "Processor.h"
#include "Cartridge.h"



MBC2Memory::MBC2Memory(Processor* pProcessor, Memory* pMemory,
                        Cartridge* pCartridge, Audio* pAudio)
                        : MemoryRules(pProcessor, pMemory, pCartridge, pAudio)
{
    Reset(false);
}

MBC2Memory::~MBC2Memory()
{

}

void MBC2Memory::Reset(bool bCGB)
{
    m_bCGB = bCGB;
    m_iCurrentROMBank = 1;
    m_CurrentROMAddr = 0x4000;
    m_bRAMEnabled = false;
}

size_t MBC2Memory::GetRAMSize()
{
    Log("MBC2Memory::GetRamSize not implemented");
    return 0;
}

uint8_t* MBC2Memory::GetRAMBanks()
{
    Log("MBC2Memory::GetRAMBanks not implemented");
    return NULL;
}

uint8_t* MBC2Memory::GetCurrentRAMBank()
{
    Log("MBC2Memory::GetCurrentRamBank not implemented");
    return NULL;
}


int MBC2Memory::GetCurrentRAMBankIndex()
{
    Log("MBC2Memory::GetCurrentRAMBankIndex not implemented");
    return NULL;
}

uint8_t* MBC2Memory::GetROMBank0()
{
    Log("MBC2Memory::GetROMbank0 not implemented");
    return NULL;
}


int MBC2Memory::GetCurrentROMBank0Index()
{
    Log("MBC2Memory::GetROMBank0Index not implemented");
    return 0;
}

uint8_t* MBC2Memory::GetCurrentROMBank1()
{
    Log("MBC2Memory::GetROMBank1 not implemented");
    return NULL;
}

int MBC2Memory::GetCurrentROMBank1Index()
{
    Log("MBC2Memory::GetCurrentROMBank1Index not implemented");
    return 0;
}

