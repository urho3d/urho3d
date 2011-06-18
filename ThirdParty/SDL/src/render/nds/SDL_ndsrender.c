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

#if SDL_VIDEO_RENDER_NDS

#include <stdio.h>
#include <stdlib.h>
#include <nds.h>

#include <gl2d.h>

#include "SDL_video.h"
#include "../../video/SDL_sysvideo.h"
#include "SDL_render.h"
#include "../SDL_sysrender.h"
#include "SDL_log.h"

/* SDL NDS renderer implementation */

extern SDL_RenderDriver NDS_RenderDriver;

typedef struct
{
	/* Whether current 3D engine is on the main or sub screen. */
	int is_sub;
} NDS_RenderData;

typedef struct
{
	glImage image[1];
} NDS_TextureData;


static int NDS_UpdateViewport(SDL_Renderer *renderer)
{
	/* Nothing to do. */
	return 0;
}

static int
NDS_RenderCopy(SDL_Renderer * renderer, SDL_Texture * texture,
               const SDL_Rect * srcrect, const SDL_Rect * dstrect)
{
    NDS_RenderData *data = (NDS_RenderData *) renderer->driverdata;
    NDS_TextureData *txdat = (NDS_TextureData *) texture->driverdata;
	int dest_y;

	if (data->is_sub) {
		dest_y = dstrect->y;
	} else {
		dest_y = dstrect->y-SCREEN_HEIGHT;
	}

	if (texture->w == dstrect->w && texture->h == dstrect->h) {
		/* No scaling */
		glSprite(dstrect->x, dest_y, GL_FLIP_NONE, txdat->image);
	} else {
		/* Convert the scaling proportion into a 20.12 value. */
		s32 scale_w = divf32(dstrect->w << 12, texture->w << 12);
		s32 scale_h = divf32(dstrect->h << 12, texture->h << 12);

		glSpriteScaleXY(dstrect->x, dest_y, scale_w, scale_h, GL_FLIP_NONE, txdat->image);
	}

    return 0;
}

static int NDS_CreateTexture(SDL_Renderer *renderer, SDL_Texture *texture)
{
    NDS_TextureData *txdat = NULL;
    int i;

	SDL_Log("NDS_CreateTexture: NDS_CreateTexture.\n");

	/* Sanity checks. */
	for (i=0; i<NDS_RenderDriver.info.num_texture_formats; i++) {
		if (texture->format == NDS_RenderDriver.info.texture_formats[i])
			break;
	}
	if (i == NDS_RenderDriver.info.num_texture_formats) {
		SDL_SetError("Unsupported texture format (%x)", texture->format);
		return -1;
	}

	if (texture->w > NDS_RenderDriver.info.max_texture_width) {
		SDL_SetError("Texture too large (%d)", texture->w);
		return -1;
	}

	if (texture->h > NDS_RenderDriver.info.max_texture_height) {
		SDL_SetError("Texture too tall (%d)", texture->h);
		return -1;
	}

	texture->driverdata = SDL_calloc(1, sizeof(NDS_TextureData));
	txdat = (NDS_TextureData *) texture->driverdata;
	if (!txdat) {
		SDL_OutOfMemory();
		return -1;
	}

    return 0;
}

static void
NDS_DestroyTexture(SDL_Renderer * renderer, SDL_Texture * texture)
{
    NDS_TextureData *txdat = texture->driverdata;

    /* free anything else allocated for texture */
    SDL_free(txdat);
}

/* size is no more than 512. */
static int get_gltexture_size(unsigned int size)
{
	if (size > 256)
		return TEXTURE_SIZE_512;
	else if (size > 128)
		return TEXTURE_SIZE_256;
	else if (size > 64)
		return TEXTURE_SIZE_128;
	else if (size > 32)
		return TEXTURE_SIZE_64;
	else if (size > 16)
		return TEXTURE_SIZE_32;
	else if (size > 8)
		return TEXTURE_SIZE_16;
	else
		return TEXTURE_SIZE_8;
}

static int NDS_UpdateTexture(SDL_Renderer * renderer, SDL_Texture * texture,
							 const SDL_Rect * rect, const void *pixels, int pitch)
{
    NDS_TextureData *txdat = (NDS_TextureData *) texture->driverdata;

	glLoadTileSet(txdat->image,
				  rect->w, rect->h,
				  rect->w, rect->h,
				  texture->format == SDL_PIXELFORMAT_ABGR1555 ? GL_RGBA : GL_RGB,
				  get_gltexture_size(rect->w),
				  get_gltexture_size(rect->h),
				  TEXGEN_OFF, 0, NULL,
				  pixels);

    return 0;
}

static int NDS_LockTexture(SDL_Renderer *renderer, SDL_Texture *texture,
						   const SDL_Rect *rect, void **pixels, int *pitch)
{
	SDL_Log("enter %s (todo)\n", __func__);

    return 0;
}

static void NDS_UnlockTexture(SDL_Renderer *renderer, SDL_Texture *texture)
{
	SDL_Log("enter %s\n", __func__);
    /* stub! */
}

static int NDS_RenderClear(SDL_Renderer *renderer)
{
    glClearColor(renderer->r >> 3,
                 renderer->g >> 3,
                 renderer->b >> 3,
                 renderer->a >> 3);

	return 0;
}

