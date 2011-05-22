//
// Urho3D Engine
// Copyright (c) 2008-2011 Lasse Öörni
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

#include <cstdio>
#include <ctime>

#include "DebugNew.h"

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
    inWrite_(false)
{
}

Log::~Log()
{
}

void Log::Open(const String& fileName)
{
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
}

void Log::Write(int level, const String& message)
{
    // Prevent recursion
    if (inWrite_)
        return;
    
    // Check message level
    if ((level_ > level) || (level < LOG_DEBUG) || (level >= LOG_NONE))
        return;
    
    inWrite_ = true;
    
    lastMessage_ = message;
    
    time_t sysTime;
    time(&sysTime);
    const char* dateTime = ctime(&sysTime);
    String dateTimeString = String(dateTime);
    dateTimeString.Replace("\n", "");
    String formattedMessage = "[" + dateTimeString + "] " + levelPrefixes[level] + ": " + message;
    
    printf("%s\n", formattedMessage.CString());
    
    if (logFile_)
        logFile_->WriteLine(formattedMessage);
    
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
    
    printf("%s", message.CString());
    
    if (logFile_)
        logFile_->Write(message.CString(), message.Length());
    
    using namespace LogMessage;
    
    VariantMap eventData;
    eventData[P_MESSAGE] = message;
    SendEvent(E_LOGMESSAGE, eventData);
    
    inWrite_ = false;
}

void Log::SetLevel(int level)
{
    level_ = level;
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
