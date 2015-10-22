//
// Copyright (c) 2008-2015 the Urho3D project.
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

#include "../Precompiled.h"

#include "../Core/Profiler.h"
#include "../IO/File.h"
#include "../IO/FileSystem.h"
#include "../IO/Log.h"
#include "../IO/MemoryBuffer.h"
#include "../IO/PackageFile.h"
#include "../Network/Connection.h"
#include "../Network/Network.h"
#include "../Network/NetworkEvents.h"
#include "../Network/NetworkPriority.h"
#include "../Network/Protocol.h"
#include "../Resource/ResourceCache.h"
#include "../Scene/Scene.h"
#include "../Scene/SceneEvents.h"
#include "../Scene/SmoothedTransform.h"

#include <kNet/kNet.h>

#include "../DebugNew.h"

namespace Urho3D
{

static const int STATS_INTERVAL_MSEC = 2000;

PackageDownload::PackageDownload() :
    totalFragments_(0),
    checksum_(0),
    initiated_(false)
{
}

PackageUpload::PackageUpload() :
    fragment_(0),
    totalFragments_(0)
{
}

Connection::Connection(Context* context, bool isClient, kNet::SharedPtr<kNet::MessageConnection> connection) :
    Object(context),
    timeStamp_(0),
    connection_(connection),
    sendMode_(OPSM_NONE),
    isClient_(isClient),
    connectPending_(false),
    sceneLoaded_(false),
    logStatistics_(false)
{
    sceneState_.connection_ = this;

    // Store address and port now for accurate logging (kNet may already have destroyed the socket on disconnection,
    // in which case we would log a zero address:port on disconnect)
    kNet::EndPoint endPoint = connection_->RemoteEndPoint();
    ///\todo Not IPv6-capable.
    address_ = Urho3D::ToString("%d.%d.%d.%d", endPoint.ip[0], endPoint.ip[1], endPoint.ip[2], endPoint.ip[3]);
    port_ = endPoint.port;
}

Connection::~Connection()
{
    // Reset scene (remove possible owner references), as this connection is about to be destroyed
    SetScene(0);
}

void Connection::SendMessage(int msgID, bool reliable, bool inOrder, const VectorBuffer& msg, unsigned contentID)
{
    SendMessage(msgID, reliable, inOrder, msg.GetData(), msg.GetSize(), contentID);
}

void Connection::SendMessage(int msgID, bool reliable, bool inOrder, const unsigned char* data, unsigned numBytes,
    unsigned contentID)
{
    // Make sure not to use kNet internal message ID's
    if (msgID <= 0x4 || msgID >= 0x3ffffffe)
    {
        URHO3D_LOGERROR("Can not send message with reserved ID");
        return;
    }

    if (numBytes && !data)
    {
        URHO3D_LOGERROR("Null pointer supplied for network message data");
        return;
    }

    kNet::NetworkMessage* msg = connection_->StartNewMessage((unsigned long)msgID, numBytes);
    if (!msg)
    {
        URHO3D_LOGERROR("Can not start new network message");
        return;
    }

    msg->reliable = reliable;
    msg->inOrder = inOrder;
    msg->priority = 0;
    msg->contentID = contentID;
    if (numBytes)
        memcpy(msg->data, data, numBytes);

    connection_->EndAndQueueMessage(msg);
}

void Connection::SendRemoteEvent(StringHash eventType, bool inOrder, const VariantMap& eventData)
{
    RemoteEvent queuedEvent;
    queuedEvent.senderID_ = 0;
    queuedEvent.eventType_ = eventType;
    queuedEvent.eventData_ = eventData;
    queuedEvent.inOrder_ = inOrder;
    remoteEvents_.Push(queuedEvent);
}

void Connection::SendRemoteEvent(Node* node, StringHash eventType, bool inOrder, const VariantMap& eventData)
{
    if (!node)
    {
        URHO3D_LOGERROR("Null sender node for remote node event");
        return;
    }
    if (node->GetScene() != scene_)
    {
        URHO3D_LOGERROR("Sender node is not in the connection's scene, can not send remote node event");
        return;
    }
    if (node->GetID() >= FIRST_LOCAL_ID)
    {
        URHO3D_LOGERROR("Sender node has a local ID, can not send remote node event");
        return;
    }

    RemoteEvent queuedEvent;
    queuedEvent.senderID_ = node->GetID();
    queuedEvent.eventType_ = eventType;
    queuedEvent.eventData_ = eventData;
    queuedEvent.inOrder_ = inOrder;
    remoteEvents_.Push(queuedEvent);
}

void Connection::SetScene(Scene* newScene)
{
    if (scene_)
    {
        // Remove replication states and owner references from the previous scene
        scene_->CleanupConnection(this);
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
        // Make sure there is no existing async loading
        scene_->StopAsyncLoading();
        SubscribeToEvent(scene_, E_ASYNCLOADFINISHED, URHO3D_HANDLER(Connection, HandleAsyncLoadFinished));
    }
}

void Connection::SetIdentity(const VariantMap& identity)
{
    identity_ = identity;
}

void Connection::SetControls(const Controls& newControls)
{
    controls_ = newControls;
}

void Connection::SetPosition(const Vector3& position)
{
    position_ = position;
    if (sendMode_ == OPSM_NONE)
        sendMode_ = OPSM_POSITION;
}

void Connection::SetRotation(const Quaternion& rotation)
{
    rotation_ = rotation;
    if (sendMode_ != OPSM_POSITION_ROTATION)
        sendMode_ = OPSM_POSITION_ROTATION;
}

void Connection::SetConnectPending(bool connectPending)
{
    connectPending_ = connectPending;
}

void Connection::SetLogStatistics(bool enable)
{
    logStatistics_ = enable;
}

void Connection::Disconnect(int waitMSec)
{
    connection_->Disconnect(waitMSec);
}

void Connection::SendServerUpdate()
{
    if (!scene_ || !sceneLoaded_)
        return;

    // Always check the root node (scene) first so that the scene-wide components get sent first,
    // and all other replicated nodes get added to the dirty set for sending the initial state
    unsigned sceneID = scene_->GetID();
    nodesToProcess_.Insert(sceneID);
    ProcessNode(sceneID);

    // Then go through all dirtied nodes
    nodesToProcess_.Insert(sceneState_.dirtyNodes_);
    nodesToProcess_.Erase(sceneID); // Do not process the root node twice

    while (nodesToProcess_.Size())
    {
        unsigned nodeID = nodesToProcess_.Front();
        ProcessNode(nodeID);
    }
}

void Connection::SendClientUpdate()
{
    if (!scene_ || !sceneLoaded_)
        return;

    msg_.Clear();
    msg_.WriteUInt(controls_.buttons_);
    msg_.WriteFloat(controls_.yaw_);
    msg_.WriteFloat(controls_.pitch_);
    msg_.WriteVariantMap(controls_.extraData_);
    msg_.WriteUByte(timeStamp_);
    if (sendMode_ >= OPSM_POSITION)
        msg_.WriteVector3(position_);
    if (sendMode_ >= OPSM_POSITION_ROTATION)
        msg_.WritePackedQuaternion(rotation_);
    SendMessage(MSG_CONTROLS, false, false, msg_, CONTROLS_CONTENT_ID);

    ++timeStamp_;
}

void Connection::SendRemoteEvents()
{
#ifdef URHO3D_LOGGING
    if (logStatistics_ && statsTimer_.GetMSec(false) > STATS_INTERVAL_MSEC)
    {
        statsTimer_.Reset();
        char statsBuffer[256];
        sprintf(statsBuffer, "RTT %.3f ms Pkt in %d Pkt out %d Data in %.3f KB/s Data out %.3f KB/s", connection_->RoundTripTime(),
            (int)connection_->PacketsInPerSec(),
            (int)connection_->PacketsOutPerSec(), connection_->BytesInPerSec() / 1000.0f, connection_->BytesOutPerSec() / 1000.0f);
        URHO3D_LOGINFO(statsBuffer);
    }
#endif

    if (remoteEvents_.Empty())
        return;

    URHO3D_PROFILE(SendRemoteEvents);

    for (Vector<RemoteEvent>::ConstIterator i = remoteEvents_.Begin(); i != remoteEvents_.End(); ++i)
    {
        msg_.Clear();
        if (!i->senderID_)
        {
            msg_.WriteStringHash(i->eventType_);
            msg_.WriteVariantMap(i->eventData_);
            SendMessage(MSG_REMOTEEVENT, true, i->inOrder_, msg_);
        }
        else
        {
            msg_.WriteNetID(i->senderID_);
            msg_.WriteStringHash(i->eventType_);
            msg_.WriteVariantMap(i->eventData_);
            SendMessage(MSG_REMOTENODEEVENT, true, i->inOrder_, msg_);
        }
    }

    remoteEvents_.Clear();
}

void Connection::SendPackages()
{
    while (!uploads_.Empty() && connection_->NumOutboundMessagesPending() < 1000)
    {
        unsigned char buffer[PACKAGE_FRAGMENT_SIZE];

        for (HashMap<StringHash, PackageUpload>::Iterator i = uploads_.Begin(); i != uploads_.End();)
        {
            HashMap<StringHash, PackageUpload>::Iterator current = i++;
            PackageUpload& upload = current->second_;
            unsigned fragmentSize =
                (unsigned)Min((int)(upload.file_->GetSize() - upload.file_->GetPosition()), (int)PACKAGE_FRAGMENT_SIZE);
            upload.file_->Read(buffer, fragmentSize);

            msg_.Clear();
            msg_.WriteStringHash(current->first_);
            msg_.WriteUInt(upload.fragment_++);
            msg_.Write(buffer, fragmentSize);
            SendMessage(MSG_PACKAGEDATA, true, false, msg_);

            // Check if upload finished
            if (upload.fragment_ == upload.totalFragments_)
                uploads_.Erase(current);
        }
    }
}

void Connection::ProcessPendingLatestData()
{
    if (!scene_ || !sceneLoaded_)
        return;

    // Iterate through pending node data and see if we can find the nodes now
    for (HashMap<unsigned, PODVector<unsigned char> >::Iterator i = nodeLatestData_.Begin(); i != nodeLatestData_.End();)
    {
        HashMap<unsigned, PODVector<unsigned char> >::Iterator current = i++;
        Node* node = scene_->GetNode(current->first_);
        if (node)
        {
            MemoryBuffer msg(current->second_);
            msg.ReadNetID(); // Skip the node ID
            node->ReadLatestDataUpdate(msg);
            // ApplyAttributes() is deliberately skipped, as Node has no attributes that require late applying.
            // Furthermore it would propagate to components and child nodes, which is not desired in this case
            nodeLatestData_.Erase(current);
        }
    }

    // Iterate through pending component data and see if we can find the components now
    for (HashMap<unsigned, PODVector<unsigned char> >::Iterator i = componentLatestData_.Begin(); i != componentLatestData_.End();)
    {
        HashMap<unsigned, PODVector<unsigned char> >::Iterator current = i++;
        Component* component = scene_->GetComponent(current->first_);
        if (component)
        {
            MemoryBuffer msg(current->second_);
            msg.ReadNetID(); // Skip the component ID
            if (component->ReadLatestDataUpdate(msg))
                component->ApplyAttributes();
            componentLatestData_.Erase(current);
        }
    }
}

bool Connection::ProcessMessage(int msgID, MemoryBuffer& msg)
{
    bool processed = true;

    switch (msgID)
    {
    case MSG_IDENTITY:
        ProcessIdentity(msgID, msg);
        break;

    case MSG_CONTROLS:
        ProcessControls(msgID, msg);
        break;

    case MSG_SCENELOADED:
        ProcessSceneLoaded(msgID, msg);
        break;

    case MSG_REQUESTPACKAGE:
    case MSG_PACKAGEDATA:
        ProcessPackageDownload(msgID, msg);
        break;

    case MSG_LOADSCENE:
        ProcessLoadScene(msgID, msg);
        break;

    case MSG_SCENECHECKSUMERROR:
        ProcessSceneChecksumError(msgID, msg);
        break;

    case MSG_CREATENODE:
    case MSG_NODEDELTAUPDATE:
    case MSG_NODELATESTDATA:
    case MSG_REMOVENODE:
    case MSG_CREATECOMPONENT:
    case MSG_COMPONENTDELTAUPDATE:
    case MSG_COMPONENTLATESTDATA:
    case MSG_REMOVECOMPONENT:
        ProcessSceneUpdate(msgID, msg);
        break;

    case MSG_REMOTEEVENT:
    case MSG_REMOTENODEEVENT:
        ProcessRemoteEvent(msgID, msg);
        break;

    case MSG_PACKAGEINFO:
        ProcessPackageInfo(msgID, msg);
        break;

    default:
        processed = false;
        break;
    }

    return processed;
}

void Connection::ProcessLoadScene(int msgID, MemoryBuffer& msg)
{
    if (IsClient())
    {
        URHO3D_LOGWARNING("Received unexpected LoadScene message from client " + ToString());
        return;
    }

    if (!scene_)
    {
        URHO3D_LOGERROR("Can not handle LoadScene message without an assigned scene");
        return;
    }

    // Store the scene file name we need to eventually load
    sceneFileName_ = msg.ReadString();

    // Clear previous pending latest data and package downloads if any
    nodeLatestData_.Clear();
    componentLatestData_.Clear();
    downloads_.Clear();

    // In case we have joined other scenes in this session, remove first all downloaded package files from the resource system
    // to prevent resource conflicts
    ResourceCache* cache = GetSubsystem<ResourceCache>();
    const String& packageCacheDir = GetSubsystem<Network>()->GetPackageCacheDir();

    Vector<SharedPtr<PackageFile> > packages = cache->GetPackageFiles();
    for (unsigned i = 0; i < packages.Size(); ++i)
    {
        PackageFile* package = packages[i];
        if (!package->GetName().Find(packageCacheDir))
            cache->RemovePackageFile(package, true);
    }

    // Now check which packages we have in the resource cache or in the download cache, and which we need to download
    unsigned numPackages = msg.ReadVLE();
    if (!RequestNeededPackages(numPackages, msg))
    {
        OnSceneLoadFailed();
        return;
    }

    // If no downloads were queued, can load the scene directly
    if (downloads_.Empty())
        OnPackagesReady();
}

void Connection::ProcessSceneChecksumError(int msgID, MemoryBuffer& msg)
{
    if (IsClient())
    {
        URHO3D_LOGWARNING("Received unexpected SceneChecksumError message from client " + ToString());
        return;
    }

    URHO3D_LOGERROR("Scene checksum error");
    OnSceneLoadFailed();
}

void Connection::ProcessSceneUpdate(int msgID, MemoryBuffer& msg)
{
    /// \todo On mobile devices processing this message may potentially cause a crash if it attempts to load new GPU resources
    /// while the application is minimized
    if (IsClient())
    {
        URHO3D_LOGWARNING("Received unexpected SceneUpdate message from client " + ToString());
        return;
    }

    if (!scene_)
        return;

    switch (msgID)
    {
    case MSG_CREATENODE:
        {
            unsigned nodeID = msg.ReadNetID();
            // In case of the root node (scene), it should already exist. Do not create in that case
            Node* node = scene_->GetNode(nodeID);
            if (!node)
            {
                // Add initially to the root level. May be moved as we receive the parent attribute
                node = scene_->CreateChild(nodeID, REPLICATED);
                // Create smoothed transform component
                node->CreateComponent<SmoothedTransform>(LOCAL);
            }

            // Read initial attributes, then snap the motion smoothing immediately to the end
            node->ReadDeltaUpdate(msg);
            SmoothedTransform* transform = node->GetComponent<SmoothedTransform>();
            if (transform)
                transform->Update(1.0f, 0.0f);

            // Read initial user variables
            unsigned numVars = msg.ReadVLE();
            while (numVars)
            {
                StringHash key = msg.ReadStringHash();
                node->SetVar(key, msg.ReadVariant());
                --numVars;
            }

            // Read components
            unsigned numComponents = msg.ReadVLE();
            while (numComponents)
            {
                --numComponents;

                StringHash type = msg.ReadStringHash();
                unsigned componentID = msg.ReadNetID();

                // Check if the component by this ID and type already exists in this node
                Component* component = scene_->GetComponent(componentID);
                if (!component || component->GetType() != type || component->GetNode() != node)
                {
                    if (component)
                        component->Remove();
                    component = node->CreateComponent(type, REPLICATED, componentID);
                }

                // If was unable to create the component, would desync the message and therefore have to abort
                if (!component)
                {
                    URHO3D_LOGERROR("CreateNode message parsing aborted due to unknown component");
                    return;
                }

                // Read initial attributes and apply
                component->ReadDeltaUpdate(msg);
                component->ApplyAttributes();
            }
        }
        break;

    case MSG_NODEDELTAUPDATE:
        {
            unsigned nodeID = msg.ReadNetID();
            Node* node = scene_->GetNode(nodeID);
            if (node)
            {
                node->ReadDeltaUpdate(msg);
                // ApplyAttributes() is deliberately skipped, as Node has no attributes that require late applying.
                // Furthermore it would propagate to components and child nodes, which is not desired in this case
                unsigned changedVars = msg.ReadVLE();
                while (changedVars)
                {
                    StringHash key = msg.ReadStringHash();
                    node->SetVar(key, msg.ReadVariant());
                    --changedVars;
                }
            }
            else
                URHO3D_LOGWARNING("NodeDeltaUpdate message received for missing node " + String(nodeID));
        }
        break;

    case MSG_NODELATESTDATA:
        {
            unsigned nodeID = msg.ReadNetID();
            Node* node = scene_->GetNode(nodeID);
            if (node)
            {
                node->ReadLatestDataUpdate(msg);
                // ApplyAttributes() is deliberately skipped, as Node has no attributes that require late applying.
                // Furthermore it would propagate to components and child nodes, which is not desired in this case
            }
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
            unsigned nodeID = msg.ReadNetID();
            Node* node = scene_->GetNode(nodeID);
            if (node)
                node->Remove();
            nodeLatestData_.Erase(nodeID);
        }
        break;

    case MSG_CREATECOMPONENT:
        {
            unsigned nodeID = msg.ReadNetID();
            Node* node = scene_->GetNode(nodeID);
            if (node)
            {
                StringHash type = msg.ReadStringHash();
                unsigned componentID = msg.ReadNetID();

                // Check if the component by this ID and type already exists in this node
                Component* component = scene_->GetComponent(componentID);
                if (!component || component->GetType() != type || component->GetNode() != node)
                {
                    if (component)
                        component->Remove();
                    component = node->CreateComponent(type, REPLICATED, componentID);
                }

                // If was unable to create the component, would desync the message and therefore have to abort
                if (!component)
                {
                    URHO3D_LOGERROR("CreateComponent message parsing aborted due to unknown component");
                    return;
                }

                // Read initial attributes and apply
                component->ReadDeltaUpdate(msg);
                component->ApplyAttributes();
            }
            else
                URHO3D_LOGWARNING("CreateComponent message received for missing node " + String(nodeID));
        }
        break;

    case MSG_COMPONENTDELTAUPDATE:
        {
            unsigned componentID = msg.ReadNetID();
            Component* component = scene_->GetComponent(componentID);
            if (component)
            {
                component->ReadDeltaUpdate(msg);
                component->ApplyAttributes();
            }
            else
                URHO3D_LOGWARNING("ComponentDeltaUpdate message received for missing component " + String(componentID));
        }
        break;

    case MSG_COMPONENTLATESTDATA:
        {
            unsigned componentID = msg.ReadNetID();
            Component* component = scene_->GetComponent(componentID);
            if (component)
            {
                if (component->ReadLatestDataUpdate(msg))
                    component->ApplyAttributes();
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
            unsigned componentID = msg.ReadNetID();
            Component* component = scene_->GetComponent(componentID);
            if (component)
                component->Remove();
            componentLatestData_.Erase(componentID);
        }
        break;

    default: break;
    }
}

void Connection::ProcessPackageDownload(int msgID, MemoryBuffer& msg)
{
    switch (msgID)
    {
    case MSG_REQUESTPACKAGE:
        if (!IsClient())
        {
            URHO3D_LOGWARNING("Received unexpected RequestPackage message from server");
            return;
        }
        else
        {
            String name = msg.ReadString();

            if (!scene_)
            {
                URHO3D_LOGWARNING("Received a RequestPackage message without an assigned scene from client " + ToString());
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
                    StringHash nameHash(name);

                    // Do not restart upload if already exists
                    if (uploads_.Contains(nameHash))
                    {
                        URHO3D_LOGWARNING("Received a request for package " + name + " already in transfer");
                        return;
                    }

                    // Try to open the file now
                    SharedPtr<File> file(new File(context_, packageFullName));
                    if (!file->IsOpen())
                    {
                        URHO3D_LOGERROR("Failed to transmit package file " + name);
                        SendPackageError(name);
                        return;
                    }

                    URHO3D_LOGINFO("Transmitting package file " + name + " to client " + ToString());

                    uploads_[nameHash].file_ = file;
                    uploads_[nameHash].fragment_ = 0;
                    uploads_[nameHash].totalFragments_ = (file->GetSize() + PACKAGE_FRAGMENT_SIZE - 1) / PACKAGE_FRAGMENT_SIZE;
                    return;
                }
            }

            URHO3D_LOGERROR("Client requested an unexpected package file " + name);
            // Send the name hash only to indicate a failed download
            SendPackageError(name);
            return;
        }
        break;

    case MSG_PACKAGEDATA:
        if (IsClient())
        {
            URHO3D_LOGWARNING("Received unexpected PackageData message from client");
            return;
        }
        else
        {
            StringHash nameHash = msg.ReadStringHash();

            HashMap<StringHash, PackageDownload>::Iterator i = downloads_.Find(nameHash);
            // In case of being unable to create the package file into the cache, we will still receive all data from the server.
            // Simply disregard it
            if (i == downloads_.End())
                return;

            PackageDownload& download = i->second_;

            // If no further data, this is an error reply
            if (msg.IsEof())
            {
                OnPackageDownloadFailed(download.name_);
                return;
            }

            // If file has not yet been opened, try to open now. Prepend the checksum to the filename to allow multiple versions
            if (!download.file_)
            {
                download.file_ = new File(context_,
                    GetSubsystem<Network>()->GetPackageCacheDir() + ToStringHex(download.checksum_) + "_" + download.name_,
                    FILE_WRITE);
                if (!download.file_->IsOpen())
                {
                    OnPackageDownloadFailed(download.name_);
                    return;
                }
            }

            // Write the fragment data to the proper index
            unsigned char buffer[PACKAGE_FRAGMENT_SIZE];
            unsigned index = msg.ReadUInt();
            unsigned fragmentSize = msg.GetSize() - msg.GetPosition();

            msg.Read(buffer, fragmentSize);
            download.file_->Seek(index * PACKAGE_FRAGMENT_SIZE);
            download.file_->Write(buffer, fragmentSize);
            download.receivedFragments_.Insert(index);

            // Check if all fragments received
            if (download.receivedFragments_.Size() == download.totalFragments_)
            {
                URHO3D_LOGINFO("Package " + download.name_ + " downloaded successfully");

                // Instantiate the package and add to the resource system, as we will need it to load the scene
                download.file_->Close();
                GetSubsystem<ResourceCache>()->AddPackageFile(download.file_->GetName(), 0);

                // Then start the next download if there are more
                downloads_.Erase(i);
                if (downloads_.Empty())
                    OnPackagesReady();
                else
                {
                    PackageDownload& nextDownload = downloads_.Begin()->second_;

                    URHO3D_LOGINFO("Requesting package " + nextDownload.name_ + " from server");
                    msg_.Clear();
                    msg_.WriteString(nextDownload.name_);
                    SendMessage(MSG_REQUESTPACKAGE, true, true, msg_);
                    nextDownload.initiated_ = true;
                }
            }
        }
        break;

    default: break;
    }
}

void Connection::ProcessIdentity(int msgID, MemoryBuffer& msg)
{
    if (!IsClient())
    {
        URHO3D_LOGWARNING("Received unexpected Identity message from server");
        return;
    }

    identity_ = msg.ReadVariantMap();

    using namespace ClientIdentity;

    VariantMap eventData = identity_;
    eventData[P_CONNECTION] = this;
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
        URHO3D_LOGWARNING("Received unexpected Controls message from server");
        return;
    }

