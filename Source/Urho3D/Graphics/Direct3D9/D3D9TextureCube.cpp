//
// Copyright (c) 2008-2022 the Urho3D project.
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
#include "../../Graphics/Renderer.h"
#include "../../Graphics/TextureCube.h"
#include "../../IO/FileSystem.h"
#include "../../IO/Log.h"
#include "../../Resource/ResourceCache.h"
#include "../../Resource/XMLFile.h"
#include "D3D9GraphicsImpl.h"

#include "../../DebugNew.h"

#ifdef _MSC_VER
#pragma warning(disable:4355)
#endif

namespace Urho3D
{

void TextureCube::OnDeviceLost_D3D9()
{
    if (usage_ > TEXTURE_STATIC)
        Release_D3D9();
}

void TextureCube::OnDeviceReset_D3D9()
{
    if (usage_ > TEXTURE_STATIC || !object_.ptr_ || dataPending_)
    {
        // If has a resource file, reload through the resource cache. Otherwise just recreate.
        ResourceCache* cache = GetSubsystem<ResourceCache>();
        if (cache->Exists(GetName()))
            dataLost_ = !cache->ReloadResource(this);

        if (!object_.ptr_)
        {
            Create_D3D9();
            dataLost_ = true;
        }
    }

    dataPending_ = false;
}

void TextureCube::Release_D3D9()
{
    if (graphics_)
    {
        for (unsigned i = 0; i < MAX_TEXTURE_UNITS; ++i)
        {
            if (graphics_->GetTexture(i) == this)
                graphics_->SetTexture(i, nullptr);
        }
    }

    for (unsigned i = 0; i < MAX_CUBEMAP_FACES; ++i)
    {
        if (renderSurfaces_[i])
            renderSurfaces_[i]->Release();
    }

    URHO3D_SAFE_RELEASE(object_.ptr_);

    resolveDirty_ = false;
    levelsDirty_ = false;
}

bool TextureCube::SetData_D3D9(CubeMapFace face, unsigned level, int x, int y, int width, int height, const void* data)
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

    if (IsCompressed_D3D9())
    {
        x &= ~3;
        y &= ~3;
    }

    int levelWidth = GetLevelWidth(level);
    int levelHeight = GetLevelHeight(level);
    if (x < 0 || x + width > levelWidth || y < 0 || y + height > levelHeight || width <= 0 || height <= 0)
    {
        URHO3D_LOGERROR("Illegal dimensions for setting data");
        return false;
    }

    D3DLOCKED_RECT d3dLockedRect;
    RECT d3dRect;
    d3dRect.left = x;
    d3dRect.top = y;
    d3dRect.right = x + width;
    d3dRect.bottom = y + height;

    DWORD flags = 0;
    if (level == 0 && x == 0 && y == 0 && width == levelWidth && height == levelHeight && usage_ > TEXTURE_STATIC)
        flags |= D3DLOCK_DISCARD;

    HRESULT hr = ((IDirect3DCubeTexture9*)object_.ptr_)->LockRect((D3DCUBEMAP_FACES)face, level, &d3dLockedRect,
        (flags & D3DLOCK_DISCARD) ? nullptr : &d3dRect, flags);
    if (FAILED(hr))
    {
        URHO3D_LOGD3DERROR("Could not lock texture", hr);
        return false;
    }

    if (IsCompressed_D3D9())
    {
        height = (height + 3) >> 2;
        y >>= 2;
    }

    unsigned char* src = (unsigned char*)data;
    unsigned rowSize = GetRowDataSize_D3D9(width);

    // GetRowDataSize_D3D9() returns CPU-side (source) data size, so need to convert for X8R8G8B8
    if (format_ == D3DFMT_X8R8G8B8)
        rowSize = rowSize / 3 * 4;

    // Perform conversion from RGB / RGBA as necessary
    switch (format_)
    {
    default:
        for (int i = 0; i < height; ++i)
        {
            unsigned char* dest = (unsigned char*)d3dLockedRect.pBits + i * d3dLockedRect.Pitch;
            memcpy(dest, src, rowSize);
            src += rowSize;
        }
        break;

    case D3DFMT_X8R8G8B8:
        for (int i = 0; i < height; ++i)
        {
            unsigned char* dest = (unsigned char*)d3dLockedRect.pBits + i * d3dLockedRect.Pitch;
            for (int j = 0; j < width; ++j)
            {
                *dest++ = src[2];
                *dest++ = src[1];
                *dest++ = src[0];
                *dest++ = 255;
                src += 3;
            }
        }
        break;

    case D3DFMT_A8R8G8B8:
        for (int i = 0; i < height; ++i)
        {
            unsigned char* dest = (unsigned char*)d3dLockedRect.pBits + i * d3dLockedRect.Pitch;
            for (int j = 0; j < width; ++j)
            {
                *dest++ = src[2];
                *dest++ = src[1];
                *dest++ = src[0];
                *dest++ = src[3];
                src += 4;
            }
        }
        break;
    }

