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
    void clock_rate( long clocks_per_sec);

    //set output rate and buffer length in ms (1/1000 sec, 1/4 of a second).
    //if not enough memory, leaves buffer untouched and returns 'out of memory'
    char* set_sample_rate(long samples_per_sec, int msc_length = 1000 /4);
    
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

class blip_eq_t {
public:
    blip_eq_t(double treble_db = 0);
    blip_eq_t(double treble, long rolloff, long sample_rate, long cutoff = 0);

private:    
    double treble;
    long rolloff;
    long sample_rate;
    long cutoff;
    void generate(float* out, int count) const;
    friend class blip_synth_;
};
int const blip_sample_bits = 30;

class silent_blip_buffer : public blip_buffer 
{
     long buf [blip_buffer_extra_ + 1];
public:
    char* set_sample_rate(long samples_per_sec, int msec_length);
    long count_clocks_frame(long count) const;
    void mix_samples(short const* buf,long count);
    
    silent_blip_buffer();
};

#if __GNUC__ >= 3 || _MSC_VER >= 1100
    #define blip_restricted __restrict
#else
    #define blip_restricted
#endif
    //Optimized reading from blip_buffer, for use in custom sample outputs.
    //Begins reading from buffer, name should be unique to the current block utilized.
#define blip_reader_begin(name, blip_buffer) \
    const blip_buffer::long * blip_restricted name##_reader_buf = (blip_buffer).buffer_; \
    long name##_reader_accum = (blip_buffer).reader_accum_

//gets value to pass to the blip_reader_next()
#define blip_reader_bass(blip_buffer) ((blip_buffer).bass_shift_)


//const valuie to use instead of blip_reader_bass, where optimal at the cost of having no bass control.
int const blip_reader_default_bass = 9;

//current sample to read
#define blip_reader_read(name) (name##_reader_accum >> (blip_sample_bits - 16))

//current dry sample
#define blip_reader_read_dry(name) (name##_reader_accum)

//advance to next sample
#define blip_reader_next(name, bass) \
    (void) (name##_reader_accum += *name##_reader_buff++ - (name##_reader_accum >> (bass)))

//ends reading samples from buffer
#define blip_reader_end(name, blip_buffer) \
    (void)((blip_buffer)).reader_accum_ = name##_reader_accum)

class blip_reader
{
public:
    int begin(blip_buffer&);
    long read() const {return accum >> (blip_sample_bits - 16);}
    long read_dry() const {return accum;}
    void next(int bass_shift = 9) {accum += *buf++ - (accum >> bass_shift);}
    void end(blip_buffer& b) {b.reader_accum_ = accum;}

private:
    const blip_buffer::long * buf;
    long accum;
};
};
