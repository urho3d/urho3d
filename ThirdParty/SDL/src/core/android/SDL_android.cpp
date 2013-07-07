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

// Modified by Lasse Oorni for Urho3D

#include "SDL_config.h"
#include "SDL_stdinc.h"
#include "SDL_assert.h"
#include "SDL_log.h"
#include "SDL_main.h"

#ifdef __ANDROID__

#include "SDL_system.h"
#include "SDL_android.h"
// Urho3D: do not require EGL to allow compiling on API level 8
// #include <EGL/egl.h>
#define EGL_BUFFER_SIZE			0x3020
#define EGL_ALPHA_SIZE			0x3021
#define EGL_BLUE_SIZE			0x3022
#define EGL_GREEN_SIZE			0x3023
#define EGL_RED_SIZE			0x3024
#define EGL_DEPTH_SIZE			0x3025
#define EGL_STENCIL_SIZE		0x3026
#define EGL_SAMPLES			0x3031
#define EGL_SAMPLE_BUFFERS		0x3032
#define EGL_RENDERABLE_TYPE		0x3040
#define EGL_OPENGL_ES_BIT		0x0001	/* EGL_RENDERABLE_TYPE mask bits */
#define EGL_OPENGL_ES2_BIT		0x0004	/* EGL_RENDERABLE_TYPE mask bits */
#define EGL_NONE			0x3038	/* Attrib list terminator */

extern "C" {
#include "../../events/SDL_events_c.h"
#include "../../video/android/SDL_androidkeyboard.h"
#include "../../video/android/SDL_androidtouch.h"
#include "../../video/android/SDL_androidvideo.h"

#include <android/log.h>
#include <pthread.h>
#include <sys/types.h>
#include <unistd.h>
#define LOG_TAG "SDL_android"
//#define LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)
//#define LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)
#define LOGI(...) do {} while (false)
#define LOGE(...) do {} while (false)

/* Uncomment this to log messages entering and exiting methods in this file */
//#define DEBUG_JNI

/* Implemented in audio/android/SDL_androidaudio.c */
extern void Android_RunAudioThread();

static void Android_JNI_ThreadDestroyed(void*);
} // C

/*******************************************************************************
 This file links the Java side of Android with libsdl
*******************************************************************************/
#include <jni.h>
#include <android/log.h>


/*******************************************************************************
                               Globals
*******************************************************************************/
static pthread_key_t mThreadKey;
static JavaVM* mJavaVM;

// Main activity
static jclass mActivityClass;

// method signatures
static jmethodID midCreateGLContext;
static jmethodID midFlipBuffers;
static jmethodID midAudioInit;
static jmethodID midAudioWriteShortBuffer;
static jmethodID midAudioWriteByteBuffer;
static jmethodID midAudioQuit;

// Accelerometer data storage
static float fLastAccelerometer[3];
static bool bHasNewData;

// Urho3D: application files dir
static char* mFilesDir = 0;

/*******************************************************************************
                 Functions called by JNI
*******************************************************************************/

// Library init
extern "C" jint JNI_OnLoad(JavaVM* vm, void* reserved)
{
    JNIEnv *env;
    mJavaVM = vm;
    LOGI("JNI_OnLoad called");
    if (mJavaVM->GetEnv((void**) &env, JNI_VERSION_1_4) != JNI_OK) {
        LOGE("Failed to get the environment using GetEnv()");
        return -1;
    }
    /*
     * Create mThreadKey so we can keep track of the JNIEnv assigned to each thread
     * Refer to http://developer.android.com/guide/practices/design/jni.html for the rationale behind this
     */
    if (pthread_key_create(&mThreadKey, Android_JNI_ThreadDestroyed)) {
        __android_log_print(ANDROID_LOG_ERROR, "SDL", "Error initializing pthread key");
    }
    else {
        Android_JNI_SetupThread();
    }

    return JNI_VERSION_1_4;
}

// Urho3D: added function
extern "C" const char* SDL_Android_GetFilesDir()
{
    return mFilesDir;
}

// Called before SDL_main() to initialize JNI bindings
// Urho3D: added passing user files directory from SDLActivity on startup
extern "C" void SDL_Android_Init(JNIEnv* mEnv, jclass cls, jstring filesDir)
{
    __android_log_print(ANDROID_LOG_INFO, "SDL", "SDL_Android_Init()");

    Android_JNI_SetupThread();

    // Copy the files dir
    const char *str;
    str = mEnv->GetStringUTFChars(filesDir, 0);
    if (str)
    {
        if (mFilesDir)
            free(mFilesDir);

        size_t length = strlen(str) + 1;
        mFilesDir = (char*)malloc(length);
        memcpy(mFilesDir, str, length);
        mEnv->ReleaseStringUTFChars(filesDir, str);
    }

    mActivityClass = (jclass)mEnv->NewGlobalRef(cls);

    midCreateGLContext = mEnv->GetStaticMethodID(mActivityClass,
                                "createGLContext","(II[I)Z");
    midFlipBuffers = mEnv->GetStaticMethodID(mActivityClass,
                                "flipBuffers","()V");
    midAudioInit = mEnv->GetStaticMethodID(mActivityClass,
                                "audioInit", "(IZZI)V");
    midAudioWriteShortBuffer = mEnv->GetStaticMethodID(mActivityClass,
                                "audioWriteShortBuffer", "([S)V");
    midAudioWriteByteBuffer = mEnv->GetStaticMethodID(mActivityClass,
                                "audioWriteByteBuffer", "([B)V");
    midAudioQuit = mEnv->GetStaticMethodID(mActivityClass,
                                "audioQuit", "()V");

    bHasNewData = false;

    if(!midCreateGLContext || !midFlipBuffers || !midAudioInit ||
       !midAudioWriteShortBuffer || !midAudioWriteByteBuffer || !midAudioQuit) {
        __android_log_print(ANDROID_LOG_WARN, "SDL", "SDL: Couldn't locate Java callbacks, check that they're named and typed correctly");
    }
    __android_log_print(ANDROID_LOG_INFO, "SDL", "SDL_Android_Init() finished!");
}

