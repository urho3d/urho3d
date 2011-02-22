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
#include "Engine.h"
#include "Log.h"
#include "Network.h"
#include "NetworkEvents.h"
#include "Octree.h"
#include "PackageFile.h"
#include "PhysicsWorld.h"
#include "Profiler.h"
#include "Protocol.h"
#include "ProtocolEvents.h"
#include "ReplicationUtils.h"
#include "Scene.h"
#include "Server.h"
#include "StringUtils.h"

#include <set>

#include "DebugNew.h"

// Timeout for closing transferred package files, in milliseconds
static const int FILE_TIMEOUT = 15 * 1000;

Server::Server(Network* network) :
    mNetwork(network),
    mNetFps(30),
    mTimeAcc(0),
    mFrameNumber(1),
    mMaxSceneRevisions(100),
    mStayRelevantTime(30)
{
    if (!mNetwork)
        EXCEPTION("Null network for Server");
    
    LOGINFO("Server created");
    
    subscribeToEvent(EVENT_PEERCONNECTED, EVENT_HANDLER(Server, handlePeerConnected));
    subscribeToEvent(EVENT_PEERDISCONNECTED, EVENT_HANDLER(Server, handlePeerDisconnected));
}

Server::~Server()
{
    LOGINFO("Server shut down");
}

void Server::setNetFps(int fps)
{
    mNetFps = max(fps, 1);
}

void Server::setMaxSceneRevisions(int revisions)
{
    mMaxSceneRevisions = max(revisions, 3);
}

void Server::setStayRelevantTime(int time)
{
    mStayRelevantTime = max(time, 1);
}

void Server::addScene(Scene* scene)
{
    if (!scene)
        return;
    
    if (hasScene(scene))
    {
        LOGWARNING("Scene " + scene->getName() + " already added to server");
        return;
    }
    
    scene->setNetFlags(NET_AUTHORITY);
    mScenes.push_back(SharedPtr<Scene>(scene));
}

void Server::removeScene(Scene* scene)
{
    if (!scene)
        return;
    
    for (unsigned i = 0; i < mScenes.size(); ++i)
    {
        if (mScenes[i] == scene)
        {
            VectorBuffer packet;
            packet.writeUByte(MSG_JOINREPLY);
            packet.writeBool(false);
            packet.writeString("The scene is shutting down");
            
            // If any clients are connected to this scene, they must leave forcibly
            for (unsigned j = 0; j < mConnections.size(); ++j)
            {
                Connection* connection = mConnections[j];
                if (connection->getScene() == scene)
                {
                    connection->sendReliable(packet);
                    connection->leftScene();
                }
            }
            
            // Remove the authority flag
            scene->setNetFlags(NET_NONE);
            mScenes.erase(mScenes.begin() + i);
            return;
        }
    }
    
    LOGWARNING("Scene " + scene->getName() + " not found on server");
}

bool Server::start(unsigned short port)
{
    mTimeAcc = 0.0f;
    mFrameNumber = 1;
    return mNetwork->startServer(port);
}

void Server::stop()
{
    mNetwork->stopServer();
}

void Server::update(float timeStep)
{
    PROFILE(Server_Update);
    
    // Process incoming packets from connections (assume that Engine has updated Network, so we do not do that here)
    for (unsigned i = 0; i < mConnections.size(); ++i)
        handlePackets(mConnections[i]);
    
    // Update scenes / send update if enough time passed
    float netPeriod = 1.0f / mNetFps;
    mTimeAcc += timeStep;
    if (mTimeAcc >= netPeriod)
    {
        // Update simulation of scene(s)
        for (unsigned i = 0; i < mScenes.size(); ++i)
            mScenes[i]->update(netPeriod);
        
        // If multiple updates have accumulated because of a slow frame, send just one
        while (mTimeAcc >= netPeriod)
            mTimeAcc -= netPeriod;
        ++mFrameNumber;
        
        // We have a policy that framenumber 0 means "frame never received", so loop back to 1
        if (!mFrameNumber)
            ++mFrameNumber;
        
        // Check for new queued remote events
        checkRemoteEvents();
        
        // Send update for each connection
        for (unsigned i = 0; i < mConnections.size(); ++i)
        {
            try
            {
                sendServerUpdate(mConnections[i]);
            }
            catch (...)
            {
                disconnect(mConnections[i], false, "Exception while sending scene update, disconnecting client");
            }
        }
    }
    
    // Remove disconnected clients
    for (std::vector<SharedPtr<Connection> >::iterator i = mConnections.begin(); i != mConnections.end();)
    {
        if (!(*i)->isConnected())
            i = mConnections.erase(i);
        else
            ++i;
    }
    
    // Close file transfers that have been unused for some time
    for (std::map<StringHash, ServerFileTransfer>::iterator i = mFileTransfers.begin(); i != mFileTransfers.end();)
    {
        std::map<StringHash, ServerFileTransfer>::iterator current = i++;
        if (current->second.mCloseTimer.getMSec(false) > FILE_TIMEOUT)
            mFileTransfers.erase(current);
    }
}

