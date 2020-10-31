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
class Processor;
class Cartridge;
class Audio;
class MemoryRules
{
public:
   MemoryRules(Processor* pProcessor, Memory* pMemory, Cartridge* pCartridge, Audio* pAudio);
   virtual ~MemoryRules();
   virtual uint8_t PerformRead(uint16_t address);
   virtual void PerformWrite(uint16_t address, uint8_t value);
   virtual void SaveRam(std::ostream &file);
   virtual bool LoadRam(std::istream &file, int32_t fileSize);
   virtual void Reset(bool bCGB);
   virtual size_t GetRamSize();
   virtual size_t GetRTCSize();
   virtual uint8_t* GetRAMBanks();
   virtual void SetRamChanged(RamChangedCallback callback);
   virtual uint8_t* GetCurrentRamBank();
   virtual int GetCurrentRAMBankIndex();
   virtual int GetCurrentROMBankIndex();
   virtual uint8_t* GetROMBank0();
   virtual int GetCurrentROMBank0Index();
   virtual uint8_t* GetROMBank1();
   virtual int GetCurrentROMBank1Index();
   virtual uint8_t* GetRTCMemory();

protected:
   Memory* m_pMemory;
   Processor* m_pProcessor;
   Cartridge* m_pCartridge;
   Audio* m_pAudio;
   bool m_bCGB;
   RamChangedCallback m_pRamChangedCallback;
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
      {
         if(addr < 0xDE00)
         {
            if(m_bCGB)
               m_pMemory->WriteCGBLCDWRAM(addr,value);
            else
               m_pMemory->Load(addr, value);
            m_pMemory->Load(addr + 0x2000, value);
         }
         else if(m_bCGB)
         {
            m_pMemory->WriteCGBLCDWRAM(addr,value);
         }
         else 
         {
            m_pMemory->Load(addr,value);
         }
         break;
      }
      default: 
      {
         Log("**** Writing to invalid area %X %X", addr,value);
         m_pMemory->Load(addr,value);
      }
    }
}
#endif