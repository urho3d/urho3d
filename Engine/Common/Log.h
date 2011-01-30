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
#include <vector>

//! Logging levels
enum LogLevel
{
    LOG_DEBUG = 0,
    LOG_INFO,
    LOG_WARNING,
    LOG_ERROR,
    LOG_NONE
};

//! Log message listener
class LogListener
{
public:
    //! Write a log message
    virtual void write(const std::string& message) = 0;
};

//! Urho3D log file
class Log : public RefCounted
{
    friend Log* getLog();
    
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
    //! Add a log listener
    void addListener(LogListener* listener);
    //! Remove a log listener
    void removeListener(LogListener* listener);
    
    //! Return logging level
    LogLevel getLevel() const { return mLevel; }
    //! Return last log message
    const std::string& getLastMessage() const { return mLastMessage; }
    
private:
    //! Log file handle
    FILE* mHandle;
    //! Logging level
    LogLevel mLevel;
    //! Last log message
    std::string mLastMessage;
    //! Log listeners
    std::vector<LogListener*> mListeners;
    
    //! Log instance
    static Log* sInstance;
};

//! Return the Log instance
inline Log* getLog()
{
    return Log::sInstance;
}

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
