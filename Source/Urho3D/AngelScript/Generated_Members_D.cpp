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
    engine->RegisterObjectBehaviour("Database", asBEHAVE_ADDREF, "void f()", AS_METHODPR(Database, AddRef, (), void), AS_CALL_THISCALL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // DbConnection* Database::Connect(const String& connectionString) | File: ../Database/Database.h
    engine->RegisterObjectMethod("Database", "DbConnection@+ Connect(const String&in)", AS_METHODPR(Database, Connect, (const String&), DbConnection*), AS_CALL_THISCALL);
    // explicit Database::Database(Context* context) | File: ../Database/Database.h
    engine->RegisterObjectBehaviour("Database", asBEHAVE_FACTORY, "Database@+ f()", AS_FUNCTION(Database_Database_Context), AS_CALL_CDECL);
    // void Database::Disconnect(DbConnection* connection) | File: ../Database/Database.h
    engine->RegisterObjectMethod("Database", "void Disconnect(DbConnection@+)", AS_METHODPR(Database, Disconnect, (DbConnection*), void), AS_CALL_THISCALL);
    // static DBAPI Database::GetAPI() | File: ../Database/Database.h
    engine->SetDefaultNamespace("Database");
    engine->RegisterGlobalFunction("DBAPI GetAPI()", AS_FUNCTIONPR(Database::GetAPI, (), DBAPI), AS_CALL_CDECL);
    engine->SetDefaultNamespace("");
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Database", "bool GetBlockEvents() const", AS_METHODPR(Database, GetBlockEvents, () const, bool), AS_CALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Database", "const String& GetCategory() const", AS_METHODPR(Database, GetCategory, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Database", "const String& get_category() const", AS_METHODPR(Database, GetCategory, () const, const String&), AS_CALL_THISCALL);
    // Context* Object::GetContext() const | File: ../Core/Object.h
    // Error: type "Context*" can used only as function parameter
    // VariantMap& Object::GetEventDataMap() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Database", "VariantMap& GetEventDataMap() const", AS_METHODPR(Database, GetEventDataMap, () const, VariantMap&), AS_CALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Database", "Object@+ GetEventSender() const", AS_METHODPR(Database, GetEventSender, () const, Object*), AS_CALL_THISCALL);
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Database", "const Variant& GetGlobalVar(StringHash) const", AS_METHODPR(Database, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Database", "const Variant& get_globalVar(StringHash) const", AS_METHODPR(Database, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Database", "const VariantMap& GetGlobalVars() const", AS_METHODPR(Database, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Database", "const VariantMap& get_globalVars() const", AS_METHODPR(Database, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    // unsigned Database::GetPoolSize() const | File: ../Database/Database.h
    engine->RegisterObjectMethod("Database", "uint GetPoolSize() const", AS_METHODPR(Database, GetPoolSize, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Database", "uint get_poolSize() const", AS_METHODPR(Database, GetPoolSize, () const, unsigned), AS_CALL_THISCALL);
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Database", "Object@+ GetSubsystem(StringHash) const", AS_METHODPR(Database, GetSubsystem, (StringHash) const, Object*), AS_CALL_THISCALL);
    // template<class T> T* Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("Database", "StringHash GetType() const", AS_METHODPR(Database, GetType, () const, StringHash), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Database", "StringHash get_type() const", AS_METHODPR(Database, GetType, () const, StringHash), AS_CALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("Database", "const String& GetTypeName() const", AS_METHODPR(Database, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Database", "const String& get_typeName() const", AS_METHODPR(Database, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Database", "bool HasEventHandlers() const", AS_METHODPR(Database, HasEventHandlers, () const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Database", "bool HasSubscribedToEvent(StringHash) const", AS_METHODPR(Database, HasSubscribedToEvent, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Database", "bool HasSubscribedToEvent(Object@+, StringHash) const", AS_METHODPR(Database, HasSubscribedToEvent, (Object*, StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Database", "bool IsInstanceOf(StringHash) const", AS_METHODPR(Database, IsInstanceOf, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // bool Database::IsPooling() const | File: ../Database/Database.h
    engine->RegisterObjectMethod("Database", "bool IsPooling() const", AS_METHODPR(Database, IsPooling, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Database", "bool get_pooling() const", AS_METHODPR(Database, IsPooling, () const, bool), AS_CALL_THISCALL);
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Database", "void OnEvent(Object@+, StringHash, VariantMap&)", AS_METHODPR(Database, OnEvent, (Object*, StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("Database", "int Refs() const", AS_METHODPR(Database, Refs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Database", "int get_refs() const", AS_METHODPR(Database, Refs, () const, int), AS_CALL_THISCALL);
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("Database", asBEHAVE_RELEASE, "void f()", AS_METHODPR(Database, ReleaseRef, (), void), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Database", "void SendEvent(StringHash)", AS_METHODPR(Database, SendEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Database", "void SendEvent(StringHash, VariantMap&)", AS_METHODPR(Database, SendEvent, (StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Database", "void SetBlockEvents(bool)", AS_METHODPR(Database, SetBlockEvents, (bool), void), AS_CALL_THISCALL);
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Database", "void SetGlobalVar(StringHash, const Variant&in)", AS_METHODPR(Database, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Database", "void set_globalVar(StringHash, const Variant&in)", AS_METHODPR(Database, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    // void Database::SetPoolSize(unsigned poolSize) | File: ../Database/Database.h
    engine->RegisterObjectMethod("Database", "void SetPoolSize(uint)", AS_METHODPR(Database, SetPoolSize, (unsigned), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Database", "void set_poolSize(uint)", AS_METHODPR(Database, SetPoolSize, (unsigned), void), AS_CALL_THISCALL);
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod("Database", "void UnsubscribeFromAllEvents()", AS_METHODPR(Database, UnsubscribeFromAllEvents, (), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Database", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", AS_FUNCTION_OBJFIRST(Database_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), AS_CALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Database", "void UnsubscribeFromEvent(StringHash)", AS_METHODPR(Database, UnsubscribeFromEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Database", "void UnsubscribeFromEvent(Object@+, StringHash)", AS_METHODPR(Database, UnsubscribeFromEvent, (Object*, StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Database", "void UnsubscribeFromEvents(Object@+)", AS_METHODPR(Database, UnsubscribeFromEvents, (Object*), void), AS_CALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("Database", "int WeakRefs() const", AS_METHODPR(Database, WeakRefs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Database", "int get_weakRefs() const", AS_METHODPR(Database, WeakRefs, () const, int), AS_CALL_THISCALL);
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
    engine->RegisterObjectBehaviour("DebugHud", asBEHAVE_ADDREF, "void f()", AS_METHODPR(DebugHud, AddRef, (), void), AS_CALL_THISCALL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // void DebugHud::ClearAppStats() | File: ../Engine/DebugHud.h
    engine->RegisterObjectMethod("DebugHud", "void ClearAppStats()", AS_METHODPR(DebugHud, ClearAppStats, (), void), AS_CALL_THISCALL);
    // explicit DebugHud::DebugHud(Context* context) | File: ../Engine/DebugHud.h
    engine->RegisterObjectBehaviour("DebugHud", asBEHAVE_FACTORY, "DebugHud@+ f()", AS_FUNCTION(DebugHud_DebugHud_Context), AS_CALL_CDECL);
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("DebugHud", "bool GetBlockEvents() const", AS_METHODPR(DebugHud, GetBlockEvents, () const, bool), AS_CALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("DebugHud", "const String& GetCategory() const", AS_METHODPR(DebugHud, GetCategory, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DebugHud", "const String& get_category() const", AS_METHODPR(DebugHud, GetCategory, () const, const String&), AS_CALL_THISCALL);
    // Context* Object::GetContext() const | File: ../Core/Object.h
    // Error: type "Context*" can used only as function parameter
    // XMLFile* DebugHud::GetDefaultStyle() const | File: ../Engine/DebugHud.h
    engine->RegisterObjectMethod("DebugHud", "XMLFile@+ GetDefaultStyle() const", AS_METHODPR(DebugHud, GetDefaultStyle, () const, XMLFile*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DebugHud", "XMLFile@+ get_defaultStyle() const", AS_METHODPR(DebugHud, GetDefaultStyle, () const, XMLFile*), AS_CALL_THISCALL);
    // VariantMap& Object::GetEventDataMap() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("DebugHud", "VariantMap& GetEventDataMap() const", AS_METHODPR(DebugHud, GetEventDataMap, () const, VariantMap&), AS_CALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("DebugHud", "Object@+ GetEventSender() const", AS_METHODPR(DebugHud, GetEventSender, () const, Object*), AS_CALL_THISCALL);
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("DebugHud", "const Variant& GetGlobalVar(StringHash) const", AS_METHODPR(DebugHud, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DebugHud", "const Variant& get_globalVar(StringHash) const", AS_METHODPR(DebugHud, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("DebugHud", "const VariantMap& GetGlobalVars() const", AS_METHODPR(DebugHud, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DebugHud", "const VariantMap& get_globalVars() const", AS_METHODPR(DebugHud, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    // Text* DebugHud::GetMemoryText() const | File: ../Engine/DebugHud.h
    engine->RegisterObjectMethod("DebugHud", "Text@+ GetMemoryText() const", AS_METHODPR(DebugHud, GetMemoryText, () const, Text*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DebugHud", "Text@+ get_memoryText() const", AS_METHODPR(DebugHud, GetMemoryText, () const, Text*), AS_CALL_THISCALL);
    // unsigned DebugHud::GetMode() const | File: ../Engine/DebugHud.h
    engine->RegisterObjectMethod("DebugHud", "uint GetMode() const", AS_METHODPR(DebugHud, GetMode, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DebugHud", "uint get_mode() const", AS_METHODPR(DebugHud, GetMode, () const, unsigned), AS_CALL_THISCALL);
    // Text* DebugHud::GetModeText() const | File: ../Engine/DebugHud.h
    engine->RegisterObjectMethod("DebugHud", "Text@+ GetModeText() const", AS_METHODPR(DebugHud, GetModeText, () const, Text*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DebugHud", "Text@+ get_modeText() const", AS_METHODPR(DebugHud, GetModeText, () const, Text*), AS_CALL_THISCALL);
    // float DebugHud::GetProfilerInterval() const | File: ../Engine/DebugHud.h
    engine->RegisterObjectMethod("DebugHud", "float GetProfilerInterval() const", AS_METHODPR(DebugHud, GetProfilerInterval, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DebugHud", "float get_profilerInterval() const", AS_METHODPR(DebugHud, GetProfilerInterval, () const, float), AS_CALL_THISCALL);
    // unsigned DebugHud::GetProfilerMaxDepth() const | File: ../Engine/DebugHud.h
    engine->RegisterObjectMethod("DebugHud", "uint GetProfilerMaxDepth() const", AS_METHODPR(DebugHud, GetProfilerMaxDepth, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DebugHud", "uint get_profilerMaxDepth() const", AS_METHODPR(DebugHud, GetProfilerMaxDepth, () const, unsigned), AS_CALL_THISCALL);
    // Text* DebugHud::GetProfilerText() const | File: ../Engine/DebugHud.h
    engine->RegisterObjectMethod("DebugHud", "Text@+ GetProfilerText() const", AS_METHODPR(DebugHud, GetProfilerText, () const, Text*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DebugHud", "Text@+ get_profilerText() const", AS_METHODPR(DebugHud, GetProfilerText, () const, Text*), AS_CALL_THISCALL);
    // Text* DebugHud::GetStatsText() const | File: ../Engine/DebugHud.h
    engine->RegisterObjectMethod("DebugHud", "Text@+ GetStatsText() const", AS_METHODPR(DebugHud, GetStatsText, () const, Text*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DebugHud", "Text@+ get_statsText() const", AS_METHODPR(DebugHud, GetStatsText, () const, Text*), AS_CALL_THISCALL);
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("DebugHud", "Object@+ GetSubsystem(StringHash) const", AS_METHODPR(DebugHud, GetSubsystem, (StringHash) const, Object*), AS_CALL_THISCALL);
    // template<class T> T* Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("DebugHud", "StringHash GetType() const", AS_METHODPR(DebugHud, GetType, () const, StringHash), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DebugHud", "StringHash get_type() const", AS_METHODPR(DebugHud, GetType, () const, StringHash), AS_CALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("DebugHud", "const String& GetTypeName() const", AS_METHODPR(DebugHud, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DebugHud", "const String& get_typeName() const", AS_METHODPR(DebugHud, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    // bool DebugHud::GetUseRendererStats() const | File: ../Engine/DebugHud.h
    engine->RegisterObjectMethod("DebugHud", "bool GetUseRendererStats() const", AS_METHODPR(DebugHud, GetUseRendererStats, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DebugHud", "bool get_useRendererStats() const", AS_METHODPR(DebugHud, GetUseRendererStats, () const, bool), AS_CALL_THISCALL);
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("DebugHud", "bool HasEventHandlers() const", AS_METHODPR(DebugHud, HasEventHandlers, () const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("DebugHud", "bool HasSubscribedToEvent(StringHash) const", AS_METHODPR(DebugHud, HasSubscribedToEvent, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("DebugHud", "bool HasSubscribedToEvent(Object@+, StringHash) const", AS_METHODPR(DebugHud, HasSubscribedToEvent, (Object*, StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("DebugHud", "bool IsInstanceOf(StringHash) const", AS_METHODPR(DebugHud, IsInstanceOf, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("DebugHud", "void OnEvent(Object@+, StringHash, VariantMap&)", AS_METHODPR(DebugHud, OnEvent, (Object*, StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("DebugHud", "int Refs() const", AS_METHODPR(DebugHud, Refs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DebugHud", "int get_refs() const", AS_METHODPR(DebugHud, Refs, () const, int), AS_CALL_THISCALL);
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("DebugHud", asBEHAVE_RELEASE, "void f()", AS_METHODPR(DebugHud, ReleaseRef, (), void), AS_CALL_THISCALL);
    // bool DebugHud::ResetAppStats(const String& label) | File: ../Engine/DebugHud.h
    engine->RegisterObjectMethod("DebugHud", "bool ResetAppStats(const String&in)", AS_METHODPR(DebugHud, ResetAppStats, (const String&), bool), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("DebugHud", "void SendEvent(StringHash)", AS_METHODPR(DebugHud, SendEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("DebugHud", "void SendEvent(StringHash, VariantMap&)", AS_METHODPR(DebugHud, SendEvent, (StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void DebugHud::SetAppStats(const String& label, const Variant& stats) | File: ../Engine/DebugHud.h
    engine->RegisterObjectMethod("DebugHud", "void SetAppStats(const String&in, const Variant&in)", AS_METHODPR(DebugHud, SetAppStats, (const String&, const Variant&), void), AS_CALL_THISCALL);
    // void DebugHud::SetAppStats(const String& label, const String& stats) | File: ../Engine/DebugHud.h
    engine->RegisterObjectMethod("DebugHud", "void SetAppStats(const String&in, const String&in)", AS_METHODPR(DebugHud, SetAppStats, (const String&, const String&), void), AS_CALL_THISCALL);
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("DebugHud", "void SetBlockEvents(bool)", AS_METHODPR(DebugHud, SetBlockEvents, (bool), void), AS_CALL_THISCALL);
    // void DebugHud::SetDefaultStyle(XMLFile* style) | File: ../Engine/DebugHud.h
    engine->RegisterObjectMethod("DebugHud", "void SetDefaultStyle(XMLFile@+)", AS_METHODPR(DebugHud, SetDefaultStyle, (XMLFile*), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DebugHud", "void set_defaultStyle(XMLFile@+)", AS_METHODPR(DebugHud, SetDefaultStyle, (XMLFile*), void), AS_CALL_THISCALL);
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("DebugHud", "void SetGlobalVar(StringHash, const Variant&in)", AS_METHODPR(DebugHud, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DebugHud", "void set_globalVar(StringHash, const Variant&in)", AS_METHODPR(DebugHud, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    // void DebugHud::SetMode(unsigned mode) | File: ../Engine/DebugHud.h
    engine->RegisterObjectMethod("DebugHud", "void SetMode(uint)", AS_METHODPR(DebugHud, SetMode, (unsigned), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DebugHud", "void set_mode(uint)", AS_METHODPR(DebugHud, SetMode, (unsigned), void), AS_CALL_THISCALL);
    // void DebugHud::SetProfilerInterval(float interval) | File: ../Engine/DebugHud.h
    engine->RegisterObjectMethod("DebugHud", "void SetProfilerInterval(float)", AS_METHODPR(DebugHud, SetProfilerInterval, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DebugHud", "void set_profilerInterval(float)", AS_METHODPR(DebugHud, SetProfilerInterval, (float), void), AS_CALL_THISCALL);
    // void DebugHud::SetProfilerMaxDepth(unsigned depth) | File: ../Engine/DebugHud.h
    engine->RegisterObjectMethod("DebugHud", "void SetProfilerMaxDepth(uint)", AS_METHODPR(DebugHud, SetProfilerMaxDepth, (unsigned), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DebugHud", "void set_profilerMaxDepth(uint)", AS_METHODPR(DebugHud, SetProfilerMaxDepth, (unsigned), void), AS_CALL_THISCALL);
    // void DebugHud::SetUseRendererStats(bool enable) | File: ../Engine/DebugHud.h
    engine->RegisterObjectMethod("DebugHud", "void SetUseRendererStats(bool)", AS_METHODPR(DebugHud, SetUseRendererStats, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DebugHud", "void set_useRendererStats(bool)", AS_METHODPR(DebugHud, SetUseRendererStats, (bool), void), AS_CALL_THISCALL);
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void DebugHud::Toggle(unsigned mode) | File: ../Engine/DebugHud.h
    engine->RegisterObjectMethod("DebugHud", "void Toggle(uint)", AS_METHODPR(DebugHud, Toggle, (unsigned), void), AS_CALL_THISCALL);
    // void DebugHud::ToggleAll() | File: ../Engine/DebugHud.h
    engine->RegisterObjectMethod("DebugHud", "void ToggleAll()", AS_METHODPR(DebugHud, ToggleAll, (), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod("DebugHud", "void UnsubscribeFromAllEvents()", AS_METHODPR(DebugHud, UnsubscribeFromAllEvents, (), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("DebugHud", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", AS_FUNCTION_OBJFIRST(DebugHud_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), AS_CALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("DebugHud", "void UnsubscribeFromEvent(StringHash)", AS_METHODPR(DebugHud, UnsubscribeFromEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("DebugHud", "void UnsubscribeFromEvent(Object@+, StringHash)", AS_METHODPR(DebugHud, UnsubscribeFromEvent, (Object*, StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("DebugHud", "void UnsubscribeFromEvents(Object@+)", AS_METHODPR(DebugHud, UnsubscribeFromEvents, (Object*), void), AS_CALL_THISCALL);
    // void DebugHud::Update() | File: ../Engine/DebugHud.h
    engine->RegisterObjectMethod("DebugHud", "void Update()", AS_METHODPR(DebugHud, Update, (), void), AS_CALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("DebugHud", "int WeakRefs() const", AS_METHODPR(DebugHud, WeakRefs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DebugHud", "int get_weakRefs() const", AS_METHODPR(DebugHud, WeakRefs, () const, int), AS_CALL_THISCALL);
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
    engine->RegisterObjectMethod("DebugRenderer", "void AddBoundingBox(const BoundingBox&in, const Color&in, bool = true, bool = false)", AS_METHODPR(DebugRenderer, AddBoundingBox, (const BoundingBox&, const Color&, bool, bool), void), AS_CALL_THISCALL);
    // void DebugRenderer::AddBoundingBox(const BoundingBox& box, const Matrix3x4& transform, const Color& color, bool depthTest=true, bool solid=false) | File: ../Graphics/DebugRenderer.h
    engine->RegisterObjectMethod("DebugRenderer", "void AddBoundingBox(const BoundingBox&in, const Matrix3x4&in, const Color&in, bool = true, bool = false)", AS_METHODPR(DebugRenderer, AddBoundingBox, (const BoundingBox&, const Matrix3x4&, const Color&, bool, bool), void), AS_CALL_THISCALL);
    // void DebugRenderer::AddCircle(const Vector3& center, const Vector3& normal, float radius, const Color& color, int steps=64, bool depthTest=true) | File: ../Graphics/DebugRenderer.h
    engine->RegisterObjectMethod("DebugRenderer", "void AddCircle(const Vector3&in, const Vector3&in, float, const Color&in, int = 64, bool = true)", AS_METHODPR(DebugRenderer, AddCircle, (const Vector3&, const Vector3&, float, const Color&, int, bool), void), AS_CALL_THISCALL);
    // void DebugRenderer::AddCross(const Vector3& center, float size, const Color& color, bool depthTest=true) | File: ../Graphics/DebugRenderer.h
    engine->RegisterObjectMethod("DebugRenderer", "void AddCross(const Vector3&in, float, const Color&in, bool = true)", AS_METHODPR(DebugRenderer, AddCross, (const Vector3&, float, const Color&, bool), void), AS_CALL_THISCALL);
    // void DebugRenderer::AddCylinder(const Vector3& position, float radius, float height, const Color& color, bool depthTest=true) | File: ../Graphics/DebugRenderer.h
    engine->RegisterObjectMethod("DebugRenderer", "void AddCylinder(const Vector3&in, float, float, const Color&in, bool = true)", AS_METHODPR(DebugRenderer, AddCylinder, (const Vector3&, float, float, const Color&, bool), void), AS_CALL_THISCALL);
    // void DebugRenderer::AddFrustum(const Frustum& frustum, const Color& color, bool depthTest=true) | File: ../Graphics/DebugRenderer.h
    engine->RegisterObjectMethod("DebugRenderer", "void AddFrustum(const Frustum&in, const Color&in, bool = true)", AS_METHODPR(DebugRenderer, AddFrustum, (const Frustum&, const Color&, bool), void), AS_CALL_THISCALL);
    // void DebugRenderer::AddLine(const Vector3& start, const Vector3& end, const Color& color, bool depthTest=true) | File: ../Graphics/DebugRenderer.h
    engine->RegisterObjectMethod("DebugRenderer", "void AddLine(const Vector3&in, const Vector3&in, const Color&in, bool = true)", AS_METHODPR(DebugRenderer, AddLine, (const Vector3&, const Vector3&, const Color&, bool), void), AS_CALL_THISCALL);
    // void DebugRenderer::AddLine(const Vector3& start, const Vector3& end, unsigned color, bool depthTest=true) | File: ../Graphics/DebugRenderer.h
    engine->RegisterObjectMethod("DebugRenderer", "void AddLine(const Vector3&in, const Vector3&in, uint, bool = true)", AS_METHODPR(DebugRenderer, AddLine, (const Vector3&, const Vector3&, unsigned, bool), void), AS_CALL_THISCALL);
    // void DebugRenderer::AddNode(Node* node, float scale=1.0f, bool depthTest=true) | File: ../Graphics/DebugRenderer.h
    engine->RegisterObjectMethod("DebugRenderer", "void AddNode(Node@+, float = 1.0f, bool = true)", AS_METHODPR(DebugRenderer, AddNode, (Node*, float, bool), void), AS_CALL_THISCALL);
    // void DebugRenderer::AddPolygon(const Vector3& v1, const Vector3& v2, const Vector3& v3, const Vector3& v4, const Color& color, bool depthTest=true) | File: ../Graphics/DebugRenderer.h
    engine->RegisterObjectMethod("DebugRenderer", "void AddPolygon(const Vector3&in, const Vector3&in, const Vector3&in, const Vector3&in, const Color&in, bool = true)", AS_METHODPR(DebugRenderer, AddPolygon, (const Vector3&, const Vector3&, const Vector3&, const Vector3&, const Color&, bool), void), AS_CALL_THISCALL);
    // void DebugRenderer::AddPolygon(const Vector3& v1, const Vector3& v2, const Vector3& v3, const Vector3& v4, unsigned color, bool depthTest=true) | File: ../Graphics/DebugRenderer.h
    engine->RegisterObjectMethod("DebugRenderer", "void AddPolygon(const Vector3&in, const Vector3&in, const Vector3&in, const Vector3&in, uint, bool = true)", AS_METHODPR(DebugRenderer, AddPolygon, (const Vector3&, const Vector3&, const Vector3&, const Vector3&, unsigned, bool), void), AS_CALL_THISCALL);
    // void DebugRenderer::AddPolyhedron(const Polyhedron& poly, const Color& color, bool depthTest=true) | File: ../Graphics/DebugRenderer.h
    engine->RegisterObjectMethod("DebugRenderer", "void AddPolyhedron(const Polyhedron&in, const Color&in, bool = true)", AS_METHODPR(DebugRenderer, AddPolyhedron, (const Polyhedron&, const Color&, bool), void), AS_CALL_THISCALL);
    // void DebugRenderer::AddQuad(const Vector3& center, float width, float height, const Color& color, bool depthTest=true) | File: ../Graphics/DebugRenderer.h
    engine->RegisterObjectMethod("DebugRenderer", "void AddQuad(const Vector3&in, float, float, const Color&in, bool = true)", AS_METHODPR(DebugRenderer, AddQuad, (const Vector3&, float, float, const Color&, bool), void), AS_CALL_THISCALL);
    // void RefCounted::AddRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("DebugRenderer", asBEHAVE_ADDREF, "void f()", AS_METHODPR(DebugRenderer, AddRef, (), void), AS_CALL_THISCALL);
    // void Component::AddReplicationState(ComponentReplicationState* state) | File: ../Scene/Component.h
    // Error: type "ComponentReplicationState*" can not automatically bind
    // void DebugRenderer::AddSkeleton(const Skeleton& skeleton, const Color& color, bool depthTest=true) | File: ../Graphics/DebugRenderer.h
    engine->RegisterObjectMethod("DebugRenderer", "void AddSkeleton(const Skeleton&in, const Color&in, bool = true)", AS_METHODPR(DebugRenderer, AddSkeleton, (const Skeleton&, const Color&, bool), void), AS_CALL_THISCALL);
    // void DebugRenderer::AddSphere(const Sphere& sphere, const Color& color, bool depthTest=true) | File: ../Graphics/DebugRenderer.h
    engine->RegisterObjectMethod("DebugRenderer", "void AddSphere(const Sphere&in, const Color&in, bool = true)", AS_METHODPR(DebugRenderer, AddSphere, (const Sphere&, const Color&, bool), void), AS_CALL_THISCALL);
    // void DebugRenderer::AddSphereSector(const Sphere& sphere, const Quaternion& rotation, float angle, bool drawLines, const Color& color, bool depthTest=true) | File: ../Graphics/DebugRenderer.h
    engine->RegisterObjectMethod("DebugRenderer", "void AddSphereSector(const Sphere&in, const Quaternion&in, float, bool, const Color&in, bool = true)", AS_METHODPR(DebugRenderer, AddSphereSector, (const Sphere&, const Quaternion&, float, bool, const Color&, bool), void), AS_CALL_THISCALL);
    // void DebugRenderer::AddTriangle(const Vector3& v1, const Vector3& v2, const Vector3& v3, const Color& color, bool depthTest=true) | File: ../Graphics/DebugRenderer.h
    engine->RegisterObjectMethod("DebugRenderer", "void AddTriangle(const Vector3&in, const Vector3&in, const Vector3&in, const Color&in, bool = true)", AS_METHODPR(DebugRenderer, AddTriangle, (const Vector3&, const Vector3&, const Vector3&, const Color&, bool), void), AS_CALL_THISCALL);
    // void DebugRenderer::AddTriangle(const Vector3& v1, const Vector3& v2, const Vector3& v3, unsigned color, bool depthTest=true) | File: ../Graphics/DebugRenderer.h
    engine->RegisterObjectMethod("DebugRenderer", "void AddTriangle(const Vector3&in, const Vector3&in, const Vector3&in, uint, bool = true)", AS_METHODPR(DebugRenderer, AddTriangle, (const Vector3&, const Vector3&, const Vector3&, unsigned, bool), void), AS_CALL_THISCALL);
    // void DebugRenderer::AddTriangleMesh(const void* vertexData, unsigned vertexSize, const void* indexData, unsigned indexSize, unsigned indexStart, unsigned indexCount, const Matrix3x4& transform, const Color& color, bool depthTest=true) | File: ../Graphics/DebugRenderer.h
    // Error: type "const void*" can not automatically bind
    // void DebugRenderer::AddTriangleMesh(const void* vertexData, unsigned vertexSize, unsigned vertexStart, const void* indexData, unsigned indexSize, unsigned indexStart, unsigned indexCount, const Matrix3x4& transform, const Color& color, bool depthTest=true) | File: ../Graphics/DebugRenderer.h
    // Error: type "const void*" can not automatically bind
    // void Serializable::AllocateNetworkState() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("DebugRenderer", "void AllocateNetworkState()", AS_METHODPR(DebugRenderer, AllocateNetworkState, (), void), AS_CALL_THISCALL);
    // virtual void Serializable::ApplyAttributes() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("DebugRenderer", "void ApplyAttributes()", AS_METHODPR(DebugRenderer, ApplyAttributes, (), void), AS_CALL_THISCALL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // void Component::CleanupConnection(Connection* connection) | File: ../Scene/Component.h
    // Not registered because have @manualbind mark
    // explicit DebugRenderer::DebugRenderer(Context* context) | File: ../Graphics/DebugRenderer.h
    engine->RegisterObjectBehaviour("DebugRenderer", asBEHAVE_FACTORY, "DebugRenderer@+ f()", AS_FUNCTION(DebugRenderer_DebugRenderer_Context), AS_CALL_CDECL);
    // virtual void Component::DrawDebugGeometry(DebugRenderer* debug, bool depthTest) | File: ../Scene/Component.h
    engine->RegisterObjectMethod("DebugRenderer", "void DrawDebugGeometry(DebugRenderer@+, bool)", AS_METHODPR(DebugRenderer, DrawDebugGeometry, (DebugRenderer*, bool), void), AS_CALL_THISCALL);
    // bool Animatable::GetAnimationEnabled() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("DebugRenderer", "bool GetAnimationEnabled() const", AS_METHODPR(DebugRenderer, GetAnimationEnabled, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DebugRenderer", "bool get_animationEnabled() const", AS_METHODPR(DebugRenderer, GetAnimationEnabled, () const, bool), AS_CALL_THISCALL);
    // Variant Serializable::GetAttribute(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("DebugRenderer", "Variant GetAttribute(uint) const", AS_METHODPR(DebugRenderer, GetAttribute, (unsigned) const, Variant), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DebugRenderer", "Variant get_attributes(uint) const", AS_METHODPR(DebugRenderer, GetAttribute, (unsigned) const, Variant), AS_CALL_THISCALL);
    // Variant Serializable::GetAttribute(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("DebugRenderer", "Variant GetAttribute(const String&in) const", AS_METHODPR(DebugRenderer, GetAttribute, (const String&) const, Variant), AS_CALL_THISCALL);
    // ValueAnimation* Animatable::GetAttributeAnimation(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("DebugRenderer", "ValueAnimation@+ GetAttributeAnimation(const String&in) const", AS_METHODPR(DebugRenderer, GetAttributeAnimation, (const String&) const, ValueAnimation*), AS_CALL_THISCALL);
    // float Animatable::GetAttributeAnimationSpeed(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("DebugRenderer", "float GetAttributeAnimationSpeed(const String&in) const", AS_METHODPR(DebugRenderer, GetAttributeAnimationSpeed, (const String&) const, float), AS_CALL_THISCALL);
    // float Animatable::GetAttributeAnimationTime(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("DebugRenderer", "float GetAttributeAnimationTime(const String&in) const", AS_METHODPR(DebugRenderer, GetAttributeAnimationTime, (const String&) const, float), AS_CALL_THISCALL);
    // WrapMode Animatable::GetAttributeAnimationWrapMode(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("DebugRenderer", "WrapMode GetAttributeAnimationWrapMode(const String&in) const", AS_METHODPR(DebugRenderer, GetAttributeAnimationWrapMode, (const String&) const, WrapMode), AS_CALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("DebugRenderer", "Variant GetAttributeDefault(uint) const", AS_METHODPR(DebugRenderer, GetAttributeDefault, (unsigned) const, Variant), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DebugRenderer", "Variant get_attributeDefaults(uint) const", AS_METHODPR(DebugRenderer, GetAttributeDefault, (unsigned) const, Variant), AS_CALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("DebugRenderer", "Variant GetAttributeDefault(const String&in) const", AS_METHODPR(DebugRenderer, GetAttributeDefault, (const String&) const, Variant), AS_CALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("DebugRenderer", "bool GetBlockEvents() const", AS_METHODPR(DebugRenderer, GetBlockEvents, () const, bool), AS_CALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("DebugRenderer", "const String& GetCategory() const", AS_METHODPR(DebugRenderer, GetCategory, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DebugRenderer", "const String& get_category() const", AS_METHODPR(DebugRenderer, GetCategory, () const, const String&), AS_CALL_THISCALL);
    // Component* Component::GetComponent(StringHash type) const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("DebugRenderer", "Component@+ GetComponent(StringHash) const", AS_METHODPR(DebugRenderer, GetComponent, (StringHash) const, Component*), AS_CALL_THISCALL);
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
    engine->RegisterObjectMethod("DebugRenderer", "VariantMap& GetEventDataMap() const", AS_METHODPR(DebugRenderer, GetEventDataMap, () const, VariantMap&), AS_CALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("DebugRenderer", "Object@+ GetEventSender() const", AS_METHODPR(DebugRenderer, GetEventSender, () const, Object*), AS_CALL_THISCALL);
    // const Frustum& DebugRenderer::GetFrustum() const | File: ../Graphics/DebugRenderer.h
    engine->RegisterObjectMethod("DebugRenderer", "const Frustum& GetFrustum() const", AS_METHODPR(DebugRenderer, GetFrustum, () const, const Frustum&), AS_CALL_THISCALL);
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("DebugRenderer", "const Variant& GetGlobalVar(StringHash) const", AS_METHODPR(DebugRenderer, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DebugRenderer", "const Variant& get_globalVar(StringHash) const", AS_METHODPR(DebugRenderer, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("DebugRenderer", "const VariantMap& GetGlobalVars() const", AS_METHODPR(DebugRenderer, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DebugRenderer", "const VariantMap& get_globalVars() const", AS_METHODPR(DebugRenderer, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    // unsigned Component::GetID() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("DebugRenderer", "uint GetID() const", AS_METHODPR(DebugRenderer, GetID, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DebugRenderer", "uint get_id() const", AS_METHODPR(DebugRenderer, GetID, () const, unsigned), AS_CALL_THISCALL);
    // bool Serializable::GetInterceptNetworkUpdate(const String& attributeName) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("DebugRenderer", "bool GetInterceptNetworkUpdate(const String&in) const", AS_METHODPR(DebugRenderer, GetInterceptNetworkUpdate, (const String&) const, bool), AS_CALL_THISCALL);
    // bool DebugRenderer::GetLineAntiAlias() const | File: ../Graphics/DebugRenderer.h
    engine->RegisterObjectMethod("DebugRenderer", "bool GetLineAntiAlias() const", AS_METHODPR(DebugRenderer, GetLineAntiAlias, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DebugRenderer", "bool get_lineAntiAlias() const", AS_METHODPR(DebugRenderer, GetLineAntiAlias, () const, bool), AS_CALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetNetworkAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // NetworkState* Serializable::GetNetworkState() const | File: ../Scene/Serializable.h
    // Error: type "NetworkState*" can not automatically bind
    // Node* Component::GetNode() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("DebugRenderer", "Node@+ GetNode() const", AS_METHODPR(DebugRenderer, GetNode, () const, Node*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DebugRenderer", "Node@+ get_node() const", AS_METHODPR(DebugRenderer, GetNode, () const, Node*), AS_CALL_THISCALL);
    // unsigned Serializable::GetNumAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("DebugRenderer", "uint GetNumAttributes() const", AS_METHODPR(DebugRenderer, GetNumAttributes, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DebugRenderer", "uint get_numAttributes() const", AS_METHODPR(DebugRenderer, GetNumAttributes, () const, unsigned), AS_CALL_THISCALL);
    // unsigned Serializable::GetNumNetworkAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("DebugRenderer", "uint GetNumNetworkAttributes() const", AS_METHODPR(DebugRenderer, GetNumNetworkAttributes, () const, unsigned), AS_CALL_THISCALL);
    // ObjectAnimation* Animatable::GetObjectAnimation() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("DebugRenderer", "ObjectAnimation@+ GetObjectAnimation() const", AS_METHODPR(DebugRenderer, GetObjectAnimation, () const, ObjectAnimation*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DebugRenderer", "ObjectAnimation@+ get_objectAnimation() const", AS_METHODPR(DebugRenderer, GetObjectAnimation, () const, ObjectAnimation*), AS_CALL_THISCALL);
    // ResourceRef Animatable::GetObjectAnimationAttr() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("DebugRenderer", "ResourceRef GetObjectAnimationAttr() const", AS_METHODPR(DebugRenderer, GetObjectAnimationAttr, () const, ResourceRef), AS_CALL_THISCALL);
    // const Matrix4& DebugRenderer::GetProjection() const | File: ../Graphics/DebugRenderer.h
    engine->RegisterObjectMethod("DebugRenderer", "const Matrix4& GetProjection() const", AS_METHODPR(DebugRenderer, GetProjection, () const, const Matrix4&), AS_CALL_THISCALL);
    // Scene* Component::GetScene() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("DebugRenderer", "Scene@+ GetScene() const", AS_METHODPR(DebugRenderer, GetScene, () const, Scene*), AS_CALL_THISCALL);
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("DebugRenderer", "Object@+ GetSubsystem(StringHash) const", AS_METHODPR(DebugRenderer, GetSubsystem, (StringHash) const, Object*), AS_CALL_THISCALL);
    // template<class T> T* Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("DebugRenderer", "StringHash GetType() const", AS_METHODPR(DebugRenderer, GetType, () const, StringHash), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DebugRenderer", "StringHash get_type() const", AS_METHODPR(DebugRenderer, GetType, () const, StringHash), AS_CALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("DebugRenderer", "const String& GetTypeName() const", AS_METHODPR(DebugRenderer, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DebugRenderer", "const String& get_typeName() const", AS_METHODPR(DebugRenderer, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    // const Matrix3x4& DebugRenderer::GetView() const | File: ../Graphics/DebugRenderer.h
    engine->RegisterObjectMethod("DebugRenderer", "const Matrix3x4& GetView() const", AS_METHODPR(DebugRenderer, GetView, () const, const Matrix3x4&), AS_CALL_THISCALL);
    // bool DebugRenderer::HasContent() const | File: ../Graphics/DebugRenderer.h
    engine->RegisterObjectMethod("DebugRenderer", "bool HasContent() const", AS_METHODPR(DebugRenderer, HasContent, () const, bool), AS_CALL_THISCALL);
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("DebugRenderer", "bool HasEventHandlers() const", AS_METHODPR(DebugRenderer, HasEventHandlers, () const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("DebugRenderer", "bool HasSubscribedToEvent(StringHash) const", AS_METHODPR(DebugRenderer, HasSubscribedToEvent, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("DebugRenderer", "bool HasSubscribedToEvent(Object@+, StringHash) const", AS_METHODPR(DebugRenderer, HasSubscribedToEvent, (Object*, StringHash) const, bool), AS_CALL_THISCALL);
    // bool Component::IsEnabled() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("DebugRenderer", "bool IsEnabled() const", AS_METHODPR(DebugRenderer, IsEnabled, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DebugRenderer", "bool get_enabled() const", AS_METHODPR(DebugRenderer, IsEnabled, () const, bool), AS_CALL_THISCALL);
    // bool Component::IsEnabledEffective() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("DebugRenderer", "bool IsEnabledEffective() const", AS_METHODPR(DebugRenderer, IsEnabledEffective, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DebugRenderer", "bool get_enabledEffective() const", AS_METHODPR(DebugRenderer, IsEnabledEffective, () const, bool), AS_CALL_THISCALL);
    // bool DebugRenderer::IsInside(const BoundingBox& box) const | File: ../Graphics/DebugRenderer.h
    engine->RegisterObjectMethod("DebugRenderer", "bool IsInside(const BoundingBox&in) const", AS_METHODPR(DebugRenderer, IsInside, (const BoundingBox&) const, bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("DebugRenderer", "bool IsInstanceOf(StringHash) const", AS_METHODPR(DebugRenderer, IsInstanceOf, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // bool Component::IsReplicated() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("DebugRenderer", "bool IsReplicated() const", AS_METHODPR(DebugRenderer, IsReplicated, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DebugRenderer", "bool get_replicated() const", AS_METHODPR(DebugRenderer, IsReplicated, () const, bool), AS_CALL_THISCALL);
    // bool Serializable::IsTemporary() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("DebugRenderer", "bool IsTemporary() const", AS_METHODPR(DebugRenderer, IsTemporary, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DebugRenderer", "bool get_temporary() const", AS_METHODPR(DebugRenderer, IsTemporary, () const, bool), AS_CALL_THISCALL);
    // virtual bool Serializable::Load(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("DebugRenderer", "bool Load(Deserializer&)", AS_METHODPR(DebugRenderer, Load, (Deserializer&), bool), AS_CALL_THISCALL);
    // bool Animatable::LoadJSON(const JSONValue& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("DebugRenderer", "bool LoadJSON(const JSONValue&in)", AS_METHODPR(DebugRenderer, LoadJSON, (const JSONValue&), bool), AS_CALL_THISCALL);
    // bool Animatable::LoadXML(const XMLElement& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("DebugRenderer", "bool LoadXML(const XMLElement&in)", AS_METHODPR(DebugRenderer, LoadXML, (const XMLElement&), bool), AS_CALL_THISCALL);
    // void Component::MarkNetworkUpdate() override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("DebugRenderer", "void MarkNetworkUpdate()", AS_METHODPR(DebugRenderer, MarkNetworkUpdate, (), void), AS_CALL_THISCALL);
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("DebugRenderer", "void OnEvent(Object@+, StringHash, VariantMap&)", AS_METHODPR(DebugRenderer, OnEvent, (Object*, StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // virtual void Serializable::OnGetAttribute(const AttributeInfo& attr, Variant& dest) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("DebugRenderer", "void OnGetAttribute(const AttributeInfo&in, Variant&) const", AS_METHODPR(DebugRenderer, OnGetAttribute, (const AttributeInfo&, Variant&) const, void), AS_CALL_THISCALL);
    // virtual void Serializable::OnSetAttribute(const AttributeInfo& attr, const Variant& src) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("DebugRenderer", "void OnSetAttribute(const AttributeInfo&in, const Variant&in)", AS_METHODPR(DebugRenderer, OnSetAttribute, (const AttributeInfo&, const Variant&), void), AS_CALL_THISCALL);
    // virtual void Component::OnSetEnabled() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("DebugRenderer", "void OnSetEnabled()", AS_METHODPR(DebugRenderer, OnSetEnabled, (), void), AS_CALL_THISCALL);
    // void Component::PrepareNetworkUpdate() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("DebugRenderer", "void PrepareNetworkUpdate()", AS_METHODPR(DebugRenderer, PrepareNetworkUpdate, (), void), AS_CALL_THISCALL);
    // bool Serializable::ReadDeltaUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("DebugRenderer", "bool ReadDeltaUpdate(Deserializer&)", AS_METHODPR(DebugRenderer, ReadDeltaUpdate, (Deserializer&), bool), AS_CALL_THISCALL);
    // bool Serializable::ReadLatestDataUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("DebugRenderer", "bool ReadLatestDataUpdate(Deserializer&)", AS_METHODPR(DebugRenderer, ReadLatestDataUpdate, (Deserializer&), bool), AS_CALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("DebugRenderer", "int Refs() const", AS_METHODPR(DebugRenderer, Refs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DebugRenderer", "int get_refs() const", AS_METHODPR(DebugRenderer, Refs, () const, int), AS_CALL_THISCALL);
    // static void DebugRenderer::RegisterObject(Context* context) | File: ../Graphics/DebugRenderer.h
    // Not registered because have @nobind mark
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("DebugRenderer", asBEHAVE_RELEASE, "void f()", AS_METHODPR(DebugRenderer, ReleaseRef, (), void), AS_CALL_THISCALL);
    // void Component::Remove() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("DebugRenderer", "void Remove()", AS_METHODPR(DebugRenderer, Remove, (), void), AS_CALL_THISCALL);
    // void Animatable::RemoveAttributeAnimation(const String& name) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("DebugRenderer", "void RemoveAttributeAnimation(const String&in)", AS_METHODPR(DebugRenderer, RemoveAttributeAnimation, (const String&), void), AS_CALL_THISCALL);
    // void Serializable::RemoveInstanceDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("DebugRenderer", "void RemoveInstanceDefault()", AS_METHODPR(DebugRenderer, RemoveInstanceDefault, (), void), AS_CALL_THISCALL);
    // void Animatable::RemoveObjectAnimation() | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("DebugRenderer", "void RemoveObjectAnimation()", AS_METHODPR(DebugRenderer, RemoveObjectAnimation, (), void), AS_CALL_THISCALL);
    // void DebugRenderer::Render() | File: ../Graphics/DebugRenderer.h
    engine->RegisterObjectMethod("DebugRenderer", "void Render()", AS_METHODPR(DebugRenderer, Render, (), void), AS_CALL_THISCALL);
    // void Serializable::ResetToDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("DebugRenderer", "void ResetToDefault()", AS_METHODPR(DebugRenderer, ResetToDefault, (), void), AS_CALL_THISCALL);
    // bool Component::Save(Serializer& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("DebugRenderer", "bool Save(Serializer&) const", AS_METHODPR(DebugRenderer, Save, (Serializer&) const, bool), AS_CALL_THISCALL);
    // virtual bool Serializable::SaveDefaultAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("DebugRenderer", "bool SaveDefaultAttributes() const", AS_METHODPR(DebugRenderer, SaveDefaultAttributes, () const, bool), AS_CALL_THISCALL);
    // bool Component::SaveJSON(JSONValue& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("DebugRenderer", "bool SaveJSON(JSONValue&) const", AS_METHODPR(DebugRenderer, SaveJSON, (JSONValue&) const, bool), AS_CALL_THISCALL);
    // bool Component::SaveXML(XMLElement& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("DebugRenderer", "bool SaveXML(XMLElement&) const", AS_METHODPR(DebugRenderer, SaveXML, (XMLElement&) const, bool), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("DebugRenderer", "void SendEvent(StringHash)", AS_METHODPR(DebugRenderer, SendEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("DebugRenderer", "void SendEvent(StringHash, VariantMap&)", AS_METHODPR(DebugRenderer, SendEvent, (StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void Animatable::SetAnimationEnabled(bool enable) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("DebugRenderer", "void SetAnimationEnabled(bool)", AS_METHODPR(DebugRenderer, SetAnimationEnabled, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DebugRenderer", "void set_animationEnabled(bool)", AS_METHODPR(DebugRenderer, SetAnimationEnabled, (bool), void), AS_CALL_THISCALL);
    // void Animatable::SetAnimationTime(float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("DebugRenderer", "void SetAnimationTime(float)", AS_METHODPR(DebugRenderer, SetAnimationTime, (float), void), AS_CALL_THISCALL);
    // bool Serializable::SetAttribute(unsigned index, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("DebugRenderer", "bool SetAttribute(uint, const Variant&in)", AS_METHODPR(DebugRenderer, SetAttribute, (unsigned, const Variant&), bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DebugRenderer", "bool set_attributes(uint, const Variant&in)", AS_METHODPR(DebugRenderer, SetAttribute, (unsigned, const Variant&), bool), AS_CALL_THISCALL);
    // bool Serializable::SetAttribute(const String& name, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("DebugRenderer", "bool SetAttribute(const String&in, const Variant&in)", AS_METHODPR(DebugRenderer, SetAttribute, (const String&, const Variant&), bool), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimation(const String& name, ValueAnimation* attributeAnimation, WrapMode wrapMode=WM_LOOP, float speed=1.0f) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("DebugRenderer", "void SetAttributeAnimation(const String&in, ValueAnimation@+, WrapMode = WM_LOOP, float = 1.0f)", AS_METHODPR(DebugRenderer, SetAttributeAnimation, (const String&, ValueAnimation*, WrapMode, float), void), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimationSpeed(const String& name, float speed) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("DebugRenderer", "void SetAttributeAnimationSpeed(const String&in, float)", AS_METHODPR(DebugRenderer, SetAttributeAnimationSpeed, (const String&, float), void), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimationTime(const String& name, float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("DebugRenderer", "void SetAttributeAnimationTime(const String&in, float)", AS_METHODPR(DebugRenderer, SetAttributeAnimationTime, (const String&, float), void), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimationWrapMode(const String& name, WrapMode wrapMode) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("DebugRenderer", "void SetAttributeAnimationWrapMode(const String&in, WrapMode)", AS_METHODPR(DebugRenderer, SetAttributeAnimationWrapMode, (const String&, WrapMode), void), AS_CALL_THISCALL);
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("DebugRenderer", "void SetBlockEvents(bool)", AS_METHODPR(DebugRenderer, SetBlockEvents, (bool), void), AS_CALL_THISCALL);
    // void Component::SetEnabled(bool enable) | File: ../Scene/Component.h
    engine->RegisterObjectMethod("DebugRenderer", "void SetEnabled(bool)", AS_METHODPR(DebugRenderer, SetEnabled, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DebugRenderer", "void set_enabled(bool)", AS_METHODPR(DebugRenderer, SetEnabled, (bool), void), AS_CALL_THISCALL);
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("DebugRenderer", "void SetGlobalVar(StringHash, const Variant&in)", AS_METHODPR(DebugRenderer, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DebugRenderer", "void set_globalVar(StringHash, const Variant&in)", AS_METHODPR(DebugRenderer, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    // void Serializable::SetInstanceDefault(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("DebugRenderer", "void SetInstanceDefault(bool)", AS_METHODPR(DebugRenderer, SetInstanceDefault, (bool), void), AS_CALL_THISCALL);
    // void Serializable::SetInterceptNetworkUpdate(const String& attributeName, bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("DebugRenderer", "void SetInterceptNetworkUpdate(const String&in, bool)", AS_METHODPR(DebugRenderer, SetInterceptNetworkUpdate, (const String&, bool), void), AS_CALL_THISCALL);
    // void DebugRenderer::SetLineAntiAlias(bool enable) | File: ../Graphics/DebugRenderer.h
    engine->RegisterObjectMethod("DebugRenderer", "void SetLineAntiAlias(bool)", AS_METHODPR(DebugRenderer, SetLineAntiAlias, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DebugRenderer", "void set_lineAntiAlias(bool)", AS_METHODPR(DebugRenderer, SetLineAntiAlias, (bool), void), AS_CALL_THISCALL);
    // void Animatable::SetObjectAnimation(ObjectAnimation* objectAnimation) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("DebugRenderer", "void SetObjectAnimation(ObjectAnimation@+)", AS_METHODPR(DebugRenderer, SetObjectAnimation, (ObjectAnimation*), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DebugRenderer", "void set_objectAnimation(ObjectAnimation@+)", AS_METHODPR(DebugRenderer, SetObjectAnimation, (ObjectAnimation*), void), AS_CALL_THISCALL);
    // void Animatable::SetObjectAnimationAttr(const ResourceRef& value) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("DebugRenderer", "void SetObjectAnimationAttr(const ResourceRef&in)", AS_METHODPR(DebugRenderer, SetObjectAnimationAttr, (const ResourceRef&), void), AS_CALL_THISCALL);
    // void Serializable::SetTemporary(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("DebugRenderer", "void SetTemporary(bool)", AS_METHODPR(DebugRenderer, SetTemporary, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DebugRenderer", "void set_temporary(bool)", AS_METHODPR(DebugRenderer, SetTemporary, (bool), void), AS_CALL_THISCALL);
    // void DebugRenderer::SetView(Camera* camera) | File: ../Graphics/DebugRenderer.h
    engine->RegisterObjectMethod("DebugRenderer", "void SetView(Camera@+)", AS_METHODPR(DebugRenderer, SetView, (Camera*), void), AS_CALL_THISCALL);
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod("DebugRenderer", "void UnsubscribeFromAllEvents()", AS_METHODPR(DebugRenderer, UnsubscribeFromAllEvents, (), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("DebugRenderer", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", AS_FUNCTION_OBJFIRST(DebugRenderer_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), AS_CALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("DebugRenderer", "void UnsubscribeFromEvent(StringHash)", AS_METHODPR(DebugRenderer, UnsubscribeFromEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("DebugRenderer", "void UnsubscribeFromEvent(Object@+, StringHash)", AS_METHODPR(DebugRenderer, UnsubscribeFromEvent, (Object*, StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("DebugRenderer", "void UnsubscribeFromEvents(Object@+)", AS_METHODPR(DebugRenderer, UnsubscribeFromEvents, (Object*), void), AS_CALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("DebugRenderer", "int WeakRefs() const", AS_METHODPR(DebugRenderer, WeakRefs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DebugRenderer", "int get_weakRefs() const", AS_METHODPR(DebugRenderer, WeakRefs, () const, int), AS_CALL_THISCALL);
    // void Serializable::WriteDeltaUpdate(Serializer& dest, const DirtyBits& attributeBits, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("DebugRenderer", "void WriteDeltaUpdate(Serializer&, const DirtyBits&in, uint8)", AS_METHODPR(DebugRenderer, WriteDeltaUpdate, (Serializer&, const DirtyBits&, unsigned char), void), AS_CALL_THISCALL);
    // void Serializable::WriteInitialDeltaUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("DebugRenderer", "void WriteInitialDeltaUpdate(Serializer&, uint8)", AS_METHODPR(DebugRenderer, WriteInitialDeltaUpdate, (Serializer&, unsigned char), void), AS_CALL_THISCALL);
    // void Serializable::WriteLatestDataUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("DebugRenderer", "void WriteLatestDataUpdate(Serializer&, uint8)", AS_METHODPR(DebugRenderer, WriteLatestDataUpdate, (Serializer&, unsigned char), void), AS_CALL_THISCALL);
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
    engine->RegisterObjectMethod("DecalSet", "bool AddDecal(Drawable@+, const Vector3&in, const Quaternion&in, float, float, float, const Vector2&in, const Vector2&in, float = 0.0f, float = 0.1f, uint = M_MAX_UNSIGNED)", AS_METHODPR(DecalSet, AddDecal, (Drawable*, const Vector3&, const Quaternion&, float, float, float, const Vector2&, const Vector2&, float, float, unsigned), bool), AS_CALL_THISCALL);
    // void Drawable::AddLight(Light* light) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("DecalSet", "void AddLight(Light@+)", AS_METHODPR(DecalSet, AddLight, (Light*), void), AS_CALL_THISCALL);
    // void RefCounted::AddRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("DecalSet", asBEHAVE_ADDREF, "void f()", AS_METHODPR(DecalSet, AddRef, (), void), AS_CALL_THISCALL);
    // void Component::AddReplicationState(ComponentReplicationState* state) | File: ../Scene/Component.h
    // Error: type "ComponentReplicationState*" can not automatically bind
    // void Drawable::AddVertexLight(Light* light) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("DecalSet", "void AddVertexLight(Light@+)", AS_METHODPR(DecalSet, AddVertexLight, (Light*), void), AS_CALL_THISCALL);
    // void Serializable::AllocateNetworkState() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("DecalSet", "void AllocateNetworkState()", AS_METHODPR(DecalSet, AllocateNetworkState, (), void), AS_CALL_THISCALL);
    // void DecalSet::ApplyAttributes() override | File: ../Graphics/DecalSet.h
    engine->RegisterObjectMethod("DecalSet", "void ApplyAttributes()", AS_METHODPR(DecalSet, ApplyAttributes, (), void), AS_CALL_THISCALL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // void Component::CleanupConnection(Connection* connection) | File: ../Scene/Component.h
    // Not registered because have @manualbind mark
    // explicit DecalSet::DecalSet(Context* context) | File: ../Graphics/DecalSet.h
    engine->RegisterObjectBehaviour("DecalSet", asBEHAVE_FACTORY, "DecalSet@+ f()", AS_FUNCTION(DecalSet_DecalSet_Context), AS_CALL_CDECL);
    // void Drawable::DrawDebugGeometry(DebugRenderer* debug, bool depthTest) override | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("DecalSet", "void DrawDebugGeometry(DebugRenderer@+, bool)", AS_METHODPR(DecalSet, DrawDebugGeometry, (DebugRenderer*, bool), void), AS_CALL_THISCALL);
    // virtual bool Drawable::DrawOcclusion(OcclusionBuffer* buffer) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("DecalSet", "bool DrawOcclusion(OcclusionBuffer@+)", AS_METHODPR(DecalSet, DrawOcclusion, (OcclusionBuffer*), bool), AS_CALL_THISCALL);
    // bool Animatable::GetAnimationEnabled() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("DecalSet", "bool GetAnimationEnabled() const", AS_METHODPR(DecalSet, GetAnimationEnabled, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DecalSet", "bool get_animationEnabled() const", AS_METHODPR(DecalSet, GetAnimationEnabled, () const, bool), AS_CALL_THISCALL);
    // Variant Serializable::GetAttribute(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("DecalSet", "Variant GetAttribute(uint) const", AS_METHODPR(DecalSet, GetAttribute, (unsigned) const, Variant), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DecalSet", "Variant get_attributes(uint) const", AS_METHODPR(DecalSet, GetAttribute, (unsigned) const, Variant), AS_CALL_THISCALL);
    // Variant Serializable::GetAttribute(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("DecalSet", "Variant GetAttribute(const String&in) const", AS_METHODPR(DecalSet, GetAttribute, (const String&) const, Variant), AS_CALL_THISCALL);
    // ValueAnimation* Animatable::GetAttributeAnimation(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("DecalSet", "ValueAnimation@+ GetAttributeAnimation(const String&in) const", AS_METHODPR(DecalSet, GetAttributeAnimation, (const String&) const, ValueAnimation*), AS_CALL_THISCALL);
    // float Animatable::GetAttributeAnimationSpeed(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("DecalSet", "float GetAttributeAnimationSpeed(const String&in) const", AS_METHODPR(DecalSet, GetAttributeAnimationSpeed, (const String&) const, float), AS_CALL_THISCALL);
    // float Animatable::GetAttributeAnimationTime(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("DecalSet", "float GetAttributeAnimationTime(const String&in) const", AS_METHODPR(DecalSet, GetAttributeAnimationTime, (const String&) const, float), AS_CALL_THISCALL);
    // WrapMode Animatable::GetAttributeAnimationWrapMode(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("DecalSet", "WrapMode GetAttributeAnimationWrapMode(const String&in) const", AS_METHODPR(DecalSet, GetAttributeAnimationWrapMode, (const String&) const, WrapMode), AS_CALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("DecalSet", "Variant GetAttributeDefault(uint) const", AS_METHODPR(DecalSet, GetAttributeDefault, (unsigned) const, Variant), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DecalSet", "Variant get_attributeDefaults(uint) const", AS_METHODPR(DecalSet, GetAttributeDefault, (unsigned) const, Variant), AS_CALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("DecalSet", "Variant GetAttributeDefault(const String&in) const", AS_METHODPR(DecalSet, GetAttributeDefault, (const String&) const, Variant), AS_CALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // const Vector<SourceBatch>& Drawable::GetBatches() const | File: ../Graphics/Drawable.h
    // Error: type "const Vector<SourceBatch>&" can not automatically bind
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("DecalSet", "bool GetBlockEvents() const", AS_METHODPR(DecalSet, GetBlockEvents, () const, bool), AS_CALL_THISCALL);
    // const BoundingBox& Drawable::GetBoundingBox() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("DecalSet", "const BoundingBox& GetBoundingBox() const", AS_METHODPR(DecalSet, GetBoundingBox, () const, const BoundingBox&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DecalSet", "const BoundingBox& get_boundingBox() const", AS_METHODPR(DecalSet, GetBoundingBox, () const, const BoundingBox&), AS_CALL_THISCALL);
    // bool Drawable::GetCastShadows() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("DecalSet", "bool GetCastShadows() const", AS_METHODPR(DecalSet, GetCastShadows, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DecalSet", "bool get_castShadows() const", AS_METHODPR(DecalSet, GetCastShadows, () const, bool), AS_CALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("DecalSet", "const String& GetCategory() const", AS_METHODPR(DecalSet, GetCategory, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DecalSet", "const String& get_category() const", AS_METHODPR(DecalSet, GetCategory, () const, const String&), AS_CALL_THISCALL);
    // Component* Component::GetComponent(StringHash type) const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("DecalSet", "Component@+ GetComponent(StringHash) const", AS_METHODPR(DecalSet, GetComponent, (StringHash) const, Component*), AS_CALL_THISCALL);
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
    engine->RegisterObjectMethod("DecalSet", "float GetDistance() const", AS_METHODPR(DecalSet, GetDistance, () const, float), AS_CALL_THISCALL);
    // unsigned char Drawable::GetDrawableFlags() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("DecalSet", "uint8 GetDrawableFlags() const", AS_METHODPR(DecalSet, GetDrawableFlags, () const, unsigned char), AS_CALL_THISCALL);
    // float Drawable::GetDrawDistance() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("DecalSet", "float GetDrawDistance() const", AS_METHODPR(DecalSet, GetDrawDistance, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DecalSet", "float get_drawDistance() const", AS_METHODPR(DecalSet, GetDrawDistance, () const, float), AS_CALL_THISCALL);
    // VariantMap& Object::GetEventDataMap() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("DecalSet", "VariantMap& GetEventDataMap() const", AS_METHODPR(DecalSet, GetEventDataMap, () const, VariantMap&), AS_CALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("DecalSet", "Object@+ GetEventSender() const", AS_METHODPR(DecalSet, GetEventSender, () const, Object*), AS_CALL_THISCALL);
    // Light* Drawable::GetFirstLight() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("DecalSet", "Light@+ GetFirstLight() const", AS_METHODPR(DecalSet, GetFirstLight, () const, Light*), AS_CALL_THISCALL);
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("DecalSet", "const Variant& GetGlobalVar(StringHash) const", AS_METHODPR(DecalSet, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DecalSet", "const Variant& get_globalVar(StringHash) const", AS_METHODPR(DecalSet, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("DecalSet", "const VariantMap& GetGlobalVars() const", AS_METHODPR(DecalSet, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DecalSet", "const VariantMap& get_globalVars() const", AS_METHODPR(DecalSet, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    // unsigned Component::GetID() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("DecalSet", "uint GetID() const", AS_METHODPR(DecalSet, GetID, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DecalSet", "uint get_id() const", AS_METHODPR(DecalSet, GetID, () const, unsigned), AS_CALL_THISCALL);
    // bool Serializable::GetInterceptNetworkUpdate(const String& attributeName) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("DecalSet", "bool GetInterceptNetworkUpdate(const String&in) const", AS_METHODPR(DecalSet, GetInterceptNetworkUpdate, (const String&) const, bool), AS_CALL_THISCALL);
    // unsigned Drawable::GetLightMask() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("DecalSet", "uint GetLightMask() const", AS_METHODPR(DecalSet, GetLightMask, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DecalSet", "uint get_lightMask() const", AS_METHODPR(DecalSet, GetLightMask, () const, unsigned), AS_CALL_THISCALL);
    // const PODVector<Light*>& Drawable::GetLights() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("DecalSet", "Array<Light@>@ GetLights() const", AS_FUNCTION_OBJFIRST(DecalSet_GetLights_void), AS_CALL_CDECL_OBJFIRST);
    // float Drawable::GetLodBias() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("DecalSet", "float GetLodBias() const", AS_METHODPR(DecalSet, GetLodBias, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DecalSet", "float get_lodBias() const", AS_METHODPR(DecalSet, GetLodBias, () const, float), AS_CALL_THISCALL);
    // float Drawable::GetLodDistance() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("DecalSet", "float GetLodDistance() const", AS_METHODPR(DecalSet, GetLodDistance, () const, float), AS_CALL_THISCALL);
    // virtual Geometry* Drawable::GetLodGeometry(unsigned batchIndex, unsigned level) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("DecalSet", "Geometry@+ GetLodGeometry(uint, uint)", AS_METHODPR(DecalSet, GetLodGeometry, (unsigned, unsigned), Geometry*), AS_CALL_THISCALL);
    // Material* DecalSet::GetMaterial() const | File: ../Graphics/DecalSet.h
    engine->RegisterObjectMethod("DecalSet", "Material@+ GetMaterial() const", AS_METHODPR(DecalSet, GetMaterial, () const, Material*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DecalSet", "Material@+ get_material() const", AS_METHODPR(DecalSet, GetMaterial, () const, Material*), AS_CALL_THISCALL);
    // ResourceRef DecalSet::GetMaterialAttr() const | File: ../Graphics/DecalSet.h
    engine->RegisterObjectMethod("DecalSet", "ResourceRef GetMaterialAttr() const", AS_METHODPR(DecalSet, GetMaterialAttr, () const, ResourceRef), AS_CALL_THISCALL);
    // unsigned DecalSet::GetMaxIndices() const | File: ../Graphics/DecalSet.h
    engine->RegisterObjectMethod("DecalSet", "uint GetMaxIndices() const", AS_METHODPR(DecalSet, GetMaxIndices, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DecalSet", "uint get_maxIndices() const", AS_METHODPR(DecalSet, GetMaxIndices, () const, unsigned), AS_CALL_THISCALL);
    // unsigned Drawable::GetMaxLights() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("DecalSet", "uint GetMaxLights() const", AS_METHODPR(DecalSet, GetMaxLights, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DecalSet", "uint get_maxLights() const", AS_METHODPR(DecalSet, GetMaxLights, () const, unsigned), AS_CALL_THISCALL);
    // unsigned DecalSet::GetMaxVertices() const | File: ../Graphics/DecalSet.h
    engine->RegisterObjectMethod("DecalSet", "uint GetMaxVertices() const", AS_METHODPR(DecalSet, GetMaxVertices, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DecalSet", "uint get_maxVertices() const", AS_METHODPR(DecalSet, GetMaxVertices, () const, unsigned), AS_CALL_THISCALL);
    // float Drawable::GetMaxZ() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("DecalSet", "float GetMaxZ() const", AS_METHODPR(DecalSet, GetMaxZ, () const, float), AS_CALL_THISCALL);
    // float Drawable::GetMinZ() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("DecalSet", "float GetMinZ() const", AS_METHODPR(DecalSet, GetMinZ, () const, float), AS_CALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetNetworkAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // NetworkState* Serializable::GetNetworkState() const | File: ../Scene/Serializable.h
    // Error: type "NetworkState*" can not automatically bind
    // Node* Component::GetNode() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("DecalSet", "Node@+ GetNode() const", AS_METHODPR(DecalSet, GetNode, () const, Node*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DecalSet", "Node@+ get_node() const", AS_METHODPR(DecalSet, GetNode, () const, Node*), AS_CALL_THISCALL);
    // unsigned Serializable::GetNumAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("DecalSet", "uint GetNumAttributes() const", AS_METHODPR(DecalSet, GetNumAttributes, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DecalSet", "uint get_numAttributes() const", AS_METHODPR(DecalSet, GetNumAttributes, () const, unsigned), AS_CALL_THISCALL);
    // unsigned DecalSet::GetNumDecals() const | File: ../Graphics/DecalSet.h
    engine->RegisterObjectMethod("DecalSet", "uint GetNumDecals() const", AS_METHODPR(DecalSet, GetNumDecals, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DecalSet", "uint get_numDecals() const", AS_METHODPR(DecalSet, GetNumDecals, () const, unsigned), AS_CALL_THISCALL);
    // unsigned DecalSet::GetNumIndices() const | File: ../Graphics/DecalSet.h
    engine->RegisterObjectMethod("DecalSet", "uint GetNumIndices() const", AS_METHODPR(DecalSet, GetNumIndices, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DecalSet", "uint get_numIndices() const", AS_METHODPR(DecalSet, GetNumIndices, () const, unsigned), AS_CALL_THISCALL);
    // unsigned Serializable::GetNumNetworkAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("DecalSet", "uint GetNumNetworkAttributes() const", AS_METHODPR(DecalSet, GetNumNetworkAttributes, () const, unsigned), AS_CALL_THISCALL);
    // virtual unsigned Drawable::GetNumOccluderTriangles() | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("DecalSet", "uint GetNumOccluderTriangles()", AS_METHODPR(DecalSet, GetNumOccluderTriangles, (), unsigned), AS_CALL_THISCALL);
    // unsigned DecalSet::GetNumVertices() const | File: ../Graphics/DecalSet.h
    engine->RegisterObjectMethod("DecalSet", "uint GetNumVertices() const", AS_METHODPR(DecalSet, GetNumVertices, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DecalSet", "uint get_numVertices() const", AS_METHODPR(DecalSet, GetNumVertices, () const, unsigned), AS_CALL_THISCALL);
    // ObjectAnimation* Animatable::GetObjectAnimation() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("DecalSet", "ObjectAnimation@+ GetObjectAnimation() const", AS_METHODPR(DecalSet, GetObjectAnimation, () const, ObjectAnimation*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DecalSet", "ObjectAnimation@+ get_objectAnimation() const", AS_METHODPR(DecalSet, GetObjectAnimation, () const, ObjectAnimation*), AS_CALL_THISCALL);
    // ResourceRef Animatable::GetObjectAnimationAttr() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("DecalSet", "ResourceRef GetObjectAnimationAttr() const", AS_METHODPR(DecalSet, GetObjectAnimationAttr, () const, ResourceRef), AS_CALL_THISCALL);
    // Octant* Drawable::GetOctant() const | File: ../Graphics/Drawable.h
    // Error: type "Octant" can not automatically bind bacause have @nobind mark
    // bool DecalSet::GetOptimizeBufferSize() const | File: ../Graphics/DecalSet.h
    engine->RegisterObjectMethod("DecalSet", "bool GetOptimizeBufferSize() const", AS_METHODPR(DecalSet, GetOptimizeBufferSize, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DecalSet", "bool get_optimizeBufferSize() const", AS_METHODPR(DecalSet, GetOptimizeBufferSize, () const, bool), AS_CALL_THISCALL);
    // Scene* Component::GetScene() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("DecalSet", "Scene@+ GetScene() const", AS_METHODPR(DecalSet, GetScene, () const, Scene*), AS_CALL_THISCALL);
    // float Drawable::GetShadowDistance() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("DecalSet", "float GetShadowDistance() const", AS_METHODPR(DecalSet, GetShadowDistance, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DecalSet", "float get_shadowDistance() const", AS_METHODPR(DecalSet, GetShadowDistance, () const, float), AS_CALL_THISCALL);
    // unsigned Drawable::GetShadowMask() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("DecalSet", "uint GetShadowMask() const", AS_METHODPR(DecalSet, GetShadowMask, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DecalSet", "uint get_shadowMask() const", AS_METHODPR(DecalSet, GetShadowMask, () const, unsigned), AS_CALL_THISCALL);
    // float Drawable::GetSortValue() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("DecalSet", "float GetSortValue() const", AS_METHODPR(DecalSet, GetSortValue, () const, float), AS_CALL_THISCALL);
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("DecalSet", "Object@+ GetSubsystem(StringHash) const", AS_METHODPR(DecalSet, GetSubsystem, (StringHash) const, Object*), AS_CALL_THISCALL);
    // template<class T> T* Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("DecalSet", "StringHash GetType() const", AS_METHODPR(DecalSet, GetType, () const, StringHash), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DecalSet", "StringHash get_type() const", AS_METHODPR(DecalSet, GetType, () const, StringHash), AS_CALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("DecalSet", "const String& GetTypeName() const", AS_METHODPR(DecalSet, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DecalSet", "const String& get_typeName() const", AS_METHODPR(DecalSet, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    // UpdateGeometryType DecalSet::GetUpdateGeometryType() override | File: ../Graphics/DecalSet.h
    engine->RegisterObjectMethod("DecalSet", "UpdateGeometryType GetUpdateGeometryType()", AS_METHODPR(DecalSet, GetUpdateGeometryType, (), UpdateGeometryType), AS_CALL_THISCALL);
    // const PODVector<Light*>& Drawable::GetVertexLights() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("DecalSet", "Array<Light@>@ GetVertexLights() const", AS_FUNCTION_OBJFIRST(DecalSet_GetVertexLights_void), AS_CALL_CDECL_OBJFIRST);
    // unsigned Drawable::GetViewMask() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("DecalSet", "uint GetViewMask() const", AS_METHODPR(DecalSet, GetViewMask, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DecalSet", "uint get_viewMask() const", AS_METHODPR(DecalSet, GetViewMask, () const, unsigned), AS_CALL_THISCALL);
    // const BoundingBox& Drawable::GetWorldBoundingBox() | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("DecalSet", "const BoundingBox& GetWorldBoundingBox()", AS_METHODPR(DecalSet, GetWorldBoundingBox, (), const BoundingBox&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DecalSet", "const BoundingBox& get_worldBoundingBox()", AS_METHODPR(DecalSet, GetWorldBoundingBox, (), const BoundingBox&), AS_CALL_THISCALL);
    // Zone* Drawable::GetZone() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("DecalSet", "Zone@+ GetZone() const", AS_METHODPR(DecalSet, GetZone, () const, Zone*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DecalSet", "Zone@+ get_zone() const", AS_METHODPR(DecalSet, GetZone, () const, Zone*), AS_CALL_THISCALL);
    // unsigned Drawable::GetZoneMask() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("DecalSet", "uint GetZoneMask() const", AS_METHODPR(DecalSet, GetZoneMask, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DecalSet", "uint get_zoneMask() const", AS_METHODPR(DecalSet, GetZoneMask, () const, unsigned), AS_CALL_THISCALL);
    // bool Drawable::HasBasePass(unsigned batchIndex) const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("DecalSet", "bool HasBasePass(uint) const", AS_METHODPR(DecalSet, HasBasePass, (unsigned) const, bool), AS_CALL_THISCALL);
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("DecalSet", "bool HasEventHandlers() const", AS_METHODPR(DecalSet, HasEventHandlers, () const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("DecalSet", "bool HasSubscribedToEvent(StringHash) const", AS_METHODPR(DecalSet, HasSubscribedToEvent, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("DecalSet", "bool HasSubscribedToEvent(Object@+, StringHash) const", AS_METHODPR(DecalSet, HasSubscribedToEvent, (Object*, StringHash) const, bool), AS_CALL_THISCALL);
    // bool Component::IsEnabled() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("DecalSet", "bool IsEnabled() const", AS_METHODPR(DecalSet, IsEnabled, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DecalSet", "bool get_enabled() const", AS_METHODPR(DecalSet, IsEnabled, () const, bool), AS_CALL_THISCALL);
    // bool Component::IsEnabledEffective() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("DecalSet", "bool IsEnabledEffective() const", AS_METHODPR(DecalSet, IsEnabledEffective, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DecalSet", "bool get_enabledEffective() const", AS_METHODPR(DecalSet, IsEnabledEffective, () const, bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("DecalSet", "bool IsInstanceOf(StringHash) const", AS_METHODPR(DecalSet, IsInstanceOf, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // bool Drawable::IsInView() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("DecalSet", "bool IsInView() const", AS_METHODPR(DecalSet, IsInView, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DecalSet", "bool get_inView() const", AS_METHODPR(DecalSet, IsInView, () const, bool), AS_CALL_THISCALL);
    // bool Drawable::IsInView(Camera* camera) const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("DecalSet", "bool IsInView(Camera@+) const", AS_METHODPR(DecalSet, IsInView, (Camera*) const, bool), AS_CALL_THISCALL);
    // bool Drawable::IsInView(const FrameInfo& frame, bool anyCamera=false) const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("DecalSet", "bool IsInView(const FrameInfo&in, bool = false) const", AS_METHODPR(DecalSet, IsInView, (const FrameInfo&, bool) const, bool), AS_CALL_THISCALL);
    // bool Drawable::IsOccludee() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("DecalSet", "bool IsOccludee() const", AS_METHODPR(DecalSet, IsOccludee, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DecalSet", "bool get_occludee() const", AS_METHODPR(DecalSet, IsOccludee, () const, bool), AS_CALL_THISCALL);
    // bool Drawable::IsOccluder() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("DecalSet", "bool IsOccluder() const", AS_METHODPR(DecalSet, IsOccluder, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DecalSet", "bool get_occluder() const", AS_METHODPR(DecalSet, IsOccluder, () const, bool), AS_CALL_THISCALL);
    // bool Component::IsReplicated() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("DecalSet", "bool IsReplicated() const", AS_METHODPR(DecalSet, IsReplicated, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DecalSet", "bool get_replicated() const", AS_METHODPR(DecalSet, IsReplicated, () const, bool), AS_CALL_THISCALL);
    // bool Serializable::IsTemporary() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("DecalSet", "bool IsTemporary() const", AS_METHODPR(DecalSet, IsTemporary, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DecalSet", "bool get_temporary() const", AS_METHODPR(DecalSet, IsTemporary, () const, bool), AS_CALL_THISCALL);
    // bool Drawable::IsZoneDirty() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("DecalSet", "bool IsZoneDirty() const", AS_METHODPR(DecalSet, IsZoneDirty, () const, bool), AS_CALL_THISCALL);
    // void Drawable::LimitLights() | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("DecalSet", "void LimitLights()", AS_METHODPR(DecalSet, LimitLights, (), void), AS_CALL_THISCALL);
    // void Drawable::LimitVertexLights(bool removeConvertedLights) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("DecalSet", "void LimitVertexLights(bool)", AS_METHODPR(DecalSet, LimitVertexLights, (bool), void), AS_CALL_THISCALL);
    // virtual bool Serializable::Load(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("DecalSet", "bool Load(Deserializer&)", AS_METHODPR(DecalSet, Load, (Deserializer&), bool), AS_CALL_THISCALL);
    // bool Animatable::LoadJSON(const JSONValue& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("DecalSet", "bool LoadJSON(const JSONValue&in)", AS_METHODPR(DecalSet, LoadJSON, (const JSONValue&), bool), AS_CALL_THISCALL);
    // bool Animatable::LoadXML(const XMLElement& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("DecalSet", "bool LoadXML(const XMLElement&in)", AS_METHODPR(DecalSet, LoadXML, (const XMLElement&), bool), AS_CALL_THISCALL);
    // void Drawable::MarkForUpdate() | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("DecalSet", "void MarkForUpdate()", AS_METHODPR(DecalSet, MarkForUpdate, (), void), AS_CALL_THISCALL);
    // void Drawable::MarkInView(const FrameInfo& frame) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("DecalSet", "void MarkInView(const FrameInfo&in)", AS_METHODPR(DecalSet, MarkInView, (const FrameInfo&), void), AS_CALL_THISCALL);
    // void Drawable::MarkInView(unsigned frameNumber) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("DecalSet", "void MarkInView(uint)", AS_METHODPR(DecalSet, MarkInView, (unsigned), void), AS_CALL_THISCALL);
    // void Component::MarkNetworkUpdate() override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("DecalSet", "void MarkNetworkUpdate()", AS_METHODPR(DecalSet, MarkNetworkUpdate, (), void), AS_CALL_THISCALL);
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("DecalSet", "void OnEvent(Object@+, StringHash, VariantMap&)", AS_METHODPR(DecalSet, OnEvent, (Object*, StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // virtual void Serializable::OnGetAttribute(const AttributeInfo& attr, Variant& dest) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("DecalSet", "void OnGetAttribute(const AttributeInfo&in, Variant&) const", AS_METHODPR(DecalSet, OnGetAttribute, (const AttributeInfo&, Variant&) const, void), AS_CALL_THISCALL);
    // virtual void Serializable::OnSetAttribute(const AttributeInfo& attr, const Variant& src) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("DecalSet", "void OnSetAttribute(const AttributeInfo&in, const Variant&in)", AS_METHODPR(DecalSet, OnSetAttribute, (const AttributeInfo&, const Variant&), void), AS_CALL_THISCALL);
    // void DecalSet::OnSetEnabled() override | File: ../Graphics/DecalSet.h
    engine->RegisterObjectMethod("DecalSet", "void OnSetEnabled()", AS_METHODPR(DecalSet, OnSetEnabled, (), void), AS_CALL_THISCALL);
    // void Component::PrepareNetworkUpdate() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("DecalSet", "void PrepareNetworkUpdate()", AS_METHODPR(DecalSet, PrepareNetworkUpdate, (), void), AS_CALL_THISCALL);
    // void DecalSet::ProcessRayQuery(const RayOctreeQuery& query, PODVector<RayQueryResult>& results) override | File: ../Graphics/DecalSet.h
    // Error: type "RayOctreeQuery" can not automatically bind bacause have @nobind mark
    // bool Serializable::ReadDeltaUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("DecalSet", "bool ReadDeltaUpdate(Deserializer&)", AS_METHODPR(DecalSet, ReadDeltaUpdate, (Deserializer&), bool), AS_CALL_THISCALL);
    // bool Serializable::ReadLatestDataUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("DecalSet", "bool ReadLatestDataUpdate(Deserializer&)", AS_METHODPR(DecalSet, ReadLatestDataUpdate, (Deserializer&), bool), AS_CALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("DecalSet", "int Refs() const", AS_METHODPR(DecalSet, Refs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DecalSet", "int get_refs() const", AS_METHODPR(DecalSet, Refs, () const, int), AS_CALL_THISCALL);
    // static void DecalSet::RegisterObject(Context* context) | File: ../Graphics/DecalSet.h
    // Not registered because have @nobind mark
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("DecalSet", asBEHAVE_RELEASE, "void f()", AS_METHODPR(DecalSet, ReleaseRef, (), void), AS_CALL_THISCALL);
    // void Component::Remove() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("DecalSet", "void Remove()", AS_METHODPR(DecalSet, Remove, (), void), AS_CALL_THISCALL);
    // void DecalSet::RemoveAllDecals() | File: ../Graphics/DecalSet.h
    engine->RegisterObjectMethod("DecalSet", "void RemoveAllDecals()", AS_METHODPR(DecalSet, RemoveAllDecals, (), void), AS_CALL_THISCALL);
    // void Animatable::RemoveAttributeAnimation(const String& name) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("DecalSet", "void RemoveAttributeAnimation(const String&in)", AS_METHODPR(DecalSet, RemoveAttributeAnimation, (const String&), void), AS_CALL_THISCALL);
    // void DecalSet::RemoveDecals(unsigned num) | File: ../Graphics/DecalSet.h
    engine->RegisterObjectMethod("DecalSet", "void RemoveDecals(uint)", AS_METHODPR(DecalSet, RemoveDecals, (unsigned), void), AS_CALL_THISCALL);
    // void Serializable::RemoveInstanceDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("DecalSet", "void RemoveInstanceDefault()", AS_METHODPR(DecalSet, RemoveInstanceDefault, (), void), AS_CALL_THISCALL);
    // void Animatable::RemoveObjectAnimation() | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("DecalSet", "void RemoveObjectAnimation()", AS_METHODPR(DecalSet, RemoveObjectAnimation, (), void), AS_CALL_THISCALL);
    // void Serializable::ResetToDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("DecalSet", "void ResetToDefault()", AS_METHODPR(DecalSet, ResetToDefault, (), void), AS_CALL_THISCALL);
    // bool Component::Save(Serializer& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("DecalSet", "bool Save(Serializer&) const", AS_METHODPR(DecalSet, Save, (Serializer&) const, bool), AS_CALL_THISCALL);
    // virtual bool Serializable::SaveDefaultAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("DecalSet", "bool SaveDefaultAttributes() const", AS_METHODPR(DecalSet, SaveDefaultAttributes, () const, bool), AS_CALL_THISCALL);
    // bool Component::SaveJSON(JSONValue& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("DecalSet", "bool SaveJSON(JSONValue&) const", AS_METHODPR(DecalSet, SaveJSON, (JSONValue&) const, bool), AS_CALL_THISCALL);
    // bool Component::SaveXML(XMLElement& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("DecalSet", "bool SaveXML(XMLElement&) const", AS_METHODPR(DecalSet, SaveXML, (XMLElement&) const, bool), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("DecalSet", "void SendEvent(StringHash)", AS_METHODPR(DecalSet, SendEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("DecalSet", "void SendEvent(StringHash, VariantMap&)", AS_METHODPR(DecalSet, SendEvent, (StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void Animatable::SetAnimationEnabled(bool enable) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("DecalSet", "void SetAnimationEnabled(bool)", AS_METHODPR(DecalSet, SetAnimationEnabled, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DecalSet", "void set_animationEnabled(bool)", AS_METHODPR(DecalSet, SetAnimationEnabled, (bool), void), AS_CALL_THISCALL);
    // void Animatable::SetAnimationTime(float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("DecalSet", "void SetAnimationTime(float)", AS_METHODPR(DecalSet, SetAnimationTime, (float), void), AS_CALL_THISCALL);
    // bool Serializable::SetAttribute(unsigned index, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("DecalSet", "bool SetAttribute(uint, const Variant&in)", AS_METHODPR(DecalSet, SetAttribute, (unsigned, const Variant&), bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DecalSet", "bool set_attributes(uint, const Variant&in)", AS_METHODPR(DecalSet, SetAttribute, (unsigned, const Variant&), bool), AS_CALL_THISCALL);
    // bool Serializable::SetAttribute(const String& name, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("DecalSet", "bool SetAttribute(const String&in, const Variant&in)", AS_METHODPR(DecalSet, SetAttribute, (const String&, const Variant&), bool), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimation(const String& name, ValueAnimation* attributeAnimation, WrapMode wrapMode=WM_LOOP, float speed=1.0f) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("DecalSet", "void SetAttributeAnimation(const String&in, ValueAnimation@+, WrapMode = WM_LOOP, float = 1.0f)", AS_METHODPR(DecalSet, SetAttributeAnimation, (const String&, ValueAnimation*, WrapMode, float), void), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimationSpeed(const String& name, float speed) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("DecalSet", "void SetAttributeAnimationSpeed(const String&in, float)", AS_METHODPR(DecalSet, SetAttributeAnimationSpeed, (const String&, float), void), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimationTime(const String& name, float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("DecalSet", "void SetAttributeAnimationTime(const String&in, float)", AS_METHODPR(DecalSet, SetAttributeAnimationTime, (const String&, float), void), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimationWrapMode(const String& name, WrapMode wrapMode) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("DecalSet", "void SetAttributeAnimationWrapMode(const String&in, WrapMode)", AS_METHODPR(DecalSet, SetAttributeAnimationWrapMode, (const String&, WrapMode), void), AS_CALL_THISCALL);
    // void Drawable::SetBasePass(unsigned batchIndex) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("DecalSet", "void SetBasePass(uint)", AS_METHODPR(DecalSet, SetBasePass, (unsigned), void), AS_CALL_THISCALL);
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("DecalSet", "void SetBlockEvents(bool)", AS_METHODPR(DecalSet, SetBlockEvents, (bool), void), AS_CALL_THISCALL);
    // void Drawable::SetCastShadows(bool enable) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("DecalSet", "void SetCastShadows(bool)", AS_METHODPR(DecalSet, SetCastShadows, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DecalSet", "void set_castShadows(bool)", AS_METHODPR(DecalSet, SetCastShadows, (bool), void), AS_CALL_THISCALL);
    // void DecalSet::SetDecalsAttr(const PODVector<unsigned char>& value) | File: ../Graphics/DecalSet.h
    // Error: type "const PODVector<unsigned char>&" can not automatically bind
    // void Drawable::SetDrawDistance(float distance) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("DecalSet", "void SetDrawDistance(float)", AS_METHODPR(DecalSet, SetDrawDistance, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DecalSet", "void set_drawDistance(float)", AS_METHODPR(DecalSet, SetDrawDistance, (float), void), AS_CALL_THISCALL);
    // void Component::SetEnabled(bool enable) | File: ../Scene/Component.h
    engine->RegisterObjectMethod("DecalSet", "void SetEnabled(bool)", AS_METHODPR(DecalSet, SetEnabled, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DecalSet", "void set_enabled(bool)", AS_METHODPR(DecalSet, SetEnabled, (bool), void), AS_CALL_THISCALL);
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("DecalSet", "void SetGlobalVar(StringHash, const Variant&in)", AS_METHODPR(DecalSet, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DecalSet", "void set_globalVar(StringHash, const Variant&in)", AS_METHODPR(DecalSet, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    // void Serializable::SetInstanceDefault(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("DecalSet", "void SetInstanceDefault(bool)", AS_METHODPR(DecalSet, SetInstanceDefault, (bool), void), AS_CALL_THISCALL);
    // void Serializable::SetInterceptNetworkUpdate(const String& attributeName, bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("DecalSet", "void SetInterceptNetworkUpdate(const String&in, bool)", AS_METHODPR(DecalSet, SetInterceptNetworkUpdate, (const String&, bool), void), AS_CALL_THISCALL);
    // void Drawable::SetLightMask(unsigned mask) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("DecalSet", "void SetLightMask(uint)", AS_METHODPR(DecalSet, SetLightMask, (unsigned), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DecalSet", "void set_lightMask(uint)", AS_METHODPR(DecalSet, SetLightMask, (unsigned), void), AS_CALL_THISCALL);
    // void Drawable::SetLodBias(float bias) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("DecalSet", "void SetLodBias(float)", AS_METHODPR(DecalSet, SetLodBias, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DecalSet", "void set_lodBias(float)", AS_METHODPR(DecalSet, SetLodBias, (float), void), AS_CALL_THISCALL);
    // void DecalSet::SetMaterial(Material* material) | File: ../Graphics/DecalSet.h
    engine->RegisterObjectMethod("DecalSet", "void SetMaterial(Material@+)", AS_METHODPR(DecalSet, SetMaterial, (Material*), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DecalSet", "void set_material(Material@+)", AS_METHODPR(DecalSet, SetMaterial, (Material*), void), AS_CALL_THISCALL);
    // void DecalSet::SetMaterialAttr(const ResourceRef& value) | File: ../Graphics/DecalSet.h
    engine->RegisterObjectMethod("DecalSet", "void SetMaterialAttr(const ResourceRef&in)", AS_METHODPR(DecalSet, SetMaterialAttr, (const ResourceRef&), void), AS_CALL_THISCALL);
    // void DecalSet::SetMaxIndices(unsigned num) | File: ../Graphics/DecalSet.h
    engine->RegisterObjectMethod("DecalSet", "void SetMaxIndices(uint)", AS_METHODPR(DecalSet, SetMaxIndices, (unsigned), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DecalSet", "void set_maxIndices(uint)", AS_METHODPR(DecalSet, SetMaxIndices, (unsigned), void), AS_CALL_THISCALL);
    // void Drawable::SetMaxLights(unsigned num) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("DecalSet", "void SetMaxLights(uint)", AS_METHODPR(DecalSet, SetMaxLights, (unsigned), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DecalSet", "void set_maxLights(uint)", AS_METHODPR(DecalSet, SetMaxLights, (unsigned), void), AS_CALL_THISCALL);
    // void DecalSet::SetMaxVertices(unsigned num) | File: ../Graphics/DecalSet.h
    engine->RegisterObjectMethod("DecalSet", "void SetMaxVertices(uint)", AS_METHODPR(DecalSet, SetMaxVertices, (unsigned), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DecalSet", "void set_maxVertices(uint)", AS_METHODPR(DecalSet, SetMaxVertices, (unsigned), void), AS_CALL_THISCALL);
    // void Drawable::SetMinMaxZ(float minZ, float maxZ) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("DecalSet", "void SetMinMaxZ(float, float)", AS_METHODPR(DecalSet, SetMinMaxZ, (float, float), void), AS_CALL_THISCALL);
    // void Animatable::SetObjectAnimation(ObjectAnimation* objectAnimation) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("DecalSet", "void SetObjectAnimation(ObjectAnimation@+)", AS_METHODPR(DecalSet, SetObjectAnimation, (ObjectAnimation*), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DecalSet", "void set_objectAnimation(ObjectAnimation@+)", AS_METHODPR(DecalSet, SetObjectAnimation, (ObjectAnimation*), void), AS_CALL_THISCALL);
    // void Animatable::SetObjectAnimationAttr(const ResourceRef& value) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("DecalSet", "void SetObjectAnimationAttr(const ResourceRef&in)", AS_METHODPR(DecalSet, SetObjectAnimationAttr, (const ResourceRef&), void), AS_CALL_THISCALL);
    // void Drawable::SetOccludee(bool enable) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("DecalSet", "void SetOccludee(bool)", AS_METHODPR(DecalSet, SetOccludee, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DecalSet", "void set_occludee(bool)", AS_METHODPR(DecalSet, SetOccludee, (bool), void), AS_CALL_THISCALL);
    // void Drawable::SetOccluder(bool enable) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("DecalSet", "void SetOccluder(bool)", AS_METHODPR(DecalSet, SetOccluder, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DecalSet", "void set_occluder(bool)", AS_METHODPR(DecalSet, SetOccluder, (bool), void), AS_CALL_THISCALL);
    // void DecalSet::SetOptimizeBufferSize(bool enable) | File: ../Graphics/DecalSet.h
    engine->RegisterObjectMethod("DecalSet", "void SetOptimizeBufferSize(bool)", AS_METHODPR(DecalSet, SetOptimizeBufferSize, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DecalSet", "void set_optimizeBufferSize(bool)", AS_METHODPR(DecalSet, SetOptimizeBufferSize, (bool), void), AS_CALL_THISCALL);
    // void Drawable::SetShadowDistance(float distance) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("DecalSet", "void SetShadowDistance(float)", AS_METHODPR(DecalSet, SetShadowDistance, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DecalSet", "void set_shadowDistance(float)", AS_METHODPR(DecalSet, SetShadowDistance, (float), void), AS_CALL_THISCALL);
    // void Drawable::SetShadowMask(unsigned mask) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("DecalSet", "void SetShadowMask(uint)", AS_METHODPR(DecalSet, SetShadowMask, (unsigned), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DecalSet", "void set_shadowMask(uint)", AS_METHODPR(DecalSet, SetShadowMask, (unsigned), void), AS_CALL_THISCALL);
    // void Drawable::SetSortValue(float value) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("DecalSet", "void SetSortValue(float)", AS_METHODPR(DecalSet, SetSortValue, (float), void), AS_CALL_THISCALL);
    // void Serializable::SetTemporary(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("DecalSet", "void SetTemporary(bool)", AS_METHODPR(DecalSet, SetTemporary, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DecalSet", "void set_temporary(bool)", AS_METHODPR(DecalSet, SetTemporary, (bool), void), AS_CALL_THISCALL);
    // void Drawable::SetViewMask(unsigned mask) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("DecalSet", "void SetViewMask(uint)", AS_METHODPR(DecalSet, SetViewMask, (unsigned), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DecalSet", "void set_viewMask(uint)", AS_METHODPR(DecalSet, SetViewMask, (unsigned), void), AS_CALL_THISCALL);
    // void Drawable::SetZone(Zone* zone, bool temporary=false) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("DecalSet", "void SetZone(Zone@+, bool = false)", AS_METHODPR(DecalSet, SetZone, (Zone*, bool), void), AS_CALL_THISCALL);
    // void Drawable::SetZoneMask(unsigned mask) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("DecalSet", "void SetZoneMask(uint)", AS_METHODPR(DecalSet, SetZoneMask, (unsigned), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DecalSet", "void set_zoneMask(uint)", AS_METHODPR(DecalSet, SetZoneMask, (unsigned), void), AS_CALL_THISCALL);
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod("DecalSet", "void UnsubscribeFromAllEvents()", AS_METHODPR(DecalSet, UnsubscribeFromAllEvents, (), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("DecalSet", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", AS_FUNCTION_OBJFIRST(DecalSet_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), AS_CALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("DecalSet", "void UnsubscribeFromEvent(StringHash)", AS_METHODPR(DecalSet, UnsubscribeFromEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("DecalSet", "void UnsubscribeFromEvent(Object@+, StringHash)", AS_METHODPR(DecalSet, UnsubscribeFromEvent, (Object*, StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("DecalSet", "void UnsubscribeFromEvents(Object@+)", AS_METHODPR(DecalSet, UnsubscribeFromEvents, (Object*), void), AS_CALL_THISCALL);
    // virtual void Drawable::Update(const FrameInfo& frame) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("DecalSet", "void Update(const FrameInfo&in)", AS_METHODPR(DecalSet, Update, (const FrameInfo&), void), AS_CALL_THISCALL);
    // void DecalSet::UpdateBatches(const FrameInfo& frame) override | File: ../Graphics/DecalSet.h
    engine->RegisterObjectMethod("DecalSet", "void UpdateBatches(const FrameInfo&in)", AS_METHODPR(DecalSet, UpdateBatches, (const FrameInfo&), void), AS_CALL_THISCALL);
    // void DecalSet::UpdateGeometry(const FrameInfo& frame) override | File: ../Graphics/DecalSet.h
    engine->RegisterObjectMethod("DecalSet", "void UpdateGeometry(const FrameInfo&in)", AS_METHODPR(DecalSet, UpdateGeometry, (const FrameInfo&), void), AS_CALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("DecalSet", "int WeakRefs() const", AS_METHODPR(DecalSet, WeakRefs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DecalSet", "int get_weakRefs() const", AS_METHODPR(DecalSet, WeakRefs, () const, int), AS_CALL_THISCALL);
    // void Serializable::WriteDeltaUpdate(Serializer& dest, const DirtyBits& attributeBits, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("DecalSet", "void WriteDeltaUpdate(Serializer&, const DirtyBits&in, uint8)", AS_METHODPR(DecalSet, WriteDeltaUpdate, (Serializer&, const DirtyBits&, unsigned char), void), AS_CALL_THISCALL);
    // void Serializable::WriteInitialDeltaUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("DecalSet", "void WriteInitialDeltaUpdate(Serializer&, uint8)", AS_METHODPR(DecalSet, WriteInitialDeltaUpdate, (Serializer&, unsigned char), void), AS_CALL_THISCALL);
    // void Serializable::WriteLatestDataUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("DecalSet", "void WriteLatestDataUpdate(Serializer&, uint8)", AS_METHODPR(DecalSet, WriteLatestDataUpdate, (Serializer&, unsigned char), void), AS_CALL_THISCALL);
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
    engine->RegisterObjectMethod("Deserializer", "uint GetChecksum()", AS_METHODPR(Deserializer, GetChecksum, (), unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Deserializer", "uint get_checksum()", AS_METHODPR(Deserializer, GetChecksum, (), unsigned), AS_CALL_THISCALL);
    // virtual const String& Deserializer::GetName() const | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("Deserializer", "const String& GetName() const", AS_METHODPR(Deserializer, GetName, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Deserializer", "const String& get_name() const", AS_METHODPR(Deserializer, GetName, () const, const String&), AS_CALL_THISCALL);
    // unsigned Deserializer::GetPosition() const | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("Deserializer", "uint GetPosition() const", AS_METHODPR(Deserializer, GetPosition, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Deserializer", "uint get_position() const", AS_METHODPR(Deserializer, GetPosition, () const, unsigned), AS_CALL_THISCALL);
    // unsigned Deserializer::GetSize() const | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("Deserializer", "uint GetSize() const", AS_METHODPR(Deserializer, GetSize, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Deserializer", "uint get_size() const", AS_METHODPR(Deserializer, GetSize, () const, unsigned), AS_CALL_THISCALL);
    // virtual bool Deserializer::IsEof() const | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("Deserializer", "bool IsEof() const", AS_METHODPR(Deserializer, IsEof, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Deserializer", "bool get_eof() const", AS_METHODPR(Deserializer, IsEof, () const, bool), AS_CALL_THISCALL);
    // virtual unsigned Deserializer::Read(void* dest, unsigned size)=0 | File: ../IO/Deserializer.h
    // Error: type "void*" can not automatically bind
    // bool Deserializer::ReadBool() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("Deserializer", "bool ReadBool()", AS_METHODPR(Deserializer, ReadBool, (), bool), AS_CALL_THISCALL);
    // BoundingBox Deserializer::ReadBoundingBox() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("Deserializer", "BoundingBox ReadBoundingBox()", AS_METHODPR(Deserializer, ReadBoundingBox, (), BoundingBox), AS_CALL_THISCALL);
    // PODVector<unsigned char> Deserializer::ReadBuffer() | File: ../IO/Deserializer.h
    // Error: type "PODVector<unsigned char>" can not automatically bind
    // signed char Deserializer::ReadByte() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("Deserializer", "int8 ReadByte()", AS_METHODPR(Deserializer, ReadByte, (), signed char), AS_CALL_THISCALL);
    // Color Deserializer::ReadColor() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("Deserializer", "Color ReadColor()", AS_METHODPR(Deserializer, ReadColor, (), Color), AS_CALL_THISCALL);
    // double Deserializer::ReadDouble() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("Deserializer", "double ReadDouble()", AS_METHODPR(Deserializer, ReadDouble, (), double), AS_CALL_THISCALL);
    // String Deserializer::ReadFileID() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("Deserializer", "String ReadFileID()", AS_METHODPR(Deserializer, ReadFileID, (), String), AS_CALL_THISCALL);
    // float Deserializer::ReadFloat() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("Deserializer", "float ReadFloat()", AS_METHODPR(Deserializer, ReadFloat, (), float), AS_CALL_THISCALL);
    // int Deserializer::ReadInt() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("Deserializer", "int ReadInt()", AS_METHODPR(Deserializer, ReadInt, (), int), AS_CALL_THISCALL);
    // long long Deserializer::ReadInt64() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("Deserializer", "int64 ReadInt64()", AS_METHODPR(Deserializer, ReadInt64, (), long long), AS_CALL_THISCALL);
    // IntRect Deserializer::ReadIntRect() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("Deserializer", "IntRect ReadIntRect()", AS_METHODPR(Deserializer, ReadIntRect, (), IntRect), AS_CALL_THISCALL);
    // IntVector2 Deserializer::ReadIntVector2() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("Deserializer", "IntVector2 ReadIntVector2()", AS_METHODPR(Deserializer, ReadIntVector2, (), IntVector2), AS_CALL_THISCALL);
    // IntVector3 Deserializer::ReadIntVector3() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("Deserializer", "IntVector3 ReadIntVector3()", AS_METHODPR(Deserializer, ReadIntVector3, (), IntVector3), AS_CALL_THISCALL);
    // String Deserializer::ReadLine() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("Deserializer", "String ReadLine()", AS_METHODPR(Deserializer, ReadLine, (), String), AS_CALL_THISCALL);
    // Matrix3 Deserializer::ReadMatrix3() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("Deserializer", "Matrix3 ReadMatrix3()", AS_METHODPR(Deserializer, ReadMatrix3, (), Matrix3), AS_CALL_THISCALL);
    // Matrix3x4 Deserializer::ReadMatrix3x4() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("Deserializer", "Matrix3x4 ReadMatrix3x4()", AS_METHODPR(Deserializer, ReadMatrix3x4, (), Matrix3x4), AS_CALL_THISCALL);
    // Matrix4 Deserializer::ReadMatrix4() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("Deserializer", "Matrix4 ReadMatrix4()", AS_METHODPR(Deserializer, ReadMatrix4, (), Matrix4), AS_CALL_THISCALL);
    // unsigned Deserializer::ReadNetID() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("Deserializer", "uint ReadNetID()", AS_METHODPR(Deserializer, ReadNetID, (), unsigned), AS_CALL_THISCALL);
    // Quaternion Deserializer::ReadPackedQuaternion() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("Deserializer", "Quaternion ReadPackedQuaternion()", AS_METHODPR(Deserializer, ReadPackedQuaternion, (), Quaternion), AS_CALL_THISCALL);
    // Vector3 Deserializer::ReadPackedVector3(float maxAbsCoord) | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("Deserializer", "Vector3 ReadPackedVector3(float)", AS_METHODPR(Deserializer, ReadPackedVector3, (float), Vector3), AS_CALL_THISCALL);
    // Quaternion Deserializer::ReadQuaternion() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("Deserializer", "Quaternion ReadQuaternion()", AS_METHODPR(Deserializer, ReadQuaternion, (), Quaternion), AS_CALL_THISCALL);
    // Rect Deserializer::ReadRect() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("Deserializer", "Rect ReadRect()", AS_METHODPR(Deserializer, ReadRect, (), Rect), AS_CALL_THISCALL);
    // ResourceRef Deserializer::ReadResourceRef() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("Deserializer", "ResourceRef ReadResourceRef()", AS_METHODPR(Deserializer, ReadResourceRef, (), ResourceRef), AS_CALL_THISCALL);
    // ResourceRefList Deserializer::ReadResourceRefList() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("Deserializer", "ResourceRefList ReadResourceRefList()", AS_METHODPR(Deserializer, ReadResourceRefList, (), ResourceRefList), AS_CALL_THISCALL);
    // short Deserializer::ReadShort() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("Deserializer", "int16 ReadShort()", AS_METHODPR(Deserializer, ReadShort, (), short), AS_CALL_THISCALL);
    // String Deserializer::ReadString() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("Deserializer", "String ReadString()", AS_METHODPR(Deserializer, ReadString, (), String), AS_CALL_THISCALL);
    // StringHash Deserializer::ReadStringHash() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("Deserializer", "StringHash ReadStringHash()", AS_METHODPR(Deserializer, ReadStringHash, (), StringHash), AS_CALL_THISCALL);
    // StringVector Deserializer::ReadStringVector() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("Deserializer", "Array<String>@ ReadStringVector()", AS_FUNCTION_OBJFIRST(Deserializer_ReadStringVector_void), AS_CALL_CDECL_OBJFIRST);
    // unsigned char Deserializer::ReadUByte() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("Deserializer", "uint8 ReadUByte()", AS_METHODPR(Deserializer, ReadUByte, (), unsigned char), AS_CALL_THISCALL);
    // unsigned Deserializer::ReadUInt() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("Deserializer", "uint ReadUInt()", AS_METHODPR(Deserializer, ReadUInt, (), unsigned), AS_CALL_THISCALL);
    // unsigned long long Deserializer::ReadUInt64() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("Deserializer", "uint64 ReadUInt64()", AS_METHODPR(Deserializer, ReadUInt64, (), unsigned long long), AS_CALL_THISCALL);
    // unsigned short Deserializer::ReadUShort() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("Deserializer", "uint16 ReadUShort()", AS_METHODPR(Deserializer, ReadUShort, (), unsigned short), AS_CALL_THISCALL);
    // Variant Deserializer::ReadVariant() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("Deserializer", "Variant ReadVariant()", AS_METHODPR(Deserializer, ReadVariant, (), Variant), AS_CALL_THISCALL);
    // Variant Deserializer::ReadVariant(VariantType type) | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("Deserializer", "Variant ReadVariant(VariantType)", AS_METHODPR(Deserializer, ReadVariant, (VariantType), Variant), AS_CALL_THISCALL);
    // VariantMap Deserializer::ReadVariantMap() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("Deserializer", "VariantMap ReadVariantMap()", AS_METHODPR(Deserializer, ReadVariantMap, (), VariantMap), AS_CALL_THISCALL);
    // VariantVector Deserializer::ReadVariantVector() | File: ../IO/Deserializer.h
    // Error: type "VariantVector" can not automatically bind
    // Vector2 Deserializer::ReadVector2() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("Deserializer", "Vector2 ReadVector2()", AS_METHODPR(Deserializer, ReadVector2, (), Vector2), AS_CALL_THISCALL);
    // Vector3 Deserializer::ReadVector3() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("Deserializer", "Vector3 ReadVector3()", AS_METHODPR(Deserializer, ReadVector3, (), Vector3), AS_CALL_THISCALL);
    // Vector4 Deserializer::ReadVector4() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("Deserializer", "Vector4 ReadVector4()", AS_METHODPR(Deserializer, ReadVector4, (), Vector4), AS_CALL_THISCALL);
    // unsigned Deserializer::ReadVLE() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("Deserializer", "uint ReadVLE()", AS_METHODPR(Deserializer, ReadVLE, (), unsigned), AS_CALL_THISCALL);
    // virtual unsigned Deserializer::Seek(unsigned position)=0 | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("Deserializer", "uint Seek(uint)", AS_METHODPR(Deserializer, Seek, (unsigned), unsigned), AS_CALL_THISCALL);
    // unsigned Deserializer::SeekRelative(int delta) | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("Deserializer", "uint SeekRelative(int)", AS_METHODPR(Deserializer, SeekRelative, (int), unsigned), AS_CALL_THISCALL);
    // unsigned Deserializer::Tell() const | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("Deserializer", "uint Tell() const", AS_METHODPR(Deserializer, Tell, () const, unsigned), AS_CALL_THISCALL);
    // Deserializer& Deserializer::operator=(const Deserializer&) | Possible implicitly-declared
    RegisterImplicitlyDeclaredAssignOperatorIfPossible<Deserializer>(engine, "Deserializer");
    engine->RegisterObjectBehaviour("Deserializer", asBEHAVE_ADDREF, "void f()", AS_FUNCTION_OBJLAST(FakeAddRef), AS_CALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("Deserializer", asBEHAVE_RELEASE, "void f()", AS_FUNCTION_OBJLAST(FakeReleaseRef), AS_CALL_CDECL_OBJLAST);
#ifdef REGISTER_MANUAL_PART_Deserializer
    REGISTER_MANUAL_PART_Deserializer(Deserializer, "Deserializer")
#endif

    // void Drawable::AddLight(Light* light) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Drawable", "void AddLight(Light@+)", AS_METHODPR(Drawable, AddLight, (Light*), void), AS_CALL_THISCALL);
    // void RefCounted::AddRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("Drawable", asBEHAVE_ADDREF, "void f()", AS_METHODPR(Drawable, AddRef, (), void), AS_CALL_THISCALL);
    // void Component::AddReplicationState(ComponentReplicationState* state) | File: ../Scene/Component.h
    // Error: type "ComponentReplicationState*" can not automatically bind
    // void Drawable::AddVertexLight(Light* light) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Drawable", "void AddVertexLight(Light@+)", AS_METHODPR(Drawable, AddVertexLight, (Light*), void), AS_CALL_THISCALL);
    // void Serializable::AllocateNetworkState() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Drawable", "void AllocateNetworkState()", AS_METHODPR(Drawable, AllocateNetworkState, (), void), AS_CALL_THISCALL);
    // virtual void Serializable::ApplyAttributes() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Drawable", "void ApplyAttributes()", AS_METHODPR(Drawable, ApplyAttributes, (), void), AS_CALL_THISCALL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // void Component::CleanupConnection(Connection* connection) | File: ../Scene/Component.h
    // Not registered because have @manualbind mark
    // void Drawable::DrawDebugGeometry(DebugRenderer* debug, bool depthTest) override | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Drawable", "void DrawDebugGeometry(DebugRenderer@+, bool)", AS_METHODPR(Drawable, DrawDebugGeometry, (DebugRenderer*, bool), void), AS_CALL_THISCALL);
    // virtual bool Drawable::DrawOcclusion(OcclusionBuffer* buffer) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Drawable", "bool DrawOcclusion(OcclusionBuffer@+)", AS_METHODPR(Drawable, DrawOcclusion, (OcclusionBuffer*), bool), AS_CALL_THISCALL);
    // bool Animatable::GetAnimationEnabled() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Drawable", "bool GetAnimationEnabled() const", AS_METHODPR(Drawable, GetAnimationEnabled, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Drawable", "bool get_animationEnabled() const", AS_METHODPR(Drawable, GetAnimationEnabled, () const, bool), AS_CALL_THISCALL);
    // Variant Serializable::GetAttribute(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Drawable", "Variant GetAttribute(uint) const", AS_METHODPR(Drawable, GetAttribute, (unsigned) const, Variant), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Drawable", "Variant get_attributes(uint) const", AS_METHODPR(Drawable, GetAttribute, (unsigned) const, Variant), AS_CALL_THISCALL);
    // Variant Serializable::GetAttribute(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Drawable", "Variant GetAttribute(const String&in) const", AS_METHODPR(Drawable, GetAttribute, (const String&) const, Variant), AS_CALL_THISCALL);
    // ValueAnimation* Animatable::GetAttributeAnimation(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Drawable", "ValueAnimation@+ GetAttributeAnimation(const String&in) const", AS_METHODPR(Drawable, GetAttributeAnimation, (const String&) const, ValueAnimation*), AS_CALL_THISCALL);
    // float Animatable::GetAttributeAnimationSpeed(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Drawable", "float GetAttributeAnimationSpeed(const String&in) const", AS_METHODPR(Drawable, GetAttributeAnimationSpeed, (const String&) const, float), AS_CALL_THISCALL);
    // float Animatable::GetAttributeAnimationTime(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Drawable", "float GetAttributeAnimationTime(const String&in) const", AS_METHODPR(Drawable, GetAttributeAnimationTime, (const String&) const, float), AS_CALL_THISCALL);
    // WrapMode Animatable::GetAttributeAnimationWrapMode(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Drawable", "WrapMode GetAttributeAnimationWrapMode(const String&in) const", AS_METHODPR(Drawable, GetAttributeAnimationWrapMode, (const String&) const, WrapMode), AS_CALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Drawable", "Variant GetAttributeDefault(uint) const", AS_METHODPR(Drawable, GetAttributeDefault, (unsigned) const, Variant), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Drawable", "Variant get_attributeDefaults(uint) const", AS_METHODPR(Drawable, GetAttributeDefault, (unsigned) const, Variant), AS_CALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Drawable", "Variant GetAttributeDefault(const String&in) const", AS_METHODPR(Drawable, GetAttributeDefault, (const String&) const, Variant), AS_CALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // const Vector<SourceBatch>& Drawable::GetBatches() const | File: ../Graphics/Drawable.h
    // Error: type "const Vector<SourceBatch>&" can not automatically bind
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Drawable", "bool GetBlockEvents() const", AS_METHODPR(Drawable, GetBlockEvents, () const, bool), AS_CALL_THISCALL);
    // const BoundingBox& Drawable::GetBoundingBox() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Drawable", "const BoundingBox& GetBoundingBox() const", AS_METHODPR(Drawable, GetBoundingBox, () const, const BoundingBox&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Drawable", "const BoundingBox& get_boundingBox() const", AS_METHODPR(Drawable, GetBoundingBox, () const, const BoundingBox&), AS_CALL_THISCALL);
    // bool Drawable::GetCastShadows() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Drawable", "bool GetCastShadows() const", AS_METHODPR(Drawable, GetCastShadows, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Drawable", "bool get_castShadows() const", AS_METHODPR(Drawable, GetCastShadows, () const, bool), AS_CALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Drawable", "const String& GetCategory() const", AS_METHODPR(Drawable, GetCategory, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Drawable", "const String& get_category() const", AS_METHODPR(Drawable, GetCategory, () const, const String&), AS_CALL_THISCALL);
    // Component* Component::GetComponent(StringHash type) const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Drawable", "Component@+ GetComponent(StringHash) const", AS_METHODPR(Drawable, GetComponent, (StringHash) const, Component*), AS_CALL_THISCALL);
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
    engine->RegisterObjectMethod("Drawable", "float GetDistance() const", AS_METHODPR(Drawable, GetDistance, () const, float), AS_CALL_THISCALL);
    // unsigned char Drawable::GetDrawableFlags() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Drawable", "uint8 GetDrawableFlags() const", AS_METHODPR(Drawable, GetDrawableFlags, () const, unsigned char), AS_CALL_THISCALL);
    // float Drawable::GetDrawDistance() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Drawable", "float GetDrawDistance() const", AS_METHODPR(Drawable, GetDrawDistance, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Drawable", "float get_drawDistance() const", AS_METHODPR(Drawable, GetDrawDistance, () const, float), AS_CALL_THISCALL);
    // VariantMap& Object::GetEventDataMap() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Drawable", "VariantMap& GetEventDataMap() const", AS_METHODPR(Drawable, GetEventDataMap, () const, VariantMap&), AS_CALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Drawable", "Object@+ GetEventSender() const", AS_METHODPR(Drawable, GetEventSender, () const, Object*), AS_CALL_THISCALL);
    // Light* Drawable::GetFirstLight() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Drawable", "Light@+ GetFirstLight() const", AS_METHODPR(Drawable, GetFirstLight, () const, Light*), AS_CALL_THISCALL);
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Drawable", "const Variant& GetGlobalVar(StringHash) const", AS_METHODPR(Drawable, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Drawable", "const Variant& get_globalVar(StringHash) const", AS_METHODPR(Drawable, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Drawable", "const VariantMap& GetGlobalVars() const", AS_METHODPR(Drawable, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Drawable", "const VariantMap& get_globalVars() const", AS_METHODPR(Drawable, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    // unsigned Component::GetID() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Drawable", "uint GetID() const", AS_METHODPR(Drawable, GetID, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Drawable", "uint get_id() const", AS_METHODPR(Drawable, GetID, () const, unsigned), AS_CALL_THISCALL);
    // bool Serializable::GetInterceptNetworkUpdate(const String& attributeName) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Drawable", "bool GetInterceptNetworkUpdate(const String&in) const", AS_METHODPR(Drawable, GetInterceptNetworkUpdate, (const String&) const, bool), AS_CALL_THISCALL);
    // unsigned Drawable::GetLightMask() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Drawable", "uint GetLightMask() const", AS_METHODPR(Drawable, GetLightMask, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Drawable", "uint get_lightMask() const", AS_METHODPR(Drawable, GetLightMask, () const, unsigned), AS_CALL_THISCALL);
    // const PODVector<Light*>& Drawable::GetLights() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Drawable", "Array<Light@>@ GetLights() const", AS_FUNCTION_OBJFIRST(Drawable_GetLights_void), AS_CALL_CDECL_OBJFIRST);
    // float Drawable::GetLodBias() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Drawable", "float GetLodBias() const", AS_METHODPR(Drawable, GetLodBias, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Drawable", "float get_lodBias() const", AS_METHODPR(Drawable, GetLodBias, () const, float), AS_CALL_THISCALL);
    // float Drawable::GetLodDistance() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Drawable", "float GetLodDistance() const", AS_METHODPR(Drawable, GetLodDistance, () const, float), AS_CALL_THISCALL);
    // virtual Geometry* Drawable::GetLodGeometry(unsigned batchIndex, unsigned level) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Drawable", "Geometry@+ GetLodGeometry(uint, uint)", AS_METHODPR(Drawable, GetLodGeometry, (unsigned, unsigned), Geometry*), AS_CALL_THISCALL);
    // unsigned Drawable::GetMaxLights() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Drawable", "uint GetMaxLights() const", AS_METHODPR(Drawable, GetMaxLights, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Drawable", "uint get_maxLights() const", AS_METHODPR(Drawable, GetMaxLights, () const, unsigned), AS_CALL_THISCALL);
    // float Drawable::GetMaxZ() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Drawable", "float GetMaxZ() const", AS_METHODPR(Drawable, GetMaxZ, () const, float), AS_CALL_THISCALL);
    // float Drawable::GetMinZ() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Drawable", "float GetMinZ() const", AS_METHODPR(Drawable, GetMinZ, () const, float), AS_CALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetNetworkAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // NetworkState* Serializable::GetNetworkState() const | File: ../Scene/Serializable.h
    // Error: type "NetworkState*" can not automatically bind
    // Node* Component::GetNode() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Drawable", "Node@+ GetNode() const", AS_METHODPR(Drawable, GetNode, () const, Node*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Drawable", "Node@+ get_node() const", AS_METHODPR(Drawable, GetNode, () const, Node*), AS_CALL_THISCALL);
    // unsigned Serializable::GetNumAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Drawable", "uint GetNumAttributes() const", AS_METHODPR(Drawable, GetNumAttributes, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Drawable", "uint get_numAttributes() const", AS_METHODPR(Drawable, GetNumAttributes, () const, unsigned), AS_CALL_THISCALL);
    // unsigned Serializable::GetNumNetworkAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Drawable", "uint GetNumNetworkAttributes() const", AS_METHODPR(Drawable, GetNumNetworkAttributes, () const, unsigned), AS_CALL_THISCALL);
    // virtual unsigned Drawable::GetNumOccluderTriangles() | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Drawable", "uint GetNumOccluderTriangles()", AS_METHODPR(Drawable, GetNumOccluderTriangles, (), unsigned), AS_CALL_THISCALL);
    // ObjectAnimation* Animatable::GetObjectAnimation() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Drawable", "ObjectAnimation@+ GetObjectAnimation() const", AS_METHODPR(Drawable, GetObjectAnimation, () const, ObjectAnimation*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Drawable", "ObjectAnimation@+ get_objectAnimation() const", AS_METHODPR(Drawable, GetObjectAnimation, () const, ObjectAnimation*), AS_CALL_THISCALL);
    // ResourceRef Animatable::GetObjectAnimationAttr() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Drawable", "ResourceRef GetObjectAnimationAttr() const", AS_METHODPR(Drawable, GetObjectAnimationAttr, () const, ResourceRef), AS_CALL_THISCALL);
    // Octant* Drawable::GetOctant() const | File: ../Graphics/Drawable.h
    // Error: type "Octant" can not automatically bind bacause have @nobind mark
    // Scene* Component::GetScene() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Drawable", "Scene@+ GetScene() const", AS_METHODPR(Drawable, GetScene, () const, Scene*), AS_CALL_THISCALL);
    // float Drawable::GetShadowDistance() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Drawable", "float GetShadowDistance() const", AS_METHODPR(Drawable, GetShadowDistance, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Drawable", "float get_shadowDistance() const", AS_METHODPR(Drawable, GetShadowDistance, () const, float), AS_CALL_THISCALL);
    // unsigned Drawable::GetShadowMask() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Drawable", "uint GetShadowMask() const", AS_METHODPR(Drawable, GetShadowMask, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Drawable", "uint get_shadowMask() const", AS_METHODPR(Drawable, GetShadowMask, () const, unsigned), AS_CALL_THISCALL);
    // float Drawable::GetSortValue() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Drawable", "float GetSortValue() const", AS_METHODPR(Drawable, GetSortValue, () const, float), AS_CALL_THISCALL);
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Drawable", "Object@+ GetSubsystem(StringHash) const", AS_METHODPR(Drawable, GetSubsystem, (StringHash) const, Object*), AS_CALL_THISCALL);
    // template<class T> T* Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("Drawable", "StringHash GetType() const", AS_METHODPR(Drawable, GetType, () const, StringHash), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Drawable", "StringHash get_type() const", AS_METHODPR(Drawable, GetType, () const, StringHash), AS_CALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("Drawable", "const String& GetTypeName() const", AS_METHODPR(Drawable, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Drawable", "const String& get_typeName() const", AS_METHODPR(Drawable, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    // virtual UpdateGeometryType Drawable::GetUpdateGeometryType() | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Drawable", "UpdateGeometryType GetUpdateGeometryType()", AS_METHODPR(Drawable, GetUpdateGeometryType, (), UpdateGeometryType), AS_CALL_THISCALL);
    // const PODVector<Light*>& Drawable::GetVertexLights() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Drawable", "Array<Light@>@ GetVertexLights() const", AS_FUNCTION_OBJFIRST(Drawable_GetVertexLights_void), AS_CALL_CDECL_OBJFIRST);
    // unsigned Drawable::GetViewMask() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Drawable", "uint GetViewMask() const", AS_METHODPR(Drawable, GetViewMask, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Drawable", "uint get_viewMask() const", AS_METHODPR(Drawable, GetViewMask, () const, unsigned), AS_CALL_THISCALL);
    // const BoundingBox& Drawable::GetWorldBoundingBox() | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Drawable", "const BoundingBox& GetWorldBoundingBox()", AS_METHODPR(Drawable, GetWorldBoundingBox, (), const BoundingBox&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Drawable", "const BoundingBox& get_worldBoundingBox()", AS_METHODPR(Drawable, GetWorldBoundingBox, (), const BoundingBox&), AS_CALL_THISCALL);
    // Zone* Drawable::GetZone() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Drawable", "Zone@+ GetZone() const", AS_METHODPR(Drawable, GetZone, () const, Zone*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Drawable", "Zone@+ get_zone() const", AS_METHODPR(Drawable, GetZone, () const, Zone*), AS_CALL_THISCALL);
    // unsigned Drawable::GetZoneMask() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Drawable", "uint GetZoneMask() const", AS_METHODPR(Drawable, GetZoneMask, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Drawable", "uint get_zoneMask() const", AS_METHODPR(Drawable, GetZoneMask, () const, unsigned), AS_CALL_THISCALL);
    // bool Drawable::HasBasePass(unsigned batchIndex) const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Drawable", "bool HasBasePass(uint) const", AS_METHODPR(Drawable, HasBasePass, (unsigned) const, bool), AS_CALL_THISCALL);
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Drawable", "bool HasEventHandlers() const", AS_METHODPR(Drawable, HasEventHandlers, () const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Drawable", "bool HasSubscribedToEvent(StringHash) const", AS_METHODPR(Drawable, HasSubscribedToEvent, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Drawable", "bool HasSubscribedToEvent(Object@+, StringHash) const", AS_METHODPR(Drawable, HasSubscribedToEvent, (Object*, StringHash) const, bool), AS_CALL_THISCALL);
    // bool Component::IsEnabled() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Drawable", "bool IsEnabled() const", AS_METHODPR(Drawable, IsEnabled, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Drawable", "bool get_enabled() const", AS_METHODPR(Drawable, IsEnabled, () const, bool), AS_CALL_THISCALL);
    // bool Component::IsEnabledEffective() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Drawable", "bool IsEnabledEffective() const", AS_METHODPR(Drawable, IsEnabledEffective, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Drawable", "bool get_enabledEffective() const", AS_METHODPR(Drawable, IsEnabledEffective, () const, bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Drawable", "bool IsInstanceOf(StringHash) const", AS_METHODPR(Drawable, IsInstanceOf, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // bool Drawable::IsInView() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Drawable", "bool IsInView() const", AS_METHODPR(Drawable, IsInView, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Drawable", "bool get_inView() const", AS_METHODPR(Drawable, IsInView, () const, bool), AS_CALL_THISCALL);
    // bool Drawable::IsInView(Camera* camera) const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Drawable", "bool IsInView(Camera@+) const", AS_METHODPR(Drawable, IsInView, (Camera*) const, bool), AS_CALL_THISCALL);
    // bool Drawable::IsInView(const FrameInfo& frame, bool anyCamera=false) const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Drawable", "bool IsInView(const FrameInfo&in, bool = false) const", AS_METHODPR(Drawable, IsInView, (const FrameInfo&, bool) const, bool), AS_CALL_THISCALL);
    // bool Drawable::IsOccludee() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Drawable", "bool IsOccludee() const", AS_METHODPR(Drawable, IsOccludee, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Drawable", "bool get_occludee() const", AS_METHODPR(Drawable, IsOccludee, () const, bool), AS_CALL_THISCALL);
    // bool Drawable::IsOccluder() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Drawable", "bool IsOccluder() const", AS_METHODPR(Drawable, IsOccluder, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Drawable", "bool get_occluder() const", AS_METHODPR(Drawable, IsOccluder, () const, bool), AS_CALL_THISCALL);
    // bool Component::IsReplicated() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Drawable", "bool IsReplicated() const", AS_METHODPR(Drawable, IsReplicated, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Drawable", "bool get_replicated() const", AS_METHODPR(Drawable, IsReplicated, () const, bool), AS_CALL_THISCALL);
    // bool Serializable::IsTemporary() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Drawable", "bool IsTemporary() const", AS_METHODPR(Drawable, IsTemporary, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Drawable", "bool get_temporary() const", AS_METHODPR(Drawable, IsTemporary, () const, bool), AS_CALL_THISCALL);
    // bool Drawable::IsZoneDirty() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Drawable", "bool IsZoneDirty() const", AS_METHODPR(Drawable, IsZoneDirty, () const, bool), AS_CALL_THISCALL);
    // void Drawable::LimitLights() | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Drawable", "void LimitLights()", AS_METHODPR(Drawable, LimitLights, (), void), AS_CALL_THISCALL);
    // void Drawable::LimitVertexLights(bool removeConvertedLights) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Drawable", "void LimitVertexLights(bool)", AS_METHODPR(Drawable, LimitVertexLights, (bool), void), AS_CALL_THISCALL);
    // virtual bool Serializable::Load(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Drawable", "bool Load(Deserializer&)", AS_METHODPR(Drawable, Load, (Deserializer&), bool), AS_CALL_THISCALL);
    // bool Animatable::LoadJSON(const JSONValue& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Drawable", "bool LoadJSON(const JSONValue&in)", AS_METHODPR(Drawable, LoadJSON, (const JSONValue&), bool), AS_CALL_THISCALL);
    // bool Animatable::LoadXML(const XMLElement& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Drawable", "bool LoadXML(const XMLElement&in)", AS_METHODPR(Drawable, LoadXML, (const XMLElement&), bool), AS_CALL_THISCALL);
    // void Drawable::MarkForUpdate() | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Drawable", "void MarkForUpdate()", AS_METHODPR(Drawable, MarkForUpdate, (), void), AS_CALL_THISCALL);
    // void Drawable::MarkInView(const FrameInfo& frame) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Drawable", "void MarkInView(const FrameInfo&in)", AS_METHODPR(Drawable, MarkInView, (const FrameInfo&), void), AS_CALL_THISCALL);
    // void Drawable::MarkInView(unsigned frameNumber) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Drawable", "void MarkInView(uint)", AS_METHODPR(Drawable, MarkInView, (unsigned), void), AS_CALL_THISCALL);
    // void Component::MarkNetworkUpdate() override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Drawable", "void MarkNetworkUpdate()", AS_METHODPR(Drawable, MarkNetworkUpdate, (), void), AS_CALL_THISCALL);
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Drawable", "void OnEvent(Object@+, StringHash, VariantMap&)", AS_METHODPR(Drawable, OnEvent, (Object*, StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // virtual void Serializable::OnGetAttribute(const AttributeInfo& attr, Variant& dest) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Drawable", "void OnGetAttribute(const AttributeInfo&in, Variant&) const", AS_METHODPR(Drawable, OnGetAttribute, (const AttributeInfo&, Variant&) const, void), AS_CALL_THISCALL);
    // virtual void Serializable::OnSetAttribute(const AttributeInfo& attr, const Variant& src) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Drawable", "void OnSetAttribute(const AttributeInfo&in, const Variant&in)", AS_METHODPR(Drawable, OnSetAttribute, (const AttributeInfo&, const Variant&), void), AS_CALL_THISCALL);
    // void Drawable::OnSetEnabled() override | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Drawable", "void OnSetEnabled()", AS_METHODPR(Drawable, OnSetEnabled, (), void), AS_CALL_THISCALL);
    // void Component::PrepareNetworkUpdate() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Drawable", "void PrepareNetworkUpdate()", AS_METHODPR(Drawable, PrepareNetworkUpdate, (), void), AS_CALL_THISCALL);
    // virtual void Drawable::ProcessRayQuery(const RayOctreeQuery& query, PODVector<RayQueryResult>& results) | File: ../Graphics/Drawable.h
    // Error: type "RayOctreeQuery" can not automatically bind bacause have @nobind mark
    // bool Serializable::ReadDeltaUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Drawable", "bool ReadDeltaUpdate(Deserializer&)", AS_METHODPR(Drawable, ReadDeltaUpdate, (Deserializer&), bool), AS_CALL_THISCALL);
    // bool Serializable::ReadLatestDataUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Drawable", "bool ReadLatestDataUpdate(Deserializer&)", AS_METHODPR(Drawable, ReadLatestDataUpdate, (Deserializer&), bool), AS_CALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("Drawable", "int Refs() const", AS_METHODPR(Drawable, Refs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Drawable", "int get_refs() const", AS_METHODPR(Drawable, Refs, () const, int), AS_CALL_THISCALL);
    // static void Drawable::RegisterObject(Context* context) | File: ../Graphics/Drawable.h
    // Not registered because have @nobind mark
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("Drawable", asBEHAVE_RELEASE, "void f()", AS_METHODPR(Drawable, ReleaseRef, (), void), AS_CALL_THISCALL);
    // void Component::Remove() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Drawable", "void Remove()", AS_METHODPR(Drawable, Remove, (), void), AS_CALL_THISCALL);
    // void Animatable::RemoveAttributeAnimation(const String& name) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Drawable", "void RemoveAttributeAnimation(const String&in)", AS_METHODPR(Drawable, RemoveAttributeAnimation, (const String&), void), AS_CALL_THISCALL);
    // void Serializable::RemoveInstanceDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Drawable", "void RemoveInstanceDefault()", AS_METHODPR(Drawable, RemoveInstanceDefault, (), void), AS_CALL_THISCALL);
    // void Animatable::RemoveObjectAnimation() | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Drawable", "void RemoveObjectAnimation()", AS_METHODPR(Drawable, RemoveObjectAnimation, (), void), AS_CALL_THISCALL);
    // void Serializable::ResetToDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Drawable", "void ResetToDefault()", AS_METHODPR(Drawable, ResetToDefault, (), void), AS_CALL_THISCALL);
    // bool Component::Save(Serializer& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Drawable", "bool Save(Serializer&) const", AS_METHODPR(Drawable, Save, (Serializer&) const, bool), AS_CALL_THISCALL);
    // virtual bool Serializable::SaveDefaultAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Drawable", "bool SaveDefaultAttributes() const", AS_METHODPR(Drawable, SaveDefaultAttributes, () const, bool), AS_CALL_THISCALL);
    // bool Component::SaveJSON(JSONValue& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Drawable", "bool SaveJSON(JSONValue&) const", AS_METHODPR(Drawable, SaveJSON, (JSONValue&) const, bool), AS_CALL_THISCALL);
    // bool Component::SaveXML(XMLElement& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Drawable", "bool SaveXML(XMLElement&) const", AS_METHODPR(Drawable, SaveXML, (XMLElement&) const, bool), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Drawable", "void SendEvent(StringHash)", AS_METHODPR(Drawable, SendEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Drawable", "void SendEvent(StringHash, VariantMap&)", AS_METHODPR(Drawable, SendEvent, (StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void Animatable::SetAnimationEnabled(bool enable) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Drawable", "void SetAnimationEnabled(bool)", AS_METHODPR(Drawable, SetAnimationEnabled, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Drawable", "void set_animationEnabled(bool)", AS_METHODPR(Drawable, SetAnimationEnabled, (bool), void), AS_CALL_THISCALL);
    // void Animatable::SetAnimationTime(float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Drawable", "void SetAnimationTime(float)", AS_METHODPR(Drawable, SetAnimationTime, (float), void), AS_CALL_THISCALL);
    // bool Serializable::SetAttribute(unsigned index, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Drawable", "bool SetAttribute(uint, const Variant&in)", AS_METHODPR(Drawable, SetAttribute, (unsigned, const Variant&), bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Drawable", "bool set_attributes(uint, const Variant&in)", AS_METHODPR(Drawable, SetAttribute, (unsigned, const Variant&), bool), AS_CALL_THISCALL);
    // bool Serializable::SetAttribute(const String& name, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Drawable", "bool SetAttribute(const String&in, const Variant&in)", AS_METHODPR(Drawable, SetAttribute, (const String&, const Variant&), bool), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimation(const String& name, ValueAnimation* attributeAnimation, WrapMode wrapMode=WM_LOOP, float speed=1.0f) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Drawable", "void SetAttributeAnimation(const String&in, ValueAnimation@+, WrapMode = WM_LOOP, float = 1.0f)", AS_METHODPR(Drawable, SetAttributeAnimation, (const String&, ValueAnimation*, WrapMode, float), void), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimationSpeed(const String& name, float speed) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Drawable", "void SetAttributeAnimationSpeed(const String&in, float)", AS_METHODPR(Drawable, SetAttributeAnimationSpeed, (const String&, float), void), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimationTime(const String& name, float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Drawable", "void SetAttributeAnimationTime(const String&in, float)", AS_METHODPR(Drawable, SetAttributeAnimationTime, (const String&, float), void), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimationWrapMode(const String& name, WrapMode wrapMode) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Drawable", "void SetAttributeAnimationWrapMode(const String&in, WrapMode)", AS_METHODPR(Drawable, SetAttributeAnimationWrapMode, (const String&, WrapMode), void), AS_CALL_THISCALL);
    // void Drawable::SetBasePass(unsigned batchIndex) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Drawable", "void SetBasePass(uint)", AS_METHODPR(Drawable, SetBasePass, (unsigned), void), AS_CALL_THISCALL);
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Drawable", "void SetBlockEvents(bool)", AS_METHODPR(Drawable, SetBlockEvents, (bool), void), AS_CALL_THISCALL);
    // void Drawable::SetCastShadows(bool enable) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Drawable", "void SetCastShadows(bool)", AS_METHODPR(Drawable, SetCastShadows, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Drawable", "void set_castShadows(bool)", AS_METHODPR(Drawable, SetCastShadows, (bool), void), AS_CALL_THISCALL);
    // void Drawable::SetDrawDistance(float distance) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Drawable", "void SetDrawDistance(float)", AS_METHODPR(Drawable, SetDrawDistance, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Drawable", "void set_drawDistance(float)", AS_METHODPR(Drawable, SetDrawDistance, (float), void), AS_CALL_THISCALL);
    // void Component::SetEnabled(bool enable) | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Drawable", "void SetEnabled(bool)", AS_METHODPR(Drawable, SetEnabled, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Drawable", "void set_enabled(bool)", AS_METHODPR(Drawable, SetEnabled, (bool), void), AS_CALL_THISCALL);
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Drawable", "void SetGlobalVar(StringHash, const Variant&in)", AS_METHODPR(Drawable, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Drawable", "void set_globalVar(StringHash, const Variant&in)", AS_METHODPR(Drawable, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    // void Serializable::SetInstanceDefault(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Drawable", "void SetInstanceDefault(bool)", AS_METHODPR(Drawable, SetInstanceDefault, (bool), void), AS_CALL_THISCALL);
    // void Serializable::SetInterceptNetworkUpdate(const String& attributeName, bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Drawable", "void SetInterceptNetworkUpdate(const String&in, bool)", AS_METHODPR(Drawable, SetInterceptNetworkUpdate, (const String&, bool), void), AS_CALL_THISCALL);
    // void Drawable::SetLightMask(unsigned mask) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Drawable", "void SetLightMask(uint)", AS_METHODPR(Drawable, SetLightMask, (unsigned), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Drawable", "void set_lightMask(uint)", AS_METHODPR(Drawable, SetLightMask, (unsigned), void), AS_CALL_THISCALL);
    // void Drawable::SetLodBias(float bias) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Drawable", "void SetLodBias(float)", AS_METHODPR(Drawable, SetLodBias, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Drawable", "void set_lodBias(float)", AS_METHODPR(Drawable, SetLodBias, (float), void), AS_CALL_THISCALL);
    // void Drawable::SetMaxLights(unsigned num) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Drawable", "void SetMaxLights(uint)", AS_METHODPR(Drawable, SetMaxLights, (unsigned), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Drawable", "void set_maxLights(uint)", AS_METHODPR(Drawable, SetMaxLights, (unsigned), void), AS_CALL_THISCALL);
    // void Drawable::SetMinMaxZ(float minZ, float maxZ) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Drawable", "void SetMinMaxZ(float, float)", AS_METHODPR(Drawable, SetMinMaxZ, (float, float), void), AS_CALL_THISCALL);
    // void Animatable::SetObjectAnimation(ObjectAnimation* objectAnimation) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Drawable", "void SetObjectAnimation(ObjectAnimation@+)", AS_METHODPR(Drawable, SetObjectAnimation, (ObjectAnimation*), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Drawable", "void set_objectAnimation(ObjectAnimation@+)", AS_METHODPR(Drawable, SetObjectAnimation, (ObjectAnimation*), void), AS_CALL_THISCALL);
    // void Animatable::SetObjectAnimationAttr(const ResourceRef& value) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Drawable", "void SetObjectAnimationAttr(const ResourceRef&in)", AS_METHODPR(Drawable, SetObjectAnimationAttr, (const ResourceRef&), void), AS_CALL_THISCALL);
    // void Drawable::SetOccludee(bool enable) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Drawable", "void SetOccludee(bool)", AS_METHODPR(Drawable, SetOccludee, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Drawable", "void set_occludee(bool)", AS_METHODPR(Drawable, SetOccludee, (bool), void), AS_CALL_THISCALL);
    // void Drawable::SetOccluder(bool enable) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Drawable", "void SetOccluder(bool)", AS_METHODPR(Drawable, SetOccluder, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Drawable", "void set_occluder(bool)", AS_METHODPR(Drawable, SetOccluder, (bool), void), AS_CALL_THISCALL);
    // void Drawable::SetShadowDistance(float distance) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Drawable", "void SetShadowDistance(float)", AS_METHODPR(Drawable, SetShadowDistance, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Drawable", "void set_shadowDistance(float)", AS_METHODPR(Drawable, SetShadowDistance, (float), void), AS_CALL_THISCALL);
    // void Drawable::SetShadowMask(unsigned mask) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Drawable", "void SetShadowMask(uint)", AS_METHODPR(Drawable, SetShadowMask, (unsigned), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Drawable", "void set_shadowMask(uint)", AS_METHODPR(Drawable, SetShadowMask, (unsigned), void), AS_CALL_THISCALL);
    // void Drawable::SetSortValue(float value) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Drawable", "void SetSortValue(float)", AS_METHODPR(Drawable, SetSortValue, (float), void), AS_CALL_THISCALL);
    // void Serializable::SetTemporary(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Drawable", "void SetTemporary(bool)", AS_METHODPR(Drawable, SetTemporary, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Drawable", "void set_temporary(bool)", AS_METHODPR(Drawable, SetTemporary, (bool), void), AS_CALL_THISCALL);
    // void Drawable::SetViewMask(unsigned mask) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Drawable", "void SetViewMask(uint)", AS_METHODPR(Drawable, SetViewMask, (unsigned), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Drawable", "void set_viewMask(uint)", AS_METHODPR(Drawable, SetViewMask, (unsigned), void), AS_CALL_THISCALL);
    // void Drawable::SetZone(Zone* zone, bool temporary=false) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Drawable", "void SetZone(Zone@+, bool = false)", AS_METHODPR(Drawable, SetZone, (Zone*, bool), void), AS_CALL_THISCALL);
    // void Drawable::SetZoneMask(unsigned mask) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Drawable", "void SetZoneMask(uint)", AS_METHODPR(Drawable, SetZoneMask, (unsigned), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Drawable", "void set_zoneMask(uint)", AS_METHODPR(Drawable, SetZoneMask, (unsigned), void), AS_CALL_THISCALL);
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod("Drawable", "void UnsubscribeFromAllEvents()", AS_METHODPR(Drawable, UnsubscribeFromAllEvents, (), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Drawable", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", AS_FUNCTION_OBJFIRST(Drawable_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), AS_CALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Drawable", "void UnsubscribeFromEvent(StringHash)", AS_METHODPR(Drawable, UnsubscribeFromEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Drawable", "void UnsubscribeFromEvent(Object@+, StringHash)", AS_METHODPR(Drawable, UnsubscribeFromEvent, (Object*, StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Drawable", "void UnsubscribeFromEvents(Object@+)", AS_METHODPR(Drawable, UnsubscribeFromEvents, (Object*), void), AS_CALL_THISCALL);
    // virtual void Drawable::Update(const FrameInfo& frame) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Drawable", "void Update(const FrameInfo&in)", AS_METHODPR(Drawable, Update, (const FrameInfo&), void), AS_CALL_THISCALL);
    // virtual void Drawable::UpdateBatches(const FrameInfo& frame) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Drawable", "void UpdateBatches(const FrameInfo&in)", AS_METHODPR(Drawable, UpdateBatches, (const FrameInfo&), void), AS_CALL_THISCALL);
    // virtual void Drawable::UpdateGeometry(const FrameInfo& frame) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Drawable", "void UpdateGeometry(const FrameInfo&in)", AS_METHODPR(Drawable, UpdateGeometry, (const FrameInfo&), void), AS_CALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("Drawable", "int WeakRefs() const", AS_METHODPR(Drawable, WeakRefs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Drawable", "int get_weakRefs() const", AS_METHODPR(Drawable, WeakRefs, () const, int), AS_CALL_THISCALL);
    // void Serializable::WriteDeltaUpdate(Serializer& dest, const DirtyBits& attributeBits, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Drawable", "void WriteDeltaUpdate(Serializer&, const DirtyBits&in, uint8)", AS_METHODPR(Drawable, WriteDeltaUpdate, (Serializer&, const DirtyBits&, unsigned char), void), AS_CALL_THISCALL);
    // void Serializable::WriteInitialDeltaUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Drawable", "void WriteInitialDeltaUpdate(Serializer&, uint8)", AS_METHODPR(Drawable, WriteInitialDeltaUpdate, (Serializer&, unsigned char), void), AS_CALL_THISCALL);
    // void Serializable::WriteLatestDataUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Drawable", "void WriteLatestDataUpdate(Serializer&, uint8)", AS_METHODPR(Drawable, WriteLatestDataUpdate, (Serializer&, unsigned char), void), AS_CALL_THISCALL);
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
    engine->RegisterObjectMethod("Drawable2D", "void AddLight(Light@+)", AS_METHODPR(Drawable2D, AddLight, (Light*), void), AS_CALL_THISCALL);
    // void RefCounted::AddRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("Drawable2D", asBEHAVE_ADDREF, "void f()", AS_METHODPR(Drawable2D, AddRef, (), void), AS_CALL_THISCALL);
    // void Component::AddReplicationState(ComponentReplicationState* state) | File: ../Scene/Component.h
    // Error: type "ComponentReplicationState*" can not automatically bind
    // void Drawable::AddVertexLight(Light* light) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Drawable2D", "void AddVertexLight(Light@+)", AS_METHODPR(Drawable2D, AddVertexLight, (Light*), void), AS_CALL_THISCALL);
    // void Serializable::AllocateNetworkState() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Drawable2D", "void AllocateNetworkState()", AS_METHODPR(Drawable2D, AllocateNetworkState, (), void), AS_CALL_THISCALL);
    // virtual void Serializable::ApplyAttributes() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Drawable2D", "void ApplyAttributes()", AS_METHODPR(Drawable2D, ApplyAttributes, (), void), AS_CALL_THISCALL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // void Component::CleanupConnection(Connection* connection) | File: ../Scene/Component.h
    // Not registered because have @manualbind mark
    // void Drawable::DrawDebugGeometry(DebugRenderer* debug, bool depthTest) override | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Drawable2D", "void DrawDebugGeometry(DebugRenderer@+, bool)", AS_METHODPR(Drawable2D, DrawDebugGeometry, (DebugRenderer*, bool), void), AS_CALL_THISCALL);
    // virtual bool Drawable::DrawOcclusion(OcclusionBuffer* buffer) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Drawable2D", "bool DrawOcclusion(OcclusionBuffer@+)", AS_METHODPR(Drawable2D, DrawOcclusion, (OcclusionBuffer*), bool), AS_CALL_THISCALL);
    // bool Animatable::GetAnimationEnabled() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Drawable2D", "bool GetAnimationEnabled() const", AS_METHODPR(Drawable2D, GetAnimationEnabled, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Drawable2D", "bool get_animationEnabled() const", AS_METHODPR(Drawable2D, GetAnimationEnabled, () const, bool), AS_CALL_THISCALL);
    // Variant Serializable::GetAttribute(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Drawable2D", "Variant GetAttribute(uint) const", AS_METHODPR(Drawable2D, GetAttribute, (unsigned) const, Variant), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Drawable2D", "Variant get_attributes(uint) const", AS_METHODPR(Drawable2D, GetAttribute, (unsigned) const, Variant), AS_CALL_THISCALL);
    // Variant Serializable::GetAttribute(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Drawable2D", "Variant GetAttribute(const String&in) const", AS_METHODPR(Drawable2D, GetAttribute, (const String&) const, Variant), AS_CALL_THISCALL);
    // ValueAnimation* Animatable::GetAttributeAnimation(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Drawable2D", "ValueAnimation@+ GetAttributeAnimation(const String&in) const", AS_METHODPR(Drawable2D, GetAttributeAnimation, (const String&) const, ValueAnimation*), AS_CALL_THISCALL);
    // float Animatable::GetAttributeAnimationSpeed(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Drawable2D", "float GetAttributeAnimationSpeed(const String&in) const", AS_METHODPR(Drawable2D, GetAttributeAnimationSpeed, (const String&) const, float), AS_CALL_THISCALL);
    // float Animatable::GetAttributeAnimationTime(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Drawable2D", "float GetAttributeAnimationTime(const String&in) const", AS_METHODPR(Drawable2D, GetAttributeAnimationTime, (const String&) const, float), AS_CALL_THISCALL);
    // WrapMode Animatable::GetAttributeAnimationWrapMode(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Drawable2D", "WrapMode GetAttributeAnimationWrapMode(const String&in) const", AS_METHODPR(Drawable2D, GetAttributeAnimationWrapMode, (const String&) const, WrapMode), AS_CALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Drawable2D", "Variant GetAttributeDefault(uint) const", AS_METHODPR(Drawable2D, GetAttributeDefault, (unsigned) const, Variant), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Drawable2D", "Variant get_attributeDefaults(uint) const", AS_METHODPR(Drawable2D, GetAttributeDefault, (unsigned) const, Variant), AS_CALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Drawable2D", "Variant GetAttributeDefault(const String&in) const", AS_METHODPR(Drawable2D, GetAttributeDefault, (const String&) const, Variant), AS_CALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // const Vector<SourceBatch>& Drawable::GetBatches() const | File: ../Graphics/Drawable.h
    // Error: type "const Vector<SourceBatch>&" can not automatically bind
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Drawable2D", "bool GetBlockEvents() const", AS_METHODPR(Drawable2D, GetBlockEvents, () const, bool), AS_CALL_THISCALL);
    // const BoundingBox& Drawable::GetBoundingBox() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Drawable2D", "const BoundingBox& GetBoundingBox() const", AS_METHODPR(Drawable2D, GetBoundingBox, () const, const BoundingBox&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Drawable2D", "const BoundingBox& get_boundingBox() const", AS_METHODPR(Drawable2D, GetBoundingBox, () const, const BoundingBox&), AS_CALL_THISCALL);
    // bool Drawable::GetCastShadows() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Drawable2D", "bool GetCastShadows() const", AS_METHODPR(Drawable2D, GetCastShadows, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Drawable2D", "bool get_castShadows() const", AS_METHODPR(Drawable2D, GetCastShadows, () const, bool), AS_CALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Drawable2D", "const String& GetCategory() const", AS_METHODPR(Drawable2D, GetCategory, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Drawable2D", "const String& get_category() const", AS_METHODPR(Drawable2D, GetCategory, () const, const String&), AS_CALL_THISCALL);
    // Component* Component::GetComponent(StringHash type) const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Drawable2D", "Component@+ GetComponent(StringHash) const", AS_METHODPR(Drawable2D, GetComponent, (StringHash) const, Component*), AS_CALL_THISCALL);
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
    engine->RegisterObjectMethod("Drawable2D", "float GetDistance() const", AS_METHODPR(Drawable2D, GetDistance, () const, float), AS_CALL_THISCALL);
    // unsigned char Drawable::GetDrawableFlags() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Drawable2D", "uint8 GetDrawableFlags() const", AS_METHODPR(Drawable2D, GetDrawableFlags, () const, unsigned char), AS_CALL_THISCALL);
    // float Drawable::GetDrawDistance() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Drawable2D", "float GetDrawDistance() const", AS_METHODPR(Drawable2D, GetDrawDistance, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Drawable2D", "float get_drawDistance() const", AS_METHODPR(Drawable2D, GetDrawDistance, () const, float), AS_CALL_THISCALL);
    // VariantMap& Object::GetEventDataMap() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Drawable2D", "VariantMap& GetEventDataMap() const", AS_METHODPR(Drawable2D, GetEventDataMap, () const, VariantMap&), AS_CALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Drawable2D", "Object@+ GetEventSender() const", AS_METHODPR(Drawable2D, GetEventSender, () const, Object*), AS_CALL_THISCALL);
    // Light* Drawable::GetFirstLight() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Drawable2D", "Light@+ GetFirstLight() const", AS_METHODPR(Drawable2D, GetFirstLight, () const, Light*), AS_CALL_THISCALL);
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Drawable2D", "const Variant& GetGlobalVar(StringHash) const", AS_METHODPR(Drawable2D, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Drawable2D", "const Variant& get_globalVar(StringHash) const", AS_METHODPR(Drawable2D, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Drawable2D", "const VariantMap& GetGlobalVars() const", AS_METHODPR(Drawable2D, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Drawable2D", "const VariantMap& get_globalVars() const", AS_METHODPR(Drawable2D, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    // unsigned Component::GetID() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Drawable2D", "uint GetID() const", AS_METHODPR(Drawable2D, GetID, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Drawable2D", "uint get_id() const", AS_METHODPR(Drawable2D, GetID, () const, unsigned), AS_CALL_THISCALL);
    // bool Serializable::GetInterceptNetworkUpdate(const String& attributeName) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Drawable2D", "bool GetInterceptNetworkUpdate(const String&in) const", AS_METHODPR(Drawable2D, GetInterceptNetworkUpdate, (const String&) const, bool), AS_CALL_THISCALL);
    // int Drawable2D::GetLayer() const | File: ../Urho2D/Drawable2D.h
    engine->RegisterObjectMethod("Drawable2D", "int GetLayer() const", AS_METHODPR(Drawable2D, GetLayer, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Drawable2D", "int get_layer() const", AS_METHODPR(Drawable2D, GetLayer, () const, int), AS_CALL_THISCALL);
    // unsigned Drawable::GetLightMask() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Drawable2D", "uint GetLightMask() const", AS_METHODPR(Drawable2D, GetLightMask, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Drawable2D", "uint get_lightMask() const", AS_METHODPR(Drawable2D, GetLightMask, () const, unsigned), AS_CALL_THISCALL);
    // const PODVector<Light*>& Drawable::GetLights() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Drawable2D", "Array<Light@>@ GetLights() const", AS_FUNCTION_OBJFIRST(Drawable2D_GetLights_void), AS_CALL_CDECL_OBJFIRST);
    // float Drawable::GetLodBias() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Drawable2D", "float GetLodBias() const", AS_METHODPR(Drawable2D, GetLodBias, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Drawable2D", "float get_lodBias() const", AS_METHODPR(Drawable2D, GetLodBias, () const, float), AS_CALL_THISCALL);
    // float Drawable::GetLodDistance() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Drawable2D", "float GetLodDistance() const", AS_METHODPR(Drawable2D, GetLodDistance, () const, float), AS_CALL_THISCALL);
    // virtual Geometry* Drawable::GetLodGeometry(unsigned batchIndex, unsigned level) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Drawable2D", "Geometry@+ GetLodGeometry(uint, uint)", AS_METHODPR(Drawable2D, GetLodGeometry, (unsigned, unsigned), Geometry*), AS_CALL_THISCALL);
    // unsigned Drawable::GetMaxLights() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Drawable2D", "uint GetMaxLights() const", AS_METHODPR(Drawable2D, GetMaxLights, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Drawable2D", "uint get_maxLights() const", AS_METHODPR(Drawable2D, GetMaxLights, () const, unsigned), AS_CALL_THISCALL);
    // float Drawable::GetMaxZ() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Drawable2D", "float GetMaxZ() const", AS_METHODPR(Drawable2D, GetMaxZ, () const, float), AS_CALL_THISCALL);
    // float Drawable::GetMinZ() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Drawable2D", "float GetMinZ() const", AS_METHODPR(Drawable2D, GetMinZ, () const, float), AS_CALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetNetworkAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // NetworkState* Serializable::GetNetworkState() const | File: ../Scene/Serializable.h
    // Error: type "NetworkState*" can not automatically bind
    // Node* Component::GetNode() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Drawable2D", "Node@+ GetNode() const", AS_METHODPR(Drawable2D, GetNode, () const, Node*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Drawable2D", "Node@+ get_node() const", AS_METHODPR(Drawable2D, GetNode, () const, Node*), AS_CALL_THISCALL);
    // unsigned Serializable::GetNumAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Drawable2D", "uint GetNumAttributes() const", AS_METHODPR(Drawable2D, GetNumAttributes, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Drawable2D", "uint get_numAttributes() const", AS_METHODPR(Drawable2D, GetNumAttributes, () const, unsigned), AS_CALL_THISCALL);
    // unsigned Serializable::GetNumNetworkAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Drawable2D", "uint GetNumNetworkAttributes() const", AS_METHODPR(Drawable2D, GetNumNetworkAttributes, () const, unsigned), AS_CALL_THISCALL);
    // virtual unsigned Drawable::GetNumOccluderTriangles() | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Drawable2D", "uint GetNumOccluderTriangles()", AS_METHODPR(Drawable2D, GetNumOccluderTriangles, (), unsigned), AS_CALL_THISCALL);
    // ObjectAnimation* Animatable::GetObjectAnimation() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Drawable2D", "ObjectAnimation@+ GetObjectAnimation() const", AS_METHODPR(Drawable2D, GetObjectAnimation, () const, ObjectAnimation*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Drawable2D", "ObjectAnimation@+ get_objectAnimation() const", AS_METHODPR(Drawable2D, GetObjectAnimation, () const, ObjectAnimation*), AS_CALL_THISCALL);
    // ResourceRef Animatable::GetObjectAnimationAttr() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Drawable2D", "ResourceRef GetObjectAnimationAttr() const", AS_METHODPR(Drawable2D, GetObjectAnimationAttr, () const, ResourceRef), AS_CALL_THISCALL);
    // Octant* Drawable::GetOctant() const | File: ../Graphics/Drawable.h
    // Error: type "Octant" can not automatically bind bacause have @nobind mark
    // int Drawable2D::GetOrderInLayer() const | File: ../Urho2D/Drawable2D.h
    engine->RegisterObjectMethod("Drawable2D", "int GetOrderInLayer() const", AS_METHODPR(Drawable2D, GetOrderInLayer, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Drawable2D", "int get_orderInLayer() const", AS_METHODPR(Drawable2D, GetOrderInLayer, () const, int), AS_CALL_THISCALL);
    // Scene* Component::GetScene() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Drawable2D", "Scene@+ GetScene() const", AS_METHODPR(Drawable2D, GetScene, () const, Scene*), AS_CALL_THISCALL);
    // float Drawable::GetShadowDistance() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Drawable2D", "float GetShadowDistance() const", AS_METHODPR(Drawable2D, GetShadowDistance, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Drawable2D", "float get_shadowDistance() const", AS_METHODPR(Drawable2D, GetShadowDistance, () const, float), AS_CALL_THISCALL);
    // unsigned Drawable::GetShadowMask() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Drawable2D", "uint GetShadowMask() const", AS_METHODPR(Drawable2D, GetShadowMask, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Drawable2D", "uint get_shadowMask() const", AS_METHODPR(Drawable2D, GetShadowMask, () const, unsigned), AS_CALL_THISCALL);
    // float Drawable::GetSortValue() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Drawable2D", "float GetSortValue() const", AS_METHODPR(Drawable2D, GetSortValue, () const, float), AS_CALL_THISCALL);
    // const Vector<SourceBatch2D>& Drawable2D::GetSourceBatches() | File: ../Urho2D/Drawable2D.h
    // Error: type "const Vector<SourceBatch2D>&" can not automatically bind
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Drawable2D", "Object@+ GetSubsystem(StringHash) const", AS_METHODPR(Drawable2D, GetSubsystem, (StringHash) const, Object*), AS_CALL_THISCALL);
    // template<class T> T* Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("Drawable2D", "StringHash GetType() const", AS_METHODPR(Drawable2D, GetType, () const, StringHash), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Drawable2D", "StringHash get_type() const", AS_METHODPR(Drawable2D, GetType, () const, StringHash), AS_CALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("Drawable2D", "const String& GetTypeName() const", AS_METHODPR(Drawable2D, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Drawable2D", "const String& get_typeName() const", AS_METHODPR(Drawable2D, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    // virtual UpdateGeometryType Drawable::GetUpdateGeometryType() | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Drawable2D", "UpdateGeometryType GetUpdateGeometryType()", AS_METHODPR(Drawable2D, GetUpdateGeometryType, (), UpdateGeometryType), AS_CALL_THISCALL);
    // const PODVector<Light*>& Drawable::GetVertexLights() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Drawable2D", "Array<Light@>@ GetVertexLights() const", AS_FUNCTION_OBJFIRST(Drawable2D_GetVertexLights_void), AS_CALL_CDECL_OBJFIRST);
    // unsigned Drawable::GetViewMask() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Drawable2D", "uint GetViewMask() const", AS_METHODPR(Drawable2D, GetViewMask, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Drawable2D", "uint get_viewMask() const", AS_METHODPR(Drawable2D, GetViewMask, () const, unsigned), AS_CALL_THISCALL);
    // const BoundingBox& Drawable::GetWorldBoundingBox() | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Drawable2D", "const BoundingBox& GetWorldBoundingBox()", AS_METHODPR(Drawable2D, GetWorldBoundingBox, (), const BoundingBox&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Drawable2D", "const BoundingBox& get_worldBoundingBox()", AS_METHODPR(Drawable2D, GetWorldBoundingBox, (), const BoundingBox&), AS_CALL_THISCALL);
    // Zone* Drawable::GetZone() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Drawable2D", "Zone@+ GetZone() const", AS_METHODPR(Drawable2D, GetZone, () const, Zone*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Drawable2D", "Zone@+ get_zone() const", AS_METHODPR(Drawable2D, GetZone, () const, Zone*), AS_CALL_THISCALL);
    // unsigned Drawable::GetZoneMask() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Drawable2D", "uint GetZoneMask() const", AS_METHODPR(Drawable2D, GetZoneMask, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Drawable2D", "uint get_zoneMask() const", AS_METHODPR(Drawable2D, GetZoneMask, () const, unsigned), AS_CALL_THISCALL);
    // bool Drawable::HasBasePass(unsigned batchIndex) const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Drawable2D", "bool HasBasePass(uint) const", AS_METHODPR(Drawable2D, HasBasePass, (unsigned) const, bool), AS_CALL_THISCALL);
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Drawable2D", "bool HasEventHandlers() const", AS_METHODPR(Drawable2D, HasEventHandlers, () const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Drawable2D", "bool HasSubscribedToEvent(StringHash) const", AS_METHODPR(Drawable2D, HasSubscribedToEvent, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Drawable2D", "bool HasSubscribedToEvent(Object@+, StringHash) const", AS_METHODPR(Drawable2D, HasSubscribedToEvent, (Object*, StringHash) const, bool), AS_CALL_THISCALL);
    // bool Component::IsEnabled() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Drawable2D", "bool IsEnabled() const", AS_METHODPR(Drawable2D, IsEnabled, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Drawable2D", "bool get_enabled() const", AS_METHODPR(Drawable2D, IsEnabled, () const, bool), AS_CALL_THISCALL);
    // bool Component::IsEnabledEffective() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Drawable2D", "bool IsEnabledEffective() const", AS_METHODPR(Drawable2D, IsEnabledEffective, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Drawable2D", "bool get_enabledEffective() const", AS_METHODPR(Drawable2D, IsEnabledEffective, () const, bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Drawable2D", "bool IsInstanceOf(StringHash) const", AS_METHODPR(Drawable2D, IsInstanceOf, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // bool Drawable::IsInView() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Drawable2D", "bool IsInView() const", AS_METHODPR(Drawable2D, IsInView, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Drawable2D", "bool get_inView() const", AS_METHODPR(Drawable2D, IsInView, () const, bool), AS_CALL_THISCALL);
    // bool Drawable::IsInView(Camera* camera) const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Drawable2D", "bool IsInView(Camera@+) const", AS_METHODPR(Drawable2D, IsInView, (Camera*) const, bool), AS_CALL_THISCALL);
    // bool Drawable::IsInView(const FrameInfo& frame, bool anyCamera=false) const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Drawable2D", "bool IsInView(const FrameInfo&in, bool = false) const", AS_METHODPR(Drawable2D, IsInView, (const FrameInfo&, bool) const, bool), AS_CALL_THISCALL);
    // bool Drawable::IsOccludee() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Drawable2D", "bool IsOccludee() const", AS_METHODPR(Drawable2D, IsOccludee, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Drawable2D", "bool get_occludee() const", AS_METHODPR(Drawable2D, IsOccludee, () const, bool), AS_CALL_THISCALL);
    // bool Drawable::IsOccluder() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Drawable2D", "bool IsOccluder() const", AS_METHODPR(Drawable2D, IsOccluder, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Drawable2D", "bool get_occluder() const", AS_METHODPR(Drawable2D, IsOccluder, () const, bool), AS_CALL_THISCALL);
    // bool Component::IsReplicated() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Drawable2D", "bool IsReplicated() const", AS_METHODPR(Drawable2D, IsReplicated, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Drawable2D", "bool get_replicated() const", AS_METHODPR(Drawable2D, IsReplicated, () const, bool), AS_CALL_THISCALL);
    // bool Serializable::IsTemporary() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Drawable2D", "bool IsTemporary() const", AS_METHODPR(Drawable2D, IsTemporary, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Drawable2D", "bool get_temporary() const", AS_METHODPR(Drawable2D, IsTemporary, () const, bool), AS_CALL_THISCALL);
    // bool Drawable::IsZoneDirty() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Drawable2D", "bool IsZoneDirty() const", AS_METHODPR(Drawable2D, IsZoneDirty, () const, bool), AS_CALL_THISCALL);
    // void Drawable::LimitLights() | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Drawable2D", "void LimitLights()", AS_METHODPR(Drawable2D, LimitLights, (), void), AS_CALL_THISCALL);
    // void Drawable::LimitVertexLights(bool removeConvertedLights) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Drawable2D", "void LimitVertexLights(bool)", AS_METHODPR(Drawable2D, LimitVertexLights, (bool), void), AS_CALL_THISCALL);
    // virtual bool Serializable::Load(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Drawable2D", "bool Load(Deserializer&)", AS_METHODPR(Drawable2D, Load, (Deserializer&), bool), AS_CALL_THISCALL);
    // bool Animatable::LoadJSON(const JSONValue& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Drawable2D", "bool LoadJSON(const JSONValue&in)", AS_METHODPR(Drawable2D, LoadJSON, (const JSONValue&), bool), AS_CALL_THISCALL);
    // bool Animatable::LoadXML(const XMLElement& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Drawable2D", "bool LoadXML(const XMLElement&in)", AS_METHODPR(Drawable2D, LoadXML, (const XMLElement&), bool), AS_CALL_THISCALL);
    // void Drawable::MarkForUpdate() | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Drawable2D", "void MarkForUpdate()", AS_METHODPR(Drawable2D, MarkForUpdate, (), void), AS_CALL_THISCALL);
    // void Drawable::MarkInView(const FrameInfo& frame) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Drawable2D", "void MarkInView(const FrameInfo&in)", AS_METHODPR(Drawable2D, MarkInView, (const FrameInfo&), void), AS_CALL_THISCALL);
    // void Drawable::MarkInView(unsigned frameNumber) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Drawable2D", "void MarkInView(uint)", AS_METHODPR(Drawable2D, MarkInView, (unsigned), void), AS_CALL_THISCALL);
    // void Component::MarkNetworkUpdate() override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Drawable2D", "void MarkNetworkUpdate()", AS_METHODPR(Drawable2D, MarkNetworkUpdate, (), void), AS_CALL_THISCALL);
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Drawable2D", "void OnEvent(Object@+, StringHash, VariantMap&)", AS_METHODPR(Drawable2D, OnEvent, (Object*, StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // virtual void Serializable::OnGetAttribute(const AttributeInfo& attr, Variant& dest) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Drawable2D", "void OnGetAttribute(const AttributeInfo&in, Variant&) const", AS_METHODPR(Drawable2D, OnGetAttribute, (const AttributeInfo&, Variant&) const, void), AS_CALL_THISCALL);
    // virtual void Serializable::OnSetAttribute(const AttributeInfo& attr, const Variant& src) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Drawable2D", "void OnSetAttribute(const AttributeInfo&in, const Variant&in)", AS_METHODPR(Drawable2D, OnSetAttribute, (const AttributeInfo&, const Variant&), void), AS_CALL_THISCALL);
    // void Drawable2D::OnSetEnabled() override | File: ../Urho2D/Drawable2D.h
    engine->RegisterObjectMethod("Drawable2D", "void OnSetEnabled()", AS_METHODPR(Drawable2D, OnSetEnabled, (), void), AS_CALL_THISCALL);
    // void Component::PrepareNetworkUpdate() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Drawable2D", "void PrepareNetworkUpdate()", AS_METHODPR(Drawable2D, PrepareNetworkUpdate, (), void), AS_CALL_THISCALL);
    // virtual void Drawable::ProcessRayQuery(const RayOctreeQuery& query, PODVector<RayQueryResult>& results) | File: ../Graphics/Drawable.h
    // Error: type "RayOctreeQuery" can not automatically bind bacause have @nobind mark
    // bool Serializable::ReadDeltaUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Drawable2D", "bool ReadDeltaUpdate(Deserializer&)", AS_METHODPR(Drawable2D, ReadDeltaUpdate, (Deserializer&), bool), AS_CALL_THISCALL);
    // bool Serializable::ReadLatestDataUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Drawable2D", "bool ReadLatestDataUpdate(Deserializer&)", AS_METHODPR(Drawable2D, ReadLatestDataUpdate, (Deserializer&), bool), AS_CALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("Drawable2D", "int Refs() const", AS_METHODPR(Drawable2D, Refs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Drawable2D", "int get_refs() const", AS_METHODPR(Drawable2D, Refs, () const, int), AS_CALL_THISCALL);
    // static void Drawable2D::RegisterObject(Context* context) | File: ../Urho2D/Drawable2D.h
    // Not registered because have @nobind mark
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("Drawable2D", asBEHAVE_RELEASE, "void f()", AS_METHODPR(Drawable2D, ReleaseRef, (), void), AS_CALL_THISCALL);
    // void Component::Remove() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Drawable2D", "void Remove()", AS_METHODPR(Drawable2D, Remove, (), void), AS_CALL_THISCALL);
    // void Animatable::RemoveAttributeAnimation(const String& name) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Drawable2D", "void RemoveAttributeAnimation(const String&in)", AS_METHODPR(Drawable2D, RemoveAttributeAnimation, (const String&), void), AS_CALL_THISCALL);
    // void Serializable::RemoveInstanceDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Drawable2D", "void RemoveInstanceDefault()", AS_METHODPR(Drawable2D, RemoveInstanceDefault, (), void), AS_CALL_THISCALL);
    // void Animatable::RemoveObjectAnimation() | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Drawable2D", "void RemoveObjectAnimation()", AS_METHODPR(Drawable2D, RemoveObjectAnimation, (), void), AS_CALL_THISCALL);
    // void Serializable::ResetToDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Drawable2D", "void ResetToDefault()", AS_METHODPR(Drawable2D, ResetToDefault, (), void), AS_CALL_THISCALL);
    // bool Component::Save(Serializer& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Drawable2D", "bool Save(Serializer&) const", AS_METHODPR(Drawable2D, Save, (Serializer&) const, bool), AS_CALL_THISCALL);
    // virtual bool Serializable::SaveDefaultAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Drawable2D", "bool SaveDefaultAttributes() const", AS_METHODPR(Drawable2D, SaveDefaultAttributes, () const, bool), AS_CALL_THISCALL);
    // bool Component::SaveJSON(JSONValue& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Drawable2D", "bool SaveJSON(JSONValue&) const", AS_METHODPR(Drawable2D, SaveJSON, (JSONValue&) const, bool), AS_CALL_THISCALL);
    // bool Component::SaveXML(XMLElement& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Drawable2D", "bool SaveXML(XMLElement&) const", AS_METHODPR(Drawable2D, SaveXML, (XMLElement&) const, bool), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Drawable2D", "void SendEvent(StringHash)", AS_METHODPR(Drawable2D, SendEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Drawable2D", "void SendEvent(StringHash, VariantMap&)", AS_METHODPR(Drawable2D, SendEvent, (StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void Animatable::SetAnimationEnabled(bool enable) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Drawable2D", "void SetAnimationEnabled(bool)", AS_METHODPR(Drawable2D, SetAnimationEnabled, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Drawable2D", "void set_animationEnabled(bool)", AS_METHODPR(Drawable2D, SetAnimationEnabled, (bool), void), AS_CALL_THISCALL);
    // void Animatable::SetAnimationTime(float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Drawable2D", "void SetAnimationTime(float)", AS_METHODPR(Drawable2D, SetAnimationTime, (float), void), AS_CALL_THISCALL);
    // bool Serializable::SetAttribute(unsigned index, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Drawable2D", "bool SetAttribute(uint, const Variant&in)", AS_METHODPR(Drawable2D, SetAttribute, (unsigned, const Variant&), bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Drawable2D", "bool set_attributes(uint, const Variant&in)", AS_METHODPR(Drawable2D, SetAttribute, (unsigned, const Variant&), bool), AS_CALL_THISCALL);
    // bool Serializable::SetAttribute(const String& name, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Drawable2D", "bool SetAttribute(const String&in, const Variant&in)", AS_METHODPR(Drawable2D, SetAttribute, (const String&, const Variant&), bool), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimation(const String& name, ValueAnimation* attributeAnimation, WrapMode wrapMode=WM_LOOP, float speed=1.0f) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Drawable2D", "void SetAttributeAnimation(const String&in, ValueAnimation@+, WrapMode = WM_LOOP, float = 1.0f)", AS_METHODPR(Drawable2D, SetAttributeAnimation, (const String&, ValueAnimation*, WrapMode, float), void), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimationSpeed(const String& name, float speed) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Drawable2D", "void SetAttributeAnimationSpeed(const String&in, float)", AS_METHODPR(Drawable2D, SetAttributeAnimationSpeed, (const String&, float), void), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimationTime(const String& name, float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Drawable2D", "void SetAttributeAnimationTime(const String&in, float)", AS_METHODPR(Drawable2D, SetAttributeAnimationTime, (const String&, float), void), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimationWrapMode(const String& name, WrapMode wrapMode) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Drawable2D", "void SetAttributeAnimationWrapMode(const String&in, WrapMode)", AS_METHODPR(Drawable2D, SetAttributeAnimationWrapMode, (const String&, WrapMode), void), AS_CALL_THISCALL);
    // void Drawable::SetBasePass(unsigned batchIndex) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Drawable2D", "void SetBasePass(uint)", AS_METHODPR(Drawable2D, SetBasePass, (unsigned), void), AS_CALL_THISCALL);
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Drawable2D", "void SetBlockEvents(bool)", AS_METHODPR(Drawable2D, SetBlockEvents, (bool), void), AS_CALL_THISCALL);
    // void Drawable::SetCastShadows(bool enable) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Drawable2D", "void SetCastShadows(bool)", AS_METHODPR(Drawable2D, SetCastShadows, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Drawable2D", "void set_castShadows(bool)", AS_METHODPR(Drawable2D, SetCastShadows, (bool), void), AS_CALL_THISCALL);
    // void Drawable::SetDrawDistance(float distance) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Drawable2D", "void SetDrawDistance(float)", AS_METHODPR(Drawable2D, SetDrawDistance, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Drawable2D", "void set_drawDistance(float)", AS_METHODPR(Drawable2D, SetDrawDistance, (float), void), AS_CALL_THISCALL);
    // void Component::SetEnabled(bool enable) | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Drawable2D", "void SetEnabled(bool)", AS_METHODPR(Drawable2D, SetEnabled, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Drawable2D", "void set_enabled(bool)", AS_METHODPR(Drawable2D, SetEnabled, (bool), void), AS_CALL_THISCALL);
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Drawable2D", "void SetGlobalVar(StringHash, const Variant&in)", AS_METHODPR(Drawable2D, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Drawable2D", "void set_globalVar(StringHash, const Variant&in)", AS_METHODPR(Drawable2D, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    // void Serializable::SetInstanceDefault(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Drawable2D", "void SetInstanceDefault(bool)", AS_METHODPR(Drawable2D, SetInstanceDefault, (bool), void), AS_CALL_THISCALL);
    // void Serializable::SetInterceptNetworkUpdate(const String& attributeName, bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Drawable2D", "void SetInterceptNetworkUpdate(const String&in, bool)", AS_METHODPR(Drawable2D, SetInterceptNetworkUpdate, (const String&, bool), void), AS_CALL_THISCALL);
    // void Drawable2D::SetLayer(int layer) | File: ../Urho2D/Drawable2D.h
    engine->RegisterObjectMethod("Drawable2D", "void SetLayer(int)", AS_METHODPR(Drawable2D, SetLayer, (int), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Drawable2D", "void set_layer(int)", AS_METHODPR(Drawable2D, SetLayer, (int), void), AS_CALL_THISCALL);
    // void Drawable::SetLightMask(unsigned mask) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Drawable2D", "void SetLightMask(uint)", AS_METHODPR(Drawable2D, SetLightMask, (unsigned), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Drawable2D", "void set_lightMask(uint)", AS_METHODPR(Drawable2D, SetLightMask, (unsigned), void), AS_CALL_THISCALL);
    // void Drawable::SetLodBias(float bias) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Drawable2D", "void SetLodBias(float)", AS_METHODPR(Drawable2D, SetLodBias, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Drawable2D", "void set_lodBias(float)", AS_METHODPR(Drawable2D, SetLodBias, (float), void), AS_CALL_THISCALL);
    // void Drawable::SetMaxLights(unsigned num) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Drawable2D", "void SetMaxLights(uint)", AS_METHODPR(Drawable2D, SetMaxLights, (unsigned), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Drawable2D", "void set_maxLights(uint)", AS_METHODPR(Drawable2D, SetMaxLights, (unsigned), void), AS_CALL_THISCALL);
    // void Drawable::SetMinMaxZ(float minZ, float maxZ) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Drawable2D", "void SetMinMaxZ(float, float)", AS_METHODPR(Drawable2D, SetMinMaxZ, (float, float), void), AS_CALL_THISCALL);
    // void Animatable::SetObjectAnimation(ObjectAnimation* objectAnimation) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Drawable2D", "void SetObjectAnimation(ObjectAnimation@+)", AS_METHODPR(Drawable2D, SetObjectAnimation, (ObjectAnimation*), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Drawable2D", "void set_objectAnimation(ObjectAnimation@+)", AS_METHODPR(Drawable2D, SetObjectAnimation, (ObjectAnimation*), void), AS_CALL_THISCALL);
    // void Animatable::SetObjectAnimationAttr(const ResourceRef& value) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Drawable2D", "void SetObjectAnimationAttr(const ResourceRef&in)", AS_METHODPR(Drawable2D, SetObjectAnimationAttr, (const ResourceRef&), void), AS_CALL_THISCALL);
    // void Drawable::SetOccludee(bool enable) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Drawable2D", "void SetOccludee(bool)", AS_METHODPR(Drawable2D, SetOccludee, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Drawable2D", "void set_occludee(bool)", AS_METHODPR(Drawable2D, SetOccludee, (bool), void), AS_CALL_THISCALL);
    // void Drawable::SetOccluder(bool enable) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Drawable2D", "void SetOccluder(bool)", AS_METHODPR(Drawable2D, SetOccluder, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Drawable2D", "void set_occluder(bool)", AS_METHODPR(Drawable2D, SetOccluder, (bool), void), AS_CALL_THISCALL);
    // void Drawable2D::SetOrderInLayer(int orderInLayer) | File: ../Urho2D/Drawable2D.h
    engine->RegisterObjectMethod("Drawable2D", "void SetOrderInLayer(int)", AS_METHODPR(Drawable2D, SetOrderInLayer, (int), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Drawable2D", "void set_orderInLayer(int)", AS_METHODPR(Drawable2D, SetOrderInLayer, (int), void), AS_CALL_THISCALL);
    // void Drawable::SetShadowDistance(float distance) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Drawable2D", "void SetShadowDistance(float)", AS_METHODPR(Drawable2D, SetShadowDistance, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Drawable2D", "void set_shadowDistance(float)", AS_METHODPR(Drawable2D, SetShadowDistance, (float), void), AS_CALL_THISCALL);
    // void Drawable::SetShadowMask(unsigned mask) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Drawable2D", "void SetShadowMask(uint)", AS_METHODPR(Drawable2D, SetShadowMask, (unsigned), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Drawable2D", "void set_shadowMask(uint)", AS_METHODPR(Drawable2D, SetShadowMask, (unsigned), void), AS_CALL_THISCALL);
    // void Drawable::SetSortValue(float value) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Drawable2D", "void SetSortValue(float)", AS_METHODPR(Drawable2D, SetSortValue, (float), void), AS_CALL_THISCALL);
    // void Serializable::SetTemporary(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Drawable2D", "void SetTemporary(bool)", AS_METHODPR(Drawable2D, SetTemporary, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Drawable2D", "void set_temporary(bool)", AS_METHODPR(Drawable2D, SetTemporary, (bool), void), AS_CALL_THISCALL);
    // void Drawable::SetViewMask(unsigned mask) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Drawable2D", "void SetViewMask(uint)", AS_METHODPR(Drawable2D, SetViewMask, (unsigned), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Drawable2D", "void set_viewMask(uint)", AS_METHODPR(Drawable2D, SetViewMask, (unsigned), void), AS_CALL_THISCALL);
    // void Drawable::SetZone(Zone* zone, bool temporary=false) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Drawable2D", "void SetZone(Zone@+, bool = false)", AS_METHODPR(Drawable2D, SetZone, (Zone*, bool), void), AS_CALL_THISCALL);
    // void Drawable::SetZoneMask(unsigned mask) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Drawable2D", "void SetZoneMask(uint)", AS_METHODPR(Drawable2D, SetZoneMask, (unsigned), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Drawable2D", "void set_zoneMask(uint)", AS_METHODPR(Drawable2D, SetZoneMask, (unsigned), void), AS_CALL_THISCALL);
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod("Drawable2D", "void UnsubscribeFromAllEvents()", AS_METHODPR(Drawable2D, UnsubscribeFromAllEvents, (), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Drawable2D", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", AS_FUNCTION_OBJFIRST(Drawable2D_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), AS_CALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Drawable2D", "void UnsubscribeFromEvent(StringHash)", AS_METHODPR(Drawable2D, UnsubscribeFromEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Drawable2D", "void UnsubscribeFromEvent(Object@+, StringHash)", AS_METHODPR(Drawable2D, UnsubscribeFromEvent, (Object*, StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Drawable2D", "void UnsubscribeFromEvents(Object@+)", AS_METHODPR(Drawable2D, UnsubscribeFromEvents, (Object*), void), AS_CALL_THISCALL);
    // virtual void Drawable::Update(const FrameInfo& frame) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Drawable2D", "void Update(const FrameInfo&in)", AS_METHODPR(Drawable2D, Update, (const FrameInfo&), void), AS_CALL_THISCALL);
    // virtual void Drawable::UpdateBatches(const FrameInfo& frame) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Drawable2D", "void UpdateBatches(const FrameInfo&in)", AS_METHODPR(Drawable2D, UpdateBatches, (const FrameInfo&), void), AS_CALL_THISCALL);
    // virtual void Drawable::UpdateGeometry(const FrameInfo& frame) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Drawable2D", "void UpdateGeometry(const FrameInfo&in)", AS_METHODPR(Drawable2D, UpdateGeometry, (const FrameInfo&), void), AS_CALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("Drawable2D", "int WeakRefs() const", AS_METHODPR(Drawable2D, WeakRefs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Drawable2D", "int get_weakRefs() const", AS_METHODPR(Drawable2D, WeakRefs, () const, int), AS_CALL_THISCALL);
    // void Serializable::WriteDeltaUpdate(Serializer& dest, const DirtyBits& attributeBits, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Drawable2D", "void WriteDeltaUpdate(Serializer&, const DirtyBits&in, uint8)", AS_METHODPR(Drawable2D, WriteDeltaUpdate, (Serializer&, const DirtyBits&, unsigned char), void), AS_CALL_THISCALL);
    // void Serializable::WriteInitialDeltaUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Drawable2D", "void WriteInitialDeltaUpdate(Serializer&, uint8)", AS_METHODPR(Drawable2D, WriteInitialDeltaUpdate, (Serializer&, unsigned char), void), AS_CALL_THISCALL);
    // void Serializable::WriteLatestDataUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Drawable2D", "void WriteLatestDataUpdate(Serializer&, uint8)", AS_METHODPR(Drawable2D, WriteLatestDataUpdate, (Serializer&, unsigned char), void), AS_CALL_THISCALL);
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
    engine->RegisterObjectMethod("DropDownList", "void AddChild(UIElement@+)", AS_METHODPR(DropDownList, AddChild, (UIElement*), void), AS_CALL_THISCALL);
    // void DropDownList::AddItem(UIElement* item) | File: ../UI/DropDownList.h
    engine->RegisterObjectMethod("DropDownList", "void AddItem(UIElement@+)", AS_METHODPR(DropDownList, AddItem, (UIElement*), void), AS_CALL_THISCALL);
    // void RefCounted::AddRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("DropDownList", asBEHAVE_ADDREF, "void f()", AS_METHODPR(DropDownList, AddRef, (), void), AS_CALL_THISCALL);
    // void UIElement::AddTag(const String& tag) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "void AddTag(const String&in)", AS_METHODPR(DropDownList, AddTag, (const String&), void), AS_CALL_THISCALL);
    // void UIElement::AddTags(const String& tags, char separator=';') | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "void AddTags(const String&in, int8 = ';')", AS_METHODPR(DropDownList, AddTags, (const String&, char), void), AS_CALL_THISCALL);
    // void UIElement::AddTags(const StringVector& tags) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "void AddTags(Array<String>@+)", AS_FUNCTION_OBJFIRST(DropDownList_AddTags_StringVector), AS_CALL_CDECL_OBJFIRST);
    // void UIElement::AdjustScissor(IntRect& currentScissor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "void AdjustScissor(IntRect&)", AS_METHODPR(DropDownList, AdjustScissor, (IntRect&), void), AS_CALL_THISCALL);
    // void Serializable::AllocateNetworkState() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("DropDownList", "void AllocateNetworkState()", AS_METHODPR(DropDownList, AllocateNetworkState, (), void), AS_CALL_THISCALL);
    // void DropDownList::ApplyAttributes() override | File: ../UI/DropDownList.h
    engine->RegisterObjectMethod("DropDownList", "void ApplyAttributes()", AS_METHODPR(DropDownList, ApplyAttributes, (), void), AS_CALL_THISCALL);
    // void UIElement::BringToFront() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "void BringToFront()", AS_METHODPR(DropDownList, BringToFront, (), void), AS_CALL_THISCALL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // UIElement* UIElement::CreateChild(StringHash type, const String& name=String::EMPTY, unsigned index=M_MAX_UNSIGNED) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "UIElement@+ CreateChild(StringHash, const String&in = String::EMPTY, uint = M_MAX_UNSIGNED)", AS_METHODPR(DropDownList, CreateChild, (StringHash, const String&, unsigned), UIElement*), AS_CALL_THISCALL);
    // template<class T> T* UIElement::CreateChild(const String& name=String::EMPTY, unsigned index=M_MAX_UNSIGNED) | File: ../UI/UIElement.h
    // Not registered because template
    // void UIElement::DisableLayoutUpdate() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "void DisableLayoutUpdate()", AS_METHODPR(DropDownList, DisableLayoutUpdate, (), void), AS_CALL_THISCALL);
    // explicit DropDownList::DropDownList(Context* context) | File: ../UI/DropDownList.h
    engine->RegisterObjectBehaviour("DropDownList", asBEHAVE_FACTORY, "DropDownList@+ f()", AS_FUNCTION(DropDownList_DropDownList_Context), AS_CALL_CDECL);
    // virtual IntVector2 UIElement::ElementToScreen(const IntVector2& position) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "IntVector2 ElementToScreen(const IntVector2&in)", AS_METHODPR(DropDownList, ElementToScreen, (const IntVector2&), IntVector2), AS_CALL_THISCALL);
    // void UIElement::EnableLayoutUpdate() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "void EnableLayoutUpdate()", AS_METHODPR(DropDownList, EnableLayoutUpdate, (), void), AS_CALL_THISCALL);
    // bool UIElement::FilterAttributes(XMLElement& dest) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "bool FilterAttributes(XMLElement&) const", AS_METHODPR(DropDownList, FilterAttributes, (XMLElement&) const, bool), AS_CALL_THISCALL);
    // unsigned UIElement::FindChild(UIElement* element) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "uint FindChild(UIElement@+) const", AS_METHODPR(DropDownList, FindChild, (UIElement*) const, unsigned), AS_CALL_THISCALL);
    // int Menu::GetAcceleratorKey() const | File: ../UI/Menu.h
    engine->RegisterObjectMethod("DropDownList", "int GetAcceleratorKey() const", AS_METHODPR(DropDownList, GetAcceleratorKey, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "int get_acceleratorKey() const", AS_METHODPR(DropDownList, GetAcceleratorKey, () const, int), AS_CALL_THISCALL);
    // int Menu::GetAcceleratorQualifiers() const | File: ../UI/Menu.h
    engine->RegisterObjectMethod("DropDownList", "int GetAcceleratorQualifiers() const", AS_METHODPR(DropDownList, GetAcceleratorQualifiers, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "int get_acceleratorQualifiers() const", AS_METHODPR(DropDownList, GetAcceleratorQualifiers, () const, int), AS_CALL_THISCALL);
    // bool Animatable::GetAnimationEnabled() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("DropDownList", "bool GetAnimationEnabled() const", AS_METHODPR(DropDownList, GetAnimationEnabled, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "bool get_animationEnabled() const", AS_METHODPR(DropDownList, GetAnimationEnabled, () const, bool), AS_CALL_THISCALL);
    // const String& UIElement::GetAppliedStyle() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "const String& GetAppliedStyle() const", AS_METHODPR(DropDownList, GetAppliedStyle, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "const String& get_style() const", AS_METHODPR(DropDownList, GetAppliedStyle, () const, const String&), AS_CALL_THISCALL);
    // Variant Serializable::GetAttribute(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("DropDownList", "Variant GetAttribute(uint) const", AS_METHODPR(DropDownList, GetAttribute, (unsigned) const, Variant), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "Variant get_attributes(uint) const", AS_METHODPR(DropDownList, GetAttribute, (unsigned) const, Variant), AS_CALL_THISCALL);
    // Variant Serializable::GetAttribute(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("DropDownList", "Variant GetAttribute(const String&in) const", AS_METHODPR(DropDownList, GetAttribute, (const String&) const, Variant), AS_CALL_THISCALL);
    // ValueAnimation* Animatable::GetAttributeAnimation(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("DropDownList", "ValueAnimation@+ GetAttributeAnimation(const String&in) const", AS_METHODPR(DropDownList, GetAttributeAnimation, (const String&) const, ValueAnimation*), AS_CALL_THISCALL);
    // float Animatable::GetAttributeAnimationSpeed(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("DropDownList", "float GetAttributeAnimationSpeed(const String&in) const", AS_METHODPR(DropDownList, GetAttributeAnimationSpeed, (const String&) const, float), AS_CALL_THISCALL);
    // float Animatable::GetAttributeAnimationTime(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("DropDownList", "float GetAttributeAnimationTime(const String&in) const", AS_METHODPR(DropDownList, GetAttributeAnimationTime, (const String&) const, float), AS_CALL_THISCALL);
    // WrapMode Animatable::GetAttributeAnimationWrapMode(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("DropDownList", "WrapMode GetAttributeAnimationWrapMode(const String&in) const", AS_METHODPR(DropDownList, GetAttributeAnimationWrapMode, (const String&) const, WrapMode), AS_CALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("DropDownList", "Variant GetAttributeDefault(uint) const", AS_METHODPR(DropDownList, GetAttributeDefault, (unsigned) const, Variant), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "Variant get_attributeDefaults(uint) const", AS_METHODPR(DropDownList, GetAttributeDefault, (unsigned) const, Variant), AS_CALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("DropDownList", "Variant GetAttributeDefault(const String&in) const", AS_METHODPR(DropDownList, GetAttributeDefault, (const String&) const, Variant), AS_CALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // void DropDownList::GetBatches(PODVector<UIBatch>& batches, PODVector<float>& vertexData, const IntRect& currentScissor) override | File: ../UI/DropDownList.h
    // Error: type "PODVector<UIBatch>&" can not automatically bind
    // void UIElement::GetBatchesWithOffset(IntVector2& offset, PODVector<UIBatch>& batches, PODVector<float>& vertexData, IntRect currentScissor) | File: ../UI/UIElement.h
    // Error: type "PODVector<UIBatch>&" can not automatically bind
    // BlendMode BorderImage::GetBlendMode() const | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("DropDownList", "BlendMode GetBlendMode() const", AS_METHODPR(DropDownList, GetBlendMode, () const, BlendMode), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "BlendMode get_blendMode() const", AS_METHODPR(DropDownList, GetBlendMode, () const, BlendMode), AS_CALL_THISCALL);
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("DropDownList", "bool GetBlockEvents() const", AS_METHODPR(DropDownList, GetBlockEvents, () const, bool), AS_CALL_THISCALL);
    // const IntRect& BorderImage::GetBorder() const | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("DropDownList", "const IntRect& GetBorder() const", AS_METHODPR(DropDownList, GetBorder, () const, const IntRect&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "const IntRect& get_border() const", AS_METHODPR(DropDownList, GetBorder, () const, const IntRect&), AS_CALL_THISCALL);
    // bool UIElement::GetBringToBack() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "bool GetBringToBack() const", AS_METHODPR(DropDownList, GetBringToBack, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "bool get_bringToBack() const", AS_METHODPR(DropDownList, GetBringToBack, () const, bool), AS_CALL_THISCALL);
    // bool UIElement::GetBringToFront() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "bool GetBringToFront() const", AS_METHODPR(DropDownList, GetBringToFront, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "bool get_bringToFront() const", AS_METHODPR(DropDownList, GetBringToFront, () const, bool), AS_CALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("DropDownList", "const String& GetCategory() const", AS_METHODPR(DropDownList, GetCategory, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "const String& get_category() const", AS_METHODPR(DropDownList, GetCategory, () const, const String&), AS_CALL_THISCALL);
    // UIElement* UIElement::GetChild(unsigned index) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "UIElement@+ GetChild(uint) const", AS_METHODPR(DropDownList, GetChild, (unsigned) const, UIElement*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "UIElement@+ get_children(uint) const", AS_METHODPR(DropDownList, GetChild, (unsigned) const, UIElement*), AS_CALL_THISCALL);
    // UIElement* UIElement::GetChild(const String& name, bool recursive=false) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "UIElement@+ GetChild(const String&in, bool = false) const", AS_METHODPR(DropDownList, GetChild, (const String&, bool) const, UIElement*), AS_CALL_THISCALL);
    // UIElement* UIElement::GetChild(const StringHash& key, const Variant& value=Variant::EMPTY, bool recursive=false) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "UIElement@+ GetChild(const StringHash&in, const Variant&in = Variant::EMPTY, bool = false) const", AS_METHODPR(DropDownList, GetChild, (const StringHash&, const Variant&, bool) const, UIElement*), AS_CALL_THISCALL);
    // template<class T> T* UIElement::GetChildDynamicCast(unsigned index) const | File: ../UI/UIElement.h
    // Not registered because template
    // template<class T> T* UIElement::GetChildDynamicCast(const String& name, bool recursive=false) const | File: ../UI/UIElement.h
    // Not registered because template
    // template<class T> T* UIElement::GetChildDynamicCast(const StringHash& key, const Variant& value=Variant::EMPTY, bool recursive=false) const | File: ../UI/UIElement.h
    // Not registered because template
    // const IntVector2& UIElement::GetChildOffset() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "const IntVector2& GetChildOffset() const", AS_METHODPR(DropDownList, GetChildOffset, () const, const IntVector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "const IntVector2& get_childOffset() const", AS_METHODPR(DropDownList, GetChildOffset, () const, const IntVector2&), AS_CALL_THISCALL);
    // const Vector<SharedPtr<UIElement>>& UIElement::GetChildren() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "Array<UIElement@>@ GetChildren() const", AS_FUNCTION_OBJFIRST(DropDownList_GetChildren_void), AS_CALL_CDECL_OBJFIRST);
    // void UIElement::GetChildren(PODVector<UIElement*>& dest, bool recursive=false) const | File: ../UI/UIElement.h
    // Error: type "PODVector<UIElement*>&" can not automatically bind
    // PODVector<UIElement*> UIElement::GetChildren(bool recursive) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "Array<UIElement@>@ GetChildren(bool) const", AS_FUNCTION_OBJFIRST(DropDownList_GetChildren_bool), AS_CALL_CDECL_OBJFIRST);
    // void UIElement::GetChildrenWithTag(PODVector<UIElement*>& dest, const String& tag, bool recursive=false) const | File: ../UI/UIElement.h
    // Error: type "PODVector<UIElement*>&" can not automatically bind
    // PODVector<UIElement*> UIElement::GetChildrenWithTag(const String& tag, bool recursive=false) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "Array<UIElement@>@ GetChildrenWithTag(const String&in, bool = false) const", AS_FUNCTION_OBJFIRST(DropDownList_GetChildrenWithTag_String_bool), AS_CALL_CDECL_OBJFIRST);
    // template<class T> T* UIElement::GetChildStaticCast(unsigned index) const | File: ../UI/UIElement.h
    // Not registered because template
    // template<class T> T* UIElement::GetChildStaticCast(const String& name, bool recursive=false) const | File: ../UI/UIElement.h
    // Not registered because template
    // template<class T> T* UIElement::GetChildStaticCast(const StringHash& key, const Variant& value=Variant::EMPTY, bool recursive=false) const | File: ../UI/UIElement.h
    // Not registered because template
    // const IntRect& UIElement::GetClipBorder() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "const IntRect& GetClipBorder() const", AS_METHODPR(DropDownList, GetClipBorder, () const, const IntRect&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "const IntRect& get_clipBorder() const", AS_METHODPR(DropDownList, GetClipBorder, () const, const IntRect&), AS_CALL_THISCALL);
    // bool UIElement::GetClipChildren() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "bool GetClipChildren() const", AS_METHODPR(DropDownList, GetClipChildren, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "bool get_clipChildren() const", AS_METHODPR(DropDownList, GetClipChildren, () const, bool), AS_CALL_THISCALL);
    // const Color& UIElement::GetColor(Corner corner) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "const Color& GetColor(Corner) const", AS_METHODPR(DropDownList, GetColor, (Corner) const, const Color&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "const Color& get_colors(Corner) const", AS_METHODPR(DropDownList, GetColor, (Corner) const, const Color&), AS_CALL_THISCALL);
    // const Color& UIElement::GetColorAttr() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "const Color& GetColorAttr() const", AS_METHODPR(DropDownList, GetColorAttr, () const, const Color&), AS_CALL_THISCALL);
    // IntRect UIElement::GetCombinedScreenRect() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "IntRect GetCombinedScreenRect()", AS_METHODPR(DropDownList, GetCombinedScreenRect, (), IntRect), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "IntRect get_combinedScreenRect()", AS_METHODPR(DropDownList, GetCombinedScreenRect, (), IntRect), AS_CALL_THISCALL);
    // Context* Object::GetContext() const | File: ../Core/Object.h
    // Error: type "Context*" can used only as function parameter
    // virtual void UIElement::GetDebugDrawBatches(PODVector<UIBatch>& batches, PODVector<float>& vertexData, const IntRect& currentScissor) | File: ../UI/UIElement.h
    // Error: type "PODVector<UIBatch>&" can not automatically bind
    // XMLFile* UIElement::GetDefaultStyle(bool recursiveUp=true) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "XMLFile@+ GetDefaultStyle(bool = true) const", AS_METHODPR(DropDownList, GetDefaultStyle, (bool) const, XMLFile*), AS_CALL_THISCALL);
    // const Color& UIElement::GetDerivedColor() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "const Color& GetDerivedColor() const", AS_METHODPR(DropDownList, GetDerivedColor, () const, const Color&), AS_CALL_THISCALL);
    // float UIElement::GetDerivedOpacity() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "float GetDerivedOpacity() const", AS_METHODPR(DropDownList, GetDerivedOpacity, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "float get_derivedOpacity() const", AS_METHODPR(DropDownList, GetDerivedOpacity, () const, float), AS_CALL_THISCALL);
    // const IntVector2& BorderImage::GetDisabledOffset() const | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("DropDownList", "const IntVector2& GetDisabledOffset() const", AS_METHODPR(DropDownList, GetDisabledOffset, () const, const IntVector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "const IntVector2& get_disabledOffset() const", AS_METHODPR(DropDownList, GetDisabledOffset, () const, const IntVector2&), AS_CALL_THISCALL);
    // MouseButtonFlags UIElement::GetDragButtonCombo() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "MouseButtonFlags GetDragButtonCombo() const", AS_METHODPR(DropDownList, GetDragButtonCombo, () const, MouseButtonFlags), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "MouseButtonFlags get_dragButtonCombo() const", AS_METHODPR(DropDownList, GetDragButtonCombo, () const, MouseButtonFlags), AS_CALL_THISCALL);
    // unsigned UIElement::GetDragButtonCount() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "uint GetDragButtonCount() const", AS_METHODPR(DropDownList, GetDragButtonCount, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "uint get_dragButtonCount() const", AS_METHODPR(DropDownList, GetDragButtonCount, () const, unsigned), AS_CALL_THISCALL);
    // DragAndDropModeFlags UIElement::GetDragDropMode() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "DragAndDropModeFlags GetDragDropMode() const", AS_METHODPR(DropDownList, GetDragDropMode, () const, DragAndDropModeFlags), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "DragAndDropModeFlags get_dragDropMode() const", AS_METHODPR(DropDownList, GetDragDropMode, () const, DragAndDropModeFlags), AS_CALL_THISCALL);
    // IntVector2 UIElement::GetEffectiveMinSize() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "IntVector2 GetEffectiveMinSize() const", AS_METHODPR(DropDownList, GetEffectiveMinSize, () const, IntVector2), AS_CALL_THISCALL);
    // UIElement* UIElement::GetElementEventSender() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "UIElement@+ GetElementEventSender() const", AS_METHODPR(DropDownList, GetElementEventSender, () const, UIElement*), AS_CALL_THISCALL);
    // bool UIElement::GetEnableAnchor() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "bool GetEnableAnchor() const", AS_METHODPR(DropDownList, GetEnableAnchor, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "bool get_enableAnchor() const", AS_METHODPR(DropDownList, GetEnableAnchor, () const, bool), AS_CALL_THISCALL);
    // VariantMap& Object::GetEventDataMap() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("DropDownList", "VariantMap& GetEventDataMap() const", AS_METHODPR(DropDownList, GetEventDataMap, () const, VariantMap&), AS_CALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("DropDownList", "Object@+ GetEventSender() const", AS_METHODPR(DropDownList, GetEventSender, () const, Object*), AS_CALL_THISCALL);
    // FocusMode UIElement::GetFocusMode() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "FocusMode GetFocusMode() const", AS_METHODPR(DropDownList, GetFocusMode, () const, FocusMode), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "FocusMode get_focusMode() const", AS_METHODPR(DropDownList, GetFocusMode, () const, FocusMode), AS_CALL_THISCALL);
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("DropDownList", "const Variant& GetGlobalVar(StringHash) const", AS_METHODPR(DropDownList, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "const Variant& get_globalVar(StringHash) const", AS_METHODPR(DropDownList, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("DropDownList", "const VariantMap& GetGlobalVars() const", AS_METHODPR(DropDownList, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "const VariantMap& get_globalVars() const", AS_METHODPR(DropDownList, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    // int UIElement::GetHeight() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "int GetHeight() const", AS_METHODPR(DropDownList, GetHeight, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "int get_height() const", AS_METHODPR(DropDownList, GetHeight, () const, int), AS_CALL_THISCALL);
    // HorizontalAlignment UIElement::GetHorizontalAlignment() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "HorizontalAlignment GetHorizontalAlignment() const", AS_METHODPR(DropDownList, GetHorizontalAlignment, () const, HorizontalAlignment), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "HorizontalAlignment get_horizontalAlignment() const", AS_METHODPR(DropDownList, GetHorizontalAlignment, () const, HorizontalAlignment), AS_CALL_THISCALL);
    // const IntVector2& BorderImage::GetHoverOffset() const | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("DropDownList", "const IntVector2& GetHoverOffset() const", AS_METHODPR(DropDownList, GetHoverOffset, () const, const IntVector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "const IntVector2& get_hoverOffset() const", AS_METHODPR(DropDownList, GetHoverOffset, () const, const IntVector2&), AS_CALL_THISCALL);
    // const IntRect& BorderImage::GetImageBorder() const | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("DropDownList", "const IntRect& GetImageBorder() const", AS_METHODPR(DropDownList, GetImageBorder, () const, const IntRect&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "const IntRect& get_imageBorder() const", AS_METHODPR(DropDownList, GetImageBorder, () const, const IntRect&), AS_CALL_THISCALL);
    // const IntRect& BorderImage::GetImageRect() const | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("DropDownList", "const IntRect& GetImageRect() const", AS_METHODPR(DropDownList, GetImageRect, () const, const IntRect&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "const IntRect& get_imageRect() const", AS_METHODPR(DropDownList, GetImageRect, () const, const IntRect&), AS_CALL_THISCALL);
    // int UIElement::GetIndent() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "int GetIndent() const", AS_METHODPR(DropDownList, GetIndent, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "int get_indent() const", AS_METHODPR(DropDownList, GetIndent, () const, int), AS_CALL_THISCALL);
    // int UIElement::GetIndentSpacing() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "int GetIndentSpacing() const", AS_METHODPR(DropDownList, GetIndentSpacing, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "int get_indentSpacing() const", AS_METHODPR(DropDownList, GetIndentSpacing, () const, int), AS_CALL_THISCALL);
    // int UIElement::GetIndentWidth() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "int GetIndentWidth() const", AS_METHODPR(DropDownList, GetIndentWidth, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "int get_indentWidth() const", AS_METHODPR(DropDownList, GetIndentWidth, () const, int), AS_CALL_THISCALL);
    // bool Serializable::GetInterceptNetworkUpdate(const String& attributeName) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("DropDownList", "bool GetInterceptNetworkUpdate(const String&in) const", AS_METHODPR(DropDownList, GetInterceptNetworkUpdate, (const String&) const, bool), AS_CALL_THISCALL);
    // UIElement* DropDownList::GetItem(unsigned index) const | File: ../UI/DropDownList.h
    engine->RegisterObjectMethod("DropDownList", "UIElement@+ GetItem(uint) const", AS_METHODPR(DropDownList, GetItem, (unsigned) const, UIElement*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "UIElement@+ get_items(uint) const", AS_METHODPR(DropDownList, GetItem, (unsigned) const, UIElement*), AS_CALL_THISCALL);
    // PODVector<UIElement*> DropDownList::GetItems() const | File: ../UI/DropDownList.h
    engine->RegisterObjectMethod("DropDownList", "Array<UIElement@>@ GetItems() const", AS_FUNCTION_OBJFIRST(DropDownList_GetItems_void), AS_CALL_CDECL_OBJFIRST);
    // const IntRect& UIElement::GetLayoutBorder() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "const IntRect& GetLayoutBorder() const", AS_METHODPR(DropDownList, GetLayoutBorder, () const, const IntRect&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "const IntRect& get_layoutBorder() const", AS_METHODPR(DropDownList, GetLayoutBorder, () const, const IntRect&), AS_CALL_THISCALL);
    // int UIElement::GetLayoutElementMaxSize() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "int GetLayoutElementMaxSize() const", AS_METHODPR(DropDownList, GetLayoutElementMaxSize, () const, int), AS_CALL_THISCALL);
    // const Vector2& UIElement::GetLayoutFlexScale() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "const Vector2& GetLayoutFlexScale() const", AS_METHODPR(DropDownList, GetLayoutFlexScale, () const, const Vector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "const Vector2& get_layoutFlexScale() const", AS_METHODPR(DropDownList, GetLayoutFlexScale, () const, const Vector2&), AS_CALL_THISCALL);
    // LayoutMode UIElement::GetLayoutMode() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "LayoutMode GetLayoutMode() const", AS_METHODPR(DropDownList, GetLayoutMode, () const, LayoutMode), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "LayoutMode get_layoutMode() const", AS_METHODPR(DropDownList, GetLayoutMode, () const, LayoutMode), AS_CALL_THISCALL);
    // int UIElement::GetLayoutSpacing() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "int GetLayoutSpacing() const", AS_METHODPR(DropDownList, GetLayoutSpacing, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "int get_layoutSpacing() const", AS_METHODPR(DropDownList, GetLayoutSpacing, () const, int), AS_CALL_THISCALL);
    // ListView* DropDownList::GetListView() const | File: ../UI/DropDownList.h
    engine->RegisterObjectMethod("DropDownList", "ListView@+ GetListView() const", AS_METHODPR(DropDownList, GetListView, () const, ListView*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "ListView@+ get_listView() const", AS_METHODPR(DropDownList, GetListView, () const, ListView*), AS_CALL_THISCALL);
    // Material* BorderImage::GetMaterial() const | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("DropDownList", "Material@+ GetMaterial() const", AS_METHODPR(DropDownList, GetMaterial, () const, Material*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "Material@+ get_material() const", AS_METHODPR(DropDownList, GetMaterial, () const, Material*), AS_CALL_THISCALL);
    // ResourceRef BorderImage::GetMaterialAttr() const | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("DropDownList", "ResourceRef GetMaterialAttr() const", AS_METHODPR(DropDownList, GetMaterialAttr, () const, ResourceRef), AS_CALL_THISCALL);
    // const Vector2& UIElement::GetMaxAnchor() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "const Vector2& GetMaxAnchor() const", AS_METHODPR(DropDownList, GetMaxAnchor, () const, const Vector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "const Vector2& get_maxAnchor() const", AS_METHODPR(DropDownList, GetMaxAnchor, () const, const Vector2&), AS_CALL_THISCALL);
    // int UIElement::GetMaxHeight() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "int GetMaxHeight() const", AS_METHODPR(DropDownList, GetMaxHeight, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "int get_maxHeight() const", AS_METHODPR(DropDownList, GetMaxHeight, () const, int), AS_CALL_THISCALL);
    // const IntVector2& UIElement::GetMaxOffset() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "const IntVector2& GetMaxOffset() const", AS_METHODPR(DropDownList, GetMaxOffset, () const, const IntVector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "const IntVector2& get_maxOffset() const", AS_METHODPR(DropDownList, GetMaxOffset, () const, const IntVector2&), AS_CALL_THISCALL);
    // const IntVector2& UIElement::GetMaxSize() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "const IntVector2& GetMaxSize() const", AS_METHODPR(DropDownList, GetMaxSize, () const, const IntVector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "const IntVector2& get_maxSize() const", AS_METHODPR(DropDownList, GetMaxSize, () const, const IntVector2&), AS_CALL_THISCALL);
    // int UIElement::GetMaxWidth() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "int GetMaxWidth() const", AS_METHODPR(DropDownList, GetMaxWidth, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "int get_maxWidth() const", AS_METHODPR(DropDownList, GetMaxWidth, () const, int), AS_CALL_THISCALL);
    // const Vector2& UIElement::GetMinAnchor() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "const Vector2& GetMinAnchor() const", AS_METHODPR(DropDownList, GetMinAnchor, () const, const Vector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "const Vector2& get_minAnchor() const", AS_METHODPR(DropDownList, GetMinAnchor, () const, const Vector2&), AS_CALL_THISCALL);
    // int UIElement::GetMinHeight() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "int GetMinHeight() const", AS_METHODPR(DropDownList, GetMinHeight, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "int get_minHeight() const", AS_METHODPR(DropDownList, GetMinHeight, () const, int), AS_CALL_THISCALL);
    // const IntVector2& UIElement::GetMinOffset() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "const IntVector2& GetMinOffset() const", AS_METHODPR(DropDownList, GetMinOffset, () const, const IntVector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "const IntVector2& get_minOffset() const", AS_METHODPR(DropDownList, GetMinOffset, () const, const IntVector2&), AS_CALL_THISCALL);
    // const IntVector2& UIElement::GetMinSize() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "const IntVector2& GetMinSize() const", AS_METHODPR(DropDownList, GetMinSize, () const, const IntVector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "const IntVector2& get_minSize() const", AS_METHODPR(DropDownList, GetMinSize, () const, const IntVector2&), AS_CALL_THISCALL);
    // int UIElement::GetMinWidth() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "int GetMinWidth() const", AS_METHODPR(DropDownList, GetMinWidth, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "int get_minWidth() const", AS_METHODPR(DropDownList, GetMinWidth, () const, int), AS_CALL_THISCALL);
    // const String& UIElement::GetName() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "const String& GetName() const", AS_METHODPR(DropDownList, GetName, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "const String& get_name() const", AS_METHODPR(DropDownList, GetName, () const, const String&), AS_CALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetNetworkAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // NetworkState* Serializable::GetNetworkState() const | File: ../Scene/Serializable.h
    // Error: type "NetworkState*" can not automatically bind
    // unsigned Serializable::GetNumAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("DropDownList", "uint GetNumAttributes() const", AS_METHODPR(DropDownList, GetNumAttributes, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "uint get_numAttributes() const", AS_METHODPR(DropDownList, GetNumAttributes, () const, unsigned), AS_CALL_THISCALL);
    // unsigned UIElement::GetNumChildren(bool recursive=false) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "uint GetNumChildren(bool = false) const", AS_METHODPR(DropDownList, GetNumChildren, (bool) const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "uint get_numChildren(bool = false) const", AS_METHODPR(DropDownList, GetNumChildren, (bool) const, unsigned), AS_CALL_THISCALL);
    // unsigned DropDownList::GetNumItems() const | File: ../UI/DropDownList.h
    engine->RegisterObjectMethod("DropDownList", "uint GetNumItems() const", AS_METHODPR(DropDownList, GetNumItems, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "uint get_numItems() const", AS_METHODPR(DropDownList, GetNumItems, () const, unsigned), AS_CALL_THISCALL);
    // unsigned Serializable::GetNumNetworkAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("DropDownList", "uint GetNumNetworkAttributes() const", AS_METHODPR(DropDownList, GetNumNetworkAttributes, () const, unsigned), AS_CALL_THISCALL);
    // ObjectAnimation* Animatable::GetObjectAnimation() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("DropDownList", "ObjectAnimation@+ GetObjectAnimation() const", AS_METHODPR(DropDownList, GetObjectAnimation, () const, ObjectAnimation*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "ObjectAnimation@+ get_objectAnimation() const", AS_METHODPR(DropDownList, GetObjectAnimation, () const, ObjectAnimation*), AS_CALL_THISCALL);
    // ResourceRef Animatable::GetObjectAnimationAttr() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("DropDownList", "ResourceRef GetObjectAnimationAttr() const", AS_METHODPR(DropDownList, GetObjectAnimationAttr, () const, ResourceRef), AS_CALL_THISCALL);
    // float UIElement::GetOpacity() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "float GetOpacity() const", AS_METHODPR(DropDownList, GetOpacity, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "float get_opacity() const", AS_METHODPR(DropDownList, GetOpacity, () const, float), AS_CALL_THISCALL);
    // UIElement* UIElement::GetParent() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "UIElement@+ GetParent() const", AS_METHODPR(DropDownList, GetParent, () const, UIElement*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "UIElement@+ get_parent() const", AS_METHODPR(DropDownList, GetParent, () const, UIElement*), AS_CALL_THISCALL);
    // const Vector2& UIElement::GetPivot() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "const Vector2& GetPivot() const", AS_METHODPR(DropDownList, GetPivot, () const, const Vector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "const Vector2& get_pivot() const", AS_METHODPR(DropDownList, GetPivot, () const, const Vector2&), AS_CALL_THISCALL);
    // UIElement* DropDownList::GetPlaceholder() const | File: ../UI/DropDownList.h
    engine->RegisterObjectMethod("DropDownList", "UIElement@+ GetPlaceholder() const", AS_METHODPR(DropDownList, GetPlaceholder, () const, UIElement*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "UIElement@+ get_placeholder() const", AS_METHODPR(DropDownList, GetPlaceholder, () const, UIElement*), AS_CALL_THISCALL);
    // const String& DropDownList::GetPlaceholderText() const | File: ../UI/DropDownList.h
    engine->RegisterObjectMethod("DropDownList", "const String& GetPlaceholderText() const", AS_METHODPR(DropDownList, GetPlaceholderText, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "const String& get_placeholderText() const", AS_METHODPR(DropDownList, GetPlaceholderText, () const, const String&), AS_CALL_THISCALL);
    // UIElement* Menu::GetPopup() const | File: ../UI/Menu.h
    engine->RegisterObjectMethod("DropDownList", "UIElement@+ GetPopup() const", AS_METHODPR(DropDownList, GetPopup, () const, UIElement*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "UIElement@+ get_popup() const", AS_METHODPR(DropDownList, GetPopup, () const, UIElement*), AS_CALL_THISCALL);
    // const IntVector2& Menu::GetPopupOffset() const | File: ../UI/Menu.h
    engine->RegisterObjectMethod("DropDownList", "const IntVector2& GetPopupOffset() const", AS_METHODPR(DropDownList, GetPopupOffset, () const, const IntVector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "const IntVector2& get_popupOffset() const", AS_METHODPR(DropDownList, GetPopupOffset, () const, const IntVector2&), AS_CALL_THISCALL);
    // const IntVector2& UIElement::GetPosition() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "const IntVector2& GetPosition() const", AS_METHODPR(DropDownList, GetPosition, () const, const IntVector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "const IntVector2& get_position() const", AS_METHODPR(DropDownList, GetPosition, () const, const IntVector2&), AS_CALL_THISCALL);
    // const IntVector2& Button::GetPressedChildOffset() const | File: ../UI/Button.h
    engine->RegisterObjectMethod("DropDownList", "const IntVector2& GetPressedChildOffset() const", AS_METHODPR(DropDownList, GetPressedChildOffset, () const, const IntVector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "const IntVector2& get_pressedChildOffset() const", AS_METHODPR(DropDownList, GetPressedChildOffset, () const, const IntVector2&), AS_CALL_THISCALL);
    // const IntVector2& Button::GetPressedOffset() const | File: ../UI/Button.h
    engine->RegisterObjectMethod("DropDownList", "const IntVector2& GetPressedOffset() const", AS_METHODPR(DropDownList, GetPressedOffset, () const, const IntVector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "const IntVector2& get_pressedOffset() const", AS_METHODPR(DropDownList, GetPressedOffset, () const, const IntVector2&), AS_CALL_THISCALL);
    // int UIElement::GetPriority() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "int GetPriority() const", AS_METHODPR(DropDownList, GetPriority, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "int get_priority() const", AS_METHODPR(DropDownList, GetPriority, () const, int), AS_CALL_THISCALL);
    // float Button::GetRepeatDelay() const | File: ../UI/Button.h
    engine->RegisterObjectMethod("DropDownList", "float GetRepeatDelay() const", AS_METHODPR(DropDownList, GetRepeatDelay, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "float get_repeatDelay() const", AS_METHODPR(DropDownList, GetRepeatDelay, () const, float), AS_CALL_THISCALL);
    // float Button::GetRepeatRate() const | File: ../UI/Button.h
    engine->RegisterObjectMethod("DropDownList", "float GetRepeatRate() const", AS_METHODPR(DropDownList, GetRepeatRate, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "float get_repeatRate() const", AS_METHODPR(DropDownList, GetRepeatRate, () const, float), AS_CALL_THISCALL);
    // bool DropDownList::GetResizePopup() const | File: ../UI/DropDownList.h
    engine->RegisterObjectMethod("DropDownList", "bool GetResizePopup() const", AS_METHODPR(DropDownList, GetResizePopup, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "bool get_resizePopup() const", AS_METHODPR(DropDownList, GetResizePopup, () const, bool), AS_CALL_THISCALL);
    // UIElement* UIElement::GetRoot() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "UIElement@+ GetRoot() const", AS_METHODPR(DropDownList, GetRoot, () const, UIElement*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "UIElement@+ get_root() const", AS_METHODPR(DropDownList, GetRoot, () const, UIElement*), AS_CALL_THISCALL);
    // virtual const IntVector2& UIElement::GetScreenPosition() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "const IntVector2& GetScreenPosition() const", AS_METHODPR(DropDownList, GetScreenPosition, () const, const IntVector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "const IntVector2& get_screenPosition() const", AS_METHODPR(DropDownList, GetScreenPosition, () const, const IntVector2&), AS_CALL_THISCALL);
    // UIElement* DropDownList::GetSelectedItem() const | File: ../UI/DropDownList.h
    engine->RegisterObjectMethod("DropDownList", "UIElement@+ GetSelectedItem() const", AS_METHODPR(DropDownList, GetSelectedItem, () const, UIElement*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "UIElement@+ get_selectedItem() const", AS_METHODPR(DropDownList, GetSelectedItem, () const, UIElement*), AS_CALL_THISCALL);
    // unsigned DropDownList::GetSelection() const | File: ../UI/DropDownList.h
    engine->RegisterObjectMethod("DropDownList", "uint GetSelection() const", AS_METHODPR(DropDownList, GetSelection, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "uint get_selection() const", AS_METHODPR(DropDownList, GetSelection, () const, unsigned), AS_CALL_THISCALL);
    // bool Menu::GetShowPopup() const | File: ../UI/Menu.h
    engine->RegisterObjectMethod("DropDownList", "bool GetShowPopup() const", AS_METHODPR(DropDownList, GetShowPopup, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "bool get_showPopup() const", AS_METHODPR(DropDownList, GetShowPopup, () const, bool), AS_CALL_THISCALL);
    // const IntVector2& UIElement::GetSize() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "const IntVector2& GetSize() const", AS_METHODPR(DropDownList, GetSize, () const, const IntVector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "const IntVector2& get_size() const", AS_METHODPR(DropDownList, GetSize, () const, const IntVector2&), AS_CALL_THISCALL);
    // bool UIElement::GetSortChildren() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "bool GetSortChildren() const", AS_METHODPR(DropDownList, GetSortChildren, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "bool get_sortChildren() const", AS_METHODPR(DropDownList, GetSortChildren, () const, bool), AS_CALL_THISCALL);
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("DropDownList", "Object@+ GetSubsystem(StringHash) const", AS_METHODPR(DropDownList, GetSubsystem, (StringHash) const, Object*), AS_CALL_THISCALL);
    // template<class T> T* Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // const StringVector& UIElement::GetTags() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "Array<String>@ GetTags() const", AS_FUNCTION_OBJFIRST(DropDownList_GetTags_void), AS_CALL_CDECL_OBJFIRST);
    engine->RegisterObjectMethod("DropDownList", "Array<String>@ get_tags() const", AS_FUNCTION_OBJFIRST(DropDownList_GetTags_void), AS_CALL_CDECL_OBJFIRST);
    // Texture* BorderImage::GetTexture() const | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("DropDownList", "Texture@+ GetTexture() const", AS_METHODPR(DropDownList, GetTexture, () const, Texture*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "Texture@+ get_texture() const", AS_METHODPR(DropDownList, GetTexture, () const, Texture*), AS_CALL_THISCALL);
    // ResourceRef BorderImage::GetTextureAttr() const | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("DropDownList", "ResourceRef GetTextureAttr() const", AS_METHODPR(DropDownList, GetTextureAttr, () const, ResourceRef), AS_CALL_THISCALL);
    // TraversalMode UIElement::GetTraversalMode() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "TraversalMode GetTraversalMode() const", AS_METHODPR(DropDownList, GetTraversalMode, () const, TraversalMode), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "TraversalMode get_traversalMode() const", AS_METHODPR(DropDownList, GetTraversalMode, () const, TraversalMode), AS_CALL_THISCALL);
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("DropDownList", "StringHash GetType() const", AS_METHODPR(DropDownList, GetType, () const, StringHash), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "StringHash get_type() const", AS_METHODPR(DropDownList, GetType, () const, StringHash), AS_CALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("DropDownList", "const String& GetTypeName() const", AS_METHODPR(DropDownList, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "const String& get_typeName() const", AS_METHODPR(DropDownList, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    // bool UIElement::GetUseDerivedOpacity() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "bool GetUseDerivedOpacity() const", AS_METHODPR(DropDownList, GetUseDerivedOpacity, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "bool get_useDerivedOpacity() const", AS_METHODPR(DropDownList, GetUseDerivedOpacity, () const, bool), AS_CALL_THISCALL);
    // const Variant& UIElement::GetVar(const StringHash& key) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "const Variant& GetVar(const StringHash&in) const", AS_METHODPR(DropDownList, GetVar, (const StringHash&) const, const Variant&), AS_CALL_THISCALL);
    // const VariantMap& UIElement::GetVars() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "const VariantMap& GetVars() const", AS_METHODPR(DropDownList, GetVars, () const, const VariantMap&), AS_CALL_THISCALL);
    // VerticalAlignment UIElement::GetVerticalAlignment() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "VerticalAlignment GetVerticalAlignment() const", AS_METHODPR(DropDownList, GetVerticalAlignment, () const, VerticalAlignment), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "VerticalAlignment get_verticalAlignment() const", AS_METHODPR(DropDownList, GetVerticalAlignment, () const, VerticalAlignment), AS_CALL_THISCALL);
    // int UIElement::GetWidth() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "int GetWidth() const", AS_METHODPR(DropDownList, GetWidth, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "int get_width() const", AS_METHODPR(DropDownList, GetWidth, () const, int), AS_CALL_THISCALL);
    // bool UIElement::HasColorGradient() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "bool HasColorGradient() const", AS_METHODPR(DropDownList, HasColorGradient, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "bool get_colorGradient() const", AS_METHODPR(DropDownList, HasColorGradient, () const, bool), AS_CALL_THISCALL);
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("DropDownList", "bool HasEventHandlers() const", AS_METHODPR(DropDownList, HasEventHandlers, () const, bool), AS_CALL_THISCALL);
    // bool UIElement::HasFocus() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "bool HasFocus() const", AS_METHODPR(DropDownList, HasFocus, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "bool get_focus() const", AS_METHODPR(DropDownList, HasFocus, () const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("DropDownList", "bool HasSubscribedToEvent(StringHash) const", AS_METHODPR(DropDownList, HasSubscribedToEvent, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("DropDownList", "bool HasSubscribedToEvent(Object@+, StringHash) const", AS_METHODPR(DropDownList, HasSubscribedToEvent, (Object*, StringHash) const, bool), AS_CALL_THISCALL);
    // bool UIElement::HasTag(const String& tag) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "bool HasTag(const String&in) const", AS_METHODPR(DropDownList, HasTag, (const String&) const, bool), AS_CALL_THISCALL);
    // void UIElement::InsertChild(unsigned index, UIElement* element) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "void InsertChild(uint, UIElement@+)", AS_METHODPR(DropDownList, InsertChild, (unsigned, UIElement*), void), AS_CALL_THISCALL);
    // void DropDownList::InsertItem(unsigned index, UIElement* item) | File: ../UI/DropDownList.h
    engine->RegisterObjectMethod("DropDownList", "void InsertItem(uint, UIElement@+)", AS_METHODPR(DropDownList, InsertItem, (unsigned, UIElement*), void), AS_CALL_THISCALL);
    // bool UIElement::IsChildOf(UIElement* element) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "bool IsChildOf(UIElement@+) const", AS_METHODPR(DropDownList, IsChildOf, (UIElement*) const, bool), AS_CALL_THISCALL);
    // bool UIElement::IsEditable() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "bool IsEditable() const", AS_METHODPR(DropDownList, IsEditable, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "bool get_editable() const", AS_METHODPR(DropDownList, IsEditable, () const, bool), AS_CALL_THISCALL);
    // bool UIElement::IsElementEventSender() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "bool IsElementEventSender() const", AS_METHODPR(DropDownList, IsElementEventSender, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "bool get_elementEventSender() const", AS_METHODPR(DropDownList, IsElementEventSender, () const, bool), AS_CALL_THISCALL);
    // bool UIElement::IsEnabled() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "bool IsEnabled() const", AS_METHODPR(DropDownList, IsEnabled, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "bool get_enabled() const", AS_METHODPR(DropDownList, IsEnabled, () const, bool), AS_CALL_THISCALL);
    // bool UIElement::IsEnabledSelf() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "bool IsEnabledSelf() const", AS_METHODPR(DropDownList, IsEnabledSelf, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "bool get_enabledSelf() const", AS_METHODPR(DropDownList, IsEnabledSelf, () const, bool), AS_CALL_THISCALL);
    // bool UIElement::IsFixedHeight() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "bool IsFixedHeight() const", AS_METHODPR(DropDownList, IsFixedHeight, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "bool get_fixedHeight() const", AS_METHODPR(DropDownList, IsFixedHeight, () const, bool), AS_CALL_THISCALL);
    // bool UIElement::IsFixedSize() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "bool IsFixedSize() const", AS_METHODPR(DropDownList, IsFixedSize, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "bool get_fixedSize() const", AS_METHODPR(DropDownList, IsFixedSize, () const, bool), AS_CALL_THISCALL);
    // bool UIElement::IsFixedWidth() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "bool IsFixedWidth() const", AS_METHODPR(DropDownList, IsFixedWidth, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "bool get_fixedWidth() const", AS_METHODPR(DropDownList, IsFixedWidth, () const, bool), AS_CALL_THISCALL);
    // bool UIElement::IsHovering() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "bool IsHovering() const", AS_METHODPR(DropDownList, IsHovering, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "bool get_hovering() const", AS_METHODPR(DropDownList, IsHovering, () const, bool), AS_CALL_THISCALL);
    // bool UIElement::IsInside(IntVector2 position, bool isScreen) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "bool IsInside(IntVector2, bool)", AS_METHODPR(DropDownList, IsInside, (IntVector2, bool), bool), AS_CALL_THISCALL);
    // bool UIElement::IsInsideCombined(IntVector2 position, bool isScreen) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "bool IsInsideCombined(IntVector2, bool)", AS_METHODPR(DropDownList, IsInsideCombined, (IntVector2, bool), bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("DropDownList", "bool IsInstanceOf(StringHash) const", AS_METHODPR(DropDownList, IsInstanceOf, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // bool UIElement::IsInternal() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "bool IsInternal() const", AS_METHODPR(DropDownList, IsInternal, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "bool get_internal() const", AS_METHODPR(DropDownList, IsInternal, () const, bool), AS_CALL_THISCALL);
    // bool Button::IsPressed() const | File: ../UI/Button.h
    engine->RegisterObjectMethod("DropDownList", "bool IsPressed() const", AS_METHODPR(DropDownList, IsPressed, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "bool get_pressed() const", AS_METHODPR(DropDownList, IsPressed, () const, bool), AS_CALL_THISCALL);
    // bool UIElement::IsSelected() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "bool IsSelected() const", AS_METHODPR(DropDownList, IsSelected, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "bool get_selected() const", AS_METHODPR(DropDownList, IsSelected, () const, bool), AS_CALL_THISCALL);
    // bool Serializable::IsTemporary() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("DropDownList", "bool IsTemporary() const", AS_METHODPR(DropDownList, IsTemporary, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "bool get_temporary() const", AS_METHODPR(DropDownList, IsTemporary, () const, bool), AS_CALL_THISCALL);
    // bool BorderImage::IsTiled() const | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("DropDownList", "bool IsTiled() const", AS_METHODPR(DropDownList, IsTiled, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "bool get_tiled() const", AS_METHODPR(DropDownList, IsTiled, () const, bool), AS_CALL_THISCALL);
    // bool UIElement::IsVisible() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "bool IsVisible() const", AS_METHODPR(DropDownList, IsVisible, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "bool get_visible() const", AS_METHODPR(DropDownList, IsVisible, () const, bool), AS_CALL_THISCALL);
    // bool UIElement::IsVisibleEffective() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "bool IsVisibleEffective() const", AS_METHODPR(DropDownList, IsVisibleEffective, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "bool get_visibleEffective() const", AS_METHODPR(DropDownList, IsVisibleEffective, () const, bool), AS_CALL_THISCALL);
    // virtual bool UIElement::IsWheelHandler() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "bool IsWheelHandler() const", AS_METHODPR(DropDownList, IsWheelHandler, () const, bool), AS_CALL_THISCALL);
    // virtual bool UIElement::IsWithinScissor(const IntRect& currentScissor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "bool IsWithinScissor(const IntRect&in)", AS_METHODPR(DropDownList, IsWithinScissor, (const IntRect&), bool), AS_CALL_THISCALL);
    // virtual bool Serializable::Load(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("DropDownList", "bool Load(Deserializer&)", AS_METHODPR(DropDownList, Load, (Deserializer&), bool), AS_CALL_THISCALL);
    // virtual UIElement* UIElement::LoadChildXML(const XMLElement& childElem, XMLFile* styleFile) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "UIElement@+ LoadChildXML(const XMLElement&in, XMLFile@+)", AS_METHODPR(DropDownList, LoadChildXML, (const XMLElement&, XMLFile*), UIElement*), AS_CALL_THISCALL);
    // bool Animatable::LoadJSON(const JSONValue& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("DropDownList", "bool LoadJSON(const JSONValue&in)", AS_METHODPR(DropDownList, LoadJSON, (const JSONValue&), bool), AS_CALL_THISCALL);
    // bool Menu::LoadXML(const XMLElement& source, XMLFile* styleFile) override | File: ../UI/Menu.h
    engine->RegisterObjectMethod("DropDownList", "bool LoadXML(const XMLElement&in, XMLFile@+)", AS_METHODPR(DropDownList, LoadXML, (const XMLElement&, XMLFile*), bool), AS_CALL_THISCALL);
    // virtual void Serializable::MarkNetworkUpdate() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("DropDownList", "void MarkNetworkUpdate()", AS_METHODPR(DropDownList, MarkNetworkUpdate, (), void), AS_CALL_THISCALL);
    // void Button::OnClickBegin(const IntVector2& position, const IntVector2& screenPosition, MouseButton button, MouseButtonFlags buttons, QualifierFlags qualifiers, Cursor* cursor) override | File: ../UI/Button.h
    engine->RegisterObjectMethod("DropDownList", "void OnClickBegin(const IntVector2&in, const IntVector2&in, MouseButton, MouseButtonFlags, QualifierFlags, Cursor@+)", AS_METHODPR(DropDownList, OnClickBegin, (const IntVector2&, const IntVector2&, MouseButton, MouseButtonFlags, QualifierFlags, Cursor*), void), AS_CALL_THISCALL);
    // void Button::OnClickEnd(const IntVector2& position, const IntVector2& screenPosition, MouseButton button, MouseButtonFlags buttons, QualifierFlags qualifiers, Cursor* cursor, UIElement* beginElement) override | File: ../UI/Button.h
    engine->RegisterObjectMethod("DropDownList", "void OnClickEnd(const IntVector2&in, const IntVector2&in, MouseButton, MouseButtonFlags, QualifierFlags, Cursor@+, UIElement@+)", AS_METHODPR(DropDownList, OnClickEnd, (const IntVector2&, const IntVector2&, MouseButton, MouseButtonFlags, QualifierFlags, Cursor*, UIElement*), void), AS_CALL_THISCALL);
    // virtual void UIElement::OnDoubleClick(const IntVector2& position, const IntVector2& screenPosition, MouseButton button, MouseButtonFlags buttons, QualifierFlags qualifiers, Cursor* cursor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "void OnDoubleClick(const IntVector2&in, const IntVector2&in, MouseButton, MouseButtonFlags, QualifierFlags, Cursor@+)", AS_METHODPR(DropDownList, OnDoubleClick, (const IntVector2&, const IntVector2&, MouseButton, MouseButtonFlags, QualifierFlags, Cursor*), void), AS_CALL_THISCALL);
    // virtual void UIElement::OnDragBegin(const IntVector2& position, const IntVector2& screenPosition, MouseButtonFlags buttons, QualifierFlags qualifiers, Cursor* cursor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "void OnDragBegin(const IntVector2&in, const IntVector2&in, MouseButtonFlags, QualifierFlags, Cursor@+)", AS_METHODPR(DropDownList, OnDragBegin, (const IntVector2&, const IntVector2&, MouseButtonFlags, QualifierFlags, Cursor*), void), AS_CALL_THISCALL);
    // virtual void UIElement::OnDragCancel(const IntVector2& position, const IntVector2& screenPosition, MouseButtonFlags dragButtons, MouseButtonFlags cancelButtons, Cursor* cursor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "void OnDragCancel(const IntVector2&in, const IntVector2&in, MouseButtonFlags, MouseButtonFlags, Cursor@+)", AS_METHODPR(DropDownList, OnDragCancel, (const IntVector2&, const IntVector2&, MouseButtonFlags, MouseButtonFlags, Cursor*), void), AS_CALL_THISCALL);
    // virtual bool UIElement::OnDragDropFinish(UIElement* source) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "bool OnDragDropFinish(UIElement@+)", AS_METHODPR(DropDownList, OnDragDropFinish, (UIElement*), bool), AS_CALL_THISCALL);
    // virtual bool UIElement::OnDragDropTest(UIElement* source) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "bool OnDragDropTest(UIElement@+)", AS_METHODPR(DropDownList, OnDragDropTest, (UIElement*), bool), AS_CALL_THISCALL);
    // virtual void UIElement::OnDragEnd(const IntVector2& position, const IntVector2& screenPosition, MouseButtonFlags dragButtons, MouseButtonFlags releaseButtons, Cursor* cursor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "void OnDragEnd(const IntVector2&in, const IntVector2&in, MouseButtonFlags, MouseButtonFlags, Cursor@+)", AS_METHODPR(DropDownList, OnDragEnd, (const IntVector2&, const IntVector2&, MouseButtonFlags, MouseButtonFlags, Cursor*), void), AS_CALL_THISCALL);
    // void Button::OnDragMove(const IntVector2& position, const IntVector2& screenPosition, const IntVector2& deltaPos, MouseButtonFlags buttons, QualifierFlags qualifiers, Cursor* cursor) override | File: ../UI/Button.h
    engine->RegisterObjectMethod("DropDownList", "void OnDragMove(const IntVector2&in, const IntVector2&in, const IntVector2&in, MouseButtonFlags, QualifierFlags, Cursor@+)", AS_METHODPR(DropDownList, OnDragMove, (const IntVector2&, const IntVector2&, const IntVector2&, MouseButtonFlags, QualifierFlags, Cursor*), void), AS_CALL_THISCALL);
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("DropDownList", "void OnEvent(Object@+, StringHash, VariantMap&)", AS_METHODPR(DropDownList, OnEvent, (Object*, StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // virtual void Serializable::OnGetAttribute(const AttributeInfo& attr, Variant& dest) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("DropDownList", "void OnGetAttribute(const AttributeInfo&in, Variant&) const", AS_METHODPR(DropDownList, OnGetAttribute, (const AttributeInfo&, Variant&) const, void), AS_CALL_THISCALL);
    // void DropDownList::OnHidePopup() override | File: ../UI/DropDownList.h
    engine->RegisterObjectMethod("DropDownList", "void OnHidePopup()", AS_METHODPR(DropDownList, OnHidePopup, (), void), AS_CALL_THISCALL);
    // void Menu::OnHover(const IntVector2& position, const IntVector2& screenPosition, MouseButtonFlags buttons, QualifierFlags qualifiers, Cursor* cursor) override | File: ../UI/Menu.h
    engine->RegisterObjectMethod("DropDownList", "void OnHover(const IntVector2&in, const IntVector2&in, MouseButtonFlags, QualifierFlags, Cursor@+)", AS_METHODPR(DropDownList, OnHover, (const IntVector2&, const IntVector2&, MouseButtonFlags, QualifierFlags, Cursor*), void), AS_CALL_THISCALL);
    // virtual void UIElement::OnIndentSet() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "void OnIndentSet()", AS_METHODPR(DropDownList, OnIndentSet, (), void), AS_CALL_THISCALL);
    // void Button::OnKey(Key key, MouseButtonFlags buttons, QualifierFlags qualifiers) override | File: ../UI/Button.h
    engine->RegisterObjectMethod("DropDownList", "void OnKey(Key, MouseButtonFlags, QualifierFlags)", AS_METHODPR(DropDownList, OnKey, (Key, MouseButtonFlags, QualifierFlags), void), AS_CALL_THISCALL);
    // virtual void UIElement::OnPositionSet(const IntVector2& newPosition) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "void OnPositionSet(const IntVector2&in)", AS_METHODPR(DropDownList, OnPositionSet, (const IntVector2&), void), AS_CALL_THISCALL);
    // virtual void UIElement::OnResize(const IntVector2& newSize, const IntVector2& delta) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "void OnResize(const IntVector2&in, const IntVector2&in)", AS_METHODPR(DropDownList, OnResize, (const IntVector2&, const IntVector2&), void), AS_CALL_THISCALL);
    // virtual void Serializable::OnSetAttribute(const AttributeInfo& attr, const Variant& src) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("DropDownList", "void OnSetAttribute(const AttributeInfo&in, const Variant&in)", AS_METHODPR(DropDownList, OnSetAttribute, (const AttributeInfo&, const Variant&), void), AS_CALL_THISCALL);
    // void DropDownList::OnSetEditable() override | File: ../UI/DropDownList.h
    engine->RegisterObjectMethod("DropDownList", "void OnSetEditable()", AS_METHODPR(DropDownList, OnSetEditable, (), void), AS_CALL_THISCALL);
    // void DropDownList::OnShowPopup() override | File: ../UI/DropDownList.h
    engine->RegisterObjectMethod("DropDownList", "void OnShowPopup()", AS_METHODPR(DropDownList, OnShowPopup, (), void), AS_CALL_THISCALL);
    // virtual void UIElement::OnTextInput(const String& text) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "void OnTextInput(const String&in)", AS_METHODPR(DropDownList, OnTextInput, (const String&), void), AS_CALL_THISCALL);
    // virtual void UIElement::OnWheel(int delta, MouseButtonFlags buttons, QualifierFlags qualifiers) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "void OnWheel(int, MouseButtonFlags, QualifierFlags)", AS_METHODPR(DropDownList, OnWheel, (int, MouseButtonFlags, QualifierFlags), void), AS_CALL_THISCALL);
    // bool Serializable::ReadDeltaUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("DropDownList", "bool ReadDeltaUpdate(Deserializer&)", AS_METHODPR(DropDownList, ReadDeltaUpdate, (Deserializer&), bool), AS_CALL_THISCALL);
    // bool Serializable::ReadLatestDataUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("DropDownList", "bool ReadLatestDataUpdate(Deserializer&)", AS_METHODPR(DropDownList, ReadLatestDataUpdate, (Deserializer&), bool), AS_CALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("DropDownList", "int Refs() const", AS_METHODPR(DropDownList, Refs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "int get_refs() const", AS_METHODPR(DropDownList, Refs, () const, int), AS_CALL_THISCALL);
    // static void DropDownList::RegisterObject(Context* context) | File: ../UI/DropDownList.h
    // Not registered because have @nobind mark
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("DropDownList", asBEHAVE_RELEASE, "void f()", AS_METHODPR(DropDownList, ReleaseRef, (), void), AS_CALL_THISCALL);
    // void UIElement::Remove() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "void Remove()", AS_METHODPR(DropDownList, Remove, (), void), AS_CALL_THISCALL);
    // void UIElement::RemoveAllChildren() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "void RemoveAllChildren()", AS_METHODPR(DropDownList, RemoveAllChildren, (), void), AS_CALL_THISCALL);
    // void DropDownList::RemoveAllItems() | File: ../UI/DropDownList.h
    engine->RegisterObjectMethod("DropDownList", "void RemoveAllItems()", AS_METHODPR(DropDownList, RemoveAllItems, (), void), AS_CALL_THISCALL);
    // void UIElement::RemoveAllTags() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "void RemoveAllTags()", AS_METHODPR(DropDownList, RemoveAllTags, (), void), AS_CALL_THISCALL);
    // void Animatable::RemoveAttributeAnimation(const String& name) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("DropDownList", "void RemoveAttributeAnimation(const String&in)", AS_METHODPR(DropDownList, RemoveAttributeAnimation, (const String&), void), AS_CALL_THISCALL);
    // void UIElement::RemoveChild(UIElement* element, unsigned index=0) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "void RemoveChild(UIElement@+, uint = 0)", AS_METHODPR(DropDownList, RemoveChild, (UIElement*, unsigned), void), AS_CALL_THISCALL);
    // void UIElement::RemoveChildAtIndex(unsigned index) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "void RemoveChildAtIndex(uint)", AS_METHODPR(DropDownList, RemoveChildAtIndex, (unsigned), void), AS_CALL_THISCALL);
    // void Serializable::RemoveInstanceDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("DropDownList", "void RemoveInstanceDefault()", AS_METHODPR(DropDownList, RemoveInstanceDefault, (), void), AS_CALL_THISCALL);
    // void DropDownList::RemoveItem(UIElement* item) | File: ../UI/DropDownList.h
    engine->RegisterObjectMethod("DropDownList", "void RemoveItem(UIElement@+)", AS_METHODPR(DropDownList, RemoveItem, (UIElement*), void), AS_CALL_THISCALL);
    // void DropDownList::RemoveItem(unsigned index) | File: ../UI/DropDownList.h
    engine->RegisterObjectMethod("DropDownList", "void RemoveItem(uint)", AS_METHODPR(DropDownList, RemoveItem, (unsigned), void), AS_CALL_THISCALL);
    // void Animatable::RemoveObjectAnimation() | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("DropDownList", "void RemoveObjectAnimation()", AS_METHODPR(DropDownList, RemoveObjectAnimation, (), void), AS_CALL_THISCALL);
    // bool UIElement::RemoveTag(const String& tag) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "bool RemoveTag(const String&in)", AS_METHODPR(DropDownList, RemoveTag, (const String&), bool), AS_CALL_THISCALL);
    // void UIElement::ResetDeepEnabled() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "void ResetDeepEnabled()", AS_METHODPR(DropDownList, ResetDeepEnabled, (), void), AS_CALL_THISCALL);
    // void Serializable::ResetToDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("DropDownList", "void ResetToDefault()", AS_METHODPR(DropDownList, ResetToDefault, (), void), AS_CALL_THISCALL);
    // virtual bool Serializable::Save(Serializer& dest) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("DropDownList", "bool Save(Serializer&) const", AS_METHODPR(DropDownList, Save, (Serializer&) const, bool), AS_CALL_THISCALL);
    // virtual bool Serializable::SaveDefaultAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("DropDownList", "bool SaveDefaultAttributes() const", AS_METHODPR(DropDownList, SaveDefaultAttributes, () const, bool), AS_CALL_THISCALL);
    // bool Animatable::SaveJSON(JSONValue& dest) const override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("DropDownList", "bool SaveJSON(JSONValue&) const", AS_METHODPR(DropDownList, SaveJSON, (JSONValue&) const, bool), AS_CALL_THISCALL);
    // bool Menu::SaveXML(XMLElement& dest) const override | File: ../UI/Menu.h
    engine->RegisterObjectMethod("DropDownList", "bool SaveXML(XMLElement&) const", AS_METHODPR(DropDownList, SaveXML, (XMLElement&) const, bool), AS_CALL_THISCALL);
    // virtual IntVector2 UIElement::ScreenToElement(const IntVector2& screenPosition) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "IntVector2 ScreenToElement(const IntVector2&in)", AS_METHODPR(DropDownList, ScreenToElement, (const IntVector2&), IntVector2), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("DropDownList", "void SendEvent(StringHash)", AS_METHODPR(DropDownList, SendEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("DropDownList", "void SendEvent(StringHash, VariantMap&)", AS_METHODPR(DropDownList, SendEvent, (StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void Menu::SetAccelerator(int key, int qualifiers) | File: ../UI/Menu.h
    engine->RegisterObjectMethod("DropDownList", "void SetAccelerator(int, int)", AS_METHODPR(DropDownList, SetAccelerator, (int, int), void), AS_CALL_THISCALL);
    // void UIElement::SetAlignment(HorizontalAlignment hAlign, VerticalAlignment vAlign) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "void SetAlignment(HorizontalAlignment, VerticalAlignment)", AS_METHODPR(DropDownList, SetAlignment, (HorizontalAlignment, VerticalAlignment), void), AS_CALL_THISCALL);
    // void Animatable::SetAnimationEnabled(bool enable) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("DropDownList", "void SetAnimationEnabled(bool)", AS_METHODPR(DropDownList, SetAnimationEnabled, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "void set_animationEnabled(bool)", AS_METHODPR(DropDownList, SetAnimationEnabled, (bool), void), AS_CALL_THISCALL);
    // void Animatable::SetAnimationTime(float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("DropDownList", "void SetAnimationTime(float)", AS_METHODPR(DropDownList, SetAnimationTime, (float), void), AS_CALL_THISCALL);
    // bool Serializable::SetAttribute(unsigned index, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("DropDownList", "bool SetAttribute(uint, const Variant&in)", AS_METHODPR(DropDownList, SetAttribute, (unsigned, const Variant&), bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "bool set_attributes(uint, const Variant&in)", AS_METHODPR(DropDownList, SetAttribute, (unsigned, const Variant&), bool), AS_CALL_THISCALL);
    // bool Serializable::SetAttribute(const String& name, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("DropDownList", "bool SetAttribute(const String&in, const Variant&in)", AS_METHODPR(DropDownList, SetAttribute, (const String&, const Variant&), bool), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimation(const String& name, ValueAnimation* attributeAnimation, WrapMode wrapMode=WM_LOOP, float speed=1.0f) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("DropDownList", "void SetAttributeAnimation(const String&in, ValueAnimation@+, WrapMode = WM_LOOP, float = 1.0f)", AS_METHODPR(DropDownList, SetAttributeAnimation, (const String&, ValueAnimation*, WrapMode, float), void), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimationSpeed(const String& name, float speed) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("DropDownList", "void SetAttributeAnimationSpeed(const String&in, float)", AS_METHODPR(DropDownList, SetAttributeAnimationSpeed, (const String&, float), void), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimationTime(const String& name, float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("DropDownList", "void SetAttributeAnimationTime(const String&in, float)", AS_METHODPR(DropDownList, SetAttributeAnimationTime, (const String&, float), void), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimationWrapMode(const String& name, WrapMode wrapMode) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("DropDownList", "void SetAttributeAnimationWrapMode(const String&in, WrapMode)", AS_METHODPR(DropDownList, SetAttributeAnimationWrapMode, (const String&, WrapMode), void), AS_CALL_THISCALL);
    // void BorderImage::SetBlendMode(BlendMode mode) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("DropDownList", "void SetBlendMode(BlendMode)", AS_METHODPR(DropDownList, SetBlendMode, (BlendMode), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "void set_blendMode(BlendMode)", AS_METHODPR(DropDownList, SetBlendMode, (BlendMode), void), AS_CALL_THISCALL);
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("DropDownList", "void SetBlockEvents(bool)", AS_METHODPR(DropDownList, SetBlockEvents, (bool), void), AS_CALL_THISCALL);
    // void BorderImage::SetBorder(const IntRect& rect) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("DropDownList", "void SetBorder(const IntRect&in)", AS_METHODPR(DropDownList, SetBorder, (const IntRect&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "void set_border(const IntRect&in)", AS_METHODPR(DropDownList, SetBorder, (const IntRect&), void), AS_CALL_THISCALL);
    // void UIElement::SetBringToBack(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "void SetBringToBack(bool)", AS_METHODPR(DropDownList, SetBringToBack, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "void set_bringToBack(bool)", AS_METHODPR(DropDownList, SetBringToBack, (bool), void), AS_CALL_THISCALL);
    // void UIElement::SetBringToFront(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "void SetBringToFront(bool)", AS_METHODPR(DropDownList, SetBringToFront, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "void set_bringToFront(bool)", AS_METHODPR(DropDownList, SetBringToFront, (bool), void), AS_CALL_THISCALL);
    // void UIElement::SetChildOffset(const IntVector2& offset) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "void SetChildOffset(const IntVector2&in)", AS_METHODPR(DropDownList, SetChildOffset, (const IntVector2&), void), AS_CALL_THISCALL);
    // void UIElement::SetClipBorder(const IntRect& rect) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "void SetClipBorder(const IntRect&in)", AS_METHODPR(DropDownList, SetClipBorder, (const IntRect&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "void set_clipBorder(const IntRect&in)", AS_METHODPR(DropDownList, SetClipBorder, (const IntRect&), void), AS_CALL_THISCALL);
    // void UIElement::SetClipChildren(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "void SetClipChildren(bool)", AS_METHODPR(DropDownList, SetClipChildren, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "void set_clipChildren(bool)", AS_METHODPR(DropDownList, SetClipChildren, (bool), void), AS_CALL_THISCALL);
    // void UIElement::SetColor(const Color& color) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "void SetColor(const Color&in)", AS_METHODPR(DropDownList, SetColor, (const Color&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "void set_color(const Color&in)", AS_METHODPR(DropDownList, SetColor, (const Color&), void), AS_CALL_THISCALL);
    // void UIElement::SetColor(Corner corner, const Color& color) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "void SetColor(Corner, const Color&in)", AS_METHODPR(DropDownList, SetColor, (Corner, const Color&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "void set_colors(Corner, const Color&in)", AS_METHODPR(DropDownList, SetColor, (Corner, const Color&), void), AS_CALL_THISCALL);
    // void UIElement::SetDeepEnabled(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "void SetDeepEnabled(bool)", AS_METHODPR(DropDownList, SetDeepEnabled, (bool), void), AS_CALL_THISCALL);
    // void UIElement::SetDefaultStyle(XMLFile* style) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "void SetDefaultStyle(XMLFile@+)", AS_METHODPR(DropDownList, SetDefaultStyle, (XMLFile*), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "void set_defaultStyle(XMLFile@+)", AS_METHODPR(DropDownList, SetDefaultStyle, (XMLFile*), void), AS_CALL_THISCALL);
    // void BorderImage::SetDisabledOffset(const IntVector2& offset) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("DropDownList", "void SetDisabledOffset(const IntVector2&in)", AS_METHODPR(DropDownList, SetDisabledOffset, (const IntVector2&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "void set_disabledOffset(const IntVector2&in)", AS_METHODPR(DropDownList, SetDisabledOffset, (const IntVector2&), void), AS_CALL_THISCALL);
    // void BorderImage::SetDisabledOffset(int x, int y) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("DropDownList", "void SetDisabledOffset(int, int)", AS_METHODPR(DropDownList, SetDisabledOffset, (int, int), void), AS_CALL_THISCALL);
    // void UIElement::SetDragDropMode(DragAndDropModeFlags mode) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "void SetDragDropMode(DragAndDropModeFlags)", AS_METHODPR(DropDownList, SetDragDropMode, (DragAndDropModeFlags), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "void set_dragDropMode(DragAndDropModeFlags)", AS_METHODPR(DropDownList, SetDragDropMode, (DragAndDropModeFlags), void), AS_CALL_THISCALL);
    // void UIElement::SetEditable(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "void SetEditable(bool)", AS_METHODPR(DropDownList, SetEditable, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "void set_editable(bool)", AS_METHODPR(DropDownList, SetEditable, (bool), void), AS_CALL_THISCALL);
    // void UIElement::SetElementEventSender(bool flag) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "void SetElementEventSender(bool)", AS_METHODPR(DropDownList, SetElementEventSender, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "void set_elementEventSender(bool)", AS_METHODPR(DropDownList, SetElementEventSender, (bool), void), AS_CALL_THISCALL);
    // void UIElement::SetEnableAnchor(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "void SetEnableAnchor(bool)", AS_METHODPR(DropDownList, SetEnableAnchor, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "void set_enableAnchor(bool)", AS_METHODPR(DropDownList, SetEnableAnchor, (bool), void), AS_CALL_THISCALL);
    // void UIElement::SetEnabled(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "void SetEnabled(bool)", AS_METHODPR(DropDownList, SetEnabled, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "void set_enabled(bool)", AS_METHODPR(DropDownList, SetEnabled, (bool), void), AS_CALL_THISCALL);
    // void UIElement::SetEnabledRecursive(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "void SetEnabledRecursive(bool)", AS_METHODPR(DropDownList, SetEnabledRecursive, (bool), void), AS_CALL_THISCALL);
    // void UIElement::SetFixedHeight(int height) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "void SetFixedHeight(int)", AS_METHODPR(DropDownList, SetFixedHeight, (int), void), AS_CALL_THISCALL);
    // void UIElement::SetFixedSize(const IntVector2& size) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "void SetFixedSize(const IntVector2&in)", AS_METHODPR(DropDownList, SetFixedSize, (const IntVector2&), void), AS_CALL_THISCALL);
    // void UIElement::SetFixedSize(int width, int height) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "void SetFixedSize(int, int)", AS_METHODPR(DropDownList, SetFixedSize, (int, int), void), AS_CALL_THISCALL);
    // void UIElement::SetFixedWidth(int width) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "void SetFixedWidth(int)", AS_METHODPR(DropDownList, SetFixedWidth, (int), void), AS_CALL_THISCALL);
    // void UIElement::SetFocus(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "void SetFocus(bool)", AS_METHODPR(DropDownList, SetFocus, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "void set_focus(bool)", AS_METHODPR(DropDownList, SetFocus, (bool), void), AS_CALL_THISCALL);
    // void UIElement::SetFocusMode(FocusMode mode) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "void SetFocusMode(FocusMode)", AS_METHODPR(DropDownList, SetFocusMode, (FocusMode), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "void set_focusMode(FocusMode)", AS_METHODPR(DropDownList, SetFocusMode, (FocusMode), void), AS_CALL_THISCALL);
    // void BorderImage::SetFullImageRect() | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("DropDownList", "void SetFullImageRect()", AS_METHODPR(DropDownList, SetFullImageRect, (), void), AS_CALL_THISCALL);
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("DropDownList", "void SetGlobalVar(StringHash, const Variant&in)", AS_METHODPR(DropDownList, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "void set_globalVar(StringHash, const Variant&in)", AS_METHODPR(DropDownList, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    // void UIElement::SetHeight(int height) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "void SetHeight(int)", AS_METHODPR(DropDownList, SetHeight, (int), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "void set_height(int)", AS_METHODPR(DropDownList, SetHeight, (int), void), AS_CALL_THISCALL);
    // void UIElement::SetHorizontalAlignment(HorizontalAlignment align) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "void SetHorizontalAlignment(HorizontalAlignment)", AS_METHODPR(DropDownList, SetHorizontalAlignment, (HorizontalAlignment), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "void set_horizontalAlignment(HorizontalAlignment)", AS_METHODPR(DropDownList, SetHorizontalAlignment, (HorizontalAlignment), void), AS_CALL_THISCALL);
    // void UIElement::SetHovering(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "void SetHovering(bool)", AS_METHODPR(DropDownList, SetHovering, (bool), void), AS_CALL_THISCALL);
    // void BorderImage::SetHoverOffset(const IntVector2& offset) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("DropDownList", "void SetHoverOffset(const IntVector2&in)", AS_METHODPR(DropDownList, SetHoverOffset, (const IntVector2&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "void set_hoverOffset(const IntVector2&in)", AS_METHODPR(DropDownList, SetHoverOffset, (const IntVector2&), void), AS_CALL_THISCALL);
    // void BorderImage::SetHoverOffset(int x, int y) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("DropDownList", "void SetHoverOffset(int, int)", AS_METHODPR(DropDownList, SetHoverOffset, (int, int), void), AS_CALL_THISCALL);
    // void BorderImage::SetImageBorder(const IntRect& rect) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("DropDownList", "void SetImageBorder(const IntRect&in)", AS_METHODPR(DropDownList, SetImageBorder, (const IntRect&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "void set_imageBorder(const IntRect&in)", AS_METHODPR(DropDownList, SetImageBorder, (const IntRect&), void), AS_CALL_THISCALL);
    // void BorderImage::SetImageRect(const IntRect& rect) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("DropDownList", "void SetImageRect(const IntRect&in)", AS_METHODPR(DropDownList, SetImageRect, (const IntRect&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "void set_imageRect(const IntRect&in)", AS_METHODPR(DropDownList, SetImageRect, (const IntRect&), void), AS_CALL_THISCALL);
    // void UIElement::SetIndent(int indent) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "void SetIndent(int)", AS_METHODPR(DropDownList, SetIndent, (int), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "void set_indent(int)", AS_METHODPR(DropDownList, SetIndent, (int), void), AS_CALL_THISCALL);
    // void UIElement::SetIndentSpacing(int indentSpacing) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "void SetIndentSpacing(int)", AS_METHODPR(DropDownList, SetIndentSpacing, (int), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "void set_indentSpacing(int)", AS_METHODPR(DropDownList, SetIndentSpacing, (int), void), AS_CALL_THISCALL);
    // void Serializable::SetInstanceDefault(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("DropDownList", "void SetInstanceDefault(bool)", AS_METHODPR(DropDownList, SetInstanceDefault, (bool), void), AS_CALL_THISCALL);
    // void Serializable::SetInterceptNetworkUpdate(const String& attributeName, bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("DropDownList", "void SetInterceptNetworkUpdate(const String&in, bool)", AS_METHODPR(DropDownList, SetInterceptNetworkUpdate, (const String&, bool), void), AS_CALL_THISCALL);
    // void UIElement::SetInternal(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "void SetInternal(bool)", AS_METHODPR(DropDownList, SetInternal, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "void set_internal(bool)", AS_METHODPR(DropDownList, SetInternal, (bool), void), AS_CALL_THISCALL);
    // void UIElement::SetLayout(LayoutMode mode, int spacing=0, const IntRect& border=IntRect::ZERO) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "void SetLayout(LayoutMode, int = 0, const IntRect&in = IntRect::ZERO)", AS_METHODPR(DropDownList, SetLayout, (LayoutMode, int, const IntRect&), void), AS_CALL_THISCALL);
    // void UIElement::SetLayoutBorder(const IntRect& border) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "void SetLayoutBorder(const IntRect&in)", AS_METHODPR(DropDownList, SetLayoutBorder, (const IntRect&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "void set_layoutBorder(const IntRect&in)", AS_METHODPR(DropDownList, SetLayoutBorder, (const IntRect&), void), AS_CALL_THISCALL);
    // void UIElement::SetLayoutFlexScale(const Vector2& scale) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "void SetLayoutFlexScale(const Vector2&in)", AS_METHODPR(DropDownList, SetLayoutFlexScale, (const Vector2&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "void set_layoutFlexScale(const Vector2&in)", AS_METHODPR(DropDownList, SetLayoutFlexScale, (const Vector2&), void), AS_CALL_THISCALL);
    // void UIElement::SetLayoutMode(LayoutMode mode) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "void SetLayoutMode(LayoutMode)", AS_METHODPR(DropDownList, SetLayoutMode, (LayoutMode), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "void set_layoutMode(LayoutMode)", AS_METHODPR(DropDownList, SetLayoutMode, (LayoutMode), void), AS_CALL_THISCALL);
    // void UIElement::SetLayoutSpacing(int spacing) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "void SetLayoutSpacing(int)", AS_METHODPR(DropDownList, SetLayoutSpacing, (int), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "void set_layoutSpacing(int)", AS_METHODPR(DropDownList, SetLayoutSpacing, (int), void), AS_CALL_THISCALL);
    // void BorderImage::SetMaterial(Material* material) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("DropDownList", "void SetMaterial(Material@+)", AS_METHODPR(DropDownList, SetMaterial, (Material*), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "void set_material(Material@+)", AS_METHODPR(DropDownList, SetMaterial, (Material*), void), AS_CALL_THISCALL);
    // void BorderImage::SetMaterialAttr(const ResourceRef& value) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("DropDownList", "void SetMaterialAttr(const ResourceRef&in)", AS_METHODPR(DropDownList, SetMaterialAttr, (const ResourceRef&), void), AS_CALL_THISCALL);
    // void UIElement::SetMaxAnchor(const Vector2& anchor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "void SetMaxAnchor(const Vector2&in)", AS_METHODPR(DropDownList, SetMaxAnchor, (const Vector2&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "void set_maxAnchor(const Vector2&in)", AS_METHODPR(DropDownList, SetMaxAnchor, (const Vector2&), void), AS_CALL_THISCALL);
    // void UIElement::SetMaxAnchor(float x, float y) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "void SetMaxAnchor(float, float)", AS_METHODPR(DropDownList, SetMaxAnchor, (float, float), void), AS_CALL_THISCALL);
    // void UIElement::SetMaxHeight(int height) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "void SetMaxHeight(int)", AS_METHODPR(DropDownList, SetMaxHeight, (int), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "void set_maxHeight(int)", AS_METHODPR(DropDownList, SetMaxHeight, (int), void), AS_CALL_THISCALL);
    // void UIElement::SetMaxOffset(const IntVector2& offset) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "void SetMaxOffset(const IntVector2&in)", AS_METHODPR(DropDownList, SetMaxOffset, (const IntVector2&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "void set_maxOffset(const IntVector2&in)", AS_METHODPR(DropDownList, SetMaxOffset, (const IntVector2&), void), AS_CALL_THISCALL);
    // void UIElement::SetMaxSize(const IntVector2& maxSize) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "void SetMaxSize(const IntVector2&in)", AS_METHODPR(DropDownList, SetMaxSize, (const IntVector2&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "void set_maxSize(const IntVector2&in)", AS_METHODPR(DropDownList, SetMaxSize, (const IntVector2&), void), AS_CALL_THISCALL);
    // void UIElement::SetMaxSize(int width, int height) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "void SetMaxSize(int, int)", AS_METHODPR(DropDownList, SetMaxSize, (int, int), void), AS_CALL_THISCALL);
    // void UIElement::SetMaxWidth(int width) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "void SetMaxWidth(int)", AS_METHODPR(DropDownList, SetMaxWidth, (int), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "void set_maxWidth(int)", AS_METHODPR(DropDownList, SetMaxWidth, (int), void), AS_CALL_THISCALL);
    // void UIElement::SetMinAnchor(const Vector2& anchor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "void SetMinAnchor(const Vector2&in)", AS_METHODPR(DropDownList, SetMinAnchor, (const Vector2&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "void set_minAnchor(const Vector2&in)", AS_METHODPR(DropDownList, SetMinAnchor, (const Vector2&), void), AS_CALL_THISCALL);
    // void UIElement::SetMinAnchor(float x, float y) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "void SetMinAnchor(float, float)", AS_METHODPR(DropDownList, SetMinAnchor, (float, float), void), AS_CALL_THISCALL);
    // void UIElement::SetMinHeight(int height) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "void SetMinHeight(int)", AS_METHODPR(DropDownList, SetMinHeight, (int), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "void set_minHeight(int)", AS_METHODPR(DropDownList, SetMinHeight, (int), void), AS_CALL_THISCALL);
    // void UIElement::SetMinOffset(const IntVector2& offset) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "void SetMinOffset(const IntVector2&in)", AS_METHODPR(DropDownList, SetMinOffset, (const IntVector2&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "void set_minOffset(const IntVector2&in)", AS_METHODPR(DropDownList, SetMinOffset, (const IntVector2&), void), AS_CALL_THISCALL);
    // void UIElement::SetMinSize(const IntVector2& minSize) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "void SetMinSize(const IntVector2&in)", AS_METHODPR(DropDownList, SetMinSize, (const IntVector2&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "void set_minSize(const IntVector2&in)", AS_METHODPR(DropDownList, SetMinSize, (const IntVector2&), void), AS_CALL_THISCALL);
    // void UIElement::SetMinSize(int width, int height) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "void SetMinSize(int, int)", AS_METHODPR(DropDownList, SetMinSize, (int, int), void), AS_CALL_THISCALL);
    // void UIElement::SetMinWidth(int width) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "void SetMinWidth(int)", AS_METHODPR(DropDownList, SetMinWidth, (int), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "void set_minWidth(int)", AS_METHODPR(DropDownList, SetMinWidth, (int), void), AS_CALL_THISCALL);
    // void UIElement::SetName(const String& name) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "void SetName(const String&in)", AS_METHODPR(DropDownList, SetName, (const String&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "void set_name(const String&in)", AS_METHODPR(DropDownList, SetName, (const String&), void), AS_CALL_THISCALL);
    // void Animatable::SetObjectAnimation(ObjectAnimation* objectAnimation) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("DropDownList", "void SetObjectAnimation(ObjectAnimation@+)", AS_METHODPR(DropDownList, SetObjectAnimation, (ObjectAnimation*), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "void set_objectAnimation(ObjectAnimation@+)", AS_METHODPR(DropDownList, SetObjectAnimation, (ObjectAnimation*), void), AS_CALL_THISCALL);
    // void Animatable::SetObjectAnimationAttr(const ResourceRef& value) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("DropDownList", "void SetObjectAnimationAttr(const ResourceRef&in)", AS_METHODPR(DropDownList, SetObjectAnimationAttr, (const ResourceRef&), void), AS_CALL_THISCALL);
    // void UIElement::SetOpacity(float opacity) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "void SetOpacity(float)", AS_METHODPR(DropDownList, SetOpacity, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "void set_opacity(float)", AS_METHODPR(DropDownList, SetOpacity, (float), void), AS_CALL_THISCALL);
    // void UIElement::SetParent(UIElement* parent, unsigned index=M_MAX_UNSIGNED) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "void SetParent(UIElement@+, uint = M_MAX_UNSIGNED)", AS_METHODPR(DropDownList, SetParent, (UIElement*, unsigned), void), AS_CALL_THISCALL);
    // void UIElement::SetPivot(const Vector2& pivot) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "void SetPivot(const Vector2&in)", AS_METHODPR(DropDownList, SetPivot, (const Vector2&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "void set_pivot(const Vector2&in)", AS_METHODPR(DropDownList, SetPivot, (const Vector2&), void), AS_CALL_THISCALL);
    // void UIElement::SetPivot(float x, float y) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "void SetPivot(float, float)", AS_METHODPR(DropDownList, SetPivot, (float, float), void), AS_CALL_THISCALL);
    // void DropDownList::SetPlaceholderText(const String& text) | File: ../UI/DropDownList.h
    engine->RegisterObjectMethod("DropDownList", "void SetPlaceholderText(const String&in)", AS_METHODPR(DropDownList, SetPlaceholderText, (const String&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "void set_placeholderText(const String&in)", AS_METHODPR(DropDownList, SetPlaceholderText, (const String&), void), AS_CALL_THISCALL);
    // void Menu::SetPopup(UIElement* popup) | File: ../UI/Menu.h
    engine->RegisterObjectMethod("DropDownList", "void SetPopup(UIElement@+)", AS_METHODPR(DropDownList, SetPopup, (UIElement*), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "void set_popup(UIElement@+)", AS_METHODPR(DropDownList, SetPopup, (UIElement*), void), AS_CALL_THISCALL);
    // void Menu::SetPopupOffset(const IntVector2& offset) | File: ../UI/Menu.h
    engine->RegisterObjectMethod("DropDownList", "void SetPopupOffset(const IntVector2&in)", AS_METHODPR(DropDownList, SetPopupOffset, (const IntVector2&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "void set_popupOffset(const IntVector2&in)", AS_METHODPR(DropDownList, SetPopupOffset, (const IntVector2&), void), AS_CALL_THISCALL);
    // void Menu::SetPopupOffset(int x, int y) | File: ../UI/Menu.h
    engine->RegisterObjectMethod("DropDownList", "void SetPopupOffset(int, int)", AS_METHODPR(DropDownList, SetPopupOffset, (int, int), void), AS_CALL_THISCALL);
    // void UIElement::SetPosition(const IntVector2& position) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "void SetPosition(const IntVector2&in)", AS_METHODPR(DropDownList, SetPosition, (const IntVector2&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "void set_position(const IntVector2&in)", AS_METHODPR(DropDownList, SetPosition, (const IntVector2&), void), AS_CALL_THISCALL);
    // void UIElement::SetPosition(int x, int y) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "void SetPosition(int, int)", AS_METHODPR(DropDownList, SetPosition, (int, int), void), AS_CALL_THISCALL);
    // void Button::SetPressedChildOffset(const IntVector2& offset) | File: ../UI/Button.h
    engine->RegisterObjectMethod("DropDownList", "void SetPressedChildOffset(const IntVector2&in)", AS_METHODPR(DropDownList, SetPressedChildOffset, (const IntVector2&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "void set_pressedChildOffset(const IntVector2&in)", AS_METHODPR(DropDownList, SetPressedChildOffset, (const IntVector2&), void), AS_CALL_THISCALL);
    // void Button::SetPressedChildOffset(int x, int y) | File: ../UI/Button.h
    engine->RegisterObjectMethod("DropDownList", "void SetPressedChildOffset(int, int)", AS_METHODPR(DropDownList, SetPressedChildOffset, (int, int), void), AS_CALL_THISCALL);
    // void Button::SetPressedOffset(const IntVector2& offset) | File: ../UI/Button.h
    engine->RegisterObjectMethod("DropDownList", "void SetPressedOffset(const IntVector2&in)", AS_METHODPR(DropDownList, SetPressedOffset, (const IntVector2&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "void set_pressedOffset(const IntVector2&in)", AS_METHODPR(DropDownList, SetPressedOffset, (const IntVector2&), void), AS_CALL_THISCALL);
    // void Button::SetPressedOffset(int x, int y) | File: ../UI/Button.h
    engine->RegisterObjectMethod("DropDownList", "void SetPressedOffset(int, int)", AS_METHODPR(DropDownList, SetPressedOffset, (int, int), void), AS_CALL_THISCALL);
    // void UIElement::SetPriority(int priority) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "void SetPriority(int)", AS_METHODPR(DropDownList, SetPriority, (int), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "void set_priority(int)", AS_METHODPR(DropDownList, SetPriority, (int), void), AS_CALL_THISCALL);
    // void UIElement::SetRenderTexture(Texture2D* texture) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "void SetRenderTexture(Texture2D@+)", AS_METHODPR(DropDownList, SetRenderTexture, (Texture2D*), void), AS_CALL_THISCALL);
    // void Button::SetRepeat(float delay, float rate) | File: ../UI/Button.h
    engine->RegisterObjectMethod("DropDownList", "void SetRepeat(float, float)", AS_METHODPR(DropDownList, SetRepeat, (float, float), void), AS_CALL_THISCALL);
    // void Button::SetRepeatDelay(float delay) | File: ../UI/Button.h
    engine->RegisterObjectMethod("DropDownList", "void SetRepeatDelay(float)", AS_METHODPR(DropDownList, SetRepeatDelay, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "void set_repeatDelay(float)", AS_METHODPR(DropDownList, SetRepeatDelay, (float), void), AS_CALL_THISCALL);
    // void Button::SetRepeatRate(float rate) | File: ../UI/Button.h
    engine->RegisterObjectMethod("DropDownList", "void SetRepeatRate(float)", AS_METHODPR(DropDownList, SetRepeatRate, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "void set_repeatRate(float)", AS_METHODPR(DropDownList, SetRepeatRate, (float), void), AS_CALL_THISCALL);
    // void DropDownList::SetResizePopup(bool enable) | File: ../UI/DropDownList.h
    engine->RegisterObjectMethod("DropDownList", "void SetResizePopup(bool)", AS_METHODPR(DropDownList, SetResizePopup, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "void set_resizePopup(bool)", AS_METHODPR(DropDownList, SetResizePopup, (bool), void), AS_CALL_THISCALL);
    // void UIElement::SetSelected(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "void SetSelected(bool)", AS_METHODPR(DropDownList, SetSelected, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "void set_selected(bool)", AS_METHODPR(DropDownList, SetSelected, (bool), void), AS_CALL_THISCALL);
    // void DropDownList::SetSelection(unsigned index) | File: ../UI/DropDownList.h
    engine->RegisterObjectMethod("DropDownList", "void SetSelection(uint)", AS_METHODPR(DropDownList, SetSelection, (unsigned), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "void set_selection(uint)", AS_METHODPR(DropDownList, SetSelection, (unsigned), void), AS_CALL_THISCALL);
    // void DropDownList::SetSelectionAttr(unsigned index) | File: ../UI/DropDownList.h
    engine->RegisterObjectMethod("DropDownList", "void SetSelectionAttr(uint)", AS_METHODPR(DropDownList, SetSelectionAttr, (unsigned), void), AS_CALL_THISCALL);
    // void UIElement::SetSize(const IntVector2& size) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "void SetSize(const IntVector2&in)", AS_METHODPR(DropDownList, SetSize, (const IntVector2&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "void set_size(const IntVector2&in)", AS_METHODPR(DropDownList, SetSize, (const IntVector2&), void), AS_CALL_THISCALL);
    // void UIElement::SetSize(int width, int height) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "void SetSize(int, int)", AS_METHODPR(DropDownList, SetSize, (int, int), void), AS_CALL_THISCALL);
    // void UIElement::SetSortChildren(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "void SetSortChildren(bool)", AS_METHODPR(DropDownList, SetSortChildren, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "void set_sortChildren(bool)", AS_METHODPR(DropDownList, SetSortChildren, (bool), void), AS_CALL_THISCALL);
    // bool UIElement::SetStyle(const String& styleName, XMLFile* file=nullptr) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "bool SetStyle(const String&in, XMLFile@+ = null)", AS_METHODPR(DropDownList, SetStyle, (const String&, XMLFile*), bool), AS_CALL_THISCALL);
    // bool UIElement::SetStyle(const XMLElement& element) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "bool SetStyle(const XMLElement&in)", AS_METHODPR(DropDownList, SetStyle, (const XMLElement&), bool), AS_CALL_THISCALL);
    // bool UIElement::SetStyleAuto(XMLFile* file=nullptr) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "bool SetStyleAuto(XMLFile@+ = null)", AS_METHODPR(DropDownList, SetStyleAuto, (XMLFile*), bool), AS_CALL_THISCALL);
    // void UIElement::SetTags(const StringVector& tags) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "void SetTags(Array<String>@+)", AS_FUNCTION_OBJFIRST(DropDownList_SetTags_StringVector), AS_CALL_CDECL_OBJFIRST);
    // void Serializable::SetTemporary(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("DropDownList", "void SetTemporary(bool)", AS_METHODPR(DropDownList, SetTemporary, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "void set_temporary(bool)", AS_METHODPR(DropDownList, SetTemporary, (bool), void), AS_CALL_THISCALL);
    // void BorderImage::SetTexture(Texture* texture) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("DropDownList", "void SetTexture(Texture@+)", AS_METHODPR(DropDownList, SetTexture, (Texture*), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "void set_texture(Texture@+)", AS_METHODPR(DropDownList, SetTexture, (Texture*), void), AS_CALL_THISCALL);
    // void BorderImage::SetTextureAttr(const ResourceRef& value) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("DropDownList", "void SetTextureAttr(const ResourceRef&in)", AS_METHODPR(DropDownList, SetTextureAttr, (const ResourceRef&), void), AS_CALL_THISCALL);
    // void BorderImage::SetTiled(bool enable) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("DropDownList", "void SetTiled(bool)", AS_METHODPR(DropDownList, SetTiled, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "void set_tiled(bool)", AS_METHODPR(DropDownList, SetTiled, (bool), void), AS_CALL_THISCALL);
    // void UIElement::SetTraversalMode(TraversalMode traversalMode) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "void SetTraversalMode(TraversalMode)", AS_METHODPR(DropDownList, SetTraversalMode, (TraversalMode), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "void set_traversalMode(TraversalMode)", AS_METHODPR(DropDownList, SetTraversalMode, (TraversalMode), void), AS_CALL_THISCALL);
    // void UIElement::SetUseDerivedOpacity(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "void SetUseDerivedOpacity(bool)", AS_METHODPR(DropDownList, SetUseDerivedOpacity, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "void set_useDerivedOpacity(bool)", AS_METHODPR(DropDownList, SetUseDerivedOpacity, (bool), void), AS_CALL_THISCALL);
    // void UIElement::SetVar(StringHash key, const Variant& value) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "void SetVar(StringHash, const Variant&in)", AS_METHODPR(DropDownList, SetVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    // void UIElement::SetVerticalAlignment(VerticalAlignment align) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "void SetVerticalAlignment(VerticalAlignment)", AS_METHODPR(DropDownList, SetVerticalAlignment, (VerticalAlignment), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "void set_verticalAlignment(VerticalAlignment)", AS_METHODPR(DropDownList, SetVerticalAlignment, (VerticalAlignment), void), AS_CALL_THISCALL);
    // void UIElement::SetVisible(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "void SetVisible(bool)", AS_METHODPR(DropDownList, SetVisible, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "void set_visible(bool)", AS_METHODPR(DropDownList, SetVisible, (bool), void), AS_CALL_THISCALL);
    // void UIElement::SetWidth(int width) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "void SetWidth(int)", AS_METHODPR(DropDownList, SetWidth, (int), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "void set_width(int)", AS_METHODPR(DropDownList, SetWidth, (int), void), AS_CALL_THISCALL);
    // void Menu::ShowPopup(bool enable) | File: ../UI/Menu.h
    engine->RegisterObjectMethod("DropDownList", "void ShowPopup(bool)", AS_METHODPR(DropDownList, ShowPopup, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "void set_showPopup(bool)", AS_METHODPR(DropDownList, ShowPopup, (bool), void), AS_CALL_THISCALL);
    // void UIElement::SortChildren() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "void SortChildren()", AS_METHODPR(DropDownList, SortChildren, (), void), AS_CALL_THISCALL);
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod("DropDownList", "void UnsubscribeFromAllEvents()", AS_METHODPR(DropDownList, UnsubscribeFromAllEvents, (), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("DropDownList", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", AS_FUNCTION_OBJFIRST(DropDownList_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), AS_CALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("DropDownList", "void UnsubscribeFromEvent(StringHash)", AS_METHODPR(DropDownList, UnsubscribeFromEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("DropDownList", "void UnsubscribeFromEvent(Object@+, StringHash)", AS_METHODPR(DropDownList, UnsubscribeFromEvent, (Object*, StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("DropDownList", "void UnsubscribeFromEvents(Object@+)", AS_METHODPR(DropDownList, UnsubscribeFromEvents, (Object*), void), AS_CALL_THISCALL);
    // void Menu::Update(float timeStep) override | File: ../UI/Menu.h
    engine->RegisterObjectMethod("DropDownList", "void Update(float)", AS_METHODPR(DropDownList, Update, (float), void), AS_CALL_THISCALL);
    // void UIElement::UpdateLayout() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("DropDownList", "void UpdateLayout()", AS_METHODPR(DropDownList, UpdateLayout, (), void), AS_CALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("DropDownList", "int WeakRefs() const", AS_METHODPR(DropDownList, WeakRefs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DropDownList", "int get_weakRefs() const", AS_METHODPR(DropDownList, WeakRefs, () const, int), AS_CALL_THISCALL);
    // void Serializable::WriteDeltaUpdate(Serializer& dest, const DirtyBits& attributeBits, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("DropDownList", "void WriteDeltaUpdate(Serializer&, const DirtyBits&in, uint8)", AS_METHODPR(DropDownList, WriteDeltaUpdate, (Serializer&, const DirtyBits&, unsigned char), void), AS_CALL_THISCALL);
    // void Serializable::WriteInitialDeltaUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("DropDownList", "void WriteInitialDeltaUpdate(Serializer&, uint8)", AS_METHODPR(DropDownList, WriteInitialDeltaUpdate, (Serializer&, unsigned char), void), AS_CALL_THISCALL);
    // void Serializable::WriteLatestDataUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("DropDownList", "void WriteLatestDataUpdate(Serializer&, uint8)", AS_METHODPR(DropDownList, WriteLatestDataUpdate, (Serializer&, unsigned char), void), AS_CALL_THISCALL);
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
    engine->RegisterObjectBehaviour("DynamicNavigationMesh", asBEHAVE_ADDREF, "void f()", AS_METHODPR(DynamicNavigationMesh, AddRef, (), void), AS_CALL_THISCALL);
    // void Component::AddReplicationState(ComponentReplicationState* state) | File: ../Scene/Component.h
    // Error: type "ComponentReplicationState*" can not automatically bind
    // bool DynamicNavigationMesh::AddTile(const PODVector<unsigned char>& tileData) override | File: ../Navigation/DynamicNavigationMesh.h
    // Error: type "const PODVector<unsigned char>&" can not automatically bind
    // bool DynamicNavigationMesh::Allocate(const BoundingBox& boundingBox, unsigned maxTiles) override | File: ../Navigation/DynamicNavigationMesh.h
    engine->RegisterObjectMethod("DynamicNavigationMesh", "bool Allocate(const BoundingBox&in, uint)", AS_METHODPR(DynamicNavigationMesh, Allocate, (const BoundingBox&, unsigned), bool), AS_CALL_THISCALL);
    // void Serializable::AllocateNetworkState() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("DynamicNavigationMesh", "void AllocateNetworkState()", AS_METHODPR(DynamicNavigationMesh, AllocateNetworkState, (), void), AS_CALL_THISCALL);
    // virtual void Serializable::ApplyAttributes() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("DynamicNavigationMesh", "void ApplyAttributes()", AS_METHODPR(DynamicNavigationMesh, ApplyAttributes, (), void), AS_CALL_THISCALL);
    // bool DynamicNavigationMesh::Build() override | File: ../Navigation/DynamicNavigationMesh.h
    engine->RegisterObjectMethod("DynamicNavigationMesh", "bool Build()", AS_METHODPR(DynamicNavigationMesh, Build, (), bool), AS_CALL_THISCALL);
    // bool DynamicNavigationMesh::Build(const BoundingBox& boundingBox) override | File: ../Navigation/DynamicNavigationMesh.h
    engine->RegisterObjectMethod("DynamicNavigationMesh", "bool Build(const BoundingBox&in)", AS_METHODPR(DynamicNavigationMesh, Build, (const BoundingBox&), bool), AS_CALL_THISCALL);
    // bool DynamicNavigationMesh::Build(const IntVector2& from, const IntVector2& to) override | File: ../Navigation/DynamicNavigationMesh.h
    engine->RegisterObjectMethod("DynamicNavigationMesh", "bool Build(const IntVector2&in, const IntVector2&in)", AS_METHODPR(DynamicNavigationMesh, Build, (const IntVector2&, const IntVector2&), bool), AS_CALL_THISCALL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // void Component::CleanupConnection(Connection* connection) | File: ../Scene/Component.h
    // Not registered because have @manualbind mark
    // void DynamicNavigationMesh::DrawDebugGeometry(DebugRenderer* debug, bool depthTest) override | File: ../Navigation/DynamicNavigationMesh.h
    engine->RegisterObjectMethod("DynamicNavigationMesh", "void DrawDebugGeometry(DebugRenderer@+, bool)", AS_METHODPR(DynamicNavigationMesh, DrawDebugGeometry, (DebugRenderer*, bool), void), AS_CALL_THISCALL);
    // void DynamicNavigationMesh::DrawDebugGeometry(bool depthTest) | File: ../Navigation/DynamicNavigationMesh.h
    engine->RegisterObjectMethod("DynamicNavigationMesh", "void DrawDebugGeometry(bool)", AS_METHODPR(DynamicNavigationMesh, DrawDebugGeometry, (bool), void), AS_CALL_THISCALL);
    // explicit DynamicNavigationMesh::DynamicNavigationMesh(Context* context) | File: ../Navigation/DynamicNavigationMesh.h
    engine->RegisterObjectBehaviour("DynamicNavigationMesh", asBEHAVE_FACTORY, "DynamicNavigationMesh@+ f()", AS_FUNCTION(DynamicNavigationMesh_DynamicNavigationMesh_Context), AS_CALL_CDECL);
    // Vector3 NavigationMesh::FindNearestPoint(const Vector3& point, const Vector3& extents=Vector3::ONE, const dtQueryFilter* filter=nullptr, dtPolyRef* nearestRef=nullptr) | File: ../Navigation/NavigationMesh.h
    // Error: type "const dtQueryFilter*" can not automatically bind
    // void NavigationMesh::FindPath(PODVector<Vector3>& dest, const Vector3& start, const Vector3& end, const Vector3& extents=Vector3::ONE, const dtQueryFilter* filter=nullptr) | File: ../Navigation/NavigationMesh.h
    // Error: type "PODVector<Vector3>&" can not automatically bind
    // void NavigationMesh::FindPath(PODVector<NavigationPathPoint>& dest, const Vector3& start, const Vector3& end, const Vector3& extents=Vector3::ONE, const dtQueryFilter* filter=nullptr) | File: ../Navigation/NavigationMesh.h
    // Error: type "PODVector<NavigationPathPoint>&" can not automatically bind
    // float NavigationMesh::GetAgentHeight() const | File: ../Navigation/NavigationMesh.h
    engine->RegisterObjectMethod("DynamicNavigationMesh", "float GetAgentHeight() const", AS_METHODPR(DynamicNavigationMesh, GetAgentHeight, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DynamicNavigationMesh", "float get_agentHeight() const", AS_METHODPR(DynamicNavigationMesh, GetAgentHeight, () const, float), AS_CALL_THISCALL);
    // float NavigationMesh::GetAgentMaxClimb() const | File: ../Navigation/NavigationMesh.h
    engine->RegisterObjectMethod("DynamicNavigationMesh", "float GetAgentMaxClimb() const", AS_METHODPR(DynamicNavigationMesh, GetAgentMaxClimb, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DynamicNavigationMesh", "float get_agentMaxClimb() const", AS_METHODPR(DynamicNavigationMesh, GetAgentMaxClimb, () const, float), AS_CALL_THISCALL);
    // float NavigationMesh::GetAgentMaxSlope() const | File: ../Navigation/NavigationMesh.h
    engine->RegisterObjectMethod("DynamicNavigationMesh", "float GetAgentMaxSlope() const", AS_METHODPR(DynamicNavigationMesh, GetAgentMaxSlope, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DynamicNavigationMesh", "float get_agentMaxSlope() const", AS_METHODPR(DynamicNavigationMesh, GetAgentMaxSlope, () const, float), AS_CALL_THISCALL);
    // float NavigationMesh::GetAgentRadius() const | File: ../Navigation/NavigationMesh.h
    engine->RegisterObjectMethod("DynamicNavigationMesh", "float GetAgentRadius() const", AS_METHODPR(DynamicNavigationMesh, GetAgentRadius, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DynamicNavigationMesh", "float get_agentRadius() const", AS_METHODPR(DynamicNavigationMesh, GetAgentRadius, () const, float), AS_CALL_THISCALL);
    // bool Animatable::GetAnimationEnabled() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("DynamicNavigationMesh", "bool GetAnimationEnabled() const", AS_METHODPR(DynamicNavigationMesh, GetAnimationEnabled, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DynamicNavigationMesh", "bool get_animationEnabled() const", AS_METHODPR(DynamicNavigationMesh, GetAnimationEnabled, () const, bool), AS_CALL_THISCALL);
    // float NavigationMesh::GetAreaCost(unsigned areaID) const | File: ../Navigation/NavigationMesh.h
    engine->RegisterObjectMethod("DynamicNavigationMesh", "float GetAreaCost(uint) const", AS_METHODPR(DynamicNavigationMesh, GetAreaCost, (unsigned) const, float), AS_CALL_THISCALL);
    // Variant Serializable::GetAttribute(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("DynamicNavigationMesh", "Variant GetAttribute(uint) const", AS_METHODPR(DynamicNavigationMesh, GetAttribute, (unsigned) const, Variant), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DynamicNavigationMesh", "Variant get_attributes(uint) const", AS_METHODPR(DynamicNavigationMesh, GetAttribute, (unsigned) const, Variant), AS_CALL_THISCALL);
    // Variant Serializable::GetAttribute(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("DynamicNavigationMesh", "Variant GetAttribute(const String&in) const", AS_METHODPR(DynamicNavigationMesh, GetAttribute, (const String&) const, Variant), AS_CALL_THISCALL);
    // ValueAnimation* Animatable::GetAttributeAnimation(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("DynamicNavigationMesh", "ValueAnimation@+ GetAttributeAnimation(const String&in) const", AS_METHODPR(DynamicNavigationMesh, GetAttributeAnimation, (const String&) const, ValueAnimation*), AS_CALL_THISCALL);
    // float Animatable::GetAttributeAnimationSpeed(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("DynamicNavigationMesh", "float GetAttributeAnimationSpeed(const String&in) const", AS_METHODPR(DynamicNavigationMesh, GetAttributeAnimationSpeed, (const String&) const, float), AS_CALL_THISCALL);
    // float Animatable::GetAttributeAnimationTime(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("DynamicNavigationMesh", "float GetAttributeAnimationTime(const String&in) const", AS_METHODPR(DynamicNavigationMesh, GetAttributeAnimationTime, (const String&) const, float), AS_CALL_THISCALL);
    // WrapMode Animatable::GetAttributeAnimationWrapMode(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("DynamicNavigationMesh", "WrapMode GetAttributeAnimationWrapMode(const String&in) const", AS_METHODPR(DynamicNavigationMesh, GetAttributeAnimationWrapMode, (const String&) const, WrapMode), AS_CALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("DynamicNavigationMesh", "Variant GetAttributeDefault(uint) const", AS_METHODPR(DynamicNavigationMesh, GetAttributeDefault, (unsigned) const, Variant), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DynamicNavigationMesh", "Variant get_attributeDefaults(uint) const", AS_METHODPR(DynamicNavigationMesh, GetAttributeDefault, (unsigned) const, Variant), AS_CALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("DynamicNavigationMesh", "Variant GetAttributeDefault(const String&in) const", AS_METHODPR(DynamicNavigationMesh, GetAttributeDefault, (const String&) const, Variant), AS_CALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("DynamicNavigationMesh", "bool GetBlockEvents() const", AS_METHODPR(DynamicNavigationMesh, GetBlockEvents, () const, bool), AS_CALL_THISCALL);
    // const BoundingBox& NavigationMesh::GetBoundingBox() const | File: ../Navigation/NavigationMesh.h
    engine->RegisterObjectMethod("DynamicNavigationMesh", "const BoundingBox& GetBoundingBox() const", AS_METHODPR(DynamicNavigationMesh, GetBoundingBox, () const, const BoundingBox&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DynamicNavigationMesh", "const BoundingBox& get_boundingBox() const", AS_METHODPR(DynamicNavigationMesh, GetBoundingBox, () const, const BoundingBox&), AS_CALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("DynamicNavigationMesh", "const String& GetCategory() const", AS_METHODPR(DynamicNavigationMesh, GetCategory, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DynamicNavigationMesh", "const String& get_category() const", AS_METHODPR(DynamicNavigationMesh, GetCategory, () const, const String&), AS_CALL_THISCALL);
    // float NavigationMesh::GetCellHeight() const | File: ../Navigation/NavigationMesh.h
    engine->RegisterObjectMethod("DynamicNavigationMesh", "float GetCellHeight() const", AS_METHODPR(DynamicNavigationMesh, GetCellHeight, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DynamicNavigationMesh", "float get_cellHeight() const", AS_METHODPR(DynamicNavigationMesh, GetCellHeight, () const, float), AS_CALL_THISCALL);
    // float NavigationMesh::GetCellSize() const | File: ../Navigation/NavigationMesh.h
    engine->RegisterObjectMethod("DynamicNavigationMesh", "float GetCellSize() const", AS_METHODPR(DynamicNavigationMesh, GetCellSize, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DynamicNavigationMesh", "float get_cellSize() const", AS_METHODPR(DynamicNavigationMesh, GetCellSize, () const, float), AS_CALL_THISCALL);
    // Component* Component::GetComponent(StringHash type) const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("DynamicNavigationMesh", "Component@+ GetComponent(StringHash) const", AS_METHODPR(DynamicNavigationMesh, GetComponent, (StringHash) const, Component*), AS_CALL_THISCALL);
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
    engine->RegisterObjectMethod("DynamicNavigationMesh", "float GetDetailSampleDistance() const", AS_METHODPR(DynamicNavigationMesh, GetDetailSampleDistance, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DynamicNavigationMesh", "float get_detailSampleDistance() const", AS_METHODPR(DynamicNavigationMesh, GetDetailSampleDistance, () const, float), AS_CALL_THISCALL);
    // float NavigationMesh::GetDetailSampleMaxError() const | File: ../Navigation/NavigationMesh.h
    engine->RegisterObjectMethod("DynamicNavigationMesh", "float GetDetailSampleMaxError() const", AS_METHODPR(DynamicNavigationMesh, GetDetailSampleMaxError, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DynamicNavigationMesh", "float get_detailSampleMaxError() const", AS_METHODPR(DynamicNavigationMesh, GetDetailSampleMaxError, () const, float), AS_CALL_THISCALL);
    // float NavigationMesh::GetDistanceToWall(const Vector3& point, float radius, const Vector3& extents=Vector3::ONE, const dtQueryFilter* filter=nullptr, Vector3* hitPos=nullptr, Vector3* hitNormal=nullptr) | File: ../Navigation/NavigationMesh.h
    // Error: type "const dtQueryFilter*" can not automatically bind
    // bool NavigationMesh::GetDrawNavAreas() const | File: ../Navigation/NavigationMesh.h
    engine->RegisterObjectMethod("DynamicNavigationMesh", "bool GetDrawNavAreas() const", AS_METHODPR(DynamicNavigationMesh, GetDrawNavAreas, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DynamicNavigationMesh", "bool get_drawNavAreas() const", AS_METHODPR(DynamicNavigationMesh, GetDrawNavAreas, () const, bool), AS_CALL_THISCALL);
    // bool DynamicNavigationMesh::GetDrawObstacles() const | File: ../Navigation/DynamicNavigationMesh.h
    engine->RegisterObjectMethod("DynamicNavigationMesh", "bool GetDrawObstacles() const", AS_METHODPR(DynamicNavigationMesh, GetDrawObstacles, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DynamicNavigationMesh", "bool get_drawObstacles() const", AS_METHODPR(DynamicNavigationMesh, GetDrawObstacles, () const, bool), AS_CALL_THISCALL);
    // bool NavigationMesh::GetDrawOffMeshConnections() const | File: ../Navigation/NavigationMesh.h
    engine->RegisterObjectMethod("DynamicNavigationMesh", "bool GetDrawOffMeshConnections() const", AS_METHODPR(DynamicNavigationMesh, GetDrawOffMeshConnections, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DynamicNavigationMesh", "bool get_drawOffMeshConnections() const", AS_METHODPR(DynamicNavigationMesh, GetDrawOffMeshConnections, () const, bool), AS_CALL_THISCALL);
    // float NavigationMesh::GetEdgeMaxError() const | File: ../Navigation/NavigationMesh.h
    engine->RegisterObjectMethod("DynamicNavigationMesh", "float GetEdgeMaxError() const", AS_METHODPR(DynamicNavigationMesh, GetEdgeMaxError, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DynamicNavigationMesh", "float get_edgeMaxError() const", AS_METHODPR(DynamicNavigationMesh, GetEdgeMaxError, () const, float), AS_CALL_THISCALL);
    // float NavigationMesh::GetEdgeMaxLength() const | File: ../Navigation/NavigationMesh.h
    engine->RegisterObjectMethod("DynamicNavigationMesh", "float GetEdgeMaxLength() const", AS_METHODPR(DynamicNavigationMesh, GetEdgeMaxLength, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DynamicNavigationMesh", "float get_edgeMaxLength() const", AS_METHODPR(DynamicNavigationMesh, GetEdgeMaxLength, () const, float), AS_CALL_THISCALL);
    // VariantMap& Object::GetEventDataMap() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("DynamicNavigationMesh", "VariantMap& GetEventDataMap() const", AS_METHODPR(DynamicNavigationMesh, GetEventDataMap, () const, VariantMap&), AS_CALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("DynamicNavigationMesh", "Object@+ GetEventSender() const", AS_METHODPR(DynamicNavigationMesh, GetEventSender, () const, Object*), AS_CALL_THISCALL);
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("DynamicNavigationMesh", "const Variant& GetGlobalVar(StringHash) const", AS_METHODPR(DynamicNavigationMesh, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DynamicNavigationMesh", "const Variant& get_globalVar(StringHash) const", AS_METHODPR(DynamicNavigationMesh, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("DynamicNavigationMesh", "const VariantMap& GetGlobalVars() const", AS_METHODPR(DynamicNavigationMesh, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DynamicNavigationMesh", "const VariantMap& get_globalVars() const", AS_METHODPR(DynamicNavigationMesh, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    // unsigned Component::GetID() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("DynamicNavigationMesh", "uint GetID() const", AS_METHODPR(DynamicNavigationMesh, GetID, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DynamicNavigationMesh", "uint get_id() const", AS_METHODPR(DynamicNavigationMesh, GetID, () const, unsigned), AS_CALL_THISCALL);
    // bool Serializable::GetInterceptNetworkUpdate(const String& attributeName) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("DynamicNavigationMesh", "bool GetInterceptNetworkUpdate(const String&in) const", AS_METHODPR(DynamicNavigationMesh, GetInterceptNetworkUpdate, (const String&) const, bool), AS_CALL_THISCALL);
    // unsigned DynamicNavigationMesh::GetMaxLayers() const | File: ../Navigation/DynamicNavigationMesh.h
    engine->RegisterObjectMethod("DynamicNavigationMesh", "uint GetMaxLayers() const", AS_METHODPR(DynamicNavigationMesh, GetMaxLayers, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DynamicNavigationMesh", "uint get_maxLayers() const", AS_METHODPR(DynamicNavigationMesh, GetMaxLayers, () const, unsigned), AS_CALL_THISCALL);
    // unsigned DynamicNavigationMesh::GetMaxObstacles() const | File: ../Navigation/DynamicNavigationMesh.h
    engine->RegisterObjectMethod("DynamicNavigationMesh", "uint GetMaxObstacles() const", AS_METHODPR(DynamicNavigationMesh, GetMaxObstacles, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DynamicNavigationMesh", "uint get_maxObstacles() const", AS_METHODPR(DynamicNavigationMesh, GetMaxObstacles, () const, unsigned), AS_CALL_THISCALL);
    // String NavigationMesh::GetMeshName() const | File: ../Navigation/NavigationMesh.h
    engine->RegisterObjectMethod("DynamicNavigationMesh", "String GetMeshName() const", AS_METHODPR(DynamicNavigationMesh, GetMeshName, () const, String), AS_CALL_THISCALL);
    // PODVector<unsigned char> DynamicNavigationMesh::GetNavigationDataAttr() const override | File: ../Navigation/DynamicNavigationMesh.h
    // Error: type "PODVector<unsigned char>" can not automatically bind
    // virtual const Vector<AttributeInfo>* Serializable::GetNetworkAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // NetworkState* Serializable::GetNetworkState() const | File: ../Scene/Serializable.h
    // Error: type "NetworkState*" can not automatically bind
    // Node* Component::GetNode() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("DynamicNavigationMesh", "Node@+ GetNode() const", AS_METHODPR(DynamicNavigationMesh, GetNode, () const, Node*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DynamicNavigationMesh", "Node@+ get_node() const", AS_METHODPR(DynamicNavigationMesh, GetNode, () const, Node*), AS_CALL_THISCALL);
    // unsigned Serializable::GetNumAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("DynamicNavigationMesh", "uint GetNumAttributes() const", AS_METHODPR(DynamicNavigationMesh, GetNumAttributes, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DynamicNavigationMesh", "uint get_numAttributes() const", AS_METHODPR(DynamicNavigationMesh, GetNumAttributes, () const, unsigned), AS_CALL_THISCALL);
    // unsigned Serializable::GetNumNetworkAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("DynamicNavigationMesh", "uint GetNumNetworkAttributes() const", AS_METHODPR(DynamicNavigationMesh, GetNumNetworkAttributes, () const, unsigned), AS_CALL_THISCALL);
    // IntVector2 NavigationMesh::GetNumTiles() const | File: ../Navigation/NavigationMesh.h
    engine->RegisterObjectMethod("DynamicNavigationMesh", "IntVector2 GetNumTiles() const", AS_METHODPR(DynamicNavigationMesh, GetNumTiles, () const, IntVector2), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DynamicNavigationMesh", "IntVector2 get_numTiles() const", AS_METHODPR(DynamicNavigationMesh, GetNumTiles, () const, IntVector2), AS_CALL_THISCALL);
    // ObjectAnimation* Animatable::GetObjectAnimation() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("DynamicNavigationMesh", "ObjectAnimation@+ GetObjectAnimation() const", AS_METHODPR(DynamicNavigationMesh, GetObjectAnimation, () const, ObjectAnimation*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DynamicNavigationMesh", "ObjectAnimation@+ get_objectAnimation() const", AS_METHODPR(DynamicNavigationMesh, GetObjectAnimation, () const, ObjectAnimation*), AS_CALL_THISCALL);
    // ResourceRef Animatable::GetObjectAnimationAttr() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("DynamicNavigationMesh", "ResourceRef GetObjectAnimationAttr() const", AS_METHODPR(DynamicNavigationMesh, GetObjectAnimationAttr, () const, ResourceRef), AS_CALL_THISCALL);
    // const Vector3& NavigationMesh::GetPadding() const | File: ../Navigation/NavigationMesh.h
    engine->RegisterObjectMethod("DynamicNavigationMesh", "const Vector3& GetPadding() const", AS_METHODPR(DynamicNavigationMesh, GetPadding, () const, const Vector3&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DynamicNavigationMesh", "const Vector3& get_padding() const", AS_METHODPR(DynamicNavigationMesh, GetPadding, () const, const Vector3&), AS_CALL_THISCALL);
    // NavmeshPartitionType NavigationMesh::GetPartitionType() const | File: ../Navigation/NavigationMesh.h
    engine->RegisterObjectMethod("DynamicNavigationMesh", "NavmeshPartitionType GetPartitionType() const", AS_METHODPR(DynamicNavigationMesh, GetPartitionType, () const, NavmeshPartitionType), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DynamicNavigationMesh", "NavmeshPartitionType get_partitionType() const", AS_METHODPR(DynamicNavigationMesh, GetPartitionType, () const, NavmeshPartitionType), AS_CALL_THISCALL);
    // Vector3 NavigationMesh::GetRandomPoint(const dtQueryFilter* filter=nullptr, dtPolyRef* randomRef=nullptr) | File: ../Navigation/NavigationMesh.h
    // Error: type "const dtQueryFilter*" can not automatically bind
    // Vector3 NavigationMesh::GetRandomPointInCircle(const Vector3& center, float radius, const Vector3& extents=Vector3::ONE, const dtQueryFilter* filter=nullptr, dtPolyRef* randomRef=nullptr) | File: ../Navigation/NavigationMesh.h
    // Error: type "const dtQueryFilter*" can not automatically bind
    // float NavigationMesh::GetRegionMergeSize() const | File: ../Navigation/NavigationMesh.h
    engine->RegisterObjectMethod("DynamicNavigationMesh", "float GetRegionMergeSize() const", AS_METHODPR(DynamicNavigationMesh, GetRegionMergeSize, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DynamicNavigationMesh", "float get_regionMergeSize() const", AS_METHODPR(DynamicNavigationMesh, GetRegionMergeSize, () const, float), AS_CALL_THISCALL);
    // float NavigationMesh::GetRegionMinSize() const | File: ../Navigation/NavigationMesh.h
    engine->RegisterObjectMethod("DynamicNavigationMesh", "float GetRegionMinSize() const", AS_METHODPR(DynamicNavigationMesh, GetRegionMinSize, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DynamicNavigationMesh", "float get_regionMinSize() const", AS_METHODPR(DynamicNavigationMesh, GetRegionMinSize, () const, float), AS_CALL_THISCALL);
    // Scene* Component::GetScene() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("DynamicNavigationMesh", "Scene@+ GetScene() const", AS_METHODPR(DynamicNavigationMesh, GetScene, () const, Scene*), AS_CALL_THISCALL);
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("DynamicNavigationMesh", "Object@+ GetSubsystem(StringHash) const", AS_METHODPR(DynamicNavigationMesh, GetSubsystem, (StringHash) const, Object*), AS_CALL_THISCALL);
    // template<class T> T* Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // BoundingBox NavigationMesh::GetTileBoundingBox(const IntVector2& tile) const | File: ../Navigation/NavigationMesh.h
    engine->RegisterObjectMethod("DynamicNavigationMesh", "BoundingBox GetTileBoundingBox(const IntVector2&in) const", AS_METHODPR(DynamicNavigationMesh, GetTileBoundingBox, (const IntVector2&) const, BoundingBox), AS_CALL_THISCALL);
    // PODVector<unsigned char> DynamicNavigationMesh::GetTileData(const IntVector2& tile) const override | File: ../Navigation/DynamicNavigationMesh.h
    // Error: type "PODVector<unsigned char>" can not automatically bind
    // IntVector2 NavigationMesh::GetTileIndex(const Vector3& position) const | File: ../Navigation/NavigationMesh.h
    engine->RegisterObjectMethod("DynamicNavigationMesh", "IntVector2 GetTileIndex(const Vector3&in) const", AS_METHODPR(DynamicNavigationMesh, GetTileIndex, (const Vector3&) const, IntVector2), AS_CALL_THISCALL);
    // int NavigationMesh::GetTileSize() const | File: ../Navigation/NavigationMesh.h
    engine->RegisterObjectMethod("DynamicNavigationMesh", "int GetTileSize() const", AS_METHODPR(DynamicNavigationMesh, GetTileSize, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DynamicNavigationMesh", "int get_tileSize() const", AS_METHODPR(DynamicNavigationMesh, GetTileSize, () const, int), AS_CALL_THISCALL);
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("DynamicNavigationMesh", "StringHash GetType() const", AS_METHODPR(DynamicNavigationMesh, GetType, () const, StringHash), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DynamicNavigationMesh", "StringHash get_type() const", AS_METHODPR(DynamicNavigationMesh, GetType, () const, StringHash), AS_CALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("DynamicNavigationMesh", "const String& GetTypeName() const", AS_METHODPR(DynamicNavigationMesh, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DynamicNavigationMesh", "const String& get_typeName() const", AS_METHODPR(DynamicNavigationMesh, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    // BoundingBox NavigationMesh::GetWorldBoundingBox() const | File: ../Navigation/NavigationMesh.h
    engine->RegisterObjectMethod("DynamicNavigationMesh", "BoundingBox GetWorldBoundingBox() const", AS_METHODPR(DynamicNavigationMesh, GetWorldBoundingBox, () const, BoundingBox), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DynamicNavigationMesh", "BoundingBox get_worldBoundingBox() const", AS_METHODPR(DynamicNavigationMesh, GetWorldBoundingBox, () const, BoundingBox), AS_CALL_THISCALL);
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("DynamicNavigationMesh", "bool HasEventHandlers() const", AS_METHODPR(DynamicNavigationMesh, HasEventHandlers, () const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("DynamicNavigationMesh", "bool HasSubscribedToEvent(StringHash) const", AS_METHODPR(DynamicNavigationMesh, HasSubscribedToEvent, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("DynamicNavigationMesh", "bool HasSubscribedToEvent(Object@+, StringHash) const", AS_METHODPR(DynamicNavigationMesh, HasSubscribedToEvent, (Object*, StringHash) const, bool), AS_CALL_THISCALL);
    // bool NavigationMesh::HasTile(const IntVector2& tile) const | File: ../Navigation/NavigationMesh.h
    engine->RegisterObjectMethod("DynamicNavigationMesh", "bool HasTile(const IntVector2&in) const", AS_METHODPR(DynamicNavigationMesh, HasTile, (const IntVector2&) const, bool), AS_CALL_THISCALL);
    // bool Component::IsEnabled() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("DynamicNavigationMesh", "bool IsEnabled() const", AS_METHODPR(DynamicNavigationMesh, IsEnabled, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DynamicNavigationMesh", "bool get_enabled() const", AS_METHODPR(DynamicNavigationMesh, IsEnabled, () const, bool), AS_CALL_THISCALL);
    // bool Component::IsEnabledEffective() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("DynamicNavigationMesh", "bool IsEnabledEffective() const", AS_METHODPR(DynamicNavigationMesh, IsEnabledEffective, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DynamicNavigationMesh", "bool get_enabledEffective() const", AS_METHODPR(DynamicNavigationMesh, IsEnabledEffective, () const, bool), AS_CALL_THISCALL);
    // bool NavigationMesh::IsInitialized() const | File: ../Navigation/NavigationMesh.h
    engine->RegisterObjectMethod("DynamicNavigationMesh", "bool IsInitialized() const", AS_METHODPR(DynamicNavigationMesh, IsInitialized, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DynamicNavigationMesh", "bool get_initialized() const", AS_METHODPR(DynamicNavigationMesh, IsInitialized, () const, bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("DynamicNavigationMesh", "bool IsInstanceOf(StringHash) const", AS_METHODPR(DynamicNavigationMesh, IsInstanceOf, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // bool DynamicNavigationMesh::IsObstacleInTile(Obstacle* obstacle, const IntVector2& tile) const | File: ../Navigation/DynamicNavigationMesh.h
    engine->RegisterObjectMethod("DynamicNavigationMesh", "bool IsObstacleInTile(Obstacle@+, const IntVector2&in) const", AS_METHODPR(DynamicNavigationMesh, IsObstacleInTile, (Obstacle*, const IntVector2&) const, bool), AS_CALL_THISCALL);
    // bool Component::IsReplicated() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("DynamicNavigationMesh", "bool IsReplicated() const", AS_METHODPR(DynamicNavigationMesh, IsReplicated, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DynamicNavigationMesh", "bool get_replicated() const", AS_METHODPR(DynamicNavigationMesh, IsReplicated, () const, bool), AS_CALL_THISCALL);
    // bool Serializable::IsTemporary() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("DynamicNavigationMesh", "bool IsTemporary() const", AS_METHODPR(DynamicNavigationMesh, IsTemporary, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DynamicNavigationMesh", "bool get_temporary() const", AS_METHODPR(DynamicNavigationMesh, IsTemporary, () const, bool), AS_CALL_THISCALL);
    // virtual bool Serializable::Load(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("DynamicNavigationMesh", "bool Load(Deserializer&)", AS_METHODPR(DynamicNavigationMesh, Load, (Deserializer&), bool), AS_CALL_THISCALL);
    // bool Animatable::LoadJSON(const JSONValue& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("DynamicNavigationMesh", "bool LoadJSON(const JSONValue&in)", AS_METHODPR(DynamicNavigationMesh, LoadJSON, (const JSONValue&), bool), AS_CALL_THISCALL);
    // bool Animatable::LoadXML(const XMLElement& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("DynamicNavigationMesh", "bool LoadXML(const XMLElement&in)", AS_METHODPR(DynamicNavigationMesh, LoadXML, (const XMLElement&), bool), AS_CALL_THISCALL);
    // void Component::MarkNetworkUpdate() override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("DynamicNavigationMesh", "void MarkNetworkUpdate()", AS_METHODPR(DynamicNavigationMesh, MarkNetworkUpdate, (), void), AS_CALL_THISCALL);
    // Vector3 NavigationMesh::MoveAlongSurface(const Vector3& start, const Vector3& end, const Vector3& extents=Vector3::ONE, int maxVisited=3, const dtQueryFilter* filter=nullptr) | File: ../Navigation/NavigationMesh.h
    // Error: type "const dtQueryFilter*" can not automatically bind
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("DynamicNavigationMesh", "void OnEvent(Object@+, StringHash, VariantMap&)", AS_METHODPR(DynamicNavigationMesh, OnEvent, (Object*, StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // virtual void Serializable::OnGetAttribute(const AttributeInfo& attr, Variant& dest) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("DynamicNavigationMesh", "void OnGetAttribute(const AttributeInfo&in, Variant&) const", AS_METHODPR(DynamicNavigationMesh, OnGetAttribute, (const AttributeInfo&, Variant&) const, void), AS_CALL_THISCALL);
    // virtual void Serializable::OnSetAttribute(const AttributeInfo& attr, const Variant& src) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("DynamicNavigationMesh", "void OnSetAttribute(const AttributeInfo&in, const Variant&in)", AS_METHODPR(DynamicNavigationMesh, OnSetAttribute, (const AttributeInfo&, const Variant&), void), AS_CALL_THISCALL);
    // virtual void Component::OnSetEnabled() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("DynamicNavigationMesh", "void OnSetEnabled()", AS_METHODPR(DynamicNavigationMesh, OnSetEnabled, (), void), AS_CALL_THISCALL);
    // void Component::PrepareNetworkUpdate() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("DynamicNavigationMesh", "void PrepareNetworkUpdate()", AS_METHODPR(DynamicNavigationMesh, PrepareNetworkUpdate, (), void), AS_CALL_THISCALL);
    // Vector3 NavigationMesh::Raycast(const Vector3& start, const Vector3& end, const Vector3& extents=Vector3::ONE, const dtQueryFilter* filter=nullptr, Vector3* hitNormal=nullptr) | File: ../Navigation/NavigationMesh.h
    // Error: type "const dtQueryFilter*" can not automatically bind
    // bool Serializable::ReadDeltaUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("DynamicNavigationMesh", "bool ReadDeltaUpdate(Deserializer&)", AS_METHODPR(DynamicNavigationMesh, ReadDeltaUpdate, (Deserializer&), bool), AS_CALL_THISCALL);
    // bool Serializable::ReadLatestDataUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("DynamicNavigationMesh", "bool ReadLatestDataUpdate(Deserializer&)", AS_METHODPR(DynamicNavigationMesh, ReadLatestDataUpdate, (Deserializer&), bool), AS_CALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("DynamicNavigationMesh", "int Refs() const", AS_METHODPR(DynamicNavigationMesh, Refs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DynamicNavigationMesh", "int get_refs() const", AS_METHODPR(DynamicNavigationMesh, Refs, () const, int), AS_CALL_THISCALL);
    // static void DynamicNavigationMesh::RegisterObject(Context* context) | File: ../Navigation/DynamicNavigationMesh.h
    // Not registered because have @nobind mark
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("DynamicNavigationMesh", asBEHAVE_RELEASE, "void f()", AS_METHODPR(DynamicNavigationMesh, ReleaseRef, (), void), AS_CALL_THISCALL);
    // void Component::Remove() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("DynamicNavigationMesh", "void Remove()", AS_METHODPR(DynamicNavigationMesh, Remove, (), void), AS_CALL_THISCALL);
    // void DynamicNavigationMesh::RemoveAllTiles() override | File: ../Navigation/DynamicNavigationMesh.h
    engine->RegisterObjectMethod("DynamicNavigationMesh", "void RemoveAllTiles()", AS_METHODPR(DynamicNavigationMesh, RemoveAllTiles, (), void), AS_CALL_THISCALL);
    // void Animatable::RemoveAttributeAnimation(const String& name) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("DynamicNavigationMesh", "void RemoveAttributeAnimation(const String&in)", AS_METHODPR(DynamicNavigationMesh, RemoveAttributeAnimation, (const String&), void), AS_CALL_THISCALL);
    // void Serializable::RemoveInstanceDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("DynamicNavigationMesh", "void RemoveInstanceDefault()", AS_METHODPR(DynamicNavigationMesh, RemoveInstanceDefault, (), void), AS_CALL_THISCALL);
    // void Animatable::RemoveObjectAnimation() | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("DynamicNavigationMesh", "void RemoveObjectAnimation()", AS_METHODPR(DynamicNavigationMesh, RemoveObjectAnimation, (), void), AS_CALL_THISCALL);
    // void DynamicNavigationMesh::RemoveTile(const IntVector2& tile) override | File: ../Navigation/DynamicNavigationMesh.h
    engine->RegisterObjectMethod("DynamicNavigationMesh", "void RemoveTile(const IntVector2&in)", AS_METHODPR(DynamicNavigationMesh, RemoveTile, (const IntVector2&), void), AS_CALL_THISCALL);
    // void Serializable::ResetToDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("DynamicNavigationMesh", "void ResetToDefault()", AS_METHODPR(DynamicNavigationMesh, ResetToDefault, (), void), AS_CALL_THISCALL);
    // bool Component::Save(Serializer& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("DynamicNavigationMesh", "bool Save(Serializer&) const", AS_METHODPR(DynamicNavigationMesh, Save, (Serializer&) const, bool), AS_CALL_THISCALL);
    // virtual bool Serializable::SaveDefaultAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("DynamicNavigationMesh", "bool SaveDefaultAttributes() const", AS_METHODPR(DynamicNavigationMesh, SaveDefaultAttributes, () const, bool), AS_CALL_THISCALL);
    // bool Component::SaveJSON(JSONValue& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("DynamicNavigationMesh", "bool SaveJSON(JSONValue&) const", AS_METHODPR(DynamicNavigationMesh, SaveJSON, (JSONValue&) const, bool), AS_CALL_THISCALL);
    // bool Component::SaveXML(XMLElement& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("DynamicNavigationMesh", "bool SaveXML(XMLElement&) const", AS_METHODPR(DynamicNavigationMesh, SaveXML, (XMLElement&) const, bool), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("DynamicNavigationMesh", "void SendEvent(StringHash)", AS_METHODPR(DynamicNavigationMesh, SendEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("DynamicNavigationMesh", "void SendEvent(StringHash, VariantMap&)", AS_METHODPR(DynamicNavigationMesh, SendEvent, (StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void NavigationMesh::SetAgentHeight(float height) | File: ../Navigation/NavigationMesh.h
    engine->RegisterObjectMethod("DynamicNavigationMesh", "void SetAgentHeight(float)", AS_METHODPR(DynamicNavigationMesh, SetAgentHeight, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DynamicNavigationMesh", "void set_agentHeight(float)", AS_METHODPR(DynamicNavigationMesh, SetAgentHeight, (float), void), AS_CALL_THISCALL);
    // void NavigationMesh::SetAgentMaxClimb(float maxClimb) | File: ../Navigation/NavigationMesh.h
    engine->RegisterObjectMethod("DynamicNavigationMesh", "void SetAgentMaxClimb(float)", AS_METHODPR(DynamicNavigationMesh, SetAgentMaxClimb, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DynamicNavigationMesh", "void set_agentMaxClimb(float)", AS_METHODPR(DynamicNavigationMesh, SetAgentMaxClimb, (float), void), AS_CALL_THISCALL);
    // void NavigationMesh::SetAgentMaxSlope(float maxSlope) | File: ../Navigation/NavigationMesh.h
    engine->RegisterObjectMethod("DynamicNavigationMesh", "void SetAgentMaxSlope(float)", AS_METHODPR(DynamicNavigationMesh, SetAgentMaxSlope, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DynamicNavigationMesh", "void set_agentMaxSlope(float)", AS_METHODPR(DynamicNavigationMesh, SetAgentMaxSlope, (float), void), AS_CALL_THISCALL);
    // void NavigationMesh::SetAgentRadius(float radius) | File: ../Navigation/NavigationMesh.h
    engine->RegisterObjectMethod("DynamicNavigationMesh", "void SetAgentRadius(float)", AS_METHODPR(DynamicNavigationMesh, SetAgentRadius, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DynamicNavigationMesh", "void set_agentRadius(float)", AS_METHODPR(DynamicNavigationMesh, SetAgentRadius, (float), void), AS_CALL_THISCALL);
    // void Animatable::SetAnimationEnabled(bool enable) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("DynamicNavigationMesh", "void SetAnimationEnabled(bool)", AS_METHODPR(DynamicNavigationMesh, SetAnimationEnabled, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DynamicNavigationMesh", "void set_animationEnabled(bool)", AS_METHODPR(DynamicNavigationMesh, SetAnimationEnabled, (bool), void), AS_CALL_THISCALL);
    // void Animatable::SetAnimationTime(float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("DynamicNavigationMesh", "void SetAnimationTime(float)", AS_METHODPR(DynamicNavigationMesh, SetAnimationTime, (float), void), AS_CALL_THISCALL);
    // void NavigationMesh::SetAreaCost(unsigned areaID, float cost) | File: ../Navigation/NavigationMesh.h
    engine->RegisterObjectMethod("DynamicNavigationMesh", "void SetAreaCost(uint, float)", AS_METHODPR(DynamicNavigationMesh, SetAreaCost, (unsigned, float), void), AS_CALL_THISCALL);
    // bool Serializable::SetAttribute(unsigned index, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("DynamicNavigationMesh", "bool SetAttribute(uint, const Variant&in)", AS_METHODPR(DynamicNavigationMesh, SetAttribute, (unsigned, const Variant&), bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DynamicNavigationMesh", "bool set_attributes(uint, const Variant&in)", AS_METHODPR(DynamicNavigationMesh, SetAttribute, (unsigned, const Variant&), bool), AS_CALL_THISCALL);
    // bool Serializable::SetAttribute(const String& name, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("DynamicNavigationMesh", "bool SetAttribute(const String&in, const Variant&in)", AS_METHODPR(DynamicNavigationMesh, SetAttribute, (const String&, const Variant&), bool), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimation(const String& name, ValueAnimation* attributeAnimation, WrapMode wrapMode=WM_LOOP, float speed=1.0f) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("DynamicNavigationMesh", "void SetAttributeAnimation(const String&in, ValueAnimation@+, WrapMode = WM_LOOP, float = 1.0f)", AS_METHODPR(DynamicNavigationMesh, SetAttributeAnimation, (const String&, ValueAnimation*, WrapMode, float), void), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimationSpeed(const String& name, float speed) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("DynamicNavigationMesh", "void SetAttributeAnimationSpeed(const String&in, float)", AS_METHODPR(DynamicNavigationMesh, SetAttributeAnimationSpeed, (const String&, float), void), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimationTime(const String& name, float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("DynamicNavigationMesh", "void SetAttributeAnimationTime(const String&in, float)", AS_METHODPR(DynamicNavigationMesh, SetAttributeAnimationTime, (const String&, float), void), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimationWrapMode(const String& name, WrapMode wrapMode) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("DynamicNavigationMesh", "void SetAttributeAnimationWrapMode(const String&in, WrapMode)", AS_METHODPR(DynamicNavigationMesh, SetAttributeAnimationWrapMode, (const String&, WrapMode), void), AS_CALL_THISCALL);
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("DynamicNavigationMesh", "void SetBlockEvents(bool)", AS_METHODPR(DynamicNavigationMesh, SetBlockEvents, (bool), void), AS_CALL_THISCALL);
    // void NavigationMesh::SetCellHeight(float height) | File: ../Navigation/NavigationMesh.h
    engine->RegisterObjectMethod("DynamicNavigationMesh", "void SetCellHeight(float)", AS_METHODPR(DynamicNavigationMesh, SetCellHeight, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DynamicNavigationMesh", "void set_cellHeight(float)", AS_METHODPR(DynamicNavigationMesh, SetCellHeight, (float), void), AS_CALL_THISCALL);
    // void NavigationMesh::SetCellSize(float size) | File: ../Navigation/NavigationMesh.h
    engine->RegisterObjectMethod("DynamicNavigationMesh", "void SetCellSize(float)", AS_METHODPR(DynamicNavigationMesh, SetCellSize, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DynamicNavigationMesh", "void set_cellSize(float)", AS_METHODPR(DynamicNavigationMesh, SetCellSize, (float), void), AS_CALL_THISCALL);
    // void NavigationMesh::SetDetailSampleDistance(float distance) | File: ../Navigation/NavigationMesh.h
    engine->RegisterObjectMethod("DynamicNavigationMesh", "void SetDetailSampleDistance(float)", AS_METHODPR(DynamicNavigationMesh, SetDetailSampleDistance, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DynamicNavigationMesh", "void set_detailSampleDistance(float)", AS_METHODPR(DynamicNavigationMesh, SetDetailSampleDistance, (float), void), AS_CALL_THISCALL);
    // void NavigationMesh::SetDetailSampleMaxError(float error) | File: ../Navigation/NavigationMesh.h
    engine->RegisterObjectMethod("DynamicNavigationMesh", "void SetDetailSampleMaxError(float)", AS_METHODPR(DynamicNavigationMesh, SetDetailSampleMaxError, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DynamicNavigationMesh", "void set_detailSampleMaxError(float)", AS_METHODPR(DynamicNavigationMesh, SetDetailSampleMaxError, (float), void), AS_CALL_THISCALL);
    // void NavigationMesh::SetDrawNavAreas(bool enable) | File: ../Navigation/NavigationMesh.h
    engine->RegisterObjectMethod("DynamicNavigationMesh", "void SetDrawNavAreas(bool)", AS_METHODPR(DynamicNavigationMesh, SetDrawNavAreas, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DynamicNavigationMesh", "void set_drawNavAreas(bool)", AS_METHODPR(DynamicNavigationMesh, SetDrawNavAreas, (bool), void), AS_CALL_THISCALL);
    // void DynamicNavigationMesh::SetDrawObstacles(bool enable) | File: ../Navigation/DynamicNavigationMesh.h
    engine->RegisterObjectMethod("DynamicNavigationMesh", "void SetDrawObstacles(bool)", AS_METHODPR(DynamicNavigationMesh, SetDrawObstacles, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DynamicNavigationMesh", "void set_drawObstacles(bool)", AS_METHODPR(DynamicNavigationMesh, SetDrawObstacles, (bool), void), AS_CALL_THISCALL);
    // void NavigationMesh::SetDrawOffMeshConnections(bool enable) | File: ../Navigation/NavigationMesh.h
    engine->RegisterObjectMethod("DynamicNavigationMesh", "void SetDrawOffMeshConnections(bool)", AS_METHODPR(DynamicNavigationMesh, SetDrawOffMeshConnections, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DynamicNavigationMesh", "void set_drawOffMeshConnections(bool)", AS_METHODPR(DynamicNavigationMesh, SetDrawOffMeshConnections, (bool), void), AS_CALL_THISCALL);
    // void NavigationMesh::SetEdgeMaxError(float error) | File: ../Navigation/NavigationMesh.h
    engine->RegisterObjectMethod("DynamicNavigationMesh", "void SetEdgeMaxError(float)", AS_METHODPR(DynamicNavigationMesh, SetEdgeMaxError, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DynamicNavigationMesh", "void set_edgeMaxError(float)", AS_METHODPR(DynamicNavigationMesh, SetEdgeMaxError, (float), void), AS_CALL_THISCALL);
    // void NavigationMesh::SetEdgeMaxLength(float length) | File: ../Navigation/NavigationMesh.h
    engine->RegisterObjectMethod("DynamicNavigationMesh", "void SetEdgeMaxLength(float)", AS_METHODPR(DynamicNavigationMesh, SetEdgeMaxLength, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DynamicNavigationMesh", "void set_edgeMaxLength(float)", AS_METHODPR(DynamicNavigationMesh, SetEdgeMaxLength, (float), void), AS_CALL_THISCALL);
    // void Component::SetEnabled(bool enable) | File: ../Scene/Component.h
    engine->RegisterObjectMethod("DynamicNavigationMesh", "void SetEnabled(bool)", AS_METHODPR(DynamicNavigationMesh, SetEnabled, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DynamicNavigationMesh", "void set_enabled(bool)", AS_METHODPR(DynamicNavigationMesh, SetEnabled, (bool), void), AS_CALL_THISCALL);
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("DynamicNavigationMesh", "void SetGlobalVar(StringHash, const Variant&in)", AS_METHODPR(DynamicNavigationMesh, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DynamicNavigationMesh", "void set_globalVar(StringHash, const Variant&in)", AS_METHODPR(DynamicNavigationMesh, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    // void Serializable::SetInstanceDefault(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("DynamicNavigationMesh", "void SetInstanceDefault(bool)", AS_METHODPR(DynamicNavigationMesh, SetInstanceDefault, (bool), void), AS_CALL_THISCALL);
    // void Serializable::SetInterceptNetworkUpdate(const String& attributeName, bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("DynamicNavigationMesh", "void SetInterceptNetworkUpdate(const String&in, bool)", AS_METHODPR(DynamicNavigationMesh, SetInterceptNetworkUpdate, (const String&, bool), void), AS_CALL_THISCALL);
    // void DynamicNavigationMesh::SetMaxLayers(unsigned maxLayers) | File: ../Navigation/DynamicNavigationMesh.h
    engine->RegisterObjectMethod("DynamicNavigationMesh", "void SetMaxLayers(uint)", AS_METHODPR(DynamicNavigationMesh, SetMaxLayers, (unsigned), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DynamicNavigationMesh", "void set_maxLayers(uint)", AS_METHODPR(DynamicNavigationMesh, SetMaxLayers, (unsigned), void), AS_CALL_THISCALL);
    // void DynamicNavigationMesh::SetMaxObstacles(unsigned maxObstacles) | File: ../Navigation/DynamicNavigationMesh.h
    engine->RegisterObjectMethod("DynamicNavigationMesh", "void SetMaxObstacles(uint)", AS_METHODPR(DynamicNavigationMesh, SetMaxObstacles, (unsigned), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DynamicNavigationMesh", "void set_maxObstacles(uint)", AS_METHODPR(DynamicNavigationMesh, SetMaxObstacles, (unsigned), void), AS_CALL_THISCALL);
    // void NavigationMesh::SetMeshName(const String& newName) | File: ../Navigation/NavigationMesh.h
    engine->RegisterObjectMethod("DynamicNavigationMesh", "void SetMeshName(const String&in)", AS_METHODPR(DynamicNavigationMesh, SetMeshName, (const String&), void), AS_CALL_THISCALL);
    // void DynamicNavigationMesh::SetNavigationDataAttr(const PODVector<unsigned char>& value) override | File: ../Navigation/DynamicNavigationMesh.h
    // Error: type "const PODVector<unsigned char>&" can not automatically bind
    // void Animatable::SetObjectAnimation(ObjectAnimation* objectAnimation) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("DynamicNavigationMesh", "void SetObjectAnimation(ObjectAnimation@+)", AS_METHODPR(DynamicNavigationMesh, SetObjectAnimation, (ObjectAnimation*), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DynamicNavigationMesh", "void set_objectAnimation(ObjectAnimation@+)", AS_METHODPR(DynamicNavigationMesh, SetObjectAnimation, (ObjectAnimation*), void), AS_CALL_THISCALL);
    // void Animatable::SetObjectAnimationAttr(const ResourceRef& value) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("DynamicNavigationMesh", "void SetObjectAnimationAttr(const ResourceRef&in)", AS_METHODPR(DynamicNavigationMesh, SetObjectAnimationAttr, (const ResourceRef&), void), AS_CALL_THISCALL);
    // void NavigationMesh::SetPadding(const Vector3& padding) | File: ../Navigation/NavigationMesh.h
    engine->RegisterObjectMethod("DynamicNavigationMesh", "void SetPadding(const Vector3&in)", AS_METHODPR(DynamicNavigationMesh, SetPadding, (const Vector3&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DynamicNavigationMesh", "void set_padding(const Vector3&in)", AS_METHODPR(DynamicNavigationMesh, SetPadding, (const Vector3&), void), AS_CALL_THISCALL);
    // void NavigationMesh::SetPartitionType(NavmeshPartitionType partitionType) | File: ../Navigation/NavigationMesh.h
    engine->RegisterObjectMethod("DynamicNavigationMesh", "void SetPartitionType(NavmeshPartitionType)", AS_METHODPR(DynamicNavigationMesh, SetPartitionType, (NavmeshPartitionType), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DynamicNavigationMesh", "void set_partitionType(NavmeshPartitionType)", AS_METHODPR(DynamicNavigationMesh, SetPartitionType, (NavmeshPartitionType), void), AS_CALL_THISCALL);
    // void NavigationMesh::SetRegionMergeSize(float size) | File: ../Navigation/NavigationMesh.h
    engine->RegisterObjectMethod("DynamicNavigationMesh", "void SetRegionMergeSize(float)", AS_METHODPR(DynamicNavigationMesh, SetRegionMergeSize, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DynamicNavigationMesh", "void set_regionMergeSize(float)", AS_METHODPR(DynamicNavigationMesh, SetRegionMergeSize, (float), void), AS_CALL_THISCALL);
    // void NavigationMesh::SetRegionMinSize(float size) | File: ../Navigation/NavigationMesh.h
    engine->RegisterObjectMethod("DynamicNavigationMesh", "void SetRegionMinSize(float)", AS_METHODPR(DynamicNavigationMesh, SetRegionMinSize, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DynamicNavigationMesh", "void set_regionMinSize(float)", AS_METHODPR(DynamicNavigationMesh, SetRegionMinSize, (float), void), AS_CALL_THISCALL);
    // void Serializable::SetTemporary(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("DynamicNavigationMesh", "void SetTemporary(bool)", AS_METHODPR(DynamicNavigationMesh, SetTemporary, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DynamicNavigationMesh", "void set_temporary(bool)", AS_METHODPR(DynamicNavigationMesh, SetTemporary, (bool), void), AS_CALL_THISCALL);
    // void NavigationMesh::SetTileSize(int size) | File: ../Navigation/NavigationMesh.h
    engine->RegisterObjectMethod("DynamicNavigationMesh", "void SetTileSize(int)", AS_METHODPR(DynamicNavigationMesh, SetTileSize, (int), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DynamicNavigationMesh", "void set_tileSize(int)", AS_METHODPR(DynamicNavigationMesh, SetTileSize, (int), void), AS_CALL_THISCALL);
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod("DynamicNavigationMesh", "void UnsubscribeFromAllEvents()", AS_METHODPR(DynamicNavigationMesh, UnsubscribeFromAllEvents, (), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("DynamicNavigationMesh", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", AS_FUNCTION_OBJFIRST(DynamicNavigationMesh_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), AS_CALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("DynamicNavigationMesh", "void UnsubscribeFromEvent(StringHash)", AS_METHODPR(DynamicNavigationMesh, UnsubscribeFromEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("DynamicNavigationMesh", "void UnsubscribeFromEvent(Object@+, StringHash)", AS_METHODPR(DynamicNavigationMesh, UnsubscribeFromEvent, (Object*, StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("DynamicNavigationMesh", "void UnsubscribeFromEvents(Object@+)", AS_METHODPR(DynamicNavigationMesh, UnsubscribeFromEvents, (Object*), void), AS_CALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("DynamicNavigationMesh", "int WeakRefs() const", AS_METHODPR(DynamicNavigationMesh, WeakRefs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DynamicNavigationMesh", "int get_weakRefs() const", AS_METHODPR(DynamicNavigationMesh, WeakRefs, () const, int), AS_CALL_THISCALL);
    // void Serializable::WriteDeltaUpdate(Serializer& dest, const DirtyBits& attributeBits, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("DynamicNavigationMesh", "void WriteDeltaUpdate(Serializer&, const DirtyBits&in, uint8)", AS_METHODPR(DynamicNavigationMesh, WriteDeltaUpdate, (Serializer&, const DirtyBits&, unsigned char), void), AS_CALL_THISCALL);
    // void Serializable::WriteInitialDeltaUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("DynamicNavigationMesh", "void WriteInitialDeltaUpdate(Serializer&, uint8)", AS_METHODPR(DynamicNavigationMesh, WriteInitialDeltaUpdate, (Serializer&, unsigned char), void), AS_CALL_THISCALL);
    // void Serializable::WriteLatestDataUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("DynamicNavigationMesh", "void WriteLatestDataUpdate(Serializer&, uint8)", AS_METHODPR(DynamicNavigationMesh, WriteLatestDataUpdate, (Serializer&, unsigned char), void), AS_CALL_THISCALL);
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
    engine->RegisterObjectBehaviour("DebugLine", asBEHAVE_CONSTRUCT, "void f(const Vector3&in, const Vector3&in, uint)", AS_FUNCTION_OBJFIRST(DebugLine_DebugLine_Vector3_Vector3_unsigned), AS_CALL_CDECL_OBJFIRST);
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
    engine->RegisterObjectBehaviour("DebugTriangle", asBEHAVE_CONSTRUCT, "void f(const Vector3&in, const Vector3&in, const Vector3&in, uint)", AS_FUNCTION_OBJFIRST(DebugTriangle_DebugTriangle_Vector3_Vector3_Vector3_unsigned), AS_CALL_CDECL_OBJFIRST);
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
    engine->RegisterObjectMethod("Decal", "void AddVertex(const DecalVertex&in)", AS_METHODPR(Decal, AddVertex, (const DecalVertex&), void), AS_CALL_THISCALL);
    // void Decal::CalculateBoundingBox() | File: ../Graphics/DecalSet.h
    engine->RegisterObjectMethod("Decal", "void CalculateBoundingBox()", AS_METHODPR(Decal, CalculateBoundingBox, (), void), AS_CALL_THISCALL);
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
    engine->RegisterObjectBehaviour("DecalVertex", asBEHAVE_CONSTRUCT, "void f(const Vector3&in, const Vector3&in)", AS_FUNCTION_OBJFIRST(DecalVertex_DecalVertex_Vector3_Vector3), AS_CALL_CDECL_OBJFIRST);
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
    engine->RegisterObjectMethod("DirtyBits", "void Clear(uint)", AS_METHODPR(DirtyBits, Clear, (unsigned), void), AS_CALL_THISCALL);
    // void DirtyBits::ClearAll() | File: ../Scene/ReplicationState.h
    engine->RegisterObjectMethod("DirtyBits", "void ClearAll()", AS_METHODPR(DirtyBits, ClearAll, (), void), AS_CALL_THISCALL);
    // unsigned DirtyBits::Count() const | File: ../Scene/ReplicationState.h
    engine->RegisterObjectMethod("DirtyBits", "uint Count() const", AS_METHODPR(DirtyBits, Count, () const, unsigned), AS_CALL_THISCALL);
    // DirtyBits::DirtyBits(const DirtyBits& bits) | File: ../Scene/ReplicationState.h
    engine->RegisterObjectBehaviour("DirtyBits", asBEHAVE_CONSTRUCT, "void f(const DirtyBits&in)", AS_FUNCTION_OBJFIRST(DirtyBits_DirtyBits_DirtyBits), AS_CALL_CDECL_OBJFIRST);
    // bool DirtyBits::IsSet(unsigned index) const | File: ../Scene/ReplicationState.h
    engine->RegisterObjectMethod("DirtyBits", "bool IsSet(uint) const", AS_METHODPR(DirtyBits, IsSet, (unsigned) const, bool), AS_CALL_THISCALL);
    // void DirtyBits::Set(unsigned index) | File: ../Scene/ReplicationState.h
    engine->RegisterObjectMethod("DirtyBits", "void Set(uint)", AS_METHODPR(DirtyBits, Set, (unsigned), void), AS_CALL_THISCALL);
    // DirtyBits& DirtyBits::operator=(const DirtyBits&) | Possible implicitly-declared
    RegisterImplicitlyDeclaredAssignOperatorIfPossible<DirtyBits>(engine, "DirtyBits");
#ifdef REGISTER_MANUAL_PART_DirtyBits
    REGISTER_MANUAL_PART_DirtyBits(DirtyBits, "DirtyBits")
#endif

}

}
