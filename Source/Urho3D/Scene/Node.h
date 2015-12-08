//
// Copyright (c) 2008-2015 the Urho3D project.
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

#include "../IO/VectorBuffer.h"
#include "../Math/Matrix3x4.h"
#include "../Scene/Animatable.h"

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

/// Transform space for translations and rotations.
enum TransformSpace
{
    TS_LOCAL = 0,
    TS_PARENT,
    TS_WORLD
};

/// %Scene node that may contain components and child nodes.
class URHO3D_API Node : public Animatable
{
    URHO3D_OBJECT(Node, Animatable);

    friend class Connection;

public:
    /// Construct.
    Node(Context* context);
    /// Destruct. Any child nodes are detached.
    virtual ~Node();
    /// Register object factory.
    static void RegisterObject(Context* context);

    /// Load from binary data. Return true if successful.
    virtual bool Load(Deserializer& source, bool setInstanceDefault = false);
    /// Load from XML data. Return true if successful.
    virtual bool LoadXML(const XMLElement& source, bool setInstanceDefault = false);
    /// Load from JSON data. Return true if successful.
    virtual bool LoadJSON(const JSONValue& source, bool setInstanceDefault = false);
    /// Save as binary data. Return true if successful.
    virtual bool Save(Serializer& dest) const;
    /// Save as XML data. Return true if successful.
    virtual bool SaveXML(XMLElement& dest) const;
    /// Save as JSON data. Return true if successful.
    virtual bool SaveJSON(JSONValue& dest) const;
    /// Apply attribute changes that can not be applied immediately recursively to child nodes and components.
    virtual void ApplyAttributes();

    /// Return whether should save default-valued attributes into XML. Always save node transforms for readability, even if identity.
    virtual bool SaveDefaultAttributes() const { return true; }

    /// Mark for attribute check on the next network update.
    virtual void MarkNetworkUpdate();
    /// Add a replication state that is tracking this node.
    virtual void AddReplicationState(NodeReplicationState* state);

    /// Save to an XML file. Return true if successful.
    bool SaveXML(Serializer& dest, const String& indentation = "\t") const;
    /// Save to a JSON file. Return true if successful.
    bool SaveJSON(Serializer& dest, const String& indentation = "\t") const;
    /// Set name of the scene node. Names are not required to be unique.
    void SetName(const String& name);
    /// Set position in parent space. If the scene node is on the root level (is child of the scene itself), this is same as world space.
    void SetPosition(const Vector3& position);

    /// Set position in parent space (for Urho2D).
    void SetPosition2D(const Vector2& position) { SetPosition(Vector3(position)); }

    /// Set position in parent space (for Urho2D).
    void SetPosition2D(float x, float y) { SetPosition(Vector3(x, y, 0.0f)); }

    /// Set rotation in parent space.
    void SetRotation(const Quaternion& rotation);

    /// Set rotation in parent space (for Urho2D).
    void SetRotation2D(float rotation) { SetRotation(Quaternion(rotation)); }

    /// Set forward direction in parent space. Positive Z axis equals identity rotation.
    void SetDirection(const Vector3& direction);
    /// Set uniform scale in parent space.
    void SetScale(float scale);
    /// Set scale in parent space.
    void SetScale(const Vector3& scale);

    /// Set scale in parent space (for Urho2D).
    void SetScale2D(const Vector2& scale) { SetScale(Vector3(scale, 1.0f)); }

    /// Set scale in parent space (for Urho2D).
    void SetScale2D(float x, float y) { SetScale(Vector3(x, y, 1.0f)); }

    /// Set both position and rotation in parent space as an atomic operation. This is faster than setting position and rotation separately.
    void SetTransform(const Vector3& position, const Quaternion& rotation);
    /// Set both position, rotation and uniform scale in parent space as an atomic operation.
    void SetTransform(const Vector3& position, const Quaternion& rotation, float scale);
    /// Set both position, rotation and scale in parent space as an atomic operation.
    void SetTransform(const Vector3& position, const Quaternion& rotation, const Vector3& scale);

    /// Set both position and rotation in parent space as an atomic operation (for Urho2D).
    void SetTransform2D(const Vector2& position, float rotation) { SetTransform(Vector3(position), Quaternion(rotation)); }

    /// Set both position, rotation and uniform scale in parent space as an atomic operation (for Urho2D).
    void SetTransform2D(const Vector2& position, float rotation, float scale)
    {
        SetTransform(Vector3(position), Quaternion(rotation), scale);
    }

