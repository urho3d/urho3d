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
#include "Scene.h"
#include "StringUtils.h"
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
    position_(Vector3::ZERO),
    rotation_(Quaternion::IDENTITY),
    scale_(Vector3::UNITY),
    worldTransform_(Matrix4x3::IDENTITY),
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
    
    ATTRIBUTE(Node, VAR_STRING, "Name", name_, std::string());
    ATTRIBUTE(Node, VAR_VECTOR3, "Position", position_, Vector3::ZERO);
    ATTRIBUTE(Node, VAR_QUATERNION, "Rotation", rotation_, Quaternion::IDENTITY);
    ATTRIBUTE(Node, VAR_VECTOR3, "Scale", scale_, Vector3::UNITY);
    ATTRIBUTE_MODE(Node, VAR_VARIANTMAP, "Variables", vars_, VariantMap(), AM_SERIALIZATION);
}

void Node::OnEvent(Object* sender, bool broadcast, StringHash eventType, VariantMap& eventData)
{
    // Make a weak pointer to self to check for destruction during event handling
    WeakPtr<Node> self(this);
    
    // If this is a targeted event, forward it to all components
    if (!broadcast)
    {
        for (unsigned i = components_.size() - 1; i < components_.size(); --i)
        {
            components_[i]->OnEvent(sender, broadcast, eventType, eventData);
            if (self.IsExpired())
                return;
        }
    }
    else
        Object::OnEvent(sender, broadcast, eventType, eventData);
}

void Node::OnSetAttribute(const AttributeInfo& attr, const Variant& value)
{
    switch (attr.offset_)
    {
    case offsetof(Node, name_):
        SetName(value.GetString());
        break;
        
    case offsetof(Node, position_):
    case offsetof(Node, rotation_):
    case offsetof(Node, scale_):
        Serializable::OnSetAttribute(attr, value);
        // If transform changes, dirty the node as applicable
        if (!dirty_)
            MarkDirty();
        break;
    
    default:
        Serializable::OnSetAttribute(attr, value);
        break;
    }
}

bool Node::Load(Deserializer& source)
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
        Component* newComponent = CreateComponent(newType, compBuffer.ReadUInt());
        if (newComponent)
        {
            if (!newComponent->Load(compBuffer))
                return false;
        }
    }
    
    unsigned numChildren = source.ReadVLE();
    for (unsigned i = 0; i < numChildren; ++i)
    {
        Node* newNode = CreateChild(source.ReadUInt());
        if (!newNode->Load(source))
            return false;
    }
    
    return true;
}

bool Node::Save(Serializer& dest)
{
    if (!Serializable::Save(dest))
        return false;
    
    dest.WriteVLE(components_.size());
    for (unsigned i = 0; i < components_.size(); ++i)
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
    
    dest.WriteVLE(children_.size());
    for (unsigned i = 0; i < children_.size(); ++i)
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
    // Remove all children and components first in case this is not a fresh load
    RemoveAllChildren();
    RemoveAllComponents();
    
    if (!Serializable::LoadXML(source))
        return false;
    
    XMLElement compElem = source.GetChildElement("component");
    while (compElem)
    {
        std::string typeName = compElem.GetString("type");
        Component* newComponent = CreateComponent(ShortStringHash(compElem.GetString("type")), compElem.GetInt("id"));
        if (newComponent)
        {
            if (!newComponent->LoadXML(compElem))
                return false;
        }
        
        compElem = compElem.GetNextElement("component");
    }
    
    XMLElement childElem = source.GetChildElement("node");
    while (childElem)
    {
        Node* newNode = CreateChild(compElem.GetInt("id"));
        if (!newNode->LoadXML(childElem))
            return false;
        
        childElem = childElem.GetNextElement("node");
    }
    
    return true;
}

bool Node::SaveXML(XMLElement& dest)
{
    if (!Serializable::SaveXML(dest))
        return false;
    
    for (unsigned i = 0; i < components_.size(); ++i)
    {
        Component* component = components_[i];
        XMLElement compElem = dest.CreateChildElement("component");
        
        compElem.SetString("type", component->GetTypeNameStr());
        compElem.SetInt("id", component->GetID());
        if (!component->SaveXML(compElem))
            return false;
    }
    
    for (unsigned i = 0; i < children_.size(); ++i)
    {
        Node* node = children_[i];
        XMLElement childElem = dest.CreateChildElement("node");
        
        childElem.SetInt("id", node->GetID());
        if (!node->SaveXML(childElem))
            return false;
    }
    
    return true;
}

