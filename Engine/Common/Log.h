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

#ifndef COMMON_LOG_H
#define COMMON_LOG_H

#include "RefCount.h"

#include <cstdio>
#include <string>

enum LogLevel
{
    LOG_DEBUG = 0,
    LOG_INFO,
    LOG_WARNING,
    LOG_ERROR,
    LOG_NONE
};

//! Urho3D log file
class Log : public RefCounted
{
public:
    //! Construct with a given filename and logging level
    Log(const std::string& fileName = std::string(), LogLevel level = LOG_INFO);
    //! Destruct. Close the log file
    virtual ~Log();
    
    //! Write to the log. If logging level is higher than the level of the message, the message is ignored
    void write(LogLevel level, const std::string& message);
    //! Write raw output to the log
    void writeRaw(const std::string& message);
    //! Set logging level
    void setLevel(LogLevel level);
    
    //! Return logging level
    LogLevel getLevel() const { return mLevel; }
    
private:
    //! Log file handle
    FILE* mHandle;
    //! Logging level
    LogLevel mLevel;
};

//! Return the Log instance
Log* getLog();
//! Write to the log
void writeToLog(LogLevel level, const std::string& message);
//! Write raw output to the log
void writeToLogRaw(const std::string& message);

#define LOGDEBUG(message) writeToLog(LOG_DEBUG, message)
#define LOGINFO(message) writeToLog(LOG_INFO, message)
#define LOGWARNING(message) writeToLog(LOG_WARNING, message)
#define LOGERROR(message) writeToLog(LOG_ERROR, message)
#define LOGRAW(message) writeToLogRaw(message)

#endif // COMMON_LOG_H
