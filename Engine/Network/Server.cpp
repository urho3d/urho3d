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
#include "Connection.h"
#include "File.h"
#include "Log.h"
#include "Network.h"
#include "NetworkEvents.h"
#include "PackageFile.h"
#include "Profiler.h"
#include "Protocol.h"
#include "ProtocolEvents.h"
#include "Scene.h"
#include "Server.h"
#include "StringUtils.h"

#include <set>

#include "DebugNew.h"

// Timeout for closing transferred package files, in milliseconds
static const int FILE_TIMEOUT = 15 * 1000;

OBJECTTYPESTATIC(Server);

Server::Server(Context* context) :
    Object(context),
    netFps_(30),
    timeAcc_(0),
    frameNumber_(1),
    maxSceneRevisions_(100),
    stayRelevantTime_(30)
{
    SubscribeToEvent(E_PEERCONNECTED, HANDLER(Server, HandlePeerConnected));
    SubscribeToEvent(E_PEERDISCONNECTED, HANDLER(Server, HandlePeerDisconnected));
}

Server::~Server()
{
}

void Server::SetNetFps(int fps)
{
    netFps_ = Max(fps, 1);
}

void Server::SetMaxSceneRevisions(int revisions)
{
    maxSceneRevisions_ = Max(revisions, 3);
}

void Server::SetStayRelevantTime(int time)
{
    stayRelevantTime_ = Max(time, 1);
}

void Server::AddScene(Scene* scene)
{
    if (!scene)
        return;
    
    if (HasScene(scene))
    {
        LOGWARNING("Scene " + scene->GetName() + " already added to server");
        return;
    }
    
    scene->SetNetworkMode(NM_SERVER);
    scenes_.push_back(SharedPtr<Scene>(scene));
}

void Server::RemoveScene(Scene* scene)
{
    if (!scene)
        return;
    
    for (unsigned i = 0; i < scenes_.size(); ++i)
    {
        if (scenes_[i] == scene)
        {
            VectorBuffer packet;
            packet.WriteUByte(MSG_JOINREPLY);
            packet.WriteBool(false);
            packet.WriteString("The scene is shutting down");
            
            // If any clients are connected to this scene, they must leave forcibly
            for (unsigned j = 0; j < connections_.size(); ++j)
            {
                Connection* connection = connections_[j];
                if (connection->GetScene() == scene)
                {
                    connection->SendReliable(packet);
                    connection->LeftScene();
                }
            }
            
            // Remove the network mode
            scene->SetNetworkMode(NM_NONETWORK);
            scenes_.erase(scenes_.begin() + i);
            return;
        }
    }
    
    LOGWARNING("Scene " + scene->GetName() + " not found on server");
}

bool Server::Start(unsigned short port)
{
    timeAcc_ = 0.0f;
    frameNumber_ = 1;
    return GetSubsystem<Network>()->StartServer(port);
}

void Server::Stop()
{
    GetSubsystem<Network>()->StopServer();
}

void Server::Update(float timeStep)
{
    PROFILE(UpdateServer);
    
    // Process incoming packets from connections (assume that Engine has updated Network, so we do not do that here)
    for (unsigned i = 0; i < connections_.size(); ++i)
        HandlePackets(connections_[i]);
    
    // Update scenes / send update if enough time passed
    float netPeriod = 1.0f / netFps_;
    timeAcc_ += timeStep;
    if (timeAcc_ >= netPeriod)
    {
        // Update simulation of scene(s)
        for (unsigned i = 0; i < scenes_.size(); ++i)
            scenes_[i]->Update(netPeriod);
        
        // If multiple updates have accumulated because of a slow frame, send just one
        while (timeAcc_ >= netPeriod)
            timeAcc_ -= netPeriod;
        ++frameNumber_;
        
        // We have a policy that framenumber 0 means "frame never received", so loop back to 1
        if (!frameNumber_)
            ++frameNumber_;
        
        // Send update for each connection
        for (unsigned i = 0; i < connections_.size(); ++i)
            SendServerUpdate(connections_[i]);
    }
    
    // Remove disconnected clients
    for (std::vector<SharedPtr<Connection> >::iterator i = connections_.begin(); i != connections_.end();)
    {
        if (!(*i)->IsConnected())
            i = connections_.erase(i);
        else
            ++i;
    }
    
    // Close file transfers that have been unused for some time
    for (std::map<StringHash, ServerFileTransfer>::iterator i = fileTransfers_.begin(); i != fileTransfers_.end();)
    {
        std::map<StringHash, ServerFileTransfer>::iterator current = i++;
        if (current->second.closeTimer_.GetMSec(false) > FILE_TIMEOUT)
            fileTransfers_.erase(current);
    }
}

