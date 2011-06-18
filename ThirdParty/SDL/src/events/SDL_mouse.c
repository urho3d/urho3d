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

// Modified by Lasse Öörni for Urho3D

#include "SDL_config.h"

/* General mouse handling code for SDL */

#include "SDL_events.h"
#include "SDL_events_c.h"
#include "default_cursor.h"
#include "../video/SDL_sysvideo.h"


/* The mouse state */
static SDL_Mouse SDL_mouse;


/* Public functions */
int
SDL_MouseInit(void)
{
    SDL_Mouse *mouse = SDL_GetMouse();

    mouse->cursor_shown = SDL_TRUE;

    return (0);
}

void
SDL_SetDefaultCursor(SDL_Cursor * cursor)
{
    SDL_Mouse *mouse = SDL_GetMouse();

    mouse->def_cursor = cursor;
    if (!mouse->cur_cursor) {
        SDL_SetCursor(cursor);
    }
}

SDL_Mouse *
SDL_GetMouse(void)
{
    return &SDL_mouse;
}

SDL_Window *
SDL_GetMouseFocus(void)
{
    SDL_Mouse *mouse = SDL_GetMouse();

    return mouse->focus;
}

void
SDL_SetMouseFocus(SDL_Window * window)
{
    SDL_Mouse *mouse = SDL_GetMouse();

    if (mouse->focus == window) {
        return;
    }

    /* See if the current window has lost focus */
    if (mouse->focus) {
        SDL_SendWindowEvent(mouse->focus, SDL_WINDOWEVENT_LEAVE, 0, 0);
    }

    mouse->focus = window;

    if (mouse->focus) {
        SDL_SendWindowEvent(mouse->focus, SDL_WINDOWEVENT_ENTER, 0, 0);
    }
}

int
SDL_SendMouseMotion(SDL_Window * window, int relative, int x, int y)
{
    SDL_Mouse *mouse = SDL_GetMouse();
    int posted;
    int xrel;
    int yrel;
    int x_max = 0, y_max = 0;

    if (window) {
        SDL_SetMouseFocus(window);
    }

    /* the relative motion is calculated regarding the system cursor last position */
    if (relative) {
        xrel = x;
        yrel = y;
        x = (mouse->last_x + x);
        y = (mouse->last_y + y);
    } else {
        xrel = x - mouse->last_x;
        yrel = y - mouse->last_y;
    }

    /* Drop events that don't change state */
    if (!xrel && !yrel) {
#if 0
        printf("Mouse event didn't change state - dropped!\n");
#endif
        return 0;
    }

    /* Update internal mouse coordinates */
    if (mouse->relative_mode == SDL_FALSE) {
        mouse->x = x;
        mouse->y = y;
    } else {
        mouse->x += xrel;
        mouse->y += yrel;
    }

    SDL_GetWindowSize(mouse->focus, &x_max, &y_max);
    --x_max;
    --y_max;

    /* make sure that the pointers find themselves inside the windows */
    /* only check if mouse->xmax is set ! */
    if (mouse->x > x_max) {
        mouse->x = x_max;
    }
    if (mouse->x < 0) {
        mouse->x = 0;
    }

    if (mouse->y > y_max) {
        mouse->y = y_max;
    }
    if (mouse->y < 0) {
        mouse->y = 0;
    }

    mouse->xdelta += xrel;
    mouse->ydelta += yrel;

#if 0 /* FIXME */
    /* Move the mouse cursor, if needed */
    if (mouse->cursor_shown && !mouse->relative_mode &&
        mouse->MoveCursor && mouse->cur_cursor) {
        mouse->MoveCursor(mouse->cur_cursor);
    }
#endif

    /* Post the event, if desired */
    posted = 0;
    if (SDL_GetEventState(SDL_MOUSEMOTION) == SDL_ENABLE) {
        SDL_Event event;
        event.motion.type = SDL_MOUSEMOTION;
        event.motion.windowID = mouse->focus ? mouse->focus->id : 0;
        event.motion.state = mouse->buttonstate;
        event.motion.x = mouse->x;
        event.motion.y = mouse->y;
        event.motion.xrel = xrel;
        event.motion.yrel = yrel;
        posted = (SDL_PushEvent(&event) > 0);
    }
    mouse->last_x = mouse->x;
    mouse->last_y = mouse->y;
    return posted;
}

