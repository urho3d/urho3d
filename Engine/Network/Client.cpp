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
#include "FileSystem.h"
#include "Log.h"
#include "Network.h"
#include "NetworkEvents.h"
#include "PackageFile.h"
#include "ProcessUtils.h"
#include "Profiler.h"
#include "Protocol.h"
#include "ProtocolEvents.h"
#include "ResourceCache.h"
#include "Scene.h"
#include "SceneEvents.h"
#include "StringUtils.h"

#include "DebugNew.h"

static const Controls noControls;
static const int MIN_FILE_FRAGMENT_COUNT = 16;
static const int MAX_FILE_FRAGMENT_COUNT = 1024;
static const int FILE_FRAGMENT_COUNT_DELTA = 8;

OBJECTTYPESTATIC(Client);

Client::Client(Context* context) :
    Object(context),
    netFps_(30),
    timeAcc_(0.0f),
    frameNumber_(1)
{
    SubscribeToEvent(E_PEERDISCONNECTED, HANDLER(Client, HandlePeerDisconnected));
    SubscribeToEvent(E_FILETRANSFERCOMPLETED, HANDLER(Client, HandleFileTransferCompleted));
    SubscribeToEvent(E_FILETRANSFERFAILED, HANDLER(Client, HandleFileTransferFailed));
    SubscribeToEvent(E_ASYNCLOADFINISHED, HANDLER(Client, HandleAsyncLoadFinished));
}

Client::~Client()
{
}

void Client::SetScene(Scene* scene)
{
    scene_ = scene;
}

void Client::SetDownloadDirectory(const String& path)
{
    downloadDirectory_ = AddTrailingSlash(path);
}

bool Client::Connect(const String& address, unsigned short port, const VariantMap& loginData)
{
    if (!scene_)
        return false;
    
    // Make sure any previous async loading is stopped
    scene_->StopAsyncLoading();
    
    Disconnect();
    
    Peer* peer = GetSubsystem<Network>()->Connect(address, port);
    if (!peer)
        return false;
    
    serverConnection_ = new Connection(context_, peer);
    frameNumber_ = 1;
    pendingLoginData_ = loginData;
    return true;
}

void Client::Disconnect()
{
    if (serverConnection_)
    {
        serverConnection_->Disconnect();
        serverConnection_.Reset();
    }
    
    // Stop async loading if was in progress
    if (!scene_)
        scene_->StopAsyncLoading();
    
    pendingDownloads_.Clear();
    fileTransfers_.Clear();
    sceneInfo_ = SceneInfo();
}

void Client::SetControls(const Controls& controls)
{
    if (serverConnection_)
        serverConnection_->SetControls(controls);
}

void Client::SetPosition(const Vector3& position)
{
    if (serverConnection_)
        serverConnection_->SetPosition(position);
}

void Client::Update(float timeStep)
{
    PROFILE(UpdateClient);
    
    // Process connection (assume that Engine has updated Network, so we do not do that here)
    if (serverConnection_)
    {
        VectorBuffer packet;
        
        // Process reliable packets first, then unreliable
        while (serverConnection_->ReceiveReliable(packet))
            HandleReliablePacket(packet);
        
        while (serverConnection_->ReceiveUnreliable(packet))
            HandleServerUpdate(packet);
        
        // Update own simulation of scene if connected
        if (serverConnection_->GetScene() == scene_)
            scene_->Update(timeStep);
    }
    
    // Send update if enough time passed
    float netPeriod = 1.0f / netFps_;
    timeAcc_ += timeStep;
    if (timeAcc_ >= netPeriod)
    {
        // If multiple updates have accumulated because of a slow frame, send just one
        while (timeAcc_ >= netPeriod)
            timeAcc_ -= netPeriod;
        ++frameNumber_;
        // We have a policy that framenumber 0 means "frame never received", so loop back to 1
        if (!frameNumber_)
            ++frameNumber_;
        SendClientUpdate();
    }
}

