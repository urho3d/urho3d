//
// Copyright (c) 2008-2014 the Urho3D project.
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

#include "../../Graphics/Graphics.h"
#include "../../Graphics/GraphicsImpl.h"
#include "../../IO/Log.h"
#include "../../Graphics/VertexBuffer.h"

#include "../../DebugNew.h"

namespace Urho3D
{

const unsigned VertexBuffer::elementSize[] =
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
    4 * sizeof(float), // Instancematrix1
    4 * sizeof(float), // Instancematrix2
    4 * sizeof(float) // Instancematrix3
};

VertexBuffer::VertexBuffer(Context* context) :
    Object(context),
    GPUObject(GetSubsystem<Graphics>()),
    vertexCount_(0),
    elementMask_(0),
    pool_(D3DPOOL_MANAGED),
    usage_(0),
    lockState_(LOCK_NONE),
    lockStart_(0),
    lockCount_(0),
    lockScratchData_(0),
    shadowed_(false)
{
    UpdateOffsets();
    
    // Force shadowing mode if graphics subsystem does not exist
    if (!graphics_)
        shadowed_ = true;
}

VertexBuffer::~VertexBuffer()
{
    Release();
}

void VertexBuffer::OnDeviceLost()
{
    if (pool_ == D3DPOOL_DEFAULT)
        Release();
}

void VertexBuffer::OnDeviceReset()
{
    if (pool_ == D3DPOOL_DEFAULT || !object_)
    {
        Create();
        dataLost_ = !UpdateToGPU();
    }
    else if (dataPending_)
        dataLost_ = !UpdateToGPU();
    
    dataPending_ = false;
}

void VertexBuffer::Release()
{
    Unlock();
    
    if (object_)
    {
        if (!graphics_)
            return;
        
        for (unsigned i = 0; i < MAX_VERTEX_STREAMS; ++i)
        {
            if (graphics_->GetVertexBuffer(i) == this)
                graphics_->SetVertexBuffer(0);
        }
        
        ((IDirect3DVertexBuffer9*)object_)->Release();
        object_ = 0;
    }
}

void VertexBuffer::SetShadowed(bool enable)
{
    // If no graphics subsystem, can not disable shadowing
    if (!graphics_)
        enable = true;
    
    if (enable != shadowed_)
    {
        if (enable && vertexSize_ && vertexCount_)
            shadowData_ = new unsigned char[vertexCount_ * vertexSize_];
        else
            shadowData_.Reset();
        
        shadowed_ = enable;
    }
}

bool VertexBuffer::SetSize(unsigned vertexCount, unsigned elementMask, bool dynamic)
{
    Unlock();
    
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
    
    vertexCount_ = vertexCount;
    elementMask_ = elementMask;
    
    UpdateOffsets();
    
    if (shadowed_ && vertexCount_ && vertexSize_)
        shadowData_ = new unsigned char[vertexCount_ * vertexSize_];
    else
        shadowData_.Reset();
    
    return Create();
}

bool VertexBuffer::SetData(const void* data)
{
    if (!data)
    {
        LOGERROR("Null pointer for vertex buffer data");
        return false;
    }
    
    if (!vertexSize_)
    {
        LOGERROR("Vertex elements not defined, can not set vertex buffer data");
        return false;
    }
    
    if (shadowData_ && data != shadowData_.Get())
        memcpy(shadowData_.Get(), data, vertexCount_ * vertexSize_);
    
    if (object_)
    {
        if (graphics_->IsDeviceLost())
        {
            LOGWARNING("Vertex buffer data assignment while device is lost");
            dataPending_ = true;
            return true;
        }
        
        void* hwData = MapBuffer(0, vertexCount_, true);
        if (hwData)
        {
            memcpy(hwData, data, vertexCount_ * vertexSize_);
            UnmapBuffer();
        }
        else
            return false;
    }
    
    dataLost_ = false;
    return true;
}

bool VertexBuffer::SetDataRange(const void* data, unsigned start, unsigned count, bool discard)
{
    if (start == 0 && count == vertexCount_)
        return SetData(data);
    
    if (!data)
    {
        LOGERROR("Null pointer for vertex buffer data");
        return false;
    }
    
    if (!vertexSize_)
    {
        LOGERROR("Vertex elements not defined, can not set vertex buffer data");
        return false;
    }
    
    if (start + count > vertexCount_)
    {
        LOGERROR("Illegal range for setting new vertex buffer data");
        return false;
    }
    
    if (!count)
        return true;
    
    if (shadowData_ && shadowData_.Get() + start * vertexSize_ != data)
        memcpy(shadowData_.Get() + start * vertexSize_, data, count * vertexSize_);
    
    if (object_)
    {
        if (graphics_->IsDeviceLost())
        {
            LOGWARNING("Vertex buffer data assignment while device is lost");
            dataPending_ = true;
            return true;
        }
        
        void* hwData = MapBuffer(start, count, discard);
        if (hwData)
        {
            memcpy(hwData, data, count * vertexSize_);
            UnmapBuffer();
        }
        else
            return false;
    }

    return true;
}