void Node::PostLoad()
{
    for (unsigned i = 0; i < components_.size(); ++i)
        components_[i]->PostLoad();
    
    for (unsigned i = 0; i < children_.size(); ++i)
        children_[i]->PostLoad();
}

void Node::SetName(const std::string& name)
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
    for (std::vector<WeakPtr<Component> >::iterator i = listeners_.begin(); i != listeners_.end();)
    {
        if (*i)
        {
            (*i)->OnMarkedDirty(this);
            ++i;
        }
        // If listener has expired, erase from list
        else
            i = listeners_.erase(i);
    }
    
    for (std::vector<SharedPtr<Node> >::iterator i = children_.begin(); i != children_.end(); ++i)
        (*i)->MarkDirty();
}

Node* Node::CreateChild(const std::string& name)
{
    SharedPtr<Node> newNode(new Node(context_));
    newNode->SetName(name);
    AddChild(newNode);
    return newNode;
}

void Node::AddChild(Node* node)
{
    // Check for illegal parent assignments, including attempt to reparent the scene
    if ((!node) || (node == this) || (node->parent_ == this) || (parent_ == node) || (scene_ == node))
        return;
    
    // Add first, then remove from old parent, to ensure the node does not get deleted
    children_.push_back(SharedPtr<Node>(node));
    
    if (node->parent_)
        node->parent_->RemoveChild(node);
    
    // Add to the scene if not added yet
    if ((scene_) && (!node->GetScene()))
        scene_->NodeAdded(node);
    
    node->parent_ = this;
    node->MarkDirty();
}

void Node::RemoveChild(Node* node)
{
    if (!node)
        return;
    
    for (std::vector<SharedPtr<Node> >::iterator i = children_.begin(); i != children_.end(); ++i)
    {
        if (i->GetPtr() == node)
        {
            RemoveChild(i);
            return;
        }
    }
}

void Node::RemoveAllChildren()
{
    while (children_.size())
        RemoveChild(children_.end() - 1);
}

void Node::SetParent(Node* parent)
{
    if (parent)
        parent->AddChild(this);
}

Component* Node::CreateComponent(ShortStringHash type)
{
    return CreateComponent(type, 0);
}

Component* Node::GetOrCreateComponent(ShortStringHash type)
{
    Component* oldComponent = GetComponent(type);
    if (oldComponent)
        return oldComponent;
    else
        return CreateComponent(type, 0);
}

void Node::RemoveComponent(Component* component)
{
    for (std::vector<SharedPtr<Component> >::iterator i = components_.begin(); i != components_.end(); ++i)
    {
        if (*i == component)
        {
            WeakPtr<Component> componentWeak(*i);
            
            RemoveListener(*i);
            if (scene_)
                scene_->ComponentRemoved(*i);
            components_.erase(i);
            
            // If the component is still referenced elsewhere, reset its node pointer now
            if (componentWeak)
                componentWeak->SetNode(0);
            return;
        }
    }
}

