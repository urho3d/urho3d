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

#include "../Core/Variant.h"

namespace Urho3D
{

// This function is called before ASRegisterGenerated()
void ASRegisterManualFirst_Core(asIScriptEngine* engine)
{
    // using VariantMap = HashMap<StringHash, Variant> | File: ../Core/Variant.h
    engine->RegisterObjectType("VariantMap", sizeof(VariantMap), asOBJ_VALUE | asGetTypeTraits<VariantMap>());
}
    
// using VariantMap = HashMap<StringHash, Variant> | File: ../Core/Variant.h
static void VariantMap_Constructor(VariantMap* ptr)
{
    new(ptr) VariantMap();
}

// using VariantMap = HashMap<StringHash, Variant> | File: ../Core/Variant.h
static void VariantMap_CopyConstructor(const VariantMap& map, VariantMap* ptr)
{
    new(ptr) VariantMap(map);
}

// using VariantMap = HashMap<StringHash, Variant> | File: ../Core/Variant.h
static void VariantMap_Destructor(VariantMap* ptr)
{
    ptr->~VariantMap();
}

// using VariantMap = HashMap<StringHash, Variant> | File: ../Core/Variant.h
static Variant& VariantMap_At(const String& key, VariantMap& map)
{
    return map[key];
}

// using VariantMap = HashMap<StringHash, Variant> | File: ../Core/Variant.h
static Variant& VariantMap_AtHash(StringHash key, VariantMap& map)
{
    return map[key];
}

// using VariantMap = HashMap<StringHash, Variant> | File: ../Core/Variant.h
static bool VariantMap_Contains(const String& key, VariantMap& map)
{
    return map.Contains(key);
}

// using VariantMap = HashMap<StringHash, Variant> | File: ../Core/Variant.h
static bool VariantMap_Erase(const String& key, VariantMap& map)
{
    return map.Erase(key);
}

// using VariantMap = HashMap<StringHash, Variant> | File: ../Core/Variant.h
static bool VariantMap_ContainsHash(StringHash key, VariantMap& map)
{
    return map.Contains(key);
}

// using VariantMap = HashMap<StringHash, Variant> | File: ../Core/Variant.h
static bool VariantMap_EraseHash(StringHash key, VariantMap& map)
{
    return map.Erase(key);
}

// using VariantMap = HashMap<StringHash, Variant> | File: ../Core/Variant.h
static CScriptArray* VariantMap_GetKeys(const VariantMap& map)
{
    return VectorToArray<StringHash>(map.Keys(), "Array<StringHash>");
}

// using VariantMap = HashMap<StringHash, Variant> | File: ../Core/Variant.h
static CScriptArray* VariantMap_GetValues(const VariantMap& map)
{
    return VectorToArray<Variant>(map.Values(), "Array<Variant>");
}

// StringVector ResourceRefList::names_ | File: ../Core/Variant.h
static void ResourceRefListResize(unsigned size, ResourceRefList* ptr)
{
    ptr->names_.Resize(size);
}

// StringVector ResourceRefList::names_ | File: ../Core/Variant.h
static unsigned ResourceRefListGetSize(ResourceRefList* ptr)
{
    return ptr->names_.Size();
}

// StringVector ResourceRefList::names_ | File: ../Core/Variant.h
static bool ResourceRefListIsEmpty(ResourceRefList* ptr)
{
    return ptr->names_.Size() == 0;
}

// StringVector ResourceRefList::names_ | File: ../Core/Variant.h
static void ResourceRefListSetName(unsigned index, const String& name, ResourceRefList* ptr)
{
    if (index >= ptr->names_.Size())
    {
        asGetActiveContext()->SetException("Index out of bounds");
        return;
    }

    ptr->names_[index] = name;
}

// StringVector ResourceRefList::names_ | File: ../Core/Variant.h
static const String& ResourceRefListGetName(unsigned index, ResourceRefList* ptr)
{
    if (index >= ptr->names_.Size())
    {
        asGetActiveContext()->SetException("Index out of bounds");
        return String::EMPTY;
    }

    return ptr->names_[index];
}


void ArrayToVariantVector(CScriptArray* arr, VariantVector& dest);

static void ConstructVariantVariantVector(CScriptArray* value, Variant* ptr)
{
    VariantVector vector;
    ArrayToVariantVector(value, vector);
    new(ptr) Variant(vector);
}

void ArrayToStringVector(CScriptArray* arr, StringVector& dest);

static void ConstructVariantStringVector(CScriptArray* value, Variant* ptr)
{
    StringVector vector;
    ArrayToStringVector(value, vector);
    new(ptr) Variant(vector);
}

static Variant& VariantAssignVariantVector(CScriptArray* value, Variant* ptr)
{
    VariantVector vector;
    ArrayToVariantVector(value, vector);
    *ptr = vector;
    return *ptr;
}

static Variant& VariantAssignStringVector(CScriptArray* value, Variant* ptr)
{
    StringVector vector;
    ArrayToStringVector(value, vector);
    *ptr = vector;
    return *ptr;
}

static bool VariantEqualsVariantVector(CScriptArray* value, Variant* ptr)
{
    VariantVector vector;
    ArrayToVariantVector(value, vector);
    return *ptr == vector;
}

static bool VariantEqualsStringVector(CScriptArray* value, Variant* ptr)
{
    StringVector vector;
    ArrayToStringVector(value, vector);
    return *ptr == vector;
}

static CScriptArray* VariantGetVariantVector(Variant* ptr)
{
    return VectorToArray<Variant>(ptr->GetVariantVector(), "Array<Variant>");
}

static CScriptArray* VariantGetStringVector(Variant* ptr)
{
    return VectorToArray<String>(ptr->GetStringVector(), "Array<String>");
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

// This function is called after ASRegisterGenerated()
void ASRegisterManualLast_Core(asIScriptEngine* engine)
{
    // using VariantMap = HashMap<StringHash, Variant> | File: ../Core/Variant.h
    engine->RegisterObjectBehaviour("VariantMap", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(VariantMap_Constructor), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("VariantMap", asBEHAVE_CONSTRUCT, "void f(const VariantMap&in)", asFUNCTION(VariantMap_CopyConstructor), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("VariantMap", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(VariantMap_Destructor), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("VariantMap", "VariantMap& opAssign(const VariantMap&in)", asMETHODPR(VariantMap, operator =, (const VariantMap&), VariantMap&), asCALL_THISCALL);
    engine->RegisterObjectMethod("VariantMap", "Variant& opIndex(const String&in)", asFUNCTION(VariantMap_At), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("VariantMap", "const Variant& opIndex(const String&in) const", asFUNCTION(VariantMap_At), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("VariantMap", "Variant& opIndex(StringHash)", asFUNCTION(VariantMap_AtHash), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("VariantMap", "const Variant& opIndex(StringHash) const", asFUNCTION(VariantMap_AtHash), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("VariantMap", "bool Contains(const String&in) const", asFUNCTION(VariantMap_Contains), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("VariantMap", "bool Erase(const String&in)", asFUNCTION(VariantMap_Erase), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("VariantMap", "bool Contains(StringHash) const", asFUNCTION(VariantMap_ContainsHash), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("VariantMap", "bool Erase(StringHash)", asFUNCTION(VariantMap_EraseHash), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("VariantMap", "void Clear()", asMETHOD(VariantMap, Clear), asCALL_THISCALL);
    engine->RegisterObjectMethod("VariantMap", "uint get_length() const", asMETHOD(VariantMap, Size), asCALL_THISCALL);
    engine->RegisterObjectMethod("VariantMap", "Array<StringHash>@ get_keys() const", asFUNCTION(VariantMap_GetKeys), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("VariantMap", "Array<Variant>@ get_values() const", asFUNCTION(VariantMap_GetValues), asCALL_CDECL_OBJLAST);

    engine->RegisterObjectBehaviour("Variant", asBEHAVE_CONSTRUCT, "void f(ScriptObject@+)", asFUNCTION(ConstructVariantScriptObject), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("Variant", asBEHAVE_CONSTRUCT, "void f(const Array<Variant>@+)", asFUNCTION(ConstructVariantVariantVector), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("Variant", asBEHAVE_CONSTRUCT, "void f(const Array<String>@+)", asFUNCTION(ConstructVariantStringVector), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("Variant", "Variant& opAssign(const Array<Variant>@+)", asFUNCTION(VariantAssignVariantVector), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("Variant", "Variant& opAssign(const Array<String>@+)", asFUNCTION(VariantAssignStringVector), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("Variant", "Variant& opAssign(ScriptObject@+)", asMETHODPR(Variant, operator =, (void*), Variant&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Variant", "bool opEquals(const Array<Variant>@+)", asFUNCTION(VariantEqualsVariantVector), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("Variant", "bool opEquals(const Array<String>@+)", asFUNCTION(VariantEqualsStringVector), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("Variant", "bool opEquals(ScriptObject@+) const", asMETHODPR(Variant, operator ==, (void*) const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Variant", "Array<Variant>@ GetVariantVector() const", asFUNCTION(VariantGetVariantVector), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("Variant", "Array<String>@ GetStringVector() const", asFUNCTION(VariantGetStringVector), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("Variant", "ScriptObject@+ GetScriptObject() const", asFUNCTION(VariantGetScriptObject), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("Variant", "bool get_zero() const", asMETHOD(Variant, IsZero), asCALL_THISCALL);
    engine->RegisterObjectMethod("Variant", "bool get_empty() const", asMETHOD(Variant, IsEmpty), asCALL_THISCALL);

    // StringVector ResourceRefList::names_ | File: ../Core/Variant.h
    engine->RegisterObjectMethod("ResourceRefList", "void Resize(uint)", asFUNCTION(ResourceRefListResize), asCALL_CDECL_OBJLAST);
    // StringVector ResourceRefList::names_ | File: ../Core/Variant.h
    engine->RegisterObjectMethod("ResourceRefList", "uint get_length() const", asFUNCTION(ResourceRefListGetSize), asCALL_CDECL_OBJLAST);
    // StringVector ResourceRefList::names_ | File: ../Core/Variant.h
    engine->RegisterObjectMethod("ResourceRefList", "bool get_empty() const", asFUNCTION(ResourceRefListIsEmpty), asCALL_CDECL_OBJLAST);
    // StringVector ResourceRefList::names_ | File: ../Core/Variant.h
    engine->RegisterObjectMethod("ResourceRefList", "void set_names(uint, const String&in) const", asFUNCTION(ResourceRefListSetName), asCALL_CDECL_OBJLAST);
    // StringVector ResourceRefList::names_ | File: ../Core/Variant.h
    engine->RegisterObjectMethod("ResourceRefList", "const String& get_names(uint) const", asFUNCTION(ResourceRefListGetName), asCALL_CDECL_OBJLAST);
}

}
