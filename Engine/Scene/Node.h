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

#ifndef SCENE_NODE_H
#define SCENE_NODE_H

#include "Component.h"
#include "Matrix4x3.h"
#include "SharedPtr.h"

#include <vector>

class Entity;

static const unsigned NODE_NONE = 0x0;
static const unsigned NODE_NODE = 0x1;
static const unsigned NODE_CAMERA = 0x2;
static const unsigned NODE_BONE = 0x4;
static const unsigned NODE_GEOMETRY = 0x8;
static const unsigned NODE_LIGHT = 0x10;
static const unsigned NODE_STATICMODEL = 0x20;
static const unsigned NODE_ANIMATEDMODEL = 0x40;
static const unsigned NODE_INSTANCEDMODEL = 0x80;
static const unsigned NODE_BILLBOARDSET = 0x100;
static const unsigned NODE_CUSTOMOBJECT = 0x200;
static const unsigned NODE_SKYBOX = 0x400;
static const unsigned NODE_ZONE = 0x800;
static const unsigned NODE_RIGIDBODY = 0x1000;
static const unsigned NODE_POSITIONALCHANNEL = 0x2000;
static const unsigned NODE_ANY = 0xffffffff;
static const unsigned NODE_PREDEFINEDFLAGS = 0x0000ffff;
static const unsigned NODE_CUSTOMFLAGS = 0xffff0000;

static const unsigned INTERP_NONE = 0x0;
static const unsigned INTERP_POS = 0x1;
static const unsigned INTERP_ROT = 0x2;
static const unsigned INTERP_SCALE = 0x4;
static const unsigned INTERP_WEIGHT = 0x8;
static const unsigned INTERP_TIME = 0x10;

//! Base class for scene nodes
class Node : public Component
{
    DEFINE_TYPE(Node);
    
public:
    //! Construct with name
    Node(const std::string& name = std::string());
    //! Destruct. Any child nodes are detached
    virtual ~Node();
    
    //! Write component state to a stream
    virtual void save(Serializer& dest);
    //! Read component state from a stream
    virtual void load(Deserializer& source, ResourceCache* cache);
    //! Write component state to an XML element
    virtual void saveXML(XMLElement& dest);
    //! Read component state from an XML element
    virtual void loadXML(const XMLElement& source, ResourceCache* cache);
    //! Resolve component references after loading
    virtual void postLoad(ResourceCache* cache);
    //! Write a network update
    virtual bool writeNetUpdate(Serializer& dest, Serializer& destRevision, Deserializer& baseRevision, const NetUpdateInfo& info);
    //! Read a network update
    virtual void readNetUpdate(Deserializer& source, ResourceCache* cache, const NetUpdateInfo& info);
    //! Resolve component references after a network update
    virtual void postNetUpdate(ResourceCache* cache);
    //! Perform client-side visual smoothing
    virtual void interpolate(bool snapToEnd = false);
    //! Return component references
    virtual void getComponentRefs(std::vector<ComponentRef>& dest);
    
    //! Set position
    void setPosition(const Vector3& position);
    //! Set rotation
    void setRotation(const Quaternion& rotation);
    //! Set direction. Positive Z equals identity
    void setDirection(const Vector3& direction);
    //! Set uniform scale
    void setScale(float scale);
    //! Set scale
    void setScale(const Vector3& scale);
    //! Set transform
    void setTransform(const Vector3& position, const Quaternion& rotation);
    //! Set transform
    void setTransform(const Vector3& position, const Quaternion& rotation, float scale);
    //! Set transform
    void setTransform(const Vector3& position, const Quaternion& rotation, const Vector3& scale);
    //! Move the scene node
    void translate(const Vector3& delta);
    //! Move the scene node relative to its rotation
    void translateRelative(const Vector3& delta);
    //! Rotate the scene node
    void rotate(const Quaternion& delta, bool fixedAxis = false);
    //! Rotate around the X axis
    void pitch(float angle, bool fixedAxis = false);
    //! Rotate around the Y axis
    void yaw(float angle, bool fixedAxis = false);
    //! Rotate around the Z axis
    void roll(float angle, bool fixedAxis = false);
    //! Modify scale uniformly
    void scale(float scale);
    //! Modify scale
    void scale(const Vector3& scale);
    //! Set custom node flags (high 16 bits.) For editing use only, these will not be saved or replicated
    void setNodeFlags(unsigned flags);
    //! Add a child scene node
    void addChild(Node* node);
    //! Remove a child scene node. Optionally set its transform to match the last world position it was in
    void removeChild(Node* node, bool setWorldTransform = false);
    //! Remove all child scene nodes
    void removeAllChildren(bool setWorldTransform = false);
    