bool Client::IsConnected() const
{
    return (serverConnection_) && (serverConnection_->IsConnected()) && (serverConnection_->HasChallenge());
}

bool Client::IsJoinPending() const
{
    return ((IsConnected()) && (serverConnection_->GetJoinState() == JS_PREPARESCENE));
}

bool Client::IsJoined() const
{
    return ((IsConnected()) && (serverConnection_->GetJoinState() > JS_PREPARESCENE));
}

const Controls& Client::GetControls() const
{
    if (!serverConnection_)
        return noControls;
    return serverConnection_->GetControls();
}

const Vector3& Client::GetPosition() const
{
    if (!serverConnection_)
        return Vector3::ZERO;
    return serverConnection_->GetPosition();
}

String Client::GetFileTransferStatus() const
{
    String ret;
    
    for (Map<StringHash, FileTransfer>::ConstIterator i = fileTransfers_.Begin(); i != fileTransfers_.End(); ++i)
    {
        String line = i->second_.fileName_ + " " + ToString(i->second_.bytesReceived_) + "/" + ToString(i->second_.size_) 
            + " (" + ToString((int)(((float)i->second_.bytesReceived_ / (float)i->second_.size_) * 100.0f + 0.5f)) + "%)\n";
        ret += line;
    }
    
    return ret;
}

void Client::HandlePeerDisconnected(StringHash eventType, VariantMap& eventData)
{
    using namespace PeerDisconnected;
    
    Peer* peerPtr = static_cast<Peer*>(eventData[P_PEER].GetPtr());
    if (peerPtr->GetType() != PEER_SERVER)
        return;
    
    if (serverConnection_)
    {
        if (serverConnection_->GetPeer() == peerPtr)
        {
            serverConnection_->LeftScene();
            serverConnection_.Reset();
            pendingDownloads_.Clear();
            fileTransfers_.Clear();
            sceneInfo_ = SceneInfo();
        }
    }
}

void Client::HandleFileTransferCompleted(StringHash eventType, VariantMap& eventData)
{
    using namespace FileTransferCompleted;
    
    String fileName = eventData[P_FILENAME].GetString();
    if (pendingDownloads_.Find(fileName) != pendingDownloads_.End())
    {
        pendingDownloads_.Erase(fileName);
        
        // Add the package to the resource cache
        SharedPtr<PackageFile> package(new PackageFile(context_));
        if (!package->Open(eventData[P_FULLPATH].GetString()))
        {
            JoinFailed("Could not open downloaded package file " + fileName);
            return;
        }
        // Add the package as first in case it overrides something in the default files
        GetSubsystem<ResourceCache>()->AddPackageFile(package, true);
        
        // If this was the last required download, can now join scene
        if ((pendingDownloads_.Empty()) && (IsJoinPending()))
            SetupScene();
    }
}

void Client::HandleFileTransferFailed(StringHash eventType, VariantMap& eventData)
{
    using namespace FileTransferFailed;
    
    String fileName = eventData[P_FILENAME].GetString();
    if (pendingDownloads_.Find(fileName) != pendingDownloads_.End())
        JoinFailed("Failed to transfer file " + fileName);
}

void Client::HandleAsyncLoadFinished(StringHash eventType, VariantMap& eventData)
{
    if ((!scene_) || (!serverConnection_))
        return;
    
    using namespace AsyncLoadFinished;
    
    // If it is the scene used for networking, send join packet now
    if ((eventData[P_SCENE].GetPtr() == (void*)scene_) && (serverConnection_->GetJoinState() == JS_LOADSCENE))
        SendJoinScene();
}

