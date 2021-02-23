// DO NOT EDIT. This file is generated

#include "../Precompiled.h"
#include "../AngelScript/APITemplates.h"

#include "../AngelScript/GeneratedIncludes.h"
#include "../AngelScript/Manual.h"

namespace Urho3D
{

void FakeAddRef(void* ptr);
void FakeReleaseRef(void* ptr);

// const Vector<String> PackageFile::GetEntryNames() const | File: ../IO/PackageFile.h
static CScriptArray* PackageFile_GetEntryNames_void(PackageFile* ptr)
{
    const Vector<String> result = ptr->GetEntryNames();
    return VectorToArray<String>(result, "Array<String>");
}

// explicit PackageFile::PackageFile(Context* context) | File: ../IO/PackageFile.h
static PackageFile* PackageFile_PackageFile_Context()
{
    return new PackageFile(GetScriptContext());
}

// PackageFile::PackageFile(Context* context, const String& fileName, unsigned startOffset=0) | File: ../IO/PackageFile.h
static PackageFile* PackageFile_PackageFile_Context_String_unsigned(const String &fileName, unsigned startOffset=0)
{
    return new PackageFile(GetScriptContext(), fileName, startOffset);
}

// void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
static void PackageFile_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool(PackageFile* ptr, CScriptArray* exceptions_conv, bool onlyUserData)
{
    PODVector<StringHash> exceptions = ArrayToPODVector<StringHash>(exceptions_conv);
    ptr->UnsubscribeFromAllEventsExcept(exceptions, onlyUserData);
}

// SharedPtr<ParticleEffect> ParticleEffect::Clone(const String& cloneName=String::EMPTY) const | File: ../Graphics/ParticleEffect.h
static ParticleEffect* ParticleEffect_Clone_String(ParticleEffect* ptr, const String& cloneName)
{
    SharedPtr<ParticleEffect> result = ptr->Clone(cloneName);
    return result.Detach();
}

// explicit ParticleEffect::ParticleEffect(Context* context) | File: ../Graphics/ParticleEffect.h
static ParticleEffect* ParticleEffect_ParticleEffect_Context()
{
    return new ParticleEffect(GetScriptContext());
}

// void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
static void ParticleEffect_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool(ParticleEffect* ptr, CScriptArray* exceptions_conv, bool onlyUserData)
{
    PODVector<StringHash> exceptions = ArrayToPODVector<StringHash>(exceptions_conv);
    ptr->UnsubscribeFromAllEventsExcept(exceptions, onlyUserData);
}

#ifdef URHO3D_URHO2D
// SharedPtr<ParticleEffect2D> ParticleEffect2D::Clone(const String& cloneName=String::EMPTY) const | File: ../Urho2D/ParticleEffect2D.h
static ParticleEffect2D* ParticleEffect2D_Clone_String(ParticleEffect2D* ptr, const String& cloneName)
{
    SharedPtr<ParticleEffect2D> result = ptr->Clone(cloneName);
    return result.Detach();
}
#endif

#ifdef URHO3D_URHO2D
// explicit ParticleEffect2D::ParticleEffect2D(Context* context) | File: ../Urho2D/ParticleEffect2D.h
static ParticleEffect2D* ParticleEffect2D_ParticleEffect2D_Context()
{
    return new ParticleEffect2D(GetScriptContext());
}
#endif

#ifdef URHO3D_URHO2D
// void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
static void ParticleEffect2D_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool(ParticleEffect2D* ptr, CScriptArray* exceptions_conv, bool onlyUserData)
{
    PODVector<StringHash> exceptions = ArrayToPODVector<StringHash>(exceptions_conv);
    ptr->UnsubscribeFromAllEventsExcept(exceptions, onlyUserData);
}
#endif

// const PODVector<Light*>& Drawable::GetLights() const | File: ../Graphics/Drawable.h
static CScriptArray* ParticleEmitter_GetLights_void(ParticleEmitter* ptr)
{
    const PODVector<Light*>& result = ptr->GetLights();
    return VectorToHandleArray(result, "Array<Light@>");
}

// const PODVector<Light*>& Drawable::GetVertexLights() const | File: ../Graphics/Drawable.h
static CScriptArray* ParticleEmitter_GetVertexLights_void(ParticleEmitter* ptr)
{
    const PODVector<Light*>& result = ptr->GetVertexLights();
    return VectorToHandleArray(result, "Array<Light@>");
}

// explicit ParticleEmitter::ParticleEmitter(Context* context) | File: ../Graphics/ParticleEmitter.h
static ParticleEmitter* ParticleEmitter_ParticleEmitter_Context()
{
    return new ParticleEmitter(GetScriptContext());
}

// void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
static void ParticleEmitter_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool(ParticleEmitter* ptr, CScriptArray* exceptions_conv, bool onlyUserData)
{
    PODVector<StringHash> exceptions = ArrayToPODVector<StringHash>(exceptions_conv);
    ptr->UnsubscribeFromAllEventsExcept(exceptions, onlyUserData);
}

#ifdef URHO3D_URHO2D
// const PODVector<Light*>& Drawable::GetLights() const | File: ../Graphics/Drawable.h
static CScriptArray* ParticleEmitter2D_GetLights_void(ParticleEmitter2D* ptr)
{
    const PODVector<Light*>& result = ptr->GetLights();
    return VectorToHandleArray(result, "Array<Light@>");
}
#endif

#ifdef URHO3D_URHO2D
// const PODVector<Light*>& Drawable::GetVertexLights() const | File: ../Graphics/Drawable.h
static CScriptArray* ParticleEmitter2D_GetVertexLights_void(ParticleEmitter2D* ptr)
{
    const PODVector<Light*>& result = ptr->GetVertexLights();
    return VectorToHandleArray(result, "Array<Light@>");
}
#endif

#ifdef URHO3D_URHO2D
// explicit ParticleEmitter2D::ParticleEmitter2D(Context* context) | File: ../Urho2D/ParticleEmitter2D.h
static ParticleEmitter2D* ParticleEmitter2D_ParticleEmitter2D_Context()
{
    return new ParticleEmitter2D(GetScriptContext());
}
#endif

#ifdef URHO3D_URHO2D
// void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
static void ParticleEmitter2D_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool(ParticleEmitter2D* ptr, CScriptArray* exceptions_conv, bool onlyUserData)
{
    PODVector<StringHash> exceptions = ArrayToPODVector<StringHash>(exceptions_conv);
    ptr->UnsubscribeFromAllEventsExcept(exceptions, onlyUserData);
}
#endif

// Vector<SharedPtr<ShaderVariation>>& Pass::GetPixelShaders() | File: ../Graphics/Technique.h
static CScriptArray* Pass_GetPixelShaders_void(Pass* ptr)
{
    Vector<SharedPtr<ShaderVariation>>& result = ptr->GetPixelShaders();
    return VectorToHandleArray(result, "Array<ShaderVariation@>");
}

// Vector<SharedPtr<ShaderVariation>>& Pass::GetPixelShaders(const StringHash& extraDefinesHash) | File: ../Graphics/Technique.h
static CScriptArray* Pass_GetPixelShaders_StringHash(Pass* ptr, const StringHash& extraDefinesHash)
{
    Vector<SharedPtr<ShaderVariation>>& result = ptr->GetPixelShaders(extraDefinesHash);
    return VectorToHandleArray(result, "Array<ShaderVariation@>");
}

// Vector<SharedPtr<ShaderVariation>>& Pass::GetVertexShaders() | File: ../Graphics/Technique.h
static CScriptArray* Pass_GetVertexShaders_void(Pass* ptr)
{
    Vector<SharedPtr<ShaderVariation>>& result = ptr->GetVertexShaders();
    return VectorToHandleArray(result, "Array<ShaderVariation@>");
}

// Vector<SharedPtr<ShaderVariation>>& Pass::GetVertexShaders(const StringHash& extraDefinesHash) | File: ../Graphics/Technique.h
static CScriptArray* Pass_GetVertexShaders_StringHash(Pass* ptr, const StringHash& extraDefinesHash)
{
    Vector<SharedPtr<ShaderVariation>>& result = ptr->GetVertexShaders(extraDefinesHash);
    return VectorToHandleArray(result, "Array<ShaderVariation@>");
}

// explicit Pass::Pass(const String& name) | File: ../Graphics/Technique.h
static Pass* Pass_Pass_String(const String &name)
{
    return new Pass(name);
}

#ifdef URHO3D_PHYSICS
// explicit PhysicsWorld::PhysicsWorld(Context* context) | File: ../Physics/PhysicsWorld.h
static PhysicsWorld* PhysicsWorld_PhysicsWorld_Context()
{
    return new PhysicsWorld(GetScriptContext());
}
#endif

#ifdef URHO3D_PHYSICS
// void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
static void PhysicsWorld_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool(PhysicsWorld* ptr, CScriptArray* exceptions_conv, bool onlyUserData)
{
    PODVector<StringHash> exceptions = ArrayToPODVector<StringHash>(exceptions_conv);
    ptr->UnsubscribeFromAllEventsExcept(exceptions, onlyUserData);
}
#endif

#ifdef URHO3D_URHO2D
// explicit PhysicsWorld2D::PhysicsWorld2D(Context* context) | File: ../Urho2D/PhysicsWorld2D.h
static PhysicsWorld2D* PhysicsWorld2D_PhysicsWorld2D_Context()
{
    return new PhysicsWorld2D(GetScriptContext());
}
#endif

#ifdef URHO3D_URHO2D
// void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
static void PhysicsWorld2D_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool(PhysicsWorld2D* ptr, CScriptArray* exceptions_conv, bool onlyUserData)
{
    PODVector<StringHash> exceptions = ArrayToPODVector<StringHash>(exceptions_conv);
    ptr->UnsubscribeFromAllEventsExcept(exceptions, onlyUserData);
}
#endif

// Plane::Plane(const Plane& plane) noexcept=default | File: ../Math/Plane.h
static void Plane_Plane_Plane(Plane* ptr, const Plane &plane)
{
    new(ptr) Plane(plane);
}

// Plane::Plane(const Vector3& v0, const Vector3& v1, const Vector3& v2) noexcept | File: ../Math/Plane.h
static void Plane_Plane_Vector3_Vector3_Vector3(Plane* ptr, const Vector3 &v0, const Vector3 &v1, const Vector3 &v2)
{
    new(ptr) Plane(v0, v1, v2);
}

// Plane::Plane(const Vector3& normal, const Vector3& point) noexcept | File: ../Math/Plane.h
static void Plane_Plane_Vector3_Vector3(Plane* ptr, const Vector3 &normal, const Vector3 &point)
{
    new(ptr) Plane(normal, point);
}

// explicit Plane::Plane(const Vector4& plane) noexcept | File: ../Math/Plane.h
static void Plane_Plane_Vector4(Plane* ptr, const Vector4 &plane)
{
    new(ptr) Plane(plane);
}

// void Polyhedron::AddFace(const PODVector<Vector3>& face) | File: ../Math/Polyhedron.h
static void Polyhedron_AddFace_PODVectorVector3(Polyhedron* ptr, CScriptArray* face_conv)
{
    PODVector<Vector3> face = ArrayToPODVector<Vector3>(face_conv);
    ptr->AddFace(face);
}

// Polyhedron::Polyhedron(const Polyhedron& polyhedron) | File: ../Math/Polyhedron.h
static void Polyhedron_Polyhedron_Polyhedron(Polyhedron* ptr, const Polyhedron &polyhedron)
{
    new(ptr) Polyhedron(polyhedron);
}

// explicit Polyhedron::Polyhedron(const BoundingBox& box) | File: ../Math/Polyhedron.h
static void Polyhedron_Polyhedron_BoundingBox(Polyhedron* ptr, const BoundingBox &box)
{
    new(ptr) Polyhedron(box);
}

// explicit Polyhedron::Polyhedron(const Frustum& frustum) | File: ../Math/Polyhedron.h
static void Polyhedron_Polyhedron_Frustum(Polyhedron* ptr, const Frustum &frustum)
{
    new(ptr) Polyhedron(frustum);
}

// explicit Profiler::Profiler(Context* context) | File: ../Core/Profiler.h
static Profiler* Profiler_Profiler_Context()
{
    return new Profiler(GetScriptContext());
}

// void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
static void Profiler_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool(Profiler* ptr, CScriptArray* exceptions_conv, bool onlyUserData)
{
    PODVector<StringHash> exceptions = ArrayToPODVector<StringHash>(exceptions_conv);
    ptr->UnsubscribeFromAllEventsExcept(exceptions, onlyUserData);
}

// void UIElement::AddTags(const StringVector& tags) | File: ../UI/UIElement.h
static void ProgressBar_AddTags_StringVector(ProgressBar* ptr, CScriptArray* tags_conv)
{
    StringVector tags = ArrayToVector<String>(tags_conv);
    ptr->AddTags(tags);
}

// const Vector<SharedPtr<UIElement>>& UIElement::GetChildren() const | File: ../UI/UIElement.h
static CScriptArray* ProgressBar_GetChildren_void(ProgressBar* ptr)
{
    const Vector<SharedPtr<UIElement>>& result = ptr->GetChildren();
    return VectorToHandleArray(result, "Array<UIElement@>");
}

// PODVector<UIElement*> UIElement::GetChildren(bool recursive) const | File: ../UI/UIElement.h
static CScriptArray* ProgressBar_GetChildren_bool(ProgressBar* ptr, bool recursive)
{
    PODVector<UIElement*> result = ptr->GetChildren(recursive);
    return VectorToHandleArray(result, "Array<UIElement@>");
}

// PODVector<UIElement*> UIElement::GetChildrenWithTag(const String& tag, bool recursive=false) const | File: ../UI/UIElement.h
static CScriptArray* ProgressBar_GetChildrenWithTag_String_bool(ProgressBar* ptr, const String& tag, bool recursive)
{
    PODVector<UIElement*> result = ptr->GetChildrenWithTag(tag, recursive);
    return VectorToHandleArray(result, "Array<UIElement@>");
}

// const StringVector& UIElement::GetTags() const | File: ../UI/UIElement.h
static CScriptArray* ProgressBar_GetTags_void(ProgressBar* ptr)
{
    const StringVector& result = ptr->GetTags();
    return VectorToArray<String>(result, "Array<String>");
}

// explicit ProgressBar::ProgressBar(Context* context) | File: ../UI/ProgressBar.h
static ProgressBar* ProgressBar_ProgressBar_Context()
{
    return new ProgressBar(GetScriptContext());
}

// void UIElement::SetTags(const StringVector& tags) | File: ../UI/UIElement.h
static void ProgressBar_SetTags_StringVector(ProgressBar* ptr, CScriptArray* tags_conv)
{
    StringVector tags = ArrayToVector<String>(tags_conv);
    ptr->SetTags(tags);
}

// void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
static void ProgressBar_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool(ProgressBar* ptr, CScriptArray* exceptions_conv, bool onlyUserData)
{
    PODVector<StringHash> exceptions = ArrayToPODVector<StringHash>(exceptions_conv);
    ptr->UnsubscribeFromAllEventsExcept(exceptions, onlyUserData);
}

#ifdef URHO3D_URHO2D
// PropertySet2D::PropertySet2D() | File: ../Urho2D/TileMapDefs2D.h
static PropertySet2D* PropertySet2D_PropertySet2D_void()
{
    return new PropertySet2D();
}
#endif

void ASRegisterGenerated_Members_P(asIScriptEngine* engine)
{
    // void RefCounted::AddRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("PackageFile", asBEHAVE_ADDREF, "void f()", AS_METHODPR(PackageFile, AddRef, (), void), AS_CALL_THISCALL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // bool PackageFile::Exists(const String& fileName) const | File: ../IO/PackageFile.h
    engine->RegisterObjectMethod("PackageFile", "bool Exists(const String&in) const", AS_METHODPR(PackageFile, Exists, (const String&) const, bool), AS_CALL_THISCALL);
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("PackageFile", "bool GetBlockEvents() const", AS_METHODPR(PackageFile, GetBlockEvents, () const, bool), AS_CALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("PackageFile", "const String& GetCategory() const", AS_METHODPR(PackageFile, GetCategory, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("PackageFile", "const String& get_category() const", AS_METHODPR(PackageFile, GetCategory, () const, const String&), AS_CALL_THISCALL);
    // unsigned PackageFile::GetChecksum() const | File: ../IO/PackageFile.h
    engine->RegisterObjectMethod("PackageFile", "uint GetChecksum() const", AS_METHODPR(PackageFile, GetChecksum, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("PackageFile", "uint get_checksum() const", AS_METHODPR(PackageFile, GetChecksum, () const, unsigned), AS_CALL_THISCALL);
    // Context* Object::GetContext() const | File: ../Core/Object.h
    // Error: type "Context*" can used only as function parameter
    // const HashMap<String, PackageEntry>& PackageFile::GetEntries() const | File: ../IO/PackageFile.h
    // Error: type "const HashMap<String, PackageEntry>&" can not automatically bind
    // const PackageEntry* PackageFile::GetEntry(const String& fileName) const | File: ../IO/PackageFile.h
    // Error: type "const PackageEntry*" can not automatically bind
    // const Vector<String> PackageFile::GetEntryNames() const | File: ../IO/PackageFile.h
    engine->RegisterObjectMethod("PackageFile", "Array<String>@ GetEntryNames() const", AS_FUNCTION_OBJFIRST(PackageFile_GetEntryNames_void), AS_CALL_CDECL_OBJFIRST);
    // VariantMap& Object::GetEventDataMap() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("PackageFile", "VariantMap& GetEventDataMap() const", AS_METHODPR(PackageFile, GetEventDataMap, () const, VariantMap&), AS_CALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("PackageFile", "Object@+ GetEventSender() const", AS_METHODPR(PackageFile, GetEventSender, () const, Object*), AS_CALL_THISCALL);
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("PackageFile", "const Variant& GetGlobalVar(StringHash) const", AS_METHODPR(PackageFile, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("PackageFile", "const Variant& get_globalVar(StringHash) const", AS_METHODPR(PackageFile, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("PackageFile", "const VariantMap& GetGlobalVars() const", AS_METHODPR(PackageFile, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("PackageFile", "const VariantMap& get_globalVars() const", AS_METHODPR(PackageFile, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    // const String& PackageFile::GetName() const | File: ../IO/PackageFile.h
    engine->RegisterObjectMethod("PackageFile", "const String& GetName() const", AS_METHODPR(PackageFile, GetName, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("PackageFile", "const String& get_name() const", AS_METHODPR(PackageFile, GetName, () const, const String&), AS_CALL_THISCALL);
    // StringHash PackageFile::GetNameHash() const | File: ../IO/PackageFile.h
    engine->RegisterObjectMethod("PackageFile", "StringHash GetNameHash() const", AS_METHODPR(PackageFile, GetNameHash, () const, StringHash), AS_CALL_THISCALL);
    // unsigned PackageFile::GetNumFiles() const | File: ../IO/PackageFile.h
    engine->RegisterObjectMethod("PackageFile", "uint GetNumFiles() const", AS_METHODPR(PackageFile, GetNumFiles, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("PackageFile", "uint get_numFiles() const", AS_METHODPR(PackageFile, GetNumFiles, () const, unsigned), AS_CALL_THISCALL);
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("PackageFile", "Object@+ GetSubsystem(StringHash) const", AS_METHODPR(PackageFile, GetSubsystem, (StringHash) const, Object*), AS_CALL_THISCALL);
    // template<class T> T* Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // unsigned PackageFile::GetTotalDataSize() const | File: ../IO/PackageFile.h
    engine->RegisterObjectMethod("PackageFile", "uint GetTotalDataSize() const", AS_METHODPR(PackageFile, GetTotalDataSize, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("PackageFile", "uint get_totalDataSize() const", AS_METHODPR(PackageFile, GetTotalDataSize, () const, unsigned), AS_CALL_THISCALL);
    // unsigned PackageFile::GetTotalSize() const | File: ../IO/PackageFile.h
    engine->RegisterObjectMethod("PackageFile", "uint GetTotalSize() const", AS_METHODPR(PackageFile, GetTotalSize, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("PackageFile", "uint get_totalSize() const", AS_METHODPR(PackageFile, GetTotalSize, () const, unsigned), AS_CALL_THISCALL);
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("PackageFile", "StringHash GetType() const", AS_METHODPR(PackageFile, GetType, () const, StringHash), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("PackageFile", "StringHash get_type() const", AS_METHODPR(PackageFile, GetType, () const, StringHash), AS_CALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("PackageFile", "const String& GetTypeName() const", AS_METHODPR(PackageFile, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("PackageFile", "const String& get_typeName() const", AS_METHODPR(PackageFile, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("PackageFile", "bool HasEventHandlers() const", AS_METHODPR(PackageFile, HasEventHandlers, () const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("PackageFile", "bool HasSubscribedToEvent(StringHash) const", AS_METHODPR(PackageFile, HasSubscribedToEvent, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("PackageFile", "bool HasSubscribedToEvent(Object@+, StringHash) const", AS_METHODPR(PackageFile, HasSubscribedToEvent, (Object*, StringHash) const, bool), AS_CALL_THISCALL);
    // bool PackageFile::IsCompressed() const | File: ../IO/PackageFile.h
    engine->RegisterObjectMethod("PackageFile", "bool IsCompressed() const", AS_METHODPR(PackageFile, IsCompressed, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("PackageFile", "bool get_compressed() const", AS_METHODPR(PackageFile, IsCompressed, () const, bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("PackageFile", "bool IsInstanceOf(StringHash) const", AS_METHODPR(PackageFile, IsInstanceOf, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("PackageFile", "void OnEvent(Object@+, StringHash, VariantMap&)", AS_METHODPR(PackageFile, OnEvent, (Object*, StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // bool PackageFile::Open(const String& fileName, unsigned startOffset=0) | File: ../IO/PackageFile.h
    engine->RegisterObjectMethod("PackageFile", "bool Open(const String&in, uint = 0)", AS_METHODPR(PackageFile, Open, (const String&, unsigned), bool), AS_CALL_THISCALL);
    // explicit PackageFile::PackageFile(Context* context) | File: ../IO/PackageFile.h
    engine->RegisterObjectBehaviour("PackageFile", asBEHAVE_FACTORY, "PackageFile@+ f()", AS_FUNCTION(PackageFile_PackageFile_Context), AS_CALL_CDECL);
    // PackageFile::PackageFile(Context* context, const String& fileName, unsigned startOffset=0) | File: ../IO/PackageFile.h
    engine->RegisterObjectBehaviour("PackageFile", asBEHAVE_FACTORY, "PackageFile@+ f(const String&in, uint = 0)", AS_FUNCTION(PackageFile_PackageFile_Context_String_unsigned), AS_CALL_CDECL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("PackageFile", "int Refs() const", AS_METHODPR(PackageFile, Refs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("PackageFile", "int get_refs() const", AS_METHODPR(PackageFile, Refs, () const, int), AS_CALL_THISCALL);
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("PackageFile", asBEHAVE_RELEASE, "void f()", AS_METHODPR(PackageFile, ReleaseRef, (), void), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("PackageFile", "void SendEvent(StringHash)", AS_METHODPR(PackageFile, SendEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("PackageFile", "void SendEvent(StringHash, VariantMap&)", AS_METHODPR(PackageFile, SendEvent, (StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("PackageFile", "void SetBlockEvents(bool)", AS_METHODPR(PackageFile, SetBlockEvents, (bool), void), AS_CALL_THISCALL);
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("PackageFile", "void SetGlobalVar(StringHash, const Variant&in)", AS_METHODPR(PackageFile, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("PackageFile", "void set_globalVar(StringHash, const Variant&in)", AS_METHODPR(PackageFile, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod("PackageFile", "void UnsubscribeFromAllEvents()", AS_METHODPR(PackageFile, UnsubscribeFromAllEvents, (), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("PackageFile", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", AS_FUNCTION_OBJFIRST(PackageFile_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), AS_CALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("PackageFile", "void UnsubscribeFromEvent(StringHash)", AS_METHODPR(PackageFile, UnsubscribeFromEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("PackageFile", "void UnsubscribeFromEvent(Object@+, StringHash)", AS_METHODPR(PackageFile, UnsubscribeFromEvent, (Object*, StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("PackageFile", "void UnsubscribeFromEvents(Object@+)", AS_METHODPR(PackageFile, UnsubscribeFromEvents, (Object*), void), AS_CALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("PackageFile", "int WeakRefs() const", AS_METHODPR(PackageFile, WeakRefs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("PackageFile", "int get_weakRefs() const", AS_METHODPR(PackageFile, WeakRefs, () const, int), AS_CALL_THISCALL);
#ifdef REGISTER_MANUAL_PART_Object
    REGISTER_MANUAL_PART_Object(PackageFile, "PackageFile")
#endif
#ifdef REGISTER_MANUAL_PART_RefCounted
    REGISTER_MANUAL_PART_RefCounted(PackageFile, "PackageFile")
#endif
#ifdef REGISTER_MANUAL_PART_PackageFile
    REGISTER_MANUAL_PART_PackageFile(PackageFile, "PackageFile")
#endif
    RegisterSubclass<Object, PackageFile>(engine, "Object", "PackageFile");
    RegisterSubclass<RefCounted, PackageFile>(engine, "RefCounted", "PackageFile");

    // void ParticleEffect::AddColorFrame(const ColorFrame& colorFrame) | File: ../Graphics/ParticleEffect.h
    engine->RegisterObjectMethod("ParticleEffect", "void AddColorFrame(const ColorFrame&in)", AS_METHODPR(ParticleEffect, AddColorFrame, (const ColorFrame&), void), AS_CALL_THISCALL);
    // void ParticleEffect::AddColorTime(const Color& color, float time) | File: ../Graphics/ParticleEffect.h
    engine->RegisterObjectMethod("ParticleEffect", "void AddColorTime(const Color&in, float)", AS_METHODPR(ParticleEffect, AddColorTime, (const Color&, float), void), AS_CALL_THISCALL);
    // void RefCounted::AddRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("ParticleEffect", asBEHAVE_ADDREF, "void f()", AS_METHODPR(ParticleEffect, AddRef, (), void), AS_CALL_THISCALL);
    // void ParticleEffect::AddTextureFrame(const TextureFrame& textureFrame) | File: ../Graphics/ParticleEffect.h
    engine->RegisterObjectMethod("ParticleEffect", "void AddTextureFrame(const TextureFrame&in)", AS_METHODPR(ParticleEffect, AddTextureFrame, (const TextureFrame&), void), AS_CALL_THISCALL);
    // void ParticleEffect::AddTextureTime(const Rect& uv, float time) | File: ../Graphics/ParticleEffect.h
    engine->RegisterObjectMethod("ParticleEffect", "void AddTextureTime(const Rect&in, float)", AS_METHODPR(ParticleEffect, AddTextureTime, (const Rect&, float), void), AS_CALL_THISCALL);
    // bool ParticleEffect::BeginLoad(Deserializer& source) override | File: ../Graphics/ParticleEffect.h
    engine->RegisterObjectMethod("ParticleEffect", "bool BeginLoad(Deserializer&)", AS_METHODPR(ParticleEffect, BeginLoad, (Deserializer&), bool), AS_CALL_THISCALL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // SharedPtr<ParticleEffect> ParticleEffect::Clone(const String& cloneName=String::EMPTY) const | File: ../Graphics/ParticleEffect.h
    engine->RegisterObjectMethod("ParticleEffect", "ParticleEffect@+ Clone(const String&in = String::EMPTY) const", AS_FUNCTION_OBJFIRST(ParticleEffect_Clone_String), AS_CALL_CDECL_OBJFIRST);
    // bool ParticleEffect::EndLoad() override | File: ../Graphics/ParticleEffect.h
    engine->RegisterObjectMethod("ParticleEffect", "bool EndLoad()", AS_METHODPR(ParticleEffect, EndLoad, (), bool), AS_CALL_THISCALL);
    // float ParticleEffect::GetActiveTime() const | File: ../Graphics/ParticleEffect.h
    engine->RegisterObjectMethod("ParticleEffect", "float GetActiveTime() const", AS_METHODPR(ParticleEffect, GetActiveTime, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEffect", "float get_activeTime() const", AS_METHODPR(ParticleEffect, GetActiveTime, () const, float), AS_CALL_THISCALL);
    // float ParticleEffect::GetAnimationLodBias() const | File: ../Graphics/ParticleEffect.h
    engine->RegisterObjectMethod("ParticleEffect", "float GetAnimationLodBias() const", AS_METHODPR(ParticleEffect, GetAnimationLodBias, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEffect", "float get_animationLodBias() const", AS_METHODPR(ParticleEffect, GetAnimationLodBias, () const, float), AS_CALL_THISCALL);
    // AsyncLoadState Resource::GetAsyncLoadState() const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("ParticleEffect", "AsyncLoadState GetAsyncLoadState() const", AS_METHODPR(ParticleEffect, GetAsyncLoadState, () const, AsyncLoadState), AS_CALL_THISCALL);
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ParticleEffect", "bool GetBlockEvents() const", AS_METHODPR(ParticleEffect, GetBlockEvents, () const, bool), AS_CALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ParticleEffect", "const String& GetCategory() const", AS_METHODPR(ParticleEffect, GetCategory, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEffect", "const String& get_category() const", AS_METHODPR(ParticleEffect, GetCategory, () const, const String&), AS_CALL_THISCALL);
    // const ColorFrame* ParticleEffect::GetColorFrame(unsigned index) const | File: ../Graphics/ParticleEffect.h
    engine->RegisterObjectMethod("ParticleEffect", "ColorFrame@+ GetColorFrame(uint) const", AS_METHODPR(ParticleEffect, GetColorFrame, (unsigned) const, const ColorFrame*), AS_CALL_THISCALL);
    // const Vector<ColorFrame>& ParticleEffect::GetColorFrames() const | File: ../Graphics/ParticleEffect.h
    // Error: type "const Vector<ColorFrame>&" can not automatically bind
    // const Vector3& ParticleEffect::GetConstantForce() const | File: ../Graphics/ParticleEffect.h
    engine->RegisterObjectMethod("ParticleEffect", "const Vector3& GetConstantForce() const", AS_METHODPR(ParticleEffect, GetConstantForce, () const, const Vector3&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEffect", "const Vector3& get_constantForce() const", AS_METHODPR(ParticleEffect, GetConstantForce, () const, const Vector3&), AS_CALL_THISCALL);
    // Context* Object::GetContext() const | File: ../Core/Object.h
    // Error: type "Context*" can used only as function parameter
    // float ParticleEffect::GetDampingForce() const | File: ../Graphics/ParticleEffect.h
    engine->RegisterObjectMethod("ParticleEffect", "float GetDampingForce() const", AS_METHODPR(ParticleEffect, GetDampingForce, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEffect", "float get_dampingForce() const", AS_METHODPR(ParticleEffect, GetDampingForce, () const, float), AS_CALL_THISCALL);
    // const Vector3& ParticleEffect::GetEmitterSize() const | File: ../Graphics/ParticleEffect.h
    engine->RegisterObjectMethod("ParticleEffect", "const Vector3& GetEmitterSize() const", AS_METHODPR(ParticleEffect, GetEmitterSize, () const, const Vector3&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEffect", "const Vector3& get_emitterSize() const", AS_METHODPR(ParticleEffect, GetEmitterSize, () const, const Vector3&), AS_CALL_THISCALL);
    // EmitterType ParticleEffect::GetEmitterType() const | File: ../Graphics/ParticleEffect.h
    engine->RegisterObjectMethod("ParticleEffect", "EmitterType GetEmitterType() const", AS_METHODPR(ParticleEffect, GetEmitterType, () const, EmitterType), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEffect", "EmitterType get_emitterType() const", AS_METHODPR(ParticleEffect, GetEmitterType, () const, EmitterType), AS_CALL_THISCALL);
    // VariantMap& Object::GetEventDataMap() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ParticleEffect", "VariantMap& GetEventDataMap() const", AS_METHODPR(ParticleEffect, GetEventDataMap, () const, VariantMap&), AS_CALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ParticleEffect", "Object@+ GetEventSender() const", AS_METHODPR(ParticleEffect, GetEventSender, () const, Object*), AS_CALL_THISCALL);
    // FaceCameraMode ParticleEffect::GetFaceCameraMode() const | File: ../Graphics/ParticleEffect.h
    engine->RegisterObjectMethod("ParticleEffect", "FaceCameraMode GetFaceCameraMode() const", AS_METHODPR(ParticleEffect, GetFaceCameraMode, () const, FaceCameraMode), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEffect", "FaceCameraMode get_faceCameraMode() const", AS_METHODPR(ParticleEffect, GetFaceCameraMode, () const, FaceCameraMode), AS_CALL_THISCALL);
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ParticleEffect", "const Variant& GetGlobalVar(StringHash) const", AS_METHODPR(ParticleEffect, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEffect", "const Variant& get_globalVar(StringHash) const", AS_METHODPR(ParticleEffect, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ParticleEffect", "const VariantMap& GetGlobalVars() const", AS_METHODPR(ParticleEffect, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEffect", "const VariantMap& get_globalVars() const", AS_METHODPR(ParticleEffect, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    // float ParticleEffect::GetInactiveTime() const | File: ../Graphics/ParticleEffect.h
    engine->RegisterObjectMethod("ParticleEffect", "float GetInactiveTime() const", AS_METHODPR(ParticleEffect, GetInactiveTime, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEffect", "float get_inactiveTime() const", AS_METHODPR(ParticleEffect, GetInactiveTime, () const, float), AS_CALL_THISCALL);
    // Material* ParticleEffect::GetMaterial() const | File: ../Graphics/ParticleEffect.h
    engine->RegisterObjectMethod("ParticleEffect", "Material@+ GetMaterial() const", AS_METHODPR(ParticleEffect, GetMaterial, () const, Material*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEffect", "Material@+ get_material() const", AS_METHODPR(ParticleEffect, GetMaterial, () const, Material*), AS_CALL_THISCALL);
    // const Vector3& ParticleEffect::GetMaxDirection() const | File: ../Graphics/ParticleEffect.h
    engine->RegisterObjectMethod("ParticleEffect", "const Vector3& GetMaxDirection() const", AS_METHODPR(ParticleEffect, GetMaxDirection, () const, const Vector3&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEffect", "const Vector3& get_maxDirection() const", AS_METHODPR(ParticleEffect, GetMaxDirection, () const, const Vector3&), AS_CALL_THISCALL);
    // float ParticleEffect::GetMaxEmissionRate() const | File: ../Graphics/ParticleEffect.h
    engine->RegisterObjectMethod("ParticleEffect", "float GetMaxEmissionRate() const", AS_METHODPR(ParticleEffect, GetMaxEmissionRate, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEffect", "float get_maxEmissionRate() const", AS_METHODPR(ParticleEffect, GetMaxEmissionRate, () const, float), AS_CALL_THISCALL);
    // const Vector2& ParticleEffect::GetMaxParticleSize() const | File: ../Graphics/ParticleEffect.h
    engine->RegisterObjectMethod("ParticleEffect", "const Vector2& GetMaxParticleSize() const", AS_METHODPR(ParticleEffect, GetMaxParticleSize, () const, const Vector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEffect", "const Vector2& get_maxParticleSize() const", AS_METHODPR(ParticleEffect, GetMaxParticleSize, () const, const Vector2&), AS_CALL_THISCALL);
    // float ParticleEffect::GetMaxRotation() const | File: ../Graphics/ParticleEffect.h
    engine->RegisterObjectMethod("ParticleEffect", "float GetMaxRotation() const", AS_METHODPR(ParticleEffect, GetMaxRotation, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEffect", "float get_maxRotation() const", AS_METHODPR(ParticleEffect, GetMaxRotation, () const, float), AS_CALL_THISCALL);
    // float ParticleEffect::GetMaxRotationSpeed() const | File: ../Graphics/ParticleEffect.h
    engine->RegisterObjectMethod("ParticleEffect", "float GetMaxRotationSpeed() const", AS_METHODPR(ParticleEffect, GetMaxRotationSpeed, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEffect", "float get_maxRotationSpeed() const", AS_METHODPR(ParticleEffect, GetMaxRotationSpeed, () const, float), AS_CALL_THISCALL);
    // float ParticleEffect::GetMaxTimeToLive() const | File: ../Graphics/ParticleEffect.h
    engine->RegisterObjectMethod("ParticleEffect", "float GetMaxTimeToLive() const", AS_METHODPR(ParticleEffect, GetMaxTimeToLive, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEffect", "float get_maxTimeToLive() const", AS_METHODPR(ParticleEffect, GetMaxTimeToLive, () const, float), AS_CALL_THISCALL);
    // float ParticleEffect::GetMaxVelocity() const | File: ../Graphics/ParticleEffect.h
    engine->RegisterObjectMethod("ParticleEffect", "float GetMaxVelocity() const", AS_METHODPR(ParticleEffect, GetMaxVelocity, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEffect", "float get_maxVelocity() const", AS_METHODPR(ParticleEffect, GetMaxVelocity, () const, float), AS_CALL_THISCALL);
    // unsigned Resource::GetMemoryUse() const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("ParticleEffect", "uint GetMemoryUse() const", AS_METHODPR(ParticleEffect, GetMemoryUse, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEffect", "uint get_memoryUse() const", AS_METHODPR(ParticleEffect, GetMemoryUse, () const, unsigned), AS_CALL_THISCALL);
    // const Vector3& ParticleEffect::GetMinDirection() const | File: ../Graphics/ParticleEffect.h
    engine->RegisterObjectMethod("ParticleEffect", "const Vector3& GetMinDirection() const", AS_METHODPR(ParticleEffect, GetMinDirection, () const, const Vector3&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEffect", "const Vector3& get_minDirection() const", AS_METHODPR(ParticleEffect, GetMinDirection, () const, const Vector3&), AS_CALL_THISCALL);
    // float ParticleEffect::GetMinEmissionRate() const | File: ../Graphics/ParticleEffect.h
    engine->RegisterObjectMethod("ParticleEffect", "float GetMinEmissionRate() const", AS_METHODPR(ParticleEffect, GetMinEmissionRate, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEffect", "float get_minEmissionRate() const", AS_METHODPR(ParticleEffect, GetMinEmissionRate, () const, float), AS_CALL_THISCALL);
    // const Vector2& ParticleEffect::GetMinParticleSize() const | File: ../Graphics/ParticleEffect.h
    engine->RegisterObjectMethod("ParticleEffect", "const Vector2& GetMinParticleSize() const", AS_METHODPR(ParticleEffect, GetMinParticleSize, () const, const Vector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEffect", "const Vector2& get_minParticleSize() const", AS_METHODPR(ParticleEffect, GetMinParticleSize, () const, const Vector2&), AS_CALL_THISCALL);
    // float ParticleEffect::GetMinRotation() const | File: ../Graphics/ParticleEffect.h
    engine->RegisterObjectMethod("ParticleEffect", "float GetMinRotation() const", AS_METHODPR(ParticleEffect, GetMinRotation, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEffect", "float get_minRotation() const", AS_METHODPR(ParticleEffect, GetMinRotation, () const, float), AS_CALL_THISCALL);
    // float ParticleEffect::GetMinRotationSpeed() const | File: ../Graphics/ParticleEffect.h
    engine->RegisterObjectMethod("ParticleEffect", "float GetMinRotationSpeed() const", AS_METHODPR(ParticleEffect, GetMinRotationSpeed, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEffect", "float get_minRotationSpeed() const", AS_METHODPR(ParticleEffect, GetMinRotationSpeed, () const, float), AS_CALL_THISCALL);
    // float ParticleEffect::GetMinTimeToLive() const | File: ../Graphics/ParticleEffect.h
    engine->RegisterObjectMethod("ParticleEffect", "float GetMinTimeToLive() const", AS_METHODPR(ParticleEffect, GetMinTimeToLive, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEffect", "float get_minTimeToLive() const", AS_METHODPR(ParticleEffect, GetMinTimeToLive, () const, float), AS_CALL_THISCALL);
    // float ParticleEffect::GetMinVelocity() const | File: ../Graphics/ParticleEffect.h
    engine->RegisterObjectMethod("ParticleEffect", "float GetMinVelocity() const", AS_METHODPR(ParticleEffect, GetMinVelocity, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEffect", "float get_minVelocity() const", AS_METHODPR(ParticleEffect, GetMinVelocity, () const, float), AS_CALL_THISCALL);
    // const String& Resource::GetName() const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("ParticleEffect", "const String& GetName() const", AS_METHODPR(ParticleEffect, GetName, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEffect", "const String& get_name() const", AS_METHODPR(ParticleEffect, GetName, () const, const String&), AS_CALL_THISCALL);
    // StringHash Resource::GetNameHash() const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("ParticleEffect", "StringHash GetNameHash() const", AS_METHODPR(ParticleEffect, GetNameHash, () const, StringHash), AS_CALL_THISCALL);
    // unsigned ParticleEffect::GetNumColorFrames() const | File: ../Graphics/ParticleEffect.h
    engine->RegisterObjectMethod("ParticleEffect", "uint GetNumColorFrames() const", AS_METHODPR(ParticleEffect, GetNumColorFrames, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEffect", "uint get_numColorFrames() const", AS_METHODPR(ParticleEffect, GetNumColorFrames, () const, unsigned), AS_CALL_THISCALL);
    // unsigned ParticleEffect::GetNumParticles() const | File: ../Graphics/ParticleEffect.h
    engine->RegisterObjectMethod("ParticleEffect", "uint GetNumParticles() const", AS_METHODPR(ParticleEffect, GetNumParticles, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEffect", "uint get_numParticles() const", AS_METHODPR(ParticleEffect, GetNumParticles, () const, unsigned), AS_CALL_THISCALL);
    // unsigned ParticleEffect::GetNumTextureFrames() const | File: ../Graphics/ParticleEffect.h
    engine->RegisterObjectMethod("ParticleEffect", "uint GetNumTextureFrames() const", AS_METHODPR(ParticleEffect, GetNumTextureFrames, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEffect", "uint get_numTextureFrames() const", AS_METHODPR(ParticleEffect, GetNumTextureFrames, () const, unsigned), AS_CALL_THISCALL);
    // Vector3 ParticleEffect::GetRandomDirection() const | File: ../Graphics/ParticleEffect.h
    engine->RegisterObjectMethod("ParticleEffect", "Vector3 GetRandomDirection() const", AS_METHODPR(ParticleEffect, GetRandomDirection, () const, Vector3), AS_CALL_THISCALL);
    // float ParticleEffect::GetRandomRotation() const | File: ../Graphics/ParticleEffect.h
    engine->RegisterObjectMethod("ParticleEffect", "float GetRandomRotation() const", AS_METHODPR(ParticleEffect, GetRandomRotation, () const, float), AS_CALL_THISCALL);
    // float ParticleEffect::GetRandomRotationSpeed() const | File: ../Graphics/ParticleEffect.h
    engine->RegisterObjectMethod("ParticleEffect", "float GetRandomRotationSpeed() const", AS_METHODPR(ParticleEffect, GetRandomRotationSpeed, () const, float), AS_CALL_THISCALL);
    // Vector2 ParticleEffect::GetRandomSize() const | File: ../Graphics/ParticleEffect.h
    engine->RegisterObjectMethod("ParticleEffect", "Vector2 GetRandomSize() const", AS_METHODPR(ParticleEffect, GetRandomSize, () const, Vector2), AS_CALL_THISCALL);
    // float ParticleEffect::GetRandomTimeToLive() const | File: ../Graphics/ParticleEffect.h
    engine->RegisterObjectMethod("ParticleEffect", "float GetRandomTimeToLive() const", AS_METHODPR(ParticleEffect, GetRandomTimeToLive, () const, float), AS_CALL_THISCALL);
    // float ParticleEffect::GetRandomVelocity() const | File: ../Graphics/ParticleEffect.h
    engine->RegisterObjectMethod("ParticleEffect", "float GetRandomVelocity() const", AS_METHODPR(ParticleEffect, GetRandomVelocity, () const, float), AS_CALL_THISCALL);
    // float ParticleEffect::GetSizeAdd() const | File: ../Graphics/ParticleEffect.h
    engine->RegisterObjectMethod("ParticleEffect", "float GetSizeAdd() const", AS_METHODPR(ParticleEffect, GetSizeAdd, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEffect", "float get_sizeAdd() const", AS_METHODPR(ParticleEffect, GetSizeAdd, () const, float), AS_CALL_THISCALL);
    // float ParticleEffect::GetSizeMul() const | File: ../Graphics/ParticleEffect.h
    engine->RegisterObjectMethod("ParticleEffect", "float GetSizeMul() const", AS_METHODPR(ParticleEffect, GetSizeMul, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEffect", "float get_sizeMul() const", AS_METHODPR(ParticleEffect, GetSizeMul, () const, float), AS_CALL_THISCALL);
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ParticleEffect", "Object@+ GetSubsystem(StringHash) const", AS_METHODPR(ParticleEffect, GetSubsystem, (StringHash) const, Object*), AS_CALL_THISCALL);
    // template<class T> T* Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // const TextureFrame* ParticleEffect::GetTextureFrame(unsigned index) const | File: ../Graphics/ParticleEffect.h
    engine->RegisterObjectMethod("ParticleEffect", "TextureFrame@+ GetTextureFrame(uint) const", AS_METHODPR(ParticleEffect, GetTextureFrame, (unsigned) const, const TextureFrame*), AS_CALL_THISCALL);
    // const Vector<TextureFrame>& ParticleEffect::GetTextureFrames() const | File: ../Graphics/ParticleEffect.h
    // Error: type "const Vector<TextureFrame>&" can not automatically bind
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("ParticleEffect", "StringHash GetType() const", AS_METHODPR(ParticleEffect, GetType, () const, StringHash), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEffect", "StringHash get_type() const", AS_METHODPR(ParticleEffect, GetType, () const, StringHash), AS_CALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("ParticleEffect", "const String& GetTypeName() const", AS_METHODPR(ParticleEffect, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEffect", "const String& get_typeName() const", AS_METHODPR(ParticleEffect, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    // bool ParticleEffect::GetUpdateInvisible() const | File: ../Graphics/ParticleEffect.h
    engine->RegisterObjectMethod("ParticleEffect", "bool GetUpdateInvisible() const", AS_METHODPR(ParticleEffect, GetUpdateInvisible, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEffect", "bool get_updateInvisible() const", AS_METHODPR(ParticleEffect, GetUpdateInvisible, () const, bool), AS_CALL_THISCALL);
    // unsigned Resource::GetUseTimer() | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("ParticleEffect", "uint GetUseTimer()", AS_METHODPR(ParticleEffect, GetUseTimer, (), unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEffect", "uint get_useTimer()", AS_METHODPR(ParticleEffect, GetUseTimer, (), unsigned), AS_CALL_THISCALL);
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ParticleEffect", "bool HasEventHandlers() const", AS_METHODPR(ParticleEffect, HasEventHandlers, () const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ParticleEffect", "bool HasSubscribedToEvent(StringHash) const", AS_METHODPR(ParticleEffect, HasSubscribedToEvent, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ParticleEffect", "bool HasSubscribedToEvent(Object@+, StringHash) const", AS_METHODPR(ParticleEffect, HasSubscribedToEvent, (Object*, StringHash) const, bool), AS_CALL_THISCALL);
    // bool ParticleEffect::IsFixedScreenSize() const | File: ../Graphics/ParticleEffect.h
    engine->RegisterObjectMethod("ParticleEffect", "bool IsFixedScreenSize() const", AS_METHODPR(ParticleEffect, IsFixedScreenSize, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEffect", "bool get_fixedScreenSize() const", AS_METHODPR(ParticleEffect, IsFixedScreenSize, () const, bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ParticleEffect", "bool IsInstanceOf(StringHash) const", AS_METHODPR(ParticleEffect, IsInstanceOf, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // bool ParticleEffect::IsRelative() const | File: ../Graphics/ParticleEffect.h
    engine->RegisterObjectMethod("ParticleEffect", "bool IsRelative() const", AS_METHODPR(ParticleEffect, IsRelative, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEffect", "bool get_relative() const", AS_METHODPR(ParticleEffect, IsRelative, () const, bool), AS_CALL_THISCALL);
    // bool ParticleEffect::IsScaled() const | File: ../Graphics/ParticleEffect.h
    engine->RegisterObjectMethod("ParticleEffect", "bool IsScaled() const", AS_METHODPR(ParticleEffect, IsScaled, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEffect", "bool get_scaled() const", AS_METHODPR(ParticleEffect, IsScaled, () const, bool), AS_CALL_THISCALL);
    // bool ParticleEffect::IsSorted() const | File: ../Graphics/ParticleEffect.h
    engine->RegisterObjectMethod("ParticleEffect", "bool IsSorted() const", AS_METHODPR(ParticleEffect, IsSorted, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEffect", "bool get_sorted() const", AS_METHODPR(ParticleEffect, IsSorted, () const, bool), AS_CALL_THISCALL);
    // bool ParticleEffect::Load(const XMLElement& source) | File: ../Graphics/ParticleEffect.h
    engine->RegisterObjectMethod("ParticleEffect", "bool Load(const XMLElement&in)", AS_METHODPR(ParticleEffect, Load, (const XMLElement&), bool), AS_CALL_THISCALL);
    // bool Resource::LoadFile(const String& fileName) | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("ParticleEffect", "bool LoadFile(const String&in)", AS_METHODPR(ParticleEffect, LoadFile, (const String&), bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEffect", "bool Load(const String&in)", AS_METHODPR(ParticleEffect, LoadFile, (const String&), bool), AS_CALL_THISCALL);
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ParticleEffect", "void OnEvent(Object@+, StringHash, VariantMap&)", AS_METHODPR(ParticleEffect, OnEvent, (Object*, StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // explicit ParticleEffect::ParticleEffect(Context* context) | File: ../Graphics/ParticleEffect.h
    engine->RegisterObjectBehaviour("ParticleEffect", asBEHAVE_FACTORY, "ParticleEffect@+ f()", AS_FUNCTION(ParticleEffect_ParticleEffect_Context), AS_CALL_CDECL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("ParticleEffect", "int Refs() const", AS_METHODPR(ParticleEffect, Refs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEffect", "int get_refs() const", AS_METHODPR(ParticleEffect, Refs, () const, int), AS_CALL_THISCALL);
    // static void ParticleEffect::RegisterObject(Context* context) | File: ../Graphics/ParticleEffect.h
    // Not registered because have @nobind mark
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("ParticleEffect", asBEHAVE_RELEASE, "void f()", AS_METHODPR(ParticleEffect, ReleaseRef, (), void), AS_CALL_THISCALL);
    // void ParticleEffect::RemoveColorFrame(unsigned index) | File: ../Graphics/ParticleEffect.h
    engine->RegisterObjectMethod("ParticleEffect", "void RemoveColorFrame(uint)", AS_METHODPR(ParticleEffect, RemoveColorFrame, (unsigned), void), AS_CALL_THISCALL);
    // void ParticleEffect::RemoveTextureFrame(unsigned index) | File: ../Graphics/ParticleEffect.h
    engine->RegisterObjectMethod("ParticleEffect", "void RemoveTextureFrame(uint)", AS_METHODPR(ParticleEffect, RemoveTextureFrame, (unsigned), void), AS_CALL_THISCALL);
    // void Resource::ResetUseTimer() | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("ParticleEffect", "void ResetUseTimer()", AS_METHODPR(ParticleEffect, ResetUseTimer, (), void), AS_CALL_THISCALL);
    // bool ParticleEffect::Save(Serializer& dest) const override | File: ../Graphics/ParticleEffect.h
    engine->RegisterObjectMethod("ParticleEffect", "bool Save(Serializer&) const", AS_METHODPR(ParticleEffect, Save, (Serializer&) const, bool), AS_CALL_THISCALL);
    // bool ParticleEffect::Save(XMLElement& dest) const | File: ../Graphics/ParticleEffect.h
    engine->RegisterObjectMethod("ParticleEffect", "bool Save(XMLElement&) const", AS_METHODPR(ParticleEffect, Save, (XMLElement&) const, bool), AS_CALL_THISCALL);
    // virtual bool Resource::SaveFile(const String& fileName) const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("ParticleEffect", "bool SaveFile(const String&in) const", AS_METHODPR(ParticleEffect, SaveFile, (const String&) const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEffect", "bool Save(const String&in) const", AS_METHODPR(ParticleEffect, SaveFile, (const String&) const, bool), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ParticleEffect", "void SendEvent(StringHash)", AS_METHODPR(ParticleEffect, SendEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ParticleEffect", "void SendEvent(StringHash, VariantMap&)", AS_METHODPR(ParticleEffect, SendEvent, (StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void ParticleEffect::SetActiveTime(float time) | File: ../Graphics/ParticleEffect.h
    engine->RegisterObjectMethod("ParticleEffect", "void SetActiveTime(float)", AS_METHODPR(ParticleEffect, SetActiveTime, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEffect", "void set_activeTime(float)", AS_METHODPR(ParticleEffect, SetActiveTime, (float), void), AS_CALL_THISCALL);
    // void ParticleEffect::SetAnimationLodBias(float lodBias) | File: ../Graphics/ParticleEffect.h
    engine->RegisterObjectMethod("ParticleEffect", "void SetAnimationLodBias(float)", AS_METHODPR(ParticleEffect, SetAnimationLodBias, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEffect", "void set_animationLodBias(float)", AS_METHODPR(ParticleEffect, SetAnimationLodBias, (float), void), AS_CALL_THISCALL);
    // void Resource::SetAsyncLoadState(AsyncLoadState newState) | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("ParticleEffect", "void SetAsyncLoadState(AsyncLoadState)", AS_METHODPR(ParticleEffect, SetAsyncLoadState, (AsyncLoadState), void), AS_CALL_THISCALL);
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ParticleEffect", "void SetBlockEvents(bool)", AS_METHODPR(ParticleEffect, SetBlockEvents, (bool), void), AS_CALL_THISCALL);
    // void ParticleEffect::SetColorFrame(unsigned index, const ColorFrame& colorFrame) | File: ../Graphics/ParticleEffect.h
    engine->RegisterObjectMethod("ParticleEffect", "void SetColorFrame(uint, const ColorFrame&in)", AS_METHODPR(ParticleEffect, SetColorFrame, (unsigned, const ColorFrame&), void), AS_CALL_THISCALL);
    // void ParticleEffect::SetColorFrames(const Vector<ColorFrame>& colorFrames) | File: ../Graphics/ParticleEffect.h
    // Error: type "const Vector<ColorFrame>&" can not automatically bind
    // void ParticleEffect::SetConstantForce(const Vector3& force) | File: ../Graphics/ParticleEffect.h
    engine->RegisterObjectMethod("ParticleEffect", "void SetConstantForce(const Vector3&in)", AS_METHODPR(ParticleEffect, SetConstantForce, (const Vector3&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEffect", "void set_constantForce(const Vector3&in)", AS_METHODPR(ParticleEffect, SetConstantForce, (const Vector3&), void), AS_CALL_THISCALL);
    // void ParticleEffect::SetDampingForce(float force) | File: ../Graphics/ParticleEffect.h
    engine->RegisterObjectMethod("ParticleEffect", "void SetDampingForce(float)", AS_METHODPR(ParticleEffect, SetDampingForce, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEffect", "void set_dampingForce(float)", AS_METHODPR(ParticleEffect, SetDampingForce, (float), void), AS_CALL_THISCALL);
    // void ParticleEffect::SetEmitterSize(const Vector3& size) | File: ../Graphics/ParticleEffect.h
    engine->RegisterObjectMethod("ParticleEffect", "void SetEmitterSize(const Vector3&in)", AS_METHODPR(ParticleEffect, SetEmitterSize, (const Vector3&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEffect", "void set_emitterSize(const Vector3&in)", AS_METHODPR(ParticleEffect, SetEmitterSize, (const Vector3&), void), AS_CALL_THISCALL);
    // void ParticleEffect::SetEmitterType(EmitterType type) | File: ../Graphics/ParticleEffect.h
    engine->RegisterObjectMethod("ParticleEffect", "void SetEmitterType(EmitterType)", AS_METHODPR(ParticleEffect, SetEmitterType, (EmitterType), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEffect", "void set_emitterType(EmitterType)", AS_METHODPR(ParticleEffect, SetEmitterType, (EmitterType), void), AS_CALL_THISCALL);
    // void ParticleEffect::SetFaceCameraMode(FaceCameraMode mode) | File: ../Graphics/ParticleEffect.h
    engine->RegisterObjectMethod("ParticleEffect", "void SetFaceCameraMode(FaceCameraMode)", AS_METHODPR(ParticleEffect, SetFaceCameraMode, (FaceCameraMode), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEffect", "void set_faceCameraMode(FaceCameraMode)", AS_METHODPR(ParticleEffect, SetFaceCameraMode, (FaceCameraMode), void), AS_CALL_THISCALL);
    // void ParticleEffect::SetFixedScreenSize(bool enable) | File: ../Graphics/ParticleEffect.h
    engine->RegisterObjectMethod("ParticleEffect", "void SetFixedScreenSize(bool)", AS_METHODPR(ParticleEffect, SetFixedScreenSize, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEffect", "void set_fixedScreenSize(bool)", AS_METHODPR(ParticleEffect, SetFixedScreenSize, (bool), void), AS_CALL_THISCALL);
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ParticleEffect", "void SetGlobalVar(StringHash, const Variant&in)", AS_METHODPR(ParticleEffect, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEffect", "void set_globalVar(StringHash, const Variant&in)", AS_METHODPR(ParticleEffect, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    // void ParticleEffect::SetInactiveTime(float time) | File: ../Graphics/ParticleEffect.h
    engine->RegisterObjectMethod("ParticleEffect", "void SetInactiveTime(float)", AS_METHODPR(ParticleEffect, SetInactiveTime, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEffect", "void set_inactiveTime(float)", AS_METHODPR(ParticleEffect, SetInactiveTime, (float), void), AS_CALL_THISCALL);
    // void ParticleEffect::SetMaterial(Material* material) | File: ../Graphics/ParticleEffect.h
    engine->RegisterObjectMethod("ParticleEffect", "void SetMaterial(Material@+)", AS_METHODPR(ParticleEffect, SetMaterial, (Material*), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEffect", "void set_material(Material@+)", AS_METHODPR(ParticleEffect, SetMaterial, (Material*), void), AS_CALL_THISCALL);
    // void ParticleEffect::SetMaxDirection(const Vector3& direction) | File: ../Graphics/ParticleEffect.h
    engine->RegisterObjectMethod("ParticleEffect", "void SetMaxDirection(const Vector3&in)", AS_METHODPR(ParticleEffect, SetMaxDirection, (const Vector3&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEffect", "void set_maxDirection(const Vector3&in)", AS_METHODPR(ParticleEffect, SetMaxDirection, (const Vector3&), void), AS_CALL_THISCALL);
    // void ParticleEffect::SetMaxEmissionRate(float rate) | File: ../Graphics/ParticleEffect.h
    engine->RegisterObjectMethod("ParticleEffect", "void SetMaxEmissionRate(float)", AS_METHODPR(ParticleEffect, SetMaxEmissionRate, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEffect", "void set_maxEmissionRate(float)", AS_METHODPR(ParticleEffect, SetMaxEmissionRate, (float), void), AS_CALL_THISCALL);
    // void ParticleEffect::SetMaxParticleSize(const Vector2& size) | File: ../Graphics/ParticleEffect.h
    engine->RegisterObjectMethod("ParticleEffect", "void SetMaxParticleSize(const Vector2&in)", AS_METHODPR(ParticleEffect, SetMaxParticleSize, (const Vector2&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEffect", "void set_maxParticleSize(const Vector2&in)", AS_METHODPR(ParticleEffect, SetMaxParticleSize, (const Vector2&), void), AS_CALL_THISCALL);
    // void ParticleEffect::SetMaxRotation(float rotation) | File: ../Graphics/ParticleEffect.h
    engine->RegisterObjectMethod("ParticleEffect", "void SetMaxRotation(float)", AS_METHODPR(ParticleEffect, SetMaxRotation, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEffect", "void set_maxRotation(float)", AS_METHODPR(ParticleEffect, SetMaxRotation, (float), void), AS_CALL_THISCALL);
    // void ParticleEffect::SetMaxRotationSpeed(float speed) | File: ../Graphics/ParticleEffect.h
    engine->RegisterObjectMethod("ParticleEffect", "void SetMaxRotationSpeed(float)", AS_METHODPR(ParticleEffect, SetMaxRotationSpeed, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEffect", "void set_maxRotationSpeed(float)", AS_METHODPR(ParticleEffect, SetMaxRotationSpeed, (float), void), AS_CALL_THISCALL);
    // void ParticleEffect::SetMaxTimeToLive(float time) | File: ../Graphics/ParticleEffect.h
    engine->RegisterObjectMethod("ParticleEffect", "void SetMaxTimeToLive(float)", AS_METHODPR(ParticleEffect, SetMaxTimeToLive, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEffect", "void set_maxTimeToLive(float)", AS_METHODPR(ParticleEffect, SetMaxTimeToLive, (float), void), AS_CALL_THISCALL);
    // void ParticleEffect::SetMaxVelocity(float velocity) | File: ../Graphics/ParticleEffect.h
    engine->RegisterObjectMethod("ParticleEffect", "void SetMaxVelocity(float)", AS_METHODPR(ParticleEffect, SetMaxVelocity, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEffect", "void set_maxVelocity(float)", AS_METHODPR(ParticleEffect, SetMaxVelocity, (float), void), AS_CALL_THISCALL);
    // void Resource::SetMemoryUse(unsigned size) | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("ParticleEffect", "void SetMemoryUse(uint)", AS_METHODPR(ParticleEffect, SetMemoryUse, (unsigned), void), AS_CALL_THISCALL);
    // void ParticleEffect::SetMinDirection(const Vector3& direction) | File: ../Graphics/ParticleEffect.h
    engine->RegisterObjectMethod("ParticleEffect", "void SetMinDirection(const Vector3&in)", AS_METHODPR(ParticleEffect, SetMinDirection, (const Vector3&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEffect", "void set_minDirection(const Vector3&in)", AS_METHODPR(ParticleEffect, SetMinDirection, (const Vector3&), void), AS_CALL_THISCALL);
    // void ParticleEffect::SetMinEmissionRate(float rate) | File: ../Graphics/ParticleEffect.h
    engine->RegisterObjectMethod("ParticleEffect", "void SetMinEmissionRate(float)", AS_METHODPR(ParticleEffect, SetMinEmissionRate, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEffect", "void set_minEmissionRate(float)", AS_METHODPR(ParticleEffect, SetMinEmissionRate, (float), void), AS_CALL_THISCALL);
    // void ParticleEffect::SetMinParticleSize(const Vector2& size) | File: ../Graphics/ParticleEffect.h
    engine->RegisterObjectMethod("ParticleEffect", "void SetMinParticleSize(const Vector2&in)", AS_METHODPR(ParticleEffect, SetMinParticleSize, (const Vector2&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEffect", "void set_minParticleSize(const Vector2&in)", AS_METHODPR(ParticleEffect, SetMinParticleSize, (const Vector2&), void), AS_CALL_THISCALL);
    // void ParticleEffect::SetMinRotation(float rotation) | File: ../Graphics/ParticleEffect.h
    engine->RegisterObjectMethod("ParticleEffect", "void SetMinRotation(float)", AS_METHODPR(ParticleEffect, SetMinRotation, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEffect", "void set_minRotation(float)", AS_METHODPR(ParticleEffect, SetMinRotation, (float), void), AS_CALL_THISCALL);
    // void ParticleEffect::SetMinRotationSpeed(float speed) | File: ../Graphics/ParticleEffect.h
    engine->RegisterObjectMethod("ParticleEffect", "void SetMinRotationSpeed(float)", AS_METHODPR(ParticleEffect, SetMinRotationSpeed, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEffect", "void set_minRotationSpeed(float)", AS_METHODPR(ParticleEffect, SetMinRotationSpeed, (float), void), AS_CALL_THISCALL);
    // void ParticleEffect::SetMinTimeToLive(float time) | File: ../Graphics/ParticleEffect.h
    engine->RegisterObjectMethod("ParticleEffect", "void SetMinTimeToLive(float)", AS_METHODPR(ParticleEffect, SetMinTimeToLive, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEffect", "void set_minTimeToLive(float)", AS_METHODPR(ParticleEffect, SetMinTimeToLive, (float), void), AS_CALL_THISCALL);
    // void ParticleEffect::SetMinVelocity(float velocity) | File: ../Graphics/ParticleEffect.h
    engine->RegisterObjectMethod("ParticleEffect", "void SetMinVelocity(float)", AS_METHODPR(ParticleEffect, SetMinVelocity, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEffect", "void set_minVelocity(float)", AS_METHODPR(ParticleEffect, SetMinVelocity, (float), void), AS_CALL_THISCALL);
    // void Resource::SetName(const String& name) | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("ParticleEffect", "void SetName(const String&in)", AS_METHODPR(ParticleEffect, SetName, (const String&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEffect", "void set_name(const String&in)", AS_METHODPR(ParticleEffect, SetName, (const String&), void), AS_CALL_THISCALL);
    // void ParticleEffect::SetNumColorFrames(unsigned number) | File: ../Graphics/ParticleEffect.h
    engine->RegisterObjectMethod("ParticleEffect", "void SetNumColorFrames(uint)", AS_METHODPR(ParticleEffect, SetNumColorFrames, (unsigned), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEffect", "void set_numColorFrames(uint)", AS_METHODPR(ParticleEffect, SetNumColorFrames, (unsigned), void), AS_CALL_THISCALL);
    // void ParticleEffect::SetNumParticles(unsigned num) | File: ../Graphics/ParticleEffect.h
    engine->RegisterObjectMethod("ParticleEffect", "void SetNumParticles(uint)", AS_METHODPR(ParticleEffect, SetNumParticles, (unsigned), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEffect", "void set_numParticles(uint)", AS_METHODPR(ParticleEffect, SetNumParticles, (unsigned), void), AS_CALL_THISCALL);
    // void ParticleEffect::SetNumTextureFrames(unsigned number) | File: ../Graphics/ParticleEffect.h
    engine->RegisterObjectMethod("ParticleEffect", "void SetNumTextureFrames(uint)", AS_METHODPR(ParticleEffect, SetNumTextureFrames, (unsigned), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEffect", "void set_numTextureFrames(uint)", AS_METHODPR(ParticleEffect, SetNumTextureFrames, (unsigned), void), AS_CALL_THISCALL);
    // void ParticleEffect::SetRelative(bool enable) | File: ../Graphics/ParticleEffect.h
    engine->RegisterObjectMethod("ParticleEffect", "void SetRelative(bool)", AS_METHODPR(ParticleEffect, SetRelative, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEffect", "void set_relative(bool)", AS_METHODPR(ParticleEffect, SetRelative, (bool), void), AS_CALL_THISCALL);
    // void ParticleEffect::SetScaled(bool enable) | File: ../Graphics/ParticleEffect.h
    engine->RegisterObjectMethod("ParticleEffect", "void SetScaled(bool)", AS_METHODPR(ParticleEffect, SetScaled, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEffect", "void set_scaled(bool)", AS_METHODPR(ParticleEffect, SetScaled, (bool), void), AS_CALL_THISCALL);
    // void ParticleEffect::SetSizeAdd(float sizeAdd) | File: ../Graphics/ParticleEffect.h
    engine->RegisterObjectMethod("ParticleEffect", "void SetSizeAdd(float)", AS_METHODPR(ParticleEffect, SetSizeAdd, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEffect", "void set_sizeAdd(float)", AS_METHODPR(ParticleEffect, SetSizeAdd, (float), void), AS_CALL_THISCALL);
    // void ParticleEffect::SetSizeMul(float sizeMul) | File: ../Graphics/ParticleEffect.h
    engine->RegisterObjectMethod("ParticleEffect", "void SetSizeMul(float)", AS_METHODPR(ParticleEffect, SetSizeMul, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEffect", "void set_sizeMul(float)", AS_METHODPR(ParticleEffect, SetSizeMul, (float), void), AS_CALL_THISCALL);
    // void ParticleEffect::SetSorted(bool enable) | File: ../Graphics/ParticleEffect.h
    engine->RegisterObjectMethod("ParticleEffect", "void SetSorted(bool)", AS_METHODPR(ParticleEffect, SetSorted, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEffect", "void set_sorted(bool)", AS_METHODPR(ParticleEffect, SetSorted, (bool), void), AS_CALL_THISCALL);
    // void ParticleEffect::SetTextureFrame(unsigned index, const TextureFrame& textureFrame) | File: ../Graphics/ParticleEffect.h
    engine->RegisterObjectMethod("ParticleEffect", "void SetTextureFrame(uint, const TextureFrame&in)", AS_METHODPR(ParticleEffect, SetTextureFrame, (unsigned, const TextureFrame&), void), AS_CALL_THISCALL);
    // void ParticleEffect::SetTextureFrames(const Vector<TextureFrame>& textureFrames) | File: ../Graphics/ParticleEffect.h
    // Error: type "const Vector<TextureFrame>&" can not automatically bind
    // void ParticleEffect::SetUpdateInvisible(bool enable) | File: ../Graphics/ParticleEffect.h
    engine->RegisterObjectMethod("ParticleEffect", "void SetUpdateInvisible(bool)", AS_METHODPR(ParticleEffect, SetUpdateInvisible, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEffect", "void set_updateInvisible(bool)", AS_METHODPR(ParticleEffect, SetUpdateInvisible, (bool), void), AS_CALL_THISCALL);
    // void ParticleEffect::SortColorFrames() | File: ../Graphics/ParticleEffect.h
    engine->RegisterObjectMethod("ParticleEffect", "void SortColorFrames()", AS_METHODPR(ParticleEffect, SortColorFrames, (), void), AS_CALL_THISCALL);
    // void ParticleEffect::SortTextureFrames() | File: ../Graphics/ParticleEffect.h
    engine->RegisterObjectMethod("ParticleEffect", "void SortTextureFrames()", AS_METHODPR(ParticleEffect, SortTextureFrames, (), void), AS_CALL_THISCALL);
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod("ParticleEffect", "void UnsubscribeFromAllEvents()", AS_METHODPR(ParticleEffect, UnsubscribeFromAllEvents, (), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ParticleEffect", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", AS_FUNCTION_OBJFIRST(ParticleEffect_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), AS_CALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ParticleEffect", "void UnsubscribeFromEvent(StringHash)", AS_METHODPR(ParticleEffect, UnsubscribeFromEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ParticleEffect", "void UnsubscribeFromEvent(Object@+, StringHash)", AS_METHODPR(ParticleEffect, UnsubscribeFromEvent, (Object*, StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ParticleEffect", "void UnsubscribeFromEvents(Object@+)", AS_METHODPR(ParticleEffect, UnsubscribeFromEvents, (Object*), void), AS_CALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("ParticleEffect", "int WeakRefs() const", AS_METHODPR(ParticleEffect, WeakRefs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEffect", "int get_weakRefs() const", AS_METHODPR(ParticleEffect, WeakRefs, () const, int), AS_CALL_THISCALL);
#ifdef REGISTER_MANUAL_PART_Resource
    REGISTER_MANUAL_PART_Resource(ParticleEffect, "ParticleEffect")
#endif
#ifdef REGISTER_MANUAL_PART_Object
    REGISTER_MANUAL_PART_Object(ParticleEffect, "ParticleEffect")
#endif
#ifdef REGISTER_MANUAL_PART_RefCounted
    REGISTER_MANUAL_PART_RefCounted(ParticleEffect, "ParticleEffect")
#endif
#ifdef REGISTER_MANUAL_PART_ParticleEffect
    REGISTER_MANUAL_PART_ParticleEffect(ParticleEffect, "ParticleEffect")
#endif
    RegisterSubclass<Resource, ParticleEffect>(engine, "Resource", "ParticleEffect");
    RegisterSubclass<Object, ParticleEffect>(engine, "Object", "ParticleEffect");
    RegisterSubclass<RefCounted, ParticleEffect>(engine, "RefCounted", "ParticleEffect");

#ifdef URHO3D_URHO2D
    // void RefCounted::AddRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("ParticleEffect2D", asBEHAVE_ADDREF, "void f()", AS_METHODPR(ParticleEffect2D, AddRef, (), void), AS_CALL_THISCALL);
    // bool ParticleEffect2D::BeginLoad(Deserializer& source) override | File: ../Urho2D/ParticleEffect2D.h
    engine->RegisterObjectMethod("ParticleEffect2D", "bool BeginLoad(Deserializer&)", AS_METHODPR(ParticleEffect2D, BeginLoad, (Deserializer&), bool), AS_CALL_THISCALL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // SharedPtr<ParticleEffect2D> ParticleEffect2D::Clone(const String& cloneName=String::EMPTY) const | File: ../Urho2D/ParticleEffect2D.h
    engine->RegisterObjectMethod("ParticleEffect2D", "ParticleEffect2D@+ Clone(const String&in = String::EMPTY) const", AS_FUNCTION_OBJFIRST(ParticleEffect2D_Clone_String), AS_CALL_CDECL_OBJFIRST);
    // bool ParticleEffect2D::EndLoad() override | File: ../Urho2D/ParticleEffect2D.h
    engine->RegisterObjectMethod("ParticleEffect2D", "bool EndLoad()", AS_METHODPR(ParticleEffect2D, EndLoad, (), bool), AS_CALL_THISCALL);
    // float ParticleEffect2D::GetAngle() const | File: ../Urho2D/ParticleEffect2D.h
    engine->RegisterObjectMethod("ParticleEffect2D", "float GetAngle() const", AS_METHODPR(ParticleEffect2D, GetAngle, () const, float), AS_CALL_THISCALL);
    // float ParticleEffect2D::GetAngleVariance() const | File: ../Urho2D/ParticleEffect2D.h
    engine->RegisterObjectMethod("ParticleEffect2D", "float GetAngleVariance() const", AS_METHODPR(ParticleEffect2D, GetAngleVariance, () const, float), AS_CALL_THISCALL);
    // AsyncLoadState Resource::GetAsyncLoadState() const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("ParticleEffect2D", "AsyncLoadState GetAsyncLoadState() const", AS_METHODPR(ParticleEffect2D, GetAsyncLoadState, () const, AsyncLoadState), AS_CALL_THISCALL);
    // BlendMode ParticleEffect2D::GetBlendMode() const | File: ../Urho2D/ParticleEffect2D.h
    engine->RegisterObjectMethod("ParticleEffect2D", "BlendMode GetBlendMode() const", AS_METHODPR(ParticleEffect2D, GetBlendMode, () const, BlendMode), AS_CALL_THISCALL);
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ParticleEffect2D", "bool GetBlockEvents() const", AS_METHODPR(ParticleEffect2D, GetBlockEvents, () const, bool), AS_CALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ParticleEffect2D", "const String& GetCategory() const", AS_METHODPR(ParticleEffect2D, GetCategory, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEffect2D", "const String& get_category() const", AS_METHODPR(ParticleEffect2D, GetCategory, () const, const String&), AS_CALL_THISCALL);
    // Context* Object::GetContext() const | File: ../Core/Object.h
    // Error: type "Context*" can used only as function parameter
    // float ParticleEffect2D::GetDuration() const | File: ../Urho2D/ParticleEffect2D.h
    engine->RegisterObjectMethod("ParticleEffect2D", "float GetDuration() const", AS_METHODPR(ParticleEffect2D, GetDuration, () const, float), AS_CALL_THISCALL);
    // EmitterType2D ParticleEffect2D::GetEmitterType() const | File: ../Urho2D/ParticleEffect2D.h
    engine->RegisterObjectMethod("ParticleEffect2D", "EmitterType2D GetEmitterType() const", AS_METHODPR(ParticleEffect2D, GetEmitterType, () const, EmitterType2D), AS_CALL_THISCALL);
    // VariantMap& Object::GetEventDataMap() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ParticleEffect2D", "VariantMap& GetEventDataMap() const", AS_METHODPR(ParticleEffect2D, GetEventDataMap, () const, VariantMap&), AS_CALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ParticleEffect2D", "Object@+ GetEventSender() const", AS_METHODPR(ParticleEffect2D, GetEventSender, () const, Object*), AS_CALL_THISCALL);
    // const Color& ParticleEffect2D::GetFinishColor() const | File: ../Urho2D/ParticleEffect2D.h
    engine->RegisterObjectMethod("ParticleEffect2D", "const Color& GetFinishColor() const", AS_METHODPR(ParticleEffect2D, GetFinishColor, () const, const Color&), AS_CALL_THISCALL);
    // const Color& ParticleEffect2D::GetFinishColorVariance() const | File: ../Urho2D/ParticleEffect2D.h
    engine->RegisterObjectMethod("ParticleEffect2D", "const Color& GetFinishColorVariance() const", AS_METHODPR(ParticleEffect2D, GetFinishColorVariance, () const, const Color&), AS_CALL_THISCALL);
    // float ParticleEffect2D::GetFinishParticleSize() const | File: ../Urho2D/ParticleEffect2D.h
    engine->RegisterObjectMethod("ParticleEffect2D", "float GetFinishParticleSize() const", AS_METHODPR(ParticleEffect2D, GetFinishParticleSize, () const, float), AS_CALL_THISCALL);
    // float ParticleEffect2D::GetFinishParticleSizeVariance() const | File: ../Urho2D/ParticleEffect2D.h
    engine->RegisterObjectMethod("ParticleEffect2D", "float GetFinishParticleSizeVariance() const", AS_METHODPR(ParticleEffect2D, GetFinishParticleSizeVariance, () const, float), AS_CALL_THISCALL);
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ParticleEffect2D", "const Variant& GetGlobalVar(StringHash) const", AS_METHODPR(ParticleEffect2D, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEffect2D", "const Variant& get_globalVar(StringHash) const", AS_METHODPR(ParticleEffect2D, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ParticleEffect2D", "const VariantMap& GetGlobalVars() const", AS_METHODPR(ParticleEffect2D, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEffect2D", "const VariantMap& get_globalVars() const", AS_METHODPR(ParticleEffect2D, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    // const Vector2& ParticleEffect2D::GetGravity() const | File: ../Urho2D/ParticleEffect2D.h
    engine->RegisterObjectMethod("ParticleEffect2D", "const Vector2& GetGravity() const", AS_METHODPR(ParticleEffect2D, GetGravity, () const, const Vector2&), AS_CALL_THISCALL);
    // int ParticleEffect2D::GetMaxParticles() const | File: ../Urho2D/ParticleEffect2D.h
    engine->RegisterObjectMethod("ParticleEffect2D", "int GetMaxParticles() const", AS_METHODPR(ParticleEffect2D, GetMaxParticles, () const, int), AS_CALL_THISCALL);
    // float ParticleEffect2D::GetMaxRadius() const | File: ../Urho2D/ParticleEffect2D.h
    engine->RegisterObjectMethod("ParticleEffect2D", "float GetMaxRadius() const", AS_METHODPR(ParticleEffect2D, GetMaxRadius, () const, float), AS_CALL_THISCALL);
    // float ParticleEffect2D::GetMaxRadiusVariance() const | File: ../Urho2D/ParticleEffect2D.h
    engine->RegisterObjectMethod("ParticleEffect2D", "float GetMaxRadiusVariance() const", AS_METHODPR(ParticleEffect2D, GetMaxRadiusVariance, () const, float), AS_CALL_THISCALL);
    // unsigned Resource::GetMemoryUse() const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("ParticleEffect2D", "uint GetMemoryUse() const", AS_METHODPR(ParticleEffect2D, GetMemoryUse, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEffect2D", "uint get_memoryUse() const", AS_METHODPR(ParticleEffect2D, GetMemoryUse, () const, unsigned), AS_CALL_THISCALL);
    // float ParticleEffect2D::GetMinRadius() const | File: ../Urho2D/ParticleEffect2D.h
    engine->RegisterObjectMethod("ParticleEffect2D", "float GetMinRadius() const", AS_METHODPR(ParticleEffect2D, GetMinRadius, () const, float), AS_CALL_THISCALL);
    // float ParticleEffect2D::GetMinRadiusVariance() const | File: ../Urho2D/ParticleEffect2D.h
    engine->RegisterObjectMethod("ParticleEffect2D", "float GetMinRadiusVariance() const", AS_METHODPR(ParticleEffect2D, GetMinRadiusVariance, () const, float), AS_CALL_THISCALL);
    // const String& Resource::GetName() const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("ParticleEffect2D", "const String& GetName() const", AS_METHODPR(ParticleEffect2D, GetName, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEffect2D", "const String& get_name() const", AS_METHODPR(ParticleEffect2D, GetName, () const, const String&), AS_CALL_THISCALL);
    // StringHash Resource::GetNameHash() const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("ParticleEffect2D", "StringHash GetNameHash() const", AS_METHODPR(ParticleEffect2D, GetNameHash, () const, StringHash), AS_CALL_THISCALL);
    // float ParticleEffect2D::GetParticleLifeSpan() const | File: ../Urho2D/ParticleEffect2D.h
    engine->RegisterObjectMethod("ParticleEffect2D", "float GetParticleLifeSpan() const", AS_METHODPR(ParticleEffect2D, GetParticleLifeSpan, () const, float), AS_CALL_THISCALL);
    // float ParticleEffect2D::GetParticleLifespanVariance() const | File: ../Urho2D/ParticleEffect2D.h
    engine->RegisterObjectMethod("ParticleEffect2D", "float GetParticleLifespanVariance() const", AS_METHODPR(ParticleEffect2D, GetParticleLifespanVariance, () const, float), AS_CALL_THISCALL);
    // float ParticleEffect2D::GetRadialAcceleration() const | File: ../Urho2D/ParticleEffect2D.h
    engine->RegisterObjectMethod("ParticleEffect2D", "float GetRadialAcceleration() const", AS_METHODPR(ParticleEffect2D, GetRadialAcceleration, () const, float), AS_CALL_THISCALL);
    // float ParticleEffect2D::GetRadialAccelVariance() const | File: ../Urho2D/ParticleEffect2D.h
    engine->RegisterObjectMethod("ParticleEffect2D", "float GetRadialAccelVariance() const", AS_METHODPR(ParticleEffect2D, GetRadialAccelVariance, () const, float), AS_CALL_THISCALL);
    // float ParticleEffect2D::GetRotatePerSecond() const | File: ../Urho2D/ParticleEffect2D.h
    engine->RegisterObjectMethod("ParticleEffect2D", "float GetRotatePerSecond() const", AS_METHODPR(ParticleEffect2D, GetRotatePerSecond, () const, float), AS_CALL_THISCALL);
    // float ParticleEffect2D::GetRotatePerSecondVariance() const | File: ../Urho2D/ParticleEffect2D.h
    engine->RegisterObjectMethod("ParticleEffect2D", "float GetRotatePerSecondVariance() const", AS_METHODPR(ParticleEffect2D, GetRotatePerSecondVariance, () const, float), AS_CALL_THISCALL);
    // float ParticleEffect2D::GetRotationEnd() const | File: ../Urho2D/ParticleEffect2D.h
    engine->RegisterObjectMethod("ParticleEffect2D", "float GetRotationEnd() const", AS_METHODPR(ParticleEffect2D, GetRotationEnd, () const, float), AS_CALL_THISCALL);
    // float ParticleEffect2D::GetRotationEndVariance() const | File: ../Urho2D/ParticleEffect2D.h
    engine->RegisterObjectMethod("ParticleEffect2D", "float GetRotationEndVariance() const", AS_METHODPR(ParticleEffect2D, GetRotationEndVariance, () const, float), AS_CALL_THISCALL);
    // float ParticleEffect2D::GetRotationStart() const | File: ../Urho2D/ParticleEffect2D.h
    engine->RegisterObjectMethod("ParticleEffect2D", "float GetRotationStart() const", AS_METHODPR(ParticleEffect2D, GetRotationStart, () const, float), AS_CALL_THISCALL);
    // float ParticleEffect2D::GetRotationStartVariance() const | File: ../Urho2D/ParticleEffect2D.h
    engine->RegisterObjectMethod("ParticleEffect2D", "float GetRotationStartVariance() const", AS_METHODPR(ParticleEffect2D, GetRotationStartVariance, () const, float), AS_CALL_THISCALL);
    // const Vector2& ParticleEffect2D::GetSourcePositionVariance() const | File: ../Urho2D/ParticleEffect2D.h
    engine->RegisterObjectMethod("ParticleEffect2D", "const Vector2& GetSourcePositionVariance() const", AS_METHODPR(ParticleEffect2D, GetSourcePositionVariance, () const, const Vector2&), AS_CALL_THISCALL);
    // float ParticleEffect2D::GetSpeed() const | File: ../Urho2D/ParticleEffect2D.h
    engine->RegisterObjectMethod("ParticleEffect2D", "float GetSpeed() const", AS_METHODPR(ParticleEffect2D, GetSpeed, () const, float), AS_CALL_THISCALL);
    // float ParticleEffect2D::GetSpeedVariance() const | File: ../Urho2D/ParticleEffect2D.h
    engine->RegisterObjectMethod("ParticleEffect2D", "float GetSpeedVariance() const", AS_METHODPR(ParticleEffect2D, GetSpeedVariance, () const, float), AS_CALL_THISCALL);
    // Sprite2D* ParticleEffect2D::GetSprite() const | File: ../Urho2D/ParticleEffect2D.h
    engine->RegisterObjectMethod("ParticleEffect2D", "Sprite2D@+ GetSprite() const", AS_METHODPR(ParticleEffect2D, GetSprite, () const, Sprite2D*), AS_CALL_THISCALL);
    // const Color& ParticleEffect2D::GetStartColor() const | File: ../Urho2D/ParticleEffect2D.h
    engine->RegisterObjectMethod("ParticleEffect2D", "const Color& GetStartColor() const", AS_METHODPR(ParticleEffect2D, GetStartColor, () const, const Color&), AS_CALL_THISCALL);
    // const Color& ParticleEffect2D::GetStartColorVariance() const | File: ../Urho2D/ParticleEffect2D.h
    engine->RegisterObjectMethod("ParticleEffect2D", "const Color& GetStartColorVariance() const", AS_METHODPR(ParticleEffect2D, GetStartColorVariance, () const, const Color&), AS_CALL_THISCALL);
    // float ParticleEffect2D::GetStartParticleSize() const | File: ../Urho2D/ParticleEffect2D.h
    engine->RegisterObjectMethod("ParticleEffect2D", "float GetStartParticleSize() const", AS_METHODPR(ParticleEffect2D, GetStartParticleSize, () const, float), AS_CALL_THISCALL);
    // float ParticleEffect2D::GetStartParticleSizeVariance() const | File: ../Urho2D/ParticleEffect2D.h
    engine->RegisterObjectMethod("ParticleEffect2D", "float GetStartParticleSizeVariance() const", AS_METHODPR(ParticleEffect2D, GetStartParticleSizeVariance, () const, float), AS_CALL_THISCALL);
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ParticleEffect2D", "Object@+ GetSubsystem(StringHash) const", AS_METHODPR(ParticleEffect2D, GetSubsystem, (StringHash) const, Object*), AS_CALL_THISCALL);
    // template<class T> T* Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // float ParticleEffect2D::GetTangentialAcceleration() const | File: ../Urho2D/ParticleEffect2D.h
    engine->RegisterObjectMethod("ParticleEffect2D", "float GetTangentialAcceleration() const", AS_METHODPR(ParticleEffect2D, GetTangentialAcceleration, () const, float), AS_CALL_THISCALL);
    // float ParticleEffect2D::GetTangentialAccelVariance() const | File: ../Urho2D/ParticleEffect2D.h
    engine->RegisterObjectMethod("ParticleEffect2D", "float GetTangentialAccelVariance() const", AS_METHODPR(ParticleEffect2D, GetTangentialAccelVariance, () const, float), AS_CALL_THISCALL);
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("ParticleEffect2D", "StringHash GetType() const", AS_METHODPR(ParticleEffect2D, GetType, () const, StringHash), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEffect2D", "StringHash get_type() const", AS_METHODPR(ParticleEffect2D, GetType, () const, StringHash), AS_CALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("ParticleEffect2D", "const String& GetTypeName() const", AS_METHODPR(ParticleEffect2D, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEffect2D", "const String& get_typeName() const", AS_METHODPR(ParticleEffect2D, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    // unsigned Resource::GetUseTimer() | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("ParticleEffect2D", "uint GetUseTimer()", AS_METHODPR(ParticleEffect2D, GetUseTimer, (), unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEffect2D", "uint get_useTimer()", AS_METHODPR(ParticleEffect2D, GetUseTimer, (), unsigned), AS_CALL_THISCALL);
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ParticleEffect2D", "bool HasEventHandlers() const", AS_METHODPR(ParticleEffect2D, HasEventHandlers, () const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ParticleEffect2D", "bool HasSubscribedToEvent(StringHash) const", AS_METHODPR(ParticleEffect2D, HasSubscribedToEvent, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ParticleEffect2D", "bool HasSubscribedToEvent(Object@+, StringHash) const", AS_METHODPR(ParticleEffect2D, HasSubscribedToEvent, (Object*, StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ParticleEffect2D", "bool IsInstanceOf(StringHash) const", AS_METHODPR(ParticleEffect2D, IsInstanceOf, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // bool Resource::Load(Deserializer& source) | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("ParticleEffect2D", "bool Load(Deserializer&)", AS_METHODPR(ParticleEffect2D, Load, (Deserializer&), bool), AS_CALL_THISCALL);
    // bool Resource::LoadFile(const String& fileName) | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("ParticleEffect2D", "bool LoadFile(const String&in)", AS_METHODPR(ParticleEffect2D, LoadFile, (const String&), bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEffect2D", "bool Load(const String&in)", AS_METHODPR(ParticleEffect2D, LoadFile, (const String&), bool), AS_CALL_THISCALL);
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ParticleEffect2D", "void OnEvent(Object@+, StringHash, VariantMap&)", AS_METHODPR(ParticleEffect2D, OnEvent, (Object*, StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // explicit ParticleEffect2D::ParticleEffect2D(Context* context) | File: ../Urho2D/ParticleEffect2D.h
    engine->RegisterObjectBehaviour("ParticleEffect2D", asBEHAVE_FACTORY, "ParticleEffect2D@+ f()", AS_FUNCTION(ParticleEffect2D_ParticleEffect2D_Context), AS_CALL_CDECL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("ParticleEffect2D", "int Refs() const", AS_METHODPR(ParticleEffect2D, Refs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEffect2D", "int get_refs() const", AS_METHODPR(ParticleEffect2D, Refs, () const, int), AS_CALL_THISCALL);
    // static void ParticleEffect2D::RegisterObject(Context* context) | File: ../Urho2D/ParticleEffect2D.h
    // Not registered because have @nobind mark
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("ParticleEffect2D", asBEHAVE_RELEASE, "void f()", AS_METHODPR(ParticleEffect2D, ReleaseRef, (), void), AS_CALL_THISCALL);
    // void Resource::ResetUseTimer() | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("ParticleEffect2D", "void ResetUseTimer()", AS_METHODPR(ParticleEffect2D, ResetUseTimer, (), void), AS_CALL_THISCALL);
    // bool ParticleEffect2D::Save(Serializer& dest) const override | File: ../Urho2D/ParticleEffect2D.h
    engine->RegisterObjectMethod("ParticleEffect2D", "bool Save(Serializer&) const", AS_METHODPR(ParticleEffect2D, Save, (Serializer&) const, bool), AS_CALL_THISCALL);
    // virtual bool Resource::SaveFile(const String& fileName) const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("ParticleEffect2D", "bool SaveFile(const String&in) const", AS_METHODPR(ParticleEffect2D, SaveFile, (const String&) const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEffect2D", "bool Save(const String&in) const", AS_METHODPR(ParticleEffect2D, SaveFile, (const String&) const, bool), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ParticleEffect2D", "void SendEvent(StringHash)", AS_METHODPR(ParticleEffect2D, SendEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ParticleEffect2D", "void SendEvent(StringHash, VariantMap&)", AS_METHODPR(ParticleEffect2D, SendEvent, (StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void ParticleEffect2D::SetAngle(float angle) | File: ../Urho2D/ParticleEffect2D.h
    engine->RegisterObjectMethod("ParticleEffect2D", "void SetAngle(float)", AS_METHODPR(ParticleEffect2D, SetAngle, (float), void), AS_CALL_THISCALL);
    // void ParticleEffect2D::SetAngleVariance(float angleVariance) | File: ../Urho2D/ParticleEffect2D.h
    engine->RegisterObjectMethod("ParticleEffect2D", "void SetAngleVariance(float)", AS_METHODPR(ParticleEffect2D, SetAngleVariance, (float), void), AS_CALL_THISCALL);
    // void Resource::SetAsyncLoadState(AsyncLoadState newState) | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("ParticleEffect2D", "void SetAsyncLoadState(AsyncLoadState)", AS_METHODPR(ParticleEffect2D, SetAsyncLoadState, (AsyncLoadState), void), AS_CALL_THISCALL);
    // void ParticleEffect2D::SetBlendMode(BlendMode blendMode) | File: ../Urho2D/ParticleEffect2D.h
    engine->RegisterObjectMethod("ParticleEffect2D", "void SetBlendMode(BlendMode)", AS_METHODPR(ParticleEffect2D, SetBlendMode, (BlendMode), void), AS_CALL_THISCALL);
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ParticleEffect2D", "void SetBlockEvents(bool)", AS_METHODPR(ParticleEffect2D, SetBlockEvents, (bool), void), AS_CALL_THISCALL);
    // void ParticleEffect2D::SetDuration(float duration) | File: ../Urho2D/ParticleEffect2D.h
    engine->RegisterObjectMethod("ParticleEffect2D", "void SetDuration(float)", AS_METHODPR(ParticleEffect2D, SetDuration, (float), void), AS_CALL_THISCALL);
    // void ParticleEffect2D::SetEmitterType(EmitterType2D emitterType) | File: ../Urho2D/ParticleEffect2D.h
    engine->RegisterObjectMethod("ParticleEffect2D", "void SetEmitterType(EmitterType2D)", AS_METHODPR(ParticleEffect2D, SetEmitterType, (EmitterType2D), void), AS_CALL_THISCALL);
    // void ParticleEffect2D::SetFinishColor(const Color& finishColor) | File: ../Urho2D/ParticleEffect2D.h
    engine->RegisterObjectMethod("ParticleEffect2D", "void SetFinishColor(const Color&in)", AS_METHODPR(ParticleEffect2D, SetFinishColor, (const Color&), void), AS_CALL_THISCALL);
    // void ParticleEffect2D::SetFinishColorVariance(const Color& finishColorVariance) | File: ../Urho2D/ParticleEffect2D.h
    engine->RegisterObjectMethod("ParticleEffect2D", "void SetFinishColorVariance(const Color&in)", AS_METHODPR(ParticleEffect2D, SetFinishColorVariance, (const Color&), void), AS_CALL_THISCALL);
    // void ParticleEffect2D::SetFinishParticleSize(float finishParticleSize) | File: ../Urho2D/ParticleEffect2D.h
    engine->RegisterObjectMethod("ParticleEffect2D", "void SetFinishParticleSize(float)", AS_METHODPR(ParticleEffect2D, SetFinishParticleSize, (float), void), AS_CALL_THISCALL);
    // void ParticleEffect2D::SetFinishParticleSizeVariance(float finishParticleSizeVariance) | File: ../Urho2D/ParticleEffect2D.h
    engine->RegisterObjectMethod("ParticleEffect2D", "void SetFinishParticleSizeVariance(float)", AS_METHODPR(ParticleEffect2D, SetFinishParticleSizeVariance, (float), void), AS_CALL_THISCALL);
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ParticleEffect2D", "void SetGlobalVar(StringHash, const Variant&in)", AS_METHODPR(ParticleEffect2D, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEffect2D", "void set_globalVar(StringHash, const Variant&in)", AS_METHODPR(ParticleEffect2D, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    // void ParticleEffect2D::SetGravity(const Vector2& gravity) | File: ../Urho2D/ParticleEffect2D.h
    engine->RegisterObjectMethod("ParticleEffect2D", "void SetGravity(const Vector2&in)", AS_METHODPR(ParticleEffect2D, SetGravity, (const Vector2&), void), AS_CALL_THISCALL);
    // void ParticleEffect2D::SetMaxParticles(int maxParticles) | File: ../Urho2D/ParticleEffect2D.h
    engine->RegisterObjectMethod("ParticleEffect2D", "void SetMaxParticles(int)", AS_METHODPR(ParticleEffect2D, SetMaxParticles, (int), void), AS_CALL_THISCALL);
    // void ParticleEffect2D::SetMaxRadius(float maxRadius) | File: ../Urho2D/ParticleEffect2D.h
    engine->RegisterObjectMethod("ParticleEffect2D", "void SetMaxRadius(float)", AS_METHODPR(ParticleEffect2D, SetMaxRadius, (float), void), AS_CALL_THISCALL);
    // void ParticleEffect2D::SetMaxRadiusVariance(float maxRadiusVariance) | File: ../Urho2D/ParticleEffect2D.h
    engine->RegisterObjectMethod("ParticleEffect2D", "void SetMaxRadiusVariance(float)", AS_METHODPR(ParticleEffect2D, SetMaxRadiusVariance, (float), void), AS_CALL_THISCALL);
    // void Resource::SetMemoryUse(unsigned size) | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("ParticleEffect2D", "void SetMemoryUse(uint)", AS_METHODPR(ParticleEffect2D, SetMemoryUse, (unsigned), void), AS_CALL_THISCALL);
    // void ParticleEffect2D::SetMinRadius(float minRadius) | File: ../Urho2D/ParticleEffect2D.h
    engine->RegisterObjectMethod("ParticleEffect2D", "void SetMinRadius(float)", AS_METHODPR(ParticleEffect2D, SetMinRadius, (float), void), AS_CALL_THISCALL);
    // void ParticleEffect2D::SetMinRadiusVariance(float minRadiusVariance) | File: ../Urho2D/ParticleEffect2D.h
    engine->RegisterObjectMethod("ParticleEffect2D", "void SetMinRadiusVariance(float)", AS_METHODPR(ParticleEffect2D, SetMinRadiusVariance, (float), void), AS_CALL_THISCALL);
    // void Resource::SetName(const String& name) | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("ParticleEffect2D", "void SetName(const String&in)", AS_METHODPR(ParticleEffect2D, SetName, (const String&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEffect2D", "void set_name(const String&in)", AS_METHODPR(ParticleEffect2D, SetName, (const String&), void), AS_CALL_THISCALL);
    // void ParticleEffect2D::SetParticleLifeSpan(float particleLifeSpan) | File: ../Urho2D/ParticleEffect2D.h
    engine->RegisterObjectMethod("ParticleEffect2D", "void SetParticleLifeSpan(float)", AS_METHODPR(ParticleEffect2D, SetParticleLifeSpan, (float), void), AS_CALL_THISCALL);
    // void ParticleEffect2D::SetParticleLifespanVariance(float particleLifespanVariance) | File: ../Urho2D/ParticleEffect2D.h
    engine->RegisterObjectMethod("ParticleEffect2D", "void SetParticleLifespanVariance(float)", AS_METHODPR(ParticleEffect2D, SetParticleLifespanVariance, (float), void), AS_CALL_THISCALL);
    // void ParticleEffect2D::SetRadialAcceleration(float radialAcceleration) | File: ../Urho2D/ParticleEffect2D.h
    engine->RegisterObjectMethod("ParticleEffect2D", "void SetRadialAcceleration(float)", AS_METHODPR(ParticleEffect2D, SetRadialAcceleration, (float), void), AS_CALL_THISCALL);
    // void ParticleEffect2D::SetRadialAccelVariance(float radialAccelVariance) | File: ../Urho2D/ParticleEffect2D.h
    engine->RegisterObjectMethod("ParticleEffect2D", "void SetRadialAccelVariance(float)", AS_METHODPR(ParticleEffect2D, SetRadialAccelVariance, (float), void), AS_CALL_THISCALL);
    // void ParticleEffect2D::SetRotatePerSecond(float rotatePerSecond) | File: ../Urho2D/ParticleEffect2D.h
    engine->RegisterObjectMethod("ParticleEffect2D", "void SetRotatePerSecond(float)", AS_METHODPR(ParticleEffect2D, SetRotatePerSecond, (float), void), AS_CALL_THISCALL);
    // void ParticleEffect2D::SetRotatePerSecondVariance(float rotatePerSecondVariance) | File: ../Urho2D/ParticleEffect2D.h
    engine->RegisterObjectMethod("ParticleEffect2D", "void SetRotatePerSecondVariance(float)", AS_METHODPR(ParticleEffect2D, SetRotatePerSecondVariance, (float), void), AS_CALL_THISCALL);
    // void ParticleEffect2D::SetRotationEnd(float rotationEnd) | File: ../Urho2D/ParticleEffect2D.h
    engine->RegisterObjectMethod("ParticleEffect2D", "void SetRotationEnd(float)", AS_METHODPR(ParticleEffect2D, SetRotationEnd, (float), void), AS_CALL_THISCALL);
    // void ParticleEffect2D::SetRotationEndVariance(float rotationEndVariance) | File: ../Urho2D/ParticleEffect2D.h
    engine->RegisterObjectMethod("ParticleEffect2D", "void SetRotationEndVariance(float)", AS_METHODPR(ParticleEffect2D, SetRotationEndVariance, (float), void), AS_CALL_THISCALL);
    // void ParticleEffect2D::SetRotationStart(float rotationStart) | File: ../Urho2D/ParticleEffect2D.h
    engine->RegisterObjectMethod("ParticleEffect2D", "void SetRotationStart(float)", AS_METHODPR(ParticleEffect2D, SetRotationStart, (float), void), AS_CALL_THISCALL);
    // void ParticleEffect2D::SetRotationStartVariance(float rotationStartVariance) | File: ../Urho2D/ParticleEffect2D.h
    engine->RegisterObjectMethod("ParticleEffect2D", "void SetRotationStartVariance(float)", AS_METHODPR(ParticleEffect2D, SetRotationStartVariance, (float), void), AS_CALL_THISCALL);
    // void ParticleEffect2D::SetSourcePositionVariance(const Vector2& sourcePositionVariance) | File: ../Urho2D/ParticleEffect2D.h
    engine->RegisterObjectMethod("ParticleEffect2D", "void SetSourcePositionVariance(const Vector2&in)", AS_METHODPR(ParticleEffect2D, SetSourcePositionVariance, (const Vector2&), void), AS_CALL_THISCALL);
    // void ParticleEffect2D::SetSpeed(float speed) | File: ../Urho2D/ParticleEffect2D.h
    engine->RegisterObjectMethod("ParticleEffect2D", "void SetSpeed(float)", AS_METHODPR(ParticleEffect2D, SetSpeed, (float), void), AS_CALL_THISCALL);
    // void ParticleEffect2D::SetSpeedVariance(float speedVariance) | File: ../Urho2D/ParticleEffect2D.h
    engine->RegisterObjectMethod("ParticleEffect2D", "void SetSpeedVariance(float)", AS_METHODPR(ParticleEffect2D, SetSpeedVariance, (float), void), AS_CALL_THISCALL);
    // void ParticleEffect2D::SetSprite(Sprite2D* sprite) | File: ../Urho2D/ParticleEffect2D.h
    engine->RegisterObjectMethod("ParticleEffect2D", "void SetSprite(Sprite2D@+)", AS_METHODPR(ParticleEffect2D, SetSprite, (Sprite2D*), void), AS_CALL_THISCALL);
    // void ParticleEffect2D::SetStartColor(const Color& startColor) | File: ../Urho2D/ParticleEffect2D.h
    engine->RegisterObjectMethod("ParticleEffect2D", "void SetStartColor(const Color&in)", AS_METHODPR(ParticleEffect2D, SetStartColor, (const Color&), void), AS_CALL_THISCALL);
    // void ParticleEffect2D::SetStartColorVariance(const Color& startColorVariance) | File: ../Urho2D/ParticleEffect2D.h
    engine->RegisterObjectMethod("ParticleEffect2D", "void SetStartColorVariance(const Color&in)", AS_METHODPR(ParticleEffect2D, SetStartColorVariance, (const Color&), void), AS_CALL_THISCALL);
    // void ParticleEffect2D::SetStartParticleSize(float startParticleSize) | File: ../Urho2D/ParticleEffect2D.h
    engine->RegisterObjectMethod("ParticleEffect2D", "void SetStartParticleSize(float)", AS_METHODPR(ParticleEffect2D, SetStartParticleSize, (float), void), AS_CALL_THISCALL);
    // void ParticleEffect2D::SetStartParticleSizeVariance(float startParticleSizeVariance) | File: ../Urho2D/ParticleEffect2D.h
    engine->RegisterObjectMethod("ParticleEffect2D", "void SetStartParticleSizeVariance(float)", AS_METHODPR(ParticleEffect2D, SetStartParticleSizeVariance, (float), void), AS_CALL_THISCALL);
    // void ParticleEffect2D::SetTangentialAcceleration(float tangentialAcceleration) | File: ../Urho2D/ParticleEffect2D.h
    engine->RegisterObjectMethod("ParticleEffect2D", "void SetTangentialAcceleration(float)", AS_METHODPR(ParticleEffect2D, SetTangentialAcceleration, (float), void), AS_CALL_THISCALL);
    // void ParticleEffect2D::SetTangentialAccelVariance(float tangentialAccelVariance) | File: ../Urho2D/ParticleEffect2D.h
    engine->RegisterObjectMethod("ParticleEffect2D", "void SetTangentialAccelVariance(float)", AS_METHODPR(ParticleEffect2D, SetTangentialAccelVariance, (float), void), AS_CALL_THISCALL);
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod("ParticleEffect2D", "void UnsubscribeFromAllEvents()", AS_METHODPR(ParticleEffect2D, UnsubscribeFromAllEvents, (), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ParticleEffect2D", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", AS_FUNCTION_OBJFIRST(ParticleEffect2D_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), AS_CALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ParticleEffect2D", "void UnsubscribeFromEvent(StringHash)", AS_METHODPR(ParticleEffect2D, UnsubscribeFromEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ParticleEffect2D", "void UnsubscribeFromEvent(Object@+, StringHash)", AS_METHODPR(ParticleEffect2D, UnsubscribeFromEvent, (Object*, StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ParticleEffect2D", "void UnsubscribeFromEvents(Object@+)", AS_METHODPR(ParticleEffect2D, UnsubscribeFromEvents, (Object*), void), AS_CALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("ParticleEffect2D", "int WeakRefs() const", AS_METHODPR(ParticleEffect2D, WeakRefs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEffect2D", "int get_weakRefs() const", AS_METHODPR(ParticleEffect2D, WeakRefs, () const, int), AS_CALL_THISCALL);
#ifdef REGISTER_MANUAL_PART_Resource
    REGISTER_MANUAL_PART_Resource(ParticleEffect2D, "ParticleEffect2D")
#endif
#ifdef REGISTER_MANUAL_PART_Object
    REGISTER_MANUAL_PART_Object(ParticleEffect2D, "ParticleEffect2D")
#endif
#ifdef REGISTER_MANUAL_PART_RefCounted
    REGISTER_MANUAL_PART_RefCounted(ParticleEffect2D, "ParticleEffect2D")
#endif
#ifdef REGISTER_MANUAL_PART_ParticleEffect2D
    REGISTER_MANUAL_PART_ParticleEffect2D(ParticleEffect2D, "ParticleEffect2D")
#endif
    RegisterSubclass<Resource, ParticleEffect2D>(engine, "Resource", "ParticleEffect2D");
    RegisterSubclass<Object, ParticleEffect2D>(engine, "Object", "ParticleEffect2D");
    RegisterSubclass<RefCounted, ParticleEffect2D>(engine, "RefCounted", "ParticleEffect2D");
#endif

    // void Drawable::AddLight(Light* light) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("ParticleEmitter", "void AddLight(Light@+)", AS_METHODPR(ParticleEmitter, AddLight, (Light*), void), AS_CALL_THISCALL);
    // void RefCounted::AddRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("ParticleEmitter", asBEHAVE_ADDREF, "void f()", AS_METHODPR(ParticleEmitter, AddRef, (), void), AS_CALL_THISCALL);
    // void Component::AddReplicationState(ComponentReplicationState* state) | File: ../Scene/Component.h
    // Error: type "ComponentReplicationState*" can not automatically bind
    // void Drawable::AddVertexLight(Light* light) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("ParticleEmitter", "void AddVertexLight(Light@+)", AS_METHODPR(ParticleEmitter, AddVertexLight, (Light*), void), AS_CALL_THISCALL);
    // void Serializable::AllocateNetworkState() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ParticleEmitter", "void AllocateNetworkState()", AS_METHODPR(ParticleEmitter, AllocateNetworkState, (), void), AS_CALL_THISCALL);
    // virtual void Serializable::ApplyAttributes() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ParticleEmitter", "void ApplyAttributes()", AS_METHODPR(ParticleEmitter, ApplyAttributes, (), void), AS_CALL_THISCALL);
    // void ParticleEmitter::ApplyEffect() | File: ../Graphics/ParticleEmitter.h
    engine->RegisterObjectMethod("ParticleEmitter", "void ApplyEffect()", AS_METHODPR(ParticleEmitter, ApplyEffect, (), void), AS_CALL_THISCALL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // void Component::CleanupConnection(Connection* connection) | File: ../Scene/Component.h
    // Not registered because have @manualbind mark
    // void BillboardSet::Commit() | File: ../Graphics/BillboardSet.h
    engine->RegisterObjectMethod("ParticleEmitter", "void Commit()", AS_METHODPR(ParticleEmitter, Commit, (), void), AS_CALL_THISCALL);
    // void Drawable::DrawDebugGeometry(DebugRenderer* debug, bool depthTest) override | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("ParticleEmitter", "void DrawDebugGeometry(DebugRenderer@+, bool)", AS_METHODPR(ParticleEmitter, DrawDebugGeometry, (DebugRenderer*, bool), void), AS_CALL_THISCALL);
    // virtual bool Drawable::DrawOcclusion(OcclusionBuffer* buffer) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("ParticleEmitter", "bool DrawOcclusion(OcclusionBuffer@+)", AS_METHODPR(ParticleEmitter, DrawOcclusion, (OcclusionBuffer*), bool), AS_CALL_THISCALL);
    // bool Animatable::GetAnimationEnabled() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ParticleEmitter", "bool GetAnimationEnabled() const", AS_METHODPR(ParticleEmitter, GetAnimationEnabled, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter", "bool get_animationEnabled() const", AS_METHODPR(ParticleEmitter, GetAnimationEnabled, () const, bool), AS_CALL_THISCALL);
    // float BillboardSet::GetAnimationLodBias() const | File: ../Graphics/BillboardSet.h
    engine->RegisterObjectMethod("ParticleEmitter", "float GetAnimationLodBias() const", AS_METHODPR(ParticleEmitter, GetAnimationLodBias, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter", "float get_animationLodBias() const", AS_METHODPR(ParticleEmitter, GetAnimationLodBias, () const, float), AS_CALL_THISCALL);
    // Variant Serializable::GetAttribute(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ParticleEmitter", "Variant GetAttribute(uint) const", AS_METHODPR(ParticleEmitter, GetAttribute, (unsigned) const, Variant), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter", "Variant get_attributes(uint) const", AS_METHODPR(ParticleEmitter, GetAttribute, (unsigned) const, Variant), AS_CALL_THISCALL);
    // Variant Serializable::GetAttribute(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ParticleEmitter", "Variant GetAttribute(const String&in) const", AS_METHODPR(ParticleEmitter, GetAttribute, (const String&) const, Variant), AS_CALL_THISCALL);
    // ValueAnimation* Animatable::GetAttributeAnimation(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ParticleEmitter", "ValueAnimation@+ GetAttributeAnimation(const String&in) const", AS_METHODPR(ParticleEmitter, GetAttributeAnimation, (const String&) const, ValueAnimation*), AS_CALL_THISCALL);
    // float Animatable::GetAttributeAnimationSpeed(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ParticleEmitter", "float GetAttributeAnimationSpeed(const String&in) const", AS_METHODPR(ParticleEmitter, GetAttributeAnimationSpeed, (const String&) const, float), AS_CALL_THISCALL);
    // float Animatable::GetAttributeAnimationTime(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ParticleEmitter", "float GetAttributeAnimationTime(const String&in) const", AS_METHODPR(ParticleEmitter, GetAttributeAnimationTime, (const String&) const, float), AS_CALL_THISCALL);
    // WrapMode Animatable::GetAttributeAnimationWrapMode(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ParticleEmitter", "WrapMode GetAttributeAnimationWrapMode(const String&in) const", AS_METHODPR(ParticleEmitter, GetAttributeAnimationWrapMode, (const String&) const, WrapMode), AS_CALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ParticleEmitter", "Variant GetAttributeDefault(uint) const", AS_METHODPR(ParticleEmitter, GetAttributeDefault, (unsigned) const, Variant), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter", "Variant get_attributeDefaults(uint) const", AS_METHODPR(ParticleEmitter, GetAttributeDefault, (unsigned) const, Variant), AS_CALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ParticleEmitter", "Variant GetAttributeDefault(const String&in) const", AS_METHODPR(ParticleEmitter, GetAttributeDefault, (const String&) const, Variant), AS_CALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // AutoRemoveMode ParticleEmitter::GetAutoRemoveMode() const | File: ../Graphics/ParticleEmitter.h
    engine->RegisterObjectMethod("ParticleEmitter", "AutoRemoveMode GetAutoRemoveMode() const", AS_METHODPR(ParticleEmitter, GetAutoRemoveMode, () const, AutoRemoveMode), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter", "AutoRemoveMode get_autoRemoveMode() const", AS_METHODPR(ParticleEmitter, GetAutoRemoveMode, () const, AutoRemoveMode), AS_CALL_THISCALL);
    // const Vector<SourceBatch>& Drawable::GetBatches() const | File: ../Graphics/Drawable.h
    // Error: type "const Vector<SourceBatch>&" can not automatically bind
    // Billboard* BillboardSet::GetBillboard(unsigned index) | File: ../Graphics/BillboardSet.h
    engine->RegisterObjectMethod("ParticleEmitter", "Billboard@+ GetBillboard(uint)", AS_METHODPR(ParticleEmitter, GetBillboard, (unsigned), Billboard*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter", "Billboard@+ get_billboards(uint)", AS_METHODPR(ParticleEmitter, GetBillboard, (unsigned), Billboard*), AS_CALL_THISCALL);
    // PODVector<Billboard>& BillboardSet::GetBillboards() | File: ../Graphics/BillboardSet.h
    // Error: type "PODVector<Billboard>&" can not automatically bind
    // VariantVector BillboardSet::GetBillboardsAttr() const | File: ../Graphics/BillboardSet.h
    // Error: type "VariantVector" can not automatically bind
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ParticleEmitter", "bool GetBlockEvents() const", AS_METHODPR(ParticleEmitter, GetBlockEvents, () const, bool), AS_CALL_THISCALL);
    // const BoundingBox& Drawable::GetBoundingBox() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("ParticleEmitter", "const BoundingBox& GetBoundingBox() const", AS_METHODPR(ParticleEmitter, GetBoundingBox, () const, const BoundingBox&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter", "const BoundingBox& get_boundingBox() const", AS_METHODPR(ParticleEmitter, GetBoundingBox, () const, const BoundingBox&), AS_CALL_THISCALL);
    // bool Drawable::GetCastShadows() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("ParticleEmitter", "bool GetCastShadows() const", AS_METHODPR(ParticleEmitter, GetCastShadows, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter", "bool get_castShadows() const", AS_METHODPR(ParticleEmitter, GetCastShadows, () const, bool), AS_CALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ParticleEmitter", "const String& GetCategory() const", AS_METHODPR(ParticleEmitter, GetCategory, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter", "const String& get_category() const", AS_METHODPR(ParticleEmitter, GetCategory, () const, const String&), AS_CALL_THISCALL);
    // Component* Component::GetComponent(StringHash type) const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ParticleEmitter", "Component@+ GetComponent(StringHash) const", AS_METHODPR(ParticleEmitter, GetComponent, (StringHash) const, Component*), AS_CALL_THISCALL);
    // template<class T> T* Component::GetComponent() const | File: ../Scene/Component.h
    // Not registered because template
    // void Component::GetComponents(PODVector<Component*>& dest, StringHash type) const | File: ../Scene/Component.h
    // Error: type "PODVector<Component*>&" can not automatically bind
    // template<class T> void Component::GetComponents(PODVector<T*>& dest) const | File: ../Scene/Component.h
    // Not registered because template
    // Context* Object::GetContext() const | File: ../Core/Object.h
    // Error: type "Context*" can used only as function parameter
    // virtual void Component::GetDependencyNodes(PODVector<Node*>& dest) | File: ../Scene/Component.h
    // Error: type "PODVector<Node*>&" can not automatically bind
    // float Drawable::GetDistance() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("ParticleEmitter", "float GetDistance() const", AS_METHODPR(ParticleEmitter, GetDistance, () const, float), AS_CALL_THISCALL);
    // unsigned char Drawable::GetDrawableFlags() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("ParticleEmitter", "uint8 GetDrawableFlags() const", AS_METHODPR(ParticleEmitter, GetDrawableFlags, () const, unsigned char), AS_CALL_THISCALL);
    // float Drawable::GetDrawDistance() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("ParticleEmitter", "float GetDrawDistance() const", AS_METHODPR(ParticleEmitter, GetDrawDistance, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter", "float get_drawDistance() const", AS_METHODPR(ParticleEmitter, GetDrawDistance, () const, float), AS_CALL_THISCALL);
    // ParticleEffect* ParticleEmitter::GetEffect() const | File: ../Graphics/ParticleEmitter.h
    engine->RegisterObjectMethod("ParticleEmitter", "ParticleEffect@+ GetEffect() const", AS_METHODPR(ParticleEmitter, GetEffect, () const, ParticleEffect*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter", "ParticleEffect@+ get_effect() const", AS_METHODPR(ParticleEmitter, GetEffect, () const, ParticleEffect*), AS_CALL_THISCALL);
    // ResourceRef ParticleEmitter::GetEffectAttr() const | File: ../Graphics/ParticleEmitter.h
    engine->RegisterObjectMethod("ParticleEmitter", "ResourceRef GetEffectAttr() const", AS_METHODPR(ParticleEmitter, GetEffectAttr, () const, ResourceRef), AS_CALL_THISCALL);
    // VariantMap& Object::GetEventDataMap() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ParticleEmitter", "VariantMap& GetEventDataMap() const", AS_METHODPR(ParticleEmitter, GetEventDataMap, () const, VariantMap&), AS_CALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ParticleEmitter", "Object@+ GetEventSender() const", AS_METHODPR(ParticleEmitter, GetEventSender, () const, Object*), AS_CALL_THISCALL);
    // FaceCameraMode BillboardSet::GetFaceCameraMode() const | File: ../Graphics/BillboardSet.h
    engine->RegisterObjectMethod("ParticleEmitter", "FaceCameraMode GetFaceCameraMode() const", AS_METHODPR(ParticleEmitter, GetFaceCameraMode, () const, FaceCameraMode), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter", "FaceCameraMode get_faceCameraMode() const", AS_METHODPR(ParticleEmitter, GetFaceCameraMode, () const, FaceCameraMode), AS_CALL_THISCALL);
    // Light* Drawable::GetFirstLight() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("ParticleEmitter", "Light@+ GetFirstLight() const", AS_METHODPR(ParticleEmitter, GetFirstLight, () const, Light*), AS_CALL_THISCALL);
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ParticleEmitter", "const Variant& GetGlobalVar(StringHash) const", AS_METHODPR(ParticleEmitter, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter", "const Variant& get_globalVar(StringHash) const", AS_METHODPR(ParticleEmitter, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ParticleEmitter", "const VariantMap& GetGlobalVars() const", AS_METHODPR(ParticleEmitter, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter", "const VariantMap& get_globalVars() const", AS_METHODPR(ParticleEmitter, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    // unsigned Component::GetID() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ParticleEmitter", "uint GetID() const", AS_METHODPR(ParticleEmitter, GetID, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter", "uint get_id() const", AS_METHODPR(ParticleEmitter, GetID, () const, unsigned), AS_CALL_THISCALL);
    // bool Serializable::GetInterceptNetworkUpdate(const String& attributeName) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ParticleEmitter", "bool GetInterceptNetworkUpdate(const String&in) const", AS_METHODPR(ParticleEmitter, GetInterceptNetworkUpdate, (const String&) const, bool), AS_CALL_THISCALL);
    // unsigned Drawable::GetLightMask() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("ParticleEmitter", "uint GetLightMask() const", AS_METHODPR(ParticleEmitter, GetLightMask, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter", "uint get_lightMask() const", AS_METHODPR(ParticleEmitter, GetLightMask, () const, unsigned), AS_CALL_THISCALL);
    // const PODVector<Light*>& Drawable::GetLights() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("ParticleEmitter", "Array<Light@>@ GetLights() const", AS_FUNCTION_OBJFIRST(ParticleEmitter_GetLights_void), AS_CALL_CDECL_OBJFIRST);
    // float Drawable::GetLodBias() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("ParticleEmitter", "float GetLodBias() const", AS_METHODPR(ParticleEmitter, GetLodBias, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter", "float get_lodBias() const", AS_METHODPR(ParticleEmitter, GetLodBias, () const, float), AS_CALL_THISCALL);
    // float Drawable::GetLodDistance() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("ParticleEmitter", "float GetLodDistance() const", AS_METHODPR(ParticleEmitter, GetLodDistance, () const, float), AS_CALL_THISCALL);
    // virtual Geometry* Drawable::GetLodGeometry(unsigned batchIndex, unsigned level) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("ParticleEmitter", "Geometry@+ GetLodGeometry(uint, uint)", AS_METHODPR(ParticleEmitter, GetLodGeometry, (unsigned, unsigned), Geometry*), AS_CALL_THISCALL);
    // Material* BillboardSet::GetMaterial() const | File: ../Graphics/BillboardSet.h
    engine->RegisterObjectMethod("ParticleEmitter", "Material@+ GetMaterial() const", AS_METHODPR(ParticleEmitter, GetMaterial, () const, Material*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter", "Material@+ get_material() const", AS_METHODPR(ParticleEmitter, GetMaterial, () const, Material*), AS_CALL_THISCALL);
    // ResourceRef BillboardSet::GetMaterialAttr() const | File: ../Graphics/BillboardSet.h
    engine->RegisterObjectMethod("ParticleEmitter", "ResourceRef GetMaterialAttr() const", AS_METHODPR(ParticleEmitter, GetMaterialAttr, () const, ResourceRef), AS_CALL_THISCALL);
    // unsigned Drawable::GetMaxLights() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("ParticleEmitter", "uint GetMaxLights() const", AS_METHODPR(ParticleEmitter, GetMaxLights, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter", "uint get_maxLights() const", AS_METHODPR(ParticleEmitter, GetMaxLights, () const, unsigned), AS_CALL_THISCALL);
    // float Drawable::GetMaxZ() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("ParticleEmitter", "float GetMaxZ() const", AS_METHODPR(ParticleEmitter, GetMaxZ, () const, float), AS_CALL_THISCALL);
    // float BillboardSet::GetMinAngle() const | File: ../Graphics/BillboardSet.h
    engine->RegisterObjectMethod("ParticleEmitter", "float GetMinAngle() const", AS_METHODPR(ParticleEmitter, GetMinAngle, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter", "float get_minAngle() const", AS_METHODPR(ParticleEmitter, GetMinAngle, () const, float), AS_CALL_THISCALL);
    // float Drawable::GetMinZ() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("ParticleEmitter", "float GetMinZ() const", AS_METHODPR(ParticleEmitter, GetMinZ, () const, float), AS_CALL_THISCALL);
    // const PODVector<unsigned char>& BillboardSet::GetNetBillboardsAttr() const | File: ../Graphics/BillboardSet.h
    // Error: type "const PODVector<unsigned char>&" can not automatically bind
    // virtual const Vector<AttributeInfo>* Serializable::GetNetworkAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // NetworkState* Serializable::GetNetworkState() const | File: ../Scene/Serializable.h
    // Error: type "NetworkState*" can not automatically bind
    // Node* Component::GetNode() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ParticleEmitter", "Node@+ GetNode() const", AS_METHODPR(ParticleEmitter, GetNode, () const, Node*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter", "Node@+ get_node() const", AS_METHODPR(ParticleEmitter, GetNode, () const, Node*), AS_CALL_THISCALL);
    // unsigned Serializable::GetNumAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ParticleEmitter", "uint GetNumAttributes() const", AS_METHODPR(ParticleEmitter, GetNumAttributes, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter", "uint get_numAttributes() const", AS_METHODPR(ParticleEmitter, GetNumAttributes, () const, unsigned), AS_CALL_THISCALL);
    // unsigned BillboardSet::GetNumBillboards() const | File: ../Graphics/BillboardSet.h
    engine->RegisterObjectMethod("ParticleEmitter", "uint GetNumBillboards() const", AS_METHODPR(ParticleEmitter, GetNumBillboards, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter", "uint get_numBillboards() const", AS_METHODPR(ParticleEmitter, GetNumBillboards, () const, unsigned), AS_CALL_THISCALL);
    // unsigned Serializable::GetNumNetworkAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ParticleEmitter", "uint GetNumNetworkAttributes() const", AS_METHODPR(ParticleEmitter, GetNumNetworkAttributes, () const, unsigned), AS_CALL_THISCALL);
    // virtual unsigned Drawable::GetNumOccluderTriangles() | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("ParticleEmitter", "uint GetNumOccluderTriangles()", AS_METHODPR(ParticleEmitter, GetNumOccluderTriangles, (), unsigned), AS_CALL_THISCALL);
    // unsigned ParticleEmitter::GetNumParticles() const | File: ../Graphics/ParticleEmitter.h
    engine->RegisterObjectMethod("ParticleEmitter", "uint GetNumParticles() const", AS_METHODPR(ParticleEmitter, GetNumParticles, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter", "uint get_numParticles() const", AS_METHODPR(ParticleEmitter, GetNumParticles, () const, unsigned), AS_CALL_THISCALL);
    // ObjectAnimation* Animatable::GetObjectAnimation() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ParticleEmitter", "ObjectAnimation@+ GetObjectAnimation() const", AS_METHODPR(ParticleEmitter, GetObjectAnimation, () const, ObjectAnimation*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter", "ObjectAnimation@+ get_objectAnimation() const", AS_METHODPR(ParticleEmitter, GetObjectAnimation, () const, ObjectAnimation*), AS_CALL_THISCALL);
    // ResourceRef Animatable::GetObjectAnimationAttr() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ParticleEmitter", "ResourceRef GetObjectAnimationAttr() const", AS_METHODPR(ParticleEmitter, GetObjectAnimationAttr, () const, ResourceRef), AS_CALL_THISCALL);
    // Octant* Drawable::GetOctant() const | File: ../Graphics/Drawable.h
    // Error: type "Octant" can not automatically bind bacause have @nobind mark
    // VariantVector ParticleEmitter::GetParticleBillboardsAttr() const | File: ../Graphics/ParticleEmitter.h
    // Error: type "VariantVector" can not automatically bind
    // VariantVector ParticleEmitter::GetParticlesAttr() const | File: ../Graphics/ParticleEmitter.h
    // Error: type "VariantVector" can not automatically bind
    // Scene* Component::GetScene() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ParticleEmitter", "Scene@+ GetScene() const", AS_METHODPR(ParticleEmitter, GetScene, () const, Scene*), AS_CALL_THISCALL);
    // bool ParticleEmitter::GetSerializeParticles() const | File: ../Graphics/ParticleEmitter.h
    engine->RegisterObjectMethod("ParticleEmitter", "bool GetSerializeParticles() const", AS_METHODPR(ParticleEmitter, GetSerializeParticles, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter", "bool get_serializeParticles() const", AS_METHODPR(ParticleEmitter, GetSerializeParticles, () const, bool), AS_CALL_THISCALL);
    // float Drawable::GetShadowDistance() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("ParticleEmitter", "float GetShadowDistance() const", AS_METHODPR(ParticleEmitter, GetShadowDistance, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter", "float get_shadowDistance() const", AS_METHODPR(ParticleEmitter, GetShadowDistance, () const, float), AS_CALL_THISCALL);
    // unsigned Drawable::GetShadowMask() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("ParticleEmitter", "uint GetShadowMask() const", AS_METHODPR(ParticleEmitter, GetShadowMask, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter", "uint get_shadowMask() const", AS_METHODPR(ParticleEmitter, GetShadowMask, () const, unsigned), AS_CALL_THISCALL);
    // float Drawable::GetSortValue() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("ParticleEmitter", "float GetSortValue() const", AS_METHODPR(ParticleEmitter, GetSortValue, () const, float), AS_CALL_THISCALL);
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ParticleEmitter", "Object@+ GetSubsystem(StringHash) const", AS_METHODPR(ParticleEmitter, GetSubsystem, (StringHash) const, Object*), AS_CALL_THISCALL);
    // template<class T> T* Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("ParticleEmitter", "StringHash GetType() const", AS_METHODPR(ParticleEmitter, GetType, () const, StringHash), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter", "StringHash get_type() const", AS_METHODPR(ParticleEmitter, GetType, () const, StringHash), AS_CALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("ParticleEmitter", "const String& GetTypeName() const", AS_METHODPR(ParticleEmitter, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter", "const String& get_typeName() const", AS_METHODPR(ParticleEmitter, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    // UpdateGeometryType BillboardSet::GetUpdateGeometryType() override | File: ../Graphics/BillboardSet.h
    engine->RegisterObjectMethod("ParticleEmitter", "UpdateGeometryType GetUpdateGeometryType()", AS_METHODPR(ParticleEmitter, GetUpdateGeometryType, (), UpdateGeometryType), AS_CALL_THISCALL);
    // const PODVector<Light*>& Drawable::GetVertexLights() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("ParticleEmitter", "Array<Light@>@ GetVertexLights() const", AS_FUNCTION_OBJFIRST(ParticleEmitter_GetVertexLights_void), AS_CALL_CDECL_OBJFIRST);
    // unsigned Drawable::GetViewMask() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("ParticleEmitter", "uint GetViewMask() const", AS_METHODPR(ParticleEmitter, GetViewMask, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter", "uint get_viewMask() const", AS_METHODPR(ParticleEmitter, GetViewMask, () const, unsigned), AS_CALL_THISCALL);
    // const BoundingBox& Drawable::GetWorldBoundingBox() | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("ParticleEmitter", "const BoundingBox& GetWorldBoundingBox()", AS_METHODPR(ParticleEmitter, GetWorldBoundingBox, (), const BoundingBox&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter", "const BoundingBox& get_worldBoundingBox()", AS_METHODPR(ParticleEmitter, GetWorldBoundingBox, (), const BoundingBox&), AS_CALL_THISCALL);
    // Zone* Drawable::GetZone() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("ParticleEmitter", "Zone@+ GetZone() const", AS_METHODPR(ParticleEmitter, GetZone, () const, Zone*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter", "Zone@+ get_zone() const", AS_METHODPR(ParticleEmitter, GetZone, () const, Zone*), AS_CALL_THISCALL);
    // unsigned Drawable::GetZoneMask() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("ParticleEmitter", "uint GetZoneMask() const", AS_METHODPR(ParticleEmitter, GetZoneMask, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter", "uint get_zoneMask() const", AS_METHODPR(ParticleEmitter, GetZoneMask, () const, unsigned), AS_CALL_THISCALL);
    // bool Drawable::HasBasePass(unsigned batchIndex) const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("ParticleEmitter", "bool HasBasePass(uint) const", AS_METHODPR(ParticleEmitter, HasBasePass, (unsigned) const, bool), AS_CALL_THISCALL);
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ParticleEmitter", "bool HasEventHandlers() const", AS_METHODPR(ParticleEmitter, HasEventHandlers, () const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ParticleEmitter", "bool HasSubscribedToEvent(StringHash) const", AS_METHODPR(ParticleEmitter, HasSubscribedToEvent, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ParticleEmitter", "bool HasSubscribedToEvent(Object@+, StringHash) const", AS_METHODPR(ParticleEmitter, HasSubscribedToEvent, (Object*, StringHash) const, bool), AS_CALL_THISCALL);
    // bool ParticleEmitter::IsEmitting() const | File: ../Graphics/ParticleEmitter.h
    engine->RegisterObjectMethod("ParticleEmitter", "bool IsEmitting() const", AS_METHODPR(ParticleEmitter, IsEmitting, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter", "bool get_emitting() const", AS_METHODPR(ParticleEmitter, IsEmitting, () const, bool), AS_CALL_THISCALL);
    // bool Component::IsEnabled() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ParticleEmitter", "bool IsEnabled() const", AS_METHODPR(ParticleEmitter, IsEnabled, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter", "bool get_enabled() const", AS_METHODPR(ParticleEmitter, IsEnabled, () const, bool), AS_CALL_THISCALL);
    // bool Component::IsEnabledEffective() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ParticleEmitter", "bool IsEnabledEffective() const", AS_METHODPR(ParticleEmitter, IsEnabledEffective, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter", "bool get_enabledEffective() const", AS_METHODPR(ParticleEmitter, IsEnabledEffective, () const, bool), AS_CALL_THISCALL);
    // bool BillboardSet::IsFixedScreenSize() const | File: ../Graphics/BillboardSet.h
    engine->RegisterObjectMethod("ParticleEmitter", "bool IsFixedScreenSize() const", AS_METHODPR(ParticleEmitter, IsFixedScreenSize, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter", "bool get_fixedScreenSize() const", AS_METHODPR(ParticleEmitter, IsFixedScreenSize, () const, bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ParticleEmitter", "bool IsInstanceOf(StringHash) const", AS_METHODPR(ParticleEmitter, IsInstanceOf, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // bool Drawable::IsInView() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("ParticleEmitter", "bool IsInView() const", AS_METHODPR(ParticleEmitter, IsInView, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter", "bool get_inView() const", AS_METHODPR(ParticleEmitter, IsInView, () const, bool), AS_CALL_THISCALL);
    // bool Drawable::IsInView(Camera* camera) const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("ParticleEmitter", "bool IsInView(Camera@+) const", AS_METHODPR(ParticleEmitter, IsInView, (Camera*) const, bool), AS_CALL_THISCALL);
    // bool Drawable::IsInView(const FrameInfo& frame, bool anyCamera=false) const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("ParticleEmitter", "bool IsInView(const FrameInfo&in, bool = false) const", AS_METHODPR(ParticleEmitter, IsInView, (const FrameInfo&, bool) const, bool), AS_CALL_THISCALL);
    // bool Drawable::IsOccludee() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("ParticleEmitter", "bool IsOccludee() const", AS_METHODPR(ParticleEmitter, IsOccludee, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter", "bool get_occludee() const", AS_METHODPR(ParticleEmitter, IsOccludee, () const, bool), AS_CALL_THISCALL);
    // bool Drawable::IsOccluder() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("ParticleEmitter", "bool IsOccluder() const", AS_METHODPR(ParticleEmitter, IsOccluder, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter", "bool get_occluder() const", AS_METHODPR(ParticleEmitter, IsOccluder, () const, bool), AS_CALL_THISCALL);
    // bool BillboardSet::IsRelative() const | File: ../Graphics/BillboardSet.h
    engine->RegisterObjectMethod("ParticleEmitter", "bool IsRelative() const", AS_METHODPR(ParticleEmitter, IsRelative, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter", "bool get_relative() const", AS_METHODPR(ParticleEmitter, IsRelative, () const, bool), AS_CALL_THISCALL);
    // bool Component::IsReplicated() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ParticleEmitter", "bool IsReplicated() const", AS_METHODPR(ParticleEmitter, IsReplicated, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter", "bool get_replicated() const", AS_METHODPR(ParticleEmitter, IsReplicated, () const, bool), AS_CALL_THISCALL);
    // bool BillboardSet::IsScaled() const | File: ../Graphics/BillboardSet.h
    engine->RegisterObjectMethod("ParticleEmitter", "bool IsScaled() const", AS_METHODPR(ParticleEmitter, IsScaled, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter", "bool get_scaled() const", AS_METHODPR(ParticleEmitter, IsScaled, () const, bool), AS_CALL_THISCALL);
    // bool BillboardSet::IsSorted() const | File: ../Graphics/BillboardSet.h
    engine->RegisterObjectMethod("ParticleEmitter", "bool IsSorted() const", AS_METHODPR(ParticleEmitter, IsSorted, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter", "bool get_sorted() const", AS_METHODPR(ParticleEmitter, IsSorted, () const, bool), AS_CALL_THISCALL);
    // bool Serializable::IsTemporary() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ParticleEmitter", "bool IsTemporary() const", AS_METHODPR(ParticleEmitter, IsTemporary, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter", "bool get_temporary() const", AS_METHODPR(ParticleEmitter, IsTemporary, () const, bool), AS_CALL_THISCALL);
    // bool Drawable::IsZoneDirty() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("ParticleEmitter", "bool IsZoneDirty() const", AS_METHODPR(ParticleEmitter, IsZoneDirty, () const, bool), AS_CALL_THISCALL);
    // void Drawable::LimitLights() | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("ParticleEmitter", "void LimitLights()", AS_METHODPR(ParticleEmitter, LimitLights, (), void), AS_CALL_THISCALL);
    // void Drawable::LimitVertexLights(bool removeConvertedLights) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("ParticleEmitter", "void LimitVertexLights(bool)", AS_METHODPR(ParticleEmitter, LimitVertexLights, (bool), void), AS_CALL_THISCALL);
    // virtual bool Serializable::Load(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ParticleEmitter", "bool Load(Deserializer&)", AS_METHODPR(ParticleEmitter, Load, (Deserializer&), bool), AS_CALL_THISCALL);
    // bool Animatable::LoadJSON(const JSONValue& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ParticleEmitter", "bool LoadJSON(const JSONValue&in)", AS_METHODPR(ParticleEmitter, LoadJSON, (const JSONValue&), bool), AS_CALL_THISCALL);
    // bool Animatable::LoadXML(const XMLElement& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ParticleEmitter", "bool LoadXML(const XMLElement&in)", AS_METHODPR(ParticleEmitter, LoadXML, (const XMLElement&), bool), AS_CALL_THISCALL);
    // void Drawable::MarkForUpdate() | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("ParticleEmitter", "void MarkForUpdate()", AS_METHODPR(ParticleEmitter, MarkForUpdate, (), void), AS_CALL_THISCALL);
    // void Drawable::MarkInView(const FrameInfo& frame) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("ParticleEmitter", "void MarkInView(const FrameInfo&in)", AS_METHODPR(ParticleEmitter, MarkInView, (const FrameInfo&), void), AS_CALL_THISCALL);
    // void Drawable::MarkInView(unsigned frameNumber) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("ParticleEmitter", "void MarkInView(uint)", AS_METHODPR(ParticleEmitter, MarkInView, (unsigned), void), AS_CALL_THISCALL);
    // void Component::MarkNetworkUpdate() override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ParticleEmitter", "void MarkNetworkUpdate()", AS_METHODPR(ParticleEmitter, MarkNetworkUpdate, (), void), AS_CALL_THISCALL);
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ParticleEmitter", "void OnEvent(Object@+, StringHash, VariantMap&)", AS_METHODPR(ParticleEmitter, OnEvent, (Object*, StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // virtual void Serializable::OnGetAttribute(const AttributeInfo& attr, Variant& dest) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ParticleEmitter", "void OnGetAttribute(const AttributeInfo&in, Variant&) const", AS_METHODPR(ParticleEmitter, OnGetAttribute, (const AttributeInfo&, Variant&) const, void), AS_CALL_THISCALL);
    // virtual void Serializable::OnSetAttribute(const AttributeInfo& attr, const Variant& src) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ParticleEmitter", "void OnSetAttribute(const AttributeInfo&in, const Variant&in)", AS_METHODPR(ParticleEmitter, OnSetAttribute, (const AttributeInfo&, const Variant&), void), AS_CALL_THISCALL);
    // void ParticleEmitter::OnSetEnabled() override | File: ../Graphics/ParticleEmitter.h
    engine->RegisterObjectMethod("ParticleEmitter", "void OnSetEnabled()", AS_METHODPR(ParticleEmitter, OnSetEnabled, (), void), AS_CALL_THISCALL);
    // explicit ParticleEmitter::ParticleEmitter(Context* context) | File: ../Graphics/ParticleEmitter.h
    engine->RegisterObjectBehaviour("ParticleEmitter", asBEHAVE_FACTORY, "ParticleEmitter@+ f()", AS_FUNCTION(ParticleEmitter_ParticleEmitter_Context), AS_CALL_CDECL);
    // void Component::PrepareNetworkUpdate() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ParticleEmitter", "void PrepareNetworkUpdate()", AS_METHODPR(ParticleEmitter, PrepareNetworkUpdate, (), void), AS_CALL_THISCALL);
    // void BillboardSet::ProcessRayQuery(const RayOctreeQuery& query, PODVector<RayQueryResult>& results) override | File: ../Graphics/BillboardSet.h
    // Error: type "RayOctreeQuery" can not automatically bind bacause have @nobind mark
    // bool Serializable::ReadDeltaUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ParticleEmitter", "bool ReadDeltaUpdate(Deserializer&)", AS_METHODPR(ParticleEmitter, ReadDeltaUpdate, (Deserializer&), bool), AS_CALL_THISCALL);
    // bool Serializable::ReadLatestDataUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ParticleEmitter", "bool ReadLatestDataUpdate(Deserializer&)", AS_METHODPR(ParticleEmitter, ReadLatestDataUpdate, (Deserializer&), bool), AS_CALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("ParticleEmitter", "int Refs() const", AS_METHODPR(ParticleEmitter, Refs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter", "int get_refs() const", AS_METHODPR(ParticleEmitter, Refs, () const, int), AS_CALL_THISCALL);
    // static void ParticleEmitter::RegisterObject(Context* context) | File: ../Graphics/ParticleEmitter.h
    // Not registered because have @nobind mark
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("ParticleEmitter", asBEHAVE_RELEASE, "void f()", AS_METHODPR(ParticleEmitter, ReleaseRef, (), void), AS_CALL_THISCALL);
    // void Component::Remove() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ParticleEmitter", "void Remove()", AS_METHODPR(ParticleEmitter, Remove, (), void), AS_CALL_THISCALL);
    // void ParticleEmitter::RemoveAllParticles() | File: ../Graphics/ParticleEmitter.h
    engine->RegisterObjectMethod("ParticleEmitter", "void RemoveAllParticles()", AS_METHODPR(ParticleEmitter, RemoveAllParticles, (), void), AS_CALL_THISCALL);
    // void Animatable::RemoveAttributeAnimation(const String& name) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ParticleEmitter", "void RemoveAttributeAnimation(const String&in)", AS_METHODPR(ParticleEmitter, RemoveAttributeAnimation, (const String&), void), AS_CALL_THISCALL);
    // void Serializable::RemoveInstanceDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ParticleEmitter", "void RemoveInstanceDefault()", AS_METHODPR(ParticleEmitter, RemoveInstanceDefault, (), void), AS_CALL_THISCALL);
    // void Animatable::RemoveObjectAnimation() | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ParticleEmitter", "void RemoveObjectAnimation()", AS_METHODPR(ParticleEmitter, RemoveObjectAnimation, (), void), AS_CALL_THISCALL);
    // void ParticleEmitter::Reset() | File: ../Graphics/ParticleEmitter.h
    engine->RegisterObjectMethod("ParticleEmitter", "void Reset()", AS_METHODPR(ParticleEmitter, Reset, (), void), AS_CALL_THISCALL);
    // void ParticleEmitter::ResetEmissionTimer() | File: ../Graphics/ParticleEmitter.h
    engine->RegisterObjectMethod("ParticleEmitter", "void ResetEmissionTimer()", AS_METHODPR(ParticleEmitter, ResetEmissionTimer, (), void), AS_CALL_THISCALL);
    // void Serializable::ResetToDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ParticleEmitter", "void ResetToDefault()", AS_METHODPR(ParticleEmitter, ResetToDefault, (), void), AS_CALL_THISCALL);
    // bool Component::Save(Serializer& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ParticleEmitter", "bool Save(Serializer&) const", AS_METHODPR(ParticleEmitter, Save, (Serializer&) const, bool), AS_CALL_THISCALL);
    // virtual bool Serializable::SaveDefaultAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ParticleEmitter", "bool SaveDefaultAttributes() const", AS_METHODPR(ParticleEmitter, SaveDefaultAttributes, () const, bool), AS_CALL_THISCALL);
    // bool Component::SaveJSON(JSONValue& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ParticleEmitter", "bool SaveJSON(JSONValue&) const", AS_METHODPR(ParticleEmitter, SaveJSON, (JSONValue&) const, bool), AS_CALL_THISCALL);
    // bool Component::SaveXML(XMLElement& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ParticleEmitter", "bool SaveXML(XMLElement&) const", AS_METHODPR(ParticleEmitter, SaveXML, (XMLElement&) const, bool), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ParticleEmitter", "void SendEvent(StringHash)", AS_METHODPR(ParticleEmitter, SendEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ParticleEmitter", "void SendEvent(StringHash, VariantMap&)", AS_METHODPR(ParticleEmitter, SendEvent, (StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void Animatable::SetAnimationEnabled(bool enable) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ParticleEmitter", "void SetAnimationEnabled(bool)", AS_METHODPR(ParticleEmitter, SetAnimationEnabled, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter", "void set_animationEnabled(bool)", AS_METHODPR(ParticleEmitter, SetAnimationEnabled, (bool), void), AS_CALL_THISCALL);
    // void BillboardSet::SetAnimationLodBias(float bias) | File: ../Graphics/BillboardSet.h
    engine->RegisterObjectMethod("ParticleEmitter", "void SetAnimationLodBias(float)", AS_METHODPR(ParticleEmitter, SetAnimationLodBias, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter", "void set_animationLodBias(float)", AS_METHODPR(ParticleEmitter, SetAnimationLodBias, (float), void), AS_CALL_THISCALL);
    // void Animatable::SetAnimationTime(float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ParticleEmitter", "void SetAnimationTime(float)", AS_METHODPR(ParticleEmitter, SetAnimationTime, (float), void), AS_CALL_THISCALL);
    // bool Serializable::SetAttribute(unsigned index, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ParticleEmitter", "bool SetAttribute(uint, const Variant&in)", AS_METHODPR(ParticleEmitter, SetAttribute, (unsigned, const Variant&), bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter", "bool set_attributes(uint, const Variant&in)", AS_METHODPR(ParticleEmitter, SetAttribute, (unsigned, const Variant&), bool), AS_CALL_THISCALL);
    // bool Serializable::SetAttribute(const String& name, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ParticleEmitter", "bool SetAttribute(const String&in, const Variant&in)", AS_METHODPR(ParticleEmitter, SetAttribute, (const String&, const Variant&), bool), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimation(const String& name, ValueAnimation* attributeAnimation, WrapMode wrapMode=WM_LOOP, float speed=1.0f) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ParticleEmitter", "void SetAttributeAnimation(const String&in, ValueAnimation@+, WrapMode = WM_LOOP, float = 1.0f)", AS_METHODPR(ParticleEmitter, SetAttributeAnimation, (const String&, ValueAnimation*, WrapMode, float), void), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimationSpeed(const String& name, float speed) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ParticleEmitter", "void SetAttributeAnimationSpeed(const String&in, float)", AS_METHODPR(ParticleEmitter, SetAttributeAnimationSpeed, (const String&, float), void), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimationTime(const String& name, float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ParticleEmitter", "void SetAttributeAnimationTime(const String&in, float)", AS_METHODPR(ParticleEmitter, SetAttributeAnimationTime, (const String&, float), void), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimationWrapMode(const String& name, WrapMode wrapMode) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ParticleEmitter", "void SetAttributeAnimationWrapMode(const String&in, WrapMode)", AS_METHODPR(ParticleEmitter, SetAttributeAnimationWrapMode, (const String&, WrapMode), void), AS_CALL_THISCALL);
    // void ParticleEmitter::SetAutoRemoveMode(AutoRemoveMode mode) | File: ../Graphics/ParticleEmitter.h
    engine->RegisterObjectMethod("ParticleEmitter", "void SetAutoRemoveMode(AutoRemoveMode)", AS_METHODPR(ParticleEmitter, SetAutoRemoveMode, (AutoRemoveMode), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter", "void set_autoRemoveMode(AutoRemoveMode)", AS_METHODPR(ParticleEmitter, SetAutoRemoveMode, (AutoRemoveMode), void), AS_CALL_THISCALL);
    // void Drawable::SetBasePass(unsigned batchIndex) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("ParticleEmitter", "void SetBasePass(uint)", AS_METHODPR(ParticleEmitter, SetBasePass, (unsigned), void), AS_CALL_THISCALL);
    // void BillboardSet::SetBillboardsAttr(const VariantVector& value) | File: ../Graphics/BillboardSet.h
    // Error: type "const VariantVector&" can not automatically bind
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ParticleEmitter", "void SetBlockEvents(bool)", AS_METHODPR(ParticleEmitter, SetBlockEvents, (bool), void), AS_CALL_THISCALL);
    // void Drawable::SetCastShadows(bool enable) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("ParticleEmitter", "void SetCastShadows(bool)", AS_METHODPR(ParticleEmitter, SetCastShadows, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter", "void set_castShadows(bool)", AS_METHODPR(ParticleEmitter, SetCastShadows, (bool), void), AS_CALL_THISCALL);
    // void Drawable::SetDrawDistance(float distance) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("ParticleEmitter", "void SetDrawDistance(float)", AS_METHODPR(ParticleEmitter, SetDrawDistance, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter", "void set_drawDistance(float)", AS_METHODPR(ParticleEmitter, SetDrawDistance, (float), void), AS_CALL_THISCALL);
    // void ParticleEmitter::SetEffect(ParticleEffect* effect) | File: ../Graphics/ParticleEmitter.h
    engine->RegisterObjectMethod("ParticleEmitter", "void SetEffect(ParticleEffect@+)", AS_METHODPR(ParticleEmitter, SetEffect, (ParticleEffect*), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter", "void set_effect(ParticleEffect@+)", AS_METHODPR(ParticleEmitter, SetEffect, (ParticleEffect*), void), AS_CALL_THISCALL);
    // void ParticleEmitter::SetEffectAttr(const ResourceRef& value) | File: ../Graphics/ParticleEmitter.h
    engine->RegisterObjectMethod("ParticleEmitter", "void SetEffectAttr(const ResourceRef&in)", AS_METHODPR(ParticleEmitter, SetEffectAttr, (const ResourceRef&), void), AS_CALL_THISCALL);
    // void ParticleEmitter::SetEmitting(bool enable) | File: ../Graphics/ParticleEmitter.h
    engine->RegisterObjectMethod("ParticleEmitter", "void SetEmitting(bool)", AS_METHODPR(ParticleEmitter, SetEmitting, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter", "void set_emitting(bool)", AS_METHODPR(ParticleEmitter, SetEmitting, (bool), void), AS_CALL_THISCALL);
    // void Component::SetEnabled(bool enable) | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ParticleEmitter", "void SetEnabled(bool)", AS_METHODPR(ParticleEmitter, SetEnabled, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter", "void set_enabled(bool)", AS_METHODPR(ParticleEmitter, SetEnabled, (bool), void), AS_CALL_THISCALL);
    // void BillboardSet::SetFaceCameraMode(FaceCameraMode mode) | File: ../Graphics/BillboardSet.h
    engine->RegisterObjectMethod("ParticleEmitter", "void SetFaceCameraMode(FaceCameraMode)", AS_METHODPR(ParticleEmitter, SetFaceCameraMode, (FaceCameraMode), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter", "void set_faceCameraMode(FaceCameraMode)", AS_METHODPR(ParticleEmitter, SetFaceCameraMode, (FaceCameraMode), void), AS_CALL_THISCALL);
    // void BillboardSet::SetFixedScreenSize(bool enable) | File: ../Graphics/BillboardSet.h
    engine->RegisterObjectMethod("ParticleEmitter", "void SetFixedScreenSize(bool)", AS_METHODPR(ParticleEmitter, SetFixedScreenSize, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter", "void set_fixedScreenSize(bool)", AS_METHODPR(ParticleEmitter, SetFixedScreenSize, (bool), void), AS_CALL_THISCALL);
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ParticleEmitter", "void SetGlobalVar(StringHash, const Variant&in)", AS_METHODPR(ParticleEmitter, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter", "void set_globalVar(StringHash, const Variant&in)", AS_METHODPR(ParticleEmitter, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    // void Serializable::SetInstanceDefault(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ParticleEmitter", "void SetInstanceDefault(bool)", AS_METHODPR(ParticleEmitter, SetInstanceDefault, (bool), void), AS_CALL_THISCALL);
    // void Serializable::SetInterceptNetworkUpdate(const String& attributeName, bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ParticleEmitter", "void SetInterceptNetworkUpdate(const String&in, bool)", AS_METHODPR(ParticleEmitter, SetInterceptNetworkUpdate, (const String&, bool), void), AS_CALL_THISCALL);
    // void Drawable::SetLightMask(unsigned mask) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("ParticleEmitter", "void SetLightMask(uint)", AS_METHODPR(ParticleEmitter, SetLightMask, (unsigned), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter", "void set_lightMask(uint)", AS_METHODPR(ParticleEmitter, SetLightMask, (unsigned), void), AS_CALL_THISCALL);
    // void Drawable::SetLodBias(float bias) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("ParticleEmitter", "void SetLodBias(float)", AS_METHODPR(ParticleEmitter, SetLodBias, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter", "void set_lodBias(float)", AS_METHODPR(ParticleEmitter, SetLodBias, (float), void), AS_CALL_THISCALL);
    // void BillboardSet::SetMaterial(Material* material) | File: ../Graphics/BillboardSet.h
    engine->RegisterObjectMethod("ParticleEmitter", "void SetMaterial(Material@+)", AS_METHODPR(ParticleEmitter, SetMaterial, (Material*), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter", "void set_material(Material@+)", AS_METHODPR(ParticleEmitter, SetMaterial, (Material*), void), AS_CALL_THISCALL);
    // void BillboardSet::SetMaterialAttr(const ResourceRef& value) | File: ../Graphics/BillboardSet.h
    engine->RegisterObjectMethod("ParticleEmitter", "void SetMaterialAttr(const ResourceRef&in)", AS_METHODPR(ParticleEmitter, SetMaterialAttr, (const ResourceRef&), void), AS_CALL_THISCALL);
    // void Drawable::SetMaxLights(unsigned num) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("ParticleEmitter", "void SetMaxLights(uint)", AS_METHODPR(ParticleEmitter, SetMaxLights, (unsigned), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter", "void set_maxLights(uint)", AS_METHODPR(ParticleEmitter, SetMaxLights, (unsigned), void), AS_CALL_THISCALL);
    // void BillboardSet::SetMinAngle(float angle) | File: ../Graphics/BillboardSet.h
    engine->RegisterObjectMethod("ParticleEmitter", "void SetMinAngle(float)", AS_METHODPR(ParticleEmitter, SetMinAngle, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter", "void set_minAngle(float)", AS_METHODPR(ParticleEmitter, SetMinAngle, (float), void), AS_CALL_THISCALL);
    // void Drawable::SetMinMaxZ(float minZ, float maxZ) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("ParticleEmitter", "void SetMinMaxZ(float, float)", AS_METHODPR(ParticleEmitter, SetMinMaxZ, (float, float), void), AS_CALL_THISCALL);
    // void BillboardSet::SetNetBillboardsAttr(const PODVector<unsigned char>& value) | File: ../Graphics/BillboardSet.h
    // Error: type "const PODVector<unsigned char>&" can not automatically bind
    // void BillboardSet::SetNumBillboards(unsigned num) | File: ../Graphics/BillboardSet.h
    engine->RegisterObjectMethod("ParticleEmitter", "void SetNumBillboards(uint)", AS_METHODPR(ParticleEmitter, SetNumBillboards, (unsigned), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter", "void set_numBillboards(uint)", AS_METHODPR(ParticleEmitter, SetNumBillboards, (unsigned), void), AS_CALL_THISCALL);
    // void ParticleEmitter::SetNumParticles(unsigned num) | File: ../Graphics/ParticleEmitter.h
    engine->RegisterObjectMethod("ParticleEmitter", "void SetNumParticles(uint)", AS_METHODPR(ParticleEmitter, SetNumParticles, (unsigned), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter", "void set_numParticles(uint)", AS_METHODPR(ParticleEmitter, SetNumParticles, (unsigned), void), AS_CALL_THISCALL);
    // void Animatable::SetObjectAnimation(ObjectAnimation* objectAnimation) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ParticleEmitter", "void SetObjectAnimation(ObjectAnimation@+)", AS_METHODPR(ParticleEmitter, SetObjectAnimation, (ObjectAnimation*), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter", "void set_objectAnimation(ObjectAnimation@+)", AS_METHODPR(ParticleEmitter, SetObjectAnimation, (ObjectAnimation*), void), AS_CALL_THISCALL);
    // void Animatable::SetObjectAnimationAttr(const ResourceRef& value) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ParticleEmitter", "void SetObjectAnimationAttr(const ResourceRef&in)", AS_METHODPR(ParticleEmitter, SetObjectAnimationAttr, (const ResourceRef&), void), AS_CALL_THISCALL);
    // void Drawable::SetOccludee(bool enable) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("ParticleEmitter", "void SetOccludee(bool)", AS_METHODPR(ParticleEmitter, SetOccludee, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter", "void set_occludee(bool)", AS_METHODPR(ParticleEmitter, SetOccludee, (bool), void), AS_CALL_THISCALL);
    // void Drawable::SetOccluder(bool enable) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("ParticleEmitter", "void SetOccluder(bool)", AS_METHODPR(ParticleEmitter, SetOccluder, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter", "void set_occluder(bool)", AS_METHODPR(ParticleEmitter, SetOccluder, (bool), void), AS_CALL_THISCALL);
    // void ParticleEmitter::SetParticlesAttr(const VariantVector& value) | File: ../Graphics/ParticleEmitter.h
    // Error: type "const VariantVector&" can not automatically bind
    // void BillboardSet::SetRelative(bool enable) | File: ../Graphics/BillboardSet.h
    engine->RegisterObjectMethod("ParticleEmitter", "void SetRelative(bool)", AS_METHODPR(ParticleEmitter, SetRelative, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter", "void set_relative(bool)", AS_METHODPR(ParticleEmitter, SetRelative, (bool), void), AS_CALL_THISCALL);
    // void BillboardSet::SetScaled(bool enable) | File: ../Graphics/BillboardSet.h
    engine->RegisterObjectMethod("ParticleEmitter", "void SetScaled(bool)", AS_METHODPR(ParticleEmitter, SetScaled, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter", "void set_scaled(bool)", AS_METHODPR(ParticleEmitter, SetScaled, (bool), void), AS_CALL_THISCALL);
    // void ParticleEmitter::SetSerializeParticles(bool enable) | File: ../Graphics/ParticleEmitter.h
    engine->RegisterObjectMethod("ParticleEmitter", "void SetSerializeParticles(bool)", AS_METHODPR(ParticleEmitter, SetSerializeParticles, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter", "void set_serializeParticles(bool)", AS_METHODPR(ParticleEmitter, SetSerializeParticles, (bool), void), AS_CALL_THISCALL);
    // void Drawable::SetShadowDistance(float distance) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("ParticleEmitter", "void SetShadowDistance(float)", AS_METHODPR(ParticleEmitter, SetShadowDistance, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter", "void set_shadowDistance(float)", AS_METHODPR(ParticleEmitter, SetShadowDistance, (float), void), AS_CALL_THISCALL);
    // void Drawable::SetShadowMask(unsigned mask) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("ParticleEmitter", "void SetShadowMask(uint)", AS_METHODPR(ParticleEmitter, SetShadowMask, (unsigned), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter", "void set_shadowMask(uint)", AS_METHODPR(ParticleEmitter, SetShadowMask, (unsigned), void), AS_CALL_THISCALL);
    // void BillboardSet::SetSorted(bool enable) | File: ../Graphics/BillboardSet.h
    engine->RegisterObjectMethod("ParticleEmitter", "void SetSorted(bool)", AS_METHODPR(ParticleEmitter, SetSorted, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter", "void set_sorted(bool)", AS_METHODPR(ParticleEmitter, SetSorted, (bool), void), AS_CALL_THISCALL);
    // void Drawable::SetSortValue(float value) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("ParticleEmitter", "void SetSortValue(float)", AS_METHODPR(ParticleEmitter, SetSortValue, (float), void), AS_CALL_THISCALL);
    // void Serializable::SetTemporary(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ParticleEmitter", "void SetTemporary(bool)", AS_METHODPR(ParticleEmitter, SetTemporary, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter", "void set_temporary(bool)", AS_METHODPR(ParticleEmitter, SetTemporary, (bool), void), AS_CALL_THISCALL);
    // void Drawable::SetViewMask(unsigned mask) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("ParticleEmitter", "void SetViewMask(uint)", AS_METHODPR(ParticleEmitter, SetViewMask, (unsigned), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter", "void set_viewMask(uint)", AS_METHODPR(ParticleEmitter, SetViewMask, (unsigned), void), AS_CALL_THISCALL);
    // void Drawable::SetZone(Zone* zone, bool temporary=false) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("ParticleEmitter", "void SetZone(Zone@+, bool = false)", AS_METHODPR(ParticleEmitter, SetZone, (Zone*, bool), void), AS_CALL_THISCALL);
    // void Drawable::SetZoneMask(unsigned mask) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("ParticleEmitter", "void SetZoneMask(uint)", AS_METHODPR(ParticleEmitter, SetZoneMask, (unsigned), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter", "void set_zoneMask(uint)", AS_METHODPR(ParticleEmitter, SetZoneMask, (unsigned), void), AS_CALL_THISCALL);
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod("ParticleEmitter", "void UnsubscribeFromAllEvents()", AS_METHODPR(ParticleEmitter, UnsubscribeFromAllEvents, (), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ParticleEmitter", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", AS_FUNCTION_OBJFIRST(ParticleEmitter_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), AS_CALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ParticleEmitter", "void UnsubscribeFromEvent(StringHash)", AS_METHODPR(ParticleEmitter, UnsubscribeFromEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ParticleEmitter", "void UnsubscribeFromEvent(Object@+, StringHash)", AS_METHODPR(ParticleEmitter, UnsubscribeFromEvent, (Object*, StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ParticleEmitter", "void UnsubscribeFromEvents(Object@+)", AS_METHODPR(ParticleEmitter, UnsubscribeFromEvents, (Object*), void), AS_CALL_THISCALL);
    // void ParticleEmitter::Update(const FrameInfo& frame) override | File: ../Graphics/ParticleEmitter.h
    engine->RegisterObjectMethod("ParticleEmitter", "void Update(const FrameInfo&in)", AS_METHODPR(ParticleEmitter, Update, (const FrameInfo&), void), AS_CALL_THISCALL);
    // void BillboardSet::UpdateBatches(const FrameInfo& frame) override | File: ../Graphics/BillboardSet.h
    engine->RegisterObjectMethod("ParticleEmitter", "void UpdateBatches(const FrameInfo&in)", AS_METHODPR(ParticleEmitter, UpdateBatches, (const FrameInfo&), void), AS_CALL_THISCALL);
    // void BillboardSet::UpdateGeometry(const FrameInfo& frame) override | File: ../Graphics/BillboardSet.h
    engine->RegisterObjectMethod("ParticleEmitter", "void UpdateGeometry(const FrameInfo&in)", AS_METHODPR(ParticleEmitter, UpdateGeometry, (const FrameInfo&), void), AS_CALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("ParticleEmitter", "int WeakRefs() const", AS_METHODPR(ParticleEmitter, WeakRefs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter", "int get_weakRefs() const", AS_METHODPR(ParticleEmitter, WeakRefs, () const, int), AS_CALL_THISCALL);
    // void Serializable::WriteDeltaUpdate(Serializer& dest, const DirtyBits& attributeBits, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ParticleEmitter", "void WriteDeltaUpdate(Serializer&, const DirtyBits&in, uint8)", AS_METHODPR(ParticleEmitter, WriteDeltaUpdate, (Serializer&, const DirtyBits&, unsigned char), void), AS_CALL_THISCALL);
    // void Serializable::WriteInitialDeltaUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ParticleEmitter", "void WriteInitialDeltaUpdate(Serializer&, uint8)", AS_METHODPR(ParticleEmitter, WriteInitialDeltaUpdate, (Serializer&, unsigned char), void), AS_CALL_THISCALL);
    // void Serializable::WriteLatestDataUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ParticleEmitter", "void WriteLatestDataUpdate(Serializer&, uint8)", AS_METHODPR(ParticleEmitter, WriteLatestDataUpdate, (Serializer&, unsigned char), void), AS_CALL_THISCALL);
#ifdef REGISTER_MANUAL_PART_BillboardSet
    REGISTER_MANUAL_PART_BillboardSet(ParticleEmitter, "ParticleEmitter")
#endif
#ifdef REGISTER_MANUAL_PART_Drawable
    REGISTER_MANUAL_PART_Drawable(ParticleEmitter, "ParticleEmitter")
#endif
#ifdef REGISTER_MANUAL_PART_Component
    REGISTER_MANUAL_PART_Component(ParticleEmitter, "ParticleEmitter")
#endif
#ifdef REGISTER_MANUAL_PART_Animatable
    REGISTER_MANUAL_PART_Animatable(ParticleEmitter, "ParticleEmitter")
#endif
#ifdef REGISTER_MANUAL_PART_Serializable
    REGISTER_MANUAL_PART_Serializable(ParticleEmitter, "ParticleEmitter")
#endif
#ifdef REGISTER_MANUAL_PART_Object
    REGISTER_MANUAL_PART_Object(ParticleEmitter, "ParticleEmitter")
#endif
#ifdef REGISTER_MANUAL_PART_RefCounted
    REGISTER_MANUAL_PART_RefCounted(ParticleEmitter, "ParticleEmitter")
#endif
#ifdef REGISTER_MANUAL_PART_ParticleEmitter
    REGISTER_MANUAL_PART_ParticleEmitter(ParticleEmitter, "ParticleEmitter")
#endif
    RegisterSubclass<BillboardSet, ParticleEmitter>(engine, "BillboardSet", "ParticleEmitter");
    RegisterSubclass<Drawable, ParticleEmitter>(engine, "Drawable", "ParticleEmitter");
    RegisterSubclass<Component, ParticleEmitter>(engine, "Component", "ParticleEmitter");
    RegisterSubclass<Animatable, ParticleEmitter>(engine, "Animatable", "ParticleEmitter");
    RegisterSubclass<Serializable, ParticleEmitter>(engine, "Serializable", "ParticleEmitter");
    RegisterSubclass<Object, ParticleEmitter>(engine, "Object", "ParticleEmitter");
    RegisterSubclass<RefCounted, ParticleEmitter>(engine, "RefCounted", "ParticleEmitter");

#ifdef URHO3D_URHO2D
    // void Drawable::AddLight(Light* light) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "void AddLight(Light@+)", AS_METHODPR(ParticleEmitter2D, AddLight, (Light*), void), AS_CALL_THISCALL);
    // void RefCounted::AddRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("ParticleEmitter2D", asBEHAVE_ADDREF, "void f()", AS_METHODPR(ParticleEmitter2D, AddRef, (), void), AS_CALL_THISCALL);
    // void Component::AddReplicationState(ComponentReplicationState* state) | File: ../Scene/Component.h
    // Error: type "ComponentReplicationState*" can not automatically bind
    // void Drawable::AddVertexLight(Light* light) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "void AddVertexLight(Light@+)", AS_METHODPR(ParticleEmitter2D, AddVertexLight, (Light*), void), AS_CALL_THISCALL);
    // void Serializable::AllocateNetworkState() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "void AllocateNetworkState()", AS_METHODPR(ParticleEmitter2D, AllocateNetworkState, (), void), AS_CALL_THISCALL);
    // virtual void Serializable::ApplyAttributes() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "void ApplyAttributes()", AS_METHODPR(ParticleEmitter2D, ApplyAttributes, (), void), AS_CALL_THISCALL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // void Component::CleanupConnection(Connection* connection) | File: ../Scene/Component.h
    // Not registered because have @manualbind mark
    // void Drawable::DrawDebugGeometry(DebugRenderer* debug, bool depthTest) override | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "void DrawDebugGeometry(DebugRenderer@+, bool)", AS_METHODPR(ParticleEmitter2D, DrawDebugGeometry, (DebugRenderer*, bool), void), AS_CALL_THISCALL);
    // virtual bool Drawable::DrawOcclusion(OcclusionBuffer* buffer) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "bool DrawOcclusion(OcclusionBuffer@+)", AS_METHODPR(ParticleEmitter2D, DrawOcclusion, (OcclusionBuffer*), bool), AS_CALL_THISCALL);
    // bool Animatable::GetAnimationEnabled() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "bool GetAnimationEnabled() const", AS_METHODPR(ParticleEmitter2D, GetAnimationEnabled, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter2D", "bool get_animationEnabled() const", AS_METHODPR(ParticleEmitter2D, GetAnimationEnabled, () const, bool), AS_CALL_THISCALL);
    // Variant Serializable::GetAttribute(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "Variant GetAttribute(uint) const", AS_METHODPR(ParticleEmitter2D, GetAttribute, (unsigned) const, Variant), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter2D", "Variant get_attributes(uint) const", AS_METHODPR(ParticleEmitter2D, GetAttribute, (unsigned) const, Variant), AS_CALL_THISCALL);
    // Variant Serializable::GetAttribute(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "Variant GetAttribute(const String&in) const", AS_METHODPR(ParticleEmitter2D, GetAttribute, (const String&) const, Variant), AS_CALL_THISCALL);
    // ValueAnimation* Animatable::GetAttributeAnimation(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "ValueAnimation@+ GetAttributeAnimation(const String&in) const", AS_METHODPR(ParticleEmitter2D, GetAttributeAnimation, (const String&) const, ValueAnimation*), AS_CALL_THISCALL);
    // float Animatable::GetAttributeAnimationSpeed(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "float GetAttributeAnimationSpeed(const String&in) const", AS_METHODPR(ParticleEmitter2D, GetAttributeAnimationSpeed, (const String&) const, float), AS_CALL_THISCALL);
    // float Animatable::GetAttributeAnimationTime(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "float GetAttributeAnimationTime(const String&in) const", AS_METHODPR(ParticleEmitter2D, GetAttributeAnimationTime, (const String&) const, float), AS_CALL_THISCALL);
    // WrapMode Animatable::GetAttributeAnimationWrapMode(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "WrapMode GetAttributeAnimationWrapMode(const String&in) const", AS_METHODPR(ParticleEmitter2D, GetAttributeAnimationWrapMode, (const String&) const, WrapMode), AS_CALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "Variant GetAttributeDefault(uint) const", AS_METHODPR(ParticleEmitter2D, GetAttributeDefault, (unsigned) const, Variant), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter2D", "Variant get_attributeDefaults(uint) const", AS_METHODPR(ParticleEmitter2D, GetAttributeDefault, (unsigned) const, Variant), AS_CALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "Variant GetAttributeDefault(const String&in) const", AS_METHODPR(ParticleEmitter2D, GetAttributeDefault, (const String&) const, Variant), AS_CALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // const Vector<SourceBatch>& Drawable::GetBatches() const | File: ../Graphics/Drawable.h
    // Error: type "const Vector<SourceBatch>&" can not automatically bind
    // BlendMode ParticleEmitter2D::GetBlendMode() const | File: ../Urho2D/ParticleEmitter2D.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "BlendMode GetBlendMode() const", AS_METHODPR(ParticleEmitter2D, GetBlendMode, () const, BlendMode), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter2D", "BlendMode get_blendMode() const", AS_METHODPR(ParticleEmitter2D, GetBlendMode, () const, BlendMode), AS_CALL_THISCALL);
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "bool GetBlockEvents() const", AS_METHODPR(ParticleEmitter2D, GetBlockEvents, () const, bool), AS_CALL_THISCALL);
    // const BoundingBox& Drawable::GetBoundingBox() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "const BoundingBox& GetBoundingBox() const", AS_METHODPR(ParticleEmitter2D, GetBoundingBox, () const, const BoundingBox&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter2D", "const BoundingBox& get_boundingBox() const", AS_METHODPR(ParticleEmitter2D, GetBoundingBox, () const, const BoundingBox&), AS_CALL_THISCALL);
    // bool Drawable::GetCastShadows() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "bool GetCastShadows() const", AS_METHODPR(ParticleEmitter2D, GetCastShadows, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter2D", "bool get_castShadows() const", AS_METHODPR(ParticleEmitter2D, GetCastShadows, () const, bool), AS_CALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "const String& GetCategory() const", AS_METHODPR(ParticleEmitter2D, GetCategory, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter2D", "const String& get_category() const", AS_METHODPR(ParticleEmitter2D, GetCategory, () const, const String&), AS_CALL_THISCALL);
    // Component* Component::GetComponent(StringHash type) const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "Component@+ GetComponent(StringHash) const", AS_METHODPR(ParticleEmitter2D, GetComponent, (StringHash) const, Component*), AS_CALL_THISCALL);
    // template<class T> T* Component::GetComponent() const | File: ../Scene/Component.h
    // Not registered because template
    // void Component::GetComponents(PODVector<Component*>& dest, StringHash type) const | File: ../Scene/Component.h
    // Error: type "PODVector<Component*>&" can not automatically bind
    // template<class T> void Component::GetComponents(PODVector<T*>& dest) const | File: ../Scene/Component.h
    // Not registered because template
    // Context* Object::GetContext() const | File: ../Core/Object.h
    // Error: type "Context*" can used only as function parameter
    // virtual void Component::GetDependencyNodes(PODVector<Node*>& dest) | File: ../Scene/Component.h
    // Error: type "PODVector<Node*>&" can not automatically bind
    // float Drawable::GetDistance() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "float GetDistance() const", AS_METHODPR(ParticleEmitter2D, GetDistance, () const, float), AS_CALL_THISCALL);
    // unsigned char Drawable::GetDrawableFlags() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "uint8 GetDrawableFlags() const", AS_METHODPR(ParticleEmitter2D, GetDrawableFlags, () const, unsigned char), AS_CALL_THISCALL);
    // float Drawable::GetDrawDistance() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "float GetDrawDistance() const", AS_METHODPR(ParticleEmitter2D, GetDrawDistance, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter2D", "float get_drawDistance() const", AS_METHODPR(ParticleEmitter2D, GetDrawDistance, () const, float), AS_CALL_THISCALL);
    // ParticleEffect2D* ParticleEmitter2D::GetEffect() const | File: ../Urho2D/ParticleEmitter2D.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "ParticleEffect2D@+ GetEffect() const", AS_METHODPR(ParticleEmitter2D, GetEffect, () const, ParticleEffect2D*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter2D", "ParticleEffect2D@+ get_effect() const", AS_METHODPR(ParticleEmitter2D, GetEffect, () const, ParticleEffect2D*), AS_CALL_THISCALL);
    // VariantMap& Object::GetEventDataMap() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "VariantMap& GetEventDataMap() const", AS_METHODPR(ParticleEmitter2D, GetEventDataMap, () const, VariantMap&), AS_CALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "Object@+ GetEventSender() const", AS_METHODPR(ParticleEmitter2D, GetEventSender, () const, Object*), AS_CALL_THISCALL);
    // Light* Drawable::GetFirstLight() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "Light@+ GetFirstLight() const", AS_METHODPR(ParticleEmitter2D, GetFirstLight, () const, Light*), AS_CALL_THISCALL);
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "const Variant& GetGlobalVar(StringHash) const", AS_METHODPR(ParticleEmitter2D, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter2D", "const Variant& get_globalVar(StringHash) const", AS_METHODPR(ParticleEmitter2D, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "const VariantMap& GetGlobalVars() const", AS_METHODPR(ParticleEmitter2D, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter2D", "const VariantMap& get_globalVars() const", AS_METHODPR(ParticleEmitter2D, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    // unsigned Component::GetID() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "uint GetID() const", AS_METHODPR(ParticleEmitter2D, GetID, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter2D", "uint get_id() const", AS_METHODPR(ParticleEmitter2D, GetID, () const, unsigned), AS_CALL_THISCALL);
    // bool Serializable::GetInterceptNetworkUpdate(const String& attributeName) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "bool GetInterceptNetworkUpdate(const String&in) const", AS_METHODPR(ParticleEmitter2D, GetInterceptNetworkUpdate, (const String&) const, bool), AS_CALL_THISCALL);
    // int Drawable2D::GetLayer() const | File: ../Urho2D/Drawable2D.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "int GetLayer() const", AS_METHODPR(ParticleEmitter2D, GetLayer, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter2D", "int get_layer() const", AS_METHODPR(ParticleEmitter2D, GetLayer, () const, int), AS_CALL_THISCALL);
    // unsigned Drawable::GetLightMask() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "uint GetLightMask() const", AS_METHODPR(ParticleEmitter2D, GetLightMask, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter2D", "uint get_lightMask() const", AS_METHODPR(ParticleEmitter2D, GetLightMask, () const, unsigned), AS_CALL_THISCALL);
    // const PODVector<Light*>& Drawable::GetLights() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "Array<Light@>@ GetLights() const", AS_FUNCTION_OBJFIRST(ParticleEmitter2D_GetLights_void), AS_CALL_CDECL_OBJFIRST);
    // float Drawable::GetLodBias() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "float GetLodBias() const", AS_METHODPR(ParticleEmitter2D, GetLodBias, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter2D", "float get_lodBias() const", AS_METHODPR(ParticleEmitter2D, GetLodBias, () const, float), AS_CALL_THISCALL);
    // float Drawable::GetLodDistance() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "float GetLodDistance() const", AS_METHODPR(ParticleEmitter2D, GetLodDistance, () const, float), AS_CALL_THISCALL);
    // virtual Geometry* Drawable::GetLodGeometry(unsigned batchIndex, unsigned level) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "Geometry@+ GetLodGeometry(uint, uint)", AS_METHODPR(ParticleEmitter2D, GetLodGeometry, (unsigned, unsigned), Geometry*), AS_CALL_THISCALL);
    // unsigned Drawable::GetMaxLights() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "uint GetMaxLights() const", AS_METHODPR(ParticleEmitter2D, GetMaxLights, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter2D", "uint get_maxLights() const", AS_METHODPR(ParticleEmitter2D, GetMaxLights, () const, unsigned), AS_CALL_THISCALL);
    // unsigned ParticleEmitter2D::GetMaxParticles() const | File: ../Urho2D/ParticleEmitter2D.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "uint GetMaxParticles() const", AS_METHODPR(ParticleEmitter2D, GetMaxParticles, () const, unsigned), AS_CALL_THISCALL);
    // float Drawable::GetMaxZ() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "float GetMaxZ() const", AS_METHODPR(ParticleEmitter2D, GetMaxZ, () const, float), AS_CALL_THISCALL);
    // float Drawable::GetMinZ() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "float GetMinZ() const", AS_METHODPR(ParticleEmitter2D, GetMinZ, () const, float), AS_CALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetNetworkAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // NetworkState* Serializable::GetNetworkState() const | File: ../Scene/Serializable.h
    // Error: type "NetworkState*" can not automatically bind
    // Node* Component::GetNode() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "Node@+ GetNode() const", AS_METHODPR(ParticleEmitter2D, GetNode, () const, Node*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter2D", "Node@+ get_node() const", AS_METHODPR(ParticleEmitter2D, GetNode, () const, Node*), AS_CALL_THISCALL);
    // unsigned Serializable::GetNumAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "uint GetNumAttributes() const", AS_METHODPR(ParticleEmitter2D, GetNumAttributes, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter2D", "uint get_numAttributes() const", AS_METHODPR(ParticleEmitter2D, GetNumAttributes, () const, unsigned), AS_CALL_THISCALL);
    // unsigned Serializable::GetNumNetworkAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "uint GetNumNetworkAttributes() const", AS_METHODPR(ParticleEmitter2D, GetNumNetworkAttributes, () const, unsigned), AS_CALL_THISCALL);
    // virtual unsigned Drawable::GetNumOccluderTriangles() | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "uint GetNumOccluderTriangles()", AS_METHODPR(ParticleEmitter2D, GetNumOccluderTriangles, (), unsigned), AS_CALL_THISCALL);
    // ObjectAnimation* Animatable::GetObjectAnimation() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "ObjectAnimation@+ GetObjectAnimation() const", AS_METHODPR(ParticleEmitter2D, GetObjectAnimation, () const, ObjectAnimation*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter2D", "ObjectAnimation@+ get_objectAnimation() const", AS_METHODPR(ParticleEmitter2D, GetObjectAnimation, () const, ObjectAnimation*), AS_CALL_THISCALL);
    // ResourceRef Animatable::GetObjectAnimationAttr() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "ResourceRef GetObjectAnimationAttr() const", AS_METHODPR(ParticleEmitter2D, GetObjectAnimationAttr, () const, ResourceRef), AS_CALL_THISCALL);
    // Octant* Drawable::GetOctant() const | File: ../Graphics/Drawable.h
    // Error: type "Octant" can not automatically bind bacause have @nobind mark
    // int Drawable2D::GetOrderInLayer() const | File: ../Urho2D/Drawable2D.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "int GetOrderInLayer() const", AS_METHODPR(ParticleEmitter2D, GetOrderInLayer, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter2D", "int get_orderInLayer() const", AS_METHODPR(ParticleEmitter2D, GetOrderInLayer, () const, int), AS_CALL_THISCALL);
    // ResourceRef ParticleEmitter2D::GetParticleEffectAttr() const | File: ../Urho2D/ParticleEmitter2D.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "ResourceRef GetParticleEffectAttr() const", AS_METHODPR(ParticleEmitter2D, GetParticleEffectAttr, () const, ResourceRef), AS_CALL_THISCALL);
    // Scene* Component::GetScene() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "Scene@+ GetScene() const", AS_METHODPR(ParticleEmitter2D, GetScene, () const, Scene*), AS_CALL_THISCALL);
    // float Drawable::GetShadowDistance() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "float GetShadowDistance() const", AS_METHODPR(ParticleEmitter2D, GetShadowDistance, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter2D", "float get_shadowDistance() const", AS_METHODPR(ParticleEmitter2D, GetShadowDistance, () const, float), AS_CALL_THISCALL);
    // unsigned Drawable::GetShadowMask() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "uint GetShadowMask() const", AS_METHODPR(ParticleEmitter2D, GetShadowMask, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter2D", "uint get_shadowMask() const", AS_METHODPR(ParticleEmitter2D, GetShadowMask, () const, unsigned), AS_CALL_THISCALL);
    // float Drawable::GetSortValue() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "float GetSortValue() const", AS_METHODPR(ParticleEmitter2D, GetSortValue, () const, float), AS_CALL_THISCALL);
    // const Vector<SourceBatch2D>& Drawable2D::GetSourceBatches() | File: ../Urho2D/Drawable2D.h
    // Error: type "const Vector<SourceBatch2D>&" can not automatically bind
    // Sprite2D* ParticleEmitter2D::GetSprite() const | File: ../Urho2D/ParticleEmitter2D.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "Sprite2D@+ GetSprite() const", AS_METHODPR(ParticleEmitter2D, GetSprite, () const, Sprite2D*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter2D", "Sprite2D@+ get_sprite() const", AS_METHODPR(ParticleEmitter2D, GetSprite, () const, Sprite2D*), AS_CALL_THISCALL);
    // ResourceRef ParticleEmitter2D::GetSpriteAttr() const | File: ../Urho2D/ParticleEmitter2D.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "ResourceRef GetSpriteAttr() const", AS_METHODPR(ParticleEmitter2D, GetSpriteAttr, () const, ResourceRef), AS_CALL_THISCALL);
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "Object@+ GetSubsystem(StringHash) const", AS_METHODPR(ParticleEmitter2D, GetSubsystem, (StringHash) const, Object*), AS_CALL_THISCALL);
    // template<class T> T* Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "StringHash GetType() const", AS_METHODPR(ParticleEmitter2D, GetType, () const, StringHash), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter2D", "StringHash get_type() const", AS_METHODPR(ParticleEmitter2D, GetType, () const, StringHash), AS_CALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "const String& GetTypeName() const", AS_METHODPR(ParticleEmitter2D, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter2D", "const String& get_typeName() const", AS_METHODPR(ParticleEmitter2D, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    // virtual UpdateGeometryType Drawable::GetUpdateGeometryType() | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "UpdateGeometryType GetUpdateGeometryType()", AS_METHODPR(ParticleEmitter2D, GetUpdateGeometryType, (), UpdateGeometryType), AS_CALL_THISCALL);
    // const PODVector<Light*>& Drawable::GetVertexLights() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "Array<Light@>@ GetVertexLights() const", AS_FUNCTION_OBJFIRST(ParticleEmitter2D_GetVertexLights_void), AS_CALL_CDECL_OBJFIRST);
    // unsigned Drawable::GetViewMask() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "uint GetViewMask() const", AS_METHODPR(ParticleEmitter2D, GetViewMask, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter2D", "uint get_viewMask() const", AS_METHODPR(ParticleEmitter2D, GetViewMask, () const, unsigned), AS_CALL_THISCALL);
    // const BoundingBox& Drawable::GetWorldBoundingBox() | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "const BoundingBox& GetWorldBoundingBox()", AS_METHODPR(ParticleEmitter2D, GetWorldBoundingBox, (), const BoundingBox&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter2D", "const BoundingBox& get_worldBoundingBox()", AS_METHODPR(ParticleEmitter2D, GetWorldBoundingBox, (), const BoundingBox&), AS_CALL_THISCALL);
    // Zone* Drawable::GetZone() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "Zone@+ GetZone() const", AS_METHODPR(ParticleEmitter2D, GetZone, () const, Zone*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter2D", "Zone@+ get_zone() const", AS_METHODPR(ParticleEmitter2D, GetZone, () const, Zone*), AS_CALL_THISCALL);
    // unsigned Drawable::GetZoneMask() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "uint GetZoneMask() const", AS_METHODPR(ParticleEmitter2D, GetZoneMask, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter2D", "uint get_zoneMask() const", AS_METHODPR(ParticleEmitter2D, GetZoneMask, () const, unsigned), AS_CALL_THISCALL);
    // bool Drawable::HasBasePass(unsigned batchIndex) const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "bool HasBasePass(uint) const", AS_METHODPR(ParticleEmitter2D, HasBasePass, (unsigned) const, bool), AS_CALL_THISCALL);
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "bool HasEventHandlers() const", AS_METHODPR(ParticleEmitter2D, HasEventHandlers, () const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "bool HasSubscribedToEvent(StringHash) const", AS_METHODPR(ParticleEmitter2D, HasSubscribedToEvent, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "bool HasSubscribedToEvent(Object@+, StringHash) const", AS_METHODPR(ParticleEmitter2D, HasSubscribedToEvent, (Object*, StringHash) const, bool), AS_CALL_THISCALL);
    // bool ParticleEmitter2D::IsEmitting() const | File: ../Urho2D/ParticleEmitter2D.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "bool IsEmitting() const", AS_METHODPR(ParticleEmitter2D, IsEmitting, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter2D", "bool get_emitting() const", AS_METHODPR(ParticleEmitter2D, IsEmitting, () const, bool), AS_CALL_THISCALL);
    // bool Component::IsEnabled() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "bool IsEnabled() const", AS_METHODPR(ParticleEmitter2D, IsEnabled, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter2D", "bool get_enabled() const", AS_METHODPR(ParticleEmitter2D, IsEnabled, () const, bool), AS_CALL_THISCALL);
    // bool Component::IsEnabledEffective() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "bool IsEnabledEffective() const", AS_METHODPR(ParticleEmitter2D, IsEnabledEffective, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter2D", "bool get_enabledEffective() const", AS_METHODPR(ParticleEmitter2D, IsEnabledEffective, () const, bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "bool IsInstanceOf(StringHash) const", AS_METHODPR(ParticleEmitter2D, IsInstanceOf, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // bool Drawable::IsInView() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "bool IsInView() const", AS_METHODPR(ParticleEmitter2D, IsInView, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter2D", "bool get_inView() const", AS_METHODPR(ParticleEmitter2D, IsInView, () const, bool), AS_CALL_THISCALL);
    // bool Drawable::IsInView(Camera* camera) const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "bool IsInView(Camera@+) const", AS_METHODPR(ParticleEmitter2D, IsInView, (Camera*) const, bool), AS_CALL_THISCALL);
    // bool Drawable::IsInView(const FrameInfo& frame, bool anyCamera=false) const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "bool IsInView(const FrameInfo&in, bool = false) const", AS_METHODPR(ParticleEmitter2D, IsInView, (const FrameInfo&, bool) const, bool), AS_CALL_THISCALL);
    // bool Drawable::IsOccludee() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "bool IsOccludee() const", AS_METHODPR(ParticleEmitter2D, IsOccludee, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter2D", "bool get_occludee() const", AS_METHODPR(ParticleEmitter2D, IsOccludee, () const, bool), AS_CALL_THISCALL);
    // bool Drawable::IsOccluder() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "bool IsOccluder() const", AS_METHODPR(ParticleEmitter2D, IsOccluder, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter2D", "bool get_occluder() const", AS_METHODPR(ParticleEmitter2D, IsOccluder, () const, bool), AS_CALL_THISCALL);
    // bool Component::IsReplicated() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "bool IsReplicated() const", AS_METHODPR(ParticleEmitter2D, IsReplicated, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter2D", "bool get_replicated() const", AS_METHODPR(ParticleEmitter2D, IsReplicated, () const, bool), AS_CALL_THISCALL);
    // bool Serializable::IsTemporary() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "bool IsTemporary() const", AS_METHODPR(ParticleEmitter2D, IsTemporary, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter2D", "bool get_temporary() const", AS_METHODPR(ParticleEmitter2D, IsTemporary, () const, bool), AS_CALL_THISCALL);
    // bool Drawable::IsZoneDirty() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "bool IsZoneDirty() const", AS_METHODPR(ParticleEmitter2D, IsZoneDirty, () const, bool), AS_CALL_THISCALL);
    // void Drawable::LimitLights() | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "void LimitLights()", AS_METHODPR(ParticleEmitter2D, LimitLights, (), void), AS_CALL_THISCALL);
    // void Drawable::LimitVertexLights(bool removeConvertedLights) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "void LimitVertexLights(bool)", AS_METHODPR(ParticleEmitter2D, LimitVertexLights, (bool), void), AS_CALL_THISCALL);
    // virtual bool Serializable::Load(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "bool Load(Deserializer&)", AS_METHODPR(ParticleEmitter2D, Load, (Deserializer&), bool), AS_CALL_THISCALL);
    // bool Animatable::LoadJSON(const JSONValue& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "bool LoadJSON(const JSONValue&in)", AS_METHODPR(ParticleEmitter2D, LoadJSON, (const JSONValue&), bool), AS_CALL_THISCALL);
    // bool Animatable::LoadXML(const XMLElement& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "bool LoadXML(const XMLElement&in)", AS_METHODPR(ParticleEmitter2D, LoadXML, (const XMLElement&), bool), AS_CALL_THISCALL);
    // void Drawable::MarkForUpdate() | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "void MarkForUpdate()", AS_METHODPR(ParticleEmitter2D, MarkForUpdate, (), void), AS_CALL_THISCALL);
    // void Drawable::MarkInView(const FrameInfo& frame) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "void MarkInView(const FrameInfo&in)", AS_METHODPR(ParticleEmitter2D, MarkInView, (const FrameInfo&), void), AS_CALL_THISCALL);
    // void Drawable::MarkInView(unsigned frameNumber) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "void MarkInView(uint)", AS_METHODPR(ParticleEmitter2D, MarkInView, (unsigned), void), AS_CALL_THISCALL);
    // void Component::MarkNetworkUpdate() override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "void MarkNetworkUpdate()", AS_METHODPR(ParticleEmitter2D, MarkNetworkUpdate, (), void), AS_CALL_THISCALL);
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "void OnEvent(Object@+, StringHash, VariantMap&)", AS_METHODPR(ParticleEmitter2D, OnEvent, (Object*, StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // virtual void Serializable::OnGetAttribute(const AttributeInfo& attr, Variant& dest) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "void OnGetAttribute(const AttributeInfo&in, Variant&) const", AS_METHODPR(ParticleEmitter2D, OnGetAttribute, (const AttributeInfo&, Variant&) const, void), AS_CALL_THISCALL);
    // virtual void Serializable::OnSetAttribute(const AttributeInfo& attr, const Variant& src) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "void OnSetAttribute(const AttributeInfo&in, const Variant&in)", AS_METHODPR(ParticleEmitter2D, OnSetAttribute, (const AttributeInfo&, const Variant&), void), AS_CALL_THISCALL);
    // void ParticleEmitter2D::OnSetEnabled() override | File: ../Urho2D/ParticleEmitter2D.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "void OnSetEnabled()", AS_METHODPR(ParticleEmitter2D, OnSetEnabled, (), void), AS_CALL_THISCALL);
    // explicit ParticleEmitter2D::ParticleEmitter2D(Context* context) | File: ../Urho2D/ParticleEmitter2D.h
    engine->RegisterObjectBehaviour("ParticleEmitter2D", asBEHAVE_FACTORY, "ParticleEmitter2D@+ f()", AS_FUNCTION(ParticleEmitter2D_ParticleEmitter2D_Context), AS_CALL_CDECL);
    // void Component::PrepareNetworkUpdate() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "void PrepareNetworkUpdate()", AS_METHODPR(ParticleEmitter2D, PrepareNetworkUpdate, (), void), AS_CALL_THISCALL);
    // virtual void Drawable::ProcessRayQuery(const RayOctreeQuery& query, PODVector<RayQueryResult>& results) | File: ../Graphics/Drawable.h
    // Error: type "RayOctreeQuery" can not automatically bind bacause have @nobind mark
    // bool Serializable::ReadDeltaUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "bool ReadDeltaUpdate(Deserializer&)", AS_METHODPR(ParticleEmitter2D, ReadDeltaUpdate, (Deserializer&), bool), AS_CALL_THISCALL);
    // bool Serializable::ReadLatestDataUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "bool ReadLatestDataUpdate(Deserializer&)", AS_METHODPR(ParticleEmitter2D, ReadLatestDataUpdate, (Deserializer&), bool), AS_CALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "int Refs() const", AS_METHODPR(ParticleEmitter2D, Refs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter2D", "int get_refs() const", AS_METHODPR(ParticleEmitter2D, Refs, () const, int), AS_CALL_THISCALL);
    // static void ParticleEmitter2D::RegisterObject(Context* context) | File: ../Urho2D/ParticleEmitter2D.h
    // Not registered because have @nobind mark
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("ParticleEmitter2D", asBEHAVE_RELEASE, "void f()", AS_METHODPR(ParticleEmitter2D, ReleaseRef, (), void), AS_CALL_THISCALL);
    // void Component::Remove() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "void Remove()", AS_METHODPR(ParticleEmitter2D, Remove, (), void), AS_CALL_THISCALL);
    // void Animatable::RemoveAttributeAnimation(const String& name) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "void RemoveAttributeAnimation(const String&in)", AS_METHODPR(ParticleEmitter2D, RemoveAttributeAnimation, (const String&), void), AS_CALL_THISCALL);
    // void Serializable::RemoveInstanceDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "void RemoveInstanceDefault()", AS_METHODPR(ParticleEmitter2D, RemoveInstanceDefault, (), void), AS_CALL_THISCALL);
    // void Animatable::RemoveObjectAnimation() | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "void RemoveObjectAnimation()", AS_METHODPR(ParticleEmitter2D, RemoveObjectAnimation, (), void), AS_CALL_THISCALL);
    // void Serializable::ResetToDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "void ResetToDefault()", AS_METHODPR(ParticleEmitter2D, ResetToDefault, (), void), AS_CALL_THISCALL);
    // bool Component::Save(Serializer& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "bool Save(Serializer&) const", AS_METHODPR(ParticleEmitter2D, Save, (Serializer&) const, bool), AS_CALL_THISCALL);
    // virtual bool Serializable::SaveDefaultAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "bool SaveDefaultAttributes() const", AS_METHODPR(ParticleEmitter2D, SaveDefaultAttributes, () const, bool), AS_CALL_THISCALL);
    // bool Component::SaveJSON(JSONValue& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "bool SaveJSON(JSONValue&) const", AS_METHODPR(ParticleEmitter2D, SaveJSON, (JSONValue&) const, bool), AS_CALL_THISCALL);
    // bool Component::SaveXML(XMLElement& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "bool SaveXML(XMLElement&) const", AS_METHODPR(ParticleEmitter2D, SaveXML, (XMLElement&) const, bool), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "void SendEvent(StringHash)", AS_METHODPR(ParticleEmitter2D, SendEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "void SendEvent(StringHash, VariantMap&)", AS_METHODPR(ParticleEmitter2D, SendEvent, (StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void Animatable::SetAnimationEnabled(bool enable) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "void SetAnimationEnabled(bool)", AS_METHODPR(ParticleEmitter2D, SetAnimationEnabled, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter2D", "void set_animationEnabled(bool)", AS_METHODPR(ParticleEmitter2D, SetAnimationEnabled, (bool), void), AS_CALL_THISCALL);
    // void Animatable::SetAnimationTime(float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "void SetAnimationTime(float)", AS_METHODPR(ParticleEmitter2D, SetAnimationTime, (float), void), AS_CALL_THISCALL);
    // bool Serializable::SetAttribute(unsigned index, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "bool SetAttribute(uint, const Variant&in)", AS_METHODPR(ParticleEmitter2D, SetAttribute, (unsigned, const Variant&), bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter2D", "bool set_attributes(uint, const Variant&in)", AS_METHODPR(ParticleEmitter2D, SetAttribute, (unsigned, const Variant&), bool), AS_CALL_THISCALL);
    // bool Serializable::SetAttribute(const String& name, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "bool SetAttribute(const String&in, const Variant&in)", AS_METHODPR(ParticleEmitter2D, SetAttribute, (const String&, const Variant&), bool), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimation(const String& name, ValueAnimation* attributeAnimation, WrapMode wrapMode=WM_LOOP, float speed=1.0f) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "void SetAttributeAnimation(const String&in, ValueAnimation@+, WrapMode = WM_LOOP, float = 1.0f)", AS_METHODPR(ParticleEmitter2D, SetAttributeAnimation, (const String&, ValueAnimation*, WrapMode, float), void), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimationSpeed(const String& name, float speed) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "void SetAttributeAnimationSpeed(const String&in, float)", AS_METHODPR(ParticleEmitter2D, SetAttributeAnimationSpeed, (const String&, float), void), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimationTime(const String& name, float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "void SetAttributeAnimationTime(const String&in, float)", AS_METHODPR(ParticleEmitter2D, SetAttributeAnimationTime, (const String&, float), void), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimationWrapMode(const String& name, WrapMode wrapMode) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "void SetAttributeAnimationWrapMode(const String&in, WrapMode)", AS_METHODPR(ParticleEmitter2D, SetAttributeAnimationWrapMode, (const String&, WrapMode), void), AS_CALL_THISCALL);
    // void Drawable::SetBasePass(unsigned batchIndex) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "void SetBasePass(uint)", AS_METHODPR(ParticleEmitter2D, SetBasePass, (unsigned), void), AS_CALL_THISCALL);
    // void ParticleEmitter2D::SetBlendMode(BlendMode blendMode) | File: ../Urho2D/ParticleEmitter2D.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "void SetBlendMode(BlendMode)", AS_METHODPR(ParticleEmitter2D, SetBlendMode, (BlendMode), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter2D", "void set_blendMode(BlendMode)", AS_METHODPR(ParticleEmitter2D, SetBlendMode, (BlendMode), void), AS_CALL_THISCALL);
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "void SetBlockEvents(bool)", AS_METHODPR(ParticleEmitter2D, SetBlockEvents, (bool), void), AS_CALL_THISCALL);
    // void Drawable::SetCastShadows(bool enable) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "void SetCastShadows(bool)", AS_METHODPR(ParticleEmitter2D, SetCastShadows, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter2D", "void set_castShadows(bool)", AS_METHODPR(ParticleEmitter2D, SetCastShadows, (bool), void), AS_CALL_THISCALL);
    // void Drawable::SetDrawDistance(float distance) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "void SetDrawDistance(float)", AS_METHODPR(ParticleEmitter2D, SetDrawDistance, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter2D", "void set_drawDistance(float)", AS_METHODPR(ParticleEmitter2D, SetDrawDistance, (float), void), AS_CALL_THISCALL);
    // void ParticleEmitter2D::SetEffect(ParticleEffect2D* effect) | File: ../Urho2D/ParticleEmitter2D.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "void SetEffect(ParticleEffect2D@+)", AS_METHODPR(ParticleEmitter2D, SetEffect, (ParticleEffect2D*), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter2D", "void set_effect(ParticleEffect2D@+)", AS_METHODPR(ParticleEmitter2D, SetEffect, (ParticleEffect2D*), void), AS_CALL_THISCALL);
    // void ParticleEmitter2D::SetEmitting(bool enable) | File: ../Urho2D/ParticleEmitter2D.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "void SetEmitting(bool)", AS_METHODPR(ParticleEmitter2D, SetEmitting, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter2D", "void set_emitting(bool)", AS_METHODPR(ParticleEmitter2D, SetEmitting, (bool), void), AS_CALL_THISCALL);
    // void Component::SetEnabled(bool enable) | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "void SetEnabled(bool)", AS_METHODPR(ParticleEmitter2D, SetEnabled, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter2D", "void set_enabled(bool)", AS_METHODPR(ParticleEmitter2D, SetEnabled, (bool), void), AS_CALL_THISCALL);
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "void SetGlobalVar(StringHash, const Variant&in)", AS_METHODPR(ParticleEmitter2D, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter2D", "void set_globalVar(StringHash, const Variant&in)", AS_METHODPR(ParticleEmitter2D, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    // void Serializable::SetInstanceDefault(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "void SetInstanceDefault(bool)", AS_METHODPR(ParticleEmitter2D, SetInstanceDefault, (bool), void), AS_CALL_THISCALL);
    // void Serializable::SetInterceptNetworkUpdate(const String& attributeName, bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "void SetInterceptNetworkUpdate(const String&in, bool)", AS_METHODPR(ParticleEmitter2D, SetInterceptNetworkUpdate, (const String&, bool), void), AS_CALL_THISCALL);
    // void Drawable2D::SetLayer(int layer) | File: ../Urho2D/Drawable2D.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "void SetLayer(int)", AS_METHODPR(ParticleEmitter2D, SetLayer, (int), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter2D", "void set_layer(int)", AS_METHODPR(ParticleEmitter2D, SetLayer, (int), void), AS_CALL_THISCALL);
    // void Drawable::SetLightMask(unsigned mask) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "void SetLightMask(uint)", AS_METHODPR(ParticleEmitter2D, SetLightMask, (unsigned), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter2D", "void set_lightMask(uint)", AS_METHODPR(ParticleEmitter2D, SetLightMask, (unsigned), void), AS_CALL_THISCALL);
    // void Drawable::SetLodBias(float bias) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "void SetLodBias(float)", AS_METHODPR(ParticleEmitter2D, SetLodBias, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter2D", "void set_lodBias(float)", AS_METHODPR(ParticleEmitter2D, SetLodBias, (float), void), AS_CALL_THISCALL);
    // void Drawable::SetMaxLights(unsigned num) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "void SetMaxLights(uint)", AS_METHODPR(ParticleEmitter2D, SetMaxLights, (unsigned), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter2D", "void set_maxLights(uint)", AS_METHODPR(ParticleEmitter2D, SetMaxLights, (unsigned), void), AS_CALL_THISCALL);
    // void ParticleEmitter2D::SetMaxParticles(unsigned maxParticles) | File: ../Urho2D/ParticleEmitter2D.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "void SetMaxParticles(uint)", AS_METHODPR(ParticleEmitter2D, SetMaxParticles, (unsigned), void), AS_CALL_THISCALL);
    // void Drawable::SetMinMaxZ(float minZ, float maxZ) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "void SetMinMaxZ(float, float)", AS_METHODPR(ParticleEmitter2D, SetMinMaxZ, (float, float), void), AS_CALL_THISCALL);
    // void Animatable::SetObjectAnimation(ObjectAnimation* objectAnimation) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "void SetObjectAnimation(ObjectAnimation@+)", AS_METHODPR(ParticleEmitter2D, SetObjectAnimation, (ObjectAnimation*), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter2D", "void set_objectAnimation(ObjectAnimation@+)", AS_METHODPR(ParticleEmitter2D, SetObjectAnimation, (ObjectAnimation*), void), AS_CALL_THISCALL);
    // void Animatable::SetObjectAnimationAttr(const ResourceRef& value) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "void SetObjectAnimationAttr(const ResourceRef&in)", AS_METHODPR(ParticleEmitter2D, SetObjectAnimationAttr, (const ResourceRef&), void), AS_CALL_THISCALL);
    // void Drawable::SetOccludee(bool enable) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "void SetOccludee(bool)", AS_METHODPR(ParticleEmitter2D, SetOccludee, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter2D", "void set_occludee(bool)", AS_METHODPR(ParticleEmitter2D, SetOccludee, (bool), void), AS_CALL_THISCALL);
    // void Drawable::SetOccluder(bool enable) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "void SetOccluder(bool)", AS_METHODPR(ParticleEmitter2D, SetOccluder, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter2D", "void set_occluder(bool)", AS_METHODPR(ParticleEmitter2D, SetOccluder, (bool), void), AS_CALL_THISCALL);
    // void Drawable2D::SetOrderInLayer(int orderInLayer) | File: ../Urho2D/Drawable2D.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "void SetOrderInLayer(int)", AS_METHODPR(ParticleEmitter2D, SetOrderInLayer, (int), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter2D", "void set_orderInLayer(int)", AS_METHODPR(ParticleEmitter2D, SetOrderInLayer, (int), void), AS_CALL_THISCALL);
    // void ParticleEmitter2D::SetParticleEffectAttr(const ResourceRef& value) | File: ../Urho2D/ParticleEmitter2D.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "void SetParticleEffectAttr(const ResourceRef&in)", AS_METHODPR(ParticleEmitter2D, SetParticleEffectAttr, (const ResourceRef&), void), AS_CALL_THISCALL);
    // void Drawable::SetShadowDistance(float distance) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "void SetShadowDistance(float)", AS_METHODPR(ParticleEmitter2D, SetShadowDistance, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter2D", "void set_shadowDistance(float)", AS_METHODPR(ParticleEmitter2D, SetShadowDistance, (float), void), AS_CALL_THISCALL);
    // void Drawable::SetShadowMask(unsigned mask) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "void SetShadowMask(uint)", AS_METHODPR(ParticleEmitter2D, SetShadowMask, (unsigned), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter2D", "void set_shadowMask(uint)", AS_METHODPR(ParticleEmitter2D, SetShadowMask, (unsigned), void), AS_CALL_THISCALL);
    // void Drawable::SetSortValue(float value) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "void SetSortValue(float)", AS_METHODPR(ParticleEmitter2D, SetSortValue, (float), void), AS_CALL_THISCALL);
    // void ParticleEmitter2D::SetSprite(Sprite2D* sprite) | File: ../Urho2D/ParticleEmitter2D.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "void SetSprite(Sprite2D@+)", AS_METHODPR(ParticleEmitter2D, SetSprite, (Sprite2D*), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter2D", "void set_sprite(Sprite2D@+)", AS_METHODPR(ParticleEmitter2D, SetSprite, (Sprite2D*), void), AS_CALL_THISCALL);
    // void ParticleEmitter2D::SetSpriteAttr(const ResourceRef& value) | File: ../Urho2D/ParticleEmitter2D.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "void SetSpriteAttr(const ResourceRef&in)", AS_METHODPR(ParticleEmitter2D, SetSpriteAttr, (const ResourceRef&), void), AS_CALL_THISCALL);
    // void Serializable::SetTemporary(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "void SetTemporary(bool)", AS_METHODPR(ParticleEmitter2D, SetTemporary, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter2D", "void set_temporary(bool)", AS_METHODPR(ParticleEmitter2D, SetTemporary, (bool), void), AS_CALL_THISCALL);
    // void Drawable::SetViewMask(unsigned mask) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "void SetViewMask(uint)", AS_METHODPR(ParticleEmitter2D, SetViewMask, (unsigned), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter2D", "void set_viewMask(uint)", AS_METHODPR(ParticleEmitter2D, SetViewMask, (unsigned), void), AS_CALL_THISCALL);
    // void Drawable::SetZone(Zone* zone, bool temporary=false) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "void SetZone(Zone@+, bool = false)", AS_METHODPR(ParticleEmitter2D, SetZone, (Zone*, bool), void), AS_CALL_THISCALL);
    // void Drawable::SetZoneMask(unsigned mask) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "void SetZoneMask(uint)", AS_METHODPR(ParticleEmitter2D, SetZoneMask, (unsigned), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter2D", "void set_zoneMask(uint)", AS_METHODPR(ParticleEmitter2D, SetZoneMask, (unsigned), void), AS_CALL_THISCALL);
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "void UnsubscribeFromAllEvents()", AS_METHODPR(ParticleEmitter2D, UnsubscribeFromAllEvents, (), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", AS_FUNCTION_OBJFIRST(ParticleEmitter2D_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), AS_CALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "void UnsubscribeFromEvent(StringHash)", AS_METHODPR(ParticleEmitter2D, UnsubscribeFromEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "void UnsubscribeFromEvent(Object@+, StringHash)", AS_METHODPR(ParticleEmitter2D, UnsubscribeFromEvent, (Object*, StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "void UnsubscribeFromEvents(Object@+)", AS_METHODPR(ParticleEmitter2D, UnsubscribeFromEvents, (Object*), void), AS_CALL_THISCALL);
    // virtual void Drawable::UpdateBatches(const FrameInfo& frame) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "void UpdateBatches(const FrameInfo&in)", AS_METHODPR(ParticleEmitter2D, UpdateBatches, (const FrameInfo&), void), AS_CALL_THISCALL);
    // virtual void Drawable::UpdateGeometry(const FrameInfo& frame) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "void UpdateGeometry(const FrameInfo&in)", AS_METHODPR(ParticleEmitter2D, UpdateGeometry, (const FrameInfo&), void), AS_CALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "int WeakRefs() const", AS_METHODPR(ParticleEmitter2D, WeakRefs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter2D", "int get_weakRefs() const", AS_METHODPR(ParticleEmitter2D, WeakRefs, () const, int), AS_CALL_THISCALL);
    // void Serializable::WriteDeltaUpdate(Serializer& dest, const DirtyBits& attributeBits, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "void WriteDeltaUpdate(Serializer&, const DirtyBits&in, uint8)", AS_METHODPR(ParticleEmitter2D, WriteDeltaUpdate, (Serializer&, const DirtyBits&, unsigned char), void), AS_CALL_THISCALL);
    // void Serializable::WriteInitialDeltaUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "void WriteInitialDeltaUpdate(Serializer&, uint8)", AS_METHODPR(ParticleEmitter2D, WriteInitialDeltaUpdate, (Serializer&, unsigned char), void), AS_CALL_THISCALL);
    // void Serializable::WriteLatestDataUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "void WriteLatestDataUpdate(Serializer&, uint8)", AS_METHODPR(ParticleEmitter2D, WriteLatestDataUpdate, (Serializer&, unsigned char), void), AS_CALL_THISCALL);
#ifdef REGISTER_MANUAL_PART_Drawable2D
    REGISTER_MANUAL_PART_Drawable2D(ParticleEmitter2D, "ParticleEmitter2D")
#endif
#ifdef REGISTER_MANUAL_PART_Drawable
    REGISTER_MANUAL_PART_Drawable(ParticleEmitter2D, "ParticleEmitter2D")
#endif
#ifdef REGISTER_MANUAL_PART_Component
    REGISTER_MANUAL_PART_Component(ParticleEmitter2D, "ParticleEmitter2D")
#endif
#ifdef REGISTER_MANUAL_PART_Animatable
    REGISTER_MANUAL_PART_Animatable(ParticleEmitter2D, "ParticleEmitter2D")
#endif
#ifdef REGISTER_MANUAL_PART_Serializable
    REGISTER_MANUAL_PART_Serializable(ParticleEmitter2D, "ParticleEmitter2D")
#endif
#ifdef REGISTER_MANUAL_PART_Object
    REGISTER_MANUAL_PART_Object(ParticleEmitter2D, "ParticleEmitter2D")
#endif
#ifdef REGISTER_MANUAL_PART_RefCounted
    REGISTER_MANUAL_PART_RefCounted(ParticleEmitter2D, "ParticleEmitter2D")
#endif
#ifdef REGISTER_MANUAL_PART_ParticleEmitter2D
    REGISTER_MANUAL_PART_ParticleEmitter2D(ParticleEmitter2D, "ParticleEmitter2D")
#endif
    RegisterSubclass<Drawable2D, ParticleEmitter2D>(engine, "Drawable2D", "ParticleEmitter2D");
    RegisterSubclass<Drawable, ParticleEmitter2D>(engine, "Drawable", "ParticleEmitter2D");
    RegisterSubclass<Component, ParticleEmitter2D>(engine, "Component", "ParticleEmitter2D");
    RegisterSubclass<Animatable, ParticleEmitter2D>(engine, "Animatable", "ParticleEmitter2D");
    RegisterSubclass<Serializable, ParticleEmitter2D>(engine, "Serializable", "ParticleEmitter2D");
    RegisterSubclass<Object, ParticleEmitter2D>(engine, "Object", "ParticleEmitter2D");
    RegisterSubclass<RefCounted, ParticleEmitter2D>(engine, "RefCounted", "ParticleEmitter2D");
#endif

    // void RefCounted::AddRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("Pass", asBEHAVE_ADDREF, "void f()", AS_METHODPR(Pass, AddRef, (), void), AS_CALL_THISCALL);
    // bool Pass::GetAlphaToCoverage() const | File: ../Graphics/Technique.h
    engine->RegisterObjectMethod("Pass", "bool GetAlphaToCoverage() const", AS_METHODPR(Pass, GetAlphaToCoverage, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Pass", "bool get_alphaToCoverage() const", AS_METHODPR(Pass, GetAlphaToCoverage, () const, bool), AS_CALL_THISCALL);
    // BlendMode Pass::GetBlendMode() const | File: ../Graphics/Technique.h
    engine->RegisterObjectMethod("Pass", "BlendMode GetBlendMode() const", AS_METHODPR(Pass, GetBlendMode, () const, BlendMode), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Pass", "BlendMode get_blendMode() const", AS_METHODPR(Pass, GetBlendMode, () const, BlendMode), AS_CALL_THISCALL);
    // CullMode Pass::GetCullMode() const | File: ../Graphics/Technique.h
    engine->RegisterObjectMethod("Pass", "CullMode GetCullMode() const", AS_METHODPR(Pass, GetCullMode, () const, CullMode), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Pass", "CullMode get_cullMode() const", AS_METHODPR(Pass, GetCullMode, () const, CullMode), AS_CALL_THISCALL);
    // CompareMode Pass::GetDepthTestMode() const | File: ../Graphics/Technique.h
    engine->RegisterObjectMethod("Pass", "CompareMode GetDepthTestMode() const", AS_METHODPR(Pass, GetDepthTestMode, () const, CompareMode), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Pass", "CompareMode get_depthTestMode() const", AS_METHODPR(Pass, GetDepthTestMode, () const, CompareMode), AS_CALL_THISCALL);
    // bool Pass::GetDepthWrite() const | File: ../Graphics/Technique.h
    engine->RegisterObjectMethod("Pass", "bool GetDepthWrite() const", AS_METHODPR(Pass, GetDepthWrite, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Pass", "bool get_depthWrite() const", AS_METHODPR(Pass, GetDepthWrite, () const, bool), AS_CALL_THISCALL);
    // String Pass::GetEffectivePixelShaderDefines() const | File: ../Graphics/Technique.h
    engine->RegisterObjectMethod("Pass", "String GetEffectivePixelShaderDefines() const", AS_METHODPR(Pass, GetEffectivePixelShaderDefines, () const, String), AS_CALL_THISCALL);
    // String Pass::GetEffectiveVertexShaderDefines() const | File: ../Graphics/Technique.h
    engine->RegisterObjectMethod("Pass", "String GetEffectiveVertexShaderDefines() const", AS_METHODPR(Pass, GetEffectiveVertexShaderDefines, () const, String), AS_CALL_THISCALL);
    // unsigned Pass::GetIndex() const | File: ../Graphics/Technique.h
    engine->RegisterObjectMethod("Pass", "uint GetIndex() const", AS_METHODPR(Pass, GetIndex, () const, unsigned), AS_CALL_THISCALL);
    // PassLightingMode Pass::GetLightingMode() const | File: ../Graphics/Technique.h
    engine->RegisterObjectMethod("Pass", "PassLightingMode GetLightingMode() const", AS_METHODPR(Pass, GetLightingMode, () const, PassLightingMode), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Pass", "PassLightingMode get_lightingMode() const", AS_METHODPR(Pass, GetLightingMode, () const, PassLightingMode), AS_CALL_THISCALL);
    // const String& Pass::GetName() const | File: ../Graphics/Technique.h
    engine->RegisterObjectMethod("Pass", "const String& GetName() const", AS_METHODPR(Pass, GetName, () const, const String&), AS_CALL_THISCALL);
    // const String& Pass::GetPixelShader() const | File: ../Graphics/Technique.h
    engine->RegisterObjectMethod("Pass", "const String& GetPixelShader() const", AS_METHODPR(Pass, GetPixelShader, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Pass", "const String& get_pixelShader() const", AS_METHODPR(Pass, GetPixelShader, () const, const String&), AS_CALL_THISCALL);
    // const String& Pass::GetPixelShaderDefineExcludes() const | File: ../Graphics/Technique.h
    engine->RegisterObjectMethod("Pass", "const String& GetPixelShaderDefineExcludes() const", AS_METHODPR(Pass, GetPixelShaderDefineExcludes, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Pass", "const String& get_pixelShaderDefineExcludes() const", AS_METHODPR(Pass, GetPixelShaderDefineExcludes, () const, const String&), AS_CALL_THISCALL);
    // const String& Pass::GetPixelShaderDefines() const | File: ../Graphics/Technique.h
    engine->RegisterObjectMethod("Pass", "const String& GetPixelShaderDefines() const", AS_METHODPR(Pass, GetPixelShaderDefines, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Pass", "const String& get_pixelShaderDefines() const", AS_METHODPR(Pass, GetPixelShaderDefines, () const, const String&), AS_CALL_THISCALL);
    // Vector<SharedPtr<ShaderVariation>>& Pass::GetPixelShaders() | File: ../Graphics/Technique.h
    engine->RegisterObjectMethod("Pass", "Array<ShaderVariation@>@ GetPixelShaders()", AS_FUNCTION_OBJFIRST(Pass_GetPixelShaders_void), AS_CALL_CDECL_OBJFIRST);
    // Vector<SharedPtr<ShaderVariation>>& Pass::GetPixelShaders(const StringHash& extraDefinesHash) | File: ../Graphics/Technique.h
    engine->RegisterObjectMethod("Pass", "Array<ShaderVariation@>@ GetPixelShaders(const StringHash&in)", AS_FUNCTION_OBJFIRST(Pass_GetPixelShaders_StringHash), AS_CALL_CDECL_OBJFIRST);
    // unsigned Pass::GetShadersLoadedFrameNumber() const | File: ../Graphics/Technique.h
    engine->RegisterObjectMethod("Pass", "uint GetShadersLoadedFrameNumber() const", AS_METHODPR(Pass, GetShadersLoadedFrameNumber, () const, unsigned), AS_CALL_THISCALL);
    // const String& Pass::GetVertexShader() const | File: ../Graphics/Technique.h
    engine->RegisterObjectMethod("Pass", "const String& GetVertexShader() const", AS_METHODPR(Pass, GetVertexShader, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Pass", "const String& get_vertexShader() const", AS_METHODPR(Pass, GetVertexShader, () const, const String&), AS_CALL_THISCALL);
    // const String& Pass::GetVertexShaderDefineExcludes() const | File: ../Graphics/Technique.h
    engine->RegisterObjectMethod("Pass", "const String& GetVertexShaderDefineExcludes() const", AS_METHODPR(Pass, GetVertexShaderDefineExcludes, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Pass", "const String& get_vertexShaderDefineExcludes() const", AS_METHODPR(Pass, GetVertexShaderDefineExcludes, () const, const String&), AS_CALL_THISCALL);
    // const String& Pass::GetVertexShaderDefines() const | File: ../Graphics/Technique.h
    engine->RegisterObjectMethod("Pass", "const String& GetVertexShaderDefines() const", AS_METHODPR(Pass, GetVertexShaderDefines, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Pass", "const String& get_vertexShaderDefines() const", AS_METHODPR(Pass, GetVertexShaderDefines, () const, const String&), AS_CALL_THISCALL);
    // Vector<SharedPtr<ShaderVariation>>& Pass::GetVertexShaders() | File: ../Graphics/Technique.h
    engine->RegisterObjectMethod("Pass", "Array<ShaderVariation@>@ GetVertexShaders()", AS_FUNCTION_OBJFIRST(Pass_GetVertexShaders_void), AS_CALL_CDECL_OBJFIRST);
    // Vector<SharedPtr<ShaderVariation>>& Pass::GetVertexShaders(const StringHash& extraDefinesHash) | File: ../Graphics/Technique.h
    engine->RegisterObjectMethod("Pass", "Array<ShaderVariation@>@ GetVertexShaders(const StringHash&in)", AS_FUNCTION_OBJFIRST(Pass_GetVertexShaders_StringHash), AS_CALL_CDECL_OBJFIRST);
    // bool Pass::IsDesktop() const | File: ../Graphics/Technique.h
    engine->RegisterObjectMethod("Pass", "bool IsDesktop() const", AS_METHODPR(Pass, IsDesktop, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Pass", "bool get_desktop() const", AS_METHODPR(Pass, IsDesktop, () const, bool), AS_CALL_THISCALL);
    // void Pass::MarkShadersLoaded(unsigned frameNumber) | File: ../Graphics/Technique.h
    engine->RegisterObjectMethod("Pass", "void MarkShadersLoaded(uint)", AS_METHODPR(Pass, MarkShadersLoaded, (unsigned), void), AS_CALL_THISCALL);
    // explicit Pass::Pass(const String& name) | File: ../Graphics/Technique.h
    engine->RegisterObjectBehaviour("Pass", asBEHAVE_FACTORY, "Pass@+ f(const String&in)", AS_FUNCTION(Pass_Pass_String), AS_CALL_CDECL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("Pass", "int Refs() const", AS_METHODPR(Pass, Refs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Pass", "int get_refs() const", AS_METHODPR(Pass, Refs, () const, int), AS_CALL_THISCALL);
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("Pass", asBEHAVE_RELEASE, "void f()", AS_METHODPR(Pass, ReleaseRef, (), void), AS_CALL_THISCALL);
    // void Pass::ReleaseShaders() | File: ../Graphics/Technique.h
    engine->RegisterObjectMethod("Pass", "void ReleaseShaders()", AS_METHODPR(Pass, ReleaseShaders, (), void), AS_CALL_THISCALL);
    // void Pass::SetAlphaToCoverage(bool enable) | File: ../Graphics/Technique.h
    engine->RegisterObjectMethod("Pass", "void SetAlphaToCoverage(bool)", AS_METHODPR(Pass, SetAlphaToCoverage, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Pass", "void set_alphaToCoverage(bool)", AS_METHODPR(Pass, SetAlphaToCoverage, (bool), void), AS_CALL_THISCALL);
    // void Pass::SetBlendMode(BlendMode mode) | File: ../Graphics/Technique.h
    engine->RegisterObjectMethod("Pass", "void SetBlendMode(BlendMode)", AS_METHODPR(Pass, SetBlendMode, (BlendMode), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Pass", "void set_blendMode(BlendMode)", AS_METHODPR(Pass, SetBlendMode, (BlendMode), void), AS_CALL_THISCALL);
    // void Pass::SetCullMode(CullMode mode) | File: ../Graphics/Technique.h
    engine->RegisterObjectMethod("Pass", "void SetCullMode(CullMode)", AS_METHODPR(Pass, SetCullMode, (CullMode), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Pass", "void set_cullMode(CullMode)", AS_METHODPR(Pass, SetCullMode, (CullMode), void), AS_CALL_THISCALL);
    // void Pass::SetDepthTestMode(CompareMode mode) | File: ../Graphics/Technique.h
    engine->RegisterObjectMethod("Pass", "void SetDepthTestMode(CompareMode)", AS_METHODPR(Pass, SetDepthTestMode, (CompareMode), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Pass", "void set_depthTestMode(CompareMode)", AS_METHODPR(Pass, SetDepthTestMode, (CompareMode), void), AS_CALL_THISCALL);
    // void Pass::SetDepthWrite(bool enable) | File: ../Graphics/Technique.h
    engine->RegisterObjectMethod("Pass", "void SetDepthWrite(bool)", AS_METHODPR(Pass, SetDepthWrite, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Pass", "void set_depthWrite(bool)", AS_METHODPR(Pass, SetDepthWrite, (bool), void), AS_CALL_THISCALL);
    // void Pass::SetIsDesktop(bool enable) | File: ../Graphics/Technique.h
    engine->RegisterObjectMethod("Pass", "void SetIsDesktop(bool)", AS_METHODPR(Pass, SetIsDesktop, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Pass", "void set_desktop(bool)", AS_METHODPR(Pass, SetIsDesktop, (bool), void), AS_CALL_THISCALL);
    // void Pass::SetLightingMode(PassLightingMode mode) | File: ../Graphics/Technique.h
    engine->RegisterObjectMethod("Pass", "void SetLightingMode(PassLightingMode)", AS_METHODPR(Pass, SetLightingMode, (PassLightingMode), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Pass", "void set_lightingMode(PassLightingMode)", AS_METHODPR(Pass, SetLightingMode, (PassLightingMode), void), AS_CALL_THISCALL);
    // void Pass::SetPixelShader(const String& name) | File: ../Graphics/Technique.h
    engine->RegisterObjectMethod("Pass", "void SetPixelShader(const String&in)", AS_METHODPR(Pass, SetPixelShader, (const String&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Pass", "void set_pixelShader(const String&in)", AS_METHODPR(Pass, SetPixelShader, (const String&), void), AS_CALL_THISCALL);
    // void Pass::SetPixelShaderDefineExcludes(const String& excludes) | File: ../Graphics/Technique.h
    engine->RegisterObjectMethod("Pass", "void SetPixelShaderDefineExcludes(const String&in)", AS_METHODPR(Pass, SetPixelShaderDefineExcludes, (const String&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Pass", "void set_pixelShaderDefineExcludes(const String&in)", AS_METHODPR(Pass, SetPixelShaderDefineExcludes, (const String&), void), AS_CALL_THISCALL);
    // void Pass::SetPixelShaderDefines(const String& defines) | File: ../Graphics/Technique.h
    engine->RegisterObjectMethod("Pass", "void SetPixelShaderDefines(const String&in)", AS_METHODPR(Pass, SetPixelShaderDefines, (const String&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Pass", "void set_pixelShaderDefines(const String&in)", AS_METHODPR(Pass, SetPixelShaderDefines, (const String&), void), AS_CALL_THISCALL);
    // void Pass::SetVertexShader(const String& name) | File: ../Graphics/Technique.h
    engine->RegisterObjectMethod("Pass", "void SetVertexShader(const String&in)", AS_METHODPR(Pass, SetVertexShader, (const String&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Pass", "void set_vertexShader(const String&in)", AS_METHODPR(Pass, SetVertexShader, (const String&), void), AS_CALL_THISCALL);
    // void Pass::SetVertexShaderDefineExcludes(const String& excludes) | File: ../Graphics/Technique.h
    engine->RegisterObjectMethod("Pass", "void SetVertexShaderDefineExcludes(const String&in)", AS_METHODPR(Pass, SetVertexShaderDefineExcludes, (const String&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Pass", "void set_vertexShaderDefineExcludes(const String&in)", AS_METHODPR(Pass, SetVertexShaderDefineExcludes, (const String&), void), AS_CALL_THISCALL);
    // void Pass::SetVertexShaderDefines(const String& defines) | File: ../Graphics/Technique.h
    engine->RegisterObjectMethod("Pass", "void SetVertexShaderDefines(const String&in)", AS_METHODPR(Pass, SetVertexShaderDefines, (const String&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Pass", "void set_vertexShaderDefines(const String&in)", AS_METHODPR(Pass, SetVertexShaderDefines, (const String&), void), AS_CALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("Pass", "int WeakRefs() const", AS_METHODPR(Pass, WeakRefs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Pass", "int get_weakRefs() const", AS_METHODPR(Pass, WeakRefs, () const, int), AS_CALL_THISCALL);
#ifdef REGISTER_MANUAL_PART_RefCounted
    REGISTER_MANUAL_PART_RefCounted(Pass, "Pass")
#endif
#ifdef REGISTER_MANUAL_PART_Pass
    REGISTER_MANUAL_PART_Pass(Pass, "Pass")
#endif
    RegisterSubclass<RefCounted, Pass>(engine, "RefCounted", "Pass");

#ifdef URHO3D_PHYSICS
    // struct PhysicsWorldConfig PhysicsWorld::config | File: ../Physics/PhysicsWorld.h
    // Error: type "struct PhysicsWorldConfig" can not automatically bind
    // void PhysicsWorld::AddCollisionShape(CollisionShape* shape) | File: ../Physics/PhysicsWorld.h
    engine->RegisterObjectMethod("PhysicsWorld", "void AddCollisionShape(CollisionShape@+)", AS_METHODPR(PhysicsWorld, AddCollisionShape, (CollisionShape*), void), AS_CALL_THISCALL);
    // void PhysicsWorld::AddConstraint(Constraint* constraint) | File: ../Physics/PhysicsWorld.h
    engine->RegisterObjectMethod("PhysicsWorld", "void AddConstraint(Constraint@+)", AS_METHODPR(PhysicsWorld, AddConstraint, (Constraint*), void), AS_CALL_THISCALL);
    // void PhysicsWorld::AddDelayedWorldTransform(const DelayedWorldTransform& transform) | File: ../Physics/PhysicsWorld.h
    engine->RegisterObjectMethod("PhysicsWorld", "void AddDelayedWorldTransform(const DelayedWorldTransform&in)", AS_METHODPR(PhysicsWorld, AddDelayedWorldTransform, (const DelayedWorldTransform&), void), AS_CALL_THISCALL);
    // void RefCounted::AddRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("PhysicsWorld", asBEHAVE_ADDREF, "void f()", AS_METHODPR(PhysicsWorld, AddRef, (), void), AS_CALL_THISCALL);
    // void Component::AddReplicationState(ComponentReplicationState* state) | File: ../Scene/Component.h
    // Error: type "ComponentReplicationState*" can not automatically bind
    // void PhysicsWorld::AddRigidBody(RigidBody* body) | File: ../Physics/PhysicsWorld.h
    engine->RegisterObjectMethod("PhysicsWorld", "void AddRigidBody(RigidBody@+)", AS_METHODPR(PhysicsWorld, AddRigidBody, (RigidBody*), void), AS_CALL_THISCALL);
    // void Serializable::AllocateNetworkState() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("PhysicsWorld", "void AllocateNetworkState()", AS_METHODPR(PhysicsWorld, AllocateNetworkState, (), void), AS_CALL_THISCALL);
    // virtual void Serializable::ApplyAttributes() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("PhysicsWorld", "void ApplyAttributes()", AS_METHODPR(PhysicsWorld, ApplyAttributes, (), void), AS_CALL_THISCALL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // void Component::CleanupConnection(Connection* connection) | File: ../Scene/Component.h
    // Not registered because have @manualbind mark
    // void PhysicsWorld::CleanupGeometryCache() | File: ../Physics/PhysicsWorld.h
    engine->RegisterObjectMethod("PhysicsWorld", "void CleanupGeometryCache()", AS_METHODPR(PhysicsWorld, CleanupGeometryCache, (), void), AS_CALL_THISCALL);
    // void PhysicsWorld::ConvexCast(PhysicsRaycastResult& result, CollisionShape* shape, const Vector3& startPos, const Quaternion& startRot, const Vector3& endPos, const Quaternion& endRot, unsigned collisionMask=M_MAX_UNSIGNED) | File: ../Physics/PhysicsWorld.h
    engine->RegisterObjectMethod("PhysicsWorld", "void ConvexCast(PhysicsRaycastResult&, CollisionShape@+, const Vector3&in, const Quaternion&in, const Vector3&in, const Quaternion&in, uint = M_MAX_UNSIGNED)", AS_METHODPR(PhysicsWorld, ConvexCast, (PhysicsRaycastResult&, CollisionShape*, const Vector3&, const Quaternion&, const Vector3&, const Quaternion&, unsigned), void), AS_CALL_THISCALL);
    // void PhysicsWorld::ConvexCast(PhysicsRaycastResult& result, btCollisionShape* shape, const Vector3& startPos, const Quaternion& startRot, const Vector3& endPos, const Quaternion& endRot, unsigned collisionMask=M_MAX_UNSIGNED) | File: ../Physics/PhysicsWorld.h
    // Error: type "btCollisionShape*" can not automatically bind
    // void PhysicsWorld::draw3dText(const btVector3& location, const char* textString) override | File: ../Physics/PhysicsWorld.h
    // Error: type "const btVector3&" can not automatically bind
    // void PhysicsWorld::drawContactPoint(const btVector3& pointOnB, const btVector3& normalOnB, btScalar distance, int lifeTime, const btVector3& color) override | File: ../Physics/PhysicsWorld.h
    // Error: type "const btVector3&" can not automatically bind
    // void PhysicsWorld::DrawDebugGeometry(DebugRenderer* debug, bool depthTest) override | File: ../Physics/PhysicsWorld.h
    engine->RegisterObjectMethod("PhysicsWorld", "void DrawDebugGeometry(DebugRenderer@+, bool)", AS_METHODPR(PhysicsWorld, DrawDebugGeometry, (DebugRenderer*, bool), void), AS_CALL_THISCALL);
    // void PhysicsWorld::DrawDebugGeometry(bool depthTest) | File: ../Physics/PhysicsWorld.h
    engine->RegisterObjectMethod("PhysicsWorld", "void DrawDebugGeometry(bool)", AS_METHODPR(PhysicsWorld, DrawDebugGeometry, (bool), void), AS_CALL_THISCALL);
    // void PhysicsWorld::drawLine(const btVector3& from, const btVector3& to, const btVector3& color) override | File: ../Physics/PhysicsWorld.h
    // Error: type "const btVector3&" can not automatically bind
    // bool Animatable::GetAnimationEnabled() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("PhysicsWorld", "bool GetAnimationEnabled() const", AS_METHODPR(PhysicsWorld, GetAnimationEnabled, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("PhysicsWorld", "bool get_animationEnabled() const", AS_METHODPR(PhysicsWorld, GetAnimationEnabled, () const, bool), AS_CALL_THISCALL);
    // Variant Serializable::GetAttribute(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("PhysicsWorld", "Variant GetAttribute(uint) const", AS_METHODPR(PhysicsWorld, GetAttribute, (unsigned) const, Variant), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("PhysicsWorld", "Variant get_attributes(uint) const", AS_METHODPR(PhysicsWorld, GetAttribute, (unsigned) const, Variant), AS_CALL_THISCALL);
    // Variant Serializable::GetAttribute(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("PhysicsWorld", "Variant GetAttribute(const String&in) const", AS_METHODPR(PhysicsWorld, GetAttribute, (const String&) const, Variant), AS_CALL_THISCALL);
    // ValueAnimation* Animatable::GetAttributeAnimation(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("PhysicsWorld", "ValueAnimation@+ GetAttributeAnimation(const String&in) const", AS_METHODPR(PhysicsWorld, GetAttributeAnimation, (const String&) const, ValueAnimation*), AS_CALL_THISCALL);
    // float Animatable::GetAttributeAnimationSpeed(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("PhysicsWorld", "float GetAttributeAnimationSpeed(const String&in) const", AS_METHODPR(PhysicsWorld, GetAttributeAnimationSpeed, (const String&) const, float), AS_CALL_THISCALL);
    // float Animatable::GetAttributeAnimationTime(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("PhysicsWorld", "float GetAttributeAnimationTime(const String&in) const", AS_METHODPR(PhysicsWorld, GetAttributeAnimationTime, (const String&) const, float), AS_CALL_THISCALL);
    // WrapMode Animatable::GetAttributeAnimationWrapMode(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("PhysicsWorld", "WrapMode GetAttributeAnimationWrapMode(const String&in) const", AS_METHODPR(PhysicsWorld, GetAttributeAnimationWrapMode, (const String&) const, WrapMode), AS_CALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("PhysicsWorld", "Variant GetAttributeDefault(uint) const", AS_METHODPR(PhysicsWorld, GetAttributeDefault, (unsigned) const, Variant), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("PhysicsWorld", "Variant get_attributeDefaults(uint) const", AS_METHODPR(PhysicsWorld, GetAttributeDefault, (unsigned) const, Variant), AS_CALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("PhysicsWorld", "Variant GetAttributeDefault(const String&in) const", AS_METHODPR(PhysicsWorld, GetAttributeDefault, (const String&) const, Variant), AS_CALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("PhysicsWorld", "bool GetBlockEvents() const", AS_METHODPR(PhysicsWorld, GetBlockEvents, () const, bool), AS_CALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("PhysicsWorld", "const String& GetCategory() const", AS_METHODPR(PhysicsWorld, GetCategory, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("PhysicsWorld", "const String& get_category() const", AS_METHODPR(PhysicsWorld, GetCategory, () const, const String&), AS_CALL_THISCALL);
    // void PhysicsWorld::GetCollidingBodies(PODVector<RigidBody*>& result, const RigidBody* body) | File: ../Physics/PhysicsWorld.h
    // Error: type "PODVector<RigidBody*>&" can not automatically bind
    // Component* Component::GetComponent(StringHash type) const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("PhysicsWorld", "Component@+ GetComponent(StringHash) const", AS_METHODPR(PhysicsWorld, GetComponent, (StringHash) const, Component*), AS_CALL_THISCALL);
    // template<class T> T* Component::GetComponent() const | File: ../Scene/Component.h
    // Not registered because template
    // void Component::GetComponents(PODVector<Component*>& dest, StringHash type) const | File: ../Scene/Component.h
    // Error: type "PODVector<Component*>&" can not automatically bind
    // template<class T> void Component::GetComponents(PODVector<T*>& dest) const | File: ../Scene/Component.h
    // Not registered because template
    // Context* Object::GetContext() const | File: ../Core/Object.h
    // Error: type "Context*" can used only as function parameter
    // CollisionGeometryDataCache& PhysicsWorld::GetConvexCache() | File: ../Physics/PhysicsWorld.h
    // Error: type "CollisionGeometryDataCache&" can not automatically bind
    // int PhysicsWorld::getDebugMode() const override | File: ../Physics/PhysicsWorld.h
    engine->RegisterObjectMethod("PhysicsWorld", "int getDebugMode() const", AS_METHODPR(PhysicsWorld, getDebugMode, () const, int), AS_CALL_THISCALL);
    // virtual void Component::GetDependencyNodes(PODVector<Node*>& dest) | File: ../Scene/Component.h
    // Error: type "PODVector<Node*>&" can not automatically bind
    // VariantMap& Object::GetEventDataMap() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("PhysicsWorld", "VariantMap& GetEventDataMap() const", AS_METHODPR(PhysicsWorld, GetEventDataMap, () const, VariantMap&), AS_CALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("PhysicsWorld", "Object@+ GetEventSender() const", AS_METHODPR(PhysicsWorld, GetEventSender, () const, Object*), AS_CALL_THISCALL);
    // int PhysicsWorld::GetFps() const | File: ../Physics/PhysicsWorld.h
    engine->RegisterObjectMethod("PhysicsWorld", "int GetFps() const", AS_METHODPR(PhysicsWorld, GetFps, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("PhysicsWorld", "int get_fps() const", AS_METHODPR(PhysicsWorld, GetFps, () const, int), AS_CALL_THISCALL);
    // CollisionGeometryDataCache& PhysicsWorld::GetGImpactTrimeshCache() | File: ../Physics/PhysicsWorld.h
    // Error: type "CollisionGeometryDataCache&" can not automatically bind
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("PhysicsWorld", "const Variant& GetGlobalVar(StringHash) const", AS_METHODPR(PhysicsWorld, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("PhysicsWorld", "const Variant& get_globalVar(StringHash) const", AS_METHODPR(PhysicsWorld, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("PhysicsWorld", "const VariantMap& GetGlobalVars() const", AS_METHODPR(PhysicsWorld, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("PhysicsWorld", "const VariantMap& get_globalVars() const", AS_METHODPR(PhysicsWorld, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    // Vector3 PhysicsWorld::GetGravity() const | File: ../Physics/PhysicsWorld.h
    engine->RegisterObjectMethod("PhysicsWorld", "Vector3 GetGravity() const", AS_METHODPR(PhysicsWorld, GetGravity, () const, Vector3), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("PhysicsWorld", "Vector3 get_gravity() const", AS_METHODPR(PhysicsWorld, GetGravity, () const, Vector3), AS_CALL_THISCALL);
    // unsigned Component::GetID() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("PhysicsWorld", "uint GetID() const", AS_METHODPR(PhysicsWorld, GetID, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("PhysicsWorld", "uint get_id() const", AS_METHODPR(PhysicsWorld, GetID, () const, unsigned), AS_CALL_THISCALL);
    // bool Serializable::GetInterceptNetworkUpdate(const String& attributeName) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("PhysicsWorld", "bool GetInterceptNetworkUpdate(const String&in) const", AS_METHODPR(PhysicsWorld, GetInterceptNetworkUpdate, (const String&) const, bool), AS_CALL_THISCALL);
    // bool PhysicsWorld::GetInternalEdge() const | File: ../Physics/PhysicsWorld.h
    engine->RegisterObjectMethod("PhysicsWorld", "bool GetInternalEdge() const", AS_METHODPR(PhysicsWorld, GetInternalEdge, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("PhysicsWorld", "bool get_internalEdge() const", AS_METHODPR(PhysicsWorld, GetInternalEdge, () const, bool), AS_CALL_THISCALL);
    // bool PhysicsWorld::GetInterpolation() const | File: ../Physics/PhysicsWorld.h
    engine->RegisterObjectMethod("PhysicsWorld", "bool GetInterpolation() const", AS_METHODPR(PhysicsWorld, GetInterpolation, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("PhysicsWorld", "bool get_interpolation() const", AS_METHODPR(PhysicsWorld, GetInterpolation, () const, bool), AS_CALL_THISCALL);
    // float PhysicsWorld::GetMaxNetworkAngularVelocity() const | File: ../Physics/PhysicsWorld.h
    engine->RegisterObjectMethod("PhysicsWorld", "float GetMaxNetworkAngularVelocity() const", AS_METHODPR(PhysicsWorld, GetMaxNetworkAngularVelocity, () const, float), AS_CALL_THISCALL);
    // int PhysicsWorld::GetMaxSubSteps() const | File: ../Physics/PhysicsWorld.h
    engine->RegisterObjectMethod("PhysicsWorld", "int GetMaxSubSteps() const", AS_METHODPR(PhysicsWorld, GetMaxSubSteps, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("PhysicsWorld", "int get_maxSubSteps() const", AS_METHODPR(PhysicsWorld, GetMaxSubSteps, () const, int), AS_CALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetNetworkAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // NetworkState* Serializable::GetNetworkState() const | File: ../Scene/Serializable.h
    // Error: type "NetworkState*" can not automatically bind
    // Node* Component::GetNode() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("PhysicsWorld", "Node@+ GetNode() const", AS_METHODPR(PhysicsWorld, GetNode, () const, Node*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("PhysicsWorld", "Node@+ get_node() const", AS_METHODPR(PhysicsWorld, GetNode, () const, Node*), AS_CALL_THISCALL);
    // unsigned Serializable::GetNumAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("PhysicsWorld", "uint GetNumAttributes() const", AS_METHODPR(PhysicsWorld, GetNumAttributes, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("PhysicsWorld", "uint get_numAttributes() const", AS_METHODPR(PhysicsWorld, GetNumAttributes, () const, unsigned), AS_CALL_THISCALL);
    // int PhysicsWorld::GetNumIterations() const | File: ../Physics/PhysicsWorld.h
    engine->RegisterObjectMethod("PhysicsWorld", "int GetNumIterations() const", AS_METHODPR(PhysicsWorld, GetNumIterations, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("PhysicsWorld", "int get_numIterations() const", AS_METHODPR(PhysicsWorld, GetNumIterations, () const, int), AS_CALL_THISCALL);
    // unsigned Serializable::GetNumNetworkAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("PhysicsWorld", "uint GetNumNetworkAttributes() const", AS_METHODPR(PhysicsWorld, GetNumNetworkAttributes, () const, unsigned), AS_CALL_THISCALL);
    // ObjectAnimation* Animatable::GetObjectAnimation() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("PhysicsWorld", "ObjectAnimation@+ GetObjectAnimation() const", AS_METHODPR(PhysicsWorld, GetObjectAnimation, () const, ObjectAnimation*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("PhysicsWorld", "ObjectAnimation@+ get_objectAnimation() const", AS_METHODPR(PhysicsWorld, GetObjectAnimation, () const, ObjectAnimation*), AS_CALL_THISCALL);
    // ResourceRef Animatable::GetObjectAnimationAttr() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("PhysicsWorld", "ResourceRef GetObjectAnimationAttr() const", AS_METHODPR(PhysicsWorld, GetObjectAnimationAttr, () const, ResourceRef), AS_CALL_THISCALL);
    // void PhysicsWorld::GetRigidBodies(PODVector<RigidBody*>& result, const Sphere& sphere, unsigned collisionMask=M_MAX_UNSIGNED) | File: ../Physics/PhysicsWorld.h
    // Error: type "PODVector<RigidBody*>&" can not automatically bind
    // void PhysicsWorld::GetRigidBodies(PODVector<RigidBody*>& result, const BoundingBox& box, unsigned collisionMask=M_MAX_UNSIGNED) | File: ../Physics/PhysicsWorld.h
    // Error: type "PODVector<RigidBody*>&" can not automatically bind
    // void PhysicsWorld::GetRigidBodies(PODVector<RigidBody*>& result, const RigidBody* body) | File: ../Physics/PhysicsWorld.h
    // Error: type "PODVector<RigidBody*>&" can not automatically bind
    // Scene* Component::GetScene() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("PhysicsWorld", "Scene@+ GetScene() const", AS_METHODPR(PhysicsWorld, GetScene, () const, Scene*), AS_CALL_THISCALL);
    // bool PhysicsWorld::GetSplitImpulse() const | File: ../Physics/PhysicsWorld.h
    engine->RegisterObjectMethod("PhysicsWorld", "bool GetSplitImpulse() const", AS_METHODPR(PhysicsWorld, GetSplitImpulse, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("PhysicsWorld", "bool get_splitImpulse() const", AS_METHODPR(PhysicsWorld, GetSplitImpulse, () const, bool), AS_CALL_THISCALL);
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("PhysicsWorld", "Object@+ GetSubsystem(StringHash) const", AS_METHODPR(PhysicsWorld, GetSubsystem, (StringHash) const, Object*), AS_CALL_THISCALL);
    // template<class T> T* Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // CollisionGeometryDataCache& PhysicsWorld::GetTriMeshCache() | File: ../Physics/PhysicsWorld.h
    // Error: type "CollisionGeometryDataCache&" can not automatically bind
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("PhysicsWorld", "StringHash GetType() const", AS_METHODPR(PhysicsWorld, GetType, () const, StringHash), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("PhysicsWorld", "StringHash get_type() const", AS_METHODPR(PhysicsWorld, GetType, () const, StringHash), AS_CALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("PhysicsWorld", "const String& GetTypeName() const", AS_METHODPR(PhysicsWorld, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("PhysicsWorld", "const String& get_typeName() const", AS_METHODPR(PhysicsWorld, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    // btDiscreteDynamicsWorld* PhysicsWorld::GetWorld() | File: ../Physics/PhysicsWorld.h
    // Error: type "btDiscreteDynamicsWorld*" can not automatically bind
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("PhysicsWorld", "bool HasEventHandlers() const", AS_METHODPR(PhysicsWorld, HasEventHandlers, () const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("PhysicsWorld", "bool HasSubscribedToEvent(StringHash) const", AS_METHODPR(PhysicsWorld, HasSubscribedToEvent, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("PhysicsWorld", "bool HasSubscribedToEvent(Object@+, StringHash) const", AS_METHODPR(PhysicsWorld, HasSubscribedToEvent, (Object*, StringHash) const, bool), AS_CALL_THISCALL);
    // bool PhysicsWorld::IsApplyingTransforms() const | File: ../Physics/PhysicsWorld.h
    engine->RegisterObjectMethod("PhysicsWorld", "bool IsApplyingTransforms() const", AS_METHODPR(PhysicsWorld, IsApplyingTransforms, () const, bool), AS_CALL_THISCALL);
    // bool Component::IsEnabled() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("PhysicsWorld", "bool IsEnabled() const", AS_METHODPR(PhysicsWorld, IsEnabled, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("PhysicsWorld", "bool get_enabled() const", AS_METHODPR(PhysicsWorld, IsEnabled, () const, bool), AS_CALL_THISCALL);
    // bool Component::IsEnabledEffective() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("PhysicsWorld", "bool IsEnabledEffective() const", AS_METHODPR(PhysicsWorld, IsEnabledEffective, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("PhysicsWorld", "bool get_enabledEffective() const", AS_METHODPR(PhysicsWorld, IsEnabledEffective, () const, bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("PhysicsWorld", "bool IsInstanceOf(StringHash) const", AS_METHODPR(PhysicsWorld, IsInstanceOf, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // bool Component::IsReplicated() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("PhysicsWorld", "bool IsReplicated() const", AS_METHODPR(PhysicsWorld, IsReplicated, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("PhysicsWorld", "bool get_replicated() const", AS_METHODPR(PhysicsWorld, IsReplicated, () const, bool), AS_CALL_THISCALL);
    // bool PhysicsWorld::IsSimulating() const | File: ../Physics/PhysicsWorld.h
    engine->RegisterObjectMethod("PhysicsWorld", "bool IsSimulating() const", AS_METHODPR(PhysicsWorld, IsSimulating, () const, bool), AS_CALL_THISCALL);
    // bool Serializable::IsTemporary() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("PhysicsWorld", "bool IsTemporary() const", AS_METHODPR(PhysicsWorld, IsTemporary, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("PhysicsWorld", "bool get_temporary() const", AS_METHODPR(PhysicsWorld, IsTemporary, () const, bool), AS_CALL_THISCALL);
    // bool PhysicsWorld::IsUpdateEnabled() const | File: ../Physics/PhysicsWorld.h
    engine->RegisterObjectMethod("PhysicsWorld", "bool IsUpdateEnabled() const", AS_METHODPR(PhysicsWorld, IsUpdateEnabled, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("PhysicsWorld", "bool get_updateEnabled() const", AS_METHODPR(PhysicsWorld, IsUpdateEnabled, () const, bool), AS_CALL_THISCALL);
    // bool PhysicsWorld::isVisible(const btVector3& aabbMin, const btVector3& aabbMax) override | File: ../Physics/PhysicsWorld.h
    // Error: type "const btVector3&" can not automatically bind
    // virtual bool Serializable::Load(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("PhysicsWorld", "bool Load(Deserializer&)", AS_METHODPR(PhysicsWorld, Load, (Deserializer&), bool), AS_CALL_THISCALL);
    // bool Animatable::LoadJSON(const JSONValue& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("PhysicsWorld", "bool LoadJSON(const JSONValue&in)", AS_METHODPR(PhysicsWorld, LoadJSON, (const JSONValue&), bool), AS_CALL_THISCALL);
    // bool Animatable::LoadXML(const XMLElement& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("PhysicsWorld", "bool LoadXML(const XMLElement&in)", AS_METHODPR(PhysicsWorld, LoadXML, (const XMLElement&), bool), AS_CALL_THISCALL);
    // void Component::MarkNetworkUpdate() override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("PhysicsWorld", "void MarkNetworkUpdate()", AS_METHODPR(PhysicsWorld, MarkNetworkUpdate, (), void), AS_CALL_THISCALL);
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("PhysicsWorld", "void OnEvent(Object@+, StringHash, VariantMap&)", AS_METHODPR(PhysicsWorld, OnEvent, (Object*, StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // virtual void Serializable::OnGetAttribute(const AttributeInfo& attr, Variant& dest) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("PhysicsWorld", "void OnGetAttribute(const AttributeInfo&in, Variant&) const", AS_METHODPR(PhysicsWorld, OnGetAttribute, (const AttributeInfo&, Variant&) const, void), AS_CALL_THISCALL);
    // virtual void Serializable::OnSetAttribute(const AttributeInfo& attr, const Variant& src) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("PhysicsWorld", "void OnSetAttribute(const AttributeInfo&in, const Variant&in)", AS_METHODPR(PhysicsWorld, OnSetAttribute, (const AttributeInfo&, const Variant&), void), AS_CALL_THISCALL);
    // virtual void Component::OnSetEnabled() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("PhysicsWorld", "void OnSetEnabled()", AS_METHODPR(PhysicsWorld, OnSetEnabled, (), void), AS_CALL_THISCALL);
    // explicit PhysicsWorld::PhysicsWorld(Context* context) | File: ../Physics/PhysicsWorld.h
    engine->RegisterObjectBehaviour("PhysicsWorld", asBEHAVE_FACTORY, "PhysicsWorld@+ f()", AS_FUNCTION(PhysicsWorld_PhysicsWorld_Context), AS_CALL_CDECL);
    // void Component::PrepareNetworkUpdate() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("PhysicsWorld", "void PrepareNetworkUpdate()", AS_METHODPR(PhysicsWorld, PrepareNetworkUpdate, (), void), AS_CALL_THISCALL);
    // void PhysicsWorld::Raycast(PODVector<PhysicsRaycastResult>& result, const Ray& ray, float maxDistance, unsigned collisionMask=M_MAX_UNSIGNED) | File: ../Physics/PhysicsWorld.h
    // Error: type "PODVector<PhysicsRaycastResult>&" can not automatically bind
    // void PhysicsWorld::RaycastSingle(PhysicsRaycastResult& result, const Ray& ray, float maxDistance, unsigned collisionMask=M_MAX_UNSIGNED) | File: ../Physics/PhysicsWorld.h
    engine->RegisterObjectMethod("PhysicsWorld", "void RaycastSingle(PhysicsRaycastResult&, const Ray&in, float, uint = M_MAX_UNSIGNED)", AS_METHODPR(PhysicsWorld, RaycastSingle, (PhysicsRaycastResult&, const Ray&, float, unsigned), void), AS_CALL_THISCALL);
    // void PhysicsWorld::RaycastSingleSegmented(PhysicsRaycastResult& result, const Ray& ray, float maxDistance, float segmentDistance, unsigned collisionMask=M_MAX_UNSIGNED, float overlapDistance=0.1f) | File: ../Physics/PhysicsWorld.h
    engine->RegisterObjectMethod("PhysicsWorld", "void RaycastSingleSegmented(PhysicsRaycastResult&, const Ray&in, float, float, uint = M_MAX_UNSIGNED, float = 0.1f)", AS_METHODPR(PhysicsWorld, RaycastSingleSegmented, (PhysicsRaycastResult&, const Ray&, float, float, unsigned, float), void), AS_CALL_THISCALL);
    // bool Serializable::ReadDeltaUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("PhysicsWorld", "bool ReadDeltaUpdate(Deserializer&)", AS_METHODPR(PhysicsWorld, ReadDeltaUpdate, (Deserializer&), bool), AS_CALL_THISCALL);
    // bool Serializable::ReadLatestDataUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("PhysicsWorld", "bool ReadLatestDataUpdate(Deserializer&)", AS_METHODPR(PhysicsWorld, ReadLatestDataUpdate, (Deserializer&), bool), AS_CALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("PhysicsWorld", "int Refs() const", AS_METHODPR(PhysicsWorld, Refs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("PhysicsWorld", "int get_refs() const", AS_METHODPR(PhysicsWorld, Refs, () const, int), AS_CALL_THISCALL);
    // static void PhysicsWorld::RegisterObject(Context* context) | File: ../Physics/PhysicsWorld.h
    // Not registered because have @nobind mark
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("PhysicsWorld", asBEHAVE_RELEASE, "void f()", AS_METHODPR(PhysicsWorld, ReleaseRef, (), void), AS_CALL_THISCALL);
    // void Component::Remove() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("PhysicsWorld", "void Remove()", AS_METHODPR(PhysicsWorld, Remove, (), void), AS_CALL_THISCALL);
    // void Animatable::RemoveAttributeAnimation(const String& name) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("PhysicsWorld", "void RemoveAttributeAnimation(const String&in)", AS_METHODPR(PhysicsWorld, RemoveAttributeAnimation, (const String&), void), AS_CALL_THISCALL);
    // void PhysicsWorld::RemoveCachedGeometry(Model* model) | File: ../Physics/PhysicsWorld.h
    engine->RegisterObjectMethod("PhysicsWorld", "void RemoveCachedGeometry(Model@+)", AS_METHODPR(PhysicsWorld, RemoveCachedGeometry, (Model*), void), AS_CALL_THISCALL);
    // void PhysicsWorld::RemoveCollisionShape(CollisionShape* shape) | File: ../Physics/PhysicsWorld.h
    engine->RegisterObjectMethod("PhysicsWorld", "void RemoveCollisionShape(CollisionShape@+)", AS_METHODPR(PhysicsWorld, RemoveCollisionShape, (CollisionShape*), void), AS_CALL_THISCALL);
    // void PhysicsWorld::RemoveConstraint(Constraint* constraint) | File: ../Physics/PhysicsWorld.h
    engine->RegisterObjectMethod("PhysicsWorld", "void RemoveConstraint(Constraint@+)", AS_METHODPR(PhysicsWorld, RemoveConstraint, (Constraint*), void), AS_CALL_THISCALL);
    // void Serializable::RemoveInstanceDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("PhysicsWorld", "void RemoveInstanceDefault()", AS_METHODPR(PhysicsWorld, RemoveInstanceDefault, (), void), AS_CALL_THISCALL);
    // void Animatable::RemoveObjectAnimation() | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("PhysicsWorld", "void RemoveObjectAnimation()", AS_METHODPR(PhysicsWorld, RemoveObjectAnimation, (), void), AS_CALL_THISCALL);
    // void PhysicsWorld::RemoveRigidBody(RigidBody* body) | File: ../Physics/PhysicsWorld.h
    engine->RegisterObjectMethod("PhysicsWorld", "void RemoveRigidBody(RigidBody@+)", AS_METHODPR(PhysicsWorld, RemoveRigidBody, (RigidBody*), void), AS_CALL_THISCALL);
    // void PhysicsWorld::reportErrorWarning(const char* warningString) override | File: ../Physics/PhysicsWorld.h
    // Error: type "const char*" can not automatically bind
    // void Serializable::ResetToDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("PhysicsWorld", "void ResetToDefault()", AS_METHODPR(PhysicsWorld, ResetToDefault, (), void), AS_CALL_THISCALL);
    // bool Component::Save(Serializer& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("PhysicsWorld", "bool Save(Serializer&) const", AS_METHODPR(PhysicsWorld, Save, (Serializer&) const, bool), AS_CALL_THISCALL);
    // virtual bool Serializable::SaveDefaultAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("PhysicsWorld", "bool SaveDefaultAttributes() const", AS_METHODPR(PhysicsWorld, SaveDefaultAttributes, () const, bool), AS_CALL_THISCALL);
    // bool Component::SaveJSON(JSONValue& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("PhysicsWorld", "bool SaveJSON(JSONValue&) const", AS_METHODPR(PhysicsWorld, SaveJSON, (JSONValue&) const, bool), AS_CALL_THISCALL);
    // bool Component::SaveXML(XMLElement& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("PhysicsWorld", "bool SaveXML(XMLElement&) const", AS_METHODPR(PhysicsWorld, SaveXML, (XMLElement&) const, bool), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("PhysicsWorld", "void SendEvent(StringHash)", AS_METHODPR(PhysicsWorld, SendEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("PhysicsWorld", "void SendEvent(StringHash, VariantMap&)", AS_METHODPR(PhysicsWorld, SendEvent, (StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void Animatable::SetAnimationEnabled(bool enable) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("PhysicsWorld", "void SetAnimationEnabled(bool)", AS_METHODPR(PhysicsWorld, SetAnimationEnabled, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("PhysicsWorld", "void set_animationEnabled(bool)", AS_METHODPR(PhysicsWorld, SetAnimationEnabled, (bool), void), AS_CALL_THISCALL);
    // void Animatable::SetAnimationTime(float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("PhysicsWorld", "void SetAnimationTime(float)", AS_METHODPR(PhysicsWorld, SetAnimationTime, (float), void), AS_CALL_THISCALL);
    // void PhysicsWorld::SetApplyingTransforms(bool enable) | File: ../Physics/PhysicsWorld.h
    engine->RegisterObjectMethod("PhysicsWorld", "void SetApplyingTransforms(bool)", AS_METHODPR(PhysicsWorld, SetApplyingTransforms, (bool), void), AS_CALL_THISCALL);
    // bool Serializable::SetAttribute(unsigned index, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("PhysicsWorld", "bool SetAttribute(uint, const Variant&in)", AS_METHODPR(PhysicsWorld, SetAttribute, (unsigned, const Variant&), bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("PhysicsWorld", "bool set_attributes(uint, const Variant&in)", AS_METHODPR(PhysicsWorld, SetAttribute, (unsigned, const Variant&), bool), AS_CALL_THISCALL);
    // bool Serializable::SetAttribute(const String& name, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("PhysicsWorld", "bool SetAttribute(const String&in, const Variant&in)", AS_METHODPR(PhysicsWorld, SetAttribute, (const String&, const Variant&), bool), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimation(const String& name, ValueAnimation* attributeAnimation, WrapMode wrapMode=WM_LOOP, float speed=1.0f) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("PhysicsWorld", "void SetAttributeAnimation(const String&in, ValueAnimation@+, WrapMode = WM_LOOP, float = 1.0f)", AS_METHODPR(PhysicsWorld, SetAttributeAnimation, (const String&, ValueAnimation*, WrapMode, float), void), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimationSpeed(const String& name, float speed) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("PhysicsWorld", "void SetAttributeAnimationSpeed(const String&in, float)", AS_METHODPR(PhysicsWorld, SetAttributeAnimationSpeed, (const String&, float), void), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimationTime(const String& name, float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("PhysicsWorld", "void SetAttributeAnimationTime(const String&in, float)", AS_METHODPR(PhysicsWorld, SetAttributeAnimationTime, (const String&, float), void), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimationWrapMode(const String& name, WrapMode wrapMode) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("PhysicsWorld", "void SetAttributeAnimationWrapMode(const String&in, WrapMode)", AS_METHODPR(PhysicsWorld, SetAttributeAnimationWrapMode, (const String&, WrapMode), void), AS_CALL_THISCALL);
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("PhysicsWorld", "void SetBlockEvents(bool)", AS_METHODPR(PhysicsWorld, SetBlockEvents, (bool), void), AS_CALL_THISCALL);
    // void PhysicsWorld::SetDebugDepthTest(bool enable) | File: ../Physics/PhysicsWorld.h
    engine->RegisterObjectMethod("PhysicsWorld", "void SetDebugDepthTest(bool)", AS_METHODPR(PhysicsWorld, SetDebugDepthTest, (bool), void), AS_CALL_THISCALL);
    // void PhysicsWorld::setDebugMode(int debugMode) override | File: ../Physics/PhysicsWorld.h
    engine->RegisterObjectMethod("PhysicsWorld", "void setDebugMode(int)", AS_METHODPR(PhysicsWorld, setDebugMode, (int), void), AS_CALL_THISCALL);
    // void PhysicsWorld::SetDebugRenderer(DebugRenderer* debug) | File: ../Physics/PhysicsWorld.h
    engine->RegisterObjectMethod("PhysicsWorld", "void SetDebugRenderer(DebugRenderer@+)", AS_METHODPR(PhysicsWorld, SetDebugRenderer, (DebugRenderer*), void), AS_CALL_THISCALL);
    // void Component::SetEnabled(bool enable) | File: ../Scene/Component.h
    engine->RegisterObjectMethod("PhysicsWorld", "void SetEnabled(bool)", AS_METHODPR(PhysicsWorld, SetEnabled, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("PhysicsWorld", "void set_enabled(bool)", AS_METHODPR(PhysicsWorld, SetEnabled, (bool), void), AS_CALL_THISCALL);
    // void PhysicsWorld::SetFps(int fps) | File: ../Physics/PhysicsWorld.h
    engine->RegisterObjectMethod("PhysicsWorld", "void SetFps(int)", AS_METHODPR(PhysicsWorld, SetFps, (int), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("PhysicsWorld", "void set_fps(int)", AS_METHODPR(PhysicsWorld, SetFps, (int), void), AS_CALL_THISCALL);
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("PhysicsWorld", "void SetGlobalVar(StringHash, const Variant&in)", AS_METHODPR(PhysicsWorld, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("PhysicsWorld", "void set_globalVar(StringHash, const Variant&in)", AS_METHODPR(PhysicsWorld, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    // void PhysicsWorld::SetGravity(const Vector3& gravity) | File: ../Physics/PhysicsWorld.h
    engine->RegisterObjectMethod("PhysicsWorld", "void SetGravity(const Vector3&in)", AS_METHODPR(PhysicsWorld, SetGravity, (const Vector3&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("PhysicsWorld", "void set_gravity(const Vector3&in)", AS_METHODPR(PhysicsWorld, SetGravity, (const Vector3&), void), AS_CALL_THISCALL);
    // void Serializable::SetInstanceDefault(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("PhysicsWorld", "void SetInstanceDefault(bool)", AS_METHODPR(PhysicsWorld, SetInstanceDefault, (bool), void), AS_CALL_THISCALL);
    // void Serializable::SetInterceptNetworkUpdate(const String& attributeName, bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("PhysicsWorld", "void SetInterceptNetworkUpdate(const String&in, bool)", AS_METHODPR(PhysicsWorld, SetInterceptNetworkUpdate, (const String&, bool), void), AS_CALL_THISCALL);
    // void PhysicsWorld::SetInternalEdge(bool enable) | File: ../Physics/PhysicsWorld.h
    engine->RegisterObjectMethod("PhysicsWorld", "void SetInternalEdge(bool)", AS_METHODPR(PhysicsWorld, SetInternalEdge, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("PhysicsWorld", "void set_internalEdge(bool)", AS_METHODPR(PhysicsWorld, SetInternalEdge, (bool), void), AS_CALL_THISCALL);
    // void PhysicsWorld::SetInterpolation(bool enable) | File: ../Physics/PhysicsWorld.h
    engine->RegisterObjectMethod("PhysicsWorld", "void SetInterpolation(bool)", AS_METHODPR(PhysicsWorld, SetInterpolation, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("PhysicsWorld", "void set_interpolation(bool)", AS_METHODPR(PhysicsWorld, SetInterpolation, (bool), void), AS_CALL_THISCALL);
    // void PhysicsWorld::SetMaxNetworkAngularVelocity(float velocity) | File: ../Physics/PhysicsWorld.h
    engine->RegisterObjectMethod("PhysicsWorld", "void SetMaxNetworkAngularVelocity(float)", AS_METHODPR(PhysicsWorld, SetMaxNetworkAngularVelocity, (float), void), AS_CALL_THISCALL);
    // void PhysicsWorld::SetMaxSubSteps(int num) | File: ../Physics/PhysicsWorld.h
    engine->RegisterObjectMethod("PhysicsWorld", "void SetMaxSubSteps(int)", AS_METHODPR(PhysicsWorld, SetMaxSubSteps, (int), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("PhysicsWorld", "void set_maxSubSteps(int)", AS_METHODPR(PhysicsWorld, SetMaxSubSteps, (int), void), AS_CALL_THISCALL);
    // void PhysicsWorld::SetNumIterations(int num) | File: ../Physics/PhysicsWorld.h
    engine->RegisterObjectMethod("PhysicsWorld", "void SetNumIterations(int)", AS_METHODPR(PhysicsWorld, SetNumIterations, (int), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("PhysicsWorld", "void set_numIterations(int)", AS_METHODPR(PhysicsWorld, SetNumIterations, (int), void), AS_CALL_THISCALL);
    // void Animatable::SetObjectAnimation(ObjectAnimation* objectAnimation) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("PhysicsWorld", "void SetObjectAnimation(ObjectAnimation@+)", AS_METHODPR(PhysicsWorld, SetObjectAnimation, (ObjectAnimation*), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("PhysicsWorld", "void set_objectAnimation(ObjectAnimation@+)", AS_METHODPR(PhysicsWorld, SetObjectAnimation, (ObjectAnimation*), void), AS_CALL_THISCALL);
    // void Animatable::SetObjectAnimationAttr(const ResourceRef& value) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("PhysicsWorld", "void SetObjectAnimationAttr(const ResourceRef&in)", AS_METHODPR(PhysicsWorld, SetObjectAnimationAttr, (const ResourceRef&), void), AS_CALL_THISCALL);
    // void PhysicsWorld::SetSplitImpulse(bool enable) | File: ../Physics/PhysicsWorld.h
    engine->RegisterObjectMethod("PhysicsWorld", "void SetSplitImpulse(bool)", AS_METHODPR(PhysicsWorld, SetSplitImpulse, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("PhysicsWorld", "void set_splitImpulse(bool)", AS_METHODPR(PhysicsWorld, SetSplitImpulse, (bool), void), AS_CALL_THISCALL);
    // void Serializable::SetTemporary(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("PhysicsWorld", "void SetTemporary(bool)", AS_METHODPR(PhysicsWorld, SetTemporary, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("PhysicsWorld", "void set_temporary(bool)", AS_METHODPR(PhysicsWorld, SetTemporary, (bool), void), AS_CALL_THISCALL);
    // void PhysicsWorld::SetUpdateEnabled(bool enable) | File: ../Physics/PhysicsWorld.h
    engine->RegisterObjectMethod("PhysicsWorld", "void SetUpdateEnabled(bool)", AS_METHODPR(PhysicsWorld, SetUpdateEnabled, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("PhysicsWorld", "void set_updateEnabled(bool)", AS_METHODPR(PhysicsWorld, SetUpdateEnabled, (bool), void), AS_CALL_THISCALL);
    // void PhysicsWorld::SphereCast(PhysicsRaycastResult& result, const Ray& ray, float radius, float maxDistance, unsigned collisionMask=M_MAX_UNSIGNED) | File: ../Physics/PhysicsWorld.h
    engine->RegisterObjectMethod("PhysicsWorld", "void SphereCast(PhysicsRaycastResult&, const Ray&in, float, float, uint = M_MAX_UNSIGNED)", AS_METHODPR(PhysicsWorld, SphereCast, (PhysicsRaycastResult&, const Ray&, float, float, unsigned), void), AS_CALL_THISCALL);
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod("PhysicsWorld", "void UnsubscribeFromAllEvents()", AS_METHODPR(PhysicsWorld, UnsubscribeFromAllEvents, (), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("PhysicsWorld", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", AS_FUNCTION_OBJFIRST(PhysicsWorld_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), AS_CALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("PhysicsWorld", "void UnsubscribeFromEvent(StringHash)", AS_METHODPR(PhysicsWorld, UnsubscribeFromEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("PhysicsWorld", "void UnsubscribeFromEvent(Object@+, StringHash)", AS_METHODPR(PhysicsWorld, UnsubscribeFromEvent, (Object*, StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("PhysicsWorld", "void UnsubscribeFromEvents(Object@+)", AS_METHODPR(PhysicsWorld, UnsubscribeFromEvents, (Object*), void), AS_CALL_THISCALL);
    // void PhysicsWorld::Update(float timeStep) | File: ../Physics/PhysicsWorld.h
    engine->RegisterObjectMethod("PhysicsWorld", "void Update(float)", AS_METHODPR(PhysicsWorld, Update, (float), void), AS_CALL_THISCALL);
    // void PhysicsWorld::UpdateCollisions() | File: ../Physics/PhysicsWorld.h
    engine->RegisterObjectMethod("PhysicsWorld", "void UpdateCollisions()", AS_METHODPR(PhysicsWorld, UpdateCollisions, (), void), AS_CALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("PhysicsWorld", "int WeakRefs() const", AS_METHODPR(PhysicsWorld, WeakRefs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("PhysicsWorld", "int get_weakRefs() const", AS_METHODPR(PhysicsWorld, WeakRefs, () const, int), AS_CALL_THISCALL);
    // void Serializable::WriteDeltaUpdate(Serializer& dest, const DirtyBits& attributeBits, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("PhysicsWorld", "void WriteDeltaUpdate(Serializer&, const DirtyBits&in, uint8)", AS_METHODPR(PhysicsWorld, WriteDeltaUpdate, (Serializer&, const DirtyBits&, unsigned char), void), AS_CALL_THISCALL);
    // void Serializable::WriteInitialDeltaUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("PhysicsWorld", "void WriteInitialDeltaUpdate(Serializer&, uint8)", AS_METHODPR(PhysicsWorld, WriteInitialDeltaUpdate, (Serializer&, unsigned char), void), AS_CALL_THISCALL);
    // void Serializable::WriteLatestDataUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("PhysicsWorld", "void WriteLatestDataUpdate(Serializer&, uint8)", AS_METHODPR(PhysicsWorld, WriteLatestDataUpdate, (Serializer&, unsigned char), void), AS_CALL_THISCALL);
#ifdef REGISTER_MANUAL_PART_Component
    REGISTER_MANUAL_PART_Component(PhysicsWorld, "PhysicsWorld")
#endif
#ifdef REGISTER_MANUAL_PART_Animatable
    REGISTER_MANUAL_PART_Animatable(PhysicsWorld, "PhysicsWorld")
#endif
#ifdef REGISTER_MANUAL_PART_Serializable
    REGISTER_MANUAL_PART_Serializable(PhysicsWorld, "PhysicsWorld")
#endif
#ifdef REGISTER_MANUAL_PART_Object
    REGISTER_MANUAL_PART_Object(PhysicsWorld, "PhysicsWorld")
#endif
#ifdef REGISTER_MANUAL_PART_RefCounted
    REGISTER_MANUAL_PART_RefCounted(PhysicsWorld, "PhysicsWorld")
#endif
#ifdef REGISTER_MANUAL_PART_PhysicsWorld
    REGISTER_MANUAL_PART_PhysicsWorld(PhysicsWorld, "PhysicsWorld")
#endif
    RegisterSubclass<Component, PhysicsWorld>(engine, "Component", "PhysicsWorld");
    RegisterSubclass<Animatable, PhysicsWorld>(engine, "Animatable", "PhysicsWorld");
    RegisterSubclass<Serializable, PhysicsWorld>(engine, "Serializable", "PhysicsWorld");
    RegisterSubclass<Object, PhysicsWorld>(engine, "Object", "PhysicsWorld");
    RegisterSubclass<RefCounted, PhysicsWorld>(engine, "RefCounted", "PhysicsWorld");
#endif

#ifdef URHO3D_URHO2D
    // void PhysicsWorld2D::AddDelayedWorldTransform(const DelayedWorldTransform2D& transform) | File: ../Urho2D/PhysicsWorld2D.h
    engine->RegisterObjectMethod("PhysicsWorld2D", "void AddDelayedWorldTransform(const DelayedWorldTransform2D&in)", AS_METHODPR(PhysicsWorld2D, AddDelayedWorldTransform, (const DelayedWorldTransform2D&), void), AS_CALL_THISCALL);
    // void RefCounted::AddRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("PhysicsWorld2D", asBEHAVE_ADDREF, "void f()", AS_METHODPR(PhysicsWorld2D, AddRef, (), void), AS_CALL_THISCALL);
    // void Component::AddReplicationState(ComponentReplicationState* state) | File: ../Scene/Component.h
    // Error: type "ComponentReplicationState*" can not automatically bind
    // void PhysicsWorld2D::AddRigidBody(RigidBody2D* rigidBody) | File: ../Urho2D/PhysicsWorld2D.h
    engine->RegisterObjectMethod("PhysicsWorld2D", "void AddRigidBody(RigidBody2D@+)", AS_METHODPR(PhysicsWorld2D, AddRigidBody, (RigidBody2D*), void), AS_CALL_THISCALL);
    // void Serializable::AllocateNetworkState() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("PhysicsWorld2D", "void AllocateNetworkState()", AS_METHODPR(PhysicsWorld2D, AllocateNetworkState, (), void), AS_CALL_THISCALL);
    // virtual void Serializable::ApplyAttributes() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("PhysicsWorld2D", "void ApplyAttributes()", AS_METHODPR(PhysicsWorld2D, ApplyAttributes, (), void), AS_CALL_THISCALL);
    // void PhysicsWorld2D::BeginContact(b2Contact* contact) override | File: ../Urho2D/PhysicsWorld2D.h
    // Error: type "b2Contact*" can not automatically bind
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // void Component::CleanupConnection(Connection* connection) | File: ../Scene/Component.h
    // Not registered because have @manualbind mark
    // void PhysicsWorld2D::DrawCircle(const b2Vec2& center, float32 radius, const b2Color& color) override | File: ../Urho2D/PhysicsWorld2D.h
    // Error: type "const b2Vec2&" can not automatically bind
    // void PhysicsWorld2D::DrawDebugGeometry(DebugRenderer* debug, bool depthTest) override | File: ../Urho2D/PhysicsWorld2D.h
    engine->RegisterObjectMethod("PhysicsWorld2D", "void DrawDebugGeometry(DebugRenderer@+, bool)", AS_METHODPR(PhysicsWorld2D, DrawDebugGeometry, (DebugRenderer*, bool), void), AS_CALL_THISCALL);
    // void PhysicsWorld2D::DrawDebugGeometry() | File: ../Urho2D/PhysicsWorld2D.h
    engine->RegisterObjectMethod("PhysicsWorld2D", "void DrawDebugGeometry()", AS_METHODPR(PhysicsWorld2D, DrawDebugGeometry, (), void), AS_CALL_THISCALL);
    // void PhysicsWorld2D::DrawPoint(const b2Vec2& p, float32 size, const b2Color& color) override | File: ../Urho2D/PhysicsWorld2D.h
    // Error: type "const b2Vec2&" can not automatically bind
    // void PhysicsWorld2D::DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color) override | File: ../Urho2D/PhysicsWorld2D.h
    // Error: type "const b2Vec2*" can not automatically bind
    // void PhysicsWorld2D::DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color) override | File: ../Urho2D/PhysicsWorld2D.h
    // Error: type "const b2Vec2&" can not automatically bind
    // void PhysicsWorld2D::DrawSolidCircle(const b2Vec2& center, float32 radius, const b2Vec2& axis, const b2Color& color) override | File: ../Urho2D/PhysicsWorld2D.h
    // Error: type "const b2Vec2&" can not automatically bind
    // void PhysicsWorld2D::DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color) override | File: ../Urho2D/PhysicsWorld2D.h
    // Error: type "const b2Vec2*" can not automatically bind
    // void PhysicsWorld2D::DrawTransform(const b2Transform& xf) override | File: ../Urho2D/PhysicsWorld2D.h
    // Error: type "const b2Transform&" can not automatically bind
    // void PhysicsWorld2D::EndContact(b2Contact* contact) override | File: ../Urho2D/PhysicsWorld2D.h
    // Error: type "b2Contact*" can not automatically bind
    // bool PhysicsWorld2D::GetAllowSleeping() const | File: ../Urho2D/PhysicsWorld2D.h
    engine->RegisterObjectMethod("PhysicsWorld2D", "bool GetAllowSleeping() const", AS_METHODPR(PhysicsWorld2D, GetAllowSleeping, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("PhysicsWorld2D", "bool get_allowSleeping() const", AS_METHODPR(PhysicsWorld2D, GetAllowSleeping, () const, bool), AS_CALL_THISCALL);
    // bool Animatable::GetAnimationEnabled() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("PhysicsWorld2D", "bool GetAnimationEnabled() const", AS_METHODPR(PhysicsWorld2D, GetAnimationEnabled, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("PhysicsWorld2D", "bool get_animationEnabled() const", AS_METHODPR(PhysicsWorld2D, GetAnimationEnabled, () const, bool), AS_CALL_THISCALL);
    // Variant Serializable::GetAttribute(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("PhysicsWorld2D", "Variant GetAttribute(uint) const", AS_METHODPR(PhysicsWorld2D, GetAttribute, (unsigned) const, Variant), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("PhysicsWorld2D", "Variant get_attributes(uint) const", AS_METHODPR(PhysicsWorld2D, GetAttribute, (unsigned) const, Variant), AS_CALL_THISCALL);
    // Variant Serializable::GetAttribute(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("PhysicsWorld2D", "Variant GetAttribute(const String&in) const", AS_METHODPR(PhysicsWorld2D, GetAttribute, (const String&) const, Variant), AS_CALL_THISCALL);
    // ValueAnimation* Animatable::GetAttributeAnimation(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("PhysicsWorld2D", "ValueAnimation@+ GetAttributeAnimation(const String&in) const", AS_METHODPR(PhysicsWorld2D, GetAttributeAnimation, (const String&) const, ValueAnimation*), AS_CALL_THISCALL);
    // float Animatable::GetAttributeAnimationSpeed(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("PhysicsWorld2D", "float GetAttributeAnimationSpeed(const String&in) const", AS_METHODPR(PhysicsWorld2D, GetAttributeAnimationSpeed, (const String&) const, float), AS_CALL_THISCALL);
    // float Animatable::GetAttributeAnimationTime(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("PhysicsWorld2D", "float GetAttributeAnimationTime(const String&in) const", AS_METHODPR(PhysicsWorld2D, GetAttributeAnimationTime, (const String&) const, float), AS_CALL_THISCALL);
    // WrapMode Animatable::GetAttributeAnimationWrapMode(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("PhysicsWorld2D", "WrapMode GetAttributeAnimationWrapMode(const String&in) const", AS_METHODPR(PhysicsWorld2D, GetAttributeAnimationWrapMode, (const String&) const, WrapMode), AS_CALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("PhysicsWorld2D", "Variant GetAttributeDefault(uint) const", AS_METHODPR(PhysicsWorld2D, GetAttributeDefault, (unsigned) const, Variant), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("PhysicsWorld2D", "Variant get_attributeDefaults(uint) const", AS_METHODPR(PhysicsWorld2D, GetAttributeDefault, (unsigned) const, Variant), AS_CALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("PhysicsWorld2D", "Variant GetAttributeDefault(const String&in) const", AS_METHODPR(PhysicsWorld2D, GetAttributeDefault, (const String&) const, Variant), AS_CALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // bool PhysicsWorld2D::GetAutoClearForces() const | File: ../Urho2D/PhysicsWorld2D.h
    engine->RegisterObjectMethod("PhysicsWorld2D", "bool GetAutoClearForces() const", AS_METHODPR(PhysicsWorld2D, GetAutoClearForces, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("PhysicsWorld2D", "bool get_autoClearForces() const", AS_METHODPR(PhysicsWorld2D, GetAutoClearForces, () const, bool), AS_CALL_THISCALL);
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("PhysicsWorld2D", "bool GetBlockEvents() const", AS_METHODPR(PhysicsWorld2D, GetBlockEvents, () const, bool), AS_CALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("PhysicsWorld2D", "const String& GetCategory() const", AS_METHODPR(PhysicsWorld2D, GetCategory, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("PhysicsWorld2D", "const String& get_category() const", AS_METHODPR(PhysicsWorld2D, GetCategory, () const, const String&), AS_CALL_THISCALL);
    // Component* Component::GetComponent(StringHash type) const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("PhysicsWorld2D", "Component@+ GetComponent(StringHash) const", AS_METHODPR(PhysicsWorld2D, GetComponent, (StringHash) const, Component*), AS_CALL_THISCALL);
    // template<class T> T* Component::GetComponent() const | File: ../Scene/Component.h
    // Not registered because template
    // void Component::GetComponents(PODVector<Component*>& dest, StringHash type) const | File: ../Scene/Component.h
    // Error: type "PODVector<Component*>&" can not automatically bind
    // template<class T> void Component::GetComponents(PODVector<T*>& dest) const | File: ../Scene/Component.h
    // Not registered because template
    // Context* Object::GetContext() const | File: ../Core/Object.h
    // Error: type "Context*" can used only as function parameter
    // bool PhysicsWorld2D::GetContinuousPhysics() const | File: ../Urho2D/PhysicsWorld2D.h
    engine->RegisterObjectMethod("PhysicsWorld2D", "bool GetContinuousPhysics() const", AS_METHODPR(PhysicsWorld2D, GetContinuousPhysics, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("PhysicsWorld2D", "bool get_continuousPhysics() const", AS_METHODPR(PhysicsWorld2D, GetContinuousPhysics, () const, bool), AS_CALL_THISCALL);
    // virtual void Component::GetDependencyNodes(PODVector<Node*>& dest) | File: ../Scene/Component.h
    // Error: type "PODVector<Node*>&" can not automatically bind
    // bool PhysicsWorld2D::GetDrawAabb() const | File: ../Urho2D/PhysicsWorld2D.h
    engine->RegisterObjectMethod("PhysicsWorld2D", "bool GetDrawAabb() const", AS_METHODPR(PhysicsWorld2D, GetDrawAabb, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("PhysicsWorld2D", "bool get_drawAabb() const", AS_METHODPR(PhysicsWorld2D, GetDrawAabb, () const, bool), AS_CALL_THISCALL);
    // bool PhysicsWorld2D::GetDrawCenterOfMass() const | File: ../Urho2D/PhysicsWorld2D.h
    engine->RegisterObjectMethod("PhysicsWorld2D", "bool GetDrawCenterOfMass() const", AS_METHODPR(PhysicsWorld2D, GetDrawCenterOfMass, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("PhysicsWorld2D", "bool get_drawCenterOfMass() const", AS_METHODPR(PhysicsWorld2D, GetDrawCenterOfMass, () const, bool), AS_CALL_THISCALL);
    // bool PhysicsWorld2D::GetDrawJoint() const | File: ../Urho2D/PhysicsWorld2D.h
    engine->RegisterObjectMethod("PhysicsWorld2D", "bool GetDrawJoint() const", AS_METHODPR(PhysicsWorld2D, GetDrawJoint, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("PhysicsWorld2D", "bool get_drawJoint() const", AS_METHODPR(PhysicsWorld2D, GetDrawJoint, () const, bool), AS_CALL_THISCALL);
    // bool PhysicsWorld2D::GetDrawPair() const | File: ../Urho2D/PhysicsWorld2D.h
    engine->RegisterObjectMethod("PhysicsWorld2D", "bool GetDrawPair() const", AS_METHODPR(PhysicsWorld2D, GetDrawPair, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("PhysicsWorld2D", "bool get_drawPair() const", AS_METHODPR(PhysicsWorld2D, GetDrawPair, () const, bool), AS_CALL_THISCALL);
    // bool PhysicsWorld2D::GetDrawShape() const | File: ../Urho2D/PhysicsWorld2D.h
    engine->RegisterObjectMethod("PhysicsWorld2D", "bool GetDrawShape() const", AS_METHODPR(PhysicsWorld2D, GetDrawShape, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("PhysicsWorld2D", "bool get_drawShape() const", AS_METHODPR(PhysicsWorld2D, GetDrawShape, () const, bool), AS_CALL_THISCALL);
    // VariantMap& Object::GetEventDataMap() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("PhysicsWorld2D", "VariantMap& GetEventDataMap() const", AS_METHODPR(PhysicsWorld2D, GetEventDataMap, () const, VariantMap&), AS_CALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("PhysicsWorld2D", "Object@+ GetEventSender() const", AS_METHODPR(PhysicsWorld2D, GetEventSender, () const, Object*), AS_CALL_THISCALL);
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("PhysicsWorld2D", "const Variant& GetGlobalVar(StringHash) const", AS_METHODPR(PhysicsWorld2D, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("PhysicsWorld2D", "const Variant& get_globalVar(StringHash) const", AS_METHODPR(PhysicsWorld2D, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("PhysicsWorld2D", "const VariantMap& GetGlobalVars() const", AS_METHODPR(PhysicsWorld2D, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("PhysicsWorld2D", "const VariantMap& get_globalVars() const", AS_METHODPR(PhysicsWorld2D, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    // const Vector2& PhysicsWorld2D::GetGravity() const | File: ../Urho2D/PhysicsWorld2D.h
    engine->RegisterObjectMethod("PhysicsWorld2D", "const Vector2& GetGravity() const", AS_METHODPR(PhysicsWorld2D, GetGravity, () const, const Vector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("PhysicsWorld2D", "const Vector2& get_gravity() const", AS_METHODPR(PhysicsWorld2D, GetGravity, () const, const Vector2&), AS_CALL_THISCALL);
    // unsigned Component::GetID() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("PhysicsWorld2D", "uint GetID() const", AS_METHODPR(PhysicsWorld2D, GetID, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("PhysicsWorld2D", "uint get_id() const", AS_METHODPR(PhysicsWorld2D, GetID, () const, unsigned), AS_CALL_THISCALL);
    // bool Serializable::GetInterceptNetworkUpdate(const String& attributeName) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("PhysicsWorld2D", "bool GetInterceptNetworkUpdate(const String&in) const", AS_METHODPR(PhysicsWorld2D, GetInterceptNetworkUpdate, (const String&) const, bool), AS_CALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetNetworkAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // NetworkState* Serializable::GetNetworkState() const | File: ../Scene/Serializable.h
    // Error: type "NetworkState*" can not automatically bind
    // Node* Component::GetNode() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("PhysicsWorld2D", "Node@+ GetNode() const", AS_METHODPR(PhysicsWorld2D, GetNode, () const, Node*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("PhysicsWorld2D", "Node@+ get_node() const", AS_METHODPR(PhysicsWorld2D, GetNode, () const, Node*), AS_CALL_THISCALL);
    // unsigned Serializable::GetNumAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("PhysicsWorld2D", "uint GetNumAttributes() const", AS_METHODPR(PhysicsWorld2D, GetNumAttributes, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("PhysicsWorld2D", "uint get_numAttributes() const", AS_METHODPR(PhysicsWorld2D, GetNumAttributes, () const, unsigned), AS_CALL_THISCALL);
    // unsigned Serializable::GetNumNetworkAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("PhysicsWorld2D", "uint GetNumNetworkAttributes() const", AS_METHODPR(PhysicsWorld2D, GetNumNetworkAttributes, () const, unsigned), AS_CALL_THISCALL);
    // ObjectAnimation* Animatable::GetObjectAnimation() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("PhysicsWorld2D", "ObjectAnimation@+ GetObjectAnimation() const", AS_METHODPR(PhysicsWorld2D, GetObjectAnimation, () const, ObjectAnimation*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("PhysicsWorld2D", "ObjectAnimation@+ get_objectAnimation() const", AS_METHODPR(PhysicsWorld2D, GetObjectAnimation, () const, ObjectAnimation*), AS_CALL_THISCALL);
    // ResourceRef Animatable::GetObjectAnimationAttr() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("PhysicsWorld2D", "ResourceRef GetObjectAnimationAttr() const", AS_METHODPR(PhysicsWorld2D, GetObjectAnimationAttr, () const, ResourceRef), AS_CALL_THISCALL);
    // int PhysicsWorld2D::GetPositionIterations() const | File: ../Urho2D/PhysicsWorld2D.h
    engine->RegisterObjectMethod("PhysicsWorld2D", "int GetPositionIterations() const", AS_METHODPR(PhysicsWorld2D, GetPositionIterations, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("PhysicsWorld2D", "int get_positionIterations() const", AS_METHODPR(PhysicsWorld2D, GetPositionIterations, () const, int), AS_CALL_THISCALL);
    // void PhysicsWorld2D::GetRigidBodies(PODVector<RigidBody2D*>& results, const Rect& aabb, unsigned collisionMask=M_MAX_UNSIGNED) | File: ../Urho2D/PhysicsWorld2D.h
    // Error: type "PODVector<RigidBody2D*>&" can not automatically bind
    // RigidBody2D* PhysicsWorld2D::GetRigidBody(const Vector2& point, unsigned collisionMask=M_MAX_UNSIGNED) | File: ../Urho2D/PhysicsWorld2D.h
    engine->RegisterObjectMethod("PhysicsWorld2D", "RigidBody2D@+ GetRigidBody(const Vector2&in, uint = M_MAX_UNSIGNED)", AS_METHODPR(PhysicsWorld2D, GetRigidBody, (const Vector2&, unsigned), RigidBody2D*), AS_CALL_THISCALL);
    // RigidBody2D* PhysicsWorld2D::GetRigidBody(int screenX, int screenY, unsigned collisionMask=M_MAX_UNSIGNED) | File: ../Urho2D/PhysicsWorld2D.h
    engine->RegisterObjectMethod("PhysicsWorld2D", "RigidBody2D@+ GetRigidBody(int, int, uint = M_MAX_UNSIGNED)", AS_METHODPR(PhysicsWorld2D, GetRigidBody, (int, int, unsigned), RigidBody2D*), AS_CALL_THISCALL);
    // Scene* Component::GetScene() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("PhysicsWorld2D", "Scene@+ GetScene() const", AS_METHODPR(PhysicsWorld2D, GetScene, () const, Scene*), AS_CALL_THISCALL);
    // bool PhysicsWorld2D::GetSubStepping() const | File: ../Urho2D/PhysicsWorld2D.h
    engine->RegisterObjectMethod("PhysicsWorld2D", "bool GetSubStepping() const", AS_METHODPR(PhysicsWorld2D, GetSubStepping, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("PhysicsWorld2D", "bool get_subStepping() const", AS_METHODPR(PhysicsWorld2D, GetSubStepping, () const, bool), AS_CALL_THISCALL);
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("PhysicsWorld2D", "Object@+ GetSubsystem(StringHash) const", AS_METHODPR(PhysicsWorld2D, GetSubsystem, (StringHash) const, Object*), AS_CALL_THISCALL);
    // template<class T> T* Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("PhysicsWorld2D", "StringHash GetType() const", AS_METHODPR(PhysicsWorld2D, GetType, () const, StringHash), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("PhysicsWorld2D", "StringHash get_type() const", AS_METHODPR(PhysicsWorld2D, GetType, () const, StringHash), AS_CALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("PhysicsWorld2D", "const String& GetTypeName() const", AS_METHODPR(PhysicsWorld2D, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("PhysicsWorld2D", "const String& get_typeName() const", AS_METHODPR(PhysicsWorld2D, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    // int PhysicsWorld2D::GetVelocityIterations() const | File: ../Urho2D/PhysicsWorld2D.h
    engine->RegisterObjectMethod("PhysicsWorld2D", "int GetVelocityIterations() const", AS_METHODPR(PhysicsWorld2D, GetVelocityIterations, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("PhysicsWorld2D", "int get_velocityIterations() const", AS_METHODPR(PhysicsWorld2D, GetVelocityIterations, () const, int), AS_CALL_THISCALL);
    // bool PhysicsWorld2D::GetWarmStarting() const | File: ../Urho2D/PhysicsWorld2D.h
    engine->RegisterObjectMethod("PhysicsWorld2D", "bool GetWarmStarting() const", AS_METHODPR(PhysicsWorld2D, GetWarmStarting, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("PhysicsWorld2D", "bool get_warmStarting() const", AS_METHODPR(PhysicsWorld2D, GetWarmStarting, () const, bool), AS_CALL_THISCALL);
    // b2World* PhysicsWorld2D::GetWorld() | File: ../Urho2D/PhysicsWorld2D.h
    // Error: type "b2World*" can not automatically bind
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("PhysicsWorld2D", "bool HasEventHandlers() const", AS_METHODPR(PhysicsWorld2D, HasEventHandlers, () const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("PhysicsWorld2D", "bool HasSubscribedToEvent(StringHash) const", AS_METHODPR(PhysicsWorld2D, HasSubscribedToEvent, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("PhysicsWorld2D", "bool HasSubscribedToEvent(Object@+, StringHash) const", AS_METHODPR(PhysicsWorld2D, HasSubscribedToEvent, (Object*, StringHash) const, bool), AS_CALL_THISCALL);
    // bool PhysicsWorld2D::IsApplyingTransforms() const | File: ../Urho2D/PhysicsWorld2D.h
    engine->RegisterObjectMethod("PhysicsWorld2D", "bool IsApplyingTransforms() const", AS_METHODPR(PhysicsWorld2D, IsApplyingTransforms, () const, bool), AS_CALL_THISCALL);
    // bool Component::IsEnabled() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("PhysicsWorld2D", "bool IsEnabled() const", AS_METHODPR(PhysicsWorld2D, IsEnabled, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("PhysicsWorld2D", "bool get_enabled() const", AS_METHODPR(PhysicsWorld2D, IsEnabled, () const, bool), AS_CALL_THISCALL);
    // bool Component::IsEnabledEffective() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("PhysicsWorld2D", "bool IsEnabledEffective() const", AS_METHODPR(PhysicsWorld2D, IsEnabledEffective, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("PhysicsWorld2D", "bool get_enabledEffective() const", AS_METHODPR(PhysicsWorld2D, IsEnabledEffective, () const, bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("PhysicsWorld2D", "bool IsInstanceOf(StringHash) const", AS_METHODPR(PhysicsWorld2D, IsInstanceOf, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // bool Component::IsReplicated() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("PhysicsWorld2D", "bool IsReplicated() const", AS_METHODPR(PhysicsWorld2D, IsReplicated, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("PhysicsWorld2D", "bool get_replicated() const", AS_METHODPR(PhysicsWorld2D, IsReplicated, () const, bool), AS_CALL_THISCALL);
    // bool Serializable::IsTemporary() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("PhysicsWorld2D", "bool IsTemporary() const", AS_METHODPR(PhysicsWorld2D, IsTemporary, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("PhysicsWorld2D", "bool get_temporary() const", AS_METHODPR(PhysicsWorld2D, IsTemporary, () const, bool), AS_CALL_THISCALL);
    // bool PhysicsWorld2D::IsUpdateEnabled() const | File: ../Urho2D/PhysicsWorld2D.h
    engine->RegisterObjectMethod("PhysicsWorld2D", "bool IsUpdateEnabled() const", AS_METHODPR(PhysicsWorld2D, IsUpdateEnabled, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("PhysicsWorld2D", "bool get_updateEnabled() const", AS_METHODPR(PhysicsWorld2D, IsUpdateEnabled, () const, bool), AS_CALL_THISCALL);
    // virtual bool Serializable::Load(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("PhysicsWorld2D", "bool Load(Deserializer&)", AS_METHODPR(PhysicsWorld2D, Load, (Deserializer&), bool), AS_CALL_THISCALL);
    // bool Animatable::LoadJSON(const JSONValue& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("PhysicsWorld2D", "bool LoadJSON(const JSONValue&in)", AS_METHODPR(PhysicsWorld2D, LoadJSON, (const JSONValue&), bool), AS_CALL_THISCALL);
    // bool Animatable::LoadXML(const XMLElement& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("PhysicsWorld2D", "bool LoadXML(const XMLElement&in)", AS_METHODPR(PhysicsWorld2D, LoadXML, (const XMLElement&), bool), AS_CALL_THISCALL);
    // void Component::MarkNetworkUpdate() override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("PhysicsWorld2D", "void MarkNetworkUpdate()", AS_METHODPR(PhysicsWorld2D, MarkNetworkUpdate, (), void), AS_CALL_THISCALL);
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("PhysicsWorld2D", "void OnEvent(Object@+, StringHash, VariantMap&)", AS_METHODPR(PhysicsWorld2D, OnEvent, (Object*, StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // virtual void Serializable::OnGetAttribute(const AttributeInfo& attr, Variant& dest) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("PhysicsWorld2D", "void OnGetAttribute(const AttributeInfo&in, Variant&) const", AS_METHODPR(PhysicsWorld2D, OnGetAttribute, (const AttributeInfo&, Variant&) const, void), AS_CALL_THISCALL);
    // virtual void Serializable::OnSetAttribute(const AttributeInfo& attr, const Variant& src) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("PhysicsWorld2D", "void OnSetAttribute(const AttributeInfo&in, const Variant&in)", AS_METHODPR(PhysicsWorld2D, OnSetAttribute, (const AttributeInfo&, const Variant&), void), AS_CALL_THISCALL);
    // virtual void Component::OnSetEnabled() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("PhysicsWorld2D", "void OnSetEnabled()", AS_METHODPR(PhysicsWorld2D, OnSetEnabled, (), void), AS_CALL_THISCALL);
    // explicit PhysicsWorld2D::PhysicsWorld2D(Context* context) | File: ../Urho2D/PhysicsWorld2D.h
    engine->RegisterObjectBehaviour("PhysicsWorld2D", asBEHAVE_FACTORY, "PhysicsWorld2D@+ f()", AS_FUNCTION(PhysicsWorld2D_PhysicsWorld2D_Context), AS_CALL_CDECL);
    // void Component::PrepareNetworkUpdate() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("PhysicsWorld2D", "void PrepareNetworkUpdate()", AS_METHODPR(PhysicsWorld2D, PrepareNetworkUpdate, (), void), AS_CALL_THISCALL);
    // void PhysicsWorld2D::PreSolve(b2Contact* contact, const b2Manifold* oldManifold) override | File: ../Urho2D/PhysicsWorld2D.h
    // Error: type "b2Contact*" can not automatically bind
    // void PhysicsWorld2D::Raycast(PODVector<PhysicsRaycastResult2D>& results, const Vector2& startPoint, const Vector2& endPoint, unsigned collisionMask=M_MAX_UNSIGNED) | File: ../Urho2D/PhysicsWorld2D.h
    // Error: type "PODVector<PhysicsRaycastResult2D>&" can not automatically bind
    // void PhysicsWorld2D::RaycastSingle(PhysicsRaycastResult2D& result, const Vector2& startPoint, const Vector2& endPoint, unsigned collisionMask=M_MAX_UNSIGNED) | File: ../Urho2D/PhysicsWorld2D.h
    engine->RegisterObjectMethod("PhysicsWorld2D", "void RaycastSingle(PhysicsRaycastResult2D&, const Vector2&in, const Vector2&in, uint = M_MAX_UNSIGNED)", AS_METHODPR(PhysicsWorld2D, RaycastSingle, (PhysicsRaycastResult2D&, const Vector2&, const Vector2&, unsigned), void), AS_CALL_THISCALL);
    // bool Serializable::ReadDeltaUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("PhysicsWorld2D", "bool ReadDeltaUpdate(Deserializer&)", AS_METHODPR(PhysicsWorld2D, ReadDeltaUpdate, (Deserializer&), bool), AS_CALL_THISCALL);
    // bool Serializable::ReadLatestDataUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("PhysicsWorld2D", "bool ReadLatestDataUpdate(Deserializer&)", AS_METHODPR(PhysicsWorld2D, ReadLatestDataUpdate, (Deserializer&), bool), AS_CALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("PhysicsWorld2D", "int Refs() const", AS_METHODPR(PhysicsWorld2D, Refs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("PhysicsWorld2D", "int get_refs() const", AS_METHODPR(PhysicsWorld2D, Refs, () const, int), AS_CALL_THISCALL);
    // static void PhysicsWorld2D::RegisterObject(Context* context) | File: ../Urho2D/PhysicsWorld2D.h
    // Not registered because have @nobind mark
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("PhysicsWorld2D", asBEHAVE_RELEASE, "void f()", AS_METHODPR(PhysicsWorld2D, ReleaseRef, (), void), AS_CALL_THISCALL);
    // void Component::Remove() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("PhysicsWorld2D", "void Remove()", AS_METHODPR(PhysicsWorld2D, Remove, (), void), AS_CALL_THISCALL);
    // void Animatable::RemoveAttributeAnimation(const String& name) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("PhysicsWorld2D", "void RemoveAttributeAnimation(const String&in)", AS_METHODPR(PhysicsWorld2D, RemoveAttributeAnimation, (const String&), void), AS_CALL_THISCALL);
    // void Serializable::RemoveInstanceDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("PhysicsWorld2D", "void RemoveInstanceDefault()", AS_METHODPR(PhysicsWorld2D, RemoveInstanceDefault, (), void), AS_CALL_THISCALL);
    // void Animatable::RemoveObjectAnimation() | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("PhysicsWorld2D", "void RemoveObjectAnimation()", AS_METHODPR(PhysicsWorld2D, RemoveObjectAnimation, (), void), AS_CALL_THISCALL);
    // void PhysicsWorld2D::RemoveRigidBody(RigidBody2D* rigidBody) | File: ../Urho2D/PhysicsWorld2D.h
    engine->RegisterObjectMethod("PhysicsWorld2D", "void RemoveRigidBody(RigidBody2D@+)", AS_METHODPR(PhysicsWorld2D, RemoveRigidBody, (RigidBody2D*), void), AS_CALL_THISCALL);
    // void Serializable::ResetToDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("PhysicsWorld2D", "void ResetToDefault()", AS_METHODPR(PhysicsWorld2D, ResetToDefault, (), void), AS_CALL_THISCALL);
    // bool Component::Save(Serializer& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("PhysicsWorld2D", "bool Save(Serializer&) const", AS_METHODPR(PhysicsWorld2D, Save, (Serializer&) const, bool), AS_CALL_THISCALL);
    // virtual bool Serializable::SaveDefaultAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("PhysicsWorld2D", "bool SaveDefaultAttributes() const", AS_METHODPR(PhysicsWorld2D, SaveDefaultAttributes, () const, bool), AS_CALL_THISCALL);
    // bool Component::SaveJSON(JSONValue& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("PhysicsWorld2D", "bool SaveJSON(JSONValue&) const", AS_METHODPR(PhysicsWorld2D, SaveJSON, (JSONValue&) const, bool), AS_CALL_THISCALL);
    // bool Component::SaveXML(XMLElement& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("PhysicsWorld2D", "bool SaveXML(XMLElement&) const", AS_METHODPR(PhysicsWorld2D, SaveXML, (XMLElement&) const, bool), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("PhysicsWorld2D", "void SendEvent(StringHash)", AS_METHODPR(PhysicsWorld2D, SendEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("PhysicsWorld2D", "void SendEvent(StringHash, VariantMap&)", AS_METHODPR(PhysicsWorld2D, SendEvent, (StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void PhysicsWorld2D::SetAllowSleeping(bool enable) | File: ../Urho2D/PhysicsWorld2D.h
    engine->RegisterObjectMethod("PhysicsWorld2D", "void SetAllowSleeping(bool)", AS_METHODPR(PhysicsWorld2D, SetAllowSleeping, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("PhysicsWorld2D", "void set_allowSleeping(bool)", AS_METHODPR(PhysicsWorld2D, SetAllowSleeping, (bool), void), AS_CALL_THISCALL);
    // void Animatable::SetAnimationEnabled(bool enable) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("PhysicsWorld2D", "void SetAnimationEnabled(bool)", AS_METHODPR(PhysicsWorld2D, SetAnimationEnabled, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("PhysicsWorld2D", "void set_animationEnabled(bool)", AS_METHODPR(PhysicsWorld2D, SetAnimationEnabled, (bool), void), AS_CALL_THISCALL);
    // void Animatable::SetAnimationTime(float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("PhysicsWorld2D", "void SetAnimationTime(float)", AS_METHODPR(PhysicsWorld2D, SetAnimationTime, (float), void), AS_CALL_THISCALL);
    // void PhysicsWorld2D::SetApplyingTransforms(bool enable) | File: ../Urho2D/PhysicsWorld2D.h
    engine->RegisterObjectMethod("PhysicsWorld2D", "void SetApplyingTransforms(bool)", AS_METHODPR(PhysicsWorld2D, SetApplyingTransforms, (bool), void), AS_CALL_THISCALL);
    // bool Serializable::SetAttribute(unsigned index, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("PhysicsWorld2D", "bool SetAttribute(uint, const Variant&in)", AS_METHODPR(PhysicsWorld2D, SetAttribute, (unsigned, const Variant&), bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("PhysicsWorld2D", "bool set_attributes(uint, const Variant&in)", AS_METHODPR(PhysicsWorld2D, SetAttribute, (unsigned, const Variant&), bool), AS_CALL_THISCALL);
    // bool Serializable::SetAttribute(const String& name, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("PhysicsWorld2D", "bool SetAttribute(const String&in, const Variant&in)", AS_METHODPR(PhysicsWorld2D, SetAttribute, (const String&, const Variant&), bool), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimation(const String& name, ValueAnimation* attributeAnimation, WrapMode wrapMode=WM_LOOP, float speed=1.0f) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("PhysicsWorld2D", "void SetAttributeAnimation(const String&in, ValueAnimation@+, WrapMode = WM_LOOP, float = 1.0f)", AS_METHODPR(PhysicsWorld2D, SetAttributeAnimation, (const String&, ValueAnimation*, WrapMode, float), void), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimationSpeed(const String& name, float speed) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("PhysicsWorld2D", "void SetAttributeAnimationSpeed(const String&in, float)", AS_METHODPR(PhysicsWorld2D, SetAttributeAnimationSpeed, (const String&, float), void), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimationTime(const String& name, float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("PhysicsWorld2D", "void SetAttributeAnimationTime(const String&in, float)", AS_METHODPR(PhysicsWorld2D, SetAttributeAnimationTime, (const String&, float), void), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimationWrapMode(const String& name, WrapMode wrapMode) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("PhysicsWorld2D", "void SetAttributeAnimationWrapMode(const String&in, WrapMode)", AS_METHODPR(PhysicsWorld2D, SetAttributeAnimationWrapMode, (const String&, WrapMode), void), AS_CALL_THISCALL);
    // void PhysicsWorld2D::SetAutoClearForces(bool enable) | File: ../Urho2D/PhysicsWorld2D.h
    engine->RegisterObjectMethod("PhysicsWorld2D", "void SetAutoClearForces(bool)", AS_METHODPR(PhysicsWorld2D, SetAutoClearForces, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("PhysicsWorld2D", "void set_autoClearForces(bool)", AS_METHODPR(PhysicsWorld2D, SetAutoClearForces, (bool), void), AS_CALL_THISCALL);
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("PhysicsWorld2D", "void SetBlockEvents(bool)", AS_METHODPR(PhysicsWorld2D, SetBlockEvents, (bool), void), AS_CALL_THISCALL);
    // void PhysicsWorld2D::SetContinuousPhysics(bool enable) | File: ../Urho2D/PhysicsWorld2D.h
    engine->RegisterObjectMethod("PhysicsWorld2D", "void SetContinuousPhysics(bool)", AS_METHODPR(PhysicsWorld2D, SetContinuousPhysics, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("PhysicsWorld2D", "void set_continuousPhysics(bool)", AS_METHODPR(PhysicsWorld2D, SetContinuousPhysics, (bool), void), AS_CALL_THISCALL);
    // void PhysicsWorld2D::SetDrawAabb(bool drawAabb) | File: ../Urho2D/PhysicsWorld2D.h
    engine->RegisterObjectMethod("PhysicsWorld2D", "void SetDrawAabb(bool)", AS_METHODPR(PhysicsWorld2D, SetDrawAabb, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("PhysicsWorld2D", "void set_drawAabb(bool)", AS_METHODPR(PhysicsWorld2D, SetDrawAabb, (bool), void), AS_CALL_THISCALL);
    // void PhysicsWorld2D::SetDrawCenterOfMass(bool drawCenterOfMass) | File: ../Urho2D/PhysicsWorld2D.h
    engine->RegisterObjectMethod("PhysicsWorld2D", "void SetDrawCenterOfMass(bool)", AS_METHODPR(PhysicsWorld2D, SetDrawCenterOfMass, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("PhysicsWorld2D", "void set_drawCenterOfMass(bool)", AS_METHODPR(PhysicsWorld2D, SetDrawCenterOfMass, (bool), void), AS_CALL_THISCALL);
    // void PhysicsWorld2D::SetDrawJoint(bool drawJoint) | File: ../Urho2D/PhysicsWorld2D.h
    engine->RegisterObjectMethod("PhysicsWorld2D", "void SetDrawJoint(bool)", AS_METHODPR(PhysicsWorld2D, SetDrawJoint, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("PhysicsWorld2D", "void set_drawJoint(bool)", AS_METHODPR(PhysicsWorld2D, SetDrawJoint, (bool), void), AS_CALL_THISCALL);
    // void PhysicsWorld2D::SetDrawPair(bool drawPair) | File: ../Urho2D/PhysicsWorld2D.h
    engine->RegisterObjectMethod("PhysicsWorld2D", "void SetDrawPair(bool)", AS_METHODPR(PhysicsWorld2D, SetDrawPair, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("PhysicsWorld2D", "void set_drawPair(bool)", AS_METHODPR(PhysicsWorld2D, SetDrawPair, (bool), void), AS_CALL_THISCALL);
    // void PhysicsWorld2D::SetDrawShape(bool drawShape) | File: ../Urho2D/PhysicsWorld2D.h
    engine->RegisterObjectMethod("PhysicsWorld2D", "void SetDrawShape(bool)", AS_METHODPR(PhysicsWorld2D, SetDrawShape, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("PhysicsWorld2D", "void set_drawShape(bool)", AS_METHODPR(PhysicsWorld2D, SetDrawShape, (bool), void), AS_CALL_THISCALL);
    // void Component::SetEnabled(bool enable) | File: ../Scene/Component.h
    engine->RegisterObjectMethod("PhysicsWorld2D", "void SetEnabled(bool)", AS_METHODPR(PhysicsWorld2D, SetEnabled, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("PhysicsWorld2D", "void set_enabled(bool)", AS_METHODPR(PhysicsWorld2D, SetEnabled, (bool), void), AS_CALL_THISCALL);
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("PhysicsWorld2D", "void SetGlobalVar(StringHash, const Variant&in)", AS_METHODPR(PhysicsWorld2D, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("PhysicsWorld2D", "void set_globalVar(StringHash, const Variant&in)", AS_METHODPR(PhysicsWorld2D, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    // void PhysicsWorld2D::SetGravity(const Vector2& gravity) | File: ../Urho2D/PhysicsWorld2D.h
    engine->RegisterObjectMethod("PhysicsWorld2D", "void SetGravity(const Vector2&in)", AS_METHODPR(PhysicsWorld2D, SetGravity, (const Vector2&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("PhysicsWorld2D", "void set_gravity(const Vector2&in)", AS_METHODPR(PhysicsWorld2D, SetGravity, (const Vector2&), void), AS_CALL_THISCALL);
    // void Serializable::SetInstanceDefault(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("PhysicsWorld2D", "void SetInstanceDefault(bool)", AS_METHODPR(PhysicsWorld2D, SetInstanceDefault, (bool), void), AS_CALL_THISCALL);
    // void Serializable::SetInterceptNetworkUpdate(const String& attributeName, bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("PhysicsWorld2D", "void SetInterceptNetworkUpdate(const String&in, bool)", AS_METHODPR(PhysicsWorld2D, SetInterceptNetworkUpdate, (const String&, bool), void), AS_CALL_THISCALL);
    // void Animatable::SetObjectAnimation(ObjectAnimation* objectAnimation) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("PhysicsWorld2D", "void SetObjectAnimation(ObjectAnimation@+)", AS_METHODPR(PhysicsWorld2D, SetObjectAnimation, (ObjectAnimation*), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("PhysicsWorld2D", "void set_objectAnimation(ObjectAnimation@+)", AS_METHODPR(PhysicsWorld2D, SetObjectAnimation, (ObjectAnimation*), void), AS_CALL_THISCALL);
    // void Animatable::SetObjectAnimationAttr(const ResourceRef& value) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("PhysicsWorld2D", "void SetObjectAnimationAttr(const ResourceRef&in)", AS_METHODPR(PhysicsWorld2D, SetObjectAnimationAttr, (const ResourceRef&), void), AS_CALL_THISCALL);
    // void PhysicsWorld2D::SetPositionIterations(int positionIterations) | File: ../Urho2D/PhysicsWorld2D.h
    engine->RegisterObjectMethod("PhysicsWorld2D", "void SetPositionIterations(int)", AS_METHODPR(PhysicsWorld2D, SetPositionIterations, (int), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("PhysicsWorld2D", "void set_positionIterations(int)", AS_METHODPR(PhysicsWorld2D, SetPositionIterations, (int), void), AS_CALL_THISCALL);
    // void PhysicsWorld2D::SetSubStepping(bool enable) | File: ../Urho2D/PhysicsWorld2D.h
    engine->RegisterObjectMethod("PhysicsWorld2D", "void SetSubStepping(bool)", AS_METHODPR(PhysicsWorld2D, SetSubStepping, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("PhysicsWorld2D", "void set_subStepping(bool)", AS_METHODPR(PhysicsWorld2D, SetSubStepping, (bool), void), AS_CALL_THISCALL);
    // void Serializable::SetTemporary(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("PhysicsWorld2D", "void SetTemporary(bool)", AS_METHODPR(PhysicsWorld2D, SetTemporary, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("PhysicsWorld2D", "void set_temporary(bool)", AS_METHODPR(PhysicsWorld2D, SetTemporary, (bool), void), AS_CALL_THISCALL);
    // void PhysicsWorld2D::SetUpdateEnabled(bool enable) | File: ../Urho2D/PhysicsWorld2D.h
    engine->RegisterObjectMethod("PhysicsWorld2D", "void SetUpdateEnabled(bool)", AS_METHODPR(PhysicsWorld2D, SetUpdateEnabled, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("PhysicsWorld2D", "void set_updateEnabled(bool)", AS_METHODPR(PhysicsWorld2D, SetUpdateEnabled, (bool), void), AS_CALL_THISCALL);
    // void PhysicsWorld2D::SetVelocityIterations(int velocityIterations) | File: ../Urho2D/PhysicsWorld2D.h
    engine->RegisterObjectMethod("PhysicsWorld2D", "void SetVelocityIterations(int)", AS_METHODPR(PhysicsWorld2D, SetVelocityIterations, (int), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("PhysicsWorld2D", "void set_velocityIterations(int)", AS_METHODPR(PhysicsWorld2D, SetVelocityIterations, (int), void), AS_CALL_THISCALL);
    // void PhysicsWorld2D::SetWarmStarting(bool enable) | File: ../Urho2D/PhysicsWorld2D.h
    engine->RegisterObjectMethod("PhysicsWorld2D", "void SetWarmStarting(bool)", AS_METHODPR(PhysicsWorld2D, SetWarmStarting, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("PhysicsWorld2D", "void set_warmStarting(bool)", AS_METHODPR(PhysicsWorld2D, SetWarmStarting, (bool), void), AS_CALL_THISCALL);
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod("PhysicsWorld2D", "void UnsubscribeFromAllEvents()", AS_METHODPR(PhysicsWorld2D, UnsubscribeFromAllEvents, (), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("PhysicsWorld2D", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", AS_FUNCTION_OBJFIRST(PhysicsWorld2D_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), AS_CALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("PhysicsWorld2D", "void UnsubscribeFromEvent(StringHash)", AS_METHODPR(PhysicsWorld2D, UnsubscribeFromEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("PhysicsWorld2D", "void UnsubscribeFromEvent(Object@+, StringHash)", AS_METHODPR(PhysicsWorld2D, UnsubscribeFromEvent, (Object*, StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("PhysicsWorld2D", "void UnsubscribeFromEvents(Object@+)", AS_METHODPR(PhysicsWorld2D, UnsubscribeFromEvents, (Object*), void), AS_CALL_THISCALL);
    // void PhysicsWorld2D::Update(float timeStep) | File: ../Urho2D/PhysicsWorld2D.h
    engine->RegisterObjectMethod("PhysicsWorld2D", "void Update(float)", AS_METHODPR(PhysicsWorld2D, Update, (float), void), AS_CALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("PhysicsWorld2D", "int WeakRefs() const", AS_METHODPR(PhysicsWorld2D, WeakRefs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("PhysicsWorld2D", "int get_weakRefs() const", AS_METHODPR(PhysicsWorld2D, WeakRefs, () const, int), AS_CALL_THISCALL);
    // void Serializable::WriteDeltaUpdate(Serializer& dest, const DirtyBits& attributeBits, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("PhysicsWorld2D", "void WriteDeltaUpdate(Serializer&, const DirtyBits&in, uint8)", AS_METHODPR(PhysicsWorld2D, WriteDeltaUpdate, (Serializer&, const DirtyBits&, unsigned char), void), AS_CALL_THISCALL);
    // void Serializable::WriteInitialDeltaUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("PhysicsWorld2D", "void WriteInitialDeltaUpdate(Serializer&, uint8)", AS_METHODPR(PhysicsWorld2D, WriteInitialDeltaUpdate, (Serializer&, unsigned char), void), AS_CALL_THISCALL);
    // void Serializable::WriteLatestDataUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("PhysicsWorld2D", "void WriteLatestDataUpdate(Serializer&, uint8)", AS_METHODPR(PhysicsWorld2D, WriteLatestDataUpdate, (Serializer&, unsigned char), void), AS_CALL_THISCALL);
#ifdef REGISTER_MANUAL_PART_Component
    REGISTER_MANUAL_PART_Component(PhysicsWorld2D, "PhysicsWorld2D")
#endif
#ifdef REGISTER_MANUAL_PART_Animatable
    REGISTER_MANUAL_PART_Animatable(PhysicsWorld2D, "PhysicsWorld2D")
#endif
#ifdef REGISTER_MANUAL_PART_Serializable
    REGISTER_MANUAL_PART_Serializable(PhysicsWorld2D, "PhysicsWorld2D")
#endif
#ifdef REGISTER_MANUAL_PART_Object
    REGISTER_MANUAL_PART_Object(PhysicsWorld2D, "PhysicsWorld2D")
#endif
#ifdef REGISTER_MANUAL_PART_RefCounted
    REGISTER_MANUAL_PART_RefCounted(PhysicsWorld2D, "PhysicsWorld2D")
#endif
#ifdef REGISTER_MANUAL_PART_PhysicsWorld2D
    REGISTER_MANUAL_PART_PhysicsWorld2D(PhysicsWorld2D, "PhysicsWorld2D")
#endif
    RegisterSubclass<Component, PhysicsWorld2D>(engine, "Component", "PhysicsWorld2D");
    RegisterSubclass<Animatable, PhysicsWorld2D>(engine, "Animatable", "PhysicsWorld2D");
    RegisterSubclass<Serializable, PhysicsWorld2D>(engine, "Serializable", "PhysicsWorld2D");
    RegisterSubclass<Object, PhysicsWorld2D>(engine, "Object", "PhysicsWorld2D");
    RegisterSubclass<RefCounted, PhysicsWorld2D>(engine, "RefCounted", "PhysicsWorld2D");
#endif

    // Vector3 Plane::absNormal_ | File: ../Math/Plane.h
    engine->RegisterObjectProperty("Plane", "Vector3 absNormal", offsetof(Plane, absNormal_));
    // float Plane::d_ | File: ../Math/Plane.h
    engine->RegisterObjectProperty("Plane", "float d", offsetof(Plane, d_));
    // Vector3 Plane::normal_ | File: ../Math/Plane.h
    engine->RegisterObjectProperty("Plane", "Vector3 normal", offsetof(Plane, normal_));
    // const Plane Plane::UP | File: ../Math/Plane.h
    engine->SetDefaultNamespace("Plane");
    engine->RegisterGlobalProperty("const Plane UP", (void*)&Plane::UP);
    engine->SetDefaultNamespace("");
    // void Plane::Define(const Vector3& v0, const Vector3& v1, const Vector3& v2) | File: ../Math/Plane.h
    engine->RegisterObjectMethod("Plane", "void Define(const Vector3&in, const Vector3&in, const Vector3&in)", AS_METHODPR(Plane, Define, (const Vector3&, const Vector3&, const Vector3&), void), AS_CALL_THISCALL);
    // void Plane::Define(const Vector3& normal, const Vector3& point) | File: ../Math/Plane.h
    engine->RegisterObjectMethod("Plane", "void Define(const Vector3&in, const Vector3&in)", AS_METHODPR(Plane, Define, (const Vector3&, const Vector3&), void), AS_CALL_THISCALL);
    // void Plane::Define(const Vector4& plane) | File: ../Math/Plane.h
    engine->RegisterObjectMethod("Plane", "void Define(const Vector4&in)", AS_METHODPR(Plane, Define, (const Vector4&), void), AS_CALL_THISCALL);
    // float Plane::Distance(const Vector3& point) const | File: ../Math/Plane.h
    engine->RegisterObjectMethod("Plane", "float Distance(const Vector3&in) const", AS_METHODPR(Plane, Distance, (const Vector3&) const, float), AS_CALL_THISCALL);
    // Plane& Plane::operator=(const Plane& rhs) noexcept=default | File: ../Math/Plane.h
    engine->RegisterObjectMethod("Plane", "Plane& opAssign(const Plane&in)", AS_METHODPR(Plane, operator=, (const Plane&), Plane&), AS_CALL_THISCALL);
    // Plane::Plane(const Plane& plane) noexcept=default | File: ../Math/Plane.h
    engine->RegisterObjectBehaviour("Plane", asBEHAVE_CONSTRUCT, "void f(const Plane&in)", AS_FUNCTION_OBJFIRST(Plane_Plane_Plane), AS_CALL_CDECL_OBJFIRST);
    // Plane::Plane(const Vector3& v0, const Vector3& v1, const Vector3& v2) noexcept | File: ../Math/Plane.h
    engine->RegisterObjectBehaviour("Plane", asBEHAVE_CONSTRUCT, "void f(const Vector3&in, const Vector3&in, const Vector3&in)", AS_FUNCTION_OBJFIRST(Plane_Plane_Vector3_Vector3_Vector3), AS_CALL_CDECL_OBJFIRST);
    // Plane::Plane(const Vector3& normal, const Vector3& point) noexcept | File: ../Math/Plane.h
    engine->RegisterObjectBehaviour("Plane", asBEHAVE_CONSTRUCT, "void f(const Vector3&in, const Vector3&in)", AS_FUNCTION_OBJFIRST(Plane_Plane_Vector3_Vector3), AS_CALL_CDECL_OBJFIRST);
    // explicit Plane::Plane(const Vector4& plane) noexcept | File: ../Math/Plane.h
    engine->RegisterObjectBehaviour("Plane", asBEHAVE_CONSTRUCT, "void f(const Vector4&in)", AS_FUNCTION_OBJFIRST(Plane_Plane_Vector4), AS_CALL_CDECL_OBJFIRST);
    // Vector3 Plane::Project(const Vector3& point) const | File: ../Math/Plane.h
    engine->RegisterObjectMethod("Plane", "Vector3 Project(const Vector3&in) const", AS_METHODPR(Plane, Project, (const Vector3&) const, Vector3), AS_CALL_THISCALL);
    // Vector3 Plane::Reflect(const Vector3& direction) const | File: ../Math/Plane.h
    engine->RegisterObjectMethod("Plane", "Vector3 Reflect(const Vector3&in) const", AS_METHODPR(Plane, Reflect, (const Vector3&) const, Vector3), AS_CALL_THISCALL);
    // Matrix3x4 Plane::ReflectionMatrix() const | File: ../Math/Plane.h
    engine->RegisterObjectMethod("Plane", "Matrix3x4 ReflectionMatrix() const", AS_METHODPR(Plane, ReflectionMatrix, () const, Matrix3x4), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Plane", "Matrix3x4 get_reflectionMatrix() const", AS_METHODPR(Plane, ReflectionMatrix, () const, Matrix3x4), AS_CALL_THISCALL);
    // Vector4 Plane::ToVector4() const | File: ../Math/Plane.h
    engine->RegisterObjectMethod("Plane", "Vector4 ToVector4() const", AS_METHODPR(Plane, ToVector4, () const, Vector4), AS_CALL_THISCALL);
    // void Plane::Transform(const Matrix3& transform) | File: ../Math/Plane.h
    engine->RegisterObjectMethod("Plane", "void Transform(const Matrix3&in)", AS_METHODPR(Plane, Transform, (const Matrix3&), void), AS_CALL_THISCALL);
    // void Plane::Transform(const Matrix3x4& transform) | File: ../Math/Plane.h
    engine->RegisterObjectMethod("Plane", "void Transform(const Matrix3x4&in)", AS_METHODPR(Plane, Transform, (const Matrix3x4&), void), AS_CALL_THISCALL);
    // void Plane::Transform(const Matrix4& transform) | File: ../Math/Plane.h
    engine->RegisterObjectMethod("Plane", "void Transform(const Matrix4&in)", AS_METHODPR(Plane, Transform, (const Matrix4&), void), AS_CALL_THISCALL);
    // Plane Plane::Transformed(const Matrix3& transform) const | File: ../Math/Plane.h
    engine->RegisterObjectMethod("Plane", "Plane Transformed(const Matrix3&in) const", AS_METHODPR(Plane, Transformed, (const Matrix3&) const, Plane), AS_CALL_THISCALL);
    // Plane Plane::Transformed(const Matrix3x4& transform) const | File: ../Math/Plane.h
    engine->RegisterObjectMethod("Plane", "Plane Transformed(const Matrix3x4&in) const", AS_METHODPR(Plane, Transformed, (const Matrix3x4&) const, Plane), AS_CALL_THISCALL);
    // Plane Plane::Transformed(const Matrix4& transform) const | File: ../Math/Plane.h
    engine->RegisterObjectMethod("Plane", "Plane Transformed(const Matrix4&in) const", AS_METHODPR(Plane, Transformed, (const Matrix4&) const, Plane), AS_CALL_THISCALL);
#ifdef REGISTER_MANUAL_PART_Plane
    REGISTER_MANUAL_PART_Plane(Plane, "Plane")
#endif

    // Vector<PODVector<Vector3>> Polyhedron::faces_ | File: ../Math/Polyhedron.h
    // Error: type "Vector<PODVector<Vector3>>" can not automatically bind
    // void Polyhedron::AddFace(const Vector3& v0, const Vector3& v1, const Vector3& v2) | File: ../Math/Polyhedron.h
    engine->RegisterObjectMethod("Polyhedron", "void AddFace(const Vector3&in, const Vector3&in, const Vector3&in)", AS_METHODPR(Polyhedron, AddFace, (const Vector3&, const Vector3&, const Vector3&), void), AS_CALL_THISCALL);
    // void Polyhedron::AddFace(const Vector3& v0, const Vector3& v1, const Vector3& v2, const Vector3& v3) | File: ../Math/Polyhedron.h
    engine->RegisterObjectMethod("Polyhedron", "void AddFace(const Vector3&in, const Vector3&in, const Vector3&in, const Vector3&in)", AS_METHODPR(Polyhedron, AddFace, (const Vector3&, const Vector3&, const Vector3&, const Vector3&), void), AS_CALL_THISCALL);
    // void Polyhedron::AddFace(const PODVector<Vector3>& face) | File: ../Math/Polyhedron.h
    engine->RegisterObjectMethod("Polyhedron", "void AddFace(Array<Vector3>@+)", AS_FUNCTION_OBJFIRST(Polyhedron_AddFace_PODVectorVector3), AS_CALL_CDECL_OBJFIRST);
    // void Polyhedron::Clear() | File: ../Math/Polyhedron.h
    engine->RegisterObjectMethod("Polyhedron", "void Clear()", AS_METHODPR(Polyhedron, Clear, (), void), AS_CALL_THISCALL);
    // void Polyhedron::Clip(const Plane& plane) | File: ../Math/Polyhedron.h
    engine->RegisterObjectMethod("Polyhedron", "void Clip(const Plane&in)", AS_METHODPR(Polyhedron, Clip, (const Plane&), void), AS_CALL_THISCALL);
    // void Polyhedron::Clip(const BoundingBox& box) | File: ../Math/Polyhedron.h
    engine->RegisterObjectMethod("Polyhedron", "void Clip(const BoundingBox&in)", AS_METHODPR(Polyhedron, Clip, (const BoundingBox&), void), AS_CALL_THISCALL);
    // void Polyhedron::Clip(const Frustum& frustum) | File: ../Math/Polyhedron.h
    engine->RegisterObjectMethod("Polyhedron", "void Clip(const Frustum&in)", AS_METHODPR(Polyhedron, Clip, (const Frustum&), void), AS_CALL_THISCALL);
    // void Polyhedron::Define(const BoundingBox& box) | File: ../Math/Polyhedron.h
    engine->RegisterObjectMethod("Polyhedron", "void Define(const BoundingBox&in)", AS_METHODPR(Polyhedron, Define, (const BoundingBox&), void), AS_CALL_THISCALL);
    // void Polyhedron::Define(const Frustum& frustum) | File: ../Math/Polyhedron.h
    engine->RegisterObjectMethod("Polyhedron", "void Define(const Frustum&in)", AS_METHODPR(Polyhedron, Define, (const Frustum&), void), AS_CALL_THISCALL);
    // bool Polyhedron::Empty() const | File: ../Math/Polyhedron.h
    engine->RegisterObjectMethod("Polyhedron", "bool Empty() const", AS_METHODPR(Polyhedron, Empty, () const, bool), AS_CALL_THISCALL);
    // Polyhedron& Polyhedron::operator=(const Polyhedron& rhs) | File: ../Math/Polyhedron.h
    engine->RegisterObjectMethod("Polyhedron", "Polyhedron& opAssign(const Polyhedron&in)", AS_METHODPR(Polyhedron, operator=, (const Polyhedron&), Polyhedron&), AS_CALL_THISCALL);
    // Polyhedron::Polyhedron(const Polyhedron& polyhedron) | File: ../Math/Polyhedron.h
    engine->RegisterObjectBehaviour("Polyhedron", asBEHAVE_CONSTRUCT, "void f(const Polyhedron&in)", AS_FUNCTION_OBJFIRST(Polyhedron_Polyhedron_Polyhedron), AS_CALL_CDECL_OBJFIRST);
    // explicit Polyhedron::Polyhedron(const Vector<PODVector<Vector3>>& faces) | File: ../Math/Polyhedron.h
    // Error: type "const Vector<PODVector<Vector3>>&" can not automatically bind
    // explicit Polyhedron::Polyhedron(const BoundingBox& box) | File: ../Math/Polyhedron.h
    engine->RegisterObjectBehaviour("Polyhedron", asBEHAVE_CONSTRUCT, "void f(const BoundingBox&in)", AS_FUNCTION_OBJFIRST(Polyhedron_Polyhedron_BoundingBox), AS_CALL_CDECL_OBJFIRST);
    // explicit Polyhedron::Polyhedron(const Frustum& frustum) | File: ../Math/Polyhedron.h
    engine->RegisterObjectBehaviour("Polyhedron", asBEHAVE_CONSTRUCT, "void f(const Frustum&in)", AS_FUNCTION_OBJFIRST(Polyhedron_Polyhedron_Frustum), AS_CALL_CDECL_OBJFIRST);
    // void Polyhedron::Transform(const Matrix3& transform) | File: ../Math/Polyhedron.h
    engine->RegisterObjectMethod("Polyhedron", "void Transform(const Matrix3&in)", AS_METHODPR(Polyhedron, Transform, (const Matrix3&), void), AS_CALL_THISCALL);
    // void Polyhedron::Transform(const Matrix3x4& transform) | File: ../Math/Polyhedron.h
    engine->RegisterObjectMethod("Polyhedron", "void Transform(const Matrix3x4&in)", AS_METHODPR(Polyhedron, Transform, (const Matrix3x4&), void), AS_CALL_THISCALL);
    // Polyhedron Polyhedron::Transformed(const Matrix3& transform) const | File: ../Math/Polyhedron.h
    engine->RegisterObjectMethod("Polyhedron", "Polyhedron Transformed(const Matrix3&in) const", AS_METHODPR(Polyhedron, Transformed, (const Matrix3&) const, Polyhedron), AS_CALL_THISCALL);
    // Polyhedron Polyhedron::Transformed(const Matrix3x4& transform) const | File: ../Math/Polyhedron.h
    engine->RegisterObjectMethod("Polyhedron", "Polyhedron Transformed(const Matrix3x4&in) const", AS_METHODPR(Polyhedron, Transformed, (const Matrix3x4&) const, Polyhedron), AS_CALL_THISCALL);
#ifdef REGISTER_MANUAL_PART_Polyhedron
    REGISTER_MANUAL_PART_Polyhedron(Polyhedron, "Polyhedron")
#endif

    // void RefCounted::AddRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("Profiler", asBEHAVE_ADDREF, "void f()", AS_METHODPR(Profiler, AddRef, (), void), AS_CALL_THISCALL);
    // void Profiler::BeginBlock(const char* name) | File: ../Core/Profiler.h
    // Error: type "const char*" can not automatically bind
    // void Profiler::BeginFrame() | File: ../Core/Profiler.h
    engine->RegisterObjectMethod("Profiler", "void BeginFrame()", AS_METHODPR(Profiler, BeginFrame, (), void), AS_CALL_THISCALL);
    // void Profiler::BeginInterval() | File: ../Core/Profiler.h
    engine->RegisterObjectMethod("Profiler", "void BeginInterval()", AS_METHODPR(Profiler, BeginInterval, (), void), AS_CALL_THISCALL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // void Profiler::EndBlock() | File: ../Core/Profiler.h
    engine->RegisterObjectMethod("Profiler", "void EndBlock()", AS_METHODPR(Profiler, EndBlock, (), void), AS_CALL_THISCALL);
    // void Profiler::EndFrame() | File: ../Core/Profiler.h
    engine->RegisterObjectMethod("Profiler", "void EndFrame()", AS_METHODPR(Profiler, EndFrame, (), void), AS_CALL_THISCALL);
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Profiler", "bool GetBlockEvents() const", AS_METHODPR(Profiler, GetBlockEvents, () const, bool), AS_CALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Profiler", "const String& GetCategory() const", AS_METHODPR(Profiler, GetCategory, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Profiler", "const String& get_category() const", AS_METHODPR(Profiler, GetCategory, () const, const String&), AS_CALL_THISCALL);
    // Context* Object::GetContext() const | File: ../Core/Object.h
    // Error: type "Context*" can used only as function parameter
    // const ProfilerBlock* Profiler::GetCurrentBlock() | File: ../Core/Profiler.h
    // Error: type "ProfilerBlock" can not automatically bind bacause have @nobind mark
    // VariantMap& Object::GetEventDataMap() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Profiler", "VariantMap& GetEventDataMap() const", AS_METHODPR(Profiler, GetEventDataMap, () const, VariantMap&), AS_CALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Profiler", "Object@+ GetEventSender() const", AS_METHODPR(Profiler, GetEventSender, () const, Object*), AS_CALL_THISCALL);
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Profiler", "const Variant& GetGlobalVar(StringHash) const", AS_METHODPR(Profiler, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Profiler", "const Variant& get_globalVar(StringHash) const", AS_METHODPR(Profiler, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Profiler", "const VariantMap& GetGlobalVars() const", AS_METHODPR(Profiler, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Profiler", "const VariantMap& get_globalVars() const", AS_METHODPR(Profiler, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    // const ProfilerBlock* Profiler::GetRootBlock() | File: ../Core/Profiler.h
    // Error: type "ProfilerBlock" can not automatically bind bacause have @nobind mark
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Profiler", "Object@+ GetSubsystem(StringHash) const", AS_METHODPR(Profiler, GetSubsystem, (StringHash) const, Object*), AS_CALL_THISCALL);
    // template<class T> T* Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("Profiler", "StringHash GetType() const", AS_METHODPR(Profiler, GetType, () const, StringHash), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Profiler", "StringHash get_type() const", AS_METHODPR(Profiler, GetType, () const, StringHash), AS_CALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("Profiler", "const String& GetTypeName() const", AS_METHODPR(Profiler, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Profiler", "const String& get_typeName() const", AS_METHODPR(Profiler, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Profiler", "bool HasEventHandlers() const", AS_METHODPR(Profiler, HasEventHandlers, () const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Profiler", "bool HasSubscribedToEvent(StringHash) const", AS_METHODPR(Profiler, HasSubscribedToEvent, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Profiler", "bool HasSubscribedToEvent(Object@+, StringHash) const", AS_METHODPR(Profiler, HasSubscribedToEvent, (Object*, StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Profiler", "bool IsInstanceOf(StringHash) const", AS_METHODPR(Profiler, IsInstanceOf, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Profiler", "void OnEvent(Object@+, StringHash, VariantMap&)", AS_METHODPR(Profiler, OnEvent, (Object*, StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // const String& Profiler::PrintData(bool showUnused=false, bool showTotal=false, unsigned maxDepth=M_MAX_UNSIGNED) const | File: ../Core/Profiler.h
    engine->RegisterObjectMethod("Profiler", "const String& PrintData(bool = false, bool = false, uint = M_MAX_UNSIGNED) const", AS_METHODPR(Profiler, PrintData, (bool, bool, unsigned) const, const String&), AS_CALL_THISCALL);
    // explicit Profiler::Profiler(Context* context) | File: ../Core/Profiler.h
    engine->RegisterObjectBehaviour("Profiler", asBEHAVE_FACTORY, "Profiler@+ f()", AS_FUNCTION(Profiler_Profiler_Context), AS_CALL_CDECL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("Profiler", "int Refs() const", AS_METHODPR(Profiler, Refs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Profiler", "int get_refs() const", AS_METHODPR(Profiler, Refs, () const, int), AS_CALL_THISCALL);
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("Profiler", asBEHAVE_RELEASE, "void f()", AS_METHODPR(Profiler, ReleaseRef, (), void), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Profiler", "void SendEvent(StringHash)", AS_METHODPR(Profiler, SendEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Profiler", "void SendEvent(StringHash, VariantMap&)", AS_METHODPR(Profiler, SendEvent, (StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Profiler", "void SetBlockEvents(bool)", AS_METHODPR(Profiler, SetBlockEvents, (bool), void), AS_CALL_THISCALL);
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Profiler", "void SetGlobalVar(StringHash, const Variant&in)", AS_METHODPR(Profiler, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Profiler", "void set_globalVar(StringHash, const Variant&in)", AS_METHODPR(Profiler, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod("Profiler", "void UnsubscribeFromAllEvents()", AS_METHODPR(Profiler, UnsubscribeFromAllEvents, (), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Profiler", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", AS_FUNCTION_OBJFIRST(Profiler_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), AS_CALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Profiler", "void UnsubscribeFromEvent(StringHash)", AS_METHODPR(Profiler, UnsubscribeFromEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Profiler", "void UnsubscribeFromEvent(Object@+, StringHash)", AS_METHODPR(Profiler, UnsubscribeFromEvent, (Object*, StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Profiler", "void UnsubscribeFromEvents(Object@+)", AS_METHODPR(Profiler, UnsubscribeFromEvents, (Object*), void), AS_CALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("Profiler", "int WeakRefs() const", AS_METHODPR(Profiler, WeakRefs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Profiler", "int get_weakRefs() const", AS_METHODPR(Profiler, WeakRefs, () const, int), AS_CALL_THISCALL);
#ifdef REGISTER_MANUAL_PART_Object
    REGISTER_MANUAL_PART_Object(Profiler, "Profiler")
#endif
#ifdef REGISTER_MANUAL_PART_RefCounted
    REGISTER_MANUAL_PART_RefCounted(Profiler, "Profiler")
#endif
#ifdef REGISTER_MANUAL_PART_Profiler
    REGISTER_MANUAL_PART_Profiler(Profiler, "Profiler")
#endif
    RegisterSubclass<Object, Profiler>(engine, "Object", "Profiler");
    RegisterSubclass<RefCounted, Profiler>(engine, "RefCounted", "Profiler");

    // void UIElement::AddChild(UIElement* element) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "void AddChild(UIElement@+)", AS_METHODPR(ProgressBar, AddChild, (UIElement*), void), AS_CALL_THISCALL);
    // void RefCounted::AddRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("ProgressBar", asBEHAVE_ADDREF, "void f()", AS_METHODPR(ProgressBar, AddRef, (), void), AS_CALL_THISCALL);
    // void UIElement::AddTag(const String& tag) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "void AddTag(const String&in)", AS_METHODPR(ProgressBar, AddTag, (const String&), void), AS_CALL_THISCALL);
    // void UIElement::AddTags(const String& tags, char separator=';') | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "void AddTags(const String&in, int8 = ';')", AS_METHODPR(ProgressBar, AddTags, (const String&, char), void), AS_CALL_THISCALL);
    // void UIElement::AddTags(const StringVector& tags) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "void AddTags(Array<String>@+)", AS_FUNCTION_OBJFIRST(ProgressBar_AddTags_StringVector), AS_CALL_CDECL_OBJFIRST);
    // void UIElement::AdjustScissor(IntRect& currentScissor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "void AdjustScissor(IntRect&)", AS_METHODPR(ProgressBar, AdjustScissor, (IntRect&), void), AS_CALL_THISCALL);
    // void Serializable::AllocateNetworkState() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ProgressBar", "void AllocateNetworkState()", AS_METHODPR(ProgressBar, AllocateNetworkState, (), void), AS_CALL_THISCALL);
    // void UIElement::ApplyAttributes() override | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "void ApplyAttributes()", AS_METHODPR(ProgressBar, ApplyAttributes, (), void), AS_CALL_THISCALL);
    // void UIElement::BringToFront() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "void BringToFront()", AS_METHODPR(ProgressBar, BringToFront, (), void), AS_CALL_THISCALL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // void ProgressBar::ChangeValue(float delta) | File: ../UI/ProgressBar.h
    engine->RegisterObjectMethod("ProgressBar", "void ChangeValue(float)", AS_METHODPR(ProgressBar, ChangeValue, (float), void), AS_CALL_THISCALL);
    // UIElement* UIElement::CreateChild(StringHash type, const String& name=String::EMPTY, unsigned index=M_MAX_UNSIGNED) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "UIElement@+ CreateChild(StringHash, const String&in = String::EMPTY, uint = M_MAX_UNSIGNED)", AS_METHODPR(ProgressBar, CreateChild, (StringHash, const String&, unsigned), UIElement*), AS_CALL_THISCALL);
    // template<class T> T* UIElement::CreateChild(const String& name=String::EMPTY, unsigned index=M_MAX_UNSIGNED) | File: ../UI/UIElement.h
    // Not registered because template
    // void UIElement::DisableLayoutUpdate() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "void DisableLayoutUpdate()", AS_METHODPR(ProgressBar, DisableLayoutUpdate, (), void), AS_CALL_THISCALL);
    // virtual IntVector2 UIElement::ElementToScreen(const IntVector2& position) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "IntVector2 ElementToScreen(const IntVector2&in)", AS_METHODPR(ProgressBar, ElementToScreen, (const IntVector2&), IntVector2), AS_CALL_THISCALL);
    // void UIElement::EnableLayoutUpdate() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "void EnableLayoutUpdate()", AS_METHODPR(ProgressBar, EnableLayoutUpdate, (), void), AS_CALL_THISCALL);
    // bool UIElement::FilterAttributes(XMLElement& dest) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "bool FilterAttributes(XMLElement&) const", AS_METHODPR(ProgressBar, FilterAttributes, (XMLElement&) const, bool), AS_CALL_THISCALL);
    // unsigned UIElement::FindChild(UIElement* element) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "uint FindChild(UIElement@+) const", AS_METHODPR(ProgressBar, FindChild, (UIElement*) const, unsigned), AS_CALL_THISCALL);
    // bool Animatable::GetAnimationEnabled() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ProgressBar", "bool GetAnimationEnabled() const", AS_METHODPR(ProgressBar, GetAnimationEnabled, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "bool get_animationEnabled() const", AS_METHODPR(ProgressBar, GetAnimationEnabled, () const, bool), AS_CALL_THISCALL);
    // const String& UIElement::GetAppliedStyle() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "const String& GetAppliedStyle() const", AS_METHODPR(ProgressBar, GetAppliedStyle, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "const String& get_style() const", AS_METHODPR(ProgressBar, GetAppliedStyle, () const, const String&), AS_CALL_THISCALL);
    // Variant Serializable::GetAttribute(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ProgressBar", "Variant GetAttribute(uint) const", AS_METHODPR(ProgressBar, GetAttribute, (unsigned) const, Variant), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "Variant get_attributes(uint) const", AS_METHODPR(ProgressBar, GetAttribute, (unsigned) const, Variant), AS_CALL_THISCALL);
    // Variant Serializable::GetAttribute(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ProgressBar", "Variant GetAttribute(const String&in) const", AS_METHODPR(ProgressBar, GetAttribute, (const String&) const, Variant), AS_CALL_THISCALL);
    // ValueAnimation* Animatable::GetAttributeAnimation(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ProgressBar", "ValueAnimation@+ GetAttributeAnimation(const String&in) const", AS_METHODPR(ProgressBar, GetAttributeAnimation, (const String&) const, ValueAnimation*), AS_CALL_THISCALL);
    // float Animatable::GetAttributeAnimationSpeed(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ProgressBar", "float GetAttributeAnimationSpeed(const String&in) const", AS_METHODPR(ProgressBar, GetAttributeAnimationSpeed, (const String&) const, float), AS_CALL_THISCALL);
    // float Animatable::GetAttributeAnimationTime(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ProgressBar", "float GetAttributeAnimationTime(const String&in) const", AS_METHODPR(ProgressBar, GetAttributeAnimationTime, (const String&) const, float), AS_CALL_THISCALL);
    // WrapMode Animatable::GetAttributeAnimationWrapMode(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ProgressBar", "WrapMode GetAttributeAnimationWrapMode(const String&in) const", AS_METHODPR(ProgressBar, GetAttributeAnimationWrapMode, (const String&) const, WrapMode), AS_CALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ProgressBar", "Variant GetAttributeDefault(uint) const", AS_METHODPR(ProgressBar, GetAttributeDefault, (unsigned) const, Variant), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "Variant get_attributeDefaults(uint) const", AS_METHODPR(ProgressBar, GetAttributeDefault, (unsigned) const, Variant), AS_CALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ProgressBar", "Variant GetAttributeDefault(const String&in) const", AS_METHODPR(ProgressBar, GetAttributeDefault, (const String&) const, Variant), AS_CALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // void BorderImage::GetBatches(PODVector<UIBatch>& batches, PODVector<float>& vertexData, const IntRect& currentScissor) override | File: ../UI/BorderImage.h
    // Error: type "PODVector<UIBatch>&" can not automatically bind
    // void UIElement::GetBatchesWithOffset(IntVector2& offset, PODVector<UIBatch>& batches, PODVector<float>& vertexData, IntRect currentScissor) | File: ../UI/UIElement.h
    // Error: type "PODVector<UIBatch>&" can not automatically bind
    // BlendMode BorderImage::GetBlendMode() const | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("ProgressBar", "BlendMode GetBlendMode() const", AS_METHODPR(ProgressBar, GetBlendMode, () const, BlendMode), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "BlendMode get_blendMode() const", AS_METHODPR(ProgressBar, GetBlendMode, () const, BlendMode), AS_CALL_THISCALL);
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ProgressBar", "bool GetBlockEvents() const", AS_METHODPR(ProgressBar, GetBlockEvents, () const, bool), AS_CALL_THISCALL);
    // const IntRect& BorderImage::GetBorder() const | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("ProgressBar", "const IntRect& GetBorder() const", AS_METHODPR(ProgressBar, GetBorder, () const, const IntRect&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "const IntRect& get_border() const", AS_METHODPR(ProgressBar, GetBorder, () const, const IntRect&), AS_CALL_THISCALL);
    // bool UIElement::GetBringToBack() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "bool GetBringToBack() const", AS_METHODPR(ProgressBar, GetBringToBack, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "bool get_bringToBack() const", AS_METHODPR(ProgressBar, GetBringToBack, () const, bool), AS_CALL_THISCALL);
    // bool UIElement::GetBringToFront() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "bool GetBringToFront() const", AS_METHODPR(ProgressBar, GetBringToFront, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "bool get_bringToFront() const", AS_METHODPR(ProgressBar, GetBringToFront, () const, bool), AS_CALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ProgressBar", "const String& GetCategory() const", AS_METHODPR(ProgressBar, GetCategory, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "const String& get_category() const", AS_METHODPR(ProgressBar, GetCategory, () const, const String&), AS_CALL_THISCALL);
    // UIElement* UIElement::GetChild(unsigned index) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "UIElement@+ GetChild(uint) const", AS_METHODPR(ProgressBar, GetChild, (unsigned) const, UIElement*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "UIElement@+ get_children(uint) const", AS_METHODPR(ProgressBar, GetChild, (unsigned) const, UIElement*), AS_CALL_THISCALL);
    // UIElement* UIElement::GetChild(const String& name, bool recursive=false) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "UIElement@+ GetChild(const String&in, bool = false) const", AS_METHODPR(ProgressBar, GetChild, (const String&, bool) const, UIElement*), AS_CALL_THISCALL);
    // UIElement* UIElement::GetChild(const StringHash& key, const Variant& value=Variant::EMPTY, bool recursive=false) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "UIElement@+ GetChild(const StringHash&in, const Variant&in = Variant::EMPTY, bool = false) const", AS_METHODPR(ProgressBar, GetChild, (const StringHash&, const Variant&, bool) const, UIElement*), AS_CALL_THISCALL);
    // template<class T> T* UIElement::GetChildDynamicCast(unsigned index) const | File: ../UI/UIElement.h
    // Not registered because template
    // template<class T> T* UIElement::GetChildDynamicCast(const String& name, bool recursive=false) const | File: ../UI/UIElement.h
    // Not registered because template
    // template<class T> T* UIElement::GetChildDynamicCast(const StringHash& key, const Variant& value=Variant::EMPTY, bool recursive=false) const | File: ../UI/UIElement.h
    // Not registered because template
    // const IntVector2& UIElement::GetChildOffset() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "const IntVector2& GetChildOffset() const", AS_METHODPR(ProgressBar, GetChildOffset, () const, const IntVector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "const IntVector2& get_childOffset() const", AS_METHODPR(ProgressBar, GetChildOffset, () const, const IntVector2&), AS_CALL_THISCALL);
    // const Vector<SharedPtr<UIElement>>& UIElement::GetChildren() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "Array<UIElement@>@ GetChildren() const", AS_FUNCTION_OBJFIRST(ProgressBar_GetChildren_void), AS_CALL_CDECL_OBJFIRST);
    // void UIElement::GetChildren(PODVector<UIElement*>& dest, bool recursive=false) const | File: ../UI/UIElement.h
    // Error: type "PODVector<UIElement*>&" can not automatically bind
    // PODVector<UIElement*> UIElement::GetChildren(bool recursive) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "Array<UIElement@>@ GetChildren(bool) const", AS_FUNCTION_OBJFIRST(ProgressBar_GetChildren_bool), AS_CALL_CDECL_OBJFIRST);
    // void UIElement::GetChildrenWithTag(PODVector<UIElement*>& dest, const String& tag, bool recursive=false) const | File: ../UI/UIElement.h
    // Error: type "PODVector<UIElement*>&" can not automatically bind
    // PODVector<UIElement*> UIElement::GetChildrenWithTag(const String& tag, bool recursive=false) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "Array<UIElement@>@ GetChildrenWithTag(const String&in, bool = false) const", AS_FUNCTION_OBJFIRST(ProgressBar_GetChildrenWithTag_String_bool), AS_CALL_CDECL_OBJFIRST);
    // template<class T> T* UIElement::GetChildStaticCast(unsigned index) const | File: ../UI/UIElement.h
    // Not registered because template
    // template<class T> T* UIElement::GetChildStaticCast(const String& name, bool recursive=false) const | File: ../UI/UIElement.h
    // Not registered because template
    // template<class T> T* UIElement::GetChildStaticCast(const StringHash& key, const Variant& value=Variant::EMPTY, bool recursive=false) const | File: ../UI/UIElement.h
    // Not registered because template
    // const IntRect& UIElement::GetClipBorder() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "const IntRect& GetClipBorder() const", AS_METHODPR(ProgressBar, GetClipBorder, () const, const IntRect&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "const IntRect& get_clipBorder() const", AS_METHODPR(ProgressBar, GetClipBorder, () const, const IntRect&), AS_CALL_THISCALL);
    // bool UIElement::GetClipChildren() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "bool GetClipChildren() const", AS_METHODPR(ProgressBar, GetClipChildren, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "bool get_clipChildren() const", AS_METHODPR(ProgressBar, GetClipChildren, () const, bool), AS_CALL_THISCALL);
    // const Color& UIElement::GetColor(Corner corner) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "const Color& GetColor(Corner) const", AS_METHODPR(ProgressBar, GetColor, (Corner) const, const Color&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "const Color& get_colors(Corner) const", AS_METHODPR(ProgressBar, GetColor, (Corner) const, const Color&), AS_CALL_THISCALL);
    // const Color& UIElement::GetColorAttr() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "const Color& GetColorAttr() const", AS_METHODPR(ProgressBar, GetColorAttr, () const, const Color&), AS_CALL_THISCALL);
    // IntRect UIElement::GetCombinedScreenRect() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "IntRect GetCombinedScreenRect()", AS_METHODPR(ProgressBar, GetCombinedScreenRect, (), IntRect), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "IntRect get_combinedScreenRect()", AS_METHODPR(ProgressBar, GetCombinedScreenRect, (), IntRect), AS_CALL_THISCALL);
    // Context* Object::GetContext() const | File: ../Core/Object.h
    // Error: type "Context*" can used only as function parameter
    // virtual void UIElement::GetDebugDrawBatches(PODVector<UIBatch>& batches, PODVector<float>& vertexData, const IntRect& currentScissor) | File: ../UI/UIElement.h
    // Error: type "PODVector<UIBatch>&" can not automatically bind
    // XMLFile* UIElement::GetDefaultStyle(bool recursiveUp=true) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "XMLFile@+ GetDefaultStyle(bool = true) const", AS_METHODPR(ProgressBar, GetDefaultStyle, (bool) const, XMLFile*), AS_CALL_THISCALL);
    // const Color& UIElement::GetDerivedColor() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "const Color& GetDerivedColor() const", AS_METHODPR(ProgressBar, GetDerivedColor, () const, const Color&), AS_CALL_THISCALL);
    // float UIElement::GetDerivedOpacity() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "float GetDerivedOpacity() const", AS_METHODPR(ProgressBar, GetDerivedOpacity, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "float get_derivedOpacity() const", AS_METHODPR(ProgressBar, GetDerivedOpacity, () const, float), AS_CALL_THISCALL);
    // const IntVector2& BorderImage::GetDisabledOffset() const | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("ProgressBar", "const IntVector2& GetDisabledOffset() const", AS_METHODPR(ProgressBar, GetDisabledOffset, () const, const IntVector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "const IntVector2& get_disabledOffset() const", AS_METHODPR(ProgressBar, GetDisabledOffset, () const, const IntVector2&), AS_CALL_THISCALL);
    // MouseButtonFlags UIElement::GetDragButtonCombo() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "MouseButtonFlags GetDragButtonCombo() const", AS_METHODPR(ProgressBar, GetDragButtonCombo, () const, MouseButtonFlags), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "MouseButtonFlags get_dragButtonCombo() const", AS_METHODPR(ProgressBar, GetDragButtonCombo, () const, MouseButtonFlags), AS_CALL_THISCALL);
    // unsigned UIElement::GetDragButtonCount() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "uint GetDragButtonCount() const", AS_METHODPR(ProgressBar, GetDragButtonCount, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "uint get_dragButtonCount() const", AS_METHODPR(ProgressBar, GetDragButtonCount, () const, unsigned), AS_CALL_THISCALL);
    // DragAndDropModeFlags UIElement::GetDragDropMode() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "DragAndDropModeFlags GetDragDropMode() const", AS_METHODPR(ProgressBar, GetDragDropMode, () const, DragAndDropModeFlags), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "DragAndDropModeFlags get_dragDropMode() const", AS_METHODPR(ProgressBar, GetDragDropMode, () const, DragAndDropModeFlags), AS_CALL_THISCALL);
    // IntVector2 UIElement::GetEffectiveMinSize() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "IntVector2 GetEffectiveMinSize() const", AS_METHODPR(ProgressBar, GetEffectiveMinSize, () const, IntVector2), AS_CALL_THISCALL);
    // UIElement* UIElement::GetElementEventSender() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "UIElement@+ GetElementEventSender() const", AS_METHODPR(ProgressBar, GetElementEventSender, () const, UIElement*), AS_CALL_THISCALL);
    // bool UIElement::GetEnableAnchor() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "bool GetEnableAnchor() const", AS_METHODPR(ProgressBar, GetEnableAnchor, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "bool get_enableAnchor() const", AS_METHODPR(ProgressBar, GetEnableAnchor, () const, bool), AS_CALL_THISCALL);
    // VariantMap& Object::GetEventDataMap() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ProgressBar", "VariantMap& GetEventDataMap() const", AS_METHODPR(ProgressBar, GetEventDataMap, () const, VariantMap&), AS_CALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ProgressBar", "Object@+ GetEventSender() const", AS_METHODPR(ProgressBar, GetEventSender, () const, Object*), AS_CALL_THISCALL);
    // FocusMode UIElement::GetFocusMode() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "FocusMode GetFocusMode() const", AS_METHODPR(ProgressBar, GetFocusMode, () const, FocusMode), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "FocusMode get_focusMode() const", AS_METHODPR(ProgressBar, GetFocusMode, () const, FocusMode), AS_CALL_THISCALL);
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ProgressBar", "const Variant& GetGlobalVar(StringHash) const", AS_METHODPR(ProgressBar, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "const Variant& get_globalVar(StringHash) const", AS_METHODPR(ProgressBar, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ProgressBar", "const VariantMap& GetGlobalVars() const", AS_METHODPR(ProgressBar, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "const VariantMap& get_globalVars() const", AS_METHODPR(ProgressBar, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    // int UIElement::GetHeight() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "int GetHeight() const", AS_METHODPR(ProgressBar, GetHeight, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "int get_height() const", AS_METHODPR(ProgressBar, GetHeight, () const, int), AS_CALL_THISCALL);
    // HorizontalAlignment UIElement::GetHorizontalAlignment() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "HorizontalAlignment GetHorizontalAlignment() const", AS_METHODPR(ProgressBar, GetHorizontalAlignment, () const, HorizontalAlignment), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "HorizontalAlignment get_horizontalAlignment() const", AS_METHODPR(ProgressBar, GetHorizontalAlignment, () const, HorizontalAlignment), AS_CALL_THISCALL);
    // const IntVector2& BorderImage::GetHoverOffset() const | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("ProgressBar", "const IntVector2& GetHoverOffset() const", AS_METHODPR(ProgressBar, GetHoverOffset, () const, const IntVector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "const IntVector2& get_hoverOffset() const", AS_METHODPR(ProgressBar, GetHoverOffset, () const, const IntVector2&), AS_CALL_THISCALL);
    // const IntRect& BorderImage::GetImageBorder() const | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("ProgressBar", "const IntRect& GetImageBorder() const", AS_METHODPR(ProgressBar, GetImageBorder, () const, const IntRect&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "const IntRect& get_imageBorder() const", AS_METHODPR(ProgressBar, GetImageBorder, () const, const IntRect&), AS_CALL_THISCALL);
    // const IntRect& BorderImage::GetImageRect() const | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("ProgressBar", "const IntRect& GetImageRect() const", AS_METHODPR(ProgressBar, GetImageRect, () const, const IntRect&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "const IntRect& get_imageRect() const", AS_METHODPR(ProgressBar, GetImageRect, () const, const IntRect&), AS_CALL_THISCALL);
    // int UIElement::GetIndent() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "int GetIndent() const", AS_METHODPR(ProgressBar, GetIndent, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "int get_indent() const", AS_METHODPR(ProgressBar, GetIndent, () const, int), AS_CALL_THISCALL);
    // int UIElement::GetIndentSpacing() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "int GetIndentSpacing() const", AS_METHODPR(ProgressBar, GetIndentSpacing, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "int get_indentSpacing() const", AS_METHODPR(ProgressBar, GetIndentSpacing, () const, int), AS_CALL_THISCALL);
    // int UIElement::GetIndentWidth() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "int GetIndentWidth() const", AS_METHODPR(ProgressBar, GetIndentWidth, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "int get_indentWidth() const", AS_METHODPR(ProgressBar, GetIndentWidth, () const, int), AS_CALL_THISCALL);
    // bool Serializable::GetInterceptNetworkUpdate(const String& attributeName) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ProgressBar", "bool GetInterceptNetworkUpdate(const String&in) const", AS_METHODPR(ProgressBar, GetInterceptNetworkUpdate, (const String&) const, bool), AS_CALL_THISCALL);
    // BorderImage* ProgressBar::GetKnob() const | File: ../UI/ProgressBar.h
    engine->RegisterObjectMethod("ProgressBar", "BorderImage@+ GetKnob() const", AS_METHODPR(ProgressBar, GetKnob, () const, BorderImage*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "BorderImage@+ get_knob() const", AS_METHODPR(ProgressBar, GetKnob, () const, BorderImage*), AS_CALL_THISCALL);
    // const IntRect& UIElement::GetLayoutBorder() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "const IntRect& GetLayoutBorder() const", AS_METHODPR(ProgressBar, GetLayoutBorder, () const, const IntRect&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "const IntRect& get_layoutBorder() const", AS_METHODPR(ProgressBar, GetLayoutBorder, () const, const IntRect&), AS_CALL_THISCALL);
    // int UIElement::GetLayoutElementMaxSize() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "int GetLayoutElementMaxSize() const", AS_METHODPR(ProgressBar, GetLayoutElementMaxSize, () const, int), AS_CALL_THISCALL);
    // const Vector2& UIElement::GetLayoutFlexScale() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "const Vector2& GetLayoutFlexScale() const", AS_METHODPR(ProgressBar, GetLayoutFlexScale, () const, const Vector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "const Vector2& get_layoutFlexScale() const", AS_METHODPR(ProgressBar, GetLayoutFlexScale, () const, const Vector2&), AS_CALL_THISCALL);
    // LayoutMode UIElement::GetLayoutMode() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "LayoutMode GetLayoutMode() const", AS_METHODPR(ProgressBar, GetLayoutMode, () const, LayoutMode), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "LayoutMode get_layoutMode() const", AS_METHODPR(ProgressBar, GetLayoutMode, () const, LayoutMode), AS_CALL_THISCALL);
    // int UIElement::GetLayoutSpacing() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "int GetLayoutSpacing() const", AS_METHODPR(ProgressBar, GetLayoutSpacing, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "int get_layoutSpacing() const", AS_METHODPR(ProgressBar, GetLayoutSpacing, () const, int), AS_CALL_THISCALL);
    // const String& ProgressBar::GetLoadingPercentStyle() const | File: ../UI/ProgressBar.h
    engine->RegisterObjectMethod("ProgressBar", "const String& GetLoadingPercentStyle() const", AS_METHODPR(ProgressBar, GetLoadingPercentStyle, () const, const String&), AS_CALL_THISCALL);
    // Material* BorderImage::GetMaterial() const | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("ProgressBar", "Material@+ GetMaterial() const", AS_METHODPR(ProgressBar, GetMaterial, () const, Material*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "Material@+ get_material() const", AS_METHODPR(ProgressBar, GetMaterial, () const, Material*), AS_CALL_THISCALL);
    // ResourceRef BorderImage::GetMaterialAttr() const | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("ProgressBar", "ResourceRef GetMaterialAttr() const", AS_METHODPR(ProgressBar, GetMaterialAttr, () const, ResourceRef), AS_CALL_THISCALL);
    // const Vector2& UIElement::GetMaxAnchor() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "const Vector2& GetMaxAnchor() const", AS_METHODPR(ProgressBar, GetMaxAnchor, () const, const Vector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "const Vector2& get_maxAnchor() const", AS_METHODPR(ProgressBar, GetMaxAnchor, () const, const Vector2&), AS_CALL_THISCALL);
    // int UIElement::GetMaxHeight() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "int GetMaxHeight() const", AS_METHODPR(ProgressBar, GetMaxHeight, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "int get_maxHeight() const", AS_METHODPR(ProgressBar, GetMaxHeight, () const, int), AS_CALL_THISCALL);
    // const IntVector2& UIElement::GetMaxOffset() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "const IntVector2& GetMaxOffset() const", AS_METHODPR(ProgressBar, GetMaxOffset, () const, const IntVector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "const IntVector2& get_maxOffset() const", AS_METHODPR(ProgressBar, GetMaxOffset, () const, const IntVector2&), AS_CALL_THISCALL);
    // const IntVector2& UIElement::GetMaxSize() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "const IntVector2& GetMaxSize() const", AS_METHODPR(ProgressBar, GetMaxSize, () const, const IntVector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "const IntVector2& get_maxSize() const", AS_METHODPR(ProgressBar, GetMaxSize, () const, const IntVector2&), AS_CALL_THISCALL);
    // int UIElement::GetMaxWidth() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "int GetMaxWidth() const", AS_METHODPR(ProgressBar, GetMaxWidth, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "int get_maxWidth() const", AS_METHODPR(ProgressBar, GetMaxWidth, () const, int), AS_CALL_THISCALL);
    // const Vector2& UIElement::GetMinAnchor() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "const Vector2& GetMinAnchor() const", AS_METHODPR(ProgressBar, GetMinAnchor, () const, const Vector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "const Vector2& get_minAnchor() const", AS_METHODPR(ProgressBar, GetMinAnchor, () const, const Vector2&), AS_CALL_THISCALL);
    // int UIElement::GetMinHeight() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "int GetMinHeight() const", AS_METHODPR(ProgressBar, GetMinHeight, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "int get_minHeight() const", AS_METHODPR(ProgressBar, GetMinHeight, () const, int), AS_CALL_THISCALL);
    // const IntVector2& UIElement::GetMinOffset() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "const IntVector2& GetMinOffset() const", AS_METHODPR(ProgressBar, GetMinOffset, () const, const IntVector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "const IntVector2& get_minOffset() const", AS_METHODPR(ProgressBar, GetMinOffset, () const, const IntVector2&), AS_CALL_THISCALL);
    // const IntVector2& UIElement::GetMinSize() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "const IntVector2& GetMinSize() const", AS_METHODPR(ProgressBar, GetMinSize, () const, const IntVector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "const IntVector2& get_minSize() const", AS_METHODPR(ProgressBar, GetMinSize, () const, const IntVector2&), AS_CALL_THISCALL);
    // int UIElement::GetMinWidth() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "int GetMinWidth() const", AS_METHODPR(ProgressBar, GetMinWidth, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "int get_minWidth() const", AS_METHODPR(ProgressBar, GetMinWidth, () const, int), AS_CALL_THISCALL);
    // const String& UIElement::GetName() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "const String& GetName() const", AS_METHODPR(ProgressBar, GetName, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "const String& get_name() const", AS_METHODPR(ProgressBar, GetName, () const, const String&), AS_CALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetNetworkAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // NetworkState* Serializable::GetNetworkState() const | File: ../Scene/Serializable.h
    // Error: type "NetworkState*" can not automatically bind
    // unsigned Serializable::GetNumAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ProgressBar", "uint GetNumAttributes() const", AS_METHODPR(ProgressBar, GetNumAttributes, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "uint get_numAttributes() const", AS_METHODPR(ProgressBar, GetNumAttributes, () const, unsigned), AS_CALL_THISCALL);
    // unsigned UIElement::GetNumChildren(bool recursive=false) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "uint GetNumChildren(bool = false) const", AS_METHODPR(ProgressBar, GetNumChildren, (bool) const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "uint get_numChildren(bool = false) const", AS_METHODPR(ProgressBar, GetNumChildren, (bool) const, unsigned), AS_CALL_THISCALL);
    // unsigned Serializable::GetNumNetworkAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ProgressBar", "uint GetNumNetworkAttributes() const", AS_METHODPR(ProgressBar, GetNumNetworkAttributes, () const, unsigned), AS_CALL_THISCALL);
    // ObjectAnimation* Animatable::GetObjectAnimation() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ProgressBar", "ObjectAnimation@+ GetObjectAnimation() const", AS_METHODPR(ProgressBar, GetObjectAnimation, () const, ObjectAnimation*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "ObjectAnimation@+ get_objectAnimation() const", AS_METHODPR(ProgressBar, GetObjectAnimation, () const, ObjectAnimation*), AS_CALL_THISCALL);
    // ResourceRef Animatable::GetObjectAnimationAttr() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ProgressBar", "ResourceRef GetObjectAnimationAttr() const", AS_METHODPR(ProgressBar, GetObjectAnimationAttr, () const, ResourceRef), AS_CALL_THISCALL);
    // float UIElement::GetOpacity() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "float GetOpacity() const", AS_METHODPR(ProgressBar, GetOpacity, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "float get_opacity() const", AS_METHODPR(ProgressBar, GetOpacity, () const, float), AS_CALL_THISCALL);
    // Orientation ProgressBar::GetOrientation() const | File: ../UI/ProgressBar.h
    engine->RegisterObjectMethod("ProgressBar", "Orientation GetOrientation() const", AS_METHODPR(ProgressBar, GetOrientation, () const, Orientation), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "Orientation get_orientation() const", AS_METHODPR(ProgressBar, GetOrientation, () const, Orientation), AS_CALL_THISCALL);
    // UIElement* UIElement::GetParent() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "UIElement@+ GetParent() const", AS_METHODPR(ProgressBar, GetParent, () const, UIElement*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "UIElement@+ get_parent() const", AS_METHODPR(ProgressBar, GetParent, () const, UIElement*), AS_CALL_THISCALL);
    // const Vector2& UIElement::GetPivot() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "const Vector2& GetPivot() const", AS_METHODPR(ProgressBar, GetPivot, () const, const Vector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "const Vector2& get_pivot() const", AS_METHODPR(ProgressBar, GetPivot, () const, const Vector2&), AS_CALL_THISCALL);
    // const IntVector2& UIElement::GetPosition() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "const IntVector2& GetPosition() const", AS_METHODPR(ProgressBar, GetPosition, () const, const IntVector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "const IntVector2& get_position() const", AS_METHODPR(ProgressBar, GetPosition, () const, const IntVector2&), AS_CALL_THISCALL);
    // int UIElement::GetPriority() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "int GetPriority() const", AS_METHODPR(ProgressBar, GetPriority, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "int get_priority() const", AS_METHODPR(ProgressBar, GetPriority, () const, int), AS_CALL_THISCALL);
    // float ProgressBar::GetRange() const | File: ../UI/ProgressBar.h
    engine->RegisterObjectMethod("ProgressBar", "float GetRange() const", AS_METHODPR(ProgressBar, GetRange, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "float get_range() const", AS_METHODPR(ProgressBar, GetRange, () const, float), AS_CALL_THISCALL);
    // UIElement* UIElement::GetRoot() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "UIElement@+ GetRoot() const", AS_METHODPR(ProgressBar, GetRoot, () const, UIElement*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "UIElement@+ get_root() const", AS_METHODPR(ProgressBar, GetRoot, () const, UIElement*), AS_CALL_THISCALL);
    // virtual const IntVector2& UIElement::GetScreenPosition() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "const IntVector2& GetScreenPosition() const", AS_METHODPR(ProgressBar, GetScreenPosition, () const, const IntVector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "const IntVector2& get_screenPosition() const", AS_METHODPR(ProgressBar, GetScreenPosition, () const, const IntVector2&), AS_CALL_THISCALL);
    // bool ProgressBar::GetShowPercentText() const | File: ../UI/ProgressBar.h
    engine->RegisterObjectMethod("ProgressBar", "bool GetShowPercentText() const", AS_METHODPR(ProgressBar, GetShowPercentText, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "bool get_showPercentText() const", AS_METHODPR(ProgressBar, GetShowPercentText, () const, bool), AS_CALL_THISCALL);
    // const IntVector2& UIElement::GetSize() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "const IntVector2& GetSize() const", AS_METHODPR(ProgressBar, GetSize, () const, const IntVector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "const IntVector2& get_size() const", AS_METHODPR(ProgressBar, GetSize, () const, const IntVector2&), AS_CALL_THISCALL);
    // bool UIElement::GetSortChildren() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "bool GetSortChildren() const", AS_METHODPR(ProgressBar, GetSortChildren, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "bool get_sortChildren() const", AS_METHODPR(ProgressBar, GetSortChildren, () const, bool), AS_CALL_THISCALL);
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ProgressBar", "Object@+ GetSubsystem(StringHash) const", AS_METHODPR(ProgressBar, GetSubsystem, (StringHash) const, Object*), AS_CALL_THISCALL);
    // template<class T> T* Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // const StringVector& UIElement::GetTags() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "Array<String>@ GetTags() const", AS_FUNCTION_OBJFIRST(ProgressBar_GetTags_void), AS_CALL_CDECL_OBJFIRST);
    engine->RegisterObjectMethod("ProgressBar", "Array<String>@ get_tags() const", AS_FUNCTION_OBJFIRST(ProgressBar_GetTags_void), AS_CALL_CDECL_OBJFIRST);
    // Texture* BorderImage::GetTexture() const | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("ProgressBar", "Texture@+ GetTexture() const", AS_METHODPR(ProgressBar, GetTexture, () const, Texture*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "Texture@+ get_texture() const", AS_METHODPR(ProgressBar, GetTexture, () const, Texture*), AS_CALL_THISCALL);
    // ResourceRef BorderImage::GetTextureAttr() const | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("ProgressBar", "ResourceRef GetTextureAttr() const", AS_METHODPR(ProgressBar, GetTextureAttr, () const, ResourceRef), AS_CALL_THISCALL);
    // TraversalMode UIElement::GetTraversalMode() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "TraversalMode GetTraversalMode() const", AS_METHODPR(ProgressBar, GetTraversalMode, () const, TraversalMode), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "TraversalMode get_traversalMode() const", AS_METHODPR(ProgressBar, GetTraversalMode, () const, TraversalMode), AS_CALL_THISCALL);
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("ProgressBar", "StringHash GetType() const", AS_METHODPR(ProgressBar, GetType, () const, StringHash), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "StringHash get_type() const", AS_METHODPR(ProgressBar, GetType, () const, StringHash), AS_CALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("ProgressBar", "const String& GetTypeName() const", AS_METHODPR(ProgressBar, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "const String& get_typeName() const", AS_METHODPR(ProgressBar, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    // bool UIElement::GetUseDerivedOpacity() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "bool GetUseDerivedOpacity() const", AS_METHODPR(ProgressBar, GetUseDerivedOpacity, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "bool get_useDerivedOpacity() const", AS_METHODPR(ProgressBar, GetUseDerivedOpacity, () const, bool), AS_CALL_THISCALL);
    // float ProgressBar::GetValue() const | File: ../UI/ProgressBar.h
    engine->RegisterObjectMethod("ProgressBar", "float GetValue() const", AS_METHODPR(ProgressBar, GetValue, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "float get_value() const", AS_METHODPR(ProgressBar, GetValue, () const, float), AS_CALL_THISCALL);
    // const Variant& UIElement::GetVar(const StringHash& key) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "const Variant& GetVar(const StringHash&in) const", AS_METHODPR(ProgressBar, GetVar, (const StringHash&) const, const Variant&), AS_CALL_THISCALL);
    // const VariantMap& UIElement::GetVars() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "const VariantMap& GetVars() const", AS_METHODPR(ProgressBar, GetVars, () const, const VariantMap&), AS_CALL_THISCALL);
    // VerticalAlignment UIElement::GetVerticalAlignment() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "VerticalAlignment GetVerticalAlignment() const", AS_METHODPR(ProgressBar, GetVerticalAlignment, () const, VerticalAlignment), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "VerticalAlignment get_verticalAlignment() const", AS_METHODPR(ProgressBar, GetVerticalAlignment, () const, VerticalAlignment), AS_CALL_THISCALL);
    // int UIElement::GetWidth() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "int GetWidth() const", AS_METHODPR(ProgressBar, GetWidth, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "int get_width() const", AS_METHODPR(ProgressBar, GetWidth, () const, int), AS_CALL_THISCALL);
    // bool UIElement::HasColorGradient() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "bool HasColorGradient() const", AS_METHODPR(ProgressBar, HasColorGradient, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "bool get_colorGradient() const", AS_METHODPR(ProgressBar, HasColorGradient, () const, bool), AS_CALL_THISCALL);
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ProgressBar", "bool HasEventHandlers() const", AS_METHODPR(ProgressBar, HasEventHandlers, () const, bool), AS_CALL_THISCALL);
    // bool UIElement::HasFocus() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "bool HasFocus() const", AS_METHODPR(ProgressBar, HasFocus, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "bool get_focus() const", AS_METHODPR(ProgressBar, HasFocus, () const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ProgressBar", "bool HasSubscribedToEvent(StringHash) const", AS_METHODPR(ProgressBar, HasSubscribedToEvent, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ProgressBar", "bool HasSubscribedToEvent(Object@+, StringHash) const", AS_METHODPR(ProgressBar, HasSubscribedToEvent, (Object*, StringHash) const, bool), AS_CALL_THISCALL);
    // bool UIElement::HasTag(const String& tag) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "bool HasTag(const String&in) const", AS_METHODPR(ProgressBar, HasTag, (const String&) const, bool), AS_CALL_THISCALL);
    // void UIElement::InsertChild(unsigned index, UIElement* element) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "void InsertChild(uint, UIElement@+)", AS_METHODPR(ProgressBar, InsertChild, (unsigned, UIElement*), void), AS_CALL_THISCALL);
    // bool UIElement::IsChildOf(UIElement* element) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "bool IsChildOf(UIElement@+) const", AS_METHODPR(ProgressBar, IsChildOf, (UIElement*) const, bool), AS_CALL_THISCALL);
    // bool UIElement::IsEditable() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "bool IsEditable() const", AS_METHODPR(ProgressBar, IsEditable, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "bool get_editable() const", AS_METHODPR(ProgressBar, IsEditable, () const, bool), AS_CALL_THISCALL);
    // bool UIElement::IsElementEventSender() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "bool IsElementEventSender() const", AS_METHODPR(ProgressBar, IsElementEventSender, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "bool get_elementEventSender() const", AS_METHODPR(ProgressBar, IsElementEventSender, () const, bool), AS_CALL_THISCALL);
    // bool UIElement::IsEnabled() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "bool IsEnabled() const", AS_METHODPR(ProgressBar, IsEnabled, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "bool get_enabled() const", AS_METHODPR(ProgressBar, IsEnabled, () const, bool), AS_CALL_THISCALL);
    // bool UIElement::IsEnabledSelf() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "bool IsEnabledSelf() const", AS_METHODPR(ProgressBar, IsEnabledSelf, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "bool get_enabledSelf() const", AS_METHODPR(ProgressBar, IsEnabledSelf, () const, bool), AS_CALL_THISCALL);
    // bool UIElement::IsFixedHeight() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "bool IsFixedHeight() const", AS_METHODPR(ProgressBar, IsFixedHeight, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "bool get_fixedHeight() const", AS_METHODPR(ProgressBar, IsFixedHeight, () const, bool), AS_CALL_THISCALL);
    // bool UIElement::IsFixedSize() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "bool IsFixedSize() const", AS_METHODPR(ProgressBar, IsFixedSize, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "bool get_fixedSize() const", AS_METHODPR(ProgressBar, IsFixedSize, () const, bool), AS_CALL_THISCALL);
    // bool UIElement::IsFixedWidth() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "bool IsFixedWidth() const", AS_METHODPR(ProgressBar, IsFixedWidth, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "bool get_fixedWidth() const", AS_METHODPR(ProgressBar, IsFixedWidth, () const, bool), AS_CALL_THISCALL);
    // bool UIElement::IsHovering() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "bool IsHovering() const", AS_METHODPR(ProgressBar, IsHovering, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "bool get_hovering() const", AS_METHODPR(ProgressBar, IsHovering, () const, bool), AS_CALL_THISCALL);
    // bool UIElement::IsInside(IntVector2 position, bool isScreen) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "bool IsInside(IntVector2, bool)", AS_METHODPR(ProgressBar, IsInside, (IntVector2, bool), bool), AS_CALL_THISCALL);
    // bool UIElement::IsInsideCombined(IntVector2 position, bool isScreen) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "bool IsInsideCombined(IntVector2, bool)", AS_METHODPR(ProgressBar, IsInsideCombined, (IntVector2, bool), bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ProgressBar", "bool IsInstanceOf(StringHash) const", AS_METHODPR(ProgressBar, IsInstanceOf, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // bool UIElement::IsInternal() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "bool IsInternal() const", AS_METHODPR(ProgressBar, IsInternal, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "bool get_internal() const", AS_METHODPR(ProgressBar, IsInternal, () const, bool), AS_CALL_THISCALL);
    // bool UIElement::IsSelected() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "bool IsSelected() const", AS_METHODPR(ProgressBar, IsSelected, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "bool get_selected() const", AS_METHODPR(ProgressBar, IsSelected, () const, bool), AS_CALL_THISCALL);
    // bool Serializable::IsTemporary() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ProgressBar", "bool IsTemporary() const", AS_METHODPR(ProgressBar, IsTemporary, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "bool get_temporary() const", AS_METHODPR(ProgressBar, IsTemporary, () const, bool), AS_CALL_THISCALL);
    // bool BorderImage::IsTiled() const | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("ProgressBar", "bool IsTiled() const", AS_METHODPR(ProgressBar, IsTiled, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "bool get_tiled() const", AS_METHODPR(ProgressBar, IsTiled, () const, bool), AS_CALL_THISCALL);
    // bool UIElement::IsVisible() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "bool IsVisible() const", AS_METHODPR(ProgressBar, IsVisible, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "bool get_visible() const", AS_METHODPR(ProgressBar, IsVisible, () const, bool), AS_CALL_THISCALL);
    // bool UIElement::IsVisibleEffective() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "bool IsVisibleEffective() const", AS_METHODPR(ProgressBar, IsVisibleEffective, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "bool get_visibleEffective() const", AS_METHODPR(ProgressBar, IsVisibleEffective, () const, bool), AS_CALL_THISCALL);
    // virtual bool UIElement::IsWheelHandler() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "bool IsWheelHandler() const", AS_METHODPR(ProgressBar, IsWheelHandler, () const, bool), AS_CALL_THISCALL);
    // virtual bool UIElement::IsWithinScissor(const IntRect& currentScissor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "bool IsWithinScissor(const IntRect&in)", AS_METHODPR(ProgressBar, IsWithinScissor, (const IntRect&), bool), AS_CALL_THISCALL);
    // virtual bool Serializable::Load(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ProgressBar", "bool Load(Deserializer&)", AS_METHODPR(ProgressBar, Load, (Deserializer&), bool), AS_CALL_THISCALL);
    // virtual UIElement* UIElement::LoadChildXML(const XMLElement& childElem, XMLFile* styleFile) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "UIElement@+ LoadChildXML(const XMLElement&in, XMLFile@+)", AS_METHODPR(ProgressBar, LoadChildXML, (const XMLElement&, XMLFile*), UIElement*), AS_CALL_THISCALL);
    // bool Animatable::LoadJSON(const JSONValue& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ProgressBar", "bool LoadJSON(const JSONValue&in)", AS_METHODPR(ProgressBar, LoadJSON, (const JSONValue&), bool), AS_CALL_THISCALL);
    // bool UIElement::LoadXML(const XMLElement& source) override | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "bool LoadXML(const XMLElement&in)", AS_METHODPR(ProgressBar, LoadXML, (const XMLElement&), bool), AS_CALL_THISCALL);
    // virtual bool UIElement::LoadXML(const XMLElement& source, XMLFile* styleFile) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "bool LoadXML(const XMLElement&in, XMLFile@+)", AS_METHODPR(ProgressBar, LoadXML, (const XMLElement&, XMLFile*), bool), AS_CALL_THISCALL);
    // bool UIElement::LoadXML(Deserializer& source) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "bool LoadXML(Deserializer&)", AS_METHODPR(ProgressBar, LoadXML, (Deserializer&), bool), AS_CALL_THISCALL);
    // virtual void Serializable::MarkNetworkUpdate() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ProgressBar", "void MarkNetworkUpdate()", AS_METHODPR(ProgressBar, MarkNetworkUpdate, (), void), AS_CALL_THISCALL);
    // virtual void UIElement::OnClickBegin(const IntVector2& position, const IntVector2& screenPosition, MouseButton button, MouseButtonFlags buttons, QualifierFlags qualifiers, Cursor* cursor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "void OnClickBegin(const IntVector2&in, const IntVector2&in, MouseButton, MouseButtonFlags, QualifierFlags, Cursor@+)", AS_METHODPR(ProgressBar, OnClickBegin, (const IntVector2&, const IntVector2&, MouseButton, MouseButtonFlags, QualifierFlags, Cursor*), void), AS_CALL_THISCALL);
    // virtual void UIElement::OnClickEnd(const IntVector2& position, const IntVector2& screenPosition, MouseButton button, MouseButtonFlags buttons, QualifierFlags qualifiers, Cursor* cursor, UIElement* beginElement) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "void OnClickEnd(const IntVector2&in, const IntVector2&in, MouseButton, MouseButtonFlags, QualifierFlags, Cursor@+, UIElement@+)", AS_METHODPR(ProgressBar, OnClickEnd, (const IntVector2&, const IntVector2&, MouseButton, MouseButtonFlags, QualifierFlags, Cursor*, UIElement*), void), AS_CALL_THISCALL);
    // virtual void UIElement::OnDoubleClick(const IntVector2& position, const IntVector2& screenPosition, MouseButton button, MouseButtonFlags buttons, QualifierFlags qualifiers, Cursor* cursor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "void OnDoubleClick(const IntVector2&in, const IntVector2&in, MouseButton, MouseButtonFlags, QualifierFlags, Cursor@+)", AS_METHODPR(ProgressBar, OnDoubleClick, (const IntVector2&, const IntVector2&, MouseButton, MouseButtonFlags, QualifierFlags, Cursor*), void), AS_CALL_THISCALL);
    // virtual void UIElement::OnDragBegin(const IntVector2& position, const IntVector2& screenPosition, MouseButtonFlags buttons, QualifierFlags qualifiers, Cursor* cursor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "void OnDragBegin(const IntVector2&in, const IntVector2&in, MouseButtonFlags, QualifierFlags, Cursor@+)", AS_METHODPR(ProgressBar, OnDragBegin, (const IntVector2&, const IntVector2&, MouseButtonFlags, QualifierFlags, Cursor*), void), AS_CALL_THISCALL);
    // virtual void UIElement::OnDragCancel(const IntVector2& position, const IntVector2& screenPosition, MouseButtonFlags dragButtons, MouseButtonFlags cancelButtons, Cursor* cursor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "void OnDragCancel(const IntVector2&in, const IntVector2&in, MouseButtonFlags, MouseButtonFlags, Cursor@+)", AS_METHODPR(ProgressBar, OnDragCancel, (const IntVector2&, const IntVector2&, MouseButtonFlags, MouseButtonFlags, Cursor*), void), AS_CALL_THISCALL);
    // virtual bool UIElement::OnDragDropFinish(UIElement* source) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "bool OnDragDropFinish(UIElement@+)", AS_METHODPR(ProgressBar, OnDragDropFinish, (UIElement*), bool), AS_CALL_THISCALL);
    // virtual bool UIElement::OnDragDropTest(UIElement* source) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "bool OnDragDropTest(UIElement@+)", AS_METHODPR(ProgressBar, OnDragDropTest, (UIElement*), bool), AS_CALL_THISCALL);
    // virtual void UIElement::OnDragEnd(const IntVector2& position, const IntVector2& screenPosition, MouseButtonFlags dragButtons, MouseButtonFlags releaseButtons, Cursor* cursor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "void OnDragEnd(const IntVector2&in, const IntVector2&in, MouseButtonFlags, MouseButtonFlags, Cursor@+)", AS_METHODPR(ProgressBar, OnDragEnd, (const IntVector2&, const IntVector2&, MouseButtonFlags, MouseButtonFlags, Cursor*), void), AS_CALL_THISCALL);
    // virtual void UIElement::OnDragMove(const IntVector2& position, const IntVector2& screenPosition, const IntVector2& deltaPos, MouseButtonFlags buttons, QualifierFlags qualifiers, Cursor* cursor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "void OnDragMove(const IntVector2&in, const IntVector2&in, const IntVector2&in, MouseButtonFlags, QualifierFlags, Cursor@+)", AS_METHODPR(ProgressBar, OnDragMove, (const IntVector2&, const IntVector2&, const IntVector2&, MouseButtonFlags, QualifierFlags, Cursor*), void), AS_CALL_THISCALL);
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ProgressBar", "void OnEvent(Object@+, StringHash, VariantMap&)", AS_METHODPR(ProgressBar, OnEvent, (Object*, StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // virtual void Serializable::OnGetAttribute(const AttributeInfo& attr, Variant& dest) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ProgressBar", "void OnGetAttribute(const AttributeInfo&in, Variant&) const", AS_METHODPR(ProgressBar, OnGetAttribute, (const AttributeInfo&, Variant&) const, void), AS_CALL_THISCALL);
    // virtual void UIElement::OnHover(const IntVector2& position, const IntVector2& screenPosition, MouseButtonFlags buttons, QualifierFlags qualifiers, Cursor* cursor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "void OnHover(const IntVector2&in, const IntVector2&in, MouseButtonFlags, QualifierFlags, Cursor@+)", AS_METHODPR(ProgressBar, OnHover, (const IntVector2&, const IntVector2&, MouseButtonFlags, QualifierFlags, Cursor*), void), AS_CALL_THISCALL);
    // virtual void UIElement::OnIndentSet() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "void OnIndentSet()", AS_METHODPR(ProgressBar, OnIndentSet, (), void), AS_CALL_THISCALL);
    // virtual void UIElement::OnKey(Key key, MouseButtonFlags buttons, QualifierFlags qualifiers) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "void OnKey(Key, MouseButtonFlags, QualifierFlags)", AS_METHODPR(ProgressBar, OnKey, (Key, MouseButtonFlags, QualifierFlags), void), AS_CALL_THISCALL);
    // virtual void UIElement::OnPositionSet(const IntVector2& newPosition) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "void OnPositionSet(const IntVector2&in)", AS_METHODPR(ProgressBar, OnPositionSet, (const IntVector2&), void), AS_CALL_THISCALL);
    // void ProgressBar::OnResize(const IntVector2& newSize, const IntVector2& delta) override | File: ../UI/ProgressBar.h
    engine->RegisterObjectMethod("ProgressBar", "void OnResize(const IntVector2&in, const IntVector2&in)", AS_METHODPR(ProgressBar, OnResize, (const IntVector2&, const IntVector2&), void), AS_CALL_THISCALL);
    // virtual void Serializable::OnSetAttribute(const AttributeInfo& attr, const Variant& src) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ProgressBar", "void OnSetAttribute(const AttributeInfo&in, const Variant&in)", AS_METHODPR(ProgressBar, OnSetAttribute, (const AttributeInfo&, const Variant&), void), AS_CALL_THISCALL);
    // virtual void UIElement::OnSetEditable() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "void OnSetEditable()", AS_METHODPR(ProgressBar, OnSetEditable, (), void), AS_CALL_THISCALL);
    // virtual void UIElement::OnTextInput(const String& text) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "void OnTextInput(const String&in)", AS_METHODPR(ProgressBar, OnTextInput, (const String&), void), AS_CALL_THISCALL);
    // virtual void UIElement::OnWheel(int delta, MouseButtonFlags buttons, QualifierFlags qualifiers) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "void OnWheel(int, MouseButtonFlags, QualifierFlags)", AS_METHODPR(ProgressBar, OnWheel, (int, MouseButtonFlags, QualifierFlags), void), AS_CALL_THISCALL);
    // explicit ProgressBar::ProgressBar(Context* context) | File: ../UI/ProgressBar.h
    engine->RegisterObjectBehaviour("ProgressBar", asBEHAVE_FACTORY, "ProgressBar@+ f()", AS_FUNCTION(ProgressBar_ProgressBar_Context), AS_CALL_CDECL);
    // bool Serializable::ReadDeltaUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ProgressBar", "bool ReadDeltaUpdate(Deserializer&)", AS_METHODPR(ProgressBar, ReadDeltaUpdate, (Deserializer&), bool), AS_CALL_THISCALL);
    // bool Serializable::ReadLatestDataUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ProgressBar", "bool ReadLatestDataUpdate(Deserializer&)", AS_METHODPR(ProgressBar, ReadLatestDataUpdate, (Deserializer&), bool), AS_CALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("ProgressBar", "int Refs() const", AS_METHODPR(ProgressBar, Refs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "int get_refs() const", AS_METHODPR(ProgressBar, Refs, () const, int), AS_CALL_THISCALL);
    // static void ProgressBar::RegisterObject(Context* context) | File: ../UI/ProgressBar.h
    // Not registered because have @nobind mark
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("ProgressBar", asBEHAVE_RELEASE, "void f()", AS_METHODPR(ProgressBar, ReleaseRef, (), void), AS_CALL_THISCALL);
    // void UIElement::Remove() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "void Remove()", AS_METHODPR(ProgressBar, Remove, (), void), AS_CALL_THISCALL);
    // void UIElement::RemoveAllChildren() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "void RemoveAllChildren()", AS_METHODPR(ProgressBar, RemoveAllChildren, (), void), AS_CALL_THISCALL);
    // void UIElement::RemoveAllTags() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "void RemoveAllTags()", AS_METHODPR(ProgressBar, RemoveAllTags, (), void), AS_CALL_THISCALL);
    // void Animatable::RemoveAttributeAnimation(const String& name) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ProgressBar", "void RemoveAttributeAnimation(const String&in)", AS_METHODPR(ProgressBar, RemoveAttributeAnimation, (const String&), void), AS_CALL_THISCALL);
    // void UIElement::RemoveChild(UIElement* element, unsigned index=0) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "void RemoveChild(UIElement@+, uint = 0)", AS_METHODPR(ProgressBar, RemoveChild, (UIElement*, unsigned), void), AS_CALL_THISCALL);
    // void UIElement::RemoveChildAtIndex(unsigned index) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "void RemoveChildAtIndex(uint)", AS_METHODPR(ProgressBar, RemoveChildAtIndex, (unsigned), void), AS_CALL_THISCALL);
    // void Serializable::RemoveInstanceDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ProgressBar", "void RemoveInstanceDefault()", AS_METHODPR(ProgressBar, RemoveInstanceDefault, (), void), AS_CALL_THISCALL);
    // void Animatable::RemoveObjectAnimation() | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ProgressBar", "void RemoveObjectAnimation()", AS_METHODPR(ProgressBar, RemoveObjectAnimation, (), void), AS_CALL_THISCALL);
    // bool UIElement::RemoveTag(const String& tag) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "bool RemoveTag(const String&in)", AS_METHODPR(ProgressBar, RemoveTag, (const String&), bool), AS_CALL_THISCALL);
    // void UIElement::ResetDeepEnabled() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "void ResetDeepEnabled()", AS_METHODPR(ProgressBar, ResetDeepEnabled, (), void), AS_CALL_THISCALL);
    // void Serializable::ResetToDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ProgressBar", "void ResetToDefault()", AS_METHODPR(ProgressBar, ResetToDefault, (), void), AS_CALL_THISCALL);
    // virtual bool Serializable::Save(Serializer& dest) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ProgressBar", "bool Save(Serializer&) const", AS_METHODPR(ProgressBar, Save, (Serializer&) const, bool), AS_CALL_THISCALL);
    // virtual bool Serializable::SaveDefaultAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ProgressBar", "bool SaveDefaultAttributes() const", AS_METHODPR(ProgressBar, SaveDefaultAttributes, () const, bool), AS_CALL_THISCALL);
    // bool Animatable::SaveJSON(JSONValue& dest) const override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ProgressBar", "bool SaveJSON(JSONValue&) const", AS_METHODPR(ProgressBar, SaveJSON, (JSONValue&) const, bool), AS_CALL_THISCALL);
    // bool UIElement::SaveXML(XMLElement& dest) const override | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "bool SaveXML(XMLElement&) const", AS_METHODPR(ProgressBar, SaveXML, (XMLElement&) const, bool), AS_CALL_THISCALL);
    // bool UIElement::SaveXML(Serializer& dest, const String& indentation="\t") const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "bool SaveXML(Serializer&, const String&in = \"\t\") const", AS_METHODPR(ProgressBar, SaveXML, (Serializer&, const String&) const, bool), AS_CALL_THISCALL);
    // virtual IntVector2 UIElement::ScreenToElement(const IntVector2& screenPosition) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "IntVector2 ScreenToElement(const IntVector2&in)", AS_METHODPR(ProgressBar, ScreenToElement, (const IntVector2&), IntVector2), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ProgressBar", "void SendEvent(StringHash)", AS_METHODPR(ProgressBar, SendEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ProgressBar", "void SendEvent(StringHash, VariantMap&)", AS_METHODPR(ProgressBar, SendEvent, (StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void UIElement::SetAlignment(HorizontalAlignment hAlign, VerticalAlignment vAlign) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "void SetAlignment(HorizontalAlignment, VerticalAlignment)", AS_METHODPR(ProgressBar, SetAlignment, (HorizontalAlignment, VerticalAlignment), void), AS_CALL_THISCALL);
    // void Animatable::SetAnimationEnabled(bool enable) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ProgressBar", "void SetAnimationEnabled(bool)", AS_METHODPR(ProgressBar, SetAnimationEnabled, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "void set_animationEnabled(bool)", AS_METHODPR(ProgressBar, SetAnimationEnabled, (bool), void), AS_CALL_THISCALL);
    // void Animatable::SetAnimationTime(float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ProgressBar", "void SetAnimationTime(float)", AS_METHODPR(ProgressBar, SetAnimationTime, (float), void), AS_CALL_THISCALL);
    // bool Serializable::SetAttribute(unsigned index, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ProgressBar", "bool SetAttribute(uint, const Variant&in)", AS_METHODPR(ProgressBar, SetAttribute, (unsigned, const Variant&), bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "bool set_attributes(uint, const Variant&in)", AS_METHODPR(ProgressBar, SetAttribute, (unsigned, const Variant&), bool), AS_CALL_THISCALL);
    // bool Serializable::SetAttribute(const String& name, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ProgressBar", "bool SetAttribute(const String&in, const Variant&in)", AS_METHODPR(ProgressBar, SetAttribute, (const String&, const Variant&), bool), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimation(const String& name, ValueAnimation* attributeAnimation, WrapMode wrapMode=WM_LOOP, float speed=1.0f) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ProgressBar", "void SetAttributeAnimation(const String&in, ValueAnimation@+, WrapMode = WM_LOOP, float = 1.0f)", AS_METHODPR(ProgressBar, SetAttributeAnimation, (const String&, ValueAnimation*, WrapMode, float), void), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimationSpeed(const String& name, float speed) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ProgressBar", "void SetAttributeAnimationSpeed(const String&in, float)", AS_METHODPR(ProgressBar, SetAttributeAnimationSpeed, (const String&, float), void), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimationTime(const String& name, float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ProgressBar", "void SetAttributeAnimationTime(const String&in, float)", AS_METHODPR(ProgressBar, SetAttributeAnimationTime, (const String&, float), void), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimationWrapMode(const String& name, WrapMode wrapMode) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ProgressBar", "void SetAttributeAnimationWrapMode(const String&in, WrapMode)", AS_METHODPR(ProgressBar, SetAttributeAnimationWrapMode, (const String&, WrapMode), void), AS_CALL_THISCALL);
    // void BorderImage::SetBlendMode(BlendMode mode) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("ProgressBar", "void SetBlendMode(BlendMode)", AS_METHODPR(ProgressBar, SetBlendMode, (BlendMode), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "void set_blendMode(BlendMode)", AS_METHODPR(ProgressBar, SetBlendMode, (BlendMode), void), AS_CALL_THISCALL);
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ProgressBar", "void SetBlockEvents(bool)", AS_METHODPR(ProgressBar, SetBlockEvents, (bool), void), AS_CALL_THISCALL);
    // void BorderImage::SetBorder(const IntRect& rect) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("ProgressBar", "void SetBorder(const IntRect&in)", AS_METHODPR(ProgressBar, SetBorder, (const IntRect&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "void set_border(const IntRect&in)", AS_METHODPR(ProgressBar, SetBorder, (const IntRect&), void), AS_CALL_THISCALL);
    // void UIElement::SetBringToBack(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "void SetBringToBack(bool)", AS_METHODPR(ProgressBar, SetBringToBack, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "void set_bringToBack(bool)", AS_METHODPR(ProgressBar, SetBringToBack, (bool), void), AS_CALL_THISCALL);
    // void UIElement::SetBringToFront(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "void SetBringToFront(bool)", AS_METHODPR(ProgressBar, SetBringToFront, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "void set_bringToFront(bool)", AS_METHODPR(ProgressBar, SetBringToFront, (bool), void), AS_CALL_THISCALL);
    // void UIElement::SetChildOffset(const IntVector2& offset) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "void SetChildOffset(const IntVector2&in)", AS_METHODPR(ProgressBar, SetChildOffset, (const IntVector2&), void), AS_CALL_THISCALL);
    // void UIElement::SetClipBorder(const IntRect& rect) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "void SetClipBorder(const IntRect&in)", AS_METHODPR(ProgressBar, SetClipBorder, (const IntRect&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "void set_clipBorder(const IntRect&in)", AS_METHODPR(ProgressBar, SetClipBorder, (const IntRect&), void), AS_CALL_THISCALL);
    // void UIElement::SetClipChildren(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "void SetClipChildren(bool)", AS_METHODPR(ProgressBar, SetClipChildren, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "void set_clipChildren(bool)", AS_METHODPR(ProgressBar, SetClipChildren, (bool), void), AS_CALL_THISCALL);
    // void UIElement::SetColor(const Color& color) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "void SetColor(const Color&in)", AS_METHODPR(ProgressBar, SetColor, (const Color&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "void set_color(const Color&in)", AS_METHODPR(ProgressBar, SetColor, (const Color&), void), AS_CALL_THISCALL);
    // void UIElement::SetColor(Corner corner, const Color& color) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "void SetColor(Corner, const Color&in)", AS_METHODPR(ProgressBar, SetColor, (Corner, const Color&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "void set_colors(Corner, const Color&in)", AS_METHODPR(ProgressBar, SetColor, (Corner, const Color&), void), AS_CALL_THISCALL);
    // void UIElement::SetDeepEnabled(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "void SetDeepEnabled(bool)", AS_METHODPR(ProgressBar, SetDeepEnabled, (bool), void), AS_CALL_THISCALL);
    // void UIElement::SetDefaultStyle(XMLFile* style) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "void SetDefaultStyle(XMLFile@+)", AS_METHODPR(ProgressBar, SetDefaultStyle, (XMLFile*), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "void set_defaultStyle(XMLFile@+)", AS_METHODPR(ProgressBar, SetDefaultStyle, (XMLFile*), void), AS_CALL_THISCALL);
    // void BorderImage::SetDisabledOffset(const IntVector2& offset) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("ProgressBar", "void SetDisabledOffset(const IntVector2&in)", AS_METHODPR(ProgressBar, SetDisabledOffset, (const IntVector2&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "void set_disabledOffset(const IntVector2&in)", AS_METHODPR(ProgressBar, SetDisabledOffset, (const IntVector2&), void), AS_CALL_THISCALL);
    // void BorderImage::SetDisabledOffset(int x, int y) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("ProgressBar", "void SetDisabledOffset(int, int)", AS_METHODPR(ProgressBar, SetDisabledOffset, (int, int), void), AS_CALL_THISCALL);
    // void UIElement::SetDragDropMode(DragAndDropModeFlags mode) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "void SetDragDropMode(DragAndDropModeFlags)", AS_METHODPR(ProgressBar, SetDragDropMode, (DragAndDropModeFlags), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "void set_dragDropMode(DragAndDropModeFlags)", AS_METHODPR(ProgressBar, SetDragDropMode, (DragAndDropModeFlags), void), AS_CALL_THISCALL);
    // void UIElement::SetEditable(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "void SetEditable(bool)", AS_METHODPR(ProgressBar, SetEditable, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "void set_editable(bool)", AS_METHODPR(ProgressBar, SetEditable, (bool), void), AS_CALL_THISCALL);
    // void UIElement::SetElementEventSender(bool flag) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "void SetElementEventSender(bool)", AS_METHODPR(ProgressBar, SetElementEventSender, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "void set_elementEventSender(bool)", AS_METHODPR(ProgressBar, SetElementEventSender, (bool), void), AS_CALL_THISCALL);
    // void UIElement::SetEnableAnchor(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "void SetEnableAnchor(bool)", AS_METHODPR(ProgressBar, SetEnableAnchor, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "void set_enableAnchor(bool)", AS_METHODPR(ProgressBar, SetEnableAnchor, (bool), void), AS_CALL_THISCALL);
    // void UIElement::SetEnabled(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "void SetEnabled(bool)", AS_METHODPR(ProgressBar, SetEnabled, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "void set_enabled(bool)", AS_METHODPR(ProgressBar, SetEnabled, (bool), void), AS_CALL_THISCALL);
    // void UIElement::SetEnabledRecursive(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "void SetEnabledRecursive(bool)", AS_METHODPR(ProgressBar, SetEnabledRecursive, (bool), void), AS_CALL_THISCALL);
    // void UIElement::SetFixedHeight(int height) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "void SetFixedHeight(int)", AS_METHODPR(ProgressBar, SetFixedHeight, (int), void), AS_CALL_THISCALL);
    // void UIElement::SetFixedSize(const IntVector2& size) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "void SetFixedSize(const IntVector2&in)", AS_METHODPR(ProgressBar, SetFixedSize, (const IntVector2&), void), AS_CALL_THISCALL);
    // void UIElement::SetFixedSize(int width, int height) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "void SetFixedSize(int, int)", AS_METHODPR(ProgressBar, SetFixedSize, (int, int), void), AS_CALL_THISCALL);
    // void UIElement::SetFixedWidth(int width) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "void SetFixedWidth(int)", AS_METHODPR(ProgressBar, SetFixedWidth, (int), void), AS_CALL_THISCALL);
    // void UIElement::SetFocus(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "void SetFocus(bool)", AS_METHODPR(ProgressBar, SetFocus, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "void set_focus(bool)", AS_METHODPR(ProgressBar, SetFocus, (bool), void), AS_CALL_THISCALL);
    // void UIElement::SetFocusMode(FocusMode mode) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "void SetFocusMode(FocusMode)", AS_METHODPR(ProgressBar, SetFocusMode, (FocusMode), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "void set_focusMode(FocusMode)", AS_METHODPR(ProgressBar, SetFocusMode, (FocusMode), void), AS_CALL_THISCALL);
    // void BorderImage::SetFullImageRect() | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("ProgressBar", "void SetFullImageRect()", AS_METHODPR(ProgressBar, SetFullImageRect, (), void), AS_CALL_THISCALL);
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ProgressBar", "void SetGlobalVar(StringHash, const Variant&in)", AS_METHODPR(ProgressBar, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "void set_globalVar(StringHash, const Variant&in)", AS_METHODPR(ProgressBar, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    // void UIElement::SetHeight(int height) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "void SetHeight(int)", AS_METHODPR(ProgressBar, SetHeight, (int), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "void set_height(int)", AS_METHODPR(ProgressBar, SetHeight, (int), void), AS_CALL_THISCALL);
    // void UIElement::SetHorizontalAlignment(HorizontalAlignment align) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "void SetHorizontalAlignment(HorizontalAlignment)", AS_METHODPR(ProgressBar, SetHorizontalAlignment, (HorizontalAlignment), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "void set_horizontalAlignment(HorizontalAlignment)", AS_METHODPR(ProgressBar, SetHorizontalAlignment, (HorizontalAlignment), void), AS_CALL_THISCALL);
    // void UIElement::SetHovering(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "void SetHovering(bool)", AS_METHODPR(ProgressBar, SetHovering, (bool), void), AS_CALL_THISCALL);
    // void BorderImage::SetHoverOffset(const IntVector2& offset) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("ProgressBar", "void SetHoverOffset(const IntVector2&in)", AS_METHODPR(ProgressBar, SetHoverOffset, (const IntVector2&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "void set_hoverOffset(const IntVector2&in)", AS_METHODPR(ProgressBar, SetHoverOffset, (const IntVector2&), void), AS_CALL_THISCALL);
    // void BorderImage::SetHoverOffset(int x, int y) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("ProgressBar", "void SetHoverOffset(int, int)", AS_METHODPR(ProgressBar, SetHoverOffset, (int, int), void), AS_CALL_THISCALL);
    // void BorderImage::SetImageBorder(const IntRect& rect) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("ProgressBar", "void SetImageBorder(const IntRect&in)", AS_METHODPR(ProgressBar, SetImageBorder, (const IntRect&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "void set_imageBorder(const IntRect&in)", AS_METHODPR(ProgressBar, SetImageBorder, (const IntRect&), void), AS_CALL_THISCALL);
    // void BorderImage::SetImageRect(const IntRect& rect) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("ProgressBar", "void SetImageRect(const IntRect&in)", AS_METHODPR(ProgressBar, SetImageRect, (const IntRect&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "void set_imageRect(const IntRect&in)", AS_METHODPR(ProgressBar, SetImageRect, (const IntRect&), void), AS_CALL_THISCALL);
    // void UIElement::SetIndent(int indent) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "void SetIndent(int)", AS_METHODPR(ProgressBar, SetIndent, (int), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "void set_indent(int)", AS_METHODPR(ProgressBar, SetIndent, (int), void), AS_CALL_THISCALL);
    // void UIElement::SetIndentSpacing(int indentSpacing) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "void SetIndentSpacing(int)", AS_METHODPR(ProgressBar, SetIndentSpacing, (int), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "void set_indentSpacing(int)", AS_METHODPR(ProgressBar, SetIndentSpacing, (int), void), AS_CALL_THISCALL);
    // void Serializable::SetInstanceDefault(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ProgressBar", "void SetInstanceDefault(bool)", AS_METHODPR(ProgressBar, SetInstanceDefault, (bool), void), AS_CALL_THISCALL);
    // void Serializable::SetInterceptNetworkUpdate(const String& attributeName, bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ProgressBar", "void SetInterceptNetworkUpdate(const String&in, bool)", AS_METHODPR(ProgressBar, SetInterceptNetworkUpdate, (const String&, bool), void), AS_CALL_THISCALL);
    // void UIElement::SetInternal(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "void SetInternal(bool)", AS_METHODPR(ProgressBar, SetInternal, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "void set_internal(bool)", AS_METHODPR(ProgressBar, SetInternal, (bool), void), AS_CALL_THISCALL);
    // void UIElement::SetLayout(LayoutMode mode, int spacing=0, const IntRect& border=IntRect::ZERO) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "void SetLayout(LayoutMode, int = 0, const IntRect&in = IntRect::ZERO)", AS_METHODPR(ProgressBar, SetLayout, (LayoutMode, int, const IntRect&), void), AS_CALL_THISCALL);
    // void UIElement::SetLayoutBorder(const IntRect& border) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "void SetLayoutBorder(const IntRect&in)", AS_METHODPR(ProgressBar, SetLayoutBorder, (const IntRect&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "void set_layoutBorder(const IntRect&in)", AS_METHODPR(ProgressBar, SetLayoutBorder, (const IntRect&), void), AS_CALL_THISCALL);
    // void UIElement::SetLayoutFlexScale(const Vector2& scale) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "void SetLayoutFlexScale(const Vector2&in)", AS_METHODPR(ProgressBar, SetLayoutFlexScale, (const Vector2&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "void set_layoutFlexScale(const Vector2&in)", AS_METHODPR(ProgressBar, SetLayoutFlexScale, (const Vector2&), void), AS_CALL_THISCALL);
    // void UIElement::SetLayoutMode(LayoutMode mode) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "void SetLayoutMode(LayoutMode)", AS_METHODPR(ProgressBar, SetLayoutMode, (LayoutMode), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "void set_layoutMode(LayoutMode)", AS_METHODPR(ProgressBar, SetLayoutMode, (LayoutMode), void), AS_CALL_THISCALL);
    // void UIElement::SetLayoutSpacing(int spacing) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "void SetLayoutSpacing(int)", AS_METHODPR(ProgressBar, SetLayoutSpacing, (int), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "void set_layoutSpacing(int)", AS_METHODPR(ProgressBar, SetLayoutSpacing, (int), void), AS_CALL_THISCALL);
    // void ProgressBar::SetLoadingPercentStyle(const String& style) | File: ../UI/ProgressBar.h
    engine->RegisterObjectMethod("ProgressBar", "void SetLoadingPercentStyle(const String&in)", AS_METHODPR(ProgressBar, SetLoadingPercentStyle, (const String&), void), AS_CALL_THISCALL);
    // void BorderImage::SetMaterial(Material* material) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("ProgressBar", "void SetMaterial(Material@+)", AS_METHODPR(ProgressBar, SetMaterial, (Material*), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "void set_material(Material@+)", AS_METHODPR(ProgressBar, SetMaterial, (Material*), void), AS_CALL_THISCALL);
    // void BorderImage::SetMaterialAttr(const ResourceRef& value) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("ProgressBar", "void SetMaterialAttr(const ResourceRef&in)", AS_METHODPR(ProgressBar, SetMaterialAttr, (const ResourceRef&), void), AS_CALL_THISCALL);
    // void UIElement::SetMaxAnchor(const Vector2& anchor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "void SetMaxAnchor(const Vector2&in)", AS_METHODPR(ProgressBar, SetMaxAnchor, (const Vector2&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "void set_maxAnchor(const Vector2&in)", AS_METHODPR(ProgressBar, SetMaxAnchor, (const Vector2&), void), AS_CALL_THISCALL);
    // void UIElement::SetMaxAnchor(float x, float y) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "void SetMaxAnchor(float, float)", AS_METHODPR(ProgressBar, SetMaxAnchor, (float, float), void), AS_CALL_THISCALL);
    // void UIElement::SetMaxHeight(int height) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "void SetMaxHeight(int)", AS_METHODPR(ProgressBar, SetMaxHeight, (int), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "void set_maxHeight(int)", AS_METHODPR(ProgressBar, SetMaxHeight, (int), void), AS_CALL_THISCALL);
    // void UIElement::SetMaxOffset(const IntVector2& offset) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "void SetMaxOffset(const IntVector2&in)", AS_METHODPR(ProgressBar, SetMaxOffset, (const IntVector2&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "void set_maxOffset(const IntVector2&in)", AS_METHODPR(ProgressBar, SetMaxOffset, (const IntVector2&), void), AS_CALL_THISCALL);
    // void UIElement::SetMaxSize(const IntVector2& maxSize) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "void SetMaxSize(const IntVector2&in)", AS_METHODPR(ProgressBar, SetMaxSize, (const IntVector2&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "void set_maxSize(const IntVector2&in)", AS_METHODPR(ProgressBar, SetMaxSize, (const IntVector2&), void), AS_CALL_THISCALL);
    // void UIElement::SetMaxSize(int width, int height) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "void SetMaxSize(int, int)", AS_METHODPR(ProgressBar, SetMaxSize, (int, int), void), AS_CALL_THISCALL);
    // void UIElement::SetMaxWidth(int width) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "void SetMaxWidth(int)", AS_METHODPR(ProgressBar, SetMaxWidth, (int), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "void set_maxWidth(int)", AS_METHODPR(ProgressBar, SetMaxWidth, (int), void), AS_CALL_THISCALL);
    // void UIElement::SetMinAnchor(const Vector2& anchor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "void SetMinAnchor(const Vector2&in)", AS_METHODPR(ProgressBar, SetMinAnchor, (const Vector2&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "void set_minAnchor(const Vector2&in)", AS_METHODPR(ProgressBar, SetMinAnchor, (const Vector2&), void), AS_CALL_THISCALL);
    // void UIElement::SetMinAnchor(float x, float y) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "void SetMinAnchor(float, float)", AS_METHODPR(ProgressBar, SetMinAnchor, (float, float), void), AS_CALL_THISCALL);
    // void UIElement::SetMinHeight(int height) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "void SetMinHeight(int)", AS_METHODPR(ProgressBar, SetMinHeight, (int), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "void set_minHeight(int)", AS_METHODPR(ProgressBar, SetMinHeight, (int), void), AS_CALL_THISCALL);
    // void UIElement::SetMinOffset(const IntVector2& offset) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "void SetMinOffset(const IntVector2&in)", AS_METHODPR(ProgressBar, SetMinOffset, (const IntVector2&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "void set_minOffset(const IntVector2&in)", AS_METHODPR(ProgressBar, SetMinOffset, (const IntVector2&), void), AS_CALL_THISCALL);
    // void UIElement::SetMinSize(const IntVector2& minSize) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "void SetMinSize(const IntVector2&in)", AS_METHODPR(ProgressBar, SetMinSize, (const IntVector2&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "void set_minSize(const IntVector2&in)", AS_METHODPR(ProgressBar, SetMinSize, (const IntVector2&), void), AS_CALL_THISCALL);
    // void UIElement::SetMinSize(int width, int height) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "void SetMinSize(int, int)", AS_METHODPR(ProgressBar, SetMinSize, (int, int), void), AS_CALL_THISCALL);
    // void UIElement::SetMinWidth(int width) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "void SetMinWidth(int)", AS_METHODPR(ProgressBar, SetMinWidth, (int), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "void set_minWidth(int)", AS_METHODPR(ProgressBar, SetMinWidth, (int), void), AS_CALL_THISCALL);
    // void UIElement::SetName(const String& name) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "void SetName(const String&in)", AS_METHODPR(ProgressBar, SetName, (const String&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "void set_name(const String&in)", AS_METHODPR(ProgressBar, SetName, (const String&), void), AS_CALL_THISCALL);
    // void Animatable::SetObjectAnimation(ObjectAnimation* objectAnimation) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ProgressBar", "void SetObjectAnimation(ObjectAnimation@+)", AS_METHODPR(ProgressBar, SetObjectAnimation, (ObjectAnimation*), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "void set_objectAnimation(ObjectAnimation@+)", AS_METHODPR(ProgressBar, SetObjectAnimation, (ObjectAnimation*), void), AS_CALL_THISCALL);
    // void Animatable::SetObjectAnimationAttr(const ResourceRef& value) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ProgressBar", "void SetObjectAnimationAttr(const ResourceRef&in)", AS_METHODPR(ProgressBar, SetObjectAnimationAttr, (const ResourceRef&), void), AS_CALL_THISCALL);
    // void UIElement::SetOpacity(float opacity) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "void SetOpacity(float)", AS_METHODPR(ProgressBar, SetOpacity, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "void set_opacity(float)", AS_METHODPR(ProgressBar, SetOpacity, (float), void), AS_CALL_THISCALL);
    // void ProgressBar::SetOrientation(Orientation orientation) | File: ../UI/ProgressBar.h
    engine->RegisterObjectMethod("ProgressBar", "void SetOrientation(Orientation)", AS_METHODPR(ProgressBar, SetOrientation, (Orientation), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "void set_orientation(Orientation)", AS_METHODPR(ProgressBar, SetOrientation, (Orientation), void), AS_CALL_THISCALL);
    // void UIElement::SetParent(UIElement* parent, unsigned index=M_MAX_UNSIGNED) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "void SetParent(UIElement@+, uint = M_MAX_UNSIGNED)", AS_METHODPR(ProgressBar, SetParent, (UIElement*, unsigned), void), AS_CALL_THISCALL);
    // void UIElement::SetPivot(const Vector2& pivot) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "void SetPivot(const Vector2&in)", AS_METHODPR(ProgressBar, SetPivot, (const Vector2&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "void set_pivot(const Vector2&in)", AS_METHODPR(ProgressBar, SetPivot, (const Vector2&), void), AS_CALL_THISCALL);
    // void UIElement::SetPivot(float x, float y) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "void SetPivot(float, float)", AS_METHODPR(ProgressBar, SetPivot, (float, float), void), AS_CALL_THISCALL);
    // void UIElement::SetPosition(const IntVector2& position) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "void SetPosition(const IntVector2&in)", AS_METHODPR(ProgressBar, SetPosition, (const IntVector2&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "void set_position(const IntVector2&in)", AS_METHODPR(ProgressBar, SetPosition, (const IntVector2&), void), AS_CALL_THISCALL);
    // void UIElement::SetPosition(int x, int y) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "void SetPosition(int, int)", AS_METHODPR(ProgressBar, SetPosition, (int, int), void), AS_CALL_THISCALL);
    // void UIElement::SetPriority(int priority) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "void SetPriority(int)", AS_METHODPR(ProgressBar, SetPriority, (int), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "void set_priority(int)", AS_METHODPR(ProgressBar, SetPriority, (int), void), AS_CALL_THISCALL);
    // void ProgressBar::SetRange(float range) | File: ../UI/ProgressBar.h
    engine->RegisterObjectMethod("ProgressBar", "void SetRange(float)", AS_METHODPR(ProgressBar, SetRange, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "void set_range(float)", AS_METHODPR(ProgressBar, SetRange, (float), void), AS_CALL_THISCALL);
    // void UIElement::SetRenderTexture(Texture2D* texture) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "void SetRenderTexture(Texture2D@+)", AS_METHODPR(ProgressBar, SetRenderTexture, (Texture2D*), void), AS_CALL_THISCALL);
    // void UIElement::SetSelected(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "void SetSelected(bool)", AS_METHODPR(ProgressBar, SetSelected, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "void set_selected(bool)", AS_METHODPR(ProgressBar, SetSelected, (bool), void), AS_CALL_THISCALL);
    // void ProgressBar::SetShowPercentText(bool enable) | File: ../UI/ProgressBar.h
    engine->RegisterObjectMethod("ProgressBar", "void SetShowPercentText(bool)", AS_METHODPR(ProgressBar, SetShowPercentText, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "void set_showPercentText(bool)", AS_METHODPR(ProgressBar, SetShowPercentText, (bool), void), AS_CALL_THISCALL);
    // void UIElement::SetSize(const IntVector2& size) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "void SetSize(const IntVector2&in)", AS_METHODPR(ProgressBar, SetSize, (const IntVector2&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "void set_size(const IntVector2&in)", AS_METHODPR(ProgressBar, SetSize, (const IntVector2&), void), AS_CALL_THISCALL);
    // void UIElement::SetSize(int width, int height) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "void SetSize(int, int)", AS_METHODPR(ProgressBar, SetSize, (int, int), void), AS_CALL_THISCALL);
    // void UIElement::SetSortChildren(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "void SetSortChildren(bool)", AS_METHODPR(ProgressBar, SetSortChildren, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "void set_sortChildren(bool)", AS_METHODPR(ProgressBar, SetSortChildren, (bool), void), AS_CALL_THISCALL);
    // bool UIElement::SetStyle(const String& styleName, XMLFile* file=nullptr) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "bool SetStyle(const String&in, XMLFile@+ = null)", AS_METHODPR(ProgressBar, SetStyle, (const String&, XMLFile*), bool), AS_CALL_THISCALL);
    // bool UIElement::SetStyle(const XMLElement& element) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "bool SetStyle(const XMLElement&in)", AS_METHODPR(ProgressBar, SetStyle, (const XMLElement&), bool), AS_CALL_THISCALL);
    // bool UIElement::SetStyleAuto(XMLFile* file=nullptr) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "bool SetStyleAuto(XMLFile@+ = null)", AS_METHODPR(ProgressBar, SetStyleAuto, (XMLFile*), bool), AS_CALL_THISCALL);
    // void UIElement::SetTags(const StringVector& tags) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "void SetTags(Array<String>@+)", AS_FUNCTION_OBJFIRST(ProgressBar_SetTags_StringVector), AS_CALL_CDECL_OBJFIRST);
    // void Serializable::SetTemporary(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ProgressBar", "void SetTemporary(bool)", AS_METHODPR(ProgressBar, SetTemporary, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "void set_temporary(bool)", AS_METHODPR(ProgressBar, SetTemporary, (bool), void), AS_CALL_THISCALL);
    // void BorderImage::SetTexture(Texture* texture) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("ProgressBar", "void SetTexture(Texture@+)", AS_METHODPR(ProgressBar, SetTexture, (Texture*), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "void set_texture(Texture@+)", AS_METHODPR(ProgressBar, SetTexture, (Texture*), void), AS_CALL_THISCALL);
    // void BorderImage::SetTextureAttr(const ResourceRef& value) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("ProgressBar", "void SetTextureAttr(const ResourceRef&in)", AS_METHODPR(ProgressBar, SetTextureAttr, (const ResourceRef&), void), AS_CALL_THISCALL);
    // void BorderImage::SetTiled(bool enable) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("ProgressBar", "void SetTiled(bool)", AS_METHODPR(ProgressBar, SetTiled, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "void set_tiled(bool)", AS_METHODPR(ProgressBar, SetTiled, (bool), void), AS_CALL_THISCALL);
    // void UIElement::SetTraversalMode(TraversalMode traversalMode) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "void SetTraversalMode(TraversalMode)", AS_METHODPR(ProgressBar, SetTraversalMode, (TraversalMode), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "void set_traversalMode(TraversalMode)", AS_METHODPR(ProgressBar, SetTraversalMode, (TraversalMode), void), AS_CALL_THISCALL);
    // void UIElement::SetUseDerivedOpacity(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "void SetUseDerivedOpacity(bool)", AS_METHODPR(ProgressBar, SetUseDerivedOpacity, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "void set_useDerivedOpacity(bool)", AS_METHODPR(ProgressBar, SetUseDerivedOpacity, (bool), void), AS_CALL_THISCALL);
    // void ProgressBar::SetValue(float value) | File: ../UI/ProgressBar.h
    engine->RegisterObjectMethod("ProgressBar", "void SetValue(float)", AS_METHODPR(ProgressBar, SetValue, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "void set_value(float)", AS_METHODPR(ProgressBar, SetValue, (float), void), AS_CALL_THISCALL);
    // void UIElement::SetVar(StringHash key, const Variant& value) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "void SetVar(StringHash, const Variant&in)", AS_METHODPR(ProgressBar, SetVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    // void UIElement::SetVerticalAlignment(VerticalAlignment align) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "void SetVerticalAlignment(VerticalAlignment)", AS_METHODPR(ProgressBar, SetVerticalAlignment, (VerticalAlignment), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "void set_verticalAlignment(VerticalAlignment)", AS_METHODPR(ProgressBar, SetVerticalAlignment, (VerticalAlignment), void), AS_CALL_THISCALL);
    // void UIElement::SetVisible(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "void SetVisible(bool)", AS_METHODPR(ProgressBar, SetVisible, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "void set_visible(bool)", AS_METHODPR(ProgressBar, SetVisible, (bool), void), AS_CALL_THISCALL);
    // void UIElement::SetWidth(int width) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "void SetWidth(int)", AS_METHODPR(ProgressBar, SetWidth, (int), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "void set_width(int)", AS_METHODPR(ProgressBar, SetWidth, (int), void), AS_CALL_THISCALL);
    // void UIElement::SortChildren() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "void SortChildren()", AS_METHODPR(ProgressBar, SortChildren, (), void), AS_CALL_THISCALL);
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod("ProgressBar", "void UnsubscribeFromAllEvents()", AS_METHODPR(ProgressBar, UnsubscribeFromAllEvents, (), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ProgressBar", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", AS_FUNCTION_OBJFIRST(ProgressBar_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), AS_CALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ProgressBar", "void UnsubscribeFromEvent(StringHash)", AS_METHODPR(ProgressBar, UnsubscribeFromEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ProgressBar", "void UnsubscribeFromEvent(Object@+, StringHash)", AS_METHODPR(ProgressBar, UnsubscribeFromEvent, (Object*, StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ProgressBar", "void UnsubscribeFromEvents(Object@+)", AS_METHODPR(ProgressBar, UnsubscribeFromEvents, (Object*), void), AS_CALL_THISCALL);
    // virtual void UIElement::Update(float timeStep) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "void Update(float)", AS_METHODPR(ProgressBar, Update, (float), void), AS_CALL_THISCALL);
    // void UIElement::UpdateLayout() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "void UpdateLayout()", AS_METHODPR(ProgressBar, UpdateLayout, (), void), AS_CALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("ProgressBar", "int WeakRefs() const", AS_METHODPR(ProgressBar, WeakRefs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "int get_weakRefs() const", AS_METHODPR(ProgressBar, WeakRefs, () const, int), AS_CALL_THISCALL);
    // void Serializable::WriteDeltaUpdate(Serializer& dest, const DirtyBits& attributeBits, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ProgressBar", "void WriteDeltaUpdate(Serializer&, const DirtyBits&in, uint8)", AS_METHODPR(ProgressBar, WriteDeltaUpdate, (Serializer&, const DirtyBits&, unsigned char), void), AS_CALL_THISCALL);
    // void Serializable::WriteInitialDeltaUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ProgressBar", "void WriteInitialDeltaUpdate(Serializer&, uint8)", AS_METHODPR(ProgressBar, WriteInitialDeltaUpdate, (Serializer&, unsigned char), void), AS_CALL_THISCALL);
    // void Serializable::WriteLatestDataUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ProgressBar", "void WriteLatestDataUpdate(Serializer&, uint8)", AS_METHODPR(ProgressBar, WriteLatestDataUpdate, (Serializer&, unsigned char), void), AS_CALL_THISCALL);
#ifdef REGISTER_MANUAL_PART_BorderImage
    REGISTER_MANUAL_PART_BorderImage(ProgressBar, "ProgressBar")
#endif
#ifdef REGISTER_MANUAL_PART_UIElement
    REGISTER_MANUAL_PART_UIElement(ProgressBar, "ProgressBar")
#endif
#ifdef REGISTER_MANUAL_PART_Animatable
    REGISTER_MANUAL_PART_Animatable(ProgressBar, "ProgressBar")
#endif
#ifdef REGISTER_MANUAL_PART_Serializable
    REGISTER_MANUAL_PART_Serializable(ProgressBar, "ProgressBar")
#endif
#ifdef REGISTER_MANUAL_PART_Object
    REGISTER_MANUAL_PART_Object(ProgressBar, "ProgressBar")
#endif
#ifdef REGISTER_MANUAL_PART_RefCounted
    REGISTER_MANUAL_PART_RefCounted(ProgressBar, "ProgressBar")
#endif
#ifdef REGISTER_MANUAL_PART_ProgressBar
    REGISTER_MANUAL_PART_ProgressBar(ProgressBar, "ProgressBar")
#endif
    RegisterSubclass<BorderImage, ProgressBar>(engine, "BorderImage", "ProgressBar");
    RegisterSubclass<UIElement, ProgressBar>(engine, "UIElement", "ProgressBar");
    RegisterSubclass<Animatable, ProgressBar>(engine, "Animatable", "ProgressBar");
    RegisterSubclass<Serializable, ProgressBar>(engine, "Serializable", "ProgressBar");
    RegisterSubclass<Object, ProgressBar>(engine, "Object", "ProgressBar");
    RegisterSubclass<RefCounted, ProgressBar>(engine, "RefCounted", "ProgressBar");

#ifdef URHO3D_URHO2D
    // void RefCounted::AddRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("PropertySet2D", asBEHAVE_ADDREF, "void f()", AS_METHODPR(PropertySet2D, AddRef, (), void), AS_CALL_THISCALL);
    // const String& PropertySet2D::GetProperty(const String& name) const | File: ../Urho2D/TileMapDefs2D.h
    engine->RegisterObjectMethod("PropertySet2D", "const String& GetProperty(const String&in) const", AS_METHODPR(PropertySet2D, GetProperty, (const String&) const, const String&), AS_CALL_THISCALL);
    // bool PropertySet2D::HasProperty(const String& name) const | File: ../Urho2D/TileMapDefs2D.h
    engine->RegisterObjectMethod("PropertySet2D", "bool HasProperty(const String&in) const", AS_METHODPR(PropertySet2D, HasProperty, (const String&) const, bool), AS_CALL_THISCALL);
    // void PropertySet2D::Load(const XMLElement& element) | File: ../Urho2D/TileMapDefs2D.h
    engine->RegisterObjectMethod("PropertySet2D", "void Load(const XMLElement&in)", AS_METHODPR(PropertySet2D, Load, (const XMLElement&), void), AS_CALL_THISCALL);
    // PropertySet2D::PropertySet2D() | File: ../Urho2D/TileMapDefs2D.h
    engine->RegisterObjectBehaviour("PropertySet2D", asBEHAVE_FACTORY, "PropertySet2D@+ f()", AS_FUNCTION(PropertySet2D_PropertySet2D_void), AS_CALL_CDECL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("PropertySet2D", "int Refs() const", AS_METHODPR(PropertySet2D, Refs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("PropertySet2D", "int get_refs() const", AS_METHODPR(PropertySet2D, Refs, () const, int), AS_CALL_THISCALL);
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("PropertySet2D", asBEHAVE_RELEASE, "void f()", AS_METHODPR(PropertySet2D, ReleaseRef, (), void), AS_CALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("PropertySet2D", "int WeakRefs() const", AS_METHODPR(PropertySet2D, WeakRefs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("PropertySet2D", "int get_weakRefs() const", AS_METHODPR(PropertySet2D, WeakRefs, () const, int), AS_CALL_THISCALL);
#ifdef REGISTER_MANUAL_PART_RefCounted
    REGISTER_MANUAL_PART_RefCounted(PropertySet2D, "PropertySet2D")
#endif
#ifdef REGISTER_MANUAL_PART_PropertySet2D
    REGISTER_MANUAL_PART_PropertySet2D(PropertySet2D, "PropertySet2D")
#endif
    RegisterSubclass<RefCounted, PropertySet2D>(engine, "RefCounted", "PropertySet2D");
#endif

#ifdef URHO3D_NETWORK
    // unsigned PackageDownload::checksum_ | File: ../Network/Connection.h
    engine->RegisterObjectProperty("PackageDownload", "uint checksum", offsetof(PackageDownload, checksum_));
    // SharedPtr<File> PackageDownload::file_ | File: ../Network/Connection.h
    // Error: type "SharedPtr<File>" can not automatically bind
    // bool PackageDownload::initiated_ | File: ../Network/Connection.h
    engine->RegisterObjectProperty("PackageDownload", "bool initiated", offsetof(PackageDownload, initiated_));
    // String PackageDownload::name_ | File: ../Network/Connection.h
    engine->RegisterObjectProperty("PackageDownload", "String name", offsetof(PackageDownload, name_));
    // HashSet<unsigned> PackageDownload::receivedFragments_ | File: ../Network/Connection.h
    // Error: type "HashSet<unsigned>" can not automatically bind
    // unsigned PackageDownload::totalFragments_ | File: ../Network/Connection.h
    engine->RegisterObjectProperty("PackageDownload", "uint totalFragments", offsetof(PackageDownload, totalFragments_));
    // PackageDownload& PackageDownload::operator=(const PackageDownload&) | Possible implicitly-declared
    RegisterImplicitlyDeclaredAssignOperatorIfPossible<PackageDownload>(engine, "PackageDownload");
#ifdef REGISTER_MANUAL_PART_PackageDownload
    REGISTER_MANUAL_PART_PackageDownload(PackageDownload, "PackageDownload")
#endif
#endif

    // unsigned PackageEntry::checksum_ | File: ../IO/PackageFile.h
    engine->RegisterObjectProperty("PackageEntry", "uint checksum", offsetof(PackageEntry, checksum_));
    // unsigned PackageEntry::offset_ | File: ../IO/PackageFile.h
    engine->RegisterObjectProperty("PackageEntry", "uint offset", offsetof(PackageEntry, offset_));
    // unsigned PackageEntry::size_ | File: ../IO/PackageFile.h
    engine->RegisterObjectProperty("PackageEntry", "uint size", offsetof(PackageEntry, size_));
    // PackageEntry& PackageEntry::operator=(const PackageEntry&) | Possible implicitly-declared
    RegisterImplicitlyDeclaredAssignOperatorIfPossible<PackageEntry>(engine, "PackageEntry");
#ifdef REGISTER_MANUAL_PART_PackageEntry
    REGISTER_MANUAL_PART_PackageEntry(PackageEntry, "PackageEntry")
#endif

#ifdef URHO3D_NETWORK
    // SharedPtr<File> PackageUpload::file_ | File: ../Network/Connection.h
    // Error: type "SharedPtr<File>" can not automatically bind
    // unsigned PackageUpload::fragment_ | File: ../Network/Connection.h
    engine->RegisterObjectProperty("PackageUpload", "uint fragment", offsetof(PackageUpload, fragment_));
    // unsigned PackageUpload::totalFragments_ | File: ../Network/Connection.h
    engine->RegisterObjectProperty("PackageUpload", "uint totalFragments", offsetof(PackageUpload, totalFragments_));
    // PackageUpload& PackageUpload::operator=(const PackageUpload&) | Possible implicitly-declared
    RegisterImplicitlyDeclaredAssignOperatorIfPossible<PackageUpload>(engine, "PackageUpload");
#ifdef REGISTER_MANUAL_PART_PackageUpload
    REGISTER_MANUAL_PART_PackageUpload(PackageUpload, "PackageUpload")
#endif
#endif

    // unsigned Particle::colorIndex_ | File: ../Graphics/ParticleEmitter.h
    engine->RegisterObjectProperty("Particle", "uint colorIndex", offsetof(Particle, colorIndex_));
    // float Particle::rotationSpeed_ | File: ../Graphics/ParticleEmitter.h
    engine->RegisterObjectProperty("Particle", "float rotationSpeed", offsetof(Particle, rotationSpeed_));
    // float Particle::scale_ | File: ../Graphics/ParticleEmitter.h
    engine->RegisterObjectProperty("Particle", "float scale", offsetof(Particle, scale_));
    // Vector2 Particle::size_ | File: ../Graphics/ParticleEmitter.h
    engine->RegisterObjectProperty("Particle", "Vector2 size", offsetof(Particle, size_));
    // unsigned Particle::texIndex_ | File: ../Graphics/ParticleEmitter.h
    engine->RegisterObjectProperty("Particle", "uint texIndex", offsetof(Particle, texIndex_));
    // float Particle::timer_ | File: ../Graphics/ParticleEmitter.h
    engine->RegisterObjectProperty("Particle", "float timer", offsetof(Particle, timer_));
    // float Particle::timeToLive_ | File: ../Graphics/ParticleEmitter.h
    engine->RegisterObjectProperty("Particle", "float timeToLive", offsetof(Particle, timeToLive_));
    // Vector3 Particle::velocity_ | File: ../Graphics/ParticleEmitter.h
    engine->RegisterObjectProperty("Particle", "Vector3 velocity", offsetof(Particle, velocity_));
    // Particle& Particle::operator=(const Particle&) | Possible implicitly-declared
    RegisterImplicitlyDeclaredAssignOperatorIfPossible<Particle>(engine, "Particle");
#ifdef REGISTER_MANUAL_PART_Particle
    REGISTER_MANUAL_PART_Particle(Particle, "Particle")
#endif

#ifdef URHO3D_URHO2D
    // Color Particle2D::color_ | File: ../Urho2D/ParticleEmitter2D.h
    engine->RegisterObjectProperty("Particle2D", "Color color", offsetof(Particle2D, color_));
    // Color Particle2D::colorDelta_ | File: ../Urho2D/ParticleEmitter2D.h
    engine->RegisterObjectProperty("Particle2D", "Color colorDelta", offsetof(Particle2D, colorDelta_));
    // float Particle2D::emitRadius_ | File: ../Urho2D/ParticleEmitter2D.h
    engine->RegisterObjectProperty("Particle2D", "float emitRadius", offsetof(Particle2D, emitRadius_));
    // float Particle2D::emitRadiusDelta_ | File: ../Urho2D/ParticleEmitter2D.h
    engine->RegisterObjectProperty("Particle2D", "float emitRadiusDelta", offsetof(Particle2D, emitRadiusDelta_));
    // float Particle2D::emitRotation_ | File: ../Urho2D/ParticleEmitter2D.h
    engine->RegisterObjectProperty("Particle2D", "float emitRotation", offsetof(Particle2D, emitRotation_));
    // float Particle2D::emitRotationDelta_ | File: ../Urho2D/ParticleEmitter2D.h
    engine->RegisterObjectProperty("Particle2D", "float emitRotationDelta", offsetof(Particle2D, emitRotationDelta_));
    // Vector3 Particle2D::position_ | File: ../Urho2D/ParticleEmitter2D.h
    engine->RegisterObjectProperty("Particle2D", "Vector3 position", offsetof(Particle2D, position_));
    // float Particle2D::radialAcceleration_ | File: ../Urho2D/ParticleEmitter2D.h
    engine->RegisterObjectProperty("Particle2D", "float radialAcceleration", offsetof(Particle2D, radialAcceleration_));
    // float Particle2D::rotation_ | File: ../Urho2D/ParticleEmitter2D.h
    engine->RegisterObjectProperty("Particle2D", "float rotation", offsetof(Particle2D, rotation_));
    // float Particle2D::rotationDelta_ | File: ../Urho2D/ParticleEmitter2D.h
    engine->RegisterObjectProperty("Particle2D", "float rotationDelta", offsetof(Particle2D, rotationDelta_));
    // float Particle2D::size_ | File: ../Urho2D/ParticleEmitter2D.h
    engine->RegisterObjectProperty("Particle2D", "float size", offsetof(Particle2D, size_));
    // float Particle2D::sizeDelta_ | File: ../Urho2D/ParticleEmitter2D.h
    engine->RegisterObjectProperty("Particle2D", "float sizeDelta", offsetof(Particle2D, sizeDelta_));
    // Vector2 Particle2D::startPos_ | File: ../Urho2D/ParticleEmitter2D.h
    engine->RegisterObjectProperty("Particle2D", "Vector2 startPos", offsetof(Particle2D, startPos_));
    // float Particle2D::tangentialAcceleration_ | File: ../Urho2D/ParticleEmitter2D.h
    engine->RegisterObjectProperty("Particle2D", "float tangentialAcceleration", offsetof(Particle2D, tangentialAcceleration_));
    // float Particle2D::timeToLive_ | File: ../Urho2D/ParticleEmitter2D.h
    engine->RegisterObjectProperty("Particle2D", "float timeToLive", offsetof(Particle2D, timeToLive_));
    // Vector2 Particle2D::velocity_ | File: ../Urho2D/ParticleEmitter2D.h
    engine->RegisterObjectProperty("Particle2D", "Vector2 velocity", offsetof(Particle2D, velocity_));
    // Particle2D& Particle2D::operator=(const Particle2D&) | Possible implicitly-declared
    RegisterImplicitlyDeclaredAssignOperatorIfPossible<Particle2D>(engine, "Particle2D");
#ifdef REGISTER_MANUAL_PART_Particle2D
    REGISTER_MANUAL_PART_Particle2D(Particle2D, "Particle2D")
#endif
#endif

    // PODVector<Drawable*> PerThreadSceneResult::geometries_ | File: ../Graphics/View.h
    // Error: type "PODVector<Drawable*>" can not automatically bind
    // PODVector<Light*> PerThreadSceneResult::lights_ | File: ../Graphics/View.h
    // Error: type "PODVector<Light*>" can not automatically bind
    // float PerThreadSceneResult::maxZ_ | File: ../Graphics/View.h
    engine->RegisterObjectProperty("PerThreadSceneResult", "float maxZ", offsetof(PerThreadSceneResult, maxZ_));
    // float PerThreadSceneResult::minZ_ | File: ../Graphics/View.h
    engine->RegisterObjectProperty("PerThreadSceneResult", "float minZ", offsetof(PerThreadSceneResult, minZ_));
    // PerThreadSceneResult& PerThreadSceneResult::operator=(const PerThreadSceneResult&) | Possible implicitly-declared
    RegisterImplicitlyDeclaredAssignOperatorIfPossible<PerThreadSceneResult>(engine, "PerThreadSceneResult");
#ifdef REGISTER_MANUAL_PART_PerThreadSceneResult
    REGISTER_MANUAL_PART_PerThreadSceneResult(PerThreadSceneResult, "PerThreadSceneResult")
#endif

#ifdef URHO3D_PHYSICS
    // RigidBody* PhysicsRaycastResult::body_ | File: ../Physics/PhysicsWorld.h
    // RigidBody* can not be registered
    // float PhysicsRaycastResult::distance_ | File: ../Physics/PhysicsWorld.h
    engine->RegisterObjectProperty("PhysicsRaycastResult", "float distance", offsetof(PhysicsRaycastResult, distance_));
    // float PhysicsRaycastResult::hitFraction_ | File: ../Physics/PhysicsWorld.h
    engine->RegisterObjectProperty("PhysicsRaycastResult", "float hitFraction", offsetof(PhysicsRaycastResult, hitFraction_));
    // Vector3 PhysicsRaycastResult::normal_ | File: ../Physics/PhysicsWorld.h
    engine->RegisterObjectProperty("PhysicsRaycastResult", "Vector3 normal", offsetof(PhysicsRaycastResult, normal_));
    // Vector3 PhysicsRaycastResult::position_ | File: ../Physics/PhysicsWorld.h
    engine->RegisterObjectProperty("PhysicsRaycastResult", "Vector3 position", offsetof(PhysicsRaycastResult, position_));
    // PhysicsRaycastResult& PhysicsRaycastResult::operator=(const PhysicsRaycastResult&) | Possible implicitly-declared
    RegisterImplicitlyDeclaredAssignOperatorIfPossible<PhysicsRaycastResult>(engine, "PhysicsRaycastResult");
#ifdef REGISTER_MANUAL_PART_PhysicsRaycastResult
    REGISTER_MANUAL_PART_PhysicsRaycastResult(PhysicsRaycastResult, "PhysicsRaycastResult")
#endif
#endif

#ifdef URHO3D_URHO2D
    // RigidBody2D* PhysicsRaycastResult2D::body_ | File: ../Urho2D/PhysicsWorld2D.h
    // RigidBody2D* can not be registered
    // float PhysicsRaycastResult2D::distance_ | File: ../Urho2D/PhysicsWorld2D.h
    engine->RegisterObjectProperty("PhysicsRaycastResult2D", "float distance", offsetof(PhysicsRaycastResult2D, distance_));
    // Vector2 PhysicsRaycastResult2D::normal_ | File: ../Urho2D/PhysicsWorld2D.h
    engine->RegisterObjectProperty("PhysicsRaycastResult2D", "Vector2 normal", offsetof(PhysicsRaycastResult2D, normal_));
    // Vector2 PhysicsRaycastResult2D::position_ | File: ../Urho2D/PhysicsWorld2D.h
    engine->RegisterObjectProperty("PhysicsRaycastResult2D", "Vector2 position", offsetof(PhysicsRaycastResult2D, position_));
    // PhysicsRaycastResult2D& PhysicsRaycastResult2D::operator=(const PhysicsRaycastResult2D&) | Possible implicitly-declared
    RegisterImplicitlyDeclaredAssignOperatorIfPossible<PhysicsRaycastResult2D>(engine, "PhysicsRaycastResult2D");
#ifdef REGISTER_MANUAL_PART_PhysicsRaycastResult2D
    REGISTER_MANUAL_PART_PhysicsRaycastResult2D(PhysicsRaycastResult2D, "PhysicsRaycastResult2D")
#endif
#endif

#ifdef URHO3D_PHYSICS
    // btCollisionConfiguration* PhysicsWorldConfig::collisionConfig_ | File: ../Physics/PhysicsWorld.h
    // btCollisionConfiguration* can not be registered
    // PhysicsWorldConfig& PhysicsWorldConfig::operator=(const PhysicsWorldConfig&) | Possible implicitly-declared
    RegisterImplicitlyDeclaredAssignOperatorIfPossible<PhysicsWorldConfig>(engine, "PhysicsWorldConfig");
#ifdef REGISTER_MANUAL_PART_PhysicsWorldConfig
    REGISTER_MANUAL_PART_PhysicsWorldConfig(PhysicsWorldConfig, "PhysicsWorldConfig")
#endif
#endif

}

}
