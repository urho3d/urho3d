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
#include "PixelShader.h"
#include "Profiler.h"
#include "Sort.h"
#include "Technique.h"
#include "Texture2D.h"
#include "VertexBuffer.h"
#include "VertexShader.h"

#include "DebugNew.h"

inline bool CompareBatchesFrontToBack(Batch* lhs, Batch* rhs)
{
    if (lhs->sortKey_ == rhs->sortKey_)
        return lhs->distance_ < rhs->distance_;
    else
        return lhs->sortKey_ < rhs->sortKey_;
}

inline bool CompareBatchesBackToFront(Batch* lhs, Batch* rhs)
{
    if (lhs->distance_ == rhs->distance_)
        return lhs->sortKey_ < rhs->sortKey_;
    else
        return lhs->distance_ > rhs->distance_;
}

inline bool CompareInstancesFrontToBack(const InstanceData& lhs, const InstanceData& rhs)
{
    return lhs.distance_ < rhs.distance_;
}

void Batch::CalculateSortKey()
{
    unsigned light = (*((unsigned*)&light_) / sizeof(Light)) & 0x7fff;
    unsigned pass = (*((unsigned*)&pass_) / sizeof(Pass)) & 0xffff;
    unsigned material = (*((unsigned*)&material_) / sizeof(Material)) & 0xffff;
    unsigned geometry = (*((unsigned*)&geometry_) / sizeof(Geometry)) & 0xffff;
    if (hasPriority_)
        light |= 0x8000;
    sortKey_ = (((unsigned long long)light) << 48) || (((unsigned long long)pass) << 32) ||
        (((unsigned long long)material) << 16) || geometry;
}

