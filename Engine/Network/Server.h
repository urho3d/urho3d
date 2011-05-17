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

#include "Object.h"
#include "Timer.h"

#include "Set.h"

class Connection;
class Network;
class Scene;
class VectorBuffer;

/// Server-side ongoing download, with a timer for closing the file if unused
struct ServerFileTransfer
{
    SharedPtr<File> file_;
    Timer closeTimer_;
};

/// Multiplayer server subsystem
class Server : public Object
{
    OBJECT(Server);
    
public:
    /// Construct with network subsystem pointer
    Server(Context* context);
    /// Destruct
    virtual ~Server();
    
    /// Set network updates (number of server frames) per second
    void SetNetFps(int fps);
    /// Set maximum unacked scene revisions stored per connection
    void SetMaxSceneRevisions(int revisions);
    /// Set delay for node becoming non-relevant, measured in server frames (prevent relevant/non-relevant state "flicker")
    void SetStayRelevantTime(int time);
    /// Add a scene to be provided over the network
    void AddScene(Scene* scene);
    /// Remove a scene
    void RemoveScene(Scene* scene);
    /// Start server in the specified port
    bool Start(unsigned short port);
    /// Stop server
    void Stop();
    /// Send and receive packets and update scene(s)
    void Update(float timeStep);
    /// Assign client to a scene
    bool SetClientScene(Connection* connection, Scene* scene);
    
    /// Return network updates per second
    int GetNetFps() const { return netFps_; }
    /// Return maximum unacked scene revisions stored per connection
    int GetMaxSceneRevisions() const { return maxSceneRevisions_; }
    /// Return delay for node becoming non-relevant
    int GetStayRelevantTime() const { return stayRelevantTime_; }
    /// Return whether is running on a port
    bool IsRunning() const;
    /// Return whether has a specific scene
    bool HasScene(Scene* scene) const;
    /// Return all scenes
    const Vector<SharedPtr<Scene> >& GetScenes() const { return scenes_; }
    /// Return all connections
    const Vector<SharedPtr<Connection> >& GetConnections() const { return connections_; }
    /// Return number of clients in scene
    unsigned GetNumUsersInScene(Scene* scene) const;
    
private:
    /// Receive and handle packets from a connection
    void HandlePackets(Connection* connection);
    /// Handle peer connected event
    void HandlePeerConnected(StringHash eventType, VariantMap& eventData);
    /// Handle peer disconnected event
    void HandlePeerDisconnected(StringHash eventType, VariantMap& eventData);
    /// Handle a reliable client packet. Return true if should continue receiving packets
    bool HandleReliablePacket(Connection* connection, VectorBuffer& packet);
    /// Handle a login packet. Return true if client was authorized
    bool HandleLogin(Connection* connection, VectorBuffer& packet);
    /// Handle a file request packet
    void HandleRequestFile(Connection* connection, VectorBuffer& packet);
    /// Handle a join scene packet
    void HandleJoinScene(Connection* connection, VectorBuffer& packet);
    /// Handle a full update ack packet
    void HandleFullUpdateAck(Connection* connection, VectorBuffer& packet);
    /// Handle a client update packet. Return true if should continue receiving packets
    bool HandleClientUpdate(Connection* connection, VectorBuffer& packet);
    /// Send scene info to the client
    void SendSceneInfo(Connection* connection);
    /// Send full scene update to the client
    void SendFullUpdate(Connection* connection);
    /// Send a scene update to the client
    void SendServerUpdate(Connection* connection);
    /// Generate a challenge value for the client
    unsigned GenerateChallenge() const;
    /// Disconnect client either forcibly or benevolently
    void Disconnect(Connection* connection, bool forced, const String& logMessage);
    /// Generate a scene update. If connection has no stored scene revisions, a full update will be written
    void WriteNetUpdate(Connection* connection, Serializer& dest);
    /// Return relevant node IDs for the client
    void GetRelevantNodes(Connection* connection, Set<unsigned>& dest) const;
    
    /// Scenes
    Vector<SharedPtr<Scene> > scenes_;
    /// Client connections
    Vector<SharedPtr<Connection> > connections_;
    /// Ongoing file downloads
    Map<StringHash, ServerFileTransfer> fileTransfers_;
    /// Network updates per second
    int netFps_;
    /// Network update time accumulator
    float timeAcc_;
    /// Current server framenumber
    unsigned short frameNumber_;
    /// Maximum scene revisions to store per connection
    unsigned maxSceneRevisions_;
    /// Delay for node becoming non-relevant, in server frames
    int stayRelevantTime_;
};
