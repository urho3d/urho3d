//
// Urho3D Engine
// Copyright (c) 2008-2011 Lasse Öörni
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

#include "Precompiled.h"
#include "Camera.h"
#include "CoreEvents.h"
#include "DebugRenderer.h"
#include "Geometry.h"
#include "Graphics.h"
#include "GraphicsEvents.h"
#include "GraphicsImpl.h"
#include "IndexBuffer.h"
#include "Light.h"
#include "Log.h"
#include "Material.h"
#include "OcclusionBuffer.h"
#include "Octree.h"
#include "OctreeQuery.h"
#include "Profiler.h"
#include "Renderer.h"
#include "ResourceCache.h"
#include "Scene.h"
#include "Shader.h"
#include "ShaderVariation.h"
#include "Technique.h"
#include "Texture2D.h"
#include "TextureCube.h"
#include "VertexBuffer.h"
#include "View.h"
#include "XMLFile.h"
#include "Zone.h"

#include "DebugNew.h"

static const float dirLightVertexData[] =
{
    -1, 1, 0,
    1, 1, 0,
    1, -1, 0,
    -1, -1, 0,
};

static const unsigned short dirLightIndexData[] =
{
    0, 1, 2,
    2, 3, 0,
};

static const float pointLightVertexData[] =
{
    -0.423169f, -1.000000f, 0.423169f,
    -0.423169f, -1.000000f, -0.423169f,
    0.423169f, -1.000000f, -0.423169f,
    0.423169f, -1.000000f, 0.423169f,
    0.423169f, 1.000000f, -0.423169f,
    -0.423169f, 1.000000f, -0.423169f,
    -0.423169f, 1.000000f, 0.423169f,
    0.423169f, 1.000000f, 0.423169f,
    -1.000000f, 0.423169f, -0.423169f,
    -1.000000f, -0.423169f, -0.423169f,
    -1.000000f, -0.423169f, 0.423169f,
    -1.000000f, 0.423169f, 0.423169f,
    0.423169f, 0.423169f, -1.000000f,
    0.423169f, -0.423169f, -1.000000f,
    -0.423169f, -0.423169f, -1.000000f,
    -0.423169f, 0.423169f, -1.000000f,
    1.000000f, 0.423169f, 0.423169f,
    1.000000f, -0.423169f, 0.423169f,
    1.000000f, -0.423169f, -0.423169f,
    1.000000f, 0.423169f, -0.423169f,
    0.423169f, -0.423169f, 1.000000f,
    0.423169f, 0.423169f, 1.000000f,
    -0.423169f, 0.423169f, 1.000000f,
    -0.423169f, -0.423169f, 1.000000f
};

static const unsigned short pointLightIndexData[] =
{
    0, 1, 2,
    0, 2, 3,
    4, 5, 6,
    4, 6, 7,
    8, 9, 10,
    8, 10, 11,
    12, 13, 14,
    12, 14, 15,
    16, 17, 18,
    16, 18, 19,
    20, 21, 22,
    20, 22, 23,
    0, 10, 9,
    0, 9, 1,
    13, 2, 1,
    13, 1, 14,
    23, 0, 3,
    23, 3, 20,
    17, 3, 2,
    17, 2, 18,
    21, 7, 6,
    21, 6, 22,
    7, 16, 19,
    7, 19, 4,
    5, 8, 11,
    5, 11, 6,
    4, 12, 15,
    4, 15, 5,
    22, 11, 10,
    22, 10, 23,
    8, 15, 14,
    8, 14, 9,
    12, 19, 18,
    12, 18, 13,
    16, 21, 20,
    16, 20, 17,
    0, 23, 10,
    1, 9, 14,
    2, 13, 18,
    3, 17, 20,
    6, 11, 22,
    5, 15, 8,
    4, 19, 12,
    7, 21, 16
};

static const float spotLightVertexData[] =
{
    // Use slightly clamped Z-range so that shadowed point light splits line up nicely
    0.00001f, 0.00001f, 0.00001f,
    0.00001f, -0.00001f, 0.00001f,
    -0.00001f, -0.00001f, 0.00001f,
    -0.00001f, 0.00001f, 0.00001f,
    1.00000f, 1.00000f, 0.99999f,
    1.00000f, -1.00000f, 0.99999f,
    -1.00000f,  -1.00000f, 0.99999f,
    -1.00000f, 1.00000f, 0.99999f,
};

static const unsigned short spotLightIndexData[] =
{
    3, 0, 1,
    3, 1, 2,
    0, 4, 5,
    0, 5, 1,
    3, 7, 4,
    3, 4, 0,
    7, 3, 2,
    7, 2, 6,
    6, 2, 1,
    6, 1, 5,
    7, 5, 4,
    7, 6, 5
};

static const String hwVariations[] =
{
    "",
    "HW"
};

static const String geometryVSVariations[] =
{
    "",
    "Skinned",
    "Instanced",
    "Billboard"
};

static const String lightVSVariations[] =
{
    "",
    "Spot",
    "Shadow",
    "SpotShadow"
};

static const String deferredLightVSVariations[] =
{
    "",
    "Dir",
    "Ortho",
    "OrthoDir"
};

static const String lightPSVariations[] = 
{
    "Dir",
    "DirSpec",
    "DirShadow",
    "DirShadowSpec",
    "Spot",
    "SpotSpec",
    "SpotShadow",
    "SpotShadowSpec",
    "Point",
    "PointSpec",
    "PointShadow",
    "PointShadowSpec",
    "PointMask",
    "PointMaskSpec",
    "PointMaskShadow",
    "PointMaskShadowSpec",
    "OrthoDir",
    "OrthoDirSpec",
    "OrthoDirShadow",
    "OrthoDirShadowSpec",
    "OrthoSpot",
    "OrthoSpotSpec",
    "OrthoSpotShadow",
    "OrthoSpotShadowSpec",
    "OrthoPoint",
    "OrthoPointSpec",
    "OrthoPointShadow",
    "OrthoPointShadowSpec",
    "OrthoPointMask",
    "OrthoPointMaskSpec",
    "OrthoPointMaskShadow",
    "OrthoPointMaskShadowSpec"
};

static const unsigned INSTANCING_BUFFER_MASK = MASK_INSTANCEMATRIX1 | MASK_INSTANCEMATRIX2 | MASK_INSTANCEMATRIX3;
static const Viewport noViewport;

