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
#include "SDL_timer.h"  /* For SDL_GetTicks() */
#include "../SDL_sysvideo.h"
#include "../../events/SDL_keyboard_c.h"
#include "../../events/SDL_mouse_c.h"
#include "../../events/SDL_touch_c.h"
#include "../../events/SDL_windowevents_c.h"
#include "SDL_cocoavideo.h"
#include "SDL_cocoashape.h"
#include "SDL_cocoamouse.h"


static Uint32 s_moveHack;

static __inline__ void ConvertNSRect(NSRect *r)
{
    r->origin.y = CGDisplayPixelsHigh(kCGDirectMainDisplay) - r->origin.y - r->size.height;
}

@implementation Cocoa_WindowListener

- (void)listen:(SDL_WindowData *)data
{
    NSNotificationCenter *center;
    NSWindow *window = data->nswindow;
    NSView *view = [window contentView];

    _data = data;

    center = [NSNotificationCenter defaultCenter];

    if ([window delegate] != nil) {
        [center addObserver:self selector:@selector(windowDidExpose:) name:NSWindowDidExposeNotification object:window];
        [center addObserver:self selector:@selector(windowDidMove:) name:NSWindowDidMoveNotification object:window];
        [center addObserver:self selector:@selector(windowDidResize:) name:NSWindowDidResizeNotification object:window];
        [center addObserver:self selector:@selector(windowDidMiniaturize:) name:NSWindowDidMiniaturizeNotification object:window];
        [center addObserver:self selector:@selector(windowDidDeminiaturize:) name:NSWindowDidDeminiaturizeNotification object:window];
        [center addObserver:self selector:@selector(windowDidBecomeKey:) name:NSWindowDidBecomeKeyNotification object:window];
        [center addObserver:self selector:@selector(windowDidResignKey:) name:NSWindowDidResignKeyNotification object:window];
    } else {
        [window setDelegate:self];
    }

    [window setNextResponder:self];
    [window setAcceptsMouseMovedEvents:YES];

    [view setNextResponder:self];
#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_6
    [view setAcceptsTouchEvents:YES];
#endif
}

- (void)close
{
    NSNotificationCenter *center;
    NSWindow *window = _data->nswindow;
    NSView *view = [window contentView];

    center = [NSNotificationCenter defaultCenter];

    if ([window delegate] != self) {
        [center removeObserver:self name:NSWindowDidExposeNotification object:window];
        [center removeObserver:self name:NSWindowDidMoveNotification object:window];
        [center removeObserver:self name:NSWindowDidResizeNotification object:window];
        [center removeObserver:self name:NSWindowDidMiniaturizeNotification object:window];
        [center removeObserver:self name:NSWindowDidDeminiaturizeNotification object:window];
        [center removeObserver:self name:NSWindowDidBecomeKeyNotification object:window];
        [center removeObserver:self name:NSWindowDidResignKeyNotification object:window];
    } else {
        [window setDelegate:nil];
    }

    if ([window nextResponder] == self) {
        [window setNextResponder:nil];
    }
    if ([view nextResponder] == self) {
        [view setNextResponder:nil];
    }
}

- (BOOL)windowShouldClose:(id)sender
{
    SDL_SendWindowEvent(_data->window, SDL_WINDOWEVENT_CLOSE, 0, 0);
    return NO;
}

- (void)windowDidExpose:(NSNotification *)aNotification
{
    SDL_SendWindowEvent(_data->window, SDL_WINDOWEVENT_EXPOSED, 0, 0);
}

