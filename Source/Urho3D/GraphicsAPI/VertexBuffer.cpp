// Copyright (c) 2008-2023 the Urho3D project
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
            shadowData_ = new byte[(size_t)vertexCount_ * vertexSize_];
        else
            shadowData_.Reset();

        shadowed_ = enable;
    }
}

bool VertexBuffer::SetSize(i32 vertexCount, VertexElements elementMask, bool dynamic)
{
    assert(vertexCount >= 0);
    return SetSize(vertexCount, GetElements(elementMask), dynamic);
}

bool VertexBuffer::SetSize(i32 vertexCount, const Vector<VertexElement>& elements, bool dynamic)
{
    assert(vertexCount >= 0);
    Unlock();

    vertexCount_ = vertexCount;
    elements_ = elements;
    dynamic_ = dynamic;

    UpdateOffsets();

    if (shadowed_ && vertexCount_ && vertexSize_)
        shadowData_ = new byte[(size_t)vertexCount_ * vertexSize_];
    else
        shadowData_.Reset();

    return Create();
}

void VertexBuffer::UpdateOffsets()
{
    i32 elementOffset = 0;
    elementHash_ = 0;
    elementMask_ = VertexElements::None;

    for (VertexElement& element : elements_)
    {
        element.offset_ = elementOffset;
        elementOffset += ELEMENT_TYPESIZES[element.type_];
        elementHash_ <<= 6;
        elementHash_ += (u64)(((i32)element.type_ + 1) * ((i32)element.semantic_ + 1) + element.index_);

        for (i32 j = 0; j < MAX_LEGACY_VERTEX_ELEMENTS; ++j)
        {
            const VertexElement& legacy = LEGACY_VERTEXELEMENTS[j];
            if (element.type_ == legacy.type_ && element.semantic_ == legacy.semantic_ && element.index_ == legacy.index_)
                elementMask_ |= VertexElements{1u << j};
        }
    }

    vertexSize_ = elementOffset;
}

const VertexElement* VertexBuffer::GetElement(VertexElementSemantic semantic, i8 index/* = 0*/) const
{
    assert(index >= 0);

    for (const VertexElement& element : elements_)
    {
        if (element.semantic_ == semantic && element.index_ == index)
            return &element;
    }

    return nullptr;
}

const VertexElement* VertexBuffer::GetElement(VertexElementType type, VertexElementSemantic semantic, i8 index/* = 0*/) const
{
    assert(index >= 0);

    for (const VertexElement& element : elements_)
    {
        if (element.type_ == type && element.semantic_ == semantic && element.index_ == index)
            return &element;
    }

    return nullptr;
}

const VertexElement* VertexBuffer::GetElement(const Vector<VertexElement>& elements, VertexElementType type, VertexElementSemantic semantic, i8 index/* = 0*/)
{
    assert(index >= 0);

    for (const VertexElement& element : elements)
    {
        if (element.type_ == type && element.semantic_ == semantic && element.index_ == index)
            return &element;
    }

    return nullptr;
}

bool VertexBuffer::HasElement(const Vector<VertexElement>& elements, VertexElementType type, VertexElementSemantic semantic, i8 index/* = 0*/)
{
    assert(index >= 0);
    return GetElement(elements, type, semantic, index) != nullptr;
}

i32 VertexBuffer::GetElementOffset(const Vector<VertexElement>& elements, VertexElementType type, VertexElementSemantic semantic, i8 index/* = 0*/)
{
    assert(index >= 0);
    const VertexElement* element = GetElement(elements, type, semantic, index);
    return element ? element->offset_ : NINDEX;
}

Vector<VertexElement> VertexBuffer::GetElements(VertexElements elementMask)
{
    Vector<VertexElement> ret;

    for (i32 i = 0; i < MAX_LEGACY_VERTEX_ELEMENTS; ++i)
    {
        if (!!(elementMask & VertexElements{1u << i}))
            ret.Push(LEGACY_VERTEXELEMENTS[i]);
    }

    return ret;
}

i32 VertexBuffer::GetVertexSize(const Vector<VertexElement>& elements)
{
    i32 size = 0;

    for (i32 i = 0; i < elements.Size(); ++i)
        size += ELEMENT_TYPESIZES[elements[i].type_];

    return size;
}

i32 VertexBuffer::GetVertexSize(VertexElements elementMask)
{
    i32 size = 0;

    for (i32 i = 0; i < MAX_LEGACY_VERTEX_ELEMENTS; ++i)
    {
        if (!!(elementMask & VertexElements{1u << i}))
            size += ELEMENT_TYPESIZES[LEGACY_VERTEXELEMENTS[i].type_];
    }

    return size;
}

void VertexBuffer::UpdateOffsets(Vector<VertexElement>& elements)
{
    i32 elementOffset = 0;

    for (VertexElement& element : elements)
    {
        element.offset_ = elementOffset;
        elementOffset += ELEMENT_TYPESIZES[element.type_];
    }
}

void VertexBuffer::OnDeviceLost()
{
    GAPI gapi = Graphics::GetGAPI();

#ifdef URHO3D_OPENGL
    if (gapi == GAPI_OPENGL)
        return OnDeviceLost_OGL();
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

#ifdef URHO3D_D3D11
    if (gapi == GAPI_D3D11)
        return SetData_D3D11(data);
#endif

    return {}; // Prevent warning
}

bool VertexBuffer::SetDataRange(const void* data, i32 start, i32 count, bool discard)
{
    assert(start >= 0 && count >= 0);
    GAPI gapi = Graphics::GetGAPI();

#ifdef URHO3D_OPENGL
    if (gapi == GAPI_OPENGL)
        return SetDataRange_OGL(data, start, count, discard);
#endif

#ifdef URHO3D_D3D11
    if (gapi == GAPI_D3D11)
        return SetDataRange_D3D11(data, start, count, discard);
#endif

    return {}; // Prevent warning
}

void* VertexBuffer::Lock(i32 start, i32 count, bool discard)
{
    assert(start >= 0 && count >= 0);
    GAPI gapi = Graphics::GetGAPI();

#ifdef URHO3D_OPENGL
    if (gapi == GAPI_OPENGL)
        return Lock_OGL(start, count, discard);
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

#ifdef URHO3D_D3D11
    if (gapi == GAPI_D3D11)
        return UpdateToGPU_D3D11();
#endif

    return {}; // Prevent warning
}

void* VertexBuffer::MapBuffer(i32 start, i32 count, bool discard)
{
    assert(start >= 0 && count >= 0);
    GAPI gapi = Graphics::GetGAPI();

#ifdef URHO3D_OPENGL
    if (gapi == GAPI_OPENGL)
        return MapBuffer_OGL(start, count, discard);
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

#ifdef URHO3D_D3D11
    if (gapi == GAPI_D3D11)
        return UnmapBuffer_D3D11();
#endif
}

}