bool Server::SetClientScene(Connection* connection, Scene* scene)
{
    // Check that the scene is under server control
    if (!HasScene(scene))
        return false;
    
    connection->SetScene(scene);
    SendSceneInfo(connection);
    
    return true;
}

bool Server::IsRunning() const
{
    return GetSubsystem<Network>()->IsServer();
}

bool Server::HasScene(Scene* scene) const
{
    for (unsigned i = 0; i < scenes_.size(); ++i)
    {
        if (scenes_[i] == scene)
            return true;
    }
    
    return false;
}

unsigned Server::GetNumUsersInScene(Scene* scene) const
{
    unsigned users = 0;
    
    for (unsigned i = 0; i < connections_.size(); ++i)
    {
        if (connections_[i]->GetScene() == scene)
            ++users;
    }
    
    return users;
}

void Server::HandlePackets(Connection* connection)
{
    VectorBuffer packet;
    
    // Process reliable packets first, then unreliable
    while (connection->ReceiveReliable(packet))
    {
        if (!HandleReliablePacket(connection, packet))
            return;
    }
    while (connection->ReceiveUnreliable(packet))
    {
        if (!HandleClientUpdate(connection, packet))
            return;
    }
}

void Server::HandlePeerConnected(StringHash eventType, VariantMap& eventData)
{
    using namespace PeerConnected;
    
    Peer* peer = static_cast<Peer*>(eventData[P_PEER].GetPtr());
    if (peer->GetPeerType() != PEER_CLIENT)
        return;
    
    // Create a new connection, assign a challenge, then send the challenge message
    SharedPtr<Connection> connection(new Connection(context_, peer));
    connections_.push_back(connection);
    
    unsigned challenge = GenerateChallenge();
    connection->SetChallenge(challenge);
    
    VectorBuffer packet;
    packet.WriteUByte(MSG_CHALLENGE);
    packet.WriteUInt(challenge);
    connection->SendReliable(packet);
}

void Server::HandlePeerDisconnected(StringHash eventType, VariantMap& eventData)
{
    using namespace PeerDisconnected;
    
    Peer* peerPtr = static_cast<Peer*>(eventData[P_PEER].GetPtr());
    if (peerPtr->GetPeerType() != PEER_CLIENT)
        return;
    
    for (unsigned i = 0; i < connections_.size(); ++i)
    {
        Connection* connection = connections_[i];
        if (connection->GetPeer() == peerPtr)
        {
            // Remove if was in a scene
            connection->LeftScene();
            return;
        }
    }
}

bool Server::HandleReliablePacket(Connection* connection, VectorBuffer& packet)
{
    unsigned char msgID = 0;
    
    msgID = packet.ReadUByte();
    
    switch (msgID)
    {
    case MSG_LOGIN:
        if (!HandleLogin(connection, packet))
            return false;
        else
            break;
        
    case MSG_REQUESTFILE:
        HandleRequestFile(connection, packet);
        break;
        
    case MSG_JOINSCENE:
        HandleJoinScene(connection, packet);
        break;
        
    case MSG_FULLUPDATEACK:
        HandleFullUpdateAck(connection, packet);
        break;
        
    default:
        Disconnect(connection, false, "Unauthorized message ID " + ToString((int)msgID) + ", disconnecting client");
        return false;
    }
    
    return true;
}