- (void)windowDidMove:(NSNotification *)aNotification
{
    int x, y;
    SDL_Window *window = _data->window;
    NSWindow *nswindow = _data->nswindow;
    NSRect rect = [nswindow contentRectForFrameRect:[nswindow frame]];
    ConvertNSRect(&rect);

    if (s_moveHack) {
        SDL_bool blockMove = ((SDL_GetTicks() - s_moveHack) < 500);

        s_moveHack = 0;

        if (blockMove) {
            /* Cocoa is adjusting the window in response to a mode change */
            rect.origin.x = window->x;
            rect.origin.y = window->y;
            ConvertNSRect(&rect);
            [nswindow setFrameOrigin:rect.origin];
            return;
        }
    }

    x = (int)rect.origin.x;
    y = (int)rect.origin.y;
    SDL_SendWindowEvent(window, SDL_WINDOWEVENT_MOVED, x, y);
}

- (void)windowDidResize:(NSNotification *)aNotification
{
    int w, h;
    NSRect rect = [_data->nswindow contentRectForFrameRect:[_data->nswindow frame]];
    w = (int)rect.size.width;
    h = (int)rect.size.height;
    if (SDL_IsShapedWindow(_data->window))
        Cocoa_ResizeWindowShape(_data->window);
    SDL_SendWindowEvent(_data->window, SDL_WINDOWEVENT_RESIZED, w, h);
}

- (void)windowDidMiniaturize:(NSNotification *)aNotification
{
    SDL_SendWindowEvent(_data->window, SDL_WINDOWEVENT_MINIMIZED, 0, 0);
}

- (void)windowDidDeminiaturize:(NSNotification *)aNotification
{
    SDL_SendWindowEvent(_data->window, SDL_WINDOWEVENT_RESTORED, 0, 0);
}

- (void)windowDidBecomeKey:(NSNotification *)aNotification
{
    SDL_Window *window = _data->window;

    /* We're going to get keyboard events, since we're key. */
    SDL_SetKeyboardFocus(window);

    /* If we just gained focus we need the updated mouse position */
    {
        NSPoint point;
        int x, y;

        point = [_data->nswindow mouseLocationOutsideOfEventStream];
        x = (int)point.x;
        y = (int)(window->h - point.y);

        if (x >= 0 && x < window->w && y >= 0 && y < window->h) {
            if (SDL_GetMouseFocus() != window) {
                [self mouseEntered:nil];
            }
            SDL_SendMouseMotion(window, 0, x, y);
        }
    }

    /* Check to see if someone updated the clipboard */
    Cocoa_CheckClipboardUpdate(_data->videodata);
}

- (void)windowDidResignKey:(NSNotification *)aNotification
{
    /* Some other window will get mouse events, since we're not key. */
    if (SDL_GetMouseFocus() == _data->window) {
        SDL_SetMouseFocus(NULL);
    }

    /* Some other window will get keyboard events, since we're not key. */
    if (SDL_GetKeyboardFocus() == _data->window) {
        SDL_SetKeyboardFocus(NULL);
    }
}

- (void)mouseDown:(NSEvent *)theEvent
{
    int button;

    switch ([theEvent buttonNumber]) {
    case 0:
        button = SDL_BUTTON_LEFT;
        break;
    case 1:
        button = SDL_BUTTON_RIGHT;
        break;
    case 2:
        button = SDL_BUTTON_MIDDLE;
        break;
    default:
        button = [theEvent buttonNumber] + 1;
        break;
    }
    SDL_SendMouseButton(_data->window, SDL_PRESSED, button);
}

- (void)rightMouseDown:(NSEvent *)theEvent
{
    [self mouseDown:theEvent];
}

- (void)otherMouseDown:(NSEvent *)theEvent
{
    [self mouseDown:theEvent];
}

- (void)mouseUp:(NSEvent *)theEvent
{
    int button;

    switch ([theEvent buttonNumber]) {
    case 0:
        button = SDL_BUTTON_LEFT;
        break;
    case 1:
        button = SDL_BUTTON_RIGHT;
        break;
    case 2:
        button = SDL_BUTTON_MIDDLE;
        break;
    default:
        button = [theEvent buttonNumber] + 1;
        break;
    }
    SDL_SendMouseButton(_data->window, SDL_RELEASED, button);
}

