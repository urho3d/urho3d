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
#include "Material.h"
#include "Pipeline.h"
#include "PixelShader.h"
#include "Profiler.h"
#include "Renderer.h"
#include "Texture2D.h"
#include "VertexShader.h"
#include "View.h"

#include "DebugNew.h"

void View::getBatchesForward()
{
    // Go through geometries for ambient batches
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
                
                MaterialPass* pass = tech->getPass(PASS_AMBIENT);
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
                    continue;
                }
                else
                {
                    // If no ambient pass, check for postopaque (custom) pass
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
                
                // Loop through lit geometries
                for (unsigned k = 0; k < sLitGeometries[j].size(); ++k)
                {
                    GeometryNode* node = sLitGeometries[j][k];
                    unsigned numBatches = node->getNumBatches();
                    
                    for (unsigned l = 0; l < numBatches; ++l)
                    {
                        MaterialTechnique* tech = getMaterialTechnique(node, l);
                        if (!tech)
                            continue;
                        
                        MaterialPass* pass = 0;
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
                        
                        // Check from the ambient pass whether the object is opaque
                        MaterialPass* ambientPass = tech->getPass(PASS_AMBIENT);
                        if ((!ambientPass) || (ambientPass->getBlendMode() == BLEND_REPLACE))
                        {
                            mPipeline->setBatchShaders(newBatch, tech, pass);
                            newBatch.calculateSortKey(true, true);
                            if (!negative)
                                lightQueue.mBatches.push_back(newBatch);
                            else
                                mNegativeQueue.push_back(newBatch);
                        }
                        else
                        {
                            // Transparent: disable shadows
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
                            
                            mPipeline->setBatchShaders(newBatch, tech, pass, false);
                            newBatch.calculateSortKey(false, false);
                            mTransparentQueue.push_back(newBatch);
                        }
                    }
                    
                    if (splitPointLight)
                        litTransparencies.insert(node);
                }
                
                // Store light & its shadow batches only if lit geometries exist
                if (sLitGeometries[j].size())
                    lightQueueCount++;
            }
            
            // Mark the last split
            if (lightQueueCount != prevLightQueueCount)
                mLightQueues[lightQueueCount - 1].mLastSplit = true;
        }
        
        // Resize the light queue vector now that final size is known
        mLightQueues.resize(lightQueueCount);
    }
    
    // Finally sort the batches
    {
        PROFILE(View_SortBatches);
        
        sortBatches(mAmbientQueue, mAmbientQueueSorted);
        sortBatches(mNegativeQueue, mNegativeQueueSorted);
        sortBatches(mPostOpaqueQueue, mPostOpaqueQueueSorted);
        sortBatches(mTransparentQueue, mTransparentQueueSorted);
        
        for (unsigned i = 0; i < mLightQueues.size(); ++i)
        {
            sortBatches(mLightQueues[i].mShadowBatches, mLightQueues[i].mSortedShadowBatches);
            sortBatches(mLightQueues[i].mBatches, mLightQueues[i].mSortedBatches);
        }
    }
}

void View::renderBatchesForward()
{
    Renderer* renderer = mPipeline->getRenderer();
    
    {
        // Render opaque objects' ambient & negative lighting
        PROFILE(View_RenderAmbient);
        
        clearLastParameterSources();
        
        renderer->setColorWrite(true);
        renderer->setFillMode(FILL_SOLID);
        renderer->setStencilTest(false);
        renderer->setRenderTarget(0, mRenderTarget);
        renderer->setDepthStencil(mDepthStencil);
        renderer->setViewport(mScreenRect);
        renderer->clear(CLEAR_COLOR | CLEAR_DEPTH | CLEAR_STENCIL, mZone->getFogColor());
        
        for (unsigned i = 0; i < mAmbientQueueSorted.size(); ++i)
            mAmbientQueueSorted[i]->draw(renderer);
        
        for (unsigned i = 0; i < mNegativeQueueSorted.size(); ++i)
        {
            optimizeLightByScissor(mNegativeQueueSorted[i]->mForwardLight);
            mNegativeQueueSorted[i]->draw(renderer);
        }
    }
    
    {
        // Render shadow maps + opaque objects' shadowed additive lighting
        PROFILE(View_RenderLights);
        
        for (unsigned i = 0; i < mLightQueues.size(); ++i)
        {
            LightBatchQueue& queue = mLightQueues[i];
            
            if (queue.mLight->getShadowMap())
            {
                PROFILE(View_RenderShadowMap);
                
                Texture2D* shadowMap = queue.mLight->getShadowMap();
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
                    float zoom = min(queue.mLight->getShadowCamera().getZoom(),
                        (float)(shadowMap->getWidth() - 2) / (float)shadowMap->getWidth());
                    Rect zoomRect(Vector2(-1.0f, -1.0f) * zoom, Vector2(1.0f, 1.0f) * zoom);
                    renderer->setScissorTest(true, zoomRect, false);
                }
                else
                    renderer->setScissorTest(false);
                
                std::vector<Batch*>& sortedBatches = queue.mSortedShadowBatches;
                if (sortedBatches.size())
                {
                    for (unsigned j = 0; j < sortedBatches.size(); ++j)
                        sortedBatches[j]->draw(renderer);
                }
                
                renderer->setColorWrite(true);
                renderer->setDepthBias(0.0f, 0.0f);
            }
            
            std::vector<Batch*>& sortedBatches = queue.mSortedBatches;
            LightType type = queue.mLight->getLightType();
            if (sortedBatches.size())
            {
                clearLastParameterSources();
                
                renderer->setRenderTarget(0, mRenderTarget);
                renderer->setDepthStencil(mDepthStencil);
                renderer->setViewport(mScreenRect);
                optimizeLightByScissor(queue.mLight);
                
                // If this is a split point or dir. light, mark the split volume to the stencil
                if ((type == LIGHT_DIRECTIONAL) || (type == LIGHT_SPLITPOINT))
                    mPipeline->drawSplitLightToStencil(*mCamera, queue.mLight);
                
                for (unsigned j = 0; j < sortedBatches.size(); ++j)
                    sortedBatches[j]->draw(renderer);
            }
            
            // Clear the stencil buffer after the last split
            if ((queue.mLastSplit) && ((type == LIGHT_DIRECTIONAL) || (type == LIGHT_SPLITPOINT)))
            {
                renderer->setScissorTest(false);
                mPipeline->drawSplitLightToStencil(*mCamera, queue.mLight, true);
            }
        }
    }
    
    {
        // Render post-opaque passes
        PROFILE(View_RenderForward);
        
        clearLastParameterSources();
        
        renderer->setScissorTest(false);
        renderer->setStencilTest(false);
        renderer->setRenderTarget(0, mRenderTarget);
        renderer->setViewport(mScreenRect);
        renderer->setDepthStencil(mDepthStencil);
        
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
}
