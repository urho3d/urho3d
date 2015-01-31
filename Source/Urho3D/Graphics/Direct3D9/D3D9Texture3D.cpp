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

#include "../../Core/Context.h"
#include "../../IO/FileSystem.h"
#include "../../Graphics/Graphics.h"
#include "../../Graphics/GraphicsEvents.h"
#include "../../Graphics/GraphicsImpl.h"
#include "../../IO/Log.h"
#include "../../Graphics/Renderer.h"
#include "../../Core/Profiler.h"
#include "../../Resource/ResourceCache.h"
#include "../../Graphics/Texture3D.h"
#include "../../Resource/XMLFile.h"

#include "../../DebugNew.h"

namespace Urho3D
{

Texture3D::Texture3D(Context* context) :
    Texture(context)
{
}

Texture3D::~Texture3D()
{
    Release();
}

void Texture3D::RegisterObject(Context* context)
{
    context->RegisterFactory<Texture3D>();
}

bool Texture3D::BeginLoad(Deserializer& source)
{
    ResourceCache* cache = GetSubsystem<ResourceCache>();

    // In headless mode, do not actually load the texture, just return success
    if (!graphics_)
        return true;
    
    // If device is lost, retry later
    if (graphics_->IsDeviceLost())
    {
        LOGWARNING("Texture load while device is lost");
        dataPending_ = true;
        return true;
    }
    
    String texPath, texName, texExt;
    SplitPath(GetName(), texPath, texName, texExt);
    
    cache->ResetDependencies(this);

    loadParameters_ = new XMLFile(context_);
    if (!loadParameters_->Load(source))
    {
        loadParameters_.Reset();
        return false;
    }
    
    XMLElement textureElem = loadParameters_->GetRoot();
    XMLElement volumeElem = textureElem.GetChild("volume");
    XMLElement colorlutElem = textureElem.GetChild("colorlut");

    if (volumeElem)
    {
        String name = volumeElem.GetAttribute("name");
        
        String volumeTexPath, volumeTexName, volumeTexExt;
        SplitPath(name, volumeTexPath, volumeTexName, volumeTexExt);
        // If path is empty, add the XML file path
        if (volumeTexPath.Empty())
            name = texPath + name;

        loadImage_ = cache->GetTempResource<Image>(name);
        // Precalculate mip levels if async loading
        if (loadImage_ && GetAsyncLoadState() == ASYNC_LOADING)
            loadImage_->PrecalculateLevels();
        cache->StoreResourceDependency(this, name);
        return true;
    }
    else if (colorlutElem)
    {
        String name = colorlutElem.GetAttribute("name");
        
        String colorlutTexPath, colorlutTexName, colorlutTexExt;
        SplitPath(name, colorlutTexPath, colorlutTexName, colorlutTexExt);
        // If path is empty, add the XML file path
        if (colorlutTexPath.Empty())
            name = texPath + name;

        SharedPtr<File> file = GetSubsystem<ResourceCache>()->GetFile(name);
        loadImage_ = new Image(context_);
        if (!loadImage_->LoadColorLUT(*(file.Get())))
        {
            loadParameters_.Reset();
            loadImage_.Reset();
            return false;
        }
        // Precalculate mip levels if async loading
        if (loadImage_ && GetAsyncLoadState() == ASYNC_LOADING)
            loadImage_->PrecalculateLevels();
        cache->StoreResourceDependency(this, name);
        return true;
    }

    LOGERROR("Texture3D XML data for " + GetName() + " did not contain either volume or colorlut element");
    return false;
}

bool Texture3D::EndLoad()
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

void Texture3D::OnDeviceLost()
{
    if (pool_ == D3DPOOL_DEFAULT)
        Release();
}

void Texture3D::OnDeviceReset()
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

void Texture3D::Release()
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
        
        ((IDirect3DVolumeTexture9*)object_)->Release();
        object_ = 0;
    }
    else
    {
        if (renderSurface_)
            renderSurface_->Release();
    }
}

