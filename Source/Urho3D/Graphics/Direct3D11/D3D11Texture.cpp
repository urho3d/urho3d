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

#include "../../Core/Profiler.h"
#include "../../Graphics/Graphics.h"
#include "../../Graphics/GraphicsImpl.h"
#include "../../Graphics/Material.h"
#include "../../IO/FileSystem.h"
#include "../../IO/Log.h"
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

static const D3D11_FILTER d3dFilterMode[] =
{
    D3D11_FILTER_MIN_MAG_MIP_POINT,
    D3D11_FILTER_MIN_MAG_LINEAR_MIP_POINT,
    D3D11_FILTER_MIN_MAG_MIP_LINEAR,
    D3D11_FILTER_ANISOTROPIC,
    D3D11_FILTER_COMPARISON_MIN_MAG_MIP_POINT,
    D3D11_FILTER_COMPARISON_MIN_MAG_LINEAR_MIP_POINT,
    D3D11_FILTER_COMPARISON_MIN_MAG_MIP_LINEAR,
    D3D11_FILTER_COMPARISON_ANISOTROPIC
};

static const D3D11_TEXTURE_ADDRESS_MODE d3dAddressMode[] =
{
    D3D11_TEXTURE_ADDRESS_WRAP,
    D3D11_TEXTURE_ADDRESS_MIRROR,
    D3D11_TEXTURE_ADDRESS_CLAMP,
    D3D11_TEXTURE_ADDRESS_BORDER
};

Texture::Texture(Context* context) :
    Resource(context),
    GPUObject(GetSubsystem<Graphics>()),
    shaderResourceView_(0),
    sampler_(0),
    format_(DXGI_FORMAT_UNKNOWN),
    usage_(TEXTURE_STATIC),
    levels_(0),
    requestedLevels_(0),
    width_(0),
    height_(0),
    depth_(0),
    shadowCompare_(false),
    filterMode_(FILTER_DEFAULT),
    sRGB_(false),
    parametersDirty_(true)
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
    if (usage_ > TEXTURE_RENDERTARGET)
        requestedLevels_ = 1;
    else
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

