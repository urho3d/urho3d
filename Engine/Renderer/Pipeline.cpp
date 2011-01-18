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
#include "DebugRenderer.h"
#include "Geometry.h"
#include "IndexBuffer.h"
#include "InstancedModel.h"
#include "Light.h"
#include "Log.h"
#include "Material.h"
#include "OcclusionBuffer.h"
#include "Octree.h"
#include "OctreeQuery.h"
#include "Pipeline.h"
#include "PixelShader.h"
#include "Profiler.h"
#include "Renderer.h"
#include "RendererEvents.h"
#include "RendererImpl.h"
#include "ResourceCache.h"
#include "StringUtils.h"
#include "Texture2D.h"
#include "TextureCube.h"
#include "VertexBuffer.h"
#include "VertexShader.h"
#include "View.h"
#include "XMLFile.h"

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

static const std::string geometryVSVariations[] =
{
    "",
    "Skinned",
    "Instanced"
};

static const std::string gBufferPSVariations[] =
{
    "",
    "HW"
};

static const std::string lightVSVariations[] =
{
    "",
    "Spot",
    "Shadow",
    "SpotShadow"
};

static const std::string deferredLightVSVariations[] =
{
    "",
    "Dir",
    "Ortho",
    "OrthoDir"
};

static const std::string deferredLightPSVariations[] = 
{
    "Dir",
    "DirSpec",
    "DirShadow",
    "DirShadowSpec",
    "DirNegative",
    "Point",
    "PointSpec",
    "PointShadow",
    "PointShadowSpec",
    "PointNegative",
    "Spot",
    "SpotSpec",
    "SpotShadow",
    "SpotShadowSpec",
    "SpotNegative",
    "OrthoDir",
    "OrthoDirSpec",
    "OrthoDirShadow",
    "OrthoDirShadowSpec",
    "OrthoDirNegative",
    "OrthoPoint",
    "OrthoPointSpec",
    "OrthoPointShadow",
    "OrthoPointShadowSpec",
    "OrthoPointNegative",
    "OrthoSpot",
    "OrthoSpotSpec",
    "OrthoSpotShadow",
    "OrthoSpotShadowSpec",
    "OrthoSpotNegative",
    "LinearDir",
    "LinearDirSpec",
    "LinearDirShadow",
    "LinearDirShadowSpec",
    "LinearDirNegative",
    "LinearPoint",
    "LinearPointSpec",
    "LinearPointShadow",
    "LinearPointShadowSpec",
    "LinearPointNegative",
    "LinearSpot",
    "LinearSpotSpec",
    "LinearSpotShadow",
    "LinearSpotShadowSpec",
    "LinearSpotNegative"
};

static const std::string shadowPSVariations[] =
{
    "",
    "HW"
};

void EdgeFilterParameters::validate()
{
    mThreshold = max(mThreshold, 0.0f);
    mFilterStep = clamp(mFilterStep, 0.0f, 1.0f);
    mMaxFilter = clamp(mMaxFilter, 0.0f, 1.0f);
    mMaxScale = max(mMaxScale, 0.0f);
}

Pipeline::Pipeline(Renderer* renderer, ResourceCache* cache) :
    mRenderer(renderer),
    mCache(cache),
    mFrameNumber(M_MAX_UNSIGNED),
    mNumViews(0),
    mNumSplitLights(0),
    mElapsedTime(0.0f),
    mSpecularLighting(true),
    mDrawShadows(true),
    mTextureAnisotropy(4),
    mTextureFilterMode(FILTER_TRILINEAR),
    mTextureQuality(QUALITY_HIGH),
    mMaterialQuality(QUALITY_HIGH),
    mLightDetailLevel(QUALITY_HIGH),
    mShadowMapSize(1024),
    mShadowMapHiresDepth(false),
    mMaxOccluderTriangles(5000),
    mOcclusionBufferSize(256),
    mOccluderSizeThreshold(0.1f),
    mEdgeFilter(EdgeFilterParameters(0.25f, 0.25f, 0.50f, 10.0f)),
    mShadersChangedFrameNumber(M_MAX_UNSIGNED),
    mShadersDirty(true)
{
    if (!mRenderer)
        EXCEPTION("Null renderer for Pipeline");
    
    LOGINFO("Rendering pipeline created");
    
    subscribeToEvent(EVENT_WINDOWRESIZED, EVENT_HANDLER(Pipeline, handleWindowResized));
    
    // Check shader model support
    if (mRenderer->getSM3Support())
    {
        mShaderPath = "Shaders/SM3/";
        mVSFormat = ".vs3";
        mPSFormat = ".ps3";
        InstancedModel::setInstancingMode(HARDWARE_INSTANCING);
    }
    else
    {
        mShaderPath = "Shaders/SM2/";
        mVSFormat = ".vs2";
        mPSFormat = ".ps2";
        InstancedModel::setInstancingMode(SHADER_INSTANCING);
    }
    
    mDefaultLightRamp = mCache->getResource<Texture2D>("Textures/Ramp.png");
    mDefaultLightSpot = mCache->getResource<Texture2D>("Textures/Spot.png");
    mDefaultMaterial = mCache->getResource<Material>("Materials/Default.xml");
    
    createGeometries();
    
    if (!createShadowMaps())
        mDrawShadows = false;
    
    resetViews();
}

Pipeline::~Pipeline()
{
    LOGINFO("Rendering pipeline shut down");
}

void Pipeline::setSpecularLighting(bool enable)
{
    mSpecularLighting = enable;
}

void Pipeline::setDrawShadows(bool enable)
{
    mDrawShadows = enable;
    
    if (!createShadowMaps())
        mDrawShadows = false;
}

void Pipeline::setTextureAnisotropy(int level)
{
    mTextureAnisotropy = max(level, 1);
}

void Pipeline::setTextureFilterMode(TextureFilterMode mode)
{
    mTextureFilterMode = mode;
}

