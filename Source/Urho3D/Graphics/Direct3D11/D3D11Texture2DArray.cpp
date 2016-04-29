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

#include "../../Core/Context.h"
#include "../../Core/Profiler.h"
#include "../../Graphics/Graphics.h"
#include "../../Graphics/GraphicsEvents.h"
#include "../../Graphics/GraphicsImpl.h"
#include "../../Graphics/Renderer.h"
#include "../../Graphics/Texture2DArray.h"
#include "../../IO/FileSystem.h"
#include "../../IO/Log.h"
#include "../../Resource/ResourceCache.h"
#include "../../Resource/XMLFile.h"

#include "../../DebugNew.h"

#ifdef _MSC_VER
#pragma warning(disable:4355)
#endif

namespace Urho3D
{

Texture2DArray::Texture2DArray(Context* context) :
    Texture(context),
    layers_(0),
    lockedLevel_(-1)
{
}

Texture2DArray::~Texture2DArray()
{
    Release();
}

void Texture2DArray::RegisterObject(Context* context)
{
    context->RegisterFactory<Texture2DArray>();
}

bool Texture2DArray::BeginLoad(Deserializer& source)
{
    ResourceCache* cache = GetSubsystem<ResourceCache>();

    // In headless mode, do not actually load the texture, just return success
    if (!graphics_)
        return true;

    cache->ResetDependencies(this);

    String texPath, texName, texExt;
    SplitPath(GetName(), texPath, texName, texExt);

    loadParameters_ = (new XMLFile(context_));
    if (!loadParameters_->Load(source))
    {
        loadParameters_.Reset();
        return false;
    }

    loadImages_.Clear();

    XMLElement textureElem = loadParameters_->GetRoot();
    XMLElement layerElem = textureElem.GetChild("layer");
    while (layerElem)
    {
        String name = layerElem.GetAttribute("name");

        // If path is empty, add the XML file path
        if (GetPath(name).Empty())
            name = texPath + name;

        loadImages_.Push(cache->GetTempResource<Image>(name));
        cache->StoreResourceDependency(this, name);

        layerElem = layerElem.GetNext("layer");
    }

    // Precalculate mip levels if async loading
    if (GetAsyncLoadState() == ASYNC_LOADING)
    {
        for (unsigned i = 0; i < loadImages_.Size(); ++i)
        {
            if (loadImages_[i])
                loadImages_[i]->PrecalculateLevels();
        }
    }

    return true;
}

bool Texture2DArray::EndLoad()
{
    // In headless mode, do not actually load the texture, just return success
    if (!graphics_)
        return true;

    // If over the texture budget, see if materials can be freed to allow textures to be freed
    CheckTextureBudget(GetTypeStatic());

    SetParameters(loadParameters_);
    SetLayers(loadImages_.Size());

    for (unsigned i = 0; i < loadImages_.Size(); ++i)
        SetData(i, loadImages_[i]);

    loadImages_.Clear();
    loadParameters_.Reset();

    return true;
}

void Texture2DArray::Release()
{
    if (graphics_)
    {
        for (unsigned i = 0; i < MAX_TEXTURE_UNITS; ++i)
        {
            if (graphics_->GetTexture(i) == this)
                graphics_->SetTexture(i, 0);
        }
    }

    if (renderSurface_)
        renderSurface_->Release();

    URHO3D_SAFE_RELEASE(object_);
    URHO3D_SAFE_RELEASE(shaderResourceView_);
    URHO3D_SAFE_RELEASE(sampler_);
}

void Texture2DArray::SetLayers(unsigned layers)
{
    Release();

    layers_ = layers;
}

bool Texture2DArray::SetSize(unsigned layers, int width, int height, unsigned format, TextureUsage usage)
{
    if (width <= 0 || height <= 0)
    {
        URHO3D_LOGERROR("Zero or negative texture array size");
        return false;
    }
    if (usage == TEXTURE_DEPTHSTENCIL)
    {
        URHO3D_LOGERROR("Depth-stencil usage not supported for texture arrays");
        return false;
    }

    // Delete the old rendersurfaces if any
    renderSurface_.Reset();

    usage_ = usage;

    if (usage_ == TEXTURE_RENDERTARGET)
    {
        renderSurface_ = new RenderSurface(this);

        // Nearest filtering and mipmaps disabled by default
        filterMode_ = FILTER_NEAREST;
        requestedLevels_ = 1;
    }
    else if (usage_ == TEXTURE_DYNAMIC)
        requestedLevels_ = 1;

    if (usage_ == TEXTURE_RENDERTARGET)
        SubscribeToEvent(E_RENDERSURFACEUPDATE, URHO3D_HANDLER(Texture2DArray, HandleRenderSurfaceUpdate));
    else
        UnsubscribeFromEvent(E_RENDERSURFACEUPDATE);

    width_ = width;
    height_ = height;
    format_ = format;
    if (layers)
        layers_ = layers;

    layerMemoryUse_.Resize(layers_);
    for (unsigned i = 0; i < layers_; ++i)
        layerMemoryUse_[i] = 0;

    return Create();
}

bool Texture2DArray::SetData(unsigned layer, unsigned level, int x, int y, int width, int height, const void* data)
{
    URHO3D_PROFILE(SetTextureData);

    if (!object_)
    {
        URHO3D_LOGERROR("Texture array not created, can not set data");
        return false;
    }

    if (!data)
    {
        URHO3D_LOGERROR("Null source for setting data");
        return false;
    }

    if (layer >= layers_)
    {
        URHO3D_LOGERROR("Illegal layer for setting data");
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
    unsigned subResource = D3D11CalcSubresource(level, layer, levels_);

    if (usage_ == TEXTURE_DYNAMIC)
    {
        if (IsCompressed())
        {
            height = (height + 3) >> 2;
            y >>= 2;
        }

        D3D11_MAPPED_SUBRESOURCE mappedData;
        mappedData.pData = 0;

        HRESULT hr = graphics_->GetImpl()->GetDeviceContext()->Map((ID3D11Resource*)object_, subResource, D3D11_MAP_WRITE_DISCARD, 0,
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
            graphics_->GetImpl()->GetDeviceContext()->Unmap((ID3D11Resource*)object_, subResource);
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

        graphics_->GetImpl()->GetDeviceContext()->UpdateSubresource((ID3D11Resource*)object_, subResource, &destBox, data,
            rowSize, 0);
    }

    return true;
}

bool Texture2DArray::SetData(unsigned layer, Deserializer& source)
{
    SharedPtr<Image> image(new Image(context_));
    if (!image->Load(source))
        return false;

    return SetData(layer, image);
}

bool Texture2DArray::SetData(unsigned layer, Image* image, bool useAlpha)
{
    if (!image)
    {
        URHO3D_LOGERROR("Null image, can not set data");
        return false;
    }
    if (!layers_)
    {
        URHO3D_LOGERROR("Number of layers in the array must be set first");
        return false;
    }
    if (layer >= layers_)
    {
        URHO3D_LOGERROR("Illegal layer for setting data");
        return false;
    }

    // Use a shared ptr for managing the temporary mip images created during this function
    SharedPtr<Image> mipImage;
    unsigned memoryUse = 0;
    int quality = QUALITY_HIGH;
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

        // Create the texture array when layer 0 is being loaded, check that rest of the layers are same size & format
        if (!layer)
        {
            // If image was previously compressed, reset number of requested levels to avoid error if level count is too high for new size
            if (IsCompressed() && requestedLevels_ > 1)
                requestedLevels_ = 0;
            // Create the texture array (the number of layers must have been already set)
            SetSize(0, levelWidth, levelHeight, format);
        }
        else
        {
            if (!object_)
            {
                URHO3D_LOGERROR("Texture array layer 0 must be loaded first");
                return false;
            }
            if (levelWidth != width_ || levelHeight != height_ || format != format_)
            {
                URHO3D_LOGERROR("Texture array layer does not match size or format of layer 0");
                return false;
            }
        }

        for (unsigned i = 0; i < levels_; ++i)
        {
            SetData(layer, i, 0, 0, levelWidth, levelHeight, levelData);
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

        // Create the texture array when layer 0 is being loaded, assume rest of the layers are same size & format
        if (!layer)
        {
            SetNumLevels(Max((levels - mipsToSkip), 1U));
            SetSize(0, width, height, format);
        }
        else
        {
            if (!object_)
            {
                URHO3D_LOGERROR("Texture array layer 0 must be loaded first");
                return false;
            }
            if (width != width_ || height != height_ || format != format_)
            {
                URHO3D_LOGERROR("Texture array layer does not match size or format of layer 0");
                return false;
            }
        }

        for (unsigned i = 0; i < levels_ && i < levels - mipsToSkip; ++i)
        {
            CompressedLevel level = image->GetCompressedLevel(i + mipsToSkip);
            if (!needDecompress)
            {
                SetData(layer, i, 0, 0, level.width_, level.height_, level.data_);
                memoryUse += level.rows_ * level.rowSize_;
            }
            else
            {
                unsigned char* rgbaData = new unsigned char[level.width_ * level.height_ * 4];
                level.Decompress(rgbaData);
                SetData(layer, i, 0, 0, level.width_, level.height_, rgbaData);
                memoryUse += level.width_ * level.height_ * 4;
                delete[] rgbaData;
            }
        }
    }

    layerMemoryUse_[layer] = memoryUse;
    unsigned totalMemoryUse = sizeof(Texture2DArray) + layerMemoryUse_.Capacity() * sizeof(unsigned);
    for (unsigned i = 0; i < layers_; ++i)
        totalMemoryUse += layerMemoryUse_[i];
    SetMemoryUse(totalMemoryUse);

    return true;
}

bool Texture2DArray::GetData(unsigned layer, unsigned level, void* dest) const
{
    if (!object_)
    {
        URHO3D_LOGERROR("Texture array not created, can not get data");
        return false;
    }

    if (!dest)
    {
        URHO3D_LOGERROR("Null destination for getting data");
        return false;
    }

    if (layer >= layers_)
    {
        URHO3D_LOGERROR("Illegal layer for getting data");
        return false;
    }

    if (level >= levels_)
    {
        URHO3D_LOGERROR("Illegal mip level for getting data");
        return false;
    }

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

    ID3D11Texture2D* stagingTexture = 0;
    HRESULT hr = graphics_->GetImpl()->GetDevice()->CreateTexture2D(&textureDesc, 0, &stagingTexture);
    if (FAILED(hr))
    {
        URHO3D_SAFE_RELEASE(stagingTexture);
        URHO3D_LOGD3DERROR("Failed to create staging texture for GetData", hr);
        return false;
    }

    unsigned srcSubResource = D3D11CalcSubresource(level, layer, levels_);
    D3D11_BOX srcBox;
    srcBox.left = 0;
    srcBox.right = (UINT)levelWidth;
    srcBox.top = 0;
    srcBox.bottom = (UINT)levelHeight;
    srcBox.front = 0;
    srcBox.back = 1;
    graphics_->GetImpl()->GetDeviceContext()->CopySubresourceRegion(stagingTexture, 0, 0, 0, 0, (ID3D11Resource*)object_,
        srcSubResource, &srcBox);

    D3D11_MAPPED_SUBRESOURCE mappedData;
    mappedData.pData = 0;
    unsigned rowSize = GetRowDataSize(levelWidth);
    unsigned numRows = (unsigned)(IsCompressed() ? (levelHeight + 3) >> 2 : levelHeight);

    hr = graphics_->GetImpl()->GetDeviceContext()->Map((ID3D11Resource*)stagingTexture, 0, D3D11_MAP_READ, 0, &mappedData);
    if (FAILED(hr) || !mappedData.pData)
    {
        URHO3D_LOGD3DERROR("Failed to map staging texture for GetData", hr);
        stagingTexture->Release();
        return false;
    }
    else
    {
        for (unsigned row = 0; row < numRows; ++row)
            memcpy((unsigned char*)dest + row * rowSize, (unsigned char*)mappedData.pData + row * mappedData.RowPitch, rowSize);
        graphics_->GetImpl()->GetDeviceContext()->Unmap((ID3D11Resource*)stagingTexture, 0);
        stagingTexture->Release();
        return true;
    }
}

bool Texture2DArray::Create()
{
    Release();

    if (!graphics_ || !width_ || !height_ || !layers_)
        return false;

    levels_ = CheckMaxLevels(width_, height_, requestedLevels_);

    D3D11_TEXTURE2D_DESC textureDesc;
    memset(&textureDesc, 0, sizeof textureDesc);
    textureDesc.Width = (UINT)width_;
    textureDesc.Height = (UINT)height_;
    textureDesc.MipLevels = levels_;
    textureDesc.ArraySize = layers_;
    textureDesc.Format = (DXGI_FORMAT)(sRGB_ ? GetSRGBFormat(format_) : format_);
    textureDesc.SampleDesc.Count = 1;
    textureDesc.SampleDesc.Quality = 0;
    textureDesc.Usage = usage_ == TEXTURE_DYNAMIC ? D3D11_USAGE_DYNAMIC : D3D11_USAGE_DEFAULT;
    textureDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
    if (usage_ == TEXTURE_RENDERTARGET)
        textureDesc.BindFlags |= D3D11_BIND_RENDER_TARGET;
    else if (usage_ == TEXTURE_DEPTHSTENCIL)
        textureDesc.BindFlags |= D3D11_BIND_DEPTH_STENCIL;
    textureDesc.CPUAccessFlags = usage_ == TEXTURE_DYNAMIC ? D3D11_CPU_ACCESS_WRITE : 0;

    HRESULT hr = graphics_->GetImpl()->GetDevice()->CreateTexture2D(&textureDesc, 0, (ID3D11Texture2D**)&object_);
    if (FAILED(hr))
    {
        URHO3D_SAFE_RELEASE(object_);
        URHO3D_LOGD3DERROR("Failed to create texture array", hr);
        return false;
    }

    D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
    memset(&srvDesc, 0, sizeof srvDesc);
    srvDesc.Format = (DXGI_FORMAT)GetSRVFormat(textureDesc.Format);
    if (layers_ == 1)
    {
        srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
        srvDesc.Texture2D.MipLevels = (UINT)levels_;
        srvDesc.Texture2D.MostDetailedMip = 0;
    }
    else
    {
        srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2DARRAY;
        srvDesc.Texture2DArray.MipLevels = (UINT)levels_;
        srvDesc.Texture2DArray.ArraySize = layers_;
        srvDesc.Texture2DArray.FirstArraySlice = 0;
        srvDesc.Texture2DArray.MostDetailedMip = 0;
    }

    hr = graphics_->GetImpl()->GetDevice()->CreateShaderResourceView((ID3D11Resource*)object_, &srvDesc,
        (ID3D11ShaderResourceView**)&shaderResourceView_);
    if (FAILED(hr))
    {
        URHO3D_SAFE_RELEASE(shaderResourceView_);
        URHO3D_LOGD3DERROR("Failed to create shader resource view for texture array", hr);
        return false;
    }

    if (usage_ == TEXTURE_RENDERTARGET)
    {
        D3D11_RENDER_TARGET_VIEW_DESC renderTargetViewDesc;
        memset(&renderTargetViewDesc, 0, sizeof renderTargetViewDesc);
        renderTargetViewDesc.Format = textureDesc.Format;
        if (layers_ == 1)
        {
            renderTargetViewDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
            renderTargetViewDesc.Texture2D.MipSlice = 0;
        }
        else
        {
            renderTargetViewDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2DARRAY;
            renderTargetViewDesc.Texture2DArray.MipSlice = 0;
            renderTargetViewDesc.Texture2DArray.ArraySize = layers_;
            renderTargetViewDesc.Texture2DArray.FirstArraySlice = 0;
        }

        hr = graphics_->GetImpl()->GetDevice()->CreateRenderTargetView((ID3D11Resource*)object_, &renderTargetViewDesc,
            (ID3D11RenderTargetView**)&renderSurface_->renderTargetView_);

        if (FAILED(hr))
        {
            URHO3D_SAFE_RELEASE(renderSurface_->renderTargetView_);
            URHO3D_LOGD3DERROR("Failed to create rendertarget view for texture array", hr);
            return false;
        }
    }

    return true;
}

void Texture2DArray::HandleRenderSurfaceUpdate(StringHash eventType, VariantMap& eventData)
{
    if (renderSurface_ && (renderSurface_->GetUpdateMode() == SURFACE_UPDATEALWAYS || renderSurface_->IsUpdateQueued()))
    {
        Renderer* renderer = GetSubsystem<Renderer>();
        if (renderer)
            renderer->QueueRenderSurface(renderSurface_);
        renderSurface_->ResetUpdateQueued();
    }
}

}