bool Server::setClientScene(Connection* connection, Scene* scene)
{
    // Check that the scene is under server control
    if (!hasScene(scene))
        return false;
    
    connection->setScene(scene);
    sendSceneInfo(connection);
    
    return true;
}

bool Server::isRunning() const
{
    return mNetwork->isServer();
}

bool Server::hasScene(Scene* scene) const
{
    for (unsigned i = 0; i < mScenes.size(); ++i)
    {
        if (mScenes[i] == scene)
            return true;
    }
    
    return false;
}

unsigned Server::getNumUsersInScene(Scene* scene) const
{
    unsigned users = 0;
    
    for (unsigned i = 0; i < mConnections.size(); ++i)
    {
        if (mConnections[i]->getScene() == scene)
            ++users;
    }
    
    return users;
}

Connection* Server::verifyConnection(Connection* connection) const
{
    for (unsigned i = 0; i < mConnections.size(); ++i)
    {
        if (mConnections[i] == connection)
            return mConnections[i];
    }
    
    return 0;
}

void Server::handlePackets(Connection* connection)
{
    static VectorBuffer packet;
    
    // Process reliable packets first, then unreliable
    while (connection->receiveReliable(packet))
    {
        if (!handleReliablePacket(connection, packet))
            return;
    }
    while (connection->receiveUnreliable(packet))
    {
        if (!handleClientUpdate(connection, packet))
            return;
    }
}

void Server::handlePeerConnected(StringHash eventType, VariantMap& eventData)
{
    using namespace PeerConnected;
    
    Peer* peer = static_cast<Peer*>(eventData[P_PEER].getPtr());
    if (peer->getType() != PEER_CLIENT)
        return;
    
    // Create a new connection, assign a challenge, then send the challenge message
    SharedPtr<Connection> connection(new Connection(peer));
    mConnections.push_back(connection);
    
    unsigned challenge = generateChallenge();
    connection->setChallenge(challenge);
    // Until client sends an identity packet, username is the IP address & port
    connection->setUserName(peer->getAddress() + ":" + toString(peer->getPort()));
    
    VectorBuffer packet;
    packet.writeUByte(MSG_CHALLENGE);
    packet.writeUInt(challenge ^ Connection::sHashInit.mData);
    connection->sendReliable(packet);
}

void Server::handlePeerDisconnected(StringHash eventType, VariantMap& eventData)
{
    using namespace PeerDisconnected;
    
    Peer* peerPtr = static_cast<Peer*>(eventData[P_PEER].getPtr());
    if (peerPtr->getType() != PEER_CLIENT)
        return;
    
    for (unsigned i = 0; i < mConnections.size(); ++i)
    {
        Connection* connection = mConnections[i];
        if (connection->getPeer() == peerPtr)
        {
            // Remove if was in a scene
            connection->leftScene();
            return;
        }
    }
}

bool Server::handleReliablePacket(Connection* connection, VectorBuffer& packet)
{
    unsigned char msgID = 0;
    bool ok = true;
    
    try
    {
        msgID = packet.readUByte();
        // Check response
        if (!connection->checkResponse(packet.readUInt()))
        {
            disconnect(connection, true, "Response check failed for message " + toString(msgID) + ", disconnecting client");
            return false;
        }
        
        switch (msgID)
        {
        case MSG_IDENTITY:
            ok = handleIdentity(connection, packet);
            break;
            
        case MSG_REQUESTFILE:
            ok = handleRequestFile(connection, packet);
            break;
            
        case MSG_JOINSCENE:
            ok = handleJoinScene(connection, packet);
            break;
            
        case MSG_FULLUPDATEACK:
            ok = handleFullUpdateAck(connection, packet);
            break;
            
        default:
            disconnect(connection, false, "Unauthorized message ID " + toString((int)msgID) + ", disconnecting client");
            return false;
        }
    }
    catch (...)
    {
        disconnect(connection, false, "Exception while handling message ID " + toString((int)msgID) + ", disconnecting client");
        return false;
    }
    
    return ok;
}

