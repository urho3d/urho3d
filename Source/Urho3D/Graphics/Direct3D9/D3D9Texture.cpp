//
// Copyright (c) 2008-2020 the Urho3D project.
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

void Texture::SetSRGB(bool enable)
{
    if (graphics_)
        enable &= graphics_->GetSRGBSupport();

    sRGB_ = enable;
}

void Texture::UpdateParameters()
{
    // No-op on Direct3D9, handled by Graphics instead by modifying the sampler settings as necessary
}

bool Texture::GetParametersDirty() const
{
    return false;
}

bool Texture::IsCompressed() const
{
    return format_ == D3DFMT_DXT1 || format_ == D3DFMT_DXT3 || format_ == D3DFMT_DXT5;
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

void Texture::RegenerateLevels()
{
    // No-op on Direct3D9
    levelsDirty_ = false;
}

}