    ((IDirect3DCubeTexture9*)object_.ptr_)->UnlockRect((D3DCUBEMAP_FACES)face, level);
    return true;
}

bool TextureCube::SetData_D3D9(CubeMapFace face, Deserializer& source)
{
    SharedPtr<Image> image(new Image(context_));
    if (!image->Load(source))
        return false;

    return SetData_D3D9(face, image);
}

bool TextureCube::SetData_D3D9(CubeMapFace face, Image* image, bool useAlpha)
{
    if (!image)
    {
        URHO3D_LOGERROR("Null image, can not load texture");
        return false;
    }

    // Use a shared ptr for managing the temporary mip images created during this function
    SharedPtr<Image> mipImage;
    unsigned memoryUse = 0;
    MaterialQuality quality = QUALITY_HIGH;
    Renderer* renderer = GetSubsystem<Renderer>();
    if (renderer)
        quality = renderer->GetTextureQuality();

    if (!image->IsCompressed())
    {
        unsigned char* levelData = image->GetData();
        int levelWidth = image->GetWidth();
        int levelHeight = image->GetHeight();
        unsigned components = image->GetComponents();
        unsigned format = 0;

        if (levelWidth != levelHeight)
        {
            URHO3D_LOGERROR("Cube texture width not equal to height");
            return false;
        }

        // Discard unnecessary mip levels
        for (unsigned i = 0; i < mipsToSkip_[quality]; ++i)
        {
            mipImage = image->GetNextLevel(); image = mipImage;
            levelData = image->GetData();
            levelWidth = image->GetWidth();
            levelHeight = image->GetHeight();
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

        // Create the texture when face 0 is being loaded, check that rest of the faces are same size & format
        if (!face)
        {
            // If image was previously compressed, reset number of requested levels to avoid error if level count is too high for new size
            if (IsCompressed_D3D9() && requestedLevels_ > 1)
                requestedLevels_ = 0;
            SetSize(levelWidth, format);
        }
        else
        {
            if (!object_.ptr_)
            {
                URHO3D_LOGERROR("Cube texture face 0 must be loaded first");
                return false;
            }
            if (levelWidth != width_ || format != format_)
            {
                URHO3D_LOGERROR("Cube texture face does not match size or format of face 0");
                return false;
            }
        }

        for (unsigned i = 0; i < levels_; ++i)
        {
            SetData_D3D9(face, i, 0, 0, levelWidth, levelHeight, levelData);
            memoryUse += levelWidth * levelHeight * components;

            if (i < levels_ - 1)
            {
                mipImage = image->GetNextLevel(); image = mipImage;
                levelData = image->GetData();
                levelWidth = image->GetWidth();
                levelHeight = image->GetHeight();
            }
        }
    }
    else
    {
        int width = image->GetWidth();
        int height = image->GetHeight();
        unsigned levels = image->GetNumCompressedLevels();
        unsigned format = graphics_->GetFormat(image->GetCompressedFormat());
        bool needDecompress = false;

        if (width != height)
        {
            URHO3D_LOGERROR("Cube texture width not equal to height");
            return false;
        }

        if (!format)
        {
            format = Graphics::GetRGBAFormat();
            needDecompress = true;
        }

        unsigned mipsToSkip = mipsToSkip_[quality];
        if (mipsToSkip >= levels)
            mipsToSkip = levels - 1;
        while (mipsToSkip && (width / (1 << mipsToSkip) < 4 || height / (1 << mipsToSkip) < 4))
            --mipsToSkip;
        width /= (1 << mipsToSkip);
        height /= (1 << mipsToSkip);

        // Create the texture when face 0 is being loaded, assume rest of the faces are same size & format
        if (!face)
        {
            SetNumLevels(Max((levels - mipsToSkip), 1U));
            SetSize(width, format);
        }
        else
        {
            if (!object_.ptr_)
            {
                URHO3D_LOGERROR("Cube texture face 0 must be loaded first");
                return false;
            }
            if (width != width_ || format != format_)
            {
                URHO3D_LOGERROR("Cube texture face does not match size or format of face 0");
                return false;
            }
        }

        for (unsigned i = 0; i < levels_ && i < levels - mipsToSkip; ++i)
        {
            CompressedLevel level = image->GetCompressedLevel(i + mipsToSkip);
            if (!needDecompress)
            {
                SetData_D3D9(face, i, 0, 0, level.width_, level.height_, level.data_);
                memoryUse += level.rows_ * level.rowSize_;
            }
            else
            {
                unsigned char* rgbaData = new unsigned char[level.width_ * level.height_ * 4];
                level.Decompress(rgbaData);
                SetData_D3D9(face, i, 0, 0, level.width_, level.height_, rgbaData);
                memoryUse += level.width_ * level.height_ * 4;
                delete[] rgbaData;
            }
        }
    }

    faceMemoryUse_[face] = memoryUse;
    unsigned totalMemoryUse = sizeof(TextureCube);
    for (unsigned i = 0; i < MAX_CUBEMAP_FACES; ++i)
        totalMemoryUse += faceMemoryUse_[i];
    SetMemoryUse(totalMemoryUse);

    return true;
}

bool TextureCube::GetData_D3D9(CubeMapFace face, unsigned level, void* dest) const
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

    if (resolveDirty_)
        graphics_->ResolveToTexture(const_cast<TextureCube*>(this));

    int levelWidth = GetLevelWidth(level);
    int levelHeight = GetLevelHeight(level);

    D3DLOCKED_RECT d3dLockedRect;
    RECT d3dRect;
    d3dRect.left = 0;
    d3dRect.top = 0;
    d3dRect.right = levelWidth;
    d3dRect.bottom = levelHeight;

    IDirect3DSurface9* offscreenSurface = nullptr;
    // Need to use a offscreen surface & GetRenderTargetData() for rendertargets
    if (renderSurfaces_[face])
    {
        if (level != 0)
        {
            URHO3D_LOGERROR("Can only get mip level 0 data from a rendertarget");
            return false;
        }

        // If multisampled, must copy the surface of the resolve texture instead of the multisampled surface
        IDirect3DSurface9* resolveSurface = nullptr;
        if (multiSample_ > 1)
        {
            HRESULT hr = ((IDirect3DCubeTexture9*)object_.ptr_)->GetCubeMapSurface((D3DCUBEMAP_FACES)face, 0,
                (IDirect3DSurface9**)&resolveSurface);
            if (FAILED(hr))
            {
                URHO3D_LOGD3DERROR("Could not get surface of the resolve texture", hr);
                URHO3D_SAFE_RELEASE(resolveSurface);
                return false;
            }
        }

        IDirect3DDevice9* device = graphics_->GetImpl_D3D9()->GetDevice();
        HRESULT hr = device->CreateOffscreenPlainSurface((UINT)width_, (UINT)height_, (D3DFORMAT)format_, D3DPOOL_SYSTEMMEM, &offscreenSurface, nullptr);
        if (FAILED(hr))
        {
            URHO3D_LOGD3DERROR("Could not create surface for getting rendertarget data", hr);
            URHO3D_SAFE_RELEASE(offscreenSurface);
            URHO3D_SAFE_RELEASE(resolveSurface);
            return false;
        }

        if (resolveSurface)
            hr = device->GetRenderTargetData(resolveSurface, offscreenSurface);
        else
            hr = device->GetRenderTargetData((IDirect3DSurface9*)renderSurfaces_[face]->GetSurface(), offscreenSurface);
        URHO3D_SAFE_RELEASE(resolveSurface);

        if (FAILED(hr))
        {
            URHO3D_LOGD3DERROR("Could not get rendertarget data", hr);
            URHO3D_SAFE_RELEASE(offscreenSurface);
            return false;
        }
        if (FAILED(offscreenSurface->LockRect(&d3dLockedRect, &d3dRect, D3DLOCK_READONLY)))
        {
            URHO3D_LOGD3DERROR("Could not lock surface for getting rendertarget data", hr);
            URHO3D_SAFE_RELEASE(offscreenSurface);
            return false;
        }
    }
    else
    {
        HRESULT hr = ((IDirect3DCubeTexture9*)object_.ptr_)->LockRect((D3DCUBEMAP_FACES)face, level, &d3dLockedRect, &d3dRect, D3DLOCK_READONLY);
        if (FAILED(hr))
        {
            URHO3D_LOGD3DERROR("Could not lock texture", hr);
            return false;
        }
    }

    int height = levelHeight;
    if (IsCompressed_D3D9())
        height = (height + 3) >> 2;

    unsigned char* destPtr = (unsigned char*)dest;
    unsigned rowSize = GetRowDataSize_D3D9(levelWidth);
    // GetRowDataSize_D3D9() returns CPU-side (destination) data size, so need to convert for X8R8G8B8
    if (format_ == D3DFMT_X8R8G8B8)
        rowSize = rowSize / 3 * 4;

    // Perform conversion to RGB / RGBA as necessary
    switch (format_)
    {
    default:
        for (int i = 0; i < height; ++i)
        {
            unsigned char* src = (unsigned char*)d3dLockedRect.pBits + i * d3dLockedRect.Pitch;
            memcpy(destPtr, src, rowSize);
            destPtr += rowSize;
        }
        break;

    case D3DFMT_X8R8G8B8:
        for (int i = 0; i < height; ++i)
        {
            unsigned char* src = (unsigned char*)d3dLockedRect.pBits + i * d3dLockedRect.Pitch;
            for (int j = 0; j < levelWidth; ++j)
            {
                destPtr[2] = *src++;
                destPtr[1] = *src++;
                destPtr[0] = *src++;
                ++src;
                destPtr += 3;
            }
        }
        break;

    case D3DFMT_A8R8G8B8:
        for (int i = 0; i < height; ++i)
        {
            unsigned char* src = (unsigned char*)d3dLockedRect.pBits + i * d3dLockedRect.Pitch;
            for (int j = 0; j < levelWidth; ++j)
            {
                destPtr[2] = *src++;
                destPtr[1] = *src++;
                destPtr[0] = *src++;
                destPtr[3] = *src++;
                destPtr += 4;
            }
        }
        break;
    }

    if (offscreenSurface)
        offscreenSurface->UnlockRect();
    else
        ((IDirect3DCubeTexture9*)object_.ptr_)->UnlockRect((D3DCUBEMAP_FACES)face, level);

    URHO3D_SAFE_RELEASE(offscreenSurface);
    return true;
}

