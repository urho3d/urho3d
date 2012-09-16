//
// Urho3D Engine
// Copyright (c) 2008-2012 Lasse Oorni
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

#pragma once

#include "GraphicsDefs.h"
#include "Viewport.h"

namespace Urho3D
{

class Texture;

/// %Color or depth-stencil surface that can be rendered into.
class RenderSurface : public RefCounted
{
    friend class Texture2D;
    friend class TextureCube;
    
public:
    /// Construct with parent texture.
    RenderSurface(Texture* parentTexture);
    /// Destruct.
    ~RenderSurface();
    
    /// Set viewport for auxiliary view rendering.
    void SetViewport(Viewport* viewport);
    /// Set linked color rendertarget.
    void SetLinkedRenderTarget(RenderSurface* renderTarget);
    /// Set linked depth-stencil surface.
    void SetLinkedDepthStencil(RenderSurface* depthStencil);
    /// Release surface.
    void Release();
    
    /// Return parent texture.
    Texture* GetParentTexture() const { return parentTexture_; }
    /// Return Direct3D surface.
    void* GetSurface() const { return surface_; }
    /// Return width.
    int GetWidth() const;
    /// Return height.
    int GetHeight() const;
    /// Return usage.
    TextureUsage GetUsage() const;
    /// Return auxiliary view rendering viewport.
    Viewport* GetViewport() const { return viewport_; }
    /// Return linked color rendertarget.
    RenderSurface* GetLinkedRenderTarget() const { return linkedRenderTarget_; }
    /// Return linked depth-stencil surface.
    RenderSurface* GetLinkedDepthStencil() const { return linkedDepthStencil_; }
    
private:
    /// Parent texture.
    Texture* parentTexture_;
    /// Direct3D surface.
    void* surface_;
    /// Viewport.
    SharedPtr<Viewport> viewport_;
    /// Linked color buffer.
    WeakPtr<RenderSurface> linkedRenderTarget_;
    /// Linked depth buffer.
    WeakPtr<RenderSurface> linkedDepthStencil_;
};

}