OBJECTTYPESTATIC(Renderer);

Renderer::Renderer(Context* context) :
    Object(context),
    defaultZone_(new Zone(context)),
    numViews_(0),
    numShadowCameras_(0),
    numSplitLights_(0),
    numTempNodes_(0),
    specularLighting_(true),
    drawShadows_(true),
    textureAnisotropy_(4),
    textureFilterMode_(FILTER_TRILINEAR),
    textureQuality_(QUALITY_HIGH),
    materialQuality_(QUALITY_HIGH),
    shadowMapSize_(1024),
    shadowMapHiresDepth_(false),
    reuseShadowMaps_(true),
    dynamicInstancing_(true),
    maxOccluderTriangles_(5000),
    occlusionBufferSize_(256),
    occluderSizeThreshold_(0.1f),
    shadersChangedFrameNumber_(M_MAX_UNSIGNED),
    shadersDirty_(true),
    initialized_(false)
{
    SubscribeToEvent(E_SCREENMODE, HANDLER(Renderer, HandleScreenMode));
    SubscribeToEvent(E_RENDERUPDATE, HANDLER(Renderer, HandleRenderUpdate));
    
    // Default to one of each shadow map resolution
    for (unsigned i = 0; i < NUM_SHADOWMAP_RESOLUTIONS; ++i)
        shadowMaps_[i].Resize(1);
    
    // Try to initialize right now, but skip if screen mode is not yet set
    Initialize();
}

Renderer::~Renderer()
{
}

void Renderer::SetNumViewports(unsigned num)
{
    viewports_.Resize(num);
}

void Renderer::SetViewport(unsigned index, const Viewport& viewport)
{
    if (index >= viewports_.Size())
    {
        LOGERROR("Viewport index out of bounds");
        return;
    }
    
    viewports_[index] = viewport;
}

void Renderer::SetSpecularLighting(bool enable)
{
    specularLighting_ = enable;
}

void Renderer::SetDrawShadows(bool enable)
{
    if (!graphics_)
        return;
    
    drawShadows_ = enable;
    
    if (!CreateShadowMaps())
        drawShadows_ = false;
}

void Renderer::SetTextureAnisotropy(int level)
{
    textureAnisotropy_ = Max(level, 1);
}

void Renderer::SetTextureFilterMode(TextureFilterMode mode)
{
    textureFilterMode_ = mode;
}

void Renderer::SetTextureQuality(int quality)
{
    quality = Clamp(quality, QUALITY_LOW, QUALITY_HIGH);
    
    if (quality != textureQuality_)
    {
        textureQuality_ = quality;
        ReloadTextures();
    }
}

void Renderer::SetMaterialQuality(int quality)
{
    materialQuality_ = Clamp(quality, QUALITY_LOW, QUALITY_MAX);
    shadersDirty_ = true;
    ResetViews();
}

void Renderer::SetShadowMapSize(int size)
{
    if (!graphics_)
        return;
    
    shadowMapSize_ = Max(size, SHADOW_MIN_PIXELS);
    
    if (!CreateShadowMaps())
    {
        shadowMapSize_ = 1024;
        if (!CreateShadowMaps())
            drawShadows_ = false;
    }
}

void Renderer::SetShadowMapHiresDepth(bool enable)
{
    if (!graphics_)
        return;
    
    if (!graphics_->GetHiresShadowSupport())
        enable = false;
    
    shadowMapHiresDepth_ = enable;
    if (!CreateShadowMaps())
        drawShadows_ = false;
}

void Renderer::SetReuseShadowMaps(bool enable)
{
    if (enable == reuseShadowMaps_)
        return;
    
    reuseShadowMaps_ = enable;
    if (reuseShadowMaps_)
    {
        for (unsigned i = 0; i < NUM_SHADOWMAP_RESOLUTIONS; ++i)
            shadowMaps_[i].Resize(1);
    }
    if (!CreateShadowMaps())
        drawShadows_ = false;
    shadersDirty_ = true;
}

void Renderer::SetNumShadowMaps(unsigned full, unsigned half, unsigned quarter)
{
    shadowMaps_[0].Resize(full ? full : 1);
    shadowMaps_[1].Resize(half ? half : 1);
    shadowMaps_[2].Resize(quarter ? quarter : 1);
    if (!CreateShadowMaps())
        drawShadows_ = false;
}

void Renderer::SetDynamicInstancing(bool enable)
{
    if (!instancingBuffer_)
        enable = false;
    
    dynamicInstancing_ = enable;
}

void Renderer::SetMaxOccluderTriangles(int triangles)
{
    maxOccluderTriangles_ = Max(triangles, 0);
}

void Renderer::SetOcclusionBufferSize(int size)
{
    occlusionBufferSize_ = Max(size, 1);
    occlusionBuffers_.Clear();
}

void Renderer::SetOccluderSizeThreshold(float screenSize)
{
    occluderSizeThreshold_ = Max(screenSize, 0.0f);
}

const Viewport& Renderer::GetViewport(unsigned index) const
{
    return index < viewports_.Size() ? viewports_[index] : noViewport;
}

ShaderVariation* Renderer::GetVertexShader(const String& name, bool checkExists) const
{
    return GetShader(name, vsFormat_, checkExists);
}

ShaderVariation* Renderer::GetPixelShader(const String& name, bool checkExists) const
{
    return GetShader(name, psFormat_, checkExists);
}

unsigned Renderer::GetNumGeometries(bool allViews) const
{
    unsigned numGeometries = 0;
    unsigned lastView = allViews ? numViews_ : 1;
    
    for (unsigned i = 0; i < lastView; ++i)
        numGeometries += views_[i]->GetGeometries().Size();
    
    return numGeometries;
}

unsigned Renderer::GetNumLights(bool allViews) const
{
    unsigned nulights_ = 0;
    unsigned lastView = allViews ? numViews_ : 1;
    
    for (unsigned i = 0; i < lastView; ++i)
        nulights_ += views_[i]->GetLights().Size();
    
    return nulights_;
}

unsigned Renderer::GetNumShadowMaps(bool allViews) const
{
    unsigned numShadowMaps = 0;
    unsigned lastView = allViews ? numViews_ : 1;
    
    for (unsigned i = 0; i < lastView; ++i)
    {
        const Vector<LightBatchQueue>& lightQueues = views_[i]->GetLightQueues();
        
        for (unsigned j = 0; j < lightQueues.Size(); ++j)
        {
            Light* light = lightQueues[j].light_;
            if ((light) && (light->GetShadowMap()))
                ++numShadowMaps;
        }
    }
    
    return numShadowMaps;
}

