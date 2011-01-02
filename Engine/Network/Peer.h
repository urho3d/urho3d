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

#ifndef NETWORK_PEER_H
#define NETWORK_PEER_H

#include "EventListener.h"
#include "RefCount.h"
#include "Timer.h"
#include "VectorBuffer.h"

#include <list>

//! Peer type
enum PeerType
{
    PEER_SERVER = 1,
    PEER_CLIENT
};

//! Peer's connection state
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

//! Queued packet
struct QueuedPacket
{
    //! ENet packet
    ENetPacket* mPacket;
    //! Channel number
    unsigned char mChannel;
    //! Timer for latency simulation
    Timer mTimer;
};

//! Networking peer (a remote host)
class Peer : public RefCounted, public EventListener
{
    friend class Network;
    
public:
    //! Construct with ENet peer pointer, peer type, and whether to notify of packets with events
    Peer(ENetPeer* peer, PeerType type, bool sendPacketEvents);
    virtual ~Peer();
    
    //! Send a packet
    void send(const VectorBuffer& packet, unsigned char channel, bool reliable, bool inOrder = true);
    //! Send a packet
    void send(const void* data, unsigned size, unsigned char channel, bool reliable, bool inOrder = true);
    //! Attempt to receive a packet. Return true if a packet was received. No effect if events are used.
    bool receive(VectorBuffer& packet, unsigned char channel = CHANNEL_ANY);
    //! Send latency simulated packets
    void update();
    //! Remove all queued packets
    void flushPackets();
    //! Disconnect benevolently
    void disconnect();
    //! Disconnect forcibly
    void forceDisconnect();
    //! Set whether to use events to notify of received packets
    void setSendPacketEvents(bool enable);
    //! Set simulated packet loss between 0.0 - 1.0
    void setSimulatedPacketLoss(float loss);
    //! Set simulated connection latency in milliseconds
    void setSimulatedLatency(unsigned lag);
    //! Set user data for identifying the peer
    void setUserData(void* userData);
    
    //! Return peer type
    PeerType getType() const { return mType; }
    //! Return connection state
    ConnectionState getConnectionState() const { return mConnectionState; }
    //! Return whether has received packets waiting
    bool hasPackets() const { return mPackets.size() > 0; }
    //! Return number of received packets waiting
    unsigned getNumPackets() const { return mPackets.size(); }
    //! Return address of remote host
    const std::string& getAddress()const { return mAddress; }
    //! Return port of remote host
    unsigned short getPort() const { return mPort; }
    //! Return whether to notify of received packets with events
    bool getSendPacketEvents() const { return mSendPacketEvents; }
    //! Return simulated packet loss
    float getSimulatedPacketLoss() const { return mSimulatedPacketLoss; }
    //! Return simulated latency
    unsigned getSimulatedLatency() const { return mSimulatedLatency; }
    //! Return user data
    void* getUserData() const { return mUserData; }
    
private:
    //! Handle connection
    void onConnect();
    //! Handle disconnection
    void onDisconnect();
    
    //! ENet peer
    ENetPeer* mPeer;
    //! Peer type
    PeerType mType;
    //! Connection state
    ConnectionState mConnectionState;
    //! Received packets per channel
    std::map<unsigned char, std::list<QueuedPacket> > mPackets;
    //! Latency-simulated packets waiting to be sent
    std::list<QueuedPacket> mSentPackets;
    //! Remote host address
    std::string mAddress;
    //! Remote host port
    unsigned short mPort;
    //! Send events for received packets flag
    bool mSendPacketEvents;
    //! Simulated packet loss
    float mSimulatedPacketLoss;
    //! Simulated latency
    unsigned mSimulatedLatency;
    //! Half of simulated latency, to divide evenly between send and receive latency
    unsigned mHalfSimulatedLatency;
    //! User data
    void* mUserData;
};

#endif // NETWORK_PEER_H
