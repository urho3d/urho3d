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
#include "../../Graphics/TextureCube.h"
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

static const char* cubeMapLayoutNames[] = {
    "horizontal",
    "horizontalnvidia",
    "horizontalcross",
    "verticalcross",
    "blender",
    0
};

static SharedPtr<Image> GetTileImage(Image* src, int tileX, int tileY, int tileWidth, int tileHeight)
{
    return SharedPtr<Image>(
        src->GetSubimage(IntRect(tileX * tileWidth, tileY * tileHeight, (tileX + 1) * tileWidth, (tileY + 1) * tileHeight)));
}

TextureCube::TextureCube(Context* context) :
    Texture(context)
{
    target_ = GL_TEXTURE_CUBE_MAP;

    // Default to clamp mode addressing
    addressMode_[COORD_U] = ADDRESS_CLAMP;
    addressMode_[COORD_V] = ADDRESS_CLAMP;
    addressMode_[COORD_W] = ADDRESS_CLAMP;

    for (unsigned i = 0; i < MAX_CUBEMAP_FACES; ++i)
        faceMemoryUse_[i] = 0;
}

TextureCube::~TextureCube()
{
    Release();
}

void TextureCube::RegisterObject(Context* context)
{
    context->RegisterFactory<TextureCube>();
}

