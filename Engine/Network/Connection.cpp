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

#include "Precompiled.h"
#include "Connection.h"
#include "Log.h"
#include "Protocol.h"
#include "Scene.h"

#include <kNet.h>

#include "DebugNew.h"

OBJECTTYPESTATIC(Connection);

Connection::Connection(Context* context, bool isClient, kNet::SharedPtr<kNet::MessageConnection> connection) :
    Object(context),
    connection_(connection),
    isClient_(isClient),
    connectPending_(false),
    sceneLoaded_(false)
{
}

Connection::~Connection()
{
    // Reset owner from the scene, as this connection is about to be destroyed
    if (scene_)
        scene_->ResetOwner(this);
}

void Connection::SendMessage(int msgID, bool reliable, bool inOrder, const unsigned char* data, unsigned numBytes)
{
    // Make sure not to use kNet internal message ID's
    if (msgID <= 0x4 || msgID >= 0x3ffffffe)
    {
        LOGERROR("Can not send message with reserved ID");
        return;
    }
    
    connection_->SendMessage(msgID, reliable, inOrder, 0, 0, (const char*)data, numBytes);
}

void Connection::SendMessage(int msgID, bool reliable, bool inOrder, const VectorBuffer& msg)
{
    SendMessage(msgID, reliable, inOrder, msg.GetData(), msg.GetSize());
}

void Connection::SendMessage(int msgID, unsigned contentID, bool reliable, bool inOrder, const unsigned char* data, unsigned numBytes)
{
    // Make sure not to use kNet internal message ID's
    if (msgID <= 0x4 || msgID >= 0x3ffffffe)
    {
        LOGERROR("Can not send message with reserved ID");
        return;
    }
    
    connection_->SendMessage(msgID, reliable, inOrder, 0, contentID, (const char*)data, numBytes);
}

void Connection::SendMessage(int msgID, unsigned contentID, bool reliable, bool inOrder, const VectorBuffer& msg)
{
    SendMessage(msgID, contentID, reliable, inOrder, msg.GetData(), msg.GetSize());
}

void Connection::SendRemoteEvent(StringHash eventType, bool inOrder, const VariantMap& eventData)
{
    VectorBuffer msg;
    msg.WriteStringHash(eventType);
    msg.WriteVariantMap(eventData);
    SendMessage(MSG_REMOTEEVENT, true, inOrder, msg);
}

void Connection::SendRemoteEvent(Node* receiver, StringHash eventType, bool inOrder, const VariantMap& eventData)
{
    if (!receiver)
    {
        LOGERROR("Null node for remote node event");
        return;
    }
    if (receiver->GetScene() != scene_)
    {
        LOGERROR("Node is not in the connection's scene, can not send remote node event");
        return;
    }
    if (receiver->GetID() >= FIRST_LOCAL_ID)
    {
        LOGERROR("Node has a local ID, can not send remote node event");
        return;
    }
    
    VectorBuffer msg;
    msg.WriteVLE(receiver->GetID());
    msg.WriteStringHash(eventType);
    msg.WriteVariantMap(eventData);
    SendMessage(MSG_REMOTENODEEVENT, true, inOrder, msg);
}

void Connection::SetScene(Scene* newScene)
{
    if (scene_ == newScene)
        return;
    
    // Reset the owner reference from the previous scene's nodes
    if (scene_)
        scene_->ResetOwner(this);
    
    scene_ = newScene;
    sceneLoaded_ = false;
    
    if (isClient_ && scene_)
    {
        // When scene is assigned on the server, instruct the client to load it
        /// \todo Download package(s) needed for the scene, if they do not exist already on the client
        VectorBuffer msg;
        msg.WriteString(scene_->GetFileName());
        SendMessage(MSG_LOADSCENE, true, true, msg);
    }
}

void Connection::SetIdentity(const VariantMap& identity)
{
    identity_ = identity;
}

void Connection::SetControls(const Controls& newControls)
{
    previousControls_ = controls_;
    controls_ = newControls;
}

void Connection::SetConnectPending(bool connectPending)
{
    connectPending_ = connectPending;
}

void Connection::Disconnect(int waitMSec)
{
    connection_->Disconnect(waitMSec);
}

kNet::MessageConnection* Connection::GetMessageConnection() const
{
    return const_cast<kNet::MessageConnection*>(connection_.ptr());
}

Scene* Connection::GetScene() const
{
    return scene_;
}

bool Connection::IsConnected() const
{
    return connection_->GetConnectionState() == kNet::ConnectionOK;
}

String Connection::GetAddress() const
{
    const unsigned char* ip = connection_->RemoteEndPoint().ip;
    char str[256];
    sprintf(str, "%d.%d.%d.%d", (unsigned)ip[0], (unsigned)ip[1], (unsigned)ip[2], (unsigned)ip[3]);
    return String(str);
}

unsigned short Connection::GetPort() const
{
    return connection_->RemoteEndPoint().port;
}

String Connection::ToString() const
{
    return GetAddress() + ":" + String(GetPort());
}
