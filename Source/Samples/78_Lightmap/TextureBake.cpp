//
// Copyright (c) 2008-2017 the Urho3D project.
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

#include <Urho3D/Core/Context.h>
#include <Urho3D/Core/CoreEvents.h>
#include <Urho3D/Graphics/Camera.h>
#include <Urho3D/Graphics/Graphics.h>
#include <Urho3D/Graphics/GraphicsEvents.h>
#include <Urho3D/Graphics/View.h>
#include <Urho3D/Graphics/TextureCube.h>
#include <Urho3D/Graphics/Material.h>
#include <Urho3D/Graphics/Model.h>
#include <Urho3D/Graphics/Octree.h>
#include <Urho3D/Graphics/Renderer.h>
#include <Urho3D/Graphics/RenderSurface.h>
#include <Urho3D/Graphics/StaticModel.h>
#include <Urho3D/Graphics/Technique.h>
#include <Urho3D/Graphics/Texture2D.h>
#include <Urho3D/Graphics/Geometry.h>
#include <Urho3D/Graphics/VertexBuffer.h>
#include <Urho3D/Graphics/IndexBuffer.h>
#include <Urho3D/Scene/Scene.h>
#include <Urho3D/Resource/ResourceCache.h>
#include <Urho3D/IO/FileSystem.h>
#include <Urho3D/IO/Log.h>
#include <cstdio>

#include "TextureBake.h"

#include <Urho3D/DebugNew.h>
//=============================================================================
//=============================================================================
TextureBake::TextureBake(Context* context)
    : Component(context)
    , origViewMask_(0)
    , texWidth_(512)
    , texHeight_(512)
    , saveFile_(true)
    , bakeUnlitLight_(false)
    , bakeMixFactor_(0.8f)
{
}

TextureBake::~TextureBake()
{
}

void TextureBake::RegisterObject(Context* context)
{
    context->RegisterFactory<TextureBake>();
}

bool TextureBake::InitModelSetting(unsigned tempViewMask)
{
    bool success = false;

    if (node_)
    {
        staticModel_ = node_->GetComponent<StaticModel>();

        if (staticModel_)
        {
            if (origMaterial_ == NULL)
            {
                origMaterial_ = staticModel_->GetMaterial()->Clone();
                origViewMask_ = staticModel_->GetViewMask();
            }

            // assign temp view mask during the process
            tempViewMask_ = tempViewMask;
            staticModel_->SetViewMask(tempViewMask_);

            success = true;
        }
    }

    return success;
}

bool TextureBake::RestoreModelSetting()
{
    bool success = false;

    if (staticModel_)
    {
        staticModel_->SetMaterial(origMaterial_);
        staticModel_->SetViewMask(origViewMask_);

        success = true;
    }

    return success;
}

void TextureBake::BakeDirectLight(const String &filepath, unsigned imageSize)
{
    // InitModelSetting() fn must be called 1st
    if (staticModel_)
    {
        ResourceCache* cache = GetSubsystem<ResourceCache>();

        texWidth_ = texHeight_ = imageSize;
        filepath_ = filepath;
        bakeUnlitLight_ = false;

        // clone mat to make changes
        SharedPtr<Material> dupMat = origMaterial_->Clone();
        staticModel_->SetMaterial(dupMat);

        // choose appropriate bake technique
        Technique *technique = dupMat->GetTechnique(0);
        if (technique->GetName().Find("NoTexture") != String::NPOS)
        {
            dupMat->SetTechnique(0, cache->GetResource<Technique>("Lightmap/Techniques/NoTextureBake.xml"));
        }
        else
        {
            dupMat->SetTechnique(0, cache->GetResource<Technique>("Lightmap/Techniques/DiffBake.xml"));
        }

        //**NOTE** change mask
        staticModel_->SetViewMask(staticModel_->GetViewMask() | ViewMask_Capture);

        // setup for direct lighting
        InitBakeLightSettings(staticModel_->GetWorldBoundingBox());

        SubscribeToEvent(E_ENDFRAME, URHO3D_HANDLER(TextureBake, HandlePostRenderBakeLighting));
    }
}

void TextureBake::SwitchToDirectImageUnlitTechnique()
{
    // InitModelSetting() fn must be called 1st
    if (staticModel_)
    {
        ResourceCache* cache = GetSubsystem<ResourceCache>();

        // clone mat to make changes
        SharedPtr<Material> dupMat = origMaterial_->Clone();
        staticModel_->SetMaterial(dupMat);

        // using direct light unlit
        Technique *technique = dupMat->GetTechnique(0);
        dupMat->SetTechnique(0, cache->GetResource<Technique>("Techniques/DiffUnlitTexCoord2.xml"));

        SharedPtr<Texture2D> diffTex(new Texture2D(context_));
        diffTex->SetData(bakedLightImage_);
        dupMat->SetTexture(TU_DIFFUSE, diffTex);
    }
}

