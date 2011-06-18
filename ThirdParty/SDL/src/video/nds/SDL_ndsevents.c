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

/* Being a null driver, there's no event stream. We just define stubs for
   most of the API. */

#include <stdio.h>
#include <stdlib.h>
#include <nds.h>

#include "../../events/SDL_events_c.h"

#include "SDL_ndsvideo.h"
#include "SDL_ndsevents_c.h"

void
NDS_PumpEvents(_THIS)
{
    scanKeys();
    /* TODO: defer click-age */
    if (keysDown() & KEY_TOUCH) {
        SDL_SendMouseButton(0, SDL_PRESSED, 0);
    } else if (keysUp() & KEY_TOUCH) {
        SDL_SendMouseButton(0, SDL_RELEASED, 0);
    }
    if (keysHeld() & KEY_TOUCH) {
		touchPosition t;

		touchRead(&t);
        SDL_SendMouseMotion(0, 0, t.px, t.py);
    }
}

/* vi: set ts=4 sw=4 expandtab: */
