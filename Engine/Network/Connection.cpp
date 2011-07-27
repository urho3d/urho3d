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
#include "Component.h"
#include "Connection.h"
#include "File.h"
#include "FileSystem.h"
#include "Log.h"
#include "MemoryBuffer.h"
#include "Network.h"
#include "NetworkEvents.h"
#include "PackageFile.h"
#include "Profiler.h"
#include "Protocol.h"
#include "ResourceCache.h"
#include "Scene.h"
#include "SceneEvents.h"
#include "StringUtils.h"

#include <kNet.h>

#include "DebugNew.h"

static const String noName;

PackageDownload::PackageDownload() :
    totalFragments_(0),
    checksum_(0),
    initiated_(false)
{
}

OBJECTTYPESTATIC(Connection);

Connection::Connection(Context* context, bool isClient, kNet::SharedPtr<kNet::MessageConnection> connection) :
    Object(context),
    connection_(connection),
    frameNumber_(0),
    isClient_(isClient),
    connectPending_(false),
    sceneLoaded_(false)
{
}

Connection::~Connection()
{
    // Reset scene (remove possible owner references), as this connection is about to be destroyed
    SetScene(0);
}

void Connection::SendMessage(int msgID, bool reliable, bool inOrder, const VectorBuffer& msg)
{
    SendMessage(msgID, 0, reliable, inOrder, msg.GetData(), msg.GetSize());
}

void Connection::SendMessage(int msgID, bool reliable, bool inOrder, const unsigned char* data, unsigned numBytes)
{
    SendMessage(msgID, 0, reliable, inOrder, data, numBytes);
}

void Connection::SendMessage(int msgID, unsigned contentID, bool reliable, bool inOrder, const VectorBuffer& msg)
{
    SendMessage(msgID, contentID, reliable, inOrder, msg.GetData(), msg.GetSize());
}

void Connection::SendMessage(int msgID, unsigned contentID, bool reliable, bool inOrder, const unsigned char* data, unsigned numBytes)
{
    // Make sure not to use kNet internal message ID's
    if (msgID <= 0x4 || msgID >= 0x3ffffffe)
    {
        LOGERROR("Can not send message with reserved ID");
        return;
    }
    
    connection_->SendMessage(msgID, reliable, inOrder, DEFAULT_MSG_PRIORITY, contentID, (const char*)data, numBytes);
}

void Connection::SendRemoteEvent(StringHash eventType, bool inOrder, const VariantMap& eventData)
{
    if (!GetSubsystem<Network>()->CheckRemoteEvent(eventType))
    {
        LOGWARNING("Discarding not allowed remote event " + eventType.ToString());
        return;
    }
    
    RemoteEvent queuedEvent;
    queuedEvent.receiverID_ = 0;
    queuedEvent.eventType_ = eventType;
    queuedEvent.eventData_ = eventData;
    queuedEvent.inOrder_ = inOrder;
    remoteEvents_.Push(queuedEvent);
}

void Connection::SendRemoteEvent(Node* receiver, StringHash eventType, bool inOrder, const VariantMap& eventData)
{
    if (!GetSubsystem<Network>()->CheckRemoteEvent(eventType))
    {
        LOGWARNING("Discarding not allowed remote event " + eventType.ToString());
        return;
    }
    
    if (!receiver)
    {
        LOGERROR("Null node for remote node event");
        return;
    }
    if (receiver->GetScene() != scene_)
    {
        LOGERROR("Node is not in the connection's scene, can not send remote node event");
        return;
    }
    if (receiver->GetID() >= FIRST_LOCAL_ID)
    {
        LOGERROR("Node has a local ID, can not send remote node event");
        return;
    }
    
    RemoteEvent queuedEvent;
    queuedEvent.receiverID_ = receiver->GetID();
    queuedEvent.eventType_ = eventType;
    queuedEvent.eventData_ = eventData;
    queuedEvent.inOrder_ = inOrder;
    remoteEvents_.Push(queuedEvent);
}

void Connection::SetScene(Scene* newScene)
{
    if (scene_)
    {
        // Disable smoothing in case scene is no longer used for networking
        if (!isClient_)
            scene_->SetSmoothed(false);
        // Reset the owner reference from the previous scene's nodes
        scene_->ResetOwner(this);
    }
    
    scene_ = newScene;
    sceneLoaded_ = false;
    UnsubscribeFromEvent(E_ASYNCLOADFINISHED);
    
    if (!scene_)
        return;
    
    if (isClient_)
    {
        sceneState_.Clear();
        
        // When scene is assigned on the server, instruct the client to load it. This may require downloading packages
        const Vector<SharedPtr<PackageFile> >& packages = scene_->GetRequiredPackageFiles();
        unsigned numPackages = packages.Size();
        msg_.Clear();
        msg_.WriteString(scene_->GetFileName());
        msg_.WriteVLE(numPackages);
        for (unsigned i = 0; i < numPackages; ++i)
        {
            PackageFile* package = packages[i];
            msg_.WriteString(GetFileNameAndExtension(package->GetName()));
            msg_.WriteUInt(package->GetTotalSize());
            msg_.WriteUInt(package->GetChecksum());
        }
        SendMessage(MSG_LOADSCENE, true, true, msg_);
    }
    else
    {
        // Enable motion smoothing on the client network scene
        scene_->SetSmoothed(true);
        // Make sure there is no existing async loading
        scene_->StopAsyncLoading();
        SubscribeToEvent(scene_, E_ASYNCLOADFINISHED, HANDLER(Connection, HandleAsyncLoadFinished));
    }
}