bool Server::handleIdentity(Connection* connection, VectorBuffer& packet)
{
    // Set initial username
    std::string userName = packet.readString();
    VariantMap loginData = packet.readVariantMap();
    if (userName.empty())
        userName = "user" + toString(random(999));
    connection->setUserName(userName);
    
    // Send identity event and check if any event handler denies access
    using namespace ClientIdentity;
    
    // Initialize eventdata with the logindata received
    VariantMap eventData = loginData;
    eventData[P_CONNECTION] = (void*)connection;
    eventData[P_USERNAME] = userName;
    eventData[P_AUTHORIZE] = true;
    sendEvent(EVENT_CLIENTIDENTITY, eventData);
    
    if (!eventData[P_AUTHORIZE].getBool())
    {
        Peer* peer = connection->getPeer();
        disconnect(connection, false, "Disconnecting unauthorized client from " + peer->getAddress() + ":" +
            toString(peer->getPort()));
        return false;
    }
    
    return true;
}

bool Server::handleRequestFile(Connection* connection, VectorBuffer& packet)
{
    StringHash nameHash = packet.readStringHash();
    int fragmentStart = packet.readVLE();
    int fragmentCount = packet.readVLE();
    
    // The only files we are willing to transmit are packages associated with scene(s)
    PackageFile* package = 0;
    for (unsigned i = 0; i < mScenes.size(); ++i)
    {
        const std::vector<SharedPtr<PackageFile> >& packages =  mScenes[i]->getRequiredPackageFiles();
        for (unsigned j = 0; j < packages.size(); ++j)
        {
            if (packages[j]->getNameHash() == nameHash)
            {
                package = packages[j];
                break;
            }
        }
    }
    if (!package)
    {
        LOGWARNING("Client " + connection->getUserName() + " requested unknown file " + toString(nameHash));
        VectorBuffer replyPacket;
        replyPacket.writeUByte(MSG_TRANSFERFAILED);
        replyPacket.writeStringHash(nameHash);
        replyPacket.writeString("File not found");
        connection->sendReliable(replyPacket);
        return true;
    }
    
    // Open file if not already open
    File* file = mFileTransfers[nameHash].mFile;
    if (!file)
    {
        try
        {
            file = mFileTransfers[nameHash].mFile = new File(package->getName());
        }
        catch(...)
        {
            LOGERROR("Failed to open package file " + package->getName() + " for file transfer");
            VectorBuffer replyPacket;
            replyPacket.writeUByte(MSG_TRANSFERFAILED);
            replyPacket.writeStringHash(nameHash);
            replyPacket.writeString("Could not open file");
            connection->sendReliable(replyPacket);
            return true;
        }
    }
    
    mFileTransfers[nameHash].mCloseTimer.reset();
    
    // Check that fragment range is valid
    unsigned fileSize = file->getSize();
    int maxFragments = (fileSize - 1) / FILE_FRAGMENT_SIZE + 1;
    if (fragmentStart + fragmentCount > maxFragments)
        fragmentCount = maxFragments - fragmentStart;
    if (fragmentCount <= 0)
        return true;
    
    if (!fragmentStart)
        LOGINFO("Client " + connection->getUserName() + " requested file " + toString(nameHash));
    
    // Send the fragments
    unsigned fragmentOffset = fragmentStart * FILE_FRAGMENT_SIZE;
    file->seek(fragmentOffset);
    
    for (int i = fragmentStart; i < fragmentStart + fragmentCount; ++i)
    {
        fragmentOffset = i * FILE_FRAGMENT_SIZE;
        unsigned fragmentSize = fileSize - fragmentOffset;
        if (fragmentSize > FILE_FRAGMENT_SIZE)
            fragmentSize = FILE_FRAGMENT_SIZE;
        
        static VectorBuffer fragmentPacket;
        fragmentPacket.seek(0);
        fragmentPacket.writeUByte(MSG_TRANSFERDATA);
        fragmentPacket.writeStringHash(nameHash);
        fragmentPacket.writeVLE(i);
        fragmentPacket.resize(fragmentPacket.getPosition() + fragmentSize);
        file->read(fragmentPacket.getModifiableData() + fragmentPacket.getPosition(), fragmentSize);
        connection->sendReliable(fragmentPacket);
    }
    
    return true;
}

