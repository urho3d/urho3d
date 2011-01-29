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
#include "Frustum.h"
#include "StringUtils.h"

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

static float ASin(float x)
{
    return M_RADTODEG * asinf(clamp(x, -1.0f, 1.0f));
}

static float ACos(float x)
{
    return M_RADTODEG * acosf(clamp(x, -1.0f, 1.0f));
}

static float ATan(float x)
{
    return M_RADTODEG * atanf(x);
}

static float ATan2(float y, float x)
{
    return M_RADTODEG * atan2f(y, x);
}

static void registerMathFunctions(asIScriptEngine* engine)
{
    engine->RegisterGlobalFunction("float sin(float)", asFUNCTION(Sin), asCALL_CDECL);
    engine->RegisterGlobalFunction("float cos(float)", asFUNCTION(Cos), asCALL_CDECL);
    engine->RegisterGlobalFunction("float tan(float)", asFUNCTION(Tan), asCALL_CDECL);
    engine->RegisterGlobalFunction("float asin(float)", asFUNCTION(ASin), asCALL_CDECL);
    engine->RegisterGlobalFunction("float acos(float)", asFUNCTION(ACos), asCALL_CDECL);
    engine->RegisterGlobalFunction("float atan(float)", asFUNCTION(ATan), asCALL_CDECL);
    engine->RegisterGlobalFunction("float atan2(float, float)", asFUNCTION(ATan2), asCALL_CDECL);
    engine->RegisterGlobalFunction("float abs(float)", asFUNCTION(fabsf), asCALL_CDECL);
    engine->RegisterGlobalFunction("float sqrt(float)", asFUNCTION(sqrtf), asCALL_CDECL);
    engine->RegisterGlobalFunction("float pow(float)", asFUNCTION(powf), asCALL_CDECL);
    engine->RegisterGlobalFunction("float random()", asFUNCTIONPR(random, (), float), asCALL_CDECL);
    engine->RegisterGlobalFunction("float random(float)", asFUNCTIONPR(random, (float), float), asCALL_CDECL);
    engine->RegisterGlobalFunction("int randomInt()", asFUNCTION(rand), asCALL_CDECL);
    engine->RegisterGlobalFunction("int randomInt(int)", asFUNCTIONPR(random, (int), int), asCALL_CDECL);
    engine->RegisterGlobalFunction("void setRandomSeed(int)", asFUNCTION(srand), asCALL_CDECL);
    engine->RegisterGlobalFunction("float min(float, float)", asFUNCTIONPR(min, (float, float), float), asCALL_CDECL);
    engine->RegisterGlobalFunction("float max(float, float)", asFUNCTIONPR(min, (float, float), float), asCALL_CDECL);
    engine->RegisterGlobalFunction("float clamp(float, float, float)", asFUNCTIONPR(clamp, (float, float, float), float), asCALL_CDECL);
    engine->RegisterGlobalFunction("float lerp(float, float, float)", asFUNCTIONPR(lerp, (float, float, float), float), asCALL_CDECL);
}

static void ConstructIntRect(IntRect* ptr)
{
    // Init to zero because performance is not critical
    new(ptr) IntRect(IntRect::sZero);
}

static void ConstructIntRectCopy(const IntRect& rect, IntRect* ptr)
{
    new(ptr) IntRect(rect);
}

static void ConstructIntRectInit(int left, int top, int right, int bottom, IntRect* ptr)
{
    new(ptr) IntRect(left, top, right, bottom);
}