    /// Set both position, rotation and scale in parent space as an atomic operation (for Urho2D).
    void SetTransform2D(const Vector2& position, float rotation, const Vector2& scale)
    {
        SetTransform(Vector3(position), Quaternion(rotation), Vector3(scale, 1.0f));
    }

    /// Set position in world space.
    void SetWorldPosition(const Vector3& position);

    /// Set position in world space (for Urho2D).
    void SetWorldPosition2D(const Vector2& position) { SetWorldPosition(Vector3(position)); }

    /// Set position in world space (for Urho2D).
    void SetWorldPosition2D(float x, float y) { SetWorldPosition(Vector3(x, y, 0.0f)); }

    /// Set rotation in world space.
    void SetWorldRotation(const Quaternion& rotation);

    /// Set rotation in world space (for Urho2D).
    void SetWorldRotation2D(float rotation) { SetWorldRotation(Quaternion(rotation)); }

    /// Set forward direction in world space.
    void SetWorldDirection(const Vector3& direction);
    /// Set uniform scale in world space.
    void SetWorldScale(float scale);
    /// Set scale in world space.
    void SetWorldScale(const Vector3& scale);

    /// Set scale in world space (for Urho2D).
    void SetWorldScale2D(const Vector2& scale) { SetWorldScale(Vector3(scale, 1.0f)); }

    /// Set scale in world space (for Urho2D).
    void SetWorldScale2D(float x, float y) { SetWorldScale(Vector3(x, y, 1.0f)); }

    /// Set both position and rotation in world space as an atomic operation.
    void SetWorldTransform(const Vector3& position, const Quaternion& rotation);
    /// Set both position, rotation and uniform scale in world space as an atomic operation.
    void SetWorldTransform(const Vector3& position, const Quaternion& rotation, float scale);
    /// Set both position, rotation and scale in world space as an atomic opration.
    void SetWorldTransform(const Vector3& position, const Quaternion& rotation, const Vector3& scale);

    /// Set both position and rotation in world space as an atomic operation (for Urho2D).
    void SetWorldTransform2D(const Vector2& position, float rotation)
    {
        SetWorldTransform(Vector3(position), Quaternion(rotation));
    }

    /// Set both position, rotation and uniform scale in world space as an atomic operation (for Urho2D).
    void SetWorldTransform2D(const Vector2& position, float rotation, float scale)
    {
        SetWorldTransform(Vector3(position), Quaternion(rotation), scale);
    }

    /// Set both position, rotation and scale in world space as an atomic opration (for Urho2D).
    void SetWorldTransform2D(const Vector2& position, float rotation, const Vector2& scale)
    {
        SetWorldTransform(Vector3(position), Quaternion(rotation), Vector3(scale, 1.0f));
    }

    /// Move the scene node in the chosen transform space.
    void Translate(const Vector3& delta, TransformSpace space = TS_LOCAL);

    /// Move the scene node in the chosen transform space (for Urho2D).
    void Translate2D(const Vector2& delta, TransformSpace space = TS_LOCAL) { Translate(Vector3(delta), space); }

    /// Rotate the scene node in the chosen transform space.
    void Rotate(const Quaternion& delta, TransformSpace space = TS_LOCAL);

    /// Rotate the scene node in the chosen transform space (for Urho2D).
    void Rotate2D(float delta, TransformSpace space = TS_LOCAL) { Rotate(Quaternion(delta), space); }

    /// Rotate around a point in the chosen transform space.
    void RotateAround(const Vector3& point, const Quaternion& delta, TransformSpace space = TS_LOCAL);

    /// Rotate around a point in the chosen transform space (for Urho2D).
    void RotateAround2D(const Vector2& point, float delta, TransformSpace space = TS_LOCAL)
    {
        RotateAround(Vector3(point), Quaternion(delta), space);
    }

    /// Rotate around the X axis.
    void Pitch(float angle, TransformSpace space = TS_LOCAL);
    /// Rotate around the Y axis.
    void Yaw(float angle, TransformSpace space = TS_LOCAL);
    /// Rotate around the Z axis.
    void Roll(float angle, TransformSpace space = TS_LOCAL);
    /// Look at a target position in the chosen transform space. Note that the up vector is always specified in world space. Return true if successful, or false if resulted in an illegal rotation, in which case the current rotation remains.
    bool LookAt(const Vector3& target, const Vector3& up = Vector3::UP, TransformSpace space = TS_WORLD);
    /// Modify scale in parent space uniformly.
    void Scale(float scale);
    /// Modify scale in parent space.
    void Scale(const Vector3& scale);