void Client::HandleReliablePacket(VectorBuffer& packet)
{
    unsigned char msgID = 0;
    
    msgID = packet.ReadUByte();
    
    switch (msgID)
    {
    case MSG_CHALLENGE:
        HandleChallenge(packet);
        break;
        
    case MSG_SCENEINFO:
        HandleSceneInfo(packet);
        break;
        
    case MSG_TRANSFERDATA:
        HandleTransferData(packet);
        break;
        
    case MSG_TRANSFERFAILED:
        HandleTransferFailed(packet);
        break;
        
    case MSG_JOINREPLY:
        HandleJoinReply(packet);
        break;
        
    case MSG_FULLUPDATE:
        HandleFullUpdate(packet);
        break;
        
    default:
        LOGERROR("Unknown message ID " + ToString((int)msgID) + " received from server");
        break;
    }
}

void Client::HandleChallenge(VectorBuffer& packet)
{
    serverConnection_->SetChallenge(packet.ReadUInt());
    
    // Send login packet as a response
    VectorBuffer replyPacket;
    replyPacket.WriteUByte(MSG_LOGIN);
    replyPacket.WriteVariantMap(pendingLoginData_);
    serverConnection_->SendReliable(replyPacket);
}

void Client::HandleSceneInfo(VectorBuffer& packet)
{
    if (!scene_)
        return;
    
    // Stop all previous loading, associate the scene with the connection
    scene_->StopAsyncLoading();
    serverConnection_->SetScene(scene_);
    
    // Read scene name, number of users and update rate
    String sceneName = packet.ReadString();
    sceneInfo_.name_ = sceneName;
    sceneInfo_.numUsers_ = packet.ReadVLE();
    sceneInfo_.netFps_ = packet.ReadInt();
    
    // Read source file name & required packages
    sceneInfo_.fileName_ = packet.ReadString();
    unsigned numPackages = packet.ReadVLE();
    sceneInfo_.requiredPackages_.Clear();
    for (unsigned i = 0; i < numPackages; ++i)
    {
        PackageInfo package;
        package.name_ = packet.ReadString();
        package.size_ = packet.ReadUInt();
        package.checksum_ = packet.ReadUInt();
        sceneInfo_.requiredPackages_.Push(package);
    }
    
    // Check need for downloads: if none, can join immediately
    if (!CheckPackages())
        SetupScene();
}