unsigned Renderer::GetNumOccluders(bool allViews) const
{
    unsigned numOccluders = 0;
    unsigned lastView = allViews ? numViews_ : 1;
    
    for (unsigned i = 0; i < lastView; ++i)
        numOccluders += views_[i]->GetOccluders().Size();
    
    return numOccluders;
}

unsigned Renderer::GetNumShadowOccluders(bool allViews) const
{
    unsigned numShadowOccluders = 0;
    unsigned lastView = allViews ? numViews_ : 1;
    
    for (unsigned i = 0; i < lastView; ++i)
        numShadowOccluders += views_[i]->GetShadowOccluders().Size();
    
    return numShadowOccluders;
}

const OcclusionBuffer* Renderer::GetOcclusionBuffer(float aspectRatio, bool halfResolution)
{
    // Return an occlusion buffer for debug output purposes. Do not allocate new
    int width = occlusionBufferSize_;
    int height = (int)(occlusionBufferSize_ / aspectRatio);
    if (halfResolution)
    {
        width >>= 1;
        height >>= 1;
    }
    int searchKey = (width << 16) | height;
    
    Map<int, SharedPtr<OcclusionBuffer> >::Iterator i = occlusionBuffers_.Find(searchKey);
    if (i != occlusionBuffers_.End())
        return i->second_;
    else
        return 0;
}

void Renderer::Update(float timeStep)
{
    PROFILE(UpdateViewports);
    
    numViews_ = 0;
    
    // If device lost, do not perform update. This is because any dynamic vertex/index buffer updates happen already here,
    // and if the device is lost, the updates queue up, causing memory use to rise constantly
    if ((!graphics_) || (!graphics_->IsInitialized()) || (graphics_->IsDeviceLost()))
        return;
    
    // Advance frame number & time, set up the frameinfo structure, and reset views & stats
    frame_.frameNumber_ = GetSubsystem<Time>()->GetFrameNumber();
    frame_.timeStep_ = timeStep;
    frame_.camera_ = 0;
    numShadowCameras_ = 0;
    numSplitLights_ = 0;
    numTempNodes_ = 0;
    updateOctrees_.Clear();
    
    // Reload shaders if needed
    if (shadersDirty_)
        LoadShaders();
    
    // Process all viewports. Use reverse order, because during rendering the order will be reversed again to handle auxiliary
    // view dependencies correctly
    for (unsigned i = viewports_.Size() - 1; i < viewports_.Size(); --i)
    {
        unsigned mainView = numViews_;
        Viewport& viewport = viewports_[i];
        if (!AddView(0, viewport))
            continue;
        
        // Update octree (perform early update for nodes which need that, and reinsert moved nodes.)
        // However, if the same scene is viewed from multiple cameras, update the octree only once
        Octree* octree = viewport.scene_->GetComponent<Octree>();
        DebugRenderer* debug = viewport.scene_->GetComponent<DebugRenderer>();
        if (updateOctrees_.Find(octree) == updateOctrees_.End())
        {
            frame_.camera_ = viewport.camera_;
            frame_.viewSize_ = IntVector2(viewport.rect_.right_ - viewport.rect_.left_, viewport.rect_.bottom_ - viewport.rect_.top_);
            if (frame_.viewSize_ == IntVector2::ZERO)
                frame_.viewSize_ = IntVector2(graphics_->GetWidth(), graphics_->GetHeight());
            octree->Update(frame_);
            updateOctrees_.Insert(octree);
            
            // Set also the view for the debug graphics already here, so that it can use culling
            /// \todo May result in incorrect debug geometry culling if the same scene is drawn from multiple viewports
            if (debug)
                debug->SetView(viewport.camera_);
        }
        
        // Update the viewport's main view and any auxiliary views it Creates
        for (unsigned i = mainView; i < numViews_; ++i)
            views_[i]->Update(frame_);
    }
    
    return;
}

void Renderer::Render()
{
    if (!graphics_)
        return;
    
    PROFILE(RenderViewports);
    
    graphics_->SetDefaultTextureFilterMode(textureFilterMode_);
    graphics_->SetTextureAnisotropy(textureAnisotropy_);
    
    // If no views, just clear the screen
    if (!numViews_)
    {
        numPrimitives_ = 0;
        numBatches_ = 0;
        graphics_->SetAlphaTest(false);
        graphics_->SetBlendMode(BLEND_REPLACE);
        graphics_->SetColorWrite(true);
        graphics_->SetDepthWrite(true);
        graphics_->SetFillMode(FILL_SOLID);
        graphics_->SetScissorTest(false);
        graphics_->SetStencilTest(false);
        graphics_->Clear(CLEAR_COLOR | CLEAR_DEPTH | CLEAR_STENCIL);
        return;
    }
    
    // Render views from last to first (each main view is rendered after the auxiliary views it depends on)
    for (unsigned i = numViews_ - 1; i < numViews_; --i)
        views_[i]->Render();
    
    // Disable scissor/stencil tests if left on by lights, and reset stream frequencies
    graphics_->SetScissorTest(false);
    graphics_->SetStencilTest(false);
    graphics_->ResetStreamFrequencies();
    
    // Copy the number of batches & primitives from Graphics so that we can account for 3D geometry only
    numPrimitives_ = graphics_->GetNumPrimitives();
    numBatches_ = graphics_->GetNumBatches();
}

void Renderer::DrawDebugGeometry(bool depthTest)
{
    PROFILE(RendererDrawDebug);
    
    /// \todo Because debug geometry is per-scene, if two cameras show views of the same area, occlusion is not shown correctly
    HashSet<Drawable*> processedGeometries;
    HashSet<Light*> processedLights;
    
    for (unsigned i = 0; i < numViews_; ++i)
    {
        // Make sure it's a main view, and process each node only once
        View* view = views_[i];
        if (view->GetRenderTarget())
            continue;
        Octree* octree = view->GetOctree();
        if (!octree)
            continue;
        Scene* scene = static_cast<Scene*>(octree->GetNode());
        if (!scene)
            continue;
        DebugRenderer* debug = scene->GetComponent<DebugRenderer>();
        if (!debug)
            continue;
        
        const PODVector<Drawable*>& geometries = view->GetGeometries();
        const PODVector<Light*>& lights = view->GetLights();
        
        for (unsigned i = 0; i < geometries.Size(); ++i)
        {
            if (processedGeometries.Find(geometries[i]) == processedGeometries.End())
            {
                geometries[i]->DrawDebugGeometry(debug, depthTest);
                processedGeometries.Insert(geometries[i]);
            }
        }
        for (unsigned i = 0; i < lights.Size(); ++i)
        {
            if (processedLights.Find(lights[i]) == processedLights.End())
            {
                lights[i]->DrawDebugGeometry(debug, depthTest);
                processedLights.Insert(lights[i]);
            }
        }
    }
}