// Resize
extern "C" void Java_org_libsdl_app_SDLActivity_onNativeResize(
                                    JNIEnv* env, jclass jcls,
                                    jint width, jint height, jint format)
{
    Android_SetScreenResolution(width, height, format);
}

// Keydown
extern "C" void Java_org_libsdl_app_SDLActivity_onNativeKeyDown(
                                    JNIEnv* env, jclass jcls, jint keycode)
{
    Android_OnKeyDown(keycode);
}

// Keyup
extern "C" void Java_org_libsdl_app_SDLActivity_onNativeKeyUp(
                                    JNIEnv* env, jclass jcls, jint keycode)
{
    Android_OnKeyUp(keycode);
}

// Touch
extern "C" void Java_org_libsdl_app_SDLActivity_onNativeTouch(
                                    JNIEnv* env, jclass jcls,
                                    jint touch_device_id_in, jint pointer_finger_id_in,
                                    jint action, jfloat x, jfloat y, jfloat p)
{
    Android_OnTouch(touch_device_id_in, pointer_finger_id_in, action, x, y, p);
}

// Accelerometer
extern "C" void Java_org_libsdl_app_SDLActivity_onNativeAccel(
                                    JNIEnv* env, jclass jcls,
                                    jfloat x, jfloat y, jfloat z)
{
    fLastAccelerometer[0] = x;
    fLastAccelerometer[1] = y;
    fLastAccelerometer[2] = z;
    bHasNewData = true;
}

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

// Low memory
extern "C" void Java_org_libsdl_app_SDLActivity_nativeLowMemory(
                                    JNIEnv* env, jclass cls)
{
    SDL_SendAppEvent(SDL_APP_LOWMEMORY);
}

// Quit
extern "C" void Java_org_libsdl_app_SDLActivity_nativeQuit(
                                    JNIEnv* env, jclass cls)
{
    // Inject a SDL_QUIT event
    SDL_SendQuit();
    SDL_SendAppEvent(SDL_APP_TERMINATING);
}

// Pause
extern "C" void Java_org_libsdl_app_SDLActivity_nativePause(
                                    JNIEnv* env, jclass cls)
{
    if (Android_Window) {
        /* Signal the pause semaphore so the event loop knows to pause and (optionally) block itself */
        if (!SDL_SemValue(Android_PauseSem)) SDL_SemPost(Android_PauseSem);
        SDL_SendWindowEvent(Android_Window, SDL_WINDOWEVENT_FOCUS_LOST, 0, 0);
        SDL_SendWindowEvent(Android_Window, SDL_WINDOWEVENT_MINIMIZED, 0, 0);
    }

    __android_log_print(ANDROID_LOG_VERBOSE, "SDL", "nativePause()");
    SDL_SendAppEvent(SDL_APP_WILLENTERBACKGROUND);
    SDL_SendAppEvent(SDL_APP_DIDENTERBACKGROUND);
}

// Resume
extern "C" void Java_org_libsdl_app_SDLActivity_nativeResume(
                                    JNIEnv* env, jclass cls)
{
    __android_log_print(ANDROID_LOG_VERBOSE, "SDL", "nativeResume()");
    SDL_SendAppEvent(SDL_APP_WILLENTERFOREGROUND);
    SDL_SendAppEvent(SDL_APP_DIDENTERFOREGROUND);

    if (Android_Window) {
        /* Signal the resume semaphore so the event loop knows to resume and restore the GL Context
         * We can't restore the GL Context here because it needs to be done on the SDL main thread
         * and this function will be called from the Java thread instead.
         */
        if (!SDL_SemValue(Android_ResumeSem)) SDL_SemPost(Android_ResumeSem);
        SDL_SendWindowEvent(Android_Window, SDL_WINDOWEVENT_FOCUS_GAINED, 0, 0);
        SDL_SendWindowEvent(Android_Window, SDL_WINDOWEVENT_RESTORED, 0, 0);
    }
}

extern "C" void Java_org_libsdl_app_SDLActivity_nativeRunAudioThread(
                                    JNIEnv* env, jclass cls)
{
    /* This is the audio thread, with a different environment */
    Android_JNI_SetupThread();

    Android_RunAudioThread();
}

extern "C" void Java_org_libsdl_app_SDLInputConnection_nativeCommitText(
                                    JNIEnv* env, jclass cls,
                                    jstring text, jint newCursorPosition)
{
    const char *utftext = env->GetStringUTFChars(text, NULL);

    SDL_SendKeyboardText(utftext);

    env->ReleaseStringUTFChars(text, utftext);
}

extern "C" void Java_org_libsdl_app_SDLInputConnection_nativeSetComposingText(
                                    JNIEnv* env, jclass cls,
                                    jstring text, jint newCursorPosition)
{
    const char *utftext = env->GetStringUTFChars(text, NULL);

    SDL_SendEditingText(utftext, 0, 0);

    env->ReleaseStringUTFChars(text, utftext);
}



/*******************************************************************************
             Functions called by SDL into Java
*******************************************************************************/

class LocalReferenceHolder
{
private:
    static int s_active;

public:
    static bool IsActive() {
        return s_active > 0;
    }

public:
    LocalReferenceHolder(const char *func) : m_env(NULL), m_func(func) {
#ifdef DEBUG_JNI
        SDL_Log("Entering function %s", m_func);
#endif
    }
    ~LocalReferenceHolder() {
#ifdef DEBUG_JNI
        SDL_Log("Leaving function %s", m_func);
#endif
        if (m_env) {
            m_env->PopLocalFrame(NULL);
            --s_active;
        }
    }

    bool init(JNIEnv *env, jint capacity = 16) {
        if (env->PushLocalFrame(capacity) < 0) {
            SDL_SetError("Failed to allocate enough JVM local references");
            return false;
        }
        ++s_active;
        m_env = env;
        return true;
    }

protected:
    JNIEnv *m_env;
    const char *m_func;
};
int LocalReferenceHolder::s_active;

