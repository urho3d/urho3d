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
#include "Log.h"
#include "Protocol.h"
#include "Scene.h"

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
    
    // Reset the owner reference from the previous scene's nodes
    if (scene_)
        scene_->ResetOwner(this);
    
    scene_ = newScene;
    sceneLoaded_ = false;
    
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
        // Make sure there is no existing async loading
        scene_->StopAsyncLoading();
    }
}

void Connection::SetSceneLoaded(bool loaded)
{
    sceneLoaded_ = loaded;
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

void Connection::ProcessReplication()
{
    if (!isClient_ || !scene_ || !sceneLoaded_)
        return;
    
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
    WriteInitialAttributes(msg_, node, newNodeState.attributes_);
    
    // Write node's variable map
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
        WriteInitialAttributes(msg_, component, newComponentState.attributes_);
        
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
    bool deltaUpdate = false;
    bool latestData = false;
    const Vector<AttributeInfo>* attributes = node->GetAttributes();
    deltaUpdateBits_.Resize((node->GetNumNetworkAttributes() + 7) >> 3);
    for (unsigned i = 0; i < deltaUpdateBits_.Size(); ++i)
        deltaUpdateBits_[i] = 0;
    unsigned index = 0;
    
    for (unsigned i = 0; i < attributes->Size(); ++i)
    {
        const AttributeInfo& attr = attributes->At(i);
        if (!(attr.mode_ & AM_NET))
            continue;
        
        // Check for attribute change
        Variant value = node->GetAttribute(i);
        if (value != nodeState.attributes_[index])
        {
            nodeState.attributes_[index] = value;
            if (attr.mode_ & AM_LATESTDATA)
                latestData = true;
            else
            {
                deltaUpdate = true;
                deltaUpdateBits_[index >> 3] |= 1 << (index & 7);
            }
        }
        
        ++index;
    }
    
    // Check if variable map has changed. Note: variable removal is not supported
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
        
        // Write changed attributes
        msg_.Write(&deltaUpdateBits_[0], deltaUpdateBits_.Size());
        
        index = 0;
        for (unsigned i = 0; i < attributes->Size(); ++i)
        {
            const AttributeInfo& attr = attributes->At(i);
            if (!(attr.mode_ & AM_NET))
                continue;
            
            if (deltaUpdateBits_[index << 3] & (1 << (index & 7)))
                msg_.WriteVariantData(nodeState.attributes_[index]);
            
            ++index;
        }
        
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
        
        index = 0;
        for (unsigned i = 0; i < attributes->Size(); ++i)
        {
            const AttributeInfo& attr = attributes->At(i);
            if (!(attr.mode_ & AM_NET))
                continue;
            
            if (attr.mode_ & AM_LATESTDATA)
                msg_.WriteVariantData(nodeState.attributes_[index]);
            
            ++index;
        }
        
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
            WriteInitialAttributes(msg_, component, newComponentState.attributes_);
            
            SendMessage(MSG_CREATECOMPONENT, true, true, msg_);
            nodeState.components_[component->GetID()] = newComponentState;
        }
        else
        {
            // Existing component
            ComponentReplicationState& componentState = j->second_;
            componentState.frameNumber_ = frameNumber_;
            
            deltaUpdate = false;
            latestData = false;
            const Vector<AttributeInfo>* attributes = component->GetAttributes();
            deltaUpdateBits_.Resize((component->GetNumNetworkAttributes() + 7) >> 3);
            for (unsigned k = 0; k < deltaUpdateBits_.Size(); ++k)
                deltaUpdateBits_[k] = 0;
            index = 0;
            
            for (unsigned k = 0; k < attributes->Size(); ++k)
            {
                const AttributeInfo& attr = attributes->At(k);
                if (!(attr.mode_ & AM_NET))
                    continue;
                
                // Check for attribute change
                Variant value = component->GetAttribute(k);
                if (value != componentState.attributes_[index])
                {
                    componentState.attributes_[index] = value;
                    if (attr.mode_ & AM_LATESTDATA)
                        latestData = true;
                    else
                    {
                        deltaUpdate = true;
                        deltaUpdateBits_[index >> 3] |= 1 << (index & 7);
                    }
                }
                
                ++index;
            }
            
            // Send deltaupdate message if necessary
            if (deltaUpdate)
            {
                msg_.Clear();
                msg_.WriteVLE(component->GetID());
                
                // Write changed attributes
                msg_.Write(&deltaUpdateBits_[0], deltaUpdateBits_.Size());
                
                index = 0;
                for (unsigned k = 0; k < attributes->Size(); ++k)
                {
                    const AttributeInfo& attr = attributes->At(k);
                    if (!(attr.mode_ & AM_NET))
                        continue;
                    
                    if (deltaUpdateBits_[index << 3] & (1 << (index & 7)))
                        msg_.WriteVariantData(componentState.attributes_[index]);
                    
                    ++index;
                }
                
                SendMessage(MSG_COMPONENTDELTAUPDATE, true, true, msg_);
            }
            
            // Send latestdata message if necessary
            if (latestData)
            {
                // If at least one latest data attribute changes, send all of them
                msg_.Clear();
                msg_.WriteVLE(component->GetID());
                
                index = 0;
                for (unsigned k = 0; k < attributes->Size(); ++k)
                {
                    const AttributeInfo& attr = attributes->At(k);
                    if (!(attr.mode_ & AM_NET))
                        continue;
                    
                    if (attr.mode_ & AM_LATESTDATA)
                        msg_.WriteVariantData(componentState.attributes_[index]);
                    
                    ++index;
                }
                
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
            msg_.WriteVLE(node->GetID());
            msg_.WriteVLE(current->first_);
            
            SendMessage(MSG_REMOVECOMPONENT, true, true, msg_);
            nodeState.components_.Erase(current);
        }
    }
}

void Connection::WriteInitialAttributes(VectorBuffer& msg, Serializable* serializable, Vector<Variant>& attributeState)
{
    const Vector<AttributeInfo>* attributes = serializable->GetAttributes();
    unsigned numAttributes = serializable->GetNumNetworkAttributes();
    if (!numAttributes)
        return;
    
    attributeState.Resize(numAttributes);
    
    deltaUpdateBits_.Resize((numAttributes + 7) >> 3);
    for (unsigned i = 0; i < deltaUpdateBits_.Size(); ++i)
        deltaUpdateBits_[i] = 0;
    
    unsigned index = 0;
    for (unsigned i = 0; i < attributes->Size(); ++i)
    {
        const AttributeInfo& attr = attributes->At(i);
        if (!(attr.mode_ & AM_NET))
            continue;
        
        Variant value = serializable->GetAttribute(i);
        if (value != attr.defaultValue_)
        {
            attributeState[index] = value;
            deltaUpdateBits_[index >> 3] |= (1 << (index & 7));
        }
        else
            attributeState[index] = attr.defaultValue_;
        
        ++index;
    }
    
    msg.Write(&deltaUpdateBits_[0], deltaUpdateBits_.Size());
    
    index = 0;
    for (unsigned i = 0; i < attributes->Size(); ++i)
    {
        const AttributeInfo& attr = attributes->At(i);
        if (!(attr.mode_ & AM_NET))
            continue;
        
        if (deltaUpdateBits_[index << 3] & (1 << (index & 7)))
            msg.WriteVariantData(attributeState[index]);
        
        ++index;
    }
}
