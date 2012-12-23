//
// Urho3D Engine
// Copyright (c) 2008-2012 Lasse Oorni
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
#include "Decompress.h"
#include "File.h"
#include "FileSystem.h"
#include "Log.h"

#include <cstring>
#include <stb_image.h>
#include <stb_image_write.h>
#include <jo_jpeg.h>

#include "DebugNew.h"

#ifndef MAKEFOURCC
#define MAKEFOURCC(ch0, ch1, ch2, ch3) ((unsigned)(ch0) | ((unsigned)(ch1) << 8) | ((unsigned)(ch2) << 16) | ((unsigned)(ch3) << 24))
#endif

#define FOURCC_DXT1 (MAKEFOURCC('D','X','T','1'))
#define FOURCC_DXT2 (MAKEFOURCC('D','X','T','2'))
#define FOURCC_DXT3 (MAKEFOURCC('D','X','T','3'))
#define FOURCC_DXT4 (MAKEFOURCC('D','X','T','4'))
#define FOURCC_DXT5 (MAKEFOURCC('D','X','T','5'))

namespace Urho3D
{

struct DDColorKey
{
    unsigned dwColorSpaceLowValue_;
    unsigned dwColorSpaceHighValue_;
};

struct DDPixelFormat
{
    unsigned dwSize_;
    unsigned dwFlags_;
    unsigned dwFourCC_;
    union
    {
        unsigned dwRGBBitCount_;
        unsigned dwYUVBitCount_;
        unsigned dwZBufferBitDepth_;
        unsigned dwAlphaBitDepth_;
        unsigned dwLuminanceBitCount_;
        unsigned dwBumpBitCount_;
        unsigned dwPrivateFormatBitCount_;
    };
    union
    {
        unsigned dwRBitMask_;
        unsigned dwYBitMask_;
        unsigned dwStencilBitDepth_;
        unsigned dwLuminanceBitMask_;
        unsigned dwBumpDuBitMask_;
        unsigned dwOperations_;
    };
    union
    {
        unsigned dwGBitMask_;
        unsigned dwUBitMask_;
        unsigned dwZBitMask_;
        unsigned dwBumpDvBitMask_;
        struct
        {
            unsigned short wFlipMSTypes_;
            unsigned short wBltMSTypes_;
        } multiSampleCaps_;
    };
    union
    {
        unsigned dwBBitMask_;
        unsigned dwVBitMask_;
        unsigned dwStencilBitMask_;
        unsigned dwBumpLuminanceBitMask_;
    };
    union
    {
        unsigned dwRGBAlphaBitMask_;
        unsigned dwYUVAlphaBitMask_;
        unsigned dwLuminanceAlphaBitMask_;
        unsigned dwRGBZBitMask_;
        unsigned dwYUVZBitMask_;
    };
};

struct DDSCaps2
{
    unsigned dwCaps_;
    unsigned dwCaps2_;
    unsigned dwCaps3_;
    union
    {
        unsigned dwCaps4_;
        unsigned dwVolumeDepth_;
    };
};

struct DDSurfaceDesc2
{
    unsigned dwSize_;
    unsigned dwFlags_;
    unsigned dwHeight_;
    unsigned dwWidth_;
    union
    {
        long lPitch_;
        unsigned dwLinearSize_;
    };
    union
    {
        unsigned dwBackBufferCount_;
        unsigned dwDepth_;
    };
    union
    {
        unsigned dwMipMapCount_;
        unsigned dwRefreshRate_;
        unsigned dwSrcVBHandle_;
    };
    unsigned dwAlphaBitDepth_;
    unsigned dwReserved_;
    void* lpSurface_;
    union
    {
        DDColorKey ddckCKDestOverlay_;
        unsigned dwEmptyFaceColor_;
    };
    DDColorKey ddckCKDestBlt_;
    DDColorKey ddckCKSrcOverlay_;
    DDColorKey ddckCKSrcBlt_;
    union
    {
        DDPixelFormat ddpfPixelFormat_;
        unsigned dwFVF_;
    };
    DDSCaps2 ddsCaps_;
    unsigned dwTextureStage_;
};

bool CompressedLevel::Decompress(unsigned char* dest)
{
    if (!data_)
        return false;
    
    switch (format_)
    {
    case CF_DXT1:
    case CF_DXT3:
    case CF_DXT5:
        DecompressImageDXT(dest, data_, width_, height_, format_);
        return true;
        
    case CF_ETC1:
        DecompressImageETC(dest, data_, width_, height_);
        return true;
        
    case CF_PVRTC_RGB_2BPP:
    case CF_PVRTC_RGBA_2BPP:
    case CF_PVRTC_RGB_4BPP:
    case CF_PVRTC_RGBA_4BPP:
        DecompressImagePVRTC(dest, data_, width_, height_, format_);
        return true;
    }
    
    // Unknown format
    return false;
}

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
    // Check for DDS, KTX or PVR compressed format
    String fileID = source.ReadFileID();
    
