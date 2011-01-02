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

#include "Precompiled.h"
#include "File.h"
#include "Image.h"
#include "Log.h"
#include "StringUtils.h"

#include <cstring>
#include <ddraw.h>
#include <stb_image.h>
#include <stb_image_write.h>

#include "DebugNew.h"

Image::Image(const std::string& name) :
    Resource(name),
    mWidth(0),
    mHeight(0),
    mComponents(0)
{
}

Image::Image(int width, int height, unsigned components, const std::string& name) :
    Resource(name),
    mWidth(0),
    mHeight(0),
    mComponents(0)
{
    setSize(width, height, components);
}

Image::Image(int width, int height, unsigned components, unsigned char* pixelData, const std::string& name) :
    Resource(name),
    mWidth(0),
    mHeight(0),
    mComponents(0)
{
    setSize(width, height, components);
    setData(pixelData);
}

Image::~Image()
{
}

void Image::load(Deserializer& source, ResourceCache* cache)
{
    char header[4];

    // Read first 4 bytes
    source.read(header, 4);

    // First 4 bytes identify DDS compressed format
    if (strncmp(header, "DDS ", 4))
    {
        // Not DDS, use STBImage to load other image formats as uncompressed
        source.seek(0);
        int width, height;
        unsigned components;
        unsigned char* pixelData = loadImageFile(source, width, height, components);
        setSize(width, height, components);
        setData(pixelData);
        freeImageFile(pixelData);
    }
    else
    {
        // DDS compressed format
        DDSURFACEDESC2 ddsd;
        source.read(&ddsd, sizeof(ddsd));
        
        switch (ddsd.ddpfPixelFormat.dwFourCC)
        {
        case FOURCC_DXT1:
            mCompressedFormat = CF_DXT1;
            mComponents = 3;
            break;
            
        case FOURCC_DXT3:
            mCompressedFormat = CF_DXT3;
            mComponents = 4;
            break;
            
        case FOURCC_DXT5:
            mCompressedFormat = CF_DXT5;
            mComponents = 4;
            break;
            
        default:
            EXCEPTION("Unsupported DDS format");
        }

        unsigned dataSize = source.getSize() - source.getPosition();
        mData = new unsigned char[dataSize];
        mWidth = ddsd.dwWidth;
        mHeight = ddsd.dwHeight;
        mCompressedLevels = ddsd.dwMipMapCount;
        if (!mCompressedLevels)
            mCompressedLevels = 1;
        
        setMemoryUse(dataSize);
        source.read(mData.getPtr(), dataSize);
    }
}

void Image::setSize(unsigned width, unsigned height, unsigned components)
{
    if ((width == mWidth) && (height == mHeight) && (components == mComponents))
        return;
    
    if ((width <= 0) || (height <= 0))
        return;
    
    mData = new unsigned char[width * height * components];
    mWidth = width;
    mHeight = height;
    mComponents = components;
    mCompressedFormat = CF_NONE;
    mCompressedLevels = 0;
    
    setMemoryUse(width * height * components);
}

void Image::setData(const unsigned char* pixelData)
{
    memcpy(mData.getPtr(), pixelData, mWidth * mHeight * mComponents);
}

void Image::saveBMP(const std::string& fileName)
{
    if (!checkDirectoryAccess(getPath(fileName)))
        SAFE_EXCEPTION("Access denied to " + fileName);
    
    if (isCompressed())
        SAFE_EXCEPTION("Can not save compressed image to BMP");
    
    if (mData)
        stbi_write_bmp(fileName.c_str(), mWidth, mHeight, mComponents, mData.getPtr());
}

void Image::saveTGA(const std::string& fileName)
{
    if (!checkDirectoryAccess(getPath(fileName)))
        SAFE_EXCEPTION("Access denied to " + fileName);
    
    if (isCompressed())
        SAFE_EXCEPTION("Can not save compressed image to TGA");
    
    if (mData)
        stbi_write_tga(fileName.c_str(), mWidth, mHeight, mComponents, mData.getPtr());
}

