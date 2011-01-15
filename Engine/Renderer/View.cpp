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
#include "GeometryNode.h"
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
#include "Texture2D.h"
#include "TextureCube.h"
#include "VertexShader.h"
#include "View.h"

#include <algorithm>

Zone View::sDefaultZone;
Light* View::sSplitLights[MAX_LIGHT_SPLITS];
std::vector<GeometryNode*> View::sLitGeometries[MAX_LIGHT_SPLITS];
std::vector<GeometryNode*> View::sShadowCasters[MAX_LIGHT_SPLITS];

static bool compareNodes(const VolumeNode* lhs, const VolumeNode* rhs)
{
    return lhs->getSortValue() < rhs->getSortValue();
}

View::View(Pipeline* pipeline) :
    mPipeline(pipeline),
    mOctree(0),
    mCamera(0),
    mZone(0),
    mRenderTarget(0),
    mDepthStencil(0),
    mSM3Support(pipeline->getRenderer()->getSM3Support())
{
    mFrame.mCamera = 0;
}

View::~View()
{
}

void View::define(Octree* octree, Camera* camera, RenderSurface* renderTarget)
{
    if ((!octree) || (!camera))
    {
        LOGERROR("Null octree or camera for View");
        return;
    }
    
    Renderer* renderer = mPipeline->getRenderer();
    
    // In deferred mode, check for the render texture being too large
    if ((renderer->getRenderMode() != RENDER_FORWARD) && (renderTarget))
    {
        if ((renderTarget->getWidth() > renderer->getWidth()) || (renderTarget->getHeight() > renderer->getHeight()))
        {
            // Display message only once per rendertarget, do not spam each frame
            static std::set<RenderSurface*> errorDisplayed;
            if (errorDisplayed.find(renderTarget) == errorDisplayed.end())
            {
                errorDisplayed.insert(renderTarget);
                LOGERROR("Render texture is larger than the G-buffer, can not add view");
            }
            return;
        }
    }
    
    mOctree = octree;
    mCamera = camera;
    mRenderTarget = renderTarget;
    
    if (renderTarget)
        mDepthStencil = renderTarget->getLinkedDepthBuffer();
    else
        mDepthStencil = 0;
    mZone = &sDefaultZone;
    
    // If there is a specified render texture, use its dimensions, else the main view size
    if (renderTarget)
    {
        mWidth = renderTarget->getWidth();
        mHeight = renderTarget->getHeight();
    }
    else
    {
        mWidth = renderer->getWidth();
        mHeight = renderer->getHeight();
    }
    
    // Set possible quality overrides from the camera
    mDrawShadows = mPipeline->getDrawShadows() && (camera->getDrawShadowsOverride());
    mLightDetailLevel = min(mPipeline->getLightDetailLevel(), camera->getLightDetailLevelOverride());
    mMaterialQuality = min(mPipeline->getMaterialQuality(), camera->getMaterialQualityOverride());
    mMaxOccluderTriangles = min(mPipeline->getMaxOccluderTriangles(), camera->getMaxOccluderTrianglesOverride());
    
    // Clear light scissor cache, geometry, light, occluder & batch lists
    mLightScissorCache.clear();
    mGeometries.clear();
    mGeometryDepthBounds.clear();
    mLights.clear();
    mOccluders.clear();
    mShadowOccluders.clear();
    mGBufferQueue.clear();
    mNegativeLightQueue.clear();
    mNoShadowLightQueue.clear();
    mAmbientQueue.clear();
    mNegativeQueue.clear();
    mForwardQueue.clear();
    mPostOpaqueQueue.clear();
    mTransparentQueue.clear();
    mLightQueues.clear();
}

void View::update(const FrameInfo& frame)
{
    if ((!mCamera) || (!mOctree))
        return;
    
    mFrame.mCamera = mCamera;
    mFrame.mTimeStep = frame.mTimeStep;
    mFrame.mFrameNumber = frame.mFrameNumber;
    
    mCamera->markInView(mFrame.mFrameNumber);
    getNodes();
    
    if (mPipeline->getRenderer()->getRenderMode() != RENDER_FORWARD)
        getBatchesDeferred();
    else
        getBatchesForward();
}

void View::render()
{
    if ((!mOctree) || (!mCamera))
        return;
    
    Renderer* renderer = mPipeline->getRenderer();
    
    // Set the "view texture" to ensure the rendertarget will not be bound as a texture during G-buffer rendering
    if (mRenderTarget)
        renderer->setViewTexture(mRenderTarget->getParentTexture());
    else
        renderer->setViewTexture(0);
    
    // Set per-view shader parameters
    float fogStart = mZone->getFogStart();
    float fogEnd = mZone->getFogEnd();
    float fogRange = max(fogEnd - fogStart, M_EPSILON);
    float farClip = mCamera->getFarClip();
    float nearClip = mCamera->getNearClip();
    Vector4 fogParams(fogStart / farClip, fogEnd / farClip, 1.0f / (fogRange / farClip), 0.0f);
    Vector4 elapsedTime(mPipeline->getElapsedTime(), 0.0f, 0.0f, 0.0f);
    Vector4 depthReconstruct = Vector4::sZero;
    
    // Non-hardware depth & orthographic modes use linear depth, else reconstruct from z/w
    if ((!mCamera->isOrthographic()) && (renderer->getHardwareDepthSupport()))
    {
        depthReconstruct.mX = farClip / (farClip - nearClip);
        depthReconstruct.mY = -nearClip / (farClip - nearClip);
    }
    
    renderer->setVertexShaderConstant(getVSRegister(VSP_AMBIENTCOLOR), mZone->getAmbientColor());
    renderer->setVertexShaderConstant(getVSRegister(VSP_ELAPSEDTIME), elapsedTime);
    renderer->setPixelShaderConstant(getPSRegister(PSP_AMBIENTCOLOR), mZone->getAmbientColor());
    renderer->setPixelShaderConstant(getPSRegister(PSP_DEPTHRECONSTRUCT), depthReconstruct);
    renderer->setPixelShaderConstant(getPSRegister(PSP_ELAPSEDTIME), elapsedTime);
    renderer->setPixelShaderConstant(getPSRegister(PSP_FOGCOLOR), mZone->getFogColor());
    renderer->setPixelShaderConstant(getPSRegister(PSP_FOGPARAMS), fogParams);
    
    if (mPipeline->getRenderer()->getRenderMode() != RENDER_FORWARD)
        renderBatchesDeferred();
    else
        renderBatchesForward();
    
    // "Forget" the camera, octree and zone after rendering
    mCamera = 0;
    mOctree = 0;
    mZone = 0;
    mFrame.mCamera = 0;
}