void Pipeline::setTextureQuality(int quality)
{
    quality = clamp(quality, QUALITY_LOW, QUALITY_HIGH);
    
    if (quality != mTextureQuality)
    {
        mTextureQuality = quality;
        Texture::setQuality(mTextureQuality);
        reloadTextures();
    }
}

void Pipeline::setMaterialQuality(int quality)
{
    mMaterialQuality = clamp(quality, QUALITY_LOW, QUALITY_MAX);
    mShadersDirty = true;
    resetViews();
}

void Pipeline::setLightDetailLevel(int detailLevel)
{
    mLightDetailLevel = clamp(detailLevel, QUALITY_LOW, QUALITY_MAX);
}

void Pipeline::setShadowMapSize(int size)
{
    mShadowMapSize = max(size, SHADOW_MIN_PIXELS);
    
    if (!createShadowMaps())
    {
        mShadowMapSize = 1024;
        if (!createShadowMaps())
            mDrawShadows = false;
    }
}

void Pipeline::setShadowMapHiresDepth(bool enable)
{
    if (!mRenderer->getHiresShadowSupport())
        enable = false;
    
    mShadowMapHiresDepth = enable;
    if (!createShadowMaps())
        mDrawShadows = false;
}

void Pipeline::setMaxOccluderTriangles(int triangles)
{
    mMaxOccluderTriangles = max(triangles, 0);
}

void Pipeline::setOcclusionBufferSize(int size)
{
    mOcclusionBufferSize = max(size, 1);
    mOcclusionBuffers.clear();
}

void Pipeline::setOccluderSizeThreshold(float screenSize)
{
    mOccluderSizeThreshold = max(screenSize, 0.0f);
}

void Pipeline::setEdgeFilter(const EdgeFilterParameters& parameters)
{
    mEdgeFilter = parameters;
}

bool Pipeline::update(float timeStep, Octree* octree, Camera* camera)
{
    PROFILE(Pipeline_Update);
    
    // If device lost, do not perform update. This is because any dynamic vertex/index buffer updates happen already here,
    // and if the device is lost, the updates queue up, causing memory use to rise constantly
    if ((mRenderer->isDeviceLost()) || (!camera) || (!octree))
    {
        mNumViews = 0;
        return false;
    }
    
    // Advance frame number & time, set up the frameinfo structure, and reset stats
    beginFrame(timeStep);
    
    // Reload shaders if needed
    if (mShadersDirty)
        loadShaders();
    
    // Update octree. Perform early update for nodes which need that, and reinsert moved nodes
    mFrame.mCamera = camera;
    octree->updateOctree(mFrame);
    
    // Add the main view
    addView(octree, camera, 0);
    
    // Get light and geometry nodes for the main view
    mViews[0]->update(mFrame);
    
    // Process any auxiliary views that were found during the main view processing
    for (unsigned i = 1; i < mNumViews; ++i)
        mViews[i]->update(mFrame);
    
    return true;
}

bool Pipeline::render()
{
    PROFILE(Pipeline_Render);
    
    mRenderer->setDefaultTextureFilterMode(mTextureFilterMode);
    mRenderer->setTextureAnisotropy(mTextureAnisotropy);
    
    // If no views, just clear the screen
    if (!mNumViews)
    {
        mRenderer->setAlphaTest(false);
        mRenderer->setBlendMode(BLEND_REPLACE);
        mRenderer->setColorWrite(true);
        mRenderer->setDepthWrite(true);
        mRenderer->setFillMode(FILL_SOLID);
        mRenderer->setScissorTest(false);
        mRenderer->setStencilTest(false);
        mRenderer->clear(CLEAR_COLOR | CLEAR_DEPTH | CLEAR_STENCIL);
        return false;
    }
    
    // Render views from last to first (main view is rendered last)
    for (unsigned i = mNumViews - 1; i < mNumViews; --i)
        mViews[i]->render();
    
    // Disable scissor/stencil tests if left on by lights, and reset stream frequencies
    mRenderer->setScissorTest(false);
    mRenderer->setStencilTest(false);
    mRenderer->resetStreamFrequencies();
    
    return true;
}

void Pipeline::drawDebugGeometry(DebugRenderer* debug)
{
    PROFILE(Pipeline_DrawDebugGeometry);
    
    if (!mNumViews)
        return;
    
    // Only use the main view
    const std::vector<GeometryNode*>& geometries = mViews[0]->getGeometries();
    const std::vector<Light*>& lights = mViews[0]->getLights();
    
    for (unsigned i = 0; i < geometries.size(); ++i)
        geometries[i]->drawDebugGeometry(debug);
    
    for (unsigned i = 0; i < lights.size(); ++i)
        lights[i]->drawDebugGeometry(debug);
}

VertexShader* Pipeline::getVertexShader(const std::string& name, bool checkExists) const
{
    // Check for extra underscore with no variations and remove
    std::string fullName = replace(mShaderPath + name + mVSFormat, "_.", ".");
    if (checkExists)
    {
        if (!mCache->exists(fullName))
            return 0;
    }
    return mCache->getResource<VertexShader>(fullName);
}

PixelShader* Pipeline::getPixelShader(const std::string& name, bool checkExists) const
{
    // Check for extra underscore with no variations and remove
    std::string fullName = replace(mShaderPath + name + mPSFormat, "_.", ".");
    if (checkExists)
    {
        if (!mCache->exists(fullName))
            return 0;
    }
    return mCache->getResource<PixelShader>(fullName);
}

unsigned Pipeline::getNumGeometries(bool allViews) const
{
    unsigned numGeometries = 0;
    unsigned lastView = allViews ? mNumViews : 1;
    
    for (unsigned i = 0; i < lastView; ++i)
        numGeometries += mViews[i]->getGeometries().size();
    
    return numGeometries;
}