bool Server::HandleLogin(Connection* connection, VectorBuffer& packet)
{
    connection->SetLoginData(packet.ReadVariantMap());
    
    // Send login event and check if any event handler denies access
    using namespace ClientLogin;
    
    // Initialize eventdata with the logindata received
    VariantMap eventData = connection->GetLoginData();
    eventData[P_CONNECTION] = (void*)connection;
    eventData[P_AUTHORIZE] = true;
    SendEvent(E_CLIENTLOGIN, eventData);
    
    if (!eventData[P_AUTHORIZE].GetBool())
    {
        Disconnect(connection, false, "Disconnecting unauthorized client");
        return false;
    }
    
    return true;
}

void Server::HandleRequestFile(Connection* connection, VectorBuffer& packet)
{
    StringHash nameHash = packet.ReadStringHash();
    int fragmentStart = packet.ReadVLE();
    int fragmentCount = packet.ReadVLE();
    
    // The only files we are willing to transmit are packages associated with scene(s)
    PackageFile* package = 0;
    for (unsigned i = 0; i < scenes_.size(); ++i)
    {
        const std::vector<SharedPtr<PackageFile> >& packages =  scenes_[i]->GetRequiredPackageFiles();
        for (unsigned j = 0; j < packages.size(); ++j)
        {
            if (packages[j]->GetNameHash() == nameHash)
            {
                package = packages[j];
                break;
            }
        }
    }
    if (!package)
    {
        LOGWARNING("Client " + connection->GetIdentity() + " requested unknown file " + ToString(nameHash));
        VectorBuffer replyPacket;
        replyPacket.WriteUByte(MSG_TRANSFERFAILED);
        replyPacket.WriteStringHash(nameHash);
        replyPacket.WriteString("File not found");
        connection->SendReliable(replyPacket);
        return;
    }
    
    // Open file if not already open
    File* file = fileTransfers_[nameHash].file_;
    if (!file)
    {
        file = fileTransfers_[nameHash].file_ = new File(context_, package->GetName());
        if (!file->IsOpen())
        {
            LOGERROR("Failed to open package file " + package->GetName() + " for file transfer");
            VectorBuffer replyPacket;
            replyPacket.WriteUByte(MSG_TRANSFERFAILED);
            replyPacket.WriteStringHash(nameHash);
            replyPacket.WriteString("Could not open file");
            connection->SendReliable(replyPacket);
            return;
        }
    }
    
    fileTransfers_[nameHash].closeTimer_.Reset();
    
    // Check that fragment range is valid
    unsigned fileSize = file->GetSize();
    int maxFragments = (fileSize - 1) / FILE_FRAGMENT_SIZE + 1;
    if (fragmentStart + fragmentCount > maxFragments)
        fragmentCount = maxFragments - fragmentStart;
    if (fragmentCount <= 0)
        return;
    
    if (!fragmentStart)
        LOGINFO("Client " + connection->GetIdentity() + " requested file " + ToString(nameHash));
    
    // Send the fragments
    unsigned fragmentOffset = fragmentStart * FILE_FRAGMENT_SIZE;
    file->Seek(fragmentOffset);
    
    for (int i = fragmentStart; i < fragmentStart + fragmentCount; ++i)
    {
        fragmentOffset = i * FILE_FRAGMENT_SIZE;
        unsigned fragmentSize = fileSize - fragmentOffset;
        if (fragmentSize > FILE_FRAGMENT_SIZE)
            fragmentSize = FILE_FRAGMENT_SIZE;
        
        VectorBuffer fragmentPacket;
        fragmentPacket.Seek(0);
        fragmentPacket.WriteUByte(MSG_TRANSFERDATA);
        fragmentPacket.WriteStringHash(nameHash);
        fragmentPacket.WriteVLE(i);
        fragmentPacket.Resize(fragmentPacket.GetPosition() + fragmentSize);
        file->Read(fragmentPacket.GetModifiableData() + fragmentPacket.GetPosition(), fragmentSize);
        connection->SendReliable(fragmentPacket);
    }
}

