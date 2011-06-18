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

#include <GLES/gl.h>
#include <GLES/egl.h>
#include <dlfcn.h>
#if defined(__OpenBSD__) && !defined(__ELF__)
#define dlsym(x,y) dlsym(x, "_" y)
#endif

#include "../SDL_sysvideo.h"

typedef struct SDL_PrivateGLESData
{
    int egl_active;             /* to stop switching drivers while we have a valid context */
    XVisualInfo *egl_visualinfo;
    EGLDisplay egl_display;
    EGLContext egl_context;     /* Current GLES context */
    EGLSurface egl_surface;
    EGLConfig egl_config;

      EGLDisplay(*eglGetDisplay) (NativeDisplayType display);
      EGLBoolean(*eglInitialize) (EGLDisplay dpy, EGLint * major,
                                  EGLint * minor);
      EGLBoolean(*eglTerminate) (EGLDisplay dpy);

    void *(*eglGetProcAddress) (const GLubyte * procName);

      EGLBoolean(*eglChooseConfig) (EGLDisplay dpy,
                                    const EGLint * attrib_list,
                                    EGLConfig * configs,
                                    EGLint config_size, EGLint * num_config);

      EGLContext(*eglCreateContext) (EGLDisplay dpy,
                                     EGLConfig config,
                                     EGLContext share_list,
                                     const EGLint * attrib_list);

      EGLBoolean(*eglDestroyContext) (EGLDisplay dpy, EGLContext ctx);

      EGLSurface(*eglCreateWindowSurface) (EGLDisplay dpy,
                                           EGLConfig config,
                                           NativeWindowType window,
                                           const EGLint * attrib_list);
      EGLBoolean(*eglDestroySurface) (EGLDisplay dpy, EGLSurface surface);

      EGLBoolean(*eglMakeCurrent) (EGLDisplay dpy, EGLSurface draw,
                                   EGLSurface read, EGLContext ctx);

      EGLBoolean(*eglSwapBuffers) (EGLDisplay dpy, EGLSurface draw);

    const char *(*eglQueryString) (EGLDisplay dpy, EGLint name);

      EGLBoolean(*eglGetConfigAttrib) (EGLDisplay dpy, EGLConfig config,
                                       EGLint attribute, EGLint * value);

} SDL_PrivateGLESData;

/* OpenGLES functions */
extern SDL_GLContext X11_GLES_CreateContext(_THIS, SDL_Window * window);
extern XVisualInfo *X11_GLES_GetVisual(_THIS, Display * display, int screen);
extern int X11_GLES_MakeCurrent(_THIS, SDL_Window * window,
                                SDL_GLContext context);
extern int X11_GLES_GetAttribute(_THIS, SDL_GLattr attrib, int *value);
extern int X11_GLES_LoadLibrary(_THIS, const char *path);
extern void *X11_GLES_GetProcAddress(_THIS, const char *proc);
extern void X11_GLES_UnloadLibrary(_THIS);

extern int X11_GLES_SetSwapInterval(_THIS, int interval);
extern int X11_GLES_GetSwapInterval(_THIS);
extern void X11_GLES_SwapWindow(_THIS, SDL_Window * window);
extern void X11_GLES_DeleteContext(_THIS, SDL_GLContext context);
