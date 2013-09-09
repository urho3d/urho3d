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
#include "HttpRequest.h"
#include "Log.h"
#include "StringUtils.h"

#include <civetweb.h>

#include "DebugNew.h"

namespace Urho3D
{

static const unsigned ERROR_BUFFER_LEN = 256;

HttpRequest::HttpRequest(const String& url, const String& verb, const Vector<String>& headers, const String& postData) :
    url_(url),
    verb_(!verb.Empty() ? verb : "GET"),
    connection_(0)
{
    String protocol = "http";
    String host;
    String path = "/";
    int port = 80;
    
    unsigned protocolEnd = url.Find("://");
    if (protocolEnd != String::NPOS)
    {
        protocol = url.Substring(0, protocolEnd);
        host = url.Substring(protocolEnd + 3);
    }
    else
        host = url;
    
    unsigned pathStart = host.Find('/');
    if (pathStart != String::NPOS)
    {
        path = host.Substring(pathStart);
        host = host.Substring(0, pathStart);
    }
    
    unsigned portStart = host.Find(':');
    if (portStart != String::NPOS)
    {
        port = ToInt(host.Substring(portStart + 1));
        host = host.Substring(0, portStart);
    }
    
    LOGDEBUG("HTTP " + verb_ + " request to host " + host + " port " + String(port) + " path " + String(path));
    
    char errorBuffer[ERROR_BUFFER_LEN];
    memset(errorBuffer, 0, sizeof(errorBuffer));
    
    String headerStr;
    for (unsigned i = 0; i < headers.Size(); ++i)
        headerStr += headers[i] + "\r\n";
    
    /// \todo SSL mode will not actually work unless Civetweb's SSL mode is initialized with an external SSL DLL
    if (postData.Empty())
    {
        connection_ = mg_download(host.CString(), port, protocol.Compare("https", false) ? 0 : 1, errorBuffer, sizeof(errorBuffer),
            "%s %s HTTP/1.0\r\n"
            "Host: %s\r\n"
            "%s"
            "\r\n", verb_.CString(), path.CString(), host.CString(), headerStr.CString());
    }
    else
    {
        connection_ = mg_download(host.CString(), port, protocol.Compare("https", false) ? 0 : 1, errorBuffer, sizeof(errorBuffer),
            "%s %s HTTP/1.0\r\n"
            "Host: %s\r\n"
            "%s"
            "Content-Length: %d\r\n"
            "\r\n"
            "%s", verb_.CString(), path.CString(), host.CString(), headerStr.CString(), postData.Length(), postData.CString());
    }
    
    if (!connection_)
        error_ = String(&errorBuffer[0]);
}

HttpRequest::~HttpRequest()
{
    Release();
}

unsigned HttpRequest::Read(void* dest, unsigned size)
{
    if (!connection_)
        return 0;
    
    int bytesRead = mg_read((mg_connection*)connection_, dest, size);
    // Automatically close the connection if no more data
    if (bytesRead <= 0)
        Release();
    
    return bytesRead > 0 ? bytesRead : 0;
}

void HttpRequest::Release()
{
    if (connection_)
    {
        mg_close_connection((mg_connection*)connection_);
        connection_ = 0;
    }
}

}

