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

#include "SDL_thread.h"
#include "SDL_timer.h"


#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <errno.h>

#include "SDL_error.h"
#include "SDL_thread.h"


struct SDL_semaphore
{
    int id;
};

/* Not defined by many operating systems, use configure to detect */
/*
#if !defined(HAVE_SEMUN)
union semun {
	int val;
	struct semid_ds *buf;
	ushort *array;
};
#endif
*/

static struct sembuf op_trywait[2] = {
    {0, -1, (IPC_NOWAIT | SEM_UNDO)}    /* Decrement semaphore, no block */
};

static struct sembuf op_wait[2] = {
    {0, -1, SEM_UNDO}           /* Decrement semaphore */
};

static struct sembuf op_post[1] = {
    {0, 1, (IPC_NOWAIT | SEM_UNDO)}     /* Increment semaphore */
};

/* Create a blockable semaphore */
SDL_sem *
SDL_CreateSemaphore(Uint32 initial_value)
{
    extern int _creating_thread_lock;   /* SDL_threads.c */
    SDL_sem *sem;
    union semun init;

    sem = (SDL_sem *) SDL_malloc(sizeof(*sem));
    if (sem == NULL) {
        SDL_OutOfMemory();
        return (NULL);
    }
    sem->id = semget(IPC_PRIVATE, 1, (0600 | IPC_CREAT));
    if (sem->id < 0) {
        SDL_SetError("Couldn't create semaphore");
        SDL_free(sem);
        return (NULL);
    }
    init.val = initial_value;   /* Initialize semaphore */
    semctl(sem->id, 0, SETVAL, init);
    return (sem);
}

void
SDL_DestroySemaphore(SDL_sem * sem)
{
    if (sem) {
#ifdef __IRIX__
        semctl(sem->id, 0, IPC_RMID);
#else
        union semun dummy;
        dummy.val = 0;
        semctl(sem->id, 0, IPC_RMID, dummy);
#endif
        SDL_free(sem);
    }
}

int
SDL_SemTryWait(SDL_sem * sem)
{
    int retval;

    if (!sem) {
        SDL_SetError("Passed a NULL semaphore");
        return -1;
    }

    retval = 0;
  tryagain:
    if (semop(sem->id, op_trywait, 1) < 0) {
        if (errno == EINTR) {
            goto tryagain;
        }
        retval = SDL_MUTEX_TIMEDOUT;
    }
    return retval;
}

int
SDL_SemWait(SDL_sem * sem)
{
    int retval;

    if (!sem) {
        SDL_SetError("Passed a NULL semaphore");
        return -1;
    }

    retval = 0;
  tryagain:
    if (semop(sem->id, op_wait, 1) < 0) {
        if (errno == EINTR) {
            goto tryagain;
        }
        SDL_SetError("Semaphore operation error");
        retval = -1;
    }
    return retval;
}

int
SDL_SemWaitTimeout(SDL_sem * sem, Uint32 timeout)
{
    int retval;

    if (!sem) {
        SDL_SetError("Passed a NULL semaphore");
        return -1;
    }

    /* Try the easy cases first */
    if (timeout == 0) {
        return SDL_SemTryWait(sem);
    }
    if (timeout == SDL_MUTEX_MAXWAIT) {
        return SDL_SemWait(sem);
    }

    /* Ack!  We have to busy wait... */
    timeout += SDL_GetTicks();
    do {
        retval = SDL_SemTryWait(sem);
        if (retval == 0) {
            break;
        }
        SDL_Delay(1);
    } while (SDL_GetTicks() < timeout);

    return retval;
}

Uint32
SDL_SemValue(SDL_sem * sem)
{
    int semval;
    Uint32 value;

    value = 0;
    if (sem) {
      tryagain:
#ifdef __IRIX__
        semval = semctl(sem->id, 0, GETVAL);
#else
        {
            union semun arg;
            arg.val = 0;
            semval = semctl(sem->id, 0, GETVAL, arg);
        }
#endif
        if (semval < 0) {
            if (errno == EINTR) {
                goto tryagain;
            }
        } else {
            value = (Uint32) semval;
        }
    }
    return value;
}

int
SDL_SemPost(SDL_sem * sem)
{
    int retval;

    if (!sem) {
        SDL_SetError("Passed a NULL semaphore");
        return -1;
    }

    retval = 0;
  tryagain:
    if (semop(sem->id, op_post, 1) < 0) {
        if (errno == EINTR) {
            goto tryagain;
        }
        SDL_SetError("Semaphore operation error");
        retval = -1;
    }
    return retval;
}

/* vi: set ts=4 sw=4 expandtab: */
