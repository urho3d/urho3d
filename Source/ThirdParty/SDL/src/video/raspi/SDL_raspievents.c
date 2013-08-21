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
#define NUM_INPUT_DEVICE SDL_arraysize(event_fd)

/* Raspberry Pi native scancode to SDL scancode mapping */
static SDL_Scancode RASPI_scancodes[] = {
    SDL_SCANCODE_UNKNOWN/*KEY_RESERVED*/,

    SDL_SCANCODE_ESCAPE,
    SDL_SCANCODE_1,
    SDL_SCANCODE_2,
    SDL_SCANCODE_3,
    SDL_SCANCODE_4,
    SDL_SCANCODE_5,
    SDL_SCANCODE_6,
    SDL_SCANCODE_7,
    SDL_SCANCODE_8,
    SDL_SCANCODE_9,
    SDL_SCANCODE_0,
    SDL_SCANCODE_MINUS,
    SDL_SCANCODE_EQUALS,
    SDL_SCANCODE_BACKSPACE,

    SDL_SCANCODE_TAB,
    SDL_SCANCODE_Q,
    SDL_SCANCODE_W,
    SDL_SCANCODE_E,
    SDL_SCANCODE_R,
    SDL_SCANCODE_T,
    SDL_SCANCODE_Y,
    SDL_SCANCODE_U,
    SDL_SCANCODE_I,
    SDL_SCANCODE_O,
    SDL_SCANCODE_P,
    SDL_SCANCODE_LEFTBRACKET,
    SDL_SCANCODE_RIGHTBRACKET,
    SDL_SCANCODE_RETURN,

    SDL_SCANCODE_LCTRL,
    SDL_SCANCODE_A,
    SDL_SCANCODE_S,
    SDL_SCANCODE_D,
    SDL_SCANCODE_F,
    SDL_SCANCODE_G,
    SDL_SCANCODE_H,
    SDL_SCANCODE_J,
    SDL_SCANCODE_K,
    SDL_SCANCODE_L,
    SDL_SCANCODE_SEMICOLON,
    SDL_SCANCODE_APOSTROPHE,
    SDL_SCANCODE_GRAVE,

    SDL_SCANCODE_LSHIFT,
    SDL_SCANCODE_BACKSLASH,
    SDL_SCANCODE_Z,
    SDL_SCANCODE_X,
    SDL_SCANCODE_C,
    SDL_SCANCODE_V,
    SDL_SCANCODE_B,
    SDL_SCANCODE_N,
    SDL_SCANCODE_M,
    SDL_SCANCODE_COMMA,
    SDL_SCANCODE_PERIOD,
    SDL_SCANCODE_SLASH,
    SDL_SCANCODE_RSHIFT,

    SDL_SCANCODE_KP_MULTIPLY,
    SDL_SCANCODE_LALT,
    SDL_SCANCODE_SPACE,
    SDL_SCANCODE_CAPSLOCK,
    SDL_SCANCODE_F1,
    SDL_SCANCODE_F2,
    SDL_SCANCODE_F3,
    SDL_SCANCODE_F4,
    SDL_SCANCODE_F5,
    SDL_SCANCODE_F6,
    SDL_SCANCODE_F7,
    SDL_SCANCODE_F8,
    SDL_SCANCODE_F9,
    SDL_SCANCODE_F10,

    SDL_SCANCODE_NUMLOCKCLEAR,
    SDL_SCANCODE_SCROLLLOCK,
    SDL_SCANCODE_KP_7,
    SDL_SCANCODE_KP_8,
    SDL_SCANCODE_KP_9,
    SDL_SCANCODE_KP_MINUS,
    SDL_SCANCODE_KP_4,
    SDL_SCANCODE_KP_5,
    SDL_SCANCODE_KP_6,
    SDL_SCANCODE_KP_PLUS,
    SDL_SCANCODE_KP_1,
    SDL_SCANCODE_KP_2,
    SDL_SCANCODE_KP_3,
    SDL_SCANCODE_KP_0,
    SDL_SCANCODE_KP_PERIOD,

    SDL_SCANCODE_UNKNOWN/*UNKNOWN*/,
    SDL_SCANCODE_UNKNOWN/*KEY_ZENKAKUHANKAKU*/,
    SDL_SCANCODE_UNKNOWN/*KEY_102ND*/,
    SDL_SCANCODE_F11,
    SDL_SCANCODE_F12,
    SDL_SCANCODE_UNKNOWN/*KEY_RO*/,
    SDL_SCANCODE_UNKNOWN/*KEY_KATAKANA*/,
    SDL_SCANCODE_UNKNOWN/*KEY_HIRAGANA*/,
    SDL_SCANCODE_UNKNOWN/*KEY_HENKAN*/,
    SDL_SCANCODE_UNKNOWN/*KEY_KATAKANAHIRAGANA*/,
    SDL_SCANCODE_UNKNOWN/*KEY_MUHENKAN*/,

    SDL_SCANCODE_KP_COMMA,
    SDL_SCANCODE_KP_ENTER,
    SDL_SCANCODE_RCTRL,
    SDL_SCANCODE_KP_DIVIDE,
    SDL_SCANCODE_PRINTSCREEN,
    SDL_SCANCODE_RALT,
    SDL_SCANCODE_UNKNOWN/*KEY_LINEFEED*/,

    SDL_SCANCODE_HOME,
    SDL_SCANCODE_UP,
    SDL_SCANCODE_PAGEUP,
    SDL_SCANCODE_LEFT,
    SDL_SCANCODE_RIGHT,
    SDL_SCANCODE_END,
    SDL_SCANCODE_DOWN,
    SDL_SCANCODE_PAGEDOWN,
    SDL_SCANCODE_INSERT,
    SDL_SCANCODE_DELETE,

    SDL_SCANCODE_UNKNOWN/*KEY_MACRO*/,
    SDL_SCANCODE_MUTE,
    SDL_SCANCODE_VOLUMEDOWN,
    SDL_SCANCODE_VOLUMEUP,
    SDL_SCANCODE_POWER,
    SDL_SCANCODE_KP_EQUALS,
    SDL_SCANCODE_KP_PLUSMINUS,
    SDL_SCANCODE_PAUSE,

    SDL_SCANCODE_UNKNOWN/*KEY_SCALE*/,
    SDL_SCANCODE_KP_COMMA,
    SDL_SCANCODE_UNKNOWN/*KEY_HANGEUL*/,
    SDL_SCANCODE_UNKNOWN/*KEY_HANJA*/,
    SDL_SCANCODE_UNKNOWN/*KEY_YEN*/,
    SDL_SCANCODE_LGUI,
    SDL_SCANCODE_RGUI,
    SDL_SCANCODE_UNKNOWN/*KEY_COMPOSE*/,
};

