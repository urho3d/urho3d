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
#include "Network.h"
#include "NetworkEvents.h"
#include "Peer.h"
#include "Profiler.h"
#include "StringUtils.h"

#include <enet/enet.h>

#include "DebugNew.h"

static unsigned instanceCount = 0;

Network::Network() :
    mServerHost(0),
    mClientHost(0),
    mServerMaxConnections(32),
    mClientMaxConnections(2),
    mNumChannels(4),
    mDataInBps(0),
    mDataOutBps(0),
    mSendPacketEventsDefault(false)
{
    if (!instanceCount)
    {
        if (enet_initialize() != 0)
            EXCEPTION("Could not initialize networking");
    }
    ++instanceCount;
    
    LOGINFO("Network created");
}

Network::~Network()
{
    stopServer();
    stopClient();
    
    --instanceCount;
    if (!instanceCount)
        enet_deinitialize();
    
    LOGINFO("Network shut down");
}

void Network::setServerMaxConnections(int connections)
{
    mServerMaxConnections = max(connections, 1);
}

void Network::setClientMaxConnections(int connections)
{
    mClientMaxConnections = max(connections, 1);
}

void Network::setNumChannels(unsigned char channels)
{
    if (!channels)
        channels = 1;
    
    if (mServerHost)
        enet_host_channel_limit(mServerHost, mNumChannels);
    if (mClientHost)
        enet_host_channel_limit(mClientHost, mNumChannels);
}

void Network::setDataRate(int dataInBps, int dataOutBps)
{
    mDataInBps = max(dataInBps, 0);
    mDataOutBps = max(dataOutBps, 0);
    
    if (mServerHost)
        enet_host_bandwidth_limit(mServerHost, mDataInBps, mDataOutBps);
    if (mClientHost)
        enet_host_bandwidth_limit(mClientHost, mDataInBps, mDataOutBps);
}

void Network::setSendPacketEventsDefault(bool enable)
{
    mSendPacketEventsDefault = enable;
}

void Network::update()
{
    PROFILE(Network_Update);
    
    // Service hosts if they exist
    if (mServerHost)
        update(mServerHost);
    if (mClientHost)
        update(mClientHost);
    
    // Update peers and purge those that are disconnected
    for (std::vector<SharedPtr<Peer> >::iterator i = mPeers.begin(); i != mPeers.end();)
    {
        (*i)->update();
        
        if ((*i)->getConnectionState() == CS_DISCONNECTED)
            i = mPeers.erase(i);
        else
            ++i;
    }
}

bool Network::startServer(unsigned short port)
{
    stopServer();
    
    ENetAddress server;
    server.host = ENET_HOST_ANY;
    server.port = port;
    
    mServerHost = enet_host_create(&server, mServerMaxConnections, mNumChannels, mDataInBps, mDataOutBps);
    if (mServerHost)
        enet_host_compress_with_range_coder(mServerHost);
    else
    {
        LOGERROR("Failed to start server on port " + toString(port));
        return false;
    }
    

    LOGINFO("Started server on port " + toString(port));
    return true;
}

Peer* Network::connect(const std::string& address, unsigned short port)
{
    // Create client host if one did not exist already
    if (!mClientHost)
    {
        mClientHost = enet_host_create(0, mClientMaxConnections, mNumChannels, mDataInBps, mDataOutBps);
        if (mClientHost)
            enet_host_compress_with_range_coder(mClientHost);
        else
        {
            LOGERROR("Failed to create client host");
            return 0;
        }
    }
    
    // Attempt to connect
    ENetAddress server;
    enet_address_set_host(&server, address.c_str());
    server.port = port;
    ENetPeer* enetPeer = enet_host_connect(mClientHost, &server, mNumChannels, 0);
    if (!enetPeer)
    {
        LOGERROR("No available network connections");
        return 0;
    }
    
    // Create a Peer instance for the server
    SharedPtr<Peer> newPeer(new Peer(enetPeer, PEER_SERVER, mSendPacketEventsDefault));
    enetPeer->data = newPeer.getPtr();
    mPeers.push_back(newPeer);
    
    LOGINFO("Connecting to " + address + ":" + toString(port));
    return newPeer;
}

void Network::broadcast(const void* data, unsigned size, unsigned char channel, bool reliable, bool inOrder)
{
    if (!mServerHost)
    {
        LOGERROR("No server running, can not broadcast");
        return;
    }
    
    if ((!data) || (!size))
        return;
    
    ENetPacket* enetPacket = enet_packet_create(data, size, reliable ? ENET_PACKET_FLAG_RELIABLE : (inOrder ? 0 :
        ENET_PACKET_FLAG_UNSEQUENCED));
    
    enet_host_broadcast(mServerHost, channel, enetPacket);
}