unsigned Pipeline::getNumLights(bool allViews) const
{
    unsigned numLights = 0;
    unsigned lastView = allViews ? mNumViews : 1;
    
    for (unsigned i = 0; i < lastView; ++i)
        numLights += mViews[i]->getLights().size();
    
    return numLights;
}

unsigned Pipeline::getNumShadowMaps(bool allViews) const
{
    unsigned numShadowMaps = 0;
    unsigned lastView = allViews ? mNumViews : 1;
    
    for (unsigned i = 0; i < lastView; ++i)
    {
        const std::vector<LightBatchQueue>& lightQueues = mViews[i]->getLightQueues();
        
        for (unsigned j = 0; j < lightQueues.size(); ++j)
        {
            Light* light = lightQueues[j].mLight;
            if ((light) && (light->getShadowMap()))
                ++numShadowMaps;
        }
    }
    
    return numShadowMaps;
}

unsigned Pipeline::getNumOccluders(bool allViews) const
{
    unsigned numOccluders = 0;
    unsigned lastView = allViews ? mNumViews : 1;
    
    for (unsigned i = 0; i < lastView; ++i)
        numOccluders += mViews[i]->getOccluders().size();
    
    return numOccluders;
}

unsigned Pipeline::getNumShadowOccluders(bool allViews) const
{
    unsigned numShadowOccluders = 0;
    unsigned lastView = allViews ? mNumViews : 1;
    
    for (unsigned i = 0; i < lastView; ++i)
        numShadowOccluders += mViews[i]->getShadowOccluders().size();
    
    return numShadowOccluders;
}

const OcclusionBuffer* Pipeline::getOcclusionBuffer(float aspectRatio, bool halfResolution)
{
    // Return an occlusion buffer for debug output purposes. Do not allocate new
    int width = mOcclusionBufferSize;
    int height = (int)(mOcclusionBufferSize / aspectRatio);
    if (halfResolution)
    {
        width >>= 1;
        height >>= 1;
    }
    int searchKey = (width << 12) | height;
    
    std::map<int, SharedPtr<OcclusionBuffer> >::iterator i = mOcclusionBuffers.find(searchKey);
    if (i != mOcclusionBuffers.end())
        return i->second;
    else
        return 0;
}

void Pipeline::beginFrame(float timeStep)
{
    mElapsedTime += timeStep;
    if (mElapsedTime >= MAX_ELAPSED_TIME)
        mElapsedTime -= MAX_ELAPSED_TIME;
    
    ++mFrameNumber;
    mFrameNumber &= M_MAX_INT;
    
    mFrame.mFrameNumber = mFrameNumber;
    mFrame.mTimeStep = timeStep;
    mFrame.mCamera = 0;
    
    mNumViews = 0;
    mNumSplitLights = 0;
}

void Pipeline::resetViews()
{
    mViews.clear();
    mNumViews = 0;
}

void Pipeline::addView(Octree* octree, Camera* camera, RenderSurface* renderTarget)
{
    if (mViews.size() <= mNumViews)
        mViews.resize(mNumViews + 1);
    if (!mViews[mNumViews])
        mViews[mNumViews] = new View(this);
    
    mViews[mNumViews]->define(octree, camera, renderTarget);
    ++mNumViews;
}

OcclusionBuffer* Pipeline::getOrCreateOcclusionBuffer(Camera& camera, int maxOccluderTriangles, bool halfResolution)
{
    // Get an occlusion buffer matching the aspect ratio. If not found, allocate new
    int width = mOcclusionBufferSize;
    int height = (int)(mOcclusionBufferSize / camera.getAspectRatio());
    if (halfResolution)
    {
        width >>= 1;
        height >>= 1;
    }
    int searchKey = (width << 12) | height;
    
    SharedPtr<OcclusionBuffer> buffer;
    std::map<int, SharedPtr<OcclusionBuffer> >::iterator i = mOcclusionBuffers.find(searchKey);
    if (i != mOcclusionBuffers.end())
        buffer = i->second;
    else
    {
        buffer = new OcclusionBuffer();
        buffer->setSize(width, height);
        mOcclusionBuffers[searchKey] = buffer;
    }
    
    buffer->setView(camera);
    buffer->setMaxTriangles(maxOccluderTriangles);
    buffer->clear();
    
    return buffer;
}

Geometry* Pipeline::getLightGeometry(Light* light)
{
    switch (light->getLightType())
    {
    case LIGHT_POINT:
        return mPointLightGeometry;
        
    case LIGHT_SPOT:
    case LIGHT_SPLITPOINT:
        return mSpotLightGeometry;
        
    default:
        return mDirLightGeometry;
    }
}

Texture2D* Pipeline::getShadowMap(float resolution)
{
    if (resolution >= 0.75f)
        return mFullShadowMap;
    else if (resolution >= 0.375f)
        return mHalfShadowMap;
    else
        return mQuarterShadowMap;
}