void Batch::Prepare(Graphics* graphics, bool SetModelTransform) const
{
    if ((!vertexShader_) || (!pixelShader_))
        return;
    
    // Set pass / material-specific renderstates
    if ((pass_) && (material_))
    {
        if (pass_->GetAlphaTest())
            graphics->SetAlphaTest(true, CMP_GREATEREQUAL, 0.5f);
        else
            graphics->SetAlphaTest(false);
        
        graphics->SetBlendMode(pass_->GetBlendMode());
        graphics->SetCullMode(pass_->GetType() != PASS_SHADOW ? material_->GetCullMode() : material_->GetShadowCullMode());
        graphics->SetDepthTest(pass_->GetDepthTestMode());
        graphics->SetDepthWrite(pass_->GetDepthWrite());
        
        const Vector<SharedPtr<Texture> >& textures = material_->GetTextures();
        
        if (pixelShader_->HasTextureUnit(TU_DIFFUSE))
            graphics->SetTexture(TU_DIFFUSE, textures[TU_DIFFUSE]);
        if (pixelShader_->HasTextureUnit(TU_NORMAL))
            graphics->SetTexture(TU_NORMAL, textures[TU_NORMAL]);
        if (pixelShader_->HasTextureUnit(TU_SPECULAR))
            graphics->SetTexture(TU_SPECULAR, textures[TU_SPECULAR]);
        if (pixelShader_->HasTextureUnit(TU_DETAIL))
            graphics->SetTexture(TU_DETAIL, textures[TU_DETAIL]);
        if (pixelShader_->HasTextureUnit(TU_ENVIRONMENT))
            graphics->SetTexture(TU_ENVIRONMENT, textures[TU_ENVIRONMENT]);
        if (!light_)
        {
            if (pixelShader_->HasTextureUnit(TU_EMISSIVE))
                graphics->SetTexture(TU_EMISSIVE, textures[TU_EMISSIVE]);
        }
    }
    
    // Set light-related textures
    Texture2D* shadowMap = 0;
    if (light_)
    {
        shadowMap = light_->GetShadowMap();
        
        if ((shadowMap) && (pixelShader_->HasTextureUnit(TU_SHADOWMAP)))
            graphics->SetTexture(TU_SHADOWMAP, shadowMap);
        if (pixelShader_->HasTextureUnit(TU_LIGHTRAMP))
            graphics->SetTexture(TU_LIGHTRAMP, light_->GetRampTexture());
        if (pixelShader_->HasTextureUnit(TU_LIGHTSPOT))
            graphics->SetTexture(TU_LIGHTSPOT, light_->GetShapeTexture());
    }
    
    // Set shaders
    graphics->SetShaders(vertexShader_, pixelShader_);
    
    // Set viewport parameters
    if (vertexShader_->NeedParameterUpdate(VSP_CAMERAPOS, camera_))
        graphics->SetVertexShaderParameter(VSP_CAMERAPOS, camera_->GetWorldPosition());
    
    if (vertexShader_->NeedParameterUpdate(VSP_CAMERAROT, camera_))
        graphics->SetVertexShaderParameter(VSP_CAMERAROT, camera_->GetWorldTransform().GetRotationMatrix());
    
    if (vertexShader_->NeedParameterUpdate(VSP_DEPTHMODE, camera_))
    {
        Vector4 depthMode = Vector4::ZERO;
        if (camera_->IsOrthographic())
            depthMode.z_ = 1.0f;
        else
            depthMode.w_ = 1.0f / camera_->GetFarClip();
        
        graphics->SetVertexShaderParameter(VSP_DEPTHMODE, depthMode);
    }
    
    // Set transforms
    if ((SetModelTransform) && (vertexShader_->NeedParameterUpdate(VSP_MODEL, worldTransform_)))
        graphics->SetVertexShaderParameter(VSP_MODEL, *worldTransform_);
    
    if ((shadowMap) && (vertexShader_->NeedParameterUpdate(VSP_SHADOWPROJ, light_)))
    {
        Camera* shadowCamera = light_->GetShadowCamera();
        Matrix4x3 shadowView(shadowCamera->GetInverseWorldTransform());
        Matrix4 shadowProj(shadowCamera->GetProjection());
        
        Matrix4 texAdjust(Matrix4::IDENTITY);
        float offset = 0.5f + 0.5f / (float)shadowMap->GetWidth();
        texAdjust.SetTranslation(Vector3(offset, offset, 0.0f));
        texAdjust.SetScale(Vector3(0.5f, -0.5f, 1.0f));
        
        graphics->SetVertexShaderParameter(VSP_SHADOWPROJ, texAdjust * shadowProj * shadowView);
    }
    
    if ((light_) && (vertexShader_->NeedParameterUpdate(VSP_SPOTPROJ, light_)))
    {
        const Matrix4x3& transform = light_->GetWorldTransform();
        Matrix4x3 spotView(transform.GetTranslation(), transform.GetRotation(), 1.0f);
        
        Matrix4 spotProj(Matrix4::ZERO);
        // Make the projected light slightly smaller than the shadow map to prevent light spill
        float h = 1.005f / tanf(light_->GetFov() * M_DEGTORAD * 0.5f);
        float w = h / light_->GetAspectRatio();
        spotProj.m00_ = w;
        spotProj.m11_ = h;
        spotProj.m22_ = 1.0f / Max(light_->GetRange(), M_EPSILON);
        spotProj.m32_ = 1.0f;
        
        Matrix4 texAdjust(Matrix4::IDENTITY);
        texAdjust.SetTranslation(Vector3(0.5f, 0.5f, 0.0f));
        texAdjust.SetScale(Vector3(0.5f, -0.5f, 1.0f));
        
        graphics->SetVertexShaderParameter(VSP_SPOTPROJ, texAdjust * spotProj * spotView.GetInverse());
    }
    
    if (overrideView_)
    {
        // If we override the view matrix, also disable any projection jittering
        /// \todo This may not be correct in all cases (skybox rendering?)
        if (vertexShader_->NeedParameterUpdate(VSP_VIEWPROJ, &Matrix4x3::IDENTITY))
            graphics->SetVertexShaderParameter(VSP_VIEWPROJ, camera_->GetProjection(false));
    }
    else
    {
        if (vertexShader_->NeedParameterUpdate(VSP_VIEWPROJ, camera_))
            graphics->SetVertexShaderParameter(VSP_VIEWPROJ, camera_->GetProjection() *
                camera_->GetInverseWorldTransform());
    }
    
    // Set material's vertex shader parameters
    if (material_)
    {
        const Map<VSParameter, Vector4>& parameters = material_->GetVertexShaderParameters();
        for (Map<VSParameter, Vector4>::ConstIterator i = parameters.Begin(); i != parameters.End(); ++i)
        {
            if (vertexShader_->NeedParameterUpdate(i->first_, material_))
                graphics->SetVertexShaderParameter(i->first_, i->second_);
        }
    }
    
    if (vertexShader_->NeedParameterUpdate(VSP_VIEWRIGHTVECTOR, camera_))
        graphics->SetVertexShaderParameter(VSP_VIEWRIGHTVECTOR, camera_->GetRightVector());
    
    if (vertexShader_->NeedParameterUpdate(VSP_VIEWUPVECTOR, camera_))
        graphics->SetVertexShaderParameter(VSP_VIEWUPVECTOR, camera_->GetUpVector());
    
    // Set skinning transforms
    if ((shaderData_) && (shaderDataSize_))
    {
        if (vertexShader_->NeedParameterUpdate(VSP_SKINMATRICES, shaderData_))
            graphics->SetVertexShaderParameter(VSP_SKINMATRICES, (const float*)shaderData_, shaderDataSize_);
    }
    
    // Set light-related parameters
    if (light_)
    {
        if (pixelShader_->NeedParameterUpdate(PSP_LIGHTATTEN, light_))
        {
            Vector4 light_Atten(1.0f / Max(light_->GetRange(), M_EPSILON), 0.0f, 0.0f, 0.0f);
            graphics->SetPixelShaderParameter(PSP_LIGHTATTEN, light_Atten);
        }
        
        if (pixelShader_->NeedParameterUpdate(PSP_LIGHTCOLOR, light_))
        {
            float fade = 1.0f;
            float fadeEnd = light_->GetDrawDistance();
            float fadeStart = light_->GetFadeDistance();
            
            // Do fade calculation for light if both fade & draw distance defined
            if ((light_->GetLightType() != LIGHT_DIRECTIONAL) && (fadeEnd > 0.0f) && (fadeStart > 0.0f) && (fadeStart < fadeEnd))
                fade = Min(1.0f - (light_->GetDistance() - fadeStart) / (fadeEnd - fadeStart), 1.0f);
            
            graphics->SetPixelShaderParameter(PSP_LIGHTCOLOR, Vector4(light_->GetColor().GetRGB(),
                light_->GetSpecularIntensity()) * fade);
        }
        
        if (pixelShader_->NeedParameterUpdate(PSP_LIGHTDIR, light_))
            graphics->SetPixelShaderParameter(PSP_LIGHTDIR, light_->GetWorldRotation() * Vector3::BACK);
        
        if (pixelShader_->NeedParameterUpdate(PSP_LIGHTPOS, light_))
            graphics->SetPixelShaderParameter(PSP_LIGHTPOS, light_->GetWorldPosition() - camera_->GetWorldPosition());
        
        if (pixelShader_->NeedParameterUpdate(PSP_LIGHTSPLITS, light_))
        {
            float nearFadeRange = light_->GetNearFadeRange();
            float farFadeRange = light_->GetFarFadeRange();
            float nearFadeStart = light_->GetNearSplit() - nearFadeRange;
            float farFadeStart = light_->GetFarSplit() - farFadeRange;
            float depthRange = camera_->GetFarClip();
            
            graphics->SetPixelShaderParameter(PSP_LIGHTSPLITS, Vector4(nearFadeStart / depthRange, 1.0f / (nearFadeRange / depthRange),
                farFadeStart / depthRange, 1.0f / (farFadeRange / depthRange)));
        }
        
        if (pixelShader_->NeedParameterUpdate(PSP_LIGHTVECROT, light_))
        {
            Matrix4x3 light_VecRot;
            // Use original light if available (split lights)
            Light* original = light_->GetOriginalLight();
            if (!original)
                light_VecRot = Matrix4x3(Vector3::ZERO, light_->GetWorldRotation(), Vector3::UNITY);
            else
                light_VecRot = Matrix4x3(Vector3::ZERO, original->GetWorldRotation(), Vector3::UNITY);
            
            graphics->SetPixelShaderParameter(PSP_LIGHTVECROT, light_VecRot);
        }
    }
    
    // Set material's pixel shader parameters
    if (material_)
    {
        const Map<PSParameter, Vector4>& parameters = material_->GetPixelShaderParameters();
        for (Map<PSParameter, Vector4>::ConstIterator i = parameters.Begin(); i != parameters.End(); ++i)
        {
            if (pixelShader_->NeedParameterUpdate(i->first_, material_))
                graphics->SetPixelShaderParameter(i->first_, i->second_);
        }
    }
    
    // Set shadow & spotlight projection parameters
    if (shadowMap)
    {
        if (pixelShader_->NeedParameterUpdate(PSP_SAMPLEOFFSETS, shadowMap))
        {
            float invWidth = 1.0f / (float)shadowMap->GetWidth();
            graphics->SetPixelShaderParameter(PSP_SAMPLEOFFSETS, Vector4(0.5f * invWidth, -0.5f * invWidth, 0.0f, 0.0f));
        }
        
        if (pixelShader_->NeedParameterUpdate(PSP_SHADOWINTENSITY, light_))
        {
            float intensity = light_->GetShadowIntensity();
            float fadeStart = light_->GetShadowFadeDistance();
            float fadeEnd = light_->GetShadowDistance();
            if ((fadeStart > 0.0f) && (fadeEnd > 0.0f) && (fadeEnd > fadeStart))
                intensity = Lerp(intensity, 1.0f, Clamp((light_->GetDistance() - fadeStart) / (fadeEnd - fadeStart), 0.0f, 1.0f));
            float pcfValues = (1.0f - intensity) * 0.25f;
            graphics->SetPixelShaderParameter(PSP_SHADOWINTENSITY, Vector4(pcfValues, intensity, 0.0f, 0.0f));
        }
        
        if (pixelShader_->NeedParameterUpdate(PSP_SHADOWPROJ, light_))
        {
            Camera* shadowCamera = light_->GetShadowCamera();
            Matrix4x3 shadowView(shadowCamera->GetInverseWorldTransform());
            Matrix4 shadowProj(shadowCamera->GetProjection());
            
            Matrix4x3 viewPos(Matrix4x3::IDENTITY);
            viewPos.SetTranslation(camera_->GetWorldPosition());
            
            Matrix4 texAdjust(Matrix4::IDENTITY);
            float offset = 0.5f + 0.5f / (float)shadowMap->GetWidth();
            texAdjust.SetTranslation(Vector3(offset, offset, 0.0f));
            texAdjust.SetScale(Vector3(0.5f, -0.5f, 1.0f));
            
            graphics->SetPixelShaderParameter(PSP_SHADOWPROJ, texAdjust * shadowProj * shadowView * viewPos);
        }
    }
    
    if ((light_) && (pixelShader_->NeedParameterUpdate(PSP_SPOTPROJ, light_)))
    {
        Matrix4x3 spotView(light_->GetWorldPosition(), light_->GetWorldRotation(), 1.0f);
        Matrix4 spotProj(Matrix4::IDENTITY);
        
        // Make the projected light slightly smaller than the shadow map to prevent light spill
        float h = 1.005f / tanf(light_->GetFov() * M_DEGTORAD * 0.5f);
        float w = h / light_->GetAspectRatio();
        spotProj.m00_ = w;
        spotProj.m11_ = h;
        spotProj.m22_ = 1.0f / Max(light_->GetRange(), M_EPSILON);
        spotProj.m32_ = 1.0f;
        
        Matrix4x3 viewPos(Matrix4x3::IDENTITY);
        viewPos.SetTranslation(camera_->GetWorldPosition());
        
        Matrix4 texAdjust(Matrix4::IDENTITY);
        texAdjust.SetTranslation(Vector3(0.5f, 0.5f, 0.0f));
        texAdjust.SetScale(Vector3(0.5f, -0.5f, 1.0f));
        
        graphics->SetPixelShaderParameter(PSP_SPOTPROJ, texAdjust * spotProj * spotView.GetInverse() * viewPos);
    }
}

