//
// Copyright (c) 2008-2015 the Urho3D project.
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

Texture3D::Texture3D(Context* context) :
    Texture(context)
{
#ifndef GL_ES_VERSION_2_0
    target_ = GL_TEXTURE_3D;
#else
    target_ = 0;
#endif
}

Texture3D::~Texture3D()
{
    Release();
}

void Texture3D::RegisterObject(Context* context)
{
    context->RegisterFactory<Texture3D>();
}

bool Texture3D::BeginLoad(Deserializer& source)
{
    ResourceCache* cache = GetSubsystem<ResourceCache>();

    // In headless mode, do not actually load the texture, just return success
    if (!graphics_)
        return true;

    // If device is lost, retry later
    if (graphics_->IsDeviceLost())
    {
        URHO3D_LOGWARNING("Texture load while device is lost");
        dataPending_ = true;
        return true;
    }

    String texPath, texName, texExt;
    SplitPath(GetName(), texPath, texName, texExt);

    cache->ResetDependencies(this);

    loadParameters_ = new XMLFile(context_);
    if (!loadParameters_->Load(source))
    {
        loadParameters_.Reset();
        return false;
    }

    XMLElement textureElem = loadParameters_->GetRoot();
    XMLElement volumeElem = textureElem.GetChild("volume");
    XMLElement colorlutElem = textureElem.GetChild("colorlut");

    if (volumeElem)
    {
        String name = volumeElem.GetAttribute("name");

        String volumeTexPath, volumeTexName, volumeTexExt;
        SplitPath(name, volumeTexPath, volumeTexName, volumeTexExt);
        // If path is empty, add the XML file path
        if (volumeTexPath.Empty())
            name = texPath + name;

        loadImage_ = cache->GetTempResource<Image>(name);
        // Precalculate mip levels if async loading
        if (loadImage_ && GetAsyncLoadState() == ASYNC_LOADING)
            loadImage_->PrecalculateLevels();
        cache->StoreResourceDependency(this, name);
        return true;
    }
    else if (colorlutElem)
    {
        String name = colorlutElem.GetAttribute("name");

        String colorlutTexPath, colorlutTexName, colorlutTexExt;
        SplitPath(name, colorlutTexPath, colorlutTexName, colorlutTexExt);
        // If path is empty, add the XML file path
        if (colorlutTexPath.Empty())
            name = texPath + name;

        SharedPtr<File> file = GetSubsystem<ResourceCache>()->GetFile(name);
        loadImage_ = new Image(context_);
        if (!loadImage_->LoadColorLUT(*(file.Get())))
        {
            loadParameters_.Reset();
            loadImage_.Reset();
            return false;
        }
        // Precalculate mip levels if async loading
        if (loadImage_ && GetAsyncLoadState() == ASYNC_LOADING)
            loadImage_->PrecalculateLevels();
        cache->StoreResourceDependency(this, name);
        return true;
    }

    URHO3D_LOGERROR("Texture3D XML data for " + GetName() + " did not contain either volume or colorlut element");
    return false;
}


bool Texture3D::EndLoad()
{
    // In headless mode, do not actually load the texture, just return success
    if (!graphics_ || graphics_->IsDeviceLost())
        return true;

    // If over the texture budget, see if materials can be freed to allow textures to be freed
    CheckTextureBudget(GetTypeStatic());

    SetParameters(loadParameters_);
    bool success = SetData(loadImage_);

    loadImage_.Reset();
    loadParameters_.Reset();

    return success;
}

void Texture3D::OnDeviceLost()
{
    GPUObject::OnDeviceLost();

    if (renderSurface_)
        renderSurface_->OnDeviceLost();
}

void Texture3D::OnDeviceReset()
{
    if (!object_ || dataPending_)
    {
        // If has a resource file, reload through the resource cache. Otherwise just recreate.
        ResourceCache* cache = GetSubsystem<ResourceCache>();
        if (cache->Exists(GetName()))
            dataLost_ = !cache->ReloadResource(this);

        if (!object_)
        {
            Create();
            dataLost_ = true;
        }
    }

    dataPending_ = false;
}

