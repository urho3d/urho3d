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
#include "NetworkEvents.h"
#include "Profiler.h"
#include "Protocol.h"
#include "Scene.h"
#include "SceneEvents.h"

#include <kNet.h>

#include "DebugNew.h"

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
    // Reset owner from the scene, as this connection is about to be destroyed
    if (scene_)
        scene_->ResetOwner(this);
}

void Connection::SendMessage(int msgID, bool reliable, bool inOrder, const unsigned char* data, unsigned numBytes)
{
    // Make sure not to use kNet internal message ID's
    if (msgID <= 0x4 || msgID >= 0x3ffffffe)
    {
        LOGERROR("Can not send message with reserved ID");
        return;
    }
    
    connection_->SendMessage(msgID, reliable, inOrder, 0, 0, (const char*)data, numBytes);
}

void Connection::SendMessage(int msgID, bool reliable, bool inOrder, const VectorBuffer& msg)
{
    SendMessage(msgID, reliable, inOrder, msg.GetData(), msg.GetSize());
}

void Connection::SendMessage(int msgID, unsigned contentID, bool reliable, bool inOrder, const unsigned char* data, unsigned numBytes)
{
    // Make sure not to use kNet internal message ID's
    if (msgID <= 0x4 || msgID >= 0x3ffffffe)
    {
        LOGERROR("Can not send message with reserved ID");
        return;
    }
    
    connection_->SendMessage(msgID, reliable, inOrder, 0, contentID, (const char*)data, numBytes);
}

void Connection::SendMessage(int msgID, unsigned contentID, bool reliable, bool inOrder, const VectorBuffer& msg)
{
    SendMessage(msgID, contentID, reliable, inOrder, msg.GetData(), msg.GetSize());
}

void Connection::SendRemoteEvent(StringHash eventType, bool inOrder, const VariantMap& eventData)
{
    msg_.Clear();
    msg_.WriteStringHash(eventType);
    msg_.WriteVariantMap(eventData);
    SendMessage(MSG_REMOTEEVENT, true, inOrder, msg_);
}

void Connection::SendRemoteEvent(Node* receiver, StringHash eventType, bool inOrder, const VariantMap& eventData)
{
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
    
    msg_.Clear();
    msg_.WriteVLE(receiver->GetID());
    msg_.WriteStringHash(eventType);
    msg_.WriteVariantMap(eventData);
    SendMessage(MSG_REMOTENODEEVENT, true, inOrder, msg_);
}

void Connection::SetScene(Scene* newScene)
{
    if (scene_ == newScene)
        return;
    
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
        
        // When scene is assigned on the server, instruct the client to load it
        /// \todo Download package(s) needed for the scene, if they do not exist already on the client
        msg_.Clear();
        msg_.WriteString(scene_->GetFileName());
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
    
    String fileName = msg.ReadString();
    
    // Make sure there is no existing async loading, and clear previous pending latest data if any
    scene_->StopAsyncLoading();
    nodeLatestData_.Clear();
    componentLatestData_.Clear();
    
    if (fileName.Empty())
    {
        scene_->Clear();
        
        // If filename is empty, can send the scene loaded reply immediately
        VectorBuffer replyMsg;
        replyMsg.WriteUInt(scene_->GetChecksum());
        SendMessage(MSG_SCENELOADED, true, true, replyMsg);
    }
    else
    {
        // Otherwise start the async loading process
        String extension = GetExtension(fileName);
        SharedPtr<File> file(new File(context_, fileName));
        bool success;
        
        if (extension == ".xml")
            success = scene_->LoadAsyncXML(file);
        else
            success = scene_->LoadAsync(file);
        
        if (!success)
        {
            using namespace NetworkSceneLoadFailed;
            
            VariantMap eventData;
            eventData[P_CONNECTION] = (void*)this;
            SendEvent(E_NETWORKSCENELOADFAILED, eventData);
        }
    }
}

