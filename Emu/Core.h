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
    
};


#endif