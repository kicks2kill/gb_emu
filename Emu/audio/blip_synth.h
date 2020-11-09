/*
   Nintendo Game boy Emulator
   Copyright (C) 2020 Orin
*/

#ifndef BLIP_SYNTH_H
#define BLIP_SYNTH_H

#include "blip_buffer.h"

enum {
    blip_low_quality = 1,
    blip_med_quality = 2,
    blip_good_quality = 3,
    blip_high_quality = 4
};

template<int quality, int range>
class blip_synth 
{
public:
    blip_synth();
    blip_synth(double volume);

    void treble_equal(const blip_eq_t& eq) {;}
};
#endif