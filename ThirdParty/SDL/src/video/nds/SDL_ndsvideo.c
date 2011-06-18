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

/* SDL Nintendo DS video driver implementation */

#include <stdio.h>
#include <stdlib.h>
#include <nds.h>
#include <fat.h>
#include <gl2d.h>

#include "SDL_video.h"
#include "SDL_ndsvideo.h"
#include "SDL_ndsevents_c.h"
#include "../../render/SDL_sysrender.h"
#include "SDL_log.h"

#define NDSVID_DRIVER_NAME "nds"

static SDL_DisplayMode display_modes[] =
{
	/* Only one screen */
	{
		.format = SDL_PIXELFORMAT_ABGR1555,
		.w = SCREEN_WIDTH,
		.h = SCREEN_HEIGHT,
		.refresh_rate = 60,
	},

	/* Aggregated display (two screens) with no gap. */
	{
		.format = SDL_PIXELFORMAT_ABGR1555,
		.w = SCREEN_WIDTH,
		.h = 2*SCREEN_HEIGHT+SCREEN_GAP,
		.refresh_rate = 60,
	},

	/* Aggregated display (two screens) with a gap. */
	{
		.format = SDL_PIXELFORMAT_ABGR1555,
		.w = SCREEN_WIDTH,
		.h = 2*SCREEN_HEIGHT,
		.refresh_rate = 60,
	},

	/* Last entry */
	{
		.w = 0,
	}
};

/* This function must not be optimized nor inlined, else the pointer
 * to the message will be in the wrong register, and the emulator won't
 * find the string. */
__attribute__ ((noinline, optimize (0)))
static void NDS_DebugOutput2(const char* message) 
{
#ifdef __thumb__
	asm volatile ("swi #0xfc");
#else
	asm volatile ("swi #0xfc0000");
#endif
}

static void NDS_DebugOutput(void *userdata, int category, SDL_LogPriority priority, const char *message)
{
	NDS_DebugOutput2(message);
}

/* SDL NDS driver bootstrap functions */
static int NDS_Available(void)
{
    return 1;                 /* always here */
}

#ifndef USE_HW_RENDERER
static int NDS_CreateWindowFramebuffer(_THIS, SDL_Window *window,
									   Uint32 *format, void **pixels,
									   int *pitch)
{
	struct NDS_WindowData *wdata;
    int bpp;
    Uint32 Rmask, Gmask, Bmask, Amask;
	const SDL_VideoDisplay *display = SDL_GetDisplayForWindow(window);
	const SDL_DisplayMode *mode = display->driverdata;
	const Uint32 fmt = mode->format;

	if (fmt != SDL_PIXELFORMAT_ABGR1555) {
		SDL_SetError("Unsupported pixel format (%x)", fmt);
		return -1;
	}

    if (!SDL_PixelFormatEnumToMasks
        (fmt, &bpp, &Rmask, &Gmask, &Bmask, &Amask)) {
        SDL_SetError("Unknown texture format");
        return -1;
    }

	wdata = SDL_calloc(1, sizeof(struct NDS_WindowData));
	if (!wdata) {
		SDL_OutOfMemory();
		return -1;
	}

	if (bpp == 8) {
		wdata->pixels_length = (SCREEN_HEIGHT+SCREEN_GAP+SCREEN_HEIGHT)*SCREEN_WIDTH;
	} else {
		wdata->pixels_length = (SCREEN_HEIGHT+SCREEN_GAP+SCREEN_HEIGHT)*SCREEN_WIDTH*2;
	}
	wdata->pixels = SDL_calloc(1, wdata->pixels_length);
	if (!wdata->pixels) {
		SDL_free(wdata);
		SDL_SetError("Not enough memory");
        return -1;
    }

	if (bpp == 8) {
		wdata->main.bg_id = bgInit(2, BgType_Bmp8, BgSize_B8_256x256, 0, 0);
		wdata->sub.bg_id = bgInitSub(3, BgType_Bmp8, BgSize_B8_256x256, 0, 0);

		wdata->main.length = SCREEN_HEIGHT*SCREEN_WIDTH;
		wdata->main.pixels = wdata->pixels;

		wdata->sub.length = SCREEN_HEIGHT*SCREEN_WIDTH;
		wdata->sub.pixels = (u8 *)wdata->pixels + wdata->main.length;	/* or ...+SCREEN_GAP */
			
	} else {
		wdata->main.bg_id = bgInit(2, BgType_Bmp16, BgSize_B16_256x256, 0, 0);
		wdata->sub.bg_id = bgInitSub(3, BgType_Bmp16, BgSize_B16_256x256, 0, 0);

		wdata->main.length = SCREEN_HEIGHT*SCREEN_WIDTH*2;
		wdata->main.pixels = wdata->pixels;

		wdata->sub.length = SCREEN_HEIGHT*SCREEN_WIDTH*2;
		wdata->sub.pixels = (u8 *)wdata->pixels + wdata->main.length;	/* or ...+SCREEN_GAP */
	}

	wdata->pitch = (window->w) * ((bpp+1) / 8);
	wdata->bpp = bpp;
	wdata->rotate = 0;
	wdata->scale.x = 0x100;
	wdata->scale.y = 0x100;
	wdata->scroll.x = 0;
	wdata->scroll.y = 0;

	wdata->main.vram_pixels = bgGetGfxPtr(wdata->main.bg_id);
	wdata->sub.vram_pixels = bgGetGfxPtr(wdata->sub.bg_id);

#if 0
	bgSetCenter(wdata->main.bg_id, 0, 0);
	bgSetRotateScale(wdata->main.bg_id, wdata->rotate, wdata->scale.x,
					 wdata->scale.y);
	bgSetScroll(wdata->main.bg_id, wdata->scroll.x, wdata->scroll.y);
#endif

#if 0
	bgSetCenter(wdata->sub.bg_id, 0, 0);
	bgSetRotateScale(wdata->sub.bg_id, wdata->rotate, wdata->scale.x,
					 wdata->scale.y);
	bgSetScroll(wdata->sub.bg_id, wdata->scroll.x, wdata->scroll.y);
#endif

	bgUpdate();

	*format = fmt;
	*pixels = wdata->pixels;
	*pitch = wdata->pitch;

	window->driverdata = wdata;

	return 0;
}

