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

#include "../../Core/Context.h"
#include "../../Core/Profiler.h"
#include "../../Graphics/Graphics.h"
#include "../../Graphics/GraphicsEvents.h"
#include "../../Graphics/GraphicsImpl.h"
#include "../../Graphics/Renderer.h"
#include "../../Graphics/Texture3D.h"
#include "../../IO/FileSystem.h"
#include "../../IO/Log.h"
#include "../../Resource/ResourceCache.h"
#include "../../Resource/XMLFile.h"

#include "../../DebugNew.h"

namespace Urho3D
{

void Texture3D::OnDeviceLost()
{
    // No-op on Direct3D11
}

void Texture3D::OnDeviceReset()
{
    // No-op on Direct3D11
}

void Texture3D::Release()
{
    if (graphics_ && object_.ptr_)
    {
        for (unsigned i = 0; i < MAX_TEXTURE_UNITS; ++i)
        {
            if (graphics_->GetTexture(i) == this)
                graphics_->SetTexture(i, nullptr);
        }
    }

    URHO3D_SAFE_RELEASE(object_.ptr_);
    URHO3D_SAFE_RELEASE(shaderResourceView_);
    URHO3D_SAFE_RELEASE(sampler_);
}

bool Texture3D::SetData(unsigned level, int x, int y, int z, int width, int height, int depth, const void* data)
{
    URHO3D_PROFILE(SetTextureData);

    if (!object_.ptr_)
    {
        URHO3D_LOGERROR("No texture created, can not set data");
        return false;
    }

    if (!data)
    {
        URHO3D_LOGERROR("Null source for setting data");
        return false;
    }

    if (level >= levels_)
    {
        URHO3D_LOGERROR("Illegal mip level for setting data");
        return false;
    }

    int levelWidth = GetLevelWidth(level);
    int levelHeight = GetLevelHeight(level);
    int levelDepth = GetLevelDepth(level);
    if (x < 0 || x + width > levelWidth || y < 0 || y + height > levelHeight || z < 0 || z + depth > levelDepth || width <= 0 ||
        height <= 0 || depth <= 0)
    {
        URHO3D_LOGERROR("Illegal dimensions for setting data");
        return false;
    }

    // If compressed, align the update region on a block
    if (IsCompressed())
    {
        x &= ~3;
        y &= ~3;
        width += 3;
        width &= 0xfffffffc;
        height += 3;
        height &= 0xfffffffc;
    }

    unsigned char* src = (unsigned char*)data;
    unsigned rowSize = GetRowDataSize(width);
    unsigned rowStart = GetRowDataSize(x);
    unsigned subResource = D3D11CalcSubresource(level, 0, levels_);

    if (usage_ == TEXTURE_DYNAMIC)
    {
        if (IsCompressed())
        {
            height = (height + 3) >> 2;
            y >>= 2;
        }

        D3D11_MAPPED_SUBRESOURCE mappedData;
        mappedData.pData = nullptr;

        HRESULT hr = graphics_->GetImpl()->GetDeviceContext()->Map((ID3D11Resource*)object_.ptr_, subResource, D3D11_MAP_WRITE_DISCARD, 0,
            &mappedData);
        if (FAILED(hr) || !mappedData.pData)
        {
            URHO3D_LOGD3DERROR("Failed to map texture for update", hr);
            return false;
        }
        else
        {
            for (int page = 0; page < depth; ++page)
            {
                for (int row = 0; row < height; ++row)
                {
                    memcpy((unsigned char*)mappedData.pData + (page + z) * mappedData.DepthPitch + (row + y) * mappedData.RowPitch +
                           rowStart, src + row * rowSize, rowSize);
                }
            }

            graphics_->GetImpl()->GetDeviceContext()->Unmap((ID3D11Resource*)object_.ptr_, subResource);
        }
    }
    else
    {
        if (IsCompressed())
            levelHeight = (levelHeight + 3) >> 2;

        D3D11_BOX destBox;
        destBox.left = (UINT)x;
        destBox.right = (UINT)(x + width);
        destBox.top = (UINT)y;
        destBox.bottom = (UINT)(y + height);
        destBox.front = (UINT)z;
        destBox.back = (UINT)(z + depth);

        graphics_->GetImpl()->GetDeviceContext()->UpdateSubresource((ID3D11Resource*)object_.ptr_, subResource, &destBox, data,
            rowSize, levelHeight * rowSize);
    }

    return true;
}

bool Texture3D::SetData(Image* image, bool useAlpha)
{
    if (!image)
    {
        URHO3D_LOGERROR("Null image, can not load texture");
        return false;
    }

    // Use a shared ptr for managing the temporary mip images created during this function
    SharedPtr<Image> mipImage;
    unsigned memoryUse = sizeof(Texture3D);
    MaterialQuality quality = QUALITY_HIGH;
    Renderer* renderer = GetSubsystem<Renderer>();
    if (renderer)
        quality = renderer->GetTextureQuality();

    if (!image->IsCompressed())
    {
        // Convert unsuitable formats to RGBA
        unsigned components = image->GetComponents();
        if ((components == 1 && !useAlpha) || components == 2 || components == 3)
        {
            mipImage = image->ConvertToRGBA(); image = mipImage;
            if (!image)
                return false;
            components = image->GetComponents();
        }

        unsigned char* levelData = image->GetData();
        int levelWidth = image->GetWidth();
        int levelHeight = image->GetHeight();
        int levelDepth = image->GetDepth();
        unsigned format = 0;

        // Discard unnecessary mip levels
        for (unsigned i = 0; i < mipsToSkip_[quality]; ++i)
        {
            mipImage = image->GetNextLevel(); image = mipImage;
            levelData = image->GetData();
            levelWidth = image->GetWidth();
            levelHeight = image->GetHeight();
            levelDepth = image->GetDepth();
        }

        switch (components)
        {
        case 1:
            format = Graphics::GetAlphaFormat();
            break;

        case 4:
            format = Graphics::GetRGBAFormat();
            break;

        default: break;
        }

        // If image was previously compressed, reset number of requested levels to avoid error if level count is too high for new size
        if (IsCompressed() && requestedLevels_ > 1)
            requestedLevels_ = 0;
        SetSize(levelWidth, levelHeight, levelDepth, format);

        for (unsigned i = 0; i < levels_; ++i)
        {
            SetData(i, 0, 0, 0, levelWidth, levelHeight, levelDepth, levelData);
            memoryUse += levelWidth * levelHeight * levelDepth * components;

            if (i < levels_ - 1)
            {
                mipImage = image->GetNextLevel(); image = mipImage;
                levelData = image->GetData();
                levelWidth = image->GetWidth();
                levelHeight = image->GetHeight();
                levelDepth = image->GetDepth();
            }
        }
    }
    else
    {
        int width = image->GetWidth();
        int height = image->GetHeight();
        int depth = image->GetDepth();
        unsigned levels = image->GetNumCompressedLevels();
        unsigned format = graphics_->GetFormat(image->GetCompressedFormat());
        bool needDecompress = false;

        if (!format)
        {
            format = Graphics::GetRGBAFormat();
            needDecompress = true;
        }

        unsigned mipsToSkip = mipsToSkip_[quality];
        if (mipsToSkip >= levels)
            mipsToSkip = levels - 1;
        while (mipsToSkip && (width / (1 << mipsToSkip) < 4 || height / (1 << mipsToSkip) < 4 || depth / (1 << mipsToSkip) < 4))
            --mipsToSkip;
        width /= (1 << mipsToSkip);
        height /= (1 << mipsToSkip);
        depth /= (1 << mipsToSkip);

        SetNumLevels(Max((levels - mipsToSkip), 1U));
        SetSize(width, height, depth, format);

        for (unsigned i = 0; i < levels_ && i < levels - mipsToSkip; ++i)
        {
            CompressedLevel level = image->GetCompressedLevel(i + mipsToSkip);
            if (!needDecompress)
            {
                SetData(i, 0, 0, 0, level.width_, level.height_, level.depth_, level.data_);
                memoryUse += level.depth_ * level.rows_ * level.rowSize_;
            }
            else
            {
                unsigned char* rgbaData = new unsigned char[level.width_ * level.height_ * level.depth_ * 4];
                level.Decompress(rgbaData);
                SetData(i, 0, 0, 0, level.width_, level.height_, level.depth_, rgbaData);
                memoryUse += level.width_ * level.height_ * level.depth_ * 4;
                delete[] rgbaData;
            }
        }
    }

    SetMemoryUse(memoryUse);
    return true;
}

bool Texture3D::GetData(unsigned level, void* dest) const
{
    if (!object_.ptr_)
    {
        URHO3D_LOGERROR("No texture created, can not get data");
        return false;
    }

    if (!dest)
    {
        URHO3D_LOGERROR("Null destination for getting data");
        return false;
    }

    if (level >= levels_)
    {
        URHO3D_LOGERROR("Illegal mip level for getting data");
        return false;
    }

    int levelWidth = GetLevelWidth(level);
    int levelHeight = GetLevelHeight(level);
    int levelDepth = GetLevelDepth(level);

    D3D11_TEXTURE3D_DESC textureDesc;
    memset(&textureDesc, 0, sizeof textureDesc);
    textureDesc.Width = (UINT)levelWidth;
    textureDesc.Height = (UINT)levelHeight;
    textureDesc.Depth = (UINT)levelDepth;
    textureDesc.MipLevels = 1;
    textureDesc.Format = (DXGI_FORMAT)format_;
    textureDesc.Usage = D3D11_USAGE_STAGING;
    textureDesc.CPUAccessFlags = D3D11_CPU_ACCESS_READ;

    ID3D11Texture3D* stagingTexture = nullptr;
    HRESULT hr = graphics_->GetImpl()->GetDevice()->CreateTexture3D(&textureDesc, nullptr, &stagingTexture);
    if (FAILED(hr))
    {
        URHO3D_LOGD3DERROR("Failed to create staging texture for GetData", hr);
        URHO3D_SAFE_RELEASE(stagingTexture);
        return false;
    }

    unsigned srcSubResource = D3D11CalcSubresource(level, 0, levels_);
    D3D11_BOX srcBox;
    srcBox.left = 0;
    srcBox.right = (UINT)levelWidth;
    srcBox.top = 0;
    srcBox.bottom = (UINT)levelHeight;
    srcBox.front = 0;
    srcBox.back = (UINT)levelDepth;
    graphics_->GetImpl()->GetDeviceContext()->CopySubresourceRegion(stagingTexture, 0, 0, 0, 0, (ID3D11Resource*)object_.ptr_,
        srcSubResource, &srcBox);

    D3D11_MAPPED_SUBRESOURCE mappedData;
    mappedData.pData = nullptr;
    unsigned rowSize = GetRowDataSize(levelWidth);
    unsigned numRows = (unsigned)(IsCompressed() ? (levelHeight + 3) >> 2 : levelHeight);

    hr = graphics_->GetImpl()->GetDeviceContext()->Map((ID3D11Resource*)stagingTexture, 0, D3D11_MAP_READ, 0, &mappedData);
    if (FAILED(hr) || !mappedData.pData)
    {
        URHO3D_LOGD3DERROR("Failed to map staging texture for GetData", hr);
        URHO3D_SAFE_RELEASE(stagingTexture);
        return false;
    }
    else
    {
        for (int page = 0; page < levelDepth; ++page)
        {
            for (unsigned row = 0; row < numRows; ++row)
            {
                memcpy((unsigned char*)dest + (page * numRows + row) * rowSize,
                    (unsigned char*)mappedData.pData + page * mappedData.DepthPitch + row * mappedData.RowPitch, rowSize);
            }
        }
        graphics_->GetImpl()->GetDeviceContext()->Unmap((ID3D11Resource*)stagingTexture, 0);
        URHO3D_SAFE_RELEASE(stagingTexture);
        return true;
    }
}

bool Texture3D::Create()
{
    Release();

    if (!graphics_ || !width_ || !height_ || !depth_)
        return false;

    levels_ = CheckMaxLevels(width_, height_, depth_, requestedLevels_);

    D3D11_TEXTURE3D_DESC textureDesc;
    memset(&textureDesc, 0, sizeof textureDesc);
    textureDesc.Width = (UINT)width_;
    textureDesc.Height = (UINT)height_;
    textureDesc.Depth = (UINT)depth_;
    textureDesc.MipLevels = usage_ != TEXTURE_DYNAMIC ? levels_ : 1;
    textureDesc.Format = (DXGI_FORMAT)(sRGB_ ? GetSRGBFormat(format_) : format_);
    textureDesc.Usage = usage_ == TEXTURE_DYNAMIC ? D3D11_USAGE_DYNAMIC : D3D11_USAGE_DEFAULT;
    textureDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
    textureDesc.CPUAccessFlags = usage_ == TEXTURE_DYNAMIC ? D3D11_CPU_ACCESS_WRITE : 0;

    HRESULT hr = graphics_->GetImpl()->GetDevice()->CreateTexture3D(&textureDesc, nullptr, (ID3D11Texture3D**)&object_.ptr_);
    if (FAILED(hr))
    {
        URHO3D_LOGD3DERROR("Failed to create texture", hr);
        URHO3D_SAFE_RELEASE(object_.ptr_);
        return false;
    }

    D3D11_SHADER_RESOURCE_VIEW_DESC resourceViewDesc;
    memset(&resourceViewDesc, 0, sizeof resourceViewDesc);
    resourceViewDesc.Format = (DXGI_FORMAT)GetSRVFormat(textureDesc.Format);
    resourceViewDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE3D;
    resourceViewDesc.Texture3D.MipLevels = usage_ != TEXTURE_DYNAMIC ? (UINT)levels_ : 1;

    hr = graphics_->GetImpl()->GetDevice()->CreateShaderResourceView((ID3D11Resource*)object_.ptr_, &resourceViewDesc,
        (ID3D11ShaderResourceView**)&shaderResourceView_);
    if (FAILED(hr))
    {
        URHO3D_LOGD3DERROR("Failed to create shader resource view for texture", hr);
        URHO3D_SAFE_RELEASE(shaderResourceView_);
        return false;
    }

    return true;
}

}
