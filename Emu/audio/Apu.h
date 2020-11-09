/*
   Nintendo Game boy Emulator
   Copyright (C) 2020 Orin
*/

#ifndef APU_H
#define APU_H

#include "blip_buffer.h"
#include "Oscil.h"
class Apu 
{
public:
    //hardware clock rate for sound
    enum { clock_rate = 4194304 };

    //Set the buffer(s) for sound output. If left && right are NULL, mono output.
    //If all are NULL, no output
    //If channel is specified, only that channel's output is changed.
    enum {oscil_count = 4}; // If 0: Square, 1: Square, 2: Wave, 3: Noise

    void set_output(blip_buffer* center, blip_buffer* left = NULL, blip_buffer* right = NULL, int channel = oscil_count);

    //reset all hardware to init power on state before boot rom runs.
    enum mode_t {
        mode_dmg, //Game Boy monochrome
        mode_cgb //Game Boy Color
    };

    void reset(mode_t mode = mode_cgb, bool agb_wave = false);

    //read and write must be within the start address to end address range inclusively. Otherwise, will not be mapped.

    enum { s_addr = 0xFF10}; //starts at 65296
    enum {end_addr = 0xFF3F}; //ends at 65343
    enum {reg_count = end_addr - s_addr + 1};

    //CPU write of data to address at specified time
    void write_register(long time, unsigned address, int data);

    //CPU read of data from address
    void read_register(long time, unsigned address);

    //start a new frame at time 0 after specified time - end time
    void end_frame(long frame_length);

    // //Volume, Treble and Tempo

    void volume(double); //1.0 is normal
    
    //set the treble equalization
    void treble_equal(blip_eq_t const&);

    //treble and bass values for various hardware
    enum
    {
        speaker_treble = -47, //speaker on sys
        speaker_bass = 2000,
        dmg_treble = 0, //headphones on each sys
        dmg_bass = 30,
        cgb_treble = 0,
        cgb_bass = 300
    };

    //1.0 is normal, this is used for adjusting tempo in a game music player.
    void set_tempo(double);

public:
    Apu();

private:
    //should be non-copyable
    Apu(const Apu&);
    Apu& operator = (const Apu&); 

    //set up types here
    Oscil* oscs [oscil_count];
    Sweep_Square square1;
    Square square2;
    Wave wave;
    Noise noise;

    long frame_time; //time of next frame sequence
    int frame_phase; //phase of next frame sequence
    
    enum {regs_size = reg_count + 0x10};
    long last_time;
    long frame_period;
    double _volume;
 
};


#endif
