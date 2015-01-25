//
// Copyright (c) 2008-2014 the Urho3D project.
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

#include "../Core/Context.h"
#include "../Resource/Decompress.h"
#include "../IO/File.h"
#include "../IO/FileSystem.h"
#include "../IO/Log.h"
#include "../Core/Profiler.h"

#include <cstdlib>
#include <cstring>
#include <STB/stb_image.h>
#include <STB/stb_image_write.h>
#include <JO/jo_jpeg.h>
#include <SDL/SDL_surface.h>

#include "../DebugNew.h"

extern "C" unsigned char *stbi_write_png_to_mem(unsigned char *pixels, int stride_bytes, int x, int y, int n, int *out_len);

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

/// DirectDraw color key definition.
struct DDColorKey
{
    unsigned dwColorSpaceLowValue_;
    unsigned dwColorSpaceHighValue_;
};

/// DirectDraw pixel format definition.
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

/// DirectDraw surface capabilities.
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

/// DirectDraw surface description.
struct DDSurfaceDesc2
{
    unsigned dwSize_;
    unsigned dwFlags_;
    unsigned dwHeight_;
    unsigned dwWidth_;
    union
    {
        unsigned lPitch_;
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
    unsigned lpSurface_; // Do not define as a void pointer, as it is 8 bytes in a 64bit build
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
        DecompressImageDXT(dest, data_, width_, height_, depth_, format_);
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

    default:
         // Unknown format
         return false;
    }
}

Image::Image(Context* context) :
    Resource(context),
    width_(0),
    height_(0),
    depth_(0),
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

