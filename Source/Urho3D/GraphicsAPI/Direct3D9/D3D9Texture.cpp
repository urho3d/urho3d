// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

#include "../../Precompiled.h"

#include "../../Core/StringUtils.h"
#include "../../Graphics/Graphics.h"
#include "../../Graphics/Material.h"
#include "../../GraphicsAPI/GraphicsImpl.h"
#include "../../IO/FileSystem.h"
#include "../../Resource/ResourceCache.h"
#include "../../Resource/XMLFile.h"

#include "../../DebugNew.h"

namespace Urho3D
{

void Texture::SetSRGB_D3D9(bool enable)
{
    if (graphics_)
        enable &= graphics_->GetSRGBSupport();

    sRGB_ = enable;
}

void Texture::UpdateParameters_D3D9()
{
    // No-op on Direct3D9, handled by Graphics instead by modifying the sampler settings as necessary
}

bool Texture::GetParametersDirty_D3D9() const
{
    return false;
}

bool Texture::IsCompressed_D3D9() const
{
    return format_ == D3DFMT_DXT1 || format_ == D3DFMT_DXT3 || format_ == D3DFMT_DXT5;
}

unsigned Texture::GetRowDataSize_D3D9(int width) const
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

void Texture::RegenerateLevels_D3D9()
{
    // No-op on Direct3D9
    levelsDirty_ = false;
}

}
