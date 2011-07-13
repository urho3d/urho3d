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
#include "Graphics.h"
#include "GraphicsImpl.h"
#include "Log.h"
#include "VertexBuffer.h"

#include "DebugNew.h"

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

const String VertexBuffer::elementName[] = 
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
    "Instancematrix1",
    "Instancematrix2",
    "Instancematrix3"
};

OBJECTTYPESTATIC(VertexBuffer);

VertexBuffer::VertexBuffer(Context* context) :
    Object(context),
    GPUObject(GetSubsystem<Graphics>()),
    pool_(D3DPOOL_MANAGED),
    usage_(0),
    vertexCount_(0),
    elementMask_(0),
    morphRangeStart_(0),
    morphRangeCount_(0),
    locked_(false),
    dataLost_(false)
{
    UpdateOffsets();
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
    if (pool_ == D3DPOOL_DEFAULT)
    {
        Create();
        dataLost_ = true;
    }
}

void VertexBuffer::Release()
{
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
    
    fallbackData_.Reset();
}

bool VertexBuffer::SetSize(unsigned vertexCount, unsigned elementMask, bool dynamic)
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
    
    vertexCount_ = vertexCount;
    elementMask_ = elementMask;
    
    if (morphRangeStart_ + morphRangeCount_ > vertexCount_)
    {
        morphRangeStart_ = 0;
        morphRangeCount_ = 0;
    }
    
    UpdateOffsets();
    return Create();
}

bool VertexBuffer::SetData(const void* data)
{
    void* hwData = Lock(0, vertexCount_, LOCK_DISCARD);
    if (!hwData)
        return false;
    
    memcpy(hwData, data, vertexCount_ * vertexSize_);
    Unlock();
    return true;
}

bool VertexBuffer::SetDataRange(const void* data, unsigned start, unsigned count)
{
    if (!count)
        return true;
    
    void* hwData = Lock(start, count, LOCK_NORMAL);
    if (!hwData)
        return false;
    
    memcpy(hwData, data, count * vertexSize_);
    Unlock();
    return true;
}

bool VertexBuffer::SetMorphRange(unsigned start, unsigned count)
{
    if (start + count > vertexCount_)
    {
        LOGERROR("Illegal morph range");
        return false;
    }
    
    morphRangeStart_ = start;
    morphRangeCount_ = count;
    return true;
}

void VertexBuffer::SetMorphRangeResetData(const SharedArrayPtr<unsigned char>& data)
{
    morphRangeResetData_ = data;
}

void* VertexBuffer::Lock(unsigned start, unsigned count, LockMode mode)
{
    if (!object_ && !fallbackData_)
        return 0;

    if (locked_)
    {
        LOGERROR("Vertex buffer already locked");
        return 0;
    }
    
    if (!count || start + count > vertexCount_)
    {
        LOGERROR("Illegal range for locking vertex buffer");
        return 0;
    }
    
    void* hwData = 0;
    
    if (object_)
    {
        DWORD flags = 0;
        
        if (mode == LOCK_DISCARD && usage_ & D3DUSAGE_DYNAMIC)
            flags = D3DLOCK_DISCARD;
        if (mode == LOCK_NOOVERWRITE && usage_ & D3DUSAGE_DYNAMIC)
            flags = D3DLOCK_NOOVERWRITE;
        if (mode == LOCK_READONLY)
            flags = D3DLOCK_READONLY;
        
        if (FAILED(((IDirect3DVertexBuffer9*)object_)->Lock(start * vertexSize_, count * vertexSize_, &hwData, flags)))
        {
            LOGERROR("Could not lock vertex buffer");
            return 0;
        }
    }
    else
        hwData = fallbackData_.RawPtr() + start * vertexSize_;
    
    locked_ = true;
    return hwData;
}

void VertexBuffer::Unlock()
{
    if (locked_)
    {
        if (object_)
            ((IDirect3DVertexBuffer9*)object_)->Unlock();
        locked_ = false;
    }
}

void* VertexBuffer::LockMorphRange()
{
    if (!HasMorphRange())
    {
        LOGERROR("No vertex morph range defined");
        return 0;
    }
    
    return Lock(morphRangeStart_, morphRangeCount_, LOCK_DISCARD);
}

void VertexBuffer::ResetMorphRange(void* lockedMorphRange)
{
    if (!lockedMorphRange || !morphRangeResetData_)
        return;
    
    memcpy(lockedMorphRange, morphRangeResetData_.RawPtr(), morphRangeCount_ * vertexSize_);
}

void VertexBuffer::ClearDataLost()
{
    dataLost_ = false;
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

unsigned long long VertexBuffer::GetHash(unsigned streaindex_, unsigned useMask)
{
    unsigned long long bufferHash = elementMask_;
    unsigned long long maskHash;
    if (useMask == MASK_DEFAULT)
        maskHash = ((unsigned long long)elementMask_) * 0x100000000ULL;
    else
        maskHash = ((unsigned long long)useMask) * 0x100000000ULL;
    
    bufferHash |= maskHash;
    bufferHash <<= streaindex_ * MAX_VERTEX_ELEMENTS;
    
    return bufferHash;
}

unsigned VertexBuffer::GetVertexSize(unsigned mask)
{
    unsigned vertexSize = 0;
    
    for (unsigned i = 0; i < MAX_VERTEX_ELEMENTS; ++i)
    {
        if (mask & (1 << i))
            vertexSize += elementSize[i];
    }
    
    return vertexSize;
}

bool VertexBuffer::Create()
{
    Release();
    
    if (!vertexCount_ || !elementMask_)
        return true;
    
    if (graphics_)
    {
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
    else
        fallbackData_ = new unsigned char[vertexCount_ * vertexSize_];
    
    return true;
}
