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
#include "Context.h"
#include "Log.h"
#include "MemoryBuffer.h"
#include "Scene.h"
#include "VectorBuffer.h"
#include "XMLElement.h"

#include "DebugNew.h"

// Normalize rotation quaternion after this many incremental updates to prevent distortion
static const int NORMALIZE_ROTATION_EVERY = 32;

OBJECTTYPESTATIC(Node);

Node::Node(Context* context) :
    Serializable(context),
    id_(0),
    parent_(0),
    scene_(0),
    owner_(0),
    position_(Vector3::ZERO),
    rotation_(Quaternion::IDENTITY),
    scale_(Vector3::UNITY),
    worldTransform_(Matrix3x4::IDENTITY),
    rotateCount_(0),
    dirty_(false)
{
}

Node::~Node()
{
    RemoveAllChildren();
    RemoveAllComponents();
    
    // Remove from the scene
    if (scene_)
        scene_->NodeRemoved(this);
}

void Node::RegisterObject(Context* context)
{
    context->RegisterFactory<Node>();
    
    REF_ACCESSOR_ATTRIBUTE(Node, VAR_STRING, "Name", GetName, SetName, String, String(), AM_DEFAULT);
    REF_ACCESSOR_ATTRIBUTE(Node, VAR_VECTOR3, "Position", GetPosition, SetPosition, Vector3, Vector3::ZERO, AM_DEFAULT | AM_LATESTDATA);
    REF_ACCESSOR_ATTRIBUTE(Node, VAR_QUATERNION, "Rotation", GetRotation, SetRotation, Quaternion, Quaternion::IDENTITY, AM_DEFAULT | AM_LATESTDATA);
    REF_ACCESSOR_ATTRIBUTE(Node, VAR_VECTOR3, "Scale", GetScale, SetScale, Vector3, Vector3::UNITY, AM_DEFAULT);
    ACCESSOR_ATTRIBUTE(Node, VAR_BUFFER, "Parent Node", GetParentAttr, SetParentAttr, PODVector<unsigned char>, PODVector<unsigned char>(), AM_NET | AM_NOEDIT);
    ATTRIBUTE(Node, VAR_VARIANTMAP, "Variables", vars_, VariantMap(), AM_FILE);
}

void Node::OnEvent(Object* sender, bool broadcast, StringHash eventType, VariantMap& eventData)
{
    // Make a weak pointer to self to check for destruction during event handling
    WeakPtr<Node> self(this);
    
    // If this is a targeted event, forward it to all components
    if (!broadcast)
    {
        for (unsigned i = components_.Size() - 1; i < components_.Size(); --i)
        {
            components_[i]->OnEvent(sender, broadcast, eventType, eventData);
            if (self.Expired())
                return;
        }
    }
    else
        Object::OnEvent(sender, broadcast, eventType, eventData);
}

bool Node::Load(Deserializer& source)
{
    return Load(source, true);
}

bool Node::Save(Serializer& dest)
{
    if (!Serializable::Save(dest))
        return false;
    
    dest.WriteVLE(components_.Size());
    for (unsigned i = 0; i < components_.Size(); ++i)
    {
        Component* component = components_[i];
        // Create a separate buffer to be able to skip unknown components during deserialization
        VectorBuffer compBuffer;
        compBuffer.WriteShortStringHash(component->GetType());
        compBuffer.WriteUInt(component->GetID());
        if (!component->Save(compBuffer))
            return false;
        dest.WriteVLE(compBuffer.GetSize());
        dest.Write(compBuffer.GetData(), compBuffer.GetSize());
    }
    
    dest.WriteVLE(children_.Size());
    for (unsigned i = 0; i < children_.Size(); ++i)
    {
        Node* node = children_[i];
        dest.WriteUInt(node->GetID());
        if (!node->Save(dest))
            return false;
    }
    
    return true;
}

bool Node::LoadXML(const XMLElement& source)
{
    return LoadXML(source, true);
}

bool Node::SaveXML(XMLElement& dest)
{
    if (!Serializable::SaveXML(dest))
        return false;
    
    for (unsigned i = 0; i < components_.Size(); ++i)
    {
        Component* component = components_[i];
        XMLElement compElem = dest.CreateChild("component");
        
        compElem.SetString("type", component->GetTypeName());
        compElem.SetInt("id", component->GetID());
        if (!component->SaveXML(compElem))
            return false;
    }
    
    for (unsigned i = 0; i < children_.Size(); ++i)
    {
        Node* node = children_[i];
        XMLElement childElem = dest.CreateChild("node");
        
        childElem.SetInt("id", node->GetID());
        if (!node->SaveXML(childElem))
            return false;
    }
    
    return true;
}