void Client::HandleTransferData(VectorBuffer& packet)
{
    StringHash nameHash = packet.ReadStringHash();
    Map<StringHash, FileTransfer>::Iterator i = fileTransfers_.Find(nameHash);
    if (i == fileTransfers_.End())
    {
        LOGDEBUG("Received fragment for nonexisting file transfer " + ToString(nameHash));
        return;
    }
    FileTransfer& transfer = i->second_;
    
    unsigned index = packet.ReadVLE();
    if (transfer.fragmentsReceived_ != index)
    {
        LOGERROR("Received unexpected fragment for file " + ToString(nameHash) + ", stopping transfer");
        
        using namespace FileTransferFailed;
        
        VariantMap eventData;
        eventData[P_FILENAME] = transfer.fileName_;
        eventData[P_REASON] = "Unexpected fragment";
        SendEvent(E_FILETRANSFERFAILED, eventData);
        
        fileTransfers_.Erase(i);
        return;
    }
    
    transfer.fragmentsReceived_ = index + 1; // We receive fragments in order
    unsigned dataSize = packet.GetSize() - packet.GetPosition();
    transfer.file_->Write(packet.GetData() + packet.GetPosition(), dataSize);
    transfer.bytesReceived_ += dataSize;
    
    if (transfer.fragmentsReceived_ == transfer.numFragments_)
    {
        if (transfer.bytesReceived_ != transfer.size_)
        {
            LOGERROR("Transfer of file " + transfer.fileName_ + " finished, expected " + ToString(transfer.size_) +
                " bytes but got " + ToString(transfer.bytesReceived_));
            
            using namespace FileTransferFailed;
            
            VariantMap eventData;
            eventData[P_FILENAME] = transfer.fileName_;
            eventData[P_REASON] = "Unexpected file size";
            SendEvent(E_FILETRANSFERFAILED, eventData);
        }
        else
        {
            float totalTime = transfer.receiveTimer_.GetMSec(true) * 0.001f;
            LOGINFO("Transfer of file " + transfer.fileName_ + " completed in " +
                ToString(totalTime) + " seconds, speed " + ToString(transfer.size_ / totalTime) + " bytes/sec");
            using namespace FileTransferCompleted;
            
            VariantMap eventData;
            eventData[P_FILENAME] = transfer.fileName_;
            eventData[P_FULLPATH] = transfer.file_->GetName();
            
            // Others might try to use the file as a response to the event, so close it first
            transfer.file_.Reset();
            
            SendEvent(E_FILETRANSFERCOMPLETED, eventData);
        }
        
        fileTransfers_.Erase(i);
        return;
    }
    
    // If current batch was finished, fire off the next
    if (transfer.fragmentsReceived_ == transfer.batchStart_ + transfer.batchSize_)
    {
        transfer.batchStart_ = transfer.fragmentsReceived_;
        float batchTime = transfer.batchTimer_.GetMSec(true) * 0.001f;
        float newDataRate = transfer.batchSize_ * FILE_FRAGMENT_SIZE / batchTime;
        LOGDEBUG("Received " + ToString(transfer.batchSize_) + " fragments in " + ToString(batchTime) + " seconds");
        
        // If this was the first batch, can not yet estimate speed, so go up in batch size
        if (!transfer.lastBatchSize_)
        {
            transfer.lastBatchSize_ = transfer.batchSize_;
            transfer.lastDataRate_ = newDataRate;
            transfer.batchSize_ += FILE_FRAGMENT_COUNT_DELTA;
        }
        else
        {
            bool goUp = true;
            // Go down in batch size if last batch was smaller and had better data rate
            if ((transfer.lastBatchSize_ < transfer.batchSize_) && (transfer.lastDataRate_ > newDataRate))
                goUp = false;
            
            transfer.lastBatchSize_ = transfer.batchSize_;
            transfer.lastDataRate_ = newDataRate;
            
            if (goUp)
                transfer.batchSize_ += FILE_FRAGMENT_COUNT_DELTA;
            else
                transfer.batchSize_ -= FILE_FRAGMENT_COUNT_DELTA;
            
            transfer.batchSize_ = Clamp((int)transfer.batchSize_, MIN_FILE_FRAGMENT_COUNT, MAX_FILE_FRAGMENT_COUNT);
        }
        
        VectorBuffer packet;
        packet.WriteUByte(MSG_REQUESTFILE);
        packet.WriteStringHash(i->first_);
        packet.WriteVLE(transfer.batchStart_);
        packet.WriteVLE(transfer.batchSize_);
        serverConnection_->SendReliable(packet);
    }
}

void Client::HandleTransferFailed(VectorBuffer& packet)
{
    StringHash nameHash = packet.ReadStringHash();
    String reason = packet.ReadString();
    
    Map<StringHash, FileTransfer>::Iterator i = fileTransfers_.Find(nameHash);
    if (i == fileTransfers_.End())
    {
        LOGDEBUG("Received fail for nonexisting file transfer " + ToString(nameHash));
        return;
    }
    
    String errorMsg = "Transfer of file " + ToString(nameHash) + " failed: " + reason;
    LOGINFO(errorMsg);
    
    using namespace FileTransferFailed;
    
    VariantMap eventData;
    eventData[P_FILENAME] = i->second_.fileName_;
    eventData[P_REASON] = reason;
    SendEvent(E_FILETRANSFERFAILED, eventData);
    
    fileTransfers_.Erase(i);
}

void Client::HandleJoinReply(VectorBuffer& packet)
{
    if (!scene_)
        return;
    
    bool success = packet.ReadBool();
    if (success)
    {
        serverConnection_->JoinedScene();
        
        LOGINFO("Joined scene " + scene_->GetName());
        
        SendEvent(E_JOINEDSCENE);
    }
    else
    {
        String reason = packet.ReadString();
        
        serverConnection_->LeftScene();
        pendingDownloads_.Clear();
        fileTransfers_.Clear();
        
        JoinFailed(reason);
    }
}

