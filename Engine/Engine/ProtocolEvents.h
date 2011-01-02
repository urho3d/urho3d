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

#ifndef ENGINE_PROTOCOLEVENTS_H
#define ENGINE_PROTOCOLEVENTS_H

#include "Event.h"

//! (Server) Client has sent identification
DEFINE_EVENT(EVENT_CLIENTIDENTITY, ClientIdentity)
{
    EVENT_PARAM(P_CONNECTION, Connection);      // Connection pointer
    EVENT_PARAM(P_PACKET, Packet);              // Buffer
    EVENT_PARAM(P_AUTHORIZE, Authorize);        // bool
}

//! (Server) Client has joined a scene
DEFINE_EVENT(EVENT_CLIENTJOINEDSCENE, ClientJoinedScene)
{
    EVENT_PARAM(P_CONNECTION, Connection);      // Connection pointer
    EVENT_PARAM(P_SCENE, Scene);                // Scene pointer
}

//! (Server) Client has left a scene
DEFINE_EVENT(EVENT_CLIENTLEFTSCENE, ClientLeftScene)
{
    EVENT_PARAM(P_CONNECTION, Connection);      // Connection pointer
    EVENT_PARAM(P_SCENE, Scene);                // Scene pointer
}

//! (Server) Controls have been received from the client
DEFINE_EVENT(EVENT_CLIENTCONTROLS, ClientControls)
{
    EVENT_PARAM(P_CONNECTION, Connection);      // Connection pointer
    EVENT_PARAM(P_FRAMENUMBER, FrameNumber);    // int (1-65535)
    EVENT_PARAM(P_BUTTONS, Buttons);            // int
    EVENT_PARAM(P_YAW, Yaw);                    // float (degrees)
    EVENT_PARAM(P_PITCH, Pitch);                // float (degrees)
    // Other parameters may exist as part of the user extra controls variant map
}

//! (Server) Client has been disconnected due to protocol violation
DEFINE_EVENT(EVENT_CLIENTDISCONNECTED, ClientDisconnected)
{
    EVENT_PARAM(P_CONNECTION, Connection);      // Connection pointer
}

//! (Client) Received scene list from server
DEFINE_EVENT(EVENT_GOTSCENELIST, GotSceneInfoList)
{
}

//! (Client) Joined the scene
DEFINE_EVENT(EVENT_JOINEDSCENE, JoinedScene)
{
}

//! (Client) Failed to join the scene
DEFINE_EVENT(EVENT_JOINSCENEFAILED, JoinSceneFailed)
{
    EVENT_PARAM(P_REASON, Reason);              // string
}

//! (Client) Left the scene
DEFINE_EVENT(EVENT_LEFTSCENE, LeftScene)
{
    EVENT_PARAM(P_CONNECTION, Connection);      // Connection pointer
    EVENT_PARAM(P_SCENE, Scene);                // Scene pointer
}

//! (Client) File transfer completed
DEFINE_EVENT(EVENT_FILETRANSFERCOMPLETED, FileTransferCompleted)
{
    EVENT_PARAM(P_FILENAME, FileName);          // string
    EVENT_PARAM(P_FULLPATH, FullPath);          // string
}

//! (Client) File transfer failed
DEFINE_EVENT(EVENT_FILETRANSFERFAILED, FileTransferFailed)
{
    EVENT_PARAM(P_FILENAME, FileName);          // string
    EVENT_PARAM(P_REASON, FileName);            // string
}

//! (Client) Controls update request, sent just before client update packet
DEFINE_EVENT(EVENT_CONTROLSUPDATE, ControlsUpdate)
{
    EVENT_PARAM(P_SCENE, Scene);                // Scene pointer
}

//! (Client) Controls playback request, sent during client-side prediction
DEFINE_EVENT(EVENT_CONTROLSPLAYBACK, ControlsPlayback)
{
    EVENT_PARAM(P_SCENE, Scene);                // Scene pointer
    EVENT_PARAM(P_TIMESTEP, TimeStep);          // float
    EVENT_PARAM(P_BUTTONS, Buttons);            // int
    EVENT_PARAM(P_YAW, Yaw);                    // float (degrees)
    EVENT_PARAM(P_PITCH, Pitch);                // float (degrees)
    // Other parameters may exist as part of the user extra controls variant map
}

#endif // ENGINE_PROTOCOLEVENTS_H
