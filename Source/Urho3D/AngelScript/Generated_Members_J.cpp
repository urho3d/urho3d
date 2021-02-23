// DO NOT EDIT. This file is generated

#include "../Precompiled.h"
#include "../AngelScript/APITemplates.h"

#include "../AngelScript/GeneratedIncludes.h"
#include "../AngelScript/Manual.h"

namespace Urho3D
{

void FakeAddRef(void* ptr);
void FakeReleaseRef(void* ptr);

// explicit JSONFile::JSONFile(Context* context) | File: ../Resource/JSONFile.h
static JSONFile* JSONFile_JSONFile_Context()
{
    return new JSONFile(GetScriptContext());
}

// void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
static void JSONFile_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool(JSONFile* ptr, CScriptArray* exceptions_conv, bool onlyUserData)
{
    PODVector<StringHash> exceptions = ArrayToPODVector<StringHash>(exceptions_conv);
    ptr->UnsubscribeFromAllEventsExcept(exceptions, onlyUserData);
}

// JSONValue::JSONValue(bool value) | File: ../Resource/JSONValue.h
static void JSONValue_JSONValue_bool(JSONValue* ptr, bool value)
{
    new(ptr) JSONValue(value);
}

// JSONValue::JSONValue(int value) | File: ../Resource/JSONValue.h
static void JSONValue_JSONValue_int(JSONValue* ptr, int value)
{
    new(ptr) JSONValue(value);
}

// JSONValue::JSONValue(unsigned value) | File: ../Resource/JSONValue.h
static void JSONValue_JSONValue_unsigned(JSONValue* ptr, unsigned value)
{
    new(ptr) JSONValue(value);
}

// JSONValue::JSONValue(float value) | File: ../Resource/JSONValue.h
static void JSONValue_JSONValue_float(JSONValue* ptr, float value)
{
    new(ptr) JSONValue(value);
}

// JSONValue::JSONValue(double value) | File: ../Resource/JSONValue.h
static void JSONValue_JSONValue_double(JSONValue* ptr, double value)
{
    new(ptr) JSONValue(value);
}

// JSONValue::JSONValue(const String& value) | File: ../Resource/JSONValue.h
static void JSONValue_JSONValue_String(JSONValue* ptr, const String &value)
{
    new(ptr) JSONValue(value);
}

// JSONValue::JSONValue(const JSONValue& value) | File: ../Resource/JSONValue.h
static void JSONValue_JSONValue_JSONValue(JSONValue* ptr, const JSONValue &value)
{
    new(ptr) JSONValue(value);
}

// void JSONValue::SetVariant(const Variant& variant, Context* context=nullptr) | File: ../Resource/JSONValue.h
static void JSONValue_SetVariant_Variant_Context(JSONValue* ptr, const Variant& variant)
{
    Context* context = GetScriptContext();
    ptr->SetVariant(variant, context);
}

// void JSONValue::SetVariantMap(const VariantMap& variantMap, Context* context=nullptr) | File: ../Resource/JSONValue.h
static void JSONValue_SetVariantMap_VariantMap_Context(JSONValue* ptr, const VariantMap& variantMap)
{
    Context* context = GetScriptContext();
    ptr->SetVariantMap(variantMap, context);
}

// void JSONValue::SetVariantValue(const Variant& variant, Context* context=nullptr) | File: ../Resource/JSONValue.h
static void JSONValue_SetVariantValue_Variant_Context(JSONValue* ptr, const Variant& variant)
{
    Context* context = GetScriptContext();
    ptr->SetVariantValue(variant, context);
}

void ASRegisterGenerated_Members_J(asIScriptEngine* engine)
{
    // void RefCounted::AddRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("JSONFile", asBEHAVE_ADDREF, "void f()", AS_METHODPR(JSONFile, AddRef, (), void), AS_CALL_THISCALL);
    // bool JSONFile::BeginLoad(Deserializer& source) override | File: ../Resource/JSONFile.h
    engine->RegisterObjectMethod("JSONFile", "bool BeginLoad(Deserializer&)", AS_METHODPR(JSONFile, BeginLoad, (Deserializer&), bool), AS_CALL_THISCALL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // virtual bool Resource::EndLoad() | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("JSONFile", "bool EndLoad()", AS_METHODPR(JSONFile, EndLoad, (), bool), AS_CALL_THISCALL);
    // bool JSONFile::FromString(const String& source) | File: ../Resource/JSONFile.h
    engine->RegisterObjectMethod("JSONFile", "bool FromString(const String&in)", AS_METHODPR(JSONFile, FromString, (const String&), bool), AS_CALL_THISCALL);
    // AsyncLoadState Resource::GetAsyncLoadState() const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("JSONFile", "AsyncLoadState GetAsyncLoadState() const", AS_METHODPR(JSONFile, GetAsyncLoadState, () const, AsyncLoadState), AS_CALL_THISCALL);
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("JSONFile", "bool GetBlockEvents() const", AS_METHODPR(JSONFile, GetBlockEvents, () const, bool), AS_CALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("JSONFile", "const String& GetCategory() const", AS_METHODPR(JSONFile, GetCategory, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("JSONFile", "const String& get_category() const", AS_METHODPR(JSONFile, GetCategory, () const, const String&), AS_CALL_THISCALL);
    // Context* Object::GetContext() const | File: ../Core/Object.h
    // Error: type "Context*" can used only as function parameter
    // VariantMap& Object::GetEventDataMap() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("JSONFile", "VariantMap& GetEventDataMap() const", AS_METHODPR(JSONFile, GetEventDataMap, () const, VariantMap&), AS_CALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("JSONFile", "Object@+ GetEventSender() const", AS_METHODPR(JSONFile, GetEventSender, () const, Object*), AS_CALL_THISCALL);
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("JSONFile", "const Variant& GetGlobalVar(StringHash) const", AS_METHODPR(JSONFile, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("JSONFile", "const Variant& get_globalVar(StringHash) const", AS_METHODPR(JSONFile, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("JSONFile", "const VariantMap& GetGlobalVars() const", AS_METHODPR(JSONFile, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("JSONFile", "const VariantMap& get_globalVars() const", AS_METHODPR(JSONFile, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    // unsigned Resource::GetMemoryUse() const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("JSONFile", "uint GetMemoryUse() const", AS_METHODPR(JSONFile, GetMemoryUse, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("JSONFile", "uint get_memoryUse() const", AS_METHODPR(JSONFile, GetMemoryUse, () const, unsigned), AS_CALL_THISCALL);
    // const String& Resource::GetName() const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("JSONFile", "const String& GetName() const", AS_METHODPR(JSONFile, GetName, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("JSONFile", "const String& get_name() const", AS_METHODPR(JSONFile, GetName, () const, const String&), AS_CALL_THISCALL);
    // StringHash Resource::GetNameHash() const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("JSONFile", "StringHash GetNameHash() const", AS_METHODPR(JSONFile, GetNameHash, () const, StringHash), AS_CALL_THISCALL);
    // JSONValue& JSONFile::GetRoot() | File: ../Resource/JSONFile.h
    engine->RegisterObjectMethod("JSONFile", "JSONValue& GetRoot()", AS_METHODPR(JSONFile, GetRoot, (), JSONValue&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("JSONFile", "JSONValue& get_root()", AS_METHODPR(JSONFile, GetRoot, (), JSONValue&), AS_CALL_THISCALL);
    // const JSONValue& JSONFile::GetRoot() const | File: ../Resource/JSONFile.h
    engine->RegisterObjectMethod("JSONFile", "const JSONValue& GetRoot() const", AS_METHODPR(JSONFile, GetRoot, () const, const JSONValue&), AS_CALL_THISCALL);
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("JSONFile", "Object@+ GetSubsystem(StringHash) const", AS_METHODPR(JSONFile, GetSubsystem, (StringHash) const, Object*), AS_CALL_THISCALL);
    // template<class T> T* Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("JSONFile", "StringHash GetType() const", AS_METHODPR(JSONFile, GetType, () const, StringHash), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("JSONFile", "StringHash get_type() const", AS_METHODPR(JSONFile, GetType, () const, StringHash), AS_CALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("JSONFile", "const String& GetTypeName() const", AS_METHODPR(JSONFile, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("JSONFile", "const String& get_typeName() const", AS_METHODPR(JSONFile, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    // unsigned Resource::GetUseTimer() | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("JSONFile", "uint GetUseTimer()", AS_METHODPR(JSONFile, GetUseTimer, (), unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("JSONFile", "uint get_useTimer()", AS_METHODPR(JSONFile, GetUseTimer, (), unsigned), AS_CALL_THISCALL);
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("JSONFile", "bool HasEventHandlers() const", AS_METHODPR(JSONFile, HasEventHandlers, () const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("JSONFile", "bool HasSubscribedToEvent(StringHash) const", AS_METHODPR(JSONFile, HasSubscribedToEvent, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("JSONFile", "bool HasSubscribedToEvent(Object@+, StringHash) const", AS_METHODPR(JSONFile, HasSubscribedToEvent, (Object*, StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("JSONFile", "bool IsInstanceOf(StringHash) const", AS_METHODPR(JSONFile, IsInstanceOf, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // explicit JSONFile::JSONFile(Context* context) | File: ../Resource/JSONFile.h
    engine->RegisterObjectBehaviour("JSONFile", asBEHAVE_FACTORY, "JSONFile@+ f()", AS_FUNCTION(JSONFile_JSONFile_Context), AS_CALL_CDECL);
    // bool Resource::Load(Deserializer& source) | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("JSONFile", "bool Load(Deserializer&)", AS_METHODPR(JSONFile, Load, (Deserializer&), bool), AS_CALL_THISCALL);
    // bool Resource::LoadFile(const String& fileName) | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("JSONFile", "bool LoadFile(const String&in)", AS_METHODPR(JSONFile, LoadFile, (const String&), bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("JSONFile", "bool Load(const String&in)", AS_METHODPR(JSONFile, LoadFile, (const String&), bool), AS_CALL_THISCALL);
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("JSONFile", "void OnEvent(Object@+, StringHash, VariantMap&)", AS_METHODPR(JSONFile, OnEvent, (Object*, StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("JSONFile", "int Refs() const", AS_METHODPR(JSONFile, Refs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("JSONFile", "int get_refs() const", AS_METHODPR(JSONFile, Refs, () const, int), AS_CALL_THISCALL);
    // static void JSONFile::RegisterObject(Context* context) | File: ../Resource/JSONFile.h
    // Not registered because have @nobind mark
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("JSONFile", asBEHAVE_RELEASE, "void f()", AS_METHODPR(JSONFile, ReleaseRef, (), void), AS_CALL_THISCALL);
    // void Resource::ResetUseTimer() | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("JSONFile", "void ResetUseTimer()", AS_METHODPR(JSONFile, ResetUseTimer, (), void), AS_CALL_THISCALL);
    // bool JSONFile::Save(Serializer& dest) const override | File: ../Resource/JSONFile.h
    engine->RegisterObjectMethod("JSONFile", "bool Save(Serializer&) const", AS_METHODPR(JSONFile, Save, (Serializer&) const, bool), AS_CALL_THISCALL);
    // bool JSONFile::Save(Serializer& dest, const String& indendation) const | File: ../Resource/JSONFile.h
    engine->RegisterObjectMethod("JSONFile", "bool Save(Serializer&, const String&in) const", AS_METHODPR(JSONFile, Save, (Serializer&, const String&) const, bool), AS_CALL_THISCALL);
    // virtual bool Resource::SaveFile(const String& fileName) const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("JSONFile", "bool SaveFile(const String&in) const", AS_METHODPR(JSONFile, SaveFile, (const String&) const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("JSONFile", "bool Save(const String&in) const", AS_METHODPR(JSONFile, SaveFile, (const String&) const, bool), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("JSONFile", "void SendEvent(StringHash)", AS_METHODPR(JSONFile, SendEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("JSONFile", "void SendEvent(StringHash, VariantMap&)", AS_METHODPR(JSONFile, SendEvent, (StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void Resource::SetAsyncLoadState(AsyncLoadState newState) | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("JSONFile", "void SetAsyncLoadState(AsyncLoadState)", AS_METHODPR(JSONFile, SetAsyncLoadState, (AsyncLoadState), void), AS_CALL_THISCALL);
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("JSONFile", "void SetBlockEvents(bool)", AS_METHODPR(JSONFile, SetBlockEvents, (bool), void), AS_CALL_THISCALL);
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("JSONFile", "void SetGlobalVar(StringHash, const Variant&in)", AS_METHODPR(JSONFile, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("JSONFile", "void set_globalVar(StringHash, const Variant&in)", AS_METHODPR(JSONFile, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    // void Resource::SetMemoryUse(unsigned size) | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("JSONFile", "void SetMemoryUse(uint)", AS_METHODPR(JSONFile, SetMemoryUse, (unsigned), void), AS_CALL_THISCALL);
    // void Resource::SetName(const String& name) | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("JSONFile", "void SetName(const String&in)", AS_METHODPR(JSONFile, SetName, (const String&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("JSONFile", "void set_name(const String&in)", AS_METHODPR(JSONFile, SetName, (const String&), void), AS_CALL_THISCALL);
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // String JSONFile::ToString(const String& indendation="\t") const | File: ../Resource/JSONFile.h
    engine->RegisterObjectMethod("JSONFile", "String ToString(const String&in = \"\t\") const", AS_METHODPR(JSONFile, ToString, (const String&) const, String), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod("JSONFile", "void UnsubscribeFromAllEvents()", AS_METHODPR(JSONFile, UnsubscribeFromAllEvents, (), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("JSONFile", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", AS_FUNCTION_OBJFIRST(JSONFile_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), AS_CALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("JSONFile", "void UnsubscribeFromEvent(StringHash)", AS_METHODPR(JSONFile, UnsubscribeFromEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("JSONFile", "void UnsubscribeFromEvent(Object@+, StringHash)", AS_METHODPR(JSONFile, UnsubscribeFromEvent, (Object*, StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("JSONFile", "void UnsubscribeFromEvents(Object@+)", AS_METHODPR(JSONFile, UnsubscribeFromEvents, (Object*), void), AS_CALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("JSONFile", "int WeakRefs() const", AS_METHODPR(JSONFile, WeakRefs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("JSONFile", "int get_weakRefs() const", AS_METHODPR(JSONFile, WeakRefs, () const, int), AS_CALL_THISCALL);
#ifdef REGISTER_MANUAL_PART_Resource
    REGISTER_MANUAL_PART_Resource(JSONFile, "JSONFile")
#endif
#ifdef REGISTER_MANUAL_PART_Object
    REGISTER_MANUAL_PART_Object(JSONFile, "JSONFile")
#endif
#ifdef REGISTER_MANUAL_PART_RefCounted
    REGISTER_MANUAL_PART_RefCounted(JSONFile, "JSONFile")
#endif
#ifdef REGISTER_MANUAL_PART_JSONFile
    REGISTER_MANUAL_PART_JSONFile(JSONFile, "JSONFile")
#endif
    RegisterSubclass<Resource, JSONFile>(engine, "Resource", "JSONFile");
    RegisterSubclass<Object, JSONFile>(engine, "Object", "JSONFile");
    RegisterSubclass<RefCounted, JSONFile>(engine, "RefCounted", "JSONFile");

    // JSONArray* JSONValue::arrayValue_ | File: ../Resource/JSONValue.h
    // Not registered because have @nobind mark
    // bool JSONValue::boolValue_ | File: ../Resource/JSONValue.h
    // Not registered because have @nobind mark
    // const JSONValue JSONValue::EMPTY | File: ../Resource/JSONValue.h
    engine->SetDefaultNamespace("JSONValue");
    engine->RegisterGlobalProperty("const JSONValue EMPTY", (void*)&JSONValue::EMPTY);
    engine->SetDefaultNamespace("");
    // const JSONArray JSONValue::emptyArray | File: ../Resource/JSONValue.h
    // Error: type "const JSONArray" can not automatically bind
    // const JSONObject JSONValue::emptyObject | File: ../Resource/JSONValue.h
    // Error: type "const JSONObject" can not automatically bind
    // double JSONValue::numberValue_ | File: ../Resource/JSONValue.h
    // Not registered because have @nobind mark
    // JSONObject* JSONValue::objectValue_ | File: ../Resource/JSONValue.h
    // Not registered because have @nobind mark
    // String* JSONValue::stringValue_ | File: ../Resource/JSONValue.h
    // Not registered because have @nobind mark
    // JSONObjectIterator JSONValue::Begin() | File: ../Resource/JSONValue.h
    // Error: type "JSONObjectIterator" can not automatically bind
    // ConstJSONObjectIterator JSONValue::Begin() const | File: ../Resource/JSONValue.h
    // Error: type "ConstJSONObjectIterator" can not automatically bind
    // void JSONValue::Clear() | File: ../Resource/JSONValue.h
    engine->RegisterObjectMethod("JSONValue", "void Clear()", AS_METHODPR(JSONValue, Clear, (), void), AS_CALL_THISCALL);
    // bool JSONValue::Contains(const String& key) const | File: ../Resource/JSONValue.h
    engine->RegisterObjectMethod("JSONValue", "bool Contains(const String&in) const", AS_METHODPR(JSONValue, Contains, (const String&) const, bool), AS_CALL_THISCALL);
    // JSONObjectIterator JSONValue::End() | File: ../Resource/JSONValue.h
    // Error: type "JSONObjectIterator" can not automatically bind
    // ConstJSONObjectIterator JSONValue::End() const | File: ../Resource/JSONValue.h
    // Error: type "ConstJSONObjectIterator" can not automatically bind
    // void JSONValue::Erase(unsigned pos, unsigned length=1) | File: ../Resource/JSONValue.h
    engine->RegisterObjectMethod("JSONValue", "void Erase(uint, uint = 1)", AS_METHODPR(JSONValue, Erase, (unsigned, unsigned), void), AS_CALL_THISCALL);
    // bool JSONValue::Erase(const String& key) | File: ../Resource/JSONValue.h
    engine->RegisterObjectMethod("JSONValue", "bool Erase(const String&in)", AS_METHODPR(JSONValue, Erase, (const String&), bool), AS_CALL_THISCALL);
    // const JSONValue& JSONValue::Get(const String& key) const | File: ../Resource/JSONValue.h
    engine->RegisterObjectMethod("JSONValue", "const JSONValue& Get(const String&in) const", AS_METHODPR(JSONValue, Get, (const String&) const, const JSONValue&), AS_CALL_THISCALL);
    // const JSONArray& JSONValue::GetArray() const | File: ../Resource/JSONValue.h
    // Error: type "const JSONArray&" can not automatically bind
    // bool JSONValue::GetBool(bool defaultValue=false) const | File: ../Resource/JSONValue.h
    engine->RegisterObjectMethod("JSONValue", "bool GetBool(bool = false) const", AS_METHODPR(JSONValue, GetBool, (bool) const, bool), AS_CALL_THISCALL);
    // const char* JSONValue::GetCString(const char* defaultValue="") const | File: ../Resource/JSONValue.h
    // Error: type "const char*" can not automatically bind
    // double JSONValue::GetDouble(double defaultValue=0.0) const | File: ../Resource/JSONValue.h
    engine->RegisterObjectMethod("JSONValue", "double GetDouble(double = 0.0) const", AS_METHODPR(JSONValue, GetDouble, (double) const, double), AS_CALL_THISCALL);
    // float JSONValue::GetFloat(float defaultValue=0.0f) const | File: ../Resource/JSONValue.h
    engine->RegisterObjectMethod("JSONValue", "float GetFloat(float = 0.0f) const", AS_METHODPR(JSONValue, GetFloat, (float) const, float), AS_CALL_THISCALL);
    // int JSONValue::GetInt(int defaultValue=0) const | File: ../Resource/JSONValue.h
    engine->RegisterObjectMethod("JSONValue", "int GetInt(int = 0) const", AS_METHODPR(JSONValue, GetInt, (int) const, int), AS_CALL_THISCALL);
    // JSONNumberType JSONValue::GetNumberType() const | File: ../Resource/JSONValue.h
    engine->RegisterObjectMethod("JSONValue", "JSONNumberType GetNumberType() const", AS_METHODPR(JSONValue, GetNumberType, () const, JSONNumberType), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("JSONValue", "JSONNumberType get_numberType() const", AS_METHODPR(JSONValue, GetNumberType, () const, JSONNumberType), AS_CALL_THISCALL);
    // static JSONNumberType JSONValue::GetNumberTypeFromName(const String& typeName) | File: ../Resource/JSONValue.h
    engine->SetDefaultNamespace("JSONValue");
    engine->RegisterGlobalFunction("JSONNumberType GetNumberTypeFromName(const String&in)", AS_FUNCTIONPR(JSONValue::GetNumberTypeFromName, (const String&), JSONNumberType), AS_CALL_CDECL);
    engine->SetDefaultNamespace("");
    // static JSONNumberType JSONValue::GetNumberTypeFromName(const char* typeName) | File: ../Resource/JSONValue.h
    // Error: type "const char*" can not automatically bind
    // String JSONValue::GetNumberTypeName() const | File: ../Resource/JSONValue.h
    engine->RegisterObjectMethod("JSONValue", "String GetNumberTypeName() const", AS_METHODPR(JSONValue, GetNumberTypeName, () const, String), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("JSONValue", "String get_numberTypeName() const", AS_METHODPR(JSONValue, GetNumberTypeName, () const, String), AS_CALL_THISCALL);
    // static String JSONValue::GetNumberTypeName(JSONNumberType type) | File: ../Resource/JSONValue.h
    engine->SetDefaultNamespace("JSONValue");
    engine->RegisterGlobalFunction("String GetNumberTypeName(JSONNumberType)", AS_FUNCTIONPR(JSONValue::GetNumberTypeName, (JSONNumberType), String), AS_CALL_CDECL);
    engine->SetDefaultNamespace("");
    // const JSONObject& JSONValue::GetObject() const | File: ../Resource/JSONValue.h
    // Error: type "const JSONObject&" can not automatically bind
    // const String& JSONValue::GetString(const String& defaultValue=String::EMPTY) const | File: ../Resource/JSONValue.h
    engine->RegisterObjectMethod("JSONValue", "const String& GetString(const String&in = String::EMPTY) const", AS_METHODPR(JSONValue, GetString, (const String&) const, const String&), AS_CALL_THISCALL);
    // unsigned JSONValue::GetUInt(unsigned defaultValue=0) const | File: ../Resource/JSONValue.h
    engine->RegisterObjectMethod("JSONValue", "uint GetUInt(uint = 0) const", AS_METHODPR(JSONValue, GetUInt, (unsigned) const, unsigned), AS_CALL_THISCALL);
    // JSONValueType JSONValue::GetValueType() const | File: ../Resource/JSONValue.h
    engine->RegisterObjectMethod("JSONValue", "JSONValueType GetValueType() const", AS_METHODPR(JSONValue, GetValueType, () const, JSONValueType), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("JSONValue", "JSONValueType get_valueType() const", AS_METHODPR(JSONValue, GetValueType, () const, JSONValueType), AS_CALL_THISCALL);
    // static JSONValueType JSONValue::GetValueTypeFromName(const String& typeName) | File: ../Resource/JSONValue.h
    engine->SetDefaultNamespace("JSONValue");
    engine->RegisterGlobalFunction("JSONValueType GetValueTypeFromName(const String&in)", AS_FUNCTIONPR(JSONValue::GetValueTypeFromName, (const String&), JSONValueType), AS_CALL_CDECL);
    engine->SetDefaultNamespace("");
    // static JSONValueType JSONValue::GetValueTypeFromName(const char* typeName) | File: ../Resource/JSONValue.h
    // Error: type "const char*" can not automatically bind
    // String JSONValue::GetValueTypeName() const | File: ../Resource/JSONValue.h
    engine->RegisterObjectMethod("JSONValue", "String GetValueTypeName() const", AS_METHODPR(JSONValue, GetValueTypeName, () const, String), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("JSONValue", "String get_valueTypeName() const", AS_METHODPR(JSONValue, GetValueTypeName, () const, String), AS_CALL_THISCALL);
    // static String JSONValue::GetValueTypeName(JSONValueType type) | File: ../Resource/JSONValue.h
    engine->SetDefaultNamespace("JSONValue");
    engine->RegisterGlobalFunction("String GetValueTypeName(JSONValueType)", AS_FUNCTIONPR(JSONValue::GetValueTypeName, (JSONValueType), String), AS_CALL_CDECL);
    engine->SetDefaultNamespace("");
    // Variant JSONValue::GetVariant() const | File: ../Resource/JSONValue.h
    engine->RegisterObjectMethod("JSONValue", "Variant GetVariant() const", AS_METHODPR(JSONValue, GetVariant, () const, Variant), AS_CALL_THISCALL);
    // VariantMap JSONValue::GetVariantMap() const | File: ../Resource/JSONValue.h
    engine->RegisterObjectMethod("JSONValue", "VariantMap GetVariantMap() const", AS_METHODPR(JSONValue, GetVariantMap, () const, VariantMap), AS_CALL_THISCALL);
    // Variant JSONValue::GetVariantValue(VariantType type) const | File: ../Resource/JSONValue.h
    engine->RegisterObjectMethod("JSONValue", "Variant GetVariantValue(VariantType) const", AS_METHODPR(JSONValue, GetVariantValue, (VariantType) const, Variant), AS_CALL_THISCALL);
    // VariantVector JSONValue::GetVariantVector() const | File: ../Resource/JSONValue.h
    // Error: type "VariantVector" can not automatically bind
    // void JSONValue::Insert(unsigned pos, const JSONValue& value) | File: ../Resource/JSONValue.h
    engine->RegisterObjectMethod("JSONValue", "void Insert(uint, const JSONValue&in)", AS_METHODPR(JSONValue, Insert, (unsigned, const JSONValue&), void), AS_CALL_THISCALL);
    // bool JSONValue::IsArray() const | File: ../Resource/JSONValue.h
    engine->RegisterObjectMethod("JSONValue", "bool IsArray() const", AS_METHODPR(JSONValue, IsArray, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("JSONValue", "bool get_isArray() const", AS_METHODPR(JSONValue, IsArray, () const, bool), AS_CALL_THISCALL);
    // bool JSONValue::IsBool() const | File: ../Resource/JSONValue.h
    engine->RegisterObjectMethod("JSONValue", "bool IsBool() const", AS_METHODPR(JSONValue, IsBool, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("JSONValue", "bool get_isBool() const", AS_METHODPR(JSONValue, IsBool, () const, bool), AS_CALL_THISCALL);
    // bool JSONValue::IsNull() const | File: ../Resource/JSONValue.h
    engine->RegisterObjectMethod("JSONValue", "bool IsNull() const", AS_METHODPR(JSONValue, IsNull, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("JSONValue", "bool get_isNull() const", AS_METHODPR(JSONValue, IsNull, () const, bool), AS_CALL_THISCALL);
    // bool JSONValue::IsNumber() const | File: ../Resource/JSONValue.h
    engine->RegisterObjectMethod("JSONValue", "bool IsNumber() const", AS_METHODPR(JSONValue, IsNumber, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("JSONValue", "bool get_isNumber() const", AS_METHODPR(JSONValue, IsNumber, () const, bool), AS_CALL_THISCALL);
    // bool JSONValue::IsObject() const | File: ../Resource/JSONValue.h
    engine->RegisterObjectMethod("JSONValue", "bool IsObject() const", AS_METHODPR(JSONValue, IsObject, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("JSONValue", "bool get_isObject() const", AS_METHODPR(JSONValue, IsObject, () const, bool), AS_CALL_THISCALL);
    // bool JSONValue::IsString() const | File: ../Resource/JSONValue.h
    engine->RegisterObjectMethod("JSONValue", "bool IsString() const", AS_METHODPR(JSONValue, IsString, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("JSONValue", "bool get_isString() const", AS_METHODPR(JSONValue, IsString, () const, bool), AS_CALL_THISCALL);
    // JSONValue::JSONValue(bool value) | File: ../Resource/JSONValue.h
    engine->RegisterObjectBehaviour("JSONValue", asBEHAVE_CONSTRUCT, "void f(bool)", AS_FUNCTION_OBJFIRST(JSONValue_JSONValue_bool), AS_CALL_CDECL_OBJFIRST);
    // JSONValue::JSONValue(int value) | File: ../Resource/JSONValue.h
    engine->RegisterObjectBehaviour("JSONValue", asBEHAVE_CONSTRUCT, "void f(int)", AS_FUNCTION_OBJFIRST(JSONValue_JSONValue_int), AS_CALL_CDECL_OBJFIRST);
    // JSONValue::JSONValue(unsigned value) | File: ../Resource/JSONValue.h
    engine->RegisterObjectBehaviour("JSONValue", asBEHAVE_CONSTRUCT, "void f(uint)", AS_FUNCTION_OBJFIRST(JSONValue_JSONValue_unsigned), AS_CALL_CDECL_OBJFIRST);
    // JSONValue::JSONValue(float value) | File: ../Resource/JSONValue.h
    engine->RegisterObjectBehaviour("JSONValue", asBEHAVE_CONSTRUCT, "void f(float)", AS_FUNCTION_OBJFIRST(JSONValue_JSONValue_float), AS_CALL_CDECL_OBJFIRST);
    // JSONValue::JSONValue(double value) | File: ../Resource/JSONValue.h
    engine->RegisterObjectBehaviour("JSONValue", asBEHAVE_CONSTRUCT, "void f(double)", AS_FUNCTION_OBJFIRST(JSONValue_JSONValue_double), AS_CALL_CDECL_OBJFIRST);
    // JSONValue::JSONValue(const String& value) | File: ../Resource/JSONValue.h
    engine->RegisterObjectBehaviour("JSONValue", asBEHAVE_CONSTRUCT, "void f(const String&in)", AS_FUNCTION_OBJFIRST(JSONValue_JSONValue_String), AS_CALL_CDECL_OBJFIRST);
    // JSONValue::JSONValue(const char* value) | File: ../Resource/JSONValue.h
    // Error: type "const char*" can not automatically bind
    // JSONValue::JSONValue(const JSONArray& value) | File: ../Resource/JSONValue.h
    // Error: type "const JSONArray&" can not automatically bind
    // JSONValue::JSONValue(const JSONObject& value) | File: ../Resource/JSONValue.h
    // Error: type "const JSONObject&" can not automatically bind
    // JSONValue::JSONValue(const JSONValue& value) | File: ../Resource/JSONValue.h
    engine->RegisterObjectBehaviour("JSONValue", asBEHAVE_CONSTRUCT, "void f(const JSONValue&in)", AS_FUNCTION_OBJFIRST(JSONValue_JSONValue_JSONValue), AS_CALL_CDECL_OBJFIRST);
    // JSONValue& JSONValue::operator=(bool rhs) | File: ../Resource/JSONValue.h
    engine->RegisterObjectMethod("JSONValue", "JSONValue& opAssign(bool)", AS_METHODPR(JSONValue, operator=, (bool), JSONValue&), AS_CALL_THISCALL);
    // JSONValue& JSONValue::operator=(int rhs) | File: ../Resource/JSONValue.h
    engine->RegisterObjectMethod("JSONValue", "JSONValue& opAssign(int)", AS_METHODPR(JSONValue, operator=, (int), JSONValue&), AS_CALL_THISCALL);
    // JSONValue& JSONValue::operator=(unsigned rhs) | File: ../Resource/JSONValue.h
    engine->RegisterObjectMethod("JSONValue", "JSONValue& opAssign(uint)", AS_METHODPR(JSONValue, operator=, (unsigned), JSONValue&), AS_CALL_THISCALL);
    // JSONValue& JSONValue::operator=(float rhs) | File: ../Resource/JSONValue.h
    engine->RegisterObjectMethod("JSONValue", "JSONValue& opAssign(float)", AS_METHODPR(JSONValue, operator=, (float), JSONValue&), AS_CALL_THISCALL);
    // JSONValue& JSONValue::operator=(double rhs) | File: ../Resource/JSONValue.h
    engine->RegisterObjectMethod("JSONValue", "JSONValue& opAssign(double)", AS_METHODPR(JSONValue, operator=, (double), JSONValue&), AS_CALL_THISCALL);
    // JSONValue& JSONValue::operator=(const String& rhs) | File: ../Resource/JSONValue.h
    engine->RegisterObjectMethod("JSONValue", "JSONValue& opAssign(const String&in)", AS_METHODPR(JSONValue, operator=, (const String&), JSONValue&), AS_CALL_THISCALL);
    // JSONValue& JSONValue::operator=(const char* rhs) | File: ../Resource/JSONValue.h
    // Error: type "const char*" can not automatically bind
    // JSONValue& JSONValue::operator=(const JSONArray& rhs) | File: ../Resource/JSONValue.h
    // Error: type "const JSONArray&" can not automatically bind
    // JSONValue& JSONValue::operator=(const JSONObject& rhs) | File: ../Resource/JSONValue.h
    // Error: type "const JSONObject&" can not automatically bind
    // JSONValue& JSONValue::operator=(const JSONValue& rhs) | File: ../Resource/JSONValue.h
    engine->RegisterObjectMethod("JSONValue", "JSONValue& opAssign(const JSONValue&in)", AS_METHODPR(JSONValue, operator=, (const JSONValue&), JSONValue&), AS_CALL_THISCALL);
    // JSONValue& JSONValue::operator[](unsigned index) | File: ../Resource/JSONValue.h
    engine->RegisterObjectMethod("JSONValue", "JSONValue& opIndex(uint)", AS_METHODPR(JSONValue, operator[], (unsigned), JSONValue&), AS_CALL_THISCALL);
    // const JSONValue& JSONValue::operator[](unsigned index) const | File: ../Resource/JSONValue.h
    engine->RegisterObjectMethod("JSONValue", "const JSONValue& opIndex(uint) const", AS_METHODPR(JSONValue, operator[], (unsigned) const, const JSONValue&), AS_CALL_THISCALL);
    // JSONValue& JSONValue::operator[](const String& key) | File: ../Resource/JSONValue.h
    engine->RegisterObjectMethod("JSONValue", "JSONValue& opIndex(const String&in)", AS_METHODPR(JSONValue, operator[], (const String&), JSONValue&), AS_CALL_THISCALL);
    // const JSONValue& JSONValue::operator[](const String& key) const | File: ../Resource/JSONValue.h
    engine->RegisterObjectMethod("JSONValue", "const JSONValue& opIndex(const String&in) const", AS_METHODPR(JSONValue, operator[], (const String&) const, const JSONValue&), AS_CALL_THISCALL);
    // void JSONValue::Pop() | File: ../Resource/JSONValue.h
    engine->RegisterObjectMethod("JSONValue", "void Pop()", AS_METHODPR(JSONValue, Pop, (), void), AS_CALL_THISCALL);
    // void JSONValue::Push(const JSONValue& value) | File: ../Resource/JSONValue.h
    engine->RegisterObjectMethod("JSONValue", "void Push(const JSONValue&in)", AS_METHODPR(JSONValue, Push, (const JSONValue&), void), AS_CALL_THISCALL);
    // void JSONValue::Resize(unsigned newSize) | File: ../Resource/JSONValue.h
    engine->RegisterObjectMethod("JSONValue", "void Resize(uint)", AS_METHODPR(JSONValue, Resize, (unsigned), void), AS_CALL_THISCALL);
    // void JSONValue::Set(const String& key, const JSONValue& value) | File: ../Resource/JSONValue.h
    engine->RegisterObjectMethod("JSONValue", "void Set(const String&in, const JSONValue&in)", AS_METHODPR(JSONValue, Set, (const String&, const JSONValue&), void), AS_CALL_THISCALL);
    // void JSONValue::SetType(JSONValueType valueType, JSONNumberType numberType=JSONNT_NAN) | File: ../Resource/JSONValue.h
    engine->RegisterObjectMethod("JSONValue", "void SetType(JSONValueType, JSONNumberType = JSONNT_NAN)", AS_METHODPR(JSONValue, SetType, (JSONValueType, JSONNumberType), void), AS_CALL_THISCALL);
    // void JSONValue::SetVariant(const Variant& variant, Context* context=nullptr) | File: ../Resource/JSONValue.h
    engine->RegisterObjectMethod("JSONValue", "void SetVariant(const Variant&in)", AS_FUNCTION_OBJFIRST(JSONValue_SetVariant_Variant_Context), AS_CALL_CDECL_OBJFIRST);
    // void JSONValue::SetVariantMap(const VariantMap& variantMap, Context* context=nullptr) | File: ../Resource/JSONValue.h
    engine->RegisterObjectMethod("JSONValue", "void SetVariantMap(const VariantMap&in)", AS_FUNCTION_OBJFIRST(JSONValue_SetVariantMap_VariantMap_Context), AS_CALL_CDECL_OBJFIRST);
    // void JSONValue::SetVariantValue(const Variant& variant, Context* context=nullptr) | File: ../Resource/JSONValue.h
    engine->RegisterObjectMethod("JSONValue", "void SetVariantValue(const Variant&in)", AS_FUNCTION_OBJFIRST(JSONValue_SetVariantValue_Variant_Context), AS_CALL_CDECL_OBJFIRST);
    // void JSONValue::SetVariantVector(const VariantVector& variantVector, Context* context=nullptr) | File: ../Resource/JSONValue.h
    // Error: type "const VariantVector&" can not automatically bind
    // unsigned JSONValue::Size() const | File: ../Resource/JSONValue.h
    engine->RegisterObjectMethod("JSONValue", "uint Size() const", AS_METHODPR(JSONValue, Size, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("JSONValue", "uint get_size() const", AS_METHODPR(JSONValue, Size, () const, unsigned), AS_CALL_THISCALL);
#ifdef REGISTER_MANUAL_PART_JSONValue
    REGISTER_MANUAL_PART_JSONValue(JSONValue, "JSONValue")
#endif

    // PODVector<float> JoystickState::axes_ | File: ../Input/Input.h
    // Error: type "PODVector<float>" can not automatically bind
    // PODVector<bool> JoystickState::buttonPress_ | File: ../Input/Input.h
    // Error: type "PODVector<bool>" can not automatically bind
    // PODVector<bool> JoystickState::buttons_ | File: ../Input/Input.h
    // Error: type "PODVector<bool>" can not automatically bind
    // SDL_GameController* JoystickState::controller_ | File: ../Input/Input.h
    // SDL_GameController* can not be registered
    // PODVector<int> JoystickState::hats_ | File: ../Input/Input.h
    // Error: type "PODVector<int>" can not automatically bind
    // SDL_Joystick* JoystickState::joystick_ | File: ../Input/Input.h
    // SDL_Joystick* can not be registered
    // SDL_JoystickID JoystickState::joystickID_ | File: ../Input/Input.h
    engine->RegisterObjectProperty("JoystickState", "SDL_JoystickID joystickID", offsetof(JoystickState, joystickID_));
    // String JoystickState::name_ | File: ../Input/Input.h
    engine->RegisterObjectProperty("JoystickState", "String name", offsetof(JoystickState, name_));
    // UIElement* JoystickState::screenJoystick_ | File: ../Input/Input.h
    // UIElement* can not be registered
    // float JoystickState::GetAxisPosition(unsigned index) const | File: ../Input/Input.h
    engine->RegisterObjectMethod("JoystickState", "float GetAxisPosition(uint) const", AS_METHODPR(JoystickState, GetAxisPosition, (unsigned) const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("JoystickState", "float get_axisPosition(uint) const", AS_METHODPR(JoystickState, GetAxisPosition, (unsigned) const, float), AS_CALL_THISCALL);
    // bool JoystickState::GetButtonDown(unsigned index) const | File: ../Input/Input.h
    engine->RegisterObjectMethod("JoystickState", "bool GetButtonDown(uint) const", AS_METHODPR(JoystickState, GetButtonDown, (unsigned) const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("JoystickState", "bool get_buttonDown(uint) const", AS_METHODPR(JoystickState, GetButtonDown, (unsigned) const, bool), AS_CALL_THISCALL);
    // bool JoystickState::GetButtonPress(unsigned index) const | File: ../Input/Input.h
    engine->RegisterObjectMethod("JoystickState", "bool GetButtonPress(uint) const", AS_METHODPR(JoystickState, GetButtonPress, (unsigned) const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("JoystickState", "bool get_buttonPress(uint) const", AS_METHODPR(JoystickState, GetButtonPress, (unsigned) const, bool), AS_CALL_THISCALL);
    // int JoystickState::GetHatPosition(unsigned index) const | File: ../Input/Input.h
    engine->RegisterObjectMethod("JoystickState", "int GetHatPosition(uint) const", AS_METHODPR(JoystickState, GetHatPosition, (unsigned) const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("JoystickState", "int get_hatPosition(uint) const", AS_METHODPR(JoystickState, GetHatPosition, (unsigned) const, int), AS_CALL_THISCALL);
    // unsigned JoystickState::GetNumAxes() const | File: ../Input/Input.h
    engine->RegisterObjectMethod("JoystickState", "uint GetNumAxes() const", AS_METHODPR(JoystickState, GetNumAxes, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("JoystickState", "uint get_numAxes() const", AS_METHODPR(JoystickState, GetNumAxes, () const, unsigned), AS_CALL_THISCALL);
    // unsigned JoystickState::GetNumButtons() const | File: ../Input/Input.h
    engine->RegisterObjectMethod("JoystickState", "uint GetNumButtons() const", AS_METHODPR(JoystickState, GetNumButtons, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("JoystickState", "uint get_numButtons() const", AS_METHODPR(JoystickState, GetNumButtons, () const, unsigned), AS_CALL_THISCALL);
    // unsigned JoystickState::GetNumHats() const | File: ../Input/Input.h
    engine->RegisterObjectMethod("JoystickState", "uint GetNumHats() const", AS_METHODPR(JoystickState, GetNumHats, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("JoystickState", "uint get_numHats() const", AS_METHODPR(JoystickState, GetNumHats, () const, unsigned), AS_CALL_THISCALL);
    // void JoystickState::Initialize(unsigned numButtons, unsigned numAxes, unsigned numHats) | File: ../Input/Input.h
    engine->RegisterObjectMethod("JoystickState", "void Initialize(uint, uint, uint)", AS_METHODPR(JoystickState, Initialize, (unsigned, unsigned, unsigned), void), AS_CALL_THISCALL);
    // bool JoystickState::IsController() const | File: ../Input/Input.h
    engine->RegisterObjectMethod("JoystickState", "bool IsController() const", AS_METHODPR(JoystickState, IsController, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("JoystickState", "bool get_controller() const", AS_METHODPR(JoystickState, IsController, () const, bool), AS_CALL_THISCALL);
    // void JoystickState::Reset() | File: ../Input/Input.h
    engine->RegisterObjectMethod("JoystickState", "void Reset()", AS_METHODPR(JoystickState, Reset, (), void), AS_CALL_THISCALL);
    // JoystickState& JoystickState::operator=(const JoystickState&) | Possible implicitly-declared
    RegisterImplicitlyDeclaredAssignOperatorIfPossible<JoystickState>(engine, "JoystickState");
    engine->RegisterObjectBehaviour("JoystickState", asBEHAVE_ADDREF, "void f()", AS_FUNCTION_OBJLAST(FakeAddRef), AS_CALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("JoystickState", asBEHAVE_RELEASE, "void f()", AS_FUNCTION_OBJLAST(FakeReleaseRef), AS_CALL_CDECL_OBJLAST);
#ifdef REGISTER_MANUAL_PART_JoystickState
    REGISTER_MANUAL_PART_JoystickState(JoystickState, "JoystickState")
#endif

}

}
