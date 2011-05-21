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
#include "Context.h"
#include "File.h"
#include "FileSystem.h"
#include "Image.h"
#include "Log.h"

#include <cstring>
#include <ddraw.h>
#include <stb_image.h>
#include <stb_image_write.h>

#include "DebugNew.h"

OBJECTTYPESTATIC(Image);

Image::Image(Context* context) :
    Resource(context),
    width_(0),
    height_(0),
    components_(0)
{
}

Image::~Image()
{
}

void Image::RegisterObject(Context* context)
{
    context->RegisterFactory<Image>();
}

bool Image::Load(Deserializer& source)
{
    // Check for DDS compressed format
    if (source.ReadID() != "DDS ")
    {
        // Not DDS, use STBImage to load other image formats as uncompressed
        source.Seek(0);
        int width, height;
        unsigned components;
        unsigned char* pixelData = GetImageData(source, width, height, components);
        if (!pixelData)
        {
            LOGERROR("Could not load image: " + String(stbi_failure_reason()));
            return false;
        }
        SetSize(width, height, components);
        SetData(pixelData);
        FreeImageData(pixelData);
    }
    else
    {
        // DDS compressed format
        DDSURFACEDESC2 ddsd;
        source.Read(&ddsd, sizeof(ddsd));
        
        switch (ddsd.ddpfPixelFormat.dwFourCC)
        {
        case FOURCC_DXT1:
            compressedFormat_ = CF_DXT1;
            components_ = 3;
            break;
            
        case FOURCC_DXT3:
            compressedFormat_ = CF_DXT3;
            components_ = 4;
            break;
            
        case FOURCC_DXT5:
            compressedFormat_ = CF_DXT5;
            components_ = 4;
            break;
            
        default:
            LOGERROR("Unsupported DDS format");
            return false;
        }

        unsigned dataSize = source.GetSize() - source.GetPosition();
        data_ = new unsigned char[dataSize];
        width_ = ddsd.dwWidth;
        height_ = ddsd.dwHeight;
        numCompressedLevels_ = ddsd.dwMipMapCount;
        if (!numCompressedLevels_)
            numCompressedLevels_ = 1;
        SetMemoryUse(dataSize);
        source.Read(data_.GetPtr(), dataSize);
    }
    
    return true;
}

void Image::SetSize(unsigned width, unsigned height, unsigned components)
{
    if ((width == width_) && (height == height_) && (components == components_))
        return;
    
    if ((width <= 0) || (height <= 0))
        return;
    
    data_ = new unsigned char[width * height * components];
    width_ = width;
    height_ = height;
    components_ = components;
    compressedFormat_ = CF_NONE;
    numCompressedLevels_ = 0;
    
    SetMemoryUse(width * height * components);
}

void Image::SetData(const unsigned char* pixelData)
{
    memcpy(data_.GetPtr(), pixelData, width_ * height_ * components_);
}

bool Image::SaveBMP(const String& fileName)
{
    FileSystem* fileSystem = GetSubsystem<FileSystem>();
    if ((fileSystem) && (!fileSystem->CheckAccess(GetPath(fileName))))
    {
        LOGERROR("Access denied to " + fileName);
        return false;
    }
    
    if (IsCompressed())
    {
        LOGERROR("Can not save compressed image to BMP");
        return false;
    }
    
    if (data_)
        return stbi_write_bmp(fileName.CString(), width_, height_, components_, data_.GetPtr()) != 0;
    else
        return false;
}

bool Image::SaveTGA(const String& fileName)
{
    FileSystem* fileSystem = GetSubsystem<FileSystem>();
    if ((fileSystem) && (!fileSystem->CheckAccess(GetPath(fileName))))
    {
        LOGERROR("Access denied to " + fileName);
        return false;
    }
    
    if (IsCompressed())
    {
        LOGERROR("Can not save compressed image to TGA");
        return false;
    }
    
    if (data_)
        return stbi_write_tga(fileName.CString(), width_, height_, components_, data_.GetPtr()) != 0;
    else
        return false;
}

