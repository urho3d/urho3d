//
// Urho3D Engine
// Copyright (c) 2008-2012 Lasse Öörni
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

#include <cstring>

#include "DebugNew.h"

OBJECTTYPESTATIC(IndexBuffer);

IndexBuffer::IndexBuffer(Context* context) :
    Object(context),
    GPUObject(GetSubsystem<Graphics>()),
    indexCount_(0),
    indexSize_(0),
    dynamic_(false),
    dataLost_(false)
{
    // Force shadowing mode if graphics subsystem does not exist
    if (!graphics_)
        shadowed_ = true;
}

IndexBuffer::~IndexBuffer()
{
    Release();
}

void IndexBuffer::OnDeviceLost()
{
    GPUObject::OnDeviceLost();
    
    dataLost_ = true;
}

void IndexBuffer::OnDeviceReset()
{
    if (!object_)
    {
        Create();
        if (UpdateToGPU())
            dataLost_ = false;
    }
}

void IndexBuffer::Release()
{
    if (object_ && graphics_)
    {
        if (graphics_->GetIndexBuffer() == this)
            graphics_->SetIndexBuffer(0);
        
        glDeleteBuffers(1, &object_);
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
    dynamic_ = dynamic;
    indexCount_ = indexCount;
    indexSize_ = largeIndices ? sizeof(unsigned) : sizeof(unsigned short);
    
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
        LOGERROR("Null pointer for index buffer data");
        return false;
    }
    
    if (object_)
    {
        graphics_->SetIndexBuffer(0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, object_);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexCount_ * indexSize_, data, dynamic_ ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW);
    }
    
    if (shadowData_ && data != shadowData_.Get())
        memcpy(shadowData_.Get(), data, indexCount_ * indexSize_);
    
    return true;
}

bool IndexBuffer::SetDataRange(const void* data, unsigned start, unsigned count, bool discard)
{
    if (start == 0 && count == indexCount_)
        return SetData(data);
    
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
    
    if (!count)
        return true;
    
    if (object_)
    {
        graphics_->SetIndexBuffer(0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, object_);
        if (!discard || start != 0)
            glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, start * indexSize_, count * indexSize_, data);
        else
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * indexSize_, data, dynamic_ ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW);
    }
    
    if (shadowData_ && shadowData_.Get() + start * indexSize_ != data)
        memcpy(shadowData_.Get() + start * indexSize_, data, count * indexSize_);
    
    return true;
}

bool IndexBuffer::UpdateToGPU()
{
    if (object_ && shadowData_)
        return SetData(shadowData_.Get());
    else
        return false;
}

void IndexBuffer::ClearDataLost()
{
    dataLost_ = false;
}

bool IndexBuffer::GetUsedVertexRange(unsigned start, unsigned count, unsigned& minVertex, unsigned& vertexCount)
{
    if (!shadowData_)
        return false;
    
    minVertex = M_MAX_UNSIGNED;
    unsigned maxVertex = 0;
    
    if (indexSize_ == sizeof(unsigned))
    {
        unsigned* indices = (unsigned*)shadowData_.Get();
        
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
        unsigned short* indices = (unsigned short*)shadowData_.Get();
        
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
        graphics_->SetIndexBuffer(0);
        
        if (!object_)
            glGenBuffers(1, &object_);
        
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, object_);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexCount_ * indexSize_, 0, dynamic_ ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW);
    }
    
    return true;
}
