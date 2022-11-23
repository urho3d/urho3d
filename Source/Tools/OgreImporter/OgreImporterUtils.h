// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

#pragma once

#include <Urho3D/Base/Utils.h>
#include <Urho3D/Graphics/Animation.h>
#include <Urho3D/Graphics/Graphics.h>
#include <Urho3D/GraphicsAPI/VertexBuffer.h>
#include <Urho3D/IO/Serializer.h>
#include <Urho3D/Math/BoundingBox.h>
#include <Urho3D/Math/Matrix3x4.h>

using namespace Urho3D;

struct Triangle
{
    // Fields are not initialized.
    Triangle() = default;

    Triangle(unsigned v0, unsigned v1, unsigned v2) :
        v0_{v0},
        v1_{v1},
        v2_{v2}
    {
    }

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
    BoneWeightAssignment(unsigned char boneIndex, float weight) :
        boneIndex_{boneIndex},
        weight_{weight}
    {
    }

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
    Vector3 position_;
    Vector3 normal_;
    Color color_;
    Vector2 texCoord1_;
    Vector2 texCoord2_;
    Vector3 cubeTexCoord1_;
    Vector3 cubeTexCoord2_;
    Vector4 tangent_;
    float blendWeights_[4]{};
    unsigned char blendIndices_[4]{};
    bool hasBlendWeights_{};
    unsigned useCount_{};
    int cachePosition_{};
    float score_{};
};

struct ModelVertexBuffer
{
    VertexElements elementMask_;
    unsigned morphStart_;
    unsigned morphCount_;
    Vector<ModelVertex> vertices_;

    ModelVertexBuffer() :
        elementMask_(VertexElements::None),
        morphStart_(0),
        morphCount_(0)
    {
    }

    void WriteData(Serializer& dest)
    {
        dest.WriteU32(vertices_.Size());

        Vector<VertexElement> elements = VertexBuffer::GetElements(elementMask_);
        dest.WriteU32(elements.Size());
        for (unsigned j = 0; j < elements.Size(); ++j)
        {
            unsigned elementDesc = ((unsigned)elements[j].type_) |
                (((unsigned)elements[j].semantic_) << 8u) |
                (((unsigned)elements[j].index_) << 16u);
            dest.WriteU32(elementDesc);
        }

        dest.WriteU32(morphStart_);
        dest.WriteU32(morphCount_);

        for (unsigned i = 0; i < vertices_.Size(); ++i)
        {
            if (!!(elementMask_ & VertexElements::Position))
                dest.WriteVector3(vertices_[i].position_);
            if (!!(elementMask_ & VertexElements::Normal))
                dest.WriteVector3(vertices_[i].normal_);
            if (!!(elementMask_ & VertexElements::Color))
                dest.WriteU32(vertices_[i].color_.ToU32());
            if (!!(elementMask_ & VertexElements::TexCoord1))
                dest.WriteVector2(vertices_[i].texCoord1_);
            if (!!(elementMask_ & VertexElements::TexCoord2))
                dest.WriteVector2(vertices_[i].texCoord2_);
            if (!!(elementMask_ & VertexElements::CubeTexCoord1))
                dest.WriteVector3(vertices_[i].cubeTexCoord1_);
            if (!!(elementMask_ & VertexElements::CubeTexCoord2))
                dest.WriteVector3(vertices_[i].cubeTexCoord2_);
            if (!!(elementMask_ & VertexElements::Tangent))
                dest.WriteVector4(vertices_[i].tangent_);
            if (!!(elementMask_ & VertexElements::BlendWeights))
                dest.Write(&vertices_[i].blendWeights_[0], 4 * sizeof(float));
            if (!!(elementMask_ & VertexElements::BlendIndices))
                dest.Write(&vertices_[i].blendIndices_[0], 4 * sizeof(unsigned char));
        }
    }
};

struct ModelMorphBuffer
{
    unsigned vertexBuffer_;
    VertexElements elementMask_;
    Vector<Pair<unsigned, ModelVertex>> vertices_;
};

struct ModelMorph
{
    String name_;
    Vector<ModelMorphBuffer> buffers_;

    void WriteData(Serializer& dest)
    {
        dest.WriteString(name_);
        dest.WriteU32(buffers_.Size());
        for (unsigned i = 0; i < buffers_.Size(); ++i)
        {
            dest.WriteU32(buffers_[i].vertexBuffer_);
            dest.WriteU32(ToU32(buffers_[i].elementMask_));
            dest.WriteU32(buffers_[i].vertices_.Size());
            VertexElements elementMask = buffers_[i].elementMask_;

            for (Vector<Pair<unsigned, ModelVertex>>::Iterator j = buffers_[i].vertices_.Begin();
                j != buffers_[i].vertices_.End(); ++j)
            {
                dest.WriteU32(j->first_);
                if (!!(elementMask & VertexElements::Position))
                    dest.WriteVector3(j->second_.position_);
                if (!!(elementMask & VertexElements::Normal))
                    dest.WriteVector3(j->second_.normal_);
                if (!!(elementMask & VertexElements::Tangent))
                    dest.WriteVector3(Vector3(j->second_.tangent_.x_, j->second_.tangent_.y_, j->second_.tangent_.z_));
            }
        }
    }
};

struct ModelIndexBuffer
{
    unsigned indexSize_;
    Vector<unsigned> indices_;

    ModelIndexBuffer() :
        indexSize_(sizeof(unsigned short))
    {
    }

    void WriteData(Serializer& dest)
    {
        dest.WriteU32(indices_.Size());
        dest.WriteU32(indexSize_);

        for (unsigned i = 0; i < indices_.Size(); ++i)
        {
            if (indexSize_ == sizeof(unsigned short))
                dest.WriteU16(indices_[i]);
            else
                dest.WriteU32(indices_[i]);
        }
    }
};

struct ModelSubGeometryLodLevel
{
    float distance_{};
    PrimitiveType primitiveType_{TRIANGLE_LIST};
    unsigned vertexBuffer_{};
    unsigned indexBuffer_{};
    unsigned indexStart_{};
    unsigned indexCount_{};
    HashMap<unsigned, Vector<BoneWeightAssignment>> boneWeights_;
    Vector<unsigned> boneMapping_;
};
