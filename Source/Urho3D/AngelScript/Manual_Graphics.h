// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

#pragma once

#include "../Graphics/AnimatedModel.h"
#include "../Graphics/Animation.h"
#include "../Graphics/AnimationController.h"
#include "../Graphics/AnimationController.h"
#include "../Graphics/AnimationState.h"
#include "../Graphics/Graphics.h"
#include "../Graphics/Material.h"
#include "../Graphics/Model.h"
#include "../Graphics/Octree.h"
#include "../Graphics/ParticleEffect.h"
#include "../Graphics/Renderer.h"
#include "../Graphics/RenderPath.h"
#include "../Graphics/Technique.h"
#include "../GraphicsAPI/GraphicsDefs.h"
#include "../GraphicsAPI/IndexBuffer.h"
#include "../GraphicsAPI/Texture2D.h"
#include "../GraphicsAPI/TextureCube.h"
#include "../GraphicsAPI/VertexBuffer.h"

namespace Urho3D
{

// Vector<RenderTargetInfo> RenderPath::renderTargets_ | File: ../Graphics/RenderPath.h
template <class T> RenderTargetInfo* RenderPath_GetRenderTarget(unsigned index, T* ptr)
{
    if (index >= ptr->renderTargets_.Size())
    {
        asIScriptContext* context = asGetActiveContext();
        if (context)
            context->SetException("Index out of bounds");
        return nullptr;
    }
    else
        return &ptr->renderTargets_[index];
}

// Vector<RenderPathCommand> RenderPath::commands_ | File: ../Graphics/RenderPath.h
template <class T> RenderPathCommand* RenderPath_GetCommand(unsigned index, T* ptr)
{
    if (index >= ptr->commands_.Size())
    {
        asIScriptContext* context = asGetActiveContext();
        if (context)
            context->SetException("Index out of bounds");
        return nullptr;
    }
    else
        return &ptr->commands_[index];
}

#define REGISTER_MEMBERS_MANUAL_PART_RenderPath() \
    /* Vector<RenderTargetInfo> RenderPath::renderTargets_ | File: ../Graphics/RenderPath.h */ \
    engine->RegisterObjectMethod(className, "const RenderTargetInfo& get_renderTargets(uint) const", AS_FUNCTION_OBJLAST(RenderPath_GetRenderTarget<T>), AS_CALL_CDECL_OBJLAST); \
    \
    /* Vector<RenderPathCommand> RenderPath::commands_ | File: ../Graphics/RenderPath.h */ \
    engine->RegisterObjectMethod(className, "const RenderPathCommand& get_commands(uint) const", AS_FUNCTION_OBJLAST(RenderPath_GetCommand<T>), AS_CALL_CDECL_OBJLAST);

// ========================================================================================

// SharedPtr<Technique> TechniqueEntry::technique_ | File: ../Graphics/Material.h
template <class T> void TechniqueEntry_SetTechnique(Technique* technique, T* ptr)
{
    ptr->technique_ = technique;
}

// SharedPtr<Technique> TechniqueEntry::technique_ | File: ../Graphics/Material.h
template <class T> Technique* TechniqueEntry_GetTechnique(T* ptr)
{
    return ptr->technique_;
}

#define REGISTER_MEMBERS_MANUAL_PART_TechniqueEntry() \
    /* SharedPtr<Technique> TechniqueEntry::technique_ | File: ../Graphics/Material.h */ \
    engine->RegisterObjectMethod(className, "void set_technique(Technique@+)", AS_FUNCTION_OBJLAST(TechniqueEntry_SetTechnique<T>), AS_CALL_CDECL_OBJLAST); \
    engine->RegisterObjectMethod(className, "Technique@+ get_technique() const", AS_FUNCTION_OBJLAST(TechniqueEntry_GetTechnique<T>), AS_CALL_CDECL_OBJLAST);

// ========================================================================================

extern TechniqueEntry noTechniqueEntry;

template <class T> bool Material_Load_File(File* file, T* ptr)
{
    return file && ptr->Resource::Load(*file);
}

// const HashMap<StringHash, MaterialShaderParameter>& Material::GetShaderParameters() const | File: ../Graphics/Material.h
template <class T> CScriptArray* Material_GetShaderParameterNames(T* material)
{
    Vector<String> result;

    const HashMap<StringHash, MaterialShaderParameter>& parameters = material->GetShaderParameters();
    for (HashMap<StringHash, MaterialShaderParameter>::ConstIterator i = parameters.Begin(); i != parameters.End(); ++i)
        result.Push(i->second_.name_);

    Sort(result.Begin(), result.End());
    return VectorToArray<String>(result, "Array<String>");
}

// const TechniqueEntry& Material::GetTechniqueEntry(unsigned index) const | File: ../Graphics/Material.h
template <class T> const TechniqueEntry& Material_GetTechniqueEntry(unsigned index, T* ptr)
{
    if (index >= ptr->GetNumTechniques())
    {
        asGetActiveContext()->SetException("Index out of bounds");
        return noTechniqueEntry;
    }

    return ptr->GetTechniqueEntry(index);
}

#define REGISTER_MEMBERS_MANUAL_PART_Material() \
    /* const HashMap<StringHash, MaterialShaderParameter>& Material::GetShaderParameters() const | File: ../Graphics/Material.h */ \
    engine->RegisterObjectMethod(className, "Array<String>@ get_shaderParameterNames() const", AS_FUNCTION_OBJLAST(Material_GetShaderParameterNames<T>), AS_CALL_CDECL_OBJLAST); \
    \
    /* const TechniqueEntry& Material::GetTechniqueEntry(unsigned index) const | File: ../Graphics/Material.h */ \
    engine->RegisterObjectMethod(className, "const TechniqueEntry& get_techniqueEntries(uint) const", AS_FUNCTION_OBJLAST(Material_GetTechniqueEntry<T>), AS_CALL_CDECL_OBJLAST);

// ========================================================================================

template <class T> VectorBuffer VertexBuffer_GetData(T* ptr)
{
    VectorBuffer ret;
    void* data = ptr->Lock(0, ptr->GetVertexCount(), false);

    if (data)
    {
        ret.Write(data, ptr->GetVertexCount() * ptr->GetVertexSize());
        ret.Seek(0);
        ptr->Unlock();
    }

    return ret;
}

// bool VertexBuffer::SetData(const void* data) | File: ../GraphicsAPI/VertexBuffer.h
template <class T> bool VertexBuffer_SetData(VectorBuffer& src, T* ptr)
{
    // Make sure there is enough data
    if (ptr->GetVertexCount() && src.GetSize() >= ptr->GetVertexCount() * ptr->GetVertexSize())
        return ptr->SetData(&src.GetBuffer()[0]);
    else
        return false;
}

// bool VertexBuffer::SetDataRange(const void* data, unsigned start, unsigned count, bool discard = false) | File: ../GraphicsAPI/VertexBuffer.h
template <class T> bool VertexBuffer_SetDataRange(VectorBuffer& src, unsigned start, unsigned count, bool discard, T* ptr)
{
    // Make sure there is enough data
    if (ptr->GetVertexCount() && src.GetSize() >= count * ptr->GetVertexSize())
        return ptr->SetDataRange(&src.GetBuffer()[0], start, count, discard);
    else
        return false;
}

#define REGISTER_MEMBERS_MANUAL_PART_VertexBuffer() \
    engine->RegisterObjectMethod(className, "VectorBuffer GetData() const", AS_FUNCTION_OBJLAST(VertexBuffer_GetData<T>), AS_CALL_CDECL_OBJLAST); \
    \
    /* bool VertexBuffer::SetData(const void* data) | File: ../GraphicsAPI/VertexBuffer.h */ \
    engine->RegisterObjectMethod(className, "bool SetData(VectorBuffer&)", AS_FUNCTION_OBJLAST(VertexBuffer_SetData<T>), AS_CALL_CDECL_OBJLAST); \
    \
    /* bool VertexBuffer::SetDataRange(const void* data, unsigned start, unsigned count, bool discard = false) | File: ../GraphicsAPI/VertexBuffer.h */ \
    engine->RegisterObjectMethod(className, "bool SetDataRange(VectorBuffer&, uint, uint, bool = false)", AS_FUNCTION_OBJLAST(VertexBuffer_SetDataRange<T>), AS_CALL_CDECL_OBJLAST);

// ========================================================================================

template <class T> VectorBuffer IndexBuffer_GetData(T* ptr)
{
    VectorBuffer ret;
    void* data = ptr->Lock(0, ptr->GetIndexCount(), false);

    if (data)
    {
        ret.Write(data, ptr->GetIndexCount() * ptr->GetIndexSize());
        ret.Seek(0);
        ptr->Unlock();
    }

    return ret;
}

// bool IndexBuffer::SetData(const void* data) | File: ../GraphicsAPI/IndexBuffer.h
template <class T> bool IndexBuffer_SetData(VectorBuffer& src, T* ptr)
{
    // Make sure there is enough data
    if (ptr->GetIndexCount() && src.GetSize() >= ptr->GetIndexCount() * ptr->GetIndexSize())
        return ptr->SetData(&src.GetBuffer()[0]);
    else
        return false;
}

// bool IndexBuffer::SetDataRange(const void* data, unsigned start, unsigned count, bool discard = false) | File: ../GraphicsAPI/IndexBuffer.h
template <class T> bool IndexBuffer_SetDataRange(VectorBuffer& src, unsigned start, unsigned count, bool discard, T* ptr)
{
    // Make sure there is enough data
    if (ptr->GetIndexCount() && src.GetSize() >= count * ptr->GetIndexSize())
        return ptr->SetDataRange(&src.GetBuffer()[0], start, count, discard);
    else
        return false;
}

#define REGISTER_MEMBERS_MANUAL_PART_IndexBuffer() \
    engine->RegisterObjectMethod(className, "VectorBuffer GetData()", AS_FUNCTION_OBJLAST(IndexBuffer_GetData<T>), AS_CALL_CDECL_OBJLAST); \
    \
    /* bool IndexBuffer::SetData(const void* data) | File: ../GraphicsAPI/IndexBuffer.h */ \
    engine->RegisterObjectMethod(className, "bool SetData(VectorBuffer&)", AS_FUNCTION_OBJLAST(IndexBuffer_SetData<T>), AS_CALL_CDECL_OBJLAST); \
    \
    /* bool IndexBuffer::SetDataRange(const void* data, unsigned start, unsigned count, bool discard = false) | File: ../GraphicsAPI/IndexBuffer.h */ \
    engine->RegisterObjectMethod(className, "bool SetDataRange(VectorBuffer&, uint, uint, bool discard = false)", AS_FUNCTION_OBJLAST(IndexBuffer_SetDataRange<T>), AS_CALL_CDECL_OBJLAST);

// ========================================================================================

#define REGISTER_MEMBERS_MANUAL_PART_AnimationTrack() \
    /* AnimationKeyFrame* AnimationTrack::GetKeyFrame(unsigned index) | File: ../Graphics/Animation.h */ \
    engine->RegisterObjectMethod(className, "const AnimationKeyFrame& get_keyFrames(uint) const", AS_METHOD(T, GetKeyFrame), AS_CALL_THISCALL);

// ========================================================================================

// AnimationTriggerPoint* Animation::GetTrigger(unsigned index) | File: ../Graphics/Animation.h
template <class T> AnimationTriggerPoint* Animation_GetTrigger(unsigned index, T* ptr)
{
    if (index >= ptr->GetNumTriggers())
    {
        asIScriptContext* context = asGetActiveContext();
        if (context)
            context->SetException("Index out of bounds");
        return nullptr;
    }
    else
        return ptr->GetTrigger(index);
}

#define REGISTER_MEMBERS_MANUAL_PART_Animation() \
    /* AnimationTriggerPoint* Animation::GetTrigger(unsigned index) | File: ../Graphics/Animation.h */ \
    engine->RegisterObjectMethod(className, "const AnimationTriggerPoint& get_triggers(uint) const", AS_FUNCTION_OBJLAST(Animation_GetTrigger<T>), AS_CALL_CDECL_OBJLAST);

// ========================================================================================

#define REGISTER_MEMBERS_MANUAL_PART_CascadeParameters() \
    /* Vector4 CascadeParameters::splits_ | File: ../Graphics/Light.h */ \
    engine->RegisterObjectProperty(className, "float split1", offsetof(T, splits_.x_)); \
    engine->RegisterObjectProperty(className, "float split2", offsetof(T, splits_.y_)); \
    engine->RegisterObjectProperty(className, "float split3", offsetof(T, splits_.z_)); \
    engine->RegisterObjectProperty(className, "float split4", offsetof(T, splits_.w_));

// ========================================================================================

// void AnimationState::SetBoneWeight(const String& name, float weight, bool recursive = false) | File: ../Graphics/AnimationState.h
template <class T> void AnimationState_SetBoneWeight(const String& name, float weight, T* ptr)
{
    ptr->SetBoneWeight(name, weight);
}

#define REGISTER_MEMBERS_MANUAL_PART_AnimationState() \
    /* void AnimationState::SetBoneWeight(const String& name, float weight, bool recursive = false) | File: ../Graphics/AnimationState.h */ \
    engine->RegisterObjectMethod(className, "void set_boneWeights(const String&in, float)", AS_FUNCTION_OBJLAST(AnimationState_SetBoneWeight<T>), AS_CALL_CDECL_OBJLAST);

// ========================================================================================

// virtual void StaticModel::SetModel(Model* model) | File: ../Graphics/StaticModel.h
template <class T> void StaticModel_SetModel(Model* model, T* ptr)
{
    // Check type here to allow operating on both AnimatedModel and StaticModel without calling the wrong function,
    // as AnimatedModel can be cast to StaticModel
    if (ptr->GetType() == AnimatedModel::GetTypeStatic())
        ((AnimatedModel*)ptr)->SetModel(model);
    else
        ptr->SetModel(model);
}

#define REGISTER_MEMBERS_MANUAL_PART_StaticModel() \
    /* virtual void StaticModel::SetModel(Model* model) | File: ../Graphics/StaticModel.h */ \
    engine->RegisterObjectMethod(className, "void SetModel(Model@+)", AS_FUNCTION_OBJLAST(StaticModel_SetModel<T>), AS_CALL_CDECL_OBJLAST); \
    engine->RegisterObjectMethod(className, "void set_model(Model@+)", AS_FUNCTION_OBJLAST(StaticModel_SetModel<T>), AS_CALL_CDECL_OBJLAST);

// ========================================================================================

// const Vector<ModelMorph>& AnimatedModel::GetMorphs() const | File: ../Graphics/AnimatedModel.h
template <class T> const String& AnimatedModel_GetMorphName(unsigned index, T* ptr)
{
    const Vector<ModelMorph>& morphs = ptr->GetMorphs();
    return index < morphs.Size() ? morphs[index].name_ : String::EMPTY;
}

// void AnimatedModel::SetModel(Model* model, bool createBones = true) | File: ../Graphics/AnimatedModel.h
template <class T> void AnimatedModel_SetModel(Model* model, T* ptr)
{
    ptr->SetModel(model);
}

#define REGISTER_MEMBERS_MANUAL_PART_AnimatedModel() \
    /* const Vector<ModelMorph>& AnimatedModel::GetMorphs() const | File: ../Graphics/AnimatedModel.h */ \
    engine->RegisterObjectMethod(className, "const String& get_morphNames(uint) const", AS_FUNCTION_OBJLAST(AnimatedModel_GetMorphName<T>), AS_CALL_CDECL_OBJLAST);

// ========================================================================================

// const Vector<AnimationControl>& AnimationController::GetAnimations() const | File: ../Graphics/AnimationController.h
template <class T> unsigned AnimationController_GetNumAnimations(T* controller)
{
    return controller->GetAnimations().Size();
}

// const Vector<AnimationControl>& AnimationController::GetAnimations() const | File: ../Graphics/AnimationController.h
template <class T> const AnimationControl* AnimationController_GetAnimation(unsigned index, T* controller)
{
    const Vector<AnimationControl>& animations = controller->GetAnimations();
    return (index < animations.Size()) ? &animations[index] : nullptr;
}

#define REGISTER_MEMBERS_MANUAL_PART_AnimationController() \
    /* const Vector<AnimationControl>& AnimationController::GetAnimations() const | File: ../Graphics/AnimationController.h */ \
    engine->RegisterObjectMethod(className, "uint get_numAnimations() const", AS_FUNCTION_OBJLAST(AnimationController_GetNumAnimations<T>), AS_CALL_CDECL_OBJLAST); \
    \
    /* const Vector<AnimationControl>& AnimationController::GetAnimations() const | File: ../Graphics/AnimationController.h */ \
    engine->RegisterObjectMethod(className, "const AnimationControl@ get_animations(uint) const", AS_FUNCTION_OBJLAST(AnimationController_GetAnimation<T>), AS_CALL_CDECL_OBJLAST);

// ========================================================================================

// void Graphics::PrecacheShaders(Deserializer& source) | File: ../Graphics/Graphics.h
template <class T> void Graphics_PrecacheShaders_File(File* file, T* ptr)
{
    if (file)
        ptr->PrecacheShaders(*file);
}

// void Graphics::PrecacheShaders(Deserializer& source) | File: ../Graphics/Graphics.h
template <class T> void Graphics_PrecacheShaders_VectorBuffer(VectorBuffer& buffer, T* ptr)
{
    ptr->PrecacheShaders(buffer);
}

#define REGISTER_MEMBERS_MANUAL_PART_Graphics() \
    /* void Graphics::PrecacheShaders(Deserializer& source) | File: ../Graphics/Graphics.h */ \
    engine->RegisterObjectMethod(className, "void PrecacheShaders(File@+)", AS_FUNCTION_OBJLAST(Graphics_PrecacheShaders_File<T>), AS_CALL_CDECL_OBJLAST); \
    \
    /* void Graphics::PrecacheShaders(Deserializer& source) | File: ../Graphics/Graphics.h */ \
    engine->RegisterObjectMethod(className, "void PrecacheShaders(VectorBuffer&)", AS_FUNCTION_OBJLAST(Graphics_PrecacheShaders_VectorBuffer<T>), AS_CALL_CDECL_OBJLAST);

// ========================================================================================

// Drawable* RayQueryResult::drawable_ | File: ../Graphics/OctreeQuery.h
template <class T> Drawable* RayQueryResult_GetDrawable(T* ptr)
{
    return ptr->drawable_;
}

// Node* RayQueryResult::node_ | File: ../Graphics/OctreeQuery.h
template <class T> Node* RayQueryResult_GetNode(T* ptr)
{
    return ptr->node_;
}

#define REGISTER_MEMBERS_MANUAL_PART_RayQueryResult() \
    /* Drawable* RayQueryResult::drawable_ | File: ../Graphics/OctreeQuery.h */ \
    engine->RegisterObjectMethod(className, "Drawable@+ get_drawable() const", AS_FUNCTION_OBJLAST(RayQueryResult_GetDrawable<T>), AS_CALL_CDECL_OBJLAST); \
    \
    /* Node* RayQueryResult::node_ | File: ../Graphics/OctreeQuery.h */ \
    engine->RegisterObjectMethod(className, "Node@+ get_node() const", AS_FUNCTION_OBJLAST(RayQueryResult_GetNode<T>), AS_CALL_CDECL_OBJLAST);

// ========================================================================================

// void Octree::Raycast(RayOctreeQuery& query) const | File: ../Graphics/Octree.h
template <class T> CScriptArray* Octree_Raycast(const Ray& ray, RayQueryLevel level, float maxDistance, unsigned char drawableFlags, unsigned viewMask, Octree* ptr)
{
    PODVector<RayQueryResult> result;
    RayOctreeQuery query(result, ray, level, maxDistance, drawableFlags, viewMask);
    ptr->Raycast(query);
    return VectorToArray<RayQueryResult>(result, "Array<RayQueryResult>");
}

// void Octree::RaycastSingle(RayOctreeQuery& query) const | File: ../Graphics/Octree.h
template <class T> RayQueryResult Octree_RaycastSingle(const Ray& ray, RayQueryLevel level, float maxDistance, unsigned char drawableFlags, unsigned viewMask, Octree* ptr)
{
    PODVector<RayQueryResult> result;
    RayOctreeQuery query(result, ray, level, maxDistance, drawableFlags, viewMask);
    ptr->RaycastSingle(query);

    if (!query.result_.Empty())
    {
        return query.result_[0];
    }
    else
    {
        RayQueryResult empty;
        empty.position_ = Vector3::ZERO;
        empty.normal_ = Vector3::ZERO;
        empty.distance_ = M_INFINITY;
        empty.subObject_ = 0;
        return empty;
    }
}

// void Octree::GetDrawables(OctreeQuery& query) const | File: ../Graphics/Octree.h
template <class T> CScriptArray* Octree_GetDrawables_Point(const Vector3& point, unsigned char drawableFlags, unsigned viewMask, Octree* ptr)
{
    PODVector<Drawable*> result;
    PointOctreeQuery query(result, point, drawableFlags, viewMask);
    ptr->GetDrawables(query);
    return VectorToHandleArray<Drawable>(result, "Array<Drawable@>");
}

// void Octree::GetDrawables(OctreeQuery& query) const | File: ../Graphics/Octree.h
template <class T> CScriptArray* Octree_GetDrawables_Box(const BoundingBox& box, unsigned char drawableFlags, unsigned viewMask, Octree* ptr)
{
    PODVector<Drawable*> result;
    BoxOctreeQuery query(result, box, drawableFlags, viewMask);
    ptr->GetDrawables(query);
    return VectorToHandleArray<Drawable>(result, "Array<Drawable@>");
}

// void Octree::GetDrawables(OctreeQuery& query) const | File: ../Graphics/Octree.h
template <class T> CScriptArray* Octree_GetDrawables_Frustum(const Frustum& frustum, unsigned char drawableFlags, unsigned viewMask, Octree* ptr)
{
    PODVector<Drawable*> result;
    FrustumOctreeQuery query(result, frustum, drawableFlags, viewMask);
    ptr->GetDrawables(query);
    return VectorToHandleArray<Drawable>(result, "Array<Drawable@>");
}

// void Octree::GetDrawables(OctreeQuery& query) const | File: ../Graphics/Octree.h
template <class T> CScriptArray* Octree_GetDrawables_Sphere(const Sphere& sphere, unsigned char drawableFlags, unsigned viewMask, Octree* ptr)
{
    PODVector<Drawable*> result;
    SphereOctreeQuery query(result, sphere, drawableFlags, viewMask);
    ptr->GetDrawables(query);
    return VectorToHandleArray<Drawable>(result, "Array<Drawable@>");
}

// void Octree::GetDrawables(OctreeQuery& query) const | File: ../Graphics/Octree.h
template <class T> CScriptArray* Octree_GetDrawables_All(unsigned char drawableFlags, unsigned viewMask, Octree* ptr)
{
    PODVector<Drawable*> result;
    AllContentOctreeQuery query(result, drawableFlags, viewMask);
    ptr->GetDrawables(query);
    return VectorToHandleArray<Drawable>(result, "Array<Drawable@>");
}

#define REGISTER_MEMBERS_MANUAL_PART_Octree() \
    /* void Octree::Raycast(RayOctreeQuery& query) const | File: ../Graphics/Octree.h */ \
    engine->RegisterObjectMethod(className, "Array<RayQueryResult>@ Raycast(const Ray&in, RayQueryLevel = RAY_TRIANGLE, float = M_INFINITY, uint8 = DRAWABLE_ANY, uint = DEFAULT_VIEWMASK) const", AS_FUNCTION_OBJLAST(Octree_Raycast<T>), AS_CALL_CDECL_OBJLAST); \
    \
    /* void Octree::RaycastSingle(RayOctreeQuery& query) const | File: ../Graphics/Octree.h */ \
    engine->RegisterObjectMethod(className, "RayQueryResult RaycastSingle(const Ray&in, RayQueryLevel = RAY_TRIANGLE, float = M_INFINITY, uint8 = DRAWABLE_ANY, uint = DEFAULT_VIEWMASK) const", AS_FUNCTION_OBJLAST(Octree_RaycastSingle<T>), AS_CALL_CDECL_OBJLAST); \
    \
    /* void Octree::GetDrawables(OctreeQuery& query) const | File: ../Graphics/Octree.h */ \
    engine->RegisterObjectMethod(className, "Array<Drawable@>@ GetDrawables(const Vector3&in, uint8 = DRAWABLE_ANY, uint = DEFAULT_VIEWMASK)", AS_FUNCTION_OBJLAST(Octree_GetDrawables_Point<T>), AS_CALL_CDECL_OBJLAST); \
    engine->RegisterObjectMethod(className, "Array<Drawable@>@ GetDrawables(const BoundingBox&in, uint8 = DRAWABLE_ANY, uint = DEFAULT_VIEWMASK)", AS_FUNCTION_OBJLAST(Octree_GetDrawables_Box<T>), AS_CALL_CDECL_OBJLAST); \
    engine->RegisterObjectMethod(className, "Array<Drawable@>@ GetDrawables(const Frustum&in, uint8 = DRAWABLE_ANY, uint = DEFAULT_VIEWMASK)", AS_FUNCTION_OBJLAST(Octree_GetDrawables_Frustum<T>), AS_CALL_CDECL_OBJLAST); \
    engine->RegisterObjectMethod(className, "Array<Drawable@>@ GetDrawables(const Sphere&in, uint8 = DRAWABLE_ANY, uint = DEFAULT_VIEWMASK)", AS_FUNCTION_OBJLAST(Octree_GetDrawables_Sphere<T>), AS_CALL_CDECL_OBJLAST); \
    engine->RegisterObjectMethod(className, "Array<Drawable@>@ GetAllDrawables(uint8 = DRAWABLE_ANY, uint = DEFAULT_VIEWMASK)", AS_FUNCTION_OBJLAST(Octree_GetDrawables_All<T>), AS_CALL_CDECL_OBJLAST);

// ========================================================================================

// void Renderer::SetVSMShadowParameters(float minVariance, float lightBleedingReduction) | File: ../Graphics/Renderer.h
template <class T> void Renderer_SetVSMShadowParameters(const Vector2& parameters, T* ptr)
{
    ptr->SetVSMShadowParameters(parameters.x_, parameters.y_);
}

#define REGISTER_MEMBERS_MANUAL_PART_Renderer() \
    /* void Renderer::SetVSMShadowParameters(float minVariance, float lightBleedingReduction) | File: ../Graphics/Renderer.h */ \
    engine->RegisterObjectMethod("Renderer", "void set_vsmShadowParameters(const Vector2&in)", AS_FUNCTION_OBJLAST(Renderer_SetVSMShadowParameters<T>), AS_CALL_CDECL_OBJLAST);

}