void Client::HandleFullUpdate(VectorBuffer& packet)
{
    HandleServerUpdate(packet, true);
}

void Client::HandleServerUpdate(VectorBuffer& packet, bool initial)
{
    if (!IsJoined())
        return;
    
    // Read frame numbers
    unsigned short lastFrameNumber = packet.ReadUShort();
    unsigned short lastFrameAck = packet.ReadUShort();
    
    if (!initial)
    {
        // Check that this packet is not older than the last received (overlap may occur when we transition
        // between a reliable full update and unreliable delta updates)
        if (!CheckFrameNumber(lastFrameNumber, serverConnection_->GetFrameNumber()))
            return;
        //LOGDEBUG("Delta: " + ToString(packet.GetSize()));
    }
    else
    {
        // If initial/full update, remove all old non-local nodes
        scene_->ClearNonLocal();
        LOGDEBUG("Initial scene: " + ToString(packet.GetSize()) + " bytes");
    }
    
    serverConnection_->SetFrameNumbers(lastFrameNumber, lastFrameAck);
    serverConnection_->UpdateRoundTripTime(netFps_, frameNumber_);
    
    unsigned short previousEventFrameNumber = serverConnection_->GetEventFrameNumber();
    
    Set<unsigned> updatedNodes;
    Set<unsigned> updatedComponents;
    
    // Read the actual scene update messages
    while (!packet.IsEof())
    {
        unsigned char msgID = packet.ReadUByte();
        switch (msgID & 0x0f)
        {
        case MSG_REMOTEEVENT:
            {
                RemoteEvent newEvent;
                newEvent.Read(packet, false);
                if (serverConnection_->CheckRemoteEventFrame(newEvent, previousEventFrameNumber))
                    newEvent.Dispatch(serverConnection_, scene_);
            }
            break;
            
        case MSG_REMOTENODEEVENT:
            {
                RemoteEvent newEvent;
                newEvent.Read(packet, true);
                if (serverConnection_->CheckRemoteEventFrame(newEvent, previousEventFrameNumber))
                    newEvent.Dispatch(serverConnection_, scene_);
            }
            break;
            
        default:
            LOGWARNING("Unknown message ID " + ToString((int)msgID) + " received from server");
            packet.Seek(packet.GetSize()); // Break loop
            break;
        }
    }
    
    // Perform post network update for nodes & components
    
    // If initial update, send back ack
    if (initial)
    {
        VectorBuffer replyPacket;
        replyPacket.WriteUByte(MSG_FULLUPDATEACK);
        replyPacket.WriteUShort(frameNumber_);
        replyPacket.WriteUShort(serverConnection_->GetFrameNumber());
        serverConnection_->SendReliable(replyPacket);
        serverConnection_->SetJoinState(JS_SENDDELTAS);
    }
    
    // Remove acked controls
    serverConnection_->PurgeAckedControls();
    
    // Send notification of the server update
    using namespace ServerUpdate;
    
    VariantMap eventData;
    eventData[P_SCENE] = (void*)scene_.GetPtr();
    SendEvent(E_SERVERUPDATE, eventData);
}

