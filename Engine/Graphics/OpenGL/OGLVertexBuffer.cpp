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

#include <cstring>

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
    vertexCount_(0),
    elementMask_(0),
    morphRangeStart_(0),
    morphRangeCount_(0),
    dynamic_(false),
    locked_(false)
{
    UpdateOffsets();
}

VertexBuffer::~VertexBuffer()
{
    Release();
}

void VertexBuffer::OnDeviceLost()
{
    if (object_)
    {
        void* hwData = Lock(0, vertexCount_, LOCK_NORMAL);
        if (hwData)
        {
            saveData_ = new unsigned char[vertexCount_ * vertexSize_];
            memcpy(saveData_.Get(), hwData, vertexCount_ * vertexSize_);
        }
        Unlock();
        Release();
    }
}

void VertexBuffer::OnDeviceReset()
{
    if (!object_)
    {
        Create();
        if (saveData_)
        {
            SetData(saveData_.Get());
            saveData_.Reset();
        }
    }
}

void VertexBuffer::Release()
{
    if (object_)
    {
        if (!graphics_)
            return;
        
        Unlock();
        
        for (unsigned i = 0; i < MAX_VERTEX_STREAMS; ++i)
        {
            if (graphics_->GetVertexBuffer(i) == this)
                graphics_->SetVertexBuffer(0);
        }
        
        glDeleteBuffers(1, &object_);
        object_ = 0;
    }
    
    fallbackData_.Reset();
}

bool VertexBuffer::SetSize(unsigned vertexCount, unsigned elementMask, bool dynamic)
{
    dynamic_ = dynamic;
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
    if (!data)
    {
        LOGERROR("Null pointer for vertex buffer data");
        return false;
    }
    
    if (locked_)
        Unlock();
    
    if (object_)
    {
        glBindBuffer(GL_ARRAY_BUFFER, object_);
        glBufferData(GL_ARRAY_BUFFER, vertexCount_ * vertexSize_, data, dynamic_ ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW);
        return true;
    }
    else if (fallbackData_)
    {
        memcpy(fallbackData_.Get(), data, vertexCount_ * vertexSize_);
        return true;
    }
    
    return false;
}

bool VertexBuffer::SetDataRange(const void* data, unsigned start, unsigned count)
{
    if (!data)
    {
        LOGERROR("Null pointer for vertex buffer data");
        return false;
    }
    
    if (start + count > vertexCount_)
    {
        LOGERROR("Illegal range for setting new index buffer data");
        return false;
    }
    
    if (locked_)
        Unlock();
    
    if (object_)
    {
        glBindBuffer(GL_ARRAY_BUFFER, object_);
        glBufferSubData(GL_ARRAY_BUFFER, start * vertexSize_, vertexCount_ * vertexSize_, data);
        return true;
    }
    else if (fallbackData_)
    {
        memcpy(fallbackData_.Get() + start * vertexSize_, data, vertexCount_ * vertexSize_);
        return true;
    }
    
    return false;
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
    GLenum glLockMode = GL_WRITE_ONLY;
    if (mode == LOCK_READONLY)
        glLockMode = GL_READ_ONLY;
    else if (mode == LOCK_NORMAL)
        glLockMode = GL_READ_WRITE;
    
    if (object_)
    {
        glBindBuffer(GL_ARRAY_BUFFER, object_);
        // If locking the whole buffer in discard mode, create a new data store
        if (mode == LOCK_DISCARD && count == vertexCount_)
            glBufferData(GL_ARRAY_BUFFER, vertexCount_ * vertexSize_, 0, dynamic_ ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW);
        
        hwData = glMapBuffer(GL_ARRAY_BUFFER, glLockMode);
        if (!hwData)
            return 0;
        hwData = (unsigned char*)hwData + start * vertexSize_;
    }
    else
        hwData = fallbackData_.Get() + start * vertexSize_;
    
    locked_ = true;
    return hwData;
}

void VertexBuffer::Unlock()
{
    if (locked_)
    {
        if (object_)
        {
            glBindBuffer(GL_ARRAY_BUFFER, object_);
            glUnmapBuffer(GL_ARRAY_BUFFER);
        }
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
    
    memcpy(lockedMorphRange, morphRangeResetData_.Get(), morphRangeCount_ * vertexSize_);
}

void VertexBuffer::ClearDataLost()
{
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
    if (!vertexCount_ || !elementMask_)
    {
        Release();
        return true;
    }
    
    if (graphics_)
    {
        if (!object_)
            glGenBuffers(1, &object_);
        
        glBindBuffer(GL_ARRAY_BUFFER, object_);
        glBufferData(GL_ARRAY_BUFFER, vertexCount_ * vertexSize_, 0, dynamic_ ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW);
    }
    else
        fallbackData_ = new unsigned char[vertexCount_ * vertexSize_];
    
    return true;
}
