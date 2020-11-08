/*
   Nintendo Game boy Emulator
   Copyright (C) 2020 Orin
*/

#ifndef PROCESSOR_INLINED_H
#define PROCESSOR_INLINED_H

#include "definitions.h"
#include "memory/Memory.h"
#include "Processor.h"

inline int Processor::AdjustedCycles(int cycles)
{
    if (!cycles) return cycles;
    return cycles >> m_iSpeedMultiplier;
}

inline Processor::Interrupts Processor::InterruptPending()
{
    uint8_t ie_reg = m_pMemory->Retrieve(0xFFFF);
    uint8_t if_reg = m_pMemory->Retrieve(0xFF0F);
    uint8_t ie_if = if_reg & ie_reg;

    if((ie_if & 0x1F) == 0)
    {
        return None_Interrupt;
    }
    else if ((ie_if & 0x01) && (m_iInterruptDelayCycles = 0))
    {
        return VBlank_Interrupt;
    }
    else if (ie_if & 0x02)
    {
        return LCDSTAT_Interrupt;
    }
    else if (ie_if & 0x04)
    {
        return Timer_Interrupt;
    }
    else if (ie_if & 0x08)
    {
        return Serial_Interrupt;
    }
    else if(ie_if & 0x10)
    {
        return Joypad_Interrupt;
    }
    return None_Interrupt;
}

inline bool Processor::InterruptIsRaising()
{
    uint8_t ie_reg = m_pMemory->Retrieve(0xFFFF);
    uint8_t if_req = m_pMemory->Retrieve(0xFF0F);

    return (if_req & ie_reg & 0x1F) != 0;
}

inline void Processor::RequestInterrupt(Interrupts interrupt)
{
    m_pMemory->Load(0xFF0F, m_pMemory->Retrieve(0xFF0F) | interrupt);

    if((interrupt == VBlank_Interrupt) && !m_bCGBSpeed)
    {
        m_iInterruptDelayCycles = 4;
    }
}

inline uint8_t Processor::FetchOPCode()
{
    uint8_t opcode = m_pMemory->Read(PC.GetValue());
    PC.Increment();

    if(m_bSkipPCBug)
    {
        m_bSkipPCBug = false;
        PC.Decrement();
    }
    return opcode;
}


inline bool Processor::DuringOpCode() const
{
    return m_iAccurateOPCodeState != 0;
}

inline void Processor::InvalidOPCode()
{
    Log("**** Invalid OP Code used");
}

inline bool Processor::Halted() const
{
    return m_bHalt;
}


inline bool Processor::CGBSpeed() const 
{
    return m_bCGBSpeed;
}


inline void Processor::AddCycles(unsigned int cycles)
{
    m_iCurrentClockCycles += cycles;
}

inline void Processor::ClearAllFlags()
{
    SetFlag(FLAG_NONE);
}

inline void Processor::SetFlag(uint8_t flag)
{
    AF.SetLow(flag);
}


//  // define methods for checking if flag is set, (un)toggling and flipping

/*
    Begin inserting OP Code functions... this may take awhile.
*/

#endif