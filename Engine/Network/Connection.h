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

#include "Controls.h"
#include "Object.h"
#include "VectorBuffer.h"

#include <kNetFwd.h>
#include <kNet/SharedPtr.h>

#ifdef SendMessage
#undef SendMessage
#endif

class Node;
class Scene;

/// Connection in a networked scene
class Connection : public Object
{
    OBJECT(Connection);
    
public:
    /// Construct with context and kNet message connection pointers
    Connection(Context* context, bool isClient, kNet::SharedPtr<kNet::MessageConnection> connection);
    /// Destruct
    ~Connection();
    
    /// Send a message
    void SendMessage(int msgID, bool reliable, bool inOrder, const unsigned char* data, unsigned numBytes);
    /// Send a message
    void SendMessage(int msgID, bool reliable, bool inOrder, const VectorBuffer& msg);
    /// Send a message with content ID
    void SendMessage(int msgID, unsigned contentID, bool reliable, bool inOrder, const unsigned char* data, unsigned numBytes);
    /// Send a message with content ID
    void SendMessage(int msgID, unsigned contentID, bool reliable, bool inOrder, const VectorBuffer& msg);
    /// Send a remote event
    void SendRemoteEvent(StringHash eventType, bool inOrder, const VariantMap& eventData = VariantMap());
    /// Send a remote node event
    void SendRemoteEvent(Node* receiver, StringHash eventType, bool inOrder, const VariantMap& eventData = VariantMap());
    /// Assign scene. On the server, this will cause the client to load it
    void SetScene(Scene* newScene);
    /// Assign identity. Called by Network
    void SetIdentity(const VariantMap& identity);
    /// Set new controls. Moves the current controls as previous
    void SetControls(const Controls& newControls);
    /// Set the connection pending status. Called by Network
    void SetConnectPending(bool connectPending);
    /// Disconnect. If wait time is non-zero, will block while waiting for disconnect to finish
    void Disconnect(int waitMSec = 0);
    
    /// Return the kNet message connection
    kNet::MessageConnection* GetMessageConnection() const;
    /// Return client identity
    const VariantMap& GetIdentity() const { return identity_; }
    /// Return the scene used by this connection
    Scene* GetScene() const;
    /// Return the client controls of this connection
    const Controls& GetControls() const { return controls_; }
    /// Return the previous client controls of this connection
    const Controls& GetPreviousControls() const { return previousControls_; }
    /// Return whether is a client connection
    bool IsClient() const { return isClient_; }
    /// Return whether is fully connected
    bool IsConnected() const;
    /// Return whether connection is pending
    bool IsConnectPending() const { return connectPending_; }
    /// Return whether the scene is loaded and ready to receive updates from network
    bool IsSceneLoaded() const { return sceneLoaded_; }
    /// Return remote address
    String GetAddress() const;
    /// Return remote port
    unsigned short GetPort() const;
    /// Return an address:port string
    String ToString() const;
    
private:
    /// kNet message connection
    kNet::SharedPtr<kNet::MessageConnection> connection_;
    /// Identity map
    VariantMap identity_;
    /// Scene
    WeakPtr<Scene> scene_;
    /// Current controls
    Controls controls_;
    /// Previous controls
    Controls previousControls_;
    /// Client flag
    bool isClient_;
    /// Connection pending flag
    bool connectPending_;
    /// Scene loaded flag
    bool sceneLoaded_;
};