    if (fileID == "DDS ")
    {
        // DDS compressed format
        DDSurfaceDesc2 ddsd;
        source.Read(&ddsd, sizeof(ddsd));
        
        switch (ddsd.ddpfPixelFormat_.dwFourCC_)
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
        width_ = ddsd.dwWidth_;
        height_ = ddsd.dwHeight_;
        numCompressedLevels_ = ddsd.dwMipMapCount_;
        if (!numCompressedLevels_)
            numCompressedLevels_ = 1;
        SetMemoryUse(dataSize);
        source.Read(data_.Get(), dataSize);
    }
    else if (fileID == "\253KTX")
    {
        source.Seek(12);
        
        unsigned endianness = source.ReadUInt();
        unsigned type = source.ReadUInt();
        unsigned typeSize = source.ReadUInt();
        unsigned format = source.ReadUInt();
        unsigned internalFormat = source.ReadUInt();
        unsigned baseInternalFormat = source.ReadUInt();
        unsigned width = source.ReadUInt();
        unsigned height = source.ReadUInt();
        unsigned depth = source.ReadUInt();
        unsigned arrayElements = source.ReadUInt();
        unsigned faces = source.ReadUInt();
        unsigned mipmaps = source.ReadUInt();
        unsigned keyValueBytes = source.ReadUInt();
        
        if (endianness != 0x04030201)
        {
            LOGERROR("Big-endian KTX files not supported");
            return false;
        }
        
        if (type != 0 || format != 0)
        {
            LOGERROR("Uncompressed KTX files not supported");
            return false;
        }
        
        if (faces > 1 || depth > 1)
        {
            LOGERROR("3D or cube KTX files not supported");
            return false;
        }
        
        if (mipmaps == 0)
        {
            LOGERROR("KTX files without explicitly specified mipmap count not supported");
            return false;
        }
        
        compressedFormat_ = CF_NONE;
        switch (internalFormat)
        {
        case 0x83f1:
            compressedFormat_ = CF_DXT1;
            components_ = 4;
            break;
            
        case 0x83f2:
            compressedFormat_ = CF_DXT3;
            components_ = 4;
            break;
            
        case 0x83f3:
            compressedFormat_ = CF_DXT5;
            components_ = 4;
            break;
            
        case 0x8d64:
            compressedFormat_ = CF_ETC1;
            components_ = 3;
            break;
            
        case 0x8c00:
            compressedFormat_ = CF_PVRTC_RGB_4BPP;
            components_ = 3;
            break;
            
        case 0x8c01:
            compressedFormat_ = CF_PVRTC_RGB_2BPP;
            components_ = 3;
            break;
            
        case 0x8c02:
            compressedFormat_ = CF_PVRTC_RGBA_4BPP;
            components_ = 4;
            break;
            
        case 0x8c03:
            compressedFormat_ = CF_PVRTC_RGBA_2BPP;
            components_ = 4;
            break;
        }
        
        if (compressedFormat_ == CF_NONE)
        {
            LOGERROR("Unsupported texture format in KTX file");
            return false;
        }
        
        source.Seek(source.GetPosition() + keyValueBytes);
        unsigned dataSize = source.GetSize() - source.GetPosition() - mipmaps * sizeof(unsigned);
        
        data_ = new unsigned char[dataSize];
        width_ = width;
        height_ = height;
        numCompressedLevels_ = mipmaps;
        
        unsigned dataOffset = 0;
        for (unsigned i = 0; i < mipmaps; ++i)
        {
            unsigned levelSize = source.ReadUInt();
            if (levelSize + dataOffset > dataSize)
            {
                LOGERROR("KTX mipmap level data size exceeds file size");
                return false;
            }
            
            source.Read(&data_[dataOffset], levelSize);
            dataOffset += levelSize;
            if (source.GetPosition() & 3)
                source.Seek((source.GetPosition() + 3) & 0xfffffffc);
        }
        
        SetMemoryUse(dataSize);
    }
    else if (fileID == "PVR\3")
    {
        unsigned flags = source.ReadUInt();
        unsigned pixelFormatLo = source.ReadUInt();
        unsigned pixelFormatHi = source.ReadUInt();
        unsigned colourSpace = source.ReadUInt();
        unsigned channelType = source.ReadUInt();
        unsigned height = source.ReadUInt();
        unsigned width = source.ReadUInt();
        unsigned depth = source.ReadUInt();
        unsigned numSurfaces = source.ReadUInt();
        unsigned numFaces = source.ReadUInt();
        unsigned mipmapCount = source.ReadUInt();
        unsigned metaDataSize = source.ReadUInt();
        
        if (depth > 1 || numFaces > 1)
        {
            LOGERROR("3D or cube PVR files not supported");
            return false;
        }
        
        if (mipmapCount == 0)
        {
            LOGERROR("PVR files without explicitly specified mipmap count not supported");
            return false;
        }
        
        compressedFormat_ = CF_NONE;
        switch (pixelFormatLo)
        {
        case 0:
            compressedFormat_ = CF_PVRTC_RGB_2BPP;
            components_ = 3;
            break;
            
        case 1:
            compressedFormat_ = CF_PVRTC_RGBA_2BPP;
            components_ = 4;
            break;
            
        case 2:
            compressedFormat_ = CF_PVRTC_RGB_4BPP;
            components_ = 3;
            break;
            
        case 3:
            compressedFormat_ = CF_PVRTC_RGBA_4BPP;
            components_ = 4;
            break;
            
        case 6:
            compressedFormat_ = CF_ETC1;
            components_ = 3;
            break;
            
        case 7:
            compressedFormat_ = CF_DXT1;
            components_ = 4;
            break;
            
        case 9:
            compressedFormat_ = CF_DXT3;
            components_ = 4;
            break;
            
        case 11:
            compressedFormat_ = CF_DXT5;
            components_ = 4;
            break;
        }
        
        if (compressedFormat_ == CF_NONE)
        {
            LOGERROR("Unsupported texture format in PVR file");
            return false;
        }
        
        source.Seek(source.GetPosition() + metaDataSize);
        unsigned dataSize = source.GetSize() - source.GetPosition();
        
        data_ = new unsigned char[dataSize];
        width_ = width;
        height_ = height;
        numCompressedLevels_ = mipmapCount;
        
        source.Read(data_.Get(), dataSize);
        SetMemoryUse(dataSize);
    }
    else
    {
        // Not DDS, KTX or PVR, use STBImage to load other image formats as uncompressed
        source.Seek(0);
        int width, height;
        unsigned components;
        unsigned char* pixelData = GetImageData(source, width, height, components);
        if (!pixelData)
        {
            LOGERROR("Could not load image " + source.GetName() + ": " + String(stbi_failure_reason()));
            return false;
        }
        SetSize(width, height, components);
        SetData(pixelData);
        FreeImageData(pixelData);
    }
    
