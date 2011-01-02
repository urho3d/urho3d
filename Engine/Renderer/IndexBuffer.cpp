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
#include "IndexBuffer.h"
#include "Log.h"
#include "Renderer.h"
#include "RendererImpl.h"

#include "DebugNew.h"

IndexBuffer::IndexBuffer(Renderer* renderer, bool dynamic) :
    GPUObject(renderer),
    mIndexCount(0),
    mIndexSize(0),
    mLocked(false),
    mDataLost(false)
{
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

IndexBuffer::~IndexBuffer()
{
    release();
}

void IndexBuffer::onDeviceLost()
{
    if (mPool == D3DPOOL_DEFAULT)
        release();
}

void IndexBuffer::onDeviceReset()
{
    if (mPool == D3DPOOL_DEFAULT)
    {
        create();
        mDataLost = true;
    }
}

void IndexBuffer::setSize(unsigned indexCount, bool largeIndices)
{
    setSize(indexCount, largeIndices ? sizeof(unsigned) : sizeof(unsigned short));
}

void IndexBuffer::setSize(unsigned indexCount, unsigned indexSize)
{
    if ((indexSize != sizeof(unsigned)) && (indexSize != sizeof(unsigned short)))
        EXCEPTION("Index size not 2 or 4 bytes");
    
    if ((indexCount == mIndexCount) && (indexSize == mIndexSize))
        return;
    
    mIndexCount = indexCount;
    mIndexSize = indexSize;
    
    create();
}

void IndexBuffer::setData(const void* data)
{
    void* hwData = lock(0, mIndexCount, LOCK_DISCARD);
    memcpy(hwData, data, mIndexCount * mIndexSize);
    unlock();
}

void IndexBuffer::setDataRange(const void* data, unsigned start, unsigned count)
{
    if (!count)
        return;
    
    void* hwData = lock(start, count, LOCK_NORMAL);
    memcpy(hwData, data, count * mIndexSize);
    unlock();
}

void* IndexBuffer::lock(unsigned start, unsigned count, LockMode mode)
{
    if ((!mObject) && (!mFallbackData))
        EXCEPTION("No index buffer created, can not lock");
    
    if (mLocked)
        EXCEPTION("Index buffer already locked");
    
    if ((!count) || (start + count > mIndexCount))
        EXCEPTION("Illegal range for locking index buffer");
    
    void* hwData;
    
    if (mObject)
    {
        DWORD flags = 0;
        
        if ((mode == LOCK_DISCARD) && (mUsage & D3DUSAGE_DYNAMIC))
            flags |= D3DLOCK_DISCARD;
        if (mode == LOCK_NOOVERWRITE)
            flags |= D3DLOCK_NOOVERWRITE;
        if (mode == LOCK_READONLY)
            flags = D3DLOCK_READONLY;
        
        if (FAILED(((IDirect3DIndexBuffer9*)mObject)->Lock(start * mIndexSize, count * mIndexSize, &hwData, flags)))
            EXCEPTION("Could not lock index buffer");
    }
    else
        hwData = mFallbackData.getPtr() + start * mIndexSize;
    
    mLocked = true;
    return hwData;
}

void IndexBuffer::unlock()
{
    if (mLocked)
    {
        if (mObject)
            ((IDirect3DIndexBuffer9*)mObject)->Unlock();
        mLocked = false;
    }
}

void IndexBuffer::clearDataLost()
{
    mDataLost = false;
}

bool IndexBuffer::isDynamic() const
{
    return mPool == D3DPOOL_DEFAULT;
}

bool IndexBuffer::getUsedVertexRange(unsigned start, unsigned count, unsigned& minVertex, unsigned& vertexCount)
{
    void* data = 0;
    
    try
    {
        data = lock(start, count, LOCK_READONLY);
    }
    catch (...)
    {
        return false;
    }
    
    minVertex = M_MAX_UNSIGNED;
    unsigned maxVertex = 0;
    
    if (mIndexSize == sizeof(unsigned))
    {
        unsigned* indices = (unsigned*)data;
            
        for (unsigned i = 0; i < count; ++i)
        {
            if (indices[i] < minVertex)
                minVertex = indices[i];
            if (indices[i] > maxVertex)
                maxVertex = indices[i];
        }
    }
    else
    {
        unsigned short* indices = (unsigned short*)data;
            
        for (unsigned i = 0; i < count; ++i)
        {
            if (indices[i] < minVertex)
                minVertex = indices[i];
            if (indices[i] > maxVertex)
                maxVertex = indices[i];
        }
    }
    
    vertexCount = maxVertex - minVertex + 1;
    
    unlock();
    return true;
}

void IndexBuffer::create()
{
    release();
    
    if (!mIndexCount)
        return;
    
    if (mRenderer)
    {
        if (FAILED(mRenderer->getImpl()->getDevice()->CreateIndexBuffer(
            mIndexCount * mIndexSize,
            mUsage,
            mIndexSize == sizeof(unsigned) ? D3DFMT_INDEX32 : D3DFMT_INDEX16,
            (D3DPOOL)mPool,
            (IDirect3DIndexBuffer9**)&mObject,
            0)))
            EXCEPTION("Could not create index buffer");
    }
    else
        mFallbackData = new unsigned char[mIndexCount * mIndexSize];
}

void IndexBuffer::release()
{
    if (mObject)
    {
        if (!mRenderer)
        {
            LOGWARNING("Renderer has expired, skipping release of IndexBuffer");
            return;
        }
        
        if (mRenderer->getIndexBuffer() == this)
            mRenderer->setIndexBuffer(0);
        
        ((IDirect3DIndexBuffer9*)mObject)->Release();
        mObject = 0;
    }
    
    mFallbackData.reset();
}
