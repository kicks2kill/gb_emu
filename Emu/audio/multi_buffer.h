/*
   Nintendo Game boy Emulator
   Copyright (C) 2020 Orin
*/


#ifndef MULTI_BUFFER_H
#define MULTI_BUFFER_H

#include "blargg_common.h"
#include "blip_buffer.h"


class multi_buffer
{
public:
   multi_buffer(int samples_per_frame);
   virtual ~multi_buffer();

   //set number of channels available and their types
   enum {type_index_mask = 0xFF};
   enum {wave_type = 0x100, noise_type = 0x200, mixed_type = wave_type | noise_type};
   virtual const char* set_channel_count(int, int const* types = 0);
   int channel_count() const { return _channel_count;}

   struct channel_type 
   {
     blip_buffer* left;
     blip_buffer* center;
     blip_buffer* right; 
   
   };

   virtual channel_type channel(int index) = 0;

private:
   //define non-copyable
   multi_buffer( const multi_buffer&);
   multi_buffer& operator = (const multi_buffer&);

   unsigned channels_changed_count;
   long sample_rate;
   int length;
   int const samples_per_frame;
   int const* channel_types;
   bool immediate_removal;
   int _channel_count;
};

#endif