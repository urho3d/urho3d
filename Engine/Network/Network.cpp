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
#include "Context.h"
#include "CoreEvents.h"
#include "Log.h"
#include "Mutex.h"
#include "Network.h"
#include "NetworkEvents.h"
#include "Peer.h"
#include "ProcessUtils.h"
#include "Profiler.h"

#include <enet/enet.h>

#include "DebugNew.h"

static unsigned numInstances = 0;

OBJECTTYPESTATIC(Network);

Network::Network(Context* context) :
    Object(context),
    serverHost_(0),
    clientHost_(0),
    serverMaxConnections_(32),
    clientMaxConnections_(2),
    numChannels_(4),
    dataInBps_(0),
    dataOutBps_(0)
{
    {
        MutexLock lock(GetStaticMutex());
        
        if (!numInstances)
        {
            if (enet_initialize() != 0)
                LOGERROR("Could not initialize networking");
        }
        ++numInstances;
    }
    
    SubscribeToEvent(E_BEGINFRAME, HANDLER(Network, HandleBeginFrame));
}

Network::~Network()
{
    StopServer();
    StopClient();
    
    {
        MutexLock lock(GetStaticMutex());
        
        --numInstances;
        if (!numInstances)
            enet_deinitialize();
    }
}

void Network::SetServerMaxConnections(unsigned connections)
{
    if (!connections)
        connections = 1;
    serverMaxConnections_ = connections;
}

void Network::SetClientMaxConnections(unsigned connections)
{
    if (!connections)
        connections = 1;
    clientMaxConnections_ = connections;
}

void Network::SetNumChannels(unsigned channels)
{
    if (!channels)
        channels = 1;
    if (channels > 255)
        channels = 255;
    
    numChannels_ = channels;
    
    if (serverHost_)
        enet_host_channel_limit(serverHost_, numChannels_);
    if (clientHost_)
        enet_host_channel_limit(clientHost_, numChannels_);
}

void Network::SetDataRate(int dataInBps, int dataOutBps)
{
    dataInBps_ = Max(dataInBps, 0);
    dataOutBps_ = Max(dataOutBps, 0);
    
    if (serverHost_)
        enet_host_bandwidth_limit(serverHost_, dataInBps_, dataOutBps_);
    if (clientHost_)
        enet_host_bandwidth_limit(clientHost_, dataInBps_, dataOutBps_);
}

void Network::Update()
{
    PROFILE(UpdateNetwork);
    
    // Service hosts if they exist
    if (serverHost_)
        Update(serverHost_);
    if (clientHost_)
        Update(clientHost_);
    
    // Update peers and purge those that are disconnected
    for (Vector<SharedPtr<Peer> >::Iterator i = peers_.Begin(); i != peers_.End();)
    {
        (*i)->Update();
        
        if ((*i)->GetConnectionState() == CS_DISCONNECTED)
            i = peers_.Erase(i);
        else
            ++i;
    }
}

bool Network::StartServer(unsigned short port)
{
    StopServer();
    
    ENetAddress server;
    server.host = ENET_HOST_ANY;
    server.port = port;
    
    serverHost_ = enet_host_create(&server, serverMaxConnections_, numChannels_, dataInBps_, dataOutBps_);
    if (serverHost_)
        enet_host_compress_with_range_coder(serverHost_);
    else
    {
        LOGERROR("Failed to start server on port " + String(port));
        return false;
    }
    

    LOGINFO("Started server on port " + String(port));
    return true;
}

Peer* Network::Connect(const String& address, unsigned short port)
{
    // Create client host if one did not exist already
    if (!clientHost_)
    {
        clientHost_ = enet_host_create(0, clientMaxConnections_, numChannels_, dataInBps_, dataOutBps_);
        if (clientHost_)
            enet_host_compress_with_range_coder(clientHost_);
        else
        {
            LOGERROR("Failed to create client host");
            return 0;
        }
    }
    
    // Attempt to connect
    ENetAddress server;
    enet_address_set_host(&server, address.CString());
    server.port = port;
    ENetPeer* enetPeer = enet_host_connect(clientHost_, &server, numChannels_, 0);
    if (!enetPeer)
    {
        LOGERROR("No available network connections");
        return 0;
    }
    
    // Create a Peer instance for the server
    SharedPtr<Peer> newPeer(new Peer(context_, enetPeer, PEER_SERVER));
    enetPeer->data = newPeer.Ptr();
    peers_.Push(newPeer);
    
    LOGINFO("Connecting to " + address + ":" + String(port));
    return newPeer;
}

