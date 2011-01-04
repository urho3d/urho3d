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
#include "Client.h"
#include "Connection.h"
#include "Engine.h"
#include "Log.h"
#include "Network.h"
#include "NetworkEvents.h"
#include "Octree.h"
#include "PackageFile.h"
#include "PhysicsWorld.h"
#include "ProcessUtils.h"
#include "Profiler.h"
#include "Protocol.h"
#include "ProtocolEvents.h"
#include "ReplicationUtils.h"
#include "ResourceCache.h"
#include "Scene.h"
#include "StringUtils.h"

#include "DebugNew.h"

static const Controls noControls;
static const int MIN_FILE_FRAGMENT_COUNT = 16;
static const int MAX_FILE_FRAGMENT_COUNT = 1024;
static const int FILE_FRAGMENT_COUNT_DELTA = 8;

Client::Client(Network* network, ResourceCache* cache, const std::string& downloadDirectory) :
    mNetwork(network),
    mCache(cache),
    mNetFps(30),
    mTimeAcc(0.0f),
    mMaxPredictionTime(0.25f), // 250 ms
    mFrameNumber(1),
    mDownloadDirectory(fixPath(downloadDirectory))
{
    if (!mNetwork)
        EXCEPTION("Null network for Client");
    
   if (!mCache)
        EXCEPTION("Null resource cache for Client");
    
    LOGINFO("Client created");
    
    subscribeToEvent(EVENT_PEERDISCONNECTED, EVENT_HANDLER(Client, handlePeerDisconnected));
    subscribeToEvent(EVENT_FILETRANSFERCOMPLETED, EVENT_HANDLER(Client, handleFileTransferCompleted));
    subscribeToEvent(EVENT_FILETRANSFERFAILED, EVENT_HANDLER(Client, handleFileTransferFailed));
}

Client::~Client()
{
    LOGINFO("Client shut down");
}

void Client::setScene(Scene* scene)
{
    mScene = scene;
}

void Client::setMaxPredictionTime(float time)
{
    mMaxPredictionTime = max(time, 0.0f);
}

bool Client::connect(const std::string& address, unsigned short port, const std::string& userName, const VariantMap& loginData)
{
    disconnect();
    
    Peer* peer = mNetwork->connect(address, port);
    if (!peer)
        return false;
    
    mServerConnection = new Connection(peer);
    mFrameNumber = 1;
    mPendingUserName = userName;
    mPendingLoginData = loginData;
    return true;
}

void Client::disconnect()
{
    if (mServerConnection)
    {
        mServerConnection->disconnect();
        mServerConnection.reset();
    }
    
    mPendingDownloads.clear();
    mFileTransfers.clear();
    mSceneInfo = SceneInfo();
}

void Client::setControls(const Controls& controls)
{
    if (mServerConnection)
        mServerConnection->setControls(controls);
}

void Client::setPosition(const Vector3& position)
{
    if (mServerConnection)
        mServerConnection->setPosition(position);
}

void Client::update(float timeStep)
{
    PROFILE(Client_Update);
    
    // Process connection (assume that Engine has updated Network, so we do not do that here)
    if (mServerConnection)
    {
        static VectorBuffer packet;
        
        // Process reliable packets first, then unreliable
        while (mServerConnection->receiveReliable(packet))
            handleReliablePacket(packet);
        
        while (mServerConnection->receiveUnreliable(packet))
            handleServerUpdate(packet);
        
        // Update own simulation of scene if connected
        if (mServerConnection->getScene() == mScene)
            mScene->update(timeStep);
    }
    
    // Send update if enough time passed
    float netPeriod = 1.0f / mNetFps;
    mTimeAcc += timeStep;
    if (mTimeAcc >= netPeriod)
    {
        // If multiple updates have accumulated because of a slow frame, send just one
        while (mTimeAcc >= netPeriod)
            mTimeAcc -= netPeriod;
        ++mFrameNumber;
        // We have a policy that framenumber 0 means "frame never received", so loop back to 1
        if (!mFrameNumber)
            ++mFrameNumber;
        sendClientUpdate();
    }
}

bool Client::isConnected() const
{
    return (mServerConnection) && (mServerConnection->isConnected()) && (mServerConnection->hasChallenge());
}

bool Client::isJoinPending() const
{
    return ((isConnected()) && (mServerConnection->getJoinState() == JS_PREPARESCENE));
}

