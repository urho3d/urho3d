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
#include "StringUtils.h"
#include "TextureCube.h"
#include "XMLFile.h"

#include "DebugNew.h"

#ifdef _MSC_VER
#pragma warning(disable:4355)
#endif

TextureCube::TextureCube(Renderer* renderer, TextureUsage usage, const std::string& name) :
    Texture(renderer, name),
    mLockedLevel(-1)
{
    mUsage = 0;
    
    for (unsigned i = 0; i < MAX_CUBEMAP_FACES; ++i)
        mFaceMemoryUse[i] = 0;
    
    if (usage == TEXTURE_DEPTHSTENCIL)
        EXCEPTION("Depth stencil usage not supported for cube maps");
    
    if (usage == TEXTURE_RENDERTARGET)
    {
        for (unsigned i = 0; i < MAX_CUBEMAP_FACES; ++i)
            mRenderSurfaces[i] = new RenderSurface(this);
        
        mUsage |= D3DUSAGE_RENDERTARGET;
        mPool = D3DPOOL_DEFAULT;
        
        // Clamp mode addressing by default, nearest filtering, and mipmaps disabled
        mAddressMode[COORD_U] = ADDRESS_CLAMP;
        mAddressMode[COORD_V] = ADDRESS_CLAMP;
        mAddressMode[COORD_W] = ADDRESS_CLAMP;
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

TextureCube::~TextureCube()
{
    release();
}

void TextureCube::onDeviceLost()
{
    if (mPool == D3DPOOL_DEFAULT)
        release();
}

void TextureCube::onDeviceReset()
{
    if (mPool == D3DPOOL_DEFAULT)
    {
        create();
        mDataLost = true;
    }
}

void TextureCube::setSize(int size, unsigned format)
{
    if (size <= 0)
        EXCEPTION("Zero or negative cube texture size");
    
    mWidth = size;
    mHeight = size;
    mFormat = format;
    
    create();
}

void TextureCube::load(Deserializer& source, ResourceCache* cache)
{
    if ((!mRenderer) || (!cache))
        return;
    
    PROFILE(TextureCube_Load);
    
    // If over the texture budget, see if materials can be freed to allow textures to be freed
    checkTextureBudget(getTypeStatic(), cache);
    
    std::string texPath;
    std::string texName;
    std::string texExt;
    splitPath(getName(), texPath, texName, texExt);
    
    XMLFile xml;
    xml.load(source, cache);
    
    loadParameters(&xml);
    
    XMLElement textureElem = xml.getRootElement();
    XMLElement faceElem = textureElem.getChildElement("face");
    unsigned faces = 0;
    while ((faceElem) && (faces < MAX_CUBEMAP_FACES))
    {
        std::string name = faceElem.getString("name");
        std::string faceTexPath;
        std::string faceTexName;
        std::string faceTexExt;
        splitPath(name, faceTexPath, faceTexName, faceTexExt);
        // If path is empty, add the XML file path
        if (faceTexPath.empty())
            name = texPath + name;
        
        SharedPtr<Image> image(cache->getResource<Image>(name));
        load((CubeMapFace)faces, image);
        faces++;
        
        faceElem = faceElem.getNextElement("face");
    }
}

void TextureCube::load(CubeMapFace face, Deserializer& source)
{
    PROFILE(TextureCube_Load);
    
    SharedPtr<Image> image(new Image());
    image->load(source);
    
    load(face, image);
}

void TextureCube::load(CubeMapFace face, SharedPtr<Image> image)
{
    unsigned memoryUse = 0;
    
    if (!image->isCompressed())
    {
        unsigned char* levelData = image->getData();
        int levelWidth = image->getWidth();
        int levelHeight = image->getHeight();
        unsigned components = image->getComponents();
        D3DFORMAT format = D3DFMT_UNKNOWN;
        
        if (levelWidth != levelHeight)
            EXCEPTION("Cube texture width not equal to height");
        
        // Discard unnecessary mip levels
        for (unsigned i = 0; i < mMipsToSkip[sQuality]; ++i)
        {
            image = image->getNextLevel();
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
        
        // Create the texture when face 0 is being loaded, check that rest of the faces are same size & format
        if (!face)
            setSize(levelWidth, format);
        else
        {
            if (!mObject)
                EXCEPTION("Cube texture face 0 must be loaded first");
            if ((levelWidth != mWidth) || (format != mFormat))
                EXCEPTION("Cube texture face does not match size or format of face 0");
        }
        
        // Make sure manual mip creation is never attempted for D3DPOOL_DEFAULT resources
        unsigned manualLevels = (mPool == D3DPOOL_DEFAULT) ? 1 : mLevels;
        
        for (unsigned i = 0; i < manualLevels; ++i)
        {
            D3DLOCKED_RECT hwRect;
            lock(face, i, 0, &hwRect);
            
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
        
        if (width != height)
            EXCEPTION("Cube texture width not equal to height");
        
        unsigned mipsToSkip = mMipsToSkip[sQuality];
        if (mipsToSkip >= levels)
            mipsToSkip = levels - 1;
        while ((mipsToSkip) && ((width / (1 << mipsToSkip) < 4) || (height / (1 << mipsToSkip) < 4)))
            --mipsToSkip;
        width /= (1 << mipsToSkip);
        height /= (1 << mipsToSkip);
        
        // Create the texture when face 0 is being loaded, assume rest of the faces are same size & format
        if (!face)
        {
            setNumLevels(max((int)(levels - mipsToSkip), 1));
            setSize(width, format);
        }
        else
        {
            if (!mObject)
                EXCEPTION("Cube texture face 0 must be loaded first");
            if ((width != mWidth) || (format != mFormat))
                EXCEPTION("Cube texture face does not match size or format of face 0");
        }
        
        for (unsigned i = 0; (i < mLevels) && (i < levels - mipsToSkip); ++i)
        {
            CompressedLevel level = image->getCompressedLevel(i + mipsToSkip);
            memoryUse += level.mRows * level.mRowSize;
            
            D3DLOCKED_RECT hwRect;
            lock(face, i, 0, &hwRect);
            
            for (unsigned j = 0; j < level.mRows; ++j)
            {
                unsigned char* dest = (unsigned char*)hwRect.pBits + hwRect.Pitch * j;
                unsigned char* src = level.mData + level.mRowSize * j;
                memcpy(dest, src, level.mRowSize);
            }
            
            unlock();
        }
    }
    
    mFaceMemoryUse[face] = memoryUse;
    unsigned totalMemoryUse = 0;
    for (unsigned i = 0; i < MAX_CUBEMAP_FACES; ++i)
        totalMemoryUse += mFaceMemoryUse[i];
    setMemoryUse(totalMemoryUse);
}

void TextureCube::lock(CubeMapFace face, unsigned level, void* rect, void* hwRect)
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
    
    if (FAILED(((IDirect3DCubeTexture9*)mObject)->LockRect((D3DCUBEMAP_FACES)face, level, lockedRect, (RECT*)rect, flags)))
        EXCEPTION("Could not lock texture");
    
    mLockedLevel = level;
    mLockedFace = face;
}

void TextureCube::unlock()
{
    if (mLockedLevel != -1)
    {
        ((IDirect3DCubeTexture9*)mObject)->UnlockRect((D3DCUBEMAP_FACES)mLockedFace, mLockedLevel);
        mLockedLevel = -1;
    }
}

void TextureCube::create()
{
    release();
    
    if (!mRenderer)
        return;
    
    if ((!mWidth) || (!mHeight))
        return;
    
    // If using a default pool texture, must generate mipmaps automatically
    if ((mPool == D3DPOOL_DEFAULT) && (mRequestedLevels != 1))
        mUsage |= D3DUSAGE_AUTOGENMIPMAP;
    else
        mUsage &= ~D3DUSAGE_AUTOGENMIPMAP;
    
    if (FAILED(mRenderer->getImpl()->getDevice()->CreateCubeTexture(
        mWidth,
        mRequestedLevels,
        mUsage,
        (D3DFORMAT)mFormat,
        (D3DPOOL)mPool,
        (IDirect3DCubeTexture9**)&mObject,
        0)))
        EXCEPTION("Could not create cube texture");
    
    mLevels = ((IDirect3DCubeTexture9*)mObject)->GetLevelCount();
    
    if (mUsage & D3DUSAGE_RENDERTARGET)
    {
        for (unsigned i = 0; i < MAX_CUBEMAP_FACES; ++i)
            ((IDirect3DCubeTexture9*)mObject)->GetCubeMapSurface((D3DCUBEMAP_FACES)i, 0, (IDirect3DSurface9**)&mRenderSurfaces[i]->mSurface);
    }
}

void TextureCube::release()
{
    if (mObject)
    {
        if (!mRenderer)
        {
            LOGWARNING("Renderer has expired, skipping release of TextureCube");
            return;
        }
        
        unlock();
        
        for (unsigned i = 0; i < MAX_TEXTURE_UNITS; ++i)
        {
            if (mRenderer->getTexture(i) == this)
                mRenderer->setTexture(i, 0);
        }
        
        for (unsigned i = 0; i < MAX_CUBEMAP_FACES; ++i)
        {
            if (mRenderSurfaces[i])
                mRenderSurfaces[i]->release();
        }
        
        ((IDirect3DCubeTexture9*)mObject)->Release();
        mObject = 0;
    }
}
