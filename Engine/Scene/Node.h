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

#pragma once

#include "Matrix3x4.h"
#include "Serializable.h"
#include "VectorBuffer.h"

namespace Urho3D
{

class Component;
class Connection;
class Scene;
class SceneResolver;

struct NodeReplicationState;

/// Component and child node creation mode for networking.
enum CreateMode
{
    REPLICATED = 0,
    LOCAL = 1
};

/// %Scene node that may contain components and child nodes.
class Node : public Serializable
{
    OBJECT(Node);
    
    friend class Connection;
    
public:
    /// Construct.
    Node(Context* context);
    /// Destruct. Any child nodes are detached.
    virtual ~Node();
    /// Register object factory.
    static void RegisterObject(Context* context);
    
    /// Handle attribute write access.
    virtual void OnSetAttribute(const AttributeInfo& attr, const Variant& src);
    /// Load from binary data. Return true if successful.
    virtual bool Load(Deserializer& source);
    /// Load from XML data. Return true if successful.
    virtual bool LoadXML(const XMLElement& source);
    /// Save as binary data. Return true if successful.
    virtual bool Save(Serializer& dest);
    /// Save as XML data. Return true if successful.
    virtual bool SaveXML(XMLElement& dest);
    /// Apply attribute changes that can not be applied immediately recursively to child nodes and components.
    virtual void ApplyAttributes();
    /// Return whether should save default-valued attributes into XML. Always save node transforms for readability, even if identity.
    virtual bool SaveDefaultAttributes() const { return true; }
    /// Add a replication state that is tracking this node.
    virtual void AddReplicationState(NodeReplicationState* state);
    
    /// Save to an XML file. Return true if successful.
    bool SaveXML(Serializer& dest);
    /// Set name.
    void SetName(const String& name);
    /// Set position relative to parent node.
    void SetPosition(const Vector3& position);
    /// Set rotation relative to parent node.
    void SetRotation(const Quaternion& rotation);
    /// Set direction relative to parent node. Positive Z equals identity.
    void SetDirection(const Vector3& direction);
    /// Set uniform scale relative to parent node.
    void SetScale(float scale);
    /// Set scale relative to parent node.
    void SetScale(const Vector3& scale);
    /// Set transform relative to parent node.
    void SetTransform(const Vector3& position, const Quaternion& rotation);
    /// Set transform relative to parent node.
    void SetTransform(const Vector3& position, const Quaternion& rotation, float scale);
    /// Set transform relative to parent node.
    void SetTransform(const Vector3& position, const Quaternion& rotation, const Vector3& scale);
    /// Set position relative to world space.
    void SetWorldPosition(const Vector3& position);
    /// Set rotation relative to world space.
    void SetWorldRotation(const Quaternion& rotation);
    /// Set direction relative to world space.
    void SetWorldDirection(const Vector3& direction);
    /// Set uniform scale relative to world space.
    void SetWorldScale(float scale);
    /// Set scale relative to world space.
    void SetWorldScale(const Vector3& scale);
    /// Set transform relative to world space.
    void SetWorldTransform(const Vector3& position, const Quaternion& rotation);
    /// Set transform relative to world space.
    void SetWorldTransform(const Vector3& position, const Quaternion& rotation, float scale);
    /// Set transform relative to world space.
    void SetWorldTransform(const Vector3& position, const Quaternion& rotation, const Vector3& scale);
    /// Move the scene node.
    void Translate(const Vector3& delta);
    /// Move the scene node relative to its rotation.
    void TranslateRelative(const Vector3& delta);
    /// Rotate the scene node.
    void Rotate(const Quaternion& delta, bool fixedAxis = false);
    /// Rotate around the X axis.
    void Pitch(float angle, bool fixedAxis = false);
    /// Rotate around the Y axis.
    void Yaw(float angle, bool fixedAxis = false);
    /// Rotate around the Z axis.
    void Roll(float angle, bool fixedAxis = false);
    /// Look at a target position.
    void LookAt(const Vector3& target, const Vector3& upAxis = Vector3::UP, bool worldSpace = false);
    /// Modify scale uniformly.
    void Scale(float scale);
    /// Modify scale.
    void Scale(const Vector3& scale);
    /// Set enabled/disabled state without recursion. Components in a disabled node become effectively disabled regardless of their own enable/disable state.
    void SetEnabled(bool enable);
    /// Set enabled/disabled state with optional recursion.
    void SetEnabled(bool enable, bool recursive);
    /// Set owner connection for networking.
    void SetOwner(Connection* owner);
    /// Mark node and child nodes to need world transform recalculation. Notify listener components.
    void MarkDirty();
    /// Create a child scene node.
    Node* CreateChild(const String& name = String::EMPTY, CreateMode mode = REPLICATED);
    /// Add a child scene node.
    void AddChild(Node* node);
    /// Remove a child scene node.
    void RemoveChild(Node* node);
    /// Remove all child scene nodes.
    void RemoveAllChildren();
    /// Create a component to this node (with specified ID if provided).
    Component* CreateComponent(ShortStringHash type, CreateMode mode = REPLICATED, unsigned id = 0);
    /// Create a component to this node if it does not exist already.
    Component* GetOrCreateComponent(ShortStringHash type, CreateMode mode = REPLICATED);
    /// Remove a component from this node.
    void RemoveComponent(Component* component);
    /// Remove the first component of specific type from this node.
    void RemoveComponent(ShortStringHash type);
    /// Remove all components from this node.
    void RemoveAllComponents();
    /// Clone scene node, components and child nodes. Return the clone.
    Node* Clone(CreateMode mode = REPLICATED);
    /// Remove from the parent node. If no other shared pointer references exist, causes immediate deletion.
    void Remove();
    /// Set parent scene node. Retains the world transform.
    void SetParent(Node* parent);
    /// Set a user variable.
    void SetVar(ShortStringHash key, const Variant& value);
    /// Add listener component that is notified of node being dirtied. Can either be in the same node or another.
    void AddListener(Component* component);
    /// Remove listener component.
    void RemoveListener(Component* component);
    /// Template version of creating a component.
    template <class T> T* CreateComponent(CreateMode mode = REPLICATED);
    /// Template version of getting or creating a component.
    template <class T> T* GetOrCreateComponent(CreateMode mode = REPLICATED);
    
