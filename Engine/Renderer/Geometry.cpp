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
#include "IndexBuffer.h"
#include "Log.h"
#include "Ray.h"
#include "Renderer.h"
#include "RendererImpl.h"
#include "StringUtils.h"
#include "VertexBuffer.h"

#include "DebugNew.h"

Geometry::Geometry() :
    mPrimitiveType(TRIANGLE_LIST),
    mIndexStart(0),
    mIndexCount(0),
    mVertexStart(0),
    mVertexCount(0),
    mInstanceCount(0),
    mLodDistance(0.0f),
    mPositionBufferIndex(M_MAX_UNSIGNED)
{
    setNumVertexBuffers(1);
}

Geometry::~Geometry()
{
}

bool Geometry::setNumVertexBuffers(unsigned num)
{
    if (num >= MAX_VERTEX_STREAMS)
    {
        LOGERROR("Too many vertex streams");
        return false;
    }
    
    unsigned oldSize = mVertexBuffers.size();
    mVertexBuffers.resize(num);
    mVertexElementMasks.resize(num);
    
    for (unsigned i = oldSize; i < num; ++i)
        mVertexElementMasks[i] = MASK_NONE;
    
    getPositionBufferIndex();
    return true;
}

bool Geometry::setVertexBuffer(unsigned index, VertexBuffer* buffer, unsigned elementMask)
{
    if (index >= mVertexBuffers.size())
    {
        LOGERROR("Illegal stream index");
        return false;
    }
    
    mVertexBuffers[index] = buffer;
    
    if (buffer)
    {
        if (elementMask == MASK_DEFAULT)
            mVertexElementMasks[index] = buffer->getElementMask();
        else
            mVertexElementMasks[index] = elementMask;
    }
    
    getPositionBufferIndex();
    return true;
}

void Geometry::setIndexBuffer(IndexBuffer* buffer)
{
    mIndexBuffer = buffer;
}

bool Geometry::setDrawRange(PrimitiveType type, unsigned indexStart, unsigned indexCount, bool getUsedVertexRange)
{
    if (!mIndexBuffer)
    {
        LOGERROR("Index buffer not defined, can not define draw range");
        return false;
    }
    if (indexStart + indexCount > mIndexBuffer->getIndexCount())
    {
        LOGERROR("Illegal draw range");
        return false;
    }
    
    mPrimitiveType = type;
    mIndexStart = indexStart;
    mIndexCount = indexCount;
    
    // Get min.vertex index and num of vertices from index buffer. If it fails, use full range as fallback
    mVertexStart = 0;
    mVertexCount = mVertexBuffers[0]->getVertexCount();
    
    if (getUsedVertexRange)
        mIndexBuffer->getUsedVertexRange(mIndexStart, mIndexCount, mVertexStart, mVertexCount);
    
    return true;
}

bool Geometry::setDrawRange(PrimitiveType type, unsigned indexStart, unsigned indexCount, unsigned minVertex, unsigned vertexCount)
{
    if (!mIndexBuffer)
    {
        LOGERROR("Index buffer not defined, can not define draw range");
        return false;
    }
    if (indexStart + indexCount > mIndexBuffer->getIndexCount())
    {
        LOGERROR("Illegal draw range");
        return false;
    }
    
    mPrimitiveType = type;
    mIndexStart = indexStart;
    mIndexCount = indexCount;
    mVertexStart = minVertex;
    mVertexCount = vertexCount;
    
    return true;
}


void Geometry::setInstanceCount(unsigned count)
{
    mInstanceCount = count;
}

void Geometry::setLodDistance(float distance)
{
    if (distance < 0.0f)
        distance = 0.0f;
    
    mLodDistance = distance;
}