void Node::FinishUpdate()
{
    for (unsigned i = 0; i < components_.Size(); ++i)
        components_[i]->FinishUpdate();
    
    for (unsigned i = 0; i < children_.Size(); ++i)
        children_[i]->FinishUpdate();
}

void Node::SetName(const String& name)
{
    name_ = name;
    nameHash_ = StringHash(name);
}

void Node::SetPosition(const Vector3& position)
{
    position_ = position;
    if (!dirty_)
        MarkDirty();
}

void Node::SetRotation(const Quaternion& rotation)
{
    rotation_ = rotation;
    rotateCount_ = 0;
    if (!dirty_)
        MarkDirty();
}

void Node::SetDirection(const Vector3& direction)
{
    SetRotation(Quaternion(Vector3::FORWARD, direction));
}

void Node::SetScale(float scale)
{
    scale_ = Vector3(scale, scale, scale);
    if (!dirty_)
        MarkDirty();
}

void Node::SetScale(const Vector3& scale)
{
    scale_ = scale;
    if (!dirty_)
        MarkDirty();
}

void Node::SetTransform(const Vector3& position, const Quaternion& rotation)
{
    position_ = position;
    rotation_ = rotation;
    rotateCount_ = 0;
    if (!dirty_)
        MarkDirty();
}

void Node::SetTransform(const Vector3& position, const Quaternion& rotation, float scale)
{
    position_ = position;
    rotation_ = rotation;
    scale_ = Vector3(scale, scale, scale);
    rotateCount_ = 0;
    if (!dirty_)
        MarkDirty();
}

void Node::SetTransform(const Vector3& position, const Quaternion& rotation, const Vector3& scale)
{
    position_ = position;
    rotation_ = rotation;
    scale_ = scale;
    rotateCount_ = 0;
    if (!dirty_)
        MarkDirty();
}

void Node::Translate(const Vector3& delta)
{
    position_ += delta;
    if (!dirty_)
        MarkDirty();
}

void Node::TranslateRelative(const Vector3& delta)
{
    position_ += rotation_ * delta;
    if (!dirty_)
        MarkDirty();
}

void Node::Rotate(const Quaternion& delta, bool fixedAxis)
{
    if (!fixedAxis)
        rotation_ = rotation_ * delta;
    else
        rotation_ = delta * rotation_;
    
    ++rotateCount_;
    if (rotateCount_ >= NORMALIZE_ROTATION_EVERY)
    {
        rotation_.Normalize();
        rotateCount_ = 0;
    }
    
    if (!dirty_)
        MarkDirty();
}

void Node::Yaw(float angle, bool fixedAxis)
{
    Rotate(Quaternion(angle, Vector3::UP), fixedAxis);
}

void Node::Pitch(float angle, bool fixedAxis)
{
    Rotate(Quaternion(angle, Vector3::RIGHT), fixedAxis);
}

void Node::Roll(float angle, bool fixedAxis)
{
    Rotate(Quaternion(angle, Vector3::FORWARD), fixedAxis);
}

void Node::Scale(float scale)
{
    scale_ *= scale;
    if (!dirty_)
        MarkDirty();
}

void Node::Scale(const Vector3& scale)
{
    scale_ *= scale;
    if (!dirty_)
        MarkDirty();
}

void Node::MarkDirty()
{
    dirty_ = true;
    
    // Notify listener components first, then mark child nodes
    for (Vector<WeakPtr<Component> >::Iterator i = listeners_.Begin(); i != listeners_.End();)
    {
        if (*i)
        {
            (*i)->OnMarkedDirty(this);
            ++i;
        }
        // If listener has expired, erase from list
        else
            i = listeners_.Erase(i);
    }
    
    for (Vector<SharedPtr<Node> >::Iterator i = children_.Begin(); i != children_.End(); ++i)
        (*i)->MarkDirty();
}

Node* Node::CreateChild(const String& name, bool local)
{
    Node* newNode = CreateChild(0, local);
    newNode->SetName(name);
    return newNode;
}

