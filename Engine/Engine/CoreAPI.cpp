//
// Urho3D Engine
// Copyright (c) 2008-2011 Lasse Öörni
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

#include "Precompiled.h"
#include "APITemplates.h"
#include "Context.h"
#include "ProcessUtils.h"
#include "StringUtils.h"

static void ConstructStringHash(StringHash* ptr)
{
    new(ptr) StringHash();
}

static void ConstructStringHashCopy(const StringHash& hash, StringHash* ptr)
{
    new(ptr) StringHash(hash);
}

static void ConstructStringHashInit(const std::string& str, StringHash* ptr)
{
    new(ptr) StringHash(str);
}

static int StringHashCmp(const StringHash& lhs, const StringHash& rhs)
{
    int cmp = 0;
    if (lhs < rhs)
        cmp = -1;
    else if (lhs > rhs)
        cmp = 1;
    return cmp;
}

static void ConstructShortStringHash(StringHash* ptr)
{
    new(ptr) ShortStringHash();
}

static void ConstructShortStringHashCopyShort(const ShortStringHash& hash, ShortStringHash* ptr)
{
    new(ptr) ShortStringHash(hash);
}

static void ConstructShortStringHashCopyLong(const StringHash& hash, ShortStringHash* ptr)
{
    new(ptr) ShortStringHash(hash);
}

static void ConstructShortStringHashInit(const std::string& str, ShortStringHash* ptr)
{
    new(ptr) ShortStringHash(str);
}

static int ShortStringHashCmp(const ShortStringHash& lhs, const ShortStringHash& rhs)
{
    int cmp = 0;
    if (lhs < rhs)
        cmp = -1;
    else if (lhs > rhs)
        cmp = 1;
    return cmp;
}

