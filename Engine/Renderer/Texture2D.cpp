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
#include "Log.h"
#include "Profiler.h"
#include "Renderer.h"
#include "RendererImpl.h"
#include "ResourceCache.h"
#include "Texture2D.h"

#include "DebugNew.h"

Texture2D::Texture2D(Renderer* renderer, TextureUsage usage, const std::string& name) :
    Texture(renderer, name),
    mLockedLevel(-1),
    mFollowWindowSize(false)
{
    mUsage = 0;
    
    if ((usage == TEXTURE_RENDERTARGET) || (usage == TEXTURE_DEPTHSTENCIL))
    {
        mRenderSurface = new RenderSurface(this);
        if (usage == TEXTURE_RENDERTARGET)
            mUsage |= D3DUSAGE_RENDERTARGET;
        else
            mUsage |= D3DUSAGE_DEPTHSTENCIL;
        mPool = D3DPOOL_DEFAULT;
        
        // Clamp mode addressing by default, nearest filtering, and mipmaps disabled
        mAddressMode[COORD_U] = ADDRESS_CLAMP;
        mAddressMode[COORD_V] = ADDRESS_CLAMP;
        mFilterMode = FILTER_NEAREST;
        mRequestedLevels = 1;
    }
    else if (usage == TEXTURE_DYNAMIC)
    {
        mUsage |= D3DUSAGE_DYNAMIC;
        mPool = D3DPOOL_DEFAULT;
    }
    else
        mPool = D3DPOOL_MANAGED;
}

Texture2D::~Texture2D()
{
    release();
}

void Texture2D::load(Deserializer& source, ResourceCache* cache)
{
    if (!mRenderer)
        return;
    
    PROFILE(Texture2D_Load);
    
    // If over the texture budget, see if materials can be freed to allow textures to be freed
    checkTextureBudget(getTypeStatic(), cache);
    
    SharedPtr<Image> image(new Image());
    image->load(source, cache);
    
    // Before actually loading the texture, get optional parameters from an XML description file
    loadParameters(cache);
    
    load(image);
}

void Texture2D::onDeviceLost()
{
    if ((mPool == D3DPOOL_DEFAULT) || (mFollowWindowSize))
        release();
}

void Texture2D::onDeviceReset()
{
    if ((mPool == D3DPOOL_DEFAULT) || (mFollowWindowSize))
    {
        create();
        mDataLost = true;
    }
}

void Texture2D::setSize(int width, int height, unsigned format)
{
    if ((width <= 0) || (height <= 0))
        mFollowWindowSize = true;
    else
    {
        mWidth = width;
        mHeight = height;
        mFollowWindowSize = false;
    }
    
    mFormat = format;
    
    create();
}

void Texture2D::load(SharedPtr<Image> image)
{
    if (!image)
        EXCEPTION("Null image");
    
    unsigned memoryUse = 0;
    
    if (!image->isCompressed())
    {
        unsigned char* levelData = image->getData();
        int levelWidth = image->getWidth();
        int levelHeight = image->getHeight();
        unsigned components = image->getComponents();
        D3DFORMAT format = D3DFMT_UNKNOWN;
        
        // Discard unnecessary mip levels
        for (unsigned i = 0; i < mMipsToSkip[sQuality]; ++i)
        {
            image = image->getNextLevel();
            levelData = image->getData();
            levelWidth = image->getWidth();
            levelHeight = image->getHeight();
        }
        
        switch (components)
        {
            case 1:
            format = D3DFMT_L8;
            break;
            
            case 2:
            format = D3DFMT_A8L8;
            break;
            
            case 3:
            format = D3DFMT_X8R8G8B8;
            break;
            
            case 4:
            format = D3DFMT_A8R8G8B8;
            break;
        }
        
        setSize(levelWidth, levelHeight, format);
        // Make sure manual mip creation is never attempted for D3DPOOL_DEFAULT resources
        unsigned manualLevels = (mPool == D3DPOOL_DEFAULT) ? 1 : mLevels;
        
        for (unsigned i = 0; i < manualLevels; ++i)
        {
            D3DLOCKED_RECT hwRect;
            lock(i, 0, &hwRect);
            
            memoryUse += levelWidth * levelHeight * components;
            
            for (int y = 0; y < levelHeight; ++y)
            {
                unsigned char* dest = (unsigned char*)hwRect.pBits + hwRect.Pitch * y;
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
                image = image->getNextLevel();
                levelData = image->getData();
                levelWidth = image->getWidth();
                levelHeight = image->getHeight();
            }
            
            unlock();
        }
    }
    else
    {
        int width = image->getWidth();
        int height = image->getHeight();
        unsigned levels = image->getNumCompressedLevels();
        D3DFORMAT format = (D3DFORMAT)getCompressedD3DFormat(image->getCompressedFormat());
        
        unsigned mipsToSkip = mMipsToSkip[sQuality];
        if (mipsToSkip >= levels)
            mipsToSkip = levels - 1;
        while ((mipsToSkip) && ((width / (1 << mipsToSkip) < 4) || (height / (1 << mipsToSkip) < 4)))
            --mipsToSkip;
        width /= (1 << mipsToSkip);
        height /= (1 << mipsToSkip);
        
        setNumLevels(max((int)(levels - mipsToSkip), 1));
        setSize(width, height, format);
        
        for (unsigned i = 0; (i < mLevels) && (i < levels - mipsToSkip); ++i)
        {
            CompressedLevel level = image->getCompressedLevel(i + mipsToSkip);
            memoryUse += level.mRows * level.mRowSize;
            
            D3DLOCKED_RECT hwRect;
            lock(i, 0, &hwRect);
            
            for (unsigned j = 0; j < level.mRows; ++j)
            {
                unsigned char* dest = (unsigned char*)hwRect.pBits + hwRect.Pitch * j;
                unsigned char* src = level.mData + level.mRowSize * j;
                memcpy(dest, src, level.mRowSize);
            }
            
            unlock();
        }
    }
    
    setMemoryUse(memoryUse);
}

