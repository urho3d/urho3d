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

#if SDL_VIDEO_DRIVER_ANDROID

#include <android/log.h>

#include "SDL_events.h"
#include "../../events/SDL_mouse_c.h"
#include "../../events/SDL_touch_c.h"

#include "SDL_androidtouch.h"


#define ACTION_DOWN 0
#define ACTION_UP 1
#define ACTION_MOVE 2
#define ACTION_CANCEL 3
#define ACTION_OUTSIDE 4
// The following two are deprecated but it seems they are still emitted (instead the corresponding ACTION_UP/DOWN) as of Android 3.2
#define ACTION_POINTER_1_DOWN 5
#define ACTION_POINTER_1_UP 6

void Android_OnTouch(int touch_device_id_in, int pointer_finger_id_in, int action, float x, float y, float p) 
{
    SDL_TouchID touchDeviceId = 0;
    SDL_FingerID fingerId = 0;
    
    if (!Android_Window) {
        return;
    }
    
    touchDeviceId = (SDL_TouchID)touch_device_id_in;
    if (!SDL_GetTouch(touchDeviceId)) {
        SDL_Touch touch;
        memset( &touch, 0, sizeof(touch) );
        touch.id = touchDeviceId;
        touch.x_min = 0.0f;
        touch.x_max = (float)Android_ScreenWidth;
        touch.native_xres = touch.x_max - touch.x_min;
        touch.y_min = 0.0f;
        touch.y_max = (float)Android_ScreenHeight;
        touch.native_yres = touch.y_max - touch.y_min;
        touch.pressure_min = 0.0f;
        touch.pressure_max = 1.0f;
        touch.native_pressureres = touch.pressure_max - touch.pressure_min;
        if (SDL_AddTouch(&touch, "") < 0) {
             SDL_Log("error: can't add touch %s, %d", __FILE__, __LINE__);
        }
    }

    
    fingerId = (SDL_FingerID)pointer_finger_id_in;
    switch (action) {
        case ACTION_DOWN:
        case ACTION_POINTER_1_DOWN:
            SDL_SendFingerDown(touchDeviceId, fingerId, SDL_TRUE, x, y, p);
            break;
        case ACTION_MOVE:
            SDL_SendTouchMotion(touchDeviceId, fingerId, SDL_FALSE, x, y, p);
            break;
        case ACTION_UP:
        case ACTION_POINTER_1_UP:
            SDL_SendFingerDown(touchDeviceId, fingerId, SDL_FALSE, x, y, p);
            break;
        default:
            break;
    } 
}

#endif /* SDL_VIDEO_DRIVER_ANDROID */

/* vi: set ts=4 sw=4 expandtab: */
