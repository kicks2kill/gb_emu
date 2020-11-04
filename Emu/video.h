/*
   Nintendo Game boy Emulator
   Copyright (C) 2020 Orin
*/


#ifndef VIDEO_H
#define VIDEO_H

#include "definitions.h"

class Memory;
class Processor;

typedef uint16_t (*PaletteMatrix)[8][4][2];


class Video
{
public:
    Video(Memory* pMemory, Processor* pProcessor);
    ~Video();
    void Init();
    void Reset(bool bCGB);
    bool tick(unsigned int &clockCycles, uint16_t* pColorFrameBuffer, GB_Color_Format pixelFormat);
    void EnableScreen();
    void DisableScreen();
    bool IsScreenEnabled() const;
    const uint8_t* GetFrameBuffer() const;
    void UpdatePaletteAsSpecified(bool background, uint8_t value);
    void SetColorPalette(bool background, uint8_t value);
    int GetCurrentStatusMode() const;
    void ResetWindowLine();
    uint8_t GetIRQ48Signal() const;
    void SetIRQ48Signal(uint8_t signal);
    void SaveState(std::ostream &stream);
    void LoadState(std::istream& stream);
    PaletteMatrix GetCGBBackgroundPalettes();
    PaletteMatrix GetCGBSpritePalettes();

private:
    void ScanLine(int line);
    void RenderBG(int line, int pixel);
    void RenderWindow(int line);
    void RenderSprites(int line);
    void UpdateStatRegister();

private:
    Memory* m_pMemory;
    Processor* m_pProcessor;
    uint8_t* m_pFrameBuffer;
    uint16_t* m_pColorFrameBuffer;
    int* m_pSpriteXCacheBuffer;
    uint8_t* m_pColorCacheBuffer;
    int m_iStatusMode;
    int m_iStatusModeCounter;
    int m_iStatusModeCounterAux;
    int m_iStatusModeLYCounter;
    int m_iScreenEnableDelayCycles;
    int m_iStatusVBlankLine;
    int m_iTileCycleCounter;
    int m_iPixelCounter;
    bool m_bScreenEnabled;
    bool m_bCGB;
    uint16_t m_CGBSpritePalettes[8][4][2];
    uint16_t m_CGBBackgroundPalettes[8][4][2];
    GB_Color_Format m_pixelFormat;
    uint8_t m_IRQ48Signal;
    int m_iHideFrames;
    int m_iWindowLine;
    bool m_bScanLineTransferred;
};

#endif