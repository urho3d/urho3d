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
#include "VectorBuffer.h"

class Peer;

struct _ENetHost;

typedef _ENetHost ENetHost;

/// Network subsystem. Sends and receives packets using ENet
class Network : public Object
{
    OBJECT(Network);
    
public:
    /// Construct. Initialize ENet
    Network(Context* context);
    /// Destruct. Deinitialize ENet
    ~Network();
    
    /// Set maximum connections on the server
    void SetServerMaxConnections(unsigned server);
    /// Set maximum connections on the client
    void SetClientMaxConnections(unsigned client);
    /// Set number of packet channels to use. Each has its own packet ordering
    void SetNumChannels(unsigned channels);
    /// Set incoming and outgoing data rate
    void SetDataRate(int dataInBps, int dataOutBps);
    /// Service incoming and outgoing packets. Called by HandleBeginFrame()
    void Update();
    /// Start server on a port. Return true if successful
    bool StartServer(unsigned short port);
    /// Connect to a server
    Peer* Connect(const String& address, unsigned short port);
    /// Broadcast a packet to all connected client peers
    void Broadcast(const VectorBuffer& packet, unsigned char channel, bool reliable, bool inOrder = true);
    /// Broadcast a packet to all connected client peers
    void Broadcast(const void* data, unsigned size, unsigned char channel, bool reliable, bool inOrder = true);
    /// Stop server and close all connections
    void StopServer();
    /// Stop server and close all connections
    void StopClient();
    
    /// Return whether server has been started
    bool IsServer() const { return serverHost_ != 0; }
    /// Return whether client has been started (is automatically started when a connection attempt is made)
    bool IsClient() const { return clientHost_ != 0; }
    /// Return number of networking peers
    unsigned GetNumPeers() const { return peers_.size(); }
    /// Return all networking peers
    const std::vector<SharedPtr<Peer> >& GetPeers() const { return peers_; }
    /// Return networking peer by index
    Peer* GetPeer(unsigned index) const;
    /// Return the first server peer
    Peer* GetServerPeer() const;
    /// Return maximum server connections
    unsigned GetServerMaxConnections() const { return serverMaxConnections_; }
    /// Return maximum client connections
    unsigned GetClientMaxConnections() const { return clientMaxConnections_; }
    /// Return number of packet channels
    unsigned GetNumChannels() const { return numChannels_; }
    /// Return incoming data rate
    int GetDataRateIn() const { return dataInBps_; }
    /// Return outgoing data rate
    int GetDataRateOut() const { return dataOutBps_; }
    
private:
    /// Update a specific network host
    void Update(ENetHost* enetHost);
    /// Handle frame begin event
    void HandleBeginFrame(StringHash eventType, VariantMap& eventData);
    
    /// Server host
    ENetHost* serverHost_;
    /// Client host
    ENetHost* clientHost_;
    /// Peers
    std::vector<SharedPtr<Peer> > peers_;
    /// Maximum server connections
    unsigned serverMaxConnections_;
    /// Maximum client connections
    unsigned clientMaxConnections_;
    /// Number of packet channels to use
    unsigned numChannels_;
    /// Incoming data rate
    int dataInBps_;
    /// Outgoing data rate
    int dataOutBps_;
};
