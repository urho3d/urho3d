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

#include "../../Precompiled.h"

#include "../../Graphics/Camera.h"
#include "../../Graphics/Graphics.h"
#include "../../Graphics/GraphicsImpl.h"
#include "../../Graphics/Renderer.h"
#include "../../Graphics/RenderSurface.h"
#include "../../Graphics/Texture.h"

#include "../../DebugNew.h"

namespace Urho3D
{

RenderSurface::RenderSurface(Texture* parentTexture) :      // NOLINT(hicpp-member-init)
    parentTexture_(parentTexture),
    renderTargetView_(nullptr),
    readOnlyView_(nullptr)
{
}

void RenderSurface::Release()
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

bool RenderSurface::CreateRenderBuffer(unsigned width, unsigned height, unsigned format, int multiSample)
{
    // Not used on Direct3D
    return false;
}

void RenderSurface::OnDeviceLost()
{
    // No-op on Direct3D
}

}
