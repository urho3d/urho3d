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
#include "FileSystem.h"
#include "Graphics.h"
#include "GraphicsImpl.h"
#include "Material.h"
#include "Profiler.h"
#include "ResourceCache.h"
#include "StringUtils.h"
#include "Texture.h"
#include "XMLFile.h"

#include <GLee.h>

#include "DebugNew.h"

GLenum glWrapModes[] =
{
    GL_REPEAT,
    GL_MIRRORED_REPEAT,
    GL_CLAMP_TO_EDGE,
    GL_CLAMP
};

static const String addressModeNames[] =
{
    "wrap",
    "mirror",
    "clamp",
    "border",
    ""
};

static const String filterModeNames[] =
{
    "nearest",
    "bilinear",
    "trilinear",
    "anisotropic",
    "default",
    ""
};

Texture::Texture(Context* context) :
    Resource(context),
    GPUObject(GetSubsystem<Graphics>()),
    levels_(0),
    requestedLevels_(0),
    depthBits_(0),
    width_(0),
    height_(0),
    dynamic_(false),
    shadowCompare_(false),
    parametersDirty_(true),
    filterMode_(FILTER_DEFAULT)
{
    for (int i = 0; i < MAX_COORDS; ++i)
        addressMode_[i] = ADDRESS_WRAP;
    for (int i = 0; i < MAX_TEXTURE_QUALITY_LEVELS; ++i)
        mipsToSkip_[i] = MAX_TEXTURE_QUALITY_LEVELS - 1 - i;
}

Texture::~Texture()
{
}

void Texture::SetNumLevels(unsigned levels)
{
    requestedLevels_ = levels;
}

void Texture::SetFilterMode(TextureFilterMode mode)
{
    filterMode_ = mode;
    parametersDirty_ = true;
}

void Texture::SetAddressMode(TextureCoordinate coord, TextureAddressMode mode)
{
    addressMode_[coord] = mode;
    parametersDirty_ = true;
}

void Texture::SetShadowCompare(bool enable)
{
    shadowCompare_ = enable;
    parametersDirty_ = true;
}

void Texture::SetBorderColor(const Color& color)
{
    borderColor_ = color;
    parametersDirty_ = true;
}

void Texture::SetBackupTexture(Texture* texture)
{
    backupTexture_ = texture;
}

void Texture::SetParametersDirty()
{
    parametersDirty_ = true;
}

void Texture::ClearDataLost()
{
}    

