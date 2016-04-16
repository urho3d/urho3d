//
// Copyright (c) 2008-2016 the Urho3D project.
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

#include <Urho3D/Graphics/Animation.h>
#include <Urho3D/Math/BoundingBox.h>
#include <Urho3D/Graphics/Graphics.h>
#include <Urho3D/Graphics/VertexBuffer.h>
#include <Urho3D/IO/Serializer.h>
#include <Urho3D/Math/Matrix3x4.h>

using namespace Urho3D;

struct Triangle
{
    unsigned v0_;
    unsigned v1_;
    unsigned v2_;
};

struct ModelBone
{
    String name_;
    unsigned parentIndex_;
    Vector3 bindPosition_;
    Quaternion bindRotation_;
    Vector3 bindScale_;
    Vector3 derivedPosition_;
    Quaternion derivedRotation_;
    Vector3 derivedScale_;
    Matrix3x4 worldTransform_;
    Matrix3x4 inverseWorldTransform_;
    unsigned char collisionMask_;
    float radius_;
    BoundingBox boundingBox_;
};

struct ModelAnimation
{
    String name_;
    float length_;
    Vector<AnimationTrack> tracks_;
};

struct BoneWeightAssignment
{
    unsigned char boneIndex_;
    float weight_;
};

bool CompareWeights(const BoneWeightAssignment& lhs, const BoneWeightAssignment& rhs)
{
    return lhs.weight_ > rhs.weight_;
}

bool CompareKeyFrames(const AnimationKeyFrame& lhs, const AnimationKeyFrame& rhs)
{
    return lhs.time_ < rhs.time_;
}

struct ModelVertex
{
    ModelVertex() :
        hasBlendWeights_(false)
    {
    }

    Vector3 position_;
    Vector3 normal_;
    Color color_;
    Vector2 texCoord1_;
    Vector2 texCoord2_;
    Vector3 cubeTexCoord1_;
    Vector3 cubeTexCoord2_;
    Vector4 tangent_;
    float blendWeights_[4];
    unsigned char blendIndices_[4];
    bool hasBlendWeights_;
    
    unsigned useCount_;
    int cachePosition_;
    float score_;
};

struct ModelVertexBuffer
{
    unsigned elementMask_;
    unsigned morphStart_;
    unsigned morphCount_;
    Vector<ModelVertex> vertices_;
    
    ModelVertexBuffer() :
        elementMask_(0),
        morphStart_(0),
        morphCount_(0)
    {
    }
    
    void WriteData(Serializer& dest)
    {
        dest.WriteUInt(vertices_.Size());
        
        PODVector<VertexElement> elements = VertexBuffer::GetElements(elementMask_);
        dest.WriteUInt(elements.Size());
        for (unsigned j = 0; j < elements.Size(); ++j)
        {
            unsigned elementDesc = ((unsigned)elements[j].type_) |
                (((unsigned)elements[j].semantic_) << 8) |
                (((unsigned)elements[j].index_) << 16);
            dest.WriteUInt(elementDesc);
        }

        dest.WriteUInt(morphStart_);
        dest.WriteUInt(morphCount_);
        
        for (unsigned i = 0; i < vertices_.Size(); ++i)
        {
            if (elementMask_ & MASK_POSITION)
                dest.WriteVector3(vertices_[i].position_);
            if (elementMask_ & MASK_NORMAL)
                dest.WriteVector3(vertices_[i].normal_);
            if (elementMask_ & MASK_COLOR)
                dest.WriteUInt(vertices_[i].color_.ToUInt());
            if (elementMask_ & MASK_TEXCOORD1)
                dest.WriteVector2(vertices_[i].texCoord1_);
            if (elementMask_ & MASK_TEXCOORD2)
                dest.WriteVector2(vertices_[i].texCoord2_);
            if (elementMask_ & MASK_CUBETEXCOORD1)
                dest.WriteVector3(vertices_[i].cubeTexCoord1_);
            if (elementMask_ & MASK_CUBETEXCOORD2)
                dest.WriteVector3(vertices_[i].cubeTexCoord2_);
            if (elementMask_ & MASK_TANGENT)
                dest.WriteVector4(vertices_[i].tangent_);
            if (elementMask_ & MASK_BLENDWEIGHTS)
                dest.Write(&vertices_[i].blendWeights_[0], 4 * sizeof(float));
            if (elementMask_ & MASK_BLENDINDICES)
                dest.Write(&vertices_[i].blendIndices_[0], 4 * sizeof(unsigned char));
        }
    }
};

struct ModelMorphBuffer
{
    unsigned vertexBuffer_;
    unsigned elementMask_;
    Vector<Pair<unsigned, ModelVertex> > vertices_;
};

struct ModelMorph
{
    String name_;
    Vector<ModelMorphBuffer> buffers_;
    
    void WriteData(Serializer& dest)
    {
        dest.WriteString(name_);
        dest.WriteUInt(buffers_.Size());
        for (unsigned i = 0; i < buffers_.Size(); ++i)
        {
            dest.WriteUInt(buffers_[i].vertexBuffer_);
            dest.WriteUInt(buffers_[i].elementMask_);
            dest.WriteUInt(buffers_[i].vertices_.Size());
            unsigned elementMask = buffers_[i].elementMask_;
            
            for (Vector<Pair<unsigned, ModelVertex> >::Iterator j = buffers_[i].vertices_.Begin();
                j != buffers_[i].vertices_.End(); ++j)
            {
                dest.WriteUInt(j->first_);
                if (elementMask & MASK_POSITION)
                    dest.WriteVector3(j->second_.position_);
                if (elementMask & MASK_NORMAL)
                    dest.WriteVector3(j->second_.normal_);
                if (elementMask & MASK_TANGENT)
                    dest.WriteVector3(Vector3(j->second_.tangent_.x_, j->second_.tangent_.y_, j->second_.tangent_.z_));
            }
        }
    }
};

struct ModelIndexBuffer
{
    unsigned indexSize_;
    PODVector<unsigned> indices_;
    
    ModelIndexBuffer() :
        indexSize_(sizeof(unsigned short))
    {
    }
    
    void WriteData(Serializer& dest)
    {
        dest.WriteUInt(indices_.Size());
        dest.WriteUInt(indexSize_);
        
        for (unsigned i = 0; i < indices_.Size(); ++i)
        {
            if (indexSize_ == sizeof(unsigned short))
                dest.WriteUShort(indices_[i]);
            else
                dest.WriteUInt(indices_[i]);
        }
    }
};

struct ModelSubGeometryLodLevel
{
    float distance_;
    PrimitiveType primitiveType_;
    unsigned vertexBuffer_;
    unsigned indexBuffer_;
    unsigned indexStart_;
    unsigned indexCount_;
    HashMap<unsigned, PODVector<BoneWeightAssignment> > boneWeights_;
    PODVector<unsigned> boneMapping_;
    
    ModelSubGeometryLodLevel() : 
        distance_(0.0f),
        primitiveType_(TRIANGLE_LIST),
        indexBuffer_(0),
        indexStart_(0),
        indexCount_(0)
    {
    }
};
