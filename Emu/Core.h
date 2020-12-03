/*
   Nintendo Game boy Emulator
   Copyright (C) 2020 Orin
*/

#ifndef CORE_H
#define CORE_H
#include "definitions.h"
#include "Cartridge.h"

class Cartridge;
class Memory;
class Processor;
class Audio;
class Video;


class Core 
{
public:
    Core();
    ~Core();
    Memory* GetMemory();
    Cartridge* GetCartridge();
    Processor* GetProcessor();
    Audio* GetAudio();
    Video* GetVideo();
    void Init(GB_Color_Format pixelFormat = GB_PIXEL_RGB565);
    void LoadROM(const char* szFilePath, bool forceDMG, Cartridge::CartridgeTypes forced = Cartridge::CartridgeNotSupported);
    void LoadROMFromBuffer(const uint8_t* buffer, int size, bool forceDMG, Cartridge::CartridgeTypes forced = Cartridge::CartridgeNotSupported);
    void RunToVBlank(uint16_t* pFrameBuffer, int16_t* pSampleBuffer, int* pSampleCount, bool bDMGBuffer = false, bool step = false, bool stopOnBreakpoints = false);
    void KeyPressed(Gameboy_Keys key);
    void KeyReleased(Gameboy_Keys key);
    void Pause(bool paused);
    bool IsPaused();
    void ResetROM(bool forceDMG, Cartridge::CartridgeTypes forceType = Cartridge::CartridgeNotSupported);

private:
    Memory* m_pMemory;
    Cartridge* m_pCartridge;
    Processor* m_pProcessor;
    Audio* m_pAudio;
    Video* m_pVideo;
};


#endif