unsigned Client::CheckPackages()
{
    pendingDownloads_.Clear();
    
    // To avoid resource version conflicts and to keep the amount of open packages reasonable, remove all existing
    // downloaded packages from the resource cache first
    Vector<String> downloadedPackages;
    Vector<SharedPtr<PackageFile> > registeredPackages = GetSubsystem<ResourceCache>()->GetPackageFiles();
    GetSubsystem<FileSystem>()->ScanDir(downloadedPackages, downloadDirectory_, "*.pak", SCAN_FILES, false);
    
    for (Vector<SharedPtr<PackageFile> >::Iterator i = registeredPackages.Begin(); i != registeredPackages.End();)
    {
        if ((*i)->GetName().Find(downloadDirectory_) != String::NPOS)
        {
            GetSubsystem<ResourceCache>()->RemovePackageFile(*i);
            i = registeredPackages.Erase(i);
        }
        else
            ++i;
    }
    
    for (unsigned i = 0; i < sceneInfo_.requiredPackages_.Size(); ++i)
    {
        const PackageInfo& required = sceneInfo_.requiredPackages_[i];
        String requiredName = GetFileName(required.name_);
        bool found = false;
        
        // Check both already registered packages, and existing downloads
        for (unsigned j = 0; j < registeredPackages.Size(); ++j)
        {
            PackageFile* package = registeredPackages[i];
            String name = GetFileName(package->GetName());
            if ((name.Find(requiredName) != String::NPOS) && (package->GetTotalSize() == required.size_) &&
                (package->GetChecksum() == required.checksum_))
            {
                found = true;
                break;
            }
        }
        
        if (!found)
        {
            for (unsigned j = 0; j < downloadedPackages.Size(); ++j)
            {
                // Downloaded packages are encoded as filename_checksum.pak, so check if the filename contains the required name
                String name = GetFileName(downloadedPackages[i]);
                if (name.Find(requiredName) != String::NPOS)
                {
                    SharedPtr<PackageFile> file(new PackageFile(context_));
                    file->Open(downloadDirectory_ + downloadedPackages[i]);
                    if ((file->GetTotalSize() == required.size_) && (file->GetChecksum() == required.checksum_))
                    {
                        // Add the package as first in case it overrides something in the default files
                        GetSubsystem<ResourceCache>()->AddPackageFile(file, true);
                        found = true;
                        break;
                    }
                }
            }
        }
        
        if (!found)
        {
            // If not found, initiate the download
            if (!RequestFile(required.name_, required.size_, required.checksum_))
            {
                JoinFailed("Failed to initiate transfer for file " + required.name_);
                return M_MAX_UNSIGNED; // Return nonzero to prevent immediate join attempt
            }
            pendingDownloads_.Insert(required.name_);
        }
    }
    
    return pendingDownloads_.Size();
}

bool Client::RequestFile(const String& fileName, unsigned size, unsigned checksum)
{
    StringHash nameHash(fileName);
    if (fileTransfers_.Find(nameHash) != fileTransfers_.End())
        return true; // Already initiated
    
    FileTransfer newTransfer;
    // Append checksum to download name, so that we can have several versions of a package
    String destName = GetFileName(fileName) + "_" + ToStringHex(checksum) + GetExtension(fileName);
    newTransfer.file_ = new File(context_, downloadDirectory_ + destName, FILE_WRITE);
    if (!newTransfer.file_->IsOpen())
        return false;
    
    newTransfer.fileName_ = fileName;
    newTransfer.size_ = size;
    newTransfer.checksum_ = checksum;
    newTransfer.numFragments_ = (size - 1) / FILE_FRAGMENT_SIZE + 1;
    newTransfer.batchTimer_.Reset();
    newTransfer.receiveTimer_.Reset();
    newTransfer.batchSize_ = MIN_FILE_FRAGMENT_COUNT;
    
    VectorBuffer packet;
    packet.WriteUByte(MSG_REQUESTFILE);
    packet.WriteStringHash(nameHash);
    packet.WriteVLE(newTransfer.batchStart_);
    packet.WriteVLE(newTransfer.batchSize_);
    serverConnection_->SendReliable(packet);
    
    fileTransfers_[nameHash] = newTransfer;
    LOGINFO("Started transfer of file " + fileName + ", " + ToString(size) + " bytes");
    return true;
}

