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
#include "Color.h"
#include "Frustum.h"

#include <angelscript.h>

static float Sin(float angle)
{
    return sinf(angle * M_DEGTORAD);
}

static float Cos(float angle)
{
    return cosf(angle * M_DEGTORAD);
}

static float Tan(float angle)
{
    return tanf(angle * M_DEGTORAD);
}

static float Asin(float x)
{
    return M_RADTODEG * asinf(Clamp(x, -1.0f, 1.0f));
}

static float Acos(float x)
{
    return M_RADTODEG * acosf(Clamp(x, -1.0f, 1.0f));
}

static float Atan(float x)
{
    return M_RADTODEG * atanf(x);
}

static float Atan2(float y, float x)
{
    return M_RADTODEG * atan2f(y, x);
}

static void RegisterMathFunctions(asIScriptEngine* engine)
{
    engine->RegisterGlobalProperty("const float M_INFINITY", (void*)&M_INFINITY);
    engine->RegisterGlobalProperty("const float M_EPSILON", (void*)&M_EPSILON);
    
    engine->RegisterGlobalFunction("bool Equals(float, float)", asFUNCTION(Equals), asCALL_CDECL);
    engine->RegisterGlobalFunction("float Sin(float)", asFUNCTION(Sin), asCALL_CDECL);
    engine->RegisterGlobalFunction("float Cos(float)", asFUNCTION(Cos), asCALL_CDECL);
    engine->RegisterGlobalFunction("float Tan(float)", asFUNCTION(Tan), asCALL_CDECL);
    engine->RegisterGlobalFunction("float Asin(float)", asFUNCTION(Asin), asCALL_CDECL);
    engine->RegisterGlobalFunction("float Acos(float)", asFUNCTION(Acos), asCALL_CDECL);
    engine->RegisterGlobalFunction("float Atan(float)", asFUNCTION(Atan), asCALL_CDECL);
    engine->RegisterGlobalFunction("float Atan2(float, float)", asFUNCTION(Atan2), asCALL_CDECL);
    engine->RegisterGlobalFunction("float Abs(float)", asFUNCTION(fabsf), asCALL_CDECL);
    engine->RegisterGlobalFunction("float Sqrt(float)", asFUNCTION(sqrtf), asCALL_CDECL);
    engine->RegisterGlobalFunction("float Pow(float)", asFUNCTION(powf), asCALL_CDECL);
    engine->RegisterGlobalFunction("float Random()", asFUNCTIONPR(Random, (), float), asCALL_CDECL);
    engine->RegisterGlobalFunction("float Random(float)", asFUNCTIONPR(Random, (float), float), asCALL_CDECL);
    engine->RegisterGlobalFunction("int RandomInt()", asFUNCTION(rand), asCALL_CDECL);
    engine->RegisterGlobalFunction("int RandomInt(int)", asFUNCTIONPR(Random, (int), int), asCALL_CDECL);
    engine->RegisterGlobalFunction("void SetRandomSeed(int)", asFUNCTION(srand), asCALL_CDECL);
    engine->RegisterGlobalFunction("float Min(float, float)", asFUNCTIONPR(Min, (float, float), float), asCALL_CDECL);
    engine->RegisterGlobalFunction("float Max(float, float)", asFUNCTIONPR(Max, (float, float), float), asCALL_CDECL);
    engine->RegisterGlobalFunction("float Clamp(float, float, float)", asFUNCTIONPR(Clamp, (float, float, float), float), asCALL_CDECL);
    engine->RegisterGlobalFunction("float Lerp(float, float, float)", asFUNCTIONPR(Lerp, (float, float, float), float), asCALL_CDECL);
    engine->RegisterGlobalFunction("float Mod(float, float)", asFUNCTION(fmodf), asCALL_CDECL);
    engine->RegisterGlobalFunction("float Floor(float)", asFUNCTION(floorf), asCALL_CDECL);
    engine->RegisterGlobalFunction("float Ceil(float)", asFUNCTION(ceilf), asCALL_CDECL);
}

static void ConstructIntRect(IntRect* ptr)
{
    // Init to zero because performance is not critical
    new(ptr) IntRect(IntRect::ZERO);
}

static void ConstructIntRectCopy(const IntRect& rect, IntRect* ptr)
{
    new(ptr) IntRect(rect);
}

static void ConstructIntRectInit(int left, int top, int right, int bottom, IntRect* ptr)
{
    new(ptr) IntRect(left, top, right, bottom);
}

