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
#include "../../Graphics/Texture2D.h"
#include "../../IO/Log.h"
#include "../../IO/FileSystem.h"
#include "../../Resource/ResourceCache.h"
#include "../../Resource/XMLFile.h"

#include "../../DebugNew.h"

namespace Urho3D
{

void Texture2D::OnDeviceLost()
{
    if (usage_ > TEXTURE_STATIC)
        Release();
}

void Texture2D::OnDeviceReset()
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

void Texture2D::Release()
{
    if (graphics_)
    {
        for (unsigned i = 0; i < MAX_TEXTURE_UNITS; ++i)
        {
            if (graphics_->GetTexture(i) == this)
                graphics_->SetTexture(i, nullptr);
        }
    }

    if (renderSurface_)
        renderSurface_->Release();

    URHO3D_SAFE_RELEASE(object_.ptr_);

    resolveDirty_ = false;
    levelsDirty_ = false;
}

bool Texture2D::SetData(unsigned level, int x, int y, int width, int height, const void* data)
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

    HRESULT hr = ((IDirect3DTexture9*)object_.ptr_)->LockRect(level, &d3dLockedRect, (flags & D3DLOCK_DISCARD) ? nullptr : &d3dRect, flags);
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

    ((IDirect3DTexture9*)object_.ptr_)->UnlockRect(level);
    return true;
}

bool Texture2D::SetData(Image* image, bool useAlpha)
{
    if (!image)
    {
        URHO3D_LOGERROR("Null image, can not load texture");
        return false;
    }

    // Use a shared ptr for managing the temporary mip images created during this function
    SharedPtr<Image> mipImage;
    unsigned memoryUse = sizeof(Texture2D);
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

        // If image was previously compressed, reset number of requested levels to avoid error if level count is too high for new size
        if (IsCompressed() && requestedLevels_ > 1)
            requestedLevels_ = 0;
        SetSize(levelWidth, levelHeight, format);

        for (unsigned i = 0; i < levels_; ++i)
        {
            SetData(i, 0, 0, levelWidth, levelHeight, levelData);
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

        SetNumLevels(Max((levels - mipsToSkip), 1U));
        SetSize(width, height, format);

        for (unsigned i = 0; i < levels_ && i < levels - mipsToSkip; ++i)
        {
            CompressedLevel level = image->GetCompressedLevel(i + mipsToSkip);
            if (!needDecompress)
            {
                SetData(i, 0, 0, level.width_, level.height_, level.data_);
                memoryUse += level.rows_ * level.rowSize_;
            }
            else
            {
                unsigned char* rgbaData = new unsigned char[level.width_ * level.height_ * 4];
                level.Decompress(rgbaData);
                SetData(i, 0, 0, level.width_, level.height_, rgbaData);
                memoryUse += level.width_ * level.height_ * 4;
                delete[] rgbaData;
            }
        }
    }

    SetMemoryUse(memoryUse);
    return true;
}

bool Texture2D::GetData(unsigned level, void* dest) const
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
        graphics_->ResolveToTexture(const_cast<Texture2D*>(this));

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
    if (renderSurface_)
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
            HRESULT hr = ((IDirect3DTexture9*)object_.ptr_)->GetSurfaceLevel(0, (IDirect3DSurface9**)&resolveSurface);
            if (FAILED(hr))
            {
                URHO3D_LOGD3DERROR("Could not get surface of the resolve texture", hr);
                URHO3D_SAFE_RELEASE(resolveSurface);
                return false;
            }
        }

        IDirect3DDevice9* device = graphics_->GetImpl()->GetDevice();
        HRESULT hr = device->CreateOffscreenPlainSurface((UINT)width_, (UINT)height_, (D3DFORMAT)format_,
            D3DPOOL_SYSTEMMEM, &offscreenSurface, nullptr);
        if (FAILED(hr))
        {
            URHO3D_LOGD3DERROR("Could not create surface for getting rendertarget data", hr);
            URHO3D_SAFE_RELEASE(offscreenSurface)
            URHO3D_SAFE_RELEASE(resolveSurface);
            return false;
        }
        
        if (resolveSurface)
            hr = device->GetRenderTargetData(resolveSurface, offscreenSurface);
        else
            hr = device->GetRenderTargetData((IDirect3DSurface9*)renderSurface_->GetSurface(), offscreenSurface);
        URHO3D_SAFE_RELEASE(resolveSurface);

        if (FAILED(hr))
        {
            URHO3D_LOGD3DERROR("Could not get rendertarget data", hr);
            URHO3D_SAFE_RELEASE(offscreenSurface);
            return false;
        }

        hr = offscreenSurface->LockRect(&d3dLockedRect, &d3dRect, D3DLOCK_READONLY);
        if (FAILED(hr))
        {
            URHO3D_LOGD3DERROR("Could not lock surface for getting rendertarget data", hr);
            URHO3D_SAFE_RELEASE(offscreenSurface);
            return false;
        }
    }
    else
    {
        HRESULT hr = ((IDirect3DTexture9*)object_.ptr_)->LockRect(level, &d3dLockedRect, &d3dRect, D3DLOCK_READONLY);
        if (FAILED(hr))
        {
            URHO3D_LOGD3DERROR("Could not lock texture", hr);
            return false;
        }
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
        ((IDirect3DTexture9*)object_.ptr_)->UnlockRect(level);

    URHO3D_SAFE_RELEASE(offscreenSurface);
    return true;
}