void Node::RemoveAllComponents()
{
    while (components_.size())
    {
        std::vector<SharedPtr<Component> >::iterator i = components_.end() - 1;
        WeakPtr<Component> componentWeak(*i);
        
        RemoveListener(*i);
        if (scene_)
            scene_->ComponentRemoved(*i);
        components_.erase(i);
        
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
    for (std::vector<WeakPtr<Component> >::iterator i = listeners_.begin(); i != listeners_.end(); ++i)
    {
        if ((*i) == component)
            return;
    }
    
    listeners_.push_back(WeakPtr<Component>(component));
    // If the node is currently dirty, notify immediately
    if (dirty_)
        component->OnMarkedDirty(this);
}

void Node::RemoveListener(Component* component)
{
    for (std::vector<WeakPtr<Component> >::iterator i = listeners_.begin(); i != listeners_.end(); ++i)
    {
        if ((*i) == component)
        {
            listeners_.erase(i);
            return;
        }
    }
}

void Node::Remove()
{
    if (parent_)
        parent_->RemoveChild(this);
}

unsigned Node::GetNumChildren(bool recursive) const
{
    if (!recursive)
        return children_.size();
    else
    {
        unsigned allChildren = children_.size();
        for (std::vector<SharedPtr<Node> >::const_iterator i = children_.begin(); i != children_.end(); ++i)
            allChildren += (*i)->GetNumChildren(true);
        
        return allChildren;
    }
}

void Node::GetChildren(std::vector<Node*>& dest, bool recursive) const
{
    dest.clear();
    
    if (!recursive)
    {
        for (std::vector<SharedPtr<Node> >::const_iterator i = children_.begin(); i != children_.end(); ++i)
            dest.push_back(*i);
    }
    else
        GetChildrenRecursive(dest);
}

void Node::GetChildrenWithComponent(std::vector<Node*>& dest, ShortStringHash type, bool recursive) const
{
    dest.clear();
    
    if (!recursive)
    {
        for (std::vector<SharedPtr<Node> >::const_iterator i = children_.begin(); i != children_.end(); ++i)
        {
            if ((*i)->HasComponent(type))
                dest.push_back(*i);
        }
    }
    else
        GetChildrenWithComponentRecursive(dest, type);
}

Node* Node::GetChild(unsigned index) const
{
    return index < children_.size() ? children_[index].GetPtr() : 0;
}

Node* Node::GetChild(const std::string& name, bool recursive) const
{
    return GetChild(StringHash(name), recursive);
}

Node* Node::GetChild(StringHash nameHash, bool recursive) const
{
    for (std::vector<SharedPtr<Node> >::const_iterator i = children_.begin(); i != children_.end(); ++i)
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

void Node::GetComponents(std::vector<Component*>& dest, ShortStringHash type) const
{
    dest.clear();
    for (std::vector<SharedPtr<Component> >::const_iterator i = components_.begin(); i != components_.end(); ++i)
    {
        if ((*i)->GetType() == type)
            dest.push_back(*i);
    }
}

bool Node::HasComponent(ShortStringHash type) const
{
    for (std::vector<SharedPtr<Component> >::const_iterator i = components_.begin(); i != components_.end(); ++i)
    {
        if ((*i)->GetType() == type)
            return true;
    }
    return false;
}

Component* Node::GetComponent(unsigned index) const
{
    return index < components_.size() ? components_[index].GetPtr() : 0;
}

Component* Node::GetComponent(ShortStringHash type, unsigned index) const
{
    unsigned cmpIndex = 0;
    for (std::vector<SharedPtr<Component> >::const_iterator i = components_.begin(); i != components_.end(); ++i)
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


Component* Node::CreateComponent(ShortStringHash type, unsigned id)
{
    // Make sure the object in question is a component
    SharedPtr<Component> newComponent = DynamicCast<Component>(context_->CreateObject(type));
    if (!newComponent)
    {
        LOGERROR("Could not create unknown component type " + ToString(type));
        return 0;
    }
    
    // If zero ID specified, the scene will auto-assign
    newComponent->SetID(id);
    
    components_.push_back(newComponent);
    if (scene_)
        scene_->ComponentAdded(newComponent);
    
    newComponent->SetNode(this);
    newComponent->OnMarkedDirty(this);
    
    return newComponent;
}

Node* Node::CreateChild(unsigned id)
{
    SharedPtr<Node> newNode(new Node(context_));
    newNode->SetID(id);
    AddChild(newNode);
    return newNode;
}

void Node::UpdateWorldTransform()
{
    // For now, assume that the Scene has identity transform so that we skip one matrix multiply. However in the future
    // we may want dynamic root nodes for large worlds
    if ((parent_) && (parent_ != scene_))
    {
        if (parent_->dirty_)
            parent_->UpdateWorldTransform();
        worldTransform_ = parent_->worldTransform_ * Matrix4x3(position_, rotation_, scale_);
    }
    else
        worldTransform_ = Matrix4x3(position_, rotation_, scale_);
    
    dirty_ = false;
}

void Node::RemoveChild(std::vector<SharedPtr<Node> >::iterator i)
{
    (*i)->parent_ = 0;
    (*i)->MarkDirty();
    children_.erase(i);
}

void Node::GetChildrenRecursive(std::vector<Node*>& dest) const
{
    for (std::vector<SharedPtr<Node> >::const_iterator i = children_.begin(); i != children_.end(); ++i)
    {
        Node* node = *i;
        dest.push_back(node);
        if (!node->children_.empty())
            node->GetChildrenRecursive(dest);
    }
}

void Node::GetChildrenWithComponentRecursive(std::vector<Node*>& dest, ShortStringHash type) const
{
    for (std::vector<SharedPtr<Node> >::const_iterator i = children_.begin(); i != children_.end(); ++i)
    {
        Node* node = *i;
        if (node->HasComponent(type))
            dest.push_back(node);
        if (!node->children_.empty())
            node->GetChildrenRecursive(dest);
    }
}

void Node::SetID(unsigned id)
{
    id_ = id;
}

void Node::setScene(Scene* scene)
{
    scene_ = scene;
}
