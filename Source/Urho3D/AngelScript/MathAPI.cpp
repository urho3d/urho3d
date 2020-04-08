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
#include "../Math/Frustum.h"
#include "../Math/Polyhedron.h"
#include "../Math/Ray.h"
#include "../Math/Matrix2.h"

// Some headers could re-define M_PI, ensure that it's undefined.
#undef M_PI

namespace Urho3D
{

static void RegisterMathFunctions(asIScriptEngine* engine)
{
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
    engine->RegisterGlobalFunction("bool IsNaN(float)", asFUNCTIONPR(IsNaN, (float), bool), asCALL_CDECL);
    engine->RegisterGlobalFunction("bool IsNaN(double)", asFUNCTIONPR(IsNaN, (double), bool), asCALL_CDECL);
    engine->RegisterGlobalFunction("float Sin(float)", asFUNCTION(Sin<float>), asCALL_CDECL);
    engine->RegisterGlobalFunction("float Cos(float)", asFUNCTION(Cos<float>), asCALL_CDECL);
    engine->RegisterGlobalFunction("float Tan(float)", asFUNCTION(Tan<float>), asCALL_CDECL);
    engine->RegisterGlobalFunction("float Asin(float)", asFUNCTION(Asin<float>), asCALL_CDECL);
    engine->RegisterGlobalFunction("float Acos(float)", asFUNCTION(Acos<float>), asCALL_CDECL);
    engine->RegisterGlobalFunction("float Atan(float)", asFUNCTION(Atan<float>), asCALL_CDECL);
    engine->RegisterGlobalFunction("float Atan2(float, float)", asFUNCTION(Atan2<float>), asCALL_CDECL);
    engine->RegisterGlobalFunction("float Abs(float)", asFUNCTION(Abs<float>), asCALL_CDECL);
    engine->RegisterGlobalFunction("float Sign(float)", asFUNCTION(Sign<float>), asCALL_CDECL);
    engine->RegisterGlobalFunction("float Sqrt(float)", asFUNCTION(Sqrt<float>), asCALL_CDECL);
    engine->RegisterGlobalFunction("float Pow(float, float)", asFUNCTION(Pow<float>), asCALL_CDECL);
    engine->RegisterGlobalFunction("float Ln(float)", asFUNCTION(Ln<float>), asCALL_CDECL);
    engine->RegisterGlobalFunction("float Min(float, float)", asFUNCTIONPR(Min, (float, float), float), asCALL_CDECL);
    engine->RegisterGlobalFunction("int Min(int, int)", asFUNCTIONPR(Min, (int, int), int), asCALL_CDECL);
    engine->RegisterGlobalFunction("float Max(float, float)", asFUNCTIONPR(Max, (float, float), float), asCALL_CDECL);
    engine->RegisterGlobalFunction("int Max(int, int)", asFUNCTIONPR(Max, (int, int), int), asCALL_CDECL);
    engine->RegisterGlobalFunction("float Clamp(float, float, float)", asFUNCTION(Clamp<float>), asCALL_CDECL);
    engine->RegisterGlobalFunction("float SmoothStep(float, float, float)", asFUNCTION(SmoothStep<float>), asCALL_CDECL);
    engine->RegisterGlobalFunction("int Clamp(int, int, int)", asFUNCTION(Clamp<int>), asCALL_CDECL);
    engine->RegisterGlobalFunction("float Lerp(float, float, float)", asFUNCTIONPR(Lerp, (float, float, float), float), asCALL_CDECL);
    engine->RegisterGlobalFunction("float InverseLerp(float, float, float)", asFUNCTION(InverseLerp<float>), asCALL_CDECL);
    engine->RegisterGlobalFunction("float Mod(float, float)", asFUNCTION(Mod<float>), asCALL_CDECL);
    engine->RegisterGlobalFunction("float Fract(float)", asFUNCTION(Fract<float>), asCALL_CDECL);
    engine->RegisterGlobalFunction("float Floor(float)", asFUNCTION(Floor<float>), asCALL_CDECL);
    engine->RegisterGlobalFunction("float Round(float)", asFUNCTION(Round<float>), asCALL_CDECL);
    engine->RegisterGlobalFunction("float Ceil(float)", asFUNCTION(Ceil<float>), asCALL_CDECL);
    engine->RegisterGlobalFunction("int FloorToInt(float)", asFUNCTION(FloorToInt<float>), asCALL_CDECL);
    engine->RegisterGlobalFunction("int RoundToInt(float)", asFUNCTION(RoundToInt<float>), asCALL_CDECL);
    engine->RegisterGlobalFunction("int CeilToInt(float)", asFUNCTION(CeilToInt<float>), asCALL_CDECL);
    engine->RegisterGlobalFunction("bool IsPowerOfTwo(uint)", asFUNCTION(IsPowerOfTwo), asCALL_CDECL);
    engine->RegisterGlobalFunction("uint NextPowerOfTwo(uint)", asFUNCTION(NextPowerOfTwo), asCALL_CDECL);
    engine->RegisterGlobalFunction("uint CountSetBits(uint)", asFUNCTION(CountSetBits), asCALL_CDECL);
    engine->RegisterGlobalFunction("uint LogBaseTwo(uint)", asFUNCTION(LogBaseTwo), asCALL_CDECL);
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

static void ConstructIntRectMinMax(const IntVector2& min, const IntVector2& max, IntRect* ptr)
{
    new(ptr) IntRect(min, max);
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
    engine->RegisterObjectType("IntRect", sizeof(IntRect), asOBJ_VALUE | asOBJ_POD | asGetTypeTraits<IntRect>() | asOBJ_APP_CLASS_ALLINTS);
    engine->RegisterObjectBehaviour("IntRect", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(ConstructIntRect), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("IntRect", asBEHAVE_CONSTRUCT, "void f(const IntRect&in)", asFUNCTION(ConstructIntRectCopy), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("IntRect", asBEHAVE_CONSTRUCT, "void f(int, int, int, int)", asFUNCTION(ConstructIntRectInit), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("IntRect", asBEHAVE_CONSTRUCT, "void f(const IntVector2&in, const IntVector2&in)", asFUNCTION(ConstructIntRectMinMax), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("IntRect", asBEHAVE_CONSTRUCT, "void f(int[]&)", asFUNCTION(ConstructIntRectArrayInit), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("IntRect", "Intersection IsInside(const IntVector2&in) const", asMETHOD(IntRect, IsInside), asCALL_THISCALL);
    engine->RegisterObjectMethod("IntRect", "int[]& get_data() const", asFUNCTION(IntRectData), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("IntRect", "IntRect& opAssign(const IntRect&in)", asMETHODPR(IntRect, operator =, (const IntRect&), IntRect&), asCALL_THISCALL);
    engine->RegisterObjectMethod("IntRect", "bool opEquals(const IntRect&in) const", asMETHOD(IntRect, operator ==), asCALL_THISCALL);
    engine->RegisterObjectMethod("IntRect", "IntVector2 get_size() const", asMETHOD(IntRect, Size), asCALL_THISCALL);
    engine->RegisterObjectMethod("IntRect", "int get_width() const", asMETHOD(IntRect, Width), asCALL_THISCALL);
    engine->RegisterObjectMethod("IntRect", "int get_height() const", asMETHOD(IntRect, Height), asCALL_THISCALL);
    engine->RegisterObjectMethod("IntRect", "int Merge(const IntRect&in)", asMETHOD(IntRect, Merge), asCALL_THISCALL);
    engine->RegisterObjectMethod("IntRect", "int Clip(const IntRect&in)", asMETHOD(IntRect, Merge), asCALL_THISCALL);
    engine->RegisterObjectProperty("IntRect", "int left", offsetof(IntRect, left_));
    engine->RegisterObjectProperty("IntRect", "int top", offsetof(IntRect, top_));
    engine->RegisterObjectProperty("IntRect", "int right", offsetof(IntRect, right_));
    engine->RegisterObjectProperty("IntRect", "int bottom", offsetof(IntRect, bottom_));
}

static void RegisterIntVector2(asIScriptEngine* engine)
{
    engine->RegisterGlobalFunction("IntVector2 VectorMin(const IntVector2&in, const IntVector2&in)", asFUNCTIONPR(VectorMin, (const IntVector2&, const IntVector2&), IntVector2), asCALL_CDECL);
    engine->RegisterGlobalFunction("IntVector2 VectorMax(const IntVector2&in, const IntVector2&in)", asFUNCTIONPR(VectorMax, (const IntVector2&, const IntVector2&), IntVector2), asCALL_CDECL);

    engine->SetDefaultNamespace("IntVector2");
    engine->RegisterGlobalProperty("const IntVector2 ZERO", (void*)&IntVector2::ZERO);
    engine->RegisterGlobalProperty("const IntVector2 LEFT", (void*)&IntVector2::LEFT);
    engine->RegisterGlobalProperty("const IntVector2 RIGHT", (void*)&IntVector2::RIGHT);
    engine->RegisterGlobalProperty("const IntVector2 UP", (void*)&IntVector2::UP);
    engine->RegisterGlobalProperty("const IntVector2 DOWN", (void*)&IntVector2::DOWN);
    engine->RegisterGlobalProperty("const IntVector2 ONE", (void*)&IntVector2::ONE);
    engine->SetDefaultNamespace("");
}

static void RegisterIntVector3(asIScriptEngine* engine)
{
    engine->RegisterGlobalFunction("IntVector3 VectorMin(const IntVector3&in, const IntVector3&in)", asFUNCTIONPR(VectorMin, (const IntVector3&, const IntVector3&), IntVector3), asCALL_CDECL);
    engine->RegisterGlobalFunction("IntVector3 VectorMax(const IntVector3&in, const IntVector3&in)", asFUNCTIONPR(VectorMax, (const IntVector3&, const IntVector3&), IntVector3), asCALL_CDECL);

    engine->SetDefaultNamespace("IntVector3");
    engine->RegisterGlobalProperty("const IntVector3 ZERO", (void*)&IntVector3::ZERO);
    engine->RegisterGlobalProperty("const IntVector3 LEFT", (void*)&IntVector3::LEFT);
    engine->RegisterGlobalProperty("const IntVector3 RIGHT", (void*)&IntVector3::RIGHT);
    engine->RegisterGlobalProperty("const IntVector3 UP", (void*)&IntVector3::UP);
    engine->RegisterGlobalProperty("const IntVector3 DOWN", (void*)&IntVector3::DOWN);
    engine->RegisterGlobalProperty("const IntVector3 FORWARD", (void*)&IntVector3::FORWARD);
    engine->RegisterGlobalProperty("const IntVector3 BACK", (void*)&IntVector3::BACK);
    engine->RegisterGlobalProperty("const IntVector3 ONE", (void*)&IntVector3::ONE);
    engine->SetDefaultNamespace("");
}

static void RegisterVector2(asIScriptEngine* engine)
{
    engine->RegisterGlobalFunction("float StableRandom(const Vector2&in)", asFUNCTIONPR(StableRandom, (const Vector2&), float), asCALL_CDECL);
    engine->RegisterGlobalFunction("float StableRandom(float)", asFUNCTIONPR(StableRandom, (float), float), asCALL_CDECL);
    engine->RegisterGlobalFunction("Vector2 VectorLerp(const Vector2&in, const Vector2&in, const Vector2&in)", asFUNCTIONPR(VectorLerp, (const Vector2&, const Vector2&, const Vector2&), Vector2), asCALL_CDECL);
    engine->RegisterGlobalFunction("Vector2 VectorMin(const Vector2&in, const Vector2&in)", asFUNCTIONPR(VectorMin, (const Vector2&, const Vector2&), Vector2), asCALL_CDECL);
    engine->RegisterGlobalFunction("Vector2 VectorMax(const Vector2&in, const Vector2&in)", asFUNCTIONPR(VectorMax, (const Vector2&, const Vector2&), Vector2), asCALL_CDECL);
    engine->RegisterGlobalFunction("Vector2 VectorFloor(const Vector2&in)", asFUNCTIONPR(VectorFloor, (const Vector2&), Vector2), asCALL_CDECL);
    engine->RegisterGlobalFunction("Vector2 VectorRound(const Vector2&in)", asFUNCTIONPR(VectorFloor, (const Vector2&), Vector2), asCALL_CDECL);
    engine->RegisterGlobalFunction("Vector2 VectorCeil(const Vector2&in)", asFUNCTIONPR(VectorFloor, (const Vector2&), Vector2), asCALL_CDECL);
    engine->RegisterGlobalFunction("IntVector2 VectorFloorToInt(const Vector2&in)", asFUNCTIONPR(VectorFloorToInt, (const Vector2&), IntVector2), asCALL_CDECL);
    engine->RegisterGlobalFunction("IntVector2 VectorRoundToInt(const Vector2&in)", asFUNCTIONPR(VectorRoundToInt, (const Vector2&), IntVector2), asCALL_CDECL);
    engine->RegisterGlobalFunction("IntVector2 VectorCeilToInt(const Vector2&in)", asFUNCTIONPR(VectorCeilToInt, (const Vector2&), IntVector2), asCALL_CDECL);

    engine->SetDefaultNamespace("Vector2");
    engine->RegisterGlobalProperty("const Vector2 ZERO", (void*)&Vector2::ZERO);
    engine->RegisterGlobalProperty("const Vector2 LEFT", (void*)&Vector2::LEFT);
    engine->RegisterGlobalProperty("const Vector2 RIGHT", (void*)&Vector2::RIGHT);
    engine->RegisterGlobalProperty("const Vector2 UP", (void*)&Vector2::UP);
    engine->RegisterGlobalProperty("const Vector2 DOWN", (void*)&Vector2::DOWN);
    engine->RegisterGlobalProperty("const Vector2 ONE", (void*)&Vector2::ONE);
    engine->SetDefaultNamespace("");
}

static void RegisterVector3(asIScriptEngine* engine)
{
    engine->RegisterGlobalFunction("float StableRandom(const Vector3&in)", asFUNCTIONPR(StableRandom, (const Vector3&), float), asCALL_CDECL);
    engine->RegisterGlobalFunction("Vector3 VectorLerp(const Vector3&in, const Vector3&in, const Vector3&in)", asFUNCTIONPR(VectorLerp, (const Vector3&, const Vector3&, const Vector3&), Vector3), asCALL_CDECL);
    engine->RegisterGlobalFunction("Vector3 VectorMin(const Vector3&in, const Vector3&in)", asFUNCTIONPR(VectorMin, (const Vector3&, const Vector3&), Vector3), asCALL_CDECL);
    engine->RegisterGlobalFunction("Vector3 VectorMax(const Vector3&in, const Vector3&in)", asFUNCTIONPR(VectorMax, (const Vector3&, const Vector3&), Vector3), asCALL_CDECL);
    engine->RegisterGlobalFunction("Vector3 VectorFloor(const Vector3&in)", asFUNCTIONPR(VectorFloor, (const Vector3&), Vector3), asCALL_CDECL);
    engine->RegisterGlobalFunction("Vector3 VectorRound(const Vector3&in)", asFUNCTIONPR(VectorFloor, (const Vector3&), Vector3), asCALL_CDECL);
    engine->RegisterGlobalFunction("Vector3 VectorCeil(const Vector3&in)", asFUNCTIONPR(VectorFloor, (const Vector3&), Vector3), asCALL_CDECL);
    engine->RegisterGlobalFunction("IntVector3 VectorFloorToInt(const Vector3&in)", asFUNCTIONPR(VectorFloorToInt, (const Vector3&), IntVector3), asCALL_CDECL);
    engine->RegisterGlobalFunction("IntVector3 VectorRoundToInt(const Vector3&in)", asFUNCTIONPR(VectorRoundToInt, (const Vector3&), IntVector3), asCALL_CDECL);
    engine->RegisterGlobalFunction("IntVector3 VectorCeilToInt(const Vector3&in)", asFUNCTIONPR(VectorCeilToInt, (const Vector3&), IntVector3), asCALL_CDECL);

    engine->SetDefaultNamespace("Vector3");
    engine->RegisterGlobalProperty("const Vector3 ZERO", (void*)&Vector3::ZERO);
    engine->RegisterGlobalProperty("const Vector3 LEFT", (void*)&Vector3::LEFT);
    engine->RegisterGlobalProperty("const Vector3 RIGHT", (void*)&Vector3::RIGHT);
    engine->RegisterGlobalProperty("const Vector3 UP", (void*)&Vector3::UP);
    engine->RegisterGlobalProperty("const Vector3 DOWN", (void*)&Vector3::DOWN);
    engine->RegisterGlobalProperty("const Vector3 FORWARD", (void*)&Vector3::FORWARD);
    engine->RegisterGlobalProperty("const Vector3 BACK", (void*)&Vector3::BACK);
    engine->RegisterGlobalProperty("const Vector3 ONE", (void*)&Vector3::ONE);
    engine->SetDefaultNamespace("");
}

static void RegisterVector4(asIScriptEngine* engine)
{
    engine->RegisterGlobalFunction("Vector4 VectorLerp(const Vector4&in, const Vector4&in, const Vector4&in)", asFUNCTIONPR(VectorLerp, (const Vector4&, const Vector4&, const Vector4&), Vector4), asCALL_CDECL);
    engine->RegisterGlobalFunction("Vector4 VectorMin(const Vector4&in, const Vector4&in)", asFUNCTIONPR(VectorMin, (const Vector4&, const Vector4&), Vector4), asCALL_CDECL);
    engine->RegisterGlobalFunction("Vector4 VectorMax(const Vector4&in, const Vector4&in)", asFUNCTIONPR(VectorMax, (const Vector4&, const Vector4&), Vector4), asCALL_CDECL);
    engine->RegisterGlobalFunction("Vector4 VectorFloor(const Vector4&in)", asFUNCTIONPR(VectorFloor, (const Vector4&), Vector4), asCALL_CDECL);
    engine->RegisterGlobalFunction("Vector4 VectorRound(const Vector4&in)", asFUNCTIONPR(VectorFloor, (const Vector4&), Vector4), asCALL_CDECL);
    engine->RegisterGlobalFunction("Vector4 VectorCeil(const Vector4&in)", asFUNCTIONPR(VectorFloor, (const Vector4&), Vector4), asCALL_CDECL);
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
    engine->RegisterObjectType("Plane", sizeof(Plane), asOBJ_VALUE | asOBJ_POD | asGetTypeTraits<Plane>() | asOBJ_APP_CLASS_ALLFLOATS);
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
    engine->RegisterObjectType("Ray", sizeof(Ray), asOBJ_VALUE | asOBJ_POD | asGetTypeTraits<Ray>() | asOBJ_APP_CLASS_ALLFLOATS);
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
    engine->RegisterObjectType("Rect", sizeof(Rect), asOBJ_VALUE | asOBJ_POD | asGetTypeTraits<Rect>() | asOBJ_APP_CLASS_ALLFLOATS);
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
    engine->RegisterObjectMethod("Rect", "Intersection IsInside(const Vector2&in) const", asMETHODPR(Rect, IsInside, (const Vector2&) const, Intersection), asCALL_THISCALL);
    engine->RegisterObjectMethod("Rect", "Intersection IsInside(const Rect&in) const", asMETHODPR(Rect, IsInside, (const Rect&) const, Intersection), asCALL_THISCALL);
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
    engine->RegisterObjectType("Sphere", sizeof(Sphere), asOBJ_VALUE | asOBJ_POD | asGetTypeTraits<Sphere>() | asOBJ_APP_CLASS_ALLFLOATS);

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
    engine->RegisterObjectMethod("BoundingBox", "float DistanceToPoint(const Vector3&in) const", asMETHOD(BoundingBox, DistanceToPoint), asCALL_THISCALL);
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
    engine->RegisterObjectMethod("Frustum", "void Define(const Matrix4&in)", asMETHODPR(Frustum, Define, (const Matrix4&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Frustum", "void DefineOrtho(float, float, float, float, float, const Matrix3x4&in)", asMETHOD(Frustum, DefineOrtho), asCALL_THISCALL);
    engine->RegisterObjectMethod("Frustum", "void DefineSplit(const Matrix4&in, float, float)", asMETHOD(Frustum, DefineSplit), asCALL_THISCALL);
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
    engine->RegisterObjectMethod("Sphere", "bool opEquals(const Sphere&in) const", asMETHOD(Sphere, operator ==), asCALL_THISCALL);
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
    engine->RegisterObjectMethod("Sphere", "Vector3 GetLocalPoint(float, float) const", asMETHOD(Sphere, GetLocalPoint), asCALL_THISCALL);
    engine->RegisterObjectMethod("Sphere", "Vector3 GetPoint(float, float) const", asMETHOD(Sphere, GetPoint), asCALL_THISCALL);
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
    engine->RegisterObjectType("Color", sizeof(Color), asOBJ_VALUE | asOBJ_POD | asGetTypeTraits<Color>() | asOBJ_APP_CLASS_ALLFLOATS);
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
    engine->RegisterObjectMethod("Color", "void FromUInt(uint)", asMETHOD(Color, FromUInt), asCALL_THISCALL);
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
    engine->RegisterObjectMethod("Color", "float Value() const", asMETHOD(Color, Value), asCALL_THISCALL);
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
    engine->RegisterGlobalProperty("const Color TRANSPARENT_BLACK", (void*)&Color::TRANSPARENT_BLACK);
}

void RegisterMathAPI(asIScriptEngine* engine)
{
    RegisterMathFunctions(engine);
    RegisterIntVector2(engine);
    RegisterIntVector3(engine);
    RegisterIntRect(engine);
    RegisterVector2(engine);
    RegisterVector3(engine);
    RegisterVector4(engine);
    RegisterRect(engine);
    RegisterVolumes(engine);
    RegisterPlane(engine);
    RegisterRay(engine);
    RegisterColor(engine);
}

}