bool TextureCube::BeginLoad(Deserializer& source)
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
    XMLElement imageElem = textureElem.GetChild("image");
    // Single image and multiple faces with layout
    if (imageElem)
    {
        String name = imageElem.GetAttribute("name");
        // If path is empty, add the XML file path
        if (GetPath(name).Empty())
            name = texPath + name;

        SharedPtr<Image> image = cache->GetTempResource<Image>(name);
        if (!image)
            return false;

        int faceWidth, faceHeight;
        loadImages_.Resize(MAX_CUBEMAP_FACES);

        if (image->IsCubemap())
        {
            loadImages_[FACE_POSITIVE_X] = image;
            loadImages_[FACE_NEGATIVE_X] = loadImages_[FACE_POSITIVE_X]->GetNextSibling();
            loadImages_[FACE_POSITIVE_Y] = loadImages_[FACE_NEGATIVE_X]->GetNextSibling();
            loadImages_[FACE_NEGATIVE_Y] = loadImages_[FACE_POSITIVE_Y]->GetNextSibling();
            loadImages_[FACE_POSITIVE_Z] = loadImages_[FACE_NEGATIVE_Y]->GetNextSibling();
            loadImages_[FACE_NEGATIVE_Z] = loadImages_[FACE_POSITIVE_Z]->GetNextSibling();
        }
        else
        {
        
            CubeMapLayout layout =
                (CubeMapLayout)GetStringListIndex(imageElem.GetAttribute("layout").CString(), cubeMapLayoutNames, CML_HORIZONTAL);
            
            switch (layout)
            {
            case CML_HORIZONTAL:
                faceWidth = image->GetWidth() / MAX_CUBEMAP_FACES;
                faceHeight = image->GetHeight();
                loadImages_[FACE_POSITIVE_Z] = GetTileImage(image, 0, 0, faceWidth, faceHeight);
                loadImages_[FACE_POSITIVE_X] = GetTileImage(image, 1, 0, faceWidth, faceHeight);
                loadImages_[FACE_NEGATIVE_Z] = GetTileImage(image, 2, 0, faceWidth, faceHeight);
                loadImages_[FACE_NEGATIVE_X] = GetTileImage(image, 3, 0, faceWidth, faceHeight);
                loadImages_[FACE_POSITIVE_Y] = GetTileImage(image, 4, 0, faceWidth, faceHeight);
                loadImages_[FACE_NEGATIVE_Y] = GetTileImage(image, 5, 0, faceWidth, faceHeight);
                break;

            case CML_HORIZONTALNVIDIA:
                faceWidth = image->GetWidth() / MAX_CUBEMAP_FACES;
                faceHeight = image->GetHeight();
                for (unsigned i = 0; i < MAX_CUBEMAP_FACES; ++i)
                    loadImages_[i] = GetTileImage(image, i, 0, faceWidth, faceHeight);
                break;

            case CML_HORIZONTALCROSS:
                faceWidth = image->GetWidth() / 4;
                faceHeight = image->GetHeight() / 3;
                loadImages_[FACE_POSITIVE_Y] = GetTileImage(image, 1, 0, faceWidth, faceHeight);
                loadImages_[FACE_NEGATIVE_X] = GetTileImage(image, 0, 1, faceWidth, faceHeight);
                loadImages_[FACE_POSITIVE_Z] = GetTileImage(image, 1, 1, faceWidth, faceHeight);
                loadImages_[FACE_POSITIVE_X] = GetTileImage(image, 2, 1, faceWidth, faceHeight);
                loadImages_[FACE_NEGATIVE_Z] = GetTileImage(image, 3, 1, faceWidth, faceHeight);
                loadImages_[FACE_NEGATIVE_Y] = GetTileImage(image, 1, 2, faceWidth, faceHeight);
                break;

            case CML_VERTICALCROSS:
                faceWidth = image->GetWidth() / 3;
                faceHeight = image->GetHeight() / 4;
                loadImages_[FACE_POSITIVE_Y] = GetTileImage(image, 1, 0, faceWidth, faceHeight);
                loadImages_[FACE_NEGATIVE_X] = GetTileImage(image, 0, 1, faceWidth, faceHeight);
                loadImages_[FACE_POSITIVE_Z] = GetTileImage(image, 1, 1, faceWidth, faceHeight);
                loadImages_[FACE_POSITIVE_X] = GetTileImage(image, 2, 1, faceWidth, faceHeight);
                loadImages_[FACE_NEGATIVE_Y] = GetTileImage(image, 1, 2, faceWidth, faceHeight);
                loadImages_[FACE_NEGATIVE_Z] = GetTileImage(image, 1, 3, faceWidth, faceHeight);
                if (loadImages_[FACE_NEGATIVE_Z])
                {
                    loadImages_[FACE_NEGATIVE_Z]->FlipVertical();
                    loadImages_[FACE_NEGATIVE_Z]->FlipHorizontal();
                }
                break;

            case CML_BLENDER:
                faceWidth = image->GetWidth() / 3;
                faceHeight = image->GetHeight() / 2;
                loadImages_[FACE_NEGATIVE_X] = GetTileImage(image, 0, 0, faceWidth, faceHeight);
                loadImages_[FACE_NEGATIVE_Z] = GetTileImage(image, 1, 0, faceWidth, faceHeight);
                loadImages_[FACE_POSITIVE_X] = GetTileImage(image, 2, 0, faceWidth, faceHeight);
                loadImages_[FACE_NEGATIVE_Y] = GetTileImage(image, 0, 1, faceWidth, faceHeight);
                loadImages_[FACE_POSITIVE_Y] = GetTileImage(image, 1, 1, faceWidth, faceHeight);
                loadImages_[FACE_POSITIVE_Z] = GetTileImage(image, 2, 1, faceWidth, faceHeight);
                break;
            }
        }
    }
    // Face per image
    else
    {
        XMLElement faceElem = textureElem.GetChild("face");
        while (faceElem)
        {
            String name = faceElem.GetAttribute("name");

            // If path is empty, add the XML file path
            if (GetPath(name).Empty())
                name = texPath + name;

            loadImages_.Push(cache->GetTempResource<Image>(name));
            cache->StoreResourceDependency(this, name);

            faceElem = faceElem.GetNext("face");
        }
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

bool TextureCube::EndLoad()
{
    // In headless mode, do not actually load the texture, just return success
    if (!graphics_ || graphics_->IsDeviceLost())
        return true;

    // If over the texture budget, see if materials can be freed to allow textures to be freed
    CheckTextureBudget(GetTypeStatic());

    SetParameters(loadParameters_);

    for (unsigned i = 0; i < loadImages_.Size() && i < MAX_CUBEMAP_FACES; ++i)
        SetData((CubeMapFace)i, loadImages_[i]);

    loadImages_.Clear();
    loadParameters_.Reset();

    return true;
}

void TextureCube::OnDeviceLost()
{
    GPUObject::OnDeviceLost();

    for (unsigned i = 0; i < MAX_CUBEMAP_FACES; ++i)
    {
        if (renderSurfaces_[i])
            renderSurfaces_[i]->OnDeviceLost();
    }
}

void TextureCube::OnDeviceReset()
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

void TextureCube::Release()
{
    if (object_)
    {
        if (!graphics_)
            return;

        if (!graphics_->IsDeviceLost())
        {
            for (unsigned i = 0; i < MAX_TEXTURE_UNITS; ++i)
            {
                if (graphics_->GetTexture(i) == this)
                    graphics_->SetTexture(i, 0);
            }

            glDeleteTextures(1, &object_);
        }

        for (unsigned i = 0; i < MAX_CUBEMAP_FACES; ++i)
        {
            if (renderSurfaces_[i])
                renderSurfaces_[i]->Release();
        }

        object_ = 0;
    }
}

bool TextureCube::SetSize(int size, unsigned format, TextureUsage usage)
{
    if (size <= 0)
    {
        URHO3D_LOGERROR("Zero or negative cube texture size");
        return false;
    }
    if (usage == TEXTURE_DEPTHSTENCIL)
    {
        URHO3D_LOGERROR("Depth-stencil usage not supported for cube maps");
        return false;
    }

    // Delete the old rendersurfaces if any
    for (unsigned i = 0; i < MAX_CUBEMAP_FACES; ++i)
    {
        renderSurfaces_[i].Reset();
        faceMemoryUse_[i] = 0;
    }

    usage_ = usage;

    if (usage == TEXTURE_RENDERTARGET)
    {
        for (unsigned i = 0; i < MAX_CUBEMAP_FACES; ++i)
        {
            renderSurfaces_[i] = new RenderSurface(this);
            renderSurfaces_[i]->SetTarget(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i);
        }

        // Nearest filtering and mipmaps disabled by default
        filterMode_ = FILTER_NEAREST;
        requestedLevels_ = 1;
    }

    if (usage == TEXTURE_RENDERTARGET)
        SubscribeToEvent(E_RENDERSURFACEUPDATE, URHO3D_HANDLER(TextureCube, HandleRenderSurfaceUpdate));
    else
        UnsubscribeFromEvent(E_RENDERSURFACEUPDATE);

    width_ = size;
    height_ = size;
    format_ = format;

    return Create();
}

bool TextureCube::SetData(CubeMapFace face, unsigned level, int x, int y, int width, int height, const void* data)
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
    if (x < 0 || x + width > levelWidth || y < 0 || y + height > levelHeight || width <= 0 || height <= 0)
    {
        URHO3D_LOGERROR("Illegal dimensions for setting data");
        return false;
    }

    graphics_->SetTextureForUpdate(this);

    bool wholeLevel = x == 0 && y == 0 && width == levelWidth && height == levelHeight;
    unsigned format = GetSRGB() ? GetSRGBFormat(format_) : format_;

    if (!IsCompressed())
    {
        if (wholeLevel)
            glTexImage2D((GLenum)(GL_TEXTURE_CUBE_MAP_POSITIVE_X + face), level, format, width, height, 0, GetExternalFormat(format_),
                GetDataType(format_), data);
        else
            glTexSubImage2D((GLenum)(GL_TEXTURE_CUBE_MAP_POSITIVE_X + face), level, x, y, width, height, GetExternalFormat(format_),
                GetDataType(format_), data);
    }
    else
    {
        if (wholeLevel)
            glCompressedTexImage2D((GLenum)(GL_TEXTURE_CUBE_MAP_POSITIVE_X + face), level, format, width, height, 0,
                GetDataSize(width, height), data);
        else
            glCompressedTexSubImage2D((GLenum)(GL_TEXTURE_CUBE_MAP_POSITIVE_X + face), level, x, y, width, height, format,
                GetDataSize(width, height), data);
    }

    graphics_->SetTexture(0, 0);
    return true;
}

