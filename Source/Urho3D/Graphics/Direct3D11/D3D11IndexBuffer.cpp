//
// Copyright (c) 2008-2020 the Urho3D project.
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

#include "../../Core/Context.h"
#include "../../Graphics/Graphics.h"
#include "../../Graphics/GraphicsImpl.h"
#include "../../Graphics/IndexBuffer.h"
#include "../../IO/Log.h"

#include "../../DebugNew.h"

namespace Urho3D
{

void IndexBuffer::OnDeviceLost()
{
    // No-op on Direct3D11
}

void IndexBuffer::OnDeviceReset()
{
    // No-op on Direct3D11
}

void IndexBuffer::Release()
{
    Unlock();

    if (graphics_ && graphics_->GetIndexBuffer() == this)
        graphics_->SetIndexBuffer(nullptr);

    URHO3D_SAFE_RELEASE(object_.ptr_);
}

bool IndexBuffer::SetData(const void* data)
{
    if (!data)
    {
        URHO3D_LOGERROR("Null pointer for index buffer data");
        return false;
    }

    if (!indexSize_)
    {
        URHO3D_LOGERROR("Index size not defined, can not set index buffer data");
        return false;
    }

    if (shadowData_ && data != shadowData_.Get())
        memcpy(shadowData_.Get(), data, indexCount_ * indexSize_);

    if (object_.ptr_)
    {
        if (dynamic_)
        {
            void* hwData = MapBuffer(0, indexCount_, true);
            if (hwData)
            {
                memcpy(hwData, data, indexCount_ * indexSize_);
                UnmapBuffer();
            }
            else
                return false;
        }
        else
        {
            D3D11_BOX destBox;
            destBox.left = 0;
            destBox.right = indexCount_ * indexSize_;
            destBox.top = 0;
            destBox.bottom = 1;
            destBox.front = 0;
            destBox.back = 1;

            graphics_->GetImpl()->GetDeviceContext()->UpdateSubresource((ID3D11Buffer*)object_.ptr_, 0, &destBox, data, 0, 0);
        }
    }

    return true;
}

bool IndexBuffer::SetDataRange(const void* data, unsigned start, unsigned count, bool discard)
{
    if (start == 0 && count == indexCount_)
        return SetData(data);

    if (!data)
    {
        URHO3D_LOGERROR("Null pointer for index buffer data");
        return false;
    }

    if (!indexSize_)
    {
        URHO3D_LOGERROR("Index size not defined, can not set index buffer data");
        return false;
    }

    if (start + count > indexCount_)
    {
        URHO3D_LOGERROR("Illegal range for setting new index buffer data");
        return false;
    }

    if (!count)
        return true;

    if (shadowData_ && shadowData_.Get() + start * indexSize_ != data)
        memcpy(shadowData_.Get() + start * indexSize_, data, count * indexSize_);

    if (object_.ptr_)
    {
        if (dynamic_)
        {
            void* hwData = MapBuffer(start, count, discard);
            if (hwData)
            {
                memcpy(hwData, data, count * indexSize_);
                UnmapBuffer();
            }
            else
                return false;
        }
        else
        {
            D3D11_BOX destBox;
            destBox.left = start * indexSize_;
            destBox.right = destBox.left + count * indexSize_;
            destBox.top = 0;
            destBox.bottom = 1;
            destBox.front = 0;
            destBox.back = 1;

            graphics_->GetImpl()->GetDeviceContext()->UpdateSubresource((ID3D11Buffer*)object_.ptr_, 0, &destBox, data, 0, 0);
        }
    }

    return true;
}

void* IndexBuffer::Lock(unsigned start, unsigned count, bool discard)
{
    if (lockState_ != LOCK_NONE)
    {
        URHO3D_LOGERROR("Index buffer already locked");
        return nullptr;
    }

    if (!indexSize_)
    {
        URHO3D_LOGERROR("Index size not defined, can not lock index buffer");
        return nullptr;
    }

    if (start + count > indexCount_)
    {
        URHO3D_LOGERROR("Illegal range for locking index buffer");
        return nullptr;
    }

    if (!count)
        return nullptr;

    lockStart_ = start;
    lockCount_ = count;

    // Because shadow data must be kept in sync, can only lock hardware buffer if not shadowed
    if (object_.ptr_ && !shadowData_ && dynamic_)
        return MapBuffer(start, count, discard);
    else if (shadowData_)
    {
        lockState_ = LOCK_SHADOW;
        return shadowData_.Get() + start * indexSize_;
    }
    else if (graphics_)
    {
        lockState_ = LOCK_SCRATCH;
        lockScratchData_ = graphics_->ReserveScratchBuffer(count * indexSize_);
        return lockScratchData_;
    }
    else
        return nullptr;
}

void IndexBuffer::Unlock()
{
    switch (lockState_)
    {
    case LOCK_HARDWARE:
        UnmapBuffer();
        break;

    case LOCK_SHADOW:
        SetDataRange(shadowData_.Get() + lockStart_ * indexSize_, lockStart_, lockCount_);
        lockState_ = LOCK_NONE;
        break;

    case LOCK_SCRATCH:
        SetDataRange(lockScratchData_, lockStart_, lockCount_);
        if (graphics_)
            graphics_->FreeScratchBuffer(lockScratchData_);
        lockScratchData_ = nullptr;
        lockState_ = LOCK_NONE;
        break;

    default: break;
    }
}

bool IndexBuffer::Create()
{
    Release();

    if (!indexCount_)
        return true;

    if (graphics_)
    {
        D3D11_BUFFER_DESC bufferDesc;
        memset(&bufferDesc, 0, sizeof bufferDesc);
        bufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
        bufferDesc.CPUAccessFlags = dynamic_ ? D3D11_CPU_ACCESS_WRITE : 0;
        bufferDesc.Usage = dynamic_ ? D3D11_USAGE_DYNAMIC : D3D11_USAGE_DEFAULT;
        bufferDesc.ByteWidth = (UINT)(indexCount_ * indexSize_);

        HRESULT hr = graphics_->GetImpl()->GetDevice()->CreateBuffer(&bufferDesc, nullptr, (ID3D11Buffer**)&object_.ptr_);
        if (FAILED(hr))
        {
            URHO3D_SAFE_RELEASE(object_.ptr_);
            URHO3D_LOGD3DERROR("Failed to create index buffer", hr);
            return false;
        }
    }

    return true;
}

bool IndexBuffer::UpdateToGPU()
{
    if (object_.ptr_ && shadowData_)
        return SetData(shadowData_.Get());
    else
        return false;
}

void* IndexBuffer::MapBuffer(unsigned start, unsigned count, bool discard)
{
    void* hwData = nullptr;

    if (object_.ptr_)
    {
        D3D11_MAPPED_SUBRESOURCE mappedData;
        mappedData.pData = nullptr;

        HRESULT hr = graphics_->GetImpl()->GetDeviceContext()->Map((ID3D11Buffer*)object_.ptr_, 0, discard ? D3D11_MAP_WRITE_DISCARD :
            D3D11_MAP_WRITE, 0, &mappedData);
        if (FAILED(hr) || !mappedData.pData)
            URHO3D_LOGD3DERROR("Failed to map index buffer", hr);
        else
        {
            hwData = mappedData.pData;
            lockState_ = LOCK_HARDWARE;
        }
    }

    return hwData;
}

void IndexBuffer::UnmapBuffer()
{
    if (object_.ptr_ && lockState_ == LOCK_HARDWARE)
    {
        graphics_->GetImpl()->GetDeviceContext()->Unmap((ID3D11Buffer*)object_.ptr_, 0);
        lockState_ = LOCK_NONE;
    }
}

}
