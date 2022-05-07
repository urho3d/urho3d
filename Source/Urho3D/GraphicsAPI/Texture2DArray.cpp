// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

#include "../Precompiled.h"

#include "../Core/Context.h"
#include "../Core/Profiler.h"
#include "../Graphics/Graphics.h"
#include "../Graphics/GraphicsEvents.h"
#include "../Graphics/Renderer.h"
#include "../GraphicsAPI/GraphicsImpl.h"
#include "../GraphicsAPI/Texture2DArray.h"
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

Texture2DArray::Texture2DArray(Context* context) :
    Texture(context)
{
#ifdef URHO3D_OPENGL
#ifndef GL_ES_VERSION_2_0
    if (Graphics::GetGAPI() == GAPI_OPENGL)
        target_ = GL_TEXTURE_2D_ARRAY;
#endif
#endif
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
    if (!graphics_ || graphics_->IsDeviceLost())
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

    // Delete the old rendersurface if any
    renderSurface_.Reset();

    usage_ = usage;

    if (usage == TEXTURE_RENDERTARGET)
    {
        renderSurface_ = new RenderSurface(this);

        // Nearest filtering by default
        filterMode_ = FILTER_NEAREST;
    }

    if (usage == TEXTURE_RENDERTARGET)
        SubscribeToEvent(E_RENDERSURFACEUPDATE, URHO3D_HANDLER(Texture2DArray, HandleRenderSurfaceUpdate));
    else
        UnsubscribeFromEvent(E_RENDERSURFACEUPDATE);

    width_ = width;
    height_ = height;
    format_ = format;
    depth_ = 1;
    if (layers)
        layers_ = layers;

    layerMemoryUse_.Resize(layers_);
    for (unsigned i = 0; i < layers_; ++i)
        layerMemoryUse_[i] = 0;

    return Create();
}

void Texture2DArray::HandleRenderSurfaceUpdate(StringHash eventType, VariantMap& eventData)
{
    if (renderSurface_ && (renderSurface_->GetUpdateMode() == SURFACE_UPDATEALWAYS || renderSurface_->IsUpdateQueued()))
    {
        auto* renderer = GetSubsystem<Renderer>();
        if (renderer)
            renderer->QueueRenderSurface(renderSurface_);
        renderSurface_->ResetUpdateQueued();
    }
}

void Texture2DArray::OnDeviceLost()
{
    GAPI gapi = Graphics::GetGAPI();

#ifdef URHO3D_OPENGL
    if (gapi == GAPI_OPENGL)
        return OnDeviceLost_OGL();
#endif

#ifdef URHO3D_D3D9
    if (gapi == GAPI_D3D9)
        return OnDeviceLost_D3D9();
#endif

#ifdef URHO3D_D3D11
    if (gapi == GAPI_D3D11)
        return OnDeviceLost_D3D11();
#endif
}

void Texture2DArray::OnDeviceReset()
{
    GAPI gapi = Graphics::GetGAPI();

#ifdef URHO3D_OPENGL
    if (gapi == GAPI_OPENGL)
        return OnDeviceReset_OGL();
#endif

#ifdef URHO3D_D3D9
    if (gapi == GAPI_D3D9)
        return OnDeviceReset_D3D9();
#endif

#ifdef URHO3D_D3D11
    if (gapi == GAPI_D3D11)
        return OnDeviceReset_D3D11();
#endif
}

void Texture2DArray::Release()
{
    GAPI gapi = Graphics::GetGAPI();

#ifdef URHO3D_OPENGL
    if (gapi == GAPI_OPENGL)
        return Release_OGL();
#endif

#ifdef URHO3D_D3D9
    if (gapi == GAPI_D3D9)
        return Release_D3D9();
#endif

#ifdef URHO3D_D3D11
    if (gapi == GAPI_D3D11)
        return Release_D3D11();
#endif
}

bool Texture2DArray::SetData(unsigned layer, unsigned level, int x, int y, int width, int height, const void* data)
{
    GAPI gapi = Graphics::GetGAPI();

#ifdef URHO3D_OPENGL
    if (gapi == GAPI_OPENGL)
        return SetData_OGL(layer, level, x, y, width, height, data);
#endif

#ifdef URHO3D_D3D9
    if (gapi == GAPI_D3D9)
        return SetData_D3D9(layer, level, x, y, width, height, data);
#endif

#ifdef URHO3D_D3D11
    if (gapi == GAPI_D3D11)
        return SetData_D3D11(layer, level, x, y, width, height, data);
#endif

    return {}; // Prevent warning
}

bool Texture2DArray::SetData(unsigned layer, Deserializer& source)
{
    GAPI gapi = Graphics::GetGAPI();

#ifdef URHO3D_OPENGL
    if (gapi == GAPI_OPENGL)
        return SetData_OGL(layer, source);
#endif

#ifdef URHO3D_D3D9
    if (gapi == GAPI_D3D9)
        return SetData_D3D9(layer, source);
#endif

#ifdef URHO3D_D3D11
    if (gapi == GAPI_D3D11)
        return SetData_D3D11(layer, source);
#endif

    return {}; // Prevent warning
}

bool Texture2DArray::SetData(unsigned layer, Image* image, bool useAlpha)
{
    GAPI gapi = Graphics::GetGAPI();

#ifdef URHO3D_OPENGL
    if (gapi == GAPI_OPENGL)
        return SetData_OGL(layer, image, useAlpha);
#endif

#ifdef URHO3D_D3D9
    if (gapi == GAPI_D3D9)
        return SetData_D3D9(layer, image, useAlpha);
#endif

#ifdef URHO3D_D3D11
    if (gapi == GAPI_D3D11)
        return SetData_D3D11(layer, image, useAlpha);
#endif

    return {}; // Prevent warning
}

bool Texture2DArray::GetData(unsigned layer, unsigned level, void* dest) const
{
    GAPI gapi = Graphics::GetGAPI();

#ifdef URHO3D_OPENGL
    if (gapi == GAPI_OPENGL)
        return GetData_OGL(layer, level, dest);
#endif

#ifdef URHO3D_D3D9
    if (gapi == GAPI_D3D9)
        return GetData_D3D9(layer, level, dest);
#endif

#ifdef URHO3D_D3D11
    if (gapi == GAPI_D3D11)
        return GetData_D3D11(layer, level, dest);
#endif

    return {}; // Prevent warning
}

bool Texture2DArray::Create()
{
    GAPI gapi = Graphics::GetGAPI();

#ifdef URHO3D_OPENGL
    if (gapi == GAPI_OPENGL)
        return Create_OGL();
#endif

#ifdef URHO3D_D3D9
    if (gapi == GAPI_D3D9)
        return Create_D3D9();
#endif

#ifdef URHO3D_D3D11
    if (gapi == GAPI_D3D11)
        return Create_D3D11();
#endif

    return {}; // Prevent warning
}

}
