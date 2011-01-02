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
#include "Log.h"
#include "Renderer.h"
#include "RendererImpl.h"
#include "VertexBuffer.h"

#include "DebugNew.h"

const unsigned VertexBuffer::sElementSize[] = 
{
    3 * sizeof(float), // Position
    3 * sizeof(float), // Normal
    4 * sizeof(unsigned char), // Color
    2 * sizeof(float), // Texcoord1
    2 * sizeof(float), // Texcoord2
    3 * sizeof(float), // Cubetexcoord1
    3 * sizeof(float), // Cubetexcoord2
    4 * sizeof(float), // Tangent
    4 * sizeof(float), // Blendweights
    4 * sizeof(unsigned char), // Blendindices
    1 * sizeof(int), // Instancenumber
    4 * sizeof(float), // Instancematrix1
    4 * sizeof(float), // Instancematrix2
    4 * sizeof(float) // Instancematrix3
};

const std::string VertexBuffer::sElementName[] = 
{
    "Position",
    "Normal",
    "Color",
    "Texcoord1",
    "Texcoord2",
    "Cubetexcoord1",
    "Cubetexcoord2",
    "Tangent"
    "Blendweights",
    "Blendindices",
    "Instancenumber",
    "Instancematrix1",
    "Instancematrix2",
    "Instancematrix3"
};

VertexBuffer::VertexBuffer(Renderer* renderer, bool dynamic) :
    GPUObject(renderer),
    mVertexCount(0),
    mElementMask(0),
    mMorphRangeStart(0),
    mMorphRangeCount(0),
    mLocked(false),
    mDataLost(false)
{
    updateOffsets();
    
    if (dynamic)
    {
        mPool = D3DPOOL_DEFAULT;
        mUsage = D3DUSAGE_DYNAMIC | D3DUSAGE_WRITEONLY;
    }
    else
    {
        mPool = D3DPOOL_MANAGED;
        mUsage = 0;
    }
}

VertexBuffer::~VertexBuffer()
{
    release();
}

void VertexBuffer::onDeviceLost()
{
    if (mPool == D3DPOOL_DEFAULT)
        release();
}

void VertexBuffer::onDeviceReset()
{
    if (mPool == D3DPOOL_DEFAULT)
    {
        create();
        mDataLost = true;
    }
}

void VertexBuffer::setSize(unsigned vertexCount, unsigned elementMask)
{
    if ((vertexCount == mVertexCount) && (elementMask == mElementMask))
        return;
    
    mVertexCount = vertexCount;
    mElementMask = elementMask;
    
    if (mMorphRangeStart + mMorphRangeCount > mVertexCount)
    {
        mMorphRangeStart = 0;
        mMorphRangeCount = 0;
    }
    
    updateOffsets();
    return create();
}

void VertexBuffer::setData(const void* data)
{
    void* hwData = lock(0, mVertexCount, LOCK_DISCARD);
    memcpy(hwData, data, mVertexCount * mVertexSize);
    unlock();
}

void VertexBuffer::setDataRange(const void* data, unsigned start, unsigned count)
{
    if (!count)
        return;
    
    void* hwData = lock(start, count, LOCK_NORMAL);
    memcpy(hwData, data, count * mVertexSize);
    unlock();
}

bool VertexBuffer::setMorphRange(unsigned start, unsigned count)
{
    if (start + count > mVertexCount)
    {
        LOGERROR("Illegal morph range");
        return false;
    }
    
    mMorphRangeStart = start;
    mMorphRangeCount = count;
    return true;
}

void VertexBuffer::setMorphRangeResetData(const SharedArrayPtr<unsigned char>& data)
{
    mMorphRangeResetData = data;
}