static int
TranslateMouseButton(__u16 code)
{
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
            if (event[i].code < SDL_arraysize(RASPI_scancodes)) {
                SDL_SendKeyboardKey(event[i].value, RASPI_scancodes[event[i].code]);
            }
            else if ((button = TranslateMouseButton(event[i].code)) != -1) {
                SDL_SendMouseButton(data->window, index, event[i].value, button);
            }
            break;

        case EV_REL:
            switch (event[i].code) {
            case REL_X:
                x = event[i].value;
                relevent = MOTION;
                break;
            case REL_Y:
                y = event[i].value;
                relevent = MOTION;
                break;
            case REL_HWHEEL:
                x = event[i].value;
                y = 0;
                relevent = WHEEL;
                break;
            case REL_WHEEL:
                x = 0;
                y = event[i].value;
                relevent = WHEEL;
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
        event_fd[i] = open(device, O_RDWR | O_NONBLOCK);
        if (event_fd[i] < 0) {
            return SDL_SetError("Couldn't open %s", device);
        }
        if (ioctl(event_fd[i], EVIOCGRAB, 1/*grab*/) < 0) {
            return SDL_SetError("Couldn't grab %s", device);
        }
    }

    /* Use default SDL scancode to SDL keycode mapping */
    SDL_Keycode keymap[SDL_NUM_SCANCODES];
    SDL_GetDefaultKeymap(keymap);
    SDL_SetKeymap(0, keymap, SDL_NUM_SCANCODES);

    return 0;
}

void
RASPI_QuitInput(_THIS)
{
    int i;
    for (i = 0; i < NUM_INPUT_DEVICE; ++i) {
        ioctl(event_fd[i], EVIOCGRAB, 0/*release*/);
        close(event_fd[i]);
        event_fd[i] = -1;
    }
}

#endif /* SDL_VIDEO_DRIVER_RASPI */

/* vi: set ts=4 sw=4 expandtab: */
