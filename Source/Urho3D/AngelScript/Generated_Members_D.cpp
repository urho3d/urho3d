// DO NOT EDIT. This file is generated

#include "../Precompiled.h"
#include "../AngelScript/APITemplates.h"

#include "../AngelScript/GeneratedIncludes.h"
#include "../AngelScript/Manual.h"

namespace Urho3D
{

void FakeAddRef(void* ptr);
void FakeReleaseRef(void* ptr);

#ifdef URHO3D_DATABASE
// explicit Database::Database(Context* context) | File: ../Database/Database.h
static Database* Database_Database_Context()
{
    return new Database(GetScriptContext());
}
#endif

#ifdef URHO3D_DATABASE
// void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
static void Database_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool(Database* ptr, CScriptArray* exceptions_conv, bool onlyUserData)
{
    PODVector<StringHash> exceptions = ArrayToPODVector<StringHash>(exceptions_conv);
    ptr->UnsubscribeFromAllEventsExcept(exceptions, onlyUserData);
}
#endif

// explicit DebugHud::DebugHud(Context* context) | File: ../Engine/DebugHud.h
static DebugHud* DebugHud_DebugHud_Context()
{
    return new DebugHud(GetScriptContext());
}

// void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
static void DebugHud_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool(DebugHud* ptr, CScriptArray* exceptions_conv, bool onlyUserData)
{
    PODVector<StringHash> exceptions = ArrayToPODVector<StringHash>(exceptions_conv);
    ptr->UnsubscribeFromAllEventsExcept(exceptions, onlyUserData);
}

// explicit DebugRenderer::DebugRenderer(Context* context) | File: ../Graphics/DebugRenderer.h
static DebugRenderer* DebugRenderer_DebugRenderer_Context()
{
    return new DebugRenderer(GetScriptContext());
}

// void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
static void DebugRenderer_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool(DebugRenderer* ptr, CScriptArray* exceptions_conv, bool onlyUserData)
{
    PODVector<StringHash> exceptions = ArrayToPODVector<StringHash>(exceptions_conv);
    ptr->UnsubscribeFromAllEventsExcept(exceptions, onlyUserData);
}

// explicit DecalSet::DecalSet(Context* context) | File: ../Graphics/DecalSet.h
static DecalSet* DecalSet_DecalSet_Context()
{
    return new DecalSet(GetScriptContext());
}

// const PODVector<Light*>& Drawable::GetLights() const | File: ../Graphics/Drawable.h
static CScriptArray* DecalSet_GetLights_void(DecalSet* ptr)
{
    const PODVector<Light*>& result = ptr->GetLights();
    return VectorToHandleArray(result, "Array<Light@>");
}

// const PODVector<Light*>& Drawable::GetVertexLights() const | File: ../Graphics/Drawable.h
static CScriptArray* DecalSet_GetVertexLights_void(DecalSet* ptr)
{
    const PODVector<Light*>& result = ptr->GetVertexLights();
    return VectorToHandleArray(result, "Array<Light@>");
}

// void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
static void DecalSet_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool(DecalSet* ptr, CScriptArray* exceptions_conv, bool onlyUserData)
{
    PODVector<StringHash> exceptions = ArrayToPODVector<StringHash>(exceptions_conv);
    ptr->UnsubscribeFromAllEventsExcept(exceptions, onlyUserData);
}

// StringVector Deserializer::ReadStringVector() | File: ../IO/Deserializer.h
static CScriptArray* Deserializer_ReadStringVector_void(Deserializer* ptr)
{
    StringVector result = ptr->ReadStringVector();
    return VectorToArray<String>(result, "Array<String>");
}

// const PODVector<Light*>& Drawable::GetLights() const | File: ../Graphics/Drawable.h
static CScriptArray* Drawable_GetLights_void(Drawable* ptr)
{
    const PODVector<Light*>& result = ptr->GetLights();
    return VectorToHandleArray(result, "Array<Light@>");
}

// const PODVector<Light*>& Drawable::GetVertexLights() const | File: ../Graphics/Drawable.h
static CScriptArray* Drawable_GetVertexLights_void(Drawable* ptr)
{
    const PODVector<Light*>& result = ptr->GetVertexLights();
    return VectorToHandleArray(result, "Array<Light@>");
}

// void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
static void Drawable_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool(Drawable* ptr, CScriptArray* exceptions_conv, bool onlyUserData)
{
    PODVector<StringHash> exceptions = ArrayToPODVector<StringHash>(exceptions_conv);
    ptr->UnsubscribeFromAllEventsExcept(exceptions, onlyUserData);
}

#ifdef URHO3D_URHO2D
// const PODVector<Light*>& Drawable::GetLights() const | File: ../Graphics/Drawable.h
static CScriptArray* Drawable2D_GetLights_void(Drawable2D* ptr)
{
    const PODVector<Light*>& result = ptr->GetLights();
    return VectorToHandleArray(result, "Array<Light@>");
}
#endif

#ifdef URHO3D_URHO2D
// const PODVector<Light*>& Drawable::GetVertexLights() const | File: ../Graphics/Drawable.h
static CScriptArray* Drawable2D_GetVertexLights_void(Drawable2D* ptr)
{
    const PODVector<Light*>& result = ptr->GetVertexLights();
    return VectorToHandleArray(result, "Array<Light@>");
}
#endif

#ifdef URHO3D_URHO2D
// void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
static void Drawable2D_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool(Drawable2D* ptr, CScriptArray* exceptions_conv, bool onlyUserData)
{
    PODVector<StringHash> exceptions = ArrayToPODVector<StringHash>(exceptions_conv);
    ptr->UnsubscribeFromAllEventsExcept(exceptions, onlyUserData);
}
#endif

// void UIElement::AddTags(const StringVector& tags) | File: ../UI/UIElement.h
static void DropDownList_AddTags_StringVector(DropDownList* ptr, CScriptArray* tags_conv)
{
    StringVector tags = ArrayToVector<String>(tags_conv);
    ptr->AddTags(tags);
}

// explicit DropDownList::DropDownList(Context* context) | File: ../UI/DropDownList.h
static DropDownList* DropDownList_DropDownList_Context()
{
    return new DropDownList(GetScriptContext());
}

// const Vector<SharedPtr<UIElement>>& UIElement::GetChildren() const | File: ../UI/UIElement.h
static CScriptArray* DropDownList_GetChildren_void(DropDownList* ptr)
{
    const Vector<SharedPtr<UIElement>>& result = ptr->GetChildren();
    return VectorToHandleArray(result, "Array<UIElement@>");
}

// PODVector<UIElement*> UIElement::GetChildren(bool recursive) const | File: ../UI/UIElement.h
static CScriptArray* DropDownList_GetChildren_bool(DropDownList* ptr, bool recursive)
{
    PODVector<UIElement*> result = ptr->GetChildren(recursive);
    return VectorToHandleArray(result, "Array<UIElement@>");
}

// PODVector<UIElement*> UIElement::GetChildrenWithTag(const String& tag, bool recursive=false) const | File: ../UI/UIElement.h
static CScriptArray* DropDownList_GetChildrenWithTag_String_bool(DropDownList* ptr, const String& tag, bool recursive)
{
    PODVector<UIElement*> result = ptr->GetChildrenWithTag(tag, recursive);
    return VectorToHandleArray(result, "Array<UIElement@>");
}

// PODVector<UIElement*> DropDownList::GetItems() const | File: ../UI/DropDownList.h
static CScriptArray* DropDownList_GetItems_void(DropDownList* ptr)
{
    PODVector<UIElement*> result = ptr->GetItems();
    return VectorToHandleArray(result, "Array<UIElement@>");
}

// const StringVector& UIElement::GetTags() const | File: ../UI/UIElement.h
static CScriptArray* DropDownList_GetTags_void(DropDownList* ptr)
{
    const StringVector& result = ptr->GetTags();
    return VectorToArray<String>(result, "Array<String>");
}

// void UIElement::SetTags(const StringVector& tags) | File: ../UI/UIElement.h
static void DropDownList_SetTags_StringVector(DropDownList* ptr, CScriptArray* tags_conv)
{
    StringVector tags = ArrayToVector<String>(tags_conv);
    ptr->SetTags(tags);
}

// void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
static void DropDownList_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool(DropDownList* ptr, CScriptArray* exceptions_conv, bool onlyUserData)
{
    PODVector<StringHash> exceptions = ArrayToPODVector<StringHash>(exceptions_conv);
    ptr->UnsubscribeFromAllEventsExcept(exceptions, onlyUserData);
}

#ifdef URHO3D_NAVIGATION
// explicit DynamicNavigationMesh::DynamicNavigationMesh(Context* context) | File: ../Navigation/DynamicNavigationMesh.h
static DynamicNavigationMesh* DynamicNavigationMesh_DynamicNavigationMesh_Context()
{
    return new DynamicNavigationMesh(GetScriptContext());
}
#endif

#ifdef URHO3D_NAVIGATION
// void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
static void DynamicNavigationMesh_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool(DynamicNavigationMesh* ptr, CScriptArray* exceptions_conv, bool onlyUserData)
{
    PODVector<StringHash> exceptions = ArrayToPODVector<StringHash>(exceptions_conv);
    ptr->UnsubscribeFromAllEventsExcept(exceptions, onlyUserData);
}
#endif

// DebugLine::DebugLine(const Vector3& start, const Vector3& end, unsigned color) | File: ../Graphics/DebugRenderer.h
static void DebugLine_DebugLine_Vector3_Vector3_unsigned(DebugLine* ptr, const Vector3 &start, const Vector3 &end, unsigned color)
{
    new(ptr) DebugLine(start, end, color);
}

// DebugTriangle::DebugTriangle(const Vector3& v1, const Vector3& v2, const Vector3& v3, unsigned color) | File: ../Graphics/DebugRenderer.h
static void DebugTriangle_DebugTriangle_Vector3_Vector3_Vector3_unsigned(DebugTriangle* ptr, const Vector3 &v1, const Vector3 &v2, const Vector3 &v3, unsigned color)
{
    new(ptr) DebugTriangle(v1, v2, v3, color);
}

// DecalVertex::DecalVertex(const Vector3& position, const Vector3& normal) | File: ../Graphics/DecalSet.h
static void DecalVertex_DecalVertex_Vector3_Vector3(DecalVertex* ptr, const Vector3 &position, const Vector3 &normal)
{
    new(ptr) DecalVertex(position, normal);
}

// DirtyBits::DirtyBits(const DirtyBits& bits) | File: ../Scene/ReplicationState.h
static void DirtyBits_DirtyBits_DirtyBits(DirtyBits* ptr, const DirtyBits &bits)
{
    new(ptr) DirtyBits(bits);
}

void ASRegisterGenerated_Members_D(asIScriptEngine* engine)
{
#ifdef URHO3D_DATABASE
    // void RefCounted::AddRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("Database", asBEHAVE_ADDREF, "void f()", asMETHODPR(Database, AddRef, (), void), asCALL_THISCALL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // DbConnection* Database::Connect(const String& connectionString) | File: ../Database/Database.h
    engine->RegisterObjectMethod("Database", "DbConnection@+ Connect(const String&in)", asMETHODPR(Database, Connect, (const String&), DbConnection*), asCALL_THISCALL);
    // explicit Database::Database(Context* context) | File: ../Database/Database.h
    engine->RegisterObjectBehaviour("Database", asBEHAVE_FACTORY, "Database@+ f()", asFUNCTION(Database_Database_Context), asCALL_CDECL);
    // void Database::Disconnect(DbConnection* connection) | File: ../Database/Database.h
    engine->RegisterObjectMethod("Database", "void Disconnect(DbConnection@+)", asMETHODPR(Database, Disconnect, (DbConnection*), void), asCALL_THISCALL);
    // static DBAPI Database::GetAPI() | File: ../Database/Database.h
    engine->SetDefaultNamespace("Database");
    engine->RegisterGlobalFunction("DBAPI GetAPI()", asFUNCTIONPR(Database::GetAPI, (), DBAPI), asCALL_CDECL);
    engine->SetDefaultNamespace("");
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Database", "bool GetBlockEvents() const", asMETHODPR(Database, GetBlockEvents, () const, bool), asCALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Database", "const String& GetCategory() const", asMETHODPR(Database, GetCategory, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Database", "const String& get_category() const", asMETHODPR(Database, GetCategory, () const, const String&), asCALL_THISCALL);
    // Context* Object::GetContext() const | File: ../Core/Object.h
    // Error: type "Context*" can used only as function parameter
    // VariantMap& Object::GetEventDataMap() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Database", "VariantMap& GetEventDataMap() const", asMETHODPR(Database, GetEventDataMap, () const, VariantMap&), asCALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Database", "Object@+ GetEventSender() const", asMETHODPR(Database, GetEventSender, () const, Object*), asCALL_THISCALL);
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Database", "const Variant& GetGlobalVar(StringHash) const", asMETHODPR(Database, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Database", "const Variant& get_globalVar(StringHash) const", asMETHODPR(Database, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Database", "const VariantMap& GetGlobalVars() const", asMETHODPR(Database, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Database", "const VariantMap& get_globalVars() const", asMETHODPR(Database, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    // unsigned Database::GetPoolSize() const | File: ../Database/Database.h
    engine->RegisterObjectMethod("Database", "uint GetPoolSize() const", asMETHODPR(Database, GetPoolSize, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("Database", "uint get_poolSize() const", asMETHODPR(Database, GetPoolSize, () const, unsigned), asCALL_THISCALL);
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Database", "Object@+ GetSubsystem(StringHash) const", asMETHODPR(Database, GetSubsystem, (StringHash) const, Object*), asCALL_THISCALL);
    // template<class T> T* Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("Database", "StringHash GetType() const", asMETHODPR(Database, GetType, () const, StringHash), asCALL_THISCALL);
    engine->RegisterObjectMethod("Database", "StringHash get_type() const", asMETHODPR(Database, GetType, () const, StringHash), asCALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("Database", "const String& GetTypeName() const", asMETHODPR(Database, GetTypeName, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Database", "const String& get_typeName() const", asMETHODPR(Database, GetTypeName, () const, const String&), asCALL_THISCALL);
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Database", "bool HasEventHandlers() const", asMETHODPR(Database, HasEventHandlers, () const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Database", "bool HasSubscribedToEvent(StringHash) const", asMETHODPR(Database, HasSubscribedToEvent, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Database", "bool HasSubscribedToEvent(Object@+, StringHash) const", asMETHODPR(Database, HasSubscribedToEvent, (Object*, StringHash) const, bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Database", "bool IsInstanceOf(StringHash) const", asMETHODPR(Database, IsInstanceOf, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // bool Database::IsPooling() const | File: ../Database/Database.h
    engine->RegisterObjectMethod("Database", "bool IsPooling() const", asMETHODPR(Database, IsPooling, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Database", "bool get_pooling() const", asMETHODPR(Database, IsPooling, () const, bool), asCALL_THISCALL);
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Database", "void OnEvent(Object@+, StringHash, VariantMap&)", asMETHODPR(Database, OnEvent, (Object*, StringHash, VariantMap&), void), asCALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("Database", "int Refs() const", asMETHODPR(Database, Refs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("Database", "int get_refs() const", asMETHODPR(Database, Refs, () const, int), asCALL_THISCALL);
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("Database", asBEHAVE_RELEASE, "void f()", asMETHODPR(Database, ReleaseRef, (), void), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Database", "void SendEvent(StringHash)", asMETHODPR(Database, SendEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Database", "void SendEvent(StringHash, VariantMap&)", asMETHODPR(Database, SendEvent, (StringHash, VariantMap&), void), asCALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Database", "void SetBlockEvents(bool)", asMETHODPR(Database, SetBlockEvents, (bool), void), asCALL_THISCALL);
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Database", "void SetGlobalVar(StringHash, const Variant&in)", asMETHODPR(Database, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Database", "void set_globalVar(StringHash, const Variant&in)", asMETHODPR(Database, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    // void Database::SetPoolSize(unsigned poolSize) | File: ../Database/Database.h
    engine->RegisterObjectMethod("Database", "void SetPoolSize(uint)", asMETHODPR(Database, SetPoolSize, (unsigned), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Database", "void set_poolSize(uint)", asMETHODPR(Database, SetPoolSize, (unsigned), void), asCALL_THISCALL);
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod("Database", "void UnsubscribeFromAllEvents()", asMETHODPR(Database, UnsubscribeFromAllEvents, (), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Database", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", asFUNCTION(Database_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), asCALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Database", "void UnsubscribeFromEvent(StringHash)", asMETHODPR(Database, UnsubscribeFromEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Database", "void UnsubscribeFromEvent(Object@+, StringHash)", asMETHODPR(Database, UnsubscribeFromEvent, (Object*, StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Database", "void UnsubscribeFromEvents(Object@+)", asMETHODPR(Database, UnsubscribeFromEvents, (Object*), void), asCALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("Database", "int WeakRefs() const", asMETHODPR(Database, WeakRefs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("Database", "int get_weakRefs() const", asMETHODPR(Database, WeakRefs, () const, int), asCALL_THISCALL);
#ifdef REGISTER_MANUAL_PART_Object
    REGISTER_MANUAL_PART_Object(Database, "Database")
#endif
#ifdef REGISTER_MANUAL_PART_RefCounted
    REGISTER_MANUAL_PART_RefCounted(Database, "Database")
#endif
#ifdef REGISTER_MANUAL_PART_Database
    REGISTER_MANUAL_PART_Database(Database, "Database")
#endif
    RegisterSubclass<Object, Database>(engine, "Object", "Database");
    RegisterSubclass<RefCounted, Database>(engine, "RefCounted", "Database");
#endif

    // void RefCounted::AddRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("DebugHud", asBEHAVE_ADDREF, "void f()", asMETHODPR(DebugHud, AddRef, (), void), asCALL_THISCALL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // void DebugHud::ClearAppStats() | File: ../Engine/DebugHud.h
    engine->RegisterObjectMethod("DebugHud", "void ClearAppStats()", asMETHODPR(DebugHud, ClearAppStats, (), void), asCALL_THISCALL);
    // explicit DebugHud::DebugHud(Context* context) | File: ../Engine/DebugHud.h
    engine->RegisterObjectBehaviour("DebugHud", asBEHAVE_FACTORY, "DebugHud@+ f()", asFUNCTION(DebugHud_DebugHud_Context), asCALL_CDECL);
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("DebugHud", "bool GetBlockEvents() const", asMETHODPR(DebugHud, GetBlockEvents, () const, bool), asCALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("DebugHud", "const String& GetCategory() const", asMETHODPR(DebugHud, GetCategory, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("DebugHud", "const String& get_category() const", asMETHODPR(DebugHud, GetCategory, () const, const String&), asCALL_THISCALL);
    // Context* Object::GetContext() const | File: ../Core/Object.h
    // Error: type "Context*" can used only as function parameter
    // XMLFile* DebugHud::GetDefaultStyle() const | File: ../Engine/DebugHud.h
    engine->RegisterObjectMethod("DebugHud", "XMLFile@+ GetDefaultStyle() const", asMETHODPR(DebugHud, GetDefaultStyle, () const, XMLFile*), asCALL_THISCALL);
    engine->RegisterObjectMethod("DebugHud", "XMLFile@+ get_defaultStyle() const", asMETHODPR(DebugHud, GetDefaultStyle, () const, XMLFile*), asCALL_THISCALL);
    // VariantMap& Object::GetEventDataMap() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("DebugHud", "VariantMap& GetEventDataMap() const", asMETHODPR(DebugHud, GetEventDataMap, () const, VariantMap&), asCALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("DebugHud", "Object@+ GetEventSender() const", asMETHODPR(DebugHud, GetEventSender, () const, Object*), asCALL_THISCALL);
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("DebugHud", "const Variant& GetGlobalVar(StringHash) const", asMETHODPR(DebugHud, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    engine->RegisterObjectMethod("DebugHud", "const Variant& get_globalVar(StringHash) const", asMETHODPR(DebugHud, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("DebugHud", "const VariantMap& GetGlobalVars() const", asMETHODPR(DebugHud, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    engine->RegisterObjectMethod("DebugHud", "const VariantMap& get_globalVars() const", asMETHODPR(DebugHud, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    // Text* DebugHud::GetMemoryText() const | File: ../Engine/DebugHud.h
    engine->RegisterObjectMethod("DebugHud", "Text@+ GetMemoryText() const", asMETHODPR(DebugHud, GetMemoryText, () const, Text*), asCALL_THISCALL);
    engine->RegisterObjectMethod("DebugHud", "Text@+ get_memoryText() const", asMETHODPR(DebugHud, GetMemoryText, () const, Text*), asCALL_THISCALL);
    // unsigned DebugHud::GetMode() const | File: ../Engine/DebugHud.h
    engine->RegisterObjectMethod("DebugHud", "uint GetMode() const", asMETHODPR(DebugHud, GetMode, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("DebugHud", "uint get_mode() const", asMETHODPR(DebugHud, GetMode, () const, unsigned), asCALL_THISCALL);
    // Text* DebugHud::GetModeText() const | File: ../Engine/DebugHud.h
    engine->RegisterObjectMethod("DebugHud", "Text@+ GetModeText() const", asMETHODPR(DebugHud, GetModeText, () const, Text*), asCALL_THISCALL);
    engine->RegisterObjectMethod("DebugHud", "Text@+ get_modeText() const", asMETHODPR(DebugHud, GetModeText, () const, Text*), asCALL_THISCALL);
    // float DebugHud::GetProfilerInterval() const | File: ../Engine/DebugHud.h
    engine->RegisterObjectMethod("DebugHud", "float GetProfilerInterval() const", asMETHODPR(DebugHud, GetProfilerInterval, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("DebugHud", "float get_profilerInterval() const", asMETHODPR(DebugHud, GetProfilerInterval, () const, float), asCALL_THISCALL);
    // unsigned DebugHud::GetProfilerMaxDepth() const | File: ../Engine/DebugHud.h
    engine->RegisterObjectMethod("DebugHud", "uint GetProfilerMaxDepth() const", asMETHODPR(DebugHud, GetProfilerMaxDepth, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("DebugHud", "uint get_profilerMaxDepth() const", asMETHODPR(DebugHud, GetProfilerMaxDepth, () const, unsigned), asCALL_THISCALL);
    // Text* DebugHud::GetProfilerText() const | File: ../Engine/DebugHud.h
    engine->RegisterObjectMethod("DebugHud", "Text@+ GetProfilerText() const", asMETHODPR(DebugHud, GetProfilerText, () const, Text*), asCALL_THISCALL);
    engine->RegisterObjectMethod("DebugHud", "Text@+ get_profilerText() const", asMETHODPR(DebugHud, GetProfilerText, () const, Text*), asCALL_THISCALL);
    // Text* DebugHud::GetStatsText() const | File: ../Engine/DebugHud.h
    engine->RegisterObjectMethod("DebugHud", "Text@+ GetStatsText() const", asMETHODPR(DebugHud, GetStatsText, () const, Text*), asCALL_THISCALL);
    engine->RegisterObjectMethod("DebugHud", "Text@+ get_statsText() const", asMETHODPR(DebugHud, GetStatsText, () const, Text*), asCALL_THISCALL);
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("DebugHud", "Object@+ GetSubsystem(StringHash) const", asMETHODPR(DebugHud, GetSubsystem, (StringHash) const, Object*), asCALL_THISCALL);
    // template<class T> T* Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("DebugHud", "StringHash GetType() const", asMETHODPR(DebugHud, GetType, () const, StringHash), asCALL_THISCALL);
    engine->RegisterObjectMethod("DebugHud", "StringHash get_type() const", asMETHODPR(DebugHud, GetType, () const, StringHash), asCALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("DebugHud", "const String& GetTypeName() const", asMETHODPR(DebugHud, GetTypeName, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("DebugHud", "const String& get_typeName() const", asMETHODPR(DebugHud, GetTypeName, () const, const String&), asCALL_THISCALL);
    // bool DebugHud::GetUseRendererStats() const | File: ../Engine/DebugHud.h
    engine->RegisterObjectMethod("DebugHud", "bool GetUseRendererStats() const", asMETHODPR(DebugHud, GetUseRendererStats, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("DebugHud", "bool get_useRendererStats() const", asMETHODPR(DebugHud, GetUseRendererStats, () const, bool), asCALL_THISCALL);
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("DebugHud", "bool HasEventHandlers() const", asMETHODPR(DebugHud, HasEventHandlers, () const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("DebugHud", "bool HasSubscribedToEvent(StringHash) const", asMETHODPR(DebugHud, HasSubscribedToEvent, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("DebugHud", "bool HasSubscribedToEvent(Object@+, StringHash) const", asMETHODPR(DebugHud, HasSubscribedToEvent, (Object*, StringHash) const, bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("DebugHud", "bool IsInstanceOf(StringHash) const", asMETHODPR(DebugHud, IsInstanceOf, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("DebugHud", "void OnEvent(Object@+, StringHash, VariantMap&)", asMETHODPR(DebugHud, OnEvent, (Object*, StringHash, VariantMap&), void), asCALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("DebugHud", "int Refs() const", asMETHODPR(DebugHud, Refs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("DebugHud", "int get_refs() const", asMETHODPR(DebugHud, Refs, () const, int), asCALL_THISCALL);
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("DebugHud", asBEHAVE_RELEASE, "void f()", asMETHODPR(DebugHud, ReleaseRef, (), void), asCALL_THISCALL);
    // bool DebugHud::ResetAppStats(const String& label) | File: ../Engine/DebugHud.h
    engine->RegisterObjectMethod("DebugHud", "bool ResetAppStats(const String&in)", asMETHODPR(DebugHud, ResetAppStats, (const String&), bool), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("DebugHud", "void SendEvent(StringHash)", asMETHODPR(DebugHud, SendEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("DebugHud", "void SendEvent(StringHash, VariantMap&)", asMETHODPR(DebugHud, SendEvent, (StringHash, VariantMap&), void), asCALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void DebugHud::SetAppStats(const String& label, const Variant& stats) | File: ../Engine/DebugHud.h
    engine->RegisterObjectMethod("DebugHud", "void SetAppStats(const String&in, const Variant&in)", asMETHODPR(DebugHud, SetAppStats, (const String&, const Variant&), void), asCALL_THISCALL);
    // void DebugHud::SetAppStats(const String& label, const String& stats) | File: ../Engine/DebugHud.h
    engine->RegisterObjectMethod("DebugHud", "void SetAppStats(const String&in, const String&in)", asMETHODPR(DebugHud, SetAppStats, (const String&, const String&), void), asCALL_THISCALL);
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("DebugHud", "void SetBlockEvents(bool)", asMETHODPR(DebugHud, SetBlockEvents, (bool), void), asCALL_THISCALL);
    // void DebugHud::SetDefaultStyle(XMLFile* style) | File: ../Engine/DebugHud.h
    engine->RegisterObjectMethod("DebugHud", "void SetDefaultStyle(XMLFile@+)", asMETHODPR(DebugHud, SetDefaultStyle, (XMLFile*), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("DebugHud", "void set_defaultStyle(XMLFile@+)", asMETHODPR(DebugHud, SetDefaultStyle, (XMLFile*), void), asCALL_THISCALL);
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("DebugHud", "void SetGlobalVar(StringHash, const Variant&in)", asMETHODPR(DebugHud, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("DebugHud", "void set_globalVar(StringHash, const Variant&in)", asMETHODPR(DebugHud, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    // void DebugHud::SetMode(unsigned mode) | File: ../Engine/DebugHud.h
    engine->RegisterObjectMethod("DebugHud", "void SetMode(uint)", asMETHODPR(DebugHud, SetMode, (unsigned), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("DebugHud", "void set_mode(uint)", asMETHODPR(DebugHud, SetMode, (unsigned), void), asCALL_THISCALL);
    // void DebugHud::SetProfilerInterval(float interval) | File: ../Engine/DebugHud.h
    engine->RegisterObjectMethod("DebugHud", "void SetProfilerInterval(float)", asMETHODPR(DebugHud, SetProfilerInterval, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("DebugHud", "void set_profilerInterval(float)", asMETHODPR(DebugHud, SetProfilerInterval, (float), void), asCALL_THISCALL);
    // void DebugHud::SetProfilerMaxDepth(unsigned depth) | File: ../Engine/DebugHud.h
    engine->RegisterObjectMethod("DebugHud", "void SetProfilerMaxDepth(uint)", asMETHODPR(DebugHud, SetProfilerMaxDepth, (unsigned), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("DebugHud", "void set_profilerMaxDepth(uint)", asMETHODPR(DebugHud, SetProfilerMaxDepth, (unsigned), void), asCALL_THISCALL);
    // void DebugHud::SetUseRendererStats(bool enable) | File: ../Engine/DebugHud.h
    engine->RegisterObjectMethod("DebugHud", "void SetUseRendererStats(bool)", asMETHODPR(DebugHud, SetUseRendererStats, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("DebugHud", "void set_useRendererStats(bool)", asMETHODPR(DebugHud, SetUseRendererStats, (bool), void), asCALL_THISCALL);
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void DebugHud::Toggle(unsigned mode) | File: ../Engine/DebugHud.h
    engine->RegisterObjectMethod("DebugHud", "void Toggle(uint)", asMETHODPR(DebugHud, Toggle, (unsigned), void), asCALL_THISCALL);
    // void DebugHud::ToggleAll() | File: ../Engine/DebugHud.h
    engine->RegisterObjectMethod("DebugHud", "void ToggleAll()", asMETHODPR(DebugHud, ToggleAll, (), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod("DebugHud", "void UnsubscribeFromAllEvents()", asMETHODPR(DebugHud, UnsubscribeFromAllEvents, (), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("DebugHud", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", asFUNCTION(DebugHud_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), asCALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("DebugHud", "void UnsubscribeFromEvent(StringHash)", asMETHODPR(DebugHud, UnsubscribeFromEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("DebugHud", "void UnsubscribeFromEvent(Object@+, StringHash)", asMETHODPR(DebugHud, UnsubscribeFromEvent, (Object*, StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("DebugHud", "void UnsubscribeFromEvents(Object@+)", asMETHODPR(DebugHud, UnsubscribeFromEvents, (Object*), void), asCALL_THISCALL);
    // void DebugHud::Update() | File: ../Engine/DebugHud.h
    engine->RegisterObjectMethod("DebugHud", "void Update()", asMETHODPR(DebugHud, Update, (), void), asCALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("DebugHud", "int WeakRefs() const", asMETHODPR(DebugHud, WeakRefs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("DebugHud", "int get_weakRefs() const", asMETHODPR(DebugHud, WeakRefs, () const, int), asCALL_THISCALL);
#ifdef REGISTER_MANUAL_PART_Object
    REGISTER_MANUAL_PART_Object(DebugHud, "DebugHud")
#endif
#ifdef REGISTER_MANUAL_PART_RefCounted
    REGISTER_MANUAL_PART_RefCounted(DebugHud, "DebugHud")
#endif
#ifdef REGISTER_MANUAL_PART_DebugHud
    REGISTER_MANUAL_PART_DebugHud(DebugHud, "DebugHud")
#endif
    RegisterSubclass<Object, DebugHud>(engine, "Object", "DebugHud");
    RegisterSubclass<RefCounted, DebugHud>(engine, "RefCounted", "DebugHud");

    // void DebugRenderer::AddBoundingBox(const BoundingBox& box, const Color& color, bool depthTest=true, bool solid=false) | File: ../Graphics/DebugRenderer.h
    engine->RegisterObjectMethod("DebugRenderer", "void AddBoundingBox(const BoundingBox&in, const Color&in, bool = true, bool = false)", asMETHODPR(DebugRenderer, AddBoundingBox, (const BoundingBox&, const Color&, bool, bool), void), asCALL_THISCALL);
    // void DebugRenderer::AddBoundingBox(const BoundingBox& box, const Matrix3x4& transform, const Color& color, bool depthTest=true, bool solid=false) | File: ../Graphics/DebugRenderer.h
    engine->RegisterObjectMethod("DebugRenderer", "void AddBoundingBox(const BoundingBox&in, const Matrix3x4&in, const Color&in, bool = true, bool = false)", asMETHODPR(DebugRenderer, AddBoundingBox, (const BoundingBox&, const Matrix3x4&, const Color&, bool, bool), void), asCALL_THISCALL);
    // void DebugRenderer::AddCircle(const Vector3& center, const Vector3& normal, float radius, const Color& color, int steps=64, bool depthTest=true) | File: ../Graphics/DebugRenderer.h
    engine->RegisterObjectMethod("DebugRenderer", "void AddCircle(const Vector3&in, const Vector3&in, float, const Color&in, int = 64, bool = true)", asMETHODPR(DebugRenderer, AddCircle, (const Vector3&, const Vector3&, float, const Color&, int, bool), void), asCALL_THISCALL);
    // void DebugRenderer::AddCross(const Vector3& center, float size, const Color& color, bool depthTest=true) | File: ../Graphics/DebugRenderer.h
    engine->RegisterObjectMethod("DebugRenderer", "void AddCross(const Vector3&in, float, const Color&in, bool = true)", asMETHODPR(DebugRenderer, AddCross, (const Vector3&, float, const Color&, bool), void), asCALL_THISCALL);
    // void DebugRenderer::AddCylinder(const Vector3& position, float radius, float height, const Color& color, bool depthTest=true) | File: ../Graphics/DebugRenderer.h
    engine->RegisterObjectMethod("DebugRenderer", "void AddCylinder(const Vector3&in, float, float, const Color&in, bool = true)", asMETHODPR(DebugRenderer, AddCylinder, (const Vector3&, float, float, const Color&, bool), void), asCALL_THISCALL);
    // void DebugRenderer::AddFrustum(const Frustum& frustum, const Color& color, bool depthTest=true) | File: ../Graphics/DebugRenderer.h
    engine->RegisterObjectMethod("DebugRenderer", "void AddFrustum(const Frustum&in, const Color&in, bool = true)", asMETHODPR(DebugRenderer, AddFrustum, (const Frustum&, const Color&, bool), void), asCALL_THISCALL);
    // void DebugRenderer::AddLine(const Vector3& start, const Vector3& end, const Color& color, bool depthTest=true) | File: ../Graphics/DebugRenderer.h
    engine->RegisterObjectMethod("DebugRenderer", "void AddLine(const Vector3&in, const Vector3&in, const Color&in, bool = true)", asMETHODPR(DebugRenderer, AddLine, (const Vector3&, const Vector3&, const Color&, bool), void), asCALL_THISCALL);
    // void DebugRenderer::AddLine(const Vector3& start, const Vector3& end, unsigned color, bool depthTest=true) | File: ../Graphics/DebugRenderer.h
    engine->RegisterObjectMethod("DebugRenderer", "void AddLine(const Vector3&in, const Vector3&in, uint, bool = true)", asMETHODPR(DebugRenderer, AddLine, (const Vector3&, const Vector3&, unsigned, bool), void), asCALL_THISCALL);
    // void DebugRenderer::AddNode(Node* node, float scale=1.0f, bool depthTest=true) | File: ../Graphics/DebugRenderer.h
    engine->RegisterObjectMethod("DebugRenderer", "void AddNode(Node@+, float = 1.0f, bool = true)", asMETHODPR(DebugRenderer, AddNode, (Node*, float, bool), void), asCALL_THISCALL);
    // void DebugRenderer::AddPolygon(const Vector3& v1, const Vector3& v2, const Vector3& v3, const Vector3& v4, const Color& color, bool depthTest=true) | File: ../Graphics/DebugRenderer.h
    engine->RegisterObjectMethod("DebugRenderer", "void AddPolygon(const Vector3&in, const Vector3&in, const Vector3&in, const Vector3&in, const Color&in, bool = true)", asMETHODPR(DebugRenderer, AddPolygon, (const Vector3&, const Vector3&, const Vector3&, const Vector3&, const Color&, bool), void), asCALL_THISCALL);
    // void DebugRenderer::AddPolygon(const Vector3& v1, const Vector3& v2, const Vector3& v3, const Vector3& v4, unsigned color, bool depthTest=true) | File: ../Graphics/DebugRenderer.h
    engine->RegisterObjectMethod("DebugRenderer", "void AddPolygon(const Vector3&in, const Vector3&in, const Vector3&in, const Vector3&in, uint, bool = true)", asMETHODPR(DebugRenderer, AddPolygon, (const Vector3&, const Vector3&, const Vector3&, const Vector3&, unsigned, bool), void), asCALL_THISCALL);
    // void DebugRenderer::AddPolyhedron(const Polyhedron& poly, const Color& color, bool depthTest=true) | File: ../Graphics/DebugRenderer.h
    engine->RegisterObjectMethod("DebugRenderer", "void AddPolyhedron(const Polyhedron&in, const Color&in, bool = true)", asMETHODPR(DebugRenderer, AddPolyhedron, (const Polyhedron&, const Color&, bool), void), asCALL_THISCALL);
    // void DebugRenderer::AddQuad(const Vector3& center, float width, float height, const Color& color, bool depthTest=true) | File: ../Graphics/DebugRenderer.h
    engine->RegisterObjectMethod("DebugRenderer", "void AddQuad(const Vector3&in, float, float, const Color&in, bool = true)", asMETHODPR(DebugRenderer, AddQuad, (const Vector3&, float, float, const Color&, bool), void), asCALL_THISCALL);
    // void RefCounted::AddRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("DebugRenderer", asBEHAVE_ADDREF, "void f()", asMETHODPR(DebugRenderer, AddRef, (), void), asCALL_THISCALL);
    // void Component::AddReplicationState(ComponentReplicationState* state) | File: ../Scene/Component.h
    // Error: type "ComponentReplicationState*" can not automatically bind
    // void DebugRenderer::AddSkeleton(const Skeleton& skeleton, const Color& color, bool depthTest=true) | File: ../Graphics/DebugRenderer.h
    engine->RegisterObjectMethod("DebugRenderer", "void AddSkeleton(const Skeleton&in, const Color&in, bool = true)", asMETHODPR(DebugRenderer, AddSkeleton, (const Skeleton&, const Color&, bool), void), asCALL_THISCALL);
    // void DebugRenderer::AddSphere(const Sphere& sphere, const Color& color, bool depthTest=true) | File: ../Graphics/DebugRenderer.h
    engine->RegisterObjectMethod("DebugRenderer", "void AddSphere(const Sphere&in, const Color&in, bool = true)", asMETHODPR(DebugRenderer, AddSphere, (const Sphere&, const Color&, bool), void), asCALL_THISCALL);
    // void DebugRenderer::AddSphereSector(const Sphere& sphere, const Quaternion& rotation, float angle, bool drawLines, const Color& color, bool depthTest=true) | File: ../Graphics/DebugRenderer.h
    engine->RegisterObjectMethod("DebugRenderer", "void AddSphereSector(const Sphere&in, const Quaternion&in, float, bool, const Color&in, bool = true)", asMETHODPR(DebugRenderer, AddSphereSector, (const Sphere&, const Quaternion&, float, bool, const Color&, bool), void), asCALL_THISCALL);
    // void DebugRenderer::AddTriangle(const Vector3& v1, const Vector3& v2, const Vector3& v3, const Color& color, bool depthTest=true) | File: ../Graphics/DebugRenderer.h
    engine->RegisterObjectMethod("DebugRenderer", "void AddTriangle(const Vector3&in, const Vector3&in, const Vector3&in, const Color&in, bool = true)", asMETHODPR(DebugRenderer, AddTriangle, (const Vector3&, const Vector3&, const Vector3&, const Color&, bool), void), asCALL_THISCALL);
    // void DebugRenderer::AddTriangle(const Vector3& v1, const Vector3& v2, const Vector3& v3, unsigned color, bool depthTest=true) | File: ../Graphics/DebugRenderer.h
    engine->RegisterObjectMethod("DebugRenderer", "void AddTriangle(const Vector3&in, const Vector3&in, const Vector3&in, uint, bool = true)", asMETHODPR(DebugRenderer, AddTriangle, (const Vector3&, const Vector3&, const Vector3&, unsigned, bool), void), asCALL_THISCALL);
    // void DebugRenderer::AddTriangleMesh(const void* vertexData, unsigned vertexSize, const void* indexData, unsigned indexSize, unsigned indexStart, unsigned indexCount, const Matrix3x4& transform, const Color& color, bool depthTest=true) | File: ../Graphics/DebugRenderer.h
    // Error: type "const void*" can not automatically bind
    // void DebugRenderer::AddTriangleMesh(const void* vertexData, unsigned vertexSize, unsigned vertexStart, const void* indexData, unsigned indexSize, unsigned indexStart, unsigned indexCount, const Matrix3x4& transform, const Color& color, bool depthTest=true) | File: ../Graphics/DebugRenderer.h
    // Error: type "const void*" can not automatically bind
    // void Serializable::AllocateNetworkState() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("DebugRenderer", "void AllocateNetworkState()", asMETHODPR(DebugRenderer, AllocateNetworkState, (), void), asCALL_THISCALL);
    // virtual void Serializable::ApplyAttributes() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("DebugRenderer", "void ApplyAttributes()", asMETHODPR(DebugRenderer, ApplyAttributes, (), void), asCALL_THISCALL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // void Component::CleanupConnection(Connection* connection) | File: ../Scene/Component.h
    // Not registered because have @manualbind mark
    // explicit DebugRenderer::DebugRenderer(Context* context) | File: ../Graphics/DebugRenderer.h
    engine->RegisterObjectBehaviour("DebugRenderer", asBEHAVE_FACTORY, "DebugRenderer@+ f()", asFUNCTION(DebugRenderer_DebugRenderer_Context), asCALL_CDECL);
    // virtual void Component::DrawDebugGeometry(DebugRenderer* debug, bool depthTest) | File: ../Scene/Component.h
    engine->RegisterObjectMethod("DebugRenderer", "void DrawDebugGeometry(DebugRenderer@+, bool)", asMETHODPR(DebugRenderer, DrawDebugGeometry, (DebugRenderer*, bool), void), asCALL_THISCALL);
    // bool Animatable::GetAnimationEnabled() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("DebugRenderer", "bool GetAnimationEnabled() const", asMETHODPR(DebugRenderer, GetAnimationEnabled, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("DebugRenderer", "bool get_animationEnabled() const", asMETHODPR(DebugRenderer, GetAnimationEnabled, () const, bool), asCALL_THISCALL);
    // Variant Serializable::GetAttribute(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("DebugRenderer", "Variant GetAttribute(uint) const", asMETHODPR(DebugRenderer, GetAttribute, (unsigned) const, Variant), asCALL_THISCALL);
    engine->RegisterObjectMethod("DebugRenderer", "Variant get_attributes(uint) const", asMETHODPR(DebugRenderer, GetAttribute, (unsigned) const, Variant), asCALL_THISCALL);
    // Variant Serializable::GetAttribute(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("DebugRenderer", "Variant GetAttribute(const String&in) const", asMETHODPR(DebugRenderer, GetAttribute, (const String&) const, Variant), asCALL_THISCALL);
    // ValueAnimation* Animatable::GetAttributeAnimation(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("DebugRenderer", "ValueAnimation@+ GetAttributeAnimation(const String&in) const", asMETHODPR(DebugRenderer, GetAttributeAnimation, (const String&) const, ValueAnimation*), asCALL_THISCALL);
    // float Animatable::GetAttributeAnimationSpeed(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("DebugRenderer", "float GetAttributeAnimationSpeed(const String&in) const", asMETHODPR(DebugRenderer, GetAttributeAnimationSpeed, (const String&) const, float), asCALL_THISCALL);
    // float Animatable::GetAttributeAnimationTime(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("DebugRenderer", "float GetAttributeAnimationTime(const String&in) const", asMETHODPR(DebugRenderer, GetAttributeAnimationTime, (const String&) const, float), asCALL_THISCALL);
    // WrapMode Animatable::GetAttributeAnimationWrapMode(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("DebugRenderer", "WrapMode GetAttributeAnimationWrapMode(const String&in) const", asMETHODPR(DebugRenderer, GetAttributeAnimationWrapMode, (const String&) const, WrapMode), asCALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("DebugRenderer", "Variant GetAttributeDefault(uint) const", asMETHODPR(DebugRenderer, GetAttributeDefault, (unsigned) const, Variant), asCALL_THISCALL);
    engine->RegisterObjectMethod("DebugRenderer", "Variant get_attributeDefaults(uint) const", asMETHODPR(DebugRenderer, GetAttributeDefault, (unsigned) const, Variant), asCALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("DebugRenderer", "Variant GetAttributeDefault(const String&in) const", asMETHODPR(DebugRenderer, GetAttributeDefault, (const String&) const, Variant), asCALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("DebugRenderer", "bool GetBlockEvents() const", asMETHODPR(DebugRenderer, GetBlockEvents, () const, bool), asCALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("DebugRenderer", "const String& GetCategory() const", asMETHODPR(DebugRenderer, GetCategory, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("DebugRenderer", "const String& get_category() const", asMETHODPR(DebugRenderer, GetCategory, () const, const String&), asCALL_THISCALL);
    // Component* Component::GetComponent(StringHash type) const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("DebugRenderer", "Component@+ GetComponent(StringHash) const", asMETHODPR(DebugRenderer, GetComponent, (StringHash) const, Component*), asCALL_THISCALL);
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
    // VariantMap& Object::GetEventDataMap() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("DebugRenderer", "VariantMap& GetEventDataMap() const", asMETHODPR(DebugRenderer, GetEventDataMap, () const, VariantMap&), asCALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("DebugRenderer", "Object@+ GetEventSender() const", asMETHODPR(DebugRenderer, GetEventSender, () const, Object*), asCALL_THISCALL);
    // const Frustum& DebugRenderer::GetFrustum() const | File: ../Graphics/DebugRenderer.h
    engine->RegisterObjectMethod("DebugRenderer", "const Frustum& GetFrustum() const", asMETHODPR(DebugRenderer, GetFrustum, () const, const Frustum&), asCALL_THISCALL);
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("DebugRenderer", "const Variant& GetGlobalVar(StringHash) const", asMETHODPR(DebugRenderer, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    engine->RegisterObjectMethod("DebugRenderer", "const Variant& get_globalVar(StringHash) const", asMETHODPR(DebugRenderer, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("DebugRenderer", "const VariantMap& GetGlobalVars() const", asMETHODPR(DebugRenderer, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    engine->RegisterObjectMethod("DebugRenderer", "const VariantMap& get_globalVars() const", asMETHODPR(DebugRenderer, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    // unsigned Component::GetID() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("DebugRenderer", "uint GetID() const", asMETHODPR(DebugRenderer, GetID, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("DebugRenderer", "uint get_id() const", asMETHODPR(DebugRenderer, GetID, () const, unsigned), asCALL_THISCALL);
    // bool Serializable::GetInterceptNetworkUpdate(const String& attributeName) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("DebugRenderer", "bool GetInterceptNetworkUpdate(const String&in) const", asMETHODPR(DebugRenderer, GetInterceptNetworkUpdate, (const String&) const, bool), asCALL_THISCALL);
    // bool DebugRenderer::GetLineAntiAlias() const | File: ../Graphics/DebugRenderer.h
    engine->RegisterObjectMethod("DebugRenderer", "bool GetLineAntiAlias() const", asMETHODPR(DebugRenderer, GetLineAntiAlias, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("DebugRenderer", "bool get_lineAntiAlias() const", asMETHODPR(DebugRenderer, GetLineAntiAlias, () const, bool), asCALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetNetworkAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // NetworkState* Serializable::GetNetworkState() const | File: ../Scene/Serializable.h
    // Error: type "NetworkState*" can not automatically bind
    // Node* Component::GetNode() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("DebugRenderer", "Node@+ GetNode() const", asMETHODPR(DebugRenderer, GetNode, () const, Node*), asCALL_THISCALL);
    engine->RegisterObjectMethod("DebugRenderer", "Node@+ get_node() const", asMETHODPR(DebugRenderer, GetNode, () const, Node*), asCALL_THISCALL);
    // unsigned Serializable::GetNumAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("DebugRenderer", "uint GetNumAttributes() const", asMETHODPR(DebugRenderer, GetNumAttributes, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("DebugRenderer", "uint get_numAttributes() const", asMETHODPR(DebugRenderer, GetNumAttributes, () const, unsigned), asCALL_THISCALL);
    // unsigned Serializable::GetNumNetworkAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("DebugRenderer", "uint GetNumNetworkAttributes() const", asMETHODPR(DebugRenderer, GetNumNetworkAttributes, () const, unsigned), asCALL_THISCALL);
    // ObjectAnimation* Animatable::GetObjectAnimation() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("DebugRenderer", "ObjectAnimation@+ GetObjectAnimation() const", asMETHODPR(DebugRenderer, GetObjectAnimation, () const, ObjectAnimation*), asCALL_THISCALL);
    engine->RegisterObjectMethod("DebugRenderer", "ObjectAnimation@+ get_objectAnimation() const", asMETHODPR(DebugRenderer, GetObjectAnimation, () const, ObjectAnimation*), asCALL_THISCALL);
    // ResourceRef Animatable::GetObjectAnimationAttr() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("DebugRenderer", "ResourceRef GetObjectAnimationAttr() const", asMETHODPR(DebugRenderer, GetObjectAnimationAttr, () const, ResourceRef), asCALL_THISCALL);
    // const Matrix4& DebugRenderer::GetProjection() const | File: ../Graphics/DebugRenderer.h
    engine->RegisterObjectMethod("DebugRenderer", "const Matrix4& GetProjection() const", asMETHODPR(DebugRenderer, GetProjection, () const, const Matrix4&), asCALL_THISCALL);
    // Scene* Component::GetScene() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("DebugRenderer", "Scene@+ GetScene() const", asMETHODPR(DebugRenderer, GetScene, () const, Scene*), asCALL_THISCALL);
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("DebugRenderer", "Object@+ GetSubsystem(StringHash) const", asMETHODPR(DebugRenderer, GetSubsystem, (StringHash) const, Object*), asCALL_THISCALL);
    // template<class T> T* Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("DebugRenderer", "StringHash GetType() const", asMETHODPR(DebugRenderer, GetType, () const, StringHash), asCALL_THISCALL);
    engine->RegisterObjectMethod("DebugRenderer", "StringHash get_type() const", asMETHODPR(DebugRenderer, GetType, () const, StringHash), asCALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("DebugRenderer", "const String& GetTypeName() const", asMETHODPR(DebugRenderer, GetTypeName, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("DebugRenderer", "const String& get_typeName() const", asMETHODPR(DebugRenderer, GetTypeName, () const, const String&), asCALL_THISCALL);
    // const Matrix3x4& DebugRenderer::GetView() const | File: ../Graphics/DebugRenderer.h
    engine->RegisterObjectMethod("DebugRenderer", "const Matrix3x4& GetView() const", asMETHODPR(DebugRenderer, GetView, () const, const Matrix3x4&), asCALL_THISCALL);
    // bool DebugRenderer::HasContent() const | File: ../Graphics/DebugRenderer.h
    engine->RegisterObjectMethod("DebugRenderer", "bool HasContent() const", asMETHODPR(DebugRenderer, HasContent, () const, bool), asCALL_THISCALL);
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("DebugRenderer", "bool HasEventHandlers() const", asMETHODPR(DebugRenderer, HasEventHandlers, () const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("DebugRenderer", "bool HasSubscribedToEvent(StringHash) const", asMETHODPR(DebugRenderer, HasSubscribedToEvent, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("DebugRenderer", "bool HasSubscribedToEvent(Object@+, StringHash) const", asMETHODPR(DebugRenderer, HasSubscribedToEvent, (Object*, StringHash) const, bool), asCALL_THISCALL);
    // bool Component::IsEnabled() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("DebugRenderer", "bool IsEnabled() const", asMETHODPR(DebugRenderer, IsEnabled, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("DebugRenderer", "bool get_enabled() const", asMETHODPR(DebugRenderer, IsEnabled, () const, bool), asCALL_THISCALL);
    // bool Component::IsEnabledEffective() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("DebugRenderer", "bool IsEnabledEffective() const", asMETHODPR(DebugRenderer, IsEnabledEffective, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("DebugRenderer", "bool get_enabledEffective() const", asMETHODPR(DebugRenderer, IsEnabledEffective, () const, bool), asCALL_THISCALL);
    // bool DebugRenderer::IsInside(const BoundingBox& box) const | File: ../Graphics/DebugRenderer.h
    engine->RegisterObjectMethod("DebugRenderer", "bool IsInside(const BoundingBox&in) const", asMETHODPR(DebugRenderer, IsInside, (const BoundingBox&) const, bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("DebugRenderer", "bool IsInstanceOf(StringHash) const", asMETHODPR(DebugRenderer, IsInstanceOf, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // bool Component::IsReplicated() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("DebugRenderer", "bool IsReplicated() const", asMETHODPR(DebugRenderer, IsReplicated, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("DebugRenderer", "bool get_replicated() const", asMETHODPR(DebugRenderer, IsReplicated, () const, bool), asCALL_THISCALL);
    // bool Serializable::IsTemporary() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("DebugRenderer", "bool IsTemporary() const", asMETHODPR(DebugRenderer, IsTemporary, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("DebugRenderer", "bool get_temporary() const", asMETHODPR(DebugRenderer, IsTemporary, () const, bool), asCALL_THISCALL);
    // virtual bool Serializable::Load(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("DebugRenderer", "bool Load(Deserializer&)", asMETHODPR(DebugRenderer, Load, (Deserializer&), bool), asCALL_THISCALL);
    // bool Animatable::LoadJSON(const JSONValue& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("DebugRenderer", "bool LoadJSON(const JSONValue&in)", asMETHODPR(DebugRenderer, LoadJSON, (const JSONValue&), bool), asCALL_THISCALL);
    // bool Animatable::LoadXML(const XMLElement& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("DebugRenderer", "bool LoadXML(const XMLElement&in)", asMETHODPR(DebugRenderer, LoadXML, (const XMLElement&), bool), asCALL_THISCALL);
    // void Component::MarkNetworkUpdate() override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("DebugRenderer", "void MarkNetworkUpdate()", asMETHODPR(DebugRenderer, MarkNetworkUpdate, (), void), asCALL_THISCALL);
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("DebugRenderer", "void OnEvent(Object@+, StringHash, VariantMap&)", asMETHODPR(DebugRenderer, OnEvent, (Object*, StringHash, VariantMap&), void), asCALL_THISCALL);
    // virtual void Serializable::OnGetAttribute(const AttributeInfo& attr, Variant& dest) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("DebugRenderer", "void OnGetAttribute(const AttributeInfo&in, Variant&) const", asMETHODPR(DebugRenderer, OnGetAttribute, (const AttributeInfo&, Variant&) const, void), asCALL_THISCALL);
    // virtual void Serializable::OnSetAttribute(const AttributeInfo& attr, const Variant& src) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("DebugRenderer", "void OnSetAttribute(const AttributeInfo&in, const Variant&in)", asMETHODPR(DebugRenderer, OnSetAttribute, (const AttributeInfo&, const Variant&), void), asCALL_THISCALL);
    // virtual void Component::OnSetEnabled() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("DebugRenderer", "void OnSetEnabled()", asMETHODPR(DebugRenderer, OnSetEnabled, (), void), asCALL_THISCALL);
    // void Component::PrepareNetworkUpdate() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("DebugRenderer", "void PrepareNetworkUpdate()", asMETHODPR(DebugRenderer, PrepareNetworkUpdate, (), void), asCALL_THISCALL);
    // bool Serializable::ReadDeltaUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("DebugRenderer", "bool ReadDeltaUpdate(Deserializer&)", asMETHODPR(DebugRenderer, ReadDeltaUpdate, (Deserializer&), bool), asCALL_THISCALL);
    // bool Serializable::ReadLatestDataUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("DebugRenderer", "bool ReadLatestDataUpdate(Deserializer&)", asMETHODPR(DebugRenderer, ReadLatestDataUpdate, (Deserializer&), bool), asCALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("DebugRenderer", "int Refs() const", asMETHODPR(DebugRenderer, Refs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("DebugRenderer", "int get_refs() const", asMETHODPR(DebugRenderer, Refs, () const, int), asCALL_THISCALL);
    // static void DebugRenderer::RegisterObject(Context* context) | File: ../Graphics/DebugRenderer.h
    // Not registered because have @nobind mark
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("DebugRenderer", asBEHAVE_RELEASE, "void f()", asMETHODPR(DebugRenderer, ReleaseRef, (), void), asCALL_THISCALL);
    // void Component::Remove() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("DebugRenderer", "void Remove()", asMETHODPR(DebugRenderer, Remove, (), void), asCALL_THISCALL);
    // void Animatable::RemoveAttributeAnimation(const String& name) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("DebugRenderer", "void RemoveAttributeAnimation(const String&in)", asMETHODPR(DebugRenderer, RemoveAttributeAnimation, (const String&), void), asCALL_THISCALL);
    // void Serializable::RemoveInstanceDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("DebugRenderer", "void RemoveInstanceDefault()", asMETHODPR(DebugRenderer, RemoveInstanceDefault, (), void), asCALL_THISCALL);
    // void Animatable::RemoveObjectAnimation() | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("DebugRenderer", "void RemoveObjectAnimation()", asMETHODPR(DebugRenderer, RemoveObjectAnimation, (), void), asCALL_THISCALL);
    // void DebugRenderer::Render() | File: ../Graphics/DebugRenderer.h
    engine->RegisterObjectMethod("DebugRenderer", "void Render()", asMETHODPR(DebugRenderer, Render, (), void), asCALL_THISCALL);
    // void Serializable::ResetToDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("DebugRenderer", "void ResetToDefault()", asMETHODPR(DebugRenderer, ResetToDefault, (), void), asCALL_THISCALL);
    // bool Component::Save(Serializer& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("DebugRenderer", "bool Save(Serializer&) const", asMETHODPR(DebugRenderer, Save, (Serializer&) const, bool), asCALL_THISCALL);
    // virtual bool Serializable::SaveDefaultAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("DebugRenderer", "bool SaveDefaultAttributes() const", asMETHODPR(DebugRenderer, SaveDefaultAttributes, () const, bool), asCALL_THISCALL);
    // bool Component::SaveJSON(JSONValue& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("DebugRenderer", "bool SaveJSON(JSONValue&) const", asMETHODPR(DebugRenderer, SaveJSON, (JSONValue&) const, bool), asCALL_THISCALL);
    // bool Component::SaveXML(XMLElement& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("DebugRenderer", "bool SaveXML(XMLElement&) const", asMETHODPR(DebugRenderer, SaveXML, (XMLElement&) const, bool), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("DebugRenderer", "void SendEvent(StringHash)", asMETHODPR(DebugRenderer, SendEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("DebugRenderer", "void SendEvent(StringHash, VariantMap&)", asMETHODPR(DebugRenderer, SendEvent, (StringHash, VariantMap&), void), asCALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void Animatable::SetAnimationEnabled(bool enable) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("DebugRenderer", "void SetAnimationEnabled(bool)", asMETHODPR(DebugRenderer, SetAnimationEnabled, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("DebugRenderer", "void set_animationEnabled(bool)", asMETHODPR(DebugRenderer, SetAnimationEnabled, (bool), void), asCALL_THISCALL);
    // void Animatable::SetAnimationTime(float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("DebugRenderer", "void SetAnimationTime(float)", asMETHODPR(DebugRenderer, SetAnimationTime, (float), void), asCALL_THISCALL);
    // bool Serializable::SetAttribute(unsigned index, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("DebugRenderer", "bool SetAttribute(uint, const Variant&in)", asMETHODPR(DebugRenderer, SetAttribute, (unsigned, const Variant&), bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("DebugRenderer", "bool set_attributes(uint, const Variant&in)", asMETHODPR(DebugRenderer, SetAttribute, (unsigned, const Variant&), bool), asCALL_THISCALL);
    // bool Serializable::SetAttribute(const String& name, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("DebugRenderer", "bool SetAttribute(const String&in, const Variant&in)", asMETHODPR(DebugRenderer, SetAttribute, (const String&, const Variant&), bool), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimation(const String& name, ValueAnimation* attributeAnimation, WrapMode wrapMode=WM_LOOP, float speed=1.0f) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("DebugRenderer", "void SetAttributeAnimation(const String&in, ValueAnimation@+, WrapMode = WM_LOOP, float = 1.0f)", asMETHODPR(DebugRenderer, SetAttributeAnimation, (const String&, ValueAnimation*, WrapMode, float), void), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimationSpeed(const String& name, float speed) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("DebugRenderer", "void SetAttributeAnimationSpeed(const String&in, float)", asMETHODPR(DebugRenderer, SetAttributeAnimationSpeed, (const String&, float), void), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimationTime(const String& name, float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("DebugRenderer", "void SetAttributeAnimationTime(const String&in, float)", asMETHODPR(DebugRenderer, SetAttributeAnimationTime, (const String&, float), void), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimationWrapMode(const String& name, WrapMode wrapMode) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("DebugRenderer", "void SetAttributeAnimationWrapMode(const String&in, WrapMode)", asMETHODPR(DebugRenderer, SetAttributeAnimationWrapMode, (const String&, WrapMode), void), asCALL_THISCALL);
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("DebugRenderer", "void SetBlockEvents(bool)", asMETHODPR(DebugRenderer, SetBlockEvents, (bool), void), asCALL_THISCALL);
    // void Component::SetEnabled(bool enable) | File: ../Scene/Component.h
    engine->RegisterObjectMethod("DebugRenderer", "void SetEnabled(bool)", asMETHODPR(DebugRenderer, SetEnabled, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("DebugRenderer", "void set_enabled(bool)", asMETHODPR(DebugRenderer, SetEnabled, (bool), void), asCALL_THISCALL);
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("DebugRenderer", "void SetGlobalVar(StringHash, const Variant&in)", asMETHODPR(DebugRenderer, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("DebugRenderer", "void set_globalVar(StringHash, const Variant&in)", asMETHODPR(DebugRenderer, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    // void Serializable::SetInstanceDefault(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("DebugRenderer", "void SetInstanceDefault(bool)", asMETHODPR(DebugRenderer, SetInstanceDefault, (bool), void), asCALL_THISCALL);
    // void Serializable::SetInterceptNetworkUpdate(const String& attributeName, bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("DebugRenderer", "void SetInterceptNetworkUpdate(const String&in, bool)", asMETHODPR(DebugRenderer, SetInterceptNetworkUpdate, (const String&, bool), void), asCALL_THISCALL);
    // void DebugRenderer::SetLineAntiAlias(bool enable) | File: ../Graphics/DebugRenderer.h
    engine->RegisterObjectMethod("DebugRenderer", "void SetLineAntiAlias(bool)", asMETHODPR(DebugRenderer, SetLineAntiAlias, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("DebugRenderer", "void set_lineAntiAlias(bool)", asMETHODPR(DebugRenderer, SetLineAntiAlias, (bool), void), asCALL_THISCALL);
    // void Animatable::SetObjectAnimation(ObjectAnimation* objectAnimation) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("DebugRenderer", "void SetObjectAnimation(ObjectAnimation@+)", asMETHODPR(DebugRenderer, SetObjectAnimation, (ObjectAnimation*), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("DebugRenderer", "void set_objectAnimation(ObjectAnimation@+)", asMETHODPR(DebugRenderer, SetObjectAnimation, (ObjectAnimation*), void), asCALL_THISCALL);
    // void Animatable::SetObjectAnimationAttr(const ResourceRef& value) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("DebugRenderer", "void SetObjectAnimationAttr(const ResourceRef&in)", asMETHODPR(DebugRenderer, SetObjectAnimationAttr, (const ResourceRef&), void), asCALL_THISCALL);
    // void Serializable::SetTemporary(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("DebugRenderer", "void SetTemporary(bool)", asMETHODPR(DebugRenderer, SetTemporary, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("DebugRenderer", "void set_temporary(bool)", asMETHODPR(DebugRenderer, SetTemporary, (bool), void), asCALL_THISCALL);
    // void DebugRenderer::SetView(Camera* camera) | File: ../Graphics/DebugRenderer.h
    engine->RegisterObjectMethod("DebugRenderer", "void SetView(Camera@+)", asMETHODPR(DebugRenderer, SetView, (Camera*), void), asCALL_THISCALL);
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod("DebugRenderer", "void UnsubscribeFromAllEvents()", asMETHODPR(DebugRenderer, UnsubscribeFromAllEvents, (), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("DebugRenderer", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", asFUNCTION(DebugRenderer_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), asCALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("DebugRenderer", "void UnsubscribeFromEvent(StringHash)", asMETHODPR(DebugRenderer, UnsubscribeFromEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("DebugRenderer", "void UnsubscribeFromEvent(Object@+, StringHash)", asMETHODPR(DebugRenderer, UnsubscribeFromEvent, (Object*, StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("DebugRenderer", "void UnsubscribeFromEvents(Object@+)", asMETHODPR(DebugRenderer, UnsubscribeFromEvents, (Object*), void), asCALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("DebugRenderer", "int WeakRefs() const", asMETHODPR(DebugRenderer, WeakRefs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("DebugRenderer", "int get_weakRefs() const", asMETHODPR(DebugRenderer, WeakRefs, () const, int), asCALL_THISCALL);
    // void Serializable::WriteDeltaUpdate(Serializer& dest, const DirtyBits& attributeBits, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("DebugRenderer", "void WriteDeltaUpdate(Serializer&, const DirtyBits&in, uint8)", asMETHODPR(DebugRenderer, WriteDeltaUpdate, (Serializer&, const DirtyBits&, unsigned char), void), asCALL_THISCALL);
    // void Serializable::WriteInitialDeltaUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("DebugRenderer", "void WriteInitialDeltaUpdate(Serializer&, uint8)", asMETHODPR(DebugRenderer, WriteInitialDeltaUpdate, (Serializer&, unsigned char), void), asCALL_THISCALL);
    // void Serializable::WriteLatestDataUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("DebugRenderer", "void WriteLatestDataUpdate(Serializer&, uint8)", asMETHODPR(DebugRenderer, WriteLatestDataUpdate, (Serializer&, unsigned char), void), asCALL_THISCALL);
#ifdef REGISTER_MANUAL_PART_Component
    REGISTER_MANUAL_PART_Component(DebugRenderer, "DebugRenderer")
#endif
#ifdef REGISTER_MANUAL_PART_Animatable
    REGISTER_MANUAL_PART_Animatable(DebugRenderer, "DebugRenderer")
#endif
#ifdef REGISTER_MANUAL_PART_Serializable
    REGISTER_MANUAL_PART_Serializable(DebugRenderer, "DebugRenderer")
#endif
#ifdef REGISTER_MANUAL_PART_Object
    REGISTER_MANUAL_PART_Object(DebugRenderer, "DebugRenderer")
#endif
#ifdef REGISTER_MANUAL_PART_RefCounted
    REGISTER_MANUAL_PART_RefCounted(DebugRenderer, "DebugRenderer")
#endif
#ifdef REGISTER_MANUAL_PART_DebugRenderer
    REGISTER_MANUAL_PART_DebugRenderer(DebugRenderer, "DebugRenderer")
#endif
    RegisterSubclass<Component, DebugRenderer>(engine, "Component", "DebugRenderer");
    RegisterSubclass<Animatable, DebugRenderer>(engine, "Animatable", "DebugRenderer");
    RegisterSubclass<Serializable, DebugRenderer>(engine, "Serializable", "DebugRenderer");
    RegisterSubclass<Object, DebugRenderer>(engine, "Object", "DebugRenderer");
    RegisterSubclass<RefCounted, DebugRenderer>(engine, "RefCounted", "DebugRenderer");

    // bool DecalSet::AddDecal(Drawable* target, const Vector3& worldPosition, const Quaternion& worldRotation, float size, float aspectRatio, float depth, const Vector2& topLeftUV, const Vector2& bottomRightUV, float timeToLive=0.0f, float normalCutoff=0.1f, unsigned subGeometry=M_MAX_UNSIGNED) | File: ../Graphics/DecalSet.h
    engine->RegisterObjectMethod("DecalSet", "bool AddDecal(Drawable@+, const Vector3&in, const Quaternion&in, float, float, float, const Vector2&in, const Vector2&in, float = 0.0f, float = 0.1f, uint = M_MAX_UNSIGNED)", asMETHODPR(DecalSet, AddDecal, (Drawable*, const Vector3&, const Quaternion&, float, float, float, const Vector2&, const Vector2&, float, float, unsigned), bool), asCALL_THISCALL);
    // void Drawable::AddLight(Light* light) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("DecalSet", "void AddLight(Light@+)", asMETHODPR(DecalSet, AddLight, (Light*), void), asCALL_THISCALL);
    // void RefCounted::AddRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("DecalSet", asBEHAVE_ADDREF, "void f()", asMETHODPR(DecalSet, AddRef, (), void), asCALL_THISCALL);
    // void Component::AddReplicationState(ComponentReplicationState* state) | File: ../Scene/Component.h
    // Error: type "ComponentReplicationState*" can not automatically bind
    // void Drawable::AddVertexLight(Light* light) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("DecalSet", "void AddVertexLight(Light@+)", asMETHODPR(DecalSet, AddVertexLight, (Light*), void), asCALL_THISCALL);
    // void Serializable::AllocateNetworkState() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("DecalSet", "void AllocateNetworkState()", asMETHODPR(DecalSet, AllocateNetworkState, (), void), asCALL_THISCALL);
    // void DecalSet::ApplyAttributes() override | File: ../Graphics/DecalSet.h
    engine->RegisterObjectMethod("DecalSet", "void ApplyAttributes()", asMETHODPR(DecalSet, ApplyAttributes, (), void), asCALL_THISCALL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // void Component::CleanupConnection(Connection* connection) | File: ../Scene/Component.h
    // Not registered because have @manualbind mark
    // explicit DecalSet::DecalSet(Context* context) | File: ../Graphics/DecalSet.h
    engine->RegisterObjectBehaviour("DecalSet", asBEHAVE_FACTORY, "DecalSet@+ f()", asFUNCTION(DecalSet_DecalSet_Context), asCALL_CDECL);
    // void Drawable::DrawDebugGeometry(DebugRenderer* debug, bool depthTest) override | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("DecalSet", "void DrawDebugGeometry(DebugRenderer@+, bool)", asMETHODPR(DecalSet, DrawDebugGeometry, (DebugRenderer*, bool), void), asCALL_THISCALL);
    // virtual bool Drawable::DrawOcclusion(OcclusionBuffer* buffer) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("DecalSet", "bool DrawOcclusion(OcclusionBuffer@+)", asMETHODPR(DecalSet, DrawOcclusion, (OcclusionBuffer*), bool), asCALL_THISCALL);
    // bool Animatable::GetAnimationEnabled() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("DecalSet", "bool GetAnimationEnabled() const", asMETHODPR(DecalSet, GetAnimationEnabled, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("DecalSet", "bool get_animationEnabled() const", asMETHODPR(DecalSet, GetAnimationEnabled, () const, bool), asCALL_THISCALL);
    // Variant Serializable::GetAttribute(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("DecalSet", "Variant GetAttribute(uint) const", asMETHODPR(DecalSet, GetAttribute, (unsigned) const, Variant), asCALL_THISCALL);
    engine->RegisterObjectMethod("DecalSet", "Variant get_attributes(uint) const", asMETHODPR(DecalSet, GetAttribute, (unsigned) const, Variant), asCALL_THISCALL);
    // Variant Serializable::GetAttribute(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("DecalSet", "Variant GetAttribute(const String&in) const", asMETHODPR(DecalSet, GetAttribute, (const String&) const, Variant), asCALL_THISCALL);
    // ValueAnimation* Animatable::GetAttributeAnimation(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("DecalSet", "ValueAnimation@+ GetAttributeAnimation(const String&in) const", asMETHODPR(DecalSet, GetAttributeAnimation, (const String&) const, ValueAnimation*), asCALL_THISCALL);
    // float Animatable::GetAttributeAnimationSpeed(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("DecalSet", "float GetAttributeAnimationSpeed(const String&in) const", asMETHODPR(DecalSet, GetAttributeAnimationSpeed, (const String&) const, float), asCALL_THISCALL);
    // float Animatable::GetAttributeAnimationTime(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("DecalSet", "float GetAttributeAnimationTime(const String&in) const", asMETHODPR(DecalSet, GetAttributeAnimationTime, (const String&) const, float), asCALL_THISCALL);
    // WrapMode Animatable::GetAttributeAnimationWrapMode(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("DecalSet", "WrapMode GetAttributeAnimationWrapMode(const String&in) const", asMETHODPR(DecalSet, GetAttributeAnimationWrapMode, (const String&) const, WrapMode), asCALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("DecalSet", "Variant GetAttributeDefault(uint) const", asMETHODPR(DecalSet, GetAttributeDefault, (unsigned) const, Variant), asCALL_THISCALL);
    engine->RegisterObjectMethod("DecalSet", "Variant get_attributeDefaults(uint) const", asMETHODPR(DecalSet, GetAttributeDefault, (unsigned) const, Variant), asCALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("DecalSet", "Variant GetAttributeDefault(const String&in) const", asMETHODPR(DecalSet, GetAttributeDefault, (const String&) const, Variant), asCALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // const Vector<SourceBatch>& Drawable::GetBatches() const | File: ../Graphics/Drawable.h
    // Error: type "const Vector<SourceBatch>&" can not automatically bind
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("DecalSet", "bool GetBlockEvents() const", asMETHODPR(DecalSet, GetBlockEvents, () const, bool), asCALL_THISCALL);
    // const BoundingBox& Drawable::GetBoundingBox() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("DecalSet", "const BoundingBox& GetBoundingBox() const", asMETHODPR(DecalSet, GetBoundingBox, () const, const BoundingBox&), asCALL_THISCALL);
    engine->RegisterObjectMethod("DecalSet", "const BoundingBox& get_boundingBox() const", asMETHODPR(DecalSet, GetBoundingBox, () const, const BoundingBox&), asCALL_THISCALL);
    // bool Drawable::GetCastShadows() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("DecalSet", "bool GetCastShadows() const", asMETHODPR(DecalSet, GetCastShadows, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("DecalSet", "bool get_castShadows() const", asMETHODPR(DecalSet, GetCastShadows, () const, bool), asCALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("DecalSet", "const String& GetCategory() const", asMETHODPR(DecalSet, GetCategory, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("DecalSet", "const String& get_category() const", asMETHODPR(DecalSet, GetCategory, () const, const String&), asCALL_THISCALL);
    // Component* Component::GetComponent(StringHash type) const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("DecalSet", "Component@+ GetComponent(StringHash) const", asMETHODPR(DecalSet, GetComponent, (StringHash) const, Component*), asCALL_THISCALL);
    // template<class T> T* Component::GetComponent() const | File: ../Scene/Component.h
    // Not registered because template
    // void Component::GetComponents(PODVector<Component*>& dest, StringHash type) const | File: ../Scene/Component.h
    // Error: type "PODVector<Component*>&" can not automatically bind
    // template<class T> void Component::GetComponents(PODVector<T*>& dest) const | File: ../Scene/Component.h
    // Not registered because template
    // Context* Object::GetContext() const | File: ../Core/Object.h
    // Error: type "Context*" can used only as function parameter
    // PODVector<unsigned char> DecalSet::GetDecalsAttr() const | File: ../Graphics/DecalSet.h
    // Error: type "PODVector<unsigned char>" can not automatically bind
    // virtual void Component::GetDependencyNodes(PODVector<Node*>& dest) | File: ../Scene/Component.h
    // Error: type "PODVector<Node*>&" can not automatically bind
    // float Drawable::GetDistance() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("DecalSet", "float GetDistance() const", asMETHODPR(DecalSet, GetDistance, () const, float), asCALL_THISCALL);
    // unsigned char Drawable::GetDrawableFlags() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("DecalSet", "uint8 GetDrawableFlags() const", asMETHODPR(DecalSet, GetDrawableFlags, () const, unsigned char), asCALL_THISCALL);
    // float Drawable::GetDrawDistance() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("DecalSet", "float GetDrawDistance() const", asMETHODPR(DecalSet, GetDrawDistance, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("DecalSet", "float get_drawDistance() const", asMETHODPR(DecalSet, GetDrawDistance, () const, float), asCALL_THISCALL);
    // VariantMap& Object::GetEventDataMap() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("DecalSet", "VariantMap& GetEventDataMap() const", asMETHODPR(DecalSet, GetEventDataMap, () const, VariantMap&), asCALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("DecalSet", "Object@+ GetEventSender() const", asMETHODPR(DecalSet, GetEventSender, () const, Object*), asCALL_THISCALL);
    // Light* Drawable::GetFirstLight() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("DecalSet", "Light@+ GetFirstLight() const", asMETHODPR(DecalSet, GetFirstLight, () const, Light*), asCALL_THISCALL);
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("DecalSet", "const Variant& GetGlobalVar(StringHash) const", asMETHODPR(DecalSet, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    engine->RegisterObjectMethod("DecalSet", "const Variant& get_globalVar(StringHash) const", asMETHODPR(DecalSet, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("DecalSet", "const VariantMap& GetGlobalVars() const", asMETHODPR(DecalSet, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    engine->RegisterObjectMethod("DecalSet", "const VariantMap& get_globalVars() const", asMETHODPR(DecalSet, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    // unsigned Component::GetID() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("DecalSet", "uint GetID() const", asMETHODPR(DecalSet, GetID, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("DecalSet", "uint get_id() const", asMETHODPR(DecalSet, GetID, () const, unsigned), asCALL_THISCALL);
    // bool Serializable::GetInterceptNetworkUpdate(const String& attributeName) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("DecalSet", "bool GetInterceptNetworkUpdate(const String&in) const", asMETHODPR(DecalSet, GetInterceptNetworkUpdate, (const String&) const, bool), asCALL_THISCALL);
    // unsigned Drawable::GetLightMask() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("DecalSet", "uint GetLightMask() const", asMETHODPR(DecalSet, GetLightMask, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("DecalSet", "uint get_lightMask() const", asMETHODPR(DecalSet, GetLightMask, () const, unsigned), asCALL_THISCALL);
    // const PODVector<Light*>& Drawable::GetLights() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("DecalSet", "Array<Light@>@ GetLights() const", asFUNCTION(DecalSet_GetLights_void), asCALL_CDECL_OBJFIRST);
    // float Drawable::GetLodBias() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("DecalSet", "float GetLodBias() const", asMETHODPR(DecalSet, GetLodBias, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("DecalSet", "float get_lodBias() const", asMETHODPR(DecalSet, GetLodBias, () const, float), asCALL_THISCALL);
    // float Drawable::GetLodDistance() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("DecalSet", "float GetLodDistance() const", asMETHODPR(DecalSet, GetLodDistance, () const, float), asCALL_THISCALL);
    // virtual Geometry* Drawable::GetLodGeometry(unsigned batchIndex, unsigned level) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("DecalSet", "Geometry@+ GetLodGeometry(uint, uint)", asMETHODPR(DecalSet, GetLodGeometry, (unsigned, unsigned), Geometry*), asCALL_THISCALL);
    // Material* DecalSet::GetMaterial() const | File: ../Graphics/DecalSet.h
    engine->RegisterObjectMethod("DecalSet", "Material@+ GetMaterial() const", asMETHODPR(DecalSet, GetMaterial, () const, Material*), asCALL_THISCALL);
    engine->RegisterObjectMethod("DecalSet", "Material@+ get_material() const", asMETHODPR(DecalSet, GetMaterial, () const, Material*), asCALL_THISCALL);
    // ResourceRef DecalSet::GetMaterialAttr() const | File: ../Graphics/DecalSet.h
    engine->RegisterObjectMethod("DecalSet", "ResourceRef GetMaterialAttr() const", asMETHODPR(DecalSet, GetMaterialAttr, () const, ResourceRef), asCALL_THISCALL);
    // unsigned DecalSet::GetMaxIndices() const | File: ../Graphics/DecalSet.h
    engine->RegisterObjectMethod("DecalSet", "uint GetMaxIndices() const", asMETHODPR(DecalSet, GetMaxIndices, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("DecalSet", "uint get_maxIndices() const", asMETHODPR(DecalSet, GetMaxIndices, () const, unsigned), asCALL_THISCALL);
    // unsigned Drawable::GetMaxLights() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("DecalSet", "uint GetMaxLights() const", asMETHODPR(DecalSet, GetMaxLights, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("DecalSet", "uint get_maxLights() const", asMETHODPR(DecalSet, GetMaxLights, () const, unsigned), asCALL_THISCALL);
    // unsigned DecalSet::GetMaxVertices() const | File: ../Graphics/DecalSet.h
    engine->RegisterObjectMethod("DecalSet", "uint GetMaxVertices() const", asMETHODPR(DecalSet, GetMaxVertices, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("DecalSet", "uint get_maxVertices() const", asMETHODPR(DecalSet, GetMaxVertices, () const, unsigned), asCALL_THISCALL);
    // float Drawable::GetMaxZ() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("DecalSet", "float GetMaxZ() const", asMETHODPR(DecalSet, GetMaxZ, () const, float), asCALL_THISCALL);
    // float Drawable::GetMinZ() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("DecalSet", "float GetMinZ() const", asMETHODPR(DecalSet, GetMinZ, () const, float), asCALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetNetworkAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // NetworkState* Serializable::GetNetworkState() const | File: ../Scene/Serializable.h
    // Error: type "NetworkState*" can not automatically bind
    // Node* Component::GetNode() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("DecalSet", "Node@+ GetNode() const", asMETHODPR(DecalSet, GetNode, () const, Node*), asCALL_THISCALL);
    engine->RegisterObjectMethod("DecalSet", "Node@+ get_node() const", asMETHODPR(DecalSet, GetNode, () const, Node*), asCALL_THISCALL);
    // unsigned Serializable::GetNumAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("DecalSet", "uint GetNumAttributes() const", asMETHODPR(DecalSet, GetNumAttributes, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("DecalSet", "uint get_numAttributes() const", asMETHODPR(DecalSet, GetNumAttributes, () const, unsigned), asCALL_THISCALL);
    // unsigned DecalSet::GetNumDecals() const | File: ../Graphics/DecalSet.h
    engine->RegisterObjectMethod("DecalSet", "uint GetNumDecals() const", asMETHODPR(DecalSet, GetNumDecals, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("DecalSet", "uint get_numDecals() const", asMETHODPR(DecalSet, GetNumDecals, () const, unsigned), asCALL_THISCALL);
    // unsigned DecalSet::GetNumIndices() const | File: ../Graphics/DecalSet.h
    engine->RegisterObjectMethod("DecalSet", "uint GetNumIndices() const", asMETHODPR(DecalSet, GetNumIndices, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("DecalSet", "uint get_numIndices() const", asMETHODPR(DecalSet, GetNumIndices, () const, unsigned), asCALL_THISCALL);
    // unsigned Serializable::GetNumNetworkAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("DecalSet", "uint GetNumNetworkAttributes() const", asMETHODPR(DecalSet, GetNumNetworkAttributes, () const, unsigned), asCALL_THISCALL);
    // virtual unsigned Drawable::GetNumOccluderTriangles() | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("DecalSet", "uint GetNumOccluderTriangles()", asMETHODPR(DecalSet, GetNumOccluderTriangles, (), unsigned), asCALL_THISCALL);
    // unsigned DecalSet::GetNumVertices() const | File: ../Graphics/DecalSet.h
    engine->RegisterObjectMethod("DecalSet", "uint GetNumVertices() const", asMETHODPR(DecalSet, GetNumVertices, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("DecalSet", "uint get_numVertices() const", asMETHODPR(DecalSet, GetNumVertices, () const, unsigned), asCALL_THISCALL);
    // ObjectAnimation* Animatable::GetObjectAnimation() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("DecalSet", "ObjectAnimation@+ GetObjectAnimation() const", asMETHODPR(DecalSet, GetObjectAnimation, () const, ObjectAnimation*), asCALL_THISCALL);
    engine->RegisterObjectMethod("DecalSet", "ObjectAnimation@+ get_objectAnimation() const", asMETHODPR(DecalSet, GetObjectAnimation, () const, ObjectAnimation*), asCALL_THISCALL);
    // ResourceRef Animatable::GetObjectAnimationAttr() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("DecalSet", "ResourceRef GetObjectAnimationAttr() const", asMETHODPR(DecalSet, GetObjectAnimationAttr, () const, ResourceRef), asCALL_THISCALL);
    // Octant* Drawable::GetOctant() const | File: ../Graphics/Drawable.h
    // Error: type "Octant" can not automatically bind bacause have @nobind mark
    // bool DecalSet::GetOptimizeBufferSize() const | File: ../Graphics/DecalSet.h
    engine->RegisterObjectMethod("DecalSet", "bool GetOptimizeBufferSize() const", asMETHODPR(DecalSet, GetOptimizeBufferSize, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("DecalSet", "bool get_optimizeBufferSize() const", asMETHODPR(DecalSet, GetOptimizeBufferSize, () const, bool), asCALL_THISCALL);
    // Scene* Component::GetScene() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("DecalSet", "Scene@+ GetScene() const", asMETHODPR(DecalSet, GetScene, () const, Scene*), asCALL_THISCALL);
    // float Drawable::GetShadowDistance() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("DecalSet", "float GetShadowDistance() const", asMETHODPR(DecalSet, GetShadowDistance, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("DecalSet", "float get_shadowDistance() const", asMETHODPR(DecalSet, GetShadowDistance, () const, float), asCALL_THISCALL);
    // unsigned Drawable::GetShadowMask() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("DecalSet", "uint GetShadowMask() const", asMETHODPR(DecalSet, GetShadowMask, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("DecalSet", "uint get_shadowMask() const", asMETHODPR(DecalSet, GetShadowMask, () const, unsigned), asCALL_THISCALL);
    // float Drawable::GetSortValue() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("DecalSet", "float GetSortValue() const", asMETHODPR(DecalSet, GetSortValue, () const, float), asCALL_THISCALL);
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("DecalSet", "Object@+ GetSubsystem(StringHash) const", asMETHODPR(DecalSet, GetSubsystem, (StringHash) const, Object*), asCALL_THISCALL);
    // template<class T> T* Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("DecalSet", "StringHash GetType() const", asMETHODPR(DecalSet, GetType, () const, StringHash), asCALL_THISCALL);
    engine->RegisterObjectMethod("DecalSet", "StringHash get_type() const", asMETHODPR(DecalSet, GetType, () const, StringHash), asCALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("DecalSet", "const String& GetTypeName() const", asMETHODPR(DecalSet, GetTypeName, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("DecalSet", "const String& get_typeName() const", asMETHODPR(DecalSet, GetTypeName, () const, const String&), asCALL_THISCALL);
    // UpdateGeometryType DecalSet::GetUpdateGeometryType() override | File: ../Graphics/DecalSet.h
    engine->RegisterObjectMethod("DecalSet", "UpdateGeometryType GetUpdateGeometryType()", asMETHODPR(DecalSet, GetUpdateGeometryType, (), UpdateGeometryType), asCALL_THISCALL);
    // const PODVector<Light*>& Drawable::GetVertexLights() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("DecalSet", "Array<Light@>@ GetVertexLights() const", asFUNCTION(DecalSet_GetVertexLights_void), asCALL_CDECL_OBJFIRST);
    // unsigned Drawable::GetViewMask() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("DecalSet", "uint GetViewMask() const", asMETHODPR(DecalSet, GetViewMask, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("DecalSet", "uint get_viewMask() const", asMETHODPR(DecalSet, GetViewMask, () const, unsigned), asCALL_THISCALL);
    // const BoundingBox& Drawable::GetWorldBoundingBox() | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("DecalSet", "const BoundingBox& GetWorldBoundingBox()", asMETHODPR(DecalSet, GetWorldBoundingBox, (), const BoundingBox&), asCALL_THISCALL);
    engine->RegisterObjectMethod("DecalSet", "const BoundingBox& get_worldBoundingBox()", asMETHODPR(DecalSet, GetWorldBoundingBox, (), const BoundingBox&), asCALL_THISCALL);
    // Zone* Drawable::GetZone() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("DecalSet", "Zone@+ GetZone() const", asMETHODPR(DecalSet, GetZone, () const, Zone*), asCALL_THISCALL);
    engine->RegisterObjectMethod("DecalSet", "Zone@+ get_zone() const", asMETHODPR(DecalSet, GetZone, () const, Zone*), asCALL_THISCALL);
    // unsigned Drawable::GetZoneMask() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("DecalSet", "uint GetZoneMask() const", asMETHODPR(DecalSet, GetZoneMask, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("DecalSet", "uint get_zoneMask() const", asMETHODPR(DecalSet, GetZoneMask, () const, unsigned), asCALL_THISCALL);
    // bool Drawable::HasBasePass(unsigned batchIndex) const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("DecalSet", "bool HasBasePass(uint) const", asMETHODPR(DecalSet, HasBasePass, (unsigned) const, bool), asCALL_THISCALL);
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("DecalSet", "bool HasEventHandlers() const", asMETHODPR(DecalSet, HasEventHandlers, () const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("DecalSet", "bool HasSubscribedToEvent(StringHash) const", asMETHODPR(DecalSet, HasSubscribedToEvent, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("DecalSet", "bool HasSubscribedToEvent(Object@+, StringHash) const", asMETHODPR(DecalSet, HasSubscribedToEvent, (Object*, StringHash) const, bool), asCALL_THISCALL);
    // bool Component::IsEnabled() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("DecalSet", "bool IsEnabled() const", asMETHODPR(DecalSet, IsEnabled, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("DecalSet", "bool get_enabled() const", asMETHODPR(DecalSet, IsEnabled, () const, bool), asCALL_THISCALL);
    // bool Component::IsEnabledEffective() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("DecalSet", "bool IsEnabledEffective() const", asMETHODPR(DecalSet, IsEnabledEffective, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("DecalSet", "bool get_enabledEffective() const", asMETHODPR(DecalSet, IsEnabledEffective, () const, bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("DecalSet", "bool IsInstanceOf(StringHash) const", asMETHODPR(DecalSet, IsInstanceOf, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // bool Drawable::IsInView() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("DecalSet", "bool IsInView() const", asMETHODPR(DecalSet, IsInView, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("DecalSet", "bool get_inView() const", asMETHODPR(DecalSet, IsInView, () const, bool), asCALL_THISCALL);
    // bool Drawable::IsInView(Camera* camera) const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("DecalSet", "bool IsInView(Camera@+) const", asMETHODPR(DecalSet, IsInView, (Camera*) const, bool), asCALL_THISCALL);
    // bool Drawable::IsInView(const FrameInfo& frame, bool anyCamera=false) const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("DecalSet", "bool IsInView(const FrameInfo&in, bool = false) const", asMETHODPR(DecalSet, IsInView, (const FrameInfo&, bool) const, bool), asCALL_THISCALL);
    // bool Drawable::IsOccludee() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("DecalSet", "bool IsOccludee() const", asMETHODPR(DecalSet, IsOccludee, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("DecalSet", "bool get_occludee() const", asMETHODPR(DecalSet, IsOccludee, () const, bool), asCALL_THISCALL);
    // bool Drawable::IsOccluder() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("DecalSet", "bool IsOccluder() const", asMETHODPR(DecalSet, IsOccluder, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("DecalSet", "bool get_occluder() const", asMETHODPR(DecalSet, IsOccluder, () const, bool), asCALL_THISCALL);
    // bool Component::IsReplicated() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("DecalSet", "bool IsReplicated() const", asMETHODPR(DecalSet, IsReplicated, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("DecalSet", "bool get_replicated() const", asMETHODPR(DecalSet, IsReplicated, () const, bool), asCALL_THISCALL);
    // bool Serializable::IsTemporary() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("DecalSet", "bool IsTemporary() const", asMETHODPR(DecalSet, IsTemporary, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("DecalSet", "bool get_temporary() const", asMETHODPR(DecalSet, IsTemporary, () const, bool), asCALL_THISCALL);
    // bool Drawable::IsZoneDirty() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("DecalSet", "bool IsZoneDirty() const", asMETHODPR(DecalSet, IsZoneDirty, () const, bool), asCALL_THISCALL);
    // void Drawable::LimitLights() | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("DecalSet", "void LimitLights()", asMETHODPR(DecalSet, LimitLights, (), void), asCALL_THISCALL);
    // void Drawable::LimitVertexLights(bool removeConvertedLights) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("DecalSet", "void LimitVertexLights(bool)", asMETHODPR(DecalSet, LimitVertexLights, (bool), void), asCALL_THISCALL);
    // virtual bool Serializable::Load(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("DecalSet", "bool Load(Deserializer&)", asMETHODPR(DecalSet, Load, (Deserializer&), bool), asCALL_THISCALL);
    // bool Animatable::LoadJSON(const JSONValue& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("DecalSet", "bool LoadJSON(const JSONValue&in)", asMETHODPR(DecalSet, LoadJSON, (const JSONValue&), bool), asCALL_THISCALL);
    // bool Animatable::LoadXML(const XMLElement& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("DecalSet", "bool LoadXML(const XMLElement&in)", asMETHODPR(DecalSet, LoadXML, (const XMLElement&), bool), asCALL_THISCALL);
    // void Drawable::MarkForUpdate() | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("DecalSet", "void MarkForUpdate()", asMETHODPR(DecalSet, MarkForUpdate, (), void), asCALL_THISCALL);
    // void Drawable::MarkInView(const FrameInfo& frame) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("DecalSet", "void MarkInView(const FrameInfo&in)", asMETHODPR(DecalSet, MarkInView, (const FrameInfo&), void), asCALL_THISCALL);
    // void Drawable::MarkInView(unsigned frameNumber) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("DecalSet", "void MarkInView(uint)", asMETHODPR(DecalSet, MarkInView, (unsigned), void), asCALL_THISCALL);
    // void Component::MarkNetworkUpdate() override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("DecalSet", "void MarkNetworkUpdate()", asMETHODPR(DecalSet, MarkNetworkUpdate, (), void), asCALL_THISCALL);
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("DecalSet", "void OnEvent(Object@+, StringHash, VariantMap&)", asMETHODPR(DecalSet, OnEvent, (Object*, StringHash, VariantMap&), void), asCALL_THISCALL);
    // virtual void Serializable::OnGetAttribute(const AttributeInfo& attr, Variant& dest) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("DecalSet", "void OnGetAttribute(const AttributeInfo&in, Variant&) const", asMETHODPR(DecalSet, OnGetAttribute, (const AttributeInfo&, Variant&) const, void), asCALL_THISCALL);
    // virtual void Serializable::OnSetAttribute(const AttributeInfo& attr, const Variant& src) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("DecalSet", "void OnSetAttribute(const AttributeInfo&in, const Variant&in)", asMETHODPR(DecalSet, OnSetAttribute, (const AttributeInfo&, const Variant&), void), asCALL_THISCALL);
    // void DecalSet::OnSetEnabled() override | File: ../Graphics/DecalSet.h
    engine->RegisterObjectMethod("DecalSet", "void OnSetEnabled()", asMETHODPR(DecalSet, OnSetEnabled, (), void), asCALL_THISCALL);
    // void Component::PrepareNetworkUpdate() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("DecalSet", "void PrepareNetworkUpdate()", asMETHODPR(DecalSet, PrepareNetworkUpdate, (), void), asCALL_THISCALL);
    // void DecalSet::ProcessRayQuery(const RayOctreeQuery& query, PODVector<RayQueryResult>& results) override | File: ../Graphics/DecalSet.h
    // Error: type "RayOctreeQuery" can not automatically bind bacause have @nobind mark
    // bool Serializable::ReadDeltaUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("DecalSet", "bool ReadDeltaUpdate(Deserializer&)", asMETHODPR(DecalSet, ReadDeltaUpdate, (Deserializer&), bool), asCALL_THISCALL);
    // bool Serializable::ReadLatestDataUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("DecalSet", "bool ReadLatestDataUpdate(Deserializer&)", asMETHODPR(DecalSet, ReadLatestDataUpdate, (Deserializer&), bool), asCALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("DecalSet", "int Refs() const", asMETHODPR(DecalSet, Refs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("DecalSet", "int get_refs() const", asMETHODPR(DecalSet, Refs, () const, int), asCALL_THISCALL);
    // static void DecalSet::RegisterObject(Context* context) | File: ../Graphics/DecalSet.h
    // Not registered because have @nobind mark
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("DecalSet", asBEHAVE_RELEASE, "void f()", asMETHODPR(DecalSet, ReleaseRef, (), void), asCALL_THISCALL);
    // void Component::Remove() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("DecalSet", "void Remove()", asMETHODPR(DecalSet, Remove, (), void), asCALL_THISCALL);
    // void DecalSet::RemoveAllDecals() | File: ../Graphics/DecalSet.h
    engine->RegisterObjectMethod("DecalSet", "void RemoveAllDecals()", asMETHODPR(DecalSet, RemoveAllDecals, (), void), asCALL_THISCALL);
    // void Animatable::RemoveAttributeAnimation(const String& name) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("DecalSet", "void RemoveAttributeAnimation(const String&in)", asMETHODPR(DecalSet, RemoveAttributeAnimation, (const String&), void), asCALL_THISCALL);
    // void DecalSet::RemoveDecals(unsigned num) | File: ../Graphics/DecalSet.h
    engine->RegisterObjectMethod("DecalSet", "void RemoveDecals(uint)", asMETHODPR(DecalSet, RemoveDecals, (unsigned), void), asCALL_THISCALL);
    // void Serializable::RemoveInstanceDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("DecalSet", "void RemoveInstanceDefault()", asMETHODPR(DecalSet, RemoveInstanceDefault, (), void), asCALL_THISCALL);
    // void Animatable::RemoveObjectAnimation() | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("DecalSet", "void RemoveObjectAnimation()", asMETHODPR(DecalSet, RemoveObjectAnimation, (), void), asCALL_THISCALL);
    // void Serializable::ResetToDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("DecalSet", "void ResetToDefault()", asMETHODPR(DecalSet, ResetToDefault, (), void), asCALL_THISCALL);
    // bool Component::Save(Serializer& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("DecalSet", "bool Save(Serializer&) const", asMETHODPR(DecalSet, Save, (Serializer&) const, bool), asCALL_THISCALL);
    // virtual bool Serializable::SaveDefaultAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("DecalSet", "bool SaveDefaultAttributes() const", asMETHODPR(DecalSet, SaveDefaultAttributes, () const, bool), asCALL_THISCALL);
    // bool Component::SaveJSON(JSONValue& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("DecalSet", "bool SaveJSON(JSONValue&) const", asMETHODPR(DecalSet, SaveJSON, (JSONValue&) const, bool), asCALL_THISCALL);
    // bool Component::SaveXML(XMLElement& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("DecalSet", "bool SaveXML(XMLElement&) const", asMETHODPR(DecalSet, SaveXML, (XMLElement&) const, bool), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("DecalSet", "void SendEvent(StringHash)", asMETHODPR(DecalSet, SendEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("DecalSet", "void SendEvent(StringHash, VariantMap&)", asMETHODPR(DecalSet, SendEvent, (StringHash, VariantMap&), void), asCALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void Animatable::SetAnimationEnabled(bool enable) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("DecalSet", "void SetAnimationEnabled(bool)", asMETHODPR(DecalSet, SetAnimationEnabled, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("DecalSet", "void set_animationEnabled(bool)", asMETHODPR(DecalSet, SetAnimationEnabled, (bool), void), asCALL_THISCALL);
    // void Animatable::SetAnimationTime(float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("DecalSet", "void SetAnimationTime(float)", asMETHODPR(DecalSet, SetAnimationTime, (float), void), asCALL_THISCALL);
    // bool Serializable::SetAttribute(unsigned index, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("DecalSet", "bool SetAttribute(uint, const Variant&in)", asMETHODPR(DecalSet, SetAttribute, (unsigned, const Variant&), bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("DecalSet", "bool set_attributes(uint, const Variant&in)", asMETHODPR(DecalSet, SetAttribute, (unsigned, const Variant&), bool), asCALL_THISCALL);
    // bool Serializable::SetAttribute(const String& name, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("DecalSet", "bool SetAttribute(const String&in, const Variant&in)", asMETHODPR(DecalSet, SetAttribute, (const String&, const Variant&), bool), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimation(const String& name, ValueAnimation* attributeAnimation, WrapMode wrapMode=WM_LOOP, float speed=1.0f) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("DecalSet", "void SetAttributeAnimation(const String&in, ValueAnimation@+, WrapMode = WM_LOOP, float = 1.0f)", asMETHODPR(DecalSet, SetAttributeAnimation, (const String&, ValueAnimation*, WrapMode, float), void), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimationSpeed(const String& name, float speed) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("DecalSet", "void SetAttributeAnimationSpeed(const String&in, float)", asMETHODPR(DecalSet, SetAttributeAnimationSpeed, (const String&, float), void), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimationTime(const String& name, float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("DecalSet", "void SetAttributeAnimationTime(const String&in, float)", asMETHODPR(DecalSet, SetAttributeAnimationTime, (const String&, float), void), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimationWrapMode(const String& name, WrapMode wrapMode) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("DecalSet", "void SetAttributeAnimationWrapMode(const String&in, WrapMode)", asMETHODPR(DecalSet, SetAttributeAnimationWrapMode, (const String&, WrapMode), void), asCALL_THISCALL);
    // void Drawable::SetBasePass(unsigned batchIndex) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("DecalSet", "void SetBasePass(uint)", asMETHODPR(DecalSet, SetBasePass, (unsigned), void), asCALL_THISCALL);
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("DecalSet", "void SetBlockEvents(bool)", asMETHODPR(DecalSet, SetBlockEvents, (bool), void), asCALL_THISCALL);
    // void Drawable::SetCastShadows(bool enable) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("DecalSet", "void SetCastShadows(bool)", asMETHODPR(DecalSet, SetCastShadows, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("DecalSet", "void set_castShadows(bool)", asMETHODPR(DecalSet, SetCastShadows, (bool), void), asCALL_THISCALL);
    // void DecalSet::SetDecalsAttr(const PODVector<unsigned char>& value) | File: ../Graphics/DecalSet.h
    // Error: type "const PODVector<unsigned char>&" can not automatically bind
    // void Drawable::SetDrawDistance(float distance) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("DecalSet", "void SetDrawDistance(float)", asMETHODPR(DecalSet, SetDrawDistance, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("DecalSet", "void set_drawDistance(float)", asMETHODPR(DecalSet, SetDrawDistance, (float), void), asCALL_THISCALL);
    // void Component::SetEnabled(bool enable) | File: ../Scene/Component.h
    engine->RegisterObjectMethod("DecalSet", "void SetEnabled(bool)", asMETHODPR(DecalSet, SetEnabled, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("DecalSet", "void set_enabled(bool)", asMETHODPR(DecalSet, SetEnabled, (bool), void), asCALL_THISCALL);
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("DecalSet", "void SetGlobalVar(StringHash, const Variant&in)", asMETHODPR(DecalSet, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("DecalSet", "void set_globalVar(StringHash, const Variant&in)", asMETHODPR(DecalSet, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    // void Serializable::SetInstanceDefault(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("DecalSet", "void SetInstanceDefault(bool)", asMETHODPR(DecalSet, SetInstanceDefault, (bool), void), asCALL_THISCALL);
    // void Serializable::SetInterceptNetworkUpdate(const String& attributeName, bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("DecalSet", "void SetInterceptNetworkUpdate(const String&in, bool)", asMETHODPR(DecalSet, SetInterceptNetworkUpdate, (const String&, bool), void), asCALL_THISCALL);
    // void Drawable::SetLightMask(unsigned mask) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("DecalSet", "void SetLightMask(uint)", asMETHODPR(DecalSet, SetLightMask, (unsigned), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("DecalSet", "void set_lightMask(uint)", asMETHODPR(DecalSet, SetLightMask, (unsigned), void), asCALL_THISCALL);
    // void Drawable::SetLodBias(float bias) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("DecalSet", "void SetLodBias(float)", asMETHODPR(DecalSet, SetLodBias, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("DecalSet", "void set_lodBias(float)", asMETHODPR(DecalSet, SetLodBias, (float), void), asCALL_THISCALL);
    // void DecalSet::SetMaterial(Material* material) | File: ../Graphics/DecalSet.h
    engine->RegisterObjectMethod("DecalSet", "void SetMaterial(Material@+)", asMETHODPR(DecalSet, SetMaterial, (Material*), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("DecalSet", "void set_material(Material@+)", asMETHODPR(DecalSet, SetMaterial, (Material*), void), asCALL_THISCALL);
    // void DecalSet::SetMaterialAttr(const ResourceRef& value) | File: ../Graphics/DecalSet.h
    engine->RegisterObjectMethod("DecalSet", "void SetMaterialAttr(const ResourceRef&in)", asMETHODPR(DecalSet, SetMaterialAttr, (const ResourceRef&), void), asCALL_THISCALL);
    // void DecalSet::SetMaxIndices(unsigned num) | File: ../Graphics/DecalSet.h
    engine->RegisterObjectMethod("DecalSet", "void SetMaxIndices(uint)", asMETHODPR(DecalSet, SetMaxIndices, (unsigned), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("DecalSet", "void set_maxIndices(uint)", asMETHODPR(DecalSet, SetMaxIndices, (unsigned), void), asCALL_THISCALL);
    // void Drawable::SetMaxLights(unsigned num) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("DecalSet", "void SetMaxLights(uint)", asMETHODPR(DecalSet, SetMaxLights, (unsigned), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("DecalSet", "void set_maxLights(uint)", asMETHODPR(DecalSet, SetMaxLights, (unsigned), void), asCALL_THISCALL);
    // void DecalSet::SetMaxVertices(unsigned num) | File: ../Graphics/DecalSet.h
    engine->RegisterObjectMethod("DecalSet", "void SetMaxVertices(uint)", asMETHODPR(DecalSet, SetMaxVertices, (unsigned), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("DecalSet", "void set_maxVertices(uint)", asMETHODPR(DecalSet, SetMaxVertices, (unsigned), void), asCALL_THISCALL);
    // void Drawable::SetMinMaxZ(float minZ, float maxZ) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("DecalSet", "void SetMinMaxZ(float, float)", asMETHODPR(DecalSet, SetMinMaxZ, (float, float), void), asCALL_THISCALL);
    // void Animatable::SetObjectAnimation(ObjectAnimation* objectAnimation) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("DecalSet", "void SetObjectAnimation(ObjectAnimation@+)", asMETHODPR(DecalSet, SetObjectAnimation, (ObjectAnimation*), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("DecalSet", "void set_objectAnimation(ObjectAnimation@+)", asMETHODPR(DecalSet, SetObjectAnimation, (ObjectAnimation*), void), asCALL_THISCALL);
    // void Animatable::SetObjectAnimationAttr(const ResourceRef& value) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("DecalSet", "void SetObjectAnimationAttr(const ResourceRef&in)", asMETHODPR(DecalSet, SetObjectAnimationAttr, (const ResourceRef&), void), asCALL_THISCALL);
    // void Drawable::SetOccludee(bool enable) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("DecalSet", "void SetOccludee(bool)", asMETHODPR(DecalSet, SetOccludee, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("DecalSet", "void set_occludee(bool)", asMETHODPR(DecalSet, SetOccludee, (bool), void), asCALL_THISCALL);
    // void Drawable::SetOccluder(bool enable) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("DecalSet", "void SetOccluder(bool)", asMETHODPR(DecalSet, SetOccluder, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("DecalSet", "void set_occluder(bool)", asMETHODPR(DecalSet, SetOccluder, (bool), void), asCALL_THISCALL);
    // void DecalSet::SetOptimizeBufferSize(bool enable) | File: ../Graphics/DecalSet.h
    engine->RegisterObjectMethod("DecalSet", "void SetOptimizeBufferSize(bool)", asMETHODPR(DecalSet, SetOptimizeBufferSize, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("DecalSet", "void set_optimizeBufferSize(bool)", asMETHODPR(DecalSet, SetOptimizeBufferSize, (bool), void), asCALL_THISCALL);
    // void Drawable::SetShadowDistance(float distance) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("DecalSet", "void SetShadowDistance(float)", asMETHODPR(DecalSet, SetShadowDistance, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("DecalSet", "void set_shadowDistance(float)", asMETHODPR(DecalSet, SetShadowDistance, (float), void), asCALL_THISCALL);
    // void Drawable::SetShadowMask(unsigned mask) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("DecalSet", "void SetShadowMask(uint)", asMETHODPR(DecalSet, SetShadowMask, (unsigned), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("DecalSet", "void set_shadowMask(uint)", asMETHODPR(DecalSet, SetShadowMask, (unsigned), void), asCALL_THISCALL);
    // void Drawable::SetSortValue(float value) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("DecalSet", "void SetSortValue(float)", asMETHODPR(DecalSet, SetSortValue, (float), void), asCALL_THISCALL);
    // void Serializable::SetTemporary(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("DecalSet", "void SetTemporary(bool)", asMETHODPR(DecalSet, SetTemporary, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("DecalSet", "void set_temporary(bool)", asMETHODPR(DecalSet, SetTemporary, (bool), void), asCALL_THISCALL);
    // void Drawable::SetViewMask(unsigned mask) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("DecalSet", "void SetViewMask(uint)", asMETHODPR(DecalSet, SetViewMask, (unsigned), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("DecalSet", "void set_viewMask(uint)", asMETHODPR(DecalSet, SetViewMask, (unsigned), void), asCALL_THISCALL);
    // void Drawable::SetZone(Zone* zone, bool temporary=false) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("DecalSet", "void SetZone(Zone@+, bool = false)", asMETHODPR(DecalSet, SetZone, (Zone*, bool), void), asCALL_THISCALL);
    // void Drawable::SetZoneMask(unsigned mask) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("DecalSet", "void SetZoneMask(uint)", asMETHODPR(DecalSet, SetZoneMask, (unsigned), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("DecalSet", "void set_zoneMask(uint)", asMETHODPR(DecalSet, SetZoneMask, (unsigned), void), asCALL_THISCALL);
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod("DecalSet", "void UnsubscribeFromAllEvents()", asMETHODPR(DecalSet, UnsubscribeFromAllEvents, (), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("DecalSet", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", asFUNCTION(DecalSet_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), asCALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("DecalSet", "void UnsubscribeFromEvent(StringHash)", asMETHODPR(DecalSet, UnsubscribeFromEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("DecalSet", "void UnsubscribeFromEvent(Object@+, StringHash)", asMETHODPR(DecalSet, UnsubscribeFromEvent, (Object*, StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("DecalSet", "void UnsubscribeFromEvents(Object@+)", asMETHODPR(DecalSet, UnsubscribeFromEvents, (Object*), void), asCALL_THISCALL);
    // virtual void Drawable::Update(const FrameInfo& frame) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("DecalSet", "void Update(const FrameInfo&in)", asMETHODPR(DecalSet, Update, (const FrameInfo&), void), asCALL_THISCALL);
    // void DecalSet::UpdateBatches(const FrameInfo& frame) override | File: ../Graphics/DecalSet.h
    engine->RegisterObjectMethod("DecalSet", "void UpdateBatches(const FrameInfo&in)", asMETHODPR(DecalSet, UpdateBatches, (const FrameInfo&), void), asCALL_THISCALL);
    // void DecalSet::UpdateGeometry(const FrameInfo& frame) override | File: ../Graphics/DecalSet.h
    engine->RegisterObjectMethod("DecalSet", "void UpdateGeometry(const FrameInfo&in)", asMETHODPR(DecalSet, UpdateGeometry, (const FrameInfo&), void), asCALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("DecalSet", "int WeakRefs() const", asMETHODPR(DecalSet, WeakRefs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("DecalSet", "int get_weakRefs() const", asMETHODPR(DecalSet, WeakRefs, () const, int), asCALL_THISCALL);
    // void Serializable::WriteDeltaUpdate(Serializer& dest, const DirtyBits& attributeBits, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("DecalSet", "void WriteDeltaUpdate(Serializer&, const DirtyBits&in, uint8)", asMETHODPR(DecalSet, WriteDeltaUpdate, (Serializer&, const DirtyBits&, unsigned char), void), asCALL_THISCALL);
    // void Serializable::WriteInitialDeltaUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("DecalSet", "void WriteInitialDeltaUpdate(Serializer&, uint8)", asMETHODPR(DecalSet, WriteInitialDeltaUpdate, (Serializer&, unsigned char), void), asCALL_THISCALL);
    // void Serializable::WriteLatestDataUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("DecalSet", "void WriteLatestDataUpdate(Serializer&, uint8)", asMETHODPR(DecalSet, WriteLatestDataUpdate, (Serializer&, unsigned char), void), asCALL_THISCALL);
#ifdef REGISTER_MANUAL_PART_Drawable
    REGISTER_MANUAL_PART_Drawable(DecalSet, "DecalSet")
#endif
#ifdef REGISTER_MANUAL_PART_Component
    REGISTER_MANUAL_PART_Component(DecalSet, "DecalSet")
#endif
#ifdef REGISTER_MANUAL_PART_Animatable
    REGISTER_MANUAL_PART_Animatable(DecalSet, "DecalSet")
#endif
#ifdef REGISTER_MANUAL_PART_Serializable
    REGISTER_MANUAL_PART_Serializable(DecalSet, "DecalSet")
#endif
#ifdef REGISTER_MANUAL_PART_Object
    REGISTER_MANUAL_PART_Object(DecalSet, "DecalSet")
#endif
#ifdef REGISTER_MANUAL_PART_RefCounted
    REGISTER_MANUAL_PART_RefCounted(DecalSet, "DecalSet")
#endif
#ifdef REGISTER_MANUAL_PART_DecalSet
    REGISTER_MANUAL_PART_DecalSet(DecalSet, "DecalSet")
#endif
    RegisterSubclass<Drawable, DecalSet>(engine, "Drawable", "DecalSet");
    RegisterSubclass<Component, DecalSet>(engine, "Component", "DecalSet");
    RegisterSubclass<Animatable, DecalSet>(engine, "Animatable", "DecalSet");
    RegisterSubclass<Serializable, DecalSet>(engine, "Serializable", "DecalSet");
    RegisterSubclass<Object, DecalSet>(engine, "Object", "DecalSet");
    RegisterSubclass<RefCounted, DecalSet>(engine, "RefCounted", "DecalSet");

    // virtual unsigned Deserializer::GetChecksum() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("Deserializer", "uint GetChecksum()", asMETHODPR(Deserializer, GetChecksum, (), unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("Deserializer", "uint get_checksum()", asMETHODPR(Deserializer, GetChecksum, (), unsigned), asCALL_THISCALL);
    // virtual const String& Deserializer::GetName() const | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("Deserializer", "const String& GetName() const", asMETHODPR(Deserializer, GetName, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Deserializer", "const String& get_name() const", asMETHODPR(Deserializer, GetName, () const, const String&), asCALL_THISCALL);
    // unsigned Deserializer::GetPosition() const | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("Deserializer", "uint GetPosition() const", asMETHODPR(Deserializer, GetPosition, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("Deserializer", "uint get_position() const", asMETHODPR(Deserializer, GetPosition, () const, unsigned), asCALL_THISCALL);
    // unsigned Deserializer::GetSize() const | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("Deserializer", "uint GetSize() const", asMETHODPR(Deserializer, GetSize, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("Deserializer", "uint get_size() const", asMETHODPR(Deserializer, GetSize, () const, unsigned), asCALL_THISCALL);
    // virtual bool Deserializer::IsEof() const | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("Deserializer", "bool IsEof() const", asMETHODPR(Deserializer, IsEof, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Deserializer", "bool get_eof() const", asMETHODPR(Deserializer, IsEof, () const, bool), asCALL_THISCALL);
    // virtual unsigned Deserializer::Read(void* dest, unsigned size)=0 | File: ../IO/Deserializer.h
    // Error: type "void*" can not automatically bind
    // bool Deserializer::ReadBool() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("Deserializer", "bool ReadBool()", asMETHODPR(Deserializer, ReadBool, (), bool), asCALL_THISCALL);
    // BoundingBox Deserializer::ReadBoundingBox() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("Deserializer", "BoundingBox ReadBoundingBox()", asMETHODPR(Deserializer, ReadBoundingBox, (), BoundingBox), asCALL_THISCALL);
    // PODVector<unsigned char> Deserializer::ReadBuffer() | File: ../IO/Deserializer.h
    // Error: type "PODVector<unsigned char>" can not automatically bind
    // signed char Deserializer::ReadByte() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("Deserializer", "int8 ReadByte()", asMETHODPR(Deserializer, ReadByte, (), signed char), asCALL_THISCALL);
    // Color Deserializer::ReadColor() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("Deserializer", "Color ReadColor()", asMETHODPR(Deserializer, ReadColor, (), Color), asCALL_THISCALL);
    // double Deserializer::ReadDouble() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("Deserializer", "double ReadDouble()", asMETHODPR(Deserializer, ReadDouble, (), double), asCALL_THISCALL);
    // String Deserializer::ReadFileID() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("Deserializer", "String ReadFileID()", asMETHODPR(Deserializer, ReadFileID, (), String), asCALL_THISCALL);
    // float Deserializer::ReadFloat() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("Deserializer", "float ReadFloat()", asMETHODPR(Deserializer, ReadFloat, (), float), asCALL_THISCALL);
    // int Deserializer::ReadInt() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("Deserializer", "int ReadInt()", asMETHODPR(Deserializer, ReadInt, (), int), asCALL_THISCALL);
    // long long Deserializer::ReadInt64() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("Deserializer", "int64 ReadInt64()", asMETHODPR(Deserializer, ReadInt64, (), long long), asCALL_THISCALL);
    // IntRect Deserializer::ReadIntRect() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("Deserializer", "IntRect ReadIntRect()", asMETHODPR(Deserializer, ReadIntRect, (), IntRect), asCALL_THISCALL);
    // IntVector2 Deserializer::ReadIntVector2() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("Deserializer", "IntVector2 ReadIntVector2()", asMETHODPR(Deserializer, ReadIntVector2, (), IntVector2), asCALL_THISCALL);
    // IntVector3 Deserializer::ReadIntVector3() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("Deserializer", "IntVector3 ReadIntVector3()", asMETHODPR(Deserializer, ReadIntVector3, (), IntVector3), asCALL_THISCALL);
    // String Deserializer::ReadLine() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("Deserializer", "String ReadLine()", asMETHODPR(Deserializer, ReadLine, (), String), asCALL_THISCALL);
    // Matrix3 Deserializer::ReadMatrix3() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("Deserializer", "Matrix3 ReadMatrix3()", asMETHODPR(Deserializer, ReadMatrix3, (), Matrix3), asCALL_THISCALL);
    // Matrix3x4 Deserializer::ReadMatrix3x4() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("Deserializer", "Matrix3x4 ReadMatrix3x4()", asMETHODPR(Deserializer, ReadMatrix3x4, (), Matrix3x4), asCALL_THISCALL);
    // Matrix4 Deserializer::ReadMatrix4() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("Deserializer", "Matrix4 ReadMatrix4()", asMETHODPR(Deserializer, ReadMatrix4, (), Matrix4), asCALL_THISCALL);
    // unsigned Deserializer::ReadNetID() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("Deserializer", "uint ReadNetID()", asMETHODPR(Deserializer, ReadNetID, (), unsigned), asCALL_THISCALL);
    // Quaternion Deserializer::ReadPackedQuaternion() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("Deserializer", "Quaternion ReadPackedQuaternion()", asMETHODPR(Deserializer, ReadPackedQuaternion, (), Quaternion), asCALL_THISCALL);
    // Vector3 Deserializer::ReadPackedVector3(float maxAbsCoord) | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("Deserializer", "Vector3 ReadPackedVector3(float)", asMETHODPR(Deserializer, ReadPackedVector3, (float), Vector3), asCALL_THISCALL);
    // Quaternion Deserializer::ReadQuaternion() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("Deserializer", "Quaternion ReadQuaternion()", asMETHODPR(Deserializer, ReadQuaternion, (), Quaternion), asCALL_THISCALL);
    // Rect Deserializer::ReadRect() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("Deserializer", "Rect ReadRect()", asMETHODPR(Deserializer, ReadRect, (), Rect), asCALL_THISCALL);
    // ResourceRef Deserializer::ReadResourceRef() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("Deserializer", "ResourceRef ReadResourceRef()", asMETHODPR(Deserializer, ReadResourceRef, (), ResourceRef), asCALL_THISCALL);
    // ResourceRefList Deserializer::ReadResourceRefList() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("Deserializer", "ResourceRefList ReadResourceRefList()", asMETHODPR(Deserializer, ReadResourceRefList, (), ResourceRefList), asCALL_THISCALL);
    // short Deserializer::ReadShort() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("Deserializer", "int16 ReadShort()", asMETHODPR(Deserializer, ReadShort, (), short), asCALL_THISCALL);
    // String Deserializer::ReadString() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("Deserializer", "String ReadString()", asMETHODPR(Deserializer, ReadString, (), String), asCALL_THISCALL);
    // StringHash Deserializer::ReadStringHash() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("Deserializer", "StringHash ReadStringHash()", asMETHODPR(Deserializer, ReadStringHash, (), StringHash), asCALL_THISCALL);
    // StringVector Deserializer::ReadStringVector() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("Deserializer", "Array<String>@ ReadStringVector()", asFUNCTION(Deserializer_ReadStringVector_void), asCALL_CDECL_OBJFIRST);
    // unsigned char Deserializer::ReadUByte() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("Deserializer", "uint8 ReadUByte()", asMETHODPR(Deserializer, ReadUByte, (), unsigned char), asCALL_THISCALL);
    // unsigned Deserializer::ReadUInt() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("Deserializer", "uint ReadUInt()", asMETHODPR(Deserializer, ReadUInt, (), unsigned), asCALL_THISCALL);
    // unsigned long long Deserializer::ReadUInt64() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("Deserializer", "uint64 ReadUInt64()", asMETHODPR(Deserializer, ReadUInt64, (), unsigned long long), asCALL_THISCALL);
    // unsigned short Deserializer::ReadUShort() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("Deserializer", "uint16 ReadUShort()", asMETHODPR(Deserializer, ReadUShort, (), unsigned short), asCALL_THISCALL);
    // Variant Deserializer::ReadVariant() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("Deserializer", "Variant ReadVariant()", asMETHODPR(Deserializer, ReadVariant, (), Variant), asCALL_THISCALL);
    // Variant Deserializer::ReadVariant(VariantType type) | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("Deserializer", "Variant ReadVariant(VariantType)", asMETHODPR(Deserializer, ReadVariant, (VariantType), Variant), asCALL_THISCALL);
    // VariantMap Deserializer::ReadVariantMap() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("Deserializer", "VariantMap ReadVariantMap()", asMETHODPR(Deserializer, ReadVariantMap, (), VariantMap), asCALL_THISCALL);
    // VariantVector Deserializer::ReadVariantVector() | File: ../IO/Deserializer.h
    // Error: type "VariantVector" can not automatically bind
    // Vector2 Deserializer::ReadVector2() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("Deserializer", "Vector2 ReadVector2()", asMETHODPR(Deserializer, ReadVector2, (), Vector2), asCALL_THISCALL);
    // Vector3 Deserializer::ReadVector3() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("Deserializer", "Vector3 ReadVector3()", asMETHODPR(Deserializer, ReadVector3, (), Vector3), asCALL_THISCALL);
    // Vector4 Deserializer::ReadVector4() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("Deserializer", "Vector4 ReadVector4()", asMETHODPR(Deserializer, ReadVector4, (), Vector4), asCALL_THISCALL);
    // unsigned Deserializer::ReadVLE() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("Deserializer", "uint ReadVLE()", asMETHODPR(Deserializer, ReadVLE, (), unsigned), asCALL_THISCALL);
    // virtual unsigned Deserializer::Seek(unsigned position)=0 | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("Deserializer", "uint Seek(uint)", asMETHODPR(Deserializer, Seek, (unsigned), unsigned), asCALL_THISCALL);
    // unsigned Deserializer::SeekRelative(int delta) | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("Deserializer", "uint SeekRelative(int)", asMETHODPR(Deserializer, SeekRelative, (int), unsigned), asCALL_THISCALL);
    // unsigned Deserializer::Tell() const | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("Deserializer", "uint Tell() const", asMETHODPR(Deserializer, Tell, () const, unsigned), asCALL_THISCALL);
    // Deserializer& Deserializer::operator=(const Deserializer&) | Possible implicitly-declared
    RegisterImplicitlyDeclaredAssignOperatorIfPossible<Deserializer>(engine, "Deserializer");
    engine->RegisterObjectBehaviour("Deserializer", asBEHAVE_ADDREF, "void f()", asFUNCTION(FakeAddRef), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("Deserializer", asBEHAVE_RELEASE, "void f()", asFUNCTION(FakeReleaseRef), asCALL_CDECL_OBJLAST);
#ifdef REGISTER_MANUAL_PART_Deserializer
    REGISTER_MANUAL_PART_Deserializer(Deserializer, "Deserializer")
#endif

    // void Drawable::AddLight(Light* light) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Drawable", "void AddLight(Light@+)", asMETHODPR(Drawable, AddLight, (Light*), void), asCALL_THISCALL);
    // void RefCounted::AddRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("Drawable", asBEHAVE_ADDREF, "void f()", asMETHODPR(Drawable, AddRef, (), void), asCALL_THISCALL);
    // void Component::AddReplicationState(ComponentReplicationState* state) | File: ../Scene/Component.h
    // Error: type "ComponentReplicationState*" can not automatically bind
    // void Drawable::AddVertexLight(Light* light) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Drawable", "void AddVertexLight(Light@+)", asMETHODPR(Drawable, AddVertexLight, (Light*), void), asCALL_THISCALL);
    // void Serializable::AllocateNetworkState() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Drawable", "void AllocateNetworkState()", asMETHODPR(Drawable, AllocateNetworkState, (), void), asCALL_THISCALL);
    // virtual void Serializable::ApplyAttributes() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Drawable", "void ApplyAttributes()", asMETHODPR(Drawable, ApplyAttributes, (), void), asCALL_THISCALL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // void Component::CleanupConnection(Connection* connection) | File: ../Scene/Component.h
    // Not registered because have @manualbind mark
    // void Drawable::DrawDebugGeometry(DebugRenderer* debug, bool depthTest) override | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Drawable", "void DrawDebugGeometry(DebugRenderer@+, bool)", asMETHODPR(Drawable, DrawDebugGeometry, (DebugRenderer*, bool), void), asCALL_THISCALL);
    // virtual bool Drawable::DrawOcclusion(OcclusionBuffer* buffer) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Drawable", "bool DrawOcclusion(OcclusionBuffer@+)", asMETHODPR(Drawable, DrawOcclusion, (OcclusionBuffer*), bool), asCALL_THISCALL);
    // bool Animatable::GetAnimationEnabled() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Drawable", "bool GetAnimationEnabled() const", asMETHODPR(Drawable, GetAnimationEnabled, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Drawable", "bool get_animationEnabled() const", asMETHODPR(Drawable, GetAnimationEnabled, () const, bool), asCALL_THISCALL);
    // Variant Serializable::GetAttribute(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Drawable", "Variant GetAttribute(uint) const", asMETHODPR(Drawable, GetAttribute, (unsigned) const, Variant), asCALL_THISCALL);
    engine->RegisterObjectMethod("Drawable", "Variant get_attributes(uint) const", asMETHODPR(Drawable, GetAttribute, (unsigned) const, Variant), asCALL_THISCALL);
    // Variant Serializable::GetAttribute(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Drawable", "Variant GetAttribute(const String&in) const", asMETHODPR(Drawable, GetAttribute, (const String&) const, Variant), asCALL_THISCALL);
    // ValueAnimation* Animatable::GetAttributeAnimation(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Drawable", "ValueAnimation@+ GetAttributeAnimation(const String&in) const", asMETHODPR(Drawable, GetAttributeAnimation, (const String&) const, ValueAnimation*), asCALL_THISCALL);
    // float Animatable::GetAttributeAnimationSpeed(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Drawable", "float GetAttributeAnimationSpeed(const String&in) const", asMETHODPR(Drawable, GetAttributeAnimationSpeed, (const String&) const, float), asCALL_THISCALL);
    // float Animatable::GetAttributeAnimationTime(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Drawable", "float GetAttributeAnimationTime(const String&in) const", asMETHODPR(Drawable, GetAttributeAnimationTime, (const String&) const, float), asCALL_THISCALL);
    // WrapMode Animatable::GetAttributeAnimationWrapMode(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Drawable", "WrapMode GetAttributeAnimationWrapMode(const String&in) const", asMETHODPR(Drawable, GetAttributeAnimationWrapMode, (const String&) const, WrapMode), asCALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Drawable", "Variant GetAttributeDefault(uint) const", asMETHODPR(Drawable, GetAttributeDefault, (unsigned) const, Variant), asCALL_THISCALL);
    engine->RegisterObjectMethod("Drawable", "Variant get_attributeDefaults(uint) const", asMETHODPR(Drawable, GetAttributeDefault, (unsigned) const, Variant), asCALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Drawable", "Variant GetAttributeDefault(const String&in) const", asMETHODPR(Drawable, GetAttributeDefault, (const String&) const, Variant), asCALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // const Vector<SourceBatch>& Drawable::GetBatches() const | File: ../Graphics/Drawable.h
    // Error: type "const Vector<SourceBatch>&" can not automatically bind
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Drawable", "bool GetBlockEvents() const", asMETHODPR(Drawable, GetBlockEvents, () const, bool), asCALL_THISCALL);
    // const BoundingBox& Drawable::GetBoundingBox() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Drawable", "const BoundingBox& GetBoundingBox() const", asMETHODPR(Drawable, GetBoundingBox, () const, const BoundingBox&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Drawable", "const BoundingBox& get_boundingBox() const", asMETHODPR(Drawable, GetBoundingBox, () const, const BoundingBox&), asCALL_THISCALL);
    // bool Drawable::GetCastShadows() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Drawable", "bool GetCastShadows() const", asMETHODPR(Drawable, GetCastShadows, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Drawable", "bool get_castShadows() const", asMETHODPR(Drawable, GetCastShadows, () const, bool), asCALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Drawable", "const String& GetCategory() const", asMETHODPR(Drawable, GetCategory, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Drawable", "const String& get_category() const", asMETHODPR(Drawable, GetCategory, () const, const String&), asCALL_THISCALL);
    // Component* Component::GetComponent(StringHash type) const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Drawable", "Component@+ GetComponent(StringHash) const", asMETHODPR(Drawable, GetComponent, (StringHash) const, Component*), asCALL_THISCALL);
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
    engine->RegisterObjectMethod("Drawable", "float GetDistance() const", asMETHODPR(Drawable, GetDistance, () const, float), asCALL_THISCALL);
    // unsigned char Drawable::GetDrawableFlags() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Drawable", "uint8 GetDrawableFlags() const", asMETHODPR(Drawable, GetDrawableFlags, () const, unsigned char), asCALL_THISCALL);
    // float Drawable::GetDrawDistance() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Drawable", "float GetDrawDistance() const", asMETHODPR(Drawable, GetDrawDistance, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("Drawable", "float get_drawDistance() const", asMETHODPR(Drawable, GetDrawDistance, () const, float), asCALL_THISCALL);
    // VariantMap& Object::GetEventDataMap() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Drawable", "VariantMap& GetEventDataMap() const", asMETHODPR(Drawable, GetEventDataMap, () const, VariantMap&), asCALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Drawable", "Object@+ GetEventSender() const", asMETHODPR(Drawable, GetEventSender, () const, Object*), asCALL_THISCALL);
    // Light* Drawable::GetFirstLight() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Drawable", "Light@+ GetFirstLight() const", asMETHODPR(Drawable, GetFirstLight, () const, Light*), asCALL_THISCALL);
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Drawable", "const Variant& GetGlobalVar(StringHash) const", asMETHODPR(Drawable, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Drawable", "const Variant& get_globalVar(StringHash) const", asMETHODPR(Drawable, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Drawable", "const VariantMap& GetGlobalVars() const", asMETHODPR(Drawable, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Drawable", "const VariantMap& get_globalVars() const", asMETHODPR(Drawable, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    // unsigned Component::GetID() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Drawable", "uint GetID() const", asMETHODPR(Drawable, GetID, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("Drawable", "uint get_id() const", asMETHODPR(Drawable, GetID, () const, unsigned), asCALL_THISCALL);
    // bool Serializable::GetInterceptNetworkUpdate(const String& attributeName) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Drawable", "bool GetInterceptNetworkUpdate(const String&in) const", asMETHODPR(Drawable, GetInterceptNetworkUpdate, (const String&) const, bool), asCALL_THISCALL);
    // unsigned Drawable::GetLightMask() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Drawable", "uint GetLightMask() const", asMETHODPR(Drawable, GetLightMask, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("Drawable", "uint get_lightMask() const", asMETHODPR(Drawable, GetLightMask, () const, unsigned), asCALL_THISCALL);
    // const PODVector<Light*>& Drawable::GetLights() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Drawable", "Array<Light@>@ GetLights() const", asFUNCTION(Drawable_GetLights_void), asCALL_CDECL_OBJFIRST);
    // float Drawable::GetLodBias() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Drawable", "float GetLodBias() const", asMETHODPR(Drawable, GetLodBias, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("Drawable", "float get_lodBias() const", asMETHODPR(Drawable, GetLodBias, () const, float), asCALL_THISCALL);
    // float Drawable::GetLodDistance() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Drawable", "float GetLodDistance() const", asMETHODPR(Drawable, GetLodDistance, () const, float), asCALL_THISCALL);
    // virtual Geometry* Drawable::GetLodGeometry(unsigned batchIndex, unsigned level) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Drawable", "Geometry@+ GetLodGeometry(uint, uint)", asMETHODPR(Drawable, GetLodGeometry, (unsigned, unsigned), Geometry*), asCALL_THISCALL);
    // unsigned Drawable::GetMaxLights() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Drawable", "uint GetMaxLights() const", asMETHODPR(Drawable, GetMaxLights, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("Drawable", "uint get_maxLights() const", asMETHODPR(Drawable, GetMaxLights, () const, unsigned), asCALL_THISCALL);
    // float Drawable::GetMaxZ() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Drawable", "float GetMaxZ() const", asMETHODPR(Drawable, GetMaxZ, () const, float), asCALL_THISCALL);
    // float Drawable::GetMinZ() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Drawable", "float GetMinZ() const", asMETHODPR(Drawable, GetMinZ, () const, float), asCALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetNetworkAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // NetworkState* Serializable::GetNetworkState() const | File: ../Scene/Serializable.h
    // Error: type "NetworkState*" can not automatically bind
    // Node* Component::GetNode() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Drawable", "Node@+ GetNode() const", asMETHODPR(Drawable, GetNode, () const, Node*), asCALL_THISCALL);
    engine->RegisterObjectMethod("Drawable", "Node@+ get_node() const", asMETHODPR(Drawable, GetNode, () const, Node*), asCALL_THISCALL);
    // unsigned Serializable::GetNumAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Drawable", "uint GetNumAttributes() const", asMETHODPR(Drawable, GetNumAttributes, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("Drawable", "uint get_numAttributes() const", asMETHODPR(Drawable, GetNumAttributes, () const, unsigned), asCALL_THISCALL);
    // unsigned Serializable::GetNumNetworkAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Drawable", "uint GetNumNetworkAttributes() const", asMETHODPR(Drawable, GetNumNetworkAttributes, () const, unsigned), asCALL_THISCALL);
    // virtual unsigned Drawable::GetNumOccluderTriangles() | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Drawable", "uint GetNumOccluderTriangles()", asMETHODPR(Drawable, GetNumOccluderTriangles, (), unsigned), asCALL_THISCALL);
    // ObjectAnimation* Animatable::GetObjectAnimation() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Drawable", "ObjectAnimation@+ GetObjectAnimation() const", asMETHODPR(Drawable, GetObjectAnimation, () const, ObjectAnimation*), asCALL_THISCALL);
    engine->RegisterObjectMethod("Drawable", "ObjectAnimation@+ get_objectAnimation() const", asMETHODPR(Drawable, GetObjectAnimation, () const, ObjectAnimation*), asCALL_THISCALL);
    // ResourceRef Animatable::GetObjectAnimationAttr() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Drawable", "ResourceRef GetObjectAnimationAttr() const", asMETHODPR(Drawable, GetObjectAnimationAttr, () const, ResourceRef), asCALL_THISCALL);
    // Octant* Drawable::GetOctant() const | File: ../Graphics/Drawable.h
    // Error: type "Octant" can not automatically bind bacause have @nobind mark
    // Scene* Component::GetScene() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Drawable", "Scene@+ GetScene() const", asMETHODPR(Drawable, GetScene, () const, Scene*), asCALL_THISCALL);
    // float Drawable::GetShadowDistance() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Drawable", "float GetShadowDistance() const", asMETHODPR(Drawable, GetShadowDistance, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("Drawable", "float get_shadowDistance() const", asMETHODPR(Drawable, GetShadowDistance, () const, float), asCALL_THISCALL);
    // unsigned Drawable::GetShadowMask() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Drawable", "uint GetShadowMask() const", asMETHODPR(Drawable, GetShadowMask, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("Drawable", "uint get_shadowMask() const", asMETHODPR(Drawable, GetShadowMask, () const, unsigned), asCALL_THISCALL);
    // float Drawable::GetSortValue() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Drawable", "float GetSortValue() const", asMETHODPR(Drawable, GetSortValue, () const, float), asCALL_THISCALL);
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Drawable", "Object@+ GetSubsystem(StringHash) const", asMETHODPR(Drawable, GetSubsystem, (StringHash) const, Object*), asCALL_THISCALL);
    // template<class T> T* Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("Drawable", "StringHash GetType() const", asMETHODPR(Drawable, GetType, () const, StringHash), asCALL_THISCALL);
    engine->RegisterObjectMethod("Drawable", "StringHash get_type() const", asMETHODPR(Drawable, GetType, () const, StringHash), asCALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("Drawable", "const String& GetTypeName() const", asMETHODPR(Drawable, GetTypeName, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Drawable", "const String& get_typeName() const", asMETHODPR(Drawable, GetTypeName, () const, const String&), asCALL_THISCALL);
    // virtual UpdateGeometryType Drawable::GetUpdateGeometryType() | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Drawable", "UpdateGeometryType GetUpdateGeometryType()", asMETHODPR(Drawable, GetUpdateGeometryType, (), UpdateGeometryType), asCALL_THISCALL);
    // const PODVector<Light*>& Drawable::GetVertexLights() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Drawable", "Array<Light@>@ GetVertexLights() const", asFUNCTION(Drawable_GetVertexLights_void), asCALL_CDECL_OBJFIRST);
    // unsigned Drawable::GetViewMask() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Drawable", "uint GetViewMask() const", asMETHODPR(Drawable, GetViewMask, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("Drawable", "uint get_viewMask() const", asMETHODPR(Drawable, GetViewMask, () const, unsigned), asCALL_THISCALL);
    // const BoundingBox& Drawable::GetWorldBoundingBox() | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Drawable", "const BoundingBox& GetWorldBoundingBox()", asMETHODPR(Drawable, GetWorldBoundingBox, (), const BoundingBox&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Drawable", "const BoundingBox& get_worldBoundingBox()", asMETHODPR(Drawable, GetWorldBoundingBox, (), const BoundingBox&), asCALL_THISCALL);
    // Zone* Drawable::GetZone() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Drawable", "Zone@+ GetZone() const", asMETHODPR(Drawable, GetZone, () const, Zone*), asCALL_THISCALL);
    engine->RegisterObjectMethod("Drawable", "Zone@+ get_zone() const", asMETHODPR(Drawable, GetZone, () const, Zone*), asCALL_THISCALL);
    // unsigned Drawable::GetZoneMask() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Drawable", "uint GetZoneMask() const", asMETHODPR(Drawable, GetZoneMask, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("Drawable", "uint get_zoneMask() const", asMETHODPR(Drawable, GetZoneMask, () const, unsigned), asCALL_THISCALL);
    // bool Drawable::HasBasePass(unsigned batchIndex) const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Drawable", "bool HasBasePass(uint) const", asMETHODPR(Drawable, HasBasePass, (unsigned) const, bool), asCALL_THISCALL);
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Drawable", "bool HasEventHandlers() const", asMETHODPR(Drawable, HasEventHandlers, () const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Drawable", "bool HasSubscribedToEvent(StringHash) const", asMETHODPR(Drawable, HasSubscribedToEvent, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Drawable", "bool HasSubscribedToEvent(Object@+, StringHash) const", asMETHODPR(Drawable, HasSubscribedToEvent, (Object*, StringHash) const, bool), asCALL_THISCALL);
    // bool Component::IsEnabled() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Drawable", "bool IsEnabled() const", asMETHODPR(Drawable, IsEnabled, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Drawable", "bool get_enabled() const", asMETHODPR(Drawable, IsEnabled, () const, bool), asCALL_THISCALL);
    // bool Component::IsEnabledEffective() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Drawable", "bool IsEnabledEffective() const", asMETHODPR(Drawable, IsEnabledEffective, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Drawable", "bool get_enabledEffective() const", asMETHODPR(Drawable, IsEnabledEffective, () const, bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Drawable", "bool IsInstanceOf(StringHash) const", asMETHODPR(Drawable, IsInstanceOf, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // bool Drawable::IsInView() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Drawable", "bool IsInView() const", asMETHODPR(Drawable, IsInView, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Drawable", "bool get_inView() const", asMETHODPR(Drawable, IsInView, () const, bool), asCALL_THISCALL);
    // bool Drawable::IsInView(Camera* camera) const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Drawable", "bool IsInView(Camera@+) const", asMETHODPR(Drawable, IsInView, (Camera*) const, bool), asCALL_THISCALL);
    // bool Drawable::IsInView(const FrameInfo& frame, bool anyCamera=false) const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Drawable", "bool IsInView(const FrameInfo&in, bool = false) const", asMETHODPR(Drawable, IsInView, (const FrameInfo&, bool) const, bool), asCALL_THISCALL);
    // bool Drawable::IsOccludee() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Drawable", "bool IsOccludee() const", asMETHODPR(Drawable, IsOccludee, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Drawable", "bool get_occludee() const", asMETHODPR(Drawable, IsOccludee, () const, bool), asCALL_THISCALL);
    // bool Drawable::IsOccluder() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Drawable", "bool IsOccluder() const", asMETHODPR(Drawable, IsOccluder, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Drawable", "bool get_occluder() const", asMETHODPR(Drawable, IsOccluder, () const, bool), asCALL_THISCALL);
    // bool Component::IsReplicated() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Drawable", "bool IsReplicated() const", asMETHODPR(Drawable, IsReplicated, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Drawable", "bool get_replicated() const", asMETHODPR(Drawable, IsReplicated, () const, bool), asCALL_THISCALL);
    // bool Serializable::IsTemporary() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Drawable", "bool IsTemporary() const", asMETHODPR(Drawable, IsTemporary, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Drawable", "bool get_temporary() const", asMETHODPR(Drawable, IsTemporary, () const, bool), asCALL_THISCALL);
    // bool Drawable::IsZoneDirty() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Drawable", "bool IsZoneDirty() const", asMETHODPR(Drawable, IsZoneDirty, () const, bool), asCALL_THISCALL);
    // void Drawable::LimitLights() | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Drawable", "void LimitLights()", asMETHODPR(Drawable, LimitLights, (), void), asCALL_THISCALL);
    // void Drawable::LimitVertexLights(bool removeConvertedLights) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Drawable", "void LimitVertexLights(bool)", asMETHODPR(Drawable, LimitVertexLights, (bool), void), asCALL_THISCALL);
    // virtual bool Serializable::Load(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Drawable", "bool Load(Deserializer&)", asMETHODPR(Drawable, Load, (Deserializer&), bool), asCALL_THISCALL);
    // bool Animatable::LoadJSON(const JSONValue& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Drawable", "bool LoadJSON(const JSONValue&in)", asMETHODPR(Drawable, LoadJSON, (const JSONValue&), bool), asCALL_THISCALL);
    // bool Animatable::LoadXML(const XMLElement& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Drawable", "bool LoadXML(const XMLElement&in)", asMETHODPR(Drawable, LoadXML, (const XMLElement&), bool), asCALL_THISCALL);
    // void Drawable::MarkForUpdate() | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Drawable", "void MarkForUpdate()", asMETHODPR(Drawable, MarkForUpdate, (), void), asCALL_THISCALL);
    // void Drawable::MarkInView(const FrameInfo& frame) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Drawable", "void MarkInView(const FrameInfo&in)", asMETHODPR(Drawable, MarkInView, (const FrameInfo&), void), asCALL_THISCALL);
    // void Drawable::MarkInView(unsigned frameNumber) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Drawable", "void MarkInView(uint)", asMETHODPR(Drawable, MarkInView, (unsigned), void), asCALL_THISCALL);
    // void Component::MarkNetworkUpdate() override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Drawable", "void MarkNetworkUpdate()", asMETHODPR(Drawable, MarkNetworkUpdate, (), void), asCALL_THISCALL);
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Drawable", "void OnEvent(Object@+, StringHash, VariantMap&)", asMETHODPR(Drawable, OnEvent, (Object*, StringHash, VariantMap&), void), asCALL_THISCALL);
    // virtual void Serializable::OnGetAttribute(const AttributeInfo& attr, Variant& dest) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Drawable", "void OnGetAttribute(const AttributeInfo&in, Variant&) const", asMETHODPR(Drawable, OnGetAttribute, (const AttributeInfo&, Variant&) const, void), asCALL_THISCALL);
    // virtual void Serializable::OnSetAttribute(const AttributeInfo& attr, const Variant& src) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Drawable", "void OnSetAttribute(const AttributeInfo&in, const Variant&in)", asMETHODPR(Drawable, OnSetAttribute, (const AttributeInfo&, const Variant&), void), asCALL_THISCALL);
    // void Drawable::OnSetEnabled() override | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Drawable", "void OnSetEnabled()", asMETHODPR(Drawable, OnSetEnabled, (), void), asCALL_THISCALL);
    // void Component::PrepareNetworkUpdate() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Drawable", "void PrepareNetworkUpdate()", asMETHODPR(Drawable, PrepareNetworkUpdate, (), void), asCALL_THISCALL);
    // virtual void Drawable::ProcessRayQuery(const RayOctreeQuery& query, PODVector<RayQueryResult>& results) | File: ../Graphics/Drawable.h
    // Error: type "RayOctreeQuery" can not automatically bind bacause have @nobind mark
    // bool Serializable::ReadDeltaUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Drawable", "bool ReadDeltaUpdate(Deserializer&)", asMETHODPR(Drawable, ReadDeltaUpdate, (Deserializer&), bool), asCALL_THISCALL);
    // bool Serializable::ReadLatestDataUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Drawable", "bool ReadLatestDataUpdate(Deserializer&)", asMETHODPR(Drawable, ReadLatestDataUpdate, (Deserializer&), bool), asCALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("Drawable", "int Refs() const", asMETHODPR(Drawable, Refs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("Drawable", "int get_refs() const", asMETHODPR(Drawable, Refs, () const, int), asCALL_THISCALL);
    // static void Drawable::RegisterObject(Context* context) | File: ../Graphics/Drawable.h
    // Not registered because have @nobind mark
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("Drawable", asBEHAVE_RELEASE, "void f()", asMETHODPR(Drawable, ReleaseRef, (), void), asCALL_THISCALL);
    // void Component::Remove() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Drawable", "void Remove()", asMETHODPR(Drawable, Remove, (), void), asCALL_THISCALL);
    // void Animatable::RemoveAttributeAnimation(const String& name) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Drawable", "void RemoveAttributeAnimation(const String&in)", asMETHODPR(Drawable, RemoveAttributeAnimation, (const String&), void), asCALL_THISCALL);
    // void Serializable::RemoveInstanceDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Drawable", "void RemoveInstanceDefault()", asMETHODPR(Drawable, RemoveInstanceDefault, (), void), asCALL_THISCALL);
    // void Animatable::RemoveObjectAnimation() | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Drawable", "void RemoveObjectAnimation()", asMETHODPR(Drawable, RemoveObjectAnimation, (), void), asCALL_THISCALL);
    // void Serializable::ResetToDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Drawable", "void ResetToDefault()", asMETHODPR(Drawable, ResetToDefault, (), void), asCALL_THISCALL);
    // bool Component::Save(Serializer& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Drawable", "bool Save(Serializer&) const", asMETHODPR(Drawable, Save, (Serializer&) const, bool), asCALL_THISCALL);
    // virtual bool Serializable::SaveDefaultAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Drawable", "bool SaveDefaultAttributes() const", asMETHODPR(Drawable, SaveDefaultAttributes, () const, bool), asCALL_THISCALL);
    // bool Component::SaveJSON(JSONValue& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Drawable", "bool SaveJSON(JSONValue&) const", asMETHODPR(Drawable, SaveJSON, (JSONValue&) const, bool), asCALL_THISCALL);
    // bool Component::SaveXML(XMLElement& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Drawable", "bool SaveXML(XMLElement&) const", asMETHODPR(Drawable, SaveXML, (XMLElement&) const, bool), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Drawable", "void SendEvent(StringHash)", asMETHODPR(Drawable, SendEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Drawable", "void SendEvent(StringHash, VariantMap&)", asMETHODPR(Drawable, SendEvent, (StringHash, VariantMap&), void), asCALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void Animatable::SetAnimationEnabled(bool enable) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Drawable", "void SetAnimationEnabled(bool)", asMETHODPR(Drawable, SetAnimationEnabled, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Drawable", "void set_animationEnabled(bool)", asMETHODPR(Drawable, SetAnimationEnabled, (bool), void), asCALL_THISCALL);
    // void Animatable::SetAnimationTime(float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Drawable", "void SetAnimationTime(float)", asMETHODPR(Drawable, SetAnimationTime, (float), void), asCALL_THISCALL);
    // bool Serializable::SetAttribute(unsigned index, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Drawable", "bool SetAttribute(uint, const Variant&in)", asMETHODPR(Drawable, SetAttribute, (unsigned, const Variant&), bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Drawable", "bool set_attributes(uint, const Variant&in)", asMETHODPR(Drawable, SetAttribute, (unsigned, const Variant&), bool), asCALL_THISCALL);
    // bool Serializable::SetAttribute(const String& name, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Drawable", "bool SetAttribute(const String&in, const Variant&in)", asMETHODPR(Drawable, SetAttribute, (const String&, const Variant&), bool), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimation(const String& name, ValueAnimation* attributeAnimation, WrapMode wrapMode=WM_LOOP, float speed=1.0f) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Drawable", "void SetAttributeAnimation(const String&in, ValueAnimation@+, WrapMode = WM_LOOP, float = 1.0f)", asMETHODPR(Drawable, SetAttributeAnimation, (const String&, ValueAnimation*, WrapMode, float), void), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimationSpeed(const String& name, float speed) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Drawable", "void SetAttributeAnimationSpeed(const String&in, float)", asMETHODPR(Drawable, SetAttributeAnimationSpeed, (const String&, float), void), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimationTime(const String& name, float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Drawable", "void SetAttributeAnimationTime(const String&in, float)", asMETHODPR(Drawable, SetAttributeAnimationTime, (const String&, float), void), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimationWrapMode(const String& name, WrapMode wrapMode) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Drawable", "void SetAttributeAnimationWrapMode(const String&in, WrapMode)", asMETHODPR(Drawable, SetAttributeAnimationWrapMode, (const String&, WrapMode), void), asCALL_THISCALL);
    // void Drawable::SetBasePass(unsigned batchIndex) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Drawable", "void SetBasePass(uint)", asMETHODPR(Drawable, SetBasePass, (unsigned), void), asCALL_THISCALL);
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Drawable", "void SetBlockEvents(bool)", asMETHODPR(Drawable, SetBlockEvents, (bool), void), asCALL_THISCALL);
    // void Drawable::SetCastShadows(bool enable) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Drawable", "void SetCastShadows(bool)", asMETHODPR(Drawable, SetCastShadows, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Drawable", "void set_castShadows(bool)", asMETHODPR(Drawable, SetCastShadows, (bool), void), asCALL_THISCALL);
    // void Drawable::SetDrawDistance(float distance) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Drawable", "void SetDrawDistance(float)", asMETHODPR(Drawable, SetDrawDistance, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Drawable", "void set_drawDistance(float)", asMETHODPR(Drawable, SetDrawDistance, (float), void), asCALL_THISCALL);
    // void Component::SetEnabled(bool enable) | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Drawable", "void SetEnabled(bool)", asMETHODPR(Drawable, SetEnabled, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Drawable", "void set_enabled(bool)", asMETHODPR(Drawable, SetEnabled, (bool), void), asCALL_THISCALL);
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Drawable", "void SetGlobalVar(StringHash, const Variant&in)", asMETHODPR(Drawable, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Drawable", "void set_globalVar(StringHash, const Variant&in)", asMETHODPR(Drawable, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    // void Serializable::SetInstanceDefault(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Drawable", "void SetInstanceDefault(bool)", asMETHODPR(Drawable, SetInstanceDefault, (bool), void), asCALL_THISCALL);
    // void Serializable::SetInterceptNetworkUpdate(const String& attributeName, bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Drawable", "void SetInterceptNetworkUpdate(const String&in, bool)", asMETHODPR(Drawable, SetInterceptNetworkUpdate, (const String&, bool), void), asCALL_THISCALL);
    // void Drawable::SetLightMask(unsigned mask) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Drawable", "void SetLightMask(uint)", asMETHODPR(Drawable, SetLightMask, (unsigned), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Drawable", "void set_lightMask(uint)", asMETHODPR(Drawable, SetLightMask, (unsigned), void), asCALL_THISCALL);
    // void Drawable::SetLodBias(float bias) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Drawable", "void SetLodBias(float)", asMETHODPR(Drawable, SetLodBias, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Drawable", "void set_lodBias(float)", asMETHODPR(Drawable, SetLodBias, (float), void), asCALL_THISCALL);
    // void Drawable::SetMaxLights(unsigned num) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Drawable", "void SetMaxLights(uint)", asMETHODPR(Drawable, SetMaxLights, (unsigned), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Drawable", "void set_maxLights(uint)", asMETHODPR(Drawable, SetMaxLights, (unsigned), void), asCALL_THISCALL);
    // void Drawable::SetMinMaxZ(float minZ, float maxZ) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Drawable", "void SetMinMaxZ(float, float)", asMETHODPR(Drawable, SetMinMaxZ, (float, float), void), asCALL_THISCALL);
    // void Animatable::SetObjectAnimation(ObjectAnimation* objectAnimation) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Drawable", "void SetObjectAnimation(ObjectAnimation@+)", asMETHODPR(Drawable, SetObjectAnimation, (ObjectAnimation*), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Drawable", "void set_objectAnimation(ObjectAnimation@+)", asMETHODPR(Drawable, SetObjectAnimation, (ObjectAnimation*), void), asCALL_THISCALL);
    // void Animatable::SetObjectAnimationAttr(const ResourceRef& value) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Drawable", "void SetObjectAnimationAttr(const ResourceRef&in)", asMETHODPR(Drawable, SetObjectAnimationAttr, (const ResourceRef&), void), asCALL_THISCALL);
    // void Drawable::SetOccludee(bool enable) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Drawable", "void SetOccludee(bool)", asMETHODPR(Drawable, SetOccludee, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Drawable", "void set_occludee(bool)", asMETHODPR(Drawable, SetOccludee, (bool), void), asCALL_THISCALL);
    // void Drawable::SetOccluder(bool enable) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Drawable", "void SetOccluder(bool)", asMETHODPR(Drawable, SetOccluder, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Drawable", "void set_occluder(bool)", asMETHODPR(Drawable, SetOccluder, (bool), void), asCALL_THISCALL);
    // void Drawable::SetShadowDistance(float distance) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Drawable", "void SetShadowDistance(float)", asMETHODPR(Drawable, SetShadowDistance, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Drawable", "void set_shadowDistance(float)", asMETHODPR(Drawable, SetShadowDistance, (float), void), asCALL_THISCALL);
    // void Drawable::SetShadowMask(unsigned mask) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Drawable", "void SetShadowMask(uint)", asMETHODPR(Drawable, SetShadowMask, (unsigned), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Drawable", "void set_shadowMask(uint)", asMETHODPR(Drawable, SetShadowMask, (unsigned), void), asCALL_THISCALL);
    // void Drawable::SetSortValue(float value) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Drawable", "void SetSortValue(float)", asMETHODPR(Drawable, SetSortValue, (float), void), asCALL_THISCALL);
    // void Serializable::SetTemporary(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Drawable", "void SetTemporary(bool)", asMETHODPR(Drawable, SetTemporary, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Drawable", "void set_temporary(bool)", asMETHODPR(Drawable, SetTemporary, (bool), void), asCALL_THISCALL);
    // void Drawable::SetViewMask(unsigned mask) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Drawable", "void SetViewMask(uint)", asMETHODPR(Drawable, SetViewMask, (unsigned), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Drawable", "void set_viewMask(uint)", asMETHODPR(Drawable, SetViewMask, (unsigned), void), asCALL_THISCALL);
    // void Drawable::SetZone(Zone* zone, bool temporary=false) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Drawable", "void SetZone(Zone@+, bool = false)", asMETHODPR(Drawable, SetZone, (Zone*, bool), void), asCALL_THISCALL);
    // void Drawable::SetZoneMask(unsigned mask) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Drawable", "void SetZoneMask(uint)", asMETHODPR(Drawable, SetZoneMask, (unsigned), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Drawable", "void set_zoneMask(uint)", asMETHODPR(Drawable, SetZoneMask, (unsigned), void), asCALL_THISCALL);
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod("Drawable", "void UnsubscribeFromAllEvents()", asMETHODPR(Drawable, UnsubscribeFromAllEvents, (), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Drawable", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", asFUNCTION(Drawable_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), asCALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Drawable", "void UnsubscribeFromEvent(StringHash)", asMETHODPR(Drawable, UnsubscribeFromEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Drawable", "void UnsubscribeFromEvent(Object@+, StringHash)", asMETHODPR(Drawable, UnsubscribeFromEvent, (Object*, StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Drawable", "void UnsubscribeFromEvents(Object@+)", asMETHODPR(Drawable, UnsubscribeFromEvents, (Object*), void), asCALL_THISCALL);
    // virtual void Drawable::Update(const FrameInfo& frame) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Drawable", "void Update(const FrameInfo&in)", asMETHODPR(Drawable, Update, (const FrameInfo&), void), asCALL_THISCALL);
    // virtual void Drawable::UpdateBatches(const FrameInfo& frame) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Drawable", "void UpdateBatches(const FrameInfo&in)", asMETHODPR(Drawable, UpdateBatches, (const FrameInfo&), void), asCALL_THISCALL);
    // virtual void Drawable::UpdateGeometry(const FrameInfo& frame) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Drawable", "void UpdateGeometry(const FrameInfo&in)", asMETHODPR(Drawable, UpdateGeometry, (const FrameInfo&), void), asCALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("Drawable", "int WeakRefs() const", asMETHODPR(Drawable, WeakRefs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("Drawable", "int get_weakRefs() const", asMETHODPR(Drawable, WeakRefs, () const, int), asCALL_THISCALL);
    // void Serializable::WriteDeltaUpdate(Serializer& dest, const DirtyBits& attributeBits, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Drawable", "void WriteDeltaUpdate(Serializer&, const DirtyBits&in, uint8)", asMETHODPR(Drawable, WriteDeltaUpdate, (Serializer&, const DirtyBits&, unsigned char), void), asCALL_THISCALL);
    // void Serializable::WriteInitialDeltaUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Drawable", "void WriteInitialDeltaUpdate(Serializer&, uint8)", asMETHODPR(Drawable, WriteInitialDeltaUpdate, (Serializer&, unsigned char), void), asCALL_THISCALL);
    // void Serializable::WriteLatestDataUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Drawable", "void WriteLatestDataUpdate(Serializer&, uint8)", asMETHODPR(Drawable, WriteLatestDataUpdate, (Serializer&, unsigned char), void), asCALL_THISCALL);
#ifdef REGISTER_MANUAL_PART_Component
    REGISTER_MANUAL_PART_Component(Drawable, "Drawable")
#endif
#ifdef REGISTER_MANUAL_PART_Animatable
    REGISTER_MANUAL_PART_Animatable(Drawable, "Drawable")
#endif
#ifdef REGISTER_MANUAL_PART_Serializable
    REGISTER_MANUAL_PART_Serializable(Drawable, "Drawable")
#endif
#ifdef REGISTER_MANUAL_PART_Object
    REGISTER_MANUAL_PART_Object(Drawable, "Drawable")
#endif
#ifdef REGISTER_MANUAL_PART_RefCounted
    REGISTER_MANUAL_PART_RefCounted(Drawable, "Drawable")
#endif
#ifdef REGISTER_MANUAL_PART_Drawable
    REGISTER_MANUAL_PART_Drawable(Drawable, "Drawable")
#endif
    RegisterSubclass<Component, Drawable>(engine, "Component", "Drawable");
    RegisterSubclass<Animatable, Drawable>(engine, "Animatable", "Drawable");
    RegisterSubclass<Serializable, Drawable>(engine, "Serializable", "Drawable");
    RegisterSubclass<Object, Drawable>(engine, "Object", "Drawable");
    RegisterSubclass<RefCounted, Drawable>(engine, "RefCounted", "Drawable");

#ifdef URHO3D_URHO2D
    // void Drawable::AddLight(Light* light) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Drawable2D", "void AddLight(Light@+)", asMETHODPR(Drawable2D, AddLight, (Light*), void), asCALL_THISCALL);
    // void RefCounted::AddRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("Drawable2D", asBEHAVE_ADDREF, "void f()", asMETHODPR(Drawable2D, AddRef, (), void), asCALL_THISCALL);
    // void Component::AddReplicationState(ComponentReplicationState* state) | File: ../Scene/Component.h
    // Error: type "ComponentReplicationState*" can not automatically bind
    // void Drawable::AddVertexLight(Light* light) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Drawable2D", "void AddVertexLight(Light@+)", asMETHODPR(Drawable2D, AddVertexLight, (Light*), void), asCALL_THISCALL);
    // void Serializable::AllocateNetworkState() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Drawable2D", "void AllocateNetworkState()", asMETHODPR(Drawable2D, AllocateNetworkState, (), void), asCALL_THISCALL);
    // virtual void Serializable::ApplyAttributes() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Drawable2D", "void ApplyAttributes()", asMETHODPR(Drawable2D, ApplyAttributes, (), void), asCALL_THISCALL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // void Component::CleanupConnection(Connection* connection) | File: ../Scene/Component.h
    // Not registered because have @manualbind mark
    // void Drawable::DrawDebugGeometry(DebugRenderer* debug, bool depthTest) override | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Drawable2D", "void DrawDebugGeometry(DebugRenderer@+, bool)", asMETHODPR(Drawable2D, DrawDebugGeometry, (DebugRenderer*, bool), void), asCALL_THISCALL);
    // virtual bool Drawable::DrawOcclusion(OcclusionBuffer* buffer) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Drawable2D", "bool DrawOcclusion(OcclusionBuffer@+)", asMETHODPR(Drawable2D, DrawOcclusion, (OcclusionBuffer*), bool), asCALL_THISCALL);
    // bool Animatable::GetAnimationEnabled() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Drawable2D", "bool GetAnimationEnabled() const", asMETHODPR(Drawable2D, GetAnimationEnabled, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Drawable2D", "bool get_animationEnabled() const", asMETHODPR(Drawable2D, GetAnimationEnabled, () const, bool), asCALL_THISCALL);
    // Variant Serializable::GetAttribute(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Drawable2D", "Variant GetAttribute(uint) const", asMETHODPR(Drawable2D, GetAttribute, (unsigned) const, Variant), asCALL_THISCALL);
    engine->RegisterObjectMethod("Drawable2D", "Variant get_attributes(uint) const", asMETHODPR(Drawable2D, GetAttribute, (unsigned) const, Variant), asCALL_THISCALL);
    // Variant Serializable::GetAttribute(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Drawable2D", "Variant GetAttribute(const String&in) const", asMETHODPR(Drawable2D, GetAttribute, (const String&) const, Variant), asCALL_THISCALL);
    // ValueAnimation* Animatable::GetAttributeAnimation(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Drawable2D", "ValueAnimation@+ GetAttributeAnimation(const String&in) const", asMETHODPR(Drawable2D, GetAttributeAnimation, (const String&) const, ValueAnimation*), asCALL_THISCALL);
    // float Animatable::GetAttributeAnimationSpeed(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Drawable2D", "float GetAttributeAnimationSpeed(const String&in) const", asMETHODPR(Drawable2D, GetAttributeAnimationSpeed, (const String&) const, float), asCALL_THISCALL);
    // float Animatable::GetAttributeAnimationTime(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Drawable2D", "float GetAttributeAnimationTime(const String&in) const", asMETHODPR(Drawable2D, GetAttributeAnimationTime, (const String&) const, float), asCALL_THISCALL);
    // WrapMode Animatable::GetAttributeAnimationWrapMode(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Drawable2D", "WrapMode GetAttributeAnimationWrapMode(const String&in) const", asMETHODPR(Drawable2D, GetAttributeAnimationWrapMode, (const String&) const, WrapMode), asCALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Drawable2D", "Variant GetAttributeDefault(uint) const", asMETHODPR(Drawable2D, GetAttributeDefault, (unsigned) const, Variant), asCALL_THISCALL);
    engine->RegisterObjectMethod("Drawable2D", "Variant get_attributeDefaults(uint) const", asMETHODPR(Drawable2D, GetAttributeDefault, (unsigned) const, Variant), asCALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Drawable2D", "Variant GetAttributeDefault(const String&in) const", asMETHODPR(Drawable2D, GetAttributeDefault, (const String&) const, Variant), asCALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // const Vector<SourceBatch>& Drawable::GetBatches() const | File: ../Graphics/Drawable.h
    // Error: type "const Vector<SourceBatch>&" can not automatically bind
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Drawable2D", "bool GetBlockEvents() const", asMETHODPR(Drawable2D, GetBlockEvents, () const, bool), asCALL_THISCALL);
    // const BoundingBox& Drawable::GetBoundingBox() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Drawable2D", "const BoundingBox& GetBoundingBox() const", asMETHODPR(Drawable2D, GetBoundingBox, () const, const BoundingBox&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Drawable2D", "const BoundingBox& get_boundingBox() const", asMETHODPR(Drawable2D, GetBoundingBox, () const, const BoundingBox&), asCALL_THISCALL);
    // bool Drawable::GetCastShadows() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Drawable2D", "bool GetCastShadows() const", asMETHODPR(Drawable2D, GetCastShadows, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Drawable2D", "bool get_castShadows() const", asMETHODPR(Drawable2D, GetCastShadows, () const, bool), asCALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Drawable2D", "const String& GetCategory() const", asMETHODPR(Drawable2D, GetCategory, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Drawable2D", "const String& get_category() const", asMETHODPR(Drawable2D, GetCategory, () const, const String&), asCALL_THISCALL);
    // Component* Component::GetComponent(StringHash type) const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Drawable2D", "Component@+ GetComponent(StringHash) const", asMETHODPR(Drawable2D, GetComponent, (StringHash) const, Component*), asCALL_THISCALL);
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
    engine->RegisterObjectMethod("Drawable2D", "float GetDistance() const", asMETHODPR(Drawable2D, GetDistance, () const, float), asCALL_THISCALL);
    // unsigned char Drawable::GetDrawableFlags() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Drawable2D", "uint8 GetDrawableFlags() const", asMETHODPR(Drawable2D, GetDrawableFlags, () const, unsigned char), asCALL_THISCALL);
    // float Drawable::GetDrawDistance() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Drawable2D", "float GetDrawDistance() const", asMETHODPR(Drawable2D, GetDrawDistance, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("Drawable2D", "float get_drawDistance() const", asMETHODPR(Drawable2D, GetDrawDistance, () const, float), asCALL_THISCALL);
    // VariantMap& Object::GetEventDataMap() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Drawable2D", "VariantMap& GetEventDataMap() const", asMETHODPR(Drawable2D, GetEventDataMap, () const, VariantMap&), asCALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Drawable2D", "Object@+ GetEventSender() const", asMETHODPR(Drawable2D, GetEventSender, () const, Object*), asCALL_THISCALL);
    // Light* Drawable::GetFirstLight() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Drawable2D", "Light@+ GetFirstLight() const", asMETHODPR(Drawable2D, GetFirstLight, () const, Light*), asCALL_THISCALL);
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Drawable2D", "const Variant& GetGlobalVar(StringHash) const", asMETHODPR(Drawable2D, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Drawable2D", "const Variant& get_globalVar(StringHash) const", asMETHODPR(Drawable2D, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Drawable2D", "const VariantMap& GetGlobalVars() const", asMETHODPR(Drawable2D, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Drawable2D", "const VariantMap& get_globalVars() const", asMETHODPR(Drawable2D, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    // unsigned Component::GetID() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Drawable2D", "uint GetID() const", asMETHODPR(Drawable2D, GetID, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("Drawable2D", "uint get_id() const", asMETHODPR(Drawable2D, GetID, () const, unsigned), asCALL_THISCALL);
    // bool Serializable::GetInterceptNetworkUpdate(const String& attributeName) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Drawable2D", "bool GetInterceptNetworkUpdate(const String&in) const", asMETHODPR(Drawable2D, GetInterceptNetworkUpdate, (const String&) const, bool), asCALL_THISCALL);
    // int Drawable2D::GetLayer() const | File: ../Urho2D/Drawable2D.h
    engine->RegisterObjectMethod("Drawable2D", "int GetLayer() const", asMETHODPR(Drawable2D, GetLayer, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("Drawable2D", "int get_layer() const", asMETHODPR(Drawable2D, GetLayer, () const, int), asCALL_THISCALL);
    // unsigned Drawable::GetLightMask() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Drawable2D", "uint GetLightMask() const", asMETHODPR(Drawable2D, GetLightMask, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("Drawable2D", "uint get_lightMask() const", asMETHODPR(Drawable2D, GetLightMask, () const, unsigned), asCALL_THISCALL);
    // const PODVector<Light*>& Drawable::GetLights() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Drawable2D", "Array<Light@>@ GetLights() const", asFUNCTION(Drawable2D_GetLights_void), asCALL_CDECL_OBJFIRST);
    // float Drawable::GetLodBias() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Drawable2D", "float GetLodBias() const", asMETHODPR(Drawable2D, GetLodBias, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("Drawable2D", "float get_lodBias() const", asMETHODPR(Drawable2D, GetLodBias, () const, float), asCALL_THISCALL);
    // float Drawable::GetLodDistance() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Drawable2D", "float GetLodDistance() const", asMETHODPR(Drawable2D, GetLodDistance, () const, float), asCALL_THISCALL);
    // virtual Geometry* Drawable::GetLodGeometry(unsigned batchIndex, unsigned level) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Drawable2D", "Geometry@+ GetLodGeometry(uint, uint)", asMETHODPR(Drawable2D, GetLodGeometry, (unsigned, unsigned), Geometry*), asCALL_THISCALL);
    // unsigned Drawable::GetMaxLights() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Drawable2D", "uint GetMaxLights() const", asMETHODPR(Drawable2D, GetMaxLights, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("Drawable2D", "uint get_maxLights() const", asMETHODPR(Drawable2D, GetMaxLights, () const, unsigned), asCALL_THISCALL);
    // float Drawable::GetMaxZ() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Drawable2D", "float GetMaxZ() const", asMETHODPR(Drawable2D, GetMaxZ, () const, float), asCALL_THISCALL);
    // float Drawable::GetMinZ() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Drawable2D", "float GetMinZ() const", asMETHODPR(Drawable2D, GetMinZ, () const, float), asCALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetNetworkAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // NetworkState* Serializable::GetNetworkState() const | File: ../Scene/Serializable.h
    // Error: type "NetworkState*" can not automatically bind
    // Node* Component::GetNode() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Drawable2D", "Node@+ GetNode() const", asMETHODPR(Drawable2D, GetNode, () const, Node*), asCALL_THISCALL);
    engine->RegisterObjectMethod("Drawable2D", "Node@+ get_node() const", asMETHODPR(Drawable2D, GetNode, () const, Node*), asCALL_THISCALL);
    // unsigned Serializable::GetNumAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Drawable2D", "uint GetNumAttributes() const", asMETHODPR(Drawable2D, GetNumAttributes, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("Drawable2D", "uint get_numAttributes() const", asMETHODPR(Drawable2D, GetNumAttributes, () const, unsigned), asCALL_THISCALL);
    // unsigned Serializable::GetNumNetworkAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Drawable2D", "uint GetNumNetworkAttributes() const", asMETHODPR(Drawable2D, GetNumNetworkAttributes, () const, unsigned), asCALL_THISCALL);
    // virtual unsigned Drawable::GetNumOccluderTriangles() | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Drawable2D", "uint GetNumOccluderTriangles()", asMETHODPR(Drawable2D, GetNumOccluderTriangles, (), unsigned), asCALL_THISCALL);
    // ObjectAnimation* Animatable::GetObjectAnimation() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Drawable2D", "ObjectAnimation@+ GetObjectAnimation() const", asMETHODPR(Drawable2D, GetObjectAnimation, () const, ObjectAnimation*), asCALL_THISCALL);
    engine->RegisterObjectMethod("Drawable2D", "ObjectAnimation@+ get_objectAnimation() const", asMETHODPR(Drawable2D, GetObjectAnimation, () const, ObjectAnimation*), asCALL_THISCALL);
    // ResourceRef Animatable::GetObjectAnimationAttr() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Drawable2D", "ResourceRef GetObjectAnimationAttr() const", asMETHODPR(Drawable2D, GetObjectAnimationAttr, () const, ResourceRef), asCALL_THISCALL);
    // Octant* Drawable::GetOctant() const | File: ../Graphics/Drawable.h
    // Error: type "Octant" can not automatically bind bacause have @nobind mark
    // int Drawable2D::GetOrderInLayer() const | File: ../Urho2D/Drawable2D.h
    engine->RegisterObjectMethod("Drawable2D", "int GetOrderInLayer() const", asMETHODPR(Drawable2D, GetOrderInLayer, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("Drawable2D", "int get_orderInLayer() const", asMETHODPR(Drawable2D, GetOrderInLayer, () const, int), asCALL_THISCALL);
    // Scene* Component::GetScene() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Drawable2D", "Scene@+ GetScene() const", asMETHODPR(Drawable2D, GetScene, () const, Scene*), asCALL_THISCALL);
    // float Drawable::GetShadowDistance() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Drawable2D", "float GetShadowDistance() const", asMETHODPR(Drawable2D, GetShadowDistance, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("Drawable2D", "float get_shadowDistance() const", asMETHODPR(Drawable2D, GetShadowDistance, () const, float), asCALL_THISCALL);
    // unsigned Drawable::GetShadowMask() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Drawable2D", "uint GetShadowMask() const", asMETHODPR(Drawable2D, GetShadowMask, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("Drawable2D", "uint get_shadowMask() const", asMETHODPR(Drawable2D, GetShadowMask, () const, unsigned), asCALL_THISCALL);
    // float Drawable::GetSortValue() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Drawable2D", "float GetSortValue() const", asMETHODPR(Drawable2D, GetSortValue, () const, float), asCALL_THISCALL);
    // const Vector<SourceBatch2D>& Drawable2D::GetSourceBatches() | File: ../Urho2D/Drawable2D.h
    // Error: type "const Vector<SourceBatch2D>&" can not automatically bind
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Drawable2D", "Object@+ GetSubsystem(StringHash) const", asMETHODPR(Drawable2D, GetSubsystem, (StringHash) const, Object*), asCALL_THISCALL);
    // template<class T> T* Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("Drawable2D", "StringHash GetType() const", asMETHODPR(Drawable2D, GetType, () const, StringHash), asCALL_THISCALL);
    engine->RegisterObjectMethod("Drawable2D", "StringHash get_type() const", asMETHODPR(Drawable2D, GetType, () const, StringHash), asCALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("Drawable2D", "const String& GetTypeName() const", asMETHODPR(Drawable2D, GetTypeName, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Drawable2D", "const String& get_typeName() const", asMETHODPR(Drawable2D, GetTypeName, () const, const String&), asCALL_THISCALL);
    // virtual UpdateGeometryType Drawable::GetUpdateGeometryType() | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Drawable2D", "UpdateGeometryType GetUpdateGeometryType()", asMETHODPR(Drawable2D, GetUpdateGeometryType, (), UpdateGeometryType), asCALL_THISCALL);
    // const PODVector<Light*>& Drawable::GetVertexLights() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Drawable2D", "Array<Light@>@ GetVertexLights() const", asFUNCTION(Drawable2D_GetVertexLights_void), asCALL_CDECL_OBJFIRST);
    // unsigned Drawable::GetViewMask() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Drawable2D", "uint GetViewMask() const", asMETHODPR(Drawable2D, GetViewMask, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("Drawable2D", "uint get_viewMask() const", asMETHODPR(Drawable2D, GetViewMask, () const, unsigned), asCALL_THISCALL);
    // const BoundingBox& Drawable::GetWorldBoundingBox() | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Drawable2D", "const BoundingBox& GetWorldBoundingBox()", asMETHODPR(Drawable2D, GetWorldBoundingBox, (), const BoundingBox&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Drawable2D", "const BoundingBox& get_worldBoundingBox()", asMETHODPR(Drawable2D, GetWorldBoundingBox, (), const BoundingBox&), asCALL_THISCALL);
    // Zone* Drawable::GetZone() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Drawable2D", "Zone@+ GetZone() const", asMETHODPR(Drawable2D, GetZone, () const, Zone*), asCALL_THISCALL);
    engine->RegisterObjectMethod("Drawable2D", "Zone@+ get_zone() const", asMETHODPR(Drawable2D, GetZone, () const, Zone*), asCALL_THISCALL);
    // unsigned Drawable::GetZoneMask() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Drawable2D", "uint GetZoneMask() const", asMETHODPR(Drawable2D, GetZoneMask, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("Drawable2D", "uint get_zoneMask() const", asMETHODPR(Drawable2D, GetZoneMask, () const, unsigned), asCALL_THISCALL);
    // bool Drawable::HasBasePass(unsigned batchIndex) const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Drawable2D", "bool HasBasePass(uint) const", asMETHODPR(Drawable2D, HasBasePass, (unsigned) const, bool), asCALL_THISCALL);
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Drawable2D", "bool HasEventHandlers() const", asMETHODPR(Drawable2D, HasEventHandlers, () const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Drawable2D", "bool HasSubscribedToEvent(StringHash) const", asMETHODPR(Drawable2D, HasSubscribedToEvent, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Drawable2D", "bool HasSubscribedToEvent(Object@+, StringHash) const", asMETHODPR(Drawable2D, HasSubscribedToEvent, (Object*, StringHash) const, bool), asCALL_THISCALL);
    // bool Component::IsEnabled() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Drawable2D", "bool IsEnabled() const", asMETHODPR(Drawable2D, IsEnabled, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Drawable2D", "bool get_enabled() const", asMETHODPR(Drawable2D, IsEnabled, () const, bool), asCALL_THISCALL);
    // bool Component::IsEnabledEffective() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Drawable2D", "bool IsEnabledEffective() const", asMETHODPR(Drawable2D, IsEnabledEffective, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Drawable2D", "bool get_enabledEffective() const", asMETHODPR(Drawable2D, IsEnabledEffective, () const, bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Drawable2D", "bool IsInstanceOf(StringHash) const", asMETHODPR(Drawable2D, IsInstanceOf, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // bool Drawable::IsInView() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Drawable2D", "bool IsInView() const", asMETHODPR(Drawable2D, IsInView, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Drawable2D", "bool get_inView() const", asMETHODPR(Drawable2D, IsInView, () const, bool), asCALL_THISCALL);
    // bool Drawable::IsInView(Camera* camera) const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Drawable2D", "bool IsInView(Camera@+) const", asMETHODPR(Drawable2D, IsInView, (Camera*) const, bool), asCALL_THISCALL);
    // bool Drawable::IsInView(const FrameInfo& frame, bool anyCamera=false) const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Drawable2D", "bool IsInView(const FrameInfo&in, bool = false) const", asMETHODPR(Drawable2D, IsInView, (const FrameInfo&, bool) const, bool), asCALL_THISCALL);
    // bool Drawable::IsOccludee() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Drawable2D", "bool IsOccludee() const", asMETHODPR(Drawable2D, IsOccludee, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Drawable2D", "bool get_occludee() const", asMETHODPR(Drawable2D, IsOccludee, () const, bool), asCALL_THISCALL);
    // bool Drawable::IsOccluder() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Drawable2D", "bool IsOccluder() const", asMETHODPR(Drawable2D, IsOccluder, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Drawable2D", "bool get_occluder() const", asMETHODPR(Drawable2D, IsOccluder, () const, bool), asCALL_THISCALL);
    // bool Component::IsReplicated() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Drawable2D", "bool IsReplicated() const", asMETHODPR(Drawable2D, IsReplicated, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Drawable2D", "bool get_replicated() const", asMETHODPR(Drawable2D, IsReplicated, () const, bool), asCALL_THISCALL);
    // bool Serializable::IsTemporary() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Drawable2D", "bool IsTemporary() const", asMETHODPR(Drawable2D, IsTemporary, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Drawable2D", "bool get_temporary() const", asMETHODPR(Drawable2D, IsTemporary, () const, bool), asCALL_THISCALL);
    // bool Drawable::IsZoneDirty() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Drawable2D", "bool IsZoneDirty() const", asMETHODPR(Drawable2D, IsZoneDirty, () const, bool), asCALL_THISCALL);
    // void Drawable::LimitLights() | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Drawable2D", "void LimitLights()", asMETHODPR(Drawable2D, LimitLights, (), void), asCALL_THISCALL);
    // void Drawable::LimitVertexLights(bool removeConvertedLights) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Drawable2D", "void LimitVertexLights(bool)", asMETHODPR(Drawable2D, LimitVertexLights, (bool), void), asCALL_THISCALL);
    // virtual bool Serializable::Load(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Drawable2D", "bool Load(Deserializer&)", asMETHODPR(Drawable2D, Load, (Deserializer&), bool), asCALL_THISCALL);
    // bool Animatable::LoadJSON(const JSONValue& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Drawable2D", "bool LoadJSON(const JSONValue&in)", asMETHODPR(Drawable2D, LoadJSON, (const JSONValue&), bool), asCALL_THISCALL);
    // bool Animatable::LoadXML(const XMLElement& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Drawable2D", "bool LoadXML(const XMLElement&in)", asMETHODPR(Drawable2D, LoadXML, (const XMLElement&), bool), asCALL_THISCALL);
    // void Drawable::MarkForUpdate() | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Drawable2D", "void MarkForUpdate()", asMETHODPR(Drawable2D, MarkForUpdate, (), void), asCALL_THISCALL);
    // void Drawable::MarkInView(const FrameInfo& frame) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Drawable2D", "void MarkInView(const FrameInfo&in)", asMETHODPR(Drawable2D, MarkInView, (const FrameInfo&), void), asCALL_THISCALL);
    // void Drawable::MarkInView(unsigned frameNumber) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Drawable2D", "void MarkInView(uint)", asMETHODPR(Drawable2D, MarkInView, (unsigned), void), asCALL_THISCALL);
    // void Component::MarkNetworkUpdate() override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Drawable2D", "void MarkNetworkUpdate()", asMETHODPR(Drawable2D, MarkNetworkUpdate, (), void), asCALL_THISCALL);
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Drawable2D", "void OnEvent(Object@+, StringHash, VariantMap&)", asMETHODPR(Drawable2D, OnEvent, (Object*, StringHash, VariantMap&), void), asCALL_THISCALL);
    // virtual void Serializable::OnGetAttribute(const AttributeInfo& attr, Variant& dest) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Drawable2D", "void OnGetAttribute(const AttributeInfo&in, Variant&) const", asMETHODPR(Drawable2D, OnGetAttribute, (const AttributeInfo&, Variant&) const, void), asCALL_THISCALL);
    // virtual void Serializable::OnSetAttribute(const AttributeInfo& attr, const Variant& src) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Drawable2D", "void OnSetAttribute(const AttributeInfo&in, const Variant&in)", asMETHODPR(Drawable2D, OnSetAttribute, (const AttributeInfo&, const Variant&), void), asCALL_THISCALL);
    // void Drawable2D::OnSetEnabled() override | File: ../Urho2D/Drawable2D.h
    engine->RegisterObjectMethod("Drawable2D", "void OnSetEnabled()", asMETHODPR(Drawable2D, OnSetEnabled, (), void), asCALL_THISCALL);
    // void Component::PrepareNetworkUpdate() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Drawable2D", "void PrepareNetworkUpdate()", asMETHODPR(Drawable2D, PrepareNetworkUpdate, (), void), asCALL_THISCALL);
    // virtual void Drawable::ProcessRayQuery(const RayOctreeQuery& query, PODVector<RayQueryResult>& results) | File: ../Graphics/Drawable.h
    // Error: type "RayOctreeQuery" can not automatically bind bacause have @nobind mark
    // bool Serializable::ReadDeltaUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Drawable2D", "bool ReadDeltaUpdate(Deserializer&)", asMETHODPR(Drawable2D, ReadDeltaUpdate, (Deserializer&), bool), asCALL_THISCALL);
    // bool Serializable::ReadLatestDataUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Drawable2D", "bool ReadLatestDataUpdate(Deserializer&)", asMETHODPR(Drawable2D, ReadLatestDataUpdate, (Deserializer&), bool), asCALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("Drawable2D", "int Refs() const", asMETHODPR(Drawable2D, Refs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("Drawable2D", "int get_refs() const", asMETHODPR(Drawable2D, Refs, () const, int), asCALL_THISCALL);
    // static void Drawable2D::RegisterObject(Context* context) | File: ../Urho2D/Drawable2D.h
    // Not registered because have @nobind mark
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("Drawable2D", asBEHAVE_RELEASE, "void f()", asMETHODPR(Drawable2D, ReleaseRef, (), void), asCALL_THISCALL);
    // void Component::Remove() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Drawable2D", "void Remove()", asMETHODPR(Drawable2D, Remove, (), void), asCALL_THISCALL);
    // void Animatable::RemoveAttributeAnimation(const String& name) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Drawable2D", "void RemoveAttributeAnimation(const String&in)", asMETHODPR(Drawable2D, RemoveAttributeAnimation, (const String&), void), asCALL_THISCALL);
    // void Serializable::RemoveInstanceDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Drawable2D", "void RemoveInstanceDefault()", asMETHODPR(Drawable2D, RemoveInstanceDefault, (), void), asCALL_THISCALL);
    // void Animatable::RemoveObjectAnimation() | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Drawable2D", "void RemoveObjectAnimation()", asMETHODPR(Drawable2D, RemoveObjectAnimation, (), void), asCALL_THISCALL);
    // void Serializable::ResetToDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Drawable2D", "void ResetToDefault()", asMETHODPR(Drawable2D, ResetToDefault, (), void), asCALL_THISCALL);
    // bool Component::Save(Serializer& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Drawable2D", "bool Save(Serializer&) const", asMETHODPR(Drawable2D, Save, (Serializer&) const, bool), asCALL_THISCALL);
    // virtual bool Serializable::SaveDefaultAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Drawable2D", "bool SaveDefaultAttributes() const", asMETHODPR(Drawable2D, SaveDefaultAttributes, () const, bool), asCALL_THISCALL);
    // bool Component::SaveJSON(JSONValue& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Drawable2D", "bool SaveJSON(JSONValue&) const", asMETHODPR(Drawable2D, SaveJSON, (JSONValue&) const, bool), asCALL_THISCALL);
    // bool Component::SaveXML(XMLElement& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Drawable2D", "bool SaveXML(XMLElement&) const", asMETHODPR(Drawable2D, SaveXML, (XMLElement&) const, bool), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Drawable2D", "void SendEvent(StringHash)", asMETHODPR(Drawable2D, SendEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Drawable2D", "void SendEvent(StringHash, VariantMap&)", asMETHODPR(Drawable2D, SendEvent, (StringHash, VariantMap&), void), asCALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void Animatable::SetAnimationEnabled(bool enable) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Drawable2D", "void SetAnimationEnabled(bool)", asMETHODPR(Drawable2D, SetAnimationEnabled, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Drawable2D", "void set_animationEnabled(bool)", asMETHODPR(Drawable2D, SetAnimationEnabled, (bool), void), asCALL_THISCALL);
    // void Animatable::SetAnimationTime(float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Drawable2D", "void SetAnimationTime(float)", asMETHODPR(Drawable2D, SetAnimationTime, (float), void), asCALL_THISCALL);
    // bool Serializable::SetAttribute(unsigned index, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Drawable2D", "bool SetAttribute(uint, const Variant&in)", asMETHODPR(Drawable2D, SetAttribute, (unsigned, const Variant&), bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Drawable2D", "bool set_attributes(uint, const Variant&in)", asMETHODPR(Drawable2D, SetAttribute, (unsigned, const Variant&), bool), asCALL_THISCALL);
    // bool Serializable::SetAttribute(const String& name, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Drawable2D", "bool SetAttribute(const String&in, const Variant&in)", asMETHODPR(Drawable2D, SetAttribute, (const String&, const Variant&), bool), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimation(const String& name, ValueAnimation* attributeAnimation, WrapMode wrapMode=WM_LOOP, float speed=1.0f) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Drawable2D", "void SetAttributeAnimation(const String&in, ValueAnimation@+, WrapMode = WM_LOOP, float = 1.0f)", asMETHODPR(Drawable2D, SetAttributeAnimation, (const String&, ValueAnimation*, WrapMode, float), void), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimationSpeed(const String& name, float speed) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Drawable2D", "void SetAttributeAnimationSpeed(const String&in, float)", asMETHODPR(Drawable2D, SetAttributeAnimationSpeed, (const String&, float), void), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimationTime(const String& name, float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Drawable2D", "void SetAttributeAnimationTime(const String&in, float)", asMETHODPR(Drawable2D, SetAttributeAnimationTime, (const String&, float), void), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimationWrapMode(const String& name, WrapMode wrapMode) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Drawable2D", "void SetAttributeAnimationWrapMode(const String&in, WrapMode)", asMETHODPR(Drawable2D, SetAttributeAnimationWrapMode, (const String&, WrapMode), void), asCALL_THISCALL);
    // void Drawable::SetBasePass(unsigned batchIndex) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Drawable2D", "void SetBasePass(uint)", asMETHODPR(Drawable2D, SetBasePass, (unsigned), void), asCALL_THISCALL);
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Drawable2D", "void SetBlockEvents(bool)", asMETHODPR(Drawable2D, SetBlockEvents, (bool), void), asCALL_THISCALL);
    // void Drawable::SetCastShadows(bool enable) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Drawable2D", "void SetCastShadows(bool)", asMETHODPR(Drawable2D, SetCastShadows, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Drawable2D", "void set_castShadows(bool)", asMETHODPR(Drawable2D, SetCastShadows, (bool), void), asCALL_THISCALL);
    // void Drawable::SetDrawDistance(float distance) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Drawable2D", "void SetDrawDistance(float)", asMETHODPR(Drawable2D, SetDrawDistance, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Drawable2D", "void set_drawDistance(float)", asMETHODPR(Drawable2D, SetDrawDistance, (float), void), asCALL_THISCALL);
    // void Component::SetEnabled(bool enable) | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Drawable2D", "void SetEnabled(bool)", asMETHODPR(Drawable2D, SetEnabled, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Drawable2D", "void set_enabled(bool)", asMETHODPR(Drawable2D, SetEnabled, (bool), void), asCALL_THISCALL);
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Drawable2D", "void SetGlobalVar(StringHash, const Variant&in)", asMETHODPR(Drawable2D, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Drawable2D", "void set_globalVar(StringHash, const Variant&in)", asMETHODPR(Drawable2D, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    // void Serializable::SetInstanceDefault(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Drawable2D", "void SetInstanceDefault(bool)", asMETHODPR(Drawable2D, SetInstanceDefault, (bool), void), asCALL_THISCALL);
    // void Serializable::SetInterceptNetworkUpdate(const String& attributeName, bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Drawable2D", "void SetInterceptNetworkUpdate(const String&in, bool)", asMETHODPR(Drawable2D, SetInterceptNetworkUpdate, (const String&, bool), void), asCALL_THISCALL);
    // void Drawable2D::SetLayer(int layer) | File: ../Urho2D/Drawable2D.h
    engine->RegisterObjectMethod("Drawable2D", "void SetLayer(int)", asMETHODPR(Drawable2D, SetLayer, (int), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Drawable2D", "void set_layer(int)", asMETHODPR(Drawable2D, SetLayer, (int), void), asCALL_THISCALL);
    // void Drawable::SetLightMask(unsigned mask) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Drawable2D", "void SetLightMask(uint)", asMETHODPR(Drawable2D, SetLightMask, (unsigned), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Drawable2D", "void set_lightMask(uint)", asMETHODPR(Drawable2D, SetLightMask, (unsigned), void), asCALL_THISCALL);
    // void Drawable::SetLodBias(float bias) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Drawable2D", "void SetLodBias(float)", asMETHODPR(Drawable2D, SetLodBias, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Drawable2D", "void set_lodBias(float)", asMETHODPR(Drawable2D, SetLodBias, (float), void), asCALL_THISCALL);
    // void Drawable::SetMaxLights(unsigned num) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Drawable2D", "void SetMaxLights(uint)", asMETHODPR(Drawable2D, SetMaxLights, (unsigned), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Drawable2D", "void set_maxLights(uint)", asMETHODPR(Drawable2D, SetMaxLights, (unsigned), void), asCALL_THISCALL);
    // void Drawable::SetMinMaxZ(float minZ, float maxZ) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Drawable2D", "void SetMinMaxZ(float, float)", asMETHODPR(Drawable2D, SetMinMaxZ, (float, float), void), asCALL_THISCALL);
    // void Animatable::SetObjectAnimation(ObjectAnimation* objectAnimation) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Drawable2D", "void SetObjectAnimation(ObjectAnimation@+)", asMETHODPR(Drawable2D, SetObjectAnimation, (ObjectAnimation*), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Drawable2D", "void set_objectAnimation(ObjectAnimation@+)", asMETHODPR(Drawable2D, SetObjectAnimation, (ObjectAnimation*), void), asCALL_THISCALL);
    // void Animatable::SetObjectAnimationAttr(const ResourceRef& value) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Drawable2D", "void SetObjectAnimationAttr(const ResourceRef&in)", asMETHODPR(Drawable2D, SetObjectAnimationAttr, (const ResourceRef&), void), asCALL_THISCALL);
    // void Drawable::SetOccludee(bool enable) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Drawable2D", "void SetOccludee(bool)", asMETHODPR(Drawable2D, SetOccludee, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Drawable2D", "void set_occludee(bool)", asMETHODPR(Drawable2D, SetOccludee, (bool), void), asCALL_THISCALL);
    // void Drawable::SetOccluder(bool enable) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Drawable2D", "void SetOccluder(bool)", asMETHODPR(Drawable2D, SetOccluder, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Drawable2D", "void set_occluder(bool)", asMETHODPR(Drawable2D, SetOccluder, (bool), void), asCALL_THISCALL);
    // void Drawable2D::SetOrderInLayer(int orderInLayer) | File: ../Urho2D/Drawable2D.h
    engine->RegisterObjectMethod("Drawable2D", "void SetOrderInLayer(int)", asMETHODPR(Drawable2D, SetOrderInLayer, (int), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Drawable2D", "void set_orderInLayer(int)", asMETHODPR(Drawable2D, SetOrderInLayer, (int), void), asCALL_THISCALL);
    // void Drawable::SetShadowDistance(float distance) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Drawable2D", "void SetShadowDistance(float)", asMETHODPR(Drawable2D, SetShadowDistance, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Drawable2D", "void set_shadowDistance(float)", asMETHODPR(Drawable2D, SetShadowDistance, (float), void), asCALL_THISCALL);
    // void Drawable::SetShadowMask(unsigned mask) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Drawable2D", "void SetShadowMask(uint)", asMETHODPR(Drawable2D, SetShadowMask, (unsigned), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Drawable2D", "void set_shadowMask(uint)", asMETHODPR(Drawable2D, SetShadowMask, (unsigned), void), asCALL_THISCALL);
    // void Drawable::SetSortValue(float value) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Drawable2D", "void SetSortValue(float)", asMETHODPR(Drawable2D, SetSortValue, (float), void), asCALL_THISCALL);
    // void Serializable::SetTemporary(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Drawable2D", "void SetTemporary(bool)", asMETHODPR(Drawable2D, SetTemporary, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Drawable2D", "void set_temporary(bool)", asMETHODPR(Drawable2D, SetTemporary, (bool), void), asCALL_THISCALL);
    // void Drawable::SetViewMask(unsigned mask) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Drawable2D", "void SetViewMask(uint)", asMETHODPR(Drawable2D, SetViewMask, (unsigned), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Drawable2D", "void set_viewMask(uint)", asMETHODPR(Drawable2D, SetViewMask, (unsigned), void), asCALL_THISCALL);
    // void Drawable::SetZone(Zone* zone, bool temporary=false) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Drawable2D", "void SetZone(Zone@+, bool = false)", asMETHODPR(Drawable2D, SetZone, (Zone*, bool), void), asCALL_THISCALL);
    // void Drawable::SetZoneMask(unsigned mask) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Drawable2D", "void SetZoneMask(uint)", asMETHODPR(Drawable2D, SetZoneMask, (unsigned), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Drawable2D", "void set_zoneMask(uint)", asMETHODPR(Drawable2D, SetZoneMask, (unsigned), void), asCALL_THISCALL);
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod("Drawable2D", "void UnsubscribeFromAllEvents()", asMETHODPR(Drawable2D, UnsubscribeFromAllEvents, (), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Drawable2D", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", asFUNCTION(Drawable2D_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), asCALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Drawable2D", "void UnsubscribeFromEvent(StringHash)", asMETHODPR(Drawable2D, UnsubscribeFromEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Drawable2D", "void UnsubscribeFromEvent(Object@+, StringHash)", asMETHODPR(Drawable2D, UnsubscribeFromEvent, (Object*, StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Drawable2D", "void UnsubscribeFromEvents(Object@+)", asMETHODPR(Drawable2D, UnsubscribeFromEvents, (Object*), void), asCALL_THISCALL);
    // virtual void Drawable::Update(const FrameInfo& frame) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Drawable2D", "void Update(const FrameInfo&in)", asMETHODPR(Drawable2D, Update, (const FrameInfo&), void), asCALL_THISCALL);
    // virtual void Drawable::UpdateBatches(const FrameInfo& frame) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Drawable2D", "void UpdateBatches(const FrameInfo&in)", asMETHODPR(Drawable2D, UpdateBatches, (const FrameInfo&), void), asCALL_THISCALL);
    // virtual void Drawable::UpdateGeometry(const FrameInfo& frame) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Drawable2D", "void UpdateGeometry(const FrameInfo&in)", asMETHODPR(Drawable2D, UpdateGeometry, (const FrameInfo&), void), asCALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("Drawable2D", "int WeakRefs() const", asMETHODPR(Drawable2D, WeakRefs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("Drawable2D", "int get_weakRefs() const", asMETHODPR(Drawable2D, WeakRefs, () const, int), asCALL_THISCALL);
    // void Serializable::WriteDeltaUpdate(Serializer& dest, const DirtyBits& attributeBits, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Drawable2D", "void WriteDeltaUpdate(Serializer&, const DirtyBits&in, uint8)", asMETHODPR(Drawable2D, WriteDeltaUpdate, (Serializer&, const DirtyBits&, unsigned char), void), asCALL_THISCALL);
    // void Serializable::WriteInitialDeltaUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Drawable2D", "void WriteInitialDeltaUpdate(Serializer&, uint8)", asMETHODPR(Drawable2D, WriteInitialDeltaUpdate, (Serializer&, unsigned char), void), asCALL_THISCALL);
    // void Serializable::WriteLatestDataUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Drawable2D", "void WriteLatestDataUpdate(Serializer&, uint8)", asMETHODPR(Drawable2D, WriteLatestDataUpdate, (Serializer&, unsigned char), void), asCALL_THISCALL);
#ifdef REGISTER_MANUAL_PART_Drawable
    REGISTER_MANUAL_PART_Drawable(Drawable2D, "Drawable2D")
#endif
#ifdef REGISTER_MANUAL_PART_Component
    REGISTER_MANUAL_PART_Component(Drawable2D, "Drawable2D")
#endif
#ifdef REGISTER_MANUAL_PART_Animatable
    REGISTER_MANUAL_PART_Animatable(Drawable2D, "Drawable2D")
#endif
#ifdef REGISTER_MANUAL_PART_Serializable
    REGISTER_MANUAL_PART_Serializable(Drawable2D, "Drawable2D")
#endif
#ifdef REGISTER_MANUAL_PART_Object
    REGISTER_MANUAL_PART_Object(Drawable2D, "Drawable2D")
#endif
#ifdef REGISTER_MANUAL_PART_RefCounted
    REGISTER_MANUAL_PART_RefCounted(Drawable2D, "Drawable2D")
#endif
#ifdef REGISTER_MANUAL_PART_Drawable2D
    REGISTER_MANUAL_PART_Drawable2D(Drawable2D, "Drawable2D")
#endif
    RegisterSubclass<Drawable, Drawable2D>(engine, "Drawable", "Drawable2D");
    RegisterSubclass<Component, Drawable2D>(engine, "Component", "Drawable2D");
    RegisterSubclass<Animatable, Drawable2D>(engine, "Animatable", "Drawable2D");
    RegisterSubclass<Serializable, Drawable2D>(engine, "Serializable", "Drawable2D");
    RegisterSubclass<Object, Drawable2D>(engine, "Object", "Drawable2D");
    RegisterSubclass<RefCounted, Drawable2D>(engine, "RefCounted", "Drawable2D");
#endif

    // void UIElement::AddChild(UIElement* element) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "void AddChild(UIElement@+)", asMETHODPR(DropDownList, AddChild, (UIElement*), void), asCALL_THISCALL);
    // void DropDownList::AddItem(UIElement* item) | File: ../UI/DropDownList.h
    engine->RegisterObjectMethod("DropDownList", "void AddItem(UIElement@+)", asMETHODPR(DropDownList, AddItem, (UIElement*), void), asCALL_THISCALL);
    // void RefCounted::AddRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("DropDownList", asBEHAVE_ADDREF, "void f()", asMETHODPR(DropDownList, AddRef, (), void), asCALL_THISCALL);
    // void UIElement::AddTag(const String& tag) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "void AddTag(const String&in)", asMETHODPR(DropDownList, AddTag, (const String&), void), asCALL_THISCALL);
    // void UIElement::AddTags(const String& tags, char separator=';') | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "void AddTags(const String&in, int8 = ';')", asMETHODPR(DropDownList, AddTags, (const String&, char), void), asCALL_THISCALL);
    // void UIElement::AddTags(const StringVector& tags) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "void AddTags(Array<String>@+)", asFUNCTION(DropDownList_AddTags_StringVector), asCALL_CDECL_OBJFIRST);
    // void UIElement::AdjustScissor(IntRect& currentScissor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "void AdjustScissor(IntRect&)", asMETHODPR(DropDownList, AdjustScissor, (IntRect&), void), asCALL_THISCALL);
    // void Serializable::AllocateNetworkState() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("DropDownList", "void AllocateNetworkState()", asMETHODPR(DropDownList, AllocateNetworkState, (), void), asCALL_THISCALL);
    // void DropDownList::ApplyAttributes() override | File: ../UI/DropDownList.h
    engine->RegisterObjectMethod("DropDownList", "void ApplyAttributes()", asMETHODPR(DropDownList, ApplyAttributes, (), void), asCALL_THISCALL);
    // void UIElement::BringToFront() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "void BringToFront()", asMETHODPR(DropDownList, BringToFront, (), void), asCALL_THISCALL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // UIElement* UIElement::CreateChild(StringHash type, const String& name=String::EMPTY, unsigned index=M_MAX_UNSIGNED) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "UIElement@+ CreateChild(StringHash, const String&in = String::EMPTY, uint = M_MAX_UNSIGNED)", asMETHODPR(DropDownList, CreateChild, (StringHash, const String&, unsigned), UIElement*), asCALL_THISCALL);
    // template<class T> T* UIElement::CreateChild(const String& name=String::EMPTY, unsigned index=M_MAX_UNSIGNED) | File: ../UI/UIElement.h
    // Not registered because template
    // void UIElement::DisableLayoutUpdate() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "void DisableLayoutUpdate()", asMETHODPR(DropDownList, DisableLayoutUpdate, (), void), asCALL_THISCALL);
    // explicit DropDownList::DropDownList(Context* context) | File: ../UI/DropDownList.h
    engine->RegisterObjectBehaviour("DropDownList", asBEHAVE_FACTORY, "DropDownList@+ f()", asFUNCTION(DropDownList_DropDownList_Context), asCALL_CDECL);
    // virtual IntVector2 UIElement::ElementToScreen(const IntVector2& position) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "IntVector2 ElementToScreen(const IntVector2&in)", asMETHODPR(DropDownList, ElementToScreen, (const IntVector2&), IntVector2), asCALL_THISCALL);
    // void UIElement::EnableLayoutUpdate() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "void EnableLayoutUpdate()", asMETHODPR(DropDownList, EnableLayoutUpdate, (), void), asCALL_THISCALL);
    // bool UIElement::FilterAttributes(XMLElement& dest) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "bool FilterAttributes(XMLElement&) const", asMETHODPR(DropDownList, FilterAttributes, (XMLElement&) const, bool), asCALL_THISCALL);
    // unsigned UIElement::FindChild(UIElement* element) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "uint FindChild(UIElement@+) const", asMETHODPR(DropDownList, FindChild, (UIElement*) const, unsigned), asCALL_THISCALL);
    // int Menu::GetAcceleratorKey() const | File: ../UI/Menu.h
    engine->RegisterObjectMethod("DropDownList", "int GetAcceleratorKey() const", asMETHODPR(DropDownList, GetAcceleratorKey, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "int get_acceleratorKey() const", asMETHODPR(DropDownList, GetAcceleratorKey, () const, int), asCALL_THISCALL);
    // int Menu::GetAcceleratorQualifiers() const | File: ../UI/Menu.h
    engine->RegisterObjectMethod("DropDownList", "int GetAcceleratorQualifiers() const", asMETHODPR(DropDownList, GetAcceleratorQualifiers, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "int get_acceleratorQualifiers() const", asMETHODPR(DropDownList, GetAcceleratorQualifiers, () const, int), asCALL_THISCALL);
    // bool Animatable::GetAnimationEnabled() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("DropDownList", "bool GetAnimationEnabled() const", asMETHODPR(DropDownList, GetAnimationEnabled, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "bool get_animationEnabled() const", asMETHODPR(DropDownList, GetAnimationEnabled, () const, bool), asCALL_THISCALL);
    // const String& UIElement::GetAppliedStyle() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "const String& GetAppliedStyle() const", asMETHODPR(DropDownList, GetAppliedStyle, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "const String& get_style() const", asMETHODPR(DropDownList, GetAppliedStyle, () const, const String&), asCALL_THISCALL);
    // Variant Serializable::GetAttribute(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("DropDownList", "Variant GetAttribute(uint) const", asMETHODPR(DropDownList, GetAttribute, (unsigned) const, Variant), asCALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "Variant get_attributes(uint) const", asMETHODPR(DropDownList, GetAttribute, (unsigned) const, Variant), asCALL_THISCALL);
    // Variant Serializable::GetAttribute(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("DropDownList", "Variant GetAttribute(const String&in) const", asMETHODPR(DropDownList, GetAttribute, (const String&) const, Variant), asCALL_THISCALL);
    // ValueAnimation* Animatable::GetAttributeAnimation(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("DropDownList", "ValueAnimation@+ GetAttributeAnimation(const String&in) const", asMETHODPR(DropDownList, GetAttributeAnimation, (const String&) const, ValueAnimation*), asCALL_THISCALL);
    // float Animatable::GetAttributeAnimationSpeed(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("DropDownList", "float GetAttributeAnimationSpeed(const String&in) const", asMETHODPR(DropDownList, GetAttributeAnimationSpeed, (const String&) const, float), asCALL_THISCALL);
    // float Animatable::GetAttributeAnimationTime(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("DropDownList", "float GetAttributeAnimationTime(const String&in) const", asMETHODPR(DropDownList, GetAttributeAnimationTime, (const String&) const, float), asCALL_THISCALL);
    // WrapMode Animatable::GetAttributeAnimationWrapMode(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("DropDownList", "WrapMode GetAttributeAnimationWrapMode(const String&in) const", asMETHODPR(DropDownList, GetAttributeAnimationWrapMode, (const String&) const, WrapMode), asCALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("DropDownList", "Variant GetAttributeDefault(uint) const", asMETHODPR(DropDownList, GetAttributeDefault, (unsigned) const, Variant), asCALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "Variant get_attributeDefaults(uint) const", asMETHODPR(DropDownList, GetAttributeDefault, (unsigned) const, Variant), asCALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("DropDownList", "Variant GetAttributeDefault(const String&in) const", asMETHODPR(DropDownList, GetAttributeDefault, (const String&) const, Variant), asCALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // void DropDownList::GetBatches(PODVector<UIBatch>& batches, PODVector<float>& vertexData, const IntRect& currentScissor) override | File: ../UI/DropDownList.h
    // Error: type "PODVector<UIBatch>&" can not automatically bind
    // void UIElement::GetBatchesWithOffset(IntVector2& offset, PODVector<UIBatch>& batches, PODVector<float>& vertexData, IntRect currentScissor) | File: ../UI/UIElement.h
    // Error: type "PODVector<UIBatch>&" can not automatically bind
    // BlendMode BorderImage::GetBlendMode() const | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("DropDownList", "BlendMode GetBlendMode() const", asMETHODPR(DropDownList, GetBlendMode, () const, BlendMode), asCALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "BlendMode get_blendMode() const", asMETHODPR(DropDownList, GetBlendMode, () const, BlendMode), asCALL_THISCALL);
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("DropDownList", "bool GetBlockEvents() const", asMETHODPR(DropDownList, GetBlockEvents, () const, bool), asCALL_THISCALL);
    // const IntRect& BorderImage::GetBorder() const | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("DropDownList", "const IntRect& GetBorder() const", asMETHODPR(DropDownList, GetBorder, () const, const IntRect&), asCALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "const IntRect& get_border() const", asMETHODPR(DropDownList, GetBorder, () const, const IntRect&), asCALL_THISCALL);
    // bool UIElement::GetBringToBack() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "bool GetBringToBack() const", asMETHODPR(DropDownList, GetBringToBack, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "bool get_bringToBack() const", asMETHODPR(DropDownList, GetBringToBack, () const, bool), asCALL_THISCALL);
    // bool UIElement::GetBringToFront() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "bool GetBringToFront() const", asMETHODPR(DropDownList, GetBringToFront, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "bool get_bringToFront() const", asMETHODPR(DropDownList, GetBringToFront, () const, bool), asCALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("DropDownList", "const String& GetCategory() const", asMETHODPR(DropDownList, GetCategory, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "const String& get_category() const", asMETHODPR(DropDownList, GetCategory, () const, const String&), asCALL_THISCALL);
    // UIElement* UIElement::GetChild(unsigned index) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "UIElement@+ GetChild(uint) const", asMETHODPR(DropDownList, GetChild, (unsigned) const, UIElement*), asCALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "UIElement@+ get_children(uint) const", asMETHODPR(DropDownList, GetChild, (unsigned) const, UIElement*), asCALL_THISCALL);
    // UIElement* UIElement::GetChild(const String& name, bool recursive=false) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "UIElement@+ GetChild(const String&in, bool = false) const", asMETHODPR(DropDownList, GetChild, (const String&, bool) const, UIElement*), asCALL_THISCALL);
    // UIElement* UIElement::GetChild(const StringHash& key, const Variant& value=Variant::EMPTY, bool recursive=false) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "UIElement@+ GetChild(const StringHash&in, const Variant&in = Variant::EMPTY, bool = false) const", asMETHODPR(DropDownList, GetChild, (const StringHash&, const Variant&, bool) const, UIElement*), asCALL_THISCALL);
    // template<class T> T* UIElement::GetChildDynamicCast(unsigned index) const | File: ../UI/UIElement.h
    // Not registered because template
    // template<class T> T* UIElement::GetChildDynamicCast(const String& name, bool recursive=false) const | File: ../UI/UIElement.h
    // Not registered because template
    // template<class T> T* UIElement::GetChildDynamicCast(const StringHash& key, const Variant& value=Variant::EMPTY, bool recursive=false) const | File: ../UI/UIElement.h
    // Not registered because template
    // const IntVector2& UIElement::GetChildOffset() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "const IntVector2& GetChildOffset() const", asMETHODPR(DropDownList, GetChildOffset, () const, const IntVector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "const IntVector2& get_childOffset() const", asMETHODPR(DropDownList, GetChildOffset, () const, const IntVector2&), asCALL_THISCALL);
    // const Vector<SharedPtr<UIElement>>& UIElement::GetChildren() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "Array<UIElement@>@ GetChildren() const", asFUNCTION(DropDownList_GetChildren_void), asCALL_CDECL_OBJFIRST);
    // void UIElement::GetChildren(PODVector<UIElement*>& dest, bool recursive=false) const | File: ../UI/UIElement.h
    // Error: type "PODVector<UIElement*>&" can not automatically bind
    // PODVector<UIElement*> UIElement::GetChildren(bool recursive) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "Array<UIElement@>@ GetChildren(bool) const", asFUNCTION(DropDownList_GetChildren_bool), asCALL_CDECL_OBJFIRST);
    // void UIElement::GetChildrenWithTag(PODVector<UIElement*>& dest, const String& tag, bool recursive=false) const | File: ../UI/UIElement.h
    // Error: type "PODVector<UIElement*>&" can not automatically bind
    // PODVector<UIElement*> UIElement::GetChildrenWithTag(const String& tag, bool recursive=false) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "Array<UIElement@>@ GetChildrenWithTag(const String&in, bool = false) const", asFUNCTION(DropDownList_GetChildrenWithTag_String_bool), asCALL_CDECL_OBJFIRST);
    // template<class T> T* UIElement::GetChildStaticCast(unsigned index) const | File: ../UI/UIElement.h
    // Not registered because template
    // template<class T> T* UIElement::GetChildStaticCast(const String& name, bool recursive=false) const | File: ../UI/UIElement.h
    // Not registered because template
    // template<class T> T* UIElement::GetChildStaticCast(const StringHash& key, const Variant& value=Variant::EMPTY, bool recursive=false) const | File: ../UI/UIElement.h
    // Not registered because template
    // const IntRect& UIElement::GetClipBorder() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "const IntRect& GetClipBorder() const", asMETHODPR(DropDownList, GetClipBorder, () const, const IntRect&), asCALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "const IntRect& get_clipBorder() const", asMETHODPR(DropDownList, GetClipBorder, () const, const IntRect&), asCALL_THISCALL);
    // bool UIElement::GetClipChildren() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "bool GetClipChildren() const", asMETHODPR(DropDownList, GetClipChildren, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "bool get_clipChildren() const", asMETHODPR(DropDownList, GetClipChildren, () const, bool), asCALL_THISCALL);
    // const Color& UIElement::GetColor(Corner corner) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "const Color& GetColor(Corner) const", asMETHODPR(DropDownList, GetColor, (Corner) const, const Color&), asCALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "const Color& get_colors(Corner) const", asMETHODPR(DropDownList, GetColor, (Corner) const, const Color&), asCALL_THISCALL);
    // const Color& UIElement::GetColorAttr() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "const Color& GetColorAttr() const", asMETHODPR(DropDownList, GetColorAttr, () const, const Color&), asCALL_THISCALL);
    // IntRect UIElement::GetCombinedScreenRect() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "IntRect GetCombinedScreenRect()", asMETHODPR(DropDownList, GetCombinedScreenRect, (), IntRect), asCALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "IntRect get_combinedScreenRect()", asMETHODPR(DropDownList, GetCombinedScreenRect, (), IntRect), asCALL_THISCALL);
    // Context* Object::GetContext() const | File: ../Core/Object.h
    // Error: type "Context*" can used only as function parameter
    // virtual void UIElement::GetDebugDrawBatches(PODVector<UIBatch>& batches, PODVector<float>& vertexData, const IntRect& currentScissor) | File: ../UI/UIElement.h
    // Error: type "PODVector<UIBatch>&" can not automatically bind
    // XMLFile* UIElement::GetDefaultStyle(bool recursiveUp=true) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "XMLFile@+ GetDefaultStyle(bool = true) const", asMETHODPR(DropDownList, GetDefaultStyle, (bool) const, XMLFile*), asCALL_THISCALL);
    // const Color& UIElement::GetDerivedColor() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "const Color& GetDerivedColor() const", asMETHODPR(DropDownList, GetDerivedColor, () const, const Color&), asCALL_THISCALL);
    // float UIElement::GetDerivedOpacity() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "float GetDerivedOpacity() const", asMETHODPR(DropDownList, GetDerivedOpacity, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "float get_derivedOpacity() const", asMETHODPR(DropDownList, GetDerivedOpacity, () const, float), asCALL_THISCALL);
    // const IntVector2& BorderImage::GetDisabledOffset() const | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("DropDownList", "const IntVector2& GetDisabledOffset() const", asMETHODPR(DropDownList, GetDisabledOffset, () const, const IntVector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "const IntVector2& get_disabledOffset() const", asMETHODPR(DropDownList, GetDisabledOffset, () const, const IntVector2&), asCALL_THISCALL);
    // MouseButtonFlags UIElement::GetDragButtonCombo() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "MouseButtonFlags GetDragButtonCombo() const", asMETHODPR(DropDownList, GetDragButtonCombo, () const, MouseButtonFlags), asCALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "MouseButtonFlags get_dragButtonCombo() const", asMETHODPR(DropDownList, GetDragButtonCombo, () const, MouseButtonFlags), asCALL_THISCALL);
    // unsigned UIElement::GetDragButtonCount() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "uint GetDragButtonCount() const", asMETHODPR(DropDownList, GetDragButtonCount, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "uint get_dragButtonCount() const", asMETHODPR(DropDownList, GetDragButtonCount, () const, unsigned), asCALL_THISCALL);
    // DragAndDropModeFlags UIElement::GetDragDropMode() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "DragAndDropModeFlags GetDragDropMode() const", asMETHODPR(DropDownList, GetDragDropMode, () const, DragAndDropModeFlags), asCALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "DragAndDropModeFlags get_dragDropMode() const", asMETHODPR(DropDownList, GetDragDropMode, () const, DragAndDropModeFlags), asCALL_THISCALL);
    // IntVector2 UIElement::GetEffectiveMinSize() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "IntVector2 GetEffectiveMinSize() const", asMETHODPR(DropDownList, GetEffectiveMinSize, () const, IntVector2), asCALL_THISCALL);
    // UIElement* UIElement::GetElementEventSender() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "UIElement@+ GetElementEventSender() const", asMETHODPR(DropDownList, GetElementEventSender, () const, UIElement*), asCALL_THISCALL);
    // bool UIElement::GetEnableAnchor() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "bool GetEnableAnchor() const", asMETHODPR(DropDownList, GetEnableAnchor, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "bool get_enableAnchor() const", asMETHODPR(DropDownList, GetEnableAnchor, () const, bool), asCALL_THISCALL);
    // VariantMap& Object::GetEventDataMap() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("DropDownList", "VariantMap& GetEventDataMap() const", asMETHODPR(DropDownList, GetEventDataMap, () const, VariantMap&), asCALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("DropDownList", "Object@+ GetEventSender() const", asMETHODPR(DropDownList, GetEventSender, () const, Object*), asCALL_THISCALL);
    // FocusMode UIElement::GetFocusMode() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "FocusMode GetFocusMode() const", asMETHODPR(DropDownList, GetFocusMode, () const, FocusMode), asCALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "FocusMode get_focusMode() const", asMETHODPR(DropDownList, GetFocusMode, () const, FocusMode), asCALL_THISCALL);
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("DropDownList", "const Variant& GetGlobalVar(StringHash) const", asMETHODPR(DropDownList, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "const Variant& get_globalVar(StringHash) const", asMETHODPR(DropDownList, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("DropDownList", "const VariantMap& GetGlobalVars() const", asMETHODPR(DropDownList, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "const VariantMap& get_globalVars() const", asMETHODPR(DropDownList, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    // int UIElement::GetHeight() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "int GetHeight() const", asMETHODPR(DropDownList, GetHeight, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "int get_height() const", asMETHODPR(DropDownList, GetHeight, () const, int), asCALL_THISCALL);
    // HorizontalAlignment UIElement::GetHorizontalAlignment() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "HorizontalAlignment GetHorizontalAlignment() const", asMETHODPR(DropDownList, GetHorizontalAlignment, () const, HorizontalAlignment), asCALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "HorizontalAlignment get_horizontalAlignment() const", asMETHODPR(DropDownList, GetHorizontalAlignment, () const, HorizontalAlignment), asCALL_THISCALL);
    // const IntVector2& BorderImage::GetHoverOffset() const | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("DropDownList", "const IntVector2& GetHoverOffset() const", asMETHODPR(DropDownList, GetHoverOffset, () const, const IntVector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "const IntVector2& get_hoverOffset() const", asMETHODPR(DropDownList, GetHoverOffset, () const, const IntVector2&), asCALL_THISCALL);
    // const IntRect& BorderImage::GetImageBorder() const | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("DropDownList", "const IntRect& GetImageBorder() const", asMETHODPR(DropDownList, GetImageBorder, () const, const IntRect&), asCALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "const IntRect& get_imageBorder() const", asMETHODPR(DropDownList, GetImageBorder, () const, const IntRect&), asCALL_THISCALL);
    // const IntRect& BorderImage::GetImageRect() const | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("DropDownList", "const IntRect& GetImageRect() const", asMETHODPR(DropDownList, GetImageRect, () const, const IntRect&), asCALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "const IntRect& get_imageRect() const", asMETHODPR(DropDownList, GetImageRect, () const, const IntRect&), asCALL_THISCALL);
    // int UIElement::GetIndent() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "int GetIndent() const", asMETHODPR(DropDownList, GetIndent, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "int get_indent() const", asMETHODPR(DropDownList, GetIndent, () const, int), asCALL_THISCALL);
    // int UIElement::GetIndentSpacing() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "int GetIndentSpacing() const", asMETHODPR(DropDownList, GetIndentSpacing, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "int get_indentSpacing() const", asMETHODPR(DropDownList, GetIndentSpacing, () const, int), asCALL_THISCALL);
    // int UIElement::GetIndentWidth() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "int GetIndentWidth() const", asMETHODPR(DropDownList, GetIndentWidth, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "int get_indentWidth() const", asMETHODPR(DropDownList, GetIndentWidth, () const, int), asCALL_THISCALL);
    // bool Serializable::GetInterceptNetworkUpdate(const String& attributeName) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("DropDownList", "bool GetInterceptNetworkUpdate(const String&in) const", asMETHODPR(DropDownList, GetInterceptNetworkUpdate, (const String&) const, bool), asCALL_THISCALL);
    // UIElement* DropDownList::GetItem(unsigned index) const | File: ../UI/DropDownList.h
    engine->RegisterObjectMethod("DropDownList", "UIElement@+ GetItem(uint) const", asMETHODPR(DropDownList, GetItem, (unsigned) const, UIElement*), asCALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "UIElement@+ get_items(uint) const", asMETHODPR(DropDownList, GetItem, (unsigned) const, UIElement*), asCALL_THISCALL);
    // PODVector<UIElement*> DropDownList::GetItems() const | File: ../UI/DropDownList.h
    engine->RegisterObjectMethod("DropDownList", "Array<UIElement@>@ GetItems() const", asFUNCTION(DropDownList_GetItems_void), asCALL_CDECL_OBJFIRST);
    // const IntRect& UIElement::GetLayoutBorder() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "const IntRect& GetLayoutBorder() const", asMETHODPR(DropDownList, GetLayoutBorder, () const, const IntRect&), asCALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "const IntRect& get_layoutBorder() const", asMETHODPR(DropDownList, GetLayoutBorder, () const, const IntRect&), asCALL_THISCALL);
    // int UIElement::GetLayoutElementMaxSize() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "int GetLayoutElementMaxSize() const", asMETHODPR(DropDownList, GetLayoutElementMaxSize, () const, int), asCALL_THISCALL);
    // const Vector2& UIElement::GetLayoutFlexScale() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "const Vector2& GetLayoutFlexScale() const", asMETHODPR(DropDownList, GetLayoutFlexScale, () const, const Vector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "const Vector2& get_layoutFlexScale() const", asMETHODPR(DropDownList, GetLayoutFlexScale, () const, const Vector2&), asCALL_THISCALL);
    // LayoutMode UIElement::GetLayoutMode() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "LayoutMode GetLayoutMode() const", asMETHODPR(DropDownList, GetLayoutMode, () const, LayoutMode), asCALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "LayoutMode get_layoutMode() const", asMETHODPR(DropDownList, GetLayoutMode, () const, LayoutMode), asCALL_THISCALL);
    // int UIElement::GetLayoutSpacing() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "int GetLayoutSpacing() const", asMETHODPR(DropDownList, GetLayoutSpacing, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "int get_layoutSpacing() const", asMETHODPR(DropDownList, GetLayoutSpacing, () const, int), asCALL_THISCALL);
    // ListView* DropDownList::GetListView() const | File: ../UI/DropDownList.h
    engine->RegisterObjectMethod("DropDownList", "ListView@+ GetListView() const", asMETHODPR(DropDownList, GetListView, () const, ListView*), asCALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "ListView@+ get_listView() const", asMETHODPR(DropDownList, GetListView, () const, ListView*), asCALL_THISCALL);
    // Material* BorderImage::GetMaterial() const | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("DropDownList", "Material@+ GetMaterial() const", asMETHODPR(DropDownList, GetMaterial, () const, Material*), asCALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "Material@+ get_material() const", asMETHODPR(DropDownList, GetMaterial, () const, Material*), asCALL_THISCALL);
    // ResourceRef BorderImage::GetMaterialAttr() const | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("DropDownList", "ResourceRef GetMaterialAttr() const", asMETHODPR(DropDownList, GetMaterialAttr, () const, ResourceRef), asCALL_THISCALL);
    // const Vector2& UIElement::GetMaxAnchor() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "const Vector2& GetMaxAnchor() const", asMETHODPR(DropDownList, GetMaxAnchor, () const, const Vector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "const Vector2& get_maxAnchor() const", asMETHODPR(DropDownList, GetMaxAnchor, () const, const Vector2&), asCALL_THISCALL);
    // int UIElement::GetMaxHeight() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "int GetMaxHeight() const", asMETHODPR(DropDownList, GetMaxHeight, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "int get_maxHeight() const", asMETHODPR(DropDownList, GetMaxHeight, () const, int), asCALL_THISCALL);
    // const IntVector2& UIElement::GetMaxOffset() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "const IntVector2& GetMaxOffset() const", asMETHODPR(DropDownList, GetMaxOffset, () const, const IntVector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "const IntVector2& get_maxOffset() const", asMETHODPR(DropDownList, GetMaxOffset, () const, const IntVector2&), asCALL_THISCALL);
    // const IntVector2& UIElement::GetMaxSize() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "const IntVector2& GetMaxSize() const", asMETHODPR(DropDownList, GetMaxSize, () const, const IntVector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "const IntVector2& get_maxSize() const", asMETHODPR(DropDownList, GetMaxSize, () const, const IntVector2&), asCALL_THISCALL);
    // int UIElement::GetMaxWidth() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "int GetMaxWidth() const", asMETHODPR(DropDownList, GetMaxWidth, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "int get_maxWidth() const", asMETHODPR(DropDownList, GetMaxWidth, () const, int), asCALL_THISCALL);
    // const Vector2& UIElement::GetMinAnchor() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "const Vector2& GetMinAnchor() const", asMETHODPR(DropDownList, GetMinAnchor, () const, const Vector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "const Vector2& get_minAnchor() const", asMETHODPR(DropDownList, GetMinAnchor, () const, const Vector2&), asCALL_THISCALL);
    // int UIElement::GetMinHeight() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "int GetMinHeight() const", asMETHODPR(DropDownList, GetMinHeight, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "int get_minHeight() const", asMETHODPR(DropDownList, GetMinHeight, () const, int), asCALL_THISCALL);
    // const IntVector2& UIElement::GetMinOffset() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "const IntVector2& GetMinOffset() const", asMETHODPR(DropDownList, GetMinOffset, () const, const IntVector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "const IntVector2& get_minOffset() const", asMETHODPR(DropDownList, GetMinOffset, () const, const IntVector2&), asCALL_THISCALL);
    // const IntVector2& UIElement::GetMinSize() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "const IntVector2& GetMinSize() const", asMETHODPR(DropDownList, GetMinSize, () const, const IntVector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "const IntVector2& get_minSize() const", asMETHODPR(DropDownList, GetMinSize, () const, const IntVector2&), asCALL_THISCALL);
    // int UIElement::GetMinWidth() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "int GetMinWidth() const", asMETHODPR(DropDownList, GetMinWidth, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "int get_minWidth() const", asMETHODPR(DropDownList, GetMinWidth, () const, int), asCALL_THISCALL);
    // const String& UIElement::GetName() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "const String& GetName() const", asMETHODPR(DropDownList, GetName, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "const String& get_name() const", asMETHODPR(DropDownList, GetName, () const, const String&), asCALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetNetworkAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // NetworkState* Serializable::GetNetworkState() const | File: ../Scene/Serializable.h
    // Error: type "NetworkState*" can not automatically bind
    // unsigned Serializable::GetNumAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("DropDownList", "uint GetNumAttributes() const", asMETHODPR(DropDownList, GetNumAttributes, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "uint get_numAttributes() const", asMETHODPR(DropDownList, GetNumAttributes, () const, unsigned), asCALL_THISCALL);
    // unsigned UIElement::GetNumChildren(bool recursive=false) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "uint GetNumChildren(bool = false) const", asMETHODPR(DropDownList, GetNumChildren, (bool) const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "uint get_numChildren(bool = false) const", asMETHODPR(DropDownList, GetNumChildren, (bool) const, unsigned), asCALL_THISCALL);
    // unsigned DropDownList::GetNumItems() const | File: ../UI/DropDownList.h
    engine->RegisterObjectMethod("DropDownList", "uint GetNumItems() const", asMETHODPR(DropDownList, GetNumItems, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "uint get_numItems() const", asMETHODPR(DropDownList, GetNumItems, () const, unsigned), asCALL_THISCALL);
    // unsigned Serializable::GetNumNetworkAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("DropDownList", "uint GetNumNetworkAttributes() const", asMETHODPR(DropDownList, GetNumNetworkAttributes, () const, unsigned), asCALL_THISCALL);
    // ObjectAnimation* Animatable::GetObjectAnimation() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("DropDownList", "ObjectAnimation@+ GetObjectAnimation() const", asMETHODPR(DropDownList, GetObjectAnimation, () const, ObjectAnimation*), asCALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "ObjectAnimation@+ get_objectAnimation() const", asMETHODPR(DropDownList, GetObjectAnimation, () const, ObjectAnimation*), asCALL_THISCALL);
    // ResourceRef Animatable::GetObjectAnimationAttr() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("DropDownList", "ResourceRef GetObjectAnimationAttr() const", asMETHODPR(DropDownList, GetObjectAnimationAttr, () const, ResourceRef), asCALL_THISCALL);
    // float UIElement::GetOpacity() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "float GetOpacity() const", asMETHODPR(DropDownList, GetOpacity, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "float get_opacity() const", asMETHODPR(DropDownList, GetOpacity, () const, float), asCALL_THISCALL);
    // UIElement* UIElement::GetParent() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "UIElement@+ GetParent() const", asMETHODPR(DropDownList, GetParent, () const, UIElement*), asCALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "UIElement@+ get_parent() const", asMETHODPR(DropDownList, GetParent, () const, UIElement*), asCALL_THISCALL);
    // const Vector2& UIElement::GetPivot() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "const Vector2& GetPivot() const", asMETHODPR(DropDownList, GetPivot, () const, const Vector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "const Vector2& get_pivot() const", asMETHODPR(DropDownList, GetPivot, () const, const Vector2&), asCALL_THISCALL);
    // UIElement* DropDownList::GetPlaceholder() const | File: ../UI/DropDownList.h
    engine->RegisterObjectMethod("DropDownList", "UIElement@+ GetPlaceholder() const", asMETHODPR(DropDownList, GetPlaceholder, () const, UIElement*), asCALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "UIElement@+ get_placeholder() const", asMETHODPR(DropDownList, GetPlaceholder, () const, UIElement*), asCALL_THISCALL);
    // const String& DropDownList::GetPlaceholderText() const | File: ../UI/DropDownList.h
    engine->RegisterObjectMethod("DropDownList", "const String& GetPlaceholderText() const", asMETHODPR(DropDownList, GetPlaceholderText, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "const String& get_placeholderText() const", asMETHODPR(DropDownList, GetPlaceholderText, () const, const String&), asCALL_THISCALL);
    // UIElement* Menu::GetPopup() const | File: ../UI/Menu.h
    engine->RegisterObjectMethod("DropDownList", "UIElement@+ GetPopup() const", asMETHODPR(DropDownList, GetPopup, () const, UIElement*), asCALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "UIElement@+ get_popup() const", asMETHODPR(DropDownList, GetPopup, () const, UIElement*), asCALL_THISCALL);
    // const IntVector2& Menu::GetPopupOffset() const | File: ../UI/Menu.h
    engine->RegisterObjectMethod("DropDownList", "const IntVector2& GetPopupOffset() const", asMETHODPR(DropDownList, GetPopupOffset, () const, const IntVector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "const IntVector2& get_popupOffset() const", asMETHODPR(DropDownList, GetPopupOffset, () const, const IntVector2&), asCALL_THISCALL);
    // const IntVector2& UIElement::GetPosition() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "const IntVector2& GetPosition() const", asMETHODPR(DropDownList, GetPosition, () const, const IntVector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "const IntVector2& get_position() const", asMETHODPR(DropDownList, GetPosition, () const, const IntVector2&), asCALL_THISCALL);
    // const IntVector2& Button::GetPressedChildOffset() const | File: ../UI/Button.h
    engine->RegisterObjectMethod("DropDownList", "const IntVector2& GetPressedChildOffset() const", asMETHODPR(DropDownList, GetPressedChildOffset, () const, const IntVector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "const IntVector2& get_pressedChildOffset() const", asMETHODPR(DropDownList, GetPressedChildOffset, () const, const IntVector2&), asCALL_THISCALL);
    // const IntVector2& Button::GetPressedOffset() const | File: ../UI/Button.h
    engine->RegisterObjectMethod("DropDownList", "const IntVector2& GetPressedOffset() const", asMETHODPR(DropDownList, GetPressedOffset, () const, const IntVector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "const IntVector2& get_pressedOffset() const", asMETHODPR(DropDownList, GetPressedOffset, () const, const IntVector2&), asCALL_THISCALL);
    // int UIElement::GetPriority() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "int GetPriority() const", asMETHODPR(DropDownList, GetPriority, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "int get_priority() const", asMETHODPR(DropDownList, GetPriority, () const, int), asCALL_THISCALL);
    // float Button::GetRepeatDelay() const | File: ../UI/Button.h
    engine->RegisterObjectMethod("DropDownList", "float GetRepeatDelay() const", asMETHODPR(DropDownList, GetRepeatDelay, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "float get_repeatDelay() const", asMETHODPR(DropDownList, GetRepeatDelay, () const, float), asCALL_THISCALL);
    // float Button::GetRepeatRate() const | File: ../UI/Button.h
    engine->RegisterObjectMethod("DropDownList", "float GetRepeatRate() const", asMETHODPR(DropDownList, GetRepeatRate, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "float get_repeatRate() const", asMETHODPR(DropDownList, GetRepeatRate, () const, float), asCALL_THISCALL);
    // bool DropDownList::GetResizePopup() const | File: ../UI/DropDownList.h
    engine->RegisterObjectMethod("DropDownList", "bool GetResizePopup() const", asMETHODPR(DropDownList, GetResizePopup, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "bool get_resizePopup() const", asMETHODPR(DropDownList, GetResizePopup, () const, bool), asCALL_THISCALL);
    // UIElement* UIElement::GetRoot() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "UIElement@+ GetRoot() const", asMETHODPR(DropDownList, GetRoot, () const, UIElement*), asCALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "UIElement@+ get_root() const", asMETHODPR(DropDownList, GetRoot, () const, UIElement*), asCALL_THISCALL);
    // virtual const IntVector2& UIElement::GetScreenPosition() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "const IntVector2& GetScreenPosition() const", asMETHODPR(DropDownList, GetScreenPosition, () const, const IntVector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "const IntVector2& get_screenPosition() const", asMETHODPR(DropDownList, GetScreenPosition, () const, const IntVector2&), asCALL_THISCALL);
    // UIElement* DropDownList::GetSelectedItem() const | File: ../UI/DropDownList.h
    engine->RegisterObjectMethod("DropDownList", "UIElement@+ GetSelectedItem() const", asMETHODPR(DropDownList, GetSelectedItem, () const, UIElement*), asCALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "UIElement@+ get_selectedItem() const", asMETHODPR(DropDownList, GetSelectedItem, () const, UIElement*), asCALL_THISCALL);
    // unsigned DropDownList::GetSelection() const | File: ../UI/DropDownList.h
    engine->RegisterObjectMethod("DropDownList", "uint GetSelection() const", asMETHODPR(DropDownList, GetSelection, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "uint get_selection() const", asMETHODPR(DropDownList, GetSelection, () const, unsigned), asCALL_THISCALL);
    // bool Menu::GetShowPopup() const | File: ../UI/Menu.h
    engine->RegisterObjectMethod("DropDownList", "bool GetShowPopup() const", asMETHODPR(DropDownList, GetShowPopup, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "bool get_showPopup() const", asMETHODPR(DropDownList, GetShowPopup, () const, bool), asCALL_THISCALL);
    // const IntVector2& UIElement::GetSize() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "const IntVector2& GetSize() const", asMETHODPR(DropDownList, GetSize, () const, const IntVector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "const IntVector2& get_size() const", asMETHODPR(DropDownList, GetSize, () const, const IntVector2&), asCALL_THISCALL);
    // bool UIElement::GetSortChildren() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "bool GetSortChildren() const", asMETHODPR(DropDownList, GetSortChildren, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "bool get_sortChildren() const", asMETHODPR(DropDownList, GetSortChildren, () const, bool), asCALL_THISCALL);
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("DropDownList", "Object@+ GetSubsystem(StringHash) const", asMETHODPR(DropDownList, GetSubsystem, (StringHash) const, Object*), asCALL_THISCALL);
    // template<class T> T* Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // const StringVector& UIElement::GetTags() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "Array<String>@ GetTags() const", asFUNCTION(DropDownList_GetTags_void), asCALL_CDECL_OBJFIRST);
    engine->RegisterObjectMethod("DropDownList", "Array<String>@ get_tags() const", asFUNCTION(DropDownList_GetTags_void), asCALL_CDECL_OBJFIRST);
    // Texture* BorderImage::GetTexture() const | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("DropDownList", "Texture@+ GetTexture() const", asMETHODPR(DropDownList, GetTexture, () const, Texture*), asCALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "Texture@+ get_texture() const", asMETHODPR(DropDownList, GetTexture, () const, Texture*), asCALL_THISCALL);
    // ResourceRef BorderImage::GetTextureAttr() const | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("DropDownList", "ResourceRef GetTextureAttr() const", asMETHODPR(DropDownList, GetTextureAttr, () const, ResourceRef), asCALL_THISCALL);
    // TraversalMode UIElement::GetTraversalMode() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "TraversalMode GetTraversalMode() const", asMETHODPR(DropDownList, GetTraversalMode, () const, TraversalMode), asCALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "TraversalMode get_traversalMode() const", asMETHODPR(DropDownList, GetTraversalMode, () const, TraversalMode), asCALL_THISCALL);
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("DropDownList", "StringHash GetType() const", asMETHODPR(DropDownList, GetType, () const, StringHash), asCALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "StringHash get_type() const", asMETHODPR(DropDownList, GetType, () const, StringHash), asCALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("DropDownList", "const String& GetTypeName() const", asMETHODPR(DropDownList, GetTypeName, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "const String& get_typeName() const", asMETHODPR(DropDownList, GetTypeName, () const, const String&), asCALL_THISCALL);
    // bool UIElement::GetUseDerivedOpacity() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "bool GetUseDerivedOpacity() const", asMETHODPR(DropDownList, GetUseDerivedOpacity, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "bool get_useDerivedOpacity() const", asMETHODPR(DropDownList, GetUseDerivedOpacity, () const, bool), asCALL_THISCALL);
    // const Variant& UIElement::GetVar(const StringHash& key) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "const Variant& GetVar(const StringHash&in) const", asMETHODPR(DropDownList, GetVar, (const StringHash&) const, const Variant&), asCALL_THISCALL);
    // const VariantMap& UIElement::GetVars() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "const VariantMap& GetVars() const", asMETHODPR(DropDownList, GetVars, () const, const VariantMap&), asCALL_THISCALL);
    // VerticalAlignment UIElement::GetVerticalAlignment() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "VerticalAlignment GetVerticalAlignment() const", asMETHODPR(DropDownList, GetVerticalAlignment, () const, VerticalAlignment), asCALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "VerticalAlignment get_verticalAlignment() const", asMETHODPR(DropDownList, GetVerticalAlignment, () const, VerticalAlignment), asCALL_THISCALL);
    // int UIElement::GetWidth() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "int GetWidth() const", asMETHODPR(DropDownList, GetWidth, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "int get_width() const", asMETHODPR(DropDownList, GetWidth, () const, int), asCALL_THISCALL);
    // bool UIElement::HasColorGradient() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "bool HasColorGradient() const", asMETHODPR(DropDownList, HasColorGradient, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "bool get_colorGradient() const", asMETHODPR(DropDownList, HasColorGradient, () const, bool), asCALL_THISCALL);
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("DropDownList", "bool HasEventHandlers() const", asMETHODPR(DropDownList, HasEventHandlers, () const, bool), asCALL_THISCALL);
    // bool UIElement::HasFocus() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "bool HasFocus() const", asMETHODPR(DropDownList, HasFocus, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "bool get_focus() const", asMETHODPR(DropDownList, HasFocus, () const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("DropDownList", "bool HasSubscribedToEvent(StringHash) const", asMETHODPR(DropDownList, HasSubscribedToEvent, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("DropDownList", "bool HasSubscribedToEvent(Object@+, StringHash) const", asMETHODPR(DropDownList, HasSubscribedToEvent, (Object*, StringHash) const, bool), asCALL_THISCALL);
    // bool UIElement::HasTag(const String& tag) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "bool HasTag(const String&in) const", asMETHODPR(DropDownList, HasTag, (const String&) const, bool), asCALL_THISCALL);
    // void UIElement::InsertChild(unsigned index, UIElement* element) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "void InsertChild(uint, UIElement@+)", asMETHODPR(DropDownList, InsertChild, (unsigned, UIElement*), void), asCALL_THISCALL);
    // void DropDownList::InsertItem(unsigned index, UIElement* item) | File: ../UI/DropDownList.h
    engine->RegisterObjectMethod("DropDownList", "void InsertItem(uint, UIElement@+)", asMETHODPR(DropDownList, InsertItem, (unsigned, UIElement*), void), asCALL_THISCALL);
    // bool UIElement::IsChildOf(UIElement* element) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "bool IsChildOf(UIElement@+) const", asMETHODPR(DropDownList, IsChildOf, (UIElement*) const, bool), asCALL_THISCALL);
    // bool UIElement::IsEditable() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "bool IsEditable() const", asMETHODPR(DropDownList, IsEditable, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "bool get_editable() const", asMETHODPR(DropDownList, IsEditable, () const, bool), asCALL_THISCALL);
    // bool UIElement::IsElementEventSender() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "bool IsElementEventSender() const", asMETHODPR(DropDownList, IsElementEventSender, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "bool get_elementEventSender() const", asMETHODPR(DropDownList, IsElementEventSender, () const, bool), asCALL_THISCALL);
    // bool UIElement::IsEnabled() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "bool IsEnabled() const", asMETHODPR(DropDownList, IsEnabled, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "bool get_enabled() const", asMETHODPR(DropDownList, IsEnabled, () const, bool), asCALL_THISCALL);
    // bool UIElement::IsEnabledSelf() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "bool IsEnabledSelf() const", asMETHODPR(DropDownList, IsEnabledSelf, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "bool get_enabledSelf() const", asMETHODPR(DropDownList, IsEnabledSelf, () const, bool), asCALL_THISCALL);
    // bool UIElement::IsFixedHeight() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "bool IsFixedHeight() const", asMETHODPR(DropDownList, IsFixedHeight, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "bool get_fixedHeight() const", asMETHODPR(DropDownList, IsFixedHeight, () const, bool), asCALL_THISCALL);
    // bool UIElement::IsFixedSize() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "bool IsFixedSize() const", asMETHODPR(DropDownList, IsFixedSize, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "bool get_fixedSize() const", asMETHODPR(DropDownList, IsFixedSize, () const, bool), asCALL_THISCALL);
    // bool UIElement::IsFixedWidth() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "bool IsFixedWidth() const", asMETHODPR(DropDownList, IsFixedWidth, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "bool get_fixedWidth() const", asMETHODPR(DropDownList, IsFixedWidth, () const, bool), asCALL_THISCALL);
    // bool UIElement::IsHovering() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "bool IsHovering() const", asMETHODPR(DropDownList, IsHovering, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "bool get_hovering() const", asMETHODPR(DropDownList, IsHovering, () const, bool), asCALL_THISCALL);
    // bool UIElement::IsInside(IntVector2 position, bool isScreen) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "bool IsInside(IntVector2, bool)", asMETHODPR(DropDownList, IsInside, (IntVector2, bool), bool), asCALL_THISCALL);
    // bool UIElement::IsInsideCombined(IntVector2 position, bool isScreen) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "bool IsInsideCombined(IntVector2, bool)", asMETHODPR(DropDownList, IsInsideCombined, (IntVector2, bool), bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("DropDownList", "bool IsInstanceOf(StringHash) const", asMETHODPR(DropDownList, IsInstanceOf, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // bool UIElement::IsInternal() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "bool IsInternal() const", asMETHODPR(DropDownList, IsInternal, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "bool get_internal() const", asMETHODPR(DropDownList, IsInternal, () const, bool), asCALL_THISCALL);
    // bool Button::IsPressed() const | File: ../UI/Button.h
    engine->RegisterObjectMethod("DropDownList", "bool IsPressed() const", asMETHODPR(DropDownList, IsPressed, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "bool get_pressed() const", asMETHODPR(DropDownList, IsPressed, () const, bool), asCALL_THISCALL);
    // bool UIElement::IsSelected() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "bool IsSelected() const", asMETHODPR(DropDownList, IsSelected, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "bool get_selected() const", asMETHODPR(DropDownList, IsSelected, () const, bool), asCALL_THISCALL);
    // bool Serializable::IsTemporary() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("DropDownList", "bool IsTemporary() const", asMETHODPR(DropDownList, IsTemporary, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "bool get_temporary() const", asMETHODPR(DropDownList, IsTemporary, () const, bool), asCALL_THISCALL);
    // bool BorderImage::IsTiled() const | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("DropDownList", "bool IsTiled() const", asMETHODPR(DropDownList, IsTiled, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "bool get_tiled() const", asMETHODPR(DropDownList, IsTiled, () const, bool), asCALL_THISCALL);
    // bool UIElement::IsVisible() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "bool IsVisible() const", asMETHODPR(DropDownList, IsVisible, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "bool get_visible() const", asMETHODPR(DropDownList, IsVisible, () const, bool), asCALL_THISCALL);
    // bool UIElement::IsVisibleEffective() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "bool IsVisibleEffective() const", asMETHODPR(DropDownList, IsVisibleEffective, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "bool get_visibleEffective() const", asMETHODPR(DropDownList, IsVisibleEffective, () const, bool), asCALL_THISCALL);
    // virtual bool UIElement::IsWheelHandler() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "bool IsWheelHandler() const", asMETHODPR(DropDownList, IsWheelHandler, () const, bool), asCALL_THISCALL);
    // virtual bool UIElement::IsWithinScissor(const IntRect& currentScissor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "bool IsWithinScissor(const IntRect&in)", asMETHODPR(DropDownList, IsWithinScissor, (const IntRect&), bool), asCALL_THISCALL);
    // virtual bool Serializable::Load(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("DropDownList", "bool Load(Deserializer&)", asMETHODPR(DropDownList, Load, (Deserializer&), bool), asCALL_THISCALL);
    // virtual UIElement* UIElement::LoadChildXML(const XMLElement& childElem, XMLFile* styleFile) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "UIElement@+ LoadChildXML(const XMLElement&in, XMLFile@+)", asMETHODPR(DropDownList, LoadChildXML, (const XMLElement&, XMLFile*), UIElement*), asCALL_THISCALL);
    // bool Animatable::LoadJSON(const JSONValue& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("DropDownList", "bool LoadJSON(const JSONValue&in)", asMETHODPR(DropDownList, LoadJSON, (const JSONValue&), bool), asCALL_THISCALL);
    // bool Menu::LoadXML(const XMLElement& source, XMLFile* styleFile) override | File: ../UI/Menu.h
    engine->RegisterObjectMethod("DropDownList", "bool LoadXML(const XMLElement&in, XMLFile@+)", asMETHODPR(DropDownList, LoadXML, (const XMLElement&, XMLFile*), bool), asCALL_THISCALL);
    // virtual void Serializable::MarkNetworkUpdate() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("DropDownList", "void MarkNetworkUpdate()", asMETHODPR(DropDownList, MarkNetworkUpdate, (), void), asCALL_THISCALL);
    // void Button::OnClickBegin(const IntVector2& position, const IntVector2& screenPosition, MouseButton button, MouseButtonFlags buttons, QualifierFlags qualifiers, Cursor* cursor) override | File: ../UI/Button.h
    engine->RegisterObjectMethod("DropDownList", "void OnClickBegin(const IntVector2&in, const IntVector2&in, MouseButton, MouseButtonFlags, QualifierFlags, Cursor@+)", asMETHODPR(DropDownList, OnClickBegin, (const IntVector2&, const IntVector2&, MouseButton, MouseButtonFlags, QualifierFlags, Cursor*), void), asCALL_THISCALL);
    // void Button::OnClickEnd(const IntVector2& position, const IntVector2& screenPosition, MouseButton button, MouseButtonFlags buttons, QualifierFlags qualifiers, Cursor* cursor, UIElement* beginElement) override | File: ../UI/Button.h
    engine->RegisterObjectMethod("DropDownList", "void OnClickEnd(const IntVector2&in, const IntVector2&in, MouseButton, MouseButtonFlags, QualifierFlags, Cursor@+, UIElement@+)", asMETHODPR(DropDownList, OnClickEnd, (const IntVector2&, const IntVector2&, MouseButton, MouseButtonFlags, QualifierFlags, Cursor*, UIElement*), void), asCALL_THISCALL);
    // virtual void UIElement::OnDoubleClick(const IntVector2& position, const IntVector2& screenPosition, MouseButton button, MouseButtonFlags buttons, QualifierFlags qualifiers, Cursor* cursor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "void OnDoubleClick(const IntVector2&in, const IntVector2&in, MouseButton, MouseButtonFlags, QualifierFlags, Cursor@+)", asMETHODPR(DropDownList, OnDoubleClick, (const IntVector2&, const IntVector2&, MouseButton, MouseButtonFlags, QualifierFlags, Cursor*), void), asCALL_THISCALL);
    // virtual void UIElement::OnDragBegin(const IntVector2& position, const IntVector2& screenPosition, MouseButtonFlags buttons, QualifierFlags qualifiers, Cursor* cursor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "void OnDragBegin(const IntVector2&in, const IntVector2&in, MouseButtonFlags, QualifierFlags, Cursor@+)", asMETHODPR(DropDownList, OnDragBegin, (const IntVector2&, const IntVector2&, MouseButtonFlags, QualifierFlags, Cursor*), void), asCALL_THISCALL);
    // virtual void UIElement::OnDragCancel(const IntVector2& position, const IntVector2& screenPosition, MouseButtonFlags dragButtons, MouseButtonFlags cancelButtons, Cursor* cursor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "void OnDragCancel(const IntVector2&in, const IntVector2&in, MouseButtonFlags, MouseButtonFlags, Cursor@+)", asMETHODPR(DropDownList, OnDragCancel, (const IntVector2&, const IntVector2&, MouseButtonFlags, MouseButtonFlags, Cursor*), void), asCALL_THISCALL);
    // virtual bool UIElement::OnDragDropFinish(UIElement* source) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "bool OnDragDropFinish(UIElement@+)", asMETHODPR(DropDownList, OnDragDropFinish, (UIElement*), bool), asCALL_THISCALL);
    // virtual bool UIElement::OnDragDropTest(UIElement* source) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "bool OnDragDropTest(UIElement@+)", asMETHODPR(DropDownList, OnDragDropTest, (UIElement*), bool), asCALL_THISCALL);
    // virtual void UIElement::OnDragEnd(const IntVector2& position, const IntVector2& screenPosition, MouseButtonFlags dragButtons, MouseButtonFlags releaseButtons, Cursor* cursor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "void OnDragEnd(const IntVector2&in, const IntVector2&in, MouseButtonFlags, MouseButtonFlags, Cursor@+)", asMETHODPR(DropDownList, OnDragEnd, (const IntVector2&, const IntVector2&, MouseButtonFlags, MouseButtonFlags, Cursor*), void), asCALL_THISCALL);
    // void Button::OnDragMove(const IntVector2& position, const IntVector2& screenPosition, const IntVector2& deltaPos, MouseButtonFlags buttons, QualifierFlags qualifiers, Cursor* cursor) override | File: ../UI/Button.h
    engine->RegisterObjectMethod("DropDownList", "void OnDragMove(const IntVector2&in, const IntVector2&in, const IntVector2&in, MouseButtonFlags, QualifierFlags, Cursor@+)", asMETHODPR(DropDownList, OnDragMove, (const IntVector2&, const IntVector2&, const IntVector2&, MouseButtonFlags, QualifierFlags, Cursor*), void), asCALL_THISCALL);
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("DropDownList", "void OnEvent(Object@+, StringHash, VariantMap&)", asMETHODPR(DropDownList, OnEvent, (Object*, StringHash, VariantMap&), void), asCALL_THISCALL);
    // virtual void Serializable::OnGetAttribute(const AttributeInfo& attr, Variant& dest) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("DropDownList", "void OnGetAttribute(const AttributeInfo&in, Variant&) const", asMETHODPR(DropDownList, OnGetAttribute, (const AttributeInfo&, Variant&) const, void), asCALL_THISCALL);
    // void DropDownList::OnHidePopup() override | File: ../UI/DropDownList.h
    engine->RegisterObjectMethod("DropDownList", "void OnHidePopup()", asMETHODPR(DropDownList, OnHidePopup, (), void), asCALL_THISCALL);
    // void Menu::OnHover(const IntVector2& position, const IntVector2& screenPosition, MouseButtonFlags buttons, QualifierFlags qualifiers, Cursor* cursor) override | File: ../UI/Menu.h
    engine->RegisterObjectMethod("DropDownList", "void OnHover(const IntVector2&in, const IntVector2&in, MouseButtonFlags, QualifierFlags, Cursor@+)", asMETHODPR(DropDownList, OnHover, (const IntVector2&, const IntVector2&, MouseButtonFlags, QualifierFlags, Cursor*), void), asCALL_THISCALL);
    // virtual void UIElement::OnIndentSet() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "void OnIndentSet()", asMETHODPR(DropDownList, OnIndentSet, (), void), asCALL_THISCALL);
    // void Button::OnKey(Key key, MouseButtonFlags buttons, QualifierFlags qualifiers) override | File: ../UI/Button.h
    engine->RegisterObjectMethod("DropDownList", "void OnKey(Key, MouseButtonFlags, QualifierFlags)", asMETHODPR(DropDownList, OnKey, (Key, MouseButtonFlags, QualifierFlags), void), asCALL_THISCALL);
    // virtual void UIElement::OnPositionSet(const IntVector2& newPosition) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "void OnPositionSet(const IntVector2&in)", asMETHODPR(DropDownList, OnPositionSet, (const IntVector2&), void), asCALL_THISCALL);
    // virtual void UIElement::OnResize(const IntVector2& newSize, const IntVector2& delta) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "void OnResize(const IntVector2&in, const IntVector2&in)", asMETHODPR(DropDownList, OnResize, (const IntVector2&, const IntVector2&), void), asCALL_THISCALL);
    // virtual void Serializable::OnSetAttribute(const AttributeInfo& attr, const Variant& src) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("DropDownList", "void OnSetAttribute(const AttributeInfo&in, const Variant&in)", asMETHODPR(DropDownList, OnSetAttribute, (const AttributeInfo&, const Variant&), void), asCALL_THISCALL);
    // void DropDownList::OnSetEditable() override | File: ../UI/DropDownList.h
    engine->RegisterObjectMethod("DropDownList", "void OnSetEditable()", asMETHODPR(DropDownList, OnSetEditable, (), void), asCALL_THISCALL);
    // void DropDownList::OnShowPopup() override | File: ../UI/DropDownList.h
    engine->RegisterObjectMethod("DropDownList", "void OnShowPopup()", asMETHODPR(DropDownList, OnShowPopup, (), void), asCALL_THISCALL);
    // virtual void UIElement::OnTextInput(const String& text) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "void OnTextInput(const String&in)", asMETHODPR(DropDownList, OnTextInput, (const String&), void), asCALL_THISCALL);
    // virtual void UIElement::OnWheel(int delta, MouseButtonFlags buttons, QualifierFlags qualifiers) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "void OnWheel(int, MouseButtonFlags, QualifierFlags)", asMETHODPR(DropDownList, OnWheel, (int, MouseButtonFlags, QualifierFlags), void), asCALL_THISCALL);
    // bool Serializable::ReadDeltaUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("DropDownList", "bool ReadDeltaUpdate(Deserializer&)", asMETHODPR(DropDownList, ReadDeltaUpdate, (Deserializer&), bool), asCALL_THISCALL);
    // bool Serializable::ReadLatestDataUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("DropDownList", "bool ReadLatestDataUpdate(Deserializer&)", asMETHODPR(DropDownList, ReadLatestDataUpdate, (Deserializer&), bool), asCALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("DropDownList", "int Refs() const", asMETHODPR(DropDownList, Refs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "int get_refs() const", asMETHODPR(DropDownList, Refs, () const, int), asCALL_THISCALL);
    // static void DropDownList::RegisterObject(Context* context) | File: ../UI/DropDownList.h
    // Not registered because have @nobind mark
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("DropDownList", asBEHAVE_RELEASE, "void f()", asMETHODPR(DropDownList, ReleaseRef, (), void), asCALL_THISCALL);
    // void UIElement::Remove() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "void Remove()", asMETHODPR(DropDownList, Remove, (), void), asCALL_THISCALL);
    // void UIElement::RemoveAllChildren() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "void RemoveAllChildren()", asMETHODPR(DropDownList, RemoveAllChildren, (), void), asCALL_THISCALL);
    // void DropDownList::RemoveAllItems() | File: ../UI/DropDownList.h
    engine->RegisterObjectMethod("DropDownList", "void RemoveAllItems()", asMETHODPR(DropDownList, RemoveAllItems, (), void), asCALL_THISCALL);
    // void UIElement::RemoveAllTags() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "void RemoveAllTags()", asMETHODPR(DropDownList, RemoveAllTags, (), void), asCALL_THISCALL);
    // void Animatable::RemoveAttributeAnimation(const String& name) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("DropDownList", "void RemoveAttributeAnimation(const String&in)", asMETHODPR(DropDownList, RemoveAttributeAnimation, (const String&), void), asCALL_THISCALL);
    // void UIElement::RemoveChild(UIElement* element, unsigned index=0) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "void RemoveChild(UIElement@+, uint = 0)", asMETHODPR(DropDownList, RemoveChild, (UIElement*, unsigned), void), asCALL_THISCALL);
    // void UIElement::RemoveChildAtIndex(unsigned index) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "void RemoveChildAtIndex(uint)", asMETHODPR(DropDownList, RemoveChildAtIndex, (unsigned), void), asCALL_THISCALL);
    // void Serializable::RemoveInstanceDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("DropDownList", "void RemoveInstanceDefault()", asMETHODPR(DropDownList, RemoveInstanceDefault, (), void), asCALL_THISCALL);
    // void DropDownList::RemoveItem(UIElement* item) | File: ../UI/DropDownList.h
    engine->RegisterObjectMethod("DropDownList", "void RemoveItem(UIElement@+)", asMETHODPR(DropDownList, RemoveItem, (UIElement*), void), asCALL_THISCALL);
    // void DropDownList::RemoveItem(unsigned index) | File: ../UI/DropDownList.h
    engine->RegisterObjectMethod("DropDownList", "void RemoveItem(uint)", asMETHODPR(DropDownList, RemoveItem, (unsigned), void), asCALL_THISCALL);
    // void Animatable::RemoveObjectAnimation() | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("DropDownList", "void RemoveObjectAnimation()", asMETHODPR(DropDownList, RemoveObjectAnimation, (), void), asCALL_THISCALL);
    // bool UIElement::RemoveTag(const String& tag) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "bool RemoveTag(const String&in)", asMETHODPR(DropDownList, RemoveTag, (const String&), bool), asCALL_THISCALL);
    // void UIElement::ResetDeepEnabled() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "void ResetDeepEnabled()", asMETHODPR(DropDownList, ResetDeepEnabled, (), void), asCALL_THISCALL);
    // void Serializable::ResetToDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("DropDownList", "void ResetToDefault()", asMETHODPR(DropDownList, ResetToDefault, (), void), asCALL_THISCALL);
    // virtual bool Serializable::Save(Serializer& dest) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("DropDownList", "bool Save(Serializer&) const", asMETHODPR(DropDownList, Save, (Serializer&) const, bool), asCALL_THISCALL);
    // virtual bool Serializable::SaveDefaultAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("DropDownList", "bool SaveDefaultAttributes() const", asMETHODPR(DropDownList, SaveDefaultAttributes, () const, bool), asCALL_THISCALL);
    // bool Animatable::SaveJSON(JSONValue& dest) const override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("DropDownList", "bool SaveJSON(JSONValue&) const", asMETHODPR(DropDownList, SaveJSON, (JSONValue&) const, bool), asCALL_THISCALL);
    // bool Menu::SaveXML(XMLElement& dest) const override | File: ../UI/Menu.h
    engine->RegisterObjectMethod("DropDownList", "bool SaveXML(XMLElement&) const", asMETHODPR(DropDownList, SaveXML, (XMLElement&) const, bool), asCALL_THISCALL);
    // virtual IntVector2 UIElement::ScreenToElement(const IntVector2& screenPosition) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "IntVector2 ScreenToElement(const IntVector2&in)", asMETHODPR(DropDownList, ScreenToElement, (const IntVector2&), IntVector2), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("DropDownList", "void SendEvent(StringHash)", asMETHODPR(DropDownList, SendEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("DropDownList", "void SendEvent(StringHash, VariantMap&)", asMETHODPR(DropDownList, SendEvent, (StringHash, VariantMap&), void), asCALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void Menu::SetAccelerator(int key, int qualifiers) | File: ../UI/Menu.h
    engine->RegisterObjectMethod("DropDownList", "void SetAccelerator(int, int)", asMETHODPR(DropDownList, SetAccelerator, (int, int), void), asCALL_THISCALL);
    // void UIElement::SetAlignment(HorizontalAlignment hAlign, VerticalAlignment vAlign) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "void SetAlignment(HorizontalAlignment, VerticalAlignment)", asMETHODPR(DropDownList, SetAlignment, (HorizontalAlignment, VerticalAlignment), void), asCALL_THISCALL);
    // void Animatable::SetAnimationEnabled(bool enable) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("DropDownList", "void SetAnimationEnabled(bool)", asMETHODPR(DropDownList, SetAnimationEnabled, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "void set_animationEnabled(bool)", asMETHODPR(DropDownList, SetAnimationEnabled, (bool), void), asCALL_THISCALL);
    // void Animatable::SetAnimationTime(float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("DropDownList", "void SetAnimationTime(float)", asMETHODPR(DropDownList, SetAnimationTime, (float), void), asCALL_THISCALL);
    // bool Serializable::SetAttribute(unsigned index, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("DropDownList", "bool SetAttribute(uint, const Variant&in)", asMETHODPR(DropDownList, SetAttribute, (unsigned, const Variant&), bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "bool set_attributes(uint, const Variant&in)", asMETHODPR(DropDownList, SetAttribute, (unsigned, const Variant&), bool), asCALL_THISCALL);
    // bool Serializable::SetAttribute(const String& name, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("DropDownList", "bool SetAttribute(const String&in, const Variant&in)", asMETHODPR(DropDownList, SetAttribute, (const String&, const Variant&), bool), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimation(const String& name, ValueAnimation* attributeAnimation, WrapMode wrapMode=WM_LOOP, float speed=1.0f) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("DropDownList", "void SetAttributeAnimation(const String&in, ValueAnimation@+, WrapMode = WM_LOOP, float = 1.0f)", asMETHODPR(DropDownList, SetAttributeAnimation, (const String&, ValueAnimation*, WrapMode, float), void), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimationSpeed(const String& name, float speed) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("DropDownList", "void SetAttributeAnimationSpeed(const String&in, float)", asMETHODPR(DropDownList, SetAttributeAnimationSpeed, (const String&, float), void), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimationTime(const String& name, float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("DropDownList", "void SetAttributeAnimationTime(const String&in, float)", asMETHODPR(DropDownList, SetAttributeAnimationTime, (const String&, float), void), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimationWrapMode(const String& name, WrapMode wrapMode) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("DropDownList", "void SetAttributeAnimationWrapMode(const String&in, WrapMode)", asMETHODPR(DropDownList, SetAttributeAnimationWrapMode, (const String&, WrapMode), void), asCALL_THISCALL);
    // void BorderImage::SetBlendMode(BlendMode mode) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("DropDownList", "void SetBlendMode(BlendMode)", asMETHODPR(DropDownList, SetBlendMode, (BlendMode), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "void set_blendMode(BlendMode)", asMETHODPR(DropDownList, SetBlendMode, (BlendMode), void), asCALL_THISCALL);
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("DropDownList", "void SetBlockEvents(bool)", asMETHODPR(DropDownList, SetBlockEvents, (bool), void), asCALL_THISCALL);
    // void BorderImage::SetBorder(const IntRect& rect) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("DropDownList", "void SetBorder(const IntRect&in)", asMETHODPR(DropDownList, SetBorder, (const IntRect&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "void set_border(const IntRect&in)", asMETHODPR(DropDownList, SetBorder, (const IntRect&), void), asCALL_THISCALL);
    // void UIElement::SetBringToBack(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "void SetBringToBack(bool)", asMETHODPR(DropDownList, SetBringToBack, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "void set_bringToBack(bool)", asMETHODPR(DropDownList, SetBringToBack, (bool), void), asCALL_THISCALL);
    // void UIElement::SetBringToFront(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "void SetBringToFront(bool)", asMETHODPR(DropDownList, SetBringToFront, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "void set_bringToFront(bool)", asMETHODPR(DropDownList, SetBringToFront, (bool), void), asCALL_THISCALL);
    // void UIElement::SetChildOffset(const IntVector2& offset) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "void SetChildOffset(const IntVector2&in)", asMETHODPR(DropDownList, SetChildOffset, (const IntVector2&), void), asCALL_THISCALL);
    // void UIElement::SetClipBorder(const IntRect& rect) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "void SetClipBorder(const IntRect&in)", asMETHODPR(DropDownList, SetClipBorder, (const IntRect&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "void set_clipBorder(const IntRect&in)", asMETHODPR(DropDownList, SetClipBorder, (const IntRect&), void), asCALL_THISCALL);
    // void UIElement::SetClipChildren(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "void SetClipChildren(bool)", asMETHODPR(DropDownList, SetClipChildren, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "void set_clipChildren(bool)", asMETHODPR(DropDownList, SetClipChildren, (bool), void), asCALL_THISCALL);
    // void UIElement::SetColor(const Color& color) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "void SetColor(const Color&in)", asMETHODPR(DropDownList, SetColor, (const Color&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "void set_color(const Color&in)", asMETHODPR(DropDownList, SetColor, (const Color&), void), asCALL_THISCALL);
    // void UIElement::SetColor(Corner corner, const Color& color) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "void SetColor(Corner, const Color&in)", asMETHODPR(DropDownList, SetColor, (Corner, const Color&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "void set_colors(Corner, const Color&in)", asMETHODPR(DropDownList, SetColor, (Corner, const Color&), void), asCALL_THISCALL);
    // void UIElement::SetDeepEnabled(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "void SetDeepEnabled(bool)", asMETHODPR(DropDownList, SetDeepEnabled, (bool), void), asCALL_THISCALL);
    // void UIElement::SetDefaultStyle(XMLFile* style) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "void SetDefaultStyle(XMLFile@+)", asMETHODPR(DropDownList, SetDefaultStyle, (XMLFile*), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "void set_defaultStyle(XMLFile@+)", asMETHODPR(DropDownList, SetDefaultStyle, (XMLFile*), void), asCALL_THISCALL);
    // void BorderImage::SetDisabledOffset(const IntVector2& offset) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("DropDownList", "void SetDisabledOffset(const IntVector2&in)", asMETHODPR(DropDownList, SetDisabledOffset, (const IntVector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "void set_disabledOffset(const IntVector2&in)", asMETHODPR(DropDownList, SetDisabledOffset, (const IntVector2&), void), asCALL_THISCALL);
    // void BorderImage::SetDisabledOffset(int x, int y) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("DropDownList", "void SetDisabledOffset(int, int)", asMETHODPR(DropDownList, SetDisabledOffset, (int, int), void), asCALL_THISCALL);
    // void UIElement::SetDragDropMode(DragAndDropModeFlags mode) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "void SetDragDropMode(DragAndDropModeFlags)", asMETHODPR(DropDownList, SetDragDropMode, (DragAndDropModeFlags), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "void set_dragDropMode(DragAndDropModeFlags)", asMETHODPR(DropDownList, SetDragDropMode, (DragAndDropModeFlags), void), asCALL_THISCALL);
    // void UIElement::SetEditable(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "void SetEditable(bool)", asMETHODPR(DropDownList, SetEditable, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "void set_editable(bool)", asMETHODPR(DropDownList, SetEditable, (bool), void), asCALL_THISCALL);
    // void UIElement::SetElementEventSender(bool flag) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "void SetElementEventSender(bool)", asMETHODPR(DropDownList, SetElementEventSender, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "void set_elementEventSender(bool)", asMETHODPR(DropDownList, SetElementEventSender, (bool), void), asCALL_THISCALL);
    // void UIElement::SetEnableAnchor(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "void SetEnableAnchor(bool)", asMETHODPR(DropDownList, SetEnableAnchor, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "void set_enableAnchor(bool)", asMETHODPR(DropDownList, SetEnableAnchor, (bool), void), asCALL_THISCALL);
    // void UIElement::SetEnabled(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "void SetEnabled(bool)", asMETHODPR(DropDownList, SetEnabled, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "void set_enabled(bool)", asMETHODPR(DropDownList, SetEnabled, (bool), void), asCALL_THISCALL);
    // void UIElement::SetEnabledRecursive(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "void SetEnabledRecursive(bool)", asMETHODPR(DropDownList, SetEnabledRecursive, (bool), void), asCALL_THISCALL);
    // void UIElement::SetFixedHeight(int height) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "void SetFixedHeight(int)", asMETHODPR(DropDownList, SetFixedHeight, (int), void), asCALL_THISCALL);
    // void UIElement::SetFixedSize(const IntVector2& size) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "void SetFixedSize(const IntVector2&in)", asMETHODPR(DropDownList, SetFixedSize, (const IntVector2&), void), asCALL_THISCALL);
    // void UIElement::SetFixedSize(int width, int height) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "void SetFixedSize(int, int)", asMETHODPR(DropDownList, SetFixedSize, (int, int), void), asCALL_THISCALL);
    // void UIElement::SetFixedWidth(int width) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "void SetFixedWidth(int)", asMETHODPR(DropDownList, SetFixedWidth, (int), void), asCALL_THISCALL);
    // void UIElement::SetFocus(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "void SetFocus(bool)", asMETHODPR(DropDownList, SetFocus, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "void set_focus(bool)", asMETHODPR(DropDownList, SetFocus, (bool), void), asCALL_THISCALL);
    // void UIElement::SetFocusMode(FocusMode mode) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "void SetFocusMode(FocusMode)", asMETHODPR(DropDownList, SetFocusMode, (FocusMode), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "void set_focusMode(FocusMode)", asMETHODPR(DropDownList, SetFocusMode, (FocusMode), void), asCALL_THISCALL);
    // void BorderImage::SetFullImageRect() | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("DropDownList", "void SetFullImageRect()", asMETHODPR(DropDownList, SetFullImageRect, (), void), asCALL_THISCALL);
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("DropDownList", "void SetGlobalVar(StringHash, const Variant&in)", asMETHODPR(DropDownList, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "void set_globalVar(StringHash, const Variant&in)", asMETHODPR(DropDownList, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    // void UIElement::SetHeight(int height) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "void SetHeight(int)", asMETHODPR(DropDownList, SetHeight, (int), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "void set_height(int)", asMETHODPR(DropDownList, SetHeight, (int), void), asCALL_THISCALL);
    // void UIElement::SetHorizontalAlignment(HorizontalAlignment align) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "void SetHorizontalAlignment(HorizontalAlignment)", asMETHODPR(DropDownList, SetHorizontalAlignment, (HorizontalAlignment), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "void set_horizontalAlignment(HorizontalAlignment)", asMETHODPR(DropDownList, SetHorizontalAlignment, (HorizontalAlignment), void), asCALL_THISCALL);
    // void UIElement::SetHovering(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "void SetHovering(bool)", asMETHODPR(DropDownList, SetHovering, (bool), void), asCALL_THISCALL);
    // void BorderImage::SetHoverOffset(const IntVector2& offset) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("DropDownList", "void SetHoverOffset(const IntVector2&in)", asMETHODPR(DropDownList, SetHoverOffset, (const IntVector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "void set_hoverOffset(const IntVector2&in)", asMETHODPR(DropDownList, SetHoverOffset, (const IntVector2&), void), asCALL_THISCALL);
    // void BorderImage::SetHoverOffset(int x, int y) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("DropDownList", "void SetHoverOffset(int, int)", asMETHODPR(DropDownList, SetHoverOffset, (int, int), void), asCALL_THISCALL);
    // void BorderImage::SetImageBorder(const IntRect& rect) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("DropDownList", "void SetImageBorder(const IntRect&in)", asMETHODPR(DropDownList, SetImageBorder, (const IntRect&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "void set_imageBorder(const IntRect&in)", asMETHODPR(DropDownList, SetImageBorder, (const IntRect&), void), asCALL_THISCALL);
    // void BorderImage::SetImageRect(const IntRect& rect) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("DropDownList", "void SetImageRect(const IntRect&in)", asMETHODPR(DropDownList, SetImageRect, (const IntRect&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "void set_imageRect(const IntRect&in)", asMETHODPR(DropDownList, SetImageRect, (const IntRect&), void), asCALL_THISCALL);
    // void UIElement::SetIndent(int indent) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "void SetIndent(int)", asMETHODPR(DropDownList, SetIndent, (int), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "void set_indent(int)", asMETHODPR(DropDownList, SetIndent, (int), void), asCALL_THISCALL);
    // void UIElement::SetIndentSpacing(int indentSpacing) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "void SetIndentSpacing(int)", asMETHODPR(DropDownList, SetIndentSpacing, (int), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "void set_indentSpacing(int)", asMETHODPR(DropDownList, SetIndentSpacing, (int), void), asCALL_THISCALL);
    // void Serializable::SetInstanceDefault(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("DropDownList", "void SetInstanceDefault(bool)", asMETHODPR(DropDownList, SetInstanceDefault, (bool), void), asCALL_THISCALL);
    // void Serializable::SetInterceptNetworkUpdate(const String& attributeName, bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("DropDownList", "void SetInterceptNetworkUpdate(const String&in, bool)", asMETHODPR(DropDownList, SetInterceptNetworkUpdate, (const String&, bool), void), asCALL_THISCALL);
    // void UIElement::SetInternal(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "void SetInternal(bool)", asMETHODPR(DropDownList, SetInternal, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "void set_internal(bool)", asMETHODPR(DropDownList, SetInternal, (bool), void), asCALL_THISCALL);
    // void UIElement::SetLayout(LayoutMode mode, int spacing=0, const IntRect& border=IntRect::ZERO) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "void SetLayout(LayoutMode, int = 0, const IntRect&in = IntRect::ZERO)", asMETHODPR(DropDownList, SetLayout, (LayoutMode, int, const IntRect&), void), asCALL_THISCALL);
    // void UIElement::SetLayoutBorder(const IntRect& border) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "void SetLayoutBorder(const IntRect&in)", asMETHODPR(DropDownList, SetLayoutBorder, (const IntRect&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "void set_layoutBorder(const IntRect&in)", asMETHODPR(DropDownList, SetLayoutBorder, (const IntRect&), void), asCALL_THISCALL);
    // void UIElement::SetLayoutFlexScale(const Vector2& scale) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "void SetLayoutFlexScale(const Vector2&in)", asMETHODPR(DropDownList, SetLayoutFlexScale, (const Vector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "void set_layoutFlexScale(const Vector2&in)", asMETHODPR(DropDownList, SetLayoutFlexScale, (const Vector2&), void), asCALL_THISCALL);
    // void UIElement::SetLayoutMode(LayoutMode mode) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "void SetLayoutMode(LayoutMode)", asMETHODPR(DropDownList, SetLayoutMode, (LayoutMode), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "void set_layoutMode(LayoutMode)", asMETHODPR(DropDownList, SetLayoutMode, (LayoutMode), void), asCALL_THISCALL);
    // void UIElement::SetLayoutSpacing(int spacing) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "void SetLayoutSpacing(int)", asMETHODPR(DropDownList, SetLayoutSpacing, (int), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "void set_layoutSpacing(int)", asMETHODPR(DropDownList, SetLayoutSpacing, (int), void), asCALL_THISCALL);
    // void BorderImage::SetMaterial(Material* material) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("DropDownList", "void SetMaterial(Material@+)", asMETHODPR(DropDownList, SetMaterial, (Material*), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "void set_material(Material@+)", asMETHODPR(DropDownList, SetMaterial, (Material*), void), asCALL_THISCALL);
    // void BorderImage::SetMaterialAttr(const ResourceRef& value) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("DropDownList", "void SetMaterialAttr(const ResourceRef&in)", asMETHODPR(DropDownList, SetMaterialAttr, (const ResourceRef&), void), asCALL_THISCALL);
    // void UIElement::SetMaxAnchor(const Vector2& anchor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "void SetMaxAnchor(const Vector2&in)", asMETHODPR(DropDownList, SetMaxAnchor, (const Vector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "void set_maxAnchor(const Vector2&in)", asMETHODPR(DropDownList, SetMaxAnchor, (const Vector2&), void), asCALL_THISCALL);
    // void UIElement::SetMaxAnchor(float x, float y) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "void SetMaxAnchor(float, float)", asMETHODPR(DropDownList, SetMaxAnchor, (float, float), void), asCALL_THISCALL);
    // void UIElement::SetMaxHeight(int height) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "void SetMaxHeight(int)", asMETHODPR(DropDownList, SetMaxHeight, (int), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "void set_maxHeight(int)", asMETHODPR(DropDownList, SetMaxHeight, (int), void), asCALL_THISCALL);
    // void UIElement::SetMaxOffset(const IntVector2& offset) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "void SetMaxOffset(const IntVector2&in)", asMETHODPR(DropDownList, SetMaxOffset, (const IntVector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "void set_maxOffset(const IntVector2&in)", asMETHODPR(DropDownList, SetMaxOffset, (const IntVector2&), void), asCALL_THISCALL);
    // void UIElement::SetMaxSize(const IntVector2& maxSize) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "void SetMaxSize(const IntVector2&in)", asMETHODPR(DropDownList, SetMaxSize, (const IntVector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "void set_maxSize(const IntVector2&in)", asMETHODPR(DropDownList, SetMaxSize, (const IntVector2&), void), asCALL_THISCALL);
    // void UIElement::SetMaxSize(int width, int height) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "void SetMaxSize(int, int)", asMETHODPR(DropDownList, SetMaxSize, (int, int), void), asCALL_THISCALL);
    // void UIElement::SetMaxWidth(int width) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "void SetMaxWidth(int)", asMETHODPR(DropDownList, SetMaxWidth, (int), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "void set_maxWidth(int)", asMETHODPR(DropDownList, SetMaxWidth, (int), void), asCALL_THISCALL);
    // void UIElement::SetMinAnchor(const Vector2& anchor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "void SetMinAnchor(const Vector2&in)", asMETHODPR(DropDownList, SetMinAnchor, (const Vector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "void set_minAnchor(const Vector2&in)", asMETHODPR(DropDownList, SetMinAnchor, (const Vector2&), void), asCALL_THISCALL);
    // void UIElement::SetMinAnchor(float x, float y) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "void SetMinAnchor(float, float)", asMETHODPR(DropDownList, SetMinAnchor, (float, float), void), asCALL_THISCALL);
    // void UIElement::SetMinHeight(int height) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "void SetMinHeight(int)", asMETHODPR(DropDownList, SetMinHeight, (int), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "void set_minHeight(int)", asMETHODPR(DropDownList, SetMinHeight, (int), void), asCALL_THISCALL);
    // void UIElement::SetMinOffset(const IntVector2& offset) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "void SetMinOffset(const IntVector2&in)", asMETHODPR(DropDownList, SetMinOffset, (const IntVector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "void set_minOffset(const IntVector2&in)", asMETHODPR(DropDownList, SetMinOffset, (const IntVector2&), void), asCALL_THISCALL);
    // void UIElement::SetMinSize(const IntVector2& minSize) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "void SetMinSize(const IntVector2&in)", asMETHODPR(DropDownList, SetMinSize, (const IntVector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "void set_minSize(const IntVector2&in)", asMETHODPR(DropDownList, SetMinSize, (const IntVector2&), void), asCALL_THISCALL);
    // void UIElement::SetMinSize(int width, int height) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "void SetMinSize(int, int)", asMETHODPR(DropDownList, SetMinSize, (int, int), void), asCALL_THISCALL);
    // void UIElement::SetMinWidth(int width) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "void SetMinWidth(int)", asMETHODPR(DropDownList, SetMinWidth, (int), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "void set_minWidth(int)", asMETHODPR(DropDownList, SetMinWidth, (int), void), asCALL_THISCALL);
    // void UIElement::SetName(const String& name) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "void SetName(const String&in)", asMETHODPR(DropDownList, SetName, (const String&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "void set_name(const String&in)", asMETHODPR(DropDownList, SetName, (const String&), void), asCALL_THISCALL);
    // void Animatable::SetObjectAnimation(ObjectAnimation* objectAnimation) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("DropDownList", "void SetObjectAnimation(ObjectAnimation@+)", asMETHODPR(DropDownList, SetObjectAnimation, (ObjectAnimation*), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "void set_objectAnimation(ObjectAnimation@+)", asMETHODPR(DropDownList, SetObjectAnimation, (ObjectAnimation*), void), asCALL_THISCALL);
    // void Animatable::SetObjectAnimationAttr(const ResourceRef& value) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("DropDownList", "void SetObjectAnimationAttr(const ResourceRef&in)", asMETHODPR(DropDownList, SetObjectAnimationAttr, (const ResourceRef&), void), asCALL_THISCALL);
    // void UIElement::SetOpacity(float opacity) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "void SetOpacity(float)", asMETHODPR(DropDownList, SetOpacity, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "void set_opacity(float)", asMETHODPR(DropDownList, SetOpacity, (float), void), asCALL_THISCALL);
    // void UIElement::SetParent(UIElement* parent, unsigned index=M_MAX_UNSIGNED) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "void SetParent(UIElement@+, uint = M_MAX_UNSIGNED)", asMETHODPR(DropDownList, SetParent, (UIElement*, unsigned), void), asCALL_THISCALL);
    // void UIElement::SetPivot(const Vector2& pivot) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "void SetPivot(const Vector2&in)", asMETHODPR(DropDownList, SetPivot, (const Vector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "void set_pivot(const Vector2&in)", asMETHODPR(DropDownList, SetPivot, (const Vector2&), void), asCALL_THISCALL);
    // void UIElement::SetPivot(float x, float y) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "void SetPivot(float, float)", asMETHODPR(DropDownList, SetPivot, (float, float), void), asCALL_THISCALL);
    // void DropDownList::SetPlaceholderText(const String& text) | File: ../UI/DropDownList.h
    engine->RegisterObjectMethod("DropDownList", "void SetPlaceholderText(const String&in)", asMETHODPR(DropDownList, SetPlaceholderText, (const String&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "void set_placeholderText(const String&in)", asMETHODPR(DropDownList, SetPlaceholderText, (const String&), void), asCALL_THISCALL);
    // void Menu::SetPopup(UIElement* popup) | File: ../UI/Menu.h
    engine->RegisterObjectMethod("DropDownList", "void SetPopup(UIElement@+)", asMETHODPR(DropDownList, SetPopup, (UIElement*), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "void set_popup(UIElement@+)", asMETHODPR(DropDownList, SetPopup, (UIElement*), void), asCALL_THISCALL);
    // void Menu::SetPopupOffset(const IntVector2& offset) | File: ../UI/Menu.h
    engine->RegisterObjectMethod("DropDownList", "void SetPopupOffset(const IntVector2&in)", asMETHODPR(DropDownList, SetPopupOffset, (const IntVector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "void set_popupOffset(const IntVector2&in)", asMETHODPR(DropDownList, SetPopupOffset, (const IntVector2&), void), asCALL_THISCALL);
    // void Menu::SetPopupOffset(int x, int y) | File: ../UI/Menu.h
    engine->RegisterObjectMethod("DropDownList", "void SetPopupOffset(int, int)", asMETHODPR(DropDownList, SetPopupOffset, (int, int), void), asCALL_THISCALL);
    // void UIElement::SetPosition(const IntVector2& position) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "void SetPosition(const IntVector2&in)", asMETHODPR(DropDownList, SetPosition, (const IntVector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "void set_position(const IntVector2&in)", asMETHODPR(DropDownList, SetPosition, (const IntVector2&), void), asCALL_THISCALL);
    // void UIElement::SetPosition(int x, int y) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "void SetPosition(int, int)", asMETHODPR(DropDownList, SetPosition, (int, int), void), asCALL_THISCALL);
    // void Button::SetPressedChildOffset(const IntVector2& offset) | File: ../UI/Button.h
    engine->RegisterObjectMethod("DropDownList", "void SetPressedChildOffset(const IntVector2&in)", asMETHODPR(DropDownList, SetPressedChildOffset, (const IntVector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "void set_pressedChildOffset(const IntVector2&in)", asMETHODPR(DropDownList, SetPressedChildOffset, (const IntVector2&), void), asCALL_THISCALL);
    // void Button::SetPressedChildOffset(int x, int y) | File: ../UI/Button.h
    engine->RegisterObjectMethod("DropDownList", "void SetPressedChildOffset(int, int)", asMETHODPR(DropDownList, SetPressedChildOffset, (int, int), void), asCALL_THISCALL);
    // void Button::SetPressedOffset(const IntVector2& offset) | File: ../UI/Button.h
    engine->RegisterObjectMethod("DropDownList", "void SetPressedOffset(const IntVector2&in)", asMETHODPR(DropDownList, SetPressedOffset, (const IntVector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "void set_pressedOffset(const IntVector2&in)", asMETHODPR(DropDownList, SetPressedOffset, (const IntVector2&), void), asCALL_THISCALL);
    // void Button::SetPressedOffset(int x, int y) | File: ../UI/Button.h
    engine->RegisterObjectMethod("DropDownList", "void SetPressedOffset(int, int)", asMETHODPR(DropDownList, SetPressedOffset, (int, int), void), asCALL_THISCALL);
    // void UIElement::SetPriority(int priority) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "void SetPriority(int)", asMETHODPR(DropDownList, SetPriority, (int), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "void set_priority(int)", asMETHODPR(DropDownList, SetPriority, (int), void), asCALL_THISCALL);
    // void UIElement::SetRenderTexture(Texture2D* texture) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "void SetRenderTexture(Texture2D@+)", asMETHODPR(DropDownList, SetRenderTexture, (Texture2D*), void), asCALL_THISCALL);
    // void Button::SetRepeat(float delay, float rate) | File: ../UI/Button.h
    engine->RegisterObjectMethod("DropDownList", "void SetRepeat(float, float)", asMETHODPR(DropDownList, SetRepeat, (float, float), void), asCALL_THISCALL);
    // void Button::SetRepeatDelay(float delay) | File: ../UI/Button.h
    engine->RegisterObjectMethod("DropDownList", "void SetRepeatDelay(float)", asMETHODPR(DropDownList, SetRepeatDelay, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "void set_repeatDelay(float)", asMETHODPR(DropDownList, SetRepeatDelay, (float), void), asCALL_THISCALL);
    // void Button::SetRepeatRate(float rate) | File: ../UI/Button.h
    engine->RegisterObjectMethod("DropDownList", "void SetRepeatRate(float)", asMETHODPR(DropDownList, SetRepeatRate, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "void set_repeatRate(float)", asMETHODPR(DropDownList, SetRepeatRate, (float), void), asCALL_THISCALL);
    // void DropDownList::SetResizePopup(bool enable) | File: ../UI/DropDownList.h
    engine->RegisterObjectMethod("DropDownList", "void SetResizePopup(bool)", asMETHODPR(DropDownList, SetResizePopup, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "void set_resizePopup(bool)", asMETHODPR(DropDownList, SetResizePopup, (bool), void), asCALL_THISCALL);
    // void UIElement::SetSelected(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "void SetSelected(bool)", asMETHODPR(DropDownList, SetSelected, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "void set_selected(bool)", asMETHODPR(DropDownList, SetSelected, (bool), void), asCALL_THISCALL);
    // void DropDownList::SetSelection(unsigned index) | File: ../UI/DropDownList.h
    engine->RegisterObjectMethod("DropDownList", "void SetSelection(uint)", asMETHODPR(DropDownList, SetSelection, (unsigned), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "void set_selection(uint)", asMETHODPR(DropDownList, SetSelection, (unsigned), void), asCALL_THISCALL);
    // void DropDownList::SetSelectionAttr(unsigned index) | File: ../UI/DropDownList.h
    engine->RegisterObjectMethod("DropDownList", "void SetSelectionAttr(uint)", asMETHODPR(DropDownList, SetSelectionAttr, (unsigned), void), asCALL_THISCALL);
    // void UIElement::SetSize(const IntVector2& size) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "void SetSize(const IntVector2&in)", asMETHODPR(DropDownList, SetSize, (const IntVector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "void set_size(const IntVector2&in)", asMETHODPR(DropDownList, SetSize, (const IntVector2&), void), asCALL_THISCALL);
    // void UIElement::SetSize(int width, int height) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "void SetSize(int, int)", asMETHODPR(DropDownList, SetSize, (int, int), void), asCALL_THISCALL);
    // void UIElement::SetSortChildren(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "void SetSortChildren(bool)", asMETHODPR(DropDownList, SetSortChildren, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "void set_sortChildren(bool)", asMETHODPR(DropDownList, SetSortChildren, (bool), void), asCALL_THISCALL);
    // bool UIElement::SetStyle(const String& styleName, XMLFile* file=nullptr) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "bool SetStyle(const String&in, XMLFile@+ = null)", asMETHODPR(DropDownList, SetStyle, (const String&, XMLFile*), bool), asCALL_THISCALL);
    // bool UIElement::SetStyle(const XMLElement& element) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "bool SetStyle(const XMLElement&in)", asMETHODPR(DropDownList, SetStyle, (const XMLElement&), bool), asCALL_THISCALL);
    // bool UIElement::SetStyleAuto(XMLFile* file=nullptr) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "bool SetStyleAuto(XMLFile@+ = null)", asMETHODPR(DropDownList, SetStyleAuto, (XMLFile*), bool), asCALL_THISCALL);
    // void UIElement::SetTags(const StringVector& tags) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "void SetTags(Array<String>@+)", asFUNCTION(DropDownList_SetTags_StringVector), asCALL_CDECL_OBJFIRST);
    // void Serializable::SetTemporary(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("DropDownList", "void SetTemporary(bool)", asMETHODPR(DropDownList, SetTemporary, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "void set_temporary(bool)", asMETHODPR(DropDownList, SetTemporary, (bool), void), asCALL_THISCALL);
    // void BorderImage::SetTexture(Texture* texture) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("DropDownList", "void SetTexture(Texture@+)", asMETHODPR(DropDownList, SetTexture, (Texture*), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "void set_texture(Texture@+)", asMETHODPR(DropDownList, SetTexture, (Texture*), void), asCALL_THISCALL);
    // void BorderImage::SetTextureAttr(const ResourceRef& value) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("DropDownList", "void SetTextureAttr(const ResourceRef&in)", asMETHODPR(DropDownList, SetTextureAttr, (const ResourceRef&), void), asCALL_THISCALL);
    // void BorderImage::SetTiled(bool enable) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("DropDownList", "void SetTiled(bool)", asMETHODPR(DropDownList, SetTiled, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "void set_tiled(bool)", asMETHODPR(DropDownList, SetTiled, (bool), void), asCALL_THISCALL);
    // void UIElement::SetTraversalMode(TraversalMode traversalMode) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "void SetTraversalMode(TraversalMode)", asMETHODPR(DropDownList, SetTraversalMode, (TraversalMode), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "void set_traversalMode(TraversalMode)", asMETHODPR(DropDownList, SetTraversalMode, (TraversalMode), void), asCALL_THISCALL);
    // void UIElement::SetUseDerivedOpacity(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "void SetUseDerivedOpacity(bool)", asMETHODPR(DropDownList, SetUseDerivedOpacity, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "void set_useDerivedOpacity(bool)", asMETHODPR(DropDownList, SetUseDerivedOpacity, (bool), void), asCALL_THISCALL);
    // void UIElement::SetVar(StringHash key, const Variant& value) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "void SetVar(StringHash, const Variant&in)", asMETHODPR(DropDownList, SetVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    // void UIElement::SetVerticalAlignment(VerticalAlignment align) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "void SetVerticalAlignment(VerticalAlignment)", asMETHODPR(DropDownList, SetVerticalAlignment, (VerticalAlignment), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "void set_verticalAlignment(VerticalAlignment)", asMETHODPR(DropDownList, SetVerticalAlignment, (VerticalAlignment), void), asCALL_THISCALL);
    // void UIElement::SetVisible(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "void SetVisible(bool)", asMETHODPR(DropDownList, SetVisible, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "void set_visible(bool)", asMETHODPR(DropDownList, SetVisible, (bool), void), asCALL_THISCALL);
    // void UIElement::SetWidth(int width) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "void SetWidth(int)", asMETHODPR(DropDownList, SetWidth, (int), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "void set_width(int)", asMETHODPR(DropDownList, SetWidth, (int), void), asCALL_THISCALL);
    // void Menu::ShowPopup(bool enable) | File: ../UI/Menu.h
    engine->RegisterObjectMethod("DropDownList", "void ShowPopup(bool)", asMETHODPR(DropDownList, ShowPopup, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "void set_showPopup(bool)", asMETHODPR(DropDownList, ShowPopup, (bool), void), asCALL_THISCALL);
    // void UIElement::SortChildren() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "void SortChildren()", asMETHODPR(DropDownList, SortChildren, (), void), asCALL_THISCALL);
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod("DropDownList", "void UnsubscribeFromAllEvents()", asMETHODPR(DropDownList, UnsubscribeFromAllEvents, (), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("DropDownList", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", asFUNCTION(DropDownList_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), asCALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("DropDownList", "void UnsubscribeFromEvent(StringHash)", asMETHODPR(DropDownList, UnsubscribeFromEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("DropDownList", "void UnsubscribeFromEvent(Object@+, StringHash)", asMETHODPR(DropDownList, UnsubscribeFromEvent, (Object*, StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("DropDownList", "void UnsubscribeFromEvents(Object@+)", asMETHODPR(DropDownList, UnsubscribeFromEvents, (Object*), void), asCALL_THISCALL);
    // void Menu::Update(float timeStep) override | File: ../UI/Menu.h
    engine->RegisterObjectMethod("DropDownList", "void Update(float)", asMETHODPR(DropDownList, Update, (float), void), asCALL_THISCALL);
    // void UIElement::UpdateLayout() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "void UpdateLayout()", asMETHODPR(DropDownList, UpdateLayout, (), void), asCALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("DropDownList", "int WeakRefs() const", asMETHODPR(DropDownList, WeakRefs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "int get_weakRefs() const", asMETHODPR(DropDownList, WeakRefs, () const, int), asCALL_THISCALL);
    // void Serializable::WriteDeltaUpdate(Serializer& dest, const DirtyBits& attributeBits, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("DropDownList", "void WriteDeltaUpdate(Serializer&, const DirtyBits&in, uint8)", asMETHODPR(DropDownList, WriteDeltaUpdate, (Serializer&, const DirtyBits&, unsigned char), void), asCALL_THISCALL);
    // void Serializable::WriteInitialDeltaUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("DropDownList", "void WriteInitialDeltaUpdate(Serializer&, uint8)", asMETHODPR(DropDownList, WriteInitialDeltaUpdate, (Serializer&, unsigned char), void), asCALL_THISCALL);
    // void Serializable::WriteLatestDataUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("DropDownList", "void WriteLatestDataUpdate(Serializer&, uint8)", asMETHODPR(DropDownList, WriteLatestDataUpdate, (Serializer&, unsigned char), void), asCALL_THISCALL);
#ifdef REGISTER_MANUAL_PART_Menu
    REGISTER_MANUAL_PART_Menu(DropDownList, "DropDownList")
#endif
#ifdef REGISTER_MANUAL_PART_Button
    REGISTER_MANUAL_PART_Button(DropDownList, "DropDownList")
#endif
#ifdef REGISTER_MANUAL_PART_BorderImage
    REGISTER_MANUAL_PART_BorderImage(DropDownList, "DropDownList")
#endif
#ifdef REGISTER_MANUAL_PART_UIElement
    REGISTER_MANUAL_PART_UIElement(DropDownList, "DropDownList")
#endif
#ifdef REGISTER_MANUAL_PART_Animatable
    REGISTER_MANUAL_PART_Animatable(DropDownList, "DropDownList")
#endif
#ifdef REGISTER_MANUAL_PART_Serializable
    REGISTER_MANUAL_PART_Serializable(DropDownList, "DropDownList")
#endif
#ifdef REGISTER_MANUAL_PART_Object
    REGISTER_MANUAL_PART_Object(DropDownList, "DropDownList")
#endif
#ifdef REGISTER_MANUAL_PART_RefCounted
    REGISTER_MANUAL_PART_RefCounted(DropDownList, "DropDownList")
#endif
#ifdef REGISTER_MANUAL_PART_DropDownList
    REGISTER_MANUAL_PART_DropDownList(DropDownList, "DropDownList")
#endif
    RegisterSubclass<Menu, DropDownList>(engine, "Menu", "DropDownList");
    RegisterSubclass<Button, DropDownList>(engine, "Button", "DropDownList");
    RegisterSubclass<BorderImage, DropDownList>(engine, "BorderImage", "DropDownList");
    RegisterSubclass<UIElement, DropDownList>(engine, "UIElement", "DropDownList");
    RegisterSubclass<Animatable, DropDownList>(engine, "Animatable", "DropDownList");
    RegisterSubclass<Serializable, DropDownList>(engine, "Serializable", "DropDownList");
    RegisterSubclass<Object, DropDownList>(engine, "Object", "DropDownList");
    RegisterSubclass<RefCounted, DropDownList>(engine, "RefCounted", "DropDownList");

#ifdef URHO3D_NAVIGATION
    // void RefCounted::AddRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("DynamicNavigationMesh", asBEHAVE_ADDREF, "void f()", asMETHODPR(DynamicNavigationMesh, AddRef, (), void), asCALL_THISCALL);
    // void Component::AddReplicationState(ComponentReplicationState* state) | File: ../Scene/Component.h
    // Error: type "ComponentReplicationState*" can not automatically bind
    // bool DynamicNavigationMesh::AddTile(const PODVector<unsigned char>& tileData) override | File: ../Navigation/DynamicNavigationMesh.h
    // Error: type "const PODVector<unsigned char>&" can not automatically bind
    // bool DynamicNavigationMesh::Allocate(const BoundingBox& boundingBox, unsigned maxTiles) override | File: ../Navigation/DynamicNavigationMesh.h
    engine->RegisterObjectMethod("DynamicNavigationMesh", "bool Allocate(const BoundingBox&in, uint)", asMETHODPR(DynamicNavigationMesh, Allocate, (const BoundingBox&, unsigned), bool), asCALL_THISCALL);
    // void Serializable::AllocateNetworkState() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("DynamicNavigationMesh", "void AllocateNetworkState()", asMETHODPR(DynamicNavigationMesh, AllocateNetworkState, (), void), asCALL_THISCALL);
    // virtual void Serializable::ApplyAttributes() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("DynamicNavigationMesh", "void ApplyAttributes()", asMETHODPR(DynamicNavigationMesh, ApplyAttributes, (), void), asCALL_THISCALL);
    // bool DynamicNavigationMesh::Build() override | File: ../Navigation/DynamicNavigationMesh.h
    engine->RegisterObjectMethod("DynamicNavigationMesh", "bool Build()", asMETHODPR(DynamicNavigationMesh, Build, (), bool), asCALL_THISCALL);
    // bool DynamicNavigationMesh::Build(const BoundingBox& boundingBox) override | File: ../Navigation/DynamicNavigationMesh.h
    engine->RegisterObjectMethod("DynamicNavigationMesh", "bool Build(const BoundingBox&in)", asMETHODPR(DynamicNavigationMesh, Build, (const BoundingBox&), bool), asCALL_THISCALL);
    // bool DynamicNavigationMesh::Build(const IntVector2& from, const IntVector2& to) override | File: ../Navigation/DynamicNavigationMesh.h
    engine->RegisterObjectMethod("DynamicNavigationMesh", "bool Build(const IntVector2&in, const IntVector2&in)", asMETHODPR(DynamicNavigationMesh, Build, (const IntVector2&, const IntVector2&), bool), asCALL_THISCALL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // void Component::CleanupConnection(Connection* connection) | File: ../Scene/Component.h
    // Not registered because have @manualbind mark
    // void DynamicNavigationMesh::DrawDebugGeometry(DebugRenderer* debug, bool depthTest) override | File: ../Navigation/DynamicNavigationMesh.h
    engine->RegisterObjectMethod("DynamicNavigationMesh", "void DrawDebugGeometry(DebugRenderer@+, bool)", asMETHODPR(DynamicNavigationMesh, DrawDebugGeometry, (DebugRenderer*, bool), void), asCALL_THISCALL);
    // void DynamicNavigationMesh::DrawDebugGeometry(bool depthTest) | File: ../Navigation/DynamicNavigationMesh.h
    engine->RegisterObjectMethod("DynamicNavigationMesh", "void DrawDebugGeometry(bool)", asMETHODPR(DynamicNavigationMesh, DrawDebugGeometry, (bool), void), asCALL_THISCALL);
    // explicit DynamicNavigationMesh::DynamicNavigationMesh(Context* context) | File: ../Navigation/DynamicNavigationMesh.h
    engine->RegisterObjectBehaviour("DynamicNavigationMesh", asBEHAVE_FACTORY, "DynamicNavigationMesh@+ f()", asFUNCTION(DynamicNavigationMesh_DynamicNavigationMesh_Context), asCALL_CDECL);
    // Vector3 NavigationMesh::FindNearestPoint(const Vector3& point, const Vector3& extents=Vector3::ONE, const dtQueryFilter* filter=nullptr, dtPolyRef* nearestRef=nullptr) | File: ../Navigation/NavigationMesh.h
    // Error: type "const dtQueryFilter*" can not automatically bind
    // void NavigationMesh::FindPath(PODVector<Vector3>& dest, const Vector3& start, const Vector3& end, const Vector3& extents=Vector3::ONE, const dtQueryFilter* filter=nullptr) | File: ../Navigation/NavigationMesh.h
    // Error: type "PODVector<Vector3>&" can not automatically bind
    // void NavigationMesh::FindPath(PODVector<NavigationPathPoint>& dest, const Vector3& start, const Vector3& end, const Vector3& extents=Vector3::ONE, const dtQueryFilter* filter=nullptr) | File: ../Navigation/NavigationMesh.h
    // Error: type "PODVector<NavigationPathPoint>&" can not automatically bind
    // float NavigationMesh::GetAgentHeight() const | File: ../Navigation/NavigationMesh.h
    engine->RegisterObjectMethod("DynamicNavigationMesh", "float GetAgentHeight() const", asMETHODPR(DynamicNavigationMesh, GetAgentHeight, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("DynamicNavigationMesh", "float get_agentHeight() const", asMETHODPR(DynamicNavigationMesh, GetAgentHeight, () const, float), asCALL_THISCALL);
    // float NavigationMesh::GetAgentMaxClimb() const | File: ../Navigation/NavigationMesh.h
    engine->RegisterObjectMethod("DynamicNavigationMesh", "float GetAgentMaxClimb() const", asMETHODPR(DynamicNavigationMesh, GetAgentMaxClimb, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("DynamicNavigationMesh", "float get_agentMaxClimb() const", asMETHODPR(DynamicNavigationMesh, GetAgentMaxClimb, () const, float), asCALL_THISCALL);
    // float NavigationMesh::GetAgentMaxSlope() const | File: ../Navigation/NavigationMesh.h
    engine->RegisterObjectMethod("DynamicNavigationMesh", "float GetAgentMaxSlope() const", asMETHODPR(DynamicNavigationMesh, GetAgentMaxSlope, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("DynamicNavigationMesh", "float get_agentMaxSlope() const", asMETHODPR(DynamicNavigationMesh, GetAgentMaxSlope, () const, float), asCALL_THISCALL);
    // float NavigationMesh::GetAgentRadius() const | File: ../Navigation/NavigationMesh.h
    engine->RegisterObjectMethod("DynamicNavigationMesh", "float GetAgentRadius() const", asMETHODPR(DynamicNavigationMesh, GetAgentRadius, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("DynamicNavigationMesh", "float get_agentRadius() const", asMETHODPR(DynamicNavigationMesh, GetAgentRadius, () const, float), asCALL_THISCALL);
    // bool Animatable::GetAnimationEnabled() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("DynamicNavigationMesh", "bool GetAnimationEnabled() const", asMETHODPR(DynamicNavigationMesh, GetAnimationEnabled, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("DynamicNavigationMesh", "bool get_animationEnabled() const", asMETHODPR(DynamicNavigationMesh, GetAnimationEnabled, () const, bool), asCALL_THISCALL);
    // float NavigationMesh::GetAreaCost(unsigned areaID) const | File: ../Navigation/NavigationMesh.h
    engine->RegisterObjectMethod("DynamicNavigationMesh", "float GetAreaCost(uint) const", asMETHODPR(DynamicNavigationMesh, GetAreaCost, (unsigned) const, float), asCALL_THISCALL);
    // Variant Serializable::GetAttribute(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("DynamicNavigationMesh", "Variant GetAttribute(uint) const", asMETHODPR(DynamicNavigationMesh, GetAttribute, (unsigned) const, Variant), asCALL_THISCALL);
    engine->RegisterObjectMethod("DynamicNavigationMesh", "Variant get_attributes(uint) const", asMETHODPR(DynamicNavigationMesh, GetAttribute, (unsigned) const, Variant), asCALL_THISCALL);
    // Variant Serializable::GetAttribute(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("DynamicNavigationMesh", "Variant GetAttribute(const String&in) const", asMETHODPR(DynamicNavigationMesh, GetAttribute, (const String&) const, Variant), asCALL_THISCALL);
    // ValueAnimation* Animatable::GetAttributeAnimation(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("DynamicNavigationMesh", "ValueAnimation@+ GetAttributeAnimation(const String&in) const", asMETHODPR(DynamicNavigationMesh, GetAttributeAnimation, (const String&) const, ValueAnimation*), asCALL_THISCALL);
    // float Animatable::GetAttributeAnimationSpeed(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("DynamicNavigationMesh", "float GetAttributeAnimationSpeed(const String&in) const", asMETHODPR(DynamicNavigationMesh, GetAttributeAnimationSpeed, (const String&) const, float), asCALL_THISCALL);
    // float Animatable::GetAttributeAnimationTime(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("DynamicNavigationMesh", "float GetAttributeAnimationTime(const String&in) const", asMETHODPR(DynamicNavigationMesh, GetAttributeAnimationTime, (const String&) const, float), asCALL_THISCALL);
    // WrapMode Animatable::GetAttributeAnimationWrapMode(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("DynamicNavigationMesh", "WrapMode GetAttributeAnimationWrapMode(const String&in) const", asMETHODPR(DynamicNavigationMesh, GetAttributeAnimationWrapMode, (const String&) const, WrapMode), asCALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("DynamicNavigationMesh", "Variant GetAttributeDefault(uint) const", asMETHODPR(DynamicNavigationMesh, GetAttributeDefault, (unsigned) const, Variant), asCALL_THISCALL);
    engine->RegisterObjectMethod("DynamicNavigationMesh", "Variant get_attributeDefaults(uint) const", asMETHODPR(DynamicNavigationMesh, GetAttributeDefault, (unsigned) const, Variant), asCALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("DynamicNavigationMesh", "Variant GetAttributeDefault(const String&in) const", asMETHODPR(DynamicNavigationMesh, GetAttributeDefault, (const String&) const, Variant), asCALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("DynamicNavigationMesh", "bool GetBlockEvents() const", asMETHODPR(DynamicNavigationMesh, GetBlockEvents, () const, bool), asCALL_THISCALL);
    // const BoundingBox& NavigationMesh::GetBoundingBox() const | File: ../Navigation/NavigationMesh.h
    engine->RegisterObjectMethod("DynamicNavigationMesh", "const BoundingBox& GetBoundingBox() const", asMETHODPR(DynamicNavigationMesh, GetBoundingBox, () const, const BoundingBox&), asCALL_THISCALL);
    engine->RegisterObjectMethod("DynamicNavigationMesh", "const BoundingBox& get_boundingBox() const", asMETHODPR(DynamicNavigationMesh, GetBoundingBox, () const, const BoundingBox&), asCALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("DynamicNavigationMesh", "const String& GetCategory() const", asMETHODPR(DynamicNavigationMesh, GetCategory, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("DynamicNavigationMesh", "const String& get_category() const", asMETHODPR(DynamicNavigationMesh, GetCategory, () const, const String&), asCALL_THISCALL);
    // float NavigationMesh::GetCellHeight() const | File: ../Navigation/NavigationMesh.h
    engine->RegisterObjectMethod("DynamicNavigationMesh", "float GetCellHeight() const", asMETHODPR(DynamicNavigationMesh, GetCellHeight, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("DynamicNavigationMesh", "float get_cellHeight() const", asMETHODPR(DynamicNavigationMesh, GetCellHeight, () const, float), asCALL_THISCALL);
    // float NavigationMesh::GetCellSize() const | File: ../Navigation/NavigationMesh.h
    engine->RegisterObjectMethod("DynamicNavigationMesh", "float GetCellSize() const", asMETHODPR(DynamicNavigationMesh, GetCellSize, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("DynamicNavigationMesh", "float get_cellSize() const", asMETHODPR(DynamicNavigationMesh, GetCellSize, () const, float), asCALL_THISCALL);
    // Component* Component::GetComponent(StringHash type) const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("DynamicNavigationMesh", "Component@+ GetComponent(StringHash) const", asMETHODPR(DynamicNavigationMesh, GetComponent, (StringHash) const, Component*), asCALL_THISCALL);
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
    // float NavigationMesh::GetDetailSampleDistance() const | File: ../Navigation/NavigationMesh.h
    engine->RegisterObjectMethod("DynamicNavigationMesh", "float GetDetailSampleDistance() const", asMETHODPR(DynamicNavigationMesh, GetDetailSampleDistance, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("DynamicNavigationMesh", "float get_detailSampleDistance() const", asMETHODPR(DynamicNavigationMesh, GetDetailSampleDistance, () const, float), asCALL_THISCALL);
    // float NavigationMesh::GetDetailSampleMaxError() const | File: ../Navigation/NavigationMesh.h
    engine->RegisterObjectMethod("DynamicNavigationMesh", "float GetDetailSampleMaxError() const", asMETHODPR(DynamicNavigationMesh, GetDetailSampleMaxError, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("DynamicNavigationMesh", "float get_detailSampleMaxError() const", asMETHODPR(DynamicNavigationMesh, GetDetailSampleMaxError, () const, float), asCALL_THISCALL);
    // float NavigationMesh::GetDistanceToWall(const Vector3& point, float radius, const Vector3& extents=Vector3::ONE, const dtQueryFilter* filter=nullptr, Vector3* hitPos=nullptr, Vector3* hitNormal=nullptr) | File: ../Navigation/NavigationMesh.h
    // Error: type "const dtQueryFilter*" can not automatically bind
    // bool NavigationMesh::GetDrawNavAreas() const | File: ../Navigation/NavigationMesh.h
    engine->RegisterObjectMethod("DynamicNavigationMesh", "bool GetDrawNavAreas() const", asMETHODPR(DynamicNavigationMesh, GetDrawNavAreas, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("DynamicNavigationMesh", "bool get_drawNavAreas() const", asMETHODPR(DynamicNavigationMesh, GetDrawNavAreas, () const, bool), asCALL_THISCALL);
    // bool DynamicNavigationMesh::GetDrawObstacles() const | File: ../Navigation/DynamicNavigationMesh.h
    engine->RegisterObjectMethod("DynamicNavigationMesh", "bool GetDrawObstacles() const", asMETHODPR(DynamicNavigationMesh, GetDrawObstacles, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("DynamicNavigationMesh", "bool get_drawObstacles() const", asMETHODPR(DynamicNavigationMesh, GetDrawObstacles, () const, bool), asCALL_THISCALL);
    // bool NavigationMesh::GetDrawOffMeshConnections() const | File: ../Navigation/NavigationMesh.h
    engine->RegisterObjectMethod("DynamicNavigationMesh", "bool GetDrawOffMeshConnections() const", asMETHODPR(DynamicNavigationMesh, GetDrawOffMeshConnections, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("DynamicNavigationMesh", "bool get_drawOffMeshConnections() const", asMETHODPR(DynamicNavigationMesh, GetDrawOffMeshConnections, () const, bool), asCALL_THISCALL);
    // float NavigationMesh::GetEdgeMaxError() const | File: ../Navigation/NavigationMesh.h
    engine->RegisterObjectMethod("DynamicNavigationMesh", "float GetEdgeMaxError() const", asMETHODPR(DynamicNavigationMesh, GetEdgeMaxError, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("DynamicNavigationMesh", "float get_edgeMaxError() const", asMETHODPR(DynamicNavigationMesh, GetEdgeMaxError, () const, float), asCALL_THISCALL);
    // float NavigationMesh::GetEdgeMaxLength() const | File: ../Navigation/NavigationMesh.h
    engine->RegisterObjectMethod("DynamicNavigationMesh", "float GetEdgeMaxLength() const", asMETHODPR(DynamicNavigationMesh, GetEdgeMaxLength, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("DynamicNavigationMesh", "float get_edgeMaxLength() const", asMETHODPR(DynamicNavigationMesh, GetEdgeMaxLength, () const, float), asCALL_THISCALL);
    // VariantMap& Object::GetEventDataMap() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("DynamicNavigationMesh", "VariantMap& GetEventDataMap() const", asMETHODPR(DynamicNavigationMesh, GetEventDataMap, () const, VariantMap&), asCALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("DynamicNavigationMesh", "Object@+ GetEventSender() const", asMETHODPR(DynamicNavigationMesh, GetEventSender, () const, Object*), asCALL_THISCALL);
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("DynamicNavigationMesh", "const Variant& GetGlobalVar(StringHash) const", asMETHODPR(DynamicNavigationMesh, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    engine->RegisterObjectMethod("DynamicNavigationMesh", "const Variant& get_globalVar(StringHash) const", asMETHODPR(DynamicNavigationMesh, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("DynamicNavigationMesh", "const VariantMap& GetGlobalVars() const", asMETHODPR(DynamicNavigationMesh, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    engine->RegisterObjectMethod("DynamicNavigationMesh", "const VariantMap& get_globalVars() const", asMETHODPR(DynamicNavigationMesh, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    // unsigned Component::GetID() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("DynamicNavigationMesh", "uint GetID() const", asMETHODPR(DynamicNavigationMesh, GetID, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("DynamicNavigationMesh", "uint get_id() const", asMETHODPR(DynamicNavigationMesh, GetID, () const, unsigned), asCALL_THISCALL);
    // bool Serializable::GetInterceptNetworkUpdate(const String& attributeName) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("DynamicNavigationMesh", "bool GetInterceptNetworkUpdate(const String&in) const", asMETHODPR(DynamicNavigationMesh, GetInterceptNetworkUpdate, (const String&) const, bool), asCALL_THISCALL);
    // unsigned DynamicNavigationMesh::GetMaxLayers() const | File: ../Navigation/DynamicNavigationMesh.h
    engine->RegisterObjectMethod("DynamicNavigationMesh", "uint GetMaxLayers() const", asMETHODPR(DynamicNavigationMesh, GetMaxLayers, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("DynamicNavigationMesh", "uint get_maxLayers() const", asMETHODPR(DynamicNavigationMesh, GetMaxLayers, () const, unsigned), asCALL_THISCALL);
    // unsigned DynamicNavigationMesh::GetMaxObstacles() const | File: ../Navigation/DynamicNavigationMesh.h
    engine->RegisterObjectMethod("DynamicNavigationMesh", "uint GetMaxObstacles() const", asMETHODPR(DynamicNavigationMesh, GetMaxObstacles, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("DynamicNavigationMesh", "uint get_maxObstacles() const", asMETHODPR(DynamicNavigationMesh, GetMaxObstacles, () const, unsigned), asCALL_THISCALL);
    // String NavigationMesh::GetMeshName() const | File: ../Navigation/NavigationMesh.h
    engine->RegisterObjectMethod("DynamicNavigationMesh", "String GetMeshName() const", asMETHODPR(DynamicNavigationMesh, GetMeshName, () const, String), asCALL_THISCALL);
    // PODVector<unsigned char> DynamicNavigationMesh::GetNavigationDataAttr() const override | File: ../Navigation/DynamicNavigationMesh.h
    // Error: type "PODVector<unsigned char>" can not automatically bind
    // virtual const Vector<AttributeInfo>* Serializable::GetNetworkAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // NetworkState* Serializable::GetNetworkState() const | File: ../Scene/Serializable.h
    // Error: type "NetworkState*" can not automatically bind
    // Node* Component::GetNode() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("DynamicNavigationMesh", "Node@+ GetNode() const", asMETHODPR(DynamicNavigationMesh, GetNode, () const, Node*), asCALL_THISCALL);
    engine->RegisterObjectMethod("DynamicNavigationMesh", "Node@+ get_node() const", asMETHODPR(DynamicNavigationMesh, GetNode, () const, Node*), asCALL_THISCALL);
    // unsigned Serializable::GetNumAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("DynamicNavigationMesh", "uint GetNumAttributes() const", asMETHODPR(DynamicNavigationMesh, GetNumAttributes, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("DynamicNavigationMesh", "uint get_numAttributes() const", asMETHODPR(DynamicNavigationMesh, GetNumAttributes, () const, unsigned), asCALL_THISCALL);
    // unsigned Serializable::GetNumNetworkAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("DynamicNavigationMesh", "uint GetNumNetworkAttributes() const", asMETHODPR(DynamicNavigationMesh, GetNumNetworkAttributes, () const, unsigned), asCALL_THISCALL);
    // IntVector2 NavigationMesh::GetNumTiles() const | File: ../Navigation/NavigationMesh.h
    engine->RegisterObjectMethod("DynamicNavigationMesh", "IntVector2 GetNumTiles() const", asMETHODPR(DynamicNavigationMesh, GetNumTiles, () const, IntVector2), asCALL_THISCALL);
    engine->RegisterObjectMethod("DynamicNavigationMesh", "IntVector2 get_numTiles() const", asMETHODPR(DynamicNavigationMesh, GetNumTiles, () const, IntVector2), asCALL_THISCALL);
    // ObjectAnimation* Animatable::GetObjectAnimation() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("DynamicNavigationMesh", "ObjectAnimation@+ GetObjectAnimation() const", asMETHODPR(DynamicNavigationMesh, GetObjectAnimation, () const, ObjectAnimation*), asCALL_THISCALL);
    engine->RegisterObjectMethod("DynamicNavigationMesh", "ObjectAnimation@+ get_objectAnimation() const", asMETHODPR(DynamicNavigationMesh, GetObjectAnimation, () const, ObjectAnimation*), asCALL_THISCALL);
    // ResourceRef Animatable::GetObjectAnimationAttr() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("DynamicNavigationMesh", "ResourceRef GetObjectAnimationAttr() const", asMETHODPR(DynamicNavigationMesh, GetObjectAnimationAttr, () const, ResourceRef), asCALL_THISCALL);
    // const Vector3& NavigationMesh::GetPadding() const | File: ../Navigation/NavigationMesh.h
    engine->RegisterObjectMethod("DynamicNavigationMesh", "const Vector3& GetPadding() const", asMETHODPR(DynamicNavigationMesh, GetPadding, () const, const Vector3&), asCALL_THISCALL);
    engine->RegisterObjectMethod("DynamicNavigationMesh", "const Vector3& get_padding() const", asMETHODPR(DynamicNavigationMesh, GetPadding, () const, const Vector3&), asCALL_THISCALL);
    // NavmeshPartitionType NavigationMesh::GetPartitionType() const | File: ../Navigation/NavigationMesh.h
    engine->RegisterObjectMethod("DynamicNavigationMesh", "NavmeshPartitionType GetPartitionType() const", asMETHODPR(DynamicNavigationMesh, GetPartitionType, () const, NavmeshPartitionType), asCALL_THISCALL);
    engine->RegisterObjectMethod("DynamicNavigationMesh", "NavmeshPartitionType get_partitionType() const", asMETHODPR(DynamicNavigationMesh, GetPartitionType, () const, NavmeshPartitionType), asCALL_THISCALL);
    // Vector3 NavigationMesh::GetRandomPoint(const dtQueryFilter* filter=nullptr, dtPolyRef* randomRef=nullptr) | File: ../Navigation/NavigationMesh.h
    // Error: type "const dtQueryFilter*" can not automatically bind
    // Vector3 NavigationMesh::GetRandomPointInCircle(const Vector3& center, float radius, const Vector3& extents=Vector3::ONE, const dtQueryFilter* filter=nullptr, dtPolyRef* randomRef=nullptr) | File: ../Navigation/NavigationMesh.h
    // Error: type "const dtQueryFilter*" can not automatically bind
    // float NavigationMesh::GetRegionMergeSize() const | File: ../Navigation/NavigationMesh.h
    engine->RegisterObjectMethod("DynamicNavigationMesh", "float GetRegionMergeSize() const", asMETHODPR(DynamicNavigationMesh, GetRegionMergeSize, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("DynamicNavigationMesh", "float get_regionMergeSize() const", asMETHODPR(DynamicNavigationMesh, GetRegionMergeSize, () const, float), asCALL_THISCALL);
    // float NavigationMesh::GetRegionMinSize() const | File: ../Navigation/NavigationMesh.h
    engine->RegisterObjectMethod("DynamicNavigationMesh", "float GetRegionMinSize() const", asMETHODPR(DynamicNavigationMesh, GetRegionMinSize, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("DynamicNavigationMesh", "float get_regionMinSize() const", asMETHODPR(DynamicNavigationMesh, GetRegionMinSize, () const, float), asCALL_THISCALL);
    // Scene* Component::GetScene() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("DynamicNavigationMesh", "Scene@+ GetScene() const", asMETHODPR(DynamicNavigationMesh, GetScene, () const, Scene*), asCALL_THISCALL);
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("DynamicNavigationMesh", "Object@+ GetSubsystem(StringHash) const", asMETHODPR(DynamicNavigationMesh, GetSubsystem, (StringHash) const, Object*), asCALL_THISCALL);
    // template<class T> T* Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // BoundingBox NavigationMesh::GetTileBoundingBox(const IntVector2& tile) const | File: ../Navigation/NavigationMesh.h
    engine->RegisterObjectMethod("DynamicNavigationMesh", "BoundingBox GetTileBoundingBox(const IntVector2&in) const", asMETHODPR(DynamicNavigationMesh, GetTileBoundingBox, (const IntVector2&) const, BoundingBox), asCALL_THISCALL);
    // PODVector<unsigned char> DynamicNavigationMesh::GetTileData(const IntVector2& tile) const override | File: ../Navigation/DynamicNavigationMesh.h
    // Error: type "PODVector<unsigned char>" can not automatically bind
    // IntVector2 NavigationMesh::GetTileIndex(const Vector3& position) const | File: ../Navigation/NavigationMesh.h
    engine->RegisterObjectMethod("DynamicNavigationMesh", "IntVector2 GetTileIndex(const Vector3&in) const", asMETHODPR(DynamicNavigationMesh, GetTileIndex, (const Vector3&) const, IntVector2), asCALL_THISCALL);
    // int NavigationMesh::GetTileSize() const | File: ../Navigation/NavigationMesh.h
    engine->RegisterObjectMethod("DynamicNavigationMesh", "int GetTileSize() const", asMETHODPR(DynamicNavigationMesh, GetTileSize, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("DynamicNavigationMesh", "int get_tileSize() const", asMETHODPR(DynamicNavigationMesh, GetTileSize, () const, int), asCALL_THISCALL);
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("DynamicNavigationMesh", "StringHash GetType() const", asMETHODPR(DynamicNavigationMesh, GetType, () const, StringHash), asCALL_THISCALL);
    engine->RegisterObjectMethod("DynamicNavigationMesh", "StringHash get_type() const", asMETHODPR(DynamicNavigationMesh, GetType, () const, StringHash), asCALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("DynamicNavigationMesh", "const String& GetTypeName() const", asMETHODPR(DynamicNavigationMesh, GetTypeName, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("DynamicNavigationMesh", "const String& get_typeName() const", asMETHODPR(DynamicNavigationMesh, GetTypeName, () const, const String&), asCALL_THISCALL);
    // BoundingBox NavigationMesh::GetWorldBoundingBox() const | File: ../Navigation/NavigationMesh.h
    engine->RegisterObjectMethod("DynamicNavigationMesh", "BoundingBox GetWorldBoundingBox() const", asMETHODPR(DynamicNavigationMesh, GetWorldBoundingBox, () const, BoundingBox), asCALL_THISCALL);
    engine->RegisterObjectMethod("DynamicNavigationMesh", "BoundingBox get_worldBoundingBox() const", asMETHODPR(DynamicNavigationMesh, GetWorldBoundingBox, () const, BoundingBox), asCALL_THISCALL);
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("DynamicNavigationMesh", "bool HasEventHandlers() const", asMETHODPR(DynamicNavigationMesh, HasEventHandlers, () const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("DynamicNavigationMesh", "bool HasSubscribedToEvent(StringHash) const", asMETHODPR(DynamicNavigationMesh, HasSubscribedToEvent, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("DynamicNavigationMesh", "bool HasSubscribedToEvent(Object@+, StringHash) const", asMETHODPR(DynamicNavigationMesh, HasSubscribedToEvent, (Object*, StringHash) const, bool), asCALL_THISCALL);
    // bool NavigationMesh::HasTile(const IntVector2& tile) const | File: ../Navigation/NavigationMesh.h
    engine->RegisterObjectMethod("DynamicNavigationMesh", "bool HasTile(const IntVector2&in) const", asMETHODPR(DynamicNavigationMesh, HasTile, (const IntVector2&) const, bool), asCALL_THISCALL);
    // bool Component::IsEnabled() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("DynamicNavigationMesh", "bool IsEnabled() const", asMETHODPR(DynamicNavigationMesh, IsEnabled, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("DynamicNavigationMesh", "bool get_enabled() const", asMETHODPR(DynamicNavigationMesh, IsEnabled, () const, bool), asCALL_THISCALL);
    // bool Component::IsEnabledEffective() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("DynamicNavigationMesh", "bool IsEnabledEffective() const", asMETHODPR(DynamicNavigationMesh, IsEnabledEffective, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("DynamicNavigationMesh", "bool get_enabledEffective() const", asMETHODPR(DynamicNavigationMesh, IsEnabledEffective, () const, bool), asCALL_THISCALL);
    // bool NavigationMesh::IsInitialized() const | File: ../Navigation/NavigationMesh.h
    engine->RegisterObjectMethod("DynamicNavigationMesh", "bool IsInitialized() const", asMETHODPR(DynamicNavigationMesh, IsInitialized, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("DynamicNavigationMesh", "bool get_initialized() const", asMETHODPR(DynamicNavigationMesh, IsInitialized, () const, bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("DynamicNavigationMesh", "bool IsInstanceOf(StringHash) const", asMETHODPR(DynamicNavigationMesh, IsInstanceOf, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // bool DynamicNavigationMesh::IsObstacleInTile(Obstacle* obstacle, const IntVector2& tile) const | File: ../Navigation/DynamicNavigationMesh.h
    engine->RegisterObjectMethod("DynamicNavigationMesh", "bool IsObstacleInTile(Obstacle@+, const IntVector2&in) const", asMETHODPR(DynamicNavigationMesh, IsObstacleInTile, (Obstacle*, const IntVector2&) const, bool), asCALL_THISCALL);
    // bool Component::IsReplicated() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("DynamicNavigationMesh", "bool IsReplicated() const", asMETHODPR(DynamicNavigationMesh, IsReplicated, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("DynamicNavigationMesh", "bool get_replicated() const", asMETHODPR(DynamicNavigationMesh, IsReplicated, () const, bool), asCALL_THISCALL);
    // bool Serializable::IsTemporary() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("DynamicNavigationMesh", "bool IsTemporary() const", asMETHODPR(DynamicNavigationMesh, IsTemporary, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("DynamicNavigationMesh", "bool get_temporary() const", asMETHODPR(DynamicNavigationMesh, IsTemporary, () const, bool), asCALL_THISCALL);
    // virtual bool Serializable::Load(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("DynamicNavigationMesh", "bool Load(Deserializer&)", asMETHODPR(DynamicNavigationMesh, Load, (Deserializer&), bool), asCALL_THISCALL);
    // bool Animatable::LoadJSON(const JSONValue& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("DynamicNavigationMesh", "bool LoadJSON(const JSONValue&in)", asMETHODPR(DynamicNavigationMesh, LoadJSON, (const JSONValue&), bool), asCALL_THISCALL);
    // bool Animatable::LoadXML(const XMLElement& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("DynamicNavigationMesh", "bool LoadXML(const XMLElement&in)", asMETHODPR(DynamicNavigationMesh, LoadXML, (const XMLElement&), bool), asCALL_THISCALL);
    // void Component::MarkNetworkUpdate() override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("DynamicNavigationMesh", "void MarkNetworkUpdate()", asMETHODPR(DynamicNavigationMesh, MarkNetworkUpdate, (), void), asCALL_THISCALL);
    // Vector3 NavigationMesh::MoveAlongSurface(const Vector3& start, const Vector3& end, const Vector3& extents=Vector3::ONE, int maxVisited=3, const dtQueryFilter* filter=nullptr) | File: ../Navigation/NavigationMesh.h
    // Error: type "const dtQueryFilter*" can not automatically bind
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("DynamicNavigationMesh", "void OnEvent(Object@+, StringHash, VariantMap&)", asMETHODPR(DynamicNavigationMesh, OnEvent, (Object*, StringHash, VariantMap&), void), asCALL_THISCALL);
    // virtual void Serializable::OnGetAttribute(const AttributeInfo& attr, Variant& dest) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("DynamicNavigationMesh", "void OnGetAttribute(const AttributeInfo&in, Variant&) const", asMETHODPR(DynamicNavigationMesh, OnGetAttribute, (const AttributeInfo&, Variant&) const, void), asCALL_THISCALL);
    // virtual void Serializable::OnSetAttribute(const AttributeInfo& attr, const Variant& src) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("DynamicNavigationMesh", "void OnSetAttribute(const AttributeInfo&in, const Variant&in)", asMETHODPR(DynamicNavigationMesh, OnSetAttribute, (const AttributeInfo&, const Variant&), void), asCALL_THISCALL);
    // virtual void Component::OnSetEnabled() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("DynamicNavigationMesh", "void OnSetEnabled()", asMETHODPR(DynamicNavigationMesh, OnSetEnabled, (), void), asCALL_THISCALL);
    // void Component::PrepareNetworkUpdate() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("DynamicNavigationMesh", "void PrepareNetworkUpdate()", asMETHODPR(DynamicNavigationMesh, PrepareNetworkUpdate, (), void), asCALL_THISCALL);
    // Vector3 NavigationMesh::Raycast(const Vector3& start, const Vector3& end, const Vector3& extents=Vector3::ONE, const dtQueryFilter* filter=nullptr, Vector3* hitNormal=nullptr) | File: ../Navigation/NavigationMesh.h
    // Error: type "const dtQueryFilter*" can not automatically bind
    // bool Serializable::ReadDeltaUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("DynamicNavigationMesh", "bool ReadDeltaUpdate(Deserializer&)", asMETHODPR(DynamicNavigationMesh, ReadDeltaUpdate, (Deserializer&), bool), asCALL_THISCALL);
    // bool Serializable::ReadLatestDataUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("DynamicNavigationMesh", "bool ReadLatestDataUpdate(Deserializer&)", asMETHODPR(DynamicNavigationMesh, ReadLatestDataUpdate, (Deserializer&), bool), asCALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("DynamicNavigationMesh", "int Refs() const", asMETHODPR(DynamicNavigationMesh, Refs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("DynamicNavigationMesh", "int get_refs() const", asMETHODPR(DynamicNavigationMesh, Refs, () const, int), asCALL_THISCALL);
    // static void DynamicNavigationMesh::RegisterObject(Context* context) | File: ../Navigation/DynamicNavigationMesh.h
    // Not registered because have @nobind mark
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("DynamicNavigationMesh", asBEHAVE_RELEASE, "void f()", asMETHODPR(DynamicNavigationMesh, ReleaseRef, (), void), asCALL_THISCALL);
    // void Component::Remove() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("DynamicNavigationMesh", "void Remove()", asMETHODPR(DynamicNavigationMesh, Remove, (), void), asCALL_THISCALL);
    // void DynamicNavigationMesh::RemoveAllTiles() override | File: ../Navigation/DynamicNavigationMesh.h
    engine->RegisterObjectMethod("DynamicNavigationMesh", "void RemoveAllTiles()", asMETHODPR(DynamicNavigationMesh, RemoveAllTiles, (), void), asCALL_THISCALL);
    // void Animatable::RemoveAttributeAnimation(const String& name) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("DynamicNavigationMesh", "void RemoveAttributeAnimation(const String&in)", asMETHODPR(DynamicNavigationMesh, RemoveAttributeAnimation, (const String&), void), asCALL_THISCALL);
    // void Serializable::RemoveInstanceDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("DynamicNavigationMesh", "void RemoveInstanceDefault()", asMETHODPR(DynamicNavigationMesh, RemoveInstanceDefault, (), void), asCALL_THISCALL);
    // void Animatable::RemoveObjectAnimation() | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("DynamicNavigationMesh", "void RemoveObjectAnimation()", asMETHODPR(DynamicNavigationMesh, RemoveObjectAnimation, (), void), asCALL_THISCALL);
    // void DynamicNavigationMesh::RemoveTile(const IntVector2& tile) override | File: ../Navigation/DynamicNavigationMesh.h
    engine->RegisterObjectMethod("DynamicNavigationMesh", "void RemoveTile(const IntVector2&in)", asMETHODPR(DynamicNavigationMesh, RemoveTile, (const IntVector2&), void), asCALL_THISCALL);
    // void Serializable::ResetToDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("DynamicNavigationMesh", "void ResetToDefault()", asMETHODPR(DynamicNavigationMesh, ResetToDefault, (), void), asCALL_THISCALL);
    // bool Component::Save(Serializer& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("DynamicNavigationMesh", "bool Save(Serializer&) const", asMETHODPR(DynamicNavigationMesh, Save, (Serializer&) const, bool), asCALL_THISCALL);
    // virtual bool Serializable::SaveDefaultAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("DynamicNavigationMesh", "bool SaveDefaultAttributes() const", asMETHODPR(DynamicNavigationMesh, SaveDefaultAttributes, () const, bool), asCALL_THISCALL);
    // bool Component::SaveJSON(JSONValue& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("DynamicNavigationMesh", "bool SaveJSON(JSONValue&) const", asMETHODPR(DynamicNavigationMesh, SaveJSON, (JSONValue&) const, bool), asCALL_THISCALL);
    // bool Component::SaveXML(XMLElement& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("DynamicNavigationMesh", "bool SaveXML(XMLElement&) const", asMETHODPR(DynamicNavigationMesh, SaveXML, (XMLElement&) const, bool), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("DynamicNavigationMesh", "void SendEvent(StringHash)", asMETHODPR(DynamicNavigationMesh, SendEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("DynamicNavigationMesh", "void SendEvent(StringHash, VariantMap&)", asMETHODPR(DynamicNavigationMesh, SendEvent, (StringHash, VariantMap&), void), asCALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void NavigationMesh::SetAgentHeight(float height) | File: ../Navigation/NavigationMesh.h
    engine->RegisterObjectMethod("DynamicNavigationMesh", "void SetAgentHeight(float)", asMETHODPR(DynamicNavigationMesh, SetAgentHeight, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("DynamicNavigationMesh", "void set_agentHeight(float)", asMETHODPR(DynamicNavigationMesh, SetAgentHeight, (float), void), asCALL_THISCALL);
    // void NavigationMesh::SetAgentMaxClimb(float maxClimb) | File: ../Navigation/NavigationMesh.h
    engine->RegisterObjectMethod("DynamicNavigationMesh", "void SetAgentMaxClimb(float)", asMETHODPR(DynamicNavigationMesh, SetAgentMaxClimb, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("DynamicNavigationMesh", "void set_agentMaxClimb(float)", asMETHODPR(DynamicNavigationMesh, SetAgentMaxClimb, (float), void), asCALL_THISCALL);
    // void NavigationMesh::SetAgentMaxSlope(float maxSlope) | File: ../Navigation/NavigationMesh.h
    engine->RegisterObjectMethod("DynamicNavigationMesh", "void SetAgentMaxSlope(float)", asMETHODPR(DynamicNavigationMesh, SetAgentMaxSlope, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("DynamicNavigationMesh", "void set_agentMaxSlope(float)", asMETHODPR(DynamicNavigationMesh, SetAgentMaxSlope, (float), void), asCALL_THISCALL);
    // void NavigationMesh::SetAgentRadius(float radius) | File: ../Navigation/NavigationMesh.h
    engine->RegisterObjectMethod("DynamicNavigationMesh", "void SetAgentRadius(float)", asMETHODPR(DynamicNavigationMesh, SetAgentRadius, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("DynamicNavigationMesh", "void set_agentRadius(float)", asMETHODPR(DynamicNavigationMesh, SetAgentRadius, (float), void), asCALL_THISCALL);
    // void Animatable::SetAnimationEnabled(bool enable) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("DynamicNavigationMesh", "void SetAnimationEnabled(bool)", asMETHODPR(DynamicNavigationMesh, SetAnimationEnabled, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("DynamicNavigationMesh", "void set_animationEnabled(bool)", asMETHODPR(DynamicNavigationMesh, SetAnimationEnabled, (bool), void), asCALL_THISCALL);
    // void Animatable::SetAnimationTime(float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("DynamicNavigationMesh", "void SetAnimationTime(float)", asMETHODPR(DynamicNavigationMesh, SetAnimationTime, (float), void), asCALL_THISCALL);
    // void NavigationMesh::SetAreaCost(unsigned areaID, float cost) | File: ../Navigation/NavigationMesh.h
    engine->RegisterObjectMethod("DynamicNavigationMesh", "void SetAreaCost(uint, float)", asMETHODPR(DynamicNavigationMesh, SetAreaCost, (unsigned, float), void), asCALL_THISCALL);
    // bool Serializable::SetAttribute(unsigned index, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("DynamicNavigationMesh", "bool SetAttribute(uint, const Variant&in)", asMETHODPR(DynamicNavigationMesh, SetAttribute, (unsigned, const Variant&), bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("DynamicNavigationMesh", "bool set_attributes(uint, const Variant&in)", asMETHODPR(DynamicNavigationMesh, SetAttribute, (unsigned, const Variant&), bool), asCALL_THISCALL);
    // bool Serializable::SetAttribute(const String& name, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("DynamicNavigationMesh", "bool SetAttribute(const String&in, const Variant&in)", asMETHODPR(DynamicNavigationMesh, SetAttribute, (const String&, const Variant&), bool), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimation(const String& name, ValueAnimation* attributeAnimation, WrapMode wrapMode=WM_LOOP, float speed=1.0f) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("DynamicNavigationMesh", "void SetAttributeAnimation(const String&in, ValueAnimation@+, WrapMode = WM_LOOP, float = 1.0f)", asMETHODPR(DynamicNavigationMesh, SetAttributeAnimation, (const String&, ValueAnimation*, WrapMode, float), void), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimationSpeed(const String& name, float speed) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("DynamicNavigationMesh", "void SetAttributeAnimationSpeed(const String&in, float)", asMETHODPR(DynamicNavigationMesh, SetAttributeAnimationSpeed, (const String&, float), void), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimationTime(const String& name, float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("DynamicNavigationMesh", "void SetAttributeAnimationTime(const String&in, float)", asMETHODPR(DynamicNavigationMesh, SetAttributeAnimationTime, (const String&, float), void), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimationWrapMode(const String& name, WrapMode wrapMode) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("DynamicNavigationMesh", "void SetAttributeAnimationWrapMode(const String&in, WrapMode)", asMETHODPR(DynamicNavigationMesh, SetAttributeAnimationWrapMode, (const String&, WrapMode), void), asCALL_THISCALL);
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("DynamicNavigationMesh", "void SetBlockEvents(bool)", asMETHODPR(DynamicNavigationMesh, SetBlockEvents, (bool), void), asCALL_THISCALL);
    // void NavigationMesh::SetCellHeight(float height) | File: ../Navigation/NavigationMesh.h
    engine->RegisterObjectMethod("DynamicNavigationMesh", "void SetCellHeight(float)", asMETHODPR(DynamicNavigationMesh, SetCellHeight, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("DynamicNavigationMesh", "void set_cellHeight(float)", asMETHODPR(DynamicNavigationMesh, SetCellHeight, (float), void), asCALL_THISCALL);
    // void NavigationMesh::SetCellSize(float size) | File: ../Navigation/NavigationMesh.h
    engine->RegisterObjectMethod("DynamicNavigationMesh", "void SetCellSize(float)", asMETHODPR(DynamicNavigationMesh, SetCellSize, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("DynamicNavigationMesh", "void set_cellSize(float)", asMETHODPR(DynamicNavigationMesh, SetCellSize, (float), void), asCALL_THISCALL);
    // void NavigationMesh::SetDetailSampleDistance(float distance) | File: ../Navigation/NavigationMesh.h
    engine->RegisterObjectMethod("DynamicNavigationMesh", "void SetDetailSampleDistance(float)", asMETHODPR(DynamicNavigationMesh, SetDetailSampleDistance, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("DynamicNavigationMesh", "void set_detailSampleDistance(float)", asMETHODPR(DynamicNavigationMesh, SetDetailSampleDistance, (float), void), asCALL_THISCALL);
    // void NavigationMesh::SetDetailSampleMaxError(float error) | File: ../Navigation/NavigationMesh.h
    engine->RegisterObjectMethod("DynamicNavigationMesh", "void SetDetailSampleMaxError(float)", asMETHODPR(DynamicNavigationMesh, SetDetailSampleMaxError, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("DynamicNavigationMesh", "void set_detailSampleMaxError(float)", asMETHODPR(DynamicNavigationMesh, SetDetailSampleMaxError, (float), void), asCALL_THISCALL);
    // void NavigationMesh::SetDrawNavAreas(bool enable) | File: ../Navigation/NavigationMesh.h
    engine->RegisterObjectMethod("DynamicNavigationMesh", "void SetDrawNavAreas(bool)", asMETHODPR(DynamicNavigationMesh, SetDrawNavAreas, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("DynamicNavigationMesh", "void set_drawNavAreas(bool)", asMETHODPR(DynamicNavigationMesh, SetDrawNavAreas, (bool), void), asCALL_THISCALL);
    // void DynamicNavigationMesh::SetDrawObstacles(bool enable) | File: ../Navigation/DynamicNavigationMesh.h
    engine->RegisterObjectMethod("DynamicNavigationMesh", "void SetDrawObstacles(bool)", asMETHODPR(DynamicNavigationMesh, SetDrawObstacles, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("DynamicNavigationMesh", "void set_drawObstacles(bool)", asMETHODPR(DynamicNavigationMesh, SetDrawObstacles, (bool), void), asCALL_THISCALL);
    // void NavigationMesh::SetDrawOffMeshConnections(bool enable) | File: ../Navigation/NavigationMesh.h
    engine->RegisterObjectMethod("DynamicNavigationMesh", "void SetDrawOffMeshConnections(bool)", asMETHODPR(DynamicNavigationMesh, SetDrawOffMeshConnections, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("DynamicNavigationMesh", "void set_drawOffMeshConnections(bool)", asMETHODPR(DynamicNavigationMesh, SetDrawOffMeshConnections, (bool), void), asCALL_THISCALL);
    // void NavigationMesh::SetEdgeMaxError(float error) | File: ../Navigation/NavigationMesh.h
    engine->RegisterObjectMethod("DynamicNavigationMesh", "void SetEdgeMaxError(float)", asMETHODPR(DynamicNavigationMesh, SetEdgeMaxError, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("DynamicNavigationMesh", "void set_edgeMaxError(float)", asMETHODPR(DynamicNavigationMesh, SetEdgeMaxError, (float), void), asCALL_THISCALL);
    // void NavigationMesh::SetEdgeMaxLength(float length) | File: ../Navigation/NavigationMesh.h
    engine->RegisterObjectMethod("DynamicNavigationMesh", "void SetEdgeMaxLength(float)", asMETHODPR(DynamicNavigationMesh, SetEdgeMaxLength, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("DynamicNavigationMesh", "void set_edgeMaxLength(float)", asMETHODPR(DynamicNavigationMesh, SetEdgeMaxLength, (float), void), asCALL_THISCALL);
    // void Component::SetEnabled(bool enable) | File: ../Scene/Component.h
    engine->RegisterObjectMethod("DynamicNavigationMesh", "void SetEnabled(bool)", asMETHODPR(DynamicNavigationMesh, SetEnabled, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("DynamicNavigationMesh", "void set_enabled(bool)", asMETHODPR(DynamicNavigationMesh, SetEnabled, (bool), void), asCALL_THISCALL);
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("DynamicNavigationMesh", "void SetGlobalVar(StringHash, const Variant&in)", asMETHODPR(DynamicNavigationMesh, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("DynamicNavigationMesh", "void set_globalVar(StringHash, const Variant&in)", asMETHODPR(DynamicNavigationMesh, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    // void Serializable::SetInstanceDefault(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("DynamicNavigationMesh", "void SetInstanceDefault(bool)", asMETHODPR(DynamicNavigationMesh, SetInstanceDefault, (bool), void), asCALL_THISCALL);
    // void Serializable::SetInterceptNetworkUpdate(const String& attributeName, bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("DynamicNavigationMesh", "void SetInterceptNetworkUpdate(const String&in, bool)", asMETHODPR(DynamicNavigationMesh, SetInterceptNetworkUpdate, (const String&, bool), void), asCALL_THISCALL);
    // void DynamicNavigationMesh::SetMaxLayers(unsigned maxLayers) | File: ../Navigation/DynamicNavigationMesh.h
    engine->RegisterObjectMethod("DynamicNavigationMesh", "void SetMaxLayers(uint)", asMETHODPR(DynamicNavigationMesh, SetMaxLayers, (unsigned), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("DynamicNavigationMesh", "void set_maxLayers(uint)", asMETHODPR(DynamicNavigationMesh, SetMaxLayers, (unsigned), void), asCALL_THISCALL);
    // void DynamicNavigationMesh::SetMaxObstacles(unsigned maxObstacles) | File: ../Navigation/DynamicNavigationMesh.h
    engine->RegisterObjectMethod("DynamicNavigationMesh", "void SetMaxObstacles(uint)", asMETHODPR(DynamicNavigationMesh, SetMaxObstacles, (unsigned), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("DynamicNavigationMesh", "void set_maxObstacles(uint)", asMETHODPR(DynamicNavigationMesh, SetMaxObstacles, (unsigned), void), asCALL_THISCALL);
    // void NavigationMesh::SetMeshName(const String& newName) | File: ../Navigation/NavigationMesh.h
    engine->RegisterObjectMethod("DynamicNavigationMesh", "void SetMeshName(const String&in)", asMETHODPR(DynamicNavigationMesh, SetMeshName, (const String&), void), asCALL_THISCALL);
    // void DynamicNavigationMesh::SetNavigationDataAttr(const PODVector<unsigned char>& value) override | File: ../Navigation/DynamicNavigationMesh.h
    // Error: type "const PODVector<unsigned char>&" can not automatically bind
    // void Animatable::SetObjectAnimation(ObjectAnimation* objectAnimation) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("DynamicNavigationMesh", "void SetObjectAnimation(ObjectAnimation@+)", asMETHODPR(DynamicNavigationMesh, SetObjectAnimation, (ObjectAnimation*), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("DynamicNavigationMesh", "void set_objectAnimation(ObjectAnimation@+)", asMETHODPR(DynamicNavigationMesh, SetObjectAnimation, (ObjectAnimation*), void), asCALL_THISCALL);
    // void Animatable::SetObjectAnimationAttr(const ResourceRef& value) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("DynamicNavigationMesh", "void SetObjectAnimationAttr(const ResourceRef&in)", asMETHODPR(DynamicNavigationMesh, SetObjectAnimationAttr, (const ResourceRef&), void), asCALL_THISCALL);
    // void NavigationMesh::SetPadding(const Vector3& padding) | File: ../Navigation/NavigationMesh.h
    engine->RegisterObjectMethod("DynamicNavigationMesh", "void SetPadding(const Vector3&in)", asMETHODPR(DynamicNavigationMesh, SetPadding, (const Vector3&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("DynamicNavigationMesh", "void set_padding(const Vector3&in)", asMETHODPR(DynamicNavigationMesh, SetPadding, (const Vector3&), void), asCALL_THISCALL);
    // void NavigationMesh::SetPartitionType(NavmeshPartitionType partitionType) | File: ../Navigation/NavigationMesh.h
    engine->RegisterObjectMethod("DynamicNavigationMesh", "void SetPartitionType(NavmeshPartitionType)", asMETHODPR(DynamicNavigationMesh, SetPartitionType, (NavmeshPartitionType), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("DynamicNavigationMesh", "void set_partitionType(NavmeshPartitionType)", asMETHODPR(DynamicNavigationMesh, SetPartitionType, (NavmeshPartitionType), void), asCALL_THISCALL);
    // void NavigationMesh::SetRegionMergeSize(float size) | File: ../Navigation/NavigationMesh.h
    engine->RegisterObjectMethod("DynamicNavigationMesh", "void SetRegionMergeSize(float)", asMETHODPR(DynamicNavigationMesh, SetRegionMergeSize, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("DynamicNavigationMesh", "void set_regionMergeSize(float)", asMETHODPR(DynamicNavigationMesh, SetRegionMergeSize, (float), void), asCALL_THISCALL);
    // void NavigationMesh::SetRegionMinSize(float size) | File: ../Navigation/NavigationMesh.h
    engine->RegisterObjectMethod("DynamicNavigationMesh", "void SetRegionMinSize(float)", asMETHODPR(DynamicNavigationMesh, SetRegionMinSize, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("DynamicNavigationMesh", "void set_regionMinSize(float)", asMETHODPR(DynamicNavigationMesh, SetRegionMinSize, (float), void), asCALL_THISCALL);
    // void Serializable::SetTemporary(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("DynamicNavigationMesh", "void SetTemporary(bool)", asMETHODPR(DynamicNavigationMesh, SetTemporary, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("DynamicNavigationMesh", "void set_temporary(bool)", asMETHODPR(DynamicNavigationMesh, SetTemporary, (bool), void), asCALL_THISCALL);
    // void NavigationMesh::SetTileSize(int size) | File: ../Navigation/NavigationMesh.h
    engine->RegisterObjectMethod("DynamicNavigationMesh", "void SetTileSize(int)", asMETHODPR(DynamicNavigationMesh, SetTileSize, (int), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("DynamicNavigationMesh", "void set_tileSize(int)", asMETHODPR(DynamicNavigationMesh, SetTileSize, (int), void), asCALL_THISCALL);
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod("DynamicNavigationMesh", "void UnsubscribeFromAllEvents()", asMETHODPR(DynamicNavigationMesh, UnsubscribeFromAllEvents, (), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("DynamicNavigationMesh", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", asFUNCTION(DynamicNavigationMesh_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), asCALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("DynamicNavigationMesh", "void UnsubscribeFromEvent(StringHash)", asMETHODPR(DynamicNavigationMesh, UnsubscribeFromEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("DynamicNavigationMesh", "void UnsubscribeFromEvent(Object@+, StringHash)", asMETHODPR(DynamicNavigationMesh, UnsubscribeFromEvent, (Object*, StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("DynamicNavigationMesh", "void UnsubscribeFromEvents(Object@+)", asMETHODPR(DynamicNavigationMesh, UnsubscribeFromEvents, (Object*), void), asCALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("DynamicNavigationMesh", "int WeakRefs() const", asMETHODPR(DynamicNavigationMesh, WeakRefs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("DynamicNavigationMesh", "int get_weakRefs() const", asMETHODPR(DynamicNavigationMesh, WeakRefs, () const, int), asCALL_THISCALL);
    // void Serializable::WriteDeltaUpdate(Serializer& dest, const DirtyBits& attributeBits, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("DynamicNavigationMesh", "void WriteDeltaUpdate(Serializer&, const DirtyBits&in, uint8)", asMETHODPR(DynamicNavigationMesh, WriteDeltaUpdate, (Serializer&, const DirtyBits&, unsigned char), void), asCALL_THISCALL);
    // void Serializable::WriteInitialDeltaUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("DynamicNavigationMesh", "void WriteInitialDeltaUpdate(Serializer&, uint8)", asMETHODPR(DynamicNavigationMesh, WriteInitialDeltaUpdate, (Serializer&, unsigned char), void), asCALL_THISCALL);
    // void Serializable::WriteLatestDataUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("DynamicNavigationMesh", "void WriteLatestDataUpdate(Serializer&, uint8)", asMETHODPR(DynamicNavigationMesh, WriteLatestDataUpdate, (Serializer&, unsigned char), void), asCALL_THISCALL);
#ifdef REGISTER_MANUAL_PART_NavigationMesh
    REGISTER_MANUAL_PART_NavigationMesh(DynamicNavigationMesh, "DynamicNavigationMesh")
#endif
#ifdef REGISTER_MANUAL_PART_Component
    REGISTER_MANUAL_PART_Component(DynamicNavigationMesh, "DynamicNavigationMesh")
#endif
#ifdef REGISTER_MANUAL_PART_Animatable
    REGISTER_MANUAL_PART_Animatable(DynamicNavigationMesh, "DynamicNavigationMesh")
#endif
#ifdef REGISTER_MANUAL_PART_Serializable
    REGISTER_MANUAL_PART_Serializable(DynamicNavigationMesh, "DynamicNavigationMesh")
#endif
#ifdef REGISTER_MANUAL_PART_Object
    REGISTER_MANUAL_PART_Object(DynamicNavigationMesh, "DynamicNavigationMesh")
#endif
#ifdef REGISTER_MANUAL_PART_RefCounted
    REGISTER_MANUAL_PART_RefCounted(DynamicNavigationMesh, "DynamicNavigationMesh")
#endif
#ifdef REGISTER_MANUAL_PART_DynamicNavigationMesh
    REGISTER_MANUAL_PART_DynamicNavigationMesh(DynamicNavigationMesh, "DynamicNavigationMesh")
#endif
    RegisterSubclass<NavigationMesh, DynamicNavigationMesh>(engine, "NavigationMesh", "DynamicNavigationMesh");
    RegisterSubclass<Component, DynamicNavigationMesh>(engine, "Component", "DynamicNavigationMesh");
    RegisterSubclass<Animatable, DynamicNavigationMesh>(engine, "Animatable", "DynamicNavigationMesh");
    RegisterSubclass<Serializable, DynamicNavigationMesh>(engine, "Serializable", "DynamicNavigationMesh");
    RegisterSubclass<Object, DynamicNavigationMesh>(engine, "Object", "DynamicNavigationMesh");
    RegisterSubclass<RefCounted, DynamicNavigationMesh>(engine, "RefCounted", "DynamicNavigationMesh");
#endif

    // unsigned DebugLine::color_ | File: ../Graphics/DebugRenderer.h
    engine->RegisterObjectProperty("DebugLine", "uint color", offsetof(DebugLine, color_));
    // Vector3 DebugLine::end_ | File: ../Graphics/DebugRenderer.h
    engine->RegisterObjectProperty("DebugLine", "Vector3 end", offsetof(DebugLine, end_));
    // Vector3 DebugLine::start_ | File: ../Graphics/DebugRenderer.h
    engine->RegisterObjectProperty("DebugLine", "Vector3 start", offsetof(DebugLine, start_));
    // DebugLine::DebugLine(const Vector3& start, const Vector3& end, unsigned color) | File: ../Graphics/DebugRenderer.h
    engine->RegisterObjectBehaviour("DebugLine", asBEHAVE_CONSTRUCT, "void f(const Vector3&in, const Vector3&in, uint)", asFUNCTION(DebugLine_DebugLine_Vector3_Vector3_unsigned), asCALL_CDECL_OBJFIRST);
    // DebugLine& DebugLine::operator=(const DebugLine&) | Possible implicitly-declared
    RegisterImplicitlyDeclaredAssignOperatorIfPossible<DebugLine>(engine, "DebugLine");
#ifdef REGISTER_MANUAL_PART_DebugLine
    REGISTER_MANUAL_PART_DebugLine(DebugLine, "DebugLine")
#endif

    // unsigned DebugTriangle::color_ | File: ../Graphics/DebugRenderer.h
    engine->RegisterObjectProperty("DebugTriangle", "uint color", offsetof(DebugTriangle, color_));
    // Vector3 DebugTriangle::v1_ | File: ../Graphics/DebugRenderer.h
    engine->RegisterObjectProperty("DebugTriangle", "Vector3 v1", offsetof(DebugTriangle, v1_));
    // Vector3 DebugTriangle::v2_ | File: ../Graphics/DebugRenderer.h
    engine->RegisterObjectProperty("DebugTriangle", "Vector3 v2", offsetof(DebugTriangle, v2_));
    // Vector3 DebugTriangle::v3_ | File: ../Graphics/DebugRenderer.h
    engine->RegisterObjectProperty("DebugTriangle", "Vector3 v3", offsetof(DebugTriangle, v3_));
    // DebugTriangle::DebugTriangle(const Vector3& v1, const Vector3& v2, const Vector3& v3, unsigned color) | File: ../Graphics/DebugRenderer.h
    engine->RegisterObjectBehaviour("DebugTriangle", asBEHAVE_CONSTRUCT, "void f(const Vector3&in, const Vector3&in, const Vector3&in, uint)", asFUNCTION(DebugTriangle_DebugTriangle_Vector3_Vector3_Vector3_unsigned), asCALL_CDECL_OBJFIRST);
    // DebugTriangle& DebugTriangle::operator=(const DebugTriangle&) | Possible implicitly-declared
    RegisterImplicitlyDeclaredAssignOperatorIfPossible<DebugTriangle>(engine, "DebugTriangle");
#ifdef REGISTER_MANUAL_PART_DebugTriangle
    REGISTER_MANUAL_PART_DebugTriangle(DebugTriangle, "DebugTriangle")
#endif

    // BoundingBox Decal::boundingBox_ | File: ../Graphics/DecalSet.h
    engine->RegisterObjectProperty("Decal", "BoundingBox boundingBox", offsetof(Decal, boundingBox_));
    // PODVector<unsigned short> Decal::indices_ | File: ../Graphics/DecalSet.h
    // Error: type "PODVector<unsigned short>" can not automatically bind
    // float Decal::timer_ | File: ../Graphics/DecalSet.h
    engine->RegisterObjectProperty("Decal", "float timer", offsetof(Decal, timer_));
    // float Decal::timeToLive_ | File: ../Graphics/DecalSet.h
    engine->RegisterObjectProperty("Decal", "float timeToLive", offsetof(Decal, timeToLive_));
    // PODVector<DecalVertex> Decal::vertices_ | File: ../Graphics/DecalSet.h
    // Error: type "PODVector<DecalVertex>" can not automatically bind
    // void Decal::AddVertex(const DecalVertex& vertex) | File: ../Graphics/DecalSet.h
    engine->RegisterObjectMethod("Decal", "void AddVertex(const DecalVertex&in)", asMETHODPR(Decal, AddVertex, (const DecalVertex&), void), asCALL_THISCALL);
    // void Decal::CalculateBoundingBox() | File: ../Graphics/DecalSet.h
    engine->RegisterObjectMethod("Decal", "void CalculateBoundingBox()", asMETHODPR(Decal, CalculateBoundingBox, (), void), asCALL_THISCALL);
    // Decal& Decal::operator=(const Decal&) | Possible implicitly-declared
    RegisterImplicitlyDeclaredAssignOperatorIfPossible<Decal>(engine, "Decal");
#ifdef REGISTER_MANUAL_PART_Decal
    REGISTER_MANUAL_PART_Decal(Decal, "Decal")
#endif

    // unsigned char DecalVertex::blendIndices_[4] | File: ../Graphics/DecalSet.h
    // Not registered because array
    // float DecalVertex::blendWeights_[4] | File: ../Graphics/DecalSet.h
    // Not registered because array
    // Vector3 DecalVertex::normal_ | File: ../Graphics/DecalSet.h
    engine->RegisterObjectProperty("DecalVertex", "Vector3 normal", offsetof(DecalVertex, normal_));
    // Vector3 DecalVertex::position_ | File: ../Graphics/DecalSet.h
    engine->RegisterObjectProperty("DecalVertex", "Vector3 position", offsetof(DecalVertex, position_));
    // Vector4 DecalVertex::tangent_ | File: ../Graphics/DecalSet.h
    engine->RegisterObjectProperty("DecalVertex", "Vector4 tangent", offsetof(DecalVertex, tangent_));
    // Vector2 DecalVertex::texCoord_ | File: ../Graphics/DecalSet.h
    engine->RegisterObjectProperty("DecalVertex", "Vector2 texCoord", offsetof(DecalVertex, texCoord_));
    // DecalVertex::DecalVertex(const Vector3& position, const Vector3& normal) | File: ../Graphics/DecalSet.h
    engine->RegisterObjectBehaviour("DecalVertex", asBEHAVE_CONSTRUCT, "void f(const Vector3&in, const Vector3&in)", asFUNCTION(DecalVertex_DecalVertex_Vector3_Vector3), asCALL_CDECL_OBJFIRST);
    // DecalVertex::DecalVertex(const Vector3& position, const Vector3& normal, const float* blendWeights, const unsigned char* blendIndices) | File: ../Graphics/DecalSet.h
    // Error: type "const float*" can not automatically bind
    // DecalVertex& DecalVertex::operator=(const DecalVertex&) | Possible implicitly-declared
    RegisterImplicitlyDeclaredAssignOperatorIfPossible<DecalVertex>(engine, "DecalVertex");
#ifdef REGISTER_MANUAL_PART_DecalVertex
    REGISTER_MANUAL_PART_DecalVertex(DecalVertex, "DecalVertex")
#endif

#ifdef URHO3D_PHYSICS
    // RigidBody* DelayedWorldTransform::parentRigidBody_ | File: ../Physics/PhysicsWorld.h
    // RigidBody* can not be registered
    // RigidBody* DelayedWorldTransform::rigidBody_ | File: ../Physics/PhysicsWorld.h
    // RigidBody* can not be registered
    // Vector3 DelayedWorldTransform::worldPosition_ | File: ../Physics/PhysicsWorld.h
    engine->RegisterObjectProperty("DelayedWorldTransform", "Vector3 worldPosition", offsetof(DelayedWorldTransform, worldPosition_));
    // Quaternion DelayedWorldTransform::worldRotation_ | File: ../Physics/PhysicsWorld.h
    engine->RegisterObjectProperty("DelayedWorldTransform", "Quaternion worldRotation", offsetof(DelayedWorldTransform, worldRotation_));
    // DelayedWorldTransform& DelayedWorldTransform::operator=(const DelayedWorldTransform&) | Possible implicitly-declared
    RegisterImplicitlyDeclaredAssignOperatorIfPossible<DelayedWorldTransform>(engine, "DelayedWorldTransform");
#ifdef REGISTER_MANUAL_PART_DelayedWorldTransform
    REGISTER_MANUAL_PART_DelayedWorldTransform(DelayedWorldTransform, "DelayedWorldTransform")
#endif
#endif

#ifdef URHO3D_URHO2D
    // RigidBody2D* DelayedWorldTransform2D::parentRigidBody_ | File: ../Urho2D/PhysicsWorld2D.h
    // RigidBody2D* can not be registered
    // RigidBody2D* DelayedWorldTransform2D::rigidBody_ | File: ../Urho2D/PhysicsWorld2D.h
    // RigidBody2D* can not be registered
    // Vector3 DelayedWorldTransform2D::worldPosition_ | File: ../Urho2D/PhysicsWorld2D.h
    engine->RegisterObjectProperty("DelayedWorldTransform2D", "Vector3 worldPosition", offsetof(DelayedWorldTransform2D, worldPosition_));
    // Quaternion DelayedWorldTransform2D::worldRotation_ | File: ../Urho2D/PhysicsWorld2D.h
    engine->RegisterObjectProperty("DelayedWorldTransform2D", "Quaternion worldRotation", offsetof(DelayedWorldTransform2D, worldRotation_));
    // DelayedWorldTransform2D& DelayedWorldTransform2D::operator=(const DelayedWorldTransform2D&) | Possible implicitly-declared
    RegisterImplicitlyDeclaredAssignOperatorIfPossible<DelayedWorldTransform2D>(engine, "DelayedWorldTransform2D");
#ifdef REGISTER_MANUAL_PART_DelayedWorldTransform2D
    REGISTER_MANUAL_PART_DelayedWorldTransform2D(DelayedWorldTransform2D, "DelayedWorldTransform2D")
#endif
#endif

    // int DepthValue::max_ | File: ../Graphics/OcclusionBuffer.h
    engine->RegisterObjectProperty("DepthValue", "int max", offsetof(DepthValue, max_));
    // int DepthValue::min_ | File: ../Graphics/OcclusionBuffer.h
    engine->RegisterObjectProperty("DepthValue", "int min", offsetof(DepthValue, min_));
    // DepthValue& DepthValue::operator=(const DepthValue&) | Possible implicitly-declared
    RegisterImplicitlyDeclaredAssignOperatorIfPossible<DepthValue>(engine, "DepthValue");
#ifdef REGISTER_MANUAL_PART_DepthValue
    REGISTER_MANUAL_PART_DepthValue(DepthValue, "DepthValue")
#endif

    // unsigned char DirtyBits::count_ | File: ../Scene/ReplicationState.h
    engine->RegisterObjectProperty("DirtyBits", "uint8 count", offsetof(DirtyBits, count_));
    // unsigned char DirtyBits::data_[MAX_NETWORK_ATTRIBUTES/8] | File: ../Scene/ReplicationState.h
    // Not registered because array
    // void DirtyBits::Clear(unsigned index) | File: ../Scene/ReplicationState.h
    engine->RegisterObjectMethod("DirtyBits", "void Clear(uint)", asMETHODPR(DirtyBits, Clear, (unsigned), void), asCALL_THISCALL);
    // void DirtyBits::ClearAll() | File: ../Scene/ReplicationState.h
    engine->RegisterObjectMethod("DirtyBits", "void ClearAll()", asMETHODPR(DirtyBits, ClearAll, (), void), asCALL_THISCALL);
    // unsigned DirtyBits::Count() const | File: ../Scene/ReplicationState.h
    engine->RegisterObjectMethod("DirtyBits", "uint Count() const", asMETHODPR(DirtyBits, Count, () const, unsigned), asCALL_THISCALL);
    // DirtyBits::DirtyBits(const DirtyBits& bits) | File: ../Scene/ReplicationState.h
    engine->RegisterObjectBehaviour("DirtyBits", asBEHAVE_CONSTRUCT, "void f(const DirtyBits&in)", asFUNCTION(DirtyBits_DirtyBits_DirtyBits), asCALL_CDECL_OBJFIRST);
    // bool DirtyBits::IsSet(unsigned index) const | File: ../Scene/ReplicationState.h
    engine->RegisterObjectMethod("DirtyBits", "bool IsSet(uint) const", asMETHODPR(DirtyBits, IsSet, (unsigned) const, bool), asCALL_THISCALL);
    // void DirtyBits::Set(unsigned index) | File: ../Scene/ReplicationState.h
    engine->RegisterObjectMethod("DirtyBits", "void Set(uint)", asMETHODPR(DirtyBits, Set, (unsigned), void), asCALL_THISCALL);
    // DirtyBits& DirtyBits::operator=(const DirtyBits&) | Possible implicitly-declared
    RegisterImplicitlyDeclaredAssignOperatorIfPossible<DirtyBits>(engine, "DirtyBits");
#ifdef REGISTER_MANUAL_PART_DirtyBits
    REGISTER_MANUAL_PART_DirtyBits(DirtyBits, "DirtyBits")
#endif

}

}
