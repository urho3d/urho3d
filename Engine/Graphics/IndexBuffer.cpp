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
#include "Context.h"
#include "Graphics.h"
#include "GraphicsImpl.h"
#include "IndexBuffer.h"
#include "Log.h"

#include "DebugNew.h"

OBJECTTYPESTATIC(IndexBuffer);

IndexBuffer::IndexBuffer(Context* context) :
    Object(context),
    GPUObject(GetSubsystem<Graphics>()),
    pool_(D3DPOOL_MANAGED),
    usage_(0),
    indexCount_(0),
    indexSize_(0),
    locked_(false),
    dataLost_(false)
{
}

IndexBuffer::~IndexBuffer()
{
    Release();
}

void IndexBuffer::OnDeviceLost()
{
    if (pool_ == D3DPOOL_DEFAULT)
        Release();
}

void IndexBuffer::OnDeviceReset()
{
    if (pool_ == D3DPOOL_DEFAULT)
    {
        Create();
        dataLost_ = true;
    }
}

void IndexBuffer::Release()
{
    if (object_)
    {
        if (!graphics_)
            return;
        
        if (graphics_->GetIndexBuffer() == this)
            graphics_->SetIndexBuffer(0);
        
        ((IDirect3DIndexBuffer9*)object_)->Release();
        object_ = 0;
    }
    
    fallbackData_.Reset();
}

bool IndexBuffer::SetSize(unsigned indexCount, bool largeIndices, bool dynamic)
{
    return SetSize(indexCount, largeIndices ? sizeof(unsigned) : sizeof(unsigned short), dynamic);
}

bool IndexBuffer::SetSize(unsigned indexCount, unsigned indexSize, bool dynamic)
{
    if ((indexSize != sizeof(unsigned)) && (indexSize != sizeof(unsigned short)))
    {
        LOGERROR("Index size not 2 or 4 bytes");
        return false;
    }
    
    if (dynamic)
    {
        pool_ = D3DPOOL_DEFAULT;
        usage_ = D3DUSAGE_DYNAMIC | D3DUSAGE_WRITEONLY;
    }
    else
    {
        pool_ = D3DPOOL_MANAGED;
        usage_ = 0;
    }
    
    indexCount_ = indexCount;
    indexSize_ = indexSize;
    
    return Create();
}

bool IndexBuffer::SetData(const void* data)
{
    void* hwData = Lock(0, indexCount_, LOCK_DISCARD);
    if (!hwData)
        return false;
    
    memcpy(hwData, data, indexCount_ * indexSize_);
    Unlock();
    return true;
}

bool IndexBuffer::SetDataRange(const void* data, unsigned start, unsigned count)
{
    if (!count)
        return true;
    
    void* hwData = Lock(start, count, LOCK_NORMAL);
    if (!hwData)
        return false;
    
    memcpy(hwData, data, count * indexSize_);
    Unlock();
    return true;
}

void* IndexBuffer::Lock(unsigned start, unsigned count, LockMode mode)
{
    if ((!object_) && (!fallbackData_))
    {
        LOGERROR("No index buffer created, can not lock");
        return 0;
    }
    
    if (locked_)
    {
        LOGERROR("Index buffer already locked");
        return 0;
    }

    if ((!count) || (start + count > indexCount_))
    {
        LOGERROR("Illegal range for locking index buffer");
        return 0;
    }
    
    void* hwData = 0;
    
    if (object_)
    {
        DWORD flags = 0;
        
        if ((mode == LOCK_DISCARD) && (usage_ & D3DUSAGE_DYNAMIC))
            flags |= D3DLOCK_DISCARD;
        if (mode == LOCK_NOOVERWRITE)
            flags |= D3DLOCK_NOOVERWRITE;
        if (mode == LOCK_READONLY)
            flags = D3DLOCK_READONLY;
        
        if (FAILED(((IDirect3DIndexBuffer9*)object_)->Lock(start * indexSize_, count * indexSize_, &hwData, flags)))
        {
            LOGERROR("Could not lock index buffer");
            return 0;
        }
    }
    else
        hwData = fallbackData_.GetPtr() + start * indexSize_;
    
    locked_ = true;
    return hwData;
}

void IndexBuffer::Unlock()
{
    if (locked_)
    {
        if (object_)
            ((IDirect3DIndexBuffer9*)object_)->Unlock();
        locked_ = false;
    }
}

void IndexBuffer::ClearDataLost()
{
    dataLost_ = false;
}

bool IndexBuffer::IsDynamic() const
{
    return pool_ == D3DPOOL_DEFAULT;
}

bool IndexBuffer::GetUsedVertexRange(unsigned start, unsigned count, unsigned& minVertex, unsigned& vertexCount)
{
    void* data = Lock(start, count, LOCK_READONLY);
    if (!data)
        return false;
    
    minVertex = M_MAX_UNSIGNED;
    unsigned maxVertex = 0;
    
    if (indexSize_ == sizeof(unsigned))
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
    
    Unlock();
    return true;
}

bool IndexBuffer::Create()
{
    Release();
    
    if (!indexCount_)
        return true;
    
    if (graphics_)
    {
        IDirect3DDevice9* device = graphics_->GetImpl()->GetDevice();
        if ((!device) || (FAILED(device->CreateIndexBuffer(
            indexCount_ * indexSize_,
            usage_,
            indexSize_ == sizeof(unsigned) ? D3DFMT_INDEX32 : D3DFMT_INDEX16,
            (D3DPOOL)pool_,
            (IDirect3DIndexBuffer9**)&object_,
            0))))
        {
            LOGERROR("Could not create index buffer");
            return false;
        }
    }
    else
        fallbackData_ = new unsigned char[indexCount_ * indexSize_];
    
    return true;
}
