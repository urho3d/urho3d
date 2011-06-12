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
#include "Profiler.h"
#include "Renderer.h"
#include "ResourceCache.h"
#include "Texture2D.h"

#include <GLee.h>

#include "DebugNew.h"

OBJECTTYPESTATIC(Texture2D);

Texture2D::Texture2D(Context* context) :
    Texture(context),
    followWindowSize_(false)
{
    target_ = GL_TEXTURE_2D;
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

void Texture2D::OnDeviceReset()
{
    if (followWindowSize_)
        Create();
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
        
        glDeleteTextures(1, &object_);
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
    
    if (usage >= TEXTURE_RENDERTARGET)
    {
        if (!graphics_->GetRenderTextureSupport())
            return false;
        
        renderSurface_ = new RenderSurface(this, GL_TEXTURE_2D);
        dynamic_ = true;
        
        // Clamp mode addressing by default, nearest filtering, and mipmaps disabled
        addressMode_[COORD_U] = ADDRESS_CLAMP;
        addressMode_[COORD_V] = ADDRESS_CLAMP;
        filterMode_ = FILTER_NEAREST;
        requestedLevels_ = 1;
    }
    else if (usage == TEXTURE_DYNAMIC)
        dynamic_ = true;
    else
        dynamic_ = false;
    
    if ((width <= 0) || (height <= 0))
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
        if (!object_)
            return false;
        
        graphics_->SetTextureForUpdate(this);
        
        for (unsigned i = 0; i < levels_; ++i)
        {
            glTexImage2D(target_, i, format_, levelWidth, levelHeight, 0, GetExternalFormat(format_), GL_UNSIGNED_BYTE,
                levelData);
            
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
        
        unsigned mipsToSkip = mipsToSkip_[quality];
        if (mipsToSkip >= levels)
            mipsToSkip = levels - 1;
        while ((mipsToSkip) && ((width / (1 << mipsToSkip) < 4) || (height / (1 << mipsToSkip) < 4)))
            --mipsToSkip;
        width /= (1 << mipsToSkip);
        height /= (1 << mipsToSkip);
        
        SetNumLevels(Max((int)(levels - mipsToSkip), 1));
        SetSize(width, height, format);
        
        graphics_->SetTextureForUpdate(this);
        
        for (unsigned i = 0; (i < levels_) && (i < levels - mipsToSkip); ++i)
        {
            CompressedLevel level = image->GetCompressedLevel(i + mipsToSkip);
            glCompressedTexImage2D(target_, i, format_, level.width_, level.height_, 0, level.dataSize_, level.data_);
            
            memoryUse += level.rows_ * level.rowSize_;
        }
        
        graphics_->SetTexture(0, 0);
    }
    
    SetMemoryUse(memoryUse);
    return true;
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
        glTexImage2D(target_, 0, format_, width_, height_, 0, externalFormat, dataType, 0);
    
    // If depth format, get the depth size
    if (externalFormat == GL_DEPTH_COMPONENT)
        glGetTexLevelParameteriv(target_, 0, GL_TEXTURE_DEPTH_SIZE, &depthBits_);
    
    // Set mipmapping
    levels_ = requestedLevels_;
    if (!levels_)
    {
        unsigned maxSize = max((int)width_, (int)height_);
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
