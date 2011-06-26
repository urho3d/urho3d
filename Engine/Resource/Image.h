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

#include "Resource.h"
#include "SharedArrayPtr.h"

/// Supported compressed image formats
enum CompressedFormat
{
    CF_NONE = 0,
    CF_DXT1,
    CF_DXT3,
    CF_DXT5
};

/// Compressed image mipmap level
struct CompressedLevel
{
    /// Construct as empty
    CompressedLevel() :
        data_(0),
        width_(0),
        height_(0),
        blockSize_(0),
        dataSize_(0),
        rowSize_(0),
        rows_(0)
    {
    }
    
    /// Image data
    unsigned char* data_;
    /// Width
    int width_;
    /// Height
    int height_;
    /// Block size in bytes
    unsigned blockSize_;
    /// Total data size in bytes
    unsigned dataSize_;
    /// Row size in bytes
    unsigned rowSize_;
    /// Number of rows
    unsigned rows_;
};

/// Image resource
class Image : public Resource
{
    OBJECT(Image);
    
public:
    /// Construct an empty image
    Image(Context* context);
    /// Destruct
    virtual ~Image();
    /// Register object factory
    static void RegisterObject(Context* context);
    
    /// Load resource. Return true if successful
    virtual bool Load(Deserializer& source);
    
    /// Set size and number of color components
    void SetSize(int width, int height, unsigned components);
    /// Set data
    void SetData(const unsigned char* pixelData);
    /// Save in BMP format. Return true if successful
    bool SaveBMP(const String& fileName);
    /// Save in TGA format. Return true if successful
    bool SaveTGA(const String& fileName);
    
    /// Return width
    int GetWidth() const { return width_; }
    /// Return height
    int GetHeight() const { return height_; }
    /// Return number of color components
    unsigned GetComponents() const { return components_; }
    /// Return pixel data
    unsigned char* GetData() const { return data_; }
    /// Return whether is compressed
    bool IsCompressed() const { return compressedFormat_ != CF_NONE; }
    /// Return compressed format
    CompressedFormat GetCompressedFormat() const { return compressedFormat_; }
    /// Return number of compressed mipmap levels
    unsigned GetNumCompressedLevels() const { return numCompressedLevels_; }
    /// Return next mipmap level by bilinear filtering
    SharedPtr<Image> GetNextLevel() const;
    /// Return a compressed mipmap level
    CompressedLevel GetCompressedLevel(unsigned index) const;
    
private:
    /// Decode an image using stb_image
    static unsigned char* GetImageData(Deserializer& source, int& width, int& height, unsigned& components);
    /// Free an image file's pixel data
    static void FreeImageData(unsigned char* pixelData);
    
    /// Width
    int width_;
    /// Height
    int height_;
    /// Number of color components
    unsigned components_;
    /// Number of compressed mipmap levels
    unsigned numCompressedLevels_;
    /// Compressed format
    CompressedFormat compressedFormat_;
    /// Pixel data
    SharedArrayPtr<unsigned char> data_;
};
