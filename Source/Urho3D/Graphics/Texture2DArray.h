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

/// 2D texture array resource.
class URHO3D_API Texture2DArray : public Texture
{
    URHO3D_OBJECT(Texture2DArray, Texture)

public:
    /// Construct.
    explicit Texture2DArray(Context* context);
    /// Destruct.
    ~Texture2DArray() override;
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

    /// Set the number of layers in the texture. To be used before SetData.
    void SetLayers(unsigned layers);
    /// Set layers, size, format and usage. Set layers to zero to leave them unchanged. Return true if successful.
    bool SetSize(unsigned layers, int width, int height, unsigned format, TextureUsage usage = TEXTURE_STATIC);
    /// Set data either partially or fully on a layer's mip level. Return true if successful.
    bool SetData(unsigned layer, unsigned level, int x, int y, int width, int height, const void* data);
    /// Set data of one layer from a stream. Return true if successful.
    bool SetData(unsigned layer, Deserializer& source);
    /// Set data of one layer from an image. Return true if successful. Optionally make a single channel image alpha-only.
    bool SetData(unsigned layer, Image* image, bool useAlpha = false);

    /// Return number of layers in the texture.
    unsigned GetLayers() const { return layers_; }
    /// Get data from a mip level. The destination buffer must be big enough. Return true if successful.
    bool GetData(unsigned layer, unsigned level, void* dest) const;
    /// Return render surface.
    RenderSurface* GetRenderSurface() const { return renderSurface_; }

protected:
    /// Create the GPU texture.
    bool Create() override;

private:
    /// Handle render surface update event.
    void HandleRenderSurfaceUpdate(StringHash eventType, VariantMap& eventData);

    /// Texture array layers number.
    unsigned layers_{};
    /// Render surface.
    SharedPtr<RenderSurface> renderSurface_;
    /// Memory use per layer.
    PODVector<unsigned> layerMemoryUse_;
    /// Layer image files acquired during BeginLoad.
    Vector<SharedPtr<Image> > loadImages_;
    /// Parameter file acquired during BeginLoad.
    SharedPtr<XMLFile> loadParameters_;
};

}
