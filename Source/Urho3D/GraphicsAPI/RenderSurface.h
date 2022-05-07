// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

#pragma once

#include "../Graphics/Viewport.h"
#include "../GraphicsAPI/GraphicsDefs.h"

namespace Urho3D
{

class Texture;

/// %Color or depth-stencil surface that can be rendered into.
class URHO3D_API RenderSurface : public RefCounted
{
    friend class Texture2D;
    friend class Texture2DArray;
    friend class TextureCube;

public:
    /// Construct with parent texture.
    explicit RenderSurface(Texture* parentTexture);
    /// Destruct.
    ~RenderSurface() override;

    /// Set number of viewports.
    /// @property
    void SetNumViewports(unsigned num);
    /// Set viewport.
    /// @property{set_viewports}
    void SetViewport(unsigned index, Viewport* viewport);
    /// Set viewport update mode. Default is to update when visible.
    /// @property
    void SetUpdateMode(RenderSurfaceUpdateMode mode);
    /// Set linked color rendertarget.
    /// @property
    void SetLinkedRenderTarget(RenderSurface* renderTarget);
    /// Set linked depth-stencil surface.
    /// @property
    void SetLinkedDepthStencil(RenderSurface* depthStencil);
    /// Queue manual update of the viewport(s).
    void QueueUpdate();
    /// Release surface.
    void Release();
    /// Mark the GPU resource destroyed on graphics context destruction. Only used on OpenGL.
    void OnDeviceLost();
    /// Create renderbuffer that cannot be sampled as a texture. Only used on OpenGL.
    bool CreateRenderBuffer(unsigned width, unsigned height, unsigned format, int multiSample);

    /// Return width.
    /// @property
    int GetWidth() const;

    /// Return height.
    /// @property
    int GetHeight() const;

    /// Return usage.
    /// @property
    TextureUsage GetUsage() const;

    /// Return multisampling level.
    int GetMultiSample() const;

    /// Return multisampling autoresolve mode.
    bool GetAutoResolve() const;

    /// Return number of viewports.
    /// @property
    unsigned GetNumViewports() const { return viewports_.Size(); }

    /// Return viewport by index.
    /// @property{get_viewports}
    Viewport* GetViewport(unsigned index) const;

    /// Return viewport update mode.
    /// @property
    RenderSurfaceUpdateMode GetUpdateMode() const { return updateMode_; }

    /// Return linked color rendertarget.
    /// @property
    RenderSurface* GetLinkedRenderTarget() const { return linkedRenderTarget_; }

    /// Return linked depth-stencil surface.
    /// @property
    RenderSurface* GetLinkedDepthStencil() const { return linkedDepthStencil_; }

    /// Return whether manual update queued. Called internally.
    bool IsUpdateQueued() const { return updateQueued_; }

    /// Reset update queued flag. Called internally.
    void ResetUpdateQueued();

    /// Return parent texture.
    /// @property
    Texture* GetParentTexture() const { return parentTexture_; }

    /// Return Direct3D9 surface.
    void* GetSurface() const { return surface_; }

    /// Return Direct3D11 rendertarget or depth-stencil view. Not valid on OpenGL.
    void* GetRenderTargetView() const { return renderTargetView_; }

    /// Return Direct3D11 read-only depth-stencil view. May be null if not applicable. Not valid on OpenGL.
    void* GetReadOnlyView() const { return readOnlyView_; }

    /// Return surface's OpenGL target.
    unsigned GetTarget() const { return target_; }

    /// Return OpenGL renderbuffer if created.
    unsigned GetRenderBuffer() const { return renderBuffer_; }

    /// Return whether multisampled rendertarget needs resolve.
    /// @property
    bool IsResolveDirty() const { return resolveDirty_; }

    /// Set or clear the need resolve flag. Called internally by Graphics.
    void SetResolveDirty(bool enable) { resolveDirty_ = enable; }

private:
#ifdef URHO3D_OPENGL
    void Constructor_OGL(Texture* parentTexture);
    bool CreateRenderBuffer_OGL(unsigned width, unsigned height, unsigned format, int multiSample);
    void OnDeviceLost_OGL();
    void Release_OGL();
#endif // def URHO3D_OPENGL

#ifdef URHO3D_D3D9
    void Constructor_D3D9(Texture* parentTexture);
    bool CreateRenderBuffer_D3D9(unsigned width, unsigned height, unsigned format, int multiSample);
    void OnDeviceLost_D3D9();
    void Release_D3D9();
#endif // def URHO3D_D3D9

#ifdef URHO3D_D3D11
    void Constructor_D3D11(Texture* parentTexture);
    bool CreateRenderBuffer_D3D11(unsigned width, unsigned height, unsigned format, int multiSample);
    void OnDeviceLost_D3D11();
    void Release_D3D11();
#endif // def URHO3D_D3D11

    /// Parent texture.
    Texture* parentTexture_;

    // https://github.com/doxygen/doxygen/issues/7623
    union
    {
        /// Direct3D9 surface.
        /// @nobind
        void* surface_;
        /// Direct3D11 rendertarget or depth-stencil view.
        /// @nobind
        void* renderTargetView_;
        /// OpenGL renderbuffer name.
        /// @nobind
        unsigned renderBuffer_;
    };

    // https://github.com/doxygen/doxygen/issues/7623
    union
    {
        /// Direct3D11 read-only depth-stencil view. Present only on depth-stencil surfaces.
        /// @nobind
        void* readOnlyView_;
        /// OpenGL target.
        /// @nobind
        unsigned target_;
    };

    /// Viewports.
    Vector<SharedPtr<Viewport> > viewports_;
    /// Linked color buffer.
    WeakPtr<RenderSurface> linkedRenderTarget_;
    /// Linked depth buffer.
    WeakPtr<RenderSurface> linkedDepthStencil_;
    /// Update mode for viewports.
    RenderSurfaceUpdateMode updateMode_{SURFACE_UPDATEVISIBLE};
    /// Update queued flag.
    bool updateQueued_{};
    /// Multisampled resolve dirty flag.
    bool resolveDirty_{};
};

}
