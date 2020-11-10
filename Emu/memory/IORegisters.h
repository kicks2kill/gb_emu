/*
   Nintendo Game boy Emulator
   Copyright (C) 2020 Orin
*/

#ifndef IOREGISTERS_H
#define IOREGISTERS_H

#include "definitions.h"
#include "Processor.h"
#include "Input.h"
#include "Audio.h"
#include "memory/Memory.h"
#include "Video.h"

class Processor;
class Input;
class Audio;
class Memory;
class Video;


class IORegisters
{
public:
    IORegisters(Processor* pProcessor, Memory* pMemory, Video* pVideo, Input* pInput, Audio* pAudio);
    virtual ~IORegisters();
    virtual void Reset(bool bCGB);
    virtual void PerformWrite(uint16_t address, uint8_t value);
    virtual uint8_t PerformRead(uint16_t address);

private:
    Processor* m_pProcessor;
    Memory* m_pMemory;
    Video* m_pVideo;
    Input* m_pInput;
    Audio* m_pAudio;
    bool m_bCGB;
};

inline uint8_t IORegisters::PerformRead(uint16_t addr)
{
    switch(addr)
    {
        case 0xFF00:
        {
            //P1
            return m_pInput->Read();
        }
        case 0xFF07:
        {
            //TAC
            return m_pMemory->Retrieve(0xFF07) | 0xF8;
        }
        case 0xFF0F:
        {
            //IF
            return m_pMemory->Retrieve(0xFF0F) | 0xE0;
        }
        case 0xFF3F:
        {
            //SOUND REG
            return m_pAudio->ReadAudioRegister(addr);
        }
        case 0xFF41:
        {
            //STAT
            return m_pMemory->Retrieve(0xFF41) | 0x80;
        }
        case 0xFF44:
        {
            //LY
            return (m_pVideo->IsScreenEnabled() ? m_pMemory->Retrieve(0xFF44) : 0x00);
        }
        case 0xFF4F:
        {
            //VBK
            return m_pMemory->Retrieve(0xFF4F) | 0xFE;
        }
        case 0xFF51:
        {
            //HDMA1
            // return (m_bCGB ? m_pMemory->GetHDMARegister(1) : m_pMemory->Retrieve(addr));
        }
        
    }
}

#endif