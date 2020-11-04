/*
   Nintendo Game boy Emulator
   Copyright (C) 2020 Orin
*/

#include "Video.h"
#include "Memory.h"
#include "Processor.h"

Video::Video(Memory* pMemory, Processor* pProcessor)
{
    m_pMemory = pMemory;
    m_pMemory->SetVideo(this);
    m_pProcessor = pProcessor;
    InitPointer(m_pFrameBuffer);
    InitPointer(m_pColorFrameBuffer);
    InitPointer(m_pSpriteXCacheBuffer);
    InitPointer(m_pColorCacheBuffer);
    m_iStatusMode = 0;
    m_iStatusModeCounter = 0;
    m_iStatusModeCounterAux = 0;
    m_iStatusModeLYCounter = 0;
    m_iScreenEnableDelayCycles = 0;
    m_iStatusVBlankLine = 0;
    m_iWindowLine = 0;
    m_iPixelCounter = 0;
    m_iTileCycleCounter = 0;
    m_bScreenEnabled = true;
    m_bCGB = false;
    m_bScanLineTransferred = false;
    m_iHideFrames = 0;
    m_IRQ48Signal = 0;
    m_pixelFormat = GB_PIXEL_RGB565;
}


Video::~Video()
{
    SafeDeleteArray(m_pSpriteXCacheBuffer);
    SafeDeleteArray(m_pColorCacheBuffer);
    SafeDeleteArray(m_pFrameBuffer);
}

void Video::Init()
{
    m_pFrameBuffer = new uint8_t[GAMEBOY_WIDTH * GAMEBOY_HEIGHT];
    m_pSpriteXCacheBuffer = new int[GAMEBOY_WIDTH * GAMEBOY_HEIGHT];
    m_pColorCacheBuffer = new uint8_t[GAMEBOY_WIDTH * GAMEBOY_HEIGHT];
    Reset(false); 
}

void Video::Reset(bool bCGB)
{
    for(int i = 0; i < (GAMEBOY_WIDTH * GAMEBOY_HEIGHT); i++)
        m_pSpriteXCacheBuffer[i] = m_pFrameBuffer[i] = m_pColorCacheBuffer[i] = 0; //iterate through the height * width and set buffer index to 0
    
    for(int i = 0; i < 8; i++)
        for(int j = 0; j < 4; j++)
        {
            m_CGBBackgroundPalettes[i][j][0] = m_CGBSpritePalettes[i][j][0] = 0x0000;
            m_CGBBackgroundPalettes[i][j][1] = m_CGBSpritePalettes[i][j][1] = 0x0000;
        }
    
    m_bCGB = bCGB;
    m_iHideFrames = 0;
    m_IRQ48Signal = 0;
    m_iStatusMode = 1;
    m_iStatusModeCounter = 0;
    m_iStatusModeCounterAux = 0;
    m_iStatusModeLYCounter = 144;
    m_iScreenEnableDelayCycles = 0;
    m_iStatusVBlankLine = 0;
    m_iWindowLine = 0;
    m_iPixelCounter = 0;
    m_iTileCycleCounter = 0;
    m_bScreenEnabled = true;
    m_bScanLineTransferred = false;
}

bool Video::Tick(unsigned int &clockCycles, uint16_t* pColorFrameBuffer, GB_Color_Format pixelFormat)
{
    //  // COME BACK TO THIS
    //I think that this method is going to rely on others, so lets define those first.
}

bool Video::IsScreenEnabled() const
{
    return m_bScreenEnabled;
}

const uint8_t* Video::GetFrameBuffer() const
{
    return m_pFrameBuffer;
}

int Video::GetCurrentStatusMode() const
{
    return m_iStatusMode;
}

PaletteMatrix Video::GetCGBBackgroundPalettes()
{
    return &m_CGBBackgroundPalettes;
}

PaletteMatrix Video::GetCGBSpritePalettes()
{
    return &m_CGBSpritePalettes;
}