void Geometry::draw(Renderer* renderer)
{
    if (!mInstanceCount)
    {
        renderer->resetStreamFrequencies();
        renderer->setVertexBuffers(mVertexBuffers, mVertexElementMasks);
        renderer->setIndexBuffer(mIndexBuffer);
        renderer->draw(mPrimitiveType, mIndexStart, mIndexCount, mVertexStart, mVertexCount);
    }
    else
    {
        renderer->setVertexBuffers(mVertexBuffers, mVertexElementMasks);
        for (unsigned i = 0; i < mVertexBuffers.size(); ++i)
        {
            if (mVertexElementMasks[i] & MASK_INSTANCEMATRIX1)
                renderer->setStreamFrequency(i, D3DSTREAMSOURCE_INSTANCEDATA | 1);
            else
                renderer->setStreamFrequency(i, D3DSTREAMSOURCE_INDEXEDDATA | mInstanceCount);
        }
        renderer->setIndexBuffer(mIndexBuffer);
        renderer->draw(mPrimitiveType, mIndexStart, mIndexCount, mVertexStart, mVertexCount, mInstanceCount);
    }
}

VertexBuffer* Geometry::getVertexBuffer(unsigned index) const
{
    if (index >= mVertexBuffers.size())
        return 0;
    
    return mVertexBuffers[index];
}

unsigned Geometry::getVertexElementMask(unsigned index) const
{
    if (index >= mVertexElementMasks.size())
        return 0;
    
    return mVertexElementMasks[index];
}

unsigned short Geometry::getBufferHash() const
{
    unsigned short hash = 0;
    
    for (unsigned i = 0; i < mVertexBuffers.size(); ++i)
    {
        VertexBuffer* vBuf = mVertexBuffers[i];
        hash += *((unsigned short*)&vBuf);
    }
    
    IndexBuffer* iBuf = mIndexBuffer;
    hash += *((unsigned short*)&iBuf);
    
    return hash;
}

float Geometry::getDistance(const Ray& ray)
{
    const unsigned char* vertexData;
    const unsigned char* indexData;
    unsigned vertexSize;
    unsigned indexSize;
    
    lockRawData(vertexData, vertexSize, indexData, indexSize);
    
    if ((!indexData) || (!vertexData))
        return M_INFINITY;
    
    float nearest = ray.getDistance(vertexData, vertexSize, indexData, indexSize, mIndexStart, mIndexCount);
    unlockRawData();
    
    return nearest;
}

void Geometry::lockRawData(const unsigned char*& vertexData, unsigned& vertexSize, const unsigned char*& indexData, unsigned& indexSize)
{
    if ((mIndexBuffer) && (mPositionBufferIndex < mVertexBuffers.size()))
    {
        VertexBuffer* positionBuffer = mVertexBuffers[mPositionBufferIndex];
        
        try
        {
            vertexData = (const unsigned char*)positionBuffer->lock(0, positionBuffer->getVertexCount(), LOCK_READONLY);
            vertexSize = positionBuffer->getVertexSize();
            indexData = (const unsigned char*)mIndexBuffer->lock(0, mIndexBuffer->getIndexCount(), LOCK_READONLY);
            indexSize = mIndexBuffer->getIndexSize();
            return;
        }
        catch (...)
        {
            // One of the lock()'s failed, but do not know which, so unlock both
            positionBuffer->unlock();
            mIndexBuffer->unlock();
        }
    }
    
    vertexData = 0;
    vertexSize = 0;
    indexData = 0;
    indexSize = 0;
}

void Geometry::unlockRawData()
{
    if ((mIndexBuffer) && (mPositionBufferIndex < mVertexBuffers.size()))
    {
        mVertexBuffers[mPositionBufferIndex]->unlock();
        mIndexBuffer->unlock();
    }
}

void Geometry::getPositionBufferIndex()
{
    for (unsigned i = 0; i < mVertexBuffers.size(); ++i)
    {
        if ((mVertexBuffers[i]) && (mVertexBuffers[i]->getElementMask() & MASK_POSITION))
        {
            mPositionBufferIndex = i;
            return;
        }
    }
    
    // No vertex buffer with positions
    mPositionBufferIndex = M_MAX_UNSIGNED;
}
