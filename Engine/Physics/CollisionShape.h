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

#include "BoundingBox.h"
#include "ArrayPtr.h"
#include "Component.h"
#include "Quaternion.h"

class DebugRenderer;
class Geometry;
class Model;
class PhysicsWorld;

class btCollisionShape;

/// Base class for physics collision shape components.
class CollisionShape : public Component
{
    OBJECT(CollisionShape);
    
public:
    /// Construct.
    CollisionShape(Context* context);
    /// Destruct. Free the geometry data and clean up unused data from the geometry data cache.
    virtual ~CollisionShape();
    
    /// Handle attribute write access.
    virtual void OnSetAttribute(const AttributeInfo& attr, const Variant& src);
    /// Apply attribute changes that can not be applied immediately. Called after scene load or a network update.
    virtual void ApplyAttributes();
    /// Create and return a collision shape instance, subject to scene node scaling. Called by RigidBody.
    virtual btCollisionShape* CreateCollisionShape() = 0;
    
    /// %Set offset position.
    void SetPosition(const Vector3& position);
    /// %Set rotation.
    void SetRotation(const Quaternion& rotation);
    /// %Set offset transform.
    void SetTransform(const Vector3& position, const Quaternion& rotation);
    
    /// Return physics world.
    PhysicsWorld* GetPhysicsWorld() const { return physicsWorld_; }
    /// Return offset position.
    const Vector3& GetPosition() const { return position_; }
    /// Return rotation.
    const Quaternion& GetRotation() const { return rotation_; }
    
    /// Add debug geometry to the debug renderer.
    void DrawDebugGeometry(DebugRenderer* debug, bool depthTest);
    
protected:
    /// Handle node being assigned.
    virtual void OnNodeSet(Node* node);
    /// Notify the RigidBody of changed collision shape transform.
    void NotifyRigidBody();
    
    /// Physics world.
    WeakPtr<PhysicsWorld> physicsWorld_;
    /// Offset position.
    Vector3 position_;
    /// Offset rotation.
    Quaternion rotation_;
    /// Collision shape dirty flag.
    bool dirty_;
};
