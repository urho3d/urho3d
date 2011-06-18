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

/* System independent thread management routines for SDL */

#include "SDL_mutex.h"
#include "SDL_thread.h"
#include "SDL_thread_c.h"
#include "SDL_systhread.h"

#define ARRAY_CHUNKSIZE	32
/* The array of threads currently active in the application
   (except the main thread)
   The manipulation of an array here is safer than using a linked list.
*/
static int SDL_maxthreads = 0;
static int SDL_numthreads = 0;
static SDL_Thread **SDL_Threads = NULL;
static SDL_mutex *thread_lock = NULL;

static int
SDL_ThreadsInit(void)
{
    int retval;

    retval = 0;
    thread_lock = SDL_CreateMutex();
    if (thread_lock == NULL) {
        retval = -1;
    }
    return (retval);
}

/* This should never be called...
   If this is called by SDL_Quit(), we don't know whether or not we should
   clean up threads here.  If any threads are still running after this call,
   they will no longer have access to any per-thread data.
 */
#if 0
static void
SDL_ThreadsQuit(void)
{
    SDL_mutex *mutex;

    mutex = thread_lock;
    thread_lock = NULL;
    if (mutex != NULL) {
        SDL_DestroyMutex(mutex);
    }
}
#endif

/* Routines for manipulating the thread list */
static void
SDL_AddThread(SDL_Thread * thread)
{
    /* WARNING:
       If the very first threads are created simultaneously, then
       there could be a race condition causing memory corruption.
       In practice, this isn't a problem because by definition there
       is only one thread running the first time this is called.
     */
    if (!thread_lock) {
        if (SDL_ThreadsInit() < 0) {
            return;
        }
    }
    SDL_mutexP(thread_lock);

    /* Expand the list of threads, if necessary */
#ifdef DEBUG_THREADS
    printf("Adding thread (%d already - %d max)\n",
           SDL_numthreads, SDL_maxthreads);
#endif
    if (SDL_numthreads == SDL_maxthreads) {
        SDL_Thread **threads;
        threads = (SDL_Thread **) SDL_realloc(SDL_Threads,
                                              (SDL_maxthreads +
                                               ARRAY_CHUNKSIZE) *
                                              (sizeof *threads));
        if (threads == NULL) {
            SDL_OutOfMemory();
            goto done;
        }
        SDL_maxthreads += ARRAY_CHUNKSIZE;
        SDL_Threads = threads;
    }
    SDL_Threads[SDL_numthreads++] = thread;
  done:
    SDL_mutexV(thread_lock);
}

static void
SDL_DelThread(SDL_Thread * thread)
{
    int i;

    if (!thread_lock) {
        return;
    }
    SDL_mutexP(thread_lock);
    for (i = 0; i < SDL_numthreads; ++i) {
        if (thread == SDL_Threads[i]) {
            break;
        }
    }
    if (i < SDL_numthreads) {
        if (--SDL_numthreads > 0) {
            while (i < SDL_numthreads) {
                SDL_Threads[i] = SDL_Threads[i + 1];
                ++i;
            }
        } else {
            SDL_maxthreads = 0;
            SDL_free(SDL_Threads);
            SDL_Threads = NULL;
        }
#ifdef DEBUG_THREADS
        printf("Deleting thread (%d left - %d max)\n",
               SDL_numthreads, SDL_maxthreads);
#endif
    }
    SDL_mutexV(thread_lock);

#if 0   /* There could be memory corruption if another thread is starting */
    if (SDL_Threads == NULL) {
        SDL_ThreadsQuit();
    }
#endif
}

/* The default (non-thread-safe) global error variable */
static SDL_error SDL_global_error;

/* Routine to get the thread-specific error variable */
SDL_error *
SDL_GetErrBuf(void)
{
    SDL_error *errbuf;

    errbuf = &SDL_global_error;
    if (SDL_Threads) {
        int i;
        SDL_threadID this_thread;

        this_thread = SDL_ThreadID();
        SDL_mutexP(thread_lock);
        for (i = 0; i < SDL_numthreads; ++i) {
            if (this_thread == SDL_Threads[i]->threadid) {
                errbuf = &SDL_Threads[i]->errbuf;
                break;
            }
        }
        SDL_mutexV(thread_lock);
    }
    return (errbuf);
}