void Renderer::Initialize()
{
    Graphics* graphics = GetSubsystem<Graphics>();
    ResourceCache* cache = GetSubsystem<ResourceCache>();
    
    if ((!graphics) || (!graphics->IsInitialized()) || (!cache))
        return;
    
    PROFILE(InitRenderer);
    
    graphics_ = graphics;
    cache_ = cache;
    
    // Check shader model support
    #ifndef USE_OPENGL
    if (graphics_->GetSM3Support())
    {
        shaderPath_ = "Shaders/SM3/";
        vsFormat_ = ".vs3";
        psFormat_ = ".ps3";
    }
    else
    {
        shaderPath_ = "Shaders/SM2/";
        vsFormat_ = ".vs2";
        psFormat_ = ".ps2";
    }
    #else
    {
        shaderPath_ = "Shaders/GLSL/";
        vsFormat_ = ".vert";
        psFormat_ = ".frag";
    }
    #endif
    
    defaultLightRamp_ = cache->GetResource<Texture2D>("Textures/Ramp.png");
    defaultLightSpot = cache->GetResource<Texture2D>("Textures/Spot.png");
    defaultMaterial_ = cache->GetResource<Material>("Materials/Default.xml");
    
    CreateGeometries();
    CreateInstancingBuffer();
    
    if (!CreateShadowMaps())
        drawShadows_ = false;
    
    viewports_.Resize(1);
    ResetViews();
    
    LOGINFO("Initialized renderer");
    initialized_ = true;
}

void Renderer::ResetViews()
{
    views_.Clear();
    numViews_ = 0;
}

bool Renderer::AddView(RenderSurface* renderTarget, const Viewport& viewport)
{
    // If using a render target texture, make sure it will not be rendered to multiple times
    if (renderTarget)
    {
        for (unsigned i = 0; i < numViews_; ++i)
        {
            if (views_[i]->GetRenderTarget() == renderTarget)
                return false;
        }
    }
    
    if (views_.Size() <= numViews_)
        views_.Resize(numViews_ + 1);
    if (!views_[numViews_])
        views_[numViews_] = new View(context_);
    
    if (views_[numViews_]->Define(renderTarget, viewport))
    {
        ++numViews_;
        return true;
    }
    else
        return false;
}

OcclusionBuffer* Renderer::GetOrCreateOcclusionBuffer(Camera* camera, int maxOccluderTriangles, bool halfResolution)
{
    // Get an occlusion buffer matching the aspect ratio. If not found, allocate new
    int width = occlusionBufferSize_;
    int height = (int)(occlusionBufferSize_ / camera->GetAspectRatio());
    if (halfResolution)
    {
        width >>= 1;
        height >>= 1;
    }
    int searchKey = (width << 16) | height;
    
    SharedPtr<OcclusionBuffer> buffer;
    Map<int, SharedPtr<OcclusionBuffer> >::Iterator i = occlusionBuffers_.Find(searchKey);
    if (i != occlusionBuffers_.End())
        buffer = i->second_;
    else
    {
        buffer = new OcclusionBuffer(context_);
        buffer->SetSize(width, height);
        occlusionBuffers_[searchKey] = buffer;
    }
    
    buffer->SetView(camera);
    buffer->SetMaxTriangles(maxOccluderTriangles);
    buffer->Clear();
    
    return buffer;
}

Geometry* Renderer::GetLightGeometry(Light* light)
{
    switch (light->GetLightType())
    {
    case LIGHT_POINT:
        return pointLightGeometry_;
        
    case LIGHT_SPOT:
    case LIGHT_SPLITPOINT:
        return spotLightGeometry_;
        
    default:
        return dirLightGeometry_;
    }
}

Texture2D* Renderer::GetShadowMap(float resolution)
{
    unsigned index = 0;
    if (resolution < 0.75f)
        index = (resolution >= 0.375f) ? 1 : 2;
    
    if (reuseShadowMaps_)
        return shadowMaps_[index][0];
    else
    {
        // If higher resolution shadow maps already used up, fall back to lower resolutions
        while (index < NUM_SHADOWMAP_RESOLUTIONS)
        {
            if (shadowMapUseCount_[index] < shadowMaps_[index].Size())
                return shadowMaps_[index][shadowMapUseCount_[index]++];
            ++index;
        }
        return 0;
    }
}

void Renderer::ResetShadowMapUseCount()
{
    for (unsigned i = 0; i < NUM_SHADOWMAP_RESOLUTIONS; ++i)
        shadowMapUseCount_[i] = 0;
}

ShaderVariation* Renderer::GetShader(const String& name, const String& extension, bool checkExists) const
{
    String shaderName = shaderPath_;
    String variationName;
    
    unsigned split = name.Find('_');
    if (split != String::NPOS)
    {
        shaderName += name.Substring(0, split) + extension;
        variationName = name.Substring(split + 1);
    }
    else
        shaderName += name + extension;
    
    if (checkExists)
    {
        if (!cache_->Exists(shaderName))
            return 0;
    }
    
    Shader* shader = cache_->GetResource<Shader>(shaderName);
    if (shader)
        return shader->GetVariation(variationName);
    else
        return 0;
}

