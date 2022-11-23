// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

#include "../Precompiled.h"

#include "../Core/Profiler.h"
#include "../IO/Log.h"
#include "../Network/HttpRequest.h"

#include <Civetweb/civetweb.h>

#include "../DebugNew.h"

namespace Urho3D
{

static constexpr i32 ERROR_BUFFER_SIZE = 256;
static constexpr i32 READ_BUFFER_SIZE = 65536; // Must be a power of two

HttpRequest::HttpRequest(const String& url, const String& verb, const Vector<String>& headers, const String& postData) :
    url_(url.Trimmed()),
    verb_(!verb.Empty() ? verb : "GET"),
    headers_(headers),
    postData_(postData),
    state_(HTTP_INITIALIZING),
    httpReadBuffer_(new u8[READ_BUFFER_SIZE]),
    readBuffer_(new u8[READ_BUFFER_SIZE]),
    readPosition_(0),
    writePosition_(0)
{
    // Size of response is unknown, so just set maximum value. The position will also be changed
    // to maximum value once the request is done, signaling end for Deserializer::IsEof().
    size_ = M_MAX_UNSIGNED;

    URHO3D_LOGDEBUG("HTTP " + verb_ + " request to URL " + url_);

#ifdef URHO3D_SSL
    static bool sslInitialized = false;
    if (!sslInitialized)
    {
        mg_init_library(MG_FEATURES_TLS);
        sslInitialized = true;
    }
#endif

#ifdef URHO3D_THREADING
    // Start the worker thread to actually create the connection and read the response data.
    Run();
#else
    URHO3D_LOGERROR("HTTP request will not execute as threading is disabled");
#endif
}

HttpRequest::~HttpRequest()
{
    Stop();
}

void HttpRequest::ThreadFunction()
{
    URHO3D_PROFILE_THREAD("HttpRequest Thread");

    String protocol = "http";
    String host;
    String path = "/";
    int port = 80;

    i32 protocolEnd = url_.Find("://");
    if (protocolEnd != String::NPOS)
    {
        protocol = url_.Substring(0, protocolEnd);
        host = url_.Substring(protocolEnd + 3);
    }
    else
        host = url_;

    i32 pathStart = host.Find('/');
    if (pathStart != String::NPOS)
    {
        path = host.Substring(pathStart);
        host = host.Substring(0, pathStart);
    }

    i32 portStart = host.Find(':');
    if (portStart != String::NPOS)
    {
        port = ToI32(host.Substring(portStart + 1));
        host = host.Substring(0, portStart);
    } else if (protocol.Compare("https", false) >= 0)
        port = 443;

    char errorBuffer[ERROR_BUFFER_SIZE];
    memset(errorBuffer, 0, sizeof(errorBuffer));

    String headersStr;
    for (i32 i = 0; i < headers_.Size(); ++i)
    {
        // Trim and only add non-empty header strings
        String header = headers_[i].Trimmed();
        if (header.Length())
            headersStr += header + "\r\n";
    }

    // Initiate the connection. This may block due to DNS query
    mg_connection* connection = nullptr;

    if (postData_.Empty())
    {
        connection = mg_download(host.CString(), port, protocol.Compare("https", false) >= 0 ? 1 : 0, errorBuffer, sizeof(errorBuffer),
            "%s %s HTTP/1.0\r\n"
            "Host: %s\r\n"
            "%s"
            "\r\n", verb_.CString(), path.CString(), host.CString(), headersStr.CString());
    }
    else
    {
        connection = mg_download(host.CString(), port, protocol.Compare("https", false) >= 0 ? 1 : 0, errorBuffer, sizeof(errorBuffer),
            "%s %s HTTP/1.0\r\n"
            "Host: %s\r\n"
            "%s"
            "Content-Length: %d\r\n"
            "\r\n"
            "%s", verb_.CString(), path.CString(), host.CString(), headersStr.CString(), postData_.Length(), postData_.CString());
    }

    {
        MutexLock lock(mutex_);
        state_ = connection ? HTTP_OPEN : HTTP_ERROR;

        // If no connection could be made, store the error and exit
        if (state_ == HTTP_ERROR)
        {
            error_ = String(&errorBuffer[0]);
            return;
        }
    }

    // Loop while should run, read data from the connection, copy to the main thread buffer if there is space
    while (shouldRun_)
    {
        // Read less than full buffer to be able to distinguish between full and empty ring buffer. Reading may block
        i32 bytesRead = mg_read(connection, httpReadBuffer_.Get(), READ_BUFFER_SIZE / 4);
        if (bytesRead <= 0)
            break;

        mutex_.Acquire();

        // Wait until enough space in the main thread's ring buffer
        for (;;)
        {
            i32 spaceInBuffer = READ_BUFFER_SIZE - ((writePosition_ - readPosition_) & (READ_BUFFER_SIZE - 1));
            if (spaceInBuffer > bytesRead || !shouldRun_)
                break;

            mutex_.Release();
            Time::Sleep(5);
            mutex_.Acquire();
        }

        if (!shouldRun_)
        {
            mutex_.Release();
            break;
        }

        if (writePosition_ + bytesRead <= READ_BUFFER_SIZE)
            memcpy(readBuffer_.Get() + writePosition_, httpReadBuffer_.Get(), (size_t)bytesRead);
        else
        {
            // Handle ring buffer wrap
            i32 part1 = READ_BUFFER_SIZE - writePosition_;
            i32 part2 = bytesRead - part1;
            memcpy(readBuffer_.Get() + writePosition_, httpReadBuffer_.Get(), part1);
            memcpy(readBuffer_.Get(), httpReadBuffer_.Get() + part1, part2);
        }

        writePosition_ += bytesRead;
        writePosition_ &= READ_BUFFER_SIZE - 1;

        mutex_.Release();
    }

    // Close the connection
    mg_close_connection(connection);

    {
        MutexLock lock(mutex_);
        state_ = HTTP_CLOSED;
    }
}

i32 HttpRequest::Read(void* dest, i32 size)
{
    assert(size >= 0);

#ifdef URHO3D_THREADING
    mutex_.Acquire();

    u8* destPtr = (u8*)dest;
    i32 sizeLeft = size;
    i32 totalRead = 0;

    for (;;)
    {
        Pair<i32, bool> status{};

        for (;;)
        {
            status = CheckAvailableSizeAndEof();
            if (status.first_ || status.second_)
                break;
            // While no bytes and connection is still open, block until has some data
            mutex_.Release();
            Time::Sleep(5);
            mutex_.Acquire();
        }

        i32 bytesAvailable = status.first_;

        if (bytesAvailable)
        {
            if (bytesAvailable > sizeLeft)
                bytesAvailable = sizeLeft;

            if (readPosition_ + bytesAvailable <= READ_BUFFER_SIZE)
                memcpy(destPtr, readBuffer_.Get() + readPosition_, bytesAvailable);
            else
            {
                // Handle ring buffer wrap
                i32 part1 = READ_BUFFER_SIZE - readPosition_;
                i32 part2 = bytesAvailable - part1;
                memcpy(destPtr, readBuffer_.Get() + readPosition_, part1);
                memcpy(destPtr + part1, readBuffer_.Get(), part2);
            }

            readPosition_ += bytesAvailable;
            readPosition_ &= READ_BUFFER_SIZE - 1;
            sizeLeft -= bytesAvailable;
            totalRead += bytesAvailable;
            destPtr += bytesAvailable;
        }

        if (!sizeLeft || !bytesAvailable)
            break;
    }

    mutex_.Release();
    return totalRead;
#else
    // Threading disabled, nothing to read
    return 0;
#endif
}

i64 HttpRequest::Seek(i64 position)
{
    return 0;
}

bool HttpRequest::IsEof() const
{
    MutexLock lock(mutex_);
    return CheckAvailableSizeAndEof().second_;
}

String HttpRequest::GetError() const
{
    MutexLock lock(mutex_);
    return error_;
}

HttpRequestState HttpRequest::GetState() const
{
    MutexLock lock(mutex_);
    return state_;
}

i32 HttpRequest::GetAvailableSize() const
{
    MutexLock lock(mutex_);
    return CheckAvailableSizeAndEof().first_;
}

Pair<i32, bool> HttpRequest::CheckAvailableSizeAndEof() const
{
    i32 size = (writePosition_ - readPosition_) & (READ_BUFFER_SIZE - 1);
    return {size, (state_ == HTTP_ERROR || (state_ == HTTP_CLOSED && !size))};
}

}