void Connection::ProcessSceneChecksumError(int msgID, MemoryBuffer& msg)
{
    if (IsClient())
    {
        LOGWARNING("Received unexpected SceneChecksumError message from client " + ToString());
        return;
    }
    
    using namespace NetworkSceneLoadFailed;
    
    VariantMap eventData;
    eventData[P_CONNECTION] = (void*)this;
    SendEvent(E_NETWORKSCENELOADFAILED, eventData);
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
        VectorBuffer replyMsg;
        SendMessage(MSG_SCENECHECKSUMERROR, true, true, replyMsg);
        
        using namespace NetworkSceneLoadFailed;
        
        VariantMap eventData;
        eventData[P_CONNECTION] = (void*)this;
        SendEvent(E_NETWORKSCENELOADFAILED, eventData);
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
    /// \todo Check whether the remote event is allowed based on a black- or whitelist
    if (msgID == MSG_REMOTEEVENT)
    {
        StringHash eventType = msg.ReadStringHash();
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

void Connection::ProcessNode(Node* node)
{
    if (!node || processedNodes_.Contains(node))
        return;
    
    processedNodes_.Insert(node);
    
    // Process depended upon nodes first
    PODVector<Node*> depends;
    node->GetDependencyNodes(depends);
    for (PODVector<Node*>::ConstIterator i = depends.Begin(); i != depends.End(); ++i)
        ProcessNode(*i);
    
    // Check if the client's scene state already has this node
    if (sceneState_.Find(node->GetID()) != sceneState_.End())
        ProcessExistingNode(node);
    else
        ProcessNewNode(node);
}

void Connection::ProcessNewNode(Node* node)
{
    msg_.Clear();
    msg_.WriteVLE(node->GetID());
    
    NodeReplicationState newNodeState;
    newNodeState.frameNumber_ = frameNumber_;
    
    // Write node's attributes
    node->WriteInitialDeltaUpdate(msg_, deltaUpdateBits_, newNodeState.attributes_);
    
    // Write node's user variables
    const VariantMap& vars = node->GetVars();
    msg_.WriteVLE(vars.Size());
    for (VariantMap::ConstIterator i = vars.Begin(); i != vars.End(); ++i)
    {
        msg_.WriteShortStringHash(i->first_);
        msg_.WriteVariant(i->second_);
        newNodeState.vars_[i->first_] = i->second_;
    }
    
    // Write node's components
    msg_.WriteVLE(node->GetNumNetworkComponents());
    const Vector<SharedPtr<Component> >& components = node->GetComponents();
    for (unsigned i = 0; i < components.Size(); ++i)
    {
        Component* component = components[i];
        if (component->GetID() >= FIRST_LOCAL_ID)
            continue;
        
        msg_.WriteShortStringHash(component->GetType());
        msg_.WriteVLE(component->GetID());
        
        ComponentReplicationState newComponentState;
        newComponentState.frameNumber_ = frameNumber_;
        newComponentState.type_ = component->GetType();
        
        // Write component's attributes
        component->WriteInitialDeltaUpdate(msg_, deltaUpdateBits_, newComponentState.attributes_);
        
        newNodeState.components_[component->GetID()] = newComponentState;
    }
    
    SendMessage(MSG_CREATENODE, true, true, msg_);
    sceneState_[node->GetID()] = newNodeState;
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
        if (component->GetID() >= FIRST_LOCAL_ID)
            continue;
        
        Map<unsigned, ComponentReplicationState>::Iterator j = nodeState.components_.Find(component->GetID());
        if (j == nodeState.components_.End())
        {
            // New component
            msg_.Clear();
            msg_.WriteVLE(node->GetID());
            msg_.WriteShortStringHash(component->GetType());
            msg_.WriteVLE(component->GetID());
            
            ComponentReplicationState newComponentState;
            newComponentState.frameNumber_ = frameNumber_;
            newComponentState.type_ = component->GetType();
            
            // Write component's attributes
            component->WriteInitialDeltaUpdate(msg_, deltaUpdateBits_, newComponentState.attributes_);
            
            SendMessage(MSG_CREATECOMPONENT, true, true, msg_);
            nodeState.components_[component->GetID()] = newComponentState;
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

void Connection::HandleAsyncLoadFinished(StringHash eventType, VariantMap& eventData)
{
    VectorBuffer msg;
    msg.WriteUInt(scene_->GetChecksum());
    SendMessage(MSG_SCENELOADED, true, true, msg);
}
