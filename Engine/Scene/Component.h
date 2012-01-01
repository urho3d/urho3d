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

#pragma once

#include "Matrix3x4.h"
#include "Serializable.h"

class Node;

/// Base class for components. Components can be created to scene nodes.
class Component : public Serializable
{
    OBJECT(Component);
    
    friend class Node;
    friend class Scene;
    
public:
    /// Construct.
    Component(Context* context);
    /// Destruct.
    virtual ~Component();
    
    /// Save as binary data. Return true if successful.
    virtual bool Save(Serializer& dest);
    /// Save as XML data. Return true if successful.
    virtual bool SaveXML(XMLElement& dest);
    /// Handle scene node being assigned at creation.
    virtual void OnNodeSet(Node* node) {};
    /// Handle scene node transform dirtied.
    virtual void OnMarkedDirty(Node* node) {};
    /// Return the depended on nodes to order network updates.
    virtual void GetDependencyNodes(PODVector<Node*>& dest) {};
    
    /// Remove from the scene node. If no other shared pointer references exist, causes immediate deletion.
    void Remove();
    
    /// Return ID.
    unsigned GetID() const { return id_; }
    /// Get scene node.
    Node* GetNode() const { return node_; }
    
    /// Return parent node's world transform.
    const Matrix3x4& GetWorldTransform() const;
    /// Return parent node's world position.
    Vector3 GetWorldPosition() const { return GetWorldTransform().Translation(); }
    /// Return parent node's world rotation.
    Quaternion GetWorldRotation() const { return GetWorldTransform().Rotation(); }
    /// Return parent node's world scale.
    Vector3 GetWorldScale() const { return GetWorldTransform().Scale(); }
    
    /// Return components in the same scene node by type.
    void GetComponents(PODVector<Component*>& dest, ShortStringHash type) const;
    /// Return component in the same scene node by type. If there are several, returns the first.
    Component* GetComponent(ShortStringHash type) const;
    /// Template version of returning a component in the same scene node by type.
    template <class T> T* GetComponent() const;
    /// Template version of returning components in the same scene node by type.
    template <class T> void GetComponents(PODVector<T*>& dest) const;
    
protected:
    /// %Set ID. Called by Scene.
    void SetID(unsigned id);
    /// %Set scene node. Called by Node when creating the component.
    void SetNode(Node* node);
    
    /// Unique ID within the scene.
    unsigned id_;
    /// Scene node.
    Node* node_;
};

template <class T> T* Component::GetComponent() const { return static_cast<T*>(GetComponent(T::GetTypeStatic())); }
template <class T> void Component::GetComponents(PODVector<T*>& dest) const { GetComponents(reinterpret_cast<PODVector<Component*>&>(dest), T::GetTypeStatic()); }
