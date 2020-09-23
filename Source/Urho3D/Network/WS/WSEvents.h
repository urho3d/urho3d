//
// Copyright (c) 2008-2020 the Urho3D project.
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

#include "../../Core/Object.h"

namespace Urho3D
{

/// New client connection established.
URHO3D_EVENT(E_WSCLIENTCONNECTED, WSClientConnected)
{
    URHO3D_PARAM(P_SOCKET, Socket); // libwebsocket pointer
}

/// Client disconnected
URHO3D_EVENT(E_WSCLIENTDISCONNECTED, WSClientDisconnected)
{
    URHO3D_PARAM(P_SOCKET, Socket); // libwebsocket pointer
}

/// Connected to WS server
URHO3D_EVENT(E_WSSERVERCONNECTED, WSServerConnected)
{
}

/// Disconnected frm WS server
URHO3D_EVENT(E_WSSERVERDISCONNECTED, WSServerDisconnected)
{
}

}
