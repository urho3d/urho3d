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
#include "Bone.h"

#include "DebugNew.h"

Bone::Bone(Bone* rootBone, const std::string& name) :
    Node(NODE_BONE, name),
    mRootBone(rootBone),
    mBindPosition(Vector3::sZero),
    mBindRotation(Quaternion::sIdentity),
    mBindScale(Vector3::sUnity),
    mInitialPosition(Vector3::sZero),
    mInitialRotation(Quaternion::sIdentity),
    mInitialScale(Vector3::sUnity),
    mCollisionMask(BONECOLLISION_NONE),
    mRadius(0.0f),
    mAnimationEnabled(true),
    mBindInverseTransformDirty(true),
    mSkinningDirty(true)
{
    if (!mRootBone)
        mRootBone = this;
}

Bone::~Bone()
{
}

void Bone::setRootBone(Bone* rootBone)
{
    if (rootBone == 0)
        rootBone = this;
    
    if (rootBone != mRootBone)
    {
        mRootBone = rootBone;
        markDirty();
        markBindInverseTransformDirty();
    }
}

void Bone::setBindTransform(const Vector3& position, const Quaternion& rotation, const Vector3& scale)
{
    mBindPosition = position;
    mBindRotation = rotation;
    mBindScale = scale;
    
    markDirty();
    markBindInverseTransformDirty();
}

void Bone::setInitialTransform(const Vector3& position, const Quaternion& rotation, const Vector3& scale)
{
    mInitialPosition = position;
    mInitialRotation = rotation;
    mInitialScale = scale;
}

void Bone::setRadius(float radius)
{
    mRadius = radius;
    mCollisionMask |= BONECOLLISION_SPHERE;
}

void Bone::setBoundingBox(const BoundingBox& box)
{
    mBoundingBox = box;
    mCollisionMask |= BONECOLLISION_BOX;
}

void Bone::setAnimationEnabled(bool enable)
{
    mAnimationEnabled = enable;
}

void Bone::reset(bool force)
{
    if ((force) || (mAnimationEnabled))
        setTransform(mInitialPosition, mInitialRotation, mInitialScale);
}

const Matrix4x3& Bone::getBindInverseTransform()
{
    if (mBindInverseTransformDirty)
    {
        // Have to traverse the hierarchy manually to get the root derived bind transform
        Vector3 derivedBindPosition = mBindPosition;
        Quaternion derivedBindRotation = mBindRotation;
        Vector3 derivedBindScale = mBindScale;
        
        if (this != mRootBone)
        {
            Bone* parent = dynamic_cast<Bone*>(getParent());
            while (parent)
            {
                const Vector3& parentBindPosition = parent->getBindPosition();
                const Quaternion& parentBindRotation = parent->getBindRotation();
                const Vector3& parentBindScale = parent->getBindScale();
                
                derivedBindPosition = parentBindPosition + (parentBindRotation * (parentBindScale * derivedBindPosition));
                derivedBindRotation = parentBindRotation * derivedBindRotation;
                derivedBindScale = parentBindScale * derivedBindScale;
                
                if (parent == mRootBone)
                    break;
                parent = dynamic_cast<Bone*>(parent->getParent());
            }
        }
        
        Matrix4x3 bindTransform(derivedBindPosition, derivedBindRotation, derivedBindScale);
        mBindInverseTransform = bindTransform.getInverse();
        
        mBindInverseTransformDirty = false;
    }
    
    return mBindInverseTransform;
}

void Bone::onMarkedDirty()
{
    mSkinningDirty = true;
    // Dirty also the skinning flag of root bone for faster checking of whether any bones have changed in the skeleton
    mRootBone->mSkinningDirty = true;
}

void Bone::onParentChanged()
{
    markBindInverseTransformDirty();
}

void Bone::markBindInverseTransformDirty()
{
    if (!mBindInverseTransformDirty)
    {
        mBindInverseTransformDirty = true;
        
        // Must also mark dirty all child nodes that are bones
        for (std::vector<SharedPtr<Node> >::iterator i = mChildren.begin(); i != mChildren.end(); ++i)
        {
            Bone* bone = dynamic_cast<Bone*>(i->getPtr());
            if (bone)
                bone->markBindInverseTransformDirty();
        }
    }
}