void Node::AddChild(Node* node)
{
    // Check for illegal parent assignments, including attempt to reparent the scene
    if (!node || node == this || node->parent_ == this || parent_ == node || scene_ == node)
        return;
    
    // Add first, then remove from old parent, to ensure the node does not get deleted
    children_.Push(SharedPtr<Node>(node));
    
    if (node->parent_)
        node->parent_->RemoveChild(node);
    
    // Add to the scene if not added yet
    if (scene_ && !node->GetScene())
        scene_->NodeAdded(node);
    
    node->parent_ = this;
    node->MarkDirty();
}

void Node::RemoveChild(Node* node)
{
    if (!node)
        return;
    
    for (Vector<SharedPtr<Node> >::Iterator i = children_.Begin(); i != children_.End(); ++i)
    {
        if (i->RawPtr() == node)
        {
            RemoveChild(i);
            return;
        }
    }
}

void Node::RemoveAllChildren()
{
    while (children_.Size())
        RemoveChild(children_.End() - 1);
}

Component* Node::CreateComponent(ShortStringHash type, bool local)
{
    return CreateComponent(type, 0, local);
}

Component* Node::GetOrCreateComponent(ShortStringHash type, bool local)
{
    Component* oldComponent = GetComponent(type);
    if (oldComponent)
        return oldComponent;
    else
        return CreateComponent(type, 0, local);
}

void Node::RemoveComponent(Component* component)
{
    for (Vector<SharedPtr<Component> >::Iterator i = components_.Begin(); i != components_.End(); ++i)
    {
        if (*i == component)
        {
            WeakPtr<Component> componentWeak(*i);
            
            RemoveListener(*i);
            if (scene_)
                scene_->ComponentRemoved(*i);
            components_.Erase(i);
            
            // If the component is still referenced elsewhere, reset its node pointer now
            if (componentWeak)
                componentWeak->SetNode(0);
            return;
        }
    }
}

void Node::RemoveAllComponents()
{
    while (components_.Size())
    {
        Vector<SharedPtr<Component> >::Iterator i = components_.End() - 1;
        WeakPtr<Component> componentWeak(*i);
        
        RemoveListener(*i);
        if (scene_)
            scene_->ComponentRemoved(*i);
        components_.Erase(i);
        
        // If the component is still referenced elsewhere, reset its node pointer now
        if (componentWeak)
            componentWeak->SetNode(0);
    }
}

void Node::AddListener(Component* component)
{
    if (!component)
        return;
    
    // Check for not adding twice
    for (Vector<WeakPtr<Component> >::Iterator i = listeners_.Begin(); i != listeners_.End(); ++i)
    {
        if ((*i) == component)
            return;
    }
    
    listeners_.Push(WeakPtr<Component>(component));
    // If the node is currently dirty, notify immediately
    if (dirty_)
        component->OnMarkedDirty(this);
}

void Node::RemoveListener(Component* component)
{
    for (Vector<WeakPtr<Component> >::Iterator i = listeners_.Begin(); i != listeners_.End(); ++i)
    {
        if ((*i) == component)
        {
            listeners_.Erase(i);
            return;
        }
    }
}

void Node::Remove()
{
    if (parent_)
        parent_->RemoveChild(this);
}

void Node::SetParent(Node* parent)
{
    if (parent)
        parent->AddChild(this);
}

unsigned Node::GetNumChildren(bool recursive) const
{
    if (!recursive)
        return children_.Size();
    else
    {
        unsigned allChildren = children_.Size();
        for (Vector<SharedPtr<Node> >::ConstIterator i = children_.Begin(); i != children_.End(); ++i)
            allChildren += (*i)->GetNumChildren(true);
        
        return allChildren;
    }
}

void Node::GetChildren(PODVector<Node*>& dest, bool recursive) const
{
    dest.Clear();
    
    if (!recursive)
    {
        for (Vector<SharedPtr<Node> >::ConstIterator i = children_.Begin(); i != children_.End(); ++i)
            dest.Push(*i);
    }
    else
        GetChildrenRecursive(dest);
}

void Node::GetChildrenWithComponent(PODVector<Node*>& dest, ShortStringHash type, bool recursive) const
{
    dest.Clear();
    
    if (!recursive)
    {
        for (Vector<SharedPtr<Node> >::ConstIterator i = children_.Begin(); i != children_.End(); ++i)
        {
            if ((*i)->HasComponent(type))
                dest.Push(*i);
        }
    }
    else
        GetChildrenWithComponentRecursive(dest, type);
}

Node* Node::GetChild(unsigned index) const
{
    return index < children_.Size() ? children_[index].RawPtr() : 0;
}