    /// Modify scale in parent space (for Urho2D).
    void Scale2D(const Vector2& scale) { Scale(Vector3(scale, 1.0f)); }

    /// Set enabled/disabled state without recursion. Components in a disabled node become effectively disabled regardless of their own enable/disable state.
    void SetEnabled(bool enable);
    /// Set enabled state on self and child nodes. Nodes' own enabled state is remembered (IsEnabledSelf) and can be restored.
    void SetDeepEnabled(bool enable);
    /// Reset enabled state to the node's remembered state prior to calling SetDeepEnabled.
    void ResetDeepEnabled();
    /// Set enabled state on self and child nodes. Unlike SetDeepEnabled this does not remember the nodes' own enabled state, but overwrites it.
    void SetEnabledRecursive(bool enable);
    /// Set owner connection for networking.
    void SetOwner(Connection* owner);
    /// Mark node and child nodes to need world transform recalculation. Notify listener components.
    void MarkDirty();
    /// Create a child scene node (with specified ID if provided).
    Node* CreateChild(const String& name = String::EMPTY, CreateMode mode = REPLICATED, unsigned id = 0);
    /// Add a child scene node at a specific index. If index is not explicitly specified or is greater than current children size, append the new child at the end.
    void AddChild(Node* node, unsigned index = M_MAX_UNSIGNED);
    /// Remove a child scene node.
    void RemoveChild(Node* node);
    /// Remove all child scene nodes.
    void RemoveAllChildren();
    /// Remove child scene nodes that match criteria.
    void RemoveChildren(bool removeReplicated, bool removeLocal, bool recursive);
    /// Create a component to this node (with specified ID if provided).
    Component* CreateComponent(StringHash type, CreateMode mode = REPLICATED, unsigned id = 0);
    /// Create a component to this node if it does not exist already.
    Component* GetOrCreateComponent(StringHash type, CreateMode mode = REPLICATED, unsigned id = 0);
    /// Clone a component from another node using its create mode. Return the clone if successful or null on failure.
    Component* CloneComponent(Component* component, unsigned id = 0);
    /// Clone a component from another node and specify the create mode. Return the clone if successful or null on failure.
    Component* CloneComponent(Component* component, CreateMode mode, unsigned id = 0);
    /// Remove a component from this node.
    void RemoveComponent(Component* component);
    /// Remove the first component of specific type from this node.
    void RemoveComponent(StringHash type);
    /// Remove components that match criteria.
    void RemoveComponents(bool removeReplicated, bool removeLocal);
    /// Remove all components of specific type.
    void RemoveComponents(StringHash type);
    /// Remove all components from this node.
    void RemoveAllComponents();
    /// Clone scene node, components and child nodes. Return the clone.
    Node* Clone(CreateMode mode = REPLICATED);
    /// Remove from the parent node. If no other shared pointer references exist, causes immediate deletion.
    void Remove();
    /// Set parent scene node. Retains the world transform.
    void SetParent(Node* parent);
    /// Set a user variable.
    void SetVar(StringHash key, const Variant& value);
    /// Add listener component that is notified of node being dirtied. Can either be in the same node or another.
    void AddListener(Component* component);
    /// Remove listener component.
    void RemoveListener(Component* component);
    /// Template version of creating a component.
    template <class T> T* CreateComponent(CreateMode mode = REPLICATED, unsigned id = 0);
    /// Template version of getting or creating a component.
    template <class T> T* GetOrCreateComponent(CreateMode mode = REPLICATED, unsigned id = 0);
    /// Template version of removing a component.
    template <class T> void RemoveComponent();
    /// Template version of removing all components of specific type.
    template <class T> void RemoveComponents();

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

    /// Returns the node's last own enabled state. May be different than the value returned by IsEnabled when SetDeepEnabled has been used.
    bool IsEnabledSelf() const { return enabledPrev_; }

    /// Return owner connection in networking.
    Connection* GetOwner() const { return owner_; }

    /// Return position in parent space.
    const Vector3& GetPosition() const { return position_; }

    /// Return position in parent space (for Urho2D).
    Vector2 GetPosition2D() const { return Vector2(position_.x_, position_.y_); }

