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

#pragma once

#include "../Container/Ptr.h"
#include "../Graphics/RenderSurface.h"
#include "../Graphics/Texture.h"

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
    RenderSurface* GetRenderSurface(CubeMapFace face) const { return renderSurfaces_[face]; }

protected:
    /// Create the GPU texture.
    bool Create() override;

private:
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
