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
#include "Log.h"
#include "NetworkEvents.h"
#include "Peer.h"
#include "StringUtils.h"

#include <enet/enet.h>

#include "DebugNew.h"

Peer::Peer(ENetPeer* peer, PeerType type, bool sendPacketEvents) :
    mPeer(peer),
    mType(type),
    mConnectionState(CS_CONNECTING),
    mPort(0),
    mSimulatedPacketLoss(0.0f),
    mSimulatedLatency(0),
    mHalfSimulatedLatency(0),
    mSendPacketEvents(sendPacketEvents),
    mUserData(0)
{
}

Peer::~Peer()
{
    flushPackets();
    onDisconnect();
}

void Peer::setSendPacketEvents(bool enable)
{
    mSendPacketEvents = enable;
}

void Peer::send(const VectorBuffer& packet, unsigned char channel, bool reliable, bool inOrder)
{
    if ((!mPeer) || (!packet.getSize()))
        return;
    
    if ((mSimulatedPacketLoss > 0.0f) && (!reliable))
    {
        if (random() < mSimulatedPacketLoss)
            return;
    }
    
    ENetPacket* enetPacket = enet_packet_create(packet.getData(), packet.getSize(), reliable ? ENET_PACKET_FLAG_RELIABLE :
        (inOrder ? 0 : ENET_PACKET_FLAG_UNSEQUENCED));
    
    if (!mSimulatedLatency)
        enet_peer_send(mPeer, channel, enetPacket);
    else
    {
        QueuedPacket packet;
        packet.mPacket = enetPacket;
        packet.mChannel = channel;
        mSentPackets.push_back(packet);
    }
}

void Peer::send(const void* data, unsigned size, unsigned char channel, bool reliable, bool inOrder)
{
    if ((!mPeer) || (!data) || (!size))
        return;
    
    if ((mSimulatedPacketLoss != 0.0f) && (!reliable))
    {
        if (random() < mSimulatedPacketLoss)
            return;
    }
    
    ENetPacket* enetPacket = enet_packet_create(data, size, reliable ? ENET_PACKET_FLAG_RELIABLE : (inOrder ? 0 :
        ENET_PACKET_FLAG_UNSEQUENCED));
    
    if (!mSimulatedLatency)
        enet_peer_send(mPeer, channel, enetPacket);
    else
    {
        QueuedPacket packet;
        packet.mPacket = enetPacket;
        packet.mChannel = channel;
        mSentPackets.push_back(packet);
    }
}

bool Peer::receive(VectorBuffer& packet, unsigned char channel)
{
    bool received = false;
    bool reliable = false;
    
    if (channel == CHANNEL_ANY)
    {
        for (std::map<unsigned char, std::list<QueuedPacket> >::iterator i = mPackets.begin(); i != mPackets.end(); ++i)
        {
            std::list<QueuedPacket>& packetList = i->second;
            if ((!packetList.empty()) && (packetList.front().mTimer.getMSec(false) >= mHalfSimulatedLatency))
            {
                ENetPacket* enetPacket = packetList.front().mPacket;
                reliable = (enetPacket->flags & ENET_PACKET_FLAG_RELIABLE) != 0;
                packetList.pop_front();
                
                packet.setData(enetPacket->data, enetPacket->dataLength);
                enet_packet_destroy(enetPacket);
                received = true;
                break;
            }
        }
    }
    else
    {
        std::list<QueuedPacket>& packetList = mPackets[channel];
        if ((!packetList.empty()) && (packetList.front().mTimer.getMSec(false) >= mHalfSimulatedLatency))
        {
            ENetPacket* enetPacket = packetList.front().mPacket;
            reliable = (enetPacket->flags & ENET_PACKET_FLAG_RELIABLE) != 0;
            packetList.pop_front();
            
            packet.setData(enetPacket->data, enetPacket->dataLength);
            enet_packet_destroy(enetPacket);
            received = true;
        }
    }
    
    if ((received) && (!reliable) && (mSimulatedPacketLoss > 0.0f))
    {
        if (random() < mSimulatedPacketLoss)
        {
            packet.clear();
            received = false;
        }
    }
    
    return received;
}

void Peer::update()
{
    // Check send timer of packets with simulated latency and send as necessary
    for (std::list<QueuedPacket>::iterator i = mSentPackets.begin(); i != mSentPackets.end();)
    {
        if (i->mTimer.getMSec(false) >= mHalfSimulatedLatency)
        {
            enet_peer_send(mPeer, i->mChannel, i->mPacket);
            i = mSentPackets.erase(i);
        }
        else
            ++i;
    }
}

void Peer::flushPackets()
{
    for (std::map<unsigned char, std::list<QueuedPacket> >::iterator i = mPackets.begin(); i != mPackets.end(); ++i)
    {
        std::list<QueuedPacket>& packetList = i->second;
        while (!packetList.empty())
        {
            ENetPacket* enetPacket = packetList.front().mPacket;
            packetList.pop_front();
            enet_packet_destroy(enetPacket);
        }
    }
    while (!mSentPackets.empty())
    {
        ENetPacket* enetPacket = mSentPackets.front().mPacket;
        mSentPackets.pop_front();
        enet_packet_destroy(enetPacket);
    }
}

void Peer::disconnect()
{
    if ((mPeer) && (mConnectionState > CS_DISCONNECTING))
    {
        mConnectionState = CS_DISCONNECTING;
        enet_peer_disconnect(mPeer, 0);
    }
}

void Peer::forceDisconnect()
{
    onDisconnect();
}

void Peer::setSimulatedPacketLoss(float loss)
{
    mSimulatedPacketLoss = clamp(loss, 0.0f, 1.0f);
}

void Peer::setSimulatedLatency(unsigned latency)
{
    mSimulatedLatency = latency;
    mHalfSimulatedLatency = latency >> 1;
}

void Peer::onConnect()
{
    if (mPeer)
    {
        static const int MAX_IPADDRESS = 32;
        char ipBuffer[MAX_IPADDRESS];
        enet_address_get_host_ip(&mPeer->address, ipBuffer, MAX_IPADDRESS);
        mAddress = std::string(ipBuffer);
        mPort = mPeer->address.port;
        mConnectionState = CS_CONNECTED;
        
        // Send event
        using namespace PeerConnected;
        
        VariantMap eventData;
        eventData[P_PEER] = (void*)this;
        sendEvent(EVENT_PEERCONNECTED, eventData);
        
        LOGINFO(mAddress + ":" + toString(mPort) + " connected");
    }
}

void Peer::onDisconnect()
{
    if (mPeer)
    {
        enet_peer_reset(mPeer);
        mConnectionState = CS_DISCONNECTED;
        mPeer = 0;
        
        // Send event
        using namespace PeerDisconnected;
        
        VariantMap eventData;
        eventData[P_PEER] = (void*)this;
        sendEvent(EVENT_PEERDISCONNECTED, eventData);
        
        if (!mAddress.empty())
            LOGINFO(mAddress + ":" + toString(mPort) + " disconnected");
        else
            LOGINFO("Disconnected");
    }
}
