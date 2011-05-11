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

#pragma once

#include "Matrix4x3.h"
#include "Serializable.h"

#include <vector>

class Component;
class Scene;

/// Scene node that may contain components and child nodes
class Node : public Serializable
{
    OBJECT(Node);
    
    friend class Scene;
    
public:
    /// Construct
    Node(Context* context);
    /// Destruct. Any child nodes are detached
    virtual ~Node();
    /// Register object factory
    static void RegisterObject(Context* context);
    
    /// Handle event
    virtual void OnEvent(Object* sender, bool broadcast, StringHash eventType, VariantMap& eventData);
    /// Handle attribute write access
    virtual void OnSetAttribute(const AttributeInfo& attr, const Variant& value);
    /// Load from binary data. Return true if successful
    virtual bool Load(Deserializer& source);
    /// Load from XML data. Return true if successful
    virtual bool LoadXML(const XMLElement& source);
    /// Save as binary data. Return true if successful
    virtual bool Save(Serializer& dest);
    /// Save as XML data. Return true if successful
    virtual bool SaveXML(XMLElement& dest);
    /// Perform post-load for components and child nodes
    virtual void PostLoad();
    
    /// Set name
    void SetName(const std::string& name);
    /// Set position
    void SetPosition(const Vector3& position);
    /// Set rotation
    void SetRotation(const Quaternion& rotation);
    /// Set direction. Positive Z equals identity
    void SetDirection(const Vector3& direction);
    /// Set uniform scale
    void SetScale(float scale);
    /// Set scale
    void SetScale(const Vector3& scale);
    /// Set transform
    void SetTransform(const Vector3& position, const Quaternion& rotation);
    /// Set transform
    void SetTransform(const Vector3& position, const Quaternion& rotation, float scale);
    /// Set transform
    void SetTransform(const Vector3& position, const Quaternion& rotation, const Vector3& scale);
    /// Move the scene node
    void Translate(const Vector3& delta);
    /// Move the scene node relative to its rotation
    void TranslateRelative(const Vector3& delta);
    /// Rotate the scene node
    void Rotate(const Quaternion& delta, bool fixedAxis = false);
    /// Rotate around the X axis
    void Pitch(float angle, bool fixedAxis = false);
    /// Rotate around the Y axis
    void Yaw(float angle, bool fixedAxis = false);
    /// Rotate around the Z axis
    void Roll(float angle, bool fixedAxis = false);
    /// Modify scale uniformly
    void Scale(float scale);
    /// Modify scale
    void Scale(const Vector3& scale);
    /// Mark node and child nodes to need world transform recalculation. Notify listener components
    void MarkDirty();
    /// Create a child scene node
    Node* CreateChild(const std::string& name = std::string(), bool local = false);
    /// Add a child scene node
    void AddChild(Node* node);
    /// Remove a child scene node
    void RemoveChild(Node* node);
    /// Remove all child scene nodes
    void RemoveAllChildren();
    /// Remove from the parent node. If no other shared pointer references exist, causes immediate deletion
    void Remove();
    /// Set parent scene node. Same as parent->AddChild(this)
    void SetParent(Node* parent);
    /// Create a component to this node
    Component* CreateComponent(ShortStringHash type, bool local = false);
    /// Create a component to this node if it does not exist already
    Component* GetOrCreateComponent(ShortStringHash type, bool local = false);
    /// Remove a component from this node
    void RemoveComponent(Component* component);
    /// Remove all components from this node
    void RemoveAllComponents();
    /// Add listener component that is notified of node being dirtied. Can either be in the same node or another
    void AddListener(Component* component);
    /// Remove listener component
    void RemoveListener(Component* component);
    /// Template version of creating a component
    template <class T> T* CreateComponent(bool local = false);
    /// Template version of getting or creating a component
    template <class T> T* GetOrCreateComponent(bool local = false);
    
    /// Return ID
    unsigned GetID() const { return id_; }
    /// Return name
    const std::string& GetName() const { return name_; }
    /// Return name hash
    StringHash GetNameHash() const { return nameHash_; }
    /// Return parent scene node
    Node* GetParent() const { return parent_; }
    /// Return scene
    Scene* GetScene() const { return scene_; }
    /// Return position
    const Vector3& GetPosition() const { return position_; }
    /// Return rotation
    const Quaternion& GetRotation() const { return rotation_; }
    /// Return direction. Identity rotation equals positive Z
    Vector3 GetDirection() const { return rotation_ * Vector3::FORWARD; }
    /// Return scale
    const Vector3& GetScale() const { return scale_; }
    /// Return local transform
    Matrix4x3 GetTransform() const { return Matrix4x3(position_, rotation_, scale_); }
    
    /// Return world-space position
    Vector3 GetWorldPosition()
    {
        if (dirty_)
            UpdateWorldTransform();
        
        return worldTransform_.GetTranslation();
    }
    
    /// Return world-space rotation
    Quaternion GetWorldRotation()
    {
        if (dirty_)
            UpdateWorldTransform();
        
        return worldTransform_.GetRotation();
    }
    
    /// Return world-space direction
    Vector3 GetWorldDirection()
    {
        if (dirty_)
            UpdateWorldTransform();
        
        return worldTransform_.GetRotationMatrix() * Vector3::FORWARD;
    }
    