void Connection::SetIdentity(const VariantMap& identity)
{
    identity_ = identity;
}

void Connection::SetControls(const Controls& newControls)
{
    previousControls_ = controls_;
    controls_ = newControls;
}

void Connection::SetConnectPending(bool connectPending)
{
    connectPending_ = connectPending;
}

void Connection::Disconnect(int waitMSec)
{
    connection_->Disconnect(waitMSec);
}

void Connection::SendServerUpdate()
{
    if (!isClient_ || !scene_ || !sceneLoaded_)
        return;
    
    PROFILE(SendServerUpdate);
    
    const Map<unsigned, Node*>& nodes = scene_->GetAllNodes();
    
    // Check for new or changed nodes
    // Start from the root node (scene) so that the scene-wide components get sent first
    processedNodes_.Clear();
    ProcessNode(scene_);
    
    // Then go through the rest of the nodes
    for (Map<unsigned, Node*>::ConstIterator i = nodes.Begin(); i != nodes.End() && i->first_ < FIRST_LOCAL_ID; ++i)
        ProcessNode(i->second_);
    
    // Check for removed nodes
    for (Map<unsigned, NodeReplicationState>::Iterator i = sceneState_.Begin(); i != sceneState_.End();)
    {
        Map<unsigned, NodeReplicationState>::Iterator current = i++;
        if (current->second_.frameNumber_ != frameNumber_)
        {
            msg_.Clear();
            msg_.WriteVLE(current->first_);
            
            SendMessage(MSG_REMOVENODE, true, true, msg_);
            sceneState_.Erase(current);
        }
    }
    
    ++frameNumber_;
}

void Connection::SendClientUpdate()
{
    if (isClient_ || !scene_ || !sceneLoaded_)
        return;
    
    PROFILE(SendClientUpdate);
    
    msg_.Clear();
    msg_.WriteUInt(controls_.buttons_);
    msg_.WriteFloat(controls_.yaw_);
    msg_.WriteFloat(controls_.pitch_);
    msg_.WriteVariantMap(controls_.extraData_);
    SendMessage(MSG_CONTROLS, CONTROLS_CONTENT_ID, false, false, msg_);
}

void Connection::SendQueuedRemoteEvents()
{
    if (remoteEvents_.Empty())
        return;
    
    for (Vector<RemoteEvent>::ConstIterator i = remoteEvents_.Begin(); i != remoteEvents_.End(); ++i)
    {
        msg_.Clear();
        if (!i->receiverID_)
        {
            msg_.WriteStringHash(i->eventType_);
            msg_.WriteVariantMap(i->eventData_);
            SendMessage(MSG_REMOTEEVENT, true, i->inOrder_, msg_);
        }
        else
        {
            msg_.WriteVLE(i->receiverID_);
            msg_.WriteStringHash(i->eventType_);
            msg_.WriteVariantMap(i->eventData_);
            SendMessage(MSG_REMOTENODEEVENT, true, i->inOrder_, msg_);
        }
    }
    
    remoteEvents_.Clear();
}

void Connection::ProcessPendingLatestData()
{
    if (!scene_)
        return;
    
    // Iterate through pending node data and see if we can find the nodes now
    for (Map<unsigned, PODVector<unsigned char> >::Iterator i = nodeLatestData_.Begin(); i != nodeLatestData_.End();)
    {
        Map<unsigned, PODVector<unsigned char> >::Iterator current = i++;
        Node* node = scene_->GetNodeByID(current->first_);
        if (node)
        {
            MemoryBuffer msg(current->second_);
            msg.ReadVLE(); // Skip the node ID
            node->ReadLatestDataUpdate(msg);
            nodeLatestData_.Erase(current);
        }
    }
    
    // Iterate through pending component data and see if we can find the components now
    for (Map<unsigned, PODVector<unsigned char> >::Iterator i = componentLatestData_.Begin(); i != componentLatestData_.End();)
    {
        Map<unsigned, PODVector<unsigned char> >::Iterator current = i++;
        Component* component = scene_->GetComponentByID(current->first_);
        if (component)
        {
            MemoryBuffer msg(current->second_);
            msg.ReadVLE(); // Skip the component ID
            component->ReadLatestDataUpdate(msg);
            component->FinishUpdate();
            componentLatestData_.Erase(current);
        }
    }
}