static void registerIntRect(asIScriptEngine* engine)
{
    engine->RegisterObjectType("IntRect", sizeof(IntRect), asOBJ_VALUE | asOBJ_POD | asOBJ_APP_CLASS_CA);
    engine->RegisterObjectBehaviour("IntRect", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(ConstructIntRect), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("IntRect", asBEHAVE_CONSTRUCT, "void f(const IntRect& in)", asFUNCTION(ConstructIntRectCopy), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("IntRect", asBEHAVE_CONSTRUCT, "void f(int, int, int, int)", asFUNCTION(ConstructIntRectInit), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("IntRect", "IntRect &opAssign(const IntRect& in)", asMETHOD(IntRect, operator =), asCALL_THISCALL);
    engine->RegisterObjectMethod("IntRect", "bool &opEquals(const IntRect& in) const", asMETHOD(IntRect, operator ==), asCALL_THISCALL);
    engine->RegisterObjectProperty("IntRect", "int left", offsetof(IntRect, mLeft));
    engine->RegisterObjectProperty("IntRect", "int top", offsetof(IntRect, mTop));
    engine->RegisterObjectProperty("IntRect", "int right", offsetof(IntRect, mRight));
    engine->RegisterObjectProperty("IntRect", "int bottom", offsetof(IntRect, mBottom));
}

static void ConstructIntVector2(IntVector2* ptr)
{
    // Init to zero because performance is not critical
    new(ptr) IntVector2(IntVector2::sZero);
}

static void ConstructIntVector2Copy(const IntVector2& vector, IntVector2* ptr)
{
    new(ptr) IntVector2(vector);
}

static void ConstructIntVector2Init(int x, int y, IntVector2* ptr)
{
    new(ptr) IntVector2(x, y);
}

static void registerIntVector2(asIScriptEngine* engine)
{
    engine->RegisterObjectType("IntVector2", sizeof(IntVector2), asOBJ_VALUE | asOBJ_POD | asOBJ_APP_CLASS_CA);
    engine->RegisterObjectBehaviour("IntVector2", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(ConstructIntVector2), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("IntVector2", asBEHAVE_CONSTRUCT, "void f(const IntVector2& in)", asFUNCTION(ConstructIntVector2Copy), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("IntVector2", asBEHAVE_CONSTRUCT, "void f(int, int)", asFUNCTION(ConstructIntVector2Init), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("IntVector2", "IntVector2 &opAssign(const IntVector2& in)", asMETHOD(IntVector2, operator =), asCALL_THISCALL);
    engine->RegisterObjectMethod("IntVector2", "IntVector2 &opAddAssign(const IntVector2& in)", asMETHOD(IntVector2, operator +=), asCALL_THISCALL);
    engine->RegisterObjectMethod("IntVector2", "IntVector2 &opSubAssign(const IntVector2& in)", asMETHOD(IntVector2, operator -=), asCALL_THISCALL);
    engine->RegisterObjectMethod("IntVector2", "IntVector2 &opMulAssign(int)", asMETHODPR(IntVector2, operator *=, (int), IntVector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("IntVector2", "IntVector2 &opDivAssign(int)", asMETHODPR(IntVector2, operator /=, (int), IntVector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("IntVector2", "bool &opEquals(const IntVector2& in) const", asMETHOD(IntVector2, operator ==), asCALL_THISCALL);
    engine->RegisterObjectMethod("IntVector2", "IntVector2 opNeg() const", asMETHODPR(IntVector2, operator -, () const, IntVector2), asCALL_THISCALL);
    engine->RegisterObjectMethod("IntVector2", "IntVector2 opAdd(const IntVector2& in) const", asMETHOD(IntVector2, operator +), asCALL_THISCALL);
    engine->RegisterObjectMethod("IntVector2", "IntVector2 opSub(const IntVector2& in) const", asMETHODPR(IntVector2, operator -, (const IntVector2&) const, IntVector2), asCALL_THISCALL);
    engine->RegisterObjectMethod("IntVector2", "IntVector2 opMul(int) const", asMETHODPR(IntVector2, operator *, (int) const, IntVector2), asCALL_THISCALL);
    engine->RegisterObjectMethod("IntVector2", "IntVector2 opDiv(int) const", asMETHODPR(IntVector2, operator /, (int) const, IntVector2), asCALL_THISCALL);
    engine->RegisterObjectMethod("IntVector2", "string toString() const", asFUNCTIONPR(toString, (const IntVector2&), std::string), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectProperty("IntVector2", "int x", offsetof(IntVector2, mX));
    engine->RegisterObjectProperty("IntVector2", "int y", offsetof(IntVector2, mY));
}

static void ConstructVector2(Vector2* ptr)
{
    // Init to zero because performance is not critical
    new(ptr) Vector2(Vector2::sZero);
}

static void ConstructVector2Copy(const Vector2& vector, Vector2* ptr)
{
    new(ptr) Vector2(vector);
}

static void ConstructVector2Init(float x, float y, Vector2* ptr)
{
    new(ptr) Vector2(x, y);
}

static void registerVector2(asIScriptEngine* engine)
{
    engine->RegisterObjectType("Vector2", sizeof(Vector2), asOBJ_VALUE | asOBJ_POD | asOBJ_APP_CLASS_CA);
    engine->RegisterObjectBehaviour("Vector2", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(ConstructVector2), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("Vector2", asBEHAVE_CONSTRUCT, "void f(const Vector2& in)", asFUNCTION(ConstructVector2Copy), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("Vector2", asBEHAVE_CONSTRUCT, "void f(float, float)", asFUNCTION(ConstructVector2Init), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("Vector2", "Vector2 &opAssign(const Vector2& in)", asMETHOD(Vector2, operator =), asCALL_THISCALL);
    engine->RegisterObjectMethod("Vector2", "Vector2 &opAddAssign(const Vector2& in)", asMETHOD(Vector2, operator +=), asCALL_THISCALL);
    engine->RegisterObjectMethod("Vector2", "Vector2 &opSubAssign(const Vector2& in)", asMETHOD(Vector2, operator -=), asCALL_THISCALL);
    engine->RegisterObjectMethod("Vector2", "Vector2 &opMulAssign(const Vector2& in)", asMETHODPR(Vector2, operator *=, (const Vector2&), Vector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Vector2", "Vector2 &opMulAssign(float)", asMETHODPR(Vector2, operator *=, (float), Vector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Vector2", "Vector2 &opDivAssign(const Vector2& in)", asMETHODPR(Vector2, operator /=, (const Vector2&), Vector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Vector2", "Vector2 &opDivAssign(float)", asMETHODPR(Vector2, operator /=, (float), Vector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Vector2", "bool &opEquals(const Vector2& in) const", asMETHOD(Vector2, operator ==), asCALL_THISCALL);
    engine->RegisterObjectMethod("Vector2", "Vector2 opNeg() const", asMETHODPR(Vector2, operator -, () const, Vector2), asCALL_THISCALL);
    engine->RegisterObjectMethod("Vector2", "Vector2 opAdd(const Vector2& in) const", asMETHOD(Vector2, operator +), asCALL_THISCALL);
    engine->RegisterObjectMethod("Vector2", "Vector2 opSub(const Vector2& in) const", asMETHODPR(Vector2, operator -, (const Vector2&) const, Vector2), asCALL_THISCALL);
    engine->RegisterObjectMethod("Vector2", "Vector2 opMul(const Vector2& in) const", asMETHODPR(Vector2, operator *, (const Vector2&) const, Vector2), asCALL_THISCALL);
    engine->RegisterObjectMethod("Vector2", "Vector2 opMul(float) const", asMETHODPR(Vector2, operator *, (float) const, Vector2), asCALL_THISCALL);
    engine->RegisterObjectMethod("Vector2", "Vector2 opDiv(const Vector2& in) const", asMETHODPR(Vector2, operator /, (const Vector2&) const, Vector2), asCALL_THISCALL);
    engine->RegisterObjectMethod("Vector2", "Vector2 opDiv(float) const", asMETHODPR(Vector2, operator /, (float) const, Vector2), asCALL_THISCALL);
    engine->RegisterObjectMethod("Vector2", "float normalize()", asMETHOD(Vector2, normalize), asCALL_THISCALL);
    engine->RegisterObjectMethod("Vector2", "float getLength() const", asMETHOD(Vector2, getLength), asCALL_THISCALL);
    engine->RegisterObjectMethod("Vector2", "float getLengthSquared() const", asMETHOD(Vector2, getLengthSquared), asCALL_THISCALL);
    engine->RegisterObjectMethod("Vector2", "float dotProduct(const Vector2& in) const", asMETHOD(Vector2, dotProduct), asCALL_THISCALL);
    engine->RegisterObjectMethod("Vector2", "float absDotProduct(const Vector2& in) const", asMETHOD(Vector2, absDotProduct), asCALL_THISCALL);
    engine->RegisterObjectMethod("Vector2", "Vector2 lerp(const Vector2& in, float) const", asMETHOD(Vector2, lerp), asCALL_THISCALL);
    engine->RegisterObjectMethod("Vector2", "Vector2 getNormalized() const", asMETHOD(Vector2, getNormalized), asCALL_THISCALL);
    engine->RegisterObjectMethod("Vector2", "string toString() const", asFUNCTIONPR(toString, (const Vector2&), std::string), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectProperty("Vector2", "float x", offsetof(Vector2, mX));
    engine->RegisterObjectProperty("Vector2", "float y", offsetof(Vector2, mY));
}

static void ConstructVector3(Vector3* ptr)
{
    // Init to zero because performance is not critical
    new(ptr) Vector3(Vector3::sZero);
}

static void ConstructVector3Copy(const Vector3& vector, Vector3* ptr)
{
    new(ptr) Vector3(vector);
}

static void ConstructVector3Init(float x, float y, float z, Vector3* ptr)
{
    new(ptr) Vector3(x, y, z);
}

static void registerVector3(asIScriptEngine* engine)
{
    engine->RegisterObjectType("Vector3", sizeof(Vector3), asOBJ_VALUE | asOBJ_POD | asOBJ_APP_CLASS_CA);
    engine->RegisterObjectBehaviour("Vector3", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(ConstructVector3), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("Vector3", asBEHAVE_CONSTRUCT, "void f(const Vector3& in)", asFUNCTION(ConstructVector3Copy), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("Vector3", asBEHAVE_CONSTRUCT, "void f(float, float, float)", asFUNCTION(ConstructVector3Init), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("Vector3", "Vector3 &opAssign(const Vector3& in)", asMETHOD(Vector3, operator =), asCALL_THISCALL);
    engine->RegisterObjectMethod("Vector3", "Vector3 &opAddAssign(const Vector3& in)", asMETHOD(Vector3, operator +=), asCALL_THISCALL);
    engine->RegisterObjectMethod("Vector3", "Vector3 &opSubAssign(const Vector3& in)", asMETHOD(Vector3, operator -=), asCALL_THISCALL);
    engine->RegisterObjectMethod("Vector3", "Vector3 &opMulAssign(const Vector3& in)", asMETHODPR(Vector3, operator *=, (const Vector3&), Vector3&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Vector3", "Vector3 &opMulAssign(float)", asMETHODPR(Vector3, operator *=, (float), Vector3&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Vector3", "Vector3 &opDivAssign(const Vector3& in)", asMETHODPR(Vector3, operator /=, (const Vector3&), Vector3&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Vector3", "Vector3 &opDivAssign(float)", asMETHODPR(Vector3, operator /=, (float), Vector3&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Vector3", "bool &opEquals(const Vector3& in) const", asMETHOD(Vector3, operator ==), asCALL_THISCALL);
    engine->RegisterObjectMethod("Vector3", "Vector3 opNeg() const", asMETHODPR(Vector3, operator -, () const, Vector3), asCALL_THISCALL);
    engine->RegisterObjectMethod("Vector3", "Vector3 opAdd(const Vector3& in) const", asMETHOD(Vector3, operator +), asCALL_THISCALL);
    engine->RegisterObjectMethod("Vector3", "Vector3 opSub(const Vector3& in) const", asMETHODPR(Vector3, operator -, (const Vector3&) const, Vector3), asCALL_THISCALL);
    engine->RegisterObjectMethod("Vector3", "Vector3 opMul(const Vector3& in) const", asMETHODPR(Vector3, operator *, (const Vector3&) const, Vector3), asCALL_THISCALL);
    engine->RegisterObjectMethod("Vector3", "Vector3 opMul(float) const", asMETHODPR(Vector3, operator *, (float) const, Vector3), asCALL_THISCALL);
    engine->RegisterObjectMethod("Vector3", "Vector3 opDiv(const Vector3& in) const", asMETHODPR(Vector3, operator /, (const Vector3&) const, Vector3), asCALL_THISCALL);
    engine->RegisterObjectMethod("Vector3", "Vector3 opDiv(float) const", asMETHODPR(Vector3, operator /, (float) const, Vector3), asCALL_THISCALL);
    engine->RegisterObjectMethod("Vector3", "float normalize()", asMETHOD(Vector3, normalize), asCALL_THISCALL);
    engine->RegisterObjectMethod("Vector3", "float getLength() const", asMETHOD(Vector3, getLength), asCALL_THISCALL);
    engine->RegisterObjectMethod("Vector3", "float getLengthSquared() const", asMETHOD(Vector3, getLengthSquared), asCALL_THISCALL);
    engine->RegisterObjectMethod("Vector3", "float dotProduct(const Vector3& in) const", asMETHOD(Vector3, dotProduct), asCALL_THISCALL);
    engine->RegisterObjectMethod("Vector3", "float absDotProduct(const Vector3& in) const", asMETHOD(Vector3, absDotProduct), asCALL_THISCALL);
    engine->RegisterObjectMethod("Vector3", "Vector3 crossProduct(const Vector3& in) const", asMETHOD(Vector3, crossProduct), asCALL_THISCALL);
    engine->RegisterObjectMethod("Vector3", "Vector3 lerp(const Vector3& in, float) const", asMETHOD(Vector3, lerp), asCALL_THISCALL);
    engine->RegisterObjectMethod("Vector3", "Vector3 getNormalized() const", asMETHOD(Vector3, getNormalized), asCALL_THISCALL);
    engine->RegisterObjectMethod("Vector3", "string toString() const", asFUNCTIONPR(toString, (const Vector3&), std::string), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectProperty("Vector3", "float x", offsetof(Vector3, mX));
    engine->RegisterObjectProperty("Vector3", "float y", offsetof(Vector3, mY));
    engine->RegisterObjectProperty("Vector3", "float z", offsetof(Vector3, mZ));
}

static void ConstructVector4(Vector4* ptr)
{
    // Init to zero because performance is not critical
    new(ptr) Vector4(Vector4::sZero);
}

static void ConstructVector4Copy(const Vector4& vector, Vector4* ptr)
{
    new(ptr) Vector4(vector);
}

static void ConstructVector4Init(float x, float y, float z, float w, Vector4* ptr)
{
    new(ptr) Vector4(x, y, z, w);
}

static void registerVector4(asIScriptEngine* engine)
{
    engine->RegisterObjectType("Vector4", sizeof(Vector4), asOBJ_VALUE | asOBJ_POD | asOBJ_APP_CLASS_CA);
    engine->RegisterObjectBehaviour("Vector4", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(ConstructVector4), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("Vector4", asBEHAVE_CONSTRUCT, "void f(const Vector4& in)", asFUNCTION(ConstructVector4Copy), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("Vector4", asBEHAVE_CONSTRUCT, "void f(float, float, float)", asFUNCTION(ConstructVector4Init), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("Vector4", "Vector4 &opAssign(const Vector4& in)", asMETHOD(Vector4, operator =), asCALL_THISCALL);
    engine->RegisterObjectMethod("Vector4", "Vector4 &opAddAssign(const Vector4& in)", asMETHOD(Vector4, operator +=), asCALL_THISCALL);
    engine->RegisterObjectMethod("Vector4", "Vector4 &opSubAssign(const Vector4& in)", asMETHOD(Vector4, operator -=), asCALL_THISCALL);
    engine->RegisterObjectMethod("Vector4", "Vector4 &opMulAssign(const Vector4& in)", asMETHODPR(Vector4, operator *=, (const Vector4&), Vector4&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Vector4", "Vector4 &opMulAssign(float)", asMETHODPR(Vector4, operator *=, (float), Vector4&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Vector4", "Vector4 &opDivAssign(const Vector4& in)", asMETHODPR(Vector4, operator /=, (const Vector4&), Vector4&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Vector4", "Vector4 &opDivAssign(float)", asMETHODPR(Vector4, operator /=, (float), Vector4&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Vector4", "bool &opEquals(const Vector4& in) const", asMETHOD(Vector4, operator ==), asCALL_THISCALL);
    engine->RegisterObjectMethod("Vector4", "Vector4 opNeg() const", asMETHODPR(Vector4, operator -, () const, Vector4), asCALL_THISCALL);
    engine->RegisterObjectMethod("Vector4", "Vector4 opAdd(const Vector4& in) const", asMETHOD(Vector4, operator +), asCALL_THISCALL);
    engine->RegisterObjectMethod("Vector4", "Vector4 opSub(const Vector4& in) const", asMETHODPR(Vector4, operator -, (const Vector4&) const, Vector4), asCALL_THISCALL);
    engine->RegisterObjectMethod("Vector4", "Vector4 opMul(const Vector4& in) const", asMETHODPR(Vector4, operator *, (const Vector4&) const, Vector4), asCALL_THISCALL);
    engine->RegisterObjectMethod("Vector4", "Vector4 opMul(float) const", asMETHODPR(Vector4, operator *, (float) const, Vector4), asCALL_THISCALL);
    engine->RegisterObjectMethod("Vector4", "Vector4 opDiv(const Vector4& in) const", asMETHODPR(Vector4, operator /, (const Vector4&) const, Vector4), asCALL_THISCALL);
    engine->RegisterObjectMethod("Vector4", "Vector4 opDiv(float) const", asMETHODPR(Vector4, operator /, (float) const, Vector4), asCALL_THISCALL);
    engine->RegisterObjectMethod("Vector4", "float dotProduct(const Vector4& in) const", asMETHOD(Vector4, dotProduct), asCALL_THISCALL);
    engine->RegisterObjectMethod("Vector4", "float absDotProduct(const Vector4& in) const", asMETHOD(Vector4, absDotProduct), asCALL_THISCALL);
    engine->RegisterObjectMethod("Vector4", "Vector4 lerp(const Vector4& in, float) const", asMETHOD(Vector4, lerp), asCALL_THISCALL);
    engine->RegisterObjectMethod("Vector4", "string toString() const", asFUNCTIONPR(toString, (const Vector4&), std::string), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectProperty("Vector4", "float x", offsetof(Vector4, mX));
    engine->RegisterObjectProperty("Vector4", "float y", offsetof(Vector4, mY));
    engine->RegisterObjectProperty("Vector4", "float z", offsetof(Vector4, mZ));
    engine->RegisterObjectProperty("Vector4", "float w", offsetof(Vector4, mW));
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

static void ConstructQuaternionRotation(const Vector3& start, const Vector3& end, Quaternion* ptr)
{
    new(ptr) Quaternion(start, end);
}

static void registerQuaternion(asIScriptEngine* engine)
{
    engine->RegisterObjectType("Quaternion", sizeof(Quaternion), asOBJ_VALUE | asOBJ_POD | asOBJ_APP_CLASS_CA);
    engine->RegisterObjectBehaviour("Quaternion", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(ConstructQuaternion), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("Quaternion", asBEHAVE_CONSTRUCT, "void f(const Quaternion& in)", asFUNCTION(ConstructQuaternionCopy), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("Quaternion", asBEHAVE_CONSTRUCT, "void f(float, float, float, float)", asFUNCTION(ConstructQuaternionInit), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("Quaternion", asBEHAVE_CONSTRUCT, "void f(float, const Vector3& in)", asFUNCTION(ConstructQuaternionAngleAxis), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("Quaternion", asBEHAVE_CONSTRUCT, "void f(float, float, float)", asFUNCTION(ConstructQuaternionEuler), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("Quaternion", asBEHAVE_CONSTRUCT, "void f(const Vector3& in, const Vector3& in)", asFUNCTION(ConstructQuaternionRotation), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("Quaternion", "Quaternion &opAssign(const Quaternion& in)", asMETHOD(Quaternion, operator =), asCALL_THISCALL);
    engine->RegisterObjectMethod("Quaternion", "Quaternion &opAddAssign(const Quaternion& in)", asMETHOD(Quaternion, operator +=), asCALL_THISCALL);
    engine->RegisterObjectMethod("Quaternion", "bool opEquals(const Quaternion& in) const", asMETHOD(Quaternion, operator ==), asCALL_THISCALL);
    engine->RegisterObjectMethod("Quaternion", "Quaternion opMul(float) const", asMETHODPR(Quaternion, operator *, (float) const, Quaternion), asCALL_THISCALL);
    engine->RegisterObjectMethod("Quaternion", "Vector3 opMul(const Vector3& in) const", asMETHODPR(Quaternion, operator *, (const Vector3&) const, Vector3), asCALL_THISCALL);
    engine->RegisterObjectMethod("Quaternion", "Quaternion opNeg() const", asMETHODPR(Quaternion, operator -, () const, Quaternion), asCALL_THISCALL);
    engine->RegisterObjectMethod("Quaternion", "Quaternion opAdd(const Quaternion& in) const", asMETHOD(Quaternion, operator +), asCALL_THISCALL);
    engine->RegisterObjectMethod("Quaternion", "Quaternion opSub(const Quaternion& in) const", asMETHODPR(Quaternion, operator +, (const Quaternion&) const, Quaternion), asCALL_THISCALL);
    engine->RegisterObjectMethod("Quaternion", "Quaternion opMul(const Quaternion& in) const", asMETHODPR(Quaternion, operator *, (const Quaternion&) const, Quaternion), asCALL_THISCALL);
    engine->RegisterObjectMethod("Quaternion", "void normalize()", asMETHOD(Quaternion, normalize), asCALL_THISCALL);
    engine->RegisterObjectMethod("Quaternion", "void fromAngleAxis(float, const Vector3& in)", asMETHOD(Quaternion, fromAngleAxis), asCALL_THISCALL);
    engine->RegisterObjectMethod("Quaternion", "void fromEulerAngles(float, float, float)", asMETHOD(Quaternion, fromEulerAngles), asCALL_THISCALL);
    engine->RegisterObjectMethod("Quaternion", "void fromRotation(const Vector3& in, const Vector3& in)", asMETHOD(Quaternion, fromRotationTo), asCALL_THISCALL);
    engine->RegisterObjectMethod("Quaternion", "Quaternion getNormalized() const", asMETHOD(Quaternion, getNormalized), asCALL_THISCALL);
    engine->RegisterObjectMethod("Quaternion", "Quaternion getInverse() const", asMETHOD(Quaternion, getInverse), asCALL_THISCALL);
    engine->RegisterObjectMethod("Quaternion", "float dotProduct(const Quaternion& in) const", asMETHOD(Quaternion, dotProduct), asCALL_THISCALL);
    engine->RegisterObjectMethod("Quaternion", "Quaternion nlerp(const Quaternion& in, float) const", asMETHOD(Quaternion, nlerp), asCALL_THISCALL);
    engine->RegisterObjectMethod("Quaternion", "void getEulerAngles(float &out, float &out, float &out) const", asMETHOD(Quaternion, getEulerAngles), asCALL_THISCALL);
    engine->RegisterObjectMethod("Quaternion", "float getYaw() const", asMETHOD(Quaternion, getYaw), asCALL_THISCALL);
    engine->RegisterObjectMethod("Quaternion", "float getPitch() const", asMETHOD(Quaternion, getPitch), asCALL_THISCALL);
    engine->RegisterObjectMethod("Quaternion", "float getRoll() const", asMETHOD(Quaternion, getRoll), asCALL_THISCALL);
    engine->RegisterObjectMethod("Quaternion", "Quaternion slerp(const Quaternion& in, float) const", asMETHOD(Quaternion, slerp), asCALL_THISCALL);
    engine->RegisterObjectMethod("Quaternion", "string toString() const", asFUNCTIONPR(toString, (const Quaternion&), std::string), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectProperty("Quaternion", "float w", offsetof(Quaternion, mW));
    engine->RegisterObjectProperty("Quaternion", "float x", offsetof(Quaternion, mX));
    engine->RegisterObjectProperty("Quaternion", "float y", offsetof(Quaternion, mY));
    engine->RegisterObjectProperty("Quaternion", "float z", offsetof(Quaternion, mZ));
}

static void ConstructRay(Ray* ptr)
{
    // Initialize to zero because performance is not critical
    new(ptr) Ray(Vector3::sZero, Vector3::sZero);
}

static void ConstructRayCopy(const Ray& ray, Ray* ptr)
{
    new(ptr) Ray(ray);
}

static void ConstructRayInit(const Vector3& origin, const Vector3& direction, Ray* ptr)
{
    // Normalize direction because performance is not critical
    new(ptr) Ray(origin, direction.getNormalized());
}

static void registerRay(asIScriptEngine* engine)
{
    engine->RegisterObjectType("Ray", sizeof(Ray), asOBJ_VALUE | asOBJ_POD | asOBJ_APP_CLASS_CA);
    engine->RegisterObjectBehaviour("Ray", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(ConstructRay), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("Ray", asBEHAVE_CONSTRUCT, "void f(const Ray& in)", asFUNCTION(ConstructRayCopy), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("Ray", asBEHAVE_CONSTRUCT, "void f(const Vector3& in, const Vector3& in)", asFUNCTION(ConstructRayInit), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("Ray", "Ray &opAssign(const Ray& in)", asMETHOD(Ray, operator =), asCALL_THISCALL);
    engine->RegisterObjectMethod("Ray", "bool &opEquals(const Ray& in) const", asMETHOD(Ray, operator ==), asCALL_THISCALL);
    engine->RegisterObjectMethod("Ray", "void define(const Vector3& in, const Vector3& in)", asMETHOD(Ray, define), asCALL_THISCALL);
    engine->RegisterObjectMethod("Ray", "float getDistance(const Vector3& in, const Vector3& in, const Vector3& in) const", asMETHODPR(Ray, getDistance, (const Vector3&, const Vector3&, const Vector3&) const, float), asCALL_THISCALL);
    engine->RegisterObjectProperty("Ray", "Vector3 origin", offsetof(Ray, mOrigin));
    engine->RegisterObjectProperty("Ray", "Vector3 direction", offsetof(Ray, mDirection));
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
        return Vector3::sZero;
    return ptr->mVertices[index];
}

static void registerVolumes(asIScriptEngine* engine)
{
    engine->RegisterEnum("Intersection");
    engine->RegisterEnumValue("Intersection", "OUTSIDE", OUTSIDE);
    engine->RegisterEnumValue("Intersection", "INTERSECTS", INTERSECTS);
    engine->RegisterEnumValue("Intersection", "INSIDE", INSIDE);
    
    engine->RegisterObjectType("BoundingBox", sizeof(BoundingBox), asOBJ_VALUE | asOBJ_POD | asOBJ_APP_CLASS_CA);
    engine->RegisterObjectType("Sphere", sizeof(Sphere), asOBJ_VALUE | asOBJ_POD | asOBJ_APP_CLASS_CA);
    engine->RegisterObjectType("Frustum", sizeof(Frustum), asOBJ_VALUE | asOBJ_APP_CLASS_CDA);
    
    engine->RegisterObjectBehaviour("BoundingBox", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(ConstructBoundingBox), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("BoundingBox", asBEHAVE_CONSTRUCT, "void f(const BoundingBox& in)", asFUNCTION(ConstructBoundingBoxCopy), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("BoundingBox", asBEHAVE_CONSTRUCT, "void f(const Vector3& in, const Vector3& in)", asFUNCTION(ConstructBoundingBoxInit), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("BoundingBox", asBEHAVE_CONSTRUCT, "void f(float, float)", asFUNCTION(ConstructBoundingBoxFloat), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("BoundingBox", "BoundingBox &opAssign(const BoundingBox& in)", asMETHODPR(BoundingBox, operator =, (const BoundingBox&), BoundingBox&), asCALL_THISCALL);
    engine->RegisterObjectMethod("BoundingBox", "bool &opEquals(const BoundingBox& in) const", asMETHOD(BoundingBox, operator ==), asCALL_THISCALL);
    engine->RegisterObjectMethod("BoundingBox", "void define(const Vector3& in, const Vector3& in)", asMETHODPR(BoundingBox, define, (const Vector3&, const Vector3&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("BoundingBox", "void define(float, float)", asMETHODPR(BoundingBox, define, (float, float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("BoundingBox", "void define(const Frustum& in)", asMETHODPR(BoundingBox, define, (const Frustum&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("BoundingBox", "void define(const Sphere& in)", asMETHODPR(BoundingBox, define, (const Sphere&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("BoundingBox", "void merge(const Vector3& in)", asMETHODPR(BoundingBox, merge, (const Vector3&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("BoundingBox", "void merge(const BoundingBox& in)", asMETHODPR(BoundingBox, merge, (const BoundingBox&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("BoundingBox", "void merge(const Frustum& in)", asMETHODPR(BoundingBox, merge, (const Frustum&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("BoundingBox", "void merge(const Sphere& in)", asMETHODPR(BoundingBox, merge, (const Sphere&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("BoundingBox", "void intersect(const BoundingBox& in)", asMETHODPR(BoundingBox, intersect, (const BoundingBox&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("BoundingBox", "Vector3 getCenter() const", asMETHOD(BoundingBox, getCenter), asCALL_THISCALL);
    engine->RegisterObjectMethod("BoundingBox", "Vector3 getSize() const", asMETHOD(BoundingBox, getSize), asCALL_THISCALL);
    engine->RegisterObjectMethod("BoundingBox", "Vector3 getHalfSize() const", asMETHOD(BoundingBox, getHalfSize), asCALL_THISCALL);
    engine->RegisterObjectMethod("BoundingBox", "Intersection isInside(const Vector3& in) const", asMETHODPR(BoundingBox, isInside, (const Vector3&) const, Intersection), asCALL_THISCALL);
    engine->RegisterObjectMethod("BoundingBox", "Intersection isInside(const Sphere& in) const", asMETHODPR(BoundingBox, isInside, (const Sphere&) const, Intersection), asCALL_THISCALL);
    engine->RegisterObjectMethod("BoundingBox", "Intersection isInside(const BoundingBox& in) const", asMETHODPR(BoundingBox, isInside, (const BoundingBox&) const, Intersection), asCALL_THISCALL);
    engine->RegisterObjectMethod("BoundingBox", "float getDistance(const Ray& in) const", asMETHOD(BoundingBox, getDistance), asCALL_THISCALL);
    engine->RegisterObjectProperty("BoundingBox", "Vector3 min", offsetof(BoundingBox, mMin));
    engine->RegisterObjectProperty("BoundingBox", "Vector3 max", offsetof(BoundingBox, mMax));
    engine->RegisterObjectProperty("BoundingBox", "bool defined", offsetof(BoundingBox, mDefined));
    
    engine->RegisterObjectBehaviour("Sphere", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(ConstructSphere), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("Sphere", asBEHAVE_CONSTRUCT, "void f(const Sphere& in)", asFUNCTION(ConstructSphereCopy), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("Sphere", asBEHAVE_CONSTRUCT, "void f(const Vector3& in, float)", asFUNCTION(ConstructSphereInit), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("Sphere", "Sphere &opAssign(const Sphere& in)", asMETHODPR(Sphere, operator =, (const Sphere&), Sphere&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Sphere", "bool &opEquals(const Sphere& in) const", asMETHOD(Sphere, operator ==), asCALL_THISCALL);
    engine->RegisterObjectMethod("Sphere", "void define(const Vector3& in, float)", asMETHODPR(Sphere, define, (const Vector3&, float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Sphere", "void define(const BoundingBox& in)", asMETHODPR(Sphere, define, (const BoundingBox&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Sphere", "void define(const Frustum& in)", asMETHODPR(Sphere, define, (const Frustum&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Sphere", "void merge(const Vector3& in)", asMETHODPR(Sphere, merge, (const Vector3&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Sphere", "void merge(const BoundingBox& in)", asMETHODPR(Sphere, merge, (const BoundingBox&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Sphere", "void merge(const Frustum& in)", asMETHODPR(Sphere, merge, (const Frustum&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Sphere", "void merge(const Sphere& in)", asMETHODPR(Sphere, merge, (const Sphere&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Sphere", "Intersection isInside(const Vector3& in) const", asMETHODPR(Sphere, isInside, (const Vector3&) const, Intersection), asCALL_THISCALL);
    engine->RegisterObjectMethod("Sphere", "Intersection isInside(const Sphere& in) const", asMETHODPR(Sphere, isInside, (const Sphere&) const, Intersection), asCALL_THISCALL);
    engine->RegisterObjectMethod("Sphere", "Intersection isInside(const BoundingBox& in) const", asMETHODPR(Sphere, isInside, (const BoundingBox&) const, Intersection), asCALL_THISCALL);
    engine->RegisterObjectMethod("Sphere", "float getDistance(const Ray& in) const", asMETHOD(Sphere, getDistance), asCALL_THISCALL);
    engine->RegisterObjectProperty("Sphere", "Vector3 center", offsetof(Sphere, mCenter));
    engine->RegisterObjectProperty("Sphere", "float radius", offsetof(Sphere, mRadius));
    engine->RegisterObjectProperty("Sphere", "bool defined", offsetof(Sphere, mDefined));
    
    engine->RegisterObjectBehaviour("Frustum", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(ConstructFrustum), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("Frustum", asBEHAVE_CONSTRUCT, "void f(const Frustum& in)", asFUNCTION(ConstructFrustumCopy), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("Frustum", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(DestructFrustum), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("Frustum", "string &opAssign(const Frustum& in)", asMETHODPR(Frustum, operator =, (const Frustum&), Frustum&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Frustum", "Intersection isInside(const Vector3& in)", asMETHODPR(Frustum, isInside, (const Vector3&) const, Intersection), asCALL_THISCALL);
    engine->RegisterObjectMethod("Frustum", "Intersection isInside(const BoundingBox& in)", asMETHODPR(Frustum, isInside, (const BoundingBox&) const, Intersection), asCALL_THISCALL);
    engine->RegisterObjectMethod("Frustum", "Intersection isInside(const Sphere& in)", asMETHODPR(Frustum, isInside, (const Sphere&) const, Intersection), asCALL_THISCALL);
    engine->RegisterObjectProperty("Frustum", "bool defined", offsetof(Frustum, mDefined));
    engine->RegisterObjectMethod("Frustum", "Vector3 get_vertices(uint)", asFUNCTION(FrustumGetVertex), asCALL_CDECL_OBJLAST);
}

void registerMathLibrary(asIScriptEngine* engine)
{
    registerMathFunctions(engine);
    registerIntRect(engine);
    registerIntVector2(engine);
    registerVector2(engine);
    registerVector3(engine);
    registerVector4(engine);
    registerQuaternion(engine);
    registerRay(engine);
    registerVolumes(engine);
}
