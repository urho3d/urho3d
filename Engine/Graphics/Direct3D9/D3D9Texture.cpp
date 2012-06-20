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
#include "FileSystem.h"
#include "Graphics.h"
#include "GraphicsImpl.h"
#include "Material.h"
#include "Profiler.h"
#include "ResourceCache.h"
#include "StringUtils.h"
#include "Texture.h"
#include "XMLFile.h"

#include "DebugNew.h"

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
    format_(D3DFMT_UNKNOWN),
    pool_(D3DPOOL_MANAGED),
    usage_(0),
    levels_(0),
    requestedLevels_(0),
    width_(0),
    height_(0),
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
    if (usage_ & D3DUSAGE_DEPTHSTENCIL)
        requestedLevels_ = 1;
    else
        requestedLevels_ = levels;
}

void Texture::SetFilterMode(TextureFilterMode mode)
{
    filterMode_ = mode;
}

void Texture::SetAddressMode(TextureCoordinate coord, TextureAddressMode mode)
{
    addressMode_[coord] = mode;
}

void Texture::SetBorderColor(const Color& color)
{
    borderColor_ = color;
}

void Texture::SetBackupTexture(Texture* texture)
{
    backupTexture_ = texture;
}

bool Texture::IsCompressed() const
{
    return format_ == D3DFMT_DXT1 || format_ == D3DFMT_DXT3 || format_ == D3DFMT_DXT5;
}

int Texture::GetLevelWidth(unsigned level) const
{
    if (level > levels_)
        return 0;
    return Max(width_ >> level, 1);
}

int Texture::GetLevelHeight(unsigned level) const
{
    if (level > levels_)
        return 0;
    return Max(height_ >> level, 1);
}

TextureUsage Texture::GetUsage() const
{
    if (usage_ & D3DUSAGE_DEPTHSTENCIL)
        return TEXTURE_DEPTHSTENCIL;
    
    if (usage_ & D3DUSAGE_RENDERTARGET)
        return TEXTURE_RENDERTARGET;
    
    if (pool_ == D3DPOOL_DEFAULT)
        return TEXTURE_DYNAMIC;
    
    return TEXTURE_STATIC;
}

unsigned Texture::GetDataSize(int width, int height) const
{
    if (IsCompressed())
        return GetRowDataSize(width) * ((height + 3) >> 2);
    else
        return GetRowDataSize(width) * height;
}

unsigned Texture::GetRowDataSize(int width) const
{
    switch (format_)
    {
    case D3DFMT_A8:
    case D3DFMT_L8:
        return width;
    
    case D3DFMT_D16:
    case D3DFMT_R5G6B5:
    case D3DFMT_A4R4G4B4:
    case D3DFMT_A8L8:
        return width * 2;

    case D3DFMT_X8R8G8B8:
        // Note: here source and destination data size differ
        return width * 3;

    case D3DFMT_A8R8G8B8:
    case D3DFMT_R32F:
    case D3DFMT_D24S8:
        return width * 4;
        
    case D3DFMT_DXT1:
        return ((width + 3) >> 2) * 8;
        
    case D3DFMT_DXT3:
    case D3DFMT_DXT5:
        return ((width + 3) >> 2) * 16;
        
    default:
        return 0;
    }
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
    
    XMLElement rootElem = file->GetRoot();
    LoadParameters(rootElem);
}

void Texture::LoadParameters(const XMLElement& elem)
{
    XMLElement paramElem = elem.GetChild();
    while (paramElem)
    {
        String name = paramElem.GetName();
        
        if (name == "address")
        {
            String coord = paramElem.GetAttributeLower("coord");
            if (coord.Length() >= 1)
            {
                TextureCoordinate coordIndex = (TextureCoordinate)(coord[0] - 'u');
                String mode = paramElem.GetAttributeLower("mode");
                SetAddressMode(coordIndex, (TextureAddressMode)GetStringListIndex(mode, addressModeNames, ADDRESS_WRAP));
            }
        }
        
        if (name == "border")
            SetBorderColor(paramElem.GetColor("color"));
        
        if (name == "filter")
        {
            String mode = paramElem.GetAttributeLower("mode");
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
        
        paramElem = paramElem.GetNext();
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
