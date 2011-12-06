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
#include "Geometry.h"
#include "Graphics.h"
#include "GraphicsImpl.h"
#include "Light.h"
#include "Material.h"
#include "Renderer.h"
#include "Profiler.h"
#include "ShaderVariation.h"
#include "Sort.h"
#include "Technique.h"
#include "Texture2D.h"
#include "VertexBuffer.h"
#include "Zone.h"

#include "DebugNew.h"

inline bool CompareBatchesFrontToBack(Batch* lhs, Batch* rhs)
{
    if (lhs->sortKey_ == rhs->sortKey_)
        return lhs->distance_ < rhs->distance_;
    else
        return lhs->sortKey_ > rhs->sortKey_;
}

inline bool CompareBatchesBackToFront(Batch* lhs, Batch* rhs)
{
    if (lhs->distance_ == rhs->distance_)
        return lhs->sortKey_ > rhs->sortKey_;
    else
        return lhs->distance_ > rhs->distance_;
}

inline bool CompareInstancesFrontToBack(const InstanceData& lhs, const InstanceData& rhs)
{
    return lhs.distance_ < rhs.distance_;
}

inline bool CompareBatchGroupsFrontToBack(BatchGroup* lhs, BatchGroup* rhs)
{
    return lhs->instances_[0].distance_ < rhs->instances_[0].distance_;
}

void CalculateShadowMatrix(Matrix4& dest, LightBatchQueue* queue, unsigned split, Graphics* graphics, Renderer* renderer, const Vector3& translation)
{
    Camera* shadowCamera = queue->shadowSplits_[split].shadowCamera_;
    const IntRect& viewport = queue->shadowSplits_[split].shadowViewport_;
    
    Matrix3x4 posAdjust(translation, Quaternion::IDENTITY, 1.0f);
    Matrix3x4 shadowView(shadowCamera->GetInverseWorldTransform());
    Matrix4 shadowProj(shadowCamera->GetProjection());
    Matrix4 texAdjust(Matrix4::IDENTITY);
    
    Texture2D* shadowMap = queue->shadowMap_;
    if (!shadowMap)
        return;
    
    float width = (float)shadowMap->GetWidth();
    float height = (float)shadowMap->GetHeight();
    
    Vector2 offset(
        (float)viewport.left_ / width,
        (float)viewport.top_ / height
    );
    
    Vector2 scale(
        0.5f * (float)(viewport.right_ - viewport.left_) / width,
        0.5f * (float)(viewport.bottom_ - viewport.top_) / height
    );
    
    #ifdef USE_OPENGL
    offset.x_ += scale.x_;
    offset.y_ += scale.y_;
    offset.y_ = 1.0f - offset.y_;
    // If using 4 shadow samples, offset the position diagonally by half pixel
    if (renderer->GetShadowQuality() & SHADOWQUALITY_HIGH_16BIT)
    {
        offset.x_ -= 0.5f / width;
        offset.y_ -= 0.5f / height;
    }
    texAdjust.SetTranslation(Vector3(offset.x_, offset.y_, 0.5f));
    texAdjust.SetScale(Vector3(scale.x_, scale.y_, 0.5f));
    #else
    offset.x_ += scale.x_ + 0.5f / width;
    offset.y_ += scale.y_ + 0.5f / height;
    if (renderer->GetShadowQuality() & SHADOWQUALITY_HIGH_16BIT)
    {
        offset.x_ -= 0.5f / width;
        offset.y_ -= 0.5f / height;
    }
    // If using 2 shadow samples (fallback mode), offset the position horizontally only
    if (graphics->GetFallback())
        offset.x_ -= 0.5f / width;
    scale.y_ = -scale.y_;
    texAdjust.SetTranslation(Vector3(offset.x_, offset.y_, 0.0f));
    texAdjust.SetScale(Vector3(scale.x_, scale.y_, 1.0f));
    #endif
    
    dest = texAdjust * shadowProj * shadowView * posAdjust;
}

void CalculateSpotMatrix(Matrix4& dest, Light* light, const Vector3& translation)
{
    Matrix3x4 posAdjust(translation, Quaternion::IDENTITY, 1.0f);
    Matrix3x4 spotView(light->GetWorldPosition(), light->GetWorldRotation(), 1.0f);
    Matrix4 spotProj(Matrix4::ZERO);
    Matrix4 texAdjust(Matrix4::IDENTITY);
    
    // Make the projected light slightly smaller than the shadow map to prevent light spill
    float h = 1.005f / tanf(light->GetFov() * M_DEGTORAD * 0.5f);
    float w = h / light->GetAspectRatio();
    spotProj.m00_ = w;
    spotProj.m11_ = h;
    spotProj.m22_ = 1.0f / Max(light->GetRange(), M_EPSILON);
    spotProj.m32_ = 1.0f;
    
    #ifdef USE_OPENGL
    texAdjust.SetTranslation(Vector3(0.5f, 0.5f, 0.5f));
    texAdjust.SetScale(Vector3(0.5f, -0.5f, 0.5f));
    #else
    texAdjust.SetTranslation(Vector3(0.5f, 0.5f, 0.0f));
    texAdjust.SetScale(Vector3(0.5f, -0.5f, 1.0f));
    #endif
    
    dest = texAdjust * spotProj * spotView.Inverse() * posAdjust;
}