    Controls newControls;
    newControls.buttons_ = msg.ReadUInt();
    newControls.yaw_ = msg.ReadFloat();
    newControls.pitch_ = msg.ReadFloat();
    newControls.extraData_ = msg.ReadVariantMap();

    SetControls(newControls);
    timeStamp_ = msg.ReadUByte();

    // Client may or may not send observer position & rotation for interest management
    if (!msg.IsEof())
        position_ = msg.ReadVector3();
    if (!msg.IsEof())
        rotation_ = msg.ReadPackedQuaternion();
}

void Connection::ProcessSceneLoaded(int msgID, MemoryBuffer& msg)
{
    if (!IsClient())
    {
        URHO3D_LOGWARNING("Received unexpected SceneLoaded message from server");
        return;
    }

    if (!scene_)
    {
        URHO3D_LOGWARNING("Received a SceneLoaded message without an assigned scene from client " + ToString());
        return;
    }

    unsigned checksum = msg.ReadUInt();

    if (checksum != scene_->GetChecksum())
    {
        URHO3D_LOGINFO("Scene checksum error from client " + ToString());
        msg_.Clear();
        SendMessage(MSG_SCENECHECKSUMERROR, true, true, msg_);
        OnSceneLoadFailed();
    }
    else
    {
        sceneLoaded_ = true;

        using namespace ClientSceneLoaded;

        VariantMap& eventData = GetEventDataMap();
        eventData[P_CONNECTION] = this;
        SendEvent(E_CLIENTSCENELOADED, eventData);
    }
}

