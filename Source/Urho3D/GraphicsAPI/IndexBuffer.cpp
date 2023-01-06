// Copyright (c) 2008-2023 the Urho3D project
// License: MIT

// This file contains IndexBuffer code common to all graphics APIs.

#include "../Precompiled.h"

#include "../Graphics/Graphics.h"
#include "../GraphicsAPI/IndexBuffer.h"
#include "../IO/Log.h"

#include "../DebugNew.h"

namespace Urho3D
{

IndexBuffer::IndexBuffer(Context* context, bool forceHeadless) :
    Object(context),
    GPUObject(forceHeadless ? nullptr : GetSubsystem<Graphics>()),
    indexCount_(0),
    indexSize_(0),
    lockState_(LOCK_NONE),
    lockStart_(0),
    lockCount_(0),
    lockScratchData_(nullptr),
    shadowed_(false),
    dynamic_(false),
    discardLock_(false)
{
    // Force shadowing mode if graphics subsystem does not exist
    if (!graphics_)
        shadowed_ = true;
}

IndexBuffer::~IndexBuffer()
{
    Release();
}

void IndexBuffer::SetShadowed(bool enable)
{
    // If no graphics subsystem, can not disable shadowing
    if (!graphics_)
        enable = true;

    if (enable != shadowed_)
    {
        if (enable && indexCount_ && indexSize_)
            shadowData_ = new byte[(size_t)indexCount_ * indexSize_];
        else
            shadowData_.Reset();

        shadowed_ = enable;
    }
}

bool IndexBuffer::SetSize(i32 indexCount, bool largeIndices, bool dynamic)
{
    assert(indexCount >= 0);
    Unlock();

    indexCount_ = indexCount;
    indexSize_ = (i32)(largeIndices ? sizeof(u32) : sizeof(u16));
    dynamic_ = dynamic;

    if (shadowed_ && indexCount_ && indexSize_)
        shadowData_ = new byte[(size_t)indexCount_ * indexSize_];
    else
        shadowData_.Reset();

    return Create();
}

bool IndexBuffer::GetUsedVertexRange(i32 start, i32 count, i32& minVertex, i32& vertexCount)
{
    assert(start >= 0 && count >= 0);

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

    minVertex = M_MAX_INT;
    i32 maxVertex = 0;

    if (indexSize_ == sizeof(u32))
    {
        u32* indices = (u32*)shadowData_.Get() + start;

        for (i32 i = 0; i < count; ++i)
        {
            i32 index = (i32)indices[i];

            if (index < minVertex)
                minVertex = index;

            if (index > maxVertex)
                maxVertex = index;
        }
    }
    else
    {
        u16* indices = (u16*)shadowData_.Get() + start;

        for (i32 i = 0; i < count; ++i)
        {
            i32 index = (i32)indices[i];

            if (index < minVertex)
                minVertex = index;

            if (index > maxVertex)
                maxVertex = index;
        }
    }

    vertexCount = maxVertex - minVertex + 1;
    return true;
}

void IndexBuffer::OnDeviceLost()
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

void IndexBuffer::OnDeviceReset()
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

void IndexBuffer::Release()
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

bool IndexBuffer::SetData(const void* data)
{
    GAPI gapi = Graphics::GetGAPI();

#ifdef URHO3D_OPENGL
    if (gapi == GAPI_OPENGL)
        return SetData_OGL(data);
#endif

#ifdef URHO3D_D3D11
    if (gapi == GAPI_D3D11)
        return SetData_D3D11(data);;
#endif

    return {}; // Prevent warning
}

bool IndexBuffer::SetDataRange(const void* data, i32 start, i32 count, bool discard)
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

void* IndexBuffer::Lock(i32 start, i32 count, bool discard)
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

void IndexBuffer::Unlock()
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

bool IndexBuffer::Create()
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

bool IndexBuffer::UpdateToGPU()
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

void* IndexBuffer::MapBuffer(i32 start, i32 count, bool discard)
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

void IndexBuffer::UnmapBuffer()
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
