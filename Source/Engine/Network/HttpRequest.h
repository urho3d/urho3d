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

#pragma once

#include "Deserializer.h"
#include "RefCounted.h"

namespace Urho3D
{

/// HTTP request class.
class HttpRequest : public RefCounted, public Deserializer
{
public:
    /// Construct with parameters.
    HttpRequest(const String& url, const String& verb, const Vector<String>& headers, const String& postData);
    /// Destruct. Release the connection object.
    ~HttpRequest();

    /// Read response data from the HTTP connection. Return bytes actually read or 0 on error or end of data.
    virtual unsigned Read(void* dest, unsigned size);
    /// Set position from the beginning of the stream. Not supported.
    virtual unsigned Seek(unsigned position) { return position_; }
    
    /// Return whether connection is still open.
    bool IsOpen() const { return connection_ != 0; }
    /// Return URL used in the request.
    const String& GetURL() const { return url_; }
    /// Return verb used in the request. Default GET if empty verb specified on construction.
    const String& GetVerb() const { return verb_; }
    /// Return error, or empty string if the connection was made successfully.
    const String& GetError() const { return error_; }
    
private:
    /// Release the connection object.
    void Release();
    
    /// URL.
    String url_;
    /// Verb.
    String verb_;
    /// Error string. Empty if no error.
    String error_;
    /// Connection object.
    void* connection_;
};

}