void Server::HandleJoinScene(Connection* connection, VectorBuffer& packet)
{
    unsigned checksum = packet.ReadUInt();
    Scene* scene = connection->GetScene();
    
    VectorBuffer replyPacket;
    replyPacket.WriteUByte(MSG_JOINREPLY);
    
    if (!scene)
    {
        replyPacket.WriteBool(false);
        replyPacket.WriteString("No scene");
        LOGINFO("Client " + connection->GetIdentity() + " attempted to join without an assigned scene");
    }
    else if (checksum != scene->GetChecksum())
    {
        replyPacket.WriteBool(false);
        replyPacket.WriteString("Scene checksum mismatch");
        LOGINFO("Client " + connection->GetIdentity() + " checksum mismatch for scene " + scene->GetName());
    }
    else
    {
        replyPacket.WriteBool(true);
        connection->JoinedScene();
    }
    
    connection->SendReliable(replyPacket);
}

void Server::HandleFullUpdateAck(Connection* connection, VectorBuffer& packet)
{
    if (connection->GetJoinState() == JS_WAITFORACK)
    {
        unsigned short lastFrameNumber = packet.ReadUShort();
        unsigned short lastFrameAck = packet.ReadUShort();
        connection->SetFrameNumbers(lastFrameNumber, lastFrameAck);
        connection->UpdateRoundTripTime(netFps_, frameNumber_);
        connection->SetJoinState(JS_SENDDELTAS);
    }
    else
        LOGWARNING("Received unexpected full update ack from client " + connection->GetIdentity());
}

bool Server::HandleClientUpdate(Connection* connection, VectorBuffer& packet)
{
    // Disregard unreliable client updates while waiting for the initial scene ack
    if (connection->GetJoinState() != JS_SENDDELTAS)
        return true;
    
    unsigned short lastFrameNumber = packet.ReadUShort();
    unsigned short lastFrameAck = packet.ReadUShort();
    
    // Check that this packet is not older than the last received (overlap may occur when we transition
    // between a reliable full update and unreliable delta updates)
    if (!CheckFrameNumber(lastFrameNumber, connection->GetFrameNumber()))
        return true;
    
    connection->SetFrameNumbers(lastFrameNumber, lastFrameAck);
    connection->UpdateRoundTripTime(netFps_, frameNumber_);
    
    unsigned short previousEventFrameNumber = connection->GetEventFrameNumber();
    
    while (!packet.IsEof())
    {
        unsigned char msgID = packet.ReadUByte();
        // The client is only allowed to send a few specific messages in the client update
        switch (msgID)
        {
        case MSG_REMOTEEVENT:
            {
                RemoteEvent newEvent;
                newEvent.Read(packet, false);
                if (connection->CheckRemoteEventFrame(newEvent, previousEventFrameNumber))
                    newEvent.Dispatch(connection, connection->GetScene());
            }
            break;
            
        case MSG_REMOTENODEEVENT:
            {
                RemoteEvent newEvent;
                newEvent.Read(packet, true);
                if (connection->CheckRemoteEventFrame(newEvent, previousEventFrameNumber))
                    newEvent.Dispatch(connection, connection->GetScene());
            }
            break;
            
        case MSG_CONTROLS:
            {
                Controls newControls;
                newControls.buttons_ = packet.ReadUInt();
                newControls.yaw_ = packet.ReadFloat();
                newControls.pitch_ = packet.ReadFloat();
                newControls.extraData_ = packet.ReadVariantMap();
                connection->SetControls(newControls);
                connection->SetPosition(packet.ReadVector3());
                
                using namespace ClientControls;
                
                // Initialize event parameters with possible extra controls
                VariantMap eventData = newControls.extraData_;
                eventData[P_CONNECTION] = (void*)connection;
                eventData[P_FRAMENUMBER] = connection->GetFrameNumber();
                eventData[P_BUTTONS] = newControls.buttons_;
                eventData[P_YAW] = newControls.yaw_;
                eventData[P_PITCH] = newControls.pitch_;
                SendEvent(E_CLIENTCONTROLS, eventData);
                break;
            }
            
        default:
            Disconnect(connection, false, "Unauthorized message ID " + ToString((int)msgID) + ", disconnecting client");
            return false;
        }
    }
    
    return true;
}