void Batch::CalculateSortKey()
{
    unsigned lightQueue = (*((unsigned*)&lightQueue_) / sizeof(LightBatchQueue)) & 0x7fff;
    unsigned pass = (*((unsigned*)&pass_) / sizeof(Pass)) & 0xffff;
    unsigned material = (*((unsigned*)&material_) / sizeof(Material)) & 0xffff;
    unsigned geometry = (*((unsigned*)&geometry_) / sizeof(Geometry)) & 0xffff;
    if (isBase_)
        lightQueue |= 0x8000;
    sortKey_ = (((unsigned long long)lightQueue) << 48) | (((unsigned long long)pass) << 32) |
        (((unsigned long long)material) << 16) | geometry;
}

void Batch::Prepare(Graphics* graphics, Renderer* renderer, bool setModelTransform) const
{
    if (!vertexShader_ || !pixelShader_)
        return;
    
    // Set pass / material-specific renderstates
    if (pass_ && material_)
    {
        if (pass_->GetAlphaTest())
            graphics->SetAlphaTest(true, CMP_GREATEREQUAL, 0.5f);
        else
            graphics->SetAlphaTest(false);
        
        graphics->SetBlendMode(pass_->GetBlendMode());
        graphics->SetCullMode(pass_->GetType() != PASS_SHADOW ? material_->GetCullMode() : material_->GetShadowCullMode());
        graphics->SetDepthTest(pass_->GetDepthTestMode());
        graphics->SetDepthWrite(pass_->GetDepthWrite());
    }
    
    // Set shaders
    graphics->SetShaders(vertexShader_, pixelShader_);
    
    // Set viewport and camera shader parameters
    if (graphics->NeedParameterUpdate(VSP_CAMERAPOS, camera_))
        graphics->SetShaderParameter(VSP_CAMERAPOS, camera_->GetWorldPosition());
    
    if (graphics->NeedParameterUpdate(VSP_CAMERAROT, camera_))
        graphics->SetShaderParameter(VSP_CAMERAROT, camera_->GetWorldTransform().RotationMatrix());
    
    if (graphics->NeedParameterUpdate(VSP_DEPTHMODE, camera_))
    {
        Vector4 depthMode = Vector4::ZERO;
        if (camera_->IsOrthographic())
        {
            depthMode.x_ = 1.0f;
            #ifdef USE_OPENGL
            depthMode.z_ = 0.5f;
            depthMode.w_ = 0.5f;
            #else
            depthMode.z_ = 1.0f;
            #endif
        }
        else
            depthMode.w_ = 1.0f / camera_->GetFarClip();
        
        graphics->SetShaderParameter(VSP_DEPTHMODE, depthMode);
    }
    
    if (graphics->NeedParameterUpdate(VSP_FRUSTUMSIZE, camera_))
    {
        Vector3 nearVector, farVector;
        camera_->GetFrustumSize(nearVector, farVector);
        Vector4 viewportParams(farVector.x_, farVector.y_, farVector.z_, 0.0f);
        
        graphics->SetShaderParameter(VSP_FRUSTUMSIZE, viewportParams);
    }
    
    IntRect viewport = graphics->GetViewport();
    unsigned viewportHash = (viewport.left_) | (viewport.top_ << 8) | (viewport.right_ << 16) | (viewport.bottom_ << 24);
    if (graphics->NeedParameterUpdate(VSP_GBUFFEROFFSETS, (const void*)viewportHash))
    {
        float gBufferWidth = (float)graphics->GetWidth();
        float gBufferHeight = (float)graphics->GetHeight();
        float widthRange = 0.5f * (viewport.right_ - viewport.left_) / gBufferWidth;
        float heightRange = 0.5f * (viewport.bottom_ - viewport.top_) / gBufferHeight;
        
        #ifdef USE_OPENGL
        Vector4 bufferUVOffset(((float)viewport.left_) / gBufferWidth + widthRange,
            ((float)viewport.top_) / gBufferHeight + heightRange, widthRange, heightRange);
        #else
        Vector4 bufferUVOffset((0.5f + (float)viewport.left_) / gBufferWidth + widthRange,
            (0.5f + (float)viewport.top_) / gBufferHeight + heightRange, widthRange, heightRange);
        #endif
        
        graphics->SetShaderParameter(VSP_GBUFFEROFFSETS, bufferUVOffset);
    }
    
    if (overrideView_)
    {
        if (graphics->NeedParameterUpdate(VSP_VIEWPROJ, ((unsigned char*)camera_) + 4))
            graphics->SetShaderParameter(VSP_VIEWPROJ, camera_->GetProjection());
    }
    else
    {
        if (graphics->NeedParameterUpdate(VSP_VIEWPROJ, camera_))
            graphics->SetShaderParameter(VSP_VIEWPROJ, camera_->GetProjection() *
                camera_->GetInverseWorldTransform());
    }
    
    if (graphics->NeedParameterUpdate(VSP_VIEWRIGHTVECTOR, camera_))
        graphics->SetShaderParameter(VSP_VIEWRIGHTVECTOR, camera_->GetRightVector());
    
    if (graphics->NeedParameterUpdate(VSP_VIEWUPVECTOR, camera_))
        graphics->SetShaderParameter(VSP_VIEWUPVECTOR, camera_->GetUpVector());
    
    // Set model transform
    if (setModelTransform && graphics->NeedParameterUpdate(VSP_MODEL, worldTransform_))
        graphics->SetShaderParameter(VSP_MODEL, *worldTransform_);
    
    // Set skinning transforms
    if (shaderData_ && shaderDataSize_)
    {
        if (graphics->NeedParameterUpdate(VSP_SKINMATRICES, shaderData_))
            graphics->SetShaderParameter(VSP_SKINMATRICES, shaderData_, shaderDataSize_);
    }
    
    // Set zone-related shader parameters
    if (zone_)
    {
        if (graphics->NeedParameterUpdate(VSP_AMBIENTSTARTCOLOR, zone_))
            graphics->SetShaderParameter(VSP_AMBIENTSTARTCOLOR, zone_->GetAmbientStartColor());
        if (graphics->NeedParameterUpdate(VSP_AMBIENTENDCOLOR, zone_))
            graphics->SetShaderParameter(VSP_AMBIENTENDCOLOR, zone_->GetAmbientEndColor().ToVector4() - zone_->GetAmbientStartColor().ToVector4());
        
        if (graphics->NeedParameterUpdate(VSP_ZONE, zone_))
        {
            const BoundingBox& box = zone_->GetBoundingBox();
            Vector3 boxSize = box.Size();
            Matrix3x4 adjust(Matrix3x4::IDENTITY);
            adjust.SetScale(Vector3(1.0f / boxSize.x_, 1.0f / boxSize.y_, 1.0f / boxSize.z_));
            adjust.SetTranslation(Vector3(0.5f, 0.5f, 0.5f));
            Matrix3x4 zoneTransform = adjust * zone_->GetWorldTransform().Inverse();
            
            graphics->SetShaderParameter(VSP_ZONE, zoneTransform);
        }
        
        if (graphics->NeedParameterUpdate(PSP_AMBIENTCOLOR, zone_))
            graphics->SetShaderParameter(PSP_AMBIENTCOLOR, zone_->GetAmbientColor());
        
        // If the pass is additive, override fog color to black so that shaders do not need a separate additive path
        BlendMode blend = pass_->GetBlendMode();
        Zone* fogColorZone = (blend == BLEND_ADD || blend == BLEND_ADDALPHA) ? renderer->GetDefaultZone() : zone_;
        if (graphics->NeedParameterUpdate(PSP_FOGCOLOR, fogColorZone))
            graphics->SetShaderParameter(PSP_FOGCOLOR, fogColorZone->GetFogColor());
        
        if (graphics->NeedParameterUpdate(PSP_FOGPARAMS, zone_))
        {
            float farClip = camera_->GetFarClip();
            float nearClip = camera_->GetNearClip();
            float fogStart = Min(zone_->GetFogStart(), farClip);
            float fogEnd = Min(zone_->GetFogEnd(), farClip);
            if (fogStart >= fogEnd * (1.0f - M_LARGE_EPSILON))
                fogStart = fogEnd * (1.0f - M_LARGE_EPSILON);
            float fogRange = Max(fogEnd - fogStart, M_EPSILON);
            Vector4 fogParams(fogStart / farClip, fogEnd / farClip, farClip / fogRange, 0.0f);
            
            graphics->SetShaderParameter(PSP_FOGPARAMS, fogParams);
        }
    }
    
    if (graphics->NeedParameterUpdate(PSP_DEPTHRECONSTRUCT, camera_))
    {
        float farClip = camera_->GetFarClip();
        float nearClip = camera_->GetNearClip();
        Vector4 depthReconstruct(farClip / (farClip - nearClip), -nearClip / (farClip - nearClip), 0.0f, 0.0f);
        
        graphics->SetShaderParameter(PSP_DEPTHRECONSTRUCT, depthReconstruct);
    }
    
    // Set light-related shader parameters
    Light* light = 0;
    Texture2D* shadowMap = 0;
    if (lightQueue_)
    {
        light = lightQueue_->light_;
        shadowMap = lightQueue_->shadowMap_;
        
        if (graphics->NeedParameterUpdate(VSP_LIGHTDIR, light))
            graphics->SetShaderParameter(VSP_LIGHTDIR, light->GetWorldRotation() * Vector3::BACK);
        
        if (graphics->NeedParameterUpdate(VSP_LIGHTPOS, light))
        {
            float atten = 1.0f / Max(light->GetRange(), M_EPSILON);
            graphics->SetShaderParameter(VSP_LIGHTPOS, Vector4(light->GetWorldPosition(), atten));
        }
        
        if (graphics->NeedParameterUpdate(VSP_LIGHTMATRICES, light))
        {
            switch (light->GetLightType())
            {
            case LIGHT_DIRECTIONAL:
                {
                    Matrix4 shadowMatrices[MAX_CASCADE_SPLITS];
                    unsigned numSplits = lightQueue_->shadowSplits_.Size();
                    for (unsigned i = 0; i < numSplits; ++i)
                        CalculateShadowMatrix(shadowMatrices[i], lightQueue_, i, graphics, renderer, Vector3::ZERO);
                    
                    graphics->SetShaderParameter(VSP_LIGHTMATRICES, shadowMatrices[0].GetData(), 16 * numSplits);
                }
                break;
                
            case LIGHT_SPOT:
                {
                    Matrix4 shadowMatrices[2];
                    
                    CalculateSpotMatrix(shadowMatrices[0], light, Vector3::ZERO);
                    bool isShadowed = lightQueue_->shadowMap_ != 0;
                    if (isShadowed)
                        CalculateShadowMatrix(shadowMatrices[1], lightQueue_, 0, graphics, renderer, Vector3::ZERO);
                    
                    graphics->SetShaderParameter(VSP_LIGHTMATRICES, shadowMatrices[0].GetData(), isShadowed ? 32 : 16);
                }
                break;
                
            case LIGHT_POINT:
                {
                    Matrix4 lightVecRot(light->GetWorldRotation().RotationMatrix());
                    graphics->SetShaderParameter(VSP_LIGHTMATRICES, lightVecRot.GetData(), 16);
                }
                break;
            }
        }
        
        if (graphics->NeedParameterUpdate(VSP_VERTEXLIGHTS, lightQueue_))
        {
            Vector4 vertexLights[MAX_VERTEX_LIGHTS * 3];
            const PODVector<Light*>& lights = lightQueue_->vertexLights_;
            
            for (unsigned i = 0; i < lights.Size(); ++i)
            {
                Light* vertexLight = lights[i];
                LightType type = vertexLight->GetLightType();
                
                // Attenuation
                float invRange, cutoff, invCutoff;
                if (type == LIGHT_DIRECTIONAL)
                    invRange = 0.0f;
                else
                    invRange = 1.0f / Max(vertexLight->GetRange(), M_EPSILON);
                if (type == LIGHT_SPOT)
                {
                    cutoff = cosf(vertexLight->GetFov() * 0.5f * M_DEGTORAD);
                    invCutoff = 1.0f / (1.0f - cutoff);
                }
                else
                {
                    cutoff = -1.0f;
                    invCutoff = 1.0f;
                }
                
                // Color
                float fade = 1.0f;
                float fadeEnd = vertexLight->GetDrawDistance();
                float fadeStart = vertexLight->GetFadeDistance();
                
                // Do fade calculation for light if both fade & draw distance defined
                if (vertexLight->GetLightType() != LIGHT_DIRECTIONAL && fadeEnd > 0.0f && fadeStart > 0.0f && fadeStart < fadeEnd)
                    fade = Min(1.0f - (vertexLight->GetDistance() - fadeStart) / (fadeEnd - fadeStart), 1.0f);
                
                Color color = vertexLight->GetColor() * fade;
                vertexLights[i * 3] = Vector4(color.r_, color.g_, color.b_, invRange);
                
                // Direction
                vertexLights[i * 3 + 1] = Vector4(-(vertexLight->GetNode()->GetWorldDirection()), cutoff);
                
                // Position
                vertexLights[i * 3 + 2] = Vector4(vertexLight->GetWorldPosition(), invCutoff);
            }
            
            if (lights.Size())
                graphics->SetShaderParameter(VSP_VERTEXLIGHTS, vertexLights[0].GetData(), lights.Size() * 3 * 4);
        }
        
        if (graphics->NeedParameterUpdate(PSP_LIGHTCOLOR, light))
        {
            float fade = 1.0f;
            float fadeEnd = light->GetDrawDistance();
            float fadeStart = light->GetFadeDistance();
            
            // Do fade calculation for light if both fade & draw distance defined
            if (light->GetLightType() != LIGHT_DIRECTIONAL && fadeEnd > 0.0f && fadeStart > 0.0f && fadeStart < fadeEnd)
                fade = Min(1.0f - (light->GetDistance() - fadeStart) / (fadeEnd - fadeStart), 1.0f);
            
            graphics->SetShaderParameter(PSP_LIGHTCOLOR, Vector4(light->GetColor().RGBValues(),
                light->GetSpecularIntensity()) * fade);
        }
        
        if (graphics->NeedParameterUpdate(PSP_LIGHTDIR, light))
            graphics->SetShaderParameter(PSP_LIGHTDIR, light->GetWorldRotation() * Vector3::BACK);
        
        if (graphics->NeedParameterUpdate(PSP_LIGHTPOS, light))
        {
            float atten = 1.0f / Max(light->GetRange(), M_EPSILON);
            graphics->SetShaderParameter(PSP_LIGHTPOS, Vector4(light->GetWorldPosition() - camera_->GetWorldPosition(), atten));
        }
        
        // Set shadow mapping shader parameters
        if (shadowMap)
        {
            if (graphics->NeedParameterUpdate(PSP_SAMPLEOFFSETS, shadowMap))
            {
                float addX = 1.0f / (float)shadowMap->GetWidth();
                float addY = 1.0f / (float)shadowMap->GetHeight();
                graphics->SetShaderParameter(PSP_SAMPLEOFFSETS, Vector4(addX, addY, 0.0f, 0.0f));
            }
            
            if (graphics->NeedParameterUpdate(PSP_SHADOWCUBEADJUST, light))
            {
                unsigned faceWidth = shadowMap->GetWidth() / 2;
                unsigned faceHeight = shadowMap->GetHeight() / 3;
                float width = (float)shadowMap->GetWidth();
                float height = (float)shadowMap->GetHeight();
                #ifdef USE_OPENGL
                    float mulX = (float)(faceWidth - 3) / width;
                    float mulY = (float)(faceHeight - 3) / height;
                    float addX = 1.5f / width;
                    float addY = 1.5f / height;
                #else
                    float mulX = (float)(faceWidth - 4) / width;
                    float mulY = (float)(faceHeight - 4) / height;
                    float addX = 2.5f / width;
                    float addY = 2.5f / height;
                #endif
                // If using 4 shadow samples, offset the position diagonally by half pixel
                if (renderer->GetShadowQuality() & SHADOWQUALITY_HIGH_16BIT)
                {
                    addX -= 0.5f / width;
                    addY -= 0.5f / height;
                }
                // If using 2 shadow samples (fallback mode), offset the position horizontally only
                if (graphics->GetFallback())
                    addX -= 0.5f / width;
                graphics->SetShaderParameter(PSP_SHADOWCUBEADJUST, Vector4(mulX, mulY, addX, addY));
            }
            
            if (graphics->NeedParameterUpdate(PSP_SHADOWDEPTHFADE, light))
            {
                // Note: we use the shadow camera of the first cube face. All are assumed to use the same projection
                Camera* shadowCamera = lightQueue_->shadowSplits_[0].shadowCamera_;
                float nearClip = shadowCamera->GetNearClip();
                float farClip = shadowCamera->GetFarClip();
                float q = farClip / (farClip - nearClip);
                float r = -q * nearClip;
                
                const CascadeParameters& parameters = light->GetShadowCascade();
                float viewFarClip = camera_->GetFarClip();
                float shadowRange = parameters.GetShadowRange();
                float fadeStart = parameters.fadeStart_ * shadowRange / viewFarClip;
                float fadeEnd = shadowRange / viewFarClip;
                float fadeRange = fadeEnd - fadeStart;
                
                graphics->SetShaderParameter(PSP_SHADOWDEPTHFADE, Vector4(q, r, fadeStart, 1.0f / fadeRange));
            }
            
            if (graphics->NeedParameterUpdate(PSP_SHADOWINTENSITY, light))
            {
                float intensity = light->GetShadowIntensity();
                float fadeStart = light->GetShadowFadeDistance();
                float fadeEnd = light->GetShadowDistance();
                if (fadeStart > 0.0f && fadeEnd > 0.0f && fadeEnd > fadeStart)
                    intensity = Lerp(intensity, 1.0f, Clamp((light->GetDistance() - fadeStart) / (fadeEnd - fadeStart), 0.0f, 1.0f));
                float pcfValues = (1.0f - intensity);
                float samples = 4.0f;
                float fallbackBias = 0.0f;
                // Fallback mode requires manual depth biasing. We do not do proper slope scale biasing,
                // instead just fudge the bias values together
                if (graphics->GetFallback())
                {
                    samples = 2.0f;
                    fallbackBias = graphics->GetDepthConstantBias() + 2.0f * graphics->GetDepthSlopeScaledBias() *
                        graphics->GetDepthConstantBias();
                }
                graphics->SetShaderParameter(PSP_SHADOWINTENSITY, Vector4(pcfValues, pcfValues / samples, intensity, fallbackBias));
            }
            
            if (graphics->NeedParameterUpdate(PSP_SHADOWSPLITS, light))
            {
                Vector4 lightSplits(M_LARGE_VALUE, M_LARGE_VALUE, M_LARGE_VALUE, M_LARGE_VALUE);
                if (lightQueue_->shadowSplits_.Size() > 1)
                    lightSplits.x_ = lightQueue_->shadowSplits_[0].farSplit_ / camera_->GetFarClip();
                if (lightQueue_->shadowSplits_.Size() > 2)
                    lightSplits.y_ = lightQueue_->shadowSplits_[1].farSplit_ / camera_->GetFarClip();
                if (lightQueue_->shadowSplits_.Size() > 3)
                    lightSplits.z_ = lightQueue_->shadowSplits_[2].farSplit_ / camera_->GetFarClip();
                
                graphics->SetShaderParameter(PSP_SHADOWSPLITS, lightSplits);
            }
        }
        
        if (graphics->NeedParameterUpdate(PSP_LIGHTMATRICES, light))
        {
            switch (light->GetLightType())
            {
            case LIGHT_DIRECTIONAL:
                {
                    Matrix4 shadowMatrices[MAX_CASCADE_SPLITS];
                    unsigned numSplits = lightQueue_->shadowSplits_.Size();
                    for (unsigned i = 0; i < numSplits; ++i)
                        CalculateShadowMatrix(shadowMatrices[i], lightQueue_, i, graphics, renderer, camera_->GetWorldPosition());
                    
                    graphics->SetShaderParameter(PSP_LIGHTMATRICES, shadowMatrices[0].GetData(), 16 * numSplits);
                }
                break;
                
            case LIGHT_SPOT:
                {
                    Matrix4 shadowMatrices[2];
                    
                    CalculateSpotMatrix(shadowMatrices[0], light, camera_->GetWorldPosition());
                    bool isShadowed = lightQueue_->shadowMap_ != 0;
                    if (isShadowed)
                        CalculateShadowMatrix(shadowMatrices[1], lightQueue_, 0, graphics, renderer, camera_->GetWorldPosition());
                    
                    graphics->SetShaderParameter(PSP_LIGHTMATRICES, shadowMatrices[0].GetData(), isShadowed ? 32 : 16);
                }
                break;
                
            case LIGHT_POINT:
                {
                    Matrix4 lightVecRot(light->GetWorldRotation().RotationMatrix());
                    graphics->SetShaderParameter(PSP_LIGHTMATRICES, lightVecRot.GetData(), 16);
                }
                break;
            }
        }
    }
    
    // Set material-specific shader parameters and textures
    if (material_)
    {
        const HashMap<StringHash, MaterialShaderParameter>& parameters = material_->GetShaderParameters();
        for (HashMap<StringHash, MaterialShaderParameter>::ConstIterator i = parameters.Begin(); i != parameters.End(); ++i)
        {
            if (graphics->NeedParameterUpdate(i->first_, material_))
                graphics->SetShaderParameter(i->first_, i->second_.value_);
        }
        
        const Vector<SharedPtr<Texture> >& textures = material_->GetTextures();
        if (graphics->NeedTextureUnit(TU_DIFFUSE))
            graphics->SetTexture(TU_DIFFUSE, textures[TU_DIFFUSE]);
        if (graphics->NeedTextureUnit(TU_NORMAL))
            graphics->SetTexture(TU_NORMAL, textures[TU_NORMAL]);
        if (graphics->NeedTextureUnit(TU_SPECULAR))
            graphics->SetTexture(TU_NORMAL, textures[TU_SPECULAR]);
        if (graphics->NeedTextureUnit(TU_DETAIL))
            graphics->SetTexture(TU_DETAIL, textures[TU_DETAIL]);
        if (graphics->NeedTextureUnit(TU_ENVIRONMENT))
            graphics->SetTexture(TU_ENVIRONMENT, textures[TU_ENVIRONMENT]);
    }
    
    // Set light-related textures
    if (light)
    {
        if (shadowMap && graphics->NeedTextureUnit(TU_SHADOWMAP))
            graphics->SetTexture(TU_SHADOWMAP, shadowMap);
        if (graphics->NeedTextureUnit(TU_LIGHTRAMP))
        {
            Texture* rampTexture = light->GetRampTexture();
            if (!rampTexture)
                rampTexture = renderer->GetDefaultLightRamp();
            graphics->SetTexture(TU_LIGHTRAMP, rampTexture);
        }
        if (graphics->NeedTextureUnit(TU_LIGHTSHAPE))
        {
            Texture* shapeTexture = light->GetShapeTexture();
            if (!shapeTexture && light->GetLightType() == LIGHT_SPOT)
                shapeTexture = renderer->GetDefaultLightSpot();
            graphics->SetTexture(TU_LIGHTSHAPE, shapeTexture);
        }
    }
}