bool Client::isJoined() const
{
    return ((isConnected()) && (mServerConnection->getJoinState() > JS_PREPARESCENE));
}

const Controls& Client::getControls() const
{
    if (!mServerConnection)
        return noControls;
    return mServerConnection->getControls();
}

const Vector3& Client::getPosition() const
{
    if (!mServerConnection)
        return Vector3::sZero;
    return mServerConnection->getPosition();
}

std::string Client::getFileTransferStatus() const
{
    std::string ret;
    
    for (std::map<StringHash, FileTransfer>::const_iterator i = mFileTransfers.begin(); i != mFileTransfers.end(); ++i)
    {
        std::string line = i->second.mFileName + " " + toString(i->second.mBytesReceived) + "/" + toString(i->second.mSize) 
            + " (" + toString((int)(((float)i->second.mBytesReceived / (float)i->second.mSize) * 100.0f + 0.5f)) + "%)\n";
        ret += line;
    }
    
    return ret;
}

void Client::handlePeerDisconnected(StringHash eventType, VariantMap& eventData)
{
    using namespace PeerDisconnected;
    
    Peer* peerPtr = static_cast<Peer*>(eventData[P_PEER].getPtr());
    if (peerPtr->getType() != PEER_SERVER)
        return;
    
    if (mServerConnection)
    {
        if (mServerConnection->getPeer() == peerPtr)
        {
            mServerConnection->leftScene();
            mServerConnection.reset();
            mPendingDownloads.clear();
            mFileTransfers.clear();
            mSceneInfo = SceneInfo();
        }
    }
}

void Client::handleFileTransferCompleted(StringHash eventType, VariantMap& eventData)
{
    using namespace FileTransferCompleted;
    
    std::string fileName = eventData[P_FILENAME].getString();
    if (mPendingDownloads.find(fileName) != mPendingDownloads.end())
    {
        mPendingDownloads.erase(fileName);
        
        // Add the package to the resource cache
        try
        {
            SharedPtr<PackageFile> package(new PackageFile(eventData[P_FULLPATH].getString()));
            // Add the package as first in case it overrides something in the default files
            mCache->addPackageFile(package, true);
        }
        catch (...)
        {
            joinFailed("Could not open downloaded package file " + fileName);
            return;
        }
        
        // If this was the last required download, can now join scene
        if ((mPendingDownloads.empty()) && (isJoinPending()))
            setupSceneAndJoin();
    }
}

void Client::handleFileTransferFailed(StringHash eventType, VariantMap& eventData)
{
    using namespace FileTransferFailed;
    
    std::string fileName = eventData[P_FILENAME].getString();
    if (mPendingDownloads.find(fileName) != mPendingDownloads.end())
        joinFailed("Failed to transfer file " + fileName);
}

void Client::handleReliablePacket(VectorBuffer& packet)
{
    unsigned char msgID = 0;
    
    try
    {
        msgID = packet.readUByte();
        
        switch (msgID)
        {
        case MSG_CHALLENGE:
            handleChallenge(packet);
            break;
            
        case MSG_SCENEINFO:
            handleSceneInfo(packet);
            break;
            
        case MSG_TRANSFERDATA:
            handleTransferData(packet);
            break;
            
        case MSG_TRANSFERFAILED:
            handleTransferFailed(packet);
            break;
            
        case MSG_JOINREPLY:
            handleJoinReply(packet);
            break;
            
        case MSG_FULLUPDATE:
            handleFullUpdate(packet);
            break;
            
        default:
            LOGERROR("Unknown message ID " + toString((int)msgID) + " received from server");
            break;
        }
    }
    catch (...)
    {
        LOGERROR("Exception while handling message ID " + toString((int)msgID));
    }
}

void Client::handleChallenge(VectorBuffer& packet)
{
    mServerConnection->setChallenge(packet.readUInt() ^ Connection::sHashInit.mData);
    
    // Send identity packet as a response
    VectorBuffer replyPacket;
    replyPacket.writeUByte(MSG_IDENTITY);
    replyPacket.writeUInt(mServerConnection->getResponse());
    replyPacket.writeString(mPendingUserName);
    replyPacket.writeVariantMap(mPendingLoginData);
    mServerConnection->sendReliable(replyPacket);
    mServerConnection->updateResponse();
}