void Texture2D::lock(unsigned level, void* rect, void* hwRect)
{
    D3DLOCKED_RECT* lockedRect = (D3DLOCKED_RECT*)hwRect;
    if (!lockedRect)
        EXCEPTION("Null locked rect structure");
    
    if (!mObject)
        EXCEPTION("No texture created, can not lock");
    
    if (mLockedLevel != -1)
        EXCEPTION("Texture already locked");
    
    DWORD flags = 0;
    if ((!rect) && (mPool == D3DPOOL_DEFAULT))
        flags |= D3DLOCK_DISCARD;
    
    if (FAILED(((IDirect3DTexture9*)mObject)->LockRect(level, lockedRect, (RECT*)rect, flags)))
        EXCEPTION("Could not lock texture");
    
    mLockedLevel = level;
}

void Texture2D::unlock()
{
    if (mLockedLevel != -1)
    {
        ((IDirect3DTexture9*)mObject)->UnlockRect(mLockedLevel);
        mLockedLevel = -1;
    }
}

void Texture2D::create()
{
    release();
    
    if (!mRenderer)
        return;
    
    if (mFollowWindowSize)
    {
        mWidth = mRenderer->getWidth();
        mHeight = mRenderer->getHeight();
    }
    
    if ((!mWidth) || (!mHeight))
        return;
    
    // If using a default pool texture, must generate mipmaps automatically
    if ((mPool == D3DPOOL_DEFAULT) && (mRequestedLevels != 1))
        mUsage |= D3DUSAGE_AUTOGENMIPMAP;
    else
        mUsage &= ~D3DUSAGE_AUTOGENMIPMAP;
    
    // If creating a depth stencil texture, and it is not supported, create a depth stencil surface instead
    if ((mUsage & D3DUSAGE_DEPTHSTENCIL) && (!mRenderer->getImpl()->checkFormatSupport((D3DFORMAT)mFormat, mUsage, D3DRTYPE_TEXTURE)))
    {
        if (FAILED(mRenderer->getImpl()->getDevice()->CreateDepthStencilSurface(
            mWidth,
            mHeight,
            (D3DFORMAT)mFormat,
            D3DMULTISAMPLE_NONE,
            0,
            FALSE,
            (IDirect3DSurface9**)&mRenderSurface->mSurface,
            0)))
            EXCEPTION("Could not create depth stencil surface");
        
        mLevels = 1;
    }
    else
    {
        if (FAILED(mRenderer->getImpl()->getDevice()->CreateTexture(
            mWidth,
            mHeight,
            mRequestedLevels,
            mUsage,
            (D3DFORMAT)mFormat,
            (D3DPOOL)mPool,
            (IDirect3DTexture9**)&mObject,
            0)))
            EXCEPTION("Could not create texture");
        
        mLevels = ((IDirect3DTexture9*)mObject)->GetLevelCount();
        
        if (mUsage & (D3DUSAGE_RENDERTARGET | D3DUSAGE_DEPTHSTENCIL))
            ((IDirect3DTexture9*)mObject)->GetSurfaceLevel(0, (IDirect3DSurface9**)&mRenderSurface->mSurface);
    }
}

void Texture2D::release()
{
    if (mObject)
    {
        if (!mRenderer)
        {
            LOGWARNING("Renderer has expired, skipping release of Texture2D");
            return;
        }
        
        unlock();
        
        for (unsigned i = 0; i < MAX_TEXTURE_UNITS; ++i)
        {
            if (mRenderer->getTexture(i) == this)
                mRenderer->setTexture(i, 0);
        }
        
        if (mRenderSurface)
            mRenderSurface->release();
        
        ((IDirect3DTexture9*)mObject)->Release();
        mObject = 0;
    }
    else
    {
        if (mRenderSurface)
            mRenderSurface->release();
    }
}