unsigned char* Image::loadImageFile(Deserializer& source, int& width, int& height, unsigned& components)
{
    unsigned dataSize = source.getSize();
    
    SharedArrayPtr<unsigned char> buffer(new unsigned char[dataSize]);
    source.read(buffer.getPtr(), dataSize);
    
    unsigned char* pixelData = stbi_load_from_memory(buffer.getPtr(), dataSize, &width, &height, (int *)&components, 0);
    if (!pixelData)
        EXCEPTION("Could not load image: " + std::string(stbi_failure_reason()));
    
    return pixelData;
}

void Image::freeImageFile(unsigned char* pixelData)
{
    if (!pixelData)
        return;

    stbi_image_free(pixelData);
}

SharedPtr<Image> Image::getNextLevel() const
{
    if (isCompressed())
        EXCEPTION("Can not generate mip level from compressed data");
    if ((mComponents < 1) || (mComponents > 4))
        EXCEPTION("Illegal number of image components for mip level generation");
    
    int widthOut = mWidth / 2;
    int heightOut = mHeight / 2;
    
    if (widthOut < 1)
        widthOut = 1;
    if (heightOut < 1)
        heightOut = 1;
    
    SharedPtr<Image> mipImage(new Image(widthOut, heightOut, mComponents));
    
    const unsigned char* pixelDataIn = mData.getPtr();
    unsigned char* pixelDataOut = mipImage->mData.getPtr();
    
    // 1D case
    if ((mHeight == 1) || (mWidth == 1))
    {
        // Loop using the larger dimension
        if (widthOut < heightOut) 
            widthOut = heightOut;
        
        switch (mComponents)
        {
        case 1:
            for (int x = 0; x < widthOut; ++x)
                pixelDataOut[x] = ((unsigned)pixelDataIn[x*2] + pixelDataIn[x*2+1]) >> 1;
            break;
            
        case 2:
            for (int x = 0; x < widthOut*2; x += 2)
            {
                pixelDataOut[x] = ((unsigned)pixelDataIn[x*2] + pixelDataIn[x*2+2]) >> 1;
                pixelDataOut[x+1] = ((unsigned)pixelDataIn[x*2+1] + pixelDataIn[x*2+3]) >> 1;
            }
            break;
            
        case 3:
            for (int x = 0; x < widthOut*3; x += 3)
            {
                pixelDataOut[x] = ((unsigned)pixelDataIn[x*2] + pixelDataIn[x*2+3]) >> 1;
                pixelDataOut[x+1] = ((unsigned)pixelDataIn[x*2+1] + pixelDataIn[x*2+4]) >> 1;
                pixelDataOut[x+2] = ((unsigned)pixelDataIn[x*2+2] + pixelDataIn[x*2+5]) >> 1;
            }
            break;
            
        case 4:
            for (int x = 0; x < widthOut*4; x += 4)
            {
                pixelDataOut[x] = ((unsigned)pixelDataIn[x*2] + pixelDataIn[x*2+4]) >> 1;
                pixelDataOut[x+1] = ((unsigned)pixelDataIn[x*2+1] + pixelDataIn[x*2+5]) >> 1;
                pixelDataOut[x+2] = ((unsigned)pixelDataIn[x*2+2] + pixelDataIn[x*2+6]) >> 1;
                pixelDataOut[x+3] = ((unsigned)pixelDataIn[x*2+3] + pixelDataIn[x*2+7]) >> 1;
            }
            break;
        }
    }
    // 2D case
    else
    {
        switch (mComponents)
        {
        case 1:
            for (int y = 0; y < heightOut; ++y)
            {
                const unsigned char* inUpper = &pixelDataIn[(y*2)*mWidth];
                const unsigned char* inLower = &pixelDataIn[(y*2+1)*mWidth];
                unsigned char* out = &pixelDataOut[y*widthOut];
                
                for (int x = 0; x < widthOut; ++x)
                {
                    out[x] = ((unsigned)inUpper[x*2] + inUpper[x*2+1] + inLower[x*2] + inLower[x*2+1]) >> 2;
                }
            }
            break;
            
        case 2:
            for (int y = 0; y < heightOut; ++y)
            {
                const unsigned char* inUpper = &pixelDataIn[(y*2)*mWidth*2];
                const unsigned char* inLower = &pixelDataIn[(y*2+1)*mWidth*2];
                unsigned char* out = &pixelDataOut[y*widthOut*2];
                
                for (int x = 0; x < widthOut*2; x += 2)
                {
                    out[x] = ((unsigned)inUpper[x*2] + inUpper[x*2+2] + inLower[x*2] + inLower[x*2+2]) >> 2;
                    out[x+1] = ((unsigned)inUpper[x*2+1] + inUpper[x*2+3] + inLower[x*2+1] + inLower[x*2+3]) >> 2;
                }
            }
            break;
            
        case 3:
            for (int y = 0; y < heightOut; ++y)
            {
                const unsigned char* inUpper = &pixelDataIn[(y*2)*mWidth*3];
                const unsigned char* inLower = &pixelDataIn[(y*2+1)*mWidth*3];
                unsigned char* out = &pixelDataOut[y*widthOut*3];
                
                for (int x = 0; x < widthOut*3; x += 3)
                {
                    out[x] = ((unsigned)inUpper[x*2] + inUpper[x*2+3] + inLower[x*2] + inLower[x*2+3]) >> 2;
                    out[x+1] = ((unsigned)inUpper[x*2+1] + inUpper[x*2+4] + inLower[x*2+1] + inLower[x*2+4]) >> 2;
                    out[x+2] = ((unsigned)inUpper[x*2+2] + inUpper[x*2+5] + inLower[x*2+2] + inLower[x*2+5]) >> 2;
                }
            }
            break;
            
        case 4:
            for (int y = 0; y < heightOut; ++y)
            {
                const unsigned char* inUpper = &pixelDataIn[(y*2)*mWidth*4];
                const unsigned char* inLower = &pixelDataIn[(y*2+1)*mWidth*4];
                unsigned char* out = &pixelDataOut[y*widthOut*4];
                
                for (int x = 0; x < widthOut*4; x += 4)
                {
                    out[x] = ((unsigned)inUpper[x*2] + inUpper[x*2+4] + inLower[x*2] + inLower[x*2+4]) >> 2;
                    out[x+1] = ((unsigned)inUpper[x*2+1] + inUpper[x*2+5] + inLower[x*2+1] + inLower[x*2+5]) >> 2;
                    out[x+2] = ((unsigned)inUpper[x*2+2] + inUpper[x*2+6] + inLower[x*2+2] + inLower[x*2+6]) >> 2;
                    out[x+3] = ((unsigned)inUpper[x*2+3] + inUpper[x*2+7] + inLower[x*2+3] + inLower[x*2+7]) >> 2;
                }
            }
            break;
        }
    }
    
    return mipImage;
}

