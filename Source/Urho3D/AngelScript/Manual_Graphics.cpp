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

#include "../Precompiled.h"
#include "../AngelScript/APITemplates.h"

#include "../AngelScript/Manual_Graphics.h"
#include "../Scene/Scene.h"
#include "../Graphics/DebugRenderer.h"

namespace Urho3D
{

// This function is called before ASRegisterGenerated()
void ASRegisterManualFirst_Graphics(asIScriptEngine* engine)
{
    // enum TextureUnit | File: ../Graphics/GraphicsDefs.h
    engine->RegisterEnum("TextureUnit");
    engine->RegisterEnumValue("TextureUnit", "TU_DIFFUSE", TU_DIFFUSE);
    engine->RegisterEnumValue("TextureUnit", "TU_ALBEDOBUFFER", TU_ALBEDOBUFFER);
    engine->RegisterEnumValue("TextureUnit", "TU_NORMAL", TU_NORMAL);
    engine->RegisterEnumValue("TextureUnit", "TU_NORMALBUFFER", TU_NORMALBUFFER);
    engine->RegisterEnumValue("TextureUnit", "TU_SPECULAR", TU_SPECULAR);
    engine->RegisterEnumValue("TextureUnit", "TU_EMISSIVE", TU_EMISSIVE);
    engine->RegisterEnumValue("TextureUnit", "TU_ENVIRONMENT", TU_ENVIRONMENT);
    engine->RegisterEnumValue("TextureUnit", "TU_LIGHTRAMP", TU_LIGHTRAMP);
    engine->RegisterEnumValue("TextureUnit", "TU_LIGHTSHAPE", TU_LIGHTSHAPE);
    engine->RegisterEnumValue("TextureUnit", "TU_SHADOWMAP", TU_SHADOWMAP);
#ifdef DESKTOP_GRAPHICS
    engine->RegisterEnumValue("TextureUnit", "TU_VOLUMEMAP", TU_VOLUMEMAP);
    engine->RegisterEnumValue("TextureUnit", "TU_CUSTOM1", TU_CUSTOM1);
    engine->RegisterEnumValue("TextureUnit", "TU_CUSTOM2", TU_CUSTOM2);
    engine->RegisterEnumValue("TextureUnit", "TU_FACESELECT", TU_FACESELECT);
    engine->RegisterEnumValue("TextureUnit", "TU_INDIRECTION", TU_INDIRECTION);
    engine->RegisterEnumValue("TextureUnit", "TU_DEPTHBUFFER", TU_DEPTHBUFFER);
    engine->RegisterEnumValue("TextureUnit", "TU_LIGHTBUFFER", TU_LIGHTBUFFER);
    engine->RegisterEnumValue("TextureUnit", "TU_ZONE", TU_ZONE);
#endif
    engine->RegisterEnumValue("TextureUnit", "MAX_MATERIAL_TEXTURE_UNITS", MAX_MATERIAL_TEXTURE_UNITS);
    engine->RegisterEnumValue("TextureUnit", "MAX_TEXTURE_UNITS", MAX_TEXTURE_UNITS);
}

// ========================================================================================

static void StaticModelSetModel(Model* model, StaticModel* ptr)
{
    // Check type here to allow operating on both AnimatedModel and StaticModel without calling the wrong function,
    // as AnimatedModel can be cast to StaticModel
    if (ptr->GetType() == AnimatedModel::GetTypeStatic())
        static_cast<AnimatedModel*>(ptr)->SetModel(model);
    else
        ptr->SetModel(model);
}

// template<class T> T * Object::GetSubsystem() const | File: ../Core/Object.h
static Graphics* GetGraphics()
{
    return GetScriptContext()->GetSubsystem<Graphics>();
}

// template<class T> T * Object::GetSubsystem() const | File: ../Core/Object.h
static Renderer* GetRenderer()
{
    return GetScriptContext()->GetSubsystem<Renderer>();
}

// template<class T> T * Object::GetSubsystem() const | File: ../Core/Object.h
static DebugRenderer* GetDebugRenderer()
{
    Scene* scene = GetScriptContextScene();
    if (scene)
        return scene->GetComponent<DebugRenderer>();
    else
        return nullptr;
}

// template<class T> T * Object::GetSubsystem() const | File: ../Core/Object.h
static Octree* GetOctree()
{
    Scene* scene = GetScriptContextScene();
    return scene ? scene->GetComponent<Octree>() : nullptr;
}

// This function is called after ASRegisterGenerated()
void ASRegisterManualLast_Graphics(asIScriptEngine* engine)
{
    engine->RegisterObjectMethod("StaticModel", "void SetModel(Model@+)", asFUNCTION(StaticModelSetModel), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("StaticModel", "void set_model(Model@+)", asFUNCTION(StaticModelSetModel), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("Skybox", "void SetModel(Model@+)", asFUNCTION(StaticModelSetModel), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("Skybox", "void set_model(Model@+)", asFUNCTION(StaticModelSetModel), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("StaticModelGroup", "void SetModel(Model@+)", asFUNCTION(StaticModelSetModel), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("StaticModelGroup", "void set_model(Model@+)", asFUNCTION(StaticModelSetModel), asCALL_CDECL_OBJLAST);

    // template<class T> T * Object::GetSubsystem() const | File: ../Core/Object.h
    engine->RegisterGlobalFunction("Graphics@+ get_graphics()", asFUNCTION(GetGraphics), asCALL_CDECL);
    // template<class T> T * Object::GetSubsystem() const | File: ../Core/Object.h
    engine->RegisterGlobalFunction("Renderer@+ get_renderer()", asFUNCTION(GetRenderer), asCALL_CDECL);
    // template<class T> T * Object::GetSubsystem() const | File: ../Core/Object.h
    engine->RegisterGlobalFunction("DebugRenderer@+ get_debugRenderer()", asFUNCTION(GetDebugRenderer), asCALL_CDECL);
    // template<class T> T * Object::GetSubsystem() const | File: ../Core/Object.h
    engine->RegisterGlobalFunction("Octree@+ get_octree()", asFUNCTION(GetOctree), asCALL_CDECL);
}

// ========================================================================================

// Vector<RenderTargetInfo> RenderPath::renderTargets_ | File: ../Graphics/RenderPath.h
RenderTargetInfo* RenderPathGetRenderTarget(unsigned index, RenderPath* ptr)
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
RenderPathCommand* RenderPathGetCommand(unsigned index, RenderPath* ptr)
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

// ========================================================================================

// SharedPtr<Technique> TechniqueEntry::technique_ | File: ../Graphics/Material.h
void TechniqueEntrySetTechnique(Technique* technique, TechniqueEntry* ptr)
{
    ptr->technique_ = technique;
}

// SharedPtr<Technique> TechniqueEntry::technique_ | File: ../Graphics/Material.h
Technique* TechniqueEntryGetTechnique(TechniqueEntry* ptr)
{
    return ptr->technique_;
}

// ========================================================================================

static TechniqueEntry noTechniqueEntry;

// const TechniqueEntry& Material::GetTechniqueEntry(unsigned index) const | File: ../Graphics/Material.h
const TechniqueEntry& MaterialGetTechniqueEntry(unsigned index, Material* ptr)
{
    if (index >= ptr->GetNumTechniques())
    {
        asGetActiveContext()->SetException("Index out of bounds");
        return noTechniqueEntry;
    }

    return ptr->GetTechniqueEntry(index);
}

CScriptArray* MaterialGetShaderParameterNames(Material* material)
{
    Vector<String> result;

    const HashMap<StringHash, MaterialShaderParameter>& parameters = material->GetShaderParameters();
    for (HashMap<StringHash, MaterialShaderParameter>::ConstIterator i = parameters.Begin(); i != parameters.End(); ++i)
        result.Push(i->second_.name_);

    Sort(result.Begin(), result.End());
    return VectorToArray<String>(result, "Array<String>");
}

// ========================================================================================

// bool VertexBuffer::SetData(const void *data) | File: ../Graphics/VertexBuffer.h
bool VertexBufferSetData(VectorBuffer& src, VertexBuffer* ptr)
{
    // Make sure there is enough data
    if (ptr->GetVertexCount() && src.GetSize() >= ptr->GetVertexCount() * ptr->GetVertexSize())
        return ptr->SetData(&src.GetBuffer()[0]);
    else
        return false;
}

// bool VertexBuffer::SetDataRange(const void *data, unsigned start, unsigned count, bool discard=false) | File: ../Graphics/VertexBuffer.h
bool VertexBufferSetDataRange(VectorBuffer& src, unsigned start, unsigned count, bool discard, VertexBuffer* ptr)
{
    // Make sure there is enough data
    if (ptr->GetVertexCount() && src.GetSize() >= count * ptr->GetVertexSize())
        return ptr->SetDataRange(&src.GetBuffer()[0], start, count, discard);
    else
        return false;
}

VectorBuffer VertexBufferGetData(VertexBuffer* ptr)
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

// ========================================================================================

// bool IndexBuffer::SetData(const void *data) | File: ../Graphics/IndexBuffer.h
bool IndexBufferSetData(VectorBuffer& src, IndexBuffer* ptr)
{
    // Make sure there is enough data
    if (ptr->GetIndexCount() && src.GetSize() >= ptr->GetIndexCount() * ptr->GetIndexSize())
        return ptr->SetData(&src.GetBuffer()[0]);
    else
        return false;
}

// bool IndexBuffer::SetDataRange(const void *data, unsigned start, unsigned count, bool discard=false) | File: ../Graphics/IndexBuffer.h
bool IndexBufferSetDataRange(VectorBuffer& src, unsigned start, unsigned count, bool discard, IndexBuffer* ptr)
{
    // Make sure there is enough data
    if (ptr->GetIndexCount() && src.GetSize() >= count * ptr->GetIndexSize())
        return ptr->SetDataRange(&src.GetBuffer()[0], start, count, discard);
    else
        return false;
}

VectorBuffer IndexBufferGetData(IndexBuffer* ptr)
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

// ========================================================================================

// AnimationTriggerPoint* Animation::GetTrigger(unsigned index) | File: ../Graphics/Animation.h
AnimationTriggerPoint* AnimationGetTrigger(unsigned index, Animation* ptr)
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

// ========================================================================================

// void AnimationState::SetBoneWeight(const String &name, float weight, bool recursive=false) | File: ../Graphics/AnimationState.h
void AnimationStateSetBoneWeight(const String& name, float weight, AnimationState* ptr)
{
    ptr->SetBoneWeight(name, weight);
}

// ========================================================================================

// void AnimatedModel::SetModel(Model *model, bool createBones=true) | File: ../Graphics/AnimatedModel.h
void AnimatedModelSetModel(Model* model, AnimatedModel* ptr)
{
    ptr->SetModel(model);
}

const String& AnimatedModelGetMorphName(unsigned index, AnimatedModel* ptr)
{
    const Vector<ModelMorph>& morphs = ptr->GetMorphs();
    return index < morphs.Size() ? morphs[index].name_ : String::EMPTY;
}

// ========================================================================================

// const Vector<AnimationControl>& AnimationController::GetAnimations() const | File: ../Graphics/AnimationController.h
unsigned AnimationControllerGetNumAnimations(AnimationController* controller)
{
    return controller->GetAnimations().Size();
}

// const Vector<AnimationControl>& AnimationController::GetAnimations() const | File: ../Graphics/AnimationController.h
const AnimationControl* AnimationControllerGetAnimation(unsigned index, AnimationController* controller)
{
    const Vector<AnimationControl>& animations = controller->GetAnimations();
    return (index < animations.Size()) ? &animations[index] : nullptr;
}

// ========================================================================================

// void Graphics::PrecacheShaders(Deserializer &source) | File: ../Graphics/Graphics.h
void GraphicsPrecacheShaders(File* file, Graphics* ptr)
{
    if (file)
        ptr->PrecacheShaders(*file);
}

// void Graphics::PrecacheShaders(Deserializer &source) | File: ../Graphics/Graphics.h
void GraphicsPrecacheShadersVectorBuffer(VectorBuffer& buffer, Graphics* ptr)
{
    ptr->PrecacheShaders(buffer);
}

// ========================================================================================

// Drawable* RayQueryResult::drawable_ | File: ../Graphics/OctreeQuery.h
Drawable* RayQueryResultGetDrawable(RayQueryResult* ptr)
{
    return ptr->drawable_;
}

// Node* RayQueryResult::node_ | File: ../Graphics/OctreeQuery.h
Node* RayQueryResultGetNode(RayQueryResult* ptr)
{
    return ptr->node_;
}

// ========================================================================================

// void Octree::Raycast(RayOctreeQuery &query) const | File: ../Graphics/Octree.h
CScriptArray* OctreeRaycast(const Ray& ray, RayQueryLevel level, float maxDistance, unsigned char drawableFlags, unsigned viewMask, Octree* ptr)
{
    PODVector<RayQueryResult> result;
    RayOctreeQuery query(result, ray, level, maxDistance, drawableFlags, viewMask);
    ptr->Raycast(query);
    return VectorToArray<RayQueryResult>(result, "Array<RayQueryResult>");
}

// void Octree::RaycastSingle(RayOctreeQuery &query) const | File: ../Graphics/Octree.h
RayQueryResult OctreeRaycastSingle(const Ray& ray, RayQueryLevel level, float maxDistance, unsigned char drawableFlags, unsigned viewMask, Octree* ptr)
{
    PODVector<RayQueryResult> result;
    RayOctreeQuery query(result, ray, level, maxDistance, drawableFlags, viewMask);
    ptr->RaycastSingle(query);
    if (!query.result_.Empty())
        return query.result_[0];
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

// void Octree::GetDrawables(OctreeQuery &query) const | File: ../Graphics/Octree.h
CScriptArray* OctreeGetDrawablesPoint(const Vector3& point, unsigned char drawableFlags, unsigned viewMask, Octree* ptr)
{
    PODVector<Drawable*> result;
    PointOctreeQuery query(result, point, drawableFlags, viewMask);
    ptr->GetDrawables(query);
    return VectorToHandleArray<Drawable>(result, "Array<Drawable@>");
}

// void Octree::GetDrawables(OctreeQuery &query) const | File: ../Graphics/Octree.h
CScriptArray* OctreeGetDrawablesBox(const BoundingBox& box, unsigned char drawableFlags, unsigned viewMask, Octree* ptr)
{
    PODVector<Drawable*> result;
    BoxOctreeQuery query(result, box, drawableFlags, viewMask);
    ptr->GetDrawables(query);
    return VectorToHandleArray<Drawable>(result, "Array<Drawable@>");
}

// void Octree::GetDrawables(OctreeQuery &query) const | File: ../Graphics/Octree.h
CScriptArray* OctreeGetDrawablesFrustum(const Frustum& frustum, unsigned char drawableFlags, unsigned viewMask, Octree* ptr)
{
    PODVector<Drawable*> result;
    FrustumOctreeQuery query(result, frustum, drawableFlags, viewMask);
    ptr->GetDrawables(query);
    return VectorToHandleArray<Drawable>(result, "Array<Drawable@>");
}

// void Octree::GetDrawables(OctreeQuery &query) const | File: ../Graphics/Octree.h
CScriptArray* OctreeGetDrawablesSphere(const Sphere& sphere, unsigned char drawableFlags, unsigned viewMask, Octree* ptr)
{
    PODVector<Drawable*> result;
    SphereOctreeQuery query(result, sphere, drawableFlags, viewMask);
    ptr->GetDrawables(query);
    return VectorToHandleArray<Drawable>(result, "Array<Drawable@>");
}

// void Octree::GetDrawables(OctreeQuery &query) const | File: ../Graphics/Octree.h
CScriptArray* OctreeGetAllDrawables(unsigned char drawableFlags, unsigned viewMask, Octree* ptr)
{
    PODVector<Drawable*> result;
    AllContentOctreeQuery query(result, drawableFlags, viewMask);
    ptr->GetDrawables(query);
    return VectorToHandleArray<Drawable>(result, "Array<Drawable@>");
}

// ========================================================================================

// void Renderer::SetVSMShadowParameters(float minVariance, float lightBleedingReduction) | File: ../Graphics/Renderer.h
void RendererSetVSMShadowParameters(const Vector2& parameters, Renderer* ptr)
{
    ptr->SetVSMShadowParameters(parameters.x_, parameters.y_);
}

}