void Connection::ProcessLoadScene(int msgID, MemoryBuffer& msg)
{
    if (IsClient())
    {
        LOGWARNING("Received unexpected LoadScene message from client " + ToString());
        return;
    }
    
    if (!scene_)
    {
        LOGERROR("Can not handle LoadScene message without an assigned scene");
        return;
    }
    
    // Store the scene file name we need to eventually load
    sceneFileName_ = msg.ReadString();
    
    // Clear previous scene content, pending latest data, and package downloads if any
    scene_->Clear();
    nodeLatestData_.Clear();
    componentLatestData_.Clear();
    downloads_.Clear();
    
    // In case we have joined other scenes in this session, remove first all downloaded package files from the resource system
    // to prevent resource conflicts
    const String& packageCacheDir = GetSubsystem<Network>()->GetPackageCacheDir();
    ResourceCache* cache = GetSubsystem<ResourceCache>();
    Vector<SharedPtr<PackageFile> > packages = cache->GetPackageFiles();
    for (unsigned i = 0; i < packages.Size(); ++i)
    {
        PackageFile* package = packages[i];
        if (!package->GetName().Find(packageCacheDir))
            cache->RemovePackageFile(package, true);
    }
    
    // Now check which packages we have in the resource cache or in the download cache, and which we need to download
    unsigned numPackages = msg.ReadVLE();
    packages = cache->GetPackageFiles(); // Refresh resource cache's package list after possible removals
    Vector<String> downloadedPackages;
    if (!packageCacheDir.Empty())
        GetSubsystem<FileSystem>()->ScanDir(downloadedPackages, packageCacheDir, "*.*", SCAN_FILES, false);
    
    for (unsigned i = 0; i < numPackages; ++i)
    {
        String name = msg.ReadString();
        unsigned fileSize = msg.ReadUInt();
        unsigned checksum = msg.ReadUInt();
        String checksumString = ToStringHex(checksum);
        bool found = false;
        
        // Check first the resource cache
        for (unsigned j = 0; j < packages.Size(); ++j)
        {
            PackageFile* package = packages[j];
            if (!GetFileNameAndExtension(package->GetName()).Compare(name, false) && package->GetTotalSize() == fileSize &&
                package->GetChecksum() == checksum)
            {
                found = true;
                break;
            }
        }
        
        // Then the download cache
        for (unsigned j = 0; j < downloadedPackages.Size(); ++j)
        {
            const String& fileName = downloadedPackages[j];
            if (!fileName.Find(checksumString) && !fileName.Substring(9).Compare(name, false))
            {
                // Name matches. Check filesize and actual checksum to be sure
                SharedPtr<PackageFile> newPackage(new PackageFile(context_, packageCacheDir + fileName));
                if (newPackage->GetTotalSize() == fileSize && newPackage->GetChecksum() == checksum)
                {
                    // Add the package to the resource cache, as we will need it to load the scene
                    cache->AddPackageFile(newPackage, true);
                    found = true;
                    break;
                }
            }
        }
        
        // Need to request a download
        if (!found)
        {
            if (!packageCacheDir.Empty())
                RequestPackage(name, fileSize, checksum);
            else
            {
                LOGERROR("Can not download required packages, as no package cache path is set");
                OnSceneLoadFailed();
                return;
            }
        }
    }
    
    // If no downloads were queued, can load the scene directly
    if (downloads_.Empty())
        OnPackagesReady();
}

void Connection::ProcessSceneChecksumError(int msgID, MemoryBuffer& msg)
{
    if (IsClient())
    {
        LOGWARNING("Received unexpected SceneChecksumError message from client " + ToString());
        return;
    }
    
    OnSceneLoadFailed();
}