    return true;
}

void Image::SetSize(int width, int height, unsigned components)
{
    if (width == width_ && height == height_ && components == components_)
        return;
    
    if (width <= 0 || height <= 0)
        return;
    
    data_ = new unsigned char[width * height * components];
    width_ = width;
    height_ = height;
    components_ = components;
    compressedFormat_ = CF_NONE;
    numCompressedLevels_ = 0;
    
    SetMemoryUse(width * height * components);
}

void Image::FlipVertical()
{
    if (!data_)
        return;
    
    if (IsCompressed())
    {
        LOGERROR("Can not flip a compressed image");
        return;
    }
    
    SharedArrayPtr<unsigned char> newData(new unsigned char[width_ * height_ * components_]);
    unsigned rowSize = width_ * components_;
    
    for (int y = 0; y < height_; ++y)
        memcpy(&newData[(height_ - y - 1) * rowSize], &data_[y * rowSize], rowSize);
    
    data_ = newData;
}

void Image::SetData(const unsigned char* pixelData)
{
    memcpy(data_.Get(), pixelData, width_ * height_ * components_);
}

bool Image::SaveBMP(const String& fileName)
{
    FileSystem* fileSystem = GetSubsystem<FileSystem>();
    if (fileSystem && !fileSystem->CheckAccess(GetPath(fileName)))
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
        return stbi_write_bmp(fileName.CString(), width_, height_, components_, data_.Get()) != 0;
    else
        return false;
}