unsigned char* Image::GetImageData(Deserializer& source, int& width, int& height, unsigned& components)
{
    unsigned dataSize = source.GetSize();
    
    SharedArrayPtr<unsigned char> buffer(new unsigned char[dataSize]);
    source.Read(buffer.GetPtr(), dataSize);
    return stbi_load_from_memory(buffer.GetPtr(), dataSize, &width, &height, (int *)&components, 0);
}

void Image::FreeImageData(unsigned char* pixelData)
{
    if (!pixelData)
        return;
    
    stbi_image_free(pixelData);
}

SharedPtr<Image> Image::GetNextLevel() const
{
    if (IsCompressed())
    {
        LOGERROR("Can not generate mip level from compressed data");
        return SharedPtr<Image>();
    }
    if ((components_ < 1) || (components_ > 4))
    {
        LOGERROR("Illegal number of image components for mip level generation");
        return SharedPtr<Image>();
    }
    
    int widthOut = width_ / 2;
    int heightOut = height_ / 2;
    
    if (widthOut < 1)
        widthOut = 1;
    if (heightOut < 1)
        heightOut = 1;
    
    SharedPtr<Image> mipImage(new Image(context_));
    mipImage->SetSize(widthOut, heightOut, components_);
    
    const unsigned char* pixelDataIn = data_.GetPtr();
    unsigned char* pixelDataOut = mipImage->data_.GetPtr();
    
    // 1D case
    if ((height_ == 1) || (width_ == 1))
    {
        // Loop using the larger dimension
        if (widthOut < heightOut) 
            widthOut = heightOut;
        
        switch (components_)
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
        switch (components_)
        {
        case 1:
            for (int y = 0; y < heightOut; ++y)
            {
                const unsigned char* inUpper = &pixelDataIn[(y*2)*width_];
                const unsigned char* inLower = &pixelDataIn[(y*2+1)*width_];
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
                const unsigned char* inUpper = &pixelDataIn[(y*2)*width_*2];
                const unsigned char* inLower = &pixelDataIn[(y*2+1)*width_*2];
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
                const unsigned char* inUpper = &pixelDataIn[(y*2)*width_*3];
                const unsigned char* inLower = &pixelDataIn[(y*2+1)*width_*3];
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
                const unsigned char* inUpper = &pixelDataIn[(y*2)*width_*4];
                const unsigned char* inLower = &pixelDataIn[(y*2+1)*width_*4];
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

CompressedLevel Image::GetCompressedLevel(unsigned index) const
{
    CompressedLevel level;
    
    if (compressedFormat_ == CF_NONE)
    {
        LOGERROR("Image is not compressed");
        return level;
    }
    if (index >= numCompressedLevels_)
    {
        LOGERROR("Compressed image mip level out of bounds");
        return level;
    }
    
    level.width_ = width_;
    level.height_ = height_;
    level.blockSize_ = (compressedFormat_ == CF_DXT1) ? 8 : 16;
    unsigned i = 0;
    unsigned offset = 0;
    
    for (;;)
    {
        if (!level.width_)
            level.width_ = 1;
        if (!level.height_)
            level.height_ = 1;
        
        level.rowSize_ = ((level.width_ + 3) / 4) * level.blockSize_;
        level.rows_ = ((level.height_ + 3) / 4);
        level.data_ = data_.GetPtr() + offset;
        level.dataSize_ = level.rows_ * level.rowSize_;
        
        if (offset + level.dataSize_ > GetMemoryUse())
        {
            LOGERROR("Compressed level is outside image data. Offset: " + String(offset) + " Size: " + String(level.dataSize_) +
                " Datasize: " + String(GetMemoryUse()));
            level.data_ = 0;
            return level;
        }
        
        if (i == index)
            return level;
        
        offset += level.dataSize_;
        level.width_ /= 2;
        level.height_ /= 2;
        ++i;
    }
}
