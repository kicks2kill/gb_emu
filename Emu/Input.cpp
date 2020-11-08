/*
   Nintendo Game boy Emulator
   Copyright (C) 2020 Orin
*/

#include "Input.h"
#include "memory/Memory.h"
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
    
    switch(current & 0x30)
    {
        case 0x10:
        {
            uint8_t joypadTop = (m_JoypadState >> 4) & 0x0F;
            current |= joypadTop;
            break;
        }
        case 0x20:
        {
            uint8_t joypadBottom = m_JoypadState & 0x0F;
            current |= joypadBottom;
            break;
        }
        case 0x30:
        {
            current |= 0x0F;
            break;
        }
    }
    m_p1 = current;
}

void Input::KeyPressed(Gameboy_Keys key)
{
    m_JoypadState = UnsetBit(m_JoypadState, key);
}

void Input::KeyReleased(Gameboy_Keys key)
{
    m_JoypadState = SetBit(m_JoypadState, key);
}



void Input::SaveState(std::ostream &stream)
{
    using namespace std;

    stream.write(reinterpret_cast<const char*> (&m_JoypadState), sizeof(m_JoypadState));
    stream.write(reinterpret_cast<const char*> (&m_p1), sizeof(m_p1));
    stream.write(reinterpret_cast<const char*> (&m_iInputCycles), sizeof(m_iInputCycles));
}

void Input::LoadState(std::istream &stream)
{
    using namespace std;

    stream.read(reinterpret_cast<char*> (&m_JoypadState), sizeof(m_JoypadState));
    stream.read(reinterpret_cast<char*> (&m_p1), sizeof(m_p1));
    stream.read(reinterpret_cast<char*> (&m_iInputCycles), sizeof(m_iInputCycles));
}
