/*
   Nintendo Game boy Emulator
   Copyright (C) 2020 Orin
*/

#ifndef INPUT_H
#define INPUT_H

#include "definitions.h"

class Memory;
class Processor;

class Input
{
public:
    Input(Memory* pMemory, Processor* pProcessor);
    void Init();
    void Reset();
    void Tick(unsigned int clockCycles);
    void Write(uint8_t value);
    uint8_t Read();
    void KeyPressed(Gameboy_Keys key);
    void KeyReleased(Gameboy_Keys key);
    void SaveState(std::ostream &stream);
    void LoadState(std::ostream &stream);

private:
    Memory* m_pMemory;
    Processor* m_pProcessor;
    uint8_t m_JoypadState;
    uint8_t m_p1;
    int m_iInputCycles;
    void Update();

};

inline uint8_t Input::Read()
{
    return m_p1;
}

inline void Input::Write(uint8_t value)
{
    m_p1 = (m_p1 & 0xCF) | (value & 0x30); //bitwise AND by 207 or the value by 48
    Update(); //write this
}


inline void Input::Tick(unsigned int clockCycles)
{   //Joypad poll speed is 64Hz
    m_iInputCycles += clockCycles;

    if(m_iInputCycles >= 65536)
    {
        m_iInputCycles -= 65536;
        Update();
    }
}
#endif