void View::getNodes()
{
    PROFILE(View_GetNodes);
    
    Renderer* renderer = mPipeline->getRenderer();
    
    // Get zones & find the zone camera is in
    static std::vector<Zone*> zones;
    PointOctreeQuery query(mCamera->getWorldPosition(), reinterpret_cast<std::vector<VolumeNode*>& >(zones), NODE_ZONE);
    mOctree->getNodes(query);
    
    int highestZonePriority = M_MIN_INT;
    const Vector3& cameraPos = mCamera->getWorldPosition();
    for (unsigned i = 0; i < zones.size(); ++i)
    {
        Zone* zone = zones[i];
        if ((zone->isInside(cameraPos)) && (zone->getPriority() > highestZonePriority))
        {
            mZone = zone;
            highestZonePriority = zone->getPriority();
        }
    }
    
    // If occlusion in use, get & render the occluders, then build the depth buffer hierarchy
    bool useOcclusion = false;
    OcclusionBuffer* buffer = 0;
    
    if (mMaxOccluderTriangles > 0)
    {
        FrustumOctreeQuery query(mCamera->getFrustum(), reinterpret_cast<std::vector<VolumeNode*>& >(mOccluders),
            NODE_GEOMETRY, 0, true, false);
        
        mOctree->getNodes(query);
        updateOccluders(mOccluders, *mCamera);
        
        if (mOccluders.size())
        {
            buffer = mPipeline->getOrCreateOcclusionBuffer(*mCamera, mMaxOccluderTriangles);
            
            drawOccluders(buffer, mOccluders);
            buffer->buildDepthHierarchy();
            useOcclusion = true;
        }
    }
    
    static std::vector<VolumeNode*> tempNodes;
    
    if (!useOcclusion)
    {
        // Get geometries & lights without occlusion
        FrustumOctreeQuery query(mCamera->getFrustum(), tempNodes, NODE_GEOMETRY | NODE_LIGHT);
        mOctree->getNodes(query);
    }
    else
    {
        // Get geometries & lights using occlusion
        OccludedFrustumOctreeQuery query(mCamera->getFrustum(), buffer, tempNodes, NODE_GEOMETRY | NODE_LIGHT);
        mOctree->getNodes(query);
    }
    
    // Sort into geometries & lights, and build visible scene bounding boxes in world and view space
    mSceneBox.mMin = mSceneBox.mMax = Vector3::sZero;
    mSceneBox.mDefined = false;
    mSceneViewBox.mMin = mSceneViewBox.mMax = Vector3::sZero;
    mSceneViewBox.mDefined = false;
    const Matrix4x3& view = mCamera->getInverseWorldTransform();
    unsigned cameraViewMask = mCamera->getViewMask();
    
    for (unsigned i = 0; i < tempNodes.size(); ++i)
    {
        VolumeNode* node = tempNodes[i];
        
        // Check view mask
        if (!(cameraViewMask & node->getViewMask()))
            continue;
        
        node->updateDistance(mFrame);
        
        // If draw distance non-zero, check it
        float maxDistance = node->getDrawDistance();
        if ((maxDistance != 0.0f) && (node->getDistance() > maxDistance))
            continue;
        
        unsigned flags = node->getNodeFlags();
        if (flags & NODE_GEOMETRY)
        {
            GeometryNode* geom = static_cast<GeometryNode*>(node);
            geom->markInView(mFrame);
            geom->updateGeometry(mFrame, renderer);
            
            // Expand the scene bounding boxes
            const BoundingBox& geomBox = geom->getWorldBoundingBox();
            BoundingBox geomViewBox = geomBox.getTransformed(view);
            mSceneBox.merge(geomBox);
            mSceneViewBox.merge(geomViewBox);
            
            // Store depth info to speed up split directional light queries
            GeometryDepthBounds bounds;
            bounds.mMin = geomViewBox.mMin.mZ;
            bounds.mMax = geomViewBox.mMax.mZ;
            
            mGeometryDepthBounds.push_back(bounds);
            mGeometries.push_back(geom);
        }
        else if (flags & NODE_LIGHT)
        {
            Light* light = static_cast<Light*>(node);
            
            // Skip if detail level does not include this light
            if (light->getDetailLevel() > mLightDetailLevel)
                continue;
            
            // Skip if light is culled by the zone
            if (!(light->getLightMask() & mZone->getLightMask()))
                continue;
            
            light->markInView(mFrame);
            mLights.push_back(light);
        }
    }
}

void View::clearLastParameterSources()
{
    VertexShader::clearLastParameterSources();
    PixelShader::clearLastParameterSources();
}

