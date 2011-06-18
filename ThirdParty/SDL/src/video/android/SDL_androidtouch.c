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

#include <android/log.h>

#include "SDL_events.h"
#include "../../events/SDL_mouse_c.h"

#include "SDL_androidtouch.h"


#define ACTION_DOWN 0
#define ACTION_UP 1
#define ACTION_MOVE 2
#define ACTION_CANCEL 3
#define ACTION_OUTSIDE 4

void Android_OnTouch(int action, float x, float y, float p)
{
    if (!Android_Window) {
        return;
    }

    if ((action != ACTION_CANCEL) && (action != ACTION_OUTSIDE)) {
        SDL_SetMouseFocus(Android_Window);
        SDL_SendMouseMotion(Android_Window, 0, (int)x, (int)y);
        switch(action) {
        case ACTION_DOWN:
            SDL_SendMouseButton(Android_Window, SDL_PRESSED, SDL_BUTTON_LEFT);
            break;
        case ACTION_UP:
            SDL_SendMouseButton(Android_Window, SDL_RELEASED, SDL_BUTTON_LEFT);
            break;
        }
    } else {
        SDL_SetMouseFocus(NULL);
    }
}

/* vi: set ts=4 sw=4 expandtab: */