void* VertexBuffer::Lock(unsigned start, unsigned count, bool discard)
{
    if (lockState_ != LOCK_NONE)
    {
        LOGERROR("Vertex buffer already locked");
        return 0;
    }
    
    if (!vertexSize_)
    {
        LOGERROR("Vertex elements not defined, can not lock vertex buffer");
        return 0;
    }
    
    if (start + count > vertexCount_)
    {
        LOGERROR("Illegal range for locking vertex buffer");
        return 0;
    }
    
    if (!count)
        return 0;
    
    lockStart_ = start;
    lockCount_ = count;
    
    // Because shadow data must be kept in sync, can only lock hardware buffer if not shadowed
    if (object_ && !shadowData_ && !graphics_->IsDeviceLost())
        return MapBuffer(start, count, discard);
    else if (shadowData_)
    {
        lockState_ = LOCK_SHADOW;
        return shadowData_.Get() + start * vertexSize_;
    }
    else if (graphics_)
    {
        lockState_ = LOCK_SCRATCH;
        lockScratchData_ = graphics_->ReserveScratchBuffer(count * vertexSize_);
        return lockScratchData_;
    }
    else
        return 0;
}

void VertexBuffer::Unlock()
{
    switch (lockState_)
    {
    case LOCK_HARDWARE:
        UnmapBuffer();
        break;
        
    case LOCK_SHADOW:
        SetDataRange(shadowData_.Get() + lockStart_ * vertexSize_, lockStart_, lockCount_);
        lockState_ = LOCK_NONE;
        break;
        
    case LOCK_SCRATCH:
        SetDataRange(lockScratchData_, lockStart_, lockCount_);
        if (graphics_)
            graphics_->FreeScratchBuffer(lockScratchData_);
        lockScratchData_ = 0;
        lockState_ = LOCK_NONE;
        break;
    }
}

bool VertexBuffer::IsDynamic() const
{
    return pool_ == D3DPOOL_DEFAULT;
}

void VertexBuffer::UpdateOffsets()
{
    unsigned elementOffset = 0;
    for (unsigned i = 0; i < MAX_VERTEX_ELEMENTS; ++i)
    {
        if (elementMask_ & (1 << i))
        {
            elementOffset_[i] = elementOffset;
            elementOffset += elementSize[i];
        }
        else
            elementOffset_[i] = NO_ELEMENT;
    }
    vertexSize_ = elementOffset;
}

unsigned long long VertexBuffer::GetBufferHash(unsigned streamIndex, unsigned useMask)
{
    unsigned long long bufferHash = elementMask_;
    unsigned long long maskHash;
    if (useMask == MASK_DEFAULT)
        maskHash = ((unsigned long long)elementMask_) * 0x100000000ULL;
    else
        maskHash = ((unsigned long long)useMask) * 0x100000000ULL;
    
    bufferHash |= maskHash;
    bufferHash <<= streamIndex * MAX_VERTEX_ELEMENTS;
    
    return bufferHash;
}

unsigned VertexBuffer::GetVertexSize(unsigned elementMask)
{
    unsigned vertexSize = 0;
    
    for (unsigned i = 0; i < MAX_VERTEX_ELEMENTS; ++i)
    {
        if (elementMask & (1 << i))
            vertexSize += elementSize[i];
    }
    
    return vertexSize;
}

unsigned VertexBuffer::GetElementOffset(unsigned elementMask, VertexElement element)
{
    unsigned offset = 0;
    
    for (unsigned i = 0; i < MAX_VERTEX_ELEMENTS; ++i)
    {
        if (i == element)
            break;
        
        if (elementMask & (1 << i))
            offset += elementSize[i];
    }
    
    return offset;
}

bool VertexBuffer::Create()
{
    Release();
    
    if (!vertexCount_ || !elementMask_)
        return true;
    
    if (graphics_)
    {
        if (graphics_->IsDeviceLost())
        {
            LOGWARNING("Vertex buffer creation while device is lost");
            return true;
        }
        
        IDirect3DDevice9* device = graphics_->GetImpl()->GetDevice();
        if (!device || FAILED(device->CreateVertexBuffer(
            vertexCount_ * vertexSize_,
            usage_,
            0,
            (D3DPOOL)pool_,
            (IDirect3DVertexBuffer9**)&object_,
            0)))
        {
            LOGERROR("Could not create vertex buffer");
            return false;
        }
    }
    
    return true;
}

bool VertexBuffer::UpdateToGPU()
{
    if (object_ && shadowData_)
        return SetData(shadowData_.Get());
    else
        return false;
}

void* VertexBuffer::MapBuffer(unsigned start, unsigned count, bool discard)
{
    void* hwData = 0;
    
    if (object_)
    {
        DWORD flags = 0;
        
        if (discard && usage_ & D3DUSAGE_DYNAMIC)
            flags = D3DLOCK_DISCARD;
        
        if (FAILED(((IDirect3DVertexBuffer9*)object_)->Lock(start * vertexSize_, count * vertexSize_, &hwData, flags)))
            LOGERROR("Could not lock vertex buffer");
        else
            lockState_ = LOCK_HARDWARE;
    }
    
    return hwData;
}

void VertexBuffer::UnmapBuffer()
{
    if (object_ && lockState_ == LOCK_HARDWARE)
    {
        ((IDirect3DVertexBuffer9*)object_)->Unlock();
        lockState_ = LOCK_NONE;
    }
}

}