extern "C" SDL_bool Android_JNI_CreateContext(int majorVersion, int minorVersion,
                                int red, int green, int blue, int alpha,
                                int buffer, int depth, int stencil,
                                int buffers, int samples)
{
    JNIEnv *env = Android_JNI_GetEnv();

    jint attribs[] = {
        EGL_RED_SIZE, red,
        EGL_GREEN_SIZE, green,
        EGL_BLUE_SIZE, blue,
        EGL_ALPHA_SIZE, alpha,
        EGL_BUFFER_SIZE, buffer,
        EGL_DEPTH_SIZE, depth,
        EGL_STENCIL_SIZE, stencil,
        EGL_SAMPLE_BUFFERS, buffers,
        EGL_SAMPLES, samples,
        EGL_RENDERABLE_TYPE, (majorVersion == 1 ? EGL_OPENGL_ES_BIT : EGL_OPENGL_ES2_BIT),
        EGL_NONE
    };
    int len = SDL_arraysize(attribs);

    jintArray array;

    array = env->NewIntArray(len);
    env->SetIntArrayRegion(array, 0, len, attribs);

    jboolean success = env->CallStaticBooleanMethod(mActivityClass, midCreateGLContext, majorVersion, minorVersion, array);

    env->DeleteLocalRef(array);

    return success ? SDL_TRUE : SDL_FALSE;
}

extern "C" void Android_JNI_SwapWindow()
{
    JNIEnv *mEnv = Android_JNI_GetEnv();
    mEnv->CallStaticVoidMethod(mActivityClass, midFlipBuffers);
}

extern "C" void Android_JNI_SetActivityTitle(const char *title)
{
    jmethodID mid;
    JNIEnv *mEnv = Android_JNI_GetEnv();
    mid = mEnv->GetStaticMethodID(mActivityClass,"setActivityTitle","(Ljava/lang/String;)Z");
    if (mid) {
        jstring jtitle = reinterpret_cast<jstring>(mEnv->NewStringUTF(title));
        mEnv->CallStaticBooleanMethod(mActivityClass, mid, jtitle);
        mEnv->DeleteLocalRef(jtitle);
    }
}

extern "C" SDL_bool Android_JNI_GetAccelerometerValues(float values[3])
{
    int i;
    SDL_bool retval = SDL_FALSE;

    if (bHasNewData) {
        for (i = 0; i < 3; ++i) {
            values[i] = fLastAccelerometer[i];
        }
        bHasNewData = false;
        retval = SDL_TRUE;
    }

    return retval;
}

static void Android_JNI_ThreadDestroyed(void* value) {
    /* The thread is being destroyed, detach it from the Java VM and set the mThreadKey value to NULL as required */
    JNIEnv *env = (JNIEnv*) value;
    if (env != NULL) {
        mJavaVM->DetachCurrentThread();
        pthread_setspecific(mThreadKey, NULL);
    }
}

JNIEnv* Android_JNI_GetEnv(void) {
    /* From http://developer.android.com/guide/practices/jni.html
     * All threads are Linux threads, scheduled by the kernel.
     * They're usually started from managed code (using Thread.start), but they can also be created elsewhere and then
     * attached to the JavaVM. For example, a thread started with pthread_create can be attached with the
     * JNI AttachCurrentThread or AttachCurrentThreadAsDaemon functions. Until a thread is attached, it has no JNIEnv,
     * and cannot make JNI calls.
     * Attaching a natively-created thread causes a java.lang.Thread object to be constructed and added to the "main"
     * ThreadGroup, making it visible to the debugger. Calling AttachCurrentThread on an already-attached thread
     * is a no-op.
     * Note: You can call this function any number of times for the same thread, there's no harm in it
     */

    JNIEnv *env;
    int status = mJavaVM->AttachCurrentThread(&env, NULL);
    if(status < 0) {
        LOGE("failed to attach current thread");
        return 0;
    }

    return env;
}

int Android_JNI_SetupThread(void) {
    /* From http://developer.android.com/guide/practices/jni.html
     * Threads attached through JNI must call DetachCurrentThread before they exit. If coding this directly is awkward,
     * in Android 2.0 (Eclair) and higher you can use pthread_key_create to define a destructor function that will be
     * called before the thread exits, and call DetachCurrentThread from there. (Use that key with pthread_setspecific
     * to store the JNIEnv in thread-local-storage; that way it'll be passed into your destructor as the argument.)
     * Note: The destructor is not called unless the stored value is != NULL
     * Note: You can call this function any number of times for the same thread, there's no harm in it
     *       (except for some lost CPU cycles)
     */
    JNIEnv *env = Android_JNI_GetEnv();
    pthread_setspecific(mThreadKey, (void*) env);
    return 1;
}

//
// Audio support
//
static jboolean audioBuffer16Bit = JNI_FALSE;
static jboolean audioBufferStereo = JNI_FALSE;
static jobject audioBuffer = NULL;
static void* audioBufferPinned = NULL;

extern "C" int Android_JNI_OpenAudioDevice(int sampleRate, int is16Bit, int channelCount, int desiredBufferFrames)
{
    int audioBufferFrames;

    JNIEnv *env = Android_JNI_GetEnv();

    if (!env) {
        LOGE("callback_handler: failed to attach current thread");
    }
    Android_JNI_SetupThread();

    __android_log_print(ANDROID_LOG_VERBOSE, "SDL", "SDL audio: opening device");
    audioBuffer16Bit = is16Bit;
    audioBufferStereo = channelCount > 1;

    env->CallStaticVoidMethod(mActivityClass, midAudioInit, sampleRate, audioBuffer16Bit, audioBufferStereo, desiredBufferFrames);

    /* Allocating the audio buffer from the Java side and passing it as the return value for audioInit no longer works on
     * Android >= 4.2 due to a "stale global reference" error. So now we allocate this buffer directly from this side. */

    if (is16Bit) {
        jshortArray audioBufferLocal = env->NewShortArray(desiredBufferFrames * (audioBufferStereo ? 2 : 1));
        if (audioBufferLocal) {
            audioBuffer = env->NewGlobalRef(audioBufferLocal);
            env->DeleteLocalRef(audioBufferLocal);
        }
    }
    else {
        jbyteArray audioBufferLocal = env->NewByteArray(desiredBufferFrames * (audioBufferStereo ? 2 : 1));
        if (audioBufferLocal) {
            audioBuffer = env->NewGlobalRef(audioBufferLocal);
            env->DeleteLocalRef(audioBufferLocal);
        }
    }

    if (audioBuffer == NULL) {
        __android_log_print(ANDROID_LOG_WARN, "SDL", "SDL audio: could not allocate an audio buffer!");
        return 0;
    }

    jboolean isCopy = JNI_FALSE;
    if (audioBuffer16Bit) {
        audioBufferPinned = env->GetShortArrayElements((jshortArray)audioBuffer, &isCopy);
        audioBufferFrames = env->GetArrayLength((jshortArray)audioBuffer);
    } else {
        audioBufferPinned = env->GetByteArrayElements((jbyteArray)audioBuffer, &isCopy);
        audioBufferFrames = env->GetArrayLength((jbyteArray)audioBuffer);
    }
    if (audioBufferStereo) {
        audioBufferFrames /= 2;
    }

    return audioBufferFrames;
}

