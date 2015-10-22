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

Texture2D::Texture2D(Context* context) :
    Texture(context)
{
}

Texture2D::~Texture2D()
{
    Release();
}

void Texture2D::RegisterObject(Context* context)
{
    context->RegisterFactory<Texture2D>();
}

bool Texture2D::BeginLoad(Deserializer& source)
{
    // In headless mode, do not actually load the texture, just return success
    if (!graphics_)
        return true;

    // If device is lost, retry later
    if (graphics_->IsDeviceLost())
    {
        URHO3D_LOGWARNING("Texture load while device is lost");
        dataPending_ = true;
        return true;
    }

    // Load the image data for EndLoad()
    loadImage_ = new Image(context_);
    if (!loadImage_->Load(source))
    {
        loadImage_.Reset();
        return false;
    }

    // Precalculate mip levels if async loading
    if (GetAsyncLoadState() == ASYNC_LOADING)
        loadImage_->PrecalculateLevels();

    // Load the optional parameters file
    ResourceCache* cache = GetSubsystem<ResourceCache>();
    String xmlName = ReplaceExtension(GetName(), ".xml");
    loadParameters_ = cache->GetTempResource<XMLFile>(xmlName, false);

    return true;
}

bool Texture2D::EndLoad()
{
    // In headless mode, do not actually load the texture, just return success
    if (!graphics_ || graphics_->IsDeviceLost())
        return true;

    // If over the texture budget, see if materials can be freed to allow textures to be freed
    CheckTextureBudget(GetTypeStatic());

    SetParameters(loadParameters_);
    bool success = SetData(loadImage_);

    loadImage_.Reset();
    loadParameters_.Reset();

    return success;
}

void Texture2D::OnDeviceLost()
{
    if (pool_ == D3DPOOL_DEFAULT)
        Release();
}

void Texture2D::OnDeviceReset()
{
    if (pool_ == D3DPOOL_DEFAULT || !object_ || dataPending_)
    {
        // If has a resource file, reload through the resource cache. Otherwise just recreate.
        ResourceCache* cache = GetSubsystem<ResourceCache>();
        if (cache->Exists(GetName()))
            dataLost_ = !cache->ReloadResource(this);

        if (!object_)
        {
            Create();
            dataLost_ = true;
        }
    }

    dataPending_ = false;
}

void Texture2D::Release()
{
    if (object_)
    {
        if (!graphics_)
            return;

        for (unsigned i = 0; i < MAX_TEXTURE_UNITS; ++i)
        {
            if (graphics_->GetTexture(i) == this)
                graphics_->SetTexture(i, 0);
        }

        if (renderSurface_)
            renderSurface_->Release();

        ((IDirect3DTexture9*)object_)->Release();
        object_ = 0;
    }
    else
    {
        if (renderSurface_)
            renderSurface_->Release();
    }
}

bool Texture2D::SetSize(int width, int height, unsigned format, TextureUsage usage)
{
    // Delete the old rendersurface if any
    renderSurface_.Reset();
    pool_ = D3DPOOL_MANAGED;
    usage_ = 0;

    if (usage == TEXTURE_RENDERTARGET || usage == TEXTURE_DEPTHSTENCIL)
    {
        renderSurface_ = new RenderSurface(this);
        if (usage == TEXTURE_RENDERTARGET)
            usage_ |= D3DUSAGE_RENDERTARGET;
        else
            usage_ |= D3DUSAGE_DEPTHSTENCIL;
        pool_ = D3DPOOL_DEFAULT;

        // Clamp mode addressing by default, nearest filtering, and mipmaps disabled
        addressMode_[COORD_U] = ADDRESS_CLAMP;
        addressMode_[COORD_V] = ADDRESS_CLAMP;
        filterMode_ = FILTER_NEAREST;
        requestedLevels_ = 1;
    }
    else if (usage == TEXTURE_DYNAMIC)
    {
        usage_ |= D3DUSAGE_DYNAMIC;
        pool_ = D3DPOOL_DEFAULT;
    }

    if (usage == TEXTURE_RENDERTARGET)
        SubscribeToEvent(E_RENDERSURFACEUPDATE, URHO3D_HANDLER(Texture2D, HandleRenderSurfaceUpdate));
    else
        UnsubscribeFromEvent(E_RENDERSURFACEUPDATE);

    width_ = width;
    height_ = height;
    format_ = format;

    return Create();
}

