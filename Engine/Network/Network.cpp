//
// Copyright (c) 2008-2013 the Urho3D project.
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
#include "FileSystem.h"
#include "Log.h"
#include "MemoryBuffer.h"
#include "Network.h"
#include "NetworkEvents.h"
#include "NetworkPriority.h"
#include "Profiler.h"
#include "Protocol.h"
#include "Scene.h"
#include "StringUtils.h"

#include <kNet.h>

#include "DebugNew.h"

namespace Urho3D
{

static const int DEFAULT_UPDATE_FPS = 30;

OBJECTTYPESTATIC(Network);

Network::Network(Context* context) :
    Object(context),
    updateFps_(DEFAULT_UPDATE_FPS),
    updateInterval_(1.0f / (float)DEFAULT_UPDATE_FPS),
    updateAcc_(0.0f)
{
    network_ = new kNet::Network();
    
    // Register Network library object factories
    RegisterNetworkLibrary(context_);
    
    SubscribeToEvent(E_BEGINFRAME, HANDLER(Network, HandleBeginFrame));
    SubscribeToEvent(E_RENDERUPDATE, HANDLER(Network, HandleRenderUpdate));
}

Network::~Network()
{
    // If server connection exists, disconnect, but do not send an event because we are shutting down
    Disconnect(100);
    serverConnection_.Reset();
    
    clientConnections_.Clear();
    
    delete network_;
    network_ = 0;
}

void Network::HandleMessage(kNet::MessageConnection *source, kNet::packet_id_t packetId, kNet::message_id_t msgId, const char *data, size_t numBytes)
{
    // Only process messages from known sources
    Connection* connection = GetConnection(source);
    if (connection)
    {
        MemoryBuffer msg(data, numBytes);
        if (connection->ProcessMessage(msgId, msg))
            return;
        
        // If message was not handled internally, forward as an event
        using namespace NetworkMessage;
        
        VariantMap eventData;
        eventData[P_CONNECTION] = (void*)connection;
        eventData[P_MESSAGEID] = (int)msgId;
        eventData[P_DATA].SetBuffer(msg.GetData(), msg.GetSize());
        connection->SendEvent(E_NETWORKMESSAGE, eventData);
    }
    else
        LOGWARNING("Discarding message from unknown MessageConnection " + ToString((void*)source));
}

u32 Network::ComputeContentID(kNet::message_id_t msgId, const char* data, size_t numBytes)
{
    switch (msgId)
    {
    case MSG_CONTROLS:
        // Return fixed content ID for controls
        return CONTROLS_CONTENT_ID;
        
    case MSG_NODELATESTDATA:
    case MSG_COMPONENTLATESTDATA:
        {
            // Return the node or component ID, which is first in the message
            MemoryBuffer msg(data, numBytes);
            return msg.ReadNetID();
        }
        
    default:
        // By default return no content ID
        return 0;
    }
}

void Network::NewConnectionEstablished(kNet::MessageConnection* connection)
{
    connection->RegisterInboundMessageHandler(this);
    
    // Create a new client connection corresponding to this MessageConnection
    SharedPtr<Connection> newConnection(new Connection(context_, true, kNet::SharedPtr<kNet::MessageConnection>(connection)));
    clientConnections_[connection] = newConnection;
    LOGINFO("Client " + newConnection->ToString() + " connected");
    
    using namespace ClientConnected;
    
    VariantMap eventData;
    eventData[P_CONNECTION] = (void*)newConnection;
    newConnection->SendEvent(E_CLIENTCONNECTED, eventData);
}

void Network::ClientDisconnected(kNet::MessageConnection* connection)
{
    connection->Disconnect(0);
    
    // Remove the client connection that corresponds to this MessageConnection
    HashMap<kNet::MessageConnection*, SharedPtr<Connection> >::Iterator i = clientConnections_.Find(connection);
    if (i != clientConnections_.End())
    {
        Connection* connection = i->second_;
        LOGINFO("Client " + connection->ToString() + " disconnected");
        
        using namespace ClientDisconnected;
        
        VariantMap eventData;
        eventData[P_CONNECTION] = (void*)connection;
        connection->SendEvent(E_CLIENTDISCONNECTED, eventData);
        
        clientConnections_.Erase(i);
    }
}

bool Network::Connect(const String& address, unsigned short port, Scene* scene, const VariantMap& identity)
{
    PROFILE(Connect);
    
    // If a previous connection already exists, disconnect it and wait for some time for the connection to terminate
    if (serverConnection_)
    {
        serverConnection_->Disconnect(100);
        OnServerDisconnected();
    }
    
    kNet::SharedPtr<kNet::MessageConnection> connection = network_->Connect(address.CString(), port, kNet::SocketOverUDP, this);
    if (connection)
    {
        LOGINFO("Connecting to server " + address + ":" + String(port));
        serverConnection_ = new Connection(context_, false, connection);
        serverConnection_->SetScene(scene);
        serverConnection_->SetIdentity(identity);
        serverConnection_->SetConnectPending(true);
        return true;
    }
    else
    {
        LOGERROR("Failed to connect to server " + address + ":" + String(port));
        SendEvent(E_CONNECTFAILED);
        return false;
    }
}

void Network::Disconnect(int waitMSec)
{
    if (!serverConnection_)
        return;
    
    PROFILE(Disconnect);
    serverConnection_->Disconnect(waitMSec);
}

bool Network::StartServer(unsigned short port)
{
    if (IsServerRunning())
        return true;
    
    PROFILE(StartServer);
    
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
    if (!IsServerRunning())
        return;
    
    PROFILE(StopServer);
    
    clientConnections_.Clear();
    network_->StopServer();
    LOGINFO("Stopped server");
}

void Network::BroadcastMessage(int msgID, bool reliable, bool inOrder, const VectorBuffer& msg, unsigned contentID)
{
    BroadcastMessage(msgID, reliable, inOrder, msg.GetData(), msg.GetSize(), contentID);
}

void Network::BroadcastMessage(int msgID, bool reliable, bool inOrder, const unsigned char* data, unsigned numBytes,
    unsigned contentID)
{
   // Make sure not to use kNet internal message ID's
    if (msgID <= 0x4 || msgID >= 0x3ffffffe)
    {
        LOGERROR("Can not send message with reserved ID");
        return;
    }
    
    kNet::NetworkServer* server = network_->GetServer();
    if (server)
        server->BroadcastMessage(msgID, reliable, inOrder, 0, contentID, (const char*)data, numBytes);
    else
        LOGERROR("Server not running, can not broadcast messages");
}

void Network::BroadcastRemoteEvent(StringHash eventType, bool inOrder, const VariantMap& eventData)
{
    for (HashMap<kNet::MessageConnection*, SharedPtr<Connection> >::Iterator i = clientConnections_.Begin();
        i != clientConnections_.End(); ++i)
        i->second_->SendRemoteEvent(eventType, inOrder, eventData);
}

void Network::BroadcastRemoteEvent(Scene* scene, StringHash eventType, bool inOrder, const VariantMap& eventData)
{
    for (HashMap<kNet::MessageConnection*, SharedPtr<Connection> >::Iterator i = clientConnections_.Begin();
        i != clientConnections_.End(); ++i)
    {
        if (i->second_->GetScene() == scene)
            i->second_->SendRemoteEvent(eventType, inOrder, eventData);
    }
}

void Network::BroadcastRemoteEvent(Node* node, StringHash eventType, bool inOrder, const VariantMap& eventData)
{
    if (!node)
    {
        LOGERROR("Null sender node for remote node event");
        return;
    }
    if (node->GetID() >= FIRST_LOCAL_ID)
    {
        LOGERROR("Sender node has a local ID, can not send remote node event");
        return;
    }
    
    Scene* scene = node->GetScene();
    for (HashMap<kNet::MessageConnection*, SharedPtr<Connection> >::Iterator i = clientConnections_.Begin();
        i != clientConnections_.End(); ++i)
    {
        if (i->second_->GetScene() == scene)
            i->second_->SendRemoteEvent(node, eventType, inOrder, eventData);
    }
}

void Network::SetUpdateFps(int fps)
{
    updateFps_ = Max(fps, 1);
    updateInterval_ = 1.0f / (float)updateFps_;
    updateAcc_ = 0.0f;
}

void Network::RegisterRemoteEvent(StringHash eventType)
{
    allowedRemoteEvents_.Insert(eventType);
}

void Network::UnregisterRemoteEvent(StringHash eventType)
{
    allowedRemoteEvents_.Erase(eventType);
}

void Network::UnregisterAllRemoteEvents()
{
    allowedRemoteEvents_.Clear();
}

void Network::SetPackageCacheDir(const String& path)
{
    packageCacheDir_ = AddTrailingSlash(path);
}

Connection* Network::GetConnection(kNet::MessageConnection* connection) const
{
    if (serverConnection_ && serverConnection_->GetMessageConnection() == connection)
        return serverConnection_;
    else
    {
        HashMap<kNet::MessageConnection*, SharedPtr<Connection> >::ConstIterator i = clientConnections_.Find(connection);
        if (i != clientConnections_.End())
            return i->second_;
        else
            return 0;
    }
}

Connection* Network::GetServerConnection() const
{
    return serverConnection_;
}

Vector<SharedPtr<Connection> > Network::GetClientConnections() const
{
    Vector<SharedPtr<Connection> > ret;
    for (HashMap<kNet::MessageConnection*, SharedPtr<Connection> >::ConstIterator i = clientConnections_.Begin();
        i != clientConnections_.End(); ++i)
        ret.Push(i->second_);
    
    return ret;
}

bool Network::IsServerRunning() const
{
    return network_->GetServer();
}

bool Network::CheckRemoteEvent(StringHash eventType) const
{
    return allowedRemoteEvents_.Empty() || allowedRemoteEvents_.Contains(eventType);
}

void Network::Update(float timeStep)
{
    PROFILE(UpdateNetwork);
    
    // Process server connection if it exists
    if (serverConnection_)
    {
        kNet::MessageConnection* connection = serverConnection_->GetMessageConnection();
        
        // Receive new messages
        connection->Process();
        
        // Process latest data messages waiting for the correct nodes or components to be created
        serverConnection_->ProcessPendingLatestData();
        
        // Check for state transitions
        kNet::ConnectionState state = connection->GetConnectionState();
        if (serverConnection_->IsConnectPending() && state == kNet::ConnectionOK)
            OnServerConnected();
        else if (state == kNet::ConnectionPeerClosed)
            serverConnection_->Disconnect();
        else if (state == kNet::ConnectionClosed)
            OnServerDisconnected();
    }
    
    // Process the network server if started
    kNet::SharedPtr<kNet::NetworkServer> server = network_->GetServer();
    if (server)
        server->Process();
}

void Network::PostUpdate(float timeStep)
{
    PROFILE(PostUpdateNetwork);
    
    // Check if periodic update should happen now
    updateAcc_ += timeStep;
    bool updateNow = updateAcc_ >= updateInterval_;
    
    if (updateNow)
    {
        // Notify of the impending update to allow for example updated client controls to be set
        SendEvent(E_NETWORKUPDATE);
        updateAcc_ = fmodf(updateAcc_, updateInterval_);
        
        if (IsServerRunning())
        {
            // Collect and prepare all networked scenes
            {
                PROFILE(PrepareServerUpdate);
                
                networkScenes_.Clear();
                for (HashMap<kNet::MessageConnection*, SharedPtr<Connection> >::Iterator i = clientConnections_.Begin();
                    i != clientConnections_.End(); ++i)
                {
                    Scene* scene = i->second_->GetScene();
                    if (scene)
                        networkScenes_.Insert(scene);
                }
                
                for (HashSet<Scene*>::ConstIterator i = networkScenes_.Begin(); i != networkScenes_.End(); ++i)
                    (*i)->PrepareNetworkUpdate();
            }
            
            {
                PROFILE(SendServerUpdate);
                
                // Then send server updates for each client connection
                for (HashMap<kNet::MessageConnection*, SharedPtr<Connection> >::Iterator i = clientConnections_.Begin();
                    i != clientConnections_.End(); ++i)
                {
                    i->second_->SendServerUpdate();
                    i->second_->SendRemoteEvents();
                    i->second_->SendPackages();
                }
            }
        }
        
        if (serverConnection_)
        {
            // Send the client update
            serverConnection_->SendClientUpdate();
            serverConnection_->SendRemoteEvents();
        }
        
        // Notify that the update was sent
        SendEvent(E_NETWORKUPDATESENT);
    }
}

void Network::HandleBeginFrame(StringHash eventType, VariantMap& eventData)
{
    using namespace BeginFrame;
    
    Update(eventData[P_TIMESTEP].GetFloat());
}

void Network::HandleRenderUpdate(StringHash eventType, VariantMap& eventData)
{
    using namespace RenderUpdate;
    
    PostUpdate(eventData[P_TIMESTEP].GetFloat());
}

void Network::OnServerConnected()
{
    serverConnection_->SetConnectPending(false);
    
    LOGINFO("Connected to server");
    
    // Send the identity map now
    VectorBuffer msg;
    msg.WriteVariantMap(serverConnection_->GetIdentity());
    serverConnection_->SendMessage(MSG_IDENTITY, true, true, msg);
    
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
        SendEvent(E_CONNECTFAILED);
    }
    
    serverConnection_.Reset();
}

void RegisterNetworkLibrary(Context* context)
{
    NetworkPriority::RegisterObject(context);
}

}