bool TextureCube::SetData(CubeMapFace face, Deserializer& source)
{
    SharedPtr<Image> image(new Image(context_));
    if (!image->Load(source))
        return false;

    return SetData(face, image);
}

bool TextureCube::SetData(CubeMapFace face, Image* image, bool useAlpha)
{
    if (!image)
    {
        URHO3D_LOGERROR("Null image, can not set face data");
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
        unsigned format = 0;

        if (levelWidth != levelHeight)
        {
            URHO3D_LOGERROR("Cube texture width not equal to height");
            return false;
        }

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

        // Create the texture when face 0 is being loaded, check that rest of the faces are same size & format
        if (!face)
        {
            // If image was previously compressed, reset number of requested levels to avoid error if level count is too high for new size
            if (IsCompressed() && requestedLevels_ > 1)
                requestedLevels_ = 0;
            SetSize(levelWidth, format);
        }
        else
        {
            if (!object_)
            {
                URHO3D_LOGERROR("Cube texture face 0 must be loaded first");
                return false;
            }
            if (levelWidth != width_ || format != format_)
            {
                URHO3D_LOGERROR("Cube texture face does not match size or format of face 0");
                return false;
            }
        }

        for (unsigned i = 0; i < levels_; ++i)
        {
            SetData(face, i, 0, 0, levelWidth, levelHeight, levelData);
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

        if (width != height)
        {
            URHO3D_LOGERROR("Cube texture width not equal to height");
            return false;
        }

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

        // Create the texture when face 0 is being loaded, assume rest of the faces are same size & format
        if (!face)
        {
            SetNumLevels(Max((levels - mipsToSkip), 1U));
            SetSize(width, format);
        }
        else
        {
            if (!object_)
            {
                URHO3D_LOGERROR("Cube texture face 0 must be loaded first");
                return false;
            }
            if (width != width_ || format != format_)
            {
                URHO3D_LOGERROR("Cube texture face does not match size or format of face 0");
                return false;
            }
        }

        for (unsigned i = 0; i < levels_ && i < levels - mipsToSkip; ++i)
        {
            CompressedLevel level = image->GetCompressedLevel(i + mipsToSkip);
            if (!needDecompress)
            {
                SetData(face, i, 0, 0, level.width_, level.height_, level.data_);
                memoryUse += level.rows_ * level.rowSize_;
            }
            else
            {
                unsigned char* rgbaData = new unsigned char[level.width_ * level.height_ * 4];
                level.Decompress(rgbaData);
                SetData(face, i, 0, 0, level.width_, level.height_, rgbaData);
                memoryUse += level.width_ * level.height_ * 4;
                delete[] rgbaData;
            }
        }
    }

    faceMemoryUse_[face] = memoryUse;
    unsigned totalMemoryUse = sizeof(TextureCube);
    for (unsigned i = 0; i < MAX_CUBEMAP_FACES; ++i)
        totalMemoryUse += faceMemoryUse_[i];
    SetMemoryUse(totalMemoryUse);
    return true;
}

bool TextureCube::GetData(CubeMapFace face, unsigned level, void* dest) const
{
    if (!object_ || !graphics_)
    {
        URHO3D_LOGERROR("No texture created, can not get data");
        return false;
    }

#ifndef GL_ES_VERSION_2_0
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

    graphics_->SetTextureForUpdate(const_cast<TextureCube*>(this));

    if (!IsCompressed())
        glGetTexImage((GLenum)(GL_TEXTURE_CUBE_MAP_POSITIVE_X + face), level, GetExternalFormat(format_), GetDataType(format_), dest);
    else
        glGetCompressedTexImage((GLenum)(GL_TEXTURE_CUBE_MAP_POSITIVE_X + face), level, dest);

    graphics_->SetTexture(0, 0);
    return true;
#else
    // Special case on GLES: if the texture is a rendertarget, can make it current and use glReadPixels()
    if (usage_ == TEXTURE_RENDERTARGET)
    {
        graphics_->SetRenderTarget(0, renderSurfaces_[face]);
        // Ensure the FBO is current; this viewport is actually never rendered to
        graphics_->SetViewport(IntRect(0, 0, width_, height_));
        glReadPixels(0, 0, width_, height_, GetExternalFormat(format_), GetDataType(format_), dest);
        return true;
    }

    URHO3D_LOGERROR("Getting texture data not supported");
    return false;
#endif
}

bool TextureCube::Create()
{
    Release();

    if (!graphics_ || !width_ || !height_)
        return false;

    if (graphics_->IsDeviceLost())
    {
        URHO3D_LOGWARNING("Texture creation while device is lost");
        return true;
    }

    glGenTextures(1, &object_);

    // Ensure that our texture is bound to OpenGL texture unit 0
    graphics_->SetTextureForUpdate(this);

    // If not compressed, create the initial level 0 texture with null data
    unsigned format = GetSRGB() ? GetSRGBFormat(format_) : format_;
    unsigned externalFormat = GetExternalFormat(format_);
    unsigned dataType = GetDataType(format_);

    bool success = true;
    if (!IsCompressed())
    {
        glGetError();
        for (unsigned i = 0; i < MAX_CUBEMAP_FACES; ++i)
        {
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, format, width_, height_, 0, externalFormat, dataType, 0);
            if (glGetError())
                success = false;
        }
    }
    if (!success)
        URHO3D_LOGERROR("Failed to create texture");

    // Set mipmapping
    levels_ = requestedLevels_;
    if (!levels_)
    {
        unsigned maxSize = (unsigned)Max(width_, height_);
        while (maxSize)
        {
            maxSize >>= 1;
            ++levels_;
        }
    }

#ifndef GL_ES_VERSION_2_0
    glTexParameteri(target_, GL_TEXTURE_BASE_LEVEL, 0);
    glTexParameteri(target_, GL_TEXTURE_MAX_LEVEL, levels_ - 1);
#endif

    // Set initial parameters, then unbind the texture
    UpdateParameters();
    graphics_->SetTexture(0, 0);

    return success;
}

void TextureCube::HandleRenderSurfaceUpdate(StringHash eventType, VariantMap& eventData)
{
    Renderer* renderer = GetSubsystem<Renderer>();

    for (unsigned i = 0; i < MAX_CUBEMAP_FACES; ++i)
    {
        if (renderSurfaces_[i] && (renderSurfaces_[i]->GetUpdateMode() == SURFACE_UPDATEALWAYS || renderSurfaces_[i]->IsUpdateQueued()))
        {
            if (renderer)
                renderer->QueueRenderSurface(renderSurfaces_[i]);
            renderSurfaces_[i]->ResetUpdateQueued();
        }
    }
}

}