void Pipeline::setBatchShaders(Batch& batch, MaterialTechnique* technique, MaterialPass* pass, bool allowShadows)
{
    static std::set<Material*> errorDisplayed;
    
    batch.mTechnique = technique;
    batch.mPass = pass;
    
    // Check if shaders are unloaded or need reloading
    std::vector<SharedPtr<VertexShader> >& vertexShaders = pass->getVertexShaders();
    std::vector<SharedPtr<PixelShader> >& pixelShaders = pass->getPixelShaders();
    if ((!vertexShaders.size()) || (!pixelShaders.size()) || (technique->getShadersLoadedFrameNumber() !=
        mShadersChangedFrameNumber))
    {
        // First release all previous shaders, then load
        technique->releaseShaders();
        loadMaterialShaders(technique);
    }
    
    // Make sure shaders are loaded now
    if ((vertexShaders.size()) && (pixelShaders.size()))
    {
        // Recognize light pass from the amount of shaders
        if (pixelShaders.size() == 1)
        {
            unsigned vsi = 0;
            if (batch.mNode->getNodeFlags() & NODE_GEOMETRY)
                vsi = static_cast<GeometryNode*>(batch.mNode)->getGeometryType();
            
            batch.mVertexShader = vertexShaders[vsi];
            batch.mPixelShader = pixelShaders[0];
        }
        else
        {
            Light* light = batch.mForwardLight;
            if (!light)
            {
                // Do not log error, as it would result in a lot of spam
                batch.mVertexShader = 0;
                batch.mPixelShader = 0;
                return;
            }
            
            unsigned vsi = 0;
            unsigned psi = 0;
            if (batch.mNode->getNodeFlags() & NODE_GEOMETRY)
                vsi = static_cast<GeometryNode*>(batch.mNode)->getGeometryType() * MAX_LIGHT_VS_VARIATIONS;
            
            // Negative lights have no specular or shadows
            if (!light->isNegative())
            {
                if ((mSpecularLighting) && (light->getSpecularIntensity() > 0.0f))
                    psi += LPS_SPEC;
                if ((allowShadows) && (light->getShadowMap()))
                {
                    vsi += LVS_SHADOW;
                    psi += LPS_SHADOW;
                }
            }
            else
                psi += LPS_NEGATIVE;
            
            switch (light->getLightType())
            {
            case LIGHT_POINT:
            case LIGHT_SPLITPOINT:
                psi += LPS_POINT;
                break;
                
            case LIGHT_SPOT:
                psi += LPS_SPOT;
                vsi += LVS_SPOT;
                break;
            }
            
            batch.mVertexShader = vertexShaders[vsi];
            batch.mPixelShader = pixelShaders[psi];
        }
    }
    
    // Log error if shaders could not be assigned, but only once per material
    if ((!batch.mVertexShader) || (!batch.mPixelShader))
    {
        Material* parentMat = technique->getParent();
        if (errorDisplayed.find(parentMat) == errorDisplayed.end())
        {
            errorDisplayed.insert(parentMat);
            LOGERROR("Material " + parentMat->getName() + " has missing shaders");
        }
    }
}

void Pipeline::setLightVolumeShaders(Batch& batch)
{
    unsigned vsi = DLVS_NONE;
    unsigned psi = DLPS_NONE;
    
    Light* light = static_cast<Light*>(batch.mNode);
    switch(light->getLightType())
    {
    case LIGHT_DIRECTIONAL:
        vsi += DLVS_DIR;
        break;
        
    case LIGHT_POINT:
    case LIGHT_SPLITPOINT:
        psi += DLPS_POINT;
        break;
        
    case LIGHT_SPOT:
        psi += DLPS_SPOT;
        break;
    }
    
    if (!light->isNegative())
    {
        if (light->getShadowMap())
            psi += DLPS_SHADOW;
        
        if ((mSpecularLighting) && (light->getSpecularIntensity() > 0.0))
            psi += DLPS_SPEC;
    }
    else
        psi += DLPS_NEGATIVE;
    
    // Non-hardware depth & orthographic modes use linear depth, else reconstruct from z/w
    if (batch.mCamera->isOrthographic())
    {
        vsi += DLVS_ORTHO;
        psi += DLPS_ORTHO;
    }
    else if (!mRenderer->getHardwareDepthSupport())
        psi += DLPS_LINEAR;
    
    unsigned hwShadows = mRenderer->getHardwareShadowSupport() ? 1 : 0;
    
    if (!mLightVS[vsi])
        mLightVS[vsi] = getVertexShader(mLightShaderName + deferredLightVSVariations[vsi]);
    
    if (!mLightPS[psi])
    {
        unsigned variation = psi % 5;
        if ((variation == LPS_SHADOW) || (variation == LPS_SHADOWSPEC))
            mLightPS[psi] = getPixelShader(mLightShaderName + deferredLightPSVariations[psi] + shadowPSVariations[hwShadows]);
        else
            mLightPS[psi] = getPixelShader(mLightShaderName + deferredLightPSVariations[psi]);
    }
    
    batch.mVertexShader = mLightVS[vsi];
    batch.mPixelShader = mLightPS[psi];
}

void Pipeline::loadShaders()
{
    PROFILE(Pipeline_LoadShaders);
    
    LOGINFO("Reloading shaders");
    
    // Release old material shaders, mark them for reload
    releaseMaterialShaders();
    mShadersChangedFrameNumber = mFrameNumber;
    
    // Load inbuilt shaders
    mStencilVS = getVertexShader("Stencil");
    mStencilPS = getPixelShader("Stencil");
    mLightVS.clear();
    mLightPS.clear();
    RenderMode renderMode = mRenderer->getRenderMode();
    if (renderMode != RENDER_FORWARD)
    {
        // There are rather many light volume shader variations, so load them later on-demand
        mLightVS.resize(MAX_DEFERRED_LIGHT_VS_VARIATIONS);
        mLightPS.resize(MAX_DEFERRED_LIGHT_PS_VARIATIONS);
        if (renderMode == RENDER_DEFERRED)
            mLightShaderName = "Deferred/Light_";
        else
            mLightShaderName = "Prepass/Light_";
    }
    
    // Remove shaders that are no longer referenced from the cache
    mCache->releaseResources(VertexShader::getTypeStatic());
    mCache->releaseResources(PixelShader::getTypeStatic());
    
    mShadersDirty = false;
}