bool Texture2D::SetData(unsigned level, int x, int y, int width, int height, const void* data)
{
    URHO3D_PROFILE(SetTextureData);

    if (!object_)
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
    if (level == 0 && x == 0 && y == 0 && width == levelWidth && height == levelHeight && pool_ == D3DPOOL_DEFAULT)
        flags |= D3DLOCK_DISCARD;

    if (FAILED(((IDirect3DTexture9*)object_)->LockRect(level, &d3dLockedRect, (flags & D3DLOCK_DISCARD) ? 0 : &d3dRect, flags)))
    {
        URHO3D_LOGERROR("Could not lock texture");
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

    ((IDirect3DTexture9*)object_)->UnlockRect(level);
    return true;
}

bool Texture2D::SetData(SharedPtr<Image> image, bool useAlpha)
{
    if (!image)
    {
        URHO3D_LOGERROR("Null image, can not load texture");
        return false;
    }

    unsigned memoryUse = sizeof(Texture2D);

    int quality = QUALITY_HIGH;
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
            image = image->GetNextLevel();
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
                image = image->GetNextLevel();
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

        SetNumLevels((unsigned)Max((int)(levels - mipsToSkip), 1));
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
    if (!object_)
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

    D3DLOCKED_RECT d3dLockedRect;
    RECT d3dRect;
    d3dRect.left = 0;
    d3dRect.top = 0;
    d3dRect.right = levelWidth;
    d3dRect.bottom = levelHeight;

    IDirect3DSurface9* offscreenSurface = 0;
    // Need to use a offscreen surface & GetRenderTargetData() for rendertargets
    if (renderSurface_)
    {
        if (level != 0)
        {
            URHO3D_LOGERROR("Can only get mip level 0 data from a rendertarget");
            return false;
        }

        IDirect3DDevice9* device = graphics_->GetImpl()->GetDevice();
        device->CreateOffscreenPlainSurface((UINT)width_, (UINT)height_, (D3DFORMAT)format_,
            D3DPOOL_SYSTEMMEM, &offscreenSurface, 0);
        if (!offscreenSurface)
        {
            URHO3D_LOGERROR("Could not create surface for getting rendertarget data");
            return false;
        }
        device->GetRenderTargetData((IDirect3DSurface9*)renderSurface_->GetSurface(), offscreenSurface);
        if (FAILED(offscreenSurface->LockRect(&d3dLockedRect, &d3dRect, D3DLOCK_READONLY)))
        {
            URHO3D_LOGERROR("Could not lock surface for getting rendertarget data");
            offscreenSurface->Release();
            return false;
        }
    }
    else
    {
        if (FAILED(((IDirect3DTexture9*)object_)->LockRect(level, &d3dLockedRect, &d3dRect, D3DLOCK_READONLY)))
        {
            URHO3D_LOGERROR("Could not lock texture");
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
    {
        offscreenSurface->UnlockRect();
        offscreenSurface->Release();
    }
    else
        ((IDirect3DTexture9*)object_)->UnlockRect(level);

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

    IDirect3DDevice9* device = graphics_->GetImpl()->GetDevice();
    // If creating a depth-stencil texture, and it is not supported, create a depth-stencil surface instead
    if (usage_ & D3DUSAGE_DEPTHSTENCIL && !graphics_->GetImpl()->CheckFormatSupport((D3DFORMAT)format_, usage_, D3DRTYPE_TEXTURE))
    {
        if (!device || FAILED(device->CreateDepthStencilSurface(
            (UINT)width_,
            (UINT)height_,
            (D3DFORMAT)format_,
            D3DMULTISAMPLE_NONE,
            0,
            FALSE,
            (IDirect3DSurface9**)&renderSurface_->surface_,
            0)))
        {
            URHO3D_LOGERROR("Could not create depth-stencil surface");
            return false;
        }

        levels_ = 1;
    }
    else
    {
        if (!device || FAILED(graphics_->GetImpl()->GetDevice()->CreateTexture(
            (UINT)width_,
            (UINT)height_,
            requestedLevels_,
            usage_,
            (D3DFORMAT)format_,
            (D3DPOOL)pool_,
            (IDirect3DTexture9**)&object_,
            0)))
        {
            URHO3D_LOGERROR("Could not create texture");
            return false;
        }

        levels_ = ((IDirect3DTexture9*)object_)->GetLevelCount();

        if (usage_ & (D3DUSAGE_RENDERTARGET | D3DUSAGE_DEPTHSTENCIL))
            ((IDirect3DTexture9*)object_)->GetSurfaceLevel(0, (IDirect3DSurface9**)&renderSurface_->surface_);
    }

    return true;
}

void Texture2D::HandleRenderSurfaceUpdate(StringHash eventType, VariantMap& eventData)
{
    if (renderSurface_ && renderSurface_->GetUpdateMode() == SURFACE_UPDATEALWAYS)
        renderSurface_->QueueUpdate();
}

}