/* Arguments and callback to setup and run the user thread function */
typedef struct
{
    int (SDLCALL * func) (void *);
    void *data;
    SDL_Thread *info;
    SDL_sem *wait;
} thread_args;

void
SDL_RunThread(void *data)
{
    thread_args *args;
    int (SDLCALL * userfunc) (void *);
    void *userdata;
    int *statusloc;

    /* Perform any system-dependent setup
       - this function cannot fail, and cannot use SDL_SetError()
     */
    SDL_SYS_SetupThread();

    /* Get the thread id */
    args = (thread_args *) data;
    args->info->threadid = SDL_ThreadID();

    /* Figure out what function to run */
    userfunc = args->func;
    userdata = args->data;
    statusloc = &args->info->status;

    /* Wake up the parent thread */
    SDL_SemPost(args->wait);

    /* Run the function */
    *statusloc = userfunc(userdata);
}

#ifdef SDL_PASSED_BEGINTHREAD_ENDTHREAD
#undef SDL_CreateThread
DECLSPEC SDL_Thread *SDLCALL
SDL_CreateThread(int (SDLCALL * fn) (void *), void *data,
                 pfnSDL_CurrentBeginThread pfnBeginThread,
                 pfnSDL_CurrentEndThread pfnEndThread)
#else
DECLSPEC SDL_Thread *SDLCALL
SDL_CreateThread(int (SDLCALL * fn) (void *), void *data)
#endif
{
    SDL_Thread *thread;
    thread_args *args;
    int ret;

    /* Allocate memory for the thread info structure */
    thread = (SDL_Thread *) SDL_malloc(sizeof(*thread));
    if (thread == NULL) {
        SDL_OutOfMemory();
        return (NULL);
    }
    SDL_memset(thread, 0, (sizeof *thread));
    thread->status = -1;

    /* Set up the arguments for the thread */
    args = (thread_args *) SDL_malloc(sizeof(*args));
    if (args == NULL) {
        SDL_OutOfMemory();
        SDL_free(thread);
        return (NULL);
    }
    args->func = fn;
    args->data = data;
    args->info = thread;
    args->wait = SDL_CreateSemaphore(0);
    if (args->wait == NULL) {
        SDL_free(thread);
        SDL_free(args);
        return (NULL);
    }

    /* Add the thread to the list of available threads */
    SDL_AddThread(thread);

    /* Create the thread and go! */
#ifdef SDL_PASSED_BEGINTHREAD_ENDTHREAD
    ret = SDL_SYS_CreateThread(thread, args, pfnBeginThread, pfnEndThread);
#else
    ret = SDL_SYS_CreateThread(thread, args);
#endif
    if (ret >= 0) {
        /* Wait for the thread function to use arguments */
        SDL_SemWait(args->wait);
    } else {
        /* Oops, failed.  Gotta free everything */
        SDL_DelThread(thread);
        SDL_free(thread);
        thread = NULL;
    }
    SDL_DestroySemaphore(args->wait);
    SDL_free(args);

    /* Everything is running now */
    return (thread);
}

SDL_threadID
SDL_GetThreadID(SDL_Thread * thread)
{
    SDL_threadID id;

    if (thread) {
        id = thread->threadid;
    } else {
        id = SDL_ThreadID();
    }
    return id;
}

int
SDL_SetThreadPriority(SDL_ThreadPriority priority)
{
    return SDL_SYS_SetThreadPriority(priority);
}

void
SDL_WaitThread(SDL_Thread * thread, int *status)
{
    if (thread) {
        SDL_SYS_WaitThread(thread);
        if (status) {
            *status = thread->status;
        }
        SDL_DelThread(thread);
        SDL_free(thread);
    }
}

/* vi: set ts=4 sw=4 expandtab: */