void View::updateOccluders(std::vector<GeometryNode*>& occluders, Camera& camera)
{
    float occluderSizeThreshold = mPipeline->getOccluderSizeThreshold();
    float halfViewSize = camera.getHalfViewSize();
    float invOrthoSize = 1.0f / camera.getOrthoSize();
    Vector3 cameraPos = camera.getWorldPosition();
    unsigned cameraViewMask = camera.getViewMask();
    
    for (unsigned i = 0; i < occluders.size(); ++i)
    {
        GeometryNode* node = occluders[i];
        node->updateDistance(mFrame);
        bool erase = false;
        
        // Check view mask
        if (!(cameraViewMask & node->getViewMask()))
            erase = true;
        
        // Check occluder's draw distance (in main camera view)
        float maxDistance = node->getDrawDistance();
        if ((maxDistance != 0.0f) && (node->getDistance() > maxDistance))
            erase = true;
        
        // Check that occluder is big enough on the screen
        const BoundingBox& box = node->getWorldBoundingBox();
        float diagonal = (box.mMax - box.mMin).getLengthFast();
        float compare;
        if (!camera.isOrthographic())
            compare = diagonal * halfViewSize / node->getDistance();
        else
            compare = diagonal * invOrthoSize;
        
        if (compare < occluderSizeThreshold)
            erase = true;
        
        if (!erase)
        {
            unsigned totalTriangles = 0;
            unsigned batches = node->getNumBatches();
            for (unsigned j = 0; j < batches; ++j)
            {
                Geometry* geom = node->getBatchGeometry(j);
                if (geom)
                    totalTriangles += geom->getIndexCount() / 3;
            }
            
            // Store squared distance from occlusion camera multiplied by amount of triangles as a sorting key
            // (best occluders are near and have few triangles)
            node->setSortValue((node->getWorldPosition() - cameraPos).getLengthSquared() * totalTriangles);
        }
        else
        {
            occluders.erase(occluders.begin() + i);
            --i;
        }
    }
    
    // Sort occluders so that if triangle budget is exceeded, best occluders have been drawn
    if (occluders.size())
        std::sort(occluders.begin(), occluders.end(), compareNodes);
}

void View::drawOccluders(OcclusionBuffer* buffer, const std::vector<GeometryNode*>& occluders)
{
    Renderer* renderer = mPipeline->getRenderer();
    
    for (unsigned i = 0; i < occluders.size(); ++i)
    {
        GeometryNode* node = occluders[i];
        if (!node->isOccluder())
            continue;
        
        if (i > 0)
        {
            // For subsequent occluders, do a test against the pixel-level occlusion buffer to see if rendering is necessary
            if (!buffer->isVisible(node->getWorldBoundingBox()))
                continue;
        }
        
        node->updateGeometry(mFrame, renderer);
        
        // Check for running out of triangles
        if (!node->drawOcclusion(buffer))
            return;
    }
}