- (void)rightMouseUp:(NSEvent *)theEvent
{
    [self mouseUp:theEvent];
}

- (void)otherMouseUp:(NSEvent *)theEvent
{
    [self mouseUp:theEvent];
}

- (void)mouseEntered:(NSEvent *)theEvent
{
    SDL_Mouse *mouse = SDL_GetMouse();

    SDL_SetMouseFocus(_data->window);

    SDL_SetCursor(NULL);
}

- (void)mouseExited:(NSEvent *)theEvent
{
    SDL_Window *window = _data->window;

    if (SDL_GetMouseFocus() == window) {
        if (window->flags & SDL_WINDOW_INPUT_GRABBED) {
            int x, y;
            NSPoint point;
            CGPoint cgpoint;

            point = [theEvent locationInWindow];
            point.y = window->h - point.y;

            SDL_SendMouseMotion(window, 0, (int)point.x, (int)point.y);
            SDL_GetMouseState(&x, &y);
            cgpoint.x = window->x + x;
            cgpoint.y = window->y + y;
            CGDisplayMoveCursorToPoint(kCGDirectMainDisplay, cgpoint);
        } else {
            SDL_SetMouseFocus(NULL);

            [[NSCursor arrowCursor] set];
            [NSCursor unhide];
        }
    }
}

- (void)mouseMoved:(NSEvent *)theEvent
{
    SDL_Mouse *mouse = SDL_GetMouse();
    SDL_Window *window = _data->window;
    NSPoint point;
    int x, y;

    if (mouse->relative_mode) {
        return;
    }

    point = [theEvent locationInWindow];
    x = (int)point.x;
    y = (int)(window->h - point.y);

    if (x < 0 || x >= window->w || y < 0 || y >= window->h) {
        if (SDL_GetMouseFocus() == window) {
            [self mouseExited:theEvent];
        }
    } else {
        if (SDL_GetMouseFocus() != window) {
            [self mouseEntered:theEvent];
        }
        SDL_SendMouseMotion(window, 0, x, y);
    }
}

- (void)mouseDragged:(NSEvent *)theEvent
{
    [self mouseMoved:theEvent];
}

- (void)rightMouseDragged:(NSEvent *)theEvent
{
    [self mouseMoved:theEvent];
}

- (void)otherMouseDragged:(NSEvent *)theEvent
{
    [self mouseMoved:theEvent];
}

- (void)scrollWheel:(NSEvent *)theEvent
{
    Cocoa_HandleMouseWheel(_data->window, theEvent);
}

- (void)touchesBeganWithEvent:(NSEvent *) theEvent
{
    [self handleTouches:COCOA_TOUCH_DOWN withEvent:theEvent];
}

- (void)touchesMovedWithEvent:(NSEvent *) theEvent
{
    [self handleTouches:COCOA_TOUCH_MOVE withEvent:theEvent];
}

- (void)touchesEndedWithEvent:(NSEvent *) theEvent
{
    [self handleTouches:COCOA_TOUCH_UP withEvent:theEvent];
}

- (void)touchesCancelledWithEvent:(NSEvent *) theEvent
{
    [self handleTouches:COCOA_TOUCH_CANCELLED withEvent:theEvent];
}

