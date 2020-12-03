/*
   Nintendo Game boy Emulator
   Copyright (C) 2020 Orin
*/

#include "Core.h"
#include "Memory.h"
#include "Processor.h"
#include "Cartridge.h"
#include "Audio.h"
#include "Video.h"
#include "Input.h"
#include "definitions.h"
#include "../memory/Memory.h"
#include "../memory/CommonMemoryRule.h"
#include "../memory/IORegisters.h"
#include "../memory/RomOnlyMemory.h"
#include "../memory/MBC1Memory.h"
#include "../memory/MBC2Memory.h"

Core::Core()
{
    InitPointer(m_pMemory);
    InitPointer(m_pCartridge);
    InitPointer(m_pProcessor);
    InitPointer(m_pAudio);
    InitPointer(m_pVideo);
}