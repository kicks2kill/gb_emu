/*
   Nintendo Game boy Emulator
   Copyright (C) 2020 Orin
*/

#include "RomOnlyMemory.h"
#include "video.h"
#include "Memory.h"
#include "Processor.h"
#include "Cartridge.h"
// #include "Input.h"

RomOnlyMemory::RomOnlyMemory(Processor* pProcessor, Memory* pMemory, Cartridge* pCartridge, Audio* pAudio)
    : MemoryRules(pProcessor, pMemory, pCartridge, pAudio)
    {
        Reset(false);
    }

RomOnlyMemory::~RomOnlyMemory()
{

}

void RomOnlyMemory::Reset(bool bCGB)
{
    m_bCGB = bCGB;
}

