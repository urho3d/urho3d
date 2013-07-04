// Modified by Lasse Oorni for Urho3D

#include "SDL_config.h"

#ifdef __ANDROID__

/* Include the SDL main definition header */
#include "SDL_main.h"

/*******************************************************************************
                 Functions called by JNI
*******************************************************************************/
#include <jni.h>

// Called before SDL_main() to initialize JNI bindings in SDL library
// Urho3D: added passing user files directory from SDLActivity on startup
extern "C" void SDL_Android_Init(JNIEnv* env, jclass cls, jstring filesDir);

// Start up the SDL app
// Urho3D: added passing user files directory from SDLActivity on startup
extern "C" void Java_org_libsdl_app_SDLActivity_nativeInit(JNIEnv* env, jclass cls, jstring filesDir)
{
    /* This interface could expand with ABI negotiation, calbacks, etc. */
    SDL_Android_Init(env, cls, filesDir);

    SDL_SetMainReady();

    /* Run the application code! */
    int status;
    char *argv[2];
    argv[0] = strdup("SDL_app");
    argv[1] = NULL;
    status = SDL_main(1, argv);

    /* Do not issue an exit or the whole application will terminate instead of just the SDL thread */
    //exit(status);
}

#endif /* __ANDROID__ */

/* vi: set ts=4 sw=4 expandtab: */
