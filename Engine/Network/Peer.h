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
#include "VectorBuffer.h"

#include <list>

/// Peer type
enum PeerType
{
    PEER_SERVER = 1,
    PEER_CLIENT
};

/// Peer's connection state
enum ConnectionState
{
    CS_DISCONNECTED = 0,
    CS_DISCONNECTING,
    CS_CONNECTING,
    CS_CONNECTED
};

static const unsigned char CHANNEL_ANY = 0xff;

class VectorBuffer;

struct _ENetHost;
struct _ENetPacket;
struct _ENetPeer;

typedef _ENetHost ENetHost;
typedef _ENetPacket ENetPacket;
typedef _ENetPeer ENetPeer;

/// Queued packet
struct QueuedPacket
{
    /// ENet packet
    ENetPacket* packet_;
    /// Channel number
    unsigned char channel_;
    /// Timer for latency simulation
    Timer timer_;
};

/// Networking peer (a remote host)
class Peer : public Object
{
    OBJECT(Peer);
    
    friend class Network;
    
public:
    /// Construct
    Peer(Context* context, ENetPeer* peer, PeerType type);
    /// Destruct
    virtual ~Peer();
    
    /// Send a packet
    void Send(const VectorBuffer& packet, unsigned char channel, bool reliable, bool inOrder = true);
    /// Send a packet
    void Send(const void* data, unsigned size, unsigned char channel, bool reliable, bool inOrder = true);
    /// Attempt to receive a packet. Return true if a packet was received
    bool Receive(VectorBuffer& packet, unsigned char channel = CHANNEL_ANY);
    /// Send latency simulated packets
    void Update();
    /// Remove all queued packets
    void FlushPackets();
    /// Disconnect benevolently
    void Disconnect();
    /// Disconnect forcibly
    void ForceDisconnect();
    /// Set simulated packet loss between 0.0 - 1.0
    void SetSimulatedPacketLoss(float loss);
    /// Set simulated connection latency in milliseconds
    void SetSimulatedLatency(unsigned lag);
    /// Set user data for identifying the peer
    void SetUserData(void* userData);
    
    /// Return peer type
    PeerType GetPeerType() const { return type_; }
    /// Return connection state
    ConnectionState GetConnectionState() const { return connectionState_; }
    /// Return whether has received packets waiting
    bool HasPackets() const { return packets_.size() > 0; }
    /// Return number of received packets waiting
    unsigned GetNumPackets() const { return packets_.size(); }
    /// Return address of remote host
    const std::string& GetAddress()const { return address_; }
    /// Return port of remote host
    unsigned short GetPort() const { return port_; }
    /// Return simulated packet loss
    float GetSimulatedPacketLoss() const { return simulatedPacketLoss_; }
    /// Return simulated latency
    unsigned GetSimulatedLatency() const { return simulatedLatency_; }
    /// Return user data
    void* GetUserData() const { return userData_; }
    
private:
    /// Handle connection
    void OnConnect();
    /// Handle disconnection
    void OnDisconnect();
    
    /// ENet peer
    ENetPeer* peer_;
    /// Peer type
    PeerType type_;
    /// Connection state
    ConnectionState connectionState_;
    /// Received packets per channel
    std::map<unsigned char, std::list<QueuedPacket> > packets_;
    /// Latency-simulated packets waiting to be sent
    std::list<QueuedPacket> sentPackets_;
    /// Remote host address
    std::string address_;
    /// Remote host port
    unsigned short port_;
    /// Simulated packet loss
    float simulatedPacketLoss_;
    /// Simulated latency
    unsigned simulatedLatency_;
    /// Half of simulated latency, to divide evenly between send and receive latency
    unsigned halfSimulatedLatency_;
    /// User data
    void* userData_;
};