void Connection::ProcessSceneUpdate(int msgID, MemoryBuffer& msg)
{
    if (IsClient())
    {
        LOGWARNING("Received unexpected SceneUpdate message from client " + ToString());
        return;
    }
    
    if (!scene_)
        return;
    
    switch (msgID)
    {
    case MSG_CREATENODE:
        {
            unsigned nodeID = msg.ReadVLE();
            // In case of the root node (scene), it may already exist. Do not create in that case
            Node* node = scene_->GetNodeByID(nodeID);
            if (!node)
            {
                // Add initially to the root level. May be moved later
                node = scene_->CreateChild(nodeID, REPLICATED);
            }
            
            // Enable motion smoothing on the node
            node->SetSmoothed(true);
            
            // Read initial attributes, then snap the motion smoothing immediately to the end
            node->ReadDeltaUpdate(msg, deltaUpdateBits_);
            node->UpdateSmoothing(1.0f, 0.0f);
            
            // Read initial user variables
            unsigned numVars = msg.ReadVLE();
            VariantMap& vars = node->GetVars();
            while (numVars)
            {
                --numVars;
                
                ShortStringHash key = msg.ReadShortStringHash();
                vars[key] = msg.ReadVariant();
            }
            
            // Read components
            unsigned numComponents = msg.ReadVLE();
            while (numComponents)
            {
                --numComponents;
                
                ShortStringHash type = msg.ReadShortStringHash();
                unsigned componentID = msg.ReadVLE();
                
                // Check if the component by this ID and type already exists in this node
                Component* component = scene_->GetComponentByID(componentID);
                if (!component || component->GetType() != type || component->GetNode() != node)
                {
                    if (component)
                        component->Remove();
                    component = node->CreateComponent(type, componentID, REPLICATED);
                }
                
                // If was unable to create the component, would desync the message and therefore have to abort
                if (!component)
                {
                    LOGERROR("CreateNode message parsing aborted due to unknown component");
                    return;
                }
                
                // Read initial attributes, then perform finalization
                component->ReadDeltaUpdate(msg, deltaUpdateBits_);
                component->FinishUpdate();
            }
        }
        break;
        
    case MSG_NODEDELTAUPDATE:
        {
            unsigned nodeID = msg.ReadVLE();
            Node* node = scene_->GetNodeByID(nodeID);
            if (node)
            {
                node->ReadDeltaUpdate(msg, deltaUpdateBits_);
                
                unsigned changedVars = msg.ReadVLE();
                VariantMap& vars = node->GetVars();
                while (changedVars)
                {
                    --changedVars;
                    
                    ShortStringHash key = msg.ReadShortStringHash();
                    vars[key] = msg.ReadVariant();
                }
            }
            else
                LOGWARNING("NodeDeltaUpdate message received for missing node " + String(nodeID));
        }
        break;
        
    case MSG_NODELATESTDATA:
        {
            unsigned nodeID = msg.ReadVLE();
            Node* node = scene_->GetNodeByID(nodeID);
            if (node)
                node->ReadLatestDataUpdate(msg);
            else
            {
                // Latest data messages may be received out-of-order relative to node creation, so cache if necessary
                PODVector<unsigned char>& data = nodeLatestData_[nodeID];
                data.Resize(msg.GetSize());
                memcpy(&data[0], msg.GetData(), msg.GetSize());
            }
        }
        break;
        
    case MSG_REMOVENODE:
        {
            unsigned nodeID = msg.ReadVLE();
            Node* node = scene_->GetNodeByID(nodeID);
            if (node)
                node->Remove();
            else
                LOGWARNING("RemoveNode message received for missing node " + String(nodeID));
            nodeLatestData_.Erase(nodeID);
        }
        break;
        
    case MSG_CREATECOMPONENT:
        {
            unsigned nodeID = msg.ReadVLE();
            Node* node = scene_->GetNodeByID(nodeID);
            if (node)
            {
                ShortStringHash type = msg.ReadShortStringHash();
                unsigned componentID = msg.ReadVLE();
                
                // Check if the component by this ID and type already exists in this node
                Component* component = scene_->GetComponentByID(componentID);
                if (!component || component->GetType() != type || component->GetNode() != node)
                {
                    if (component)
                        component->Remove();
                    component = node->CreateComponent(type, componentID, REPLICATED);
                }
                
                // If was unable to create the component, would desync the message and therefore have to abort
                if (!component)
                {
                    LOGERROR("CreateComponent message parsing aborted due to unknown component");
                    return;
                }
                
                // Read initial attributes, then perform finalization
                component->ReadDeltaUpdate(msg, deltaUpdateBits_);
                component->FinishUpdate();
            }
            else
                LOGWARNING("CreateComponent message received for missing node " + String(nodeID));
        }
        break;
        
    case MSG_COMPONENTDELTAUPDATE:
        {
            unsigned componentID = msg.ReadVLE();
            Component* component = scene_->GetComponentByID(componentID);
            if (component)
            {
                component->ReadDeltaUpdate(msg, deltaUpdateBits_);
                component->FinishUpdate();
            }
            else
                LOGWARNING("ComponentDeltaUpdate message received for missing component " + String(componentID));
        }
        break;
        
    case MSG_COMPONENTLATESTDATA:
        {
            unsigned componentID = msg.ReadVLE();
            Component* component = scene_->GetComponentByID(componentID);
            if (component)
            {
                component->ReadLatestDataUpdate(msg);
                component->FinishUpdate();
            }
            else
            {
                // Latest data messages may be received out-of-order relative to component creation, so cache if necessary
                PODVector<unsigned char>& data = componentLatestData_[componentID];
                data.Resize(msg.GetSize());
                memcpy(&data[0], msg.GetData(), msg.GetSize());
            }
        }
        break;
        
    case MSG_REMOVECOMPONENT:
        {
            unsigned componentID = msg.ReadVLE();
            Component* component = scene_->GetComponentByID(componentID);
            if (component)
                component->Remove();
            else
                LOGWARNING("RemoveComponent message received for missing component " + String(componentID));
            componentLatestData_.Erase(componentID);
        }
        break;
    }
}

