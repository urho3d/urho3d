// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

#include "../../Precompiled.h"

#include "../../Graphics/Graphics.h"
#include "../../GraphicsAPI/GraphicsImpl.h"
#include "../../GraphicsAPI/VertexBuffer.h"
#include "../../IO/Log.h"

#include "../../DebugNew.h"

namespace Urho3D
{

void VertexBuffer::OnDeviceLost_OGL()
{
    if (object_.name_ && !graphics_->IsDeviceLost())
        glDeleteBuffers(1, &object_.name_);

    GPUObject::OnDeviceLost();
}

void VertexBuffer::OnDeviceReset_OGL()
{
    if (!object_.name_)
    {
        Create_OGL();
        dataLost_ = !UpdateToGPU_OGL();
    }
    else if (dataPending_)
        dataLost_ = !UpdateToGPU_OGL();

    dataPending_ = false;
}

void VertexBuffer::Release_OGL()
{
    Unlock_OGL();

    if (object_.name_)
    {
        if (!graphics_)
            return;

        if (!graphics_->IsDeviceLost())
        {
            for (unsigned i = 0; i < MAX_VERTEX_STREAMS; ++i)
            {
                if (graphics_->GetVertexBuffer(i) == this)
                    graphics_->SetVertexBuffer(nullptr);
            }

            graphics_->SetVBO_OGL(0);
            glDeleteBuffers(1, &object_.name_);
        }

        object_.name_ = 0;
    }
}

bool VertexBuffer::SetData_OGL(const void* data)
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
        memcpy(shadowData_.Get(), data, vertexCount_ * (size_t)vertexSize_);

    if (object_.name_)
    {
        if (!graphics_->IsDeviceLost())
        {
            graphics_->SetVBO_OGL(object_.name_);
            glBufferData(GL_ARRAY_BUFFER, vertexCount_ * (size_t)vertexSize_, data, dynamic_ ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW);
        }
        else
        {
            URHO3D_LOGWARNING("Vertex buffer data assignment while device is lost");
            dataPending_ = true;
        }
    }

    dataLost_ = false;
    return true;
}

bool VertexBuffer::SetDataRange_OGL(const void* data, unsigned start, unsigned count, bool discard)
{
    if (start == 0 && count == vertexCount_)
        return SetData_OGL(data);

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
        memcpy(shadowData_.Get() + start * vertexSize_, data, count * (size_t)vertexSize_);

    if (object_.name_)
    {
        if (!graphics_->IsDeviceLost())
        {
            graphics_->SetVBO_OGL(object_.name_);
            if (!discard || start != 0)
                glBufferSubData(GL_ARRAY_BUFFER, start * (size_t)vertexSize_, count * vertexSize_, data);
            else
                glBufferData(GL_ARRAY_BUFFER, count * (size_t)vertexSize_, data, dynamic_ ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW);
        }
        else
        {
            URHO3D_LOGWARNING("Vertex buffer data assignment while device is lost");
            dataPending_ = true;
        }
    }

    return true;
}

void* VertexBuffer::Lock_OGL(unsigned start, unsigned count, bool discard)
{
    if (lockState_ != LOCK_NONE)
    {
        URHO3D_LOGERROR("Vertex buffer already locked");
        return nullptr;
    }

    if (!vertexSize_)
    {
        URHO3D_LOGERROR("Vertex elements not defined, can not lock vertex buffer");
        return nullptr;
    }

    if (start + count > vertexCount_)
    {
        URHO3D_LOGERROR("Illegal range for locking vertex buffer");
        return nullptr;
    }

    if (!count)
        return nullptr;

    lockStart_ = start;
    lockCount_ = count;
    discardLock_ = discard;

    if (shadowData_)
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
        return nullptr;
}

void VertexBuffer::Unlock_OGL()
{
    switch (lockState_)
    {
    case LOCK_SHADOW:
        SetDataRange_OGL(shadowData_.Get() + lockStart_ * vertexSize_, lockStart_, lockCount_, discardLock_);
        lockState_ = LOCK_NONE;
        break;

    case LOCK_SCRATCH:
        SetDataRange_OGL(lockScratchData_, lockStart_, lockCount_, discardLock_);
        if (graphics_)
            graphics_->FreeScratchBuffer(lockScratchData_);
        lockScratchData_ = nullptr;
        lockState_ = LOCK_NONE;
        break;

    default:
        break;
    }
}

bool VertexBuffer::Create_OGL()
{
    if (!vertexCount_ || !elementMask_)
    {
        Release_OGL();
        return true;
    }

    if (graphics_)
    {
        if (graphics_->IsDeviceLost())
        {
            URHO3D_LOGWARNING("Vertex buffer creation while device is lost");
            return true;
        }

        if (!object_.name_)
            glGenBuffers(1, &object_.name_);
        if (!object_.name_)
        {
            URHO3D_LOGERROR("Failed to create vertex buffer");
            return false;
        }

        graphics_->SetVBO_OGL(object_.name_);
        glBufferData(GL_ARRAY_BUFFER, vertexCount_ * (size_t)vertexSize_, nullptr, dynamic_ ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW);
    }

    return true;
}

bool VertexBuffer::UpdateToGPU_OGL()
{
    if (object_.name_ && shadowData_)
        return SetData_OGL(shadowData_.Get());
    else
        return false;
}

void* VertexBuffer::MapBuffer_OGL(unsigned start, unsigned count, bool discard)
{
    // Never called on OpenGL
    return nullptr;
}

void VertexBuffer::UnmapBuffer_OGL()
{
    // Never called on OpenGL
}

}