void Texture::UpdateParameters()
{
    if ((!object_) || (!graphics_))
        return;
    
   // Wrapping
    glTexParameteri(textureType_, GL_TEXTURE_WRAP_S, glWrapModes[addressMode_[0]]);
    glTexParameteri(textureType_, GL_TEXTURE_WRAP_T, glWrapModes[addressMode_[1]]);
    
    TextureFilterMode filterMode = filterMode_;
    if (filterMode == FILTER_DEFAULT)
        filterMode = graphics_->GetDefaultTextureFilterMode();
    
    // Filtering
    switch (filterMode)
    {
    case FILTER_NEAREST:
        glTexParameteri(textureType_, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(textureType_, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        break;
        
    case FILTER_BILINEAR:
        if (levels_ < 2)
            glTexParameteri(textureType_, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        else
            glTexParameteri(textureType_, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
        glTexParameteri(textureType_, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        break;
        
    case FILTER_ANISOTROPIC:
    case FILTER_TRILINEAR:
        if (levels_ < 2)
            glTexParameteri(textureType_, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        else
            glTexParameteri(textureType_, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(textureType_, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        break;
    }
    
    // Anisotropy
    glTexParameterf(textureType_, GL_TEXTURE_MAX_ANISOTROPY_EXT, filterMode_ == FILTER_ANISOTROPIC ?
        (float)graphics_->GetTextureAnisotropy() : 1.0f);
    
    // Shadow compare
    if (shadowCompare_)
    {
        glTexParameteri(textureType_, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_R_TO_TEXTURE);
        glTexParameteri(textureType_, GL_TEXTURE_COMPARE_FUNC, GL_LEQUAL);
    }
    else
        glTexParameteri(textureType_, GL_TEXTURE_COMPARE_MODE, GL_NONE);
    
    glTexParameterfv(textureType_, GL_TEXTURE_BORDER_COLOR, borderColor_.GetData());
    
    parametersDirty_ = false;
}

TextureUsage Texture::GetUsage() const
{
    /// \todo Check for rendertarget / depthstencil mode
    
    if (dynamic_)
        return TEXTURE_DYNAMIC;
    
    return TEXTURE_STATIC;
}

unsigned Texture::GetDXTFormat(CompressedFormat format)
{
    switch (format)
    {
    case CF_DXT1:
        return GL_COMPRESSED_RGBA_S3TC_DXT1_EXT;
        
    case CF_DXT3:
        return GL_COMPRESSED_RGBA_S3TC_DXT3_EXT;
        
    case CF_DXT5:
        return GL_COMPRESSED_RGBA_S3TC_DXT5_EXT;
    }
    
    return 0;
}

unsigned Texture::GetExternalFormat(unsigned format)
{
    // For DEPTH_COMPONENTxx textures DEPTH_COMPONENT needs to be returned
    if ((format == GL_DEPTH_COMPONENT16) || (format == GL_DEPTH_COMPONENT24) || (format == GL_DEPTH_COMPONENT32))
        return GL_DEPTH_COMPONENT;
    else if (format == GL_DEPTH24_STENCIL8_EXT)
        return GL_DEPTH_STENCIL_EXT;
    else
        return format;
}

unsigned Texture::GetDataType(unsigned format)
{
    if (format == GL_DEPTH24_STENCIL8_EXT)
        return GL_UNSIGNED_INT_24_8_EXT;
    else
        return GL_UNSIGNED_BYTE;
}

void Texture::LoadParameters()
{
    ResourceCache* cache = GetSubsystem<ResourceCache>();
    
    String texPath, texName, texExt;
    SplitPath(GetName(), texPath, texName, texExt);
    String xmlName = texPath + texName + ".xml";
    
    if (cache->Exists(xmlName))
    {
        XMLFile* file = cache->GetResource<XMLFile>(xmlName);
        LoadParameters(file);
    }
}

void Texture::LoadParameters(XMLFile* file)
{
    if (!file)
        return;
    
    XMLElement rootElem = file->GetRootElement();
    XMLElement paramElem = rootElem.GetChildElement("");
    
    while (paramElem)
    {
        String name = paramElem.GetName();
        
        if (name == "address")
        {
            String coord = paramElem.GetStringLower("coord");
            if (coord.Length() >= 1)
            {
                TextureCoordinate coordIndex = (TextureCoordinate)(coord[0] - 'u');
                String mode = paramElem.GetStringLower("mode");
                SetAddressMode(coordIndex, (TextureAddressMode)GetStringListIndex(mode, addressModeNames, ADDRESS_WRAP));
            }
        }
        
        if (name == "border")
            SetBorderColor(paramElem.GetColor("color"));
        
        if (name == "filter")
        {
            String mode = paramElem.GetStringLower("mode");
            SetFilterMode((TextureFilterMode)GetStringListIndex(mode, filterModeNames, FILTER_DEFAULT));
        }
        
        if (name == "mipmap")
            SetNumLevels(paramElem.GetBool("enable") ? 0 : 1);
        
        if (name == "quality")
        {
            if (paramElem.HasAttribute("low"))
                mipsToSkip_[QUALITY_LOW] = Max(paramElem.GetInt("low"), 0);
            if (paramElem.HasAttribute("med"))
                mipsToSkip_[QUALITY_MEDIUM] = Max(paramElem.GetInt("med"), 0);
            if (paramElem.HasAttribute("medium"))
                mipsToSkip_[QUALITY_MEDIUM] = Max(paramElem.GetInt("medium"), 0);
            if (paramElem.HasAttribute("high"))
                mipsToSkip_[QUALITY_HIGH] = Max(paramElem.GetInt("high"), 0);
            
            // Make sure a higher quality level does not actually skip more mips
            for (int i = 1; i < MAX_TEXTURE_QUALITY_LEVELS; ++i)
            {
                if (mipsToSkip_[i] > mipsToSkip_[i - 1])
                    mipsToSkip_[i] = mipsToSkip_[i - 1];
            }
        }
        
        paramElem = paramElem.GetNextElement();
    }
}

void Texture::CheckTextureBudget(ShortStringHash type)
{
    ResourceCache* cache = GetSubsystem<ResourceCache>();
    unsigned textureBudget = cache->GetMemoryBudget(type);
    unsigned textureUse = cache->GetMemoryUse(type);
    if (!textureBudget)
        return;
    
    // If textures are over the budget, they likely can not be freed directly as materials still refer to them.
    // Therefore free unused materials first
    if (textureUse > textureBudget)
        cache->ReleaseResources(Material::GetTypeStatic());
}