void Client::handleSceneInfo(VectorBuffer& packet)
{
    if (!mScene)
        return;
    
    // Empty the scene of any previous contents
    mServerConnection->setScene(mScene);
    
    // Read scene name, number of users and update rate
    std::string sceneName = packet.readString();
    mSceneInfo.mName = sceneName;
    mSceneInfo.mNumUsers = packet.readVLE();
    mSceneInfo.mNetFps = packet.readInt();
    
    // Read source file name & required packages
    mSceneInfo.mFileName = packet.readString();
    unsigned numPackages = packet.readVLE();
    mSceneInfo.mRequiredPackages.clear();
    for (unsigned i = 0; i < numPackages; ++i)
    {
        PackageInfo package;
        package.mName = packet.readString();
        package.mSize = packet.readUInt();
        package.mChecksum = packet.readUInt();
        mSceneInfo.mRequiredPackages.push_back(package);
    }
    
    // Read scene properties
    unsigned scenePropertiesSize = packet.readVLE();
    mSceneInfo.mSceneProperties.setData(packet, scenePropertiesSize);
    
    // Check need for downloads: if none, can join immediately
    if (!checkPackages())
        setupSceneAndJoin();
}

void Client::handleTransferData(VectorBuffer& packet)
{
    StringHash nameHash = packet.readStringHash();
    std::map<StringHash, FileTransfer>::iterator i = mFileTransfers.find(nameHash);
    if (i == mFileTransfers.end())
    {
        LOGDEBUG("Received fragment for nonexisting file transfer " + toString(nameHash));
        return;
    }
    FileTransfer& transfer = i->second;
    
    unsigned index = packet.readVLE();
    if (transfer.mNumReceived != index)
    {
        LOGERROR("Received unexpected fragment for file " + toString(nameHash) + ", stopping transfer");
        
        using namespace FileTransferFailed;
        
        VariantMap eventData;
        eventData[P_FILENAME] = transfer.mFileName;
        eventData[P_REASON] = "Unexpected fragment";
        sendEvent(EVENT_FILETRANSFERFAILED, eventData);
        
        mFileTransfers.erase(i);
        return;
    }
    
    transfer.mNumReceived = index + 1; // We receive fragments in order
    unsigned dataSize = packet.getSize() - packet.getPosition();
    transfer.mFile->write(packet.getData() + packet.getPosition(), dataSize);
    transfer.mBytesReceived += dataSize;
    
    if (transfer.mNumReceived == transfer.mNumFragments)
    {
        if (transfer.mBytesReceived != transfer.mSize)
        {
            LOGERROR("Transfer of file " + transfer.mFileName + " finished, expected " + toString(transfer.mSize) +
                " bytes but got " + toString(transfer.mBytesReceived));
            
            using namespace FileTransferFailed;
            
            VariantMap eventData;
            eventData[P_FILENAME] = transfer.mFileName;
            eventData[P_REASON] = "Unexpected file size";
            sendEvent(EVENT_FILETRANSFERFAILED, eventData);
        }
        else
        {
            float totalTime = transfer.mReceiveTimer.getMSec(true) * 0.001f;
            LOGINFO("Transfer of file " + transfer.mFileName + " completed in " +
                toString(totalTime) + " seconds, speed " + toString(transfer.mSize / totalTime) + " bytes/sec");
            using namespace FileTransferCompleted;
            
            VariantMap eventData;
            eventData[P_FILENAME] = transfer.mFileName;
            eventData[P_FULLPATH] = transfer.mFile->getName();
            
            // Others might try to use the file as a response to the event, so close it first
            transfer.mFile.reset();
            
            sendEvent(EVENT_FILETRANSFERCOMPLETED, eventData);
        }
        
        mFileTransfers.erase(i);
        return;
    }
    
    // If current batch was finished, fire off the next
    if (transfer.mNumReceived == transfer.mBatchStart + transfer.mBatchSize)
    {
        transfer.mBatchStart = transfer.mNumReceived;
        float batchTime = transfer.mBatchTimer.getMSec(true) * 0.001f;
        float newDataRate = transfer.mBatchSize * FILE_FRAGMENT_SIZE / batchTime;
        LOGDEBUG("Received " + toString(transfer.mBatchSize) + " fragments in " + toString(batchTime) + " seconds");
        
        // If this was the first batch, can not yet estimate speed, so go up in batch size
        if (!transfer.mLastBatchSize)
        {
            transfer.mLastBatchSize = transfer.mBatchSize;
            transfer.mLastDataRate = newDataRate;
            transfer.mBatchSize += FILE_FRAGMENT_COUNT_DELTA;
        }
        else
        {
            bool goUp = true;
            // Go down in batch size if last batch was smaller and had better data rate
            if ((transfer.mLastBatchSize < transfer.mBatchSize) && (transfer.mLastDataRate > newDataRate))
                goUp = false;
            
            transfer.mLastBatchSize = transfer.mBatchSize;
            transfer.mLastDataRate = newDataRate;
            
            if (goUp)
                transfer.mBatchSize += FILE_FRAGMENT_COUNT_DELTA;
            else
                transfer.mBatchSize -= FILE_FRAGMENT_COUNT_DELTA;
            
            transfer.mBatchSize = clamp((int)transfer.mBatchSize, MIN_FILE_FRAGMENT_COUNT, MAX_FILE_FRAGMENT_COUNT);
        }
        
        VectorBuffer packet;
        packet.writeUByte(MSG_REQUESTFILE);
        packet.writeUInt(mServerConnection->getResponse());
        packet.writeStringHash(i->first);
        packet.writeVLE(transfer.mBatchStart);
        packet.writeVLE(transfer.mBatchSize);
        mServerConnection->sendReliable(packet);
        mServerConnection->updateResponse();
    }
}

