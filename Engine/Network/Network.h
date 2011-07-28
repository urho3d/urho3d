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

#include "Connection.h"
#include "Object.h"
#include "VectorBuffer.h"

#include <kNet/IMessageHandler.h>
#include <kNet/INetworkServerListener.h>

class MemoryBuffer;
class Scene;

/// Network subsystem. Manages joining to or hosting networked scenes.
class Network : public Object, public kNet::IMessageHandler, public kNet::INetworkServerListener
{
    OBJECT(Network);
    
public:
    /// Construct
    Network(Context* context);
    /// Destruct
    ~Network();
    
    /// Handle a kNet message from either a client or the server
    virtual void HandleMessage(kNet::MessageConnection* source, kNet::message_id_t id, const char* data, size_t numBytes);
    /// Compute the content ID for a message
    virtual u32 ComputeContentID(kNet::message_id_t id, const char* data, size_t numBytes);
    /// Handle a new client connection
    virtual void NewConnectionEstablished(kNet::MessageConnection* connection);
    /// Handle a client disconnection
    virtual void ClientDisconnected(kNet::MessageConnection* connection);
    
    /// Connect to a server using UDP protocol. Return true if connection process successfully started
    bool Connect(const String& address, unsigned short port, Scene* scene, const VariantMap& identity = VariantMap());
    /// Disconnect the connection to the server. If wait time is non-zero, will block while waiting for disconnect to finish
    void Disconnect(int waitMSec = 0);
    /// Start a server on a port using UDP protocol. Return true if successful
    bool StartServer(unsigned short port);
    /// Stop the server
    void StopServer();
    /// Broadcast a message with content ID to all client connections
    void BroadcastMessage(int msgID, bool reliable, bool inOrder, const VectorBuffer& msg, unsigned priority = 0, unsigned contentID = 0);
    /// Broadcast a message with content ID to all client connections
    void BroadcastMessage(int msgID, bool reliable, bool inOrder, const unsigned char* data, unsigned numBytes, unsigned priority = 0, unsigned contentID = 0);
    /// Broadcast a remote event to all client connections
    void BroadcastRemoteEvent(StringHash eventType, bool inOrder, const VariantMap& eventData = VariantMap());
    /// Broadcast a remote event to all client connections in the specific scene
    void BroadcastRemoteEvent(Scene* scene, StringHash eventType, bool inOrder, const VariantMap& eventData = VariantMap());
    /// Broadcast a remote node event to all client connections in the scene with this node
    void BroadcastRemoteEvent(Node* receiver, StringHash eventType, bool inOrder, const VariantMap& eventData = VariantMap());
    /// Set network update FPS
    void SetUpdateFps(int fps);
    /// Register a remote event as allowed to be sent and received. If no events are registered, all are allowed
    void RegisterRemoteEvent(StringHash eventType);
    /// Unregister a remote event as allowed to be sent and received
    void UnregisterRemoteEvent(StringHash eventType);
    /// Unregister all remote events. This results in all being allowed
    void UnregisterAllRemoteEvents();
    /// Set the package download cache path
    void SetPackageCacheDir(const String& path);
    
    /// Return network update FPS
    int GetUpdateFps() const { return updateFps_; }
    /// Return a client or server connection by kNet MessageConnection, or null if none exist
    Connection* GetConnection(kNet::MessageConnection* connection) const;
    /// Return the connection to the server. Null if not connected
    Connection* GetServerConnection() const;
    /// Return all client connections
    const Map<kNet::MessageConnection*, SharedPtr<Connection> > GetClientConnections() const { return clientConnections_; }
    /// Return whether the server is running
    bool IsServerRunning() const;
    /// Return whether a remote event is allowed to be sent and received. If no events are registered, all are allowed
    bool CheckRemoteEvent(StringHash eventType) const;
    /// Return the package download cache path
    const String& GetPackageCacheDir() const { return packageCacheDir_; }
    
    /// Update connections. Called by HandleBeginFrame
    void Update(float timeStep);
    
private:
    /// Handle begin frame event
    void HandleBeginFrame(StringHash eventType, VariantMap& eventData);
    /// Handle server connection
    void OnServerConnected();
    /// Handle server disconnection
    void OnServerDisconnected();
    
    /// kNet Network instance
    kNet::Network* network_;
    /// Client's server connection
    SharedPtr<Connection> serverConnection_;
    /// Server's client connections
    Map<kNet::MessageConnection*, SharedPtr<Connection> > clientConnections_;
    /// Allowed remote events
    Set<StringHash> allowedRemoteEvents_;
    /// Network update FPS
    int updateFps_;
    /// Network time interval
    float updateInterval_;
    /// Network update time accumulator
    float updateAcc_;
    /// Package cache directory
    String packageCacheDir_;
};