static void RegisterIntRect(asIScriptEngine* engine)
{
    engine->RegisterObjectType("IntRect", sizeof(IntRect), asOBJ_VALUE | asOBJ_POD | asOBJ_APP_CLASS_CAK);
    engine->RegisterObjectBehaviour("IntRect", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(ConstructIntRect), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("IntRect", asBEHAVE_CONSTRUCT, "void f(const IntRect&in)", asFUNCTION(ConstructIntRectCopy), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("IntRect", asBEHAVE_CONSTRUCT, "void f(int, int, int, int)", asFUNCTION(ConstructIntRectInit), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("IntRect", "IntRect& opAssign(const IntRect&in)", asMETHOD(IntRect, operator =), asCALL_THISCALL);
    engine->RegisterObjectMethod("IntRect", "bool opEquals(const IntRect&in) const", asMETHOD(IntRect, operator ==), asCALL_THISCALL);
    engine->RegisterObjectProperty("IntRect", "int left", offsetof(IntRect, left_));
    engine->RegisterObjectProperty("IntRect", "int top", offsetof(IntRect, top_));
    engine->RegisterObjectProperty("IntRect", "int right", offsetof(IntRect, right_));
    engine->RegisterObjectProperty("IntRect", "int bottom", offsetof(IntRect, bottom_));
}

static void ConstructIntVector2(IntVector2* ptr)
{
    // Init to zero because performance is not critical
    new(ptr) IntVector2(IntVector2::ZERO);
}

static void ConstructIntVector2Copy(const IntVector2& vector, IntVector2* ptr)
{
    new(ptr) IntVector2(vector);
}

static void ConstructIntVector2Init(int x, int y, IntVector2* ptr)
{
    new(ptr) IntVector2(x, y);
}

static void RegisterIntVector2(asIScriptEngine* engine)
{
    engine->RegisterObjectType("IntVector2", sizeof(IntVector2), asOBJ_VALUE | asOBJ_POD | asOBJ_APP_CLASS_CAK);
    engine->RegisterObjectBehaviour("IntVector2", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(ConstructIntVector2), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("IntVector2", asBEHAVE_CONSTRUCT, "void f(const IntVector2&in)", asFUNCTION(ConstructIntVector2Copy), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("IntVector2", asBEHAVE_CONSTRUCT, "void f(int, int)", asFUNCTION(ConstructIntVector2Init), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("IntVector2", "IntVector2& opAssign(const IntVector2&in)", asMETHOD(IntVector2, operator =), asCALL_THISCALL);
    engine->RegisterObjectMethod("IntVector2", "IntVector2& opAddAssign(const IntVector2&in)", asMETHOD(IntVector2, operator +=), asCALL_THISCALL);
    engine->RegisterObjectMethod("IntVector2", "IntVector2& opSubAssign(const IntVector2&in)", asMETHOD(IntVector2, operator -=), asCALL_THISCALL);
    engine->RegisterObjectMethod("IntVector2", "IntVector2& opMulAssign(int)", asMETHODPR(IntVector2, operator *=, (int), IntVector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("IntVector2", "IntVector2& opDivAssign(int)", asMETHODPR(IntVector2, operator /=, (int), IntVector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("IntVector2", "bool opEquals(const IntVector2&in) const", asMETHOD(IntVector2, operator ==), asCALL_THISCALL);
    engine->RegisterObjectMethod("IntVector2", "IntVector2 opNeg() const", asMETHODPR(IntVector2, operator -, () const, IntVector2), asCALL_THISCALL);
    engine->RegisterObjectMethod("IntVector2", "IntVector2 opAdd(const IntVector2&in) const", asMETHOD(IntVector2, operator +), asCALL_THISCALL);
    engine->RegisterObjectMethod("IntVector2", "IntVector2 opSub(const IntVector2&in) const", asMETHODPR(IntVector2, operator -, (const IntVector2&) const, IntVector2), asCALL_THISCALL);
    engine->RegisterObjectMethod("IntVector2", "IntVector2 opMul(int) const", asMETHODPR(IntVector2, operator *, (int) const, IntVector2), asCALL_THISCALL);
    engine->RegisterObjectMethod("IntVector2", "IntVector2 opDiv(int) const", asMETHODPR(IntVector2, operator /, (int) const, IntVector2), asCALL_THISCALL);
    engine->RegisterObjectMethod("IntVector2", "String ToString() const", asMETHOD(IntVector2, ToString), asCALL_THISCALL);
    engine->RegisterObjectProperty("IntVector2", "int x", offsetof(IntVector2, x_));
    engine->RegisterObjectProperty("IntVector2", "int y", offsetof(IntVector2, y_));
}

static void ConstructVector2(Vector2* ptr)
{
    // Init to zero because performance is not critical
    new(ptr) Vector2(Vector2::ZERO);
}

static void ConstructVector2Copy(const Vector2& vector, Vector2* ptr)
{
    new(ptr) Vector2(vector);
}

static void ConstructVector2Init(float x, float y, Vector2* ptr)
{
    new(ptr) Vector2(x, y);
}

static void RegisterVector2(asIScriptEngine* engine)
{
    engine->RegisterObjectType("Vector2", sizeof(Vector2), asOBJ_VALUE | asOBJ_POD | asOBJ_APP_CLASS_CAK);
    engine->RegisterObjectBehaviour("Vector2", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(ConstructVector2), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("Vector2", asBEHAVE_CONSTRUCT, "void f(const Vector2&in)", asFUNCTION(ConstructVector2Copy), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("Vector2", asBEHAVE_CONSTRUCT, "void f(float, float)", asFUNCTION(ConstructVector2Init), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("Vector2", "Vector2& opAssign(const Vector2&in)", asMETHOD(Vector2, operator =), asCALL_THISCALL);
    engine->RegisterObjectMethod("Vector2", "Vector2& opAddAssign(const Vector2&in)", asMETHOD(Vector2, operator +=), asCALL_THISCALL);
    engine->RegisterObjectMethod("Vector2", "Vector2& opSubAssign(const Vector2&in)", asMETHOD(Vector2, operator -=), asCALL_THISCALL);
    engine->RegisterObjectMethod("Vector2", "Vector2& opMulAssign(const Vector2&in)", asMETHODPR(Vector2, operator *=, (const Vector2&), Vector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Vector2", "Vector2& opMulAssign(float)", asMETHODPR(Vector2, operator *=, (float), Vector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Vector2", "Vector2& opDivAssign(const Vector2&in)", asMETHODPR(Vector2, operator /=, (const Vector2&), Vector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Vector2", "Vector2& opDivAssign(float)", asMETHODPR(Vector2, operator /=, (float), Vector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Vector2", "bool opEquals(const Vector2&in) const", asMETHOD(Vector2, operator ==), asCALL_THISCALL);
    engine->RegisterObjectMethod("Vector2", "Vector2 opNeg() const", asMETHODPR(Vector2, operator -, () const, Vector2), asCALL_THISCALL);
    engine->RegisterObjectMethod("Vector2", "Vector2 opAdd(const Vector2&in) const", asMETHOD(Vector2, operator +), asCALL_THISCALL);
    engine->RegisterObjectMethod("Vector2", "Vector2 opSub(const Vector2&in) const", asMETHODPR(Vector2, operator -, (const Vector2&) const, Vector2), asCALL_THISCALL);
    engine->RegisterObjectMethod("Vector2", "Vector2 opMul(const Vector2&in) const", asMETHODPR(Vector2, operator *, (const Vector2&) const, Vector2), asCALL_THISCALL);
    engine->RegisterObjectMethod("Vector2", "Vector2 opMul(float) const", asMETHODPR(Vector2, operator *, (float) const, Vector2), asCALL_THISCALL);
    engine->RegisterObjectMethod("Vector2", "Vector2 opDiv(const Vector2&in) const", asMETHODPR(Vector2, operator /, (const Vector2&) const, Vector2), asCALL_THISCALL);
    engine->RegisterObjectMethod("Vector2", "Vector2 opDiv(float) const", asMETHODPR(Vector2, operator /, (float) const, Vector2), asCALL_THISCALL);
    engine->RegisterObjectMethod("Vector2", "float Normalize()", asMETHOD(Vector2, Normalize), asCALL_THISCALL);
    engine->RegisterObjectMethod("Vector2", "float DotProduct(const Vector2&in) const", asMETHOD(Vector2, DotProduct), asCALL_THISCALL);
    engine->RegisterObjectMethod("Vector2", "float AbsDotProduct(const Vector2&in) const", asMETHOD(Vector2, AbsDotProduct), asCALL_THISCALL);
    engine->RegisterObjectMethod("Vector2", "Vector2 Lerp(const Vector2&in, float) const", asMETHOD(Vector2, Lerp), asCALL_THISCALL);
    engine->RegisterObjectMethod("Vector2", "Vector2 Normalized() const", asMETHOD(Vector2, Normalized), asCALL_THISCALL);
    engine->RegisterObjectMethod("Vector2", "String ToString() const", asMETHOD(Vector2, ToString), asCALL_THISCALL);
    engine->RegisterObjectMethod("Vector2", "float get_length() const", asMETHOD(Vector2, Length), asCALL_THISCALL);
    engine->RegisterObjectMethod("Vector2", "float get_lengthSquared() const", asMETHOD(Vector2, LengthSquared), asCALL_THISCALL);
    engine->RegisterObjectProperty("Vector2", "float x", offsetof(Vector2, x_));
    engine->RegisterObjectProperty("Vector2", "float y", offsetof(Vector2, y_));
}

static void ConstructVector3(Vector3* ptr)
{
    // Init to zero because performance is not critical
    new(ptr) Vector3(Vector3::ZERO);
}

static void ConstructVector3Copy(const Vector3& vector, Vector3* ptr)
{
    new(ptr) Vector3(vector);
}

static void ConstructVector3Init(float x, float y, float z, Vector3* ptr)
{
    new(ptr) Vector3(x, y, z);
}

static void RegisterVector3(asIScriptEngine* engine)
{
    engine->RegisterObjectType("Vector3", sizeof(Vector3), asOBJ_VALUE | asOBJ_POD | asOBJ_APP_CLASS_CAK);
    engine->RegisterObjectBehaviour("Vector3", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(ConstructVector3), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("Vector3", asBEHAVE_CONSTRUCT, "void f(const Vector3&in)", asFUNCTION(ConstructVector3Copy), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("Vector3", asBEHAVE_CONSTRUCT, "void f(float, float, float)", asFUNCTION(ConstructVector3Init), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("Vector3", "Vector3& opAssign(const Vector3&in)", asMETHOD(Vector3, operator =), asCALL_THISCALL);
    engine->RegisterObjectMethod("Vector3", "Vector3& opAddAssign(const Vector3&in)", asMETHOD(Vector3, operator +=), asCALL_THISCALL);
    engine->RegisterObjectMethod("Vector3", "Vector3& opSubAssign(const Vector3&in)", asMETHOD(Vector3, operator -=), asCALL_THISCALL);
    engine->RegisterObjectMethod("Vector3", "Vector3& opMulAssign(const Vector3&in)", asMETHODPR(Vector3, operator *=, (const Vector3&), Vector3&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Vector3", "Vector3& opMulAssign(float)", asMETHODPR(Vector3, operator *=, (float), Vector3&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Vector3", "Vector3& opDivAssign(const Vector3&in)", asMETHODPR(Vector3, operator /=, (const Vector3&), Vector3&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Vector3", "Vector3& opDivAssign(float)", asMETHODPR(Vector3, operator /=, (float), Vector3&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Vector3", "bool opEquals(const Vector3&in) const", asMETHOD(Vector3, operator ==), asCALL_THISCALL);
    engine->RegisterObjectMethod("Vector3", "Vector3 opNeg() const", asMETHODPR(Vector3, operator -, () const, Vector3), asCALL_THISCALL);
    engine->RegisterObjectMethod("Vector3", "Vector3 opAdd(const Vector3&in) const", asMETHOD(Vector3, operator +), asCALL_THISCALL);
    engine->RegisterObjectMethod("Vector3", "Vector3 opSub(const Vector3&in) const", asMETHODPR(Vector3, operator -, (const Vector3&) const, Vector3), asCALL_THISCALL);
    engine->RegisterObjectMethod("Vector3", "Vector3 opMul(const Vector3&in) const", asMETHODPR(Vector3, operator *, (const Vector3&) const, Vector3), asCALL_THISCALL);
    engine->RegisterObjectMethod("Vector3", "Vector3 opMul(float) const", asMETHODPR(Vector3, operator *, (float) const, Vector3), asCALL_THISCALL);
    engine->RegisterObjectMethod("Vector3", "Vector3 opDiv(const Vector3&in) const", asMETHODPR(Vector3, operator /, (const Vector3&) const, Vector3), asCALL_THISCALL);
    engine->RegisterObjectMethod("Vector3", "Vector3 opDiv(float) const", asMETHODPR(Vector3, operator /, (float) const, Vector3), asCALL_THISCALL);
    engine->RegisterObjectMethod("Vector3", "float Normalize()", asMETHOD(Vector3, Normalize), asCALL_THISCALL);
    engine->RegisterObjectMethod("Vector3", "float DotProduct(const Vector3&in) const", asMETHOD(Vector3, DotProduct), asCALL_THISCALL);
    engine->RegisterObjectMethod("Vector3", "float AbsDotProduct(const Vector3&in) const", asMETHOD(Vector3, AbsDotProduct), asCALL_THISCALL);
    engine->RegisterObjectMethod("Vector3", "Vector3 CrossProduct(const Vector3&in) const", asMETHOD(Vector3, CrossProduct), asCALL_THISCALL);
    engine->RegisterObjectMethod("Vector3", "Vector3 Lerp(const Vector3&in, float) const", asMETHOD(Vector3, Lerp), asCALL_THISCALL);
    engine->RegisterObjectMethod("Vector3", "Vector3 Normalized() const", asMETHOD(Vector3, Normalized), asCALL_THISCALL);
    engine->RegisterObjectMethod("Vector3", "String ToString() const", asMETHOD(Vector3, ToString), asCALL_THISCALL);
    engine->RegisterObjectMethod("Vector3", "float get_length() const", asMETHOD(Vector3, Length), asCALL_THISCALL);
    engine->RegisterObjectMethod("Vector3", "float get_lengthSquared() const", asMETHOD(Vector3, LengthSquared), asCALL_THISCALL);
    engine->RegisterObjectProperty("Vector3", "float x", offsetof(Vector3, x_));
    engine->RegisterObjectProperty("Vector3", "float y", offsetof(Vector3, y_));
    engine->RegisterObjectProperty("Vector3", "float z", offsetof(Vector3, z_));
}

static void ConstructVector4(Vector4* ptr)
{
    // Init to zero because performance is not critical
    new(ptr) Vector4(Vector4::ZERO);
}

static void ConstructVector4Copy(const Vector4& vector, Vector4* ptr)
{
    new(ptr) Vector4(vector);
}

static void ConstructVector4Init(float x, float y, float z, float w, Vector4* ptr)
{
    new(ptr) Vector4(x, y, z, w);
}

static void RegisterVector4(asIScriptEngine* engine)
{
    engine->RegisterObjectType("Vector4", sizeof(Vector4), asOBJ_VALUE | asOBJ_POD | asOBJ_APP_CLASS_CAK);
    engine->RegisterObjectBehaviour("Vector4", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(ConstructVector4), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("Vector4", asBEHAVE_CONSTRUCT, "void f(const Vector4&in)", asFUNCTION(ConstructVector4Copy), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("Vector4", asBEHAVE_CONSTRUCT, "void f(float, float, float)", asFUNCTION(ConstructVector4Init), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("Vector4", "Vector4& opAssign(const Vector4&in)", asMETHOD(Vector4, operator =), asCALL_THISCALL);
    engine->RegisterObjectMethod("Vector4", "Vector4& opAddAssign(const Vector4&in)", asMETHOD(Vector4, operator +=), asCALL_THISCALL);
    engine->RegisterObjectMethod("Vector4", "Vector4& opSubAssign(const Vector4&in)", asMETHOD(Vector4, operator -=), asCALL_THISCALL);
    engine->RegisterObjectMethod("Vector4", "Vector4& opMulAssign(const Vector4&in)", asMETHODPR(Vector4, operator *=, (const Vector4&), Vector4&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Vector4", "Vector4& opMulAssign(float)", asMETHODPR(Vector4, operator *=, (float), Vector4&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Vector4", "Vector4& opDivAssign(const Vector4&in)", asMETHODPR(Vector4, operator /=, (const Vector4&), Vector4&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Vector4", "Vector4& opDivAssign(float)", asMETHODPR(Vector4, operator /=, (float), Vector4&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Vector4", "bool &opEquals(const Vector4&in) const", asMETHOD(Vector4, operator ==), asCALL_THISCALL);
    engine->RegisterObjectMethod("Vector4", "Vector4 opNeg() const", asMETHODPR(Vector4, operator -, () const, Vector4), asCALL_THISCALL);
    engine->RegisterObjectMethod("Vector4", "Vector4 opAdd(const Vector4&in) const", asMETHOD(Vector4, operator +), asCALL_THISCALL);
    engine->RegisterObjectMethod("Vector4", "Vector4 opSub(const Vector4&in) const", asMETHODPR(Vector4, operator -, (const Vector4&) const, Vector4), asCALL_THISCALL);
    engine->RegisterObjectMethod("Vector4", "Vector4 opMul(const Vector4&in) const", asMETHODPR(Vector4, operator *, (const Vector4&) const, Vector4), asCALL_THISCALL);
    engine->RegisterObjectMethod("Vector4", "Vector4 opMul(float) const", asMETHODPR(Vector4, operator *, (float) const, Vector4), asCALL_THISCALL);
    engine->RegisterObjectMethod("Vector4", "Vector4 opDiv(const Vector4&in) const", asMETHODPR(Vector4, operator /, (const Vector4&) const, Vector4), asCALL_THISCALL);
    engine->RegisterObjectMethod("Vector4", "Vector4 opDiv(float) const", asMETHODPR(Vector4, operator /, (float) const, Vector4), asCALL_THISCALL);
    engine->RegisterObjectMethod("Vector4", "float DotProduct(const Vector4&in) const", asMETHOD(Vector4, DotProduct), asCALL_THISCALL);
    engine->RegisterObjectMethod("Vector4", "float AbsDotProduct(const Vector4&in) const", asMETHOD(Vector4, AbsDotProduct), asCALL_THISCALL);
    engine->RegisterObjectMethod("Vector4", "Vector4 Lerp(const Vector4&in, float) const", asMETHOD(Vector4, Lerp), asCALL_THISCALL);
    engine->RegisterObjectMethod("Vector4", "String ToString() const", asMETHOD(Vector4, ToString), asCALL_THISCALL);
    engine->RegisterObjectProperty("Vector4", "float x", offsetof(Vector4, x_));
    engine->RegisterObjectProperty("Vector4", "float y", offsetof(Vector4, y_));
    engine->RegisterObjectProperty("Vector4", "float z", offsetof(Vector4, z_));
    engine->RegisterObjectProperty("Vector4", "float w", offsetof(Vector4, w_));
}

static void ConstructQuaternion(Quaternion* ptr)
{
    new(ptr) Quaternion();
}

static void ConstructQuaternionCopy(const Quaternion& quat, Quaternion* ptr)
{
    new(ptr) Quaternion(quat);
}

static void ConstructQuaternionInit(float w, float x, float y, float z, Quaternion* ptr)
{
    new(ptr) Quaternion(w, x, y, z);
}

static void ConstructQuaternionAngleAxis(float angle, const Vector3& axis, Quaternion* ptr)
{
    new(ptr) Quaternion(angle, axis);
}

static void ConstructQuaternionEuler(float angleX, float angleY, float angleZ, Quaternion* ptr)
{
    new(ptr) Quaternion(angleX, angleY, angleZ);
}

static void ConstructQuaternionEulerVector(const Vector3& angles, Quaternion* ptr)
{
    new(ptr) Quaternion(angles.x_, angles.y_, angles.z_);
}

static void ConstructQuaternionRotation(const Vector3& start, const Vector3& end, Quaternion* ptr)
{
    new(ptr) Quaternion(start, end);
}

static void RegisterQuaternion(asIScriptEngine* engine)
{
    engine->RegisterObjectType("Quaternion", sizeof(Quaternion), asOBJ_VALUE | asOBJ_POD | asOBJ_APP_CLASS_CAK);
    engine->RegisterObjectBehaviour("Quaternion", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(ConstructQuaternion), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("Quaternion", asBEHAVE_CONSTRUCT, "void f(const Quaternion&in)", asFUNCTION(ConstructQuaternionCopy), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("Quaternion", asBEHAVE_CONSTRUCT, "void f(float, float, float, float)", asFUNCTION(ConstructQuaternionInit), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("Quaternion", asBEHAVE_CONSTRUCT, "void f(float, const Vector3&in)", asFUNCTION(ConstructQuaternionAngleAxis), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("Quaternion", asBEHAVE_CONSTRUCT, "void f(float, float, float)", asFUNCTION(ConstructQuaternionEuler), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("Quaternion", asBEHAVE_CONSTRUCT, "void f(const Vector3&in)", asFUNCTION(ConstructQuaternionEulerVector), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("Quaternion", asBEHAVE_CONSTRUCT, "void f(const Vector3&in, const Vector3&in)", asFUNCTION(ConstructQuaternionRotation), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("Quaternion", "Quaternion& opAssign(const Quaternion&in)", asMETHOD(Quaternion, operator =), asCALL_THISCALL);
    engine->RegisterObjectMethod("Quaternion", "Quaternion& opAddAssign(const Quaternion&in)", asMETHOD(Quaternion, operator +=), asCALL_THISCALL);
    engine->RegisterObjectMethod("Quaternion", "bool opEquals(const Quaternion&in) const", asMETHOD(Quaternion, operator ==), asCALL_THISCALL);
    engine->RegisterObjectMethod("Quaternion", "Quaternion opMul(float) const", asMETHODPR(Quaternion, operator *, (float) const, Quaternion), asCALL_THISCALL);
    engine->RegisterObjectMethod("Quaternion", "Vector3 opMul(const Vector3&in) const", asMETHODPR(Quaternion, operator *, (const Vector3&) const, Vector3), asCALL_THISCALL);
    engine->RegisterObjectMethod("Quaternion", "Quaternion opNeg() const", asMETHODPR(Quaternion, operator -, () const, Quaternion), asCALL_THISCALL);
    engine->RegisterObjectMethod("Quaternion", "Quaternion opAdd(const Quaternion&in) const", asMETHOD(Quaternion, operator +), asCALL_THISCALL);
    engine->RegisterObjectMethod("Quaternion", "Quaternion opSub(const Quaternion&in) const", asMETHODPR(Quaternion, operator +, (const Quaternion&) const, Quaternion), asCALL_THISCALL);
    engine->RegisterObjectMethod("Quaternion", "Quaternion opMul(const Quaternion&in) const", asMETHODPR(Quaternion, operator *, (const Quaternion&) const, Quaternion), asCALL_THISCALL);
    engine->RegisterObjectMethod("Quaternion", "void Normalize()", asMETHOD(Quaternion, Normalize), asCALL_THISCALL);
    engine->RegisterObjectMethod("Quaternion", "Quaternion Normalized() const", asMETHOD(Quaternion, Normalized), asCALL_THISCALL);
    engine->RegisterObjectMethod("Quaternion", "Quaternion Inverse() const", asMETHOD(Quaternion, Inverse), asCALL_THISCALL);
    engine->RegisterObjectMethod("Quaternion", "float DotProduct(const Quaternion&in) const", asMETHOD(Quaternion, DotProduct), asCALL_THISCALL);
    engine->RegisterObjectMethod("Quaternion", "Quaternion Nlerp(const Quaternion&in, float) const", asMETHOD(Quaternion, Nlerp), asCALL_THISCALL);
    engine->RegisterObjectMethod("Quaternion", "Quaternion Slerp(const Quaternion&in, float) const", asMETHOD(Quaternion, Slerp), asCALL_THISCALL);
    engine->RegisterObjectMethod("Quaternion", "String ToString() const", asMETHOD(Quaternion, ToString), asCALL_THISCALL);
    engine->RegisterObjectMethod("Quaternion", "Vector3 get_eulerAngles() const", asMETHOD(Quaternion, EulerAngles), asCALL_THISCALL);
    engine->RegisterObjectMethod("Quaternion", "float get_yaw() const", asMETHOD(Quaternion, YawAngle), asCALL_THISCALL);
    engine->RegisterObjectMethod("Quaternion", "float get_pitch() const", asMETHOD(Quaternion, PitchAngle), asCALL_THISCALL);
    engine->RegisterObjectMethod("Quaternion", "float get_roll() const", asMETHOD(Quaternion, RollAngle), asCALL_THISCALL);
    engine->RegisterObjectProperty("Quaternion", "float w", offsetof(Quaternion, w_));
    engine->RegisterObjectProperty("Quaternion", "float x", offsetof(Quaternion, x_));
    engine->RegisterObjectProperty("Quaternion", "float y", offsetof(Quaternion, y_));
    engine->RegisterObjectProperty("Quaternion", "float z", offsetof(Quaternion, z_));
}

static void ConstructRay(Ray* ptr)
{
    // Initialize to zero because performance is not critical
    new(ptr) Ray(Vector3::ZERO, Vector3::ZERO);
}

static void ConstructRayCopy(const Ray& ray, Ray* ptr)
{
    new(ptr) Ray(ray);
}

static void ConstructRayInit(const Vector3& origin, const Vector3& direction, Ray* ptr)
{
    // Normalize direction because performance is not critical
    new(ptr) Ray(origin, direction.Normalized());
}

static void RegisterRay(asIScriptEngine* engine)
{
    engine->RegisterObjectType("Ray", sizeof(Ray), asOBJ_VALUE | asOBJ_POD | asOBJ_APP_CLASS_CAK);
    engine->RegisterObjectBehaviour("Ray", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(ConstructRay), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("Ray", asBEHAVE_CONSTRUCT, "void f(const Ray&in)", asFUNCTION(ConstructRayCopy), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("Ray", asBEHAVE_CONSTRUCT, "void f(const Vector3&in, const Vector3&in)", asFUNCTION(ConstructRayInit), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("Ray", "Ray& opAssign(const Ray&in)", asMETHOD(Ray, operator =), asCALL_THISCALL);
    engine->RegisterObjectMethod("Ray", "bool opEquals(const Ray&in) const", asMETHOD(Ray, operator ==), asCALL_THISCALL);
    engine->RegisterObjectMethod("Ray", "void Define(const Vector3&in, const Vector3&in)", asMETHOD(Ray, Define), asCALL_THISCALL);
    engine->RegisterObjectMethod("Ray", "float Distance(const Vector3&in, const Vector3&in, const Vector3&in) const", asMETHODPR(Ray, Distance, (const Vector3&, const Vector3&, const Vector3&) const, float), asCALL_THISCALL);
    engine->RegisterObjectProperty("Ray", "Vector3 origin", offsetof(Ray, origin_));
    engine->RegisterObjectProperty("Ray", "Vector3 direction", offsetof(Ray, direction_));
}

static void ConstructRect(Rect* ptr)
{
    // Init to zero because performance is not critical
    new(ptr) Rect(Rect::ZERO);
}

static void ConstructRectCopy(const Rect& rect, Rect* ptr)
{
    new(ptr) Rect(rect);
}

static void ConstructRectInit(float left, float top, float right, float bottom, Rect* ptr)
{
    new(ptr) Rect(left, top, right, bottom);
}

static void ConstructRectInitVec(const Vector2& min, const Vector2& max, Rect* ptr)
{
    new(ptr) Rect(min, max);
}

static void RegisterRect(asIScriptEngine* engine)
{
    engine->RegisterObjectType("Rect", sizeof(Rect), asOBJ_VALUE | asOBJ_POD | asOBJ_APP_CLASS_CAK);
    engine->RegisterObjectBehaviour("Rect", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(ConstructRect), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("Rect", asBEHAVE_CONSTRUCT, "void f(const Rect&in)", asFUNCTION(ConstructRectCopy), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("Rect", asBEHAVE_CONSTRUCT, "void f(float, float, float, float)", asFUNCTION(ConstructRectInit), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("Rect", asBEHAVE_CONSTRUCT, "void f(const Vector2&in, const Vector2&in)", asFUNCTION(ConstructRectInitVec), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("Rect", "Rect& opAssign(const Rect&in)", asMETHOD(Rect, operator =), asCALL_THISCALL);
    engine->RegisterObjectMethod("Rect", "bool opEquals(const Rect&in) const", asMETHOD(Rect, operator ==), asCALL_THISCALL);
    engine->RegisterObjectMethod("Rect", "void Define(const Vector2&in, const Vector2&in)", asMETHODPR(Rect, Define, (const Vector2&, const Vector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Rect", "void Define(const Vector2&in)", asMETHODPR(Rect, Define, (const Vector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Rect", "void Merge(const Vector2&in)", asMETHODPR(Rect, Merge, (const Vector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Rect", "void Merge(const Rect&in)", asMETHODPR(Rect, Merge, (const Rect&), void), asCALL_THISCALL);
    engine->RegisterObjectProperty("Rect", "Vector2 min", offsetof(Rect, min_));
    engine->RegisterObjectProperty("Rect", "Vector2 max", offsetof(Rect, max_));
    engine->RegisterObjectProperty("Rect", "float left", offsetof(Rect, min_.x_));
    engine->RegisterObjectProperty("Rect", "float top", offsetof(Rect, min_.y_));
    engine->RegisterObjectProperty("Rect", "float right", offsetof(Rect, max_.x_));
    engine->RegisterObjectProperty("Rect", "float bottom", offsetof(Rect, max_.y_));
    engine->RegisterObjectProperty("Rect", "bool defined", offsetof(Rect, defined_));
}

static void ConstructBoundingBox(BoundingBox* ptr)
{
    new(ptr) BoundingBox();
}

static void ConstructBoundingBoxCopy(const BoundingBox& box, BoundingBox* ptr)
{
    new(ptr) BoundingBox(box);
}

static void ConstructBoundingBoxInit(const Vector3& min, const Vector3& max, BoundingBox* ptr)
{
    new(ptr) BoundingBox(min, max);
}

static void ConstructBoundingBoxFloat(float min, float max, BoundingBox* ptr)
{
    new(ptr) BoundingBox(min, max);
}

static void ConstructSphere(Sphere* ptr)
{
    new(ptr) Sphere();
}

static void ConstructSphereCopy(const Sphere& sphere, Sphere* ptr)
{
    new(ptr) Sphere(sphere);
}

static void ConstructSphereInit(const Vector3& center, float radius, Sphere* ptr)
{
    new(ptr) Sphere(center, radius);
}

static void ConstructFrustum(Frustum* ptr)
{
    new(ptr) Frustum();
}

static void ConstructFrustumCopy(const Frustum& frustum, Frustum* ptr)
{
    new(ptr) Frustum(frustum);
}

static void DestructFrustum(Frustum* ptr)
{
    ptr->~Frustum();
}

static Vector3 FrustumGetVertex(unsigned index, Frustum* ptr)
{
    if (index >= NUM_FRUSTUM_VERTICES)
        return Vector3::ZERO;
    return ptr->vertices_[index];
}

static void RegisterVolumes(asIScriptEngine* engine)
{
    engine->RegisterEnum("Intersection");
    engine->RegisterEnumValue("Intersection", "OUTSIDE", OUTSIDE);
    engine->RegisterEnumValue("Intersection", "INTERSECTS", INTERSECTS);
    engine->RegisterEnumValue("Intersection", "INSIDE", INSIDE);
    
    engine->RegisterObjectType("BoundingBox", sizeof(BoundingBox), asOBJ_VALUE | asOBJ_POD | asOBJ_APP_CLASS_CAK);
    engine->RegisterObjectType("Sphere", sizeof(Sphere), asOBJ_VALUE | asOBJ_POD | asOBJ_APP_CLASS_CAK);
    engine->RegisterObjectType("Frustum", sizeof(Frustum), asOBJ_VALUE | asOBJ_APP_CLASS_CDA);
    
    engine->RegisterObjectBehaviour("BoundingBox", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(ConstructBoundingBox), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("BoundingBox", asBEHAVE_CONSTRUCT, "void f(const BoundingBox&in)", asFUNCTION(ConstructBoundingBoxCopy), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("BoundingBox", asBEHAVE_CONSTRUCT, "void f(const Vector3&in, const Vector3&in)", asFUNCTION(ConstructBoundingBoxInit), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("BoundingBox", asBEHAVE_CONSTRUCT, "void f(float, float)", asFUNCTION(ConstructBoundingBoxFloat), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("BoundingBox", "BoundingBox& opAssign(const BoundingBox&in)", asMETHODPR(BoundingBox, operator =, (const BoundingBox&), BoundingBox&), asCALL_THISCALL);
    engine->RegisterObjectMethod("BoundingBox", "bool opEquals(const BoundingBox&in) const", asMETHOD(BoundingBox, operator ==), asCALL_THISCALL);
    engine->RegisterObjectMethod("BoundingBox", "void Define(const Vector3&in, const Vector3&in)", asMETHODPR(BoundingBox, Define, (const Vector3&, const Vector3&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("BoundingBox", "void Define(float, float)", asMETHODPR(BoundingBox, Define, (float, float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("BoundingBox", "void Define(const Frustum&in)", asMETHODPR(BoundingBox, Define, (const Frustum&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("BoundingBox", "void Define(const Sphere&in)", asMETHODPR(BoundingBox, Define, (const Sphere&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("BoundingBox", "void Merge(const Vector3&in)", asMETHODPR(BoundingBox, Merge, (const Vector3&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("BoundingBox", "void Merge(const BoundingBox&in)", asMETHODPR(BoundingBox, Merge, (const BoundingBox&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("BoundingBox", "void Merge(const Frustum&in)", asMETHODPR(BoundingBox, Merge, (const Frustum&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("BoundingBox", "void Merge(const Sphere&in)", asMETHODPR(BoundingBox, Merge, (const Sphere&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("BoundingBox", "void Intersect(const BoundingBox&in)", asMETHODPR(BoundingBox, Intersect, (const BoundingBox&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("BoundingBox", "Intersection IsInside(const Vector3&in) const", asMETHODPR(BoundingBox, IsInside, (const Vector3&) const, Intersection), asCALL_THISCALL);
    engine->RegisterObjectMethod("BoundingBox", "Intersection IsInside(const Sphere&in) const", asMETHODPR(BoundingBox, IsInside, (const Sphere&) const, Intersection), asCALL_THISCALL);
    engine->RegisterObjectMethod("BoundingBox", "Intersection IsInside(const BoundingBox&in) const", asMETHODPR(BoundingBox, IsInside, (const BoundingBox&) const, Intersection), asCALL_THISCALL);
    engine->RegisterObjectMethod("BoundingBox", "float Distance(const Ray&in) const", asMETHOD(BoundingBox, Distance), asCALL_THISCALL);
    engine->RegisterObjectMethod("BoundingBox", "Vector3 get_center() const", asMETHOD(BoundingBox, Center), asCALL_THISCALL);
    engine->RegisterObjectMethod("BoundingBox", "Vector3 get_size() const", asMETHOD(BoundingBox, Size), asCALL_THISCALL);
    engine->RegisterObjectMethod("BoundingBox", "Vector3 get_halfSize() const", asMETHOD(BoundingBox, HalfSize), asCALL_THISCALL);
    engine->RegisterObjectProperty("BoundingBox", "Vector3 min", offsetof(BoundingBox, min_));
    engine->RegisterObjectProperty("BoundingBox", "Vector3 max", offsetof(BoundingBox, max_));
    engine->RegisterObjectProperty("BoundingBox", "bool defined", offsetof(BoundingBox, defined_));
    
    engine->RegisterObjectBehaviour("Sphere", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(ConstructSphere), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("Sphere", asBEHAVE_CONSTRUCT, "void f(const Sphere&in)", asFUNCTION(ConstructSphereCopy), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("Sphere", asBEHAVE_CONSTRUCT, "void f(const Vector3&in, float)", asFUNCTION(ConstructSphereInit), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("Sphere", "Sphere& opAssign(const Sphere&in)", asMETHODPR(Sphere, operator =, (const Sphere&), Sphere&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Sphere", "bool &opEquals(const Sphere&in) const", asMETHOD(Sphere, operator ==), asCALL_THISCALL);
    engine->RegisterObjectMethod("Sphere", "void Define(const Vector3&in, float)", asMETHODPR(Sphere, Define, (const Vector3&, float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Sphere", "void Define(const BoundingBox&in)", asMETHODPR(Sphere, Define, (const BoundingBox&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Sphere", "void Define(const Frustum&in)", asMETHODPR(Sphere, Define, (const Frustum&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Sphere", "void Merge(const Vector3&in)", asMETHODPR(Sphere, Merge, (const Vector3&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Sphere", "void Merge(const BoundingBox&in)", asMETHODPR(Sphere, Merge, (const BoundingBox&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Sphere", "void Merge(const Frustum&in)", asMETHODPR(Sphere, Merge, (const Frustum&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Sphere", "void Merge(const Sphere&in)", asMETHODPR(Sphere, Merge, (const Sphere&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Sphere", "Intersection IsInside(const Vector3&in) const", asMETHODPR(Sphere, IsInside, (const Vector3&) const, Intersection), asCALL_THISCALL);
    engine->RegisterObjectMethod("Sphere", "Intersection IsInside(const Sphere&in) const", asMETHODPR(Sphere, IsInside, (const Sphere&) const, Intersection), asCALL_THISCALL);
    engine->RegisterObjectMethod("Sphere", "Intersection IsInside(const BoundingBox&in) const", asMETHODPR(Sphere, IsInside, (const BoundingBox&) const, Intersection), asCALL_THISCALL);
    engine->RegisterObjectMethod("Sphere", "float Distance(const Ray&in) const", asMETHOD(Sphere, Distance), asCALL_THISCALL);
    engine->RegisterObjectProperty("Sphere", "Vector3 center", offsetof(Sphere, center_));
    engine->RegisterObjectProperty("Sphere", "float radius", offsetof(Sphere, radius_));
    engine->RegisterObjectProperty("Sphere", "bool defined", offsetof(Sphere, defined_));
    
    engine->RegisterObjectBehaviour("Frustum", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(ConstructFrustum), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("Frustum", asBEHAVE_CONSTRUCT, "void f(const Frustum&in)", asFUNCTION(ConstructFrustumCopy), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("Frustum", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(DestructFrustum), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("Frustum", "Frustum& opAssign(const Frustum&in)", asMETHODPR(Frustum, operator =, (const Frustum&), Frustum&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Frustum", "Intersection IsInside(const Vector3&in)", asMETHODPR(Frustum, IsInside, (const Vector3&) const, Intersection), asCALL_THISCALL);
    engine->RegisterObjectMethod("Frustum", "Intersection IsInside(const BoundingBox&in)", asMETHODPR(Frustum, IsInside, (const BoundingBox&) const, Intersection), asCALL_THISCALL);
    engine->RegisterObjectMethod("Frustum", "Intersection IsInside(const Sphere&in)", asMETHODPR(Frustum, IsInside, (const Sphere&) const, Intersection), asCALL_THISCALL);
    engine->RegisterObjectProperty("Frustum", "bool defined", offsetof(Frustum, defined_));
    engine->RegisterObjectMethod("Frustum", "Vector3 get_vertices(uint) const", asFUNCTION(FrustumGetVertex), asCALL_CDECL_OBJLAST);
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

static void RegisterColor(asIScriptEngine* engine)
{
    engine->RegisterObjectType("Color", sizeof(Color), asOBJ_VALUE | asOBJ_POD | asOBJ_APP_CLASS_CAK);
    engine->RegisterObjectBehaviour("Color", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(ConstructColor), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("Color", asBEHAVE_CONSTRUCT, "void f(const Color&in)", asFUNCTION(ConstructColorCopy), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("Color", asBEHAVE_CONSTRUCT, "void f(float, float, float, float)", asFUNCTION(ConstructColorRGBA), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("Color", asBEHAVE_CONSTRUCT, "void f(float, float, float)", asFUNCTION(ConstructColorRGB), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("Color", "Color& opAssign(const Color&in)", asMETHOD(Color, operator =), asCALL_THISCALL);
    engine->RegisterObjectMethod("Color", "Color& opAddAssign(const Color&in)", asMETHOD(Color, operator +=), asCALL_THISCALL);
    engine->RegisterObjectMethod("Color", "bool opEquals(const Color&in) const", asMETHOD(Color, operator ==), asCALL_THISCALL);
    engine->RegisterObjectMethod("Color", "Color opMul(float) const", asMETHOD(Color, operator *), asCALL_THISCALL);
    engine->RegisterObjectMethod("Color", "Color opAdd(const Color&in) const", asMETHOD(Color, operator +), asCALL_THISCALL);
    engine->RegisterObjectMethod("Color", "Color Lerp(const Color&in, float) const", asMETHOD(Color, Lerp), asCALL_THISCALL);
    engine->RegisterObjectMethod("Color", "String ToString() const", asMETHOD(Color, ToString), asCALL_THISCALL);
    engine->RegisterObjectMethod("Color", "Vector3 get_rgb() const", asMETHOD(Color, RGBValues), asCALL_THISCALL);
    engine->RegisterObjectMethod("Color", "float get_intensity() const", asMETHOD(Color, Intensity), asCALL_THISCALL);
    engine->RegisterObjectProperty("Color", "float r", offsetof(Color, r_));
    engine->RegisterObjectProperty("Color", "float g", offsetof(Color, g_));
    engine->RegisterObjectProperty("Color", "float b", offsetof(Color, b_));
    engine->RegisterObjectProperty("Color", "float a", offsetof(Color, a_));
}

void RegisterMathAPI(asIScriptEngine* engine)
{
    RegisterMathFunctions(engine);
    RegisterIntRect(engine);
    RegisterIntVector2(engine);
    RegisterVector2(engine);
    RegisterVector3(engine);
    RegisterVector4(engine);
    RegisterQuaternion(engine);
    RegisterRay(engine);
    RegisterRect(engine);
    RegisterVolumes(engine);
    RegisterColor(engine);
    
    /// \todo Register Matrix types
}