void Batch::Draw(Graphics* graphics, Renderer* renderer) const
{
    Prepare(graphics, renderer);
    geometry_->Draw(graphics);
}

void BatchGroup::SetTransforms(Renderer* renderer, void* lockedData, unsigned& freeIndex)
{
    // Do not use up buffer space if not going to draw as instanced
    if (geometry_->GetIndexCount() > (unsigned)renderer->GetMaxInstanceTriangles() * 3)
        return;
    
    startIndex_ = freeIndex;
    Matrix3x4* dest = (Matrix3x4*)lockedData;
    dest += freeIndex;
    
    for (unsigned i = 0; i < instances_.Size(); ++i)
        *dest++ = *instances_[i].worldTransform_;
    
    freeIndex += instances_.Size();
}

void BatchGroup::Draw(Graphics* graphics, Renderer* renderer) const
{
    if (!instances_.Size())
        return;
    
    // Draw as individual objects if instancing not supported
    VertexBuffer* instanceBuffer = renderer->GetInstancingBuffer();
    if (!instanceBuffer || geometry_->GetIndexCount() > (unsigned)renderer->GetMaxInstanceTriangles() * 3)
    {
        Batch::Prepare(graphics, renderer, false);
        
        graphics->SetIndexBuffer(geometry_->GetIndexBuffer());
        graphics->SetVertexBuffers(geometry_->GetVertexBuffers(), geometry_->GetVertexElementMasks());
        
        for (unsigned i = 0; i < instances_.Size(); ++i)
        {
            graphics->SetShaderParameter(VSP_MODEL, *instances_[i].worldTransform_);
            graphics->Draw(geometry_->GetPrimitiveType(), geometry_->GetIndexStart(), geometry_->GetIndexCount(),
                geometry_->GetVertexStart(), geometry_->GetVertexCount());
        }
        
        graphics->ClearTransformSources();
    }
    else
    {
        Batch::Prepare(graphics, renderer, false);
        
        // Get the geometry vertex buffers, then add the instancing stream buffer
        // Hack: use a const_cast to avoid dynamic allocation of new temp vectors
        Vector<SharedPtr<VertexBuffer> >& vertexBuffers = const_cast<Vector<SharedPtr<VertexBuffer> >&>
            (geometry_->GetVertexBuffers());
        PODVector<unsigned>& elementMasks = const_cast<PODVector<unsigned>&>(geometry_->GetVertexElementMasks());
        vertexBuffers.Push(SharedPtr<VertexBuffer>(instanceBuffer));
        elementMasks.Push(instanceBuffer->GetElementMask());
        
        // No stream offset support, instancing buffer not pre-filled with transforms: have to lock and fill now
        if (startIndex_ == M_MAX_UNSIGNED)
        {
            unsigned startIndex = 0;
            while (startIndex < instances_.Size())
            {
                unsigned instances = instances_.Size() - startIndex;
                if (instances > instanceBuffer->GetVertexCount())
                    instances = instanceBuffer->GetVertexCount();
                
                // Lock the instance stream buffer and copy the transforms
                void* data = instanceBuffer->Lock(0, instances, LOCK_DISCARD);
                if (!data)
                {
                    // Remember to remove the instancing buffer and element mask
                    vertexBuffers.Pop();
                    elementMasks.Pop();
                    return;
                }
                Matrix3x4* dest = (Matrix3x4*)data;
                for (unsigned i = 0; i < instances; ++i)
                    dest[i] = *instances_[i + startIndex].worldTransform_;
                instanceBuffer->Unlock();
                
                graphics->SetIndexBuffer(geometry_->GetIndexBuffer());
                graphics->SetVertexBuffers(vertexBuffers, elementMasks);
                graphics->DrawInstanced(geometry_->GetPrimitiveType(), geometry_->GetIndexStart(), geometry_->GetIndexCount(),
                    geometry_->GetVertexStart(), geometry_->GetVertexCount(), instances);
                
                startIndex += instances;
            }
        }
        // Stream offset supported, and instancing buffer has been already filled, so just draw
        else
        {
            graphics->SetIndexBuffer(geometry_->GetIndexBuffer());
            graphics->SetVertexBuffers(vertexBuffers, elementMasks, startIndex_);
            graphics->DrawInstanced(geometry_->GetPrimitiveType(), geometry_->GetIndexStart(), geometry_->GetIndexCount(),
                geometry_->GetVertexStart(), geometry_->GetVertexCount(), instances_.Size());
        }
        
        // Remove the instancing buffer & element mask now
        vertexBuffers.Pop();
        elementMasks.Pop();
    }
}

