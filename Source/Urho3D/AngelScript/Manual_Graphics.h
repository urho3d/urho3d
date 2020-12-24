//
// Copyright (c) 2008-2020 the Urho3D project.
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

#pragma once

#include "../Graphics/AnimationController.h"
#include "../Graphics/IndexBuffer.h"
#include "../Graphics/RenderPath.h"
#include "../Graphics/Texture2D.h"
#include "../Graphics/Animation.h"
#include "../Graphics/AnimationState.h"
#include "../Graphics/AnimationController.h"
#include "../Graphics/GraphicsDefs.h"
#include "../Graphics/Model.h"
#include "../Graphics/AnimatedModel.h"
#include "../Graphics/ParticleEffect.h"
#include "../Graphics/VertexBuffer.h"
#include "../Graphics/Graphics.h"
#include "../Graphics/Octree.h"
#include "../Graphics/TextureCube.h"
#include "../Graphics/Renderer.h"
#include "../Graphics/Technique.h"

namespace Urho3D
{

// Vector<RenderTargetInfo> RenderPath::renderTargets_ | File: ../Graphics/RenderPath.h
RenderTargetInfo* RenderPathGetRenderTarget(unsigned index, RenderPath* ptr);
// Vector<RenderPathCommand> RenderPath::commands_ | File: ../Graphics/RenderPath.h
RenderPathCommand* RenderPathGetCommand(unsigned index, RenderPath* ptr);

#define REGISTER_MANUAL_PART_RenderPath(T, className) \
    /* Vector<RenderTargetInfo> RenderPath::renderTargets_ | File: ../Graphics/RenderPath.h */ \
    engine->RegisterObjectMethod(className, "const RenderTargetInfo& get_renderTargets(uint) const", asFUNCTION(RenderPathGetRenderTarget), asCALL_CDECL_OBJLAST); \
    /* Vector<RenderPathCommand> RenderPath::commands_ | File: ../Graphics/RenderPath.h */ \
    engine->RegisterObjectMethod(className, "const RenderPathCommand& get_commands(uint) const", asFUNCTION(RenderPathGetCommand), asCALL_CDECL_OBJLAST); \

// ========================================================================================

// SharedPtr<Technique> TechniqueEntry::technique_ | File: ../Graphics/Material.h
void TechniqueEntrySetTechnique(Technique* technique, TechniqueEntry* ptr);
// SharedPtr<Technique> TechniqueEntry::technique_ | File: ../Graphics/Material.h
Technique* TechniqueEntryGetTechnique(TechniqueEntry* ptr);

#define REGISTER_MANUAL_PART_TechniqueEntry(T, className) \
    /* SharedPtr<Technique> TechniqueEntry::technique_ | File: ../Graphics/Material.h */ \
    engine->RegisterObjectMethod(className, "void set_technique(Technique@+)", asFUNCTION(TechniqueEntrySetTechnique), asCALL_CDECL_OBJLAST); \
    /* SharedPtr<Technique> TechniqueEntry::technique_ | File: ../Graphics/Material.h */ \
    engine->RegisterObjectMethod(className, "Technique@+ get_technique() const", asFUNCTION(TechniqueEntryGetTechnique), asCALL_CDECL_OBJLAST);

// ========================================================================================

CScriptArray* MaterialGetShaderParameterNames(Material* material);
// const TechniqueEntry& Material::GetTechniqueEntry(unsigned index) const | File: ../Graphics/Material.h
const TechniqueEntry& MaterialGetTechniqueEntry(unsigned index, Material* ptr);

#define REGISTER_MANUAL_PART_Material(T, className) \
    engine->RegisterObjectMethod(className, "Array<String>@ get_shaderParameterNames() const", asFUNCTION(MaterialGetShaderParameterNames), asCALL_CDECL_OBJLAST); \
    /* const TechniqueEntry& Material::GetTechniqueEntry(unsigned index) const | File: ../Graphics/Material.h */ \
    engine->RegisterObjectMethod(className, "const TechniqueEntry& get_techniqueEntries(uint) const", asFUNCTION(MaterialGetTechniqueEntry), asCALL_CDECL_OBJLAST);

// ========================================================================================

VectorBuffer VertexBufferGetData(VertexBuffer* ptr);
// bool VertexBuffer::SetData(const void *data) | File: ../Graphics/VertexBuffer.h
bool VertexBufferSetData(VectorBuffer& src, VertexBuffer* ptr);
// bool VertexBuffer::SetDataRange(const void *data, unsigned start, unsigned count, bool discard=false) | File: ../Graphics/VertexBuffer.h
bool VertexBufferSetDataRange(VectorBuffer& src, unsigned start, unsigned count, bool discard, VertexBuffer* ptr);

#define REGISTER_MANUAL_PART_VertexBuffer(T, className) \
    engine->RegisterObjectMethod(className, "VectorBuffer GetData() const", asFUNCTION(VertexBufferGetData), asCALL_CDECL_OBJLAST); \
    /* bool VertexBuffer::SetData(const void *data) | File: ../Graphics/VertexBuffer.h */ \
    engine->RegisterObjectMethod(className, "bool SetData(VectorBuffer&)", asFUNCTION(VertexBufferSetData), asCALL_CDECL_OBJLAST); \
    /* bool VertexBuffer::SetDataRange(const void *data, unsigned start, unsigned count, bool discard=false) | File: ../Graphics/VertexBuffer.h */ \
    engine->RegisterObjectMethod(className, "bool SetDataRange(VectorBuffer&, uint, uint, bool discard = false)", asFUNCTION(VertexBufferSetDataRange), asCALL_CDECL_OBJLAST);

// ========================================================================================

VectorBuffer IndexBufferGetData(IndexBuffer* ptr);
// bool IndexBuffer::SetData(const void *data) | File: ../Graphics/IndexBuffer.h
bool IndexBufferSetData(VectorBuffer& src, IndexBuffer* ptr);
// bool IndexBuffer::SetDataRange(const void *data, unsigned start, unsigned count, bool discard=false) | File: ../Graphics/IndexBuffer.h
bool IndexBufferSetDataRange(VectorBuffer& src, unsigned start, unsigned count, bool discard, IndexBuffer* ptr);

#define REGISTER_MANUAL_PART_IndexBuffer(T, className) \
    engine->RegisterObjectMethod(className, "VectorBuffer GetData()", asFUNCTION(IndexBufferGetData), asCALL_CDECL_OBJLAST); \
    /* bool IndexBuffer::SetData(const void *data) | File: ../Graphics/IndexBuffer.h */ \
    engine->RegisterObjectMethod(className, "bool SetData(VectorBuffer&)", asFUNCTION(IndexBufferSetData), asCALL_CDECL_OBJLAST); \
    /* bool IndexBuffer::SetDataRange(const void *data, unsigned start, unsigned count, bool discard=false) | File: ../Graphics/IndexBuffer.h */ \
    engine->RegisterObjectMethod(className, "bool SetDataRange(VectorBuffer&, uint, uint, bool discard = false)", asFUNCTION(IndexBufferSetDataRange), asCALL_CDECL_OBJLAST);

// ========================================================================================

#define REGISTER_MANUAL_PART_AnimationTrack(T, className) \
    /* AnimationKeyFrame* AnimationTrack::GetKeyFrame(unsigned index) | File: ../Graphics/Animation.h */ \
    engine->RegisterObjectMethod(className, "const AnimationKeyFrame& get_keyFrames(uint) const", asMETHOD(T, GetKeyFrame), asCALL_THISCALL);

// ========================================================================================

// AnimationTriggerPoint* Animation::GetTrigger(unsigned index) | File: ../Graphics/Animation.h
AnimationTriggerPoint* AnimationGetTrigger(unsigned index, Animation* ptr);

#define REGISTER_MANUAL_PART_Animation(T, className) \
    /* AnimationTriggerPoint* Animation::GetTrigger(unsigned index) | File: ../Graphics/Animation.h */ \
    engine->RegisterObjectMethod(className, "const AnimationTriggerPoint& get_triggers(uint) const", asFUNCTION(AnimationGetTrigger), asCALL_CDECL_OBJLAST);

// ========================================================================================

#define REGISTER_MANUAL_PART_CascadeParameters(T, className) \
    /* Vector4 CascadeParameters::splits_ | File: ../Graphics/Light.h */ \
    engine->RegisterObjectProperty(className, "float split1", offsetof(T, splits_.x_)); \
    /* Vector4 CascadeParameters::splits_ | File: ../Graphics/Light.h */ \
    engine->RegisterObjectProperty(className, "float split2", offsetof(T, splits_.y_)); \
    /* Vector4 CascadeParameters::splits_ | File: ../Graphics/Light.h */ \
    engine->RegisterObjectProperty(className, "float split3", offsetof(T, splits_.z_)); \
    /* Vector4 CascadeParameters::splits_ | File: ../Graphics/Light.h */ \
    engine->RegisterObjectProperty(className, "float split4", offsetof(T, splits_.w_));

// ========================================================================================

// void AnimationState::SetBoneWeight(const String &name, float weight, bool recursive=false) | File: ../Graphics/AnimationState.h
void AnimationStateSetBoneWeight(const String& name, float weight, AnimationState* ptr);

#define REGISTER_MANUAL_PART_AnimationState(T, className) \
    /* void AnimationState::SetBoneWeight(const String &name, float weight, bool recursive=false) | File: ../Graphics/AnimationState.h */ \
    engine->RegisterObjectMethod(className, "void set_boneWeights(const String&in, float)", asFUNCTION(AnimationStateSetBoneWeight), asCALL_CDECL_OBJLAST);

// ========================================================================================

const String& AnimatedModelGetMorphName(unsigned index, AnimatedModel* ptr);
// void AnimatedModel::SetModel(Model *model, bool createBones=true) | File: ../Graphics/AnimatedModel.h
void AnimatedModelSetModel(Model* model, AnimatedModel* ptr);

#define REGISTER_MANUAL_PART_AnimatedModel(T, className) \
    engine->RegisterObjectMethod(className, "const String& get_morphNames(uint) const", asFUNCTION(AnimatedModelGetMorphName), asCALL_CDECL_OBJLAST); \
    /* void AnimatedModel::SetModel(Model *model, bool createBones=true) | File: ../Graphics/AnimatedModel.h */ \
    engine->RegisterObjectMethod(className, "void set_model(Model@+)", asFUNCTION(AnimatedModelSetModel), asCALL_CDECL_OBJLAST);

// ========================================================================================

// const Vector<AnimationControl>& AnimationController::GetAnimations() const | File: ../Graphics/AnimationController.h
unsigned AnimationControllerGetNumAnimations(AnimationController* controller);
// const Vector<AnimationControl>& AnimationController::GetAnimations() const | File: ../Graphics/AnimationController.h
const AnimationControl* AnimationControllerGetAnimation(unsigned index, AnimationController* controller);

#define REGISTER_MANUAL_PART_AnimationController(T, className) \
    /* const Vector<AnimationControl>& AnimationController::GetAnimations() const | File: ../Graphics/AnimationController.h */ \
    engine->RegisterObjectMethod(className, "uint get_numAnimations() const", asFUNCTION(AnimationControllerGetNumAnimations), asCALL_CDECL_OBJLAST); \
    /* const Vector<AnimationControl>& AnimationController::GetAnimations() const | File: ../Graphics/AnimationController.h */ \
    engine->RegisterObjectMethod(className, "const AnimationControl@+ get_animations(uint) const", asFUNCTION(AnimationControllerGetAnimation), asCALL_CDECL_OBJLAST);

// ========================================================================================

// void Graphics::PrecacheShaders(Deserializer &source) | File: ../Graphics/Graphics.h
void GraphicsPrecacheShaders(File* file, Graphics* ptr);
// void Graphics::PrecacheShaders(Deserializer &source) | File: ../Graphics/Graphics.h
void GraphicsPrecacheShadersVectorBuffer(VectorBuffer& buffer, Graphics* ptr);

#define REGISTER_MANUAL_PART_Graphics(T, className) \
    /* void Graphics::PrecacheShaders(Deserializer &source) | File: ../Graphics/Graphics.h */ \
    engine->RegisterObjectMethod(className, "void PrecacheShaders(File@+)", asFUNCTION(GraphicsPrecacheShaders), asCALL_CDECL_OBJLAST); \
    /* void Graphics::PrecacheShaders(Deserializer &source) | File: ../Graphics/Graphics.h */ \
    engine->RegisterObjectMethod(className, "void PrecacheShaders(VectorBuffer&)", asFUNCTION(GraphicsPrecacheShadersVectorBuffer), asCALL_CDECL_OBJLAST);

// ========================================================================================

// Drawable* RayQueryResult::drawable_ | File: ../Graphics/OctreeQuery.h
Drawable* RayQueryResultGetDrawable(RayQueryResult* ptr);
// Node* RayQueryResult::node_ | File: ../Graphics/OctreeQuery.h
Node* RayQueryResultGetNode(RayQueryResult* ptr);

#define REGISTER_MANUAL_PART_RayQueryResult(T, className) \
    /* Drawable* RayQueryResult::drawable_ | File: ../Graphics/OctreeQuery.h */ \
    engine->RegisterObjectMethod(className, "Drawable@+ get_drawable() const", asFUNCTION(RayQueryResultGetDrawable), asCALL_CDECL_OBJLAST); \
    /* Node* RayQueryResult::node_ | File: ../Graphics/OctreeQuery.h */ \
    engine->RegisterObjectMethod(className, "Node@+ get_node() const", asFUNCTION(RayQueryResultGetNode), asCALL_CDECL_OBJLAST);

// ========================================================================================

// void Octree::Raycast(RayOctreeQuery &query) const | File: ../Graphics/Octree.h
CScriptArray* OctreeRaycast(const Ray& ray, RayQueryLevel level, float maxDistance, unsigned char drawableFlags, unsigned viewMask, Octree* ptr);
// void Octree::RaycastSingle(RayOctreeQuery &query) const | File: ../Graphics/Octree.h
RayQueryResult OctreeRaycastSingle(const Ray& ray, RayQueryLevel level, float maxDistance, unsigned char drawableFlags, unsigned viewMask, Octree* ptr);
// void Octree::GetDrawables(OctreeQuery &query) const | File: ../Graphics/Octree.h
CScriptArray* OctreeGetDrawablesPoint(const Vector3& point, unsigned char drawableFlags, unsigned viewMask, Octree* ptr);
// void Octree::GetDrawables(OctreeQuery &query) const | File: ../Graphics/Octree.h
CScriptArray* OctreeGetDrawablesBox(const BoundingBox& box, unsigned char drawableFlags, unsigned viewMask, Octree* ptr);
// void Octree::GetDrawables(OctreeQuery &query) const | File: ../Graphics/Octree.h
CScriptArray* OctreeGetDrawablesFrustum(const Frustum& frustum, unsigned char drawableFlags, unsigned viewMask, Octree* ptr);
// void Octree::GetDrawables(OctreeQuery &query) const | File: ../Graphics/Octree.h
CScriptArray* OctreeGetDrawablesSphere(const Sphere& sphere, unsigned char drawableFlags, unsigned viewMask, Octree* ptr);
// void Octree::GetDrawables(OctreeQuery &query) const | File: ../Graphics/Octree.h
CScriptArray* OctreeGetAllDrawables(unsigned char drawableFlags, unsigned viewMask, Octree* ptr);

#define REGISTER_MANUAL_PART_Octree(T, className) \
    /* void Octree::Raycast(RayOctreeQuery &query) const | File: ../Graphics/Octree.h */ \
    engine->RegisterObjectMethod(className, "Array<RayQueryResult>@ Raycast(const Ray&in, RayQueryLevel level = RAY_TRIANGLE, float maxDistance = M_INFINITY, uint8 drawableFlags = DRAWABLE_ANY, uint viewMask = DEFAULT_VIEWMASK) const", asFUNCTION(OctreeRaycast), asCALL_CDECL_OBJLAST); \
    /* void Octree::RaycastSingle(RayOctreeQuery &query) const | File: ../Graphics/Octree.h */ \
    engine->RegisterObjectMethod(className, "RayQueryResult RaycastSingle(const Ray&in, RayQueryLevel level = RAY_TRIANGLE, float maxDistance = M_INFINITY, uint8 drawableFlags = DRAWABLE_ANY, uint viewMask = DEFAULT_VIEWMASK) const", asFUNCTION(OctreeRaycastSingle), asCALL_CDECL_OBJLAST); \
    /* void Octree::GetDrawables(OctreeQuery &query) const | File: ../Graphics/Octree.h */ \
    engine->RegisterObjectMethod(className, "Array<Drawable@>@ GetDrawables(const Vector3&in, uint8 drawableFlags = DRAWABLE_ANY, uint viewMask = DEFAULT_VIEWMASK)", asFUNCTION(OctreeGetDrawablesPoint), asCALL_CDECL_OBJLAST); \
    /* void Octree::GetDrawables(OctreeQuery &query) const | File: ../Graphics/Octree.h */ \
    engine->RegisterObjectMethod(className, "Array<Drawable@>@ GetDrawables(const BoundingBox&in, uint8 drawableFlags = DRAWABLE_ANY, uint viewMask = DEFAULT_VIEWMASK)", asFUNCTION(OctreeGetDrawablesBox), asCALL_CDECL_OBJLAST); \
    /* void Octree::GetDrawables(OctreeQuery &query) const | File: ../Graphics/Octree.h */ \
    engine->RegisterObjectMethod(className, "Array<Drawable@>@ GetDrawables(const Frustum&in, uint8 drawableFlags = DRAWABLE_ANY, uint viewMask = DEFAULT_VIEWMASK)", asFUNCTION(OctreeGetDrawablesFrustum), asCALL_CDECL_OBJLAST); \
    /* void Octree::GetDrawables(OctreeQuery &query) const | File: ../Graphics/Octree.h */ \
    engine->RegisterObjectMethod(className, "Array<Drawable@>@ GetDrawables(const Sphere&in, uint8 drawableFlags = DRAWABLE_ANY, uint viewMask = DEFAULT_VIEWMASK)", asFUNCTION(OctreeGetDrawablesSphere), asCALL_CDECL_OBJLAST); \
    /* void Octree::GetDrawables(OctreeQuery &query) const | File: ../Graphics/Octree.h */ \
    engine->RegisterObjectMethod(className, "Array<Drawable@>@ GetAllDrawables(uint8 drawableFlags = DRAWABLE_ANY, uint viewMask = DEFAULT_VIEWMASK)", asFUNCTION(OctreeGetAllDrawables), asCALL_CDECL_OBJLAST);

// ========================================================================================

// void Renderer::SetVSMShadowParameters(float minVariance, float lightBleedingReduction) | File: ../Graphics/Renderer.h
void RendererSetVSMShadowParameters(const Vector2& parameters, Renderer* ptr);

#define REGISTER_MANUAL_PART_Renderer(T, className) \
    /* void Renderer::SetVSMShadowParameters(float minVariance, float lightBleedingReduction) | File: ../Graphics/Renderer.h */ \
    engine->RegisterObjectMethod("Renderer", "void set_vsmShadowParameters(const Vector2&in)", asFUNCTION(RendererSetVSMShadowParameters), asCALL_CDECL_OBJLAST);

}