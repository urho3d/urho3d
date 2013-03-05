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
#include "Log.h"
#include "MemoryBuffer.h"
#include "Profiler.h"
#include "ReplicationState.h"
#include "Scene.h"
#include "SmoothedTransform.h"
#include "XMLFile.h"

#include "DebugNew.h"

namespace Urho3D
{

// Normalize rotation quaternion after this many incremental updates to prevent distortion
static const int NORMALIZE_ROTATION_EVERY = 32;

OBJECTTYPESTATIC(Node);

Node::Node(Context* context) :
    Serializable(context),
    worldTransform_(Matrix3x4::IDENTITY),
    dirty_(false),
    networkUpdate_(false),
    rotateCount_(0),
    parent_(0),
    scene_(0),
    id_(0),
    position_(Vector3::ZERO),
    rotation_(Quaternion::IDENTITY),
    scale_(Vector3::ONE),
    owner_(0)
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
    
    /// \todo When position/rotation updates are received from the network, route to SmoothedTransform if exists
    REF_ACCESSOR_ATTRIBUTE(Node, VAR_STRING, "Name", GetName, SetName, String, String::EMPTY, AM_DEFAULT);
    REF_ACCESSOR_ATTRIBUTE(Node, VAR_VECTOR3, "Position", GetPosition, SetPosition, Vector3, Vector3::ZERO, AM_FILE);
    REF_ACCESSOR_ATTRIBUTE(Node, VAR_QUATERNION, "Rotation", GetRotation, SetRotation, Quaternion, Quaternion::IDENTITY, AM_FILE);
    REF_ACCESSOR_ATTRIBUTE(Node, VAR_VECTOR3, "Scale", GetScale, SetScale, Vector3, Vector3::ONE, AM_DEFAULT);
    ATTRIBUTE(Node, VAR_VARIANTMAP, "Variables", vars_, Variant::emptyVariantMap, AM_FILE); // Network replication of vars uses custom data
    REF_ACCESSOR_ATTRIBUTE(Node, VAR_VECTOR3, "Network Position", GetNetPositionAttr, SetNetPositionAttr, Vector3, Vector3::ZERO, AM_NET | AM_LATESTDATA | AM_NOEDIT);
    REF_ACCESSOR_ATTRIBUTE(Node, VAR_BUFFER, "Network Rotation", GetNetRotationAttr, SetNetRotationAttr, PODVector<unsigned char>, Variant::emptyBuffer, AM_NET | AM_LATESTDATA | AM_NOEDIT);
    REF_ACCESSOR_ATTRIBUTE(Node, VAR_BUFFER, "Network Parent Node", GetNetParentAttr, SetNetParentAttr, PODVector<unsigned char>, Variant::emptyBuffer, AM_NET | AM_NOEDIT);
}

void Node::OnSetAttribute(const AttributeInfo& attr, const Variant& src)
{
    Serializable::OnSetAttribute(attr, src);
    MarkNetworkUpdate();
}

bool Node::Load(Deserializer& source)
{
    SceneResolver resolver;
    
    // Read own ID. Will not be applied, only stored for resolving possible references
    unsigned nodeID = source.ReadInt();
    resolver.AddNode(nodeID, this);
    
    // Read attributes, components and child nodes
    bool success = Load(source, resolver);
    if (success)
    {
        resolver.Resolve();
        ApplyAttributes();
    }
    
    return success;
}

bool Node::Save(Serializer& dest)
{
    // Write node ID
    if (!dest.WriteUInt(id_))
        return false;
    
    // Write attributes
    if (!Serializable::Save(dest))
        return false;
    
    // Write components
    dest.WriteVLE(components_.Size());
    for (unsigned i = 0; i < components_.Size(); ++i)
    {
        Component* component = components_[i];
        // Create a separate buffer to be able to skip unknown components during deserialization
        VectorBuffer compBuffer;
        if (!component->Save(compBuffer))
            return false;
        dest.WriteVLE(compBuffer.GetSize());
        dest.Write(compBuffer.GetData(), compBuffer.GetSize());
    }
    
    // Write child nodes
    dest.WriteVLE(children_.Size());
    for (unsigned i = 0; i < children_.Size(); ++i)
    {
        Node* node = children_[i];
        if (!node->Save(dest))
            return false;
    }
    
    return true;
}