int
SDL_SendMouseButton(SDL_Window * window, Uint8 state, Uint8 button)
{
    SDL_Mouse *mouse = SDL_GetMouse();
    int posted;
    Uint32 type;

    if (window) {
        SDL_SetMouseFocus(window);
    }

    /* Figure out which event to perform */
    switch (state) {
    case SDL_PRESSED:
        if (mouse->buttonstate & SDL_BUTTON(button)) {
            /* Ignore this event, no state change */
            return 0;
        }
        type = SDL_MOUSEBUTTONDOWN;
        mouse->buttonstate |= SDL_BUTTON(button);
        break;
    case SDL_RELEASED:
        if (!(mouse->buttonstate & SDL_BUTTON(button))) {
            /* Ignore this event, no state change */
            return 0;
        }
        type = SDL_MOUSEBUTTONUP;
        mouse->buttonstate &= ~SDL_BUTTON(button);
        break;
    default:
        /* Invalid state -- bail */
        return 0;
    }

    /* Post the event, if desired */
    posted = 0;
    if (SDL_GetEventState(type) == SDL_ENABLE) {
        SDL_Event event;
        event.type = type;
        event.button.state = state;
        event.button.button = button;
        event.button.x = mouse->x;
        event.button.y = mouse->y;
        event.button.windowID = mouse->focus ? mouse->focus->id : 0;
        posted = (SDL_PushEvent(&event) > 0);
    }
    return posted;
}

int
SDL_SendMouseWheel(SDL_Window * window, int x, int y)
{
    SDL_Mouse *mouse = SDL_GetMouse();
    int posted;

    if (window) {
        SDL_SetMouseFocus(window);
    }

    if (!x && !y) {
        return 0;
    }

    /* Post the event, if desired */
    posted = 0;
    if (SDL_GetEventState(SDL_MOUSEWHEEL) == SDL_ENABLE) {
        SDL_Event event;
        event.type = SDL_MOUSEWHEEL;
        event.wheel.windowID = mouse->focus ? mouse->focus->id : 0;
        event.wheel.x = x;
        event.wheel.y = y;
        posted = (SDL_PushEvent(&event) > 0);
    }
    return posted;
}

void
SDL_MouseQuit(void)
{
}

Uint8
SDL_GetMouseState(int *x, int *y)
{
    SDL_Mouse *mouse = SDL_GetMouse();

    if (x) {
        *x = mouse->x;
    }
    if (y) {
        *y = mouse->y;
    }
    return mouse->buttonstate;
}

Uint8
SDL_GetRelativeMouseState(int *x, int *y)
{
    SDL_Mouse *mouse = SDL_GetMouse();

    if (x) {
        *x = mouse->xdelta;
    }
    if (y) {
        *y = mouse->ydelta;
    }
    mouse->xdelta = 0;
    mouse->ydelta = 0;
    return mouse->buttonstate;
}

void
SDL_WarpMouseInWindow(SDL_Window * window, int x, int y)
{
    SDL_Mouse *mouse = SDL_GetMouse();

    if (mouse->WarpMouse) {
        // Urho3D: make sure to update the internal position when the mouse is warped
        mouse->x = x;
        mouse->y = y;
        mouse->WarpMouse(window, x, y);
    } else {
        SDL_SendMouseMotion(window, 0, x, y);
    }
}

int
SDL_SetRelativeMouseMode(SDL_bool enabled)
{
    SDL_Mouse *mouse = SDL_GetMouse();

    if (enabled == mouse->relative_mode) {
        return 0;
    }

    if (!mouse->SetRelativeMouseMode) {
        SDL_Unsupported();
        return -1;
    }

    if (mouse->SetRelativeMouseMode(enabled) < 0) {
        return -1;
    }

    /* Set the relative mode */
    mouse->relative_mode = enabled;

    if (!enabled) {
        /* Restore the expected mouse position */
        SDL_WarpMouseInWindow(mouse->focus, mouse->x, mouse->y);
    }

    /* Flush pending mouse motion */
    SDL_FlushEvent(SDL_MOUSEMOTION);

    /* Update cursor visibility */
    SDL_SetCursor(NULL);

    return 0;
}

SDL_bool
SDL_GetRelativeMouseMode()
{
    SDL_Mouse *mouse = SDL_GetMouse();

    return mouse->relative_mode;
}

SDL_Cursor *
SDL_CreateCursor(const Uint8 * data, const Uint8 * mask,
                 int w, int h, int hot_x, int hot_y)
{
    SDL_Mouse *mouse = SDL_GetMouse();
    SDL_Surface *surface;
    SDL_Cursor *cursor;
    int x, y;
    Uint32 *pixel;
    Uint8 datab = 0, maskb = 0;
    const Uint32 black = 0xFF000000;
    const Uint32 white = 0xFFFFFFFF;
    const Uint32 transparent = 0x00000000;

    /* Make sure the width is a multiple of 8 */
    w = ((w + 7) & ~7);

    /* Create the surface from a bitmap */
    surface = SDL_CreateRGBSurface(0, w, h, 32,
                                   0x00FF0000,
                                   0x0000FF00,
                                   0x000000FF,
                                   0xFF000000);
    if (!surface) {
        return NULL;
    }
    for (y = 0; y < h; ++y) {
        pixel = (Uint32 *) ((Uint8 *) surface->pixels + y * surface->pitch);
        for (x = 0; x < w; ++x) {
            if ((x % 8) == 0) {
                datab = *data++;
                maskb = *mask++;
            }
            if (maskb & 0x80) {
                *pixel++ = (datab & 0x80) ? black : white;
            } else {
                *pixel++ = (datab & 0x80) ? black : transparent;
            }
            datab <<= 1;
            maskb <<= 1;
        }
    }

    cursor = SDL_CreateColorCursor(surface, hot_x, hot_y);

    SDL_FreeSurface(surface);

    return cursor;
}