void Video::EnableScreen()
{
    if (!m_bScreenEnabled)
        m_iScreenEnableDelayCycles = 244;
}

void Video::DisableScreen()
{
    m_bScreenEnabled = false;
    m_pMemory->Load(0xFF44, 0x00); //65438 to 0
    uint8_t stat = m_pMemory->Retrieve(0xFF41); //65345
    stat &= 0x7C; //do a bitwise AND between 65345 and 124. add result to stat
    m_pMemory->Load(0xFF41, stat);
    m_iStatusMode = 0;
    m_iStatusModeCounter = 0;
    m_iStatusModeCounterAux = 0;
    m_iStatusModeLYCounter = 0;
    m_IRQ48Signal = 0;
}


void Video::SaveState(std::ostream& stream)
{
    using namespace std;

    stream.write(reinterpret_cast<const char*> (m_pFrameBuffer), GAMEBOY_WIDTH * GAMEBOY_HEIGHT);
    stream.write(reinterpret_cast<const char*> (m_pSpriteXCacheBuffer), sizeof(int) * GAMEBOY_WIDTH * GAMEBOY_HEIGHT);
    stream.write(reinterpret_cast<const char*> (m_pColorCacheBuffer), GAMEBOY_WIDTH * GAMEBOY_HEIGHT);
    stream.write(reinterpret_cast<const char*> (&m_iStatusMode), sizeof(m_iStatusMode));
    stream.write(reinterpret_cast<const char*> (&m_iStatusModeCounter), sizeof(m_iStatusModeCounter));
    stream.write(reinterpret_cast<const char*> (&m_iStatusModeCounterAux), sizeof(m_iStatusModeCounterAux));
    stream.write(reinterpret_cast<const char*> (&m_iStatusModeLYCounter), sizeof(m_iStatusModeLYCounter));
    stream.write(reinterpret_cast<const char*> (&m_iScreenEnableDelayCycles), sizeof(m_iScreenEnableDelayCycles));
    stream.write(reinterpret_cast<const char*> (&m_iStatusVBlankLine), sizeof(m_iStatusVBlankLine));
    stream.write(reinterpret_cast<const char*> (&m_iPixelCounter), sizeof(m_iPixelCounter));
    stream.write(reinterpret_cast<const char*> (&m_iTileCycleCounter), sizeof(m_iTileCycleCounter));
    stream.write(reinterpret_cast<const char*> (&m_bScreenEnabled), sizeof(m_bScreenEnabled));
    stream.write(reinterpret_cast<const char*> (m_CGBSpritePalettes), sizeof(m_CGBSpritePalettes));
    stream.write(reinterpret_cast<const char*> (m_CGBBackgroundPalettes), sizeof(m_CGBBackgroundPalettes));
    stream.write(reinterpret_cast<const char*> (&m_bScanLineTransferred), sizeof(m_bScanLineTransferred));
    stream.write(reinterpret_cast<const char*> (&m_iWindowLine), sizeof(m_iWindowLine));
    stream.write(reinterpret_cast<const char*> (&m_iHideFrames), sizeof(m_iHideFrames));
    stream.write(reinterpret_cast<const char*> (&m_IRQ48Signal), sizeof(m_IRQ48Signal));
}

