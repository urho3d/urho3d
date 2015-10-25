//
// Copyright (c) 2008-2015 the Urho3D project.
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

#include "../../Precompiled.h"

#include "../../Graphics/Graphics.h"
#include "../../Graphics/GraphicsImpl.h"
#include "../../Graphics/VertexBuffer.h"
#include "../../IO/Log.h"

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

const char* VertexBuffer::elementSemantics[] =
{
    "POSITION",
    "NORMAL",
    "COLOR",
    "TEXCOORD",
    "TEXCOORD",
    "TEXCOORD",
    "TEXCOORD",
    "TANGENT",
    "BLENDWEIGHT",
    "BLENDINDICES",
    "TEXCOORD",
    "TEXCOORD",
    "TEXCOORD"
};

const unsigned VertexBuffer::elementSemanticIndices[] =
{
    0,
    0,
    0,
    0,
    1,
    0,
    1,
    0,
    0,
    0,
    2,
    3,
    4
};

const unsigned VertexBuffer::elementFormats[] =
{
    DXGI_FORMAT_R32G32B32_FLOAT,
    DXGI_FORMAT_R32G32B32_FLOAT,
    DXGI_FORMAT_R8G8B8A8_UNORM,
    DXGI_FORMAT_R32G32_FLOAT,
    DXGI_FORMAT_R32G32_FLOAT,
    DXGI_FORMAT_R32G32B32_FLOAT,
    DXGI_FORMAT_R32G32B32_FLOAT,
    DXGI_FORMAT_R32G32B32A32_FLOAT,
    DXGI_FORMAT_R32G32B32A32_FLOAT,
    DXGI_FORMAT_R8G8B8A8_UINT,
    DXGI_FORMAT_R32G32B32A32_FLOAT,
    DXGI_FORMAT_R32G32B32A32_FLOAT,
    DXGI_FORMAT_R32G32B32A32_FLOAT
};

VertexBuffer::VertexBuffer(Context* context, bool forceHeadless) :
    Object(context),
    GPUObject(forceHeadless ? (Graphics*)0 : GetSubsystem<Graphics>()),
    vertexCount_(0),
    elementMask_(0),
    lockState_(LOCK_NONE),
    lockStart_(0),
    lockCount_(0),
    lockScratchData_(0),
    dynamic_(false),
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

        ((ID3D11Buffer*)object_)->Release();
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

    dynamic_ = dynamic;
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
        URHO3D_LOGERROR("Null pointer for vertex buffer data");
        return false;
    }

    if (!vertexSize_)
    {
        URHO3D_LOGERROR("Vertex elements not defined, can not set vertex buffer data");
        return false;
    }

    if (shadowData_ && data != shadowData_.Get())
        memcpy(shadowData_.Get(), data, vertexCount_ * vertexSize_);

    if (object_)
    {
        if (dynamic_)
        {
            void* hwData = MapBuffer(0, vertexCount_, true);
            if (hwData)
            {
                memcpy(hwData, data, vertexCount_ * vertexSize_);
                UnmapBuffer();
            }
            else
                return false;
        }
        else
        {
            D3D11_BOX destBox;
            destBox.left = 0;
            destBox.right = vertexCount_ * vertexSize_;
            destBox.top = 0;
            destBox.bottom = 1;
            destBox.front = 0;
            destBox.back = 1;

            graphics_->GetImpl()->GetDeviceContext()->UpdateSubresource((ID3D11Buffer*)object_, 0, &destBox, data, 0, 0);
        }
    }

    return true;
}

bool VertexBuffer::SetDataRange(const void* data, unsigned start, unsigned count, bool discard)
{
    if (start == 0 && count == vertexCount_)
        return SetData(data);

    if (!data)
    {
        URHO3D_LOGERROR("Null pointer for vertex buffer data");
        return false;
    }

    if (!vertexSize_)
    {
        URHO3D_LOGERROR("Vertex elements not defined, can not set vertex buffer data");
        return false;
    }

    if (start + count > vertexCount_)
    {
        URHO3D_LOGERROR("Illegal range for setting new vertex buffer data");
        return false;
    }

    if (!count)
        return true;

    if (shadowData_ && shadowData_.Get() + start * vertexSize_ != data)
        memcpy(shadowData_.Get() + start * vertexSize_, data, count * vertexSize_);

    if (object_)
    {
        if (dynamic_)
        {
            void* hwData = MapBuffer(start, count, discard);
            if (hwData)
            {
                memcpy(hwData, data, count * vertexSize_);
                UnmapBuffer();
            }
            else
                return false;
        }
        else
        {
            D3D11_BOX destBox;
            destBox.left = start * vertexSize_;
            destBox.right = destBox.left + count * vertexSize_;
            destBox.top = 0;
            destBox.bottom = 1;
            destBox.front = 0;
            destBox.back = 1;

            graphics_->GetImpl()->GetDeviceContext()->UpdateSubresource((ID3D11Buffer*)object_, 0, &destBox, data, 0, 0);
        }
    }

    return true;
}

void* VertexBuffer::Lock(unsigned start, unsigned count, bool discard)
{
    if (lockState_ != LOCK_NONE)
    {
        URHO3D_LOGERROR("Vertex buffer already locked");
        return 0;
    }

    if (!vertexSize_)
    {
        URHO3D_LOGERROR("Vertex elements not defined, can not lock vertex buffer");
        return 0;
    }

    if (start + count > vertexCount_)
    {
        URHO3D_LOGERROR("Illegal range for locking vertex buffer");
        return 0;
    }

    if (!count)
        return 0;

    lockStart_ = start;
    lockCount_ = count;

    // Because shadow data must be kept in sync, can only lock hardware buffer if not shadowed
    if (object_ && !shadowData_ && dynamic_)
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

    default: break;
    }
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
        D3D11_BUFFER_DESC bufferDesc;
        memset(&bufferDesc, 0, sizeof bufferDesc);
        bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
        bufferDesc.CPUAccessFlags = dynamic_ ? D3D11_CPU_ACCESS_WRITE : 0;
        bufferDesc.Usage = dynamic_ ? D3D11_USAGE_DYNAMIC : D3D11_USAGE_DEFAULT;
        bufferDesc.ByteWidth = (UINT)(vertexCount_ * vertexSize_);

        graphics_->GetImpl()->GetDevice()->CreateBuffer(&bufferDesc, 0, (ID3D11Buffer**)&object_);

        if (!object_)
        {
            URHO3D_LOGERROR("Failed to create vertex buffer");
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
        D3D11_MAPPED_SUBRESOURCE mappedData;
        mappedData.pData = 0;

        graphics_->GetImpl()->GetDeviceContext()->Map((ID3D11Buffer*)object_, 0, discard ? D3D11_MAP_WRITE_DISCARD :
            D3D11_MAP_WRITE, 0, &mappedData);
        hwData = mappedData.pData;
        if (!hwData)
            URHO3D_LOGERROR("Failed to map vertex buffer");
        else
            lockState_ = LOCK_HARDWARE;
    }

    return hwData;
}

void VertexBuffer::UnmapBuffer()
{
    if (object_ && lockState_ == LOCK_HARDWARE)
    {
        graphics_->GetImpl()->GetDeviceContext()->Unmap((ID3D11Buffer*)object_, 0);
        lockState_ = LOCK_NONE;
    }
}

}
