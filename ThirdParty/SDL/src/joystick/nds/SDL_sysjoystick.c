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

#ifdef SDL_JOYSTICK_NDS

/* This is the system specific header for the SDL joystick API */
#include <nds.h>
#include <stdio.h>              /* For the definition of NULL */

#include "SDL_error.h"
#include "SDL_events.h"
#include "SDL_joystick.h"
#include "../SDL_sysjoystick.h"
#include "../SDL_joystick_c.h"

#include "../../video/nds/SDL_ndsevents_c.h"

/* Function to scan the system for joysticks.
 * This function should set SDL_numjoysticks to the number of available
 * joysticks.  Joystick 0 should be the system default joystick.
 * It should return 0, or -1 on an unrecoverable fatal error.
 */
int
SDL_SYS_JoystickInit(void)
{
    SDL_numjoysticks = 1;
    return (1);
}

/* Function to get the device-dependent name of a joystick */
const char *
SDL_SYS_JoystickName(int index)
{
    if (!index)
        return "NDS builtin joypad";
    SDL_SetError("No joystick available with that index");
    return (NULL);
}

/* Function to open a joystick for use.
   The joystick to open is specified by the index field of the joystick.
   This should fill the nbuttons and naxes fields of the joystick structure.
   It returns 0, or -1 if there is an error.
 */
int
SDL_SYS_JoystickOpen(SDL_Joystick * joystick)
{
    joystick->nbuttons = 8;
    joystick->nhats = 0;
    joystick->nballs = 0;
    joystick->naxes = 2;
    return 0;
}


/* Function to update the state of a joystick - called as a device poll.
 * This function shouldn't update the joystick structure directly,
 * but instead should call SDL_PrivateJoystick*() to deliver events
 * and update joystick device state.
 */
    void
SDL_SYS_JoystickUpdate(SDL_Joystick * joystick)
{
    u32 keysd, keysu;
    int magnitude = 16384;
    
        /*scanKeys(); - this is done in PumpEvents, because touch uses it too */ 
        keysd = keysDown();
    keysu = keysUp();

    if ((keysd & KEY_UP)) {
        SDL_PrivateJoystickAxis(joystick, 1, -magnitude);
    }
    if ((keysd & KEY_DOWN)) {
        SDL_PrivateJoystickAxis(joystick, 1, magnitude);
    }
    if ((keysd & KEY_LEFT)) {
        SDL_PrivateJoystickAxis(joystick, 0, -magnitude);
    }
    if ((keysd & KEY_RIGHT)) {
        SDL_PrivateJoystickAxis(joystick, 0, magnitude);
    }
    if ((keysu & (KEY_UP | KEY_DOWN))) {
        SDL_PrivateJoystickAxis(joystick, 1, 0);
    }
    if ((keysu & (KEY_LEFT | KEY_RIGHT))) {
        SDL_PrivateJoystickAxis(joystick, 0, 0);
    }
    if ((keysd & KEY_A)) {
        SDL_PrivateJoystickButton(joystick, 0, SDL_PRESSED);
    }
    if ((keysd & KEY_B)) {
        SDL_PrivateJoystickButton(joystick, 1, SDL_PRESSED);
    }
    if ((keysd & KEY_X)) {
        SDL_PrivateJoystickButton(joystick, 2, SDL_PRESSED);
    }
    if ((keysd & KEY_Y)) {
        SDL_PrivateJoystickButton(joystick, 3, SDL_PRESSED);
    }
    if ((keysd & KEY_L)) {
        SDL_PrivateJoystickButton(joystick, 4, SDL_PRESSED);
    }
    if ((keysd & KEY_R)) {
        SDL_PrivateJoystickButton(joystick, 5, SDL_PRESSED);
    }
    if ((keysd & KEY_SELECT)) {
        SDL_PrivateJoystickButton(joystick, 6, SDL_PRESSED);
    }
    if ((keysd & KEY_START)) {
        SDL_PrivateJoystickButton(joystick, 7, SDL_PRESSED);
    }
    if ((keysu & KEY_A)) {
        SDL_PrivateJoystickButton(joystick, 0, SDL_RELEASED);
    }
    if ((keysu & KEY_B)) {
        SDL_PrivateJoystickButton(joystick, 1, SDL_RELEASED);
    }
    if ((keysu & KEY_X)) {
        SDL_PrivateJoystickButton(joystick, 2, SDL_RELEASED);
    }
    if ((keysu & KEY_Y)) {
        SDL_PrivateJoystickButton(joystick, 3, SDL_RELEASED);
    }
    if ((keysu & KEY_L)) {
        SDL_PrivateJoystickButton(joystick, 4, SDL_RELEASED);
    }
    if ((keysu & KEY_R)) {
        SDL_PrivateJoystickButton(joystick, 5, SDL_RELEASED);
    }
    if ((keysu & KEY_SELECT)) {
        SDL_PrivateJoystickButton(joystick, 6, SDL_RELEASED);
    }
    if ((keysu & KEY_START)) {
        SDL_PrivateJoystickButton(joystick, 7, SDL_RELEASED);
    }
}

/* Function to close a joystick after use */
void
SDL_SYS_JoystickClose(SDL_Joystick * joystick)
{
}

/* Function to perform any system-specific joystick related cleanup */
void
SDL_SYS_JoystickQuit(void)
{
}

#endif /* SDL_JOYSTICK_NDS */
