/*
   Nintendo Game boy Emulator
   Copyright (C) 2020 Orin
*/

#include "application.h"

int main(int argc, char* argv[])
{
    int ret = application_init((argc == 2) ? argv[1] : NULL);

    if (ret >= 0)
        application_mainloop();

    application_destroy();    

    return ret;
}