- (void)handleTouches:(cocoaTouchType)type withEvent:(NSEvent *)event
{
#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_6
    NSSet *touches = 0;
    NSEnumerator *enumerator;
    NSTouch *touch;

    switch (type) {
        case COCOA_TOUCH_DOWN:
            touches = [event touchesMatchingPhase:NSTouchPhaseBegan inView:nil];
            break;
        case COCOA_TOUCH_UP:
        case COCOA_TOUCH_CANCELLED:
            touches = [event touchesMatchingPhase:NSTouchPhaseEnded inView:nil];
            break;
        case COCOA_TOUCH_MOVE:
            touches = [event touchesMatchingPhase:NSTouchPhaseMoved inView:nil];
            break;
    }

    enumerator = [touches objectEnumerator];
    touch = (NSTouch*)[enumerator nextObject];
    while (touch) {
        SDL_TouchID touchId = (SDL_TouchID)[touch device];
        if (!SDL_GetTouch(touchId)) {
            SDL_Touch touch;

            touch.id = touchId;
            touch.x_min = 0;
            touch.x_max = 1;
            touch.native_xres = touch.x_max - touch.x_min;
            touch.y_min = 0;
            touch.y_max = 1;
            touch.native_yres = touch.y_max - touch.y_min;
            touch.pressure_min = 0;
            touch.pressure_max = 1;
            touch.native_pressureres = touch.pressure_max - touch.pressure_min;
            
            if (SDL_AddTouch(&touch, "") < 0) {
                return;
            }
        } 

        SDL_FingerID fingerId = (SDL_FingerID)[touch identity];
        float x = [touch normalizedPosition].x;
        float y = [touch normalizedPosition].y;
        /* Make the origin the upper left instead of the lower left */
        y = 1.0f - y;

        switch (type) {
        case COCOA_TOUCH_DOWN:
            SDL_SendFingerDown(touchId, fingerId, SDL_TRUE, x, y, 1);
            break;
        case COCOA_TOUCH_UP:
        case COCOA_TOUCH_CANCELLED:
            SDL_SendFingerDown(touchId, fingerId, SDL_FALSE, x, y, 1);
            break;
        case COCOA_TOUCH_MOVE:
            SDL_SendTouchMotion(touchId, fingerId, SDL_FALSE, x, y, 1);
            break;
        }
        
        touch = (NSTouch*)[enumerator nextObject];
    }
#endif /* MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_6 */
}

@end

@interface SDLWindow : NSWindow
/* These are needed for borderless/fullscreen windows */
- (BOOL)canBecomeKeyWindow;
- (BOOL)canBecomeMainWindow;
@end

@implementation SDLWindow
- (BOOL)canBecomeKeyWindow
{
    return YES;
}

- (BOOL)canBecomeMainWindow
{
    return YES;
}
@end

@interface SDLView : NSView
/* The default implementation doesn't pass rightMouseDown to responder chain */
- (void)rightMouseDown:(NSEvent *)theEvent;
@end

@implementation SDLView
- (void)rightMouseDown:(NSEvent *)theEvent
{
    [[self nextResponder] rightMouseDown:theEvent];
}
@end

static unsigned int
GetWindowStyle(SDL_Window * window)
{
    unsigned int style;

	if (window->flags & SDL_WINDOW_FULLSCREEN) {
        style = NSBorderlessWindowMask;
	} else {
		if (window->flags & SDL_WINDOW_BORDERLESS) {
			style = NSBorderlessWindowMask;
		} else {
			style = (NSTitledWindowMask|NSClosableWindowMask|NSMiniaturizableWindowMask);
		}
		if (window->flags & SDL_WINDOW_RESIZABLE) {
			style |= NSResizableWindowMask;
		}
	}
    return style;
}