bool Texture3D::SetSize(int width, int height, int depth, unsigned format, TextureUsage usage)
{
    // Delete the old rendersurface if any
    renderSurface_.Reset();
    pool_ = D3DPOOL_MANAGED;
    usage_ = 0;
    
    if (usage == TEXTURE_RENDERTARGET)
    {
        renderSurface_ = new RenderSurface(this);
        usage_ |= D3DUSAGE_RENDERTARGET;
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
        SubscribeToEvent(E_RENDERSURFACEUPDATE, HANDLER(Texture3D, HandleRenderSurfaceUpdate));
    else
        UnsubscribeFromEvent(E_RENDERSURFACEUPDATE);

    width_ = width;
    height_ = height;
    depth_ = depth;
    format_ = format;
    
    return Create();
}

bool Texture3D::SetData(unsigned level, int x, int y, int z, int width, int height, int depth, const void* data)
{
    PROFILE(SetTextureData);
    
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
    
    if (graphics_->IsDeviceLost())
    {
        LOGWARNING("Texture data assignment while device is lost");
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
    if (x < 0 || x + width > levelWidth || y < 0 || y + height > levelHeight || z < 0 || z + depth > levelDepth || width <= 0 || height <= 0 || depth <= 0)
    {
        LOGERROR("Illegal dimensions for setting data");
        return false;
    }
    
    D3DLOCKED_BOX d3dLockedBox;
    D3DBOX d3dBox;
    d3dBox.Left = x;
    d3dBox.Top = y;
    d3dBox.Front = z;
    d3dBox.Right = x + width;
    d3dBox.Bottom = y + height;
    d3dBox.Back = z + depth;
    
    DWORD flags = 0;
    if (level == 0 && x == 0 && y == 0 && z == 0 && width == levelWidth && height == levelHeight && depth == levelDepth && pool_ == D3DPOOL_DEFAULT)
        flags |= D3DLOCK_DISCARD;
    
    if (FAILED(((IDirect3DVolumeTexture9*)object_)->LockBox(level, &d3dLockedBox, (flags & D3DLOCK_DISCARD) ? 0 : &d3dBox, flags)))
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
                unsigned char* dest = (unsigned char*)d3dLockedBox.pBits + (k * d3dLockedBox.SlicePitch) + i * d3dLockedBox.RowPitch;
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
                unsigned char* dest = (unsigned char*)d3dLockedBox.pBits + (k * d3dLockedBox.SlicePitch) + i * d3dLockedBox.RowPitch;
                for (int j = 0; j < width; ++j)
                {
                    *dest++  = src[2]; *dest++ = src[1]; *dest++ = src[0]; *dest++ = 255;
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
                unsigned char* dest = (unsigned char*)d3dLockedBox.pBits + (k * d3dLockedBox.SlicePitch) + i * d3dLockedBox.RowPitch;
                for (int j = 0; j < width; ++j)
                {
                    *dest++  = src[2]; *dest++ = src[1]; *dest++ = src[0]; *dest++ = src[3];
                    src += 4;
                }
            }
        }
        break;
    }
    
    ((IDirect3DVolumeTexture9*)object_)->UnlockBox(level);
    return true;
}

bool Texture3D::SetData(SharedPtr<Image> image, bool useAlpha)
{
    if (!image)
    {
        LOGERROR("Null image, can not load texture");
        return false;
    }
    
    unsigned memoryUse = sizeof(Texture3D);
    
    int quality = QUALITY_HIGH;
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
            image = image->GetNextLevel();
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
                image = image->GetNextLevel();
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
        
        SetNumLevels(Max((int)(levels - mipsToSkip), 1));
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
    
    if (graphics_->IsDeviceLost())
    {
        LOGWARNING("Getting texture data while device is lost");
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
    d3dBox.Right = levelWidth;
    d3dBox.Bottom = levelHeight;
    d3dBox.Back = levelDepth;
    
    if (FAILED(((IDirect3DVolumeTexture9*)object_)->LockBox(level, &d3dLockedBox, &d3dBox, D3DLOCK_READONLY)))
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
                    destPtr[2] = *src++; destPtr[1] = *src++; destPtr[0] = *src++; ++src;
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
                    destPtr[2] = *src++; destPtr[1] = *src++; destPtr[0] = *src++; destPtr[3] = *src++;
                    destPtr += 4;
               }
            }
        }
        break;
    }
    
    ((IDirect3DVolumeTexture9*)object_)->UnlockBox(level);
    return true;
}

bool Texture3D::Create()
{
    Release();
    
    if (!graphics_ || !width_ || !height_)
        return false;
    
    if (graphics_->IsDeviceLost())
    {
        LOGWARNING("Texture creation while device is lost");
        return true;
    }
    
    IDirect3DDevice9* device = graphics_->GetImpl()->GetDevice();

    if (!device || FAILED(graphics_->GetImpl()->GetDevice()->CreateVolumeTexture(
        width_,
        height_,
        depth_,
        requestedLevels_,
        usage_,
        (D3DFORMAT)format_,
        (D3DPOOL)pool_,
        (IDirect3DVolumeTexture9**)&object_,
        0)))
    {
        LOGERROR("Could not create texture");
        return false;
    }
    
    levels_ = ((IDirect3DVolumeTexture9*)object_)->GetLevelCount();
    
    return true;
}

void Texture3D::HandleRenderSurfaceUpdate(StringHash eventType, VariantMap& eventData)
{
    if (renderSurface_ && renderSurface_->GetUpdateMode() == SURFACE_UPDATEALWAYS)
        renderSurface_->QueueUpdate();
}

}