extern "C" void * Android_JNI_GetAudioBuffer()
{
    return audioBufferPinned;
}

extern "C" void Android_JNI_WriteAudioBuffer()
{
    JNIEnv *mAudioEnv = Android_JNI_GetEnv();

    if (audioBuffer16Bit) {
        mAudioEnv->ReleaseShortArrayElements((jshortArray)audioBuffer, (jshort *)audioBufferPinned, JNI_COMMIT);
        mAudioEnv->CallStaticVoidMethod(mActivityClass, midAudioWriteShortBuffer, (jshortArray)audioBuffer);
    } else {
        mAudioEnv->ReleaseByteArrayElements((jbyteArray)audioBuffer, (jbyte *)audioBufferPinned, JNI_COMMIT);
        mAudioEnv->CallStaticVoidMethod(mActivityClass, midAudioWriteByteBuffer, (jbyteArray)audioBuffer);
    }

    /* JNI_COMMIT means the changes are committed to the VM but the buffer remains pinned */
}

extern "C" void Android_JNI_CloseAudioDevice()
{
    JNIEnv *env = Android_JNI_GetEnv();

    env->CallStaticVoidMethod(mActivityClass, midAudioQuit);

    if (audioBuffer) {
        env->DeleteGlobalRef(audioBuffer);
        audioBuffer = NULL;
        audioBufferPinned = NULL;
    }
}

// Test for an exception and call SDL_SetError with its detail if one occurs
// If optional parameter silent is truthy then SDL_SetError() is not called.
static bool Android_JNI_ExceptionOccurred(bool silent = false)
{
    SDL_assert(LocalReferenceHolder::IsActive());
    JNIEnv *mEnv = Android_JNI_GetEnv();

    jthrowable exception = mEnv->ExceptionOccurred();
    if (exception != NULL) {
        jmethodID mid;

        // Until this happens most JNI operations have undefined behaviour
        mEnv->ExceptionClear();

        if (!silent) {
            jclass exceptionClass = mEnv->GetObjectClass(exception);
            jclass classClass = mEnv->FindClass("java/lang/Class");

            mid = mEnv->GetMethodID(classClass, "getName", "()Ljava/lang/String;");
            jstring exceptionName = (jstring)mEnv->CallObjectMethod(exceptionClass, mid);
            const char* exceptionNameUTF8 = mEnv->GetStringUTFChars(exceptionName, 0);

            mid = mEnv->GetMethodID(exceptionClass, "getMessage", "()Ljava/lang/String;");
            jstring exceptionMessage = (jstring)mEnv->CallObjectMethod(exception, mid);

            if (exceptionMessage != NULL) {
                const char* exceptionMessageUTF8 = mEnv->GetStringUTFChars(exceptionMessage, 0);
                SDL_SetError("%s: %s", exceptionNameUTF8, exceptionMessageUTF8);
                mEnv->ReleaseStringUTFChars(exceptionMessage, exceptionMessageUTF8);
            } else {
                SDL_SetError("%s", exceptionNameUTF8);
            }

            mEnv->ReleaseStringUTFChars(exceptionName, exceptionNameUTF8);
        }

        return true;
    }

    return false;
}