bool Server::handleJoinScene(Connection* connection, VectorBuffer& packet)
{
    unsigned checksum = packet.readUInt();
    Scene* scene = connection->getScene();
    
    VectorBuffer replyPacket;
    replyPacket.writeUByte(MSG_JOINREPLY);
    
    if (!scene)
    {
        replyPacket.writeBool(false);
        replyPacket.writeString("No scene");
        LOGINFO("Client " + connection->getUserName() + " attempted to join without an assigned scene");
    }
    else if (checksum != scene->getChecksum())
    {
        replyPacket.writeBool(false);
        replyPacket.writeString("Scene checksum mismatch");
        LOGINFO("Client " + connection->getUserName() + " checksum mismatch for scene " + scene->getName());
    }
    else
    {
        replyPacket.writeBool(true);
        replyPacket.writeString(connection->getUserName());
        connection->joinedScene();
    }
    
    connection->sendReliable(replyPacket);
    return true;
}

bool Server::handleFullUpdateAck(Connection* connection, VectorBuffer& packet)
{
    if (connection->getJoinState() == JS_WAITFORACK)
    {
        unsigned short lastFrameNumber = packet.readUShort();
        unsigned short lastFrameAck = packet.readUShort();
        connection->setFrameNumbers(lastFrameNumber, lastFrameAck);
        connection->updateRoundTripTime(mNetFps, mFrameNumber);
        connection->setJoinState(JS_SENDDELTAS);
    }
    else
        LOGWARNING("Received unexpected full update ack from client " + connection->getUserName());
    
    return true;
}

bool Server::handleClientUpdate(Connection* connection, VectorBuffer& packet)
{
    // Disregard unreliable client updates while waiting for the initial scene ack
    if (connection->getJoinState() != JS_SENDDELTAS)
        return true;
    
    unsigned short lastFrameNumber = packet.readUShort();
    unsigned short lastFrameAck = packet.readUShort();
    
    // Check that this packet is not older than the last received (overlap may occur when we transition
    // between a reliable full update and unreliable delta updates)
    if (!checkFrameNumber(lastFrameNumber, connection->getFrameNumber()))
        return true;
    
    connection->setFrameNumbers(lastFrameNumber, lastFrameAck);
    connection->updateRoundTripTime(mNetFps, mFrameNumber);
    
    unsigned short previousEventFrameNumber = connection->getEventFrameNumber();
    
    while (!packet.isEof())
    {
        unsigned char msgID = packet.readUByte();
        // The client is only allowed to send a few specific messages in the client update
        switch (msgID)
        {
        case MSG_REMOTEEVENT:
            {
                RemoteEvent newEvent;
                newEvent.read(packet, false);
                if (connection->checkRemoteEventFrame(newEvent, previousEventFrameNumber))
                    newEvent.dispatch(connection, connection->getScene());
            }
            break;
            
        case MSG_REMOTEENTITYEVENT:
            {
                RemoteEvent newEvent;
                newEvent.read(packet, true);
                if (connection->checkRemoteEventFrame(newEvent, previousEventFrameNumber))
                    newEvent.dispatch(connection, connection->getScene());
            }
            break;
            
        case MSG_CONTROLS:
            {
                Controls newControls;
                newControls.mButtons = packet.readUInt();
                newControls.mYaw = packet.readFloat();
                newControls.mPitch = packet.readFloat();
                newControls.mExtraData = packet.readVariantMap();
                connection->setControls(newControls);
                connection->setPosition(packet.readVector3());
                
                using namespace ClientControls;
                
                // Initialize event parameters with possible extra controls
                VariantMap eventData = newControls.mExtraData;
                eventData[P_CONNECTION] = (void*)connection;
                eventData[P_FRAMENUMBER] = connection->getFrameNumber();
                eventData[P_BUTTONS] = newControls.mButtons;
                eventData[P_YAW] = newControls.mYaw;
                eventData[P_PITCH] = newControls.mPitch;
                sendEvent(EVENT_CLIENTCONTROLS, eventData);
                break;
            }
            
        default:
            disconnect(connection, false, "Unauthorized message ID " + toString((int)msgID) + ", disconnecting client");
            return false;
        }
    }
    return true;
}

void Server::checkRemoteEvents()
{
    for (unsigned i = 0; i < mScenes.size(); ++i)
    {
        Scene* scene = mScenes[i];
        
        // Check new outgoing remote events, assign them framenumbers, and put to unacked queue
        std::vector<RemoteEvent>& outEvents = scene->getQueuedRemoteEvents();
        for (std::vector<RemoteEvent>::iterator j = outEvents.begin(); j != outEvents.end();)
        {
            j->mFrameNumber = mFrameNumber;
            
            // Check for broadcast event
            if (!j->mReceiver)
            {
                for (unsigned k = 0; k < mConnections.size(); ++k)
                {
                    Connection* connection = mConnections[k];
                    if (connection->getScene() == scene)
                        connection->addRemoteEvent(*j);
                }
            }
            else
            {
                // The connection stored in the event might not be valid by now, so verify it
                Connection* connection = verifyConnection(j->mReceiver);
                if (connection)
                    connection->addRemoteEvent(*j);
            }
            
            j = outEvents.erase(j);
        }
    }
}

