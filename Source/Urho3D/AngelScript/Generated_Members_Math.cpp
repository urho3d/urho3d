// DO NOT EDIT. This file is generated

#include "../Precompiled.h"
#include "../AngelScript/APITemplates.h"

#include "../AngelScript/GeneratedIncludes.h"
#include "../AngelScript/GeneratedClassMembers.h"
#include "../AngelScript/Manual.h"

namespace Urho3D
{

// class AreaAllocator | File: ../Math/AreaAllocator.h
void CollectMembers_AreaAllocator(MemberCollection& members)
{
}

// class BoundingBox | File: ../Math/BoundingBox.h
void CollectMembers_BoundingBox(MemberCollection& members)
{
    // void BoundingBox::Define(const Vector3* vertices, unsigned count)
    // Error: type "const Vector3*" can not automatically bind
    // void BoundingBox::Merge(const Vector3* vertices, unsigned count)
    // Error: type "const Vector3*" can not automatically bind
    // bool BoundingBox::operator !=(const BoundingBox& rhs) const
    // Only operator == is needed

    members.fields_.Push(RegisterObjectPropertyArgs("Vector3 BoundingBox::min_", "Vector3 min", offsetof(BoundingBox, min_)));
    members.fields_.Push(RegisterObjectPropertyArgs("float BoundingBox::dummyMin_", "float dummyMin", offsetof(BoundingBox, dummyMin_)));
    members.fields_.Push(RegisterObjectPropertyArgs("Vector3 BoundingBox::max_", "Vector3 max", offsetof(BoundingBox, max_)));
    members.fields_.Push(RegisterObjectPropertyArgs("float BoundingBox::dummyMax_", "float dummyMax", offsetof(BoundingBox, dummyMax_)));

}

// class Color | File: ../Math/Color.h
void CollectMembers_Color(MemberCollection& members)
{
    // void Color::Bounds(float* min, float* max, bool clipped = false) const
    // Error: type "float*" can not automatically bind
    // const float* Color::Data() const
    // Error: type "const float*" can not automatically bind
    // void Color::FromUIntMask(unsigned color, const ChannelMask& mask)
    // Error: type "const ChannelMask&" can not automatically bind
    // unsigned Color::ToUIntMask(const ChannelMask& mask) const
    // Error: type "const ChannelMask&" can not automatically bind
    // bool Color::operator !=(const Color& rhs) const
    // Only operator == is needed

    members.fields_.Push(RegisterObjectPropertyArgs("float Color::r_", "float r", offsetof(Color, r_)));
    members.fields_.Push(RegisterObjectPropertyArgs("float Color::g_", "float g", offsetof(Color, g_)));
    members.fields_.Push(RegisterObjectPropertyArgs("float Color::b_", "float b", offsetof(Color, b_)));
    members.fields_.Push(RegisterObjectPropertyArgs("float Color::a_", "float a", offsetof(Color, a_)));

    // static const ChannelMask Color::ABGR
    // Error: type "const ChannelMask" can not automatically bind
    // static const ChannelMask Color::ARGB
    // Error: type "const ChannelMask" can not automatically bind

    members.staticFields_.Push(RegisterGlobalPropertyArgs("static const Color Color::WHITE", "const Color WHITE", (void*)&Color::WHITE));
    members.staticFields_.Push(RegisterGlobalPropertyArgs("static const Color Color::GRAY", "const Color GRAY", (void*)&Color::GRAY));
    members.staticFields_.Push(RegisterGlobalPropertyArgs("static const Color Color::BLACK", "const Color BLACK", (void*)&Color::BLACK));
    members.staticFields_.Push(RegisterGlobalPropertyArgs("static const Color Color::RED", "const Color RED", (void*)&Color::RED));
    members.staticFields_.Push(RegisterGlobalPropertyArgs("static const Color Color::GREEN", "const Color GREEN", (void*)&Color::GREEN));
    members.staticFields_.Push(RegisterGlobalPropertyArgs("static const Color Color::BLUE", "const Color BLUE", (void*)&Color::BLUE));
    members.staticFields_.Push(RegisterGlobalPropertyArgs("static const Color Color::CYAN", "const Color CYAN", (void*)&Color::CYAN));
    members.staticFields_.Push(RegisterGlobalPropertyArgs("static const Color Color::MAGENTA", "const Color MAGENTA", (void*)&Color::MAGENTA));
    members.staticFields_.Push(RegisterGlobalPropertyArgs("static const Color Color::YELLOW", "const Color YELLOW", (void*)&Color::YELLOW));
    members.staticFields_.Push(RegisterGlobalPropertyArgs("static const Color Color::TRANSPARENT_BLACK", "const Color TRANSPARENT_BLACK", (void*)&Color::TRANSPARENT_BLACK));

}

// class Frustum | File: ../Math/Frustum.h
void CollectMembers_Frustum(MemberCollection& members)
{
    // Plane Frustum::planes_[NUM_FRUSTUM_PLANES]
    // Not registered because array
    // Vector3 Frustum::vertices_[NUM_FRUSTUM_VERTICES]
    // Not registered because array

}

// class IntRect | File: ../Math/Rect.h
void CollectMembers_IntRect(MemberCollection& members)
{
    // const int* IntRect::Data() const
    // Error: type "const int*" can not automatically bind
    // bool IntRect::operator !=(const IntRect& rhs) const
    // Only operator == is needed

    members.fields_.Push(RegisterObjectPropertyArgs("int IntRect::left_", "int left", offsetof(IntRect, left_)));
    members.fields_.Push(RegisterObjectPropertyArgs("int IntRect::top_", "int top", offsetof(IntRect, top_)));
    members.fields_.Push(RegisterObjectPropertyArgs("int IntRect::right_", "int right", offsetof(IntRect, right_)));
    members.fields_.Push(RegisterObjectPropertyArgs("int IntRect::bottom_", "int bottom", offsetof(IntRect, bottom_)));

    members.staticFields_.Push(RegisterGlobalPropertyArgs("static const IntRect IntRect::ZERO", "const IntRect ZERO", (void*)&IntRect::ZERO));

}

// class IntVector2 | File: ../Math/Vector2.h
void CollectMembers_IntVector2(MemberCollection& members)
{
    // const int* IntVector2::Data() const
    // Error: type "const int*" can not automatically bind
    // bool IntVector2::operator !=(const IntVector2& rhs) const
    // Only operator == is needed

    members.fields_.Push(RegisterObjectPropertyArgs("int IntVector2::x_", "int x", offsetof(IntVector2, x_)));
    members.fields_.Push(RegisterObjectPropertyArgs("int IntVector2::y_", "int y", offsetof(IntVector2, y_)));

    members.staticFields_.Push(RegisterGlobalPropertyArgs("static const IntVector2 IntVector2::ZERO", "const IntVector2 ZERO", (void*)&IntVector2::ZERO));
    members.staticFields_.Push(RegisterGlobalPropertyArgs("static const IntVector2 IntVector2::LEFT", "const IntVector2 LEFT", (void*)&IntVector2::LEFT));
    members.staticFields_.Push(RegisterGlobalPropertyArgs("static const IntVector2 IntVector2::RIGHT", "const IntVector2 RIGHT", (void*)&IntVector2::RIGHT));
    members.staticFields_.Push(RegisterGlobalPropertyArgs("static const IntVector2 IntVector2::UP", "const IntVector2 UP", (void*)&IntVector2::UP));
    members.staticFields_.Push(RegisterGlobalPropertyArgs("static const IntVector2 IntVector2::DOWN", "const IntVector2 DOWN", (void*)&IntVector2::DOWN));
    members.staticFields_.Push(RegisterGlobalPropertyArgs("static const IntVector2 IntVector2::ONE", "const IntVector2 ONE", (void*)&IntVector2::ONE));

}

// class IntVector3 | File: ../Math/Vector3.h
void CollectMembers_IntVector3(MemberCollection& members)
{
    // const int* IntVector3::Data() const
    // Error: type "const int*" can not automatically bind
    // bool IntVector3::operator !=(const IntVector3& rhs) const
    // Only operator == is needed

    members.fields_.Push(RegisterObjectPropertyArgs("int IntVector3::x_", "int x", offsetof(IntVector3, x_)));
    members.fields_.Push(RegisterObjectPropertyArgs("int IntVector3::y_", "int y", offsetof(IntVector3, y_)));
    members.fields_.Push(RegisterObjectPropertyArgs("int IntVector3::z_", "int z", offsetof(IntVector3, z_)));

    members.staticFields_.Push(RegisterGlobalPropertyArgs("static const IntVector3 IntVector3::ZERO", "const IntVector3 ZERO", (void*)&IntVector3::ZERO));
    members.staticFields_.Push(RegisterGlobalPropertyArgs("static const IntVector3 IntVector3::LEFT", "const IntVector3 LEFT", (void*)&IntVector3::LEFT));
    members.staticFields_.Push(RegisterGlobalPropertyArgs("static const IntVector3 IntVector3::RIGHT", "const IntVector3 RIGHT", (void*)&IntVector3::RIGHT));
    members.staticFields_.Push(RegisterGlobalPropertyArgs("static const IntVector3 IntVector3::UP", "const IntVector3 UP", (void*)&IntVector3::UP));
    members.staticFields_.Push(RegisterGlobalPropertyArgs("static const IntVector3 IntVector3::DOWN", "const IntVector3 DOWN", (void*)&IntVector3::DOWN));
    members.staticFields_.Push(RegisterGlobalPropertyArgs("static const IntVector3 IntVector3::FORWARD", "const IntVector3 FORWARD", (void*)&IntVector3::FORWARD));
    members.staticFields_.Push(RegisterGlobalPropertyArgs("static const IntVector3 IntVector3::BACK", "const IntVector3 BACK", (void*)&IntVector3::BACK));
    members.staticFields_.Push(RegisterGlobalPropertyArgs("static const IntVector3 IntVector3::ONE", "const IntVector3 ONE", (void*)&IntVector3::ONE));

}

// class Matrix2 | File: ../Math/Matrix2.h
void CollectMembers_Matrix2(MemberCollection& members)
{
    // const float* Matrix2::Data() const
    // Error: type "const float*" can not automatically bind
    // bool Matrix2::operator !=(const Matrix2& rhs) const
    // Only operator == is needed

    // static void Matrix2::BulkTranspose(float* dest, const float* src, unsigned count)
    // Error: type "float*" can not automatically bind

    members.fields_.Push(RegisterObjectPropertyArgs("float Matrix2::m00_", "float m00", offsetof(Matrix2, m00_)));
    members.fields_.Push(RegisterObjectPropertyArgs("float Matrix2::m01_", "float m01", offsetof(Matrix2, m01_)));
    members.fields_.Push(RegisterObjectPropertyArgs("float Matrix2::m10_", "float m10", offsetof(Matrix2, m10_)));
    members.fields_.Push(RegisterObjectPropertyArgs("float Matrix2::m11_", "float m11", offsetof(Matrix2, m11_)));

    members.staticFields_.Push(RegisterGlobalPropertyArgs("static const Matrix2 Matrix2::ZERO", "const Matrix2 ZERO", (void*)&Matrix2::ZERO));
    members.staticFields_.Push(RegisterGlobalPropertyArgs("static const Matrix2 Matrix2::IDENTITY", "const Matrix2 IDENTITY", (void*)&Matrix2::IDENTITY));

}

// class Matrix3 | File: ../Math/Matrix3.h
void CollectMembers_Matrix3(MemberCollection& members)
{
    // const float* Matrix3::Data() const
    // Error: type "const float*" can not automatically bind
    // bool Matrix3::operator !=(const Matrix3& rhs) const
    // Only operator == is needed

    // static void Matrix3::BulkTranspose(float* dest, const float* src, unsigned count)
    // Error: type "float*" can not automatically bind

    members.fields_.Push(RegisterObjectPropertyArgs("float Matrix3::m00_", "float m00", offsetof(Matrix3, m00_)));
    members.fields_.Push(RegisterObjectPropertyArgs("float Matrix3::m01_", "float m01", offsetof(Matrix3, m01_)));
    members.fields_.Push(RegisterObjectPropertyArgs("float Matrix3::m02_", "float m02", offsetof(Matrix3, m02_)));
    members.fields_.Push(RegisterObjectPropertyArgs("float Matrix3::m10_", "float m10", offsetof(Matrix3, m10_)));
    members.fields_.Push(RegisterObjectPropertyArgs("float Matrix3::m11_", "float m11", offsetof(Matrix3, m11_)));
    members.fields_.Push(RegisterObjectPropertyArgs("float Matrix3::m12_", "float m12", offsetof(Matrix3, m12_)));
    members.fields_.Push(RegisterObjectPropertyArgs("float Matrix3::m20_", "float m20", offsetof(Matrix3, m20_)));
    members.fields_.Push(RegisterObjectPropertyArgs("float Matrix3::m21_", "float m21", offsetof(Matrix3, m21_)));
    members.fields_.Push(RegisterObjectPropertyArgs("float Matrix3::m22_", "float m22", offsetof(Matrix3, m22_)));

    members.staticFields_.Push(RegisterGlobalPropertyArgs("static const Matrix3 Matrix3::ZERO", "const Matrix3 ZERO", (void*)&Matrix3::ZERO));
    members.staticFields_.Push(RegisterGlobalPropertyArgs("static const Matrix3 Matrix3::IDENTITY", "const Matrix3 IDENTITY", (void*)&Matrix3::IDENTITY));

}

// class Matrix3x4 | File: ../Math/Matrix3x4.h
void CollectMembers_Matrix3x4(MemberCollection& members)
{
    // const float* Matrix3x4::Data() const
    // Error: type "const float*" can not automatically bind
    // bool Matrix3x4::operator !=(const Matrix3x4& rhs) const
    // Only operator == is needed

    members.fields_.Push(RegisterObjectPropertyArgs("float Matrix3x4::m00_", "float m00", offsetof(Matrix3x4, m00_)));
    members.fields_.Push(RegisterObjectPropertyArgs("float Matrix3x4::m01_", "float m01", offsetof(Matrix3x4, m01_)));
    members.fields_.Push(RegisterObjectPropertyArgs("float Matrix3x4::m02_", "float m02", offsetof(Matrix3x4, m02_)));
    members.fields_.Push(RegisterObjectPropertyArgs("float Matrix3x4::m03_", "float m03", offsetof(Matrix3x4, m03_)));
    members.fields_.Push(RegisterObjectPropertyArgs("float Matrix3x4::m10_", "float m10", offsetof(Matrix3x4, m10_)));
    members.fields_.Push(RegisterObjectPropertyArgs("float Matrix3x4::m11_", "float m11", offsetof(Matrix3x4, m11_)));
    members.fields_.Push(RegisterObjectPropertyArgs("float Matrix3x4::m12_", "float m12", offsetof(Matrix3x4, m12_)));
    members.fields_.Push(RegisterObjectPropertyArgs("float Matrix3x4::m13_", "float m13", offsetof(Matrix3x4, m13_)));
    members.fields_.Push(RegisterObjectPropertyArgs("float Matrix3x4::m20_", "float m20", offsetof(Matrix3x4, m20_)));
    members.fields_.Push(RegisterObjectPropertyArgs("float Matrix3x4::m21_", "float m21", offsetof(Matrix3x4, m21_)));
    members.fields_.Push(RegisterObjectPropertyArgs("float Matrix3x4::m22_", "float m22", offsetof(Matrix3x4, m22_)));
    members.fields_.Push(RegisterObjectPropertyArgs("float Matrix3x4::m23_", "float m23", offsetof(Matrix3x4, m23_)));

    members.staticFields_.Push(RegisterGlobalPropertyArgs("static const Matrix3x4 Matrix3x4::ZERO", "const Matrix3x4 ZERO", (void*)&Matrix3x4::ZERO));
    members.staticFields_.Push(RegisterGlobalPropertyArgs("static const Matrix3x4 Matrix3x4::IDENTITY", "const Matrix3x4 IDENTITY", (void*)&Matrix3x4::IDENTITY));

}

// class Matrix4 | File: ../Math/Matrix4.h
void CollectMembers_Matrix4(MemberCollection& members)
{
    // const float* Matrix4::Data() const
    // Error: type "const float*" can not automatically bind
    // bool Matrix4::operator !=(const Matrix4& rhs) const
    // Only operator == is needed

    // static void Matrix4::BulkTranspose(float* dest, const float* src, unsigned count)
    // Error: type "float*" can not automatically bind

    members.fields_.Push(RegisterObjectPropertyArgs("float Matrix4::m00_", "float m00", offsetof(Matrix4, m00_)));
    members.fields_.Push(RegisterObjectPropertyArgs("float Matrix4::m01_", "float m01", offsetof(Matrix4, m01_)));
    members.fields_.Push(RegisterObjectPropertyArgs("float Matrix4::m02_", "float m02", offsetof(Matrix4, m02_)));
    members.fields_.Push(RegisterObjectPropertyArgs("float Matrix4::m03_", "float m03", offsetof(Matrix4, m03_)));
    members.fields_.Push(RegisterObjectPropertyArgs("float Matrix4::m10_", "float m10", offsetof(Matrix4, m10_)));
    members.fields_.Push(RegisterObjectPropertyArgs("float Matrix4::m11_", "float m11", offsetof(Matrix4, m11_)));
    members.fields_.Push(RegisterObjectPropertyArgs("float Matrix4::m12_", "float m12", offsetof(Matrix4, m12_)));
    members.fields_.Push(RegisterObjectPropertyArgs("float Matrix4::m13_", "float m13", offsetof(Matrix4, m13_)));
    members.fields_.Push(RegisterObjectPropertyArgs("float Matrix4::m20_", "float m20", offsetof(Matrix4, m20_)));
    members.fields_.Push(RegisterObjectPropertyArgs("float Matrix4::m21_", "float m21", offsetof(Matrix4, m21_)));
    members.fields_.Push(RegisterObjectPropertyArgs("float Matrix4::m22_", "float m22", offsetof(Matrix4, m22_)));
    members.fields_.Push(RegisterObjectPropertyArgs("float Matrix4::m23_", "float m23", offsetof(Matrix4, m23_)));
    members.fields_.Push(RegisterObjectPropertyArgs("float Matrix4::m30_", "float m30", offsetof(Matrix4, m30_)));
    members.fields_.Push(RegisterObjectPropertyArgs("float Matrix4::m31_", "float m31", offsetof(Matrix4, m31_)));
    members.fields_.Push(RegisterObjectPropertyArgs("float Matrix4::m32_", "float m32", offsetof(Matrix4, m32_)));
    members.fields_.Push(RegisterObjectPropertyArgs("float Matrix4::m33_", "float m33", offsetof(Matrix4, m33_)));

    members.staticFields_.Push(RegisterGlobalPropertyArgs("static const Matrix4 Matrix4::ZERO", "const Matrix4 ZERO", (void*)&Matrix4::ZERO));
    members.staticFields_.Push(RegisterGlobalPropertyArgs("static const Matrix4 Matrix4::IDENTITY", "const Matrix4 IDENTITY", (void*)&Matrix4::IDENTITY));

}

// class Plane | File: ../Math/Plane.h
void CollectMembers_Plane(MemberCollection& members)
{
    members.fields_.Push(RegisterObjectPropertyArgs("Vector3 Plane::normal_", "Vector3 normal", offsetof(Plane, normal_)));
    members.fields_.Push(RegisterObjectPropertyArgs("Vector3 Plane::absNormal_", "Vector3 absNormal", offsetof(Plane, absNormal_)));
    members.fields_.Push(RegisterObjectPropertyArgs("float Plane::d_", "float d", offsetof(Plane, d_)));

    members.staticFields_.Push(RegisterGlobalPropertyArgs("static const Plane Plane::UP", "const Plane UP", (void*)&Plane::UP));

}

// class Polyhedron | File: ../Math/Polyhedron.h
void CollectMembers_Polyhedron(MemberCollection& members)
{
    // Vector<PODVector<Vector3>> Polyhedron::faces_
    // Error: type "Vector<PODVector<Vector3>>" can not automatically bind

}

// class Quaternion | File: ../Math/Quaternion.h
void CollectMembers_Quaternion(MemberCollection& members)
{
    // const float* Quaternion::Data() const
    // Error: type "const float*" can not automatically bind
    // bool Quaternion::operator !=(const Quaternion& rhs) const
    // Only operator == is needed

    members.fields_.Push(RegisterObjectPropertyArgs("float Quaternion::w_", "float w", offsetof(Quaternion, w_)));
    members.fields_.Push(RegisterObjectPropertyArgs("float Quaternion::x_", "float x", offsetof(Quaternion, x_)));
    members.fields_.Push(RegisterObjectPropertyArgs("float Quaternion::y_", "float y", offsetof(Quaternion, y_)));
    members.fields_.Push(RegisterObjectPropertyArgs("float Quaternion::z_", "float z", offsetof(Quaternion, z_)));

    members.staticFields_.Push(RegisterGlobalPropertyArgs("static const Quaternion Quaternion::IDENTITY", "const Quaternion IDENTITY", (void*)&Quaternion::IDENTITY));

}

// class Ray | File: ../Math/Ray.h
void CollectMembers_Ray(MemberCollection& members)
{
    // float Ray::HitDistance(const Vector3& v0, const Vector3& v1, const Vector3& v2, Vector3* outNormal = nullptr, Vector3* outBary = nullptr) const
    // Error: type "Vector3*" can not automatically bind
    // float Ray::HitDistance(const void* vertexData, unsigned vertexStride, const void* indexData, unsigned indexSize, unsigned indexStart, unsigned indexCount, Vector3* outNormal = nullptr, Vector2* outUV = nullptr, unsigned uvOffset = 0) const
    // Error: type "const void*" can not automatically bind
    // float Ray::HitDistance(const void* vertexData, unsigned vertexStride, unsigned vertexStart, unsigned vertexCount, Vector3* outNormal = nullptr, Vector2* outUV = nullptr, unsigned uvOffset = 0) const
    // Error: type "const void*" can not automatically bind
    // bool Ray::InsideGeometry(const void* vertexData, unsigned vertexSize, const void* indexData, unsigned indexSize, unsigned indexStart, unsigned indexCount) const
    // Error: type "const void*" can not automatically bind
    // bool Ray::InsideGeometry(const void* vertexData, unsigned vertexSize, unsigned vertexStart, unsigned vertexCount) const
    // Error: type "const void*" can not automatically bind
    // bool Ray::operator !=(const Ray& rhs) const
    // Only operator == is needed

    members.fields_.Push(RegisterObjectPropertyArgs("Vector3 Ray::origin_", "Vector3 origin", offsetof(Ray, origin_)));
    members.fields_.Push(RegisterObjectPropertyArgs("Vector3 Ray::direction_", "Vector3 direction", offsetof(Ray, direction_)));

}

// class Rect | File: ../Math/Rect.h
void CollectMembers_Rect(MemberCollection& members)
{
    // const float* Rect::Data() const
    // Error: type "const float*" can not automatically bind
    // bool Rect::operator !=(const Rect& rhs) const
    // Only operator == is needed

    members.fields_.Push(RegisterObjectPropertyArgs("Vector2 Rect::min_", "Vector2 min", offsetof(Rect, min_)));
    members.fields_.Push(RegisterObjectPropertyArgs("Vector2 Rect::max_", "Vector2 max", offsetof(Rect, max_)));

    members.staticFields_.Push(RegisterGlobalPropertyArgs("static const Rect Rect::FULL", "const Rect FULL", (void*)&Rect::FULL));
    members.staticFields_.Push(RegisterGlobalPropertyArgs("static const Rect Rect::POSITIVE", "const Rect POSITIVE", (void*)&Rect::POSITIVE));
    members.staticFields_.Push(RegisterGlobalPropertyArgs("static const Rect Rect::ZERO", "const Rect ZERO", (void*)&Rect::ZERO));

}

// class Sphere | File: ../Math/Sphere.h
void CollectMembers_Sphere(MemberCollection& members)
{
    // void Sphere::Define(const Vector3* vertices, unsigned count)
    // Error: type "const Vector3*" can not automatically bind
    // void Sphere::Merge(const Vector3* vertices, unsigned count)
    // Error: type "const Vector3*" can not automatically bind
    // bool Sphere::operator !=(const Sphere& rhs) const
    // Only operator == is needed

    members.fields_.Push(RegisterObjectPropertyArgs("Vector3 Sphere::center_", "Vector3 center", offsetof(Sphere, center_)));
    members.fields_.Push(RegisterObjectPropertyArgs("float Sphere::radius_", "float radius", offsetof(Sphere, radius_)));

}

// bool StringHash::operator <(const StringHash& rhs) const
static int StringHash_bool_operatorles_constspStringHashamp(const StringHash& lhs, const StringHash& rhs)
{
    if (lhs < rhs)
        return -1;

    if (lhs > rhs)
        return 1;

    return 0;
}

// class StringHash | File: ../Math/StringHash.h
void CollectMembers_StringHash(MemberCollection& members)
{
    // bool StringHash::operator !=(const StringHash& rhs) const
    // Only operator == is needed
    // bool StringHash::operator <(const StringHash& rhs) const
    // Registerd as opCmp separately
    // bool StringHash::operator>(const StringHash& rhs) const
    // Registerd as opCmp separately

    members.methods_.Push(RegisterObjectMethodArgs("bool StringHash::operator <(const StringHash& rhs) const", "int opCmp(const StringHash&in) const", AS_FUNCTION_OBJFIRST(StringHash_bool_operatorles_constspStringHashamp), AS_CALL_CDECL_OBJFIRST));

    // static unsigned StringHash::Calculate(const char* str, unsigned hash = 0)
    // Error: type "const char*" can not automatically bind
    // static StringHashRegister* StringHash::GetGlobalStringHashRegister()
    // Error: type "StringHashRegister*" can not automatically bind

    members.staticFields_.Push(RegisterGlobalPropertyArgs("static const StringHash StringHash::ZERO", "const StringHash ZERO", (void*)&StringHash::ZERO));

}

// class Vector2 | File: ../Math/Vector2.h
void CollectMembers_Vector2(MemberCollection& members)
{
    // const float* Vector2::Data() const
    // Error: type "const float*" can not automatically bind
    // bool Vector2::operator !=(const Vector2& rhs) const
    // Only operator == is needed

    members.fields_.Push(RegisterObjectPropertyArgs("float Vector2::x_", "float x", offsetof(Vector2, x_)));
    members.fields_.Push(RegisterObjectPropertyArgs("float Vector2::y_", "float y", offsetof(Vector2, y_)));

    members.staticFields_.Push(RegisterGlobalPropertyArgs("static const Vector2 Vector2::ZERO", "const Vector2 ZERO", (void*)&Vector2::ZERO));
    members.staticFields_.Push(RegisterGlobalPropertyArgs("static const Vector2 Vector2::LEFT", "const Vector2 LEFT", (void*)&Vector2::LEFT));
    members.staticFields_.Push(RegisterGlobalPropertyArgs("static const Vector2 Vector2::RIGHT", "const Vector2 RIGHT", (void*)&Vector2::RIGHT));
    members.staticFields_.Push(RegisterGlobalPropertyArgs("static const Vector2 Vector2::UP", "const Vector2 UP", (void*)&Vector2::UP));
    members.staticFields_.Push(RegisterGlobalPropertyArgs("static const Vector2 Vector2::DOWN", "const Vector2 DOWN", (void*)&Vector2::DOWN));
    members.staticFields_.Push(RegisterGlobalPropertyArgs("static const Vector2 Vector2::ONE", "const Vector2 ONE", (void*)&Vector2::ONE));

}

// class Vector3 | File: ../Math/Vector3.h
void CollectMembers_Vector3(MemberCollection& members)
{
    // const float* Vector3::Data() const
    // Error: type "const float*" can not automatically bind
    // bool Vector3::operator !=(const Vector3& rhs) const
    // Only operator == is needed

    members.fields_.Push(RegisterObjectPropertyArgs("float Vector3::x_", "float x", offsetof(Vector3, x_)));
    members.fields_.Push(RegisterObjectPropertyArgs("float Vector3::y_", "float y", offsetof(Vector3, y_)));
    members.fields_.Push(RegisterObjectPropertyArgs("float Vector3::z_", "float z", offsetof(Vector3, z_)));

    members.staticFields_.Push(RegisterGlobalPropertyArgs("static const Vector3 Vector3::ZERO", "const Vector3 ZERO", (void*)&Vector3::ZERO));
    members.staticFields_.Push(RegisterGlobalPropertyArgs("static const Vector3 Vector3::LEFT", "const Vector3 LEFT", (void*)&Vector3::LEFT));
    members.staticFields_.Push(RegisterGlobalPropertyArgs("static const Vector3 Vector3::RIGHT", "const Vector3 RIGHT", (void*)&Vector3::RIGHT));
    members.staticFields_.Push(RegisterGlobalPropertyArgs("static const Vector3 Vector3::UP", "const Vector3 UP", (void*)&Vector3::UP));
    members.staticFields_.Push(RegisterGlobalPropertyArgs("static const Vector3 Vector3::DOWN", "const Vector3 DOWN", (void*)&Vector3::DOWN));
    members.staticFields_.Push(RegisterGlobalPropertyArgs("static const Vector3 Vector3::FORWARD", "const Vector3 FORWARD", (void*)&Vector3::FORWARD));
    members.staticFields_.Push(RegisterGlobalPropertyArgs("static const Vector3 Vector3::BACK", "const Vector3 BACK", (void*)&Vector3::BACK));
    members.staticFields_.Push(RegisterGlobalPropertyArgs("static const Vector3 Vector3::ONE", "const Vector3 ONE", (void*)&Vector3::ONE));

}

// class Vector4 | File: ../Math/Vector4.h
void CollectMembers_Vector4(MemberCollection& members)
{
    // const float* Vector4::Data() const
    // Error: type "const float*" can not automatically bind
    // bool Vector4::operator !=(const Vector4& rhs) const
    // Only operator == is needed

    members.fields_.Push(RegisterObjectPropertyArgs("float Vector4::x_", "float x", offsetof(Vector4, x_)));
    members.fields_.Push(RegisterObjectPropertyArgs("float Vector4::y_", "float y", offsetof(Vector4, y_)));
    members.fields_.Push(RegisterObjectPropertyArgs("float Vector4::z_", "float z", offsetof(Vector4, z_)));
    members.fields_.Push(RegisterObjectPropertyArgs("float Vector4::w_", "float w", offsetof(Vector4, w_)));

    members.staticFields_.Push(RegisterGlobalPropertyArgs("static const Vector4 Vector4::ZERO", "const Vector4 ZERO", (void*)&Vector4::ZERO));
    members.staticFields_.Push(RegisterGlobalPropertyArgs("static const Vector4 Vector4::ONE", "const Vector4 ONE", (void*)&Vector4::ONE));

}

} // namespace Urho3D