void TextureBake::SwitchToLightmapTechnique(SharedPtr<Image> lightmapImg)
{
    // InitModelSetting() fn must be called 1st
    if (staticModel_)
    {
        ResourceCache* cache = GetSubsystem<ResourceCache>();

        // clone mat to make changes
        SharedPtr<Material> dupMat = origMaterial_->Clone();
        staticModel_->SetMaterial(dupMat);

        // choose appropriate lightmap technique
        Technique *technique = dupMat->GetTechnique(0);
        if (technique->GetName().Find("NoTexture") != String::NPOS)
        {
            dupMat->SetTechnique(0, cache->GetResource<Technique>("Lightmap/Techniques/NoTextureLightMap.xml"));
        }
        else
        {
            dupMat->SetTechnique(0, cache->GetResource<Technique>("Techniques/DiffLightMap.xml"));
        }

        lightmapImage_ = lightmapImg;
        SharedPtr<Texture2D> emissiveTex(new Texture2D(context_));
        emissiveTex->SetData(lightmapImage_);

        dupMat->SetTexture(TU_EMISSIVE, emissiveTex);
        dupMat->SetShaderParameter("MatEmissiveColor", Color::BLACK);
    }
}

void TextureBake::BakeIndirectLight(const String &filepath, unsigned imageSize)
{
    // InitModelSetting() and SwitchToLightmapTechnique() fns must've be called 1st
    if (staticModel_ && lightmapImage_)
    {
        ResourceCache* cache = GetSubsystem<ResourceCache>();

        texWidth_ = texHeight_ = imageSize;
        filepath_ = filepath;
        bakeUnlitLight_ = true;

        // clone mat to make changes
        SharedPtr<Material> dupMat = origMaterial_->Clone();
        staticModel_->SetMaterial(dupMat);

        // set technique to bake both textures on texcoord2
        dupMat->SetTechnique(0, cache->GetResource<Technique>("Lightmap/Techniques/UnlitBake.xml"));

        // setup direct and indirect textures
        SharedPtr<Texture2D> normalTex(new Texture2D(context_));
        SharedPtr<Texture2D> emissiveTex(new Texture2D(context_));
        normalTex->SetData(bakedLightImage_);
        emissiveTex->SetData(lightmapImage_);

        dupMat->SetTexture(TU_NORMAL, normalTex);
        dupMat->SetTexture(TU_EMISSIVE, emissiveTex);
        dupMat->SetShaderParameter("MixFactor", bakeMixFactor_);

        //**NOTE** change mask
        staticModel_->SetViewMask(staticModel_->GetViewMask() | ViewMask_Capture);

        // setup for direct lighting
        InitBakeLightSettings(staticModel_->GetWorldBoundingBox());

        SubscribeToEvent(E_ENDFRAME, URHO3D_HANDLER(TextureBake, HandlePostRenderBakeLighting));
    }
}

void TextureBake::InitBakeLightSettings(const BoundingBox& worldBoundingBox)
{
    camNode_ = GetScene()->CreateChild("RenderCamera");

    // set campos right at the model
    Vector3 halfSize = worldBoundingBox.HalfSize();
    camNode_->SetWorldPosition(worldBoundingBox.Center() - Vector3(0, 0, halfSize.z_));

    camera_ = camNode_->CreateComponent<Camera>();
    camera_->SetFov(90.0f);
    camera_->SetNearClip(0.0001f);
    camera_->SetAspectRatio(1.0f);
    camera_->SetOrthographic(true);
    camera_->SetOrthoSize(Vector2((float)texWidth_, (float)texHeight_));

    //**NOTE** change mask
    camera_->SetViewMask(ViewMask_Capture);

    viewport_ = new Viewport(context_, GetScene(), camera_);
    viewport_->SetRenderPath(GetSubsystem<Renderer>()->GetViewport(0)->GetRenderPath());

    // Construct render surface 
    renderTexture_ = new Texture2D(context_);
    renderTexture_->SetNumLevels(1);
    renderTexture_->SetSize(texWidth_, texHeight_, Graphics::GetRGBAFormat(), TEXTURE_RENDERTARGET);
    renderTexture_->SetFilterMode(FILTER_BILINEAR);
    
    renderSurface_ = renderTexture_->GetRenderSurface();
    renderSurface_->SetViewport(0, viewport_);
    renderSurface_->SetUpdateMode(SURFACE_UPDATEALWAYS);
}

void TextureBake::RestoreTempViewMask()
{
    staticModel_->SetViewMask(tempViewMask_);
}

void TextureBake::Stop()
{
    // remove
    camNode_->Remove();
    camNode_ = NULL;
    viewport_ = NULL;
    renderSurface_ = NULL;
    renderTexture_ = NULL;

    UnsubscribeFromEvent(E_ENDFRAME);
}

void TextureBake::OutputFile()
{
    // generate output file
    if (saveFile_ && bakeUnlitLight_)
    {
        String name = ToString("node%u_unlit.png", node_->GetID());

        String path = filepath_ + name;

        bakedLightImage_->SavePNG(path);
    }
}

void TextureBake::SendTextureBakedtMsg()
{
    using namespace BakeLightmapDone;

    VariantMap& eventData  = GetEventDataMap();
    eventData[P_NODE]      = node_;

    SendEvent(E_BAKELIGHTINGDONE, eventData);
}

void TextureBake::HandlePostRenderBakeLighting(StringHash eventType, VariantMap& eventData)
{
    // get image prior to deleting the surface
    bakedLightImage_ = renderTexture_->GetImage();

    RestoreTempViewMask();

    Stop();

    OutputFile();

    SendTextureBakedtMsg();
}





