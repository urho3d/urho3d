/*
    SDL_android_main.c, placed in the public domain by Sam Lantinga  3/13/14
*/

// Modified by Lasse Oorni and Yao Wei Tjong for Urho3D

// Urho3D - use SDK include dir
#include <SDL/SDL_internal.h>

#ifdef __ANDROID__

/* Include the SDL main definition header */ // Urho3D - use SDK include dir
#include <SDL/SDL_main.h>

/*******************************************************************************
                 Functions called by JNI
*******************************************************************************/
#include <jni.h>

// Urho3D: added extra filesDir parameter
/* Called before SDL_main() to initialize JNI bindings in SDL library */
extern void SDL_Android_Init(JNIEnv* env, jclass cls, jstring filesDir);

/* Start up the SDL app */
void Java_org_libsdl_app_SDLActivity_nativeInit(JNIEnv* env, jclass cls, jstring filesDir)
{
    /* This interface could expand with ABI negotiation, calbacks, etc. */
    SDL_Android_Init(env, cls, filesDir);

    SDL_SetMainReady();

    /* Run the application code! */
    int status;
    char *argv[2];
    argv[0] = SDL_strdup("SDL_app");
    argv[1] = NULL;
    status = SDL_main(1, argv);

    /* Do not issue an exit or the whole application will terminate instead of just the SDL thread */
    /* exit(status); */
}

#endif /* __ANDROID__ */

/* vi: set ts=4 sw=4 expandtab: */