void Server::SendSceneInfo(Connection* connection)
{
    Scene* scene = connection->GetScene();
    if (!scene)
        return;
    
    VectorBuffer packet;
    packet.WriteUByte(MSG_SCENEINFO);
    
    // Write scene name, number of users and update rate
    packet.WriteString(scene->GetName());
    packet.WriteVLE(GetNumUsersInScene(scene));
    packet.WriteInt(netFps_);
    
    // Write source file name & required packages
    const std::vector<SharedPtr<PackageFile> >& requiredPackages = scene->GetRequiredPackageFiles();
    packet.WriteString(scene->GetFileName());
    packet.WriteVLE(requiredPackages.size());
    for (unsigned i = 0; i < requiredPackages.size(); ++i)
    {
        PackageFile* package = requiredPackages[i];
        packet.WriteString(package->GetName());
        packet.WriteUInt(package->GetTotalSize());
        packet.WriteUInt(package->GetChecksum());
    }
    
    connection->SendReliable(packet);
}

void Server::SendFullUpdate(Connection* connection)
{
    PROFILE(SendFullUpdate);
    
    Scene* scene = connection->GetScene();
    if (!scene)
        return;
    
    // Clear all scene revision data so that we write a full update
    connection->ClearSceneState();
    
    VectorBuffer packet;
    packet.WriteUByte(MSG_FULLUPDATE);
    WriteNetUpdate(connection, packet);
    connection->SendReliable(packet);
    
    // All unacked remote events were sent reliably, so clear them
    connection->ClearRemoteEvents();
    connection->SetJoinState(JS_WAITFORACK);
    
    LOGDEBUG("Initial scene: " + ToString(packet.GetSize()) + " bytes");
}

void Server::SendServerUpdate(Connection* connection)
{
    PROFILE(SendServerUpdate);
    
    Scene* scene = connection->GetScene();
    JoinState state = connection->GetJoinState();
    if ((!scene) || (state < JS_SENDFULLUPDATE) || (state == JS_WAITFORACK))
        return;
    
    // Purge states and events which are older than last acked, and expired remote events
    connection->PurgeAckedSceneState();
    connection->PurgeAckedRemoteEvents(frameNumber_);
    
    // If already have too many revisions stored, fall back to the initial scene sending (reliable)
    if (connection->GetSceneState().GetRevisionCount() >= maxSceneRevisions_)
    {
        LOGWARNING("Too many scene revisions for client " + connection->GetIdentity() + ", falling back to initial scene send");
        state = JS_SENDFULLUPDATE;
    }
    
    // Send initial scene as reliable
    if (state == JS_SENDFULLUPDATE)
    {
        SendFullUpdate(connection);
        return;
    }
    
    VectorBuffer packet;
    WriteNetUpdate(connection, packet);
    connection->SendUnreliable(packet);
    
    //LOGDEBUG("Delta: " + ToString(packet.GetSize()) + " Revisions: " +
    //    ToString(connection->GetSceneState().GetRevisionCount()) + " Events: " +
    //    ToString(connection->GetUnackedRemoteEvents().size()));
}

unsigned Server::GenerateChallenge() const
{
    return (rand() & 32767) | ((rand() & 32767) << 15) | ((rand() & 32767) << 30);
}

void Server::Disconnect(Connection* connection, bool forced, const std::string& logMessage)
{
    LOGERROR(logMessage + " " + connection->GetIdentity());
    
    if (forced)
        connection->forceDisconnect();
    else
        connection->Disconnect();
    
    // Send event
    using namespace ClientDisconnected;
    
    VariantMap eventData;
    eventData[P_CONNECTION] = (void*)connection;
    SendEvent(E_CLIENTDISCONNECTED, eventData);
}

