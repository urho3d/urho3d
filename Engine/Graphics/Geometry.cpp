//
// Urho3D Engine
// Copyright (c) 2008-2012 Lasse Öörni
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
#include "Geometry.h"
#include "Graphics.h"
#include "IndexBuffer.h"
#include "Log.h"
#include "Ray.h"
#include "VertexBuffer.h"

#include "DebugNew.h"

OBJECTTYPESTATIC(Geometry);

Geometry::Geometry(Context* context) :
    Object(context),
    primitiveType_(TRIANGLE_LIST),
    indexStart_(0),
    indexCount_(0),
    vertexStart_(0),
    vertexCount_(0),
    positionBufferIndex_(M_MAX_UNSIGNED),
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
        LOGERROR("Too many vertex streams");
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
        LOGERROR("Stream index out of bounds");
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
    if (!indexBuffer_)
    {
        LOGERROR("Null index buffer, can not define indexed draw range");
        return false;
    }
    if (indexStart + indexCount > indexBuffer_->GetIndexCount())
    {
        LOGERROR("Illegal draw range");
        return false;
    }
    
    primitiveType_ = type;
    indexStart_ = indexStart;
    indexCount_ = indexCount;
    
    // Get min.vertex index and num of vertices from index buffer. If it fails, use full range as fallback
    vertexStart_ = 0;
    vertexCount_ = vertexBuffers_[0]->GetVertexCount();
    
    if (getUsedVertexRange)
        indexBuffer_->GetUsedVertexRange(indexStart_, indexCount_, vertexStart_, vertexCount_);
    
    return true;
}

bool Geometry::SetDrawRange(PrimitiveType type, unsigned indexStart, unsigned indexCount, unsigned minVertex, unsigned vertexCount)
{
    if (indexBuffer_)
    {
        if (indexStart + indexCount > indexBuffer_->GetIndexCount())
        {
            LOGERROR("Illegal draw range");
            return false;
        }
    }
    else
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

void Geometry::Draw(Graphics* graphics)
{
    if (indexBuffer_)
    {
        graphics->SetIndexBuffer(indexBuffer_);
        graphics->SetVertexBuffers(vertexBuffers_, elementMasks_);
        graphics->Draw(primitiveType_, indexStart_, indexCount_, vertexStart_, vertexCount_);
    }
    else
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

bool Geometry::IsEmpty() const
{
    if (indexBuffer_)
        return indexCount_ == 0;
    else
        return vertexCount_ == 0;
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


void Geometry::GetRawData(const unsigned char*& vertexData, unsigned& vertexSize, const unsigned char*& indexData, unsigned& indexSize, unsigned& elementMask)
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

float Geometry::GetDistance(const Ray& ray)
{
    const unsigned char* rawVertexData;
    const unsigned char* rawIndexData;
    unsigned vertexSize;
    unsigned indexSize;
    unsigned elementMask;
    
    GetRawData(rawVertexData, vertexSize, rawIndexData, indexSize, elementMask);
    if (!rawVertexData || !rawIndexData)
        return M_INFINITY;
    
    return ray.HitDistance(rawVertexData, vertexSize, rawIndexData, indexSize, indexStart_, indexCount_);
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
