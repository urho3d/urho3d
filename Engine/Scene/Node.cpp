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
#include "Node.h"
#include "ReplicationUtils.h"
#include "Scene.h"
#include "StringUtils.h"

#include "DebugNew.h"

// Normalize rotation quaternion after this many incremental updates to prevent distortion
static const unsigned NORMALIZE_ROTATION_EVERY = 32;

Node::Node(const std::string& name) :
    Component(name),
    mParent(0),
    mInterpolationFlags(INTERP_NONE),
    mNodeFlags(NODE_NODE),
    mDirty(false),
    mWorldTransformDirty(false),
    mPosition(Vector3::sZero),
    mRotation(Quaternion::sIdentity),
    mScale(Vector3::sUnity),
    mWorldPosition(Vector3::sZero),
    mWorldRotation(Quaternion::sIdentity),
    mWorldScale(Vector3::sUnity),
    mWorldTransform(Matrix4x3::sIdentity),
    mRotateCount(0)
{
}

Node::Node(unsigned flags, const std::string& name) :
    Component(name),
    mParent(0),
    mNodeFlags(flags),
    mDirty(true),
    mWorldTransformDirty(true),
    mPosition(Vector3::sZero),
    mRotation(Quaternion::sIdentity),
    mScale(Vector3::sUnity),
    mRotateCount(0),
    mInterpolationFlags(0)
{
}

Node::~Node()
{
    // Remove all children, and set world transform if they are refcounted elsewhere
    while (mChildren.size())
    {
        std::vector<SharedPtr<Node> >::iterator i = mChildren.end() - 1;
        if (i->getRefCount() > 1)
            removeChild(i, true);
        else
            removeChild(i, false);
    }
}

void Node::save(Serializer& dest)
{
    // Write Component properties
    Component::save(dest);
    
    // Write transform (interpolation transform & flags for network proxies)
    if (!isProxy())
    {
        dest.writeVector3(mPosition);
        dest.writeQuaternion(mRotation);
        dest.writeVector3(mScale);
    }
    else
    {
        dest.writeVector3(mInterpolationPosition);
        dest.writeQuaternion(mInterpolationRotation);
        dest.writeVector3(mInterpolationScale);
        dest.writeUByte(mInterpolationFlags);
    }
    
    // Write parent node reference
    ComponentRef parentRef(mParent);
    parentRef.write(dest);
}

void Node::load(Deserializer& source, ResourceCache* cache)
{
    // Read Component properties
    Component::load(source, cache);
    
    // Read transform (interpolation transform & flags for network proxies)
    if (!isProxy())
    {
        mPosition = source.readVector3();
        mRotation = source.readQuaternion();
        mScale = source.readVector3();
    }
    else
    {
        mInterpolationPosition = source.readVector3();
        mInterpolationRotation = source.readQuaternion();
        mInterpolationScale = source.readVector3();
        mInterpolationFlags = source.readUByte();
    }
    
    // Read parent node reference
    mParentRef.read(source);
    
    markDirty();
}

void Node::saveXML(XMLElement& dest)
{
    // Write Component properties
    Component::saveXML(dest);
    
    // Write transform
    XMLElement transformElem = dest.createChildElement("transform");
    transformElem.setVector3("pos", mPosition);
    transformElem.setQuaternion("rot", mRotation);
    transformElem.setVector3("scale", mScale);
    
    // Write parent node reference
    ComponentRef parentRef(mParent, true);
    if (parentRef.mEntityID)
    {
        XMLElement parentElem = dest.createChildElement("parent");
        parentRef.writeXML(parentElem);
    }
}

void Node::loadXML(const XMLElement& source, ResourceCache* cache)
{
    // Read Component properties
    Component::loadXML(source, cache);
    
    // Read transform
    XMLElement transformElem = source.getChildElement("transform");
    mPosition = transformElem.getVector3("pos");
    mRotation = transformElem.getQuaternion("rot");
    mScale = transformElem.getVector3("scale");
    
    // Read parent node reference
    if (source.hasChildElement("parent"))
    {
        XMLElement parentElem = source.getChildElement("parent");
        mParentRef.readXML(parentElem);
    }
    else
        mParentRef = ComponentRef();
    
    markDirty();
}


void Node::postLoad(ResourceCache* cache)
{
    if (mParentRef.mDirty)
    {
        Node* parent = static_cast<Node*>(mEntity->getScene()->getComponent(mParentRef));
        if (parent)
            parent->addChild(this);
        mParentRef.mDirty = false;
    }
}