static int
SetupWindowData(_THIS, SDL_Window * window, NSWindow *nswindow, SDL_bool created)
{
    NSAutoreleasePool *pool;
    SDL_VideoData *videodata = (SDL_VideoData *) _this->driverdata;
    SDL_WindowData *data;

    /* Allocate the window data */
    data = (SDL_WindowData *) SDL_calloc(1, sizeof(*data));
    if (!data) {
        SDL_OutOfMemory();
        return -1;
    }
    data->window = window;
    data->nswindow = nswindow;
    data->created = created;
    data->videodata = videodata;

    pool = [[NSAutoreleasePool alloc] init];

    /* Create an event listener for the window */
    data->listener = [[Cocoa_WindowListener alloc] init];

    /* Fill in the SDL window with the window data */
    {
        NSRect rect = [nswindow contentRectForFrameRect:[nswindow frame]];
        NSView *contentView = [[SDLView alloc] initWithFrame:rect];
        [nswindow setContentView: contentView];
        [contentView release];

        ConvertNSRect(&rect);
        window->x = (int)rect.origin.x;
        window->y = (int)rect.origin.y;
        window->w = (int)rect.size.width;
        window->h = (int)rect.size.height;
    }

    /* Set up the listener after we create the view */
    [data->listener listen:data];

    if ([nswindow isVisible]) {
        window->flags |= SDL_WINDOW_SHOWN;
    } else {
        window->flags &= ~SDL_WINDOW_SHOWN;
    }
    {
        unsigned int style = [nswindow styleMask];

        if (style == NSBorderlessWindowMask) {
            window->flags |= SDL_WINDOW_BORDERLESS;
        } else {
            window->flags &= ~SDL_WINDOW_BORDERLESS;
        }
        if (style & NSResizableWindowMask) {
            window->flags |= SDL_WINDOW_RESIZABLE;
        } else {
            window->flags &= ~SDL_WINDOW_RESIZABLE;
        }
    }
    /* isZoomed always returns true if the window is not resizable */
    if ((window->flags & SDL_WINDOW_RESIZABLE) && [nswindow isZoomed]) {
        window->flags |= SDL_WINDOW_MAXIMIZED;
    } else {
        window->flags &= ~SDL_WINDOW_MAXIMIZED;
    }
    if ([nswindow isMiniaturized]) {
        window->flags |= SDL_WINDOW_MINIMIZED;
    } else {
        window->flags &= ~SDL_WINDOW_MINIMIZED;
    }
    if ([nswindow isKeyWindow]) {
        window->flags |= SDL_WINDOW_INPUT_FOCUS;
        SDL_SetKeyboardFocus(data->window);
    }

    /* All done! */
    [pool release];
    window->driverdata = data;
    return 0;
}

int
Cocoa_CreateWindow(_THIS, SDL_Window * window)
{
    NSAutoreleasePool *pool = [[NSAutoreleasePool alloc] init];
    NSWindow *nswindow;
    SDL_VideoDisplay *display = SDL_GetDisplayForWindow(window);
    NSRect rect;
    SDL_Rect bounds;
    unsigned int style;

    Cocoa_GetDisplayBounds(_this, display, &bounds);
    rect.origin.x = window->x;
    rect.origin.y = window->y;
    rect.size.width = window->w;
    rect.size.height = window->h;
    ConvertNSRect(&rect);

    style = GetWindowStyle(window);

    /* Figure out which screen to place this window */
    NSArray *screens = [NSScreen screens];
    NSScreen *screen = nil;
    NSScreen *candidate;
    int i, count = [screens count];
    for (i = 0; i < count; ++i) {
        candidate = [screens objectAtIndex:i];
        NSRect screenRect = [candidate frame];
        if (rect.origin.x >= screenRect.origin.x &&
            rect.origin.x < screenRect.origin.x + screenRect.size.width &&
            rect.origin.y >= screenRect.origin.y &&
            rect.origin.y < screenRect.origin.y + screenRect.size.height) {
            screen = candidate;
            rect.origin.x -= screenRect.origin.x;
            rect.origin.y -= screenRect.origin.y;
        }
    }
    nswindow = [[SDLWindow alloc] initWithContentRect:rect styleMask:style backing:NSBackingStoreBuffered defer:YES screen:screen];

    [pool release];

    if (SetupWindowData(_this, window, nswindow, SDL_TRUE) < 0) {
        [nswindow release];
        return -1;
    }
    return 0;
}

int
Cocoa_CreateWindowFrom(_THIS, SDL_Window * window, const void *data)
{
    NSAutoreleasePool *pool;
    NSWindow *nswindow = (NSWindow *) data;
    NSString *title;

    pool = [[NSAutoreleasePool alloc] init];

    /* Query the title from the existing window */
    title = [nswindow title];
    if (title) {
        window->title = SDL_strdup([title UTF8String]);
    }

    [pool release];

    return SetupWindowData(_this, window, nswindow, SDL_FALSE);
}