void Pipeline::loadMaterialShaders(MaterialTechnique* technique)
{
    loadMaterialPassShaders(technique, PASS_SHADOW);
    loadMaterialPassShaders(technique, PASS_POSTOPAQUE);
    
    if (mRenderer->getRenderMode() == RENDER_FORWARD)
    {
        loadMaterialPassShaders(technique, PASS_AMBIENT);
        loadMaterialPassShaders(technique, PASS_LIGHT);
        loadMaterialPassShaders(technique, PASS_NEGATIVE, false);
    }
    else
    {
        // G-Buffer pass types depend on whether deferred shading or light prepass is in use
        PassType gBufferPass, additionalPass;
        if (mRenderer->getRenderMode() == RENDER_DEFERRED)
        {
            gBufferPass = PASS_DEFERRED;
            additionalPass = PASS_EMISSIVE;
        }
        else
        {
            gBufferPass = PASS_PREPASS;
            additionalPass = PASS_MATERIAL;
        }
        
        if (technique->hasPass(gBufferPass))
        {
            loadMaterialPassShaders(technique, gBufferPass);
            loadMaterialPassShaders(technique, additionalPass);
        }
        else
        {
            loadMaterialPassShaders(technique, PASS_AMBIENT);
            // No shadows used in forward lighting, so do not load the shadowing shaders
            loadMaterialPassShaders(technique, PASS_LIGHT, false);
            loadMaterialPassShaders(technique, PASS_NEGATIVE, false);
        }
    }
}

void Pipeline::loadMaterialPassShaders(MaterialTechnique* technique, PassType pass, bool allowShadows)
{
    std::map<PassType, MaterialPass>::iterator i = technique->mPasses.find(pass);
    if (i == technique->mPasses.end())
        return;
    
    std::string vertexShaderName = i->second.getVertexShaderName();
    std::string pixelShaderName = i->second.getPixelShaderName();
    
    // Check if the shader name is already a variation in itself
    if (vertexShaderName.find('_') == std::string::npos)
        vertexShaderName += "_";
    if (pixelShaderName.find('_') == std::string::npos)
        pixelShaderName += "_";
    
    // If INTZ depth is used, do not write depth into the third RT in GBuffer pass
    if ((pass == PASS_DEFERRED) || (pass == PASS_PREPASS))
    {
        unsigned hwDepth = mRenderer->getHardwareDepthSupport() ? 1 : 0;
        pixelShaderName += gBufferPSVariations[hwDepth];
    }
    
    // If ambient pass is not using REPLACE as the blend mode, do not load shadow shaders for the light pass
    if (pass == PASS_LIGHT)
    {
        if ((!technique->hasPass(PASS_AMBIENT)) || (technique->getPass(PASS_AMBIENT)->getBlendMode() != BLEND_REPLACE))
            allowShadows = false;
    }
    
    if (pass == PASS_NEGATIVE)
        allowShadows = false;
    
    unsigned hwShadows = mRenderer->getHardwareShadowSupport() ? 1 : 0;
    
    std::vector<SharedPtr<VertexShader> >& vertexShaders = i->second.getVertexShaders();
    std::vector<SharedPtr<PixelShader> >& pixelShaders = i->second.getPixelShaders();
    
    // Forget all the old shaders
    vertexShaders.clear();
    pixelShaders.clear();
    
    try
    {
        switch (i->first)
        {
        default:
            vertexShaders.resize(MAX_GEOMETRYTYPES);
            pixelShaders.resize(1);
            for (unsigned j = 0; j < MAX_GEOMETRYTYPES; ++j)
                vertexShaders[j] = getVertexShader(vertexShaderName + geometryVSVariations[j], j != 0);
            pixelShaders[0] = getPixelShader(pixelShaderName);
            break;
            
        case PASS_LIGHT:
        case PASS_NEGATIVE:
            vertexShaders.resize(MAX_GEOMETRYTYPES * MAX_LIGHT_VS_VARIATIONS);
            pixelShaders.resize(MAX_LIGHT_PS_VARIATIONS);
            
            for (unsigned j = 0; j < MAX_GEOMETRYTYPES * MAX_LIGHT_VS_VARIATIONS; ++j)
            {
                unsigned g = j / MAX_LIGHT_VS_VARIATIONS;
                unsigned l = j % MAX_LIGHT_VS_VARIATIONS;
                if ((!(l & LVS_SHADOW)) || (allowShadows))
                    vertexShaders[j] = getVertexShader(vertexShaderName + lightVSVariations[l] + geometryVSVariations[g], g != 0);
                else
                    vertexShaders[j].reset();
            }
            for (unsigned j = 0; j < MAX_LIGHT_PS_VARIATIONS; ++j)
            {
                unsigned variation = j % 5;
                if ((variation == LPS_SHADOW) || (variation == LPS_SHADOWSPEC))
                {
                    if (allowShadows)
                        pixelShaders[j] = getPixelShader(pixelShaderName + deferredLightPSVariations[j] + 
                            shadowPSVariations[hwShadows]);
                    else
                        pixelShaders[j].reset();
                }
                else
                {
                    // For the negative pass, load only the negative version of the shader
                    bool needed = (pass == PASS_LIGHT) ? (variation != LPS_NEGATIVE) : (variation == LPS_NEGATIVE);
                    if (needed)
                        pixelShaders[j] = getPixelShader(pixelShaderName + deferredLightPSVariations[j]);
                    else
                        pixelShaders[j].reset();
                }
            }
            break;
        }
    }
    catch (...)
    {
    }
    
    technique->markShadersLoaded(mShadersChangedFrameNumber);
}

void Pipeline::releaseMaterialShaders()
{
    std::vector<Material*> materials = mCache->getResources<Material>();
    
    for (unsigned i = 0; i < materials.size(); ++i)
    {
        for (unsigned j = 0; j < materials[i]->getNumTechniques(); ++j)
            materials[i]->releaseShaders();
    }
}

void Pipeline::reloadTextures()
{
    std::vector<Texture2D*> textures = mCache->getResources<Texture2D>();
    std::vector<TextureCube*> cubeTextures = mCache->getResources<TextureCube>();
    
    for (unsigned i = 0; i < textures.size(); ++i)
        mCache->reloadResource(textures[i]);
    for (unsigned i = 0; i < cubeTextures.size(); ++i)
        mCache->reloadResource(cubeTextures[i]);
}