void BatchQueue::Clear()
{
    batches_.Clear();
    sortedBaseBatches_.Clear();
    sortedBatches_.Clear();
    baseBatchGroups_.Clear();
    batchGroups_.Clear();
}

void BatchQueue::AddBatch(const Batch& batch)
{
    // Important: this function does not check whether the batch can actually be instanced. It must have been checked before,
    // including setting the correct vertex shader (non-instanced or instanced)
    if (batch.geometryType_ != GEOM_INSTANCED)
        batches_.Push(batch);
    else
    {
        Map<BatchGroupKey, BatchGroup>* groups = batch.isBase_ ? &baseBatchGroups_ : &batchGroups_;
        BatchGroupKey key(batch);
        
        Map<BatchGroupKey, BatchGroup>::Iterator i = groups->Find(key);
        if (i == groups->End())
        {
            // Create a new group based on the batch
            BatchGroup newGroup(batch);
            newGroup.instances_.Push(InstanceData(batch.worldTransform_, batch.distance_));
            groups->Insert(MakePair(key, newGroup));
        }
        else
            i->second_.instances_.Push(InstanceData(batch.worldTransform_, batch.distance_));
    }
}

void BatchQueue::SortBackToFront()
{
    sortedBaseBatches_.Clear();
    sortedBatches_.Resize(batches_.Size());
    
    for (unsigned i = 0; i < batches_.Size(); ++i)
        sortedBatches_[i] = &batches_[i];
    
    Sort(sortedBatches_.Begin(), sortedBatches_.End(), CompareBatchesBackToFront);
    
    // Do not actually sort batch groups, just list them
    sortedBaseBatchGroups_.Resize(baseBatchGroups_.Size());
    sortedBatchGroups_.Resize(batchGroups_.Size());
    
    unsigned index = 0;
    for (Map<BatchGroupKey, BatchGroup>::Iterator i = baseBatchGroups_.Begin(); i != baseBatchGroups_.End(); ++i)
        sortedBaseBatchGroups_[index++] = &i->second_;
    index = 0;
    for (Map<BatchGroupKey, BatchGroup>::Iterator i = batchGroups_.Begin(); i != batchGroups_.End(); ++i)
        sortedBatchGroups_[index++] = &i->second_;
}