void
Cocoa_SetWindowTitle(_THIS, SDL_Window * window)
{
    NSAutoreleasePool *pool = [[NSAutoreleasePool alloc] init];
    NSWindow *nswindow = ((SDL_WindowData *) window->driverdata)->nswindow;
    NSString *string;

    if(window->title) {
        string = [[NSString alloc] initWithUTF8String:window->title];
    } else {
        string = [[NSString alloc] init];
    }
    [nswindow setTitle:string];
    [string release];

    [pool release];
}

void
Cocoa_SetWindowIcon(_THIS, SDL_Window * window, SDL_Surface * icon)
{
    NSAutoreleasePool *pool = [[NSAutoreleasePool alloc] init];
    NSImage *nsimage = Cocoa_CreateImage(icon);

    if (nsimage) {
        [NSApp setApplicationIconImage:nsimage];
    }

    [pool release];
}

void
Cocoa_SetWindowPosition(_THIS, SDL_Window * window)
{
    NSAutoreleasePool *pool = [[NSAutoreleasePool alloc] init];
    NSWindow *nswindow = ((SDL_WindowData *) window->driverdata)->nswindow;
    NSRect rect;
    Uint32 moveHack;

    rect.origin.x = window->x;
    rect.origin.y = window->y;
    rect.size.width = window->w;
    rect.size.height = window->h;
    ConvertNSRect(&rect);

    moveHack = s_moveHack;
    s_moveHack = 0;
    [nswindow setFrameOrigin:rect.origin];
    s_moveHack = moveHack;

    [pool release];
}

void
Cocoa_SetWindowSize(_THIS, SDL_Window * window)
{
    NSAutoreleasePool *pool = [[NSAutoreleasePool alloc] init];
    NSWindow *nswindow = ((SDL_WindowData *) window->driverdata)->nswindow;
    NSSize size;

    size.width = window->w;
    size.height = window->h;
    [nswindow setContentSize:size];
    [pool release];
}

void
Cocoa_ShowWindow(_THIS, SDL_Window * window)
{
    NSAutoreleasePool *pool = [[NSAutoreleasePool alloc] init];
    NSWindow *nswindow = ((SDL_WindowData *) window->driverdata)->nswindow;

    if (![nswindow isMiniaturized]) {
        [nswindow makeKeyAndOrderFront:nil];
    }
    [pool release];
}

void
Cocoa_HideWindow(_THIS, SDL_Window * window)
{
    NSAutoreleasePool *pool = [[NSAutoreleasePool alloc] init];
    NSWindow *nswindow = ((SDL_WindowData *) window->driverdata)->nswindow;

    [nswindow orderOut:nil];
    [pool release];
}

void
Cocoa_RaiseWindow(_THIS, SDL_Window * window)
{
    NSAutoreleasePool *pool = [[NSAutoreleasePool alloc] init];
    NSWindow *nswindow = ((SDL_WindowData *) window->driverdata)->nswindow;

    [nswindow makeKeyAndOrderFront:nil];
    [pool release];
}

void
Cocoa_MaximizeWindow(_THIS, SDL_Window * window)
{
    NSAutoreleasePool *pool = [[NSAutoreleasePool alloc] init];
    NSWindow *nswindow = ((SDL_WindowData *) window->driverdata)->nswindow;

    [nswindow zoom:nil];
    [pool release];
}

void
Cocoa_MinimizeWindow(_THIS, SDL_Window * window)
{
    NSAutoreleasePool *pool = [[NSAutoreleasePool alloc] init];
    NSWindow *nswindow = ((SDL_WindowData *) window->driverdata)->nswindow;

    [nswindow miniaturize:nil];
    [pool release];
}

