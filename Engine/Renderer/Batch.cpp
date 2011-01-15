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

#include <cstring>

#include "DebugNew.h"

void Batch::calculateSortKey(bool stateHasPriority, bool frontToBack)
{
    // Distance
    unsigned short distance = (unsigned short)(clamp(mDistance / mCamera->getFarClip(), 0.0f, 1.0f) * 65535.0f);
    if (frontToBack)
        distance = 65535 - distance;
    
    // Shaders
    unsigned short shaders = (mVertexShader ? mVertexShader->getHash() : 0) + (mPixelShader ? mPixelShader->getHash() : 0);
    
    // Material technique (determines textures and shader parameters)
    unsigned short technique = *((unsigned short*)&mTechnique);
    
    // Vertex and index buffers and forward light
    unsigned short buffers = 0;
    buffers += mGeometry->getBufferHash();
    buffers += *((unsigned short*)&mForwardLight);
    
    if (stateHasPriority)
    {
        shaders >>= 1;
        if (mHasPriority) shaders |= 32768;
        
        mSortKey = (((unsigned long long)shaders) << 48) | (((unsigned long long)technique) << 32) |
                   (((unsigned long long)buffers) << 16) | ((unsigned long long)distance);
    }
    else
    {
        distance >>= 1;
        if (mHasPriority) distance |= 32768;
        
        mSortKey = (((unsigned long long)distance) << 48) | (((unsigned long long)shaders) << 32) |
                   (((unsigned long long)technique) << 16) | ((unsigned long long)buffers);
    }
}

