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
#include "MemoryBuffer.h"
#include "Network.h"
#include "NetworkEvents.h"
#include "Protocol.h"
#include "StringUtils.h"

#include <kNet.h>

#include "DebugNew.h"

OBJECTTYPESTATIC(Network);

Network::Network(Context* context) :
    Object(context)
{
    network_ = new kNet::Network();
    
    SubscribeToEvent(E_BEGINFRAME, HANDLER(Network, HandleBeginFrame));
}

Network::~Network()
{
    clientConnections_.Clear();
    
    delete network_;
    network_ = 0;
}

void Network::HandleMessage(kNet::MessageConnection* source, kNet::message_id_t id, const char *data, size_t numBytes)
{
    // Only process messages from known sources
    Connection* connection = GetConnection(source);
    if (connection)
    {
        bool handled = false;
        if (connection == serverConnection_)
            handled = OnServerMessage(connection, id, data, numBytes);
        else
            handled = OnClientMessage(connection, id, data, numBytes);
        
        // If message was not handled internally, forward as an event
        if (!handled)
        {
            using namespace NetworkMessage;
            
            VariantMap eventData;
            eventData[P_CONNECTION] = (void*)connection;
            eventData[P_MESSAGEID] = (int)id;
            eventData[P_DATA] = PODVector<unsigned char>((const unsigned char*)data, numBytes);
            connection->SendEvent(E_NETWORKMESSAGE, eventData);
        }
    }
    else
        LOGWARNING("Discarding message from unknown MessageConnection " + ToString((void*)source));
}

void Network::NewConnectionEstablished(kNet::MessageConnection* connection)
{
    connection->RegisterInboundMessageHandler(this);
    
    // Create a new client connection corresponding to this MessageConnection
    Connection* newConnection = new Connection(context_, kNet::SharedPtr<kNet::MessageConnection>(connection));
    clientConnections_[connection] = newConnection;
    LOGINFO("Client " + newConnection->ToString() + " connected");
    
    using namespace ClientConnected;
    
    VariantMap eventData;
    eventData[P_CONNECTION] = (void*)newConnection;
    SendEvent(E_CLIENTCONNECTED, eventData);
}

void Network::ClientDisconnected(kNet::MessageConnection* connection)
{
    connection->Disconnect(0);
    
    // Remove the client connection that corresponds to this MessageConnection
    Map<kNet::MessageConnection*, SharedPtr<Connection> >::Iterator i = clientConnections_.Find(connection);
    if (i != clientConnections_.End())
    {
        LOGINFO("Client " + i->second_->ToString() + " disconnected");
        
        using namespace ClientDisconnected;
        
        VariantMap eventData;
        eventData[P_CONNECTION] = (void*)i->second_;
        SendEvent(E_CLIENTDISCONNECTED, eventData);
        
        clientConnections_.Erase(i);
    }
}

bool Network::Connect(const String& address, unsigned short port)
{
    // If connection already exists, disconnect it and wait for some time for the connection to terminate
    if (serverConnection_)
    {
        serverConnection_->Disconnect(100);
        OnServerDisconnected();
    }
    
    kNet::SharedPtr<kNet::MessageConnection> connection = network_->Connect(address.CString(), port, kNet::SocketOverUDP, this);
    if (connection)
    {
        LOGINFO("Connecting to server " + address + ":" + String(port));
        serverConnection_ = new Connection(context_, connection);
        serverConnection_->connectPending_ = true;
        return true;
    }
    else
    {
        LOGERROR("Failed to connect to server " + address + ":" + String(port));
        SendEvent(E_SERVERCONNECTFAILED);
        return false;
    }
}

void Network::Disconnect(int waitMSec)
{
    if (serverConnection_)
        serverConnection_->Disconnect(waitMSec);
}

bool Network::StartServer(unsigned short port)
{
    if (IsServerRunning())
        return true;
    
    /// \todo Investigate why server fails to restart after stopping when false is specified for reuse
    if (network_->StartServer(port, kNet::SocketOverUDP, this, true) != 0)
    {
        LOGINFO("Started server on port " + String(port));
        return true;
    }
    else
    {
        LOGERROR("Failed to start server on port " + String(port));
        return false;
    }
}

void Network::StopServer()
{
    if (IsServerRunning())
    {
        clientConnections_.Clear();
        network_->StopServer();
        LOGINFO("Stopped server");
    }
}

Connection* Network::GetConnection(kNet::MessageConnection* connection) const
{
    Map<kNet::MessageConnection*, SharedPtr<Connection> >::ConstIterator i = clientConnections_.Find(connection);
    if (i != clientConnections_.End())
        return i->second_;
    else if (serverConnection_ && serverConnection_->GetMessageConnection() == connection)
        return serverConnection_;
    else
        return 0;
}

Connection* Network::GetServerConnection() const
{
    return serverConnection_;
}

bool Network::IsServerRunning() const
{
    return network_->GetServer();
}

void Network::Update()
{
    // Process server connection if it exists
    if (serverConnection_)
    {
        kNet::MessageConnection* connection = serverConnection_->GetMessageConnection();
        connection->Process();
        
        // Check for state transitions
        kNet::ConnectionState state = connection->GetConnectionState();
        if (serverConnection_->IsConnectPending() && state == kNet::ConnectionOK)
            OnServerConnected();
        else if (state == kNet::ConnectionPeerClosed)
            serverConnection_->Disconnect();
        else if (state == kNet::ConnectionClosed)
            OnServerDisconnected();
    }
    
    // Process client connections if the server has been started
    kNet::NetworkServer* server = network_->GetServer();
    if (server)
        server->Process();
}

void Network::OnServerConnected()
{
    serverConnection_->connectPending_ = false;
    LOGINFO("Connected to server");
    SendEvent(E_SERVERCONNECTED);
}

void Network::OnServerDisconnected()
{
    // Differentiate between failed connection, and disconnection
    bool failedConnect = serverConnection_ && serverConnection_->IsConnectPending();
    if (!failedConnect)
    {
        LOGINFO("Disconnected from server");
        SendEvent(E_SERVERDISCONNECTED);
    }
    else
    {
        LOGERROR("Failed to connect to server");
        SendEvent(E_SERVERCONNECTFAILED);
    }
    
    serverConnection_.Reset();
}

bool Network::OnServerMessage(Connection* connection, kNet::message_id_t id, const char *data, size_t numBytes)
{
    return false;
}

bool Network::OnClientMessage(Connection* connection, kNet::message_id_t id, const char *data, size_t numBytes)
{
    switch (id)
    {
    case MSG_IDENTITY:
        {
            using namespace ClientIdentity;
            
            MemoryBuffer msg(data, numBytes);
            VariantMap eventData = msg.ReadVariantMap();
            eventData[P_CONNECTION] = (void*)connection;
            eventData[P_ALLOW] = true;
            connection->SendEvent(E_CLIENTIDENTITY, eventData);
            
            // Check if connection was denied
            if (!eventData[P_ALLOW].GetBool())
                connection->Disconnect();
        }
        return true;
    }
    
    return false;
}

void Network::HandleBeginFrame(StringHash eventType, VariantMap& eventData)
{
    Update();
}
