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
    engine->RegisterObjectBehaviour("JSONFile", asBEHAVE_ADDREF, "void f()", asMETHODPR(JSONFile, AddRef, (), void), asCALL_THISCALL);
    // bool JSONFile::BeginLoad(Deserializer& source) override | File: ../Resource/JSONFile.h
    engine->RegisterObjectMethod("JSONFile", "bool BeginLoad(Deserializer&)", asMETHODPR(JSONFile, BeginLoad, (Deserializer&), bool), asCALL_THISCALL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // virtual bool Resource::EndLoad() | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("JSONFile", "bool EndLoad()", asMETHODPR(JSONFile, EndLoad, (), bool), asCALL_THISCALL);
    // bool JSONFile::FromString(const String& source) | File: ../Resource/JSONFile.h
    engine->RegisterObjectMethod("JSONFile", "bool FromString(const String&in)", asMETHODPR(JSONFile, FromString, (const String&), bool), asCALL_THISCALL);
    // AsyncLoadState Resource::GetAsyncLoadState() const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("JSONFile", "AsyncLoadState GetAsyncLoadState() const", asMETHODPR(JSONFile, GetAsyncLoadState, () const, AsyncLoadState), asCALL_THISCALL);
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("JSONFile", "bool GetBlockEvents() const", asMETHODPR(JSONFile, GetBlockEvents, () const, bool), asCALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("JSONFile", "const String& GetCategory() const", asMETHODPR(JSONFile, GetCategory, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("JSONFile", "const String& get_category() const", asMETHODPR(JSONFile, GetCategory, () const, const String&), asCALL_THISCALL);
    // Context* Object::GetContext() const | File: ../Core/Object.h
    // Error: type "Context*" can used only as function parameter
    // VariantMap& Object::GetEventDataMap() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("JSONFile", "VariantMap& GetEventDataMap() const", asMETHODPR(JSONFile, GetEventDataMap, () const, VariantMap&), asCALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("JSONFile", "Object@+ GetEventSender() const", asMETHODPR(JSONFile, GetEventSender, () const, Object*), asCALL_THISCALL);
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("JSONFile", "const Variant& GetGlobalVar(StringHash) const", asMETHODPR(JSONFile, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    engine->RegisterObjectMethod("JSONFile", "const Variant& get_globalVar(StringHash) const", asMETHODPR(JSONFile, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("JSONFile", "const VariantMap& GetGlobalVars() const", asMETHODPR(JSONFile, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    engine->RegisterObjectMethod("JSONFile", "const VariantMap& get_globalVars() const", asMETHODPR(JSONFile, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    // unsigned Resource::GetMemoryUse() const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("JSONFile", "uint GetMemoryUse() const", asMETHODPR(JSONFile, GetMemoryUse, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("JSONFile", "uint get_memoryUse() const", asMETHODPR(JSONFile, GetMemoryUse, () const, unsigned), asCALL_THISCALL);
    // const String& Resource::GetName() const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("JSONFile", "const String& GetName() const", asMETHODPR(JSONFile, GetName, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("JSONFile", "const String& get_name() const", asMETHODPR(JSONFile, GetName, () const, const String&), asCALL_THISCALL);
    // StringHash Resource::GetNameHash() const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("JSONFile", "StringHash GetNameHash() const", asMETHODPR(JSONFile, GetNameHash, () const, StringHash), asCALL_THISCALL);
    // JSONValue& JSONFile::GetRoot() | File: ../Resource/JSONFile.h
    engine->RegisterObjectMethod("JSONFile", "JSONValue& GetRoot()", asMETHODPR(JSONFile, GetRoot, (), JSONValue&), asCALL_THISCALL);
    engine->RegisterObjectMethod("JSONFile", "JSONValue& get_root()", asMETHODPR(JSONFile, GetRoot, (), JSONValue&), asCALL_THISCALL);
    // const JSONValue& JSONFile::GetRoot() const | File: ../Resource/JSONFile.h
    engine->RegisterObjectMethod("JSONFile", "const JSONValue& GetRoot() const", asMETHODPR(JSONFile, GetRoot, () const, const JSONValue&), asCALL_THISCALL);
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("JSONFile", "Object@+ GetSubsystem(StringHash) const", asMETHODPR(JSONFile, GetSubsystem, (StringHash) const, Object*), asCALL_THISCALL);
    // template<class T> T* Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("JSONFile", "StringHash GetType() const", asMETHODPR(JSONFile, GetType, () const, StringHash), asCALL_THISCALL);
    engine->RegisterObjectMethod("JSONFile", "StringHash get_type() const", asMETHODPR(JSONFile, GetType, () const, StringHash), asCALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("JSONFile", "const String& GetTypeName() const", asMETHODPR(JSONFile, GetTypeName, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("JSONFile", "const String& get_typeName() const", asMETHODPR(JSONFile, GetTypeName, () const, const String&), asCALL_THISCALL);
    // unsigned Resource::GetUseTimer() | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("JSONFile", "uint GetUseTimer()", asMETHODPR(JSONFile, GetUseTimer, (), unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("JSONFile", "uint get_useTimer()", asMETHODPR(JSONFile, GetUseTimer, (), unsigned), asCALL_THISCALL);
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("JSONFile", "bool HasEventHandlers() const", asMETHODPR(JSONFile, HasEventHandlers, () const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("JSONFile", "bool HasSubscribedToEvent(StringHash) const", asMETHODPR(JSONFile, HasSubscribedToEvent, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("JSONFile", "bool HasSubscribedToEvent(Object@+, StringHash) const", asMETHODPR(JSONFile, HasSubscribedToEvent, (Object*, StringHash) const, bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("JSONFile", "bool IsInstanceOf(StringHash) const", asMETHODPR(JSONFile, IsInstanceOf, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // explicit JSONFile::JSONFile(Context* context) | File: ../Resource/JSONFile.h
    engine->RegisterObjectBehaviour("JSONFile", asBEHAVE_FACTORY, "JSONFile@+ f()", asFUNCTION(JSONFile_JSONFile_Context), asCALL_CDECL);
    // bool Resource::Load(Deserializer& source) | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("JSONFile", "bool Load(Deserializer&)", asMETHODPR(JSONFile, Load, (Deserializer&), bool), asCALL_THISCALL);
    // bool Resource::LoadFile(const String& fileName) | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("JSONFile", "bool LoadFile(const String&in)", asMETHODPR(JSONFile, LoadFile, (const String&), bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("JSONFile", "bool Load(const String&in)", asMETHODPR(JSONFile, LoadFile, (const String&), bool), asCALL_THISCALL);
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("JSONFile", "void OnEvent(Object@+, StringHash, VariantMap&)", asMETHODPR(JSONFile, OnEvent, (Object*, StringHash, VariantMap&), void), asCALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("JSONFile", "int Refs() const", asMETHODPR(JSONFile, Refs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("JSONFile", "int get_refs() const", asMETHODPR(JSONFile, Refs, () const, int), asCALL_THISCALL);
    // static void JSONFile::RegisterObject(Context* context) | File: ../Resource/JSONFile.h
    // Not registered because have @nobind mark
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("JSONFile", asBEHAVE_RELEASE, "void f()", asMETHODPR(JSONFile, ReleaseRef, (), void), asCALL_THISCALL);
    // void Resource::ResetUseTimer() | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("JSONFile", "void ResetUseTimer()", asMETHODPR(JSONFile, ResetUseTimer, (), void), asCALL_THISCALL);
    // bool JSONFile::Save(Serializer& dest) const override | File: ../Resource/JSONFile.h
    engine->RegisterObjectMethod("JSONFile", "bool Save(Serializer&) const", asMETHODPR(JSONFile, Save, (Serializer&) const, bool), asCALL_THISCALL);
    // bool JSONFile::Save(Serializer& dest, const String& indendation) const | File: ../Resource/JSONFile.h
    engine->RegisterObjectMethod("JSONFile", "bool Save(Serializer&, const String&in) const", asMETHODPR(JSONFile, Save, (Serializer&, const String&) const, bool), asCALL_THISCALL);
    // virtual bool Resource::SaveFile(const String& fileName) const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("JSONFile", "bool SaveFile(const String&in) const", asMETHODPR(JSONFile, SaveFile, (const String&) const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("JSONFile", "bool Save(const String&in) const", asMETHODPR(JSONFile, SaveFile, (const String&) const, bool), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("JSONFile", "void SendEvent(StringHash)", asMETHODPR(JSONFile, SendEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("JSONFile", "void SendEvent(StringHash, VariantMap&)", asMETHODPR(JSONFile, SendEvent, (StringHash, VariantMap&), void), asCALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void Resource::SetAsyncLoadState(AsyncLoadState newState) | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("JSONFile", "void SetAsyncLoadState(AsyncLoadState)", asMETHODPR(JSONFile, SetAsyncLoadState, (AsyncLoadState), void), asCALL_THISCALL);
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("JSONFile", "void SetBlockEvents(bool)", asMETHODPR(JSONFile, SetBlockEvents, (bool), void), asCALL_THISCALL);
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("JSONFile", "void SetGlobalVar(StringHash, const Variant&in)", asMETHODPR(JSONFile, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("JSONFile", "void set_globalVar(StringHash, const Variant&in)", asMETHODPR(JSONFile, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    // void Resource::SetMemoryUse(unsigned size) | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("JSONFile", "void SetMemoryUse(uint)", asMETHODPR(JSONFile, SetMemoryUse, (unsigned), void), asCALL_THISCALL);
    // void Resource::SetName(const String& name) | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("JSONFile", "void SetName(const String&in)", asMETHODPR(JSONFile, SetName, (const String&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("JSONFile", "void set_name(const String&in)", asMETHODPR(JSONFile, SetName, (const String&), void), asCALL_THISCALL);
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // String JSONFile::ToString(const String& indendation="\t") const | File: ../Resource/JSONFile.h
    engine->RegisterObjectMethod("JSONFile", "String ToString(const String&in = \"\t\") const", asMETHODPR(JSONFile, ToString, (const String&) const, String), asCALL_THISCALL);
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod("JSONFile", "void UnsubscribeFromAllEvents()", asMETHODPR(JSONFile, UnsubscribeFromAllEvents, (), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("JSONFile", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", asFUNCTION(JSONFile_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), asCALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("JSONFile", "void UnsubscribeFromEvent(StringHash)", asMETHODPR(JSONFile, UnsubscribeFromEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("JSONFile", "void UnsubscribeFromEvent(Object@+, StringHash)", asMETHODPR(JSONFile, UnsubscribeFromEvent, (Object*, StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("JSONFile", "void UnsubscribeFromEvents(Object@+)", asMETHODPR(JSONFile, UnsubscribeFromEvents, (Object*), void), asCALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("JSONFile", "int WeakRefs() const", asMETHODPR(JSONFile, WeakRefs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("JSONFile", "int get_weakRefs() const", asMETHODPR(JSONFile, WeakRefs, () const, int), asCALL_THISCALL);
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
    engine->RegisterObjectMethod("JSONValue", "void Clear()", asMETHODPR(JSONValue, Clear, (), void), asCALL_THISCALL);
    // bool JSONValue::Contains(const String& key) const | File: ../Resource/JSONValue.h
    engine->RegisterObjectMethod("JSONValue", "bool Contains(const String&in) const", asMETHODPR(JSONValue, Contains, (const String&) const, bool), asCALL_THISCALL);
    // JSONObjectIterator JSONValue::End() | File: ../Resource/JSONValue.h
    // Error: type "JSONObjectIterator" can not automatically bind
    // ConstJSONObjectIterator JSONValue::End() const | File: ../Resource/JSONValue.h
    // Error: type "ConstJSONObjectIterator" can not automatically bind
    // void JSONValue::Erase(unsigned pos, unsigned length=1) | File: ../Resource/JSONValue.h
    engine->RegisterObjectMethod("JSONValue", "void Erase(uint, uint = 1)", asMETHODPR(JSONValue, Erase, (unsigned, unsigned), void), asCALL_THISCALL);
    // bool JSONValue::Erase(const String& key) | File: ../Resource/JSONValue.h
    engine->RegisterObjectMethod("JSONValue", "bool Erase(const String&in)", asMETHODPR(JSONValue, Erase, (const String&), bool), asCALL_THISCALL);
    // const JSONValue& JSONValue::Get(const String& key) const | File: ../Resource/JSONValue.h
    engine->RegisterObjectMethod("JSONValue", "const JSONValue& Get(const String&in) const", asMETHODPR(JSONValue, Get, (const String&) const, const JSONValue&), asCALL_THISCALL);
    // const JSONArray& JSONValue::GetArray() const | File: ../Resource/JSONValue.h
    // Error: type "const JSONArray&" can not automatically bind
    // bool JSONValue::GetBool(bool defaultValue=false) const | File: ../Resource/JSONValue.h
    engine->RegisterObjectMethod("JSONValue", "bool GetBool(bool = false) const", asMETHODPR(JSONValue, GetBool, (bool) const, bool), asCALL_THISCALL);
    // const char* JSONValue::GetCString(const char* defaultValue="") const | File: ../Resource/JSONValue.h
    // Error: type "const char*" can not automatically bind
    // double JSONValue::GetDouble(double defaultValue=0.0) const | File: ../Resource/JSONValue.h
    engine->RegisterObjectMethod("JSONValue", "double GetDouble(double = 0.0) const", asMETHODPR(JSONValue, GetDouble, (double) const, double), asCALL_THISCALL);
    // float JSONValue::GetFloat(float defaultValue=0.0f) const | File: ../Resource/JSONValue.h
    engine->RegisterObjectMethod("JSONValue", "float GetFloat(float = 0.0f) const", asMETHODPR(JSONValue, GetFloat, (float) const, float), asCALL_THISCALL);
    // int JSONValue::GetInt(int defaultValue=0) const | File: ../Resource/JSONValue.h
    engine->RegisterObjectMethod("JSONValue", "int GetInt(int = 0) const", asMETHODPR(JSONValue, GetInt, (int) const, int), asCALL_THISCALL);
    // JSONNumberType JSONValue::GetNumberType() const | File: ../Resource/JSONValue.h
    engine->RegisterObjectMethod("JSONValue", "JSONNumberType GetNumberType() const", asMETHODPR(JSONValue, GetNumberType, () const, JSONNumberType), asCALL_THISCALL);
    engine->RegisterObjectMethod("JSONValue", "JSONNumberType get_numberType() const", asMETHODPR(JSONValue, GetNumberType, () const, JSONNumberType), asCALL_THISCALL);
    // static JSONNumberType JSONValue::GetNumberTypeFromName(const String& typeName) | File: ../Resource/JSONValue.h
    engine->SetDefaultNamespace("JSONValue");
    engine->RegisterGlobalFunction("JSONNumberType GetNumberTypeFromName(const String&in)", asFUNCTIONPR(JSONValue::GetNumberTypeFromName, (const String&), JSONNumberType), asCALL_CDECL);
    engine->SetDefaultNamespace("");
    // static JSONNumberType JSONValue::GetNumberTypeFromName(const char* typeName) | File: ../Resource/JSONValue.h
    // Error: type "const char*" can not automatically bind
    // String JSONValue::GetNumberTypeName() const | File: ../Resource/JSONValue.h
    engine->RegisterObjectMethod("JSONValue", "String GetNumberTypeName() const", asMETHODPR(JSONValue, GetNumberTypeName, () const, String), asCALL_THISCALL);
    engine->RegisterObjectMethod("JSONValue", "String get_numberTypeName() const", asMETHODPR(JSONValue, GetNumberTypeName, () const, String), asCALL_THISCALL);
    // static String JSONValue::GetNumberTypeName(JSONNumberType type) | File: ../Resource/JSONValue.h
    engine->SetDefaultNamespace("JSONValue");
    engine->RegisterGlobalFunction("String GetNumberTypeName(JSONNumberType)", asFUNCTIONPR(JSONValue::GetNumberTypeName, (JSONNumberType), String), asCALL_CDECL);
    engine->SetDefaultNamespace("");
    // const JSONObject& JSONValue::GetObject() const | File: ../Resource/JSONValue.h
    // Error: type "const JSONObject&" can not automatically bind
    // const String& JSONValue::GetString(const String& defaultValue=String::EMPTY) const | File: ../Resource/JSONValue.h
    engine->RegisterObjectMethod("JSONValue", "const String& GetString(const String&in = String::EMPTY) const", asMETHODPR(JSONValue, GetString, (const String&) const, const String&), asCALL_THISCALL);
    // unsigned JSONValue::GetUInt(unsigned defaultValue=0) const | File: ../Resource/JSONValue.h
    engine->RegisterObjectMethod("JSONValue", "uint GetUInt(uint = 0) const", asMETHODPR(JSONValue, GetUInt, (unsigned) const, unsigned), asCALL_THISCALL);
    // JSONValueType JSONValue::GetValueType() const | File: ../Resource/JSONValue.h
    engine->RegisterObjectMethod("JSONValue", "JSONValueType GetValueType() const", asMETHODPR(JSONValue, GetValueType, () const, JSONValueType), asCALL_THISCALL);
    engine->RegisterObjectMethod("JSONValue", "JSONValueType get_valueType() const", asMETHODPR(JSONValue, GetValueType, () const, JSONValueType), asCALL_THISCALL);
    // static JSONValueType JSONValue::GetValueTypeFromName(const String& typeName) | File: ../Resource/JSONValue.h
    engine->SetDefaultNamespace("JSONValue");
    engine->RegisterGlobalFunction("JSONValueType GetValueTypeFromName(const String&in)", asFUNCTIONPR(JSONValue::GetValueTypeFromName, (const String&), JSONValueType), asCALL_CDECL);
    engine->SetDefaultNamespace("");
    // static JSONValueType JSONValue::GetValueTypeFromName(const char* typeName) | File: ../Resource/JSONValue.h
    // Error: type "const char*" can not automatically bind
    // String JSONValue::GetValueTypeName() const | File: ../Resource/JSONValue.h
    engine->RegisterObjectMethod("JSONValue", "String GetValueTypeName() const", asMETHODPR(JSONValue, GetValueTypeName, () const, String), asCALL_THISCALL);
    engine->RegisterObjectMethod("JSONValue", "String get_valueTypeName() const", asMETHODPR(JSONValue, GetValueTypeName, () const, String), asCALL_THISCALL);
    // static String JSONValue::GetValueTypeName(JSONValueType type) | File: ../Resource/JSONValue.h
    engine->SetDefaultNamespace("JSONValue");
    engine->RegisterGlobalFunction("String GetValueTypeName(JSONValueType)", asFUNCTIONPR(JSONValue::GetValueTypeName, (JSONValueType), String), asCALL_CDECL);
    engine->SetDefaultNamespace("");
    // Variant JSONValue::GetVariant() const | File: ../Resource/JSONValue.h
    engine->RegisterObjectMethod("JSONValue", "Variant GetVariant() const", asMETHODPR(JSONValue, GetVariant, () const, Variant), asCALL_THISCALL);
    // VariantMap JSONValue::GetVariantMap() const | File: ../Resource/JSONValue.h
    engine->RegisterObjectMethod("JSONValue", "VariantMap GetVariantMap() const", asMETHODPR(JSONValue, GetVariantMap, () const, VariantMap), asCALL_THISCALL);
    // Variant JSONValue::GetVariantValue(VariantType type) const | File: ../Resource/JSONValue.h
    engine->RegisterObjectMethod("JSONValue", "Variant GetVariantValue(VariantType) const", asMETHODPR(JSONValue, GetVariantValue, (VariantType) const, Variant), asCALL_THISCALL);
    // VariantVector JSONValue::GetVariantVector() const | File: ../Resource/JSONValue.h
    // Error: type "VariantVector" can not automatically bind
    // void JSONValue::Insert(unsigned pos, const JSONValue& value) | File: ../Resource/JSONValue.h
    engine->RegisterObjectMethod("JSONValue", "void Insert(uint, const JSONValue&in)", asMETHODPR(JSONValue, Insert, (unsigned, const JSONValue&), void), asCALL_THISCALL);
    // bool JSONValue::IsArray() const | File: ../Resource/JSONValue.h
    engine->RegisterObjectMethod("JSONValue", "bool IsArray() const", asMETHODPR(JSONValue, IsArray, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("JSONValue", "bool get_isArray() const", asMETHODPR(JSONValue, IsArray, () const, bool), asCALL_THISCALL);
    // bool JSONValue::IsBool() const | File: ../Resource/JSONValue.h
    engine->RegisterObjectMethod("JSONValue", "bool IsBool() const", asMETHODPR(JSONValue, IsBool, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("JSONValue", "bool get_isBool() const", asMETHODPR(JSONValue, IsBool, () const, bool), asCALL_THISCALL);
    // bool JSONValue::IsNull() const | File: ../Resource/JSONValue.h
    engine->RegisterObjectMethod("JSONValue", "bool IsNull() const", asMETHODPR(JSONValue, IsNull, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("JSONValue", "bool get_isNull() const", asMETHODPR(JSONValue, IsNull, () const, bool), asCALL_THISCALL);
    // bool JSONValue::IsNumber() const | File: ../Resource/JSONValue.h
    engine->RegisterObjectMethod("JSONValue", "bool IsNumber() const", asMETHODPR(JSONValue, IsNumber, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("JSONValue", "bool get_isNumber() const", asMETHODPR(JSONValue, IsNumber, () const, bool), asCALL_THISCALL);
    // bool JSONValue::IsObject() const | File: ../Resource/JSONValue.h
    engine->RegisterObjectMethod("JSONValue", "bool IsObject() const", asMETHODPR(JSONValue, IsObject, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("JSONValue", "bool get_isObject() const", asMETHODPR(JSONValue, IsObject, () const, bool), asCALL_THISCALL);
    // bool JSONValue::IsString() const | File: ../Resource/JSONValue.h
    engine->RegisterObjectMethod("JSONValue", "bool IsString() const", asMETHODPR(JSONValue, IsString, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("JSONValue", "bool get_isString() const", asMETHODPR(JSONValue, IsString, () const, bool), asCALL_THISCALL);
    // JSONValue::JSONValue(bool value) | File: ../Resource/JSONValue.h
    engine->RegisterObjectBehaviour("JSONValue", asBEHAVE_CONSTRUCT, "void f(bool)", asFUNCTION(JSONValue_JSONValue_bool), asCALL_CDECL_OBJFIRST);
    // JSONValue::JSONValue(int value) | File: ../Resource/JSONValue.h
    engine->RegisterObjectBehaviour("JSONValue", asBEHAVE_CONSTRUCT, "void f(int)", asFUNCTION(JSONValue_JSONValue_int), asCALL_CDECL_OBJFIRST);
    // JSONValue::JSONValue(unsigned value) | File: ../Resource/JSONValue.h
    engine->RegisterObjectBehaviour("JSONValue", asBEHAVE_CONSTRUCT, "void f(uint)", asFUNCTION(JSONValue_JSONValue_unsigned), asCALL_CDECL_OBJFIRST);
    // JSONValue::JSONValue(float value) | File: ../Resource/JSONValue.h
    engine->RegisterObjectBehaviour("JSONValue", asBEHAVE_CONSTRUCT, "void f(float)", asFUNCTION(JSONValue_JSONValue_float), asCALL_CDECL_OBJFIRST);
    // JSONValue::JSONValue(double value) | File: ../Resource/JSONValue.h
    engine->RegisterObjectBehaviour("JSONValue", asBEHAVE_CONSTRUCT, "void f(double)", asFUNCTION(JSONValue_JSONValue_double), asCALL_CDECL_OBJFIRST);
    // JSONValue::JSONValue(const String& value) | File: ../Resource/JSONValue.h
    engine->RegisterObjectBehaviour("JSONValue", asBEHAVE_CONSTRUCT, "void f(const String&in)", asFUNCTION(JSONValue_JSONValue_String), asCALL_CDECL_OBJFIRST);
    // JSONValue::JSONValue(const char* value) | File: ../Resource/JSONValue.h
    // Error: type "const char*" can not automatically bind
    // JSONValue::JSONValue(const JSONArray& value) | File: ../Resource/JSONValue.h
    // Error: type "const JSONArray&" can not automatically bind
    // JSONValue::JSONValue(const JSONObject& value) | File: ../Resource/JSONValue.h
    // Error: type "const JSONObject&" can not automatically bind
    // JSONValue::JSONValue(const JSONValue& value) | File: ../Resource/JSONValue.h
    engine->RegisterObjectBehaviour("JSONValue", asBEHAVE_CONSTRUCT, "void f(const JSONValue&in)", asFUNCTION(JSONValue_JSONValue_JSONValue), asCALL_CDECL_OBJFIRST);
    // JSONValue& JSONValue::operator=(bool rhs) | File: ../Resource/JSONValue.h
    engine->RegisterObjectMethod("JSONValue", "JSONValue& opAssign(bool)", asMETHODPR(JSONValue, operator=, (bool), JSONValue&), asCALL_THISCALL);
    // JSONValue& JSONValue::operator=(int rhs) | File: ../Resource/JSONValue.h
    engine->RegisterObjectMethod("JSONValue", "JSONValue& opAssign(int)", asMETHODPR(JSONValue, operator=, (int), JSONValue&), asCALL_THISCALL);
    // JSONValue& JSONValue::operator=(unsigned rhs) | File: ../Resource/JSONValue.h
    engine->RegisterObjectMethod("JSONValue", "JSONValue& opAssign(uint)", asMETHODPR(JSONValue, operator=, (unsigned), JSONValue&), asCALL_THISCALL);
    // JSONValue& JSONValue::operator=(float rhs) | File: ../Resource/JSONValue.h
    engine->RegisterObjectMethod("JSONValue", "JSONValue& opAssign(float)", asMETHODPR(JSONValue, operator=, (float), JSONValue&), asCALL_THISCALL);
    // JSONValue& JSONValue::operator=(double rhs) | File: ../Resource/JSONValue.h
    engine->RegisterObjectMethod("JSONValue", "JSONValue& opAssign(double)", asMETHODPR(JSONValue, operator=, (double), JSONValue&), asCALL_THISCALL);
    // JSONValue& JSONValue::operator=(const String& rhs) | File: ../Resource/JSONValue.h
    engine->RegisterObjectMethod("JSONValue", "JSONValue& opAssign(const String&in)", asMETHODPR(JSONValue, operator=, (const String&), JSONValue&), asCALL_THISCALL);
    // JSONValue& JSONValue::operator=(const char* rhs) | File: ../Resource/JSONValue.h
    // Error: type "const char*" can not automatically bind
    // JSONValue& JSONValue::operator=(const JSONArray& rhs) | File: ../Resource/JSONValue.h
    // Error: type "const JSONArray&" can not automatically bind
    // JSONValue& JSONValue::operator=(const JSONObject& rhs) | File: ../Resource/JSONValue.h
    // Error: type "const JSONObject&" can not automatically bind
    // JSONValue& JSONValue::operator=(const JSONValue& rhs) | File: ../Resource/JSONValue.h
    engine->RegisterObjectMethod("JSONValue", "JSONValue& opAssign(const JSONValue&in)", asMETHODPR(JSONValue, operator=, (const JSONValue&), JSONValue&), asCALL_THISCALL);
    // JSONValue& JSONValue::operator[](unsigned index) | File: ../Resource/JSONValue.h
    engine->RegisterObjectMethod("JSONValue", "JSONValue& opIndex(uint)", asMETHODPR(JSONValue, operator[], (unsigned), JSONValue&), asCALL_THISCALL);
    // const JSONValue& JSONValue::operator[](unsigned index) const | File: ../Resource/JSONValue.h
    engine->RegisterObjectMethod("JSONValue", "const JSONValue& opIndex(uint) const", asMETHODPR(JSONValue, operator[], (unsigned) const, const JSONValue&), asCALL_THISCALL);
    // JSONValue& JSONValue::operator[](const String& key) | File: ../Resource/JSONValue.h
    engine->RegisterObjectMethod("JSONValue", "JSONValue& opIndex(const String&in)", asMETHODPR(JSONValue, operator[], (const String&), JSONValue&), asCALL_THISCALL);
    // const JSONValue& JSONValue::operator[](const String& key) const | File: ../Resource/JSONValue.h
    engine->RegisterObjectMethod("JSONValue", "const JSONValue& opIndex(const String&in) const", asMETHODPR(JSONValue, operator[], (const String&) const, const JSONValue&), asCALL_THISCALL);
    // void JSONValue::Pop() | File: ../Resource/JSONValue.h
    engine->RegisterObjectMethod("JSONValue", "void Pop()", asMETHODPR(JSONValue, Pop, (), void), asCALL_THISCALL);
    // void JSONValue::Push(const JSONValue& value) | File: ../Resource/JSONValue.h
    engine->RegisterObjectMethod("JSONValue", "void Push(const JSONValue&in)", asMETHODPR(JSONValue, Push, (const JSONValue&), void), asCALL_THISCALL);
    // void JSONValue::Resize(unsigned newSize) | File: ../Resource/JSONValue.h
    engine->RegisterObjectMethod("JSONValue", "void Resize(uint)", asMETHODPR(JSONValue, Resize, (unsigned), void), asCALL_THISCALL);
    // void JSONValue::Set(const String& key, const JSONValue& value) | File: ../Resource/JSONValue.h
    engine->RegisterObjectMethod("JSONValue", "void Set(const String&in, const JSONValue&in)", asMETHODPR(JSONValue, Set, (const String&, const JSONValue&), void), asCALL_THISCALL);
    // void JSONValue::SetType(JSONValueType valueType, JSONNumberType numberType=JSONNT_NAN) | File: ../Resource/JSONValue.h
    engine->RegisterObjectMethod("JSONValue", "void SetType(JSONValueType, JSONNumberType = JSONNT_NAN)", asMETHODPR(JSONValue, SetType, (JSONValueType, JSONNumberType), void), asCALL_THISCALL);
    // void JSONValue::SetVariant(const Variant& variant, Context* context=nullptr) | File: ../Resource/JSONValue.h
    engine->RegisterObjectMethod("JSONValue", "void SetVariant(const Variant&in)", asFUNCTION(JSONValue_SetVariant_Variant_Context), asCALL_CDECL_OBJFIRST);
    // void JSONValue::SetVariantMap(const VariantMap& variantMap, Context* context=nullptr) | File: ../Resource/JSONValue.h
    engine->RegisterObjectMethod("JSONValue", "void SetVariantMap(const VariantMap&in)", asFUNCTION(JSONValue_SetVariantMap_VariantMap_Context), asCALL_CDECL_OBJFIRST);
    // void JSONValue::SetVariantValue(const Variant& variant, Context* context=nullptr) | File: ../Resource/JSONValue.h
    engine->RegisterObjectMethod("JSONValue", "void SetVariantValue(const Variant&in)", asFUNCTION(JSONValue_SetVariantValue_Variant_Context), asCALL_CDECL_OBJFIRST);
    // void JSONValue::SetVariantVector(const VariantVector& variantVector, Context* context=nullptr) | File: ../Resource/JSONValue.h
    // Error: type "const VariantVector&" can not automatically bind
    // unsigned JSONValue::Size() const | File: ../Resource/JSONValue.h
    engine->RegisterObjectMethod("JSONValue", "uint Size() const", asMETHODPR(JSONValue, Size, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("JSONValue", "uint get_size() const", asMETHODPR(JSONValue, Size, () const, unsigned), asCALL_THISCALL);
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
    engine->RegisterObjectMethod("JoystickState", "float GetAxisPosition(uint) const", asMETHODPR(JoystickState, GetAxisPosition, (unsigned) const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("JoystickState", "float get_axisPosition(uint) const", asMETHODPR(JoystickState, GetAxisPosition, (unsigned) const, float), asCALL_THISCALL);
    // bool JoystickState::GetButtonDown(unsigned index) const | File: ../Input/Input.h
    engine->RegisterObjectMethod("JoystickState", "bool GetButtonDown(uint) const", asMETHODPR(JoystickState, GetButtonDown, (unsigned) const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("JoystickState", "bool get_buttonDown(uint) const", asMETHODPR(JoystickState, GetButtonDown, (unsigned) const, bool), asCALL_THISCALL);
    // bool JoystickState::GetButtonPress(unsigned index) const | File: ../Input/Input.h
    engine->RegisterObjectMethod("JoystickState", "bool GetButtonPress(uint) const", asMETHODPR(JoystickState, GetButtonPress, (unsigned) const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("JoystickState", "bool get_buttonPress(uint) const", asMETHODPR(JoystickState, GetButtonPress, (unsigned) const, bool), asCALL_THISCALL);
    // int JoystickState::GetHatPosition(unsigned index) const | File: ../Input/Input.h
    engine->RegisterObjectMethod("JoystickState", "int GetHatPosition(uint) const", asMETHODPR(JoystickState, GetHatPosition, (unsigned) const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("JoystickState", "int get_hatPosition(uint) const", asMETHODPR(JoystickState, GetHatPosition, (unsigned) const, int), asCALL_THISCALL);
    // unsigned JoystickState::GetNumAxes() const | File: ../Input/Input.h
    engine->RegisterObjectMethod("JoystickState", "uint GetNumAxes() const", asMETHODPR(JoystickState, GetNumAxes, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("JoystickState", "uint get_numAxes() const", asMETHODPR(JoystickState, GetNumAxes, () const, unsigned), asCALL_THISCALL);
    // unsigned JoystickState::GetNumButtons() const | File: ../Input/Input.h
    engine->RegisterObjectMethod("JoystickState", "uint GetNumButtons() const", asMETHODPR(JoystickState, GetNumButtons, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("JoystickState", "uint get_numButtons() const", asMETHODPR(JoystickState, GetNumButtons, () const, unsigned), asCALL_THISCALL);
    // unsigned JoystickState::GetNumHats() const | File: ../Input/Input.h
    engine->RegisterObjectMethod("JoystickState", "uint GetNumHats() const", asMETHODPR(JoystickState, GetNumHats, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("JoystickState", "uint get_numHats() const", asMETHODPR(JoystickState, GetNumHats, () const, unsigned), asCALL_THISCALL);
    // void JoystickState::Initialize(unsigned numButtons, unsigned numAxes, unsigned numHats) | File: ../Input/Input.h
    engine->RegisterObjectMethod("JoystickState", "void Initialize(uint, uint, uint)", asMETHODPR(JoystickState, Initialize, (unsigned, unsigned, unsigned), void), asCALL_THISCALL);
    // bool JoystickState::IsController() const | File: ../Input/Input.h
    engine->RegisterObjectMethod("JoystickState", "bool IsController() const", asMETHODPR(JoystickState, IsController, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("JoystickState", "bool get_controller() const", asMETHODPR(JoystickState, IsController, () const, bool), asCALL_THISCALL);
    // void JoystickState::Reset() | File: ../Input/Input.h
    engine->RegisterObjectMethod("JoystickState", "void Reset()", asMETHODPR(JoystickState, Reset, (), void), asCALL_THISCALL);
    // JoystickState& JoystickState::operator=(const JoystickState&) | Possible implicitly-declared
    RegisterImplicitlyDeclaredAssignOperatorIfPossible<JoystickState>(engine, "JoystickState");
    engine->RegisterObjectBehaviour("JoystickState", asBEHAVE_ADDREF, "void f()", asFUNCTION(FakeAddRef), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("JoystickState", asBEHAVE_RELEASE, "void f()", asFUNCTION(FakeReleaseRef), asCALL_CDECL_OBJLAST);
#ifdef REGISTER_MANUAL_PART_JoystickState
    REGISTER_MANUAL_PART_JoystickState(JoystickState, "JoystickState")
#endif

}

}
