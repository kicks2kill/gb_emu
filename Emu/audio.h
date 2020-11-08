/*
   Nintendo Game boy Emulator
   Copyright (C) 2020 Orin
*/


#ifndef AUDIO_H
#define AUDIO_H

#include "definitions.h"
#include "audio/blip_buffer.h"

class Audio
{
public:
   Audio();
   ~Audio();
   void Init();
   void Reset(bool bCGB);
   void SetSampleRate(int rate);
   void SetVolume(float volume);
   uint8_t ReadAudioRegister(uint16_t address);
   void WriteAudioRegister(uint16_t address, uint8_t value);
   void Tick(unsigned int clockCycles);
   void EndFrame(int16_t* pSampleBuffer, int* pSampleCount);
   void SaveState(std::ostream& stream);
   void LoadState(std::istream& stream);

private:
   int m_ElapsedCycles;
   int m_SampleRate;
   short* m_pSampleBuffer;
   bool m_bCGB;
};

inline void Audio::Tick(unsigned int clockCycles)
{
   m_ElapsedCycles += clockCycles;
}

inline uint8_t Audio::ReadAudioRegister(uint16_t address)
{
   //need an APU here
}

inline void Audio::WriteAudioRegister(uint16_t address, uint8_t value)
{
   //need an APU here as well
}
#endif