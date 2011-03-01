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
#include "Exception.h"
#include "Log.h"
#include "ProcessUtils.h"
#include "StringUtils.h"

#include "DebugNew.h"

#include <time.h>

Log* Log::sInstance = 0;

Log::Log(const std::string& fileName, LogLevel level) :
    mHandle(0),
    mLevel(level)
{
    if (sInstance)
        EXCEPTION("Log already exists");
    
    // If empty log file name, use a default name in the executable directory. Writing to it may fail depending on access rights.
    std::string useFileName = fileName.empty() ? getExecutableDirectory() + "Urho3D.log" : fileName;
    
    mHandle = fopen(useFileName.c_str(), "w");
    if (mHandle)
        write(LOG_INFO, "Log file " + useFileName + " created");
    else
        write(LOG_ERROR, "Failed to create log file " + useFileName);
    
    sInstance = this;
}

Log::~Log()
{
    if (mHandle)
    {
        write(LOG_INFO, "Log file closed");
        fclose(mHandle);
        mHandle = 0;
    }
    
    if (sInstance == this)
        sInstance = 0;
}

void Log::write(LogLevel level, const std::string& message)
{
    static const std::string levelPrefixes[] =
    {
        "DEBUG",
        "INFO",
        "WARNING",
        "ERROR"
    };
    
    if ((mLevel > level) || (level == LOG_NONE))
        return;
    
    mLastMessage = message;
    
    static time_t sysTime;
    time(&sysTime);
    const char* dateTime = ctime(&sysTime);
    std::string dateTimeString = replace(std::string(dateTime), "\n", "");
    std::string formattedMessage = "[" + dateTimeString + "] " + levelPrefixes[level] + ": " + message;
    
    printf("%s\n", formattedMessage.c_str());
    
    if (mHandle)
    {
        fprintf(mHandle, "%s\n", formattedMessage.c_str());
        fflush(mHandle);
    }
    
    using namespace LogMessage;
    
    VariantMap eventData;
    eventData[P_MESSAGE] = formattedMessage;
    sendEvent(EVENT_LOGMESSAGE, eventData);
}

void Log::writeRaw(const std::string& message)
{
    mLastMessage = message;
    
    printf("%s", message.c_str());
    
    if (mHandle)
    {
        fprintf(mHandle, "%s", message.c_str());
        fflush(mHandle);
    }
    
    using namespace LogMessage;
    
    VariantMap eventData;
    eventData[P_MESSAGE] = message;
    sendEvent(EVENT_LOGMESSAGE, eventData);
}

void writeToLog(LogLevel level, const std::string& message)
{
    Log* log = getLog();
    if (log)
        log->write(level, message);
}

void writeToLogRaw(const std::string& message)
{
    Log* log = getLog();
    if (log)
        log->writeRaw(message);
}