bool Image::SaveTGA(const String& fileName)
{
    FileSystem* fileSystem = GetSubsystem<FileSystem>();
    if (fileSystem && !fileSystem->CheckAccess(GetPath(fileName)))
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
        return stbi_write_tga(fileName.CString(), width_, height_, components_, data_.Get()) != 0;
    else
        return false;
}

bool Image::SaveJPG(const String & fileName, int quality)
{
    FileSystem* fileSystem = GetSubsystem<FileSystem>();
    if (fileSystem && !fileSystem->CheckAccess(GetPath(fileName)))
    {
        LOGERROR("Access denied to " + fileName);
        return false;
    }
    
    if (IsCompressed())
    {
        LOGERROR("Can not save compressed image to JPG");
        return false;
    }
    
    if (data_)
        return jo_write_jpg(fileName.CString(), data_.Get(), width_, height_, components_, quality) != 0;
    else
        return false;
}

unsigned char* Image::GetImageData(Deserializer& source, int& width, int& height, unsigned& components)
{
    unsigned dataSize = source.GetSize();
    
    SharedArrayPtr<unsigned char> buffer(new unsigned char[dataSize]);
    source.Read(buffer.Get(), dataSize);
    return stbi_load_from_memory(buffer.Get(), dataSize, &width, &height, (int *)&components, 0);
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
    if (components_ < 1 || components_ > 4)
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
    
    const unsigned char* pixelDataIn = data_.Get();
    unsigned char* pixelDataOut = mipImage->data_.Get();
    
    // 1D case
    if (height_ == 1 || width_ == 1)
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
    
    level.format_ = compressedFormat_;
    level.width_ = width_;
    level.height_ = height_;
    
    if (compressedFormat_ < CF_PVRTC_RGB_2BPP)
    {
        level.blockSize_ = (compressedFormat_ == CF_DXT1 || compressedFormat_ == CF_ETC1) ? 8 : 16;
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
            level.data_ = data_.Get() + offset;
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
    else
    {
        level.blockSize_ = compressedFormat_ < CF_PVRTC_RGB_4BPP ? 2 : 4;
        unsigned i = 0;
        unsigned offset = 0;
        
        for (;;)
        {
            if (!level.width_)
                level.width_ = 1;
            if (!level.height_)
                level.height_ = 1;
            
            int dataWidth = Max(level.width_, level.blockSize_ == 2 ? 16 : 8);
            int dataHeight = Max(level.height_, 8);
            level.data_ = data_.Get() + offset;
            level.dataSize_ = (dataWidth * dataHeight * level.blockSize_ + 7) >> 3;
            level.rows_ = dataHeight;
            level.rowSize_ = level.dataSize_ / level.rows_;
            
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
}

}
