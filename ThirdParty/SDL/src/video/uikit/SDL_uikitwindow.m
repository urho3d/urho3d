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

@implementation SDL_uikitviewcontroller

- (id)initWithSDLWindow:(SDL_Window *)_window {
    if ((self = [self init]) == nil) {
        return nil;
    }
    self->window = _window;
    return self;
}

- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)orient {
    const char *orientationsCString;
    if ((orientationsCString = SDL_GetHint(SDL_HINT_ORIENTATIONS)) != NULL) {
        BOOL rotate = NO;
        NSString *orientationsNSString = [NSString stringWithCString:orientationsCString
                                                            encoding:NSUTF8StringEncoding];
        NSArray *orientations = [orientationsNSString componentsSeparatedByCharactersInSet:
                                 [NSCharacterSet characterSetWithCharactersInString:@" "]];
        
        switch (orient) {
            case UIInterfaceOrientationLandscapeLeft:
                rotate = [orientations containsObject:@"LandscapeLeft"];
                break;
                
            case UIInterfaceOrientationLandscapeRight:
                rotate = [orientations containsObject:@"LandscapeRight"];
                break;
                
            case UIInterfaceOrientationPortrait:
                rotate = [orientations containsObject:@"Portrait"];
                break;
                
            case UIInterfaceOrientationPortraitUpsideDown:
                rotate = [orientations containsObject:@"PortraitUpsideDown"];
                break;
                
            default: break;
        }
        
        return rotate;
    }

    if (self->window->flags & SDL_WINDOW_RESIZABLE) {
        return YES;  // any orientation is okay.
    }

    // If not resizable, allow device to orient to other matching sizes
    //  (that is, let the user turn the device upside down...same screen
    //   dimensions, but it lets the user place the device where it's most
    //   comfortable in relation to its physical buttons, headphone jack, etc).
    switch (orient) {
        case UIInterfaceOrientationLandscapeLeft:
        case UIInterfaceOrientationLandscapeRight:
            return (self->window->w >= self->window->h);

        case UIInterfaceOrientationPortrait:
        case UIInterfaceOrientationPortraitUpsideDown:
            return (self->window->h >= self->window->w);

        default: break;
    }

    return NO;  // Nothing else is acceptable.
}

- (void)loadView  {
    // do nothing.
}

// Send a resized event when the orientation changes.
- (void)didRotateFromInterfaceOrientation:(UIInterfaceOrientation)fromInterfaceOrientation {
    if ((self->window->flags & SDL_WINDOW_RESIZABLE) == 0) {
        return;   // don't care, we're just flipping over in this case.
    }

    const UIInterfaceOrientation toInterfaceOrientation = [self interfaceOrientation];
    SDL_WindowData *data = self->window->driverdata;
    UIWindow *uiwindow = data->uiwindow;
    UIScreen *uiscreen = [uiwindow screen];
    const int noborder = self->window->flags & SDL_WINDOW_BORDERLESS;
    CGRect frame = noborder ? [uiscreen bounds] : [uiscreen applicationFrame];
    const CGSize size = frame.size;
    int w, h;

    switch (toInterfaceOrientation) {
        case UIInterfaceOrientationPortrait:
        case UIInterfaceOrientationPortraitUpsideDown:
            w = (size.width < size.height) ? size.width : size.height;
            h = (size.width > size.height) ? size.width : size.height;
            break;

        case UIInterfaceOrientationLandscapeLeft:
        case UIInterfaceOrientationLandscapeRight:
            w = (size.width > size.height) ? size.width : size.height;
            h = (size.width < size.height) ? size.width : size.height;
            break;

        default:
            SDL_assert(0 && "Unexpected interface orientation!");
            return;
    }

    frame.size.width = w;
    frame.size.height = h;
    frame.origin.x = 0;
    frame.origin.y = 0;

    [uiwindow setFrame:frame];
    [data->view updateFrame];
    SDL_SendWindowEvent(self->window, SDL_WINDOWEVENT_RESIZED, w, h);
}

@end



static int SetupWindowData(_THIS, SDL_Window *window, UIWindow *uiwindow, SDL_bool created)
{
    SDL_VideoDisplay *display = SDL_GetDisplayForWindow(window);
    UIScreen *uiscreen = (UIScreen *) display->driverdata;
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
        window->w = (int)uiwindow.frame.size.width;
        window->h = (int)uiwindow.frame.size.height;
    }
    
    window->driverdata = data;

    // !!! FIXME: should we force this? Shouldn't specifying FULLSCREEN
    // !!! FIXME:  imply BORDERLESS?
    window->flags |= SDL_WINDOW_FULLSCREEN;        /* window is always fullscreen */
    window->flags |= SDL_WINDOW_SHOWN;            /* only one window on iOS, always shown */

    // SDL_WINDOW_BORDERLESS controls whether status bar is hidden.
    // This is only set if the window is on the main screen. Other screens
    //  just force the window to have the borderless flag.
    if ([UIScreen mainScreen] != uiscreen) {
        window->flags &= ~SDL_WINDOW_RESIZABLE;  // window is NEVER resizeable
        window->flags &= ~SDL_WINDOW_INPUT_FOCUS;  // never has input focus
        window->flags |= SDL_WINDOW_BORDERLESS;  // never has a status bar.
    } else {
        window->flags |= SDL_WINDOW_INPUT_FOCUS;  // always has input focus

        if (window->flags & SDL_WINDOW_BORDERLESS) {
            [UIApplication sharedApplication].statusBarHidden = YES;
        } else {
            [UIApplication sharedApplication].statusBarHidden = NO;
        }

        const UIDeviceOrientation o = [[UIDevice currentDevice] orientation];
        const BOOL landscape = (o == UIDeviceOrientationLandscapeLeft) ||
                                   (o == UIDeviceOrientationLandscapeRight);
        const BOOL rotate = ( ((window->w > window->h) && (!landscape)) ||
                              ((window->w < window->h) && (landscape)) );

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
    UIScreen *uiscreen = (UIScreen *) display->driverdata;
    const BOOL external = ([UIScreen mainScreen] != uiscreen);

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
        const CGSize origsize = [[uiscreen currentMode] size];
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
                UIScreenMode *uimode = (UIScreenMode *) bestmode->driverdata;
                [uiscreen setCurrentMode:uimode];
                display->desktop_mode = *bestmode;
                display->current_mode = *bestmode;
            }
        }
    }

    /* ignore the size user requested, and make a fullscreen window */
    // !!! FIXME: can we have a smaller view?
    UIWindow *uiwindow = [UIWindow alloc];
    if (window->flags & SDL_WINDOW_BORDERLESS)
        uiwindow = [uiwindow initWithFrame:[uiscreen bounds]];
    else
        uiwindow = [uiwindow initWithFrame:[uiscreen applicationFrame]];
    
    // put the window on an external display if appropriate. This implicitly
    //  does [uiwindow setframe:[uiscreen bounds]], so don't do it on the
    //  main display, where we land by default, as that would eat the
    //  status bar real estate.
    if (external) {
        [uiwindow setScreen:uiscreen];
    }

    if (SetupWindowData(_this, window, uiwindow, SDL_TRUE) < 0) {
        [uiwindow release];
        return -1;
    }    
    
    return 1;
    
}

void
UIKit_DestroyWindow(_THIS, SDL_Window * window) {
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

/* vi: set ts=4 sw=4 expandtab: */
