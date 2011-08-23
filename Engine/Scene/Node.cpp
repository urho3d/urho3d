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
    targetPosition_(Vector3::ZERO),
    targetRotation_(Quaternion::IDENTITY),
    rotateCount_(0),
    smoothingMask_(SMOOTH_NONE),
    dirty_(false),
    smoothed_(false)
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
    REF_ACCESSOR_ATTRIBUTE(Node, VAR_QUATERNION, "Rotation", GetRotation, SetRotation, Quaternion, Quaternion::IDENTITY, AM_FILE);
    REF_ACCESSOR_ATTRIBUTE(Node, VAR_VECTOR3, "Scale", GetScale, SetScale, Vector3, Vector3::UNITY, AM_DEFAULT);
    ATTRIBUTE(Node, VAR_VARIANTMAP, "Variables", vars_, VariantMap(), AM_FILE); // Network replication of vars uses custom data
    REF_ACCESSOR_ATTRIBUTE(Node, VAR_BUFFER, "Network Rotation", GetNetRotationAttr, SetNetRotationAttr, PODVector<unsigned char>, PODVector<unsigned char>(), AM_NET | AM_LATESTDATA | AM_NOEDIT);
    REF_ACCESSOR_ATTRIBUTE(Node, VAR_BUFFER, "Network Parent Node", GetNetParentAttr, SetNetParentAttr, PODVector<unsigned char>, PODVector<unsigned char>(), AM_NET | AM_NOEDIT);
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

void Node::ApplyAttributes()
{
    for (unsigned i = 0; i < components_.Size(); ++i)
        components_[i]->ApplyAttributes();
    
    for (unsigned i = 0; i < children_.Size(); ++i)
        children_[i]->ApplyAttributes();
}

void Node::SetName(const String& name)
{
    name_ = name;
    nameHash_ = StringHash(name);
}

void Node::SetPosition(const Vector3& position)
{
    if (!smoothed_)
    {
        position_ = position;
        if (!dirty_)
            MarkDirty();
    }
    else
    {
        targetPosition_ = position;
        smoothingMask_ |= SMOOTH_POSITION;
    }
}

void Node::SetRotation(const Quaternion& rotation)
{
    if (!smoothed_)
    {
        rotation_ = rotation;
        if (!dirty_)
            MarkDirty();
    }
    else
    {
        targetRotation_ = rotation;
        smoothingMask_ |= SMOOTH_ROTATION;
    }
    rotateCount_ = 0;
}

void Node::SetDirection(const Vector3& direction)
{
    SetRotation(Quaternion(Vector3::FORWARD, direction));
}

void Node::SetScale(float scale)
{
    scale_ = Vector3(scale, scale, scale).Abs();
    if (!dirty_)
        MarkDirty();
}

void Node::SetScale(const Vector3& scale)
{
    scale_ = scale.Abs();
    if (!dirty_)
        MarkDirty();
}

void Node::SetTransform(const Vector3& position, const Quaternion& rotation)
{
    if (!smoothed_)
    {
        position_ = position;
        rotation_ = rotation;
        if (!dirty_)
            MarkDirty();
    }
    else
    {
        targetPosition_ = position;
        targetRotation_ = rotation;
        smoothingMask_ |= SMOOTH_POSITION | SMOOTH_ROTATION;
    }
    rotateCount_ = 0;
}

void Node::SetTransform(const Vector3& position, const Quaternion& rotation, float scale)
{
    if (!smoothed_)
    {
        position_ = position;
        rotation_ = rotation;
    }
    else
    {
        targetPosition_ = position;
        targetRotation_ = rotation;
        smoothingMask_ |= SMOOTH_POSITION | SMOOTH_ROTATION;
    }
    rotateCount_ = 0;
    scale_ = Vector3(scale, scale, scale);
    if (!dirty_)
        MarkDirty();
}

void Node::SetTransform(const Vector3& position, const Quaternion& rotation, const Vector3& scale)
{
    if (!smoothed_)
    {
        position_ = position;
        rotation_ = rotation;
    }
    else
    {
        targetPosition_ = position;
        targetRotation_ = rotation;
        smoothingMask_ |= SMOOTH_POSITION | SMOOTH_ROTATION;
    }
    rotateCount_ = 0;
    scale_ = scale;
    if (!dirty_)
        MarkDirty();
}