void Connection::ProcessPackageDownload(int msgID, MemoryBuffer& msg)
{
    switch (msgID)
    {
    case MSG_REQUESTPACKAGE:
        if (!IsClient())
        {
            LOGWARNING("Received unexpected RequestPackage message from server");
            return;
        }
        else
        {
            String name = msg.ReadString();
            
            if (!scene_)
            {
                LOGWARNING("Received a RequestPackage message without an assigned scene from client " + ToString());
                return;
            }
            
            // The package must be one of those required by the scene
            const Vector<SharedPtr<PackageFile> >& packages = scene_->GetRequiredPackageFiles();
            for (unsigned i = 0; i < packages.Size(); ++i)
            {
                PackageFile* package = packages[i];
                String packageFullName = package->GetName();
                if (!GetFileNameAndExtension(packageFullName).Compare(name, false))
                {
                    SharedPtr<File> file(new File(context_, packageFullName));
                    if (!file->IsOpen())
                    {
                        LOGERROR("Failed to transmit package file " + name);
                        SendPackageError(name);
                        return;
                    }
                    
                    LOGINFO("Transmitting package file " + name + " to client " + ToString());
                    
                    StringHash nameHash(name);
                    unsigned totalFragments = (file->GetSize() + PACKAGE_FRAGMENT_SIZE - 1) / PACKAGE_FRAGMENT_SIZE;
                    unsigned char buffer[PACKAGE_FRAGMENT_SIZE];
                    
                    // Now simply read the file fragments and queue them
                    for (unsigned i = 0; i < totalFragments; ++i)
                    {
                        unsigned fragmentSize = Min((int)(file->GetSize() - file->GetPosition()), (int)PACKAGE_FRAGMENT_SIZE);
                        file->Read(buffer, fragmentSize);
                        
                        msg_.Clear();
                        msg_.WriteStringHash(nameHash);
                        msg_.WriteVLE(i);
                        msg_.Write(buffer, fragmentSize);
                        SendMessage(MSG_PACKAGEDATA, true, false, msg_);
                    }
                    
                    return;
                }
            }
            
            LOGERROR("Client requested a nonexisting package file " + name);
            // Send the name hash only to indicate a failed download
            SendPackageError(name);
            return;
        }
        break;
        
    case MSG_PACKAGEDATA:
        if (IsClient())
        {
            LOGWARNING("Received unexpected PackageData message from client");
            return;
        }
        else
        {
            StringHash nameHash = msg.ReadStringHash();
            
            Map<StringHash, PackageDownload>::Iterator i = downloads_.Find(nameHash);
            // In case of being unable to create the package file into the cache, we will still receive all data from the server.
            // Simply disregard it
            if (i == downloads_.End())
                return;
            
            PackageDownload& download = i->second_;
            
            // If no further data, this is an error reply
            if (msg.IsEof())
            {
                LOGERROR("Download of package " + download.name_ + " failed");
                OnPackageDownloadFailed();
                return;
            }
            
            // If file has not yet been opened, try to open now. Prepend the checksum to the filename to allow multiple versions
            if (!download.file_)
            {
                download.file_ = new File(context_, GetSubsystem<Network>()->GetPackageCacheDir() + ToStringHex(download.checksum_) + "_" + download.name_, FILE_WRITE);
                if (!download.file_->IsOpen())
                {
                    LOGERROR("Download of package " + download.name_ + " failed");
                    OnPackageDownloadFailed();
                    return;
                }
            }
            
            // Write the fragment data to the proper index
            unsigned char buffer[PACKAGE_FRAGMENT_SIZE];
            unsigned index = msg.ReadVLE();
            unsigned fragmentSize = msg.GetSize() - msg.GetPosition();
            
            msg.Read(buffer, fragmentSize);
            download.file_->Seek(index * PACKAGE_FRAGMENT_SIZE);
            download.file_->Write(buffer, fragmentSize);
            download.receivedFragments_.Insert(index);
            
            // Check if all fragments received
            if (download.receivedFragments_.Size() > download.totalFragments_)
            {
                LOGERROR("Received extra fragments for package " + download.name_);
                OnPackageDownloadFailed();
                return;
            }
            
            if (download.receivedFragments_.Size() == download.totalFragments_)
            {
                LOGINFO("Package " + download.name_ + " downloaded successfully");
                
                // Instantiate the package and add to the resource system, as we will need it to load the scene
                download.file_->Close();
                SharedPtr<PackageFile> newPackage(new PackageFile(context_, download.file_->GetName()));
                GetSubsystem<ResourceCache>()->AddPackageFile(newPackage, true);
                
                // Then start the next download if there are more
                downloads_.Erase(i);
                if (downloads_.Empty())
                    OnPackagesReady();
                else
                {
                    PackageDownload& nextDownload = downloads_.Begin()->second_;
                    
                    LOGINFO("Requesting package " + nextDownload.name_ + " from server");
                    msg_.Clear();
                    msg_.WriteString(nextDownload.name_);
                    SendMessage(MSG_REQUESTPACKAGE, true, true, msg_);
                    nextDownload.initiated_ = true;
                }
            }
        }
        break;
    }
}

