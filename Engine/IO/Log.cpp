//
// Urho3D Engine
// Copyright (c) 2008-2012 Lasse Oorni
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

#include "Precompiled.h"
#include "Context.h"
#include "File.h"
#include "IOEvents.h"
#include "Log.h"
#include "ProcessUtils.h"
#include "Timer.h"

#include <cstdio>

#ifdef ANDROID
#include <android/log.h>
#endif
#ifdef IOS
extern "C" void SDL_IOS_LogMessage(const char* message);
#endif

#include "DebugNew.h"

namespace Urho3D
{

static const String levelPrefixes[] =
{
    "DEBUG",
    "INFO",
    "WARNING",
    "ERROR"
};

OBJECTTYPESTATIC(Log);

Log::Log(Context* context) :
    Object(context),
    #ifdef _DEBUG
    level_(LOG_DEBUG),
    #else
    level_(LOG_INFO),
    #endif
    timeStamp_(true),
    inWrite_(false)
{
}

Log::~Log()
{
}

void Log::Open(const String& fileName)
{
    #if !defined(ANDROID) && !defined(IOS)
    if (fileName.Empty())
        return;
    
    logFile_ = new File(context_);
    if (logFile_->Open(fileName, FILE_WRITE))
        Write(LOG_INFO, "Opened log file " + fileName);
    else
    {
        logFile_.Reset();
        Write(LOG_ERROR, "Failed to create log file " + fileName);
    }
    #endif
}

void Log::Write(int level, const String& message)
{
    assert(level >= LOG_DEBUG && level < LOG_NONE);
    
    // Prevent recursion
    if (inWrite_)
        return;
    
    // Check message level
    if (level_ > level)
        return;
    
    inWrite_ = true;
    lastMessage_ = message;
    String formattedMessage = levelPrefixes[level] + ": " + message;
    
    if (timeStamp_)
    {
        Time* time = GetSubsystem<Time>();
        if (time)
            formattedMessage = "[" + time->GetTimeStamp() + "] " + formattedMessage;
    }
    
    #if defined(ANDROID)
    int androidLevel = ANDROID_LOG_DEBUG + level;
    __android_log_print(androidLevel, "Urho3D", "%s", message.CString());
    #elif defined(IOS)
    SDL_IOS_LogMessage(message.CString());
    #else
    PrintUnicodeLine(formattedMessage);
    #endif
    
    if (logFile_)
    {
        logFile_->WriteLine(formattedMessage);
        logFile_->Flush();
    }
    
    using namespace LogMessage;
    
    VariantMap eventData;
    eventData[P_MESSAGE] = formattedMessage;
    SendEvent(E_LOGMESSAGE, eventData);
    
    inWrite_ = false;
}

void Log::WriteRaw(const String& message)
{
    // Prevent recursion
    if (inWrite_)
        return;
    
    inWrite_ = true;
    lastMessage_ = message;
    
    #if defined(ANDROID)
    __android_log_print(ANDROID_LOG_INFO, "Urho3D", message.CString());
    #elif defined(IOS)
    SDL_IOS_LogMessage(message.CString());
    #else
    PrintUnicode(message);
    #endif
    
    if (logFile_)
    {
        logFile_->Write(message.CString(), message.Length());
        logFile_->Flush();
    }
    
    using namespace LogMessage;
    
    VariantMap eventData;
    eventData[P_MESSAGE] = message;
    SendEvent(E_LOGMESSAGE, eventData);
    
    inWrite_ = false;
}

void Log::SetLevel(int level)
{
    assert(level >= LOG_DEBUG && level < LOG_NONE);

    level_ = level;
}

void Log::SetTimeStamp(bool enable)
{
    timeStamp_ = enable;
}

void WriteToLog(Context* context, int level, const String& message)
{
    Log* log = context->GetSubsystem<Log>();
    if (log)
        log->Write(level, message);
}

void WriteToLogRaw(Context* context, const String& message)
{
    Log* log = context->GetSubsystem<Log>();
    if (log)
        log->WriteRaw(message);
}

}