void* VertexBuffer::lock(unsigned start, unsigned count, LockMode mode)
{
    if ((!mObject) && (!mFallbackData))
        EXCEPTION("No vertex buffer created, can not lock");
    
    if (mLocked)
        EXCEPTION("Vertex buffer already locked");
    
    if ((!count) || (start + count > mVertexCount))
        EXCEPTION("Illegal range for locking vertex buffer");
    
    void* hwData = 0;
    
    if (mObject)
    {
        DWORD flags = 0;
        
        if ((mode == LOCK_DISCARD) && (mUsage & D3DUSAGE_DYNAMIC))
            flags = D3DLOCK_DISCARD;
        if (mode == LOCK_NOOVERWRITE)
            flags = D3DLOCK_NOOVERWRITE;
        if (mode == LOCK_READONLY)
            flags = D3DLOCK_READONLY;
        
        if (FAILED(((IDirect3DVertexBuffer9*)mObject)->Lock(start * mVertexSize, count * mVertexSize, &hwData, flags)))
            EXCEPTION("Could not lock vertex buffer");
    }
    else
        hwData = mFallbackData.getPtr() + start * mVertexSize;
    
    mLocked = true;
    return hwData;
}

void VertexBuffer::unlock()
{
    if (mLocked)
    {
        if (mObject)
            ((IDirect3DVertexBuffer9*)mObject)->Unlock();
        mLocked = false;
    }
}

void* VertexBuffer::lockMorphRange()
{
    if (!hasMorphRange())
        EXCEPTION("No vertex morph range defined");
    
    return lock(mMorphRangeStart, mMorphRangeCount, LOCK_DISCARD);
}

void VertexBuffer::resetMorphRange(void* lockedMorphRange)
{
    if ((!lockedMorphRange) || (!mMorphRangeResetData))
        return;
    
    memcpy(lockedMorphRange, mMorphRangeResetData.getPtr(), mMorphRangeCount * mVertexSize);
}

void VertexBuffer::clearDataLost()
{
    mDataLost = false;
}

bool VertexBuffer::isDynamic() const
{
    return mPool == D3DPOOL_DEFAULT;
}

void VertexBuffer::updateOffsets()
{
    unsigned elementOffset = 0;
    for (unsigned i = 0; i < MAX_VERTEX_ELEMENTS; ++i)
    {
        if (mElementMask & (1 << i))
        {
            mElementOffset[i] = elementOffset;
            elementOffset += sElementSize[i];
        }
        else
            mElementOffset[i] = NO_ELEMENT;
    }
    mVertexSize = elementOffset;
}

unsigned long long VertexBuffer::getHash(unsigned streamIndex, unsigned useMask)
{
    unsigned long long bufferHash = mElementMask;
    unsigned long long maskHash;
    if (useMask == MASK_DEFAULT)
        maskHash = ((unsigned long long)mElementMask) * 0x100000000ULL;
    else
        maskHash = ((unsigned long long)useMask) * 0x100000000ULL;
    
    bufferHash |= maskHash;
    bufferHash <<= streamIndex * MAX_VERTEX_ELEMENTS;
    
    return bufferHash;
}

unsigned VertexBuffer::getVertexSize(unsigned mask)
{
    unsigned vertexSize = 0;
    
    for (unsigned i = 0; i < MAX_VERTEX_ELEMENTS; ++i)
    {
        if (mask & (1 << i))
            vertexSize += sElementSize[i];
    }
    
    return vertexSize;
}

void VertexBuffer::create()
{
    release();
    
    if ((!mVertexCount) || (!mElementMask))
        return;
    
    if (mRenderer)
    {
        if (FAILED(mRenderer->getImpl()->getDevice()->CreateVertexBuffer(
            mVertexCount * mVertexSize,
            mUsage,
            0,
            (D3DPOOL)mPool,
            (IDirect3DVertexBuffer9**)&mObject,
            0)))
            EXCEPTION("Could not create vertex buffer");
    }
    else
        mFallbackData = new unsigned char[mVertexCount * mVertexSize];
}

void VertexBuffer::release()
{
    if (mObject)
    {
        if (!mRenderer)
        {
            LOGWARNING("Renderer has expired, skipping release of VertexBuffer");
            return;
        }
        
        for (unsigned i = 0; i < MAX_VERTEX_STREAMS; ++i)
        {
            if (mRenderer->getVertexBuffer(i) == this)
                mRenderer->setVertexBuffer(0);
        }
        
        ((IDirect3DVertexBuffer9*)mObject)->Release();
        mObject = 0;
    }
    
    mFallbackData.reset();
}