bool Image::BeginLoad(Deserializer& source)
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

        case 0:
            if (ddsd.ddpfPixelFormat_.dwRGBBitCount_ != 32 && ddsd.ddpfPixelFormat_.dwRGBBitCount_ != 24 &&
                ddsd.ddpfPixelFormat_.dwRGBBitCount_ != 16)
            {
                LOGERROR("Unsupported DDS pixel byte size");
                return false;
            }
            compressedFormat_ = CF_RGBA;
            components_ = 4;
            break;
            
        default:
            LOGERROR("Unrecognized DDS image format");
            return false;
        }

        unsigned dataSize = source.GetSize() - source.GetPosition();
        data_ = new unsigned char[dataSize];
        width_ = ddsd.dwWidth_;
        height_ = ddsd.dwHeight_;
        depth_ = ddsd.dwDepth_;
        numCompressedLevels_ = ddsd.dwMipMapCount_;
        if (!numCompressedLevels_)
            numCompressedLevels_ = 1;
        SetMemoryUse(dataSize);
        source.Read(data_.Get(), dataSize);
        
        // If uncompressed DDS, convert the data to 8bit RGBA as the texture classes can not currently use eg. RGB565 format
        if (compressedFormat_ == CF_RGBA)
        {
            PROFILE(ConvertDDSToRGBA);
            
            unsigned sourcePixelByteSize = ddsd.ddpfPixelFormat_.dwRGBBitCount_ >> 3;
            unsigned numPixels = dataSize / sourcePixelByteSize;
            
            #define ADJUSTSHIFT(mask, l, r) \
                if (mask && mask >= 0x100) \
                { \
                    while ((mask >> r) >= 0x100) \
                        ++r; \
                } \
                else if (mask && mask < 0x80) \
                { \
                    while ((mask << l) < 0x80) \
                        ++l; \
                }
            
            unsigned rShiftL = 0, gShiftL = 0, bShiftL = 0, aShiftL = 0;
            unsigned rShiftR = 0, gShiftR = 0, bShiftR = 0, aShiftR = 0;
            unsigned rMask = ddsd.ddpfPixelFormat_.dwRBitMask_;
            unsigned gMask = ddsd.ddpfPixelFormat_.dwGBitMask_;
            unsigned bMask = ddsd.ddpfPixelFormat_.dwBBitMask_;
            unsigned aMask = ddsd.ddpfPixelFormat_.dwRGBAlphaBitMask_;
            ADJUSTSHIFT(rMask, rShiftL, rShiftR)
            ADJUSTSHIFT(gMask, gShiftL, gShiftR)
            ADJUSTSHIFT(bMask, bShiftL, bShiftR)
            ADJUSTSHIFT(aMask, aShiftL, aShiftR)
            
            SharedArrayPtr<unsigned char> rgbaData(new unsigned char[numPixels * 4]);
            SetMemoryUse(numPixels * 4);
            
            switch (sourcePixelByteSize)
            {
            case 4:
                {
                    unsigned* src = (unsigned*)data_.Get();
                    unsigned char* dest = rgbaData.Get();
                    
                    while (numPixels--)
                    {
                        unsigned pixels = *src++;
                        *dest++ = ((pixels & rMask) << rShiftL) >> rShiftR;
                        *dest++ = ((pixels & gMask) << gShiftL) >> gShiftR;
                        *dest++ = ((pixels & bMask) << bShiftL) >> bShiftR;
                        *dest++ = ((pixels & aMask) << aShiftL) >> aShiftR;
                    }
                }
                break;
                
            case 3:
                {
                    unsigned char* src = data_.Get();
                    unsigned char* dest = rgbaData.Get();
                    
                    while (numPixels--)
                    {
                        unsigned pixels = src[0] | (src[1] << 8) | (src[2] << 16);
                        src += 3;
                        *dest++ = ((pixels & rMask) << rShiftL) >> rShiftR;
                        *dest++ = ((pixels & gMask) << gShiftL) >> gShiftR;
                        *dest++ = ((pixels & bMask) << bShiftL) >> bShiftR;
                        *dest++ = ((pixels & aMask) << aShiftL) >> aShiftR;
                    }
                }
                break;
                
            default:
                {
                    unsigned short* src = (unsigned short*)data_.Get();
                    unsigned char* dest = rgbaData.Get();
                    
                    while (numPixels--)
                    {
                        unsigned short pixels = *src++;
                        *dest++ = ((pixels & rMask) << rShiftL) >> rShiftR;
                        *dest++ = ((pixels & gMask) << gShiftL) >> gShiftR;
                        *dest++ = ((pixels & bMask) << bShiftL) >> bShiftR;
                        *dest++ = ((pixels & aMask) << aShiftL) >> aShiftR;
                    }
                }
                break;
            }
            
            // Replace with converted data
            data_ = rgbaData;
        }
    }
    else if (fileID == "\253KTX")
    {
        source.Seek(12);

        unsigned endianness = source.ReadUInt();
        unsigned type = source.ReadUInt();
        /* unsigned typeSize = */ source.ReadUInt();
        unsigned format = source.ReadUInt();
        unsigned internalFormat = source.ReadUInt();
        /* unsigned baseInternalFormat = */ source.ReadUInt();
        unsigned width = source.ReadUInt();
        unsigned height = source.ReadUInt();
        unsigned depth = source.ReadUInt();
        /* unsigned arrayElements = */ source.ReadUInt();
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
        /* unsigned flags = */ source.ReadUInt();
        unsigned pixelFormatLo = source.ReadUInt();
        /* unsigned pixelFormatHi = */ source.ReadUInt();
        /* unsigned colourSpace = */ source.ReadUInt();
        /* unsigned channelType = */ source.ReadUInt();
        unsigned height = source.ReadUInt();
        unsigned width = source.ReadUInt();
        unsigned depth = source.ReadUInt();
        /* unsigned numSurfaces = */ source.ReadUInt();
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

bool Image::Save(Serializer& dest) const
{
    PROFILE(SaveImage);

    if (IsCompressed())
    {
        LOGERROR("Can not save compressed image " + GetName());
        return false;
    }

    if (!data_)
    {
        LOGERROR("Can not save zero-sized image " + GetName());
        return false;
    }

    int len;
    unsigned char *png = stbi_write_png_to_mem(data_.Get(), 0, width_, height_, components_, &len);
    bool success = dest.Write(png, len) == (unsigned)len;
    free(png);
    return success;
}


bool Image::SetSize(int width, int height, unsigned components)
{
    return SetSize(width, height, 1, components);
}

bool Image::SetSize(int width, int height, int depth, unsigned components)
{
    if (width == width_ && height == height_ && depth == depth_ && components == components_)
        return true;

    if (width <= 0 || height <= 0 || depth <= 0)
        return false;

    if (components > 4)
    {
        LOGERROR("More than 4 color components are not supported");
        return false;
    }

    data_ = new unsigned char[width * height * depth * components];
    width_ = width;
    height_ = height;
    depth_ = depth;
    components_ = components;
    compressedFormat_ = CF_NONE;
    numCompressedLevels_ = 0;
    nextLevel_.Reset();

    SetMemoryUse(width * height * depth * components);
    return true;
}

void Image::SetPixel(int x, int y, const Color& color)
{
    SetPixelInt(x, y, 0, color.ToUInt());
}

void Image::SetPixel(int x, int y, int z, const Color& color)
{
    SetPixelInt(x, y, z, color.ToUInt());
}

void Image::SetPixelInt(int x, int y, unsigned uintColor)
{
    SetPixelInt(x, y, 0, uintColor);
}

void Image::SetPixelInt(int x, int y, int z, unsigned uintColor)
{
    if (!data_ || x < 0 || x >= width_ || y < 0 || y >= height_ || z < 0 || z >= depth_ || IsCompressed())
        return;

    unsigned char* dest = data_ + (z * width_ * height_ + y * width_ + x) * components_;
    unsigned char* src = (unsigned char*)&uintColor;

    switch (components_)
    {
    case 4:
        dest[3] = src[3];
        // Fall through
    case 3:
        dest[2] = src[2];
        // Fall through
    case 2:
        dest[1]= src[1];
        // Fall through
    default:
        dest[0] = src[0];
        break;
    }
}

void Image::SetData(const unsigned char* pixelData)
{
    if (!data_)
        return;

    if (IsCompressed())
    {
        LOGERROR("Can not set new pixel data for a compressed image");
        return;
    }

    memcpy(data_.Get(), pixelData, width_ * height_ * depth_ * components_);
    nextLevel_.Reset();
}

bool Image::LoadColorLUT(Deserializer& source)
{
    String fileID = source.ReadFileID();

    if (fileID == "DDS " || fileID == "\253KTX" || fileID == "PVR\3")
    {
        LOGERROR("Invalid image format, can not load image");
        return false;
    }

    source.Seek(0);
    int width, height;
    unsigned components;
    unsigned char* pixelDataIn = GetImageData(source, width, height, components);
    if (!pixelDataIn)
    {
        LOGERROR("Could not load image " + source.GetName() + ": " + String(stbi_failure_reason()));
        return false;
    }
    if (components != 3)
    {
        LOGERROR("Invalid image format, can not load image");
        return false;
    }

    SetSize(COLOR_LUT_SIZE, COLOR_LUT_SIZE, COLOR_LUT_SIZE, components);
    SetMemoryUse(width_ * height_ * depth_ * components);

    unsigned char* pixelDataOut = GetData();

    for (int z = 0; z < depth_; ++z)
    {
        for (int y = 0; y < height_; ++y)
        {
            unsigned char* in = &pixelDataIn[z * width_ * 3 + y * width * 3];
            unsigned char* out = &pixelDataOut[z * width_ * height_ * 3 + y * width_ * 3];

            for (int x = 0; x < width_ * 3; x += 3)
            {
                out[x] = in[x];
                out[x+1] = in[x + 1];
                out[x+2] = in[x + 2];
            }
        }
    }

    FreeImageData(pixelDataIn);

    return true;
}

bool Image::FlipHorizontal()
{
    if (!data_)
        return false;

    if (depth_ > 1)
    {
        LOGERROR("FlipHorizontal not supported for 3D images");
        return false;
    }

    if (!IsCompressed())
    {
        SharedArrayPtr<unsigned char> newData(new unsigned char[width_ * height_ * components_]);
        unsigned rowSize = width_ * components_;

        for (int y = 0; y < height_; ++y)
        {
            for (int x = 0; x < width_; ++x)
            {
                for (unsigned c = 0; c < components_; ++c)
                    newData[y * rowSize + x * components_ + c] = data_[y * rowSize + (width_ - x - 1) * components_ + c];
            }
        }
        
        data_ = newData;
    }
    else
    {
        if (compressedFormat_ > CF_DXT5)
        {
            LOGERROR("FlipHorizontal not yet implemented for other compressed formats than RGBA & DXT1,3,5");
            return false;
        }
        
        // Memory use = combined size of the compressed mip levels
        SharedArrayPtr<unsigned char> newData(new unsigned char[GetMemoryUse()]);
        unsigned dataOffset = 0;
        
        for (unsigned i = 0; i < numCompressedLevels_; ++i)
        {
            CompressedLevel level = GetCompressedLevel(i);
            if (!level.data_)
            {
                LOGERROR("Got compressed level with no data, aborting horizontal flip");
                return false;
            }
            
            for (unsigned y = 0; y < level.rows_; ++y)
            {
                for (unsigned x = 0; x < level.rowSize_; x += level.blockSize_)
                {
                    unsigned char* src = level.data_ + y * level.rowSize_ + (level.rowSize_ - level.blockSize_ - x);
                    unsigned char* dest = newData.Get() + y * level.rowSize_ + x;
                    FlipBlockHorizontal(dest, src, compressedFormat_);
                }
            }
            
            dataOffset += level.dataSize_;
        }
        
        data_ = newData;
    }
    
    return true;
}

bool Image::FlipVertical()
{
    if (!data_)
        return false;

    if (depth_ > 1)
    {
        LOGERROR("FlipVertical not supported for 3D images");
        return false;
    }

    if (!IsCompressed())
    {
        SharedArrayPtr<unsigned char> newData(new unsigned char[width_ * height_ * components_]);
        unsigned rowSize = width_ * components_;

        for (int y = 0; y < height_; ++y)
            memcpy(&newData[(height_ - y - 1) * rowSize], &data_[y * rowSize], rowSize);

        data_ = newData;
    }
    else
    {
        if (compressedFormat_ > CF_DXT5)
        {
            LOGERROR("FlipVertical not yet implemented for other compressed formats than DXT1,3,5");
            return false;
        }
        
        // Memory use = combined size of the compressed mip levels
        SharedArrayPtr<unsigned char> newData(new unsigned char[GetMemoryUse()]);
        unsigned dataOffset = 0;
        
        for (unsigned i = 0; i < numCompressedLevels_; ++i)
        {
            CompressedLevel level = GetCompressedLevel(i);
            if (!level.data_)
            {
                LOGERROR("Got compressed level with no data, aborting vertical flip");
                return false;
            }
            
            for (unsigned y = 0; y < level.rows_; ++y)
            {
                unsigned char* src = level.data_ + y * level.rowSize_;
                unsigned char* dest = newData.Get() + dataOffset + (level.rows_ - y - 1) * level.rowSize_;
                
                for (unsigned x = 0; x < level.rowSize_; x += level.blockSize_)
                    FlipBlockVertical(dest + x, src + x, compressedFormat_);
            }
            
            dataOffset += level.dataSize_;
        }
        
        data_ = newData;
    }
    
    return true;
}

bool Image::Resize(int width, int height)
{
    PROFILE(ResizeImage);

    if (IsCompressed())
    {
        LOGERROR("Resize not supported for compressed images");
        return false;
    }

    if (depth_ > 1)
    {
        LOGERROR("Resize not supported for 3D images");
        return false;
    }

    if (!data_ || width <= 0 || height <= 0)
        return false;

    /// \todo Reducing image size does not sample all needed pixels
    SharedArrayPtr<unsigned char> newData(new unsigned char[width * height * components_]);
    for (int y = 0; y < height; ++y)
    {
        for (int x = 0; x < width; ++x)
        {
            // Calculate float coordinates between 0 - 1 for resampling
            float xF = (width_ > 1) ? (float)x / (float)(width - 1) : 0.0f;
            float yF = (height_ > 1) ? (float)y / (float)(height - 1) : 0.0f;
            unsigned uintColor = GetPixelBilinear(xF, yF).ToUInt();
            unsigned char* dest = newData + (y * width + x) * components_;
            unsigned char* src = (unsigned char*)&uintColor;

            switch (components_)
            {
            case 4:
                dest[3] = src[3];
                // Fall through
            case 3:
                dest[2] = src[2];
                // Fall through
            case 2:
                dest[1] = src[1];
                // Fall through
            default:
                dest[0] = src[0];
                break;
            }
        }
    }

    width_ = width;
    height_ = height;
    data_ = newData;
    SetMemoryUse(width * height * depth_ * components_);
    return true;
}

void Image::Clear(const Color& color)
{
    ClearInt(color.ToUInt());
}

void Image::ClearInt(unsigned uintColor)
{
    PROFILE(ClearImage);

    if (!data_)
        return;

    if (IsCompressed())
    {
        LOGERROR("Clear not supported for compressed images");
        return;
    }

    unsigned char* src = (unsigned char*)&uintColor;
    for (unsigned i = 0; i < width_ * height_ * depth_ * components_; ++i)
        data_[i] = src[i % components_];
}

bool Image::SaveBMP(const String& fileName) const
{
    PROFILE(SaveImageBMP);

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

bool Image::SavePNG(const String& fileName) const
{
    PROFILE(SaveImagePNG);

    FileSystem* fileSystem = GetSubsystem<FileSystem>();
    if (fileSystem && !fileSystem->CheckAccess(GetPath(fileName)))
    {
        LOGERROR("Access denied to " + fileName);
        return false;
    }

    if (IsCompressed())
    {
        LOGERROR("Can not save compressed image to PNG");
        return false;
    }

    if (data_)
        return stbi_write_png(GetNativePath(fileName).CString(), width_, height_, components_, data_.Get(), 0) != 0;
    else
        return false;
}

bool Image::SaveTGA(const String& fileName) const
{
    PROFILE(SaveImageTGA);

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
        return stbi_write_tga(GetNativePath(fileName).CString(), width_, height_, components_, data_.Get()) != 0;
    else
        return false;
}

bool Image::SaveJPG(const String & fileName, int quality) const
{
    PROFILE(SaveImageJPG);

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
        return jo_write_jpg(GetNativePath(fileName).CString(), data_.Get(), width_, height_, components_, quality) != 0;
    else
        return false;
}

Color Image::GetPixel(int x, int y) const
{
    return GetPixel(x, y, 0);
}

Color Image::GetPixel(int x, int y, int z) const
{
    if (!data_ || z < 0 || z >= depth_ || IsCompressed())
        return Color::BLACK;
    x = Clamp(x, 0, width_ - 1);
    y = Clamp(y, 0, height_ - 1);

    unsigned char* src = data_ + (z * width_ * height_ + y * width_ + x) * components_;
    Color ret;

    switch (components_)
    {
    case 4:
        ret.a_ = (float)src[3] / 255.0f;
        // Fall through
    case 3:
        ret.b_ = (float)src[2] / 255.0f;
        // Fall through
    case 2:
        ret.g_ = (float)src[1] / 255.0f;
        ret.r_ = (float)src[0] / 255.0f;
        break;
    default:
        ret.r_ = ret.g_ = ret.b_ = (float)src[0] / 255.0f;
        break;
    }

    return ret;
}

unsigned Image::GetPixelInt(int x, int y) const
{
    return GetPixelInt(x, y, 0);
}

unsigned Image::GetPixelInt(int x, int y, int z) const
{
    if (!data_ || z < 0 || z >= depth_ || IsCompressed())
        return 0xff000000;
    x = Clamp(x, 0, width_ - 1);
    y = Clamp(y, 0, height_ - 1);

    unsigned char* src = data_ + (z * width_ * height_ + y * width_ + x) * components_;
    unsigned ret = 0;
    if (components_ < 4)
        ret |= 0xff000000;

    switch (components_)
    {
    case 4:
        ret |= (unsigned)src[3] << 24;
        // Fall through
    case 3:
        ret |= (unsigned)src[2] << 16;
        // Fall through
    case 2:
        ret |= (unsigned)src[1] << 8;
        ret |= (unsigned)src[0];
        break;
    default:
        ret |= (unsigned)src[0] << 16;
        ret |= (unsigned)src[0] << 8;
        ret |= (unsigned)src[0];
        break;
    }

    return ret;
}

Color Image::GetPixelBilinear(float x, float y) const
{
    x = Clamp(x * width_ - 0.5f, 0.0f, (float)(width_ - 1));
    y = Clamp(y * height_ - 0.5f, 0.0f, (float)(height_ - 1));

    int xI = (int)x;
    int yI = (int)y;
    float xF = x - floorf(x);
    float yF = y - floorf(y);

    Color topColor = GetPixel(xI, yI).Lerp(GetPixel(xI + 1, yI), xF);
    Color bottomColor = GetPixel(xI, yI + 1).Lerp(GetPixel(xI + 1, yI + 1), xF);
    return topColor.Lerp(bottomColor, yF);
}

Color Image::GetPixelTrilinear(float x, float y, float z) const
{
    if (depth_ < 2)
        return GetPixelBilinear(x, y);

    x = Clamp(x * width_ - 0.5f, 0.0f, (float)(width_ - 1));
    y = Clamp(y * height_ - 0.5f, 0.0f, (float)(height_ - 1));
    z = Clamp(z * depth_ - 0.5f, 0.0f, (float)(depth_ - 1));

    int xI = (int)x;
    int yI = (int)y;
    int zI = (int)z;
    if (zI == depth_ - 1)
        return GetPixelBilinear(x, y);
    float xF = x - floorf(x);
    float yF = y - floorf(y);
    float zF = z - floorf(z);

    Color topColorNear = GetPixel(xI, yI, zI).Lerp(GetPixel(xI + 1, yI, zI), xF);
    Color bottomColorNear = GetPixel(xI, yI + 1, zI).Lerp(GetPixel(xI + 1, yI + 1, zI), xF);
    Color colorNear = topColorNear.Lerp(bottomColorNear, yF);
    Color topColorFar = GetPixel(xI, yI, zI + 1).Lerp(GetPixel(xI + 1, yI, zI + 1), xF);
    Color bottomColorFar = GetPixel(xI, yI + 1, zI + 1).Lerp(GetPixel(xI + 1, yI + 1, zI + 1), xF);
    Color colorFar = topColorFar.Lerp(bottomColorFar, yF);
    return colorNear.Lerp(colorFar, zF);
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

    if (nextLevel_)
        return nextLevel_;

    PROFILE(CalculateImageMipLevel);

    int widthOut = width_ / 2;
    int heightOut = height_ / 2;
    int depthOut = depth_ / 2;

    if (widthOut < 1)
        widthOut = 1;
    if (heightOut < 1)
        heightOut = 1;
    if (depthOut < 1)
        depthOut = 1;

    SharedPtr<Image> mipImage(new Image(context_));

    if (depth_ > 1)
        mipImage->SetSize(widthOut, heightOut, depthOut, components_);
    else
        mipImage->SetSize(widthOut, heightOut, components_);

    const unsigned char* pixelDataIn = data_.Get();
    unsigned char* pixelDataOut = mipImage->data_.Get();

    // 1D case
    if (depth_ == 1 && (height_ == 1 || width_ == 1))
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
    else if (depth_ == 1)
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
    // 3D case
    else
    {
        switch (components_)
        {
        case 1:
            for (int z = 0; z < depthOut; ++z)
            {
                const unsigned char* inOuter = &pixelDataIn[(z*2)*width_*height_];
                const unsigned char* inInner = &pixelDataIn[(z*2+1)*width_*height_];

                for (int y = 0; y < heightOut; ++y)
                {
                    const unsigned char* inOuterUpper = &inOuter[(y*2)*width_];
                    const unsigned char* inOuterLower = &inOuter[(y*2+1)*width_];
                    const unsigned char* inInnerUpper = &inInner[(y*2)*width_];
                    const unsigned char* inInnerLower = &inInner[(y*2+1)*width_];
                    unsigned char* out = &pixelDataOut[z*widthOut*heightOut + y*widthOut];

                    for (int x = 0; x < widthOut; ++x)
                    {
                        out[x] = ((unsigned)inOuterUpper[x*2] + inOuterUpper[x*2+1] + inOuterLower[x*2] + inOuterLower[x*2+1] +
                            inInnerUpper[x*2] + inInnerUpper[x*2+1] + inInnerLower[x*2] + inInnerLower[x*2+1]) >> 3;
                    }
                }
            }
            break;

        case 2:
            for (int z = 0; z < depthOut; ++z)
            {
                const unsigned char* inOuter = &pixelDataIn[(z*2)*width_*height_*2];
                const unsigned char* inInner = &pixelDataIn[(z*2+1)*width_*height_*2];

                for (int y = 0; y < heightOut; ++y)
                {
                    const unsigned char* inOuterUpper = &inOuter[(y*2)*width_*2];
                    const unsigned char* inOuterLower = &inOuter[(y*2+1)*width_*2];
                    const unsigned char* inInnerUpper = &inInner[(y*2)*width_*2];
                    const unsigned char* inInnerLower = &inInner[(y*2+1)*width_*2];
                    unsigned char* out = &pixelDataOut[z*widthOut*heightOut*2 + y*widthOut*2];

                    for (int x = 0; x < widthOut*2; x += 2)
                    {
                        out[x] = ((unsigned)inOuterUpper[x*2] + inOuterUpper[x*2+2] + inOuterLower[x*2] + inOuterLower[x*2+2] +
                            inInnerUpper[x*2] + inInnerUpper[x*2+2] + inInnerLower[x*2] + inInnerLower[x*2+2]) >> 3;
                        out[x+1] = ((unsigned)inOuterUpper[x*2+1] + inOuterUpper[x*2+3] + inOuterLower[x*2+1] + inOuterLower[x*2+3] +
                            inInnerUpper[x*2+1] + inInnerUpper[x*2+3] + inInnerLower[x*2+1] + inInnerLower[x*2+3]) >> 3;
                    }
                }
            }
            break;

        case 3:
            for (int z = 0; z < depthOut; ++z)
            {
                const unsigned char* inOuter = &pixelDataIn[(z*2)*width_*height_*3];
                const unsigned char* inInner = &pixelDataIn[(z*2+1)*width_*height_*3];

                for (int y = 0; y < heightOut; ++y)
                {
                    const unsigned char* inOuterUpper = &inOuter[(y*2)*width_*3];
                    const unsigned char* inOuterLower = &inOuter[(y*2+1)*width_*3];
                    const unsigned char* inInnerUpper = &inInner[(y*2)*width_*3];
                    const unsigned char* inInnerLower = &inInner[(y*2+1)*width_*3];
                    unsigned char* out = &pixelDataOut[z*widthOut*heightOut*3 + y*widthOut*3];

                    for (int x = 0; x < widthOut*3; x += 3)
                    {
                        out[x] = ((unsigned)inOuterUpper[x*2] + inOuterUpper[x*2+3] + inOuterLower[x*2] + inOuterLower[x*2+3] +
                            inInnerUpper[x*2] + inInnerUpper[x*2+3] + inInnerLower[x*2] + inInnerLower[x*2+3]) >> 3;
                        out[x+1] = ((unsigned)inOuterUpper[x*2+1] + inOuterUpper[x*2+4] + inOuterLower[x*2+1] + inOuterLower[x*2+4] +
                            inInnerUpper[x*2+1] + inInnerUpper[x*2+4] + inInnerLower[x*2+1] + inInnerLower[x*2+4]) >> 3;
                        out[x+2] = ((unsigned)inOuterUpper[x*2+2] + inOuterUpper[x*2+5] + inOuterLower[x*2+2] + inOuterLower[x*2+5] +
                            inInnerUpper[x*2+2] + inInnerUpper[x*2+5] + inInnerLower[x*2+2] + inInnerLower[x*2+5]) >> 3;
                    }
                }
            }
            break;

        case 4:
            for (int z = 0; z < depthOut; ++z)
            {
                const unsigned char* inOuter = &pixelDataIn[(z*2)*width_*height_*4];
                const unsigned char* inInner = &pixelDataIn[(z*2+1)*width_*height_*4];

                for (int y = 0; y < heightOut; ++y)
                {
                    const unsigned char* inOuterUpper = &inOuter[(y*2)*width_*4];
                    const unsigned char* inOuterLower = &inOuter[(y*2+1)*width_*4];
                    const unsigned char* inInnerUpper = &inInner[(y*2)*width_*4];
                    const unsigned char* inInnerLower = &inInner[(y*2+1)*width_*4];
                    unsigned char* out = &pixelDataOut[z*widthOut*heightOut*4 + y*widthOut*4];

                    for (int x = 0; x < widthOut*4; x += 4)
                    {
                        out[x] = ((unsigned)inOuterUpper[x*2] + inOuterUpper[x*2+4] + inOuterLower[x*2] + inOuterLower[x*2+4] +
                            inInnerUpper[x*2] + inInnerUpper[x*2+4] + inInnerLower[x*2] + inInnerLower[x*2+4]) >> 3;
                        out[x+1] = ((unsigned)inOuterUpper[x*2+1] + inOuterUpper[x*2+5] + inOuterLower[x*2+1] + inOuterLower[x*2+5] +
                            inInnerUpper[x*2+1] + inInnerUpper[x*2+5] + inInnerLower[x*2+1] + inInnerLower[x*2+5]) >> 3;
                        out[x+2] = ((unsigned)inOuterUpper[x*2+2] + inOuterUpper[x*2+6] + inOuterLower[x*2+2] + inOuterLower[x*2+6] +
                            inInnerUpper[x*2+2] + inInnerUpper[x*2+6] + inInnerLower[x*2+2] + inInnerLower[x*2+6]) >> 3;
                    }
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
    level.depth_ = depth_;

    if (compressedFormat_ == CF_RGBA)
    {
        level.blockSize_ = 4;
        unsigned i = 0;
        unsigned offset = 0;

        for (;;)
        {
            if (!level.width_)
                level.width_ = 1;
            if (!level.height_)
                level.height_ = 1;
            if (!level.depth_)
                level.depth_ = 1;

            level.rowSize_ = level.width_ * level.blockSize_;
            level.rows_ = level.height_;
            level.data_ = data_.Get() + offset;
            level.dataSize_ = level.depth_ * level.rows_ * level.rowSize_;

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
            level.depth_ /= 2;
            ++i;
        }
    }
    else if (compressedFormat_ < CF_PVRTC_RGB_2BPP)
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
            if (!level.depth_)
                level.depth_ = 1;

            level.rowSize_ = ((level.width_ + 3) / 4) * level.blockSize_;
            level.rows_ = ((level.height_ + 3) / 4);
            level.data_ = data_.Get() + offset;
            level.dataSize_ = level.depth_ * level.rows_ * level.rowSize_;

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
            level.depth_ /= 2;
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

Image* Image::GetSubimage(const IntRect& rect) const
{
    if (!data_)
        return 0;

    if (depth_ > 1)
    {
        LOGERROR("Subimage not supported for 3D images");
        return 0;
    }
    
    if (rect.left_ < 0 || rect.top_ < 0 || rect.right_ > width_ || rect.bottom_ > height_ || !rect.Width() || !rect.Height())
    {
        LOGERROR("Can not get subimage from image " + GetName() + " with invalid region");
        return 0;
    }
    
    if (!IsCompressed())
    {
        int x = rect.left_;
        int y = rect.top_;
        int width = rect.Width();
        int height = rect.Height();

        Image* image = new Image(context_);
        image->SetSize(width, height, components_);

        unsigned char* dest = image->GetData();
        unsigned char* src = data_.Get() + (y * width_ + x) * components_;
        for (int i = 0; i < height; ++i)
        {
            memcpy(dest, src, width * components_);
            dest += width * components_;
            src += width_ * components_;
        }
    
        return image;
    }
    else
    {
        // Pad the region to be a multiple of block size
        IntRect paddedRect = rect;
        paddedRect.left_ = (rect.left_ / 4) * 4;
        paddedRect.top_ = (rect.top_ / 4) * 4;
        paddedRect.right_ = (rect.right_ / 4) * 4;
        paddedRect.bottom_ = (rect.bottom_ / 4) * 4;
        IntRect currentRect = paddedRect;
        
        PODVector<unsigned char> subimageData;
        unsigned subimageLevels = 0;
        
        // Save as many mips as possible until the next mip would cross a block boundary
        for (unsigned i = 0; i < numCompressedLevels_; ++i)
        {
            CompressedLevel level = GetCompressedLevel(i);
            if (!level.data_)
                break;

            // Mips are stored continuously
            unsigned destStartOffset = subimageData.Size();
            unsigned destRowSize = currentRect.Width() / 4 * level.blockSize_;
            unsigned destSize = currentRect.Height() / 4 * destRowSize;
            if (!destSize)
                break;
            
            subimageData.Resize(destStartOffset + destSize);
            unsigned char* dest = &subimageData[destStartOffset];
            
            for (int y = currentRect.top_; y < currentRect.bottom_; y += 4)
            {
                unsigned char* src = level.data_ + level.rowSize_ * (y / 4) + currentRect.left_ / 4 * level.blockSize_;
                memcpy(dest, src, destRowSize);
                dest += destRowSize;
            }
            
            ++subimageLevels;
            if ((currentRect.left_ & 4) || (currentRect.right_ & 4) || (currentRect.top_ & 4) || (currentRect.bottom_ & 4))
                break;
            else
            {
                currentRect.left_ /= 2;
                currentRect.right_ /= 2;
                currentRect.top_ /= 2;
                currentRect.bottom_ /= 2;
            }
        }
        
        if (!subimageLevels)
        {
            LOGERROR("Subimage region from compressed image " + GetName() + " did not produce any data");
            return 0;
        }
        
        Image* image = new Image(context_);
        image->width_ = paddedRect.Width();
        image->height_ = paddedRect.Height();
        image->depth_ = 1;
        image->compressedFormat_ = compressedFormat_;
        image->numCompressedLevels_ = subimageLevels;
        image->components_ = components_;
        image->data_ = new unsigned char[subimageData.Size()];
        memcpy(image->data_.Get(), &subimageData[0], subimageData.Size());
        image->SetMemoryUse(subimageData.Size());
        
        return image;
    }
}

SDL_Surface* Image::GetSDLSurface(const IntRect& rect) const
{
    if (!data_)
        return 0;

    if (depth_ > 1)
    {
        LOGERROR("Can not get SDL surface from 3D image");
        return 0;
    }
    
    if (IsCompressed())
    {
        LOGERROR("Can not get SDL surface from compressed image " + GetName());
        return 0;
    }

    if (components_ < 3)
    {
        LOGERROR("Can not get SDL surface from image " + GetName() + " with less than 3 components");
        return 0;
    }

    IntRect imageRect = rect;
    // Use full image if illegal rect
    if (imageRect.left_ < 0 || imageRect.top_ < 0 || imageRect.right_ > width_ || imageRect.bottom_ > height_ ||
        imageRect.left_ >= imageRect.right_ || imageRect.top_ >= imageRect.bottom_)
    {
        imageRect.left_ = 0;
        imageRect.top_ = 0;
        imageRect.right_ = width_;
        imageRect.bottom_ = height_;
    }

    int imageWidth = width_;
    int width = imageRect.Width();
    int height = imageRect.Height();

    // Assume little-endian for all the supported platforms
    unsigned rMask = 0x000000ff;
    unsigned gMask = 0x0000ff00;
    unsigned bMask = 0x00ff0000;
    unsigned aMask = 0xff000000;

    SDL_Surface* surface = SDL_CreateRGBSurface(0, width, height, components_ * 8, rMask, gMask, bMask, aMask);
    if (surface)
    {
        SDL_LockSurface(surface);

        unsigned char* destination = reinterpret_cast<unsigned char*>(surface->pixels);
        unsigned char* source = data_ + components_ * (imageWidth * imageRect.top_ + imageRect.left_);
        for (int i = 0; i < height; ++i)
        {
            memcpy(destination, source, components_ * width);
            destination += surface->pitch;
            source += components_ * imageWidth;
        }

        SDL_UnlockSurface(surface);
    }
    else
        LOGERROR("Failed to create SDL surface from image " + GetName());

    return surface;
}

void Image::PrecalculateLevels()
{
    if (!data_ || IsCompressed())
        return;

    PROFILE(PrecalculateImageMipLevels);

    nextLevel_.Reset();

    if (width_ > 1 || height_ > 1)
    {
        SharedPtr<Image> current = GetNextLevel();
        nextLevel_ = current;
        while (current && (current->width_ > 1 || current->height_ > 1))
        {
            current->nextLevel_ = current->GetNextLevel();
            current = current->nextLevel_;
        }
    }
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

}
