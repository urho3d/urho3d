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
#include "Geometry.h"
#include "Graphics.h"
#include "GraphicsImpl.h"
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
    lodDistance_(0.0f),
    positionBufferIndex_(M_MAX_UNSIGNED)
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
    
    unsigned oldSize = vertexBuffer_.size();
    vertexBuffer_.resize(num);
    elementMasks_.resize(num);
    
    for (unsigned i = oldSize; i < num; ++i)
        elementMasks_[i] = MASK_NONE;
    
    GetPositionBufferIndex();
    return true;
}

bool Geometry::SetVertexBuffer(unsigned index, VertexBuffer* buffer, unsigned elementMask)
{
    if (index >= vertexBuffer_.size())
    {
        LOGERROR("Illegal stream index");
        return false;
    }
    
    vertexBuffer_[index] = buffer;
    
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

bool Geometry::SetDrawRange(PrimitiveType type, unsigned indexStart, unsigned indexCount, bool GetUsedVertexRange)
{
    if (!indexBuffer_)
    {
        LOGERROR("Index buffer not defined, can not define draw range");
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
    vertexCount_ = vertexBuffer_[0]->GetVertexCount();
    
    if (GetUsedVertexRange)
        indexBuffer_->GetUsedVertexRange(indexStart_, indexCount_, vertexStart_, vertexCount_);
    
    return true;
}

bool Geometry::SetDrawRange(PrimitiveType type, unsigned indexStart, unsigned indexCount, unsigned minVertex, unsigned vertexCount)
{
    if (!indexBuffer_)
    {
        LOGERROR("Index buffer not defined, can not define draw range");
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
    graphics->SetIndexBuffer(indexBuffer_);
    graphics->SetVertexBuffers(vertexBuffer_, elementMasks_);
    graphics->Draw(primitiveType_, indexStart_, indexCount_, vertexStart_, vertexCount_);
}

VertexBuffer* Geometry::GetVertexBuffer(unsigned index) const
{
    return index < vertexBuffer_.size() ? vertexBuffer_[index] : (VertexBuffer*)0;
}

unsigned Geometry::GetVertexElementMask(unsigned index) const
{
    return index < elementMasks_.size() ? elementMasks_[index] : 0;
}

unsigned short Geometry::GetBufferHash() const
{
    unsigned short hash = 0;
    
    for (unsigned i = 0; i < vertexBuffer_.size(); ++i)
    {
        VertexBuffer* vBuf = vertexBuffer_[i];
        hash += *((unsigned short*)&vBuf);
    }
    
    IndexBuffer* iBuf = indexBuffer_;
    hash += *((unsigned short*)&iBuf);
    
    return hash;
}

float Geometry::GetDistance(const Ray& ray)
{
    const unsigned char* vertexData;
    const unsigned char* indexData;
    unsigned vertexSize;
    unsigned indexSize;
    
    LockRawData(vertexData, vertexSize, indexData, indexSize);
    
    if ((!indexData) || (!vertexData))
        return M_INFINITY;
    
    float nearest = ray.GetDistance(vertexData, vertexSize, indexData, indexSize, indexStart_, indexCount_);
    UnlockRawData();
    
    return nearest;
}

void Geometry::LockRawData(const unsigned char*& vertexData, unsigned& vertexSize, const unsigned char*& indexData, unsigned& indexSize)
{
    if ((indexBuffer_) && (positionBufferIndex_ < vertexBuffer_.size()))
    {
        VertexBuffer* positionBuffer = vertexBuffer_[positionBufferIndex_];
        
        vertexData = reinterpret_cast<const unsigned char*>(positionBuffer->Lock(0, positionBuffer->GetVertexCount(), LOCK_READONLY));
        vertexSize = positionBuffer->GetVertexSize();
        indexData = reinterpret_cast<const unsigned char*>(indexBuffer_->Lock(0, indexBuffer_->GetIndexCount(), LOCK_READONLY));
        indexSize = indexBuffer_->GetIndexSize();
        if ((vertexData) && (indexData))
            return;
        
        // One of the locks failed; unlock the other
        if (vertexData)
            positionBuffer->Unlock();
        if (indexData)
            indexBuffer_->Unlock();
    }
    
    // Lock failed, or no buffers: return null pointers and sizes
    vertexData = 0;
    vertexSize = 0;
    indexData = 0;
    indexSize = 0;
}

void Geometry::UnlockRawData()
{
    if ((indexBuffer_) && (positionBufferIndex_ < vertexBuffer_.size()))
    {
        vertexBuffer_[positionBufferIndex_]->Unlock();
        indexBuffer_->Unlock();
    }
}

void Geometry::GetPositionBufferIndex()
{
    for (unsigned i = 0; i < vertexBuffer_.size(); ++i)
    {
        if ((vertexBuffer_[i]) && (vertexBuffer_[i]->GetElementMask() & MASK_POSITION))
        {
            positionBufferIndex_ = i;
            return;
        }
    }
    
    // No vertex buffer with positions
    positionBufferIndex_ = M_MAX_UNSIGNED;
}
