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

#if SDL_INPUT_LINUXEV
#include <linux/input.h>
#endif

/* The private structure used to keep track of a joystick */
struct joystick_hwdata
{
    int fd;
    char *fname;                /* Used in haptic subsystem */

    /* The current linux joystick driver maps hats to two axes */
    struct hwdata_hat
    {
        int axis[2];
    } *hats;
    /* The current linux joystick driver maps balls to two axes */
    struct hwdata_ball
    {
        int axis[2];
    } *balls;

    /* Support for the Linux 2.4 unified input interface */
#if SDL_INPUT_LINUXEV
    SDL_bool is_hid;
    Uint8 key_map[KEY_MAX - BTN_MISC];
    Uint8 abs_map[ABS_MAX];
    struct axis_correct
    {
        int used;
        int coef[3];
    } abs_correct[ABS_MAX];
#endif
};