void Batch::draw(Renderer* renderer) const
{
    // Get node
    VolumeNode* node = mNode;
    
    // Get shaders
    VertexShader* vs = mVertexShader;
    PixelShader* ps = mPixelShader;
    if ((!vs) || (!ps))
        return;
    
    // Get light (if any)
    Light* light = mForwardLight;
    if (node->getNodeFlags() & NODE_LIGHT)
        light = static_cast<Light*>(mNode);
    
    // Set pass-specific renderstates
    if (mPass)
    {
        if (mPass->getAlphaTest())
            renderer->setAlphaTest(true, CMP_GREATEREQUAL, 0.5f);
        else
            renderer->setAlphaTest(false);
        
        renderer->setBlendMode(mPass->getBlendMode());
        renderer->setCullMode(mPass->getCullMode());
        renderer->setDepthTest(mPass->getDepthTestMode());
        renderer->setDepthWrite(mPass->getDepthWrite());
    }
    
    // Set material textures
    if (mTechnique)
    {
        const std::vector<SharedPtr<Texture> >& textures = mTechnique->getTextures();
        
        if (ps->hasTextureUnit(TU_DIFFUSE))
            renderer->setTexture(TU_DIFFUSE, textures[TU_DIFFUSE]);
        if (ps->hasTextureUnit(TU_NORMAL))
            renderer->setTexture(TU_NORMAL, textures[TU_NORMAL]);
        if (ps->hasTextureUnit(TU_SPECULAR))
            renderer->setTexture(TU_SPECULAR, textures[TU_SPECULAR]);
        if (ps->hasTextureUnit(TU_DETAIL))
            renderer->setTexture(TU_DETAIL, textures[TU_DETAIL]);
        if (ps->hasTextureUnit(TU_ENVIRONMENT))
            renderer->setTexture(TU_ENVIRONMENT, textures[TU_ENVIRONMENT]);
        if (!light)
        {
            if (ps->hasTextureUnit(TU_EMISSIVE))
                renderer->setTexture(TU_EMISSIVE, textures[TU_EMISSIVE]);
        }
    }
    
    // Set light-related textures
    Texture2D* shadowMap = 0;
    if (light)
    {
        shadowMap = light->getShadowMap();
        
        if ((shadowMap) && (ps->hasTextureUnit(TU_SHADOWMAP)))
            renderer->setTexture(TU_SHADOWMAP, shadowMap);
        if (ps->hasTextureUnit(TU_LIGHTRAMP))
            renderer->setTexture(TU_LIGHTRAMP, light->getRampTexture());
        if (ps->hasTextureUnit(TU_LIGHTSPOT))
            renderer->setTexture(TU_LIGHTSPOT, light->getSpotTexture());
    }
    
    // Set shaders
    renderer->setVertexShader(vs);
    renderer->setPixelShader(ps);
    
    // Set viewport parameters
    if (vs->needParameterUpdate(VSP_DEPTHMODE, mCamera))
    {
        Vector4 depthMode = Vector4::sZero;
        if (mCamera->isOrthographic())
            depthMode.mZ = 1.0f;
        else
            depthMode.mW = 1.0f / mCamera->getFarClip();
        
        renderer->setVertexShaderConstant(getVSRegister(VSP_DEPTHMODE), depthMode);
    }
    
    if (vs->needParameterUpdate(VSP_FRUSTUMSIZE, mCamera))
    {
        const Vector3& farVector = mCamera->getFrustumFarSize();
        Vector4 viewportParams(farVector.mX, farVector.mY, farVector.mZ, 0.0f);
        renderer->setVertexShaderConstant(getVSRegister(VSP_FRUSTUMSIZE), viewportParams);
    }
    
    // Set node transforms
    if (node)
    {
        const Matrix4x3* model = &node->getWorldTransform();
        const Matrix4x3* view = &mCamera->getInverseWorldTransform();
        const Matrix4* projection = &mCamera->getProjection();
        const void* modelSrc = node;
        const void* viewSrc = mCamera;
        
        node->overrideTransforms(mBatchIndex, *mCamera, &model, &view);
        // See if the node actually adjusted the transforms, and set the sources accordingly
        // so that we can avoid setting the same transforms over again
        if (model == &Matrix4x3::sIdentity)
            modelSrc = mCamera;
        if (view != &mCamera->getInverseWorldTransform())
            viewSrc = node;
        
        if (vs->needParameterUpdate(VSP_MODEL, modelSrc))
            renderer->setVertexShaderConstant(getVSRegister(VSP_MODEL), *model);
        
        if (vs->needParameterUpdate(VSP_MODELVIEWPROJ, modelSrc))
            renderer->setVertexShaderConstant(getVSRegister(VSP_MODELVIEWPROJ), (*projection) * (*view) * (*model));
        
        if ((shadowMap) && (vs->needParameterUpdate(VSP_SHADOWPROJ, light)))
        {
            Camera& shadowCamera = light->getShadowCamera();
            const Matrix4x3& shadowView = shadowCamera.getInverseWorldTransform();
            Matrix4 shadowProj = shadowCamera.getProjection();
            
            Matrix4 texAdjust = Matrix4::sIdentity;
            float offset = 0.5f + 0.5f / (float)shadowMap->getWidth();
            texAdjust.setTranslation(Vector3(offset, offset, 0.0f));
            texAdjust.setScale(Vector3(0.5f, -0.5f, 1.0f));
            
            renderer->setVertexShaderConstant(getVSRegister(VSP_SHADOWPROJ), texAdjust * shadowProj * shadowView);
        }
        
        if ((light) && (vs->needParameterUpdate(VSP_SPOTPROJ, light)))
        {
            Matrix4x3 spotView;
            Quaternion rotation(Vector3(0.0f, 0.0f, 1.0f), light->getDirection());
            spotView.define(light->getWorldPosition(), light->getWorldRotation() * rotation, 1.0f);
            
            Matrix4 spotProj;
            memset(&spotProj, 0, sizeof(spotProj));
            // Make the projected light slightly smaller than the shadow map to prevent light spill
            float h = 1.005f / tanf(light->getFov() * M_DEGTORAD * 0.5f);
            float w = h / light->getAspectRatio();
            spotProj.m00 = w;
            spotProj.m11 = h;
            spotProj.m22 = 1.0f / max(light->getRange(), M_EPSILON);
            spotProj.m32 = 1.0f;
            
            Matrix4 texAdjust = Matrix4::sIdentity;
            texAdjust.setTranslation(Vector3(0.5f, 0.5f, 0.0f));
            texAdjust.setScale(Vector3(0.5f, -0.5f, 1.0f));
            
            renderer->setVertexShaderConstant(getVSRegister(VSP_SPOTPROJ), texAdjust * spotProj * spotView.getInverse());
        }
        
        if (vs->needParameterUpdate(VSP_VIEWINVERSE, mCamera))
            renderer->setVertexShaderConstant(getVSRegister(VSP_VIEWINVERSE), mCamera->getWorldTransform());
        
        if (vs->needParameterUpdate(VSP_VIEWPROJ, viewSrc))
            renderer->setVertexShaderConstant(getVSRegister(VSP_VIEWPROJ), (*projection) * (*view));
    }
    
    // Set material's vertex shader parameters
    if (mTechnique)
    {
        const std::map<VSParameter, Vector4>& parameters = mTechnique->getVertexShaderParameters();
        for (std::map<VSParameter, Vector4>::const_iterator i = parameters.begin(); i != parameters.end(); ++i)
        {
            if (vs->needParameterUpdate(i->first, mTechnique))
                renderer->setVertexShaderConstant(getVSRegister(i->first), i->second);
        }
    }
    
    if (vs->needParameterUpdate(VSP_VIEWRIGHTVECTOR, mCamera))
        renderer->setVertexShaderConstant(getVSRegister(VSP_VIEWRIGHTVECTOR), mCamera->getRightVector());
    
    if (vs->needParameterUpdate(VSP_VIEWUPVECTOR, mCamera))
        renderer->setVertexShaderConstant(getVSRegister(VSP_VIEWUPVECTOR), mCamera->getUpVector());
    
    // Set node's instance & skinning parameters
    if (node->getNodeFlags() & NODE_GEOMETRY)
    {
        GeometryNode* geom = static_cast<GeometryNode*>(node);
        const float* data;
        unsigned count;
        
        if (vs->hasParameter(VSP_MODELSKINMATRICES))
        {
            if (geom->getVertexShaderParameter(mBatchIndex, VSP_MODELSKINMATRICES, &data, &count))
            {
                if (vs->needParameterUpdate(VSP_MODELSKINMATRICES, data))
                    renderer->setVertexShaderConstant(getVSRegister(VSP_MODELSKINMATRICES), data, count);
            }
        }
        
        if (vs->hasParameter(VSP_MODELINSTANCES))
        {
            if (geom->getVertexShaderParameter(mBatchIndex, VSP_MODELINSTANCES, &data, &count))
            {
                if (vs->needParameterUpdate(VSP_MODELINSTANCES, data))
                    renderer->setVertexShaderConstant(getVSRegister(VSP_MODELINSTANCES), data, count);
            }
        }
    }
    
    // Set light-related parameters
    if (light)
    {
        if (ps->needParameterUpdate(PSP_LIGHTATTEN, light))
        {
            Vector4 lightAtten(1.0f / max(light->getRange(), M_EPSILON), 0.0f, 0.0f, 0.0f);
            renderer->setPixelShaderConstant(getPSRegister(PSP_LIGHTATTEN), lightAtten);
        }
        
        if (ps->needParameterUpdate(PSP_LIGHTCOLOR, light))
        {
            float fade = 1.0f;
            float fadeEnd = light->getDrawDistance();
            float fadeStart = light->getFadeDistance();
            
            // Do fade calculation for light if both fade & draw distance defined
            if ((light->getLightType() != LIGHT_DIRECTIONAL) && (fadeEnd != 0.0f) && (fadeStart != 0.0f) && (fadeStart < fadeEnd))
                fade = min(1.0f - (light->getDistance() - fadeStart) / (fadeEnd - fadeStart), 1.0f);
            
            renderer->setPixelShaderConstant(getPSRegister(PSP_LIGHTCOLOR), Vector4(light->getColor().getRGB(), light->getSpecularIntensity()) * fade);
        }
        
        if (ps->needParameterUpdate(PSP_LIGHTDIR, light))
            renderer->setPixelShaderConstant(getPSRegister(PSP_LIGHTDIR), -(light->getWorldRotation() * light->getDirection()));
        
        if (ps->needParameterUpdate(PSP_LIGHTPOS, light))
            renderer->setPixelShaderConstant(getPSRegister(PSP_LIGHTPOS), light->getWorldPosition() - mCamera->getWorldPosition());
        
        if (ps->needParameterUpdate(PSP_LIGHTSPLITS, light))
        {
            float nearFadeRange = light->getNearFadeRange();
            float farFadeRange = light->getFarFadeRange();
            float nearFadeStart = light->getNearSplit() - nearFadeRange;
            float farFadeStart = light->getFarSplit() - farFadeRange;
            float depthRange = mCamera->getFarClip();
            
            renderer->setPixelShaderConstant(getPSRegister(PSP_LIGHTSPLITS),
                Vector4(nearFadeStart / depthRange, 1.0f / (nearFadeRange / depthRange),
                farFadeStart / depthRange, 1.0f / (farFadeRange / depthRange)));
        }
    }
    
    // Set material's pixel shader parameters
    if (mTechnique)
    {
        const std::map<PSParameter, Vector4>& parameters = mTechnique->getPixelShaderParameters();
        for (std::map<PSParameter, Vector4>::const_iterator i = parameters.begin(); i != parameters.end(); ++i)
        {
            if (ps->needParameterUpdate(i->first, mTechnique))
                renderer->setPixelShaderConstant(getPSRegister(i->first), i->second);
        }
    }
    
    // Set shadow & spotlight projection parameters
    if (shadowMap)
    {
        if (ps->needParameterUpdate(PSP_SAMPLEOFFSETS, shadowMap))
        {
            float invWidth = 1.0f / (float)shadowMap->getWidth();
            renderer->setPixelShaderConstant(getPSRegister(PSP_SAMPLEOFFSETS),
                Vector4(0.5f * invWidth, -0.5f * invWidth, 0.0f, 0.0f));
        }
        
        if (ps->needParameterUpdate(PSP_SHADOWPROJ, light))
        {
            Camera& shadowCamera = light->getShadowCamera();
            const Matrix4x3& shadowView = shadowCamera.getInverseWorldTransform();
            Matrix4 shadowProj = shadowCamera.getProjection();
            
            Matrix4x3 viewPos = Matrix4x3::sIdentity;
            viewPos.setTranslation(mCamera->getWorldPosition());
            
            Matrix4 texAdjust = Matrix4::sIdentity;
            float offset = 0.5f + 0.5f / (float)shadowMap->getWidth();
            texAdjust.setTranslation(Vector3(offset, offset, 0.0f));
            texAdjust.setScale(Vector3(0.5f, -0.5f, 1.0f));
            
            renderer->setPixelShaderConstant(getPSRegister(PSP_SHADOWPROJ),
                texAdjust * shadowProj * shadowView * viewPos);
        }
    }
    
    if ((light) && (ps->needParameterUpdate(PSP_SPOTPROJ, light)))
    {
        Matrix4x3 spotView;
        Quaternion rotation(Vector3(0.0f, 0.0f, 1.0f), light->getDirection());
        spotView.define(light->getWorldPosition(), light->getWorldRotation() * rotation, 1.0f);
        
        Matrix4 spotProj;
        memset(&spotProj, 0, sizeof(spotProj));
        // Make the projected light slightly smaller than the shadow map to prevent light spill
        float h = 1.005f / tanf(light->getFov() * M_DEGTORAD * 0.5f);
        float w = h / light->getAspectRatio();
        spotProj.m00 = w;
        spotProj.m11 = h;
        spotProj.m22 = 1.0f / max(light->getRange(), M_EPSILON);
        spotProj.m32 = 1.0f;
        
        Matrix4x3 viewPos = Matrix4x3::sIdentity;
        viewPos.setTranslation(mCamera->getWorldPosition());
        
        Matrix4 texAdjust = Matrix4::sIdentity;
        texAdjust.setTranslation(Vector3(0.5f, 0.5f, 0.0f));
        texAdjust.setScale(Vector3(0.5f, -0.5f, 1.0f));
        
        renderer->setPixelShaderConstant(getPSRegister(PSP_SPOTPROJ), texAdjust * spotProj * spotView.getInverse() * viewPos);
    }
    
    // Draw
    mGeometry->draw(renderer);
}

