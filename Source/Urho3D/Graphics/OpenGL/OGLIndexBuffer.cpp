//
// Copyright (c) 2008-2016 the Urho3D project.
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

IndexBuffer::IndexBuffer(Context* context, bool forceHeadless) :
    Object(context),
    GPUObject(forceHeadless ? (Graphics*)0 : GetSubsystem<Graphics>()),
    indexCount_(0),
    indexSize_(0),
    lockState_(LOCK_NONE),
    lockStart_(0),
    lockCount_(0),
    lockScratchData_(0),
    shadowed_(false),
    dynamic_(false)
{
    // Force shadowing mode if graphics subsystem does not exist
    if (!graphics_)
        shadowed_ = true;
}

IndexBuffer::~IndexBuffer()
{
    Release();
}

void IndexBuffer::OnDeviceReset()
{
    if (!object_)
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

    if (object_)
    {
        if (!graphics_)
            return;

        if (!graphics_->IsDeviceLost())
        {
            if (graphics_->GetIndexBuffer() == this)
                graphics_->SetIndexBuffer(0);

            glDeleteBuffers(1, &object_);
        }

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
        if (enable && indexCount_ && indexSize_)
            shadowData_ = new unsigned char[indexCount_ * indexSize_];
        else
            shadowData_.Reset();

        shadowed_ = enable;
    }
}

bool IndexBuffer::SetSize(unsigned indexCount, bool largeIndices, bool dynamic)
{
    Unlock();

    dynamic_ = dynamic;
    indexCount_ = indexCount;
    indexSize_ = (unsigned)(largeIndices ? sizeof(unsigned) : sizeof(unsigned short));

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

    if (object_)
    {
        if (!graphics_->IsDeviceLost())
        {
            graphics_->SetIndexBuffer(this);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexCount_ * indexSize_, data, dynamic_ ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW);
        }
        else
        {
            URHO3D_LOGWARNING("Index buffer data assignment while device is lost");
            dataPending_ = true;
        }
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

    if (object_)
    {
        if (!graphics_->IsDeviceLost())
        {
            graphics_->SetIndexBuffer(this);
            if (!discard || start != 0)
                glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, start * indexSize_, count * indexSize_, data);
            else
                glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * indexSize_, data, dynamic_ ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW);
        }
        else
        {
            URHO3D_LOGWARNING("Index buffer data assignment while device is lost");
            dataPending_ = true;
        }
    }

    return true;
}

void* IndexBuffer::Lock(unsigned start, unsigned count, bool discard)
{
    if (lockState_ != LOCK_NONE)
    {
        URHO3D_LOGERROR("Index buffer already locked");
        return 0;
    }

    if (!indexSize_)
    {
        URHO3D_LOGERROR("Index size not defined, can not lock index buffer");
        return 0;
    }

    if (start + count > indexCount_)
    {
        URHO3D_LOGERROR("Illegal range for locking index buffer");
        return 0;
    }

    if (!count)
        return 0;

    lockStart_ = start;
    lockCount_ = count;

    if (shadowData_)
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
        return 0;
}

void IndexBuffer::Unlock()
{
    switch (lockState_)
    {
    case LOCK_SHADOW:
        SetDataRange(shadowData_.Get() + lockStart_ * indexSize_, lockStart_, lockCount_);
        lockState_ = LOCK_NONE;
        break;

    case LOCK_SCRATCH:
        SetDataRange(lockScratchData_, lockStart_, lockCount_);
        if (graphics_)
            graphics_->FreeScratchBuffer(lockScratchData_);
        lockScratchData_ = 0;
        lockState_ = LOCK_NONE;
        break;

    default:
        break;
    }
}

bool IndexBuffer::GetUsedVertexRange(unsigned start, unsigned count, unsigned& minVertex, unsigned& vertexCount)
{
    if (!shadowData_)
    {
        URHO3D_LOGERROR("Used vertex range can only be queried from an index buffer with shadow data");
        return false;
    }

    if (start + count > indexCount_)
    {
        URHO3D_LOGERROR("Illegal index range for querying used vertices");
        return false;
    }

    minVertex = M_MAX_UNSIGNED;
    unsigned maxVertex = 0;

    if (indexSize_ == sizeof(unsigned))
    {
        unsigned* indices = ((unsigned*)shadowData_.Get()) + start;

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
        unsigned short* indices = ((unsigned short*)shadowData_.Get()) + start;

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
    if (!indexCount_)
    {
        Release();
        return true;
    }

    if (graphics_)
    {
        if (graphics_->IsDeviceLost())
        {
            URHO3D_LOGWARNING("Index buffer creation while device is lost");
            return true;
        }

        if (!object_)
            glGenBuffers(1, &object_);
        if (!object_)
        {
            URHO3D_LOGERROR("Failed to create index buffer");
            return false;
        }

        graphics_->SetIndexBuffer(this);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexCount_ * indexSize_, 0, dynamic_ ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW);
    }

    return true;
}

bool IndexBuffer::UpdateToGPU()
{
    if (object_ && shadowData_)
        return SetData(shadowData_.Get());
    else
        return false;
}

}
