/*
   Nintendo Game boy Emulator
   Copyright (C) 2020 Orin
*/

#ifndef OSCIL_H
#define OSCIL_H

#include "blargg_common.h"
#include "blip_buffer.h"
#include "definitions.h"

#ifndef APU_OVERCLOCK
    #define APU_OVERCLOCK 1
#endif

class Oscil
{
protected:
    //11-bit frequency in NRx3 and Nrx4
    int frequency() const {return (regs[4] & 7) * 0x100 + regs[3];}

    void update_amp(long, int new_amp);
    int write_trig(int frame_phase, int max_len, int old_d);

public:
    enum {clk_mul = APU_OVERCLOCK};

    blip_buffer* outputs[4]; //NULL, Center, Left and Right
    blip_buffer* output;     //where to output sound
    uint8_t* regs; //oscillators 5 registers
    // typedef blip_synth<blip_good_quality,1> g_synth; //define this later as a separate synth declaration.
    int mode; //mode_dmg, mode_cgb
    int delay; //clock until freq timer expires
    int length_ctr; //length counter
    unsigned phase; //waveform phase
    bool enabled; //enable flag
    void reset();
    void clock_length();

};

class Env : public Oscil 
{
public:
    Env() : env_delay{0}, env_enabled{false} {}
    int env_delay;
    int volume;
    bool env_enabled;

    void clock_envelope();
    bool write_register(int frame_phase, int reg, int old_d, int new_d);

    void reset()
    {
        env_delay = 0;
        volume = 0;
        Oscil::reset();
    }
protected:

private:
    int reload_env_timer();
};

class Square : public Env
{
public:
    bool write_register(int frame_phase, int reg, int old_d, int new_d);
    void run(long, long);

    void reset()
    {
        Env::reset();
    }

private:    
    int period() const {return (2048 - frequency()) * (4 * clk_mul);}
};


class Sweep_Square : public Square
{
public:
    int sweep_freq;
    int sweep_delay;
    bool sweep_enabled;
    bool sweep_neg;

    void clock_sweep();
    void write_register(int frame_phase, int reg, int old_d, int new_d);

    void reset()
    {
        sweep_freq = 0;
        sweep_delay = 0;
        sweep_enabled = false;
        sweep_neg = false;
        Square::reset();
    }

private:
    enum {period_mask = 0x70};
    enum {shift_mask = 0x07};

    void calc_sweep(bool updated);
    void reload_sweep_timer();
};

class Noise : public Env
{
public:
    int dividers; 
    void write_register(int frame_phase, int reg, int old_d, int new_d);
    void run(long, long);

    void reset()
    {
        dividers = 0;
        Env::reset();
    }

private:
    enum {period2_mask = 0x1FFFF};
    int period2_index() const {return regs[3] >> 4;}
    int period2(int base = 8) const {return base << period2_index();}
};


class Wave : public Oscil 
{
public:
    int sample_buf;
    
    void write_register(int frame_phase, int reg, int old_d, int data);
    void run(long, long);

    //Read/write wave RAM data
    void read(unsigned address) const;
    void write(unsigned address, int data);

    void reset()
    {
        sample_buf = 0;
        Oscil::reset();
    }

private:
    enum {bank40_mask = 0x40};
    enum {bank_size = 32};

    uint8_t* wave_ram; //32 bytes, stored in APU

    friend class Apu;
    //frequency timer period
    int period() const {return (2048-frequency()) * (2 * clk_mul);}

};
#endif