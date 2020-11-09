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
    bool b_CGB;
};

inline uint8_t IORegisters::PerformRead(uint16_t addr)
{
    //TODO
}

#endif