void Server::sendSceneInfo(Connection* connection)
{
    Scene* scene = connection->getScene();
    if (!scene)
        return;
    
    VectorBuffer packet;
    packet.writeUByte(MSG_SCENEINFO);
    
    // Write scene name, number of users and update rate
    packet.writeString(scene->getName());
    packet.writeVLE(getNumUsersInScene(scene));
    packet.writeInt(mNetFps);
    
    // Write source file name & required packages
    const std::vector<SharedPtr<PackageFile> >& requiredPackages = scene->getRequiredPackageFiles();
    packet.writeString(scene->getFileName());
    packet.writeVLE(requiredPackages.size());
    for (unsigned i = 0; i < requiredPackages.size(); ++i)
    {
        PackageFile* package = requiredPackages[i];
        packet.writeString(package->getName());
        packet.writeUInt(package->getTotalSize());
        packet.writeUInt(package->getChecksum());
    }
    
    // Write scene properties
    VectorBuffer sceneProperties;
    scene->saveProperties(sceneProperties);
    
    packet.writeVLE(sceneProperties.getSize());
    packet.write(sceneProperties.getData(), sceneProperties.getSize());
    
    connection->sendReliable(packet);
}

void Server::sendFullUpdate(Connection* connection)
{
    PROFILE(Server_SendFullUpdate);
    
    Scene* scene = connection->getScene();
    if (!scene)
        return;
    
    // Clear all scene revision data so that we write a full update
    connection->clearSceneState();
    
    static VectorBuffer packet;
    packet.resize(0);
    packet.writeUByte(MSG_FULLUPDATE);
    writeNetUpdate(connection, packet);
    connection->sendReliable(packet);
    
    // All unacked remote events were sent reliably, so clear them
    connection->clearRemoteEvents();
    connection->setJoinState(JS_WAITFORACK);
    
    LOGINFO("Initial scene: " + toString(packet.getSize()) + " bytes");
}

void Server::sendServerUpdate(Connection* connection)
{
    PROFILE(Server_SendServerUpdate);
    
    Scene* scene = connection->getScene();
    JoinState state = connection->getJoinState();
    if ((!scene) || (state < JS_SENDFULLUPDATE) || (state == JS_WAITFORACK))
        return;
    
    // Purge states and events which are older than last acked, and expired remote events
    connection->purgeAckedSceneState();
    connection->purgeAckedRemoteEvents(mFrameNumber);
    
    // If already have too many revisions stored, fall back to the initial scene sending (reliable)
    if (connection->getSceneState().getRevisionCount() >= mMaxSceneRevisions)
    {
        LOGWARNING("Too many scene revisions for client " + connection->getUserName() +
            ", falling back to initial scene send");
        state = JS_SENDFULLUPDATE;
    }
    
    // Send initial scene as reliable
    if (state == JS_SENDFULLUPDATE)
    {
        sendFullUpdate(connection);
        return;
    }
    
    static VectorBuffer packet;
    packet.resize(0);
    writeNetUpdate(connection, packet);
    connection->sendUnreliable(packet);
    
    //LOGINFO("Delta: " + toString(packet.getSize()) + " Revisions: " +
    //    toString(connection->getSceneState().getRevisionCount()) + " Events: " +
    //    toString(connection->getUnackedRemoteEvents().size()));
}

unsigned Server::generateChallenge() const
{
    return (rand() & 32767) | ((rand() & 32767) << 15) | ((rand() & 32767) << 30);
}

void Server::disconnect(Connection* connection, bool forced, const std::string& logMessage)
{
    LOGERROR(logMessage + " " + connection->getUserName());
    
    if (forced)
        connection->forceDisconnect();
    else
        connection->disconnect();
    
    // Send event
    using namespace ClientDisconnected;
    
    VariantMap eventData;
    eventData[P_CONNECTION] = (void*)connection;
    sendEvent(EVENT_CLIENTDISCONNECTED, eventData);
}

