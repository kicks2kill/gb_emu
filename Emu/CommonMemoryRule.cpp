/*
   Nintendo Game boy Emulator
   Copyright (C) 2020 Orin
*/

#include "CommonMemoryRule.h"
    //  // This needs to reference Video and input as well once created
CommonMemoryRule::CommonMemoryRule(Processor* pProcessor, Memory* pMemory, Cartridge* pCartridge, Audio* pAudio)
{
    m_pProcessor = pProcessor;
    m_pMemory = pMemory;
    m_pCartridge = pCartridge;
    m_pAudio = pAudio;
    m_bCGB = false;
    InitPointer(m_pRamChangedCallback);
}

CommonMemoryRule::~CommonMemoryRule()
{

}

void CommonMemoryRule::SaveRAM(std::ostream&)
{
    Log("CommonMemoryRule::SaveRAM not implemented");
}


bool CommonMemoryRule::LoadRAM(std::istream&, int32_t)
{
    Log("CommonMemoryRule::SaveRAM not implemented");
    return false;
}

void CommonMemoryRule::SetRamChanged(RamChangedCallback callback)
{
    m_pRamChangedCallback = callback;
}

size_t CommonMemoryRule::GetRamSize()
{
    Log("CommonMemoryRule::GetRamSize not implemented");
    return 0;
}

uint8_t* CommonMemoryRule::GetRAMBanks()
{
    Log("CommonMemoryRule::GetRAMBanks not implemented");
    return NULL;
}

uint8_t* CommonMemoryRule::GetCurrentRamBank()
{
    Log("CommonMemoryRule::GetCurrentRamBank not implemented");
    return NULL;
}


int CommonMemoryRule::GetCurrentRAMBankIndex()
{
    Log("CommonMemoryRule::GetCurrentRAMBankIndex not implemented");
    return NULL;
}

uint8_t* CommonMemoryRule::GetROMBank0()
{
    Log("CommonMemoryRule::GetROMbank0 not implemented");
    return NULL;
}


int CommonMemoryRule::GetCurrentROMBank0Index()
{
    Log("CommonMemoryRule::GetROMBank0Index not implemented");
    return 0;
}

uint8_t* CommonMemoryRule::GetROMBank1()
{
    Log("CommonMemoryRule::GetROMBank1 not implemented");
    return NULL;
}

int CommonMemoryRule::GetCurrentROMBank1Index()
{
    Log("CommonMemoryRule::GetCurrentROMBank1Index not implemented");
    return 0;
}


uint8_t* CommonMemoryRule::GetRTCMemory()
{
    Log("MemoryRule::GetRTCMemory not implemented");
    return NULL;
}


void CommonMemoryRule::SaveState(std::ostream&)
{
    Log("CommonMemoryRule::SaveState not implemented");
}

void CommonMemoryRule::LoadState(std::istream&)
{
    Log("CommonMemoryRule::LoadState not implemented");
}