void Renderer::SetBatchShaders(Batch& batch, Technique* technique, Pass* pass, bool allowShadows)
{
    batch.pass_ = pass;
    
    // Check if shaders are unloaded or need reloading
    Vector<SharedPtr<ShaderVariation> >& vertexShaders = pass->GetVertexShaders();
    Vector<SharedPtr<ShaderVariation> >& pixelShaders = pass->GetPixelShaders();
    if ((!vertexShaders.Size()) || (!pixelShaders.Size()) || (technique->GetShadersLoadedFrameNumber() !=
        shadersChangedFrameNumber_))
    {
        // First release all previous shaders, then load
        technique->ReleaseShaders();
        LoadMaterialShaders(technique);
    }
    
    // Make sure shaders are loaded now
    if ((vertexShaders.Size()) && (pixelShaders.Size()))
    {
        //  Check whether is a forward lit pass. If not, there is only one pixel shader
        PassType type = pass->GetType();
        if ((type != PASS_LITBASE) && (type != PASS_LIGHT))
        {
            unsigned vsi = batch.geometryType_;
            batch.vertexShader_ = vertexShaders[vsi];
            batch.pixelShader_ = pixelShaders[0];
            batch.vertexShaderIndex_ = vsi;
        }
        else
        {
            Light* light = batch.light_;
            if (!light)
            {
                // Do not log error, as it would result in a lot of spam
                batch.vertexShader_ = 0;
                batch.pixelShader_ = 0;
                return;
            }
            
            unsigned vsi = 0;
            unsigned psi = 0;
            vsi = batch.geometryType_ * MAX_LIGHT_VS_VARIATIONS;
            
            if ((specularLighting_) && (light->GetSpecularIntensity() > 0.0f))
                psi += LPS_SPEC;
            if ((allowShadows) && (light->GetShadowMap()))
            {
                vsi += LVS_SHADOW;
                psi += LPS_SHADOW;
            }
            
            switch (light->GetLightType())
            {
            case LIGHT_POINT:
            case LIGHT_SPLITPOINT:
                if (light->GetShapeTexture())
                    psi += LPS_POINTMASK;
                else
                    psi += LPS_POINT;
                break;
                
            case LIGHT_SPOT:
                psi += LPS_SPOT;
                vsi += LVS_SPOT;
                break;
            }
            
            batch.vertexShader_ = vertexShaders[vsi];
            batch.pixelShader_ = pixelShaders[psi];
            batch.vertexShaderIndex_ = vsi;
        }
    }
    
    batch.CalculateSortKey();
    
    // Log error if shaders could not be assigned, but only once per technique
    if ((!batch.vertexShader_) || (!batch.pixelShader_))
    {
        if (shaderErrorDisplayed_.Find(technique) == shaderErrorDisplayed_.End())
        {
            shaderErrorDisplayed_.Insert(technique);
            LOGERROR("Technique " + technique->GetName() + " has missing shaders");
        }
    }
}

void Renderer::SetLightVolumeShaders(Batch& batch)
{
    unsigned vsi = DLVS_NONE;
    unsigned psi = DLPS_NONE;
    Light* light = batch.light_;
    
    switch(light->GetLightType())
    {
    case LIGHT_DIRECTIONAL:
        vsi += DLVS_DIR;
        break;
        
    case LIGHT_POINT:
    case LIGHT_SPLITPOINT:
        if (light->GetShapeTexture())
            psi += DLPS_POINTMASK;
        else
            psi += DLPS_POINT;
        break;
        
    case LIGHT_SPOT:
        psi += DLPS_SPOT;
        break;
    }
    
    if (light->GetShadowMap())
        psi += DLPS_SHADOW;
    
    if ((specularLighting_) && (light->GetSpecularIntensity() > 0.0))
        psi += DLPS_SPEC;
    
    if (batch.camera_->IsOrthographic())
    {
        vsi += DLVS_ORTHO;
        psi += DLPS_ORTHO;
    }
    
    unsigned hwShadows = graphics_->GetHardwareShadowSupport() ? 1 : 0;
    
    if (!lightVS_[vsi])
        lightVS_[vsi] = GetVertexShader(lightShaderName_ + deferredLightVSVariations[vsi]);
    
    if (!lightPS_[psi])
    {
        unsigned variation = psi % DLPS_SPOT;
        if ((variation == DLPS_SHADOW) || (variation == DLPS_SHADOWSPEC))
            lightPS_[psi] = GetPixelShader(lightShaderName_ + lightPSVariations[psi] + hwVariations[hwShadows]);
        else
            lightPS_[psi] = GetPixelShader(lightShaderName_ + lightPSVariations[psi]);
    }
    
    batch.material_ = 0;
    batch.pass_ = 0;
    batch.vertexShader_ = lightVS_[vsi];
    batch.pixelShader_ = lightPS_[psi];
    batch.vertexShaderIndex_ = vsi;
    batch.CalculateSortKey();
}

void Renderer::LoadShaders()
{
    LOGINFO("Reloading shaders");
    
    // Release old material shaders, mark them for reload
    ReleaseMaterialShaders();
    shadersChangedFrameNumber_ = GetSubsystem<Time>()->GetFrameNumber();
    
    // Load inbuilt shaders
    stencilVS_ = GetVertexShader("Stencil");
    stencilPS_ = GetPixelShader("Stencil");
    lightVS_.Clear();
    lightPS_.Clear();
    
    RenderMode mode = graphics_->GetRenderMode();
    if (mode != RENDER_FORWARD)
    {
        // There are rather many light volume shader variations, so load them later on-demand
        lightVS_.Resize(MAX_DEFERRED_LIGHT_VS_VARIATIONS);
        lightPS_.Resize(MAX_DEFERRED_LIGHT_PS_VARIATIONS);
        if (mode == RENDER_DEFERRED)
            lightShaderName_ = "Deferred/Light_";
        else
            lightShaderName_ = "Prepass/Light_";
    }
    
    // Remove shaders that are no longer referenced from the cache
    cache_->ReleaseResources(Shader::GetTypeStatic());
    
    shadersDirty_ = false;
}

void Renderer::LoadMaterialShaders(Technique* technique)
{
    LoadPassShaders(technique, PASS_SHADOW);
    LoadPassShaders(technique, PASS_EXTRA);
    
    RenderMode mode = graphics_->GetRenderMode();
    if (mode == RENDER_FORWARD)
    {
        LoadPassShaders(technique, PASS_BASE);
        LoadPassShaders(technique, PASS_LITBASE);
        LoadPassShaders(technique, PASS_LIGHT);
    }
    else
    {
        // G-Buffer pass types depend on whether deferred shading or light prepass is in use
        if (mode == RENDER_DEFERRED)
            LoadPassShaders(technique, PASS_DEFERRED);
        else if (mode == RENDER_PREPASS)
        {
            LoadPassShaders(technique, PASS_PREPASS);
            LoadPassShaders(technique, PASS_MATERIAL);
        }
        else
        {
            LoadPassShaders(technique, PASS_BASE);
            // If shadow maps are not reused, transparencies can be rendered shadowed
            LoadPassShaders(technique, PASS_LITBASE, !reuseShadowMaps_);
            LoadPassShaders(technique, PASS_LIGHT, !reuseShadowMaps_);
        }
    }
}