bool Node::LoadXML(const XMLElement& source)
{
    SceneResolver resolver;
    
    // Read own ID. Will not be applied, only stored for resolving possible references
    unsigned nodeID = source.GetInt("id");
    resolver.AddNode(nodeID, this);
    
    // Read attributes, components and child nodes
    bool success = LoadXML(source, resolver);
    if (success)
    {
        resolver.Resolve();
        ApplyAttributes();
    }
    
    return success;
}

bool Node::SaveXML(XMLElement& dest)
{
    // Write node ID
    if (!dest.SetInt("id", id_))
        return false;
    
    // Write attributes
    if (!Serializable::SaveXML(dest))
        return false;
    
    // Write components
    for (unsigned i = 0; i < components_.Size(); ++i)
    {
        Component* component = components_[i];
        XMLElement compElem = dest.CreateChild("component");
        if (!component->SaveXML(compElem))
            return false;
    }
    
    // Write child nodes
    for (unsigned i = 0; i < children_.Size(); ++i)
    {
        Node* node = children_[i];
        XMLElement childElem = dest.CreateChild("node");
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

void Node::AddReplicationState(NodeReplicationState* state)
{
    if (!networkState_)
        AllocateNetworkState();
    
    networkState_->replicationStates_.Push(state);
}

bool Node::SaveXML(Serializer& dest)
{
    SharedPtr<XMLFile> xml(new XMLFile(context_));
    XMLElement rootElem = xml->CreateRoot("node");
    if (!SaveXML(rootElem))
        return false;
    
    return xml->Save(dest);
}

void Node::SetName(const String& name)
{
    name_ = name;
    nameHash_ = StringHash(name);
    
    MarkNetworkUpdate();
}

void Node::SetPosition(const Vector3& position)
{
    position_ = position;
    MarkDirty();
    
    MarkNetworkUpdate();
}

void Node::SetRotation(const Quaternion& rotation)
{
    rotation_ = rotation;
    rotateCount_ = 0;
    MarkDirty();
    
    MarkNetworkUpdate();
}

void Node::SetDirection(const Vector3& direction)
{
    SetRotation(Quaternion(Vector3::FORWARD, direction));
}

void Node::SetScale(float scale)
{
    SetScale(Vector3(scale, scale, scale));
}

void Node::SetScale(const Vector3& scale)
{
    scale_ = scale.Abs();
    MarkDirty();
    
    MarkNetworkUpdate();
}

void Node::SetTransform(const Vector3& position, const Quaternion& rotation)
{
    position_ = position;
    rotation_ = rotation;
    rotateCount_ = 0;
    MarkDirty();
    
    MarkNetworkUpdate();
}

void Node::SetTransform(const Vector3& position, const Quaternion& rotation, float scale)
{
    SetTransform(position, rotation, Vector3(scale, scale, scale));
}

void Node::SetTransform(const Vector3& position, const Quaternion& rotation, const Vector3& scale)
{
    position_ = position;
    rotation_ = rotation;
    rotateCount_ = 0;
    scale_ = scale;
    MarkDirty();
    
    MarkNetworkUpdate();
}

void Node::SetWorldPosition(const Vector3& position)
{
    if (!parent_)
        SetPosition(position);
    else
        SetPosition(parent_->GetWorldTransform().Inverse() * position);
}

void Node::SetWorldRotation(const Quaternion& rotation)
{
    if (!parent_)
        SetRotation(rotation);
    else
        SetRotation(parent_->GetWorldRotation().Inverse() * rotation);
}

void Node::SetWorldDirection(const Vector3& direction)
{
    Vector3 localDirection;
    if (!parent_)
        localDirection = direction;
    else
        localDirection = parent_->GetWorldTransform().Inverse() * direction;
    
    SetRotation(Quaternion(Vector3::FORWARD, localDirection));
}

void Node::SetWorldScale(float scale)
{
    if (!parent_)
        SetScale(scale);
    else
    {
        Vector3 parentWorldScale = parent_->GetWorldScale();
        SetScale(Vector3(scale / parentWorldScale.x_, scale / parentWorldScale.y_, scale / parentWorldScale.z_));
    }
}

void Node::SetWorldScale(const Vector3& scale)
{
    if (!parent_)
        SetScale(scale);
    else
        SetScale(scale / parent_->GetWorldScale());
}

void Node::SetWorldTransform(const Vector3& position, const Quaternion& rotation)
{
    SetWorldPosition(position);
    SetWorldRotation(rotation);
}

void Node::SetWorldTransform(const Vector3& position, const Quaternion& rotation, float scale)
{
    SetWorldPosition(position);
    SetWorldRotation(rotation);
    SetWorldScale(scale);
}

void Node::SetWorldTransform(const Vector3& position, const Quaternion& rotation, const Vector3& scale)
{
    SetWorldPosition(position);
    SetWorldRotation(rotation);
    SetWorldScale(scale);
}

void Node::Translate(const Vector3& delta)
{
    position_ += delta;
    MarkDirty();
    
    MarkNetworkUpdate();
}

void Node::TranslateRelative(const Vector3& delta)
{
    position_ += rotation_ * delta;
    MarkDirty();
    
    MarkNetworkUpdate();
}

void Node::Rotate(const Quaternion& delta, bool fixedAxis)
{
    if (!fixedAxis)
        rotation_ = rotation_ * delta;
    else
        rotation_ = delta * rotation_;
    
    if (++rotateCount_ >= NORMALIZE_ROTATION_EVERY)
    {
        rotation_.Normalize();
        rotateCount_ = 0;
    }
    
    MarkDirty();
    
    MarkNetworkUpdate();
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

void Node::LookAt(const Vector3& target, const Vector3& upAxis, bool worldSpace)
{
    Vector3 targetZ;
    if (worldSpace)
        targetZ = (target - GetWorldPosition()).Normalized();
    else
        targetZ = (target - position_).Normalized();
    
    Vector3 targetX = upAxis.CrossProduct(targetZ).Normalized();
    Vector3 targetY = targetZ.CrossProduct(targetX).Normalized();
    
    if (!worldSpace || !parent_)
        SetRotation(Quaternion(targetX, targetY, targetZ));
    else
        SetRotation(parent_->GetWorldRotation().Inverse() * Quaternion(targetX, targetY, targetZ));
}

void Node::Scale(float scale)
{
    Scale(Vector3(scale, scale, scale));
}

void Node::Scale(const Vector3& scale)
{
    scale_ *= scale;
    MarkDirty();
    
    MarkNetworkUpdate();
}

void Node::SetOwner(Connection* owner)
{
    owner_ = owner;
}

void Node::MarkDirty()
{
    if (dirty_)
        return;

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
    node->Remove();
    
    // Add to the scene if not added yet
    if (scene_ && !node->GetScene())
        scene_->NodeAdded(node);
    
    node->parent_ = this;
    node->MarkDirty();
    node->MarkNetworkUpdate();
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
        RemoveChild(--children_.End());
}

Component* Node::CreateComponent(ShortStringHash type, CreateMode mode, unsigned id)
{
    // Check that creation succeeds and that the object in fact is a component
    SharedPtr<Component> newComponent = DynamicCast<Component>(context_->CreateObject(type));
    if (!newComponent)
    {
        LOGERROR("Could not create unknown component type " + type.ToString());
        return 0;
    }
    
    AddComponent(newComponent, id, mode);
    return newComponent;
}

Component* Node::GetOrCreateComponent(ShortStringHash type, CreateMode mode)
{
    Component* oldComponent = GetComponent(type);
    if (oldComponent)
        return oldComponent;
    else
        return CreateComponent(type, mode);
}

void Node::RemoveComponent(Component* component)
{
    for (Vector<SharedPtr<Component> >::Iterator i = components_.Begin(); i != components_.End(); ++i)
    {
        if (*i == component)
        {
            RemoveComponent(i);
            
            // Mark node dirty in all replication states
            MarkReplicationDirty();
            return;
        }
    }
}

void Node::RemoveComponent(ShortStringHash type)
{
    for (Vector<SharedPtr<Component> >::Iterator i = components_.Begin(); i != components_.End(); ++i)
    {
        if ((*i)->GetType() == type)
        {
            RemoveComponent(i);
            
            // Mark node dirty in all replication states
            MarkReplicationDirty();
            return;
        }
    }
}

void Node::RemoveAllComponents()
{
    if (components_.Empty())
        return;
    
    while (components_.Size())
        RemoveComponent(--components_.End());
    
    // Mark node dirty in all replication states
    MarkReplicationDirty();
}

Node* Node::Clone(CreateMode mode)
{
    // The scene itself can not be cloned
    if (this == scene_ || !parent_)
    {
        LOGERROR("Can not clone node without a parent");
        return 0;
    }
    
    PROFILE(CloneNode);
    
    SceneResolver resolver;
    Node* clone = CloneRecursive(parent_, resolver, mode);
    resolver.Resolve();
    clone->ApplyAttributes();
    return clone;
}

void Node::Remove()
{
    if (parent_)
        parent_->RemoveChild(this);
}

void Node::SetParent(Node* parent)
{
    if (parent)
    {
        Vector3 worldPosition;
        Quaternion worldRotation;
        Vector3 worldScale;
        GetWorldTransform().Decompose(worldPosition, worldRotation, worldScale);
        
        parent->AddChild(this);
        SetWorldTransform(worldPosition, worldRotation, worldScale);
    }
}

void Node::SetVar(ShortStringHash key, const Variant& value)
{
    vars_[key] = value;
    MarkNetworkUpdate();
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

Vector3 Node::LocalToWorld(const Vector3& position) const
{
    return GetWorldTransform() * position;
}

Vector3 Node::LocalToWorld(const Vector4& vector) const
{
    return GetWorldTransform() * vector;
}

Vector3 Node::WorldToLocal(const Vector3& position) const
{
    return GetWorldTransform().Inverse() * position;
}

Vector3 Node::WorldToLocal(const Vector4& vector) const
{
    return GetWorldTransform().Inverse() * vector;
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

const Variant& Node::GetVar(ShortStringHash key) const
{
    VariantMap::ConstIterator i = vars_.Find(key);
    if (i != vars_.End())
        return i->second_;
    else
        return Variant::EMPTY;
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

void Node::SetID(unsigned id)
{
    id_ = id;
}

void Node::SetScene(Scene* scene)
{
    scene_ = scene;
}

void Node::ResetScene()
{
    SetID(0);
    SetScene(0);
    SetOwner(0);
}

void Node::SetNetPositionAttr(const Vector3& value)
{
    SmoothedTransform* transform = GetComponent<SmoothedTransform>();
    if (transform)
        transform->SetTargetPosition(value);
    else
        SetPosition(value);
}

void Node::SetNetRotationAttr(const PODVector<unsigned char>& value)
{
    MemoryBuffer buf(value);
    SmoothedTransform* transform = GetComponent<SmoothedTransform>();
    if (transform)
        transform->SetTargetRotation(buf.ReadPackedQuaternion());
    else
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
        scene->AddChild(this);
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
        baseNode->AddChild(this);
    else
    {
        // Else the parent is local and we must find it recursively by name hash
        StringHash nameHash = buf.ReadStringHash();
        Node* parentNode = baseNode->GetChild(nameHash, true);
        if (!parentNode)
            LOGWARNING("Failed to find parent node with name hash " + nameHash.ToString());
        else
            parentNode->AddChild(this);
    }
}

const Vector3& Node::GetNetPositionAttr() const
{
    return position_;
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
            attrBuffer_.WriteNetID(current->GetID());
            attrBuffer_.WriteStringHash(parent_->GetNameHash());
        }
    }
    
    return attrBuffer_.GetBuffer();
}

bool Node::Load(Deserializer& source, SceneResolver& resolver, bool readChildren, bool rewriteIDs, CreateMode mode)
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
        ShortStringHash compType = compBuffer.ReadShortStringHash();
        unsigned compID = compBuffer.ReadUInt();
        Component* newComponent = CreateComponent(compType,
            (mode == REPLICATED && compID < FIRST_LOCAL_ID) ? REPLICATED : LOCAL, rewriteIDs ? 0 : compID);
        if (newComponent)
        {
            resolver.AddComponent(compID, newComponent);
            if (!newComponent->Load(compBuffer))
                return false;
        }
    }
    
    if (!readChildren)
        return true;
    
    unsigned numChildren = source.ReadVLE();
    for (unsigned i = 0; i < numChildren; ++i)
    {
        unsigned nodeID = source.ReadUInt();
        Node* newNode = CreateChild(rewriteIDs ? 0 : nodeID, (mode == REPLICATED && nodeID < FIRST_LOCAL_ID) ? REPLICATED :
            LOCAL);
        resolver.AddNode(nodeID, newNode);
        if (!newNode->Load(source, resolver, readChildren, rewriteIDs, mode))
            return false;
    }
    
    return true;
}

bool Node::LoadXML(const XMLElement& source, SceneResolver& resolver, bool readChildren, bool rewriteIDs, CreateMode mode)
{
    // Remove all children and components first in case this is not a fresh load
    RemoveAllChildren();
    RemoveAllComponents();
    
    if (!Serializable::LoadXML(source))
        return false;
    
    XMLElement compElem = source.GetChild("component");
    while (compElem)
    {
        String typeName = compElem.GetAttribute("type");
        unsigned compID = compElem.GetInt("id");
        Component* newComponent = CreateComponent(ShortStringHash(typeName),
            (mode == REPLICATED && compID < FIRST_LOCAL_ID) ? REPLICATED : LOCAL, rewriteIDs ? 0 : compID);
        if (newComponent)
        {
            resolver.AddComponent(compID, newComponent);
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
        unsigned nodeID = childElem.GetInt("id");
        Node* newNode = CreateChild(rewriteIDs ? 0 : nodeID, (mode == REPLICATED && nodeID < FIRST_LOCAL_ID) ? REPLICATED :
            LOCAL);
        resolver.AddNode(nodeID, newNode);
        if (!newNode->LoadXML(childElem, resolver, readChildren, rewriteIDs, mode))
            return false;
        
        childElem = childElem.GetNext("node");
    }
    
    return true;
}


void Node::PrepareNetworkUpdate()
{
    // Update dependency nodes list first
    dependencyNodes_.Clear();
    
    // Add the parent node, but if it is local, traverse to the first non-local node
    if (parent_ && parent_ != scene_)
    {
        Node* current = parent_;
        while (current->id_ >= FIRST_LOCAL_ID)
            current = current->parent_;
        if (current && current != scene_)
            dependencyNodes_.Push(current);
    }
    
    // Let the components add their dependencies
    for (Vector<SharedPtr<Component> >::ConstIterator i = components_.Begin(); i != components_.End(); ++i)
    {
        Component* component = *i;
        if (component->GetID() < FIRST_LOCAL_ID)
            component->GetDependencyNodes(dependencyNodes_);
    }
    
    // Then check for node attribute changes
    if (!networkState_)
        AllocateNetworkState();
    
    const Vector<AttributeInfo>* attributes = networkState_->attributes_;
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
            
            // Mark the attribute dirty in all replication states that are tracking this node
            for (PODVector<ReplicationState*>::Iterator j = networkState_->replicationStates_.Begin(); j !=
                networkState_->replicationStates_.End();
                ++j)
            {
                NodeReplicationState* nodeState = static_cast<NodeReplicationState*>(*j);
                nodeState->dirtyAttributes_.Set(i);
                
                // Add node to the dirty set if not added yet
                if (!nodeState->markedDirty_)
                {
                    nodeState->markedDirty_ = true;
                    nodeState->sceneState_->dirtyNodes_.Insert(id_);
                }
            }
        }
    }
    
    // Finally check for user var changes
    for (VariantMap::ConstIterator i = vars_.Begin(); i != vars_.End(); ++i)
    {
        VariantMap::ConstIterator j = networkState_->previousVars_.Find(i->first_);
        if (j == networkState_->previousVars_.End() || j->second_ != i->second_)
        {
            networkState_->previousVars_[i->first_] = i->second_;
            
            // Mark the var dirty in all replication states that are tracking this node
            for (PODVector<ReplicationState*>::Iterator j = networkState_->replicationStates_.Begin(); j !=
                networkState_->replicationStates_.End(); ++j)
            {
                NodeReplicationState* nodeState = static_cast<NodeReplicationState*>(*j);
                nodeState->dirtyVars_.Insert(i->first_);
                
                if (!nodeState->markedDirty_)
                {
                    nodeState->markedDirty_ = true;
                    nodeState->sceneState_->dirtyNodes_.Insert(id_);
                }
            }
        }
    }
    
    networkUpdate_ = false;
}

void Node::CleanupConnection(Connection* connection)
{
    if (owner_ == connection)
        owner_ = 0;
    
    if (networkState_)
    {
        for (unsigned i = networkState_->replicationStates_.Size() - 1; i < networkState_->replicationStates_.Size(); --i)
        {
            if (networkState_->replicationStates_[i]->connection_ == connection)
                networkState_->replicationStates_.Erase(i);
        }
    }
}

void Node::MarkNetworkUpdate()
{
    if (!networkUpdate_ && scene_ && id_ < FIRST_LOCAL_ID)
    {
        scene_->MarkNetworkUpdate(this);
        networkUpdate_ = true;
    }
}

void Node::MarkReplicationDirty()
{
    if (networkState_)
    {
        for (PODVector<ReplicationState*>::Iterator j = networkState_->replicationStates_.Begin(); j !=
            networkState_->replicationStates_.End(); ++j)
        {
            NodeReplicationState* nodeState = static_cast<NodeReplicationState*>(*j);
            if (!nodeState->markedDirty_)
            {
                nodeState->markedDirty_ = true;
                nodeState->sceneState_->dirtyNodes_.Insert(id_);
            }
        }
    }
}

Node* Node::CreateChild(unsigned id, CreateMode mode)
{
    SharedPtr<Node> newNode(new Node(context_));
    
    // If zero ID specified, or the ID is already taken, let the scene assign
    if (scene_)
    {
        if (!id || scene_->GetNode(id))
            id = scene_->GetFreeNodeID(mode);
        newNode->SetID(id);
    }
    else
        newNode->SetID(id);
    
    AddChild(newNode);
    return newNode;
}

void Node::AddComponent(Component* component, unsigned id, CreateMode mode)
{
    if (!component)
        return;
    
    components_.Push(SharedPtr<Component>(component));
    
    // If zero ID specified, or the ID is already taken, let the scene assign
    if (scene_)
    {
        if (!id || scene_->GetComponent(id))
            id = scene_->GetFreeComponentID(mode);
        component->SetID(id);
        scene_->ComponentAdded(component);
    }
    else
        component->SetID(id);
    
    component->SetNode(this);
    component->OnMarkedDirty(this);
    
    // Check attributes of the new component on next network update, and mark node dirty in all replication states
    component->MarkNetworkUpdate();
    MarkNetworkUpdate();
    MarkReplicationDirty();
}

void Node::UpdateWorldTransform() const
{
    Matrix3x4 transform = GetTransform();
    if (parent_)
        worldTransform_ = parent_->GetWorldTransform() * transform;
    else
        worldTransform_ = transform;
    
    dirty_ = false;
}

void Node::RemoveChild(Vector<SharedPtr<Node> >::Iterator i)
{
    (*i)->parent_ = 0;
    (*i)->MarkDirty();
    (*i)->MarkNetworkUpdate();
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
            node->GetChildrenWithComponentRecursive(dest, type);
    }
}

