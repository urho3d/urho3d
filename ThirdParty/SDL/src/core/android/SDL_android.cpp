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
#include "SDL_stdinc.h"
#include "SDL_assert.h"

#ifdef __ANDROID__

#include "SDL_android.h"

extern "C" {
#include "../../events/SDL_events_c.h"
#include "../../video/android/SDL_androidkeyboard.h"
#include "../../video/android/SDL_androidtouch.h"
#include "../../video/android/SDL_androidvideo.h"

#include <android/log.h>
#define LOG_TAG "SDL_android"
//#define LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)
//#define LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)
#define LOGI(...) do {} while (false)
#define LOGE(...) do {} while (false)


/* Implemented in audio/android/SDL_androidaudio.c */
extern void Android_RunAudioThread();
} // C

/*******************************************************************************
 This file links the Java side of Android with libsdl
*******************************************************************************/
#include <jni.h>
#include <android/log.h>


/*******************************************************************************
                               Globals
*******************************************************************************/
static JNIEnv* mEnv = NULL;
static JNIEnv* mAudioEnv = NULL;
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

    return JNI_VERSION_1_4;
}

// Called before SDL_main() to initialize JNI bindings
extern "C" void SDL_Android_Init(JNIEnv* env, jclass cls)
{
    __android_log_print(ANDROID_LOG_INFO, "SDL", "SDL_Android_Init()");

    mEnv = env;
    mActivityClass = (jclass)env->NewGlobalRef(cls);

    midCreateGLContext = mEnv->GetStaticMethodID(mActivityClass,
                                "createGLContext","(II)Z");
    midFlipBuffers = mEnv->GetStaticMethodID(mActivityClass,
                                "flipBuffers","()V");
    midAudioInit = mEnv->GetStaticMethodID(mActivityClass, 
                                "audioInit", "(IZZI)Ljava/lang/Object;");
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

// Quit
extern "C" void Java_org_libsdl_app_SDLActivity_nativeQuit(
                                    JNIEnv* env, jclass cls)
{    
    // Inject a SDL_QUIT event
    SDL_SendQuit();
}

// Pause
extern "C" void Java_org_libsdl_app_SDLActivity_nativePause(
                                    JNIEnv* env, jclass cls)
{
    if (Android_Window) {
        SDL_SendWindowEvent(Android_Window, SDL_WINDOWEVENT_FOCUS_LOST, 0, 0);
        SDL_SendWindowEvent(Android_Window, SDL_WINDOWEVENT_MINIMIZED, 0, 0);
    }
}

// Resume
extern "C" void Java_org_libsdl_app_SDLActivity_nativeResume(
                                    JNIEnv* env, jclass cls)
{
    if (Android_Window) {
        SDL_SendWindowEvent(Android_Window, SDL_WINDOWEVENT_FOCUS_GAINED, 0, 0);
        SDL_SendWindowEvent(Android_Window, SDL_WINDOWEVENT_RESTORED, 0, 0);
    }
}

extern "C" void Java_org_libsdl_app_SDLActivity_nativeRunAudioThread(
                                    JNIEnv* env, jclass cls)
{
    /* This is the audio thread, with a different environment */
    mAudioEnv = env;

    Android_RunAudioThread();
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
    LocalReferenceHolder() : m_env(NULL) { }
    ~LocalReferenceHolder() {
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
};
int LocalReferenceHolder::s_active;

extern "C" SDL_bool Android_JNI_CreateContext(int majorVersion, int minorVersion)
{
    if (mEnv->CallStaticBooleanMethod(mActivityClass, midCreateGLContext, majorVersion, minorVersion)) {
        return SDL_TRUE;
    } else {
        return SDL_FALSE;
    }
}

extern "C" void Android_JNI_SwapWindow()
{
    mEnv->CallStaticVoidMethod(mActivityClass, midFlipBuffers); 
}

extern "C" void Android_JNI_SetActivityTitle(const char *title)
{
    jmethodID mid;

    mid = mEnv->GetStaticMethodID(mActivityClass,"setActivityTitle","(Ljava/lang/String;)V");
    if (mid) {
        mEnv->CallStaticVoidMethod(mActivityClass, mid, mEnv->NewStringUTF(title));
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

    int status;
    JNIEnv *env;
    static bool isAttached = false;    
    status = mJavaVM->GetEnv((void **) &env, JNI_VERSION_1_4);
    if(status < 0) {
        LOGE("callback_handler: failed to get JNI environment, assuming native thread");
        status = mJavaVM->AttachCurrentThread(&env, NULL);
        if(status < 0) {
            LOGE("callback_handler: failed to attach current thread");
            return 0;
        }
        isAttached = true;
    }

    
    __android_log_print(ANDROID_LOG_VERBOSE, "SDL", "SDL audio: opening device");
    audioBuffer16Bit = is16Bit;
    audioBufferStereo = channelCount > 1;

    audioBuffer = env->CallStaticObjectMethod(mActivityClass, midAudioInit, sampleRate, audioBuffer16Bit, audioBufferStereo, desiredBufferFrames);

    if (audioBuffer == NULL) {
        __android_log_print(ANDROID_LOG_WARN, "SDL", "SDL audio: didn't get back a good audio buffer!");
        return 0;
    }
    audioBuffer = env->NewGlobalRef(audioBuffer);

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
 
    if (isAttached) {
        mJavaVM->DetachCurrentThread();
    }

    return audioBufferFrames;
}

extern "C" void * Android_JNI_GetAudioBuffer()
{
    return audioBufferPinned;
}

extern "C" void Android_JNI_WriteAudioBuffer()
{
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
    int status;
    JNIEnv *env;
    static bool isAttached = false;    
    status = mJavaVM->GetEnv((void **) &env, JNI_VERSION_1_4);
    if(status < 0) {
        LOGE("callback_handler: failed to get JNI environment, assuming native thread");
        status = mJavaVM->AttachCurrentThread(&env, NULL);
        if(status < 0) {
            LOGE("callback_handler: failed to attach current thread");
            return;
        }
        isAttached = true;
    }

    env->CallStaticVoidMethod(mActivityClass, midAudioQuit); 

    if (audioBuffer) {
        env->DeleteGlobalRef(audioBuffer);
        audioBuffer = NULL;
        audioBufferPinned = NULL;
    }

    if (isAttached) {
        mJavaVM->DetachCurrentThread();
    }
}

// Test for an exception and call SDL_SetError with its detail if one occurs
static bool Android_JNI_ExceptionOccurred()
{
    SDL_assert(LocalReferenceHolder::IsActive());

    jthrowable exception = mEnv->ExceptionOccurred();
    if (exception != NULL) {
        jmethodID mid;

        // Until this happens most JNI operations have undefined behaviour
        mEnv->ExceptionClear();

        jclass exceptionClass = mEnv->GetObjectClass(exception);
        jclass classClass = mEnv->FindClass("java/lang/Class");

        mid = mEnv->GetMethodID(classClass, "getName", "()Ljava/lang/String;");
        jstring exceptionName = (jstring)mEnv->CallObjectMethod(exceptionClass, mid);
        const char* exceptionNameUTF8 = mEnv->GetStringUTFChars(exceptionName, 0);

        mid = mEnv->GetMethodID(exceptionClass, "getMessage", "()Ljava/lang/String;");
        jstring exceptionMessage = (jstring)mEnv->CallObjectMethod(exception, mid);

        if (exceptionMessage != NULL) {
            const char* exceptionMessageUTF8 = mEnv->GetStringUTFChars(
                    exceptionMessage, 0);
            SDL_SetError("%s: %s", exceptionNameUTF8, exceptionMessageUTF8);
            mEnv->ReleaseStringUTFChars(exceptionMessage, exceptionMessageUTF8);
        } else {
            SDL_SetError("%s", exceptionNameUTF8);
        }

        mEnv->ReleaseStringUTFChars(exceptionName, exceptionNameUTF8);

        return true;
    }

    return false;
}

static int Android_JNI_FileOpen(SDL_RWops* ctx)
{
    LocalReferenceHolder refs;
    int result = 0;

    jmethodID mid;
    jobject context;
    jobject assetManager;
    jobject inputStream;
    jclass channels;
    jobject readableByteChannel;
    jstring fileNameJString;

    if (!refs.init(mEnv)) {
        goto failure;
    }

    fileNameJString = (jstring)ctx->hidden.androidio.fileName;

    // context = SDLActivity.getContext();
    mid = mEnv->GetStaticMethodID(mActivityClass,
            "getContext","()Landroid/content/Context;");
    context = mEnv->CallStaticObjectMethod(mActivityClass, mid);

    // assetManager = context.getAssets();
    mid = mEnv->GetMethodID(mEnv->GetObjectClass(context),
            "getAssets", "()Landroid/content/res/AssetManager;");
    assetManager = mEnv->CallObjectMethod(context, mid);

    // inputStream = assetManager.open(<filename>);
    mid = mEnv->GetMethodID(mEnv->GetObjectClass(assetManager),
            "open", "(Ljava/lang/String;)Ljava/io/InputStream;");
    inputStream = mEnv->CallObjectMethod(assetManager, mid, fileNameJString);
    if (Android_JNI_ExceptionOccurred()) {
        goto failure;
    }

    ctx->hidden.androidio.inputStream = inputStream;
    ctx->hidden.androidio.inputStreamRef = mEnv->NewGlobalRef(inputStream);

    // Despite all the visible documentation on [Asset]InputStream claiming
    // that the .available() method is not guaranteed to return the entire file
    // size, comments in <sdk>/samples/<ver>/ApiDemos/src/com/example/ ...
    // android/apis/content/ReadAsset.java imply that Android's
    // AssetInputStream.available() /will/ always return the total file size

    // size = inputStream.available();
    mid = mEnv->GetMethodID(mEnv->GetObjectClass(inputStream),
            "available", "()I");
    ctx->hidden.androidio.size = mEnv->CallIntMethod(inputStream, mid);
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

    ctx->hidden.androidio.readableByteChannel = readableByteChannel;
    ctx->hidden.androidio.readableByteChannelRef =
        mEnv->NewGlobalRef(readableByteChannel);

    // Store .read id for reading purposes
    mid = mEnv->GetMethodID(mEnv->GetObjectClass(readableByteChannel),
            "read", "(Ljava/nio/ByteBuffer;)I");
    ctx->hidden.androidio.readMethod = mid;

    ctx->hidden.androidio.position = 0;

    if (false) {
failure:
        result = -1;

        mEnv->DeleteGlobalRef((jobject)ctx->hidden.androidio.fileNameRef);

        if(ctx->hidden.androidio.inputStreamRef != NULL) {
            mEnv->DeleteGlobalRef((jobject)ctx->hidden.androidio.inputStreamRef);
        }
    }

    return result;
}

extern "C" int Android_JNI_FileOpen(SDL_RWops* ctx,
        const char* fileName, const char*)
{
    LocalReferenceHolder refs;

    if (!refs.init(mEnv)) {
        return -1;
    }

    if (!ctx) {
        return -1;
    }

    jstring fileNameJString = mEnv->NewStringUTF(fileName);
    ctx->hidden.androidio.fileName = fileNameJString;
    ctx->hidden.androidio.fileNameRef = mEnv->NewGlobalRef(fileNameJString);
    ctx->hidden.androidio.inputStreamRef = NULL;

    return Android_JNI_FileOpen(ctx);
}

extern "C" size_t Android_JNI_FileRead(SDL_RWops* ctx, void* buffer,
        size_t size, size_t maxnum)
{
    LocalReferenceHolder refs;
    int bytesRemaining = size * maxnum;
    int bytesRead = 0;

    if (!refs.init(mEnv)) {
        return -1;
    }

    jobject readableByteChannel = (jobject)ctx->hidden.androidio.readableByteChannel;
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

extern "C" size_t Android_JNI_FileWrite(SDL_RWops* ctx, const void* buffer,
        size_t size, size_t num)
{
    SDL_SetError("Cannot write to Android package filesystem");
    return 0;
}

static int Android_JNI_FileClose(SDL_RWops* ctx, bool release)
{
    LocalReferenceHolder refs;
    int result = 0;

    if (!refs.init(mEnv)) {
        SDL_SetError("Failed to allocate enough JVM local references");
        return -1;
    }

    if (ctx) {
        if (release) {
            mEnv->DeleteGlobalRef((jobject)ctx->hidden.androidio.fileNameRef);
        }

        jobject inputStream = (jobject)ctx->hidden.androidio.inputStream;

        // inputStream.close();
        jmethodID mid = mEnv->GetMethodID(mEnv->GetObjectClass(inputStream),
                "close", "()V");
        mEnv->CallVoidMethod(inputStream, mid);
        mEnv->DeleteGlobalRef((jobject)ctx->hidden.androidio.inputStreamRef);
        mEnv->DeleteGlobalRef((jobject)ctx->hidden.androidio.readableByteChannelRef);
        if (Android_JNI_ExceptionOccurred()) {
            result = -1;
        }

        if (release) {
            SDL_FreeRW(ctx);
        }
    }

    return result;
}


extern "C" long Android_JNI_FileSeek(SDL_RWops* ctx, long offset, int whence)
{
    long newPosition;

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
            SDL_SetError("Unknown value for 'whence'");
            return -1;
    }
    if (newPosition < 0) {
        newPosition = 0;
    }
    if (newPosition > ctx->hidden.androidio.size) {
        newPosition = ctx->hidden.androidio.size;
    }

    long movement = newPosition - ctx->hidden.androidio.position;
    jobject inputStream = (jobject)ctx->hidden.androidio.inputStream;

    if (movement > 0) {
        unsigned char buffer[1024];

        // The easy case where we're seeking forwards
        while (movement > 0) {
            long amount = (long) sizeof (buffer);
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

    ctx->hidden.androidio.position = newPosition;

    return ctx->hidden.androidio.position;
}

extern "C" int Android_JNI_FileClose(SDL_RWops* ctx)
{
    return Android_JNI_FileClose(ctx, true);
}

#endif /* __ANDROID__ */

/* vi: set ts=4 sw=4 expandtab: */