bool Node::writeNetUpdate(Serializer& dest, Serializer& destRevision, Deserializer& baseRevision, const NetUpdateInfo& info)
{
    // Use possibly modified transform in case the parent component is not to be replicated
    Vector3 position;
    Quaternion rotation;
    Vector3 scale;
    ComponentRef parentRef;
    getNetTransform(position, rotation, scale, parentRef, info);
    
    // Build bitmask of changed properties
    unsigned char bits = 0;
    checkVector3(position, Vector3::sZero, baseRevision, bits, 1);
    checkQuaternion(rotation, Quaternion::sIdentity, baseRevision, bits, 2);
    checkVector3(scale, Vector3::sUnity, baseRevision, bits, 4);
    checkComponentRef(parentRef, ComponentRef(), baseRevision, bits, 8);
    
    // Update replication state fully, and network stream by delta
    dest.writeUByte(bits);
    writeVector3Delta(position, dest, destRevision, bits & 1);
    writePackedQuaternionDelta(rotation, dest, destRevision, bits & 2);
    writeVector3Delta(scale, dest, destRevision, bits & 4);
    writeComponentRefDelta(parentRef, dest, destRevision, bits & 8);
    
    return bits != 0;
}

void Node::readNetUpdate(Deserializer& source, ResourceCache* cache, const NetUpdateInfo& info)
{
    unsigned char bits = source.readUByte();
    // Interpolate if just position/rotation/scale changes, snap if parent changes
    bool interpolate = (bits & 7) && (!(bits & 8));
    if (!interpolate)
    {
        if (bits & 1)
            setPosition(source.readVector3());
        if (bits & 2)
            setRotation(source.readPackedQuaternion());
        if (bits & 4)
            setScale(source.readVector3());
    }
    else
    {
        if (bits & 1)
        {
            mInterpolationPosition = source.readVector3();
            mInterpolationFlags |= INTERP_POS;
        }
        if (bits & 2)
        {
            mInterpolationRotation = source.readPackedQuaternion();
            mInterpolationFlags |= INTERP_ROT;
        }
        if (bits & 4)
        {
            mInterpolationScale = source.readVector3();
            mInterpolationFlags |= INTERP_SCALE;
        }
    }
    
    readComponentRefDelta(mParentRef, source, bits & 8);
    
    if (bits & 7)
        markDirty();
}

void Node::postNetUpdate(ResourceCache* cache)
{
    // This is the same as in file deserialization: update parent if the ref is dirty
    postLoad(cache);
}

void Node::interpolate(bool snapToEnd)
{
    if (!mInterpolationFlags)
        return;
    
    if (!snapToEnd)
    {
        Scene* scene = mEntity->getScene();
        float t = scene->getInterpolationLerpFactor();
        
        if (mInterpolationFlags & INTERP_POS)
        {
            // If position snaps, snap everything to the end
            float delta = (mPosition - mInterpolationPosition).getLengthSquared();
            if (delta > scene->getInterpolationSnapThresholdSquared())
                t = 1.0f;
            
            if (delta < M_EPSILON)
            {
                mPosition = mInterpolationPosition;
                mInterpolationFlags &= ~INTERP_POS;
            }
            else
                mPosition = mPosition.lerp(mInterpolationPosition, t);
        }
        if (mInterpolationFlags & INTERP_ROT)
        {
            float delta = (mRotation - mInterpolationRotation).getLengthSquared();
            if (delta < M_EPSILON)
            {
                mRotation = mInterpolationRotation;
                mInterpolationFlags &= ~INTERP_ROT;
            }
            else
                mRotation = mRotation.slerp(mInterpolationRotation, t);
        }
        if (mInterpolationFlags & INTERP_SCALE)
        {
            float delta = (mScale - mInterpolationScale).getLengthSquared();
            if (delta < M_EPSILON)
            {
                mScale = mInterpolationScale;
                mInterpolationFlags &= ~INTERP_SCALE;
            }
            else
                mScale = mScale.lerp(mInterpolationScale, t);
        }
    }
    else
    {
        if (mInterpolationFlags & INTERP_POS)
            mPosition = mInterpolationPosition;
        if (mInterpolationFlags & INTERP_ROT)
            mRotation = mInterpolationRotation;
        if (mInterpolationFlags & INTERP_SCALE)
            mScale = mInterpolationScale;
        mInterpolationFlags = INTERP_NONE;
    }
    
    markDirty();
}

