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
#include "../../Core/Profiler.h"
#include "../../Graphics/Renderer.h"
#include "../../Resource/ResourceCache.h"
#include "../../Graphics/TextureCube.h"
#include "../../Resource/XMLFile.h"

#include "../../DebugNew.h"

#ifdef _MSC_VER
#pragma warning(disable:4355)
#endif

namespace Urho3D
{

static const char* cubeMapLayoutNames[] = {
    "horizontal",
    "horizontalnvidia",
    "horizontalcross",
    "verticalcross",
    "blender",
    0
};

static SharedPtr<Image> GetTileImage(Image* src, int tileX, int tileY, int tileWidth, int tileHeight)
{
    return SharedPtr<Image>(src->GetSubimage(IntRect(tileX * tileWidth, tileY * tileHeight, (tileX + 1) * tileWidth, (tileY + 1) * tileHeight)));
}

TextureCube::TextureCube(Context* context) :
    Texture(context),
    lockedLevel_(-1)
{
    // Default to clamp mode addressing
    addressMode_[COORD_U] = ADDRESS_CLAMP;
    addressMode_[COORD_V] = ADDRESS_CLAMP;
    addressMode_[COORD_W] = ADDRESS_CLAMP;
    
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

bool TextureCube::BeginLoad(Deserializer& source)
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
    
    cache->ResetDependencies(this);

    String texPath, texName, texExt;
    SplitPath(GetName(), texPath, texName, texExt);
    
    loadParameters_ = (new XMLFile(context_));
    if (!loadParameters_->Load(source))
    {
        loadParameters_.Reset();
        return false;
    }
    
    loadImages_.Clear();

    XMLElement textureElem = loadParameters_->GetRoot();
    XMLElement imageElem = textureElem.GetChild("image");
    // Single image and multiple faces with layout
    if (imageElem)
    {
        String name = imageElem.GetAttribute("name");
        // If path is empty, add the XML file path
        if (GetPath(name).Empty())
            name = texPath + name;
        
        CubeMapLayout layout = (CubeMapLayout)GetStringListIndex(imageElem.GetAttribute("layout").CString(), cubeMapLayoutNames, CML_HORIZONTAL);
        SharedPtr<Image> image = cache->GetTempResource<Image>(name);
        if (!image)
            return false;
        
        int faceWidth, faceHeight;
        loadImages_.Resize(MAX_CUBEMAP_FACES);
        
        switch (layout)
        {
        case CML_HORIZONTAL:
            faceWidth = image->GetWidth() / MAX_CUBEMAP_FACES;
            faceHeight = image->GetHeight();
            loadImages_[FACE_POSITIVE_Z] = GetTileImage(image, 0, 0, faceWidth, faceHeight);
            loadImages_[FACE_POSITIVE_X] = GetTileImage(image, 1, 0, faceWidth, faceHeight);
            loadImages_[FACE_NEGATIVE_Z] = GetTileImage(image, 2, 0, faceWidth, faceHeight);
            loadImages_[FACE_NEGATIVE_X] = GetTileImage(image, 3, 0, faceWidth, faceHeight);
            loadImages_[FACE_POSITIVE_Y] = GetTileImage(image, 4, 0, faceWidth, faceHeight);
            loadImages_[FACE_NEGATIVE_Y] = GetTileImage(image, 5, 0, faceWidth, faceHeight);
            break;
            
        case CML_HORIZONTALNVIDIA:
            faceWidth = image->GetWidth() / MAX_CUBEMAP_FACES;
            faceHeight = image->GetHeight();
            for (unsigned i = 0; i < MAX_CUBEMAP_FACES; ++i)
                loadImages_[i] = GetTileImage(image, i, 0, faceWidth, faceHeight);
            break;
            
        case CML_HORIZONTALCROSS:
            faceWidth = image->GetWidth() / 4;
            faceHeight = image->GetHeight() / 3;
            loadImages_[FACE_POSITIVE_Y] = GetTileImage(image, 1, 0, faceWidth, faceHeight);
            loadImages_[FACE_NEGATIVE_X] = GetTileImage(image, 0, 1, faceWidth, faceHeight);
            loadImages_[FACE_POSITIVE_Z] = GetTileImage(image, 1, 1, faceWidth, faceHeight);
            loadImages_[FACE_POSITIVE_X] = GetTileImage(image, 2, 1, faceWidth, faceHeight);
            loadImages_[FACE_NEGATIVE_Z] = GetTileImage(image, 3, 1, faceWidth, faceHeight);
            loadImages_[FACE_NEGATIVE_Y] = GetTileImage(image, 1, 2, faceWidth, faceHeight);
            break;
            
        case CML_VERTICALCROSS:
            faceWidth = image->GetWidth() / 3;
            faceHeight = image->GetHeight() / 4;
            loadImages_[FACE_POSITIVE_Y] = GetTileImage(image, 1, 0, faceWidth, faceHeight);
            loadImages_[FACE_NEGATIVE_X] = GetTileImage(image, 0, 1, faceWidth, faceHeight);
            loadImages_[FACE_POSITIVE_Z] = GetTileImage(image, 1, 1, faceWidth, faceHeight);
            loadImages_[FACE_POSITIVE_X] = GetTileImage(image, 2, 1, faceWidth, faceHeight);
            loadImages_[FACE_NEGATIVE_Y] = GetTileImage(image, 1, 2, faceWidth, faceHeight);
            loadImages_[FACE_NEGATIVE_Z] = GetTileImage(image, 1, 3, faceWidth, faceHeight);
            if (loadImages_[FACE_NEGATIVE_Z])
            {
                loadImages_[FACE_NEGATIVE_Z]->FlipVertical();
                loadImages_[FACE_NEGATIVE_Z]->FlipHorizontal();
            }
            break;
            
        case CML_BLENDER:
            faceWidth = image->GetWidth() / 3;
            faceHeight = image->GetHeight() / 2;
            loadImages_[FACE_NEGATIVE_X] = GetTileImage(image, 0, 0, faceWidth, faceHeight);
            loadImages_[FACE_NEGATIVE_Z] = GetTileImage(image, 1, 0, faceWidth, faceHeight);
            loadImages_[FACE_POSITIVE_X] = GetTileImage(image, 2, 0, faceWidth, faceHeight);
            loadImages_[FACE_NEGATIVE_Y] = GetTileImage(image, 0, 1, faceWidth, faceHeight);
            loadImages_[FACE_POSITIVE_Y] = GetTileImage(image, 1, 1, faceWidth, faceHeight);
            loadImages_[FACE_POSITIVE_Z] = GetTileImage(image, 2, 1, faceWidth, faceHeight);
            break;
        }
    }
    // Face per image
    else
    {
        XMLElement faceElem = textureElem.GetChild("face");
        while (faceElem)
        {
            String name = faceElem.GetAttribute("name");
            
            // If path is empty, add the XML file path
            if (GetPath(name).Empty())
                name = texPath + name;
            
            loadImages_.Push(cache->GetTempResource<Image>(name));
            cache->StoreResourceDependency(this, name);
            
            faceElem = faceElem.GetNext("face");
        }
    }

    // Precalculate mip levels if async loading
    if (GetAsyncLoadState() == ASYNC_LOADING)
    {
        for (unsigned i = 0; i < loadImages_.Size(); ++i)
        {
            if (loadImages_[i])
                loadImages_[i]->PrecalculateLevels();
        }
    }

    return true;
}

bool TextureCube::EndLoad()
{
    // In headless mode, do not actually load the texture, just return success
    if (!graphics_ || graphics_->IsDeviceLost())
        return true;
    
    // If over the texture budget, see if materials can be freed to allow textures to be freed
    CheckTextureBudget(GetTypeStatic());

    SetParameters(loadParameters_);
    
    for (unsigned i = 0; i < loadImages_.Size() && i < MAX_CUBEMAP_FACES; ++i)
        SetData((CubeMapFace)i, loadImages_[i]);
    
    loadImages_.Clear();
    loadParameters_.Reset();
    
    return true;
}

void TextureCube::OnDeviceLost()
{
    if (pool_ == D3DPOOL_DEFAULT)
        Release();
}

void TextureCube::OnDeviceReset()
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
        
