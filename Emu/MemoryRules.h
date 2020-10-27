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

inline uint8_t MemoryRules::PerformRead(uint16_t addr)
{
   if(m_bCGB)
   {
      switch(addr & 0xE000)
      {
         case 0x8000:
         {
            return m_pMemory->ReadCGBLCDRAM(addr, false);
         }
         case 0xC000:
         {
            return m_pMemory->ReadCGBWRAM(addr);
         }
      }
   } //I feel like there are some edge cases here. Come back and check
   return m_pMemory->Retrieve(addr);
}

inline void MemoryRules::PerformWrite(uint16_t addr, uint8_t value)
{
   switch( addr & 0xE000)
   {
      case 0x8000:
      {
         if(m_bCGB)
            m_pMemory->WriteCGBLCDRAM(addr, value);
         else
            m_pMemory->Load(addr,value);
      }
      case 0xC000:
         if(addr < 0xDE00)
         {
            if(m_bCGB)
               m_pMemory->WriteCGBLCDWRAM(addr,value);
            else
               m_pMemory->Load(addr, value);
            m_pMemory->Load(addr + 0x2000, value);
         }
         //finish the switch case statement
   }
}

#endif