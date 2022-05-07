// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

#include "../../Precompiled.h"

#include "../../Core/Context.h"
#include "../../Graphics/Graphics.h"
#include "../../GraphicsAPI/Direct3D9/D3D9GraphicsImpl.h"
#include "../../GraphicsAPI/IndexBuffer.h"
#include "../../IO/Log.h"

#include "../../DebugNew.h"

namespace Urho3D
{

void IndexBuffer::OnDeviceLost_D3D9()
{
    // Dynamic buffers are in the default pool and need to be released on device loss
    if (dynamic_)
        Release_D3D9();
}

void IndexBuffer::OnDeviceReset_D3D9()
{
    // Dynamic buffers are in the default pool and need to be recreated after device reset
    if (dynamic_ || !object_.ptr_)
    {
        Create_D3D9();
        dataLost_ = !UpdateToGPU_D3D9();
    }
    else if (dataPending_)
        dataLost_ = !UpdateToGPU_D3D9();

    dataPending_ = false;
}

void IndexBuffer::Release_D3D9()
{
    Unlock_D3D9();

    if (graphics_ && graphics_->GetIndexBuffer() == this)
        graphics_->SetIndexBuffer(nullptr);

    URHO3D_SAFE_RELEASE(object_.ptr_);
}

bool IndexBuffer::SetData_D3D9(const void* data)
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

        void* hwData = MapBuffer_D3D9(0, indexCount_, true);
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

bool IndexBuffer::SetDataRange_D3D9(const void* data, unsigned start, unsigned count, bool discard)
{
    if (start == 0 && count == indexCount_)
        return SetData_D3D9(data);

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

        void* hwData = MapBuffer_D3D9(start, count, discard);
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

void* IndexBuffer::Lock_D3D9(unsigned start, unsigned count, bool discard)
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
        return MapBuffer_D3D9(start, count, discard);
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

void IndexBuffer::Unlock_D3D9()
{
    switch (lockState_)
    {
    case LOCK_HARDWARE:
        UnmapBuffer();
        break;

    case LOCK_SHADOW:
        SetDataRange_D3D9(shadowData_.Get() + lockStart_ * indexSize_, lockStart_, lockCount_);
        lockState_ = LOCK_NONE;
        break;

    case LOCK_SCRATCH:
        SetDataRange_D3D9(lockScratchData_, lockStart_, lockCount_);
        if (graphics_)
            graphics_->FreeScratchBuffer(lockScratchData_);
        lockScratchData_ = nullptr;
        lockState_ = LOCK_NONE;
        break;

    default: break;
    }
}

bool IndexBuffer::Create_D3D9()
{
    Release_D3D9();

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

        IDirect3DDevice9* device = graphics_->GetImpl_D3D9()->GetDevice();
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

bool IndexBuffer::UpdateToGPU_D3D9()
{
    if (object_.ptr_ && shadowData_)
        return SetData_D3D9(shadowData_.Get());
    else
        return false;
}

void* IndexBuffer::MapBuffer_D3D9(unsigned start, unsigned count, bool discard)
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

void IndexBuffer::UnmapBuffer_D3D9()
{
    if (object_.ptr_ && lockState_ == LOCK_HARDWARE)
    {
        ((IDirect3DIndexBuffer9*)object_.ptr_)->Unlock();
        lockState_ = LOCK_NONE;
    }
}

}
