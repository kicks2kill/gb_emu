/*
   Nintendo Game boy Emulator
   Copyright (C) 2020 Orin
*/

#ifndef OSCIL_H
#define OSCIL_H

#include "blargg_common.h"
#include "blip_buffer.h"

#ifndef APU_OVERCLOCK
    #define APU_OVERCLOCK 1
#endif

class Oscil
{
public:
    blip_buffer* outputs[4]; //NULL, Center, Left and Right
    blip_buffer* output;     //where to output sound
    int mode; //mode_dmg, mode_cgb
    int delay; //clock until freq timer expires
    int length_ctr; //length counter
    unsigned phase; //waveform phase
    bool enabled; //enable flag
    void reset();
    void clock_length();

};


#endif