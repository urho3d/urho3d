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

#include "../AngelScript/Manual_Core.h"

namespace Urho3D
{

// This function is called before ASRegisterGenerated()
void ASRegisterManualFirst_Core(asIScriptEngine* engine)
{
    // using VariantMap = HashMap<StringHash, Variant> | File: ../Core/Variant.h
    engine->RegisterObjectType("VariantMap", sizeof(VariantMap), asOBJ_VALUE | asGetTypeTraits<VariantMap>());
    // WeakPtr<RefCounted> | File: ../Container/Ptr.h
    engine->RegisterObjectType("WeakHandle", sizeof(WeakPtr<RefCounted>), asOBJ_VALUE | asOBJ_APP_CLASS_CDAK);
}

// ========================================================================================

// using VariantMap = HashMap<StringHash, Variant> | File: ../Core/Variant.h
// HashMap::HashMap()| File: ../Container/HashMap.h
static void ConstructVariantMap(VariantMap* ptr)
{
    new(ptr) VariantMap();
}

// using VariantMap = HashMap<StringHash, Variant> | File: ../Core/Variant.h
// HashMap::HashMap(const HashMap<T, U>& map) | File: ../Container/HashMap.h
static void ConstructVariantMapCopy(const VariantMap& map, VariantMap* ptr)
{
    new(ptr) VariantMap(map);
}

// using VariantMap = HashMap<StringHash, Variant> | File: ../Core/Variant.h
// U& HashMap::operator [](const T& key) | File: ../Container/HashMap.h
static Variant& VariantMapAtHash(StringHash key, VariantMap& map)
{
    return map[key];
}

// using VariantMap = HashMap<StringHash, Variant> | File: ../Core/Variant.h
// bool HashMap::Contains(const T& key) const | File: ../Container/HashMap.h
static bool VariantMapContainsHash(StringHash key, VariantMap& map)
{
    return map.Contains(key);
}

// using VariantMap = HashMap<StringHash, Variant> | File: ../Core/Variant.h
// bool HashMap::Erase(const T& key) | File: ../Container/HashMap.h
static bool VariantMapEraseHash(StringHash key, VariantMap& map)
{
    return map.Erase(key);
}

// using VariantMap = HashMap<StringHash, Variant> | File: ../Core/Variant.h
// Vector<T> HashMap::Keys() const | File: ../Container/HashMap.h
static CScriptArray* VariantMapGetKeys(const VariantMap& map)
{
    return VectorToArray<StringHash>(map.Keys(), "Array<StringHash>");
}

// using VariantMap = HashMap<StringHash, Variant> | File: ../Core/Variant.h
// Vector<U> HashMap::Values() const | File: ../Container/HashMap.h
static CScriptArray* VariantMapGetValues(const VariantMap& map)
{
    return VectorToArray<Variant>(map.Values(), "Array<Variant>");
}

static void RegisterVariantMap(asIScriptEngine* engine)
{
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
    // HashMap::HashMap()| File: ../Container/HashMap.h
    engine->RegisterObjectBehaviour("VariantMap", asBEHAVE_CONSTRUCT, "void f()", AS_FUNCTION_OBJLAST(ConstructVariantMap), AS_CALL_CDECL_OBJLAST);
    // using VariantMap = HashMap<StringHash, Variant> | File: ../Core/Variant.h
    // HashMap::HashMap(const HashMap<T, U>& map) | File: ../Container/HashMap.h
    engine->RegisterObjectBehaviour("VariantMap", asBEHAVE_CONSTRUCT, "void f(const VariantMap&in)", AS_FUNCTION_OBJLAST(ConstructVariantMapCopy), AS_CALL_CDECL_OBJLAST);
    // using VariantMap = HashMap<StringHash, Variant> | File: ../Core/Variant.h
    // HashMap::~HashMap() | File: ../Container/HashMap.h
    engine->RegisterObjectBehaviour("VariantMap", asBEHAVE_DESTRUCT, "void f()", AS_DESTRUCTOR(VariantMap), AS_CALL_CDECL_OBJLAST);
    // using VariantMap = HashMap<StringHash, Variant> | File: ../Core/Variant.h
    // U& HashMap::operator [](const T& key) | File: ../Container/HashMap.h
    engine->RegisterObjectMethod("VariantMap", "Variant& opIndex(StringHash)", AS_FUNCTION_OBJLAST(VariantMapAtHash), AS_CALL_CDECL_OBJLAST);
    // using VariantMap = HashMap<StringHash, Variant> | File: ../Core/Variant.h
    // bool HashMap::Contains(const T& key) const | File: ../Container/HashMap.h
    engine->RegisterObjectMethod("VariantMap", "bool Contains(StringHash) const", AS_FUNCTION_OBJLAST(VariantMapContainsHash), AS_CALL_CDECL_OBJLAST);
    // using VariantMap = HashMap<StringHash, Variant> | File: ../Core/Variant.h
    // bool HashMap::Erase(const T& key) | File: ../Container/HashMap.h
    engine->RegisterObjectMethod("VariantMap", "bool Erase(StringHash)", AS_FUNCTION_OBJLAST(VariantMapEraseHash), AS_CALL_CDECL_OBJLAST);
    // using VariantMap = HashMap<StringHash, Variant> | File: ../Core/Variant.h
    // Vector<T> HashMap::Keys() const | File: ../Container/HashMap.h
    engine->RegisterObjectMethod("VariantMap", "Array<StringHash>@ get_keys() const", AS_FUNCTION_OBJLAST(VariantMapGetKeys), AS_CALL_CDECL_OBJLAST);
    // using VariantMap = HashMap<StringHash, Variant> | File: ../Core/Variant.h
    // Vector<U> HashMap::Values() const | File: ../Container/HashMap.h
    engine->RegisterObjectMethod("VariantMap", "Array<Variant>@ get_values() const", AS_FUNCTION_OBJLAST(VariantMapGetValues), AS_CALL_CDECL_OBJLAST);
}

// ========================================================================================

// WeakPtr<RefCounted> | File: ../Container/Ptr.h
// WeakPtr::WeakPtr() noexcept | File: ../Container/Ptr.h
static void ConstructWeakHandle(WeakPtr<RefCounted>* ptr)
{
    new(ptr) WeakPtr<RefCounted>();
}

// WeakPtr<RefCounted> | File: ../Container/Ptr.h
// WeakPtr::WeakPtr(const WeakPtr<T>& rhs) noexcept | File: ../Container/Ptr.h
static void ConstructWeakHandleCopy(const WeakPtr<RefCounted>& src, WeakPtr<RefCounted>* ptr)
{
    new(ptr) WeakPtr<RefCounted>(src);
}

// WeakPtr<RefCounted> | File: ../Container/Ptr.h
// explicit WeakPtr::WeakPtr(T* ptr) noexcept | File: ../Container/Ptr.h
static void ConstructWeakHandlePtr(RefCounted* object, WeakPtr<RefCounted>* ptr)
{
    new(ptr) WeakPtr<RefCounted>(object);
}

static void RegisterWeakHandle(asIScriptEngine* engine)
{
    // WeakPtr<RefCounted> | File: ../Container/Ptr.h
    // WeakPtr::WeakPtr() noexcept | File: ../Container/Ptr.h
    engine->RegisterObjectBehaviour("WeakHandle", asBEHAVE_CONSTRUCT, "void f()", AS_FUNCTION_OBJLAST(ConstructWeakHandle), AS_CALL_CDECL_OBJLAST);
    // WeakPtr<RefCounted> | File: ../Container/Ptr.h
    // WeakPtr::WeakPtr(const WeakPtr<T>& rhs) noexcept | File: ../Container/Ptr.h
    engine->RegisterObjectBehaviour("WeakHandle", asBEHAVE_CONSTRUCT, "void f(const WeakHandle&in)", AS_FUNCTION_OBJLAST(ConstructWeakHandleCopy), AS_CALL_CDECL_OBJLAST);
    // WeakPtr<RefCounted> | File: ../Container/Ptr.h
    // explicit WeakPtr::WeakPtr(T* ptr) noexcept | File: ../Container/Ptr.h
    engine->RegisterObjectBehaviour("WeakHandle", asBEHAVE_CONSTRUCT, "void f(RefCounted@+)", AS_FUNCTION_OBJLAST(ConstructWeakHandlePtr), AS_CALL_CDECL_OBJLAST);
    // WeakPtr<RefCounted> | File: ../Container/Ptr.h
    // WeakPtr::~WeakPtr() noexcept | File: ../Container/Ptr.h
    engine->RegisterObjectBehaviour("WeakHandle", asBEHAVE_DESTRUCT, "void f()", AS_DESTRUCTOR(WeakPtr<RefCounted>), AS_CALL_CDECL_OBJLAST);
    // WeakPtr<RefCounted> | File: ../Container/Ptr.h
    // WeakPtr<T>& WeakPtr::operator =(const WeakPtr<T>& rhs) | File: ../Container/Ptr.h
    engine->RegisterObjectMethod("WeakHandle", "WeakHandle& opAssign(const WeakHandle&in)", AS_METHODPR(WeakPtr<RefCounted>, operator =, (const WeakPtr<RefCounted>&), WeakPtr<RefCounted>&), AS_CALL_THISCALL);
    // WeakPtr<RefCounted> | File: ../Container/Ptr.h
    // WeakPtr<T>& WeakPtr::operator =(T* ptr) | File: ../Container/Ptr.h
    engine->RegisterObjectMethod("WeakHandle", "WeakHandle& opAssign(RefCounted@+)", AS_METHODPR(WeakPtr<RefCounted>, operator =, (RefCounted*), WeakPtr<RefCounted>&), AS_CALL_THISCALL);
    // WeakPtr<RefCounted> | File: ../Container/Ptr.h
    // T* WeakPtr::Get() const | File: ../Container/Ptr.h
    engine->RegisterObjectMethod("WeakHandle", "RefCounted@+ Get() const", AS_METHODPR(WeakPtr<RefCounted>, Get, () const, RefCounted*), AS_CALL_THISCALL);
    // WeakPtr<RefCounted> | File: ../Container/Ptr.h
    // int WeakPtr::Refs() const | File: ../Container/Ptr.h
    engine->RegisterObjectMethod("WeakHandle", "int get_refs() const", AS_METHOD(WeakPtr<RefCounted>, Refs), AS_CALL_THISCALL);
    // WeakPtr<RefCounted> | File: ../Container/Ptr.h
    // int WeakPtr::WeakRefs() const | File: ../Container/Ptr.h
    engine->RegisterObjectMethod("WeakHandle", "int get_weakRefs() const", AS_METHOD(WeakPtr<RefCounted>, WeakRefs), AS_CALL_THISCALL);
    // WeakPtr<RefCounted> | File: ../Container/Ptr.h
    // bool WeakPtr::Expired() const | File: ../Container/Ptr.h
    engine->RegisterObjectMethod("WeakHandle", "bool get_expired() const", AS_METHOD(WeakPtr<RefCounted>, Expired), AS_CALL_THISCALL);
}

// ========================================================================================

void ArrayToVariantVector(CScriptArray* arr, VariantVector& dest);
void ArrayToStringVector(CScriptArray* arr, StringVector& dest);

// Variant::Variant(const VariantVector &value) | File: ../Core/Variant.h
static void ConstructVariantVariantVector(CScriptArray* value, Variant* ptr)
{
    VariantVector vector;
    ArrayToVariantVector(value, vector);
    new(ptr) Variant(vector);
}

// Variant::Variant(const StringVector &value) | File: ../Core/Variant.h
static void ConstructVariantStringVector(CScriptArray* value, Variant* ptr)
{
    StringVector vector;
    ArrayToStringVector(value, vector);
    new(ptr) Variant(vector);
}

// Variant& Variant::operator=(const VariantVector &rhs) | File: ../Core/Variant.h
static Variant& VariantAssignVariantVector(CScriptArray* value, Variant* ptr)
{
    VariantVector vector;
    ArrayToVariantVector(value, vector);
    *ptr = vector;
    return *ptr;
}

// Variant& Variant::operator=(const StringVector &rhs) | File: ../Core/Variant.h
static Variant& VariantAssignStringVector(CScriptArray* value, Variant* ptr)
{
    StringVector vector;
    ArrayToStringVector(value, vector);
    *ptr = vector;
    return *ptr;
}

// bool Variant::operator==(const VariantVector &rhs) const | File: ../Core/Variant.h
static bool VariantEqualsVariantVector(CScriptArray* value, Variant* ptr)
{
    VariantVector vector;
    ArrayToVariantVector(value, vector);
    return *ptr == vector;
}

// bool Variant::operator==(const StringVector &rhs) const | File: ../Core/Variant.h
static bool VariantEqualsStringVector(CScriptArray* value, Variant* ptr)
{
    StringVector vector;
    ArrayToStringVector(value, vector);
    return *ptr == vector;
}

// const VariantVector& Variant::GetVariantVector() const | File: ../Core/Variant.h
static CScriptArray* VariantGetVariantVector(Variant* ptr)
{
    return VectorToArray<Variant>(ptr->GetVariantVector(), "Array<Variant>");
}

static void ConstructVariantScriptObject(asIScriptObject* value, Variant* ptr)
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

static asIScriptObject* VariantGetScriptObject(Variant* ptr)
{
    auto* object = static_cast<asIScriptObject*>(ptr->GetVoidPtr());
    if (!object)
        return nullptr;

    asITypeInfo* scriptObjectInterface = object->GetEngine()->GetTypeInfoByName("ScriptObject");
    if (!object->GetObjectType()->Implements(scriptObjectInterface))
        return nullptr;

    return object;
}

static void RegisterVariant(asIScriptEngine* engine)
{
    engine->RegisterObjectBehaviour("Variant", asBEHAVE_CONSTRUCT, "void f(ScriptObject@+)", AS_FUNCTION_OBJLAST(ConstructVariantScriptObject), AS_CALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("Variant", "ScriptObject@+ GetScriptObject() const", AS_FUNCTION_OBJLAST(VariantGetScriptObject), AS_CALL_CDECL_OBJLAST);
    // Variant& Variant::operator=(void *rhs) | File: ../Core/Variant.h
    engine->RegisterObjectMethod("Variant", "Variant& opAssign(ScriptObject@+)", AS_METHODPR(Variant, operator =, (void*), Variant&), AS_CALL_THISCALL);
    // bool Variant::operator==(void *rhs) const | File: ../Core/Variant.h
    engine->RegisterObjectMethod("Variant", "bool opEquals(ScriptObject@+) const", AS_METHODPR(Variant, operator ==, (void*) const, bool), AS_CALL_THISCALL);
    // Variant::Variant(const VariantVector &value) | File: ../Core/Variant.h
    engine->RegisterObjectBehaviour("Variant", asBEHAVE_CONSTRUCT, "void f(const Array<Variant>@+)", AS_FUNCTION_OBJLAST(ConstructVariantVariantVector), AS_CALL_CDECL_OBJLAST);
    // Variant::Variant(const StringVector &value) | File: ../Core/Variant.h
    engine->RegisterObjectBehaviour("Variant", asBEHAVE_CONSTRUCT, "void f(const Array<String>@+)", AS_FUNCTION_OBJLAST(ConstructVariantStringVector), AS_CALL_CDECL_OBJLAST);
    // Variant& Variant::operator=(const VariantVector &rhs) | File: ../Core/Variant.h
    engine->RegisterObjectMethod("Variant", "Variant& opAssign(const Array<Variant>@+)", AS_FUNCTION_OBJLAST(VariantAssignVariantVector), AS_CALL_CDECL_OBJLAST);
    // Variant& Variant::operator=(const StringVector &rhs) | File: ../Core/Variant.h
    engine->RegisterObjectMethod("Variant", "Variant& opAssign(const Array<String>@+)", AS_FUNCTION_OBJLAST(VariantAssignStringVector), AS_CALL_CDECL_OBJLAST);
    // bool Variant::operator==(const VariantVector &rhs) const | File: ../Core/Variant.h
    engine->RegisterObjectMethod("Variant", "bool opEquals(const Array<Variant>@+)", AS_FUNCTION_OBJLAST(VariantEqualsVariantVector), AS_CALL_CDECL_OBJLAST);
    // bool Variant::operator==(const StringVector &rhs) const | File: ../Core/Variant.h
    engine->RegisterObjectMethod("Variant", "bool opEquals(const Array<String>@+)", AS_FUNCTION_OBJLAST(VariantEqualsStringVector), AS_CALL_CDECL_OBJLAST);
    // const VariantVector& Variant::GetVariantVector() const | File: ../Core/Variant.h
    engine->RegisterObjectMethod("Variant", "Array<Variant>@ GetVariantVector() const", AS_FUNCTION_OBJLAST(VariantGetVariantVector), AS_CALL_CDECL_OBJLAST);
    // VectorBuffer Variant::GetVectorBuffer() const | File: ../Core/Variant.h
    engine->RegisterObjectMethod("Variant", "VectorBuffer GetBuffer() const", AS_METHOD(Variant, GetVectorBuffer), AS_CALL_THISCALL);
}

// ========================================================================================

// template<class T> T * Object::GetSubsystem() const | File: ../Core/Object.h
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

    // template<class T> T * Object::GetSubsystem() const | File: ../Core/Object.h
    engine->RegisterGlobalFunction("Time@+ get_time()", AS_FUNCTION(GetTime), AS_CALL_CDECL);
}

// ========================================================================================

// const char** AttributeInfo::enumNames_ | File: ../Core/Attribute.h
CScriptArray* AttributeInfoGetEnumNames(AttributeInfo* ptr)
{
    Vector<String> enumNames;
    const char** enumNamePtrs = ptr->enumNames_;
    while (enumNamePtrs && *enumNamePtrs)
        enumNames.Push(*enumNamePtrs++);
    return VectorToArray<String>(enumNames, "Array<String>");
}

// ========================================================================================

// StringVector ResourceRefList::names_ | File: ../Core/Variant.h
void ResourceRefListResize(unsigned size, ResourceRefList* ptr)
{
    ptr->names_.Resize(size);
}

// StringVector ResourceRefList::names_ | File: ../Core/Variant.h
unsigned ResourceRefListGetSize(ResourceRefList* ptr)
{
    return ptr->names_.Size();
}

// StringVector ResourceRefList::names_ | File: ../Core/Variant.h
bool ResourceRefListIsEmpty(ResourceRefList* ptr)
{
    return ptr->names_.Size() == 0;
}

// StringVector ResourceRefList::names_ | File: ../Core/Variant.h
void ResourceRefListSetName(unsigned index, const String& name, ResourceRefList* ptr)
{
    if (index >= ptr->names_.Size())
    {
        asGetActiveContext()->SetException("Index out of bounds");
        return;
    }

    ptr->names_[index] = name;
}

// StringVector ResourceRefList::names_ | File: ../Core/Variant.h
const String& ResourceRefListGetName(unsigned index, ResourceRefList* ptr)
{
    if (index >= ptr->names_.Size())
    {
        asGetActiveContext()->SetException("Index out of bounds");
        return String::EMPTY;
    }

    return ptr->names_[index];
}

// ========================================================================================

// explicit Spline::Spline(const Vector< Variant > &knots, InterpolationMode mode=BEZIER_CURVE) | File: ../Core/Spline.h
void ConstructSpline(CScriptArray* arr, InterpolationMode mode, Spline* ptr)
{
    new(ptr) Spline(ArrayToVector<Variant>(arr), mode);
}

// const VariantVector& Spline::GetKnots() const | File: ../Core/Spline.h
CScriptArray* GetSplineKnots(Spline* ptr)
{
    return VectorToArray(ptr->GetKnots(), "Array<Variant>");
}

// void Spline::SetKnots(const Vector< Variant > &knots) | File: ../Core/Spline.h
void SetSplineKnots(CScriptArray* arr, Spline* ptr)
{
    ptr->SetKnots(ArrayToVector<Variant>(arr));
}

// void Spline::SetKnot(const Variant &knot, unsigned index) | File: ../Core/Spline.h
void SetSplineKnot(unsigned index, const Variant& in, Spline* ptr)
{
    ptr->SetKnot(in, index);
}

// ========================================================================================

// static unsigned GetSystemTime() | File: ../Core/Timer.h
unsigned TimeGetSystemTime(Time* time)
{
    return Time::GetSystemTime();
}

// static unsigned GetTimeSinceEpoch() | File: ../Core/Timer.h
unsigned TimeGetTimeSinceEpoch(Time* time)
{
    return Time::GetTimeSinceEpoch();
}

// static String GetTimeStamp() | File: ../Core/Timer.h
String TimeGetTimeStamp(Time* time)
{
    return Time::GetTimeStamp();
}

}