void Client::handleTransferFailed(VectorBuffer& packet)
{
    StringHash nameHash = packet.readStringHash();
    std::string reason = packet.readString();
    
    std::map<StringHash, FileTransfer>::iterator i = mFileTransfers.find(nameHash);
    if (i == mFileTransfers.end())
    {
        LOGDEBUG("Received fail for nonexisting file transfer " + toString(nameHash));
        return;
    }
    
    std::string errorMsg = "Transfer of file " + toString(nameHash) + " failed: " + reason;
    LOGINFO(errorMsg);
    
    using namespace FileTransferFailed;
    
    VariantMap eventData;
    eventData[P_FILENAME] = i->second.mFileName;
    eventData[P_REASON] = reason;
    sendEvent(EVENT_FILETRANSFERFAILED, eventData);
    
    mFileTransfers.erase(i);
}

void Client::handleJoinReply(VectorBuffer& packet)
{
    if (!mScene)
        return;
    
    bool success = packet.readBool();
    if (success)
    {
        std::string userName = packet.readString(); // Read back (possibly changed) username
        mServerConnection->setUserName(userName);
        mServerConnection->joinedScene();
        
        LOGINFO("Joined scene " + mScene->getName() + " with username " + userName);
        
        sendEvent(EVENT_JOINEDSCENE);
    }
    else
    {
        std::string reason = packet.readString();
        
        mServerConnection->leftScene();
        mPendingDownloads.clear();
        mFileTransfers.clear();
        
        joinFailed(reason);
    }
}

void Client::handleFullUpdate(VectorBuffer& packet)
{
    handleServerUpdate(packet, true);
}

