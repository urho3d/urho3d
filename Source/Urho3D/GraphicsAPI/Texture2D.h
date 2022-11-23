// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

#pragma once

#include "../Container/Ptr.h"
#include "../GraphicsAPI/RenderSurface.h"
#include "../GraphicsAPI/Texture.h"

namespace Urho3D
{

class Image;
class XMLFile;

/// 2D texture resource.
class URHO3D_API Texture2D : public Texture
{
    URHO3D_OBJECT(Texture2D, Texture);

public:
    /// Construct.
    explicit Texture2D(Context* context);
    /// Destruct.
    ~Texture2D() override;
    /// Register object factory.
    /// @nobind
    static void RegisterObject(Context* context);

    /// Load resource from stream. May be called from a worker thread. Return true if successful.
    bool BeginLoad(Deserializer& source) override;
    /// Finish resource loading. Always called from the main thread. Return true if successful.
    bool EndLoad() override;
    /// Mark the GPU resource destroyed on context destruction.
    void OnDeviceLost() override;
    /// Recreate the GPU resource and restore data if applicable.
    void OnDeviceReset() override;
    /// Release the texture.
    void Release() override;

    /// Set size, format, usage and multisampling parameters for rendertargets. Zero size will follow application window size. Return true if successful.
    /** Autoresolve true means the multisampled texture will be automatically resolved to 1-sample after being rendered to and before being sampled as a texture.
        Autoresolve false means the multisampled texture will be read as individual samples in the shader and is not supported on Direct3D9.
        */
    bool SetSize(int width, int height, unsigned format, TextureUsage usage = TEXTURE_STATIC, int multiSample = 1, bool autoResolve = true);
    /// Set data either partially or fully on a mip level. Return true if successful.
    bool SetData(unsigned level, int x, int y, int width, int height, const void* data);
    /// Set data from an image. Return true if successful. Optionally make a single channel image alpha-only.
    bool SetData(Image* image, bool useAlpha = false);

    /// Get data from a mip level. The destination buffer must be big enough. Return true if successful.
    bool GetData(unsigned level, void* dest) const;
    /// Get image data from zero mip level. Only RGB and RGBA textures are supported.
    bool GetImage(Image& image) const;
    /// Get image data from zero mip level. Only RGB and RGBA textures are supported.
    SharedPtr<Image> GetImage() const;

    /// Return render surface.
    /// @property
    RenderSurface* GetRenderSurface() const { return renderSurface_; }

protected:
    /// Create the GPU texture.
    bool Create() override;

private:
#ifdef URHO3D_OPENGL
    void OnDeviceLost_OGL();
    void OnDeviceReset_OGL();
    void Release_OGL();
    bool SetData_OGL(unsigned level, int x, int y, int width, int height, const void* data);
    bool SetData_OGL(Image* image, bool useAlpha);
    bool GetData_OGL(unsigned level, void* dest) const;
    bool Create_OGL();
#endif // def URHO3D_OPENGL

#ifdef URHO3D_D3D9
    void OnDeviceLost_D3D9();
    void OnDeviceReset_D3D9();
    void Release_D3D9();
    bool SetData_D3D9(unsigned level, int x, int y, int width, int height, const void* data);
    bool SetData_D3D9(Image* image, bool useAlpha);
    bool GetData_D3D9(unsigned level, void* dest) const;
    bool Create_D3D9();
#endif // def URHO3D_D3D9

#ifdef URHO3D_D3D11
    void OnDeviceLost_D3D11();
    void OnDeviceReset_D3D11();
    void Release_D3D11();
    bool SetData_D3D11(unsigned level, int x, int y, int width, int height, const void* data);
    bool SetData_D3D11(Image* image, bool useAlpha);
    bool GetData_D3D11(unsigned level, void* dest) const;
    bool Create_D3D11();
#endif // def URHO3D_D3D11

    /// Handle render surface update event.
    void HandleRenderSurfaceUpdate(StringHash eventType, VariantMap& eventData);

    /// Render surface.
    SharedPtr<RenderSurface> renderSurface_;
    /// Image file acquired during BeginLoad.
    SharedPtr<Image> loadImage_;
    /// Parameter file acquired during BeginLoad.
    SharedPtr<XMLFile> loadParameters_;
};

}
