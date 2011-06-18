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


#ifndef __SDL_SYS_YUV_H__
#define __SDL_SYS_YUV_H__

/* This is the BeOS implementation of YUV video overlays */

#include "SDL_video.h"
#include "SDL_lowvideo.h"

extern "C"
{

    struct private_yuvhwdata
    {
/*  FRAMEDATA* CurrentFrameData;
    FRAMEDATA* FrameData0;
    FRAMEDATA* FrameData1;
    PgScalerProps_t   props;
    PgScalerCaps_t    caps;
    PgVideoChannel_t* channel;
    PhArea_t CurrentViewPort;
    PhPoint_t CurrentWindowPos;
    long format;
    int scaler_on;
    int current;
    long YStride;
    long VStride;
    long UStride;
    int ischromakey;
    long chromakey;
    int forcedredraw;
    unsigned long State;
    long flags;
*/
        SDL_Surface *display;
        BView *bview;
        bool first_display;
        BBitmap *bbitmap;
        int locked;
    };

    extern BBitmap *BE_GetOverlayBitmap(BRect bounds, color_space cs);
    extern SDL_Overlay *BE_CreateYUVOverlay(_THIS, int width, int height,
                                            Uint32 format,
                                            SDL_Surface * display);
    extern int BE_LockYUVOverlay(_THIS, SDL_Overlay * overlay);
    extern void BE_UnlockYUVOverlay(_THIS, SDL_Overlay * overlay);
    extern int BE_DisplayYUVOverlay(_THIS, SDL_Overlay * overlay,
                                    SDL_Rect * src, SDL_Rect * dst);
    extern void BE_FreeYUVOverlay(_THIS, SDL_Overlay * overlay);

};

#endif /* __SDL_PH_YUV_H__ */
/* vi: set ts=4 sw=4 expandtab: */
