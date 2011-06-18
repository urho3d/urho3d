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
    Texture(context)
{
    target_ = GL_TEXTURE_CUBE_MAP;
    
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

void TextureCube::OnDeviceReset()
{
    if (!object_)
    {
        // Reload from the original file if possible
        ResourceCache* cache = GetSubsystem<ResourceCache>();
        const String& name = GetName();
        if ((cache) && (!name.Empty()) && (cache->Exists(name)))
            cache->ReloadResource(this);
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
        
        glDeleteTextures(1, &object_);
        object_ = 0;
        dataLost_ = true;
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
        LOGERROR("Depth stencil usage not supported for cube maps");
        return false;
    }
    
    // Delete the old rendersurfaces if any
    for (unsigned i = 0; i < MAX_CUBEMAP_FACES; ++i)
    {
        renderSurfaces_[i].Reset();
        faceMemoryUse_[i] = 0;
    }
    
    if (usage == TEXTURE_RENDERTARGET)
    {
        for (unsigned i = 0; i < MAX_CUBEMAP_FACES; ++i)
            renderSurfaces_[i] = new RenderSurface(this, GL_TEXTURE_CUBE_MAP_POSITIVE_X + i);
        
        // Clamp mode addressing by default, nearest filtering, and mipmaps disabled
        addressMode_[COORD_U] = ADDRESS_CLAMP;
        addressMode_[COORD_V] = ADDRESS_CLAMP;
        addressMode_[COORD_W] = ADDRESS_CLAMP;
        filterMode_ = FILTER_NEAREST;
        requestedLevels_ = 1;
        dynamic_ = true;
    }
    else if (usage == TEXTURE_DYNAMIC)
        dynamic_ = true;
    else
        dynamic_ = false;
    
    width_ = size;
    height_ = size;
    format_ = format;
    
    return Create();
}

bool TextureCube::Load(Deserializer& source)
{
    PROFILE(LoadTextureCube);
    
    ResourceCache* cache = GetSubsystem<ResourceCache>();
    
    if (!graphics_)
        return false;
    
    // If over the texture budget, see if materials can be freed to allow textures to be freed
    CheckTextureBudget(GetTypeStatic());
    
    String texPath, texName, texExt;
    SplitPath(GetName(), texPath, texName, texExt);
    
    SharedPtr<XMLFile> xml(new XMLFile(context_));
    if (!xml->Load(source))
        return false;
    
    LoadParameters(xml);
    
    XMLElement textureElem = xml->GetRootElement();
    XMLElement faceElem = textureElem.GetChildElement("face");
    unsigned faces = 0;
    while ((faceElem) && (faces < MAX_CUBEMAP_FACES))
    {
        String name = faceElem.GetString("name");
        
        String faceTexPath, faceTexName, faceTexExt;
        SplitPath(name, faceTexPath, faceTexName, faceTexExt);
        // If path is empty, add the XML file path
        if (faceTexPath.Empty())
            name = texPath + name;
        
        SharedPtr<Image> image(cache->GetResource<Image>(name));
        Load((CubeMapFace)faces, image);
        faces++;
        
        faceElem = faceElem.GetNextElement("face");
    }
    
    ClearDataLost();
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
            if ((levelWidth != width_) || (format != format_))
            {
                LOGERROR("Cube texture face does not match size or format of face 0");
                return false;
            }
        }
        
        graphics_->SetTextureForUpdate(this);
        
        for (unsigned i = 0; i < levels_; ++i)
        {
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + face, i, format_, levelWidth, levelHeight, 0,
                GetExternalFormat(format_), GL_UNSIGNED_BYTE, levelData);
            
            if (i < levels_ - 1)
            {
                image = image->GetNextLevel();
                levelData = image->GetData();
                levelWidth = image->GetWidth();
                levelHeight = image->GetHeight();
            }
            
            memoryUse += levelWidth * levelHeight * components;
        }
        
        graphics_->SetTexture(0, 0);
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
        while ((mipsToSkip) && ((width / (1 << mipsToSkip) < 4) || (height / (1 << mipsToSkip) < 4)))
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
            if ((width != width_) || (format != format_))
            {
                LOGERROR("Cube texture face does not match size or format of face 0");
                return false;
            }
        }
        
        graphics_->SetTextureForUpdate(this);
        
        for (unsigned i = 0; (i < levels_) && (i < levels - mipsToSkip); ++i)
        {
            CompressedLevel level = image->GetCompressedLevel(i + mipsToSkip);
            glCompressedTexImage2D(target_, i, format_, level.width_, level.height_, 0, level.dataSize_, level.data_);
            
            memoryUse += level.rows_ * level.rowSize_;
        }
        
        graphics_->SetTexture(0, 0);
    }
    
    faceMemoryUse_[face] = memoryUse;
    unsigned totalMemoryUse = 0;
    for (unsigned i = 0; i < MAX_CUBEMAP_FACES; ++i)
        totalMemoryUse += faceMemoryUse_[i];
    SetMemoryUse(totalMemoryUse);
    return true;
}

bool TextureCube::Create()
{
    Release();
    
    if (!graphics_)
        return false;
    
    if ((!width_) || (!height_))
        return false;
    
    glGenTextures(1, &object_);
    
    // Ensure that our texture is bound to OpenGL texture unit 0
    graphics_->SetTextureForUpdate(this);
    
    // If not compressed, create the initial level 0 texture with null data
    unsigned externalFormat = GetExternalFormat(format_);
    unsigned dataType = GetDataType(format_);
    
    if ((format_ != GL_COMPRESSED_RGBA_S3TC_DXT1_EXT) && (format_ != GL_COMPRESSED_RGBA_S3TC_DXT3_EXT) &&
        (format_ != GL_COMPRESSED_RGBA_S3TC_DXT5_EXT))
    {
        for (unsigned i = 0; i < MAX_CUBEMAP_FACES; ++i)
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, format_, width_, height_, 0, externalFormat, dataType, 0);
    }
    
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
    
    glTexParameteri(target_, GL_TEXTURE_BASE_LEVEL, 0);
    glTexParameteri(target_, GL_TEXTURE_MAX_LEVEL, levels_ - 1);
    
    // Set initial parameters, then unbind the texture
    UpdateParameters();
    graphics_->SetTexture(0, 0);
    
    return true;
}
