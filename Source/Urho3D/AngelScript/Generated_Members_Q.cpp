// DO NOT EDIT. This file is generated

#include "../Precompiled.h"
#include "../AngelScript/APITemplates.h"

#include "../AngelScript/GeneratedIncludes.h"
#include "../AngelScript/Manual.h"

namespace Urho3D
{

void FakeAddRef(void* ptr);
void FakeReleaseRef(void* ptr);

// Quaternion::Quaternion(const Quaternion& quat) noexcept | File: ../Math/Quaternion.h
static void Quaternion_Quaternion_Quaternion(Quaternion* ptr, const Quaternion &quat)
{
    new(ptr) Quaternion(quat);
}

// Quaternion::Quaternion(float w, float x, float y, float z) noexcept | File: ../Math/Quaternion.h
static void Quaternion_Quaternion_float_float_float_float(Quaternion* ptr, float w, float x, float y, float z)
{
    new(ptr) Quaternion(w, x, y, z);
}

// Quaternion::Quaternion(float angle, const Vector3& axis) noexcept | File: ../Math/Quaternion.h
static void Quaternion_Quaternion_float_Vector3(Quaternion* ptr, float angle, const Vector3 &axis)
{
    new(ptr) Quaternion(angle, axis);
}

// explicit Quaternion::Quaternion(float angle) noexcept | File: ../Math/Quaternion.h
static void Quaternion_Quaternion_float(Quaternion* ptr, float angle)
{
    new(ptr) Quaternion(angle);
}

// Quaternion::Quaternion(float x, float y, float z) noexcept | File: ../Math/Quaternion.h
static void Quaternion_Quaternion_float_float_float(Quaternion* ptr, float x, float y, float z)
{
    new(ptr) Quaternion(x, y, z);
}

// explicit Quaternion::Quaternion(const Vector3& angles) noexcept | File: ../Math/Quaternion.h
static void Quaternion_Quaternion_Vector3(Quaternion* ptr, const Vector3 &angles)
{
    new(ptr) Quaternion(angles);
}

// Quaternion::Quaternion(const Vector3& start, const Vector3& end) noexcept | File: ../Math/Quaternion.h
static void Quaternion_Quaternion_Vector3_Vector3(Quaternion* ptr, const Vector3 &start, const Vector3 &end)
{
    new(ptr) Quaternion(start, end);
}

// Quaternion::Quaternion(const Vector3& xAxis, const Vector3& yAxis, const Vector3& zAxis) noexcept | File: ../Math/Quaternion.h
static void Quaternion_Quaternion_Vector3_Vector3_Vector3(Quaternion* ptr, const Vector3 &xAxis, const Vector3 &yAxis, const Vector3 &zAxis)
{
    new(ptr) Quaternion(xAxis, yAxis, zAxis);
}

// explicit Quaternion::Quaternion(const Matrix3& matrix) noexcept | File: ../Math/Quaternion.h
static void Quaternion_Quaternion_Matrix3(Quaternion* ptr, const Matrix3 &matrix)
{
    new(ptr) Quaternion(matrix);
}

void ASRegisterGenerated_Members_Q(asIScriptEngine* engine)
{
    // const Quaternion Quaternion::IDENTITY | File: ../Math/Quaternion.h
    engine->SetDefaultNamespace("Quaternion");
    engine->RegisterGlobalProperty("const Quaternion IDENTITY", (void*)&Quaternion::IDENTITY);
    engine->SetDefaultNamespace("");
    // float Quaternion::w_ | File: ../Math/Quaternion.h
    engine->RegisterObjectProperty("Quaternion", "float w", offsetof(Quaternion, w_));
    // float Quaternion::x_ | File: ../Math/Quaternion.h
    engine->RegisterObjectProperty("Quaternion", "float x", offsetof(Quaternion, x_));
    // float Quaternion::y_ | File: ../Math/Quaternion.h
    engine->RegisterObjectProperty("Quaternion", "float y", offsetof(Quaternion, y_));
    // float Quaternion::z_ | File: ../Math/Quaternion.h
    engine->RegisterObjectProperty("Quaternion", "float z", offsetof(Quaternion, z_));
    // float Quaternion::Angle() const | File: ../Math/Quaternion.h
    engine->RegisterObjectMethod("Quaternion", "float Angle() const", AS_METHODPR(Quaternion, Angle, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Quaternion", "float get_angle() const", AS_METHODPR(Quaternion, Angle, () const, float), AS_CALL_THISCALL);
    // Vector3 Quaternion::Axis() const | File: ../Math/Quaternion.h
    engine->RegisterObjectMethod("Quaternion", "Vector3 Axis() const", AS_METHODPR(Quaternion, Axis, () const, Vector3), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Quaternion", "Vector3 get_axis() const", AS_METHODPR(Quaternion, Axis, () const, Vector3), AS_CALL_THISCALL);
    // Quaternion Quaternion::Conjugate() const | File: ../Math/Quaternion.h
    engine->RegisterObjectMethod("Quaternion", "Quaternion Conjugate() const", AS_METHODPR(Quaternion, Conjugate, () const, Quaternion), AS_CALL_THISCALL);
    // const float* Quaternion::Data() const | File: ../Math/Quaternion.h
    // Error: type "const float*" can not automatically bind
    // float Quaternion::DotProduct(const Quaternion& rhs) const | File: ../Math/Quaternion.h
    engine->RegisterObjectMethod("Quaternion", "float DotProduct(const Quaternion&in) const", AS_METHODPR(Quaternion, DotProduct, (const Quaternion&) const, float), AS_CALL_THISCALL);
    // bool Quaternion::Equals(const Quaternion& rhs) const | File: ../Math/Quaternion.h
    engine->RegisterObjectMethod("Quaternion", "bool Equals(const Quaternion&in) const", AS_METHODPR(Quaternion, Equals, (const Quaternion&) const, bool), AS_CALL_THISCALL);
    // Vector3 Quaternion::EulerAngles() const | File: ../Math/Quaternion.h
    engine->RegisterObjectMethod("Quaternion", "Vector3 EulerAngles() const", AS_METHODPR(Quaternion, EulerAngles, () const, Vector3), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Quaternion", "Vector3 get_eulerAngles() const", AS_METHODPR(Quaternion, EulerAngles, () const, Vector3), AS_CALL_THISCALL);
    // void Quaternion::FromAngleAxis(float angle, const Vector3& axis) | File: ../Math/Quaternion.h
    engine->RegisterObjectMethod("Quaternion", "void FromAngleAxis(float, const Vector3&in)", AS_METHODPR(Quaternion, FromAngleAxis, (float, const Vector3&), void), AS_CALL_THISCALL);
    // void Quaternion::FromAxes(const Vector3& xAxis, const Vector3& yAxis, const Vector3& zAxis) | File: ../Math/Quaternion.h
    engine->RegisterObjectMethod("Quaternion", "void FromAxes(const Vector3&in, const Vector3&in, const Vector3&in)", AS_METHODPR(Quaternion, FromAxes, (const Vector3&, const Vector3&, const Vector3&), void), AS_CALL_THISCALL);
    // void Quaternion::FromEulerAngles(float x, float y, float z) | File: ../Math/Quaternion.h
    engine->RegisterObjectMethod("Quaternion", "void FromEulerAngles(float, float, float)", AS_METHODPR(Quaternion, FromEulerAngles, (float, float, float), void), AS_CALL_THISCALL);
    // bool Quaternion::FromLookRotation(const Vector3& direction, const Vector3& up=Vector3::UP) | File: ../Math/Quaternion.h
    engine->RegisterObjectMethod("Quaternion", "bool FromLookRotation(const Vector3&in, const Vector3&in = Vector3::UP)", AS_METHODPR(Quaternion, FromLookRotation, (const Vector3&, const Vector3&), bool), AS_CALL_THISCALL);
    // void Quaternion::FromRotationMatrix(const Matrix3& matrix) | File: ../Math/Quaternion.h
    engine->RegisterObjectMethod("Quaternion", "void FromRotationMatrix(const Matrix3&in)", AS_METHODPR(Quaternion, FromRotationMatrix, (const Matrix3&), void), AS_CALL_THISCALL);
    // void Quaternion::FromRotationTo(const Vector3& start, const Vector3& end) | File: ../Math/Quaternion.h
    engine->RegisterObjectMethod("Quaternion", "void FromRotationTo(const Vector3&in, const Vector3&in)", AS_METHODPR(Quaternion, FromRotationTo, (const Vector3&, const Vector3&), void), AS_CALL_THISCALL);
    // Quaternion Quaternion::Inverse() const | File: ../Math/Quaternion.h
    engine->RegisterObjectMethod("Quaternion", "Quaternion Inverse() const", AS_METHODPR(Quaternion, Inverse, () const, Quaternion), AS_CALL_THISCALL);
    // bool Quaternion::IsInf() const | File: ../Math/Quaternion.h
    engine->RegisterObjectMethod("Quaternion", "bool IsInf() const", AS_METHODPR(Quaternion, IsInf, () const, bool), AS_CALL_THISCALL);
    // bool Quaternion::IsNaN() const | File: ../Math/Quaternion.h
    engine->RegisterObjectMethod("Quaternion", "bool IsNaN() const", AS_METHODPR(Quaternion, IsNaN, () const, bool), AS_CALL_THISCALL);
    // float Quaternion::LengthSquared() const | File: ../Math/Quaternion.h
    engine->RegisterObjectMethod("Quaternion", "float LengthSquared() const", AS_METHODPR(Quaternion, LengthSquared, () const, float), AS_CALL_THISCALL);
    // Quaternion Quaternion::Nlerp(const Quaternion& rhs, float t, bool shortestPath=false) const | File: ../Math/Quaternion.h
    engine->RegisterObjectMethod("Quaternion", "Quaternion Nlerp(const Quaternion&in, float, bool = false) const", AS_METHODPR(Quaternion, Nlerp, (const Quaternion&, float, bool) const, Quaternion), AS_CALL_THISCALL);
    // void Quaternion::Normalize() | File: ../Math/Quaternion.h
    engine->RegisterObjectMethod("Quaternion", "void Normalize()", AS_METHODPR(Quaternion, Normalize, (), void), AS_CALL_THISCALL);
    // Quaternion Quaternion::Normalized() const | File: ../Math/Quaternion.h
    engine->RegisterObjectMethod("Quaternion", "Quaternion Normalized() const", AS_METHODPR(Quaternion, Normalized, () const, Quaternion), AS_CALL_THISCALL);
    // Quaternion Quaternion::operator*(float rhs) const | File: ../Math/Quaternion.h
    engine->RegisterObjectMethod("Quaternion", "Quaternion opMul(float) const", AS_METHODPR(Quaternion, operator*, (float) const, Quaternion), AS_CALL_THISCALL);
    // Quaternion Quaternion::operator*(const Quaternion& rhs) const | File: ../Math/Quaternion.h
    engine->RegisterObjectMethod("Quaternion", "Quaternion opMul(const Quaternion&in) const", AS_METHODPR(Quaternion, operator*, (const Quaternion&) const, Quaternion), AS_CALL_THISCALL);
    // Vector3 Quaternion::operator*(const Vector3& rhs) const | File: ../Math/Quaternion.h
    engine->RegisterObjectMethod("Quaternion", "Vector3 opMul(const Vector3&in) const", AS_METHODPR(Quaternion, operator*, (const Vector3&) const, Vector3), AS_CALL_THISCALL);
    // Quaternion& Quaternion::operator*=(float rhs) | File: ../Math/Quaternion.h
    engine->RegisterObjectMethod("Quaternion", "Quaternion& opMulAssign(float)", AS_METHODPR(Quaternion, operator*=, (float), Quaternion&), AS_CALL_THISCALL);
    // Quaternion Quaternion::operator+(const Quaternion& rhs) const | File: ../Math/Quaternion.h
    engine->RegisterObjectMethod("Quaternion", "Quaternion opAdd(const Quaternion&in) const", AS_METHODPR(Quaternion, operator+, (const Quaternion&) const, Quaternion), AS_CALL_THISCALL);
    // Quaternion& Quaternion::operator+=(const Quaternion& rhs) | File: ../Math/Quaternion.h
    engine->RegisterObjectMethod("Quaternion", "Quaternion& opAddAssign(const Quaternion&in)", AS_METHODPR(Quaternion, operator+=, (const Quaternion&), Quaternion&), AS_CALL_THISCALL);
    // Quaternion Quaternion::operator-() const | File: ../Math/Quaternion.h
    engine->RegisterObjectMethod("Quaternion", "Quaternion opNeg() const", AS_METHODPR(Quaternion, operator-, () const, Quaternion), AS_CALL_THISCALL);
    // Quaternion Quaternion::operator-(const Quaternion& rhs) const | File: ../Math/Quaternion.h
    engine->RegisterObjectMethod("Quaternion", "Quaternion opSub(const Quaternion&in) const", AS_METHODPR(Quaternion, operator-, (const Quaternion&) const, Quaternion), AS_CALL_THISCALL);
    // Quaternion& Quaternion::operator=(const Quaternion& rhs) noexcept | File: ../Math/Quaternion.h
    engine->RegisterObjectMethod("Quaternion", "Quaternion& opAssign(const Quaternion&in)", AS_METHODPR(Quaternion, operator=, (const Quaternion&), Quaternion&), AS_CALL_THISCALL);
    // bool Quaternion::operator==(const Quaternion& rhs) const | File: ../Math/Quaternion.h
    engine->RegisterObjectMethod("Quaternion", "bool opEquals(const Quaternion&in) const", AS_METHODPR(Quaternion, operator==, (const Quaternion&) const, bool), AS_CALL_THISCALL);
    // float Quaternion::PitchAngle() const | File: ../Math/Quaternion.h
    engine->RegisterObjectMethod("Quaternion", "float PitchAngle() const", AS_METHODPR(Quaternion, PitchAngle, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Quaternion", "float get_pitch() const", AS_METHODPR(Quaternion, PitchAngle, () const, float), AS_CALL_THISCALL);
    // Quaternion::Quaternion(const Quaternion& quat) noexcept | File: ../Math/Quaternion.h
    engine->RegisterObjectBehaviour("Quaternion", asBEHAVE_CONSTRUCT, "void f(const Quaternion&in)", AS_FUNCTION_OBJFIRST(Quaternion_Quaternion_Quaternion), AS_CALL_CDECL_OBJFIRST);
    // Quaternion::Quaternion(float w, float x, float y, float z) noexcept | File: ../Math/Quaternion.h
    engine->RegisterObjectBehaviour("Quaternion", asBEHAVE_CONSTRUCT, "void f(float, float, float, float)", AS_FUNCTION_OBJFIRST(Quaternion_Quaternion_float_float_float_float), AS_CALL_CDECL_OBJFIRST);
    // explicit Quaternion::Quaternion(const float* data) noexcept | File: ../Math/Quaternion.h
    // Error: type "const float*" can not automatically bind
    // Quaternion::Quaternion(float angle, const Vector3& axis) noexcept | File: ../Math/Quaternion.h
    engine->RegisterObjectBehaviour("Quaternion", asBEHAVE_CONSTRUCT, "void f(float, const Vector3&in)", AS_FUNCTION_OBJFIRST(Quaternion_Quaternion_float_Vector3), AS_CALL_CDECL_OBJFIRST);
    // explicit Quaternion::Quaternion(float angle) noexcept | File: ../Math/Quaternion.h
    engine->RegisterObjectBehaviour("Quaternion", asBEHAVE_CONSTRUCT, "void f(float)", AS_FUNCTION_OBJFIRST(Quaternion_Quaternion_float), AS_CALL_CDECL_OBJFIRST);
    // Quaternion::Quaternion(float x, float y, float z) noexcept | File: ../Math/Quaternion.h
    engine->RegisterObjectBehaviour("Quaternion", asBEHAVE_CONSTRUCT, "void f(float, float, float)", AS_FUNCTION_OBJFIRST(Quaternion_Quaternion_float_float_float), AS_CALL_CDECL_OBJFIRST);
    // explicit Quaternion::Quaternion(const Vector3& angles) noexcept | File: ../Math/Quaternion.h
    engine->RegisterObjectBehaviour("Quaternion", asBEHAVE_CONSTRUCT, "void f(const Vector3&in)", AS_FUNCTION_OBJFIRST(Quaternion_Quaternion_Vector3), AS_CALL_CDECL_OBJFIRST);
    // Quaternion::Quaternion(const Vector3& start, const Vector3& end) noexcept | File: ../Math/Quaternion.h
    engine->RegisterObjectBehaviour("Quaternion", asBEHAVE_CONSTRUCT, "void f(const Vector3&in, const Vector3&in)", AS_FUNCTION_OBJFIRST(Quaternion_Quaternion_Vector3_Vector3), AS_CALL_CDECL_OBJFIRST);
    // Quaternion::Quaternion(const Vector3& xAxis, const Vector3& yAxis, const Vector3& zAxis) noexcept | File: ../Math/Quaternion.h
    engine->RegisterObjectBehaviour("Quaternion", asBEHAVE_CONSTRUCT, "void f(const Vector3&in, const Vector3&in, const Vector3&in)", AS_FUNCTION_OBJFIRST(Quaternion_Quaternion_Vector3_Vector3_Vector3), AS_CALL_CDECL_OBJFIRST);
    // explicit Quaternion::Quaternion(const Matrix3& matrix) noexcept | File: ../Math/Quaternion.h
    engine->RegisterObjectBehaviour("Quaternion", asBEHAVE_CONSTRUCT, "void f(const Matrix3&in)", AS_FUNCTION_OBJFIRST(Quaternion_Quaternion_Matrix3), AS_CALL_CDECL_OBJFIRST);
    // float Quaternion::RollAngle() const | File: ../Math/Quaternion.h
    engine->RegisterObjectMethod("Quaternion", "float RollAngle() const", AS_METHODPR(Quaternion, RollAngle, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Quaternion", "float get_roll() const", AS_METHODPR(Quaternion, RollAngle, () const, float), AS_CALL_THISCALL);
    // Matrix3 Quaternion::RotationMatrix() const | File: ../Math/Quaternion.h
    engine->RegisterObjectMethod("Quaternion", "Matrix3 RotationMatrix() const", AS_METHODPR(Quaternion, RotationMatrix, () const, Matrix3), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Quaternion", "Matrix3 get_rotationMatrix() const", AS_METHODPR(Quaternion, RotationMatrix, () const, Matrix3), AS_CALL_THISCALL);
    // Quaternion Quaternion::Slerp(const Quaternion& rhs, float t) const | File: ../Math/Quaternion.h
    engine->RegisterObjectMethod("Quaternion", "Quaternion Slerp(const Quaternion&in, float) const", AS_METHODPR(Quaternion, Slerp, (const Quaternion&, float) const, Quaternion), AS_CALL_THISCALL);
    // String Quaternion::ToString() const | File: ../Math/Quaternion.h
    engine->RegisterObjectMethod("Quaternion", "String ToString() const", AS_METHODPR(Quaternion, ToString, () const, String), AS_CALL_THISCALL);
    // float Quaternion::YawAngle() const | File: ../Math/Quaternion.h
    engine->RegisterObjectMethod("Quaternion", "float YawAngle() const", AS_METHODPR(Quaternion, YawAngle, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Quaternion", "float get_yaw() const", AS_METHODPR(Quaternion, YawAngle, () const, float), AS_CALL_THISCALL);
#ifdef REGISTER_MANUAL_PART_Quaternion
    REGISTER_MANUAL_PART_Quaternion(Quaternion, "Quaternion")
#endif

}

}
