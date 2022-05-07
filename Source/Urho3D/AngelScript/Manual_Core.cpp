// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

#include "../Precompiled.h"
#include "../AngelScript/APITemplates.h"

#include "../AngelScript/Manual_Core.h"

namespace Urho3D
{

// This function is called before ASRegisterGenerated()
void ASRegisterManualFirst_Core(asIScriptEngine* engine)
{
    // using VariantMap = HashMap<StringHash, Variant> | File: ../Core/Variant.h
    engine->RegisterObjectType("VariantMap", sizeof(VariantMap), asOBJ_VALUE | asGetTypeTraits<VariantMap>());
    
    // class WeakPtr<RefCounted> | File: ../Container/Ptr.h
    engine->RegisterObjectType("WeakHandle", sizeof(WeakPtr<RefCounted>), asOBJ_VALUE | asOBJ_APP_CLASS_CDAK);
}

// ========================================================================================

// using VariantMap = HashMap<StringHash, Variant> | File: ../Core/Variant.h
// HashMap::HashMap() | File: ../Container/HashMap.h
static void VariantMap_VariantMap(VariantMap* ptr)
{
    new(ptr) VariantMap();
}

// using VariantMap = HashMap<StringHash, Variant> | File: ../Core/Variant.h
// HashMap::HashMap(const HashMap<T, U>& map) | File: ../Container/HashMap.h
static void VariantMap_VariantMap_Copy(const VariantMap& map, VariantMap* ptr)
{
    new(ptr) VariantMap(map);
}

// using VariantMap = HashMap<StringHash, Variant> | File: ../Core/Variant.h
// U& HashMap::operator [](const T& key) | File: ../Container/HashMap.h
static Variant& VariantMap_OperatorBrackets(StringHash key, VariantMap& map)
{
    return map[key];
}

// using VariantMap = HashMap<StringHash, Variant> | File: ../Core/Variant.h
// bool HashMap::Contains(const T& key) const | File: ../Container/HashMap.h
static bool VariantMap_Contains_Hash(StringHash key, VariantMap& map)
{
    return map.Contains(key);
}

// using VariantMap = HashMap<StringHash, Variant> | File: ../Core/Variant.h
// bool HashMap::Erase(const T& key) | File: ../Container/HashMap.h
static bool VariantMap_Erase_Hash(StringHash key, VariantMap& map)
{
    return map.Erase(key);
}

// using VariantMap = HashMap<StringHash, Variant> | File: ../Core/Variant.h
// Vector<T> HashMap::Keys() const | File: ../Container/HashMap.h
static CScriptArray* VariantMap_GetKeys(const VariantMap& map)
{
    return VectorToArray<StringHash>(map.Keys(), "Array<StringHash>");
}

// using VariantMap = HashMap<StringHash, Variant> | File: ../Core/Variant.h
// Vector<U> HashMap::Values() const | File: ../Container/HashMap.h
static CScriptArray* VariantMap_GetValues(const VariantMap& map)
{
    return VectorToArray<Variant>(map.Values(), "Array<Variant>");
}

static void RegisterVariantMap(asIScriptEngine* engine)
{
    // using VariantMap = HashMap<StringHash, Variant> | File: ../Core/Variant.h
    // HashMap::HashMap()| File: ../Container/HashMap.h
    engine->RegisterObjectBehaviour("VariantMap", asBEHAVE_CONSTRUCT, "void f()", AS_FUNCTION_OBJLAST(VariantMap_VariantMap), AS_CALL_CDECL_OBJLAST);

    // using VariantMap = HashMap<StringHash, Variant> | File: ../Core/Variant.h
    // HashMap::HashMap(const HashMap<T, U>& map) | File: ../Container/HashMap.h
    engine->RegisterObjectBehaviour("VariantMap", asBEHAVE_CONSTRUCT, "void f(const VariantMap&in)", AS_FUNCTION_OBJLAST(VariantMap_VariantMap_Copy), AS_CALL_CDECL_OBJLAST);

    // using VariantMap = HashMap<StringHash, Variant> | File: ../Core/Variant.h
    // HashMap::~HashMap() | File: ../Container/HashMap.h
    engine->RegisterObjectBehaviour("VariantMap", asBEHAVE_DESTRUCT, "void f()", AS_DESTRUCTOR(VariantMap), AS_CALL_CDECL_OBJLAST);

    // using VariantMap = HashMap<StringHash, Variant> | File: ../Core/Variant.h
    // unsigned HashBase::Size() const | File: ../Container/HashBase.h
    engine->RegisterObjectMethod("VariantMap", "uint get_length() const", AS_METHOD(VariantMap, Size), AS_CALL_THISCALL);
    
    // using VariantMap = HashMap<StringHash, Variant> | File: ../Core/Variant.h
    // void HashMap::Clear() | File: ../Container/HashMap.h
    engine->RegisterObjectMethod("VariantMap", "void Clear()", AS_METHOD(VariantMap, Clear), AS_CALL_THISCALL);
    
    // using VariantMap = HashMap<StringHash, Variant> | File: ../Core/Variant.h
    // HashMap& operator =(const HashMap<T, U>& rhs) | File: ../Container/HashMap.h
    engine->RegisterObjectMethod("VariantMap", "VariantMap& opAssign(const VariantMap&in)", AS_METHODPR(VariantMap, operator =, (const VariantMap&), VariantMap&), AS_CALL_THISCALL);
    
    // using VariantMap = HashMap<StringHash, Variant> | File: ../Core/Variant.h
    // U& HashMap::operator [](const T& key) | File: ../Container/HashMap.h
    engine->RegisterObjectMethod("VariantMap", "Variant& opIndex(StringHash)", AS_FUNCTION_OBJLAST(VariantMap_OperatorBrackets), AS_CALL_CDECL_OBJLAST);
    
    // using VariantMap = HashMap<StringHash, Variant> | File: ../Core/Variant.h
    // bool HashMap::Contains(const T& key) const | File: ../Container/HashMap.h
    engine->RegisterObjectMethod("VariantMap", "bool Contains(StringHash) const", AS_FUNCTION_OBJLAST(VariantMap_Contains_Hash), AS_CALL_CDECL_OBJLAST);
    
    // using VariantMap = HashMap<StringHash, Variant> | File: ../Core/Variant.h
    // bool HashMap::Erase(const T& key) | File: ../Container/HashMap.h
    engine->RegisterObjectMethod("VariantMap", "bool Erase(StringHash)", AS_FUNCTION_OBJLAST(VariantMap_Erase_Hash), AS_CALL_CDECL_OBJLAST);
    
    // using VariantMap = HashMap<StringHash, Variant> | File: ../Core/Variant.h
    // Vector<T> HashMap::Keys() const | File: ../Container/HashMap.h
    engine->RegisterObjectMethod("VariantMap", "Array<StringHash>@ get_keys() const", AS_FUNCTION_OBJLAST(VariantMap_GetKeys), AS_CALL_CDECL_OBJLAST);
    
    // using VariantMap = HashMap<StringHash, Variant> | File: ../Core/Variant.h
    // Vector<U> HashMap::Values() const | File: ../Container/HashMap.h
    engine->RegisterObjectMethod("VariantMap", "Array<Variant>@ get_values() const", AS_FUNCTION_OBJLAST(VariantMap_GetValues), AS_CALL_CDECL_OBJLAST);
}

// ========================================================================================

// class WeakPtr<RefCounted> | File: ../Container/Ptr.h
// WeakPtr::WeakPtr() noexcept | File: ../Container/Ptr.h
static void WeakPtr_WeakPtr(WeakPtr<RefCounted>* ptr)
{
    new(ptr) WeakPtr<RefCounted>();
}

// class WeakPtr<RefCounted> | File: ../Container/Ptr.h
// WeakPtr::WeakPtr(const WeakPtr<T>& rhs) noexcept | File: ../Container/Ptr.h
static void WeakPtr_WeakPtr_Copy(const WeakPtr<RefCounted>& src, WeakPtr<RefCounted>* ptr)
{
    new(ptr) WeakPtr<RefCounted>(src);
}

// class WeakPtr<RefCounted> | File: ../Container/Ptr.h
// explicit WeakPtr::WeakPtr(T* ptr) noexcept | File: ../Container/Ptr.h
static void WeakPtr_WeakPtr_Ptr(RefCounted* object, WeakPtr<RefCounted>* ptr)
{
    new(ptr) WeakPtr<RefCounted>(object);
}

static void RegisterWeakHandle(asIScriptEngine* engine)
{
    // class WeakPtr<RefCounted> | File: ../Container/Ptr.h
    // WeakPtr::WeakPtr() noexcept | File: ../Container/Ptr.h
    engine->RegisterObjectBehaviour("WeakHandle", asBEHAVE_CONSTRUCT, "void f()", AS_FUNCTION_OBJLAST(WeakPtr_WeakPtr), AS_CALL_CDECL_OBJLAST);
    
    // class WeakPtr<RefCounted> | File: ../Container/Ptr.h
    // WeakPtr::WeakPtr(const WeakPtr<T>& rhs) noexcept | File: ../Container/Ptr.h
    engine->RegisterObjectBehaviour("WeakHandle", asBEHAVE_CONSTRUCT, "void f(const WeakHandle&in)", AS_FUNCTION_OBJLAST(WeakPtr_WeakPtr_Copy), AS_CALL_CDECL_OBJLAST);
    
    // class WeakPtr<RefCounted> | File: ../Container/Ptr.h
    // explicit WeakPtr::WeakPtr(T* ptr) noexcept | File: ../Container/Ptr.h
    engine->RegisterObjectBehaviour("WeakHandle", asBEHAVE_CONSTRUCT, "void f(RefCounted@+)", AS_FUNCTION_OBJLAST(WeakPtr_WeakPtr_Ptr), AS_CALL_CDECL_OBJLAST);
    
    // class WeakPtr<RefCounted> | File: ../Container/Ptr.h
    // WeakPtr::~WeakPtr() noexcept | File: ../Container/Ptr.h
    engine->RegisterObjectBehaviour("WeakHandle", asBEHAVE_DESTRUCT, "void f()", AS_DESTRUCTOR(WeakPtr<RefCounted>), AS_CALL_CDECL_OBJLAST);
    
    // class WeakPtr<RefCounted> | File: ../Container/Ptr.h
    // WeakPtr<T>& WeakPtr::operator =(const WeakPtr<T>& rhs) | File: ../Container/Ptr.h
    engine->RegisterObjectMethod("WeakHandle", "WeakHandle& opAssign(const WeakHandle&in)", AS_METHODPR(WeakPtr<RefCounted>, operator =, (const WeakPtr<RefCounted>&), WeakPtr<RefCounted>&), AS_CALL_THISCALL);
    
    // class WeakPtr<RefCounted> | File: ../Container/Ptr.h
    // WeakPtr<T>& WeakPtr::operator =(T* ptr) | File: ../Container/Ptr.h
    engine->RegisterObjectMethod("WeakHandle", "WeakHandle& opAssign(RefCounted@+)", AS_METHODPR(WeakPtr<RefCounted>, operator =, (RefCounted*), WeakPtr<RefCounted>&), AS_CALL_THISCALL);
    
    // class WeakPtr<RefCounted> | File: ../Container/Ptr.h
    // T* WeakPtr::Get() const | File: ../Container/Ptr.h
    engine->RegisterObjectMethod("WeakHandle", "RefCounted@+ Get() const", AS_METHODPR(WeakPtr<RefCounted>, Get, () const, RefCounted*), AS_CALL_THISCALL);
    
    // class WeakPtr<RefCounted> | File: ../Container/Ptr.h
    // int WeakPtr::Refs() const | File: ../Container/Ptr.h
    engine->RegisterObjectMethod("WeakHandle", "int get_refs() const", AS_METHOD(WeakPtr<RefCounted>, Refs), AS_CALL_THISCALL);
    
    // class WeakPtr<RefCounted> | File: ../Container/Ptr.h
    // int WeakPtr::WeakRefs() const | File: ../Container/Ptr.h
    engine->RegisterObjectMethod("WeakHandle", "int get_weakRefs() const", AS_METHOD(WeakPtr<RefCounted>, WeakRefs), AS_CALL_THISCALL);
    
    // class WeakPtr<RefCounted> | File: ../Container/Ptr.h
    // bool WeakPtr::Expired() const | File: ../Container/Ptr.h
    engine->RegisterObjectMethod("WeakHandle", "bool get_expired() const", AS_METHOD(WeakPtr<RefCounted>, Expired), AS_CALL_THISCALL);
}

// ========================================================================================

void ArrayToVariantVector(CScriptArray* arr, VariantVector& dest);
void ArrayToStringVector(CScriptArray* arr, StringVector& dest);

static void Variant_Variant_ScriptObject(asIScriptObject* value, Variant* ptr)
{
    if (value)
    {
        asITypeInfo* scriptObjectInterface = value->GetEngine()->GetTypeInfoByName("ScriptObject");
        if (value->GetObjectType()->Implements(scriptObjectInterface))
            new(ptr) Variant(value);
        else
            new(ptr) Variant();
    }
    else
        new(ptr) Variant();
}

static asIScriptObject* Variant_GetScriptObject(Variant* ptr)
{
    auto* object = static_cast<asIScriptObject*>(ptr->GetVoidPtr());
    if (!object)
        return nullptr;

    asITypeInfo* scriptObjectInterface = object->GetEngine()->GetTypeInfoByName("ScriptObject");
    if (!object->GetObjectType()->Implements(scriptObjectInterface))
        return nullptr;

    return object;
}

// Variant::Variant(const VariantVector& value) | File: ../Core/Variant.h
static void Variant_Variant_VariantVector(CScriptArray* value, Variant* ptr)
{
    VariantVector vector;
    ArrayToVariantVector(value, vector);
    new(ptr) Variant(vector);
}

/* TODO: Check
// Variant::Variant(const StringVector& value) | File: ../Core/Variant.h
static void Variant_Variant_StringVector(CScriptArray* value, Variant* ptr)
{
    StringVector vector;
    ArrayToStringVector(value, vector);
    new(ptr) Variant(vector);
}
*/

// Variant& Variant::operator =(const VariantVector& rhs) | File: ../Core/Variant.h
static Variant& Variant_OperatorAssign_VariantVector(CScriptArray* value, Variant* ptr)
{
    VariantVector vector;
    ArrayToVariantVector(value, vector);
    *ptr = vector;
    return *ptr;
}

/* TODO: Check
// Variant& Variant::operator =(const StringVector& rhs) | File: ../Core/Variant.h
static Variant& Variant_OperatorAssign_StringVector(CScriptArray* value, Variant* ptr)
{
    StringVector vector;
    ArrayToStringVector(value, vector);
    *ptr = vector;
    return *ptr;
}
*/

// bool Variant::operator ==(const VariantVector& rhs) const | File: ../Core/Variant.h
static bool Variant_OperatorEquals_VariantVector(CScriptArray* value, Variant* ptr)
{
    VariantVector vector;
    ArrayToVariantVector(value, vector);
    return *ptr == vector;
}

/* TODO: Check
// bool Variant::operator ==(const StringVector& rhs) const | File: ../Core/Variant.h
static bool Variant_OperatorEquals_StringVector(CScriptArray* value, Variant* ptr)
{
    StringVector vector;
    ArrayToStringVector(value, vector);
    return *ptr == vector;
}
*/

// const VariantVector& Variant::GetVariantVector() const | File: ../Core/Variant.h
static CScriptArray* Variant_GetVariantVector(Variant* ptr)
{
    return VectorToArray<Variant>(ptr->GetVariantVector(), "Array<Variant>");
}

static void RegisterVariant(asIScriptEngine* engine)
{
    engine->RegisterObjectBehaviour("Variant", asBEHAVE_CONSTRUCT, "void f(ScriptObject@+)", AS_FUNCTION_OBJLAST(Variant_Variant_ScriptObject), AS_CALL_CDECL_OBJLAST);
    
    engine->RegisterObjectMethod("Variant", "ScriptObject@+ GetScriptObject() const", AS_FUNCTION_OBJLAST(Variant_GetScriptObject), AS_CALL_CDECL_OBJLAST);

    // Variant::Variant(const VariantVector& value) | File: ../Core/Variant.h
    engine->RegisterObjectBehaviour("Variant", asBEHAVE_CONSTRUCT, "void f(const Array<Variant>@+)", AS_FUNCTION_OBJLAST(Variant_Variant_VariantVector), AS_CALL_CDECL_OBJLAST);

    // Variant::Variant(const StringVector& value) | File: ../Core/Variant.h
    //engine->RegisterObjectBehaviour("Variant", asBEHAVE_CONSTRUCT, "void f(const Array<String>@+)", AS_FUNCTION_OBJLAST(Variant_Variant_StringVector), AS_CALL_CDECL_OBJLAST);

    // Variant& Variant::operator =(void* rhs) | File: ../Core/Variant.h
    engine->RegisterObjectMethod("Variant", "Variant& opAssign(ScriptObject@+)", AS_METHODPR(Variant, operator=, (void*), Variant&), AS_CALL_THISCALL);
    
    // bool Variant::operator ==(void* rhs) const | File: ../Core/Variant.h
    engine->RegisterObjectMethod("Variant", "bool opEquals(ScriptObject@+) const", AS_METHODPR(Variant, operator==, (void*) const, bool), AS_CALL_THISCALL);
    
    // Variant& Variant::operator =(const VariantVector& rhs) | File: ../Core/Variant.h
    engine->RegisterObjectMethod("Variant", "Variant& opAssign(const Array<Variant>@+)", AS_FUNCTION_OBJLAST(Variant_OperatorAssign_VariantVector), AS_CALL_CDECL_OBJLAST);
    
    // Variant& Variant::operator =(const StringVector& rhs) | File: ../Core/Variant.h
    //engine->RegisterObjectMethod("Variant", "Variant& opAssign(const Array<String>@+)", AS_FUNCTION_OBJLAST(Variant_OperatorAssign_StringVector), AS_CALL_CDECL_OBJLAST);
    
    // bool Variant::operator ==(const VariantVector& rhs) const | File: ../Core/Variant.h
    engine->RegisterObjectMethod("Variant", "bool opEquals(const Array<Variant>@+)", AS_FUNCTION_OBJLAST(Variant_OperatorEquals_VariantVector), AS_CALL_CDECL_OBJLAST);
    
    // bool Variant::operator ==(const StringVector& rhs) const | File: ../Core/Variant.h
    //engine->RegisterObjectMethod("Variant", "bool opEquals(const Array<String>@+)", AS_FUNCTION_OBJLAST(Variant_OperatorEquals_StringVector), AS_CALL_CDECL_OBJLAST);
    
    // const VariantVector& Variant::GetVariantVector() const | File: ../Core/Variant.h
    engine->RegisterObjectMethod("Variant", "Array<Variant>@ GetVariantVector() const", AS_FUNCTION_OBJLAST(Variant_GetVariantVector), AS_CALL_CDECL_OBJLAST);
    
    // VectorBuffer Variant::GetVectorBuffer() const | File: ../Core/Variant.h
    engine->RegisterObjectMethod("Variant", "VectorBuffer GetBuffer() const", AS_METHOD(Variant, GetVectorBuffer), AS_CALL_THISCALL);
}

// ========================================================================================

// static unsigned Time::GetSystemTime() | File: ../Core/Timer.h
unsigned Time_GetSystemTime(Time* time)
{
    return Time::GetSystemTime();
}

// static unsigned Time::GetTimeSinceEpoch() | File: ../Core/Timer.h
unsigned Time_GetTimeSinceEpoch(Time* time)
{
    return Time::GetTimeSinceEpoch();
}

// static String Time::GetTimeStamp() | File: ../Core/Timer.h
String Time_GetTimeStamp(Time* time)
{
    return Time::GetTimeStamp();
}

static void RegisterTime(asIScriptEngine* engine)
{
    // static unsigned Time::GetSystemTime() | File: ../Core/Timer.h
    engine->RegisterObjectMethod("Time", "uint get_systemTime() const", AS_FUNCTION_OBJLAST(Time_GetSystemTime), AS_CALL_CDECL_OBJLAST);

    // static unsigned Time::GetTimeSinceEpoch() | File: ../Core/Timer.h
    engine->RegisterObjectMethod("Time", "uint get_timeSinceEpoch() const", AS_FUNCTION_OBJLAST(Time_GetTimeSinceEpoch), AS_CALL_CDECL_OBJLAST);

    // static String Time::GetTimeStamp() | File: ../Core/Timer.h */
    engine->RegisterObjectMethod("Time", "String get_timeStamp() const", AS_FUNCTION_OBJLAST(Time_GetTimeStamp), AS_CALL_CDECL_OBJLAST);
}

// ========================================================================================

// template <class T> T* Context::GetSubsystem() const | File: ../Core/Context.h
static Time* GetTime()
{
    return GetScriptContext()->GetSubsystem<Time>();
}

// This function is called after ASRegisterGenerated()
void ASRegisterManualLast_Core(asIScriptEngine* engine)
{
    RegisterVariantMap(engine);
    RegisterWeakHandle(engine);
    RegisterVariant(engine);
    RegisterTime(engine);

    // template <class T> T* Context::GetSubsystem() const | File: ../Core/Context.h
    engine->RegisterGlobalFunction("Time@+ get_time()", AS_FUNCTION(GetTime), AS_CALL_CDECL);
}

}
