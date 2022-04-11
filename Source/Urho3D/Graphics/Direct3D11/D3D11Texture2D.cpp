//
// Copyright (c) 2008-2022 the Urho3D project.
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
#include "../../Graphics/Renderer.h"
#include "../../Graphics/Texture2D.h"
#include "../../IO/FileSystem.h"
#include "../../IO/Log.h"
#include "../../Resource/ResourceCache.h"
#include "../../Resource/XMLFile.h"
#include "D3D11GraphicsImpl.h"

#include "../../DebugNew.h"

namespace Urho3D
{

void Texture2D::OnDeviceLost_D3D11()
{
    // No-op on Direct3D11
}

void Texture2D::OnDeviceReset_D3D11()
{
    // No-op on Direct3D11
}

void Texture2D::Release_D3D11()
{
    if (graphics_ && object_.ptr_)
    {
        for (unsigned i = 0; i < MAX_TEXTURE_UNITS; ++i)
        {
            if (graphics_->GetTexture(i) == this)
                graphics_->SetTexture(i, nullptr);
        }
    }

    if (renderSurface_)
        renderSurface_->Release();

    URHO3D_SAFE_RELEASE(object_.ptr_);
    URHO3D_SAFE_RELEASE(resolveTexture_);
    URHO3D_SAFE_RELEASE(shaderResourceView_);
    URHO3D_SAFE_RELEASE(sampler_);
}

bool Texture2D::SetData_D3D11(unsigned level, int x, int y, int width, int height, const void* data)
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
    if (x < 0 || x + width > levelWidth || y < 0 || y + height > levelHeight || width <= 0 || height <= 0)
    {
        URHO3D_LOGERROR("Illegal dimensions for setting data");
        return false;
    }

    // If compressed, align the update region on a block
    if (IsCompressed_D3D11())
    {
        x &= ~3;
        y &= ~3;
        width += 3;
        width &= 0xfffffffc;
        height += 3;
        height &= 0xfffffffc;
    }

    unsigned char* src = (unsigned char*)data;
    unsigned rowSize = GetRowDataSize_D3D11(width);
    unsigned rowStart = GetRowDataSize_D3D11(x);
    unsigned subResource = D3D11CalcSubresource(level, 0, levels_);

    if (usage_ == TEXTURE_DYNAMIC)
    {
        if (IsCompressed_D3D11())
        {
            height = (height + 3) >> 2;
            y >>= 2;
        }

        D3D11_MAPPED_SUBRESOURCE mappedData;
        mappedData.pData = nullptr;

        HRESULT hr = graphics_->GetImpl_D3D11()->GetDeviceContext()->Map((ID3D11Resource*)object_.ptr_, subResource, D3D11_MAP_WRITE_DISCARD, 0,
            &mappedData);
        if (FAILED(hr) || !mappedData.pData)
        {
            URHO3D_LOGD3DERROR("Failed to map texture for update", hr);
            return false;
        }
        else
        {
            for (int row = 0; row < height; ++row)
                memcpy((unsigned char*)mappedData.pData + (row + y) * mappedData.RowPitch + rowStart, src + row * rowSize, rowSize);
            graphics_->GetImpl_D3D11()->GetDeviceContext()->Unmap((ID3D11Resource*)object_.ptr_, subResource);
        }
    }
    else
    {
        D3D11_BOX destBox;
        destBox.left = (UINT)x;
        destBox.right = (UINT)(x + width);
        destBox.top = (UINT)y;
        destBox.bottom = (UINT)(y + height);
        destBox.front = 0;
        destBox.back = 1;

        graphics_->GetImpl_D3D11()->GetDeviceContext()->UpdateSubresource((ID3D11Resource*)object_.ptr_, subResource, &destBox, data,
            rowSize, 0);
    }

    return true;
}