void Network::broadcast(const VectorBuffer& packet, unsigned char channel, bool reliable, bool inOrder)
{
    if (!mServerHost)
    {
        LOGERROR("No server running, can not broadcast");
        return;
    }
    
    if (!packet.getSize())
        return;
    
    ENetPacket* enetPacket = enet_packet_create(packet.getData(), packet.getSize(), reliable ? ENET_PACKET_FLAG_RELIABLE :
        (inOrder ? 0 : ENET_PACKET_FLAG_UNSEQUENCED));
    
    enet_host_broadcast(mServerHost, channel, enetPacket);
}

void Network::stopServer()
{
    if (mServerHost)
    {
        // Disconnect all peers created through the server host
        for (std::vector<SharedPtr<Peer> >::iterator i = mPeers.begin(); i != mPeers.end(); ++i)
        {
            if ((*i)->getType() == PEER_CLIENT)
                (*i)->disconnect();
        }
        
        // Update once more, so that disconnect packet (maybe) goes to clients
        update(mServerHost);
        
        // Then perform forcible disconnection
        for (std::vector<SharedPtr<Peer> >::iterator i = mPeers.begin(); i != mPeers.end(); ++i)
        {
            if ((*i)->getType() == PEER_CLIENT)
                (*i)->onDisconnect();
        }
        
        enet_host_destroy(mServerHost);
        mServerHost = 0;
        
        LOGINFO("Stopped server");
    }
}

void Network::stopClient()
{
    if (mClientHost)
    {
        // Disconnect all peers created through the client host
        for (std::vector<SharedPtr<Peer> >::iterator i = mPeers.begin(); i != mPeers.end(); ++i)
        {
            if ((*i)->getType() == PEER_SERVER)
                (*i)->disconnect();
        }
        
        // Update once more, so that disconnect packet (maybe) goes to server
        update(mClientHost);
        
        // Then perform forcible disconnection
        for (std::vector<SharedPtr<Peer> >::iterator i = mPeers.begin(); i != mPeers.end(); ++i)
        {
            if ((*i)->getType() == PEER_SERVER)
                (*i)->onDisconnect();
        }
        
        enet_host_destroy(mClientHost);
        mClientHost = 0;
        
        LOGINFO("Stopped client");
    }
}

Peer* Network::getPeer(unsigned index) const
{
    return index < mPeers.size() ? mPeers[index] : (Peer*)0;
}

Peer* Network::getServerPeer() const
{
    // Just return the first server peer
    for (std::vector<SharedPtr<Peer> >::const_iterator i = mPeers.begin(); i != mPeers.end(); ++i)
    {
        if ((*i)->getType() == PEER_SERVER)
            return *i;
    }
    
    return 0;
}

void Network::update(ENetHost* enetHost)
{
    ENetEvent enetEvent;
    ENetPeer* enetPeer;
    Peer* peer;
    
    while (enet_host_service(enetHost, &enetEvent, 0) > 0)
    {
        enetPeer = enetEvent.peer;
        peer = static_cast<Peer*>(enetPeer->data);
        
        switch (enetEvent.type)
        {
        case ENET_EVENT_TYPE_CONNECT:
            if (!peer)
            {
                // If no existing Peer instance (server operation), create one now
                SharedPtr<Peer> newPeer(new Peer(enetPeer, PEER_CLIENT, mSendPacketEventsDefault));
                enetPeer->data = newPeer.getPtr();
                mPeers.push_back(newPeer);
                newPeer->onConnect();
            }
            else
                peer->onConnect();
            break;
            
        case ENET_EVENT_TYPE_RECEIVE:
            if (peer)
            {
                if (peer->getSendPacketEvents())
                {
                    // Send event if packet events are enabled
                    // Note: receiving packets with events does not support simulated latency
                    using namespace NetworkPacket;
                    
                    VariantMap eventData;
                    eventData[P_PEER] = (void*)peer;
                    eventData[P_CHANNEL] = enetEvent.channelID;
                    eventData[P_DATA].setBuffer(enetEvent.packet->data, enetEvent.packet->dataLength);
                    sendEvent(EVENT_NETWORKPACKET, eventData);
                    
                    enet_packet_destroy(enetEvent.packet);
                }
                else
                {
                    // Else queue the packet
                    QueuedPacket newPacket;
                    newPacket.mPacket = enetEvent.packet;
                    newPacket.mChannel = enetEvent.channelID;
                    peer->mPackets[enetEvent.channelID].push_back(newPacket);
                }
            }
            else
                enet_packet_destroy(enetEvent.packet);
            break;
            
        case ENET_EVENT_TYPE_DISCONNECT:
            if (peer)
            {
                peer->onDisconnect();
                enetPeer->data = 0;
            }
            break;
        }
    }
}

