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

#ifdef SAVE_RCSID
static char rcsid =
    "@(#) $Id: SDL_systhread.c,v 1.2 2001/04/26 16:50:18 hercules Exp $";
#endif

/* Thread management routines for SDL */

#include "SDL_error.h"
#include "SDL_thread.h"
#include "../SDL_systhread.h"

int
SDL_SYS_CreateThread(SDL_Thread * thread, void *args)
{
    SDL_SetError("Threads are not supported on this platform");
    return (-1);
}

void
SDL_SYS_SetupThread(const char *name)
{
    return;
}

SDL_threadID
SDL_ThreadID(void)
{
    return (0);
}

void
SDL_SYS_WaitThread(SDL_Thread * thread)
{
    return;
}

int
SDL_SYS_SetThreadPriority(SDL_ThreadPriority priority)
{
    return (0);
}

/* vi: set ts=4 sw=4 expandtab: */
