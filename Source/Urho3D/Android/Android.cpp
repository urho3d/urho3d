//
// Copyright (c) 2008-2019 the Urho3D project.
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//

#ifdef __ANDROID__
#include "../Precompiled.h"
#include "../Input/Input.h"
#include "../Resource/JSONFile.h"
#include "../IO/Log.h"
#include "Android.h"
#include "AndroidEvents.h"
#include <jni.h>
#include <SDL/SDL_events.h>


namespace Urho3D
{

extern "C" {
JNIEnv *Android_JNI_GetEnv(void);

/**
    * Function for correctly sending string messages from the main UI activity thread to the SDL game thread.
    Data is placed in the object and post to the SDL message queue.
    In input.cpp in HandleSDLEvent data unpacked and generate SendEvent in main SDL game thread.
*/

JNIEXPORT void Java_com_github_urho3d_UrhoActivity_nativeUserActivityCallback(JNIEnv* env, jclass cls, jstring json)
{
    const char *str = env->GetStringUTFChars(json, 0);
    String strData(str);
    if (str)
        env->ReleaseStringUTFChars(json, str);
    VariantMap* pArgs = new VariantMap;
    (*pArgs)[AndroidNotify::P_DATA] = strData;
    SDL_Event event;
    SDL_zero(event);
    event.type = sdlUserEventType;
    event.user.data2 = pArgs;
    event.user.code = E_ANDROID_NOTIFY.Value();
    SDL_PushEvent(&event);
}

}

void PostCommandToAndroid(const JSONFile& data)
{
    JNIEnv *mEnv = Android_JNI_GetEnv();
    if (!mEnv)
    {
        URHO3D_LOGERROR("No mEnv in PostCommandToAndroid");
        return;
    }
    jclass mainClass = mEnv->FindClass("com/github/urho3d/UrhoActivity");
    if (!mainClass)
    {
        URHO3D_LOGERROR("No mainClass in PostCommandToAndroid");
        return;
    }
    jmethodID midPostData = mEnv->GetStaticMethodID(mainClass, "postDataToUI", "(Ljava/lang/String;)V");
    if (!midPostData)
    {
        URHO3D_LOGERROR("No midPostData in PostCommandToAndroid");
        return;
    }
    jstring jparam = (jstring)mEnv->NewStringUTF(data.ToString(String()).CString());
    if (!jparam)
    {
        URHO3D_LOGERROR("No jparam in PostCommandToAndroid");
        return;
    }
    mEnv->CallStaticVoidMethod(mainClass, midPostData, jparam);
    mEnv->DeleteLocalRef(jparam);
}

}

#endif // __ANDROID__
