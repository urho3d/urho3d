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

#ifndef _SDL_dmaaudio_h
#define _SDL_dmaaudio_h

#include "../SDL_sysaudio.h"

/* Hidden "this" pointer for the audio functions */
#define _THIS	SDL_AudioDevice *this

struct SDL_PrivateAudioData
{
    /* The file descriptor for the audio device */
    int audio_fd;

    /* The parent process id, to detect when application quits */
    pid_t parent;

    /* Raw mixing buffer */
    Uint8 *dma_buf;
    int dma_len;
    int num_buffers;

    /* Support for audio timing using a timer, in addition to select() */
    float frame_ticks;
    float next_frame;
};
#define FUDGE_TICKS	10      /* The scheduler overhead ticks per frame */

/* Old variable names */
/* !!! FIXME: remove these. */
#define audio_fd		(this->hidden->audio_fd)
#define parent			(this->hidden->parent)
#define dma_buf			(this->hidden->dma_buf)
#define dma_len			(this->hidden->dma_len)
#define num_buffers		(this->hidden->num_buffers)
#define frame_ticks		(this->hidden->frame_ticks)
#define next_frame		(this->hidden->next_frame)

#endif /* _SDL_dmaaudio_h */

/* vi: set ts=4 sw=4 expandtab: */
