// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

#pragma once

#include "../Math/Polyhedron.h"
#include "../Math/Ray.h"

namespace Urho3D
{

// explicit IntVector2::IntVector2(const int* data) noexcept | File: ../Math/Vector2.h
static void IntVector2_IntVector2_Data(CScriptArray* data, IntVector2* ptr)
{
    new(ptr) IntVector2(static_cast<int*>(data->At(0)));
}

#define REGISTER_CLASS_MANUAL_PART_IntVector2() \
    /* explicit IntVector2::IntVector2(const int* data) noexcept | File: ../Math/Vector2.h */ \
    engine->RegisterObjectBehaviour("IntVector2", asBEHAVE_CONSTRUCT, "void f(int[]&)", AS_FUNCTION_OBJLAST(IntVector2_IntVector2_Data), AS_CALL_CDECL_OBJLAST);

// const int* IntVector2::Data() const | File: ../Math/Vector2.h
template <class T> CScriptArray* IntVector2_Data(T* ptr)
{
    return BufferToArray<int>(ptr->Data(), 2, "int[]");
}

#define REGISTER_MEMBERS_MANUAL_PART_IntVector2() \
    /* const int* IntVector2::Data() const | File: ../Math/Vector2.h */ \
    engine->RegisterObjectMethod(className, "int[]& get_data() const", AS_FUNCTION_OBJLAST(IntVector2_Data<T>), AS_CALL_CDECL_OBJLAST);

// ========================================================================================

// explicit Vector2::Vector2(const float* data) noexcept | File: ../Math/Vector2.h
static void Vector2_Vector2_Data(CScriptArray* data, Vector2* ptr)
{
    new(ptr) Vector2(static_cast<float*>(data->At(0)));
}

#define REGISTER_CLASS_MANUAL_PART_Vector2() \
    /* explicit Vector2::Vector2(const float* data) noexcept | File: ../Math/Vector2.h */ \
    engine->RegisterObjectBehaviour("Vector2", asBEHAVE_CONSTRUCT, "void f(float[]&)", AS_FUNCTION_OBJLAST(Vector2_Vector2_Data), AS_CALL_CDECL_OBJLAST);

// const float* Vector2::Data() const | File: ../Math/Vector2.h
template <class T> CScriptArray* Vector2_Data(T* ptr)
{
    return BufferToArray<float>(ptr->Data(), 2, "float[]");
}

#define REGISTER_MEMBERS_MANUAL_PART_Vector2() \
    /* const float* Vector2::Data() const | File: ../Math/Vector2.h */ \
    engine->RegisterObjectMethod(className, "float[]& get_data() const", AS_FUNCTION_OBJLAST(Vector2_Data<T>), AS_CALL_CDECL_OBJLAST);

// ========================================================================================

// explicit IntVector3::IntVector3(const int* data) noexcept | File: ../Math/Vector3.h
static void IntVector3_IntVector3_Data(CScriptArray* data, IntVector3* ptr)
{
    new(ptr) IntVector3(static_cast<int*>(data->At(0)));
}

#define REGISTER_CLASS_MANUAL_PART_IntVector3() \
    /* explicit IntVector3::IntVector3(const int* data) noexcept | File: ../Math/Vector3.h */ \
    engine->RegisterObjectBehaviour("IntVector3", asBEHAVE_CONSTRUCT, "void f(int[]&)", AS_FUNCTION_OBJLAST(IntVector3_IntVector3_Data), AS_CALL_CDECL_OBJLAST);

// const int* IntVector3::Data() const | File: ../Math/Vector3.h
template <class T> CScriptArray* IntVector3_Data(IntVector3* ptr)
{
    return BufferToArray<int>(ptr->Data(), 3, "int[]");
}

#define REGISTER_MEMBERS_MANUAL_PART_IntVector3() \
    /* const int* IntVector3::Data() const | File: ../Math/Vector3.h */ \
    engine->RegisterObjectMethod(className, "int[]& get_data() const", AS_FUNCTION_OBJLAST(IntVector3_Data<T>), AS_CALL_CDECL_OBJLAST);

// ========================================================================================

// explicit Vector3::Vector3(const float* data) noexcept | File: ../Math/Vector3.h
static void Vector3_Vector3_Data(CScriptArray* data, Vector3* ptr)
{
    new(ptr) Vector3(static_cast<float*>(data->At(0)));
}

#define REGISTER_CLASS_MANUAL_PART_Vector3() \
    /* explicit Vector3::Vector3(const float* data) noexcept | File: ../Math/Vector3.h */ \
    engine->RegisterObjectBehaviour("Vector3", asBEHAVE_CONSTRUCT, "void f(float[]&)", AS_FUNCTION_OBJLAST(Vector3_Vector3_Data), AS_CALL_CDECL_OBJLAST);

// const float* Vector3::Data() const | File: ../Math/Vector3.h
template <class T> CScriptArray* Vector3_Data(T* ptr)
{
    return BufferToArray<float>(ptr->Data(), 3, "float[]");
}

#define REGISTER_MEMBERS_MANUAL_PART_Vector3() \
    /* const float* Vector3::Data() const | File: ../Math/Vector3.h */ \
    engine->RegisterObjectMethod(className, "float[]& get_data() const", AS_FUNCTION_OBJLAST(Vector3_Data<T>), AS_CALL_CDECL_OBJLAST);

// ========================================================================================

// explicit Vector4::Vector4(const float* data) noexcept | File: ../Math/Vector4.h
static void Vector4_Vector4_Data(CScriptArray* data, Vector4* ptr)
{
    new(ptr) Vector4(static_cast<float*>(data->At(0)));
}

#define REGISTER_CLASS_MANUAL_PART_Vector4() \
    /* explicit Vector4::Vector4(const float* data) noexcept | File: ../Math/Vector4.h */ \
    engine->RegisterObjectBehaviour("Vector4", asBEHAVE_CONSTRUCT, "void f(float[]&)", AS_FUNCTION_OBJLAST(Vector4_Vector4_Data), AS_CALL_CDECL_OBJLAST);

// const float* Vector4::Data() const | File: ../Math/Vector4.h
template <class T> CScriptArray* Vector4_Data(T* ptr)
{
    return BufferToArray<float>(ptr->Data(), 4, "float[]");
}

#define REGISTER_MEMBERS_MANUAL_PART_Vector4() \
    /* const float* Vector4::Data() const | File: ../Math/Vector4.h */ \
    engine->RegisterObjectMethod(className, "float[]& get_data() const", AS_FUNCTION_OBJLAST(Vector4_Data<T>), AS_CALL_CDECL_OBJLAST);

// ========================================================================================

// explicit IntRect::IntRect(const int* data) noexcept | File: ../Math/Rect.h
static void IntRect_IntRect_Data(CScriptArray* data, IntRect* ptr)
{
    new(ptr) IntRect(static_cast<int*>(data->At(0)));
}

#define REGISTER_CLASS_MANUAL_PART_IntRect() \
    /* explicit IntRect::IntRect(const int* data) noexcept | File: ../Math/Rect.h */ \
    engine->RegisterObjectBehaviour("IntRect", asBEHAVE_CONSTRUCT, "void f(int[]&)", AS_FUNCTION_OBJLAST(IntRect_IntRect_Data), AS_CALL_CDECL_OBJLAST);

// const int* IntRect::Data() const | File: ../Math/Rect.h
template <class T> CScriptArray* IntRect_Data(T* ptr)
{
    return BufferToArray<int>(ptr->Data(), 4, "int[]");
}

#define REGISTER_MEMBERS_MANUAL_PART_IntRect() \
    /* const int* IntRect::Data() const | File: ../Math/Rect.h */ \
    engine->RegisterObjectMethod(className, "int[]& get_data() const", AS_FUNCTION_OBJLAST(IntRect_Data<T>), AS_CALL_CDECL_OBJLAST);

// ========================================================================================

// explicit Color::Color(const float* data) noexcept | File: ../Math/Color.h
static void Color_Color_Data(CScriptArray* data, Color* ptr)
{
    new(ptr) Color(static_cast<float*>(data->At(0)));
}

#define REGISTER_CLASS_MANUAL_PART_Color() \
    /* explicit Color::Color(const float* data) noexcept | File: ../Math/Color.h */ \
    engine->RegisterObjectBehaviour("Color", asBEHAVE_CONSTRUCT, "void f(float[]&)", AS_FUNCTION_OBJLAST(Color_Color_Data), AS_CALL_CDECL_OBJLAST);

// const float* Color::Data() const | File: ../Math/Color.h
template <class T> CScriptArray* Color_Data(T* ptr)
{
    return BufferToArray<float>(ptr->Data(), 4, "float[]");
}

#define REGISTER_MEMBERS_MANUAL_PART_Color() \
    /* const float* Color::Data() const | File: ../Math/Color.h */ \
    engine->RegisterObjectMethod(className, "float[]& get_data() const", AS_FUNCTION_OBJLAST(Color_Data<T>), AS_CALL_CDECL_OBJLAST);

// ========================================================================================

// float Ray::HitDistance(const Vector3& v0, const Vector3& v1, const Vector3& v2, Vector3* outNormal = nullptr, Vector3* outBary = nullptr) const | File: ../Math/Ray.h
template <class T> float Ray_HitDistance(const Vector3& v0, const Vector3& v1, const Vector3& v2, T* ptr)
{
    return ptr->HitDistance(v0, v1, v2);
}

#define REGISTER_MEMBERS_MANUAL_PART_Ray() \
    /* float Ray::HitDistance(const Vector3& v0, const Vector3& v1, const Vector3& v2, Vector3* outNormal = nullptr, Vector3* outBary = nullptr) const | File: ../Math/Ray.h */ \
    engine->RegisterObjectMethod(className, "float HitDistance(const Vector3&in, const Vector3&in, const Vector3&in) const", AS_FUNCTION_OBJLAST(Ray_HitDistance<T>), AS_CALL_CDECL_OBJLAST);

// ========================================================================================

// Vector3 Frustum::vertices_[NUM_FRUSTUM_VERTICES] | File: ../Math/Frustum.h
template <class T> Vector3 Frustum_GetVertex(unsigned index, T* ptr)
{
    if (index >= NUM_FRUSTUM_VERTICES)
        return Vector3::ZERO;
    return ptr->vertices_[index];
}

#define REGISTER_MEMBERS_MANUAL_PART_Frustum() \
    /* Vector3 Frustum::vertices_[NUM_FRUSTUM_VERTICES] | File: ../Math/Frustum.h */ \
    engine->RegisterObjectMethod(className, "Vector3 get_vertices(uint) const", AS_FUNCTION_OBJLAST(Frustum_GetVertex<T>), AS_CALL_CDECL_OBJLAST);

// ========================================================================================

// Vector<PODVector<Vector3>> Polyhedron::faces_ | File: ../Math/Polyhedron.h
template <class T> unsigned Polyhedron_GetNumFaces(T* ptr)
{
    return ptr->faces_.Size();
}

// Vector<PODVector<Vector3>> Polyhedron::faces_ | File: ../Math/Polyhedron.h
template <class T> CScriptArray* Polyhedron_GetFace(unsigned index, T* ptr)
{
    PODVector<Vector3> face;
    if (index < ptr->faces_.Size())
        face = ptr->faces_[index];
    return VectorToArray<Vector3>(face, "Array<Vector3>");
}

#define REGISTER_MEMBERS_MANUAL_PART_Polyhedron() \
    /* Vector<PODVector<Vector3>> Polyhedron::faces_ | File: ../Math/Polyhedron.h */ \
    engine->RegisterObjectMethod(className, "uint get_numFaces() const", AS_FUNCTION_OBJLAST(Polyhedron_GetNumFaces<T>), AS_CALL_CDECL_OBJLAST); \
    engine->RegisterObjectMethod(className, "Array<Vector3>@ get_face(uint) const", AS_FUNCTION_OBJLAST(Polyhedron_GetFace<T>), AS_CALL_CDECL_OBJLAST);

}
