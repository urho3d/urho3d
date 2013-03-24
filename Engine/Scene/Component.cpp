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
#include "Component.h"
#include "Context.h"
#include "ReplicationState.h"
#include "Scene.h"
#include "SceneEvents.h"

#include "DebugNew.h"

namespace Urho3D
{

OBJECTTYPESTATIC(Component);

Component::Component(Context* context) :
    Serializable(context),
    node_(0),
    id_(0),
    networkUpdate_(false)
{
}

Component::~Component()
{
}

void Component::OnSetAttribute(const AttributeInfo& attr, const Variant& src)
{
    Serializable::OnSetAttribute(attr, src);
    MarkNetworkUpdate();
}

bool Component::Save(Serializer& dest)
{
    // Write type and ID
    if (!dest.WriteShortStringHash(GetType()))
        return false;
    if (!dest.WriteUInt(id_))
        return false;
    
    // Write attributes
    return Serializable::Save(dest);
}

bool Component::SaveXML(XMLElement& dest)
{
    // Write type and ID
    if (!dest.SetString("type", GetTypeName()))
        return false;
    if (!dest.SetInt("id", id_))
        return false;
    
    // Write attributes
    return Serializable::SaveXML(dest);
}

void Component::Remove()
{
    if (node_)
        node_->RemoveComponent(this);
}

Scene* Component::GetScene() const
{
    return node_ ? node_->GetScene() : 0;
}

void Component::AddReplicationState(ComponentReplicationState* state)
{
    if (!networkState_)
        AllocateNetworkState();
    
    networkState_->replicationStates_.Push(state);
}

void Component::PrepareNetworkUpdate()
{
    if (!networkState_)
        AllocateNetworkState();
    
    const Vector<AttributeInfo>* attributes = networkState_->attributes_;
    if (!attributes)
        return;
    
    unsigned numAttributes = attributes->Size();
    
    if (networkState_->currentValues_.Size() != numAttributes)
    {
        networkState_->currentValues_.Resize(numAttributes);
        networkState_->previousValues_.Resize(numAttributes);
        
        // Copy the default attribute values to the previous state as a starting point
        for (unsigned i = 0; i < numAttributes; ++i)
            networkState_->previousValues_[i] = attributes->At(i).defaultValue_;
    }
    
    // Check for attribute changes
    for (unsigned i = 0; i < numAttributes; ++i)
    {
        const AttributeInfo& attr = attributes->At(i);
        OnGetAttribute(attr, networkState_->currentValues_[i]);
        
        if (networkState_->currentValues_[i] != networkState_->previousValues_[i])
        {
            networkState_->previousValues_[i] = networkState_->currentValues_[i];
            
            // Mark the attribute dirty in all replication states that are tracking this component
            for (PODVector<ReplicationState*>::Iterator j = networkState_->replicationStates_.Begin(); j !=
                networkState_->replicationStates_.End(); ++j)
            {
                ComponentReplicationState* compState = static_cast<ComponentReplicationState*>(*j);
                compState->dirtyAttributes_.Set(i);
                
                // Add component's parent node to the dirty set if not added yet
                NodeReplicationState* nodeState = compState->nodeState_;
                if (!nodeState->markedDirty_)
                {
                    nodeState->markedDirty_ = true;
                    nodeState->sceneState_->dirtyNodes_.Insert(node_->GetID());
                }
            }
        }
    }
    
    networkUpdate_ = false;
}

void Component::CleanupConnection(Connection* connection)
{
    if (networkState_)
    {
        for (unsigned i = networkState_->replicationStates_.Size() - 1; i < networkState_->replicationStates_.Size(); --i)
        {
            if (networkState_->replicationStates_[i]->connection_ == connection)
                networkState_->replicationStates_.Erase(i);
        }
    }
}

void Component::MarkNetworkUpdate()
{
    if (!networkUpdate_ && id_ < FIRST_LOCAL_ID)
    {
        Scene* scene = GetScene();
        if (scene)
        {
            scene->MarkNetworkUpdate(this);
            networkUpdate_ = true;
        }
    }
}

void Component::SetID(unsigned id)
{
    id_ = id;
}

void Component::SetNode(Node* node)
{
    node_ = node;
    OnNodeSet(node_);
}

Component* Component::GetComponent(ShortStringHash type) const
{
    return node_ ? node_->GetComponent(type) : 0;
}

void Component::GetComponents(PODVector<Component*>& dest, ShortStringHash type) const
{
    if (node_)
        node_->GetComponents(dest, type);
    else
        dest.Clear();
}

}
