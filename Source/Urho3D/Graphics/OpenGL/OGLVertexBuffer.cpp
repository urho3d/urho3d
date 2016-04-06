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

#include "../../Graphics/Graphics.h"
#include "../../Graphics/GraphicsImpl.h"
#include "../../Graphics/VertexBuffer.h"
#include "../../IO/Log.h"

#include "../../DebugNew.h"

namespace Urho3D
{

VertexBuffer::VertexBuffer(Context* context, bool forceHeadless) :
    Object(context),
    GPUObject(forceHeadless ? (Graphics*)0 : GetSubsystem<Graphics>()),
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

            graphics_->SetVBO(0);
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
    return SetSize(vertexCount, GetElements(elementMask), dynamic);
}

bool VertexBuffer::SetSize(unsigned vertexCount, const PODVector<VertexElement>& elements, bool dynamic)
{
    Unlock();

    vertexCount_ = vertexCount;
    elements_ = elements;
    dynamic_ = dynamic;

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
        if (!graphics_->IsDeviceLost())
        {
            graphics_->SetVBO(object_);
            glBufferData(GL_ARRAY_BUFFER, vertexCount_ * vertexSize_, data, dynamic_ ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW);
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
        if (!graphics_->IsDeviceLost())
        {
            graphics_->SetVBO(object_);
            if (!discard || start != 0)
                glBufferSubData(GL_ARRAY_BUFFER, start * vertexSize_, count * vertexSize_, data);
            else
                glBufferData(GL_ARRAY_BUFFER, count * vertexSize_, data, dynamic_ ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW);
        }
        else
        {
            URHO3D_LOGWARNING("Vertex buffer data assignment while device is lost");
            dataPending_ = true;
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
    elementHash_ = 0;
    elementMask_ = 0;

    for (PODVector<VertexElement>::Iterator i = elements_.Begin(); i != elements_.End(); ++i)
    {
        i->offset_ = elementOffset;
        elementOffset += ELEMENT_TYPESIZES[i->type_];
        elementHash_ <<= 6;
        elementHash_ += (((int)i->type_ + 1) * ((int)i->semantic_ + 1) + i->index_);

        for (unsigned j = 0; j < MAX_LEGACY_VERTEX_ELEMENTS; ++j)
        {
            const VertexElement& legacy = LEGACY_VERTEXELEMENTS[j];
            if (i->type_ == legacy.type_ && i->semantic_ == legacy.semantic_ && i->index_ == legacy.index_)
                elementMask_ |= (1 << j);
        }
    }

    vertexSize_ = elementOffset;
}

const VertexElement* VertexBuffer::GetElement(VertexElementSemantic semantic, unsigned char index) const
{
    for (PODVector<VertexElement>::ConstIterator i = elements_.Begin(); i != elements_.End(); ++i)
    {
        if (i->semantic_ == semantic && i->index_ == index)
            return &(*i);
    }

    return 0;
}

const VertexElement* VertexBuffer::GetElement(VertexElementType type, VertexElementSemantic semantic, unsigned char index) const
{
    for (PODVector<VertexElement>::ConstIterator i = elements_.Begin(); i != elements_.End(); ++i)
    {
        if (i->type_ == type && i->semantic_ == semantic && i->index_ == index)
            return &(*i);
    }

    return 0;
}

const VertexElement* VertexBuffer::GetElement(const PODVector<VertexElement>& elements, VertexElementType type, VertexElementSemantic semantic, unsigned char index)
{
    for (PODVector<VertexElement>::ConstIterator i = elements.Begin(); i != elements.End(); ++i)
    {
        if (i->type_ == type && i->semantic_ == semantic && i->index_ == index)
            return &(*i);
    }

    return 0;
}

bool VertexBuffer::HasElement(const PODVector<VertexElement>& elements, VertexElementType type, VertexElementSemantic semantic, unsigned char index)
{
    return GetElement(elements, type, semantic, index) != 0;
}

unsigned VertexBuffer::GetElementOffset(const PODVector<VertexElement>& elements, VertexElementType type, VertexElementSemantic semantic, unsigned char index)
{
    const VertexElement* element = GetElement(elements, type, semantic, index);
    return element ? element->offset_ : M_MAX_UNSIGNED;
}

PODVector<VertexElement> VertexBuffer::GetElements(unsigned elementMask)
{
    PODVector<VertexElement> ret;

    for (unsigned i = 0; i < MAX_LEGACY_VERTEX_ELEMENTS; ++i)
    {
        if (elementMask & (1 << i))
            ret.Push(LEGACY_VERTEXELEMENTS[i]);
    }

    return ret;
}

unsigned VertexBuffer::GetVertexSize(const PODVector<VertexElement>& elements)
{
    unsigned size = 0;

    for (unsigned i = 0; i < elements.Size(); ++i)
        size += ELEMENT_TYPESIZES[elements[i].type_];

    return size;
}

unsigned VertexBuffer::GetVertexSize(unsigned elementMask)
{
    unsigned size = 0;

    for (unsigned i = 0; i < MAX_LEGACY_VERTEX_ELEMENTS; ++i)
    {
        if (elementMask & (1 << i))
            size += ELEMENT_TYPESIZES[LEGACY_VERTEXELEMENTS[i].type_];
    }

    return size;
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
            URHO3D_LOGWARNING("Vertex buffer creation while device is lost");
            return true;
        }

        if (!object_)
            glGenBuffers(1, &object_);
        if (!object_)
        {
            URHO3D_LOGERROR("Failed to create vertex buffer");
            return false;
        }

        graphics_->SetVBO(object_);
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
