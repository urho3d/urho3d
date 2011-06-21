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
#include "Graphics.h"
#include "GraphicsImpl.h"
#include "Log.h"
#include "Renderer.h"
#include "Profiler.h"
#include "ResourceCache.h"
#include "Texture2D.h"

#include "DebugNew.h"

OBJECTTYPESTATIC(Texture2D);

Texture2D::Texture2D(Context* context) :
    Texture(context),
    lockedLevel_(-1),
    followWindowSize_(false)
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

bool Texture2D::Load(Deserializer& source)
{
    PROFILE(LoadTexture2D);
    
    if (!graphics_)
        return false;
    
    // If over the texture budget, see if materials can be freed to allow textures to be freed
    CheckTextureBudget(GetTypeStatic());
    
    SharedPtr<Image> image(new Image(context_));
    if (!image->Load(source))
        return false;
    
    // Before actually loading the texture, get optional parameters from an XML description file
    LoadParameters();
    
    return Load(image);
}

void Texture2D::OnDeviceLost()
{
    if (pool_ == D3DPOOL_DEFAULT || followWindowSize_)
        Release();
}

void Texture2D::OnDeviceReset()
{
    if (pool_ == D3DPOOL_DEFAULT || followWindowSize_)
    {
        Create();
        dataLost_ = true;
    }
}

void Texture2D::Release()
{
    if (object_)
    {
        if (!graphics_)
            return;
        
        Unlock();
        
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
    
    if (width <= 0 || height <= 0)
        followWindowSize_ = true;
    else
    {
        width_ = width;
        height_ = height;
        followWindowSize_ = false;
    }
    
    format_ = format;
    
    return Create();
}

bool Texture2D::Load(SharedPtr<Image> image, bool useAlpha)
{
    if (!image)
    {
        LOGERROR("Null image, can not load texture");
        return false;
    }
    
    unsigned memoryUse = 0;
    
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
        }
        
        SetSize(levelWidth, levelHeight, format);
        // Make sure manual mip creation is never attempted for D3DPOOL_DEFAULT resources
        unsigned manualLevels = (pool_ == D3DPOOL_DEFAULT) ? 1 : levels_;
        
        for (unsigned i = 0; i < manualLevels; ++i)
        {
            LockedRect hwRect;
            if (!Lock(i, 0, hwRect))
                return false;
            
            memoryUse += levelWidth * levelHeight * components;
            
            for (int y = 0; y < levelHeight; ++y)
            {
                unsigned char* dest = hwRect.bits_ + hwRect.pitch_ * y;
                unsigned char* src = levelData + components * levelWidth * y;
                
                switch (components)
                {
                case 1:
                case 2:
                    memcpy(dest, src, components * levelWidth);
                    break;
                
                case 3:
                    for (int x = 0; x < levelWidth; ++x)
                    {
                        *dest++ = src[2]; *dest++ = src[1]; *dest++ = src[0]; *dest++ = 255;
                        src += 3;
                    }
                    break;
                
                case 4:
                    for (int x = 0; x < levelWidth; ++x)
                    {
                        *dest++ = src[2]; *dest++ = src[1]; *dest++ = src[0]; *dest++ = src[3];
                        src += 4;
                    }
                    break;
                }
            }
            
            if (i < manualLevels - 1)
            {
                image = image->GetNextLevel();
                levelData = image->GetData();
                levelWidth = image->GetWidth();
                levelHeight = image->GetHeight();
            }
            
            Unlock();
        }
    }
    else
    {
        int width = image->GetWidth();
        int height = image->GetHeight();
        unsigned levels = image->GetNumCompressedLevels();
        unsigned format = GetDXTFormat(image->GetCompressedFormat());
        
        unsigned mipsToSkip = mipsToSkip_[quality];
        if (mipsToSkip >= levels)
            mipsToSkip = levels - 1;
        while (mipsToSkip && (width / (1 << mipsToSkip) < 4 || height / (1 << mipsToSkip) < 4))
            --mipsToSkip;
        width /= (1 << mipsToSkip);
        height /= (1 << mipsToSkip);
        
        SetNumLevels(Max((int)(levels - mipsToSkip), 1));
        SetSize(width, height, format);
        
        for (unsigned i = 0; i < levels_ && i < levels - mipsToSkip; ++i)
        {
            CompressedLevel level = image->GetCompressedLevel(i + mipsToSkip);
            memoryUse += level.rows_ * level.rowSize_;
            
            LockedRect hwRect;
            if (!Lock(i, 0, hwRect))
                return false;
            
            for (unsigned j = 0; j < level.rows_; ++j)
            {
                unsigned char* dest = hwRect.bits_ + hwRect.pitch_ * j;
                unsigned char* src = level.data_ + level.rowSize_ * j;
                memcpy(dest, src, level.rowSize_);
            }
            
            Unlock();
        }
    }
    
    SetMemoryUse(memoryUse);
    return true;
}