unsigned View::processLight(Light* light)
{
    unsigned litGeometries = 0;
    unsigned shadowCasters = 0;
    
    unsigned splitLights;
    // Check if light detail level allows the light to be shadowed. Also negative lights are never shadowed
    bool isShadowed = (mDrawShadows) && (light->getCastShadows()) && (!light->isNegative()) && (light->getShadowDetailLevel() <= mLightDetailLevel);
    // If shadow distance non-zero, check it
    if ((isShadowed) && (light->getShadowDistance() > 0.0f) && (light->getDistance() > light->getShadowDistance()))
        isShadowed = false;
    
    // If light has no ramp textures defined, set defaults
    if (!light->getRampTexture())
        light->setRampTexture(mPipeline->getDefaultLightRamp());
    if (!light->getSpotTexture())
        light->setSpotTexture(mPipeline->getDefaultLightSpot());
    
    // Split the light if necessary
    if (isShadowed)
        splitLights = splitLight(light);
    else
    {
        // No splitting, use the original light
        sSplitLights[0] = light;
        splitLights = 1;
    }
    
    // For a shadowed directional light, get occluders once using the whole (non-split) light frustum
    bool useOcclusion = false;
    OcclusionBuffer* buffer = 0;
    
    if ((mMaxOccluderTriangles > 0) && (isShadowed) && (light->getLightType() == LIGHT_DIRECTIONAL))
    {
        // This shadow camera is never used for actually querying shadow casters, just occluders
        setupShadowCamera(light, true);
        Camera& shadowCamera = light->getShadowCamera();
        
        // Get occluders, which must be shadow-casting themselves
        FrustumOctreeQuery query(shadowCamera.getFrustum(), reinterpret_cast<std::vector<VolumeNode*>& >(mShadowOccluders),
            NODE_GEOMETRY, 0, true, true);
        mOctree->getNodes(query);
        
        updateOccluders(mShadowOccluders, shadowCamera);
        
        if (mShadowOccluders.size())
        {
            // Shadow viewport is rectangular and consumes more CPU fillrate, so halve size
            buffer = mPipeline->getOrCreateOcclusionBuffer(shadowCamera, mMaxOccluderTriangles, true);
            
            drawOccluders(buffer, mShadowOccluders);
            buffer->buildDepthHierarchy();
            useOcclusion = true;
        }
    }
    
    // Process each split for shadow camera update, lit geometries, and shadow casters
    for (unsigned i = 0; i < splitLights; ++i)
    {
        sLitGeometries[i].clear();
        sShadowCasters[i].clear();
    }
    
    for (unsigned i = 0; i < splitLights; ++i)
    {
        LightType type = sSplitLights[i]->getLightType();
        bool isSplitShadowed = (isShadowed) && (sSplitLights[i]->getCastShadows());
        
        // If shadow casting, choose the shadow map & update shadow camera
        if (isSplitShadowed)
        {
            sSplitLights[i]->setShadowMap(mPipeline->getShadowMap(sSplitLights[i]->getShadowResolution()));
            setupShadowCamera(sSplitLights[i]);
        }
        else
            sSplitLights[i]->setShadowMap(0);
        
        BoundingBox geometryBox;
        BoundingBox shadowCasterBox;
        
        static std::vector<VolumeNode*> tempLitNodes;
        
        switch (type)
        {
        case LIGHT_DIRECTIONAL:
            // Loop through visible geometries and check if they belong to this split
            {
                float nearSplit = sSplitLights[i]->getNearSplit() - sSplitLights[i]->getNearFadeRange();
                float farSplit = sSplitLights[i]->getFarSplit();
                // If split extends to the whole visible frustum, no depth check necessary
                bool optimize = (nearSplit <= mCamera->getNearClip()) && (farSplit >= mCamera->getFarClip());
                
                // If whole visible scene is outside the split, can reject trivially
                if ((mSceneViewBox.mMin.mZ > farSplit) || (mSceneViewBox.mMax.mZ < nearSplit))
                {
                    sSplitLights[i]->setShadowMap(0);
                    continue;
                }
                
                const Matrix4x3& lightView = sSplitLights[i]->getShadowCamera().getInverseWorldTransform();
                bool generateBoxes = (isSplitShadowed) && (sSplitLights[i]->getShadowFocus().mFocus);
                unsigned lightMask = sSplitLights[i]->getLightMask();
                
                if (!optimize)
                {
                    for (unsigned j = 0; j < mGeometries.size(); ++j)
                    {
                        const GeometryDepthBounds& bounds = mGeometryDepthBounds[j];
                        if ((bounds.mMin <= farSplit) && (bounds.mMax >= nearSplit) && (lightMask & mGeometries[j]->getLightMask()))
                        {
                            sLitGeometries[i].push_back(mGeometries[j]);
                            if (generateBoxes)
                                geometryBox.merge(mGeometries[j]->getWorldBoundingBox().getTransformed(lightView));
                        }
                    }
                }
                else
                {
                    for (unsigned j = 0; j < mGeometries.size(); ++j)
                    {
                        if (lightMask & mGeometries[j]->getLightMask())
                        {
                            sLitGeometries[i].push_back(mGeometries[j]);
                            if (generateBoxes)
                                geometryBox.merge(mGeometries[j]->getWorldBoundingBox().getTransformed(lightView));
                        }
                    }
                }
            }
            
            // Then get shadow casters by shadow camera frustum query. Use occlusion because of potentially many geometries
            if ((isSplitShadowed) && (sLitGeometries[i].size()))
            {
                Camera& shadowCamera = sSplitLights[i]->getShadowCamera();
                
                if (!useOcclusion)
                {
                    // Get potential shadow casters without occlusion
                    FrustumOctreeQuery query(shadowCamera.getFrustum(), tempLitNodes, NODE_GEOMETRY);
                    mOctree->getNodes(query);
                }
                else
                {
                    // Get potential shadow casters with occlusion
                    OccludedFrustumOctreeQuery query(shadowCamera.getFrustum(), buffer, tempLitNodes,
                        NODE_GEOMETRY);
                    mOctree->getNodes(query);
                }
                
                processLightQuery(i, tempLitNodes, false, isSplitShadowed, geometryBox, shadowCasterBox);
            }
            break;
            
        case LIGHT_POINT:
            {
                SphereOctreeQuery query(Sphere(sSplitLights[i]->getWorldPosition(), sSplitLights[i]->getRange()),
                    tempLitNodes, NODE_GEOMETRY);
                mOctree->getNodes(query);
                
                processLightQuery(i, tempLitNodes, true, false, geometryBox, shadowCasterBox);
            }
            break;
            
        case LIGHT_SPOT:
        case LIGHT_SPLITPOINT:
            {
                FrustumOctreeQuery query(sSplitLights[i]->getFrustum(), tempLitNodes, NODE_GEOMETRY);
                mOctree->getNodes(query);
                
                processLightQuery(i, tempLitNodes, true, isSplitShadowed, geometryBox, shadowCasterBox);
            }
            break;
        }
        
        // Optimization: if a particular split has no shadow casters, render as unshadowed
        if (!sShadowCasters[i].size())
            sSplitLights[i]->setShadowMap(0);
        
        // Focus shadow camera as applicable
        if (sSplitLights[i]->getShadowMap())
        {
            if (sSplitLights[i]->getShadowFocus().mFocus)
                focusShadowCamera(sSplitLights[i], geometryBox, shadowCasterBox);
            
            // Set a zoom factor to ensure that we do not render to the shadow map border
            // (clamp addressing is necessary because border mode /w hardware shadow maps is not supported by all GPUs)
            Camera& shadowCamera = sSplitLights[i]->getShadowCamera();
            Texture2D* shadowMap = sSplitLights[i]->getShadowMap();
            if (shadowCamera.getZoom() >= 1.0f)
                shadowCamera.setZoom(shadowCamera.getZoom() * ((float)(shadowMap->getWidth() - 2) / (float)shadowMap->getWidth()));
        }
        
        // Update count of total lit geometries & shadow casters
        litGeometries += sLitGeometries[i].size();
        shadowCasters += sShadowCasters[i].size();
    }
    
    // If no lit geometries at all, no need to process further
    if (!litGeometries)
        splitLights = 0;
    // If no shadow casters at all, concatenate lit geometries into one & return the original light
    else if (!shadowCasters)
    {
        if (splitLights > 1)
        {
            // Make sure there are no duplicates
            static std::set<GeometryNode*> allLitGeometries;
            allLitGeometries.clear();
            for (unsigned i = 0; i < splitLights; ++i)
            {
                for (std::vector<GeometryNode*>::iterator j = sLitGeometries[i].begin(); j != sLitGeometries[i].end(); ++j)
                    allLitGeometries.insert(*j);
            }
            
            sLitGeometries[0].resize(allLitGeometries.size());
            unsigned index = 0;
            for (std::set<GeometryNode*>::iterator i = allLitGeometries.begin(); i != allLitGeometries.end(); ++i)
                sLitGeometries[0][index++] = *i;
        }
        
        sSplitLights[0] = light;
        sSplitLights[0]->setShadowMap(0);
        splitLights = 1;
    }
    
    return splitLights;
}