void Client::SetupScene()
{
    netFps_ = sceneInfo_.netFps_;
    timeAcc_ = 0.0f;
    
    // Setup the scene
    // If no filename, just empty it
    if (sceneInfo_.fileName_.Empty())
    {
        scene_->SetName(sceneInfo_.name_);
        scene_->Clear();
        SendJoinScene();
    }
    else
    {
        SharedPtr<File> sceneFile = GetSubsystem<ResourceCache>()->GetFile(sceneInfo_.fileName_);
        // Support either binary or XML format scene
        if (GetExtension(sceneInfo_.fileName_) == ".xml")
            scene_->LoadAsyncXML(sceneFile);
        else
            scene_->LoadAsync(sceneFile);
        
        // Check if scene started loading successfully
        if (scene_->IsAsyncLoading())
            serverConnection_->SetJoinState(JS_LOADSCENE);
        else
            JoinFailed("Failed to load scene " + sceneInfo_.fileName_);
    }
}

void Client::SendJoinScene()
{
    if ((!scene_) || (!serverConnection_))
        return;
    
    VectorBuffer packet;
    packet.WriteUByte(MSG_JOINSCENE);
    packet.WriteUInt(scene_->GetChecksum());
    serverConnection_->SendReliable(packet);
}

void Client::JoinFailed(const String& reason)
{
    LOGINFO("Failed to join scene, reason: " + reason);
    
    using namespace JoinSceneFailed;
    
    VariantMap eventData;
    eventData[P_REASON] = reason;
    SendEvent(E_JOINSCENEFAILED);
}

void Client::SendClientUpdate()
{
    if (!IsJoined())
    {
        // If we are not connected but remote events have been queued, clear them
        serverConnection_->ClearRemoteEvents();
        return;
    }
    
    // Request updated controls from the application
    using namespace ControlsUpdate;
    
    VariantMap eventData;
    eventData[P_SCENE] = (void*)scene_.GetPtr();
    SendEvent(E_CONTROLSUPDATE, eventData);
    
    // Purge acked and expired remote events
    serverConnection_->PurgeAckedRemoteEvents(frameNumber_);
    
    VectorBuffer packet;
    packet.WriteUShort(frameNumber_);
    packet.WriteUShort(serverConnection_->GetFrameNumber());
    
    // Write controls and position
    const Controls& controls = serverConnection_->GetControls();
    packet.WriteUByte(MSG_CONTROLS);
    packet.WriteUInt(controls.buttons_);
    packet.WriteFloat(controls.yaw_);
    packet.WriteFloat(controls.pitch_);
    packet.WriteVariantMap(controls.extraData_);
    packet.WriteVector3(serverConnection_->GetPosition());
    
    // Remember the controls if prediction & replay is needed
    serverConnection_->AddUnackedControls(frameNumber_, controls);
    
    // Append unacked remote events
    const Vector<RemoteEvent>& unackedEvents = serverConnection_->GetUnackedRemoteEvents();
    for (Vector<RemoteEvent>::ConstIterator i = unackedEvents.Begin(); i != unackedEvents.End(); ++i)
    {
        packet.WriteUByte(i->nodeID_ ? MSG_REMOTENODEEVENT : MSG_REMOTEEVENT);
        i->Write(packet);
    }
    
    serverConnection_->SendUnreliable(packet);
}