    /// Return rotation in parent space.
    const Quaternion& GetRotation() const { return rotation_; }

    /// Return rotation in parent space (for Urho2D).
    float GetRotation2D() const { return rotation_.RollAngle(); }

    /// Return forward direction in parent space. Positive Z axis equals identity rotation.
    Vector3 GetDirection() const { return rotation_ * Vector3::FORWARD; }

    /// Return up direction in parent space. Positive Y axis equals identity rotation.
    Vector3 GetUp() const { return rotation_ * Vector3::UP; }

    /// Return right direction in parent space. Positive X axis equals identity rotation.
    Vector3 GetRight() const { return rotation_ * Vector3::RIGHT; }

    /// Return scale in parent space.
    const Vector3& GetScale() const { return scale_; }

    /// Return scale in parent space (for Urho2D).
    Vector2 GetScale2D() const { return Vector2(scale_.x_, scale_.y_); }

    /// Return parent space transform matrix.
    Matrix3x4 GetTransform() const { return Matrix3x4(position_, rotation_, scale_); }

    /// Return position in world space.
    Vector3 GetWorldPosition() const
    {
        if (dirty_)
            UpdateWorldTransform();

        return worldTransform_.Translation();
    }

    /// Return position in world space (for Urho2D).
    Vector2 GetWorldPosition2D() const
    {
        Vector3 worldPosition = GetWorldPosition();
        return Vector2(worldPosition.x_, worldPosition.y_);
    }

    /// Return rotation in world space.
    Quaternion GetWorldRotation() const
    {
        if (dirty_)
            UpdateWorldTransform();

        return worldRotation_;
    }

    /// Return rotation in world space (for Urho2D).
    float GetWorldRotation2D() const
    {
        return GetWorldRotation().RollAngle();
    }

    /// Return direction in world space.
    Vector3 GetWorldDirection() const
    {
        if (dirty_)
            UpdateWorldTransform();

        return worldRotation_ * Vector3::FORWARD;
    }

    /// Return node's up vector in world space.
    Vector3 GetWorldUp() const
    {
        if (dirty_)
            UpdateWorldTransform();

        return worldRotation_ * Vector3::UP;
    }

    /// Return node's right vector in world space.
    Vector3 GetWorldRight() const
    {
        if (dirty_)
            UpdateWorldTransform();

        return worldRotation_ * Vector3::RIGHT;
    }

    /// Return scale in world space.
    Vector3 GetWorldScale() const
    {
        if (dirty_)
            UpdateWorldTransform();

        return worldTransform_.Scale();
    }

    /// Return scale in world space (for Urho2D).
    Vector2 GetWorldScale2D() const
    {
        Vector3 worldScale = GetWorldScale();
        return Vector2(worldScale.x_, worldScale.y_);
    }

    /// Return world space transform matrix.
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
    /// Convert a local space position or rotation to world space (for Urho2D).
    Vector2 LocalToWorld2D(const Vector2& vector) const;
    /// Convert a world space position to local space.
    Vector3 WorldToLocal(const Vector3& position) const;
    /// Convert a world space position or rotation to local space.
    Vector3 WorldToLocal(const Vector4& vector) const;
    /// Convert a world space position or rotation to local space (for Urho2D).
    Vector2 WorldToLocal2D(const Vector2& vector) const;

    /// Return whether transform has changed and world transform needs recalculation.
    bool IsDirty() const { return dirty_; }

    /// Return number of child scene nodes.
    unsigned GetNumChildren(bool recursive = false) const;

    /// Return immediate child scene nodes.
    const Vector<SharedPtr<Node> >& GetChildren() const { return children_; }

    /// Return child scene nodes, optionally recursive.
    void GetChildren(PODVector<Node*>& dest, bool recursive = false) const;
    /// Return child scene nodes with a specific component.
    void GetChildrenWithComponent(PODVector<Node*>& dest, StringHash type, bool recursive = false) const;
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
    void GetComponents(PODVector<Component*>& dest, StringHash type, bool recursive = false) const;
    /// Return component by type. If there are several, returns the first.
    Component* GetComponent(StringHash type, bool recursive = false) const;
    /// Return component in parent node. If there are several, returns the first. May optional traverse up to the root node.
    Component* GetParentComponent(StringHash type, bool fullTraversal = false) const;
    /// Return whether has a specific component.
    bool HasComponent(StringHash type) const;