static int Android_JNI_FileOpen(SDL_RWops* ctx)
{
    LocalReferenceHolder refs(__FUNCTION__);
    int result = 0;

    jmethodID mid;
    jobject context;
    jobject assetManager;
    jobject inputStream;
    jclass channels;
    jobject readableByteChannel;
    jstring fileNameJString;
    jobject fd;
    jclass fdCls;
    jfieldID descriptor;

    JNIEnv *mEnv = Android_JNI_GetEnv();
    if (!refs.init(mEnv)) {
        goto failure;
    }

    fileNameJString = (jstring)ctx->hidden.androidio.fileNameRef;
    ctx->hidden.androidio.position = 0;

    // context = SDLActivity.getContext();
    mid = mEnv->GetStaticMethodID(mActivityClass,
            "getContext","()Landroid/content/Context;");
    context = mEnv->CallStaticObjectMethod(mActivityClass, mid);


    // assetManager = context.getAssets();
    mid = mEnv->GetMethodID(mEnv->GetObjectClass(context),
            "getAssets", "()Landroid/content/res/AssetManager;");
    assetManager = mEnv->CallObjectMethod(context, mid);

    /* First let's try opening the file to obtain an AssetFileDescriptor.
    * This method reads the files directly from the APKs using standard *nix calls
    */
    mid = mEnv->GetMethodID(mEnv->GetObjectClass(assetManager), "openFd", "(Ljava/lang/String;)Landroid/content/res/AssetFileDescriptor;");
    inputStream = mEnv->CallObjectMethod(assetManager, mid, fileNameJString);
    if (Android_JNI_ExceptionOccurred(true)) {
        goto fallback;
    }

    mid = mEnv->GetMethodID(mEnv->GetObjectClass(inputStream), "getStartOffset", "()J");
    ctx->hidden.androidio.offset = mEnv->CallLongMethod(inputStream, mid);
    if (Android_JNI_ExceptionOccurred(true)) {
        goto fallback;
    }

    mid = mEnv->GetMethodID(mEnv->GetObjectClass(inputStream), "getDeclaredLength", "()J");
    ctx->hidden.androidio.size = mEnv->CallLongMethod(inputStream, mid);
    if (Android_JNI_ExceptionOccurred(true)) {
        goto fallback;
    }

    mid = mEnv->GetMethodID(mEnv->GetObjectClass(inputStream), "getFileDescriptor", "()Ljava/io/FileDescriptor;");
    fd = mEnv->CallObjectMethod(inputStream, mid);
    fdCls = mEnv->GetObjectClass(fd);
    descriptor = mEnv->GetFieldID(fdCls, "descriptor", "I");
    ctx->hidden.androidio.fd = mEnv->GetIntField(fd, descriptor);
    ctx->hidden.androidio.assetFileDescriptorRef = mEnv->NewGlobalRef(inputStream);

    // Seek to the correct offset in the file.
    lseek(ctx->hidden.androidio.fd, (off_t)ctx->hidden.androidio.offset, SEEK_SET);

    if (false) {
fallback:
        // Disabled log message because of spam on the Nexus 7
        //__android_log_print(ANDROID_LOG_DEBUG, "SDL", "Falling back to legacy InputStream method for opening file");

        /* Try the old method using InputStream */
        ctx->hidden.androidio.assetFileDescriptorRef = NULL;

        // inputStream = assetManager.open(<filename>);
        mid = mEnv->GetMethodID(mEnv->GetObjectClass(assetManager),
                "open", "(Ljava/lang/String;I)Ljava/io/InputStream;");
        inputStream = mEnv->CallObjectMethod(assetManager, mid, fileNameJString, 1 /*ACCESS_RANDOM*/);
        if (Android_JNI_ExceptionOccurred()) {
            goto failure;
        }

        ctx->hidden.androidio.inputStreamRef = mEnv->NewGlobalRef(inputStream);

        // Despite all the visible documentation on [Asset]InputStream claiming
        // that the .available() method is not guaranteed to return the entire file
        // size, comments in <sdk>/samples/<ver>/ApiDemos/src/com/example/ ...
        // android/apis/content/ReadAsset.java imply that Android's
        // AssetInputStream.available() /will/ always return the total file size

        // size = inputStream.available();
        mid = mEnv->GetMethodID(mEnv->GetObjectClass(inputStream),
                "available", "()I");
        ctx->hidden.androidio.size = (long)mEnv->CallIntMethod(inputStream, mid);
        if (Android_JNI_ExceptionOccurred()) {
            goto failure;
        }

        // readableByteChannel = Channels.newChannel(inputStream);
        channels = mEnv->FindClass("java/nio/channels/Channels");
        mid = mEnv->GetStaticMethodID(channels,
                "newChannel",
                "(Ljava/io/InputStream;)Ljava/nio/channels/ReadableByteChannel;");
        readableByteChannel = mEnv->CallStaticObjectMethod(
                channels, mid, inputStream);
        if (Android_JNI_ExceptionOccurred()) {
            goto failure;
        }

        ctx->hidden.androidio.readableByteChannelRef =
            mEnv->NewGlobalRef(readableByteChannel);

        // Store .read id for reading purposes
        mid = mEnv->GetMethodID(mEnv->GetObjectClass(readableByteChannel),
                "read", "(Ljava/nio/ByteBuffer;)I");
        ctx->hidden.androidio.readMethod = mid;
    }

    if (false) {
failure:
        result = -1;

        mEnv->DeleteGlobalRef((jobject)ctx->hidden.androidio.fileNameRef);

        if(ctx->hidden.androidio.inputStreamRef != NULL) {
            mEnv->DeleteGlobalRef((jobject)ctx->hidden.androidio.inputStreamRef);
        }

        if(ctx->hidden.androidio.readableByteChannelRef != NULL) {
            mEnv->DeleteGlobalRef((jobject)ctx->hidden.androidio.readableByteChannelRef);
        }

        if(ctx->hidden.androidio.assetFileDescriptorRef != NULL) {
            mEnv->DeleteGlobalRef((jobject)ctx->hidden.androidio.assetFileDescriptorRef);
        }

    }

    return result;
}

extern "C" int Android_JNI_FileOpen(SDL_RWops* ctx,
        const char* fileName, const char*)
{
    LocalReferenceHolder refs(__FUNCTION__);
    JNIEnv *mEnv = Android_JNI_GetEnv();

    if (!refs.init(mEnv)) {
        return -1;
    }

    if (!ctx) {
        return -1;
    }

    jstring fileNameJString = mEnv->NewStringUTF(fileName);
    ctx->hidden.androidio.fileNameRef = mEnv->NewGlobalRef(fileNameJString);
    ctx->hidden.androidio.inputStreamRef = NULL;
    ctx->hidden.androidio.readableByteChannelRef = NULL;
    ctx->hidden.androidio.readMethod = NULL;
    ctx->hidden.androidio.assetFileDescriptorRef = NULL;

    return Android_JNI_FileOpen(ctx);
}

extern "C" size_t Android_JNI_FileRead(SDL_RWops* ctx, void* buffer,
        size_t size, size_t maxnum)
{
    LocalReferenceHolder refs(__FUNCTION__);

    if (ctx->hidden.androidio.assetFileDescriptorRef) {
        size_t bytesMax = size * maxnum;
        if (ctx->hidden.androidio.size != -1 /*UNKNOWN_LENGTH*/ && ctx->hidden.androidio.position + bytesMax > ctx->hidden.androidio.size) {
            bytesMax = ctx->hidden.androidio.size - ctx->hidden.androidio.position;
        }
        size_t result = read(ctx->hidden.androidio.fd, buffer, bytesMax );
        if (result > 0) {
            ctx->hidden.androidio.position += result;
            return result / size;
        }
        return 0;
    } else {
        jlong bytesRemaining = (jlong) (size * maxnum);
        jlong bytesMax = (jlong) (ctx->hidden.androidio.size -  ctx->hidden.androidio.position);
        int bytesRead = 0;

        /* Don't read more bytes than those that remain in the file, otherwise we get an exception */
        if (bytesRemaining >  bytesMax) bytesRemaining = bytesMax;

        JNIEnv *mEnv = Android_JNI_GetEnv();
        if (!refs.init(mEnv)) {
            return -1;
        }

        jobject readableByteChannel = (jobject)ctx->hidden.androidio.readableByteChannelRef;
        jmethodID readMethod = (jmethodID)ctx->hidden.androidio.readMethod;
        jobject byteBuffer = mEnv->NewDirectByteBuffer(buffer, bytesRemaining);

        while (bytesRemaining > 0) {
            // result = readableByteChannel.read(...);
            int result = mEnv->CallIntMethod(readableByteChannel, readMethod, byteBuffer);

            if (Android_JNI_ExceptionOccurred()) {
                return 0;
            }

            if (result < 0) {
                break;
            }

            bytesRemaining -= result;
            bytesRead += result;
            ctx->hidden.androidio.position += result;
        }
        return bytesRead / size;
    }
}

