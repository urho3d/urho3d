//
// Copyright (c) 2008-2016 the Urho3D project.
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
#include "../Math/Frustum.h"
#include "../Math/Polyhedron.h"
#include "../Math/Ray.h"
#include "../Math/Matrix2.h"

namespace Urho3D
{

static void RegisterMathFunctions(asIScriptEngine* engine)
{
    engine->RegisterEnum("Intersection");
    engine->RegisterEnumValue("Intersection", "OUTSIDE", OUTSIDE);
    engine->RegisterEnumValue("Intersection", "INTERSECTS", INTERSECTS);
    engine->RegisterEnumValue("Intersection", "INSIDE", INSIDE);

    engine->RegisterGlobalProperty("const float M_INFINITY", (void*)&M_INFINITY);
    engine->RegisterGlobalProperty("const float M_EPSILON", (void*)&M_EPSILON);
    engine->RegisterGlobalProperty("const float M_LARGE_EPSILON", (void*)&M_LARGE_EPSILON);
    engine->RegisterGlobalProperty("const float M_LARGE_VALUE", (void*)&M_LARGE_VALUE);
    engine->RegisterGlobalProperty("const float M_DEGTORAD", (void*)&M_DEGTORAD);
    engine->RegisterGlobalProperty("const float M_DEGTORAD_2", (void*)&M_DEGTORAD_2);
    engine->RegisterGlobalProperty("const float M_RADTODEG", (void*)&M_RADTODEG);
    engine->RegisterGlobalProperty("const float M_PI", (void*)&M_PI);
    engine->RegisterGlobalProperty("const float M_HALF_PI", (void*)&M_HALF_PI);
    engine->RegisterGlobalProperty("const int M_MIN_INT", (void*)&M_MIN_INT);
    engine->RegisterGlobalProperty("const int M_MAX_INT", (void*)&M_MAX_INT);
    engine->RegisterGlobalProperty("const uint M_MIN_UNSIGNED", (void*)&M_MIN_UNSIGNED);
    engine->RegisterGlobalProperty("const uint M_MAX_UNSIGNED", (void*)&M_MAX_UNSIGNED);

    engine->RegisterGlobalFunction("bool Equals(float, float)", asFUNCTION(Equals<float>), asCALL_CDECL);
    engine->RegisterGlobalFunction("bool IsNaN(float)", asFUNCTION(IsNaN), asCALL_CDECL);
    engine->RegisterGlobalFunction("float Sin(float)", asFUNCTION(Sin<float>), asCALL_CDECL);
    engine->RegisterGlobalFunction("float Cos(float)", asFUNCTION(Cos<float>), asCALL_CDECL);
    engine->RegisterGlobalFunction("float Tan(float)", asFUNCTION(Tan<float>), asCALL_CDECL);
    engine->RegisterGlobalFunction("float Asin(float)", asFUNCTION(Asin<float>), asCALL_CDECL);
    engine->RegisterGlobalFunction("float Acos(float)", asFUNCTION(Acos<float>), asCALL_CDECL);
    engine->RegisterGlobalFunction("float Atan(float)", asFUNCTION(Atan<float>), asCALL_CDECL);
    engine->RegisterGlobalFunction("float Atan2(float, float)", asFUNCTION(Atan2<float>), asCALL_CDECL);
    engine->RegisterGlobalFunction("float Abs(float)", asFUNCTIONPR(Abs, (float), float), asCALL_CDECL);
    engine->RegisterGlobalFunction("float Sign(float)", asFUNCTION(Sign<float>), asCALL_CDECL);
    engine->RegisterGlobalFunction("float Sqrt(float)", asFUNCTION(sqrtf), asCALL_CDECL);
    engine->RegisterGlobalFunction("float Pow(float, float)", asFUNCTION(powf), asCALL_CDECL);
    engine->RegisterGlobalFunction("float Min(float, float)", asFUNCTIONPR(Min, (float, float), float), asCALL_CDECL);
    engine->RegisterGlobalFunction("int Min(int, int)", asFUNCTIONPR(Min, (int, int), int), asCALL_CDECL);
    engine->RegisterGlobalFunction("float Max(float, float)", asFUNCTIONPR(Max, (float, float), float), asCALL_CDECL);
    engine->RegisterGlobalFunction("int Max(int, int)", asFUNCTIONPR(Max, (int, int), int), asCALL_CDECL);
    engine->RegisterGlobalFunction("float Clamp(float, float, float)", asFUNCTIONPR(Clamp, (float, float, float), float), asCALL_CDECL);
    engine->RegisterGlobalFunction("float SmoothStep(float, float, float)", asFUNCTION(SmoothStep<float>), asCALL_CDECL);
    engine->RegisterGlobalFunction("int Clamp(int, int, int)", asFUNCTIONPR(Clamp, (int, int, int), int), asCALL_CDECL);
    engine->RegisterGlobalFunction("float Lerp(float, float, float)", asFUNCTIONPR(Lerp, (float, float, float), float), asCALL_CDECL);
    engine->RegisterGlobalFunction("float Mod(float, float)", asFUNCTION(fmodf), asCALL_CDECL);
    engine->RegisterGlobalFunction("float Floor(float)", asFUNCTION(floorf), asCALL_CDECL);
    engine->RegisterGlobalFunction("float Ceil(float)", asFUNCTION(ceilf), asCALL_CDECL);
    engine->RegisterGlobalFunction("bool IsPowerOfTwo(uint)", asFUNCTION(IsPowerOfTwo), asCALL_CDECL);
    engine->RegisterGlobalFunction("uint NextPowerOfTwo(uint)", asFUNCTION(NextPowerOfTwo), asCALL_CDECL);
    engine->RegisterGlobalFunction("uint CountSetBits(uint)", asFUNCTION(CountSetBits), asCALL_CDECL);
    engine->RegisterGlobalFunction("uint SDBMHash(uint, uint8)", asFUNCTION(SDBMHash), asCALL_CDECL);
    engine->RegisterGlobalFunction("float Random()", asFUNCTIONPR(Random, (), float), asCALL_CDECL);
    engine->RegisterGlobalFunction("float Random(float)", asFUNCTIONPR(Random, (float), float), asCALL_CDECL);
    engine->RegisterGlobalFunction("float Random(float, float)", asFUNCTIONPR(Random, (float, float), float), asCALL_CDECL);
    engine->RegisterGlobalFunction("int RandomInt()", asFUNCTION(Rand), asCALL_CDECL);
    engine->RegisterGlobalFunction("int RandomInt(int)", asFUNCTIONPR(Random, (int), int), asCALL_CDECL);
    engine->RegisterGlobalFunction("int RandomInt(int, int)", asFUNCTIONPR(Random, (int, int), int), asCALL_CDECL);
    engine->RegisterGlobalFunction("float RandomNormal(float, float)", asFUNCTIONPR(RandomNormal, (float, float), float), asCALL_CDECL);
    engine->RegisterGlobalFunction("void SetRandomSeed(uint)", asFUNCTION(SetRandomSeed), asCALL_CDECL);
    engine->RegisterGlobalFunction("uint GetRandomSeed()", asFUNCTION(GetRandomSeed), asCALL_CDECL);
}

static void ConstructIntRect(IntRect* ptr)
{
    new(ptr) IntRect();
}

static void ConstructIntRectCopy(const IntRect& rect, IntRect* ptr)
{
    new(ptr) IntRect(rect);
}

static void ConstructIntRectInit(int left, int top, int right, int bottom, IntRect* ptr)
{
    new(ptr) IntRect(left, top, right, bottom);
}

static void ConstructIntRectArrayInit(CScriptArray* data, IntRect* ptr)
{
    new(ptr) IntRect((static_cast<int*>(data->At(0))));
}

static CScriptArray* IntRectData(IntRect* ptr)
{
    return BufferToArray<int>(ptr->Data(), 4, "int[]");
}

static void RegisterIntRect(asIScriptEngine* engine)
{
    engine->RegisterObjectType("IntRect", sizeof(IntRect), asOBJ_VALUE | asOBJ_POD | asOBJ_APP_CLASS_CAK);
    engine->RegisterObjectBehaviour("IntRect", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(ConstructIntRect), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("IntRect", asBEHAVE_CONSTRUCT, "void f(const IntRect&in)", asFUNCTION(ConstructIntRectCopy), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("IntRect", asBEHAVE_CONSTRUCT, "void f(int, int, int, int)", asFUNCTION(ConstructIntRectInit), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("IntRect", asBEHAVE_CONSTRUCT, "void f(int[]&)", asFUNCTION(ConstructIntRectArrayInit), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("IntRect", "Intersection IsInside(const IntVector2&in) const", asMETHOD(IntRect, IsInside), asCALL_THISCALL);
    engine->RegisterObjectMethod("IntRect", "int[]& get_data() const", asFUNCTION(IntRectData), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("IntRect", "IntRect& opAssign(const IntRect&in)", asMETHODPR(IntRect, operator =, (const IntRect&), IntRect&), asCALL_THISCALL);
    engine->RegisterObjectMethod("IntRect", "bool opEquals(const IntRect&in) const", asMETHOD(IntRect, operator ==), asCALL_THISCALL);
    engine->RegisterObjectMethod("IntRect", "IntVector2 get_size() const", asMETHOD(IntRect, Size), asCALL_THISCALL);
    engine->RegisterObjectMethod("IntRect", "int get_width() const", asMETHOD(IntRect, Width), asCALL_THISCALL);
    engine->RegisterObjectMethod("IntRect", "int get_height() const", asMETHOD(IntRect, Height), asCALL_THISCALL);
    engine->RegisterObjectProperty("IntRect", "int left", offsetof(IntRect, left_));
    engine->RegisterObjectProperty("IntRect", "int top", offsetof(IntRect, top_));
    engine->RegisterObjectProperty("IntRect", "int right", offsetof(IntRect, right_));
    engine->RegisterObjectProperty("IntRect", "int bottom", offsetof(IntRect, bottom_));
}

static void ConstructIntVector2(IntVector2* ptr)
{
    new(ptr) IntVector2();
}

static void ConstructIntVector2Copy(const IntVector2& vector, IntVector2* ptr)
{
    new(ptr) IntVector2(vector);
}

static void ConstructIntVector2Init(int x, int y, IntVector2* ptr)
{
    new(ptr) IntVector2(x, y);
}

static void ConstructIntVector2ArrayInit(CScriptArray* data, IntVector2* ptr)
{
    new(ptr) IntVector2((static_cast<int*>(data->At(0))));
}

static CScriptArray* IntVector2Data(IntVector2* ptr)
{
    return BufferToArray<int>(ptr->Data(), 2, "int[]");
}

static void RegisterIntVector2(asIScriptEngine* engine)
{
    engine->RegisterObjectType("IntVector2", sizeof(IntVector2), asOBJ_VALUE | asOBJ_POD | asOBJ_APP_CLASS_CAK);
    engine->RegisterObjectBehaviour("IntVector2", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(ConstructIntVector2), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("IntVector2", asBEHAVE_CONSTRUCT, "void f(const IntVector2&in)", asFUNCTION(ConstructIntVector2Copy), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("IntVector2", asBEHAVE_CONSTRUCT, "void f(int, int)", asFUNCTION(ConstructIntVector2Init), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("IntVector2", asBEHAVE_CONSTRUCT, "void f(int[]&)", asFUNCTION(ConstructIntVector2ArrayInit), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("IntVector2", "int[]& get_data() const", asFUNCTION(IntVector2Data), asCALL_CDECL_OBJLAST);
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
    new(ptr) Vector2();
}

static void ConstructVector2Copy(const Vector2& vector, Vector2* ptr)
{
    new(ptr) Vector2(vector);
}

static void ConstructVector2Init(float x, float y, Vector2* ptr)
{
    new(ptr) Vector2(x, y);
}

static void ConstructVector2ArrayInit(CScriptArray* data, Vector2* ptr)
{
    new(ptr) Vector2((static_cast<float*>(data->At(0))));
}

static CScriptArray* Vector2Data(Vector2* ptr)
{
    return BufferToArray<float>(ptr->Data(), 2, "float[]");
}

static void RegisterVector2(asIScriptEngine* engine)
{
    engine->RegisterObjectType("Vector2", sizeof(Vector2), asOBJ_VALUE | asOBJ_POD | asOBJ_APP_CLASS_CAK);
    engine->RegisterObjectBehaviour("Vector2", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(ConstructVector2), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("Vector2", asBEHAVE_CONSTRUCT, "void f(const Vector2&in)", asFUNCTION(ConstructVector2Copy), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("Vector2", asBEHAVE_CONSTRUCT, "void f(float, float)", asFUNCTION(ConstructVector2Init), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("Vector2", asBEHAVE_CONSTRUCT, "void f(float[]&)", asFUNCTION(ConstructVector2ArrayInit), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("Vector2", "float[]& get_data() const", asFUNCTION(Vector2Data), asCALL_CDECL_OBJLAST);
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
    engine->RegisterObjectMethod("Vector2", "void Normalize()", asMETHOD(Vector2, Normalize), asCALL_THISCALL);
    engine->RegisterObjectMethod("Vector2", "float DotProduct(const Vector2&in) const", asMETHOD(Vector2, DotProduct), asCALL_THISCALL);
    engine->RegisterObjectMethod("Vector2", "float AbsDotProduct(const Vector2&in) const", asMETHOD(Vector2, AbsDotProduct), asCALL_THISCALL);
    engine->RegisterObjectMethod("Vector2", "float Angle(const Vector2&in) const", asMETHOD(Vector2, Angle), asCALL_THISCALL);
    engine->RegisterObjectMethod("Vector2", "Vector2 Abs() const", asMETHOD(Vector2, Abs), asCALL_THISCALL);
    engine->RegisterObjectMethod("Vector2", "Vector2 Lerp(const Vector2&in, float) const", asMETHOD(Vector2, Lerp), asCALL_THISCALL);
    engine->RegisterObjectMethod("Vector2", "bool Equals(const Vector2&in) const", asMETHOD(Vector2, Equals), asCALL_THISCALL);
    engine->RegisterObjectMethod("Vector2", "bool IsNaN() const", asMETHOD(Vector2, IsNaN), asCALL_THISCALL);
    engine->RegisterObjectMethod("Vector2", "Vector2 Normalized() const", asMETHOD(Vector2, Normalized), asCALL_THISCALL);
    engine->RegisterObjectMethod("Vector2", "String ToString() const", asMETHOD(Vector2, ToString), asCALL_THISCALL);
    engine->RegisterObjectMethod("Vector2", "float get_length() const", asMETHOD(Vector2, Length), asCALL_THISCALL);
    engine->RegisterObjectMethod("Vector2", "float get_lengthSquared() const", asMETHOD(Vector2, LengthSquared), asCALL_THISCALL);
    engine->RegisterObjectProperty("Vector2", "float x", offsetof(Vector2, x_));
    engine->RegisterObjectProperty("Vector2", "float y", offsetof(Vector2, y_));
}

static void ConstructVector3(Vector3* ptr)
{
    new(ptr) Vector3();
}

static void ConstructVector3Copy(const Vector3& vector, Vector3* ptr)
{
    new(ptr) Vector3(vector);
}

static void ConstructVector3Vector2Z(const Vector2& vector, float z, Vector3* ptr)
{
    new(ptr) Vector3(vector, z);
}

static void ConstructVector3Vector2(const Vector2& vector, Vector3* ptr)
{
    new(ptr) Vector3(vector);
}

static void ConstructVector3XYZ(float x, float y, float z, Vector3* ptr)
{
    new(ptr) Vector3(x, y, z);
}

static void ConstructVector3XY(float x, float y, Vector3* ptr)
{
    new(ptr) Vector3(x, y);
}

static void ConstructVector3ArrayInit(CScriptArray* data, Vector3* ptr)
{
    new(ptr) Vector3((static_cast<float*>(data->At(0))));
}

static CScriptArray* Vector3Data(Vector3* ptr)
{
    return BufferToArray<float>(ptr->Data(), 3, "float[]");
}

static void RegisterVector3(asIScriptEngine* engine)
{
    engine->RegisterObjectType("Vector3", sizeof(Vector3), asOBJ_VALUE | asOBJ_POD | asOBJ_APP_CLASS_CAK);
    engine->RegisterObjectBehaviour("Vector3", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(ConstructVector3), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("Vector3", asBEHAVE_CONSTRUCT, "void f(const Vector3&in)", asFUNCTION(ConstructVector3Copy), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("Vector3", asBEHAVE_CONSTRUCT, "void f(const Vector2&in, float)", asFUNCTION(ConstructVector3Vector2Z), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("Vector3", asBEHAVE_CONSTRUCT, "void f(const Vector2&in)", asFUNCTION(ConstructVector3Vector2), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("Vector3", asBEHAVE_CONSTRUCT, "void f(float, float, float)", asFUNCTION(ConstructVector3XYZ), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("Vector3", asBEHAVE_CONSTRUCT, "void f(float, float)", asFUNCTION(ConstructVector3XY), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("Vector3", asBEHAVE_CONSTRUCT, "void f(float[]&)", asFUNCTION(ConstructVector3ArrayInit), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("Vector3", "float[]& get_data() const", asFUNCTION(Vector3Data), asCALL_CDECL_OBJLAST);
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
    engine->RegisterObjectMethod("Vector3", "void Normalize()", asMETHOD(Vector3, Normalize), asCALL_THISCALL);
    engine->RegisterObjectMethod("Vector3", "float DotProduct(const Vector3&in) const", asMETHOD(Vector3, DotProduct), asCALL_THISCALL);
    engine->RegisterObjectMethod("Vector3", "float AbsDotProduct(const Vector3&in) const", asMETHOD(Vector3, AbsDotProduct), asCALL_THISCALL);
    engine->RegisterObjectMethod("Vector3", "Vector3 CrossProduct(const Vector3&in) const", asMETHOD(Vector3, CrossProduct), asCALL_THISCALL);
    engine->RegisterObjectMethod("Vector3", "Vector3 Abs() const", asMETHOD(Vector3, Abs), asCALL_THISCALL);
    engine->RegisterObjectMethod("Vector3", "Vector3 Lerp(const Vector3&in, float) const", asMETHOD(Vector3, Lerp), asCALL_THISCALL);
    engine->RegisterObjectMethod("Vector3", "bool Equals(const Vector3&in) const", asMETHOD(Vector3, Equals), asCALL_THISCALL);
    engine->RegisterObjectMethod("Vector3", "bool IsNaN() const", asMETHOD(Vector3, IsNaN), asCALL_THISCALL);
    engine->RegisterObjectMethod("Vector3", "float Angle(const Vector3&in) const", asMETHOD(Vector3, Angle), asCALL_THISCALL);
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
    new(ptr) Vector4();
}

static void ConstructVector4Copy(const Vector4& vector, Vector4* ptr)
{
    new(ptr) Vector4(vector);
}

static void ConstructVector4Init(float x, float y, float z, float w, Vector4* ptr)
{
    new(ptr) Vector4(x, y, z, w);
}

static void ConstructVector4InitVector3(const Vector3& vector, float w, Vector4* ptr)
{
    new(ptr) Vector4(vector, w);
}

static void ConstructVector4ArrayInit(CScriptArray* data, Vector4* ptr)
{
    new(ptr) Vector4((static_cast<float*>(data->At(0))));
}

static CScriptArray* Vector4Data(Vector4* ptr)
{
    return BufferToArray<float>(ptr->Data(), 4, "float[]");
}

static void RegisterVector4(asIScriptEngine* engine)
{
    engine->RegisterObjectType("Vector4", sizeof(Vector4), asOBJ_VALUE | asOBJ_POD | asOBJ_APP_CLASS_CAK);
    engine->RegisterObjectBehaviour("Vector4", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(ConstructVector4), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("Vector4", asBEHAVE_CONSTRUCT, "void f(const Vector4&in)", asFUNCTION(ConstructVector4Copy), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("Vector4", asBEHAVE_CONSTRUCT, "void f(float, float, float, float)", asFUNCTION(ConstructVector4Init), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("Vector4", asBEHAVE_CONSTRUCT, "void f(const Vector3&in, float)", asFUNCTION(ConstructVector4InitVector3), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("Vector4", asBEHAVE_CONSTRUCT, "void f(float[]&)", asFUNCTION(ConstructVector4ArrayInit), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("Vector4", "float[]& get_data() const", asFUNCTION(Vector4Data), asCALL_CDECL_OBJLAST);
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
    engine->RegisterObjectMethod("Vector4", "Vector4 Abs() const", asMETHOD(Vector4, Abs), asCALL_THISCALL);
    engine->RegisterObjectMethod("Vector4", "Vector4 Lerp(const Vector4&in, float) const", asMETHOD(Vector4, Lerp), asCALL_THISCALL);
    engine->RegisterObjectMethod("Vector4", "bool Equals(const Vector4&in) const", asMETHOD(Vector4, Equals), asCALL_THISCALL);
    engine->RegisterObjectMethod("Vector4", "bool IsNaN() const", asMETHOD(Vector4, IsNaN), asCALL_THISCALL);
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

static void ConstructQuaternionAngle(float angle, Quaternion* ptr)
{
    new(ptr) Quaternion(angle);
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

static void ConstructQuaternionAxes(const Vector3& xAxis, const Vector3& yAxis, const Vector3& zAxis, Quaternion* ptr)
{
    new(ptr) Quaternion(xAxis, yAxis, zAxis);
}

static void ConstructQuaternionMatrix(const Matrix3& matrix, Quaternion* ptr)
{
    new(ptr) Quaternion(matrix);
}

static void RegisterQuaternion(asIScriptEngine* engine)
{
    engine->RegisterObjectType("Quaternion", sizeof(Quaternion), asOBJ_VALUE | asOBJ_POD | asOBJ_APP_CLASS_CAK);
    engine->RegisterObjectBehaviour("Quaternion", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(ConstructQuaternion), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("Quaternion", asBEHAVE_CONSTRUCT, "void f(const Quaternion&in)", asFUNCTION(ConstructQuaternionCopy), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("Quaternion", asBEHAVE_CONSTRUCT, "void f(float, float, float, float)", asFUNCTION(ConstructQuaternionInit), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("Quaternion", asBEHAVE_CONSTRUCT, "void f(float, const Vector3&in)", asFUNCTION(ConstructQuaternionAngleAxis), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("Quaternion", asBEHAVE_CONSTRUCT, "void f(float)", asFUNCTION(ConstructQuaternionAngle), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("Quaternion", asBEHAVE_CONSTRUCT, "void f(float, float, float)", asFUNCTION(ConstructQuaternionEuler), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("Quaternion", asBEHAVE_CONSTRUCT, "void f(const Vector3&in)", asFUNCTION(ConstructQuaternionEulerVector), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("Quaternion", asBEHAVE_CONSTRUCT, "void f(const Vector3&in, const Vector3&in)", asFUNCTION(ConstructQuaternionRotation), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("Quaternion", asBEHAVE_CONSTRUCT, "void f(const Vector3&in, const Vector3&in, const Vector3&in)", asFUNCTION(ConstructQuaternionAxes), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("Quaternion", asBEHAVE_CONSTRUCT, "void f(const Matrix3&in)", asFUNCTION(ConstructQuaternionMatrix), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("Quaternion", "Quaternion& opAssign(const Quaternion&in)", asMETHOD(Quaternion, operator =), asCALL_THISCALL);
    engine->RegisterObjectMethod("Quaternion", "Quaternion& opAddAssign(const Quaternion&in)", asMETHOD(Quaternion, operator +=), asCALL_THISCALL);
    engine->RegisterObjectMethod("Quaternion", "bool opEquals(const Quaternion&in) const", asMETHOD(Quaternion, operator ==), asCALL_THISCALL);
    engine->RegisterObjectMethod("Quaternion", "Quaternion opMul(float) const", asMETHODPR(Quaternion, operator *, (float) const, Quaternion), asCALL_THISCALL);
    engine->RegisterObjectMethod("Quaternion", "Vector3 opMul(const Vector3&in) const", asMETHODPR(Quaternion, operator *, (const Vector3&) const, Vector3), asCALL_THISCALL);
    engine->RegisterObjectMethod("Quaternion", "Quaternion opNeg() const", asMETHODPR(Quaternion, operator -, () const, Quaternion), asCALL_THISCALL);
    engine->RegisterObjectMethod("Quaternion", "Quaternion opAdd(const Quaternion&in) const", asMETHOD(Quaternion, operator +), asCALL_THISCALL);
    engine->RegisterObjectMethod("Quaternion", "Quaternion opSub(const Quaternion&in) const", asMETHODPR(Quaternion, operator +, (const Quaternion&) const, Quaternion), asCALL_THISCALL);
    engine->RegisterObjectMethod("Quaternion", "Quaternion opMul(const Quaternion&in) const", asMETHODPR(Quaternion, operator *, (const Quaternion&) const, Quaternion), asCALL_THISCALL);
    engine->RegisterObjectMethod("Quaternion", "void FromAngleAxis(float, const Vector3&in)", asMETHOD(Quaternion, FromAngleAxis), asCALL_THISCALL);
    engine->RegisterObjectMethod("Quaternion", "void FromEulerAngles(float, float, float)", asMETHOD(Quaternion, FromEulerAngles), asCALL_THISCALL);
    engine->RegisterObjectMethod("Quaternion", "void FromRotationTo(const Vector3&in, const Vector3&in)", asMETHOD(Quaternion, FromRotationTo), asCALL_THISCALL);
    engine->RegisterObjectMethod("Quaternion", "void FromAxes(const Vector3&in, const Vector3&in, const Vector3&in)", asMETHOD(Quaternion, FromAxes), asCALL_THISCALL);
    engine->RegisterObjectMethod("Quaternion", "void FromRotationMatrix(const Matrix3&in)", asMETHOD(Quaternion, FromRotationMatrix), asCALL_THISCALL);
    engine->RegisterObjectMethod("Quaternion", "bool FromLookRotation(const Vector3&in, const Vector3&in up = Vector3(0.0, 1.0, 0.0))", asMETHOD(Quaternion, FromLookRotation), asCALL_THISCALL);
    engine->RegisterObjectMethod("Quaternion", "void Normalize()", asMETHOD(Quaternion, Normalize), asCALL_THISCALL);
    engine->RegisterObjectMethod("Quaternion", "Quaternion Normalized() const", asMETHOD(Quaternion, Normalized), asCALL_THISCALL);
    engine->RegisterObjectMethod("Quaternion", "Quaternion Inverse() const", asMETHOD(Quaternion, Inverse), asCALL_THISCALL);
    engine->RegisterObjectMethod("Quaternion", "float LengthSquared() const", asMETHOD(Quaternion, LengthSquared), asCALL_THISCALL);
    engine->RegisterObjectMethod("Quaternion", "float DotProduct(const Quaternion&in) const", asMETHOD(Quaternion, DotProduct), asCALL_THISCALL);
    engine->RegisterObjectMethod("Quaternion", "bool Equals(const Quaternion&in) const", asMETHOD(Quaternion, Equals), asCALL_THISCALL);
    engine->RegisterObjectMethod("Quaternion", "bool IsNaN() const", asMETHOD(Quaternion, IsNaN), asCALL_THISCALL);
    engine->RegisterObjectMethod("Quaternion", "Quaternion Conjugate() const", asMETHOD(Quaternion, Conjugate), asCALL_THISCALL);
    engine->RegisterObjectMethod("Quaternion", "Vector3 get_eulerAngles() const", asMETHOD(Quaternion, EulerAngles), asCALL_THISCALL);
    engine->RegisterObjectMethod("Quaternion", "float get_yaw() const", asMETHOD(Quaternion, YawAngle), asCALL_THISCALL);
    engine->RegisterObjectMethod("Quaternion", "float get_pitch() const", asMETHOD(Quaternion, PitchAngle), asCALL_THISCALL);
    engine->RegisterObjectMethod("Quaternion", "float get_roll() const", asMETHOD(Quaternion, RollAngle), asCALL_THISCALL);
    engine->RegisterObjectMethod("Quaternion", "Matrix3 get_rotationMatrix() const", asMETHOD(Quaternion, RotationMatrix), asCALL_THISCALL);
    engine->RegisterObjectMethod("Quaternion", "Quaternion Slerp(Quaternion, float) const", asMETHOD(Quaternion, Slerp), asCALL_THISCALL);
    engine->RegisterObjectMethod("Quaternion", "Quaternion Nlerp(Quaternion, float, bool) const", asMETHOD(Quaternion, Nlerp), asCALL_THISCALL);
    engine->RegisterObjectMethod("Quaternion", "String ToString() const", asMETHOD(Quaternion, ToString), asCALL_THISCALL);
    engine->RegisterObjectProperty("Quaternion", "float w", offsetof(Quaternion, w_));
    engine->RegisterObjectProperty("Quaternion", "float x", offsetof(Quaternion, x_));
    engine->RegisterObjectProperty("Quaternion", "float y", offsetof(Quaternion, y_));
    engine->RegisterObjectProperty("Quaternion", "float z", offsetof(Quaternion, z_));
}

static void ConstructMatrix3(Matrix3* ptr)
{
    new(ptr) Matrix3();
}

static void ConstructMatrix3Copy(const Matrix3& mat, Matrix3* ptr)
{
    new(ptr) Matrix3(mat);
}

static void ConstructMatrix3Init(float v00, float v01, float v02, float v10, float v11, float v12, float v20, float v21, float v22, Matrix3* ptr)
{
    new(ptr) Matrix3(v00, v01, v02, v10, v11, v12, v20, v21, v22);
}

static void RegisterMatrix3(asIScriptEngine* engine)
{
    engine->RegisterObjectType("Matrix3", sizeof(Matrix3), asOBJ_VALUE | asOBJ_POD | asOBJ_APP_CLASS_CAK);
    engine->RegisterObjectBehaviour("Matrix3", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(ConstructMatrix3), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("Matrix3", asBEHAVE_CONSTRUCT, "void f(const Matrix3&in)", asFUNCTION(ConstructMatrix3Copy), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("Matrix3", asBEHAVE_CONSTRUCT, "void f(float, float, float, float, float, float, float, float, float)", asFUNCTION(ConstructMatrix3Init), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("Matrix3", "Matrix3 opMul(const Matrix3&in) const", asMETHODPR(Matrix3, operator *, (const Matrix3&) const, Matrix3), asCALL_THISCALL);
    engine->RegisterObjectMethod("Matrix3", "Matrix3 opMul(float) const", asMETHODPR(Matrix3, operator *, (float) const, Matrix3), asCALL_THISCALL);
    engine->RegisterObjectMethod("Matrix3", "Vector3 opMul(const Vector3&in) const", asMETHODPR(Matrix3, operator *, (const Vector3&) const, Vector3), asCALL_THISCALL);
    engine->RegisterObjectMethod("Matrix3", "Matrix3 opAdd(const Matrix3&in) const", asMETHODPR(Matrix3, operator +, (const Matrix3 &) const, Matrix3), asCALL_THISCALL);
    engine->RegisterObjectMethod("Matrix3", "Matrix3 opSub(const Matrix3&in) const", asMETHODPR(Matrix3, operator -, (const Matrix3 &) const, Matrix3), asCALL_THISCALL);
    engine->RegisterObjectMethod("Matrix3", "Matrix3& opAssign(const Matrix3&in)", asMETHODPR(Matrix3, operator =, (const Matrix3 &), Matrix3&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Matrix3", "bool opEquals(const Matrix3&in) const", asMETHOD(Matrix3, operator ==), asCALL_THISCALL);
    engine->RegisterObjectMethod("Matrix3", "Vector3 Scale() const", asMETHODPR(Matrix3, Scale, () const, Vector3), asCALL_THISCALL);
    engine->RegisterObjectMethod("Matrix3", "Matrix3 Scaled(const Vector3&in) const", asMETHODPR(Matrix3, Scaled, (const Vector3 &) const, Matrix3), asCALL_THISCALL);
    engine->RegisterObjectMethod("Matrix3", "void SetScale(const Vector3&in)", asMETHODPR(Matrix3,SetScale, (const Vector3 &), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Matrix3", "void SetScale(float)", asMETHODPR(Matrix3,SetScale, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Matrix3", "Matrix3 Transpose() const", asMETHODPR(Matrix3, Transpose, () const, Matrix3), asCALL_THISCALL);
    engine->RegisterObjectMethod("Matrix3", "Matrix3 Inverse() const", asMETHODPR(Matrix3, Inverse, () const, Matrix3), asCALL_THISCALL);
    engine->RegisterObjectMethod("Matrix3", "bool Equals(const Matrix3&in) const", asMETHOD(Matrix3, Equals), asCALL_THISCALL);
    engine->RegisterObjectMethod("Matrix3", "String ToString() const", asMETHOD(Matrix3, ToString), asCALL_THISCALL);
    engine->RegisterObjectProperty("Matrix3", "float m00", offsetof(Matrix3, m00_));
    engine->RegisterObjectProperty("Matrix3", "float m01", offsetof(Matrix3, m01_));
    engine->RegisterObjectProperty("Matrix3", "float m02", offsetof(Matrix3, m02_));
    engine->RegisterObjectProperty("Matrix3", "float m10", offsetof(Matrix3, m10_));
    engine->RegisterObjectProperty("Matrix3", "float m11", offsetof(Matrix3, m11_));
    engine->RegisterObjectProperty("Matrix3", "float m12", offsetof(Matrix3, m12_));
    engine->RegisterObjectProperty("Matrix3", "float m20", offsetof(Matrix3, m20_));
    engine->RegisterObjectProperty("Matrix3", "float m21", offsetof(Matrix3, m21_));
    engine->RegisterObjectProperty("Matrix3", "float m22", offsetof(Matrix3, m22_));
}

static void ConstructMatrix2(Matrix2* ptr)
{
    new(ptr) Matrix2();
}

static void ConstructMatrix2Copy(const Matrix2& mat, Matrix2* ptr)
{
    new(ptr) Matrix2(mat);
}

static void ConstructMatrix2Init(float v00, float v01, float v10, float v11, Matrix2* ptr)
{
    new(ptr) Matrix2(v00, v01, v10, v11);
}

static void RegisterMatrix2(asIScriptEngine* engine)
{
    engine->RegisterObjectType("Matrix2", sizeof(Matrix2), asOBJ_VALUE | asOBJ_POD | asOBJ_APP_CLASS_CAK);
    engine->RegisterObjectBehaviour("Matrix2", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(ConstructMatrix2), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("Matrix2", asBEHAVE_CONSTRUCT, "void f(const Matrix2&in)", asFUNCTION(ConstructMatrix2Copy), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("Matrix2", asBEHAVE_CONSTRUCT, "void f(float, float, float, float)", asFUNCTION(ConstructMatrix2Init), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("Matrix2", "Matrix2 opMul(const Matrix2&in) const", asMETHODPR(Matrix2, operator *, (const Matrix2&) const, Matrix2), asCALL_THISCALL);
    engine->RegisterObjectMethod("Matrix2", "Matrix2 opMul(float) const", asMETHODPR(Matrix2, operator *, (float) const, Matrix2), asCALL_THISCALL);
    engine->RegisterObjectMethod("Matrix2", "Vector2 opMul(const Vector2&in) const", asMETHODPR(Matrix2, operator *, (const Vector2&) const, Vector2), asCALL_THISCALL);
    engine->RegisterObjectMethod("Matrix2", "Matrix2 opAdd(const Matrix2&in) const", asMETHODPR(Matrix2, operator +, (const Matrix2 &) const, Matrix2), asCALL_THISCALL);
    engine->RegisterObjectMethod("Matrix2", "Matrix2 opSub(const Matrix2&in) const", asMETHODPR(Matrix2, operator -, (const Matrix2 &) const, Matrix2), asCALL_THISCALL);
    engine->RegisterObjectMethod("Matrix2", "Matrix2& opAssign(const Matrix2&in)", asMETHODPR(Matrix2, operator =, (const Matrix2 &), Matrix2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Matrix2", "bool opEquals(const Matrix2&in) const", asMETHOD(Matrix2, operator ==), asCALL_THISCALL);
    engine->RegisterObjectMethod("Matrix2", "Vector2 Scale() const", asMETHODPR(Matrix2, Scale, () const, Vector2), asCALL_THISCALL);
    engine->RegisterObjectMethod("Matrix2", "Matrix2 Scaled(const Vector2&in) const", asMETHODPR(Matrix2, Scaled, (const Vector2 &) const, Matrix2), asCALL_THISCALL);
    engine->RegisterObjectMethod("Matrix2", "void SetScale(const Vector2&in)", asMETHODPR(Matrix2,SetScale, (const Vector2 &), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Matrix2", "void SetScale(float)", asMETHODPR(Matrix2,SetScale, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Matrix2", "Matrix2 Transpose() const", asMETHODPR(Matrix2, Transpose, () const, Matrix2), asCALL_THISCALL);
    engine->RegisterObjectMethod("Matrix2", "Matrix2 Inverse() const", asMETHODPR(Matrix2, Inverse, () const, Matrix2), asCALL_THISCALL);
    engine->RegisterObjectMethod("Matrix2", "bool Equals(const Matrix2&in) const", asMETHOD(Matrix2, Equals), asCALL_THISCALL);
    engine->RegisterObjectMethod("Matrix2", "String ToString() const", asMETHOD(Matrix2, ToString), asCALL_THISCALL);
    engine->RegisterObjectProperty("Matrix2", "float m00", offsetof(Matrix2, m00_));
    engine->RegisterObjectProperty("Matrix2", "float m01", offsetof(Matrix2, m01_));
    engine->RegisterObjectProperty("Matrix2", "float m10", offsetof(Matrix2, m10_));
    engine->RegisterObjectProperty("Matrix2", "float m11", offsetof(Matrix2, m11_));
}

static void ConstructMatrix4(Matrix4* ptr)
{
    new(ptr) Matrix4();
}

static void ConstructMatrix4Copy(const Matrix4& mat, Matrix4* ptr)
{
    new(ptr) Matrix4(mat);
}

static void ConstructMatrix4CopyMatrix3(const Matrix3& mat, Matrix4* ptr)
{
    new(ptr) Matrix4(mat);
}

static void ConstructMatrix4Init(float v00, float v01, float v02, float v03, float v10, float v11, float v12, float v13, float v20, float v21, float v22, float v23, float v30, float v31, float v32, float v33, Matrix3* ptr)
{
    new(ptr) Matrix4(v00, v01, v02, v03, v10, v11, v12, v13, v20, v21, v22, v23, v30, v31, v32, v33);
}

static void RegisterMatrix4(asIScriptEngine* engine)
{
    engine->RegisterObjectType("Matrix4", sizeof(Matrix4), asOBJ_VALUE | asOBJ_POD | asOBJ_APP_CLASS_CAK);
    engine->RegisterObjectBehaviour("Matrix4", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(ConstructMatrix4), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("Matrix4", asBEHAVE_CONSTRUCT, "void f(const Matrix4&in)", asFUNCTION(ConstructMatrix4Copy), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("Matrix4", asBEHAVE_CONSTRUCT, "void f(const Matrix3&in)", asFUNCTION(ConstructMatrix4CopyMatrix3), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("Matrix4", asBEHAVE_CONSTRUCT, "void f(float, float, float, float, float, float, float, float, float, float, float, float, float, float, float, float)", asFUNCTION(ConstructMatrix4Init), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("Matrix4", "Matrix4 opMul(const Matrix4&) const", asMETHODPR(Matrix4, operator *, (const Matrix4&) const, Matrix4), asCALL_THISCALL);
    engine->RegisterObjectMethod("Matrix4", "Matrix4 opMul(float) const", asMETHODPR(Matrix4, operator *, (float) const, Matrix4), asCALL_THISCALL);
    engine->RegisterObjectMethod("Matrix4", "Vector3 opMul(const Vector3&) const", asMETHODPR(Matrix4, operator *, (const Vector3&) const, Vector3), asCALL_THISCALL);
    engine->RegisterObjectMethod("Matrix4", "Vector4 opMul(const Vector4&) const", asMETHODPR(Matrix4, operator *, (const Vector4&) const, Vector4), asCALL_THISCALL);
    engine->RegisterObjectMethod("Matrix4", "Matrix4 opAdd(const Matrix4&) const", asMETHODPR(Matrix4, operator +, (const Matrix4&) const, Matrix4), asCALL_THISCALL);
    engine->RegisterObjectMethod("Matrix4", "Matrix4 opSub(const Matrix4&) const", asMETHODPR(Matrix4, operator -, (const Matrix4&) const, Matrix4), asCALL_THISCALL);
    engine->RegisterObjectMethod("Matrix4", "Matrix4& opAssign(const Matrix3&)", asMETHODPR(Matrix4, operator =, (const Matrix3&), Matrix4&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Matrix4", "Matrix4& opAssign(const Matrix4&)", asMETHODPR(Matrix4, operator =, (const Matrix4&), Matrix4&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Matrix4", "bool opEquals(const Matrix4&in) const", asMETHOD(Matrix4, operator ==), asCALL_THISCALL);
    engine->RegisterObjectMethod("Matrix4", "Quaternion Rotation() const", asMETHODPR(Matrix4, Rotation, () const, Quaternion), asCALL_THISCALL);
    engine->RegisterObjectMethod("Matrix4", "Matrix3 RotationMatrix() const", asMETHODPR(Matrix4, RotationMatrix, () const, Matrix3), asCALL_THISCALL);
    engine->RegisterObjectMethod("Matrix4", "Vector3 Scale() const", asMETHODPR(Matrix4, Scale, () const, Vector3), asCALL_THISCALL);
    engine->RegisterObjectMethod("Matrix4", "void SetRotation(const Matrix3&in)", asMETHODPR(Matrix4, SetRotation, (const Matrix3&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Matrix4", "void SetScale(const Vector3&in)", asMETHODPR(Matrix4, SetScale, (const Vector3&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Matrix4", "void SetScale(float)", asMETHODPR(Matrix4, SetScale, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Matrix4", "void SetTranslation(const Vector3&in)", asMETHODPR(Matrix4, SetTranslation, (const Vector3&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Matrix4", "Matrix3 ToMatrix3() const", asMETHODPR(Matrix4, ToMatrix3, () const, Matrix3), asCALL_THISCALL);
    engine->RegisterObjectMethod("Matrix4", "Vector3 Translation() const", asMETHODPR(Matrix4, Translation, () const, Vector3), asCALL_THISCALL);
    engine->RegisterObjectMethod("Matrix4", "Matrix4 Transpose() const", asMETHODPR(Matrix4, Transpose, () const, Matrix4), asCALL_THISCALL);
    engine->RegisterObjectMethod("Matrix4", "void Decompose(Vector3&, Quaternion&, Vector3&) const", asMETHODPR(Matrix4,Decompose, (Vector3 &, Quaternion &, Vector3 &) const, void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Matrix4", "Matrix4 Inverse() const", asMETHODPR(Matrix4, Inverse, () const, Matrix4), asCALL_THISCALL);
    engine->RegisterObjectMethod("Matrix4", "bool Equals(const Matrix4&in) const", asMETHOD(Matrix4, Equals), asCALL_THISCALL);
    engine->RegisterObjectMethod("Matrix4", "String ToString() const", asMETHOD(Matrix4, ToString), asCALL_THISCALL);
    engine->RegisterObjectProperty("Matrix4", "float m00", offsetof(Matrix4, m00_));
    engine->RegisterObjectProperty("Matrix4", "float m01", offsetof(Matrix4, m01_));
    engine->RegisterObjectProperty("Matrix4", "float m02", offsetof(Matrix4, m02_));
    engine->RegisterObjectProperty("Matrix4", "float m03", offsetof(Matrix4, m03_));
    engine->RegisterObjectProperty("Matrix4", "float m10", offsetof(Matrix4, m10_));
    engine->RegisterObjectProperty("Matrix4", "float m11", offsetof(Matrix4, m11_));
    engine->RegisterObjectProperty("Matrix4", "float m12", offsetof(Matrix4, m12_));
    engine->RegisterObjectProperty("Matrix4", "float m13", offsetof(Matrix4, m13_));
    engine->RegisterObjectProperty("Matrix4", "float m20", offsetof(Matrix4, m20_));
    engine->RegisterObjectProperty("Matrix4", "float m21", offsetof(Matrix4, m21_));
    engine->RegisterObjectProperty("Matrix4", "float m22", offsetof(Matrix4, m22_));
    engine->RegisterObjectProperty("Matrix4", "float m23", offsetof(Matrix4, m23_));
    engine->RegisterObjectProperty("Matrix4", "float m30", offsetof(Matrix4, m30_));
    engine->RegisterObjectProperty("Matrix4", "float m31", offsetof(Matrix4, m31_));
    engine->RegisterObjectProperty("Matrix4", "float m32", offsetof(Matrix4, m32_));
    engine->RegisterObjectProperty("Matrix4", "float m33", offsetof(Matrix4, m33_));
}

static void ConstructMatrix3x4(Matrix3x4* ptr)
{
    new(ptr) Matrix3x4();
}

static void ConstructMatrix3x4Copy(const Matrix3x4& mat, Matrix3x4* ptr)
{
    new(ptr) Matrix3x4(mat);
}

static void ConstructMatrix3x4CopyMatrix3(const Matrix3& mat, Matrix3x4* ptr)
{
    new(ptr) Matrix3x4(mat);
}

static void ConstructMatrix3x4CopyMatrix4(const Matrix4& mat, Matrix3x4* ptr)
{
    new(ptr) Matrix3x4(mat);
}

static void ConstructMatrix3x4Init(float v00, float v01, float v02, float v03, float v10, float v11, float v12, float v13, float v20, float v21, float v22, float v23, Matrix3* ptr)
{
    new(ptr) Matrix3x4(v00, v01, v02, v03, v10, v11, v12, v13, v20, v21, v22, v23);
}

static void ConstructMatrix3x4InitTransform(const Vector3& pos, const Quaternion& rot, const Vector3& scale, Matrix3x4* ptr)
{
    new(ptr) Matrix3x4(pos, rot, scale);
}

static void ConstructMatrix3x4InitTransformUniform(const Vector3& pos, const Quaternion& rot, float scale, Matrix3x4* ptr)
{
    new(ptr) Matrix3x4(pos, rot, scale);
}

static void RegisterMatrix3x4(asIScriptEngine* engine)
{
    engine->RegisterObjectType("Matrix3x4", sizeof(Matrix3x4), asOBJ_VALUE | asOBJ_POD | asOBJ_APP_CLASS_CAK);
    engine->RegisterObjectBehaviour("Matrix3x4", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(ConstructMatrix3x4), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("Matrix3x4", asBEHAVE_CONSTRUCT, "void f(const Matrix3x4&in)", asFUNCTION(ConstructMatrix3x4Copy), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("Matrix3x4", asBEHAVE_CONSTRUCT, "void f(const Matrix3&in)", asFUNCTION(ConstructMatrix3x4CopyMatrix3), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("Matrix3x4", asBEHAVE_CONSTRUCT, "void f(const Matrix4&in)", asFUNCTION(ConstructMatrix3x4CopyMatrix4), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("Matrix3x4", asBEHAVE_CONSTRUCT, "void f(float, float, float, float, float, float, float, float, float, float, float, float)", asFUNCTION(ConstructMatrix3x4Init), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("Matrix3x4", asBEHAVE_CONSTRUCT, "void f(const Vector3&in, const Quaternion&in, const Vector3&in)", asFUNCTION(ConstructMatrix3x4InitTransform), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("Matrix3x4", asBEHAVE_CONSTRUCT, "void f(const Vector3&in, const Quaternion&in, float)", asFUNCTION(ConstructMatrix3x4InitTransformUniform), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("Matrix3x4", "Matrix3x4 opMul(const Matrix3x4&in) const", asMETHODPR(Matrix3x4, operator *, (const Matrix3x4&) const, Matrix3x4), asCALL_THISCALL);
    engine->RegisterObjectMethod("Matrix3x4", "Matrix3x4 opMul(float) const", asMETHODPR(Matrix3x4, operator *, (float) const, Matrix3x4), asCALL_THISCALL);
    engine->RegisterObjectMethod("Matrix3x4", "Matrix4 opMul(const Matrix4&in) const", asMETHODPR(Matrix3x4, operator *, (const Matrix4&) const, Matrix4), asCALL_THISCALL);
    engine->RegisterObjectMethod("Matrix3x4", "Vector3 opMul(const Vector3&in) const", asMETHODPR(Matrix3x4, operator *, (const Vector3&) const, Vector3), asCALL_THISCALL);
    engine->RegisterObjectMethod("Matrix3x4", "Vector3 opMul(const Vector4&in) const", asMETHODPR(Matrix3x4, operator *, (const Vector4&) const, Vector3), asCALL_THISCALL);
    engine->RegisterObjectMethod("Matrix3x4", "Matrix3x4 opAdd(const Matrix3x4&in) const", asMETHODPR(Matrix3x4, operator +, (const Matrix3x4&) const, Matrix3x4), asCALL_THISCALL);
    engine->RegisterObjectMethod("Matrix3x4", "Matrix3x4 opSub(const Matrix3x4&in) const", asMETHODPR(Matrix3x4, operator -, (const Matrix3x4&) const, Matrix3x4), asCALL_THISCALL);
    engine->RegisterObjectMethod("Matrix3x4", "Matrix3x4& opAssign(const Matrix3&in)", asMETHODPR(Matrix3x4, operator =, (const Matrix3&), Matrix3x4&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Matrix3x4", "Matrix3x4& opAssign(const Matrix3x4&in)", asMETHODPR(Matrix3x4, operator =, (const Matrix3x4&), Matrix3x4&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Matrix3x4", "Matrix3x4& opAssign(const Matrix4&in)", asMETHODPR(Matrix3x4, operator =, (const Matrix4&), Matrix3x4&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Matrix3x4", "bool opEquals(const Matrix3x4&in) const", asMETHOD(Matrix3x4, operator ==), asCALL_THISCALL);
    engine->RegisterObjectMethod("Matrix3x4", "Quaternion Rotation() const", asMETHODPR(Matrix3x4, Rotation, () const, Quaternion), asCALL_THISCALL);
    engine->RegisterObjectMethod("Matrix3x4", "Matrix3 RotationMatrix() const", asMETHODPR(Matrix3x4, RotationMatrix, () const, Matrix3), asCALL_THISCALL);
    engine->RegisterObjectMethod("Matrix3x4", "Vector3 Scale() const", asMETHODPR(Matrix3x4, Scale, () const, Vector3), asCALL_THISCALL);
    engine->RegisterObjectMethod("Matrix3x4", "void SetRotation(const Matrix3&in)", asMETHODPR(Matrix3x4, SetRotation, (const Matrix3&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Matrix3x4", "void SetScale(const Vector3&in)", asMETHODPR(Matrix3x4, SetScale, (const Vector3&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Matrix3x4", "void SetScale(float)", asMETHODPR(Matrix3x4, SetScale, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Matrix3x4", "void SetTranslation(const Vector3&in)", asMETHODPR(Matrix3x4, SetTranslation, (const Vector3&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Matrix3x4", "Matrix3 ToMatrix3() const", asMETHODPR(Matrix3x4, ToMatrix3, () const, Matrix3), asCALL_THISCALL);
    engine->RegisterObjectMethod("Matrix3x4", "Matrix4 ToMatrix4() const", asMETHODPR(Matrix3x4, ToMatrix4, () const, Matrix4), asCALL_THISCALL);
    engine->RegisterObjectMethod("Matrix3x4", "Vector3 Translation() const", asMETHODPR(Matrix3x4, Translation, () const, Vector3), asCALL_THISCALL);
    engine->RegisterObjectMethod("Matrix3x4", "void Decompose(Vector3&, Quaternion&, Vector3&) const", asMETHODPR(Matrix3x4, Decompose, (Vector3&, Quaternion&, Vector3&) const, void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Matrix3x4", "Matrix3x4 Inverse() const", asMETHODPR(Matrix3x4, Inverse, () const, Matrix3x4), asCALL_THISCALL);
    engine->RegisterObjectMethod("Matrix3x4", "bool Equals(const Matrix3x4&in) const", asMETHOD(Matrix3x4, Equals), asCALL_THISCALL);
    engine->RegisterObjectMethod("Matrix3x4", "String ToString() const", asMETHOD(Matrix3x4, ToString), asCALL_THISCALL);
    engine->RegisterObjectProperty("Matrix3x4", "float m00", offsetof(Matrix3x4, m00_));
    engine->RegisterObjectProperty("Matrix3x4", "float m01", offsetof(Matrix3x4, m01_));
    engine->RegisterObjectProperty("Matrix3x4", "float m02", offsetof(Matrix3x4, m02_));
    engine->RegisterObjectProperty("Matrix3x4", "float m03", offsetof(Matrix3x4, m03_));
    engine->RegisterObjectProperty("Matrix3x4", "float m10", offsetof(Matrix3x4, m10_));
    engine->RegisterObjectProperty("Matrix3x4", "float m11", offsetof(Matrix3x4, m11_));
    engine->RegisterObjectProperty("Matrix3x4", "float m12", offsetof(Matrix3x4, m12_));
    engine->RegisterObjectProperty("Matrix3x4", "float m13", offsetof(Matrix3x4, m13_));
    engine->RegisterObjectProperty("Matrix3x4", "float m20", offsetof(Matrix3x4, m20_));
    engine->RegisterObjectProperty("Matrix3x4", "float m21", offsetof(Matrix3x4, m21_));
    engine->RegisterObjectProperty("Matrix3x4", "float m22", offsetof(Matrix3x4, m22_));
    engine->RegisterObjectProperty("Matrix3x4", "float m23", offsetof(Matrix3x4, m23_));

    engine->RegisterObjectMethod("Matrix4", "Matrix4 opMul(const Matrix3x4&) const", asMETHODPR(Matrix4, operator *, (const Matrix3x4&) const, Matrix4), asCALL_THISCALL);
}

static void ConstructPlane(Plane* ptr)
{
    new(ptr) Plane();
}

static void ConstructPlaneCopy(const Plane& plane, Plane* ptr)
{
    new(ptr) Plane(plane);
}

static void ConstructPlaneInitVertices(const Vector3& v0, const Vector3& v1, const Vector3& v2, Plane* ptr)
{
    new(ptr) Plane(v0, v1, v2);
}

static void ConstructPlaneInitNormalPoint(const Vector3& normal, const Vector3& point, Plane* ptr)
{
    new(ptr) Plane(normal, point);
}

static void ConstructPlaneInitVector4(const Vector4& plane, Plane* ptr)
{
    new(ptr) Plane(plane);
}

static void RegisterPlane(asIScriptEngine* engine)
{
    engine->RegisterObjectType("Plane", sizeof(Plane), asOBJ_VALUE | asOBJ_POD | asOBJ_APP_CLASS_CAK);
    engine->RegisterObjectBehaviour("Plane", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(ConstructPlane), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("Plane", asBEHAVE_CONSTRUCT, "void f(const Plane&in)", asFUNCTION(ConstructPlaneCopy), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("Plane", asBEHAVE_CONSTRUCT, "void f(const Vector3&in, const Vector3&in, const Vector3&in)", asFUNCTION(ConstructPlaneInitVertices), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("Plane", asBEHAVE_CONSTRUCT, "void f(const Vector3&in, const Vector3&in)", asFUNCTION(ConstructPlaneInitNormalPoint), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("Plane", asBEHAVE_CONSTRUCT, "void f(const Vector4&in)", asFUNCTION(ConstructPlaneInitVector4), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("Plane", "void Define(const Vector3&in, const Vector3&in, const Vector3&in)", asMETHODPR(Plane, Define, (const Vector3&, const Vector3&, const Vector3&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Plane", "void Define(const Vector3&in, const Vector3&in)", asMETHODPR(Plane, Define, (const Vector3&, const Vector3&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Plane", "void Define(const Vector4&in)", asMETHODPR(Plane, Define, (const Vector4&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Plane", "void Transform(const Matrix3&in)", asMETHODPR(Plane, Transform, (const Matrix3&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Plane", "void Transform(const Matrix3x4&in)", asMETHODPR(Plane, Transform, (const Matrix3x4&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Plane", "void Transform(const Matrix4&in)", asMETHODPR(Plane, Transform, (const Matrix4&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Plane", "Vector3 Project(const Vector3&in) const", asMETHOD(Plane, Project), asCALL_THISCALL);
    engine->RegisterObjectMethod("Plane", "float Distance(const Vector3&in) const", asMETHOD(Plane, Distance), asCALL_THISCALL);
    engine->RegisterObjectMethod("Plane", "Vector3 Reflect(const Vector3&in) const", asMETHOD(Plane, Reflect), asCALL_THISCALL);
    engine->RegisterObjectMethod("Plane", "Plane Transformed(const Matrix3&in) const", asMETHODPR(Plane, Transformed, (const Matrix3&) const, Plane), asCALL_THISCALL);
    engine->RegisterObjectMethod("Plane", "Plane Transformed(const Matrix3x4&in) const", asMETHODPR(Plane, Transformed, (const Matrix3x4&) const, Plane), asCALL_THISCALL);
    engine->RegisterObjectMethod("Plane", "Plane Transformed(const Matrix4&in) const", asMETHODPR(Plane, Transformed, (const Matrix4&) const, Plane), asCALL_THISCALL);
    engine->RegisterObjectMethod("Plane", "Vector4 ToVector4() const", asMETHOD(Plane, ToVector4), asCALL_THISCALL);
    engine->RegisterObjectMethod("Plane", "Matrix3x4 get_reflectionMatrix() const", asMETHOD(Plane, ReflectionMatrix), asCALL_THISCALL);
    engine->RegisterObjectProperty("Plane", "Vector3 normal", offsetof(Plane, normal_));
    engine->RegisterObjectProperty("Plane", "Vector3 absNormal", offsetof(Plane, absNormal_));
    engine->RegisterObjectProperty("Plane", "float d", offsetof(Plane, d_));
}

static void ConstructRay(Ray* ptr)
{
    new(ptr) Ray();
}

static void ConstructRayCopy(const Ray& ray, Ray* ptr)
{
    new(ptr) Ray(ray);
}

static void ConstructRayInit(const Vector3& origin, const Vector3& direction, Ray* ptr)
{
    new(ptr) Ray(origin, direction);
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
    engine->RegisterObjectMethod("Ray", "Vector3 Project(const Vector3&in) const", asMETHOD(Ray, Project), asCALL_THISCALL);
    engine->RegisterObjectMethod("Ray", "float Distance(const Vector3&in) const", asMETHOD(Ray, Distance), asCALL_THISCALL);
    engine->RegisterObjectMethod("Ray", "Vector3 ClosestPoint(const Ray&in) const", asMETHOD(Ray, ClosestPoint), asCALL_THISCALL);
    engine->RegisterObjectMethod("Ray", "float HitDistance(const Plane&in) const", asMETHODPR(Ray, HitDistance, (const Plane&) const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("Ray", "float HitDistance(const Sphere&in) const", asMETHODPR(Ray, HitDistance, (const Sphere&) const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("Ray", "float HitDistance(const BoundingBox&in) const", asMETHODPR(Ray, HitDistance, (const BoundingBox&) const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("Ray", "float HitDistance(const Frustum&in, bool solidInside = true) const", asMETHODPR(Ray, HitDistance, (const Frustum&, bool) const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("Ray", "float HitDistance(const Vector3&in, const Vector3&in, const Vector3&in) const", asMETHODPR(Ray, HitDistance, (const Vector3&, const Vector3&, const Vector3&, Vector3*, Vector3*) const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("Ray", "Ray Transformed(const Matrix3x4&in) const", asMETHOD(Ray, Transformed), asCALL_THISCALL);
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

static void ConstructRectInitVec4(const Vector4& vec, Rect* ptr)
{
    new(ptr) Rect(vec);
}

static void RegisterRect(asIScriptEngine* engine)
{
    engine->RegisterObjectType("Rect", sizeof(Rect), asOBJ_VALUE | asOBJ_POD | asOBJ_APP_CLASS_CAK);
    engine->RegisterObjectBehaviour("Rect", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(ConstructRect), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("Rect", asBEHAVE_CONSTRUCT, "void f(const Rect&in)", asFUNCTION(ConstructRectCopy), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("Rect", asBEHAVE_CONSTRUCT, "void f(float, float, float, float)", asFUNCTION(ConstructRectInit), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("Rect", asBEHAVE_CONSTRUCT, "void f(const Vector2&in, const Vector2&in)", asFUNCTION(ConstructRectInitVec), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("Rect", asBEHAVE_CONSTRUCT, "void f(const Vector4&in)", asFUNCTION(ConstructRectInitVec4), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("Rect", "Rect& opAssign(const Rect&in)", asMETHOD(Rect, operator =), asCALL_THISCALL);
    engine->RegisterObjectMethod("Rect", "bool opEquals(const Rect&in) const", asMETHOD(Rect, operator ==), asCALL_THISCALL);
    engine->RegisterObjectMethod("Rect", "void Define(const Vector2&in, const Vector2&in)", asMETHODPR(Rect, Define, (const Vector2&, const Vector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Rect", "void Define(const Vector2&in)", asMETHODPR(Rect, Define, (const Vector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Rect", "void Merge(const Vector2&in)", asMETHODPR(Rect, Merge, (const Vector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Rect", "void Merge(const Rect&in)", asMETHODPR(Rect, Merge, (const Rect&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Rect", "void Clip(const Rect&in)", asMETHODPR(Rect, Clip, (const Rect&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Rect", "void Clear()", asMETHOD(Rect, Clear), asCALL_THISCALL);
    engine->RegisterObjectMethod("Rect", "bool Equals(const Rect&in) const", asMETHOD(Rect, Equals), asCALL_THISCALL);
    engine->RegisterObjectMethod("Rect", "Intersection IsInside(const Vector2&in) const", asMETHOD(Rect, IsInside), asCALL_THISCALL);
    engine->RegisterObjectMethod("Rect", "Vector4 ToVector4() const", asMETHOD(Rect, ToVector4), asCALL_THISCALL);
    engine->RegisterObjectMethod("Rect", "bool Defined() const", asMETHOD(Rect, Defined), asCALL_THISCALL);
    engine->RegisterObjectMethod("Rect", "Vector2 get_center() const", asMETHOD(Rect, Center), asCALL_THISCALL);
    engine->RegisterObjectMethod("Rect", "Vector2 get_size() const", asMETHOD(Rect, Size), asCALL_THISCALL);
    engine->RegisterObjectMethod("Rect", "Vector2 get_halfSize() const", asMETHOD(Rect, HalfSize), asCALL_THISCALL);
    engine->RegisterObjectProperty("Rect", "Vector2 min", offsetof(Rect, min_));
    engine->RegisterObjectProperty("Rect", "Vector2 max", offsetof(Rect, max_));
    engine->RegisterObjectProperty("Rect", "float left", offsetof(Rect, min_.x_));
    engine->RegisterObjectProperty("Rect", "float top", offsetof(Rect, min_.y_));
    engine->RegisterObjectProperty("Rect", "float right", offsetof(Rect, max_.x_));
    engine->RegisterObjectProperty("Rect", "float bottom", offsetof(Rect, max_.y_));
}

static void ConstructBoundingBox(BoundingBox* ptr)
{
    new(ptr) BoundingBox();
}

static void ConstructBoundingBoxCopy(const BoundingBox& box, BoundingBox* ptr)
{
    new(ptr) BoundingBox(box);
}

static void ConstructBoundingBoxRect(const Rect& rect, BoundingBox* ptr)
{
    new(ptr) BoundingBox(rect);
}

static void ConstructBoundingBoxInit(const Vector3& min, const Vector3& max, BoundingBox* ptr)
{
    new(ptr) BoundingBox(min, max);
}

static void ConstructBoundingBoxFloat(float min, float max, BoundingBox* ptr)
{
    new(ptr) BoundingBox(min, max);
}


static void ConstructBoundingBoxFrustum(const Frustum& frustum, BoundingBox* ptr)
{
    new(ptr) BoundingBox(frustum);
}

static void ConstructBoundingBoxPolyhedron(const Polyhedron& poly, BoundingBox* ptr)
{
    new(ptr) BoundingBox(poly);
}

static void ConstructBoundingBoxSphere(const Sphere& sphere, BoundingBox* ptr)
{
    new(ptr) BoundingBox(sphere);
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

static void ConstructSphereBoundingBox(const BoundingBox& box, Sphere* ptr)
{
    new(ptr) Sphere(box);
}

static void ConstructSphereFrustum(const Frustum& frustum, Sphere* ptr)
{
    new(ptr) Sphere(frustum);
}

static void ConstructSpherePolyhedron(const Polyhedron& poly, Sphere* ptr)
{
    new(ptr) Sphere(poly);
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

static void ConstructPolyhedron(Polyhedron* ptr)
{
    new(ptr) Polyhedron();
}

static void ConstructPolyhedronCopy(const Polyhedron& polyhedron, Polyhedron* ptr)
{
    new(ptr) Polyhedron(polyhedron);
}

static void ConstructPolyhedronBoundingBox(const BoundingBox& box, Polyhedron* ptr)
{
    new(ptr) Polyhedron(box);
}

static void ConstructPolyhedronFrustum(const Frustum& frustum, Polyhedron* ptr)
{
    new(ptr) Polyhedron(frustum);
}

static void DestructPolyhedron(Polyhedron* ptr)
{
    ptr->~Polyhedron();
}

void PolyhedronAddFaceArray(CScriptArray* arr, Polyhedron* ptr)
{
    PODVector<Vector3> face;
    unsigned numVertices = arr->GetSize();

    face.Resize(numVertices);
    for (unsigned i = 0; i < numVertices; ++i)
        face[i] = *((Vector3*)arr->At(i));
    ptr->AddFace(face);
}

static unsigned PolyhedronGetNumFaces(Polyhedron* ptr)
{
    return ptr->faces_.Size();
}

static CScriptArray* PolyhedronGetFace(unsigned index, Polyhedron* ptr)
{
    PODVector<Vector3> face;
    if (index < ptr->faces_.Size())
        face = ptr->faces_[index];
    return VectorToArray<Vector3>(face, "Array<Vector3>");
}

static Vector3 FrustumGetVertex(unsigned index, Frustum* ptr)
{
    if (index >= NUM_FRUSTUM_VERTICES)
        return Vector3::ZERO;
    return ptr->vertices_[index];
}

static void RegisterVolumes(asIScriptEngine* engine)
{
    engine->RegisterObjectType("BoundingBox", sizeof(BoundingBox), asOBJ_VALUE | asOBJ_POD | asOBJ_APP_CLASS_CAK);
    engine->RegisterObjectType("Frustum", sizeof(Frustum), asOBJ_VALUE | asOBJ_APP_CLASS_CDAK);
    engine->RegisterObjectType("Polyhedron", sizeof(Polyhedron), asOBJ_VALUE | asOBJ_APP_CLASS_CDK);
    engine->RegisterObjectType("Sphere", sizeof(Sphere), asOBJ_VALUE | asOBJ_POD | asOBJ_APP_CLASS_CAK);

    engine->RegisterObjectBehaviour("BoundingBox", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(ConstructBoundingBox), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("BoundingBox", asBEHAVE_CONSTRUCT, "void f(const BoundingBox&in)", asFUNCTION(ConstructBoundingBoxCopy), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("BoundingBox", asBEHAVE_CONSTRUCT, "void f(const Rect&in)", asFUNCTION(ConstructBoundingBoxRect), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("BoundingBox", asBEHAVE_CONSTRUCT, "void f(const Vector3&in, const Vector3&in)", asFUNCTION(ConstructBoundingBoxInit), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("BoundingBox", asBEHAVE_CONSTRUCT, "void f(float, float)", asFUNCTION(ConstructBoundingBoxFloat), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("BoundingBox", asBEHAVE_CONSTRUCT, "void f(const Frustum&in)", asFUNCTION(ConstructBoundingBoxFrustum), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("BoundingBox", asBEHAVE_CONSTRUCT, "void f(const Polyhedron&in)", asFUNCTION(ConstructBoundingBoxPolyhedron), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("BoundingBox", asBEHAVE_CONSTRUCT, "void f(const Sphere&in)", asFUNCTION(ConstructBoundingBoxSphere), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("BoundingBox", "BoundingBox& opAssign(const BoundingBox&in)", asMETHODPR(BoundingBox, operator =, (const BoundingBox&), BoundingBox&), asCALL_THISCALL);
    engine->RegisterObjectMethod("BoundingBox", "bool opEquals(const BoundingBox&in) const", asMETHOD(BoundingBox, operator ==), asCALL_THISCALL);
    engine->RegisterObjectMethod("BoundingBox", "void Define(const Vector3&in, const Vector3&in)", asMETHODPR(BoundingBox, Define, (const Vector3&, const Vector3&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("BoundingBox", "void Define(float, float)", asMETHODPR(BoundingBox, Define, (float, float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("BoundingBox", "void Define(const Vector3&in)", asMETHODPR(BoundingBox, Define, (const Vector3&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("BoundingBox", "void Define(const BoundingBox&in)", asMETHODPR(BoundingBox, Define, (const BoundingBox&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("BoundingBox", "void Define(const Frustum&in)", asMETHODPR(BoundingBox, Define, (const Frustum&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("BoundingBox", "void Define(const Polyhedron&in)", asMETHODPR(BoundingBox, Define, (const Polyhedron&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("BoundingBox", "void Define(const Sphere&in)", asMETHODPR(BoundingBox, Define, (const Sphere&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("BoundingBox", "void Merge(const Vector3&in)", asMETHODPR(BoundingBox, Merge, (const Vector3&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("BoundingBox", "void Merge(const BoundingBox&in)", asMETHODPR(BoundingBox, Merge, (const BoundingBox&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("BoundingBox", "void Merge(const Frustum&in)", asMETHODPR(BoundingBox, Merge, (const Frustum&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("BoundingBox", "void Merge(const Polyhedron&in)", asMETHODPR(BoundingBox, Merge, (const Polyhedron&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("BoundingBox", "void Merge(const Sphere&in)", asMETHODPR(BoundingBox, Merge, (const Sphere&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("BoundingBox", "void Clip(const BoundingBox&in)", asMETHODPR(BoundingBox, Clip, (const BoundingBox&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("BoundingBox", "void Clear()", asMETHOD(BoundingBox, Clear), asCALL_THISCALL);
    engine->RegisterObjectMethod("BoundingBox", "void Transform(const Matrix3&in)", asMETHODPR(BoundingBox, Transform, (const Matrix3&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("BoundingBox", "void Transform(const Matrix3x4&in)", asMETHODPR(BoundingBox, Transform, (const Matrix3x4&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("BoundingBox", "Intersection IsInside(const Vector3&in) const", asMETHODPR(BoundingBox, IsInside, (const Vector3&) const, Intersection), asCALL_THISCALL);
    engine->RegisterObjectMethod("BoundingBox", "Intersection IsInside(const Sphere&in) const", asMETHODPR(BoundingBox, IsInside, (const Sphere&) const, Intersection), asCALL_THISCALL);
    engine->RegisterObjectMethod("BoundingBox", "Intersection IsInsideFast(const Sphere&in) const", asMETHODPR(BoundingBox, IsInsideFast, (const Sphere&) const, Intersection), asCALL_THISCALL);
    engine->RegisterObjectMethod("BoundingBox", "Intersection IsInside(const BoundingBox&in) const", asMETHODPR(BoundingBox, IsInside, (const BoundingBox&) const, Intersection), asCALL_THISCALL);
    engine->RegisterObjectMethod("BoundingBox", "Intersection IsInsideFast(const BoundingBox&in) const", asMETHODPR(BoundingBox, IsInsideFast, (const BoundingBox&) const, Intersection), asCALL_THISCALL);
    engine->RegisterObjectMethod("BoundingBox", "BoundingBox Transformed(const Matrix3&in) const", asMETHODPR(BoundingBox, Transformed, (const Matrix3&) const, BoundingBox), asCALL_THISCALL);
    engine->RegisterObjectMethod("BoundingBox", "BoundingBox Transformed(const Matrix3x4&in) const", asMETHODPR(BoundingBox, Transformed, (const Matrix3x4&) const, BoundingBox), asCALL_THISCALL);
    engine->RegisterObjectMethod("BoundingBox", "Rect Projected(const Matrix4&in) const", asMETHODPR(BoundingBox, Projected, (const Matrix4&) const, Rect), asCALL_THISCALL);
    engine->RegisterObjectMethod("BoundingBox", "String ToString() const", asMETHOD(BoundingBox, ToString), asCALL_THISCALL);
    engine->RegisterObjectMethod("BoundingBox", "bool Defined() const", asMETHOD(BoundingBox, Defined), asCALL_THISCALL);
    engine->RegisterObjectMethod("BoundingBox", "Vector3 get_center() const", asMETHOD(BoundingBox, Center), asCALL_THISCALL);
    engine->RegisterObjectMethod("BoundingBox", "Vector3 get_size() const", asMETHOD(BoundingBox, Size), asCALL_THISCALL);
    engine->RegisterObjectMethod("BoundingBox", "Vector3 get_halfSize() const", asMETHOD(BoundingBox, HalfSize), asCALL_THISCALL);
    engine->RegisterObjectProperty("BoundingBox", "Vector3 min", offsetof(BoundingBox, min_));
    engine->RegisterObjectProperty("BoundingBox", "Vector3 max", offsetof(BoundingBox, max_));

    engine->RegisterObjectBehaviour("Frustum", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(ConstructFrustum), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("Frustum", asBEHAVE_CONSTRUCT, "void f(const Frustum&in)", asFUNCTION(ConstructFrustumCopy), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("Frustum", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(DestructFrustum), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("Frustum", "Frustum& opAssign(const Frustum&in)", asMETHODPR(Frustum, operator =, (const Frustum&), Frustum&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Frustum", "void Define(float, float, float, float, float, const Matrix3x4&in)", asMETHODPR(Frustum, Define, (float, float, float, float, float, const Matrix3x4&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Frustum", "void Define(const Vector3&in, const Vector3&in, const Matrix3x4&in)", asMETHODPR(Frustum, Define, (const Vector3&, const Vector3&, const Matrix3x4&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Frustum", "void Define(const BoundingBox&in, const Matrix3x4&in)", asMETHODPR(Frustum, Define, (const BoundingBox&, const Matrix3x4&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Frustum", "void DefineOrtho(float, float, float, float, float, const Matrix3x4&in)", asMETHOD(Frustum, DefineOrtho), asCALL_THISCALL);
    engine->RegisterObjectMethod("Frustum", "void Transform(const Matrix3&in)", asMETHODPR(Frustum, Transform, (const Matrix3&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Frustum", "void Transform(const Matrix3x4&in)", asMETHODPR(Frustum, Transform, (const Matrix3x4&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Frustum", "Intersection IsInside(const Vector3&in)", asMETHODPR(Frustum, IsInside, (const Vector3&) const, Intersection), asCALL_THISCALL);
    engine->RegisterObjectMethod("Frustum", "Intersection IsInside(const BoundingBox&in)", asMETHODPR(Frustum, IsInside, (const BoundingBox&) const, Intersection), asCALL_THISCALL);
    engine->RegisterObjectMethod("Frustum", "Intersection IsInsideFast(const BoundingBox&in) const", asMETHODPR(Frustum, IsInsideFast, (const BoundingBox&) const, Intersection), asCALL_THISCALL);
    engine->RegisterObjectMethod("Frustum", "Intersection IsInside(const Sphere&in)", asMETHODPR(Frustum, IsInside, (const Sphere&) const, Intersection), asCALL_THISCALL);
    engine->RegisterObjectMethod("Frustum", "Intersection IsInsideFast(const Sphere&in) const", asMETHODPR(Frustum, IsInsideFast, (const Sphere&) const, Intersection), asCALL_THISCALL);
    engine->RegisterObjectMethod("Frustum", "float Distance(const Vector3&in) const", asMETHOD(Frustum, Distance), asCALL_THISCALL);
    engine->RegisterObjectMethod("Frustum", "Frustum Transformed(const Matrix3&in) const", asMETHODPR(Frustum, Transformed, (const Matrix3&) const, Frustum), asCALL_THISCALL);
    engine->RegisterObjectMethod("Frustum", "Frustum Transformed(const Matrix3x4&in) const", asMETHODPR(Frustum, Transformed, (const Matrix3x4&) const, Frustum), asCALL_THISCALL);
    engine->RegisterObjectMethod("Frustum", "Vector3 get_vertices(uint) const", asFUNCTION(FrustumGetVertex), asCALL_CDECL_OBJLAST);

    engine->RegisterObjectBehaviour("Polyhedron", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(ConstructPolyhedron), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("Polyhedron", asBEHAVE_CONSTRUCT, "void f(const Polyhedron&in)", asFUNCTION(ConstructPolyhedronCopy), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("Polyhedron", asBEHAVE_CONSTRUCT, "void f(const BoundingBox&in)", asFUNCTION(ConstructPolyhedronBoundingBox), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("Polyhedron", asBEHAVE_CONSTRUCT, "void f(const Frustum&in)", asFUNCTION(ConstructPolyhedronFrustum), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("Polyhedron", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(DestructPolyhedron), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("Polyhedron", "Polyhedron& opAssign(const Polyhedron&in)", asMETHOD(Polyhedron, operator =), asCALL_THISCALL);
    engine->RegisterObjectMethod("Polyhedron", "void AddFace(const Vector3&in, const Vector3&in, const Vector3&in)", asMETHODPR(Polyhedron, AddFace, (const Vector3&, const Vector3&, const Vector3&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Polyhedron", "void AddFace(const Vector3&in, const Vector3&in, const Vector3&in, const Vector3&in)", asMETHODPR(Polyhedron, AddFace, (const Vector3&, const Vector3&, const Vector3&, const Vector3&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Polyhedron", "void AddFace(const Array<Vector3>@)", asFUNCTION(PolyhedronAddFaceArray), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("Polyhedron", "void Define(const BoundingBox&in)", asMETHODPR(Polyhedron, Define, (const BoundingBox&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Polyhedron", "void Define(const Frustum&in)", asMETHODPR(Polyhedron, Define, (const Frustum&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Polyhedron", "void Clip(const BoundingBox&in)", asMETHODPR(Polyhedron, Clip, (const BoundingBox&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Polyhedron", "void Clip(const Frustum&in)", asMETHODPR(Polyhedron, Clip, (const Frustum&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Polyhedron", "void Clear()", asMETHOD(Polyhedron, Clear), asCALL_THISCALL);
    engine->RegisterObjectMethod("Polyhedron", "void Transform(const Matrix3&in)", asMETHODPR(Polyhedron, Transform, (const Matrix3&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Polyhedron", "void Transform(const Matrix3x4&in)", asMETHODPR(Polyhedron, Transform, (const Matrix3x4&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Polyhedron", "Polyhedron Transformed(const Matrix3&in) const", asMETHODPR(Polyhedron, Transformed, (const Matrix3&) const, Polyhedron), asCALL_THISCALL);
    engine->RegisterObjectMethod("Polyhedron", "Polyhedron Transformed(const Matrix3x4&in) const", asMETHODPR(Polyhedron, Transformed, (const Matrix3x4&) const, Polyhedron), asCALL_THISCALL);
    engine->RegisterObjectMethod("Polyhedron", "uint get_numFaces() const", asFUNCTION(PolyhedronGetNumFaces), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("Polyhedron", "Array<Vector3>@ get_face(uint) const", asFUNCTION(PolyhedronGetFace), asCALL_CDECL_OBJLAST);

    engine->RegisterObjectBehaviour("Sphere", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(ConstructSphere), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("Sphere", asBEHAVE_CONSTRUCT, "void f(const Sphere&in)", asFUNCTION(ConstructSphereCopy), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("Sphere", asBEHAVE_CONSTRUCT, "void f(const Vector3&in, float)", asFUNCTION(ConstructSphereInit), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("Sphere", asBEHAVE_CONSTRUCT, "void f(const BoundingBox&in)", asFUNCTION(ConstructSphereBoundingBox), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("Sphere", asBEHAVE_CONSTRUCT, "void f(const Frustum&in)", asFUNCTION(ConstructSphereFrustum), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("Sphere", asBEHAVE_CONSTRUCT, "void f(const Polyhedron&in)", asFUNCTION(ConstructSpherePolyhedron), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("Sphere", "Sphere& opAssign(const Sphere&in)", asMETHODPR(Sphere, operator =, (const Sphere&), Sphere&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Sphere", "bool &opEquals(const Sphere&in) const", asMETHOD(Sphere, operator ==), asCALL_THISCALL);
    engine->RegisterObjectMethod("Sphere", "void Define(const Vector3&in, float)", asMETHODPR(Sphere, Define, (const Vector3&, float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Sphere", "void Define(const BoundingBox&in)", asMETHODPR(Sphere, Define, (const BoundingBox&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Sphere", "void Define(const Frustum&in)", asMETHODPR(Sphere, Define, (const Frustum&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Sphere", "void Define(const Polyhedron&in)", asMETHODPR(Sphere, Define, (const Polyhedron&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Sphere", "void Define(const Sphere&in)", asMETHODPR(Sphere, Define, (const Sphere&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Sphere", "void Merge(const Vector3&in)", asMETHODPR(Sphere, Merge, (const Vector3&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Sphere", "void Merge(const BoundingBox&in)", asMETHODPR(Sphere, Merge, (const BoundingBox&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Sphere", "void Merge(const Frustum&in)", asMETHODPR(Sphere, Merge, (const Frustum&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Sphere", "void Merge(const Sphere&in)", asMETHODPR(Sphere, Merge, (const Sphere&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Sphere", "void Clear()", asMETHOD(Sphere, Clear), asCALL_THISCALL);
    engine->RegisterObjectMethod("Sphere", "bool Defined() const", asMETHOD(Sphere, Defined), asCALL_THISCALL);
    engine->RegisterObjectMethod("Sphere", "Intersection IsInside(const Vector3&in) const", asMETHODPR(Sphere, IsInside, (const Vector3&) const, Intersection), asCALL_THISCALL);
    engine->RegisterObjectMethod("Sphere", "Intersection IsInside(const Sphere&in) const", asMETHODPR(Sphere, IsInside, (const Sphere&) const, Intersection), asCALL_THISCALL);
    engine->RegisterObjectMethod("Sphere", "Intersection IsInsideFast(const Sphere&in) const", asMETHODPR(Sphere, IsInsideFast, (const Sphere&) const, Intersection), asCALL_THISCALL);
    engine->RegisterObjectMethod("Sphere", "Intersection IsInside(const BoundingBox&in) const", asMETHODPR(Sphere, IsInside, (const BoundingBox&) const, Intersection), asCALL_THISCALL);
    engine->RegisterObjectMethod("Sphere", "Intersection IsInsideFast(const BoundingBox&in) const", asMETHODPR(Sphere, IsInsideFast, (const BoundingBox&) const, Intersection), asCALL_THISCALL);
    engine->RegisterObjectMethod("Sphere", "float Distance(const Vector3&in) const", asMETHOD(Sphere, Distance), asCALL_THISCALL);
    engine->RegisterObjectProperty("Sphere", "Vector3 center", offsetof(Sphere, center_));
    engine->RegisterObjectProperty("Sphere", "float radius", offsetof(Sphere, radius_));
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

static void ConstructColorArrayInit(CScriptArray* data, Color* ptr)
{
    new(ptr) Color((static_cast<float*>(data->At(0))));
}

static CScriptArray* ColorData(Color* ptr)
{
    return BufferToArray<float>(ptr->Data(), 4, "float[]");
}

static float ColorHue(Color* ptr)
{
    return ptr->Hue();
}

static float ColorSaturationHSL(Color* ptr)
{
    return ptr->SaturationHSL();
}

static float ColorSaturationHSV(Color* ptr)
{
    return ptr->SaturationHSV();
}

static void RegisterColor(asIScriptEngine* engine)
{
    engine->RegisterObjectType("Color", sizeof(Color), asOBJ_VALUE | asOBJ_POD | asOBJ_APP_CLASS_CAK);
    engine->RegisterObjectBehaviour("Color", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(ConstructColor), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("Color", asBEHAVE_CONSTRUCT, "void f(const Color&in)", asFUNCTION(ConstructColorCopy), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("Color", asBEHAVE_CONSTRUCT, "void f(float, float, float, float)", asFUNCTION(ConstructColorRGBA), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("Color", asBEHAVE_CONSTRUCT, "void f(float, float, float)", asFUNCTION(ConstructColorRGB), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("Color", asBEHAVE_CONSTRUCT, "void f(float[]&)", asFUNCTION(ConstructColorArrayInit), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("Color", "Color& opAssign(const Color&in)", asMETHOD(Color, operator =), asCALL_THISCALL);
    engine->RegisterObjectMethod("Color", "Color& opAddAssign(const Color&in)", asMETHOD(Color, operator +=), asCALL_THISCALL);
    engine->RegisterObjectMethod("Color", "bool opEquals(const Color&in) const", asMETHOD(Color, operator ==), asCALL_THISCALL);
    engine->RegisterObjectMethod("Color", "Color opMul(float) const", asMETHOD(Color, operator *), asCALL_THISCALL);
    engine->RegisterObjectMethod("Color", "Color opAdd(const Color&in) const", asMETHOD(Color, operator +), asCALL_THISCALL);
    engine->RegisterObjectMethod("Color", "float[]& get_data() const", asFUNCTION(ColorData), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("Color", "uint ToUInt() const", asMETHOD(Color, ToUInt), asCALL_THISCALL);
    engine->RegisterObjectMethod("Color", "Vector3 ToHSL() const", asMETHOD(Color, ToHSL), asCALL_THISCALL);
    engine->RegisterObjectMethod("Color", "Vector3 ToHSV() const", asMETHOD(Color, ToHSV), asCALL_THISCALL);
    engine->RegisterObjectMethod("Color", "void FromHSL(float, float, float, float)", asMETHOD(Color, FromHSL), asCALL_THISCALL);
    engine->RegisterObjectMethod("Color", "void FromHSV(float, float, float, float)", asMETHOD(Color, FromHSV), asCALL_THISCALL);
    engine->RegisterObjectMethod("Color", "Vector3 get_rgb() const", asMETHOD(Color, ToVector3), asCALL_THISCALL);
    engine->RegisterObjectMethod("Color", "Vector4 get_rgba() const", asMETHOD(Color, ToVector4), asCALL_THISCALL);
    engine->RegisterObjectMethod("Color", "float SumRGB() const", asMETHOD(Color, SumRGB), asCALL_THISCALL);
    engine->RegisterObjectMethod("Color", "float Average() const", asMETHOD(Color, Average), asCALL_THISCALL);
    engine->RegisterObjectMethod("Color", "float Luma() const", asMETHOD(Color, Luma), asCALL_THISCALL);
    engine->RegisterObjectMethod("Color", "float Chroma() const", asMETHOD(Color, Chroma), asCALL_THISCALL);
    engine->RegisterObjectMethod("Color", "float Hue() const", asFUNCTION(ColorHue), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("Color", "float SaturationHSL() const", asFUNCTION(ColorSaturationHSL), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("Color", "float SaturationHSV() const", asFUNCTION(ColorSaturationHSV), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("Color", "float Value(void) const", asMETHOD(Color, Value), asCALL_THISCALL);
    engine->RegisterObjectMethod("Color", "float Lightness() const", asMETHOD(Color, Lightness), asCALL_THISCALL);
    engine->RegisterObjectMethod("Color", "float MaxRGB() const", asMETHOD(Color, MaxRGB), asCALL_THISCALL);
    engine->RegisterObjectMethod("Color", "float MinRGB() const", asMETHOD(Color, MinRGB), asCALL_THISCALL);
    engine->RegisterObjectMethod("Color", "float Range() const", asMETHOD(Color, Range), asCALL_THISCALL);
    engine->RegisterObjectMethod("Color", "void Clip(bool)", asMETHOD(Color, Clip), asCALL_THISCALL);
    engine->RegisterObjectMethod("Color", "void Invert(bool)", asMETHOD(Color, Invert), asCALL_THISCALL);
    engine->RegisterObjectMethod("Color", "Color Lerp(const Color&in, float) const", asMETHOD(Color, Lerp), asCALL_THISCALL);
    engine->RegisterObjectMethod("Color", "Color Abs() const", asMETHOD(Color, Abs), asCALL_THISCALL);
    engine->RegisterObjectMethod("Color", "bool Equals() const", asMETHOD(Color, Equals), asCALL_THISCALL);
    engine->RegisterObjectMethod("Color", "String ToString() const", asMETHOD(Color, ToString), asCALL_THISCALL);

    engine->RegisterObjectProperty("Color", "float r", offsetof(Color, r_));
    engine->RegisterObjectProperty("Color", "float g", offsetof(Color, g_));
    engine->RegisterObjectProperty("Color", "float b", offsetof(Color, b_));
    engine->RegisterObjectProperty("Color", "float a", offsetof(Color, a_));

    engine->RegisterGlobalProperty("const Color WHITE", (void*)&Color::WHITE);
    engine->RegisterGlobalProperty("const Color GRAY", (void*)&Color::GRAY);
    engine->RegisterGlobalProperty("const Color BLACK", (void*)&Color::BLACK);
    engine->RegisterGlobalProperty("const Color RED", (void*)&Color::RED);
    engine->RegisterGlobalProperty("const Color GREEN", (void*)&Color::GREEN);
    engine->RegisterGlobalProperty("const Color BLUE", (void*)&Color::BLUE);
    engine->RegisterGlobalProperty("const Color CYAN", (void*)&Color::CYAN);
    engine->RegisterGlobalProperty("const Color MAGENTA", (void*)&Color::MAGENTA);
    engine->RegisterGlobalProperty("const Color YELLOW", (void*)&Color::YELLOW);
    engine->RegisterGlobalProperty("const Color TRANSPARENT", (void*)&Color::TRANSPARENT);
}

void RegisterMathAPI(asIScriptEngine* engine)
{
    RegisterMathFunctions(engine);
    RegisterIntVector2(engine);
    RegisterIntRect(engine);
    RegisterVector2(engine);
    RegisterVector3(engine);
    RegisterVector4(engine);
    RegisterMatrix2(engine);
    RegisterMatrix3(engine);
    RegisterQuaternion(engine);
    RegisterMatrix4(engine);
    RegisterMatrix3x4(engine);
    RegisterRect(engine);
    RegisterVolumes(engine);
    RegisterPlane(engine);
    RegisterRay(engine);
    RegisterColor(engine);
}

}