void Client::handleServerUpdate(VectorBuffer& packet, bool initial)
{
    if (!isJoined())
        return;
    
    // Read frame numbers and physics sync information
    unsigned short lastFrameNumber = packet.readUShort();
    unsigned short lastFrameAck = packet.readUShort();
    float physicsTimeAcc = packet.readFloat();
    PhysicsWorld* world = mScene->getExtension<PhysicsWorld>();
    if (world)
        world->setTimeAccumulator(physicsTimeAcc);
    
    if (!initial)
    {
        // Check that this packet is not older than the last received (overlap may occur when we transition
        // between a reliable full update and unreliable delta updates)
        if (!checkFrameNumber(lastFrameNumber, mServerConnection->getFrameNumber()))
            return;
        //LOGINFO("Delta: " + toString(packet.getSize()));
    }
    else
    {
        // If initial/full update, remove all old proxy entities
        mScene->removeAllEntities(NET_PROXY);
        LOGINFO("Initial scene: " + toString(packet.getSize()) + " bytes");
    }
    
    mServerConnection->setFrameNumbers(lastFrameNumber, lastFrameAck);
    mServerConnection->updateRoundTripTime(mNetFps, mFrameNumber);
    
    unsigned short previousEventFrameNumber = mServerConnection->getEventFrameNumber();
    
    NetUpdateInfo info;
    info.mConnection = mServerConnection;
    info.mFrameNumber = mFrameNumber;
    info.mFrameAck = mServerConnection->getFrameAck();
    info.mRemoteFrameNumber = mServerConnection->getFrameNumber();
    info.mRoundTripTime = mServerConnection->getRoundTripTime();
    
    std::set<EntityID> updatedEntities;
    
    // Restore predicted entities' state to the last one we got from server
    mScene->restorePredictedEntities();
    
    // Read the actual scene update messages
    while (!packet.isEof())
    {
        unsigned char msgID = packet.readUByte();
        switch (msgID & 0x0f)
        {
        case MSG_CREATEENTITY:
        case MSG_REMOVEENTITY:
        case MSG_UPDATEENTITY:
            readNetUpdateBlock(packet, msgID, info, updatedEntities);
            break;
            
        case MSG_REMOTEEVENT:
            {
                RemoteEvent newEvent;
                newEvent.read(packet, false);
                if (mServerConnection->checkRemoteEventFrame(newEvent, previousEventFrameNumber))
                    newEvent.dispatch(mServerConnection, mScene);
            }
            break;
            
        case MSG_REMOTEENTITYEVENT:
            {
                RemoteEvent newEvent;
                newEvent.read(packet, true);
                if (mServerConnection->checkRemoteEventFrame(newEvent, previousEventFrameNumber))
                    newEvent.dispatch(mServerConnection, mScene);
            }
            break;
            
        default:
            LOGWARNING("Unknown message ID " + toString((int)msgID) + " received from server");
            packet.seek(packet.getSize()); // Break loop
            break;
        }
    }
    
    // Perform post-update for entities
    for (std::set<EntityID>::iterator i = updatedEntities.begin(); i != updatedEntities.end(); ++i)
    {
        Entity* entity = mScene->getEntity(*i);
        if (entity)
            entity->postNetUpdate(mCache);
    }
    
    // Store predicted entities' state for later recall
    mScene->storePredictedEntities();
    
    // If initial update, send back ack
    if (initial)
    {
        VectorBuffer replyPacket;
        replyPacket.writeUByte(MSG_FULLUPDATEACK);
        replyPacket.writeUInt(mServerConnection->getResponse());
        replyPacket.writeUShort(mFrameNumber);
        replyPacket.writeUShort(mServerConnection->getFrameNumber());
        mServerConnection->sendReliable(replyPacket);
        mServerConnection->updateResponse();
        mServerConnection->setJoinState(JS_SENDDELTAS);
    }
    
    // Remove acked controls
    mServerConnection->purgeAckedControls();
    
    // Run scene playback to overcome latency
    replayControls();
}

void Client::replayControls()
{
    float netPeriod = 1.0f / mNetFps;
    float roundTripTime = mServerConnection->getRoundTripTime();
    float totalTime = 0.0f;
    float maxTime = min(roundTripTime, mMaxPredictionTime);
    
    // If total RTT is less than one client/server frame, do not replay
    if (roundTripTime < netPeriod)
        return;
    
    PROFILE(Client_ReplayControls);
    
    // Replay old controls to counteract network latency
    // Note: index 0 is the last acked client update, so unacked controls start from index 1
    std::vector<std::pair<unsigned short, Controls> >& unackedControls = mServerConnection->getUnackedControls();
    mScene->setPlayback(true);
    
    for (unsigned i = 0; i < unackedControls.size(); ++i)
    {
        float timeStep = netPeriod;
        
        // Run all controls for the full time step, except the last for the amount of accumulated time since last client update
        if (i == unackedControls.size() - 1)
            timeStep = clamp(mTimeAcc, M_EPSILON, netPeriod);
        // Check for predicting too much (risk of lag due to CPU usage)
        if (totalTime + timeStep > maxTime)
            timeStep = max(maxTime - totalTime, 0.0f);
        
        const Controls& controls = unackedControls[i].second;
        
        using namespace ControlsPlayback;
        
        VariantMap eventData;
        eventData = controls.mExtraData;
        eventData[P_SCENE] = (void*)mScene.getPtr();
        eventData[P_TIMESTEP] = timeStep;
        eventData[P_BUTTONS] = controls.mButtons;
        eventData[P_YAW] = controls.mYaw;
        eventData[P_PITCH] = controls.mPitch;
        
        // Send the controls playback event, so that the application can inject the controls into the entity being controlled
        sendEvent(EVENT_CONTROLSPLAYBACK, eventData);
        
        // Then run the scene in controls playback mode
        if ((i > 0) && (timeStep > 0.0f))
        {
            mScene->update(timeStep);
            totalTime += timeStep;
        }
    }
    
    mScene->setPlayback(false);
}