void Node::SnapPosition(const Vector3& position)
{
    position_ = position;
    targetPosition_ = position;
    smoothingMask_ &= ~SMOOTH_POSITION;
    if (!dirty_)
        MarkDirty();
}

void Node::SnapRotation(const Quaternion& rotation)
{
    rotation_ = rotation;
    targetRotation_ = rotation;
    smoothingMask_ &= ~SMOOTH_ROTATION;
    rotateCount_ = 0;
    if (!dirty_)
        MarkDirty();
}

void Node::Translate(const Vector3& delta)
{
    if (!smoothed_)
    {
        position_ += delta;
        if (!dirty_)
            MarkDirty();
    }
    else
    {
        targetPosition_ += delta;
        smoothingMask_ |= SMOOTH_POSITION;
    }
}

void Node::TranslateRelative(const Vector3& delta)
{
    if (!smoothed_)
    {
        position_ += rotation_ * delta;
        if (!dirty_)
            MarkDirty();
    }
    else
    {
        targetPosition_ += targetRotation_ * delta;
        smoothingMask_ |= SMOOTH_POSITION;
    }
}

void Node::Rotate(const Quaternion& delta, bool fixedAxis)
{
    if (!smoothed_)
    {
        if (!fixedAxis)
            rotation_ = rotation_ * delta;
        else
            rotation_ = delta * rotation_;
    }
    else
    {
        if (!fixedAxis)
            targetRotation_ = targetRotation_ * delta;
        else
            targetRotation_ = delta * targetRotation_;
        smoothingMask_ |= SMOOTH_ROTATION;
    }
    
    ++rotateCount_;
    if (rotateCount_ >= NORMALIZE_ROTATION_EVERY)
    {
        if (!smoothed_)
            rotation_.Normalize();
        else
            targetRotation_.Normalize();
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

void Node::SetOwner(Connection* owner)
{
    owner_ = owner;
}

void Node::SetSmoothed(bool enable)
{
    smoothed_ = enable;
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

Node* Node::CreateChild(const String& name, CreateMode mode)
{
    Node* newNode = CreateChild(0, mode);
    newNode->SetName(name);
    return newNode;
}

void Node::AddChild(Node* node)
{
    // Check for illegal or redundant parent assignment
    if (!node || node == this || node->parent_ == this)
        return;
    // Check for possible cyclic parent assignment
    Node* parent = parent_;
    while (parent)
    {
        if (parent == node)
            return;
        parent = parent->parent_;
    }
    
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
        if (*i == node)
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

Component* Node::CreateComponent(ShortStringHash type, CreateMode mode)
{
    return CreateComponent(type, 0, mode);
}

Component* Node::GetOrCreateComponent(ShortStringHash type, CreateMode mode)
{
    Component* oldComponent = GetComponent(type);
    if (oldComponent)
        return oldComponent;
    else
        return CreateComponent(type, 0, mode);
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
        if (*i == component)
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
        if (*i == component)
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

Matrix3x4 Node::GetWorldTargetTransform() const
{
    if (!smoothed_)
        return GetWorldTransform();
    
    Matrix3x4 ret(targetPosition_, targetRotation_, scale_);
    Node* current = parent_;
    while (current)
    {
        ret = Matrix3x4(current->targetPosition_, current->targetRotation_, current->scale_) * ret;
        current = current->parent_;
    }
    
    return ret;
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
    return index < children_.Size() ? children_[index].Get() : 0;
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

Component* Node::GetComponent(ShortStringHash type) const
{
    for (Vector<SharedPtr<Component> >::ConstIterator i = components_.Begin(); i != components_.End(); ++i)
    {
        if ((*i)->GetType() == type)
            return *i;
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

void Node::SetNetRotationAttr(const PODVector<unsigned char>& value)
{
    MemoryBuffer buf(value);
    SetRotation(buf.ReadPackedQuaternion());
}

void Node::SetNetParentAttr(const PODVector<unsigned char>& value)
{
    Scene* scene = GetScene();
    if (!scene)
        return;
    
    MemoryBuffer buf(value);
    // If nothing in the buffer, parent is the root node
    if (buf.IsEof())
    {
        SetParent(scene);
        return;
    }
    
    unsigned baseNodeID = buf.ReadNetID();
    Node* baseNode = scene->GetNode(baseNodeID);
    if (!baseNode)
    {
        LOGWARNING("Failed to find parent node " + String(baseNodeID));
        return;
    }
    
    // If buffer contains just an ID, the parent is replicated and we are done
    if (buf.IsEof())
        SetParent(baseNode);
    else
    {
        // Else the parent is local and we must find it recursively by name hash
        StringHash nameHash = buf.ReadStringHash();
        Node* parentNode = baseNode->GetChild(nameHash, true);
        if (!parentNode)
            LOGWARNING("Failed to find parent node with name hash " + nameHash.ToString());
        else
            SetParent(parentNode);
    }
}

const PODVector<unsigned char>& Node::GetNetRotationAttr() const
{
    attrBuffer_.Clear();
    attrBuffer_.WritePackedQuaternion(rotation_);
    return attrBuffer_.GetBuffer();
}

const PODVector<unsigned char>& Node::GetNetParentAttr() const
{
    attrBuffer_.Clear();
    Scene* scene = GetScene();
    if (scene && parent_ && parent_ != scene)
    {
        // If parent is replicated, can write the ID directly
        unsigned parentID = parent_->GetID();
        if (parentID < FIRST_LOCAL_ID)
            attrBuffer_.WriteNetID(parentID);
        else
        {
            // Parent is local: traverse hierarchy to find a non-local base node
            // This iteration always stops due to the scene (root) being non-local
            Node* current = parent_;
            while (current->GetID() >= FIRST_LOCAL_ID)
                current = current->GetParent();
            
            // Then write the base node ID and the parent's name hash
            attrBuffer_.WriteVLE(current->GetID());
            attrBuffer_.WriteStringHash(parent_->GetNameHash());
        }
    }
    
    return attrBuffer_.GetBuffer();
}

void Node::UpdateSmoothing(float constant, float squaredSnapThreshold)
{
    if (!smoothed_ || !smoothingMask_)
        return;
    
    if (smoothingMask_ & SMOOTH_POSITION)
    {
        // If position snaps, snap everything to the end
        float delta = (position_ - targetPosition_).LengthSquared();
        if (delta > squaredSnapThreshold)
            constant = 1.0f;
        
        if (delta < M_EPSILON || constant >= 1.0f)
        {
            position_ = targetPosition_;
            smoothingMask_ &= ~SMOOTH_POSITION;
        }
        else
            position_ = position_.Lerp(targetPosition_, constant);
    }
    if (smoothingMask_ & SMOOTH_ROTATION)
    {
        float delta = (rotation_ - targetRotation_).LengthSquared();
        if (delta < M_EPSILON || constant >= 1.0f)
        {
            rotation_ = targetRotation_;
            smoothingMask_ &= ~SMOOTH_ROTATION;
        }
        else
            rotation_ = rotation_.Slerp(targetRotation_, constant);
    }
    
    if (!dirty_)
        MarkDirty();
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
        Component* newComponent = CreateComponent(newType, compBuffer.ReadUInt(), REPLICATED);
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
        Node* newNode = CreateChild(source.ReadUInt(), REPLICATED);
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
        Component* newComponent = CreateComponent(ShortStringHash(compElem.GetString("type")), compElem.GetInt("id"), REPLICATED);
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
        Node* newNode = CreateChild(childElem.GetInt("id"), REPLICATED);
        if (!newNode->LoadXML(childElem))
            return false;
        
        childElem = childElem.GetNext("node");
    }
    
    return true;
}

Component* Node::CreateComponent(ShortStringHash type, unsigned id, CreateMode mode)
{
    // Check that creation succeeds and that the object in fact is a component
    SharedPtr<Component> newComponent = DynamicCast<Component>(context_->CreateObject(type));
    if (!newComponent)
    {
        LOGERROR("Could not create unknown component type " + type.ToString());
        return 0;
    }
    
    components_.Push(newComponent);
    
    // If zero ID specified, let the scene assign
    if (scene_)
    {
        newComponent->SetID(id ? id : scene_->GetFreeComponentID(mode));
        scene_->ComponentAdded(newComponent);
    }
    else
        newComponent->SetID(id);
    
    newComponent->SetNode(this);
    newComponent->OnMarkedDirty(this);
    return newComponent;
}

Node* Node::CreateChild(unsigned id, CreateMode mode)
{
    SharedPtr<Node> newNode(new Node(context_));
    
    // If zero ID specified, let the scene assign
    if (scene_)
        newNode->SetID(id ? id : scene_->GetFreeNodeID(mode));
    else
        newNode->SetID(id);
    
    AddChild(newNode);
    return newNode;
}

void Node::UpdateWorldTransform() const
{
    if (parent_)
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
