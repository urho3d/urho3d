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
    // Dynamic buffers are in the default pool and need to be released on device loss
    if (dynamic_)
        Release();
}

void IndexBuffer::OnDeviceReset()
{
    // Dynamic buffers are in the default pool and need to be recreated after device reset
    if (dynamic_ || !object_.ptr_)
    {
        Create();
        dataLost_ = !UpdateToGPU();
    }
    else if (dataPending_)
        dataLost_ = !UpdateToGPU();

    dataPending_ = false;
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
        if (graphics_->IsDeviceLost())
        {
            URHO3D_LOGWARNING("Index buffer data assignment while device is lost");
            dataPending_ = true;
            return true;
        }

        void* hwData = MapBuffer(0, indexCount_, true);
        if (hwData)
        {
            memcpy(hwData, data, indexCount_ * indexSize_);
            UnmapBuffer();
        }
        else
            return false;
    }

    dataLost_ = false;
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
        if (graphics_->IsDeviceLost())
        {
            URHO3D_LOGWARNING("Index buffer data assignment while device is lost");
            dataPending_ = true;
            return true;
        }

        void* hwData = MapBuffer(start, count, discard);
        if (hwData)
        {
            memcpy(hwData, data, count * indexSize_);
            UnmapBuffer();
        }
        else
            return false;
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
    if (object_.ptr_ && !shadowData_ && !graphics_->IsDeviceLost())
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
        if (graphics_->IsDeviceLost())
        {
            URHO3D_LOGWARNING("Index buffer creation while device is lost");
            return true;
        }

        unsigned pool = dynamic_ ? D3DPOOL_DEFAULT : D3DPOOL_MANAGED;
        unsigned d3dUsage = dynamic_ ? D3DUSAGE_DYNAMIC | D3DUSAGE_WRITEONLY : 0;

        IDirect3DDevice9* device = graphics_->GetImpl()->GetDevice();
        HRESULT hr = device->CreateIndexBuffer(
            indexCount_ * indexSize_,
            d3dUsage,
            indexSize_ == sizeof(unsigned) ? D3DFMT_INDEX32 : D3DFMT_INDEX16,
            (D3DPOOL)pool,
            (IDirect3DIndexBuffer9**)&object_,
            nullptr);
        if (FAILED(hr))
        {
            URHO3D_SAFE_RELEASE(object_.ptr_)
            URHO3D_LOGD3DERROR("Could not create index buffer", hr);
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
        DWORD flags = 0;

        if (discard && dynamic_)
            flags = D3DLOCK_DISCARD;

        HRESULT hr = ((IDirect3DIndexBuffer9*)object_.ptr_)->Lock(start * indexSize_, count * indexSize_, &hwData, flags);
        if (FAILED(hr))
            URHO3D_LOGD3DERROR("Could not lock index buffer", hr);
        else
            lockState_ = LOCK_HARDWARE;
    }

    return hwData;
}

void IndexBuffer::UnmapBuffer()
{
    if (object_.ptr_ && lockState_ == LOCK_HARDWARE)
    {
        ((IDirect3DIndexBuffer9*)object_.ptr_)->Unlock();
        lockState_ = LOCK_NONE;
    }
}

}
