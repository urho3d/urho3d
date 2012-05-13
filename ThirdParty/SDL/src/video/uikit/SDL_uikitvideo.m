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

#import <UIKit/UIKit.h>

#include "SDL_video.h"
#include "SDL_mouse.h"
#include "../SDL_sysvideo.h"
#include "../SDL_pixels_c.h"
#include "../../events/SDL_events_c.h"

#include "SDL_uikitvideo.h"
#include "SDL_uikitevents.h"
#include "SDL_uikitwindow.h"
#include "SDL_uikitopengles.h"

#include "SDL_assert.h"

#define UIKITVID_DRIVER_NAME "uikit"

/* Initialization/Query functions */
static int UIKit_VideoInit(_THIS);
static void UIKit_GetDisplayModes(_THIS, SDL_VideoDisplay * sdl_display);
static int UIKit_SetDisplayMode(_THIS, SDL_VideoDisplay * display,
                                SDL_DisplayMode * mode);
static void UIKit_VideoQuit(_THIS);

BOOL SDL_UIKit_supports_multiple_displays = NO;

/* DUMMY driver bootstrap functions */

static int
UIKit_Available(void)
{
    return 1;
}

static void UIKit_DeleteDevice(SDL_VideoDevice * device)
{
    SDL_free(device);
}

static SDL_VideoDevice *
UIKit_CreateDevice(int devindex)
{
    SDL_VideoDevice *device;

    /* Initialize all variables that we clean on shutdown */
    device = (SDL_VideoDevice *) SDL_calloc(1, sizeof(SDL_VideoDevice));
    if (!device) {
        SDL_OutOfMemory();
        if (device) {
            SDL_free(device);
        }
        return (0);
    }

    /* Set the function pointers */
    device->VideoInit = UIKit_VideoInit;
    device->VideoQuit = UIKit_VideoQuit;
    device->GetDisplayModes = UIKit_GetDisplayModes;
    device->SetDisplayMode = UIKit_SetDisplayMode;
    device->PumpEvents = UIKit_PumpEvents;
    device->CreateWindow = UIKit_CreateWindow;
    device->SetWindowFullscreen = UIKit_SetWindowFullscreen;
    device->DestroyWindow = UIKit_DestroyWindow;
    device->GetWindowWMInfo = UIKit_GetWindowWMInfo;


    /* OpenGL (ES) functions */
    device->GL_MakeCurrent        = UIKit_GL_MakeCurrent;
    device->GL_SwapWindow        = UIKit_GL_SwapWindow;
    device->GL_CreateContext    = UIKit_GL_CreateContext;
    device->GL_DeleteContext    = UIKit_GL_DeleteContext;
    device->GL_GetProcAddress   = UIKit_GL_GetProcAddress;
    device->GL_LoadLibrary        = UIKit_GL_LoadLibrary;
    device->free = UIKit_DeleteDevice;

    device->gl_config.accelerated = 1;

    return device;
}

VideoBootStrap UIKIT_bootstrap = {
    UIKITVID_DRIVER_NAME, "SDL UIKit video driver",
    UIKit_Available, UIKit_CreateDevice
};


/*
!!! FIXME:

The main screen should list a AxB mode for portrait orientation, and then
 also list BxA for landscape mode. When setting a given resolution, we should
 rotate the view's transform appropriately (extra credit if you check the
 accelerometer and rotate the display so it's never upside down).

  http://iphonedevelopment.blogspot.com/2008/10/starting-in-landscape-mode-without.html

*/

static int
UIKit_AllocateDisplayModeData(SDL_DisplayMode * mode,
    UIScreenMode * uiscreenmode, CGFloat scale)
{
    SDL_DisplayModeData *data = NULL;
    
    if (uiscreenmode != nil) {
        /* Allocate the display mode data */
        data = (SDL_DisplayModeData *) SDL_malloc(sizeof(*data));
        if (!data) {
            SDL_OutOfMemory();
            return -1;
        }
        
        data->uiscreenmode = uiscreenmode;
        [data->uiscreenmode retain];
        
        data->scale = scale;
    }
    
    mode->driverdata = data;
    
    return 0;
}