void Server::writeNetUpdate(Connection* connection, Serializer& dest)
{
    PROFILE(Server_WriteNetUpdate);
    
    Scene* scene = connection->getScene();
    SceneReplicationState& sceneState = connection->getSceneState();
    
    // Write frame numbers and physics sync information
    dest.writeUShort(mFrameNumber);
    dest.writeUShort(connection->getFrameNumber());
    float physicsTimeAcc = 0.0f;
    PhysicsWorld* world = scene->getExtension<PhysicsWorld>();
    if (world)
        physicsTimeAcc = world->getTimeAccumulator();
    dest.writeFloat(physicsTimeAcc);
    
    NetUpdateInfo info;
    info.mConnection = connection;
    info.mFrameNumber = mFrameNumber;
    info.mFrameAck = connection->getFrameAck();
    info.mRemoteFrameNumber = connection->getFrameNumber();
    info.mRoundTripTime = connection->getRoundTripTime();
    
    static VectorBuffer emptyBaseRevision;
    static VectorBuffer propertyBuffer;
    static VectorBuffer newBuffer;
    static VectorBuffer removeBuffer;
    static VectorBuffer updateBuffer;
    static VectorBuffer newRevision;
    
    // Find relevant entities for this client
    static std::set<EntityID> relevantEntities;
    getRelevantEntities(connection, relevantEntities);
    
    {
        // Go through the scene and see which entities are new and which have been removed
        const std::map<EntityID, SharedPtr<Entity> >& entities = scene->getEntities();
        std::set<EntityID> processedEntities;
        for (std::map<EntityID, SharedPtr<Entity> >::const_iterator i = entities.begin(); i != entities.end(); ++i)
        {
            // If we reach the local entity ID's, break
            if (i->first >= LOCAL_ENTITY)
                break;
            
            processedEntities.insert(i->first);
            
            bool relevant = relevantEntities.find(i->first) != relevantEntities.end();
            
            Entity* entity = i->second;
            EntityReplicationState* entityState = sceneState.findEntity(i->first);
            if (!entityState)
            {
                // If client does not have this entity and it is not relevant, skip
                if (!relevant)
                    continue;
                
                entityState = &sceneState.mEntities[i->first];
                entityState->created(mFrameNumber);
                entityState->mStayRelevantTime = mStayRelevantTime;
            }
            else
            {
                // If entitystate exists, check relevancy timer and refresh it if necessary
                if (relevant)
                    entityState->mStayRelevantTime = mStayRelevantTime;
                else if (entityState->mStayRelevantTime > 0)
                {
                    --entityState->mStayRelevantTime;
                    relevant = true;
                }
                else
                    // If entity is not relevant, and relevancy timer has expired, do not check for changes
                    continue;
                
                if (!entityState->mExists)
                    entityState->created(mFrameNumber);
            }
            
            // Check components of this entity
            const std::vector<SharedPtr<Component> >& components = entity->getComponents();
            std::set<ShortStringHash> processedComponents;
            for (std::vector<SharedPtr<Component> >::const_iterator j = components.begin(); j != components.end(); ++j)
            {
                Component* component = *j;
                if (!component->checkSync(connection))
                    continue;
                
                ShortStringHash combinedHash = component->getCombinedHash();
                ComponentReplicationState* componentState = entityState->findComponent(combinedHash);
                
                if (!componentState)
                {
                    componentState = &entityState->mComponents[combinedHash];
                    componentState->created(mFrameNumber);
                }
                else if (!componentState->mExists)
                    componentState->created(mFrameNumber);
                
                processedComponents.insert(combinedHash);
            }
            
            // Check components that have been removed
            for (std::map<ShortStringHash, ComponentReplicationState>::iterator j = entityState->mComponents.begin();
                j != entityState->mComponents.end(); ++j)
            {
                if (j->second.mExists)
                {
                    if (processedComponents.find(j->first) == processedComponents.end())
                        j->second.removed(mFrameNumber);
                }
            }
        }
        
        // Check entities that have been removed
        for (std::map<EntityID, EntityReplicationState>::iterator i = sceneState.mEntities.begin();
            i != sceneState.mEntities.end(); ++i)
        {
            if (i->second.mExists)
            {
                if (processedEntities.find(i->first) == processedEntities.end())
                    i->second.removed(mFrameNumber);
            }
        }
    }
    
    {
        // Now go through the replication state again and build commands
        for (std::map<EntityID, EntityReplicationState>::iterator i = sceneState.mEntities.begin();
            i != sceneState.mEntities.end(); ++i)
        {
            Entity* entity = scene->getEntity(i->first);
            EntityReplicationState& entityState = i->second;
            // Create
            if ((entityState.mCreatedFrame) && (entity))
            {
                dest.writeUByte(MSG_CREATEENTITY);
                dest.writeUShort(entity->getID());
                dest.writeString(entity->getName());
                dest.writeUByte(getClientNetFlags(connection, entity, entity->getNetFlags()));
                dest.writeVLE(entity->getGroupFlags());
                
                // Write a full update of entity properties
                newRevision.seek(0);
                if (entity->writeNetUpdate(dest, newRevision, emptyBaseRevision, info))
                    entityState.mPropertyRevisions.commit(mFrameNumber, newRevision);
                
                // Write a full update of all components that should be synced
                const std::vector<SharedPtr<Component> >& components = entity->getComponents();
                unsigned newComponents = 0;
                newBuffer.seek(0);
                
                for (std::vector<SharedPtr<Component> >::const_iterator j = components.begin(); j != components.end(); ++j)
                {
                    Component* component = *j;
                    if (!component->checkSync(connection))
                        continue;
                    
                    ComponentReplicationState& componentState = entityState.mComponents[component->getCombinedHash()];
                    newBuffer.writeShortStringHash(component->getType());
                    newBuffer.writeString(component->getName());
                    newBuffer.writeUByte(getClientNetFlags(connection, entity, component->getNetFlags()));
                    newRevision.seek(0);
                    component->writeNetUpdate(newBuffer, newRevision, emptyBaseRevision, info);
                    componentState.mRevisions.commit(mFrameNumber, newRevision);
                    ++newComponents;
                }
                
                dest.writeVLE(newComponents);
                // Check if any components were actually written
                if (newComponents)
                    dest.write(newBuffer.getData(), newBuffer.getPosition());
            }
            // Remove
            else if (entityState.mRemovedFrame)
            {
                dest.writeUByte(MSG_REMOVEENTITY);
                dest.writeUShort(i->first);
            }
            // Update
            else if (entity)
            {
                // If entity's update timer has expired (it is not relevant), do not write updates
                if (entityState.mStayRelevantTime <= 0)
                {
                    // However, we must be careful to see what to do when the entity becomes relevant again
                    // If entity has unacked property or component revisions, must forget all of them
                    if (entityState.hasUnacked(connection->getFrameAck()))
                    {
                        entityState.mPropertyRevisions.clear();
                        for (std::map<ShortStringHash, ComponentReplicationState>::iterator j = entityState.mComponents.begin();
                            j != entityState.mComponents.end(); ++j)
                            j->second.mRevisions.clear();
                    }
                    continue;
                }
                
                // Divide update types into separate buffers, then see which of them got data
                // (if there are no updates, then this entity does not need to write anything into the final stream)
                unsigned newComponents = 0;
                unsigned removedComponents = 0;
                unsigned updatedComponents = 0;
                
                propertyBuffer.seek(0);
                newBuffer.seek(0);
                removeBuffer.seek(0);
                updateBuffer.seek(0);
                
                unsigned char msgID = MSG_UPDATEENTITY;
                
                // Property update
                Deserializer& baseRevision = entityState.mPropertyRevisions.getBase();
                newRevision.seek(0);
                if (entity->writeNetUpdate(propertyBuffer, newRevision, baseRevision, info))
                {
                    entityState.mPropertyRevisions.commit(mFrameNumber, newRevision);
                    msgID |= UPD_PROPERTIES;
                }
                
                // Component create/remove/update
                for (std::map<ShortStringHash, ComponentReplicationState>::iterator j = entityState.mComponents.begin();
                    j != entityState.mComponents.end(); ++j)
                {
                    Component* component = entity->getComponent(j->first.mData);
                    ComponentReplicationState& componentState = j->second;
                    // Create
                    if ((componentState.mCreatedFrame) && (component))
                    {
                        newBuffer.writeShortStringHash(component->getType());
                        newBuffer.writeString(component->getName());
                        newBuffer.writeUByte(getClientNetFlags(connection, entity, component->getNetFlags()));
                        newRevision.seek(0);
                        component->writeNetUpdate(newBuffer, newRevision, emptyBaseRevision, info);
                        componentState.mRevisions.commit(mFrameNumber, newRevision);
                        msgID |= UPD_NEWCOMPONENTS;
                        ++newComponents;
                    }
                    // Remove
                    else if (componentState.mRemovedFrame)
                    {
                        msgID |= UPD_REMOVECOMPONENTS;
                        ++removedComponents;
                        removeBuffer.writeShortStringHash(j->first);
                    }
                    // Update
                    else if (component)
                    {
                        // Prepare to rewind buffer in case component writes nothing meaningful
                        unsigned oldPos = updateBuffer.getPosition();
                        updateBuffer.writeShortStringHash(component->getCombinedHash());
                        newRevision.seek(0);
                        Deserializer& baseRevision = componentState.mRevisions.getBase();
                        if (component->writeNetUpdate(updateBuffer, newRevision, baseRevision, info))
                        {
                            componentState.mRevisions.commit(mFrameNumber, newRevision);
                            msgID |= UPD_UPDATECOMPONENTS;
                            ++updatedComponents;
                        }
                        else
                            updateBuffer.seek(oldPos);
                    }
                }
                
                // Now write each buffer if there was some data
                if (msgID != MSG_UPDATEENTITY)
                {
                    dest.writeUByte(msgID);
                    dest.writeUShort(entity->getID());
                    
                    if (msgID & UPD_PROPERTIES)
                        dest.write(propertyBuffer.getData(), propertyBuffer.getPosition());
                    if (msgID & UPD_NEWCOMPONENTS)
                    {
                        dest.writeVLE(newComponents);
                        dest.write(newBuffer.getData(), newBuffer.getPosition());
                    }
                    if (msgID & UPD_REMOVECOMPONENTS)
                    {
                        dest.writeVLE(removedComponents);
                        dest.write(removeBuffer.getData(), removeBuffer.getPosition());
                    }
                    if (msgID & UPD_UPDATECOMPONENTS)
                    {
                        dest.writeVLE(updatedComponents);
                        dest.write(updateBuffer.getData(), updateBuffer.getPosition());
                    }
                }
            }
        }
    }
    
    // Append unacked remote events
    const std::vector<RemoteEvent>& unackedEvents = connection->getUnackedRemoteEvents();
    for (std::vector<RemoteEvent>::const_iterator i = unackedEvents.begin(); i != unackedEvents.end(); ++i)
    {
        dest.writeUByte(i->mEntityID ? MSG_REMOTEENTITYEVENT : MSG_REMOTEEVENT);
        i->write(dest);
    }
}

