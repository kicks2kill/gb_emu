/*
   Nintendo Game boy Emulator
   Copyright (C) 2020 Orin
*/

#include "MBC1Memory.h"
#include "Video.h"
#include "Memory.h"
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