void Texture3D::Release()
{
    if (object_)
    {
        if (!graphics_ || graphics_->IsDeviceLost())
            return;

        for (unsigned i = 0; i < MAX_TEXTURE_UNITS; ++i)
        {
            if (graphics_->GetTexture(i) == this)
                graphics_->SetTexture(i, 0);
        }

        if (renderSurface_)
            renderSurface_->Release();

        glDeleteTextures(1, &object_);
        object_ = 0;
    }
    else
    {
        if (renderSurface_)
            renderSurface_->Release();
    }
}

bool Texture3D::SetSize(int width, int height, int depth, unsigned format, TextureUsage usage)
{
    // Delete the old rendersurface if any
    renderSurface_.Reset();

    usage_ = usage;

    if (usage >= TEXTURE_RENDERTARGET)
    {
        renderSurface_ = new RenderSurface(this);

        // Clamp mode addressing by default, nearest filtering, and mipmaps disabled
        addressMode_[COORD_U] = ADDRESS_CLAMP;
        addressMode_[COORD_V] = ADDRESS_CLAMP;
        filterMode_ = FILTER_NEAREST;
        requestedLevels_ = 1;
    }

    if (usage == TEXTURE_RENDERTARGET)
        SubscribeToEvent(E_RENDERSURFACEUPDATE, URHO3D_HANDLER(Texture3D, HandleRenderSurfaceUpdate));
    else
        UnsubscribeFromEvent(E_RENDERSURFACEUPDATE);

    width_ = width;
    height_ = height;
    depth_ = depth;
    format_ = format;

    return Create();
}

