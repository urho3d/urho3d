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

#ifndef NETWORK_NETWORK_H
#define NETWORK_NETWORK_H

#include "EventListener.h"
#include "SharedPtr.h"
#include "VectorBuffer.h"

class Peer;

struct _ENetHost;

typedef _ENetHost ENetHost;

//! Sends and receives packets using ENet
class Network : public RefCounted, public EventListener
{
public:
    //! Construct and initialize ENet
    Network();
    //! Destruct. Deinitialize ENet
    ~Network();
    
    //! Set maximum connections on the server
    void setServerMaxConnections(int server);
    //! Set maximum connections on the client
    void setClientMaxConnections(int client);
    //! Set number of packet channels to use. Each has its own packet ordering
    void setNumChannels(unsigned char channels);
    //! Set incoming and outgoing data rate
    void setDataRate(int dataInBps, int dataOutBps);
    //! Set whether new peers should use events to notify of received packets. Default is false
    void setSendPacketEventsDefault(bool enable);
    //! Service incoming and outgoing packets
    void update();
    //! Start server on a port
    bool startServer(unsigned short port);
    //! Connect to a server
    Peer* connect(const std::string& address, unsigned short port);
    //! Broadcast a packet to all connected peers
    void broadcast(const VectorBuffer& packet, unsigned char channel, bool reliable, bool inOrder = true);
    //! Broadcast a packet to all connected peers
    void broadcast(const void* data, unsigned size, unsigned char channel, bool reliable, bool inOrder = true);
    //! Stop server and close all connections
    void stopServer();
    //! Stop server and close all connections
    void stopClient();
    
    //! Return whether server has been started
    bool isServer() const { return mServerHost != 0; }
    //! Return whether client has been started (is automatically started when a connection attempt is made)
    bool isClient() const { return mClientHost != 0; }
    //! Return number of networking peers
    unsigned getNumPeers() const { return mPeers.size(); }
    //! Return all networking peers
    const std::vector<SharedPtr<Peer> >& getPeers() const { return mPeers; }
    //! Return networking peer by index
    Peer* getPeer(unsigned index) const;
    //! Return the first server peer
    Peer* getServerPeer() const;
    //! Return maximum server connections
    int getServerMaxConnections() const { return mServerMaxConnections; }
    //! Return maximum client connections
    int getClientMaxConenctions() const { return mClientMaxConnections; }
    //! Return number of packet channels
    int getNumChannels() const { return mNumChannels; }
    //! Return incoming data rate
    int getDataRateIn() const { return mDataInBps; }
    //! Return outgoing data rate
    int getDataRateOut() const { return mDataOutBps; }
    //! Return whether new peers should notify of received packets with events
    bool getSendPacketEventsDefault() const { return mSendPacketEventsDefault; }
    
private:
    //! Update a specific network host
    void update(ENetHost* enetHost);
    
    //! Server host
    ENetHost* mServerHost;
    //! Client host
    ENetHost* mClientHost;
    //! Peers
    std::vector<SharedPtr<Peer> > mPeers;
    //! Maximum server connections
    int mServerMaxConnections;
    //! Maximum client connections
    int mClientMaxConnections;
    //! Number of packet channels to use
    unsigned char mNumChannels;
    //! Incoming data rate
    int mDataInBps;
    //! Outgoing data rate
    int mDataOutBps;
    //! Set new peers to send packet events flag
    bool mSendPacketEventsDefault;
};

#endif // NETWORK_NETWORK_H