    /// Return world-space scale
    Vector3 GetWorldScale()
    {
        if (dirty_)
            UpdateWorldTransform();
        
        return worldTransform_.GetScale();
    }
    
    /// Return world-space transform
    const Matrix4x3& GetWorldTransform()
    {
        if (dirty_)
            UpdateWorldTransform();
        
        return worldTransform_;
    }
    
    /// Return whether transform has changed and world transform needs recalculation
    bool IsDirty() const { return dirty_; }
    /// Return number of child scene nodes
    unsigned GetNumChildren(bool recursive = false) const;
    /// Return immediate child scene nodes
    const std::vector<SharedPtr<Node> >& GetChildren() const { return children_; }
    /// Return child scene nodes, optionally recursive
    void GetChildren(std::vector<Node*>& dest, bool recursive = false) const;
    /// Return child scene nodes with a specific component
    void GetChildrenWithComponent(std::vector<Node*>& dest, ShortStringHash type, bool recursive = false) const;
    /// Return child scene node by index
    Node* GetChild(unsigned index) const;
    /// Return child scene node by name
    Node* GetChild(const std::string& name, bool recursive = false) const;
    /// Return child scene node by name hash
    Node* GetChild(StringHash nameHash, bool recursive = false) const;
    /// Return number of components
    unsigned GetNumComponents() const { return components_.size(); }
    /// Return all components
    const std::vector<SharedPtr<Component> >& GetComponents() const { return components_; }
    /// Return all components of type
    void GetComponents(std::vector<Component*>& dest, ShortStringHash type) const;
    /// Return component by index
    Component* GetComponent(unsigned index) const;
    /// Return component by type. The optional index allows to specify which component, if there are several
    Component* GetComponent(ShortStringHash type, unsigned index = 0) const;
    /// Return whether has a specific component
    bool HasComponent(ShortStringHash type) const;
    /// Return listener components
    const std::vector<WeakPtr<Component> > GetListeners() const { return listeners_; }
    /// Return user variables
    VariantMap& GetVars() { return vars_; }
    /// Template version of returning child nodes with a specific component
    template <class T> void GetChildrenWithComponent(std::vector<Node*>& dest, bool recursive = false) const;
    /// Template version of returning a component by type
    template <class T> T* GetComponent(unsigned index = 0) const;
    /// Template version of returning all components of type
    template <class T> void GetComponents(std::vector<T*>& dest) const;
    /// Template version of checking whether has a specific component
    template <class T> bool HasComponent() const;
    
    /// User variables
    VariantMap vars_;
    
protected:
    /// Load components and optionally load child nodes. Used internally
    bool Load(Deserializer& source, bool loadChildren);
    /// Load components from XML data and optionally load child nodes. Used internally
    bool LoadXML(const XMLElement& source, bool loadChildren);
    /// Create a component with specific ID. Used internally
    Component* CreateComponent(ShortStringHash type, unsigned id, bool local);
    /// Create a child node with specific ID. Used internally
    Node* CreateChild(unsigned id, bool local);
    
private:
    /// Recalculate the world transform
    void UpdateWorldTransform();
    /// Remove child node by iterator
    void RemoveChild(std::vector<SharedPtr<Node> >::iterator i);
    /// Return child nodes recursively
    void GetChildrenRecursive(std::vector<Node*>& dest) const;
    /// Return child nodes with a specific component recursively
    void GetChildrenWithComponentRecursive(std::vector<Node*>& dest, ShortStringHash type) const;
    /// Set ID. Called by Scene
    void SetID(unsigned id);
    /// Set scene. Called by Scene
    void setScene(Scene* scene);
    
    /// Unique ID within the scene
    unsigned id_;
    /// Parent scene node
    Node* parent_;
    /// Scene (root node)
    Scene* scene_;
    /// Position
    Vector3 position_;
    /// Rotation
    Quaternion rotation_;
    /// Scale
    Vector3 scale_;
    /// World-space transform matrix
    Matrix4x3 worldTransform_;
    /// Name
    std::string name_;
    /// Name hash
    StringHash nameHash_;
    /// Child scene nodes
    std::vector<SharedPtr<Node> > children_;
    /// Components
    std::vector<SharedPtr<Component> > components_;
    /// Node listeners
    std::vector<WeakPtr<Component> > listeners_;
    /// Consecutive rotation count for rotation renormalization
    unsigned char rotateCount_;
    /// World transform needs update flag
    bool dirty_;
};

template <class T> T* Node::CreateComponent(bool local)
{
    return static_cast<T*>(CreateComponent(T::GetTypeStatic(), local));
}

template <class T> T* Node::GetOrCreateComponent(bool local)
{
    return static_cast<T*>(GetOrCreateComponent(T::GetTypeStatic(), local));
}

template <class T> void Node::GetChildrenWithComponent(std::vector<Node*>& dest, bool recursive) const
{
    GetChildrenWithComponent(dest, T::GetTypeStatic(), recursive);
}

template <class T> T* Node::GetComponent(unsigned index) const
{
    return static_cast<T*>(GetComponent(T::GetTypeStatic(), index));
}

template <class T> void Node::GetComponents(std::vector<T*>& dest) const
{
    GetComponents(reinterpret_cast<std::vector<Component*>&>(dest), T::GetTypeStatic());
}

template <class T> bool Node::HasComponent() const
{
    return HasComponent(T::GetTypeStatic());
}
