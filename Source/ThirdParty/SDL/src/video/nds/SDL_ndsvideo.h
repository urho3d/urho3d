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

#ifndef _SDL_ndsvideo_h
#define _SDL_ndsvideo_h

#include "../SDL_sysvideo.h"

#include "SDL_ndswindow.h"

#define SCREEN_GAP 92			/* line-equivalent gap between the 2 screens  */

/* Per Window information. */
struct NDS_WindowData {
	struct {
		int bg_id;
		void *vram_pixels;           /* where the pixel data is stored (a pointer into VRAM) */
		void *pixels;				 /* area in user frame buffer */
		int length;
	} main, sub;

    int pitch, bpp;             /* useful information about the texture */
    struct {
        int x, y;
    } scale;                    /* x/y stretch (24.8 fixed point) */

    struct {
        int x, y;
    } scroll;                   /* x/y offset */
    int rotate;                 /* -32768 to 32767, texture rotation */

	/* user frame buffer - todo: better way to do double buffering */
	void *pixels;
	int pixels_length;
};


#endif /* _SDL_ndsvideo_h */

/* vi: set ts=4 sw=4 expandtab: */