void Renderer::LoadPassShaders(Technique* technique, PassType pass, bool allowShadows)
{
    Map<PassType, Pass>::Iterator i = technique->passes_.Find(pass);
    if (i == technique->passes_.End())
        return;
    
    String vertexShaderName = i->second_.GetVertexShaderName();
    String pixelShaderName = i->second_.GetPixelShaderName();
    
    // Check if the shader name is already a variation in itself
    if (vertexShaderName.Find('_') == String::NPOS)
        vertexShaderName += "_";
    if (pixelShaderName.Find('_') == String::NPOS)
        pixelShaderName += "_";
    
    // If ambient pass is not using REPLACE as the blend mode, and shadow maps are reused, do not load shadow variations
    if ((reuseShadowMaps_) && ((pass == PASS_LIGHT) || (pass == PASS_LITBASE)))
    {
        if ((!technique->HasPass(PASS_BASE)) || (technique->GetPass(PASS_BASE)->GetBlendMode() != BLEND_REPLACE))
            allowShadows = false;
    }
    
    unsigned hwShadows = graphics_->GetHardwareShadowSupport() ? 1 : 0;
    
    Vector<SharedPtr<ShaderVariation> >& vertexShaders = i->second_.GetVertexShaders();
    Vector<SharedPtr<ShaderVariation> >& pixelShaders = i->second_.GetPixelShaders();
    
    // Forget all the old shaders
    vertexShaders.Clear();
    pixelShaders.Clear();
    
    switch (i->first_)
    {
    default:
        vertexShaders.Resize(MAX_GEOMETRYTYPES);
        pixelShaders.Resize(1);
        for (unsigned j = 0; j < MAX_GEOMETRYTYPES; ++j)
            vertexShaders[j] = GetVertexShader(vertexShaderName + geometryVSVariations[j], j != 0);
        pixelShaders[0] = GetPixelShader(pixelShaderName);
        break;
        
    case PASS_LITBASE:
    case PASS_LIGHT:
        {
            // In first light pass, load only directional light shaders
            unsigned numPS = i->first_ == PASS_LIGHT ? MAX_LIGHT_PS_VARIATIONS : LPS_SPOT;
            
            vertexShaders.Resize(MAX_GEOMETRYTYPES * MAX_LIGHT_VS_VARIATIONS);
            pixelShaders.Resize(numPS);
            
            for (unsigned j = 0; j < MAX_GEOMETRYTYPES * MAX_LIGHT_VS_VARIATIONS; ++j)
            {
                unsigned g = j / MAX_LIGHT_VS_VARIATIONS;
                unsigned l = j % MAX_LIGHT_VS_VARIATIONS;
                if ((!(l & LVS_SHADOW)) || (allowShadows))
                    vertexShaders[j] = GetVertexShader(vertexShaderName + lightVSVariations[l] + geometryVSVariations[g], g != 0);
                else
                    vertexShaders[j].Reset();
            }
            for (unsigned j = 0; j < numPS; ++j)
            {
                unsigned variation = j % LPS_SPOT;
                if ((variation == LPS_SHADOW) || (variation == LPS_SHADOWSPEC))
                {
                    if (allowShadows)
                        pixelShaders[j] = GetPixelShader(pixelShaderName + lightPSVariations[j] +
                            hwVariations[hwShadows]);
                    else
                        pixelShaders[j].Reset();
                }
                else
                    pixelShaders[j] = GetPixelShader(pixelShaderName + lightPSVariations[j]);
            }
            break;
        }
    }
    
    technique->MarkShadersLoaded(shadersChangedFrameNumber_);
}

void Renderer::ReleaseMaterialShaders()
{
    PODVector<Material*> materials;
    cache_->GetResources<Material>(materials);
    
    for (unsigned i = 0; i < materials.Size(); ++i)
        materials[i]->ReleaseShaders();
}

void Renderer::ReloadTextures()
{
    PODVector<Resource*> textures;
    
    cache_->GetResources(textures, Texture2D::GetTypeStatic());
    for (unsigned i = 0; i < textures.Size(); ++i)
        cache_->ReloadResource(textures[i]);
    
    cache_->GetResources(textures, TextureCube::GetTypeStatic());
    for (unsigned i = 0; i < textures.Size(); ++i)
        cache_->ReloadResource(textures[i]);
}

void Renderer::CreateGeometries()
{
    SharedPtr<VertexBuffer> dlvb(new VertexBuffer(context_));
    dlvb->SetSize(4, MASK_POSITION);
    dlvb->SetData(dirLightVertexData);
    
    SharedPtr<IndexBuffer> dlib(new IndexBuffer(context_));
    dlib->SetSize(6, false);
    dlib->SetData(dirLightIndexData);
    
    dirLightGeometry_ = new Geometry(context_);
    dirLightGeometry_->SetVertexBuffer(0, dlvb);
    dirLightGeometry_->SetIndexBuffer(dlib);
    dirLightGeometry_->SetDrawRange(TRIANGLE_LIST, 0, dlib->GetIndexCount());
    
    SharedPtr<VertexBuffer> plvb(new VertexBuffer(context_));
    plvb->SetSize(24, MASK_POSITION);
    plvb->SetData(pointLightVertexData);
    
    SharedPtr<IndexBuffer> plib(new IndexBuffer(context_));
    plib->SetSize(132, false);
    plib->SetData(pointLightIndexData);
    
    pointLightGeometry_ = new Geometry(context_);
    pointLightGeometry_->SetVertexBuffer(0, plvb);
    pointLightGeometry_->SetIndexBuffer(plib);
    pointLightGeometry_->SetDrawRange(TRIANGLE_LIST, 0, plib->GetIndexCount());
    
    SharedPtr<VertexBuffer> slvb(new VertexBuffer(context_));
    slvb->SetSize(8, MASK_POSITION);
    slvb->SetData(spotLightVertexData);
    
    SharedPtr<IndexBuffer> slib(new IndexBuffer(context_));
    slib->SetSize(36, false);
    slib->SetData(spotLightIndexData);
    
    spotLightGeometry_ = new Geometry(context_);
    spotLightGeometry_->SetVertexBuffer(0, slvb);
    spotLightGeometry_->SetIndexBuffer(slib);
    spotLightGeometry_->SetDrawRange(TRIANGLE_LIST, 0, slib->GetIndexCount());
}