void Server::getRelevantEntities(Connection* connection, std::set<EntityID>& dest) const
{
    // Generate just the raw set of relevant entities based on their owner, distance and references. An entity might need
    // to stay relevant because it has unacked changes, or has time left in its relevancy timer, but that is checked in
    // writeNetUpdate()
    PROFILE(Server_GetRelevantEntities);
    
    dest.clear();
    
    Scene* scene = connection->getScene();
    const std::map<EntityID, SharedPtr<Entity> >& entities = scene->getEntities();
    const Vector3& clientPos = connection->getPosition();
    
    for (std::map<EntityID, SharedPtr<Entity> >::const_iterator i = entities.begin(); i != entities.end(); ++i)
    {
        // Stop when local entity ID range reached
        if (i->first >= LOCAL_ENTITY)
            break;
        
        Entity* entity = i->second;
        
        // Skip if entity is not to be synced
        if (!entity->checkSync(connection))
            continue;
        
        // If entity is not owned by client and max. update distance has been defined, check it
        if (entity->getOwner() != connection)
        {
            float maxDistance = entity->getNetUpdateDistance();
            if (maxDistance > 0.0f)
            {
                if ((scene->getEntityPosition(entity) - clientPos).getLengthSquared() > maxDistance * maxDistance)
                    continue;
            }
        }
        
        // Entity is relevant. Now also find its dependencies
        dest.insert(i->first);
        getEntityDependencies(connection, entity, dest);
    }
}

