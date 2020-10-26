/*
   Nintendo Game boy Emulator
   Copyright (C) 2020 Orin
*/

#include <algorithm>
#include <ctype.h>
#include "Processor.h"
#include "opcode_names.h"
#include "opcode_timing.h"

Processor::Processor(Memory* pMemory)
{
    m_pMemory = pMemory;
    // m_pMemory->SetProcessor(this);
    // InitOPCodeFunctors();

}