void Renderer::CreateInstancingBuffer()
{
    // Do not create buffer if instancing not supported
    if (!graphics_->GetSM3Support())
    {
        dynamicInstancing_ = false;
        return;
    }
    
    // If must lock the buffer for each batch group, set a smaller size
    unsigned defaultSize = graphics_->GetStreamOffsetSupport() ? INSTANCING_BUFFER_DEFAULT_SIZE : INSTANCING_BUFFER_DEFAULT_SIZE / 4;
    
    instancingBuffer_ = new VertexBuffer(context_);
    if (!instancingBuffer_->SetSize(defaultSize, INSTANCING_BUFFER_MASK, true))
    {
        instancingBuffer_.Reset();
        dynamicInstancing_ = false;
    }
}

bool Renderer::ResizeInstancingBuffer(unsigned numInstances)
{
    if (!instancingBuffer_)
        return false;
    
    unsigned oldSize = instancingBuffer_->GetVertexCount();
    if (numInstances <= oldSize)
        return true;
    
    unsigned newSize = INSTANCING_BUFFER_DEFAULT_SIZE;
    while (newSize < numInstances)
        newSize <<= 1;
    
    if (!instancingBuffer_->SetSize(newSize, INSTANCING_BUFFER_MASK, true))
    {
        LOGERROR("Failed to resize instancing buffer to " + String(newSize));
        // If failed, try to restore the old size
        instancingBuffer_->SetSize(oldSize, INSTANCING_BUFFER_MASK, true);
        return false;
    }
    
    LOGDEBUG("Resized instancing buffer to " + String(newSize));
    return true;
}

bool Renderer::CreateShadowMaps()
{
    unsigned shadowMapFormat = shadowMapHiresDepth_ ? graphics_->GetHiresShadowMapFormat() : graphics_->GetShadowMapFormat();
    unsigned dummyColorFormat = graphics_->GetDummyColorFormat();
    bool hardwarePCF = graphics_->GetHardwareShadowSupport();
    
    if (!shadowMapFormat)
        return false;
    
    if (!drawShadows_)
    {
        for (unsigned i = 0; i < NUM_SHADOWMAP_RESOLUTIONS; ++i)
        {
            for (unsigned j = 0; j < shadowMaps_[i].Size(); ++j)
                shadowMaps_[i][j].Reset();
        }
        return true;
    }
    
    #ifdef USE_OPENGL
    
    // Create shadow maps only. Color rendertargets are not needed
    unsigned size = shadowMapSize_;
    for (unsigned i = 0; i < NUM_SHADOWMAP_RESOLUTIONS; ++i)
    {
        for (unsigned j = 0; j < shadowMaps_[i].Size(); ++j)
        {
            if (!shadowMaps_[i][j])
                shadowMaps_[i][j] = new Texture2D(context_);
            if (!shadowMaps_[i][j]->SetSize(size, size, shadowMapFormat, TEXTURE_DEPTHSTENCIL))
                return false;
            shadowMaps_[i][j]->SetFilterMode(FILTER_BILINEAR);
            shadowMaps_[i][j]->SetShadowCompare(true);
        }
        size >>= 1;
    }
    
    #else
    
    // Create shadow maps and dummy color rendertargets
    unsigned size = shadowMapSize_;
    for (unsigned i = 0; i < NUM_SHADOWMAP_RESOLUTIONS; ++i)
    {
        if (!colorShadowMaps_[i])
            colorShadowMaps_[i] = new Texture2D(context_);
        if (!colorShadowMaps_[i]->SetSize(size, size, dummyColorFormat, TEXTURE_RENDERTARGET))
            return false;
        
        for (unsigned j = 0; j < shadowMaps_[i].Size(); ++j)
        {
            if (!shadowMaps_[i][j])
                shadowMaps_[i][j] = new Texture2D(context_);
            if (!shadowMaps_[i][j]->SetSize(size, size, shadowMapFormat, TEXTURE_DEPTHSTENCIL))
                return false;
            shadowMaps_[i][j]->SetFilterMode(hardwarePCF ? FILTER_BILINEAR : FILTER_NEAREST);
            
            // Link the color rendertarget to depth rendertarget
            shadowMaps_[i][j]->GetRenderSurface()->SetLinkedRenderTarget(colorShadowMaps_[i]->GetRenderSurface());
        }
        size >>= 1;
    }
    
    #endif
    
    return true;
}

Camera* Renderer::CreateShadowCamera()
{
    if (numShadowCameras_ >= shadowCameraStore_.Size())
        shadowCameraStore_.Push(SharedPtr<Camera>(new Camera(context_)));
    Camera* camera = shadowCameraStore_[numShadowCameras_];
    camera->SetNode(CreateTempNode());
    
    ++numShadowCameras_;
    return camera;
}

Light* Renderer::CreateSplitLight(Light* original)
{
    if (numSplitLights_ >= splitLightStore_.Size())
        splitLightStore_.Push(SharedPtr<Light>(new Light(context_)));
    Light* light = splitLightStore_[numSplitLights_];
    light->SetNode(CreateTempNode());
    light->copyFrom(original);
    
    ++numSplitLights_;
    return light;
}

Node* Renderer::CreateTempNode()
{
    if (numTempNodes_ >= tempNodeStore_.Size())
        tempNodeStore_.Push(SharedPtr<Node>(new Node(context_)));
    Node* node = tempNodeStore_[numTempNodes_];
    
    ++numTempNodes_;
    return node;
}

