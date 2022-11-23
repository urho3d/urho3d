// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

#include "../../Precompiled.h"

#include "../../Graphics/Camera.h"
#include "../../Graphics/Graphics.h"
#include "../../Graphics/Renderer.h"
#include "../../GraphicsAPI/GraphicsImpl.h"
#include "../../GraphicsAPI/RenderSurface.h"
#include "../../GraphicsAPI/Texture.h"

#include "../../DebugNew.h"

namespace Urho3D
{

void RenderSurface::Constructor_D3D11(Texture* parentTexture)
{
    parentTexture_ = parentTexture;
    renderTargetView_ = nullptr;
    readOnlyView_ = nullptr;
}

void RenderSurface::Release_D3D11()
{
    Graphics* graphics = parentTexture_->GetGraphics();
    if (graphics && renderTargetView_)
    {
        for (unsigned i = 0; i < MAX_RENDERTARGETS; ++i)
        {
            if (graphics->GetRenderTarget(i) == this)
                graphics->ResetRenderTarget(i);
        }

        if (graphics->GetDepthStencil() == this)
            graphics->ResetDepthStencil();
    }

    URHO3D_SAFE_RELEASE(renderTargetView_);
    URHO3D_SAFE_RELEASE(readOnlyView_);
}

bool RenderSurface::CreateRenderBuffer_D3D11(unsigned width, unsigned height, unsigned format, int multiSample)
{
    // Not used on Direct3D
    return false;
}

void RenderSurface::OnDeviceLost_D3D11()
{
    // No-op on Direct3D
}

}
