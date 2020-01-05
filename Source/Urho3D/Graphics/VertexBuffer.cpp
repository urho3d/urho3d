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

// This file contains VertexBuffer code common to all graphics APIs.

#include "../Precompiled.h"

#include "../Graphics/Graphics.h"
#include "../Graphics/VertexBuffer.h"
#include "../Math/MathDefs.h"

#include "../DebugNew.h"

namespace Urho3D
{

VertexBuffer::VertexBuffer(Context* context, bool forceHeadless) :
    Object(context),
    GPUObject(forceHeadless ? nullptr : GetSubsystem<Graphics>())
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

void VertexBuffer::UpdateOffsets()
{
    unsigned elementOffset = 0;
    elementHash_ = 0;
    elementMask_ = MASK_NONE;

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
                elementMask_ |= VertexMaskFlags(1u << j);
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

    return nullptr;
}

const VertexElement* VertexBuffer::GetElement(VertexElementType type, VertexElementSemantic semantic, unsigned char index) const
{
    for (PODVector<VertexElement>::ConstIterator i = elements_.Begin(); i != elements_.End(); ++i)
    {
        if (i->type_ == type && i->semantic_ == semantic && i->index_ == index)
            return &(*i);
    }

    return nullptr;
}

const VertexElement* VertexBuffer::GetElement(const PODVector<VertexElement>& elements, VertexElementType type, VertexElementSemantic semantic, unsigned char index)
{
    for (PODVector<VertexElement>::ConstIterator i = elements.Begin(); i != elements.End(); ++i)
    {
        if (i->type_ == type && i->semantic_ == semantic && i->index_ == index)
            return &(*i);
    }

    return nullptr;
}

bool VertexBuffer::HasElement(const PODVector<VertexElement>& elements, VertexElementType type, VertexElementSemantic semantic, unsigned char index)
{
    return GetElement(elements, type, semantic, index) != nullptr;
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
        if (elementMask & (1u << i))
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
        if (elementMask & (1u << i))
            size += ELEMENT_TYPESIZES[LEGACY_VERTEXELEMENTS[i].type_];
    }

    return size;
}

void VertexBuffer::UpdateOffsets(PODVector<VertexElement>& elements)
{
    unsigned elementOffset = 0;

    for (PODVector<VertexElement>::Iterator i = elements.Begin(); i != elements.End(); ++i)
    {
        i->offset_ = elementOffset;
        elementOffset += ELEMENT_TYPESIZES[i->type_];
    }
}

}
