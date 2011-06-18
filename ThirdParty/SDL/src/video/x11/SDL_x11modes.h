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

#ifndef _SDL_x11modes_h
#define _SDL_x11modes_h

typedef struct
{
    int screen;
    Visual *visual;
    int depth;
    int scanline_pad;

    int use_xinerama;
    int use_xrandr;
    int use_vidmode;

#if SDL_VIDEO_DRIVER_X11_XINERAMA
    XineramaScreenInfo xinerama_info;
#endif
#if SDL_VIDEO_DRIVER_X11_XRANDR
    XRRScreenConfiguration *screen_config;
    int saved_size;
    Rotation saved_rotation;
    short saved_rate;
#endif
#if SDL_VIDEO_DRIVER_X11_XVIDMODE
    XF86VidModeModeInfo saved_mode;
    struct
    {
        int x, y;
    } saved_view;
#endif

} SDL_DisplayData;

extern int X11_InitModes(_THIS);
extern void X11_GetDisplayModes(_THIS, SDL_VideoDisplay * display);
extern int X11_SetDisplayMode(_THIS, SDL_VideoDisplay * display, SDL_DisplayMode * mode);
extern void X11_QuitModes(_THIS);

/* Some utility functions for working with visuals */
extern int X11_GetVisualInfoFromVisual(Display * display, Visual * visual,
                                       XVisualInfo * vinfo);
extern Uint32 X11_GetPixelFormatFromVisualInfo(Display * display,
                                               XVisualInfo * vinfo);

#endif /* _SDL_x11modes_h */

/* vi: set ts=4 sw=4 expandtab: */
