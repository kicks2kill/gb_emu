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

void CommonMemoryRule::SaveState(std::ostream&)
{
    Log("CommonMemoryRule::SaveState not implemented");
}

void CommonMemoryRule::LoadState(std::istream&)
{
    Log("CommonMemoryRule::LoadState not implemented");
}

