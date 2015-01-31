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

#include "../../Graphics/Graphics.h"
#include "../../Graphics/GraphicsImpl.h"
#include "../../IO/Log.h"
#include "../../Graphics/VertexBuffer.h"

#include <cstring>

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

const unsigned VertexBuffer::elementType[] =
{
    GL_FLOAT, // Position
    GL_FLOAT, // Normal
    GL_UNSIGNED_BYTE, // Color
    GL_FLOAT, // Texcoord1
    GL_FLOAT, // Texcoord2
    GL_FLOAT, // Cubetexcoord1
    GL_FLOAT, // Cubetexcoord2
    GL_FLOAT, // Tangent
    GL_FLOAT, // Blendweights
    GL_UNSIGNED_BYTE, // Blendindices
    GL_FLOAT, // Instancematrix1
    GL_FLOAT, // Instancematrix2
    GL_FLOAT // Instancematrix3
};

const unsigned VertexBuffer::elementComponents[] =
{
    3, // Position
    3, // Normal
    4, // Color
    2, // Texcoord1
    2, // Texcoord2
    3, // Cubetexcoord1
    3, // Cubetexcoord2
    4, // Tangent
    4, // Blendweights
    4, // Blendindices
    4, // Instancematrix1
    4, // Instancematrix2
    4 // Instancematrix3
};

const unsigned VertexBuffer::elementNormalize[] =
{
    GL_FALSE, // Position
    GL_FALSE, // Normal
    GL_TRUE, // Color
    GL_FALSE, // Texcoord1
    GL_FALSE, // Texcoord2
    GL_FALSE, // Cubetexcoord1
    GL_FALSE, // Cubetexcoord2
    GL_FALSE, // Tangent
    GL_FALSE, // Blendweights
    GL_FALSE, // Blendindices
    GL_FALSE, // Instancematrix1
    GL_FALSE, // Instancematrix2
    GL_FALSE // Instancematrix3
};

VertexBuffer::VertexBuffer(Context* context) :
    Object(context),
    GPUObject(GetSubsystem<Graphics>()),
    vertexCount_(0),
    elementMask_(0),
    lockState_(LOCK_NONE),
    lockStart_(0),
    lockCount_(0),
    lockScratchData_(0),
    shadowed_(false),
    dynamic_(false)
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

void VertexBuffer::OnDeviceReset()
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

void VertexBuffer::Release()
{
    Unlock();
    
    if (object_)
    {
        if (!graphics_)
            return;
        
        if (!graphics_->IsDeviceLost())
        {
            for (unsigned i = 0; i < MAX_VERTEX_STREAMS; ++i)
            {
                if (graphics_->GetVertexBuffer(i) == this)
                    graphics_->SetVertexBuffer(0);
            }
            
            glDeleteBuffers(1, &object_);
        }
        
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
        if (!graphics_->IsDeviceLost())
        {
            glBindBuffer(GL_ARRAY_BUFFER, object_);
            glBufferData(GL_ARRAY_BUFFER, vertexCount_ * vertexSize_, data, dynamic_ ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW);
        }
        else
        {
            LOGWARNING("Vertex buffer data assignment while device is lost");
            dataPending_ = true;
        }
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
        if (!graphics_->IsDeviceLost())
        {
            glBindBuffer(GL_ARRAY_BUFFER, object_);
            if (!discard || start != 0)
                glBufferSubData(GL_ARRAY_BUFFER, start * vertexSize_, count * vertexSize_, data);
            else
                glBufferData(GL_ARRAY_BUFFER, count * vertexSize_, data, dynamic_ ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW);
        }
        else
        {
            LOGWARNING("Vertex buffer data assignment while device is lost");
            dataPending_ = true;
        }
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
        return 0;
}

void VertexBuffer::Unlock()
{
    switch (lockState_)
    {
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
    
    default:
        break;
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
    
    for (unsigned i = 0; i != element; ++i)
    {
        if (elementMask & (1 << i))
            offset += elementSize[i];
    }
    
    return offset;
}

bool VertexBuffer::Create()
{
    if (!vertexCount_ || !elementMask_)
    {
        Release();
        return true;
    }
    
    if (graphics_)
    {
        if (graphics_->IsDeviceLost())
        {
            LOGWARNING("Vertex buffer creation while device is lost");
            return true;
        }
        
        if (!object_)
            glGenBuffers(1, &object_);
        if (!object_)
        {
            LOGERROR("Failed to create vertex buffer");
            return false;
        }
        
        glBindBuffer(GL_ARRAY_BUFFER, object_);
        glBufferData(GL_ARRAY_BUFFER, vertexCount_ * vertexSize_, 0, dynamic_ ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW);
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

}
