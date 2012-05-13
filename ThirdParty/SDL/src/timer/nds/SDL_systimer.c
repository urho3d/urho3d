/*
  Simple DirectMedia Layer
  Copyright (C) 1997-2012 Sam Lantinga <slouken@libsdl.org>

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

#ifdef SDL_TIMER_NDS

#include <nds.h>
#include <nds/timers.h>

#include "SDL_timer.h"

/* Will wrap after 49 days. Shouldn't be an issue. */
static volatile Uint32 timer_ticks;

static void
NDS_TimerInterrupt(void)
{
    timer_ticks++;
}

void
SDL_StartTicks(void)
{
    timer_ticks = 0;

	/* Set timer 2 to fire every ms. */
	timerStart(2, ClockDivider_1024, TIMER_FREQ_1024(1000), NDS_TimerInterrupt);
}

Uint32
SDL_GetTicks(void)
{
    return timer_ticks;
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

void
SDL_Delay(Uint32 ms)
{
    Uint32 start = SDL_GetTicks();
    while (1) {
        if ((SDL_GetTicks() - start) >= ms)
            break;
    }
}

#endif /* SDL_TIMER_NDS */

/* vi: set ts=4 sw=4 expandtab: */