extern "C" size_t Android_JNI_FileWrite(SDL_RWops* ctx, const void* buffer,
        size_t size, size_t num)
{
    SDL_SetError("Cannot write to Android package filesystem");
    return 0;
}

static int Android_JNI_FileClose(SDL_RWops* ctx, bool release)
{
    LocalReferenceHolder refs(__FUNCTION__);
    int result = 0;
    JNIEnv *mEnv = Android_JNI_GetEnv();

    if (!refs.init(mEnv)) {
        return SDL_SetError("Failed to allocate enough JVM local references");
    }

    if (ctx) {
        if (release) {
            mEnv->DeleteGlobalRef((jobject)ctx->hidden.androidio.fileNameRef);
        }

        if (ctx->hidden.androidio.assetFileDescriptorRef) {
            jobject inputStream = (jobject)ctx->hidden.androidio.assetFileDescriptorRef;
            jmethodID mid = mEnv->GetMethodID(mEnv->GetObjectClass(inputStream),
                    "close", "()V");
            mEnv->CallVoidMethod(inputStream, mid);
            mEnv->DeleteGlobalRef((jobject)ctx->hidden.androidio.assetFileDescriptorRef);
            if (Android_JNI_ExceptionOccurred()) {
                result = -1;
            }
        }
        else {
            jobject inputStream = (jobject)ctx->hidden.androidio.inputStreamRef;

            // inputStream.close();
            jmethodID mid = mEnv->GetMethodID(mEnv->GetObjectClass(inputStream),
                    "close", "()V");
            mEnv->CallVoidMethod(inputStream, mid);
            mEnv->DeleteGlobalRef((jobject)ctx->hidden.androidio.inputStreamRef);
            mEnv->DeleteGlobalRef((jobject)ctx->hidden.androidio.readableByteChannelRef);
            if (Android_JNI_ExceptionOccurred()) {
                result = -1;
            }
        }

        if (release) {
            SDL_FreeRW(ctx);
        }
    }

    return result;
}


extern "C" Sint64 Android_JNI_FileSize(SDL_RWops* ctx)
{
    return ctx->hidden.androidio.size;
}

extern "C" Sint64 Android_JNI_FileSeek(SDL_RWops* ctx, Sint64 offset, int whence)
{
    if (ctx->hidden.androidio.assetFileDescriptorRef) {
        switch (whence) {
            case RW_SEEK_SET:
                if (ctx->hidden.androidio.size != -1 /*UNKNOWN_LENGTH*/ && offset > ctx->hidden.androidio.size) offset = ctx->hidden.androidio.size;
                offset += ctx->hidden.androidio.offset;
                break;
            case RW_SEEK_CUR:
                offset += ctx->hidden.androidio.position;
                if (ctx->hidden.androidio.size != -1 /*UNKNOWN_LENGTH*/ && offset > ctx->hidden.androidio.size) offset = ctx->hidden.androidio.size;
                offset += ctx->hidden.androidio.offset;
                break;
            case RW_SEEK_END:
                offset = ctx->hidden.androidio.offset + ctx->hidden.androidio.size + offset;
                break;
            default:
                return SDL_SetError("Unknown value for 'whence'");
        }
        whence = SEEK_SET;

        off_t ret = lseek(ctx->hidden.androidio.fd, (off_t)offset, SEEK_SET);
        if (ret == -1) return -1;
        ctx->hidden.androidio.position = ret - ctx->hidden.androidio.offset;
    } else {
        Sint64 newPosition;

        switch (whence) {
            case RW_SEEK_SET:
                newPosition = offset;
                break;
            case RW_SEEK_CUR:
                newPosition = ctx->hidden.androidio.position + offset;
                break;
            case RW_SEEK_END:
                newPosition = ctx->hidden.androidio.size + offset;
                break;
            default:
                return SDL_SetError("Unknown value for 'whence'");
        }

        /* Validate the new position */
        if (newPosition < 0) {
            return SDL_Error(SDL_EFSEEK);
        }
        if (newPosition > ctx->hidden.androidio.size) {
            newPosition = ctx->hidden.androidio.size;
        }

        Sint64 movement = newPosition - ctx->hidden.androidio.position;
        if (movement > 0) {
            unsigned char buffer[4096];

            // The easy case where we're seeking forwards
            while (movement > 0) {
                Sint64 amount = sizeof (buffer);
                if (amount > movement) {
                    amount = movement;
                }
                size_t result = Android_JNI_FileRead(ctx, buffer, 1, amount);
                if (result <= 0) {
                    // Failed to read/skip the required amount, so fail
                    return -1;
                }

                movement -= result;
            }

        } else if (movement < 0) {
            // We can't seek backwards so we have to reopen the file and seek
            // forwards which obviously isn't very efficient
            Android_JNI_FileClose(ctx, false);
            Android_JNI_FileOpen(ctx);
            Android_JNI_FileSeek(ctx, newPosition, RW_SEEK_SET);
        }
    }

    return ctx->hidden.androidio.position;

}

extern "C" int Android_JNI_FileClose(SDL_RWops* ctx)
{
    return Android_JNI_FileClose(ctx, true);
}

// returns a new global reference which needs to be released later
static jobject Android_JNI_GetSystemServiceObject(const char* name)
{
    LocalReferenceHolder refs(__FUNCTION__);
    JNIEnv* env = Android_JNI_GetEnv();
    if (!refs.init(env)) {
        return NULL;
    }

    jstring service = env->NewStringUTF(name);

    jmethodID mid;

    mid = env->GetStaticMethodID(mActivityClass, "getContext", "()Landroid/content/Context;");
    jobject context = env->CallStaticObjectMethod(mActivityClass, mid);

    mid = env->GetMethodID(mActivityClass, "getSystemService", "(Ljava/lang/String;)Ljava/lang/Object;");
    jobject manager = env->CallObjectMethod(context, mid, service);

    env->DeleteLocalRef(service);

    return manager ? env->NewGlobalRef(manager) : NULL;
}

