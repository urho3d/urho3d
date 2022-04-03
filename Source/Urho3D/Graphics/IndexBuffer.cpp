//
// Copyright (c) 2008-2022 the Urho3D project.
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

// This file contains IndexBuffer code common to all graphics APIs.

#include "../Precompiled.h"

#include "../Graphics/Graphics.h"
#include "../Graphics/IndexBuffer.h"
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
            shadowData_ = new unsigned char[indexCount_ * indexSize_];
        else
            shadowData_.Reset();

        shadowed_ = enable;
    }
}

bool IndexBuffer::SetSize(unsigned indexCount, bool largeIndices, bool dynamic)
{
    Unlock();

    indexCount_ = indexCount;
    indexSize_ = (unsigned)(largeIndices ? sizeof(unsigned) : sizeof(unsigned short));
    dynamic_ = dynamic;

    if (shadowed_ && indexCount_ && indexSize_)
        shadowData_ = new unsigned char[indexCount_ * indexSize_];
    else
        shadowData_.Reset();

    return Create();
}

bool IndexBuffer::GetUsedVertexRange(unsigned start, unsigned count, unsigned& minVertex, unsigned& vertexCount)
{
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

    minVertex = M_MAX_UNSIGNED;
    unsigned maxVertex = 0;

    if (indexSize_ == sizeof(unsigned))
    {
        unsigned* indices = ((unsigned*)shadowData_.Get()) + start;

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
        unsigned short* indices = ((unsigned short*)shadowData_.Get()) + start;

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

void IndexBuffer::OnDeviceLost()
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

void IndexBuffer::OnDeviceReset()
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

void IndexBuffer::Release()
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

bool IndexBuffer::SetData(const void* data)
{
    GAPI gapi = Graphics::GetGAPI();

#ifdef URHO3D_OPENGL
    if (gapi == GAPI_OPENGL)
        return SetData_OGL(data);
#endif

#ifdef URHO3D_D3D9
    if (gapi == GAPI_D3D9)
        return SetData_D3D9(data);;
#endif

#ifdef URHO3D_D3D11
    if (gapi == GAPI_D3D11)
        return SetData_D3D11(data);;
#endif
}

bool IndexBuffer::SetDataRange(const void* data, unsigned start, unsigned count, bool discard)
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
}

void* IndexBuffer::Lock(unsigned start, unsigned count, bool discard)
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
}

void IndexBuffer::Unlock()
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

bool IndexBuffer::Create()
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
}

bool IndexBuffer::UpdateToGPU()
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
}

void* IndexBuffer::MapBuffer(unsigned start, unsigned count, bool discard)
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
}

void IndexBuffer::UnmapBuffer()
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