void Connection::ProcessRemoteEvent(int msgID, MemoryBuffer& msg)
{
    using namespace RemoteEventData;

    if (msgID == MSG_REMOTEEVENT)
    {
        StringHash eventType = msg.ReadStringHash();
        if (!GetSubsystem<Network>()->CheckRemoteEvent(eventType))
        {
            URHO3D_LOGWARNING("Discarding not allowed remote event " + eventType.ToString());
            return;
        }

        VariantMap eventData = msg.ReadVariantMap();
        eventData[P_CONNECTION] = this;
        SendEvent(eventType, eventData);
    }
    else
    {
        if (!scene_)
        {
            URHO3D_LOGERROR("Can not receive remote node event without an assigned scene");
            return;
        }

        unsigned nodeID = msg.ReadNetID();
        StringHash eventType = msg.ReadStringHash();
        if (!GetSubsystem<Network>()->CheckRemoteEvent(eventType))
        {
            URHO3D_LOGWARNING("Discarding not allowed remote event " + eventType.ToString());
            return;
        }

        VariantMap eventData = msg.ReadVariantMap();
        Node* sender = scene_->GetNode(nodeID);
        if (!sender)
        {
            URHO3D_LOGWARNING("Missing sender for remote node event, discarding");
            return;
        }
        eventData[P_CONNECTION] = this;
        sender->SendEvent(eventType, eventData);
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

float Connection::GetRoundTripTime() const
{
    return connection_->RoundTripTime();
}

float Connection::GetLastHeardTime() const
{
    return connection_->LastHeardTime();
}

float Connection::GetBytesInPerSec() const
{
    return connection_->BytesInPerSec();
}

float Connection::GetBytesOutPerSec() const
{
    return connection_->BytesOutPerSec();
}

float Connection::GetPacketsInPerSec() const
{
    return connection_->PacketsInPerSec();
}

float Connection::GetPacketsOutPerSec() const
{
    return connection_->PacketsOutPerSec();
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
    for (HashMap<StringHash, PackageDownload>::ConstIterator i = downloads_.Begin(); i != downloads_.End(); ++i)
    {
        if (i->second_.initiated_)
            return i->second_.name_;
    }
    return String::EMPTY;
}

float Connection::GetDownloadProgress() const
{
    for (HashMap<StringHash, PackageDownload>::ConstIterator i = downloads_.Begin(); i != downloads_.End(); ++i)
    {
        if (i->second_.initiated_)
            return (float)i->second_.receivedFragments_.Size() / (float)i->second_.totalFragments_;
    }
    return 1.0f;
}

void Connection::SendPackageToClient(PackageFile* package)
{
    if (!scene_)
        return;

    if (!IsClient())
    {
        URHO3D_LOGERROR("SendPackageToClient can be called on the server only");
        return;
    }
    if (!package)
    {
        URHO3D_LOGERROR("Null package specified for SendPackageToClient");
        return;
    }

    msg_.Clear();

    String filename = GetFileNameAndExtension(package->GetName());
    msg_.WriteString(filename);
    msg_.WriteUInt(package->GetTotalSize());
    msg_.WriteUInt(package->GetChecksum());
    SendMessage(MSG_PACKAGEINFO, true, true, msg_);
}

void Connection::ConfigureNetworkSimulator(int latencyMs, float packetLoss)
{
    if (connection_)
    {
        kNet::NetworkSimulator& simulator = connection_->NetworkSendSimulator();
        simulator.enabled = latencyMs > 0 || packetLoss > 0.0f;
        simulator.constantPacketSendDelay = (float)latencyMs;
        simulator.packetLossRate = packetLoss;
    }
}

void Connection::HandleAsyncLoadFinished(StringHash eventType, VariantMap& eventData)
{
    sceneLoaded_ = true;

    msg_.Clear();
    msg_.WriteUInt(scene_->GetChecksum());
    SendMessage(MSG_SCENELOADED, true, true, msg_);
}

void Connection::ProcessNode(unsigned nodeID)
{
    // Check that we have not already processed this due to dependency recursion
    if (!nodesToProcess_.Erase(nodeID))
        return;

    // Find replication state for the node
    HashMap<unsigned, NodeReplicationState>::Iterator i = sceneState_.nodeStates_.Find(nodeID);
    if (i != sceneState_.nodeStates_.End())
    {
        // Replication state found: the node is either be existing or removed
        Node* node = i->second_.node_;
        if (!node)
        {
            msg_.Clear();
            msg_.WriteNetID(nodeID);

            // Note: we will send MSG_REMOVENODE redundantly for each node in the hierarchy, even if removing the root node
            // would be enough. However, this may be better due to the client not possibly having updated parenting
            // information at the time of receiving this message
            SendMessage(MSG_REMOVENODE, true, true, msg_);
            sceneState_.nodeStates_.Erase(nodeID);
        }
        else
            ProcessExistingNode(node, i->second_);
    }
    else
    {
        // Replication state not found: this is a new node
        Node* node = scene_->GetNode(nodeID);
        if (node)
            ProcessNewNode(node);
        else
        {
            // Did not find the new node (may have been created, then removed immediately): erase from dirty set.
            sceneState_.dirtyNodes_.Erase(nodeID);
        }
    }
}

void Connection::ProcessNewNode(Node* node)
{
    // Process depended upon nodes first, if they are dirty
    const PODVector<Node*>& dependencyNodes = node->GetDependencyNodes();
    for (PODVector<Node*>::ConstIterator i = dependencyNodes.Begin(); i != dependencyNodes.End(); ++i)
    {
        unsigned nodeID = (*i)->GetID();
        if (sceneState_.dirtyNodes_.Contains(nodeID))
            ProcessNode(nodeID);
    }

    msg_.Clear();
    msg_.WriteNetID(node->GetID());

    NodeReplicationState& nodeState = sceneState_.nodeStates_[node->GetID()];
    nodeState.connection_ = this;
    nodeState.sceneState_ = &sceneState_;
    nodeState.node_ = node;
    node->AddReplicationState(&nodeState);

    // Write node's attributes
    node->WriteInitialDeltaUpdate(msg_, timeStamp_);

    // Write node's user variables
    const VariantMap& vars = node->GetVars();
    msg_.WriteVLE(vars.Size());
    for (VariantMap::ConstIterator i = vars.Begin(); i != vars.End(); ++i)
    {
        msg_.WriteStringHash(i->first_);
        msg_.WriteVariant(i->second_);
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

        ComponentReplicationState& componentState = nodeState.componentStates_[component->GetID()];
        componentState.connection_ = this;
        componentState.nodeState_ = &nodeState;
        componentState.component_ = component;
        component->AddReplicationState(&componentState);

        msg_.WriteStringHash(component->GetType());
        msg_.WriteNetID(component->GetID());
        component->WriteInitialDeltaUpdate(msg_, timeStamp_);
    }

    SendMessage(MSG_CREATENODE, true, true, msg_);

    nodeState.markedDirty_ = false;
    sceneState_.dirtyNodes_.Erase(node->GetID());
}

void Connection::ProcessExistingNode(Node* node, NodeReplicationState& nodeState)
{
    // Process depended upon nodes first, if they are dirty
    const PODVector<Node*>& dependencyNodes = node->GetDependencyNodes();
    for (PODVector<Node*>::ConstIterator i = dependencyNodes.Begin(); i != dependencyNodes.End(); ++i)
    {
        unsigned nodeID = (*i)->GetID();
        if (sceneState_.dirtyNodes_.Contains(nodeID))
            ProcessNode(nodeID);
    }

    // Check from the interest management component, if exists, whether should update
    /// \todo Searching for the component is a potential CPU hotspot. It should be cached
    NetworkPriority* priority = node->GetComponent<NetworkPriority>();
    if (priority && (!priority->GetAlwaysUpdateOwner() || node->GetOwner() != this))
    {
        float distance = (node->GetWorldPosition() - position_).Length();
        if (!priority->CheckUpdate(distance, nodeState.priorityAcc_))
            return;
    }

    // Check if attributes have changed
    if (nodeState.dirtyAttributes_.Count() || nodeState.dirtyVars_.Size())
    {
        const Vector<AttributeInfo>* attributes = node->GetNetworkAttributes();
        unsigned numAttributes = attributes->Size();
        bool hasLatestData = false;

        for (unsigned i = 0; i < numAttributes; ++i)
        {
            if (nodeState.dirtyAttributes_.IsSet(i) && (attributes->At(i).mode_ & AM_LATESTDATA))
            {
                hasLatestData = true;
                nodeState.dirtyAttributes_.Clear(i);
            }
        }

        // Send latestdata message if necessary
        if (hasLatestData)
        {
            msg_.Clear();
            msg_.WriteNetID(node->GetID());
            node->WriteLatestDataUpdate(msg_, timeStamp_);

            SendMessage(MSG_NODELATESTDATA, true, false, msg_, node->GetID());
        }

        // Send deltaupdate if remaining dirty bits, or vars have changed
        if (nodeState.dirtyAttributes_.Count() || nodeState.dirtyVars_.Size())
        {
            msg_.Clear();
            msg_.WriteNetID(node->GetID());
            node->WriteDeltaUpdate(msg_, nodeState.dirtyAttributes_, timeStamp_);

            // Write changed variables
            msg_.WriteVLE(nodeState.dirtyVars_.Size());
            const VariantMap& vars = node->GetVars();
            for (HashSet<StringHash>::ConstIterator i = nodeState.dirtyVars_.Begin(); i != nodeState.dirtyVars_.End(); ++i)
            {
                VariantMap::ConstIterator j = vars.Find(*i);
                if (j != vars.End())
                {
                    msg_.WriteStringHash(j->first_);
                    msg_.WriteVariant(j->second_);
                }
                else
                {
                    // Variable has been marked dirty, but is removed (which is unsupported): send a dummy variable in place
                    URHO3D_LOGWARNING("Sending dummy user variable as original value was removed");
                    msg_.WriteStringHash(StringHash());
                    msg_.WriteVariant(Variant::EMPTY);
                }
            }

            SendMessage(MSG_NODEDELTAUPDATE, true, true, msg_);

            nodeState.dirtyAttributes_.ClearAll();
            nodeState.dirtyVars_.Clear();
        }
    }

    // Check for removed or changed components
    for (HashMap<unsigned, ComponentReplicationState>::Iterator i = nodeState.componentStates_.Begin();
         i != nodeState.componentStates_.End();)
    {
        HashMap<unsigned, ComponentReplicationState>::Iterator current = i++;
        ComponentReplicationState& componentState = current->second_;
        Component* component = componentState.component_;
        if (!component)
        {
            // Removed component
            msg_.Clear();
            msg_.WriteNetID(current->first_);

            SendMessage(MSG_REMOVECOMPONENT, true, true, msg_);
            nodeState.componentStates_.Erase(current);
        }
        else
        {
            // Existing component. Check if attributes have changed
            if (componentState.dirtyAttributes_.Count())
            {
                const Vector<AttributeInfo>* attributes = component->GetNetworkAttributes();
                unsigned numAttributes = attributes->Size();
                bool hasLatestData = false;

                for (unsigned i = 0; i < numAttributes; ++i)
                {
                    if (componentState.dirtyAttributes_.IsSet(i) && (attributes->At(i).mode_ & AM_LATESTDATA))
                    {
                        hasLatestData = true;
                        componentState.dirtyAttributes_.Clear(i);
                    }
                }

                // Send latestdata message if necessary
                if (hasLatestData)
                {
                    msg_.Clear();
                    msg_.WriteNetID(component->GetID());
                    component->WriteLatestDataUpdate(msg_, timeStamp_);

                    SendMessage(MSG_COMPONENTLATESTDATA, true, false, msg_, component->GetID());
                }

                // Send deltaupdate if remaining dirty bits
                if (componentState.dirtyAttributes_.Count())
                {
                    msg_.Clear();
                    msg_.WriteNetID(component->GetID());
                    component->WriteDeltaUpdate(msg_, componentState.dirtyAttributes_, timeStamp_);

                    SendMessage(MSG_COMPONENTDELTAUPDATE, true, true, msg_);

                    componentState.dirtyAttributes_.ClearAll();
                }
            }
        }
    }

    // Check for new components
    if (nodeState.componentStates_.Size() != node->GetNumNetworkComponents())
    {
        const Vector<SharedPtr<Component> >& components = node->GetComponents();
        for (unsigned i = 0; i < components.Size(); ++i)
        {
            Component* component = components[i];
            // Check if component is not to be replicated
            if (component->GetID() >= FIRST_LOCAL_ID)
                continue;

            HashMap<unsigned, ComponentReplicationState>::Iterator j = nodeState.componentStates_.Find(component->GetID());
            if (j == nodeState.componentStates_.End())
            {
                // New component
                ComponentReplicationState& componentState = nodeState.componentStates_[component->GetID()];
                componentState.connection_ = this;
                componentState.nodeState_ = &nodeState;
                componentState.component_ = component;
                component->AddReplicationState(&componentState);

                msg_.Clear();
                msg_.WriteNetID(node->GetID());
                msg_.WriteStringHash(component->GetType());
                msg_.WriteNetID(component->GetID());
                component->WriteInitialDeltaUpdate(msg_, timeStamp_);

                SendMessage(MSG_CREATECOMPONENT, true, true, msg_);
            }
        }
    }

    nodeState.markedDirty_ = false;
    sceneState_.dirtyNodes_.Erase(node->GetID());
}

bool Connection::RequestNeededPackages(unsigned numPackages, MemoryBuffer& msg)
{
    ResourceCache* cache = GetSubsystem<ResourceCache>();
    const String& packageCacheDir = GetSubsystem<Network>()->GetPackageCacheDir();

    Vector<SharedPtr<PackageFile> > packages = cache->GetPackageFiles();
    Vector<String> downloadedPackages;
    bool packagesScanned = false;

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

        if (found)
            continue;

        if (!packagesScanned)
        {
            if (packageCacheDir.Empty())
            {
                URHO3D_LOGERROR("Can not check/download required packages, as package cache directory is not set");
                return false;
            }

            GetSubsystem<FileSystem>()->ScanDir(downloadedPackages, packageCacheDir, "*.*", SCAN_FILES, false);
            packagesScanned = true;
        }

        // Then the download cache
        for (unsigned j = 0; j < downloadedPackages.Size(); ++j)
        {
            const String& fileName = downloadedPackages[j];
            // In download cache, package file name format is checksum_packagename
            if (!fileName.Find(checksumString) && !fileName.Substring(9).Compare(name, false))
            {
                // Name matches. Check file size and actual checksum to be sure
                SharedPtr<PackageFile> newPackage(new PackageFile(context_, packageCacheDir + fileName));
                if (newPackage->GetTotalSize() == fileSize && newPackage->GetChecksum() == checksum)
                {
                    // Add the package to the resource system now, as we will need it to load the scene
                    cache->AddPackageFile(newPackage, 0);
                    found = true;
                    break;
                }
            }
        }

        // Package not found, need to request a download
        if (!found)
            RequestPackage(name, fileSize, checksum);
    }

    return true;
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
        URHO3D_LOGINFO("Requesting package " + name + " from server");
        msg_.Clear();
        msg_.WriteString(name);
        SendMessage(MSG_REQUESTPACKAGE, true, true, msg_);
        download.initiated_ = true;
    }
}