#define SETUP_CLIPBOARD(error) \
    LocalReferenceHolder refs(__FUNCTION__); \
    JNIEnv* env = Android_JNI_GetEnv(); \
    if (!refs.init(env)) { \
        return error; \
    } \
    jobject clipboard = Android_JNI_GetSystemServiceObject("clipboard"); \
    if (!clipboard) { \
        return error; \
    }

extern "C" int Android_JNI_SetClipboardText(const char* text)
{
    SETUP_CLIPBOARD(-1)

    jmethodID mid = env->GetMethodID(env->GetObjectClass(clipboard), "setText", "(Ljava/lang/CharSequence;)V");
    jstring string = env->NewStringUTF(text);
    env->CallVoidMethod(clipboard, mid, string);
    env->DeleteGlobalRef(clipboard);
    env->DeleteLocalRef(string);
    return 0;
}

extern "C" char* Android_JNI_GetClipboardText()
{
    SETUP_CLIPBOARD(SDL_strdup(""))

    jmethodID mid = env->GetMethodID(env->GetObjectClass(clipboard), "getText", "()Ljava/lang/CharSequence;");
    jobject sequence = env->CallObjectMethod(clipboard, mid);
    env->DeleteGlobalRef(clipboard);
    if (sequence) {
        mid = env->GetMethodID(env->GetObjectClass(sequence), "toString", "()Ljava/lang/String;");
        jstring string = reinterpret_cast<jstring>(env->CallObjectMethod(sequence, mid));
        const char* utf = env->GetStringUTFChars(string, 0);
        if (utf) {
            char* text = SDL_strdup(utf);
            env->ReleaseStringUTFChars(string, utf);
            return text;
        }
    }
    return SDL_strdup("");
}

extern "C" SDL_bool Android_JNI_HasClipboardText()
{
    SETUP_CLIPBOARD(SDL_FALSE)

    jmethodID mid = env->GetMethodID(env->GetObjectClass(clipboard), "hasText", "()Z");
    jboolean has = env->CallBooleanMethod(clipboard, mid);
    env->DeleteGlobalRef(clipboard);
    return has ? SDL_TRUE : SDL_FALSE;
}


// returns 0 on success or -1 on error (others undefined then)
// returns truthy or falsy value in plugged, charged and battery
// returns the value in seconds and percent or -1 if not available
extern "C" int Android_JNI_GetPowerInfo(int* plugged, int* charged, int* battery, int* seconds, int* percent)
{
    LocalReferenceHolder refs(__FUNCTION__);
    JNIEnv* env = Android_JNI_GetEnv();
    if (!refs.init(env)) {
        return -1;
    }

    jmethodID mid;

    mid = env->GetStaticMethodID(mActivityClass, "getContext", "()Landroid/content/Context;");
    jobject context = env->CallStaticObjectMethod(mActivityClass, mid);

    jstring action = env->NewStringUTF("android.intent.action.BATTERY_CHANGED");

    jclass cls = env->FindClass("android/content/IntentFilter");

    mid = env->GetMethodID(cls, "<init>", "(Ljava/lang/String;)V");
    jobject filter = env->NewObject(cls, mid, action);

    env->DeleteLocalRef(action);

    mid = env->GetMethodID(mActivityClass, "registerReceiver", "(Landroid/content/BroadcastReceiver;Landroid/content/IntentFilter;)Landroid/content/Intent;");
    jobject intent = env->CallObjectMethod(context, mid, NULL, filter);

    env->DeleteLocalRef(filter);

    cls = env->GetObjectClass(intent);

    jstring iname;
    jmethodID imid = env->GetMethodID(cls, "getIntExtra", "(Ljava/lang/String;I)I");

#define GET_INT_EXTRA(var, key) \
    iname = env->NewStringUTF(key); \
    int var = env->CallIntMethod(intent, imid, iname, -1); \
    env->DeleteLocalRef(iname);

    jstring bname;
    jmethodID bmid = env->GetMethodID(cls, "getBooleanExtra", "(Ljava/lang/String;Z)Z");

#define GET_BOOL_EXTRA(var, key) \
    bname = env->NewStringUTF(key); \
    int var = env->CallBooleanMethod(intent, bmid, bname, JNI_FALSE); \
    env->DeleteLocalRef(bname);

    if (plugged) {
        GET_INT_EXTRA(plug, "plugged") // == BatteryManager.EXTRA_PLUGGED (API 5)
        if (plug == -1) {
            return -1;
        }
        // 1 == BatteryManager.BATTERY_PLUGGED_AC
        // 2 == BatteryManager.BATTERY_PLUGGED_USB
        *plugged = (0 < plug) ? 1 : 0;
    }

    if (charged) {
        GET_INT_EXTRA(status, "status") // == BatteryManager.EXTRA_STATUS (API 5)
        if (status == -1) {
            return -1;
        }
        // 5 == BatteryManager.BATTERY_STATUS_FULL
        *charged = (status == 5) ? 1 : 0;
    }

    if (battery) {
        GET_BOOL_EXTRA(present, "present") // == BatteryManager.EXTRA_PRESENT (API 5)
        *battery = present ? 1 : 0;
    }

    if (seconds) {
        *seconds = -1; // not possible
    }

    if (percent) {
        GET_INT_EXTRA(level, "level") // == BatteryManager.EXTRA_LEVEL (API 5)
        GET_INT_EXTRA(scale, "scale") // == BatteryManager.EXTRA_SCALE (API 5)
        if ((level == -1) || (scale == -1)) {
            return -1;
        }
        *percent = level * 100 / scale;
    }

    env->DeleteLocalRef(intent);

    return 0;
}

// sends message to be handled on the UI event dispatch thread
extern "C" int Android_JNI_SendMessage(int command, int param)
{
    JNIEnv *env = Android_JNI_GetEnv();
    if (!env) {
        return -1;
    }
    jmethodID mid = env->GetStaticMethodID(mActivityClass, "sendMessage", "(II)Z");
    if (!mid) {
        return -1;
    }
    jboolean success = env->CallStaticBooleanMethod(mActivityClass, mid, command, param);
    return success ? 0 : -1;
}

