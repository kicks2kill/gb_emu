/*
   Nintendo Game boy Emulator
   Copyright (C) 2020 Orin
*/

#ifndef APPLICATION_H
#define	APPLICATION_H

#define SDL_MAIN_HANDLED
#include "SDL/include/SDL.h"

#ifdef APPLICATION_IMPORT
    #define EXTERN
#else
    #define EXTERN extern
#endif

EXTERN SDL_GameController* application_gamepad;
EXTERN int application_gamepad_mappings;
EXTERN float application_display_scale;
EXTERN SDL_version application_sdl_build_version;
EXTERN SDL_version application_sdl_link_version;

EXTERN int application_init(const char* arg);
EXTERN void application_destroy(void);
EXTERN void application_mainloop(void);
EXTERN void application_trigger_quit(void);

#undef APPLICATION_IMPORT
#undef EXTERN

#endif