bool Texture2D::SetData_D3D11(Image* image, bool useAlpha)
{
    if (!image)
    {
        URHO3D_LOGERROR("Null image, can not load texture");
        return false;
    }

    // Use a shared ptr for managing the temporary mip images created during this function
    SharedPtr<Image> mipImage;
    unsigned memoryUse = sizeof(Texture2D);
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
        unsigned format = 0;

        // Discard unnecessary mip levels
        for (unsigned i = 0; i < mipsToSkip_[quality]; ++i)
        {
            mipImage = image->GetNextLevel(); image = mipImage;
            levelData = image->GetData();
            levelWidth = image->GetWidth();
            levelHeight = image->GetHeight();
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
        if (IsCompressed_D3D11() && requestedLevels_ > 1)
            requestedLevels_ = 0;
        SetSize(levelWidth, levelHeight, format);

        for (unsigned i = 0; i < levels_; ++i)
        {
            SetData_D3D11(i, 0, 0, levelWidth, levelHeight, levelData);
            memoryUse += levelWidth * levelHeight * components;

            if (i < levels_ - 1)
            {
                mipImage = image->GetNextLevel(); image = mipImage;
                levelData = image->GetData();
                levelWidth = image->GetWidth();
                levelHeight = image->GetHeight();
            }
        }
    }
    else
    {
        int width = image->GetWidth();
        int height = image->GetHeight();
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
        while (mipsToSkip && (width / (1 << mipsToSkip) < 4 || height / (1 << mipsToSkip) < 4))
            --mipsToSkip;
        width /= (1 << mipsToSkip);
        height /= (1 << mipsToSkip);

        SetNumLevels(Max((levels - mipsToSkip), 1U));
        SetSize(width, height, format);

        for (unsigned i = 0; i < levels_ && i < levels - mipsToSkip; ++i)
        {
            CompressedLevel level = image->GetCompressedLevel(i + mipsToSkip);
            if (!needDecompress)
            {
                SetData_D3D11(i, 0, 0, level.width_, level.height_, level.data_);
                memoryUse += level.rows_ * level.rowSize_;
            }
            else
            {
                unsigned char* rgbaData = new unsigned char[level.width_ * level.height_ * 4];
                level.Decompress(rgbaData);
                SetData_D3D11(i, 0, 0, level.width_, level.height_, rgbaData);
                memoryUse += level.width_ * level.height_ * 4;
                delete[] rgbaData;
            }
        }
    }

    SetMemoryUse(memoryUse);
    return true;
}

bool Texture2D::GetData_D3D11(unsigned level, void* dest) const
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

    if (multiSample_ > 1 && !autoResolve_)
    {
        URHO3D_LOGERROR("Can not get data from multisampled texture without autoresolve");
        return false;
    }

    if (resolveDirty_)
        graphics_->ResolveToTexture(const_cast<Texture2D*>(this));

    int levelWidth = GetLevelWidth(level);
    int levelHeight = GetLevelHeight(level);

    D3D11_TEXTURE2D_DESC textureDesc;
    memset(&textureDesc, 0, sizeof textureDesc);
    textureDesc.Width = (UINT)levelWidth;
    textureDesc.Height = (UINT)levelHeight;
    textureDesc.MipLevels = 1;
    textureDesc.ArraySize = 1;
    textureDesc.Format = (DXGI_FORMAT)format_;
    textureDesc.SampleDesc.Count = 1;
    textureDesc.SampleDesc.Quality = 0;
    textureDesc.Usage = D3D11_USAGE_STAGING;
    textureDesc.CPUAccessFlags = D3D11_CPU_ACCESS_READ;

    ID3D11Texture2D* stagingTexture = nullptr;
    HRESULT hr = graphics_->GetImpl_D3D11()->GetDevice()->CreateTexture2D(&textureDesc, nullptr, &stagingTexture);
    if (FAILED(hr))
    {
        URHO3D_LOGD3DERROR("Failed to create staging texture for GetData", hr);
        URHO3D_SAFE_RELEASE(stagingTexture);
        return false;
    }

    ID3D11Resource* srcResource = (ID3D11Resource*)(resolveTexture_ ? resolveTexture_ : object_.ptr_);
    unsigned srcSubResource = D3D11CalcSubresource(level, 0, levels_);

    D3D11_BOX srcBox;
    srcBox.left = 0;
    srcBox.right = (UINT)levelWidth;
    srcBox.top = 0;
    srcBox.bottom = (UINT)levelHeight;
    srcBox.front = 0;
    srcBox.back = 1;
    graphics_->GetImpl_D3D11()->GetDeviceContext()->CopySubresourceRegion(stagingTexture, 0, 0, 0, 0, srcResource,
        srcSubResource, &srcBox);

    D3D11_MAPPED_SUBRESOURCE mappedData;
    mappedData.pData = nullptr;
    unsigned rowSize = GetRowDataSize_D3D11(levelWidth);
    unsigned numRows = (unsigned)(IsCompressed_D3D11() ? (levelHeight + 3) >> 2 : levelHeight);

    hr = graphics_->GetImpl_D3D11()->GetDeviceContext()->Map((ID3D11Resource*)stagingTexture, 0, D3D11_MAP_READ, 0, &mappedData);
    if (FAILED(hr) || !mappedData.pData)
    {
        URHO3D_LOGD3DERROR("Failed to map staging texture for GetData", hr);
        URHO3D_SAFE_RELEASE(stagingTexture);
        return false;
    }
    else
    {
        for (unsigned row = 0; row < numRows; ++row)
            memcpy((unsigned char*)dest + row * rowSize, (unsigned char*)mappedData.pData + row * mappedData.RowPitch, rowSize);
        graphics_->GetImpl_D3D11()->GetDeviceContext()->Unmap((ID3D11Resource*)stagingTexture, 0);
        URHO3D_SAFE_RELEASE(stagingTexture);
        return true;
    }
}

