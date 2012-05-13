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
#include "SDL_config.h"

#include "SDL_hints.h"
#include "SDL_hints_c.h"


/* Assuming there aren't many hints set and they aren't being queried in
   critical performance paths, we'll just use a linked list here.
 */
typedef struct SDL_Hint {
    char *name;
    char *value;
    SDL_HintPriority priority;
    SDL_HintChangedCb callback;
    struct SDL_Hint *next;
} SDL_Hint;

static SDL_Hint *SDL_hints;

SDL_bool
SDL_RegisterHintChangedCb(const char *name, SDL_HintChangedCb hintCb)
{
    SDL_Hint *hint;
	
    for (hint = SDL_hints; hint; hint = hint->next) {
        if (SDL_strcmp(name, hint->name) == 0) {
            hint->callback = hintCb;
            return SDL_TRUE;
        }
    }
	
    return SDL_FALSE;
}

SDL_bool
SDL_SetHintWithPriority(const char *name, const char *value,
                        SDL_HintPriority priority)
{
    const char *env;
    SDL_Hint *prev, *hint;

    if (!name || !value) {
        return SDL_FALSE;
    }

    env = SDL_getenv(name);
    if (env && priority < SDL_HINT_OVERRIDE) {
        return SDL_FALSE;
    }

    prev = NULL;
    for (hint = SDL_hints; hint; prev = hint, hint = hint->next) {
        if (SDL_strcmp(name, hint->name) == 0) {
            if (priority < hint->priority) {
                return SDL_FALSE;
            }
            if (SDL_strcmp(hint->value, value) != 0) {
                if (hint->callback != NULL) {
                    (*hint->callback)(name, hint->value, value);
                }
                SDL_free(hint->value);
                hint->value = SDL_strdup(value);
            }
            hint->priority = priority;
            return SDL_TRUE;
        }
    }

    /* Couldn't find the hint, add a new one */
    hint = (SDL_Hint *)SDL_malloc(sizeof(*hint));
    if (!hint) {
        return SDL_FALSE;
    }
    hint->name = SDL_strdup(name);
    hint->value = SDL_strdup(value);
    hint->priority = priority;
    hint->callback = NULL;
    hint->next = SDL_hints;
    SDL_hints = hint;
    return SDL_TRUE;
}

SDL_bool
SDL_SetHint(const char *name, const char *value)
{
    return SDL_SetHintWithPriority(name, value, SDL_HINT_NORMAL);
}

const char *
SDL_GetHint(const char *name)
{
    const char *env;
    SDL_Hint *hint;

    env = SDL_getenv(name);
    for (hint = SDL_hints; hint; hint = hint->next) {
        if (SDL_strcmp(name, hint->name) == 0) {
            if (!env || hint->priority == SDL_HINT_OVERRIDE) {
                return hint->value;
            }
            break;
        }
    }
    return env;
}

void SDL_ClearHints(void)
{
    SDL_Hint *hint;

    while (SDL_hints) {
        hint = SDL_hints;
        SDL_hints = hint->next;

        SDL_free(hint->name);
        SDL_free(hint->value);
        SDL_free(hint);
    }
}

/* vi: set ts=4 sw=4 expandtab: */
