/*
   Nintendo Game boy Emulator
   Copyright (C) 2020 Orin
*/

#include "MBC1Memory.h"
#include "Video.h"
#include "memory/Memory.h"
#include "Processor.h"
#include "Cartridge.h"

const int MBC1RAMBankSize = 0x8000;

MBC1Memory::MBC1Memory(Processor* pProcessor, Memory* pMemory,
                        Cartridge* pCartridge, Audio* pAudio)
                        : MemoryRules(pProcessor, pMemory, pCartridge, pAudio)
{
    m_pRAMBanks = new uint8_t[MBC1RAMBankSize];
    Reset(false);
}

MBC1Memory::~MBC1Memory()
{
    SafeDeleteArray(m_pRAMBanks);
}

void MBC1Memory::Reset(bool bCGB)
{
    m_bCGB = bCGB;
    m_iMode = 0;
    m_iCurrentRAMBank = 0;
    m_iCurrentROMBank = 1;
    m_HigherROMBankBits = 0;
    m_bRAMEnabled = false;
    for(int i = 0; i < MBC1RAMBankSize; i++)
        m_pRAMBanks[i] = 0xFF;
    m_CurrentROMAddr = 0x4000;
    m_CurrentRAMAddr = 0;
}

void MBC1Memory::SaveRAM(std::ostream& file)
{
    Log("MBC1Memory Saving RAM....");
    Log("Attempting to save %d banks...", m_pCartridge->GetRAMBankCount());

    uint32_t ramSize = m_pCartridge->GetRAMBankCount() * 0x2000; //times 8192

    for( uint32_t i = 0; i < ramSize; i++)
    {
        uint8_t ramBytes = m_pRAMBanks[i];
        file.write(reinterpret_cast<const char*>(&ramBytes),1);
    }

    Log("MBC1Memory save RAM complete");
}

bool MBC1Memory::LoadRAM(std::istream& file, int32_t fileSize)
{
    Log("MBC1Memory Loading RAM....");
    Log("Attempting to load %d banks...", m_pCartridge->GetRAMBankCount());

    int32_t ramSize = m_pCartridge->GetRAMBankCount() * 0x2000;
    if((fileSize > 0) && (fileSize != ramSize))
    {
        Log("MBC1Memory is incorrect size. Expected size %d, but found %d",ramSize, fileSize);
        return false;
    }
    else if(fileSize ==0)
    {
        //There should be some checking here.
    }
    for(int32_t i = 0; i < ramSize; i++)
    {
        uint8_t ramBytes = 0;
        file.read(reinterpret_cast<char*>(&ramBytes),1);
        m_pRAMBanks[i] = ramBytes;
    }
    Log("MBC1Memory loading RAM complete..");
    return true;
}

void MBC1Memory::LoadState(std::istream& stream)
{
    using namespace std;

    stream.read(reinterpret_cast<char*>(&m_iMode), sizeof(m_iMode));
    stream.read(reinterpret_cast<char*>(&m_iCurrentRAMBank), sizeof(m_iCurrentRAMBank));
    stream.read(reinterpret_cast<char*>(&m_iCurrentROMBank), sizeof(m_iCurrentROMBank));
    stream.read(reinterpret_cast<char*>(&m_bRAMEnabled), sizeof(m_bRAMEnabled));
    stream.read(reinterpret_cast<char*>(&m_HigherROMBankBits), sizeof(m_HigherROMBankBits));
    stream.read(reinterpret_cast<char*>(&m_pRAMBanks), sizeof(m_pRAMBanks));
    stream.read(reinterpret_cast<char*>(&m_CurrentROMAddr), sizeof(m_CurrentROMAddr));
    stream.read(reinterpret_cast<char*>(&m_CurrentRAMAddr), sizeof(m_CurrentRAMAddr));
}


void MBC1Memory::SaveState(std::ostream& stream)
{
     using namespace std;

    stream.write(reinterpret_cast<const char*>(&m_iMode), sizeof(m_iMode));
    stream.write(reinterpret_cast<const char*>(&m_iCurrentRAMBank), sizeof(m_iCurrentRAMBank));
    stream.write(reinterpret_cast<const char*>(&m_iCurrentROMBank), sizeof(m_iCurrentROMBank));
    stream.write(reinterpret_cast<const char*>(&m_bRAMEnabled), sizeof(m_bRAMEnabled));
    stream.write(reinterpret_cast<const char*>(&m_HigherROMBankBits), sizeof(m_HigherROMBankBits));
    stream.write(reinterpret_cast<const char*>(&m_pRAMBanks), sizeof(m_pRAMBanks));
    stream.write(reinterpret_cast<const char*>(&m_CurrentROMAddr), sizeof(m_CurrentROMAddr));
    stream.write(reinterpret_cast<const char*>(&m_CurrentRAMAddr), sizeof(m_CurrentRAMAddr));
}

size_t MBC1Memory::GetRAMSize()
{
    Log("MBC1Memory::GetRamSize not implemented");
    return 0;
}

uint8_t* MBC1Memory::GetRAMBanks()
{
    Log("MBC1Memory::GetRAMBanks not implemented");
    return NULL;
}

uint8_t* MBC1Memory::GetCurrentRAMBank()
{
    Log("MBC1Memory::GetCurrentRamBank not implemented");
    return NULL;
}


int MBC1Memory::GetCurrentRAMBankIndex()
{
    Log("MBC1Memory::GetCurrentRAMBankIndex not implemented");
    return NULL;
}

uint8_t* MBC1Memory::GetROMBank0()
{
    Log("MBC1Memory::GetROMbank0 not implemented");
    return NULL;
}


int MBC1Memory::GetCurrentROMBank0Index()
{
    Log("MBC1Memory::GetROMBank0Index not implemented");
    return 0;
}

uint8_t* MBC1Memory::GetCurrentROMBank1()
{
    Log("MBC1Memory::GetROMBank1 not implemented");
    return NULL;
}

int MBC1Memory::GetCurrentROMBank1Index()
{
    Log("MBC1Memory::GetCurrentROMBank1Index not implemented");
    return 0;
}

