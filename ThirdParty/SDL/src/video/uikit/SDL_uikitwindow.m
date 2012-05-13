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

#if SDL_VIDEO_DRIVER_UIKIT

#include "SDL_syswm.h"
#include "SDL_video.h"
#include "SDL_mouse.h"
#include "SDL_assert.h"
#include "SDL_hints.h"
#include "../SDL_sysvideo.h"
#include "../SDL_pixels_c.h"
#include "../../events/SDL_events_c.h"

#include "SDL_uikitvideo.h"
#include "SDL_uikitevents.h"
#include "SDL_uikitwindow.h"
#import "SDL_uikitappdelegate.h"

#import "SDL_uikitopenglview.h"

#include <Foundation/Foundation.h>




static int SetupWindowData(_THIS, SDL_Window *window, UIWindow *uiwindow, SDL_bool created)
{
    SDL_VideoDisplay *display = SDL_GetDisplayForWindow(window);
    SDL_DisplayModeData *displaymodedata = (SDL_DisplayModeData *) display->current_mode.driverdata;
    SDL_DisplayData *displaydata = (SDL_DisplayData *) display->driverdata;
    SDL_WindowData *data;

    /* Allocate the window data */
    data = (SDL_WindowData *)SDL_malloc(sizeof(*data));
    if (!data) {
        SDL_OutOfMemory();
        return -1;
    }
    data->uiwindow = uiwindow;
    data->viewcontroller = nil;
    data->view = nil;

    /* Fill in the SDL window with the window data */
    {
        window->x = 0;
        window->y = 0;

        /* Get frame dimensions in pixels */
        int width = (int)(uiwindow.frame.size.width * displaymodedata->scale);
        int height = (int)(uiwindow.frame.size.height * displaymodedata->scale);

        /* We can pick either width or height here and we'll rotate the
           screen to match, so we pick the closest to what we wanted.
         */
        if (window->w >= window->h) {
            if (uiwindow.frame.size.width > uiwindow.frame.size.height) {
                window->w = width;
                window->h = height;
            } else {
                window->w = height;
                window->h = width;
            }
        } else {
            if (uiwindow.frame.size.width > uiwindow.frame.size.height) {
                window->w = height;
                window->h = width;
            } else {
                window->w = width;
                window->h = height;
            }
        }
    }

    window->driverdata = data;

    /* only one window on iOS, always shown */
    window->flags &= ~SDL_WINDOW_HIDDEN;
    window->flags |= SDL_WINDOW_SHOWN;

    // SDL_WINDOW_BORDERLESS controls whether status bar is hidden.
    // This is only set if the window is on the main screen. Other screens
    //  just force the window to have the borderless flag.
    if ([UIScreen mainScreen] != displaydata->uiscreen) {
        window->flags &= ~SDL_WINDOW_RESIZABLE;  // window is NEVER resizeable
        window->flags &= ~SDL_WINDOW_INPUT_FOCUS;  // never has input focus
        window->flags |= SDL_WINDOW_BORDERLESS;  // never has a status bar.
    } else {
        window->flags |= SDL_WINDOW_INPUT_FOCUS;  // always has input focus

        if (window->flags & (SDL_WINDOW_FULLSCREEN|SDL_WINDOW_BORDERLESS)) {
            [UIApplication sharedApplication].statusBarHidden = YES;
        } else {
            [UIApplication sharedApplication].statusBarHidden = NO;
        }

        //const UIDeviceOrientation o = [[UIDevice currentDevice] orientation];
        //const BOOL landscape = (o == UIDeviceOrientationLandscapeLeft) ||
        //                           (o == UIDeviceOrientationLandscapeRight);
        //const BOOL rotate = ( ((window->w > window->h) && (!landscape)) ||
        //                      ((window->w < window->h) && (landscape)) );

        // The View Controller will handle rotating the view when the
        //  device orientation changes. This will trigger resize events, if
        //  appropriate.
        SDL_uikitviewcontroller *controller;
        controller = [SDL_uikitviewcontroller alloc];
        data->viewcontroller = [controller initWithSDLWindow:window];
        [data->viewcontroller setTitle:@"SDL App"];  // !!! FIXME: hook up SDL_SetWindowTitle()
        // !!! FIXME: if (rotate), force a "resize" right at the start
    }

    return 0;
}