void Video::LoadState(std::istream& stream)
{
    using namespace std;

    stream.read(reinterpret_cast<char*> (m_pFrameBuffer), GAMEBOY_WIDTH * GAMEBOY_HEIGHT);
    stream.read(reinterpret_cast<char*> (m_pSpriteXCacheBuffer), sizeof(int) * GAMEBOY_WIDTH * GAMEBOY_HEIGHT);
    stream.read(reinterpret_cast<char*> (m_pColorCacheBuffer), GAMEBOY_WIDTH * GAMEBOY_HEIGHT);
    stream.read(reinterpret_cast<char*> (&m_iStatusMode), sizeof(m_iStatusMode));
    stream.read(reinterpret_cast<char*> (&m_iStatusModeCounter), sizeof(m_iStatusModeCounter));
    stream.read(reinterpret_cast<char*> (&m_iStatusModeCounterAux), sizeof(m_iStatusModeCounterAux));
    stream.read(reinterpret_cast<char*> (&m_iStatusModeLYCounter), sizeof(m_iStatusModeLYCounter));
    stream.read(reinterpret_cast<char*> (&m_iScreenEnableDelayCycles), sizeof(m_iScreenEnableDelayCycles));
    stream.read(reinterpret_cast<char*> (&m_iStatusVBlankLine), sizeof(m_iStatusVBlankLine));
    stream.read(reinterpret_cast<char*> (&m_iPixelCounter), sizeof(m_iPixelCounter));
    stream.read(reinterpret_cast<char*> (&m_iTileCycleCounter), sizeof(m_iTileCycleCounter));
    stream.read(reinterpret_cast<char*> (&m_bScreenEnabled), sizeof(m_bScreenEnabled));
    stream.read(reinterpret_cast<char*> (m_CGBSpritePalettes), sizeof(m_CGBSpritePalettes));
    stream.read(reinterpret_cast<char*> (m_CGBBackgroundPalettes), sizeof(m_CGBBackgroundPalettes));
    stream.read(reinterpret_cast<char*> (&m_bScanLineTransferred), sizeof(m_bScanLineTransferred));
    stream.read(reinterpret_cast<char*> (&m_iWindowLine), sizeof(m_iWindowLine));
    stream.read(reinterpret_cast<char*> (&m_iHideFrames), sizeof(m_iHideFrames));
    stream.read(reinterpret_cast<char*> (&m_IRQ48Signal), sizeof(m_IRQ48Signal));
}

void Video::UpdatePaletteAsSpecified(bool background, uint8_t value)
{
    bool hl = IsSetBit(value, 0);
    int index = (value >> 1) & 0x03;
    int pal = (value >> 3) & 0x07;

    uint16_t color = (background ? m_CGBBackgroundPalettes[pal][index][0] : m_CGBSpritePalettes[pal][index][0]);
    m_pMemory->Load(background ? 0xFF69 : 0xFF6B, hl); //I'm not sure if this is complete, come back to it.
}

void Video::SetColorPalette(bool background, uint8_t value)
{
    uint8_t pos = background ? m_pMemory->Retrieve(0xFF68) : m_pMemory->Retrieve(0xFF6A); //65384 or 65386
    bool hl = IsSetBit(pos, 0);
    int index = (pos >> 1) & 0x03;
    int pal = (pos >> 3) & 0x07;
    bool increment = IsSetBit(pos, 7);
    //perform if check

    uint16_t* gbcPaletteColor = background ? &m_CGBBackgroundPalettes[pal][index][0] : &m_CGBSpritePalettes[pal][index][0];
    uint16_t* gbcPaletteColorFinal = background ? &m_CGBBackgroundPalettes[pal][index][1] : &m_CGBSpritePalettes[pal][index][1];
    /*
        bitwise AND the value of gbcPaletteColor, or, perform a bitwise OR on the value where the value is shifted by 8 bits.
        If neither, bitwise AND the value by 65280, then bitwise OR by the value
    */
    *gbcPaletteColor = hl ? (*gbcPaletteColor & 0x00FF) | (value << 8) : (*gbcPaletteColor & 0xFF00) | value;
    uint8_t red_5bits = *gbcPaletteColor & 0x1F; //bitwise AND by 31 to get the red 5 bits
    uint8_t green_5bits = (*gbcPaletteColor >> 5) & 0x1F; //bit shift right by 5, then bitwise AND by 31
    uint8_t blue_5bits = (*gbcPaletteColor >> 10) & 0x1F; //bit shift right by 10, then bitwise AND by 31
    uint8_t green_6bits = green_5bits << 1; //get 6th bit by bitshifting left by 1
 

    
}