void Connection::SendPackageError(const String& name)
{
    msg_.Clear();
    msg_.WriteStringHash(name);
    SendMessage(MSG_PACKAGEDATA, true, false, msg_);
}

void Connection::OnSceneLoadFailed()
{
    sceneLoaded_ = false;

    using namespace NetworkSceneLoadFailed;

    VariantMap& eventData = GetEventDataMap();
    eventData[P_CONNECTION] = this;
    SendEvent(E_NETWORKSCENELOADFAILED, eventData);
}

void Connection::OnPackageDownloadFailed(const String& name)
{
    URHO3D_LOGERROR("Download of package " + name + " failed");
    // As one package failed, we can not join the scene in any case. Clear the downloads
    downloads_.Clear();
    OnSceneLoadFailed();
}

void Connection::OnPackagesReady()
{
    if (!scene_)
        return;

    // If sceneLoaded_ is true, we may have received additional package downloads while already joined in a scene.
    // In that case the scene should not be loaded.
    if (sceneLoaded_)
        return;

    if (sceneFileName_.Empty())
    {
        // If the scene filename is empty, just clear the scene of all existing replicated content, and send the loaded reply
        scene_->Clear(true, false);
        sceneLoaded_ = true;

        msg_.Clear();
        msg_.WriteUInt(scene_->GetChecksum());
        SendMessage(MSG_SCENELOADED, true, true, msg_);
    }
    else
    {
        // Otherwise start the async loading process
        String extension = GetExtension(sceneFileName_);
        SharedPtr<File> file = GetSubsystem<ResourceCache>()->GetFile(sceneFileName_);
        bool success;

        if (extension == ".xml")
            success = scene_->LoadAsyncXML(file);
        else
            success = scene_->LoadAsync(file);

        if (!success)
            OnSceneLoadFailed();
    }
}

void Connection::ProcessPackageInfo(int msgID, MemoryBuffer& msg)
{
    if (!scene_)
        return;

    if (IsClient())
    {
        URHO3D_LOGWARNING("Received unexpected packages info message from client");
        return;
    }

    RequestNeededPackages(1, msg);
}

}
