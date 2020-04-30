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

static void RegisterColor(asIScriptEngine* engine)
{
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
    RegisterVector2(engine);
    RegisterVector3(engine);
    RegisterVector4(engine);
    RegisterColor(engine);
}

}
