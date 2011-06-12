//
// Urho3D Engine
// Copyright (c) 2008-2011 Lasse Öörni
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

#include "Rect.h"
#include "GraphicsDefs.h"
#include "SharedPtr.h"

class Camera;
class Scene;
class Texture;

/// Viewport definition either for a RenderSurface or the backbuffer
struct Viewport
{
    /// Construct with defaults
    Viewport();
    /// Construct with a full rectangle
    Viewport(Scene* scene, Camera* camera);
    /// Construct with a specified rectangle
    Viewport(Scene* scene, Camera* camera, const IntRect& rect);
    
    /// Scene pointer
    WeakPtr<Scene> scene_;
    /// Camera pointer
    WeakPtr<Camera> camera_;
    /// Viewport rectangle
    IntRect rect_;
};

/// Color or depth stencil surface that can be rendered into
class RenderSurface : public RefCounted
{
    friend class Texture2D;
    friend class TextureCube;
    
public:
    /// Construct with parent texture and target
    RenderSurface(Texture* parentTexture, unsigned target);
    /// Destruct
    ~RenderSurface();
    
    /// Set viewport for auxiliary view rendering
    void SetViewport(const Viewport& viewport);
    /// Set linked color buffer
    void SetLinkedRenderTarget(RenderSurface* renderTarget);
    /// Set linked depth buffer
    void SetLinkedDepthBuffer(RenderSurface* depthBuffer);
    /// Release surface
    void Release();
    
    /// Return parent texture
    Texture* GetParentTexture() const { return parentTexture_; }
    /// Return surface's OpenGL target
    unsigned GetTarget() const { return target_; }
    /// Return width
    int GetWidth() const;
    /// Return height
    int GetHeight() const;
    /// Return usage
    TextureUsage GetUsage() const;
    /// Return auxiliary view rendering viewport
    const Viewport& GetViewport() const { return viewport_; }
    /// Return linked color buffer
    RenderSurface* GetLinkedRenderTarget() const { return linkedRenderTarget_; }
    /// Return linked depth buffer
    RenderSurface* GetLinkedDepthBuffer() const { return linkedDepthBuffer_; }
    
private:
    /// Parent texture
    Texture* parentTexture_;
    /// OpenGL target
    unsigned target_;
    /// Viewport
    Viewport viewport_;
    /// Linked color buffer
    WeakPtr<RenderSurface> linkedRenderTarget_;
    /// Linked depth buffer
    WeakPtr<RenderSurface> linkedDepthBuffer_;
};
