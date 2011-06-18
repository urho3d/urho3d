/*
  Simple DirectMedia Layer
  Copyright (C) 1997-2011 Sam Lantinga <slouken@libsdl.org>

  This software is provided 'as-is', without any express or implied
  warranty.  In no event will the authors be held liable for any damages
  arising from the use of this software.

  Permission is granted to anyone to use this software for any purpose,
  including commercial applications, and to alter it and redistribute it
  freely, subject to the following restrictions:

  1. The origin of this software must not be misrepresented; you must not
     claim that you wrote the original software. If you use this software
     in a product, an acknowledgment in the product documentation would be
     appreciated but is not required.
  2. Altered source versions must be plainly marked as such, and must not be
     misrepresented as being the original software.
  3. This notice may not be removed or altered from any source distribution.
*/
#include "SDL_config.h"

#ifdef SDL_TIMER_WINCE

#include "../../core/windows/SDL_windows.h"

#include "SDL_timer.h"

static Uint64 start_date;
static Uint64 start_ticks;

static Uint64
wce_ticks(void)
{
    return ((Uint64) GetTickCount());
}

static Uint64
wce_date(void)
{
    union
    {
        FILETIME ftime;
        Uint64 itime;
    } ftime;
    SYSTEMTIME stime;

    GetSystemTime(&stime);
    SystemTimeToFileTime(&stime, &ftime.ftime);
    ftime.itime /= 10000;       // Convert 100ns intervals to 1ms intervals
    // Remove ms portion, which can't be relied on
    ftime.itime -= (ftime.itime % 1000);
    return (ftime.itime);
}

static Sint32
wce_rel_ticks(void)
{
    return ((Sint32) (wce_ticks() - start_ticks));
}

static Sint32
wce_rel_date(void)
{
    return ((Sint32) (wce_date() - start_date));
}

/* Recard start-time of application for reference */
void
SDL_StartTicks(void)
{
    start_date = wce_date();
    start_ticks = wce_ticks();
}

/* Return time in ms relative to when SDL was started */
Uint32
SDL_GetTicks()
{
    Sint32 offset = wce_rel_date() - wce_rel_ticks();
    if ((offset < -1000) || (offset > 1000)) {
//    fprintf(stderr,"Time desync(%+d), resyncing\n",offset/1000);
        start_ticks -= offset;
    }

    return ((Uint32) wce_rel_ticks());
}

Uint64
SDL_GetPerformanceCounter(void)
{
    return SDL_GetTicks();
}

Uint64
SDL_GetPerformanceFrequency(void)
{
    return 1000;
}

/* Give up approx. givem milliseconds to the OS. */
void
SDL_Delay(Uint32 ms)
{
    Sleep(ms);
}

#endif /* SDL_TIMER_WINCE */

/* vi: set ts=4 sw=4 expandtab: */
