/*
  Simple DirectMedia Layer
  Copyright (C) 1997-2013 Sam Lantinga <slouken@libsdl.org>

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

// Created by Yao Wei Tjong for Urho3D

#include "SDL_config.h"

#ifndef _SDL_raspiopengles_h
#define _SDL_raspiopengles_h

#include "../SDL_sysvideo.h"
#include <GLES/gl.h>

/* Broadcom VideoCore EGL */
#include <EGL/egl.h>

typedef struct SDL_PrivateGLESData
{
    void *egl_dll_handle;
    EGLDisplay egl_display;
    EGLContext egl_context;
    EGLSurface egl_surface;
    EGLConfig egl_config;
    int egl_swapinterval;

    EGLDisplay(*eglGetDisplay) (NativeDisplayType display);

    EGLBoolean(*eglInitialize) (EGLDisplay dpy, EGLint *major,
                                EGLint *minor);

    EGLBoolean(*eglTerminate) (EGLDisplay dpy);

    void *(*eglGetProcAddress) (const char *procName);

    EGLBoolean(*eglChooseConfig) (EGLDisplay dpy,
                                  const EGLint *attrib_list,
                                  EGLConfig *configs,
                                  EGLint config_size, EGLint *num_config);

    EGLContext(*eglCreateContext) (EGLDisplay dpy,
                                   EGLConfig config,
                                   EGLContext share_list,
                                   const EGLint *attrib_list);

    EGLBoolean(*eglDestroyContext) (EGLDisplay dpy, EGLContext ctx);

    EGLSurface(*eglCreateWindowSurface) (EGLDisplay dpy,
                                         EGLConfig config,
                                         NativeWindowType window,
                                         const EGLint *attrib_list);

    EGLBoolean(*eglDestroySurface) (EGLDisplay dpy, EGLSurface surface);

    EGLBoolean(*eglMakeCurrent) (EGLDisplay dpy, EGLSurface draw,
                                 EGLSurface read, EGLContext ctx);

    EGLBoolean(*eglSwapBuffers) (EGLDisplay dpy, EGLSurface draw);

    EGLBoolean(*eglSwapInterval) (EGLDisplay dpy, EGLint interval);

    EGLBoolean(*eglGetConfigAttrib) (EGLDisplay dpy, EGLConfig config,
                                     EGLint attribute, EGLint *value);
} SDL_PrivateGLESData;

/* OpenGLES functions */
extern void *RASPI_GLES_GetProcAddress(_THIS, const char *proc);
extern int RASPI_GLES_LoadLibrary(_THIS, const char *path);
extern void RASPI_GLES_UnloadLibrary(_THIS);
extern SDL_GLContext RASPI_GLES_CreateContext(_THIS, SDL_Window *window);
extern int RASPI_GLES_MakeCurrent(_THIS, SDL_Window *window,
                                  SDL_GLContext context);
extern int RASPI_GLES_SetSwapInterval(_THIS, int interval);
extern int RASPI_GLES_GetSwapInterval(_THIS);
extern int RASPI_GLES_GetAttribute(_THIS, SDL_GLattr attrib, int *value);
extern void RASPI_GLES_SwapWindow(_THIS, SDL_Window *window);
extern void RASPI_GLES_DeleteContext(_THIS, SDL_GLContext context);
extern int RASPI_GLES_ChooseConfig(_THIS);
#endif /* _SDL_raspiopengles_h */

/* vi: set ts=4 sw=4 expandtab: */