void Pipeline::createGeometries()
{
    PROFILE(Pipeline_CreateGeometries);
    
    SharedPtr<VertexBuffer> dlvb(new VertexBuffer(mRenderer));
    dlvb->setSize(4, MASK_POSITION);
    dlvb->setData(dirLightVertexData);
    
    SharedPtr<IndexBuffer> dlib(new IndexBuffer(mRenderer));
    dlib->setSize(6, false);
    dlib->setData(dirLightIndexData);
    
    mDirLightGeometry = new Geometry();
    mDirLightGeometry->setVertexBuffer(0, dlvb);
    mDirLightGeometry->setIndexBuffer(dlib);
    mDirLightGeometry->setDrawRange(TRIANGLE_LIST, 0, dlib->getIndexCount());
    
    SharedPtr<VertexBuffer> plvb(new VertexBuffer(mRenderer));
    plvb->setSize(24, MASK_POSITION);
    plvb->setData(pointLightVertexData);
    
    SharedPtr<IndexBuffer> plib(new IndexBuffer(mRenderer));
    plib->setSize(132, false);
    plib->setData(pointLightIndexData);
    
    mPointLightGeometry = new Geometry();
    mPointLightGeometry->setVertexBuffer(0, plvb);
    mPointLightGeometry->setIndexBuffer(plib);
    mPointLightGeometry->setDrawRange(TRIANGLE_LIST, 0, plib->getIndexCount());
    
    SharedPtr<VertexBuffer> slvb(new VertexBuffer(mRenderer));
    slvb->setSize(8, MASK_POSITION);
    slvb->setData(spotLightVertexData);
    
    SharedPtr<IndexBuffer> slib(new IndexBuffer(mRenderer));
    slib->setSize(36, false);
    slib->setData(spotLightIndexData);
    
    mSpotLightGeometry = new Geometry();
    mSpotLightGeometry->setVertexBuffer(0, slvb);
    mSpotLightGeometry->setIndexBuffer(slib);
    mSpotLightGeometry->setDrawRange(TRIANGLE_LIST, 0, slib->getIndexCount());
}

bool Pipeline::createShadowMaps()
{
    PROFILE(Pipeline_CreateShadowMaps);
    
    unsigned shadowMapFormat = mShadowMapHiresDepth ? mRenderer->getHiresShadowMapFormat() : mRenderer->getShadowMapFormat();
    unsigned dummyColorFormat = mRenderer->getDummyColorFormat();
    bool hardwarePCF = mRenderer->getHardwareShadowSupport();
    
    if (shadowMapFormat == D3DFMT_UNKNOWN)
        return false;
    
    if (!mDrawShadows)
    {
        mFullShadowMap.reset();
        mHalfShadowMap.reset();
        mQuarterShadowMap.reset();
        mFullShadowMapColor.reset();
        mHalfShadowMapColor.reset();
        mQuarterShadowMapColor.reset();
        return true;
    }
    
    try
    {
        // Create shadow maps and dummy color rendertargets
        if (!mFullShadowMap)
            mFullShadowMap = new Texture2D(mRenderer, TEXTURE_DEPTHSTENCIL);
        mFullShadowMap->setSize(mShadowMapSize, mShadowMapSize, shadowMapFormat);
        mFullShadowMap->setFilterMode(hardwarePCF ? FILTER_BILINEAR : FILTER_NEAREST);
        
        if (!mHalfShadowMap)
            mHalfShadowMap = new Texture2D(mRenderer, TEXTURE_DEPTHSTENCIL);
        mHalfShadowMap->setSize(mShadowMapSize >> 1, mShadowMapSize >> 1, shadowMapFormat);
        mHalfShadowMap->setFilterMode(hardwarePCF ? FILTER_BILINEAR : FILTER_NEAREST);
        
        if (!mQuarterShadowMap)
            mQuarterShadowMap = new Texture2D(mRenderer, TEXTURE_DEPTHSTENCIL);
        mQuarterShadowMap->setSize(mShadowMapSize >> 2, mShadowMapSize >> 2, shadowMapFormat);
        mQuarterShadowMap->setFilterMode(hardwarePCF ? FILTER_BILINEAR : FILTER_NEAREST);
        
        if (!mFullShadowMapColor)
            mFullShadowMapColor = new Texture2D(mRenderer, TEXTURE_RENDERTARGET);
        mFullShadowMapColor->setSize(mShadowMapSize, mShadowMapSize, dummyColorFormat);
        
        if (!mHalfShadowMapColor)
            mHalfShadowMapColor = new Texture2D(mRenderer, TEXTURE_RENDERTARGET);
        mHalfShadowMapColor->setSize(mShadowMapSize >> 1, mShadowMapSize >> 1, dummyColorFormat);
        
        if (!mQuarterShadowMapColor)
            mQuarterShadowMapColor = new Texture2D(mRenderer, TEXTURE_RENDERTARGET);
        mQuarterShadowMapColor->setSize(mShadowMapSize >> 2, mShadowMapSize >> 2, dummyColorFormat);
        
        // Link the color rendertargets to depth rendertargets
        mFullShadowMap->getRenderSurface()->setLinkedRenderTarget(mFullShadowMapColor->getRenderSurface());
        mHalfShadowMap->getRenderSurface()->setLinkedRenderTarget(mHalfShadowMapColor->getRenderSurface());
        mQuarterShadowMap->getRenderSurface()->setLinkedRenderTarget(mQuarterShadowMapColor->getRenderSurface());
    }
    catch (...)
    {
        return false;
    }
    
    return true;
}

Light* Pipeline::createSplitLight(Light* original)
{
    if (mNumSplitLights >= mSplitLightStore.size())
        mSplitLightStore.push_back(SharedPtr<Light>(new Light()));
    Light* light = mSplitLightStore[mNumSplitLights];
    light->copyFrom(original);
    
    mNumSplitLights++;
    return light;
}

