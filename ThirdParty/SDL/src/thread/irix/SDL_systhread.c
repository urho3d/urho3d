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

/* IRIX thread management routines for SDL */

#include <errno.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/prctl.h>

#include "SDL_thread.h"
#include "../SDL_systhread.h"


static int sig_list[] = {
    SIGHUP, SIGINT, SIGQUIT, SIGPIPE, SIGALRM, SIGTERM, SIGCLD, SIGWINCH,
    SIGVTALRM, SIGPROF, 0
};


int
SDL_SYS_CreateThread(SDL_Thread * thread, void *args)
{
    /* Create the thread and go! */
    if (sproc(SDL_RunThread, PR_SALL, args) < 0) {
        SDL_SetError("Not enough resources to create thread");
        return (-1);
    }
    return (0);
}

void
SDL_SYS_SetupThread(void)
{
    int i;
    sigset_t mask;

    /* Mask asynchronous signals for this thread */
    sigemptyset(&mask);
    for (i = 0; sig_list[i]; ++i) {
        sigaddset(&mask, sig_list[i]);
    }
    sigprocmask(SIG_BLOCK, &mask, NULL);
}

SDL_threadID
SDL_ThreadID(void)
{
    return ((SDL_threadID) getpid());
}

void
SDL_WaitThread(SDL_Thread * thread, int *status)
{
    errno = 0;
    while (errno != ECHILD) {
        waitpid(thread->handle, NULL, 0);
    }
}

/* vi: set ts=4 sw=4 expandtab: */
