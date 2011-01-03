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

#ifndef MODELCONVERTER_MODELCONVERTERUTILS_H
#define MODELCONVERTER_MODELCONVERTERUTILS_H

#include "Animation.h"
#include "BoundingBox.h"
#include "Serializer.h"
#include "Matrix4x3.h"
#include "Renderer.h"

struct Triangle
{
    unsigned mVertex1;
    unsigned mVertex2;
    unsigned mVertex3;
};

struct ModelBone
{
    std::string mName;
    unsigned mParentIndex;
    Vector3 mBindPosition;
    Quaternion mBindRotation;
    Vector3 mBindScale;
    Vector3 mDerivedPosition;
    Quaternion mDerivedRotation;
    Vector3 mDerivedScale;
    Matrix4x3 mWorldTransform;
    Matrix4x3 mInverseWorldTransform;
    unsigned char mCollisionMask;
    float mRadius;
    BoundingBox mBoundingBox;
};

struct ModelAnimation
{
    std::string mName;
    float mLength;
    std::vector<AnimationTrack> mTracks;
};

struct BoneWeightAssignment
{
    unsigned char mBoneIndex;
    float mWeight;
};

bool compareWeights(const BoneWeightAssignment& lhs, const BoneWeightAssignment& rhs)
{
    return lhs.mWeight > rhs.mWeight;
}

bool compareKeyFrames(const AnimationKeyFrame& lhs, const AnimationKeyFrame& rhs)
{
    return lhs.mTime < rhs.mTime;
}

struct ModelVertex
{
    ModelVertex() :
        mHasBlendWeights(false)
    {
    }

    Vector3 mPosition;
    Vector3 mNormal;
    Color mColor;
    Vector2 mTexCoord1;
    Vector2 mTexCoord2;
    Vector3 mCubeTexCoord1;
    Vector3 mCubeTexCoord2;
    Vector4 mTangent;
    float mBlendWeights[4];
    unsigned char mBlendIndices[4];
    bool mHasBlendWeights;
    
    unsigned mUseCount;
    int mCachePosition;
    float mScore;
};

struct ModelVertexBuffer
{
    unsigned mElementMask;
    unsigned mMorphStart;
    unsigned mMorphCount;
    std::vector<ModelVertex> mVertices;
    
    ModelVertexBuffer() :
        mElementMask(0),
        mMorphStart(0),
        mMorphCount(0)
    {
    }
    
    void writeData(Serializer& dest)
    {
        dest.writeUInt(mVertices.size());
        dest.writeUInt(mElementMask);
        dest.writeUInt(mMorphStart);
        dest.writeUInt(mMorphCount);
        
        for (unsigned i = 0; i < mVertices.size(); ++i)
        {
            if (mElementMask & MASK_POSITION)
                dest.writeVector3(mVertices[i].mPosition);
            if (mElementMask & MASK_NORMAL)
                dest.writeVector3(mVertices[i].mNormal);
            if (mElementMask & MASK_COLOR)
                dest.writeUInt(Renderer::getD3DColor(mVertices[i].mColor));
            if (mElementMask & MASK_TEXCOORD1)
                dest.writeVector2(mVertices[i].mTexCoord1);
            if (mElementMask & MASK_TEXCOORD2)
                dest.writeVector2(mVertices[i].mTexCoord2);
            if (mElementMask & MASK_CUBETEXCOORD1)
                dest.writeVector3(mVertices[i].mCubeTexCoord1);
            if (mElementMask & MASK_CUBETEXCOORD2)
                dest.writeVector3(mVertices[i].mCubeTexCoord2);
            if (mElementMask & MASK_TANGENT)
                dest.writeVector4(mVertices[i].mTangent);
            if (mElementMask & MASK_BLENDWEIGHTS)
                dest.write(&mVertices[i].mBlendWeights[0], 4 * sizeof(float));
            if (mElementMask & MASK_BLENDINDICES)
                dest.write(&mVertices[i].mBlendIndices[0], 4 * sizeof(unsigned char));
        }
    }
};

struct ModelMorphBuffer
{
    unsigned mVertexBuffer;
    unsigned mElementMask;
    std::map<unsigned, ModelVertex> mVertices;
};

struct ModelMorph
{
    std::string mName;
    std::vector<ModelMorphBuffer> mBuffers;
    
    void writeData(Serializer& dest)
    {
        dest.writeString(mName);
        dest.writeUInt(mBuffers.size());
        for (unsigned i = 0; i < mBuffers.size(); ++i)
        {
            dest.writeUInt(mBuffers[i].mVertexBuffer);
            dest.writeUInt(mBuffers[i].mElementMask);
            dest.writeUInt(mBuffers[i].mVertices.size());
            unsigned elementMask = mBuffers[i].mElementMask;
            
            for (std::map<unsigned, ModelVertex>::iterator j = mBuffers[i].mVertices.begin(); j != mBuffers[i].mVertices.end(); ++j)
            {
                dest.writeUInt(j->first);
                if (elementMask & MASK_POSITION)
                    dest.writeVector3(j->second.mPosition);
                if (elementMask & MASK_NORMAL)
                    dest.writeVector3(j->second.mNormal);
                if (elementMask & MASK_TANGENT)
                    dest.writeVector4(j->second.mTangent);
            }
        }
    }
};

struct ModelIndexBuffer
{
    unsigned mIndexSize;
    std::vector<unsigned> mIndices;
    
    ModelIndexBuffer() :
        mIndexSize(sizeof(unsigned short))
    {
    }
    
    void writeData(Serializer& dest)
    {
        dest.writeUInt(mIndices.size());
        dest.writeUInt(mIndexSize);
        
        for (unsigned i = 0; i < mIndices.size(); ++i)
        {
            if (mIndexSize == sizeof(unsigned short))
                dest.writeUShort(mIndices[i]);
            else
                dest.writeUInt(mIndices[i]);
        }
    }
};

struct ModelSubGeometryLodLevel
{
    float mDistance;
    PrimitiveType mPrimitiveType;
    unsigned mVertexBuffer;
    unsigned mIndexBuffer;
    unsigned mIndexStart;
    unsigned mIndexCount;
    std::map<unsigned, std::vector<BoneWeightAssignment> > mBoneWeights;
    std::vector<unsigned> mBoneMapping;
    
    ModelSubGeometryLodLevel() : 
        mDistance(0.0f),
        mPrimitiveType(TRIANGLE_LIST),
        mIndexBuffer(0),
        mIndexStart(0),
        mIndexCount(0)
    {
    }
};

#endif // MODELCONVERTER_MODELCONVERTERUTILS_H