void Client::ReadNetUpdateBlock(Deserializer& source, unsigned char msgID, Set<unsigned>& updatedNodes, Set<unsigned>& updatedComponents)
{
    /*
    unsigned id = source.ReadUShort();
    Node* node = scene_->GetNodeByID(id);
    
    switch (msgID & 0x0f)
    {
    case MSG_CREATEENTITY:
        {
            // Node may already exist if server sends the create many times. But data may have changed
            String name = source.ReadString();
            if (!node)
                node = scene_->createNode(id, name);
            
            unsigned char netFlags = source.ReadUByte();
            node->setNetFlags(netFlags);
            if (netFlags & NET_OWNER)
                node->setOwner(serverConnection_);
            else
                node->setOwner(0);
            node->setGroupFlags(source.ReadVLE());
            
            node->setProperties(source.ReadVariantMap(), true);
            
            Set<Component*> extraComponents;
            extraComponents.Clear();
            const Vector<SharedPtr<Component> >& components = node->GetComponents();
            for (Vector<SharedPtr<Component> >::ConstIterator i = components.Begin(); i != components.End(); ++i)
                extraComponents.Insert(*i);
            
            unsigned nucomponents_ = source.ReadVLE();
            for (unsigned i = 0; i < nucomponents_; ++i)
            {
                ShortStringHash type = source.ReadShortStringHash();
                String name = source.ReadString();
                // We might apply the same update multiple times, so check if the component already exists
                Component* component = node->GetComponent(type, name);
                bool newComponent = false;
                if (!component)
                {
                    component = node->createComponent(type, name);
                    newComponent = true;
                }
                component->setNetFlags(source.ReadUByte());
                component->readNetUpdate(source, GetSubsystem<ResourceCache>(), info);
                // If component is new, finish interpolation immediately
                if (newComponent)
                    component->interpolate(true);
                
                extraComponents.Erase(component);
            }
            
            // Now check if the node has extra components it should not, and remove them
            for (Set<Component*>::Iterator i = extraComponents.Begin(); i != extraComponents.End(); ++i)
                node->removeComponent(*i);
            
            updatedNodes.Insert(id);
        }
        break;
        
    case MSG_REMOVEENTITY:
        if (node)
            scene_->removeNode(id);
        break;
        
    case MSG_UPDATEENTITY:
        {
            // Node should exist, but if it does not, create it now to not desync the stream
            if (!node)
            {
                LOGERROR("Update to nonexisting node " + ToString(id));
                node = scene_->createNode(id);
            }
            if (msgID & UPD_PROPERTIES)
            {
                unsigned numProperties = source.ReadVLE();
                for (unsigned i = 0; i < numProperties; ++i)
                {
                    ShortStringHash key = source.ReadShortStringHash();
                    Variant value = source.ReadVariant();
                    node->setProperty(key, value, true);
                }
            }
            if (msgID & UPD_NEWCOMPONENTS)
            {
                unsigned nucomponents_ = source.ReadVLE();
                for (unsigned i = 0; i < nucomponents_; ++i)
                {
                    ShortStringHash type = source.ReadShortStringHash();
                    String name = source.ReadString();
                    // We might apply the same update multiple times, so check if the component already exists
                    Component* component = node->GetComponent(type, name);
                    bool newComponent = false;
                    if (!component)
                    {
                        component = node->createComponent(type, name);
                        newComponent = true;
                    }
                    component->setNetFlags(source.ReadUByte());
                    component->readNetUpdate(source, GetSubsystem<ResourceCache>(), info);
                    // If component is new, finish interpolation immediately
                    if (newComponent)
                        component->interpolate(true);
                }
            }
            if (msgID & UPD_REMOVECOMPONENTS)
            {
                unsigned nucomponents_ = source.ReadVLE();
                for (unsigned i = 0; i < nucomponents_; ++i)
                {
                    Component* component = node->GetComponent(source.ReadShortStringHash().mData);
                    if (component)
                        node->removeComponent(component);
                }
            }
            if (msgID & UPD_UPDATECOMPONENTS)
            {
                unsigned nucomponents_ = source.ReadVLE();
                for (unsigned i = 0; i < nucomponents_; ++i)
                {
                    ShortStringHash combinedHash = source.ReadShortStringHash();
                    Component* component = node->GetComponent(combinedHash.mData);
                    if (component)
                        component->readNetUpdate(source, GetSubsystem<ResourceCache>(), info);
                    else
                    {
                        // Component should exist, but if it does not, create it now to not desync the stream
                        // Note that we only have the combined hash to go on with
                        LOGERROR("Update to nonexisting component " + ToString(combinedHash) + " in node " +
                            node->GetName());
                        component = node->createComponent(combinedHash);
                        component->readNetUpdate(source, GetSubsystem<ResourceCache>(), info);
                        component->interpolate(true);
                    }
                }
            }
            updatedNodes.Insert(id);
        }
        break;
    }
    */
}