void View::processLightQuery(unsigned index, const std::vector<VolumeNode*>& result,
    bool getLitGeometries, bool getShadowCasters, BoundingBox& geometryBox, BoundingBox& shadowCasterBox)
{
    Renderer* renderer = mPipeline->getRenderer();
    
    // Transform scene frustum into shadow camera's view space for shadow caster visibility check
    Camera& shadowCamera = sSplitLights[index]->getShadowCamera();
    const Matrix4x3& lightView = shadowCamera.getInverseWorldTransform();
    const Matrix4& lightProj = shadowCamera.getProjection();
    
    // For point & spot lights, we can use the whole scene frustum. For directional lights, use the
    // intersection of the scene frustum and the split frustum, so that shadow casters do not get
    // rendered into unnecessary splits
    Frustum lightViewFrustum;
    if (sSplitLights[index]->getLightType() != LIGHT_DIRECTIONAL)
    {
        lightViewFrustum = mCamera->getSplitFrustum(
            mSceneViewBox.mMin.mZ, mSceneViewBox.mMax.mZ).getTransformed(lightView);
    }
    else
    {
        lightViewFrustum = mCamera->getSplitFrustum(
            max(mSceneViewBox.mMin.mZ, sSplitLights[index]->getNearSplit() - sSplitLights[index]->getNearFadeRange()),
            min(mSceneViewBox.mMax.mZ, sSplitLights[index]->getFarSplit())
        ).getTransformed(lightView);
    }
    BoundingBox lightViewFrustumBox;
    lightViewFrustumBox.define(lightViewFrustum);
    
    // Check for degenerate split frustum: in that case there is no need to get shadow casters
    if (lightViewFrustum.mVertices[0] == lightViewFrustum.mVertices[4])
        getShadowCasters = false;
    
    // Generate merged light view geometry/shadowcaster bounding boxes box for shadow focusing
    bool mergeBoxes = (sSplitLights[index]->getLightType() != LIGHT_SPLITPOINT) && (sSplitLights[index]->getShadowMap()) &&
        (sSplitLights[index]->getShadowFocus().mFocus);
    bool projectBoxes = !shadowCamera.isOrthographic();
    
    BoundingBox lightViewBox;
    BoundingBox lightProjBox;
    unsigned lightMask = sSplitLights[index]->getLightMask();
    
    for (unsigned i = 0; i < result.size(); ++i)
    {
        GeometryNode* geom = static_cast<GeometryNode*>(result[i]);
        geom->updateDistance(mFrame);
        bool boxGenerated = false;
        
        // If draw distance non-zero, check it
        float maxDistance = geom->getDrawDistance();
        if ((maxDistance != 0.0f) && (geom->getDistance() > maxDistance))
            continue;
        
        // Check light mask
        if (!(lightMask & geom->getLightMask()))
            continue;
        
        // Get lit geometry only if inside main camera frustum this frame
        if (getLitGeometries)
        {
            if (geom->isInView(mFrame))
            {
                if (mergeBoxes)
                {
                    // Transform bounding box into light view space, and to projection space if needed
                    lightViewBox = geom->getWorldBoundingBox().getTransformed(lightView);
                    
                    if (!projectBoxes)
                        geometryBox.merge(lightViewBox);
                    else
                    {
                        lightProjBox = lightViewBox.getProjected(lightProj);
                        geometryBox.merge(lightProjBox);
                    }
                    
                    boxGenerated = true;
                }
                
                sLitGeometries[index].push_back(geom);
            }
        }
        
        // Shadow caster need not be inside main camera frustum: in that case we try to detect whether
        // the shadow projection intersects the view
        if ((getShadowCasters) && (geom->getCastShadows()))
        {
            // If shadow distance non-zero, check it
            float maxShadowDistance = geom->getShadowDistance();
            if ((maxShadowDistance != 0.0f) && (geom->getDistance() > maxShadowDistance))
                continue;
            
            // Check if any of the geometry's materials casts shadows
            unsigned numMat = geom->getNumBatches();
            for (unsigned i = 0; i < numMat; ++i)
            {
                Material* material = geom->getBatchMaterial(i);
                // Note: if material is null, default will be used, and it casts shadows
                if ((!material) || (material->getCastShadows()))
                {
                    if (!boxGenerated)
                        lightViewBox = geom->getWorldBoundingBox().getTransformed(lightView);
                    
                    if (isShadowCasterVisible(geom, lightViewBox, shadowCamera, lightView, lightViewFrustum, lightViewFrustumBox))
                    {
                        if (mergeBoxes)
                        {
                            if (!projectBoxes)
                                shadowCasterBox.merge(lightViewBox);
                            else
                            {
                                if (!boxGenerated)
                                    lightProjBox = lightViewBox.getProjected(lightProj);
                                shadowCasterBox.merge(lightProjBox);
                            }
                        }
                        
                        // Update geometry now if not updated yet
                        if (!geom->isInView(mFrame))
                            geom->updateGeometry(mFrame, renderer);
                        sShadowCasters[index].push_back(geom);
                    }
                    break;
                }
            }
        }
    }
}

