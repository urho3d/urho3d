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

#ifndef _SDL_thread_c_h
#define _SDL_thread_c_h

/* Need the definitions of SYS_ThreadHandle */
#if SDL_THREADS_DISABLED
#include "generic/SDL_systhread_c.h"
#elif SDL_THREAD_BEOS
#include "beos/SDL_systhread_c.h"
#elif SDL_THREAD_EPOC
#include "epoc/SDL_systhread_c.h"
#elif SDL_THREAD_PTHREAD
#include "pthread/SDL_systhread_c.h"
#elif SDL_THREAD_SPROC
#include "irix/SDL_systhread_c.h"
#elif SDL_THREAD_WINDOWS
#include "windows/SDL_systhread_c.h"
#elif SDL_THREAD_NDS
#include "nds/SDL_systhread_c.h"
#else
#error Need thread implementation for this platform
#include "generic/SDL_systhread_c.h"
#endif
#include "../SDL_error_c.h"

/* This is the system-independent thread info structure */
struct SDL_Thread
{
    SDL_threadID threadid;
    SYS_ThreadHandle handle;
    int status;
    SDL_error errbuf;
    void *data;
};

/* This is the function called to run a thread */
extern void SDL_RunThread(void *data);

#endif /* _SDL_thread_c_h */
/* vi: set ts=4 sw=4 expandtab: */
