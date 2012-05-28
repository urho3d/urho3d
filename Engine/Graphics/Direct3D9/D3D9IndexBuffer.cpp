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
    shadowed_(false),
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
    {
        Release();
        dataLost_ = true;
    }
}

void IndexBuffer::OnDeviceReset()
{
    if (pool_ == D3DPOOL_DEFAULT)
    {
        Create();
        if (UpdateToGPU())
            dataLost_ = false;
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
}

void IndexBuffer::SetShadowed(bool enable)
{
    // If no graphics subsystem, can not disable shadowing
    if (!graphics_)
        enable = true;
    
    if (enable != shadowed_)
    {
        if (enable && indexSize_ && indexCount_)
            shadowData_ = new unsigned char[indexCount_ * indexSize_];
        else
            shadowData_.Reset();
        
        shadowed_ = enable;
    }
}

bool IndexBuffer::SetSize(unsigned indexCount, bool largeIndices, bool dynamic)
{
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
    indexSize_ = largeIndices ? sizeof(unsigned) : sizeof(unsigned short);
    
    if (shadowed_ && indexCount_ && indexSize_)
        shadowData_ = new unsigned char[indexCount_ * indexSize_];
    else
        shadowData_.Reset();
    
    return Create();
}

bool IndexBuffer::SetData(const void* data)
{
    if (!data)
    {
        LOGERROR("Null pointer for index buffer data");
        return false;
    }
    
    if (object_)
    {
        void* hwData = Lock(0, indexCount_, true);
        if (hwData)
        {
            memcpy(hwData, data, indexCount_ * indexSize_);
            Unlock();
        }
    }
    if (shadowData_ && data != shadowData_.Get())
        memcpy(shadowData_.Get(), data, indexCount_ * indexSize_);
    
    return true;
}

bool IndexBuffer::SetDataRange(const void* data, unsigned start, unsigned count, bool discard)
{
    if (start == 0 && count == indexCount_)
        return SetData(data);
    
    if (!data)
    {
        LOGERROR("Null pointer for index buffer data");
        return false;
    }
    
    if (start + count > indexCount_)
    {
        LOGERROR("Illegal range for setting new index buffer data");
        return false;
    }
    
    if (!count)
        return true;
    
    if (object_)
    {
        void* hwData = Lock(start, count, discard);
        if (hwData)
        {
            memcpy(hwData, data, count * indexSize_);
            Unlock();
        }
    }
    
    if (shadowData_ && shadowData_.Get() + start * indexSize_ != data)
        memcpy(shadowData_.Get() + start * indexSize_, data, count * indexSize_);
    
    return true;
}

bool IndexBuffer::UpdateToGPU()
{
    if (object_ && shadowData_)
        return SetData(shadowData_.Get());
    else
        return false;
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
    if (!shadowData_)
        return false;
    
    minVertex = M_MAX_UNSIGNED;
    unsigned maxVertex = 0;
    
    if (indexSize_ == sizeof(unsigned))
    {
        unsigned* indices = (unsigned*)shadowData_.Get();
        
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
        unsigned short* indices = (unsigned short*)shadowData_.Get();
        
        for (unsigned i = 0; i < count; ++i)
        {
            if (indices[i] < minVertex)
                minVertex = indices[i];
            if (indices[i] > maxVertex)
                maxVertex = indices[i];
        }
    }
    
    vertexCount = maxVertex - minVertex + 1;
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
        if (!device || FAILED(device->CreateIndexBuffer(
            indexCount_ * indexSize_,
            usage_,
            indexSize_ == sizeof(unsigned) ? D3DFMT_INDEX32 : D3DFMT_INDEX16,
            (D3DPOOL)pool_,
            (IDirect3DIndexBuffer9**)&object_,
            0)))
        {
            LOGERROR("Could not create index buffer");
            return false;
        }
    }
    
    return true;
}


void* IndexBuffer::Lock(unsigned start, unsigned count, bool discard)
{
    void* hwData = 0;
    
    if (object_)
    {
        DWORD flags = 0;
        
        if (discard && usage_ & D3DUSAGE_DYNAMIC)
            flags = D3DLOCK_DISCARD;
        
        if (FAILED(((IDirect3DIndexBuffer9*)object_)->Lock(start * indexSize_, count * indexSize_, &hwData, flags)))
        {
            LOGERROR("Could not lock index buffer");
            return 0;
        }
    }
    
    return hwData;
}

void IndexBuffer::Unlock()
{
    if (object_)
        ((IDirect3DIndexBuffer9*)object_)->Unlock();
}
