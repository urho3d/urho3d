//
// Copyright (c) 2008-2015 the Urho3D project.
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

#include "../../Graphics/GraphicsDefs.h"
#include "../../Graphics/Viewport.h"

namespace Urho3D
{

class Camera;
class Scene;
class Texture;

/// %Color or depth-stencil surface that can be rendered into.
class URHO3D_API RenderSurface : public RefCounted
{
    friend class Texture2D;
    friend class TextureCube;
    
public:
    /// Construct with parent texture.
    RenderSurface(Texture* parentTexture);
    /// Destruct.
    ~RenderSurface();
    
    /// Set number of viewports.
    void SetNumViewports(unsigned num);
    /// Set viewport.
    void SetViewport(unsigned index, Viewport* viewport);
    /// Set viewport update mode. Default is to update when visible.
    void SetUpdateMode(RenderSurfaceUpdateMode mode);
    /// Set linked color rendertarget.
    void SetLinkedRenderTarget(RenderSurface* renderTarget);
    /// Set linked depth-stencil surface.
    void SetLinkedDepthStencil(RenderSurface* depthStencil);
    /// Queue manual update of the viewport(s).
    void QueueUpdate();
    /// Create a renderbuffer. Return true if successful.
    bool CreateRenderBuffer(unsigned width, unsigned height, unsigned format);
    /// Handle device loss.
    void OnDeviceLost();
    /// Release renderbuffer if any.
    void Release();
    
    /// Return parent texture.
    Texture* GetParentTexture() const { return parentTexture_; }
    /// Return renderbuffer if created.
    unsigned GetRenderBuffer() const { return renderBuffer_; }
    /// Return width.
    int GetWidth() const;
    /// Return height.
    int GetHeight() const;
    /// Return usage.
    TextureUsage GetUsage() const;
    /// Return number of viewports.
    unsigned GetNumViewports() const { return viewports_.Size(); }
    /// Return viewport by index.
    Viewport* GetViewport(unsigned index) const;
    /// Return viewport update mode.
    RenderSurfaceUpdateMode GetUpdateMode() const { return updateMode_; }
    /// Return linked color buffer.
    RenderSurface* GetLinkedRenderTarget() const { return linkedRenderTarget_; }
    /// Return linked depth buffer.
    RenderSurface* GetLinkedDepthStencil() const { return linkedDepthStencil_; }
    
    /// Set surface's OpenGL target.
    void SetTarget(unsigned target);
    /// Return surface's OpenGL target.
    unsigned GetTarget() const { return target_; }
    /// Clear update flag. Called by Renderer.
    void WasUpdated();
    
private:
    /// Parent texture.
    Texture* parentTexture_;
    /// OpenGL target.
    unsigned target_;
    /// OpenGL renderbuffer.
    unsigned renderBuffer_;
    /// Viewports.
    Vector<SharedPtr<Viewport> > viewports_;
    /// Linked color buffer.
    WeakPtr<RenderSurface> linkedRenderTarget_;
    /// Linked depth buffer.
    WeakPtr<RenderSurface> linkedDepthStencil_;
    /// Update mode for viewports.
    RenderSurfaceUpdateMode updateMode_;
    /// Update queued flag.
    bool updateQueued_;
};

}