        // Nearest filtering and mipmaps disabled by default
        filterMode_ = FILTER_NEAREST;
        requestedLevels_ = 1;
    }
    else if (usage == TEXTURE_DYNAMIC)
    {
        usage_ |= D3DUSAGE_DYNAMIC;
        pool_ = D3DPOOL_DEFAULT;
    }
    
    if (usage == TEXTURE_RENDERTARGET)
        SubscribeToEvent(E_RENDERSURFACEUPDATE, HANDLER(TextureCube, HandleRenderSurfaceUpdate));
    else
        UnsubscribeFromEvent(E_RENDERSURFACEUPDATE);
    
    width_ = size;
    height_ = size;
    format_ = format;
    
    return Create();
}

bool TextureCube::SetData(CubeMapFace face, unsigned level, int x, int y, int width, int height, const void* data)
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
                *dest++  = src[2]; *dest++ = src[1]; *dest++ = src[0]; *dest++ = 255;
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
                *dest++  = src[2]; *dest++ = src[1]; *dest++ = src[0]; *dest++ = src[3];
                src += 4;
           }
        }
        break;
    }
    
    ((IDirect3DCubeTexture9*)object_)->UnlockRect((D3DCUBEMAP_FACES)face, level);
    return true;
}

bool TextureCube::SetData(CubeMapFace face, Deserializer& source)
{
    SharedPtr<Image> image(new Image(context_));
    if (!image->Load(source))
        return false;
    
    return SetData(face, image);
}

bool TextureCube::SetData(CubeMapFace face, SharedPtr<Image> image, bool useAlpha)
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
        
        // Create the texture when face 0 is being loaded, check that rest of the faces are same size & format
        if (!face)
        {
            // If image was previously compressed, reset number of requested levels to avoid error if level count is too high for new size
            if (IsCompressed() && requestedLevels_ > 1)
                requestedLevels_ = 0;
            SetSize(levelWidth, format);
        }
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
        unsigned format = graphics_->GetFormat(image->GetCompressedFormat());
        bool needDecompress = false;
        
        if (width != height)
        {
            LOGERROR("Cube texture width not equal to height");
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
            if (!needDecompress)
            {
                SetData(face, i, 0, 0, level.width_, level.height_, level.data_);
                memoryUse += level.rows_ * level.rowSize_;
            }
            else
            {
                unsigned char* rgbaData = new unsigned char[level.width_ * level.height_ * 4];
                level.Decompress(rgbaData);
                SetData(face, i, 0, 0, level.width_, level.height_, rgbaData);
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
    
    if (graphics_->IsDeviceLost())
    {
        LOGWARNING("Getting texture data while device is lost");
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
    
    if (!graphics_ || !width_ || !height_)
        return false;
    
    if (graphics_->IsDeviceLost())
    {
        LOGWARNING("Texture creation while device is lost");
        return true;
    }
    
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

void TextureCube::HandleRenderSurfaceUpdate(StringHash eventType, VariantMap& eventData)
{
    for (unsigned i = 0; i < MAX_CUBEMAP_FACES; ++i)
    {
        if (renderSurfaces_[i] && renderSurfaces_[i]->GetUpdateMode() == SURFACE_UPDATEALWAYS)
            renderSurfaces_[i]->QueueUpdate();
    }
}

}
