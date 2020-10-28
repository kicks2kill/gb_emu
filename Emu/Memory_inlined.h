/*
   Nintendo Game boy Emulator
   Copyright (C) 2020 Orin
*/


#ifndef MEMORY_INLINED_H
#define MEMORY_INLINED_H

#include "CommonMemoryRule.h"
#include "MemoryRules.h"

inline Memory::stDisassembleRecord* Memory::GetDisassembledMemoryMap()
{
    return m_pDisassembledMap;
}

inline Memory::stDisassembleRecord* Memory::GetDisassembledROMMemoryMap()
{
    return m_pDisassembledROMMap;
}

#endif