    /// Return ID.
    unsigned GetID() const { return id_; }
    /// Return name.
    const String& GetName() const { return name_; }
    /// Return name hash.
    StringHash GetNameHash() const { return nameHash_; }
    /// Return parent scene node.
    Node* GetParent() const { return parent_; }
    /// Return scene.
    Scene* GetScene() const { return scene_; }
    /// Return whether is enabled. Disables nodes effectively disable all their components.
    bool IsEnabled() const { return enabled_; }
    /// Return owner connection in networking.
    Connection* GetOwner() const { return owner_; }
    /// Return position relative to parent node.
    const Vector3& GetPosition() const { return position_; }
    /// Return rotation relative to parent node.
    const Quaternion& GetRotation() const { return rotation_; }
    /// Return direction relative to parent node. Identity rotation equals positive Z.
    Vector3 GetDirection() const { return rotation_ * Vector3::FORWARD; }
    /// Return scale relative to parent node.
    const Vector3& GetScale() const { return scale_; }
    /// Return transform matrix relative to parent node.
    Matrix3x4 GetTransform() const { return Matrix3x4(position_, rotation_, scale_); }
    
    /// Return position in world space.
    Vector3 GetWorldPosition() const
    {
        return GetWorldTransform().Translation();
    }
    
    /// Return rotation in world space.
    Quaternion GetWorldRotation() const
    {
        return GetWorldTransform().Rotation();
    }
    
    /// Return direction in world space.
    Vector3 GetWorldDirection() const
    {
        return GetWorldTransform().RotationMatrix() * Vector3::FORWARD;
    }
    
    /// Return scale in world space.
    Vector3 GetWorldScale() const
    {
        return GetWorldTransform().Scale();
    }
    
    /// Return transform matrix in world space.
    const Matrix3x4& GetWorldTransform() const
    {
        if (dirty_)
            UpdateWorldTransform();
        
        return worldTransform_;
    }
    
