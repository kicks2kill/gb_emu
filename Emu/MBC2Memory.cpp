/*
   Nintendo Game boy Emulator
   Copyright (C) 2020 Orin
*/

#include "MBC2Memory.h"
#include "Video.h"
#include "Memory.h"
#include "Processor.h"
#include "Cartridge.h"



MBC2Memory::MBC2Memory(Processor* pProcessor, Memory* pMemory,
                        Cartridge* pCartridge, Audio* pAudio)
                        : MemoryRules(pProcessor, pMemory, pCartridge, pAudio)
{
    Reset(false);
}

MBC2Memory::~MBC2Memory()
{

}

void MBC2Memory::Reset(bool bCGB)
{
    m_bCGB = bCGB;
    m_iCurrentROMBank = 1;
    m_CurrentROMAddr = 0x4000;
    m_bRAMEnabled = false;
}

size_t MBC2Memory::GetRAMSize()
{
    Log("MBC2Memory::GetRamSize not implemented");
    return 0;
}

uint8_t* MBC2Memory::GetRAMBanks()
{
    Log("MBC2Memory::GetRAMBanks not implemented");
    return NULL;
}

uint8_t* MBC2Memory::GetCurrentRAMBank()
{
    Log("MBC2Memory::GetCurrentRamBank not implemented");
    return NULL;
}


int MBC2Memory::GetCurrentRAMBankIndex()
{
    Log("MBC2Memory::GetCurrentRAMBankIndex not implemented");
    return NULL;
}

uint8_t* MBC2Memory::GetROMBank0()
{
    Log("MBC2Memory::GetROMbank0 not implemented");
    return NULL;
}


int MBC2Memory::GetCurrentROMBank0Index()
{
    Log("MBC2Memory::GetROMBank0Index not implemented");
    return 0;
}

uint8_t* MBC2Memory::GetCurrentROMBank1()
{
    Log("MBC2Memory::GetROMBank1 not implemented");
    return NULL;
}

int MBC2Memory::GetCurrentROMBank1Index()
{
    Log("MBC2Memory::GetCurrentROMBank1Index not implemented");
    return 0;
}

void MBC2Memory::SaveRAM(std::ostream& file)
{
    Log("MBC2Memory Saving Ram...");

    for(int i = 0xA000; i < 0xA200; i++) //from 40960 to 41472
    {
        uint8_t ramBytes = m_pMemory->Retrieve(i);
        file.write(reinterpret_cast<const char*>(&ramBytes), 1);
    }
    Log("MBC2Memory save RAM complete");
}

bool MBC2Memory::LoadRAM(std::istream &file, int32_t fileSize)
{
    Log("MBC2Memory Load RAM...");

    if((fileSize > 0) && (fileSize != 512))
    {
        Log("MBC2Memory incorrect Size. Expected: 512 but found %d",fileSize);
        return false;
    }

    for(int i = 0xA000; i < 0xA200; i++) //from 40960 to 41472
    {
        uint8_t ramBytes = 0;
        file.read(reinterpret_cast<char*>(&ramBytes), 1);
        m_pMemory->Load(i, ramBytes);
    }

    Log("MBC2Memory loading RAM complete");
    return true;
}

void MBC2Memory::SaveState(std::ostream& stream)
{
    using namespace std;

    stream.write(reinterpret_cast<const char*> (&m_iCurrentROMBank), sizeof(m_iCurrentROMBank));
    stream.write(reinterpret_cast<const char*> (&m_bRAMEnabled), sizeof(m_bRAMEnabled));
    stream.write(reinterpret_cast<const char*> (&m_CurrentROMAddr), sizeof(m_CurrentROMAddr));
}

void MBC2Memory::LoadState(std::istream& stream)
{
    using namespace std;

    stream.read(reinterpret_cast<char*> (&m_iCurrentROMBank), sizeof(m_iCurrentROMBank));
    stream.read(reinterpret_cast<char*> (&m_bRAMEnabled), sizeof(m_bRAMEnabled));
    stream.read(reinterpret_cast<char*> (&m_CurrentROMAddr), sizeof(m_CurrentROMAddr));
}
