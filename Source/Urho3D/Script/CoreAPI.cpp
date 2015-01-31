//
// Copyright (c) 2008-2015 the Urho3D project.
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

#include "../Script/APITemplates.h"
#include "../Core/Context.h"
#include "../Core/ProcessUtils.h"
#include "../Core/Spline.h"
#include "../Core/StringUtils.h"

namespace Urho3D
{

static void ConstructStringHash(StringHash* ptr)
{
    new(ptr) StringHash();
}

static void ConstructStringHashCopy(const StringHash& hash, StringHash* ptr)
{
    new(ptr) StringHash(hash);
}

static void ConstructStringHashInit(const String& str, StringHash* ptr)
{
    new(ptr) StringHash(str);
}

static void ConstructStringHashInitUInt(unsigned value, StringHash* ptr)
{
    new(ptr) StringHash(value);
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

static void RegisterStringHash(asIScriptEngine* engine)
{
    engine->RegisterObjectType("StringHash", sizeof(StringHash), asOBJ_VALUE | asOBJ_POD | asOBJ_APP_CLASS_CAK);
    engine->RegisterObjectBehaviour("StringHash", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(ConstructStringHash), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("StringHash", asBEHAVE_CONSTRUCT, "void f(const StringHash&in)", asFUNCTION(ConstructStringHashCopy), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("StringHash", asBEHAVE_CONSTRUCT, "void f(const String&in)", asFUNCTION(ConstructStringHashInit), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("StringHash", asBEHAVE_CONSTRUCT, "void f(uint)", asFUNCTION(ConstructStringHashInitUInt), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("StringHash", "StringHash& opAssign(const StringHash&in)", asMETHOD(StringHash, operator =), asCALL_THISCALL);
    engine->RegisterObjectMethod("StringHash", "StringHash& opAddAssign(const StringHash&in)", asMETHOD(StringHash, operator +=), asCALL_THISCALL);
    engine->RegisterObjectMethod("StringHash", "bool opEquals(const StringHash&in) const", asMETHOD(StringHash, operator ==), asCALL_THISCALL);
    engine->RegisterObjectMethod("StringHash", "int opCmp(const StringHash&in) const", asFUNCTION(StringHashCmp), asCALL_CDECL_OBJFIRST);
    engine->RegisterObjectMethod("StringHash", "StringHash opAdd(const StringHash&in) const", asMETHOD(StringHash, operator +), asCALL_THISCALL);
    engine->RegisterObjectMethod("StringHash", "String ToString() const", asMETHOD(StringHash, ToString), asCALL_THISCALL);
    engine->RegisterObjectMethod("StringHash", "uint get_value()", asMETHOD(StringHash, Value), asCALL_THISCALL);
}

static void ConstructResourceRef(ResourceRef* ptr)
{
    new(ptr) ResourceRef();
}

static void ConstructResourceRefCopy(const ResourceRef& ref, ResourceRef* ptr)
{
    new(ptr) ResourceRef(ref);
}

static void DestructResourceRef(ResourceRef* ptr)
{
    ptr->~ResourceRef();
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
    ptr->names_.Resize(size);
}

static unsigned ResourceRefListGetSize(ResourceRefList* ptr)
{
    return ptr->names_.Size();
}

static bool ResourceRefListIsEmpty(ResourceRefList* ptr)
{
    return ptr->names_.Size() == 0;
}

static void ResourceRefListSetName(unsigned index, const String& name, ResourceRefList* ptr)
{
    if (index >= ptr->names_.Size())
    {
        asGetActiveContext()->SetException("Index out of bounds");
        return;
    }

    ptr->names_[index] = name;
}

static const String& ResourceRefListGetName(unsigned index, ResourceRefList* ptr)
{
    if (index >= ptr->names_.Size())
    {
        asGetActiveContext()->SetException("Index out of bounds");
        return String::EMPTY;
    }

    return ptr->names_[index];
}

void ArrayToVariantVector(CScriptArray* arr, VariantVector& dest)
{
    unsigned numVariants = arr->GetSize();
    dest.Resize(numVariants);
    for (unsigned i = 0; i < numVariants; ++i)
        dest[i] = *(static_cast<Variant*>(arr->At(i)));
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

static void ConstructVariantString(const String& value, Variant* ptr)
{
    new(ptr) Variant(value);
}

static void ConstructVariantResourceRef(const ResourceRef& value, Variant* ptr)
{
    new(ptr) Variant(value);
}

static void ConstructVariantResourceRefList(const ResourceRefList& value, Variant* ptr)
{
    new(ptr) Variant(value);
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

static void ConstructVariantIntRect(const IntRect& value, Variant* ptr)
{
    new(ptr) Variant(value);
}

static void ConstructVariantIntVector2(const IntVector2& value, Variant* ptr)
{
    new(ptr) Variant(value);
}

static void ConstructVariantPtr(RefCounted* value, Variant* ptr)
{
    new(ptr) Variant(value);
}

static void ConstructVariantScriptObject(asIScriptObject* value, Variant* ptr)
{
    if (value)
    {
        asIObjectType* scriptObjectInterface = value->GetEngine()->GetObjectTypeByName("ScriptObject");
        if (value->GetObjectType()->Implements(scriptObjectInterface))
            new(ptr) Variant(value);
        else
            new(ptr) Variant();
    }
    else
        new(ptr) Variant();
}

static void ConstructVariantMatrix3(const Matrix3& value, Variant* ptr)
{
    new(ptr) Variant(value);
}

static void ConstructVariantMatrix3x4(const Matrix3x4& value, Variant* ptr)
{
    new(ptr) Variant(value);
}

static void ConstructVariantMatrix4(const Matrix4& value, Variant* ptr)
{
    new(ptr) Variant(value);
}

static void ConstructVariantTypeNameValue(const String& type, const String& value, Variant* ptr)
{
    new(ptr) Variant(type, value);
}

static void ConstructVariantTypeValue(VariantType type, const String& value, Variant* ptr)
{
    new(ptr) Variant(type, value);
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

static asIScriptObject* VariantGetScriptObject(Variant* ptr)
{
    asIScriptObject* object = static_cast<asIScriptObject*>(ptr->GetVoidPtr());
    if (!object)
        return 0;

    asIObjectType* scriptObjectInterface = object->GetEngine()->GetObjectTypeByName("ScriptObject");
    if (!object->GetObjectType()->Implements(scriptObjectInterface))
        return 0;

    return object;
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

static Variant& VariantMapAt(const String& key, VariantMap& map)
{
    return map[key];
}

static Variant& VariantMapAtHash(StringHash key, VariantMap& map)
{
    return map[key];
}

static bool VariantMapContains(const String& key, VariantMap& map)
{
    return map.Contains(key);
}

static bool VariantMapErase(const String& key, VariantMap& map)
{
    return map.Erase(key);
}

static bool VariantMapContainsHash(StringHash key, VariantMap& map)
{
    return map.Contains(key);
}

static bool VariantMapEraseHash(StringHash key, VariantMap& map)
{
    return map.Erase(key);
}

static CScriptArray* VariantMapGetKeys(const VariantMap& map)
{
    return VectorToArray<StringHash>(map.Keys(), "Array<StringHash>");
}

static CScriptArray* VariantMapGetValues(const VariantMap& map)
{
    return VectorToArray<Variant>(map.Values(), "Array<Variant>");
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
    engine->RegisterEnumValue("VariantType", "VAR_VOIDPTR", VAR_VOIDPTR);
    engine->RegisterEnumValue("VariantType", "VAR_RESOURCEREF", VAR_RESOURCEREF);
    engine->RegisterEnumValue("VariantType", "VAR_RESOURCEREFLIST", VAR_RESOURCEREFLIST);
    engine->RegisterEnumValue("VariantType", "VAR_VARIANTVECTOR", VAR_VARIANTVECTOR);
    engine->RegisterEnumValue("VariantType", "VAR_VARIANTMAP", VAR_VARIANTMAP);
    engine->RegisterEnumValue("VariantType", "VAR_INTRECT", VAR_INTRECT);
    engine->RegisterEnumValue("VariantType", "VAR_INTVECTOR2", VAR_INTVECTOR2);
    engine->RegisterEnumValue("VariantType", "VAR_PTR", VAR_PTR);
    engine->RegisterEnumValue("VariantType", "VAR_MATRIX3", VAR_MATRIX3);
    engine->RegisterEnumValue("VariantType", "VAR_MATRIX3X4", VAR_MATRIX3X4);
    engine->RegisterEnumValue("VariantType", "VAR_MATRIX4", VAR_MATRIX4);

    engine->RegisterObjectType("ResourceRef", sizeof(ResourceRef), asOBJ_VALUE | asOBJ_POD | asOBJ_APP_CLASS_CK);
    engine->RegisterObjectBehaviour("ResourceRef", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(ConstructResourceRef), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("ResourceRef", asBEHAVE_CONSTRUCT, "void f(const ResourceRef&in)", asFUNCTION(ConstructResourceRefCopy), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("ResourceRef", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(DestructResourceRef), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("ResourceRef", "ResourceRef& opAssign(const ResourceRef&in)", asMETHOD(ResourceRef, operator =), asCALL_THISCALL);
    engine->RegisterObjectMethod("ResourceRef", "bool opEquals(const ResourceRef&in) const", asMETHOD(ResourceRef, operator ==), asCALL_THISCALL);
    engine->RegisterObjectProperty("ResourceRef", "StringHash type", offsetof(ResourceRef, type_));
    engine->RegisterObjectProperty("ResourceRef", "String name", offsetof(ResourceRef, name_));

    engine->RegisterObjectType("ResourceRefList", sizeof(ResourceRefList), asOBJ_VALUE | asOBJ_APP_CLASS_C);
    engine->RegisterObjectBehaviour("ResourceRefList", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(ConstructResourceRefList), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("ResourceRefList", asBEHAVE_CONSTRUCT, "void f(const ResourceRefList&in)", asFUNCTION(ConstructResourceRefListCopy), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("ResourceRefList", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(DestructResourceRefList), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("ResourceRefList", "ResourceRefList& opAssign(const ResourceRefList&in)", asMETHOD(ResourceRefList, operator =), asCALL_THISCALL);
    engine->RegisterObjectMethod("ResourceRefList", "bool opEquals(const ResourceRefList&in) const", asMETHOD(ResourceRefList, operator ==), asCALL_THISCALL);
    engine->RegisterObjectMethod("ResourceRefList", "void Resize(uint)", asFUNCTION(ResourceRefListResize), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("ResourceRefList", "uint get_length() const", asFUNCTION(ResourceRefListGetSize), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("ResourceRefList", "bool get_empty() const", asFUNCTION(ResourceRefListIsEmpty), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("ResourceRefList", "void set_names(uint, const String&in) const", asFUNCTION(ResourceRefListSetName), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("ResourceRefList", "const String& get_names(uint) const", asFUNCTION(ResourceRefListGetName), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectProperty("ResourceRefList", "StringHash type", offsetof(ResourceRef, type_));

    RegisterRefCounted<RefCounted>(engine, "RefCounted");
    
    engine->RegisterObjectType("Variant", sizeof(Variant), asOBJ_VALUE | asOBJ_APP_CLASS_CDAK);
    engine->RegisterObjectType("VariantMap", sizeof(VariantMap), asOBJ_VALUE | asOBJ_APP_CLASS_CDAK);
    engine->RegisterObjectBehaviour("Variant", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(ConstructVariant), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("Variant", asBEHAVE_CONSTRUCT, "void f(const Variant&in)", asFUNCTION(ConstructVariantCopy), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("Variant", asBEHAVE_CONSTRUCT, "void f(int)", asFUNCTION(ConstructVariantInt), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("Variant", asBEHAVE_CONSTRUCT, "void f(uint)", asFUNCTION(ConstructVariantUInt), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("Variant", asBEHAVE_CONSTRUCT, "void f(const StringHash&in)", asFUNCTION(ConstructVariantStringHash), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("Variant", asBEHAVE_CONSTRUCT, "void f(bool)", asFUNCTION(ConstructVariantBool), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("Variant", asBEHAVE_CONSTRUCT, "void f(float)", asFUNCTION(ConstructVariantFloat), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("Variant", asBEHAVE_CONSTRUCT, "void f(const Vector2&in)", asFUNCTION(ConstructVariantVector2), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("Variant", asBEHAVE_CONSTRUCT, "void f(const Vector3&in)", asFUNCTION(ConstructVariantVector3), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("Variant", asBEHAVE_CONSTRUCT, "void f(const Vector4&in)", asFUNCTION(ConstructVariantVector4), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("Variant", asBEHAVE_CONSTRUCT, "void f(const Quaternion&in)", asFUNCTION(ConstructVariantQuaternion), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("Variant", asBEHAVE_CONSTRUCT, "void f(const Color&in)", asFUNCTION(ConstructVariantColor), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("Variant", asBEHAVE_CONSTRUCT, "void f(const String&in)", asFUNCTION(ConstructVariantString), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("Variant", asBEHAVE_CONSTRUCT, "void f(const ResourceRef&in)", asFUNCTION(ConstructVariantResourceRef), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("Variant", asBEHAVE_CONSTRUCT, "void f(const ResourceRefList&in)", asFUNCTION(ConstructVariantResourceRefList), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("Variant", asBEHAVE_CONSTRUCT, "void f(const Array<Variant>@+)", asFUNCTION(ConstructVariantVariantVector), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("Variant", asBEHAVE_CONSTRUCT, "void f(const VariantMap&in)", asFUNCTION(ConstructVariantVariantMap), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("Variant", asBEHAVE_CONSTRUCT, "void f(const IntRect&in)", asFUNCTION(ConstructVariantIntRect), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("Variant", asBEHAVE_CONSTRUCT, "void f(const IntVector2&in)", asFUNCTION(ConstructVariantIntVector2), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("Variant", asBEHAVE_CONSTRUCT, "void f(RefCounted@+)", asFUNCTION(ConstructVariantPtr), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("Variant", asBEHAVE_CONSTRUCT, "void f(ScriptObject@+)", asFUNCTION(ConstructVariantScriptObject), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("Variant", asBEHAVE_CONSTRUCT, "void f(const Matrix3&in)", asFUNCTION(ConstructVariantMatrix3), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("Variant", asBEHAVE_CONSTRUCT, "void f(const Matrix3x4&in)", asFUNCTION(ConstructVariantMatrix3x4), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("Variant", asBEHAVE_CONSTRUCT, "void f(const Matrix4&in)", asFUNCTION(ConstructVariantMatrix4), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("Variant", asBEHAVE_CONSTRUCT, "void f(const String&in, const String&in)", asFUNCTION(ConstructVariantTypeNameValue), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("Variant", asBEHAVE_CONSTRUCT, "void f(VariantType, const String&in)", asFUNCTION(ConstructVariantTypeValue), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("Variant", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(DestructVariant), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("Variant", "void Clear()", asMETHOD(Variant, Clear), asCALL_THISCALL);
    engine->RegisterObjectMethod("Variant", "Variant& opAssign(const Variant&in)", asMETHODPR(Variant, operator =, (const Variant&), Variant&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Variant", "Variant& opAssign(int)", asMETHODPR(Variant, operator =, (int), Variant&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Variant", "Variant& opAssign(uint)", asMETHODPR(Variant, operator =, (unsigned), Variant&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Variant", "Variant& opAssign(const StringHash&in)", asMETHODPR(Variant, operator =, (const StringHash&), Variant&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Variant", "Variant& opAssign(bool)", asMETHODPR(Variant, operator =, (bool), Variant&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Variant", "Variant& opAssign(float)", asMETHODPR(Variant, operator =, (float), Variant&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Variant", "Variant& opAssign(const Vector2&in)", asMETHODPR(Variant, operator =, (const Vector2&), Variant&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Variant", "Variant& opAssign(const Vector3&in)", asMETHODPR(Variant, operator =, (const Vector3&), Variant&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Variant", "Variant& opAssign(const Vector4&in)", asMETHODPR(Variant, operator =, (const Vector4&), Variant&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Variant", "Variant& opAssign(const Quaternion&in)", asMETHODPR(Variant, operator =, (const Quaternion&), Variant&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Variant", "Variant& opAssign(const Color&in)", asMETHODPR(Variant, operator =, (const Color&), Variant&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Variant", "Variant& opAssign(const String&in)", asMETHODPR(Variant, operator =, (const String&), Variant&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Variant", "Variant& opAssign(const ResourceRef&in)", asMETHODPR(Variant, operator =, (const ResourceRef&), Variant&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Variant", "Variant& opAssign(const ResourceRefList&in)", asMETHODPR(Variant, operator =, (const ResourceRefList&), Variant&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Variant", "Variant& opAssign(const Array<Variant>@+)", asFUNCTION(VariantAssignVariantVector), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("Variant", "Variant& opAssign(const VariantMap&in)", asMETHODPR(Variant, operator =, (const VariantMap&), Variant&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Variant", "Variant& opAssign(const IntRect&in)", asMETHODPR(Variant, operator =, (const IntRect&), Variant&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Variant", "Variant& opAssign(const IntVector2&in)", asMETHODPR(Variant, operator =, (const IntVector2&), Variant&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Variant", "Variant& opAssign(RefCounted@+)", asMETHODPR(Variant, operator =, (RefCounted*), Variant&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Variant", "Variant& opAssign(ScriptObject@+)", asMETHODPR(Variant, operator =, (void*), Variant&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Variant", "Variant& opAssign(const Matrix3&in)", asMETHODPR(Variant, operator =, (const Matrix3&), Variant&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Variant", "Variant& opAssign(const Matrix3x4&in)", asMETHODPR(Variant, operator =, (const Matrix3x4&), Variant&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Variant", "Variant& opAssign(const Matrix4&in)", asMETHODPR(Variant, operator =, (const Matrix4&), Variant&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Variant", "bool opEquals(const Variant&in) const", asMETHODPR(Variant, operator ==, (const Variant&) const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Variant", "bool opEquals(int) const", asMETHODPR(Variant, operator ==, (int) const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Variant", "bool opEquals(uint) const", asMETHODPR(Variant, operator ==, (unsigned) const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Variant", "bool opEquals(const StringHash&in) const", asMETHODPR(Variant, operator ==, (const StringHash&) const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Variant", "bool opEquals(bool) const", asMETHODPR(Variant, operator ==, (bool) const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Variant", "bool opEquals(float) const", asMETHODPR(Variant, operator ==, (float) const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Variant", "bool opEquals(const Vector2&in) const", asMETHODPR(Variant, operator ==, (const Vector2&) const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Variant", "bool opEquals(const Vector3&in) const", asMETHODPR(Variant, operator ==, (const Vector3&) const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Variant", "bool opEquals(const Vector4&in) const", asMETHODPR(Variant, operator ==, (const Vector4&) const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Variant", "bool opEquals(const Quaternion&in) const", asMETHODPR(Variant, operator ==, (const Quaternion&) const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Variant", "bool opEquals(const Color&in) const", asMETHODPR(Variant, operator ==, (const Color&) const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Variant", "bool opEquals(const String&in) const", asMETHODPR(Variant, operator ==, (const String&) const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Variant", "bool opEquals(const ResourceRef&in) const", asMETHODPR(Variant, operator ==, (const ResourceRef&) const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Variant", "bool opEquals(const ResourceRefList&in) const", asMETHODPR(Variant, operator ==, (const ResourceRefList&) const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Variant", "bool opEquals(const Array<Variant>@+)", asFUNCTION(VariantEqualsVariantVector), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("Variant", "bool opEquals(const VariantMap&in) const", asMETHODPR(Variant, operator ==, (const VariantMap&) const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Variant", "bool opEquals(const IntRect&in) const", asMETHODPR(Variant, operator ==, (const IntRect&) const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Variant", "bool opEquals(const IntVector2&in) const", asMETHODPR(Variant, operator ==, (const IntVector2&) const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Variant", "bool opEquals(RefCounted@+) const", asMETHODPR(Variant, operator ==, (RefCounted*) const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Variant", "bool opEquals(ScriptObject@+) const", asMETHODPR(Variant, operator ==, (void*) const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Variant", "bool opEquals(const Matrix3&in) const", asMETHODPR(Variant, operator ==, (const Matrix3&) const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Variant", "bool opEquals(const Matrix3x4&in) const", asMETHODPR(Variant, operator ==, (const Matrix3x4&) const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Variant", "bool opEquals(const Matrix4&in) const", asMETHODPR(Variant, operator ==, (const Matrix4&) const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Variant", "int GetInt() const", asMETHOD(Variant, GetInt), asCALL_THISCALL);
    engine->RegisterObjectMethod("Variant", "uint GetUInt() const", asMETHOD(Variant, GetUInt), asCALL_THISCALL);
    engine->RegisterObjectMethod("Variant", "StringHash GetStringHash() const", asMETHOD(Variant, GetStringHash), asCALL_THISCALL);
    engine->RegisterObjectMethod("Variant", "bool GetBool() const", asMETHOD(Variant, GetBool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Variant", "float GetFloat() const", asMETHOD(Variant, GetFloat), asCALL_THISCALL);
    engine->RegisterObjectMethod("Variant", "const Vector2& GetVector2() const", asMETHOD(Variant, GetVector2), asCALL_THISCALL);
    engine->RegisterObjectMethod("Variant", "const Vector3& GetVector3() const", asMETHOD(Variant, GetVector3), asCALL_THISCALL);
    engine->RegisterObjectMethod("Variant", "const Vector4& GetVector4() const", asMETHOD(Variant, GetVector4), asCALL_THISCALL);
    engine->RegisterObjectMethod("Variant", "const Quaternion& GetQuaternion() const", asMETHOD(Variant, GetQuaternion), asCALL_THISCALL);
    engine->RegisterObjectMethod("Variant", "const Color& GetColor() const", asMETHOD(Variant, GetColor), asCALL_THISCALL);
    engine->RegisterObjectMethod("Variant", "const String& GetString() const", asMETHOD(Variant, GetString), asCALL_THISCALL);
    engine->RegisterObjectMethod("Variant", "const ResourceRef& GetResourceRef() const", asMETHOD(Variant, GetResourceRef), asCALL_THISCALL);
    engine->RegisterObjectMethod("Variant", "const ResourceRefList& GetResourceRefList() const", asMETHOD(Variant, GetResourceRefList), asCALL_THISCALL);
    engine->RegisterObjectMethod("Variant", "Array<Variant>@ GetVariantVector() const", asFUNCTION(VariantGetVariantVector), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("Variant", "const VariantMap& GetVariantMap() const", asMETHOD(Variant, GetVariantMap), asCALL_THISCALL);
    engine->RegisterObjectMethod("Variant", "const IntRect& GetIntRect() const", asMETHOD(Variant, GetIntRect), asCALL_THISCALL);
    engine->RegisterObjectMethod("Variant", "const IntVector2& GetIntVector2() const", asMETHOD(Variant, GetIntVector2), asCALL_THISCALL);
    engine->RegisterObjectMethod("Variant", "RefCounted@+ GetPtr() const", asMETHOD(Variant, GetPtr), asCALL_THISCALL);
    engine->RegisterObjectMethod("Variant", "ScriptObject@+ GetScriptObject() const", asFUNCTION(VariantGetScriptObject), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("Variant", "const Matrix3& GetMatrix3() const", asMETHOD(Variant, GetMatrix3), asCALL_THISCALL);
    engine->RegisterObjectMethod("Variant", "const Matrix3x4& GetMatrix3x4() const", asMETHOD(Variant, GetMatrix3x4), asCALL_THISCALL);
    engine->RegisterObjectMethod("Variant", "const Matrix4& GetMatrix4() const", asMETHOD(Variant, GetMatrix4), asCALL_THISCALL);
    engine->RegisterObjectMethod("Variant", "void FromString(const String&in, const String&in)", asMETHODPR(Variant, FromString, (const String&, const String&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Variant", "void FromString(VariantType, const String&in)", asMETHODPR(Variant, FromString, (VariantType, const String&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Variant", "String ToString() const", asMETHOD(Variant, ToString), asCALL_THISCALL);
    engine->RegisterObjectMethod("Variant", "bool get_zero() const", asMETHOD(Variant, IsZero), asCALL_THISCALL);
    engine->RegisterObjectMethod("Variant", "bool get_empty() const", asMETHOD(Variant, IsEmpty), asCALL_THISCALL);
    engine->RegisterObjectMethod("Variant", "VariantType get_type() const", asMETHOD(Variant, GetType), asCALL_THISCALL);
    engine->RegisterObjectMethod("Variant", "String get_typeName() const", asMETHODPR(Variant, GetTypeName, () const, String), asCALL_THISCALL);

    engine->RegisterObjectBehaviour("VariantMap", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(ConstructVariantMap), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("VariantMap", asBEHAVE_CONSTRUCT, "void f(const VariantMap&in)", asFUNCTION(ConstructVariantMapCopy), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("VariantMap", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(DestructVariantMap), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("VariantMap", "VariantMap& opAssign(const VariantMap&in)", asMETHODPR(VariantMap, operator =, (const VariantMap&), VariantMap&), asCALL_THISCALL);
    engine->RegisterObjectMethod("VariantMap", "Variant& opIndex(const String&in)", asFUNCTION(VariantMapAt), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("VariantMap", "const Variant& opIndex(const String&in) const", asFUNCTION(VariantMapAt), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("VariantMap", "Variant& opIndex(StringHash)", asFUNCTION(VariantMapAtHash), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("VariantMap", "const Variant& opIndex(StringHash) const", asFUNCTION(VariantMapAtHash), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("VariantMap", "bool Contains(const String&in) const", asFUNCTION(VariantMapContains), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("VariantMap", "bool Erase(const String&in)", asFUNCTION(VariantMapErase), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("VariantMap", "bool Contains(StringHash) const", asFUNCTION(VariantMapContainsHash), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("VariantMap", "bool Erase(StringHash)", asFUNCTION(VariantMapEraseHash), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("VariantMap", "void Clear()", asMETHOD(VariantMap, Clear), asCALL_THISCALL);
    engine->RegisterObjectMethod("VariantMap", "uint get_length() const", asMETHOD(VariantMap, Size), asCALL_THISCALL);
    engine->RegisterObjectMethod("VariantMap", "Array<StringHash>@ get_keys() const", asFUNCTION(VariantMapGetKeys), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("VariantMap", "Array<Variant>@ get_values() const", asFUNCTION(VariantMapGetValues), asCALL_CDECL_OBJLAST);
}

static void ConstructSpline(Spline* ptr)
{
    new (ptr) Spline();
}

static void ConstructSpline(InterpolationMode mode, Spline* ptr)
{
    new (ptr) Spline(mode);
}

static void ConstructSpline(CScriptArray* arr, InterpolationMode mode, Spline* ptr)
{
    new (ptr) Spline(ArrayToVector<Variant>(arr), mode);
}

static void ConstructSpline(const Spline& rhs, Spline* ptr)
{
    new (ptr) Spline(rhs);
}

static CScriptArray* GetSplineKnots(Spline* ptr)
{
    return VectorToArray(ptr->GetKnots(), "Array<Variant>");
}

static void SetSplineKnots(CScriptArray* arr, Spline* ptr)
{
    ptr->SetKnots(ArrayToVector<Variant>(arr));
}

static void SetSplineKnot(unsigned index, const Variant& in, Spline* ptr)
{
    ptr->SetKnot(in, index);
}

static void RegisterSpline(asIScriptEngine* engine)
{
    engine->RegisterEnum("InterpolationMode");
    engine->RegisterEnumValue("InterpolationMode", "BEZIER_CURVE", BEZIER_CURVE);

    engine->RegisterObjectType("Spline", sizeof(Spline), asOBJ_VALUE | asOBJ_POD | asOBJ_APP_CLASS_CAK);
    engine->RegisterObjectBehaviour("Spline", asBEHAVE_CONSTRUCT, "void f()", asFUNCTIONPR(ConstructSpline, (Spline*), void), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("Spline", asBEHAVE_CONSTRUCT, "void f(InterpolationMode)", asFUNCTIONPR(ConstructSpline, (InterpolationMode, Spline*), void), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("Spline", asBEHAVE_CONSTRUCT, "void f(Array<Variant>@+, InterpolationMode = BEZIER_CURVE)", asFUNCTIONPR(ConstructSpline, (CScriptArray*, InterpolationMode, Spline*), void), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("Spline", asBEHAVE_CONSTRUCT, "void f(const Spline&in)", asFUNCTIONPR(ConstructSpline, (const Spline&, Spline*), void), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("Spline", "Spline& opAssign(const Spline&in)", asMETHOD(Spline, operator =), asCALL_THISCALL);
    engine->RegisterObjectMethod("Spline", "bool opEquals(const Spline&in) const", asMETHOD(Spline, operator ==), asCALL_THISCALL);

    engine->RegisterObjectMethod("Spline", "InterpolationMode get_interpolationMode() const", asMETHOD(Spline, GetInterpolationMode), asCALL_THISCALL);
    engine->RegisterObjectMethod("Spline", "void set_interpolationMode(InterpolationMode)", asMETHOD(Spline, SetInterpolationMode), asCALL_THISCALL);
    engine->RegisterObjectMethod("Spline", "Array<Variant>@ get_knots() const", asFUNCTION(GetSplineKnots), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("Spline", "void set_knots(Array<Variant>@+)", asFUNCTION(SetSplineKnots), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("Spline", "Variant get_knot(uint) const", asMETHOD(Spline, GetKnot), asCALL_THISCALL);
    engine->RegisterObjectMethod("Spline", "void set_knot(uint, const Variant&in)", asFUNCTION(SetSplineKnot), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("Spline", "void AddKnot(const Variant&in)", asMETHODPR(Spline, AddKnot, (const Variant&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Spline", "void AddKnot(const Variant&in, uint)", asMETHODPR(Spline, AddKnot, (const Variant&, unsigned), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Spline", "void RemoveKnot()", asMETHODPR(Spline, RemoveKnot, (), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Spline", "void RemoveKnot(uint)", asMETHODPR(Spline, RemoveKnot, (unsigned), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Spline", "void Clear()", asMETHOD(Spline, Clear), asCALL_THISCALL);
    engine->RegisterObjectMethod("Spline", "Variant GetPoint(float)", asMETHOD(Spline, GetPoint), asCALL_THISCALL);
}

static CScriptArray* StringSplit(char separator, const String* str)
{
    Vector<String> result = str->Split(separator);
    return VectorToArray<String>(result, "Array<String>");
}

static void StringJoin(CScriptArray* arr, const String& glue, String* str)
{
    Vector<String> subStrings = ArrayToVector<String>(arr);
    str->Join(subStrings, glue);
}

static String StringJoined(CScriptArray* arr, const String& glue)
{
    Vector<String> subStrings = ArrayToVector<String>(arr);
    return String::Joined(subStrings, glue);
}

static void RegisterStringUtils(asIScriptEngine* engine)
{
    engine->RegisterObjectMethod("String", "Array<String>@ Split(uint8) const", asFUNCTION(StringSplit), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("String", "void Join(String[]&, const String&in)", asFUNCTION(StringJoin), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("String", "bool ToBool() const", asFUNCTIONPR(ToBool, (const String&), bool), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("String", "float ToFloat() const", asFUNCTIONPR(ToFloat, (const String&), float), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("String", "int ToInt() const", asFUNCTIONPR(ToInt, (const String&), int), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("String", "uint ToUInt() const", asFUNCTIONPR(ToUInt, (const String&), unsigned), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("String", "Color ToColor() const", asFUNCTIONPR(ToColor, (const String&), Color), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("String", "IntRect ToIntRect() const", asFUNCTIONPR(ToIntRect, (const String&), IntRect), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("String", "IntVector2 ToIntVector2() const", asFUNCTIONPR(ToIntVector2, (const String&), IntVector2), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("String", "Quaternion ToQuaternion() const", asFUNCTIONPR(ToQuaternion, (const String&), Quaternion), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("String", "Vector2 ToVector2() const", asFUNCTIONPR(ToVector2, (const String&), Vector2), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("String", "Vector3 ToVector3() const", asFUNCTIONPR(ToVector3, (const String&), Vector3), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("String", "Vector4 ToVector4(bool allowMissingCoords = false) const", asFUNCTIONPR(ToVector4, (const String&, bool), Vector4), asCALL_CDECL_OBJFIRST);
    engine->RegisterObjectMethod("String", "Variant ToVectorVariant() const", asFUNCTIONPR(ToVectorVariant, (const String&), Variant), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("String", "Matrix3 ToMatrix3() const", asFUNCTIONPR(ToMatrix3, (const String&), Matrix3), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("String", "Matrix3x4 ToMatrix3x4() const", asFUNCTIONPR(ToMatrix3x4, (const String&), Matrix3x4), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("String", "Matrix4 ToMatrix4() const", asFUNCTIONPR(ToMatrix4, (const String&), Matrix4), asCALL_CDECL_OBJLAST);
    engine->RegisterGlobalFunction("String ToStringHex(int)", asFUNCTION(ToStringHex), asCALL_CDECL);
    engine->RegisterGlobalFunction("String Join(String[]&, const String&in glue)", asFUNCTION(StringJoined), asCALL_CDECL);
    engine->RegisterGlobalFunction("bool IsDigit(uint)", asFUNCTION(IsDigit), asCALL_CDECL);
    engine->RegisterGlobalFunction("bool IsAlpha(uint)", asFUNCTION(IsAlpha), asCALL_CDECL);
    engine->RegisterGlobalFunction("uint ToUpper(uint)", asFUNCTION(ToUpper), asCALL_CDECL);
    engine->RegisterGlobalFunction("uint ToLower(uint)", asFUNCTION(ToLower), asCALL_CDECL);
}

static void ConstructTimer(Timer* ptr)
{
    new(ptr) Timer();
}

static Time* GetTime()
{
    return GetScriptContext()->GetSubsystem<Time>();
}

static unsigned TimeGetSystemTime(Time* time)
{
    return Time::GetSystemTime();
}

static unsigned TimeGetTimeSinceEpoch(Time* time)
{
    return Time::GetTimeSinceEpoch();
}

static String TimeGetTimeStamp(Time* time)
{
    return Time::GetTimeStamp();
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
    engine->RegisterObjectMethod("Time", "float get_elapsedTime()", asMETHOD(Time, GetElapsedTime), asCALL_THISCALL);
    engine->RegisterObjectMethod("Time", "uint get_systemTime() const", asFUNCTION(TimeGetSystemTime), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("Time", "uint get_timeSinceEpoch() const", asFUNCTION(TimeGetTimeSinceEpoch), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("Time", "String get_timeStamp() const", asFUNCTION(TimeGetTimeStamp), asCALL_CDECL_OBJLAST);
    engine->RegisterGlobalFunction("Time@+ get_time()", asFUNCTION(GetTime), asCALL_CDECL);
}

static CScriptArray* GetArgumentsToArray()
{
    return VectorToArray<String>(GetArguments(), "Array<String>");
}

static void RegisterProcessUtils(asIScriptEngine* engine)
{
    engine->RegisterGlobalFunction("void ErrorDialog(const String&in, const String&in)", asFUNCTION(ErrorDialog), asCALL_CDECL);
    engine->RegisterGlobalFunction("void OpenConsoleWindow()", asFUNCTION(OpenConsoleWindow), asCALL_CDECL);
    engine->RegisterGlobalFunction("String GetConsoleInput()", asFUNCTION(GetConsoleInput), asCALL_CDECL);
    engine->RegisterGlobalFunction("Array<String>@ GetArguments()", asFUNCTION(GetArgumentsToArray), asCALL_CDECL);
    engine->RegisterGlobalFunction("String GetPlatform()", asFUNCTION(GetPlatform), asCALL_CDECL);
    engine->RegisterGlobalFunction("uint GetNumPhysicalCPUs()", asFUNCTION(GetNumPhysicalCPUs), asCALL_CDECL);
    engine->RegisterGlobalFunction("uint GetNumLogicalCPUs()", asFUNCTION(GetNumLogicalCPUs), asCALL_CDECL);
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

static CScriptArray* AttributeInfoGetEnumNames(AttributeInfo* ptr)
{
    Vector<String> enumNames;
    const char** enumNamePtrs = ptr->enumNames_;
    while (enumNamePtrs && *enumNamePtrs)
        enumNames.Push(*enumNamePtrs++);
    return VectorToArray<String>(enumNames, "Array<String>");
}

static void SendEvent(const String& eventType, VariantMap& eventData)
{
    Object* sender = GetScriptContextEventListenerObject();
    if (sender)
        sender->SendEvent(eventType, eventData);
}

static void SubscribeToEvent(const String& eventType, const String& handlerName)
{
    ScriptEventListener* listener = GetScriptContextEventListener();
    if (listener)
        listener->AddEventHandler(eventType, handlerName);
}

static void SubscribeToSenderEvent(Object* sender, const String& eventType, const String& handlerName)
{
    ScriptEventListener* listener = GetScriptContextEventListener();
    if (listener)
        listener->AddEventHandler(sender, eventType, handlerName);
}

static void UnsubscribeFromEvent(const String& eventType)
{
    ScriptEventListener* listener = GetScriptContextEventListener();
    if (listener)
        listener->RemoveEventHandler(eventType);
}

static void UnsubscribeFromSenderEvent(Object* sender, const String& eventType)
{
    ScriptEventListener* listener = GetScriptContextEventListener();
    if (listener)
        listener->RemoveEventHandler(sender, eventType);
}

static void UnsubscribeFromSenderEvents(Object* sender)
{
    ScriptEventListener* listener = GetScriptContextEventListener();
    if (listener)
        listener->RemoveEventHandlers(sender);
}

static void UnsubscribeFromAllEvents()
{
    ScriptEventListener* listener = GetScriptContextEventListener();
    if (listener)
        listener->RemoveEventHandlers();
}

static void UnsubscribeFromAllEventsExcept(CScriptArray* exceptions)
{
    ScriptEventListener* listener = GetScriptContextEventListener();
    if (!listener || !exceptions)
        return;

    unsigned numExceptions = exceptions->GetSize();
    PODVector<StringHash> destExceptions(numExceptions);
    for (unsigned i = 0; i < numExceptions; ++i)
        destExceptions[i] = StringHash(*(static_cast<String*>(exceptions->At(i))));

    listener->RemoveEventHandlersExcept(destExceptions);
}

static Object* GetEventSender()
{
    return GetScriptContext()->GetEventSender();
}

static const String& GetTypeName(StringHash type)
{
    return GetScriptContext()->GetTypeName(type);
}

static void ConstructWeakHandle(WeakPtr<RefCounted>* ptr)
{
    new(ptr) WeakPtr<RefCounted>();
}

static void ConstructWeakHandleCopy(const WeakPtr<RefCounted>& src, WeakPtr<RefCounted>* ptr)
{
    new(ptr) WeakPtr<RefCounted>(src);
}

static void ConstructWeakHandlePtr(RefCounted* object, WeakPtr<RefCounted>* ptr)
{
    new(ptr) WeakPtr<RefCounted>(object);
}

static void DestructWeakHandle(WeakPtr<RefCounted>* ptr)
{
    ptr->~WeakPtr<RefCounted>();
}

void RegisterObject(asIScriptEngine* engine)
{
    engine->RegisterObjectType("AttributeInfo", sizeof(AttributeInfo), asOBJ_VALUE | asOBJ_APP_CLASS_CDAK);
    engine->RegisterObjectBehaviour("AttributeInfo", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(ConstructAttributeInfo), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("AttributeInfo", asBEHAVE_CONSTRUCT, "void f(const AttributeInfo&in)", asFUNCTION(ConstructAttributeInfoCopy), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("AttributeInfo", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(DestructAttributeInfo), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("AttributeInfo", "AttributeInfo& opAssign(const AttributeInfo&in)", asMETHODPR(AttributeInfo, operator =, (const AttributeInfo&), AttributeInfo&), asCALL_THISCALL);
    engine->RegisterObjectMethod("AttributeInfo", "Array<String>@ get_enumNames() const", asFUNCTION(AttributeInfoGetEnumNames), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectProperty("AttributeInfo", "VariantType type", offsetof(AttributeInfo, type_));
    engine->RegisterObjectProperty("AttributeInfo", "String name", offsetof(AttributeInfo, name_));
    engine->RegisterObjectProperty("AttributeInfo", "Variant defaultValue", offsetof(AttributeInfo, defaultValue_));
    engine->RegisterObjectProperty("AttributeInfo", "uint mode", offsetof(AttributeInfo, mode_));

    RegisterObject<Object>(engine, "Object");

    engine->RegisterGlobalFunction("void SendEvent(const String&in, VariantMap& eventData = VariantMap())", asFUNCTION(SendEvent), asCALL_CDECL);
    engine->RegisterGlobalFunction("void SubscribeToEvent(const String&in, const String&in)", asFUNCTION(SubscribeToEvent), asCALL_CDECL);
    engine->RegisterGlobalFunction("void SubscribeToEvent(Object@+, const String&in, const String&in)", asFUNCTION(SubscribeToSenderEvent), asCALL_CDECL);
    engine->RegisterGlobalFunction("void UnsubscribeFromEvent(const String&in)", asFUNCTION(UnsubscribeFromEvent), asCALL_CDECL);
    engine->RegisterGlobalFunction("void UnsubscribeFromEvent(Object@+, const String&in)", asFUNCTION(UnsubscribeFromSenderEvent), asCALL_CDECL);
    engine->RegisterGlobalFunction("void UnsubscribeFromEvents(Object@+)", asFUNCTION(UnsubscribeFromSenderEvents), asCALL_CDECL);
    engine->RegisterGlobalFunction("void UnsubscribeFromAllEvents()", asFUNCTION(UnsubscribeFromAllEvents), asCALL_CDECL);
    engine->RegisterGlobalFunction("void UnsubscribeFromAllEventsExcept(Array<String>@+)", asFUNCTION(UnsubscribeFromAllEventsExcept), asCALL_CDECL);
    engine->RegisterGlobalFunction("Object@+ GetEventSender()", asFUNCTION(GetEventSender), asCALL_CDECL);
    engine->RegisterGlobalFunction("const String& GetTypeName(StringHash)", asFUNCTION(GetTypeName), asCALL_CDECL);

    engine->RegisterObjectType("WeakHandle", sizeof(WeakPtr<RefCounted>), asOBJ_VALUE | asOBJ_APP_CLASS_CDAK);
    engine->RegisterObjectBehaviour("WeakHandle", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(ConstructWeakHandle), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("WeakHandle", asBEHAVE_CONSTRUCT, "void f(const WeakHandle&in)", asFUNCTION(ConstructWeakHandleCopy), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("WeakHandle", asBEHAVE_CONSTRUCT, "void f(RefCounted@+)", asFUNCTION(ConstructWeakHandlePtr), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("WeakHandle", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(DestructWeakHandle), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("WeakHandle", "WeakHandle& opAssign(const WeakHandle&in)", asMETHODPR(WeakPtr<RefCounted>, operator =, (const WeakPtr<RefCounted>&), WeakPtr<RefCounted>&), asCALL_THISCALL);
    engine->RegisterObjectMethod("WeakHandle", "WeakHandle& opAssign(RefCounted@+)", asMETHODPR(WeakPtr<RefCounted>, operator =, (RefCounted*), WeakPtr<RefCounted>&), asCALL_THISCALL);
    engine->RegisterObjectMethod("WeakHandle", "RefCounted@+ Get() const", asMETHODPR(WeakPtr<RefCounted>, Get, () const, RefCounted*), asCALL_THISCALL);
    engine->RegisterObjectMethod("WeakHandle", "int get_refs() const", asMETHOD(WeakPtr<RefCounted>, Refs), asCALL_THISCALL);
    engine->RegisterObjectMethod("WeakHandle", "int get_weakRefs() const", asMETHOD(WeakPtr<RefCounted>, WeakRefs), asCALL_THISCALL);
    engine->RegisterObjectMethod("WeakHandle", "bool get_expired() const", asMETHOD(WeakPtr<RefCounted>, Expired), asCALL_THISCALL);
}

void RegisterCoreAPI(asIScriptEngine* engine)
{
    RegisterStringHash(engine);
    RegisterVariant(engine);
    RegisterSpline(engine);
    RegisterStringUtils(engine);
    RegisterProcessUtils(engine);
    RegisterObject(engine);
    RegisterTimer(engine);
}

}
