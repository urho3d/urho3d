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

#include "../../Precompiled.h"

#include "../../Core/Context.h"
#include "../../Core/Profiler.h"
#include "../../Graphics/Graphics.h"
#include "../../Graphics/GraphicsEvents.h"
#include "../../Graphics/GraphicsImpl.h"
#include "../../Graphics/Renderer.h"
#include "../../Graphics/Texture3D.h"
#include "../../IO/FileSystem.h"
#include "../../IO/Log.h"
#include "../../Resource/ResourceCache.h"
#include "../../Resource/XMLFile.h"

#include "../../DebugNew.h"

namespace Urho3D
{

void Texture3D::OnDeviceLost()
{
    if (usage_ > TEXTURE_STATIC)
        Release();
}

void Texture3D::OnDeviceReset()
{
    if (usage_ > TEXTURE_STATIC || !object_.ptr_ || dataPending_)
    {
        // If has a resource file, reload through the resource cache. Otherwise just recreate.
        ResourceCache* cache = GetSubsystem<ResourceCache>();
        if (cache->Exists(GetName()))
            dataLost_ = !cache->ReloadResource(this);

        if (!object_.ptr_)
        {
            Create();
            dataLost_ = true;
        }
    }

    dataPending_ = false;
}

void Texture3D::Release()
{
    if (graphics_)
    {
        for (unsigned i = 0; i < MAX_TEXTURE_UNITS; ++i)
        {
            if (graphics_->GetTexture(i) == this)
                graphics_->SetTexture(i, nullptr);
        }
    }

    URHO3D_SAFE_RELEASE(object_.ptr_);
}

bool Texture3D::SetData(unsigned level, int x, int y, int z, int width, int height, int depth, const void* data)
{
    URHO3D_PROFILE(SetTextureData);

    if (!object_.ptr_)
    {
        URHO3D_LOGERROR("No texture created, can not set data");
        return false;
    }

    if (!data)
    {
        URHO3D_LOGERROR("Null source for setting data");
        return false;
    }

    if (level >= levels_)
    {
        URHO3D_LOGERROR("Illegal mip level for setting data");
        return false;
    }

    if (graphics_->IsDeviceLost())
    {
        URHO3D_LOGWARNING("Texture data assignment while device is lost");
        dataPending_ = true;
        return true;
    }

    if (IsCompressed())
    {
        x &= ~3;
        y &= ~3;
    }

    int levelWidth = GetLevelWidth(level);
    int levelHeight = GetLevelHeight(level);
    int levelDepth = GetLevelDepth(level);
    if (x < 0 || x + width > levelWidth || y < 0 || y + height > levelHeight || z < 0 || z + depth > levelDepth || width <= 0 ||
        height <= 0 || depth <= 0)
    {
        URHO3D_LOGERROR("Illegal dimensions for setting data");
        return false;
    }

    D3DLOCKED_BOX d3dLockedBox;
    D3DBOX d3dBox;
    d3dBox.Left = (UINT)x;
    d3dBox.Top = (UINT)y;
    d3dBox.Front = (UINT)z;
    d3dBox.Right = (UINT)(x + width);
    d3dBox.Bottom = (UINT)(y + height);
    d3dBox.Back = (UINT)(z + depth);

    DWORD flags = 0;
    if (level == 0 && x == 0 && y == 0 && z == 0 && width == levelWidth && height == levelHeight && depth == levelDepth &&
        usage_ > TEXTURE_STATIC)
        flags |= D3DLOCK_DISCARD;

    HRESULT hr = ((IDirect3DVolumeTexture9*)object_.ptr_)->LockBox(level, &d3dLockedBox, (flags & D3DLOCK_DISCARD) ? nullptr : &d3dBox, flags);
    if (FAILED(hr))
    {
        URHO3D_LOGD3DERROR("Could not lock texture", hr);
        return false;
    }

    if (IsCompressed())
    {
        height = (height + 3) >> 2;
        y >>= 2;
    }

    unsigned char* src = (unsigned char*)data;
    unsigned rowSize = GetRowDataSize(width);

    // GetRowDataSize() returns CPU-side (source) data size, so need to convert for X8R8G8B8
    if (format_ == D3DFMT_X8R8G8B8)
        rowSize = rowSize / 3 * 4;

    // Perform conversion from RGB / RGBA as necessary
    switch (format_)
    {
    default:
        for (int k = 0; k < levelDepth; ++k)
        {
            for (int i = 0; i < height; ++i)
            {
                unsigned char
                    * dest = (unsigned char*)d3dLockedBox.pBits + (k * d3dLockedBox.SlicePitch) + i * d3dLockedBox.RowPitch;
                memcpy(dest, src, rowSize);
                src += rowSize;
            }
        }
        break;

    case D3DFMT_X8R8G8B8:
        for (int k = 0; k < levelDepth; ++k)
        {
            for (int i = 0; i < height; ++i)
            {
                unsigned char
                    * dest = (unsigned char*)d3dLockedBox.pBits + (k * d3dLockedBox.SlicePitch) + i * d3dLockedBox.RowPitch;
                for (int j = 0; j < width; ++j)
                {
                    *dest++ = src[2];
                    *dest++ = src[1];
                    *dest++ = src[0];
                    *dest++ = 255;
                    src += 3;
                }
            }
        }
        break;

    case D3DFMT_A8R8G8B8:
        for (int k = 0; k < levelDepth; ++k)
        {
            for (int i = 0; i < height; ++i)
            {
                unsigned char
                    * dest = (unsigned char*)d3dLockedBox.pBits + (k * d3dLockedBox.SlicePitch) + i * d3dLockedBox.RowPitch;
                for (int j = 0; j < width; ++j)
                {
                    *dest++ = src[2];
                    *dest++ = src[1];
                    *dest++ = src[0];
                    *dest++ = src[3];
                    src += 4;
                }
            }
        }
        break;
    }

    ((IDirect3DVolumeTexture9*)object_.ptr_)->UnlockBox(level);
    return true;
}

bool Texture3D::SetData(Image* image, bool useAlpha)
{
    if (!image)
    {
        URHO3D_LOGERROR("Null image, can not load texture");
        return false;
    }

    // Use a shared ptr for managing the temporary mip images created during this function
    SharedPtr<Image> mipImage;
    unsigned memoryUse = sizeof(Texture3D);
    MaterialQuality quality = QUALITY_HIGH;
    Renderer* renderer = GetSubsystem<Renderer>();
    if (renderer)
        quality = renderer->GetTextureQuality();

    if (!image->IsCompressed())
    {
        unsigned char* levelData = image->GetData();
        int levelWidth = image->GetWidth();
        int levelHeight = image->GetHeight();
        int levelDepth = image->GetDepth();
        unsigned components = image->GetComponents();
        unsigned format = 0;

        // Discard unnecessary mip levels
        for (unsigned i = 0; i < mipsToSkip_[quality]; ++i)
        {
            mipImage = image->GetNextLevel(); image = mipImage;
            levelData = image->GetData();
            levelWidth = image->GetWidth();
            levelHeight = image->GetHeight();
            levelDepth = image->GetDepth();
        }

        switch (components)
        {
        case 1:
            format = useAlpha ? Graphics::GetAlphaFormat() : Graphics::GetLuminanceFormat();
            break;

        case 2:
            format = Graphics::GetLuminanceAlphaFormat();
            break;

        case 3:
            format = Graphics::GetRGBFormat();
            break;

        case 4:
            format = Graphics::GetRGBAFormat();
            break;

        default:
            assert(false);  // Should never reach here
            break;
        }

        // If image was previously compressed, reset number of requested levels to avoid error if level count is too high for new size
        if (IsCompressed() && requestedLevels_ > 1)
            requestedLevels_ = 0;
        SetSize(levelWidth, levelHeight, levelDepth, format);

        for (unsigned i = 0; i < levels_; ++i)
        {
            SetData(i, 0, 0, 0, levelWidth, levelHeight, levelDepth, levelData);
            memoryUse += levelWidth * levelHeight * levelDepth * components;

            if (i < levels_ - 1)
            {
                mipImage = image->GetNextLevel(); image = mipImage;
                levelData = image->GetData();
                levelWidth = image->GetWidth();
                levelHeight = image->GetHeight();
                levelDepth = image->GetDepth();
            }
        }
    }
    else
    {
        int width = image->GetWidth();
        int height = image->GetHeight();
        int depth = image->GetDepth();
        unsigned levels = image->GetNumCompressedLevels();
        unsigned format = graphics_->GetFormat(image->GetCompressedFormat());
        bool needDecompress = false;

        if (!format)
        {
            format = Graphics::GetRGBAFormat();
            needDecompress = true;
        }

        unsigned mipsToSkip = mipsToSkip_[quality];
        if (mipsToSkip >= levels)
            mipsToSkip = levels - 1;
        while (mipsToSkip && (width / (1 << mipsToSkip) < 4 || height / (1 << mipsToSkip) < 4 || depth / (1 << mipsToSkip) < 4))
            --mipsToSkip;
        width /= (1 << mipsToSkip);
        height /= (1 << mipsToSkip);
        depth /= (1 << mipsToSkip);

        SetNumLevels(Max((levels - mipsToSkip), 1U));
        SetSize(width, height, depth, format);

        for (unsigned i = 0; i < levels_ && i < levels - mipsToSkip; ++i)
        {
            CompressedLevel level = image->GetCompressedLevel(i + mipsToSkip);
            if (!needDecompress)
            {
                SetData(i, 0, 0, 0, level.width_, level.height_, level.depth_, level.data_);
                memoryUse += level.depth_ * level.rows_ * level.rowSize_;
            }
            else
            {
                unsigned char* rgbaData = new unsigned char[level.width_ * level.height_ * level.depth_ * 4];
                level.Decompress(rgbaData);
                SetData(i, 0, 0, 0, level.width_, level.height_, level.depth_, rgbaData);
                memoryUse += level.width_ * level.height_ * level.depth_ * 4;
                delete[] rgbaData;
            }
        }
    }

    SetMemoryUse(memoryUse);
    return true;
}

bool Texture3D::GetData(unsigned level, void* dest) const
{
    if (!object_.ptr_)
    {
        URHO3D_LOGERROR("No texture created, can not get data");
        return false;
    }

    if (!dest)
    {
        URHO3D_LOGERROR("Null destination for getting data");
        return false;
    }

    if (level >= levels_)
    {
        URHO3D_LOGERROR("Illegal mip level for getting data");
        return false;
    }

    if (graphics_->IsDeviceLost())
    {
        URHO3D_LOGWARNING("Getting texture data while device is lost");
        return false;
    }

    int levelWidth = GetLevelWidth(level);
    int levelHeight = GetLevelHeight(level);
    int levelDepth = GetLevelDepth(level);

    D3DLOCKED_BOX d3dLockedBox;
    D3DBOX d3dBox;
    d3dBox.Left = 0;
    d3dBox.Top = 0;
    d3dBox.Front = 0;
    d3dBox.Right = (UINT)levelWidth;
    d3dBox.Bottom = (UINT)levelHeight;
    d3dBox.Back = (UINT)levelDepth;

    HRESULT hr = ((IDirect3DVolumeTexture9*)object_.ptr_)->LockBox(level, &d3dLockedBox, &d3dBox, D3DLOCK_READONLY);
    if (FAILED(hr))
    {
        URHO3D_LOGD3DERROR("Could not lock texture", hr);
        return false;
    }

    int height = levelHeight;
    if (IsCompressed())
        height = (height + 3) >> 2;

    unsigned char* destPtr = (unsigned char*)dest;
    unsigned rowSize = GetRowDataSize(levelWidth);
    // GetRowDataSize() returns CPU-side (destination) data size, so need to convert for X8R8G8B8
    if (format_ == D3DFMT_X8R8G8B8)
        rowSize = rowSize / 3 * 4;

    // Perform conversion to RGB / RGBA as necessary
    switch (format_)
    {
    default:
        for (int k = 0; k < levelDepth; ++k)
        {
            for (int i = 0; i < height; ++i)
            {
                unsigned char* src = (unsigned char*)d3dLockedBox.pBits + (k * d3dLockedBox.SlicePitch) + i * d3dLockedBox.RowPitch;
                memcpy(destPtr, src, rowSize);
                destPtr += rowSize;
            }
        }
        break;

    case D3DFMT_X8R8G8B8:
        for (int k = 0; k < levelDepth; ++k)
        {
            for (int i = 0; i < height; ++i)
            {
                unsigned char* src = (unsigned char*)d3dLockedBox.pBits + (k * d3dLockedBox.SlicePitch) + i * d3dLockedBox.RowPitch;
                for (int j = 0; j < levelWidth; ++j)
                {
                    destPtr[2] = *src++;
                    destPtr[1] = *src++;
                    destPtr[0] = *src++;
                    ++src;
                    destPtr += 3;
                }
            }
        }
        break;

    case D3DFMT_A8R8G8B8:
        for (int k = 0; k < levelDepth; ++k)
        {
            for (int i = 0; i < height; ++i)
            {
                unsigned char* src = (unsigned char*)d3dLockedBox.pBits + (k * d3dLockedBox.SlicePitch) + i * d3dLockedBox.RowPitch;
                for (int j = 0; j < levelWidth; ++j)
                {
                    destPtr[2] = *src++;
                    destPtr[1] = *src++;
                    destPtr[0] = *src++;
                    destPtr[3] = *src++;
                    destPtr += 4;
                }
            }
        }
        break;
    }

    ((IDirect3DVolumeTexture9*)object_.ptr_)->UnlockBox(level);
    return true;
}

bool Texture3D::Create()
{
    Release();

    if (!graphics_ || !width_ || !height_)
        return false;

    if (graphics_->IsDeviceLost())
    {
        URHO3D_LOGWARNING("Texture creation while device is lost");
        return true;
    }

    unsigned pool = usage_ > TEXTURE_STATIC ? D3DPOOL_DEFAULT : D3DPOOL_MANAGED;
    unsigned d3dUsage = usage_ == TEXTURE_DYNAMIC ? D3DUSAGE_DYNAMIC : 0;

    IDirect3DDevice9* device = graphics_->GetImpl()->GetDevice();
    HRESULT hr = device->CreateVolumeTexture(
        (UINT)width_,
        (UINT)height_,
        (UINT)depth_,
        requestedLevels_,
        d3dUsage,
        (D3DFORMAT)format_,
        (D3DPOOL)pool,
        (IDirect3DVolumeTexture9**)&object_,
        nullptr);
    if (FAILED(hr))
    {
        URHO3D_LOGD3DERROR("Could not create texture", hr);
        URHO3D_SAFE_RELEASE(object_.ptr_);
        return false;
    }

    levels_ = ((IDirect3DVolumeTexture9*)object_.ptr_)->GetLevelCount();

    return true;
}

}
