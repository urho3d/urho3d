// Copyright (c) 2008-2023 the Urho3D project
// License: MIT

/// \file

#pragma once

#include "../Container/ArrayPtr.h"
#include "../Core/Mutex.h"
#include "../Container/RefCounted.h"
#include "../Core/Thread.h"
#include "../IO/Deserializer.h"

namespace Urho3D
{

/// HTTP connection state.
enum HttpRequestState
{
    HTTP_INITIALIZING = 0,
    HTTP_ERROR,
    HTTP_OPEN,
    HTTP_CLOSED
};

/// An HTTP connection with response data stream.
class URHO3D_API HttpRequest : public RefCounted, public Deserializer, public Thread
{
public:
    /// Construct with parameters.
    HttpRequest(const String& url, const String& verb, const Vector<String>& headers, const String& postData);
    /// Destruct. Release the connection object.
    ~HttpRequest() override;

    /// Process the connection in the worker thread until closed.
    void ThreadFunction() override;

    /// Read response data from the HTTP connection and return number of bytes actually read. While the connection is open, will block while trying to read the specified size. To avoid blocking, only read up to as many bytes as GetAvailableSize() returns.
    i32 Read(void* dest, i32 size) override;
    /// Set position from the beginning of the stream. Not supported.
    i64 Seek(i64 position) override;
    /// Return whether all response data has been read.
    bool IsEof() const override;

    /// Return URL used in the request.
    /// @property{get_url}
    const String& GetURL() const { return url_; }

    /// Return verb used in the request. Default GET if empty verb specified on construction.
    /// @property
    const String& GetVerb() const { return verb_; }

    /// Return error. Only non-empty in the error state.
    /// @property
    String GetError() const;
    /// Return connection state.
    /// @property
    HttpRequestState GetState() const;
    /// Return amount of bytes in the read buffer.
    /// @property
    i32 GetAvailableSize() const;

    /// Return whether connection is in the open state.
    /// @property
    bool IsOpen() const { return GetState() == HTTP_OPEN; }

private:
    /// Check for available read data in buffer and whether end has been reached. Must only be called when the mutex is held by the main thread.
    Pair<i32, bool> CheckAvailableSizeAndEof() const;

    /// URL.
    String url_;
    /// Verb.
    String verb_;
    /// Error string. Empty if no error.
    String error_;
    /// Headers.
    Vector<String> headers_;
    /// POST data.
    String postData_;
    /// Connection state.
    HttpRequestState state_;
    /// Mutex for synchronizing the worker and the main thread.
    mutable Mutex mutex_;
    /// Read buffer for the worker thread.
    SharedArrayPtr<u8> httpReadBuffer_;
    /// Read buffer for the main thread.
    SharedArrayPtr<u8> readBuffer_;
    /// Read buffer read cursor.
    i32 readPosition_;
    /// Read buffer write cursor.
    i32 writePosition_;
};

}