Node* Node::GetChild(const String& name, bool recursive) const
{
    return GetChild(StringHash(name), recursive);
}

Node* Node::GetChild(StringHash nameHash, bool recursive) const
{
    for (Vector<SharedPtr<Node> >::ConstIterator i = children_.Begin(); i != children_.End(); ++i)
    {
        if ((*i)->GetNameHash() == nameHash)
            return *i;
        
        if (recursive)
        {
            Node* node = (*i)->GetChild(nameHash, true);
            if (node)
                return node;
        }
    }
    
    return 0;
}

unsigned Node::GetNumNetworkComponents() const
{
    unsigned num = 0;
    for (Vector<SharedPtr<Component> >::ConstIterator i = components_.Begin(); i != components_.End(); ++i)
    {
        if ((*i)->GetID() < FIRST_LOCAL_ID)
            ++num;
    }
    
    return num;
}

void Node::GetComponents(PODVector<Component*>& dest, ShortStringHash type) const
{
    dest.Clear();
    for (Vector<SharedPtr<Component> >::ConstIterator i = components_.Begin(); i != components_.End(); ++i)
    {
        if ((*i)->GetType() == type)
            dest.Push(*i);
    }
}

bool Node::HasComponent(ShortStringHash type) const
{
    for (Vector<SharedPtr<Component> >::ConstIterator i = components_.Begin(); i != components_.End(); ++i)
    {
        if ((*i)->GetType() == type)
            return true;
    }
    return false;
}

Component* Node::GetComponent(unsigned index) const
{
    return index < components_.Size() ? components_[index].RawPtr() : 0;
}

Component* Node::GetComponent(ShortStringHash type, unsigned index) const
{
    unsigned cmpIndex = 0;
    for (Vector<SharedPtr<Component> >::ConstIterator i = components_.Begin(); i != components_.End(); ++i)
    {
        if ((*i)->GetType() == type)
        {
            if (cmpIndex == index)
                return *i;
            ++cmpIndex;
        }
    }
    
    return 0;
}

void Node::GetDependencyNodes(PODVector<Node*>& dest) const
{
    // Add the parent node, but if it is local, traverse to the first non-local node
    if (parent_ && parent_ != scene_)
    {
        Node* current = parent_;
        while (current->id_ >= FIRST_LOCAL_ID)
            current = current->parent_;
        dest.Push(current);
    }
    
    // Then let the components add their dependencies
    for (Vector<SharedPtr<Component> >::ConstIterator i = components_.Begin(); i != components_.End(); ++i)
        (*i)->GetDependencyNodes(dest);
}

void Node::SetID(unsigned id)
{
    id_ = id;
}

void Node::SetScene(Scene* scene)
{
    scene_ = scene;
}

void Node::SetOwner(Connection* owner)
{
    owner_ = owner;
}

void Node::SetParentAttr(PODVector<unsigned char> value)
{
    Scene* scene = GetScene();
    if (!scene)
        return;
    
    MemoryBuffer buf(value);
    unsigned baseNodeID = buf.ReadVLE();
    if (!baseNodeID)
        return;
    
    if (baseNodeID < FIRST_LOCAL_ID)
        SetParent(scene->GetNodeByID(baseNodeID));
    else
    {
        Node* baseNode = scene->GetNodeByID(baseNodeID);
        if (baseNode)
            SetParent(baseNode->GetChild(buf.ReadStringHash(), true));
    }
}

PODVector<unsigned char> Node::GetParentAttr() const
{
    VectorBuffer buf;
    Scene* scene = GetScene();
    if (scene && parent_)
    {
        unsigned parentID = parent_->GetID();
        if (parentID < FIRST_LOCAL_ID)
            buf.WriteVLE(parentID);
        else
        {
            // Parent is local: traverse hierarchy to find a non-local base node
            // This iteration always stops due to the scene (root) being non-local
            Node* current = parent_;
            while (current->GetID() >= FIRST_LOCAL_ID)
                current = current->GetParent();
            
            buf.WriteVLE(current->GetID());
            buf.WriteStringHash(parent_->GetNameHash());
        }
    }
    else
        buf.WriteVLE(0);
    
    return buf.GetBuffer();
}

