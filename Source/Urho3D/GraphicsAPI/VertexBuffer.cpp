// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

// This file contains VertexBuffer code common to all graphics APIs.

#include "../Precompiled.h"

#include "../Graphics/Graphics.h"
#include "../Math/MathDefs.h"
#include "VertexBuffer.h"

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

void VertexBuffer::OnDeviceLost()
{
    GAPI gapi = Graphics::GetGAPI();

#ifdef URHO3D_OPENGL
    if (gapi == GAPI_OPENGL)
        return OnDeviceLost_OGL();
#endif

#ifdef URHO3D_D3D9
    if (gapi == GAPI_D3D9)
        return OnDeviceLost_D3D9();
#endif

#ifdef URHO3D_D3D11
    if (gapi == GAPI_D3D11)
        return OnDeviceLost_D3D11();
#endif
}

void VertexBuffer::OnDeviceReset()
{
    GAPI gapi = Graphics::GetGAPI();

#ifdef URHO3D_OPENGL
    if (gapi == GAPI_OPENGL)
        return OnDeviceReset_OGL();
#endif

#ifdef URHO3D_D3D9
    if (gapi == GAPI_D3D9)
        return OnDeviceReset_D3D9();
#endif

#ifdef URHO3D_D3D11
    if (gapi == GAPI_D3D11)
        return OnDeviceReset_D3D11();
#endif
}

void VertexBuffer::Release()
{
    GAPI gapi = Graphics::GetGAPI();

#ifdef URHO3D_OPENGL
    if (gapi == GAPI_OPENGL)
        return Release_OGL();
#endif

#ifdef URHO3D_D3D9
    if (gapi == GAPI_D3D9)
        return Release_D3D9();
#endif

#ifdef URHO3D_D3D11
    if (gapi == GAPI_D3D11)
        return Release_D3D11();
#endif
}

bool VertexBuffer::SetData(const void* data)
{
    GAPI gapi = Graphics::GetGAPI();

#ifdef URHO3D_OPENGL
    if (gapi == GAPI_OPENGL)
        return SetData_OGL(data);
#endif

#ifdef URHO3D_D3D9
    if (gapi == GAPI_D3D9)
        return SetData_D3D9(data);
#endif

#ifdef URHO3D_D3D11
    if (gapi == GAPI_D3D11)
        return SetData_D3D11(data);
#endif

    return {}; // Prevent warning
}

bool VertexBuffer::SetDataRange(const void* data, unsigned start, unsigned count, bool discard)
{
    GAPI gapi = Graphics::GetGAPI();

#ifdef URHO3D_OPENGL
    if (gapi == GAPI_OPENGL)
        return SetDataRange_OGL(data, start, count, discard);
#endif

#ifdef URHO3D_D3D9
    if (gapi == GAPI_D3D9)
        return SetDataRange_D3D9(data, start, count, discard);
#endif

#ifdef URHO3D_D3D11
    if (gapi == GAPI_D3D11)
        return SetDataRange_D3D11(data, start, count, discard);
#endif

    return {}; // Prevent warning
}

void* VertexBuffer::Lock(unsigned start, unsigned count, bool discard)
{
    GAPI gapi = Graphics::GetGAPI();

#ifdef URHO3D_OPENGL
    if (gapi == GAPI_OPENGL)
        return Lock_OGL(start, count, discard);
#endif

#ifdef URHO3D_D3D9
    if (gapi == GAPI_D3D9)
        return Lock_D3D9(start, count, discard);
#endif

#ifdef URHO3D_D3D11
    if (gapi == GAPI_D3D11)
        return Lock_D3D11(start, count, discard);
#endif

    return {}; // Prevent warning
}

void VertexBuffer::Unlock()
{
    GAPI gapi = Graphics::GetGAPI();

#ifdef URHO3D_OPENGL
    if (gapi == GAPI_OPENGL)
        return Unlock_OGL();
#endif

#ifdef URHO3D_D3D9
    if (gapi == GAPI_D3D9)
        return Unlock_D3D9();
#endif

#ifdef URHO3D_D3D11
    if (gapi == GAPI_D3D11)
        return Unlock_D3D11();
#endif
}

bool VertexBuffer::Create()
{
    GAPI gapi = Graphics::GetGAPI();

#ifdef URHO3D_OPENGL
    if (gapi == GAPI_OPENGL)
        return Create_OGL();
#endif

#ifdef URHO3D_D3D9
    if (gapi == GAPI_D3D9)
        return Create_D3D9();
#endif

#ifdef URHO3D_D3D11
    if (gapi == GAPI_D3D11)
        return Create_D3D11();
#endif

    return {}; // Prevent warning
}

bool VertexBuffer::UpdateToGPU()
{
    GAPI gapi = Graphics::GetGAPI();

#ifdef URHO3D_OPENGL
    if (gapi == GAPI_OPENGL)
        return UpdateToGPU_OGL();
#endif

#ifdef URHO3D_D3D9
    if (gapi == GAPI_D3D9)
        return UpdateToGPU_D3D9();
#endif

#ifdef URHO3D_D3D11
    if (gapi == GAPI_D3D11)
        return UpdateToGPU_D3D11();
#endif

    return {}; // Prevent warning
}

void* VertexBuffer::MapBuffer(unsigned start, unsigned count, bool discard)
{
    GAPI gapi = Graphics::GetGAPI();

#ifdef URHO3D_OPENGL
    if (gapi == GAPI_OPENGL)
        return MapBuffer_OGL(start, count, discard);
#endif

#ifdef URHO3D_D3D9
    if (gapi == GAPI_D3D9)
        return MapBuffer_D3D9(start, count, discard);
#endif

#ifdef URHO3D_D3D11
    if (gapi == GAPI_D3D11)
        return MapBuffer_D3D11(start, count, discard);
#endif

    return {}; // Prevent warning
}

void VertexBuffer::UnmapBuffer()
{
    GAPI gapi = Graphics::GetGAPI();

#ifdef URHO3D_OPENGL
    if (gapi == GAPI_OPENGL)
        return UnmapBuffer_OGL();
#endif

#ifdef URHO3D_D3D9
    if (gapi == GAPI_D3D9)
        return UnmapBuffer_D3D9();
#endif

#ifdef URHO3D_D3D11
    if (gapi == GAPI_D3D11)
        return UnmapBuffer_D3D11();
#endif
}

}
