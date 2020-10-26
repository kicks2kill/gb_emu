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

};

#endif