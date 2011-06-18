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

#ifndef _SDL_lowvideo_h
#define _SDL_lowvideo_h

#include "SDL_BWin.h"
#include "SDL_mouse.h"
#include "../SDL_sysvideo.h"

/* Hidden "this" pointer for the video functions */
#define _THIS	SDL_VideoDevice *_this

/* Private display data */
struct SDL_PrivateVideoData
{
    /* The main window */
    SDL_BWin *SDL_Win;

    /* The fullscreen mode list */
    display_mode saved_mode;
#define NUM_MODELISTS	4       /* 8, 16, 24, and 32 bits-per-pixel */
    int SDL_nummodes[NUM_MODELISTS];
    SDL_Rect **SDL_modelist[NUM_MODELISTS];

    /* A completely clear cursor */
    WMcursor *BlankCursor;

    SDL_Overlay *overlay;
};
/* Old variable names */
#define SDL_Win		(_this->hidden->SDL_Win)
#define saved_mode	(_this->hidden->saved_mode)
#define SDL_nummodes	(_this->hidden->SDL_nummodes)
#define SDL_modelist	(_this->hidden->SDL_modelist)
#define SDL_BlankCursor	(_this->hidden->BlankCursor)
#define current_overlay (_this->hidden->overlay)

#endif /* _SDL_lowvideo_h */
/* vi: set ts=4 sw=4 expandtab: */