static int NDS_UpdateWindowFramebuffer(_THIS, SDL_Window * window,
									   SDL_Rect * rects, int numrects)
{
	struct NDS_WindowData *wdata = window->driverdata;

	/* Copy everything. TODO: use rects/numrects. */
	DC_FlushRange(wdata->pixels, wdata->pixels_length);

	swiWaitForVBlank();

	dmaCopy(wdata->main.pixels, wdata->main.vram_pixels, wdata->main.length);
	dmaCopy(wdata->sub.pixels, wdata->sub.vram_pixels, wdata->sub.length);

    return 0;
}

static void NDS_DestroyWindowFramebuffer(_THIS, SDL_Window *window)
{
    struct NDS_WindowData *wdata = window->driverdata;

    SDL_free(wdata->pixels);
    SDL_free(wdata);
}
#endif

#ifdef USE_HW_RENDERER
/* Set up a 2D layer construced of bitmap sprites. This holds the
 * image when rendering to the top screen. From libnds example. 
 */
static void initSubSprites(void)
{
    oamInit(&oamSub, SpriteMapping_Bmp_2D_256, false);
 
    int x = 0;
    int y = 0;
 
    int id = 0;

    //set up a 4x3 grid of 64x64 sprites to cover the screen
    for(y = 0; y < 3; y++)
    for(x = 0; x < 4; x++)
    {
        oamSub.oamMemory[id].attribute[0] = ATTR0_BMP | ATTR0_SQUARE | (64 * y);
        oamSub.oamMemory[id].attribute[1] = ATTR1_SIZE_64 | (64 * x);
        oamSub.oamMemory[id].attribute[2] = ATTR2_ALPHA(1) | (8 * 32 * y) | (8 * x);
        id++;
    }
 
    swiWaitForVBlank();
 
    oamUpdate(&oamSub);
}
#endif