void BatchQueue::SortFrontToBack()
{
    sortedBaseBatches_.Clear();
    sortedBatches_.Clear();
    
    // Must explicitly divide into base and non-base batches, so that priorities do not get mixed up between
    // instanced and non-instanced batches
    for (unsigned i = 0; i < batches_.Size(); ++i)
    {
        if (batches_[i].isBase_)
            sortedBaseBatches_.Push(&batches_[i]);
        else
            sortedBatches_.Push(&batches_[i]);
    }
    
    Sort(sortedBaseBatches_.Begin(), sortedBaseBatches_.End(), CompareBatchesFrontToBack);
    Sort(sortedBatches_.Begin(), sortedBatches_.End(), CompareBatchesFrontToBack);
    
    // Sort each group front to back
    for (Map<BatchGroupKey, BatchGroup>::Iterator i = baseBatchGroups_.Begin(); i != baseBatchGroups_.End(); ++i)
        Sort(i->second_.instances_.Begin(), i->second_.instances_.End(), CompareInstancesFrontToBack);
    for (Map<BatchGroupKey, BatchGroup>::Iterator i = batchGroups_.Begin(); i != batchGroups_.End(); ++i)
        Sort(i->second_.instances_.Begin(), i->second_.instances_.End(), CompareInstancesFrontToBack);
    
    // Now sort batch groups by the distance of the first batch
    sortedBaseBatchGroups_.Resize(baseBatchGroups_.Size());
    sortedBatchGroups_.Resize(batchGroups_.Size());
    
    unsigned index = 0;
    for (Map<BatchGroupKey, BatchGroup>::Iterator i = baseBatchGroups_.Begin(); i != baseBatchGroups_.End(); ++i)
        sortedBaseBatchGroups_[index++] = &i->second_;
    index = 0;
    for (Map<BatchGroupKey, BatchGroup>::Iterator i = batchGroups_.Begin(); i != batchGroups_.End(); ++i)
        sortedBatchGroups_[index++] = &i->second_;
    
    Sort(sortedBaseBatchGroups_.Begin(), sortedBaseBatchGroups_.End(), CompareBatchGroupsFrontToBack);
    Sort(sortedBatchGroups_.Begin(), sortedBatchGroups_.End(), CompareBatchGroupsFrontToBack);
}

