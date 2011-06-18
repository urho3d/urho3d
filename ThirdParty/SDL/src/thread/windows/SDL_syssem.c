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

/* Semaphore functions using the Win32 API */

#include "../../core/windows/SDL_windows.h"

#include "SDL_thread.h"
#if defined(_WIN32_WCE) && (_WIN32_WCE < 300)
#include "win_ce_semaphore.h"
#endif


struct SDL_semaphore
{
#if defined(_WIN32_WCE) && (_WIN32_WCE < 300)
    SYNCHHANDLE id;
#else
    HANDLE id;
#endif
    LONG count;
};


/* Create a semaphore */
SDL_sem *
SDL_CreateSemaphore(Uint32 initial_value)
{
    SDL_sem *sem;

    /* Allocate sem memory */
    sem = (SDL_sem *) SDL_malloc(sizeof(*sem));
    if (sem) {
        /* Create the semaphore, with max value 32K */
#if defined(_WIN32_WCE) && (_WIN32_WCE < 300)
        sem->id = CreateSemaphoreCE(NULL, initial_value, 32 * 1024, NULL);
#else
        sem->id = CreateSemaphore(NULL, initial_value, 32 * 1024, NULL);
#endif
        sem->count = initial_value;
        if (!sem->id) {
            SDL_SetError("Couldn't create semaphore");
            SDL_free(sem);
            sem = NULL;
        }
    } else {
        SDL_OutOfMemory();
    }
    return (sem);
}

/* Free the semaphore */
void
SDL_DestroySemaphore(SDL_sem * sem)
{
    if (sem) {
        if (sem->id) {
#if defined(_WIN32_WCE) && (_WIN32_WCE < 300)
            CloseSynchHandle(sem->id);
#else
            CloseHandle(sem->id);
#endif
            sem->id = 0;
        }
        SDL_free(sem);
    }
}

int
SDL_SemWaitTimeout(SDL_sem * sem, Uint32 timeout)
{
    int retval;
    DWORD dwMilliseconds;

    if (!sem) {
        SDL_SetError("Passed a NULL sem");
        return -1;
    }

    if (timeout == SDL_MUTEX_MAXWAIT) {
        dwMilliseconds = INFINITE;
    } else {
        dwMilliseconds = (DWORD) timeout;
    }
#if defined(_WIN32_WCE) && (_WIN32_WCE < 300)
    switch (WaitForSemaphoreCE(sem->id, dwMilliseconds)) {
#else
    switch (WaitForSingleObject(sem->id, dwMilliseconds)) {
#endif
    case WAIT_OBJECT_0:
        InterlockedDecrement(&sem->count);
        retval = 0;
        break;
    case WAIT_TIMEOUT:
        retval = SDL_MUTEX_TIMEDOUT;
        break;
    default:
        SDL_SetError("WaitForSingleObject() failed");
        retval = -1;
        break;
    }
    return retval;
}

int
SDL_SemTryWait(SDL_sem * sem)
{
    return SDL_SemWaitTimeout(sem, 0);
}

int
SDL_SemWait(SDL_sem * sem)
{
    return SDL_SemWaitTimeout(sem, SDL_MUTEX_MAXWAIT);
}

/* Returns the current count of the semaphore */
Uint32
SDL_SemValue(SDL_sem * sem)
{
    if (!sem) {
        SDL_SetError("Passed a NULL sem");
        return 0;
    }
    return (Uint32)sem->count;
}

int
SDL_SemPost(SDL_sem * sem)
{
    if (!sem) {
        SDL_SetError("Passed a NULL sem");
        return -1;
    }
    /* Increase the counter in the first place, because
     * after a successful release the semaphore may
     * immediately get destroyed by another thread which
     * is waiting for this semaphore.
     */
    InterlockedIncrement(&sem->count);
#if defined(_WIN32_WCE) && (_WIN32_WCE < 300)
    if (ReleaseSemaphoreCE(sem->id, 1, NULL) == FALSE) {
#else
    if (ReleaseSemaphore(sem->id, 1, NULL) == FALSE) {
#endif
        InterlockedDecrement(&sem->count);      /* restore */
        SDL_SetError("ReleaseSemaphore() failed");
        return -1;
    }
    return 0;
}

/* vi: set ts=4 sw=4 expandtab: */