static void
UIKit_FreeDisplayModeData(SDL_DisplayMode * mode)
{
    if (!SDL_UIKit_supports_multiple_displays) {
        // Not on at least iPhoneOS 3.2 (versions prior to iPad).
        SDL_assert(mode->driverdata == NULL);
    } else if (mode->driverdata != NULL) {
        SDL_DisplayModeData *data = (SDL_DisplayModeData *)mode->driverdata;
        [data->uiscreenmode release];
        SDL_free(data);
        mode->driverdata = NULL;
    }
}

static int
UIKit_AddSingleDisplayMode(SDL_VideoDisplay * display, int w, int h,
    UIScreenMode * uiscreenmode, CGFloat scale)
{
    SDL_DisplayMode mode;
    SDL_zero(mode);
    
    mode.format = SDL_PIXELFORMAT_ABGR8888;
    mode.refresh_rate = 0;
    if (UIKit_AllocateDisplayModeData(&mode, uiscreenmode, scale) < 0) {
        return -1;
    }
    
    mode.w = w;
    mode.h = h;
    if (SDL_AddDisplayMode(display, &mode)) {
        return 0;
    }
    
    // Failure case; free resources
    SDL_DisplayModeData *data = (SDL_DisplayModeData *) mode.driverdata;
    
    if (data != NULL) {
        [data->uiscreenmode release];
        SDL_free(data);
    }

    return -1;
}

static int
UIKit_AddDisplayMode(SDL_VideoDisplay * display, int w, int h, CGFloat scale,
                     UIScreenMode * uiscreenmode, BOOL rotated)
{
    if (UIKit_AddSingleDisplayMode(display, w, h, uiscreenmode, scale) < 0) {
        return -1;
    }
    
    if (rotated) {
        // Add the rotated version
        if (UIKit_AddSingleDisplayMode(display, h, w, uiscreenmode, scale) < 0) {
            return -1;
        }
    }
    
    return 0;
}

static void
UIKit_GetDisplayModes(_THIS, SDL_VideoDisplay * display)
{
    SDL_DisplayData *data = (SDL_DisplayData *) display->driverdata;

    if (SDL_UIKit_supports_multiple_displays) {
        // availableModes showed up in 3.2 (the iPad and later). We should only
        //  land here for at least that version of the OS.
        for (UIScreenMode *uimode in [data->uiscreen availableModes]) {
            BOOL mainscreen = (data->uiscreen == [UIScreen mainScreen]);
            CGSize size = [uimode size];
            int w = (int)size.width;
            int h = (int)size.height;
            
            // Add the native screen resolution.
            UIKit_AddDisplayMode(display, w, h, data->scale, uimode, mainscreen);
            
            if (data->scale != 1.0f) {
                // Add the native screen resolution divided by its scale.
                // This is so devices capable of e.g. 640x960 also advertise
                // 320x480.
                UIKit_AddDisplayMode(display,
                    (int)(w / data->scale), (int)(h / data->scale),
                    1.0f, uimode, mainscreen);
            }
        }
    } else {
        const CGRect rect = [data->uiscreen bounds];
        UIKit_AddDisplayMode(display,
            (int)rect.size.width, (int)rect.size.height,
            1.0f, nil, YES);
    } 
}


