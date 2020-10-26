/*
   Nintendo Game boy Emulator
   Copyright (C) 2020 Orin
*/

#ifndef MEMORYRULES_H
#define MEMORYRULES_H

#include "definitions.h"
#include "Memory.h"
#include <vector>

class Memory;

class MemoryRules
{
public:
   MemoryRules(Memory* pMemory);
   virtual ~MemoryRules();
   virtual uint8_t PerformRead(uint16_t address);
   virtual void PerformWrite(uint16_t address, uint8_t value);
   virtual void Reset(bool bCGB);

private:
   Memory* m_pMemory;
   bool m_bCGB;
};





#endif