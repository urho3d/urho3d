//
// Urho3D Engine
// Copyright (c) 2008-2012 Lasse Öörni
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
#include "Log.h"
#include "Material.h"
#include "OcclusionBuffer.h"
#include "Octree.h"
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

namespace Urho3D
{

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

static const String shadowVariations[] =
{
    // No specific hardware shadow compare variation on OpenGL, it is always supported
    #ifdef USE_OPENGL
    "LQ",
    "LQ",
    "",
    ""
    #else
    "",
    "LQHW",
    "",
    "HW"
    #endif
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
    "Dir",
    "Spot",
    "Point",
    "DirSpec",
    "SpotSpec",
    "PointSpec",
    "DirShadow",
    "SpotShadow",
    "PointShadow",
    "DirSpecShadow",
    "SpotSpecShadow",
    "PointSpecShadow"
};

static const String vertexLightVSVariations[] =
{
    "",
    "1VL",
    "2VL",
    "3VL",
    "4VL",
    "5VL",
    "6VL"
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
    "Spot",
    "Point",
    "PointMask",
    "DirSpec",
    "SpotSpec",
    "PointSpec",
    "PointMaskSpec",
    "DirShadow",
    "SpotShadow",
    "PointShadow",
    "PointMaskShadow",
    "DirSpecShadow",
    "SpotSpecShadow",
    "PointSpecShadow",
    "PointMaskSpecShadow"
};

static const unsigned INSTANCING_BUFFER_MASK = MASK_INSTANCEMATRIX1 | MASK_INSTANCEMATRIX2 | MASK_INSTANCEMATRIX3;
static const unsigned MAX_BUFFER_AGE = 2000;

OBJECTTYPESTATIC(Renderer);

Renderer::Renderer(Context* context) :
    Object(context),
    defaultZone_(new Zone(context)),
    quadDirLight_(new Light(context)),
    renderMode_(RENDER_FORWARD),
    textureAnisotropy_(4),
    textureFilterMode_(FILTER_TRILINEAR),
    textureQuality_(QUALITY_HIGH),
    materialQuality_(QUALITY_HIGH),
    shadowMapSize_(1024),
    shadowQuality_(SHADOWQUALITY_HIGH_16BIT),
    maxShadowMaps_(1),
    maxShadowCascades_(MAX_CASCADE_SPLITS),
    maxInstanceTriangles_(500),
    maxSortedInstances_(1000),
    maxOccluderTriangles_(5000),
    occlusionBufferSize_(256),
    occluderSizeThreshold_(0.025f),
    numViews_(0), 
    numOcclusionBuffers_(0),
    numShadowCameras_(0),
    shadersChangedFrameNumber_(M_MAX_UNSIGNED),
    specularLighting_(true),
    drawShadows_(true),
    reuseShadowMaps_(true),
    dynamicInstancing_(true),
    shadersDirty_(true),
    initialized_(false)
{
    SubscribeToEvent(E_SCREENMODE, HANDLER(Renderer, HandleScreenMode));
    SubscribeToEvent(E_GRAPHICSFEATURES, HANDLER(Renderer, HandleGraphicsFeatures));
    SubscribeToEvent(E_RENDERUPDATE, HANDLER(Renderer, HandleRenderUpdate));
    
    quadDirLight_->SetLightType(LIGHT_DIRECTIONAL);
    
    // Try to initialize right now, but skip if screen mode is not yet set
    Initialize();
    SetNumViewports(1);
}

Renderer::~Renderer()
{
}

void Renderer::SetNumViewports(unsigned num)
{
    viewports_.Resize(num);
    
    for (unsigned i = 0; i < viewports_.Size(); ++i)
    {
        if (!viewports_[i])
            viewports_[i] = new Viewport();
    }
}

bool Renderer::SetViewport(unsigned index, Viewport* viewport)
{
    if (index >= viewports_.Size())
    {
        LOGERROR("Viewport index out of bounds");
        return false;
    }
    
    if (!viewport)
    {
        LOGERROR("Null viewport");
        return false;
    }
    
    viewports_[index] = viewport;
    return true;
}

void Renderer::SetRenderMode(RenderMode mode)
{
    if (!initialized_)
    {
        LOGERROR("Can not switch rendering mode before setting initial screen mode");
        return;
    }
    
    if (mode == RENDER_PREPASS && !graphics_->GetLightPrepassSupport())
        mode = RENDER_FORWARD;
    if (mode == RENDER_DEFERRED && !graphics_->GetDeferredSupport())
        mode = RENDER_FORWARD;
    
    if (mode != renderMode_)
    {
        // Deferred rendering is incompatible with hardware multisampling, so set new screen mode with 1x sampling if in use
        if (mode != RENDER_FORWARD && graphics_->GetMultiSample() > 1)
        {
            graphics_->SetMode(graphics_->GetWidth(), graphics_->GetHeight(), graphics_->GetFullscreen(), graphics_->GetVSync(),
                graphics_->GetTripleBuffer(), 1);
        }
        
        ResetBuffers();
        ResetShadowMaps();
        renderMode_ = mode;
        shadersDirty_ = true;
    }
}

void Renderer::SetSpecularLighting(bool enable)
{
    specularLighting_ = enable;
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

void Renderer::SetDrawShadows(bool enable)
{
    if (!graphics_ || !graphics_->GetShadowMapFormat())
        return;
    
    drawShadows_ = enable;
    if (!drawShadows_)
        ResetShadowMaps();
}

void Renderer::SetShadowMapSize(int size)
{
    if (!graphics_)
        return;
    
    size = NextPowerOfTwo(Max(size, SHADOW_MIN_PIXELS));
    if (size != shadowMapSize_)
    {
        shadowMapSize_ = size;
        ResetShadowMaps();
    }
}

void Renderer::SetShadowQuality(int quality)
{
    if (!graphics_)
        return;
    
    quality &= SHADOWQUALITY_HIGH_24BIT;
    
    // If no hardware PCF, do not allow to select one-sample quality
    if (!graphics_->GetHardwareShadowSupport())
        quality |= SHADOWQUALITY_HIGH_16BIT;
    if (!graphics_->GetHiresShadowMapFormat())
        quality &= SHADOWQUALITY_HIGH_16BIT;
    
    if (quality != shadowQuality_)
    {
        shadowQuality_ = quality;
        shadersDirty_ = true;
        ResetShadowMaps();
    }
}

void Renderer::SetReuseShadowMaps(bool enable)
{
    if (enable == reuseShadowMaps_)
        return;
    
    reuseShadowMaps_ = enable;
}

void Renderer::SetMaxShadowMaps(int shadowMaps)
{
    if (shadowMaps < 1)
        return;
    
    maxShadowMaps_ = shadowMaps;
    for (HashMap<int, Vector<SharedPtr<Texture2D> > >::Iterator i = shadowMaps_.Begin(); i != shadowMaps_.End(); ++i)
    {
        if ((int)i->second_.Size() > maxShadowMaps_)
            i->second_.Resize(maxShadowMaps_);
    }
}

void Renderer::SetMaxShadowCascades(int cascades)
{
    cascades = Clamp(cascades, 1, MAX_CASCADE_SPLITS);
    
    if (cascades != maxShadowCascades_)
    {
        maxShadowCascades_ = cascades;
        ResetShadowMaps();
    }
}

void Renderer::SetDynamicInstancing(bool enable)
{
    if (!instancingBuffer_)
        enable = false;
    
    dynamicInstancing_ = enable;
}

void Renderer::SetMaxInstanceTriangles(int triangles)
{
    maxInstanceTriangles_ = Max(triangles, 0);
}

void Renderer::SetMaxSortedInstances(int instances)
{
    maxSortedInstances_ = Max(instances, 0);
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

void Renderer::ReloadShaders()
{
    shadersDirty_ = true;
}

Viewport* Renderer::GetViewport(unsigned index) const
{
    return index < viewports_.Size() ? viewports_[index] : (Viewport*)0;
}

int Renderer::GetMaxShadowCascades() const
{
    // Due to instruction count limits, deferred modes in SM2.0 can only support up to 3 cascades
    #ifndef USE_OPENGL
    if (renderMode_ != RENDER_FORWARD && !graphics_->GetSM3Support())
        return Max(maxShadowCascades_, 3);
    #endif
    
    return maxShadowCascades_;
}

ShaderVariation* Renderer::GetVertexShader(const String& name, bool checkExists) const
{
    return GetShader(VS, name, checkExists);
}

ShaderVariation* Renderer::GetPixelShader(const String& name, bool checkExists) const
{
    return GetShader(PS, name, checkExists);
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
    unsigned numLights = 0;
    unsigned lastView = allViews ? numViews_ : 1;
    
    for (unsigned i = 0; i < lastView; ++i)
        numLights += views_[i]->GetLights().Size();
    
    return numLights;
}

unsigned Renderer::GetNumShadowMaps(bool allViews) const
{
    unsigned numShadowMaps = 0;
    unsigned lastView = allViews ? numViews_ : 1;
    
    for (unsigned i = 0; i < lastView; ++i)
    {
        const Vector<LightBatchQueue>& lightQueues = views_[i]->GetLightQueues();
        
        for (Vector<LightBatchQueue>::ConstIterator i = lightQueues.Begin(); i != lightQueues.End(); ++i)
        {
            if (i->shadowMap_)
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

void Renderer::Update(float timeStep)
{
    PROFILE(UpdateViews);
    
    numViews_ = 0;
    
    // If device lost, do not perform update. This is because any dynamic vertex/index buffer updates happen already here,
    // and if the device is lost, the updates queue up, causing memory use to rise constantly
    if (!graphics_ || !graphics_->IsInitialized() || graphics_->IsDeviceLost())
        return;
    
    // Set up the frameinfo structure for this frame
    frame_.frameNumber_ = GetSubsystem<Time>()->GetFrameNumber();
    frame_.timeStep_ = timeStep;
    frame_.camera_ = 0;
    numShadowCameras_ = 0;
    numOcclusionBuffers_ = 0;
    updatedOctrees_.Clear();
    
    // Reload shaders now if needed
    if (shadersDirty_)
        LoadShaders();
    
    // Process all viewports. Use reverse order, because during rendering the order will be reversed again
    // to handle auxiliary view dependencies correctly
    for (unsigned i = viewports_.Size() - 1; i < viewports_.Size(); --i)
    {
        unsigned mainView = numViews_;
        Viewport* viewport = viewports_[i];
        if (!viewport || !AddView(0, viewport))
            continue;
        
        const IntRect& viewRect = viewport->GetRect();
        Scene* scene = viewport->GetScene();
        
        // Update octree (perform early update for drawables which need that, and reinsert moved drawables.)
        // However, if the same scene is viewed from multiple cameras, update the octree only once
        Octree* octree = scene->GetComponent<Octree>();
        if (!updatedOctrees_.Contains(octree))
        {
            frame_.camera_ = viewport->GetCamera();
            frame_.viewSize_ = IntVector2(viewRect.right_ - viewRect.left_, viewRect.bottom_ - viewRect.top_);
            if (frame_.viewSize_ == IntVector2::ZERO)
                frame_.viewSize_ = IntVector2(graphics_->GetWidth(), graphics_->GetHeight());
            octree->Update(frame_);
            updatedOctrees_.Insert(octree);
            
            // Set also the view for the debug graphics already here, so that it can use culling
            /// \todo May result in incorrect debug geometry culling if the same scene is drawn from multiple viewports
            DebugRenderer* debug = scene->GetComponent<DebugRenderer>();
            if (debug)
                debug->SetView(viewport->GetCamera());
        }
        
        // Update the viewport's main view and any auxiliary views it has created
        for (unsigned i = mainView; i < numViews_; ++i)
        {
            // Reset shadow map allocations; they can be reused between views as each is rendered completely at a time
            ResetShadowMapAllocations();
            views_[i]->Update(frame_);
        }
    }
}

void Renderer::Render()
{
    if (!graphics_)
        return;
    
    PROFILE(RenderViews);
    
    // If the indirection textures have lost content (OpenGL mode only), restore them now
    if (faceSelectCubeMap_ && faceSelectCubeMap_->IsDataLost())
        SetIndirectionTextureData();
    
    graphics_->SetDefaultTextureFilterMode(textureFilterMode_);
    graphics_->SetTextureAnisotropy(textureAnisotropy_);
    graphics_->ClearParameterSources();
    
    // If no views, just clear the screen
    if (!numViews_)
    {
        graphics_->SetBlendMode(BLEND_REPLACE);
        graphics_->SetColorWrite(true);
        graphics_->SetDepthWrite(true);
        graphics_->SetScissorTest(false);
        graphics_->SetStencilTest(false);
        graphics_->ResetRenderTargets();
        graphics_->Clear(CLEAR_COLOR | CLEAR_DEPTH | CLEAR_STENCIL);
        
        numPrimitives_ = 0;
        numBatches_ = 0;
    }
    else
    {
        // Render views from last to first (each main view is rendered after the auxiliary views it depends on)
        for (unsigned i = numViews_ - 1; i < numViews_; --i)
        {
            // Screen buffers can be reused between views, as each is rendered completely
            PrepareViewRender();
            views_[i]->Render();
        }
        
        // Copy the number of batches & primitives from Graphics so that we can account for 3D geometry only
        numPrimitives_ = graphics_->GetNumPrimitives();
        numBatches_ = graphics_->GetNumBatches();
    }
    
    // Remove unused occlusion buffers and renderbuffers
    RemoveUnusedBuffers();
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
        DebugRenderer* debug = octree->GetComponent<DebugRenderer>();
        if (!debug)
            continue;
        
        const PODVector<Drawable*>& geometries = view->GetGeometries();
        const PODVector<Light*>& lights = view->GetLights();
        
        for (unsigned i = 0; i < geometries.Size(); ++i)
        {
            if (!processedGeometries.Contains(geometries[i]))
            {
                geometries[i]->DrawDebugGeometry(debug, depthTest);
                processedGeometries.Insert(geometries[i]);
            }
        }
        for (unsigned i = 0; i < lights.Size(); ++i)
        {
            if (!processedLights.Contains(lights[i]))
            {
                lights[i]->DrawDebugGeometry(debug, depthTest);
                processedLights.Insert(lights[i]);
            }
        }
    }
}

bool Renderer::AddView(RenderSurface* renderTarget, Viewport* viewport)
{
    // If using a rendertarget texture, make sure it will not be rendered to multiple times
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

Geometry* Renderer::GetLightGeometry(Light* light)
{
    LightType type = light->GetLightType();
    if (type == LIGHT_DIRECTIONAL)
        return dirLightGeometry_;
    if (type == LIGHT_SPOT)
        return spotLightGeometry_;
    else if (type == LIGHT_POINT)
        return pointLightGeometry_;
    else
        return 0;
}

Texture2D* Renderer::GetShadowMap(Light* light, Camera* camera, unsigned viewWidth, unsigned viewHeight)
{
    LightType type = light->GetLightType();
    const FocusParameters& parameters = light->GetShadowFocus();
    float size = (float)shadowMapSize_ * light->GetShadowResolution();
    // Automatically reduce shadow map size when far away
    if (parameters.autoSize_ && type != LIGHT_DIRECTIONAL)
    {
        const Matrix3x4& view = camera->GetInverseWorldTransform();
        const Matrix4& projection = camera->GetProjection();
        BoundingBox lightBox;
        float lightPixels;
        
        if (type == LIGHT_POINT)
        {
            // Calculate point light pixel size from the projection of its diagonal
            Vector3 center = view * light->GetNode()->GetWorldPosition();
            float extent = 0.58f * light->GetRange();
            lightBox.Define(center + Vector3(extent, extent, extent), center - Vector3(extent, extent, extent));
        }
        else
        {
            // Calculate spot light pixel size from the projection of its frustum far vertices
            Frustum lightFrustum = light->GetFrustum().Transformed(view);
            lightBox.Define(&lightFrustum.vertices_[4], 4);
        }
        
        Vector2 projectionSize = lightBox.Projected(projection).Size();
        lightPixels = Max(0.5f * (float)viewWidth * projectionSize.x_, 0.5f * (float)viewHeight * projectionSize.y_);
        
        // Clamp pixel amount to a sufficient minimum to avoid self-shadowing artifacts due to loss of precision
        if (lightPixels < SHADOW_MIN_PIXELS)
            lightPixels = SHADOW_MIN_PIXELS;
        
        size = Min(size, lightPixels);
    }
    
    /// \todo Allow to specify maximum shadow maps per resolution, as smaller shadow maps take less memory
    int width = NextPowerOfTwo((unsigned)size);
    int height = width;
    
    // Adjust the size for directional or point light shadow map atlases
    if (type == LIGHT_DIRECTIONAL)
    {
        if (maxShadowCascades_ > 1)
            width *= 2;
        if (maxShadowCascades_ > 2)
            height *= 2;
    }
    else if (type == LIGHT_POINT)
    {
        width *= 2;
        height *= 3;
    }
    
    int searchKey = (width << 16) | height;
    if (shadowMaps_.Contains(searchKey))
    {
        // If shadow maps are reused, always return the first
        if (reuseShadowMaps_)
            return shadowMaps_[searchKey][0];
        else
        {
            // If not reused, check allocation count and return existing shadow map if possible
            unsigned allocated = shadowMapAllocations_[searchKey].Size();
            if (allocated < shadowMaps_[searchKey].Size())
            {
                shadowMapAllocations_[searchKey].Push(light);
                return shadowMaps_[searchKey][allocated];
            }
            else if ((int)allocated >= maxShadowMaps_)
                return 0;
        }
    }
    
    unsigned shadowMapFormat = (shadowQuality_ & SHADOWQUALITY_LOW_24BIT) ? graphics_->GetHiresShadowMapFormat() :
        graphics_->GetShadowMapFormat();
    unsigned dummyColorFormat = graphics_->GetDummyColorFormat();
    if (!shadowMapFormat)
        return 0;
    
    SharedPtr<Texture2D> newShadowMap(new Texture2D(context_));
    int retries = 3;
    
    // OpenGL: create shadow map only. Color rendertarget is not needed
    #ifdef USE_OPENGL
    while (retries)
    {
        if (!newShadowMap->SetSize(width, height, shadowMapFormat, TEXTURE_DEPTHSTENCIL))
        {
            width >>= 1;
            height >>= 1;
            --retries;
        }
        else
        {
            #ifndef GL_ES_VERSION_2_0
            newShadowMap->SetFilterMode(FILTER_BILINEAR);
            newShadowMap->SetShadowCompare(true);
            #endif
            break;
        }
    }
    #else
    // Direct3D9: create shadow map and dummy color rendertarget
    while (retries)
    {
        if (!newShadowMap->SetSize(width, height, shadowMapFormat, TEXTURE_DEPTHSTENCIL))
        {
            width >>= 1;
            height >>= 1;
            --retries;
        }
        else
        {
            newShadowMap->SetFilterMode(FILTER_BILINEAR);
            // If no dummy color rendertarget for this size exists yet, create one now
            if (!colorShadowMaps_.Contains(searchKey))
            {
                colorShadowMaps_[searchKey] = new Texture2D(context_);
                colorShadowMaps_[searchKey]->SetSize(width, height, dummyColorFormat, TEXTURE_RENDERTARGET);
            }
            // Link the color rendertarget to the shadow map
            newShadowMap->GetRenderSurface()->SetLinkedRenderTarget(colorShadowMaps_[searchKey]->GetRenderSurface());
            break;
        }
    }
    #endif
    // If failed to set size, store a null pointer so that we will not retry
    if (!retries)
        newShadowMap.Reset();
    
    shadowMaps_[searchKey].Push(newShadowMap);
    if (!reuseShadowMaps_)
        shadowMapAllocations_[searchKey].Push(light);
    
    return newShadowMap;
}

Texture2D* Renderer::GetScreenBuffer(int width, int height, unsigned format, bool filtered)
{
    bool depthStencil = (format == Graphics::GetDepthStencilFormat());
    if (depthStencil)
        filtered = false;
    
    long long searchKey = ((long long)format << 32) | (width << 16) | height;
    if (filtered)
        searchKey |= 0x8000000000000000LL;
    
    // Return the default depth-stencil if applicable (Direct3D9 only)
    if (width <= graphics_->GetWidth() && height <= graphics_->GetHeight() && depthStencil)
    {
        Texture2D* depthTexture = graphics_->GetDepthTexture();
        if (depthTexture)
            return depthTexture;
    }
    
    // If new size or format, initialize the allocation stats
    if (screenBuffers_.Find(searchKey) == screenBuffers_.End())
        screenBufferAllocations_[searchKey] = 0;
    
    unsigned allocations = screenBufferAllocations_[searchKey]++;
    if (allocations >= screenBuffers_[searchKey].Size())
    {
        SharedPtr<Texture2D> newBuffer(new Texture2D(context_));
        newBuffer->SetSize(width, height, format, depthStencil ? TEXTURE_DEPTHSTENCIL : TEXTURE_RENDERTARGET);
        if (filtered)
            newBuffer->SetFilterMode(FILTER_BILINEAR);
        newBuffer->ResetUseTimer();
        screenBuffers_[searchKey].Push(newBuffer);
        LOGDEBUG("Allocated new screen buffer size " + String(width) + "x" + String(height) + " format " + String(format));
        return newBuffer;
    }
    else
    {
        Texture2D* buffer = screenBuffers_[searchKey][allocations];
        buffer->ResetUseTimer();
        return buffer;
    }
}

RenderSurface* Renderer::GetDepthStencil(int width, int height)
{
    // Return the default depth-stencil surface if applicable
    // (when using OpenGL Graphics will allocate right size surfaces on demand to emulate Direct3D9)
    if (width <= graphics_->GetWidth() && height <= graphics_->GetHeight() && graphics_->GetMultiSample() <= 1)
        return 0;
    else
        return GetScreenBuffer(width, height, Graphics::GetDepthStencilFormat())->GetRenderSurface();
}

OcclusionBuffer* Renderer::GetOcclusionBuffer(Camera* camera)
{
    if (numOcclusionBuffers_ >= occlusionBuffers_.Size())
    {
        SharedPtr<OcclusionBuffer> newBuffer(new OcclusionBuffer(context_));
        occlusionBuffers_.Push(newBuffer);
    }
    
    int width = occlusionBufferSize_;
    int height = (int)((float)occlusionBufferSize_ / camera->GetAspectRatio() + 0.5f);
    
    OcclusionBuffer* buffer = occlusionBuffers_[numOcclusionBuffers_];
    buffer->SetSize(width, height);
    buffer->SetView(camera);
    buffer->ResetUseTimer();
    
    ++numOcclusionBuffers_;
    return buffer;
}

Camera* Renderer::GetShadowCamera()
{
    MutexLock lock(rendererMutex_);
    
    if (numShadowCameras_ >= shadowCameraNodes_.Size())
    {
        SharedPtr<Node> newNode(new Node(context_));
        newNode->CreateComponent<Camera>();
        shadowCameraNodes_.Push(newNode);
    }
    
    Camera* camera = shadowCameraNodes_[numShadowCameras_]->GetComponent<Camera>();
    camera->SetOrthographic(false);
    camera->SetZoom(1.0f);
    
    ++numShadowCameras_;
    return camera;
}

ShaderVariation* Renderer::GetShader(ShaderType type, const String& name, bool checkExists) const
{
    String shaderName = shaderPath_;
    String variationName;
    
    unsigned split = name.Find('_');
    if (split != String::NPOS)
    {
        shaderName += name.Substring(0, split) + ".xml";
        variationName = name.Substring(split + 1);
    }
    else
        shaderName += name + ".xml";
    
    if (checkExists)
    {
        if (!cache_->Exists(shaderName))
            return 0;
    }
    
    Shader* shader = cache_->GetResource<Shader>(shaderName);
    if (shader)
        return shader->GetVariation(type, variationName);
    else
        return 0;
}

void Renderer::SetBatchShaders(Batch& batch, Technique* tech, bool allowShadows)
{
    // Check if shaders are unloaded or need reloading
    Vector<SharedPtr<ShaderVariation> >& vertexShaders = batch.pass_->GetVertexShaders();
    Vector<SharedPtr<ShaderVariation> >& pixelShaders = batch.pass_->GetPixelShaders();
    if (!vertexShaders.Size() || !pixelShaders.Size() || tech->GetShadersLoadedFrameNumber() !=
        shadersChangedFrameNumber_)
    {
        // First release all previous shaders, then load
        tech->ReleaseShaders();
        LoadMaterialShaders(tech);
    }
    
    // Make sure shaders are loaded now
    if (vertexShaders.Size() && pixelShaders.Size())
    {
        GeometryType geomType = batch.geometryType_;
        // If instancing is not supported, but was requested, or the object is too large to be instanced,
        // choose static geometry vertex shader instead
        if (geomType == GEOM_INSTANCED && (!GetDynamicInstancing() || batch.geometry_->GetIndexCount() >
            (unsigned)maxInstanceTriangles_ * 3))
            geomType = GEOM_STATIC;
        
        if (geomType == GEOM_STATIC_NOINSTANCING)
            geomType = GEOM_STATIC;
        
        //  Check whether is a pixel lit forward pass. If not, there is only one pixel shader
        PassType type = batch.pass_->GetType();
        if (type == PASS_LIGHT || type == PASS_LITBASE)
        {
            LightBatchQueue* lightQueue = batch.lightQueue_;
            if (!lightQueue)
            {
                // Do not log error, as it would result in a lot of spam
                batch.vertexShader_ = 0;
                batch.pixelShader_ = 0;
                return;
            }
            
            Light* light = lightQueue->light_;
            unsigned vsi = 0;
            unsigned psi = 0;
            vsi = geomType * MAX_LIGHT_VS_VARIATIONS;
            
            bool materialHasSpecular = batch.material_ ? batch.material_->GetSpecular() : true;
            if (specularLighting_ && light->GetSpecularIntensity() > 0.0f && materialHasSpecular)
            {
                vsi += LVS_SPEC;
                psi += LPS_SPEC;
            }
            if (allowShadows && lightQueue->shadowMap_)
            {
                vsi += LVS_SHADOW;
                psi += LPS_SHADOW;
            }
            
            switch (light->GetLightType())
            {
            case LIGHT_DIRECTIONAL:
                vsi += LVS_DIR;
                break;
                
            case LIGHT_POINT:
                if (light->GetShapeTexture())
                    psi += LPS_POINTMASK;
                else
                    psi += LPS_POINT;
                vsi += LVS_POINT;
                break;
                
            case LIGHT_SPOT:
                psi += LPS_SPOT;
                vsi += LVS_SPOT;
                break;
            }
            
            batch.vertexShader_ = vertexShaders[vsi];
            batch.pixelShader_ = pixelShaders[psi];
            
            // If shadow or specular variations do not exist, try without them
            if ((!batch.vertexShader_ || !batch.pixelShader_) && (vsi >= LVS_SHADOW))
            {
                vsi -= LVS_SHADOW;
                psi -= LPS_SHADOW;
                batch.vertexShader_ = vertexShaders[vsi];
                batch.pixelShader_ = pixelShaders[psi];
            }
            if ((!batch.vertexShader_ || !batch.pixelShader_) && (vsi >= LVS_SPEC))
            {
                vsi -= LVS_SPEC;
                psi -= LPS_SPEC;
                batch.vertexShader_ = vertexShaders[vsi];
                batch.pixelShader_ = pixelShaders[psi];
            }
        }
        else
        {
            // Check if pass has vertex lighting support
            if (type == PASS_BASE || type == PASS_MATERIAL || type == PASS_DEFERRED)
            {
                unsigned numVertexLights = 0;
                if (batch.lightQueue_)
                    numVertexLights = batch.lightQueue_->vertexLights_.Size();
                
                unsigned vsi = geomType * MAX_VERTEXLIGHT_VS_VARIATIONS + numVertexLights;
                batch.vertexShader_ = vertexShaders[vsi];
                // If vertex lights variations do not exist, try without them
                if (!batch.vertexShader_)
                {
                    unsigned vsi = geomType * MAX_VERTEXLIGHT_VS_VARIATIONS;
                    batch.vertexShader_ = vertexShaders[vsi];
                }
            }
            else
            {
                unsigned vsi = geomType;
                batch.vertexShader_ = vertexShaders[vsi];
            }
            
            batch.pixelShader_ = pixelShaders[0];
        }
    }
    
    // Log error if shaders could not be assigned, but only once per technique
    if (!batch.vertexShader_ || !batch.pixelShader_)
    {
        if (!shaderErrorDisplayed_.Contains(tech))
        {
            shaderErrorDisplayed_.Insert(tech);
            LOGERROR("Technique " + tech->GetName() + " has missing shaders");
        }
    }
}

void Renderer::SetLightVolumeBatchShaders(Batch& batch)
{
    unsigned vsi = DLVS_NONE;
    unsigned psi = DLPS_NONE;
    Light* light = batch.lightQueue_->light_;
    
    switch (light->GetLightType())
    {
    case LIGHT_DIRECTIONAL:
        vsi += DLVS_DIR;
        break;
        
    case LIGHT_POINT:
        if (light->GetShapeTexture())
            psi += DLPS_POINTMASK;
        else
            psi += DLPS_POINT;
        break;
        
    case LIGHT_SPOT:
        psi += DLPS_SPOT;
        break;
    }
    
    if (batch.lightQueue_->shadowMap_)
        psi += DLPS_SHADOW;
    
    if (specularLighting_ && light->GetSpecularIntensity() > 0.0f)
        psi += DLPS_SPEC;
    
    if (batch.camera_->IsOrthographic())
    {
        vsi += DLVS_ORTHO;
        psi += DLPS_ORTHO;
    }
    
    batch.vertexShader_ = lightVS_[vsi];
    batch.pixelShader_ = lightPS_[psi];
}

void Renderer::SetCullMode(CullMode mode, Camera* camera)
{
    // If a camera is specified, check for vertical flipping and reverse culling in that case
    if (camera && camera->GetFlipVertical())
    {
        if (mode == CULL_CW)
            mode = CULL_CCW;
        else if (mode == CULL_CCW)
            mode = CULL_CW;
    }
    
    graphics_->SetCullMode(mode);
}

bool Renderer::ResizeInstancingBuffer(unsigned numInstances)
{
    if (!instancingBuffer_ || !dynamicInstancing_)
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

void Renderer::SaveScreenBufferAllocations()
{
    savedScreenBufferAllocations_ = screenBufferAllocations_;
}

void Renderer::RestoreScreenBufferAllocations()
{
    screenBufferAllocations_ = savedScreenBufferAllocations_;
}


void Renderer::OptimizeLightByScissor(Light* light, Camera* camera)
{
    if (light && light->GetLightType() != LIGHT_DIRECTIONAL)
        graphics_->SetScissorTest(true, GetLightScissor(light, camera));
    else
        graphics_->SetScissorTest(false);
}

void Renderer::OptimizeLightByStencil(Light* light, Camera* camera)
{
    #ifndef GL_ES_VERSION_2_0
    if (light)
    {
        LightType type = light->GetLightType();
        if (type == LIGHT_DIRECTIONAL)
        {
            graphics_->SetStencilTest(false);
            return;
        }
        
        Geometry* geometry = GetLightGeometry(light);
        const Matrix3x4& view = camera->GetInverseWorldTransform();
        const Matrix4& projection = camera->GetProjection();
        Vector3 cameraPos = camera->GetNode()->GetWorldPosition();
        float lightDist;
        
        if (type == LIGHT_POINT)
            lightDist = Sphere(light->GetNode()->GetWorldPosition(), light->GetRange() * 1.25f).Distance(cameraPos);
        else
            lightDist = light->GetFrustum().Distance(cameraPos);
        
        // If the camera is actually inside the light volume, do not draw to stencil as it would waste fillrate
        if (lightDist < M_EPSILON)
        {
            graphics_->SetStencilTest(false);
            return;
        }
        
        // If the stencil value has wrapped, clear the whole stencil first
        if (!lightStencilValue_)
        {
            graphics_->Clear(CLEAR_STENCIL);
            lightStencilValue_ = 1;
        }
        
        // If possible, render the stencil volume front faces. However, close to the near clip plane render back faces instead
        // to avoid clipping.
        if (lightDist < camera->GetNearClip() * 2.0f)
        {
            SetCullMode(CULL_CW, camera);
            graphics_->SetDepthTest(CMP_GREATER);
        }
        else
        {
            SetCullMode(CULL_CCW, camera);
            graphics_->SetDepthTest(CMP_LESSEQUAL);
        }
        
        graphics_->SetColorWrite(false);
        graphics_->SetDepthWrite(false);
        graphics_->SetStencilTest(true, CMP_ALWAYS, OP_REF, OP_KEEP, OP_KEEP, lightStencilValue_);
        graphics_->SetShaders(stencilVS_, stencilPS_);
        graphics_->SetShaderParameter(VSP_VIEWPROJ, projection * view);
        graphics_->SetShaderParameter(VSP_MODEL, light->GetVolumeTransform(camera));
        
        geometry->Draw(graphics_);
        
        graphics_->ClearTransformSources();
        graphics_->SetColorWrite(true);
        graphics_->SetStencilTest(true, CMP_EQUAL, OP_KEEP, OP_KEEP, OP_KEEP, lightStencilValue_);
        
        // Increase stencil value for next light
        ++lightStencilValue_;
    }
    else
        graphics_->SetStencilTest(false);
    #endif
}

const Rect& Renderer::GetLightScissor(Light* light, Camera* camera)
{
    Pair<Light*, Camera*> combination(light, camera);
    
    HashMap<Pair<Light*, Camera*>, Rect>::Iterator i = lightScissorCache_.Find(combination);
    if (i != lightScissorCache_.End())
        return i->second_;
    
    const Matrix3x4& view = camera->GetInverseWorldTransform();
    const Matrix4& projection = camera->GetProjection();
    
    switch (light->GetLightType())
    {
    case LIGHT_POINT:
        {
            BoundingBox viewBox(light->GetWorldBoundingBox().Transformed(view));
            return lightScissorCache_[combination] = viewBox.Projected(projection);
        }
        
    case LIGHT_SPOT:
        {
            Frustum viewFrustum(light->GetFrustum().Transformed(view));
            return lightScissorCache_[combination] = viewFrustum.Projected(projection);
        }
        
    default:
        return lightScissorCache_[combination] = Rect::FULL;
    }
}

void Renderer::PrepareViewRender()
{
    ResetScreenBufferAllocations();
    lightScissorCache_.Clear();
    lightStencilValue_ = 1;
}

void Renderer::RemoveUnusedBuffers()
{
    for (unsigned i = occlusionBuffers_.Size() - 1; i < occlusionBuffers_.Size(); --i)
    {
        if (occlusionBuffers_[i]->GetUseTimer() > MAX_BUFFER_AGE)
        {
            LOGDEBUG("Removed unused occlusion buffer");
            occlusionBuffers_.Erase(i);
        }
    }
    
    for (HashMap<long long, Vector<SharedPtr<Texture2D> > >::Iterator i = screenBuffers_.Begin(); i != screenBuffers_.End();)
    {
        HashMap<long long, Vector<SharedPtr<Texture2D> > >::Iterator current = i++;
        Vector<SharedPtr<Texture2D> >& buffers = current->second_;
        for (unsigned j = buffers.Size() - 1; j < buffers.Size(); --j)
        {
            Texture2D* buffer = buffers[j];
            if (buffer->GetUseTimer() > MAX_BUFFER_AGE)
            {
                LOGDEBUG("Removed unused screen buffer size " + String(buffer->GetWidth()) + "x" + String(buffer->GetHeight()) + " format " + String(buffer->GetFormat()));
                buffers.Erase(j);
            }
        }
        if (buffers.Empty())
        {
            screenBufferAllocations_.Erase(current->first_);
            screenBuffers_.Erase(current);
        }
    }
}

void Renderer::ResetShadowMapAllocations()
{
    for (HashMap<int, PODVector<Light*> >::Iterator i = shadowMapAllocations_.Begin(); i != shadowMapAllocations_.End(); ++i)
        i->second_.Clear();
}

void Renderer::ResetScreenBufferAllocations()
{
    for (HashMap<long long, unsigned>::Iterator i = screenBufferAllocations_.Begin(); i != screenBufferAllocations_.End(); ++i)
        i->second_ = 0;
}

void Renderer::Initialize()
{
    Graphics* graphics = GetSubsystem<Graphics>();
    ResourceCache* cache = GetSubsystem<ResourceCache>();
    
    if (!graphics || !graphics->IsInitialized() || !cache)
        return;
    
    PROFILE(InitRenderer);
    
    graphics_ = graphics;
    cache_ = cache;
    
    #ifndef USE_OPENGL
    shaderPath_ = "Shaders/HLSL/";
    #else
    shaderPath_ = "Shaders/GLSL/";
    #endif
    
    if (!graphics_->GetShadowMapFormat())
        drawShadows_ = false;
    
    defaultLightRamp_ = cache->GetResource<Texture2D>("Textures/Ramp.png");
    defaultLightSpot_ = cache->GetResource<Texture2D>("Textures/Spot.png");
    defaultMaterial_ = cache->GetResource<Material>("Materials/Default.xml");
    
    // If default material not found, create one. This will actually not render properly, but prevents crashing
    if (!defaultMaterial_)
        defaultMaterial_ = new Material(context_);
    
    CreateGeometries();
    CreateInstancingBuffer();
    
    viewports_.Resize(1);
    ResetViews();
    ResetShadowMaps();
    ResetBuffers();
    
    shadersDirty_ = true;
    initialized_ = true;
    
    LOGINFO("Initialized renderer");
}

void Renderer::ResetViews()
{
    views_.Clear();
    numViews_ = 0;
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
    
    if (renderMode_ != RENDER_FORWARD)
    {
        lightVS_.Resize(MAX_DEFERRED_LIGHT_VS_VARIATIONS);
        lightPS_.Resize(MAX_DEFERRED_LIGHT_PS_VARIATIONS);
        
        unsigned shadows = (graphics_->GetHardwareShadowSupport() ? 1 : 0) | (shadowQuality_ & SHADOWQUALITY_HIGH_16BIT);
        String shaderName = renderMode_ == RENDER_PREPASS ? "PrepassLight_" : "DeferredLight_";
        
        for (unsigned i = 0; i < MAX_DEFERRED_LIGHT_VS_VARIATIONS; ++i)
            lightVS_[i] = GetVertexShader(shaderName + deferredLightVSVariations[i]);
        
        for (unsigned i = 0; i < lightPS_.Size(); ++i)
        {
            String ortho, hwDepth;
            #ifdef USE_OPENGL
            hwDepth = hwVariations[graphics_->GetHardwareDepthSupport() ? 1 : 0];
            #else
            if (!graphics_->GetHardwareDepthSupport() && i < DLPS_ORTHO)
                ortho = "Linear";
            #endif
            if (i >= DLPS_ORTHO)
                ortho = "Ortho";
            
            if (i & DLPS_SHADOW)
            {
                lightPS_[i] = GetPixelShader(shaderName + ortho + lightPSVariations[i % DLPS_ORTHO] +
                    shadowVariations[shadows] + hwDepth);
            }
            else
                lightPS_[i] = GetPixelShader(shaderName + ortho + lightPSVariations[i % DLPS_ORTHO] + hwDepth);
        }
    }
    
    shadersDirty_ = false;
}

void Renderer::LoadMaterialShaders(Technique* tech)
{
    if (renderMode_ == RENDER_PREPASS && tech->HasPass(PASS_PREPASS))
    {
        LoadPassShaders(tech, PASS_PREPASS);
        LoadPassShaders(tech, PASS_MATERIAL);
    }
    else if (renderMode_ == RENDER_DEFERRED && tech->HasPass(PASS_DEFERRED))
        LoadPassShaders(tech, PASS_DEFERRED);
    else
    {
        LoadPassShaders(tech, PASS_BASE);
        LoadPassShaders(tech, PASS_LITBASE);
        LoadPassShaders(tech, PASS_LIGHT);
    }
    
    LoadPassShaders(tech, PASS_PREALPHA);
    LoadPassShaders(tech, PASS_POSTALPHA);
    LoadPassShaders(tech, PASS_SHADOW);
}

void Renderer::LoadPassShaders(Technique* tech, PassType type, bool allowShadows)
{
    Pass* pass = tech->GetPass(type);
    if (!pass)
        return;
    
    unsigned shadows = (graphics_->GetHardwareShadowSupport() ? 1 : 0) | (shadowQuality_ & SHADOWQUALITY_HIGH_16BIT);
    
    String vertexShaderName = pass->GetVertexShader();
    String pixelShaderName = pass->GetPixelShader();
    
    // Check if the shader name is already a variation in itself
    if (vertexShaderName.Find('_') == String::NPOS)
        vertexShaderName += "_";
    if (pixelShaderName.Find('_') == String::NPOS)
        pixelShaderName += "_";
    
    // If hardware depth is used, choose a G-buffer shader that does not write depth manually
    if (type == PASS_PREPASS || type == PASS_DEFERRED)
    {
        unsigned hwDepth = graphics_->GetHardwareDepthSupport() ? 1 : 0;
        pixelShaderName += hwVariations[hwDepth];
    }
    
    Vector<SharedPtr<ShaderVariation> >& vertexShaders = pass->GetVertexShaders();
    Vector<SharedPtr<ShaderVariation> >& pixelShaders = pass->GetPixelShaders();
    
    // Forget all the old shaders
    vertexShaders.Clear();
    pixelShaders.Clear();
    
    if (type == PASS_LIGHT || type == PASS_LITBASE)
    {
        // Load forward pixel lit variations. If material is transparent, and shadow maps are reused,
        // do not load shadowed variations
        if (reuseShadowMaps_)
        {
            if (!tech->HasPass(PASS_BASE) || tech->GetPass(PASS_BASE)->GetBlendMode() != BLEND_REPLACE)
                allowShadows = false;
        }
        
        vertexShaders.Resize(MAX_GEOMETRYTYPES * MAX_LIGHT_VS_VARIATIONS);
        pixelShaders.Resize(MAX_LIGHT_PS_VARIATIONS);
        
        for (unsigned j = 0; j < MAX_GEOMETRYTYPES * MAX_LIGHT_VS_VARIATIONS; ++j)
        {
            unsigned g = j / MAX_LIGHT_VS_VARIATIONS;
            unsigned l = j % MAX_LIGHT_VS_VARIATIONS;
            if (l < LVS_SHADOW || allowShadows)
                vertexShaders[j] = GetVertexShader(vertexShaderName + lightVSVariations[l] + geometryVSVariations[g], g != 0);
            else
                vertexShaders[j].Reset();
        }
        for (unsigned j = 0; j < MAX_LIGHT_PS_VARIATIONS; ++j)
        {
            if (j & LPS_SHADOW)
            {
                if (allowShadows)
                    pixelShaders[j] = GetPixelShader(pixelShaderName + lightPSVariations[j] + shadowVariations[shadows]);
                else
                    pixelShaders[j].Reset();
            }
            else
                pixelShaders[j] = GetPixelShader(pixelShaderName + lightPSVariations[j]);
        }
    }
    else
    {
        // Load vertex light variations for forward ambient pass, deferred G-buffer pass and pre-pass material pass
        if (type == PASS_BASE || type == PASS_MATERIAL || type == PASS_DEFERRED)
        {
            vertexShaders.Resize(MAX_VERTEXLIGHT_VS_VARIATIONS * MAX_GEOMETRYTYPES);
            for (unsigned j = 0; j < MAX_GEOMETRYTYPES * MAX_VERTEXLIGHT_VS_VARIATIONS; ++j)
            {
                unsigned g = j / MAX_VERTEXLIGHT_VS_VARIATIONS;
                unsigned l = j % MAX_VERTEXLIGHT_VS_VARIATIONS;
                vertexShaders[j] = GetVertexShader(vertexShaderName + vertexLightVSVariations[l] + geometryVSVariations[g],
                    g != 0 || l != 0);
            }
        }
        else
        {
            vertexShaders.Resize(MAX_GEOMETRYTYPES);
            for (unsigned j = 0; j < MAX_GEOMETRYTYPES; ++j)
                vertexShaders[j] = GetVertexShader(vertexShaderName + geometryVSVariations[j], j != 0);
        }
        
        pixelShaders.Resize(1);
        pixelShaders[0] = GetPixelShader(pixelShaderName);
    }
    
    tech->MarkShadersLoaded(shadersChangedFrameNumber_);
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
    dlvb->SetShadowed(true);
    dlvb->SetSize(4, MASK_POSITION);
    dlvb->SetData(dirLightVertexData);
    
    SharedPtr<IndexBuffer> dlib(new IndexBuffer(context_));
    dlib->SetShadowed(true);
    dlib->SetSize(6, false);
    dlib->SetData(dirLightIndexData);
    
    dirLightGeometry_ = new Geometry(context_);
    dirLightGeometry_->SetVertexBuffer(0, dlvb);
    dirLightGeometry_->SetIndexBuffer(dlib);
    dirLightGeometry_->SetDrawRange(TRIANGLE_LIST, 0, dlib->GetIndexCount());
    
    SharedPtr<VertexBuffer> slvb(new VertexBuffer(context_));
    slvb->SetShadowed(true);
    slvb->SetSize(8, MASK_POSITION);
    slvb->SetData(spotLightVertexData);
    
    SharedPtr<IndexBuffer> slib(new IndexBuffer(context_));
    slib->SetShadowed(true);
    slib->SetSize(36, false);
    slib->SetData(spotLightIndexData);
    
    spotLightGeometry_ = new Geometry(context_);
    spotLightGeometry_->SetVertexBuffer(0, slvb);
    spotLightGeometry_->SetIndexBuffer(slib);
    spotLightGeometry_->SetDrawRange(TRIANGLE_LIST, 0, slib->GetIndexCount());
    
    SharedPtr<VertexBuffer> plvb(new VertexBuffer(context_));
    plvb->SetShadowed(true);
    plvb->SetSize(24, MASK_POSITION);
    plvb->SetData(pointLightVertexData);
    
    SharedPtr<IndexBuffer> plib(new IndexBuffer(context_));
    plib->SetShadowed(true);
    plib->SetSize(132, false);
    plib->SetData(pointLightIndexData);
    
    pointLightGeometry_ = new Geometry(context_);
    pointLightGeometry_->SetVertexBuffer(0, plvb);
    pointLightGeometry_->SetIndexBuffer(plib);
    pointLightGeometry_->SetDrawRange(TRIANGLE_LIST, 0, plib->GetIndexCount());
    
    #if !defined(USE_OPENGL) || !defined(GL_ES_VERSION_2_0)
    if (graphics_->GetShadowMapFormat())
    {
        faceSelectCubeMap_ = new TextureCube(context_);
        faceSelectCubeMap_->SetNumLevels(1);
        faceSelectCubeMap_->SetSize(1, graphics_->GetRGBAFormat());
        faceSelectCubeMap_->SetFilterMode(FILTER_NEAREST);
        
        indirectionCubeMap_ = new TextureCube(context_);
        indirectionCubeMap_->SetNumLevels(1);
        indirectionCubeMap_->SetSize(256, graphics_->GetRGBAFormat());
        indirectionCubeMap_->SetFilterMode(FILTER_BILINEAR);
        indirectionCubeMap_->SetAddressMode(COORD_U, ADDRESS_CLAMP);
        indirectionCubeMap_->SetAddressMode(COORD_V, ADDRESS_CLAMP);
        indirectionCubeMap_->SetAddressMode(COORD_W, ADDRESS_CLAMP);
        
        SetIndirectionTextureData();
    }
    #endif
}

void Renderer::SetIndirectionTextureData()
{
    unsigned char data[256 * 256 * 4];
    
    for (unsigned i = 0; i < MAX_CUBEMAP_FACES; ++i)
    {
        unsigned axis = i / 2;
        data[0] = (axis == 0) ? 255 : 0;
        data[1] = (axis == 1) ? 255 : 0;
        data[2] = (axis == 2) ? 255 : 0;
        data[3] = 0;
        faceSelectCubeMap_->SetData((CubeMapFace)i, 0, 0, 0, 1, 1, data);
    }
    
    for (unsigned i = 0; i < MAX_CUBEMAP_FACES; ++i)
    {
        unsigned char faceX = (i & 1) * 255;
        unsigned char faceY = (i / 2) * 255 / 3;
        unsigned char* dest = data;
        for (unsigned y = 0; y < 256; ++y)
        {
            for (unsigned x = 0; x < 256; ++x)
            {
                #ifdef USE_OPENGL
                *dest++ = x;
                *dest++ = 255 - y;
                *dest++ = faceX;
                *dest++ = 255 * 2 / 3 - faceY;
                #else
                *dest++ = x;
                *dest++ = y;
                *dest++ = faceX;
                *dest++ = faceY;
                #endif
            }
        }
        
        indirectionCubeMap_->SetData((CubeMapFace)i, 0, 0, 0, 256, 256, data);
    }
    
    faceSelectCubeMap_->ClearDataLost();
    indirectionCubeMap_->ClearDataLost();
}

void Renderer::CreateInstancingBuffer()
{
    // Do not create buffer if instancing not supported
    if (!graphics_->GetSM3Support())
    {
        instancingBuffer_.Reset();
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

void Renderer::ResetShadowMaps()
{
    shadowMaps_.Clear();
    shadowMapAllocations_.Clear();
    colorShadowMaps_.Clear();
}

void Renderer::ResetBuffers()
{
    occlusionBuffers_.Clear();
    screenBuffers_.Clear();
    screenBufferAllocations_.Clear();
}

void Renderer::HandleScreenMode(StringHash eventType, VariantMap& eventData)
{
    if (!initialized_)
        Initialize();
    else
    {
        // When screen mode changes, purge old views
        ResetViews();
    }
}

void Renderer::HandleGraphicsFeatures(StringHash eventType, VariantMap& eventData)
{
    // Reinitialize if already initialized
    if (initialized_)
        Initialize();
}

void Renderer::HandleRenderUpdate(StringHash eventType, VariantMap& eventData)
{
    if (initialized_)
    {
        using namespace RenderUpdate;
        
        Update(eventData[P_TIMESTEP].GetFloat());
    }
}

}
