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

#pragma once

#include "../Math/Polyhedron.h"
#include "../Math/Ray.h"

namespace Urho3D
{

// explicit IntVector2::IntVector2(const int *data) noexcept | File: ../Math/Vector2.h
void ConstructIntVector2ArrayInit(CScriptArray* data, IntVector2* ptr);
// const int* IntVector2::Data() const | File: ../Math/Vector2.h
CScriptArray* IntVector2Data(IntVector2* ptr);

#define REGISTER_MANUAL_PART_IntVector2(T, className) \
    /* explicit IntVector2::IntVector2(const int *data) noexcept | File: ../Math/Vector2.h */ \
    engine->RegisterObjectBehaviour(className, asBEHAVE_CONSTRUCT, "void f(int[]&)", asFUNCTION(ConstructIntVector2ArrayInit), asCALL_CDECL_OBJLAST); \
    /* const int* IntVector2::Data() const | File: ../Math/Vector2.h */ \
    engine->RegisterObjectMethod(className, "int[]& get_data() const", asFUNCTION(IntVector2Data), asCALL_CDECL_OBJLAST);

// ========================================================================================

// explicit Vector2::Vector2(const float *data) noexcept | File: ../Math/Vector2.h
void ConstructVector2ArrayInit(CScriptArray* data, Vector2* ptr);
// const float* Vector2::Data() const | File: ../Math/Vector2.h
CScriptArray* Vector2Data(Vector2* ptr);

#define REGISTER_MANUAL_PART_Vector2(T, className) \
    /* explicit Vector2::Vector2(const float *data) noexcept | File: ../Math/Vector2.h */ \
    engine->RegisterObjectBehaviour(className, asBEHAVE_CONSTRUCT, "void f(float[]&)", asFUNCTION(ConstructVector2ArrayInit), asCALL_CDECL_OBJLAST); \
    /* const float* Vector2::Data() const | File: ../Math/Vector2.h */ \
    engine->RegisterObjectMethod(className, "float[]& get_data() const", asFUNCTION(Vector2Data), asCALL_CDECL_OBJLAST);

// ========================================================================================

// explicit IntVector3::IntVector3(const int *data) noexcept | File: ../Math/Vector3.h
void ConstructIntVector3ArrayInit(CScriptArray* data, IntVector3* ptr);
// const int* IntVector3::Data() const | File: ../Math/Vector3.h
CScriptArray* IntVector3Data(IntVector3* ptr);

#define REGISTER_MANUAL_PART_IntVector3(T, className) \
    /* explicit IntVector3::IntVector3(const int *data) noexcept | File: ../Math/Vector3.h */ \
    engine->RegisterObjectBehaviour(className, asBEHAVE_CONSTRUCT, "void f(int[]&)", asFUNCTION(ConstructIntVector3ArrayInit), asCALL_CDECL_OBJLAST); \
    /* const int* IntVector3::Data() const | File: ../Math/Vector3.h */ \
    engine->RegisterObjectMethod(className, "int[]& get_data() const", asFUNCTION(IntVector3Data), asCALL_CDECL_OBJLAST);

// ========================================================================================

// explicit Vector3::Vector3(const float *data) noexcept | File: ../Math/Vector3.h
void ConstructVector3ArrayInit(CScriptArray* data, Vector3* ptr);
// const float* Vector3::Data() const | File: ../Math/Vector3.h
CScriptArray* Vector3Data(Vector3* ptr);

#define REGISTER_MANUAL_PART_Vector3(T, className) \
    /* explicit Vector3::Vector3(const float *data) noexcept | File: ../Math/Vector3.h */ \
    engine->RegisterObjectBehaviour(className, asBEHAVE_CONSTRUCT, "void f(float[]&)", asFUNCTION(ConstructVector3ArrayInit), asCALL_CDECL_OBJLAST); \
    /* const float* Vector3::Data() const | File: ../Math/Vector3.h */ \
    engine->RegisterObjectMethod(className, "float[]& get_data() const", asFUNCTION(Vector3Data), asCALL_CDECL_OBJLAST);

// ========================================================================================

// explicit Vector4::Vector4(const float *data) noexcept | File: ../Math/Vector4.h
void ConstructVector4ArrayInit(CScriptArray* data, Vector4* ptr);
// const float* Vector4::Data() const | File: ../Math/Vector4.h
CScriptArray* Vector4Data(Vector4* ptr);

#define REGISTER_MANUAL_PART_Vector4(T, className) \
    /* explicit Vector4::Vector4(const float *data) noexcept | File: ../Math/Vector4.h */ \
    engine->RegisterObjectBehaviour(className, asBEHAVE_CONSTRUCT, "void f(float[]&)", asFUNCTION(ConstructVector4ArrayInit), asCALL_CDECL_OBJLAST); \
    /* const float* Vector4::Data() const | File: ../Math/Vector4.h */ \
    engine->RegisterObjectMethod(className, "float[]& get_data() const", asFUNCTION(Vector4Data), asCALL_CDECL_OBJLAST);

// ========================================================================================

// explicit IntRect::IntRect(const int *data) noexcept | File: ../Math/Rect.h
void ConstructIntRectArrayInit(CScriptArray* data, IntRect* ptr);
// const int* IntRect::Data() const | File: ../Math/Rect.h
CScriptArray* IntRectData(IntRect* ptr);

#define REGISTER_MANUAL_PART_IntRect(T, className) \
    /* explicit IntRect::IntRect(const int *data) noexcept | File: ../Math/Rect.h */ \
    engine->RegisterObjectBehaviour(className, asBEHAVE_CONSTRUCT, "void f(int[]&)", asFUNCTION(ConstructIntRectArrayInit), asCALL_CDECL_OBJLAST); \
    /* const int* IntRect::Data() const | File: ../Math/Rect.h */ \
    engine->RegisterObjectMethod(className, "int[]& get_data() const", asFUNCTION(IntRectData), asCALL_CDECL_OBJLAST);

// ========================================================================================

// explicit Color::Color(const float *data) noexcept | File: ../Math/Color.h
void ConstructColorArrayInit(CScriptArray* data, Color* ptr);
// const float* Color::Data() const | File: ../Math/Color.h
CScriptArray* ColorData(Color* ptr);

#define REGISTER_MANUAL_PART_Color(T, className) \
    /* explicit Color::Color(const float *data) noexcept | File: ../Math/Color.h */ \
    engine->RegisterObjectBehaviour(className, asBEHAVE_CONSTRUCT, "void f(float[]&)", asFUNCTION(ConstructColorArrayInit), asCALL_CDECL_OBJLAST); \
    /* const float* Color::Data() const | File: ../Math/Color.h */ \
    engine->RegisterObjectMethod(className, "float[]& get_data() const", asFUNCTION(ColorData), asCALL_CDECL_OBJLAST);

// ========================================================================================

// float Ray::HitDistance(const Vector3 &v0, const Vector3 &v1, const Vector3 &v2, Vector3 *outNormal=nullptr, Vector3 *outBary=nullptr) const | File: ../Math/Ray.h
float Ray_HitDistance(const Vector3& v0, const Vector3& v1, const Vector3& v2, Ray* ptr);

#define REGISTER_MANUAL_PART_Ray(T, className) \
    /* float Ray::HitDistance(const Vector3 &v0, const Vector3 &v1, const Vector3 &v2, Vector3 *outNormal=nullptr, Vector3 *outBary=nullptr) const | File: ../Math/Ray.h */ \
    engine->RegisterObjectMethod(className, "float HitDistance(const Vector3&in, const Vector3&in, const Vector3&in) const", asFUNCTION(Ray_HitDistance), asCALL_CDECL_OBJLAST);

// ========================================================================================

// Vector3 Frustum::vertices_[NUM_FRUSTUM_VERTICES] | File: ../Math/Frustum.h
Vector3 FrustumGetVertex(unsigned index, Frustum* ptr);

#define REGISTER_MANUAL_PART_Frustum(T, className) \
    /* Vector3 Frustum::vertices_[NUM_FRUSTUM_VERTICES] | File: ../Math/Frustum.h */ \
    engine->RegisterObjectMethod(className, "Vector3 get_vertices(uint) const", asFUNCTION(FrustumGetVertex), asCALL_CDECL_OBJLAST);

// ========================================================================================

// Vector<PODVector<Vector3> > Polyhedron::faces_ | File: ../Math/Polyhedron.h
unsigned PolyhedronGetNumFaces(Polyhedron* ptr);
// Vector<PODVector<Vector3> > Polyhedron::faces_ | File: ../Math/Polyhedron.h
CScriptArray* PolyhedronGetFace(unsigned index, Polyhedron* ptr);

#define REGISTER_MANUAL_PART_Polyhedron(T, className) \
    /* Vector<PODVector<Vector3> > Polyhedron::faces_ | File: ../Math/Polyhedron.h */ \
    engine->RegisterObjectMethod(className, "uint get_numFaces() const", asFUNCTION(PolyhedronGetNumFaces), asCALL_CDECL_OBJLAST); \
    /* Vector<PODVector<Vector3> > Polyhedron::faces_ | File: ../Math/Polyhedron.h */ \
    engine->RegisterObjectMethod(className, "Array<Vector3>@ get_face(uint) const", asFUNCTION(PolyhedronGetFace), asCALL_CDECL_OBJLAST);

}