bool View::isShadowCasterVisible(GeometryNode* geom, BoundingBox lightViewBox, const Camera& shadowCamera,
    const Matrix4x3& lightView, const Frustum& lightViewFrustum, const BoundingBox& lightViewFrustumBox)
{
    // If shadow caster is also an occluder, must let it be visible, because it has potentially already culled
    // away other shadow casters (could also check the actual shadow occluder vector, but that would be slower)
    if (geom->isOccluder())
        return true;
    
    if (shadowCamera.isOrthographic())
    {
        // Extrude the light space bounding box up to the far edge of the frustum's light space bounding box
        lightViewBox.mMax.mZ = max(lightViewBox.mMax.mZ,lightViewFrustumBox.mMax.mZ);
        return lightViewFrustum.isInsideFast(lightViewBox) != OUTSIDE;
    }
    else
    {
        // If light is not directional, can do a simple check: if object is visible, its shadow is too
        if (geom->isInView(mFrame))
            return true;
        
        // For perspective lights, extrusion direction depends on the position of the shadow caster
        Vector3 center = lightViewBox.getCenter();
        Ray extrusionRay(center, center.getNormalized());
        
        float extrusionDistance = shadowCamera.getFarClip();
        float originalDistance = clamp(center.getLengthFast(), M_EPSILON, extrusionDistance);
        
        // Because of the perspective, the bounding box must also grow when it is extruded to the distance
        float sizeFactor = extrusionDistance / originalDistance;
        
        // Calculate the endpoint box and merge it to the original. Because it's axis-aligned, it will be larger
        // than necessary, so the test will be conservative
        Vector3 newCenter = extrusionDistance * extrusionRay.mDirection;
        Vector3 newHalfSize = lightViewBox.getSize() * sizeFactor * 0.5f;
        BoundingBox extrudedBox(newCenter - newHalfSize, newCenter + newHalfSize);
        lightViewBox.merge(extrudedBox);
        
        return lightViewFrustum.isInsideFast(lightViewBox) != OUTSIDE;
    }
}

void View::setupShadowCamera(Light* light, bool shadowOcclusion)
{
    Camera& shadowCamera = light->getShadowCamera();
    const FocusParameters& parameters = light->getShadowFocus();
    
    // Reset zoom
    shadowCamera.setZoom(1.0f);
    
    switch(light->getLightType())
    {
    case LIGHT_DIRECTIONAL:
        {
            float extrusionDistance = mCamera->getFarClip();
            
            // Calculate initial position & rotation
            Vector3 lightWorldDirection = light->getWorldRotation() * light->getDirection();
            Vector3 pos = mCamera->getWorldPosition() - extrusionDistance * lightWorldDirection;
            Quaternion rot(Vector3::sForward, lightWorldDirection);
            shadowCamera.setPosition(pos);
            shadowCamera.setRotation(rot);
            
            // Calculate main camera shadowed frustum in light's view space
            float sceneMaxZ = mCamera->getFarClip();
            // When shadow focusing is enabled, use the scene far Z to limit maximum frustum size
            if ((shadowOcclusion) || (parameters.mFocus))
                sceneMaxZ = min(mSceneViewBox.mMax.mZ, sceneMaxZ);
            
            const Matrix4x3& lightView = shadowCamera.getInverseWorldTransform();
            Frustum lightViewSplitFrustum = mCamera->getSplitFrustum(light->getNearSplit() - light->getNearFadeRange(),
                min(light->getFarSplit(), sceneMaxZ)).getTransformed(lightView);
            
            // Fit the frustum inside a bounding box. If uniform size, use a sphere instead
            BoundingBox shadowBox;
            if ((!shadowOcclusion) && (parameters.mNonUniform))
                shadowBox.define(lightViewSplitFrustum);
            else
            {
                Sphere shadowSphere;
                shadowSphere.define(lightViewSplitFrustum);
                shadowBox.define(shadowSphere);
            }
            
            shadowCamera.setOrthographic(true);
            shadowCamera.setNearClip(0.0f);
            shadowCamera.setFarClip(shadowBox.mMax.mZ);
            
            // Center shadow camera on the bounding box, snap to whole texels
            quantizeDirShadowCamera(light, shadowBox);
        }
        break;
        
    case LIGHT_SPOT:
    case LIGHT_SPLITPOINT:
        {
            Quaternion rotation(Vector3(0.0f, 0.0f, 1.0f), light->getDirection());
            shadowCamera.setPosition(light->getWorldPosition());
            shadowCamera.setRotation(light->getWorldRotation() * rotation);
            
            shadowCamera.setNearClip(light->getShadowNearFarRatio() * light->getRange());
            shadowCamera.setFarClip(light->getRange());
            shadowCamera.setOrthographic(false);
            shadowCamera.setFov(light->getFov());
            shadowCamera.setAspectRatio(light->getAspectRatio());
            
            // For spot lights, zoom out shadowmap if far away (reduces fillrate)
            if ((light->getLightType() == LIGHT_SPOT) && (parameters.mZoomOut))
            {
                // Make sure the out-zooming does not start while we are inside the spot
                float distance = max((mCamera->getInverseWorldTransform() * light->getWorldPosition()).mZ - light->getRange(), 1.0f);
                float lightPixels = (((float)mHeight * light->getRange() * mCamera->getZoom() * 0.5f) / distance);
                
                // Clamp pixel amount to a sufficient minimum to avoid self-shadowing artifacts due to loss of precision
                if (lightPixels < SHADOW_MIN_PIXELS)
                    lightPixels = SHADOW_MIN_PIXELS;
                
                float zoomLevel = min(lightPixels / (float)light->getShadowMap()->getHeight(), 1.0f);
                
                shadowCamera.setZoom(zoomLevel);
            }
        }
        break;
    }
}

