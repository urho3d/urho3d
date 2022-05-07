// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

#include "../../Precompiled.h"

#include "../../Core/Profiler.h"
#include "../../Graphics/Graphics.h"
#include "../../Graphics/Material.h"
#include "../../GraphicsAPI/Direct3D11/D3D11GraphicsImpl.h"
#include "../../IO/FileSystem.h"
#include "../../IO/Log.h"
#include "../../Resource/ResourceCache.h"
#include "../../Resource/XMLFile.h"

#include "../../DebugNew.h"

namespace Urho3D
{

static const D3D11_FILTER d3dFilterMode[] =
{
    D3D11_FILTER_MIN_MAG_MIP_POINT,
    D3D11_FILTER_MIN_MAG_LINEAR_MIP_POINT,
    D3D11_FILTER_MIN_MAG_MIP_LINEAR,
    D3D11_FILTER_ANISOTROPIC,
    D3D11_FILTER_MIN_MAG_POINT_MIP_LINEAR,
    D3D11_FILTER_COMPARISON_MIN_MAG_MIP_POINT,
    D3D11_FILTER_COMPARISON_MIN_MAG_LINEAR_MIP_POINT,
    D3D11_FILTER_COMPARISON_MIN_MAG_MIP_LINEAR,
    D3D11_FILTER_COMPARISON_ANISOTROPIC,
    D3D11_FILTER_COMPARISON_MIN_MAG_POINT_MIP_LINEAR
};

static const D3D11_TEXTURE_ADDRESS_MODE d3dAddressMode[] =
{
    D3D11_TEXTURE_ADDRESS_WRAP,
    D3D11_TEXTURE_ADDRESS_MIRROR,
    D3D11_TEXTURE_ADDRESS_CLAMP,
    D3D11_TEXTURE_ADDRESS_BORDER
};

void Texture::SetSRGB_D3D11(bool enable)
{
    if (graphics_)
        enable &= graphics_->GetSRGBSupport();

    if (enable != sRGB_)
    {
        sRGB_ = enable;
        // If texture had already been created, must recreate it to set the sRGB texture format
        if (object_.name_)
            Create();
    }
}

bool Texture::GetParametersDirty_D3D11() const
{
    return parametersDirty_ || !sampler_;
}

bool Texture::IsCompressed_D3D11() const
{
    return format_ == DXGI_FORMAT_BC1_UNORM || format_ == DXGI_FORMAT_BC2_UNORM || format_ == DXGI_FORMAT_BC3_UNORM;
}

unsigned Texture::GetRowDataSize_D3D11(int width) const
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

void Texture::UpdateParameters_D3D11()
{
    if ((!parametersDirty_ && sampler_) || !object_.ptr_)
        return;

    // Release old sampler
    URHO3D_SAFE_RELEASE(sampler_);

    D3D11_SAMPLER_DESC samplerDesc;
    memset(&samplerDesc, 0, sizeof samplerDesc);
    unsigned filterModeIndex = filterMode_ != FILTER_DEFAULT ? filterMode_ : graphics_->GetDefaultTextureFilterMode();
    if (shadowCompare_)
        filterModeIndex += 5;
    samplerDesc.Filter = d3dFilterMode[filterModeIndex];
    samplerDesc.AddressU = d3dAddressMode[addressModes_[0]];
    samplerDesc.AddressV = d3dAddressMode[addressModes_[1]];
    samplerDesc.AddressW = d3dAddressMode[addressModes_[2]];
    samplerDesc.MaxAnisotropy = anisotropy_ ? anisotropy_ : graphics_->GetDefaultTextureAnisotropy();
    samplerDesc.ComparisonFunc = D3D11_COMPARISON_LESS_EQUAL;
    samplerDesc.MinLOD = -M_INFINITY;
    samplerDesc.MaxLOD = M_INFINITY;
    memcpy(&samplerDesc.BorderColor, borderColor_.Data(), 4 * sizeof(float));

    HRESULT hr = graphics_->GetImpl_D3D11()->GetDevice()->CreateSamplerState(&samplerDesc, (ID3D11SamplerState**)&sampler_);
    if (FAILED(hr))
    {
        URHO3D_SAFE_RELEASE(sampler_);
        URHO3D_LOGD3DERROR("Failed to create sampler state", hr);
    }

    parametersDirty_ = false;
}

unsigned Texture::GetSRVFormat_D3D11(unsigned format)
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

unsigned Texture::GetDSVFormat_D3D11(unsigned format)
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

unsigned Texture::GetSRGBFormat_D3D11(unsigned format)
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

void Texture::RegenerateLevels_D3D11()
{
    if (!shaderResourceView_)
        return;

    graphics_->GetImpl_D3D11()->GetDeviceContext()->GenerateMips((ID3D11ShaderResourceView*)shaderResourceView_);
    levelsDirty_ = false;
}

}
