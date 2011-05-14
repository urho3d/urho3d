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

#pragma once

#include "Event.h"

/// (Server) Client has sent login
EVENT(E_CLIENTLOGIN, ClientLogin)
{
    PARAM(P_CONNECTION, Connection);      // Connection pointer
    PARAM(P_AUTHORIZE, Authorize);        // bool (set false to deny access)
    // Extra login data may exist if sent by the client
}

/// (Server) Client has joined a scene
EVENT(E_CLIENTJOINEDSCENE, ClientJoinedScene)
{
    PARAM(P_CONNECTION, Connection);      // Connection pointer
    PARAM(P_SCENE, Scene);                // Scene pointer
}

/// (Server) Client has left a scene
EVENT(E_CLIENTLEFTSCENE, ClientLeftScene)
{
    PARAM(P_CONNECTION, Connection);      // Connection pointer
    PARAM(P_SCENE, Scene);                // Scene pointer
}

/// (Server) Controls have been received from the client
EVENT(E_CLIENTCONTROLS, ClientControls)
{
    PARAM(P_CONNECTION, Connection);      // Connection pointer
    PARAM(P_FRAMENUMBER, FrameNumber);    // int (1-65535)
    PARAM(P_BUTTONS, Buttons);            // int
    PARAM(P_YAW, Yaw);                    // float (degrees)
    PARAM(P_PITCH, Pitch);                // float (degrees)
    // Other parameters may exist as part of the user extra controls variant map
}

/// (Server) Client has been disconnected
EVENT(E_CLIENTDISCONNECTED, ClientDisconnected)
{
    PARAM(P_CONNECTION, Connection);      // Connection pointer
}

/// (Client) Joined the scene
EVENT(E_JOINEDSCENE, JoinedScene)
{
}

/// (Client) Failed to join the scene
EVENT(E_JOINSCENEFAILED, JoinSceneFailed)
{
    PARAM(P_REASON, Reason);              // string
}

/// (Client) File transfer completed
EVENT(E_FILETRANSFERCOMPLETED, FileTransferCompleted)
{
    PARAM(P_FILENAME, FileName);          // string
    PARAM(P_FULLPATH, FullPath);          // string
}

/// (Client) File transfer failed
EVENT(E_FILETRANSFERFAILED, FileTransferFailed)
{
    PARAM(P_FILENAME, FileName);          // string
    PARAM(P_REASON, FileName);            // string
}

/// (Client) Controls update request, sent just before client update packet
EVENT(E_CONTROLSUPDATE, ControlsUpdate)
{
    PARAM(P_SCENE, Scene);                // Scene pointer
}

/// (Client) Server update received
EVENT(E_SERVERUPDATE, ServerUpdate)
{
    PARAM(P_SCENE, Scene);                // Scene pointer
}