void Batch::Draw(Graphics* graphics) const
{
    Prepare(graphics);
    geometry_->Draw(graphics);
}

void BatchGroup::SetTransforms(void* lockedData, unsigned& freeIndex)
{
    // Do not use up buffer space if not going to draw as instanced
    if (instances_.Size() < MIN_INSTANCES)
        return;
    
    startIndex_ = freeIndex;
    Matrix4x3* dest = (Matrix4x3*)lockedData;
    dest += freeIndex;
    
    for (unsigned i = 0; i < instances_.Size(); ++i)
        *dest++ = *instances_[i].worldTransform_;
    
    freeIndex += instances_.Size();
}

void BatchGroup::Draw(Graphics* graphics, VertexBuffer* buffer) const
{
    if (!instances_.Size())
        return;
    
    // Construct a temporary batch for rendering
    Batch batch;
    batch.geometry_ = geometry_;
    batch.material_ = material_;
    batch.pass_ = pass_;
    batch.vertexShader_ = vertexShader_;
    batch.pixelShader_ = pixelShader_;
    batch.camera_ = camera_;
    batch.light_ = light_;
    batch.vertexShaderIndex_ = vertexShaderIndex_;
    
    // Draw as individual instances if below minimum size, or if instancing not supported
    if ((instances_.Size() < MIN_INSTANCES) || (!buffer))
    {
        batch.Prepare(graphics, false);
        
        graphics->SetIndexBuffer(geometry_->GetIndexBuffer());
        graphics->SetVertexBuffers(geometry_->GetVertexBuffers(), geometry_->GetVertexElementMasks());
        
        for (unsigned i = 0; i < instances_.Size(); ++i)
        {
            if (vertexShader_->NeedParameterUpdate(VSP_MODEL, instances_[i].worldTransform_))
                graphics->SetVertexShaderParameter(VSP_MODEL, *instances_[i].worldTransform_);
            
            graphics->Draw(geometry_->GetPrimitiveType(), geometry_->GetIndexStart(), geometry_->GetIndexCount(),
                geometry_->GetVertexStart(), geometry_->GetVertexCount());
        }
    }
    else
    {
        // Switch to the instancing vertex shader
        // The indexing is different in the forward lit passes
        Vector<SharedPtr<VertexShader> >& vertexShaders = pass_->GetVertexShaders();
        Vector<SharedPtr<PixelShader> >& pixelShaders = pass_->GetPixelShaders();
        PassType type = pass_->GetType();
        if ((type != PASS_LITBASE) && (type != PASS_LIGHT))
            batch.vertexShader_ = vertexShaders[vertexShaderIndex_ + GEOM_INSTANCED];
        else
            batch.vertexShader_ = vertexShaders[vertexShaderIndex_ + GEOM_INSTANCED * MAX_LIGHT_VS_VARIATIONS];
        
        batch.Prepare(graphics, false);
        
        // Get the geometry vertex buffers, then add the instancing stream buffer
        Vector<SharedPtr<VertexBuffer> > vertexBuffers = geometry_->GetVertexBuffers();
        PODVector<unsigned> elementMasks = geometry_->GetVertexElementMasks();
        vertexBuffers.Push(SharedPtr<VertexBuffer>(buffer));
        elementMasks.Push(buffer->GetElementMask());
        
        // No stream offset support, instancing buffer not pre-filled with transforms: have to lock and fill now
        if (startIndex_ == M_MAX_UNSIGNED)
        {
            unsigned startIndex = 0;
            while (startIndex < instances_.Size())
            {
                unsigned instances = instances_.Size() - startIndex;
                if (instances > buffer->GetVertexCount())
                    instances = buffer->GetVertexCount();
                
                // Lock the instance stream buffer and copy the transforms
                void* data = buffer->Lock(0, instances, LOCK_DISCARD);
                if (!data)
                    return;
                Matrix4x3* dest = (Matrix4x3*)data;
                for (unsigned i = 0; i < instances; ++i)
                    dest[i] = *instances_[i + startIndex].worldTransform_;
                buffer->Unlock();
                
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
    }
}

void BatchQueue::Clear()
{
    batches_.Clear();
    sortedPriorityBatches_.Clear();
    sortedBatches_.Clear();
    priorityBatchGroups_.Clear();
    batchGroups_.Clear();
}

void BatchQueue::AddBatch(const Batch& batch, bool noInstancing)
{
    // If batch is something else than static, has custom view, or has per-instance shader data defined, can not instance
    if ((noInstancing) || (batch.geometryType_ != GEOM_STATIC) || (batch.overrideView_) || (batch.shaderData_))
        batches_.Push(batch);
    else
    {
        BatchGroupKey key;
        key.light_ = batch.light_;
        key.pass_ = batch.pass_;
        key.material_ = batch.material_;
        key.geometry_ = batch.geometry_;
        
        Map<BatchGroupKey, BatchGroup>* groups = batch.hasPriority_ ? &priorityBatchGroups_ : &batchGroups_;
        
        Map<BatchGroupKey, BatchGroup>::Iterator i = groups->Find(key);
        if (i == groups->End())
        {
            // Create new group
            BatchGroup newGroup;
            newGroup.geometry_ = batch.geometry_;
            newGroup.material_ = batch.material_;
            newGroup.pass_ = batch.pass_;
            newGroup.vertexShader_ = batch.vertexShader_;
            newGroup.pixelShader_ = batch.pixelShader_;
            newGroup.camera_ = batch.camera_;
            newGroup.light_ = batch.light_;
            newGroup.vertexShaderIndex_ = batch.vertexShaderIndex_;
            newGroup.instances_.Push(InstanceData(batch.worldTransform_, batch.distance_));
            groups->Insert(MakePair(key, newGroup));
        }
        else
            i->second_.instances_.Push(InstanceData(batch.worldTransform_, batch.distance_));
    }
}

void BatchQueue::SortBackToFront()
{
    sortedPriorityBatches_.Clear();
    sortedBatches_.Resize(batches_.Size());
    
    for (unsigned i = 0; i < batches_.Size(); ++i)
        sortedBatches_[i] = &batches_[i];
    
    Sort(sortedBatches_.Begin(), sortedBatches_.End(), CompareBatchesBackToFront);
}

void BatchQueue::SortFrontToBack()
{
    sortedPriorityBatches_.Clear();
    sortedBatches_.Clear();
    
    // Must explicitly divide into priority batches and non-priority, so that priorities do not get mixed up between
    // instanced and non-instanced batches
    for (unsigned i = 0; i < batches_.Size(); ++i)
    {
        if (batches_[i].hasPriority_)
            sortedPriorityBatches_.Push(&batches_[i]);
        else
            sortedBatches_.Push(&batches_[i]);
    }
    
    Sort(sortedPriorityBatches_.Begin(), sortedPriorityBatches_.End(), CompareBatchesFrontToBack);
    Sort(sortedBatches_.Begin(), sortedBatches_.End(), CompareBatchesFrontToBack);
    
    // Sort each group front to back
    for (Map<BatchGroupKey, BatchGroup>::Iterator i = priorityBatchGroups_.Begin(); i != priorityBatchGroups_.End(); ++i)
        Sort(i->second_.instances_.Begin(), i->second_.instances_.End(), CompareInstancesFrontToBack);
    for (Map<BatchGroupKey, BatchGroup>::Iterator i = batchGroups_.Begin(); i != batchGroups_.End(); ++i)
        Sort(i->second_.instances_.Begin(), i->second_.instances_.End(), CompareInstancesFrontToBack);
}

void BatchQueue::SetTransforms(void* lockedData, unsigned& freeIndex)
{
    for (Map<BatchGroupKey, BatchGroup>::Iterator i = priorityBatchGroups_.Begin(); i != priorityBatchGroups_.End(); ++i)
        i->second_.SetTransforms(lockedData, freeIndex);
    for (Map<BatchGroupKey, BatchGroup>::Iterator i = batchGroups_.Begin(); i != batchGroups_.End(); ++i)
        i->second_.SetTransforms(lockedData, freeIndex);
}

unsigned BatchQueue::GetNumInstances() const
{
    unsigned total = 0;
    
    // This is for the purpose of calculating how much space is needed in the instancing buffer. Do not add instance counts
    // that are below the minimum threshold for instancing
    for (Map<BatchGroupKey, BatchGroup>::ConstIterator i = priorityBatchGroups_.Begin(); i != priorityBatchGroups_.End(); ++i)
    {
        unsigned instances = i->second_.instances_.Size();
        if (instances >= MIN_INSTANCES)
            total += instances;
    }
    for (Map<BatchGroupKey, BatchGroup>::ConstIterator i = batchGroups_.Begin(); i != batchGroups_.End(); ++i)
    {
        unsigned instances = i->second_.instances_.Size();
        if (instances >= MIN_INSTANCES)
            total += instances;
    }
    
    return total;
}
