/*
   Nintendo Game boy Emulator
   Copyright (C) 2020 Orin
*/

#include "RomOnlyMemory.h"
#include "video.h"
#include "Memory.h"
#include "Processor.h"
#include "Cartridge.h"
// #include "Input.h"

RomOnlyMemory::RomOnlyMemory(Processor* pProcessor, Memory* pMemory, Cartridge* pCartridge, Audio* pAudio)
    : MemoryRules(pProcessor, pMemory, pCartridge, pAudio)
    {
        Reset(false);
    }

RomOnlyMemory::~RomOnlyMemory()
{

}

void RomOnlyMemory::Reset(bool bCGB)
{
    m_bCGB = bCGB;
}

uint8_t RomOnlyMemory::PerformRead(uint16_t address)
{
    if (address >= 0xA000 && address < 0xC000)
    {
        if(m_pCartridge->GetRAMSize() > 0)
            return m_pMemory->Retrieve(address);
        else
        {
            Log("**** -- Please add ram to cart. Attempting to read from RAM without ram in cart %X", address);
            return 0xFF;
        }
    }
    else
        return m_pMemory->Retrieve(address);
}

void RomOnlyMemory::PerformWrite(uint16_t address, uint8_t value)
{
    if (address < 0x8000)
    {
        //ROM address 
        Log("**** -- Attempting to write on ROM address %X %X", address, value);
    }
    else if(address > 0xA000 && address < 0xC000)
    {
        if(m_pCartridge->GetRAMSize() > 0)
        {
            m_pMemory->Load(address,value);
        }
        else
        {
            Log("**** -- Please add ram to cart. Attempting to read from RAM without ram in cart %X %X", address, value);
        }
    }
    else
        m_pMemory->Load(address,value);
}


void RomOnlyMemory::SaveRAM(std::ostream &file)
{
    Log("RomOnlyMemory saving RAM....");

    for(int i = 0xA000; i < 0xC000; i++)
    {
        uint8_t ram_bytes = m_pMemory->Retrieve(i);
        file.write(reinterpret_cast<const char*> (&ram_bytes), 1);
    }
    Log("RomOnlyMemory RAM save complete");
}

bool RomOnlyMemory::LoadRAM(std::istream &file, int32_t fileSize)
{
    Log("RomOnlyMemory loading RAM....");

    if((fileSize > 0) && (fileSize != 0x2000))
    {
        Log("RomOnlyMemory is incorrect size. Expected: %d but found %d", 0x2000, fileSize);
        return false;
    }
    for(int i = 0xA000; i < 0xC000; i++)
    {
        uint8_t ram_bytes = 0;
        file.read(reinterpret_cast<char*>(&ram_bytes), 1);
        m_pMemory->Load(i, ram_bytes);
    }
    Log("RomOnlyMemory Loading RAM complete");
    
    return true;
}

size_t RomOnlyMemory::GetRAMSize()
{
    return m_pCartridge->GetRAMBankCount() * 0x2000;
}

uint8_t* RomOnlyMemory::GetRAMBanks()
{
    return m_pMemory->GetMemoryMap() + 0xA000;
}

uint8_t* RomOnlyMemory::GetCurrentRAMBank()
{
    return m_pMemory->GetMemoryMap() + 0xA000;
}

int RomOnlyMemory::GetCurrentRAMBankIndex()
{
    return 0;
}
uint8_t* RomOnlyMemory::GetROMBank0()
{
    return m_pMemory->GetMemoryMap() + 0x0000;
}

int RomOnlyMemory::GetCurrentROMBank0Index()
{
    return 0;
}

uint8_t* RomOnlyMemory::GetCurrentROMBank1()
{
    return m_pMemory->GetMemoryMap() + 0x4000;
}

int RomOnlyMemory::GetCurrentROMBank1Index()
{
    return 0;
}