int
UIKit_CreateWindow(_THIS, SDL_Window *window)
{
    SDL_VideoDisplay *display = SDL_GetDisplayForWindow(window);
    SDL_DisplayData *data = (SDL_DisplayData *) display->driverdata;
    const BOOL external = ([UIScreen mainScreen] != data->uiscreen);

    // SDL currently puts this window at the start of display's linked list. We rely on this.
    SDL_assert(_this->windows == window);

    /* We currently only handle a single window per display on iOS */
    if (window->next != NULL) {
        SDL_SetError("Only one window allowed per display.");
        return -1;
    }

    // Non-mainscreen windows must be force to borderless, as there's no
    //  status bar there, and we want to get the right dimensions later in
    //  this function.
    if (external) {
        window->flags |= SDL_WINDOW_BORDERLESS;
    }

    // If monitor has a resolution of 0x0 (hasn't been explicitly set by the
    //  user, so it's in standby), try to force the display to a resolution
    //  that most closely matches the desired window size.
    if (SDL_UIKit_supports_multiple_displays) {
        const CGSize origsize = [[data->uiscreen currentMode] size];
        if ((origsize.width == 0.0f) && (origsize.height == 0.0f)) {
            if (display->num_display_modes == 0) {
                _this->GetDisplayModes(_this, display);
            }

            int i;
            const SDL_DisplayMode *bestmode = NULL;
            for (i = display->num_display_modes; i >= 0; i--) {
                const SDL_DisplayMode *mode = &display->display_modes[i];
                if ((mode->w >= window->w) && (mode->h >= window->h))
                    bestmode = mode;
            }

            if (bestmode) {
                SDL_DisplayModeData *modedata = (SDL_DisplayModeData *)bestmode->driverdata;
                [data->uiscreen setCurrentMode:modedata->uiscreenmode];

                // desktop_mode doesn't change here (the higher level will
                //  use it to set all the screens back to their defaults
                //  upon window destruction, SDL_Quit(), etc.
                display->current_mode = *bestmode;
            }
        }
    }

    /* ignore the size user requested, and make a fullscreen window */
    // !!! FIXME: can we have a smaller view?
    UIWindow *uiwindow = [UIWindow alloc];
    if (window->flags & (SDL_WINDOW_FULLSCREEN|SDL_WINDOW_BORDERLESS))
        uiwindow = [uiwindow initWithFrame:[data->uiscreen bounds]];
    else
        uiwindow = [uiwindow initWithFrame:[data->uiscreen applicationFrame]];

    // put the window on an external display if appropriate. This implicitly
    //  does [uiwindow setframe:[uiscreen bounds]], so don't do it on the
    //  main display, where we land by default, as that would eat the
    //  status bar real estate.
    if (external) {
        [uiwindow setScreen:data->uiscreen];
    }

    if (SetupWindowData(_this, window, uiwindow, SDL_TRUE) < 0) {
        [uiwindow release];
        return -1;
    }

    return 1;

}

void
UIKit_SetWindowFullscreen(_THIS, SDL_Window * window, SDL_VideoDisplay * display, SDL_bool fullscreen)
{
    SDL_DisplayData *displaydata = (SDL_DisplayData *) display->driverdata;
    SDL_DisplayModeData *displaymodedata = (SDL_DisplayModeData *) display->current_mode.driverdata;
    UIWindow *uiwindow = ((SDL_WindowData *) window->driverdata)->uiwindow;

    if (fullscreen) {
        [UIApplication sharedApplication].statusBarHidden = YES;
        uiwindow.frame = [displaydata->uiscreen bounds];
    } else {
        [UIApplication sharedApplication].statusBarHidden = NO;
        uiwindow.frame = [displaydata->uiscreen applicationFrame];
    }

    /* Get frame dimensions in pixels */
    int width = (int)(uiwindow.frame.size.width * displaymodedata->scale);
    int height = (int)(uiwindow.frame.size.height * displaymodedata->scale);

    /* We can pick either width or height here and we'll rotate the
       screen to match, so we pick the closest to what we wanted.
     */
    if (window->w >= window->h) {
        if (uiwindow.frame.size.width > uiwindow.frame.size.height) {
            window->w = width;
            window->h = height;
        } else {
            window->w = height;
            window->h = width;
        }
    } else {
        if (uiwindow.frame.size.width > uiwindow.frame.size.height) {
            window->w = height;
            window->h = width;
        } else {
            window->w = width;
            window->h = height;
        }
    }
}

void
UIKit_DestroyWindow(_THIS, SDL_Window * window)
{
    SDL_WindowData *data = (SDL_WindowData *)window->driverdata;
    if (data) {
        [data->viewcontroller release];
        [data->uiwindow release];
        SDL_free(data);
        window->driverdata = NULL;
    }
}

SDL_bool
UIKit_GetWindowWMInfo(_THIS, SDL_Window * window, SDL_SysWMinfo * info)
{
    UIWindow *uiwindow = ((SDL_WindowData *) window->driverdata)->uiwindow;

    if (info->version.major <= SDL_MAJOR_VERSION) {
        info->subsystem = SDL_SYSWM_UIKIT;
        info->info.uikit.window = uiwindow;
        return SDL_TRUE;
    } else {
        SDL_SetError("Application not compiled with SDL %d.%d\n",
                     SDL_MAJOR_VERSION, SDL_MINOR_VERSION);
        return SDL_FALSE;
    }
}

#endif /* SDL_VIDEO_DRIVER_UIKIT */

/* vi: set ts=4 sw=4 expandtab: */
