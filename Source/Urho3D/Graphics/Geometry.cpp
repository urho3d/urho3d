//
// Copyright (c) 2008-2015 the Urho3D project.
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

#include "../Precompiled.h"

#include "../Graphics/Geometry.h"
#include "../Graphics/Graphics.h"
#include "../Graphics/IndexBuffer.h"
#include "../Graphics/VertexBuffer.h"
#include "../IO/Log.h"
#include "../Math/Ray.h"

#include "../DebugNew.h"

namespace Urho3D
{

Geometry::Geometry(Context* context) :
    Object(context),
    primitiveType_(TRIANGLE_LIST),
    indexStart_(0),
    indexCount_(0),
    vertexStart_(0),
    vertexCount_(0),
    positionBufferIndex_(M_MAX_UNSIGNED),
    rawVertexSize_(0),
    rawElementMask_(0),
    rawIndexSize_(0),
    lodDistance_(0.0f)
{
    SetNumVertexBuffers(1);
}

Geometry::~Geometry()
{
}

bool Geometry::SetNumVertexBuffers(unsigned num)
{
    if (num >= MAX_VERTEX_STREAMS)
    {
        URHO3D_LOGERROR("Too many vertex streams");
        return false;
    }

    unsigned oldSize = vertexBuffers_.Size();
    vertexBuffers_.Resize(num);
    elementMasks_.Resize(num);

    for (unsigned i = oldSize; i < num; ++i)
        elementMasks_[i] = MASK_NONE;

    GetPositionBufferIndex();
    return true;
}

bool Geometry::SetVertexBuffer(unsigned index, VertexBuffer* buffer, unsigned elementMask)
{
    if (index >= vertexBuffers_.Size())
    {
        URHO3D_LOGERROR("Stream index out of bounds");
        return false;
    }

    vertexBuffers_[index] = buffer;

    if (buffer)
    {
        if (elementMask == MASK_DEFAULT)
            elementMasks_[index] = buffer->GetElementMask();
        else
            elementMasks_[index] = elementMask;
    }

    GetPositionBufferIndex();
    return true;
}

void Geometry::SetIndexBuffer(IndexBuffer* buffer)
{
    indexBuffer_ = buffer;
}

bool Geometry::SetDrawRange(PrimitiveType type, unsigned indexStart, unsigned indexCount, bool getUsedVertexRange)
{
    if (!indexBuffer_ && !rawIndexData_)
    {
        URHO3D_LOGERROR("Null index buffer and no raw index data, can not define indexed draw range");
        return false;
    }
    if (indexBuffer_ && indexStart + indexCount > indexBuffer_->GetIndexCount())
    {
        URHO3D_LOGERROR("Illegal draw range " + String(indexStart) + " to " + String(indexStart + indexCount - 1) + ", index buffer has " +
                 String(indexBuffer_->GetIndexCount()) + " indices");
        return false;
    }

    primitiveType_ = type;
    indexStart_ = indexStart;
    indexCount_ = indexCount;

    // Get min.vertex index and num of vertices from index buffer. If it fails, use full range as fallback
    if (indexCount)
    {
        vertexStart_ = 0;
        vertexCount_ = vertexBuffers_[0] ? vertexBuffers_[0]->GetVertexCount() : 0;

        if (getUsedVertexRange && indexBuffer_)
            indexBuffer_->GetUsedVertexRange(indexStart_, indexCount_, vertexStart_, vertexCount_);
    }
    else
    {
        vertexStart_ = 0;
        vertexCount_ = 0;
    }

    return true;
}

bool Geometry::SetDrawRange(PrimitiveType type, unsigned indexStart, unsigned indexCount, unsigned minVertex, unsigned vertexCount,
    bool checkIllegal)
{
    if (indexBuffer_)
    {
        // We can allow setting an illegal draw range now if the caller guarantees to resize / fill the buffer later
        if (checkIllegal && indexStart + indexCount > indexBuffer_->GetIndexCount())
        {
            URHO3D_LOGERROR("Illegal draw range " + String(indexStart) + " to " + String(indexStart + indexCount - 1) +
                     ", index buffer has " + String(indexBuffer_->GetIndexCount()) + " indices");
            return false;
        }
    }
    else if (!rawIndexData_)
    {
        indexStart = 0;
        indexCount = 0;
    }

    primitiveType_ = type;
    indexStart_ = indexStart;
    indexCount_ = indexCount;
    vertexStart_ = minVertex;
    vertexCount_ = vertexCount;

    return true;
}

void Geometry::SetLodDistance(float distance)
{
    if (distance < 0.0f)
        distance = 0.0f;

    lodDistance_ = distance;
}

void Geometry::SetRawVertexData(SharedArrayPtr<unsigned char> data, unsigned vertexSize, unsigned elementMask)
{
    rawVertexData_ = data;
    rawVertexSize_ = vertexSize;
    rawElementMask_ = elementMask;
}

void Geometry::SetRawIndexData(SharedArrayPtr<unsigned char> data, unsigned indexSize)
{
    rawIndexData_ = data;
    rawIndexSize_ = indexSize;
}

void Geometry::Draw(Graphics* graphics)
{
    if (indexBuffer_ && indexCount_ > 0)
    {
        graphics->SetIndexBuffer(indexBuffer_);
        graphics->SetVertexBuffers(vertexBuffers_, elementMasks_);
        graphics->Draw(primitiveType_, indexStart_, indexCount_, vertexStart_, vertexCount_);
    }
    else if (vertexCount_ > 0)
    {
        graphics->SetVertexBuffers(vertexBuffers_, elementMasks_);
        graphics->Draw(primitiveType_, vertexStart_, vertexCount_);
    }
}

VertexBuffer* Geometry::GetVertexBuffer(unsigned index) const
{
    return index < vertexBuffers_.Size() ? vertexBuffers_[index] : (VertexBuffer*)0;
}

unsigned Geometry::GetVertexElementMask(unsigned index) const
{
    return index < elementMasks_.Size() ? elementMasks_[index] : 0;
}

unsigned short Geometry::GetBufferHash() const
{
    unsigned short hash = 0;

    for (unsigned i = 0; i < vertexBuffers_.Size(); ++i)
    {
        VertexBuffer* vBuf = vertexBuffers_[i];
        hash += *((unsigned short*)&vBuf);
    }

    IndexBuffer* iBuf = indexBuffer_;
    hash += *((unsigned short*)&iBuf);

    return hash;
}

void Geometry::GetRawData(const unsigned char*& vertexData, unsigned& vertexSize, const unsigned char*& indexData,
    unsigned& indexSize, unsigned& elementMask) const
{
    if (rawVertexData_)
    {
        vertexData = rawVertexData_;
        vertexSize = rawVertexSize_;
        elementMask = rawElementMask_;
    }
    else
    {
        if (positionBufferIndex_ < vertexBuffers_.Size() && vertexBuffers_[positionBufferIndex_])
        {
            vertexData = vertexBuffers_[positionBufferIndex_]->GetShadowData();
            if (vertexData)
            {
                vertexSize = vertexBuffers_[positionBufferIndex_]->GetVertexSize();
                elementMask = vertexBuffers_[positionBufferIndex_]->GetElementMask();
            }
            else
            {
                vertexSize = 0;
                elementMask = 0;
            }
        }
        else
        {
            vertexData = 0;
            vertexSize = 0;
            elementMask = 0;
        }
    }

    if (rawIndexData_)
    {
        indexData = rawIndexData_;
        indexSize = rawIndexSize_;
    }
    else
    {
        if (indexBuffer_)
        {
            indexData = indexBuffer_->GetShadowData();
            if (indexData)
                indexSize = indexBuffer_->GetIndexSize();
            else
                indexSize = 0;
        }
        else
        {
            indexData = 0;
            indexSize = 0;
        }
    }
}

void Geometry::GetRawDataShared(SharedArrayPtr<unsigned char>& vertexData, unsigned& vertexSize,
    SharedArrayPtr<unsigned char>& indexData, unsigned& indexSize, unsigned& elementMask) const
{
    if (rawVertexData_)
    {
        vertexData = rawVertexData_;
        vertexSize = rawVertexSize_;
        elementMask = rawElementMask_;
    }
    else
    {
        if (positionBufferIndex_ < vertexBuffers_.Size() && vertexBuffers_[positionBufferIndex_])
        {
            vertexData = vertexBuffers_[positionBufferIndex_]->GetShadowDataShared();
            if (vertexData)
            {
                vertexSize = vertexBuffers_[positionBufferIndex_]->GetVertexSize();
                elementMask = vertexBuffers_[positionBufferIndex_]->GetElementMask();
            }
            else
            {
                vertexSize = 0;
                elementMask = 0;
            }
        }
        else
        {
            vertexData = 0;
            vertexSize = 0;
            elementMask = 0;
        }
    }

    if (rawIndexData_)
    {
        indexData = rawIndexData_;
        indexSize = rawIndexSize_;
    }
    else
    {
        if (indexBuffer_)
        {
            indexData = indexBuffer_->GetShadowDataShared();
            if (indexData)
                indexSize = indexBuffer_->GetIndexSize();
            else
                indexSize = 0;
        }
        else
        {
            indexData = 0;
            indexSize = 0;
        }
    }
}

float Geometry::GetHitDistance(const Ray& ray, Vector3* outNormal, Vector2* outUV) const
{
    const unsigned char* vertexData;
    const unsigned char* indexData;
    unsigned vertexSize;
    unsigned indexSize;
    unsigned elementMask;
    unsigned uvOffset = 0;

    GetRawData(vertexData, vertexSize, indexData, indexSize, elementMask);

    if (vertexData)
    {
        if (outUV)
        {
            if ((elementMask & MASK_TEXCOORD1) == 0)
            {
                // requested UV output, but no texture data in vertex buffer
                URHO3D_LOGWARNING("Illegal GetHitDistance call: UV return requested on vertex buffer without UV coords");
                *outUV = Vector2::ZERO;
                outUV = 0;
            }
            else
                uvOffset = VertexBuffer::GetElementOffset(elementMask, ELEMENT_TEXCOORD1);
        }

        return indexData ? ray.HitDistance(vertexData, vertexSize, indexData, indexSize, indexStart_, indexCount_, outNormal, outUV,
            uvOffset) :
               ray.HitDistance(vertexData, vertexSize, vertexStart_, vertexCount_, outNormal, outUV, uvOffset);
    }

    return M_INFINITY;
}

bool Geometry::IsInside(const Ray& ray) const
{
    const unsigned char* vertexData;
    const unsigned char* indexData;
    unsigned vertexSize;
    unsigned indexSize;
    unsigned elementMask;

    GetRawData(vertexData, vertexSize, indexData, indexSize, elementMask);

    return vertexData ? (indexData ? ray.InsideGeometry(vertexData, vertexSize, indexData, indexSize, indexStart_, indexCount_) :
                         ray.InsideGeometry(vertexData, vertexSize, vertexStart_, vertexCount_)) : false;
}

void Geometry::GetPositionBufferIndex()
{
    for (unsigned i = 0; i < vertexBuffers_.Size(); ++i)
    {
        if (vertexBuffers_[i] && vertexBuffers_[i]->GetElementMask() & MASK_POSITION)
        {
            positionBufferIndex_ = i;
            return;
        }
    }

    // No vertex buffer with positions
    positionBufferIndex_ = M_MAX_UNSIGNED;
}

}
