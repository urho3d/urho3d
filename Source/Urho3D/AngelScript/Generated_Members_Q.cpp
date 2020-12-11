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
    engine->RegisterObjectMethod("Quaternion", "float Angle() const", asMETHODPR(Quaternion, Angle, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("Quaternion", "float get_angle() const", asMETHODPR(Quaternion, Angle, () const, float), asCALL_THISCALL);
    // Vector3 Quaternion::Axis() const | File: ../Math/Quaternion.h
    engine->RegisterObjectMethod("Quaternion", "Vector3 Axis() const", asMETHODPR(Quaternion, Axis, () const, Vector3), asCALL_THISCALL);
    engine->RegisterObjectMethod("Quaternion", "Vector3 get_axis() const", asMETHODPR(Quaternion, Axis, () const, Vector3), asCALL_THISCALL);
    // Quaternion Quaternion::Conjugate() const | File: ../Math/Quaternion.h
    engine->RegisterObjectMethod("Quaternion", "Quaternion Conjugate() const", asMETHODPR(Quaternion, Conjugate, () const, Quaternion), asCALL_THISCALL);
    // const float* Quaternion::Data() const | File: ../Math/Quaternion.h
    // Error: type "const float*" can not automatically bind
    // float Quaternion::DotProduct(const Quaternion& rhs) const | File: ../Math/Quaternion.h
    engine->RegisterObjectMethod("Quaternion", "float DotProduct(const Quaternion&in) const", asMETHODPR(Quaternion, DotProduct, (const Quaternion&) const, float), asCALL_THISCALL);
    // bool Quaternion::Equals(const Quaternion& rhs) const | File: ../Math/Quaternion.h
    engine->RegisterObjectMethod("Quaternion", "bool Equals(const Quaternion&in) const", asMETHODPR(Quaternion, Equals, (const Quaternion&) const, bool), asCALL_THISCALL);
    // Vector3 Quaternion::EulerAngles() const | File: ../Math/Quaternion.h
    engine->RegisterObjectMethod("Quaternion", "Vector3 EulerAngles() const", asMETHODPR(Quaternion, EulerAngles, () const, Vector3), asCALL_THISCALL);
    engine->RegisterObjectMethod("Quaternion", "Vector3 get_eulerAngles() const", asMETHODPR(Quaternion, EulerAngles, () const, Vector3), asCALL_THISCALL);
    // void Quaternion::FromAngleAxis(float angle, const Vector3& axis) | File: ../Math/Quaternion.h
    engine->RegisterObjectMethod("Quaternion", "void FromAngleAxis(float, const Vector3&in)", asMETHODPR(Quaternion, FromAngleAxis, (float, const Vector3&), void), asCALL_THISCALL);
    // void Quaternion::FromAxes(const Vector3& xAxis, const Vector3& yAxis, const Vector3& zAxis) | File: ../Math/Quaternion.h
    engine->RegisterObjectMethod("Quaternion", "void FromAxes(const Vector3&in, const Vector3&in, const Vector3&in)", asMETHODPR(Quaternion, FromAxes, (const Vector3&, const Vector3&, const Vector3&), void), asCALL_THISCALL);
    // void Quaternion::FromEulerAngles(float x, float y, float z) | File: ../Math/Quaternion.h
    engine->RegisterObjectMethod("Quaternion", "void FromEulerAngles(float, float, float)", asMETHODPR(Quaternion, FromEulerAngles, (float, float, float), void), asCALL_THISCALL);
    // bool Quaternion::FromLookRotation(const Vector3& direction, const Vector3& up=Vector3::UP) | File: ../Math/Quaternion.h
    engine->RegisterObjectMethod("Quaternion", "bool FromLookRotation(const Vector3&in, const Vector3&in = Vector3::UP)", asMETHODPR(Quaternion, FromLookRotation, (const Vector3&, const Vector3&), bool), asCALL_THISCALL);
    // void Quaternion::FromRotationMatrix(const Matrix3& matrix) | File: ../Math/Quaternion.h
    engine->RegisterObjectMethod("Quaternion", "void FromRotationMatrix(const Matrix3&in)", asMETHODPR(Quaternion, FromRotationMatrix, (const Matrix3&), void), asCALL_THISCALL);
    // void Quaternion::FromRotationTo(const Vector3& start, const Vector3& end) | File: ../Math/Quaternion.h
    engine->RegisterObjectMethod("Quaternion", "void FromRotationTo(const Vector3&in, const Vector3&in)", asMETHODPR(Quaternion, FromRotationTo, (const Vector3&, const Vector3&), void), asCALL_THISCALL);
    // Quaternion Quaternion::Inverse() const | File: ../Math/Quaternion.h
    engine->RegisterObjectMethod("Quaternion", "Quaternion Inverse() const", asMETHODPR(Quaternion, Inverse, () const, Quaternion), asCALL_THISCALL);
    // bool Quaternion::IsInf() const | File: ../Math/Quaternion.h
    engine->RegisterObjectMethod("Quaternion", "bool IsInf() const", asMETHODPR(Quaternion, IsInf, () const, bool), asCALL_THISCALL);
    // bool Quaternion::IsNaN() const | File: ../Math/Quaternion.h
    engine->RegisterObjectMethod("Quaternion", "bool IsNaN() const", asMETHODPR(Quaternion, IsNaN, () const, bool), asCALL_THISCALL);
    // float Quaternion::LengthSquared() const | File: ../Math/Quaternion.h
    engine->RegisterObjectMethod("Quaternion", "float LengthSquared() const", asMETHODPR(Quaternion, LengthSquared, () const, float), asCALL_THISCALL);
    // Quaternion Quaternion::Nlerp(const Quaternion& rhs, float t, bool shortestPath=false) const | File: ../Math/Quaternion.h
    engine->RegisterObjectMethod("Quaternion", "Quaternion Nlerp(const Quaternion&in, float, bool = false) const", asMETHODPR(Quaternion, Nlerp, (const Quaternion&, float, bool) const, Quaternion), asCALL_THISCALL);
    // void Quaternion::Normalize() | File: ../Math/Quaternion.h
    engine->RegisterObjectMethod("Quaternion", "void Normalize()", asMETHODPR(Quaternion, Normalize, (), void), asCALL_THISCALL);
    // Quaternion Quaternion::Normalized() const | File: ../Math/Quaternion.h
    engine->RegisterObjectMethod("Quaternion", "Quaternion Normalized() const", asMETHODPR(Quaternion, Normalized, () const, Quaternion), asCALL_THISCALL);
    // Quaternion Quaternion::operator*(float rhs) const | File: ../Math/Quaternion.h
    engine->RegisterObjectMethod("Quaternion", "Quaternion opMul(float) const", asMETHODPR(Quaternion, operator*, (float) const, Quaternion), asCALL_THISCALL);
    // Quaternion Quaternion::operator*(const Quaternion& rhs) const | File: ../Math/Quaternion.h
    engine->RegisterObjectMethod("Quaternion", "Quaternion opMul(const Quaternion&in) const", asMETHODPR(Quaternion, operator*, (const Quaternion&) const, Quaternion), asCALL_THISCALL);
    // Vector3 Quaternion::operator*(const Vector3& rhs) const | File: ../Math/Quaternion.h
    engine->RegisterObjectMethod("Quaternion", "Vector3 opMul(const Vector3&in) const", asMETHODPR(Quaternion, operator*, (const Vector3&) const, Vector3), asCALL_THISCALL);
    // Quaternion& Quaternion::operator*=(float rhs) | File: ../Math/Quaternion.h
    engine->RegisterObjectMethod("Quaternion", "Quaternion& opMulAssign(float)", asMETHODPR(Quaternion, operator*=, (float), Quaternion&), asCALL_THISCALL);
    // Quaternion Quaternion::operator+(const Quaternion& rhs) const | File: ../Math/Quaternion.h
    engine->RegisterObjectMethod("Quaternion", "Quaternion opAdd(const Quaternion&in) const", asMETHODPR(Quaternion, operator+, (const Quaternion&) const, Quaternion), asCALL_THISCALL);
    // Quaternion& Quaternion::operator+=(const Quaternion& rhs) | File: ../Math/Quaternion.h
    engine->RegisterObjectMethod("Quaternion", "Quaternion& opAddAssign(const Quaternion&in)", asMETHODPR(Quaternion, operator+=, (const Quaternion&), Quaternion&), asCALL_THISCALL);
    // Quaternion Quaternion::operator-() const | File: ../Math/Quaternion.h
    engine->RegisterObjectMethod("Quaternion", "Quaternion opNeg() const", asMETHODPR(Quaternion, operator-, () const, Quaternion), asCALL_THISCALL);
    // Quaternion Quaternion::operator-(const Quaternion& rhs) const | File: ../Math/Quaternion.h
    engine->RegisterObjectMethod("Quaternion", "Quaternion opSub(const Quaternion&in) const", asMETHODPR(Quaternion, operator-, (const Quaternion&) const, Quaternion), asCALL_THISCALL);
    // Quaternion& Quaternion::operator=(const Quaternion& rhs) noexcept | File: ../Math/Quaternion.h
    engine->RegisterObjectMethod("Quaternion", "Quaternion& opAssign(const Quaternion&in)", asMETHODPR(Quaternion, operator=, (const Quaternion&), Quaternion&), asCALL_THISCALL);
    // bool Quaternion::operator==(const Quaternion& rhs) const | File: ../Math/Quaternion.h
    engine->RegisterObjectMethod("Quaternion", "bool opEquals(const Quaternion&in) const", asMETHODPR(Quaternion, operator==, (const Quaternion&) const, bool), asCALL_THISCALL);
    // float Quaternion::PitchAngle() const | File: ../Math/Quaternion.h
    engine->RegisterObjectMethod("Quaternion", "float PitchAngle() const", asMETHODPR(Quaternion, PitchAngle, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("Quaternion", "float get_pitch() const", asMETHODPR(Quaternion, PitchAngle, () const, float), asCALL_THISCALL);
    // Quaternion::Quaternion(const Quaternion& quat) noexcept | File: ../Math/Quaternion.h
    engine->RegisterObjectBehaviour("Quaternion", asBEHAVE_CONSTRUCT, "void f(const Quaternion&in)", asFUNCTION(Quaternion_Quaternion_Quaternion), asCALL_CDECL_OBJFIRST);
    // Quaternion::Quaternion(float w, float x, float y, float z) noexcept | File: ../Math/Quaternion.h
    engine->RegisterObjectBehaviour("Quaternion", asBEHAVE_CONSTRUCT, "void f(float, float, float, float)", asFUNCTION(Quaternion_Quaternion_float_float_float_float), asCALL_CDECL_OBJFIRST);
    // explicit Quaternion::Quaternion(const float* data) noexcept | File: ../Math/Quaternion.h
    // Error: type "const float*" can not automatically bind
    // Quaternion::Quaternion(float angle, const Vector3& axis) noexcept | File: ../Math/Quaternion.h
    engine->RegisterObjectBehaviour("Quaternion", asBEHAVE_CONSTRUCT, "void f(float, const Vector3&in)", asFUNCTION(Quaternion_Quaternion_float_Vector3), asCALL_CDECL_OBJFIRST);
    // explicit Quaternion::Quaternion(float angle) noexcept | File: ../Math/Quaternion.h
    engine->RegisterObjectBehaviour("Quaternion", asBEHAVE_CONSTRUCT, "void f(float)", asFUNCTION(Quaternion_Quaternion_float), asCALL_CDECL_OBJFIRST);
    // Quaternion::Quaternion(float x, float y, float z) noexcept | File: ../Math/Quaternion.h
    engine->RegisterObjectBehaviour("Quaternion", asBEHAVE_CONSTRUCT, "void f(float, float, float)", asFUNCTION(Quaternion_Quaternion_float_float_float), asCALL_CDECL_OBJFIRST);
    // explicit Quaternion::Quaternion(const Vector3& angles) noexcept | File: ../Math/Quaternion.h
    engine->RegisterObjectBehaviour("Quaternion", asBEHAVE_CONSTRUCT, "void f(const Vector3&in)", asFUNCTION(Quaternion_Quaternion_Vector3), asCALL_CDECL_OBJFIRST);
    // Quaternion::Quaternion(const Vector3& start, const Vector3& end) noexcept | File: ../Math/Quaternion.h
    engine->RegisterObjectBehaviour("Quaternion", asBEHAVE_CONSTRUCT, "void f(const Vector3&in, const Vector3&in)", asFUNCTION(Quaternion_Quaternion_Vector3_Vector3), asCALL_CDECL_OBJFIRST);
    // Quaternion::Quaternion(const Vector3& xAxis, const Vector3& yAxis, const Vector3& zAxis) noexcept | File: ../Math/Quaternion.h
    engine->RegisterObjectBehaviour("Quaternion", asBEHAVE_CONSTRUCT, "void f(const Vector3&in, const Vector3&in, const Vector3&in)", asFUNCTION(Quaternion_Quaternion_Vector3_Vector3_Vector3), asCALL_CDECL_OBJFIRST);
    // explicit Quaternion::Quaternion(const Matrix3& matrix) noexcept | File: ../Math/Quaternion.h
    engine->RegisterObjectBehaviour("Quaternion", asBEHAVE_CONSTRUCT, "void f(const Matrix3&in)", asFUNCTION(Quaternion_Quaternion_Matrix3), asCALL_CDECL_OBJFIRST);
    // float Quaternion::RollAngle() const | File: ../Math/Quaternion.h
    engine->RegisterObjectMethod("Quaternion", "float RollAngle() const", asMETHODPR(Quaternion, RollAngle, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("Quaternion", "float get_roll() const", asMETHODPR(Quaternion, RollAngle, () const, float), asCALL_THISCALL);
    // Matrix3 Quaternion::RotationMatrix() const | File: ../Math/Quaternion.h
    engine->RegisterObjectMethod("Quaternion", "Matrix3 RotationMatrix() const", asMETHODPR(Quaternion, RotationMatrix, () const, Matrix3), asCALL_THISCALL);
    engine->RegisterObjectMethod("Quaternion", "Matrix3 get_rotationMatrix() const", asMETHODPR(Quaternion, RotationMatrix, () const, Matrix3), asCALL_THISCALL);
    // Quaternion Quaternion::Slerp(const Quaternion& rhs, float t) const | File: ../Math/Quaternion.h
    engine->RegisterObjectMethod("Quaternion", "Quaternion Slerp(const Quaternion&in, float) const", asMETHODPR(Quaternion, Slerp, (const Quaternion&, float) const, Quaternion), asCALL_THISCALL);
    // String Quaternion::ToString() const | File: ../Math/Quaternion.h
    engine->RegisterObjectMethod("Quaternion", "String ToString() const", asMETHODPR(Quaternion, ToString, () const, String), asCALL_THISCALL);
    // float Quaternion::YawAngle() const | File: ../Math/Quaternion.h
    engine->RegisterObjectMethod("Quaternion", "float YawAngle() const", asMETHODPR(Quaternion, YawAngle, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("Quaternion", "float get_yaw() const", asMETHODPR(Quaternion, YawAngle, () const, float), asCALL_THISCALL);
#ifdef REGISTER_MANUAL_PART_Quaternion
    REGISTER_MANUAL_PART_Quaternion(Quaternion, "Quaternion")
#endif

}

}