void View::focusShadowCamera(Light* light, const BoundingBox& geometryBox, const BoundingBox& shadowCasterBox)
{
    // If either no geometries or no shadow casters, do nothing
    if ((!geometryBox.mDefined) || (!shadowCasterBox.mDefined))
        return;
    
    Camera& shadowCamera = light->getShadowCamera();
    const FocusParameters& parameters = light->getShadowFocus();
    
    switch (light->getLightType())
    {
    case LIGHT_DIRECTIONAL:
        {
            BoundingBox combinedBox;
            combinedBox.mMax.mY = shadowCamera.getOrthoSize() * 0.5f;
            combinedBox.mMax.mX = shadowCamera.getAspectRatio() * combinedBox.mMax.mY;
            combinedBox.mMin.mY = -combinedBox.mMax.mY;
            combinedBox.mMin.mX = -combinedBox.mMax.mX;
            combinedBox.intersect(geometryBox);
            combinedBox.intersect(shadowCasterBox);
            quantizeDirShadowCamera(light, combinedBox);
        }
        break;
        
    case LIGHT_SPOT:
        // Can not move, but can zoom the shadow camera. Check for out-zooming (distant shadow map), do nothing in that case
        if (shadowCamera.getZoom() >= 1.0f)
        {
            BoundingBox combinedBox(-1.0f, 1.0f);
            combinedBox.intersect(geometryBox);
            combinedBox.intersect(shadowCasterBox);
            
            float viewSizeX = max(fabsf(combinedBox.mMin.mX), fabsf(combinedBox.mMax.mX));
            float viewSizeY = max(fabsf(combinedBox.mMin.mY), fabsf(combinedBox.mMax.mY));
            float viewSize = max(viewSizeX, viewSizeY);
            // Scale the quantization parameters, because view size is in projection space (-1.0 - 1.0)
            float invOrthoSize = 1.0f / shadowCamera.getOrthoSize();
            float quantize = parameters.mQuantize * invOrthoSize;
            float minView = parameters.mMinView * invOrthoSize;
            viewSize = max(ceilf(viewSize / quantize) * quantize, minView);
            
            if (viewSize < 1.0f)
                shadowCamera.setZoom(1.0f / viewSize);
        }
        break;
    }
}

void View::quantizeDirShadowCamera(Light* light, const BoundingBox& viewBox)
{
    Camera& shadowCamera = light->getShadowCamera();
    const FocusParameters& parameters = light->getShadowFocus();
    
    float minX = viewBox.mMin.mX;
    float minY = viewBox.mMin.mY;
    float maxX = viewBox.mMax.mX;
    float maxY = viewBox.mMax.mY;
    
    Vector2 center((minX + maxX) * 0.5f, (minY + maxY) * 0.5f);
    Vector2 viewSize(maxX - minX, maxY - minY);
    
    // Quantize size to reduce swimming
    // Note: if size is uniform and there is no focusing, quantization is unnecessary
    if (parameters.mNonUniform)
    {
        viewSize.mX = ceilf(sqrtf(viewSize.mX / parameters.mQuantize));
        viewSize.mY = ceilf(sqrtf(viewSize.mY / parameters.mQuantize));
        viewSize.mX = max(viewSize.mX * viewSize.mX * parameters.mQuantize, parameters.mMinView);
        viewSize.mY = max(viewSize.mY * viewSize.mY * parameters.mQuantize, parameters.mMinView);
    }
    else if (parameters.mFocus)
    {
        viewSize.mX = max(viewSize.mX, viewSize.mY);
        viewSize.mX = ceilf(sqrtf(viewSize.mX / parameters.mQuantize));
        viewSize.mX = max(viewSize.mX * viewSize.mX * parameters.mQuantize, parameters.mMinView);
        viewSize.mY = viewSize.mX;
    }
    
    shadowCamera.setOrthoSize(viewSize);
    
    // Center shadow camera to the view space bounding box
    const Quaternion& rot = shadowCamera.getRotation();
    Vector3 adjust(center.mX, center.mY, 0.0f);
    shadowCamera.translate(rot * adjust);
    
    // If there is a shadow map, snap to its whole texels
    Texture2D* shadowMap = light->getShadowMap();
    if (shadowMap)
    {
        Vector3 viewPos(rot.getInverse() * shadowCamera.getPosition());
        // Take into account that shadow map border will not be used
        float invActualSize = 1.0f / (float)(shadowMap->getWidth() - 2);
        Vector2 texelSize(viewSize.mX * invActualSize, viewSize.mY * invActualSize);
        Vector3 snap(-fmodf(viewPos.mX, texelSize.mX), -fmodf(viewPos.mY, texelSize.mY), 0.0f);
        shadowCamera.translate(rot * snap);
    }
}

void View::optimizeLightByScissor(Light* light)
{
    Renderer* renderer = mPipeline->getRenderer();
    
    if (light)
        renderer->setScissorTest(true, getLightScissor(light));
    else
        renderer->setScissorTest(false);
}

const Rect& View::getLightScissor(Light* light)
{
    std::map<Light*, Rect>::iterator i = mLightScissorCache.find(light);
    if (i != mLightScissorCache.end())
        return i->second;
    
    const Matrix4x3& view = mCamera->getInverseWorldTransform();
    const Matrix4& projection = mCamera->getProjection();
    
    switch (light->getLightType())
    {
    case LIGHT_POINT:
        {
            BoundingBox viewBox = light->getWorldBoundingBox().getTransformed(view);
            return mLightScissorCache[light] = viewBox.getProjected(projection);
        }
        
    case LIGHT_SPOT:
    case LIGHT_SPLITPOINT:
        {
            Frustum viewFrustum = light->getFrustum().getTransformed(view);
            return mLightScissorCache[light] = viewFrustum.getProjected(projection);
        }
        
    default:
        return mLightScissorCache[light] = Rect::sFullRect;
    }
}

