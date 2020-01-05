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
#include "../Resource/Image.h"

namespace Urho3D
{

/// 3D texture resource.
class URHO3D_API Texture3D : public Texture
{
    URHO3D_OBJECT(Texture3D, Texture);

public:
    /// Construct.
    explicit Texture3D(Context* context);
    /// Destruct.
    ~Texture3D() override;
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

    /// Set size, format and usage. Zero size will follow application window size. Return true if successful.
    bool SetSize(int width, int height, int depth, unsigned format, TextureUsage usage = TEXTURE_STATIC);
    /// Set data either partially or fully on a mip level. Return true if successful.
    bool SetData(unsigned level, int x, int y, int z, int width, int height, int depth, const void* data);
    /// Set data from an image. Return true if successful. Optionally make a single channel image alpha-only.
    bool SetData(Image* image, bool useAlpha = false);

    /// Get data from a mip level. The destination buffer must be big enough. Return true if successful.
    bool GetData(unsigned level, void* dest) const;

protected:
    /// Create the GPU texture.
    bool Create() override;

private:
    /// Image file acquired during BeginLoad.
    SharedPtr<Image> loadImage_;
    /// Parameter file acquired during BeginLoad.
    SharedPtr<XMLFile> loadParameters_;
};

}