    /// Convert a local space position to world space.
    Vector3 LocalToWorld(const Vector3& position) const;
    /// Convert a local space position or rotation to world space.
    Vector3 LocalToWorld(const Vector4& vector) const;
    /// Convert a world space position to local space.
    Vector3 WorldToLocal(const Vector3& position) const;
    /// Convert a world space position or rotation to local space.
    Vector3 WorldToLocal(const Vector4& vector) const;
    /// Return whether transform has changed and world transform needs recalculation.
    bool IsDirty() const { return dirty_; }
    /// Return number of child scene nodes.
    unsigned GetNumChildren(bool recursive = false) const;
    /// Return immediate child scene nodes.
    const Vector<SharedPtr<Node> >& GetChildren() const { return children_; }
    /// Return child scene nodes, optionally recursive.
    void GetChildren(PODVector<Node*>& dest, bool recursive = false) const;
    /// Return child scene nodes with a specific component.
    void GetChildrenWithComponent(PODVector<Node*>& dest, ShortStringHash type, bool recursive = false) const;
    /// Return child scene node by index.
    Node* GetChild(unsigned index) const;
    /// Return child scene node by name.
    Node* GetChild(const String& name, bool recursive = false) const;
    /// Return child scene node by name.
    Node* GetChild(const char* name, bool recursive = false) const;
    /// Return child scene node by name hash.
    Node* GetChild(StringHash nameHash, bool recursive = false) const;
    /// Return number of components.
    unsigned GetNumComponents() const { return components_.Size(); }
    /// Return number of non-local components.
    unsigned GetNumNetworkComponents() const;
    /// Return all components.
    const Vector<SharedPtr<Component> >& GetComponents() const { return components_; }
    /// Return all components of type. Optionally recursive.
    void GetComponents(PODVector<Component*>& dest, ShortStringHash type, bool recursive = false) const;
    /// Return component by type. If there are several, returns the first.
    Component* GetComponent(ShortStringHash type) const;
    /// Return whether has a specific component.
    bool HasComponent(ShortStringHash type) const;
    /// Return listener components.
    const Vector<WeakPtr<Component> > GetListeners() const { return listeners_; }
    /// Return a user variable.
    const Variant& GetVar(ShortStringHash key) const;
    /// Return all user variables.
    const VariantMap& GetVars() const { return vars_; }
    /// Return first component derived from class.
    template <class T> T* GetDerivedComponent() const;
    /// Return components derived from class.
    template <class T> void GetDerivedComponents(PODVector<T*>& dest) const;
    /// Template version of returning child nodes with a specific component.
    template <class T> void GetChildrenWithComponent(PODVector<Node*>& dest, bool recursive = false) const;
    /// Template version of returning a component by type.
    template <class T> T* GetComponent() const;
    /// Template version of returning all components of type.
    template <class T> void GetComponents(PODVector<T*>& dest, bool recursive = false) const;
    /// Template version of checking whether has a specific component.
    template <class T> bool HasComponent() const;
    
