//
// Urho3D Engine
// Copyright (c) 2008-2012 Lasse Öörni
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
#include "FileSystem.h"
#include "Graphics.h"
#include "GraphicsImpl.h"
#include "Log.h"
#include "Profiler.h"
#include "Renderer.h"
#include "ResourceCache.h"
#include "TextureCube.h"
#include "XMLFile.h"

#include "DebugNew.h"

#ifdef _MSC_VER
#pragma warning(disable:4355)
#endif

OBJECTTYPESTATIC(TextureCube);

TextureCube::TextureCube(Context* context) :
    Texture(context),
    lockedLevel_(-1)
{
    for (unsigned i = 0; i < MAX_CUBEMAP_FACES; ++i)
        faceMemoryUse_[i] = 0;
}

TextureCube::~TextureCube()
{
    Release();
}

void TextureCube::RegisterObject(Context* context)
{
    context->RegisterFactory<TextureCube>();
}

void TextureCube::OnDeviceLost()
{
    if (pool_ == D3DPOOL_DEFAULT)
        Release();
}

void TextureCube::OnDeviceReset()
{
    if (pool_ == D3DPOOL_DEFAULT)
    {
        // If has a file name, reload through the resource cache. Otherwise just recreate.
        if (!GetName().Trimmed().Empty())
            dataLost_ = !GetSubsystem<ResourceCache>()->ReloadResource(this);
        else
        {
            Create();
            dataLost_ = true;
        }
    }
}

void TextureCube::Release()
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
        
        for (unsigned i = 0; i < MAX_CUBEMAP_FACES; ++i)
        {
            if (renderSurfaces_[i])
                renderSurfaces_[i]->Release();
        }
        
        ((IDirect3DCubeTexture9*)object_)->Release();
        object_ = 0;
    }
}

bool TextureCube::SetSize(int size, unsigned format, TextureUsage usage)
{
    if (size <= 0)
    {
        LOGERROR("Zero or negative cube texture size");
        return false;
    }
    if (usage == TEXTURE_DEPTHSTENCIL)
    {
        LOGERROR("Depth-stencil usage not supported for cube maps");
        return false;
    }
    
    // Delete the old rendersurfaces if any
    for (unsigned i = 0; i < MAX_CUBEMAP_FACES; ++i)
    {
        renderSurfaces_[i].Reset();
        faceMemoryUse_[i] = 0;
    }
    
    pool_ = D3DPOOL_MANAGED;
    usage_ = 0;
    
    if (usage == TEXTURE_RENDERTARGET)
    {
        for (unsigned i = 0; i < MAX_CUBEMAP_FACES; ++i)
            renderSurfaces_[i] = new RenderSurface(this);
        
        usage_ |= D3DUSAGE_RENDERTARGET;
        pool_ = D3DPOOL_DEFAULT;
        
        // Clamp mode addressing by default, nearest filtering, and mipmaps disabled
        addressMode_[COORD_U] = ADDRESS_CLAMP;
        addressMode_[COORD_V] = ADDRESS_CLAMP;
        addressMode_[COORD_W] = ADDRESS_CLAMP;
        filterMode_ = FILTER_NEAREST;
        requestedLevels_ = 1;
    }
    else if (usage == TEXTURE_DYNAMIC)
    {
        usage_ |= D3DUSAGE_DYNAMIC;
        pool_ = D3DPOOL_DEFAULT;
    }
    
    width_ = size;
    height_ = size;
    format_ = format;
    
    return Create();
}