void Connection::ProcessIdentity(int msgID, MemoryBuffer& msg)
{
    if (!IsClient())
    {
        LOGWARNING("Received unexpected Identity message from server");
        return;
    }
    
    identity_ = msg.ReadVariantMap();
    
    using namespace ClientIdentity;
    
    VariantMap eventData = identity_;
    eventData[P_CONNECTION] = (void*)this;
    eventData[P_ALLOW] = true;
    SendEvent(E_CLIENTIDENTITY, eventData);
    
    // If connection was denied as a response to the identity event, disconnect now
    if (!eventData[P_ALLOW].GetBool())
        Disconnect();
}

void Connection::ProcessControls(int msgID, MemoryBuffer& msg)
{
    if (!IsClient())
    {
        LOGWARNING("Received unexpected Controls message from server");
        return;
    }
    
    Controls newControls;
    newControls.buttons_ = msg.ReadUInt();
    newControls.yaw_ = msg.ReadFloat();
    newControls.pitch_ = msg.ReadFloat();
    newControls.extraData_ = msg.ReadVariantMap();
    SetControls(newControls);
}

void Connection::ProcessSceneLoaded(int msgID, MemoryBuffer& msg)
{
    if (!IsClient())
    {
        LOGWARNING("Received unexpected SceneLoaded message from server");
        return;
    }
    
    if (!scene_)
    {
        LOGWARNING("Received a SceneLoaded message without an assigned scene from client " + ToString());
        return;
    }
    
    unsigned checksum = msg.ReadUInt();
    
    if (checksum != scene_->GetChecksum())
    {
        msg_.Clear();
        SendMessage(MSG_SCENECHECKSUMERROR, true, true, msg_);
        OnSceneLoadFailed();
    }
    else
    {
        sceneLoaded_ = true;
        
        using namespace ClientSceneLoaded;
        
        VariantMap eventData;
        eventData[P_CONNECTION] = (void*)this;
        SendEvent(E_CLIENTSCENELOADED, eventData);
    }
}

void Connection::ProcessRemoteEvent(int msgID, MemoryBuffer& msg)
{
    if (msgID == MSG_REMOTEEVENT)
    {
        StringHash eventType = msg.ReadStringHash();
        if (!GetSubsystem<Network>()->CheckRemoteEvent(eventType))
        {
            LOGWARNING("Discarding not allowed remote event " + eventType.ToString());
            return;
        }
        
        VariantMap eventData = msg.ReadVariantMap();
        SendEvent(eventType, eventData);
    }
    else
    {
        if (!scene_)
        {
            LOGERROR("Can not receive remote node event without an assigned scene");
            return;
        }
        
        unsigned nodeID = msg.ReadVLE();
        StringHash eventType = msg.ReadStringHash();
        if (!GetSubsystem<Network>()->CheckRemoteEvent(eventType))
        {
            LOGWARNING("Discarding not allowed remote event " + eventType.ToString());
            return;
        }
        
        VariantMap eventData = msg.ReadVariantMap();
        Node* receiver = scene_->GetNodeByID(nodeID);
        if (!receiver)
        {
            LOGWARNING("Missing receiver for remote node event, discarding");
            return;
        }
        SendEvent(receiver, eventType, eventData);
    }
}

kNet::MessageConnection* Connection::GetMessageConnection() const
{
    return const_cast<kNet::MessageConnection*>(connection_.ptr());
}

Scene* Connection::GetScene() const
{
    return scene_;
}

bool Connection::IsConnected() const
{
    return connection_->GetConnectionState() == kNet::ConnectionOK;
}

String Connection::GetAddress() const
{
    const unsigned char* ip = connection_->RemoteEndPoint().ip;
    char str[256];
    sprintf(str, "%d.%d.%d.%d", (unsigned)ip[0], (unsigned)ip[1], (unsigned)ip[2], (unsigned)ip[3]);
    return String(str);
}

unsigned short Connection::GetPort() const
{
    return connection_->RemoteEndPoint().port;
}

String Connection::ToString() const
{
    return GetAddress() + ":" + String(GetPort());
}

unsigned Connection::GetNumDownloads() const
{
    return downloads_.Size();
}

const String& Connection::GetDownloadName() const
{
    for (Map<StringHash, PackageDownload>::ConstIterator i = downloads_.Begin(); i != downloads_.End(); ++i)
    {
        if (i->second_.initiated_)
            return i->second_.name_;
    }
    return noName;
}