static int
UIKit_AddDisplay(UIScreen *uiscreen, CGSize size)
{
    // When dealing with UIKit all coordinates are specified in terms of
    // what Apple refers to as points. On earlier devices without the
    // so called "Retina" display, there is a one to one mapping between
    // points and pixels. In other cases [UIScreen scale] indicates the
    // relationship between points and pixels. Since SDL has no notion
    // of points, we must compensate in all cases where dealing with such
    // units.
    CGFloat scale;
    if ([UIScreen instancesRespondToSelector:@selector(scale)]) {
        scale = [uiscreen scale]; // iOS >= 4.0
    } else {
        scale = 1.0f; // iOS < 4.0
    }
	
    SDL_VideoDisplay display;
    SDL_DisplayMode mode;
    SDL_zero(mode);
    mode.format = SDL_PIXELFORMAT_ABGR8888;
    mode.w = (int)(size.width * scale);
    mode.h = (int)(size.height * scale);
    mode.refresh_rate = 0;
 
    UIScreenMode * uiscreenmode = nil;
    // UIScreenMode showed up in 3.2 (the iPad and later). We're
    //  misusing this supports_multiple_displays flag here for that.
    if (SDL_UIKit_supports_multiple_displays) {
        uiscreenmode = [uiscreen currentMode];
    }
    
    if (UIKit_AllocateDisplayModeData(&mode, uiscreenmode, scale) < 0) {
        return -1;
    }

    SDL_zero(display);
    display.desktop_mode = mode;
    display.current_mode = mode;

    /* Allocate the display data */
    SDL_DisplayData *data = (SDL_DisplayData *) SDL_malloc(sizeof(*data));
    if (!data) {
        SDL_OutOfMemory();
        UIKit_FreeDisplayModeData(&display.desktop_mode);
        return -1;
    }
	
    [uiscreen retain];
    data->uiscreen = uiscreen;
    data->scale = scale;
	
    display.driverdata = data;
    SDL_AddVideoDisplay(&display);
    
    return 0;
}


int
UIKit_VideoInit(_THIS)
{
    _this->gl_config.driver_loaded = 1;

    // this tells us whether we are running on ios >= 3.2
    SDL_UIKit_supports_multiple_displays = [UIScreen instancesRespondToSelector:@selector(currentMode)];

    // Add the main screen.
    UIScreen *uiscreen = [UIScreen mainScreen];
    const CGSize size = [uiscreen bounds].size;

    if (UIKit_AddDisplay(uiscreen, size) < 0) {
        return -1;
    }

    // If this is iPhoneOS < 3.2, all devices are one screen, 320x480 pixels.
    //  The iPad added both a larger main screen and the ability to use
    //  external displays. So, add the other displays (screens in UI speak).
    if (SDL_UIKit_supports_multiple_displays) {
        for (UIScreen *uiscreen in [UIScreen screens]) {
            // Only add the other screens
            if (uiscreen != [UIScreen mainScreen]) {
                const CGSize size = [uiscreen bounds].size;
                if (UIKit_AddDisplay(uiscreen, size) < 0) {
                    return -1;
                }
            }
        }
    }

    /* We're done! */
    return 0;
}

static int
UIKit_SetDisplayMode(_THIS, SDL_VideoDisplay * display, SDL_DisplayMode * mode)
{
    SDL_DisplayData *data = (SDL_DisplayData *) display->driverdata;
    if (!SDL_UIKit_supports_multiple_displays) {
        // Not on at least iPhoneOS 3.2 (versions prior to iPad).
        SDL_assert(mode->driverdata == NULL);
    } else {
        SDL_DisplayModeData *modedata = (SDL_DisplayModeData *)mode->driverdata;
        [data->uiscreen setCurrentMode:modedata->uiscreenmode];

        CGSize size = [modedata->uiscreenmode size];
        if (size.width >= size.height) {
            [[UIApplication sharedApplication] setStatusBarOrientation:UIInterfaceOrientationLandscapeRight animated:NO];
        } else {
            [[UIApplication sharedApplication] setStatusBarOrientation:UIInterfaceOrientationPortrait animated:NO];
        }
    }

    return 0;
}

void
UIKit_VideoQuit(_THIS)
{
    // Release Objective-C objects, so higher level doesn't free() them.
    int i, j;
    for (i = 0; i < _this->num_displays; i++) {
        SDL_VideoDisplay *display = &_this->displays[i];
        SDL_DisplayData *data = (SDL_DisplayData *) display->driverdata;
        [data->uiscreen release];
        SDL_free(data);
        display->driverdata = NULL;
        UIKit_FreeDisplayModeData(&display->desktop_mode);
        for (j = 0; j < display->num_display_modes; j++) {
            SDL_DisplayMode *mode = &display->display_modes[j];
            UIKit_FreeDisplayModeData(mode);
        }
    }
}

#endif /* SDL_VIDEO_DRIVER_UIKIT */

/* vi: set ts=4 sw=4 expandtab: */