bool TextureCube::SetData(CubeMapFace face, unsigned level, int x, int y, int width, int height, const void* data)
{
    if (!object_)
    {
        LOGERROR("No texture created, can not set data");
        return false;
    }
    
    if (!data)
    {
        LOGERROR("Null source for setting data");
        return false;
    }
    
    if (level >= levels_)
    {
        LOGERROR("Illegal mip level for setting data");
        return false;
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
        LOGERROR("Illegal dimensions for setting data");
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
    
    if (FAILED(((IDirect3DCubeTexture9*)object_)->LockRect((D3DCUBEMAP_FACES)face, level, &d3dLockedRect, (flags &
        D3DLOCK_DISCARD) ? 0 : &d3dRect, flags)))
    {
        LOGERROR("Could not lock texture");
        return false;
    }
    
    if (IsCompressed())
    {
        height = (height + 3) >> 2;
        y >>= 2;
    }
    
    unsigned char* src = (unsigned char*)data;
    unsigned rowSize = GetRowDataSize(width);
    unsigned rowOffset = GetRowDataSize(x);
    // GetRowDataSize() returns CPU-side (source) data size, so need to convert for X8R8G8B8
    if (format_ == D3DFMT_X8R8G8B8)
    {
        rowSize = rowSize / 3 * 4;
        rowOffset = rowOffset / 3 * 4;
    }
    
    // Perform conversion from RGB / RGBA as necessary
    switch (format_)
    {
    default:
        for (int i = 0; i < height; ++i)
        {
            unsigned char* dest = (unsigned char*)d3dLockedRect.pBits + (y + i) * d3dLockedRect.Pitch + rowOffset;
            memcpy(dest, src, rowSize);
            src += rowSize;
        }
        break;
    
    case D3DFMT_X8R8G8B8:
        for (int i = 0; i < height; ++i)
        {
            unsigned char* dest = (unsigned char*)d3dLockedRect.pBits + (y + i) * d3dLockedRect.Pitch + rowOffset;
            for (int j = 0; j < width; ++j)
            {
                *dest++  = src[2]; *dest++ = src[1]; *dest++ = src[0]; *dest++ = 255;
                src += 3;
           }
        }
        break;
        
    case D3DFMT_A8R8G8B8:
        for (int i = 0; i < height; ++i)
        {
            unsigned char* dest = (unsigned char*)d3dLockedRect.pBits + (y + i) * d3dLockedRect.Pitch + rowOffset;
            for (int j = 0; j < width; ++j)
            {
                *dest++  = src[2]; *dest++ = src[1]; *dest++ = src[0]; *dest++ = src[3];
                src += 4;
           }
        }
        break;
    }
    
    ((IDirect3DCubeTexture9*)object_)->UnlockRect((D3DCUBEMAP_FACES)face, level);
    return true;
}

bool TextureCube::Load(Deserializer& source)
{
    PROFILE(LoadTextureCube);
    
    ResourceCache* cache = GetSubsystem<ResourceCache>();
    
    // In headless mode, do not actually load the texture, just return success
    Graphics* graphics = GetSubsystem<Graphics>();
    if (!graphics)
        return true;
    
    // If over the texture budget, see if materials can be freed to allow textures to be freed
    CheckTextureBudget(GetTypeStatic());
    
    String texPath, texName, texExt;
    SplitPath(GetName(), texPath, texName, texExt);
    
    SharedPtr<XMLFile> xml(new XMLFile(context_));
    if (!xml->Load(source))
        return false;
    
    LoadParameters(xml);
    
    XMLElement textureElem = xml->GetRoot();
    XMLElement faceElem = textureElem.GetChild("face");
    unsigned faces = 0;
    while (faceElem && faces < MAX_CUBEMAP_FACES)
    {
        String name = faceElem.GetAttribute("name");
        
        String faceTexPath, faceTexName, faceTexExt;
        SplitPath(name, faceTexPath, faceTexName, faceTexExt);
        // If path is empty, add the XML file path
        if (faceTexPath.Empty())
            name = texPath + name;
        
        SharedPtr<Image> image(cache->GetResource<Image>(name));
        Load((CubeMapFace)faces, image);
        faces++;
        
        faceElem = faceElem.GetNext("face");
    }
    
    return true;
}

bool TextureCube::Load(CubeMapFace face, Deserializer& source)
{
    PROFILE(LoadTextureCube);
    
    SharedPtr<Image> image(new Image(context_));
    if (!image->Load(source))
        return false;
    
    return Load(face, image);
}

bool TextureCube::Load(CubeMapFace face, SharedPtr<Image> image, bool useAlpha)
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
        
        if (levelWidth != levelHeight)
        {
            LOGERROR("Cube texture width not equal to height");
            return false;
        }
        
        // Discard unnecessary mip levels
        for (unsigned i = 0; i < mipsToSkip_[quality]; ++i)
        {
            image = image->GetNextLevel();
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
        
        // Create the texture when face 0 is being loaded, check that rest of the faces are same size & format
        if (!face)
            SetSize(levelWidth, format);
        else
        {
            if (!object_)
            {
                LOGERROR("Cube texture face 0 must be loaded first");
                return false;
            }
            if (levelWidth != width_ || format != format_)
            {
                LOGERROR("Cube texture face does not match size or format of face 0");
                return false;
            }
        }
        
        for (unsigned i = 0; i < levels_; ++i)
        {
            SetData(face, i, 0, 0, levelWidth, levelHeight, levelData);
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
        unsigned format = GetDXTFormat(image->GetCompressedFormat());
        
        if (width != height)
        {
            LOGERROR("Cube texture width not equal to height");
            return false;
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
            SetNumLevels(Max((int)(levels - mipsToSkip), 1));
            SetSize(width, format);
        }
        else
        {
            if (!object_)
            {
                LOGERROR("Cube texture face 0 must be loaded first");
                return false;
            }
            if (width != width_ || format != format_)
            {
                LOGERROR("Cube texture face does not match size or format of face 0");
                return false;
            }
        }
        
        for (unsigned i = 0; i < levels_ && i < levels - mipsToSkip; ++i)
        {
            CompressedLevel level = image->GetCompressedLevel(i + mipsToSkip);
            SetData(face, i, 0, 0, level.width_, level.height_, level.data_);
            memoryUse += level.rows_ * level.rowSize_;
        }
    }
    
    faceMemoryUse_[face] = memoryUse;
    unsigned totalMemoryUse = sizeof(TextureCube);
    for (unsigned i = 0; i < MAX_CUBEMAP_FACES; ++i)
        totalMemoryUse += faceMemoryUse_[i];
    SetMemoryUse(totalMemoryUse);
    
    return true;
}

bool TextureCube::GetData(CubeMapFace face, unsigned level, void* dest) const
{
    if (!object_)
    {
        LOGERROR("No texture created, can not get data");
        return false;
    }
    
    if (!dest)
    {
        LOGERROR("Null destination for getting data");
        return false;
    }
    
    if (level >= levels_)
    {
        LOGERROR("Illegal mip level for getting data");
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
    
    if (FAILED(((IDirect3DCubeTexture9*)object_)->LockRect((D3DCUBEMAP_FACES)face, level, &d3dLockedRect, &d3dRect, D3DLOCK_READONLY)))
    {
        LOGERROR("Could not lock texture");
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
                destPtr[2] = *src++; destPtr[1] = *src++; destPtr[0] = *src++; ++src;
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
                destPtr[2] = *src++; destPtr[1] = *src++; destPtr[0] = *src++; destPtr[3] = *src++;
                destPtr += 4;
           }
        }
        break;
    }
    
    ((IDirect3DCubeTexture9*)object_)->UnlockRect((D3DCUBEMAP_FACES)face, level);
    return true;
}

bool TextureCube::Create()
{
    Release();
    
    if (!graphics_)
        return false;
    
    if (!width_ || !height_)
        return false;
    
    IDirect3DDevice9* device = graphics_->GetImpl()->GetDevice();
    if (!device || FAILED(device->CreateCubeTexture(
        width_,
        requestedLevels_,
        usage_,
        (D3DFORMAT)format_,
        (D3DPOOL)pool_,
        (IDirect3DCubeTexture9**)&object_,
        0)))
    {
        LOGERROR("Could not create cube texture");
        return false;
    }
    
    levels_ = ((IDirect3DCubeTexture9*)object_)->GetLevelCount();
    
    if (usage_ & D3DUSAGE_RENDERTARGET)
    {
        for (unsigned i = 0; i < MAX_CUBEMAP_FACES; ++i)
        {
            ((IDirect3DCubeTexture9*)object_)->GetCubeMapSurface((D3DCUBEMAP_FACES)i, 0,
                (IDirect3DSurface9**)&renderSurfaces_[i]->surface_);
        }
    }
    
    return true;
}