bool TextureCube::Create_D3D9()
{
    Release_D3D9();

    if (!graphics_ || !width_ || !height_)
        return false;

    if (graphics_->IsDeviceLost())
    {
        URHO3D_LOGWARNING("Texture creation while device is lost");
        return true;
    }

    GraphicsImpl_D3D9* impl = graphics_->GetImpl_D3D9();

    unsigned pool = usage_ > TEXTURE_STATIC ? D3DPOOL_DEFAULT : D3DPOOL_MANAGED;
    unsigned d3dUsage = 0;

    switch (usage_)
    {
    case TEXTURE_DYNAMIC:
        d3dUsage |= D3DUSAGE_DYNAMIC;
        break;
    case TEXTURE_RENDERTARGET:
        d3dUsage |= D3DUSAGE_RENDERTARGET;
        if (requestedLevels_ != 1)
        {
            // Check mipmap autogeneration support
            if (impl->CheckFormatSupport((D3DFORMAT)format_, D3DUSAGE_AUTOGENMIPMAP, D3DRTYPE_TEXTURE))
            {
                requestedLevels_ = 0;
                d3dUsage |= D3DUSAGE_AUTOGENMIPMAP;
            }
            else
                requestedLevels_ = 1;
        }
        break;
    default:
        break;
    }

    if (multiSample_ > 1)
    {
        // Fall back to non-multisampled if unsupported multisampling mode
        GraphicsImpl_D3D9* impl = graphics_->GetImpl_D3D9();
        if (!impl->CheckMultiSampleSupport((D3DFORMAT)format_, multiSample_))
        {
            multiSample_ = 1;
            autoResolve_ = false;
        }
    }

    IDirect3DDevice9* device = graphics_->GetImpl_D3D9()->GetDevice();
    HRESULT hr = device->CreateCubeTexture(
        (UINT)width_,
        requestedLevels_,
        d3dUsage,
        (D3DFORMAT)format_,
        (D3DPOOL)pool,
        (IDirect3DCubeTexture9**)&object_.ptr_,
        nullptr);
    if (FAILED(hr))
    {
        URHO3D_LOGD3DERROR("Could not create cube texture", hr);
        URHO3D_SAFE_RELEASE(object_.ptr_);
        return false;
    }

    levels_ = ((IDirect3DCubeTexture9*)object_.ptr_)->GetLevelCount();

    if (usage_ == TEXTURE_RENDERTARGET)
    {
        for (unsigned i = 0; i < MAX_CUBEMAP_FACES; ++i)
        {
            if (multiSample_ > 1)
            {
                // Create the multisampled face rendertarget if necessary
                HRESULT hr = device->CreateRenderTarget(
                    (UINT)width_,
                    (UINT)height_,
                    (D3DFORMAT)format_,
                    (D3DMULTISAMPLE_TYPE)multiSample_,
                    0,
                    FALSE,
                    (IDirect3DSurface9**)&renderSurfaces_[i]->surface_,
                    nullptr);
                if (FAILED(hr))
                {
                    URHO3D_LOGD3DERROR("Could not create multisampled rendertarget surface", hr);
                    URHO3D_SAFE_RELEASE(renderSurfaces_[i]->surface_);
                    return false;
                }
            }
            else
            {
                hr = ((IDirect3DCubeTexture9*)object_.ptr_)->GetCubeMapSurface((D3DCUBEMAP_FACES)i, 0,
                    (IDirect3DSurface9**)&renderSurfaces_[i]->surface_);
                if (FAILED(hr))
                {
                    URHO3D_LOGD3DERROR("Could not get rendertarget surface", hr);
                    URHO3D_SAFE_RELEASE(renderSurfaces_[i]->surface_);
                    return false;
                }
            }
        }
    }

    return true;
}

}