extern "C" void Android_JNI_ShowTextInput(SDL_Rect *inputRect)
{
    JNIEnv *env = Android_JNI_GetEnv();
    if (!env) {
        return;
    }

    jmethodID mid = env->GetStaticMethodID(mActivityClass, "showTextInput", "(IIII)Z");
    if (!mid) {
        return;
    }
    env->CallStaticBooleanMethod( mActivityClass, mid,
                               inputRect->x,
                               inputRect->y,
                               inputRect->w,
                               inputRect->h );
}

extern "C" void Android_JNI_HideTextInput()
{
    // has to match Activity constant
    const int COMMAND_TEXTEDIT_HIDE = 3;
    Android_JNI_SendMessage(COMMAND_TEXTEDIT_HIDE, 0);
}

//////////////////////////////////////////////////////////////////////////////
//
// Functions exposed to SDL applications in SDL_system.h
//

extern "C" void *SDL_AndroidGetJNIEnv()
{
    return Android_JNI_GetEnv();
}



extern "C" void *SDL_AndroidGetActivity()
{
    /* See SDL_system.h for caveats on using this function. */

    jmethodID mid;

    JNIEnv *env = Android_JNI_GetEnv();
    if (!env) {
        return NULL;
    }

    // return SDLActivity.getContext();
    mid = env->GetStaticMethodID(mActivityClass,
            "getContext","()Landroid/content/Context;");
    return env->CallStaticObjectMethod(mActivityClass, mid);
}

extern "C" const char * SDL_AndroidGetInternalStoragePath()
{
    static char *s_AndroidInternalFilesPath = NULL;

    if (!s_AndroidInternalFilesPath) {
        LocalReferenceHolder refs(__FUNCTION__);
        jmethodID mid;
        jobject context;
        jobject fileObject;
        jstring pathString;
        const char *path;

        JNIEnv *env = Android_JNI_GetEnv();
        if (!refs.init(env)) {
            return NULL;
        }

        // context = SDLActivity.getContext();
        mid = env->GetStaticMethodID(mActivityClass,
                "getContext","()Landroid/content/Context;");
        context = env->CallStaticObjectMethod(mActivityClass, mid);

        // fileObj = context.getFilesDir();
        mid = env->GetMethodID(env->GetObjectClass(context),
                "getFilesDir", "()Ljava/io/File;");
        fileObject = env->CallObjectMethod(context, mid);
        if (!fileObject) {
            SDL_SetError("Couldn't get internal directory");
            return NULL;
        }

        // path = fileObject.getAbsolutePath();
        mid = env->GetMethodID(env->GetObjectClass(fileObject),
                "getAbsolutePath", "()Ljava/lang/String;");
        pathString = (jstring)env->CallObjectMethod(fileObject, mid);

        path = env->GetStringUTFChars(pathString, NULL);
        s_AndroidInternalFilesPath = SDL_strdup(path);
        env->ReleaseStringUTFChars(pathString, path);
    }
    return s_AndroidInternalFilesPath;
}

extern "C" int SDL_AndroidGetExternalStorageState()
{
    LocalReferenceHolder refs(__FUNCTION__);
    jmethodID mid;
    jclass cls;
    jstring stateString;
    const char *state;
    int stateFlags;

    JNIEnv *env = Android_JNI_GetEnv();
    if (!refs.init(env)) {
        return 0;
    }

    cls = env->FindClass("android/os/Environment");
    mid = env->GetStaticMethodID(cls,
            "getExternalStorageState", "()Ljava/lang/String;");
    stateString = (jstring)env->CallStaticObjectMethod(cls, mid);

    state = env->GetStringUTFChars(stateString, NULL);

    // Print an info message so people debugging know the storage state
    __android_log_print(ANDROID_LOG_INFO, "SDL", "external storage state: %s", state);

    if (SDL_strcmp(state, "mounted") == 0) {
        stateFlags = SDL_ANDROID_EXTERNAL_STORAGE_READ |
                     SDL_ANDROID_EXTERNAL_STORAGE_WRITE;
    } else if (SDL_strcmp(state, "mounted_ro") == 0) {
        stateFlags = SDL_ANDROID_EXTERNAL_STORAGE_READ;
    } else {
        stateFlags = 0;
    }
    env->ReleaseStringUTFChars(stateString, state);

    return stateFlags;
}

extern "C" const char * SDL_AndroidGetExternalStoragePath()
{
    static char *s_AndroidExternalFilesPath = NULL;

    if (!s_AndroidExternalFilesPath) {
        LocalReferenceHolder refs(__FUNCTION__);
        jmethodID mid;
        jobject context;
        jobject fileObject;
        jstring pathString;
        const char *path;

        JNIEnv *env = Android_JNI_GetEnv();
        if (!refs.init(env)) {
            return NULL;
        }

        // context = SDLActivity.getContext();
        mid = env->GetStaticMethodID(mActivityClass,
                "getContext","()Landroid/content/Context;");
        context = env->CallStaticObjectMethod(mActivityClass, mid);

        // fileObj = context.getExternalFilesDir();
        mid = env->GetMethodID(env->GetObjectClass(context),
                "getExternalFilesDir", "(Ljava/lang/String;)Ljava/io/File;");
        fileObject = env->CallObjectMethod(context, mid, NULL);
        if (!fileObject) {
            SDL_SetError("Couldn't get external directory");
            return NULL;
        }

        // path = fileObject.getAbsolutePath();
        mid = env->GetMethodID(env->GetObjectClass(fileObject),
                "getAbsolutePath", "()Ljava/lang/String;");
        pathString = (jstring)env->CallObjectMethod(fileObject, mid);

        path = env->GetStringUTFChars(pathString, NULL);
        s_AndroidExternalFilesPath = SDL_strdup(path);
        env->ReleaseStringUTFChars(pathString, path);
    }
    return s_AndroidExternalFilesPath;
}

#endif /* __ANDROID__ */

/* vi: set ts=4 sw=4 expandtab: */