unsigned View::splitLight(Light* light)
{
    LightType type = light->getLightType();
    
    if (type == LIGHT_DIRECTIONAL)
    {
        const CascadeParameters& cascade = light->getShadowCascade();
        
        unsigned splits = cascade.mSplits;
        if (splits > MAX_LIGHT_SPLITS - 1)
            splits = MAX_LIGHT_SPLITS;
        
        // Orthographic view actually has near clip 0, but clamp it to a theoretical minimum
        float farClip = cascade.mShadowRange; // Shadow range end
        float nearClip = max(mCamera->getNearClip(), M_MIN_NEARCLIP); // Shadow range start
        bool createExtraSplit = farClip < mCamera->getFarClip();
        
        // Practical split scheme (Zhang et al.)
        unsigned i;
        for (i = 0; i < splits; ++i)
        {
            // Set a minimum for the fade range to avoid boundary artifacts (missing lighting)
            float splitFadeRange = max(cascade.mSplitFadeRange, 0.001f);
            
            float iPerM = (float)i / (float)splits;
            float log = nearClip * powf(farClip / nearClip, iPerM);
            float uniform = nearClip + (farClip - nearClip) * iPerM;
            float nearSplit = log * cascade.mLambda + uniform * (1.0f - cascade.mLambda);
            float nearFadeRange = nearSplit * splitFadeRange;
            
            iPerM = (float)(i + 1) / (float)splits;
            log = nearClip * powf(farClip / nearClip, iPerM);
            uniform = nearClip + (farClip - nearClip) * iPerM;
            float farSplit = log * cascade.mLambda + uniform * (1.0f - cascade.mLambda);
            float farFadeRange = farSplit * splitFadeRange;
            
            // If split is completely beyond camera far clip, we are done
            if ((nearSplit - nearFadeRange) > mCamera->getFarClip())
                break;
            
            Light* splitLight = mPipeline->createSplitLight(light);
            sSplitLights[i] = splitLight;
            
            // Though the near clip was previously clamped, use the real near clip value for the first split,
            // so that there are no unlit portions
            if (i)
                splitLight->setNearSplit(nearSplit);
            else
                splitLight->setNearSplit(mCamera->getNearClip());
            
            splitLight->setNearFadeRange(nearFadeRange);
            splitLight->setFarSplit(farSplit);
            
            // The final split will not fade
            if ((createExtraSplit) || (i < splits - 1))
                splitLight->setFarFadeRange(farFadeRange);
            
            // Create an extra unshadowed split if necessary
            if ((createExtraSplit) && (i == splits - 1))
            {
                Light* splitLight = mPipeline->createSplitLight(light);
                sSplitLights[i + 1] = splitLight;
                
                splitLight->setNearSplit(farSplit);
                splitLight->setNearFadeRange(farFadeRange);
                splitLight->setCastShadows(false);
            }
        }
        
        if (createExtraSplit)
            return i + 1;
        else
            return i;
    }
    
    if (type == LIGHT_POINT)
    {
        static const Vector3 directions[] = 
        {
            Vector3::sRight,
            Vector3::sLeft,
            Vector3::sUp,
            Vector3::sDown,
            Vector3::sForward,
            Vector3::sBack,
        };
        
        for (unsigned i = 0; i < MAX_CUBEMAP_FACES; ++i)
        {
            Light* splitLight = mPipeline->createSplitLight(light);
            sSplitLights[i] = splitLight;
            
            splitLight->setLightType(LIGHT_SPLITPOINT);
            splitLight->setRotation(Quaternion::sIdentity);
            splitLight->setDirection(directions[i]);
            splitLight->setFov(90.0f);
            splitLight->setAspectRatio(1.0f);
        }
        
        return MAX_CUBEMAP_FACES;
    }
    
    // A spot light does not actually need splitting. However, we may be rendering several views,
    // and in some the light might be unshadowed, so better create an unique copy
    Light* splitLight = mPipeline->createSplitLight(light);
    sSplitLights[0] = splitLight;
    return 1;
}

MaterialTechnique* View::getMaterialTechnique(GeometryNode* node, unsigned index)
{
    Material* mat = node->getBatchMaterial(index);
    if (!mat)
        mat = mPipeline->getDefaultMaterial();
    if (!mat)
        return 0;
    
    float lodDistance = node->getLodDistance();
    unsigned numTechniques = mat->getNumTechniques();
    
    // Check for suitable technique. Techniques should be ordered like this:
    // Most distant & highest quality
    // Most distant & lowest quality
    // Second most distant & highest quality
    // ...
    for (unsigned i = 0; i < numTechniques; ++i)
    {
        MaterialTechnique* technique = mat->getTechnique(i);
        if (((!mSM3Support) && (technique->getRequireSM3())) || (mMaterialQuality < technique->getQualityLevel()))
            continue;
        if (lodDistance >= technique->getLodDistance())
            return technique;
    }
    
    // If no suitable technique found, fallback to the last
    return mat->getTechnique(numTechniques - 1);
}

void View::checkTechniqueForAuxView(MaterialTechnique* technique)
{
    const std::vector<SharedPtr<Texture> >& textures = technique->getTextures();
    
    for (unsigned i = 0; i < textures.size(); ++i)
    {
        // Have to check cube & 2D textures separately
        Texture* texture = textures[i];
        if (texture)
        {
            if (texture->getType() == Texture2D::getTypeStatic())
            {
                Texture2D* tex2D = static_cast<Texture2D*>(texture);
                RenderSurface* target = tex2D->getRenderSurface();
                if (target)
                {
                    // Add the view only if it has not been added already
                    Camera* camera = target->getCamera();
                    if ((camera) && (!camera->isInView(mFrame.mFrameNumber)))
                        mPipeline->addView(mOctree, camera, target);
                }
            }
            else if (texture->getType() == TextureCube::getTypeStatic())
            {
                TextureCube* texCube = static_cast<TextureCube*>(texture);
                for (unsigned j = 0; j < MAX_CUBEMAP_FACES; ++j)
                {
                    RenderSurface* target = texCube->getRenderSurface((CubeMapFace)j);
                    if (target)
                    {
                        // Add the view only if it has not been added already
                        Camera* camera = target->getCamera();
                        if ((camera) && (!camera->isInView(mFrame.mFrameNumber)))
                            mPipeline->addView(mOctree, camera, target);
                    }
                }
            }
        }
    }
    
    // Set frame number so that we can early-out next time we come across this technique on the same frame
    technique->markForAuxView(mFrame.mFrameNumber);
}

void View::sortBatches(std::vector<Batch>& originalBatches, std::vector<Batch*>& sortedBatches)
{
    sortedBatches.resize(originalBatches.size());
    for (unsigned i = 0; i < originalBatches.size(); ++i)
        sortedBatches[i] = &originalBatches[i];
    std::sort(sortedBatches.begin(), sortedBatches.end(), compareBatches);
}