float Connection::GetDownloadProgress() const
{
    for (Map<StringHash, PackageDownload>::ConstIterator i = downloads_.Begin(); i != downloads_.End(); ++i)
    {
        if (i->second_.initiated_)
        {
            return i->second_.totalFragments_ ? (float)i->second_.receivedFragments_.Size() / (float)i->second_.totalFragments_ :
                0.0f;
        }
    }
    return 1.0f;
}

void Connection::HandleAsyncLoadFinished(StringHash eventType, VariantMap& eventData)
{
    VectorBuffer msg;
    msg.WriteUInt(scene_->GetChecksum());
    SendMessage(MSG_SCENELOADED, true, true, msg);
}

void Connection::ProcessNode(Node* node)
{
    processedNodes_.Insert(node);
    
    // Process depended upon nodes first
    PODVector<Node*> depends;
    node->GetDependencyNodes(depends);
    for (PODVector<Node*>::ConstIterator i = depends.Begin(); i != depends.End(); ++i)
    {
        // Paranoid null check: a component might supply a null dependency
        if (*i && !processedNodes_.Contains(*i))
            ProcessNode(*i);
    }
    
    // Check if the client's replication state already has this node
    if (sceneState_.Find(node->GetID()) != sceneState_.End())
        ProcessExistingNode(node);
    else
        ProcessNewNode(node);
}

void Connection::ProcessNewNode(Node* node)
{
    msg_.Clear();
    msg_.WriteVLE(node->GetID());
    
    NodeReplicationState& nodeState = sceneState_[node->GetID()];
    nodeState.frameNumber_ = frameNumber_;
    
    // Write node's attributes
    node->WriteInitialDeltaUpdate(msg_, deltaUpdateBits_, nodeState.attributes_);
    
    // Write node's user variables
    const VariantMap& vars = node->GetVars();
    msg_.WriteVLE(vars.Size());
    for (VariantMap::ConstIterator i = vars.Begin(); i != vars.End(); ++i)
    {
        msg_.WriteShortStringHash(i->first_);
        msg_.WriteVariant(i->second_);
        nodeState.vars_[i->first_] = i->second_;
    }
    
    // Write node's components
    msg_.WriteVLE(node->GetNumNetworkComponents());
    const Vector<SharedPtr<Component> >& components = node->GetComponents();
    for (unsigned i = 0; i < components.Size(); ++i)
    {
        Component* component = components[i];
        // Check if component is not to be replicated
        if (component->GetID() >= FIRST_LOCAL_ID)
            continue;
        
        ComponentReplicationState& componentState = nodeState.components_[component->GetID()];
        componentState.frameNumber_ = frameNumber_;
        componentState.type_ = component->GetType();
        
        msg_.WriteShortStringHash(component->GetType());
        msg_.WriteVLE(component->GetID());
        component->WriteInitialDeltaUpdate(msg_, deltaUpdateBits_, componentState.attributes_);
    }
    
    SendMessage(MSG_CREATENODE, true, true, msg_);
}