void Node::getComponentRefs(std::vector<ComponentRef>& dest)
{
    if (mParent)
        dest.push_back(ComponentRef(mParent));
}

void Node::setPosition(const Vector3& position)
{
    mPosition = position;
    mInterpolationFlags &= ~INTERP_POS;
    
    if (!mDirty)
        markDirty();
}

void Node::setRotation(const Quaternion& rotation)
{
    mRotation = rotation;
    mRotateCount = 0;
    mInterpolationFlags &= ~INTERP_ROT;
    
    if (!mDirty)
        markDirty();
}

void Node::setScale(float scale)
{
    mScale = Vector3(scale, scale, scale);
    mInterpolationFlags &= ~INTERP_SCALE;
    
    if (!mDirty)
        markDirty();
}

void Node::setScale(const Vector3& scale)
{
    mScale = scale;
    mInterpolationFlags &= ~INTERP_SCALE;
    
    if (!mDirty)
        markDirty();
}

void Node::setTransform(const Vector3& position, const Quaternion& rotation)
{
    mPosition = position;
    mRotation = rotation;
    mRotateCount = 0;
    mInterpolationFlags &= ~(INTERP_POS | INTERP_ROT);
    
    if (!mDirty)
        markDirty();
}

void Node::setTransform(const Vector3& position, const Quaternion& rotation, float scale)
{
    mPosition = position;
    mRotation = rotation;
    mScale = Vector3(scale, scale, scale);
    mRotateCount = 0;
    mInterpolationFlags &= ~(INTERP_POS | INTERP_ROT | INTERP_SCALE);
    
    if (!mDirty)
        markDirty();
}

void Node::setTransform(const Vector3& position, const Quaternion& rotation, const Vector3& scale)
{
    mPosition = position;
    mRotation = rotation;
    mScale = scale;
    mRotateCount = 0;
    mInterpolationFlags &= ~(INTERP_POS | INTERP_ROT | INTERP_SCALE);
    
    if (!mDirty)
        markDirty();
}

void Node::translate(const Vector3& delta)
{
    mPosition += delta;
    mInterpolationFlags &= ~INTERP_POS;
    
    if (!mDirty)
        markDirty();
}

void Node::translateRelative(const Vector3& delta)
{
    mPosition += mRotation * delta;
    mInterpolationFlags &= ~INTERP_POS;
    
    if (!mDirty)
        markDirty();
}

void Node::rotate(const Quaternion& delta, bool fixedAxis)
{
    if (!fixedAxis)
        mRotation = mRotation * delta;
    else
        mRotation = delta * mRotation;
    
    mRotateCount++;
    if (mRotateCount >= NORMALIZE_ROTATION_EVERY)
    {
        mRotation.normalize();
        mRotateCount = 0;
    }
    
    mInterpolationFlags &= ~INTERP_ROT;
    
    if (!mDirty)
        markDirty();
}

void Node::yaw(float angle, bool fixedAxis)
{
    rotate(Quaternion(angle, Vector3::sUp), fixedAxis);
}

void Node::pitch(float angle, bool fixedAxis)
{
    rotate(Quaternion(angle, Vector3::sRight), fixedAxis);
}

void Node::roll(float angle, bool fixedAxis)
{
    rotate(Quaternion(angle, Vector3::sForward), fixedAxis);
}

void Node::scale(float scale)
{
    mScale *= scale;
    mInterpolationFlags &= ~INTERP_SCALE;
    
    if (!mDirty)
        markDirty();
}

void Node::scale(const Vector3& scale)
{
    mScale *= scale;
    mInterpolationFlags &= ~INTERP_SCALE;
    
    if (!mDirty)
        markDirty();
}

void Node::setNodeFlags(unsigned flags)
{
    mNodeFlags = (mNodeFlags & NODE_PREDEFINEDFLAGS) | (flags & NODE_CUSTOMFLAGS);
}

void Node::addChild(Node* node)
{
    if ((!node) || (node->mParent == this) || (mParent == node))
        return;
    
    // Add first, then remove from old parent, to ensure the node does not get deleted
    mChildren.push_back(SharedPtr<Node>(node));
    
    if (node->mParent)
        node->mParent->removeChild(node);
    
    node->mParent = this;
    node->markDirty();
}