void Renderer::SetupLightBatch(Batch& batch)
{
    graphics_->ClearTransformSources();
    Matrix3x4 view(batch.camera_->GetInverseWorldTransform());
    
    Light* light = batch.light_;
    float lightExtent = light->GetVolumeExtent();
    float lightViewDist = (light->GetWorldPosition() - batch.camera_->GetWorldPosition()).LengthFast();
    
    graphics_->SetAlphaTest(false);
    graphics_->SetBlendMode(BLEND_ADD);
    graphics_->SetDepthWrite(false);
    
    if (light->GetLightType() == LIGHT_DIRECTIONAL)
    {
        // Get projection without jitter offset to ensure the whole screen is filled
        Matrix4 projection(batch.camera_->GetProjection(false));
        
        // If the light does not extend to the near plane, use a stencil test. Else just draw with depth fail
        if (light->GetNearSplit() <= batch.camera_->GetNearClip())
        {
            graphics_->SetCullMode(CULL_NONE);
            graphics_->SetDepthTest(CMP_GREATER);
            graphics_->SetStencilTest(false);
        }
        else
        {
            Matrix3x4 nearTransform = light->GetDirLightTransform(*batch.camera_, true);
            
            // Set state for stencil rendering
            graphics_->SetColorWrite(false);
            graphics_->SetCullMode(CULL_NONE);
            graphics_->SetDepthTest(CMP_LESSEQUAL);
            graphics_->SetStencilTest(true, CMP_ALWAYS, OP_INCR, OP_KEEP, OP_KEEP, 1);
            graphics_->SetShaders(stencilVS_, stencilPS_);
            graphics_->SetShaderParameter(VSP_VIEWPROJ, projection);
            graphics_->SetShaderParameter(VSP_MODEL, nearTransform);
            
            // Draw to stencil
            batch.geometry_->Draw(graphics_);
            
            // Re-enable color write, set test for rendering the actual light
            graphics_->SetColorWrite(true);
            graphics_->SetDepthTest(CMP_GREATER);
            graphics_->SetStencilTest(true, CMP_EQUAL, OP_ZERO, OP_KEEP, OP_ZERO, 1);
        }
    }
    else
    {
        Matrix4 projection(batch.camera_->GetProjection());
        const Matrix3x4& model = light->GetVolumeTransform(*batch.camera_);
        
        if (light->GetLightType() == LIGHT_SPLITPOINT)
        {
            // Shadowed point light, split in 6 frustums: mask out overlapping pixels to prevent overlighting
            // Check whether we should draw front or back faces
            bool drawBackFaces = lightViewDist < (lightExtent + batch.camera_->GetNearClip());
            graphics_->SetColorWrite(false);
            graphics_->SetCullMode(drawBackFaces ? CULL_CCW : CULL_CW);
            graphics_->SetDepthTest(drawBackFaces ? CMP_GREATER : CMP_LESS);
            graphics_->SetStencilTest(true, CMP_EQUAL, OP_INCR, OP_KEEP, OP_KEEP, 0);
            graphics_->SetShaders(stencilVS_, stencilPS_);
            graphics_->SetShaderParameter(VSP_VIEWPROJ, projection * view);
            graphics_->SetShaderParameter(VSP_MODEL, model);
            
            // Draw the other faces to stencil to mark where we should not draw
            batch.geometry_->Draw(graphics_);
            
            graphics_->SetColorWrite(true);
            graphics_->SetCullMode(drawBackFaces ? CULL_CW : CULL_CCW);
            graphics_->SetStencilTest(true, CMP_EQUAL, OP_DECR, OP_DECR, OP_KEEP, 0);
        }
        else
        {
            // If light is close to near clip plane, we might be inside light volume
            if (lightViewDist < (lightExtent + batch.camera_->GetNearClip()))
            {
                // In this case reverse cull mode & depth test and render back faces
                graphics_->SetCullMode(CULL_CW);
                graphics_->SetDepthTest(CMP_GREATER);
                graphics_->SetStencilTest(false);
            }
            else
            {
                // If not too close to far clip plane, write the back faces to stencil for optimization,
                // then render front faces. Else just render front faces.
                if (lightViewDist < (batch.camera_->GetFarClip() - lightExtent))
                {
                    // Set state for stencil rendering
                    graphics_->SetColorWrite(false);
                    graphics_->SetCullMode(CULL_CW);
                    graphics_->SetDepthTest(CMP_GREATEREQUAL);
                    graphics_->SetStencilTest(true, CMP_ALWAYS, OP_INCR, OP_KEEP, OP_KEEP, 1);
                    graphics_->SetShaders(stencilVS_, stencilPS_);
                    graphics_->SetShaderParameter(VSP_VIEWPROJ, projection * view);
                    graphics_->SetShaderParameter(VSP_MODEL, model);
                    
                    // Draw to stencil
                    batch.geometry_->Draw(graphics_);
                    
                    // Re-enable color write, set test for rendering the actual light
                    graphics_->SetColorWrite(true);
                    graphics_->SetStencilTest(true, CMP_EQUAL, OP_ZERO, OP_KEEP, OP_ZERO, 1);
                    graphics_->SetCullMode(CULL_CCW);
                    graphics_->SetDepthTest(CMP_LESS);
                }
                else
                {
                    graphics_->SetStencilTest(false);
                    graphics_->SetCullMode(CULL_CCW);
                    graphics_->SetDepthTest(CMP_LESS);
                }
            }
        }
    }
}

void Renderer::DrawFullScreenQuad(Camera& camera, ShaderVariation* vs, ShaderVariation* ps, bool nearQuad, const HashMap<ShaderParameter, Vector4>& shaderParameters)
{
    graphics_->ClearTransformSources();
    
    Light quadDirLight(context_);
    Matrix3x4 model(quadDirLight.GetDirLightTransform(camera, nearQuad));
    
    graphics_->SetCullMode(CULL_NONE);
    graphics_->SetShaders(vs, ps);
    graphics_->SetShaderParameter(VSP_MODEL, model);
    // Get projection without jitter offset to ensure the whole screen is filled
    graphics_->SetShaderParameter(VSP_VIEWPROJ, camera.GetProjection(false));
    
    // Set global shader parameters as needed
    for (HashMap<ShaderParameter, Vector4>::ConstIterator i = shaderParameters.Begin(); i != shaderParameters.End(); ++i)
    {
        if (graphics_->NeedParameterUpdate(i->first_, &shaderParameters))
            graphics_->SetShaderParameter(i->first_, i->second_);
    }
    
    dirLightGeometry_->Draw(graphics_);
}

void Renderer::HandleScreenMode(StringHash eventType, VariantMap& eventData)
{
    if (!initialized_)
        Initialize();
    else
    {
        // When screen mode changes, reload shaders and purge old views and occlusion buffers
        shadersDirty_ = true;
        occlusionBuffers_.Clear();
        ResetViews();
    }
}

void Renderer::HandleRenderUpdate(StringHash eventType, VariantMap& eventData)
{
    if (initialized_)
    {
        using namespace RenderUpdate;
        
        Update(eventData[P_TIMESTEP].GetFloat());
    }
}
