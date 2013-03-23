//
// Copyright (c) 2008-2013 the Urho3D project.
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
#include "Mutex.h"
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

OBJECTTYPESTATIC(Log);

SharedPtr<File> Log::logFile_;
String Log::lastMessage_;
#ifdef _DEBUG
int Log::level_ = LOG_DEBUG;
#else
int Log::level_ = LOG_INFO;
#endif
bool Log::timeStamp_ = true;
bool Log::inWrite_ = false;
bool Log::quiet_ = false;

static PODVector<Log*> logInstances;

Log::Log(Context* context) :
    Object(context)
{
    MutexLock lock(GetStaticMutex());
    logInstances.Push(this);
}

Log::~Log()
{
    MutexLock lock(GetStaticMutex());
    
    logInstances.Remove(this);
    
    // Close log file if was last instance
    if (logInstances.Empty())
        logFile_.Reset();
}

void Log::Open(const String& fileName)
{
    #if !defined(ANDROID) && !defined(IOS)
    MutexLock lock(GetStaticMutex());
    
    // Only the first log instance actually opens the file, the rest are routed to it
    if ((logFile_ && logFile_->IsOpen()) || fileName.Empty())
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

void Log::SetLevel(int level)
{
    assert(level >= LOG_DEBUG && level < LOG_NONE);
    
    level_ = level;
}

void Log::SetTimeStamp(bool enable)
{
    timeStamp_ = enable;
}

void Log::SetQuiet(bool quiet)
{
    quiet_ = quiet;
}

String Log::GetLastMessage() const
{
    MutexLock lock(GetStaticMutex());
    return lastMessage_;
}

void Log::Write(int level, const String& message)
{
    assert(level >= LOG_DEBUG && level < LOG_NONE);
    
    // Do not log if message level excluded or if currently sending a log event
    if (level_ > level || inWrite_)
        return;
    
    {
        MutexLock lock(GetStaticMutex());
        
        String formattedMessage = levelPrefixes[level] + ": " + message;
        lastMessage_ = message;
        
        if (timeStamp_)
            formattedMessage = "[" + Time::GetTimeStamp() + "] " + formattedMessage;
        
        #if defined(ANDROID)
        int androidLevel = ANDROID_LOG_DEBUG + level;
        __android_log_print(androidLevel, "Urho3D", "%s", message.CString());
        #elif defined(IOS)
        SDL_IOS_LogMessage(message.CString());
        #else
        if (quiet_)
        {
            // If in quiet mode, still print the error message to the standard error stream
            if (level == LOG_ERROR)
                PrintUnicodeLine(formattedMessage, true);
        }
        else
            PrintUnicodeLine(formattedMessage, level == LOG_ERROR);
        #endif
        
        if (logFile_)
        {
            logFile_->WriteLine(formattedMessage);
            logFile_->Flush();
        }
        
        // Log messages can be safely sent as an event only in single-instance mode
        if (logInstances.Size() == 1)
        {
            inWrite_ = true;
            
            using namespace LogMessage;
            
            VariantMap eventData;
            eventData[P_MESSAGE] = formattedMessage;
            logInstances[0]->SendEvent(E_LOGMESSAGE, eventData);
            
            inWrite_ = false;
        }
    }
}

void Log::WriteRaw(const String& message, bool error)
{
    // Prevent recursion during log event
    if (inWrite_)
        return;
    
    {
        MutexLock lock(GetStaticMutex());
        
        lastMessage_ = message;
        
        #if defined(ANDROID)
        __android_log_print(ANDROID_LOG_INFO, "Urho3D", message.CString());
        #elif defined(IOS)
        SDL_IOS_LogMessage(message.CString());
        #else
        if (quiet_)
        {
            // If in quiet mode, still print the error message to the standard error stream
            if (error)
            	PrintUnicode(message, true);
        }
        else
        	PrintUnicode(message, error);
        #endif
        
        if (logFile_)
        {
            logFile_->Write(message.CString(), message.Length());
            logFile_->Flush();
        }
        
        // Log messages can be safely sent as an event only in single-instance mode
        if (logInstances.Size() == 1)
        {
            inWrite_ = true;
            
            using namespace LogMessage;
            
            VariantMap eventData;
            eventData[P_MESSAGE] = message;
            logInstances[0]->SendEvent(E_LOGMESSAGE, eventData);
            
            inWrite_ = false;
        }
    }
}

}
