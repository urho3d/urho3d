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
#include "Log.h"
#include "PackageFile.h"
#include "ProcessUtils.h"
#include "RegisterTemplates.h"
#include "ScriptInstance.h"
#include "StringUtils.h"
#include "VectorBuffer.h"

void FakeAddRef(void* ptr)
{
}

void FakeReleaseRef(void* ptr)
{
}

static void ConstructColor(Color* ptr)
{
    new(ptr) Color();
}

static void ConstructColorCopy(const Color& color, Color* ptr)
{
    new(ptr) Color(color);
}

static void ConstructColorRGBA(float r, float g, float b, float a, Color* ptr)
{
    new(ptr) Color(r, g, b, a);
}

static void ConstructColorRGB(float r, float g, float b, Color* ptr)
{
    new(ptr) Color(r, g, b);
}

static void registerColor(asIScriptEngine* engine)
{
    engine->RegisterObjectType("Color", sizeof(Color), asOBJ_VALUE | asOBJ_POD | asOBJ_APP_CLASS_CA);
    engine->RegisterObjectBehaviour("Color", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(ConstructColor), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("Color", asBEHAVE_CONSTRUCT, "void f(const Color& in)", asFUNCTION(ConstructColorCopy), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("Color", asBEHAVE_CONSTRUCT, "void f(float, float, float, float)", asFUNCTION(ConstructColorRGBA), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("Color", asBEHAVE_CONSTRUCT, "void f(float, float, float)", asFUNCTION(ConstructColorRGB), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("Color", "Color &opAssign(const Color& in)", asMETHOD(Color, operator =), asCALL_THISCALL);
    engine->RegisterObjectMethod("Color", "Color &opAddAssign(const Color& in)", asMETHOD(Color, operator +=), asCALL_THISCALL);
    engine->RegisterObjectMethod("Color", "bool opEquals(const Color& in) const", asMETHOD(Color, operator ==), asCALL_THISCALL);
    engine->RegisterObjectMethod("Color", "Color opMul(float) const", asMETHOD(Color, operator *), asCALL_THISCALL);
    engine->RegisterObjectMethod("Color", "Color opAdd(const Color& in) const", asMETHOD(Color, operator +), asCALL_THISCALL);
    engine->RegisterObjectMethod("Color", "Vector3 getRGB() const", asMETHOD(Color, getRGB), asCALL_THISCALL);
    engine->RegisterObjectMethod("Color", "Color lerp(const Color& in, float) const", asMETHOD(Color, lerp), asCALL_THISCALL);
    engine->RegisterObjectMethod("Color", "string toString() const", asFUNCTIONPR(toString, (const Color&), std::string), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectProperty("Color", "float r", offsetof(Color, mR));
    engine->RegisterObjectProperty("Color", "float g", offsetof(Color, mG));
    engine->RegisterObjectProperty("Color", "float b", offsetof(Color, mB));
    engine->RegisterObjectProperty("Color", "float a", offsetof(Color, mA));
}

static void Print(const std::string& str)
{
    LOGRAW(str + "\n");
}

static void PrintInt(int value)
{
    LOGRAW(toString(value) + "\n");
}

static void PrintFloat(float value)
{
    LOGRAW(toString(value) + "\n");
}

static void PrintBool(bool value)
{
    LOGRAW(toString(value) + "\n");
}

static void LogDebug(const std::string& str)
{
    LOGDEBUG(str);
}

static void LogInfo(const std::string& str)
{
    LOGINFO(str);
}

static void LogWarning(const std::string& str)
{
    LOGWARNING(str);
}

static void LogError(const std::string& str)
{
    LOGERROR(str);
}

static void registerLog(asIScriptEngine* engine)
{
    engine->RegisterGlobalFunction("void print(const string& in)", asFUNCTION(Print), asCALL_CDECL);
    engine->RegisterGlobalFunction("void print(int)", asFUNCTION(PrintInt), asCALL_CDECL);
    engine->RegisterGlobalFunction("void print(float)", asFUNCTION(PrintFloat), asCALL_CDECL);
    engine->RegisterGlobalFunction("void print(bool)", asFUNCTION(PrintBool), asCALL_CDECL);
    engine->RegisterGlobalFunction("void logDebug(const string& in)", asFUNCTION(LogDebug), asCALL_CDECL);
    engine->RegisterGlobalFunction("void logInfo(const string& in)", asFUNCTION(LogInfo), asCALL_CDECL);
    engine->RegisterGlobalFunction("void logWarning(const string& in)", asFUNCTION(LogWarning), asCALL_CDECL);
    engine->RegisterGlobalFunction("void logError(const string& in)", asFUNCTION(LogError), asCALL_CDECL);
}

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

static void RegisterHash(const std::string& str)
{
    // Do not throw when a script registers a hash
    registerHash(str, false);
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

static void RegisterShortHash(const std::string& str)
{
    // Do not throw when a script registers a short hash
    registerShortHash(str, false);
}

static void registerStringHash(asIScriptEngine* engine)
{
    engine->RegisterObjectType("StringHash", sizeof(StringHash), asOBJ_VALUE | asOBJ_POD | asOBJ_APP_CLASS_CA);
    engine->RegisterObjectBehaviour("StringHash", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(ConstructStringHash), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("StringHash", asBEHAVE_CONSTRUCT, "void f(const StringHash& in)", asFUNCTION(ConstructStringHashCopy), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("StringHash", asBEHAVE_CONSTRUCT, "void f(const string& in)", asFUNCTION(ConstructStringHashInit), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("StringHash", "StringHash &opAssign(const StringHash& in)", asMETHOD(StringHash, operator =), asCALL_THISCALL);
    engine->RegisterObjectMethod("StringHash", "StringHash &opAddAssign(const StringHash& in)", asMETHOD(StringHash, operator +=), asCALL_THISCALL);
    engine->RegisterObjectMethod("StringHash", "bool opEquals(const StringHash& in) const", asMETHOD(StringHash, operator ==), asCALL_THISCALL);
    engine->RegisterObjectMethod("StringHash", "int opCmp(const StringHash& in) const", asFUNCTION(StringHashCmp), asCALL_CDECL_OBJFIRST);
    engine->RegisterObjectMethod("StringHash", "StringHash opAdd(const StringHash& in) const", asMETHOD(StringHash, operator +), asCALL_THISCALL);
    engine->RegisterObjectMethod("StringHash", "string toString() const", asFUNCTIONPR(toString, (const StringHash&), std::string), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectProperty("StringHash", "uint data", offsetof(StringHash, mData));
    
    engine->RegisterObjectType("ShortStringHash", sizeof(ShortStringHash), asOBJ_VALUE | asOBJ_POD | asOBJ_APP_CLASS_CA);
    engine->RegisterObjectBehaviour("ShortStringHash", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(ConstructShortStringHash), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("ShortStringHash", asBEHAVE_CONSTRUCT, "void f(const ShortStringHash& in)", asFUNCTION(ConstructShortStringHashCopyShort), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("ShortStringHash", asBEHAVE_CONSTRUCT, "void f(const StringHash& in)", asFUNCTION(ConstructShortStringHashCopyLong), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("ShortStringHash", asBEHAVE_CONSTRUCT, "void f(const string& in)", asFUNCTION(ConstructShortStringHashInit), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("ShortStringHash", "ShortStringHash &opAssign(const ShortStringHash& in)", asMETHODPR(ShortStringHash, operator =, (const ShortStringHash&), ShortStringHash&), asCALL_THISCALL);
    engine->RegisterObjectMethod("ShortStringHash", "bool opEquals(const ShortStringHash& in) const", asMETHOD(ShortStringHash, operator ==), asCALL_THISCALL);
    engine->RegisterObjectMethod("ShortStringHash", "int opCmp(const ShortStringHash& in) const", asFUNCTION(ShortStringHashCmp), asCALL_CDECL_OBJFIRST);
    engine->RegisterObjectMethod("ShortStringHash", "string toString() const", asFUNCTIONPR(toString, (const ShortStringHash&), std::string), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectProperty("ShortStringHash", "uint16 data", offsetof(ShortStringHash, mData));
    
    engine->RegisterGlobalFunction("void registerHash(const string& in)", asFUNCTION(RegisterHash), asCALL_CDECL);
    engine->RegisterGlobalFunction("const string& hashToString(const StringHash& in)", asFUNCTION(hashToString), asCALL_CDECL);
    engine->RegisterGlobalFunction("void registerShortHash(const string& in)", asFUNCTION(RegisterShortHash), asCALL_CDECL);
    engine->RegisterGlobalFunction("const string& shortHashToString(const ShortStringHash& in)", asFUNCTION(shortHashToString), asCALL_CDECL);
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

void arrayToVariantVector(CScriptArray* arr, VariantVector& dest)
{
    unsigned numVariants = arr->GetSize();
    dest.resize(numVariants);
    for (unsigned i = 0; i < numVariants; ++i)
        dest[i] = *(static_cast<Variant*>(arr->At(i)));
}

static void ConstructVariantVariantVector(CScriptArray* value, Variant* ptr)
{
    VariantVector vector;
    arrayToVariantVector(value, vector);
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
    arrayToVariantVector(value, vector);
    *ptr = vector;
    return *ptr;
}

static bool VariantEqualsVariantVector(CScriptArray* value, Variant* ptr)
{
    VariantVector vector;
    arrayToVariantVector(value, vector);
    return *ptr == vector;
}

static CScriptArray* VariantGetVariantVector(Variant* ptr)
{
    return vectorToArray<Variant>(ptr->getVariantVector(), "array<Variant>");
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

static void registerVariant(asIScriptEngine* engine)
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
    engine->RegisterEnumValue("VariantType", "VAR_VARIANTVECTOR", VAR_VARIANTVECTOR);
    engine->RegisterEnumValue("VariantType", "VAR_VARIANTMAP", VAR_VARIANTMAP);
    
    engine->RegisterObjectType("Variant", sizeof(Variant), asOBJ_VALUE | asOBJ_APP_CLASS_CDA);
    engine->RegisterObjectType("VariantMap", sizeof(VariantMap), asOBJ_VALUE | asOBJ_APP_CLASS_CDA);
    engine->RegisterObjectBehaviour("Variant", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(ConstructVariant), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("Variant", asBEHAVE_CONSTRUCT, "void f(const Variant& in)", asFUNCTION(ConstructVariantCopy), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("Variant", asBEHAVE_CONSTRUCT, "void f(int)", asFUNCTION(ConstructVariantInt), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("Variant", asBEHAVE_CONSTRUCT, "void f(uint)", asFUNCTION(ConstructVariantUInt), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("Variant", asBEHAVE_CONSTRUCT, "void f(const StringHash& in)", asFUNCTION(ConstructVariantStringHash), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("Variant", asBEHAVE_CONSTRUCT, "void f(const ShortStringHash& in)", asFUNCTION(ConstructVariantShortStringHash), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("Variant", asBEHAVE_CONSTRUCT, "void f(bool)", asFUNCTION(ConstructVariantBool), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("Variant", asBEHAVE_CONSTRUCT, "void f(float)", asFUNCTION(ConstructVariantFloat), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("Variant", asBEHAVE_CONSTRUCT, "void f(const Vector2& in)", asFUNCTION(ConstructVariantVector2), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("Variant", asBEHAVE_CONSTRUCT, "void f(const Vector3& in)", asFUNCTION(ConstructVariantVector3), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("Variant", asBEHAVE_CONSTRUCT, "void f(const Quaternion& in)", asFUNCTION(ConstructVariantQuaternion), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("Variant", asBEHAVE_CONSTRUCT, "void f(const Color& in)", asFUNCTION(ConstructVariantColor), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("Variant", asBEHAVE_CONSTRUCT, "void f(const string& in)", asFUNCTION(ConstructVariantString), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("Variant", asBEHAVE_CONSTRUCT, "void f(const array<Variant>@+)", asFUNCTION(ConstructVariantVariantVector), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("Variant", asBEHAVE_CONSTRUCT, "void f(const VariantMap& in)", asFUNCTION(ConstructVariantVariantMap), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("Variant", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(DestructVariant), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("Variant", "void clear()", asMETHOD(Variant, clear), asCALL_THISCALL);
    engine->RegisterObjectMethod("Variant", "Variant &opAssign(const Variant& in)", asMETHODPR(Variant, operator =, (const Variant&), Variant&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Variant", "Variant &opAssign(int)", asMETHODPR(Variant, operator =, (int), Variant&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Variant", "Variant &opAssign(uint)", asMETHODPR(Variant, operator =, (unsigned), Variant&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Variant", "Variant &opAssign(const StringHash& in)", asMETHODPR(Variant, operator =, (const StringHash&), Variant&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Variant", "Variant &opAssign(const ShortStringHash& in)", asMETHODPR(Variant, operator =, (const ShortStringHash&), Variant&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Variant", "Variant &opAssign(bool)", asMETHODPR(Variant, operator =, (bool), Variant&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Variant", "Variant &opAssign(float)", asMETHODPR(Variant, operator =, (float), Variant&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Variant", "Variant &opAssign(const Vector2& in)", asMETHODPR(Variant, operator =, (const Vector2&), Variant&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Variant", "Variant &opAssign(const Vector3& in)", asMETHODPR(Variant, operator =, (const Vector3&), Variant&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Variant", "Variant &opAssign(const Quaternion& in)", asMETHODPR(Variant, operator =, (const Quaternion&), Variant&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Variant", "Variant &opAssign(const Color& in)", asMETHODPR(Variant, operator =, (const Color&), Variant&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Variant", "Variant &opAssign(const string& in)", asMETHODPR(Variant, operator =, (const std::string&), Variant&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Variant", "Variant &opAssign(const array<Variant>@+)", asFUNCTION(VariantAssignVariantVector), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("Variant", "Variant &opAssign(const VariantMap& in)", asMETHODPR(Variant, operator =, (const VariantMap&), Variant&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Variant", "bool opEquals(const Variant& in) const", asMETHODPR(Variant, operator ==, (const Variant&) const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Variant", "bool opEquals(int) const", asMETHODPR(Variant, operator ==, (int) const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Variant", "bool opEquals(uint) const", asMETHODPR(Variant, operator ==, (unsigned) const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Variant", "bool opEquals(const StringHash& in) const", asMETHODPR(Variant, operator ==, (const StringHash&) const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Variant", "bool opEquals(const ShortStringHash& in) const", asMETHODPR(Variant, operator ==, (const ShortStringHash&) const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Variant", "bool opEquals(bool) const", asMETHODPR(Variant, operator ==, (bool) const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Variant", "bool opEquals(float) const", asMETHODPR(Variant, operator ==, (float) const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Variant", "bool opEquals(const Vector2& in) const", asMETHODPR(Variant, operator ==, (const Vector2&) const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Variant", "bool opEquals(const Vector3& in) const", asMETHODPR(Variant, operator ==, (const Vector3&) const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Variant", "bool opEquals(const Quaternion& in) const", asMETHODPR(Variant, operator ==, (const Quaternion&) const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Variant", "bool opEquals(const Color& in) const", asMETHODPR(Variant, operator ==, (const Color&) const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Variant", "bool opEquals(const string& in) const", asMETHODPR(Variant, operator ==, (const std::string&) const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Variant", "bool opEquals(const array<Variant>@+)", asFUNCTION(VariantEqualsVariantVector), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("Variant", "bool opEquals(const VariantMap& in) const", asMETHODPR(Variant, operator ==, (const VariantMap&) const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Variant", "int getInt() const", asMETHOD(Variant, getInt), asCALL_THISCALL);
    engine->RegisterObjectMethod("Variant", "uint getUInt() const", asMETHOD(Variant, getUInt), asCALL_THISCALL);
    engine->RegisterObjectMethod("Variant", "StringHash getStringHash() const", asMETHOD(Variant, getStringHash), asCALL_THISCALL);
    engine->RegisterObjectMethod("Variant", "ShortStringHash getShortStringHash() const", asMETHOD(Variant, getShortStringHash), asCALL_THISCALL);
    engine->RegisterObjectMethod("Variant", "bool getBool() const", asMETHOD(Variant, getBool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Variant", "float getFloat() const", asMETHOD(Variant, getFloat), asCALL_THISCALL);
    engine->RegisterObjectMethod("Variant", "const Vector2& getVector2() const", asMETHOD(Variant, getVector2), asCALL_THISCALL);
    engine->RegisterObjectMethod("Variant", "const Vector3& getVector3() const", asMETHOD(Variant, getVector3), asCALL_THISCALL);
    engine->RegisterObjectMethod("Variant", "const Quaternion& getQuaternion() const", asMETHOD(Variant, getQuaternion), asCALL_THISCALL);
    engine->RegisterObjectMethod("Variant", "const Color& getColor() const", asMETHOD(Variant, getColor), asCALL_THISCALL);
    engine->RegisterObjectMethod("Variant", "const string& getString() const", asMETHOD(Variant, getString), asCALL_THISCALL);
    engine->RegisterObjectMethod("Variant", "array<Variant>@ getVariantVector() const", asFUNCTION(VariantGetVariantVector), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("Variant", "const VariantMap& getVariantMap() const", asMETHOD(Variant, getVariantMap), asCALL_THISCALL);
    engine->RegisterObjectMethod("Variant", "void fromString(const string& in, const string& in)", asMETHOD(Variant, fromString), asCALL_THISCALL);
    engine->RegisterObjectMethod("Variant", "VariantType getType() const", asMETHOD(Variant, getType), asCALL_THISCALL);
    engine->RegisterObjectMethod("Variant", "const string &getTypeName() const", asMETHOD(Variant, getTypeName), asCALL_THISCALL);
    engine->RegisterObjectMethod("Variant", "string toString() const", asMETHOD(Variant, toString), asCALL_THISCALL);
    
    engine->RegisterObjectBehaviour("VariantMap", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(ConstructVariantMap), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("VariantMap", asBEHAVE_CONSTRUCT, "void f(const VariantMap& in)", asFUNCTION(ConstructVariantMapCopy), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("VariantMap", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(DestructVariantMap), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("VariantMap", "VariantMap& opAssign(const VariantMap& in)", asMETHODPR(VariantMap, operator =, (const VariantMap&), VariantMap&), asCALL_THISCALL);
    engine->RegisterObjectMethod("VariantMap", "Variant& opIndex(const string& in)", asFUNCTION(VariantMapAt), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("VariantMap", "const Variant& opIndex(const string& in) const", asFUNCTION(VariantMapAt), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("VariantMap", "uint size() const", asMETHOD(VariantMap, size), asCALL_THISCALL);
    engine->RegisterObjectMethod("VariantMap", "bool contains(const string& in) const", asFUNCTION(VariantMapContains), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("VariantMap", "void erase(const string& in)", asFUNCTION(VariantMapErase), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("VariantMap", "void clear()", asMETHOD(VariantMap, clear), asCALL_THISCALL);
}

static CScriptArray* Split(char separator, const std::string* str)
{
    std::vector<std::string> result = split(*str, separator);
    return vectorToArray<std::string>(result, "array<string>");
}

static void registerStringUtils(asIScriptEngine* engine)
{
    // Register most of StringUtils as string's const methods, or objects' toString() const methods for convenience
    engine->RegisterObjectMethod("string", "array<string>@ split(uint8) const", asFUNCTION(Split), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("string", "string replace(uint8, uint8) const", asFUNCTIONPR(replace, (const std::string&, char, char), std::string), asCALL_CDECL_OBJFIRST);
    engine->RegisterObjectMethod("string", "string replace(const string& in, const string& in) const", asFUNCTIONPR(replace, (const std::string&, const std::string&, const std::string&), std::string), asCALL_CDECL_OBJFIRST);
    engine->RegisterObjectMethod("string", "string toUpper() const", asFUNCTION(toUpper), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("string", "string toLower() const", asFUNCTION(toLower), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("string", "bool toBool() const", asFUNCTION(toBool), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("string", "float toFloat() const", asFUNCTION(toFloat), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("string", "int toInt() const", asFUNCTION(toInt), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("string", "uint toUInt() const", asFUNCTION(toUInt), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("string", "Color toColor() const", asFUNCTION(toColor), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("string", "IntRect toIntRect() const", asFUNCTION(toIntRect), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("string", "IntVector2 toIntVector2() const", asFUNCTION(toIntVector2), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("string", "Quaternion toQuaternion() const", asFUNCTION(toQuaternion), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("string", "Vector2 toVector2() const", asFUNCTION(toVector2), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("string", "Vector3 toVector3() const", asFUNCTION(toVector3), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("string", "Vector4 toVector4() const", asFUNCTION(toVector4), asCALL_CDECL_OBJLAST);
    engine->RegisterGlobalFunction("string toString(bool)", asFUNCTIONPR(toString, (bool), std::string), asCALL_CDECL);
    engine->RegisterGlobalFunction("string toString(float)", asFUNCTIONPR(toString, (float), std::string), asCALL_CDECL);
    engine->RegisterGlobalFunction("string toString(int)", asFUNCTIONPR(toString, (int), std::string), asCALL_CDECL);
    engine->RegisterGlobalFunction("string toString(uint)", asFUNCTIONPR(toString, (unsigned), std::string), asCALL_CDECL);
    engine->RegisterGlobalFunction("string toStringHex(int)", asFUNCTION(toStringHex), asCALL_CDECL);
}

static File* ConstructFile(const std::string& fileName, FileMode mode)
{
    TRY_CONSTRUCT(new File(fileName, mode));
}

static void ConstructVectorBuffer(VectorBuffer* ptr)
{
    new(ptr) VectorBuffer();
}

static void ConstructVectorBufferCopy(const VectorBuffer& buffer, VectorBuffer* ptr)
{
    new(ptr) VectorBuffer(buffer);
}

static void ConstructVectorBufferFromStream(Deserializer* src, unsigned size, VectorBuffer* ptr)
{
    if (!src)
        SAFE_EXCEPTION("Null VectorBuffer source");
    
    new(ptr) VectorBuffer(*src, size);
}

static void DestructVectorBuffer(VectorBuffer* ptr)
{
    ptr->~VectorBuffer();
}

static void VectorBufferSetData(Deserializer* src, unsigned size, VectorBuffer* ptr)
{
    if (!src)
        SAFE_EXCEPTION("Null VectorBuffer source");
    
    ptr->setData(*src, size);
}

static unsigned char* VectorBufferAt(unsigned index, VectorBuffer* ptr)
{
    if (index >= ptr->getSize())
        SAFE_EXCEPTION_RET("Index out of bounds", 0);
    
    return ptr->getModifiableData() + index;
}

static void ConstructVariantBuffer(const VectorBuffer& buffer, Variant* ptr)
{
    new(ptr) Variant(buffer.getBuffer());
}

static VectorBuffer VariantGetBuffer(Variant* ptr)
{
    VectorBuffer ret(ptr->getBuffer());
    return ret;
}

static bool VariantEqualsBuffer(const VectorBuffer& buffer, Variant* ptr)
{
    return (*ptr) == buffer.getBuffer();
}

static CScriptArray* ScanDirectory(const std::string& pathName, const std::string& filter, unsigned flags, bool recursive)
{
    std::vector<std::string> result;
    scanDirectory(result, pathName, filter, flags, recursive);
    return vectorToArray<std::string>(result, "array<string>");
}

static int SystemRun(const std::string& fileName, CScriptArray* srcArguments)
{
    if (!srcArguments)
        return -1;
    
    unsigned numArguments = srcArguments->GetSize();
    std::vector<std::string> destArguments(numArguments);
    for (unsigned i = 0; i < numArguments; ++i)
        destArguments[i] = *(static_cast<std::string*>(srcArguments->At(i)));
    
    return systemRun(fileName, destArguments);
}

static void registerSerialization(asIScriptEngine* engine)
{
    engine->RegisterObjectType("Serializer", 0, asOBJ_REF);
    engine->RegisterObjectBehaviour("Serializer", asBEHAVE_ADDREF, "void f()", asFUNCTION(FakeAddRef), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("Serializer", asBEHAVE_RELEASE, "void f()", asFUNCTION(FakeReleaseRef), asCALL_CDECL_OBJLAST);
    registerSerializer<Serializer>(engine, "Serializer");
    
    engine->RegisterObjectType("Deserializer", 0, asOBJ_REF);
    engine->RegisterObjectBehaviour("Deserializer", asBEHAVE_ADDREF, "void f()", asFUNCTION(FakeAddRef), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("Deserializer", asBEHAVE_RELEASE, "void f()", asFUNCTION(FakeReleaseRef), asCALL_CDECL_OBJLAST);
    registerDeserializer<Deserializer>(engine, "Deserializer");
    
    engine->RegisterEnum("FileMode");
    engine->RegisterEnumValue("FileMode", "FILE_READ", FILE_READ);
    engine->RegisterEnumValue("FileMode", "FILE_WRITE", FILE_WRITE);
    engine->RegisterEnumValue("FileMode", "FILE_READWRITE", FILE_READWRITE);
    
    engine->RegisterGlobalProperty("const uint SCAN_FILES", (void*)&SCAN_FILES);
    engine->RegisterGlobalProperty("const uint SCAN_DIRECTORIES", (void*)&SCAN_DIRECTORIES);
    engine->RegisterGlobalProperty("const uint SCAN_HIDDEN", (void*)&SCAN_HIDDEN);
    
    engine->RegisterObjectType("File", 0, asOBJ_REF);
    engine->RegisterObjectBehaviour("File", asBEHAVE_FACTORY, "File@+ f(string& in, FileMode)", asFUNCTION(ConstructFile), asCALL_CDECL);
    engine->RegisterObjectBehaviour("File", asBEHAVE_ADDREF, "void f()", asMETHOD(File, addRef), asCALL_THISCALL);
    engine->RegisterObjectBehaviour("File", asBEHAVE_RELEASE, "void f()", asMETHOD(File, releaseRef), asCALL_THISCALL);
    registerSerializer<File>(engine, "File");
    registerDeserializer<File>(engine, "File");
    engine->RegisterObjectMethod("File", "void close()", asMETHOD(File, close), asCALL_THISCALL);
    engine->RegisterObjectMethod("File", "FileMode getMode() const", asMETHOD(File, getMode), asCALL_THISCALL);
    engine->RegisterObjectMethod("File", "uint getChecksum()", asMETHOD(File, getChecksum), asCALL_THISCALL);
    
    engine->RegisterGlobalFunction("bool fileExists(const string& in)", asFUNCTION(fileExists), asCALL_CDECL);
    engine->RegisterGlobalFunction("bool directoryExists(const string& in)", asFUNCTION(directoryExists), asCALL_CDECL);
    engine->RegisterGlobalFunction("array<string>@ scanDirectory(const string& in, const string& in, uint, bool)", asFUNCTION(ScanDirectory), asCALL_CDECL);
    engine->RegisterGlobalFunction("string getCurrentDirectory()", asFUNCTION(getCurrentDirectory), asCALL_CDECL);
    engine->RegisterGlobalFunction("void setCurrentDirectory(const string& in)", asFUNCTION(setCurrentDirectory), asCALL_CDECL);
    engine->RegisterGlobalFunction("bool createDirectory(const string& in)", asFUNCTION(createDirectory), asCALL_CDECL);
    engine->RegisterGlobalFunction("int systemCommand(const string& in)", asFUNCTION(systemCommand), asCALL_CDECL);
    engine->RegisterGlobalFunction("int systemRun(const string& in, array<string>@+)", asFUNCTION(SystemRun), asCALL_CDECL);
    engine->RegisterGlobalFunction("bool systemOpenFile(const string& in, const string& in)", asFUNCTION(systemOpenFile), asCALL_CDECL);
    engine->RegisterGlobalFunction("bool copyFile(const string& in, const string& in)", asFUNCTION(copyFile), asCALL_CDECL);
    engine->RegisterGlobalFunction("bool renameFile(const string& in, const string& in)", asFUNCTION(renameFile), asCALL_CDECL);
    engine->RegisterGlobalFunction("bool deleteFile(const string& in)", asFUNCTION(deleteFile), asCALL_CDECL);
    engine->RegisterGlobalFunction("string getPath(const string& in)", asFUNCTION(getPath), asCALL_CDECL);
    engine->RegisterGlobalFunction("string getFileName(const string& in)", asFUNCTION(getFileName), asCALL_CDECL);
    engine->RegisterGlobalFunction("string getExtension(const string& in)", asFUNCTION(getExtension), asCALL_CDECL);
    engine->RegisterGlobalFunction("string getFileNameAndExtension(const string& in)", asFUNCTION(getFileNameAndExtension), asCALL_CDECL);
    engine->RegisterGlobalFunction("string fixPath(const string& in)", asFUNCTION(fixPath), asCALL_CDECL);
    engine->RegisterGlobalFunction("string unfixPath(const string& in)", asFUNCTION(unfixPath), asCALL_CDECL);
    engine->RegisterGlobalFunction("string getParentPath(const string& in)", asFUNCTION(getParentPath), asCALL_CDECL);
    engine->RegisterGlobalFunction("string getAbsoluteFileName(const string& in)", asFUNCTION(getAbsoluteFileName), asCALL_CDECL);
    
    engine->RegisterObjectType("VectorBuffer", sizeof(VectorBuffer), asOBJ_VALUE | asOBJ_APP_CLASS_CDA);
    engine->RegisterObjectBehaviour("VectorBuffer", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(ConstructVectorBuffer), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("VectorBuffer", asBEHAVE_CONSTRUCT, "void f(const VectorBuffer& in)", asFUNCTION(ConstructVectorBufferCopy), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("VectorBuffer", asBEHAVE_CONSTRUCT, "void f(Deserializer@+, uint)", asFUNCTION(ConstructVectorBufferFromStream), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("VectorBuffer", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(DestructVectorBuffer), asCALL_CDECL_OBJLAST);
    registerSerializer<VectorBuffer>(engine, "VectorBuffer");
    registerDeserializer<VectorBuffer>(engine, "VectorBuffer");
    engine->RegisterObjectMethod("VectorBuffer", "VectorBuffer &opAssign(const VectorBuffer& in)", asMETHOD(VectorBuffer, operator =), asCALL_THISCALL);
    engine->RegisterObjectMethod("VectorBuffer", "void setData(Deserializer@+, uint)", asFUNCTION(VectorBufferSetData), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("VectorBuffer", "void clear()", asMETHOD(VectorBuffer, clear), asCALL_THISCALL);
    engine->RegisterObjectMethod("VectorBuffer", "void resize(uint)", asMETHOD(VectorBuffer, resize), asCALL_THISCALL);
    engine->RegisterObjectMethod("VectorBuffer", "uint8 &opIndex(uint)", asFUNCTION(VectorBufferAt), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("VectorBuffer", "const uint8 &opIndex(uint) const", asFUNCTION(VectorBufferAt), asCALL_CDECL_OBJLAST);
    
    // Register VectorBuffer conversions to Variant
    engine->RegisterObjectBehaviour("Variant", asBEHAVE_CONSTRUCT, "void f(const VectorBuffer& in)", asFUNCTION(ConstructVariantBuffer), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("Variant", "VectorBuffer getBuffer() const", asFUNCTION(VariantGetBuffer), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("Variant", "bool opEquals(const VectorBuffer& in) const", asFUNCTION(VariantEqualsBuffer), asCALL_CDECL_OBJLAST);
}

static PackageFile* ConstructPackageFile(const std::string& fileName)
{
    TRY_CONSTRUCT(new PackageFile(fileName));
}

static void registerPackageFile(asIScriptEngine* engine)
{
    engine->RegisterObjectType("PackageFile", 0, asOBJ_REF);
    engine->RegisterObjectBehaviour("PackageFile", asBEHAVE_FACTORY, "PackageFile@+ f(const string& in)", asFUNCTION(ConstructPackageFile), asCALL_CDECL);
    engine->RegisterObjectBehaviour("PackageFile", asBEHAVE_ADDREF, "void f()", asMETHOD(PackageFile, addRef), asCALL_THISCALL);
    engine->RegisterObjectBehaviour("PackageFile", asBEHAVE_RELEASE, "void f()", asMETHOD(PackageFile, releaseRef), asCALL_THISCALL);
    engine->RegisterObjectMethod("PackageFile", "bool exists(string& in) const", asMETHOD(PackageFile, exists), asCALL_THISCALL);
    engine->RegisterObjectMethod("PackageFile", "const string& getName() const", asMETHOD(PackageFile, getName), asCALL_THISCALL);
    engine->RegisterObjectMethod("PackageFile", "uint getNumFiles() const", asMETHOD(PackageFile, getNumFiles), asCALL_THISCALL);
    engine->RegisterObjectMethod("PackageFile", "uint getTotalSize() const", asMETHOD(PackageFile, getTotalSize), asCALL_THISCALL);
    engine->RegisterObjectMethod("PackageFile", "uint getChecksum() const", asMETHOD(PackageFile, getChecksum), asCALL_THISCALL);
}

static void ConstructTimer(Timer* ptr)
{
    new(ptr) Timer();
}

static void registerTimer(asIScriptEngine* engine)
{
    engine->RegisterObjectType("Timer", sizeof(Timer), asOBJ_VALUE | asOBJ_POD | asOBJ_APP_CLASS_C);
    engine->RegisterObjectBehaviour("Timer", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(ConstructTimer), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("Timer", "uint getMSec(bool)", asMETHOD(Timer, getMSec), asCALL_THISCALL);
    engine->RegisterObjectMethod("Timer", "void reset()", asMETHOD(Timer, reset), asCALL_THISCALL);
}

static CScriptArray* GetArguments()
{
    return vectorToArray<std::string>(getArguments(), "array<string>");
}

static void registerProcessUtils(asIScriptEngine* engine)
{
    engine->RegisterGlobalFunction("array<string>@ getArguments()", asFUNCTION(GetArguments), asCALL_CDECL);
    engine->RegisterGlobalFunction("void errorDialog(const string& in, const string& in)", asFUNCTION(errorDialog), asCALL_CDECL);
    engine->RegisterGlobalFunction("string getExecutableDirectory()", asFUNCTION(getExecutableDirectory), asCALL_CDECL);
    engine->RegisterGlobalFunction("string getUserDocumentsDirectory()", asFUNCTION(getUserDocumentsDirectory), asCALL_CDECL);
    engine->RegisterGlobalFunction("uint getNumLogicalProcessors()", asFUNCTION(getNumLogicalProcessors), asCALL_CDECL);
}

static void SendEvent(const std::string& eventType, VariantMap& parameters)
{
    ScriptEventListener* sender = getScriptContextEventListener();
    if (sender)
        sender->sendEvent(StringHash(eventType), parameters);
}

static void SendTargetedEvent(EventListener* receiver, const std::string& eventType, VariantMap& parameters)
{
    ScriptEventListener* sender = getScriptContextEventListener();
    if (sender)
        sender->sendEvent(receiver, StringHash(eventType), parameters);
}

static void SubscribeToEvent(const std::string& eventType, const std::string& handlerName)
{
    ScriptEventListener* listener = getScriptContextEventListener();
    if (listener)
        listener->addEventHandler(StringHash(eventType), handlerName);
}

static void SubscribeToSenderEvent(EventListener* sender, const std::string& eventType, const std::string& handlerName)
{
    ScriptEventListener* listener = getScriptContextEventListener();
    if (listener)
        listener->addEventHandler(sender, StringHash(eventType), handlerName);
}

static void UnsubscribeFromEvent(const std::string& eventType)
{
    ScriptEventListener* listener = getScriptContextEventListener();
    if (listener)
        listener->unsubscribeFromEvent(StringHash(eventType));
}

static void UnsubscribeFromSenderEvent(EventListener* sender, const std::string& eventType)
{
    ScriptEventListener* listener = getScriptContextEventListener();
    if (listener)
        listener->unsubscribeFromEvent(sender, StringHash(eventType));
}

static void UnsubscribeFromSenderEvents(EventListener* sender)
{
    ScriptEventListener* listener = getScriptContextEventListener();
    if (listener)
        listener->unsubscribeFromEvents(sender);
}

static void UnsubscribeFromAllEvents()
{
    ScriptEventListener* listener = getScriptContextEventListener();
    if (listener)
        listener->removeAllEventHandlers();
}

void registerEventListener(asIScriptEngine* engine)
{
    engine->RegisterObjectType("EventListener", 0, asOBJ_REF);
    engine->RegisterObjectBehaviour("EventListener", asBEHAVE_ADDREF, "void f()", asFUNCTION(optionalAddRef<EventListener>), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("EventListener", asBEHAVE_RELEASE, "void f()", asFUNCTION(optionalReleaseRef<EventListener>), asCALL_CDECL_OBJLAST);
    
    engine->RegisterGlobalFunction("void sendEvent(const string& in, VariantMap&)", asFUNCTION(SendEvent), asCALL_CDECL);
    engine->RegisterGlobalFunction("void sendEvent(EventListener@+, const string& in, VariantMap&)", asFUNCTION(SendTargetedEvent), asCALL_CDECL);
    engine->RegisterGlobalFunction("void subscribeToEvent(const string& in, const string& in)", asFUNCTION(SubscribeToEvent), asCALL_CDECL);
    engine->RegisterGlobalFunction("void subscribeToEvent(EventListener@+, const string& in, const string& in)", asFUNCTION(SubscribeToSenderEvent), asCALL_CDECL);
    engine->RegisterGlobalFunction("void unsubscribeFromEvent(const string& in)", asFUNCTION(UnsubscribeFromEvent), asCALL_CDECL);
    engine->RegisterGlobalFunction("void unsubscribeFromEvent(EventListener@+, const string& in)", asFUNCTION(UnsubscribeFromSenderEvent), asCALL_CDECL);
    engine->RegisterGlobalFunction("void unsubscribeFromEvents(EventListener@+)", asFUNCTION(UnsubscribeFromSenderEvents), asCALL_CDECL);
    engine->RegisterGlobalFunction("void unsubscribeFromAllEvents()", asFUNCTION(UnsubscribeFromAllEvents), asCALL_CDECL);
    
    engine->RegisterGlobalFunction("EventListener@+ getEventSender()", asFUNCTION(getEventSender), asCALL_CDECL);
}

void registerCommonLibrary(asIScriptEngine* engine)
{
    registerColor(engine);
    registerLog(engine);
    registerStringHash(engine);
    registerVariant(engine);
    registerStringUtils(engine);
    registerSerialization(engine);
    registerPackageFile(engine);
    registerTimer(engine);
    registerProcessUtils(engine);
    registerEventListener(engine);
}