unsigned Client::checkPackages()
{
    mPendingDownloads.clear();
    
    // To avoid resource version conflicts and to keep the amount of open packages reasonable, remove all existing
    // downloaded packages from the resource cache first
    std::vector<std::string> downloadedPackages = scanDirectory(mDownloadDirectory, "*.pak", false);
    std::vector<SharedPtr<PackageFile> > registeredPackages = mCache->getPackageFiles();
    for (std::vector<SharedPtr<PackageFile> >::iterator i = registeredPackages.begin(); i != registeredPackages.end();)
    {
        if ((*i)->getName().find(mDownloadDirectory) != std::string::npos)
        {
            mCache->removePackageFile(*i);
            i = registeredPackages.erase(i);
        }
        else
            ++i;
    }
    
    for (unsigned i = 0; i < mSceneInfo.mRequiredPackages.size(); ++i)
    {
        const PackageInfo& required = mSceneInfo.mRequiredPackages[i];
        std::string requiredName = getFileName(required.mName);
        bool found = false;
        
        // Check both already registered packages, and existing downloads
        for (unsigned j = 0; j < registeredPackages.size(); ++j)
        {
            PackageFile* package = registeredPackages[i];
            std::string name = getFileName(package->getName());
            if ((name.find(requiredName) != std::string::npos) && (package->getTotalSize() == required.mSize) &&
                (package->getChecksum() == required.mChecksum))
            {
                found = true;
                break;
            }
        }
        
        if (!found)
        {
            for (unsigned j = 0; j < downloadedPackages.size(); ++j)
            {
                // Downloaded packages are encoded as filename_checksum.pak, so check if the filename contains the required name
                std::string name = getFileName(downloadedPackages[i]);
                if (name.find(requiredName) != std::string::npos)
                {
                    try
                    {
                        SharedPtr<PackageFile> file(new PackageFile(mDownloadDirectory + downloadedPackages[i]));
                        if ((file->getTotalSize() == required.mSize) && (file->getChecksum() == required.mChecksum))
                        {
                            // Add the package as first in case it overrides something in the default files
                            mCache->addPackageFile(file, true);
                            found = true;
                            break;
                        }
                    }
                    catch (...)
                    {
                    }
                }
            }
        }
        
        if (!found)
        {
            // If not found, initiate the download
            if (!requestFile(required.mName, required.mSize, required.mChecksum))
            {
                joinFailed("Failed to initiate transfer for file " + required.mName);
                return M_MAX_UNSIGNED; // Return nonzero to prevent immediate join attempt
            }
            mPendingDownloads.insert(required.mName);
        }
    }
    
    return mPendingDownloads.size();
}

bool Client::requestFile(const std::string& fileName, unsigned size, unsigned checksum)
{
    // Register hash reverse mapping so that error messages will be intelligible
    registerHash(fileName);
    StringHash nameHash(fileName);
    if (mFileTransfers.find(nameHash) != mFileTransfers.end())
        return true; // Already initiated
    
    FileTransfer newTransfer;
    try
    {
        // Append checksum to download name, so that we can have several versions of a package
        std::string destName = getFileName(fileName) + "_" + toStringHex(checksum) + getExtension(fileName);
        newTransfer.mFile = new File(mDownloadDirectory + destName, FILE_WRITE);
    }
    catch (...)
    {
        return false;
    }
    newTransfer.mFileName = fileName;
    newTransfer.mSize = size;
    newTransfer.mChecksum = checksum;
    newTransfer.mNumFragments = (size - 1) / FILE_FRAGMENT_SIZE + 1;
    newTransfer.mBatchTimer.reset();
    newTransfer.mReceiveTimer.reset();
    newTransfer.mBatchSize = MIN_FILE_FRAGMENT_COUNT;
    
    VectorBuffer packet;
    packet.writeUByte(MSG_REQUESTFILE);
    packet.writeUInt(mServerConnection->getResponse());
    packet.writeStringHash(nameHash);
    packet.writeVLE(newTransfer.mBatchStart);
    packet.writeVLE(newTransfer.mBatchSize);
    mServerConnection->sendReliable(packet);
    mServerConnection->updateResponse();
    
    mFileTransfers[nameHash] = newTransfer;
    LOGINFO("Started transfer of file " + fileName + ", " + toString(size) + " bytes");
    return true;
}