SDL_Cursor *
SDL_CreateColorCursor(SDL_Surface *surface, int hot_x, int hot_y)
{
    SDL_Mouse *mouse = SDL_GetMouse();
    SDL_Surface *temp = NULL;
    SDL_Cursor *cursor;

    if (!surface) {
        SDL_SetError("Passed NULL cursor surface");
        return NULL;
    }

    if (!mouse->CreateCursor) {
        SDL_SetError("Cursors are not currently supported");
        return NULL;
    }

    /* Sanity check the hot spot */
    if ((hot_x < 0) || (hot_y < 0) ||
        (hot_x >= surface->w) || (hot_y >= surface->h)) {
        SDL_SetError("Cursor hot spot doesn't lie within cursor");
        return NULL;
    }

    if (surface->format->format != SDL_PIXELFORMAT_ARGB8888) {
        temp = SDL_ConvertSurfaceFormat(surface, SDL_PIXELFORMAT_ARGB8888, 0);
        if (!temp) {
            return NULL;
        }
        surface = temp;
    }

    cursor = mouse->CreateCursor(surface, hot_x, hot_y);
    if (cursor) {
        cursor->next = mouse->cursors;
        mouse->cursors = cursor;
    }

    if (temp) {
        SDL_FreeSurface(temp);
    }

    return cursor;
}

/* SDL_SetCursor(NULL) can be used to force the cursor redraw,
   if this is desired for any reason.  This is used when setting
   the video mode and when the SDL window gains the mouse focus.
 */
void
SDL_SetCursor(SDL_Cursor * cursor)
{
    SDL_Mouse *mouse = SDL_GetMouse();

    /* Set the new cursor */
    if (cursor) {
        /* Make sure the cursor is still valid for this mouse */
        if (cursor != mouse->def_cursor) {
            SDL_Cursor *found;
            for (found = mouse->cursors; found; found = found->next) {
                if (found == cursor) {
                    break;
                }
            }
            if (!found) {
                SDL_SetError("Cursor not associated with the current mouse");
                return;
            }
        }
        mouse->cur_cursor = cursor;
    } else {
        cursor = mouse->cur_cursor;
    }

    if (cursor && mouse->cursor_shown && !mouse->relative_mode) {
        if (mouse->ShowCursor) {
            mouse->ShowCursor(cursor);
        }
    } else {
        if (mouse->ShowCursor) {
            mouse->ShowCursor(NULL);
        }
    }
}

SDL_Cursor *
SDL_GetCursor(void)
{
    SDL_Mouse *mouse = SDL_GetMouse();

    if (!mouse) {
        return NULL;
    }
    return mouse->cur_cursor;
}

void
SDL_FreeCursor(SDL_Cursor * cursor)
{
    SDL_Mouse *mouse = SDL_GetMouse();
    SDL_Cursor *curr, *prev;

    if (!cursor) {
        return;
    }

    if (cursor == mouse->def_cursor) {
        return;
    }
    if (cursor == mouse->cur_cursor) {
        SDL_SetCursor(mouse->def_cursor);
    }

    for (prev = NULL, curr = mouse->cursors; curr;
         prev = curr, curr = curr->next) {
        if (curr == cursor) {
            if (prev) {
                prev->next = curr->next;
            } else {
                mouse->cursors = curr->next;
            }

            if (mouse->FreeCursor) {
                mouse->FreeCursor(curr);
            }
            return;
        }
    }
}

int
SDL_ShowCursor(int toggle)
{
    SDL_Mouse *mouse = SDL_GetMouse();
    SDL_bool shown;

    if (!mouse) {
        return 0;
    }

    shown = mouse->cursor_shown;
    if (toggle >= 0) {
        if (toggle) {
            mouse->cursor_shown = SDL_TRUE;
        } else {
            mouse->cursor_shown = SDL_FALSE;
        }
        if (mouse->cursor_shown != shown) {
            SDL_SetCursor(NULL);
        }
    }
    return shown;
}

/* vi: set ts=4 sw=4 expandtab: */