bool Texture3D::SetData(unsigned level, int x, int y, int z, int width, int height, int depth, const void* data)
{
    URHO3D_PROFILE(SetTextureData);

    if (!object_ || !graphics_)
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

    if (graphics_->IsDeviceLost())
    {
        URHO3D_LOGWARNING("Texture data assignment while device is lost");
        dataPending_ = true;
        return true;
    }

    if (IsCompressed())
    {
        x &= ~3;
        y &= ~3;
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

    graphics_->SetTextureForUpdate(this);

#ifndef GL_ES_VERSION_2_0
    bool wholeLevel = x == 0 && y == 0 && z == 0 && width == levelWidth && height == levelHeight && depth == levelDepth;
    unsigned format = GetSRGB() ? GetSRGBFormat(format_) : format_;

    if (!IsCompressed())
    {
        if (wholeLevel)
            glTexImage3D(target_, level, format, width, height, depth, 0, GetExternalFormat(format_), GetDataType(format_), data);
        else
            glTexSubImage3D(target_, level, x, y, z, width, height, depth, GetExternalFormat(format_), GetDataType(format_), data);
    }
    else
    {
        if (wholeLevel)
            glCompressedTexImage3D(target_, level, format, width, height, depth, 0, GetDataSize(width, height, depth), data);
        else
            glCompressedTexSubImage3D(target_, level, x, y, z, width, height, depth, format, GetDataSize(width, height, depth),
                data);
    }
#endif

    graphics_->SetTexture(0, 0);
    return true;
}

bool Texture3D::SetData(SharedPtr<Image> image, bool useAlpha)
{
    if (!image)
    {
        URHO3D_LOGERROR("Null image, can not set data");
        return false;
    }

    unsigned memoryUse = sizeof(Texture3D);

    int quality = QUALITY_HIGH;
    Renderer* renderer = GetSubsystem<Renderer>();
    if (renderer)
        quality = renderer->GetTextureQuality();

    if (!image->IsCompressed())
    {
        // Convert unsuitable formats to RGBA
        unsigned components = image->GetComponents();
        if (Graphics::GetGL3Support() && ((components == 1 && !useAlpha) || components == 2))
        {
            image = image->ConvertToRGBA();
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
            image = image->GetNextLevel();
            levelData = image->GetData();
            levelWidth = image->GetWidth();
            levelHeight = image->GetHeight();
            levelDepth = image->GetDepth();
        }

        switch (components)
        {
        case 1:
            format = useAlpha ? Graphics::GetAlphaFormat() : Graphics::GetLuminanceFormat();
            break;

        case 2:
            format = Graphics::GetLuminanceAlphaFormat();
            break;

        case 3:
            format = Graphics::GetRGBFormat();
            break;

        case 4:
            format = Graphics::GetRGBAFormat();
            break;

        default:
            assert(false);  // Should not reach here
            break;
        }

        // If image was previously compressed, reset number of requested levels to avoid error if level count is too high for new size
        if (IsCompressed() && requestedLevels_ > 1)
            requestedLevels_ = 0;
        SetSize(levelWidth, levelHeight, levelDepth, format);
        if (!object_)
            return false;

        for (unsigned i = 0; i < levels_; ++i)
        {
            SetData(i, 0, 0, 0, levelWidth, levelHeight, levelDepth, levelData);
            memoryUse += levelWidth * levelHeight * levelDepth * components;

            if (i < levels_ - 1)
            {
                image = image->GetNextLevel();
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

        SetNumLevels((unsigned)Max((int)(levels - mipsToSkip), 1));
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
#ifndef GL_ES_VERSION_2_0
    if (!object_ || !graphics_)
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

    if (graphics_->IsDeviceLost())
    {
        URHO3D_LOGWARNING("Getting texture data while device is lost");
        return false;
    }

    graphics_->SetTextureForUpdate(const_cast<Texture3D*>(this));

    if (!IsCompressed())
        glGetTexImage(target_, level, GetExternalFormat(format_), GetDataType(format_), dest);
    else
        glGetCompressedTexImage(target_, level, dest);

    graphics_->SetTexture(0, 0);
    return true;
#else
    URHO3D_LOGERROR("Getting texture data not supported");
    return false;
#endif
}

bool Texture3D::Create()
{
    Release();

#ifdef GL_ES_VERSION_2_0
    URHO3D_LOGERROR("Failed to create 3D texture, currently unsupported on OpenGL ES 2");
    return false;
#else
    if (!graphics_ || !width_ || !height_ || !depth_)
        return false;

    if (graphics_->IsDeviceLost())
    {
        URHO3D_LOGWARNING("Texture creation while device is lost");
        return true;
    }

    unsigned format = GetSRGB() ? GetSRGBFormat(format_) : format_;
    unsigned externalFormat = GetExternalFormat(format_);
    unsigned dataType = GetDataType(format_);

    glGenTextures(1, &object_);

    // Ensure that our texture is bound to OpenGL texture unit 0
    graphics_->SetTextureForUpdate(this);

    // If not compressed, create the initial level 0 texture with null data
    bool success = true;

    if (!IsCompressed())
    {
        glGetError();
        glTexImage3D(target_, 0, format, width_, height_, depth_, 0, externalFormat, dataType, 0);
        if (glGetError())
        {
            URHO3D_LOGERROR("Failed to create texture");
            success = false;
        }
    }

    // Set mipmapping
    levels_ = requestedLevels_;
    if (!levels_)
    {
        unsigned maxSize = (unsigned)Max(Max((int)width_, (int)height_), (int)depth_);
        while (maxSize)
        {
            maxSize >>= 1;
            ++levels_;
        }
    }

    glTexParameteri(target_, GL_TEXTURE_BASE_LEVEL, 0);
    glTexParameteri(target_, GL_TEXTURE_MAX_LEVEL, levels_ - 1);

    // Set initial parameters, then unbind the texture
    UpdateParameters();
    graphics_->SetTexture(0, 0);

    return success;
#endif
}

void Texture3D::HandleRenderSurfaceUpdate(StringHash eventType, VariantMap& eventData)
{
    if (renderSurface_ && renderSurface_->GetUpdateMode() == SURFACE_UPDATEALWAYS)
        renderSurface_->QueueUpdate();
}

}