void Connection::ProcessExistingNode(Node* node)
{
    NodeReplicationState& nodeState = sceneState_[node->GetID()];
    nodeState.frameNumber_ = frameNumber_;
    
    // Check if attributes have changed
    bool deltaUpdate, latestData;
    
    node->PrepareUpdates(deltaUpdateBits_, classCurrentState_[node->GetType()], nodeState.attributes_, deltaUpdate, latestData);
    
    // Check if user variables have changed. Note: variable removal is not supported
    changedVars_.Clear();
    const VariantMap& vars = node->GetVars();
    for (VariantMap::ConstIterator i = vars.Begin(); i != vars.End(); ++i)
    {
        VariantMap::Iterator j = nodeState.vars_.Find(i->first_);
        if (j == nodeState.vars_.End() || i->second_ != j->second_)
        {
            j->second_ = i->second_;
            changedVars_.Insert(i->first_);
            deltaUpdate = true;
        }
    }
    
    // Send deltaupdate message if necessary
    if (deltaUpdate)
    {
        msg_.Clear();
        msg_.WriteVLE(node->GetID());
        node->WriteDeltaUpdate(msg_, deltaUpdateBits_, nodeState.attributes_);
        
        // Write changed variables
        msg_.WriteVLE(changedVars_.Size());
        for (HashSet<ShortStringHash>::ConstIterator i = changedVars_.Begin(); i != changedVars_.End(); ++i)
        {
            VariantMap::ConstIterator j = vars.Find(*i);
            msg_.WriteShortStringHash(j->first_);
            msg_.WriteVariant(j->second_);
        }
        
        SendMessage(MSG_NODEDELTAUPDATE, true, true, msg_);
    }
    
    // Send latestdata message if necessary
    if (latestData)
    {
        // If at least one latest data attribute changes, send all of them
        msg_.Clear();
        msg_.WriteVLE(node->GetID());
        node->WriteLatestDataUpdate(msg_, nodeState.attributes_);
        
        SendMessage(MSG_NODELATESTDATA, node->GetID(), true, false, msg_);
    }
    
    // Check for new or changed components
    const Vector<SharedPtr<Component> >& components = node->GetComponents();
    for (unsigned i = 0; i < components.Size(); ++i)
    {
        Component* component = components[i];
        // Check if component is not to be replicated
        if (component->GetID() >= FIRST_LOCAL_ID)
            continue;
        
        Map<unsigned, ComponentReplicationState>::Iterator j = nodeState.components_.Find(component->GetID());
        if (j == nodeState.components_.End())
        {
            // New component
            ComponentReplicationState& componentState = nodeState.components_[component->GetID()];
            componentState.frameNumber_ = frameNumber_;
            componentState.type_ = component->GetType();
            
            msg_.Clear();
            msg_.WriteVLE(node->GetID());
            msg_.WriteShortStringHash(component->GetType());
            msg_.WriteVLE(component->GetID());
            component->WriteInitialDeltaUpdate(msg_, deltaUpdateBits_, componentState.attributes_);
            
            SendMessage(MSG_CREATECOMPONENT, true, true, msg_);
        }
        else
        {
            // Existing component
            ComponentReplicationState& componentState = j->second_;
            componentState.frameNumber_ = frameNumber_;
            
            component->PrepareUpdates(deltaUpdateBits_, classCurrentState_[component->GetType()], componentState.attributes_,
                deltaUpdate, latestData);
            
            // Send deltaupdate message if necessary
            if (deltaUpdate)
            {
                msg_.Clear();
                msg_.WriteVLE(component->GetID());
                component->WriteDeltaUpdate(msg_, deltaUpdateBits_, componentState.attributes_);
                
                SendMessage(MSG_COMPONENTDELTAUPDATE, true, true, msg_);
            }
            
            // Send latestdata message if necessary
            if (latestData)
            {
                // If at least one latest data attribute changes, send all of them
                msg_.Clear();
                msg_.WriteVLE(component->GetID());
                component->WriteLatestDataUpdate(msg_, componentState.attributes_);
                
                SendMessage(MSG_COMPONENTLATESTDATA, component->GetID(), true, false, msg_);
            }
        }
    }
    
    // Check for removed components
    for (Map<unsigned, ComponentReplicationState>::Iterator i = nodeState.components_.Begin(); i != nodeState.components_.End();)
    {
        Map<unsigned, ComponentReplicationState>::Iterator current = i++;
        if (current->second_.frameNumber_ != frameNumber_)
        {
            msg_.Clear();
            msg_.WriteVLE(current->first_);
            
            SendMessage(MSG_REMOVECOMPONENT, true, true, msg_);
            nodeState.components_.Erase(current);
        }
    }
}

void Connection::RequestPackage(const String& name, unsigned fileSize, unsigned checksum)
{
    StringHash nameHash(name);
    if (downloads_.Contains(nameHash))
        return; // Download already exists
    
    PackageDownload& download = downloads_[nameHash];
    download.name_ = name;
    download.totalFragments_ = (fileSize + PACKAGE_FRAGMENT_SIZE - 1) / PACKAGE_FRAGMENT_SIZE;
    download.checksum_ = checksum;
    
    // Start download now only if no existing downloads, else wait for the existing ones to finish
    if (downloads_.Size() == 1)
    {
        LOGINFO("Requesting package " + name + " from server");
        msg_.Clear();
        msg_.WriteString(name);
        SendMessage(MSG_REQUESTPACKAGE, true, true, msg_);
        download.initiated_ = true;
    }
}

void Connection::SendPackageError(const String& name)
{
    msg_.Clear();
    msg_.WriteStringHash(StringHash(name));
    SendMessage(MSG_PACKAGEDATA, true, false, msg_);
}

void Connection::OnSceneLoadFailed()
{
    using namespace NetworkSceneLoadFailed;
    
    VariantMap eventData;
    eventData[P_CONNECTION] = (void*)this;
    SendEvent(E_NETWORKSCENELOADFAILED, eventData);
    return;
}

void Connection::OnPackageDownloadFailed()
{
    // As one package failed, we can not join the scene in any case. Clear the downloads
    downloads_.Clear();
    OnSceneLoadFailed();
}

void Connection::OnPackagesReady()
{
    if (!scene_)
        return;
    
    if (sceneFileName_.Empty())
    {
        scene_->Clear();
        
        // If filename is empty, can send the scene loaded reply immediately
        msg_.Clear();
        msg_.WriteUInt(scene_->GetChecksum());
        SendMessage(MSG_SCENELOADED, true, true, msg_);
    }
    else
    {
        // Otherwise start the async loading process
        String extension = GetExtension(sceneFileName_);
        SharedPtr<File> file(new File(context_, sceneFileName_));
        bool success;
        
        if (extension == ".xml")
            success = scene_->LoadAsyncXML(file);
        else
            success = scene_->LoadAsync(file);
        
        if (!success)
            OnSceneLoadFailed();
    }
}