void Server::WriteNetUpdate(Connection* connection, Serializer& dest)
{
    PROFILE(WriteNetUpdate);
    
    Scene* scene = connection->GetScene();
    SceneReplicationState& sceneState = connection->GetSceneState();
    
    // Write frame numbers
    dest.WriteUShort(frameNumber_);
    dest.WriteUShort(connection->GetFrameNumber());
    
    VectorBuffer emptyBaseRevision;
    VectorBuffer propertyBuffer;
    VectorBuffer newBuffer;
    VectorBuffer removeBuffer;
    VectorBuffer updateBuffer;
    VectorBuffer newRevision;
    
    /*
    
    // Find relevant nodes for this client
    std::set<unsigned> relevantNodes;
    GetRelevantNodes(connection, relevantNodes);
    
    {
        // Go through the scene and see which nodes are new and which have been removed
        const std::map<unsigned, SharedPtr<Node> >& nodes = scene->GetAllNodes();
        std::set<unsigned> processedNodes;
        for (std::map<unsigned, SharedPtr<Node> >::const_iterator i = nodes.begin(); i != nodes.end(); ++i)
        {
            // If we reach the local node ID's, break
            if (i->first >= FIRST_LOCAL_ID)
                break;
            
            processedNodes.insert(i->first);
            
            bool relevant = relevantNodes.find(i->first) != relevantNodes.end();
            
            Node* node = i->second;
            NodeReplicationState* nodeState = sceneState.findNode(i->first);
            if (!nodeState)
            {
                // If client does not have this node and it is not relevant, skip
                if (!relevant)
                    continue;
                
                nodeState = &sceneState.nodes_[i->first];
                nodeState->Created(frameNumber_);
                nodeState->stayRelevantTime_ = stayRelevantTime_;
            }
            else
            {
                // If nodestate exists, check relevancy timer and refresh it if necessary
                if (relevant)
                    nodeState->stayRelevantTime_ = stayRelevantTime_;
                else if (nodeState->stayRelevantTime_ > 0)
                {
                    --nodeState->stayRelevantTime_;
                    relevant = true;
                }
                else
                    // If node is not relevant, and relevancy timer has expired, do not check for changes
                    continue;
                
                if (!nodeState->exists_)
                    nodeState->Created(frameNumber_);
            }
            
            // Check components of this node
            const std::vector<SharedPtr<Component> >& components = node->GetComponents();
            std::set<ShortStringHash> processedComponents;
            for (std::vector<SharedPtr<Component> >::const_iterator j = components.begin(); j != components.end(); ++j)
            {
                Component* component = *j;
                if (!component->checkSync(connection))
                    continue;
                
                ShortStringHash combinedHash = component->GetCombinedHash();
                ComponentReplicationState* componentState = nodeState->findComponent(combinedHash);
                
                if (!componentState)
                {
                    componentState = &nodeState->components_[combinedHash];
                    componentState->Created(frameNumber_);
                }
                else if (!componentState->exists_)
                    componentState->Created(frameNumber_);
                
                processedComponents.insert(combinedHash);
            }
            
            // Check components that have been removed
            for (std::map<ShortStringHash, ComponentReplicationState>::iterator j = nodeState->components_.begin();
                j != nodeState->components_.end(); ++j)
            {
                if (j->second.exists_)
                {
                    if (processedComponents.find(j->first) == processedComponents.end())
                        j->second.Removed(frameNumber_);
                }
            }
        }
        
        // Check nodes that have been removed
        for (std::map<unsigned, NodeReplicationState>::iterator i = sceneState.nodes_.begin();
            i != sceneState.nodes_.end(); ++i)
        {
            if (i->second.exists_)
            {
                if (processedNodes.find(i->first) == processedNodes.end())
                    i->second.Removed(frameNumber_);
            }
        }
    }
    
    {
        // Now go through the replication state again and build commands
        for (std::map<unsigned, NodeReplicationState>::iterator i = sceneState.nodes_.begin();
            i != sceneState.nodes_.end(); ++i)
        {
            Node* node = scene->GetNode(i->first);
            NodeReplicationState& nodeState = i->second;
            // Create
            if ((nodeState.createdFrame_) && (node))
            {
                dest.WriteUByte(MSG_CREATEENTITY);
                dest.WriteUShort(node->GetID());
                dest.WriteString(node->GetName());
                dest.WriteUByte(GetClientNetFlags(connection, node, node->GetNetFlags()));
                dest.WriteVLE(node->GetGroupFlags());
                
                // Write a full update of node properties
                newRevision.Seek(0);
                if (node->WriteNetUpdate(dest, newRevision, emptyBaseRevision, info))
                    nodeState.revisions_.Commit(frameNumber_, newRevision);
                
                // Write a full update of all components that should be synced
                const std::vector<SharedPtr<Component> >& components = node->GetComponents();
                unsigned newComponents = 0;
                newBuffer.Seek(0);
                
                for (std::vector<SharedPtr<Component> >::const_iterator j = components.begin(); j != components.end(); ++j)
                {
                    Component* component = *j;
                    if (!component->checkSync(connection))
                        continue;
                    
                    ComponentReplicationState& componentState = nodeState.components_[component->GetCombinedHash()];
                    newBuffer.WriteShortStringHash(component->GetType());
                    newBuffer.WriteString(component->GetName());
                    newBuffer.WriteUByte(GetClientNetFlags(connection, node, component->GetNetFlags()));
                    newRevision.Seek(0);
                    component->WriteNetUpdate(newBuffer, newRevision, emptyBaseRevision, info);
                    componentState.revisions_.Commit(frameNumber_, newRevision);
                    ++newComponents;
                }
                
                dest.WriteVLE(newComponents);
                // Check if any components were actually written
                if (newComponents)
                    dest.Write(newBuffer.GetData(), newBuffer.GetPosition());
            }
            // Remove
            else if (nodeState.removedFrame_)
            {
                dest.WriteUByte(MSG_REMOVEENTITY);
                dest.WriteUShort(i->first);
            }
            // Update
            else if (node)
            {
                // If node's update timer has expired (it is not relevant), do not write updates
                if (nodeState.stayRelevantTime_ <= 0)
                {
                    // However, we must be careful to see what to do when the node becomes relevant again
                    // If node has unacked property or component revisions, must forget all of them
                    if (nodeState.HasUnAcked(connection->GetFrameAck()))
                    {
                        nodeState.revisions_.clear();
                        for (std::map<ShortStringHash, ComponentReplicationState>::iterator j = nodeState.components_.begin();
                            j != nodeState.components_.end(); ++j)
                            j->second.revisions_.clear();
                    }
                    continue;
                }
                
                // Divide update types into separate buffers, then see which of them got data
                // (if there are no updates, then this node does not need to write anything into the final stream)
                unsigned newComponents = 0;
                unsigned removedComponents = 0;
                unsigned updatedComponents = 0;
                
                propertyBuffer.Seek(0);
                newBuffer.Seek(0);
                removeBuffer.Seek(0);
                updateBuffer.Seek(0);
                
                unsigned char msgID = MSG_UPDATEENTITY;
                
                // Property update
                Deserializer& baseRevision = nodeState.revisions_.GetBase();
                newRevision.Seek(0);
                if (node->WriteNetUpdate(propertyBuffer, newRevision, baseRevision, info))
                {
                    nodeState.revisions_.Commit(frameNumber_, newRevision);
                    msgID |= UPD_PROPERTIES;
                }
                
                // Component create/remove/update
                for (std::map<ShortStringHash, ComponentReplicationState>::iterator j = nodeState.components_.begin();
                    j != nodeState.components_.end(); ++j)
                {
                    Component* component = node->GetComponent(j->first.mData);
                    ComponentReplicationState& componentState = j->second;
                    // Create
                    if ((componentState.createdFrame_) && (component))
                    {
                        newBuffer.WriteShortStringHash(component->GetType());
                        newBuffer.WriteString(component->GetName());
                        newBuffer.WriteUByte(GetClientNetFlags(connection, node, component->GetNetFlags()));
                        newRevision.Seek(0);
                        component->WriteNetUpdate(newBuffer, newRevision, emptyBaseRevision, info);
                        componentState.revisions_.Commit(frameNumber_, newRevision);
                        msgID |= UPD_NEWCOMPONENTS;
                        ++newComponents;
                    }
                    // Remove
                    else if (componentState.removedFrame_)
                    {
                        msgID |= UPD_REMOVECOMPONENTS;
                        ++removedComponents;
                        removeBuffer.WriteShortStringHash(j->first);
                    }
                    // Update
                    else if (component)
                    {
                        // Prepare to rewind buffer in case component writes nothing meaningful
                        unsigned oldPos = updateBuffer.GetPosition();
                        updateBuffer.WriteShortStringHash(component->GetCombinedHash());
                        newRevision.Seek(0);
                        Deserializer& baseRevision = componentState.revisions_.GetBase();
                        if (component->WriteNetUpdate(updateBuffer, newRevision, baseRevision, info))
                        {
                            componentState.revisions_.Commit(frameNumber_, newRevision);
                            msgID |= UPD_UPDATECOMPONENTS;
                            ++updatedComponents;
                        }
                        else
                            updateBuffer.Seek(oldPos);
                    }
                }
                
                // Now write each buffer if there was some data
                if (msgID != MSG_UPDATEENTITY)
                {
                    dest.WriteUByte(msgID);
                    dest.WriteUShort(node->GetID());
                    
                    if (msgID & UPD_PROPERTIES)
                        dest.Write(propertyBuffer.GetData(), propertyBuffer.GetPosition());
                    if (msgID & UPD_NEWCOMPONENTS)
                    {
                        dest.WriteVLE(newComponents);
                        dest.Write(newBuffer.GetData(), newBuffer.GetPosition());
                    }
                    if (msgID & UPD_REMOVECOMPONENTS)
                    {
                        dest.WriteVLE(removedComponents);
                        dest.Write(removeBuffer.GetData(), removeBuffer.GetPosition());
                    }
                    if (msgID & UPD_UPDATECOMPONENTS)
                    {
                        dest.WriteVLE(updatedComponents);
                        dest.Write(updateBuffer.GetData(), updateBuffer.GetPosition());
                    }
                }
            }
        }
    }
    
    */
    
    // Append unacked remote events
    const std::vector<RemoteEvent>& unackedEvents = connection->GetUnackedRemoteEvents();
    for (std::vector<RemoteEvent>::const_iterator i = unackedEvents.begin(); i != unackedEvents.end(); ++i)
    {
        dest.WriteUByte(i->nodeID_ ? MSG_REMOTENODEEVENT : MSG_REMOTEEVENT);
        i->Write(dest);
    }
}