void Network::Broadcast(const void* data, unsigned size, unsigned char channel, bool reliable, bool inOrder)
{
    if (!serverHost_)
    {
        LOGERROR("No server running, can not broadcast");
        return;
    }
    
    if (!data || !size)
        return;
    
    ENetPacket* enetPacket = enet_packet_create(data, size, reliable ? ENET_PACKET_FLAG_RELIABLE : (inOrder ? 0 :
        ENET_PACKET_FLAG_UNSEQUENCED));
    
    enet_host_broadcast(serverHost_, channel, enetPacket);
}


void Network::Broadcast(const VectorBuffer& packet, unsigned char channel, bool reliable, bool inOrder)
{
    if (!serverHost_)
    {
        LOGERROR("No server running, can not broadcast");
        return;
    }
    
    if (!packet.GetSize())
        return;
    
    ENetPacket* enetPacket = enet_packet_create(packet.GetData(), packet.GetSize(), reliable ? ENET_PACKET_FLAG_RELIABLE :
        (inOrder ? 0 : ENET_PACKET_FLAG_UNSEQUENCED));
    
    enet_host_broadcast(serverHost_, channel, enetPacket);
}

void Network::StopServer()
{
    if (serverHost_)
    {
        // Disconnect all peers created through the server host
        for (Vector<SharedPtr<Peer> >::Iterator i = peers_.Begin(); i != peers_.End(); ++i)
        {
            if ((*i)->GetPeerType() == PEER_CLIENT)
                (*i)->Disconnect();
        }
        
        // Update once more, so that disconnect packet (maybe) goes to clients
        Update(serverHost_);
        
        // Then perform forcible disconnection
        for (Vector<SharedPtr<Peer> >::Iterator i = peers_.Begin(); i != peers_.End(); ++i)
        {
            if ((*i)->GetPeerType() == PEER_CLIENT)
                (*i)->OnDisconnect();
        }
        
        enet_host_destroy(serverHost_);
        serverHost_ = 0;
        
        LOGINFO("Stopped server");
    }
}

void Network::StopClient()
{
    if (clientHost_)
    {
        // Disconnect all peers created through the client host
        for (Vector<SharedPtr<Peer> >::Iterator i = peers_.Begin(); i != peers_.End(); ++i)
        {
            if ((*i)->GetPeerType() == PEER_SERVER)
                (*i)->Disconnect();
        }
        
        // Update once more, so that disconnect packet (maybe) goes to server
        Update(clientHost_);
        
        // Then perform forcible disconnection
        for (Vector<SharedPtr<Peer> >::Iterator i = peers_.Begin(); i != peers_.End(); ++i)
        {
            if ((*i)->GetPeerType() == PEER_SERVER)
                (*i)->OnDisconnect();
        }
        
        enet_host_destroy(clientHost_);
        clientHost_ = 0;
        
        LOGINFO("Stopped client");
    }
}

Peer* Network::GetPeer(unsigned index) const
{
    return index < peers_.Size() ? peers_[index] : (Peer*)0;
}

Peer* Network::GetServerPeer() const
{
    // Just return the first server peer
    for (Vector<SharedPtr<Peer> >::ConstIterator i = peers_.Begin(); i != peers_.End(); ++i)
    {
        if ((*i)->GetPeerType() == PEER_SERVER)
            return *i;
    }
    
    return 0;
}

void Network::Update(ENetHost* enetHost)
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
                SharedPtr<Peer> newPeer(new Peer(context_, enetPeer, PEER_CLIENT));
                enetPeer->data = newPeer.Ptr();
                peers_.Push(newPeer);
                newPeer->OnConnect();
            }
            else
                peer->OnConnect();
            break;
            
        case ENET_EVENT_TYPE_RECEIVE:
            if (peer)
            {
                // queue the packet
                QueuedPacket newPacket;
                newPacket.packet_ = enetEvent.packet;
                newPacket.channel_ = enetEvent.channelID;
                peer->packets_[enetEvent.channelID].Push(newPacket);
            }
            else
                enet_packet_destroy(enetEvent.packet);
            break;
            
        case ENET_EVENT_TYPE_DISCONNECT:
            if (peer)
            {
                peer->OnDisconnect();
                enetPeer->data = 0;
            }
            break;
        }
    }
}

void Network::HandleBeginFrame(StringHash eventType, VariantMap& eventData)
{
    Update();
}