bool Texture2D::Create_D3D11()
{
    Release_D3D11();

    if (!graphics_ || !width_ || !height_)
        return false;

    levels_ = CheckMaxLevels(width_, height_, requestedLevels_);

    D3D11_TEXTURE2D_DESC textureDesc;
    memset(&textureDesc, 0, sizeof textureDesc);
    textureDesc.Format = (DXGI_FORMAT)(sRGB_ ? GetSRGBFormat_D3D11(format_) : format_);

    // Disable multisampling if not supported
    if (multiSample_ > 1 && !graphics_->GetImpl_D3D11()->CheckMultiSampleSupport(textureDesc.Format, multiSample_))
    {
        multiSample_ = 1;
        autoResolve_ = false;
    }

    // Set mipmapping
    if (usage_ == TEXTURE_DEPTHSTENCIL)
        levels_ = 1;
    else if (usage_ == TEXTURE_RENDERTARGET && levels_ != 1 && multiSample_ == 1)
        textureDesc.MiscFlags |= D3D11_RESOURCE_MISC_GENERATE_MIPS;

    textureDesc.Width = (UINT)width_;
    textureDesc.Height = (UINT)height_;
    // Disable mip levels from the multisample texture. Rather create them to the resolve texture
    textureDesc.MipLevels = (multiSample_ == 1 && usage_ != TEXTURE_DYNAMIC) ? levels_ : 1;
    textureDesc.ArraySize = 1;
    textureDesc.SampleDesc.Count = (UINT)multiSample_;
    textureDesc.SampleDesc.Quality = graphics_->GetImpl_D3D11()->GetMultiSampleQuality(textureDesc.Format, multiSample_);

    textureDesc.Usage = usage_ == TEXTURE_DYNAMIC ? D3D11_USAGE_DYNAMIC : D3D11_USAGE_DEFAULT;
    textureDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
    if (usage_ == TEXTURE_RENDERTARGET)
        textureDesc.BindFlags |= D3D11_BIND_RENDER_TARGET;
    else if (usage_ == TEXTURE_DEPTHSTENCIL)
        textureDesc.BindFlags |= D3D11_BIND_DEPTH_STENCIL;
    textureDesc.CPUAccessFlags = usage_ == TEXTURE_DYNAMIC ? D3D11_CPU_ACCESS_WRITE : 0;

    // D3D feature level 10.0 or below does not support readable depth when multisampled
    if (usage_ == TEXTURE_DEPTHSTENCIL && multiSample_ > 1 && graphics_->GetImpl_D3D11()->GetDevice()->GetFeatureLevel() < D3D_FEATURE_LEVEL_10_1)
        textureDesc.BindFlags &= ~D3D11_BIND_SHADER_RESOURCE;

    HRESULT hr = graphics_->GetImpl_D3D11()->GetDevice()->CreateTexture2D(&textureDesc, nullptr, (ID3D11Texture2D**)&object_);
    if (FAILED(hr))
    {
        URHO3D_LOGD3DERROR("Failed to create texture", hr);
        URHO3D_SAFE_RELEASE(object_.ptr_);
        return false;
    }

    // Create resolve texture for multisampling if necessary
    if (multiSample_ > 1 && autoResolve_)
    {
        textureDesc.MipLevels = levels_;
        textureDesc.SampleDesc.Count = 1;
        textureDesc.SampleDesc.Quality = 0;
        if (levels_ != 1)
            textureDesc.MiscFlags |= D3D11_RESOURCE_MISC_GENERATE_MIPS;

        HRESULT hr = graphics_->GetImpl_D3D11()->GetDevice()->CreateTexture2D(&textureDesc, nullptr, (ID3D11Texture2D**)&resolveTexture_);
        if (FAILED(hr))
        {
            URHO3D_LOGD3DERROR("Failed to create resolve texture", hr);
            URHO3D_SAFE_RELEASE(resolveTexture_);
            return false;
        }
    }

    if (textureDesc.BindFlags & D3D11_BIND_SHADER_RESOURCE)
    {
        D3D11_SHADER_RESOURCE_VIEW_DESC resourceViewDesc;
        memset(&resourceViewDesc, 0, sizeof resourceViewDesc);
        resourceViewDesc.Format = (DXGI_FORMAT)GetSRVFormat_D3D11(textureDesc.Format);
        resourceViewDesc.ViewDimension = (multiSample_ > 1 && !autoResolve_) ? D3D11_SRV_DIMENSION_TEXTURE2DMS :
            D3D11_SRV_DIMENSION_TEXTURE2D;
        resourceViewDesc.Texture2D.MipLevels = usage_ != TEXTURE_DYNAMIC ? (UINT)levels_ : 1;

        // Sample the resolve texture if created, otherwise the original
        ID3D11Resource* viewObject = resolveTexture_ ? (ID3D11Resource*)resolveTexture_ : (ID3D11Resource*)object_.ptr_;
        hr = graphics_->GetImpl_D3D11()->GetDevice()->CreateShaderResourceView(viewObject, &resourceViewDesc,
            (ID3D11ShaderResourceView**)&shaderResourceView_);
        if (FAILED(hr))
        {
            URHO3D_LOGD3DERROR("Failed to create shader resource view for texture", hr);
            URHO3D_SAFE_RELEASE(shaderResourceView_);
            return false;
        }
    }

    if (usage_ == TEXTURE_RENDERTARGET)
    {
        D3D11_RENDER_TARGET_VIEW_DESC renderTargetViewDesc;
        memset(&renderTargetViewDesc, 0, sizeof renderTargetViewDesc);
        renderTargetViewDesc.Format = textureDesc.Format;
        renderTargetViewDesc.ViewDimension = multiSample_ > 1 ? D3D11_RTV_DIMENSION_TEXTURE2DMS : D3D11_RTV_DIMENSION_TEXTURE2D;

        hr = graphics_->GetImpl_D3D11()->GetDevice()->CreateRenderTargetView((ID3D11Resource*)object_.ptr_, &renderTargetViewDesc,
            (ID3D11RenderTargetView**)&renderSurface_->renderTargetView_);
        if (FAILED(hr))
        {
            URHO3D_LOGD3DERROR("Failed to create rendertarget view for texture", hr);
            URHO3D_SAFE_RELEASE(renderSurface_->renderTargetView_);
            return false;
        }
    }
    else if (usage_ == TEXTURE_DEPTHSTENCIL)
    {
        D3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc;
        memset(&depthStencilViewDesc, 0, sizeof depthStencilViewDesc);
        depthStencilViewDesc.Format = (DXGI_FORMAT)GetDSVFormat_D3D11(textureDesc.Format);
        depthStencilViewDesc.ViewDimension = multiSample_ > 1 ? D3D11_DSV_DIMENSION_TEXTURE2DMS : D3D11_DSV_DIMENSION_TEXTURE2D;

        hr = graphics_->GetImpl_D3D11()->GetDevice()->CreateDepthStencilView((ID3D11Resource*)object_.ptr_, &depthStencilViewDesc,
            (ID3D11DepthStencilView**)&renderSurface_->renderTargetView_);
        if (FAILED(hr))
        {
            URHO3D_LOGD3DERROR("Failed to create depth-stencil view for texture", hr);
            URHO3D_SAFE_RELEASE(renderSurface_->renderTargetView_);
            return false;
        }

        // Create also a read-only version of the view for simultaneous depth testing and sampling in shader
        // Requires feature level 11
        if (graphics_->GetImpl_D3D11()->GetDevice()->GetFeatureLevel() >= D3D_FEATURE_LEVEL_11_0)
        {
            depthStencilViewDesc.Flags = D3D11_DSV_READ_ONLY_DEPTH;
            hr = graphics_->GetImpl_D3D11()->GetDevice()->CreateDepthStencilView((ID3D11Resource*)object_.ptr_, &depthStencilViewDesc,
                (ID3D11DepthStencilView**)&renderSurface_->readOnlyView_);
            if (FAILED(hr))
            {
                URHO3D_LOGD3DERROR("Failed to create read-only depth-stencil view for texture", hr);
                URHO3D_SAFE_RELEASE(renderSurface_->readOnlyView_);
            }
        }
    }

    return true;
}

}
