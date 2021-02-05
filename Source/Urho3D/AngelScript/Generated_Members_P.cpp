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
    engine->RegisterObjectBehaviour("PackageFile", asBEHAVE_ADDREF, "void f()", asMETHODPR(PackageFile, AddRef, (), void), asCALL_THISCALL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // bool PackageFile::Exists(const String& fileName) const | File: ../IO/PackageFile.h
    engine->RegisterObjectMethod("PackageFile", "bool Exists(const String&in) const", asMETHODPR(PackageFile, Exists, (const String&) const, bool), asCALL_THISCALL);
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("PackageFile", "bool GetBlockEvents() const", asMETHODPR(PackageFile, GetBlockEvents, () const, bool), asCALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("PackageFile", "const String& GetCategory() const", asMETHODPR(PackageFile, GetCategory, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("PackageFile", "const String& get_category() const", asMETHODPR(PackageFile, GetCategory, () const, const String&), asCALL_THISCALL);
    // unsigned PackageFile::GetChecksum() const | File: ../IO/PackageFile.h
    engine->RegisterObjectMethod("PackageFile", "uint GetChecksum() const", asMETHODPR(PackageFile, GetChecksum, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("PackageFile", "uint get_checksum() const", asMETHODPR(PackageFile, GetChecksum, () const, unsigned), asCALL_THISCALL);
    // Context* Object::GetContext() const | File: ../Core/Object.h
    // Error: type "Context*" can used only as function parameter
    // const HashMap<String, PackageEntry>& PackageFile::GetEntries() const | File: ../IO/PackageFile.h
    // Error: type "const HashMap<String, PackageEntry>&" can not automatically bind
    // const PackageEntry* PackageFile::GetEntry(const String& fileName) const | File: ../IO/PackageFile.h
    // Error: type "const PackageEntry*" can not automatically bind
    // const Vector<String> PackageFile::GetEntryNames() const | File: ../IO/PackageFile.h
    engine->RegisterObjectMethod("PackageFile", "Array<String>@ GetEntryNames() const", asFUNCTION(PackageFile_GetEntryNames_void), asCALL_CDECL_OBJFIRST);
    // VariantMap& Object::GetEventDataMap() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("PackageFile", "VariantMap& GetEventDataMap() const", asMETHODPR(PackageFile, GetEventDataMap, () const, VariantMap&), asCALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("PackageFile", "Object@+ GetEventSender() const", asMETHODPR(PackageFile, GetEventSender, () const, Object*), asCALL_THISCALL);
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("PackageFile", "const Variant& GetGlobalVar(StringHash) const", asMETHODPR(PackageFile, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    engine->RegisterObjectMethod("PackageFile", "const Variant& get_globalVar(StringHash) const", asMETHODPR(PackageFile, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("PackageFile", "const VariantMap& GetGlobalVars() const", asMETHODPR(PackageFile, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    engine->RegisterObjectMethod("PackageFile", "const VariantMap& get_globalVars() const", asMETHODPR(PackageFile, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    // const String& PackageFile::GetName() const | File: ../IO/PackageFile.h
    engine->RegisterObjectMethod("PackageFile", "const String& GetName() const", asMETHODPR(PackageFile, GetName, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("PackageFile", "const String& get_name() const", asMETHODPR(PackageFile, GetName, () const, const String&), asCALL_THISCALL);
    // StringHash PackageFile::GetNameHash() const | File: ../IO/PackageFile.h
    engine->RegisterObjectMethod("PackageFile", "StringHash GetNameHash() const", asMETHODPR(PackageFile, GetNameHash, () const, StringHash), asCALL_THISCALL);
    // unsigned PackageFile::GetNumFiles() const | File: ../IO/PackageFile.h
    engine->RegisterObjectMethod("PackageFile", "uint GetNumFiles() const", asMETHODPR(PackageFile, GetNumFiles, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("PackageFile", "uint get_numFiles() const", asMETHODPR(PackageFile, GetNumFiles, () const, unsigned), asCALL_THISCALL);
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("PackageFile", "Object@+ GetSubsystem(StringHash) const", asMETHODPR(PackageFile, GetSubsystem, (StringHash) const, Object*), asCALL_THISCALL);
    // template<class T> T*  Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // unsigned PackageFile::GetTotalDataSize() const | File: ../IO/PackageFile.h
    engine->RegisterObjectMethod("PackageFile", "uint GetTotalDataSize() const", asMETHODPR(PackageFile, GetTotalDataSize, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("PackageFile", "uint get_totalDataSize() const", asMETHODPR(PackageFile, GetTotalDataSize, () const, unsigned), asCALL_THISCALL);
    // unsigned PackageFile::GetTotalSize() const | File: ../IO/PackageFile.h
    engine->RegisterObjectMethod("PackageFile", "uint GetTotalSize() const", asMETHODPR(PackageFile, GetTotalSize, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("PackageFile", "uint get_totalSize() const", asMETHODPR(PackageFile, GetTotalSize, () const, unsigned), asCALL_THISCALL);
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("PackageFile", "StringHash GetType() const", asMETHODPR(PackageFile, GetType, () const, StringHash), asCALL_THISCALL);
    engine->RegisterObjectMethod("PackageFile", "StringHash get_type() const", asMETHODPR(PackageFile, GetType, () const, StringHash), asCALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("PackageFile", "const String& GetTypeName() const", asMETHODPR(PackageFile, GetTypeName, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("PackageFile", "const String& get_typeName() const", asMETHODPR(PackageFile, GetTypeName, () const, const String&), asCALL_THISCALL);
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("PackageFile", "bool HasEventHandlers() const", asMETHODPR(PackageFile, HasEventHandlers, () const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("PackageFile", "bool HasSubscribedToEvent(StringHash) const", asMETHODPR(PackageFile, HasSubscribedToEvent, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("PackageFile", "bool HasSubscribedToEvent(Object@+, StringHash) const", asMETHODPR(PackageFile, HasSubscribedToEvent, (Object*, StringHash) const, bool), asCALL_THISCALL);
    // bool PackageFile::IsCompressed() const | File: ../IO/PackageFile.h
    engine->RegisterObjectMethod("PackageFile", "bool IsCompressed() const", asMETHODPR(PackageFile, IsCompressed, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("PackageFile", "bool get_compressed() const", asMETHODPR(PackageFile, IsCompressed, () const, bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("PackageFile", "bool IsInstanceOf(StringHash) const", asMETHODPR(PackageFile, IsInstanceOf, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("PackageFile", "void OnEvent(Object@+, StringHash, VariantMap&)", asMETHODPR(PackageFile, OnEvent, (Object*, StringHash, VariantMap&), void), asCALL_THISCALL);
    // bool PackageFile::Open(const String& fileName, unsigned startOffset=0) | File: ../IO/PackageFile.h
    engine->RegisterObjectMethod("PackageFile", "bool Open(const String&in, uint = 0)", asMETHODPR(PackageFile, Open, (const String&, unsigned), bool), asCALL_THISCALL);
    // explicit PackageFile::PackageFile(Context* context) | File: ../IO/PackageFile.h
    engine->RegisterObjectBehaviour("PackageFile", asBEHAVE_FACTORY, "PackageFile@+ f()", asFUNCTION(PackageFile_PackageFile_Context), asCALL_CDECL);
    // PackageFile::PackageFile(Context* context, const String& fileName, unsigned startOffset=0) | File: ../IO/PackageFile.h
    engine->RegisterObjectBehaviour("PackageFile", asBEHAVE_FACTORY, "PackageFile@+ f(const String&in, uint = 0)", asFUNCTION(PackageFile_PackageFile_Context_String_unsigned), asCALL_CDECL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("PackageFile", "int Refs() const", asMETHODPR(PackageFile, Refs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("PackageFile", "int get_refs() const", asMETHODPR(PackageFile, Refs, () const, int), asCALL_THISCALL);
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("PackageFile", asBEHAVE_RELEASE, "void f()", asMETHODPR(PackageFile, ReleaseRef, (), void), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("PackageFile", "void SendEvent(StringHash)", asMETHODPR(PackageFile, SendEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("PackageFile", "void SendEvent(StringHash, VariantMap&)", asMETHODPR(PackageFile, SendEvent, (StringHash, VariantMap&), void), asCALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("PackageFile", "void SetBlockEvents(bool)", asMETHODPR(PackageFile, SetBlockEvents, (bool), void), asCALL_THISCALL);
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("PackageFile", "void SetGlobalVar(StringHash, const Variant&in)", asMETHODPR(PackageFile, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("PackageFile", "void set_globalVar(StringHash, const Variant&in)", asMETHODPR(PackageFile, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod("PackageFile", "void UnsubscribeFromAllEvents()", asMETHODPR(PackageFile, UnsubscribeFromAllEvents, (), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("PackageFile", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", asFUNCTION(PackageFile_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), asCALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("PackageFile", "void UnsubscribeFromEvent(StringHash)", asMETHODPR(PackageFile, UnsubscribeFromEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("PackageFile", "void UnsubscribeFromEvent(Object@+, StringHash)", asMETHODPR(PackageFile, UnsubscribeFromEvent, (Object*, StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("PackageFile", "void UnsubscribeFromEvents(Object@+)", asMETHODPR(PackageFile, UnsubscribeFromEvents, (Object*), void), asCALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("PackageFile", "int WeakRefs() const", asMETHODPR(PackageFile, WeakRefs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("PackageFile", "int get_weakRefs() const", asMETHODPR(PackageFile, WeakRefs, () const, int), asCALL_THISCALL);
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
    engine->RegisterObjectMethod("ParticleEffect", "void AddColorFrame(const ColorFrame&in)", asMETHODPR(ParticleEffect, AddColorFrame, (const ColorFrame&), void), asCALL_THISCALL);
    // void ParticleEffect::AddColorTime(const Color& color, float time) | File: ../Graphics/ParticleEffect.h
    engine->RegisterObjectMethod("ParticleEffect", "void AddColorTime(const Color&in, float)", asMETHODPR(ParticleEffect, AddColorTime, (const Color&, float), void), asCALL_THISCALL);
    // void RefCounted::AddRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("ParticleEffect", asBEHAVE_ADDREF, "void f()", asMETHODPR(ParticleEffect, AddRef, (), void), asCALL_THISCALL);
    // void ParticleEffect::AddTextureFrame(const TextureFrame& textureFrame) | File: ../Graphics/ParticleEffect.h
    engine->RegisterObjectMethod("ParticleEffect", "void AddTextureFrame(const TextureFrame&in)", asMETHODPR(ParticleEffect, AddTextureFrame, (const TextureFrame&), void), asCALL_THISCALL);
    // void ParticleEffect::AddTextureTime(const Rect& uv, float time) | File: ../Graphics/ParticleEffect.h
    engine->RegisterObjectMethod("ParticleEffect", "void AddTextureTime(const Rect&in, float)", asMETHODPR(ParticleEffect, AddTextureTime, (const Rect&, float), void), asCALL_THISCALL);
    // bool ParticleEffect::BeginLoad(Deserializer& source) override | File: ../Graphics/ParticleEffect.h
    engine->RegisterObjectMethod("ParticleEffect", "bool BeginLoad(Deserializer&)", asMETHODPR(ParticleEffect, BeginLoad, (Deserializer&), bool), asCALL_THISCALL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // SharedPtr<ParticleEffect> ParticleEffect::Clone(const String& cloneName=String::EMPTY) const | File: ../Graphics/ParticleEffect.h
    engine->RegisterObjectMethod("ParticleEffect", "ParticleEffect@+ Clone(const String&in = String::EMPTY) const", asFUNCTION(ParticleEffect_Clone_String), asCALL_CDECL_OBJFIRST);
    // bool ParticleEffect::EndLoad() override | File: ../Graphics/ParticleEffect.h
    engine->RegisterObjectMethod("ParticleEffect", "bool EndLoad()", asMETHODPR(ParticleEffect, EndLoad, (), bool), asCALL_THISCALL);
    // float ParticleEffect::GetActiveTime() const | File: ../Graphics/ParticleEffect.h
    engine->RegisterObjectMethod("ParticleEffect", "float GetActiveTime() const", asMETHODPR(ParticleEffect, GetActiveTime, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEffect", "float get_activeTime() const", asMETHODPR(ParticleEffect, GetActiveTime, () const, float), asCALL_THISCALL);
    // float ParticleEffect::GetAnimationLodBias() const | File: ../Graphics/ParticleEffect.h
    engine->RegisterObjectMethod("ParticleEffect", "float GetAnimationLodBias() const", asMETHODPR(ParticleEffect, GetAnimationLodBias, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEffect", "float get_animationLodBias() const", asMETHODPR(ParticleEffect, GetAnimationLodBias, () const, float), asCALL_THISCALL);
    // AsyncLoadState Resource::GetAsyncLoadState() const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("ParticleEffect", "AsyncLoadState GetAsyncLoadState() const", asMETHODPR(ParticleEffect, GetAsyncLoadState, () const, AsyncLoadState), asCALL_THISCALL);
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ParticleEffect", "bool GetBlockEvents() const", asMETHODPR(ParticleEffect, GetBlockEvents, () const, bool), asCALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ParticleEffect", "const String& GetCategory() const", asMETHODPR(ParticleEffect, GetCategory, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEffect", "const String& get_category() const", asMETHODPR(ParticleEffect, GetCategory, () const, const String&), asCALL_THISCALL);
    // const ColorFrame* ParticleEffect::GetColorFrame(unsigned index) const | File: ../Graphics/ParticleEffect.h
    engine->RegisterObjectMethod("ParticleEffect", "ColorFrame@+ GetColorFrame(uint) const", asMETHODPR(ParticleEffect, GetColorFrame, (unsigned) const, const ColorFrame*), asCALL_THISCALL);
    // const Vector<ColorFrame>& ParticleEffect::GetColorFrames() const | File: ../Graphics/ParticleEffect.h
    // Error: type "const Vector<ColorFrame>&" can not automatically bind
    // const Vector3& ParticleEffect::GetConstantForce() const | File: ../Graphics/ParticleEffect.h
    engine->RegisterObjectMethod("ParticleEffect", "const Vector3& GetConstantForce() const", asMETHODPR(ParticleEffect, GetConstantForce, () const, const Vector3&), asCALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEffect", "const Vector3& get_constantForce() const", asMETHODPR(ParticleEffect, GetConstantForce, () const, const Vector3&), asCALL_THISCALL);
    // Context* Object::GetContext() const | File: ../Core/Object.h
    // Error: type "Context*" can used only as function parameter
    // float ParticleEffect::GetDampingForce() const | File: ../Graphics/ParticleEffect.h
    engine->RegisterObjectMethod("ParticleEffect", "float GetDampingForce() const", asMETHODPR(ParticleEffect, GetDampingForce, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEffect", "float get_dampingForce() const", asMETHODPR(ParticleEffect, GetDampingForce, () const, float), asCALL_THISCALL);
    // const Vector3& ParticleEffect::GetEmitterSize() const | File: ../Graphics/ParticleEffect.h
    engine->RegisterObjectMethod("ParticleEffect", "const Vector3& GetEmitterSize() const", asMETHODPR(ParticleEffect, GetEmitterSize, () const, const Vector3&), asCALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEffect", "const Vector3& get_emitterSize() const", asMETHODPR(ParticleEffect, GetEmitterSize, () const, const Vector3&), asCALL_THISCALL);
    // EmitterType ParticleEffect::GetEmitterType() const | File: ../Graphics/ParticleEffect.h
    engine->RegisterObjectMethod("ParticleEffect", "EmitterType GetEmitterType() const", asMETHODPR(ParticleEffect, GetEmitterType, () const, EmitterType), asCALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEffect", "EmitterType get_emitterType() const", asMETHODPR(ParticleEffect, GetEmitterType, () const, EmitterType), asCALL_THISCALL);
    // VariantMap& Object::GetEventDataMap() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ParticleEffect", "VariantMap& GetEventDataMap() const", asMETHODPR(ParticleEffect, GetEventDataMap, () const, VariantMap&), asCALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ParticleEffect", "Object@+ GetEventSender() const", asMETHODPR(ParticleEffect, GetEventSender, () const, Object*), asCALL_THISCALL);
    // FaceCameraMode ParticleEffect::GetFaceCameraMode() const | File: ../Graphics/ParticleEffect.h
    engine->RegisterObjectMethod("ParticleEffect", "FaceCameraMode GetFaceCameraMode() const", asMETHODPR(ParticleEffect, GetFaceCameraMode, () const, FaceCameraMode), asCALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEffect", "FaceCameraMode get_faceCameraMode() const", asMETHODPR(ParticleEffect, GetFaceCameraMode, () const, FaceCameraMode), asCALL_THISCALL);
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ParticleEffect", "const Variant& GetGlobalVar(StringHash) const", asMETHODPR(ParticleEffect, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEffect", "const Variant& get_globalVar(StringHash) const", asMETHODPR(ParticleEffect, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ParticleEffect", "const VariantMap& GetGlobalVars() const", asMETHODPR(ParticleEffect, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEffect", "const VariantMap& get_globalVars() const", asMETHODPR(ParticleEffect, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    // float ParticleEffect::GetInactiveTime() const | File: ../Graphics/ParticleEffect.h
    engine->RegisterObjectMethod("ParticleEffect", "float GetInactiveTime() const", asMETHODPR(ParticleEffect, GetInactiveTime, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEffect", "float get_inactiveTime() const", asMETHODPR(ParticleEffect, GetInactiveTime, () const, float), asCALL_THISCALL);
    // Material* ParticleEffect::GetMaterial() const | File: ../Graphics/ParticleEffect.h
    engine->RegisterObjectMethod("ParticleEffect", "Material@+ GetMaterial() const", asMETHODPR(ParticleEffect, GetMaterial, () const, Material*), asCALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEffect", "Material@+ get_material() const", asMETHODPR(ParticleEffect, GetMaterial, () const, Material*), asCALL_THISCALL);
    // const Vector3& ParticleEffect::GetMaxDirection() const | File: ../Graphics/ParticleEffect.h
    engine->RegisterObjectMethod("ParticleEffect", "const Vector3& GetMaxDirection() const", asMETHODPR(ParticleEffect, GetMaxDirection, () const, const Vector3&), asCALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEffect", "const Vector3& get_maxDirection() const", asMETHODPR(ParticleEffect, GetMaxDirection, () const, const Vector3&), asCALL_THISCALL);
    // float ParticleEffect::GetMaxEmissionRate() const | File: ../Graphics/ParticleEffect.h
    engine->RegisterObjectMethod("ParticleEffect", "float GetMaxEmissionRate() const", asMETHODPR(ParticleEffect, GetMaxEmissionRate, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEffect", "float get_maxEmissionRate() const", asMETHODPR(ParticleEffect, GetMaxEmissionRate, () const, float), asCALL_THISCALL);
    // const Vector2& ParticleEffect::GetMaxParticleSize() const | File: ../Graphics/ParticleEffect.h
    engine->RegisterObjectMethod("ParticleEffect", "const Vector2& GetMaxParticleSize() const", asMETHODPR(ParticleEffect, GetMaxParticleSize, () const, const Vector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEffect", "const Vector2& get_maxParticleSize() const", asMETHODPR(ParticleEffect, GetMaxParticleSize, () const, const Vector2&), asCALL_THISCALL);
    // float ParticleEffect::GetMaxRotation() const | File: ../Graphics/ParticleEffect.h
    engine->RegisterObjectMethod("ParticleEffect", "float GetMaxRotation() const", asMETHODPR(ParticleEffect, GetMaxRotation, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEffect", "float get_maxRotation() const", asMETHODPR(ParticleEffect, GetMaxRotation, () const, float), asCALL_THISCALL);
    // float ParticleEffect::GetMaxRotationSpeed() const | File: ../Graphics/ParticleEffect.h
    engine->RegisterObjectMethod("ParticleEffect", "float GetMaxRotationSpeed() const", asMETHODPR(ParticleEffect, GetMaxRotationSpeed, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEffect", "float get_maxRotationSpeed() const", asMETHODPR(ParticleEffect, GetMaxRotationSpeed, () const, float), asCALL_THISCALL);
    // float ParticleEffect::GetMaxTimeToLive() const | File: ../Graphics/ParticleEffect.h
    engine->RegisterObjectMethod("ParticleEffect", "float GetMaxTimeToLive() const", asMETHODPR(ParticleEffect, GetMaxTimeToLive, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEffect", "float get_maxTimeToLive() const", asMETHODPR(ParticleEffect, GetMaxTimeToLive, () const, float), asCALL_THISCALL);
    // float ParticleEffect::GetMaxVelocity() const | File: ../Graphics/ParticleEffect.h
    engine->RegisterObjectMethod("ParticleEffect", "float GetMaxVelocity() const", asMETHODPR(ParticleEffect, GetMaxVelocity, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEffect", "float get_maxVelocity() const", asMETHODPR(ParticleEffect, GetMaxVelocity, () const, float), asCALL_THISCALL);
    // unsigned Resource::GetMemoryUse() const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("ParticleEffect", "uint GetMemoryUse() const", asMETHODPR(ParticleEffect, GetMemoryUse, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEffect", "uint get_memoryUse() const", asMETHODPR(ParticleEffect, GetMemoryUse, () const, unsigned), asCALL_THISCALL);
    // const Vector3& ParticleEffect::GetMinDirection() const | File: ../Graphics/ParticleEffect.h
    engine->RegisterObjectMethod("ParticleEffect", "const Vector3& GetMinDirection() const", asMETHODPR(ParticleEffect, GetMinDirection, () const, const Vector3&), asCALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEffect", "const Vector3& get_minDirection() const", asMETHODPR(ParticleEffect, GetMinDirection, () const, const Vector3&), asCALL_THISCALL);
    // float ParticleEffect::GetMinEmissionRate() const | File: ../Graphics/ParticleEffect.h
    engine->RegisterObjectMethod("ParticleEffect", "float GetMinEmissionRate() const", asMETHODPR(ParticleEffect, GetMinEmissionRate, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEffect", "float get_minEmissionRate() const", asMETHODPR(ParticleEffect, GetMinEmissionRate, () const, float), asCALL_THISCALL);
    // const Vector2& ParticleEffect::GetMinParticleSize() const | File: ../Graphics/ParticleEffect.h
    engine->RegisterObjectMethod("ParticleEffect", "const Vector2& GetMinParticleSize() const", asMETHODPR(ParticleEffect, GetMinParticleSize, () const, const Vector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEffect", "const Vector2& get_minParticleSize() const", asMETHODPR(ParticleEffect, GetMinParticleSize, () const, const Vector2&), asCALL_THISCALL);
    // float ParticleEffect::GetMinRotation() const | File: ../Graphics/ParticleEffect.h
    engine->RegisterObjectMethod("ParticleEffect", "float GetMinRotation() const", asMETHODPR(ParticleEffect, GetMinRotation, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEffect", "float get_minRotation() const", asMETHODPR(ParticleEffect, GetMinRotation, () const, float), asCALL_THISCALL);
    // float ParticleEffect::GetMinRotationSpeed() const | File: ../Graphics/ParticleEffect.h
    engine->RegisterObjectMethod("ParticleEffect", "float GetMinRotationSpeed() const", asMETHODPR(ParticleEffect, GetMinRotationSpeed, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEffect", "float get_minRotationSpeed() const", asMETHODPR(ParticleEffect, GetMinRotationSpeed, () const, float), asCALL_THISCALL);
    // float ParticleEffect::GetMinTimeToLive() const | File: ../Graphics/ParticleEffect.h
    engine->RegisterObjectMethod("ParticleEffect", "float GetMinTimeToLive() const", asMETHODPR(ParticleEffect, GetMinTimeToLive, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEffect", "float get_minTimeToLive() const", asMETHODPR(ParticleEffect, GetMinTimeToLive, () const, float), asCALL_THISCALL);
    // float ParticleEffect::GetMinVelocity() const | File: ../Graphics/ParticleEffect.h
    engine->RegisterObjectMethod("ParticleEffect", "float GetMinVelocity() const", asMETHODPR(ParticleEffect, GetMinVelocity, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEffect", "float get_minVelocity() const", asMETHODPR(ParticleEffect, GetMinVelocity, () const, float), asCALL_THISCALL);
    // const String& Resource::GetName() const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("ParticleEffect", "const String& GetName() const", asMETHODPR(ParticleEffect, GetName, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEffect", "const String& get_name() const", asMETHODPR(ParticleEffect, GetName, () const, const String&), asCALL_THISCALL);
    // StringHash Resource::GetNameHash() const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("ParticleEffect", "StringHash GetNameHash() const", asMETHODPR(ParticleEffect, GetNameHash, () const, StringHash), asCALL_THISCALL);
    // unsigned ParticleEffect::GetNumColorFrames() const | File: ../Graphics/ParticleEffect.h
    engine->RegisterObjectMethod("ParticleEffect", "uint GetNumColorFrames() const", asMETHODPR(ParticleEffect, GetNumColorFrames, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEffect", "uint get_numColorFrames() const", asMETHODPR(ParticleEffect, GetNumColorFrames, () const, unsigned), asCALL_THISCALL);
    // unsigned ParticleEffect::GetNumParticles() const | File: ../Graphics/ParticleEffect.h
    engine->RegisterObjectMethod("ParticleEffect", "uint GetNumParticles() const", asMETHODPR(ParticleEffect, GetNumParticles, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEffect", "uint get_numParticles() const", asMETHODPR(ParticleEffect, GetNumParticles, () const, unsigned), asCALL_THISCALL);
    // unsigned ParticleEffect::GetNumTextureFrames() const | File: ../Graphics/ParticleEffect.h
    engine->RegisterObjectMethod("ParticleEffect", "uint GetNumTextureFrames() const", asMETHODPR(ParticleEffect, GetNumTextureFrames, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEffect", "uint get_numTextureFrames() const", asMETHODPR(ParticleEffect, GetNumTextureFrames, () const, unsigned), asCALL_THISCALL);
    // Vector3 ParticleEffect::GetRandomDirection() const | File: ../Graphics/ParticleEffect.h
    engine->RegisterObjectMethod("ParticleEffect", "Vector3 GetRandomDirection() const", asMETHODPR(ParticleEffect, GetRandomDirection, () const, Vector3), asCALL_THISCALL);
    // float ParticleEffect::GetRandomRotation() const | File: ../Graphics/ParticleEffect.h
    engine->RegisterObjectMethod("ParticleEffect", "float GetRandomRotation() const", asMETHODPR(ParticleEffect, GetRandomRotation, () const, float), asCALL_THISCALL);
    // float ParticleEffect::GetRandomRotationSpeed() const | File: ../Graphics/ParticleEffect.h
    engine->RegisterObjectMethod("ParticleEffect", "float GetRandomRotationSpeed() const", asMETHODPR(ParticleEffect, GetRandomRotationSpeed, () const, float), asCALL_THISCALL);
    // Vector2 ParticleEffect::GetRandomSize() const | File: ../Graphics/ParticleEffect.h
    engine->RegisterObjectMethod("ParticleEffect", "Vector2 GetRandomSize() const", asMETHODPR(ParticleEffect, GetRandomSize, () const, Vector2), asCALL_THISCALL);
    // float ParticleEffect::GetRandomTimeToLive() const | File: ../Graphics/ParticleEffect.h
    engine->RegisterObjectMethod("ParticleEffect", "float GetRandomTimeToLive() const", asMETHODPR(ParticleEffect, GetRandomTimeToLive, () const, float), asCALL_THISCALL);
    // float ParticleEffect::GetRandomVelocity() const | File: ../Graphics/ParticleEffect.h
    engine->RegisterObjectMethod("ParticleEffect", "float GetRandomVelocity() const", asMETHODPR(ParticleEffect, GetRandomVelocity, () const, float), asCALL_THISCALL);
    // float ParticleEffect::GetSizeAdd() const | File: ../Graphics/ParticleEffect.h
    engine->RegisterObjectMethod("ParticleEffect", "float GetSizeAdd() const", asMETHODPR(ParticleEffect, GetSizeAdd, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEffect", "float get_sizeAdd() const", asMETHODPR(ParticleEffect, GetSizeAdd, () const, float), asCALL_THISCALL);
    // float ParticleEffect::GetSizeMul() const | File: ../Graphics/ParticleEffect.h
    engine->RegisterObjectMethod("ParticleEffect", "float GetSizeMul() const", asMETHODPR(ParticleEffect, GetSizeMul, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEffect", "float get_sizeMul() const", asMETHODPR(ParticleEffect, GetSizeMul, () const, float), asCALL_THISCALL);
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ParticleEffect", "Object@+ GetSubsystem(StringHash) const", asMETHODPR(ParticleEffect, GetSubsystem, (StringHash) const, Object*), asCALL_THISCALL);
    // template<class T> T*  Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // const TextureFrame* ParticleEffect::GetTextureFrame(unsigned index) const | File: ../Graphics/ParticleEffect.h
    engine->RegisterObjectMethod("ParticleEffect", "TextureFrame@+ GetTextureFrame(uint) const", asMETHODPR(ParticleEffect, GetTextureFrame, (unsigned) const, const TextureFrame*), asCALL_THISCALL);
    // const Vector<TextureFrame>& ParticleEffect::GetTextureFrames() const | File: ../Graphics/ParticleEffect.h
    // Error: type "const Vector<TextureFrame>&" can not automatically bind
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("ParticleEffect", "StringHash GetType() const", asMETHODPR(ParticleEffect, GetType, () const, StringHash), asCALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEffect", "StringHash get_type() const", asMETHODPR(ParticleEffect, GetType, () const, StringHash), asCALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("ParticleEffect", "const String& GetTypeName() const", asMETHODPR(ParticleEffect, GetTypeName, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEffect", "const String& get_typeName() const", asMETHODPR(ParticleEffect, GetTypeName, () const, const String&), asCALL_THISCALL);
    // bool ParticleEffect::GetUpdateInvisible() const | File: ../Graphics/ParticleEffect.h
    engine->RegisterObjectMethod("ParticleEffect", "bool GetUpdateInvisible() const", asMETHODPR(ParticleEffect, GetUpdateInvisible, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEffect", "bool get_updateInvisible() const", asMETHODPR(ParticleEffect, GetUpdateInvisible, () const, bool), asCALL_THISCALL);
    // unsigned Resource::GetUseTimer() | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("ParticleEffect", "uint GetUseTimer()", asMETHODPR(ParticleEffect, GetUseTimer, (), unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEffect", "uint get_useTimer()", asMETHODPR(ParticleEffect, GetUseTimer, (), unsigned), asCALL_THISCALL);
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ParticleEffect", "bool HasEventHandlers() const", asMETHODPR(ParticleEffect, HasEventHandlers, () const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ParticleEffect", "bool HasSubscribedToEvent(StringHash) const", asMETHODPR(ParticleEffect, HasSubscribedToEvent, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ParticleEffect", "bool HasSubscribedToEvent(Object@+, StringHash) const", asMETHODPR(ParticleEffect, HasSubscribedToEvent, (Object*, StringHash) const, bool), asCALL_THISCALL);
    // bool ParticleEffect::IsFixedScreenSize() const | File: ../Graphics/ParticleEffect.h
    engine->RegisterObjectMethod("ParticleEffect", "bool IsFixedScreenSize() const", asMETHODPR(ParticleEffect, IsFixedScreenSize, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEffect", "bool get_fixedScreenSize() const", asMETHODPR(ParticleEffect, IsFixedScreenSize, () const, bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ParticleEffect", "bool IsInstanceOf(StringHash) const", asMETHODPR(ParticleEffect, IsInstanceOf, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // bool ParticleEffect::IsRelative() const | File: ../Graphics/ParticleEffect.h
    engine->RegisterObjectMethod("ParticleEffect", "bool IsRelative() const", asMETHODPR(ParticleEffect, IsRelative, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEffect", "bool get_relative() const", asMETHODPR(ParticleEffect, IsRelative, () const, bool), asCALL_THISCALL);
    // bool ParticleEffect::IsScaled() const | File: ../Graphics/ParticleEffect.h
    engine->RegisterObjectMethod("ParticleEffect", "bool IsScaled() const", asMETHODPR(ParticleEffect, IsScaled, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEffect", "bool get_scaled() const", asMETHODPR(ParticleEffect, IsScaled, () const, bool), asCALL_THISCALL);
    // bool ParticleEffect::IsSorted() const | File: ../Graphics/ParticleEffect.h
    engine->RegisterObjectMethod("ParticleEffect", "bool IsSorted() const", asMETHODPR(ParticleEffect, IsSorted, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEffect", "bool get_sorted() const", asMETHODPR(ParticleEffect, IsSorted, () const, bool), asCALL_THISCALL);
    // bool ParticleEffect::Load(const XMLElement& source) | File: ../Graphics/ParticleEffect.h
    engine->RegisterObjectMethod("ParticleEffect", "bool Load(const XMLElement&in)", asMETHODPR(ParticleEffect, Load, (const XMLElement&), bool), asCALL_THISCALL);
    // bool Resource::LoadFile(const String& fileName) | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("ParticleEffect", "bool LoadFile(const String&in)", asMETHODPR(ParticleEffect, LoadFile, (const String&), bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEffect", "bool Load(const String&in)", asMETHODPR(ParticleEffect, LoadFile, (const String&), bool), asCALL_THISCALL);
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ParticleEffect", "void OnEvent(Object@+, StringHash, VariantMap&)", asMETHODPR(ParticleEffect, OnEvent, (Object*, StringHash, VariantMap&), void), asCALL_THISCALL);
    // explicit ParticleEffect::ParticleEffect(Context* context) | File: ../Graphics/ParticleEffect.h
    engine->RegisterObjectBehaviour("ParticleEffect", asBEHAVE_FACTORY, "ParticleEffect@+ f()", asFUNCTION(ParticleEffect_ParticleEffect_Context), asCALL_CDECL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("ParticleEffect", "int Refs() const", asMETHODPR(ParticleEffect, Refs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEffect", "int get_refs() const", asMETHODPR(ParticleEffect, Refs, () const, int), asCALL_THISCALL);
    // static void ParticleEffect::RegisterObject(Context* context) | File: ../Graphics/ParticleEffect.h
    // Not registered because have @nobind mark
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("ParticleEffect", asBEHAVE_RELEASE, "void f()", asMETHODPR(ParticleEffect, ReleaseRef, (), void), asCALL_THISCALL);
    // void ParticleEffect::RemoveColorFrame(unsigned index) | File: ../Graphics/ParticleEffect.h
    engine->RegisterObjectMethod("ParticleEffect", "void RemoveColorFrame(uint)", asMETHODPR(ParticleEffect, RemoveColorFrame, (unsigned), void), asCALL_THISCALL);
    // void ParticleEffect::RemoveTextureFrame(unsigned index) | File: ../Graphics/ParticleEffect.h
    engine->RegisterObjectMethod("ParticleEffect", "void RemoveTextureFrame(uint)", asMETHODPR(ParticleEffect, RemoveTextureFrame, (unsigned), void), asCALL_THISCALL);
    // void Resource::ResetUseTimer() | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("ParticleEffect", "void ResetUseTimer()", asMETHODPR(ParticleEffect, ResetUseTimer, (), void), asCALL_THISCALL);
    // bool ParticleEffect::Save(Serializer& dest) const override | File: ../Graphics/ParticleEffect.h
    engine->RegisterObjectMethod("ParticleEffect", "bool Save(Serializer&) const", asMETHODPR(ParticleEffect, Save, (Serializer&) const, bool), asCALL_THISCALL);
    // bool ParticleEffect::Save(XMLElement& dest) const | File: ../Graphics/ParticleEffect.h
    engine->RegisterObjectMethod("ParticleEffect", "bool Save(XMLElement&) const", asMETHODPR(ParticleEffect, Save, (XMLElement&) const, bool), asCALL_THISCALL);
    // virtual bool Resource::SaveFile(const String& fileName) const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("ParticleEffect", "bool SaveFile(const String&in) const", asMETHODPR(ParticleEffect, SaveFile, (const String&) const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEffect", "bool Save(const String&in) const", asMETHODPR(ParticleEffect, SaveFile, (const String&) const, bool), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ParticleEffect", "void SendEvent(StringHash)", asMETHODPR(ParticleEffect, SendEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ParticleEffect", "void SendEvent(StringHash, VariantMap&)", asMETHODPR(ParticleEffect, SendEvent, (StringHash, VariantMap&), void), asCALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void ParticleEffect::SetActiveTime(float time) | File: ../Graphics/ParticleEffect.h
    engine->RegisterObjectMethod("ParticleEffect", "void SetActiveTime(float)", asMETHODPR(ParticleEffect, SetActiveTime, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEffect", "void set_activeTime(float)", asMETHODPR(ParticleEffect, SetActiveTime, (float), void), asCALL_THISCALL);
    // void ParticleEffect::SetAnimationLodBias(float lodBias) | File: ../Graphics/ParticleEffect.h
    engine->RegisterObjectMethod("ParticleEffect", "void SetAnimationLodBias(float)", asMETHODPR(ParticleEffect, SetAnimationLodBias, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEffect", "void set_animationLodBias(float)", asMETHODPR(ParticleEffect, SetAnimationLodBias, (float), void), asCALL_THISCALL);
    // void Resource::SetAsyncLoadState(AsyncLoadState newState) | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("ParticleEffect", "void SetAsyncLoadState(AsyncLoadState)", asMETHODPR(ParticleEffect, SetAsyncLoadState, (AsyncLoadState), void), asCALL_THISCALL);
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ParticleEffect", "void SetBlockEvents(bool)", asMETHODPR(ParticleEffect, SetBlockEvents, (bool), void), asCALL_THISCALL);
    // void ParticleEffect::SetColorFrame(unsigned index, const ColorFrame& colorFrame) | File: ../Graphics/ParticleEffect.h
    engine->RegisterObjectMethod("ParticleEffect", "void SetColorFrame(uint, const ColorFrame&in)", asMETHODPR(ParticleEffect, SetColorFrame, (unsigned, const ColorFrame&), void), asCALL_THISCALL);
    // void ParticleEffect::SetColorFrames(const Vector<ColorFrame>& colorFrames) | File: ../Graphics/ParticleEffect.h
    // Error: type "const Vector<ColorFrame>&" can not automatically bind
    // void ParticleEffect::SetConstantForce(const Vector3& force) | File: ../Graphics/ParticleEffect.h
    engine->RegisterObjectMethod("ParticleEffect", "void SetConstantForce(const Vector3&in)", asMETHODPR(ParticleEffect, SetConstantForce, (const Vector3&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEffect", "void set_constantForce(const Vector3&in)", asMETHODPR(ParticleEffect, SetConstantForce, (const Vector3&), void), asCALL_THISCALL);
    // void ParticleEffect::SetDampingForce(float force) | File: ../Graphics/ParticleEffect.h
    engine->RegisterObjectMethod("ParticleEffect", "void SetDampingForce(float)", asMETHODPR(ParticleEffect, SetDampingForce, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEffect", "void set_dampingForce(float)", asMETHODPR(ParticleEffect, SetDampingForce, (float), void), asCALL_THISCALL);
    // void ParticleEffect::SetEmitterSize(const Vector3& size) | File: ../Graphics/ParticleEffect.h
    engine->RegisterObjectMethod("ParticleEffect", "void SetEmitterSize(const Vector3&in)", asMETHODPR(ParticleEffect, SetEmitterSize, (const Vector3&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEffect", "void set_emitterSize(const Vector3&in)", asMETHODPR(ParticleEffect, SetEmitterSize, (const Vector3&), void), asCALL_THISCALL);
    // void ParticleEffect::SetEmitterType(EmitterType type) | File: ../Graphics/ParticleEffect.h
    engine->RegisterObjectMethod("ParticleEffect", "void SetEmitterType(EmitterType)", asMETHODPR(ParticleEffect, SetEmitterType, (EmitterType), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEffect", "void set_emitterType(EmitterType)", asMETHODPR(ParticleEffect, SetEmitterType, (EmitterType), void), asCALL_THISCALL);
    // void ParticleEffect::SetFaceCameraMode(FaceCameraMode mode) | File: ../Graphics/ParticleEffect.h
    engine->RegisterObjectMethod("ParticleEffect", "void SetFaceCameraMode(FaceCameraMode)", asMETHODPR(ParticleEffect, SetFaceCameraMode, (FaceCameraMode), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEffect", "void set_faceCameraMode(FaceCameraMode)", asMETHODPR(ParticleEffect, SetFaceCameraMode, (FaceCameraMode), void), asCALL_THISCALL);
    // void ParticleEffect::SetFixedScreenSize(bool enable) | File: ../Graphics/ParticleEffect.h
    engine->RegisterObjectMethod("ParticleEffect", "void SetFixedScreenSize(bool)", asMETHODPR(ParticleEffect, SetFixedScreenSize, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEffect", "void set_fixedScreenSize(bool)", asMETHODPR(ParticleEffect, SetFixedScreenSize, (bool), void), asCALL_THISCALL);
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ParticleEffect", "void SetGlobalVar(StringHash, const Variant&in)", asMETHODPR(ParticleEffect, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEffect", "void set_globalVar(StringHash, const Variant&in)", asMETHODPR(ParticleEffect, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    // void ParticleEffect::SetInactiveTime(float time) | File: ../Graphics/ParticleEffect.h
    engine->RegisterObjectMethod("ParticleEffect", "void SetInactiveTime(float)", asMETHODPR(ParticleEffect, SetInactiveTime, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEffect", "void set_inactiveTime(float)", asMETHODPR(ParticleEffect, SetInactiveTime, (float), void), asCALL_THISCALL);
    // void ParticleEffect::SetMaterial(Material* material) | File: ../Graphics/ParticleEffect.h
    engine->RegisterObjectMethod("ParticleEffect", "void SetMaterial(Material@+)", asMETHODPR(ParticleEffect, SetMaterial, (Material*), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEffect", "void set_material(Material@+)", asMETHODPR(ParticleEffect, SetMaterial, (Material*), void), asCALL_THISCALL);
    // void ParticleEffect::SetMaxDirection(const Vector3& direction) | File: ../Graphics/ParticleEffect.h
    engine->RegisterObjectMethod("ParticleEffect", "void SetMaxDirection(const Vector3&in)", asMETHODPR(ParticleEffect, SetMaxDirection, (const Vector3&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEffect", "void set_maxDirection(const Vector3&in)", asMETHODPR(ParticleEffect, SetMaxDirection, (const Vector3&), void), asCALL_THISCALL);
    // void ParticleEffect::SetMaxEmissionRate(float rate) | File: ../Graphics/ParticleEffect.h
    engine->RegisterObjectMethod("ParticleEffect", "void SetMaxEmissionRate(float)", asMETHODPR(ParticleEffect, SetMaxEmissionRate, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEffect", "void set_maxEmissionRate(float)", asMETHODPR(ParticleEffect, SetMaxEmissionRate, (float), void), asCALL_THISCALL);
    // void ParticleEffect::SetMaxParticleSize(const Vector2& size) | File: ../Graphics/ParticleEffect.h
    engine->RegisterObjectMethod("ParticleEffect", "void SetMaxParticleSize(const Vector2&in)", asMETHODPR(ParticleEffect, SetMaxParticleSize, (const Vector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEffect", "void set_maxParticleSize(const Vector2&in)", asMETHODPR(ParticleEffect, SetMaxParticleSize, (const Vector2&), void), asCALL_THISCALL);
    // void ParticleEffect::SetMaxRotation(float rotation) | File: ../Graphics/ParticleEffect.h
    engine->RegisterObjectMethod("ParticleEffect", "void SetMaxRotation(float)", asMETHODPR(ParticleEffect, SetMaxRotation, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEffect", "void set_maxRotation(float)", asMETHODPR(ParticleEffect, SetMaxRotation, (float), void), asCALL_THISCALL);
    // void ParticleEffect::SetMaxRotationSpeed(float speed) | File: ../Graphics/ParticleEffect.h
    engine->RegisterObjectMethod("ParticleEffect", "void SetMaxRotationSpeed(float)", asMETHODPR(ParticleEffect, SetMaxRotationSpeed, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEffect", "void set_maxRotationSpeed(float)", asMETHODPR(ParticleEffect, SetMaxRotationSpeed, (float), void), asCALL_THISCALL);
    // void ParticleEffect::SetMaxTimeToLive(float time) | File: ../Graphics/ParticleEffect.h
    engine->RegisterObjectMethod("ParticleEffect", "void SetMaxTimeToLive(float)", asMETHODPR(ParticleEffect, SetMaxTimeToLive, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEffect", "void set_maxTimeToLive(float)", asMETHODPR(ParticleEffect, SetMaxTimeToLive, (float), void), asCALL_THISCALL);
    // void ParticleEffect::SetMaxVelocity(float velocity) | File: ../Graphics/ParticleEffect.h
    engine->RegisterObjectMethod("ParticleEffect", "void SetMaxVelocity(float)", asMETHODPR(ParticleEffect, SetMaxVelocity, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEffect", "void set_maxVelocity(float)", asMETHODPR(ParticleEffect, SetMaxVelocity, (float), void), asCALL_THISCALL);
    // void Resource::SetMemoryUse(unsigned size) | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("ParticleEffect", "void SetMemoryUse(uint)", asMETHODPR(ParticleEffect, SetMemoryUse, (unsigned), void), asCALL_THISCALL);
    // void ParticleEffect::SetMinDirection(const Vector3& direction) | File: ../Graphics/ParticleEffect.h
    engine->RegisterObjectMethod("ParticleEffect", "void SetMinDirection(const Vector3&in)", asMETHODPR(ParticleEffect, SetMinDirection, (const Vector3&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEffect", "void set_minDirection(const Vector3&in)", asMETHODPR(ParticleEffect, SetMinDirection, (const Vector3&), void), asCALL_THISCALL);
    // void ParticleEffect::SetMinEmissionRate(float rate) | File: ../Graphics/ParticleEffect.h
    engine->RegisterObjectMethod("ParticleEffect", "void SetMinEmissionRate(float)", asMETHODPR(ParticleEffect, SetMinEmissionRate, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEffect", "void set_minEmissionRate(float)", asMETHODPR(ParticleEffect, SetMinEmissionRate, (float), void), asCALL_THISCALL);
    // void ParticleEffect::SetMinParticleSize(const Vector2& size) | File: ../Graphics/ParticleEffect.h
    engine->RegisterObjectMethod("ParticleEffect", "void SetMinParticleSize(const Vector2&in)", asMETHODPR(ParticleEffect, SetMinParticleSize, (const Vector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEffect", "void set_minParticleSize(const Vector2&in)", asMETHODPR(ParticleEffect, SetMinParticleSize, (const Vector2&), void), asCALL_THISCALL);
    // void ParticleEffect::SetMinRotation(float rotation) | File: ../Graphics/ParticleEffect.h
    engine->RegisterObjectMethod("ParticleEffect", "void SetMinRotation(float)", asMETHODPR(ParticleEffect, SetMinRotation, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEffect", "void set_minRotation(float)", asMETHODPR(ParticleEffect, SetMinRotation, (float), void), asCALL_THISCALL);
    // void ParticleEffect::SetMinRotationSpeed(float speed) | File: ../Graphics/ParticleEffect.h
    engine->RegisterObjectMethod("ParticleEffect", "void SetMinRotationSpeed(float)", asMETHODPR(ParticleEffect, SetMinRotationSpeed, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEffect", "void set_minRotationSpeed(float)", asMETHODPR(ParticleEffect, SetMinRotationSpeed, (float), void), asCALL_THISCALL);
    // void ParticleEffect::SetMinTimeToLive(float time) | File: ../Graphics/ParticleEffect.h
    engine->RegisterObjectMethod("ParticleEffect", "void SetMinTimeToLive(float)", asMETHODPR(ParticleEffect, SetMinTimeToLive, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEffect", "void set_minTimeToLive(float)", asMETHODPR(ParticleEffect, SetMinTimeToLive, (float), void), asCALL_THISCALL);
    // void ParticleEffect::SetMinVelocity(float velocity) | File: ../Graphics/ParticleEffect.h
    engine->RegisterObjectMethod("ParticleEffect", "void SetMinVelocity(float)", asMETHODPR(ParticleEffect, SetMinVelocity, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEffect", "void set_minVelocity(float)", asMETHODPR(ParticleEffect, SetMinVelocity, (float), void), asCALL_THISCALL);
    // void Resource::SetName(const String& name) | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("ParticleEffect", "void SetName(const String&in)", asMETHODPR(ParticleEffect, SetName, (const String&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEffect", "void set_name(const String&in)", asMETHODPR(ParticleEffect, SetName, (const String&), void), asCALL_THISCALL);
    // void ParticleEffect::SetNumColorFrames(unsigned number) | File: ../Graphics/ParticleEffect.h
    engine->RegisterObjectMethod("ParticleEffect", "void SetNumColorFrames(uint)", asMETHODPR(ParticleEffect, SetNumColorFrames, (unsigned), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEffect", "void set_numColorFrames(uint)", asMETHODPR(ParticleEffect, SetNumColorFrames, (unsigned), void), asCALL_THISCALL);
    // void ParticleEffect::SetNumParticles(unsigned num) | File: ../Graphics/ParticleEffect.h
    engine->RegisterObjectMethod("ParticleEffect", "void SetNumParticles(uint)", asMETHODPR(ParticleEffect, SetNumParticles, (unsigned), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEffect", "void set_numParticles(uint)", asMETHODPR(ParticleEffect, SetNumParticles, (unsigned), void), asCALL_THISCALL);
    // void ParticleEffect::SetNumTextureFrames(unsigned number) | File: ../Graphics/ParticleEffect.h
    engine->RegisterObjectMethod("ParticleEffect", "void SetNumTextureFrames(uint)", asMETHODPR(ParticleEffect, SetNumTextureFrames, (unsigned), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEffect", "void set_numTextureFrames(uint)", asMETHODPR(ParticleEffect, SetNumTextureFrames, (unsigned), void), asCALL_THISCALL);
    // void ParticleEffect::SetRelative(bool enable) | File: ../Graphics/ParticleEffect.h
    engine->RegisterObjectMethod("ParticleEffect", "void SetRelative(bool)", asMETHODPR(ParticleEffect, SetRelative, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEffect", "void set_relative(bool)", asMETHODPR(ParticleEffect, SetRelative, (bool), void), asCALL_THISCALL);
    // void ParticleEffect::SetScaled(bool enable) | File: ../Graphics/ParticleEffect.h
    engine->RegisterObjectMethod("ParticleEffect", "void SetScaled(bool)", asMETHODPR(ParticleEffect, SetScaled, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEffect", "void set_scaled(bool)", asMETHODPR(ParticleEffect, SetScaled, (bool), void), asCALL_THISCALL);
    // void ParticleEffect::SetSizeAdd(float sizeAdd) | File: ../Graphics/ParticleEffect.h
    engine->RegisterObjectMethod("ParticleEffect", "void SetSizeAdd(float)", asMETHODPR(ParticleEffect, SetSizeAdd, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEffect", "void set_sizeAdd(float)", asMETHODPR(ParticleEffect, SetSizeAdd, (float), void), asCALL_THISCALL);
    // void ParticleEffect::SetSizeMul(float sizeMul) | File: ../Graphics/ParticleEffect.h
    engine->RegisterObjectMethod("ParticleEffect", "void SetSizeMul(float)", asMETHODPR(ParticleEffect, SetSizeMul, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEffect", "void set_sizeMul(float)", asMETHODPR(ParticleEffect, SetSizeMul, (float), void), asCALL_THISCALL);
    // void ParticleEffect::SetSorted(bool enable) | File: ../Graphics/ParticleEffect.h
    engine->RegisterObjectMethod("ParticleEffect", "void SetSorted(bool)", asMETHODPR(ParticleEffect, SetSorted, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEffect", "void set_sorted(bool)", asMETHODPR(ParticleEffect, SetSorted, (bool), void), asCALL_THISCALL);
    // void ParticleEffect::SetTextureFrame(unsigned index, const TextureFrame& textureFrame) | File: ../Graphics/ParticleEffect.h
    engine->RegisterObjectMethod("ParticleEffect", "void SetTextureFrame(uint, const TextureFrame&in)", asMETHODPR(ParticleEffect, SetTextureFrame, (unsigned, const TextureFrame&), void), asCALL_THISCALL);
    // void ParticleEffect::SetTextureFrames(const Vector<TextureFrame>& textureFrames) | File: ../Graphics/ParticleEffect.h
    // Error: type "const Vector<TextureFrame>&" can not automatically bind
    // void ParticleEffect::SetUpdateInvisible(bool enable) | File: ../Graphics/ParticleEffect.h
    engine->RegisterObjectMethod("ParticleEffect", "void SetUpdateInvisible(bool)", asMETHODPR(ParticleEffect, SetUpdateInvisible, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEffect", "void set_updateInvisible(bool)", asMETHODPR(ParticleEffect, SetUpdateInvisible, (bool), void), asCALL_THISCALL);
    // void ParticleEffect::SortColorFrames() | File: ../Graphics/ParticleEffect.h
    engine->RegisterObjectMethod("ParticleEffect", "void SortColorFrames()", asMETHODPR(ParticleEffect, SortColorFrames, (), void), asCALL_THISCALL);
    // void ParticleEffect::SortTextureFrames() | File: ../Graphics/ParticleEffect.h
    engine->RegisterObjectMethod("ParticleEffect", "void SortTextureFrames()", asMETHODPR(ParticleEffect, SortTextureFrames, (), void), asCALL_THISCALL);
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod("ParticleEffect", "void UnsubscribeFromAllEvents()", asMETHODPR(ParticleEffect, UnsubscribeFromAllEvents, (), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ParticleEffect", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", asFUNCTION(ParticleEffect_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), asCALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ParticleEffect", "void UnsubscribeFromEvent(StringHash)", asMETHODPR(ParticleEffect, UnsubscribeFromEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ParticleEffect", "void UnsubscribeFromEvent(Object@+, StringHash)", asMETHODPR(ParticleEffect, UnsubscribeFromEvent, (Object*, StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ParticleEffect", "void UnsubscribeFromEvents(Object@+)", asMETHODPR(ParticleEffect, UnsubscribeFromEvents, (Object*), void), asCALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("ParticleEffect", "int WeakRefs() const", asMETHODPR(ParticleEffect, WeakRefs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEffect", "int get_weakRefs() const", asMETHODPR(ParticleEffect, WeakRefs, () const, int), asCALL_THISCALL);
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
    engine->RegisterObjectBehaviour("ParticleEffect2D", asBEHAVE_ADDREF, "void f()", asMETHODPR(ParticleEffect2D, AddRef, (), void), asCALL_THISCALL);
    // bool ParticleEffect2D::BeginLoad(Deserializer& source) override | File: ../Urho2D/ParticleEffect2D.h
    engine->RegisterObjectMethod("ParticleEffect2D", "bool BeginLoad(Deserializer&)", asMETHODPR(ParticleEffect2D, BeginLoad, (Deserializer&), bool), asCALL_THISCALL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // SharedPtr<ParticleEffect2D> ParticleEffect2D::Clone(const String& cloneName=String::EMPTY) const | File: ../Urho2D/ParticleEffect2D.h
    engine->RegisterObjectMethod("ParticleEffect2D", "ParticleEffect2D@+ Clone(const String&in = String::EMPTY) const", asFUNCTION(ParticleEffect2D_Clone_String), asCALL_CDECL_OBJFIRST);
    // bool ParticleEffect2D::EndLoad() override | File: ../Urho2D/ParticleEffect2D.h
    engine->RegisterObjectMethod("ParticleEffect2D", "bool EndLoad()", asMETHODPR(ParticleEffect2D, EndLoad, (), bool), asCALL_THISCALL);
    // float ParticleEffect2D::GetAngle() const | File: ../Urho2D/ParticleEffect2D.h
    engine->RegisterObjectMethod("ParticleEffect2D", "float GetAngle() const", asMETHODPR(ParticleEffect2D, GetAngle, () const, float), asCALL_THISCALL);
    // float ParticleEffect2D::GetAngleVariance() const | File: ../Urho2D/ParticleEffect2D.h
    engine->RegisterObjectMethod("ParticleEffect2D", "float GetAngleVariance() const", asMETHODPR(ParticleEffect2D, GetAngleVariance, () const, float), asCALL_THISCALL);
    // AsyncLoadState Resource::GetAsyncLoadState() const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("ParticleEffect2D", "AsyncLoadState GetAsyncLoadState() const", asMETHODPR(ParticleEffect2D, GetAsyncLoadState, () const, AsyncLoadState), asCALL_THISCALL);
    // BlendMode ParticleEffect2D::GetBlendMode() const | File: ../Urho2D/ParticleEffect2D.h
    engine->RegisterObjectMethod("ParticleEffect2D", "BlendMode GetBlendMode() const", asMETHODPR(ParticleEffect2D, GetBlendMode, () const, BlendMode), asCALL_THISCALL);
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ParticleEffect2D", "bool GetBlockEvents() const", asMETHODPR(ParticleEffect2D, GetBlockEvents, () const, bool), asCALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ParticleEffect2D", "const String& GetCategory() const", asMETHODPR(ParticleEffect2D, GetCategory, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEffect2D", "const String& get_category() const", asMETHODPR(ParticleEffect2D, GetCategory, () const, const String&), asCALL_THISCALL);
    // Context* Object::GetContext() const | File: ../Core/Object.h
    // Error: type "Context*" can used only as function parameter
    // float ParticleEffect2D::GetDuration() const | File: ../Urho2D/ParticleEffect2D.h
    engine->RegisterObjectMethod("ParticleEffect2D", "float GetDuration() const", asMETHODPR(ParticleEffect2D, GetDuration, () const, float), asCALL_THISCALL);
    // EmitterType2D ParticleEffect2D::GetEmitterType() const | File: ../Urho2D/ParticleEffect2D.h
    engine->RegisterObjectMethod("ParticleEffect2D", "EmitterType2D GetEmitterType() const", asMETHODPR(ParticleEffect2D, GetEmitterType, () const, EmitterType2D), asCALL_THISCALL);
    // VariantMap& Object::GetEventDataMap() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ParticleEffect2D", "VariantMap& GetEventDataMap() const", asMETHODPR(ParticleEffect2D, GetEventDataMap, () const, VariantMap&), asCALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ParticleEffect2D", "Object@+ GetEventSender() const", asMETHODPR(ParticleEffect2D, GetEventSender, () const, Object*), asCALL_THISCALL);
    // const Color& ParticleEffect2D::GetFinishColor() const | File: ../Urho2D/ParticleEffect2D.h
    engine->RegisterObjectMethod("ParticleEffect2D", "const Color& GetFinishColor() const", asMETHODPR(ParticleEffect2D, GetFinishColor, () const, const Color&), asCALL_THISCALL);
    // const Color& ParticleEffect2D::GetFinishColorVariance() const | File: ../Urho2D/ParticleEffect2D.h
    engine->RegisterObjectMethod("ParticleEffect2D", "const Color& GetFinishColorVariance() const", asMETHODPR(ParticleEffect2D, GetFinishColorVariance, () const, const Color&), asCALL_THISCALL);
    // float ParticleEffect2D::GetFinishParticleSize() const | File: ../Urho2D/ParticleEffect2D.h
    engine->RegisterObjectMethod("ParticleEffect2D", "float GetFinishParticleSize() const", asMETHODPR(ParticleEffect2D, GetFinishParticleSize, () const, float), asCALL_THISCALL);
    // float ParticleEffect2D::GetFinishParticleSizeVariance() const | File: ../Urho2D/ParticleEffect2D.h
    engine->RegisterObjectMethod("ParticleEffect2D", "float GetFinishParticleSizeVariance() const", asMETHODPR(ParticleEffect2D, GetFinishParticleSizeVariance, () const, float), asCALL_THISCALL);
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ParticleEffect2D", "const Variant& GetGlobalVar(StringHash) const", asMETHODPR(ParticleEffect2D, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEffect2D", "const Variant& get_globalVar(StringHash) const", asMETHODPR(ParticleEffect2D, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ParticleEffect2D", "const VariantMap& GetGlobalVars() const", asMETHODPR(ParticleEffect2D, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEffect2D", "const VariantMap& get_globalVars() const", asMETHODPR(ParticleEffect2D, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    // const Vector2& ParticleEffect2D::GetGravity() const | File: ../Urho2D/ParticleEffect2D.h
    engine->RegisterObjectMethod("ParticleEffect2D", "const Vector2& GetGravity() const", asMETHODPR(ParticleEffect2D, GetGravity, () const, const Vector2&), asCALL_THISCALL);
    // int ParticleEffect2D::GetMaxParticles() const | File: ../Urho2D/ParticleEffect2D.h
    engine->RegisterObjectMethod("ParticleEffect2D", "int GetMaxParticles() const", asMETHODPR(ParticleEffect2D, GetMaxParticles, () const, int), asCALL_THISCALL);
    // float ParticleEffect2D::GetMaxRadius() const | File: ../Urho2D/ParticleEffect2D.h
    engine->RegisterObjectMethod("ParticleEffect2D", "float GetMaxRadius() const", asMETHODPR(ParticleEffect2D, GetMaxRadius, () const, float), asCALL_THISCALL);
    // float ParticleEffect2D::GetMaxRadiusVariance() const | File: ../Urho2D/ParticleEffect2D.h
    engine->RegisterObjectMethod("ParticleEffect2D", "float GetMaxRadiusVariance() const", asMETHODPR(ParticleEffect2D, GetMaxRadiusVariance, () const, float), asCALL_THISCALL);
    // unsigned Resource::GetMemoryUse() const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("ParticleEffect2D", "uint GetMemoryUse() const", asMETHODPR(ParticleEffect2D, GetMemoryUse, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEffect2D", "uint get_memoryUse() const", asMETHODPR(ParticleEffect2D, GetMemoryUse, () const, unsigned), asCALL_THISCALL);
    // float ParticleEffect2D::GetMinRadius() const | File: ../Urho2D/ParticleEffect2D.h
    engine->RegisterObjectMethod("ParticleEffect2D", "float GetMinRadius() const", asMETHODPR(ParticleEffect2D, GetMinRadius, () const, float), asCALL_THISCALL);
    // float ParticleEffect2D::GetMinRadiusVariance() const | File: ../Urho2D/ParticleEffect2D.h
    engine->RegisterObjectMethod("ParticleEffect2D", "float GetMinRadiusVariance() const", asMETHODPR(ParticleEffect2D, GetMinRadiusVariance, () const, float), asCALL_THISCALL);
    // const String& Resource::GetName() const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("ParticleEffect2D", "const String& GetName() const", asMETHODPR(ParticleEffect2D, GetName, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEffect2D", "const String& get_name() const", asMETHODPR(ParticleEffect2D, GetName, () const, const String&), asCALL_THISCALL);
    // StringHash Resource::GetNameHash() const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("ParticleEffect2D", "StringHash GetNameHash() const", asMETHODPR(ParticleEffect2D, GetNameHash, () const, StringHash), asCALL_THISCALL);
    // float ParticleEffect2D::GetParticleLifeSpan() const | File: ../Urho2D/ParticleEffect2D.h
    engine->RegisterObjectMethod("ParticleEffect2D", "float GetParticleLifeSpan() const", asMETHODPR(ParticleEffect2D, GetParticleLifeSpan, () const, float), asCALL_THISCALL);
    // float ParticleEffect2D::GetParticleLifespanVariance() const | File: ../Urho2D/ParticleEffect2D.h
    engine->RegisterObjectMethod("ParticleEffect2D", "float GetParticleLifespanVariance() const", asMETHODPR(ParticleEffect2D, GetParticleLifespanVariance, () const, float), asCALL_THISCALL);
    // float ParticleEffect2D::GetRadialAcceleration() const | File: ../Urho2D/ParticleEffect2D.h
    engine->RegisterObjectMethod("ParticleEffect2D", "float GetRadialAcceleration() const", asMETHODPR(ParticleEffect2D, GetRadialAcceleration, () const, float), asCALL_THISCALL);
    // float ParticleEffect2D::GetRadialAccelVariance() const | File: ../Urho2D/ParticleEffect2D.h
    engine->RegisterObjectMethod("ParticleEffect2D", "float GetRadialAccelVariance() const", asMETHODPR(ParticleEffect2D, GetRadialAccelVariance, () const, float), asCALL_THISCALL);
    // float ParticleEffect2D::GetRotatePerSecond() const | File: ../Urho2D/ParticleEffect2D.h
    engine->RegisterObjectMethod("ParticleEffect2D", "float GetRotatePerSecond() const", asMETHODPR(ParticleEffect2D, GetRotatePerSecond, () const, float), asCALL_THISCALL);
    // float ParticleEffect2D::GetRotatePerSecondVariance() const | File: ../Urho2D/ParticleEffect2D.h
    engine->RegisterObjectMethod("ParticleEffect2D", "float GetRotatePerSecondVariance() const", asMETHODPR(ParticleEffect2D, GetRotatePerSecondVariance, () const, float), asCALL_THISCALL);
    // float ParticleEffect2D::GetRotationEnd() const | File: ../Urho2D/ParticleEffect2D.h
    engine->RegisterObjectMethod("ParticleEffect2D", "float GetRotationEnd() const", asMETHODPR(ParticleEffect2D, GetRotationEnd, () const, float), asCALL_THISCALL);
    // float ParticleEffect2D::GetRotationEndVariance() const | File: ../Urho2D/ParticleEffect2D.h
    engine->RegisterObjectMethod("ParticleEffect2D", "float GetRotationEndVariance() const", asMETHODPR(ParticleEffect2D, GetRotationEndVariance, () const, float), asCALL_THISCALL);
    // float ParticleEffect2D::GetRotationStart() const | File: ../Urho2D/ParticleEffect2D.h
    engine->RegisterObjectMethod("ParticleEffect2D", "float GetRotationStart() const", asMETHODPR(ParticleEffect2D, GetRotationStart, () const, float), asCALL_THISCALL);
    // float ParticleEffect2D::GetRotationStartVariance() const | File: ../Urho2D/ParticleEffect2D.h
    engine->RegisterObjectMethod("ParticleEffect2D", "float GetRotationStartVariance() const", asMETHODPR(ParticleEffect2D, GetRotationStartVariance, () const, float), asCALL_THISCALL);
    // const Vector2& ParticleEffect2D::GetSourcePositionVariance() const | File: ../Urho2D/ParticleEffect2D.h
    engine->RegisterObjectMethod("ParticleEffect2D", "const Vector2& GetSourcePositionVariance() const", asMETHODPR(ParticleEffect2D, GetSourcePositionVariance, () const, const Vector2&), asCALL_THISCALL);
    // float ParticleEffect2D::GetSpeed() const | File: ../Urho2D/ParticleEffect2D.h
    engine->RegisterObjectMethod("ParticleEffect2D", "float GetSpeed() const", asMETHODPR(ParticleEffect2D, GetSpeed, () const, float), asCALL_THISCALL);
    // float ParticleEffect2D::GetSpeedVariance() const | File: ../Urho2D/ParticleEffect2D.h
    engine->RegisterObjectMethod("ParticleEffect2D", "float GetSpeedVariance() const", asMETHODPR(ParticleEffect2D, GetSpeedVariance, () const, float), asCALL_THISCALL);
    // Sprite2D* ParticleEffect2D::GetSprite() const | File: ../Urho2D/ParticleEffect2D.h
    engine->RegisterObjectMethod("ParticleEffect2D", "Sprite2D@+ GetSprite() const", asMETHODPR(ParticleEffect2D, GetSprite, () const, Sprite2D*), asCALL_THISCALL);
    // const Color& ParticleEffect2D::GetStartColor() const | File: ../Urho2D/ParticleEffect2D.h
    engine->RegisterObjectMethod("ParticleEffect2D", "const Color& GetStartColor() const", asMETHODPR(ParticleEffect2D, GetStartColor, () const, const Color&), asCALL_THISCALL);
    // const Color& ParticleEffect2D::GetStartColorVariance() const | File: ../Urho2D/ParticleEffect2D.h
    engine->RegisterObjectMethod("ParticleEffect2D", "const Color& GetStartColorVariance() const", asMETHODPR(ParticleEffect2D, GetStartColorVariance, () const, const Color&), asCALL_THISCALL);
    // float ParticleEffect2D::GetStartParticleSize() const | File: ../Urho2D/ParticleEffect2D.h
    engine->RegisterObjectMethod("ParticleEffect2D", "float GetStartParticleSize() const", asMETHODPR(ParticleEffect2D, GetStartParticleSize, () const, float), asCALL_THISCALL);
    // float ParticleEffect2D::GetStartParticleSizeVariance() const | File: ../Urho2D/ParticleEffect2D.h
    engine->RegisterObjectMethod("ParticleEffect2D", "float GetStartParticleSizeVariance() const", asMETHODPR(ParticleEffect2D, GetStartParticleSizeVariance, () const, float), asCALL_THISCALL);
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ParticleEffect2D", "Object@+ GetSubsystem(StringHash) const", asMETHODPR(ParticleEffect2D, GetSubsystem, (StringHash) const, Object*), asCALL_THISCALL);
    // template<class T> T*  Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // float ParticleEffect2D::GetTangentialAcceleration() const | File: ../Urho2D/ParticleEffect2D.h
    engine->RegisterObjectMethod("ParticleEffect2D", "float GetTangentialAcceleration() const", asMETHODPR(ParticleEffect2D, GetTangentialAcceleration, () const, float), asCALL_THISCALL);
    // float ParticleEffect2D::GetTangentialAccelVariance() const | File: ../Urho2D/ParticleEffect2D.h
    engine->RegisterObjectMethod("ParticleEffect2D", "float GetTangentialAccelVariance() const", asMETHODPR(ParticleEffect2D, GetTangentialAccelVariance, () const, float), asCALL_THISCALL);
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("ParticleEffect2D", "StringHash GetType() const", asMETHODPR(ParticleEffect2D, GetType, () const, StringHash), asCALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEffect2D", "StringHash get_type() const", asMETHODPR(ParticleEffect2D, GetType, () const, StringHash), asCALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("ParticleEffect2D", "const String& GetTypeName() const", asMETHODPR(ParticleEffect2D, GetTypeName, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEffect2D", "const String& get_typeName() const", asMETHODPR(ParticleEffect2D, GetTypeName, () const, const String&), asCALL_THISCALL);
    // unsigned Resource::GetUseTimer() | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("ParticleEffect2D", "uint GetUseTimer()", asMETHODPR(ParticleEffect2D, GetUseTimer, (), unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEffect2D", "uint get_useTimer()", asMETHODPR(ParticleEffect2D, GetUseTimer, (), unsigned), asCALL_THISCALL);
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ParticleEffect2D", "bool HasEventHandlers() const", asMETHODPR(ParticleEffect2D, HasEventHandlers, () const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ParticleEffect2D", "bool HasSubscribedToEvent(StringHash) const", asMETHODPR(ParticleEffect2D, HasSubscribedToEvent, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ParticleEffect2D", "bool HasSubscribedToEvent(Object@+, StringHash) const", asMETHODPR(ParticleEffect2D, HasSubscribedToEvent, (Object*, StringHash) const, bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ParticleEffect2D", "bool IsInstanceOf(StringHash) const", asMETHODPR(ParticleEffect2D, IsInstanceOf, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // bool Resource::Load(Deserializer& source) | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("ParticleEffect2D", "bool Load(Deserializer&)", asMETHODPR(ParticleEffect2D, Load, (Deserializer&), bool), asCALL_THISCALL);
    // bool Resource::LoadFile(const String& fileName) | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("ParticleEffect2D", "bool LoadFile(const String&in)", asMETHODPR(ParticleEffect2D, LoadFile, (const String&), bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEffect2D", "bool Load(const String&in)", asMETHODPR(ParticleEffect2D, LoadFile, (const String&), bool), asCALL_THISCALL);
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ParticleEffect2D", "void OnEvent(Object@+, StringHash, VariantMap&)", asMETHODPR(ParticleEffect2D, OnEvent, (Object*, StringHash, VariantMap&), void), asCALL_THISCALL);
    // explicit ParticleEffect2D::ParticleEffect2D(Context* context) | File: ../Urho2D/ParticleEffect2D.h
    engine->RegisterObjectBehaviour("ParticleEffect2D", asBEHAVE_FACTORY, "ParticleEffect2D@+ f()", asFUNCTION(ParticleEffect2D_ParticleEffect2D_Context), asCALL_CDECL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("ParticleEffect2D", "int Refs() const", asMETHODPR(ParticleEffect2D, Refs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEffect2D", "int get_refs() const", asMETHODPR(ParticleEffect2D, Refs, () const, int), asCALL_THISCALL);
    // static void ParticleEffect2D::RegisterObject(Context* context) | File: ../Urho2D/ParticleEffect2D.h
    // Not registered because have @nobind mark
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("ParticleEffect2D", asBEHAVE_RELEASE, "void f()", asMETHODPR(ParticleEffect2D, ReleaseRef, (), void), asCALL_THISCALL);
    // void Resource::ResetUseTimer() | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("ParticleEffect2D", "void ResetUseTimer()", asMETHODPR(ParticleEffect2D, ResetUseTimer, (), void), asCALL_THISCALL);
    // bool ParticleEffect2D::Save(Serializer& dest) const override | File: ../Urho2D/ParticleEffect2D.h
    engine->RegisterObjectMethod("ParticleEffect2D", "bool Save(Serializer&) const", asMETHODPR(ParticleEffect2D, Save, (Serializer&) const, bool), asCALL_THISCALL);
    // virtual bool Resource::SaveFile(const String& fileName) const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("ParticleEffect2D", "bool SaveFile(const String&in) const", asMETHODPR(ParticleEffect2D, SaveFile, (const String&) const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEffect2D", "bool Save(const String&in) const", asMETHODPR(ParticleEffect2D, SaveFile, (const String&) const, bool), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ParticleEffect2D", "void SendEvent(StringHash)", asMETHODPR(ParticleEffect2D, SendEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ParticleEffect2D", "void SendEvent(StringHash, VariantMap&)", asMETHODPR(ParticleEffect2D, SendEvent, (StringHash, VariantMap&), void), asCALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void ParticleEffect2D::SetAngle(float angle) | File: ../Urho2D/ParticleEffect2D.h
    engine->RegisterObjectMethod("ParticleEffect2D", "void SetAngle(float)", asMETHODPR(ParticleEffect2D, SetAngle, (float), void), asCALL_THISCALL);
    // void ParticleEffect2D::SetAngleVariance(float angleVariance) | File: ../Urho2D/ParticleEffect2D.h
    engine->RegisterObjectMethod("ParticleEffect2D", "void SetAngleVariance(float)", asMETHODPR(ParticleEffect2D, SetAngleVariance, (float), void), asCALL_THISCALL);
    // void Resource::SetAsyncLoadState(AsyncLoadState newState) | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("ParticleEffect2D", "void SetAsyncLoadState(AsyncLoadState)", asMETHODPR(ParticleEffect2D, SetAsyncLoadState, (AsyncLoadState), void), asCALL_THISCALL);
    // void ParticleEffect2D::SetBlendMode(BlendMode blendMode) | File: ../Urho2D/ParticleEffect2D.h
    engine->RegisterObjectMethod("ParticleEffect2D", "void SetBlendMode(BlendMode)", asMETHODPR(ParticleEffect2D, SetBlendMode, (BlendMode), void), asCALL_THISCALL);
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ParticleEffect2D", "void SetBlockEvents(bool)", asMETHODPR(ParticleEffect2D, SetBlockEvents, (bool), void), asCALL_THISCALL);
    // void ParticleEffect2D::SetDuration(float duration) | File: ../Urho2D/ParticleEffect2D.h
    engine->RegisterObjectMethod("ParticleEffect2D", "void SetDuration(float)", asMETHODPR(ParticleEffect2D, SetDuration, (float), void), asCALL_THISCALL);
    // void ParticleEffect2D::SetEmitterType(EmitterType2D emitterType) | File: ../Urho2D/ParticleEffect2D.h
    engine->RegisterObjectMethod("ParticleEffect2D", "void SetEmitterType(EmitterType2D)", asMETHODPR(ParticleEffect2D, SetEmitterType, (EmitterType2D), void), asCALL_THISCALL);
    // void ParticleEffect2D::SetFinishColor(const Color& finishColor) | File: ../Urho2D/ParticleEffect2D.h
    engine->RegisterObjectMethod("ParticleEffect2D", "void SetFinishColor(const Color&in)", asMETHODPR(ParticleEffect2D, SetFinishColor, (const Color&), void), asCALL_THISCALL);
    // void ParticleEffect2D::SetFinishColorVariance(const Color& finishColorVariance) | File: ../Urho2D/ParticleEffect2D.h
    engine->RegisterObjectMethod("ParticleEffect2D", "void SetFinishColorVariance(const Color&in)", asMETHODPR(ParticleEffect2D, SetFinishColorVariance, (const Color&), void), asCALL_THISCALL);
    // void ParticleEffect2D::SetFinishParticleSize(float finishParticleSize) | File: ../Urho2D/ParticleEffect2D.h
    engine->RegisterObjectMethod("ParticleEffect2D", "void SetFinishParticleSize(float)", asMETHODPR(ParticleEffect2D, SetFinishParticleSize, (float), void), asCALL_THISCALL);
    // void ParticleEffect2D::SetFinishParticleSizeVariance(float finishParticleSizeVariance) | File: ../Urho2D/ParticleEffect2D.h
    engine->RegisterObjectMethod("ParticleEffect2D", "void SetFinishParticleSizeVariance(float)", asMETHODPR(ParticleEffect2D, SetFinishParticleSizeVariance, (float), void), asCALL_THISCALL);
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ParticleEffect2D", "void SetGlobalVar(StringHash, const Variant&in)", asMETHODPR(ParticleEffect2D, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEffect2D", "void set_globalVar(StringHash, const Variant&in)", asMETHODPR(ParticleEffect2D, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    // void ParticleEffect2D::SetGravity(const Vector2& gravity) | File: ../Urho2D/ParticleEffect2D.h
    engine->RegisterObjectMethod("ParticleEffect2D", "void SetGravity(const Vector2&in)", asMETHODPR(ParticleEffect2D, SetGravity, (const Vector2&), void), asCALL_THISCALL);
    // void ParticleEffect2D::SetMaxParticles(int maxParticles) | File: ../Urho2D/ParticleEffect2D.h
    engine->RegisterObjectMethod("ParticleEffect2D", "void SetMaxParticles(int)", asMETHODPR(ParticleEffect2D, SetMaxParticles, (int), void), asCALL_THISCALL);
    // void ParticleEffect2D::SetMaxRadius(float maxRadius) | File: ../Urho2D/ParticleEffect2D.h
    engine->RegisterObjectMethod("ParticleEffect2D", "void SetMaxRadius(float)", asMETHODPR(ParticleEffect2D, SetMaxRadius, (float), void), asCALL_THISCALL);
    // void ParticleEffect2D::SetMaxRadiusVariance(float maxRadiusVariance) | File: ../Urho2D/ParticleEffect2D.h
    engine->RegisterObjectMethod("ParticleEffect2D", "void SetMaxRadiusVariance(float)", asMETHODPR(ParticleEffect2D, SetMaxRadiusVariance, (float), void), asCALL_THISCALL);
    // void Resource::SetMemoryUse(unsigned size) | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("ParticleEffect2D", "void SetMemoryUse(uint)", asMETHODPR(ParticleEffect2D, SetMemoryUse, (unsigned), void), asCALL_THISCALL);
    // void ParticleEffect2D::SetMinRadius(float minRadius) | File: ../Urho2D/ParticleEffect2D.h
    engine->RegisterObjectMethod("ParticleEffect2D", "void SetMinRadius(float)", asMETHODPR(ParticleEffect2D, SetMinRadius, (float), void), asCALL_THISCALL);
    // void ParticleEffect2D::SetMinRadiusVariance(float minRadiusVariance) | File: ../Urho2D/ParticleEffect2D.h
    engine->RegisterObjectMethod("ParticleEffect2D", "void SetMinRadiusVariance(float)", asMETHODPR(ParticleEffect2D, SetMinRadiusVariance, (float), void), asCALL_THISCALL);
    // void Resource::SetName(const String& name) | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("ParticleEffect2D", "void SetName(const String&in)", asMETHODPR(ParticleEffect2D, SetName, (const String&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEffect2D", "void set_name(const String&in)", asMETHODPR(ParticleEffect2D, SetName, (const String&), void), asCALL_THISCALL);
    // void ParticleEffect2D::SetParticleLifeSpan(float particleLifeSpan) | File: ../Urho2D/ParticleEffect2D.h
    engine->RegisterObjectMethod("ParticleEffect2D", "void SetParticleLifeSpan(float)", asMETHODPR(ParticleEffect2D, SetParticleLifeSpan, (float), void), asCALL_THISCALL);
    // void ParticleEffect2D::SetParticleLifespanVariance(float particleLifespanVariance) | File: ../Urho2D/ParticleEffect2D.h
    engine->RegisterObjectMethod("ParticleEffect2D", "void SetParticleLifespanVariance(float)", asMETHODPR(ParticleEffect2D, SetParticleLifespanVariance, (float), void), asCALL_THISCALL);
    // void ParticleEffect2D::SetRadialAcceleration(float radialAcceleration) | File: ../Urho2D/ParticleEffect2D.h
    engine->RegisterObjectMethod("ParticleEffect2D", "void SetRadialAcceleration(float)", asMETHODPR(ParticleEffect2D, SetRadialAcceleration, (float), void), asCALL_THISCALL);
    // void ParticleEffect2D::SetRadialAccelVariance(float radialAccelVariance) | File: ../Urho2D/ParticleEffect2D.h
    engine->RegisterObjectMethod("ParticleEffect2D", "void SetRadialAccelVariance(float)", asMETHODPR(ParticleEffect2D, SetRadialAccelVariance, (float), void), asCALL_THISCALL);
    // void ParticleEffect2D::SetRotatePerSecond(float rotatePerSecond) | File: ../Urho2D/ParticleEffect2D.h
    engine->RegisterObjectMethod("ParticleEffect2D", "void SetRotatePerSecond(float)", asMETHODPR(ParticleEffect2D, SetRotatePerSecond, (float), void), asCALL_THISCALL);
    // void ParticleEffect2D::SetRotatePerSecondVariance(float rotatePerSecondVariance) | File: ../Urho2D/ParticleEffect2D.h
    engine->RegisterObjectMethod("ParticleEffect2D", "void SetRotatePerSecondVariance(float)", asMETHODPR(ParticleEffect2D, SetRotatePerSecondVariance, (float), void), asCALL_THISCALL);
    // void ParticleEffect2D::SetRotationEnd(float rotationEnd) | File: ../Urho2D/ParticleEffect2D.h
    engine->RegisterObjectMethod("ParticleEffect2D", "void SetRotationEnd(float)", asMETHODPR(ParticleEffect2D, SetRotationEnd, (float), void), asCALL_THISCALL);
    // void ParticleEffect2D::SetRotationEndVariance(float rotationEndVariance) | File: ../Urho2D/ParticleEffect2D.h
    engine->RegisterObjectMethod("ParticleEffect2D", "void SetRotationEndVariance(float)", asMETHODPR(ParticleEffect2D, SetRotationEndVariance, (float), void), asCALL_THISCALL);
    // void ParticleEffect2D::SetRotationStart(float rotationStart) | File: ../Urho2D/ParticleEffect2D.h
    engine->RegisterObjectMethod("ParticleEffect2D", "void SetRotationStart(float)", asMETHODPR(ParticleEffect2D, SetRotationStart, (float), void), asCALL_THISCALL);
    // void ParticleEffect2D::SetRotationStartVariance(float rotationStartVariance) | File: ../Urho2D/ParticleEffect2D.h
    engine->RegisterObjectMethod("ParticleEffect2D", "void SetRotationStartVariance(float)", asMETHODPR(ParticleEffect2D, SetRotationStartVariance, (float), void), asCALL_THISCALL);
    // void ParticleEffect2D::SetSourcePositionVariance(const Vector2& sourcePositionVariance) | File: ../Urho2D/ParticleEffect2D.h
    engine->RegisterObjectMethod("ParticleEffect2D", "void SetSourcePositionVariance(const Vector2&in)", asMETHODPR(ParticleEffect2D, SetSourcePositionVariance, (const Vector2&), void), asCALL_THISCALL);
    // void ParticleEffect2D::SetSpeed(float speed) | File: ../Urho2D/ParticleEffect2D.h
    engine->RegisterObjectMethod("ParticleEffect2D", "void SetSpeed(float)", asMETHODPR(ParticleEffect2D, SetSpeed, (float), void), asCALL_THISCALL);
    // void ParticleEffect2D::SetSpeedVariance(float speedVariance) | File: ../Urho2D/ParticleEffect2D.h
    engine->RegisterObjectMethod("ParticleEffect2D", "void SetSpeedVariance(float)", asMETHODPR(ParticleEffect2D, SetSpeedVariance, (float), void), asCALL_THISCALL);
    // void ParticleEffect2D::SetSprite(Sprite2D* sprite) | File: ../Urho2D/ParticleEffect2D.h
    engine->RegisterObjectMethod("ParticleEffect2D", "void SetSprite(Sprite2D@+)", asMETHODPR(ParticleEffect2D, SetSprite, (Sprite2D*), void), asCALL_THISCALL);
    // void ParticleEffect2D::SetStartColor(const Color& startColor) | File: ../Urho2D/ParticleEffect2D.h
    engine->RegisterObjectMethod("ParticleEffect2D", "void SetStartColor(const Color&in)", asMETHODPR(ParticleEffect2D, SetStartColor, (const Color&), void), asCALL_THISCALL);
    // void ParticleEffect2D::SetStartColorVariance(const Color& startColorVariance) | File: ../Urho2D/ParticleEffect2D.h
    engine->RegisterObjectMethod("ParticleEffect2D", "void SetStartColorVariance(const Color&in)", asMETHODPR(ParticleEffect2D, SetStartColorVariance, (const Color&), void), asCALL_THISCALL);
    // void ParticleEffect2D::SetStartParticleSize(float startParticleSize) | File: ../Urho2D/ParticleEffect2D.h
    engine->RegisterObjectMethod("ParticleEffect2D", "void SetStartParticleSize(float)", asMETHODPR(ParticleEffect2D, SetStartParticleSize, (float), void), asCALL_THISCALL);
    // void ParticleEffect2D::SetStartParticleSizeVariance(float startParticleSizeVariance) | File: ../Urho2D/ParticleEffect2D.h
    engine->RegisterObjectMethod("ParticleEffect2D", "void SetStartParticleSizeVariance(float)", asMETHODPR(ParticleEffect2D, SetStartParticleSizeVariance, (float), void), asCALL_THISCALL);
    // void ParticleEffect2D::SetTangentialAcceleration(float tangentialAcceleration) | File: ../Urho2D/ParticleEffect2D.h
    engine->RegisterObjectMethod("ParticleEffect2D", "void SetTangentialAcceleration(float)", asMETHODPR(ParticleEffect2D, SetTangentialAcceleration, (float), void), asCALL_THISCALL);
    // void ParticleEffect2D::SetTangentialAccelVariance(float tangentialAccelVariance) | File: ../Urho2D/ParticleEffect2D.h
    engine->RegisterObjectMethod("ParticleEffect2D", "void SetTangentialAccelVariance(float)", asMETHODPR(ParticleEffect2D, SetTangentialAccelVariance, (float), void), asCALL_THISCALL);
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod("ParticleEffect2D", "void UnsubscribeFromAllEvents()", asMETHODPR(ParticleEffect2D, UnsubscribeFromAllEvents, (), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ParticleEffect2D", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", asFUNCTION(ParticleEffect2D_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), asCALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ParticleEffect2D", "void UnsubscribeFromEvent(StringHash)", asMETHODPR(ParticleEffect2D, UnsubscribeFromEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ParticleEffect2D", "void UnsubscribeFromEvent(Object@+, StringHash)", asMETHODPR(ParticleEffect2D, UnsubscribeFromEvent, (Object*, StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ParticleEffect2D", "void UnsubscribeFromEvents(Object@+)", asMETHODPR(ParticleEffect2D, UnsubscribeFromEvents, (Object*), void), asCALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("ParticleEffect2D", "int WeakRefs() const", asMETHODPR(ParticleEffect2D, WeakRefs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEffect2D", "int get_weakRefs() const", asMETHODPR(ParticleEffect2D, WeakRefs, () const, int), asCALL_THISCALL);
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
    engine->RegisterObjectMethod("ParticleEmitter", "void AddLight(Light@+)", asMETHODPR(ParticleEmitter, AddLight, (Light*), void), asCALL_THISCALL);
    // void RefCounted::AddRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("ParticleEmitter", asBEHAVE_ADDREF, "void f()", asMETHODPR(ParticleEmitter, AddRef, (), void), asCALL_THISCALL);
    // void Component::AddReplicationState(ComponentReplicationState* state) | File: ../Scene/Component.h
    // Error: type "ComponentReplicationState*" can not automatically bind
    // void Drawable::AddVertexLight(Light* light) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("ParticleEmitter", "void AddVertexLight(Light@+)", asMETHODPR(ParticleEmitter, AddVertexLight, (Light*), void), asCALL_THISCALL);
    // void Serializable::AllocateNetworkState() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ParticleEmitter", "void AllocateNetworkState()", asMETHODPR(ParticleEmitter, AllocateNetworkState, (), void), asCALL_THISCALL);
    // virtual void Serializable::ApplyAttributes() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ParticleEmitter", "void ApplyAttributes()", asMETHODPR(ParticleEmitter, ApplyAttributes, (), void), asCALL_THISCALL);
    // void ParticleEmitter::ApplyEffect() | File: ../Graphics/ParticleEmitter.h
    engine->RegisterObjectMethod("ParticleEmitter", "void ApplyEffect()", asMETHODPR(ParticleEmitter, ApplyEffect, (), void), asCALL_THISCALL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // void Component::CleanupConnection(Connection* connection) | File: ../Scene/Component.h
    // Not registered because have @manualbind mark
    // void BillboardSet::Commit() | File: ../Graphics/BillboardSet.h
    engine->RegisterObjectMethod("ParticleEmitter", "void Commit()", asMETHODPR(ParticleEmitter, Commit, (), void), asCALL_THISCALL);
    // void Drawable::DrawDebugGeometry(DebugRenderer* debug, bool depthTest) override | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("ParticleEmitter", "void DrawDebugGeometry(DebugRenderer@+, bool)", asMETHODPR(ParticleEmitter, DrawDebugGeometry, (DebugRenderer*, bool), void), asCALL_THISCALL);
    // virtual bool Drawable::DrawOcclusion(OcclusionBuffer* buffer) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("ParticleEmitter", "bool DrawOcclusion(OcclusionBuffer@+)", asMETHODPR(ParticleEmitter, DrawOcclusion, (OcclusionBuffer*), bool), asCALL_THISCALL);
    // bool Animatable::GetAnimationEnabled() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ParticleEmitter", "bool GetAnimationEnabled() const", asMETHODPR(ParticleEmitter, GetAnimationEnabled, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter", "bool get_animationEnabled() const", asMETHODPR(ParticleEmitter, GetAnimationEnabled, () const, bool), asCALL_THISCALL);
    // float BillboardSet::GetAnimationLodBias() const | File: ../Graphics/BillboardSet.h
    engine->RegisterObjectMethod("ParticleEmitter", "float GetAnimationLodBias() const", asMETHODPR(ParticleEmitter, GetAnimationLodBias, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter", "float get_animationLodBias() const", asMETHODPR(ParticleEmitter, GetAnimationLodBias, () const, float), asCALL_THISCALL);
    // Variant Serializable::GetAttribute(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ParticleEmitter", "Variant GetAttribute(uint) const", asMETHODPR(ParticleEmitter, GetAttribute, (unsigned) const, Variant), asCALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter", "Variant get_attributes(uint) const", asMETHODPR(ParticleEmitter, GetAttribute, (unsigned) const, Variant), asCALL_THISCALL);
    // Variant Serializable::GetAttribute(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ParticleEmitter", "Variant GetAttribute(const String&in) const", asMETHODPR(ParticleEmitter, GetAttribute, (const String&) const, Variant), asCALL_THISCALL);
    // ValueAnimation* Animatable::GetAttributeAnimation(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ParticleEmitter", "ValueAnimation@+ GetAttributeAnimation(const String&in) const", asMETHODPR(ParticleEmitter, GetAttributeAnimation, (const String&) const, ValueAnimation*), asCALL_THISCALL);
    // float Animatable::GetAttributeAnimationSpeed(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ParticleEmitter", "float GetAttributeAnimationSpeed(const String&in) const", asMETHODPR(ParticleEmitter, GetAttributeAnimationSpeed, (const String&) const, float), asCALL_THISCALL);
    // float Animatable::GetAttributeAnimationTime(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ParticleEmitter", "float GetAttributeAnimationTime(const String&in) const", asMETHODPR(ParticleEmitter, GetAttributeAnimationTime, (const String&) const, float), asCALL_THISCALL);
    // WrapMode Animatable::GetAttributeAnimationWrapMode(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ParticleEmitter", "WrapMode GetAttributeAnimationWrapMode(const String&in) const", asMETHODPR(ParticleEmitter, GetAttributeAnimationWrapMode, (const String&) const, WrapMode), asCALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ParticleEmitter", "Variant GetAttributeDefault(uint) const", asMETHODPR(ParticleEmitter, GetAttributeDefault, (unsigned) const, Variant), asCALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter", "Variant get_attributeDefaults(uint) const", asMETHODPR(ParticleEmitter, GetAttributeDefault, (unsigned) const, Variant), asCALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ParticleEmitter", "Variant GetAttributeDefault(const String&in) const", asMETHODPR(ParticleEmitter, GetAttributeDefault, (const String&) const, Variant), asCALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // AutoRemoveMode ParticleEmitter::GetAutoRemoveMode() const | File: ../Graphics/ParticleEmitter.h
    engine->RegisterObjectMethod("ParticleEmitter", "AutoRemoveMode GetAutoRemoveMode() const", asMETHODPR(ParticleEmitter, GetAutoRemoveMode, () const, AutoRemoveMode), asCALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter", "AutoRemoveMode get_autoRemoveMode() const", asMETHODPR(ParticleEmitter, GetAutoRemoveMode, () const, AutoRemoveMode), asCALL_THISCALL);
    // const Vector<SourceBatch>& Drawable::GetBatches() const | File: ../Graphics/Drawable.h
    // Error: type "const Vector<SourceBatch>&" can not automatically bind
    // Billboard* BillboardSet::GetBillboard(unsigned index) | File: ../Graphics/BillboardSet.h
    engine->RegisterObjectMethod("ParticleEmitter", "Billboard@+ GetBillboard(uint)", asMETHODPR(ParticleEmitter, GetBillboard, (unsigned), Billboard*), asCALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter", "Billboard@+ get_billboards(uint)", asMETHODPR(ParticleEmitter, GetBillboard, (unsigned), Billboard*), asCALL_THISCALL);
    // PODVector<Billboard>& BillboardSet::GetBillboards() | File: ../Graphics/BillboardSet.h
    // Error: type "PODVector<Billboard>&" can not automatically bind
    // VariantVector BillboardSet::GetBillboardsAttr() const | File: ../Graphics/BillboardSet.h
    // Error: type "VariantVector" can not automatically bind
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ParticleEmitter", "bool GetBlockEvents() const", asMETHODPR(ParticleEmitter, GetBlockEvents, () const, bool), asCALL_THISCALL);
    // const BoundingBox& Drawable::GetBoundingBox() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("ParticleEmitter", "const BoundingBox& GetBoundingBox() const", asMETHODPR(ParticleEmitter, GetBoundingBox, () const, const BoundingBox&), asCALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter", "const BoundingBox& get_boundingBox() const", asMETHODPR(ParticleEmitter, GetBoundingBox, () const, const BoundingBox&), asCALL_THISCALL);
    // bool Drawable::GetCastShadows() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("ParticleEmitter", "bool GetCastShadows() const", asMETHODPR(ParticleEmitter, GetCastShadows, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter", "bool get_castShadows() const", asMETHODPR(ParticleEmitter, GetCastShadows, () const, bool), asCALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ParticleEmitter", "const String& GetCategory() const", asMETHODPR(ParticleEmitter, GetCategory, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter", "const String& get_category() const", asMETHODPR(ParticleEmitter, GetCategory, () const, const String&), asCALL_THISCALL);
    // Component* Component::GetComponent(StringHash type) const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ParticleEmitter", "Component@+ GetComponent(StringHash) const", asMETHODPR(ParticleEmitter, GetComponent, (StringHash) const, Component*), asCALL_THISCALL);
    // template<class T> T*  Component::GetComponent() const | File: ../Scene/Component.h
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
    engine->RegisterObjectMethod("ParticleEmitter", "float GetDistance() const", asMETHODPR(ParticleEmitter, GetDistance, () const, float), asCALL_THISCALL);
    // unsigned char Drawable::GetDrawableFlags() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("ParticleEmitter", "uint8 GetDrawableFlags() const", asMETHODPR(ParticleEmitter, GetDrawableFlags, () const, unsigned char), asCALL_THISCALL);
    // float Drawable::GetDrawDistance() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("ParticleEmitter", "float GetDrawDistance() const", asMETHODPR(ParticleEmitter, GetDrawDistance, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter", "float get_drawDistance() const", asMETHODPR(ParticleEmitter, GetDrawDistance, () const, float), asCALL_THISCALL);
    // ParticleEffect* ParticleEmitter::GetEffect() const | File: ../Graphics/ParticleEmitter.h
    engine->RegisterObjectMethod("ParticleEmitter", "ParticleEffect@+ GetEffect() const", asMETHODPR(ParticleEmitter, GetEffect, () const, ParticleEffect*), asCALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter", "ParticleEffect@+ get_effect() const", asMETHODPR(ParticleEmitter, GetEffect, () const, ParticleEffect*), asCALL_THISCALL);
    // ResourceRef ParticleEmitter::GetEffectAttr() const | File: ../Graphics/ParticleEmitter.h
    engine->RegisterObjectMethod("ParticleEmitter", "ResourceRef GetEffectAttr() const", asMETHODPR(ParticleEmitter, GetEffectAttr, () const, ResourceRef), asCALL_THISCALL);
    // VariantMap& Object::GetEventDataMap() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ParticleEmitter", "VariantMap& GetEventDataMap() const", asMETHODPR(ParticleEmitter, GetEventDataMap, () const, VariantMap&), asCALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ParticleEmitter", "Object@+ GetEventSender() const", asMETHODPR(ParticleEmitter, GetEventSender, () const, Object*), asCALL_THISCALL);
    // FaceCameraMode BillboardSet::GetFaceCameraMode() const | File: ../Graphics/BillboardSet.h
    engine->RegisterObjectMethod("ParticleEmitter", "FaceCameraMode GetFaceCameraMode() const", asMETHODPR(ParticleEmitter, GetFaceCameraMode, () const, FaceCameraMode), asCALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter", "FaceCameraMode get_faceCameraMode() const", asMETHODPR(ParticleEmitter, GetFaceCameraMode, () const, FaceCameraMode), asCALL_THISCALL);
    // Light* Drawable::GetFirstLight() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("ParticleEmitter", "Light@+ GetFirstLight() const", asMETHODPR(ParticleEmitter, GetFirstLight, () const, Light*), asCALL_THISCALL);
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ParticleEmitter", "const Variant& GetGlobalVar(StringHash) const", asMETHODPR(ParticleEmitter, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter", "const Variant& get_globalVar(StringHash) const", asMETHODPR(ParticleEmitter, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ParticleEmitter", "const VariantMap& GetGlobalVars() const", asMETHODPR(ParticleEmitter, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter", "const VariantMap& get_globalVars() const", asMETHODPR(ParticleEmitter, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    // unsigned Component::GetID() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ParticleEmitter", "uint GetID() const", asMETHODPR(ParticleEmitter, GetID, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter", "uint get_id() const", asMETHODPR(ParticleEmitter, GetID, () const, unsigned), asCALL_THISCALL);
    // bool Serializable::GetInterceptNetworkUpdate(const String& attributeName) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ParticleEmitter", "bool GetInterceptNetworkUpdate(const String&in) const", asMETHODPR(ParticleEmitter, GetInterceptNetworkUpdate, (const String&) const, bool), asCALL_THISCALL);
    // unsigned Drawable::GetLightMask() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("ParticleEmitter", "uint GetLightMask() const", asMETHODPR(ParticleEmitter, GetLightMask, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter", "uint get_lightMask() const", asMETHODPR(ParticleEmitter, GetLightMask, () const, unsigned), asCALL_THISCALL);
    // const PODVector<Light*>& Drawable::GetLights() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("ParticleEmitter", "Array<Light@>@ GetLights() const", asFUNCTION(ParticleEmitter_GetLights_void), asCALL_CDECL_OBJFIRST);
    // float Drawable::GetLodBias() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("ParticleEmitter", "float GetLodBias() const", asMETHODPR(ParticleEmitter, GetLodBias, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter", "float get_lodBias() const", asMETHODPR(ParticleEmitter, GetLodBias, () const, float), asCALL_THISCALL);
    // float Drawable::GetLodDistance() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("ParticleEmitter", "float GetLodDistance() const", asMETHODPR(ParticleEmitter, GetLodDistance, () const, float), asCALL_THISCALL);
    // virtual Geometry* Drawable::GetLodGeometry(unsigned batchIndex, unsigned level) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("ParticleEmitter", "Geometry@+ GetLodGeometry(uint, uint)", asMETHODPR(ParticleEmitter, GetLodGeometry, (unsigned, unsigned), Geometry*), asCALL_THISCALL);
    // Material* BillboardSet::GetMaterial() const | File: ../Graphics/BillboardSet.h
    engine->RegisterObjectMethod("ParticleEmitter", "Material@+ GetMaterial() const", asMETHODPR(ParticleEmitter, GetMaterial, () const, Material*), asCALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter", "Material@+ get_material() const", asMETHODPR(ParticleEmitter, GetMaterial, () const, Material*), asCALL_THISCALL);
    // ResourceRef BillboardSet::GetMaterialAttr() const | File: ../Graphics/BillboardSet.h
    engine->RegisterObjectMethod("ParticleEmitter", "ResourceRef GetMaterialAttr() const", asMETHODPR(ParticleEmitter, GetMaterialAttr, () const, ResourceRef), asCALL_THISCALL);
    // unsigned Drawable::GetMaxLights() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("ParticleEmitter", "uint GetMaxLights() const", asMETHODPR(ParticleEmitter, GetMaxLights, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter", "uint get_maxLights() const", asMETHODPR(ParticleEmitter, GetMaxLights, () const, unsigned), asCALL_THISCALL);
    // float Drawable::GetMaxZ() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("ParticleEmitter", "float GetMaxZ() const", asMETHODPR(ParticleEmitter, GetMaxZ, () const, float), asCALL_THISCALL);
    // float BillboardSet::GetMinAngle() const | File: ../Graphics/BillboardSet.h
    engine->RegisterObjectMethod("ParticleEmitter", "float GetMinAngle() const", asMETHODPR(ParticleEmitter, GetMinAngle, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter", "float get_minAngle() const", asMETHODPR(ParticleEmitter, GetMinAngle, () const, float), asCALL_THISCALL);
    // float Drawable::GetMinZ() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("ParticleEmitter", "float GetMinZ() const", asMETHODPR(ParticleEmitter, GetMinZ, () const, float), asCALL_THISCALL);
    // const PODVector<unsigned char>& BillboardSet::GetNetBillboardsAttr() const | File: ../Graphics/BillboardSet.h
    // Error: type "const PODVector<unsigned char>&" can not automatically bind
    // virtual const Vector<AttributeInfo>* Serializable::GetNetworkAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // NetworkState* Serializable::GetNetworkState() const | File: ../Scene/Serializable.h
    // Error: type "NetworkState*" can not automatically bind
    // Node* Component::GetNode() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ParticleEmitter", "Node@+ GetNode() const", asMETHODPR(ParticleEmitter, GetNode, () const, Node*), asCALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter", "Node@+ get_node() const", asMETHODPR(ParticleEmitter, GetNode, () const, Node*), asCALL_THISCALL);
    // unsigned Serializable::GetNumAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ParticleEmitter", "uint GetNumAttributes() const", asMETHODPR(ParticleEmitter, GetNumAttributes, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter", "uint get_numAttributes() const", asMETHODPR(ParticleEmitter, GetNumAttributes, () const, unsigned), asCALL_THISCALL);
    // unsigned BillboardSet::GetNumBillboards() const | File: ../Graphics/BillboardSet.h
    engine->RegisterObjectMethod("ParticleEmitter", "uint GetNumBillboards() const", asMETHODPR(ParticleEmitter, GetNumBillboards, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter", "uint get_numBillboards() const", asMETHODPR(ParticleEmitter, GetNumBillboards, () const, unsigned), asCALL_THISCALL);
    // unsigned Serializable::GetNumNetworkAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ParticleEmitter", "uint GetNumNetworkAttributes() const", asMETHODPR(ParticleEmitter, GetNumNetworkAttributes, () const, unsigned), asCALL_THISCALL);
    // virtual unsigned Drawable::GetNumOccluderTriangles() | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("ParticleEmitter", "uint GetNumOccluderTriangles()", asMETHODPR(ParticleEmitter, GetNumOccluderTriangles, (), unsigned), asCALL_THISCALL);
    // unsigned ParticleEmitter::GetNumParticles() const | File: ../Graphics/ParticleEmitter.h
    engine->RegisterObjectMethod("ParticleEmitter", "uint GetNumParticles() const", asMETHODPR(ParticleEmitter, GetNumParticles, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter", "uint get_numParticles() const", asMETHODPR(ParticleEmitter, GetNumParticles, () const, unsigned), asCALL_THISCALL);
    // ObjectAnimation* Animatable::GetObjectAnimation() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ParticleEmitter", "ObjectAnimation@+ GetObjectAnimation() const", asMETHODPR(ParticleEmitter, GetObjectAnimation, () const, ObjectAnimation*), asCALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter", "ObjectAnimation@+ get_objectAnimation() const", asMETHODPR(ParticleEmitter, GetObjectAnimation, () const, ObjectAnimation*), asCALL_THISCALL);
    // ResourceRef Animatable::GetObjectAnimationAttr() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ParticleEmitter", "ResourceRef GetObjectAnimationAttr() const", asMETHODPR(ParticleEmitter, GetObjectAnimationAttr, () const, ResourceRef), asCALL_THISCALL);
    // Octant* Drawable::GetOctant() const | File: ../Graphics/Drawable.h
    // Error: type "Octant" can not automatically bind bacause have @nobind mark
    // VariantVector ParticleEmitter::GetParticleBillboardsAttr() const | File: ../Graphics/ParticleEmitter.h
    // Error: type "VariantVector" can not automatically bind
    // VariantVector ParticleEmitter::GetParticlesAttr() const | File: ../Graphics/ParticleEmitter.h
    // Error: type "VariantVector" can not automatically bind
    // Scene* Component::GetScene() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ParticleEmitter", "Scene@+ GetScene() const", asMETHODPR(ParticleEmitter, GetScene, () const, Scene*), asCALL_THISCALL);
    // bool ParticleEmitter::GetSerializeParticles() const | File: ../Graphics/ParticleEmitter.h
    engine->RegisterObjectMethod("ParticleEmitter", "bool GetSerializeParticles() const", asMETHODPR(ParticleEmitter, GetSerializeParticles, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter", "bool get_serializeParticles() const", asMETHODPR(ParticleEmitter, GetSerializeParticles, () const, bool), asCALL_THISCALL);
    // float Drawable::GetShadowDistance() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("ParticleEmitter", "float GetShadowDistance() const", asMETHODPR(ParticleEmitter, GetShadowDistance, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter", "float get_shadowDistance() const", asMETHODPR(ParticleEmitter, GetShadowDistance, () const, float), asCALL_THISCALL);
    // unsigned Drawable::GetShadowMask() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("ParticleEmitter", "uint GetShadowMask() const", asMETHODPR(ParticleEmitter, GetShadowMask, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter", "uint get_shadowMask() const", asMETHODPR(ParticleEmitter, GetShadowMask, () const, unsigned), asCALL_THISCALL);
    // float Drawable::GetSortValue() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("ParticleEmitter", "float GetSortValue() const", asMETHODPR(ParticleEmitter, GetSortValue, () const, float), asCALL_THISCALL);
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ParticleEmitter", "Object@+ GetSubsystem(StringHash) const", asMETHODPR(ParticleEmitter, GetSubsystem, (StringHash) const, Object*), asCALL_THISCALL);
    // template<class T> T*  Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("ParticleEmitter", "StringHash GetType() const", asMETHODPR(ParticleEmitter, GetType, () const, StringHash), asCALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter", "StringHash get_type() const", asMETHODPR(ParticleEmitter, GetType, () const, StringHash), asCALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("ParticleEmitter", "const String& GetTypeName() const", asMETHODPR(ParticleEmitter, GetTypeName, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter", "const String& get_typeName() const", asMETHODPR(ParticleEmitter, GetTypeName, () const, const String&), asCALL_THISCALL);
    // UpdateGeometryType BillboardSet::GetUpdateGeometryType() override | File: ../Graphics/BillboardSet.h
    engine->RegisterObjectMethod("ParticleEmitter", "UpdateGeometryType GetUpdateGeometryType()", asMETHODPR(ParticleEmitter, GetUpdateGeometryType, (), UpdateGeometryType), asCALL_THISCALL);
    // const PODVector<Light*>& Drawable::GetVertexLights() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("ParticleEmitter", "Array<Light@>@ GetVertexLights() const", asFUNCTION(ParticleEmitter_GetVertexLights_void), asCALL_CDECL_OBJFIRST);
    // unsigned Drawable::GetViewMask() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("ParticleEmitter", "uint GetViewMask() const", asMETHODPR(ParticleEmitter, GetViewMask, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter", "uint get_viewMask() const", asMETHODPR(ParticleEmitter, GetViewMask, () const, unsigned), asCALL_THISCALL);
    // const BoundingBox& Drawable::GetWorldBoundingBox() | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("ParticleEmitter", "const BoundingBox& GetWorldBoundingBox()", asMETHODPR(ParticleEmitter, GetWorldBoundingBox, (), const BoundingBox&), asCALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter", "const BoundingBox& get_worldBoundingBox()", asMETHODPR(ParticleEmitter, GetWorldBoundingBox, (), const BoundingBox&), asCALL_THISCALL);
    // Zone* Drawable::GetZone() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("ParticleEmitter", "Zone@+ GetZone() const", asMETHODPR(ParticleEmitter, GetZone, () const, Zone*), asCALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter", "Zone@+ get_zone() const", asMETHODPR(ParticleEmitter, GetZone, () const, Zone*), asCALL_THISCALL);
    // unsigned Drawable::GetZoneMask() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("ParticleEmitter", "uint GetZoneMask() const", asMETHODPR(ParticleEmitter, GetZoneMask, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter", "uint get_zoneMask() const", asMETHODPR(ParticleEmitter, GetZoneMask, () const, unsigned), asCALL_THISCALL);
    // bool Drawable::HasBasePass(unsigned batchIndex) const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("ParticleEmitter", "bool HasBasePass(uint) const", asMETHODPR(ParticleEmitter, HasBasePass, (unsigned) const, bool), asCALL_THISCALL);
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ParticleEmitter", "bool HasEventHandlers() const", asMETHODPR(ParticleEmitter, HasEventHandlers, () const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ParticleEmitter", "bool HasSubscribedToEvent(StringHash) const", asMETHODPR(ParticleEmitter, HasSubscribedToEvent, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ParticleEmitter", "bool HasSubscribedToEvent(Object@+, StringHash) const", asMETHODPR(ParticleEmitter, HasSubscribedToEvent, (Object*, StringHash) const, bool), asCALL_THISCALL);
    // bool ParticleEmitter::IsEmitting() const | File: ../Graphics/ParticleEmitter.h
    engine->RegisterObjectMethod("ParticleEmitter", "bool IsEmitting() const", asMETHODPR(ParticleEmitter, IsEmitting, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter", "bool get_emitting() const", asMETHODPR(ParticleEmitter, IsEmitting, () const, bool), asCALL_THISCALL);
    // bool Component::IsEnabled() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ParticleEmitter", "bool IsEnabled() const", asMETHODPR(ParticleEmitter, IsEnabled, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter", "bool get_enabled() const", asMETHODPR(ParticleEmitter, IsEnabled, () const, bool), asCALL_THISCALL);
    // bool Component::IsEnabledEffective() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ParticleEmitter", "bool IsEnabledEffective() const", asMETHODPR(ParticleEmitter, IsEnabledEffective, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter", "bool get_enabledEffective() const", asMETHODPR(ParticleEmitter, IsEnabledEffective, () const, bool), asCALL_THISCALL);
    // bool BillboardSet::IsFixedScreenSize() const | File: ../Graphics/BillboardSet.h
    engine->RegisterObjectMethod("ParticleEmitter", "bool IsFixedScreenSize() const", asMETHODPR(ParticleEmitter, IsFixedScreenSize, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter", "bool get_fixedScreenSize() const", asMETHODPR(ParticleEmitter, IsFixedScreenSize, () const, bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ParticleEmitter", "bool IsInstanceOf(StringHash) const", asMETHODPR(ParticleEmitter, IsInstanceOf, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // bool Drawable::IsInView() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("ParticleEmitter", "bool IsInView() const", asMETHODPR(ParticleEmitter, IsInView, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter", "bool get_inView() const", asMETHODPR(ParticleEmitter, IsInView, () const, bool), asCALL_THISCALL);
    // bool Drawable::IsInView(Camera* camera) const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("ParticleEmitter", "bool IsInView(Camera@+) const", asMETHODPR(ParticleEmitter, IsInView, (Camera*) const, bool), asCALL_THISCALL);
    // bool Drawable::IsInView(const FrameInfo& frame, bool anyCamera=false) const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("ParticleEmitter", "bool IsInView(const FrameInfo&in, bool = false) const", asMETHODPR(ParticleEmitter, IsInView, (const FrameInfo&, bool) const, bool), asCALL_THISCALL);
    // bool Drawable::IsOccludee() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("ParticleEmitter", "bool IsOccludee() const", asMETHODPR(ParticleEmitter, IsOccludee, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter", "bool get_occludee() const", asMETHODPR(ParticleEmitter, IsOccludee, () const, bool), asCALL_THISCALL);
    // bool Drawable::IsOccluder() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("ParticleEmitter", "bool IsOccluder() const", asMETHODPR(ParticleEmitter, IsOccluder, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter", "bool get_occluder() const", asMETHODPR(ParticleEmitter, IsOccluder, () const, bool), asCALL_THISCALL);
    // bool BillboardSet::IsRelative() const | File: ../Graphics/BillboardSet.h
    engine->RegisterObjectMethod("ParticleEmitter", "bool IsRelative() const", asMETHODPR(ParticleEmitter, IsRelative, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter", "bool get_relative() const", asMETHODPR(ParticleEmitter, IsRelative, () const, bool), asCALL_THISCALL);
    // bool Component::IsReplicated() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ParticleEmitter", "bool IsReplicated() const", asMETHODPR(ParticleEmitter, IsReplicated, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter", "bool get_replicated() const", asMETHODPR(ParticleEmitter, IsReplicated, () const, bool), asCALL_THISCALL);
    // bool BillboardSet::IsScaled() const | File: ../Graphics/BillboardSet.h
    engine->RegisterObjectMethod("ParticleEmitter", "bool IsScaled() const", asMETHODPR(ParticleEmitter, IsScaled, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter", "bool get_scaled() const", asMETHODPR(ParticleEmitter, IsScaled, () const, bool), asCALL_THISCALL);
    // bool BillboardSet::IsSorted() const | File: ../Graphics/BillboardSet.h
    engine->RegisterObjectMethod("ParticleEmitter", "bool IsSorted() const", asMETHODPR(ParticleEmitter, IsSorted, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter", "bool get_sorted() const", asMETHODPR(ParticleEmitter, IsSorted, () const, bool), asCALL_THISCALL);
    // bool Serializable::IsTemporary() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ParticleEmitter", "bool IsTemporary() const", asMETHODPR(ParticleEmitter, IsTemporary, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter", "bool get_temporary() const", asMETHODPR(ParticleEmitter, IsTemporary, () const, bool), asCALL_THISCALL);
    // bool Drawable::IsZoneDirty() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("ParticleEmitter", "bool IsZoneDirty() const", asMETHODPR(ParticleEmitter, IsZoneDirty, () const, bool), asCALL_THISCALL);
    // void Drawable::LimitLights() | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("ParticleEmitter", "void LimitLights()", asMETHODPR(ParticleEmitter, LimitLights, (), void), asCALL_THISCALL);
    // void Drawable::LimitVertexLights(bool removeConvertedLights) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("ParticleEmitter", "void LimitVertexLights(bool)", asMETHODPR(ParticleEmitter, LimitVertexLights, (bool), void), asCALL_THISCALL);
    // virtual bool Serializable::Load(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ParticleEmitter", "bool Load(Deserializer&)", asMETHODPR(ParticleEmitter, Load, (Deserializer&), bool), asCALL_THISCALL);
    // bool Animatable::LoadJSON(const JSONValue& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ParticleEmitter", "bool LoadJSON(const JSONValue&in)", asMETHODPR(ParticleEmitter, LoadJSON, (const JSONValue&), bool), asCALL_THISCALL);
    // bool Animatable::LoadXML(const XMLElement& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ParticleEmitter", "bool LoadXML(const XMLElement&in)", asMETHODPR(ParticleEmitter, LoadXML, (const XMLElement&), bool), asCALL_THISCALL);
    // void Drawable::MarkForUpdate() | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("ParticleEmitter", "void MarkForUpdate()", asMETHODPR(ParticleEmitter, MarkForUpdate, (), void), asCALL_THISCALL);
    // void Drawable::MarkInView(const FrameInfo& frame) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("ParticleEmitter", "void MarkInView(const FrameInfo&in)", asMETHODPR(ParticleEmitter, MarkInView, (const FrameInfo&), void), asCALL_THISCALL);
    // void Drawable::MarkInView(unsigned frameNumber) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("ParticleEmitter", "void MarkInView(uint)", asMETHODPR(ParticleEmitter, MarkInView, (unsigned), void), asCALL_THISCALL);
    // void Component::MarkNetworkUpdate() override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ParticleEmitter", "void MarkNetworkUpdate()", asMETHODPR(ParticleEmitter, MarkNetworkUpdate, (), void), asCALL_THISCALL);
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ParticleEmitter", "void OnEvent(Object@+, StringHash, VariantMap&)", asMETHODPR(ParticleEmitter, OnEvent, (Object*, StringHash, VariantMap&), void), asCALL_THISCALL);
    // virtual void Serializable::OnGetAttribute(const AttributeInfo& attr, Variant& dest) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ParticleEmitter", "void OnGetAttribute(const AttributeInfo&in, Variant&) const", asMETHODPR(ParticleEmitter, OnGetAttribute, (const AttributeInfo&, Variant&) const, void), asCALL_THISCALL);
    // virtual void Serializable::OnSetAttribute(const AttributeInfo& attr, const Variant& src) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ParticleEmitter", "void OnSetAttribute(const AttributeInfo&in, const Variant&in)", asMETHODPR(ParticleEmitter, OnSetAttribute, (const AttributeInfo&, const Variant&), void), asCALL_THISCALL);
    // void ParticleEmitter::OnSetEnabled() override | File: ../Graphics/ParticleEmitter.h
    engine->RegisterObjectMethod("ParticleEmitter", "void OnSetEnabled()", asMETHODPR(ParticleEmitter, OnSetEnabled, (), void), asCALL_THISCALL);
    // explicit ParticleEmitter::ParticleEmitter(Context* context) | File: ../Graphics/ParticleEmitter.h
    engine->RegisterObjectBehaviour("ParticleEmitter", asBEHAVE_FACTORY, "ParticleEmitter@+ f()", asFUNCTION(ParticleEmitter_ParticleEmitter_Context), asCALL_CDECL);
    // void Component::PrepareNetworkUpdate() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ParticleEmitter", "void PrepareNetworkUpdate()", asMETHODPR(ParticleEmitter, PrepareNetworkUpdate, (), void), asCALL_THISCALL);
    // void BillboardSet::ProcessRayQuery(const RayOctreeQuery& query, PODVector<RayQueryResult>& results) override | File: ../Graphics/BillboardSet.h
    // Error: type "RayOctreeQuery" can not automatically bind bacause have @nobind mark
    // bool Serializable::ReadDeltaUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ParticleEmitter", "bool ReadDeltaUpdate(Deserializer&)", asMETHODPR(ParticleEmitter, ReadDeltaUpdate, (Deserializer&), bool), asCALL_THISCALL);
    // bool Serializable::ReadLatestDataUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ParticleEmitter", "bool ReadLatestDataUpdate(Deserializer&)", asMETHODPR(ParticleEmitter, ReadLatestDataUpdate, (Deserializer&), bool), asCALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("ParticleEmitter", "int Refs() const", asMETHODPR(ParticleEmitter, Refs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter", "int get_refs() const", asMETHODPR(ParticleEmitter, Refs, () const, int), asCALL_THISCALL);
    // static void ParticleEmitter::RegisterObject(Context* context) | File: ../Graphics/ParticleEmitter.h
    // Not registered because have @nobind mark
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("ParticleEmitter", asBEHAVE_RELEASE, "void f()", asMETHODPR(ParticleEmitter, ReleaseRef, (), void), asCALL_THISCALL);
    // void Component::Remove() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ParticleEmitter", "void Remove()", asMETHODPR(ParticleEmitter, Remove, (), void), asCALL_THISCALL);
    // void ParticleEmitter::RemoveAllParticles() | File: ../Graphics/ParticleEmitter.h
    engine->RegisterObjectMethod("ParticleEmitter", "void RemoveAllParticles()", asMETHODPR(ParticleEmitter, RemoveAllParticles, (), void), asCALL_THISCALL);
    // void Animatable::RemoveAttributeAnimation(const String& name) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ParticleEmitter", "void RemoveAttributeAnimation(const String&in)", asMETHODPR(ParticleEmitter, RemoveAttributeAnimation, (const String&), void), asCALL_THISCALL);
    // void Serializable::RemoveInstanceDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ParticleEmitter", "void RemoveInstanceDefault()", asMETHODPR(ParticleEmitter, RemoveInstanceDefault, (), void), asCALL_THISCALL);
    // void Animatable::RemoveObjectAnimation() | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ParticleEmitter", "void RemoveObjectAnimation()", asMETHODPR(ParticleEmitter, RemoveObjectAnimation, (), void), asCALL_THISCALL);
    // void ParticleEmitter::Reset() | File: ../Graphics/ParticleEmitter.h
    engine->RegisterObjectMethod("ParticleEmitter", "void Reset()", asMETHODPR(ParticleEmitter, Reset, (), void), asCALL_THISCALL);
    // void ParticleEmitter::ResetEmissionTimer() | File: ../Graphics/ParticleEmitter.h
    engine->RegisterObjectMethod("ParticleEmitter", "void ResetEmissionTimer()", asMETHODPR(ParticleEmitter, ResetEmissionTimer, (), void), asCALL_THISCALL);
    // void Serializable::ResetToDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ParticleEmitter", "void ResetToDefault()", asMETHODPR(ParticleEmitter, ResetToDefault, (), void), asCALL_THISCALL);
    // bool Component::Save(Serializer& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ParticleEmitter", "bool Save(Serializer&) const", asMETHODPR(ParticleEmitter, Save, (Serializer&) const, bool), asCALL_THISCALL);
    // virtual bool Serializable::SaveDefaultAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ParticleEmitter", "bool SaveDefaultAttributes() const", asMETHODPR(ParticleEmitter, SaveDefaultAttributes, () const, bool), asCALL_THISCALL);
    // bool Component::SaveJSON(JSONValue& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ParticleEmitter", "bool SaveJSON(JSONValue&) const", asMETHODPR(ParticleEmitter, SaveJSON, (JSONValue&) const, bool), asCALL_THISCALL);
    // bool Component::SaveXML(XMLElement& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ParticleEmitter", "bool SaveXML(XMLElement&) const", asMETHODPR(ParticleEmitter, SaveXML, (XMLElement&) const, bool), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ParticleEmitter", "void SendEvent(StringHash)", asMETHODPR(ParticleEmitter, SendEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ParticleEmitter", "void SendEvent(StringHash, VariantMap&)", asMETHODPR(ParticleEmitter, SendEvent, (StringHash, VariantMap&), void), asCALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void Animatable::SetAnimationEnabled(bool enable) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ParticleEmitter", "void SetAnimationEnabled(bool)", asMETHODPR(ParticleEmitter, SetAnimationEnabled, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter", "void set_animationEnabled(bool)", asMETHODPR(ParticleEmitter, SetAnimationEnabled, (bool), void), asCALL_THISCALL);
    // void BillboardSet::SetAnimationLodBias(float bias) | File: ../Graphics/BillboardSet.h
    engine->RegisterObjectMethod("ParticleEmitter", "void SetAnimationLodBias(float)", asMETHODPR(ParticleEmitter, SetAnimationLodBias, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter", "void set_animationLodBias(float)", asMETHODPR(ParticleEmitter, SetAnimationLodBias, (float), void), asCALL_THISCALL);
    // void Animatable::SetAnimationTime(float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ParticleEmitter", "void SetAnimationTime(float)", asMETHODPR(ParticleEmitter, SetAnimationTime, (float), void), asCALL_THISCALL);
    // bool Serializable::SetAttribute(unsigned index, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ParticleEmitter", "bool SetAttribute(uint, const Variant&in)", asMETHODPR(ParticleEmitter, SetAttribute, (unsigned, const Variant&), bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter", "bool set_attributes(uint, const Variant&in)", asMETHODPR(ParticleEmitter, SetAttribute, (unsigned, const Variant&), bool), asCALL_THISCALL);
    // bool Serializable::SetAttribute(const String& name, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ParticleEmitter", "bool SetAttribute(const String&in, const Variant&in)", asMETHODPR(ParticleEmitter, SetAttribute, (const String&, const Variant&), bool), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimation(const String& name, ValueAnimation* attributeAnimation, WrapMode wrapMode=WM_LOOP, float speed=1.0f) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ParticleEmitter", "void SetAttributeAnimation(const String&in, ValueAnimation@+, WrapMode = WM_LOOP, float = 1.0f)", asMETHODPR(ParticleEmitter, SetAttributeAnimation, (const String&, ValueAnimation*, WrapMode, float), void), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimationSpeed(const String& name, float speed) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ParticleEmitter", "void SetAttributeAnimationSpeed(const String&in, float)", asMETHODPR(ParticleEmitter, SetAttributeAnimationSpeed, (const String&, float), void), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimationTime(const String& name, float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ParticleEmitter", "void SetAttributeAnimationTime(const String&in, float)", asMETHODPR(ParticleEmitter, SetAttributeAnimationTime, (const String&, float), void), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimationWrapMode(const String& name, WrapMode wrapMode) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ParticleEmitter", "void SetAttributeAnimationWrapMode(const String&in, WrapMode)", asMETHODPR(ParticleEmitter, SetAttributeAnimationWrapMode, (const String&, WrapMode), void), asCALL_THISCALL);
    // void ParticleEmitter::SetAutoRemoveMode(AutoRemoveMode mode) | File: ../Graphics/ParticleEmitter.h
    engine->RegisterObjectMethod("ParticleEmitter", "void SetAutoRemoveMode(AutoRemoveMode)", asMETHODPR(ParticleEmitter, SetAutoRemoveMode, (AutoRemoveMode), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter", "void set_autoRemoveMode(AutoRemoveMode)", asMETHODPR(ParticleEmitter, SetAutoRemoveMode, (AutoRemoveMode), void), asCALL_THISCALL);
    // void Drawable::SetBasePass(unsigned batchIndex) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("ParticleEmitter", "void SetBasePass(uint)", asMETHODPR(ParticleEmitter, SetBasePass, (unsigned), void), asCALL_THISCALL);
    // void BillboardSet::SetBillboardsAttr(const VariantVector& value) | File: ../Graphics/BillboardSet.h
    // Error: type "const VariantVector&" can not automatically bind
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ParticleEmitter", "void SetBlockEvents(bool)", asMETHODPR(ParticleEmitter, SetBlockEvents, (bool), void), asCALL_THISCALL);
    // void Drawable::SetCastShadows(bool enable) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("ParticleEmitter", "void SetCastShadows(bool)", asMETHODPR(ParticleEmitter, SetCastShadows, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter", "void set_castShadows(bool)", asMETHODPR(ParticleEmitter, SetCastShadows, (bool), void), asCALL_THISCALL);
    // void Drawable::SetDrawDistance(float distance) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("ParticleEmitter", "void SetDrawDistance(float)", asMETHODPR(ParticleEmitter, SetDrawDistance, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter", "void set_drawDistance(float)", asMETHODPR(ParticleEmitter, SetDrawDistance, (float), void), asCALL_THISCALL);
    // void ParticleEmitter::SetEffect(ParticleEffect* effect) | File: ../Graphics/ParticleEmitter.h
    engine->RegisterObjectMethod("ParticleEmitter", "void SetEffect(ParticleEffect@+)", asMETHODPR(ParticleEmitter, SetEffect, (ParticleEffect*), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter", "void set_effect(ParticleEffect@+)", asMETHODPR(ParticleEmitter, SetEffect, (ParticleEffect*), void), asCALL_THISCALL);
    // void ParticleEmitter::SetEffectAttr(const ResourceRef& value) | File: ../Graphics/ParticleEmitter.h
    engine->RegisterObjectMethod("ParticleEmitter", "void SetEffectAttr(const ResourceRef&in)", asMETHODPR(ParticleEmitter, SetEffectAttr, (const ResourceRef&), void), asCALL_THISCALL);
    // void ParticleEmitter::SetEmitting(bool enable) | File: ../Graphics/ParticleEmitter.h
    engine->RegisterObjectMethod("ParticleEmitter", "void SetEmitting(bool)", asMETHODPR(ParticleEmitter, SetEmitting, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter", "void set_emitting(bool)", asMETHODPR(ParticleEmitter, SetEmitting, (bool), void), asCALL_THISCALL);
    // void Component::SetEnabled(bool enable) | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ParticleEmitter", "void SetEnabled(bool)", asMETHODPR(ParticleEmitter, SetEnabled, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter", "void set_enabled(bool)", asMETHODPR(ParticleEmitter, SetEnabled, (bool), void), asCALL_THISCALL);
    // void BillboardSet::SetFaceCameraMode(FaceCameraMode mode) | File: ../Graphics/BillboardSet.h
    engine->RegisterObjectMethod("ParticleEmitter", "void SetFaceCameraMode(FaceCameraMode)", asMETHODPR(ParticleEmitter, SetFaceCameraMode, (FaceCameraMode), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter", "void set_faceCameraMode(FaceCameraMode)", asMETHODPR(ParticleEmitter, SetFaceCameraMode, (FaceCameraMode), void), asCALL_THISCALL);
    // void BillboardSet::SetFixedScreenSize(bool enable) | File: ../Graphics/BillboardSet.h
    engine->RegisterObjectMethod("ParticleEmitter", "void SetFixedScreenSize(bool)", asMETHODPR(ParticleEmitter, SetFixedScreenSize, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter", "void set_fixedScreenSize(bool)", asMETHODPR(ParticleEmitter, SetFixedScreenSize, (bool), void), asCALL_THISCALL);
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ParticleEmitter", "void SetGlobalVar(StringHash, const Variant&in)", asMETHODPR(ParticleEmitter, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter", "void set_globalVar(StringHash, const Variant&in)", asMETHODPR(ParticleEmitter, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    // void Serializable::SetInstanceDefault(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ParticleEmitter", "void SetInstanceDefault(bool)", asMETHODPR(ParticleEmitter, SetInstanceDefault, (bool), void), asCALL_THISCALL);
    // void Serializable::SetInterceptNetworkUpdate(const String& attributeName, bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ParticleEmitter", "void SetInterceptNetworkUpdate(const String&in, bool)", asMETHODPR(ParticleEmitter, SetInterceptNetworkUpdate, (const String&, bool), void), asCALL_THISCALL);
    // void Drawable::SetLightMask(unsigned mask) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("ParticleEmitter", "void SetLightMask(uint)", asMETHODPR(ParticleEmitter, SetLightMask, (unsigned), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter", "void set_lightMask(uint)", asMETHODPR(ParticleEmitter, SetLightMask, (unsigned), void), asCALL_THISCALL);
    // void Drawable::SetLodBias(float bias) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("ParticleEmitter", "void SetLodBias(float)", asMETHODPR(ParticleEmitter, SetLodBias, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter", "void set_lodBias(float)", asMETHODPR(ParticleEmitter, SetLodBias, (float), void), asCALL_THISCALL);
    // void BillboardSet::SetMaterial(Material* material) | File: ../Graphics/BillboardSet.h
    engine->RegisterObjectMethod("ParticleEmitter", "void SetMaterial(Material@+)", asMETHODPR(ParticleEmitter, SetMaterial, (Material*), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter", "void set_material(Material@+)", asMETHODPR(ParticleEmitter, SetMaterial, (Material*), void), asCALL_THISCALL);
    // void BillboardSet::SetMaterialAttr(const ResourceRef& value) | File: ../Graphics/BillboardSet.h
    engine->RegisterObjectMethod("ParticleEmitter", "void SetMaterialAttr(const ResourceRef&in)", asMETHODPR(ParticleEmitter, SetMaterialAttr, (const ResourceRef&), void), asCALL_THISCALL);
    // void Drawable::SetMaxLights(unsigned num) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("ParticleEmitter", "void SetMaxLights(uint)", asMETHODPR(ParticleEmitter, SetMaxLights, (unsigned), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter", "void set_maxLights(uint)", asMETHODPR(ParticleEmitter, SetMaxLights, (unsigned), void), asCALL_THISCALL);
    // void BillboardSet::SetMinAngle(float angle) | File: ../Graphics/BillboardSet.h
    engine->RegisterObjectMethod("ParticleEmitter", "void SetMinAngle(float)", asMETHODPR(ParticleEmitter, SetMinAngle, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter", "void set_minAngle(float)", asMETHODPR(ParticleEmitter, SetMinAngle, (float), void), asCALL_THISCALL);
    // void Drawable::SetMinMaxZ(float minZ, float maxZ) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("ParticleEmitter", "void SetMinMaxZ(float, float)", asMETHODPR(ParticleEmitter, SetMinMaxZ, (float, float), void), asCALL_THISCALL);
    // void BillboardSet::SetNetBillboardsAttr(const PODVector<unsigned char>& value) | File: ../Graphics/BillboardSet.h
    // Error: type "const PODVector<unsigned char>&" can not automatically bind
    // void BillboardSet::SetNumBillboards(unsigned num) | File: ../Graphics/BillboardSet.h
    engine->RegisterObjectMethod("ParticleEmitter", "void SetNumBillboards(uint)", asMETHODPR(ParticleEmitter, SetNumBillboards, (unsigned), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter", "void set_numBillboards(uint)", asMETHODPR(ParticleEmitter, SetNumBillboards, (unsigned), void), asCALL_THISCALL);
    // void ParticleEmitter::SetNumParticles(unsigned num) | File: ../Graphics/ParticleEmitter.h
    engine->RegisterObjectMethod("ParticleEmitter", "void SetNumParticles(uint)", asMETHODPR(ParticleEmitter, SetNumParticles, (unsigned), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter", "void set_numParticles(uint)", asMETHODPR(ParticleEmitter, SetNumParticles, (unsigned), void), asCALL_THISCALL);
    // void Animatable::SetObjectAnimation(ObjectAnimation* objectAnimation) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ParticleEmitter", "void SetObjectAnimation(ObjectAnimation@+)", asMETHODPR(ParticleEmitter, SetObjectAnimation, (ObjectAnimation*), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter", "void set_objectAnimation(ObjectAnimation@+)", asMETHODPR(ParticleEmitter, SetObjectAnimation, (ObjectAnimation*), void), asCALL_THISCALL);
    // void Animatable::SetObjectAnimationAttr(const ResourceRef& value) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ParticleEmitter", "void SetObjectAnimationAttr(const ResourceRef&in)", asMETHODPR(ParticleEmitter, SetObjectAnimationAttr, (const ResourceRef&), void), asCALL_THISCALL);
    // void Drawable::SetOccludee(bool enable) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("ParticleEmitter", "void SetOccludee(bool)", asMETHODPR(ParticleEmitter, SetOccludee, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter", "void set_occludee(bool)", asMETHODPR(ParticleEmitter, SetOccludee, (bool), void), asCALL_THISCALL);
    // void Drawable::SetOccluder(bool enable) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("ParticleEmitter", "void SetOccluder(bool)", asMETHODPR(ParticleEmitter, SetOccluder, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter", "void set_occluder(bool)", asMETHODPR(ParticleEmitter, SetOccluder, (bool), void), asCALL_THISCALL);
    // void ParticleEmitter::SetParticlesAttr(const VariantVector& value) | File: ../Graphics/ParticleEmitter.h
    // Error: type "const VariantVector&" can not automatically bind
    // void BillboardSet::SetRelative(bool enable) | File: ../Graphics/BillboardSet.h
    engine->RegisterObjectMethod("ParticleEmitter", "void SetRelative(bool)", asMETHODPR(ParticleEmitter, SetRelative, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter", "void set_relative(bool)", asMETHODPR(ParticleEmitter, SetRelative, (bool), void), asCALL_THISCALL);
    // void BillboardSet::SetScaled(bool enable) | File: ../Graphics/BillboardSet.h
    engine->RegisterObjectMethod("ParticleEmitter", "void SetScaled(bool)", asMETHODPR(ParticleEmitter, SetScaled, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter", "void set_scaled(bool)", asMETHODPR(ParticleEmitter, SetScaled, (bool), void), asCALL_THISCALL);
    // void ParticleEmitter::SetSerializeParticles(bool enable) | File: ../Graphics/ParticleEmitter.h
    engine->RegisterObjectMethod("ParticleEmitter", "void SetSerializeParticles(bool)", asMETHODPR(ParticleEmitter, SetSerializeParticles, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter", "void set_serializeParticles(bool)", asMETHODPR(ParticleEmitter, SetSerializeParticles, (bool), void), asCALL_THISCALL);
    // void Drawable::SetShadowDistance(float distance) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("ParticleEmitter", "void SetShadowDistance(float)", asMETHODPR(ParticleEmitter, SetShadowDistance, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter", "void set_shadowDistance(float)", asMETHODPR(ParticleEmitter, SetShadowDistance, (float), void), asCALL_THISCALL);
    // void Drawable::SetShadowMask(unsigned mask) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("ParticleEmitter", "void SetShadowMask(uint)", asMETHODPR(ParticleEmitter, SetShadowMask, (unsigned), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter", "void set_shadowMask(uint)", asMETHODPR(ParticleEmitter, SetShadowMask, (unsigned), void), asCALL_THISCALL);
    // void BillboardSet::SetSorted(bool enable) | File: ../Graphics/BillboardSet.h
    engine->RegisterObjectMethod("ParticleEmitter", "void SetSorted(bool)", asMETHODPR(ParticleEmitter, SetSorted, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter", "void set_sorted(bool)", asMETHODPR(ParticleEmitter, SetSorted, (bool), void), asCALL_THISCALL);
    // void Drawable::SetSortValue(float value) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("ParticleEmitter", "void SetSortValue(float)", asMETHODPR(ParticleEmitter, SetSortValue, (float), void), asCALL_THISCALL);
    // void Serializable::SetTemporary(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ParticleEmitter", "void SetTemporary(bool)", asMETHODPR(ParticleEmitter, SetTemporary, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter", "void set_temporary(bool)", asMETHODPR(ParticleEmitter, SetTemporary, (bool), void), asCALL_THISCALL);
    // void Drawable::SetViewMask(unsigned mask) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("ParticleEmitter", "void SetViewMask(uint)", asMETHODPR(ParticleEmitter, SetViewMask, (unsigned), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter", "void set_viewMask(uint)", asMETHODPR(ParticleEmitter, SetViewMask, (unsigned), void), asCALL_THISCALL);
    // void Drawable::SetZone(Zone* zone, bool temporary=false) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("ParticleEmitter", "void SetZone(Zone@+, bool = false)", asMETHODPR(ParticleEmitter, SetZone, (Zone*, bool), void), asCALL_THISCALL);
    // void Drawable::SetZoneMask(unsigned mask) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("ParticleEmitter", "void SetZoneMask(uint)", asMETHODPR(ParticleEmitter, SetZoneMask, (unsigned), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter", "void set_zoneMask(uint)", asMETHODPR(ParticleEmitter, SetZoneMask, (unsigned), void), asCALL_THISCALL);
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod("ParticleEmitter", "void UnsubscribeFromAllEvents()", asMETHODPR(ParticleEmitter, UnsubscribeFromAllEvents, (), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ParticleEmitter", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", asFUNCTION(ParticleEmitter_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), asCALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ParticleEmitter", "void UnsubscribeFromEvent(StringHash)", asMETHODPR(ParticleEmitter, UnsubscribeFromEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ParticleEmitter", "void UnsubscribeFromEvent(Object@+, StringHash)", asMETHODPR(ParticleEmitter, UnsubscribeFromEvent, (Object*, StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ParticleEmitter", "void UnsubscribeFromEvents(Object@+)", asMETHODPR(ParticleEmitter, UnsubscribeFromEvents, (Object*), void), asCALL_THISCALL);
    // void ParticleEmitter::Update(const FrameInfo& frame) override | File: ../Graphics/ParticleEmitter.h
    engine->RegisterObjectMethod("ParticleEmitter", "void Update(const FrameInfo&in)", asMETHODPR(ParticleEmitter, Update, (const FrameInfo&), void), asCALL_THISCALL);
    // void BillboardSet::UpdateBatches(const FrameInfo& frame) override | File: ../Graphics/BillboardSet.h
    engine->RegisterObjectMethod("ParticleEmitter", "void UpdateBatches(const FrameInfo&in)", asMETHODPR(ParticleEmitter, UpdateBatches, (const FrameInfo&), void), asCALL_THISCALL);
    // void BillboardSet::UpdateGeometry(const FrameInfo& frame) override | File: ../Graphics/BillboardSet.h
    engine->RegisterObjectMethod("ParticleEmitter", "void UpdateGeometry(const FrameInfo&in)", asMETHODPR(ParticleEmitter, UpdateGeometry, (const FrameInfo&), void), asCALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("ParticleEmitter", "int WeakRefs() const", asMETHODPR(ParticleEmitter, WeakRefs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter", "int get_weakRefs() const", asMETHODPR(ParticleEmitter, WeakRefs, () const, int), asCALL_THISCALL);
    // void Serializable::WriteDeltaUpdate(Serializer& dest, const DirtyBits& attributeBits, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ParticleEmitter", "void WriteDeltaUpdate(Serializer&, const DirtyBits&in, uint8)", asMETHODPR(ParticleEmitter, WriteDeltaUpdate, (Serializer&, const DirtyBits&, unsigned char), void), asCALL_THISCALL);
    // void Serializable::WriteInitialDeltaUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ParticleEmitter", "void WriteInitialDeltaUpdate(Serializer&, uint8)", asMETHODPR(ParticleEmitter, WriteInitialDeltaUpdate, (Serializer&, unsigned char), void), asCALL_THISCALL);
    // void Serializable::WriteLatestDataUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ParticleEmitter", "void WriteLatestDataUpdate(Serializer&, uint8)", asMETHODPR(ParticleEmitter, WriteLatestDataUpdate, (Serializer&, unsigned char), void), asCALL_THISCALL);
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
    engine->RegisterObjectMethod("ParticleEmitter2D", "void AddLight(Light@+)", asMETHODPR(ParticleEmitter2D, AddLight, (Light*), void), asCALL_THISCALL);
    // void RefCounted::AddRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("ParticleEmitter2D", asBEHAVE_ADDREF, "void f()", asMETHODPR(ParticleEmitter2D, AddRef, (), void), asCALL_THISCALL);
    // void Component::AddReplicationState(ComponentReplicationState* state) | File: ../Scene/Component.h
    // Error: type "ComponentReplicationState*" can not automatically bind
    // void Drawable::AddVertexLight(Light* light) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "void AddVertexLight(Light@+)", asMETHODPR(ParticleEmitter2D, AddVertexLight, (Light*), void), asCALL_THISCALL);
    // void Serializable::AllocateNetworkState() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "void AllocateNetworkState()", asMETHODPR(ParticleEmitter2D, AllocateNetworkState, (), void), asCALL_THISCALL);
    // virtual void Serializable::ApplyAttributes() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "void ApplyAttributes()", asMETHODPR(ParticleEmitter2D, ApplyAttributes, (), void), asCALL_THISCALL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // void Component::CleanupConnection(Connection* connection) | File: ../Scene/Component.h
    // Not registered because have @manualbind mark
    // void Drawable::DrawDebugGeometry(DebugRenderer* debug, bool depthTest) override | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "void DrawDebugGeometry(DebugRenderer@+, bool)", asMETHODPR(ParticleEmitter2D, DrawDebugGeometry, (DebugRenderer*, bool), void), asCALL_THISCALL);
    // virtual bool Drawable::DrawOcclusion(OcclusionBuffer* buffer) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "bool DrawOcclusion(OcclusionBuffer@+)", asMETHODPR(ParticleEmitter2D, DrawOcclusion, (OcclusionBuffer*), bool), asCALL_THISCALL);
    // bool Animatable::GetAnimationEnabled() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "bool GetAnimationEnabled() const", asMETHODPR(ParticleEmitter2D, GetAnimationEnabled, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter2D", "bool get_animationEnabled() const", asMETHODPR(ParticleEmitter2D, GetAnimationEnabled, () const, bool), asCALL_THISCALL);
    // Variant Serializable::GetAttribute(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "Variant GetAttribute(uint) const", asMETHODPR(ParticleEmitter2D, GetAttribute, (unsigned) const, Variant), asCALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter2D", "Variant get_attributes(uint) const", asMETHODPR(ParticleEmitter2D, GetAttribute, (unsigned) const, Variant), asCALL_THISCALL);
    // Variant Serializable::GetAttribute(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "Variant GetAttribute(const String&in) const", asMETHODPR(ParticleEmitter2D, GetAttribute, (const String&) const, Variant), asCALL_THISCALL);
    // ValueAnimation* Animatable::GetAttributeAnimation(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "ValueAnimation@+ GetAttributeAnimation(const String&in) const", asMETHODPR(ParticleEmitter2D, GetAttributeAnimation, (const String&) const, ValueAnimation*), asCALL_THISCALL);
    // float Animatable::GetAttributeAnimationSpeed(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "float GetAttributeAnimationSpeed(const String&in) const", asMETHODPR(ParticleEmitter2D, GetAttributeAnimationSpeed, (const String&) const, float), asCALL_THISCALL);
    // float Animatable::GetAttributeAnimationTime(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "float GetAttributeAnimationTime(const String&in) const", asMETHODPR(ParticleEmitter2D, GetAttributeAnimationTime, (const String&) const, float), asCALL_THISCALL);
    // WrapMode Animatable::GetAttributeAnimationWrapMode(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "WrapMode GetAttributeAnimationWrapMode(const String&in) const", asMETHODPR(ParticleEmitter2D, GetAttributeAnimationWrapMode, (const String&) const, WrapMode), asCALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "Variant GetAttributeDefault(uint) const", asMETHODPR(ParticleEmitter2D, GetAttributeDefault, (unsigned) const, Variant), asCALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter2D", "Variant get_attributeDefaults(uint) const", asMETHODPR(ParticleEmitter2D, GetAttributeDefault, (unsigned) const, Variant), asCALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "Variant GetAttributeDefault(const String&in) const", asMETHODPR(ParticleEmitter2D, GetAttributeDefault, (const String&) const, Variant), asCALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // const Vector<SourceBatch>& Drawable::GetBatches() const | File: ../Graphics/Drawable.h
    // Error: type "const Vector<SourceBatch>&" can not automatically bind
    // BlendMode ParticleEmitter2D::GetBlendMode() const | File: ../Urho2D/ParticleEmitter2D.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "BlendMode GetBlendMode() const", asMETHODPR(ParticleEmitter2D, GetBlendMode, () const, BlendMode), asCALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter2D", "BlendMode get_blendMode() const", asMETHODPR(ParticleEmitter2D, GetBlendMode, () const, BlendMode), asCALL_THISCALL);
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "bool GetBlockEvents() const", asMETHODPR(ParticleEmitter2D, GetBlockEvents, () const, bool), asCALL_THISCALL);
    // const BoundingBox& Drawable::GetBoundingBox() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "const BoundingBox& GetBoundingBox() const", asMETHODPR(ParticleEmitter2D, GetBoundingBox, () const, const BoundingBox&), asCALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter2D", "const BoundingBox& get_boundingBox() const", asMETHODPR(ParticleEmitter2D, GetBoundingBox, () const, const BoundingBox&), asCALL_THISCALL);
    // bool Drawable::GetCastShadows() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "bool GetCastShadows() const", asMETHODPR(ParticleEmitter2D, GetCastShadows, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter2D", "bool get_castShadows() const", asMETHODPR(ParticleEmitter2D, GetCastShadows, () const, bool), asCALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "const String& GetCategory() const", asMETHODPR(ParticleEmitter2D, GetCategory, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter2D", "const String& get_category() const", asMETHODPR(ParticleEmitter2D, GetCategory, () const, const String&), asCALL_THISCALL);
    // Component* Component::GetComponent(StringHash type) const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "Component@+ GetComponent(StringHash) const", asMETHODPR(ParticleEmitter2D, GetComponent, (StringHash) const, Component*), asCALL_THISCALL);
    // template<class T> T*  Component::GetComponent() const | File: ../Scene/Component.h
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
    engine->RegisterObjectMethod("ParticleEmitter2D", "float GetDistance() const", asMETHODPR(ParticleEmitter2D, GetDistance, () const, float), asCALL_THISCALL);
    // unsigned char Drawable::GetDrawableFlags() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "uint8 GetDrawableFlags() const", asMETHODPR(ParticleEmitter2D, GetDrawableFlags, () const, unsigned char), asCALL_THISCALL);
    // float Drawable::GetDrawDistance() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "float GetDrawDistance() const", asMETHODPR(ParticleEmitter2D, GetDrawDistance, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter2D", "float get_drawDistance() const", asMETHODPR(ParticleEmitter2D, GetDrawDistance, () const, float), asCALL_THISCALL);
    // ParticleEffect2D* ParticleEmitter2D::GetEffect() const | File: ../Urho2D/ParticleEmitter2D.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "ParticleEffect2D@+ GetEffect() const", asMETHODPR(ParticleEmitter2D, GetEffect, () const, ParticleEffect2D*), asCALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter2D", "ParticleEffect2D@+ get_effect() const", asMETHODPR(ParticleEmitter2D, GetEffect, () const, ParticleEffect2D*), asCALL_THISCALL);
    // VariantMap& Object::GetEventDataMap() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "VariantMap& GetEventDataMap() const", asMETHODPR(ParticleEmitter2D, GetEventDataMap, () const, VariantMap&), asCALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "Object@+ GetEventSender() const", asMETHODPR(ParticleEmitter2D, GetEventSender, () const, Object*), asCALL_THISCALL);
    // Light* Drawable::GetFirstLight() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "Light@+ GetFirstLight() const", asMETHODPR(ParticleEmitter2D, GetFirstLight, () const, Light*), asCALL_THISCALL);
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "const Variant& GetGlobalVar(StringHash) const", asMETHODPR(ParticleEmitter2D, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter2D", "const Variant& get_globalVar(StringHash) const", asMETHODPR(ParticleEmitter2D, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "const VariantMap& GetGlobalVars() const", asMETHODPR(ParticleEmitter2D, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter2D", "const VariantMap& get_globalVars() const", asMETHODPR(ParticleEmitter2D, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    // unsigned Component::GetID() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "uint GetID() const", asMETHODPR(ParticleEmitter2D, GetID, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter2D", "uint get_id() const", asMETHODPR(ParticleEmitter2D, GetID, () const, unsigned), asCALL_THISCALL);
    // bool Serializable::GetInterceptNetworkUpdate(const String& attributeName) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "bool GetInterceptNetworkUpdate(const String&in) const", asMETHODPR(ParticleEmitter2D, GetInterceptNetworkUpdate, (const String&) const, bool), asCALL_THISCALL);
    // int Drawable2D::GetLayer() const | File: ../Urho2D/Drawable2D.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "int GetLayer() const", asMETHODPR(ParticleEmitter2D, GetLayer, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter2D", "int get_layer() const", asMETHODPR(ParticleEmitter2D, GetLayer, () const, int), asCALL_THISCALL);
    // unsigned Drawable::GetLightMask() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "uint GetLightMask() const", asMETHODPR(ParticleEmitter2D, GetLightMask, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter2D", "uint get_lightMask() const", asMETHODPR(ParticleEmitter2D, GetLightMask, () const, unsigned), asCALL_THISCALL);
    // const PODVector<Light*>& Drawable::GetLights() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "Array<Light@>@ GetLights() const", asFUNCTION(ParticleEmitter2D_GetLights_void), asCALL_CDECL_OBJFIRST);
    // float Drawable::GetLodBias() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "float GetLodBias() const", asMETHODPR(ParticleEmitter2D, GetLodBias, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter2D", "float get_lodBias() const", asMETHODPR(ParticleEmitter2D, GetLodBias, () const, float), asCALL_THISCALL);
    // float Drawable::GetLodDistance() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "float GetLodDistance() const", asMETHODPR(ParticleEmitter2D, GetLodDistance, () const, float), asCALL_THISCALL);
    // virtual Geometry* Drawable::GetLodGeometry(unsigned batchIndex, unsigned level) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "Geometry@+ GetLodGeometry(uint, uint)", asMETHODPR(ParticleEmitter2D, GetLodGeometry, (unsigned, unsigned), Geometry*), asCALL_THISCALL);
    // unsigned Drawable::GetMaxLights() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "uint GetMaxLights() const", asMETHODPR(ParticleEmitter2D, GetMaxLights, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter2D", "uint get_maxLights() const", asMETHODPR(ParticleEmitter2D, GetMaxLights, () const, unsigned), asCALL_THISCALL);
    // unsigned ParticleEmitter2D::GetMaxParticles() const | File: ../Urho2D/ParticleEmitter2D.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "uint GetMaxParticles() const", asMETHODPR(ParticleEmitter2D, GetMaxParticles, () const, unsigned), asCALL_THISCALL);
    // float Drawable::GetMaxZ() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "float GetMaxZ() const", asMETHODPR(ParticleEmitter2D, GetMaxZ, () const, float), asCALL_THISCALL);
    // float Drawable::GetMinZ() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "float GetMinZ() const", asMETHODPR(ParticleEmitter2D, GetMinZ, () const, float), asCALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetNetworkAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // NetworkState* Serializable::GetNetworkState() const | File: ../Scene/Serializable.h
    // Error: type "NetworkState*" can not automatically bind
    // Node* Component::GetNode() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "Node@+ GetNode() const", asMETHODPR(ParticleEmitter2D, GetNode, () const, Node*), asCALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter2D", "Node@+ get_node() const", asMETHODPR(ParticleEmitter2D, GetNode, () const, Node*), asCALL_THISCALL);
    // unsigned Serializable::GetNumAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "uint GetNumAttributes() const", asMETHODPR(ParticleEmitter2D, GetNumAttributes, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter2D", "uint get_numAttributes() const", asMETHODPR(ParticleEmitter2D, GetNumAttributes, () const, unsigned), asCALL_THISCALL);
    // unsigned Serializable::GetNumNetworkAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "uint GetNumNetworkAttributes() const", asMETHODPR(ParticleEmitter2D, GetNumNetworkAttributes, () const, unsigned), asCALL_THISCALL);
    // virtual unsigned Drawable::GetNumOccluderTriangles() | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "uint GetNumOccluderTriangles()", asMETHODPR(ParticleEmitter2D, GetNumOccluderTriangles, (), unsigned), asCALL_THISCALL);
    // ObjectAnimation* Animatable::GetObjectAnimation() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "ObjectAnimation@+ GetObjectAnimation() const", asMETHODPR(ParticleEmitter2D, GetObjectAnimation, () const, ObjectAnimation*), asCALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter2D", "ObjectAnimation@+ get_objectAnimation() const", asMETHODPR(ParticleEmitter2D, GetObjectAnimation, () const, ObjectAnimation*), asCALL_THISCALL);
    // ResourceRef Animatable::GetObjectAnimationAttr() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "ResourceRef GetObjectAnimationAttr() const", asMETHODPR(ParticleEmitter2D, GetObjectAnimationAttr, () const, ResourceRef), asCALL_THISCALL);
    // Octant* Drawable::GetOctant() const | File: ../Graphics/Drawable.h
    // Error: type "Octant" can not automatically bind bacause have @nobind mark
    // int Drawable2D::GetOrderInLayer() const | File: ../Urho2D/Drawable2D.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "int GetOrderInLayer() const", asMETHODPR(ParticleEmitter2D, GetOrderInLayer, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter2D", "int get_orderInLayer() const", asMETHODPR(ParticleEmitter2D, GetOrderInLayer, () const, int), asCALL_THISCALL);
    // ResourceRef ParticleEmitter2D::GetParticleEffectAttr() const | File: ../Urho2D/ParticleEmitter2D.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "ResourceRef GetParticleEffectAttr() const", asMETHODPR(ParticleEmitter2D, GetParticleEffectAttr, () const, ResourceRef), asCALL_THISCALL);
    // Scene* Component::GetScene() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "Scene@+ GetScene() const", asMETHODPR(ParticleEmitter2D, GetScene, () const, Scene*), asCALL_THISCALL);
    // float Drawable::GetShadowDistance() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "float GetShadowDistance() const", asMETHODPR(ParticleEmitter2D, GetShadowDistance, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter2D", "float get_shadowDistance() const", asMETHODPR(ParticleEmitter2D, GetShadowDistance, () const, float), asCALL_THISCALL);
    // unsigned Drawable::GetShadowMask() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "uint GetShadowMask() const", asMETHODPR(ParticleEmitter2D, GetShadowMask, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter2D", "uint get_shadowMask() const", asMETHODPR(ParticleEmitter2D, GetShadowMask, () const, unsigned), asCALL_THISCALL);
    // float Drawable::GetSortValue() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "float GetSortValue() const", asMETHODPR(ParticleEmitter2D, GetSortValue, () const, float), asCALL_THISCALL);
    // const Vector<SourceBatch2D>& Drawable2D::GetSourceBatches() | File: ../Urho2D/Drawable2D.h
    // Error: type "const Vector<SourceBatch2D>&" can not automatically bind
    // Sprite2D* ParticleEmitter2D::GetSprite() const | File: ../Urho2D/ParticleEmitter2D.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "Sprite2D@+ GetSprite() const", asMETHODPR(ParticleEmitter2D, GetSprite, () const, Sprite2D*), asCALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter2D", "Sprite2D@+ get_sprite() const", asMETHODPR(ParticleEmitter2D, GetSprite, () const, Sprite2D*), asCALL_THISCALL);
    // ResourceRef ParticleEmitter2D::GetSpriteAttr() const | File: ../Urho2D/ParticleEmitter2D.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "ResourceRef GetSpriteAttr() const", asMETHODPR(ParticleEmitter2D, GetSpriteAttr, () const, ResourceRef), asCALL_THISCALL);
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "Object@+ GetSubsystem(StringHash) const", asMETHODPR(ParticleEmitter2D, GetSubsystem, (StringHash) const, Object*), asCALL_THISCALL);
    // template<class T> T*  Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "StringHash GetType() const", asMETHODPR(ParticleEmitter2D, GetType, () const, StringHash), asCALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter2D", "StringHash get_type() const", asMETHODPR(ParticleEmitter2D, GetType, () const, StringHash), asCALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "const String& GetTypeName() const", asMETHODPR(ParticleEmitter2D, GetTypeName, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter2D", "const String& get_typeName() const", asMETHODPR(ParticleEmitter2D, GetTypeName, () const, const String&), asCALL_THISCALL);
    // virtual UpdateGeometryType Drawable::GetUpdateGeometryType() | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "UpdateGeometryType GetUpdateGeometryType()", asMETHODPR(ParticleEmitter2D, GetUpdateGeometryType, (), UpdateGeometryType), asCALL_THISCALL);
    // const PODVector<Light*>& Drawable::GetVertexLights() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "Array<Light@>@ GetVertexLights() const", asFUNCTION(ParticleEmitter2D_GetVertexLights_void), asCALL_CDECL_OBJFIRST);
    // unsigned Drawable::GetViewMask() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "uint GetViewMask() const", asMETHODPR(ParticleEmitter2D, GetViewMask, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter2D", "uint get_viewMask() const", asMETHODPR(ParticleEmitter2D, GetViewMask, () const, unsigned), asCALL_THISCALL);
    // const BoundingBox& Drawable::GetWorldBoundingBox() | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "const BoundingBox& GetWorldBoundingBox()", asMETHODPR(ParticleEmitter2D, GetWorldBoundingBox, (), const BoundingBox&), asCALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter2D", "const BoundingBox& get_worldBoundingBox()", asMETHODPR(ParticleEmitter2D, GetWorldBoundingBox, (), const BoundingBox&), asCALL_THISCALL);
    // Zone* Drawable::GetZone() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "Zone@+ GetZone() const", asMETHODPR(ParticleEmitter2D, GetZone, () const, Zone*), asCALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter2D", "Zone@+ get_zone() const", asMETHODPR(ParticleEmitter2D, GetZone, () const, Zone*), asCALL_THISCALL);
    // unsigned Drawable::GetZoneMask() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "uint GetZoneMask() const", asMETHODPR(ParticleEmitter2D, GetZoneMask, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter2D", "uint get_zoneMask() const", asMETHODPR(ParticleEmitter2D, GetZoneMask, () const, unsigned), asCALL_THISCALL);
    // bool Drawable::HasBasePass(unsigned batchIndex) const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "bool HasBasePass(uint) const", asMETHODPR(ParticleEmitter2D, HasBasePass, (unsigned) const, bool), asCALL_THISCALL);
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "bool HasEventHandlers() const", asMETHODPR(ParticleEmitter2D, HasEventHandlers, () const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "bool HasSubscribedToEvent(StringHash) const", asMETHODPR(ParticleEmitter2D, HasSubscribedToEvent, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "bool HasSubscribedToEvent(Object@+, StringHash) const", asMETHODPR(ParticleEmitter2D, HasSubscribedToEvent, (Object*, StringHash) const, bool), asCALL_THISCALL);
    // bool ParticleEmitter2D::IsEmitting() const | File: ../Urho2D/ParticleEmitter2D.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "bool IsEmitting() const", asMETHODPR(ParticleEmitter2D, IsEmitting, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter2D", "bool get_emitting() const", asMETHODPR(ParticleEmitter2D, IsEmitting, () const, bool), asCALL_THISCALL);
    // bool Component::IsEnabled() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "bool IsEnabled() const", asMETHODPR(ParticleEmitter2D, IsEnabled, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter2D", "bool get_enabled() const", asMETHODPR(ParticleEmitter2D, IsEnabled, () const, bool), asCALL_THISCALL);
    // bool Component::IsEnabledEffective() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "bool IsEnabledEffective() const", asMETHODPR(ParticleEmitter2D, IsEnabledEffective, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter2D", "bool get_enabledEffective() const", asMETHODPR(ParticleEmitter2D, IsEnabledEffective, () const, bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "bool IsInstanceOf(StringHash) const", asMETHODPR(ParticleEmitter2D, IsInstanceOf, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // bool Drawable::IsInView() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "bool IsInView() const", asMETHODPR(ParticleEmitter2D, IsInView, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter2D", "bool get_inView() const", asMETHODPR(ParticleEmitter2D, IsInView, () const, bool), asCALL_THISCALL);
    // bool Drawable::IsInView(Camera* camera) const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "bool IsInView(Camera@+) const", asMETHODPR(ParticleEmitter2D, IsInView, (Camera*) const, bool), asCALL_THISCALL);
    // bool Drawable::IsInView(const FrameInfo& frame, bool anyCamera=false) const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "bool IsInView(const FrameInfo&in, bool = false) const", asMETHODPR(ParticleEmitter2D, IsInView, (const FrameInfo&, bool) const, bool), asCALL_THISCALL);
    // bool Drawable::IsOccludee() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "bool IsOccludee() const", asMETHODPR(ParticleEmitter2D, IsOccludee, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter2D", "bool get_occludee() const", asMETHODPR(ParticleEmitter2D, IsOccludee, () const, bool), asCALL_THISCALL);
    // bool Drawable::IsOccluder() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "bool IsOccluder() const", asMETHODPR(ParticleEmitter2D, IsOccluder, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter2D", "bool get_occluder() const", asMETHODPR(ParticleEmitter2D, IsOccluder, () const, bool), asCALL_THISCALL);
    // bool Component::IsReplicated() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "bool IsReplicated() const", asMETHODPR(ParticleEmitter2D, IsReplicated, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter2D", "bool get_replicated() const", asMETHODPR(ParticleEmitter2D, IsReplicated, () const, bool), asCALL_THISCALL);
    // bool Serializable::IsTemporary() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "bool IsTemporary() const", asMETHODPR(ParticleEmitter2D, IsTemporary, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter2D", "bool get_temporary() const", asMETHODPR(ParticleEmitter2D, IsTemporary, () const, bool), asCALL_THISCALL);
    // bool Drawable::IsZoneDirty() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "bool IsZoneDirty() const", asMETHODPR(ParticleEmitter2D, IsZoneDirty, () const, bool), asCALL_THISCALL);
    // void Drawable::LimitLights() | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "void LimitLights()", asMETHODPR(ParticleEmitter2D, LimitLights, (), void), asCALL_THISCALL);
    // void Drawable::LimitVertexLights(bool removeConvertedLights) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "void LimitVertexLights(bool)", asMETHODPR(ParticleEmitter2D, LimitVertexLights, (bool), void), asCALL_THISCALL);
    // virtual bool Serializable::Load(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "bool Load(Deserializer&)", asMETHODPR(ParticleEmitter2D, Load, (Deserializer&), bool), asCALL_THISCALL);
    // bool Animatable::LoadJSON(const JSONValue& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "bool LoadJSON(const JSONValue&in)", asMETHODPR(ParticleEmitter2D, LoadJSON, (const JSONValue&), bool), asCALL_THISCALL);
    // bool Animatable::LoadXML(const XMLElement& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "bool LoadXML(const XMLElement&in)", asMETHODPR(ParticleEmitter2D, LoadXML, (const XMLElement&), bool), asCALL_THISCALL);
    // void Drawable::MarkForUpdate() | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "void MarkForUpdate()", asMETHODPR(ParticleEmitter2D, MarkForUpdate, (), void), asCALL_THISCALL);
    // void Drawable::MarkInView(const FrameInfo& frame) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "void MarkInView(const FrameInfo&in)", asMETHODPR(ParticleEmitter2D, MarkInView, (const FrameInfo&), void), asCALL_THISCALL);
    // void Drawable::MarkInView(unsigned frameNumber) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "void MarkInView(uint)", asMETHODPR(ParticleEmitter2D, MarkInView, (unsigned), void), asCALL_THISCALL);
    // void Component::MarkNetworkUpdate() override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "void MarkNetworkUpdate()", asMETHODPR(ParticleEmitter2D, MarkNetworkUpdate, (), void), asCALL_THISCALL);
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "void OnEvent(Object@+, StringHash, VariantMap&)", asMETHODPR(ParticleEmitter2D, OnEvent, (Object*, StringHash, VariantMap&), void), asCALL_THISCALL);
    // virtual void Serializable::OnGetAttribute(const AttributeInfo& attr, Variant& dest) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "void OnGetAttribute(const AttributeInfo&in, Variant&) const", asMETHODPR(ParticleEmitter2D, OnGetAttribute, (const AttributeInfo&, Variant&) const, void), asCALL_THISCALL);
    // virtual void Serializable::OnSetAttribute(const AttributeInfo& attr, const Variant& src) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "void OnSetAttribute(const AttributeInfo&in, const Variant&in)", asMETHODPR(ParticleEmitter2D, OnSetAttribute, (const AttributeInfo&, const Variant&), void), asCALL_THISCALL);
    // void ParticleEmitter2D::OnSetEnabled() override | File: ../Urho2D/ParticleEmitter2D.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "void OnSetEnabled()", asMETHODPR(ParticleEmitter2D, OnSetEnabled, (), void), asCALL_THISCALL);
    // explicit ParticleEmitter2D::ParticleEmitter2D(Context* context) | File: ../Urho2D/ParticleEmitter2D.h
    engine->RegisterObjectBehaviour("ParticleEmitter2D", asBEHAVE_FACTORY, "ParticleEmitter2D@+ f()", asFUNCTION(ParticleEmitter2D_ParticleEmitter2D_Context), asCALL_CDECL);
    // void Component::PrepareNetworkUpdate() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "void PrepareNetworkUpdate()", asMETHODPR(ParticleEmitter2D, PrepareNetworkUpdate, (), void), asCALL_THISCALL);
    // virtual void Drawable::ProcessRayQuery(const RayOctreeQuery& query, PODVector<RayQueryResult>& results) | File: ../Graphics/Drawable.h
    // Error: type "RayOctreeQuery" can not automatically bind bacause have @nobind mark
    // bool Serializable::ReadDeltaUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "bool ReadDeltaUpdate(Deserializer&)", asMETHODPR(ParticleEmitter2D, ReadDeltaUpdate, (Deserializer&), bool), asCALL_THISCALL);
    // bool Serializable::ReadLatestDataUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "bool ReadLatestDataUpdate(Deserializer&)", asMETHODPR(ParticleEmitter2D, ReadLatestDataUpdate, (Deserializer&), bool), asCALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "int Refs() const", asMETHODPR(ParticleEmitter2D, Refs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter2D", "int get_refs() const", asMETHODPR(ParticleEmitter2D, Refs, () const, int), asCALL_THISCALL);
    // static void ParticleEmitter2D::RegisterObject(Context* context) | File: ../Urho2D/ParticleEmitter2D.h
    // Not registered because have @nobind mark
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("ParticleEmitter2D", asBEHAVE_RELEASE, "void f()", asMETHODPR(ParticleEmitter2D, ReleaseRef, (), void), asCALL_THISCALL);
    // void Component::Remove() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "void Remove()", asMETHODPR(ParticleEmitter2D, Remove, (), void), asCALL_THISCALL);
    // void Animatable::RemoveAttributeAnimation(const String& name) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "void RemoveAttributeAnimation(const String&in)", asMETHODPR(ParticleEmitter2D, RemoveAttributeAnimation, (const String&), void), asCALL_THISCALL);
    // void Serializable::RemoveInstanceDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "void RemoveInstanceDefault()", asMETHODPR(ParticleEmitter2D, RemoveInstanceDefault, (), void), asCALL_THISCALL);
    // void Animatable::RemoveObjectAnimation() | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "void RemoveObjectAnimation()", asMETHODPR(ParticleEmitter2D, RemoveObjectAnimation, (), void), asCALL_THISCALL);
    // void Serializable::ResetToDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "void ResetToDefault()", asMETHODPR(ParticleEmitter2D, ResetToDefault, (), void), asCALL_THISCALL);
    // bool Component::Save(Serializer& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "bool Save(Serializer&) const", asMETHODPR(ParticleEmitter2D, Save, (Serializer&) const, bool), asCALL_THISCALL);
    // virtual bool Serializable::SaveDefaultAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "bool SaveDefaultAttributes() const", asMETHODPR(ParticleEmitter2D, SaveDefaultAttributes, () const, bool), asCALL_THISCALL);
    // bool Component::SaveJSON(JSONValue& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "bool SaveJSON(JSONValue&) const", asMETHODPR(ParticleEmitter2D, SaveJSON, (JSONValue&) const, bool), asCALL_THISCALL);
    // bool Component::SaveXML(XMLElement& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "bool SaveXML(XMLElement&) const", asMETHODPR(ParticleEmitter2D, SaveXML, (XMLElement&) const, bool), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "void SendEvent(StringHash)", asMETHODPR(ParticleEmitter2D, SendEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "void SendEvent(StringHash, VariantMap&)", asMETHODPR(ParticleEmitter2D, SendEvent, (StringHash, VariantMap&), void), asCALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void Animatable::SetAnimationEnabled(bool enable) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "void SetAnimationEnabled(bool)", asMETHODPR(ParticleEmitter2D, SetAnimationEnabled, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter2D", "void set_animationEnabled(bool)", asMETHODPR(ParticleEmitter2D, SetAnimationEnabled, (bool), void), asCALL_THISCALL);
    // void Animatable::SetAnimationTime(float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "void SetAnimationTime(float)", asMETHODPR(ParticleEmitter2D, SetAnimationTime, (float), void), asCALL_THISCALL);
    // bool Serializable::SetAttribute(unsigned index, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "bool SetAttribute(uint, const Variant&in)", asMETHODPR(ParticleEmitter2D, SetAttribute, (unsigned, const Variant&), bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter2D", "bool set_attributes(uint, const Variant&in)", asMETHODPR(ParticleEmitter2D, SetAttribute, (unsigned, const Variant&), bool), asCALL_THISCALL);
    // bool Serializable::SetAttribute(const String& name, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "bool SetAttribute(const String&in, const Variant&in)", asMETHODPR(ParticleEmitter2D, SetAttribute, (const String&, const Variant&), bool), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimation(const String& name, ValueAnimation* attributeAnimation, WrapMode wrapMode=WM_LOOP, float speed=1.0f) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "void SetAttributeAnimation(const String&in, ValueAnimation@+, WrapMode = WM_LOOP, float = 1.0f)", asMETHODPR(ParticleEmitter2D, SetAttributeAnimation, (const String&, ValueAnimation*, WrapMode, float), void), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimationSpeed(const String& name, float speed) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "void SetAttributeAnimationSpeed(const String&in, float)", asMETHODPR(ParticleEmitter2D, SetAttributeAnimationSpeed, (const String&, float), void), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimationTime(const String& name, float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "void SetAttributeAnimationTime(const String&in, float)", asMETHODPR(ParticleEmitter2D, SetAttributeAnimationTime, (const String&, float), void), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimationWrapMode(const String& name, WrapMode wrapMode) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "void SetAttributeAnimationWrapMode(const String&in, WrapMode)", asMETHODPR(ParticleEmitter2D, SetAttributeAnimationWrapMode, (const String&, WrapMode), void), asCALL_THISCALL);
    // void Drawable::SetBasePass(unsigned batchIndex) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "void SetBasePass(uint)", asMETHODPR(ParticleEmitter2D, SetBasePass, (unsigned), void), asCALL_THISCALL);
    // void ParticleEmitter2D::SetBlendMode(BlendMode blendMode) | File: ../Urho2D/ParticleEmitter2D.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "void SetBlendMode(BlendMode)", asMETHODPR(ParticleEmitter2D, SetBlendMode, (BlendMode), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter2D", "void set_blendMode(BlendMode)", asMETHODPR(ParticleEmitter2D, SetBlendMode, (BlendMode), void), asCALL_THISCALL);
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "void SetBlockEvents(bool)", asMETHODPR(ParticleEmitter2D, SetBlockEvents, (bool), void), asCALL_THISCALL);
    // void Drawable::SetCastShadows(bool enable) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "void SetCastShadows(bool)", asMETHODPR(ParticleEmitter2D, SetCastShadows, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter2D", "void set_castShadows(bool)", asMETHODPR(ParticleEmitter2D, SetCastShadows, (bool), void), asCALL_THISCALL);
    // void Drawable::SetDrawDistance(float distance) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "void SetDrawDistance(float)", asMETHODPR(ParticleEmitter2D, SetDrawDistance, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter2D", "void set_drawDistance(float)", asMETHODPR(ParticleEmitter2D, SetDrawDistance, (float), void), asCALL_THISCALL);
    // void ParticleEmitter2D::SetEffect(ParticleEffect2D* effect) | File: ../Urho2D/ParticleEmitter2D.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "void SetEffect(ParticleEffect2D@+)", asMETHODPR(ParticleEmitter2D, SetEffect, (ParticleEffect2D*), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter2D", "void set_effect(ParticleEffect2D@+)", asMETHODPR(ParticleEmitter2D, SetEffect, (ParticleEffect2D*), void), asCALL_THISCALL);
    // void ParticleEmitter2D::SetEmitting(bool enable) | File: ../Urho2D/ParticleEmitter2D.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "void SetEmitting(bool)", asMETHODPR(ParticleEmitter2D, SetEmitting, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter2D", "void set_emitting(bool)", asMETHODPR(ParticleEmitter2D, SetEmitting, (bool), void), asCALL_THISCALL);
    // void Component::SetEnabled(bool enable) | File: ../Scene/Component.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "void SetEnabled(bool)", asMETHODPR(ParticleEmitter2D, SetEnabled, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter2D", "void set_enabled(bool)", asMETHODPR(ParticleEmitter2D, SetEnabled, (bool), void), asCALL_THISCALL);
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "void SetGlobalVar(StringHash, const Variant&in)", asMETHODPR(ParticleEmitter2D, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter2D", "void set_globalVar(StringHash, const Variant&in)", asMETHODPR(ParticleEmitter2D, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    // void Serializable::SetInstanceDefault(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "void SetInstanceDefault(bool)", asMETHODPR(ParticleEmitter2D, SetInstanceDefault, (bool), void), asCALL_THISCALL);
    // void Serializable::SetInterceptNetworkUpdate(const String& attributeName, bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "void SetInterceptNetworkUpdate(const String&in, bool)", asMETHODPR(ParticleEmitter2D, SetInterceptNetworkUpdate, (const String&, bool), void), asCALL_THISCALL);
    // void Drawable2D::SetLayer(int layer) | File: ../Urho2D/Drawable2D.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "void SetLayer(int)", asMETHODPR(ParticleEmitter2D, SetLayer, (int), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter2D", "void set_layer(int)", asMETHODPR(ParticleEmitter2D, SetLayer, (int), void), asCALL_THISCALL);
    // void Drawable::SetLightMask(unsigned mask) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "void SetLightMask(uint)", asMETHODPR(ParticleEmitter2D, SetLightMask, (unsigned), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter2D", "void set_lightMask(uint)", asMETHODPR(ParticleEmitter2D, SetLightMask, (unsigned), void), asCALL_THISCALL);
    // void Drawable::SetLodBias(float bias) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "void SetLodBias(float)", asMETHODPR(ParticleEmitter2D, SetLodBias, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter2D", "void set_lodBias(float)", asMETHODPR(ParticleEmitter2D, SetLodBias, (float), void), asCALL_THISCALL);
    // void Drawable::SetMaxLights(unsigned num) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "void SetMaxLights(uint)", asMETHODPR(ParticleEmitter2D, SetMaxLights, (unsigned), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter2D", "void set_maxLights(uint)", asMETHODPR(ParticleEmitter2D, SetMaxLights, (unsigned), void), asCALL_THISCALL);
    // void ParticleEmitter2D::SetMaxParticles(unsigned maxParticles) | File: ../Urho2D/ParticleEmitter2D.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "void SetMaxParticles(uint)", asMETHODPR(ParticleEmitter2D, SetMaxParticles, (unsigned), void), asCALL_THISCALL);
    // void Drawable::SetMinMaxZ(float minZ, float maxZ) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "void SetMinMaxZ(float, float)", asMETHODPR(ParticleEmitter2D, SetMinMaxZ, (float, float), void), asCALL_THISCALL);
    // void Animatable::SetObjectAnimation(ObjectAnimation* objectAnimation) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "void SetObjectAnimation(ObjectAnimation@+)", asMETHODPR(ParticleEmitter2D, SetObjectAnimation, (ObjectAnimation*), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter2D", "void set_objectAnimation(ObjectAnimation@+)", asMETHODPR(ParticleEmitter2D, SetObjectAnimation, (ObjectAnimation*), void), asCALL_THISCALL);
    // void Animatable::SetObjectAnimationAttr(const ResourceRef& value) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "void SetObjectAnimationAttr(const ResourceRef&in)", asMETHODPR(ParticleEmitter2D, SetObjectAnimationAttr, (const ResourceRef&), void), asCALL_THISCALL);
    // void Drawable::SetOccludee(bool enable) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "void SetOccludee(bool)", asMETHODPR(ParticleEmitter2D, SetOccludee, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter2D", "void set_occludee(bool)", asMETHODPR(ParticleEmitter2D, SetOccludee, (bool), void), asCALL_THISCALL);
    // void Drawable::SetOccluder(bool enable) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "void SetOccluder(bool)", asMETHODPR(ParticleEmitter2D, SetOccluder, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter2D", "void set_occluder(bool)", asMETHODPR(ParticleEmitter2D, SetOccluder, (bool), void), asCALL_THISCALL);
    // void Drawable2D::SetOrderInLayer(int orderInLayer) | File: ../Urho2D/Drawable2D.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "void SetOrderInLayer(int)", asMETHODPR(ParticleEmitter2D, SetOrderInLayer, (int), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter2D", "void set_orderInLayer(int)", asMETHODPR(ParticleEmitter2D, SetOrderInLayer, (int), void), asCALL_THISCALL);
    // void ParticleEmitter2D::SetParticleEffectAttr(const ResourceRef& value) | File: ../Urho2D/ParticleEmitter2D.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "void SetParticleEffectAttr(const ResourceRef&in)", asMETHODPR(ParticleEmitter2D, SetParticleEffectAttr, (const ResourceRef&), void), asCALL_THISCALL);
    // void Drawable::SetShadowDistance(float distance) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "void SetShadowDistance(float)", asMETHODPR(ParticleEmitter2D, SetShadowDistance, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter2D", "void set_shadowDistance(float)", asMETHODPR(ParticleEmitter2D, SetShadowDistance, (float), void), asCALL_THISCALL);
    // void Drawable::SetShadowMask(unsigned mask) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "void SetShadowMask(uint)", asMETHODPR(ParticleEmitter2D, SetShadowMask, (unsigned), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter2D", "void set_shadowMask(uint)", asMETHODPR(ParticleEmitter2D, SetShadowMask, (unsigned), void), asCALL_THISCALL);
    // void Drawable::SetSortValue(float value) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "void SetSortValue(float)", asMETHODPR(ParticleEmitter2D, SetSortValue, (float), void), asCALL_THISCALL);
    // void ParticleEmitter2D::SetSprite(Sprite2D* sprite) | File: ../Urho2D/ParticleEmitter2D.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "void SetSprite(Sprite2D@+)", asMETHODPR(ParticleEmitter2D, SetSprite, (Sprite2D*), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter2D", "void set_sprite(Sprite2D@+)", asMETHODPR(ParticleEmitter2D, SetSprite, (Sprite2D*), void), asCALL_THISCALL);
    // void ParticleEmitter2D::SetSpriteAttr(const ResourceRef& value) | File: ../Urho2D/ParticleEmitter2D.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "void SetSpriteAttr(const ResourceRef&in)", asMETHODPR(ParticleEmitter2D, SetSpriteAttr, (const ResourceRef&), void), asCALL_THISCALL);
    // void Serializable::SetTemporary(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "void SetTemporary(bool)", asMETHODPR(ParticleEmitter2D, SetTemporary, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter2D", "void set_temporary(bool)", asMETHODPR(ParticleEmitter2D, SetTemporary, (bool), void), asCALL_THISCALL);
    // void Drawable::SetViewMask(unsigned mask) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "void SetViewMask(uint)", asMETHODPR(ParticleEmitter2D, SetViewMask, (unsigned), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter2D", "void set_viewMask(uint)", asMETHODPR(ParticleEmitter2D, SetViewMask, (unsigned), void), asCALL_THISCALL);
    // void Drawable::SetZone(Zone* zone, bool temporary=false) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "void SetZone(Zone@+, bool = false)", asMETHODPR(ParticleEmitter2D, SetZone, (Zone*, bool), void), asCALL_THISCALL);
    // void Drawable::SetZoneMask(unsigned mask) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "void SetZoneMask(uint)", asMETHODPR(ParticleEmitter2D, SetZoneMask, (unsigned), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter2D", "void set_zoneMask(uint)", asMETHODPR(ParticleEmitter2D, SetZoneMask, (unsigned), void), asCALL_THISCALL);
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "void UnsubscribeFromAllEvents()", asMETHODPR(ParticleEmitter2D, UnsubscribeFromAllEvents, (), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", asFUNCTION(ParticleEmitter2D_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), asCALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "void UnsubscribeFromEvent(StringHash)", asMETHODPR(ParticleEmitter2D, UnsubscribeFromEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "void UnsubscribeFromEvent(Object@+, StringHash)", asMETHODPR(ParticleEmitter2D, UnsubscribeFromEvent, (Object*, StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "void UnsubscribeFromEvents(Object@+)", asMETHODPR(ParticleEmitter2D, UnsubscribeFromEvents, (Object*), void), asCALL_THISCALL);
    // virtual void Drawable::UpdateBatches(const FrameInfo& frame) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "void UpdateBatches(const FrameInfo&in)", asMETHODPR(ParticleEmitter2D, UpdateBatches, (const FrameInfo&), void), asCALL_THISCALL);
    // virtual void Drawable::UpdateGeometry(const FrameInfo& frame) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "void UpdateGeometry(const FrameInfo&in)", asMETHODPR(ParticleEmitter2D, UpdateGeometry, (const FrameInfo&), void), asCALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "int WeakRefs() const", asMETHODPR(ParticleEmitter2D, WeakRefs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter2D", "int get_weakRefs() const", asMETHODPR(ParticleEmitter2D, WeakRefs, () const, int), asCALL_THISCALL);
    // void Serializable::WriteDeltaUpdate(Serializer& dest, const DirtyBits& attributeBits, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "void WriteDeltaUpdate(Serializer&, const DirtyBits&in, uint8)", asMETHODPR(ParticleEmitter2D, WriteDeltaUpdate, (Serializer&, const DirtyBits&, unsigned char), void), asCALL_THISCALL);
    // void Serializable::WriteInitialDeltaUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "void WriteInitialDeltaUpdate(Serializer&, uint8)", asMETHODPR(ParticleEmitter2D, WriteInitialDeltaUpdate, (Serializer&, unsigned char), void), asCALL_THISCALL);
    // void Serializable::WriteLatestDataUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ParticleEmitter2D", "void WriteLatestDataUpdate(Serializer&, uint8)", asMETHODPR(ParticleEmitter2D, WriteLatestDataUpdate, (Serializer&, unsigned char), void), asCALL_THISCALL);
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
    engine->RegisterObjectBehaviour("Pass", asBEHAVE_ADDREF, "void f()", asMETHODPR(Pass, AddRef, (), void), asCALL_THISCALL);
    // bool Pass::GetAlphaToCoverage() const | File: ../Graphics/Technique.h
    engine->RegisterObjectMethod("Pass", "bool GetAlphaToCoverage() const", asMETHODPR(Pass, GetAlphaToCoverage, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Pass", "bool get_alphaToCoverage() const", asMETHODPR(Pass, GetAlphaToCoverage, () const, bool), asCALL_THISCALL);
    // BlendMode Pass::GetBlendMode() const | File: ../Graphics/Technique.h
    engine->RegisterObjectMethod("Pass", "BlendMode GetBlendMode() const", asMETHODPR(Pass, GetBlendMode, () const, BlendMode), asCALL_THISCALL);
    engine->RegisterObjectMethod("Pass", "BlendMode get_blendMode() const", asMETHODPR(Pass, GetBlendMode, () const, BlendMode), asCALL_THISCALL);
    // CullMode Pass::GetCullMode() const | File: ../Graphics/Technique.h
    engine->RegisterObjectMethod("Pass", "CullMode GetCullMode() const", asMETHODPR(Pass, GetCullMode, () const, CullMode), asCALL_THISCALL);
    engine->RegisterObjectMethod("Pass", "CullMode get_cullMode() const", asMETHODPR(Pass, GetCullMode, () const, CullMode), asCALL_THISCALL);
    // CompareMode Pass::GetDepthTestMode() const | File: ../Graphics/Technique.h
    engine->RegisterObjectMethod("Pass", "CompareMode GetDepthTestMode() const", asMETHODPR(Pass, GetDepthTestMode, () const, CompareMode), asCALL_THISCALL);
    engine->RegisterObjectMethod("Pass", "CompareMode get_depthTestMode() const", asMETHODPR(Pass, GetDepthTestMode, () const, CompareMode), asCALL_THISCALL);
    // bool Pass::GetDepthWrite() const | File: ../Graphics/Technique.h
    engine->RegisterObjectMethod("Pass", "bool GetDepthWrite() const", asMETHODPR(Pass, GetDepthWrite, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Pass", "bool get_depthWrite() const", asMETHODPR(Pass, GetDepthWrite, () const, bool), asCALL_THISCALL);
    // String Pass::GetEffectivePixelShaderDefines() const | File: ../Graphics/Technique.h
    engine->RegisterObjectMethod("Pass", "String GetEffectivePixelShaderDefines() const", asMETHODPR(Pass, GetEffectivePixelShaderDefines, () const, String), asCALL_THISCALL);
    // String Pass::GetEffectiveVertexShaderDefines() const | File: ../Graphics/Technique.h
    engine->RegisterObjectMethod("Pass", "String GetEffectiveVertexShaderDefines() const", asMETHODPR(Pass, GetEffectiveVertexShaderDefines, () const, String), asCALL_THISCALL);
    // unsigned Pass::GetIndex() const | File: ../Graphics/Technique.h
    engine->RegisterObjectMethod("Pass", "uint GetIndex() const", asMETHODPR(Pass, GetIndex, () const, unsigned), asCALL_THISCALL);
    // PassLightingMode Pass::GetLightingMode() const | File: ../Graphics/Technique.h
    engine->RegisterObjectMethod("Pass", "PassLightingMode GetLightingMode() const", asMETHODPR(Pass, GetLightingMode, () const, PassLightingMode), asCALL_THISCALL);
    engine->RegisterObjectMethod("Pass", "PassLightingMode get_lightingMode() const", asMETHODPR(Pass, GetLightingMode, () const, PassLightingMode), asCALL_THISCALL);
    // const String& Pass::GetName() const | File: ../Graphics/Technique.h
    engine->RegisterObjectMethod("Pass", "const String& GetName() const", asMETHODPR(Pass, GetName, () const, const String&), asCALL_THISCALL);
    // const String& Pass::GetPixelShader() const | File: ../Graphics/Technique.h
    engine->RegisterObjectMethod("Pass", "const String& GetPixelShader() const", asMETHODPR(Pass, GetPixelShader, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Pass", "const String& get_pixelShader() const", asMETHODPR(Pass, GetPixelShader, () const, const String&), asCALL_THISCALL);
    // const String& Pass::GetPixelShaderDefineExcludes() const | File: ../Graphics/Technique.h
    engine->RegisterObjectMethod("Pass", "const String& GetPixelShaderDefineExcludes() const", asMETHODPR(Pass, GetPixelShaderDefineExcludes, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Pass", "const String& get_pixelShaderDefineExcludes() const", asMETHODPR(Pass, GetPixelShaderDefineExcludes, () const, const String&), asCALL_THISCALL);
    // const String& Pass::GetPixelShaderDefines() const | File: ../Graphics/Technique.h
    engine->RegisterObjectMethod("Pass", "const String& GetPixelShaderDefines() const", asMETHODPR(Pass, GetPixelShaderDefines, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Pass", "const String& get_pixelShaderDefines() const", asMETHODPR(Pass, GetPixelShaderDefines, () const, const String&), asCALL_THISCALL);
    // Vector<SharedPtr<ShaderVariation>>& Pass::GetPixelShaders() | File: ../Graphics/Technique.h
    engine->RegisterObjectMethod("Pass", "Array<ShaderVariation@>@ GetPixelShaders()", asFUNCTION(Pass_GetPixelShaders_void), asCALL_CDECL_OBJFIRST);
    // Vector<SharedPtr<ShaderVariation>>& Pass::GetPixelShaders(const StringHash& extraDefinesHash) | File: ../Graphics/Technique.h
    engine->RegisterObjectMethod("Pass", "Array<ShaderVariation@>@ GetPixelShaders(const StringHash&in)", asFUNCTION(Pass_GetPixelShaders_StringHash), asCALL_CDECL_OBJFIRST);
    // unsigned Pass::GetShadersLoadedFrameNumber() const | File: ../Graphics/Technique.h
    engine->RegisterObjectMethod("Pass", "uint GetShadersLoadedFrameNumber() const", asMETHODPR(Pass, GetShadersLoadedFrameNumber, () const, unsigned), asCALL_THISCALL);
    // const String& Pass::GetVertexShader() const | File: ../Graphics/Technique.h
    engine->RegisterObjectMethod("Pass", "const String& GetVertexShader() const", asMETHODPR(Pass, GetVertexShader, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Pass", "const String& get_vertexShader() const", asMETHODPR(Pass, GetVertexShader, () const, const String&), asCALL_THISCALL);
    // const String& Pass::GetVertexShaderDefineExcludes() const | File: ../Graphics/Technique.h
    engine->RegisterObjectMethod("Pass", "const String& GetVertexShaderDefineExcludes() const", asMETHODPR(Pass, GetVertexShaderDefineExcludes, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Pass", "const String& get_vertexShaderDefineExcludes() const", asMETHODPR(Pass, GetVertexShaderDefineExcludes, () const, const String&), asCALL_THISCALL);
    // const String& Pass::GetVertexShaderDefines() const | File: ../Graphics/Technique.h
    engine->RegisterObjectMethod("Pass", "const String& GetVertexShaderDefines() const", asMETHODPR(Pass, GetVertexShaderDefines, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Pass", "const String& get_vertexShaderDefines() const", asMETHODPR(Pass, GetVertexShaderDefines, () const, const String&), asCALL_THISCALL);
    // Vector<SharedPtr<ShaderVariation>>& Pass::GetVertexShaders() | File: ../Graphics/Technique.h
    engine->RegisterObjectMethod("Pass", "Array<ShaderVariation@>@ GetVertexShaders()", asFUNCTION(Pass_GetVertexShaders_void), asCALL_CDECL_OBJFIRST);
    // Vector<SharedPtr<ShaderVariation>>& Pass::GetVertexShaders(const StringHash& extraDefinesHash) | File: ../Graphics/Technique.h
    engine->RegisterObjectMethod("Pass", "Array<ShaderVariation@>@ GetVertexShaders(const StringHash&in)", asFUNCTION(Pass_GetVertexShaders_StringHash), asCALL_CDECL_OBJFIRST);
    // bool Pass::IsDesktop() const | File: ../Graphics/Technique.h
    engine->RegisterObjectMethod("Pass", "bool IsDesktop() const", asMETHODPR(Pass, IsDesktop, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Pass", "bool get_desktop() const", asMETHODPR(Pass, IsDesktop, () const, bool), asCALL_THISCALL);
    // void Pass::MarkShadersLoaded(unsigned frameNumber) | File: ../Graphics/Technique.h
    engine->RegisterObjectMethod("Pass", "void MarkShadersLoaded(uint)", asMETHODPR(Pass, MarkShadersLoaded, (unsigned), void), asCALL_THISCALL);
    // explicit Pass::Pass(const String& name) | File: ../Graphics/Technique.h
    engine->RegisterObjectBehaviour("Pass", asBEHAVE_FACTORY, "Pass@+ f(const String&in)", asFUNCTION(Pass_Pass_String), asCALL_CDECL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("Pass", "int Refs() const", asMETHODPR(Pass, Refs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("Pass", "int get_refs() const", asMETHODPR(Pass, Refs, () const, int), asCALL_THISCALL);
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("Pass", asBEHAVE_RELEASE, "void f()", asMETHODPR(Pass, ReleaseRef, (), void), asCALL_THISCALL);
    // void Pass::ReleaseShaders() | File: ../Graphics/Technique.h
    engine->RegisterObjectMethod("Pass", "void ReleaseShaders()", asMETHODPR(Pass, ReleaseShaders, (), void), asCALL_THISCALL);
    // void Pass::SetAlphaToCoverage(bool enable) | File: ../Graphics/Technique.h
    engine->RegisterObjectMethod("Pass", "void SetAlphaToCoverage(bool)", asMETHODPR(Pass, SetAlphaToCoverage, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Pass", "void set_alphaToCoverage(bool)", asMETHODPR(Pass, SetAlphaToCoverage, (bool), void), asCALL_THISCALL);
    // void Pass::SetBlendMode(BlendMode mode) | File: ../Graphics/Technique.h
    engine->RegisterObjectMethod("Pass", "void SetBlendMode(BlendMode)", asMETHODPR(Pass, SetBlendMode, (BlendMode), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Pass", "void set_blendMode(BlendMode)", asMETHODPR(Pass, SetBlendMode, (BlendMode), void), asCALL_THISCALL);
    // void Pass::SetCullMode(CullMode mode) | File: ../Graphics/Technique.h
    engine->RegisterObjectMethod("Pass", "void SetCullMode(CullMode)", asMETHODPR(Pass, SetCullMode, (CullMode), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Pass", "void set_cullMode(CullMode)", asMETHODPR(Pass, SetCullMode, (CullMode), void), asCALL_THISCALL);
    // void Pass::SetDepthTestMode(CompareMode mode) | File: ../Graphics/Technique.h
    engine->RegisterObjectMethod("Pass", "void SetDepthTestMode(CompareMode)", asMETHODPR(Pass, SetDepthTestMode, (CompareMode), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Pass", "void set_depthTestMode(CompareMode)", asMETHODPR(Pass, SetDepthTestMode, (CompareMode), void), asCALL_THISCALL);
    // void Pass::SetDepthWrite(bool enable) | File: ../Graphics/Technique.h
    engine->RegisterObjectMethod("Pass", "void SetDepthWrite(bool)", asMETHODPR(Pass, SetDepthWrite, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Pass", "void set_depthWrite(bool)", asMETHODPR(Pass, SetDepthWrite, (bool), void), asCALL_THISCALL);
    // void Pass::SetIsDesktop(bool enable) | File: ../Graphics/Technique.h
    engine->RegisterObjectMethod("Pass", "void SetIsDesktop(bool)", asMETHODPR(Pass, SetIsDesktop, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Pass", "void set_desktop(bool)", asMETHODPR(Pass, SetIsDesktop, (bool), void), asCALL_THISCALL);
    // void Pass::SetLightingMode(PassLightingMode mode) | File: ../Graphics/Technique.h
    engine->RegisterObjectMethod("Pass", "void SetLightingMode(PassLightingMode)", asMETHODPR(Pass, SetLightingMode, (PassLightingMode), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Pass", "void set_lightingMode(PassLightingMode)", asMETHODPR(Pass, SetLightingMode, (PassLightingMode), void), asCALL_THISCALL);
    // void Pass::SetPixelShader(const String& name) | File: ../Graphics/Technique.h
    engine->RegisterObjectMethod("Pass", "void SetPixelShader(const String&in)", asMETHODPR(Pass, SetPixelShader, (const String&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Pass", "void set_pixelShader(const String&in)", asMETHODPR(Pass, SetPixelShader, (const String&), void), asCALL_THISCALL);
    // void Pass::SetPixelShaderDefineExcludes(const String& excludes) | File: ../Graphics/Technique.h
    engine->RegisterObjectMethod("Pass", "void SetPixelShaderDefineExcludes(const String&in)", asMETHODPR(Pass, SetPixelShaderDefineExcludes, (const String&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Pass", "void set_pixelShaderDefineExcludes(const String&in)", asMETHODPR(Pass, SetPixelShaderDefineExcludes, (const String&), void), asCALL_THISCALL);
    // void Pass::SetPixelShaderDefines(const String& defines) | File: ../Graphics/Technique.h
    engine->RegisterObjectMethod("Pass", "void SetPixelShaderDefines(const String&in)", asMETHODPR(Pass, SetPixelShaderDefines, (const String&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Pass", "void set_pixelShaderDefines(const String&in)", asMETHODPR(Pass, SetPixelShaderDefines, (const String&), void), asCALL_THISCALL);
    // void Pass::SetVertexShader(const String& name) | File: ../Graphics/Technique.h
    engine->RegisterObjectMethod("Pass", "void SetVertexShader(const String&in)", asMETHODPR(Pass, SetVertexShader, (const String&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Pass", "void set_vertexShader(const String&in)", asMETHODPR(Pass, SetVertexShader, (const String&), void), asCALL_THISCALL);
    // void Pass::SetVertexShaderDefineExcludes(const String& excludes) | File: ../Graphics/Technique.h
    engine->RegisterObjectMethod("Pass", "void SetVertexShaderDefineExcludes(const String&in)", asMETHODPR(Pass, SetVertexShaderDefineExcludes, (const String&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Pass", "void set_vertexShaderDefineExcludes(const String&in)", asMETHODPR(Pass, SetVertexShaderDefineExcludes, (const String&), void), asCALL_THISCALL);
    // void Pass::SetVertexShaderDefines(const String& defines) | File: ../Graphics/Technique.h
    engine->RegisterObjectMethod("Pass", "void SetVertexShaderDefines(const String&in)", asMETHODPR(Pass, SetVertexShaderDefines, (const String&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Pass", "void set_vertexShaderDefines(const String&in)", asMETHODPR(Pass, SetVertexShaderDefines, (const String&), void), asCALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("Pass", "int WeakRefs() const", asMETHODPR(Pass, WeakRefs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("Pass", "int get_weakRefs() const", asMETHODPR(Pass, WeakRefs, () const, int), asCALL_THISCALL);
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
    engine->RegisterObjectMethod("PhysicsWorld", "void AddCollisionShape(CollisionShape@+)", asMETHODPR(PhysicsWorld, AddCollisionShape, (CollisionShape*), void), asCALL_THISCALL);
    // void PhysicsWorld::AddConstraint(Constraint* constraint) | File: ../Physics/PhysicsWorld.h
    engine->RegisterObjectMethod("PhysicsWorld", "void AddConstraint(Constraint@+)", asMETHODPR(PhysicsWorld, AddConstraint, (Constraint*), void), asCALL_THISCALL);
    // void PhysicsWorld::AddDelayedWorldTransform(const DelayedWorldTransform& transform) | File: ../Physics/PhysicsWorld.h
    engine->RegisterObjectMethod("PhysicsWorld", "void AddDelayedWorldTransform(const DelayedWorldTransform&in)", asMETHODPR(PhysicsWorld, AddDelayedWorldTransform, (const DelayedWorldTransform&), void), asCALL_THISCALL);
    // void RefCounted::AddRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("PhysicsWorld", asBEHAVE_ADDREF, "void f()", asMETHODPR(PhysicsWorld, AddRef, (), void), asCALL_THISCALL);
    // void Component::AddReplicationState(ComponentReplicationState* state) | File: ../Scene/Component.h
    // Error: type "ComponentReplicationState*" can not automatically bind
    // void PhysicsWorld::AddRigidBody(RigidBody* body) | File: ../Physics/PhysicsWorld.h
    engine->RegisterObjectMethod("PhysicsWorld", "void AddRigidBody(RigidBody@+)", asMETHODPR(PhysicsWorld, AddRigidBody, (RigidBody*), void), asCALL_THISCALL);
    // void Serializable::AllocateNetworkState() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("PhysicsWorld", "void AllocateNetworkState()", asMETHODPR(PhysicsWorld, AllocateNetworkState, (), void), asCALL_THISCALL);
    // virtual void Serializable::ApplyAttributes() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("PhysicsWorld", "void ApplyAttributes()", asMETHODPR(PhysicsWorld, ApplyAttributes, (), void), asCALL_THISCALL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // void Component::CleanupConnection(Connection* connection) | File: ../Scene/Component.h
    // Not registered because have @manualbind mark
    // void PhysicsWorld::CleanupGeometryCache() | File: ../Physics/PhysicsWorld.h
    engine->RegisterObjectMethod("PhysicsWorld", "void CleanupGeometryCache()", asMETHODPR(PhysicsWorld, CleanupGeometryCache, (), void), asCALL_THISCALL);
    // void PhysicsWorld::ConvexCast(PhysicsRaycastResult& result, CollisionShape* shape, const Vector3& startPos, const Quaternion& startRot, const Vector3& endPos, const Quaternion& endRot, unsigned collisionMask=M_MAX_UNSIGNED) | File: ../Physics/PhysicsWorld.h
    engine->RegisterObjectMethod("PhysicsWorld", "void ConvexCast(PhysicsRaycastResult&, CollisionShape@+, const Vector3&in, const Quaternion&in, const Vector3&in, const Quaternion&in, uint = M_MAX_UNSIGNED)", asMETHODPR(PhysicsWorld, ConvexCast, (PhysicsRaycastResult&, CollisionShape*, const Vector3&, const Quaternion&, const Vector3&, const Quaternion&, unsigned), void), asCALL_THISCALL);
    // void PhysicsWorld::ConvexCast(PhysicsRaycastResult& result, btCollisionShape* shape, const Vector3& startPos, const Quaternion& startRot, const Vector3& endPos, const Quaternion& endRot, unsigned collisionMask=M_MAX_UNSIGNED) | File: ../Physics/PhysicsWorld.h
    // Error: type "btCollisionShape*" can not automatically bind
    // void PhysicsWorld::draw3dText(const btVector3& location, const char* textString) override | File: ../Physics/PhysicsWorld.h
    // Error: type "const btVector3&" can not automatically bind
    // void PhysicsWorld::drawContactPoint(const btVector3& pointOnB, const btVector3& normalOnB, btScalar distance, int lifeTime, const btVector3& color) override | File: ../Physics/PhysicsWorld.h
    // Error: type "const btVector3&" can not automatically bind
    // void PhysicsWorld::DrawDebugGeometry(DebugRenderer* debug, bool depthTest) override | File: ../Physics/PhysicsWorld.h
    engine->RegisterObjectMethod("PhysicsWorld", "void DrawDebugGeometry(DebugRenderer@+, bool)", asMETHODPR(PhysicsWorld, DrawDebugGeometry, (DebugRenderer*, bool), void), asCALL_THISCALL);
    // void PhysicsWorld::DrawDebugGeometry(bool depthTest) | File: ../Physics/PhysicsWorld.h
    engine->RegisterObjectMethod("PhysicsWorld", "void DrawDebugGeometry(bool)", asMETHODPR(PhysicsWorld, DrawDebugGeometry, (bool), void), asCALL_THISCALL);
    // void PhysicsWorld::drawLine(const btVector3& from, const btVector3& to, const btVector3& color) override | File: ../Physics/PhysicsWorld.h
    // Error: type "const btVector3&" can not automatically bind
    // bool Animatable::GetAnimationEnabled() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("PhysicsWorld", "bool GetAnimationEnabled() const", asMETHODPR(PhysicsWorld, GetAnimationEnabled, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("PhysicsWorld", "bool get_animationEnabled() const", asMETHODPR(PhysicsWorld, GetAnimationEnabled, () const, bool), asCALL_THISCALL);
    // Variant Serializable::GetAttribute(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("PhysicsWorld", "Variant GetAttribute(uint) const", asMETHODPR(PhysicsWorld, GetAttribute, (unsigned) const, Variant), asCALL_THISCALL);
    engine->RegisterObjectMethod("PhysicsWorld", "Variant get_attributes(uint) const", asMETHODPR(PhysicsWorld, GetAttribute, (unsigned) const, Variant), asCALL_THISCALL);
    // Variant Serializable::GetAttribute(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("PhysicsWorld", "Variant GetAttribute(const String&in) const", asMETHODPR(PhysicsWorld, GetAttribute, (const String&) const, Variant), asCALL_THISCALL);
    // ValueAnimation* Animatable::GetAttributeAnimation(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("PhysicsWorld", "ValueAnimation@+ GetAttributeAnimation(const String&in) const", asMETHODPR(PhysicsWorld, GetAttributeAnimation, (const String&) const, ValueAnimation*), asCALL_THISCALL);
    // float Animatable::GetAttributeAnimationSpeed(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("PhysicsWorld", "float GetAttributeAnimationSpeed(const String&in) const", asMETHODPR(PhysicsWorld, GetAttributeAnimationSpeed, (const String&) const, float), asCALL_THISCALL);
    // float Animatable::GetAttributeAnimationTime(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("PhysicsWorld", "float GetAttributeAnimationTime(const String&in) const", asMETHODPR(PhysicsWorld, GetAttributeAnimationTime, (const String&) const, float), asCALL_THISCALL);
    // WrapMode Animatable::GetAttributeAnimationWrapMode(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("PhysicsWorld", "WrapMode GetAttributeAnimationWrapMode(const String&in) const", asMETHODPR(PhysicsWorld, GetAttributeAnimationWrapMode, (const String&) const, WrapMode), asCALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("PhysicsWorld", "Variant GetAttributeDefault(uint) const", asMETHODPR(PhysicsWorld, GetAttributeDefault, (unsigned) const, Variant), asCALL_THISCALL);
    engine->RegisterObjectMethod("PhysicsWorld", "Variant get_attributeDefaults(uint) const", asMETHODPR(PhysicsWorld, GetAttributeDefault, (unsigned) const, Variant), asCALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("PhysicsWorld", "Variant GetAttributeDefault(const String&in) const", asMETHODPR(PhysicsWorld, GetAttributeDefault, (const String&) const, Variant), asCALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("PhysicsWorld", "bool GetBlockEvents() const", asMETHODPR(PhysicsWorld, GetBlockEvents, () const, bool), asCALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("PhysicsWorld", "const String& GetCategory() const", asMETHODPR(PhysicsWorld, GetCategory, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("PhysicsWorld", "const String& get_category() const", asMETHODPR(PhysicsWorld, GetCategory, () const, const String&), asCALL_THISCALL);
    // void PhysicsWorld::GetCollidingBodies(PODVector<RigidBody*>& result, const RigidBody* body) | File: ../Physics/PhysicsWorld.h
    // Error: type "PODVector<RigidBody*>&" can not automatically bind
    // Component* Component::GetComponent(StringHash type) const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("PhysicsWorld", "Component@+ GetComponent(StringHash) const", asMETHODPR(PhysicsWorld, GetComponent, (StringHash) const, Component*), asCALL_THISCALL);
    // template<class T> T*  Component::GetComponent() const | File: ../Scene/Component.h
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
    engine->RegisterObjectMethod("PhysicsWorld", "int getDebugMode() const", asMETHODPR(PhysicsWorld, getDebugMode, () const, int), asCALL_THISCALL);
    // virtual void Component::GetDependencyNodes(PODVector<Node*>& dest) | File: ../Scene/Component.h
    // Error: type "PODVector<Node*>&" can not automatically bind
    // VariantMap& Object::GetEventDataMap() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("PhysicsWorld", "VariantMap& GetEventDataMap() const", asMETHODPR(PhysicsWorld, GetEventDataMap, () const, VariantMap&), asCALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("PhysicsWorld", "Object@+ GetEventSender() const", asMETHODPR(PhysicsWorld, GetEventSender, () const, Object*), asCALL_THISCALL);
    // int PhysicsWorld::GetFps() const | File: ../Physics/PhysicsWorld.h
    engine->RegisterObjectMethod("PhysicsWorld", "int GetFps() const", asMETHODPR(PhysicsWorld, GetFps, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("PhysicsWorld", "int get_fps() const", asMETHODPR(PhysicsWorld, GetFps, () const, int), asCALL_THISCALL);
    // CollisionGeometryDataCache& PhysicsWorld::GetGImpactTrimeshCache() | File: ../Physics/PhysicsWorld.h
    // Error: type "CollisionGeometryDataCache&" can not automatically bind
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("PhysicsWorld", "const Variant& GetGlobalVar(StringHash) const", asMETHODPR(PhysicsWorld, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    engine->RegisterObjectMethod("PhysicsWorld", "const Variant& get_globalVar(StringHash) const", asMETHODPR(PhysicsWorld, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("PhysicsWorld", "const VariantMap& GetGlobalVars() const", asMETHODPR(PhysicsWorld, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    engine->RegisterObjectMethod("PhysicsWorld", "const VariantMap& get_globalVars() const", asMETHODPR(PhysicsWorld, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    // Vector3 PhysicsWorld::GetGravity() const | File: ../Physics/PhysicsWorld.h
    engine->RegisterObjectMethod("PhysicsWorld", "Vector3 GetGravity() const", asMETHODPR(PhysicsWorld, GetGravity, () const, Vector3), asCALL_THISCALL);
    engine->RegisterObjectMethod("PhysicsWorld", "Vector3 get_gravity() const", asMETHODPR(PhysicsWorld, GetGravity, () const, Vector3), asCALL_THISCALL);
    // unsigned Component::GetID() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("PhysicsWorld", "uint GetID() const", asMETHODPR(PhysicsWorld, GetID, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("PhysicsWorld", "uint get_id() const", asMETHODPR(PhysicsWorld, GetID, () const, unsigned), asCALL_THISCALL);
    // bool Serializable::GetInterceptNetworkUpdate(const String& attributeName) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("PhysicsWorld", "bool GetInterceptNetworkUpdate(const String&in) const", asMETHODPR(PhysicsWorld, GetInterceptNetworkUpdate, (const String&) const, bool), asCALL_THISCALL);
    // bool PhysicsWorld::GetInternalEdge() const | File: ../Physics/PhysicsWorld.h
    engine->RegisterObjectMethod("PhysicsWorld", "bool GetInternalEdge() const", asMETHODPR(PhysicsWorld, GetInternalEdge, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("PhysicsWorld", "bool get_internalEdge() const", asMETHODPR(PhysicsWorld, GetInternalEdge, () const, bool), asCALL_THISCALL);
    // bool PhysicsWorld::GetInterpolation() const | File: ../Physics/PhysicsWorld.h
    engine->RegisterObjectMethod("PhysicsWorld", "bool GetInterpolation() const", asMETHODPR(PhysicsWorld, GetInterpolation, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("PhysicsWorld", "bool get_interpolation() const", asMETHODPR(PhysicsWorld, GetInterpolation, () const, bool), asCALL_THISCALL);
    // float PhysicsWorld::GetMaxNetworkAngularVelocity() const | File: ../Physics/PhysicsWorld.h
    engine->RegisterObjectMethod("PhysicsWorld", "float GetMaxNetworkAngularVelocity() const", asMETHODPR(PhysicsWorld, GetMaxNetworkAngularVelocity, () const, float), asCALL_THISCALL);
    // int PhysicsWorld::GetMaxSubSteps() const | File: ../Physics/PhysicsWorld.h
    engine->RegisterObjectMethod("PhysicsWorld", "int GetMaxSubSteps() const", asMETHODPR(PhysicsWorld, GetMaxSubSteps, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("PhysicsWorld", "int get_maxSubSteps() const", asMETHODPR(PhysicsWorld, GetMaxSubSteps, () const, int), asCALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetNetworkAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // NetworkState* Serializable::GetNetworkState() const | File: ../Scene/Serializable.h
    // Error: type "NetworkState*" can not automatically bind
    // Node* Component::GetNode() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("PhysicsWorld", "Node@+ GetNode() const", asMETHODPR(PhysicsWorld, GetNode, () const, Node*), asCALL_THISCALL);
    engine->RegisterObjectMethod("PhysicsWorld", "Node@+ get_node() const", asMETHODPR(PhysicsWorld, GetNode, () const, Node*), asCALL_THISCALL);
    // unsigned Serializable::GetNumAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("PhysicsWorld", "uint GetNumAttributes() const", asMETHODPR(PhysicsWorld, GetNumAttributes, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("PhysicsWorld", "uint get_numAttributes() const", asMETHODPR(PhysicsWorld, GetNumAttributes, () const, unsigned), asCALL_THISCALL);
    // int PhysicsWorld::GetNumIterations() const | File: ../Physics/PhysicsWorld.h
    engine->RegisterObjectMethod("PhysicsWorld", "int GetNumIterations() const", asMETHODPR(PhysicsWorld, GetNumIterations, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("PhysicsWorld", "int get_numIterations() const", asMETHODPR(PhysicsWorld, GetNumIterations, () const, int), asCALL_THISCALL);
    // unsigned Serializable::GetNumNetworkAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("PhysicsWorld", "uint GetNumNetworkAttributes() const", asMETHODPR(PhysicsWorld, GetNumNetworkAttributes, () const, unsigned), asCALL_THISCALL);
    // ObjectAnimation* Animatable::GetObjectAnimation() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("PhysicsWorld", "ObjectAnimation@+ GetObjectAnimation() const", asMETHODPR(PhysicsWorld, GetObjectAnimation, () const, ObjectAnimation*), asCALL_THISCALL);
    engine->RegisterObjectMethod("PhysicsWorld", "ObjectAnimation@+ get_objectAnimation() const", asMETHODPR(PhysicsWorld, GetObjectAnimation, () const, ObjectAnimation*), asCALL_THISCALL);
    // ResourceRef Animatable::GetObjectAnimationAttr() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("PhysicsWorld", "ResourceRef GetObjectAnimationAttr() const", asMETHODPR(PhysicsWorld, GetObjectAnimationAttr, () const, ResourceRef), asCALL_THISCALL);
    // void PhysicsWorld::GetRigidBodies(PODVector<RigidBody*>& result, const Sphere& sphere, unsigned collisionMask=M_MAX_UNSIGNED) | File: ../Physics/PhysicsWorld.h
    // Error: type "PODVector<RigidBody*>&" can not automatically bind
    // void PhysicsWorld::GetRigidBodies(PODVector<RigidBody*>& result, const BoundingBox& box, unsigned collisionMask=M_MAX_UNSIGNED) | File: ../Physics/PhysicsWorld.h
    // Error: type "PODVector<RigidBody*>&" can not automatically bind
    // void PhysicsWorld::GetRigidBodies(PODVector<RigidBody*>& result, const RigidBody* body) | File: ../Physics/PhysicsWorld.h
    // Error: type "PODVector<RigidBody*>&" can not automatically bind
    // Scene* Component::GetScene() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("PhysicsWorld", "Scene@+ GetScene() const", asMETHODPR(PhysicsWorld, GetScene, () const, Scene*), asCALL_THISCALL);
    // bool PhysicsWorld::GetSplitImpulse() const | File: ../Physics/PhysicsWorld.h
    engine->RegisterObjectMethod("PhysicsWorld", "bool GetSplitImpulse() const", asMETHODPR(PhysicsWorld, GetSplitImpulse, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("PhysicsWorld", "bool get_splitImpulse() const", asMETHODPR(PhysicsWorld, GetSplitImpulse, () const, bool), asCALL_THISCALL);
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("PhysicsWorld", "Object@+ GetSubsystem(StringHash) const", asMETHODPR(PhysicsWorld, GetSubsystem, (StringHash) const, Object*), asCALL_THISCALL);
    // template<class T> T*  Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // CollisionGeometryDataCache& PhysicsWorld::GetTriMeshCache() | File: ../Physics/PhysicsWorld.h
    // Error: type "CollisionGeometryDataCache&" can not automatically bind
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("PhysicsWorld", "StringHash GetType() const", asMETHODPR(PhysicsWorld, GetType, () const, StringHash), asCALL_THISCALL);
    engine->RegisterObjectMethod("PhysicsWorld", "StringHash get_type() const", asMETHODPR(PhysicsWorld, GetType, () const, StringHash), asCALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("PhysicsWorld", "const String& GetTypeName() const", asMETHODPR(PhysicsWorld, GetTypeName, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("PhysicsWorld", "const String& get_typeName() const", asMETHODPR(PhysicsWorld, GetTypeName, () const, const String&), asCALL_THISCALL);
    // btDiscreteDynamicsWorld* PhysicsWorld::GetWorld() | File: ../Physics/PhysicsWorld.h
    // Error: type "btDiscreteDynamicsWorld*" can not automatically bind
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("PhysicsWorld", "bool HasEventHandlers() const", asMETHODPR(PhysicsWorld, HasEventHandlers, () const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("PhysicsWorld", "bool HasSubscribedToEvent(StringHash) const", asMETHODPR(PhysicsWorld, HasSubscribedToEvent, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("PhysicsWorld", "bool HasSubscribedToEvent(Object@+, StringHash) const", asMETHODPR(PhysicsWorld, HasSubscribedToEvent, (Object*, StringHash) const, bool), asCALL_THISCALL);
    // bool PhysicsWorld::IsApplyingTransforms() const | File: ../Physics/PhysicsWorld.h
    engine->RegisterObjectMethod("PhysicsWorld", "bool IsApplyingTransforms() const", asMETHODPR(PhysicsWorld, IsApplyingTransforms, () const, bool), asCALL_THISCALL);
    // bool Component::IsEnabled() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("PhysicsWorld", "bool IsEnabled() const", asMETHODPR(PhysicsWorld, IsEnabled, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("PhysicsWorld", "bool get_enabled() const", asMETHODPR(PhysicsWorld, IsEnabled, () const, bool), asCALL_THISCALL);
    // bool Component::IsEnabledEffective() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("PhysicsWorld", "bool IsEnabledEffective() const", asMETHODPR(PhysicsWorld, IsEnabledEffective, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("PhysicsWorld", "bool get_enabledEffective() const", asMETHODPR(PhysicsWorld, IsEnabledEffective, () const, bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("PhysicsWorld", "bool IsInstanceOf(StringHash) const", asMETHODPR(PhysicsWorld, IsInstanceOf, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // bool Component::IsReplicated() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("PhysicsWorld", "bool IsReplicated() const", asMETHODPR(PhysicsWorld, IsReplicated, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("PhysicsWorld", "bool get_replicated() const", asMETHODPR(PhysicsWorld, IsReplicated, () const, bool), asCALL_THISCALL);
    // bool PhysicsWorld::IsSimulating() const | File: ../Physics/PhysicsWorld.h
    engine->RegisterObjectMethod("PhysicsWorld", "bool IsSimulating() const", asMETHODPR(PhysicsWorld, IsSimulating, () const, bool), asCALL_THISCALL);
    // bool Serializable::IsTemporary() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("PhysicsWorld", "bool IsTemporary() const", asMETHODPR(PhysicsWorld, IsTemporary, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("PhysicsWorld", "bool get_temporary() const", asMETHODPR(PhysicsWorld, IsTemporary, () const, bool), asCALL_THISCALL);
    // bool PhysicsWorld::IsUpdateEnabled() const | File: ../Physics/PhysicsWorld.h
    engine->RegisterObjectMethod("PhysicsWorld", "bool IsUpdateEnabled() const", asMETHODPR(PhysicsWorld, IsUpdateEnabled, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("PhysicsWorld", "bool get_updateEnabled() const", asMETHODPR(PhysicsWorld, IsUpdateEnabled, () const, bool), asCALL_THISCALL);
    // bool PhysicsWorld::isVisible(const btVector3& aabbMin, const btVector3& aabbMax) override | File: ../Physics/PhysicsWorld.h
    // Error: type "const btVector3&" can not automatically bind
    // virtual bool Serializable::Load(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("PhysicsWorld", "bool Load(Deserializer&)", asMETHODPR(PhysicsWorld, Load, (Deserializer&), bool), asCALL_THISCALL);
    // bool Animatable::LoadJSON(const JSONValue& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("PhysicsWorld", "bool LoadJSON(const JSONValue&in)", asMETHODPR(PhysicsWorld, LoadJSON, (const JSONValue&), bool), asCALL_THISCALL);
    // bool Animatable::LoadXML(const XMLElement& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("PhysicsWorld", "bool LoadXML(const XMLElement&in)", asMETHODPR(PhysicsWorld, LoadXML, (const XMLElement&), bool), asCALL_THISCALL);
    // void Component::MarkNetworkUpdate() override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("PhysicsWorld", "void MarkNetworkUpdate()", asMETHODPR(PhysicsWorld, MarkNetworkUpdate, (), void), asCALL_THISCALL);
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("PhysicsWorld", "void OnEvent(Object@+, StringHash, VariantMap&)", asMETHODPR(PhysicsWorld, OnEvent, (Object*, StringHash, VariantMap&), void), asCALL_THISCALL);
    // virtual void Serializable::OnGetAttribute(const AttributeInfo& attr, Variant& dest) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("PhysicsWorld", "void OnGetAttribute(const AttributeInfo&in, Variant&) const", asMETHODPR(PhysicsWorld, OnGetAttribute, (const AttributeInfo&, Variant&) const, void), asCALL_THISCALL);
    // virtual void Serializable::OnSetAttribute(const AttributeInfo& attr, const Variant& src) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("PhysicsWorld", "void OnSetAttribute(const AttributeInfo&in, const Variant&in)", asMETHODPR(PhysicsWorld, OnSetAttribute, (const AttributeInfo&, const Variant&), void), asCALL_THISCALL);
    // virtual void Component::OnSetEnabled() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("PhysicsWorld", "void OnSetEnabled()", asMETHODPR(PhysicsWorld, OnSetEnabled, (), void), asCALL_THISCALL);
    // explicit PhysicsWorld::PhysicsWorld(Context* context) | File: ../Physics/PhysicsWorld.h
    engine->RegisterObjectBehaviour("PhysicsWorld", asBEHAVE_FACTORY, "PhysicsWorld@+ f()", asFUNCTION(PhysicsWorld_PhysicsWorld_Context), asCALL_CDECL);
    // void Component::PrepareNetworkUpdate() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("PhysicsWorld", "void PrepareNetworkUpdate()", asMETHODPR(PhysicsWorld, PrepareNetworkUpdate, (), void), asCALL_THISCALL);
    // void PhysicsWorld::Raycast(PODVector<PhysicsRaycastResult>& result, const Ray& ray, float maxDistance, unsigned collisionMask=M_MAX_UNSIGNED) | File: ../Physics/PhysicsWorld.h
    // Error: type "PODVector<PhysicsRaycastResult>&" can not automatically bind
    // void PhysicsWorld::RaycastSingle(PhysicsRaycastResult& result, const Ray& ray, float maxDistance, unsigned collisionMask=M_MAX_UNSIGNED) | File: ../Physics/PhysicsWorld.h
    engine->RegisterObjectMethod("PhysicsWorld", "void RaycastSingle(PhysicsRaycastResult&, const Ray&in, float, uint = M_MAX_UNSIGNED)", asMETHODPR(PhysicsWorld, RaycastSingle, (PhysicsRaycastResult&, const Ray&, float, unsigned), void), asCALL_THISCALL);
    // void PhysicsWorld::RaycastSingleSegmented(PhysicsRaycastResult& result, const Ray& ray, float maxDistance, float segmentDistance, unsigned collisionMask=M_MAX_UNSIGNED, float overlapDistance=0.1f) | File: ../Physics/PhysicsWorld.h
    engine->RegisterObjectMethod("PhysicsWorld", "void RaycastSingleSegmented(PhysicsRaycastResult&, const Ray&in, float, float, uint = M_MAX_UNSIGNED, float = 0.1f)", asMETHODPR(PhysicsWorld, RaycastSingleSegmented, (PhysicsRaycastResult&, const Ray&, float, float, unsigned, float), void), asCALL_THISCALL);
    // bool Serializable::ReadDeltaUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("PhysicsWorld", "bool ReadDeltaUpdate(Deserializer&)", asMETHODPR(PhysicsWorld, ReadDeltaUpdate, (Deserializer&), bool), asCALL_THISCALL);
    // bool Serializable::ReadLatestDataUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("PhysicsWorld", "bool ReadLatestDataUpdate(Deserializer&)", asMETHODPR(PhysicsWorld, ReadLatestDataUpdate, (Deserializer&), bool), asCALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("PhysicsWorld", "int Refs() const", asMETHODPR(PhysicsWorld, Refs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("PhysicsWorld", "int get_refs() const", asMETHODPR(PhysicsWorld, Refs, () const, int), asCALL_THISCALL);
    // static void PhysicsWorld::RegisterObject(Context* context) | File: ../Physics/PhysicsWorld.h
    // Not registered because have @nobind mark
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("PhysicsWorld", asBEHAVE_RELEASE, "void f()", asMETHODPR(PhysicsWorld, ReleaseRef, (), void), asCALL_THISCALL);
    // void Component::Remove() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("PhysicsWorld", "void Remove()", asMETHODPR(PhysicsWorld, Remove, (), void), asCALL_THISCALL);
    // void Animatable::RemoveAttributeAnimation(const String& name) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("PhysicsWorld", "void RemoveAttributeAnimation(const String&in)", asMETHODPR(PhysicsWorld, RemoveAttributeAnimation, (const String&), void), asCALL_THISCALL);
    // void PhysicsWorld::RemoveCachedGeometry(Model* model) | File: ../Physics/PhysicsWorld.h
    engine->RegisterObjectMethod("PhysicsWorld", "void RemoveCachedGeometry(Model@+)", asMETHODPR(PhysicsWorld, RemoveCachedGeometry, (Model*), void), asCALL_THISCALL);
    // void PhysicsWorld::RemoveCollisionShape(CollisionShape* shape) | File: ../Physics/PhysicsWorld.h
    engine->RegisterObjectMethod("PhysicsWorld", "void RemoveCollisionShape(CollisionShape@+)", asMETHODPR(PhysicsWorld, RemoveCollisionShape, (CollisionShape*), void), asCALL_THISCALL);
    // void PhysicsWorld::RemoveConstraint(Constraint* constraint) | File: ../Physics/PhysicsWorld.h
    engine->RegisterObjectMethod("PhysicsWorld", "void RemoveConstraint(Constraint@+)", asMETHODPR(PhysicsWorld, RemoveConstraint, (Constraint*), void), asCALL_THISCALL);
    // void Serializable::RemoveInstanceDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("PhysicsWorld", "void RemoveInstanceDefault()", asMETHODPR(PhysicsWorld, RemoveInstanceDefault, (), void), asCALL_THISCALL);
    // void Animatable::RemoveObjectAnimation() | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("PhysicsWorld", "void RemoveObjectAnimation()", asMETHODPR(PhysicsWorld, RemoveObjectAnimation, (), void), asCALL_THISCALL);
    // void PhysicsWorld::RemoveRigidBody(RigidBody* body) | File: ../Physics/PhysicsWorld.h
    engine->RegisterObjectMethod("PhysicsWorld", "void RemoveRigidBody(RigidBody@+)", asMETHODPR(PhysicsWorld, RemoveRigidBody, (RigidBody*), void), asCALL_THISCALL);
    // void PhysicsWorld::reportErrorWarning(const char* warningString) override | File: ../Physics/PhysicsWorld.h
    // Error: type "const char*" can not automatically bind
    // void Serializable::ResetToDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("PhysicsWorld", "void ResetToDefault()", asMETHODPR(PhysicsWorld, ResetToDefault, (), void), asCALL_THISCALL);
    // bool Component::Save(Serializer& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("PhysicsWorld", "bool Save(Serializer&) const", asMETHODPR(PhysicsWorld, Save, (Serializer&) const, bool), asCALL_THISCALL);
    // virtual bool Serializable::SaveDefaultAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("PhysicsWorld", "bool SaveDefaultAttributes() const", asMETHODPR(PhysicsWorld, SaveDefaultAttributes, () const, bool), asCALL_THISCALL);
    // bool Component::SaveJSON(JSONValue& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("PhysicsWorld", "bool SaveJSON(JSONValue&) const", asMETHODPR(PhysicsWorld, SaveJSON, (JSONValue&) const, bool), asCALL_THISCALL);
    // bool Component::SaveXML(XMLElement& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("PhysicsWorld", "bool SaveXML(XMLElement&) const", asMETHODPR(PhysicsWorld, SaveXML, (XMLElement&) const, bool), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("PhysicsWorld", "void SendEvent(StringHash)", asMETHODPR(PhysicsWorld, SendEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("PhysicsWorld", "void SendEvent(StringHash, VariantMap&)", asMETHODPR(PhysicsWorld, SendEvent, (StringHash, VariantMap&), void), asCALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void Animatable::SetAnimationEnabled(bool enable) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("PhysicsWorld", "void SetAnimationEnabled(bool)", asMETHODPR(PhysicsWorld, SetAnimationEnabled, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("PhysicsWorld", "void set_animationEnabled(bool)", asMETHODPR(PhysicsWorld, SetAnimationEnabled, (bool), void), asCALL_THISCALL);
    // void Animatable::SetAnimationTime(float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("PhysicsWorld", "void SetAnimationTime(float)", asMETHODPR(PhysicsWorld, SetAnimationTime, (float), void), asCALL_THISCALL);
    // void PhysicsWorld::SetApplyingTransforms(bool enable) | File: ../Physics/PhysicsWorld.h
    engine->RegisterObjectMethod("PhysicsWorld", "void SetApplyingTransforms(bool)", asMETHODPR(PhysicsWorld, SetApplyingTransforms, (bool), void), asCALL_THISCALL);
    // bool Serializable::SetAttribute(unsigned index, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("PhysicsWorld", "bool SetAttribute(uint, const Variant&in)", asMETHODPR(PhysicsWorld, SetAttribute, (unsigned, const Variant&), bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("PhysicsWorld", "bool set_attributes(uint, const Variant&in)", asMETHODPR(PhysicsWorld, SetAttribute, (unsigned, const Variant&), bool), asCALL_THISCALL);
    // bool Serializable::SetAttribute(const String& name, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("PhysicsWorld", "bool SetAttribute(const String&in, const Variant&in)", asMETHODPR(PhysicsWorld, SetAttribute, (const String&, const Variant&), bool), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimation(const String& name, ValueAnimation* attributeAnimation, WrapMode wrapMode=WM_LOOP, float speed=1.0f) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("PhysicsWorld", "void SetAttributeAnimation(const String&in, ValueAnimation@+, WrapMode = WM_LOOP, float = 1.0f)", asMETHODPR(PhysicsWorld, SetAttributeAnimation, (const String&, ValueAnimation*, WrapMode, float), void), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimationSpeed(const String& name, float speed) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("PhysicsWorld", "void SetAttributeAnimationSpeed(const String&in, float)", asMETHODPR(PhysicsWorld, SetAttributeAnimationSpeed, (const String&, float), void), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimationTime(const String& name, float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("PhysicsWorld", "void SetAttributeAnimationTime(const String&in, float)", asMETHODPR(PhysicsWorld, SetAttributeAnimationTime, (const String&, float), void), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimationWrapMode(const String& name, WrapMode wrapMode) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("PhysicsWorld", "void SetAttributeAnimationWrapMode(const String&in, WrapMode)", asMETHODPR(PhysicsWorld, SetAttributeAnimationWrapMode, (const String&, WrapMode), void), asCALL_THISCALL);
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("PhysicsWorld", "void SetBlockEvents(bool)", asMETHODPR(PhysicsWorld, SetBlockEvents, (bool), void), asCALL_THISCALL);
    // void PhysicsWorld::SetDebugDepthTest(bool enable) | File: ../Physics/PhysicsWorld.h
    engine->RegisterObjectMethod("PhysicsWorld", "void SetDebugDepthTest(bool)", asMETHODPR(PhysicsWorld, SetDebugDepthTest, (bool), void), asCALL_THISCALL);
    // void PhysicsWorld::setDebugMode(int debugMode) override | File: ../Physics/PhysicsWorld.h
    engine->RegisterObjectMethod("PhysicsWorld", "void setDebugMode(int)", asMETHODPR(PhysicsWorld, setDebugMode, (int), void), asCALL_THISCALL);
    // void PhysicsWorld::SetDebugRenderer(DebugRenderer* debug) | File: ../Physics/PhysicsWorld.h
    engine->RegisterObjectMethod("PhysicsWorld", "void SetDebugRenderer(DebugRenderer@+)", asMETHODPR(PhysicsWorld, SetDebugRenderer, (DebugRenderer*), void), asCALL_THISCALL);
    // void Component::SetEnabled(bool enable) | File: ../Scene/Component.h
    engine->RegisterObjectMethod("PhysicsWorld", "void SetEnabled(bool)", asMETHODPR(PhysicsWorld, SetEnabled, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("PhysicsWorld", "void set_enabled(bool)", asMETHODPR(PhysicsWorld, SetEnabled, (bool), void), asCALL_THISCALL);
    // void PhysicsWorld::SetFps(int fps) | File: ../Physics/PhysicsWorld.h
    engine->RegisterObjectMethod("PhysicsWorld", "void SetFps(int)", asMETHODPR(PhysicsWorld, SetFps, (int), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("PhysicsWorld", "void set_fps(int)", asMETHODPR(PhysicsWorld, SetFps, (int), void), asCALL_THISCALL);
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("PhysicsWorld", "void SetGlobalVar(StringHash, const Variant&in)", asMETHODPR(PhysicsWorld, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("PhysicsWorld", "void set_globalVar(StringHash, const Variant&in)", asMETHODPR(PhysicsWorld, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    // void PhysicsWorld::SetGravity(const Vector3& gravity) | File: ../Physics/PhysicsWorld.h
    engine->RegisterObjectMethod("PhysicsWorld", "void SetGravity(const Vector3&in)", asMETHODPR(PhysicsWorld, SetGravity, (const Vector3&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("PhysicsWorld", "void set_gravity(const Vector3&in)", asMETHODPR(PhysicsWorld, SetGravity, (const Vector3&), void), asCALL_THISCALL);
    // void Serializable::SetInstanceDefault(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("PhysicsWorld", "void SetInstanceDefault(bool)", asMETHODPR(PhysicsWorld, SetInstanceDefault, (bool), void), asCALL_THISCALL);
    // void Serializable::SetInterceptNetworkUpdate(const String& attributeName, bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("PhysicsWorld", "void SetInterceptNetworkUpdate(const String&in, bool)", asMETHODPR(PhysicsWorld, SetInterceptNetworkUpdate, (const String&, bool), void), asCALL_THISCALL);
    // void PhysicsWorld::SetInternalEdge(bool enable) | File: ../Physics/PhysicsWorld.h
    engine->RegisterObjectMethod("PhysicsWorld", "void SetInternalEdge(bool)", asMETHODPR(PhysicsWorld, SetInternalEdge, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("PhysicsWorld", "void set_internalEdge(bool)", asMETHODPR(PhysicsWorld, SetInternalEdge, (bool), void), asCALL_THISCALL);
    // void PhysicsWorld::SetInterpolation(bool enable) | File: ../Physics/PhysicsWorld.h
    engine->RegisterObjectMethod("PhysicsWorld", "void SetInterpolation(bool)", asMETHODPR(PhysicsWorld, SetInterpolation, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("PhysicsWorld", "void set_interpolation(bool)", asMETHODPR(PhysicsWorld, SetInterpolation, (bool), void), asCALL_THISCALL);
    // void PhysicsWorld::SetMaxNetworkAngularVelocity(float velocity) | File: ../Physics/PhysicsWorld.h
    engine->RegisterObjectMethod("PhysicsWorld", "void SetMaxNetworkAngularVelocity(float)", asMETHODPR(PhysicsWorld, SetMaxNetworkAngularVelocity, (float), void), asCALL_THISCALL);
    // void PhysicsWorld::SetMaxSubSteps(int num) | File: ../Physics/PhysicsWorld.h
    engine->RegisterObjectMethod("PhysicsWorld", "void SetMaxSubSteps(int)", asMETHODPR(PhysicsWorld, SetMaxSubSteps, (int), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("PhysicsWorld", "void set_maxSubSteps(int)", asMETHODPR(PhysicsWorld, SetMaxSubSteps, (int), void), asCALL_THISCALL);
    // void PhysicsWorld::SetNumIterations(int num) | File: ../Physics/PhysicsWorld.h
    engine->RegisterObjectMethod("PhysicsWorld", "void SetNumIterations(int)", asMETHODPR(PhysicsWorld, SetNumIterations, (int), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("PhysicsWorld", "void set_numIterations(int)", asMETHODPR(PhysicsWorld, SetNumIterations, (int), void), asCALL_THISCALL);
    // void Animatable::SetObjectAnimation(ObjectAnimation* objectAnimation) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("PhysicsWorld", "void SetObjectAnimation(ObjectAnimation@+)", asMETHODPR(PhysicsWorld, SetObjectAnimation, (ObjectAnimation*), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("PhysicsWorld", "void set_objectAnimation(ObjectAnimation@+)", asMETHODPR(PhysicsWorld, SetObjectAnimation, (ObjectAnimation*), void), asCALL_THISCALL);
    // void Animatable::SetObjectAnimationAttr(const ResourceRef& value) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("PhysicsWorld", "void SetObjectAnimationAttr(const ResourceRef&in)", asMETHODPR(PhysicsWorld, SetObjectAnimationAttr, (const ResourceRef&), void), asCALL_THISCALL);
    // void PhysicsWorld::SetSplitImpulse(bool enable) | File: ../Physics/PhysicsWorld.h
    engine->RegisterObjectMethod("PhysicsWorld", "void SetSplitImpulse(bool)", asMETHODPR(PhysicsWorld, SetSplitImpulse, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("PhysicsWorld", "void set_splitImpulse(bool)", asMETHODPR(PhysicsWorld, SetSplitImpulse, (bool), void), asCALL_THISCALL);
    // void Serializable::SetTemporary(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("PhysicsWorld", "void SetTemporary(bool)", asMETHODPR(PhysicsWorld, SetTemporary, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("PhysicsWorld", "void set_temporary(bool)", asMETHODPR(PhysicsWorld, SetTemporary, (bool), void), asCALL_THISCALL);
    // void PhysicsWorld::SetUpdateEnabled(bool enable) | File: ../Physics/PhysicsWorld.h
    engine->RegisterObjectMethod("PhysicsWorld", "void SetUpdateEnabled(bool)", asMETHODPR(PhysicsWorld, SetUpdateEnabled, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("PhysicsWorld", "void set_updateEnabled(bool)", asMETHODPR(PhysicsWorld, SetUpdateEnabled, (bool), void), asCALL_THISCALL);
    // void PhysicsWorld::SphereCast(PhysicsRaycastResult& result, const Ray& ray, float radius, float maxDistance, unsigned collisionMask=M_MAX_UNSIGNED) | File: ../Physics/PhysicsWorld.h
    engine->RegisterObjectMethod("PhysicsWorld", "void SphereCast(PhysicsRaycastResult&, const Ray&in, float, float, uint = M_MAX_UNSIGNED)", asMETHODPR(PhysicsWorld, SphereCast, (PhysicsRaycastResult&, const Ray&, float, float, unsigned), void), asCALL_THISCALL);
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod("PhysicsWorld", "void UnsubscribeFromAllEvents()", asMETHODPR(PhysicsWorld, UnsubscribeFromAllEvents, (), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("PhysicsWorld", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", asFUNCTION(PhysicsWorld_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), asCALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("PhysicsWorld", "void UnsubscribeFromEvent(StringHash)", asMETHODPR(PhysicsWorld, UnsubscribeFromEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("PhysicsWorld", "void UnsubscribeFromEvent(Object@+, StringHash)", asMETHODPR(PhysicsWorld, UnsubscribeFromEvent, (Object*, StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("PhysicsWorld", "void UnsubscribeFromEvents(Object@+)", asMETHODPR(PhysicsWorld, UnsubscribeFromEvents, (Object*), void), asCALL_THISCALL);
    // void PhysicsWorld::Update(float timeStep) | File: ../Physics/PhysicsWorld.h
    engine->RegisterObjectMethod("PhysicsWorld", "void Update(float)", asMETHODPR(PhysicsWorld, Update, (float), void), asCALL_THISCALL);
    // void PhysicsWorld::UpdateCollisions() | File: ../Physics/PhysicsWorld.h
    engine->RegisterObjectMethod("PhysicsWorld", "void UpdateCollisions()", asMETHODPR(PhysicsWorld, UpdateCollisions, (), void), asCALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("PhysicsWorld", "int WeakRefs() const", asMETHODPR(PhysicsWorld, WeakRefs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("PhysicsWorld", "int get_weakRefs() const", asMETHODPR(PhysicsWorld, WeakRefs, () const, int), asCALL_THISCALL);
    // void Serializable::WriteDeltaUpdate(Serializer& dest, const DirtyBits& attributeBits, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("PhysicsWorld", "void WriteDeltaUpdate(Serializer&, const DirtyBits&in, uint8)", asMETHODPR(PhysicsWorld, WriteDeltaUpdate, (Serializer&, const DirtyBits&, unsigned char), void), asCALL_THISCALL);
    // void Serializable::WriteInitialDeltaUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("PhysicsWorld", "void WriteInitialDeltaUpdate(Serializer&, uint8)", asMETHODPR(PhysicsWorld, WriteInitialDeltaUpdate, (Serializer&, unsigned char), void), asCALL_THISCALL);
    // void Serializable::WriteLatestDataUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("PhysicsWorld", "void WriteLatestDataUpdate(Serializer&, uint8)", asMETHODPR(PhysicsWorld, WriteLatestDataUpdate, (Serializer&, unsigned char), void), asCALL_THISCALL);
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
    engine->RegisterObjectMethod("PhysicsWorld2D", "void AddDelayedWorldTransform(const DelayedWorldTransform2D&in)", asMETHODPR(PhysicsWorld2D, AddDelayedWorldTransform, (const DelayedWorldTransform2D&), void), asCALL_THISCALL);
    // void RefCounted::AddRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("PhysicsWorld2D", asBEHAVE_ADDREF, "void f()", asMETHODPR(PhysicsWorld2D, AddRef, (), void), asCALL_THISCALL);
    // void Component::AddReplicationState(ComponentReplicationState* state) | File: ../Scene/Component.h
    // Error: type "ComponentReplicationState*" can not automatically bind
    // void PhysicsWorld2D::AddRigidBody(RigidBody2D* rigidBody) | File: ../Urho2D/PhysicsWorld2D.h
    engine->RegisterObjectMethod("PhysicsWorld2D", "void AddRigidBody(RigidBody2D@+)", asMETHODPR(PhysicsWorld2D, AddRigidBody, (RigidBody2D*), void), asCALL_THISCALL);
    // void Serializable::AllocateNetworkState() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("PhysicsWorld2D", "void AllocateNetworkState()", asMETHODPR(PhysicsWorld2D, AllocateNetworkState, (), void), asCALL_THISCALL);
    // virtual void Serializable::ApplyAttributes() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("PhysicsWorld2D", "void ApplyAttributes()", asMETHODPR(PhysicsWorld2D, ApplyAttributes, (), void), asCALL_THISCALL);
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
    engine->RegisterObjectMethod("PhysicsWorld2D", "void DrawDebugGeometry(DebugRenderer@+, bool)", asMETHODPR(PhysicsWorld2D, DrawDebugGeometry, (DebugRenderer*, bool), void), asCALL_THISCALL);
    // void PhysicsWorld2D::DrawDebugGeometry() | File: ../Urho2D/PhysicsWorld2D.h
    engine->RegisterObjectMethod("PhysicsWorld2D", "void DrawDebugGeometry()", asMETHODPR(PhysicsWorld2D, DrawDebugGeometry, (), void), asCALL_THISCALL);
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
    engine->RegisterObjectMethod("PhysicsWorld2D", "bool GetAllowSleeping() const", asMETHODPR(PhysicsWorld2D, GetAllowSleeping, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("PhysicsWorld2D", "bool get_allowSleeping() const", asMETHODPR(PhysicsWorld2D, GetAllowSleeping, () const, bool), asCALL_THISCALL);
    // bool Animatable::GetAnimationEnabled() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("PhysicsWorld2D", "bool GetAnimationEnabled() const", asMETHODPR(PhysicsWorld2D, GetAnimationEnabled, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("PhysicsWorld2D", "bool get_animationEnabled() const", asMETHODPR(PhysicsWorld2D, GetAnimationEnabled, () const, bool), asCALL_THISCALL);
    // Variant Serializable::GetAttribute(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("PhysicsWorld2D", "Variant GetAttribute(uint) const", asMETHODPR(PhysicsWorld2D, GetAttribute, (unsigned) const, Variant), asCALL_THISCALL);
    engine->RegisterObjectMethod("PhysicsWorld2D", "Variant get_attributes(uint) const", asMETHODPR(PhysicsWorld2D, GetAttribute, (unsigned) const, Variant), asCALL_THISCALL);
    // Variant Serializable::GetAttribute(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("PhysicsWorld2D", "Variant GetAttribute(const String&in) const", asMETHODPR(PhysicsWorld2D, GetAttribute, (const String&) const, Variant), asCALL_THISCALL);
    // ValueAnimation* Animatable::GetAttributeAnimation(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("PhysicsWorld2D", "ValueAnimation@+ GetAttributeAnimation(const String&in) const", asMETHODPR(PhysicsWorld2D, GetAttributeAnimation, (const String&) const, ValueAnimation*), asCALL_THISCALL);
    // float Animatable::GetAttributeAnimationSpeed(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("PhysicsWorld2D", "float GetAttributeAnimationSpeed(const String&in) const", asMETHODPR(PhysicsWorld2D, GetAttributeAnimationSpeed, (const String&) const, float), asCALL_THISCALL);
    // float Animatable::GetAttributeAnimationTime(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("PhysicsWorld2D", "float GetAttributeAnimationTime(const String&in) const", asMETHODPR(PhysicsWorld2D, GetAttributeAnimationTime, (const String&) const, float), asCALL_THISCALL);
    // WrapMode Animatable::GetAttributeAnimationWrapMode(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("PhysicsWorld2D", "WrapMode GetAttributeAnimationWrapMode(const String&in) const", asMETHODPR(PhysicsWorld2D, GetAttributeAnimationWrapMode, (const String&) const, WrapMode), asCALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("PhysicsWorld2D", "Variant GetAttributeDefault(uint) const", asMETHODPR(PhysicsWorld2D, GetAttributeDefault, (unsigned) const, Variant), asCALL_THISCALL);
    engine->RegisterObjectMethod("PhysicsWorld2D", "Variant get_attributeDefaults(uint) const", asMETHODPR(PhysicsWorld2D, GetAttributeDefault, (unsigned) const, Variant), asCALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("PhysicsWorld2D", "Variant GetAttributeDefault(const String&in) const", asMETHODPR(PhysicsWorld2D, GetAttributeDefault, (const String&) const, Variant), asCALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // bool PhysicsWorld2D::GetAutoClearForces() const | File: ../Urho2D/PhysicsWorld2D.h
    engine->RegisterObjectMethod("PhysicsWorld2D", "bool GetAutoClearForces() const", asMETHODPR(PhysicsWorld2D, GetAutoClearForces, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("PhysicsWorld2D", "bool get_autoClearForces() const", asMETHODPR(PhysicsWorld2D, GetAutoClearForces, () const, bool), asCALL_THISCALL);
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("PhysicsWorld2D", "bool GetBlockEvents() const", asMETHODPR(PhysicsWorld2D, GetBlockEvents, () const, bool), asCALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("PhysicsWorld2D", "const String& GetCategory() const", asMETHODPR(PhysicsWorld2D, GetCategory, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("PhysicsWorld2D", "const String& get_category() const", asMETHODPR(PhysicsWorld2D, GetCategory, () const, const String&), asCALL_THISCALL);
    // Component* Component::GetComponent(StringHash type) const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("PhysicsWorld2D", "Component@+ GetComponent(StringHash) const", asMETHODPR(PhysicsWorld2D, GetComponent, (StringHash) const, Component*), asCALL_THISCALL);
    // template<class T> T*  Component::GetComponent() const | File: ../Scene/Component.h
    // Not registered because template
    // void Component::GetComponents(PODVector<Component*>& dest, StringHash type) const | File: ../Scene/Component.h
    // Error: type "PODVector<Component*>&" can not automatically bind
    // template<class T> void Component::GetComponents(PODVector<T*>& dest) const | File: ../Scene/Component.h
    // Not registered because template
    // Context* Object::GetContext() const | File: ../Core/Object.h
    // Error: type "Context*" can used only as function parameter
    // bool PhysicsWorld2D::GetContinuousPhysics() const | File: ../Urho2D/PhysicsWorld2D.h
    engine->RegisterObjectMethod("PhysicsWorld2D", "bool GetContinuousPhysics() const", asMETHODPR(PhysicsWorld2D, GetContinuousPhysics, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("PhysicsWorld2D", "bool get_continuousPhysics() const", asMETHODPR(PhysicsWorld2D, GetContinuousPhysics, () const, bool), asCALL_THISCALL);
    // virtual void Component::GetDependencyNodes(PODVector<Node*>& dest) | File: ../Scene/Component.h
    // Error: type "PODVector<Node*>&" can not automatically bind
    // bool PhysicsWorld2D::GetDrawAabb() const | File: ../Urho2D/PhysicsWorld2D.h
    engine->RegisterObjectMethod("PhysicsWorld2D", "bool GetDrawAabb() const", asMETHODPR(PhysicsWorld2D, GetDrawAabb, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("PhysicsWorld2D", "bool get_drawAabb() const", asMETHODPR(PhysicsWorld2D, GetDrawAabb, () const, bool), asCALL_THISCALL);
    // bool PhysicsWorld2D::GetDrawCenterOfMass() const | File: ../Urho2D/PhysicsWorld2D.h
    engine->RegisterObjectMethod("PhysicsWorld2D", "bool GetDrawCenterOfMass() const", asMETHODPR(PhysicsWorld2D, GetDrawCenterOfMass, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("PhysicsWorld2D", "bool get_drawCenterOfMass() const", asMETHODPR(PhysicsWorld2D, GetDrawCenterOfMass, () const, bool), asCALL_THISCALL);
    // bool PhysicsWorld2D::GetDrawJoint() const | File: ../Urho2D/PhysicsWorld2D.h
    engine->RegisterObjectMethod("PhysicsWorld2D", "bool GetDrawJoint() const", asMETHODPR(PhysicsWorld2D, GetDrawJoint, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("PhysicsWorld2D", "bool get_drawJoint() const", asMETHODPR(PhysicsWorld2D, GetDrawJoint, () const, bool), asCALL_THISCALL);
    // bool PhysicsWorld2D::GetDrawPair() const | File: ../Urho2D/PhysicsWorld2D.h
    engine->RegisterObjectMethod("PhysicsWorld2D", "bool GetDrawPair() const", asMETHODPR(PhysicsWorld2D, GetDrawPair, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("PhysicsWorld2D", "bool get_drawPair() const", asMETHODPR(PhysicsWorld2D, GetDrawPair, () const, bool), asCALL_THISCALL);
    // bool PhysicsWorld2D::GetDrawShape() const | File: ../Urho2D/PhysicsWorld2D.h
    engine->RegisterObjectMethod("PhysicsWorld2D", "bool GetDrawShape() const", asMETHODPR(PhysicsWorld2D, GetDrawShape, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("PhysicsWorld2D", "bool get_drawShape() const", asMETHODPR(PhysicsWorld2D, GetDrawShape, () const, bool), asCALL_THISCALL);
    // VariantMap& Object::GetEventDataMap() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("PhysicsWorld2D", "VariantMap& GetEventDataMap() const", asMETHODPR(PhysicsWorld2D, GetEventDataMap, () const, VariantMap&), asCALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("PhysicsWorld2D", "Object@+ GetEventSender() const", asMETHODPR(PhysicsWorld2D, GetEventSender, () const, Object*), asCALL_THISCALL);
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("PhysicsWorld2D", "const Variant& GetGlobalVar(StringHash) const", asMETHODPR(PhysicsWorld2D, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    engine->RegisterObjectMethod("PhysicsWorld2D", "const Variant& get_globalVar(StringHash) const", asMETHODPR(PhysicsWorld2D, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("PhysicsWorld2D", "const VariantMap& GetGlobalVars() const", asMETHODPR(PhysicsWorld2D, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    engine->RegisterObjectMethod("PhysicsWorld2D", "const VariantMap& get_globalVars() const", asMETHODPR(PhysicsWorld2D, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    // const Vector2& PhysicsWorld2D::GetGravity() const | File: ../Urho2D/PhysicsWorld2D.h
    engine->RegisterObjectMethod("PhysicsWorld2D", "const Vector2& GetGravity() const", asMETHODPR(PhysicsWorld2D, GetGravity, () const, const Vector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("PhysicsWorld2D", "const Vector2& get_gravity() const", asMETHODPR(PhysicsWorld2D, GetGravity, () const, const Vector2&), asCALL_THISCALL);
    // unsigned Component::GetID() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("PhysicsWorld2D", "uint GetID() const", asMETHODPR(PhysicsWorld2D, GetID, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("PhysicsWorld2D", "uint get_id() const", asMETHODPR(PhysicsWorld2D, GetID, () const, unsigned), asCALL_THISCALL);
    // bool Serializable::GetInterceptNetworkUpdate(const String& attributeName) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("PhysicsWorld2D", "bool GetInterceptNetworkUpdate(const String&in) const", asMETHODPR(PhysicsWorld2D, GetInterceptNetworkUpdate, (const String&) const, bool), asCALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetNetworkAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // NetworkState* Serializable::GetNetworkState() const | File: ../Scene/Serializable.h
    // Error: type "NetworkState*" can not automatically bind
    // Node* Component::GetNode() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("PhysicsWorld2D", "Node@+ GetNode() const", asMETHODPR(PhysicsWorld2D, GetNode, () const, Node*), asCALL_THISCALL);
    engine->RegisterObjectMethod("PhysicsWorld2D", "Node@+ get_node() const", asMETHODPR(PhysicsWorld2D, GetNode, () const, Node*), asCALL_THISCALL);
    // unsigned Serializable::GetNumAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("PhysicsWorld2D", "uint GetNumAttributes() const", asMETHODPR(PhysicsWorld2D, GetNumAttributes, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("PhysicsWorld2D", "uint get_numAttributes() const", asMETHODPR(PhysicsWorld2D, GetNumAttributes, () const, unsigned), asCALL_THISCALL);
    // unsigned Serializable::GetNumNetworkAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("PhysicsWorld2D", "uint GetNumNetworkAttributes() const", asMETHODPR(PhysicsWorld2D, GetNumNetworkAttributes, () const, unsigned), asCALL_THISCALL);
    // ObjectAnimation* Animatable::GetObjectAnimation() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("PhysicsWorld2D", "ObjectAnimation@+ GetObjectAnimation() const", asMETHODPR(PhysicsWorld2D, GetObjectAnimation, () const, ObjectAnimation*), asCALL_THISCALL);
    engine->RegisterObjectMethod("PhysicsWorld2D", "ObjectAnimation@+ get_objectAnimation() const", asMETHODPR(PhysicsWorld2D, GetObjectAnimation, () const, ObjectAnimation*), asCALL_THISCALL);
    // ResourceRef Animatable::GetObjectAnimationAttr() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("PhysicsWorld2D", "ResourceRef GetObjectAnimationAttr() const", asMETHODPR(PhysicsWorld2D, GetObjectAnimationAttr, () const, ResourceRef), asCALL_THISCALL);
    // int PhysicsWorld2D::GetPositionIterations() const | File: ../Urho2D/PhysicsWorld2D.h
    engine->RegisterObjectMethod("PhysicsWorld2D", "int GetPositionIterations() const", asMETHODPR(PhysicsWorld2D, GetPositionIterations, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("PhysicsWorld2D", "int get_positionIterations() const", asMETHODPR(PhysicsWorld2D, GetPositionIterations, () const, int), asCALL_THISCALL);
    // void PhysicsWorld2D::GetRigidBodies(PODVector<RigidBody2D*>& results, const Rect& aabb, unsigned collisionMask=M_MAX_UNSIGNED) | File: ../Urho2D/PhysicsWorld2D.h
    // Error: type "PODVector<RigidBody2D*>&" can not automatically bind
    // RigidBody2D* PhysicsWorld2D::GetRigidBody(const Vector2& point, unsigned collisionMask=M_MAX_UNSIGNED) | File: ../Urho2D/PhysicsWorld2D.h
    engine->RegisterObjectMethod("PhysicsWorld2D", "RigidBody2D@+ GetRigidBody(const Vector2&in, uint = M_MAX_UNSIGNED)", asMETHODPR(PhysicsWorld2D, GetRigidBody, (const Vector2&, unsigned), RigidBody2D*), asCALL_THISCALL);
    // RigidBody2D* PhysicsWorld2D::GetRigidBody(int screenX, int screenY, unsigned collisionMask=M_MAX_UNSIGNED) | File: ../Urho2D/PhysicsWorld2D.h
    engine->RegisterObjectMethod("PhysicsWorld2D", "RigidBody2D@+ GetRigidBody(int, int, uint = M_MAX_UNSIGNED)", asMETHODPR(PhysicsWorld2D, GetRigidBody, (int, int, unsigned), RigidBody2D*), asCALL_THISCALL);
    // Scene* Component::GetScene() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("PhysicsWorld2D", "Scene@+ GetScene() const", asMETHODPR(PhysicsWorld2D, GetScene, () const, Scene*), asCALL_THISCALL);
    // bool PhysicsWorld2D::GetSubStepping() const | File: ../Urho2D/PhysicsWorld2D.h
    engine->RegisterObjectMethod("PhysicsWorld2D", "bool GetSubStepping() const", asMETHODPR(PhysicsWorld2D, GetSubStepping, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("PhysicsWorld2D", "bool get_subStepping() const", asMETHODPR(PhysicsWorld2D, GetSubStepping, () const, bool), asCALL_THISCALL);
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("PhysicsWorld2D", "Object@+ GetSubsystem(StringHash) const", asMETHODPR(PhysicsWorld2D, GetSubsystem, (StringHash) const, Object*), asCALL_THISCALL);
    // template<class T> T*  Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("PhysicsWorld2D", "StringHash GetType() const", asMETHODPR(PhysicsWorld2D, GetType, () const, StringHash), asCALL_THISCALL);
    engine->RegisterObjectMethod("PhysicsWorld2D", "StringHash get_type() const", asMETHODPR(PhysicsWorld2D, GetType, () const, StringHash), asCALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("PhysicsWorld2D", "const String& GetTypeName() const", asMETHODPR(PhysicsWorld2D, GetTypeName, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("PhysicsWorld2D", "const String& get_typeName() const", asMETHODPR(PhysicsWorld2D, GetTypeName, () const, const String&), asCALL_THISCALL);
    // int PhysicsWorld2D::GetVelocityIterations() const | File: ../Urho2D/PhysicsWorld2D.h
    engine->RegisterObjectMethod("PhysicsWorld2D", "int GetVelocityIterations() const", asMETHODPR(PhysicsWorld2D, GetVelocityIterations, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("PhysicsWorld2D", "int get_velocityIterations() const", asMETHODPR(PhysicsWorld2D, GetVelocityIterations, () const, int), asCALL_THISCALL);
    // bool PhysicsWorld2D::GetWarmStarting() const | File: ../Urho2D/PhysicsWorld2D.h
    engine->RegisterObjectMethod("PhysicsWorld2D", "bool GetWarmStarting() const", asMETHODPR(PhysicsWorld2D, GetWarmStarting, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("PhysicsWorld2D", "bool get_warmStarting() const", asMETHODPR(PhysicsWorld2D, GetWarmStarting, () const, bool), asCALL_THISCALL);
    // b2World* PhysicsWorld2D::GetWorld() | File: ../Urho2D/PhysicsWorld2D.h
    // Error: type "b2World*" can not automatically bind
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("PhysicsWorld2D", "bool HasEventHandlers() const", asMETHODPR(PhysicsWorld2D, HasEventHandlers, () const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("PhysicsWorld2D", "bool HasSubscribedToEvent(StringHash) const", asMETHODPR(PhysicsWorld2D, HasSubscribedToEvent, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("PhysicsWorld2D", "bool HasSubscribedToEvent(Object@+, StringHash) const", asMETHODPR(PhysicsWorld2D, HasSubscribedToEvent, (Object*, StringHash) const, bool), asCALL_THISCALL);
    // bool PhysicsWorld2D::IsApplyingTransforms() const | File: ../Urho2D/PhysicsWorld2D.h
    engine->RegisterObjectMethod("PhysicsWorld2D", "bool IsApplyingTransforms() const", asMETHODPR(PhysicsWorld2D, IsApplyingTransforms, () const, bool), asCALL_THISCALL);
    // bool Component::IsEnabled() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("PhysicsWorld2D", "bool IsEnabled() const", asMETHODPR(PhysicsWorld2D, IsEnabled, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("PhysicsWorld2D", "bool get_enabled() const", asMETHODPR(PhysicsWorld2D, IsEnabled, () const, bool), asCALL_THISCALL);
    // bool Component::IsEnabledEffective() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("PhysicsWorld2D", "bool IsEnabledEffective() const", asMETHODPR(PhysicsWorld2D, IsEnabledEffective, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("PhysicsWorld2D", "bool get_enabledEffective() const", asMETHODPR(PhysicsWorld2D, IsEnabledEffective, () const, bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("PhysicsWorld2D", "bool IsInstanceOf(StringHash) const", asMETHODPR(PhysicsWorld2D, IsInstanceOf, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // bool Component::IsReplicated() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("PhysicsWorld2D", "bool IsReplicated() const", asMETHODPR(PhysicsWorld2D, IsReplicated, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("PhysicsWorld2D", "bool get_replicated() const", asMETHODPR(PhysicsWorld2D, IsReplicated, () const, bool), asCALL_THISCALL);
    // bool Serializable::IsTemporary() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("PhysicsWorld2D", "bool IsTemporary() const", asMETHODPR(PhysicsWorld2D, IsTemporary, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("PhysicsWorld2D", "bool get_temporary() const", asMETHODPR(PhysicsWorld2D, IsTemporary, () const, bool), asCALL_THISCALL);
    // bool PhysicsWorld2D::IsUpdateEnabled() const | File: ../Urho2D/PhysicsWorld2D.h
    engine->RegisterObjectMethod("PhysicsWorld2D", "bool IsUpdateEnabled() const", asMETHODPR(PhysicsWorld2D, IsUpdateEnabled, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("PhysicsWorld2D", "bool get_updateEnabled() const", asMETHODPR(PhysicsWorld2D, IsUpdateEnabled, () const, bool), asCALL_THISCALL);
    // virtual bool Serializable::Load(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("PhysicsWorld2D", "bool Load(Deserializer&)", asMETHODPR(PhysicsWorld2D, Load, (Deserializer&), bool), asCALL_THISCALL);
    // bool Animatable::LoadJSON(const JSONValue& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("PhysicsWorld2D", "bool LoadJSON(const JSONValue&in)", asMETHODPR(PhysicsWorld2D, LoadJSON, (const JSONValue&), bool), asCALL_THISCALL);
    // bool Animatable::LoadXML(const XMLElement& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("PhysicsWorld2D", "bool LoadXML(const XMLElement&in)", asMETHODPR(PhysicsWorld2D, LoadXML, (const XMLElement&), bool), asCALL_THISCALL);
    // void Component::MarkNetworkUpdate() override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("PhysicsWorld2D", "void MarkNetworkUpdate()", asMETHODPR(PhysicsWorld2D, MarkNetworkUpdate, (), void), asCALL_THISCALL);
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("PhysicsWorld2D", "void OnEvent(Object@+, StringHash, VariantMap&)", asMETHODPR(PhysicsWorld2D, OnEvent, (Object*, StringHash, VariantMap&), void), asCALL_THISCALL);
    // virtual void Serializable::OnGetAttribute(const AttributeInfo& attr, Variant& dest) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("PhysicsWorld2D", "void OnGetAttribute(const AttributeInfo&in, Variant&) const", asMETHODPR(PhysicsWorld2D, OnGetAttribute, (const AttributeInfo&, Variant&) const, void), asCALL_THISCALL);
    // virtual void Serializable::OnSetAttribute(const AttributeInfo& attr, const Variant& src) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("PhysicsWorld2D", "void OnSetAttribute(const AttributeInfo&in, const Variant&in)", asMETHODPR(PhysicsWorld2D, OnSetAttribute, (const AttributeInfo&, const Variant&), void), asCALL_THISCALL);
    // virtual void Component::OnSetEnabled() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("PhysicsWorld2D", "void OnSetEnabled()", asMETHODPR(PhysicsWorld2D, OnSetEnabled, (), void), asCALL_THISCALL);
    // explicit PhysicsWorld2D::PhysicsWorld2D(Context* context) | File: ../Urho2D/PhysicsWorld2D.h
    engine->RegisterObjectBehaviour("PhysicsWorld2D", asBEHAVE_FACTORY, "PhysicsWorld2D@+ f()", asFUNCTION(PhysicsWorld2D_PhysicsWorld2D_Context), asCALL_CDECL);
    // void Component::PrepareNetworkUpdate() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("PhysicsWorld2D", "void PrepareNetworkUpdate()", asMETHODPR(PhysicsWorld2D, PrepareNetworkUpdate, (), void), asCALL_THISCALL);
    // void PhysicsWorld2D::PreSolve(b2Contact* contact, const b2Manifold* oldManifold) override | File: ../Urho2D/PhysicsWorld2D.h
    // Error: type "b2Contact*" can not automatically bind
    // void PhysicsWorld2D::Raycast(PODVector<PhysicsRaycastResult2D>& results, const Vector2& startPoint, const Vector2& endPoint, unsigned collisionMask=M_MAX_UNSIGNED) | File: ../Urho2D/PhysicsWorld2D.h
    // Error: type "PODVector<PhysicsRaycastResult2D>&" can not automatically bind
    // void PhysicsWorld2D::RaycastSingle(PhysicsRaycastResult2D& result, const Vector2& startPoint, const Vector2& endPoint, unsigned collisionMask=M_MAX_UNSIGNED) | File: ../Urho2D/PhysicsWorld2D.h
    engine->RegisterObjectMethod("PhysicsWorld2D", "void RaycastSingle(PhysicsRaycastResult2D&, const Vector2&in, const Vector2&in, uint = M_MAX_UNSIGNED)", asMETHODPR(PhysicsWorld2D, RaycastSingle, (PhysicsRaycastResult2D&, const Vector2&, const Vector2&, unsigned), void), asCALL_THISCALL);
    // bool Serializable::ReadDeltaUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("PhysicsWorld2D", "bool ReadDeltaUpdate(Deserializer&)", asMETHODPR(PhysicsWorld2D, ReadDeltaUpdate, (Deserializer&), bool), asCALL_THISCALL);
    // bool Serializable::ReadLatestDataUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("PhysicsWorld2D", "bool ReadLatestDataUpdate(Deserializer&)", asMETHODPR(PhysicsWorld2D, ReadLatestDataUpdate, (Deserializer&), bool), asCALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("PhysicsWorld2D", "int Refs() const", asMETHODPR(PhysicsWorld2D, Refs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("PhysicsWorld2D", "int get_refs() const", asMETHODPR(PhysicsWorld2D, Refs, () const, int), asCALL_THISCALL);
    // static void PhysicsWorld2D::RegisterObject(Context* context) | File: ../Urho2D/PhysicsWorld2D.h
    // Not registered because have @nobind mark
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("PhysicsWorld2D", asBEHAVE_RELEASE, "void f()", asMETHODPR(PhysicsWorld2D, ReleaseRef, (), void), asCALL_THISCALL);
    // void Component::Remove() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("PhysicsWorld2D", "void Remove()", asMETHODPR(PhysicsWorld2D, Remove, (), void), asCALL_THISCALL);
    // void Animatable::RemoveAttributeAnimation(const String& name) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("PhysicsWorld2D", "void RemoveAttributeAnimation(const String&in)", asMETHODPR(PhysicsWorld2D, RemoveAttributeAnimation, (const String&), void), asCALL_THISCALL);
    // void Serializable::RemoveInstanceDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("PhysicsWorld2D", "void RemoveInstanceDefault()", asMETHODPR(PhysicsWorld2D, RemoveInstanceDefault, (), void), asCALL_THISCALL);
    // void Animatable::RemoveObjectAnimation() | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("PhysicsWorld2D", "void RemoveObjectAnimation()", asMETHODPR(PhysicsWorld2D, RemoveObjectAnimation, (), void), asCALL_THISCALL);
    // void PhysicsWorld2D::RemoveRigidBody(RigidBody2D* rigidBody) | File: ../Urho2D/PhysicsWorld2D.h
    engine->RegisterObjectMethod("PhysicsWorld2D", "void RemoveRigidBody(RigidBody2D@+)", asMETHODPR(PhysicsWorld2D, RemoveRigidBody, (RigidBody2D*), void), asCALL_THISCALL);
    // void Serializable::ResetToDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("PhysicsWorld2D", "void ResetToDefault()", asMETHODPR(PhysicsWorld2D, ResetToDefault, (), void), asCALL_THISCALL);
    // bool Component::Save(Serializer& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("PhysicsWorld2D", "bool Save(Serializer&) const", asMETHODPR(PhysicsWorld2D, Save, (Serializer&) const, bool), asCALL_THISCALL);
    // virtual bool Serializable::SaveDefaultAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("PhysicsWorld2D", "bool SaveDefaultAttributes() const", asMETHODPR(PhysicsWorld2D, SaveDefaultAttributes, () const, bool), asCALL_THISCALL);
    // bool Component::SaveJSON(JSONValue& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("PhysicsWorld2D", "bool SaveJSON(JSONValue&) const", asMETHODPR(PhysicsWorld2D, SaveJSON, (JSONValue&) const, bool), asCALL_THISCALL);
    // bool Component::SaveXML(XMLElement& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("PhysicsWorld2D", "bool SaveXML(XMLElement&) const", asMETHODPR(PhysicsWorld2D, SaveXML, (XMLElement&) const, bool), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("PhysicsWorld2D", "void SendEvent(StringHash)", asMETHODPR(PhysicsWorld2D, SendEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("PhysicsWorld2D", "void SendEvent(StringHash, VariantMap&)", asMETHODPR(PhysicsWorld2D, SendEvent, (StringHash, VariantMap&), void), asCALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void PhysicsWorld2D::SetAllowSleeping(bool enable) | File: ../Urho2D/PhysicsWorld2D.h
    engine->RegisterObjectMethod("PhysicsWorld2D", "void SetAllowSleeping(bool)", asMETHODPR(PhysicsWorld2D, SetAllowSleeping, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("PhysicsWorld2D", "void set_allowSleeping(bool)", asMETHODPR(PhysicsWorld2D, SetAllowSleeping, (bool), void), asCALL_THISCALL);
    // void Animatable::SetAnimationEnabled(bool enable) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("PhysicsWorld2D", "void SetAnimationEnabled(bool)", asMETHODPR(PhysicsWorld2D, SetAnimationEnabled, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("PhysicsWorld2D", "void set_animationEnabled(bool)", asMETHODPR(PhysicsWorld2D, SetAnimationEnabled, (bool), void), asCALL_THISCALL);
    // void Animatable::SetAnimationTime(float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("PhysicsWorld2D", "void SetAnimationTime(float)", asMETHODPR(PhysicsWorld2D, SetAnimationTime, (float), void), asCALL_THISCALL);
    // void PhysicsWorld2D::SetApplyingTransforms(bool enable) | File: ../Urho2D/PhysicsWorld2D.h
    engine->RegisterObjectMethod("PhysicsWorld2D", "void SetApplyingTransforms(bool)", asMETHODPR(PhysicsWorld2D, SetApplyingTransforms, (bool), void), asCALL_THISCALL);
    // bool Serializable::SetAttribute(unsigned index, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("PhysicsWorld2D", "bool SetAttribute(uint, const Variant&in)", asMETHODPR(PhysicsWorld2D, SetAttribute, (unsigned, const Variant&), bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("PhysicsWorld2D", "bool set_attributes(uint, const Variant&in)", asMETHODPR(PhysicsWorld2D, SetAttribute, (unsigned, const Variant&), bool), asCALL_THISCALL);
    // bool Serializable::SetAttribute(const String& name, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("PhysicsWorld2D", "bool SetAttribute(const String&in, const Variant&in)", asMETHODPR(PhysicsWorld2D, SetAttribute, (const String&, const Variant&), bool), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimation(const String& name, ValueAnimation* attributeAnimation, WrapMode wrapMode=WM_LOOP, float speed=1.0f) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("PhysicsWorld2D", "void SetAttributeAnimation(const String&in, ValueAnimation@+, WrapMode = WM_LOOP, float = 1.0f)", asMETHODPR(PhysicsWorld2D, SetAttributeAnimation, (const String&, ValueAnimation*, WrapMode, float), void), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimationSpeed(const String& name, float speed) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("PhysicsWorld2D", "void SetAttributeAnimationSpeed(const String&in, float)", asMETHODPR(PhysicsWorld2D, SetAttributeAnimationSpeed, (const String&, float), void), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimationTime(const String& name, float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("PhysicsWorld2D", "void SetAttributeAnimationTime(const String&in, float)", asMETHODPR(PhysicsWorld2D, SetAttributeAnimationTime, (const String&, float), void), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimationWrapMode(const String& name, WrapMode wrapMode) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("PhysicsWorld2D", "void SetAttributeAnimationWrapMode(const String&in, WrapMode)", asMETHODPR(PhysicsWorld2D, SetAttributeAnimationWrapMode, (const String&, WrapMode), void), asCALL_THISCALL);
    // void PhysicsWorld2D::SetAutoClearForces(bool enable) | File: ../Urho2D/PhysicsWorld2D.h
    engine->RegisterObjectMethod("PhysicsWorld2D", "void SetAutoClearForces(bool)", asMETHODPR(PhysicsWorld2D, SetAutoClearForces, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("PhysicsWorld2D", "void set_autoClearForces(bool)", asMETHODPR(PhysicsWorld2D, SetAutoClearForces, (bool), void), asCALL_THISCALL);
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("PhysicsWorld2D", "void SetBlockEvents(bool)", asMETHODPR(PhysicsWorld2D, SetBlockEvents, (bool), void), asCALL_THISCALL);
    // void PhysicsWorld2D::SetContinuousPhysics(bool enable) | File: ../Urho2D/PhysicsWorld2D.h
    engine->RegisterObjectMethod("PhysicsWorld2D", "void SetContinuousPhysics(bool)", asMETHODPR(PhysicsWorld2D, SetContinuousPhysics, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("PhysicsWorld2D", "void set_continuousPhysics(bool)", asMETHODPR(PhysicsWorld2D, SetContinuousPhysics, (bool), void), asCALL_THISCALL);
    // void PhysicsWorld2D::SetDrawAabb(bool drawAabb) | File: ../Urho2D/PhysicsWorld2D.h
    engine->RegisterObjectMethod("PhysicsWorld2D", "void SetDrawAabb(bool)", asMETHODPR(PhysicsWorld2D, SetDrawAabb, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("PhysicsWorld2D", "void set_drawAabb(bool)", asMETHODPR(PhysicsWorld2D, SetDrawAabb, (bool), void), asCALL_THISCALL);
    // void PhysicsWorld2D::SetDrawCenterOfMass(bool drawCenterOfMass) | File: ../Urho2D/PhysicsWorld2D.h
    engine->RegisterObjectMethod("PhysicsWorld2D", "void SetDrawCenterOfMass(bool)", asMETHODPR(PhysicsWorld2D, SetDrawCenterOfMass, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("PhysicsWorld2D", "void set_drawCenterOfMass(bool)", asMETHODPR(PhysicsWorld2D, SetDrawCenterOfMass, (bool), void), asCALL_THISCALL);
    // void PhysicsWorld2D::SetDrawJoint(bool drawJoint) | File: ../Urho2D/PhysicsWorld2D.h
    engine->RegisterObjectMethod("PhysicsWorld2D", "void SetDrawJoint(bool)", asMETHODPR(PhysicsWorld2D, SetDrawJoint, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("PhysicsWorld2D", "void set_drawJoint(bool)", asMETHODPR(PhysicsWorld2D, SetDrawJoint, (bool), void), asCALL_THISCALL);
    // void PhysicsWorld2D::SetDrawPair(bool drawPair) | File: ../Urho2D/PhysicsWorld2D.h
    engine->RegisterObjectMethod("PhysicsWorld2D", "void SetDrawPair(bool)", asMETHODPR(PhysicsWorld2D, SetDrawPair, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("PhysicsWorld2D", "void set_drawPair(bool)", asMETHODPR(PhysicsWorld2D, SetDrawPair, (bool), void), asCALL_THISCALL);
    // void PhysicsWorld2D::SetDrawShape(bool drawShape) | File: ../Urho2D/PhysicsWorld2D.h
    engine->RegisterObjectMethod("PhysicsWorld2D", "void SetDrawShape(bool)", asMETHODPR(PhysicsWorld2D, SetDrawShape, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("PhysicsWorld2D", "void set_drawShape(bool)", asMETHODPR(PhysicsWorld2D, SetDrawShape, (bool), void), asCALL_THISCALL);
    // void Component::SetEnabled(bool enable) | File: ../Scene/Component.h
    engine->RegisterObjectMethod("PhysicsWorld2D", "void SetEnabled(bool)", asMETHODPR(PhysicsWorld2D, SetEnabled, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("PhysicsWorld2D", "void set_enabled(bool)", asMETHODPR(PhysicsWorld2D, SetEnabled, (bool), void), asCALL_THISCALL);
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("PhysicsWorld2D", "void SetGlobalVar(StringHash, const Variant&in)", asMETHODPR(PhysicsWorld2D, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("PhysicsWorld2D", "void set_globalVar(StringHash, const Variant&in)", asMETHODPR(PhysicsWorld2D, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    // void PhysicsWorld2D::SetGravity(const Vector2& gravity) | File: ../Urho2D/PhysicsWorld2D.h
    engine->RegisterObjectMethod("PhysicsWorld2D", "void SetGravity(const Vector2&in)", asMETHODPR(PhysicsWorld2D, SetGravity, (const Vector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("PhysicsWorld2D", "void set_gravity(const Vector2&in)", asMETHODPR(PhysicsWorld2D, SetGravity, (const Vector2&), void), asCALL_THISCALL);
    // void Serializable::SetInstanceDefault(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("PhysicsWorld2D", "void SetInstanceDefault(bool)", asMETHODPR(PhysicsWorld2D, SetInstanceDefault, (bool), void), asCALL_THISCALL);
    // void Serializable::SetInterceptNetworkUpdate(const String& attributeName, bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("PhysicsWorld2D", "void SetInterceptNetworkUpdate(const String&in, bool)", asMETHODPR(PhysicsWorld2D, SetInterceptNetworkUpdate, (const String&, bool), void), asCALL_THISCALL);
    // void Animatable::SetObjectAnimation(ObjectAnimation* objectAnimation) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("PhysicsWorld2D", "void SetObjectAnimation(ObjectAnimation@+)", asMETHODPR(PhysicsWorld2D, SetObjectAnimation, (ObjectAnimation*), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("PhysicsWorld2D", "void set_objectAnimation(ObjectAnimation@+)", asMETHODPR(PhysicsWorld2D, SetObjectAnimation, (ObjectAnimation*), void), asCALL_THISCALL);
    // void Animatable::SetObjectAnimationAttr(const ResourceRef& value) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("PhysicsWorld2D", "void SetObjectAnimationAttr(const ResourceRef&in)", asMETHODPR(PhysicsWorld2D, SetObjectAnimationAttr, (const ResourceRef&), void), asCALL_THISCALL);
    // void PhysicsWorld2D::SetPositionIterations(int positionIterations) | File: ../Urho2D/PhysicsWorld2D.h
    engine->RegisterObjectMethod("PhysicsWorld2D", "void SetPositionIterations(int)", asMETHODPR(PhysicsWorld2D, SetPositionIterations, (int), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("PhysicsWorld2D", "void set_positionIterations(int)", asMETHODPR(PhysicsWorld2D, SetPositionIterations, (int), void), asCALL_THISCALL);
    // void PhysicsWorld2D::SetSubStepping(bool enable) | File: ../Urho2D/PhysicsWorld2D.h
    engine->RegisterObjectMethod("PhysicsWorld2D", "void SetSubStepping(bool)", asMETHODPR(PhysicsWorld2D, SetSubStepping, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("PhysicsWorld2D", "void set_subStepping(bool)", asMETHODPR(PhysicsWorld2D, SetSubStepping, (bool), void), asCALL_THISCALL);
    // void Serializable::SetTemporary(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("PhysicsWorld2D", "void SetTemporary(bool)", asMETHODPR(PhysicsWorld2D, SetTemporary, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("PhysicsWorld2D", "void set_temporary(bool)", asMETHODPR(PhysicsWorld2D, SetTemporary, (bool), void), asCALL_THISCALL);
    // void PhysicsWorld2D::SetUpdateEnabled(bool enable) | File: ../Urho2D/PhysicsWorld2D.h
    engine->RegisterObjectMethod("PhysicsWorld2D", "void SetUpdateEnabled(bool)", asMETHODPR(PhysicsWorld2D, SetUpdateEnabled, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("PhysicsWorld2D", "void set_updateEnabled(bool)", asMETHODPR(PhysicsWorld2D, SetUpdateEnabled, (bool), void), asCALL_THISCALL);
    // void PhysicsWorld2D::SetVelocityIterations(int velocityIterations) | File: ../Urho2D/PhysicsWorld2D.h
    engine->RegisterObjectMethod("PhysicsWorld2D", "void SetVelocityIterations(int)", asMETHODPR(PhysicsWorld2D, SetVelocityIterations, (int), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("PhysicsWorld2D", "void set_velocityIterations(int)", asMETHODPR(PhysicsWorld2D, SetVelocityIterations, (int), void), asCALL_THISCALL);
    // void PhysicsWorld2D::SetWarmStarting(bool enable) | File: ../Urho2D/PhysicsWorld2D.h
    engine->RegisterObjectMethod("PhysicsWorld2D", "void SetWarmStarting(bool)", asMETHODPR(PhysicsWorld2D, SetWarmStarting, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("PhysicsWorld2D", "void set_warmStarting(bool)", asMETHODPR(PhysicsWorld2D, SetWarmStarting, (bool), void), asCALL_THISCALL);
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod("PhysicsWorld2D", "void UnsubscribeFromAllEvents()", asMETHODPR(PhysicsWorld2D, UnsubscribeFromAllEvents, (), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("PhysicsWorld2D", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", asFUNCTION(PhysicsWorld2D_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), asCALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("PhysicsWorld2D", "void UnsubscribeFromEvent(StringHash)", asMETHODPR(PhysicsWorld2D, UnsubscribeFromEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("PhysicsWorld2D", "void UnsubscribeFromEvent(Object@+, StringHash)", asMETHODPR(PhysicsWorld2D, UnsubscribeFromEvent, (Object*, StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("PhysicsWorld2D", "void UnsubscribeFromEvents(Object@+)", asMETHODPR(PhysicsWorld2D, UnsubscribeFromEvents, (Object*), void), asCALL_THISCALL);
    // void PhysicsWorld2D::Update(float timeStep) | File: ../Urho2D/PhysicsWorld2D.h
    engine->RegisterObjectMethod("PhysicsWorld2D", "void Update(float)", asMETHODPR(PhysicsWorld2D, Update, (float), void), asCALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("PhysicsWorld2D", "int WeakRefs() const", asMETHODPR(PhysicsWorld2D, WeakRefs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("PhysicsWorld2D", "int get_weakRefs() const", asMETHODPR(PhysicsWorld2D, WeakRefs, () const, int), asCALL_THISCALL);
    // void Serializable::WriteDeltaUpdate(Serializer& dest, const DirtyBits& attributeBits, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("PhysicsWorld2D", "void WriteDeltaUpdate(Serializer&, const DirtyBits&in, uint8)", asMETHODPR(PhysicsWorld2D, WriteDeltaUpdate, (Serializer&, const DirtyBits&, unsigned char), void), asCALL_THISCALL);
    // void Serializable::WriteInitialDeltaUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("PhysicsWorld2D", "void WriteInitialDeltaUpdate(Serializer&, uint8)", asMETHODPR(PhysicsWorld2D, WriteInitialDeltaUpdate, (Serializer&, unsigned char), void), asCALL_THISCALL);
    // void Serializable::WriteLatestDataUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("PhysicsWorld2D", "void WriteLatestDataUpdate(Serializer&, uint8)", asMETHODPR(PhysicsWorld2D, WriteLatestDataUpdate, (Serializer&, unsigned char), void), asCALL_THISCALL);
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
    engine->RegisterObjectMethod("Plane", "void Define(const Vector3&in, const Vector3&in, const Vector3&in)", asMETHODPR(Plane, Define, (const Vector3&, const Vector3&, const Vector3&), void), asCALL_THISCALL);
    // void Plane::Define(const Vector3& normal, const Vector3& point) | File: ../Math/Plane.h
    engine->RegisterObjectMethod("Plane", "void Define(const Vector3&in, const Vector3&in)", asMETHODPR(Plane, Define, (const Vector3&, const Vector3&), void), asCALL_THISCALL);
    // void Plane::Define(const Vector4& plane) | File: ../Math/Plane.h
    engine->RegisterObjectMethod("Plane", "void Define(const Vector4&in)", asMETHODPR(Plane, Define, (const Vector4&), void), asCALL_THISCALL);
    // float Plane::Distance(const Vector3& point) const | File: ../Math/Plane.h
    engine->RegisterObjectMethod("Plane", "float Distance(const Vector3&in) const", asMETHODPR(Plane, Distance, (const Vector3&) const, float), asCALL_THISCALL);
    // Plane& Plane::operator=(const Plane& rhs) noexcept=default | File: ../Math/Plane.h
    engine->RegisterObjectMethod("Plane", "Plane& opAssign(const Plane&in)", asMETHODPR(Plane, operator=, (const Plane&), Plane&), asCALL_THISCALL);
    // Plane::Plane(const Plane& plane) noexcept=default | File: ../Math/Plane.h
    engine->RegisterObjectBehaviour("Plane", asBEHAVE_CONSTRUCT, "void f(const Plane&in)", asFUNCTION(Plane_Plane_Plane), asCALL_CDECL_OBJFIRST);
    // Plane::Plane(const Vector3& v0, const Vector3& v1, const Vector3& v2) noexcept | File: ../Math/Plane.h
    engine->RegisterObjectBehaviour("Plane", asBEHAVE_CONSTRUCT, "void f(const Vector3&in, const Vector3&in, const Vector3&in)", asFUNCTION(Plane_Plane_Vector3_Vector3_Vector3), asCALL_CDECL_OBJFIRST);
    // Plane::Plane(const Vector3& normal, const Vector3& point) noexcept | File: ../Math/Plane.h
    engine->RegisterObjectBehaviour("Plane", asBEHAVE_CONSTRUCT, "void f(const Vector3&in, const Vector3&in)", asFUNCTION(Plane_Plane_Vector3_Vector3), asCALL_CDECL_OBJFIRST);
    // explicit Plane::Plane(const Vector4& plane) noexcept | File: ../Math/Plane.h
    engine->RegisterObjectBehaviour("Plane", asBEHAVE_CONSTRUCT, "void f(const Vector4&in)", asFUNCTION(Plane_Plane_Vector4), asCALL_CDECL_OBJFIRST);
    // Vector3 Plane::Project(const Vector3& point) const | File: ../Math/Plane.h
    engine->RegisterObjectMethod("Plane", "Vector3 Project(const Vector3&in) const", asMETHODPR(Plane, Project, (const Vector3&) const, Vector3), asCALL_THISCALL);
    // Vector3 Plane::Reflect(const Vector3& direction) const | File: ../Math/Plane.h
    engine->RegisterObjectMethod("Plane", "Vector3 Reflect(const Vector3&in) const", asMETHODPR(Plane, Reflect, (const Vector3&) const, Vector3), asCALL_THISCALL);
    // Matrix3x4 Plane::ReflectionMatrix() const | File: ../Math/Plane.h
    engine->RegisterObjectMethod("Plane", "Matrix3x4 ReflectionMatrix() const", asMETHODPR(Plane, ReflectionMatrix, () const, Matrix3x4), asCALL_THISCALL);
    engine->RegisterObjectMethod("Plane", "Matrix3x4 get_reflectionMatrix() const", asMETHODPR(Plane, ReflectionMatrix, () const, Matrix3x4), asCALL_THISCALL);
    // Vector4 Plane::ToVector4() const | File: ../Math/Plane.h
    engine->RegisterObjectMethod("Plane", "Vector4 ToVector4() const", asMETHODPR(Plane, ToVector4, () const, Vector4), asCALL_THISCALL);
    // void Plane::Transform(const Matrix3& transform) | File: ../Math/Plane.h
    engine->RegisterObjectMethod("Plane", "void Transform(const Matrix3&in)", asMETHODPR(Plane, Transform, (const Matrix3&), void), asCALL_THISCALL);
    // void Plane::Transform(const Matrix3x4& transform) | File: ../Math/Plane.h
    engine->RegisterObjectMethod("Plane", "void Transform(const Matrix3x4&in)", asMETHODPR(Plane, Transform, (const Matrix3x4&), void), asCALL_THISCALL);
    // void Plane::Transform(const Matrix4& transform) | File: ../Math/Plane.h
    engine->RegisterObjectMethod("Plane", "void Transform(const Matrix4&in)", asMETHODPR(Plane, Transform, (const Matrix4&), void), asCALL_THISCALL);
    // Plane Plane::Transformed(const Matrix3& transform) const | File: ../Math/Plane.h
    engine->RegisterObjectMethod("Plane", "Plane Transformed(const Matrix3&in) const", asMETHODPR(Plane, Transformed, (const Matrix3&) const, Plane), asCALL_THISCALL);
    // Plane Plane::Transformed(const Matrix3x4& transform) const | File: ../Math/Plane.h
    engine->RegisterObjectMethod("Plane", "Plane Transformed(const Matrix3x4&in) const", asMETHODPR(Plane, Transformed, (const Matrix3x4&) const, Plane), asCALL_THISCALL);
    // Plane Plane::Transformed(const Matrix4& transform) const | File: ../Math/Plane.h
    engine->RegisterObjectMethod("Plane", "Plane Transformed(const Matrix4&in) const", asMETHODPR(Plane, Transformed, (const Matrix4&) const, Plane), asCALL_THISCALL);
#ifdef REGISTER_MANUAL_PART_Plane
    REGISTER_MANUAL_PART_Plane(Plane, "Plane")
#endif

    // Vector<PODVector<Vector3> > Polyhedron::faces_ | File: ../Math/Polyhedron.h
    // Error: type "Vector<PODVector<Vector3>>" can not automatically bind
    // void Polyhedron::AddFace(const Vector3& v0, const Vector3& v1, const Vector3& v2) | File: ../Math/Polyhedron.h
    engine->RegisterObjectMethod("Polyhedron", "void AddFace(const Vector3&in, const Vector3&in, const Vector3&in)", asMETHODPR(Polyhedron, AddFace, (const Vector3&, const Vector3&, const Vector3&), void), asCALL_THISCALL);
    // void Polyhedron::AddFace(const Vector3& v0, const Vector3& v1, const Vector3& v2, const Vector3& v3) | File: ../Math/Polyhedron.h
    engine->RegisterObjectMethod("Polyhedron", "void AddFace(const Vector3&in, const Vector3&in, const Vector3&in, const Vector3&in)", asMETHODPR(Polyhedron, AddFace, (const Vector3&, const Vector3&, const Vector3&, const Vector3&), void), asCALL_THISCALL);
    // void Polyhedron::AddFace(const PODVector<Vector3>& face) | File: ../Math/Polyhedron.h
    engine->RegisterObjectMethod("Polyhedron", "void AddFace(Array<Vector3>@+)", asFUNCTION(Polyhedron_AddFace_PODVectorVector3), asCALL_CDECL_OBJFIRST);
    // void Polyhedron::Clear() | File: ../Math/Polyhedron.h
    engine->RegisterObjectMethod("Polyhedron", "void Clear()", asMETHODPR(Polyhedron, Clear, (), void), asCALL_THISCALL);
    // void Polyhedron::Clip(const Plane& plane) | File: ../Math/Polyhedron.h
    engine->RegisterObjectMethod("Polyhedron", "void Clip(const Plane&in)", asMETHODPR(Polyhedron, Clip, (const Plane&), void), asCALL_THISCALL);
    // void Polyhedron::Clip(const BoundingBox& box) | File: ../Math/Polyhedron.h
    engine->RegisterObjectMethod("Polyhedron", "void Clip(const BoundingBox&in)", asMETHODPR(Polyhedron, Clip, (const BoundingBox&), void), asCALL_THISCALL);
    // void Polyhedron::Clip(const Frustum& frustum) | File: ../Math/Polyhedron.h
    engine->RegisterObjectMethod("Polyhedron", "void Clip(const Frustum&in)", asMETHODPR(Polyhedron, Clip, (const Frustum&), void), asCALL_THISCALL);
    // void Polyhedron::Define(const BoundingBox& box) | File: ../Math/Polyhedron.h
    engine->RegisterObjectMethod("Polyhedron", "void Define(const BoundingBox&in)", asMETHODPR(Polyhedron, Define, (const BoundingBox&), void), asCALL_THISCALL);
    // void Polyhedron::Define(const Frustum& frustum) | File: ../Math/Polyhedron.h
    engine->RegisterObjectMethod("Polyhedron", "void Define(const Frustum&in)", asMETHODPR(Polyhedron, Define, (const Frustum&), void), asCALL_THISCALL);
    // bool Polyhedron::Empty() const | File: ../Math/Polyhedron.h
    engine->RegisterObjectMethod("Polyhedron", "bool Empty() const", asMETHODPR(Polyhedron, Empty, () const, bool), asCALL_THISCALL);
    // Polyhedron& Polyhedron::operator=(const Polyhedron& rhs) | File: ../Math/Polyhedron.h
    engine->RegisterObjectMethod("Polyhedron", "Polyhedron& opAssign(const Polyhedron&in)", asMETHODPR(Polyhedron, operator=, (const Polyhedron&), Polyhedron&), asCALL_THISCALL);
    // Polyhedron::Polyhedron(const Polyhedron& polyhedron) | File: ../Math/Polyhedron.h
    engine->RegisterObjectBehaviour("Polyhedron", asBEHAVE_CONSTRUCT, "void f(const Polyhedron&in)", asFUNCTION(Polyhedron_Polyhedron_Polyhedron), asCALL_CDECL_OBJFIRST);
    // explicit Polyhedron::Polyhedron(const Vector<PODVector<Vector3>>& faces) | File: ../Math/Polyhedron.h
    // Error: type "const Vector<PODVector<Vector3>>&" can not automatically bind
    // explicit Polyhedron::Polyhedron(const BoundingBox& box) | File: ../Math/Polyhedron.h
    engine->RegisterObjectBehaviour("Polyhedron", asBEHAVE_CONSTRUCT, "void f(const BoundingBox&in)", asFUNCTION(Polyhedron_Polyhedron_BoundingBox), asCALL_CDECL_OBJFIRST);
    // explicit Polyhedron::Polyhedron(const Frustum& frustum) | File: ../Math/Polyhedron.h
    engine->RegisterObjectBehaviour("Polyhedron", asBEHAVE_CONSTRUCT, "void f(const Frustum&in)", asFUNCTION(Polyhedron_Polyhedron_Frustum), asCALL_CDECL_OBJFIRST);
    // void Polyhedron::Transform(const Matrix3& transform) | File: ../Math/Polyhedron.h
    engine->RegisterObjectMethod("Polyhedron", "void Transform(const Matrix3&in)", asMETHODPR(Polyhedron, Transform, (const Matrix3&), void), asCALL_THISCALL);
    // void Polyhedron::Transform(const Matrix3x4& transform) | File: ../Math/Polyhedron.h
    engine->RegisterObjectMethod("Polyhedron", "void Transform(const Matrix3x4&in)", asMETHODPR(Polyhedron, Transform, (const Matrix3x4&), void), asCALL_THISCALL);
    // Polyhedron Polyhedron::Transformed(const Matrix3& transform) const | File: ../Math/Polyhedron.h
    engine->RegisterObjectMethod("Polyhedron", "Polyhedron Transformed(const Matrix3&in) const", asMETHODPR(Polyhedron, Transformed, (const Matrix3&) const, Polyhedron), asCALL_THISCALL);
    // Polyhedron Polyhedron::Transformed(const Matrix3x4& transform) const | File: ../Math/Polyhedron.h
    engine->RegisterObjectMethod("Polyhedron", "Polyhedron Transformed(const Matrix3x4&in) const", asMETHODPR(Polyhedron, Transformed, (const Matrix3x4&) const, Polyhedron), asCALL_THISCALL);
#ifdef REGISTER_MANUAL_PART_Polyhedron
    REGISTER_MANUAL_PART_Polyhedron(Polyhedron, "Polyhedron")
#endif

    // void RefCounted::AddRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("Profiler", asBEHAVE_ADDREF, "void f()", asMETHODPR(Profiler, AddRef, (), void), asCALL_THISCALL);
    // void Profiler::BeginBlock(const char* name) | File: ../Core/Profiler.h
    // Error: type "const char*" can not automatically bind
    // void Profiler::BeginFrame() | File: ../Core/Profiler.h
    engine->RegisterObjectMethod("Profiler", "void BeginFrame()", asMETHODPR(Profiler, BeginFrame, (), void), asCALL_THISCALL);
    // void Profiler::BeginInterval() | File: ../Core/Profiler.h
    engine->RegisterObjectMethod("Profiler", "void BeginInterval()", asMETHODPR(Profiler, BeginInterval, (), void), asCALL_THISCALL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // void Profiler::EndBlock() | File: ../Core/Profiler.h
    engine->RegisterObjectMethod("Profiler", "void EndBlock()", asMETHODPR(Profiler, EndBlock, (), void), asCALL_THISCALL);
    // void Profiler::EndFrame() | File: ../Core/Profiler.h
    engine->RegisterObjectMethod("Profiler", "void EndFrame()", asMETHODPR(Profiler, EndFrame, (), void), asCALL_THISCALL);
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Profiler", "bool GetBlockEvents() const", asMETHODPR(Profiler, GetBlockEvents, () const, bool), asCALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Profiler", "const String& GetCategory() const", asMETHODPR(Profiler, GetCategory, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Profiler", "const String& get_category() const", asMETHODPR(Profiler, GetCategory, () const, const String&), asCALL_THISCALL);
    // Context* Object::GetContext() const | File: ../Core/Object.h
    // Error: type "Context*" can used only as function parameter
    // const ProfilerBlock* Profiler::GetCurrentBlock() | File: ../Core/Profiler.h
    // Error: type "ProfilerBlock" can not automatically bind bacause have @nobind mark
    // VariantMap& Object::GetEventDataMap() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Profiler", "VariantMap& GetEventDataMap() const", asMETHODPR(Profiler, GetEventDataMap, () const, VariantMap&), asCALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Profiler", "Object@+ GetEventSender() const", asMETHODPR(Profiler, GetEventSender, () const, Object*), asCALL_THISCALL);
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Profiler", "const Variant& GetGlobalVar(StringHash) const", asMETHODPR(Profiler, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Profiler", "const Variant& get_globalVar(StringHash) const", asMETHODPR(Profiler, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Profiler", "const VariantMap& GetGlobalVars() const", asMETHODPR(Profiler, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Profiler", "const VariantMap& get_globalVars() const", asMETHODPR(Profiler, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    // const ProfilerBlock* Profiler::GetRootBlock() | File: ../Core/Profiler.h
    // Error: type "ProfilerBlock" can not automatically bind bacause have @nobind mark
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Profiler", "Object@+ GetSubsystem(StringHash) const", asMETHODPR(Profiler, GetSubsystem, (StringHash) const, Object*), asCALL_THISCALL);
    // template<class T> T*  Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("Profiler", "StringHash GetType() const", asMETHODPR(Profiler, GetType, () const, StringHash), asCALL_THISCALL);
    engine->RegisterObjectMethod("Profiler", "StringHash get_type() const", asMETHODPR(Profiler, GetType, () const, StringHash), asCALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("Profiler", "const String& GetTypeName() const", asMETHODPR(Profiler, GetTypeName, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Profiler", "const String& get_typeName() const", asMETHODPR(Profiler, GetTypeName, () const, const String&), asCALL_THISCALL);
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Profiler", "bool HasEventHandlers() const", asMETHODPR(Profiler, HasEventHandlers, () const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Profiler", "bool HasSubscribedToEvent(StringHash) const", asMETHODPR(Profiler, HasSubscribedToEvent, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Profiler", "bool HasSubscribedToEvent(Object@+, StringHash) const", asMETHODPR(Profiler, HasSubscribedToEvent, (Object*, StringHash) const, bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Profiler", "bool IsInstanceOf(StringHash) const", asMETHODPR(Profiler, IsInstanceOf, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Profiler", "void OnEvent(Object@+, StringHash, VariantMap&)", asMETHODPR(Profiler, OnEvent, (Object*, StringHash, VariantMap&), void), asCALL_THISCALL);
    // const String& Profiler::PrintData(bool showUnused=false, bool showTotal=false, unsigned maxDepth=M_MAX_UNSIGNED) const | File: ../Core/Profiler.h
    engine->RegisterObjectMethod("Profiler", "const String& PrintData(bool = false, bool = false, uint = M_MAX_UNSIGNED) const", asMETHODPR(Profiler, PrintData, (bool, bool, unsigned) const, const String&), asCALL_THISCALL);
    // explicit Profiler::Profiler(Context* context) | File: ../Core/Profiler.h
    engine->RegisterObjectBehaviour("Profiler", asBEHAVE_FACTORY, "Profiler@+ f()", asFUNCTION(Profiler_Profiler_Context), asCALL_CDECL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("Profiler", "int Refs() const", asMETHODPR(Profiler, Refs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("Profiler", "int get_refs() const", asMETHODPR(Profiler, Refs, () const, int), asCALL_THISCALL);
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("Profiler", asBEHAVE_RELEASE, "void f()", asMETHODPR(Profiler, ReleaseRef, (), void), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Profiler", "void SendEvent(StringHash)", asMETHODPR(Profiler, SendEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Profiler", "void SendEvent(StringHash, VariantMap&)", asMETHODPR(Profiler, SendEvent, (StringHash, VariantMap&), void), asCALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Profiler", "void SetBlockEvents(bool)", asMETHODPR(Profiler, SetBlockEvents, (bool), void), asCALL_THISCALL);
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Profiler", "void SetGlobalVar(StringHash, const Variant&in)", asMETHODPR(Profiler, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Profiler", "void set_globalVar(StringHash, const Variant&in)", asMETHODPR(Profiler, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod("Profiler", "void UnsubscribeFromAllEvents()", asMETHODPR(Profiler, UnsubscribeFromAllEvents, (), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Profiler", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", asFUNCTION(Profiler_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), asCALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Profiler", "void UnsubscribeFromEvent(StringHash)", asMETHODPR(Profiler, UnsubscribeFromEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Profiler", "void UnsubscribeFromEvent(Object@+, StringHash)", asMETHODPR(Profiler, UnsubscribeFromEvent, (Object*, StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Profiler", "void UnsubscribeFromEvents(Object@+)", asMETHODPR(Profiler, UnsubscribeFromEvents, (Object*), void), asCALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("Profiler", "int WeakRefs() const", asMETHODPR(Profiler, WeakRefs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("Profiler", "int get_weakRefs() const", asMETHODPR(Profiler, WeakRefs, () const, int), asCALL_THISCALL);
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
    engine->RegisterObjectMethod("ProgressBar", "void AddChild(UIElement@+)", asMETHODPR(ProgressBar, AddChild, (UIElement*), void), asCALL_THISCALL);
    // void RefCounted::AddRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("ProgressBar", asBEHAVE_ADDREF, "void f()", asMETHODPR(ProgressBar, AddRef, (), void), asCALL_THISCALL);
    // void UIElement::AddTag(const String& tag) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "void AddTag(const String&in)", asMETHODPR(ProgressBar, AddTag, (const String&), void), asCALL_THISCALL);
    // void UIElement::AddTags(const String& tags, char separator=';') | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "void AddTags(const String&in, int8 = ';')", asMETHODPR(ProgressBar, AddTags, (const String&, char), void), asCALL_THISCALL);
    // void UIElement::AddTags(const StringVector& tags) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "void AddTags(Array<String>@+)", asFUNCTION(ProgressBar_AddTags_StringVector), asCALL_CDECL_OBJFIRST);
    // void UIElement::AdjustScissor(IntRect& currentScissor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "void AdjustScissor(IntRect&)", asMETHODPR(ProgressBar, AdjustScissor, (IntRect&), void), asCALL_THISCALL);
    // void Serializable::AllocateNetworkState() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ProgressBar", "void AllocateNetworkState()", asMETHODPR(ProgressBar, AllocateNetworkState, (), void), asCALL_THISCALL);
    // void UIElement::ApplyAttributes() override | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "void ApplyAttributes()", asMETHODPR(ProgressBar, ApplyAttributes, (), void), asCALL_THISCALL);
    // void UIElement::BringToFront() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "void BringToFront()", asMETHODPR(ProgressBar, BringToFront, (), void), asCALL_THISCALL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // void ProgressBar::ChangeValue(float delta) | File: ../UI/ProgressBar.h
    engine->RegisterObjectMethod("ProgressBar", "void ChangeValue(float)", asMETHODPR(ProgressBar, ChangeValue, (float), void), asCALL_THISCALL);
    // UIElement* UIElement::CreateChild(StringHash type, const String& name=String::EMPTY, unsigned index=M_MAX_UNSIGNED) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "UIElement@+ CreateChild(StringHash, const String&in = String::EMPTY, uint = M_MAX_UNSIGNED)", asMETHODPR(ProgressBar, CreateChild, (StringHash, const String&, unsigned), UIElement*), asCALL_THISCALL);
    // template<class T> T*  UIElement::CreateChild(const String& name=String::EMPTY, unsigned index=M_MAX_UNSIGNED) | File: ../UI/UIElement.h
    // Not registered because template
    // void UIElement::DisableLayoutUpdate() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "void DisableLayoutUpdate()", asMETHODPR(ProgressBar, DisableLayoutUpdate, (), void), asCALL_THISCALL);
    // virtual IntVector2 UIElement::ElementToScreen(const IntVector2& position) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "IntVector2 ElementToScreen(const IntVector2&in)", asMETHODPR(ProgressBar, ElementToScreen, (const IntVector2&), IntVector2), asCALL_THISCALL);
    // void UIElement::EnableLayoutUpdate() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "void EnableLayoutUpdate()", asMETHODPR(ProgressBar, EnableLayoutUpdate, (), void), asCALL_THISCALL);
    // bool UIElement::FilterAttributes(XMLElement& dest) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "bool FilterAttributes(XMLElement&) const", asMETHODPR(ProgressBar, FilterAttributes, (XMLElement&) const, bool), asCALL_THISCALL);
    // unsigned UIElement::FindChild(UIElement* element) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "uint FindChild(UIElement@+) const", asMETHODPR(ProgressBar, FindChild, (UIElement*) const, unsigned), asCALL_THISCALL);
    // bool Animatable::GetAnimationEnabled() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ProgressBar", "bool GetAnimationEnabled() const", asMETHODPR(ProgressBar, GetAnimationEnabled, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "bool get_animationEnabled() const", asMETHODPR(ProgressBar, GetAnimationEnabled, () const, bool), asCALL_THISCALL);
    // const String& UIElement::GetAppliedStyle() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "const String& GetAppliedStyle() const", asMETHODPR(ProgressBar, GetAppliedStyle, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "const String& get_style() const", asMETHODPR(ProgressBar, GetAppliedStyle, () const, const String&), asCALL_THISCALL);
    // Variant Serializable::GetAttribute(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ProgressBar", "Variant GetAttribute(uint) const", asMETHODPR(ProgressBar, GetAttribute, (unsigned) const, Variant), asCALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "Variant get_attributes(uint) const", asMETHODPR(ProgressBar, GetAttribute, (unsigned) const, Variant), asCALL_THISCALL);
    // Variant Serializable::GetAttribute(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ProgressBar", "Variant GetAttribute(const String&in) const", asMETHODPR(ProgressBar, GetAttribute, (const String&) const, Variant), asCALL_THISCALL);
    // ValueAnimation* Animatable::GetAttributeAnimation(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ProgressBar", "ValueAnimation@+ GetAttributeAnimation(const String&in) const", asMETHODPR(ProgressBar, GetAttributeAnimation, (const String&) const, ValueAnimation*), asCALL_THISCALL);
    // float Animatable::GetAttributeAnimationSpeed(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ProgressBar", "float GetAttributeAnimationSpeed(const String&in) const", asMETHODPR(ProgressBar, GetAttributeAnimationSpeed, (const String&) const, float), asCALL_THISCALL);
    // float Animatable::GetAttributeAnimationTime(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ProgressBar", "float GetAttributeAnimationTime(const String&in) const", asMETHODPR(ProgressBar, GetAttributeAnimationTime, (const String&) const, float), asCALL_THISCALL);
    // WrapMode Animatable::GetAttributeAnimationWrapMode(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ProgressBar", "WrapMode GetAttributeAnimationWrapMode(const String&in) const", asMETHODPR(ProgressBar, GetAttributeAnimationWrapMode, (const String&) const, WrapMode), asCALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ProgressBar", "Variant GetAttributeDefault(uint) const", asMETHODPR(ProgressBar, GetAttributeDefault, (unsigned) const, Variant), asCALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "Variant get_attributeDefaults(uint) const", asMETHODPR(ProgressBar, GetAttributeDefault, (unsigned) const, Variant), asCALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ProgressBar", "Variant GetAttributeDefault(const String&in) const", asMETHODPR(ProgressBar, GetAttributeDefault, (const String&) const, Variant), asCALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // void BorderImage::GetBatches(PODVector<UIBatch>& batches, PODVector<float>& vertexData, const IntRect& currentScissor) override | File: ../UI/BorderImage.h
    // Error: type "PODVector<UIBatch>&" can not automatically bind
    // void UIElement::GetBatchesWithOffset(IntVector2& offset, PODVector<UIBatch>& batches, PODVector<float>& vertexData, IntRect currentScissor) | File: ../UI/UIElement.h
    // Error: type "PODVector<UIBatch>&" can not automatically bind
    // BlendMode BorderImage::GetBlendMode() const | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("ProgressBar", "BlendMode GetBlendMode() const", asMETHODPR(ProgressBar, GetBlendMode, () const, BlendMode), asCALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "BlendMode get_blendMode() const", asMETHODPR(ProgressBar, GetBlendMode, () const, BlendMode), asCALL_THISCALL);
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ProgressBar", "bool GetBlockEvents() const", asMETHODPR(ProgressBar, GetBlockEvents, () const, bool), asCALL_THISCALL);
    // const IntRect& BorderImage::GetBorder() const | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("ProgressBar", "const IntRect& GetBorder() const", asMETHODPR(ProgressBar, GetBorder, () const, const IntRect&), asCALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "const IntRect& get_border() const", asMETHODPR(ProgressBar, GetBorder, () const, const IntRect&), asCALL_THISCALL);
    // bool UIElement::GetBringToBack() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "bool GetBringToBack() const", asMETHODPR(ProgressBar, GetBringToBack, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "bool get_bringToBack() const", asMETHODPR(ProgressBar, GetBringToBack, () const, bool), asCALL_THISCALL);
    // bool UIElement::GetBringToFront() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "bool GetBringToFront() const", asMETHODPR(ProgressBar, GetBringToFront, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "bool get_bringToFront() const", asMETHODPR(ProgressBar, GetBringToFront, () const, bool), asCALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ProgressBar", "const String& GetCategory() const", asMETHODPR(ProgressBar, GetCategory, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "const String& get_category() const", asMETHODPR(ProgressBar, GetCategory, () const, const String&), asCALL_THISCALL);
    // UIElement* UIElement::GetChild(unsigned index) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "UIElement@+ GetChild(uint) const", asMETHODPR(ProgressBar, GetChild, (unsigned) const, UIElement*), asCALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "UIElement@+ get_children(uint) const", asMETHODPR(ProgressBar, GetChild, (unsigned) const, UIElement*), asCALL_THISCALL);
    // UIElement* UIElement::GetChild(const String& name, bool recursive=false) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "UIElement@+ GetChild(const String&in, bool = false) const", asMETHODPR(ProgressBar, GetChild, (const String&, bool) const, UIElement*), asCALL_THISCALL);
    // UIElement* UIElement::GetChild(const StringHash& key, const Variant& value=Variant::EMPTY, bool recursive=false) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "UIElement@+ GetChild(const StringHash&in, const Variant&in = Variant::EMPTY, bool = false) const", asMETHODPR(ProgressBar, GetChild, (const StringHash&, const Variant&, bool) const, UIElement*), asCALL_THISCALL);
    // template<class T> T*  UIElement::GetChildDynamicCast(unsigned index) const | File: ../UI/UIElement.h
    // Not registered because template
    // template<class T> T*  UIElement::GetChildDynamicCast(const String& name, bool recursive=false) const | File: ../UI/UIElement.h
    // Not registered because template
    // template<class T> T*  UIElement::GetChildDynamicCast(const StringHash& key, const Variant& value=Variant::EMPTY, bool recursive=false) const | File: ../UI/UIElement.h
    // Not registered because template
    // const IntVector2& UIElement::GetChildOffset() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "const IntVector2& GetChildOffset() const", asMETHODPR(ProgressBar, GetChildOffset, () const, const IntVector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "const IntVector2& get_childOffset() const", asMETHODPR(ProgressBar, GetChildOffset, () const, const IntVector2&), asCALL_THISCALL);
    // const Vector<SharedPtr<UIElement>>& UIElement::GetChildren() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "Array<UIElement@>@ GetChildren() const", asFUNCTION(ProgressBar_GetChildren_void), asCALL_CDECL_OBJFIRST);
    // void UIElement::GetChildren(PODVector<UIElement*>& dest, bool recursive=false) const | File: ../UI/UIElement.h
    // Error: type "PODVector<UIElement*>&" can not automatically bind
    // PODVector<UIElement*> UIElement::GetChildren(bool recursive) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "Array<UIElement@>@ GetChildren(bool) const", asFUNCTION(ProgressBar_GetChildren_bool), asCALL_CDECL_OBJFIRST);
    // void UIElement::GetChildrenWithTag(PODVector<UIElement*>& dest, const String& tag, bool recursive=false) const | File: ../UI/UIElement.h
    // Error: type "PODVector<UIElement*>&" can not automatically bind
    // PODVector<UIElement*> UIElement::GetChildrenWithTag(const String& tag, bool recursive=false) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "Array<UIElement@>@ GetChildrenWithTag(const String&in, bool = false) const", asFUNCTION(ProgressBar_GetChildrenWithTag_String_bool), asCALL_CDECL_OBJFIRST);
    // template<class T> T*  UIElement::GetChildStaticCast(unsigned index) const | File: ../UI/UIElement.h
    // Not registered because template
    // template<class T> T*  UIElement::GetChildStaticCast(const String& name, bool recursive=false) const | File: ../UI/UIElement.h
    // Not registered because template
    // template<class T> T*  UIElement::GetChildStaticCast(const StringHash& key, const Variant& value=Variant::EMPTY, bool recursive=false) const | File: ../UI/UIElement.h
    // Not registered because template
    // const IntRect& UIElement::GetClipBorder() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "const IntRect& GetClipBorder() const", asMETHODPR(ProgressBar, GetClipBorder, () const, const IntRect&), asCALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "const IntRect& get_clipBorder() const", asMETHODPR(ProgressBar, GetClipBorder, () const, const IntRect&), asCALL_THISCALL);
    // bool UIElement::GetClipChildren() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "bool GetClipChildren() const", asMETHODPR(ProgressBar, GetClipChildren, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "bool get_clipChildren() const", asMETHODPR(ProgressBar, GetClipChildren, () const, bool), asCALL_THISCALL);
    // const Color& UIElement::GetColor(Corner corner) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "const Color& GetColor(Corner) const", asMETHODPR(ProgressBar, GetColor, (Corner) const, const Color&), asCALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "const Color& get_colors(Corner) const", asMETHODPR(ProgressBar, GetColor, (Corner) const, const Color&), asCALL_THISCALL);
    // const Color& UIElement::GetColorAttr() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "const Color& GetColorAttr() const", asMETHODPR(ProgressBar, GetColorAttr, () const, const Color&), asCALL_THISCALL);
    // IntRect UIElement::GetCombinedScreenRect() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "IntRect GetCombinedScreenRect()", asMETHODPR(ProgressBar, GetCombinedScreenRect, (), IntRect), asCALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "IntRect get_combinedScreenRect()", asMETHODPR(ProgressBar, GetCombinedScreenRect, (), IntRect), asCALL_THISCALL);
    // Context* Object::GetContext() const | File: ../Core/Object.h
    // Error: type "Context*" can used only as function parameter
    // virtual void UIElement::GetDebugDrawBatches(PODVector<UIBatch>& batches, PODVector<float>& vertexData, const IntRect& currentScissor) | File: ../UI/UIElement.h
    // Error: type "PODVector<UIBatch>&" can not automatically bind
    // XMLFile* UIElement::GetDefaultStyle(bool recursiveUp=true) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "XMLFile@+ GetDefaultStyle(bool = true) const", asMETHODPR(ProgressBar, GetDefaultStyle, (bool) const, XMLFile*), asCALL_THISCALL);
    // const Color& UIElement::GetDerivedColor() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "const Color& GetDerivedColor() const", asMETHODPR(ProgressBar, GetDerivedColor, () const, const Color&), asCALL_THISCALL);
    // float UIElement::GetDerivedOpacity() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "float GetDerivedOpacity() const", asMETHODPR(ProgressBar, GetDerivedOpacity, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "float get_derivedOpacity() const", asMETHODPR(ProgressBar, GetDerivedOpacity, () const, float), asCALL_THISCALL);
    // const IntVector2& BorderImage::GetDisabledOffset() const | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("ProgressBar", "const IntVector2& GetDisabledOffset() const", asMETHODPR(ProgressBar, GetDisabledOffset, () const, const IntVector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "const IntVector2& get_disabledOffset() const", asMETHODPR(ProgressBar, GetDisabledOffset, () const, const IntVector2&), asCALL_THISCALL);
    // MouseButtonFlags UIElement::GetDragButtonCombo() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "MouseButtonFlags GetDragButtonCombo() const", asMETHODPR(ProgressBar, GetDragButtonCombo, () const, MouseButtonFlags), asCALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "MouseButtonFlags get_dragButtonCombo() const", asMETHODPR(ProgressBar, GetDragButtonCombo, () const, MouseButtonFlags), asCALL_THISCALL);
    // unsigned UIElement::GetDragButtonCount() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "uint GetDragButtonCount() const", asMETHODPR(ProgressBar, GetDragButtonCount, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "uint get_dragButtonCount() const", asMETHODPR(ProgressBar, GetDragButtonCount, () const, unsigned), asCALL_THISCALL);
    // DragAndDropModeFlags UIElement::GetDragDropMode() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "DragAndDropModeFlags GetDragDropMode() const", asMETHODPR(ProgressBar, GetDragDropMode, () const, DragAndDropModeFlags), asCALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "DragAndDropModeFlags get_dragDropMode() const", asMETHODPR(ProgressBar, GetDragDropMode, () const, DragAndDropModeFlags), asCALL_THISCALL);
    // IntVector2 UIElement::GetEffectiveMinSize() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "IntVector2 GetEffectiveMinSize() const", asMETHODPR(ProgressBar, GetEffectiveMinSize, () const, IntVector2), asCALL_THISCALL);
    // UIElement* UIElement::GetElementEventSender() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "UIElement@+ GetElementEventSender() const", asMETHODPR(ProgressBar, GetElementEventSender, () const, UIElement*), asCALL_THISCALL);
    // bool UIElement::GetEnableAnchor() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "bool GetEnableAnchor() const", asMETHODPR(ProgressBar, GetEnableAnchor, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "bool get_enableAnchor() const", asMETHODPR(ProgressBar, GetEnableAnchor, () const, bool), asCALL_THISCALL);
    // VariantMap& Object::GetEventDataMap() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ProgressBar", "VariantMap& GetEventDataMap() const", asMETHODPR(ProgressBar, GetEventDataMap, () const, VariantMap&), asCALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ProgressBar", "Object@+ GetEventSender() const", asMETHODPR(ProgressBar, GetEventSender, () const, Object*), asCALL_THISCALL);
    // FocusMode UIElement::GetFocusMode() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "FocusMode GetFocusMode() const", asMETHODPR(ProgressBar, GetFocusMode, () const, FocusMode), asCALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "FocusMode get_focusMode() const", asMETHODPR(ProgressBar, GetFocusMode, () const, FocusMode), asCALL_THISCALL);
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ProgressBar", "const Variant& GetGlobalVar(StringHash) const", asMETHODPR(ProgressBar, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "const Variant& get_globalVar(StringHash) const", asMETHODPR(ProgressBar, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ProgressBar", "const VariantMap& GetGlobalVars() const", asMETHODPR(ProgressBar, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "const VariantMap& get_globalVars() const", asMETHODPR(ProgressBar, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    // int UIElement::GetHeight() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "int GetHeight() const", asMETHODPR(ProgressBar, GetHeight, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "int get_height() const", asMETHODPR(ProgressBar, GetHeight, () const, int), asCALL_THISCALL);
    // HorizontalAlignment UIElement::GetHorizontalAlignment() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "HorizontalAlignment GetHorizontalAlignment() const", asMETHODPR(ProgressBar, GetHorizontalAlignment, () const, HorizontalAlignment), asCALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "HorizontalAlignment get_horizontalAlignment() const", asMETHODPR(ProgressBar, GetHorizontalAlignment, () const, HorizontalAlignment), asCALL_THISCALL);
    // const IntVector2& BorderImage::GetHoverOffset() const | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("ProgressBar", "const IntVector2& GetHoverOffset() const", asMETHODPR(ProgressBar, GetHoverOffset, () const, const IntVector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "const IntVector2& get_hoverOffset() const", asMETHODPR(ProgressBar, GetHoverOffset, () const, const IntVector2&), asCALL_THISCALL);
    // const IntRect& BorderImage::GetImageBorder() const | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("ProgressBar", "const IntRect& GetImageBorder() const", asMETHODPR(ProgressBar, GetImageBorder, () const, const IntRect&), asCALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "const IntRect& get_imageBorder() const", asMETHODPR(ProgressBar, GetImageBorder, () const, const IntRect&), asCALL_THISCALL);
    // const IntRect& BorderImage::GetImageRect() const | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("ProgressBar", "const IntRect& GetImageRect() const", asMETHODPR(ProgressBar, GetImageRect, () const, const IntRect&), asCALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "const IntRect& get_imageRect() const", asMETHODPR(ProgressBar, GetImageRect, () const, const IntRect&), asCALL_THISCALL);
    // int UIElement::GetIndent() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "int GetIndent() const", asMETHODPR(ProgressBar, GetIndent, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "int get_indent() const", asMETHODPR(ProgressBar, GetIndent, () const, int), asCALL_THISCALL);
    // int UIElement::GetIndentSpacing() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "int GetIndentSpacing() const", asMETHODPR(ProgressBar, GetIndentSpacing, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "int get_indentSpacing() const", asMETHODPR(ProgressBar, GetIndentSpacing, () const, int), asCALL_THISCALL);
    // int UIElement::GetIndentWidth() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "int GetIndentWidth() const", asMETHODPR(ProgressBar, GetIndentWidth, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "int get_indentWidth() const", asMETHODPR(ProgressBar, GetIndentWidth, () const, int), asCALL_THISCALL);
    // bool Serializable::GetInterceptNetworkUpdate(const String& attributeName) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ProgressBar", "bool GetInterceptNetworkUpdate(const String&in) const", asMETHODPR(ProgressBar, GetInterceptNetworkUpdate, (const String&) const, bool), asCALL_THISCALL);
    // BorderImage* ProgressBar::GetKnob() const | File: ../UI/ProgressBar.h
    engine->RegisterObjectMethod("ProgressBar", "BorderImage@+ GetKnob() const", asMETHODPR(ProgressBar, GetKnob, () const, BorderImage*), asCALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "BorderImage@+ get_knob() const", asMETHODPR(ProgressBar, GetKnob, () const, BorderImage*), asCALL_THISCALL);
    // const IntRect& UIElement::GetLayoutBorder() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "const IntRect& GetLayoutBorder() const", asMETHODPR(ProgressBar, GetLayoutBorder, () const, const IntRect&), asCALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "const IntRect& get_layoutBorder() const", asMETHODPR(ProgressBar, GetLayoutBorder, () const, const IntRect&), asCALL_THISCALL);
    // int UIElement::GetLayoutElementMaxSize() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "int GetLayoutElementMaxSize() const", asMETHODPR(ProgressBar, GetLayoutElementMaxSize, () const, int), asCALL_THISCALL);
    // const Vector2& UIElement::GetLayoutFlexScale() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "const Vector2& GetLayoutFlexScale() const", asMETHODPR(ProgressBar, GetLayoutFlexScale, () const, const Vector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "const Vector2& get_layoutFlexScale() const", asMETHODPR(ProgressBar, GetLayoutFlexScale, () const, const Vector2&), asCALL_THISCALL);
    // LayoutMode UIElement::GetLayoutMode() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "LayoutMode GetLayoutMode() const", asMETHODPR(ProgressBar, GetLayoutMode, () const, LayoutMode), asCALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "LayoutMode get_layoutMode() const", asMETHODPR(ProgressBar, GetLayoutMode, () const, LayoutMode), asCALL_THISCALL);
    // int UIElement::GetLayoutSpacing() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "int GetLayoutSpacing() const", asMETHODPR(ProgressBar, GetLayoutSpacing, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "int get_layoutSpacing() const", asMETHODPR(ProgressBar, GetLayoutSpacing, () const, int), asCALL_THISCALL);
    // const String& ProgressBar::GetLoadingPercentStyle() const | File: ../UI/ProgressBar.h
    engine->RegisterObjectMethod("ProgressBar", "const String& GetLoadingPercentStyle() const", asMETHODPR(ProgressBar, GetLoadingPercentStyle, () const, const String&), asCALL_THISCALL);
    // Material* BorderImage::GetMaterial() const | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("ProgressBar", "Material@+ GetMaterial() const", asMETHODPR(ProgressBar, GetMaterial, () const, Material*), asCALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "Material@+ get_material() const", asMETHODPR(ProgressBar, GetMaterial, () const, Material*), asCALL_THISCALL);
    // ResourceRef BorderImage::GetMaterialAttr() const | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("ProgressBar", "ResourceRef GetMaterialAttr() const", asMETHODPR(ProgressBar, GetMaterialAttr, () const, ResourceRef), asCALL_THISCALL);
    // const Vector2& UIElement::GetMaxAnchor() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "const Vector2& GetMaxAnchor() const", asMETHODPR(ProgressBar, GetMaxAnchor, () const, const Vector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "const Vector2& get_maxAnchor() const", asMETHODPR(ProgressBar, GetMaxAnchor, () const, const Vector2&), asCALL_THISCALL);
    // int UIElement::GetMaxHeight() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "int GetMaxHeight() const", asMETHODPR(ProgressBar, GetMaxHeight, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "int get_maxHeight() const", asMETHODPR(ProgressBar, GetMaxHeight, () const, int), asCALL_THISCALL);
    // const IntVector2& UIElement::GetMaxOffset() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "const IntVector2& GetMaxOffset() const", asMETHODPR(ProgressBar, GetMaxOffset, () const, const IntVector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "const IntVector2& get_maxOffset() const", asMETHODPR(ProgressBar, GetMaxOffset, () const, const IntVector2&), asCALL_THISCALL);
    // const IntVector2& UIElement::GetMaxSize() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "const IntVector2& GetMaxSize() const", asMETHODPR(ProgressBar, GetMaxSize, () const, const IntVector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "const IntVector2& get_maxSize() const", asMETHODPR(ProgressBar, GetMaxSize, () const, const IntVector2&), asCALL_THISCALL);
    // int UIElement::GetMaxWidth() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "int GetMaxWidth() const", asMETHODPR(ProgressBar, GetMaxWidth, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "int get_maxWidth() const", asMETHODPR(ProgressBar, GetMaxWidth, () const, int), asCALL_THISCALL);
    // const Vector2& UIElement::GetMinAnchor() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "const Vector2& GetMinAnchor() const", asMETHODPR(ProgressBar, GetMinAnchor, () const, const Vector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "const Vector2& get_minAnchor() const", asMETHODPR(ProgressBar, GetMinAnchor, () const, const Vector2&), asCALL_THISCALL);
    // int UIElement::GetMinHeight() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "int GetMinHeight() const", asMETHODPR(ProgressBar, GetMinHeight, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "int get_minHeight() const", asMETHODPR(ProgressBar, GetMinHeight, () const, int), asCALL_THISCALL);
    // const IntVector2& UIElement::GetMinOffset() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "const IntVector2& GetMinOffset() const", asMETHODPR(ProgressBar, GetMinOffset, () const, const IntVector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "const IntVector2& get_minOffset() const", asMETHODPR(ProgressBar, GetMinOffset, () const, const IntVector2&), asCALL_THISCALL);
    // const IntVector2& UIElement::GetMinSize() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "const IntVector2& GetMinSize() const", asMETHODPR(ProgressBar, GetMinSize, () const, const IntVector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "const IntVector2& get_minSize() const", asMETHODPR(ProgressBar, GetMinSize, () const, const IntVector2&), asCALL_THISCALL);
    // int UIElement::GetMinWidth() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "int GetMinWidth() const", asMETHODPR(ProgressBar, GetMinWidth, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "int get_minWidth() const", asMETHODPR(ProgressBar, GetMinWidth, () const, int), asCALL_THISCALL);
    // const String& UIElement::GetName() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "const String& GetName() const", asMETHODPR(ProgressBar, GetName, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "const String& get_name() const", asMETHODPR(ProgressBar, GetName, () const, const String&), asCALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetNetworkAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // NetworkState* Serializable::GetNetworkState() const | File: ../Scene/Serializable.h
    // Error: type "NetworkState*" can not automatically bind
    // unsigned Serializable::GetNumAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ProgressBar", "uint GetNumAttributes() const", asMETHODPR(ProgressBar, GetNumAttributes, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "uint get_numAttributes() const", asMETHODPR(ProgressBar, GetNumAttributes, () const, unsigned), asCALL_THISCALL);
    // unsigned UIElement::GetNumChildren(bool recursive=false) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "uint GetNumChildren(bool = false) const", asMETHODPR(ProgressBar, GetNumChildren, (bool) const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "uint get_numChildren(bool = false) const", asMETHODPR(ProgressBar, GetNumChildren, (bool) const, unsigned), asCALL_THISCALL);
    // unsigned Serializable::GetNumNetworkAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ProgressBar", "uint GetNumNetworkAttributes() const", asMETHODPR(ProgressBar, GetNumNetworkAttributes, () const, unsigned), asCALL_THISCALL);
    // ObjectAnimation* Animatable::GetObjectAnimation() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ProgressBar", "ObjectAnimation@+ GetObjectAnimation() const", asMETHODPR(ProgressBar, GetObjectAnimation, () const, ObjectAnimation*), asCALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "ObjectAnimation@+ get_objectAnimation() const", asMETHODPR(ProgressBar, GetObjectAnimation, () const, ObjectAnimation*), asCALL_THISCALL);
    // ResourceRef Animatable::GetObjectAnimationAttr() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ProgressBar", "ResourceRef GetObjectAnimationAttr() const", asMETHODPR(ProgressBar, GetObjectAnimationAttr, () const, ResourceRef), asCALL_THISCALL);
    // float UIElement::GetOpacity() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "float GetOpacity() const", asMETHODPR(ProgressBar, GetOpacity, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "float get_opacity() const", asMETHODPR(ProgressBar, GetOpacity, () const, float), asCALL_THISCALL);
    // Orientation ProgressBar::GetOrientation() const | File: ../UI/ProgressBar.h
    engine->RegisterObjectMethod("ProgressBar", "Orientation GetOrientation() const", asMETHODPR(ProgressBar, GetOrientation, () const, Orientation), asCALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "Orientation get_orientation() const", asMETHODPR(ProgressBar, GetOrientation, () const, Orientation), asCALL_THISCALL);
    // UIElement* UIElement::GetParent() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "UIElement@+ GetParent() const", asMETHODPR(ProgressBar, GetParent, () const, UIElement*), asCALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "UIElement@+ get_parent() const", asMETHODPR(ProgressBar, GetParent, () const, UIElement*), asCALL_THISCALL);
    // const Vector2& UIElement::GetPivot() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "const Vector2& GetPivot() const", asMETHODPR(ProgressBar, GetPivot, () const, const Vector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "const Vector2& get_pivot() const", asMETHODPR(ProgressBar, GetPivot, () const, const Vector2&), asCALL_THISCALL);
    // const IntVector2& UIElement::GetPosition() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "const IntVector2& GetPosition() const", asMETHODPR(ProgressBar, GetPosition, () const, const IntVector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "const IntVector2& get_position() const", asMETHODPR(ProgressBar, GetPosition, () const, const IntVector2&), asCALL_THISCALL);
    // int UIElement::GetPriority() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "int GetPriority() const", asMETHODPR(ProgressBar, GetPriority, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "int get_priority() const", asMETHODPR(ProgressBar, GetPriority, () const, int), asCALL_THISCALL);
    // float ProgressBar::GetRange() const | File: ../UI/ProgressBar.h
    engine->RegisterObjectMethod("ProgressBar", "float GetRange() const", asMETHODPR(ProgressBar, GetRange, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "float get_range() const", asMETHODPR(ProgressBar, GetRange, () const, float), asCALL_THISCALL);
    // UIElement* UIElement::GetRoot() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "UIElement@+ GetRoot() const", asMETHODPR(ProgressBar, GetRoot, () const, UIElement*), asCALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "UIElement@+ get_root() const", asMETHODPR(ProgressBar, GetRoot, () const, UIElement*), asCALL_THISCALL);
    // virtual const IntVector2& UIElement::GetScreenPosition() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "const IntVector2& GetScreenPosition() const", asMETHODPR(ProgressBar, GetScreenPosition, () const, const IntVector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "const IntVector2& get_screenPosition() const", asMETHODPR(ProgressBar, GetScreenPosition, () const, const IntVector2&), asCALL_THISCALL);
    // bool ProgressBar::GetShowPercentText() const | File: ../UI/ProgressBar.h
    engine->RegisterObjectMethod("ProgressBar", "bool GetShowPercentText() const", asMETHODPR(ProgressBar, GetShowPercentText, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "bool get_showPercentText() const", asMETHODPR(ProgressBar, GetShowPercentText, () const, bool), asCALL_THISCALL);
    // const IntVector2& UIElement::GetSize() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "const IntVector2& GetSize() const", asMETHODPR(ProgressBar, GetSize, () const, const IntVector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "const IntVector2& get_size() const", asMETHODPR(ProgressBar, GetSize, () const, const IntVector2&), asCALL_THISCALL);
    // bool UIElement::GetSortChildren() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "bool GetSortChildren() const", asMETHODPR(ProgressBar, GetSortChildren, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "bool get_sortChildren() const", asMETHODPR(ProgressBar, GetSortChildren, () const, bool), asCALL_THISCALL);
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ProgressBar", "Object@+ GetSubsystem(StringHash) const", asMETHODPR(ProgressBar, GetSubsystem, (StringHash) const, Object*), asCALL_THISCALL);
    // template<class T> T*  Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // const StringVector& UIElement::GetTags() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "Array<String>@ GetTags() const", asFUNCTION(ProgressBar_GetTags_void), asCALL_CDECL_OBJFIRST);
    engine->RegisterObjectMethod("ProgressBar", "Array<String>@ get_tags() const", asFUNCTION(ProgressBar_GetTags_void), asCALL_CDECL_OBJFIRST);
    // Texture* BorderImage::GetTexture() const | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("ProgressBar", "Texture@+ GetTexture() const", asMETHODPR(ProgressBar, GetTexture, () const, Texture*), asCALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "Texture@+ get_texture() const", asMETHODPR(ProgressBar, GetTexture, () const, Texture*), asCALL_THISCALL);
    // ResourceRef BorderImage::GetTextureAttr() const | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("ProgressBar", "ResourceRef GetTextureAttr() const", asMETHODPR(ProgressBar, GetTextureAttr, () const, ResourceRef), asCALL_THISCALL);
    // TraversalMode UIElement::GetTraversalMode() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "TraversalMode GetTraversalMode() const", asMETHODPR(ProgressBar, GetTraversalMode, () const, TraversalMode), asCALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "TraversalMode get_traversalMode() const", asMETHODPR(ProgressBar, GetTraversalMode, () const, TraversalMode), asCALL_THISCALL);
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("ProgressBar", "StringHash GetType() const", asMETHODPR(ProgressBar, GetType, () const, StringHash), asCALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "StringHash get_type() const", asMETHODPR(ProgressBar, GetType, () const, StringHash), asCALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("ProgressBar", "const String& GetTypeName() const", asMETHODPR(ProgressBar, GetTypeName, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "const String& get_typeName() const", asMETHODPR(ProgressBar, GetTypeName, () const, const String&), asCALL_THISCALL);
    // bool UIElement::GetUseDerivedOpacity() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "bool GetUseDerivedOpacity() const", asMETHODPR(ProgressBar, GetUseDerivedOpacity, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "bool get_useDerivedOpacity() const", asMETHODPR(ProgressBar, GetUseDerivedOpacity, () const, bool), asCALL_THISCALL);
    // float ProgressBar::GetValue() const | File: ../UI/ProgressBar.h
    engine->RegisterObjectMethod("ProgressBar", "float GetValue() const", asMETHODPR(ProgressBar, GetValue, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "float get_value() const", asMETHODPR(ProgressBar, GetValue, () const, float), asCALL_THISCALL);
    // const Variant& UIElement::GetVar(const StringHash& key) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "const Variant& GetVar(const StringHash&in) const", asMETHODPR(ProgressBar, GetVar, (const StringHash&) const, const Variant&), asCALL_THISCALL);
    // const VariantMap& UIElement::GetVars() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "const VariantMap& GetVars() const", asMETHODPR(ProgressBar, GetVars, () const, const VariantMap&), asCALL_THISCALL);
    // VerticalAlignment UIElement::GetVerticalAlignment() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "VerticalAlignment GetVerticalAlignment() const", asMETHODPR(ProgressBar, GetVerticalAlignment, () const, VerticalAlignment), asCALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "VerticalAlignment get_verticalAlignment() const", asMETHODPR(ProgressBar, GetVerticalAlignment, () const, VerticalAlignment), asCALL_THISCALL);
    // int UIElement::GetWidth() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "int GetWidth() const", asMETHODPR(ProgressBar, GetWidth, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "int get_width() const", asMETHODPR(ProgressBar, GetWidth, () const, int), asCALL_THISCALL);
    // bool UIElement::HasColorGradient() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "bool HasColorGradient() const", asMETHODPR(ProgressBar, HasColorGradient, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "bool get_colorGradient() const", asMETHODPR(ProgressBar, HasColorGradient, () const, bool), asCALL_THISCALL);
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ProgressBar", "bool HasEventHandlers() const", asMETHODPR(ProgressBar, HasEventHandlers, () const, bool), asCALL_THISCALL);
    // bool UIElement::HasFocus() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "bool HasFocus() const", asMETHODPR(ProgressBar, HasFocus, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "bool get_focus() const", asMETHODPR(ProgressBar, HasFocus, () const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ProgressBar", "bool HasSubscribedToEvent(StringHash) const", asMETHODPR(ProgressBar, HasSubscribedToEvent, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ProgressBar", "bool HasSubscribedToEvent(Object@+, StringHash) const", asMETHODPR(ProgressBar, HasSubscribedToEvent, (Object*, StringHash) const, bool), asCALL_THISCALL);
    // bool UIElement::HasTag(const String& tag) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "bool HasTag(const String&in) const", asMETHODPR(ProgressBar, HasTag, (const String&) const, bool), asCALL_THISCALL);
    // void UIElement::InsertChild(unsigned index, UIElement* element) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "void InsertChild(uint, UIElement@+)", asMETHODPR(ProgressBar, InsertChild, (unsigned, UIElement*), void), asCALL_THISCALL);
    // bool UIElement::IsChildOf(UIElement* element) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "bool IsChildOf(UIElement@+) const", asMETHODPR(ProgressBar, IsChildOf, (UIElement*) const, bool), asCALL_THISCALL);
    // bool UIElement::IsEditable() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "bool IsEditable() const", asMETHODPR(ProgressBar, IsEditable, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "bool get_editable() const", asMETHODPR(ProgressBar, IsEditable, () const, bool), asCALL_THISCALL);
    // bool UIElement::IsElementEventSender() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "bool IsElementEventSender() const", asMETHODPR(ProgressBar, IsElementEventSender, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "bool get_elementEventSender() const", asMETHODPR(ProgressBar, IsElementEventSender, () const, bool), asCALL_THISCALL);
    // bool UIElement::IsEnabled() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "bool IsEnabled() const", asMETHODPR(ProgressBar, IsEnabled, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "bool get_enabled() const", asMETHODPR(ProgressBar, IsEnabled, () const, bool), asCALL_THISCALL);
    // bool UIElement::IsEnabledSelf() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "bool IsEnabledSelf() const", asMETHODPR(ProgressBar, IsEnabledSelf, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "bool get_enabledSelf() const", asMETHODPR(ProgressBar, IsEnabledSelf, () const, bool), asCALL_THISCALL);
    // bool UIElement::IsFixedHeight() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "bool IsFixedHeight() const", asMETHODPR(ProgressBar, IsFixedHeight, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "bool get_fixedHeight() const", asMETHODPR(ProgressBar, IsFixedHeight, () const, bool), asCALL_THISCALL);
    // bool UIElement::IsFixedSize() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "bool IsFixedSize() const", asMETHODPR(ProgressBar, IsFixedSize, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "bool get_fixedSize() const", asMETHODPR(ProgressBar, IsFixedSize, () const, bool), asCALL_THISCALL);
    // bool UIElement::IsFixedWidth() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "bool IsFixedWidth() const", asMETHODPR(ProgressBar, IsFixedWidth, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "bool get_fixedWidth() const", asMETHODPR(ProgressBar, IsFixedWidth, () const, bool), asCALL_THISCALL);
    // bool UIElement::IsHovering() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "bool IsHovering() const", asMETHODPR(ProgressBar, IsHovering, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "bool get_hovering() const", asMETHODPR(ProgressBar, IsHovering, () const, bool), asCALL_THISCALL);
    // bool UIElement::IsInside(IntVector2 position, bool isScreen) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "bool IsInside(IntVector2, bool)", asMETHODPR(ProgressBar, IsInside, (IntVector2, bool), bool), asCALL_THISCALL);
    // bool UIElement::IsInsideCombined(IntVector2 position, bool isScreen) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "bool IsInsideCombined(IntVector2, bool)", asMETHODPR(ProgressBar, IsInsideCombined, (IntVector2, bool), bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ProgressBar", "bool IsInstanceOf(StringHash) const", asMETHODPR(ProgressBar, IsInstanceOf, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // bool UIElement::IsInternal() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "bool IsInternal() const", asMETHODPR(ProgressBar, IsInternal, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "bool get_internal() const", asMETHODPR(ProgressBar, IsInternal, () const, bool), asCALL_THISCALL);
    // bool UIElement::IsSelected() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "bool IsSelected() const", asMETHODPR(ProgressBar, IsSelected, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "bool get_selected() const", asMETHODPR(ProgressBar, IsSelected, () const, bool), asCALL_THISCALL);
    // bool Serializable::IsTemporary() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ProgressBar", "bool IsTemporary() const", asMETHODPR(ProgressBar, IsTemporary, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "bool get_temporary() const", asMETHODPR(ProgressBar, IsTemporary, () const, bool), asCALL_THISCALL);
    // bool BorderImage::IsTiled() const | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("ProgressBar", "bool IsTiled() const", asMETHODPR(ProgressBar, IsTiled, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "bool get_tiled() const", asMETHODPR(ProgressBar, IsTiled, () const, bool), asCALL_THISCALL);
    // bool UIElement::IsVisible() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "bool IsVisible() const", asMETHODPR(ProgressBar, IsVisible, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "bool get_visible() const", asMETHODPR(ProgressBar, IsVisible, () const, bool), asCALL_THISCALL);
    // bool UIElement::IsVisibleEffective() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "bool IsVisibleEffective() const", asMETHODPR(ProgressBar, IsVisibleEffective, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "bool get_visibleEffective() const", asMETHODPR(ProgressBar, IsVisibleEffective, () const, bool), asCALL_THISCALL);
    // virtual bool UIElement::IsWheelHandler() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "bool IsWheelHandler() const", asMETHODPR(ProgressBar, IsWheelHandler, () const, bool), asCALL_THISCALL);
    // virtual bool UIElement::IsWithinScissor(const IntRect& currentScissor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "bool IsWithinScissor(const IntRect&in)", asMETHODPR(ProgressBar, IsWithinScissor, (const IntRect&), bool), asCALL_THISCALL);
    // virtual bool Serializable::Load(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ProgressBar", "bool Load(Deserializer&)", asMETHODPR(ProgressBar, Load, (Deserializer&), bool), asCALL_THISCALL);
    // virtual UIElement* UIElement::LoadChildXML(const XMLElement& childElem, XMLFile* styleFile) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "UIElement@+ LoadChildXML(const XMLElement&in, XMLFile@+)", asMETHODPR(ProgressBar, LoadChildXML, (const XMLElement&, XMLFile*), UIElement*), asCALL_THISCALL);
    // bool Animatable::LoadJSON(const JSONValue& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ProgressBar", "bool LoadJSON(const JSONValue&in)", asMETHODPR(ProgressBar, LoadJSON, (const JSONValue&), bool), asCALL_THISCALL);
    // bool UIElement::LoadXML(const XMLElement& source) override | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "bool LoadXML(const XMLElement&in)", asMETHODPR(ProgressBar, LoadXML, (const XMLElement&), bool), asCALL_THISCALL);
    // virtual bool UIElement::LoadXML(const XMLElement& source, XMLFile* styleFile) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "bool LoadXML(const XMLElement&in, XMLFile@+)", asMETHODPR(ProgressBar, LoadXML, (const XMLElement&, XMLFile*), bool), asCALL_THISCALL);
    // bool UIElement::LoadXML(Deserializer& source) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "bool LoadXML(Deserializer&)", asMETHODPR(ProgressBar, LoadXML, (Deserializer&), bool), asCALL_THISCALL);
    // virtual void Serializable::MarkNetworkUpdate() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ProgressBar", "void MarkNetworkUpdate()", asMETHODPR(ProgressBar, MarkNetworkUpdate, (), void), asCALL_THISCALL);
    // virtual void UIElement::OnClickBegin(const IntVector2& position, const IntVector2& screenPosition, MouseButton button, MouseButtonFlags buttons, QualifierFlags qualifiers, Cursor* cursor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "void OnClickBegin(const IntVector2&in, const IntVector2&in, MouseButton, MouseButtonFlags, QualifierFlags, Cursor@+)", asMETHODPR(ProgressBar, OnClickBegin, (const IntVector2&, const IntVector2&, MouseButton, MouseButtonFlags, QualifierFlags, Cursor*), void), asCALL_THISCALL);
    // virtual void UIElement::OnClickEnd(const IntVector2& position, const IntVector2& screenPosition, MouseButton button, MouseButtonFlags buttons, QualifierFlags qualifiers, Cursor* cursor, UIElement* beginElement) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "void OnClickEnd(const IntVector2&in, const IntVector2&in, MouseButton, MouseButtonFlags, QualifierFlags, Cursor@+, UIElement@+)", asMETHODPR(ProgressBar, OnClickEnd, (const IntVector2&, const IntVector2&, MouseButton, MouseButtonFlags, QualifierFlags, Cursor*, UIElement*), void), asCALL_THISCALL);
    // virtual void UIElement::OnDoubleClick(const IntVector2& position, const IntVector2& screenPosition, MouseButton button, MouseButtonFlags buttons, QualifierFlags qualifiers, Cursor* cursor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "void OnDoubleClick(const IntVector2&in, const IntVector2&in, MouseButton, MouseButtonFlags, QualifierFlags, Cursor@+)", asMETHODPR(ProgressBar, OnDoubleClick, (const IntVector2&, const IntVector2&, MouseButton, MouseButtonFlags, QualifierFlags, Cursor*), void), asCALL_THISCALL);
    // virtual void UIElement::OnDragBegin(const IntVector2& position, const IntVector2& screenPosition, MouseButtonFlags buttons, QualifierFlags qualifiers, Cursor* cursor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "void OnDragBegin(const IntVector2&in, const IntVector2&in, MouseButtonFlags, QualifierFlags, Cursor@+)", asMETHODPR(ProgressBar, OnDragBegin, (const IntVector2&, const IntVector2&, MouseButtonFlags, QualifierFlags, Cursor*), void), asCALL_THISCALL);
    // virtual void UIElement::OnDragCancel(const IntVector2& position, const IntVector2& screenPosition, MouseButtonFlags dragButtons, MouseButtonFlags cancelButtons, Cursor* cursor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "void OnDragCancel(const IntVector2&in, const IntVector2&in, MouseButtonFlags, MouseButtonFlags, Cursor@+)", asMETHODPR(ProgressBar, OnDragCancel, (const IntVector2&, const IntVector2&, MouseButtonFlags, MouseButtonFlags, Cursor*), void), asCALL_THISCALL);
    // virtual bool UIElement::OnDragDropFinish(UIElement* source) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "bool OnDragDropFinish(UIElement@+)", asMETHODPR(ProgressBar, OnDragDropFinish, (UIElement*), bool), asCALL_THISCALL);
    // virtual bool UIElement::OnDragDropTest(UIElement* source) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "bool OnDragDropTest(UIElement@+)", asMETHODPR(ProgressBar, OnDragDropTest, (UIElement*), bool), asCALL_THISCALL);
    // virtual void UIElement::OnDragEnd(const IntVector2& position, const IntVector2& screenPosition, MouseButtonFlags dragButtons, MouseButtonFlags releaseButtons, Cursor* cursor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "void OnDragEnd(const IntVector2&in, const IntVector2&in, MouseButtonFlags, MouseButtonFlags, Cursor@+)", asMETHODPR(ProgressBar, OnDragEnd, (const IntVector2&, const IntVector2&, MouseButtonFlags, MouseButtonFlags, Cursor*), void), asCALL_THISCALL);
    // virtual void UIElement::OnDragMove(const IntVector2& position, const IntVector2& screenPosition, const IntVector2& deltaPos, MouseButtonFlags buttons, QualifierFlags qualifiers, Cursor* cursor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "void OnDragMove(const IntVector2&in, const IntVector2&in, const IntVector2&in, MouseButtonFlags, QualifierFlags, Cursor@+)", asMETHODPR(ProgressBar, OnDragMove, (const IntVector2&, const IntVector2&, const IntVector2&, MouseButtonFlags, QualifierFlags, Cursor*), void), asCALL_THISCALL);
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ProgressBar", "void OnEvent(Object@+, StringHash, VariantMap&)", asMETHODPR(ProgressBar, OnEvent, (Object*, StringHash, VariantMap&), void), asCALL_THISCALL);
    // virtual void Serializable::OnGetAttribute(const AttributeInfo& attr, Variant& dest) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ProgressBar", "void OnGetAttribute(const AttributeInfo&in, Variant&) const", asMETHODPR(ProgressBar, OnGetAttribute, (const AttributeInfo&, Variant&) const, void), asCALL_THISCALL);
    // virtual void UIElement::OnHover(const IntVector2& position, const IntVector2& screenPosition, MouseButtonFlags buttons, QualifierFlags qualifiers, Cursor* cursor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "void OnHover(const IntVector2&in, const IntVector2&in, MouseButtonFlags, QualifierFlags, Cursor@+)", asMETHODPR(ProgressBar, OnHover, (const IntVector2&, const IntVector2&, MouseButtonFlags, QualifierFlags, Cursor*), void), asCALL_THISCALL);
    // virtual void UIElement::OnIndentSet() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "void OnIndentSet()", asMETHODPR(ProgressBar, OnIndentSet, (), void), asCALL_THISCALL);
    // virtual void UIElement::OnKey(Key key, MouseButtonFlags buttons, QualifierFlags qualifiers) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "void OnKey(Key, MouseButtonFlags, QualifierFlags)", asMETHODPR(ProgressBar, OnKey, (Key, MouseButtonFlags, QualifierFlags), void), asCALL_THISCALL);
    // virtual void UIElement::OnPositionSet(const IntVector2& newPosition) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "void OnPositionSet(const IntVector2&in)", asMETHODPR(ProgressBar, OnPositionSet, (const IntVector2&), void), asCALL_THISCALL);
    // void ProgressBar::OnResize(const IntVector2& newSize, const IntVector2& delta) override | File: ../UI/ProgressBar.h
    engine->RegisterObjectMethod("ProgressBar", "void OnResize(const IntVector2&in, const IntVector2&in)", asMETHODPR(ProgressBar, OnResize, (const IntVector2&, const IntVector2&), void), asCALL_THISCALL);
    // virtual void Serializable::OnSetAttribute(const AttributeInfo& attr, const Variant& src) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ProgressBar", "void OnSetAttribute(const AttributeInfo&in, const Variant&in)", asMETHODPR(ProgressBar, OnSetAttribute, (const AttributeInfo&, const Variant&), void), asCALL_THISCALL);
    // virtual void UIElement::OnSetEditable() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "void OnSetEditable()", asMETHODPR(ProgressBar, OnSetEditable, (), void), asCALL_THISCALL);
    // virtual void UIElement::OnTextInput(const String& text) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "void OnTextInput(const String&in)", asMETHODPR(ProgressBar, OnTextInput, (const String&), void), asCALL_THISCALL);
    // virtual void UIElement::OnWheel(int delta, MouseButtonFlags buttons, QualifierFlags qualifiers) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "void OnWheel(int, MouseButtonFlags, QualifierFlags)", asMETHODPR(ProgressBar, OnWheel, (int, MouseButtonFlags, QualifierFlags), void), asCALL_THISCALL);
    // explicit ProgressBar::ProgressBar(Context* context) | File: ../UI/ProgressBar.h
    engine->RegisterObjectBehaviour("ProgressBar", asBEHAVE_FACTORY, "ProgressBar@+ f()", asFUNCTION(ProgressBar_ProgressBar_Context), asCALL_CDECL);
    // bool Serializable::ReadDeltaUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ProgressBar", "bool ReadDeltaUpdate(Deserializer&)", asMETHODPR(ProgressBar, ReadDeltaUpdate, (Deserializer&), bool), asCALL_THISCALL);
    // bool Serializable::ReadLatestDataUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ProgressBar", "bool ReadLatestDataUpdate(Deserializer&)", asMETHODPR(ProgressBar, ReadLatestDataUpdate, (Deserializer&), bool), asCALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("ProgressBar", "int Refs() const", asMETHODPR(ProgressBar, Refs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "int get_refs() const", asMETHODPR(ProgressBar, Refs, () const, int), asCALL_THISCALL);
    // static void ProgressBar::RegisterObject(Context* context) | File: ../UI/ProgressBar.h
    // Not registered because have @nobind mark
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("ProgressBar", asBEHAVE_RELEASE, "void f()", asMETHODPR(ProgressBar, ReleaseRef, (), void), asCALL_THISCALL);
    // void UIElement::Remove() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "void Remove()", asMETHODPR(ProgressBar, Remove, (), void), asCALL_THISCALL);
    // void UIElement::RemoveAllChildren() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "void RemoveAllChildren()", asMETHODPR(ProgressBar, RemoveAllChildren, (), void), asCALL_THISCALL);
    // void UIElement::RemoveAllTags() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "void RemoveAllTags()", asMETHODPR(ProgressBar, RemoveAllTags, (), void), asCALL_THISCALL);
    // void Animatable::RemoveAttributeAnimation(const String& name) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ProgressBar", "void RemoveAttributeAnimation(const String&in)", asMETHODPR(ProgressBar, RemoveAttributeAnimation, (const String&), void), asCALL_THISCALL);
    // void UIElement::RemoveChild(UIElement* element, unsigned index=0) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "void RemoveChild(UIElement@+, uint = 0)", asMETHODPR(ProgressBar, RemoveChild, (UIElement*, unsigned), void), asCALL_THISCALL);
    // void UIElement::RemoveChildAtIndex(unsigned index) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "void RemoveChildAtIndex(uint)", asMETHODPR(ProgressBar, RemoveChildAtIndex, (unsigned), void), asCALL_THISCALL);
    // void Serializable::RemoveInstanceDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ProgressBar", "void RemoveInstanceDefault()", asMETHODPR(ProgressBar, RemoveInstanceDefault, (), void), asCALL_THISCALL);
    // void Animatable::RemoveObjectAnimation() | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ProgressBar", "void RemoveObjectAnimation()", asMETHODPR(ProgressBar, RemoveObjectAnimation, (), void), asCALL_THISCALL);
    // bool UIElement::RemoveTag(const String& tag) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "bool RemoveTag(const String&in)", asMETHODPR(ProgressBar, RemoveTag, (const String&), bool), asCALL_THISCALL);
    // void UIElement::ResetDeepEnabled() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "void ResetDeepEnabled()", asMETHODPR(ProgressBar, ResetDeepEnabled, (), void), asCALL_THISCALL);
    // void Serializable::ResetToDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ProgressBar", "void ResetToDefault()", asMETHODPR(ProgressBar, ResetToDefault, (), void), asCALL_THISCALL);
    // virtual bool Serializable::Save(Serializer& dest) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ProgressBar", "bool Save(Serializer&) const", asMETHODPR(ProgressBar, Save, (Serializer&) const, bool), asCALL_THISCALL);
    // virtual bool Serializable::SaveDefaultAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ProgressBar", "bool SaveDefaultAttributes() const", asMETHODPR(ProgressBar, SaveDefaultAttributes, () const, bool), asCALL_THISCALL);
    // bool Animatable::SaveJSON(JSONValue& dest) const override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ProgressBar", "bool SaveJSON(JSONValue&) const", asMETHODPR(ProgressBar, SaveJSON, (JSONValue&) const, bool), asCALL_THISCALL);
    // bool UIElement::SaveXML(XMLElement& dest) const override | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "bool SaveXML(XMLElement&) const", asMETHODPR(ProgressBar, SaveXML, (XMLElement&) const, bool), asCALL_THISCALL);
    // bool UIElement::SaveXML(Serializer& dest, const String& indentation="\t") const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "bool SaveXML(Serializer&, const String&in = \"\t\") const", asMETHODPR(ProgressBar, SaveXML, (Serializer&, const String&) const, bool), asCALL_THISCALL);
    // virtual IntVector2 UIElement::ScreenToElement(const IntVector2& screenPosition) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "IntVector2 ScreenToElement(const IntVector2&in)", asMETHODPR(ProgressBar, ScreenToElement, (const IntVector2&), IntVector2), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ProgressBar", "void SendEvent(StringHash)", asMETHODPR(ProgressBar, SendEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ProgressBar", "void SendEvent(StringHash, VariantMap&)", asMETHODPR(ProgressBar, SendEvent, (StringHash, VariantMap&), void), asCALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void UIElement::SetAlignment(HorizontalAlignment hAlign, VerticalAlignment vAlign) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "void SetAlignment(HorizontalAlignment, VerticalAlignment)", asMETHODPR(ProgressBar, SetAlignment, (HorizontalAlignment, VerticalAlignment), void), asCALL_THISCALL);
    // void Animatable::SetAnimationEnabled(bool enable) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ProgressBar", "void SetAnimationEnabled(bool)", asMETHODPR(ProgressBar, SetAnimationEnabled, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "void set_animationEnabled(bool)", asMETHODPR(ProgressBar, SetAnimationEnabled, (bool), void), asCALL_THISCALL);
    // void Animatable::SetAnimationTime(float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ProgressBar", "void SetAnimationTime(float)", asMETHODPR(ProgressBar, SetAnimationTime, (float), void), asCALL_THISCALL);
    // bool Serializable::SetAttribute(unsigned index, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ProgressBar", "bool SetAttribute(uint, const Variant&in)", asMETHODPR(ProgressBar, SetAttribute, (unsigned, const Variant&), bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "bool set_attributes(uint, const Variant&in)", asMETHODPR(ProgressBar, SetAttribute, (unsigned, const Variant&), bool), asCALL_THISCALL);
    // bool Serializable::SetAttribute(const String& name, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ProgressBar", "bool SetAttribute(const String&in, const Variant&in)", asMETHODPR(ProgressBar, SetAttribute, (const String&, const Variant&), bool), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimation(const String& name, ValueAnimation* attributeAnimation, WrapMode wrapMode=WM_LOOP, float speed=1.0f) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ProgressBar", "void SetAttributeAnimation(const String&in, ValueAnimation@+, WrapMode = WM_LOOP, float = 1.0f)", asMETHODPR(ProgressBar, SetAttributeAnimation, (const String&, ValueAnimation*, WrapMode, float), void), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimationSpeed(const String& name, float speed) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ProgressBar", "void SetAttributeAnimationSpeed(const String&in, float)", asMETHODPR(ProgressBar, SetAttributeAnimationSpeed, (const String&, float), void), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimationTime(const String& name, float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ProgressBar", "void SetAttributeAnimationTime(const String&in, float)", asMETHODPR(ProgressBar, SetAttributeAnimationTime, (const String&, float), void), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimationWrapMode(const String& name, WrapMode wrapMode) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ProgressBar", "void SetAttributeAnimationWrapMode(const String&in, WrapMode)", asMETHODPR(ProgressBar, SetAttributeAnimationWrapMode, (const String&, WrapMode), void), asCALL_THISCALL);
    // void BorderImage::SetBlendMode(BlendMode mode) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("ProgressBar", "void SetBlendMode(BlendMode)", asMETHODPR(ProgressBar, SetBlendMode, (BlendMode), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "void set_blendMode(BlendMode)", asMETHODPR(ProgressBar, SetBlendMode, (BlendMode), void), asCALL_THISCALL);
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ProgressBar", "void SetBlockEvents(bool)", asMETHODPR(ProgressBar, SetBlockEvents, (bool), void), asCALL_THISCALL);
    // void BorderImage::SetBorder(const IntRect& rect) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("ProgressBar", "void SetBorder(const IntRect&in)", asMETHODPR(ProgressBar, SetBorder, (const IntRect&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "void set_border(const IntRect&in)", asMETHODPR(ProgressBar, SetBorder, (const IntRect&), void), asCALL_THISCALL);
    // void UIElement::SetBringToBack(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "void SetBringToBack(bool)", asMETHODPR(ProgressBar, SetBringToBack, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "void set_bringToBack(bool)", asMETHODPR(ProgressBar, SetBringToBack, (bool), void), asCALL_THISCALL);
    // void UIElement::SetBringToFront(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "void SetBringToFront(bool)", asMETHODPR(ProgressBar, SetBringToFront, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "void set_bringToFront(bool)", asMETHODPR(ProgressBar, SetBringToFront, (bool), void), asCALL_THISCALL);
    // void UIElement::SetChildOffset(const IntVector2& offset) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "void SetChildOffset(const IntVector2&in)", asMETHODPR(ProgressBar, SetChildOffset, (const IntVector2&), void), asCALL_THISCALL);
    // void UIElement::SetClipBorder(const IntRect& rect) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "void SetClipBorder(const IntRect&in)", asMETHODPR(ProgressBar, SetClipBorder, (const IntRect&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "void set_clipBorder(const IntRect&in)", asMETHODPR(ProgressBar, SetClipBorder, (const IntRect&), void), asCALL_THISCALL);
    // void UIElement::SetClipChildren(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "void SetClipChildren(bool)", asMETHODPR(ProgressBar, SetClipChildren, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "void set_clipChildren(bool)", asMETHODPR(ProgressBar, SetClipChildren, (bool), void), asCALL_THISCALL);
    // void UIElement::SetColor(const Color& color) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "void SetColor(const Color&in)", asMETHODPR(ProgressBar, SetColor, (const Color&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "void set_color(const Color&in)", asMETHODPR(ProgressBar, SetColor, (const Color&), void), asCALL_THISCALL);
    // void UIElement::SetColor(Corner corner, const Color& color) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "void SetColor(Corner, const Color&in)", asMETHODPR(ProgressBar, SetColor, (Corner, const Color&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "void set_colors(Corner, const Color&in)", asMETHODPR(ProgressBar, SetColor, (Corner, const Color&), void), asCALL_THISCALL);
    // void UIElement::SetDeepEnabled(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "void SetDeepEnabled(bool)", asMETHODPR(ProgressBar, SetDeepEnabled, (bool), void), asCALL_THISCALL);
    // void UIElement::SetDefaultStyle(XMLFile* style) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "void SetDefaultStyle(XMLFile@+)", asMETHODPR(ProgressBar, SetDefaultStyle, (XMLFile*), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "void set_defaultStyle(XMLFile@+)", asMETHODPR(ProgressBar, SetDefaultStyle, (XMLFile*), void), asCALL_THISCALL);
    // void BorderImage::SetDisabledOffset(const IntVector2& offset) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("ProgressBar", "void SetDisabledOffset(const IntVector2&in)", asMETHODPR(ProgressBar, SetDisabledOffset, (const IntVector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "void set_disabledOffset(const IntVector2&in)", asMETHODPR(ProgressBar, SetDisabledOffset, (const IntVector2&), void), asCALL_THISCALL);
    // void BorderImage::SetDisabledOffset(int x, int y) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("ProgressBar", "void SetDisabledOffset(int, int)", asMETHODPR(ProgressBar, SetDisabledOffset, (int, int), void), asCALL_THISCALL);
    // void UIElement::SetDragDropMode(DragAndDropModeFlags mode) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "void SetDragDropMode(DragAndDropModeFlags)", asMETHODPR(ProgressBar, SetDragDropMode, (DragAndDropModeFlags), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "void set_dragDropMode(DragAndDropModeFlags)", asMETHODPR(ProgressBar, SetDragDropMode, (DragAndDropModeFlags), void), asCALL_THISCALL);
    // void UIElement::SetEditable(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "void SetEditable(bool)", asMETHODPR(ProgressBar, SetEditable, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "void set_editable(bool)", asMETHODPR(ProgressBar, SetEditable, (bool), void), asCALL_THISCALL);
    // void UIElement::SetElementEventSender(bool flag) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "void SetElementEventSender(bool)", asMETHODPR(ProgressBar, SetElementEventSender, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "void set_elementEventSender(bool)", asMETHODPR(ProgressBar, SetElementEventSender, (bool), void), asCALL_THISCALL);
    // void UIElement::SetEnableAnchor(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "void SetEnableAnchor(bool)", asMETHODPR(ProgressBar, SetEnableAnchor, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "void set_enableAnchor(bool)", asMETHODPR(ProgressBar, SetEnableAnchor, (bool), void), asCALL_THISCALL);
    // void UIElement::SetEnabled(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "void SetEnabled(bool)", asMETHODPR(ProgressBar, SetEnabled, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "void set_enabled(bool)", asMETHODPR(ProgressBar, SetEnabled, (bool), void), asCALL_THISCALL);
    // void UIElement::SetEnabledRecursive(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "void SetEnabledRecursive(bool)", asMETHODPR(ProgressBar, SetEnabledRecursive, (bool), void), asCALL_THISCALL);
    // void UIElement::SetFixedHeight(int height) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "void SetFixedHeight(int)", asMETHODPR(ProgressBar, SetFixedHeight, (int), void), asCALL_THISCALL);
    // void UIElement::SetFixedSize(const IntVector2& size) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "void SetFixedSize(const IntVector2&in)", asMETHODPR(ProgressBar, SetFixedSize, (const IntVector2&), void), asCALL_THISCALL);
    // void UIElement::SetFixedSize(int width, int height) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "void SetFixedSize(int, int)", asMETHODPR(ProgressBar, SetFixedSize, (int, int), void), asCALL_THISCALL);
    // void UIElement::SetFixedWidth(int width) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "void SetFixedWidth(int)", asMETHODPR(ProgressBar, SetFixedWidth, (int), void), asCALL_THISCALL);
    // void UIElement::SetFocus(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "void SetFocus(bool)", asMETHODPR(ProgressBar, SetFocus, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "void set_focus(bool)", asMETHODPR(ProgressBar, SetFocus, (bool), void), asCALL_THISCALL);
    // void UIElement::SetFocusMode(FocusMode mode) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "void SetFocusMode(FocusMode)", asMETHODPR(ProgressBar, SetFocusMode, (FocusMode), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "void set_focusMode(FocusMode)", asMETHODPR(ProgressBar, SetFocusMode, (FocusMode), void), asCALL_THISCALL);
    // void BorderImage::SetFullImageRect() | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("ProgressBar", "void SetFullImageRect()", asMETHODPR(ProgressBar, SetFullImageRect, (), void), asCALL_THISCALL);
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ProgressBar", "void SetGlobalVar(StringHash, const Variant&in)", asMETHODPR(ProgressBar, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "void set_globalVar(StringHash, const Variant&in)", asMETHODPR(ProgressBar, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    // void UIElement::SetHeight(int height) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "void SetHeight(int)", asMETHODPR(ProgressBar, SetHeight, (int), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "void set_height(int)", asMETHODPR(ProgressBar, SetHeight, (int), void), asCALL_THISCALL);
    // void UIElement::SetHorizontalAlignment(HorizontalAlignment align) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "void SetHorizontalAlignment(HorizontalAlignment)", asMETHODPR(ProgressBar, SetHorizontalAlignment, (HorizontalAlignment), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "void set_horizontalAlignment(HorizontalAlignment)", asMETHODPR(ProgressBar, SetHorizontalAlignment, (HorizontalAlignment), void), asCALL_THISCALL);
    // void UIElement::SetHovering(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "void SetHovering(bool)", asMETHODPR(ProgressBar, SetHovering, (bool), void), asCALL_THISCALL);
    // void BorderImage::SetHoverOffset(const IntVector2& offset) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("ProgressBar", "void SetHoverOffset(const IntVector2&in)", asMETHODPR(ProgressBar, SetHoverOffset, (const IntVector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "void set_hoverOffset(const IntVector2&in)", asMETHODPR(ProgressBar, SetHoverOffset, (const IntVector2&), void), asCALL_THISCALL);
    // void BorderImage::SetHoverOffset(int x, int y) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("ProgressBar", "void SetHoverOffset(int, int)", asMETHODPR(ProgressBar, SetHoverOffset, (int, int), void), asCALL_THISCALL);
    // void BorderImage::SetImageBorder(const IntRect& rect) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("ProgressBar", "void SetImageBorder(const IntRect&in)", asMETHODPR(ProgressBar, SetImageBorder, (const IntRect&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "void set_imageBorder(const IntRect&in)", asMETHODPR(ProgressBar, SetImageBorder, (const IntRect&), void), asCALL_THISCALL);
    // void BorderImage::SetImageRect(const IntRect& rect) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("ProgressBar", "void SetImageRect(const IntRect&in)", asMETHODPR(ProgressBar, SetImageRect, (const IntRect&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "void set_imageRect(const IntRect&in)", asMETHODPR(ProgressBar, SetImageRect, (const IntRect&), void), asCALL_THISCALL);
    // void UIElement::SetIndent(int indent) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "void SetIndent(int)", asMETHODPR(ProgressBar, SetIndent, (int), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "void set_indent(int)", asMETHODPR(ProgressBar, SetIndent, (int), void), asCALL_THISCALL);
    // void UIElement::SetIndentSpacing(int indentSpacing) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "void SetIndentSpacing(int)", asMETHODPR(ProgressBar, SetIndentSpacing, (int), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "void set_indentSpacing(int)", asMETHODPR(ProgressBar, SetIndentSpacing, (int), void), asCALL_THISCALL);
    // void Serializable::SetInstanceDefault(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ProgressBar", "void SetInstanceDefault(bool)", asMETHODPR(ProgressBar, SetInstanceDefault, (bool), void), asCALL_THISCALL);
    // void Serializable::SetInterceptNetworkUpdate(const String& attributeName, bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ProgressBar", "void SetInterceptNetworkUpdate(const String&in, bool)", asMETHODPR(ProgressBar, SetInterceptNetworkUpdate, (const String&, bool), void), asCALL_THISCALL);
    // void UIElement::SetInternal(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "void SetInternal(bool)", asMETHODPR(ProgressBar, SetInternal, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "void set_internal(bool)", asMETHODPR(ProgressBar, SetInternal, (bool), void), asCALL_THISCALL);
    // void UIElement::SetLayout(LayoutMode mode, int spacing=0, const IntRect& border=IntRect::ZERO) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "void SetLayout(LayoutMode, int = 0, const IntRect&in = IntRect::ZERO)", asMETHODPR(ProgressBar, SetLayout, (LayoutMode, int, const IntRect&), void), asCALL_THISCALL);
    // void UIElement::SetLayoutBorder(const IntRect& border) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "void SetLayoutBorder(const IntRect&in)", asMETHODPR(ProgressBar, SetLayoutBorder, (const IntRect&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "void set_layoutBorder(const IntRect&in)", asMETHODPR(ProgressBar, SetLayoutBorder, (const IntRect&), void), asCALL_THISCALL);
    // void UIElement::SetLayoutFlexScale(const Vector2& scale) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "void SetLayoutFlexScale(const Vector2&in)", asMETHODPR(ProgressBar, SetLayoutFlexScale, (const Vector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "void set_layoutFlexScale(const Vector2&in)", asMETHODPR(ProgressBar, SetLayoutFlexScale, (const Vector2&), void), asCALL_THISCALL);
    // void UIElement::SetLayoutMode(LayoutMode mode) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "void SetLayoutMode(LayoutMode)", asMETHODPR(ProgressBar, SetLayoutMode, (LayoutMode), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "void set_layoutMode(LayoutMode)", asMETHODPR(ProgressBar, SetLayoutMode, (LayoutMode), void), asCALL_THISCALL);
    // void UIElement::SetLayoutSpacing(int spacing) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "void SetLayoutSpacing(int)", asMETHODPR(ProgressBar, SetLayoutSpacing, (int), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "void set_layoutSpacing(int)", asMETHODPR(ProgressBar, SetLayoutSpacing, (int), void), asCALL_THISCALL);
    // void ProgressBar::SetLoadingPercentStyle(const String& style) | File: ../UI/ProgressBar.h
    engine->RegisterObjectMethod("ProgressBar", "void SetLoadingPercentStyle(const String&in)", asMETHODPR(ProgressBar, SetLoadingPercentStyle, (const String&), void), asCALL_THISCALL);
    // void BorderImage::SetMaterial(Material* material) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("ProgressBar", "void SetMaterial(Material@+)", asMETHODPR(ProgressBar, SetMaterial, (Material*), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "void set_material(Material@+)", asMETHODPR(ProgressBar, SetMaterial, (Material*), void), asCALL_THISCALL);
    // void BorderImage::SetMaterialAttr(const ResourceRef& value) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("ProgressBar", "void SetMaterialAttr(const ResourceRef&in)", asMETHODPR(ProgressBar, SetMaterialAttr, (const ResourceRef&), void), asCALL_THISCALL);
    // void UIElement::SetMaxAnchor(const Vector2& anchor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "void SetMaxAnchor(const Vector2&in)", asMETHODPR(ProgressBar, SetMaxAnchor, (const Vector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "void set_maxAnchor(const Vector2&in)", asMETHODPR(ProgressBar, SetMaxAnchor, (const Vector2&), void), asCALL_THISCALL);
    // void UIElement::SetMaxAnchor(float x, float y) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "void SetMaxAnchor(float, float)", asMETHODPR(ProgressBar, SetMaxAnchor, (float, float), void), asCALL_THISCALL);
    // void UIElement::SetMaxHeight(int height) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "void SetMaxHeight(int)", asMETHODPR(ProgressBar, SetMaxHeight, (int), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "void set_maxHeight(int)", asMETHODPR(ProgressBar, SetMaxHeight, (int), void), asCALL_THISCALL);
    // void UIElement::SetMaxOffset(const IntVector2& offset) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "void SetMaxOffset(const IntVector2&in)", asMETHODPR(ProgressBar, SetMaxOffset, (const IntVector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "void set_maxOffset(const IntVector2&in)", asMETHODPR(ProgressBar, SetMaxOffset, (const IntVector2&), void), asCALL_THISCALL);
    // void UIElement::SetMaxSize(const IntVector2& maxSize) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "void SetMaxSize(const IntVector2&in)", asMETHODPR(ProgressBar, SetMaxSize, (const IntVector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "void set_maxSize(const IntVector2&in)", asMETHODPR(ProgressBar, SetMaxSize, (const IntVector2&), void), asCALL_THISCALL);
    // void UIElement::SetMaxSize(int width, int height) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "void SetMaxSize(int, int)", asMETHODPR(ProgressBar, SetMaxSize, (int, int), void), asCALL_THISCALL);
    // void UIElement::SetMaxWidth(int width) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "void SetMaxWidth(int)", asMETHODPR(ProgressBar, SetMaxWidth, (int), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "void set_maxWidth(int)", asMETHODPR(ProgressBar, SetMaxWidth, (int), void), asCALL_THISCALL);
    // void UIElement::SetMinAnchor(const Vector2& anchor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "void SetMinAnchor(const Vector2&in)", asMETHODPR(ProgressBar, SetMinAnchor, (const Vector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "void set_minAnchor(const Vector2&in)", asMETHODPR(ProgressBar, SetMinAnchor, (const Vector2&), void), asCALL_THISCALL);
    // void UIElement::SetMinAnchor(float x, float y) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "void SetMinAnchor(float, float)", asMETHODPR(ProgressBar, SetMinAnchor, (float, float), void), asCALL_THISCALL);
    // void UIElement::SetMinHeight(int height) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "void SetMinHeight(int)", asMETHODPR(ProgressBar, SetMinHeight, (int), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "void set_minHeight(int)", asMETHODPR(ProgressBar, SetMinHeight, (int), void), asCALL_THISCALL);
    // void UIElement::SetMinOffset(const IntVector2& offset) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "void SetMinOffset(const IntVector2&in)", asMETHODPR(ProgressBar, SetMinOffset, (const IntVector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "void set_minOffset(const IntVector2&in)", asMETHODPR(ProgressBar, SetMinOffset, (const IntVector2&), void), asCALL_THISCALL);
    // void UIElement::SetMinSize(const IntVector2& minSize) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "void SetMinSize(const IntVector2&in)", asMETHODPR(ProgressBar, SetMinSize, (const IntVector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "void set_minSize(const IntVector2&in)", asMETHODPR(ProgressBar, SetMinSize, (const IntVector2&), void), asCALL_THISCALL);
    // void UIElement::SetMinSize(int width, int height) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "void SetMinSize(int, int)", asMETHODPR(ProgressBar, SetMinSize, (int, int), void), asCALL_THISCALL);
    // void UIElement::SetMinWidth(int width) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "void SetMinWidth(int)", asMETHODPR(ProgressBar, SetMinWidth, (int), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "void set_minWidth(int)", asMETHODPR(ProgressBar, SetMinWidth, (int), void), asCALL_THISCALL);
    // void UIElement::SetName(const String& name) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "void SetName(const String&in)", asMETHODPR(ProgressBar, SetName, (const String&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "void set_name(const String&in)", asMETHODPR(ProgressBar, SetName, (const String&), void), asCALL_THISCALL);
    // void Animatable::SetObjectAnimation(ObjectAnimation* objectAnimation) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ProgressBar", "void SetObjectAnimation(ObjectAnimation@+)", asMETHODPR(ProgressBar, SetObjectAnimation, (ObjectAnimation*), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "void set_objectAnimation(ObjectAnimation@+)", asMETHODPR(ProgressBar, SetObjectAnimation, (ObjectAnimation*), void), asCALL_THISCALL);
    // void Animatable::SetObjectAnimationAttr(const ResourceRef& value) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ProgressBar", "void SetObjectAnimationAttr(const ResourceRef&in)", asMETHODPR(ProgressBar, SetObjectAnimationAttr, (const ResourceRef&), void), asCALL_THISCALL);
    // void UIElement::SetOpacity(float opacity) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "void SetOpacity(float)", asMETHODPR(ProgressBar, SetOpacity, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "void set_opacity(float)", asMETHODPR(ProgressBar, SetOpacity, (float), void), asCALL_THISCALL);
    // void ProgressBar::SetOrientation(Orientation orientation) | File: ../UI/ProgressBar.h
    engine->RegisterObjectMethod("ProgressBar", "void SetOrientation(Orientation)", asMETHODPR(ProgressBar, SetOrientation, (Orientation), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "void set_orientation(Orientation)", asMETHODPR(ProgressBar, SetOrientation, (Orientation), void), asCALL_THISCALL);
    // void UIElement::SetParent(UIElement* parent, unsigned index=M_MAX_UNSIGNED) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "void SetParent(UIElement@+, uint = M_MAX_UNSIGNED)", asMETHODPR(ProgressBar, SetParent, (UIElement*, unsigned), void), asCALL_THISCALL);
    // void UIElement::SetPivot(const Vector2& pivot) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "void SetPivot(const Vector2&in)", asMETHODPR(ProgressBar, SetPivot, (const Vector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "void set_pivot(const Vector2&in)", asMETHODPR(ProgressBar, SetPivot, (const Vector2&), void), asCALL_THISCALL);
    // void UIElement::SetPivot(float x, float y) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "void SetPivot(float, float)", asMETHODPR(ProgressBar, SetPivot, (float, float), void), asCALL_THISCALL);
    // void UIElement::SetPosition(const IntVector2& position) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "void SetPosition(const IntVector2&in)", asMETHODPR(ProgressBar, SetPosition, (const IntVector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "void set_position(const IntVector2&in)", asMETHODPR(ProgressBar, SetPosition, (const IntVector2&), void), asCALL_THISCALL);
    // void UIElement::SetPosition(int x, int y) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "void SetPosition(int, int)", asMETHODPR(ProgressBar, SetPosition, (int, int), void), asCALL_THISCALL);
    // void UIElement::SetPriority(int priority) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "void SetPriority(int)", asMETHODPR(ProgressBar, SetPriority, (int), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "void set_priority(int)", asMETHODPR(ProgressBar, SetPriority, (int), void), asCALL_THISCALL);
    // void ProgressBar::SetRange(float range) | File: ../UI/ProgressBar.h
    engine->RegisterObjectMethod("ProgressBar", "void SetRange(float)", asMETHODPR(ProgressBar, SetRange, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "void set_range(float)", asMETHODPR(ProgressBar, SetRange, (float), void), asCALL_THISCALL);
    // void UIElement::SetRenderTexture(Texture2D* texture) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "void SetRenderTexture(Texture2D@+)", asMETHODPR(ProgressBar, SetRenderTexture, (Texture2D*), void), asCALL_THISCALL);
    // void UIElement::SetSelected(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "void SetSelected(bool)", asMETHODPR(ProgressBar, SetSelected, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "void set_selected(bool)", asMETHODPR(ProgressBar, SetSelected, (bool), void), asCALL_THISCALL);
    // void ProgressBar::SetShowPercentText(bool enable) | File: ../UI/ProgressBar.h
    engine->RegisterObjectMethod("ProgressBar", "void SetShowPercentText(bool)", asMETHODPR(ProgressBar, SetShowPercentText, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "void set_showPercentText(bool)", asMETHODPR(ProgressBar, SetShowPercentText, (bool), void), asCALL_THISCALL);
    // void UIElement::SetSize(const IntVector2& size) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "void SetSize(const IntVector2&in)", asMETHODPR(ProgressBar, SetSize, (const IntVector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "void set_size(const IntVector2&in)", asMETHODPR(ProgressBar, SetSize, (const IntVector2&), void), asCALL_THISCALL);
    // void UIElement::SetSize(int width, int height) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "void SetSize(int, int)", asMETHODPR(ProgressBar, SetSize, (int, int), void), asCALL_THISCALL);
    // void UIElement::SetSortChildren(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "void SetSortChildren(bool)", asMETHODPR(ProgressBar, SetSortChildren, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "void set_sortChildren(bool)", asMETHODPR(ProgressBar, SetSortChildren, (bool), void), asCALL_THISCALL);
    // bool UIElement::SetStyle(const String& styleName, XMLFile* file=nullptr) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "bool SetStyle(const String&in, XMLFile@+ = null)", asMETHODPR(ProgressBar, SetStyle, (const String&, XMLFile*), bool), asCALL_THISCALL);
    // bool UIElement::SetStyle(const XMLElement& element) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "bool SetStyle(const XMLElement&in)", asMETHODPR(ProgressBar, SetStyle, (const XMLElement&), bool), asCALL_THISCALL);
    // bool UIElement::SetStyleAuto(XMLFile* file=nullptr) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "bool SetStyleAuto(XMLFile@+ = null)", asMETHODPR(ProgressBar, SetStyleAuto, (XMLFile*), bool), asCALL_THISCALL);
    // void UIElement::SetTags(const StringVector& tags) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "void SetTags(Array<String>@+)", asFUNCTION(ProgressBar_SetTags_StringVector), asCALL_CDECL_OBJFIRST);
    // void Serializable::SetTemporary(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ProgressBar", "void SetTemporary(bool)", asMETHODPR(ProgressBar, SetTemporary, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "void set_temporary(bool)", asMETHODPR(ProgressBar, SetTemporary, (bool), void), asCALL_THISCALL);
    // void BorderImage::SetTexture(Texture* texture) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("ProgressBar", "void SetTexture(Texture@+)", asMETHODPR(ProgressBar, SetTexture, (Texture*), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "void set_texture(Texture@+)", asMETHODPR(ProgressBar, SetTexture, (Texture*), void), asCALL_THISCALL);
    // void BorderImage::SetTextureAttr(const ResourceRef& value) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("ProgressBar", "void SetTextureAttr(const ResourceRef&in)", asMETHODPR(ProgressBar, SetTextureAttr, (const ResourceRef&), void), asCALL_THISCALL);
    // void BorderImage::SetTiled(bool enable) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("ProgressBar", "void SetTiled(bool)", asMETHODPR(ProgressBar, SetTiled, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "void set_tiled(bool)", asMETHODPR(ProgressBar, SetTiled, (bool), void), asCALL_THISCALL);
    // void UIElement::SetTraversalMode(TraversalMode traversalMode) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "void SetTraversalMode(TraversalMode)", asMETHODPR(ProgressBar, SetTraversalMode, (TraversalMode), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "void set_traversalMode(TraversalMode)", asMETHODPR(ProgressBar, SetTraversalMode, (TraversalMode), void), asCALL_THISCALL);
    // void UIElement::SetUseDerivedOpacity(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "void SetUseDerivedOpacity(bool)", asMETHODPR(ProgressBar, SetUseDerivedOpacity, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "void set_useDerivedOpacity(bool)", asMETHODPR(ProgressBar, SetUseDerivedOpacity, (bool), void), asCALL_THISCALL);
    // void ProgressBar::SetValue(float value) | File: ../UI/ProgressBar.h
    engine->RegisterObjectMethod("ProgressBar", "void SetValue(float)", asMETHODPR(ProgressBar, SetValue, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "void set_value(float)", asMETHODPR(ProgressBar, SetValue, (float), void), asCALL_THISCALL);
    // void UIElement::SetVar(StringHash key, const Variant& value) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "void SetVar(StringHash, const Variant&in)", asMETHODPR(ProgressBar, SetVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    // void UIElement::SetVerticalAlignment(VerticalAlignment align) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "void SetVerticalAlignment(VerticalAlignment)", asMETHODPR(ProgressBar, SetVerticalAlignment, (VerticalAlignment), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "void set_verticalAlignment(VerticalAlignment)", asMETHODPR(ProgressBar, SetVerticalAlignment, (VerticalAlignment), void), asCALL_THISCALL);
    // void UIElement::SetVisible(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "void SetVisible(bool)", asMETHODPR(ProgressBar, SetVisible, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "void set_visible(bool)", asMETHODPR(ProgressBar, SetVisible, (bool), void), asCALL_THISCALL);
    // void UIElement::SetWidth(int width) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "void SetWidth(int)", asMETHODPR(ProgressBar, SetWidth, (int), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "void set_width(int)", asMETHODPR(ProgressBar, SetWidth, (int), void), asCALL_THISCALL);
    // void UIElement::SortChildren() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "void SortChildren()", asMETHODPR(ProgressBar, SortChildren, (), void), asCALL_THISCALL);
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod("ProgressBar", "void UnsubscribeFromAllEvents()", asMETHODPR(ProgressBar, UnsubscribeFromAllEvents, (), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ProgressBar", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", asFUNCTION(ProgressBar_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), asCALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ProgressBar", "void UnsubscribeFromEvent(StringHash)", asMETHODPR(ProgressBar, UnsubscribeFromEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ProgressBar", "void UnsubscribeFromEvent(Object@+, StringHash)", asMETHODPR(ProgressBar, UnsubscribeFromEvent, (Object*, StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ProgressBar", "void UnsubscribeFromEvents(Object@+)", asMETHODPR(ProgressBar, UnsubscribeFromEvents, (Object*), void), asCALL_THISCALL);
    // virtual void UIElement::Update(float timeStep) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "void Update(float)", asMETHODPR(ProgressBar, Update, (float), void), asCALL_THISCALL);
    // void UIElement::UpdateLayout() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ProgressBar", "void UpdateLayout()", asMETHODPR(ProgressBar, UpdateLayout, (), void), asCALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("ProgressBar", "int WeakRefs() const", asMETHODPR(ProgressBar, WeakRefs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("ProgressBar", "int get_weakRefs() const", asMETHODPR(ProgressBar, WeakRefs, () const, int), asCALL_THISCALL);
    // void Serializable::WriteDeltaUpdate(Serializer& dest, const DirtyBits& attributeBits, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ProgressBar", "void WriteDeltaUpdate(Serializer&, const DirtyBits&in, uint8)", asMETHODPR(ProgressBar, WriteDeltaUpdate, (Serializer&, const DirtyBits&, unsigned char), void), asCALL_THISCALL);
    // void Serializable::WriteInitialDeltaUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ProgressBar", "void WriteInitialDeltaUpdate(Serializer&, uint8)", asMETHODPR(ProgressBar, WriteInitialDeltaUpdate, (Serializer&, unsigned char), void), asCALL_THISCALL);
    // void Serializable::WriteLatestDataUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ProgressBar", "void WriteLatestDataUpdate(Serializer&, uint8)", asMETHODPR(ProgressBar, WriteLatestDataUpdate, (Serializer&, unsigned char), void), asCALL_THISCALL);
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
    engine->RegisterObjectBehaviour("PropertySet2D", asBEHAVE_ADDREF, "void f()", asMETHODPR(PropertySet2D, AddRef, (), void), asCALL_THISCALL);
    // const String& PropertySet2D::GetProperty(const String& name) const | File: ../Urho2D/TileMapDefs2D.h
    engine->RegisterObjectMethod("PropertySet2D", "const String& GetProperty(const String&in) const", asMETHODPR(PropertySet2D, GetProperty, (const String&) const, const String&), asCALL_THISCALL);
    // bool PropertySet2D::HasProperty(const String& name) const | File: ../Urho2D/TileMapDefs2D.h
    engine->RegisterObjectMethod("PropertySet2D", "bool HasProperty(const String&in) const", asMETHODPR(PropertySet2D, HasProperty, (const String&) const, bool), asCALL_THISCALL);
    // void PropertySet2D::Load(const XMLElement& element) | File: ../Urho2D/TileMapDefs2D.h
    engine->RegisterObjectMethod("PropertySet2D", "void Load(const XMLElement&in)", asMETHODPR(PropertySet2D, Load, (const XMLElement&), void), asCALL_THISCALL);
    // PropertySet2D::PropertySet2D() | File: ../Urho2D/TileMapDefs2D.h
    engine->RegisterObjectBehaviour("PropertySet2D", asBEHAVE_FACTORY, "PropertySet2D@+ f()", asFUNCTION(PropertySet2D_PropertySet2D_void), asCALL_CDECL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("PropertySet2D", "int Refs() const", asMETHODPR(PropertySet2D, Refs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("PropertySet2D", "int get_refs() const", asMETHODPR(PropertySet2D, Refs, () const, int), asCALL_THISCALL);
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("PropertySet2D", asBEHAVE_RELEASE, "void f()", asMETHODPR(PropertySet2D, ReleaseRef, (), void), asCALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("PropertySet2D", "int WeakRefs() const", asMETHODPR(PropertySet2D, WeakRefs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("PropertySet2D", "int get_weakRefs() const", asMETHODPR(PropertySet2D, WeakRefs, () const, int), asCALL_THISCALL);
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
