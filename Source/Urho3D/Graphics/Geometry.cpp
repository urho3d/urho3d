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
    rawVertexSize_(0),
    rawIndexSize_(0),
    lodDistance_(0.0f)
{
    SetNumVertexBuffers(1);
}

Geometry::~Geometry() = default;

bool Geometry::SetNumVertexBuffers(unsigned num)
{
    if (num >= MAX_VERTEX_STREAMS)
    {
        URHO3D_LOGERROR("Too many vertex streams");
        return false;
    }

    unsigned oldSize = vertexBuffers_.Size();
    vertexBuffers_.Resize(num);

    return true;
}

bool Geometry::SetVertexBuffer(unsigned index, VertexBuffer* buffer)
{
    if (index >= vertexBuffers_.Size())
    {
        URHO3D_LOGERROR("Stream index out of bounds");
        return false;
    }

    vertexBuffers_[index] = buffer;
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

bool Geometry::SetDrawRange(PrimitiveType type, unsigned indexStart, unsigned indexCount, unsigned vertexStart, unsigned vertexCount,
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
    vertexStart_ = vertexStart;
    vertexCount_ = vertexCount;

    return true;
}

void Geometry::SetLodDistance(float distance)
{
    if (distance < 0.0f)
        distance = 0.0f;

    lodDistance_ = distance;
}

void Geometry::SetRawVertexData(const SharedArrayPtr<unsigned char>& data, const PODVector<VertexElement>& elements)
{
    rawVertexData_ = data;
    rawVertexSize_ = VertexBuffer::GetVertexSize(elements);
    rawElements_ = elements;
}

void Geometry::SetRawVertexData(const SharedArrayPtr<unsigned char>& data, unsigned elementMask)
{
    rawVertexData_ = data;
    rawVertexSize_ = VertexBuffer::GetVertexSize(elementMask);
    rawElements_ = VertexBuffer::GetElements(elementMask);
}

void Geometry::SetRawIndexData(const SharedArrayPtr<unsigned char>& data, unsigned indexSize)
{
    rawIndexData_ = data;
    rawIndexSize_ = indexSize;
}

void Geometry::Draw(Graphics* graphics)
{
    if (indexBuffer_ && indexCount_ > 0)
    {
        graphics->SetIndexBuffer(indexBuffer_);
        graphics->SetVertexBuffers(vertexBuffers_);
        graphics->Draw(primitiveType_, indexStart_, indexCount_, vertexStart_, vertexCount_);
    }
    else if (vertexCount_ > 0)
    {
        graphics->SetVertexBuffers(vertexBuffers_);
        graphics->Draw(primitiveType_, vertexStart_, vertexCount_);
    }
}

VertexBuffer* Geometry::GetVertexBuffer(unsigned index) const
{
    return index < vertexBuffers_.Size() ? vertexBuffers_[index] : nullptr;
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
    unsigned& indexSize, const PODVector<VertexElement>*& elements) const
{
    if (rawVertexData_)
    {
        vertexData = rawVertexData_;
        vertexSize = rawVertexSize_;
        elements = &rawElements_;
    }
    else if (vertexBuffers_.Size() && vertexBuffers_[0])
    {
        vertexData = vertexBuffers_[0]->GetShadowData();
        vertexSize = vertexBuffers_[0]->GetVertexSize();
        elements = &vertexBuffers_[0]->GetElements();
    }
    else
    {
        vertexData = nullptr;
        vertexSize = 0;
        elements = nullptr;
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
            indexData = nullptr;
            indexSize = 0;
        }
    }
}

void Geometry::GetRawDataShared(SharedArrayPtr<unsigned char>& vertexData, unsigned& vertexSize,
    SharedArrayPtr<unsigned char>& indexData, unsigned& indexSize, const PODVector<VertexElement>*& elements) const
{
    if (rawVertexData_)
    {
        vertexData = rawVertexData_;
        vertexSize = rawVertexSize_;
        elements = &rawElements_;
    }
    else if (vertexBuffers_.Size() && vertexBuffers_[0])
    {
        vertexData = vertexBuffers_[0]->GetShadowDataShared();
        vertexSize = vertexBuffers_[0]->GetVertexSize();
        elements = &vertexBuffers_[0]->GetElements();
    }
    else
    {
        vertexData = nullptr;
        vertexSize = 0;
        elements = nullptr;
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
            indexData = nullptr;
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
    const PODVector<VertexElement>* elements;

    GetRawData(vertexData, vertexSize, indexData, indexSize, elements);

    if (!vertexData || !elements || VertexBuffer::GetElementOffset(*elements, TYPE_VECTOR3, SEM_POSITION) != 0)
        return M_INFINITY;

    unsigned uvOffset = VertexBuffer::GetElementOffset(*elements, TYPE_VECTOR2, SEM_TEXCOORD);

    if (outUV && uvOffset == M_MAX_UNSIGNED)
    {
        // requested UV output, but no texture data in vertex buffer
        URHO3D_LOGWARNING("Illegal GetHitDistance call: UV return requested on vertex buffer without UV coords");
        *outUV = Vector2::ZERO;
        outUV = nullptr;
    }

    return indexData ? ray.HitDistance(vertexData, vertexSize, indexData, indexSize, indexStart_, indexCount_, outNormal, outUV,
        uvOffset) : ray.HitDistance(vertexData, vertexSize, vertexStart_, vertexCount_, outNormal, outUV, uvOffset);
}

bool Geometry::IsInside(const Ray& ray) const
{
    const unsigned char* vertexData;
    const unsigned char* indexData;
    unsigned vertexSize;
    unsigned indexSize;
    const PODVector<VertexElement>* elements;

    GetRawData(vertexData, vertexSize, indexData, indexSize, elements);

    return vertexData ? (indexData ? ray.InsideGeometry(vertexData, vertexSize, indexData, indexSize, indexStart_, indexCount_) :
                         ray.InsideGeometry(vertexData, vertexSize, vertexStart_, vertexCount_)) : false;
}

}
