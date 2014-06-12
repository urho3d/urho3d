//
// Copyright (c) 2008-2014 the Urho3D project.
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
#include "GraphicsEvents.h"
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

namespace Urho3D
{

TextureCube::TextureCube(Context* context) :
    Texture(context)
{
    target_ = GL_TEXTURE_CUBE_MAP;
    
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

void TextureCube::OnDeviceLost()
{
    GPUObject::OnDeviceLost();
    
    for (unsigned i = 0; i < MAX_CUBEMAP_FACES; ++i)
    {
        if (renderSurfaces_[i])
            renderSurfaces_[i]->OnDeviceLost();
    }
}

void TextureCube::OnDeviceReset()
{
    if (!object_ || dataPending_)
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
        
        if (!graphics_->IsDeviceLost())
        {
            for (unsigned i = 0; i < MAX_TEXTURE_UNITS; ++i)
            {
                if (graphics_->GetTexture(i) == this)
                    graphics_->SetTexture(i, 0);
            }
            
            glDeleteTextures(1, &object_);
        }
        
        for (unsigned i = 0; i < MAX_CUBEMAP_FACES; ++i)
        {
            if (renderSurfaces_[i])
                renderSurfaces_[i]->Release();
        }
        
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
    
    usage_ = usage;
    
    if (usage == TEXTURE_RENDERTARGET)
    {
        for (unsigned i = 0; i < MAX_CUBEMAP_FACES; ++i)
        {
            renderSurfaces_[i] = new RenderSurface(this);
            renderSurfaces_[i]->SetTarget(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i);
        }
        
        // Nearest filtering and mipmaps disabled by default
        filterMode_ = FILTER_NEAREST;
        requestedLevels_ = 1;
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
    if (!object_ || !graphics_)
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
    
    graphics_->SetTextureForUpdate(this);
    
    bool wholeLevel = x == 0 && y == 0 && width == levelWidth && height == levelHeight;
    unsigned format = GetSRGB() ? GetSRGBFormat(format_) : format_;
    
    if (!IsCompressed())
    {
        if (wholeLevel)
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + face, level, format, width, height, 0, GetExternalFormat(format_),
                GetDataType(format_), data);
        else
            glTexSubImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + face, level, x, y, width, height, GetExternalFormat(format_),
                GetDataType(format_), data);
    }
    else
    {
        if (wholeLevel)
            glCompressedTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + face, level, format, width, height, 0,
                GetDataSize(width, height), data);
        else
            glCompressedTexSubImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + face, level, x, y, width, height, format,
                GetDataSize(width, height), data);
    }
    
    graphics_->SetTexture(0, 0);
    return true;
}

bool TextureCube::Load(Deserializer& source)
{
    PROFILE(LoadTextureCube);
    
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
        ++faces;
        
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
    #ifndef GL_ES_VERSION_2_0
    if (!object_ || !graphics_)
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
    
    graphics_->SetTextureForUpdate(const_cast<TextureCube*>(this));
    
    if (!IsCompressed())
        glGetTexImage(GL_TEXTURE_CUBE_MAP_POSITIVE_X + face, level, GetExternalFormat(format_), GetDataType(format_), dest);
    else
        glGetCompressedTexImage(GL_TEXTURE_CUBE_MAP_POSITIVE_X + face, level, dest);
    
    graphics_->SetTexture(0, 0);
    return true;
    #else
    LOGERROR("Getting texture data not supported");
    return false;
    #endif
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
    
    glGenTextures(1, &object_);
    
    // Ensure that our texture is bound to OpenGL texture unit 0
    graphics_->SetTextureForUpdate(this);
    
    // If not compressed, create the initial level 0 texture with null data
    unsigned format = GetSRGB() ? GetSRGBFormat(format_) : format_;
    unsigned externalFormat = GetExternalFormat(format_);
    unsigned dataType = GetDataType(format_);
    
    bool success = true;
    if (!IsCompressed())
    {
        glGetError();
        for (unsigned i = 0; i < MAX_CUBEMAP_FACES; ++i)
        {
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, format, width_, height_, 0, externalFormat, dataType, 0);
            if (glGetError())
                success = false;
        }
    }
    if (!success)
        LOGERROR("Failed to create texture");
    
    // Set mipmapping
    levels_ = requestedLevels_;
    if (!levels_)
    {
        unsigned maxSize = Max((int)width_, (int)height_);
        while (maxSize)
        {
            maxSize >>= 1;
            ++levels_;
        }
    }
    
    #ifndef GL_ES_VERSION_2_0
    glTexParameteri(target_, GL_TEXTURE_BASE_LEVEL, 0);
    glTexParameteri(target_, GL_TEXTURE_MAX_LEVEL, levels_ - 1);
    #endif
    
    // Set initial parameters, then unbind the texture
    UpdateParameters();
    graphics_->SetTexture(0, 0);
    
    return success;
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