    /// Return listener components.
    const Vector<WeakPtr<Component> > GetListeners() const { return listeners_; }

    /// Return a user variable.
    const Variant& GetVar(StringHash key) const;

    /// Return all user variables.
    const VariantMap& GetVars() const { return vars_; }

    /// Return first component derived from class.
    template <class T> T* GetDerivedComponent(bool recursive = false) const;
    /// Return first component derived from class in the parent node, or if fully traversing then the first node up the tree with one.
    template <class T> T* GetParentDerivedComponent(bool fullTraversal = false) const;
    /// Return components derived from class.
    template <class T> void GetDerivedComponents(PODVector<T*>& dest, bool recursive = false, bool clearVector = true) const;
    /// Template version of returning child nodes with a specific component.
    template <class T> void GetChildrenWithComponent(PODVector<Node*>& dest, bool recursive = false) const;
    /// Template version of returning a component by type.
    template <class T> T* GetComponent(bool recursive = false) const;
    /// Template version of returning a parent's component by type.
    template <class T> T* GetParentComponent(bool fullTraversal = false) const;
    /// Template version of returning all components of type.
    template <class T> void GetComponents(PODVector<T*>& dest, bool recursive = false) const;
    /// Template version of checking whether has a specific component.
    template <class T> bool HasComponent() const;

    /// Set ID. Called by Scene.
    void SetID(unsigned id);
    /// Set scene. Called by Scene.
    void SetScene(Scene* scene);
    /// Reset scene, ID and owner. Called by Scene.
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
    bool Load(Deserializer& source, SceneResolver& resolver, bool loadChildren = true, bool rewriteIDs = false,
        CreateMode mode = REPLICATED);
    /// Load components from XML data and optionally load child nodes.
    bool LoadXML(const XMLElement& source, SceneResolver& resolver, bool loadChildren = true, bool rewriteIDs = false,
        CreateMode mode = REPLICATED);
    /// Load components from XML data and optionally load child nodes.
    bool LoadJSON(const JSONValue& source, SceneResolver& resolver, bool loadChildren = true, bool rewriteIDs = false,
        CreateMode mode = REPLICATED);
    /// Return the depended on nodes to order network updates.
    const PODVector<Node*>& GetDependencyNodes() const { return dependencyNodes_; }

    /// Prepare network update by comparing attributes and marking replication states dirty as necessary.
    void PrepareNetworkUpdate();
    /// Clean up all references to a network connection that is about to be removed.
    void CleanupConnection(Connection* connection);
    /// Mark node dirty in scene replication states.
    void MarkReplicationDirty();
    /// Create a child node with specific ID.
    Node* CreateChild(unsigned id, CreateMode mode);
    /// Add a pre-created component.
    void AddComponent(Component* component, unsigned id, CreateMode mode);
    /// Calculate number of non-temporary child nodes.
    unsigned GetNumPersistentChildren() const;
    /// Calculate number of non-temporary components.
    unsigned GetNumPersistentComponents() const;

    /// Set position in parent space silently without marking the node & child nodes dirty. Used by animation code.
    void SetPositionSilent(const Vector3& position) { position_ = position; }

    /// Set position in parent space silently without marking the node & child nodes dirty. Used by animation code.
    void SetRotationSilent(const Quaternion& rotation) { rotation_ = rotation; }

    /// Set scale in parent space silently without marking the node & child nodes dirty. Used by animation code.
    void SetScaleSilent(const Vector3& scale) { scale_ = scale; }

    /// Set local transform silently without marking the node & child nodes dirty. Used by animation code.
    void SetTransformSilent(const Vector3& position, const Quaternion& rotation, const Vector3& scale);

protected:
    /// Handle attribute animation added.
    virtual void OnAttributeAnimationAdded();
    /// Handle attribute animation removed.
    virtual void OnAttributeAnimationRemoved();
    /// Find target of an attribute animation from object hierarchy by name.
    virtual Animatable* FindAttributeAnimationTarget(const String& name, String& outName);

