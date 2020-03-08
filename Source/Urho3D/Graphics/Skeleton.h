//
// Copyright (c) 2008-2020 the Urho3D project.
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

/// \file

#pragma once

#include "../Math/BoundingBox.h"
#include "../Scene/Node.h"

namespace Urho3D
{

enum BoneCollisionShape : unsigned char
{
    BONECOLLISION_NONE = 0x0,
    BONECOLLISION_SPHERE = 0x1,
    BONECOLLISION_BOX = 0x2,
};
URHO3D_FLAGSET(BoneCollisionShape, BoneCollisionShapeFlags);

class Deserializer;
class ResourceCache;
class Serializer;

/// %Bone in a skeleton.
struct Bone
{
    /// Construct with defaults.
    Bone() :
        parentIndex_(0),
        initialPosition_(Vector3::ZERO),
        initialRotation_(Quaternion::IDENTITY),
        initialScale_(Vector3::ONE),
        animated_(true),
        radius_(0.0f)
    {
    }

    /// Bone name.
    String name_;
    /// Bone name hash.
    StringHash nameHash_;
    /// Parent bone index.
    unsigned parentIndex_;
    /// Reset position.
    Vector3 initialPosition_;
    /// Reset rotation.
    Quaternion initialRotation_;
    /// Reset scale.
    Vector3 initialScale_;
    /// Offset matrix.
    Matrix3x4 offsetMatrix_;
    /// Animation enable flag.
    bool animated_;
    /// Supported collision types.
    BoneCollisionShapeFlags collisionMask_ = BONECOLLISION_NONE;
    /// Radius.
    float radius_;
    /// Local-space bounding box.
    BoundingBox boundingBox_;
    /// Scene node.
    WeakPtr<Node> node_;
};

/// Hierarchical collection of bones.
class URHO3D_API Skeleton
{
public:
    /// Construct an empty skeleton.
    Skeleton();
    /// Destruct.
    ~Skeleton();

    /// Read from a stream. Return true if successful.
    bool Load(Deserializer& source);
    /// Write to a stream. Return true if successful.
    bool Save(Serializer& dest) const;
    /// Define from another skeleton.
    void Define(const Skeleton& src);
    /// Set root bone's index.
    void SetRootBoneIndex(unsigned index);
    /// Clear bones.
    void ClearBones();
    /// Reset all animating bones to initial positions.
    void Reset();

    /// Return all bones.
    const Vector<Bone>& GetBones() const { return bones_; }

    /// Return modifiable bones.
    Vector<Bone>& GetModifiableBones() { return bones_; }

    /// Return number of bones.
    unsigned GetNumBones() const { return bones_.Size(); }

    /// Return root bone.
    Bone* GetRootBone();
    /// Return index of the bone by name. Return M_MAX_UNSIGNED if not found.
    unsigned GetBoneIndex(const String& boneName) const;
    /// Return index of the bone by name hash. Return M_MAX_UNSIGNED if not found.
    unsigned GetBoneIndex(const StringHash& boneNameHash) const;
    /// Return index of the bone by the bone pointer. Return M_MAX_UNSIGNED if not found.
    unsigned GetBoneIndex(const Bone* bone) const;
    /// Return parent of the given bone. Return null for root bones.
    Bone* GetBoneParent(const Bone* bone);
    /// Return bone by index.
    Bone* GetBone(unsigned index);
    /// Return bone by name.
    Bone* GetBone(const String& name);
    /// Return bone by name.
    Bone* GetBone(const char* name);
    /// Return bone by name hash.
    Bone* GetBone(const StringHash& boneNameHash);

    /// Reset all animating bones to initial positions without marking the nodes dirty. Requires the node dirtying to be performed later.
    void ResetSilent();

private:
    /// Bones.
    Vector<Bone> bones_;
    /// Root bone index.
    unsigned rootBoneIndex_;
};

}
