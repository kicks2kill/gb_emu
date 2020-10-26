/*
   Nintendo Game boy Emulator
   Copyright (C) 2020 Orin
*/

#ifndef MEMORY_H
#define MEMORY_H

#include "definitions.h"
#include "MemoryRules.h"
#include <vector>

class Processor;
class MemoryRule;

class Memory
{
public:
    struct stDisassembleRecord
    {
        uint16_t address;
        char name[32];
        char bytes[16];
        int sz;
        int bank;
    };

public:
    Memory();
    ~Memory();
    // void SetProcessor(Processor* pProcessor);
    // void SetVideo(Video* pVideo);
    void Init();
    void Reset(bool bCGB);
    void SetCurrentRule(MemoryRules* pRule);
    void SetCommonRule(CommonMemoryRule* pRule);
    // void SetIORule(IORegisterMemoryRule* pRule);
    MemoryRules* GetCurrentRule();
    uint8_t* GetMemoryMap();
    uint8_t Read(uint16_t addr);
    void Write(uint16_t addr, uint8_t value);
    void MemoryDump(const char* szFilePath);
    void Load(uint16_t addr, uint8_t value);

private:
    Processor* m_pProcessor;
    // Video* m_pVideo;
    CommonMemoryRule* m_pCommonMemoryRule;
    // IORegisterMemoryRule* m_pIORegisterMemoryRule;
    MemoryRule* m_pCurrentMemoryRule;
    uint8_t* m_pMap;
    stDisassembleRecord* m_pDisassembledMap;
    stDiassessembleRecord* m_pDiassembledROMMap;
    std::vector<stDiassembleRecord*> m_BreakpointsInMap;
    stDiassembleRecord* m_pRunToBreakpoint;
    bool m_bCGB;
    int m_iCurrentWRAMBank;
    int m_iCurrentLCDRAMBank;
    uint8_t* m_pWRAMBanks;
    uint8_t* m_pLCDRAMBank1;
};

#endif