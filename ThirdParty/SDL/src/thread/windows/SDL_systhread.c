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

/* Win32 thread management routines for SDL */

#include "SDL_thread.h"
#include "../SDL_thread_c.h"
#include "../SDL_systhread.h"
#include "SDL_systhread_c.h"

#ifndef SDL_PASSED_BEGINTHREAD_ENDTHREAD
#ifndef _WIN32_WCE
/* We'll use the C library from this DLL */
#include <process.h>
#endif

#if __GNUC__
typedef uintptr_t (__cdecl * pfnSDL_CurrentBeginThread) (void *, unsigned,
                                                             unsigned
                                                             (__stdcall *
                                                              func) (void *),
                                                             void *arg,
                                                             unsigned,
                                                             unsigned
                                                             *threadID);
typedef void (__cdecl * pfnSDL_CurrentEndThread) (unsigned code);
#elif defined(__WATCOMC__)
/* This is for Watcom targets except OS2 */
#if __WATCOMC__ < 1240
#define __watcall
#endif
typedef unsigned long (__watcall * pfnSDL_CurrentBeginThread) (void *,
                                                               unsigned,
                                                               unsigned
                                                               (__stdcall *
                                                                func) (void
                                                                       *),
                                                               void *arg,
                                                               unsigned,
                                                               unsigned
                                                               *threadID);
typedef void (__watcall * pfnSDL_CurrentEndThread) (unsigned code);
#else
typedef uintptr_t(__cdecl * pfnSDL_CurrentBeginThread) (void *, unsigned,
                                                        unsigned (__stdcall *
                                                                  func) (void
                                                                         *),
                                                        void *arg, unsigned,
                                                        unsigned *threadID);
typedef void (__cdecl * pfnSDL_CurrentEndThread) (unsigned code);
#endif
#endif /* !SDL_PASSED_BEGINTHREAD_ENDTHREAD */


typedef struct ThreadStartParms
{
    void *args;
    pfnSDL_CurrentEndThread pfnCurrentEndThread;
} tThreadStartParms, *pThreadStartParms;

static DWORD __stdcall
RunThread(void *data)
{
    pThreadStartParms pThreadParms = (pThreadStartParms) data;
    pfnSDL_CurrentEndThread pfnCurrentEndThread = NULL;

    // Call the thread function!
    SDL_RunThread(pThreadParms->args);

    // Get the current endthread we have to use!
    if (pThreadParms) {
        pfnCurrentEndThread = pThreadParms->pfnCurrentEndThread;
        SDL_free(pThreadParms);
    }
    // Call endthread!
    if (pfnCurrentEndThread)
        (*pfnCurrentEndThread) (0);
    return (0);
}

#ifdef SDL_PASSED_BEGINTHREAD_ENDTHREAD
int
SDL_SYS_CreateThread(SDL_Thread * thread, void *args,
                     pfnSDL_CurrentBeginThread pfnBeginThread,
                     pfnSDL_CurrentEndThread pfnEndThread)
{
#else
int
SDL_SYS_CreateThread(SDL_Thread * thread, void *args)
{
#ifdef _WIN32_WCE
    pfnSDL_CurrentBeginThread pfnBeginThread = NULL;
    pfnSDL_CurrentEndThread pfnEndThread = NULL;
#else
    pfnSDL_CurrentBeginThread pfnBeginThread = _beginthreadex;
    pfnSDL_CurrentEndThread pfnEndThread = _endthreadex;
#endif
#endif /* SDL_PASSED_BEGINTHREAD_ENDTHREAD */
    unsigned threadid;
    pThreadStartParms pThreadParms =
        (pThreadStartParms) SDL_malloc(sizeof(tThreadStartParms));
    if (!pThreadParms) {
        SDL_OutOfMemory();
        return (-1);
    }
    // Save the function which we will have to call to clear the RTL of calling app!
    pThreadParms->pfnCurrentEndThread = pfnEndThread;
    // Also save the real parameters we have to pass to thread function
    pThreadParms->args = args;

    if (pfnBeginThread) {
        thread->handle =
            (SYS_ThreadHandle) pfnBeginThread(NULL, 0, RunThread,
                                              pThreadParms, 0, &threadid);
    } else {
        thread->handle =
            CreateThread(NULL, 0, RunThread, pThreadParms, 0, &threadid);
    }
    if (thread->handle == NULL) {
        SDL_SetError("Not enough resources to create thread");
        return (-1);
    }
    return (0);
}

void
SDL_SYS_SetupThread(void)
{
    return;
}

SDL_threadID
SDL_ThreadID(void)
{
    return ((SDL_threadID) GetCurrentThreadId());
}

int
SDL_SYS_SetThreadPriority(SDL_ThreadPriority priority)
{
    int value;

    if (priority == SDL_THREAD_PRIORITY_LOW) {
        value = THREAD_PRIORITY_LOWEST;
    } else if (priority == SDL_THREAD_PRIORITY_HIGH) {
        value = THREAD_PRIORITY_HIGHEST;
    } else {
        value = THREAD_PRIORITY_NORMAL;
    }
    if (!SetThreadPriority(GetCurrentThread(), value)) {
        WIN_SetError("SetThreadPriority()");
        return -1;
    }
    return 0;
}

void
SDL_SYS_WaitThread(SDL_Thread * thread)
{
    WaitForSingleObject(thread->handle, INFINITE);
    CloseHandle(thread->handle);
}

/* vi: set ts=4 sw=4 expandtab: */