CompressedLevel Image::getCompressedLevel(unsigned index) const
{
    CompressedLevel level;
    
    if (mCompressedFormat == CF_NONE)
        SAFE_EXCEPTION_RET("Image is not compressed", level);
    if (index >= mCompressedLevels)
        SAFE_EXCEPTION_RET("Illegal compressed image mip level", level);
    
    level.mWidth = mWidth;
    level.mHeight = mHeight;
    level.mBlockSize = (mCompressedFormat == CF_DXT1) ? 8 : 16;
    unsigned i = 0;
    unsigned offset = 0;
    
    for (;;)
    {
        if (!level.mWidth)
            level.mWidth = 1;
        if (!level.mHeight)
            level.mHeight = 1;
        
        level.mRowSize = ((level.mWidth + 3) / 4) * level.mBlockSize;
        level.mRows = ((level.mHeight + 3) / 4);
        level.mData = mData.getPtr() + offset;
        level.mDataSize = level.mRows * level.mRowSize;
        
        if (offset + level.mDataSize > getMemoryUse())
            SAFE_EXCEPTION_RET("Compressed level is outside image data. Offset: " + toString(offset) + " Size: " + toString(level.mDataSize) + " Datasize: " + toString(getMemoryUse()), level);
        
        if (i == index)
            return level;
        
        offset += level.mDataSize;
        level.mWidth /= 2;
        level.mHeight /= 2;
        ++i;
    }
}