void Client::setupSceneAndJoin()
{
    mNetFps = mSceneInfo.mNetFps;
    mTimeAcc = 0.0f;
    
    // Setup the scene according to the received properties
    // If no filename, just empty the scene and setup octree/physics/interpolation
    if (mSceneInfo.mFileName.empty())
    {
        mSceneInfo.mSceneProperties.seek(0);
        mScene->setName(mSceneInfo.mName);
        mScene->removeAllEntities();
        mScene->loadProperties(mSceneInfo.mSceneProperties);
    }
    else
    {
        try
        {
            SharedPtr<File> sceneFile = mCache->getFile(mSceneInfo.mFileName);
            // Support either binary or XML format scene
            if (getExtension(mSceneInfo.mFileName) == ".xml")
                mScene->loadXML(*sceneFile);
            else
                mScene->load(*sceneFile);
        }
        catch (...)
        {
            joinFailed("Failed to load scene " + mSceneInfo.mFileName);
            return;
        }
    }
    
    VectorBuffer packet;
    packet.writeUByte(MSG_JOINSCENE);
    packet.writeUInt(mServerConnection->getResponse());
    packet.writeUInt(mScene->getChecksum());
    mServerConnection->sendReliable(packet);
    mServerConnection->updateResponse();
}

void Client::joinFailed(const std::string& reason)
{
    LOGINFO("Failed to join scene, reason: " + reason);
    
    using namespace JoinSceneFailed;
    
    VariantMap eventData;
    eventData[P_REASON] = reason;
    sendEvent(EVENT_JOINSCENEFAILED);
}

void Client::sendClientUpdate()
{
    if (!isJoined())
    {
        // If we are not connected but remote events have been queued, clear them
        if (mScene)
            mScene->clearQueuedRemoteEvents();
        return;
    }
    
    // Request updated controls from the application
    using namespace ControlsUpdate;
    
    VariantMap eventData;
    eventData[P_SCENE] = (void*)mScene.getPtr();
    sendEvent(EVENT_CONTROLSUPDATE, eventData);
    
    // Purge acked and expired remote events
    mServerConnection->purgeAckedRemoteEvents(mFrameNumber);
    
    // Check new outgoing remote events, assign them framenumbers, and put to unacked queue
    // (note: as we can only send events to the server, the receiver field in the event is ignored)
    std::vector<RemoteEvent>& outEvents = mScene->getQueuedRemoteEvents();
    for (std::vector<RemoteEvent>::iterator i = outEvents.begin(); i != outEvents.end();)
    {
        if (i->mDelay <= 0.0f)
        {
            i->mFrameNumber = mFrameNumber;
            mServerConnection->addRemoteEvent(*i);
            i = outEvents.erase(i);
        }
        else
            ++i;
    }
    
    static VectorBuffer packet;
    packet.resize(0);
    packet.writeUShort(mFrameNumber);
    packet.writeUShort(mServerConnection->getFrameNumber());
    
    // Write controls and position
    const Controls& controls = mServerConnection->getControls();
    packet.writeUByte(MSG_CONTROLS);
    packet.writeUInt(controls.mButtons);
    packet.writeFloat(controls.mYaw);
    packet.writeFloat(controls.mPitch);
    packet.writeVariantMap(controls.mExtraData);
    packet.writeVector3(mServerConnection->getPosition());
    
    // Remember the controls for later replay
    mServerConnection->addUnackedControls(mFrameNumber, controls);
    
    // Append unacked remote events
    const std::vector<RemoteEvent>& unackedEvents = mServerConnection->getUnackedRemoteEvents();
    for (std::vector<RemoteEvent>::const_iterator i = unackedEvents.begin(); i != unackedEvents.end(); ++i)
    {
        packet.writeUByte(i->mEntityID ? MSG_REMOTEENTITYEVENT : MSG_REMOTEEVENT);
        i->write(packet);
    }
    
    mServerConnection->sendUnreliable(packet);
}