bool Texture2D::Lock(unsigned level, const IntRect* rect, LockedRect& lockedRect)
{
    if (!object_)
    {
        LOGERROR("No texture created, can not lock");
        return false;
    }
    
    if (lockedLevel_ != -1)
    {
        LOGERROR("Texture already locked");
        return false;
    }
    
    D3DLOCKED_RECT d3dLockedRect;
    RECT d3dRect;
    if (rect)
    {
        d3dRect.left = rect->left_;
        d3dRect.top = rect->top_;
        d3dRect.right = rect->right_;
        d3dRect.bottom = rect->bottom_;
    }
    
    DWORD flags = 0;
    if (!rect && pool_ == D3DPOOL_DEFAULT)
        flags |= D3DLOCK_DISCARD;
    
    if (FAILED(((IDirect3DTexture9*)object_)->LockRect(level, &d3dLockedRect, rect ? &d3dRect : 0, flags)))
    {
        LOGERROR("Could not lock texture");
        return false;
    }
    
    lockedRect.bits_ = (unsigned char*)d3dLockedRect.pBits;
    lockedRect.pitch_ = d3dLockedRect.Pitch;
    lockedLevel_ = level;
    return true;
}

void Texture2D::Unlock()
{
    if (lockedLevel_ != -1)
    {
        ((IDirect3DTexture9*)object_)->UnlockRect(lockedLevel_);
        lockedLevel_ = -1;
    }
}

bool Texture2D::Create()
{
    Release();
    
    if (!graphics_)
        return false;
    
    if (followWindowSize_)
    {
        width_ = graphics_->GetWidth();
        height_ = graphics_->GetHeight();
    }
    
    if (!width_ || !height_)
        return false;
    
    // If using a default pool texture, must generate mipmaps automatically
    if (pool_ == D3DPOOL_DEFAULT && requestedLevels_ != 1)
        usage_ |= D3DUSAGE_AUTOGENMIPMAP;
    else
        usage_ &= ~D3DUSAGE_AUTOGENMIPMAP;
    
    IDirect3DDevice9* device = graphics_->GetImpl()->GetDevice();
    // If creating a depth stencil texture, and it is not supported, create a depth stencil surface instead
    if (usage_ & D3DUSAGE_DEPTHSTENCIL && !graphics_->GetImpl()->CheckFormatSupport((D3DFORMAT)format_, usage_, D3DRTYPE_TEXTURE))
    {
        if (!device || FAILED(device->CreateDepthStencilSurface(
            width_,
            height_,
            (D3DFORMAT)format_,
            D3DMULTISAMPLE_NONE,
            0,
            FALSE,
            (IDirect3DSurface9**)&renderSurface_->surface_,
            0)))
        {
            LOGERROR("Could not create depth stencil surface");
            return false;
        }
        
        levels_ = 1;
    }
    else
    {
        if (!device || FAILED(graphics_->GetImpl()->GetDevice()->CreateTexture(
            width_,
            height_,
            requestedLevels_,
            usage_,
            (D3DFORMAT)format_,
            (D3DPOOL)pool_,
            (IDirect3DTexture9**)&object_,
            0)))
        {
            LOGERROR("Could not create texture");
            return false;
        }
        
        levels_ = ((IDirect3DTexture9*)object_)->GetLevelCount();
        
        if (usage_ & (D3DUSAGE_RENDERTARGET | D3DUSAGE_DEPTHSTENCIL))
            ((IDirect3DTexture9*)object_)->GetSurfaceLevel(0, (IDirect3DSurface9**)&renderSurface_->surface_);
    }
    
    return true;
}