void
Cocoa_RestoreWindow(_THIS, SDL_Window * window)
{
    NSAutoreleasePool *pool = [[NSAutoreleasePool alloc] init];
    NSWindow *nswindow = ((SDL_WindowData *) window->driverdata)->nswindow;

    if ([nswindow isMiniaturized]) {
        [nswindow deminiaturize:nil];
    } else if ((window->flags & SDL_WINDOW_RESIZABLE) && [nswindow isZoomed]) {
        [nswindow zoom:nil];
    }
    [pool release];
}

static NSWindow *
Cocoa_RebuildWindow(SDL_WindowData * data, NSWindow * nswindow, unsigned style)
{
    if (!data->created) {
        /* Don't mess with other people's windows... */
        return nswindow;
    }

    [data->listener close];
    data->nswindow = [[SDLWindow alloc] initWithContentRect:[[nswindow contentView] frame] styleMask:style backing:NSBackingStoreBuffered defer:YES screen:[nswindow screen]];
    [data->nswindow setContentView:[nswindow contentView]];
    [data->listener listen:data];

    [nswindow close];

    return data->nswindow;
}

void
Cocoa_SetWindowFullscreen(_THIS, SDL_Window * window, SDL_VideoDisplay * display, SDL_bool fullscreen)
{
    NSAutoreleasePool *pool = [[NSAutoreleasePool alloc] init];
    SDL_WindowData *data = (SDL_WindowData *) window->driverdata;
    NSWindow *nswindow = data->nswindow;
    NSRect rect;

    /* The view responder chain gets messed with during setStyleMask */
    if ([[nswindow contentView] nextResponder] == data->listener) {
        [[nswindow contentView] setNextResponder:nil];
    }

    if (fullscreen) {
        SDL_Rect bounds;

        Cocoa_GetDisplayBounds(_this, display, &bounds);
        rect.origin.x = bounds.x;
        rect.origin.y = bounds.y;
        rect.size.width = bounds.w;
        rect.size.height = bounds.h;
        ConvertNSRect(&rect);

        /* Hack to fix origin on Mac OS X 10.4 */
        NSRect screenRect = [[nswindow screen] frame];
        if (screenRect.size.height >= 1.0f) {
            rect.origin.y += (screenRect.size.height - rect.size.height);
        }

        if ([nswindow respondsToSelector: @selector(setStyleMask:)]) {
            [nswindow performSelector: @selector(setStyleMask:) withObject: (id)NSBorderlessWindowMask];
        } else {
            nswindow = Cocoa_RebuildWindow(data, nswindow, NSBorderlessWindowMask);
        }
    } else {
        rect.origin.x = window->windowed.x;
        rect.origin.y = window->windowed.y;
        rect.size.width = window->windowed.w;
        rect.size.height = window->windowed.h;
        ConvertNSRect(&rect);

        if ([nswindow respondsToSelector: @selector(setStyleMask:)]) {
            [nswindow performSelector: @selector(setStyleMask:) withObject: (id)(uintptr_t)GetWindowStyle(window)];
        } else {
            nswindow = Cocoa_RebuildWindow(data, nswindow, GetWindowStyle(window));
        }
    }

    /* The view responder chain gets messed with during setStyleMask */
    if ([[nswindow contentView] nextResponder] != data->listener) {
        [[nswindow contentView] setNextResponder:data->listener];
    }

    s_moveHack = 0;
    [nswindow setFrameOrigin:rect.origin];
    [nswindow setContentSize:rect.size];
    s_moveHack = SDL_GetTicks();

    /* When the window style changes the title is cleared */
    if (!fullscreen) {
        Cocoa_SetWindowTitle(_this, window);
    }

#ifdef FULLSCREEN_TOGGLEABLE
    if (fullscreen) {
        /* OpenGL is rendering to the window, so make it visible! */
        [nswindow setLevel:CGShieldingWindowLevel()];
    } else {
        [nswindow setLevel:kCGNormalWindowLevel];
    }
#endif
    [nswindow makeKeyAndOrderFront:nil];

    [pool release];
}

