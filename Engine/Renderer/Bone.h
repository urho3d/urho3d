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

#ifndef RENDERER_BONE_H
#define RENDERER_BONE_H

#include "BoundingBox.h"
#include "Node.h"

static const unsigned BONECOLLISION_NONE = 0x0;
static const unsigned BONECOLLISION_SPHERE = 0x1;
static const unsigned BONECOLLISION_BOX = 0x2;

//! Bone scene node
class Bone : public Node
{
    DEFINE_TYPE(Bone);
    
public:
    //! Construct with skeleton root bone pointer and name
    Bone(Bone* rootBone = 0, const std::string& name = std::string());
    //! Destruct
    virtual ~Bone();
    
    //! Set root bone
    void setRootBone(Bone* rootBone);
    //! Set initial transform
    void setInitialTransform(const Vector3& position, const Quaternion& rotation, const Vector3& scale);
    //! Set skinning offset matrix
    void setOffsetMatrix(const Matrix4x3& offset);
    //! Set animation enabled
    void setAnimationEnabled(bool enable);
    //! Set radius for raycasts
    void setRadius(float radius);
    //! Set bounding box for raycasts
    void setBoundingBox(const BoundingBox& box);
    //! Reset to initial transform. If animation disabled, does nothing unless forced
    void reset(bool force = false);
    //! Clear skinning update flag
    void clearSkinningDirty() { mSkinningDirty = false; }
    
    //! Return root bone
    Bone* getRootBone() const { return mRootBone; }
    //! Return initial position
    const Vector3& getInitialPosition() const { return mInitialPosition; }
    //! Return initial rotation
    const Quaternion& getInitialRotation() const { return mInitialRotation; }
    //! Return initial scale
    const Vector3& getInitialScale() const { return mInitialScale; }
    //! Return offset matrix
    const Matrix4x3& getOffsetMatrix() const { return mOffsetMatrix; }
    //! Return supported collision types
    unsigned getCollisionMask() const { return mCollisionMask; }
    //! Return radius
    float getRadius() const { return mRadius; }
    //! Return bounding box
    const BoundingBox& getBoundingBox() const { return mBoundingBox; }
    //! Return whether animation is enabled
    bool isAnimationEnabled() const { return mAnimationEnabled; }
    //! Return whether skinning needs update
    bool isSkinningDirty() const { return mSkinningDirty; }
    
protected:
    //! Transform has changed. Mark skinning to need updating
    virtual void onMarkedDirty();
    
private:
    //! Skeleton root bone
    Bone* mRootBone;
    //! Reset position
    Vector3 mInitialPosition;
    //! Reset rotation
    Quaternion mInitialRotation;
    //! Reset scale
    Vector3 mInitialScale;
    //! Offset matrix
    Matrix4x3 mOffsetMatrix;
    //! Supported collision types
    unsigned char mCollisionMask;
    //! Radius
    float mRadius;
    //! Bounding box
    BoundingBox mBoundingBox;
    //! Animation enabled flag
    bool mAnimationEnabled;
    //! Skinning needs update flag
    bool mSkinningDirty;
};

#endif // RENDERER_BONE_H
