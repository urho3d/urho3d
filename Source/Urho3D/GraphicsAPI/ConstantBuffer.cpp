// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

#include "../Precompiled.h"

#include "../Graphics/Graphics.h"
#include "../GraphicsAPI/ConstantBuffer.h"
#include "../IO/Log.h"

#include "../DebugNew.h"

namespace Urho3D
{

ConstantBuffer::ConstantBuffer(Context* context) :
    Object(context),
    GPUObject(GetSubsystem<Graphics>())
{
}

ConstantBuffer::~ConstantBuffer()
{
    Release();
}

void ConstantBuffer::SetParameter(unsigned offset, unsigned size, const void* data)
{
    if (offset + size > size_)
        return; // Would overflow the buffer

    memcpy(&shadowData_[offset], data, size);
    dirty_ = true;
}

void ConstantBuffer::SetVector3ArrayParameter(unsigned offset, unsigned rows, const void* data)
{
    if (offset + rows * 4 * sizeof(float) > size_)
        return; // Would overflow the buffer

    auto* dest = (float*)&shadowData_[offset];
    const auto* src = (const float*)data;

    while (rows--)
    {
        *dest++ = *src++;
        *dest++ = *src++;
        *dest++ = *src++;
        ++dest; // Skip over the w coordinate
    }

    dirty_ = true;
}

void ConstantBuffer::Release()
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

void ConstantBuffer::OnDeviceReset()
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

bool ConstantBuffer::SetSize(unsigned size)
{
    GAPI gapi = Graphics::GetGAPI();

#ifdef URHO3D_OPENGL
    if (gapi == GAPI_OPENGL)
        return SetSize_OGL(size);
#endif

#ifdef URHO3D_D3D9
    if (gapi == GAPI_D3D9)
        return SetSize_D3D9(size);
#endif

#ifdef URHO3D_D3D11
    if (gapi == GAPI_D3D11)
        return SetSize_D3D11(size);
#endif

    return {}; // Prevent warning
}

void ConstantBuffer::Apply()
{
    GAPI gapi = Graphics::GetGAPI();

#ifdef URHO3D_OPENGL
    if (gapi == GAPI_OPENGL)
        return Apply_OGL();
#endif

#ifdef URHO3D_D3D9
    if (gapi == GAPI_D3D9)
        return Apply_D3D9();
#endif

#ifdef URHO3D_D3D11
    if (gapi == GAPI_D3D11)
        return Apply_D3D11();
#endif
}

}