void BatchQueue::SetTransforms(Renderer* renderer, void* lockedData, unsigned& freeIndex)
{
    for (Map<BatchGroupKey, BatchGroup>::Iterator i = baseBatchGroups_.Begin(); i != baseBatchGroups_.End(); ++i)
        i->second_.SetTransforms(renderer, lockedData, freeIndex);
    for (Map<BatchGroupKey, BatchGroup>::Iterator i = batchGroups_.Begin(); i != batchGroups_.End(); ++i)
        i->second_.SetTransforms(renderer, lockedData, freeIndex);
}

unsigned BatchQueue::GetNumInstances(Renderer* renderer) const
{
    unsigned total = 0;
    unsigned maxIndexCount = renderer->GetMaxInstanceTriangles() * 3;
    
    // This is for the purpose of calculating how much space is needed in the instancing buffer. Do not add groups
    // that have too many triangles
    for (Map<BatchGroupKey, BatchGroup>::ConstIterator i = baseBatchGroups_.Begin(); i != baseBatchGroups_.End(); ++i)
    {
        if (i->second_.geometry_->GetIndexCount() <= maxIndexCount)
            total += i->second_.instances_.Size();
    }
    for (Map<BatchGroupKey, BatchGroup>::ConstIterator i = batchGroups_.Begin(); i != batchGroups_.End(); ++i)
    {
        if (i->second_.geometry_->GetIndexCount() <= maxIndexCount)
            total += i->second_.instances_.Size();
    }
    
    return total;
}
