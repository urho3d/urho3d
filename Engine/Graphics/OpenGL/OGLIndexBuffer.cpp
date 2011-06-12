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
#include "Context.h"
#include "Graphics.h"
#include "GraphicsImpl.h"
#include "IndexBuffer.h"
#include "Log.h"

#include <GLee.h>

#include "DebugNew.h"

OBJECTTYPESTATIC(IndexBuffer);

IndexBuffer::IndexBuffer(Context* context) :
    Object(context),
    GPUObject(GetSubsystem<Graphics>()),
    indexCount_(0),
    indexSize_(0),
    dynamic_(false),
    locked_(false)
{
}

IndexBuffer::~IndexBuffer()
{
    Release();
}

void IndexBuffer::Release()
{
    if (object_)
    {
        if (!graphics_)
            return;
        
        if (graphics_->GetIndexBuffer() == this)
            graphics_->SetIndexBuffer(0);
        
        glDeleteBuffers(1, &object_);
    }
    
    fallbackData_.Reset();
}

bool IndexBuffer::SetSize(unsigned indexCount, bool largeIndices, bool dynamic)
{
    return SetSize(indexCount, largeIndices ? sizeof(unsigned) : sizeof(unsigned short), dynamic);
}

bool IndexBuffer::SetSize(unsigned indexCount, unsigned indexSize, bool dynamic)
{
    if ((indexSize != sizeof(unsigned)) && (indexSize != sizeof(unsigned short)))
    {
        LOGERROR("Index size not 2 or 4 bytes");
        return false;
    }
    
    dynamic_ = dynamic;
    indexCount_ = indexCount;
    indexSize_ = indexSize;
    
    return Create();
}

bool IndexBuffer::SetData(const void* data)
{
    return SetData(data, indexCount_);
}

bool IndexBuffer::SetData(const void* data, unsigned indexCount)
{
    if (!indexCount)
    {
        LOGERROR("Null size for index buffer data");
        return false;
    }
    if (!data)
    {
        LOGERROR("Null pointer for index buffer data");
        return false;
    }
    
    if (locked_)
        Unlock();
    
    indexCount_ = indexCount;
    
    if (object_)
    {
        graphics_->SetIndexBuffer(this);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexCount_ * indexSize_, data, dynamic_ ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW);
        return true;
    }
    else if (fallbackData_)
    {
        memcpy(fallbackData_.GetPtr(), data, indexCount_ * indexSize_);
        return true;
    }
    
    return false;
}

bool IndexBuffer::SetDataRange(const void* data, unsigned start, unsigned count)
{
    if (!data)
    {
        LOGERROR("Null pointer for index buffer data");
        return false;
    }
    
    if (start + count > indexCount_)
    {
        LOGERROR("Illegal range for setting new index buffer data");
        return false;
    }
    
    if (locked_)
        Unlock();
    
    if (object_)
    {
        graphics_->SetIndexBuffer(this);
        glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, start * indexSize_, indexCount_ * indexSize_, data);
        return true;
    }
    else if (fallbackData_)
    {
        memcpy(fallbackData_.GetPtr() + start * indexSize_, data, indexCount_ * indexSize_);
        return true;
    }
    
    return false;
}

void* IndexBuffer::Lock(unsigned start, unsigned count, LockMode mode)
{
    if ((!object_) && (!fallbackData_))
        return 0;
    
    if (locked_)
    {
        LOGERROR("Index buffer already locked");
        return 0;
    }

    if ((!count) || (start + count > indexCount_))
    {
        LOGERROR("Illegal range for locking index buffer");
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
        graphics_->SetIndexBuffer(this);
        hwData = glMapBuffer(GL_ELEMENT_ARRAY_BUFFER, glLockMode);
        if (!hwData)
            return 0;
        hwData = (unsigned char*)hwData + start * indexSize_;
    }
    else
        hwData = fallbackData_.GetPtr() + start * indexSize_;
    
    locked_ = true;
    return hwData;
}

void IndexBuffer::Unlock()
{
    if (locked_)
    {
        if (object_)
        {
            graphics_->SetIndexBuffer(this);
            glUnmapBuffer(GL_ELEMENT_ARRAY_BUFFER);
        }
        locked_ = false;
    }
}

bool IndexBuffer::GetUsedVertexRange(unsigned start, unsigned count, unsigned& minVertex, unsigned& vertexCount)
{
    void* data = Lock(start, count, LOCK_READONLY);
    if (!data)
        return false;
    
    minVertex = M_MAX_UNSIGNED;
    unsigned maxVertex = 0;
    
    if (indexSize_ == sizeof(unsigned))
    {
        unsigned* indices = (unsigned*)data;
        
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
        unsigned short* indices = (unsigned short*)data;
        
        for (unsigned i = 0; i < count; ++i)
        {
            if (indices[i] < minVertex)
                minVertex = indices[i];
            if (indices[i] > maxVertex)
                maxVertex = indices[i];
        }
    }
    
    vertexCount = maxVertex - minVertex + 1;
    
    Unlock();
    return true;
}

bool IndexBuffer::Create()
{
    Release();
    
    if (!indexCount_)
        return true;
    
    if (graphics_)
    {
        glGenBuffers(1, &object_);
        graphics_->SetIndexBuffer(this);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexCount_ * indexSize_, 0, dynamic_ ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW);
    }
    else
        fallbackData_ = new unsigned char[indexCount_ * indexSize_];
    
    return true;
}