    /// Network update queued flag.
    bool networkUpdate_;
    /// User variables.
    VariantMap vars_;

private:
    /// Set enabled/disabled state with optional recursion. Optionally affect the remembered enable state.
    void SetEnabled(bool enable, bool recursive, bool storeSelf);
    /// Create component, allowing UnknownComponent if actual type is not supported. Leave typeName empty if not known.
    Component* SafeCreateComponent(const String& typeName, StringHash type, CreateMode mode, unsigned id);
    /// Recalculate the world transform.
    void UpdateWorldTransform() const;
    /// Remove child node by iterator.
    void RemoveChild(Vector<SharedPtr<Node> >::Iterator i);
    /// Return child nodes recursively.
    void GetChildrenRecursive(PODVector<Node*>& dest) const;
    /// Return child nodes with a specific component recursively.
    void GetChildrenWithComponentRecursive(PODVector<Node*>& dest, StringHash type) const;
    /// Return specific components recursively.
    void GetComponentsRecursive(PODVector<Component*>& dest, StringHash type) const;
    /// Clone node recursively.
    Node* CloneRecursive(Node* parent, SceneResolver& resolver, CreateMode mode);
    /// Remove a component from this node with the specified iterator.
    void RemoveComponent(Vector<SharedPtr<Component> >::Iterator i);
    /// Handle attribute animation update event.
    void HandleAttributeAnimationUpdate(StringHash eventType, VariantMap& eventData);

    /// World-space transform matrix.
    mutable Matrix3x4 worldTransform_;
    /// World transform needs update flag.
    mutable bool dirty_;
    /// Enabled flag.
    bool enabled_;
    /// Last SetEnabled flag before any SetDeepEnabled.
    bool enabledPrev_;
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
    /// World-space rotation.
    mutable Quaternion worldRotation_;
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

template <class T> T* Node::CreateComponent(CreateMode mode, unsigned id)
{
    return static_cast<T*>(CreateComponent(T::GetTypeStatic(), mode, id));
}

template <class T> T* Node::GetOrCreateComponent(CreateMode mode, unsigned id)
{
    return static_cast<T*>(GetOrCreateComponent(T::GetTypeStatic(), mode, id));
}

template <class T> void Node::RemoveComponent() { RemoveComponent(T::GetTypeStatic()); }

template <class T> void Node::RemoveComponents() { RemoveComponents(T::GetTypeStatic()); }

template <class T> void Node::GetChildrenWithComponent(PODVector<Node*>& dest, bool recursive) const
{
    GetChildrenWithComponent(dest, T::GetTypeStatic(), recursive);
}

template <class T> T* Node::GetComponent(bool recursive) const { return static_cast<T*>(GetComponent(T::GetTypeStatic(), recursive)); }

template <class T> T* Node::GetParentComponent(bool fullTraversal) const { return static_cast<T*>(GetParentComponent(T::GetTypeStatic(), fullTraversal)); }

template <class T> void Node::GetComponents(PODVector<T*>& dest, bool recursive) const
{
    GetComponents(reinterpret_cast<PODVector<Component*>&>(dest), T::GetTypeStatic(), recursive);
}

template <class T> bool Node::HasComponent() const { return HasComponent(T::GetTypeStatic()); }

template <class T> T* Node::GetDerivedComponent(bool recursive) const
{
    for (Vector<SharedPtr<Component> >::ConstIterator i = components_.Begin(); i != components_.End(); ++i)
    {
        T* component = dynamic_cast<T*>(i->Get());
        if (component)
            return component;
    }

    if (recursive)
    {
        for (Vector<SharedPtr<Node> >::ConstIterator i = children_.Begin(); i != children_.End(); ++i)
        {
            T* component = (*i)->GetDerivedComponent<T>(true);
            if (component)
                return component;
        }
    }

    return 0;
}

template <class T> T* Node::GetParentDerivedComponent(bool fullTraversal) const
{
    Node* current = GetParent();
    while (current)
    {
        T* soughtComponent = current->GetDerivedComponent<T>();
        if (soughtComponent)
            return soughtComponent;

        if (fullTraversal)
            current = current->GetParent();
        else
            break;
    }
    return 0;
}

template <class T> void Node::GetDerivedComponents(PODVector<T*>& dest, bool recursive, bool clearVector) const
{
    if (clearVector)
        dest.Clear();

    for (Vector<SharedPtr<Component> >::ConstIterator i = components_.Begin(); i != components_.End(); ++i)
    {
        T* component = dynamic_cast<T*>(i->Get());
        if (component)
            dest.Push(component);
    }

    if (recursive)
    {
        for (Vector<SharedPtr<Node> >::ConstIterator i = children_.Begin(); i != children_.End(); ++i)
            (*i)->GetDerivedComponents<T>(dest, true, false);
    }
}

}
