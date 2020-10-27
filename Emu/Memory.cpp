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

void Memory::SetProcessor(Processor* pProcessor)
{
    m_pProcessor = pProcessor;
}