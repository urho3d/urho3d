/*
    SDL - Simple DirectMedia Layer
    Copyright (C) 1997-2012 Sam Lantinga

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library; if not, write to the Free Software
    Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA

    Sam Lantinga
    slouken@libsdl.org
*/

#ifndef SDL_BKEYBOARD_H
#define SDL_BKEYBOARD_H

#include <SupportDefs.h>

#ifdef __cplusplus
extern "C" {
#endif

#include "../../../include/SDL_keyboard.h"

extern void BE_InitOSKeymap();
extern SDL_Scancode BE_GetScancodeFromBeKey(int32 bkey);
extern int8 BE_GetKeyState(int32 bkey);
extern void BE_SetKeyState(int32 bkey, int8 state);

#ifdef __cplusplus
}
#endif

#endif
