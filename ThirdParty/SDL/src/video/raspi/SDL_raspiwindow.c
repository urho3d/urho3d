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

#include "SDL_raspivideo.h"
#include "SDL_raspiwindow.h"
#include "SDL_raspiopengles.h"

int
RASPI_CreateWindow(_THIS, SDL_Window *window)
{
    SDL_VideoData *data = (SDL_VideoData *) _this->driverdata;
    if (data->window) {
        return SDL_SetError("Raspberry Pi video driver only supports one native window");
    }
    data->window = window;

    /* Adjust the window data to match the current mode */
    SDL_VideoDisplay *display = SDL_GetDisplayForWindow(window);
    SDL_DisplayMode mode = display->current_mode;

    window->x = 0;
    window->y = 0;
    window->w = mode.w;
    window->h = mode.h;

    window->flags &= ~SDL_WINDOW_RESIZABLE;     /* window is NEVER resizeable */
    window->flags |= SDL_WINDOW_FULLSCREEN;     /* window is always fullscreen */
    window->flags &= ~SDL_WINDOW_HIDDEN;
    window->flags |= SDL_WINDOW_SHOWN;          /* only support one window */
    window->flags |= SDL_WINDOW_INPUT_FOCUS;    /* always has input focus */

    display->fullscreen_window = window;

    /* One window, it always has focus */
    SDL_SetMouseFocus(window);
    SDL_SetKeyboardFocus(window);

    /* Broadcom VideoCore specific */
    if (RASPI_GLES_ChooseConfig(_this) < 0) {
        /* SDL_GetError() should have info */
        return -1;
    }

    const uint32_t device = 0;  /* LCD */
    DISPMANX_UPDATE_HANDLE_T update_handle;
    DISPMANX_ELEMENT_HANDLE_T element_handle;
    VC_RECT_T dst_rect;
    VC_RECT_T src_rect;
    VC_DISPMANX_ALPHA_T alpha;

    dst_rect.x = 0;
    dst_rect.y = 0;
    dst_rect.width = mode.w;
    dst_rect.height = mode.h;

    src_rect.x = 0;
    src_rect.y = 0;
    src_rect.width = mode.w << 16;
    src_rect.height = mode.h << 16;

    /* Through trial and error, these combination seems to work well for Urho3D engine */
    alpha.flags = DISPMANX_FLAGS_ALPHA_FIXED_ALL_PIXELS;
    alpha.opacity = 255;
    alpha.mask = 0;

    data->display = vc_dispmanx_display_open(device);
    if (!data->display) {
        return SDL_SetError("Couldn't open vc_dispmanx");
    }
    update_handle = vc_dispmanx_update_start(0 /*priority*/);
    if (!update_handle) {
        return SDL_SetError("vc_dispmanx couldn't start update");
    }
    element_handle = vc_dispmanx_element_add (update_handle, data->display, 0/*layer*/,
                                              &dst_rect, 0/*src*/, &src_rect, DISPMANX_PROTECTION_NONE,
                                              &alpha, 0/*clamp*/, 0/*transform*/);
    if (!element_handle) {
        return SDL_SetError("vc_dispmanx couldn't add element");
    }

    data->nativewindow.element = element_handle;
    data->nativewindow.width = mode.w;
    data->nativewindow.height = mode.h;

    if (vc_dispmanx_update_submit_sync(update_handle) < 0) {
        return SDL_SetError("vc_dispmanx couldn't commit update");
    }

    /* Create the GLES window surface */
    _this->gles_data->egl_surface =
        _this->gles_data->eglCreateWindowSurface(_this->gles_data->egl_display,
                                                 _this->gles_data->egl_config,
                                                 (NativeWindowType) &data->nativewindow,
                                                 NULL);

    if (_this->gles_data->egl_surface == EGL_NO_SURFACE) {
        return SDL_SetError("Couldn't create EGL window surface");
    }

    return 0;
}

void
RASPI_DestroyWindow(_THIS, SDL_Window * window)
{
    SDL_VideoData *data = (SDL_VideoData *) _this->driverdata;
    if (data->window != window) {
        SDL_SetError("Invalid window - Raspberry Pi video driver only supports one native window and it's not this one");
        return;
    }

    if (vc_dispmanx_display_close(data->display) < 0) {
        SDL_SetError("Couldn't close vc_dispmanx");
    }
}

#endif /* SDL_VIDEO_DRIVER_RASPI */

/* vi: set ts=4 sw=4 expandtab: */
