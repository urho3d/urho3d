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
#include "Geometry.h"
#include "GeometryNode.h"
#include "Light.h"
#include "Log.h"
#include "Material.h"
#include "Pipeline.h"
#include "PixelShader.h"
#include "Profiler.h"
#include "Renderer.h"
#include "RendererImpl.h"
#include "Texture2D.h"
#include "VertexShader.h"
#include "View.h"

#include "DebugNew.h"

static const std::string hwDepthVariations[] =
{
    "",
    "HW"
};

static const std::string linearVariations[] =
{
    "",
    "Linear"
};

void View::getBatchesDeferred()
{
    Renderer* renderer = mPipeline->getRenderer();
    bool deferred = renderer->getRenderMode() == RENDER_DEFERRED;
    
    // G-Buffer pass types depend on whether deferred shading or light prepass is in use
    PassType gBufferPass, additionalPass;
    if (deferred)
    {
        gBufferPass = PASS_DEFERRED;
        additionalPass = PASS_EMISSIVE;
    }
    else
    {
        gBufferPass = PASS_PREPASS;
        additionalPass = PASS_MATERIAL;
    }
    
    // Go through geometries for GBuffer and ambient batches
    {
        PROFILE(View_GetAmbientBatches);
        for (unsigned i = 0; i < mGeometries.size(); ++i)
        {
            GeometryNode* node = mGeometries[i];
            unsigned numBatches = node->getNumBatches();
        
            for (unsigned j = 0; j < numBatches; ++j)
            {
                Geometry* geom = node->getBatchGeometry(j);
                if (!geom)
                    continue;
                MaterialTechnique* tech = getMaterialTechnique(node, j);
                if (!tech)
                    continue;
                
                // Check here if the material technique refers to a render target texture with camera(s) attached
                // Only check this for the main view (null rendertarget)
                if ((!mRenderTarget) && (tech->getAuxViewFrameNumber() != mFrame.mFrameNumber))
                    checkTechniqueForAuxView(tech);
                
                Batch newBatch;
                newBatch.mNode = node;
                newBatch.mCamera = mCamera;
                newBatch.mDistance = node->getDistance();
                newBatch.mGeometry = geom;
                newBatch.mBatchIndex = j;
                
                // GBuffer pass has priority over ambient pass
                MaterialPass* pass = tech->getPass(gBufferPass);
                if (pass)
                {
                    // Render opaque objects without alpha masking first
                    newBatch.mHasPriority = !(pass->getAlphaMask() || pass->getAlphaTest());
                    mPipeline->setBatchShaders(newBatch, tech, pass);
                    newBatch.calculateSortKey(true, true);
                    mGBufferQueue.push_back(newBatch);
                    
                    // Check for additional emissive pass with deferred rendering, and material pass with light prepass
                    pass = tech->getPass(additionalPass);
                    if (pass)
                    {
                        newBatch.mHasPriority = false;
                        mPipeline->setBatchShaders(newBatch, tech, pass);
                        newBatch.calculateSortKey(true, true);
                        mForwardQueue.push_back(newBatch);
                    }
                }
                else
                {
                    pass = tech->getPass(PASS_AMBIENT);
                    
                    if (pass)
                    {
                        mPipeline->setBatchShaders(newBatch, tech, pass);
                        if (pass->getBlendMode() == BLEND_REPLACE)
                        {
                            newBatch.mHasPriority = !(pass->getAlphaTest() || pass->getAlphaMask());
                            newBatch.calculateSortKey(true, true);
                            mAmbientQueue.push_back(newBatch);
                        }
                        else
                        {
                            newBatch.mHasPriority = true;
                            newBatch.calculateSortKey(false, false);
                            mTransparentQueue.push_back(newBatch);
                        }
                    }
                    else
                    {
                        // If no other pass yet, check for post-opaque (custom) pass
                        pass = tech->getPass(PASS_POSTOPAQUE);
                        if (pass)
                        {
                            newBatch.mHasPriority = false;
                            mPipeline->setBatchShaders(newBatch, tech, pass);
                            newBatch.calculateSortKey(true, true);
                            mPostOpaqueQueue.push_back(newBatch);
                        }
                    }
                }
            }
        }
    }
    
    // Go through lights
    {
        PROFILE_MULTIPLE(Pipeline_GetLightBatches, mLights.size());
        
        unsigned lightQueueCount = 0;
        for (unsigned i = 0; i < mLights.size(); ++i)
        {
            Light* light = mLights[i];
            unsigned splits = processLight(light);
            
            if (!splits)
                continue;
            
            // For split point lights, check that a transparent object is not lit multiple times
            bool splitPointLight = sSplitLights[0]->getLightType() == LIGHT_SPLITPOINT;
            static std::set<GeometryNode*> litTransparencies;
            litTransparencies.clear();
            
            // Negative (darkening) lighting flag
            bool negative = mLights[i]->isNegative();
            
            // Prepare lit object + shadow caster queues for each split
            if (mLightQueues.size() < lightQueueCount + splits)
                mLightQueues.resize(lightQueueCount + splits);
            unsigned prevLightQueueCount = lightQueueCount;
            
            for (unsigned j = 0; j < splits; ++j)
            {
                LightBatchQueue& lightQueue = mLightQueues[lightQueueCount];
                lightQueue.mLight = sSplitLights[j];
                lightQueue.mShadowBatches.clear();
                lightQueue.mBatches.clear();
                lightQueue.mLastSplit = false;
                
                // Loop through shadow casters
                Camera& shadowCamera = sSplitLights[j]->getShadowCamera();
                for (unsigned k = 0; k < sShadowCasters[j].size(); ++k)
                {
                    GeometryNode* node = sShadowCasters[j][k];
                    unsigned numBatches = node->getNumBatches();
                    
                    for (unsigned l = 0; l < numBatches; ++l)
                    {
                        MaterialTechnique* tech = getMaterialTechnique(node, l);
                        if (!tech)
                            continue;
                        MaterialPass* pass = tech->getPass(PASS_SHADOW);
                        // Skip if material has no shadow pass
                        if (!pass)
                            continue;
                        Geometry* geom = node->getBatchGeometry(l);
                        if (!geom)
                            continue;
                        
                        // Build the shadow batch
                        // Note: shadow cameras are never parented, so can simply use getPosition()
                        Batch shadowBatch;
                        shadowBatch.mNode = node;
                        shadowBatch.mCamera = &shadowCamera;
                        shadowBatch.mDistance = (node->getWorldPosition() - shadowCamera.getPosition()).getLengthFast();
                        shadowBatch.mGeometry = geom;
                        shadowBatch.mBatchIndex = l;
                        shadowBatch.mForwardLight = sSplitLights[j];
                        shadowBatch.mHasPriority = !(pass->getAlphaTest() || pass->getAlphaMask());
                        
                        mPipeline->setBatchShaders(shadowBatch, tech, pass);
                        shadowBatch.calculateSortKey(true, true);
                        lightQueue.mShadowBatches.push_back(shadowBatch);
                    }
                }
                
                // Loop through lit geometries to get forward lit objects
                for (unsigned k = 0; k < sLitGeometries[j].size(); ++k)
                {
                    GeometryNode* node = sLitGeometries[j][k];
                    unsigned numBatches = node->getNumBatches();
                    
                    for (unsigned l = 0; l < numBatches; ++l)
                    {
                        MaterialTechnique* tech = getMaterialTechnique(node, l);
                        if (!tech)
                            continue;
                        
                        // Skip if material uses deferred rendering
                        if (tech->hasPass(gBufferPass))
                            continue;
                        
                        MaterialPass* pass;
                        if (!negative)
                            pass = tech->getPass(PASS_LIGHT);
                        else
                            pass = tech->getPass(PASS_NEGATIVE);
                        // Skip if material does not receive light
                        if (!pass)
                            continue;
                        
                        Geometry* geom = node->getBatchGeometry(l);
                        if (!geom)
                            continue;
                        
                        // Build the lit batch
                        Batch newBatch;
                        newBatch.mNode = node;
                        newBatch.mCamera = mCamera;
                        newBatch.mDistance = node->getDistance();
                        newBatch.mGeometry = geom;
                        newBatch.mBatchIndex = l;
                        newBatch.mForwardLight = sSplitLights[j];
                        
                        // No shadows in any forward lighting
                        mPipeline->setBatchShaders(newBatch, tech, pass, false);
                        
                        // Check from the ambient pass whether the object is opaque
                        MaterialPass* ambientPass = tech->getPass(PASS_AMBIENT);
                        if ((!ambientPass) || (ambientPass->getBlendMode() == BLEND_REPLACE))
                        {
                            // Render negative lights first in the forward lighting queue
                            newBatch.mHasPriority = negative;
                            newBatch.calculateSortKey(true, true);
                            mForwardQueue.push_back(newBatch);
                        }
                        else
                        {
                            // Prevent multi-lighting by a split point light
                            // (transparent rendering can not handle the needed stencil masking)
                            if (splitPointLight)
                            {
                                if (litTransparencies.find(node) != litTransparencies.end())
                                    continue;
                                // Use the original light instead of the split one, to choose correct scissor
                                newBatch.mForwardLight = mLights[i];
                            }
                            
                            // If light is negative, bias the distance slightly to ensure it has priority
                            if (negative)
                                newBatch.mDistance -= 0.001f;
                            
                            newBatch.calculateSortKey(false, false);
                            mTransparentQueue.push_back(newBatch);
                        }
                    }
                    
                    if (splitPointLight)
                        litTransparencies.insert(node);
                }
                
                // Build the light volume batch
                // Check amount of lit geometries
                if (sLitGeometries[j].size())
                {
                    Batch lightBatch;
                    lightBatch.mNode = sSplitLights[j];
                    lightBatch.mCamera = mCamera;
                    lightBatch.mDistance = sSplitLights[j]->getDistance();
                    lightBatch.mGeometry = mPipeline->getLightGeometry(sSplitLights[j]);
                    
                    mPipeline->setLightVolumeShaders(lightBatch);
                    lightBatch.calculateSortKey(true, true);
                    
                    // If light is a split point light, it must be treated as shadowed in any case for correct stencil clearing
                    if ((sSplitLights[j]->getShadowMap()) || (sSplitLights[j]->getLightType() == LIGHT_SPLITPOINT))
                    {
                        lightQueue.mBatches.push_back(lightBatch);
                        lightQueueCount++;
                    }
                    else
                    {
                        if (!negative)
                            mNoShadowLightQueue.push_back(lightBatch);
                        else
                            mNegativeLightQueue.push_back(lightBatch);
                    }
                }
            }
            
            // Mark the last split
            if (lightQueueCount != prevLightQueueCount)
                mLightQueues[lightQueueCount - 1].mLastSplit = true;
        }
        
        // Resize the shadowed light queue vector now that final size is known
        mLightQueues.resize(lightQueueCount);
    }
    
    // Finally sort the batches
    {
        PROFILE(View_SortBatches);
        
        sortBatches(mGBufferQueue, mGBufferQueueSorted);
        sortBatches(mNegativeLightQueue, mNegativeLightQueueSorted);
        sortBatches(mNoShadowLightQueue, mNoShadowLightQueueSorted);
        sortBatches(mAmbientQueue, mAmbientQueueSorted);
        sortBatches(mForwardQueue, mForwardQueueSorted);
        sortBatches(mPostOpaqueQueue, mPostOpaqueQueueSorted);
        sortBatches(mTransparentQueue, mTransparentQueueSorted);
        
        for (unsigned i = 0; i < mLightQueues.size(); ++i)
            sortBatches(mLightQueues[i].mShadowBatches, mLightQueues[i].mSortedShadowBatches);
    }
}