bool Texture2D::Create()
{
    Release();

    if (!graphics_ || !width_ || !height_)
        return false;

    if (graphics_->IsDeviceLost())
    {
        URHO3D_LOGWARNING("Texture creation while device is lost");
        return true;
    }

    if (multiSample_ > 1 && !autoResolve_)
    {
        URHO3D_LOGWARNING("Multisampled texture without autoresolve is not supported on Direct3D9");
        autoResolve_ = true;
    }

    GraphicsImpl* impl = graphics_->GetImpl();

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
    case TEXTURE_DEPTHSTENCIL:
        d3dUsage |= D3DUSAGE_DEPTHSTENCIL;
        // No mipmaps for depth-stencil textures
        requestedLevels_ = 1;
        break;
    default:
        break;
    }

    if (multiSample_ > 1)
    {
        // Fall back to non-multisampled if unsupported multisampling mode
        if (!impl->CheckMultiSampleSupport((D3DFORMAT)format_,  multiSample_))
        {
            multiSample_ = 1;
            autoResolve_ = false;
        }
    }

    IDirect3DDevice9* device = graphics_->GetImpl()->GetDevice();
    // If creating a depth-stencil texture, and it is not supported, create a depth-stencil surface instead
    // Multisampled surfaces need also to be created this way
    if (usage_ == TEXTURE_DEPTHSTENCIL && (multiSample_ > 1 || !graphics_->GetImpl()->CheckFormatSupport((D3DFORMAT)format_, 
        d3dUsage, D3DRTYPE_TEXTURE)))
    {
        HRESULT hr = device->CreateDepthStencilSurface(
            (UINT)width_,
            (UINT)height_,
            (D3DFORMAT)format_,
            (multiSample_ > 1) ? (D3DMULTISAMPLE_TYPE)multiSample_ : D3DMULTISAMPLE_NONE,
            0,
            FALSE,
            (IDirect3DSurface9**)&renderSurface_->surface_,
            nullptr);
        if (FAILED(hr))
        {
            URHO3D_LOGD3DERROR("Could not create depth-stencil surface", hr);
            URHO3D_SAFE_RELEASE(renderSurface_->surface_);
            return false;
        }

        levels_ = 1;
    }
    else
    {
        HRESULT hr = graphics_->GetImpl()->GetDevice()->CreateTexture(
            (UINT)width_,
            (UINT)height_,
            requestedLevels_,
            d3dUsage,
            (D3DFORMAT)format_,
            (D3DPOOL)pool,
            (IDirect3DTexture9**)&object_,
            nullptr);
        if (FAILED(hr))
        {
            URHO3D_LOGD3DERROR("Could not create texture", hr);
            URHO3D_SAFE_RELEASE(object_.ptr_);
            return false;
        }

        levels_ = ((IDirect3DTexture9*)object_.ptr_)->GetLevelCount();

        // Create the multisampled rendertarget for rendering to if necessary
        if (usage_ == TEXTURE_RENDERTARGET && multiSample_ > 1)
        {
            HRESULT hr = device->CreateRenderTarget(
                (UINT)width_,
                (UINT)height_,
                (D3DFORMAT)format_,
                (D3DMULTISAMPLE_TYPE)multiSample_,
                0,
                FALSE,
                (IDirect3DSurface9**)&renderSurface_->surface_,
                nullptr);
            if (FAILED(hr))
            {
                URHO3D_LOGD3DERROR("Could not create multisampled rendertarget surface", hr);
                URHO3D_SAFE_RELEASE(renderSurface_->surface_);
                return false;
            }
        }
        else if (usage_ >= TEXTURE_RENDERTARGET)
        {
            // Else use the texture surface directly for rendering
            hr = ((IDirect3DTexture9*)object_.ptr_)->GetSurfaceLevel(0, (IDirect3DSurface9**)&renderSurface_->surface_);
            if (FAILED(hr))
            {
                URHO3D_LOGD3DERROR("Could not get rendertarget surface", hr);
                URHO3D_SAFE_RELEASE(renderSurface_->surface_);
                return false;
            }
        }
    }

    return true;
}

}
