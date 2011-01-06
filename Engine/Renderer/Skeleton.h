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

#ifndef RENDERER_SKELETON_H
#define RENDERER_SKELETON_H

#include "Bone.h"

class Deserializer;
class ResourceCache;
class Serializer;

//! A hierarchical collection of bones
class Skeleton
{
public:
    //! Construct an empty skeleton
    Skeleton();
    //! Destruct. Detach the root bone from its parent
    ~Skeleton();
    
    //! Read from a stream
    void load(Deserializer& source);
    //! Write to a stream
    void save(Serializer& dest);
    //! Define from source bones
    void define(const std::vector<SharedPtr<Bone> >& srcBones);
    //! Reset all animated bones, or all bones if forced
    void reset(bool force = false);
    
    //! Return all bones
    const std::vector<SharedPtr<Bone> >& getBones() const { return mBones; }
    //! Return root bone
    Bone* getRootBone() const { return mRootBone; }
    //! Return number of bones
    unsigned getNumBones() const { return mBones.size(); }
    //! Return bone by index
    Bone* getBone(unsigned index) const;
    //! Return bone by name
    Bone* getBone(const std::string& boneName) const;
    //! Return bone by name hash
    Bone* getBone(StringHash boneNameHash) const;
    //! Return bone index from pointer, or 0xffffffff if not found
    unsigned getBoneIndex(Bone* bone) const;
    //! Return whether bones have attached scene nodes
    bool hasAttachedNodes();
    
private:
    //! Prevent copy construction
    Skeleton(const Skeleton& rhs);
    //! Prevent assignment
    Skeleton& operator = (const Skeleton& rhs);
    //! Remove all bones
    void clearBones();
    
    //! Bones
    std::vector<SharedPtr<Bone> > mBones;
    //! Root bone
    SharedPtr<Bone> mRootBone;
    //! Scene nodes attached to bones flag
    bool mHasAttachedNodes;
};

#endif // RENDERER_SKELETON_H
