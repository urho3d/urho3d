//
// Urho3D Engine
// Copyright (c) 2008-2012 Lasse Öörni
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
#include "Node.h"
#include "ReplicationState.h"
#include "XMLElement.h"

#include "DebugNew.h"

OBJECTTYPESTATIC(Component);

Component::Component(Context* context) :
    Serializable(context),
    id_(0),
    node_(0)
{
}

Component::~Component()
{
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

const Matrix3x4& Component::GetWorldTransform() const
{
    return node_ ? node_->GetWorldTransform() : Matrix3x4::IDENTITY;
}

void Component::AddReplicationState(ComponentReplicationState* state)
{
    replicationStates_.Push(state);
}

void Component::PrepareNetworkUpdate()
{
    const Vector<AttributeInfo>* attributes = GetNetworkAttributes();
    if (!attributes)
        return;
    
    unsigned numAttributes = attributes->Size();
    
    if (currentState_.Size() != numAttributes)
    {
        currentState_.Resize(numAttributes);
        previousState_.Resize(numAttributes);
        
        // Copy the default attribute values to the previous state as a starting point
        for (unsigned i = 0; i < numAttributes; ++i)
            previousState_[i] = attributes->At(i).defaultValue_;
    }
    
    // Check for attribute changes
    for (unsigned i = 0; i < numAttributes; ++i)
    {
        const AttributeInfo& attr = attributes->At(i);
        OnGetAttribute(attr, currentState_[i]);
        
        if (currentState_[i] != previousState_[i])
        {
            previousState_[i] = currentState_[i];
            
            // Mark the attribute dirty in all replication states that are tracking this component
            for (PODVector<ComponentReplicationState*>::Iterator j = replicationStates_.Begin(); j != replicationStates_.End(); ++j)
            {
                (*j)->dirtyAttributes_.Set(i);
                
                // Add component's parent node to the dirty set if not added yet
                if (!(*j)->nodeState_->markedDirty_)
                {
                    (*j)->nodeState_->markedDirty_ = true;
                    (*j)->nodeState_->sceneState_->dirtyNodes_.Insert(node_->GetID());
                }
            }
        }
    }
}

void Component::CleanupConnection(Connection* connection)
{
    for (unsigned i = replicationStates_.Size() - 1; i < replicationStates_.Size(); --i)
    {
        if (replicationStates_[i]->connection_ == connection)
            replicationStates_.Erase(i);
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
