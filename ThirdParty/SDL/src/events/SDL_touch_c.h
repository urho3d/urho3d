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
#include "../../include/SDL_touch.h"

#ifndef _SDL_touch_c_h
#define _SDL_touch_c_h



/* Initialize the touch subsystem */
extern int SDL_TouchInit(void);

/*Get the touch at an index */
extern SDL_Touch *SDL_GetTouchIndex(int index);

/* Get the touch with id = id */
extern SDL_Touch *SDL_GetTouch(SDL_TouchID id);

/*Get the finger at an index */
extern SDL_Finger *SDL_GetFingerIndex(SDL_Touch *touch, int index);

/* Get the finger with id = id */
extern SDL_Finger *SDL_GetFinger(SDL_Touch *touch,SDL_FingerID id);


/* Add a touch, possibly reattaching at a particular index (or -1),
   returning the index of the touch, or -1 if there was an error. */
extern int SDL_AddTouch(const SDL_Touch * touch, char *name);
                     

/* Remove a touch at an index, clearing the slot for later */
extern void SDL_DelTouch(SDL_TouchID id);

/* Set the touch focus window */
extern void SDL_SetTouchFocus(SDL_TouchID id, SDL_Window * window);

/* Send a touch motion event for a touch */
extern int SDL_SendTouchMotion(SDL_TouchID id, SDL_FingerID fingerid,
			       int relative, float x, float y, float z);

/* Send a touch down/up event for a touch */
extern int SDL_SendFingerDown(SDL_TouchID id, SDL_FingerID fingerid, 
			      SDL_bool down, float x, float y, float pressure);

/* Send a touch button event for a touch */
extern int SDL_SendTouchButton(SDL_TouchID id, Uint8 state, Uint8 button);

/* Shutdown the touch subsystem */
extern void SDL_TouchQuit(void);

/* Get the index of a touch device */
extern int SDL_GetTouchIndexId(SDL_TouchID id);

/* Print a debug message for a nonexistent touch */
extern int SDL_TouchNotFoundError(SDL_TouchID id);

#endif /* _SDL_touch_c_h */

/* vi: set ts=4 sw=4 expandtab: */
