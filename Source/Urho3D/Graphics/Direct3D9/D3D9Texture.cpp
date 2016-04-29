//
// Copyright (c) 2008-2016 the Urho3D project.
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

#include "../../Precompiled.h"

#include "../../Core/StringUtils.h"
#include "../../Graphics/Graphics.h"
#include "../../Graphics/GraphicsImpl.h"
#include "../../Graphics/Material.h"
#include "../../IO/FileSystem.h"
#include "../../Resource/ResourceCache.h"
#include "../../Resource/XMLFile.h"

#include "../../DebugNew.h"

namespace Urho3D
{

static const char* addressModeNames[] =
{
    "wrap",
    "mirror",
    "clamp",
    "border",
    0
};

static const char* filterModeNames[] =
{
    "nearest",
    "bilinear",
    "trilinear",
    "anisotropic",
    "default",
    0
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
    depth_(0),
    filterMode_(FILTER_DEFAULT),
    sRGB_(false)
{
    for (int i = 0; i < MAX_COORDS; ++i)
        addressMode_[i] = ADDRESS_WRAP;
    for (int i = 0; i < MAX_TEXTURE_QUALITY_LEVELS; ++i)
        mipsToSkip_[i] = (unsigned)(MAX_TEXTURE_QUALITY_LEVELS - 1 - i);
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

void Texture::SetShadowCompare(bool /*enable*/)
{
}

void Texture::SetBorderColor(const Color& color)
{
    borderColor_ = color;
}

void Texture::SetSRGB(bool enable)
{
    if (graphics_)
        enable &= graphics_->GetSRGBSupport();

    sRGB_ = enable;
}

void Texture::SetBackupTexture(Texture* texture)
{
    backupTexture_ = texture;
}

void Texture::SetMipsToSkip(int quality, int toSkip)
{
    if (quality >= QUALITY_LOW && quality < MAX_TEXTURE_QUALITY_LEVELS)
    {
        mipsToSkip_[quality] = (unsigned)toSkip;

        // Make sure a higher quality level does not actually skip more mips
        for (int i = 1; i < MAX_TEXTURE_QUALITY_LEVELS; ++i)
        {
            if (mipsToSkip_[i] > mipsToSkip_[i - 1])
                mipsToSkip_[i] = mipsToSkip_[i - 1];
        }
    }
}

bool Texture::IsCompressed() const
{
    return format_ == D3DFMT_DXT1 || format_ == D3DFMT_DXT3 || format_ == D3DFMT_DXT5;
}

int Texture::GetMipsToSkip(int quality) const
{
    return (quality >= QUALITY_LOW && quality < MAX_TEXTURE_QUALITY_LEVELS) ? mipsToSkip_[quality] : 0;
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

int Texture::GetLevelDepth(unsigned level) const
{
    if (level > levels_)
        return 0;
    return Max(depth_ >> level, 1);
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

unsigned Texture::GetDataSize(int width, int height, int depth) const
{
    return depth * GetDataSize(width, height);
}

unsigned Texture::GetRowDataSize(int width) const
{
    switch (format_)
    {
    case D3DFMT_A8:
    case D3DFMT_L8:
        return (unsigned)width;

    case D3DFMT_D16:
    case D3DFMT_R5G6B5:
    case D3DFMT_A4R4G4B4:
    case D3DFMT_A8L8:
    case D3DFMT_R16F:
        return (unsigned)(width * 2);

    case D3DFMT_X8R8G8B8:
        // Note: here source and destination data size differ
        return (unsigned)(width * 3);

    case D3DFMT_A8R8G8B8:
    case D3DFMT_G16R16:
    case D3DFMT_R32F:
    case D3DFMT_G16R16F:
    case D3DFMT_D24S8:
    case D3DFMT_D32:
        return (unsigned)(width * 4);

    case D3DFMT_A16B16G16R16:
    case D3DFMT_A16B16G16R16F:
        return (unsigned)(width * 8);

    case D3DFMT_A32B32G32R32F:
        return (unsigned)(width * 16);

    case D3DFMT_DXT1:
        return (unsigned)(((width + 3) >> 2) * 8);

    case D3DFMT_DXT3:
    case D3DFMT_DXT5:
        return (unsigned)(((width + 3) >> 2) * 16);

    default:
        return 0;
    }
}

unsigned Texture::GetComponents() const
{
    if (!width_ || IsCompressed())
        return 0;
    else
        return GetRowDataSize(width_) / width_;
}

void Texture::SetParameters(XMLFile* file)
{
    if (!file)
        return;

    XMLElement rootElem = file->GetRoot();
    SetParameters(rootElem);
}

void Texture::SetParameters(const XMLElement& element)
{
    XMLElement paramElem = element.GetChild();
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
                SetAddressMode(coordIndex, (TextureAddressMode)GetStringListIndex(mode.CString(), addressModeNames, ADDRESS_WRAP));
            }
        }

        if (name == "border")
            SetBorderColor(paramElem.GetColor("color"));

        if (name == "filter")
        {
            String mode = paramElem.GetAttributeLower("mode");
            SetFilterMode((TextureFilterMode)GetStringListIndex(mode.CString(), filterModeNames, FILTER_DEFAULT));
        }

        if (name == "mipmap")
            SetNumLevels(paramElem.GetBool("enable") ? 0 : 1);

        if (name == "quality")
        {
            if (paramElem.HasAttribute("low"))
                SetMipsToSkip(QUALITY_LOW, paramElem.GetInt("low"));
            if (paramElem.HasAttribute("med"))
                SetMipsToSkip(QUALITY_MEDIUM, paramElem.GetInt("med"));
            if (paramElem.HasAttribute("medium"))
                SetMipsToSkip(QUALITY_MEDIUM, paramElem.GetInt("medium"));
            if (paramElem.HasAttribute("high"))
                SetMipsToSkip(QUALITY_HIGH, paramElem.GetInt("high"));
        }

        if (name == "srgb")
            SetSRGB(paramElem.GetBool("enable"));

        paramElem = paramElem.GetNext();
    }
}

void Texture::CheckTextureBudget(StringHash type)
{
    ResourceCache* cache = GetSubsystem<ResourceCache>();
    unsigned long long textureBudget = cache->GetMemoryBudget(type);
    unsigned long long textureUse = cache->GetMemoryUse(type);
    if (!textureBudget)
        return;

    // If textures are over the budget, they likely can not be freed directly as materials still refer to them.
    // Therefore free unused materials first
    if (textureUse > textureBudget)
        cache->ReleaseResources(Material::GetTypeStatic());
}

}
