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

#include "../Container/ArrayPtr.h"
#include "../Resource/Resource.h"

struct SDL_Surface;

namespace Urho3D
{

static const int COLOR_LUT_SIZE = 16;

/// Supported compressed image formats.
enum CompressedFormat
{
    CF_NONE = 0,
    CF_RGBA,
    CF_DXT1,
    CF_DXT3,
    CF_DXT5,
    CF_ETC1,
    CF_PVRTC_RGB_2BPP,
    CF_PVRTC_RGBA_2BPP,
    CF_PVRTC_RGB_4BPP,
    CF_PVRTC_RGBA_4BPP,
};

/// Compressed image mip level.
struct CompressedLevel
{
    /// Construct empty.
    CompressedLevel() :
        data_(0),
        width_(0),
        height_(0),
        depth_(0),
        blockSize_(0),
        dataSize_(0),
        rowSize_(0),
        rows_(0)
    {
    }

    /// Decompress to RGBA. The destination buffer required is width * height * 4 bytes. Return true if successful.
    bool Decompress(unsigned char* dest);

    /// Compressed image data.
    unsigned char* data_;
    /// Compression format.
    CompressedFormat format_;
    /// Width.
    int width_;
    /// Height.
    int height_;
    /// Depth.
    int depth_;
    /// Block size in bytes.
    unsigned blockSize_;
    /// Total data size in bytes.
    unsigned dataSize_;
    /// Row size in bytes.
    unsigned rowSize_;
    /// Number of rows.
    unsigned rows_;
};

/// %Image resource.
class URHO3D_API Image : public Resource
{
    OBJECT(Image);

public:
    /// Construct empty.
    Image(Context* context);
    /// Destruct.
    virtual ~Image();
    /// Register object factory.
    static void RegisterObject(Context* context);

    /// Load resource from stream. May be called from a worker thread. Return true if successful.
    virtual bool BeginLoad(Deserializer& source);
    /// Save the image to a stream. Regardless of original format, the image is saved as png. Compressed image data is not supported. Return true if successful.
    virtual bool Save(Serializer& dest) const;

    /// Set 2D size and number of color components. Old image data will be destroyed and new data is undefined. Return true if successful.
    bool SetSize(int width, int height, unsigned components);
    /// Set 3D size and number of color components. Old image data will be destroyed and new data is undefined. Return true if successful.
    bool SetSize(int width, int height, int depth, unsigned components);
    /// Set new image data.
    void SetData(const unsigned char* pixelData);
    /// Set a 2D pixel.
    void SetPixel(int x, int y, const Color& color);
    /// Set a 3D pixel.
    void SetPixel(int x, int y, int z, const Color& color);
    /// Set a 2D pixel with an integer color. R component is in the 8 lowest bits.
    void SetPixelInt(int x, int y, unsigned uintColor);
    /// Set a 3D pixel with an integer color. R component is in the 8 lowest bits.
    void SetPixelInt(int x, int y, int z, unsigned uintColor);
    /// Load as color LUT. Return true if successful.
    bool LoadColorLUT(Deserializer& source);
    /// Flip image horizontally. Return true if successful.
    bool FlipHorizontal();
    /// Flip image vertically. Return true if successful.
    bool FlipVertical();
    /// Resize image by bilinear resampling. Return true if successful.
    bool Resize(int width, int height);
    /// Clear the image with a color.
    void Clear(const Color& color);
    /// Clear the image with an integer color. R component is in the 8 lowest bits.
    void ClearInt(unsigned uintColor);
    /// Save in BMP format. Return true if successful.
    bool SaveBMP(const String& fileName) const;
    /// Save in PNG format. Return true if successful.
    bool SavePNG(const String& fileName) const;
    /// Save in TGA format. Return true if successful.
    bool SaveTGA(const String& fileName) const;
    /// Save in JPG format with compression quality. Return true if successful.
    bool SaveJPG(const String& fileName, int quality) const;

    /// Return a 2D pixel color.
    Color GetPixel(int x, int y) const;
    /// Return a 3D pixel color.
    Color GetPixel(int x, int y, int z) const;
    /// Return a 2D pixel integer color. R component is in the 8 lowest bits.
    unsigned GetPixelInt(int x, int y) const;
    /// Return a 3D pixel integer color. R component is in the 8 lowest bits.
    unsigned GetPixelInt(int x, int y, int z) const;
    /// Return a bilinearly sampled 2D pixel color. X and Y have the range 0-1.
    Color GetPixelBilinear(float x, float y) const;
    /// Return a trilinearly sampled 3D pixel color. X, Y and Z have the range 0-1.
    Color GetPixelTrilinear(float x, float y, float z) const;
    /// Return width.
    int GetWidth() const { return width_; }
    /// Return height.
    int GetHeight() const { return height_; }
    /// Return depth.
    int GetDepth() const { return depth_; }
    /// Return number of color components.
    unsigned GetComponents() const { return components_; }
    /// Return pixel data.
    unsigned char* GetData() const { return data_; }
    /// Return whether is compressed.
    bool IsCompressed() const { return compressedFormat_ != CF_NONE; }
    /// Return compressed format.
    CompressedFormat GetCompressedFormat() const { return compressedFormat_; }
    /// Return number of compressed mip levels.
    unsigned GetNumCompressedLevels() const { return numCompressedLevels_; }
    /// Return next mip level by bilinear filtering.
    SharedPtr<Image> GetNextLevel() const;
    /// Return a compressed mip level.
    CompressedLevel GetCompressedLevel(unsigned index) const;
    /// Return subimage from the image by the defined rect or null if failed. 3D images are not supported. You must free the subimage yourself.
    Image* GetSubimage(const IntRect& rect) const;
    /// Return an SDL surface from the image, or null if failed. Only RGB images are supported. Specify rect to only return partial image. You must free the surface yourself.
    SDL_Surface* GetSDLSurface(const IntRect& rect = IntRect::ZERO) const;
    /// Precalculate the mip levels. Used by asynchronous texture loading.
    void PrecalculateLevels();

private:
    /// Decode an image using stb_image.
    static unsigned char* GetImageData(Deserializer& source, int& width, int& height, unsigned& components);
    /// Free an image file's pixel data.
    static void FreeImageData(unsigned char* pixelData);

    /// Width.
    int width_;
    /// Height.
    int height_;
    /// Depth.
    int depth_;
    /// Number of color components.
    unsigned components_;
    /// Number of compressed mip levels.
    unsigned numCompressedLevels_;
    /// Compressed format.
    CompressedFormat compressedFormat_;
    /// Pixel data.
    SharedArrayPtr<unsigned char> data_;
    /// Precalculated mip level image.
    SharedPtr<Image> nextLevel_;
};

}