void Server::GetRelevantNodes(Connection* connection, std::set<unsigned>& dest) const
{
    // Generate just the raw set of relevant nodes based on their owner, distance and references. A node might need
    // to stay relevant because it has unacked changes, or has time left in its relevancy timer, but that is checked in
    // WriteNetUpdate()
    PROFILE(GetRelevantNodes);
    
    dest.clear();
    
    Scene* scene = connection->GetScene();
    const std::map<unsigned, Node*>& nodes = scene->GetAllNodes();
    const Vector3& clientPos = connection->GetPosition();
    
    for (std::map<unsigned, Node*>::const_iterator i = nodes.begin(); i != nodes.end(); ++i)
    {
        // Stop when local node ID range reached
        if (i->first >= FIRST_LOCAL_ID)
            break;
        
        Node* node = i->second;
        
        // If node is not owned by client and max. update distance has been defined, check it
        if (node->GetOwner() != connection)
        {
            //float maxDistance = node->GetNetUpdateDistance();
            float maxDistance = 100.0f; /// \todo Add max. update distance to Node
            if (maxDistance > 0.0f)
            {
                if ((node->GetWorldPosition() - clientPos).GetLengthSquared() > maxDistance * maxDistance)
                    continue;
            }
        }
        
        // Node is relevant. Now also find its dependencies
        dest.insert(i->first);
        /// \todo Implement getting the dependencies from a node
        //GetNodeDependencies(connection, node, dest);
    }
}
