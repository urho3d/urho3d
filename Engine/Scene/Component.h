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
#include "Node.h"

/// Base class for components. Components can be added to scene nodes
class Component : public Serializable
{
    OBJECT(Component);
    
    friend class Node;
    friend class Renderer;
    friend class Scene;
    
public:
    /// Construct
    Component(Context* context);
    /// Destruct
    virtual ~Component();
    
    /// Handle scene node being assigned at creation
    virtual void OnNodeSet(Node* node) {};
    /// Handle scene node transform dirtied
    virtual void OnMarkedDirty(Node* node) {};
    
    /// Remove from the scene node. If no other shared pointer references exist, causes immediate deletion
    void Remove();
    
    /// Return ID
    unsigned GetID() const { return id_; }
    /// Get scene node
    Node* GetNode() const { return node_; }
    
    /// Return parent node's world transform
    const Matrix4x3& GetWorldTransform() const
    {
        if (node_)
            return node_->GetWorldTransform();
        else
            return Matrix4x3::IDENTITY;
    }
    
    /// Return parent node's world position
    Vector3 GetWorldPosition() const
    {
        return GetWorldTransform().GetTranslation();
    }
    
    /// Return parent node's world rotation
    Quaternion GetWorldRotation() const
    {
        return GetWorldTransform().GetRotation();
    }
    
    /// Return parent node's world scale
    Vector3 GetWorldScale() const
    {
        return GetWorldTransform().GetScale();
    }
    
    /// Return components in the same scene node by type
    void GetComponents(PODVector<Component*>& dest, ShortStringHash type) const;
    /// Return component in the same scene node by type. The optional index allows to specify which component, if there are several
    Component* GetComponent(ShortStringHash type, unsigned index = 0) const;
    /// Return whether the same scene node has a specific component
    bool HasComponent(ShortStringHash type) const;
    /// Template version of returning a component in the same scene node by type
    template <class T> T* GetComponent(unsigned index = 0) const;
    /// Template version of returning components in the same scene node by type
    template <class T> void GetComponents(PODVector<T*>& dest) const;
    
protected:
    /// Set ID. Called by Scene
    void SetID(unsigned id);
    /// Set scene node. Called by Node when creating the component
    void SetNode(Node* node);
    
    /// Unique ID within the scene
    unsigned id_;
    /// Scene node
    Node* node_;
};

template <class T> T* Component::GetComponent(unsigned index) const
{
    return static_cast<T*>(GetComponent(T::GetTypeStatic(), index));
}

template <class T> void Component::GetComponents(PODVector<T*>& dest) const
{
    GetComponents(reinterpret_cast<PODVector<Component*>&>(dest), T::GetTypeStatic());
}