void Pipeline::setupLightBatch(Batch& batch)
{
    Light* light = static_cast<Light*>(batch.mNode);
    
    const Matrix4x3* model = &light->getWorldTransform();
    const Matrix4x3* view = &batch.mCamera->getInverseWorldTransform();
    const Matrix4* projection = &batch.mCamera->getProjection();
    
    light->overrideTransforms(0, *batch.mCamera, &model, &view);
    
    float lightExtent = light->getVolumeExtent();
    float lightViewDist = (light->getWorldPosition() - batch.mCamera->getWorldPosition()).getLengthFast();
    
    mRenderer->setAlphaTest(false);
    mRenderer->setBlendMode(light->isNegative() ? BLEND_MULTIPLY : BLEND_ADD);
    mRenderer->setDepthWrite(false);
    
    if (light->getLightType() == LIGHT_DIRECTIONAL)
    {
        // If the light does not extend to the near plane, use a stencil test. Else just draw with depth fail
        if (light->getNearSplit() <= batch.mCamera->getNearClip())
        {
            mRenderer->setCullMode(CULL_NONE);
            mRenderer->setDepthTest(CMP_GREATER);
            mRenderer->setStencilTest(false);
        }
        else
        {
            Matrix4x3 nearTransform = light->getDirLightTransform(*batch.mCamera, true);
            
            // Set state for stencil rendering
            mRenderer->setColorWrite(false);
            mRenderer->setCullMode(CULL_NONE);
            mRenderer->setDepthTest(CMP_LESSEQUAL);
            mRenderer->setStencilTest(true, CMP_ALWAYS, OP_INCR, OP_KEEP, OP_KEEP, 1);
            mRenderer->setVertexShader(mStencilVS);
            mRenderer->setPixelShader(mStencilPS);
            mRenderer->setVertexShaderConstant(getVSRegister(VSP_MODELVIEWPROJ), (*projection) * nearTransform);
            
            // Draw to stencil
            batch.mGeometry->draw(mRenderer);
            
            // Re-enable color write, set test for rendering the actual light
            mRenderer->setColorWrite(true);
            mRenderer->setDepthTest(CMP_GREATER);
            mRenderer->setStencilTest(true, CMP_EQUAL, OP_ZERO, OP_KEEP, OP_ZERO, 1);
        }
    }
    else
    {
        if (light->getLightType() == LIGHT_SPLITPOINT)
        {
            // Shadowed point light, split in 6 frustums: mask out overlapping pixels to prevent overlighting
            // Check whether we should draw front or back faces
            bool drawBackFaces = lightViewDist < (lightExtent + batch.mCamera->getNearClip());
            mRenderer->setColorWrite(false);
            mRenderer->setCullMode(drawBackFaces ? CULL_CCW : CULL_CW);
            mRenderer->setDepthTest(drawBackFaces ? CMP_GREATER : CMP_LESS);
            mRenderer->setStencilTest(true, CMP_EQUAL, OP_INCR, OP_KEEP, OP_KEEP, 0);
            mRenderer->setVertexShader(mStencilVS);
            mRenderer->setPixelShader(mStencilPS);
            mRenderer->setVertexShaderConstant(getVSRegister(VSP_MODELVIEWPROJ), (*projection) * (*view) * (*model));
            
            // Draw the other faces to stencil to mark where we should not draw
            batch.mGeometry->draw(mRenderer);
            
            mRenderer->setColorWrite(true);
            mRenderer->setCullMode(drawBackFaces ? CULL_CW : CULL_CCW);
            mRenderer->setStencilTest(true, CMP_EQUAL, OP_DECR, OP_DECR, OP_KEEP, 0);
        }
        else
        {
            // If light is close to near clip plane, we might be inside light volume
            if (lightViewDist < (lightExtent + batch.mCamera->getNearClip()))
            {
                // In this case reverse cull mode & depth test and render back faces
                mRenderer->setCullMode(CULL_CW);
                mRenderer->setDepthTest(CMP_GREATER);
                mRenderer->setStencilTest(false);
            }
            else
            {
                // If not too close to far clip plane, write the back faces to stencil for optimization,
                // then render front faces. Else just render front faces.
                if (lightViewDist < (batch.mCamera->getFarClip() - lightExtent))
                {
                    // Set state for stencil rendering
                    mRenderer->setColorWrite(false);
                    mRenderer->setCullMode(CULL_CW);
                    mRenderer->setDepthTest(CMP_GREATEREQUAL);
                    mRenderer->setStencilTest(true, CMP_ALWAYS, OP_INCR, OP_KEEP, OP_KEEP, 1);
                    mRenderer->setVertexShader(mStencilVS);
                    mRenderer->setPixelShader(mStencilPS);
                    mRenderer->setVertexShaderConstant(getVSRegister(VSP_MODELVIEWPROJ), (*projection) * (*view) * (*model));
                    
                    // Draw to stencil
                    batch.mGeometry->draw(mRenderer);
                    
                    // Re-enable color write, set test for rendering the actual light
                    mRenderer->setColorWrite(true);
                    mRenderer->setStencilTest(true, CMP_EQUAL, OP_ZERO, OP_KEEP, OP_ZERO, 1);
                    mRenderer->setCullMode(CULL_CCW);
                    mRenderer->setDepthTest(CMP_LESS);
                }
                else
                {
                    mRenderer->setStencilTest(false);
                    mRenderer->setCullMode(CULL_CCW);
                    mRenderer->setDepthTest(CMP_LESS);
                }
            }
        }
    }
}

void Pipeline::drawFullScreenQuad(Camera& camera, VertexShader* vs, PixelShader* ps, bool nearQuad)
{
    Light quadDirLight;
    Matrix4x3 model = quadDirLight.getDirLightTransform(camera, nearQuad);
    
    mRenderer->setCullMode(CULL_NONE);
    mRenderer->setVertexShader(vs);
    mRenderer->setPixelShader(ps);
    mRenderer->setVertexShaderConstant(getVSRegister(VSP_MODELVIEWPROJ), camera.getProjection() * model);
    
    mDirLightGeometry->draw(mRenderer);
}

