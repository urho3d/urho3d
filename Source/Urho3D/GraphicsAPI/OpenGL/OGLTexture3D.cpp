// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

#include "../../Precompiled.h"

#include "../../Core/Context.h"
#include "../../Core/Profiler.h"
#include "../../Graphics/Graphics.h"
#include "../../Graphics/GraphicsEvents.h"
#include "../../Graphics/Renderer.h"
#include "../../GraphicsAPI/GraphicsImpl.h"
#include "../../GraphicsAPI/Texture3D.h"
#include "../../IO/FileSystem.h"
#include "../../IO/Log.h"
#include "../../Resource/ResourceCache.h"
#include "../../Resource/XMLFile.h"

#include "../../DebugNew.h"

namespace Urho3D
{

void Texture3D::OnDeviceLost_OGL()
{
    if (object_.name_ && !graphics_->IsDeviceLost())
        glDeleteTextures(1, &object_.name_);

    GPUObject::OnDeviceLost();
}

void Texture3D::OnDeviceReset_OGL()
{
    if (!object_.name_ || dataPending_)
    {
        // If has a resource file, reload through the resource cache. Otherwise just recreate.
        auto* cache = GetSubsystem<ResourceCache>();
        if (cache->Exists(GetName()))
            dataLost_ = !cache->ReloadResource(this);

        if (!object_.name_)
        {
            Create_OGL();
            dataLost_ = true;
        }
    }

    dataPending_ = false;
}

void Texture3D::Release_OGL()
{
    if (object_.name_)
    {
        if (!graphics_ || graphics_->IsDeviceLost())
            return;

        for (unsigned i = 0; i < MAX_TEXTURE_UNITS; ++i)
        {
            if (graphics_->GetTexture(i) == this)
                graphics_->SetTexture(i, nullptr);
        }

        glDeleteTextures(1, &object_.name_);
        object_.name_ = 0;
    }
}

bool Texture3D::SetData_OGL(unsigned level, int x, int y, int z, int width, int height, int depth, const void* data)
{
    URHO3D_PROFILE(SetTextureData);

    if (!object_.name_ || !graphics_)
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

    if (IsCompressed_OGL())
    {
        x &= ~3u;
        y &= ~3u;
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

    graphics_->SetTextureForUpdate_OGL(this);

#ifndef GL_ES_VERSION_2_0
    bool wholeLevel = x == 0 && y == 0 && z == 0 && width == levelWidth && height == levelHeight && depth == levelDepth;
    unsigned format = GetSRGB() ? GetSRGBFormat_OGL(format_) : format_;

    if (!IsCompressed_OGL())
    {
        if (wholeLevel)
            glTexImage3D(target_, level, format, width, height, depth, 0, GetExternalFormat_OGL(format_), GetDataType_OGL(format_), data);
        else
            glTexSubImage3D(target_, level, x, y, z, width, height, depth, GetExternalFormat_OGL(format_), GetDataType_OGL(format_), data);
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

    graphics_->SetTexture(0, nullptr);
    return true;
}

bool Texture3D::SetData_OGL(Image* image, bool useAlpha)
{
    if (!image)
    {
        URHO3D_LOGERROR("Null image, can not set data");
        return false;
    }

    // Use a shared ptr for managing the temporary mip images created during this function
    SharedPtr<Image> mipImage;
    unsigned memoryUse = sizeof(Texture3D);
    MaterialQuality quality = QUALITY_HIGH;
    auto* renderer = GetSubsystem<Renderer>();
    if (renderer)
        quality = renderer->GetTextureQuality();

    if (!image->IsCompressed())
    {
        // Convert unsuitable formats to RGBA
        unsigned components = image->GetComponents();
        if (Graphics::GetGL3Support() && ((components == 1 && !useAlpha) || components == 2))
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
        if (IsCompressed_OGL() && requestedLevels_ > 1)
            requestedLevels_ = 0;
        SetSize(levelWidth, levelHeight, levelDepth, format);
        if (!object_.name_)
            return false;

        for (unsigned i = 0; i < levels_; ++i)
        {
            SetData_OGL(i, 0, 0, 0, levelWidth, levelHeight, levelDepth, levelData);
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
        while (mipsToSkip && (width / (1u << mipsToSkip) < 4 || height / (1u << mipsToSkip) < 4 || depth / (1u << mipsToSkip) < 4))
            --mipsToSkip;
        width /= (1u << mipsToSkip);
        height /= (1u << mipsToSkip);
        depth /= (1u << mipsToSkip);

        SetNumLevels(Max((levels - mipsToSkip), 1U));
        SetSize(width, height, depth, format);

        for (unsigned i = 0; i < levels_ && i < levels - mipsToSkip; ++i)
        {
            CompressedLevel level = image->GetCompressedLevel(i + mipsToSkip);
            if (!needDecompress)
            {
                SetData_OGL(i, 0, 0, 0, level.width_, level.height_, level.depth_, level.data_);
                memoryUse += level.depth_ * level.rows_ * level.rowSize_;
            }
            else
            {
                auto* rgbaData = new unsigned char[level.width_ * level.height_ * level.depth_ * 4];
                level.Decompress(rgbaData);
                SetData_OGL(i, 0, 0, 0, level.width_, level.height_, level.depth_, rgbaData);
                memoryUse += level.width_ * level.height_ * level.depth_ * 4;
                delete[] rgbaData;
            }
        }
    }

    SetMemoryUse(memoryUse);
    return true;
}

bool Texture3D::GetData_OGL(unsigned level, void* dest) const
{
#ifndef GL_ES_VERSION_2_0
    if (!object_.name_ || !graphics_)
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

    graphics_->SetTextureForUpdate_OGL(const_cast<Texture3D*>(this));

    if (!IsCompressed_OGL())
        glGetTexImage(target_, level, GetExternalFormat_OGL(format_), GetDataType_OGL(format_), dest);
    else
        glGetCompressedTexImage(target_, level, dest);

    graphics_->SetTexture(0, nullptr);
    return true;
#else
    URHO3D_LOGERROR("Getting texture data not supported");
    return false;
#endif
}

bool Texture3D::Create_OGL()
{
    Release_OGL();

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

    unsigned format = GetSRGB() ? GetSRGBFormat_OGL(format_) : format_;
    unsigned externalFormat = GetExternalFormat_OGL(format_);
    unsigned dataType = GetDataType_OGL(format_);

    glGenTextures(1, &object_.name_);

    // Ensure that our texture is bound to OpenGL texture unit 0
    graphics_->SetTextureForUpdate_OGL(this);

    // If not compressed, create the initial level 0 texture with null data
    bool success = true;

    if (!IsCompressed_OGL())
    {
        glGetError();
        glTexImage3D(target_, 0, format, width_, height_, depth_, 0, externalFormat, dataType, nullptr);
        if (glGetError())
        {
            URHO3D_LOGERROR("Failed to create texture");
            success = false;
        }
    }

    // Set mipmapping
    levels_ = CheckMaxLevels(width_, height_, depth_, requestedLevels_);
    glTexParameteri(target_, GL_TEXTURE_BASE_LEVEL, 0);
    glTexParameteri(target_, GL_TEXTURE_MAX_LEVEL, levels_ - 1);

    // Set initial parameters, then unbind the texture
    UpdateParameters();
    graphics_->SetTexture(0, nullptr);

    return success;
#endif
}

}
