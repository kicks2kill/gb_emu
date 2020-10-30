/*
   Nintendo Game boy Emulator
   Copyright (C) 2020 Orin
*/

#include "MemoryRules.h"

void MemoryRules::SaveRam(std::ostream&)
{
    Log("MemoryRule::SaveRam not implemented");
}

bool MemoryRules::LoadRam(std::istream&, int32_t)
{
    Log("MemoryRule::LoadRam not implemented");
    return false;
}

void MemoryRules::SetRamChanged(RamChangedCallback callback) 
{
    m_pRamChangedCallback = callback;
}

size_t MemoryRules::GetRamSize()
{
    Log("MemoryRules::GetRamSize not implemented");
    return 0;
}

uint8_t* MemoryRules::GetRAMBanks()
{
    Log("MemoryRules::GetRAMBanks not implemented");
    return NULL;
}

uint8_t* MemoryRules::GetCurrentRamBank()
{
    Log("MemoryRules::GetCurrentRamBank not implemented");
    return NULL;
}


int MemoryRules::GetCurrentRAMBankIndex()
{
    Log("MemoryRules::GetCurrentRAMBankIndex not implemented");
    return NULL;
}

uint8_t* MemoryRules::GetROMBank0()
{
    Log("MemoryRules::GetROMbank0 not implemented");
    return NULL;
}


int MemoryRules::GetCurrentROMBank0Index()
{
    Log("MemoryRules::GetROMBank0Index not implemented");
    return 0;
}

uint8_t* MemoryRules::GetROMBank1()
{
    Log("MemoryRules::GetROMBank1 not implemented");
    return NULL;
}

int MemoryRules::GetCurrentROMBank1Index()
{
    Log("MemoryRules::GetCurrentROMBank1Index not implemented");
    return 0;
}


uint8_t* MemoryRules::GetRTCMemory()
{
    Log("MemoryRule::GetRTCMemory not implemented");
    return NULL;
}

