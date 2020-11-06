/*
   Nintendo Game boy Emulator
   Copyright (C) 2020 Orin
*/

#include "Input.h"
#include "Memory.h"
#include "Processor.h"

Input::Input(Memory* pMemory, Processor* pProcessor)
{
    m_pMemory = pMemory;
    m_pProcessor = pProcessor;
    m_JoypadState = 0xFF;
    m_p1 = 0xFF;
    m_iInputCycles = 0;
}

void Input::Init()
{
    Reset();
}

void Input::Update()
{
    uint8_t current = m_p1 & 0xF0; //240
    
    //I think we need to test if the Hz is below 40?
}