    //! Return position
    const Vector3& getPosition() const { return mPosition; }
    //! Return rotation
    const Quaternion& getRotation() const { return mRotation; }
    //! Return direction. Identity rotation equals positive Z
    Vector3 getDirection() const { return mRotation * Vector3::sForward; }
    //! Return scale
    const Vector3& getScale() const { return mScale; }
    
    //! Return world-space position
    const Vector3& getWorldPosition()
    {
        if (mDirty)
            updateWorldPosition();
        
        return mWorldPosition;
    }
    
    //! Return world-space rotation
    const Quaternion& getWorldRotation()
    {
        if (mDirty)
            updateWorldPosition();
        
        return mWorldRotation;
    }
    
    //! Return world-space direction
    Vector3 getWorldDirection()
    {
        if (mDirty)
            updateWorldPosition();
        
        return mWorldRotation * Vector3::sForward;
    }
    
    //! Return world-space scale
    const Vector3& getWorldScale()
    {
        if (mDirty)
            updateWorldPosition();
        
        return mWorldScale;
    }
    
    //! Return world-space transform matrix
    const Matrix4x3& getWorldTransform()
    {
        if (mDirty)
            updateWorldPosition();
        
        if (mWorldTransformDirty)
        {
            mWorldTransform.define(mWorldPosition, mWorldRotation, mWorldScale);
            mWorldTransformDirty = false;
        }
        
        return mWorldTransform;
    }
    
    //! Return node flags
    unsigned getNodeFlags() const { return mNodeFlags; }
    //! Return parent scene node
    Node* getParent() const { return mParent; }
    //! Return whether transform has changed and world transform needs recalculation
    bool isDirty() const { return mDirty; }
    //! Return child scene nodes
    std::vector<Node*> getChildren(unsigned nodeFlags = NODE_ANY, bool recursive = false) const;
    //! Return number of child scene nodes
    unsigned getNumChildren(bool recursive = false) const;
    //! Return child scene node by index
    Node* getChild(unsigned index) const;
    //! Return child scene node by name
    Node* getChild(const std::string& name, bool recursive = false) const;
    //! Return child scene node by name hash
    Node* getChild(StringHash nameHash, bool recursive = false) const;
    
protected:
    //! Construct with node flags and name
    Node(unsigned flags, const std::string& name = std::string());
    //! Mark node and child nodes to need world transform recalculation
    void markDirty();
    //! Return transform for network replication (return world transform is parent scene node is not replicated)
    void getNetTransform(Vector3& position, Quaternion& rotation, Vector3& scale, ComponentRef& parentRef, const NetUpdateInfo& info);
    
    //! Transform has changed. Perform subclass-specific operations
    virtual void onMarkedDirty() {}
    
    //! Parent scene node
    Node* mParent;
    //! Child scene nodes
    std::vector<SharedPtr<Node> > mChildren;
    //! Parent scene node component reference
    ComponentRef mParentRef;
    
    //! Visual smoothing target position
    Vector3 mInterpolationPosition;
    //! Visual smoothing target rotation
    Quaternion mInterpolationRotation;
    //! Visual smoothing target scale
    Vector3 mInterpolationScale;
    //! Currently active visual smoothings
    unsigned char mInterpolationFlags;
    
private:
    //! Recalculate the world transform
    void updateWorldPosition();
    //! Remove child node by iterator
    void removeChild(std::vector<SharedPtr<Node> >::iterator i, bool setWorldTransform = false);
    //! Return child nodes recursively
    void getChildrenRecursive(unsigned nodeFlags, std::vector<Node*>& dest) const;
    
    //! Node flags
    unsigned mNodeFlags;
    //! Position
    Vector3 mPosition;
    //! Rotation
    Quaternion mRotation;
    //! Scale
    Vector3 mScale;
    //! World-space position
    Vector3 mWorldPosition;
    //! World-space rotation
    Quaternion mWorldRotation;
    //! World-space scale
    Vector3 mWorldScale;
    //! World-space transform matrix
    Matrix4x3 mWorldTransform;
    //! World transform needs update flag
    bool mDirty;
    //! World transform matrix needs update flag
    bool mWorldTransformDirty;
    //! Consecutive rotation count, for rotation renormalization
    unsigned mRotateCount;
};

#endif // SCENE_NODE_H