    /// Set ID. Called by Scene.
    void SetID(unsigned id);
    /// Set scene. Called by Scene.
    void SetScene(Scene* scene);
    /// Reset scene. Called by Scene.
    void ResetScene();
    /// Set network position attribute.
    void SetNetPositionAttr(const Vector3& value);
    /// Set network rotation attribute.
    void SetNetRotationAttr(const PODVector<unsigned char>& value);
    /// Set network parent attribute.
    void SetNetParentAttr(const PODVector<unsigned char>& value);
    /// Return network position attribute.
    const Vector3& GetNetPositionAttr() const;
    /// Return network rotation attribute.
    const PODVector<unsigned char>& GetNetRotationAttr() const;
    /// Return network parent attribute.
    const PODVector<unsigned char>& GetNetParentAttr() const;
    /// Load components and optionally load child nodes.
    bool Load(Deserializer& source, SceneResolver& resolver, bool loadChildren = true, bool rewriteIDs = false, CreateMode mode = REPLICATED);
    /// Load components from XML data and optionally load child nodes.
    bool LoadXML(const XMLElement& source, SceneResolver& resolver, bool loadChildren = true, bool rewriteIDs = false, CreateMode mode = REPLICATED);
    /// Return the depended on nodes to order network updates.
    const PODVector<Node*>& GetDependencyNodes() const { return dependencyNodes_; }
    /// Prepare network update by comparing attributes and marking replication states dirty as necessary.
    void PrepareNetworkUpdate();
    /// Clean up all references to a network connection that is about to be removed.
    void CleanupConnection(Connection* connection);
    /// Mark for attribute check on the next network update.
    void MarkNetworkUpdate();
    /// Mark node dirty in scene replication states.
    void MarkReplicationDirty();
    /// Create a child node with specific ID.
    Node* CreateChild(unsigned id, CreateMode mode);
    /// Add a pre-created component.
    void AddComponent(Component* component, unsigned id, CreateMode mode);
    
protected:
    /// User variables.
    VariantMap vars_;

private:
    /// Recalculate the world transform.
    void UpdateWorldTransform() const;
    /// Remove child node by iterator.
    void RemoveChild(Vector<SharedPtr<Node> >::Iterator i);
    /// Return child nodes recursively.
    void GetChildrenRecursive(PODVector<Node*>& dest) const;
    /// Return child nodes with a specific component recursively.
    void GetChildrenWithComponentRecursive(PODVector<Node*>& dest, ShortStringHash type) const;
    /// Return specific components recursively.
    void GetComponentsRecursive(PODVector<Component*>& dest, ShortStringHash type) const;
    /// Clone node recursively.
    Node* CloneRecursive(Node* parent, SceneResolver& resolver, CreateMode mode);
    /// Remove a component from this node with the specified iterator.
    void RemoveComponent(Vector<SharedPtr<Component> >::Iterator i);
   
    /// World-space transform matrix.
    mutable Matrix3x4 worldTransform_;
    /// World transform needs update flag.
    mutable bool dirty_;
    /// Network update queued flag.
    bool networkUpdate_;
    /// Enabled flag.
    bool enabled_;
    /// Parent scene node.
    Node* parent_;
    /// Scene (root node.)
    Scene* scene_;
    /// Unique ID within the scene.
    unsigned id_;
    /// Position.
    Vector3 position_;
    /// Rotation.
    Quaternion rotation_;
    /// Scale.
    Vector3 scale_;
    /// Components.
    Vector<SharedPtr<Component> > components_;
    /// Child scene nodes.
    Vector<SharedPtr<Node> > children_;
    /// Node listeners.
    Vector<WeakPtr<Component> > listeners_;
    /// Nodes this node depends on for network updates.
    PODVector<Node*> dependencyNodes_;
    /// Network owner connection.
    Connection* owner_;
    /// Name.
    String name_;
    /// Name hash.
    StringHash nameHash_;
    /// Attribute buffer for network updates.
    mutable VectorBuffer attrBuffer_;
};

template <class T> T* Node::CreateComponent(CreateMode mode) { return static_cast<T*>(CreateComponent(T::GetTypeStatic(), mode)); }
template <class T> T* Node::GetOrCreateComponent(CreateMode mode) { return static_cast<T*>(GetOrCreateComponent(T::GetTypeStatic(), mode)); }
template <class T> void Node::GetChildrenWithComponent(PODVector<Node*>& dest, bool recursive) const { GetChildrenWithComponent(dest, T::GetTypeStatic(), recursive); }
template <class T> T* Node::GetComponent() const { return static_cast<T*>(GetComponent(T::GetTypeStatic())); }
template <class T> void Node::GetComponents(PODVector<T*>& dest, bool recursive) const { GetComponents(reinterpret_cast<PODVector<Component*>&>(dest), T::GetTypeStatic(), recursive); }
template <class T> bool Node::HasComponent() const { return HasComponent(T::GetTypeStatic()); }

template <class T> T* Node::GetDerivedComponent() const
{
    for (Vector<SharedPtr<Component> >::ConstIterator i = components_.Begin(); i != components_.End(); ++i)
    {
        T* component = dynamic_cast<T*>(i->Get());
        if (component)
            return component;
    }
    
    return 0;
}

template <class T> void Node::GetDerivedComponents(PODVector<T*>& dest) const
{
    dest.Clear();
    
    for (Vector<SharedPtr<Component> >::ConstIterator i = components_.Begin(); i != components_.End(); ++i)
    {
        T* component = dynamic_cast<T*>(i->Get());
        if (component)
            dest.Push(component);
    }
}

}
