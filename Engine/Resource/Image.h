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

#ifndef RESOURCE_IMAGE_H
#define RESOURCE_IMAGE_H

#include "Resource.h"
#include "SharedPtr.h"
#include "SharedArrayPtr.h"

//! Supported compressed image formats
enum CompressedFormat
{
    CF_NONE = 0,
    CF_DXT1,
    CF_DXT3,
    CF_DXT5
};

//! Description of a compressed image mipmap level
struct CompressedLevel
{
    //! Construct as empty
    CompressedLevel() :
        mData(0),
        mWidth(0),
        mHeight(0),
        mBlockSize(0),
        mDataSize(0),
        mRowSize(0),
        mRows(0)
    {
    }
    
    //! Image data
    unsigned char* mData;
    //! Width
    int mWidth;
    //! Height
    int mHeight;
    //! Block size in bytes
    unsigned mBlockSize;
    //! Total data size in bytes
    unsigned mDataSize;
    //! Row size in bytes
    unsigned mRowSize;
    //! Number of rows
    unsigned mRows;
};

//! An image resource
class Image : public Resource
{
    DEFINE_TYPE(Image);
    
public:
    //! Construct with name
    Image(const std::string& name = std::string());
    //! Construct with initial size and name
    Image(int width, int height, unsigned components, const std::string& name = std::string());
    //! Construct with initial size, pixel data and name
    Image(int width, int height, unsigned components, unsigned char* pixelData, const std::string& name = std::string());
    //! Destruct
    virtual ~Image();
    
    //! Load resource. Throw exception on error
    virtual void load(Deserializer& source, ResourceCache* cache = 0);
    
    //! Set size and number of color components
    void setSize(unsigned width, unsigned height, unsigned components);
    //! Set data
    void setData(const unsigned char* pixelData);
    //! Save in BMP format
    void saveBMP(const std::string& fileName);
    //! Save in TGA format
    void saveTGA(const std::string& fileName);
    
    //! Return width
    int getWidth() const { return mWidth; }
    //! Return height
    int getHeight() const { return mHeight; }
    //! Return number of color components
    unsigned getComponents() const { return mComponents; }
    //! Return pixel data
    unsigned char* getData() const { return mData; }
    //! Return whether is compressed
    bool isCompressed() const { return mCompressedFormat != CF_NONE; }
    //! Return compressed format
    CompressedFormat getCompressedFormat() const { return mCompressedFormat; }
    //! Return number of compressed mipmap levels
    unsigned getNumCompressedLevels() const { return mCompressedLevels; }
    //! Return next mipmap level by bilinear filtering
    SharedPtr<Image> getNextLevel() const;
    //! Return a compressed mipmap level
    CompressedLevel getCompressedLevel(unsigned index) const;
    
private:
    //! Load an image file
    static unsigned char* loadImageFile(Deserializer& source, int& width, int& height, unsigned& components);
    //! Free an image file's pixel data
    static void freeImageFile(unsigned char* pixelData);
    
    //! Width
    int mWidth;
    //! Height
    int mHeight;
    //! Number of color components
    unsigned mComponents;
    //! Number of compressed mipmap levels
    unsigned mCompressedLevels;
    //! Compressed format
    CompressedFormat mCompressedFormat;
    //! Pixel data
    SharedArrayPtr<unsigned char> mData;
};

#endif // RESOURCE_IMAGE_H