static void NDS_RenderPresent(SDL_Renderer * renderer)
{
    NDS_RenderData *data = (NDS_RenderData *) renderer->driverdata;
	static int frame =0;

	glEnd2D();
		
	glFlush(0);

	swiWaitForVBlank();

	/* wait for capture unit to be ready */
	while(REG_DISPCAPCNT & DCAP_ENABLE);

	/* 3D engine can only work on one screen at a time. */
	data->is_sub = !data->is_sub;
	if (data->is_sub) {
		lcdMainOnBottom();
		vramSetBankC(VRAM_C_LCD);
		vramSetBankD(VRAM_D_SUB_SPRITE);
		REG_DISPCAPCNT = DCAP_BANK(2) | DCAP_ENABLE | DCAP_SIZE(3);
	} else {
		lcdMainOnTop();
		vramSetBankD(VRAM_D_LCD);
		vramSetBankC(VRAM_C_SUB_BG);
		REG_DISPCAPCNT = DCAP_BANK(3) | DCAP_ENABLE | DCAP_SIZE(3);
	}

	glBegin2D();
}

static int NDS_RenderDrawPoints(SDL_Renderer *renderer, const SDL_Point *points,
								int count)
{
    NDS_RenderData *data = (NDS_RenderData *) renderer->driverdata;
	int i;
	int color = RGB15(renderer->r >> 3,
					  renderer->g >> 3,
					  renderer->b >> 3);

	for (i=0; i < count; i++) {
		if (data->is_sub) {
			glPutPixel(points[i].x, points[i].y, color);
		} else {
			glPutPixel(points[i].x, points[i].y - SCREEN_HEIGHT, color);
		}
	}

	return 0;
}

static int NDS_RenderDrawLines(SDL_Renderer *renderer, const SDL_Point *points,
							   int count)
{
    NDS_RenderData *data = (NDS_RenderData *) renderer->driverdata;
	int i;
	int color = RGB15(renderer->r >> 3,
					  renderer->g >> 3,
					  renderer->b >> 3);

	for (i=0; i < count-1; i++) {
		if (data->is_sub) {
			glLine(points[i].x, points[i].y, points[i+1].x, points[i+1].y, color);
		} else {
			glLine(points[i].x, points[i].y - SCREEN_HEIGHT, 
				   points[i+1].x, points[i+1].y - SCREEN_HEIGHT, color);
		}
	}

	return 0;
}

static int NDS_RenderFillRects(SDL_Renderer *renderer, const SDL_Rect *rects,
							   int count)
{
    NDS_RenderData *data = (NDS_RenderData *) renderer->driverdata;
	int i;
	int color = RGB15(renderer->r >> 3,
					  renderer->g >> 3,
					  renderer->b >> 3);

	for (i=0; i<count; i++) {
		if (data->is_sub) {
			glBoxFilled(rects[i].x, rects[i].y, 
						rects[i].x + rects[i].w,
						rects[i].y + rects[i].h, color);
	} else {
			glBoxFilled(rects[i].x, rects[i].y - SCREEN_HEIGHT,
						rects[i].x + rects[i].w,
						rects[i].y + rects[i].h - SCREEN_HEIGHT,
						color);
		}
	}

	return 0;
}

static SDL_Renderer *
NDS_CreateRenderer(SDL_Window * window, Uint32 flags)
{
    SDL_VideoDisplay *display = SDL_GetDisplayForWindow(window);
    SDL_DisplayMode *displayMode = &display->current_mode;
    SDL_Renderer *renderer;
    NDS_RenderData *data;
    int bpp;
    Uint32 Rmask, Gmask, Bmask, Amask;

	if (displayMode->format != SDL_PIXELFORMAT_ABGR1555) {
		SDL_SetError("Unsupported pixel format (%x)", displayMode->format);
		return NULL;
	}

    if (!SDL_PixelFormatEnumToMasks(displayMode->format, &bpp,
                                    &Rmask, &Gmask, &Bmask, &Amask)) {
        SDL_SetError("Unknown display format");
        return NULL;
    }

    renderer = (SDL_Renderer *) SDL_calloc(1, sizeof(*renderer));
    if (!renderer) {
        SDL_OutOfMemory();
        return NULL;
    }

    data = (NDS_RenderData *) SDL_calloc(1, sizeof(*data));
    if (!data) {
        SDL_free(renderer);
        SDL_OutOfMemory();
        return NULL;
    }

    renderer->info = NDS_RenderDriver.info;
    renderer->info.flags = SDL_RENDERER_ACCELERATED;

	renderer->UpdateViewport = NDS_UpdateViewport;
    renderer->CreateTexture = NDS_CreateTexture;
	renderer->DestroyTexture = NDS_DestroyTexture;
	renderer->RenderCopy = NDS_RenderCopy;	
	renderer->UpdateTexture = NDS_UpdateTexture;
	renderer->LockTexture = NDS_LockTexture;
	renderer->UnlockTexture = NDS_UnlockTexture;
	renderer->RenderClear = NDS_RenderClear;
	renderer->RenderPresent = NDS_RenderPresent;
	renderer->RenderDrawPoints = NDS_RenderDrawPoints;
	renderer->RenderDrawLines = NDS_RenderDrawLines;
	renderer->RenderFillRects = NDS_RenderFillRects;

	renderer->driverdata = data;

    return renderer;
}

SDL_RenderDriver NDS_RenderDriver = {
	.CreateRenderer = NDS_CreateRenderer,
    .info = {
		.name = "nds",
		.flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC,
		.num_texture_formats = 2,
		.texture_formats = { [0] = SDL_PIXELFORMAT_ABGR1555,
							 [1] = SDL_PIXELFORMAT_BGR555,
		},
		.max_texture_width = 512,
		.max_texture_height = 512,
     }
};

#endif /* SDL_VIDEO_RENDER_NDS */

/* vi: set ts=4 sw=4 expandtab: */