bool Node::Load(Deserializer& source, bool readChildren)
{
    // Remove all children and components first in case this is not a fresh load
    RemoveAllChildren();
    RemoveAllComponents();
    
    // ID has been read at the parent level
    if (!Serializable::Load(source))
        return false;
    
    unsigned numComponents = source.ReadVLE();
    for (unsigned i = 0; i < numComponents; ++i)
    {
        VectorBuffer compBuffer(source, source.ReadVLE());
        ShortStringHash newType = compBuffer.ReadShortStringHash();
        Component* newComponent = CreateComponent(newType, compBuffer.ReadUInt(), false);
        if (newComponent)
        {
            if (!newComponent->Load(compBuffer))
                return false;
        }
    }
    
    if (!readChildren)
        return true;
    
    unsigned numChildren = source.ReadVLE();
    for (unsigned i = 0; i < numChildren; ++i)
    {
        Node* newNode = CreateChild(source.ReadUInt(), false);
        if (!newNode->Load(source))
            return false;
    }
    
    return true;
}

bool Node::LoadXML(const XMLElement& source, bool readChildren)
{
    // Remove all children and components first in case this is not a fresh load
    RemoveAllChildren();
    RemoveAllComponents();
    
    if (!Serializable::LoadXML(source))
        return false;
    
    XMLElement compElem = source.GetChild("component");
    while (compElem)
    {
        String typeName = compElem.GetString("type");
        Component* newComponent = CreateComponent(ShortStringHash(compElem.GetString("type")), compElem.GetInt("id"), false);
        if (newComponent)
        {
            if (!newComponent->LoadXML(compElem))
                return false;
        }
        
        compElem = compElem.GetNext("component");
    }
    
    if (!readChildren)
        return true;
    
    XMLElement childElem = source.GetChild("node");
    while (childElem)
    {
        Node* newNode = CreateChild(childElem.GetInt("id"), false);
        if (!newNode->LoadXML(childElem))
            return false;
        
        childElem = childElem.GetNext("node");
    }
    
    return true;
}

Component* Node::CreateComponent(ShortStringHash type, unsigned id, bool local)
{
    // Make sure the object in question is a component
    SharedPtr<Component> newComponent = DynamicCast<Component>(context_->CreateObject(type));
    if (!newComponent)
    {
        LOGERROR("Could not create unknown component type " + type);
        return 0;
    }
    
    components_.Push(newComponent);
    
    // If zero ID specified, let the scene assign
    if (scene_)
    {
        newComponent->SetID(id ? id : scene_->GetFreeComponentID(local));
        scene_->ComponentAdded(newComponent);
    }
    else
        newComponent->SetID(id);
    
    newComponent->SetNode(this);
    newComponent->OnMarkedDirty(this);
    return newComponent;
}

Node* Node::CreateChild(unsigned id, bool local)
{
    SharedPtr<Node> newNode(new Node(context_));
    
    // If zero ID specified, let the scene assign
    if (scene_)
        newNode->SetID(id ? id : scene_->GetFreeNodeID(local));
    else
        newNode->SetID(id);
    
    AddChild(newNode);
    return newNode;
}

void Node::UpdateWorldTransform()
{
    // For now, assume that the Scene has identity transform so that we skip one matrix multiply. However in the future
    // we may want dynamic root nodes for large worlds
    if (parent_ && parent_ != scene_)
    {
        if (parent_->dirty_)
            parent_->UpdateWorldTransform();
        worldTransform_ = parent_->worldTransform_ * Matrix3x4(position_, rotation_, scale_);
    }
    else
        worldTransform_ = Matrix3x4(position_, rotation_, scale_);
    
    dirty_ = false;
}

void Node::RemoveChild(Vector<SharedPtr<Node> >::Iterator i)
{
    (*i)->parent_ = 0;
    (*i)->MarkDirty();
    children_.Erase(i);
}

void Node::GetChildrenRecursive(PODVector<Node*>& dest) const
{
    for (Vector<SharedPtr<Node> >::ConstIterator i = children_.Begin(); i != children_.End(); ++i)
    {
        Node* node = *i;
        dest.Push(node);
        if (!node->children_.Empty())
            node->GetChildrenRecursive(dest);
    }
}

void Node::GetChildrenWithComponentRecursive(PODVector<Node*>& dest, ShortStringHash type) const
{
    for (Vector<SharedPtr<Node> >::ConstIterator i = children_.Begin(); i != children_.End(); ++i)
    {
        Node* node = *i;
        if (node->HasComponent(type))
            dest.Push(node);
        if (!node->children_.Empty())
            node->GetChildrenRecursive(dest);
    }
}