int
Cocoa_SetWindowGammaRamp(_THIS, SDL_Window * window, const Uint16 * ramp)
{
    SDL_VideoDisplay *display = SDL_GetDisplayForWindow(window);
    CGDirectDisplayID display_id = ((SDL_DisplayData *)display->driverdata)->display;
    const uint32_t tableSize = 256;
    CGGammaValue redTable[tableSize];
    CGGammaValue greenTable[tableSize];
    CGGammaValue blueTable[tableSize];
    uint32_t i;
    float inv65535 = 1.0f / 65535.0f;

    /* Extract gamma values into separate tables, convert to floats between 0.0 and 1.0 */
    for (i = 0; i < 256; i++) {
        redTable[i] = ramp[0*256+i] * inv65535;
        greenTable[i] = ramp[1*256+i] * inv65535;
        blueTable[i] = ramp[2*256+i] * inv65535;
    }

    if (CGSetDisplayTransferByTable(display_id, tableSize,
                                    redTable, greenTable, blueTable) != CGDisplayNoErr) {
        SDL_SetError("CGSetDisplayTransferByTable()");
        return -1;
    }
    return 0;
}

int
Cocoa_GetWindowGammaRamp(_THIS, SDL_Window * window, Uint16 * ramp)
{
    SDL_VideoDisplay *display = SDL_GetDisplayForWindow(window);
    CGDirectDisplayID display_id = ((SDL_DisplayData *)display->driverdata)->display;
    const uint32_t tableSize = 256;
    CGGammaValue redTable[tableSize];
    CGGammaValue greenTable[tableSize];
    CGGammaValue blueTable[tableSize];
    uint32_t i, tableCopied;

    if (CGGetDisplayTransferByTable(display_id, tableSize,
                                    redTable, greenTable, blueTable, &tableCopied) != CGDisplayNoErr) {
        SDL_SetError("CGGetDisplayTransferByTable()");
        return -1;
    }

    for (i = 0; i < tableCopied; i++) {
        ramp[0*256+i] = (Uint16)(redTable[i] * 65535.0f);
        ramp[1*256+i] = (Uint16)(greenTable[i] * 65535.0f);
        ramp[2*256+i] = (Uint16)(blueTable[i] * 65535.0f);
    }
    return 0;
}

void
Cocoa_SetWindowGrab(_THIS, SDL_Window * window)
{
    /* Move the cursor to the nearest point in the window */
    if ((window->flags & SDL_WINDOW_INPUT_GRABBED) &&
        (window->flags & SDL_WINDOW_INPUT_FOCUS)) {
        int x, y;
        CGPoint cgpoint;

        SDL_GetMouseState(&x, &y);
        cgpoint.x = window->x + x;
        cgpoint.y = window->y + y;
        CGDisplayMoveCursorToPoint(kCGDirectMainDisplay, cgpoint);
    }
}

void
Cocoa_DestroyWindow(_THIS, SDL_Window * window)
{
    NSAutoreleasePool *pool = [[NSAutoreleasePool alloc] init];
    SDL_WindowData *data = (SDL_WindowData *) window->driverdata;

    if (data) {
        [data->listener close];
        [data->listener release];
        if (data->created) {
            [data->nswindow close];
        }
        SDL_free(data);
    }
    [pool release];
}

SDL_bool
Cocoa_GetWindowWMInfo(_THIS, SDL_Window * window, SDL_SysWMinfo * info)
{
    NSWindow *nswindow = ((SDL_WindowData *) window->driverdata)->nswindow;

    if (info->version.major <= SDL_MAJOR_VERSION) {
        info->subsystem = SDL_SYSWM_COCOA;
        info->info.cocoa.window = nswindow;
        return SDL_TRUE;
    } else {
        SDL_SetError("Application not compiled with SDL %d.%d\n",
                     SDL_MAJOR_VERSION, SDL_MINOR_VERSION);
        return SDL_FALSE;
    }
}

/* vi: set ts=4 sw=4 expandtab: */
