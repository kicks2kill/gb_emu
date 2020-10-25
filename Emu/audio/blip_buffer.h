/*
   Nintendo Game boy Emulator
   Copyright (C) 2020 Orin
*/

#ifndef BLIP_BUFFER_H
#define BLIP_BUFFER_H

#include <limits.h>

enum { blip_sample_max = 32767};

struct blip_buffer_state_t;

class blip_buffer {
public:
    typedef const char* blargg__err;

    void clock_rate( long clocks_per_sec);

    //set output rate and buffer length in ms (1/1000 sec, 1/4 of a second).
    //if not enough memory, leaves buffer untouched and returns 'out of memory'
    blargg__err set_sample_rate(long samples_per_sec, int msc_length = 1000 /4);
    
    //Ends current time frame of specified duration and makes its samples available
    //for reading with read_samples(). Begin a new time frame at end of current frame
    void end_frame(long time);

    //Reads at most 'max_samples' out of buffer into 'dest', removing from the buffer.
    //returns number of samples actually read and removed. If stereo is true, increments
    //'dest' one extra time after writing each sample, to allow easy interleaving of two channels into a stereo output buffer
    long read_samples(short* dest, long max_samples, int stereo = 0);
   
    void clear(int entire_buffer = 1);

    long samples_avail() const;

    void remove_samples(long count);

    void bass_freq(int freq);

    long sample_rate() const;

    int length() const;

    long clock_rate() const;

public:
    blip_buffer();
    ~blip_buffer();

private:
    blip_buffer(const blip_buffer&);
    blip_buffer& operator = (const blip_buffer&);

public:
    long* buffer_;
    long buffer_size_;
    long reader_accum_;
    int bass_shift_;

private:
    long sample_rate_;
    long clock_rate_;
    int bass_freq_;
    int length_;
    blip_buffer* modified_; 
    friend class blip_reader;
};

#endif

//Num of bits in resample ratio fraction. Higher values give more accurate ratio but reduce buffer size
#ifndef BLIP_BUFFER_ACCURACY
    #define BLIP_BUFFER_ACCURACY 16
#endif

//Num of bits in phase offset. fewer than 6 bits (64 phase offsets) results in noticeable broadband noise
#ifndef BLIP_PHASE_BITS
    #if BLIP_BUFFER_FAST
        #define BLIP_PHASE_BITS 8 
    #else
        #define BLIP_PHASE_BITS 6
    #endif
#endif


//internal use
int const blip_widest_impulse_ = 16;
int const blip_buffer_extra_ = blip_widest_impulse_ + 2;
int const blip_res = 1 << BLIP_PHASE_BITS;
class blip_eq_t;

class blip_synth_fast_ {
public:
    blip_buffer* buf;
    int last_amp;
    int delta_factor;

    void volume_unit( double);
    blip_synth_fast_();
    void treble_eq(blip_eq_t const&) {}

};

class blip_synth_ {
public:
    blip_buffer* buf;
    int last_amp;
    void volume_unit(double);
    blip_synth_(short* impulse, int width);
    void treble_eq(blip_eq_t const&);

private:
    double m_volume_unit;
    short* const impulse;
    int const width;
    long kernel_unit;
    int impulse_size() const { return blip_res / 2 * width + 1;}
    void adjust_impulse();
};


//quality levels

const int blip_med_q = 8;
const int blip_good_q = 12;
const int blip_high_q = 16;


template<int quality, int range>
class blip_synth {
public:
    //set overall volume of particular waveform
    void volume ( double v) {impl.volume_unit(v * (1.0 / (range < 0 ? -range : range)));}

    //configure low-pass filter
    void treble_eq( blip_eq_t const& eq) { impl.treble_eq(eq);}

    //get/set blip_buffer for our output
    blip_buffer* output() const {return impl.buf;}
    void output(blip_buffer* b) {impl.buf = b; impl.last_amp = 0;}

    //update amplitude of waveform at a given time. We need a separate blip_synth for each waveform

    void update(long time, int amplitude);

//  // Low level implementations

    //Add an amplitutde transition of a specified delta, if we choose into a specified buffer
    //rather than the one set with output(). Delta is signed
    //the actual change in amplitude is delta * (volume / range)

    void offset(long t, int delta, blip_buffer*) const;
    void offset( long t, int delta) const { offset(t, delta, impl.buf);}

private:    
    #if BLIP_BUFFER_FAST
        #define  blip_synth_fast_ impl;
    #else
        blip_synth_ impl;
        short impulses [ blip_res * (quality / 2) + 1];
public:
    blip_synth() : impl( impulses, quality) {}
    #endif
};