void Node::removeChild(Node* node, bool setWorldTransform)
{
    for (std::vector<SharedPtr<Node> >::iterator i = mChildren.begin(); i != mChildren.end(); ++i)
    {
        if ((*i) == node)
        {
            removeChild(i, setWorldTransform);
            return;
        }
    }
}

void Node::removeAllChildren(bool setWorldPosition)
{
    while (mChildren.size())
        removeChild(mChildren.end() - 1, setWorldPosition);
}

std::vector<Node*> Node::getChildren(unsigned nodeFlags, bool recursive) const
{
    if (!recursive)
    {
        std::vector<Node*> children;
        for (std::vector<SharedPtr<Node> >::const_iterator i = mChildren.begin(); i != mChildren.end(); ++i)
        {
            if ((*i)->mNodeFlags & nodeFlags)
                children.push_back(*i);
        }
        
        return children;
    }
    else
    {
        std::vector<Node*> allChildren;
        getChildrenRecursive(nodeFlags, allChildren);
        
        return allChildren;
    }
}

unsigned Node::getNumChildren(bool recursive) const
{
    if (!recursive)
        return mChildren.size();
    else
    {
        unsigned allChildren = mChildren.size();
        for (std::vector<SharedPtr<Node> >::const_iterator i = mChildren.begin(); i != mChildren.end(); ++i)
            allChildren += (*i)->getNumChildren(true);
        
        return allChildren;
    }
}

Node* Node::getChild(unsigned index) const
{
    if (index >= mChildren.size())
        return 0;
    
    return mChildren[index];
}

Node* Node::getChild(const std::string& name, bool recursive) const
{
    return getChild(StringHash(name), recursive);
}

Node* Node::getChild(StringHash nameHash, bool recursive) const
{
    for (std::vector<SharedPtr<Node> >::const_iterator i = mChildren.begin(); i != mChildren.end(); ++i)
    {
        if ((*i)->getNameHash() == nameHash)
            return *i;
        
        if (recursive)
        {
            Node* node = (*i)->getChild(nameHash, true);
            if (node)
                return node;
        }
    }
    
    return 0;
}

void Node::markDirty()
{
    mDirty = true;
    onMarkedDirty();
    
    for (std::vector<SharedPtr<Node> >::iterator i = mChildren.begin(); i != mChildren.end(); ++i)
        (*i)->markDirty();
}

void Node::getNetTransform(Vector3& position, Quaternion& rotation, Vector3& scale, ComponentRef& parentRef, const NetUpdateInfo& info)
{
    // Use the parent node only if it will be synced
    bool useParent = (!mParent) || (mParent->checkSync(info.mConnection));
    
    if (useParent)
    {
        position = mPosition;
        rotation = mRotation;
        scale = mScale;
        parentRef = ComponentRef(mParent);
    }
    else
    {
        position = getWorldPosition();
        rotation = getWorldRotation();
        scale = getWorldScale();
        parentRef = ComponentRef();
    }
}

void Node::updateWorldPosition()
{
    if (mParent)
    {
        const Quaternion& parentRotation = mParent->getWorldRotation();
        const Vector3& parentScale = mParent->getWorldScale();
        
        mWorldPosition = mParent->getWorldPosition() + (parentRotation * (parentScale * mPosition));
        mWorldRotation = parentRotation * mRotation;
        mWorldScale = parentScale * mScale;
    }
    else
    {
        mWorldPosition = mPosition;
        mWorldRotation = mRotation;
        mWorldScale = mScale;
    }
    
    mDirty = false;
    mWorldTransformDirty = true;
}

void Node::removeChild(std::vector<SharedPtr<Node> >::iterator i, bool setWorldTransform)
{
    Node* node = (*i);
    if (setWorldTransform)
        node->setTransform(node->getWorldPosition(), node->getWorldRotation(), node->getWorldScale());
    node->mParent = 0;
    node->markDirty();
    mChildren.erase(i);
}

void Node::getChildrenRecursive(unsigned nodeFlags, std::vector<Node*>& dest) const
{
    for (std::vector<SharedPtr<Node> >::const_iterator i = mChildren.begin(); i != mChildren.end(); ++i)
    {
        if ((*i)->mNodeFlags & nodeFlags)
            dest.push_back(*i);
        (*i)->getChildrenRecursive(nodeFlags, dest);
    }
}
