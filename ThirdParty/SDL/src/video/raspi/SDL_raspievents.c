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

#include "../../events/SDL_events_c.h"
#include "SDL_raspivideo.h"

#include <linux/input.h>
#include <fcntl.h>

static int event_fd[] = { -1, -1 };        /* assume two USB HID input devices */
struct input_event event[64];
#define NUM_INPUT_DEVICE sizeof(event_fd) / sizeof(int)

static SDL_Keycode keymap[] = {
    0/*KEY_RESERVED*/,
    SDLK_ESCAPE,'1','2','3','4','5','6','7','8','9','0','-','=',SDLK_BACKSPACE,
    SDLK_TAB,'q','w','e','r','t','y','u','i','o','p','[',']',SDLK_RETURN,
    SDLK_LCTRL,'a','s','d','f','g','h','j','k','l',';','\'','`',
    SDLK_LSHIFT,'\\','z','x','c','v','b','n','m',',','.','/',SDLK_RSHIFT,
    SDLK_KP_MULTIPLY,SDLK_LALT,SDLK_SPACE,SDLK_CAPSLOCK,
    SDLK_F1,SDLK_F2,SDLK_F3,SDLK_F4,SDLK_F5,SDLK_F6,SDLK_F7,SDLK_F8,SDLK_F9,SDLK_F10,
    SDLK_NUMLOCKCLEAR,SDLK_SCROLLLOCK,
    SDLK_KP_7,SDLK_KP_8,SDLK_KP_9,SDLK_KP_MINUS,SDLK_KP_4,SDLK_KP_5,SDLK_KP_6,
    SDLK_KP_PLUS,SDLK_KP_1,SDLK_KP_2,SDLK_KP_3,SDLK_KP_0,SDLK_KP_PERIOD,
    0/*UNKNOWN*/,0/*KEY_ZENKAKUHANKAKU*/,0/*KEY_102ND*/,SDLK_F11,SDLK_F12,0/*KEY_RO*/,
    0/*KEY_KATAKANA*/,0/*KEY_HIRAGANA*/,0/*KEY_HENKAN*/,0/*KEY_KATAKANAHIRAGANA*/,0/*KEY_MUHENKAN*/,
    0/*KEY_KPJPCOMMA*/,SDLK_KP_ENTER,SDLK_RCTRL,SDLK_KP_DIVIDE,SDLK_PRINTSCREEN,SDLK_RALT,0/*KEY_LINEFEED*/,
    SDLK_HOME,SDLK_UP,SDLK_PAGEUP,SDLK_LEFT,SDLK_RIGHT,SDLK_END,SDLK_DOWN,SDLK_PAGEDOWN,SDLK_INSERT,SDLK_DELETE,
    0/*KEY_MACRO*/,SDLK_MUTE,SDLK_VOLUMEDOWN,SDLK_VOLUMEUP,SDLK_POWER,SDLK_KP_EQUALS,SDLK_KP_PLUSMINUS,SDL_SCANCODE_PAUSE,
    0/*KEY_SCALE*/,SDLK_KP_COMMA,0/*KEY_HANGEUL*/,0/*KEY_HANJA*/,0/*KEY_YEN*/,SDLK_LGUI,SDLK_RGUI,0/*KEY_COMPOSE*/,
};

static int
TranslateMouseButton(__u16 code) {
    switch (code) {
    case 272:
        return SDL_BUTTON_LEFT;
    case 273:
        return SDL_BUTTON_RIGHT;
    case 274:
        return SDL_BUTTON_MIDDLE;
    default:
        return -1;
    }
}

typedef enum
{
    NONE,
    MOTION,
    WHEEL
} RelativeEvent;

static void
PropagateEvents(_THIS, int index)
{
    SDL_VideoData *data = (SDL_VideoData *) _this->driverdata;

    int i, count, button, x, y;
    RelativeEvent relevent;
    if ((count = read(event_fd[index], event, sizeof(event))) < 0) {
        return;
    }
    count = count / sizeof(struct input_event);
    for (i = 0; i < count; ++i) {
        switch (event[i].type) {
        case EV_KEY:
            if (event[i].code < sizeof(keymap) / sizeof(SDL_Keycode)) {
                SDL_SendKeyboardKey(event[i].value, event[i].code);
            }
            else if ((button = TranslateMouseButton(event[i].code)) != -1) {
                SDL_SendMouseButton(data->window, index, event[i].value, button);
            }
            break;

        case EV_REL:
            switch (event[i].code) {
            case REL_X:
            case REL_HWHEEL:
                x = event[i].value;
                relevent = event[i].code == REL_X ? MOTION : WHEEL;
                break;
            case REL_Y:
            case REL_WHEEL:
                y = event[i].value;
                relevent = event[i].code == REL_Y ? MOTION : WHEEL;
                break;
            default:
                relevent = NONE;
            }
            break;

        case EV_SYN:
            switch (relevent) {
            case MOTION:
                SDL_SendMouseMotion(data->window, index, 1/*relative*/, x, y);
                break;
            case WHEEL:
                SDL_SendMouseWheel(data->window, index, x, y);
                break;
            default: ;
            }
            break;

        default: ;
        }
    }
}

void
RASPI_PumpEvents(_THIS)
{
    int i;
    for (i = 0; i < NUM_INPUT_DEVICE; ++i) {
        PropagateEvents(_this, i);
    }
}

int
RASPI_InitInput(_THIS)
{
    int i;
    char device[32];
    for (i = 0; i < NUM_INPUT_DEVICE; ++i) {
        sprintf(device, "/dev/input/event%i", i);
        event_fd[i] = open(device, O_RDONLY | O_NONBLOCK);
        if (event_fd[i] < 0) {
            return SDL_SetError("Couldn't open %s", device);
        }
    }

    /* Set Linux scancode to SDL key mapping */
    SDL_SetKeymap(0, keymap, sizeof(keymap));

    return 0;
}

void
RASPI_QuitInput(_THIS)
{
    int i;
    for (i = 0; i < NUM_INPUT_DEVICE; ++i) {
        close(event_fd[i]);
        event_fd[i] = -1;
    }
}

#endif /* SDL_VIDEO_DRIVER_RASPI */

/* vi: set ts=4 sw=4 expandtab: */