static void RegisterStringHash(asIScriptEngine* engine)
{
    engine->RegisterObjectType("StringHash", sizeof(StringHash), asOBJ_VALUE | asOBJ_POD | asOBJ_APP_CLASS_CAK);
    engine->RegisterObjectBehaviour("StringHash", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(ConstructStringHash), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("StringHash", asBEHAVE_CONSTRUCT, "void f(const StringHash&in)", asFUNCTION(ConstructStringHashCopy), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("StringHash", asBEHAVE_CONSTRUCT, "void f(const String&in)", asFUNCTION(ConstructStringHashInit), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("StringHash", "StringHash &opAssign(const StringHash&in)", asMETHOD(StringHash, operator =), asCALL_THISCALL);
    engine->RegisterObjectMethod("StringHash", "StringHash &opAddAssign(const StringHash&in)", asMETHOD(StringHash, operator +=), asCALL_THISCALL);
    engine->RegisterObjectMethod("StringHash", "bool opEquals(const StringHash&in) const", asMETHOD(StringHash, operator ==), asCALL_THISCALL);
    engine->RegisterObjectMethod("StringHash", "int opCmp(const StringHash&in) const", asFUNCTION(StringHashCmp), asCALL_CDECL_OBJFIRST);
    engine->RegisterObjectMethod("StringHash", "StringHash opAdd(const StringHash&in) const", asMETHOD(StringHash, operator +), asCALL_THISCALL);
    engine->RegisterObjectMethod("StringHash", "String ToString() const", asFUNCTIONPR(ToString, (const StringHash&), std::string), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("StringHash", "uint get_value()", asMETHOD(StringHash, GetValue), asCALL_THISCALL);
    
    engine->RegisterObjectType("ShortStringHash", sizeof(ShortStringHash), asOBJ_VALUE | asOBJ_POD | asOBJ_APP_CLASS_CAK);
    engine->RegisterObjectBehaviour("ShortStringHash", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(ConstructShortStringHash), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("ShortStringHash", asBEHAVE_CONSTRUCT, "void f(const ShortStringHash&in)", asFUNCTION(ConstructShortStringHashCopyShort), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("ShortStringHash", asBEHAVE_CONSTRUCT, "void f(const StringHash&in)", asFUNCTION(ConstructShortStringHashCopyLong), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("ShortStringHash", asBEHAVE_CONSTRUCT, "void f(const String&in)", asFUNCTION(ConstructShortStringHashInit), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("ShortStringHash", "ShortStringHash &opAssign(const ShortStringHash&in)", asMETHODPR(ShortStringHash, operator =, (const ShortStringHash&), ShortStringHash&), asCALL_THISCALL);
    engine->RegisterObjectMethod("ShortStringHash", "bool opEquals(const ShortStringHash&in) const", asMETHOD(ShortStringHash, operator ==), asCALL_THISCALL);
    engine->RegisterObjectMethod("ShortStringHash", "int opCmp(const ShortStringHash&in) const", asFUNCTION(ShortStringHashCmp), asCALL_CDECL_OBJFIRST);
    engine->RegisterObjectMethod("ShortStringHash", "String ToString() const", asFUNCTIONPR(ToString, (const ShortStringHash&), std::string), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("ShortStringHash", "uint16 get_value()", asMETHOD(ShortStringHash, GetValue), asCALL_THISCALL);
}

static void ConstructResourceRef(ResourceRef* ptr)
{
    new(ptr) ResourceRef();
}

static void ConstructResourceRefCopy(const ResourceRef& ref, ResourceRef* ptr)
{
    new(ptr) ResourceRef(ref);
}

static void ConstructResourceRefList(ResourceRefList* ptr)
{
    new(ptr) ResourceRefList();
}

static void ConstructResourceRefListCopy(const ResourceRefList& ref, ResourceRefList* ptr)
{
    new(ptr) ResourceRefList(ref);
}

static void DestructResourceRefList(ResourceRefList* ptr)
{
    ptr->~ResourceRefList();
}

static void ResourceRefListResize(unsigned size, ResourceRefList* ptr)
{
    ptr->ids_.resize(size);
}

static unsigned ResourceRefListGetSize(ResourceRefList* ptr)
{
    return ptr->ids_.size();
}

static bool ResourceRefListIsEmpty(ResourceRefList* ptr)
{
    return ptr->ids_.size() == 0;
}

static void ResourceRefListSetId(unsigned index, const StringHash& id, ResourceRefList* ptr)
{
    if (index >= ptr->ids_.size())
    {
        asGetActiveContext()->SetException("Index out of bounds");
        return;
    }
    
    ptr->ids_[index] = id;
}

static StringHash ResourceRefListGetId(unsigned index, ResourceRefList* ptr)
{
    if (index >= ptr->ids_.size())
    {
        asGetActiveContext()->SetException("Index out of bounds");
        return StringHash();
    }
    
    return ptr->ids_[index];
}

static void ConstructVariant(Variant* ptr)
{
    new(ptr) Variant();
}

static void ConstructVariantCopy(const Variant& variant, Variant* ptr)
{
    new(ptr) Variant(variant);
}

static void ConstructVariantInt(int value, Variant* ptr)
{
    new(ptr) Variant(value);
}

static void ConstructVariantUInt(unsigned value, Variant* ptr)
{
    new(ptr) Variant(value);
}

static void ConstructVariantStringHash(const StringHash& value, Variant* ptr)
{
    new(ptr) Variant(value);
}

static void ConstructVariantShortStringHash(const ShortStringHash& value, Variant* ptr)
{
    new(ptr) Variant(value);
}

static void ConstructVariantBool(bool value, Variant* ptr)
{
    new(ptr) Variant(value);
}

static void ConstructVariantFloat(float value, Variant* ptr)
{
    new(ptr) Variant(value);
}

static void ConstructVariantVector2(const Vector2& value, Variant* ptr)
{
    new(ptr) Variant(value);
}

static void ConstructVariantVector3(const Vector3& value, Variant* ptr)
{
    new(ptr) Variant(value);
}

static void ConstructVariantVector4(const Vector4& value, Variant* ptr)
{
    new(ptr) Variant(value);
}

static void ConstructVariantQuaternion(const Quaternion& value, Variant* ptr)
{
    new(ptr) Variant(value);
}

static void ConstructVariantColor(const Color& value, Variant* ptr)
{
    new(ptr) Variant(value);
}

static void ConstructVariantString(const std::string& value, Variant* ptr)
{
    new(ptr) Variant(value);
}

void ArrayToVariantVector(CScriptArray* arr, VariantVector& dest)
{
    unsigned numVariants = arr->GetSize();
    dest.resize(numVariants);
    for (unsigned i = 0; i < numVariants; ++i)
        dest[i] = *(static_cast<Variant*>(arr->At(i)));
}

static void ConstructVariantVariantVector(CScriptArray* value, Variant* ptr)
{
    VariantVector vector;
    ArrayToVariantVector(value, vector);
    new(ptr) Variant(vector);
}

static void ConstructVariantVariantMap(const VariantMap& value, Variant* ptr)
{
    new(ptr) Variant(value);
}

static void DestructVariant(Variant* ptr)
{
    ptr->~Variant();
}

static Variant& VariantAssignVariantVector(CScriptArray* value, Variant* ptr)
{
    VariantVector vector;
    ArrayToVariantVector(value, vector);
    *ptr = vector;
    return *ptr;
}

static bool VariantEqualsVariantVector(CScriptArray* value, Variant* ptr)
{
    VariantVector vector;
    ArrayToVariantVector(value, vector);
    return *ptr == vector;
}

static CScriptArray* VariantGetVariantVector(Variant* ptr)
{
    return VectorToArray<Variant>(ptr->GetVariantVector(), "Array<Variant>");
}

static void ConstructVariantMap(VariantMap* ptr)
{
    new(ptr) VariantMap();
}

static void ConstructVariantMapCopy(const VariantMap& map, VariantMap* ptr)
{
    new(ptr) VariantMap(map);
}

static void DestructVariantMap(VariantMap* ptr)
{
    ptr->~VariantMap();
}

static Variant& VariantMapAt(const std::string& key, VariantMap& map)
{
    return map[ShortStringHash(key)];
}

static bool VariantMapContains(const std::string& key, VariantMap& map)
{
    return map.find(ShortStringHash(key)) != map.end();
}

static void VariantMapErase(const std::string& key, VariantMap& map)
{
    map.erase(ShortStringHash(key));
}

static void RegisterVariant(asIScriptEngine* engine)
{
    engine->RegisterEnum("VariantType");
    engine->RegisterEnumValue("VariantType", "VAR_NONE", VAR_NONE);
    engine->RegisterEnumValue("VariantType", "VAR_INT", VAR_INT);
    engine->RegisterEnumValue("VariantType", "VAR_BOOL", VAR_BOOL);
    engine->RegisterEnumValue("VariantType", "VAR_FLOAT", VAR_FLOAT);
    engine->RegisterEnumValue("VariantType", "VAR_VECTOR2", VAR_VECTOR2);
    engine->RegisterEnumValue("VariantType", "VAR_VECTOR3", VAR_VECTOR3);
    engine->RegisterEnumValue("VariantType", "VAR_VECTOR4", VAR_VECTOR4);
    engine->RegisterEnumValue("VariantType", "VAR_QUATERNION", VAR_QUATERNION);
    engine->RegisterEnumValue("VariantType", "VAR_COLOR", VAR_COLOR);
    engine->RegisterEnumValue("VariantType", "VAR_STRING", VAR_STRING);
    engine->RegisterEnumValue("VariantType", "VAR_BUFFER", VAR_BUFFER);
    engine->RegisterEnumValue("VariantType", "VAR_PTR", VAR_PTR);
    engine->RegisterEnumValue("VariantType", "VAR_RESOURCEREF", VAR_RESOURCEREF);
    engine->RegisterEnumValue("VariantType", "VAR_RESOURCEREFLIST", VAR_RESOURCEREFLIST);
    engine->RegisterEnumValue("VariantType", "VAR_VARIANTVECTOR", VAR_VARIANTVECTOR);
    engine->RegisterEnumValue("VariantType", "VAR_VARIANTMAP", VAR_VARIANTMAP);
    
    engine->RegisterObjectType("ResourceRef", sizeof(ResourceRef), asOBJ_VALUE | asOBJ_POD | asOBJ_APP_CLASS_CAK);
    engine->RegisterObjectBehaviour("ResourceRef", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(ConstructResourceRef), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("ResourceRef", asBEHAVE_CONSTRUCT, "void f(const ResourceRef&in)", asFUNCTION(ConstructResourceRefCopy), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("ResourceRef", "ResourceRef &opAssign(const ResourceRef&in)", asMETHOD(ResourceRef, operator =), asCALL_THISCALL);
    engine->RegisterObjectMethod("ResourceRef", "bool opEquals(const ResourceRef&in) const", asMETHOD(ResourceRef, operator ==), asCALL_THISCALL);
    engine->RegisterObjectProperty("ResourceRef", "ShortStringHash type", offsetof(ResourceRef, type_));
    engine->RegisterObjectProperty("ResourceRef", "StringHash id", offsetof(ResourceRef, id_));
    
    engine->RegisterObjectType("ResourceRefList", sizeof(ResourceRefList), asOBJ_VALUE | asOBJ_APP_CLASS_CDA);
    engine->RegisterObjectBehaviour("ResourceRefList", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(ConstructResourceRefList), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("ResourceRefList", asBEHAVE_CONSTRUCT, "void f(const ResourceRefList&in)", asFUNCTION(ConstructResourceRefListCopy), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("ResourceRefList", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(DestructResourceRefList), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("ResourceRefList", "ResourceRefList &opAssign(const ResourceRefList&in)", asMETHOD(ResourceRefList, operator =), asCALL_THISCALL);
    engine->RegisterObjectMethod("ResourceRefList", "bool opEquals(const ResourceRefList&in) const", asMETHOD(ResourceRefList, operator ==), asCALL_THISCALL);
    engine->RegisterObjectMethod("ResourceRefList", "void Resize(uint)", asFUNCTION(ResourceRefListResize), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("ResourceRefList", "uint get_length() const", asFUNCTION(ResourceRefListGetSize), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("ResourceRefList", "bool get_empty() const", asFUNCTION(ResourceRefListIsEmpty), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("ResourceRefList", "void set_ids(uint, const StringHash&in) const", asFUNCTION(ResourceRefListSetId), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("ResourceRefList", "StringHash get_ids(uint) const", asFUNCTION(ResourceRefListGetId), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectProperty("ResourceRefList", "ShortStringHash type", offsetof(ResourceRef, type_));
    
    engine->RegisterObjectType("Variant", sizeof(Variant), asOBJ_VALUE | asOBJ_APP_CLASS_CDA);
    engine->RegisterObjectType("VariantMap", sizeof(VariantMap), asOBJ_VALUE | asOBJ_APP_CLASS_CDA);
    engine->RegisterObjectBehaviour("Variant", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(ConstructVariant), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("Variant", asBEHAVE_CONSTRUCT, "void f(const Variant&in)", asFUNCTION(ConstructVariantCopy), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("Variant", asBEHAVE_CONSTRUCT, "void f(int)", asFUNCTION(ConstructVariantInt), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("Variant", asBEHAVE_CONSTRUCT, "void f(uint)", asFUNCTION(ConstructVariantUInt), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("Variant", asBEHAVE_CONSTRUCT, "void f(const StringHash&in)", asFUNCTION(ConstructVariantStringHash), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("Variant", asBEHAVE_CONSTRUCT, "void f(const ShortStringHash&in)", asFUNCTION(ConstructVariantShortStringHash), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("Variant", asBEHAVE_CONSTRUCT, "void f(bool)", asFUNCTION(ConstructVariantBool), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("Variant", asBEHAVE_CONSTRUCT, "void f(float)", asFUNCTION(ConstructVariantFloat), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("Variant", asBEHAVE_CONSTRUCT, "void f(const Vector2&in)", asFUNCTION(ConstructVariantVector2), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("Variant", asBEHAVE_CONSTRUCT, "void f(const Vector3&in)", asFUNCTION(ConstructVariantVector3), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("Variant", asBEHAVE_CONSTRUCT, "void f(const Quaternion&in)", asFUNCTION(ConstructVariantQuaternion), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("Variant", asBEHAVE_CONSTRUCT, "void f(const Color&in)", asFUNCTION(ConstructVariantColor), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("Variant", asBEHAVE_CONSTRUCT, "void f(const String&in)", asFUNCTION(ConstructVariantString), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("Variant", asBEHAVE_CONSTRUCT, "void f(const Array<Variant>@+)", asFUNCTION(ConstructVariantVariantVector), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("Variant", asBEHAVE_CONSTRUCT, "void f(const VariantMap&in)", asFUNCTION(ConstructVariantVariantMap), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("Variant", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(DestructVariant), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("Variant", "void Clear()", asMETHOD(Variant, Clear), asCALL_THISCALL);
    engine->RegisterObjectMethod("Variant", "Variant &opAssign(const Variant&in)", asMETHODPR(Variant, operator =, (const Variant&), Variant&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Variant", "Variant &opAssign(int)", asMETHODPR(Variant, operator =, (int), Variant&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Variant", "Variant &opAssign(uint)", asMETHODPR(Variant, operator =, (unsigned), Variant&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Variant", "Variant &opAssign(const StringHash&in)", asMETHODPR(Variant, operator =, (const StringHash&), Variant&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Variant", "Variant &opAssign(const ShortStringHash&in)", asMETHODPR(Variant, operator =, (const ShortStringHash&), Variant&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Variant", "Variant &opAssign(bool)", asMETHODPR(Variant, operator =, (bool), Variant&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Variant", "Variant &opAssign(float)", asMETHODPR(Variant, operator =, (float), Variant&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Variant", "Variant &opAssign(const Vector2&in)", asMETHODPR(Variant, operator =, (const Vector2&), Variant&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Variant", "Variant &opAssign(const Vector3&in)", asMETHODPR(Variant, operator =, (const Vector3&), Variant&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Variant", "Variant &opAssign(const Quaternion&in)", asMETHODPR(Variant, operator =, (const Quaternion&), Variant&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Variant", "Variant &opAssign(const Color&in)", asMETHODPR(Variant, operator =, (const Color&), Variant&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Variant", "Variant &opAssign(const String&in)", asMETHODPR(Variant, operator =, (const std::string&), Variant&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Variant", "Variant &opAssign(const Array<Variant>@+)", asFUNCTION(VariantAssignVariantVector), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("Variant", "Variant &opAssign(const VariantMap&in)", asMETHODPR(Variant, operator =, (const VariantMap&), Variant&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Variant", "bool opEquals(const Variant&in) const", asMETHODPR(Variant, operator ==, (const Variant&) const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Variant", "bool opEquals(int) const", asMETHODPR(Variant, operator ==, (int) const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Variant", "bool opEquals(uint) const", asMETHODPR(Variant, operator ==, (unsigned) const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Variant", "bool opEquals(const StringHash&in) const", asMETHODPR(Variant, operator ==, (const StringHash&) const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Variant", "bool opEquals(const ShortStringHash&in) const", asMETHODPR(Variant, operator ==, (const ShortStringHash&) const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Variant", "bool opEquals(bool) const", asMETHODPR(Variant, operator ==, (bool) const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Variant", "bool opEquals(float) const", asMETHODPR(Variant, operator ==, (float) const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Variant", "bool opEquals(const Vector2&in) const", asMETHODPR(Variant, operator ==, (const Vector2&) const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Variant", "bool opEquals(const Vector3&in) const", asMETHODPR(Variant, operator ==, (const Vector3&) const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Variant", "bool opEquals(const Quaternion&in) const", asMETHODPR(Variant, operator ==, (const Quaternion&) const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Variant", "bool opEquals(const Color&in) const", asMETHODPR(Variant, operator ==, (const Color&) const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Variant", "bool opEquals(const String&in) const", asMETHODPR(Variant, operator ==, (const std::string&) const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Variant", "bool opEquals(const Array<Variant>@+)", asFUNCTION(VariantEqualsVariantVector), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("Variant", "bool opEquals(const VariantMap&in) const", asMETHODPR(Variant, operator ==, (const VariantMap&) const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Variant", "int GetInt() const", asMETHOD(Variant, GetInt), asCALL_THISCALL);
    engine->RegisterObjectMethod("Variant", "uint GetUInt() const", asMETHOD(Variant, GetUInt), asCALL_THISCALL);
    engine->RegisterObjectMethod("Variant", "StringHash GetStringHash() const", asMETHOD(Variant, GetStringHash), asCALL_THISCALL);
    engine->RegisterObjectMethod("Variant", "ShortStringHash GetShortStringHash() const", asMETHOD(Variant, GetShortStringHash), asCALL_THISCALL);
    engine->RegisterObjectMethod("Variant", "bool GetBool() const", asMETHOD(Variant, GetBool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Variant", "float GetFloat() const", asMETHOD(Variant, GetFloat), asCALL_THISCALL);
    engine->RegisterObjectMethod("Variant", "const Vector2& GetVector2() const", asMETHOD(Variant, GetVector2), asCALL_THISCALL);
    engine->RegisterObjectMethod("Variant", "const Vector3& GetVector3() const", asMETHOD(Variant, GetVector3), asCALL_THISCALL);
    engine->RegisterObjectMethod("Variant", "const Vector4& GetVector4() const", asMETHOD(Variant, GetVector4), asCALL_THISCALL);
    engine->RegisterObjectMethod("Variant", "const Quaternion& GetQuaternion() const", asMETHOD(Variant, GetQuaternion), asCALL_THISCALL);
    engine->RegisterObjectMethod("Variant", "const Color& GetColor() const", asMETHOD(Variant, GetColor), asCALL_THISCALL);
    engine->RegisterObjectMethod("Variant", "const String& GetString() const", asMETHOD(Variant, GetString), asCALL_THISCALL);
    engine->RegisterObjectMethod("Variant", "Array<Variant>@ GetVariantVector() const", asFUNCTION(VariantGetVariantVector), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("Variant", "const VariantMap& GetVariantMap() const", asMETHOD(Variant, GetVariantMap), asCALL_THISCALL);
    engine->RegisterObjectMethod("Variant", "void FromString(const String&in, const String&in)", asMETHOD(Variant, FromString), asCALL_THISCALL);
    engine->RegisterObjectMethod("Variant", "String ToString() const", asMETHOD(Variant, ToString), asCALL_THISCALL);
    engine->RegisterObjectMethod("Variant", "VariantType get_type() const", asMETHOD(Variant, GetType), asCALL_THISCALL);
    engine->RegisterObjectMethod("Variant", "const String &get_typeName() const", asMETHOD(Variant, GetTypeName), asCALL_THISCALL);
    
    engine->RegisterObjectBehaviour("VariantMap", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(ConstructVariantMap), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("VariantMap", asBEHAVE_CONSTRUCT, "void f(const VariantMap&in)", asFUNCTION(ConstructVariantMapCopy), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("VariantMap", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(DestructVariantMap), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("VariantMap", "VariantMap& opAssign(const VariantMap&in)", asMETHODPR(VariantMap, operator =, (const VariantMap&), VariantMap&), asCALL_THISCALL);
    engine->RegisterObjectMethod("VariantMap", "Variant& opIndex(const String&in)", asFUNCTION(VariantMapAt), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("VariantMap", "const Variant& opIndex(const String&in) const", asFUNCTION(VariantMapAt), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("VariantMap", "bool Contains(const String&in) const", asFUNCTION(VariantMapContains), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("VariantMap", "void Erase(const String&in)", asFUNCTION(VariantMapErase), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("VariantMap", "void Clear()", asMETHOD(VariantMap, clear), asCALL_THISCALL);
    engine->RegisterObjectMethod("VariantMap", "uint get_length() const", asMETHOD(VariantMap, size), asCALL_THISCALL);
}

static CScriptArray* StringSplit(char separator, const std::string* str)
{
    std::vector<std::string> result = Split(*str, separator);
    return VectorToArray<std::string>(result, "Array<String>");
}

static void RegisterStringUtils(asIScriptEngine* engine)
{
    // Register most of StringUtils as string's const methods, or objects' ToString() const methods for convenience
    engine->RegisterObjectMethod("String", "Array<String>@ Split(uint8) const", asFUNCTION(StringSplit), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("String", "String Replace(uint8, uint8) const", asFUNCTIONPR(Replace, (const std::string&, char, char), std::string), asCALL_CDECL_OBJFIRST);
    engine->RegisterObjectMethod("String", "String Replace(const String&in, const String&in) const", asFUNCTIONPR(Replace, (const std::string&, const std::string&, const std::string&), std::string), asCALL_CDECL_OBJFIRST);
    engine->RegisterObjectMethod("String", "String ToUpper() const", asFUNCTION(ToUpper), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("String", "String ToLower() const", asFUNCTION(ToLower), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("String", "bool ToBool() const", asFUNCTION(ToBool), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("String", "float ToFloat() const", asFUNCTION(ToFloat), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("String", "int ToInt() const", asFUNCTION(ToInt), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("String", "uint ToUInt() const", asFUNCTION(ToUInt), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("String", "Color ToColor() const", asFUNCTION(ToColor), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("String", "IntRect ToIntRect() const", asFUNCTION(ToIntRect), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("String", "IntVector2 ToIntVector2() const", asFUNCTION(ToIntVector2), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("String", "Quaternion ToQuaternion() const", asFUNCTION(ToQuaternion), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("String", "Vector2 ToVector2() const", asFUNCTION(ToVector2), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("String", "Vector3 ToVector3() const", asFUNCTION(ToVector3), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("String", "Vector4 ToVector4() const", asFUNCTION(ToVector4), asCALL_CDECL_OBJLAST);
    engine->RegisterGlobalFunction("String ToString(bool)", asFUNCTIONPR(ToString, (bool), std::string), asCALL_CDECL);
    engine->RegisterGlobalFunction("String ToString(float)", asFUNCTIONPR(ToString, (float), std::string), asCALL_CDECL);
    engine->RegisterGlobalFunction("String ToString(int)", asFUNCTIONPR(ToString, (int), std::string), asCALL_CDECL);
    engine->RegisterGlobalFunction("String ToString(uint)", asFUNCTIONPR(ToString, (unsigned), std::string), asCALL_CDECL);
    engine->RegisterGlobalFunction("String ToStringHex(int)", asFUNCTION(ToStringHex), asCALL_CDECL);
}

static void ConstructTimer(Timer* ptr)
{
    new(ptr) Timer();
}

static Time* GetTime()
{
    return GetScriptContext()->GetSubsystem<Time>();
}

static void RegisterTimer(asIScriptEngine* engine)
{
    engine->RegisterObjectType("Timer", sizeof(Timer), asOBJ_VALUE | asOBJ_POD | asOBJ_APP_CLASS_C);
    engine->RegisterObjectBehaviour("Timer", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(ConstructTimer), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("Timer", "uint GetMSec(bool)", asMETHOD(Timer, GetMSec), asCALL_THISCALL);
    engine->RegisterObjectMethod("Timer", "void Reset()", asMETHOD(Timer, Reset), asCALL_THISCALL);
     
    RegisterObject<Time>(engine, "Time");
    engine->RegisterObjectMethod("Time", "uint get_frameNumber() const", asMETHOD(Time, GetFrameNumber), asCALL_THISCALL);
    engine->RegisterObjectMethod("Time", "float get_timeStep() const", asMETHOD(Time, GetTimeStep), asCALL_THISCALL);
    engine->RegisterObjectMethod("Time", "uint get_timeStepMSec() const", asMETHOD(Time, GetTimeStepMSec), asCALL_THISCALL);
    engine->RegisterObjectMethod("Time", "uint get_totalMSec() const", asMETHOD(Time, GetTotalMSec), asCALL_THISCALL);
    engine->RegisterGlobalFunction("Time@+ get_time()", asFUNCTION(GetTime), asCALL_CDECL);
}

static CScriptArray* GetArgumentsToArray()
{
    return VectorToArray<std::string>(GetArguments(), "Array<String>");
}

static void ShowErrorDialog(const std::string& title, const std::string& message)
{
    ErrorDialog(title.c_str(), message.c_str());
}

static void RegisterProcessUtils(asIScriptEngine* engine)
{
    engine->RegisterGlobalFunction("void ErrorDialog(const String&in, const String&in)", asFUNCTION(ShowErrorDialog), asCALL_CDECL);
    engine->RegisterGlobalFunction("void OpenConsoleWindow()", asFUNCTION(OpenConsoleWindow), asCALL_CDECL);
    engine->RegisterGlobalFunction("String GetConsoleInput()", asFUNCTION(GetConsoleInput), asCALL_CDECL);
    engine->RegisterGlobalFunction("Array<String>@ get_arguments()", asFUNCTION(GetArgumentsToArray), asCALL_CDECL);
    engine->RegisterGlobalFunction("uint get_numCpuCores()", asFUNCTION(GetNumCPUCores), asCALL_CDECL);
}

static void ConstructAttributeInfo(AttributeInfo* ptr)
{
    new(ptr) AttributeInfo();
}

static void ConstructAttributeInfoCopy(const AttributeInfo& attr, AttributeInfo* ptr)
{
    new(ptr) AttributeInfo(attr);
}

static void DestructAttributeInfo(AttributeInfo* ptr)
{
    ptr->~AttributeInfo();
}

static std::string AttributeInfoGetName(AttributeInfo* ptr)
{
    return ptr->name_ ? std::string(ptr->name_) : std::string();
}

static CScriptArray* AttributeInfoGetEnumNames(AttributeInfo* ptr)
{
    std::vector<std::string> enumNames;
    const char** enumNamePtrs = ptr->enumNames_;
    while ((enumNamePtrs) && (*enumNamePtrs))
    {
        enumNames.push_back(std::string(*enumNamePtrs));
        ++enumNamePtrs;
    }
    return VectorToArray<std::string>(enumNames, "Array<String>");
}

static void SendEvent(const std::string& eventType, VariantMap& parameters)
{
    Object* sender = GetScriptContextEventListenerObject();
    if (sender)
        sender->SendEvent(StringHash(eventType), parameters);
}

static void SendTargetedEvent(Object* receiver, const std::string& eventType, VariantMap& parameters)
{
    Object* sender = GetScriptContextEventListenerObject();
    if (sender)
        sender->SendEvent(receiver, StringHash(eventType), parameters);
}

static void SubscribeToEvent(const std::string& eventType, const std::string& handlerName)
{
    ScriptEventListener* listener = GetScriptContextEventListener();
    if (listener)
        listener->AddEventHandler(StringHash(eventType), handlerName);
}

static void SubscribeToSenderEvent(Object* sender, const std::string& eventType, const std::string& handlerName)
{
    ScriptEventListener* listener = GetScriptContextEventListener();
    if (listener)
        listener->AddEventHandler(sender, StringHash(eventType), handlerName);
}

static void UnsubscribeFromEvent(const std::string& eventType)
{
    Object* listener = GetScriptContextEventListenerObject();
    if (listener)
        listener->UnsubscribeFromEvent(StringHash(eventType));
}

static void UnsubscribeFromSenderEvent(Object* sender, const std::string& eventType)
{
    Object* listener = GetScriptContextEventListenerObject();
    if (listener)
        listener->UnsubscribeFromEvent(sender, StringHash(eventType));
}

static void UnsubscribeFromSenderEvents(Object* sender)
{
    Object* listener = GetScriptContextEventListenerObject();
    if (listener)
        listener->UnsubscribeFromEvents(sender);
}

static void UnsubscribeFromAllEvents()
{
    Object* listener = GetScriptContextEventListenerObject();
    if (listener)
        listener->UnsubscribeFromAllEventsWithUserData();
}

static Object* GetSender()
{
    return GetScriptContext()->GetSender();
}

void RegisterObject(asIScriptEngine* engine)
{
    engine->RegisterObjectType("AttributeInfo", sizeof(AttributeInfo), asOBJ_VALUE | asOBJ_APP_CLASS_CDA);
    engine->RegisterObjectBehaviour("AttributeInfo", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(ConstructAttributeInfo), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("AttributeInfo", asBEHAVE_CONSTRUCT, "void f(const AttributeInfo&in)", asFUNCTION(ConstructAttributeInfoCopy), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("AttributeInfo", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(DestructAttributeInfo), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("AttributeInfo", "AttributeInfo& opAssign(const AttributeInfo&in)", asMETHODPR(AttributeInfo, operator =, (const AttributeInfo&), AttributeInfo&), asCALL_THISCALL);
    engine->RegisterObjectMethod("AttributeInfo", "String get_name()", asFUNCTION(AttributeInfoGetName), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("AttributeInfo", "Array<String>@ get_enumNames()", asFUNCTION(AttributeInfoGetEnumNames), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectProperty("AttributeInfo", "VariantType type", offsetof(AttributeInfo, type_));
    engine->RegisterObjectProperty("AttributeInfo", "Variant defaultValue", offsetof(AttributeInfo, defaultValue_));
    engine->RegisterObjectProperty("AttributeInfo", "uint mode", offsetof(AttributeInfo, mode_));
    
    RegisterObject<Object>(engine, "Object");
    
    engine->RegisterGlobalFunction("void SendEvent(const String&in, VariantMap&)", asFUNCTION(SendEvent), asCALL_CDECL);
    engine->RegisterGlobalFunction("void SendEvent(Object@+, const String&in, VariantMap&)", asFUNCTION(SendTargetedEvent), asCALL_CDECL);
    engine->RegisterGlobalFunction("void SubscribeToEvent(const String&in, const String&in)", asFUNCTION(SubscribeToEvent), asCALL_CDECL);
    engine->RegisterGlobalFunction("void SubscribeToEvent(Object@+, const String&in, const String&in)", asFUNCTION(SubscribeToSenderEvent), asCALL_CDECL);
    engine->RegisterGlobalFunction("void UnsubscribeFromEvent(const String&in)", asFUNCTION(UnsubscribeFromEvent), asCALL_CDECL);
    engine->RegisterGlobalFunction("void UnsubscribeFromEvent(Object@+, const String&in)", asFUNCTION(UnsubscribeFromSenderEvent), asCALL_CDECL);
    engine->RegisterGlobalFunction("void UnsubscribeFromEvents(Object@+)", asFUNCTION(UnsubscribeFromSenderEvents), asCALL_CDECL);
    engine->RegisterGlobalFunction("void UnsubscribeFromAllEvents()", asFUNCTION(UnsubscribeFromAllEvents), asCALL_CDECL);
    
    engine->RegisterGlobalFunction("Object@+ get_Sender()", asFUNCTION(GetSender), asCALL_CDECL);
}

void RegisterCoreAPI(asIScriptEngine* engine)
{
    RegisterStringHash(engine);
    RegisterVariant(engine);
    RegisterStringUtils(engine);
    RegisterProcessUtils(engine);
    RegisterObject(engine);
    RegisterTimer(engine);
}
