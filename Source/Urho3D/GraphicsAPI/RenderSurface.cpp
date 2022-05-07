// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

#include "../Precompiled.h"

#include "../Graphics/Camera.h"
#include "../Graphics/Graphics.h"
#include "../Graphics/Renderer.h"
#include "../GraphicsAPI/GraphicsImpl.h"
#include "../GraphicsAPI/RenderSurface.h"
#include "../GraphicsAPI/Texture.h"

#include "../DebugNew.h"

namespace Urho3D
{

RenderSurface::~RenderSurface()
{
    Release();
}

void RenderSurface::SetNumViewports(unsigned num)
{
    viewports_.Resize(num);
}

void RenderSurface::SetViewport(unsigned index, Viewport* viewport)
{
    if (index >= viewports_.Size())
        viewports_.Resize(index + 1);

    viewports_[index] = viewport;
}

void RenderSurface::SetUpdateMode(RenderSurfaceUpdateMode mode)
{
    updateMode_ = mode;
}

void RenderSurface::SetLinkedRenderTarget(RenderSurface* renderTarget)
{
    if (renderTarget != this)
        linkedRenderTarget_ = renderTarget;
}

void RenderSurface::SetLinkedDepthStencil(RenderSurface* depthStencil)
{
    if (depthStencil != this)
        linkedDepthStencil_ = depthStencil;
}

void RenderSurface::QueueUpdate()
{
    updateQueued_ = true;
}

void RenderSurface::ResetUpdateQueued()
{
    updateQueued_ = false;
}

int RenderSurface::GetWidth() const
{
    return parentTexture_->GetWidth();
}

int RenderSurface::GetHeight() const
{
    return parentTexture_->GetHeight();
}

TextureUsage RenderSurface::GetUsage() const
{
    return parentTexture_->GetUsage();
}

int RenderSurface::GetMultiSample() const
{
    return parentTexture_->GetMultiSample();
}

bool RenderSurface::GetAutoResolve() const
{
    return parentTexture_->GetAutoResolve();
}

Viewport* RenderSurface::GetViewport(unsigned index) const
{
    return index < viewports_.Size() ? viewports_[index] : nullptr;
}

RenderSurface::RenderSurface(Texture* parentTexture)
{
    GAPI gapi = Graphics::GetGAPI();

#ifdef URHO3D_OPENGL
    if (gapi == GAPI_OPENGL)
    {
        Constructor_OGL(parentTexture);
        return;
    }
#endif

#ifdef URHO3D_D3D9
    if (gapi == GAPI_D3D9)
    {
        Constructor_D3D9(parentTexture);
        return;
    }
#endif

#ifdef URHO3D_D3D11
    if (gapi == GAPI_D3D11)
    {
        Constructor_D3D11(parentTexture);
        return;
    }
#endif
}

bool RenderSurface::CreateRenderBuffer(unsigned width, unsigned height, unsigned format, int multiSample)
{
    GAPI gapi = Graphics::GetGAPI();

#ifdef URHO3D_OPENGL
    if (gapi == GAPI_OPENGL)
        return CreateRenderBuffer_OGL(width, height, format, multiSample);
#endif

#ifdef URHO3D_D3D9
    if (gapi == GAPI_D3D9)
        return CreateRenderBuffer_D3D9(width, height, format, multiSample);
#endif

#ifdef URHO3D_D3D11
    if (gapi == GAPI_D3D11)
        return CreateRenderBuffer_D3D11(width, height, format, multiSample);
#endif

    return {}; // Prevent warning
}

void RenderSurface::OnDeviceLost()
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

void RenderSurface::Release()
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

}
