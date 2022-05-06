// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

#pragma once

#include "../Container/Ptr.h"
#include "../GraphicsAPI/RenderSurface.h"
#include "../GraphicsAPI/Texture.h"

namespace Urho3D
{

class Deserializer;
class Image;

/// Cube texture resource.
class URHO3D_API TextureCube : public Texture
{
    URHO3D_OBJECT(TextureCube, Texture);

public:
    /// Construct.
    explicit TextureCube(Context* context);
    /// Destruct.
    ~TextureCube() override;
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

    /// Set size, format, usage and multisampling parameter for rendertargets. Note that cube textures always use autoresolve when multisampled due to lacking support (on all APIs) to multisample them in a shader. Return true if successful.
    bool SetSize(int size, unsigned format, TextureUsage usage = TEXTURE_STATIC, int multiSample = 1);
    /// Set data either partially or fully on a face's mip level. Return true if successful.
    bool SetData(CubeMapFace face, unsigned level, int x, int y, int width, int height, const void* data);
    /// Set data of one face from a stream. Return true if successful.
    bool SetData(CubeMapFace face, Deserializer& source);
    /// Set data of one face from an image. Return true if successful. Optionally make a single channel image alpha-only.
    bool SetData(CubeMapFace face, Image* image, bool useAlpha = false);

    /// Get data from a face's mip level. The destination buffer must be big enough. Return true if successful.
    bool GetData(CubeMapFace face, unsigned level, void* dest) const;
    /// Get image data from a face's zero mip level. Only RGB and RGBA textures are supported.
    SharedPtr<Image> GetImage(CubeMapFace face) const;

    /// Return render surface for one face.
    /// @property{get_renderSurfaces}
    RenderSurface* GetRenderSurface(CubeMapFace face) const { return renderSurfaces_[face]; }

protected:
    /// Create the GPU texture.
    bool Create() override;

private:
#ifdef URHO3D_OPENGL
    void OnDeviceLost_OGL();
    void OnDeviceReset_OGL();
    void Release_OGL();
    bool SetData_OGL(CubeMapFace face, unsigned level, int x, int y, int width, int height, const void* data);
    bool SetData_OGL(CubeMapFace face, Deserializer& source);
    bool SetData_OGL(CubeMapFace face, Image* image, bool useAlpha = false);
    bool GetData_OGL(CubeMapFace face, unsigned level, void* dest) const;
    bool Create_OGL();
#endif // def URHO3D_OPENGL

#ifdef URHO3D_D3D9
    void OnDeviceLost_D3D9();
    void OnDeviceReset_D3D9();
    void Release_D3D9();
    bool SetData_D3D9(CubeMapFace face, unsigned level, int x, int y, int width, int height, const void* data);
    bool SetData_D3D9(CubeMapFace face, Deserializer& source);
    bool SetData_D3D9(CubeMapFace face, Image* image, bool useAlpha = false);
    bool GetData_D3D9(CubeMapFace face, unsigned level, void* dest) const;
    bool Create_D3D9();
#endif // def URHO3D_D3D9

#ifdef URHO3D_D3D11
    void OnDeviceLost_D3D11();
    void OnDeviceReset_D3D11();
    void Release_D3D11();
    bool SetData_D3D11(CubeMapFace face, unsigned level, int x, int y, int width, int height, const void* data);
    bool SetData_D3D11(CubeMapFace face, Deserializer& source);
    bool SetData_D3D11(CubeMapFace face, Image* image, bool useAlpha = false);
    bool GetData_D3D11(CubeMapFace face, unsigned level, void* dest) const;
    bool Create_D3D11();
#endif // def URHO3D_D3D11

    /// Handle render surface update event.
    void HandleRenderSurfaceUpdate(StringHash eventType, VariantMap& eventData);

    /// Render surfaces.
    SharedPtr<RenderSurface> renderSurfaces_[MAX_CUBEMAP_FACES];
    /// Memory use per face.
    unsigned faceMemoryUse_[MAX_CUBEMAP_FACES]{};
    /// Face image files acquired during BeginLoad.
    Vector<SharedPtr<Image> > loadImages_;
    /// Parameter file acquired during BeginLoad.
    SharedPtr<XMLFile> loadParameters_;
};

}
