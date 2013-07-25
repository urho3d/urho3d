/*
  Simple DirectMedia Layer
  Copyright (C) 1997-2013 Sam Lantinga <slouken@libsdl.org>

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

// Created by Yao Wei Tjong for Urho3D

#include "SDL_config.h"

#if SDL_VIDEO_DRIVER_RASPI

#include "SDL_video.h"
#include "SDL_raspivideo.h"
#include "SDL_raspiwindow.h"
#include "SDL_raspiopengles.h"
#include "SDL_raspievents.h"

#include <GLES/gl.h>

/* Broadcom VideoCore EGL */
#include <EGL/egl.h>

#define RASPI_VID_DRIVER_NAME "RASPI"

/* Initialization/Termination functions */
static int RASPI_VideoInit(_THIS);
static void RASPI_VideoQuit(_THIS);

/* RASPI driver bootstrap functions */

static int
RASPI_Available(void)
{
    return 1;
}

static void
RASPI_DeleteDevice(SDL_VideoDevice * device)
{
    SDL_free(device->driverdata);
    SDL_free(device);
}

static SDL_VideoDevice *
RASPI_CreateDevice(int devindex)
{
    SDL_VideoDevice *device;
    SDL_VideoData *data;

    /* Initialize all variables that we clean on shutdown */
    device = (SDL_VideoDevice *) SDL_calloc(1, sizeof(SDL_VideoDevice));
    if (!device) {
        SDL_OutOfMemory();
        return NULL;
    }

    data = (SDL_VideoData*) SDL_calloc(1, sizeof(SDL_VideoData));
    if (!data) {
        SDL_OutOfMemory();
        SDL_free(device);
        return NULL;
    }

    device->driverdata = data;

    /* Set the function pointers */
    device->free = RASPI_DeleteDevice;

    device->VideoInit = RASPI_VideoInit;
    device->VideoQuit = RASPI_VideoQuit;
    device->PumpEvents = RASPI_PumpEvents;

    device->CreateWindow = RASPI_CreateWindow;
    device->DestroyWindow = RASPI_DestroyWindow;

    /* OpenGLES functiion pointers */
    device->GL_GetProcAddress = RASPI_GLES_GetProcAddress;
    device->GL_LoadLibrary = RASPI_GLES_LoadLibrary;
    device->GL_UnloadLibrary = RASPI_GLES_UnloadLibrary;
    device->GL_CreateContext = RASPI_GLES_CreateContext;
    device->GL_MakeCurrent = RASPI_GLES_MakeCurrent;
    device->GL_SetSwapInterval = RASPI_GLES_SetSwapInterval;
    device->GL_GetSwapInterval = RASPI_GLES_GetSwapInterval;
    device->GL_SwapWindow = RASPI_GLES_SwapWindow;
    device->GL_DeleteContext = RASPI_GLES_DeleteContext;

    return device;
}

VideoBootStrap RASPI_bootstrap = {
    RASPI_VID_DRIVER_NAME, "SDL Raspberry Pi video driver",
    RASPI_Available, RASPI_CreateDevice
};

int
RASPI_InitModes(_THIS)
{
    SDL_VideoData *data = (SDL_VideoData *) _this->driverdata;

    const uint32_t device = 0;  /* LCD */
    DISPMANX_DISPLAY_HANDLE_T display_handle;
    DISPMANX_MODEINFO_T mode_info;

    display_handle = vc_dispmanx_display_open(device);
    if (!display_handle) {
        return SDL_SetError("Couldn't open vc_dispmanx for InitModes");
    }
    if (vc_dispmanx_display_get_info(display_handle, &mode_info) < 0) {
        SDL_SetError("vc_dispmanx couldn't get display info");
    }
    if (vc_dispmanx_display_close(display_handle) < 0) {
        return SDL_SetError("Couldn't close vc_dispmanx for InitModes");
    }

    SDL_DisplayMode mode;
    SDL_zero(mode);
    mode.w = mode_info.width;
    mode.h = mode_info.height;

    /* FIXME: this code does not seem to work as it always returns VCOS_DISPLAY_INPUT_FORMAT_INVALID
    switch (mode_info.input_format) {
    case VCOS_DISPLAY_INPUT_FORMAT_RGB888:
        mode.format = SDL_PIXELFORMAT_RGB888;
        break;
    case VCOS_DISPLAY_INPUT_FORMAT_RGB565:
        mode.format = SDL_PIXELFORMAT_RGB565;
        break;
    default:
        mode.format = SDL_PIXELFORMAT_UNKNOWN;
    }
    */
    mode.format = SDL_PIXELFORMAT_RGBA8888;

    return SDL_AddBasicVideoDisplay(&mode);
}

int
RASPI_VideoInit(_THIS)
{
    bcm_host_init();

    if (RASPI_InitModes(_this) < 0) {
        return -1;
    }

    if (RASPI_InitInput(_this) < 0) {
        return -1;
    }

    return 0;
}

void
RASPI_VideoQuit(_THIS)
{
    RASPI_QuitInput(_this);
    bcm_host_deinit();
}

#endif /* SDL_VIDEO_DRIVER_RASPI */

/* vi: set ts=4 sw=4 expandtab: */
