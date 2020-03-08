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

#include "../Precompiled.h"

#include "../Core/Context.h"
#include "../Core/Profiler.h"
#include "../Graphics/Graphics.h"
#include "../Graphics/GraphicsEvents.h"
#include "../Graphics/GraphicsImpl.h"
#include "../Graphics/Renderer.h"
#include "../Graphics/TextureCube.h"
#include "../IO/FileSystem.h"
#include "../IO/Log.h"
#include "../Resource/ResourceCache.h"
#include "../Resource/XMLFile.h"

#include "../DebugNew.h"

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
    nullptr
};

static SharedPtr<Image> GetTileImage(Image* src, int tileX, int tileY, int tileWidth, int tileHeight)
{
    return SharedPtr<Image>(
        src->GetSubimage(IntRect(tileX * tileWidth, tileY * tileHeight, (tileX + 1) * tileWidth, (tileY + 1) * tileHeight)));
}

TextureCube::TextureCube(Context* context) :
    Texture(context)
{
#ifdef URHO3D_OPENGL
    target_ = GL_TEXTURE_CUBE_MAP;
#endif

    // Default to clamp mode addressing
    addressModes_[COORD_U] = ADDRESS_CLAMP;
    addressModes_[COORD_V] = ADDRESS_CLAMP;
    addressModes_[COORD_W] = ADDRESS_CLAMP;
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
    auto* cache = GetSubsystem<ResourceCache>();

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

bool TextureCube::SetSize(int size, unsigned format, TextureUsage usage, int multiSample)
{
    if (size <= 0)
    {
        URHO3D_LOGERROR("Zero or negative cube texture size");
        return false;
    }
    if (usage == TEXTURE_DEPTHSTENCIL)
    {
        URHO3D_LOGERROR("Depth-stencil usage not supported for cube textures");
        return false;
    }

    multiSample = Clamp(multiSample, 1, 16);
    if (multiSample > 1 && usage < TEXTURE_RENDERTARGET)
    {
        URHO3D_LOGERROR("Multisampling is only supported for rendertarget cube textures");
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
#ifdef URHO3D_OPENGL
            renderSurfaces_[i]->target_ = GL_TEXTURE_CUBE_MAP_POSITIVE_X + i;
#endif
        }

        // Nearest filtering by default
        filterMode_ = FILTER_NEAREST;
    }

    if (usage == TEXTURE_RENDERTARGET)
        SubscribeToEvent(E_RENDERSURFACEUPDATE, URHO3D_HANDLER(TextureCube, HandleRenderSurfaceUpdate));
    else
        UnsubscribeFromEvent(E_RENDERSURFACEUPDATE);

    width_ = size;
    height_ = size;
    depth_ = 1;
    format_ = format;
    multiSample_ = multiSample;
    autoResolve_ = multiSample > 1;

    return Create();
}

SharedPtr<Image> TextureCube::GetImage(CubeMapFace face) const
{
    if (format_ != Graphics::GetRGBAFormat() && format_ != Graphics::GetRGBFormat())
    {
        URHO3D_LOGERROR("Unsupported texture format, can not convert to Image");
        return SharedPtr<Image>();
    }

    auto* rawImage = new Image(context_);
    if (format_ == Graphics::GetRGBAFormat())
        rawImage->SetSize(width_, height_, 4);
    else if (format_ == Graphics::GetRGBFormat())
        rawImage->SetSize(width_, height_, 3);
    else
        assert(false);

    GetData(face, 0, rawImage->GetData());
    return SharedPtr<Image>(rawImage);
}

void TextureCube::HandleRenderSurfaceUpdate(StringHash eventType, VariantMap& eventData)
{
    auto* renderer = GetSubsystem<Renderer>();

    for (auto& renderSurface : renderSurfaces_)
    {
        if (renderSurface && (renderSurface->GetUpdateMode() == SURFACE_UPDATEALWAYS || renderSurface->IsUpdateQueued()))
        {
            if (renderer)
                renderer->QueueRenderSurface(renderSurface);
            renderSurface->ResetUpdateQueued();
        }
    }
}

}
