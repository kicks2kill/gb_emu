/*
   Nintendo Game boy Emulator
   Copyright (C) 2020 Orin
*/

#ifndef EMU_H
#define EMU_H

// #include "../boy.h"
#include "../definitions.h"
#include "../Cartridge.h"

extern bool emu_audio_sync;
extern bool emu_debug_disable_breakpoints;
extern int emu_debug_background_tile_addr;
extern int emu_debug_background_map_addr;
extern int emu_debug_tile_dmg_palette;


extern void emu_init(const char* save_path);
extern void emu_destroy(void);
extern void emu_update(void);
extern void emu_load_rom(const char* file_path, bool force_dmg, bool save_in_rom, Cartridge::CartridgeTypes mbc);
extern void emu_reset(bool force_dmg, bool save_in_rom, Cartridge::CartridgeTypes mbc);
extern void emu_key_pressed(Gameboy_Keys key);
extern void emu_key_released(Gameboy_Keys key);
extern void emu_memory_dump(void);
extern void emu_audio_volume(float volume);
extern void emu_audio_reset(void);
extern bool emu_is_audio_enabled(void);


#endif