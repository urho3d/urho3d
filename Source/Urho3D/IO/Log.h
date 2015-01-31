//
// Copyright (c) 2008-2015 the Urho3D project.
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

#pragma once

#include "../Container/List.h"
#include "../Core/Mutex.h"
#include "../Core/Object.h"
#include "../Core/StringUtils.h"

namespace Urho3D
{

/// Fictional message level to indicate a stored raw message.
static const int LOG_RAW = -1;
/// Debug message level. By default only shown in debug mode.
static const int LOG_DEBUG = 0;
/// Informative message level.
static const int LOG_INFO = 1;
/// Warning message level.
static const int LOG_WARNING = 2;
/// Error message level.
static const int LOG_ERROR = 3;
/// Disable all log messages.
static const int LOG_NONE = 4;

class File;

/// Stored log message from another thread.
struct StoredLogMessage
{
    /// Construct undefined.
    StoredLogMessage()
    {
    }
    
    /// Construct with parameters.
    StoredLogMessage(const String& message, int level, bool error) :
        message_(message),
        level_(level),
        error_(error)
    {
    }
    
    /// Message text.
    String message_;
    /// Message level. -1 for raw messages.
    int level_;
    /// Error flag for raw messages.
    bool error_;
};

/// Logging subsystem.
class URHO3D_API Log : public Object
{
    OBJECT(Log);

public:
    /// Construct.
    Log(Context* context);
    /// Destruct. Close the log file if open.
    virtual ~Log();

    /// Open the log file.
    void Open(const String& fileName);
    /// Close the log file.
    void Close();
    /// Set logging level.
    void SetLevel(int level);
    /// Set whether to timestamp log messages.
    void SetTimeStamp(bool enable);
    /// Set quiet mode ie. only print error entries to standard error stream (which is normally redirected to console also). Output to log file is not affected by this mode.
    void SetQuiet(bool quiet);

    /// Return logging level.
    int GetLevel() const { return level_; }
    /// Return whether log messages are timestamped.
    bool GetTimeStamp() const { return timeStamp_; }
    /// Return last log message.
    String GetLastMessage() const { return lastMessage_; }
    /// Return whether log is in quiet mode (only errors printed to standard error stream).
    bool IsQuiet() const { return quiet_; }

    /// Write to the log. If logging level is higher than the level of the message, the message is ignored.
    static void Write(int level, const String& message);
    /// Write raw output to the log.
    static void WriteRaw(const String& message, bool error = false);

private:
    /// Handle end of frame. Process the threaded log messages.
    void HandleEndFrame(StringHash eventType, VariantMap& eventData);
    
    /// Mutex for threaded operation.
    Mutex logMutex_;
    /// Log messages from other threads.
    List<StoredLogMessage> threadMessages_;
    /// Log file.
    SharedPtr<File> logFile_;
    /// Last log message.
    String lastMessage_;
    /// Logging level.
    int level_;
    /// Timestamp log messages flag.
    bool timeStamp_;
    /// In write flag to prevent recursion.
    bool inWrite_;
    /// Quiet mode flag.
    bool quiet_;
};

#ifdef URHO3D_LOGGING
#define LOGDEBUG(message) Urho3D::Log::Write(Urho3D::LOG_DEBUG, message)
#define LOGINFO(message) Urho3D::Log::Write(Urho3D::LOG_INFO, message)
#define LOGWARNING(message) Urho3D::Log::Write(Urho3D::LOG_WARNING, message)
#define LOGERROR(message) Urho3D::Log::Write(Urho3D::LOG_ERROR, message)
#define LOGRAW(message) Urho3D::Log::WriteRaw(message)
#define LOGDEBUGF(format, ...) Urho3D::Log::Write(Urho3D::LOG_DEBUG, Urho3D::ToString(format, ##__VA_ARGS__))
#define LOGINFOF(format, ...) Urho3D::Log::Write(Urho3D::LOG_INFO, Urho3D::ToString(format, ##__VA_ARGS__))
#define LOGWARNINGF(format, ...) Urho3D::Log::Write(Urho3D::LOG_WARNING, Urho3D::ToString(format, ##__VA_ARGS__))
#define LOGERRORF(format, ...) Urho3D::Log::Write(Urho3D::LOG_ERROR, Urho3D::ToString(format, ##__VA_ARGS__))
#define LOGRAWF(format, ...) Urho3D::Log::WriteRaw(Urho3D::ToString(format, ##__VA_ARGS__))
#else
#define LOGDEBUG(message)
#define LOGINFO(message)
#define LOGWARNING(message)
#define LOGERROR(message)
#define LOGRAW(message)
#define LOGDEBUGF(...)
#define LOGINFOF(...)
#define LOGWARNINGF(...)
#define LOGERRORF(...)
#define LOGRAWF(...)
#endif
}