void View::renderBatchesDeferred()
{
    Renderer* renderer = mPipeline->getRenderer();
    bool deferred = renderer->getRenderMode() == RENDER_DEFERRED;
    
    Texture2D* diffBuffer = renderer->getDiffBuffer();
    Texture2D* normalBuffer = renderer->getNormalBuffer();
    Texture2D* depthBuffer = renderer->getDepthBuffer();
    bool hwDepth = renderer->getHardwareDepthSupport();
    
    // Check for edge filter. Only use it on the main view (null rendertarget)
    const EdgeFilterParameters& filterParams = mPipeline->getEdgeFilter();
    bool edgeFilter = (!mRenderTarget) && renderer->getMultiSample() && renderer->getScreenBuffer() &&
       (filterParams.mFilterStep > 0.0f) && (filterParams.mMaxFilter > 0.0f);
    
    // Use screen buffer only with edge filtering, else render direct to rendertarget or backbuffer
    RenderSurface* renderBuffer = edgeFilter ? renderer->getScreenBuffer()->getRenderSurface() : mRenderTarget;
    
    // Set the G-buffer UV coord adjustment here
    int gBufferWidth = diffBuffer->getWidth();
    int gBufferHeight = diffBuffer->getHeight();
    float widthRange = 0.5f * mWidth / gBufferWidth;
    float heightRange = 0.5f * mHeight / gBufferHeight;
    Vector4 bufferUVOffset((0.5f + (float)mScreenRect.mLeft) / gBufferWidth, (0.5f + (float)mScreenRect.mTop) / gBufferHeight,
        widthRange, heightRange);
    renderer->setVertexShaderConstant(getVSRegister(VSP_GBUFFEROFFSETS), bufferUVOffset);
    
    {
        // Render G-buffer
        PROFILE(View_RenderGBuffer);
        
        clearLastParameterSources();
        
        // Use always the default depth stencil, so that it matches the G-buffer size, and is in the expected format
        // Enable depth rendertarget only if hardware depth not supported
        renderer->setColorWrite(true);
        renderer->setFillMode(FILL_SOLID);
        renderer->setScissorTest(false);
        renderer->setStencilTest(false);
        renderer->resetDepthStencil();
        if (deferred)
        {
            renderer->setRenderTarget(0, diffBuffer);
            renderer->setRenderTarget(1, normalBuffer);
            if (!hwDepth)
                renderer->setRenderTarget(2, depthBuffer);
        }
        else
        {
            renderer->setRenderTarget(0, normalBuffer);
            if (!hwDepth)
                renderer->setRenderTarget(1, depthBuffer);
        }
        renderer->setViewport(mScreenRect);
        
        // Clear only depth and stencil at first, render the G-buffer batches
        renderer->clear(CLEAR_DEPTH | CLEAR_STENCIL);
        for (unsigned i = 0; i < mGBufferQueueSorted.size(); ++i)
            mGBufferQueueSorted[i]->draw(renderer);
        
        // Then fill the untouched parts of the G-buffer with defaults: black diffuse + specular (deferred only), far depth
        renderer->setAlphaTest(false);
        renderer->setBlendMode(BLEND_REPLACE);
        renderer->setDepthTest(CMP_LESSEQUAL);
        renderer->setDepthWrite(false);
        if (deferred)
        {
            renderer->resetRenderTarget(2);
            if (!hwDepth)
                renderer->setRenderTarget(1, depthBuffer);
            else
                renderer->resetRenderTarget(1);
            
            mPipeline->drawFullScreenQuad(*mCamera, mPipeline->getVertexShader("Deferred/GBufferFill"),
                mPipeline->getPixelShader("Deferred/GBufferFill_" + hwDepthVariations[hwDepth ? 1 : 0]), false);
        }
        else if (!hwDepth)
        {
            renderer->resetRenderTarget(1);
            renderer->setRenderTarget(0, depthBuffer);
            renderer->setViewport(mScreenRect);
            
            // The stencil shader writes color 1.0, which equals far depth
            mPipeline->drawFullScreenQuad(*mCamera, mPipeline->getVertexShader("Stencil"),
                mPipeline->getPixelShader("Stencil"), false);
        }
    }
    
    if (deferred)
    {
        // Render ambient color & fog
        clearLastParameterSources();
        
        renderer->setDepthTest(CMP_ALWAYS);
        renderer->setRenderTarget(0, renderBuffer);
        renderer->resetRenderTarget(1);
        renderer->resetRenderTarget(2);
        renderer->setTexture(TU_DIFFBUFFER, diffBuffer);
        renderer->setTexture(TU_DEPTHBUFFER, depthBuffer);
        renderer->setViewport(mScreenRect);
        
        // Use depth reconstruction only if necessary
        bool linear = mCamera->isOrthographic() || (!hwDepth);
        mPipeline->drawFullScreenQuad(*mCamera, mPipeline->getVertexShader("Deferred/Ambient"),
            mPipeline->getPixelShader("Deferred/Ambient_" + linearVariations[linear ? 1 : 0]), false);
    }
    else
    {
        // Light prepass: reset the light accumulation buffer with ambient light (half intensity to allow 2x "overburn")
        renderer->setRenderTarget(0, diffBuffer);
        renderer->resetRenderTarget(1);
        renderer->setViewport(mScreenRect);
        renderer->clear(CLEAR_COLOR, mZone->getAmbientColor() * 0.5f);
    }
    
    {
        // Render lights
        PROFILE(View_RenderLights);
        
        // Negative lights
        if (mNegativeLightQueueSorted.size())
        {
            clearLastParameterSources();
            
            if (deferred)
                renderer->setTexture(TU_DIFFBUFFER, diffBuffer);
            renderer->setTexture(TU_NORMALBUFFER, normalBuffer);
            renderer->setTexture(TU_DEPTHBUFFER, depthBuffer);
            
            for (unsigned i = 0; i < mNegativeLightQueueSorted.size(); ++i)
            {
                mPipeline->setupLightBatch(*mNegativeLightQueueSorted[i]);
                mNegativeLightQueueSorted[i]->draw(renderer);
            }
        }
        
        // Shadowed lights
        for (unsigned i = 0; i < mLightQueues.size(); ++i)
        {
            LightBatchQueue& queue = mLightQueues[i];
            
            Texture2D* shadowMap = queue.mLight->getShadowMap();
            if (shadowMap)
            {
                PROFILE(View_RenderShadowMap);
                
                clearLastParameterSources();
                
                renderer->setColorWrite(false);
                renderer->setStencilTest(false);
                renderer->setTexture(TU_SHADOWMAP, 0);
                renderer->setRenderTarget(0, shadowMap->getRenderSurface()->getLinkedRenderTarget());
                renderer->setDepthStencil(shadowMap);
                renderer->clear(CLEAR_DEPTH);
                
                // Set shadow depth bias
                BiasParameters parameters = queue.mLight->getShadowBias();
                renderer->setDepthBias(parameters.mConstantBias, parameters.mSlopeScaledBias);
                
                // Set a scissor rectangle to match possible shadow map size reduction by out-zooming
                // However, do not do this for point lights
                if (queue.mLight->getLightType() != LIGHT_SPLITPOINT)
                {
                    Texture2D* shadowMap = queue.mLight->getShadowMap();
                    float zoom = min(queue.mLight->getShadowCamera().getZoom(),
                        (float)(shadowMap->getWidth() - 2) / (float)shadowMap->getWidth());
                    Rect zoomRect(Vector2(-1.0f, -1.0f) * zoom, Vector2(1.0f, 1.0f) * zoom);
                    renderer->setScissorTest(true, zoomRect, false);
                }
                else
                    renderer->setScissorTest(false);
                
                const std::vector<Batch*>& sortedBatches = queue.mSortedShadowBatches;
                if (sortedBatches.size())
                {
                    for (unsigned j = 0; j < sortedBatches.size(); ++j)
                        sortedBatches[j]->draw(renderer);
                }
                
                renderer->setColorWrite(true);
                renderer->setDepthBias(0.0f, 0.0f);
            }
            
            // Light volume batches are not sorted as there should be only one of them
            if (queue.mBatches.size())
            {
                clearLastParameterSources();
                
                if (deferred)
                {
                    renderer->setRenderTarget(0, renderBuffer);
                    renderer->setTexture(TU_DIFFBUFFER, diffBuffer);
                }
                else
                    renderer->setRenderTarget(0, diffBuffer);
                
                renderer->setTexture(TU_NORMALBUFFER, normalBuffer);
                renderer->setTexture(TU_DEPTHBUFFER, depthBuffer);
                renderer->resetDepthStencil();
                renderer->setViewport(mScreenRect);
                
                for (unsigned j = 0; j < queue.mBatches.size(); ++j)
                {
                    mPipeline->setupLightBatch(queue.mBatches[j]);
                    queue.mBatches[j].draw(renderer);
                }
                
                // If was the last split of a split point light, clear the stencil by rendering the point light again
                if ((queue.mLastSplit) && (queue.mLight->getLightType() == LIGHT_SPLITPOINT))
                    mPipeline->drawSplitLightToStencil(*mCamera, queue.mLight, true);
            }
        }
        
        // Non-shadowed lights
        if (mNoShadowLightQueueSorted.size())
        {
            clearLastParameterSources();
            
            if (deferred)
            {
                renderer->setRenderTarget(0, renderBuffer);
                renderer->setTexture(TU_DIFFBUFFER, diffBuffer);
            }
            else
                renderer->setRenderTarget(0, diffBuffer);
            
            renderer->setTexture(TU_NORMALBUFFER, normalBuffer);
            renderer->setTexture(TU_DEPTHBUFFER, depthBuffer);
            renderer->resetDepthStencil();
            renderer->setViewport(mScreenRect);
            
            for (unsigned i = 0; i < mNoShadowLightQueueSorted.size(); ++i)
            {
                mPipeline->setupLightBatch(*mNoShadowLightQueueSorted[i]);
                mNoShadowLightQueueSorted[i]->draw(renderer);
            }
        }
    }
    
    {
        // Render forward passes
        PROFILE(View_RenderForward);
        
        clearLastParameterSources();
        renderer->setStencilTest(false);
        renderer->setRenderTarget(0, renderBuffer);
        renderer->setTexture(TU_DIFFBUFFER, 0);
        renderer->setTexture(TU_NORMALBUFFER, 0);
        renderer->setTexture(TU_DEPTHBUFFER, 0);
        renderer->setViewport(mScreenRect);
        
        if (!deferred)
            renderer->clear(CLEAR_COLOR, mZone->getFogColor());
        
        for (unsigned i = 0; i < mAmbientQueueSorted.size(); ++i)
            mAmbientQueueSorted[i]->draw(renderer);
        
        for (unsigned i = 0; i < mForwardQueueSorted.size(); ++i)
        {
            if (mForwardQueueSorted[i]->mForwardLight)
                optimizeLightByScissor(mForwardQueueSorted[i]->mForwardLight);
            else
            {
                renderer->setScissorTest(false);
                // Bind the light accumulation buffer for material pass of prepass mode
                if (!deferred)
                    renderer->setTexture(TU_LIGHTBUFFER, diffBuffer);
            }
            
            mForwardQueueSorted[i]->draw(renderer);
        }
        
        renderer->setScissorTest(false);
        for (unsigned i = 0; i < mPostOpaqueQueueSorted.size(); ++i)
            mPostOpaqueQueueSorted[i]->draw(renderer);
    }
    
    {
        // Render transparent objects last (both ambient & additive lighting)
        PROFILE(View_RenderTransparent);
        
        for (unsigned i = 0; i < mTransparentQueueSorted.size(); ++i)
        {
            optimizeLightByScissor(mTransparentQueueSorted[i]->mForwardLight);
            mTransparentQueueSorted[i]->draw(renderer);
        }
    }
    
    // Render edge filter now if enabled
    if (edgeFilter)
    {
        PROFILE(View_RenderEdgeFilter);
        
        float invWidth = 0.5f / gBufferWidth;
        float invHeight = 0.5f / gBufferHeight;
        
        renderer->setAlphaTest(false);
        renderer->setBlendMode(BLEND_REPLACE);
        renderer->setDepthTest(CMP_ALWAYS);
        renderer->setDepthWrite(false);
        renderer->setScissorTest(false);
        renderer->setStencilTest(false);
        renderer->setRenderTarget(0, mRenderTarget);
        renderer->setTexture(TU_DIFFBUFFER, renderer->getScreenBuffer());
        renderer->setPixelShaderConstant(getPSRegister(PSP_SAMPLEOFFSETS), Vector4(invWidth, -invWidth, invHeight, -invHeight));
        renderer->setPixelShaderConstant(getPSRegister(PSP_EDGEFILTERPARAMS), Vector4(filterParams.mThreshold,
            filterParams.mFilterStep, filterParams.mMaxFilter, filterParams.mMaxScale));
        renderer->setViewport(mScreenRect);
        
        mPipeline->drawFullScreenQuad(*mCamera, mPipeline->getVertexShader("EdgeFilter"),
            mPipeline->getPixelShader("EdgeFilter"), false);
    }
}

