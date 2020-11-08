/*
   Nintendo Game boy Emulator
   Copyright (C) 2020 Orin
*/

#include "Audio.h"
#include "memory/Memory.h"

Audio::Audio()
{
    m_bCGB = false;
    m_ElapsedCycles = 0;
    m_SampleRate = 44100; //standard
    //Eventually will add the APU here
    InitPointer(m_pSampleBuffer);
}

Audio::~Audio()
{
    SafeDelete(m_pSampleBuffer);
}

void Audio::Init()
{
    m_pSampleBuffer = new short[AUDIO_BUFFER];
    //define APU and Stereo
}