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

#ifndef _SDL_x11opengl_h
#define _SDL_x11opengl_h

#if SDL_VIDEO_OPENGL_GLX
#include "SDL_opengl.h"
#include <GL/glx.h>

struct SDL_GLDriverData
{
    SDL_bool HAS_GLX_EXT_visual_rating;

    void *(*glXGetProcAddress) (const GLubyte * procName);

    XVisualInfo *(*glXChooseVisual)
      (Display * dpy, int screen, int *attribList);

      GLXContext(*glXCreateContext)
      (Display * dpy, XVisualInfo * vis, GLXContext shareList, Bool direct);

    void (*glXDestroyContext)
      (Display * dpy, GLXContext ctx);

      Bool(*glXMakeCurrent)
      (Display * dpy, GLXDrawable drawable, GLXContext ctx);

    void (*glXSwapBuffers)
      (Display * dpy, GLXDrawable drawable);

    int (*glXSwapIntervalSGI) (int interval);
      GLint(*glXSwapIntervalMESA) (unsigned interval);
      GLint(*glXGetSwapIntervalMESA) (void);
};

/* OpenGL functions */
extern int X11_GL_LoadLibrary(_THIS, const char *path);
extern void *X11_GL_GetProcAddress(_THIS, const char *proc);
extern void X11_GL_UnloadLibrary(_THIS);
extern XVisualInfo *X11_GL_GetVisual(_THIS, Display * display, int screen);
extern SDL_GLContext X11_GL_CreateContext(_THIS, SDL_Window * window);
extern int X11_GL_MakeCurrent(_THIS, SDL_Window * window,
                              SDL_GLContext context);
extern int X11_GL_SetSwapInterval(_THIS, int interval);
extern int X11_GL_GetSwapInterval(_THIS);
extern void X11_GL_SwapWindow(_THIS, SDL_Window * window);
extern void X11_GL_DeleteContext(_THIS, SDL_GLContext context);

#endif /* SDL_VIDEO_OPENGL_GLX */

#endif /* _SDL_x11opengl_h */

/* vi: set ts=4 sw=4 expandtab: */
