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