static int NDS_SetDisplayMode(_THIS, SDL_VideoDisplay *display, SDL_DisplayMode *mode)
{
	display->driverdata = mode->driverdata;

    powerOn(POWER_ALL_2D);

#ifdef USE_HW_RENDERER

	videoSetMode(MODE_5_3D);
	videoSetModeSub(MODE_5_2D);

	/* initialize gl2d */
	glScreen2D();
	glBegin2D();
	
	vramSetBankA(VRAM_A_TEXTURE);
	vramSetBankB(VRAM_B_TEXTURE );
	vramSetBankC(VRAM_C_SUB_BG_0x06200000);
	vramSetBankE(VRAM_E_TEX_PALETTE);

    // sub sprites hold the bottom image when 3D directed to top
    initSubSprites();
 
    // sub background holds the top image when 3D directed to bottom
    bgInitSub(3, BgType_Bmp16, BgSize_B16_256x256, 0, 0);
#else

	/* Select mode 5 for both screens. Can do Extended Rotation
	 * Background on both (BG 2 and 3). */
	videoSetMode(MODE_5_2D);
	videoSetModeSub(MODE_5_2D);

	vramSetBankA(VRAM_A_MAIN_BG_0x06000000);
	vramSetBankB(VRAM_B_TEXTURE );
	vramSetBankC(VRAM_C_SUB_BG_0x06200000);
	vramSetBankE(VRAM_E_TEX_PALETTE);

#endif

    return 0;
}

void NDS_GetDisplayModes(_THIS, SDL_VideoDisplay * display)
{
    SDL_DisplayMode *mode;

	for (mode = display_modes; mode->w; mode++) {
		mode->driverdata = mode; /* point back to self */
		SDL_AddDisplayMode(display, mode);
	}
}

static int NDS_VideoInit(_THIS)
{
	SDL_VideoDisplay display;
    SDL_DisplayMode mode;

	SDL_zero(mode);

    mode.format = SDL_PIXELFORMAT_UNKNOWN; // should be SDL_PIXELFORMAT_ABGR1555;
    mode.w = SCREEN_WIDTH;
    mode.h = 2*SCREEN_HEIGHT+SCREEN_GAP;
    mode.refresh_rate = 60;

	SDL_zero(display);

	display.desktop_mode = mode;

	SDL_AddVideoDisplay(&display);

    return 0;
}

static void NDS_VideoQuit(_THIS)
{
    videoSetMode(DISPLAY_SCREEN_OFF);
    videoSetModeSub(DISPLAY_SCREEN_OFF);
    vramSetBankA(VRAM_A_LCD);
    vramSetBankB(VRAM_B_LCD);
    vramSetBankC(VRAM_C_LCD);
    vramSetBankD(VRAM_D_LCD);
    vramSetBankE(VRAM_E_LCD);
    vramSetBankF(VRAM_F_LCD);
    vramSetBankG(VRAM_G_LCD);
    vramSetBankH(VRAM_H_LCD);
    vramSetBankI(VRAM_I_LCD);
}

static void NDS_DeleteDevice(SDL_VideoDevice * device)
{
    SDL_free(device);
}

static SDL_VideoDevice *NDS_CreateDevice(int devindex)
{
    SDL_VideoDevice *device;

    fatInitDefault();

    /* Initialize all variables that we clean on shutdown */
    device = SDL_calloc(1, sizeof(SDL_VideoDevice));
    if (!device) {
        SDL_OutOfMemory();
        return NULL;
    }

	device->driverdata = SDL_calloc(1, sizeof(SDL_VideoDevice));
    if (!device) {
		SDL_free(device);
        SDL_OutOfMemory();
        return NULL;
    }

    /* Set the function pointers */
    device->VideoInit = NDS_VideoInit;
    device->VideoQuit = NDS_VideoQuit;
	device->GetDisplayModes = NDS_GetDisplayModes;
    device->SetDisplayMode = NDS_SetDisplayMode;
    device->CreateWindow = NDS_CreateWindow;
#ifndef USE_HW_RENDERER
	device->CreateWindowFramebuffer = NDS_CreateWindowFramebuffer;
	device->UpdateWindowFramebuffer = NDS_UpdateWindowFramebuffer;
	device->DestroyWindowFramebuffer = NDS_DestroyWindowFramebuffer;
#endif
    device->PumpEvents = NDS_PumpEvents;
    device->free = NDS_DeleteDevice;

	/* Set the debug output. Use only under an emulator. Will crash the DS. */
#if 0
	SDL_LogSetOutputFunction(NDS_DebugOutput, NULL);
#endif

    return device;
}

VideoBootStrap NDS_bootstrap = {
    NDSVID_DRIVER_NAME, "SDL NDS video driver",
    NDS_Available, NDS_CreateDevice
};

double SDLCALL SDL_pow(double x, double y)
{
	static int once = 1;
	if (once) {
		SDL_Log("SDL_pow called but not supported on this platform");
		once = 0;
	}
	return 0;
}

/* vi: set ts=4 sw=4 expandtab: */