Node* Node::CloneRecursive(Node* parent, SceneResolver& resolver, CreateMode mode)
{
    // Create clone node
    Node* cloneNode = parent->CreateChild(0, (mode == REPLICATED && id_ < FIRST_LOCAL_ID) ? REPLICATED : LOCAL);
    resolver.AddNode(id_, cloneNode);
    
    // Copy attributes
    unsigned numAttributes = GetNumAttributes();
    for (unsigned j = 0; j < numAttributes; ++j)
        cloneNode->SetAttribute(j, GetAttribute(j));
    
    // Clone components
    for (Vector<SharedPtr<Component> >::ConstIterator i = components_.Begin(); i != components_.End(); ++i)
    {
        Component* component = *i;
        Component* cloneComponent = cloneNode->CreateComponent(component->GetType(), (mode == REPLICATED && component->GetID() <
            FIRST_LOCAL_ID) ? REPLICATED : LOCAL);
        if (!cloneComponent)
        {
            LOGERROR("Could not clone component " + component->GetTypeName());
            continue;
        }
        resolver.AddComponent(component->GetID(), cloneComponent);
        
        numAttributes = component->GetNumAttributes();
        for (unsigned j = 0; j < numAttributes; ++j)
            cloneComponent->SetAttribute(j, component->GetAttribute(j));
    }
    
    // Clone child nodes recursively
    for (Vector<SharedPtr<Node> >::ConstIterator i = children_.Begin(); i != children_.End(); ++i)
    {
        Node* node = *i;
        node->CloneRecursive(cloneNode, resolver, mode);
    }
    
    return cloneNode;
}

void Node::RemoveComponent(Vector<SharedPtr<Component> >::Iterator i)
{
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