void Server::getEntityDependencies(Connection* connection, Entity* entity, std::set<EntityID>& dest) const
{
    static std::vector<ComponentRef> refs;
    static std::set<EntityID> checked;
    checked.clear();
    
    EntityID ownID = entity->getID();
    // Local entities should not depend on non-local entities or vice versa
    if (ownID >= LOCAL_ENTITY)
        return;
    
    entity->getComponentRefs(refs);
    for (std::vector<ComponentRef>::iterator i = refs.begin(); i != refs.end(); ++i)
    {
        // If an entity depends on a local entity, it may either be totally harmless, or a serious bug, depending on whether
        // the client also has the same entity from a scene file, and it is unmodified. We can not know, so let it go
        if ((i->mEntityID) && (i->mEntityID != ownID) && (i->mEntityID < LOCAL_ENTITY))
        {
            if (checked.find(i->mEntityID) == checked.end())
            {
                // Check sync of the depended entity before we store it
                Entity* other = connection->getScene()->getEntity(i->mEntityID);
                if ((other) && (other->checkSync(connection)))
                    dest.insert(i->mEntityID);
                checked.insert(i->mEntityID);
            }
        }
    }
}

unsigned char Server::getClientNetFlags(Connection* connection, Entity* entity, unsigned char flags) const
{
    unsigned char ret = flags & ~(NET_MODEFLAGS);
    ret |= NET_PROXY;
    
    if (entity->getOwner() == connection)
        ret |= NET_OWNER;
    else
        ret &= ~NET_OWNERPREDICT;
    
    return ret;
}