void Texture::SetSRGB(bool enable)
{
    if (graphics_)
        enable &= graphics_->GetSRGBSupport();

    // Note: on D3D11 sRGB only affects the texture before creation
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
    return format_ == DXGI_FORMAT_BC1_UNORM || format_ == DXGI_FORMAT_BC2_UNORM || format_ == DXGI_FORMAT_BC3_UNORM;
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
    case DXGI_FORMAT_R8_UNORM:
    case DXGI_FORMAT_A8_UNORM:
        return (unsigned)width;

    case DXGI_FORMAT_R8G8_UNORM:
    case DXGI_FORMAT_R16_UNORM:
    case DXGI_FORMAT_R16_FLOAT:
    case DXGI_FORMAT_R16_TYPELESS:
        return (unsigned)(width * 2);

    case DXGI_FORMAT_R8G8B8A8_UNORM:
    case DXGI_FORMAT_R16G16_UNORM:
    case DXGI_FORMAT_R16G16_FLOAT:
    case DXGI_FORMAT_R32_FLOAT:
    case DXGI_FORMAT_R24G8_TYPELESS:
    case DXGI_FORMAT_R32_TYPELESS:
        return (unsigned)(width * 4);

    case DXGI_FORMAT_R16G16B16A16_UNORM:
    case DXGI_FORMAT_R16G16B16A16_FLOAT:
        return (unsigned)(width * 8);

    case DXGI_FORMAT_R32G32B32A32_FLOAT:
        return (unsigned)(width * 16);

    case DXGI_FORMAT_BC1_UNORM:
        return (unsigned)(((width + 3) >> 2) * 8);

    case DXGI_FORMAT_BC2_UNORM:
    case DXGI_FORMAT_BC3_UNORM:
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

void Texture::SetParametersDirty()
{
    parametersDirty_ = true;
}

void Texture::UpdateParameters()
{
    if ((!parametersDirty_ && sampler_) || !object_)
        return;

    // Release old sampler
    URHO3D_SAFE_RELEASE(sampler_);

    D3D11_SAMPLER_DESC samplerDesc;
    memset(&samplerDesc, 0, sizeof samplerDesc);
    unsigned filterModeIndex = filterMode_ != FILTER_DEFAULT ? filterMode_ : graphics_->GetDefaultTextureFilterMode();
    if (shadowCompare_)
        filterModeIndex += 4;
    samplerDesc.Filter = d3dFilterMode[filterModeIndex];
    samplerDesc.AddressU = d3dAddressMode[addressMode_[0]];
    samplerDesc.AddressV = d3dAddressMode[addressMode_[1]];
    samplerDesc.AddressW = d3dAddressMode[addressMode_[2]];
    samplerDesc.MaxAnisotropy = graphics_->GetTextureAnisotropy();
    samplerDesc.ComparisonFunc = D3D11_COMPARISON_LESS_EQUAL;
    samplerDesc.MinLOD = -M_INFINITY;
    samplerDesc.MaxLOD = M_INFINITY;
    memcpy(&samplerDesc.BorderColor, borderColor_.Data(), 4 * sizeof(float));

    HRESULT hr = graphics_->GetImpl()->GetDevice()->CreateSamplerState(&samplerDesc, (ID3D11SamplerState**)&sampler_);
    if (FAILED(hr))
    {
        URHO3D_SAFE_RELEASE(sampler_);
        URHO3D_LOGD3DERROR("Failed to create sampler state", hr);
    }

    parametersDirty_ = false;
}

unsigned Texture::CheckMaxLevels(int width, int height, unsigned requestedLevels)
{
    unsigned maxLevels = 1;
    while (width > 1 && height > 1)
    {
        ++maxLevels;
        width >>= 1;
        height >>= 1;
    }

    if (!requestedLevels || maxLevels < requestedLevels)
        return maxLevels;
    else
        return requestedLevels;
}

unsigned Texture::CheckMaxLevels(int width, int height, int depth, unsigned requestedLevels)
{
    unsigned maxLevels = 1;
    while (width > 1 && height > 1 && depth > 1)
    {
        ++maxLevels;
        width >>= 1;
        height >>= 1;
        depth >>= 1;
    }

    if (!requestedLevels || maxLevels < requestedLevels)
        return maxLevels;
    else
        return requestedLevels;
}


unsigned Texture::GetSRVFormat(unsigned format)
{
    if (format == DXGI_FORMAT_R24G8_TYPELESS)
        return DXGI_FORMAT_R24_UNORM_X8_TYPELESS;
    else if (format == DXGI_FORMAT_R16_TYPELESS)
        return DXGI_FORMAT_R16_UNORM;
    else if (format == DXGI_FORMAT_R32_TYPELESS)
        return DXGI_FORMAT_R32_FLOAT;
    else
        return format;
}

unsigned Texture::GetDSVFormat(unsigned format)
{
    if (format == DXGI_FORMAT_R24G8_TYPELESS)
        return DXGI_FORMAT_D24_UNORM_S8_UINT;
    else if (format == DXGI_FORMAT_R16_TYPELESS)
        return DXGI_FORMAT_D16_UNORM;
    else if (format == DXGI_FORMAT_R32_TYPELESS)
        return DXGI_FORMAT_D32_FLOAT;
    else
        return format;
}

unsigned Texture::GetSRGBFormat(unsigned format)
{
    if (format == DXGI_FORMAT_R8G8B8A8_UNORM)
        return DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;
    else if (format == DXGI_FORMAT_BC1_UNORM)
        return DXGI_FORMAT_BC1_UNORM_SRGB;
    else if (format == DXGI_FORMAT_BC2_UNORM)
        return DXGI_FORMAT_BC2_UNORM_SRGB;
    else if (format == DXGI_FORMAT_BC3_UNORM)
        return DXGI_FORMAT_BC3_UNORM_SRGB;
    else
        return format;
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