void Client::readNetUpdateBlock(Deserializer& source, unsigned char msgID, const NetUpdateInfo& info, std::set<EntityID>& updatedEntities)
{
    EntityID id = source.readUShort();
    Entity* entity = mScene->getEntity(id);
    
    switch (msgID & 0x0f)
    {
    case MSG_CREATEENTITY:
        {
            // Entity may already exist if server sends the create many times. But data may have changed
            std::string name = source.readString();
            if (!entity)
                entity = mScene->createEntity(id, name);
            
            unsigned char netFlags = source.readUByte();
            entity->setNetFlags(netFlags);
            if (netFlags & NET_OWNER)
                entity->setOwner(mServerConnection);
            else
                entity->setOwner(0);
            
            entity->setProperties(source.readVariantMap(), true);
            
            static std::set<Component*> extraComponents;
            extraComponents.clear();
            const std::vector<SharedPtr<Component> >& components = entity->getComponents();
            for (std::vector<SharedPtr<Component> >::const_iterator i = components.begin(); i != components.end(); ++i)
                extraComponents.insert(*i);
            
            unsigned numComponents = source.readVLE();
            for (unsigned i = 0; i < numComponents; ++i)
            {
                ShortStringHash type = source.readShortStringHash();
                std::string name = source.readString();
                // We might apply the same update multiple times, so check if the component already exists
                Component* component = entity->getComponent(type, name);
                bool newComponent = false;
                if (!component)
                {
                    component = entity->createComponent(type, name);
                    newComponent = true;
                }
                component->setNetFlags(source.readUByte());
                component->readNetUpdate(source, mCache, info);
                // If component is new, finish interpolation immediately
                if (newComponent)
                    component->interpolate(true);
                
                extraComponents.erase(component);
            }
            
            // Now check if the entity has extra components it should not, and remove them
            for (std::set<Component*>::iterator i = extraComponents.begin(); i != extraComponents.end(); ++i)
                entity->removeComponent(*i);
            
            updatedEntities.insert(id);
        }
        break;
        
    case MSG_REMOVEENTITY:
        if (entity)
            mScene->removeEntity(id);
        break;
        
    case MSG_UPDATEENTITY:
        {
            // Entity should exist, but if it does not, create it now to not desync the stream
            if (!entity)
            {
                LOGERROR("Update to nonexisting entity " + toString(id));
                entity = mScene->createEntity(id);
            }
            if (msgID & UPD_PROPERTIES)
            {
                unsigned numProperties = source.readVLE();
                for (unsigned i = 0; i < numProperties; ++i)
                {
                    ShortStringHash key = source.readShortStringHash();
                    Variant value = source.readVariant();
                    entity->setProperty(key, value, true);
                }
            }
            if (msgID & UPD_NEWCOMPONENTS)
            {
                unsigned numComponents = source.readVLE();
                for (unsigned i = 0; i < numComponents; ++i)
                {
                    ShortStringHash type = source.readShortStringHash();
                    std::string name = source.readString();
                    // We might apply the same update multiple times, so check if the component already exists
                    Component* component = entity->getComponent(type, name);
                    bool newComponent = false;
                    if (!component)
                    {
                        component = entity->createComponent(type, name);
                        newComponent = true;
                    }
                    component->setNetFlags(source.readUByte());
                    component->readNetUpdate(source, mCache, info);
                    // If component is new, finish interpolation immediately
                    if (newComponent)
                        component->interpolate(true);
                }
            }
            if (msgID & UPD_REMOVECOMPONENTS)
            {
                unsigned numComponents = source.readVLE();
                for (unsigned i = 0; i < numComponents; ++i)
                {
                    Component* component = entity->getComponent(source.readShortStringHash().mData);
                    if (component)
                        entity->removeComponent(component);
                }
            }
            if (msgID & UPD_UPDATECOMPONENTS)
            {
                unsigned numComponents = source.readVLE();
                for (unsigned i = 0; i < numComponents; ++i)
                {
                    ShortStringHash combinedHash = source.readShortStringHash();
                    Component* component = entity->getComponent(combinedHash.mData);
                    if (component)
                        component->readNetUpdate(source, mCache, info);
                    else
                    {
                        // Component should exist, but if it does not, create it now to not desync the stream
                        // Note that we only have the combined hash to go on with, and we may guess the type
                        // wrong, in that case an exception will be thrown
                        LOGERROR("Update to nonexisting component " + toString(combinedHash) + " in entity " +
                            entity->getName());
                        component = entity->createComponent(combinedHash);
                        component->readNetUpdate(source, mCache, info);
                        component->interpolate(true);
                    }
                }
            }
            updatedEntities.insert(id);
        }
        break;
    }
}
