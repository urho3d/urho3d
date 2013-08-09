/*
  Simple DirectMedia Layer
  Copyright (C) 1997-2013 Sam Lantinga <slouken@libsdl.org>

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

#if defined(SDL_HAPTIC_DUMMY) || defined(SDL_HAPTIC_DISABLED)

#include "SDL_haptic.h"
#include "../SDL_syshaptic.h"


static int
SDL_SYS_LogicError(void)
{
    SDL_SetError("Logic error: No haptic devices available.");
    return 0;
}


int
SDL_SYS_HapticInit(void)
{
    return 0;
}


const char *
SDL_SYS_HapticName(int index)
{
    SDL_SYS_LogicError();
    return NULL;
}


int
SDL_SYS_HapticOpen(SDL_Haptic * haptic)
{
    SDL_SYS_LogicError();
    return -1;
}


int
SDL_SYS_HapticMouse(void)
{
    return -1;
}


int
SDL_SYS_JoystickIsHaptic(SDL_Joystick * joystick)
{
    return 0;
}


int
SDL_SYS_HapticOpenFromJoystick(SDL_Haptic * haptic, SDL_Joystick * joystick)
{
    SDL_SYS_LogicError();
    return -1;
}


int
SDL_SYS_JoystickSameHaptic(SDL_Haptic * haptic, SDL_Joystick * joystick)
{
    return 0;
}


void
SDL_SYS_HapticClose(SDL_Haptic * haptic)
{
    return;
}


void
SDL_SYS_HapticQuit(void)
{
    return;
}


int
SDL_SYS_HapticNewEffect(SDL_Haptic * haptic,
                        struct haptic_effect *effect, SDL_HapticEffect * base)
{
    SDL_SYS_LogicError();
    return -1;
}


int
SDL_SYS_HapticUpdateEffect(SDL_Haptic * haptic,
                           struct haptic_effect *effect,
                           SDL_HapticEffect * data)
{
    SDL_SYS_LogicError();
    return -1;
}


int
SDL_SYS_HapticRunEffect(SDL_Haptic * haptic, struct haptic_effect *effect,
                        Uint32 iterations)
{
    SDL_SYS_LogicError();
    return -1;
}


int
SDL_SYS_HapticStopEffect(SDL_Haptic * haptic, struct haptic_effect *effect)
{
    SDL_SYS_LogicError();
    return -1;
}


void
SDL_SYS_HapticDestroyEffect(SDL_Haptic * haptic, struct haptic_effect *effect)
{
    SDL_SYS_LogicError();
    return;
}


int
SDL_SYS_HapticGetEffectStatus(SDL_Haptic * haptic,
                              struct haptic_effect *effect)
{
    SDL_SYS_LogicError();
    return -1;
}


int
SDL_SYS_HapticSetGain(SDL_Haptic * haptic, int gain)
{
    SDL_SYS_LogicError();
    return -1;
}


int
SDL_SYS_HapticSetAutocenter(SDL_Haptic * haptic, int autocenter)
{
    SDL_SYS_LogicError();
    return -1;
}

int
SDL_SYS_HapticPause(SDL_Haptic * haptic)
{
    SDL_SYS_LogicError();
    return -1;
}

int
SDL_SYS_HapticUnpause(SDL_Haptic * haptic)
{
    SDL_SYS_LogicError();
    return -1;
}

int
SDL_SYS_HapticStopAll(SDL_Haptic * haptic)
{
    SDL_SYS_LogicError();
    return -1;
}



#endif /* SDL_HAPTIC_DUMMY || SDL_HAPTIC_DISABLED */