void Pipeline::drawSplitLightToStencil(Camera& camera, Light* light, bool clear)
{
    switch (light->getLightType())
    {
    case LIGHT_SPLITPOINT:
        {
            const Matrix4x3* model = &light->getWorldTransform();
            const Matrix4x3* view = &camera.getInverseWorldTransform();
            const Matrix4* projection = &camera.getProjection();
            
            light->overrideTransforms(0, camera, &model, &view);
            
            float lightExtent = light->getVolumeExtent();
            float lightViewDist = (light->getWorldPosition() - camera.getWorldPosition()).getLengthFast();
            bool drawBackFaces = lightViewDist < (lightExtent + camera.getNearClip());
            
            mRenderer->setAlphaTest(false);
            mRenderer->setColorWrite(false);
            mRenderer->setDepthWrite(false);
            mRenderer->setCullMode(drawBackFaces ? CULL_CW : CULL_CCW);
            mRenderer->setDepthTest(drawBackFaces ? CMP_GREATER : CMP_LESS);
            mRenderer->setVertexShader(mStencilVS);
            mRenderer->setPixelShader(mStencilPS);
            mRenderer->setVertexShaderConstant(getVSRegister(VSP_MODELVIEWPROJ), (*projection) * (*view) * (*model));
            
            if (!clear)
            {
                // Draw the faces to stencil which we should draw (where no light has not been rendered yet)
                mRenderer->setStencilTest(true, CMP_EQUAL, OP_INCR, OP_KEEP, OP_KEEP, 0);
                mSpotLightGeometry->draw(mRenderer);
                
                // Draw the other faces to stencil to mark where we should not draw ("frees up" the pixels for other faces)
                mRenderer->setCullMode(drawBackFaces ? CULL_CCW : CULL_CW);
                mRenderer->setStencilTest(true, CMP_EQUAL, OP_DECR, OP_KEEP, OP_KEEP, 1);
                mSpotLightGeometry->draw(mRenderer);
                
                // Now set stencil test for rendering the lit geometries (also marks the pixels so that they will not be used again)
                mRenderer->setStencilTest(true, CMP_EQUAL, OP_INCR, OP_KEEP, OP_KEEP, 1);
                mRenderer->setColorWrite(true);
            }
            else
            {
                // Clear the stencil by drawing the whole point light volume
                mRenderer->setStencilTest(true, CMP_ALWAYS, OP_ZERO, OP_KEEP, OP_ZERO, 0);
                mPointLightGeometry->draw(mRenderer);
                mRenderer->setColorWrite(true);
                mRenderer->setStencilTest(false);
            }
        }
        break;
        
    case LIGHT_DIRECTIONAL:
        // If light encompasses whole frustum, no drawing to frustum necessary
        if ((light->getNearSplit() <= camera.getNearClip()) && (light->getFarSplit() >= camera.getFarClip()))
            return;
        else
        {
            const Matrix4& projection = camera.getProjection();
            Matrix4x3 nearTransform = light->getDirLightTransform(camera, true);
            Matrix4x3 farTransform = light->getDirLightTransform(camera, false);
            
            mRenderer->setAlphaTest(false);
            mRenderer->setColorWrite(false);
            mRenderer->setDepthWrite(false);
            mRenderer->setCullMode(CULL_NONE);
            
            if (!clear)
            {
                // If the split begins at the near plane (first split), draw at split far plane
                if (light->getNearSplit() <= camera.getNearClip())
                {
                    mRenderer->setDepthTest(CMP_GREATEREQUAL);
                    mRenderer->setVertexShader(mStencilVS);
                    mRenderer->setPixelShader(mStencilPS);
                    mRenderer->setVertexShaderConstant(getVSRegister(VSP_MODELVIEWPROJ), projection * farTransform);
                    mRenderer->setStencilTest(true, CMP_ALWAYS, OP_REF, OP_ZERO, OP_ZERO, 1);
                }
                // Otherwise draw at split near plane
                else
                {
                    mRenderer->setDepthTest(CMP_LESSEQUAL);
                    mRenderer->setVertexShader(mStencilVS);
                    mRenderer->setPixelShader(mStencilPS);
                    mRenderer->setVertexShaderConstant(getVSRegister(VSP_MODELVIEWPROJ), projection * nearTransform);
                    mRenderer->setStencilTest(true, CMP_ALWAYS, OP_REF, OP_ZERO, OP_ZERO, 1);
                }
                
                mDirLightGeometry->draw(mRenderer);
                mRenderer->setColorWrite(true);
                mRenderer->setStencilTest(true, CMP_EQUAL, OP_KEEP, OP_KEEP, OP_KEEP, 1);
            }
            else
            {
                // Clear the stencil by drawing at the far plane (assumed to be the last and most distant split)
                mRenderer->setDepthTest(CMP_GREATER);
                mRenderer->setVertexShader(mStencilVS);
                mRenderer->setPixelShader(mStencilPS);
                mRenderer->setVertexShaderConstant(getVSRegister(VSP_MODELVIEWPROJ), projection * farTransform);
                mRenderer->setStencilTest(true, CMP_ALWAYS, OP_ZERO, OP_KEEP, OP_ZERO, 0);
                mDirLightGeometry->draw(mRenderer);
                mRenderer->setColorWrite(true);
                mRenderer->setStencilTest(false);
            }
        }
    }
}

void Pipeline::handleWindowResized(StringHash eventType, VariantMap& eventData)
{
    // When screen mode changes, reload shaders and purge old views and occlusion buffers
    mShadersDirty = true;
    mOcclusionBuffers.clear();
    resetViews();
}
