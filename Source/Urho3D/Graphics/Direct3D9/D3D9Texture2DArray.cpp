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

void Texture2DArray::OnDeviceLost()
{
    if (usage_ > TEXTURE_STATIC)
        Release();
}

void Texture2DArray::OnDeviceReset()
{
    if (usage_ > TEXTURE_STATIC || !object_.ptr_ || dataPending_)
    {
        // If has a resource file, reload through the resource cache. Otherwise just recreate.
        ResourceCache* cache = GetSubsystem<ResourceCache>();
        if (cache->Exists(GetName()))
            dataLost_ = !cache->ReloadResource(this);

        if (!object_.ptr_)
        {
            Create();
            dataLost_ = true;
        }
    }

    dataPending_ = false;
}

void Texture2DArray::Release()
{
    if (graphics_)
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
}

bool Texture2DArray::SetData(unsigned layer, unsigned level, int x, int y, int width, int height, const void* data)
{
    URHO3D_LOGERROR("Texture2DArray not supported on Direct3D9, can not set data");
    return false;
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
    MaterialQuality quality = QUALITY_HIGH;
    Renderer* renderer = GetSubsystem<Renderer>();
    if (renderer)
        quality = renderer->GetTextureQuality();

    if (!image->IsCompressed())
    {
        unsigned char* levelData = image->GetData();
        int levelWidth = image->GetWidth();
        int levelHeight = image->GetHeight();
        unsigned components = image->GetComponents();
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
            if (!object_.ptr_)
            {
                // Do not spam this error on D3D9
                //URHO3D_LOGERROR("Texture array layer 0 must be loaded first");
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
            if (!object_.ptr_)
            {
                //URHO3D_LOGERROR("Texture array layer 0 must be loaded first");
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
    URHO3D_LOGERROR("Texture2DArray not supported on Direct3D9, can not get data");
    return false;
}

bool Texture2DArray::Create()
{
    Release();

    if (!graphics_ || !width_ || !height_ || !layers_)
        return false;

    URHO3D_LOGERROR("Texture2DArray not supported on Direct3D9, can not create");
    return false;
}

}
