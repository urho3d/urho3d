// DO NOT EDIT. This file is generated

#include "../Precompiled.h"
#include "../AngelScript/APITemplates.h"

// Ignored headers
//#include "../AngelScript/Script.h"
//#include "../AngelScript/ScriptInstance.h"
//#include "../Graphics/Drawable.h"
//#include "../LuaScript/LuaScriptInstance.h"
//#include "../Resource/PListFile.h"
//#include "../Resource/Resource.h"

#include "../Core/Attribute.h"
#include "../Core/Spline.h"
#include "../Core/Variant.h"
#ifdef URHO3D_DATABASE
#include "../Database/Database.h"
#endif
#include "../Graphics/Animation.h"
#include "../Graphics/AnimationState.h"
#include "../Graphics/Camera.h"
#include "../Graphics/GraphicsDefs.h"
#include "../Graphics/Light.h"
#include "../Graphics/OctreeQuery.h"
#include "../Graphics/ParticleEffect.h"
#include "../Graphics/RenderPath.h"
#include "../Graphics/RibbonTrail.h"
#include "../Graphics/Skeleton.h"
#include "../Graphics/Technique.h"
#include "../IO/File.h"
#include "../Input/Input.h"
#include "../Input/InputConstants.h"
#include "../Math/BoundingBox.h"
#include "../Math/Color.h"
#include "../Math/Frustum.h"
#include "../Math/MathDefs.h"
#include "../Math/Matrix2.h"
#include "../Math/Matrix3.h"
#include "../Math/Matrix3x4.h"
#include "../Math/Matrix4.h"
#include "../Math/Plane.h"
#include "../Math/Polyhedron.h"
#include "../Math/Quaternion.h"
#include "../Math/Ray.h"
#include "../Math/Rect.h"
#include "../Math/Sphere.h"
#include "../Math/Vector2.h"
#include "../Math/Vector3.h"
#include "../Math/Vector4.h"
#ifdef URHO3D_NAVIGATION
#include "../Navigation/CrowdAgent.h"
#endif
#ifdef URHO3D_NAVIGATION
#include "../Navigation/NavigationMesh.h"
#endif
#ifdef URHO3D_NETWORK
#include "../Network/Connection.h"
#endif
#ifdef URHO3D_NETWORK
#include "../Network/HttpRequest.h"
#endif
#ifdef URHO3D_PHYSICS
#include "../Physics/CollisionShape.h"
#endif
#ifdef URHO3D_PHYSICS
#include "../Physics/Constraint.h"
#endif
#ifdef URHO3D_PHYSICS
#include "../Physics/RigidBody.h"
#endif
#include "../Resource/Image.h"
#include "../Resource/JSONValue.h"
#include "../Scene/AnimationDefs.h"
#include "../Scene/Component.h"
#include "../Scene/Node.h"
#include "../Scene/Scene.h"
#include "../Scene/SmoothedTransform.h"
#include "../Scene/ValueAnimation.h"
#include "../UI/Cursor.h"
#include "../UI/Font.h"
#include "../UI/ListView.h"
#include "../UI/Text.h"
#include "../UI/UI.h"
#include "../UI/UIElement.h"
#include "../UI/Window.h"
#ifdef URHO3D_URHO2D
#include "../Urho2D/AnimatedSprite2D.h"
#endif
#ifdef URHO3D_URHO2D
#include "../Urho2D/ParticleEffect2D.h"
#endif
#ifdef URHO3D_URHO2D
#include "../Urho2D/RigidBody2D.h"
#endif
#ifdef URHO3D_URHO2D
#include "../Urho2D/TileMapDefs2D.h"
#endif

namespace Urho3D
{

// IntRect::IntRect() noexcept | File: ../Math/Rect.h | Line: 286
static void IntRect_IntRect_286_5(IntRect* ptr)
{
    new(ptr) IntRect();
}

// IntRect::IntRect(const IntVector2 &min, const IntVector2 &max) noexcept | File: ../Math/Rect.h | Line: 295
static void IntRect_IntRect_295_5(IntRect* ptr, const IntVector2 &min, const IntVector2 &max)
{
    new(ptr) IntRect(min, max);
}

// IntRect::IntRect(int left, int top, int right, int bottom) noexcept | File: ../Math/Rect.h | Line: 304
static void IntRect_IntRect_304_5(IntRect* ptr, int left, int top, int right, int bottom)
{
    new(ptr) IntRect(left, top, right, bottom);
}

// IntVector2::IntVector2() noexcept | File: ../Math/Vector2.h | Line: 36
static void IntVector2_IntVector2_36_5(IntVector2* ptr)
{
    new(ptr) IntVector2();
}

// IntVector2::IntVector2(int x, int y) noexcept | File: ../Math/Vector2.h | Line: 43
static void IntVector2_IntVector2_43_5(IntVector2* ptr, int x, int y)
{
    new(ptr) IntVector2(x, y);
}

// IntVector2::IntVector2(const IntVector2 &rhs) noexcept=default | File: ../Math/Vector2.h | Line: 65
static void IntVector2_IntVector2_65_5(IntVector2* ptr, const IntVector2 &rhs)
{
    new(ptr) IntVector2(rhs);
}

// IntVector3::IntVector3() noexcept | File: ../Math/Vector3.h | Line: 36
static void IntVector3_IntVector3_36_5(IntVector3* ptr)
{
    new(ptr) IntVector3();
}

// IntVector3::IntVector3(int x, int y, int z) noexcept | File: ../Math/Vector3.h | Line: 44
static void IntVector3_IntVector3_44_5(IntVector3* ptr, int x, int y, int z)
{
    new(ptr) IntVector3(x, y, z);
}

// IntVector3::IntVector3(const IntVector3 &rhs) noexcept=default | File: ../Math/Vector3.h | Line: 61
static void IntVector3_IntVector3_61_5(IntVector3* ptr, const IntVector3 &rhs)
{
    new(ptr) IntVector3(rhs);
}

// BoundingBox::BoundingBox() noexcept | File: ../Math/BoundingBox.h | Line: 48
static void BoundingBox_BoundingBox_48_5(BoundingBox* ptr)
{
    new(ptr) BoundingBox();
}

// BoundingBox::BoundingBox(const BoundingBox &box) noexcept | File: ../Math/BoundingBox.h | Line: 55
static void BoundingBox_BoundingBox_55_5(BoundingBox* ptr, const BoundingBox &box)
{
    new(ptr) BoundingBox(box);
}

// BoundingBox::BoundingBox(const Rect &rect) noexcept | File: ../Math/BoundingBox.h | Line: 62
static void BoundingBox_BoundingBox_62_14(BoundingBox* ptr, const Rect &rect)
{
    new(ptr) BoundingBox(rect);
}

// BoundingBox::BoundingBox(const Vector3 &min, const Vector3 &max) noexcept | File: ../Math/BoundingBox.h | Line: 69
static void BoundingBox_BoundingBox_69_5(BoundingBox* ptr, const Vector3 &min, const Vector3 &max)
{
    new(ptr) BoundingBox(min, max);
}

// BoundingBox::BoundingBox(float min, float max) noexcept | File: ../Math/BoundingBox.h | Line: 76
static void BoundingBox_BoundingBox_76_5(BoundingBox* ptr, float min, float max)
{
    new(ptr) BoundingBox(min, max);
}

// BoundingBox::BoundingBox(const Frustum &frustum) | File: ../Math/BoundingBox.h | Line: 101
static void BoundingBox_BoundingBox_101_14(BoundingBox* ptr, const Frustum &frustum)
{
    new(ptr) BoundingBox(frustum);
}

// BoundingBox::BoundingBox(const Polyhedron &poly) | File: ../Math/BoundingBox.h | Line: 109
static void BoundingBox_BoundingBox_109_14(BoundingBox* ptr, const Polyhedron &poly)
{
    new(ptr) BoundingBox(poly);
}

// BoundingBox::BoundingBox(const Sphere &sphere) | File: ../Math/BoundingBox.h | Line: 117
static void BoundingBox_BoundingBox_117_14(BoundingBox* ptr, const Sphere &sphere)
{
    new(ptr) BoundingBox(sphere);
}

// Color::Color() noexcept | File: ../Math/Color.h | Line: 54
static void Color_Color_54_5(Color* ptr)
{
    new(ptr) Color();
}

// Color::Color(const Color &color) noexcept=default | File: ../Math/Color.h | Line: 63
static void Color_Color_63_5(Color* ptr, const Color &color)
{
    new(ptr) Color(color);
}

// Color::Color(const Color &color, float a) noexcept | File: ../Math/Color.h | Line: 66
static void Color_Color_66_5(Color* ptr, const Color &color, float a)
{
    new(ptr) Color(color, a);
}

// Color::Color(float r, float g, float b) noexcept | File: ../Math/Color.h | Line: 75
static void Color_Color_75_5(Color* ptr, float r, float g, float b)
{
    new(ptr) Color(r, g, b);
}

// Color::Color(float r, float g, float b, float a) noexcept | File: ../Math/Color.h | Line: 84
static void Color_Color_84_5(Color* ptr, float r, float g, float b, float a)
{
    new(ptr) Color(r, g, b, a);
}

// Color::Color(const Vector3 &color) | File: ../Math/Color.h | Line: 107
static void Color_Color_107_14(Color* ptr, const Vector3 &color)
{
    new(ptr) Color(color);
}

// Color::Color(const Vector4 &color) | File: ../Math/Color.h | Line: 110
static void Color_Color_110_14(Color* ptr, const Vector4 &color)
{
    new(ptr) Color(color);
}

// Frustum::~Frustum()
static void Frustum_Destructor(Frustum* ptr)
{
    ptr->~Frustum();
}

// Frustum::Frustum() noexcept=default | File: ../Math/Frustum.h | Line: 55
static void Frustum_Frustum_55_5(Frustum* ptr)
{
    new(ptr) Frustum();
}

// Frustum::Frustum(const Frustum &frustum) noexcept | File: ../Math/Frustum.h | Line: 58
static void Frustum_Frustum_58_5(Frustum* ptr, const Frustum &frustum)
{
    new(ptr) Frustum(frustum);
}

// Vector2::Vector2() noexcept | File: ../Math/Vector2.h | Line: 182
static void Vector2_Vector2_182_5(Vector2* ptr)
{
    new(ptr) Vector2();
}

// Vector2::Vector2(const Vector2 &vector) noexcept=default | File: ../Math/Vector2.h | Line: 189
static void Vector2_Vector2_189_5(Vector2* ptr, const Vector2 &vector)
{
    new(ptr) Vector2(vector);
}

// Vector2::Vector2(const IntVector2 &vector) noexcept | File: ../Math/Vector2.h | Line: 192
static void Vector2_Vector2_192_14(Vector2* ptr, const IntVector2 &vector)
{
    new(ptr) Vector2(vector);
}

// Vector2::Vector2(float x, float y) noexcept | File: ../Math/Vector2.h | Line: 199
static void Vector2_Vector2_199_5(Vector2* ptr, float x, float y)
{
    new(ptr) Vector2(x, y);
}

// Matrix2::Matrix2() noexcept | File: ../Math/Matrix2.h | Line: 35
static void Matrix2_Matrix2_35_5(Matrix2* ptr)
{
    new(ptr) Matrix2();
}

// Matrix2::Matrix2(const Matrix2 &matrix) noexcept=default | File: ../Math/Matrix2.h | Line: 44
static void Matrix2_Matrix2_44_5(Matrix2* ptr, const Matrix2 &matrix)
{
    new(ptr) Matrix2(matrix);
}

// Matrix2::Matrix2(float v00, float v01, float v10, float v11) noexcept | File: ../Math/Matrix2.h | Line: 47
static void Matrix2_Matrix2_47_5(Matrix2* ptr, float v00, float v01, float v10, float v11)
{
    new(ptr) Matrix2(v00, v01, v10, v11);
}

// Matrix3::Matrix3() noexcept | File: ../Math/Matrix3.h | Line: 35
static void Matrix3_Matrix3_35_5(Matrix3* ptr)
{
    new(ptr) Matrix3();
}

// Matrix3::Matrix3(const Matrix3 &matrix) noexcept=default | File: ../Math/Matrix3.h | Line: 49
static void Matrix3_Matrix3_49_5(Matrix3* ptr, const Matrix3 &matrix)
{
    new(ptr) Matrix3(matrix);
}

// Matrix3::Matrix3(float v00, float v01, float v02, float v10, float v11, float v12, float v20, float v21, float v22) noexcept | File: ../Math/Matrix3.h | Line: 52
static void Matrix3_Matrix3_52_5(Matrix3* ptr, float v00, float v01, float v02, float v10, float v11, float v12, float v20, float v21, float v22)
{
    new(ptr) Matrix3(v00, v01, v02, v10, v11, v12, v20, v21, v22);
}

// Matrix3x4::Matrix3x4() noexcept | File: ../Math/Matrix3x4.h | Line: 39
static void Matrix3x4_Matrix3x4_39_5(Matrix3x4* ptr)
{
    new(ptr) Matrix3x4();
}

// Matrix3x4::Matrix3x4(const Matrix3x4 &matrix) noexcept=default | File: ../Math/Matrix3x4.h | Line: 63
static void Matrix3x4_Matrix3x4_63_5(Matrix3x4* ptr, const Matrix3x4 &matrix)
{
    new(ptr) Matrix3x4(matrix);
}

// Matrix3x4::Matrix3x4(const Matrix3 &matrix) noexcept | File: ../Math/Matrix3x4.h | Line: 66
static void Matrix3x4_Matrix3x4_66_14(Matrix3x4* ptr, const Matrix3 &matrix)
{
    new(ptr) Matrix3x4(matrix);
}

// Matrix3x4::Matrix3x4(const Matrix4 &matrix) noexcept | File: ../Math/Matrix3x4.h | Line: 83
static void Matrix3x4_Matrix3x4_83_14(Matrix3x4* ptr, const Matrix4 &matrix)
{
    new(ptr) Matrix3x4(matrix);
}

// Matrix3x4::Matrix3x4(float v00, float v01, float v02, float v03, float v10, float v11, float v12, float v13, float v20, float v21, float v22, float v23) noexcept | File: ../Math/Matrix3x4.h | Line: 107
static void Matrix3x4_Matrix3x4_107_5(Matrix3x4* ptr, float v00, float v01, float v02, float v03, float v10, float v11, float v12, float v13, float v20, float v21, float v22, float v23)
{
    new(ptr) Matrix3x4(v00, v01, v02, v03, v10, v11, v12, v13, v20, v21, v22, v23);
}

// Matrix3x4::Matrix3x4(const Vector3 &translation, const Quaternion &rotation, float scale) noexcept | File: ../Math/Matrix3x4.h | Line: 151
static void Matrix3x4_Matrix3x4_151_5(Matrix3x4* ptr, const Vector3 &translation, const Quaternion &rotation, float scale)
{
    new(ptr) Matrix3x4(translation, rotation, scale);
}

// Matrix3x4::Matrix3x4(const Vector3 &translation, const Quaternion &rotation, const Vector3 &scale) noexcept | File: ../Math/Matrix3x4.h | Line: 165
static void Matrix3x4_Matrix3x4_165_5(Matrix3x4* ptr, const Vector3 &translation, const Quaternion &rotation, const Vector3 &scale)
{
    new(ptr) Matrix3x4(translation, rotation, scale);
}

// Matrix4::Matrix4() noexcept | File: ../Math/Matrix4.h | Line: 42
static void Matrix4_Matrix4_42_5(Matrix4* ptr)
{
    new(ptr) Matrix4();
}

// Matrix4::Matrix4(const Matrix4 &matrix) noexcept | File: ../Math/Matrix4.h | Line: 71
static void Matrix4_Matrix4_71_5(Matrix4* ptr, const Matrix4 &matrix)
{
    new(ptr) Matrix4(matrix);
}

// Matrix4::Matrix4(const Matrix3 &matrix) noexcept | File: ../Math/Matrix4.h | Line: 100
static void Matrix4_Matrix4_100_14(Matrix4* ptr, const Matrix3 &matrix)
{
    new(ptr) Matrix4(matrix);
}

// Matrix4::Matrix4(float v00, float v01, float v02, float v03, float v10, float v11, float v12, float v13, float v20, float v21, float v22, float v23, float v30, float v31, float v32, float v33) noexcept | File: ../Math/Matrix4.h | Line: 121
static void Matrix4_Matrix4_121_5(Matrix4* ptr, float v00, float v01, float v02, float v03, float v10, float v11, float v12, float v13, float v20, float v21, float v22, float v23, float v30, float v31, float v32, float v33)
{
    new(ptr) Matrix4(v00, v01, v02, v03, v10, v11, v12, v13, v20, v21, v22, v23, v30, v31, v32, v33);
}

// Vector4::Vector4() noexcept | File: ../Math/Vector4.h | Line: 35
static void Vector4_Vector4_35_5(Vector4* ptr)
{
    new(ptr) Vector4();
}

// Vector4::Vector4(const Vector4 &vector) noexcept=default | File: ../Math/Vector4.h | Line: 44
static void Vector4_Vector4_44_5(Vector4* ptr, const Vector4 &vector)
{
    new(ptr) Vector4(vector);
}

// Vector4::Vector4(const Vector3 &vector, float w) noexcept | File: ../Math/Vector4.h | Line: 47
static void Vector4_Vector4_47_5(Vector4* ptr, const Vector3 &vector, float w)
{
    new(ptr) Vector4(vector, w);
}

// Vector4::Vector4(float x, float y, float z, float w) noexcept | File: ../Math/Vector4.h | Line: 56
static void Vector4_Vector4_56_5(Vector4* ptr, float x, float y, float z, float w)
{
    new(ptr) Vector4(x, y, z, w);
}

// Plane::Plane() noexcept | File: ../Math/Plane.h | Line: 36
static void Plane_Plane_36_5(Plane* ptr)
{
    new(ptr) Plane();
}

// Plane::Plane(const Plane &plane) noexcept=default | File: ../Math/Plane.h | Line: 42
static void Plane_Plane_42_5(Plane* ptr, const Plane &plane)
{
    new(ptr) Plane(plane);
}

// Plane::Plane(const Vector3 &v0, const Vector3 &v1, const Vector3 &v2) noexcept | File: ../Math/Plane.h | Line: 45
static void Plane_Plane_45_5(Plane* ptr, const Vector3 &v0, const Vector3 &v1, const Vector3 &v2)
{
    new(ptr) Plane(v0, v1, v2);
}

// Plane::Plane(const Vector3 &normal, const Vector3 &point) noexcept | File: ../Math/Plane.h | Line: 51
static void Plane_Plane_51_5(Plane* ptr, const Vector3 &normal, const Vector3 &point)
{
    new(ptr) Plane(normal, point);
}

// Plane::Plane(const Vector4 &plane) noexcept | File: ../Math/Plane.h | Line: 57
static void Plane_Plane_57_14(Plane* ptr, const Vector4 &plane)
{
    new(ptr) Plane(plane);
}

// Polyhedron::Polyhedron() noexcept=default | File: ../Math/Polyhedron.h | Line: 41
static void Polyhedron_Polyhedron_41_5(Polyhedron* ptr)
{
    new(ptr) Polyhedron();
}

// Polyhedron::Polyhedron(const Polyhedron &polyhedron) | File: ../Math/Polyhedron.h | Line: 46
static void Polyhedron_Polyhedron_46_5(Polyhedron* ptr, const Polyhedron &polyhedron)
{
    new(ptr) Polyhedron(polyhedron);
}

// Polyhedron::Polyhedron(const BoundingBox &box) | File: ../Math/Polyhedron.h | Line: 59
static void Polyhedron_Polyhedron_59_14(Polyhedron* ptr, const BoundingBox &box)
{
    new(ptr) Polyhedron(box);
}

// Polyhedron::Polyhedron(const Frustum &frustum) | File: ../Math/Polyhedron.h | Line: 65
static void Polyhedron_Polyhedron_65_14(Polyhedron* ptr, const Frustum &frustum)
{
    new(ptr) Polyhedron(frustum);
}

// Polyhedron::~Polyhedron() noexcept=default | File: ../Math/Polyhedron.h | Line: 43
static void Polyhedron_Destructor_Polyhedron_43_5(Polyhedron* ptr)
{
    ptr->~Polyhedron();
}

// Quaternion::Quaternion() noexcept | File: ../Math/Quaternion.h | Line: 39
static void Quaternion_Quaternion_39_5(Quaternion* ptr)
{
    new(ptr) Quaternion();
}

// Quaternion::Quaternion(const Quaternion &quat) noexcept | File: ../Math/Quaternion.h | Line: 53
static void Quaternion_Quaternion_53_5(Quaternion* ptr, const Quaternion &quat)
{
    new(ptr) Quaternion(quat);
}

// Quaternion::Quaternion(float w, float x, float y, float z) noexcept | File: ../Math/Quaternion.h | Line: 68
static void Quaternion_Quaternion_68_5(Quaternion* ptr, float w, float x, float y, float z)
{
    new(ptr) Quaternion(w, x, y, z);
}

// Quaternion::Quaternion(float angle, const Vector3 &axis) noexcept | File: ../Math/Quaternion.h | Line: 97
static void Quaternion_Quaternion_97_5(Quaternion* ptr, float angle, const Vector3 &axis)
{
    new(ptr) Quaternion(angle, axis);
}

// Quaternion::Quaternion(float angle) noexcept | File: ../Math/Quaternion.h | Line: 103
static void Quaternion_Quaternion_103_14(Quaternion* ptr, float angle)
{
    new(ptr) Quaternion(angle);
}

// Quaternion::Quaternion(float x, float y, float z) noexcept | File: ../Math/Quaternion.h | Line: 109
static void Quaternion_Quaternion_109_5(Quaternion* ptr, float x, float y, float z)
{
    new(ptr) Quaternion(x, y, z);
}

// Quaternion::Quaternion(const Vector3 &angles) noexcept | File: ../Math/Quaternion.h | Line: 115
static void Quaternion_Quaternion_115_14(Quaternion* ptr, const Vector3 &angles)
{
    new(ptr) Quaternion(angles);
}

// Quaternion::Quaternion(const Vector3 &start, const Vector3 &end) noexcept | File: ../Math/Quaternion.h | Line: 121
static void Quaternion_Quaternion_121_5(Quaternion* ptr, const Vector3 &start, const Vector3 &end)
{
    new(ptr) Quaternion(start, end);
}

// Quaternion::Quaternion(const Vector3 &xAxis, const Vector3 &yAxis, const Vector3 &zAxis) noexcept | File: ../Math/Quaternion.h | Line: 127
static void Quaternion_Quaternion_127_5(Quaternion* ptr, const Vector3 &xAxis, const Vector3 &yAxis, const Vector3 &zAxis)
{
    new(ptr) Quaternion(xAxis, yAxis, zAxis);
}

// Quaternion::Quaternion(const Matrix3 &matrix) noexcept | File: ../Math/Quaternion.h | Line: 133
static void Quaternion_Quaternion_133_14(Quaternion* ptr, const Matrix3 &matrix)
{
    new(ptr) Quaternion(matrix);
}

// Ray::Ray() noexcept=default | File: ../Math/Ray.h | Line: 42
static void Ray_Ray_42_5(Ray* ptr)
{
    new(ptr) Ray();
}

// Ray::Ray(const Vector3 &origin, const Vector3 &direction) noexcept | File: ../Math/Ray.h | Line: 45
static void Ray_Ray_45_5(Ray* ptr, const Vector3 &origin, const Vector3 &direction)
{
    new(ptr) Ray(origin, direction);
}

// Ray::Ray(const Ray &ray) noexcept=default | File: ../Math/Ray.h | Line: 51
static void Ray_Ray_51_5(Ray* ptr, const Ray &ray)
{
    new(ptr) Ray(ray);
}

// Rect::Rect() noexcept | File: ../Math/Rect.h | Line: 36
static void Rect_Rect_36_5(Rect* ptr)
{
    new(ptr) Rect();
}

// Rect::Rect(const Vector2 &min, const Vector2 &max) noexcept | File: ../Math/Rect.h | Line: 43
static void Rect_Rect_43_5(Rect* ptr, const Vector2 &min, const Vector2 &max)
{
    new(ptr) Rect(min, max);
}

// Rect::Rect(float left, float top, float right, float bottom) noexcept | File: ../Math/Rect.h | Line: 50
static void Rect_Rect_50_5(Rect* ptr, float left, float top, float right, float bottom)
{
    new(ptr) Rect(left, top, right, bottom);
}

// Rect::Rect(const Vector4 &vector) noexcept | File: ../Math/Rect.h | Line: 57
static void Rect_Rect_57_14(Rect* ptr, const Vector4 &vector)
{
    new(ptr) Rect(vector);
}

// Rect::Rect(const Rect &rect) noexcept=default | File: ../Math/Rect.h | Line: 72
static void Rect_Rect_72_5(Rect* ptr, const Rect &rect)
{
    new(ptr) Rect(rect);
}

// Sphere::Sphere() noexcept | File: ../Math/Sphere.h | Line: 40
static void Sphere_Sphere_40_5(Sphere* ptr)
{
    new(ptr) Sphere();
}

// Sphere::Sphere(const Sphere &sphere) noexcept=default | File: ../Math/Sphere.h | Line: 47
static void Sphere_Sphere_47_5(Sphere* ptr, const Sphere &sphere)
{
    new(ptr) Sphere(sphere);
}

// Sphere::Sphere(const Vector3 &center, float radius) noexcept | File: ../Math/Sphere.h | Line: 50
static void Sphere_Sphere_50_5(Sphere* ptr, const Vector3 &center, float radius)
{
    new(ptr) Sphere(center, radius);
}

// Sphere::Sphere(const BoundingBox &box) noexcept | File: ../Math/Sphere.h | Line: 64
static void Sphere_Sphere_64_14(Sphere* ptr, const BoundingBox &box)
{
    new(ptr) Sphere(box);
}

// Sphere::Sphere(const Frustum &frustum) noexcept | File: ../Math/Sphere.h | Line: 70
static void Sphere_Sphere_70_14(Sphere* ptr, const Frustum &frustum)
{
    new(ptr) Sphere(frustum);
}

// Sphere::Sphere(const Polyhedron &poly) noexcept | File: ../Math/Sphere.h | Line: 76
static void Sphere_Sphere_76_14(Sphere* ptr, const Polyhedron &poly)
{
    new(ptr) Sphere(poly);
}

// Vector3::Vector3() noexcept | File: ../Math/Vector3.h | Line: 190
static void Vector3_Vector3_190_5(Vector3* ptr)
{
    new(ptr) Vector3();
}

// Vector3::Vector3(const Vector3 &vector) noexcept=default | File: ../Math/Vector3.h | Line: 198
static void Vector3_Vector3_198_5(Vector3* ptr, const Vector3 &vector)
{
    new(ptr) Vector3(vector);
}

// Vector3::Vector3(const Vector2 &vector, float z) noexcept | File: ../Math/Vector3.h | Line: 201
static void Vector3_Vector3_201_5(Vector3* ptr, const Vector2 &vector, float z)
{
    new(ptr) Vector3(vector, z);
}

// Vector3::Vector3(const Vector2 &vector) noexcept | File: ../Math/Vector3.h | Line: 209
static void Vector3_Vector3_209_14(Vector3* ptr, const Vector2 &vector)
{
    new(ptr) Vector3(vector);
}

// Vector3::Vector3(const IntVector3 &vector) noexcept | File: ../Math/Vector3.h | Line: 217
static void Vector3_Vector3_217_14(Vector3* ptr, const IntVector3 &vector)
{
    new(ptr) Vector3(vector);
}

// Vector3::Vector3(float x, float y, float z) noexcept | File: ../Math/Vector3.h | Line: 225
static void Vector3_Vector3_225_5(Vector3* ptr, float x, float y, float z)
{
    new(ptr) Vector3(x, y, z);
}

// Vector3::Vector3(float x, float y) noexcept | File: ../Math/Vector3.h | Line: 233
static void Vector3_Vector3_233_5(Vector3* ptr, float x, float y)
{
    new(ptr) Vector3(x, y);
}

void RegisterGenerated(asIScriptEngine* engine)
{
    // enum AttributeMode | File: ../Core/Attribute.h | Line: 35
    engine->RegisterEnum("AttributeMode");
    engine->RegisterEnumValue("AttributeMode", "AM_EDIT", AM_EDIT);
    engine->RegisterEnumValue("AttributeMode", "AM_FILE", AM_FILE);
    engine->RegisterEnumValue("AttributeMode", "AM_NET", AM_NET);
    engine->RegisterEnumValue("AttributeMode", "AM_DEFAULT", AM_DEFAULT);
    engine->RegisterEnumValue("AttributeMode", "AM_LATESTDATA", AM_LATESTDATA);
    engine->RegisterEnumValue("AttributeMode", "AM_NOEDIT", AM_NOEDIT);
    engine->RegisterEnumValue("AttributeMode", "AM_NODEID", AM_NODEID);
    engine->RegisterEnumValue("AttributeMode", "AM_COMPONENTID", AM_COMPONENTID);
    engine->RegisterEnumValue("AttributeMode", "AM_NODEIDVECTOR", AM_NODEIDVECTOR);
    engine->RegisterEnumValue("AttributeMode", "AM_FILEREADONLY", AM_FILEREADONLY);

    // enum InterpolationMode | File: ../Core/Spline.h | Line: 37
    engine->RegisterEnum("InterpolationMode");
    engine->RegisterEnumValue("InterpolationMode", "BEZIER_CURVE", BEZIER_CURVE);
    engine->RegisterEnumValue("InterpolationMode", "CATMULL_ROM_CURVE", CATMULL_ROM_CURVE);
    engine->RegisterEnumValue("InterpolationMode", "LINEAR_CURVE", LINEAR_CURVE);
    engine->RegisterEnumValue("InterpolationMode", "CATMULL_ROM_FULL_CURVE", CATMULL_ROM_FULL_CURVE);

    // enum VariantType | File: ../Core/Variant.h | Line: 42
    engine->RegisterEnum("VariantType");
    engine->RegisterEnumValue("VariantType", "VAR_NONE", VAR_NONE);
    engine->RegisterEnumValue("VariantType", "VAR_INT", VAR_INT);
    engine->RegisterEnumValue("VariantType", "VAR_BOOL", VAR_BOOL);
    engine->RegisterEnumValue("VariantType", "VAR_FLOAT", VAR_FLOAT);
    engine->RegisterEnumValue("VariantType", "VAR_VECTOR2", VAR_VECTOR2);
    engine->RegisterEnumValue("VariantType", "VAR_VECTOR3", VAR_VECTOR3);
    engine->RegisterEnumValue("VariantType", "VAR_VECTOR4", VAR_VECTOR4);
    engine->RegisterEnumValue("VariantType", "VAR_QUATERNION", VAR_QUATERNION);
    engine->RegisterEnumValue("VariantType", "VAR_COLOR", VAR_COLOR);
    engine->RegisterEnumValue("VariantType", "VAR_STRING", VAR_STRING);
    engine->RegisterEnumValue("VariantType", "VAR_BUFFER", VAR_BUFFER);
    engine->RegisterEnumValue("VariantType", "VAR_VOIDPTR", VAR_VOIDPTR);
    engine->RegisterEnumValue("VariantType", "VAR_RESOURCEREF", VAR_RESOURCEREF);
    engine->RegisterEnumValue("VariantType", "VAR_RESOURCEREFLIST", VAR_RESOURCEREFLIST);
    engine->RegisterEnumValue("VariantType", "VAR_VARIANTVECTOR", VAR_VARIANTVECTOR);
    engine->RegisterEnumValue("VariantType", "VAR_VARIANTMAP", VAR_VARIANTMAP);
    engine->RegisterEnumValue("VariantType", "VAR_INTRECT", VAR_INTRECT);
    engine->RegisterEnumValue("VariantType", "VAR_INTVECTOR2", VAR_INTVECTOR2);
    engine->RegisterEnumValue("VariantType", "VAR_PTR", VAR_PTR);
    engine->RegisterEnumValue("VariantType", "VAR_MATRIX3", VAR_MATRIX3);
    engine->RegisterEnumValue("VariantType", "VAR_MATRIX3X4", VAR_MATRIX3X4);
    engine->RegisterEnumValue("VariantType", "VAR_MATRIX4", VAR_MATRIX4);
    engine->RegisterEnumValue("VariantType", "VAR_DOUBLE", VAR_DOUBLE);
    engine->RegisterEnumValue("VariantType", "VAR_STRINGVECTOR", VAR_STRINGVECTOR);
    engine->RegisterEnumValue("VariantType", "VAR_RECT", VAR_RECT);
    engine->RegisterEnumValue("VariantType", "VAR_INTVECTOR3", VAR_INTVECTOR3);
    engine->RegisterEnumValue("VariantType", "VAR_INT64", VAR_INT64);
    engine->RegisterEnumValue("VariantType", "VAR_CUSTOM_HEAP", VAR_CUSTOM_HEAP);
    engine->RegisterEnumValue("VariantType", "VAR_CUSTOM_STACK", VAR_CUSTOM_STACK);
    engine->RegisterEnumValue("VariantType", "MAX_VAR_TYPES", MAX_VAR_TYPES);

#ifdef URHO3D_DATABASE
    // enum DBAPI | File: ../Database/Database.h | Line: 35
    engine->RegisterEnum("DBAPI");
    engine->RegisterEnumValue("DBAPI", "DBAPI_SQLITE", DBAPI_SQLITE);
    engine->RegisterEnumValue("DBAPI", "DBAPI_ODBC", DBAPI_ODBC);
#endif

    // enum AnimationChannel | File: ../Graphics/Animation.h | Line: 37
    engine->RegisterEnum("AnimationChannel");
    engine->RegisterEnumValue("AnimationChannel", "CHANNEL_NONE", CHANNEL_NONE);
    engine->RegisterEnumValue("AnimationChannel", "CHANNEL_POSITION", CHANNEL_POSITION);
    engine->RegisterEnumValue("AnimationChannel", "CHANNEL_ROTATION", CHANNEL_ROTATION);
    engine->RegisterEnumValue("AnimationChannel", "CHANNEL_SCALE", CHANNEL_SCALE);

    // enum AnimationBlendMode | File: ../Graphics/AnimationState.h | Line: 43
    engine->RegisterEnum("AnimationBlendMode");
    engine->RegisterEnumValue("AnimationBlendMode", "ABM_LERP", ABM_LERP);
    engine->RegisterEnumValue("AnimationBlendMode", "ABM_ADDITIVE", ABM_ADDITIVE);

    // enum ViewOverride | File: ../Graphics/Camera.h | Line: 41
    engine->RegisterEnum("ViewOverride");
    engine->RegisterEnumValue("ViewOverride", "VO_NONE", VO_NONE);
    engine->RegisterEnumValue("ViewOverride", "VO_LOW_MATERIAL_QUALITY", VO_LOW_MATERIAL_QUALITY);
    engine->RegisterEnumValue("ViewOverride", "VO_DISABLE_SHADOWS", VO_DISABLE_SHADOWS);
    engine->RegisterEnumValue("ViewOverride", "VO_DISABLE_OCCLUSION", VO_DISABLE_OCCLUSION);

    // enum PrimitiveType | File: ../Graphics/GraphicsDefs.h | Line: 45
    engine->RegisterEnum("PrimitiveType");
    engine->RegisterEnumValue("PrimitiveType", "TRIANGLE_LIST", TRIANGLE_LIST);
    engine->RegisterEnumValue("PrimitiveType", "LINE_LIST", LINE_LIST);
    engine->RegisterEnumValue("PrimitiveType", "POINT_LIST", POINT_LIST);
    engine->RegisterEnumValue("PrimitiveType", "TRIANGLE_STRIP", TRIANGLE_STRIP);
    engine->RegisterEnumValue("PrimitiveType", "LINE_STRIP", LINE_STRIP);
    engine->RegisterEnumValue("PrimitiveType", "TRIANGLE_FAN", TRIANGLE_FAN);

    // enum BlendMode | File: ../Graphics/GraphicsDefs.h | Line: 72
    engine->RegisterEnum("BlendMode");
    engine->RegisterEnumValue("BlendMode", "BLEND_REPLACE", BLEND_REPLACE);
    engine->RegisterEnumValue("BlendMode", "BLEND_ADD", BLEND_ADD);
    engine->RegisterEnumValue("BlendMode", "BLEND_MULTIPLY", BLEND_MULTIPLY);
    engine->RegisterEnumValue("BlendMode", "BLEND_ALPHA", BLEND_ALPHA);
    engine->RegisterEnumValue("BlendMode", "BLEND_ADDALPHA", BLEND_ADDALPHA);
    engine->RegisterEnumValue("BlendMode", "BLEND_PREMULALPHA", BLEND_PREMULALPHA);
    engine->RegisterEnumValue("BlendMode", "BLEND_INVDESTALPHA", BLEND_INVDESTALPHA);
    engine->RegisterEnumValue("BlendMode", "BLEND_SUBTRACT", BLEND_SUBTRACT);
    engine->RegisterEnumValue("BlendMode", "BLEND_SUBTRACTALPHA", BLEND_SUBTRACTALPHA);
    engine->RegisterEnumValue("BlendMode", "MAX_BLENDMODES", MAX_BLENDMODES);

    // enum CompareMode | File: ../Graphics/GraphicsDefs.h | Line: 87
    engine->RegisterEnum("CompareMode");
    engine->RegisterEnumValue("CompareMode", "CMP_ALWAYS", CMP_ALWAYS);
    engine->RegisterEnumValue("CompareMode", "CMP_EQUAL", CMP_EQUAL);
    engine->RegisterEnumValue("CompareMode", "CMP_NOTEQUAL", CMP_NOTEQUAL);
    engine->RegisterEnumValue("CompareMode", "CMP_LESS", CMP_LESS);
    engine->RegisterEnumValue("CompareMode", "CMP_LESSEQUAL", CMP_LESSEQUAL);
    engine->RegisterEnumValue("CompareMode", "CMP_GREATER", CMP_GREATER);
    engine->RegisterEnumValue("CompareMode", "CMP_GREATEREQUAL", CMP_GREATEREQUAL);
    engine->RegisterEnumValue("CompareMode", "MAX_COMPAREMODES", MAX_COMPAREMODES);

    // enum CullMode | File: ../Graphics/GraphicsDefs.h | Line: 100
    engine->RegisterEnum("CullMode");
    engine->RegisterEnumValue("CullMode", "CULL_NONE", CULL_NONE);
    engine->RegisterEnumValue("CullMode", "CULL_CCW", CULL_CCW);
    engine->RegisterEnumValue("CullMode", "CULL_CW", CULL_CW);
    engine->RegisterEnumValue("CullMode", "MAX_CULLMODES", MAX_CULLMODES);

    // enum FillMode | File: ../Graphics/GraphicsDefs.h | Line: 109
    engine->RegisterEnum("FillMode");
    engine->RegisterEnumValue("FillMode", "FILL_SOLID", FILL_SOLID);
    engine->RegisterEnumValue("FillMode", "FILL_WIREFRAME", FILL_WIREFRAME);
    engine->RegisterEnumValue("FillMode", "FILL_POINT", FILL_POINT);

    // enum VertexElementType | File: ../Graphics/GraphicsDefs.h | Line: 160
    engine->RegisterEnum("VertexElementType");
    engine->RegisterEnumValue("VertexElementType", "TYPE_INT", TYPE_INT);
    engine->RegisterEnumValue("VertexElementType", "TYPE_FLOAT", TYPE_FLOAT);
    engine->RegisterEnumValue("VertexElementType", "TYPE_VECTOR2", TYPE_VECTOR2);
    engine->RegisterEnumValue("VertexElementType", "TYPE_VECTOR3", TYPE_VECTOR3);
    engine->RegisterEnumValue("VertexElementType", "TYPE_VECTOR4", TYPE_VECTOR4);
    engine->RegisterEnumValue("VertexElementType", "TYPE_UBYTE4", TYPE_UBYTE4);
    engine->RegisterEnumValue("VertexElementType", "TYPE_UBYTE4_NORM", TYPE_UBYTE4_NORM);
    engine->RegisterEnumValue("VertexElementType", "MAX_VERTEX_ELEMENT_TYPES", MAX_VERTEX_ELEMENT_TYPES);

    // enum VertexElementSemantic | File: ../Graphics/GraphicsDefs.h | Line: 173
    engine->RegisterEnum("VertexElementSemantic");
    engine->RegisterEnumValue("VertexElementSemantic", "SEM_POSITION", SEM_POSITION);
    engine->RegisterEnumValue("VertexElementSemantic", "SEM_NORMAL", SEM_NORMAL);
    engine->RegisterEnumValue("VertexElementSemantic", "SEM_BINORMAL", SEM_BINORMAL);
    engine->RegisterEnumValue("VertexElementSemantic", "SEM_TANGENT", SEM_TANGENT);
    engine->RegisterEnumValue("VertexElementSemantic", "SEM_TEXCOORD", SEM_TEXCOORD);
    engine->RegisterEnumValue("VertexElementSemantic", "SEM_COLOR", SEM_COLOR);
    engine->RegisterEnumValue("VertexElementSemantic", "SEM_BLENDWEIGHTS", SEM_BLENDWEIGHTS);
    engine->RegisterEnumValue("VertexElementSemantic", "SEM_BLENDINDICES", SEM_BLENDINDICES);
    engine->RegisterEnumValue("VertexElementSemantic", "SEM_OBJECTINDEX", SEM_OBJECTINDEX);
    engine->RegisterEnumValue("VertexElementSemantic", "MAX_VERTEX_ELEMENT_SEMANTICS", MAX_VERTEX_ELEMENT_SEMANTICS);

    // enum TextureFilterMode | File: ../Graphics/GraphicsDefs.h | Line: 235
    engine->RegisterEnum("TextureFilterMode");
    engine->RegisterEnumValue("TextureFilterMode", "FILTER_NEAREST", FILTER_NEAREST);
    engine->RegisterEnumValue("TextureFilterMode", "FILTER_BILINEAR", FILTER_BILINEAR);
    engine->RegisterEnumValue("TextureFilterMode", "FILTER_TRILINEAR", FILTER_TRILINEAR);
    engine->RegisterEnumValue("TextureFilterMode", "FILTER_ANISOTROPIC", FILTER_ANISOTROPIC);
    engine->RegisterEnumValue("TextureFilterMode", "FILTER_NEAREST_ANISOTROPIC", FILTER_NEAREST_ANISOTROPIC);
    engine->RegisterEnumValue("TextureFilterMode", "FILTER_DEFAULT", FILTER_DEFAULT);
    engine->RegisterEnumValue("TextureFilterMode", "MAX_FILTERMODES", MAX_FILTERMODES);

    // enum TextureAddressMode | File: ../Graphics/GraphicsDefs.h | Line: 247
    engine->RegisterEnum("TextureAddressMode");
    engine->RegisterEnumValue("TextureAddressMode", "ADDRESS_WRAP", ADDRESS_WRAP);
    engine->RegisterEnumValue("TextureAddressMode", "ADDRESS_MIRROR", ADDRESS_MIRROR);
    engine->RegisterEnumValue("TextureAddressMode", "ADDRESS_CLAMP", ADDRESS_CLAMP);
    engine->RegisterEnumValue("TextureAddressMode", "ADDRESS_BORDER", ADDRESS_BORDER);
    engine->RegisterEnumValue("TextureAddressMode", "MAX_ADDRESSMODES", MAX_ADDRESSMODES);

    // enum TextureCoordinate | File: ../Graphics/GraphicsDefs.h | Line: 257
    engine->RegisterEnum("TextureCoordinate");
    engine->RegisterEnumValue("TextureCoordinate", "COORD_U", COORD_U);
    engine->RegisterEnumValue("TextureCoordinate", "COORD_V", COORD_V);
    engine->RegisterEnumValue("TextureCoordinate", "COORD_W", COORD_W);
    engine->RegisterEnumValue("TextureCoordinate", "MAX_COORDS", MAX_COORDS);

    // enum TextureUsage | File: ../Graphics/GraphicsDefs.h | Line: 266
    engine->RegisterEnum("TextureUsage");
    engine->RegisterEnumValue("TextureUsage", "TEXTURE_STATIC", TEXTURE_STATIC);
    engine->RegisterEnumValue("TextureUsage", "TEXTURE_DYNAMIC", TEXTURE_DYNAMIC);
    engine->RegisterEnumValue("TextureUsage", "TEXTURE_RENDERTARGET", TEXTURE_RENDERTARGET);
    engine->RegisterEnumValue("TextureUsage", "TEXTURE_DEPTHSTENCIL", TEXTURE_DEPTHSTENCIL);

    // enum CubeMapFace | File: ../Graphics/GraphicsDefs.h | Line: 275
    engine->RegisterEnum("CubeMapFace");
    engine->RegisterEnumValue("CubeMapFace", "FACE_POSITIVE_X", FACE_POSITIVE_X);
    engine->RegisterEnumValue("CubeMapFace", "FACE_NEGATIVE_X", FACE_NEGATIVE_X);
    engine->RegisterEnumValue("CubeMapFace", "FACE_POSITIVE_Y", FACE_POSITIVE_Y);
    engine->RegisterEnumValue("CubeMapFace", "FACE_NEGATIVE_Y", FACE_NEGATIVE_Y);
    engine->RegisterEnumValue("CubeMapFace", "FACE_POSITIVE_Z", FACE_POSITIVE_Z);
    engine->RegisterEnumValue("CubeMapFace", "FACE_NEGATIVE_Z", FACE_NEGATIVE_Z);
    engine->RegisterEnumValue("CubeMapFace", "MAX_CUBEMAP_FACES", MAX_CUBEMAP_FACES);

    // enum RenderSurfaceUpdateMode | File: ../Graphics/GraphicsDefs.h | Line: 298
    engine->RegisterEnum("RenderSurfaceUpdateMode");
    engine->RegisterEnumValue("RenderSurfaceUpdateMode", "SURFACE_MANUALUPDATE", SURFACE_MANUALUPDATE);
    engine->RegisterEnumValue("RenderSurfaceUpdateMode", "SURFACE_UPDATEVISIBLE", SURFACE_UPDATEVISIBLE);
    engine->RegisterEnumValue("RenderSurfaceUpdateMode", "SURFACE_UPDATEALWAYS", SURFACE_UPDATEALWAYS);

    // enum FaceCameraMode | File: ../Graphics/GraphicsDefs.h | Line: 362
    engine->RegisterEnum("FaceCameraMode");
    engine->RegisterEnumValue("FaceCameraMode", "FC_NONE", FC_NONE);
    engine->RegisterEnumValue("FaceCameraMode", "FC_ROTATE_XYZ", FC_ROTATE_XYZ);
    engine->RegisterEnumValue("FaceCameraMode", "FC_ROTATE_Y", FC_ROTATE_Y);
    engine->RegisterEnumValue("FaceCameraMode", "FC_LOOKAT_XYZ", FC_LOOKAT_XYZ);
    engine->RegisterEnumValue("FaceCameraMode", "FC_LOOKAT_Y", FC_LOOKAT_Y);
    engine->RegisterEnumValue("FaceCameraMode", "FC_LOOKAT_MIXED", FC_LOOKAT_MIXED);
    engine->RegisterEnumValue("FaceCameraMode", "FC_DIRECTION", FC_DIRECTION);

    // enum ShadowQuality | File: ../Graphics/GraphicsDefs.h | Line: 374
    engine->RegisterEnum("ShadowQuality");
    engine->RegisterEnumValue("ShadowQuality", "SHADOWQUALITY_SIMPLE_16BIT", SHADOWQUALITY_SIMPLE_16BIT);
    engine->RegisterEnumValue("ShadowQuality", "SHADOWQUALITY_SIMPLE_24BIT", SHADOWQUALITY_SIMPLE_24BIT);
    engine->RegisterEnumValue("ShadowQuality", "SHADOWQUALITY_PCF_16BIT", SHADOWQUALITY_PCF_16BIT);
    engine->RegisterEnumValue("ShadowQuality", "SHADOWQUALITY_PCF_24BIT", SHADOWQUALITY_PCF_24BIT);
    engine->RegisterEnumValue("ShadowQuality", "SHADOWQUALITY_VSM", SHADOWQUALITY_VSM);
    engine->RegisterEnumValue("ShadowQuality", "SHADOWQUALITY_BLUR_VSM", SHADOWQUALITY_BLUR_VSM);

    // enum MaterialQuality | File: ../Graphics/GraphicsDefs.h | Line: 445
    engine->RegisterEnum("MaterialQuality");
    engine->RegisterEnumValue("MaterialQuality", "QUALITY_LOW", QUALITY_LOW);
    engine->RegisterEnumValue("MaterialQuality", "QUALITY_MEDIUM", QUALITY_MEDIUM);
    engine->RegisterEnumValue("MaterialQuality", "QUALITY_HIGH", QUALITY_HIGH);
    engine->RegisterEnumValue("MaterialQuality", "QUALITY_MAX", QUALITY_MAX);

    // enum ClearTarget | File: ../Graphics/GraphicsDefs.h | Line: 453
    engine->RegisterEnum("ClearTarget");
    engine->RegisterEnumValue("ClearTarget", "CLEAR_COLOR", CLEAR_COLOR);
    engine->RegisterEnumValue("ClearTarget", "CLEAR_DEPTH", CLEAR_DEPTH);
    engine->RegisterEnumValue("ClearTarget", "CLEAR_STENCIL", CLEAR_STENCIL);

    // enum VertexMask | File: ../Graphics/GraphicsDefs.h | Line: 462
    engine->RegisterEnum("VertexMask");
    engine->RegisterEnumValue("VertexMask", "MASK_NONE", MASK_NONE);
    engine->RegisterEnumValue("VertexMask", "MASK_POSITION", MASK_POSITION);
    engine->RegisterEnumValue("VertexMask", "MASK_NORMAL", MASK_NORMAL);
    engine->RegisterEnumValue("VertexMask", "MASK_COLOR", MASK_COLOR);
    engine->RegisterEnumValue("VertexMask", "MASK_TEXCOORD1", MASK_TEXCOORD1);
    engine->RegisterEnumValue("VertexMask", "MASK_TEXCOORD2", MASK_TEXCOORD2);
    engine->RegisterEnumValue("VertexMask", "MASK_CUBETEXCOORD1", MASK_CUBETEXCOORD1);
    engine->RegisterEnumValue("VertexMask", "MASK_CUBETEXCOORD2", MASK_CUBETEXCOORD2);
    engine->RegisterEnumValue("VertexMask", "MASK_TANGENT", MASK_TANGENT);
    engine->RegisterEnumValue("VertexMask", "MASK_BLENDWEIGHTS", MASK_BLENDWEIGHTS);
    engine->RegisterEnumValue("VertexMask", "MASK_BLENDINDICES", MASK_BLENDINDICES);
    engine->RegisterEnumValue("VertexMask", "MASK_INSTANCEMATRIX1", MASK_INSTANCEMATRIX1);
    engine->RegisterEnumValue("VertexMask", "MASK_INSTANCEMATRIX2", MASK_INSTANCEMATRIX2);
    engine->RegisterEnumValue("VertexMask", "MASK_INSTANCEMATRIX3", MASK_INSTANCEMATRIX3);
    engine->RegisterEnumValue("VertexMask", "MASK_OBJECTINDEX", MASK_OBJECTINDEX);

    // enum LightType | File: ../Graphics/Light.h | Line: 40
    engine->RegisterEnum("LightType");
    engine->RegisterEnumValue("LightType", "LIGHT_DIRECTIONAL", LIGHT_DIRECTIONAL);
    engine->RegisterEnumValue("LightType", "LIGHT_SPOT", LIGHT_SPOT);
    engine->RegisterEnumValue("LightType", "LIGHT_POINT", LIGHT_POINT);

    // enum RayQueryLevel | File: ../Graphics/OctreeQuery.h | Line: 177
    engine->RegisterEnum("RayQueryLevel");
    engine->RegisterEnumValue("RayQueryLevel", "RAY_AABB", RAY_AABB);
    engine->RegisterEnumValue("RayQueryLevel", "RAY_OBB", RAY_OBB);
    engine->RegisterEnumValue("RayQueryLevel", "RAY_TRIANGLE", RAY_TRIANGLE);
    engine->RegisterEnumValue("RayQueryLevel", "RAY_TRIANGLE_UV", RAY_TRIANGLE_UV);

    // enum EmitterType | File: ../Graphics/ParticleEffect.h | Line: 35
    engine->RegisterEnum("EmitterType");
    engine->RegisterEnumValue("EmitterType", "EMITTER_SPHERE", EMITTER_SPHERE);
    engine->RegisterEnumValue("EmitterType", "EMITTER_BOX", EMITTER_BOX);
    engine->RegisterEnumValue("EmitterType", "EMITTER_SPHEREVOLUME", EMITTER_SPHEREVOLUME);
    engine->RegisterEnumValue("EmitterType", "EMITTER_CYLINDER", EMITTER_CYLINDER);
    engine->RegisterEnumValue("EmitterType", "EMITTER_RING", EMITTER_RING);

    // enum RenderCommandType | File: ../Graphics/RenderPath.h | Line: 41
    engine->RegisterEnum("RenderCommandType");
    engine->RegisterEnumValue("RenderCommandType", "CMD_NONE", CMD_NONE);
    engine->RegisterEnumValue("RenderCommandType", "CMD_CLEAR", CMD_CLEAR);
    engine->RegisterEnumValue("RenderCommandType", "CMD_SCENEPASS", CMD_SCENEPASS);
    engine->RegisterEnumValue("RenderCommandType", "CMD_QUAD", CMD_QUAD);
    engine->RegisterEnumValue("RenderCommandType", "CMD_FORWARDLIGHTS", CMD_FORWARDLIGHTS);
    engine->RegisterEnumValue("RenderCommandType", "CMD_LIGHTVOLUMES", CMD_LIGHTVOLUMES);
    engine->RegisterEnumValue("RenderCommandType", "CMD_RENDERUI", CMD_RENDERUI);
    engine->RegisterEnumValue("RenderCommandType", "CMD_SENDEVENT", CMD_SENDEVENT);

    // enum RenderCommandSortMode | File: ../Graphics/RenderPath.h | Line: 54
    engine->RegisterEnum("RenderCommandSortMode");
    engine->RegisterEnumValue("RenderCommandSortMode", "SORT_FRONTTOBACK", SORT_FRONTTOBACK);
    engine->RegisterEnumValue("RenderCommandSortMode", "SORT_BACKTOFRONT", SORT_BACKTOFRONT);

    // enum RenderTargetSizeMode | File: ../Graphics/RenderPath.h | Line: 61
    engine->RegisterEnum("RenderTargetSizeMode");
    engine->RegisterEnumValue("RenderTargetSizeMode", "SIZE_ABSOLUTE", SIZE_ABSOLUTE);
    engine->RegisterEnumValue("RenderTargetSizeMode", "SIZE_VIEWPORTDIVISOR", SIZE_VIEWPORTDIVISOR);
    engine->RegisterEnumValue("RenderTargetSizeMode", "SIZE_VIEWPORTMULTIPLIER", SIZE_VIEWPORTMULTIPLIER);

    // enum TrailType | File: ../Graphics/RibbonTrail.h | Line: 33
    engine->RegisterEnum("TrailType");
    engine->RegisterEnumValue("TrailType", "TT_FACE_CAMERA", TT_FACE_CAMERA);
    engine->RegisterEnumValue("TrailType", "TT_BONE", TT_BONE);

    // enum BoneCollisionShape | File: ../Graphics/Skeleton.h | Line: 34
    engine->RegisterEnum("BoneCollisionShape");
    engine->RegisterEnumValue("BoneCollisionShape", "BONECOLLISION_NONE", BONECOLLISION_NONE);
    engine->RegisterEnumValue("BoneCollisionShape", "BONECOLLISION_SPHERE", BONECOLLISION_SPHERE);
    engine->RegisterEnumValue("BoneCollisionShape", "BONECOLLISION_BOX", BONECOLLISION_BOX);

    // enum PassLightingMode | File: ../Graphics/Technique.h | Line: 37
    engine->RegisterEnum("PassLightingMode");
    engine->RegisterEnumValue("PassLightingMode", "LIGHTING_UNLIT", LIGHTING_UNLIT);
    engine->RegisterEnumValue("PassLightingMode", "LIGHTING_PERVERTEX", LIGHTING_PERVERTEX);
    engine->RegisterEnumValue("PassLightingMode", "LIGHTING_PERPIXEL", LIGHTING_PERPIXEL);

    // enum MouseMode | File: ../Input/Input.h | Line: 40
    engine->RegisterEnum("MouseMode");
    engine->RegisterEnumValue("MouseMode", "MM_ABSOLUTE", MM_ABSOLUTE);
    engine->RegisterEnumValue("MouseMode", "MM_RELATIVE", MM_RELATIVE);
    engine->RegisterEnumValue("MouseMode", "MM_WRAP", MM_WRAP);
    engine->RegisterEnumValue("MouseMode", "MM_FREE", MM_FREE);
    engine->RegisterEnumValue("MouseMode", "MM_INVALID", MM_INVALID);

    // enum MouseButton | File: ../Input/InputConstants.h | Line: 40
    engine->RegisterEnum("MouseButton");
    engine->RegisterEnumValue("MouseButton", "MOUSEB_NONE", MOUSEB_NONE);
    engine->RegisterEnumValue("MouseButton", "MOUSEB_LEFT", MOUSEB_LEFT);
    engine->RegisterEnumValue("MouseButton", "MOUSEB_MIDDLE", MOUSEB_MIDDLE);
    engine->RegisterEnumValue("MouseButton", "MOUSEB_RIGHT", MOUSEB_RIGHT);
    engine->RegisterEnumValue("MouseButton", "MOUSEB_X1", MOUSEB_X1);
    engine->RegisterEnumValue("MouseButton", "MOUSEB_X2", MOUSEB_X2);
    engine->RegisterEnumValue("MouseButton", "MOUSEB_ANY", MOUSEB_ANY);

    // enum Qualifier | File: ../Input/InputConstants.h | Line: 52
    engine->RegisterEnum("Qualifier");
    engine->RegisterEnumValue("Qualifier", "QUAL_NONE", QUAL_NONE);
    engine->RegisterEnumValue("Qualifier", "QUAL_SHIFT", QUAL_SHIFT);
    engine->RegisterEnumValue("Qualifier", "QUAL_CTRL", QUAL_CTRL);
    engine->RegisterEnumValue("Qualifier", "QUAL_ALT", QUAL_ALT);
    engine->RegisterEnumValue("Qualifier", "QUAL_ANY", QUAL_ANY);

    // enum Key | File: ../Input/InputConstants.h | Line: 63
    engine->RegisterEnum("Key");
    engine->RegisterEnumValue("Key", "KEY_UNKNOWN", KEY_UNKNOWN);
    engine->RegisterEnumValue("Key", "KEY_A", KEY_A);
    engine->RegisterEnumValue("Key", "KEY_B", KEY_B);
    engine->RegisterEnumValue("Key", "KEY_C", KEY_C);
    engine->RegisterEnumValue("Key", "KEY_D", KEY_D);
    engine->RegisterEnumValue("Key", "KEY_E", KEY_E);
    engine->RegisterEnumValue("Key", "KEY_F", KEY_F);
    engine->RegisterEnumValue("Key", "KEY_G", KEY_G);
    engine->RegisterEnumValue("Key", "KEY_H", KEY_H);
    engine->RegisterEnumValue("Key", "KEY_I", KEY_I);
    engine->RegisterEnumValue("Key", "KEY_J", KEY_J);
    engine->RegisterEnumValue("Key", "KEY_K", KEY_K);
    engine->RegisterEnumValue("Key", "KEY_L", KEY_L);
    engine->RegisterEnumValue("Key", "KEY_M", KEY_M);
    engine->RegisterEnumValue("Key", "KEY_N", KEY_N);
    engine->RegisterEnumValue("Key", "KEY_O", KEY_O);
    engine->RegisterEnumValue("Key", "KEY_P", KEY_P);
    engine->RegisterEnumValue("Key", "KEY_Q", KEY_Q);
    engine->RegisterEnumValue("Key", "KEY_R", KEY_R);
    engine->RegisterEnumValue("Key", "KEY_S", KEY_S);
    engine->RegisterEnumValue("Key", "KEY_T", KEY_T);
    engine->RegisterEnumValue("Key", "KEY_U", KEY_U);
    engine->RegisterEnumValue("Key", "KEY_V", KEY_V);
    engine->RegisterEnumValue("Key", "KEY_W", KEY_W);
    engine->RegisterEnumValue("Key", "KEY_X", KEY_X);
    engine->RegisterEnumValue("Key", "KEY_Y", KEY_Y);
    engine->RegisterEnumValue("Key", "KEY_Z", KEY_Z);
    engine->RegisterEnumValue("Key", "KEY_0", KEY_0);
    engine->RegisterEnumValue("Key", "KEY_1", KEY_1);
    engine->RegisterEnumValue("Key", "KEY_2", KEY_2);
    engine->RegisterEnumValue("Key", "KEY_3", KEY_3);
    engine->RegisterEnumValue("Key", "KEY_4", KEY_4);
    engine->RegisterEnumValue("Key", "KEY_5", KEY_5);
    engine->RegisterEnumValue("Key", "KEY_6", KEY_6);
    engine->RegisterEnumValue("Key", "KEY_7", KEY_7);
    engine->RegisterEnumValue("Key", "KEY_8", KEY_8);
    engine->RegisterEnumValue("Key", "KEY_9", KEY_9);
    engine->RegisterEnumValue("Key", "KEY_BACKSPACE", KEY_BACKSPACE);
    engine->RegisterEnumValue("Key", "KEY_TAB", KEY_TAB);
    engine->RegisterEnumValue("Key", "KEY_RETURN", KEY_RETURN);
    engine->RegisterEnumValue("Key", "KEY_RETURN2", KEY_RETURN2);
    engine->RegisterEnumValue("Key", "KEY_KP_ENTER", KEY_KP_ENTER);
    engine->RegisterEnumValue("Key", "KEY_SHIFT", KEY_SHIFT);
    engine->RegisterEnumValue("Key", "KEY_CTRL", KEY_CTRL);
    engine->RegisterEnumValue("Key", "KEY_ALT", KEY_ALT);
    engine->RegisterEnumValue("Key", "KEY_GUI", KEY_GUI);
    engine->RegisterEnumValue("Key", "KEY_PAUSE", KEY_PAUSE);
    engine->RegisterEnumValue("Key", "KEY_CAPSLOCK", KEY_CAPSLOCK);
    engine->RegisterEnumValue("Key", "KEY_ESCAPE", KEY_ESCAPE);
    engine->RegisterEnumValue("Key", "KEY_SPACE", KEY_SPACE);
    engine->RegisterEnumValue("Key", "KEY_PAGEUP", KEY_PAGEUP);
    engine->RegisterEnumValue("Key", "KEY_PAGEDOWN", KEY_PAGEDOWN);
    engine->RegisterEnumValue("Key", "KEY_END", KEY_END);
    engine->RegisterEnumValue("Key", "KEY_HOME", KEY_HOME);
    engine->RegisterEnumValue("Key", "KEY_LEFT", KEY_LEFT);
    engine->RegisterEnumValue("Key", "KEY_UP", KEY_UP);
    engine->RegisterEnumValue("Key", "KEY_RIGHT", KEY_RIGHT);
    engine->RegisterEnumValue("Key", "KEY_DOWN", KEY_DOWN);
    engine->RegisterEnumValue("Key", "KEY_SELECT", KEY_SELECT);
    engine->RegisterEnumValue("Key", "KEY_PRINTSCREEN", KEY_PRINTSCREEN);
    engine->RegisterEnumValue("Key", "KEY_INSERT", KEY_INSERT);
    engine->RegisterEnumValue("Key", "KEY_DELETE", KEY_DELETE);
    engine->RegisterEnumValue("Key", "KEY_LGUI", KEY_LGUI);
    engine->RegisterEnumValue("Key", "KEY_RGUI", KEY_RGUI);
    engine->RegisterEnumValue("Key", "KEY_APPLICATION", KEY_APPLICATION);
    engine->RegisterEnumValue("Key", "KEY_KP_0", KEY_KP_0);
    engine->RegisterEnumValue("Key", "KEY_KP_1", KEY_KP_1);
    engine->RegisterEnumValue("Key", "KEY_KP_2", KEY_KP_2);
    engine->RegisterEnumValue("Key", "KEY_KP_3", KEY_KP_3);
    engine->RegisterEnumValue("Key", "KEY_KP_4", KEY_KP_4);
    engine->RegisterEnumValue("Key", "KEY_KP_5", KEY_KP_5);
    engine->RegisterEnumValue("Key", "KEY_KP_6", KEY_KP_6);
    engine->RegisterEnumValue("Key", "KEY_KP_7", KEY_KP_7);
    engine->RegisterEnumValue("Key", "KEY_KP_8", KEY_KP_8);
    engine->RegisterEnumValue("Key", "KEY_KP_9", KEY_KP_9);
    engine->RegisterEnumValue("Key", "KEY_KP_MULTIPLY", KEY_KP_MULTIPLY);
    engine->RegisterEnumValue("Key", "KEY_KP_PLUS", KEY_KP_PLUS);
    engine->RegisterEnumValue("Key", "KEY_KP_MINUS", KEY_KP_MINUS);
    engine->RegisterEnumValue("Key", "KEY_KP_PERIOD", KEY_KP_PERIOD);
    engine->RegisterEnumValue("Key", "KEY_KP_DIVIDE", KEY_KP_DIVIDE);
    engine->RegisterEnumValue("Key", "KEY_F1", KEY_F1);
    engine->RegisterEnumValue("Key", "KEY_F2", KEY_F2);
    engine->RegisterEnumValue("Key", "KEY_F3", KEY_F3);
    engine->RegisterEnumValue("Key", "KEY_F4", KEY_F4);
    engine->RegisterEnumValue("Key", "KEY_F5", KEY_F5);
    engine->RegisterEnumValue("Key", "KEY_F6", KEY_F6);
    engine->RegisterEnumValue("Key", "KEY_F7", KEY_F7);
    engine->RegisterEnumValue("Key", "KEY_F8", KEY_F8);
    engine->RegisterEnumValue("Key", "KEY_F9", KEY_F9);
    engine->RegisterEnumValue("Key", "KEY_F10", KEY_F10);
    engine->RegisterEnumValue("Key", "KEY_F11", KEY_F11);
    engine->RegisterEnumValue("Key", "KEY_F12", KEY_F12);
    engine->RegisterEnumValue("Key", "KEY_F13", KEY_F13);
    engine->RegisterEnumValue("Key", "KEY_F14", KEY_F14);
    engine->RegisterEnumValue("Key", "KEY_F15", KEY_F15);
    engine->RegisterEnumValue("Key", "KEY_F16", KEY_F16);
    engine->RegisterEnumValue("Key", "KEY_F17", KEY_F17);
    engine->RegisterEnumValue("Key", "KEY_F18", KEY_F18);
    engine->RegisterEnumValue("Key", "KEY_F19", KEY_F19);
    engine->RegisterEnumValue("Key", "KEY_F20", KEY_F20);
    engine->RegisterEnumValue("Key", "KEY_F21", KEY_F21);
    engine->RegisterEnumValue("Key", "KEY_F22", KEY_F22);
    engine->RegisterEnumValue("Key", "KEY_F23", KEY_F23);
    engine->RegisterEnumValue("Key", "KEY_F24", KEY_F24);
    engine->RegisterEnumValue("Key", "KEY_NUMLOCKCLEAR", KEY_NUMLOCKCLEAR);
    engine->RegisterEnumValue("Key", "KEY_SCROLLLOCK", KEY_SCROLLLOCK);
    engine->RegisterEnumValue("Key", "KEY_LSHIFT", KEY_LSHIFT);
    engine->RegisterEnumValue("Key", "KEY_RSHIFT", KEY_RSHIFT);
    engine->RegisterEnumValue("Key", "KEY_LCTRL", KEY_LCTRL);
    engine->RegisterEnumValue("Key", "KEY_RCTRL", KEY_RCTRL);
    engine->RegisterEnumValue("Key", "KEY_LALT", KEY_LALT);
    engine->RegisterEnumValue("Key", "KEY_RALT", KEY_RALT);
    engine->RegisterEnumValue("Key", "KEY_AC_BACK", KEY_AC_BACK);
    engine->RegisterEnumValue("Key", "KEY_AC_BOOKMARKS", KEY_AC_BOOKMARKS);
    engine->RegisterEnumValue("Key", "KEY_AC_FORWARD", KEY_AC_FORWARD);
    engine->RegisterEnumValue("Key", "KEY_AC_HOME", KEY_AC_HOME);
    engine->RegisterEnumValue("Key", "KEY_AC_REFRESH", KEY_AC_REFRESH);
    engine->RegisterEnumValue("Key", "KEY_AC_SEARCH", KEY_AC_SEARCH);
    engine->RegisterEnumValue("Key", "KEY_AC_STOP", KEY_AC_STOP);
    engine->RegisterEnumValue("Key", "KEY_AGAIN", KEY_AGAIN);
    engine->RegisterEnumValue("Key", "KEY_ALTERASE", KEY_ALTERASE);
    engine->RegisterEnumValue("Key", "KEY_AMPERSAND", KEY_AMPERSAND);
    engine->RegisterEnumValue("Key", "KEY_ASTERISK", KEY_ASTERISK);
    engine->RegisterEnumValue("Key", "KEY_AT", KEY_AT);
    engine->RegisterEnumValue("Key", "KEY_AUDIOMUTE", KEY_AUDIOMUTE);
    engine->RegisterEnumValue("Key", "KEY_AUDIONEXT", KEY_AUDIONEXT);
    engine->RegisterEnumValue("Key", "KEY_AUDIOPLAY", KEY_AUDIOPLAY);
    engine->RegisterEnumValue("Key", "KEY_AUDIOPREV", KEY_AUDIOPREV);
    engine->RegisterEnumValue("Key", "KEY_AUDIOSTOP", KEY_AUDIOSTOP);
    engine->RegisterEnumValue("Key", "KEY_BACKQUOTE", KEY_BACKQUOTE);
    engine->RegisterEnumValue("Key", "KEY_BACKSLASH", KEY_BACKSLASH);
    engine->RegisterEnumValue("Key", "KEY_BRIGHTNESSDOWN", KEY_BRIGHTNESSDOWN);
    engine->RegisterEnumValue("Key", "KEY_BRIGHTNESSUP", KEY_BRIGHTNESSUP);
    engine->RegisterEnumValue("Key", "KEY_CALCULATOR", KEY_CALCULATOR);
    engine->RegisterEnumValue("Key", "KEY_CANCEL", KEY_CANCEL);
    engine->RegisterEnumValue("Key", "KEY_CARET", KEY_CARET);
    engine->RegisterEnumValue("Key", "KEY_CLEAR", KEY_CLEAR);
    engine->RegisterEnumValue("Key", "KEY_CLEARAGAIN", KEY_CLEARAGAIN);
    engine->RegisterEnumValue("Key", "KEY_COLON", KEY_COLON);
    engine->RegisterEnumValue("Key", "KEY_COMMA", KEY_COMMA);
    engine->RegisterEnumValue("Key", "KEY_COMPUTER", KEY_COMPUTER);
    engine->RegisterEnumValue("Key", "KEY_COPY", KEY_COPY);
    engine->RegisterEnumValue("Key", "KEY_CRSEL", KEY_CRSEL);
    engine->RegisterEnumValue("Key", "KEY_CURRENCYSUBUNIT", KEY_CURRENCYSUBUNIT);
    engine->RegisterEnumValue("Key", "KEY_CURRENCYUNIT", KEY_CURRENCYUNIT);
    engine->RegisterEnumValue("Key", "KEY_CUT", KEY_CUT);
    engine->RegisterEnumValue("Key", "KEY_DECIMALSEPARATOR", KEY_DECIMALSEPARATOR);
    engine->RegisterEnumValue("Key", "KEY_DISPLAYSWITCH", KEY_DISPLAYSWITCH);
    engine->RegisterEnumValue("Key", "KEY_DOLLAR", KEY_DOLLAR);
    engine->RegisterEnumValue("Key", "KEY_EJECT", KEY_EJECT);
    engine->RegisterEnumValue("Key", "KEY_EQUALS", KEY_EQUALS);
    engine->RegisterEnumValue("Key", "KEY_EXCLAIM", KEY_EXCLAIM);
    engine->RegisterEnumValue("Key", "KEY_EXSEL", KEY_EXSEL);
    engine->RegisterEnumValue("Key", "KEY_FIND", KEY_FIND);
    engine->RegisterEnumValue("Key", "KEY_GREATER", KEY_GREATER);
    engine->RegisterEnumValue("Key", "KEY_HASH", KEY_HASH);
    engine->RegisterEnumValue("Key", "KEY_HELP", KEY_HELP);
    engine->RegisterEnumValue("Key", "KEY_KBDILLUMDOWN", KEY_KBDILLUMDOWN);
    engine->RegisterEnumValue("Key", "KEY_KBDILLUMTOGGLE", KEY_KBDILLUMTOGGLE);
    engine->RegisterEnumValue("Key", "KEY_KBDILLUMUP", KEY_KBDILLUMUP);
    engine->RegisterEnumValue("Key", "KEY_KP_00", KEY_KP_00);
    engine->RegisterEnumValue("Key", "KEY_KP_000", KEY_KP_000);
    engine->RegisterEnumValue("Key", "KEY_KP_A", KEY_KP_A);
    engine->RegisterEnumValue("Key", "KEY_KP_AMPERSAND", KEY_KP_AMPERSAND);
    engine->RegisterEnumValue("Key", "KEY_KP_AT", KEY_KP_AT);
    engine->RegisterEnumValue("Key", "KEY_KP_B", KEY_KP_B);
    engine->RegisterEnumValue("Key", "KEY_KP_BACKSPACE", KEY_KP_BACKSPACE);
    engine->RegisterEnumValue("Key", "KEY_KP_BINARY", KEY_KP_BINARY);
    engine->RegisterEnumValue("Key", "KEY_KP_C", KEY_KP_C);
    engine->RegisterEnumValue("Key", "KEY_KP_CLEAR", KEY_KP_CLEAR);
    engine->RegisterEnumValue("Key", "KEY_KP_CLEARENTRY", KEY_KP_CLEARENTRY);
    engine->RegisterEnumValue("Key", "KEY_KP_COLON", KEY_KP_COLON);
    engine->RegisterEnumValue("Key", "KEY_KP_COMMA", KEY_KP_COMMA);
    engine->RegisterEnumValue("Key", "KEY_KP_D", KEY_KP_D);
    engine->RegisterEnumValue("Key", "KEY_KP_DBLAMPERSAND", KEY_KP_DBLAMPERSAND);
    engine->RegisterEnumValue("Key", "KEY_KP_DBLVERTICALBAR", KEY_KP_DBLVERTICALBAR);
    engine->RegisterEnumValue("Key", "KEY_KP_DECIMAL", KEY_KP_DECIMAL);
    engine->RegisterEnumValue("Key", "KEY_KP_E", KEY_KP_E);
    engine->RegisterEnumValue("Key", "KEY_KP_EQUALS", KEY_KP_EQUALS);
    engine->RegisterEnumValue("Key", "KEY_KP_EQUALSAS400", KEY_KP_EQUALSAS400);
    engine->RegisterEnumValue("Key", "KEY_KP_EXCLAM", KEY_KP_EXCLAM);
    engine->RegisterEnumValue("Key", "KEY_KP_F", KEY_KP_F);
    engine->RegisterEnumValue("Key", "KEY_KP_GREATER", KEY_KP_GREATER);
    engine->RegisterEnumValue("Key", "KEY_KP_HASH", KEY_KP_HASH);
    engine->RegisterEnumValue("Key", "KEY_KP_HEXADECIMAL", KEY_KP_HEXADECIMAL);
    engine->RegisterEnumValue("Key", "KEY_KP_LEFTBRACE", KEY_KP_LEFTBRACE);
    engine->RegisterEnumValue("Key", "KEY_KP_LEFTPAREN", KEY_KP_LEFTPAREN);
    engine->RegisterEnumValue("Key", "KEY_KP_LESS", KEY_KP_LESS);
    engine->RegisterEnumValue("Key", "KEY_KP_MEMADD", KEY_KP_MEMADD);
    engine->RegisterEnumValue("Key", "KEY_KP_MEMCLEAR", KEY_KP_MEMCLEAR);
    engine->RegisterEnumValue("Key", "KEY_KP_MEMDIVIDE", KEY_KP_MEMDIVIDE);
    engine->RegisterEnumValue("Key", "KEY_KP_MEMMULTIPLY", KEY_KP_MEMMULTIPLY);
    engine->RegisterEnumValue("Key", "KEY_KP_MEMRECALL", KEY_KP_MEMRECALL);
    engine->RegisterEnumValue("Key", "KEY_KP_MEMSTORE", KEY_KP_MEMSTORE);
    engine->RegisterEnumValue("Key", "KEY_KP_MEMSUBTRACT", KEY_KP_MEMSUBTRACT);
    engine->RegisterEnumValue("Key", "KEY_KP_OCTAL", KEY_KP_OCTAL);
    engine->RegisterEnumValue("Key", "KEY_KP_PERCENT", KEY_KP_PERCENT);
    engine->RegisterEnumValue("Key", "KEY_KP_PLUSMINUS", KEY_KP_PLUSMINUS);
    engine->RegisterEnumValue("Key", "KEY_KP_POWER", KEY_KP_POWER);
    engine->RegisterEnumValue("Key", "KEY_KP_RIGHTBRACE", KEY_KP_RIGHTBRACE);
    engine->RegisterEnumValue("Key", "KEY_KP_RIGHTPAREN", KEY_KP_RIGHTPAREN);
    engine->RegisterEnumValue("Key", "KEY_KP_SPACE", KEY_KP_SPACE);
    engine->RegisterEnumValue("Key", "KEY_KP_TAB", KEY_KP_TAB);
    engine->RegisterEnumValue("Key", "KEY_KP_VERTICALBAR", KEY_KP_VERTICALBAR);
    engine->RegisterEnumValue("Key", "KEY_KP_XOR", KEY_KP_XOR);
    engine->RegisterEnumValue("Key", "KEY_LEFTBRACKET", KEY_LEFTBRACKET);
    engine->RegisterEnumValue("Key", "KEY_LEFTPAREN", KEY_LEFTPAREN);
    engine->RegisterEnumValue("Key", "KEY_LESS", KEY_LESS);
    engine->RegisterEnumValue("Key", "KEY_MAIL", KEY_MAIL);
    engine->RegisterEnumValue("Key", "KEY_MEDIASELECT", KEY_MEDIASELECT);
    engine->RegisterEnumValue("Key", "KEY_MENU", KEY_MENU);
    engine->RegisterEnumValue("Key", "KEY_MINUS", KEY_MINUS);
    engine->RegisterEnumValue("Key", "KEY_MODE", KEY_MODE);
    engine->RegisterEnumValue("Key", "KEY_MUTE", KEY_MUTE);
    engine->RegisterEnumValue("Key", "KEY_OPER", KEY_OPER);
    engine->RegisterEnumValue("Key", "KEY_OUT", KEY_OUT);
    engine->RegisterEnumValue("Key", "KEY_PASTE", KEY_PASTE);
    engine->RegisterEnumValue("Key", "KEY_PERCENT", KEY_PERCENT);
    engine->RegisterEnumValue("Key", "KEY_PERIOD", KEY_PERIOD);
    engine->RegisterEnumValue("Key", "KEY_PLUS", KEY_PLUS);
    engine->RegisterEnumValue("Key", "KEY_POWER", KEY_POWER);
    engine->RegisterEnumValue("Key", "KEY_PRIOR", KEY_PRIOR);
    engine->RegisterEnumValue("Key", "KEY_QUESTION", KEY_QUESTION);
    engine->RegisterEnumValue("Key", "KEY_QUOTE", KEY_QUOTE);
    engine->RegisterEnumValue("Key", "KEY_QUOTEDBL", KEY_QUOTEDBL);
    engine->RegisterEnumValue("Key", "KEY_RIGHTBRACKET", KEY_RIGHTBRACKET);
    engine->RegisterEnumValue("Key", "KEY_RIGHTPAREN", KEY_RIGHTPAREN);
    engine->RegisterEnumValue("Key", "KEY_SEMICOLON", KEY_SEMICOLON);
    engine->RegisterEnumValue("Key", "KEY_SEPARATOR", KEY_SEPARATOR);
    engine->RegisterEnumValue("Key", "KEY_SLASH", KEY_SLASH);
    engine->RegisterEnumValue("Key", "KEY_SLEEP", KEY_SLEEP);
    engine->RegisterEnumValue("Key", "KEY_STOP", KEY_STOP);
    engine->RegisterEnumValue("Key", "KEY_SYSREQ", KEY_SYSREQ);
    engine->RegisterEnumValue("Key", "KEY_THOUSANDSSEPARATOR", KEY_THOUSANDSSEPARATOR);
    engine->RegisterEnumValue("Key", "KEY_UNDERSCORE", KEY_UNDERSCORE);
    engine->RegisterEnumValue("Key", "KEY_UNDO", KEY_UNDO);
    engine->RegisterEnumValue("Key", "KEY_VOLUMEDOWN", KEY_VOLUMEDOWN);
    engine->RegisterEnumValue("Key", "KEY_VOLUMEUP", KEY_VOLUMEUP);
    engine->RegisterEnumValue("Key", "KEY_WWW", KEY_WWW);

    // enum Scancode | File: ../Input/InputConstants.h | Line: 306
    engine->RegisterEnum("Scancode");
    engine->RegisterEnumValue("Scancode", "SCANCODE_UNKNOWN", SCANCODE_UNKNOWN);
    engine->RegisterEnumValue("Scancode", "SCANCODE_CTRL", SCANCODE_CTRL);
    engine->RegisterEnumValue("Scancode", "SCANCODE_SHIFT", SCANCODE_SHIFT);
    engine->RegisterEnumValue("Scancode", "SCANCODE_ALT", SCANCODE_ALT);
    engine->RegisterEnumValue("Scancode", "SCANCODE_GUI", SCANCODE_GUI);
    engine->RegisterEnumValue("Scancode", "SCANCODE_A", SCANCODE_A);
    engine->RegisterEnumValue("Scancode", "SCANCODE_B", SCANCODE_B);
    engine->RegisterEnumValue("Scancode", "SCANCODE_C", SCANCODE_C);
    engine->RegisterEnumValue("Scancode", "SCANCODE_D", SCANCODE_D);
    engine->RegisterEnumValue("Scancode", "SCANCODE_E", SCANCODE_E);
    engine->RegisterEnumValue("Scancode", "SCANCODE_F", SCANCODE_F);
    engine->RegisterEnumValue("Scancode", "SCANCODE_G", SCANCODE_G);
    engine->RegisterEnumValue("Scancode", "SCANCODE_H", SCANCODE_H);
    engine->RegisterEnumValue("Scancode", "SCANCODE_I", SCANCODE_I);
    engine->RegisterEnumValue("Scancode", "SCANCODE_J", SCANCODE_J);
    engine->RegisterEnumValue("Scancode", "SCANCODE_K", SCANCODE_K);
    engine->RegisterEnumValue("Scancode", "SCANCODE_L", SCANCODE_L);
    engine->RegisterEnumValue("Scancode", "SCANCODE_M", SCANCODE_M);
    engine->RegisterEnumValue("Scancode", "SCANCODE_N", SCANCODE_N);
    engine->RegisterEnumValue("Scancode", "SCANCODE_O", SCANCODE_O);
    engine->RegisterEnumValue("Scancode", "SCANCODE_P", SCANCODE_P);
    engine->RegisterEnumValue("Scancode", "SCANCODE_Q", SCANCODE_Q);
    engine->RegisterEnumValue("Scancode", "SCANCODE_R", SCANCODE_R);
    engine->RegisterEnumValue("Scancode", "SCANCODE_S", SCANCODE_S);
    engine->RegisterEnumValue("Scancode", "SCANCODE_T", SCANCODE_T);
    engine->RegisterEnumValue("Scancode", "SCANCODE_U", SCANCODE_U);
    engine->RegisterEnumValue("Scancode", "SCANCODE_V", SCANCODE_V);
    engine->RegisterEnumValue("Scancode", "SCANCODE_W", SCANCODE_W);
    engine->RegisterEnumValue("Scancode", "SCANCODE_X", SCANCODE_X);
    engine->RegisterEnumValue("Scancode", "SCANCODE_Y", SCANCODE_Y);
    engine->RegisterEnumValue("Scancode", "SCANCODE_Z", SCANCODE_Z);
    engine->RegisterEnumValue("Scancode", "SCANCODE_1", SCANCODE_1);
    engine->RegisterEnumValue("Scancode", "SCANCODE_2", SCANCODE_2);
    engine->RegisterEnumValue("Scancode", "SCANCODE_3", SCANCODE_3);
    engine->RegisterEnumValue("Scancode", "SCANCODE_4", SCANCODE_4);
    engine->RegisterEnumValue("Scancode", "SCANCODE_5", SCANCODE_5);
    engine->RegisterEnumValue("Scancode", "SCANCODE_6", SCANCODE_6);
    engine->RegisterEnumValue("Scancode", "SCANCODE_7", SCANCODE_7);
    engine->RegisterEnumValue("Scancode", "SCANCODE_8", SCANCODE_8);
    engine->RegisterEnumValue("Scancode", "SCANCODE_9", SCANCODE_9);
    engine->RegisterEnumValue("Scancode", "SCANCODE_0", SCANCODE_0);
    engine->RegisterEnumValue("Scancode", "SCANCODE_RETURN", SCANCODE_RETURN);
    engine->RegisterEnumValue("Scancode", "SCANCODE_ESCAPE", SCANCODE_ESCAPE);
    engine->RegisterEnumValue("Scancode", "SCANCODE_BACKSPACE", SCANCODE_BACKSPACE);
    engine->RegisterEnumValue("Scancode", "SCANCODE_TAB", SCANCODE_TAB);
    engine->RegisterEnumValue("Scancode", "SCANCODE_SPACE", SCANCODE_SPACE);
    engine->RegisterEnumValue("Scancode", "SCANCODE_MINUS", SCANCODE_MINUS);
    engine->RegisterEnumValue("Scancode", "SCANCODE_EQUALS", SCANCODE_EQUALS);
    engine->RegisterEnumValue("Scancode", "SCANCODE_LEFTBRACKET", SCANCODE_LEFTBRACKET);
    engine->RegisterEnumValue("Scancode", "SCANCODE_RIGHTBRACKET", SCANCODE_RIGHTBRACKET);
    engine->RegisterEnumValue("Scancode", "SCANCODE_BACKSLASH", SCANCODE_BACKSLASH);
    engine->RegisterEnumValue("Scancode", "SCANCODE_NONUSHASH", SCANCODE_NONUSHASH);
    engine->RegisterEnumValue("Scancode", "SCANCODE_SEMICOLON", SCANCODE_SEMICOLON);
    engine->RegisterEnumValue("Scancode", "SCANCODE_APOSTROPHE", SCANCODE_APOSTROPHE);
    engine->RegisterEnumValue("Scancode", "SCANCODE_GRAVE", SCANCODE_GRAVE);
    engine->RegisterEnumValue("Scancode", "SCANCODE_COMMA", SCANCODE_COMMA);
    engine->RegisterEnumValue("Scancode", "SCANCODE_PERIOD", SCANCODE_PERIOD);
    engine->RegisterEnumValue("Scancode", "SCANCODE_SLASH", SCANCODE_SLASH);
    engine->RegisterEnumValue("Scancode", "SCANCODE_CAPSLOCK", SCANCODE_CAPSLOCK);
    engine->RegisterEnumValue("Scancode", "SCANCODE_F1", SCANCODE_F1);
    engine->RegisterEnumValue("Scancode", "SCANCODE_F2", SCANCODE_F2);
    engine->RegisterEnumValue("Scancode", "SCANCODE_F3", SCANCODE_F3);
    engine->RegisterEnumValue("Scancode", "SCANCODE_F4", SCANCODE_F4);
    engine->RegisterEnumValue("Scancode", "SCANCODE_F5", SCANCODE_F5);
    engine->RegisterEnumValue("Scancode", "SCANCODE_F6", SCANCODE_F6);
    engine->RegisterEnumValue("Scancode", "SCANCODE_F7", SCANCODE_F7);
    engine->RegisterEnumValue("Scancode", "SCANCODE_F8", SCANCODE_F8);
    engine->RegisterEnumValue("Scancode", "SCANCODE_F9", SCANCODE_F9);
    engine->RegisterEnumValue("Scancode", "SCANCODE_F10", SCANCODE_F10);
    engine->RegisterEnumValue("Scancode", "SCANCODE_F11", SCANCODE_F11);
    engine->RegisterEnumValue("Scancode", "SCANCODE_F12", SCANCODE_F12);
    engine->RegisterEnumValue("Scancode", "SCANCODE_PRINTSCREEN", SCANCODE_PRINTSCREEN);
    engine->RegisterEnumValue("Scancode", "SCANCODE_SCROLLLOCK", SCANCODE_SCROLLLOCK);
    engine->RegisterEnumValue("Scancode", "SCANCODE_PAUSE", SCANCODE_PAUSE);
    engine->RegisterEnumValue("Scancode", "SCANCODE_INSERT", SCANCODE_INSERT);
    engine->RegisterEnumValue("Scancode", "SCANCODE_HOME", SCANCODE_HOME);
    engine->RegisterEnumValue("Scancode", "SCANCODE_PAGEUP", SCANCODE_PAGEUP);
    engine->RegisterEnumValue("Scancode", "SCANCODE_DELETE", SCANCODE_DELETE);
    engine->RegisterEnumValue("Scancode", "SCANCODE_END", SCANCODE_END);
    engine->RegisterEnumValue("Scancode", "SCANCODE_PAGEDOWN", SCANCODE_PAGEDOWN);
    engine->RegisterEnumValue("Scancode", "SCANCODE_RIGHT", SCANCODE_RIGHT);
    engine->RegisterEnumValue("Scancode", "SCANCODE_LEFT", SCANCODE_LEFT);
    engine->RegisterEnumValue("Scancode", "SCANCODE_DOWN", SCANCODE_DOWN);
    engine->RegisterEnumValue("Scancode", "SCANCODE_UP", SCANCODE_UP);
    engine->RegisterEnumValue("Scancode", "SCANCODE_NUMLOCKCLEAR", SCANCODE_NUMLOCKCLEAR);
    engine->RegisterEnumValue("Scancode", "SCANCODE_KP_DIVIDE", SCANCODE_KP_DIVIDE);
    engine->RegisterEnumValue("Scancode", "SCANCODE_KP_MULTIPLY", SCANCODE_KP_MULTIPLY);
    engine->RegisterEnumValue("Scancode", "SCANCODE_KP_MINUS", SCANCODE_KP_MINUS);
    engine->RegisterEnumValue("Scancode", "SCANCODE_KP_PLUS", SCANCODE_KP_PLUS);
    engine->RegisterEnumValue("Scancode", "SCANCODE_KP_ENTER", SCANCODE_KP_ENTER);
    engine->RegisterEnumValue("Scancode", "SCANCODE_KP_1", SCANCODE_KP_1);
    engine->RegisterEnumValue("Scancode", "SCANCODE_KP_2", SCANCODE_KP_2);
    engine->RegisterEnumValue("Scancode", "SCANCODE_KP_3", SCANCODE_KP_3);
    engine->RegisterEnumValue("Scancode", "SCANCODE_KP_4", SCANCODE_KP_4);
    engine->RegisterEnumValue("Scancode", "SCANCODE_KP_5", SCANCODE_KP_5);
    engine->RegisterEnumValue("Scancode", "SCANCODE_KP_6", SCANCODE_KP_6);
    engine->RegisterEnumValue("Scancode", "SCANCODE_KP_7", SCANCODE_KP_7);
    engine->RegisterEnumValue("Scancode", "SCANCODE_KP_8", SCANCODE_KP_8);
    engine->RegisterEnumValue("Scancode", "SCANCODE_KP_9", SCANCODE_KP_9);
    engine->RegisterEnumValue("Scancode", "SCANCODE_KP_0", SCANCODE_KP_0);
    engine->RegisterEnumValue("Scancode", "SCANCODE_KP_PERIOD", SCANCODE_KP_PERIOD);
    engine->RegisterEnumValue("Scancode", "SCANCODE_NONUSBACKSLASH", SCANCODE_NONUSBACKSLASH);
    engine->RegisterEnumValue("Scancode", "SCANCODE_APPLICATION", SCANCODE_APPLICATION);
    engine->RegisterEnumValue("Scancode", "SCANCODE_POWER", SCANCODE_POWER);
    engine->RegisterEnumValue("Scancode", "SCANCODE_KP_EQUALS", SCANCODE_KP_EQUALS);
    engine->RegisterEnumValue("Scancode", "SCANCODE_F13", SCANCODE_F13);
    engine->RegisterEnumValue("Scancode", "SCANCODE_F14", SCANCODE_F14);
    engine->RegisterEnumValue("Scancode", "SCANCODE_F15", SCANCODE_F15);
    engine->RegisterEnumValue("Scancode", "SCANCODE_F16", SCANCODE_F16);
    engine->RegisterEnumValue("Scancode", "SCANCODE_F17", SCANCODE_F17);
    engine->RegisterEnumValue("Scancode", "SCANCODE_F18", SCANCODE_F18);
    engine->RegisterEnumValue("Scancode", "SCANCODE_F19", SCANCODE_F19);
    engine->RegisterEnumValue("Scancode", "SCANCODE_F20", SCANCODE_F20);
    engine->RegisterEnumValue("Scancode", "SCANCODE_F21", SCANCODE_F21);
    engine->RegisterEnumValue("Scancode", "SCANCODE_F22", SCANCODE_F22);
    engine->RegisterEnumValue("Scancode", "SCANCODE_F23", SCANCODE_F23);
    engine->RegisterEnumValue("Scancode", "SCANCODE_F24", SCANCODE_F24);
    engine->RegisterEnumValue("Scancode", "SCANCODE_EXECUTE", SCANCODE_EXECUTE);
    engine->RegisterEnumValue("Scancode", "SCANCODE_HELP", SCANCODE_HELP);
    engine->RegisterEnumValue("Scancode", "SCANCODE_MENU", SCANCODE_MENU);
    engine->RegisterEnumValue("Scancode", "SCANCODE_SELECT", SCANCODE_SELECT);
    engine->RegisterEnumValue("Scancode", "SCANCODE_STOP", SCANCODE_STOP);
    engine->RegisterEnumValue("Scancode", "SCANCODE_AGAIN", SCANCODE_AGAIN);
    engine->RegisterEnumValue("Scancode", "SCANCODE_UNDO", SCANCODE_UNDO);
    engine->RegisterEnumValue("Scancode", "SCANCODE_CUT", SCANCODE_CUT);
    engine->RegisterEnumValue("Scancode", "SCANCODE_COPY", SCANCODE_COPY);
    engine->RegisterEnumValue("Scancode", "SCANCODE_PASTE", SCANCODE_PASTE);
    engine->RegisterEnumValue("Scancode", "SCANCODE_FIND", SCANCODE_FIND);
    engine->RegisterEnumValue("Scancode", "SCANCODE_MUTE", SCANCODE_MUTE);
    engine->RegisterEnumValue("Scancode", "SCANCODE_VOLUMEUP", SCANCODE_VOLUMEUP);
    engine->RegisterEnumValue("Scancode", "SCANCODE_VOLUMEDOWN", SCANCODE_VOLUMEDOWN);
    engine->RegisterEnumValue("Scancode", "SCANCODE_KP_COMMA", SCANCODE_KP_COMMA);
    engine->RegisterEnumValue("Scancode", "SCANCODE_KP_EQUALSAS400", SCANCODE_KP_EQUALSAS400);
    engine->RegisterEnumValue("Scancode", "SCANCODE_INTERNATIONAL1", SCANCODE_INTERNATIONAL1);
    engine->RegisterEnumValue("Scancode", "SCANCODE_INTERNATIONAL2", SCANCODE_INTERNATIONAL2);
    engine->RegisterEnumValue("Scancode", "SCANCODE_INTERNATIONAL3", SCANCODE_INTERNATIONAL3);
    engine->RegisterEnumValue("Scancode", "SCANCODE_INTERNATIONAL4", SCANCODE_INTERNATIONAL4);
    engine->RegisterEnumValue("Scancode", "SCANCODE_INTERNATIONAL5", SCANCODE_INTERNATIONAL5);
    engine->RegisterEnumValue("Scancode", "SCANCODE_INTERNATIONAL6", SCANCODE_INTERNATIONAL6);
    engine->RegisterEnumValue("Scancode", "SCANCODE_INTERNATIONAL7", SCANCODE_INTERNATIONAL7);
    engine->RegisterEnumValue("Scancode", "SCANCODE_INTERNATIONAL8", SCANCODE_INTERNATIONAL8);
    engine->RegisterEnumValue("Scancode", "SCANCODE_INTERNATIONAL9", SCANCODE_INTERNATIONAL9);
    engine->RegisterEnumValue("Scancode", "SCANCODE_LANG1", SCANCODE_LANG1);
    engine->RegisterEnumValue("Scancode", "SCANCODE_LANG2", SCANCODE_LANG2);
    engine->RegisterEnumValue("Scancode", "SCANCODE_LANG3", SCANCODE_LANG3);
    engine->RegisterEnumValue("Scancode", "SCANCODE_LANG4", SCANCODE_LANG4);
    engine->RegisterEnumValue("Scancode", "SCANCODE_LANG5", SCANCODE_LANG5);
    engine->RegisterEnumValue("Scancode", "SCANCODE_LANG6", SCANCODE_LANG6);
    engine->RegisterEnumValue("Scancode", "SCANCODE_LANG7", SCANCODE_LANG7);
    engine->RegisterEnumValue("Scancode", "SCANCODE_LANG8", SCANCODE_LANG8);
    engine->RegisterEnumValue("Scancode", "SCANCODE_LANG9", SCANCODE_LANG9);
    engine->RegisterEnumValue("Scancode", "SCANCODE_ALTERASE", SCANCODE_ALTERASE);
    engine->RegisterEnumValue("Scancode", "SCANCODE_SYSREQ", SCANCODE_SYSREQ);
    engine->RegisterEnumValue("Scancode", "SCANCODE_CANCEL", SCANCODE_CANCEL);
    engine->RegisterEnumValue("Scancode", "SCANCODE_CLEAR", SCANCODE_CLEAR);
    engine->RegisterEnumValue("Scancode", "SCANCODE_PRIOR", SCANCODE_PRIOR);
    engine->RegisterEnumValue("Scancode", "SCANCODE_RETURN2", SCANCODE_RETURN2);
    engine->RegisterEnumValue("Scancode", "SCANCODE_SEPARATOR", SCANCODE_SEPARATOR);
    engine->RegisterEnumValue("Scancode", "SCANCODE_OUT", SCANCODE_OUT);
    engine->RegisterEnumValue("Scancode", "SCANCODE_OPER", SCANCODE_OPER);
    engine->RegisterEnumValue("Scancode", "SCANCODE_CLEARAGAIN", SCANCODE_CLEARAGAIN);
    engine->RegisterEnumValue("Scancode", "SCANCODE_CRSEL", SCANCODE_CRSEL);
    engine->RegisterEnumValue("Scancode", "SCANCODE_EXSEL", SCANCODE_EXSEL);
    engine->RegisterEnumValue("Scancode", "SCANCODE_KP_00", SCANCODE_KP_00);
    engine->RegisterEnumValue("Scancode", "SCANCODE_KP_000", SCANCODE_KP_000);
    engine->RegisterEnumValue("Scancode", "SCANCODE_THOUSANDSSEPARATOR", SCANCODE_THOUSANDSSEPARATOR);
    engine->RegisterEnumValue("Scancode", "SCANCODE_DECIMALSEPARATOR", SCANCODE_DECIMALSEPARATOR);
    engine->RegisterEnumValue("Scancode", "SCANCODE_CURRENCYUNIT", SCANCODE_CURRENCYUNIT);
    engine->RegisterEnumValue("Scancode", "SCANCODE_CURRENCYSUBUNIT", SCANCODE_CURRENCYSUBUNIT);
    engine->RegisterEnumValue("Scancode", "SCANCODE_KP_LEFTPAREN", SCANCODE_KP_LEFTPAREN);
    engine->RegisterEnumValue("Scancode", "SCANCODE_KP_RIGHTPAREN", SCANCODE_KP_RIGHTPAREN);
    engine->RegisterEnumValue("Scancode", "SCANCODE_KP_LEFTBRACE", SCANCODE_KP_LEFTBRACE);
    engine->RegisterEnumValue("Scancode", "SCANCODE_KP_RIGHTBRACE", SCANCODE_KP_RIGHTBRACE);
    engine->RegisterEnumValue("Scancode", "SCANCODE_KP_TAB", SCANCODE_KP_TAB);
    engine->RegisterEnumValue("Scancode", "SCANCODE_KP_BACKSPACE", SCANCODE_KP_BACKSPACE);
    engine->RegisterEnumValue("Scancode", "SCANCODE_KP_A", SCANCODE_KP_A);
    engine->RegisterEnumValue("Scancode", "SCANCODE_KP_B", SCANCODE_KP_B);
    engine->RegisterEnumValue("Scancode", "SCANCODE_KP_C", SCANCODE_KP_C);
    engine->RegisterEnumValue("Scancode", "SCANCODE_KP_D", SCANCODE_KP_D);
    engine->RegisterEnumValue("Scancode", "SCANCODE_KP_E", SCANCODE_KP_E);
    engine->RegisterEnumValue("Scancode", "SCANCODE_KP_F", SCANCODE_KP_F);
    engine->RegisterEnumValue("Scancode", "SCANCODE_KP_XOR", SCANCODE_KP_XOR);
    engine->RegisterEnumValue("Scancode", "SCANCODE_KP_POWER", SCANCODE_KP_POWER);
    engine->RegisterEnumValue("Scancode", "SCANCODE_KP_PERCENT", SCANCODE_KP_PERCENT);
    engine->RegisterEnumValue("Scancode", "SCANCODE_KP_LESS", SCANCODE_KP_LESS);
    engine->RegisterEnumValue("Scancode", "SCANCODE_KP_GREATER", SCANCODE_KP_GREATER);
    engine->RegisterEnumValue("Scancode", "SCANCODE_KP_AMPERSAND", SCANCODE_KP_AMPERSAND);
    engine->RegisterEnumValue("Scancode", "SCANCODE_KP_DBLAMPERSAND", SCANCODE_KP_DBLAMPERSAND);
    engine->RegisterEnumValue("Scancode", "SCANCODE_KP_VERTICALBAR", SCANCODE_KP_VERTICALBAR);
    engine->RegisterEnumValue("Scancode", "SCANCODE_KP_DBLVERTICALBAR", SCANCODE_KP_DBLVERTICALBAR);
    engine->RegisterEnumValue("Scancode", "SCANCODE_KP_COLON", SCANCODE_KP_COLON);
    engine->RegisterEnumValue("Scancode", "SCANCODE_KP_HASH", SCANCODE_KP_HASH);
    engine->RegisterEnumValue("Scancode", "SCANCODE_KP_SPACE", SCANCODE_KP_SPACE);
    engine->RegisterEnumValue("Scancode", "SCANCODE_KP_AT", SCANCODE_KP_AT);
    engine->RegisterEnumValue("Scancode", "SCANCODE_KP_EXCLAM", SCANCODE_KP_EXCLAM);
    engine->RegisterEnumValue("Scancode", "SCANCODE_KP_MEMSTORE", SCANCODE_KP_MEMSTORE);
    engine->RegisterEnumValue("Scancode", "SCANCODE_KP_MEMRECALL", SCANCODE_KP_MEMRECALL);
    engine->RegisterEnumValue("Scancode", "SCANCODE_KP_MEMCLEAR", SCANCODE_KP_MEMCLEAR);
    engine->RegisterEnumValue("Scancode", "SCANCODE_KP_MEMADD", SCANCODE_KP_MEMADD);
    engine->RegisterEnumValue("Scancode", "SCANCODE_KP_MEMSUBTRACT", SCANCODE_KP_MEMSUBTRACT);
    engine->RegisterEnumValue("Scancode", "SCANCODE_KP_MEMMULTIPLY", SCANCODE_KP_MEMMULTIPLY);
    engine->RegisterEnumValue("Scancode", "SCANCODE_KP_MEMDIVIDE", SCANCODE_KP_MEMDIVIDE);
    engine->RegisterEnumValue("Scancode", "SCANCODE_KP_PLUSMINUS", SCANCODE_KP_PLUSMINUS);
    engine->RegisterEnumValue("Scancode", "SCANCODE_KP_CLEAR", SCANCODE_KP_CLEAR);
    engine->RegisterEnumValue("Scancode", "SCANCODE_KP_CLEARENTRY", SCANCODE_KP_CLEARENTRY);
    engine->RegisterEnumValue("Scancode", "SCANCODE_KP_BINARY", SCANCODE_KP_BINARY);
    engine->RegisterEnumValue("Scancode", "SCANCODE_KP_OCTAL", SCANCODE_KP_OCTAL);
    engine->RegisterEnumValue("Scancode", "SCANCODE_KP_DECIMAL", SCANCODE_KP_DECIMAL);
    engine->RegisterEnumValue("Scancode", "SCANCODE_KP_HEXADECIMAL", SCANCODE_KP_HEXADECIMAL);
    engine->RegisterEnumValue("Scancode", "SCANCODE_LCTRL", SCANCODE_LCTRL);
    engine->RegisterEnumValue("Scancode", "SCANCODE_LSHIFT", SCANCODE_LSHIFT);
    engine->RegisterEnumValue("Scancode", "SCANCODE_LALT", SCANCODE_LALT);
    engine->RegisterEnumValue("Scancode", "SCANCODE_LGUI", SCANCODE_LGUI);
    engine->RegisterEnumValue("Scancode", "SCANCODE_RCTRL", SCANCODE_RCTRL);
    engine->RegisterEnumValue("Scancode", "SCANCODE_RSHIFT", SCANCODE_RSHIFT);
    engine->RegisterEnumValue("Scancode", "SCANCODE_RALT", SCANCODE_RALT);
    engine->RegisterEnumValue("Scancode", "SCANCODE_RGUI", SCANCODE_RGUI);
    engine->RegisterEnumValue("Scancode", "SCANCODE_MODE", SCANCODE_MODE);
    engine->RegisterEnumValue("Scancode", "SCANCODE_AUDIONEXT", SCANCODE_AUDIONEXT);
    engine->RegisterEnumValue("Scancode", "SCANCODE_AUDIOPREV", SCANCODE_AUDIOPREV);
    engine->RegisterEnumValue("Scancode", "SCANCODE_AUDIOSTOP", SCANCODE_AUDIOSTOP);
    engine->RegisterEnumValue("Scancode", "SCANCODE_AUDIOPLAY", SCANCODE_AUDIOPLAY);
    engine->RegisterEnumValue("Scancode", "SCANCODE_AUDIOMUTE", SCANCODE_AUDIOMUTE);
    engine->RegisterEnumValue("Scancode", "SCANCODE_MEDIASELECT", SCANCODE_MEDIASELECT);
    engine->RegisterEnumValue("Scancode", "SCANCODE_WWW", SCANCODE_WWW);
    engine->RegisterEnumValue("Scancode", "SCANCODE_MAIL", SCANCODE_MAIL);
    engine->RegisterEnumValue("Scancode", "SCANCODE_CALCULATOR", SCANCODE_CALCULATOR);
    engine->RegisterEnumValue("Scancode", "SCANCODE_COMPUTER", SCANCODE_COMPUTER);
    engine->RegisterEnumValue("Scancode", "SCANCODE_AC_SEARCH", SCANCODE_AC_SEARCH);
    engine->RegisterEnumValue("Scancode", "SCANCODE_AC_HOME", SCANCODE_AC_HOME);
    engine->RegisterEnumValue("Scancode", "SCANCODE_AC_BACK", SCANCODE_AC_BACK);
    engine->RegisterEnumValue("Scancode", "SCANCODE_AC_FORWARD", SCANCODE_AC_FORWARD);
    engine->RegisterEnumValue("Scancode", "SCANCODE_AC_STOP", SCANCODE_AC_STOP);
    engine->RegisterEnumValue("Scancode", "SCANCODE_AC_REFRESH", SCANCODE_AC_REFRESH);
    engine->RegisterEnumValue("Scancode", "SCANCODE_AC_BOOKMARKS", SCANCODE_AC_BOOKMARKS);
    engine->RegisterEnumValue("Scancode", "SCANCODE_BRIGHTNESSDOWN", SCANCODE_BRIGHTNESSDOWN);
    engine->RegisterEnumValue("Scancode", "SCANCODE_BRIGHTNESSUP", SCANCODE_BRIGHTNESSUP);
    engine->RegisterEnumValue("Scancode", "SCANCODE_DISPLAYSWITCH", SCANCODE_DISPLAYSWITCH);
    engine->RegisterEnumValue("Scancode", "SCANCODE_KBDILLUMTOGGLE", SCANCODE_KBDILLUMTOGGLE);
    engine->RegisterEnumValue("Scancode", "SCANCODE_KBDILLUMDOWN", SCANCODE_KBDILLUMDOWN);
    engine->RegisterEnumValue("Scancode", "SCANCODE_KBDILLUMUP", SCANCODE_KBDILLUMUP);
    engine->RegisterEnumValue("Scancode", "SCANCODE_EJECT", SCANCODE_EJECT);
    engine->RegisterEnumValue("Scancode", "SCANCODE_SLEEP", SCANCODE_SLEEP);
    engine->RegisterEnumValue("Scancode", "SCANCODE_APP1", SCANCODE_APP1);
    engine->RegisterEnumValue("Scancode", "SCANCODE_APP2", SCANCODE_APP2);

    // enum HatPosition | File: ../Input/InputConstants.h | Line: 555
    engine->RegisterEnum("HatPosition");
    engine->RegisterEnumValue("HatPosition", "HAT_CENTER", HAT_CENTER);
    engine->RegisterEnumValue("HatPosition", "HAT_UP", HAT_UP);
    engine->RegisterEnumValue("HatPosition", "HAT_RIGHT", HAT_RIGHT);
    engine->RegisterEnumValue("HatPosition", "HAT_DOWN", HAT_DOWN);
    engine->RegisterEnumValue("HatPosition", "HAT_LEFT", HAT_LEFT);

    // enum ControllerButton | File: ../Input/InputConstants.h | Line: 564
    engine->RegisterEnum("ControllerButton");
    engine->RegisterEnumValue("ControllerButton", "CONTROLLER_BUTTON_A", CONTROLLER_BUTTON_A);
    engine->RegisterEnumValue("ControllerButton", "CONTROLLER_BUTTON_B", CONTROLLER_BUTTON_B);
    engine->RegisterEnumValue("ControllerButton", "CONTROLLER_BUTTON_X", CONTROLLER_BUTTON_X);
    engine->RegisterEnumValue("ControllerButton", "CONTROLLER_BUTTON_Y", CONTROLLER_BUTTON_Y);
    engine->RegisterEnumValue("ControllerButton", "CONTROLLER_BUTTON_BACK", CONTROLLER_BUTTON_BACK);
    engine->RegisterEnumValue("ControllerButton", "CONTROLLER_BUTTON_GUIDE", CONTROLLER_BUTTON_GUIDE);
    engine->RegisterEnumValue("ControllerButton", "CONTROLLER_BUTTON_START", CONTROLLER_BUTTON_START);
    engine->RegisterEnumValue("ControllerButton", "CONTROLLER_BUTTON_LEFTSTICK", CONTROLLER_BUTTON_LEFTSTICK);
    engine->RegisterEnumValue("ControllerButton", "CONTROLLER_BUTTON_RIGHTSTICK", CONTROLLER_BUTTON_RIGHTSTICK);
    engine->RegisterEnumValue("ControllerButton", "CONTROLLER_BUTTON_LEFTSHOULDER", CONTROLLER_BUTTON_LEFTSHOULDER);
    engine->RegisterEnumValue("ControllerButton", "CONTROLLER_BUTTON_RIGHTSHOULDER", CONTROLLER_BUTTON_RIGHTSHOULDER);
    engine->RegisterEnumValue("ControllerButton", "CONTROLLER_BUTTON_DPAD_UP", CONTROLLER_BUTTON_DPAD_UP);
    engine->RegisterEnumValue("ControllerButton", "CONTROLLER_BUTTON_DPAD_DOWN", CONTROLLER_BUTTON_DPAD_DOWN);
    engine->RegisterEnumValue("ControllerButton", "CONTROLLER_BUTTON_DPAD_LEFT", CONTROLLER_BUTTON_DPAD_LEFT);
    engine->RegisterEnumValue("ControllerButton", "CONTROLLER_BUTTON_DPAD_RIGHT", CONTROLLER_BUTTON_DPAD_RIGHT);

    // enum ControllerAxis | File: ../Input/InputConstants.h | Line: 583
    engine->RegisterEnum("ControllerAxis");
    engine->RegisterEnumValue("ControllerAxis", "CONTROLLER_AXIS_LEFTX", CONTROLLER_AXIS_LEFTX);
    engine->RegisterEnumValue("ControllerAxis", "CONTROLLER_AXIS_LEFTY", CONTROLLER_AXIS_LEFTY);
    engine->RegisterEnumValue("ControllerAxis", "CONTROLLER_AXIS_RIGHTX", CONTROLLER_AXIS_RIGHTX);
    engine->RegisterEnumValue("ControllerAxis", "CONTROLLER_AXIS_RIGHTY", CONTROLLER_AXIS_RIGHTY);
    engine->RegisterEnumValue("ControllerAxis", "CONTROLLER_AXIS_TRIGGERLEFT", CONTROLLER_AXIS_TRIGGERLEFT);
    engine->RegisterEnumValue("ControllerAxis", "CONTROLLER_AXIS_TRIGGERRIGHT", CONTROLLER_AXIS_TRIGGERRIGHT);

    // enum FileMode | File: ../IO/File.h | Line: 53
    engine->RegisterEnum("FileMode");
    engine->RegisterEnumValue("FileMode", "FILE_READ", FILE_READ);
    engine->RegisterEnumValue("FileMode", "FILE_WRITE", FILE_WRITE);
    engine->RegisterEnumValue("FileMode", "FILE_READWRITE", FILE_READWRITE);

    // enum FrustumPlane | File: ../Math/Frustum.h | Line: 38
    engine->RegisterEnum("FrustumPlane");
    engine->RegisterEnumValue("FrustumPlane", "PLANE_NEAR", PLANE_NEAR);
    engine->RegisterEnumValue("FrustumPlane", "PLANE_LEFT", PLANE_LEFT);
    engine->RegisterEnumValue("FrustumPlane", "PLANE_RIGHT", PLANE_RIGHT);
    engine->RegisterEnumValue("FrustumPlane", "PLANE_UP", PLANE_UP);
    engine->RegisterEnumValue("FrustumPlane", "PLANE_DOWN", PLANE_DOWN);
    engine->RegisterEnumValue("FrustumPlane", "PLANE_FAR", PLANE_FAR);

    // enum Intersection | File: ../Math/MathDefs.h | Line: 63
    engine->RegisterEnum("Intersection");
    engine->RegisterEnumValue("Intersection", "OUTSIDE", OUTSIDE);
    engine->RegisterEnumValue("Intersection", "INTERSECTS", INTERSECTS);
    engine->RegisterEnumValue("Intersection", "INSIDE", INSIDE);

#ifdef URHO3D_NAVIGATION
    // enum CrowdAgentRequestedTarget | File: ../Navigation/CrowdAgent.h | Line: 34
    engine->RegisterEnum("CrowdAgentRequestedTarget");
    engine->RegisterEnumValue("CrowdAgentRequestedTarget", "CA_REQUESTEDTARGET_NONE", CA_REQUESTEDTARGET_NONE);
    engine->RegisterEnumValue("CrowdAgentRequestedTarget", "CA_REQUESTEDTARGET_POSITION", CA_REQUESTEDTARGET_POSITION);
    engine->RegisterEnumValue("CrowdAgentRequestedTarget", "CA_REQUESTEDTARGET_VELOCITY", CA_REQUESTEDTARGET_VELOCITY);
#endif

#ifdef URHO3D_NAVIGATION
    // enum CrowdAgentTargetState | File: ../Navigation/CrowdAgent.h | Line: 41
    engine->RegisterEnum("CrowdAgentTargetState");
    engine->RegisterEnumValue("CrowdAgentTargetState", "CA_TARGET_NONE", CA_TARGET_NONE);
    engine->RegisterEnumValue("CrowdAgentTargetState", "CA_TARGET_FAILED", CA_TARGET_FAILED);
    engine->RegisterEnumValue("CrowdAgentTargetState", "CA_TARGET_VALID", CA_TARGET_VALID);
    engine->RegisterEnumValue("CrowdAgentTargetState", "CA_TARGET_REQUESTING", CA_TARGET_REQUESTING);
    engine->RegisterEnumValue("CrowdAgentTargetState", "CA_TARGET_WAITINGFORQUEUE", CA_TARGET_WAITINGFORQUEUE);
    engine->RegisterEnumValue("CrowdAgentTargetState", "CA_TARGET_WAITINGFORPATH", CA_TARGET_WAITINGFORPATH);
    engine->RegisterEnumValue("CrowdAgentTargetState", "CA_TARGET_VELOCITY", CA_TARGET_VELOCITY);
#endif

#ifdef URHO3D_NAVIGATION
    // enum CrowdAgentState | File: ../Navigation/CrowdAgent.h | Line: 52
    engine->RegisterEnum("CrowdAgentState");
    engine->RegisterEnumValue("CrowdAgentState", "CA_STATE_INVALID", CA_STATE_INVALID);
    engine->RegisterEnumValue("CrowdAgentState", "CA_STATE_WALKING", CA_STATE_WALKING);
    engine->RegisterEnumValue("CrowdAgentState", "CA_STATE_OFFMESH", CA_STATE_OFFMESH);
#endif

#ifdef URHO3D_NAVIGATION
    // enum NavigationQuality | File: ../Navigation/CrowdAgent.h | Line: 59
    engine->RegisterEnum("NavigationQuality");
    engine->RegisterEnumValue("NavigationQuality", "NAVIGATIONQUALITY_LOW", NAVIGATIONQUALITY_LOW);
    engine->RegisterEnumValue("NavigationQuality", "NAVIGATIONQUALITY_MEDIUM", NAVIGATIONQUALITY_MEDIUM);
    engine->RegisterEnumValue("NavigationQuality", "NAVIGATIONQUALITY_HIGH", NAVIGATIONQUALITY_HIGH);
#endif

#ifdef URHO3D_NAVIGATION
    // enum NavigationPushiness | File: ../Navigation/CrowdAgent.h | Line: 66
    engine->RegisterEnum("NavigationPushiness");
    engine->RegisterEnumValue("NavigationPushiness", "NAVIGATIONPUSHINESS_LOW", NAVIGATIONPUSHINESS_LOW);
    engine->RegisterEnumValue("NavigationPushiness", "NAVIGATIONPUSHINESS_MEDIUM", NAVIGATIONPUSHINESS_MEDIUM);
    engine->RegisterEnumValue("NavigationPushiness", "NAVIGATIONPUSHINESS_HIGH", NAVIGATIONPUSHINESS_HIGH);
    engine->RegisterEnumValue("NavigationPushiness", "NAVIGATIONPUSHINESS_NONE", NAVIGATIONPUSHINESS_NONE);
#endif

#ifdef URHO3D_NAVIGATION
    // enum NavmeshPartitionType | File: ../Navigation/NavigationMesh.h | Line: 47
    engine->RegisterEnum("NavmeshPartitionType");
    engine->RegisterEnumValue("NavmeshPartitionType", "NAVMESH_PARTITION_WATERSHED", NAVMESH_PARTITION_WATERSHED);
    engine->RegisterEnumValue("NavmeshPartitionType", "NAVMESH_PARTITION_MONOTONE", NAVMESH_PARTITION_MONOTONE);
#endif

#ifdef URHO3D_NAVIGATION
    // enum NavigationPathPointFlag | File: ../Navigation/NavigationMesh.h | Line: 74
    engine->RegisterEnum("NavigationPathPointFlag");
    engine->RegisterEnumValue("NavigationPathPointFlag", "NAVPATHFLAG_NONE", NAVPATHFLAG_NONE);
    engine->RegisterEnumValue("NavigationPathPointFlag", "NAVPATHFLAG_START", NAVPATHFLAG_START);
    engine->RegisterEnumValue("NavigationPathPointFlag", "NAVPATHFLAG_END", NAVPATHFLAG_END);
    engine->RegisterEnumValue("NavigationPathPointFlag", "NAVPATHFLAG_OFF_MESH", NAVPATHFLAG_OFF_MESH);
#endif

#ifdef URHO3D_NETWORK
    // enum ObserverPositionSendMode | File: ../Network/Connection.h | Line: 103
    engine->RegisterEnum("ObserverPositionSendMode");
    engine->RegisterEnumValue("ObserverPositionSendMode", "OPSM_NONE", OPSM_NONE);
    engine->RegisterEnumValue("ObserverPositionSendMode", "OPSM_POSITION", OPSM_POSITION);
    engine->RegisterEnumValue("ObserverPositionSendMode", "OPSM_POSITION_ROTATION", OPSM_POSITION_ROTATION);
#endif

#ifdef URHO3D_NETWORK
    // enum HttpRequestState | File: ../Network/HttpRequest.h | Line: 38
    engine->RegisterEnum("HttpRequestState");
    engine->RegisterEnumValue("HttpRequestState", "HTTP_INITIALIZING", HTTP_INITIALIZING);
    engine->RegisterEnumValue("HttpRequestState", "HTTP_ERROR", HTTP_ERROR);
    engine->RegisterEnumValue("HttpRequestState", "HTTP_OPEN", HTTP_OPEN);
    engine->RegisterEnumValue("HttpRequestState", "HTTP_CLOSED", HTTP_CLOSED);
#endif

#ifdef URHO3D_PHYSICS
    // enum ShapeType | File: ../Physics/CollisionShape.h | Line: 53
    engine->RegisterEnum("ShapeType");
    engine->RegisterEnumValue("ShapeType", "SHAPE_BOX", SHAPE_BOX);
    engine->RegisterEnumValue("ShapeType", "SHAPE_SPHERE", SHAPE_SPHERE);
    engine->RegisterEnumValue("ShapeType", "SHAPE_STATICPLANE", SHAPE_STATICPLANE);
    engine->RegisterEnumValue("ShapeType", "SHAPE_CYLINDER", SHAPE_CYLINDER);
    engine->RegisterEnumValue("ShapeType", "SHAPE_CAPSULE", SHAPE_CAPSULE);
    engine->RegisterEnumValue("ShapeType", "SHAPE_CONE", SHAPE_CONE);
    engine->RegisterEnumValue("ShapeType", "SHAPE_TRIANGLEMESH", SHAPE_TRIANGLEMESH);
    engine->RegisterEnumValue("ShapeType", "SHAPE_CONVEXHULL", SHAPE_CONVEXHULL);
    engine->RegisterEnumValue("ShapeType", "SHAPE_TERRAIN", SHAPE_TERRAIN);
    engine->RegisterEnumValue("ShapeType", "SHAPE_GIMPACTMESH", SHAPE_GIMPACTMESH);
#endif

#ifdef URHO3D_PHYSICS
    // enum ConstraintType | File: ../Physics/Constraint.h | Line: 37
    engine->RegisterEnum("ConstraintType");
    engine->RegisterEnumValue("ConstraintType", "CONSTRAINT_POINT", CONSTRAINT_POINT);
    engine->RegisterEnumValue("ConstraintType", "CONSTRAINT_HINGE", CONSTRAINT_HINGE);
    engine->RegisterEnumValue("ConstraintType", "CONSTRAINT_SLIDER", CONSTRAINT_SLIDER);
    engine->RegisterEnumValue("ConstraintType", "CONSTRAINT_CONETWIST", CONSTRAINT_CONETWIST);
#endif

#ifdef URHO3D_PHYSICS
    // enum CollisionEventMode | File: ../Physics/RigidBody.h | Line: 45
    engine->RegisterEnum("CollisionEventMode");
    engine->RegisterEnumValue("CollisionEventMode", "COLLISION_NEVER", COLLISION_NEVER);
    engine->RegisterEnumValue("CollisionEventMode", "COLLISION_ACTIVE", COLLISION_ACTIVE);
    engine->RegisterEnumValue("CollisionEventMode", "COLLISION_ALWAYS", COLLISION_ALWAYS);
#endif

    // enum CompressedFormat | File: ../Resource/Image.h | Line: 39
    engine->RegisterEnum("CompressedFormat");
    engine->RegisterEnumValue("CompressedFormat", "CF_NONE", CF_NONE);
    engine->RegisterEnumValue("CompressedFormat", "CF_RGBA", CF_RGBA);
    engine->RegisterEnumValue("CompressedFormat", "CF_DXT1", CF_DXT1);
    engine->RegisterEnumValue("CompressedFormat", "CF_DXT3", CF_DXT3);
    engine->RegisterEnumValue("CompressedFormat", "CF_DXT5", CF_DXT5);
    engine->RegisterEnumValue("CompressedFormat", "CF_ETC1", CF_ETC1);
    engine->RegisterEnumValue("CompressedFormat", "CF_ETC2_RGB", CF_ETC2_RGB);
    engine->RegisterEnumValue("CompressedFormat", "CF_ETC2_RGBA", CF_ETC2_RGBA);
    engine->RegisterEnumValue("CompressedFormat", "CF_PVRTC_RGB_2BPP", CF_PVRTC_RGB_2BPP);
    engine->RegisterEnumValue("CompressedFormat", "CF_PVRTC_RGBA_2BPP", CF_PVRTC_RGBA_2BPP);
    engine->RegisterEnumValue("CompressedFormat", "CF_PVRTC_RGB_4BPP", CF_PVRTC_RGB_4BPP);
    engine->RegisterEnumValue("CompressedFormat", "CF_PVRTC_RGBA_4BPP", CF_PVRTC_RGBA_4BPP);

    // enum JSONValueType | File: ../Resource/JSONValue.h | Line: 34
    engine->RegisterEnum("JSONValueType");
    engine->RegisterEnumValue("JSONValueType", "JSON_NULL", JSON_NULL);
    engine->RegisterEnumValue("JSONValueType", "JSON_BOOL", JSON_BOOL);
    engine->RegisterEnumValue("JSONValueType", "JSON_NUMBER", JSON_NUMBER);
    engine->RegisterEnumValue("JSONValueType", "JSON_STRING", JSON_STRING);
    engine->RegisterEnumValue("JSONValueType", "JSON_ARRAY", JSON_ARRAY);
    engine->RegisterEnumValue("JSONValueType", "JSON_OBJECT", JSON_OBJECT);

    // enum JSONNumberType | File: ../Resource/JSONValue.h | Line: 51
    engine->RegisterEnum("JSONNumberType");
    engine->RegisterEnumValue("JSONNumberType", "JSONNT_NAN", JSONNT_NAN);
    engine->RegisterEnumValue("JSONNumberType", "JSONNT_INT", JSONNT_INT);
    engine->RegisterEnumValue("JSONNumberType", "JSONNT_UINT", JSONNT_UINT);
    engine->RegisterEnumValue("JSONNumberType", "JSONNT_FLOAT_DOUBLE", JSONNT_FLOAT_DOUBLE);

    // enum WrapMode | File: ../Scene/AnimationDefs.h | Line: 32
    engine->RegisterEnum("WrapMode");
    engine->RegisterEnumValue("WrapMode", "WM_LOOP", WM_LOOP);
    engine->RegisterEnumValue("WrapMode", "WM_ONCE", WM_ONCE);
    engine->RegisterEnumValue("WrapMode", "WM_CLAMP", WM_CLAMP);

    // enum AutoRemoveMode | File: ../Scene/Component.h | Line: 40
    engine->RegisterEnum("AutoRemoveMode");
    engine->RegisterEnumValue("AutoRemoveMode", "REMOVE_DISABLED", REMOVE_DISABLED);
    engine->RegisterEnumValue("AutoRemoveMode", "REMOVE_COMPONENT", REMOVE_COMPONENT);
    engine->RegisterEnumValue("AutoRemoveMode", "REMOVE_NODE", REMOVE_NODE);

    // enum CreateMode | File: ../Scene/Node.h | Line: 44
    engine->RegisterEnum("CreateMode");
    engine->RegisterEnumValue("CreateMode", "REPLICATED", REPLICATED);
    engine->RegisterEnumValue("CreateMode", "LOCAL", LOCAL);

    // enum TransformSpace | File: ../Scene/Node.h | Line: 51
    engine->RegisterEnum("TransformSpace");
    engine->RegisterEnumValue("TransformSpace", "TS_LOCAL", TS_LOCAL);
    engine->RegisterEnumValue("TransformSpace", "TS_PARENT", TS_PARENT);
    engine->RegisterEnumValue("TransformSpace", "TS_WORLD", TS_WORLD);

    // enum LoadMode | File: ../Scene/Scene.h | Line: 47
    engine->RegisterEnum("LoadMode");
    engine->RegisterEnumValue("LoadMode", "LOAD_RESOURCES_ONLY", LOAD_RESOURCES_ONLY);
    engine->RegisterEnumValue("LoadMode", "LOAD_SCENE", LOAD_SCENE);
    engine->RegisterEnumValue("LoadMode", "LOAD_SCENE_AND_RESOURCES", LOAD_SCENE_AND_RESOURCES);

    // enum SmoothingType | File: ../Scene/SmoothedTransform.h | Line: 33
    engine->RegisterEnum("SmoothingType");
    engine->RegisterEnumValue("SmoothingType", "SMOOTH_NONE", SMOOTH_NONE);
    engine->RegisterEnumValue("SmoothingType", "SMOOTH_POSITION", SMOOTH_POSITION);
    engine->RegisterEnumValue("SmoothingType", "SMOOTH_ROTATION", SMOOTH_ROTATION);

    // enum InterpMethod | File: ../Scene/ValueAnimation.h | Line: 38
    engine->RegisterEnum("InterpMethod");
    engine->RegisterEnumValue("InterpMethod", "IM_NONE", IM_NONE);
    engine->RegisterEnumValue("InterpMethod", "IM_LINEAR", IM_LINEAR);
    engine->RegisterEnumValue("InterpMethod", "IM_SPLINE", IM_SPLINE);

    // enum CursorShape | File: ../UI/Cursor.h | Line: 38
    engine->RegisterEnum("CursorShape");
    engine->RegisterEnumValue("CursorShape", "CS_NORMAL", CS_NORMAL);
    engine->RegisterEnumValue("CursorShape", "CS_IBEAM", CS_IBEAM);
    engine->RegisterEnumValue("CursorShape", "CS_CROSS", CS_CROSS);
    engine->RegisterEnumValue("CursorShape", "CS_RESIZEVERTICAL", CS_RESIZEVERTICAL);
    engine->RegisterEnumValue("CursorShape", "CS_RESIZEDIAGONAL_TOPRIGHT", CS_RESIZEDIAGONAL_TOPRIGHT);
    engine->RegisterEnumValue("CursorShape", "CS_RESIZEHORIZONTAL", CS_RESIZEHORIZONTAL);
    engine->RegisterEnumValue("CursorShape", "CS_RESIZEDIAGONAL_TOPLEFT", CS_RESIZEDIAGONAL_TOPLEFT);
    engine->RegisterEnumValue("CursorShape", "CS_RESIZE_ALL", CS_RESIZE_ALL);
    engine->RegisterEnumValue("CursorShape", "CS_ACCEPTDROP", CS_ACCEPTDROP);
    engine->RegisterEnumValue("CursorShape", "CS_REJECTDROP", CS_REJECTDROP);
    engine->RegisterEnumValue("CursorShape", "CS_BUSY", CS_BUSY);
    engine->RegisterEnumValue("CursorShape", "CS_BUSY_ARROW", CS_BUSY_ARROW);
    engine->RegisterEnumValue("CursorShape", "CS_MAX_SHAPES", CS_MAX_SHAPES);

    // enum FontType | File: ../UI/Font.h | Line: 40
    engine->RegisterEnum("FontType");
    engine->RegisterEnumValue("FontType", "FONT_NONE", FONT_NONE);
    engine->RegisterEnumValue("FontType", "FONT_FREETYPE", FONT_FREETYPE);
    engine->RegisterEnumValue("FontType", "FONT_BITMAP", FONT_BITMAP);
    engine->RegisterEnumValue("FontType", "MAX_FONT_TYPES", MAX_FONT_TYPES);

    // enum HighlightMode | File: ../UI/ListView.h | Line: 35
    engine->RegisterEnum("HighlightMode");
    engine->RegisterEnumValue("HighlightMode", "HM_NEVER", HM_NEVER);
    engine->RegisterEnumValue("HighlightMode", "HM_FOCUS", HM_FOCUS);
    engine->RegisterEnumValue("HighlightMode", "HM_ALWAYS", HM_ALWAYS);

    // enum TextEffect | File: ../UI/Text.h | Line: 40
    engine->RegisterEnum("TextEffect");
    engine->RegisterEnumValue("TextEffect", "TE_NONE", TE_NONE);
    engine->RegisterEnumValue("TextEffect", "TE_SHADOW", TE_SHADOW);
    engine->RegisterEnumValue("TextEffect", "TE_STROKE", TE_STROKE);

    // enum FontHintLevel | File: ../UI/UI.h | Line: 37
    engine->RegisterEnum("FontHintLevel");
    engine->RegisterEnumValue("FontHintLevel", "FONT_HINT_LEVEL_NONE", FONT_HINT_LEVEL_NONE);
    engine->RegisterEnumValue("FontHintLevel", "FONT_HINT_LEVEL_LIGHT", FONT_HINT_LEVEL_LIGHT);
    engine->RegisterEnumValue("FontHintLevel", "FONT_HINT_LEVEL_NORMAL", FONT_HINT_LEVEL_NORMAL);

    // enum HorizontalAlignment | File: ../UI/UIElement.h | Line: 38
    engine->RegisterEnum("HorizontalAlignment");
    engine->RegisterEnumValue("HorizontalAlignment", "HA_LEFT", HA_LEFT);
    engine->RegisterEnumValue("HorizontalAlignment", "HA_CENTER", HA_CENTER);
    engine->RegisterEnumValue("HorizontalAlignment", "HA_RIGHT", HA_RIGHT);
    engine->RegisterEnumValue("HorizontalAlignment", "HA_CUSTOM", HA_CUSTOM);

    // enum VerticalAlignment | File: ../UI/UIElement.h | Line: 47
    engine->RegisterEnum("VerticalAlignment");
    engine->RegisterEnumValue("VerticalAlignment", "VA_TOP", VA_TOP);
    engine->RegisterEnumValue("VerticalAlignment", "VA_CENTER", VA_CENTER);
    engine->RegisterEnumValue("VerticalAlignment", "VA_BOTTOM", VA_BOTTOM);
    engine->RegisterEnumValue("VerticalAlignment", "VA_CUSTOM", VA_CUSTOM);

    // enum Corner | File: ../UI/UIElement.h | Line: 56
    engine->RegisterEnum("Corner");
    engine->RegisterEnumValue("Corner", "C_TOPLEFT", C_TOPLEFT);
    engine->RegisterEnumValue("Corner", "C_TOPRIGHT", C_TOPRIGHT);
    engine->RegisterEnumValue("Corner", "C_BOTTOMLEFT", C_BOTTOMLEFT);
    engine->RegisterEnumValue("Corner", "C_BOTTOMRIGHT", C_BOTTOMRIGHT);
    engine->RegisterEnumValue("Corner", "MAX_UIELEMENT_CORNERS", MAX_UIELEMENT_CORNERS);

    // enum Orientation | File: ../UI/UIElement.h | Line: 66
    engine->RegisterEnum("Orientation");
    engine->RegisterEnumValue("Orientation", "O_HORIZONTAL", O_HORIZONTAL);
    engine->RegisterEnumValue("Orientation", "O_VERTICAL", O_VERTICAL);

    // enum FocusMode | File: ../UI/UIElement.h | Line: 73
    engine->RegisterEnum("FocusMode");
    engine->RegisterEnumValue("FocusMode", "FM_NOTFOCUSABLE", FM_NOTFOCUSABLE);
    engine->RegisterEnumValue("FocusMode", "FM_RESETFOCUS", FM_RESETFOCUS);
    engine->RegisterEnumValue("FocusMode", "FM_FOCUSABLE", FM_FOCUSABLE);
    engine->RegisterEnumValue("FocusMode", "FM_FOCUSABLE_DEFOCUSABLE", FM_FOCUSABLE_DEFOCUSABLE);

    // enum LayoutMode | File: ../UI/UIElement.h | Line: 86
    engine->RegisterEnum("LayoutMode");
    engine->RegisterEnumValue("LayoutMode", "LM_FREE", LM_FREE);
    engine->RegisterEnumValue("LayoutMode", "LM_HORIZONTAL", LM_HORIZONTAL);
    engine->RegisterEnumValue("LayoutMode", "LM_VERTICAL", LM_VERTICAL);

    // enum TraversalMode | File: ../UI/UIElement.h | Line: 97
    engine->RegisterEnum("TraversalMode");
    engine->RegisterEnumValue("TraversalMode", "TM_BREADTH_FIRST", TM_BREADTH_FIRST);
    engine->RegisterEnumValue("TraversalMode", "TM_DEPTH_FIRST", TM_DEPTH_FIRST);

    // enum DragAndDropMode | File: ../UI/UIElement.h | Line: 105
    engine->RegisterEnum("DragAndDropMode");
    engine->RegisterEnumValue("DragAndDropMode", "DD_DISABLED", DD_DISABLED);
    engine->RegisterEnumValue("DragAndDropMode", "DD_SOURCE", DD_SOURCE);
    engine->RegisterEnumValue("DragAndDropMode", "DD_TARGET", DD_TARGET);
    engine->RegisterEnumValue("DragAndDropMode", "DD_SOURCE_AND_TARGET", DD_SOURCE_AND_TARGET);

    // enum WindowDragMode | File: ../UI/Window.h | Line: 34
    engine->RegisterEnum("WindowDragMode");
    engine->RegisterEnumValue("WindowDragMode", "DRAG_NONE", DRAG_NONE);
    engine->RegisterEnumValue("WindowDragMode", "DRAG_MOVE", DRAG_MOVE);
    engine->RegisterEnumValue("WindowDragMode", "DRAG_RESIZE_TOPLEFT", DRAG_RESIZE_TOPLEFT);
    engine->RegisterEnumValue("WindowDragMode", "DRAG_RESIZE_TOP", DRAG_RESIZE_TOP);
    engine->RegisterEnumValue("WindowDragMode", "DRAG_RESIZE_TOPRIGHT", DRAG_RESIZE_TOPRIGHT);
    engine->RegisterEnumValue("WindowDragMode", "DRAG_RESIZE_RIGHT", DRAG_RESIZE_RIGHT);
    engine->RegisterEnumValue("WindowDragMode", "DRAG_RESIZE_BOTTOMRIGHT", DRAG_RESIZE_BOTTOMRIGHT);
    engine->RegisterEnumValue("WindowDragMode", "DRAG_RESIZE_BOTTOM", DRAG_RESIZE_BOTTOM);
    engine->RegisterEnumValue("WindowDragMode", "DRAG_RESIZE_BOTTOMLEFT", DRAG_RESIZE_BOTTOMLEFT);
    engine->RegisterEnumValue("WindowDragMode", "DRAG_RESIZE_LEFT", DRAG_RESIZE_LEFT);

#ifdef URHO3D_URHO2D
    // enum LoopMode2D | File: ../Urho2D/AnimatedSprite2D.h | Line: 40
    engine->RegisterEnum("LoopMode2D");
    engine->RegisterEnumValue("LoopMode2D", "LM_DEFAULT", LM_DEFAULT);
    engine->RegisterEnumValue("LoopMode2D", "LM_FORCE_LOOPED", LM_FORCE_LOOPED);
    engine->RegisterEnumValue("LoopMode2D", "LM_FORCE_CLAMPED", LM_FORCE_CLAMPED);
#endif

#ifdef URHO3D_URHO2D
    // enum EmitterType2D | File: ../Urho2D/ParticleEffect2D.h | Line: 38
    engine->RegisterEnum("EmitterType2D");
    engine->RegisterEnumValue("EmitterType2D", "EMITTER_TYPE_GRAVITY", EMITTER_TYPE_GRAVITY);
    engine->RegisterEnumValue("EmitterType2D", "EMITTER_TYPE_RADIAL", EMITTER_TYPE_RADIAL);
#endif

#ifdef URHO3D_URHO2D
    // enum BodyType2D | File: ../Urho2D/RigidBody2D.h | Line: 40
    engine->RegisterEnum("BodyType2D");
    engine->RegisterEnumValue("BodyType2D", "BT_STATIC", BT_STATIC);
    engine->RegisterEnumValue("BodyType2D", "BT_KINEMATIC", BT_KINEMATIC);
    engine->RegisterEnumValue("BodyType2D", "BT_DYNAMIC", BT_DYNAMIC);
#endif

#ifdef URHO3D_URHO2D
    // enum Orientation2D | File: ../Urho2D/TileMapDefs2D.h | Line: 37
    engine->RegisterEnum("Orientation2D");
    engine->RegisterEnumValue("Orientation2D", "O_ORTHOGONAL", O_ORTHOGONAL);
    engine->RegisterEnumValue("Orientation2D", "O_ISOMETRIC", O_ISOMETRIC);
    engine->RegisterEnumValue("Orientation2D", "O_STAGGERED", O_STAGGERED);
    engine->RegisterEnumValue("Orientation2D", "O_HEXAGONAL", O_HEXAGONAL);
#endif

#ifdef URHO3D_URHO2D
    // enum TileMapLayerType2D | File: ../Urho2D/TileMapDefs2D.h | Line: 77
    engine->RegisterEnum("TileMapLayerType2D");
    engine->RegisterEnumValue("TileMapLayerType2D", "LT_TILE_LAYER", LT_TILE_LAYER);
    engine->RegisterEnumValue("TileMapLayerType2D", "LT_OBJECT_GROUP", LT_OBJECT_GROUP);
    engine->RegisterEnumValue("TileMapLayerType2D", "LT_IMAGE_LAYER", LT_IMAGE_LAYER);
    engine->RegisterEnumValue("TileMapLayerType2D", "LT_INVALID", LT_INVALID);
#endif

#ifdef URHO3D_URHO2D
    // enum TileMapObjectType2D | File: ../Urho2D/TileMapDefs2D.h | Line: 90
    engine->RegisterEnum("TileMapObjectType2D");
    engine->RegisterEnumValue("TileMapObjectType2D", "OT_RECTANGLE", OT_RECTANGLE);
    engine->RegisterEnumValue("TileMapObjectType2D", "OT_ELLIPSE", OT_ELLIPSE);
    engine->RegisterEnumValue("TileMapObjectType2D", "OT_POLYGON", OT_POLYGON);
    engine->RegisterEnumValue("TileMapObjectType2D", "OT_POLYLINE", OT_POLYLINE);
    engine->RegisterEnumValue("TileMapObjectType2D", "OT_TILE", OT_TILE);
    engine->RegisterEnumValue("TileMapObjectType2D", "OT_INVALID", OT_INVALID);
#endif

    // Classes and structs
    // class IntRect | File: ../Math/Rect.h | Line: 283
    engine->RegisterObjectType("IntRect", sizeof(IntRect), asOBJ_VALUE | asGetTypeTraits<IntRect>() | asOBJ_POD | asOBJ_APP_CLASS_ALLINTS);
    // class IntVector2 | File: ../Math/Vector2.h | Line: 33
    engine->RegisterObjectType("IntVector2", sizeof(IntVector2), asOBJ_VALUE | asGetTypeTraits<IntVector2>() | asOBJ_POD | asOBJ_APP_CLASS_ALLINTS);
    // class IntVector3 | File: ../Math/Vector3.h | Line: 33
    engine->RegisterObjectType("IntVector3", sizeof(IntVector3), asOBJ_VALUE | asGetTypeTraits<IntVector3>() | asOBJ_POD | asOBJ_APP_CLASS_ALLINTS);
    // class BoundingBox | File: ../Math/BoundingBox.h | Line: 45
    engine->RegisterObjectType("BoundingBox", sizeof(BoundingBox), asOBJ_VALUE | asGetTypeTraits<BoundingBox>() | asOBJ_POD | asOBJ_APP_CLASS_ALLFLOATS);
    // class Color | File: ../Math/Color.h | Line: 34
    engine->RegisterObjectType("Color", sizeof(Color), asOBJ_VALUE | asGetTypeTraits<Color>() | asOBJ_POD | asOBJ_APP_CLASS_ALLFLOATS);
    // class Frustum | File: ../Math/Frustum.h | Line: 52
    engine->RegisterObjectType("Frustum", sizeof(Frustum), asOBJ_VALUE | asGetTypeTraits<Frustum>());
    // class Vector2 | File: ../Math/Vector2.h | Line: 179
    engine->RegisterObjectType("Vector2", sizeof(Vector2), asOBJ_VALUE | asGetTypeTraits<Vector2>() | asOBJ_POD | asOBJ_APP_CLASS_ALLFLOATS);
    // class Matrix2 | File: ../Math/Matrix2.h | Line: 32
    engine->RegisterObjectType("Matrix2", sizeof(Matrix2), asOBJ_VALUE | asGetTypeTraits<Matrix2>() | asOBJ_POD | asOBJ_APP_CLASS_ALLFLOATS);
    // class Matrix3 | File: ../Math/Matrix3.h | Line: 32
    engine->RegisterObjectType("Matrix3", sizeof(Matrix3), asOBJ_VALUE | asGetTypeTraits<Matrix3>() | asOBJ_POD | asOBJ_APP_CLASS_ALLFLOATS);
    // class Matrix3x4 | File: ../Math/Matrix3x4.h | Line: 36
    engine->RegisterObjectType("Matrix3x4", sizeof(Matrix3x4), asOBJ_VALUE | asGetTypeTraits<Matrix3x4>() | asOBJ_POD | asOBJ_APP_CLASS_ALLFLOATS);
    // class Matrix4 | File: ../Math/Matrix4.h | Line: 39
    engine->RegisterObjectType("Matrix4", sizeof(Matrix4), asOBJ_VALUE | asGetTypeTraits<Matrix4>() | asOBJ_POD | asOBJ_APP_CLASS_ALLFLOATS);
    // class Vector4 | File: ../Math/Vector4.h | Line: 32
    engine->RegisterObjectType("Vector4", sizeof(Vector4), asOBJ_VALUE | asGetTypeTraits<Vector4>() | asOBJ_POD | asOBJ_APP_CLASS_ALLFLOATS);
    // class Plane | File: ../Math/Plane.h | Line: 33
    engine->RegisterObjectType("Plane", sizeof(Plane), asOBJ_VALUE | asGetTypeTraits<Plane>() | asOBJ_POD | asOBJ_APP_CLASS_ALLFLOATS);
    // class Polyhedron | File: ../Math/Polyhedron.h | Line: 38
    engine->RegisterObjectType("Polyhedron", sizeof(Polyhedron), asOBJ_VALUE | asGetTypeTraits<Polyhedron>());
    // class Quaternion | File: ../Math/Quaternion.h | Line: 36
    engine->RegisterObjectType("Quaternion", sizeof(Quaternion), asOBJ_VALUE | asGetTypeTraits<Quaternion>() | asOBJ_POD | asOBJ_APP_CLASS_ALLFLOATS);
    // class Ray | File: ../Math/Ray.h | Line: 39
    engine->RegisterObjectType("Ray", sizeof(Ray), asOBJ_VALUE | asGetTypeTraits<Ray>() | asOBJ_POD | asOBJ_APP_CLASS_ALLFLOATS);
    // class Rect | File: ../Math/Rect.h | Line: 33
    engine->RegisterObjectType("Rect", sizeof(Rect), asOBJ_VALUE | asGetTypeTraits<Rect>() | asOBJ_POD | asOBJ_APP_CLASS_ALLFLOATS);
    // class Sphere | File: ../Math/Sphere.h | Line: 37
    engine->RegisterObjectType("Sphere", sizeof(Sphere), asOBJ_VALUE | asGetTypeTraits<Sphere>() | asOBJ_POD | asOBJ_APP_CLASS_ALLFLOATS);
    // class Vector3 | File: ../Math/Vector3.h | Line: 187
    engine->RegisterObjectType("Vector3", sizeof(Vector3), asOBJ_VALUE | asGetTypeTraits<Vector3>() | asOBJ_POD | asOBJ_APP_CLASS_ALLFLOATS);

    // int IntRect::bottom_ | File: ../Math/Rect.h | Line: 471
    engine->RegisterObjectProperty("IntRect", "int bottom", offsetof(IntRect, bottom_));
    // int IntRect::left_ | File: ../Math/Rect.h | Line: 465
    engine->RegisterObjectProperty("IntRect", "int left", offsetof(IntRect, left_));
    // int IntRect::right_ | File: ../Math/Rect.h | Line: 469
    engine->RegisterObjectProperty("IntRect", "int right", offsetof(IntRect, right_));
    // int IntRect::top_ | File: ../Math/Rect.h | Line: 467
    engine->RegisterObjectProperty("IntRect", "int top", offsetof(IntRect, top_));
    // int IntRect::Bottom() const | File: ../Math/Rect.h | Line: 462
    engine->RegisterObjectMethod("IntRect", "int Bottom() const", asMETHODPR(IntRect, Bottom, () const, int), asCALL_THISCALL);
    // void IntRect::Clip(const IntRect &rect) | File: ../Math/Rect.h | Line: 433
    engine->RegisterObjectMethod("IntRect", "void Clip(const IntRect&in)", asMETHODPR(IntRect, Clip, (const IntRect &), void), asCALL_THISCALL);
    // int IntRect::Height() const | File: ../Math/Rect.h | Line: 420
    engine->RegisterObjectMethod("IntRect", "int get_height() const", asMETHODPR(IntRect, Height, () const, int), asCALL_THISCALL);
    // IntRect::IntRect() noexcept | File: ../Math/Rect.h | Line: 286
    engine->RegisterObjectBehaviour("IntRect", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(IntRect_IntRect_286_5), asCALL_CDECL_OBJFIRST);
    // IntRect::IntRect(const IntVector2 &min, const IntVector2 &max) noexcept | File: ../Math/Rect.h | Line: 295
    engine->RegisterObjectBehaviour("IntRect", asBEHAVE_CONSTRUCT, "void f(const IntVector2&in, const IntVector2&in)", asFUNCTION(IntRect_IntRect_295_5), asCALL_CDECL_OBJFIRST);
    // IntRect::IntRect(int left, int top, int right, int bottom) noexcept | File: ../Math/Rect.h | Line: 304
    engine->RegisterObjectBehaviour("IntRect", asBEHAVE_CONSTRUCT, "void f(int, int, int, int)", asFUNCTION(IntRect_IntRect_304_5), asCALL_CDECL_OBJFIRST);
    // Intersection IntRect::IsInside(const IntVector2 &point) const | File: ../Math/Rect.h | Line: 423
    engine->RegisterObjectMethod("IntRect", "Intersection IsInside(const IntVector2&in) const", asMETHODPR(IntRect, IsInside, (const IntVector2 &) const, Intersection), asCALL_THISCALL);
    // int IntRect::Left() const | File: ../Math/Rect.h | Line: 453
    engine->RegisterObjectMethod("IntRect", "int Left() const", asMETHODPR(IntRect, Left, () const, int), asCALL_THISCALL);
    // IntVector2 IntRect::Max() const | File: ../Math/Rect.h | Line: 450
    engine->RegisterObjectMethod("IntRect", "IntVector2 Max() const", asMETHODPR(IntRect, Max, () const, IntVector2), asCALL_THISCALL);
    // void IntRect::Merge(const IntRect &rect) | File: ../Math/Rect.h | Line: 437
    engine->RegisterObjectMethod("IntRect", "void Merge(const IntRect&in)", asMETHODPR(IntRect, Merge, (const IntRect &), void), asCALL_THISCALL);
    // IntVector2 IntRect::Min() const | File: ../Math/Rect.h | Line: 447
    engine->RegisterObjectMethod("IntRect", "IntVector2 Min() const", asMETHODPR(IntRect, Min, () const, IntVector2), asCALL_THISCALL);
    // IntRect IntRect::operator*(float value) const | File: ../Math/Rect.h | Line: 384
    engine->RegisterObjectMethod("IntRect", "IntRect opMul(float) const", asMETHODPR(IntRect, operator*, (float) const, IntRect), asCALL_THISCALL);
    // IntRect& IntRect::operator*=(float value) | File: ../Math/Rect.h | Line: 365
    engine->RegisterObjectMethod("IntRect", "IntRect& opMulAssign(float)", asMETHODPR(IntRect, operator*=, (float), IntRect &), asCALL_THISCALL);
    // IntRect IntRect::operator+(const IntRect &rhs) const | File: ../Math/Rect.h | Line: 393
    engine->RegisterObjectMethod("IntRect", "IntRect opAdd(const IntRect&in) const", asMETHODPR(IntRect, operator+, (const IntRect &) const, IntRect), asCALL_THISCALL);
    // IntRect& IntRect::operator+=(const IntRect &rhs) | File: ../Math/Rect.h | Line: 335
    engine->RegisterObjectMethod("IntRect", "IntRect& opAddAssign(const IntRect&in)", asMETHODPR(IntRect, operator+=, (const IntRect &), IntRect &), asCALL_THISCALL);
    // IntRect IntRect::operator-(const IntRect &rhs) const | File: ../Math/Rect.h | Line: 402
    engine->RegisterObjectMethod("IntRect", "IntRect opSub(const IntRect&in) const", asMETHODPR(IntRect, operator-, (const IntRect &) const, IntRect), asCALL_THISCALL);
    // IntRect& IntRect::operator-=(const IntRect &rhs) | File: ../Math/Rect.h | Line: 345
    engine->RegisterObjectMethod("IntRect", "IntRect& opSubAssign(const IntRect&in)", asMETHODPR(IntRect, operator-=, (const IntRect &), IntRect &), asCALL_THISCALL);
    // IntRect IntRect::operator/(float value) const | File: ../Math/Rect.h | Line: 375
    engine->RegisterObjectMethod("IntRect", "IntRect opDiv(float) const", asMETHODPR(IntRect, operator/, (float) const, IntRect), asCALL_THISCALL);
    // IntRect& IntRect::operator/=(float value) | File: ../Math/Rect.h | Line: 355
    engine->RegisterObjectMethod("IntRect", "IntRect& opDivAssign(float)", asMETHODPR(IntRect, operator/=, (float), IntRect &), asCALL_THISCALL);
    // bool IntRect::operator==(const IntRect &rhs) const | File: ../Math/Rect.h | Line: 323
    engine->RegisterObjectMethod("IntRect", "bool opEquals(const IntRect&in) const", asMETHODPR(IntRect, operator==, (const IntRect &) const, bool), asCALL_THISCALL);
    // int IntRect::Right() const | File: ../Math/Rect.h | Line: 459
    engine->RegisterObjectMethod("IntRect", "int Right() const", asMETHODPR(IntRect, Right, () const, int), asCALL_THISCALL);
    // IntVector2 IntRect::Size() const | File: ../Math/Rect.h | Line: 412
    engine->RegisterObjectMethod("IntRect", "IntVector2 get_size() const", asMETHODPR(IntRect, Size, () const, IntVector2), asCALL_THISCALL);
    // int IntRect::Top() const | File: ../Math/Rect.h | Line: 456
    engine->RegisterObjectMethod("IntRect", "int Top() const", asMETHODPR(IntRect, Top, () const, int), asCALL_THISCALL);
    // String IntRect::ToString() const | File: ../Math/Rect.h | Line: 444
    engine->RegisterObjectMethod("IntRect", "String ToString() const", asMETHODPR(IntRect, ToString, () const, String), asCALL_THISCALL);
    // int IntRect::Width() const | File: ../Math/Rect.h | Line: 416
    engine->RegisterObjectMethod("IntRect", "int get_width() const", asMETHODPR(IntRect, Width, () const, int), asCALL_THISCALL);

    // int IntVector2::x_ | File: ../Math/Vector2.h | Line: 159
    engine->RegisterObjectProperty("IntVector2", "int x", offsetof(IntVector2, x_));
    // int IntVector2::y_ | File: ../Math/Vector2.h | Line: 161
    engine->RegisterObjectProperty("IntVector2", "int y", offsetof(IntVector2, y_));
    // IntVector2::IntVector2() noexcept | File: ../Math/Vector2.h | Line: 36
    engine->RegisterObjectBehaviour("IntVector2", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(IntVector2_IntVector2_36_5), asCALL_CDECL_OBJFIRST);
    // IntVector2::IntVector2(int x, int y) noexcept | File: ../Math/Vector2.h | Line: 43
    engine->RegisterObjectBehaviour("IntVector2", asBEHAVE_CONSTRUCT, "void f(int, int)", asFUNCTION(IntVector2_IntVector2_43_5), asCALL_CDECL_OBJFIRST);
    // IntVector2::IntVector2(const IntVector2 &rhs) noexcept=default | File: ../Math/Vector2.h | Line: 65
    engine->RegisterObjectBehaviour("IntVector2", asBEHAVE_CONSTRUCT, "void f(const IntVector2&in)", asFUNCTION(IntVector2_IntVector2_65_5), asCALL_CDECL_OBJFIRST);
    // float IntVector2::Length() const | File: ../Math/Vector2.h | Line: 156
    engine->RegisterObjectMethod("IntVector2", "float Length() const", asMETHODPR(IntVector2, Length, () const, float), asCALL_THISCALL);
    // IntVector2 IntVector2::operator*(int rhs) const | File: ../Math/Vector2.h | Line: 86
    engine->RegisterObjectMethod("IntVector2", "IntVector2 opMul(int) const", asMETHODPR(IntVector2, operator*, (int) const, IntVector2), asCALL_THISCALL);
    // IntVector2 IntVector2::operator*(const IntVector2 &rhs) const | File: ../Math/Vector2.h | Line: 89
    engine->RegisterObjectMethod("IntVector2", "IntVector2 opMul(const IntVector2&in) const", asMETHODPR(IntVector2, operator*, (const IntVector2 &) const, IntVector2), asCALL_THISCALL);
    // IntVector2& IntVector2::operator*=(int rhs) | File: ../Math/Vector2.h | Line: 114
    engine->RegisterObjectMethod("IntVector2", "IntVector2& opMulAssign(int)", asMETHODPR(IntVector2, operator*=, (int), IntVector2 &), asCALL_THISCALL);
    // IntVector2& IntVector2::operator*=(const IntVector2 &rhs) | File: ../Math/Vector2.h | Line: 122
    engine->RegisterObjectMethod("IntVector2", "IntVector2& opMulAssign(const IntVector2&in)", asMETHODPR(IntVector2, operator*=, (const IntVector2 &), IntVector2 &), asCALL_THISCALL);
    // IntVector2 IntVector2::operator+(const IntVector2 &rhs) const | File: ../Math/Vector2.h | Line: 77
    engine->RegisterObjectMethod("IntVector2", "IntVector2 opAdd(const IntVector2&in) const", asMETHODPR(IntVector2, operator+, (const IntVector2 &) const, IntVector2), asCALL_THISCALL);
    // IntVector2& IntVector2::operator+=(const IntVector2 &rhs) | File: ../Math/Vector2.h | Line: 98
    engine->RegisterObjectMethod("IntVector2", "IntVector2& opAddAssign(const IntVector2&in)", asMETHODPR(IntVector2, operator+=, (const IntVector2 &), IntVector2 &), asCALL_THISCALL);
    // IntVector2 IntVector2::operator-() const | File: ../Math/Vector2.h | Line: 80
    engine->RegisterObjectMethod("IntVector2", "IntVector2 opNeg() const", asMETHODPR(IntVector2, operator-, () const, IntVector2), asCALL_THISCALL);
    // IntVector2 IntVector2::operator-(const IntVector2 &rhs) const | File: ../Math/Vector2.h | Line: 83
    engine->RegisterObjectMethod("IntVector2", "IntVector2 opSub(const IntVector2&in) const", asMETHODPR(IntVector2, operator-, (const IntVector2 &) const, IntVector2), asCALL_THISCALL);
    // IntVector2& IntVector2::operator-=(const IntVector2 &rhs) | File: ../Math/Vector2.h | Line: 106
    engine->RegisterObjectMethod("IntVector2", "IntVector2& opSubAssign(const IntVector2&in)", asMETHODPR(IntVector2, operator-=, (const IntVector2 &), IntVector2 &), asCALL_THISCALL);
    // IntVector2 IntVector2::operator/(int rhs) const | File: ../Math/Vector2.h | Line: 92
    engine->RegisterObjectMethod("IntVector2", "IntVector2 opDiv(int) const", asMETHODPR(IntVector2, operator/, (int) const, IntVector2), asCALL_THISCALL);
    // IntVector2 IntVector2::operator/(const IntVector2 &rhs) const | File: ../Math/Vector2.h | Line: 95
    engine->RegisterObjectMethod("IntVector2", "IntVector2 opDiv(const IntVector2&in) const", asMETHODPR(IntVector2, operator/, (const IntVector2 &) const, IntVector2), asCALL_THISCALL);
    // IntVector2& IntVector2::operator/=(int rhs) | File: ../Math/Vector2.h | Line: 130
    engine->RegisterObjectMethod("IntVector2", "IntVector2& opDivAssign(int)", asMETHODPR(IntVector2, operator/=, (int), IntVector2 &), asCALL_THISCALL);
    // IntVector2& IntVector2::operator/=(const IntVector2 &rhs) | File: ../Math/Vector2.h | Line: 138
    engine->RegisterObjectMethod("IntVector2", "IntVector2& opDivAssign(const IntVector2&in)", asMETHODPR(IntVector2, operator/=, (const IntVector2 &), IntVector2 &), asCALL_THISCALL);
    // IntVector2& IntVector2::operator=(const IntVector2 &rhs) noexcept=default | File: ../Math/Vector2.h | Line: 68
    engine->RegisterObjectMethod("IntVector2", "IntVector2& opAssign(const IntVector2&in)", asMETHODPR(IntVector2, operator=, (const IntVector2 &), IntVector2 &), asCALL_THISCALL);
    // bool IntVector2::operator==(const IntVector2 &rhs) const | File: ../Math/Vector2.h | Line: 71
    engine->RegisterObjectMethod("IntVector2", "bool opEquals(const IntVector2&in) const", asMETHODPR(IntVector2, operator==, (const IntVector2 &) const, bool), asCALL_THISCALL);
    // unsigned IntVector2::ToHash() const | File: ../Math/Vector2.h | Line: 153
    engine->RegisterObjectMethod("IntVector2", "uint ToHash() const", asMETHODPR(IntVector2, ToHash, () const, unsigned), asCALL_THISCALL);
    // String IntVector2::ToString() const | File: ../Math/Vector2.h | Line: 150
    engine->RegisterObjectMethod("IntVector2", "String ToString() const", asMETHODPR(IntVector2, ToString, () const, String), asCALL_THISCALL);

    // int IntVector3::x_ | File: ../Math/Vector3.h | Line: 161
    engine->RegisterObjectProperty("IntVector3", "int x", offsetof(IntVector3, x_));
    // int IntVector3::y_ | File: ../Math/Vector3.h | Line: 163
    engine->RegisterObjectProperty("IntVector3", "int y", offsetof(IntVector3, y_));
    // int IntVector3::z_ | File: ../Math/Vector3.h | Line: 165
    engine->RegisterObjectProperty("IntVector3", "int z", offsetof(IntVector3, z_));
    // IntVector3::IntVector3() noexcept | File: ../Math/Vector3.h | Line: 36
    engine->RegisterObjectBehaviour("IntVector3", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(IntVector3_IntVector3_36_5), asCALL_CDECL_OBJFIRST);
    // IntVector3::IntVector3(int x, int y, int z) noexcept | File: ../Math/Vector3.h | Line: 44
    engine->RegisterObjectBehaviour("IntVector3", asBEHAVE_CONSTRUCT, "void f(int, int, int)", asFUNCTION(IntVector3_IntVector3_44_5), asCALL_CDECL_OBJFIRST);
    // IntVector3::IntVector3(const IntVector3 &rhs) noexcept=default | File: ../Math/Vector3.h | Line: 61
    engine->RegisterObjectBehaviour("IntVector3", asBEHAVE_CONSTRUCT, "void f(const IntVector3&in)", asFUNCTION(IntVector3_IntVector3_61_5), asCALL_CDECL_OBJFIRST);
    // float IntVector3::Length() const | File: ../Math/Vector3.h | Line: 158
    engine->RegisterObjectMethod("IntVector3", "float Length() const", asMETHODPR(IntVector3, Length, () const, float), asCALL_THISCALL);
    // IntVector3 IntVector3::operator*(int rhs) const | File: ../Math/Vector3.h | Line: 82
    engine->RegisterObjectMethod("IntVector3", "IntVector3 opMul(int) const", asMETHODPR(IntVector3, operator*, (int) const, IntVector3), asCALL_THISCALL);
    // IntVector3 IntVector3::operator*(const IntVector3 &rhs) const | File: ../Math/Vector3.h | Line: 85
    engine->RegisterObjectMethod("IntVector3", "IntVector3 opMul(const IntVector3&in) const", asMETHODPR(IntVector3, operator*, (const IntVector3 &) const, IntVector3), asCALL_THISCALL);
    // IntVector3& IntVector3::operator*=(int rhs) | File: ../Math/Vector3.h | Line: 112
    engine->RegisterObjectMethod("IntVector3", "IntVector3& opMulAssign(int)", asMETHODPR(IntVector3, operator*=, (int), IntVector3 &), asCALL_THISCALL);
    // IntVector3& IntVector3::operator*=(const IntVector3 &rhs) | File: ../Math/Vector3.h | Line: 121
    engine->RegisterObjectMethod("IntVector3", "IntVector3& opMulAssign(const IntVector3&in)", asMETHODPR(IntVector3, operator*=, (const IntVector3 &), IntVector3 &), asCALL_THISCALL);
    // IntVector3 IntVector3::operator+(const IntVector3 &rhs) const | File: ../Math/Vector3.h | Line: 73
    engine->RegisterObjectMethod("IntVector3", "IntVector3 opAdd(const IntVector3&in) const", asMETHODPR(IntVector3, operator+, (const IntVector3 &) const, IntVector3), asCALL_THISCALL);
    // IntVector3& IntVector3::operator+=(const IntVector3 &rhs) | File: ../Math/Vector3.h | Line: 94
    engine->RegisterObjectMethod("IntVector3", "IntVector3& opAddAssign(const IntVector3&in)", asMETHODPR(IntVector3, operator+=, (const IntVector3 &), IntVector3 &), asCALL_THISCALL);
    // IntVector3 IntVector3::operator-() const | File: ../Math/Vector3.h | Line: 76
    engine->RegisterObjectMethod("IntVector3", "IntVector3 opNeg() const", asMETHODPR(IntVector3, operator-, () const, IntVector3), asCALL_THISCALL);
    // IntVector3 IntVector3::operator-(const IntVector3 &rhs) const | File: ../Math/Vector3.h | Line: 79
    engine->RegisterObjectMethod("IntVector3", "IntVector3 opSub(const IntVector3&in) const", asMETHODPR(IntVector3, operator-, (const IntVector3 &) const, IntVector3), asCALL_THISCALL);
    // IntVector3& IntVector3::operator-=(const IntVector3 &rhs) | File: ../Math/Vector3.h | Line: 103
    engine->RegisterObjectMethod("IntVector3", "IntVector3& opSubAssign(const IntVector3&in)", asMETHODPR(IntVector3, operator-=, (const IntVector3 &), IntVector3 &), asCALL_THISCALL);
    // IntVector3 IntVector3::operator/(int rhs) const | File: ../Math/Vector3.h | Line: 88
    engine->RegisterObjectMethod("IntVector3", "IntVector3 opDiv(int) const", asMETHODPR(IntVector3, operator/, (int) const, IntVector3), asCALL_THISCALL);
    // IntVector3 IntVector3::operator/(const IntVector3 &rhs) const | File: ../Math/Vector3.h | Line: 91
    engine->RegisterObjectMethod("IntVector3", "IntVector3 opDiv(const IntVector3&in) const", asMETHODPR(IntVector3, operator/, (const IntVector3 &) const, IntVector3), asCALL_THISCALL);
    // IntVector3& IntVector3::operator/=(int rhs) | File: ../Math/Vector3.h | Line: 130
    engine->RegisterObjectMethod("IntVector3", "IntVector3& opDivAssign(int)", asMETHODPR(IntVector3, operator/=, (int), IntVector3 &), asCALL_THISCALL);
    // IntVector3& IntVector3::operator/=(const IntVector3 &rhs) | File: ../Math/Vector3.h | Line: 139
    engine->RegisterObjectMethod("IntVector3", "IntVector3& opDivAssign(const IntVector3&in)", asMETHODPR(IntVector3, operator/=, (const IntVector3 &), IntVector3 &), asCALL_THISCALL);
    // IntVector3& IntVector3::operator=(const IntVector3 &rhs) noexcept=default | File: ../Math/Vector3.h | Line: 64
    engine->RegisterObjectMethod("IntVector3", "IntVector3& opAssign(const IntVector3&in)", asMETHODPR(IntVector3, operator=, (const IntVector3 &), IntVector3 &), asCALL_THISCALL);
    // bool IntVector3::operator==(const IntVector3 &rhs) const | File: ../Math/Vector3.h | Line: 67
    engine->RegisterObjectMethod("IntVector3", "bool opEquals(const IntVector3&in) const", asMETHODPR(IntVector3, operator==, (const IntVector3 &) const, bool), asCALL_THISCALL);
    // unsigned IntVector3::ToHash() const | File: ../Math/Vector3.h | Line: 155
    engine->RegisterObjectMethod("IntVector3", "uint ToHash() const", asMETHODPR(IntVector3, ToHash, () const, unsigned), asCALL_THISCALL);
    // String IntVector3::ToString() const | File: ../Math/Vector3.h | Line: 152
    engine->RegisterObjectMethod("IntVector3", "String ToString() const", asMETHODPR(IntVector3, ToString, () const, String), asCALL_THISCALL);

    // Vector3 BoundingBox::max_ | File: ../Math/BoundingBox.h | Line: 333
    engine->RegisterObjectProperty("BoundingBox", "Vector3 max", offsetof(BoundingBox, max_));
    // Vector3 BoundingBox::min_ | File: ../Math/BoundingBox.h | Line: 329
    engine->RegisterObjectProperty("BoundingBox", "Vector3 min", offsetof(BoundingBox, min_));
    // BoundingBox::BoundingBox() noexcept | File: ../Math/BoundingBox.h | Line: 48
    engine->RegisterObjectBehaviour("BoundingBox", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(BoundingBox_BoundingBox_48_5), asCALL_CDECL_OBJFIRST);
    // BoundingBox::BoundingBox(const BoundingBox &box) noexcept | File: ../Math/BoundingBox.h | Line: 55
    engine->RegisterObjectBehaviour("BoundingBox", asBEHAVE_CONSTRUCT, "void f(const BoundingBox&in)", asFUNCTION(BoundingBox_BoundingBox_55_5), asCALL_CDECL_OBJFIRST);
    // BoundingBox::BoundingBox(const Rect &rect) noexcept | File: ../Math/BoundingBox.h | Line: 62
    engine->RegisterObjectBehaviour("BoundingBox", asBEHAVE_CONSTRUCT, "void f(const Rect&in)", asFUNCTION(BoundingBox_BoundingBox_62_14), asCALL_CDECL_OBJFIRST);
    // BoundingBox::BoundingBox(const Vector3 &min, const Vector3 &max) noexcept | File: ../Math/BoundingBox.h | Line: 69
    engine->RegisterObjectBehaviour("BoundingBox", asBEHAVE_CONSTRUCT, "void f(const Vector3&in, const Vector3&in)", asFUNCTION(BoundingBox_BoundingBox_69_5), asCALL_CDECL_OBJFIRST);
    // BoundingBox::BoundingBox(float min, float max) noexcept | File: ../Math/BoundingBox.h | Line: 76
    engine->RegisterObjectBehaviour("BoundingBox", asBEHAVE_CONSTRUCT, "void f(float, float)", asFUNCTION(BoundingBox_BoundingBox_76_5), asCALL_CDECL_OBJFIRST);
    // BoundingBox::BoundingBox(const Frustum &frustum) | File: ../Math/BoundingBox.h | Line: 101
    engine->RegisterObjectBehaviour("BoundingBox", asBEHAVE_CONSTRUCT, "void f(const Frustum&in)", asFUNCTION(BoundingBox_BoundingBox_101_14), asCALL_CDECL_OBJFIRST);
    // BoundingBox::BoundingBox(const Polyhedron &poly) | File: ../Math/BoundingBox.h | Line: 109
    engine->RegisterObjectBehaviour("BoundingBox", asBEHAVE_CONSTRUCT, "void f(const Polyhedron&in)", asFUNCTION(BoundingBox_BoundingBox_109_14), asCALL_CDECL_OBJFIRST);
    // BoundingBox::BoundingBox(const Sphere &sphere) | File: ../Math/BoundingBox.h | Line: 117
    engine->RegisterObjectBehaviour("BoundingBox", asBEHAVE_CONSTRUCT, "void f(const Sphere&in)", asFUNCTION(BoundingBox_BoundingBox_117_14), asCALL_CDECL_OBJFIRST);
    // Vector3 BoundingBox::Center() const | File: ../Math/BoundingBox.h | Line: 268
    engine->RegisterObjectMethod("BoundingBox", "Vector3 get_center() const", asMETHODPR(BoundingBox, Center, () const, Vector3), asCALL_THISCALL);
    // void BoundingBox::Clear() | File: ../Math/BoundingBox.h | Line: 249
    engine->RegisterObjectMethod("BoundingBox", "void Clear()", asMETHODPR(BoundingBox, Clear, (), void), asCALL_THISCALL);
    // void BoundingBox::Clip(const BoundingBox &box) | File: ../Math/BoundingBox.h | Line: 242
    engine->RegisterObjectMethod("BoundingBox", "void Clip(const BoundingBox&in)", asMETHODPR(BoundingBox, Clip, (const BoundingBox &), void), asCALL_THISCALL);
    // void BoundingBox::Define(const BoundingBox &box) | File: ../Math/BoundingBox.h | Line: 147
    engine->RegisterObjectMethod("BoundingBox", "void Define(const BoundingBox&in)", asMETHODPR(BoundingBox, Define, (const BoundingBox &), void), asCALL_THISCALL);
    // void BoundingBox::Define(const Rect &rect) | File: ../Math/BoundingBox.h | Line: 153
    engine->RegisterObjectMethod("BoundingBox", "void Define(const Rect&in)", asMETHODPR(BoundingBox, Define, (const Rect &), void), asCALL_THISCALL);
    // void BoundingBox::Define(const Vector3 &min, const Vector3 &max) | File: ../Math/BoundingBox.h | Line: 159
    engine->RegisterObjectMethod("BoundingBox", "void Define(const Vector3&in, const Vector3&in)", asMETHODPR(BoundingBox, Define, (const Vector3 &, const Vector3 &), void), asCALL_THISCALL);
    // void BoundingBox::Define(float min, float max) | File: ../Math/BoundingBox.h | Line: 166
    engine->RegisterObjectMethod("BoundingBox", "void Define(float, float)", asMETHODPR(BoundingBox, Define, (float, float), void), asCALL_THISCALL);
    // void BoundingBox::Define(const Vector3 &point) | File: ../Math/BoundingBox.h | Line: 173
    engine->RegisterObjectMethod("BoundingBox", "void Define(const Vector3&in)", asMETHODPR(BoundingBox, Define, (const Vector3 &), void), asCALL_THISCALL);
    // void BoundingBox::Define(const Frustum &frustum) | File: ../Math/BoundingBox.h | Line: 227
    engine->RegisterObjectMethod("BoundingBox", "void Define(const Frustum&in)", asMETHODPR(BoundingBox, Define, (const Frustum &), void), asCALL_THISCALL);
    // void BoundingBox::Define(const Polyhedron &poly) | File: ../Math/BoundingBox.h | Line: 229
    engine->RegisterObjectMethod("BoundingBox", "void Define(const Polyhedron&in)", asMETHODPR(BoundingBox, Define, (const Polyhedron &), void), asCALL_THISCALL);
    // void BoundingBox::Define(const Sphere &sphere) | File: ../Math/BoundingBox.h | Line: 231
    engine->RegisterObjectMethod("BoundingBox", "void Define(const Sphere&in)", asMETHODPR(BoundingBox, Define, (const Sphere &), void), asCALL_THISCALL);
    // bool BoundingBox::Defined() const | File: ../Math/BoundingBox.h | Line: 261
    engine->RegisterObjectMethod("BoundingBox", "bool Defined() const", asMETHODPR(BoundingBox, Defined, () const, bool), asCALL_THISCALL);
    // float BoundingBox::DistanceToPoint(const Vector3 &point) const | File: ../Math/BoundingBox.h | Line: 285
    engine->RegisterObjectMethod("BoundingBox", "float DistanceToPoint(const Vector3&in) const", asMETHODPR(BoundingBox, DistanceToPoint, (const Vector3 &) const, float), asCALL_THISCALL);
    // Vector3 BoundingBox::HalfSize() const | File: ../Math/BoundingBox.h | Line: 276
    engine->RegisterObjectMethod("BoundingBox", "Vector3 get_halfSize() const", asMETHODPR(BoundingBox, HalfSize, () const, Vector3), asCALL_THISCALL);
    // Intersection BoundingBox::IsInside(const Vector3 &point) const | File: ../Math/BoundingBox.h | Line: 288
    engine->RegisterObjectMethod("BoundingBox", "Intersection IsInside(const Vector3&in) const", asMETHODPR(BoundingBox, IsInside, (const Vector3 &) const, Intersection), asCALL_THISCALL);
    // Intersection BoundingBox::IsInside(const BoundingBox &box) const | File: ../Math/BoundingBox.h | Line: 298
    engine->RegisterObjectMethod("BoundingBox", "Intersection IsInside(const BoundingBox&in) const", asMETHODPR(BoundingBox, IsInside, (const BoundingBox &) const, Intersection), asCALL_THISCALL);
    // Intersection BoundingBox::IsInside(const Sphere &sphere) const | File: ../Math/BoundingBox.h | Line: 321
    engine->RegisterObjectMethod("BoundingBox", "Intersection IsInside(const Sphere&in) const", asMETHODPR(BoundingBox, IsInside, (const Sphere &) const, Intersection), asCALL_THISCALL);
    // Intersection BoundingBox::IsInsideFast(const BoundingBox &box) const | File: ../Math/BoundingBox.h | Line: 311
    engine->RegisterObjectMethod("BoundingBox", "Intersection IsInsideFast(const BoundingBox&in) const", asMETHODPR(BoundingBox, IsInsideFast, (const BoundingBox &) const, Intersection), asCALL_THISCALL);
    // Intersection BoundingBox::IsInsideFast(const Sphere &sphere) const | File: ../Math/BoundingBox.h | Line: 323
    engine->RegisterObjectMethod("BoundingBox", "Intersection IsInsideFast(const Sphere&in) const", asMETHODPR(BoundingBox, IsInsideFast, (const Sphere &) const, Intersection), asCALL_THISCALL);
    // void BoundingBox::Merge(const Vector3 &point) | File: ../Math/BoundingBox.h | Line: 179
    engine->RegisterObjectMethod("BoundingBox", "void Merge(const Vector3&in)", asMETHODPR(BoundingBox, Merge, (const Vector3 &), void), asCALL_THISCALL);
    // void BoundingBox::Merge(const BoundingBox &box) | File: ../Math/BoundingBox.h | Line: 202
    engine->RegisterObjectMethod("BoundingBox", "void Merge(const BoundingBox&in)", asMETHODPR(BoundingBox, Merge, (const BoundingBox &), void), asCALL_THISCALL);
    // void BoundingBox::Merge(const Frustum &frustum) | File: ../Math/BoundingBox.h | Line: 236
    engine->RegisterObjectMethod("BoundingBox", "void Merge(const Frustum&in)", asMETHODPR(BoundingBox, Merge, (const Frustum &), void), asCALL_THISCALL);
    // void BoundingBox::Merge(const Polyhedron &poly) | File: ../Math/BoundingBox.h | Line: 238
    engine->RegisterObjectMethod("BoundingBox", "void Merge(const Polyhedron&in)", asMETHODPR(BoundingBox, Merge, (const Polyhedron &), void), asCALL_THISCALL);
    // void BoundingBox::Merge(const Sphere &sphere) | File: ../Math/BoundingBox.h | Line: 240
    engine->RegisterObjectMethod("BoundingBox", "void Merge(const Sphere&in)", asMETHODPR(BoundingBox, Merge, (const Sphere &), void), asCALL_THISCALL);
    // BoundingBox& BoundingBox::operator=(const BoundingBox &rhs) noexcept | File: ../Math/BoundingBox.h | Line: 125
    engine->RegisterObjectMethod("BoundingBox", "BoundingBox& opAssign(const BoundingBox&in)", asMETHODPR(BoundingBox, operator=, (const BoundingBox &), BoundingBox &), asCALL_THISCALL);
    // BoundingBox& BoundingBox::operator=(const Rect &rhs) noexcept | File: ../Math/BoundingBox.h | Line: 133
    engine->RegisterObjectMethod("BoundingBox", "BoundingBox& opAssign(const Rect&in)", asMETHODPR(BoundingBox, operator=, (const Rect &), BoundingBox &), asCALL_THISCALL);
    // bool BoundingBox::operator==(const BoundingBox &rhs) const | File: ../Math/BoundingBox.h | Line: 141
    engine->RegisterObjectMethod("BoundingBox", "bool opEquals(const BoundingBox&in) const", asMETHODPR(BoundingBox, operator==, (const BoundingBox &) const, bool), asCALL_THISCALL);
    // Rect BoundingBox::Projected(const Matrix4 &projection) const | File: ../Math/BoundingBox.h | Line: 283
    engine->RegisterObjectMethod("BoundingBox", "Rect Projected(const Matrix4&in) const", asMETHODPR(BoundingBox, Projected, (const Matrix4 &) const, Rect), asCALL_THISCALL);
    // Vector3 BoundingBox::Size() const | File: ../Math/BoundingBox.h | Line: 272
    engine->RegisterObjectMethod("BoundingBox", "Vector3 get_size() const", asMETHODPR(BoundingBox, Size, () const, Vector3), asCALL_THISCALL);
    // String BoundingBox::ToString() const | File: ../Math/BoundingBox.h | Line: 326
    engine->RegisterObjectMethod("BoundingBox", "String ToString() const", asMETHODPR(BoundingBox, ToString, () const, String), asCALL_THISCALL);
    // void BoundingBox::Transform(const Matrix3 &transform) | File: ../Math/BoundingBox.h | Line: 244
    engine->RegisterObjectMethod("BoundingBox", "void Transform(const Matrix3&in)", asMETHODPR(BoundingBox, Transform, (const Matrix3 &), void), asCALL_THISCALL);
    // void BoundingBox::Transform(const Matrix3x4 &transform) | File: ../Math/BoundingBox.h | Line: 246
    engine->RegisterObjectMethod("BoundingBox", "void Transform(const Matrix3x4&in)", asMETHODPR(BoundingBox, Transform, (const Matrix3x4 &), void), asCALL_THISCALL);
    // BoundingBox BoundingBox::Transformed(const Matrix3 &transform) const | File: ../Math/BoundingBox.h | Line: 279
    engine->RegisterObjectMethod("BoundingBox", "BoundingBox Transformed(const Matrix3&in) const", asMETHODPR(BoundingBox, Transformed, (const Matrix3 &) const, BoundingBox), asCALL_THISCALL);
    // BoundingBox BoundingBox::Transformed(const Matrix3x4 &transform) const | File: ../Math/BoundingBox.h | Line: 281
    engine->RegisterObjectMethod("BoundingBox", "BoundingBox Transformed(const Matrix3x4&in) const", asMETHODPR(BoundingBox, Transformed, (const Matrix3x4 &) const, BoundingBox), asCALL_THISCALL);

    // float Color::a_ | File: ../Math/Color.h | Line: 268
    engine->RegisterObjectProperty("Color", "float a", offsetof(Color, a_));
    // float Color::b_ | File: ../Math/Color.h | Line: 266
    engine->RegisterObjectProperty("Color", "float b", offsetof(Color, b_));
    // float Color::g_ | File: ../Math/Color.h | Line: 264
    engine->RegisterObjectProperty("Color", "float g", offsetof(Color, g_));
    // float Color::r_ | File: ../Math/Color.h | Line: 262
    engine->RegisterObjectProperty("Color", "float r", offsetof(Color, r_));
    // Color Color::Abs() const | File: ../Math/Color.h | Line: 244
    engine->RegisterObjectMethod("Color", "Color Abs() const", asMETHODPR(Color, Abs, () const, Color), asCALL_THISCALL);
    // float Color::Average() const | File: ../Math/Color.h | Line: 176
    engine->RegisterObjectMethod("Color", "float Average() const", asMETHODPR(Color, Average, () const, float), asCALL_THISCALL);
    // float Color::Chroma() const | File: ../Math/Color.h | Line: 182
    engine->RegisterObjectMethod("Color", "float Chroma() const", asMETHODPR(Color, Chroma, () const, float), asCALL_THISCALL);
    // void Color::Clip(bool clipAlpha=false) | File: ../Math/Color.h | Line: 237
    engine->RegisterObjectMethod("Color", "void Clip(bool)", asMETHODPR(Color, Clip, (bool), void), asCALL_THISCALL);
    // Color::Color() noexcept | File: ../Math/Color.h | Line: 54
    engine->RegisterObjectBehaviour("Color", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(Color_Color_54_5), asCALL_CDECL_OBJFIRST);
    // Color::Color(const Color &color) noexcept=default | File: ../Math/Color.h | Line: 63
    engine->RegisterObjectBehaviour("Color", asBEHAVE_CONSTRUCT, "void f(const Color&in)", asFUNCTION(Color_Color_63_5), asCALL_CDECL_OBJFIRST);
    // Color::Color(const Color &color, float a) noexcept | File: ../Math/Color.h | Line: 66
    engine->RegisterObjectBehaviour("Color", asBEHAVE_CONSTRUCT, "void f(const Color&in, float)", asFUNCTION(Color_Color_66_5), asCALL_CDECL_OBJFIRST);
    // Color::Color(float r, float g, float b) noexcept | File: ../Math/Color.h | Line: 75
    engine->RegisterObjectBehaviour("Color", asBEHAVE_CONSTRUCT, "void f(float, float, float)", asFUNCTION(Color_Color_75_5), asCALL_CDECL_OBJFIRST);
    // Color::Color(float r, float g, float b, float a) noexcept | File: ../Math/Color.h | Line: 84
    engine->RegisterObjectBehaviour("Color", asBEHAVE_CONSTRUCT, "void f(float, float, float, float)", asFUNCTION(Color_Color_84_5), asCALL_CDECL_OBJFIRST);
    // Color::Color(const Vector3 &color) | File: ../Math/Color.h | Line: 107
    engine->RegisterObjectBehaviour("Color", asBEHAVE_CONSTRUCT, "void f(const Vector3&in)", asFUNCTION(Color_Color_107_14), asCALL_CDECL_OBJFIRST);
    // Color::Color(const Vector4 &color) | File: ../Math/Color.h | Line: 110
    engine->RegisterObjectBehaviour("Color", asBEHAVE_CONSTRUCT, "void f(const Vector4&in)", asFUNCTION(Color_Color_110_14), asCALL_CDECL_OBJFIRST);
    // bool Color::Equals(const Color &rhs) const | File: ../Math/Color.h | Line: 247
    engine->RegisterObjectMethod("Color", "bool Equals(const Color&in) const", asMETHODPR(Color, Equals, (const Color &) const, bool), asCALL_THISCALL);
    // void Color::FromHSL(float h, float s, float l, float a=1.0f) | File: ../Math/Color.h | Line: 162
    engine->RegisterObjectMethod("Color", "void FromHSL(float, float, float, float)", asMETHODPR(Color, FromHSL, (float, float, float, float), void), asCALL_THISCALL);
    // void Color::FromHSV(float h, float s, float v, float a=1.0f) | File: ../Math/Color.h | Line: 164
    engine->RegisterObjectMethod("Color", "void FromHSV(float, float, float, float)", asMETHODPR(Color, FromHSV, (float, float, float, float), void), asCALL_THISCALL);
    // void Color::FromUInt(unsigned color) | File: ../Math/Color.h | Line: 157
    engine->RegisterObjectMethod("Color", "void FromUInt(uint)", asMETHODPR(Color, FromUInt, (unsigned), void), asCALL_THISCALL);
    // Color Color::GammaToLinear() const | File: ../Math/Color.h | Line: 218
    engine->RegisterObjectMethod("Color", "Color GammaToLinear() const", asMETHODPR(Color, GammaToLinear, () const, Color), asCALL_THISCALL);
    // float Color::Hue() const | File: ../Math/Color.h | Line: 184
    engine->RegisterObjectMethod("Color", "float Hue() const", asMETHODPR(Color, Hue, () const, float), asCALL_THISCALL);
    // void Color::Invert(bool invertAlpha=false) | File: ../Math/Color.h | Line: 239
    engine->RegisterObjectMethod("Color", "void Invert(bool)", asMETHODPR(Color, Invert, (bool), void), asCALL_THISCALL);
    // Color Color::Lerp(const Color &rhs, float t) const | File: ../Math/Color.h | Line: 241
    engine->RegisterObjectMethod("Color", "Color Lerp(const Color&in, float) const", asMETHODPR(Color, Lerp, (const Color &, float) const, Color), asCALL_THISCALL);
    // float Color::Lightness() const | File: ../Math/Color.h | Line: 224
    engine->RegisterObjectMethod("Color", "float Lightness() const", asMETHODPR(Color, Lightness, () const, float), asCALL_THISCALL);
    // Color Color::LinearToGamma() const | File: ../Math/Color.h | Line: 221
    engine->RegisterObjectMethod("Color", "Color LinearToGamma() const", asMETHODPR(Color, LinearToGamma, () const, Color), asCALL_THISCALL);
    // float Color::Luma() const | File: ../Math/Color.h | Line: 179
    engine->RegisterObjectMethod("Color", "float Luma() const", asMETHODPR(Color, Luma, () const, float), asCALL_THISCALL);
    // float Color::MaxRGB() const | File: ../Math/Color.h | Line: 230
    engine->RegisterObjectMethod("Color", "float MaxRGB() const", asMETHODPR(Color, MaxRGB, () const, float), asCALL_THISCALL);
    // float Color::MinRGB() const | File: ../Math/Color.h | Line: 232
    engine->RegisterObjectMethod("Color", "float MinRGB() const", asMETHODPR(Color, MinRGB, () const, float), asCALL_THISCALL);
    // Color Color::operator*(float rhs) const | File: ../Math/Color.h | Line: 122
    engine->RegisterObjectMethod("Color", "Color opMul(float) const", asMETHODPR(Color, operator*, (float) const, Color), asCALL_THISCALL);
    // Color Color::operator+(const Color &rhs) const | File: ../Math/Color.h | Line: 125
    engine->RegisterObjectMethod("Color", "Color opAdd(const Color&in) const", asMETHODPR(Color, operator+, (const Color &) const, Color), asCALL_THISCALL);
    // Color& Color::operator+=(const Color &rhs) | File: ../Math/Color.h | Line: 134
    engine->RegisterObjectMethod("Color", "Color& opAddAssign(const Color&in)", asMETHODPR(Color, operator+=, (const Color &), Color &), asCALL_THISCALL);
    // Color Color::operator-() const | File: ../Math/Color.h | Line: 128
    engine->RegisterObjectMethod("Color", "Color opNeg() const", asMETHODPR(Color, operator-, () const, Color), asCALL_THISCALL);
    // Color Color::operator-(const Color &rhs) const | File: ../Math/Color.h | Line: 131
    engine->RegisterObjectMethod("Color", "Color opSub(const Color&in) const", asMETHODPR(Color, operator-, (const Color &) const, Color), asCALL_THISCALL);
    // Color& Color::operator=(const Color &rhs) noexcept=default | File: ../Math/Color.h | Line: 113
    engine->RegisterObjectMethod("Color", "Color& opAssign(const Color&in)", asMETHODPR(Color, operator=, (const Color &), Color &), asCALL_THISCALL);
    // bool Color::operator==(const Color &rhs) const | File: ../Math/Color.h | Line: 116
    engine->RegisterObjectMethod("Color", "bool opEquals(const Color&in) const", asMETHODPR(Color, operator==, (const Color &) const, bool), asCALL_THISCALL);
    // float Color::Range() const | File: ../Math/Color.h | Line: 234
    engine->RegisterObjectMethod("Color", "float Range() const", asMETHODPR(Color, Range, () const, float), asCALL_THISCALL);
    // float Color::SaturationHSL() const | File: ../Math/Color.h | Line: 186
    engine->RegisterObjectMethod("Color", "float SaturationHSL() const", asMETHODPR(Color, SaturationHSL, () const, float), asCALL_THISCALL);
    // float Color::SaturationHSV() const | File: ../Math/Color.h | Line: 188
    engine->RegisterObjectMethod("Color", "float SaturationHSV() const", asMETHODPR(Color, SaturationHSV, () const, float), asCALL_THISCALL);
    // float Color::SumRGB() const | File: ../Math/Color.h | Line: 173
    engine->RegisterObjectMethod("Color", "float SumRGB() const", asMETHODPR(Color, SumRGB, () const, float), asCALL_THISCALL);
    // unsigned Color::ToHash() const | File: ../Math/Color.h | Line: 259
    engine->RegisterObjectMethod("Color", "uint ToHash() const", asMETHODPR(Color, ToHash, () const, unsigned), asCALL_THISCALL);
    // Vector3 Color::ToHSL() const | File: ../Math/Color.h | Line: 153
    engine->RegisterObjectMethod("Color", "Vector3 ToHSL() const", asMETHODPR(Color, ToHSL, () const, Vector3), asCALL_THISCALL);
    // Vector3 Color::ToHSV() const | File: ../Math/Color.h | Line: 155
    engine->RegisterObjectMethod("Color", "Vector3 ToHSV() const", asMETHODPR(Color, ToHSV, () const, Vector3), asCALL_THISCALL);
    // String Color::ToString() const | File: ../Math/Color.h | Line: 253
    engine->RegisterObjectMethod("Color", "String ToString() const", asMETHODPR(Color, ToString, () const, String), asCALL_THISCALL);
    // unsigned Color::ToUInt() const | File: ../Math/Color.h | Line: 148
    engine->RegisterObjectMethod("Color", "uint ToUInt() const", asMETHODPR(Color, ToUInt, () const, unsigned), asCALL_THISCALL);
    // unsigned Color::ToUIntArgb() const | File: ../Math/Color.h | Line: 256
    engine->RegisterObjectMethod("Color", "uint ToUIntArgb() const", asMETHODPR(Color, ToUIntArgb, () const, unsigned), asCALL_THISCALL);
    // Vector3 Color::ToVector3() const | File: ../Math/Color.h | Line: 167
    engine->RegisterObjectMethod("Color", "Vector3 ToVector3() const", asMETHODPR(Color, ToVector3, () const, Vector3), asCALL_THISCALL);
    // Vector4 Color::ToVector4() const | File: ../Math/Color.h | Line: 170
    engine->RegisterObjectMethod("Color", "Vector4 ToVector4() const", asMETHODPR(Color, ToVector4, () const, Vector4), asCALL_THISCALL);
    // float Color::Value() const | File: ../Math/Color.h | Line: 191
    engine->RegisterObjectMethod("Color", "float Value() const", asMETHODPR(Color, Value, () const, float), asCALL_THISCALL);

    // Frustum::~Frustum()
    engine->RegisterObjectBehaviour("Frustum", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(Frustum_Destructor), asCALL_CDECL_OBJFIRST);
    // void Frustum::Define(float fov, float aspectRatio, float zoom, float nearZ, float farZ, const Matrix3x4 &transform=Matrix3x4::IDENTITY) | File: ../Math/Frustum.h | Line: 65
    engine->RegisterObjectMethod("Frustum", "void Define(float, float, float, float, float, const Matrix3x4&in)", asMETHODPR(Frustum, Define, (float, float, float, float, float, const Matrix3x4 &), void), asCALL_THISCALL);
    // void Frustum::Define(const Vector3 &near, const Vector3 &far, const Matrix3x4 &transform=Matrix3x4::IDENTITY) | File: ../Math/Frustum.h | Line: 67
    engine->RegisterObjectMethod("Frustum", "void Define(const Vector3&in, const Vector3&in, const Matrix3x4&in)", asMETHODPR(Frustum, Define, (const Vector3 &, const Vector3 &, const Matrix3x4 &), void), asCALL_THISCALL);
    // void Frustum::Define(const BoundingBox &box, const Matrix3x4 &transform=Matrix3x4::IDENTITY) | File: ../Math/Frustum.h | Line: 69
    engine->RegisterObjectMethod("Frustum", "void Define(const BoundingBox&in, const Matrix3x4&in)", asMETHODPR(Frustum, Define, (const BoundingBox &, const Matrix3x4 &), void), asCALL_THISCALL);
    // void Frustum::Define(const Matrix4 &projection) | File: ../Math/Frustum.h | Line: 71
    engine->RegisterObjectMethod("Frustum", "void Define(const Matrix4&in)", asMETHODPR(Frustum, Define, (const Matrix4 &), void), asCALL_THISCALL);
    // void Frustum::DefineOrtho(float orthoSize, float aspectRatio, float zoom, float nearZ, float farZ, const Matrix3x4 &transform=Matrix3x4::IDENTITY) | File: ../Math/Frustum.h | Line: 73
    engine->RegisterObjectMethod("Frustum", "void DefineOrtho(float, float, float, float, float, const Matrix3x4&in)", asMETHODPR(Frustum, DefineOrtho, (float, float, float, float, float, const Matrix3x4 &), void), asCALL_THISCALL);
    // void Frustum::DefineSplit(const Matrix4 &projection, float near, float far) | File: ../Math/Frustum.h | Line: 76
    engine->RegisterObjectMethod("Frustum", "void DefineSplit(const Matrix4&in, float, float)", asMETHODPR(Frustum, DefineSplit, (const Matrix4 &, float, float), void), asCALL_THISCALL);
    // float Frustum::Distance(const Vector3 &point) const | File: ../Math/Frustum.h | Line: 162
    engine->RegisterObjectMethod("Frustum", "float Distance(const Vector3&in) const", asMETHODPR(Frustum, Distance, (const Vector3 &) const, float), asCALL_THISCALL);
    // Frustum::Frustum() noexcept=default | File: ../Math/Frustum.h | Line: 55
    engine->RegisterObjectBehaviour("Frustum", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(Frustum_Frustum_55_5), asCALL_CDECL_OBJFIRST);
    // Frustum::Frustum(const Frustum &frustum) noexcept | File: ../Math/Frustum.h | Line: 58
    engine->RegisterObjectBehaviour("Frustum", asBEHAVE_CONSTRUCT, "void f(const Frustum&in)", asFUNCTION(Frustum_Frustum_58_5), asCALL_CDECL_OBJFIRST);
    // Intersection Frustum::IsInside(const Vector3 &point) const | File: ../Math/Frustum.h | Line: 83
    engine->RegisterObjectMethod("Frustum", "Intersection IsInside(const Vector3&in) const", asMETHODPR(Frustum, IsInside, (const Vector3 &) const, Intersection), asCALL_THISCALL);
    // Intersection Frustum::IsInside(const Sphere &sphere) const | File: ../Math/Frustum.h | Line: 95
    engine->RegisterObjectMethod("Frustum", "Intersection IsInside(const Sphere&in) const", asMETHODPR(Frustum, IsInside, (const Sphere &) const, Intersection), asCALL_THISCALL);
    // Intersection Frustum::IsInside(const BoundingBox &box) const | File: ../Math/Frustum.h | Line: 123
    engine->RegisterObjectMethod("Frustum", "Intersection IsInside(const BoundingBox&in) const", asMETHODPR(Frustum, IsInside, (const BoundingBox &) const, Intersection), asCALL_THISCALL);
    // Intersection Frustum::IsInsideFast(const Sphere &sphere) const | File: ../Math/Frustum.h | Line: 111
    engine->RegisterObjectMethod("Frustum", "Intersection IsInsideFast(const Sphere&in) const", asMETHODPR(Frustum, IsInsideFast, (const Sphere &) const, Intersection), asCALL_THISCALL);
    // Intersection Frustum::IsInsideFast(const BoundingBox &box) const | File: ../Math/Frustum.h | Line: 144
    engine->RegisterObjectMethod("Frustum", "Intersection IsInsideFast(const BoundingBox&in) const", asMETHODPR(Frustum, IsInsideFast, (const BoundingBox &) const, Intersection), asCALL_THISCALL);
    // Frustum& Frustum::operator=(const Frustum &rhs) noexcept | File: ../Math/Frustum.h | Line: 61
    engine->RegisterObjectMethod("Frustum", "Frustum& opAssign(const Frustum&in)", asMETHODPR(Frustum, operator=, (const Frustum &), Frustum &), asCALL_THISCALL);
    // Rect Frustum::Projected(const Matrix4 &projection) const | File: ../Math/Frustum.h | Line: 176
    engine->RegisterObjectMethod("Frustum", "Rect Projected(const Matrix4&in) const", asMETHODPR(Frustum, Projected, (const Matrix4 &) const, Rect), asCALL_THISCALL);
    // void Frustum::Transform(const Matrix3 &transform) | File: ../Math/Frustum.h | Line: 78
    engine->RegisterObjectMethod("Frustum", "void Transform(const Matrix3&in)", asMETHODPR(Frustum, Transform, (const Matrix3 &), void), asCALL_THISCALL);
    // void Frustum::Transform(const Matrix3x4 &transform) | File: ../Math/Frustum.h | Line: 80
    engine->RegisterObjectMethod("Frustum", "void Transform(const Matrix3x4&in)", asMETHODPR(Frustum, Transform, (const Matrix3x4 &), void), asCALL_THISCALL);
    // Frustum Frustum::Transformed(const Matrix3 &transform) const | File: ../Math/Frustum.h | Line: 172
    engine->RegisterObjectMethod("Frustum", "Frustum Transformed(const Matrix3&in) const", asMETHODPR(Frustum, Transformed, (const Matrix3 &) const, Frustum), asCALL_THISCALL);
    // Frustum Frustum::Transformed(const Matrix3x4 &transform) const | File: ../Math/Frustum.h | Line: 174
    engine->RegisterObjectMethod("Frustum", "Frustum Transformed(const Matrix3x4&in) const", asMETHODPR(Frustum, Transformed, (const Matrix3x4 &) const, Frustum), asCALL_THISCALL);
    // void Frustum::UpdatePlanes() | File: ../Math/Frustum.h | Line: 179
    engine->RegisterObjectMethod("Frustum", "void UpdatePlanes()", asMETHODPR(Frustum, UpdatePlanes, (), void), asCALL_THISCALL);

    // float Vector2::x_ | File: ../Math/Vector2.h | Line: 381
    engine->RegisterObjectProperty("Vector2", "float x", offsetof(Vector2, x_));
    // float Vector2::y_ | File: ../Math/Vector2.h | Line: 383
    engine->RegisterObjectProperty("Vector2", "float y", offsetof(Vector2, y_));
    // Vector2 Vector2::Abs() const | File: ../Math/Vector2.h | Line: 325
    engine->RegisterObjectMethod("Vector2", "Vector2 Abs() const", asMETHODPR(Vector2, Abs, () const, Vector2), asCALL_THISCALL);
    // float Vector2::AbsDotProduct(const Vector2 &rhs) const | File: ../Math/Vector2.h | Line: 316
    engine->RegisterObjectMethod("Vector2", "float AbsDotProduct(const Vector2&in) const", asMETHODPR(Vector2, AbsDotProduct, (const Vector2 &) const, float), asCALL_THISCALL);
    // float Vector2::Angle(const Vector2 &rhs) const | File: ../Math/Vector2.h | Line: 322
    engine->RegisterObjectMethod("Vector2", "float Angle(const Vector2&in) const", asMETHODPR(Vector2, Angle, (const Vector2 &) const, float), asCALL_THISCALL);
    // float Vector2::DotProduct(const Vector2 &rhs) const | File: ../Math/Vector2.h | Line: 313
    engine->RegisterObjectMethod("Vector2", "float DotProduct(const Vector2&in) const", asMETHODPR(Vector2, DotProduct, (const Vector2 &) const, float), asCALL_THISCALL);
    // bool Vector2::Equals(const Vector2 &rhs) const | File: ../Math/Vector2.h | Line: 331
    engine->RegisterObjectMethod("Vector2", "bool Equals(const Vector2&in) const", asMETHODPR(Vector2, Equals, (const Vector2 &) const, bool), asCALL_THISCALL);
    // bool Vector2::IsInf() const | File: ../Math/Vector2.h | Line: 337
    engine->RegisterObjectMethod("Vector2", "bool IsInf() const", asMETHODPR(Vector2, IsInf, () const, bool), asCALL_THISCALL);
    // bool Vector2::IsNaN() const | File: ../Math/Vector2.h | Line: 334
    engine->RegisterObjectMethod("Vector2", "bool IsNaN() const", asMETHODPR(Vector2, IsNaN, () const, bool), asCALL_THISCALL);
    // float Vector2::Length() const | File: ../Math/Vector2.h | Line: 306
    engine->RegisterObjectMethod("Vector2", "float get_length() const", asMETHODPR(Vector2, Length, () const, float), asCALL_THISCALL);
    // float Vector2::LengthSquared() const | File: ../Math/Vector2.h | Line: 310
    engine->RegisterObjectMethod("Vector2", "float get_lengthSquared() const", asMETHODPR(Vector2, LengthSquared, () const, float), asCALL_THISCALL);
    // Vector2 Vector2::Lerp(const Vector2 &rhs, float t) const | File: ../Math/Vector2.h | Line: 328
    engine->RegisterObjectMethod("Vector2", "Vector2 Lerp(const Vector2&in, float) const", asMETHODPR(Vector2, Lerp, (const Vector2 &, float) const, Vector2), asCALL_THISCALL);
    // void Vector2::Normalize() | File: ../Math/Vector2.h | Line: 293
    engine->RegisterObjectMethod("Vector2", "void Normalize()", asMETHODPR(Vector2, Normalize, (), void), asCALL_THISCALL);
    // Vector2 Vector2::Normalized() const | File: ../Math/Vector2.h | Line: 340
    engine->RegisterObjectMethod("Vector2", "Vector2 Normalized() const", asMETHODPR(Vector2, Normalized, () const, Vector2), asCALL_THISCALL);
    // Vector2 Vector2::NormalizedOrDefault(const Vector2 &defaultValue=Vector2::ZERO, float eps=M_LARGE_EPSILON) const | File: ../Math/Vector2.h | Line: 353
    engine->RegisterObjectMethod("Vector2", "Vector2 NormalizedOrDefault(const Vector2&in, float) const", asMETHODPR(Vector2, NormalizedOrDefault, (const Vector2 &, float) const, Vector2), asCALL_THISCALL);
    // Vector2 Vector2::operator*(float rhs) const | File: ../Math/Vector2.h | Line: 232
    engine->RegisterObjectMethod("Vector2", "Vector2 opMul(float) const", asMETHODPR(Vector2, operator*, (float) const, Vector2), asCALL_THISCALL);
    // Vector2 Vector2::operator*(const Vector2 &rhs) const | File: ../Math/Vector2.h | Line: 235
    engine->RegisterObjectMethod("Vector2", "Vector2 opMul(const Vector2&in) const", asMETHODPR(Vector2, operator*, (const Vector2 &) const, Vector2), asCALL_THISCALL);
    // Vector2& Vector2::operator*=(float rhs) | File: ../Math/Vector2.h | Line: 260
    engine->RegisterObjectMethod("Vector2", "Vector2& opMulAssign(float)", asMETHODPR(Vector2, operator*=, (float), Vector2 &), asCALL_THISCALL);
    // Vector2& Vector2::operator*=(const Vector2 &rhs) | File: ../Math/Vector2.h | Line: 268
    engine->RegisterObjectMethod("Vector2", "Vector2& opMulAssign(const Vector2&in)", asMETHODPR(Vector2, operator*=, (const Vector2 &), Vector2 &), asCALL_THISCALL);
    // Vector2 Vector2::operator+(const Vector2 &rhs) const | File: ../Math/Vector2.h | Line: 223
    engine->RegisterObjectMethod("Vector2", "Vector2 opAdd(const Vector2&in) const", asMETHODPR(Vector2, operator+, (const Vector2 &) const, Vector2), asCALL_THISCALL);
    // Vector2& Vector2::operator+=(const Vector2 &rhs) | File: ../Math/Vector2.h | Line: 244
    engine->RegisterObjectMethod("Vector2", "Vector2& opAddAssign(const Vector2&in)", asMETHODPR(Vector2, operator+=, (const Vector2 &), Vector2 &), asCALL_THISCALL);
    // Vector2 Vector2::operator-() const | File: ../Math/Vector2.h | Line: 226
    engine->RegisterObjectMethod("Vector2", "Vector2 opNeg() const", asMETHODPR(Vector2, operator-, () const, Vector2), asCALL_THISCALL);
    // Vector2 Vector2::operator-(const Vector2 &rhs) const | File: ../Math/Vector2.h | Line: 229
    engine->RegisterObjectMethod("Vector2", "Vector2 opSub(const Vector2&in) const", asMETHODPR(Vector2, operator-, (const Vector2 &) const, Vector2), asCALL_THISCALL);
    // Vector2& Vector2::operator-=(const Vector2 &rhs) | File: ../Math/Vector2.h | Line: 252
    engine->RegisterObjectMethod("Vector2", "Vector2& opSubAssign(const Vector2&in)", asMETHODPR(Vector2, operator-=, (const Vector2 &), Vector2 &), asCALL_THISCALL);
    // Vector2 Vector2::operator/(float rhs) const | File: ../Math/Vector2.h | Line: 238
    engine->RegisterObjectMethod("Vector2", "Vector2 opDiv(float) const", asMETHODPR(Vector2, operator/, (float) const, Vector2), asCALL_THISCALL);
    // Vector2 Vector2::operator/(const Vector2 &rhs) const | File: ../Math/Vector2.h | Line: 241
    engine->RegisterObjectMethod("Vector2", "Vector2 opDiv(const Vector2&in) const", asMETHODPR(Vector2, operator/, (const Vector2 &) const, Vector2), asCALL_THISCALL);
    // Vector2& Vector2::operator/=(float rhs) | File: ../Math/Vector2.h | Line: 276
    engine->RegisterObjectMethod("Vector2", "Vector2& opDivAssign(float)", asMETHODPR(Vector2, operator/=, (float), Vector2 &), asCALL_THISCALL);
    // Vector2& Vector2::operator/=(const Vector2 &rhs) | File: ../Math/Vector2.h | Line: 285
    engine->RegisterObjectMethod("Vector2", "Vector2& opDivAssign(const Vector2&in)", asMETHODPR(Vector2, operator/=, (const Vector2 &), Vector2 &), asCALL_THISCALL);
    // Vector2& Vector2::operator=(const Vector2 &rhs) noexcept=default | File: ../Math/Vector2.h | Line: 214
    engine->RegisterObjectMethod("Vector2", "Vector2& opAssign(const Vector2&in)", asMETHODPR(Vector2, operator=, (const Vector2 &), Vector2 &), asCALL_THISCALL);
    // bool Vector2::operator==(const Vector2 &rhs) const | File: ../Math/Vector2.h | Line: 217
    engine->RegisterObjectMethod("Vector2", "bool opEquals(const Vector2&in) const", asMETHODPR(Vector2, operator==, (const Vector2 &) const, bool), asCALL_THISCALL);
    // float Vector2::ProjectOntoAxis(const Vector2 &axis) const | File: ../Math/Vector2.h | Line: 319
    engine->RegisterObjectMethod("Vector2", "float ProjectOntoAxis(const Vector2&in) const", asMETHODPR(Vector2, ProjectOntoAxis, (const Vector2 &) const, float), asCALL_THISCALL);
    // Vector2 Vector2::ReNormalized(float minLength, float maxLength, const Vector2 &defaultValue=Vector2::ZERO, float eps=M_LARGE_EPSILON) const | File: ../Math/Vector2.h | Line: 362
    engine->RegisterObjectMethod("Vector2", "Vector2 ReNormalized(float, float, const Vector2&in, float) const", asMETHODPR(Vector2, ReNormalized, (float, float, const Vector2 &, float) const, Vector2), asCALL_THISCALL);
    // String Vector2::ToString() const | File: ../Math/Vector2.h | Line: 378
    engine->RegisterObjectMethod("Vector2", "String ToString() const", asMETHODPR(Vector2, ToString, () const, String), asCALL_THISCALL);
    // Vector2::Vector2() noexcept | File: ../Math/Vector2.h | Line: 182
    engine->RegisterObjectBehaviour("Vector2", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(Vector2_Vector2_182_5), asCALL_CDECL_OBJFIRST);
    // Vector2::Vector2(const Vector2 &vector) noexcept=default | File: ../Math/Vector2.h | Line: 189
    engine->RegisterObjectBehaviour("Vector2", asBEHAVE_CONSTRUCT, "void f(const Vector2&in)", asFUNCTION(Vector2_Vector2_189_5), asCALL_CDECL_OBJFIRST);
    // Vector2::Vector2(const IntVector2 &vector) noexcept | File: ../Math/Vector2.h | Line: 192
    engine->RegisterObjectBehaviour("Vector2", asBEHAVE_CONSTRUCT, "void f(const IntVector2&in)", asFUNCTION(Vector2_Vector2_192_14), asCALL_CDECL_OBJFIRST);
    // Vector2::Vector2(float x, float y) noexcept | File: ../Math/Vector2.h | Line: 199
    engine->RegisterObjectBehaviour("Vector2", asBEHAVE_CONSTRUCT, "void f(float, float)", asFUNCTION(Vector2_Vector2_199_5), asCALL_CDECL_OBJFIRST);

    // float Matrix2::m00_ | File: ../Math/Matrix2.h | Line: 234
    engine->RegisterObjectProperty("Matrix2", "float m00", offsetof(Matrix2, m00_));
    // float Matrix2::m01_ | File: ../Math/Matrix2.h | Line: 235
    engine->RegisterObjectProperty("Matrix2", "float m01", offsetof(Matrix2, m01_));
    // float Matrix2::m10_ | File: ../Math/Matrix2.h | Line: 236
    engine->RegisterObjectProperty("Matrix2", "float m10", offsetof(Matrix2, m10_));
    // float Matrix2::m11_ | File: ../Math/Matrix2.h | Line: 237
    engine->RegisterObjectProperty("Matrix2", "float m11", offsetof(Matrix2, m11_));
    // bool Matrix2::Equals(const Matrix2 &rhs) const | File: ../Math/Matrix2.h | Line: 186
    engine->RegisterObjectMethod("Matrix2", "bool Equals(const Matrix2&in) const", asMETHODPR(Matrix2, Equals, (const Matrix2 &) const, bool), asCALL_THISCALL);
    // Matrix2 Matrix2::Inverse() const | File: ../Math/Matrix2.h | Line: 201
    engine->RegisterObjectMethod("Matrix2", "Matrix2 Inverse() const", asMETHODPR(Matrix2, Inverse, () const, Matrix2), asCALL_THISCALL);
    // bool Matrix2::IsInf() const | File: ../Math/Matrix2.h | Line: 220
    engine->RegisterObjectMethod("Matrix2", "bool IsInf() const", asMETHODPR(Matrix2, IsInf, () const, bool), asCALL_THISCALL);
    // bool Matrix2::IsNaN() const | File: ../Math/Matrix2.h | Line: 208
    engine->RegisterObjectMethod("Matrix2", "bool IsNaN() const", asMETHODPR(Matrix2, IsNaN, () const, bool), asCALL_THISCALL);
    // Matrix2::Matrix2() noexcept | File: ../Math/Matrix2.h | Line: 35
    engine->RegisterObjectBehaviour("Matrix2", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(Matrix2_Matrix2_35_5), asCALL_CDECL_OBJFIRST);
    // Matrix2::Matrix2(const Matrix2 &matrix) noexcept=default | File: ../Math/Matrix2.h | Line: 44
    engine->RegisterObjectBehaviour("Matrix2", asBEHAVE_CONSTRUCT, "void f(const Matrix2&in)", asFUNCTION(Matrix2_Matrix2_44_5), asCALL_CDECL_OBJFIRST);
    // Matrix2::Matrix2(float v00, float v01, float v10, float v11) noexcept | File: ../Math/Matrix2.h | Line: 47
    engine->RegisterObjectBehaviour("Matrix2", asBEHAVE_CONSTRUCT, "void f(float, float, float, float)", asFUNCTION(Matrix2_Matrix2_47_5), asCALL_CDECL_OBJFIRST);
    // Vector2 Matrix2::operator*(const Vector2 &rhs) const | File: ../Math/Matrix2.h | Line: 88
    engine->RegisterObjectMethod("Matrix2", "Vector2 opMul(const Vector2&in) const", asMETHODPR(Matrix2, operator*, (const Vector2 &) const, Vector2), asCALL_THISCALL);
    // Matrix2 Matrix2::operator*(float rhs) const | File: ../Math/Matrix2.h | Line: 119
    engine->RegisterObjectMethod("Matrix2", "Matrix2 opMul(float) const", asMETHODPR(Matrix2, operator*, (float) const, Matrix2), asCALL_THISCALL);
    // Matrix2 Matrix2::operator*(const Matrix2 &rhs) const | File: ../Math/Matrix2.h | Line: 130
    engine->RegisterObjectMethod("Matrix2", "Matrix2 opMul(const Matrix2&in) const", asMETHODPR(Matrix2, operator*, (const Matrix2 &) const, Matrix2), asCALL_THISCALL);
    // Matrix2 Matrix2::operator+(const Matrix2 &rhs) const | File: ../Math/Matrix2.h | Line: 97
    engine->RegisterObjectMethod("Matrix2", "Matrix2 opAdd(const Matrix2&in) const", asMETHODPR(Matrix2, operator+, (const Matrix2 &) const, Matrix2), asCALL_THISCALL);
    // Matrix2 Matrix2::operator-(const Matrix2 &rhs) const | File: ../Math/Matrix2.h | Line: 108
    engine->RegisterObjectMethod("Matrix2", "Matrix2 opSub(const Matrix2&in) const", asMETHODPR(Matrix2, operator-, (const Matrix2 &) const, Matrix2), asCALL_THISCALL);
    // Matrix2& Matrix2::operator=(const Matrix2 &rhs) noexcept=default | File: ../Math/Matrix2.h | Line: 67
    engine->RegisterObjectMethod("Matrix2", "Matrix2& opAssign(const Matrix2&in)", asMETHODPR(Matrix2, operator=, (const Matrix2 &), Matrix2 &), asCALL_THISCALL);
    // bool Matrix2::operator==(const Matrix2 &rhs) const | File: ../Math/Matrix2.h | Line: 70
    engine->RegisterObjectMethod("Matrix2", "bool opEquals(const Matrix2&in) const", asMETHODPR(Matrix2, operator==, (const Matrix2 &) const, bool), asCALL_THISCALL);
    // Vector2 Matrix2::Scale() const | File: ../Math/Matrix2.h | Line: 155
    engine->RegisterObjectMethod("Matrix2", "Vector2 Scale() const", asMETHODPR(Matrix2, Scale, () const, Vector2), asCALL_THISCALL);
    // Matrix2 Matrix2::Scaled(const Vector2 &scale) const | File: ../Math/Matrix2.h | Line: 175
    engine->RegisterObjectMethod("Matrix2", "Matrix2 Scaled(const Vector2&in) const", asMETHODPR(Matrix2, Scaled, (const Vector2 &) const, Matrix2), asCALL_THISCALL);
    // void Matrix2::SetScale(const Vector2 &scale) | File: ../Math/Matrix2.h | Line: 141
    engine->RegisterObjectMethod("Matrix2", "void SetScale(const Vector2&in)", asMETHODPR(Matrix2, SetScale, (const Vector2 &), void), asCALL_THISCALL);
    // void Matrix2::SetScale(float scale) | File: ../Math/Matrix2.h | Line: 148
    engine->RegisterObjectMethod("Matrix2", "void SetScale(float)", asMETHODPR(Matrix2, SetScale, (float), void), asCALL_THISCALL);
    // String Matrix2::ToString() const | File: ../Math/Matrix2.h | Line: 232
    engine->RegisterObjectMethod("Matrix2", "String ToString() const", asMETHODPR(Matrix2, ToString, () const, String), asCALL_THISCALL);
    // Matrix2 Matrix2::Transpose() const | File: ../Math/Matrix2.h | Line: 164
    engine->RegisterObjectMethod("Matrix2", "Matrix2 Transpose() const", asMETHODPR(Matrix2, Transpose, () const, Matrix2), asCALL_THISCALL);

    // float Matrix3::m00_ | File: ../Math/Matrix3.h | Line: 303
    engine->RegisterObjectProperty("Matrix3", "float m00", offsetof(Matrix3, m00_));
    // float Matrix3::m01_ | File: ../Math/Matrix3.h | Line: 304
    engine->RegisterObjectProperty("Matrix3", "float m01", offsetof(Matrix3, m01_));
    // float Matrix3::m02_ | File: ../Math/Matrix3.h | Line: 305
    engine->RegisterObjectProperty("Matrix3", "float m02", offsetof(Matrix3, m02_));
    // float Matrix3::m10_ | File: ../Math/Matrix3.h | Line: 306
    engine->RegisterObjectProperty("Matrix3", "float m10", offsetof(Matrix3, m10_));
    // float Matrix3::m11_ | File: ../Math/Matrix3.h | Line: 307
    engine->RegisterObjectProperty("Matrix3", "float m11", offsetof(Matrix3, m11_));
    // float Matrix3::m12_ | File: ../Math/Matrix3.h | Line: 308
    engine->RegisterObjectProperty("Matrix3", "float m12", offsetof(Matrix3, m12_));
    // float Matrix3::m20_ | File: ../Math/Matrix3.h | Line: 309
    engine->RegisterObjectProperty("Matrix3", "float m20", offsetof(Matrix3, m20_));
    // float Matrix3::m21_ | File: ../Math/Matrix3.h | Line: 310
    engine->RegisterObjectProperty("Matrix3", "float m21", offsetof(Matrix3, m21_));
    // float Matrix3::m22_ | File: ../Math/Matrix3.h | Line: 311
    engine->RegisterObjectProperty("Matrix3", "float m22", offsetof(Matrix3, m22_));
    // Vector3 Matrix3::Column(unsigned j) const | File: ../Math/Matrix3.h | Line: 274
    engine->RegisterObjectMethod("Matrix3", "Vector3 Column(uint) const", asMETHODPR(Matrix3, Column, (unsigned) const, Vector3), asCALL_THISCALL);
    // float Matrix3::Element(unsigned i, unsigned j) const | File: ../Math/Matrix3.h | Line: 268
    engine->RegisterObjectMethod("Matrix3", "float Element(uint, uint) const", asMETHODPR(Matrix3, Element, (unsigned, unsigned) const, float), asCALL_THISCALL);
    // bool Matrix3::Equals(const Matrix3 &rhs) const | File: ../Math/Matrix3.h | Line: 246
    engine->RegisterObjectMethod("Matrix3", "bool Equals(const Matrix3&in) const", asMETHODPR(Matrix3, Equals, (const Matrix3 &) const, bool), asCALL_THISCALL);
    // Matrix3 Matrix3::Inverse() const | File: ../Math/Matrix3.h | Line: 261
    engine->RegisterObjectMethod("Matrix3", "Matrix3 Inverse() const", asMETHODPR(Matrix3, Inverse, () const, Matrix3), asCALL_THISCALL);
    // bool Matrix3::IsInf() const | File: ../Math/Matrix3.h | Line: 289
    engine->RegisterObjectMethod("Matrix3", "bool IsInf() const", asMETHODPR(Matrix3, IsInf, () const, bool), asCALL_THISCALL);
    // bool Matrix3::IsNaN() const | File: ../Math/Matrix3.h | Line: 277
    engine->RegisterObjectMethod("Matrix3", "bool IsNaN() const", asMETHODPR(Matrix3, IsNaN, () const, bool), asCALL_THISCALL);
    // Matrix3::Matrix3() noexcept | File: ../Math/Matrix3.h | Line: 35
    engine->RegisterObjectBehaviour("Matrix3", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(Matrix3_Matrix3_35_5), asCALL_CDECL_OBJFIRST);
    // Matrix3::Matrix3(const Matrix3 &matrix) noexcept=default | File: ../Math/Matrix3.h | Line: 49
    engine->RegisterObjectBehaviour("Matrix3", asBEHAVE_CONSTRUCT, "void f(const Matrix3&in)", asFUNCTION(Matrix3_Matrix3_49_5), asCALL_CDECL_OBJFIRST);
    // Matrix3::Matrix3(float v00, float v01, float v02, float v10, float v11, float v12, float v20, float v21, float v22) noexcept | File: ../Math/Matrix3.h | Line: 52
    engine->RegisterObjectBehaviour("Matrix3", asBEHAVE_CONSTRUCT, "void f(float, float, float, float, float, float, float, float, float)", asFUNCTION(Matrix3_Matrix3_52_5), asCALL_CDECL_OBJFIRST);
    // Vector3 Matrix3::operator*(const Vector3 &rhs) const | File: ../Math/Matrix3.h | Line: 104
    engine->RegisterObjectMethod("Matrix3", "Vector3 opMul(const Vector3&in) const", asMETHODPR(Matrix3, operator*, (const Vector3 &) const, Vector3), asCALL_THISCALL);
    // Matrix3 Matrix3::operator*(float rhs) const | File: ../Math/Matrix3.h | Line: 146
    engine->RegisterObjectMethod("Matrix3", "Matrix3 opMul(float) const", asMETHODPR(Matrix3, operator*, (float) const, Matrix3), asCALL_THISCALL);
    // Matrix3 Matrix3::operator*(const Matrix3 &rhs) const | File: ../Math/Matrix3.h | Line: 162
    engine->RegisterObjectMethod("Matrix3", "Matrix3 opMul(const Matrix3&in) const", asMETHODPR(Matrix3, operator*, (const Matrix3 &) const, Matrix3), asCALL_THISCALL);
    // Matrix3 Matrix3::operator+(const Matrix3 &rhs) const | File: ../Math/Matrix3.h | Line: 114
    engine->RegisterObjectMethod("Matrix3", "Matrix3 opAdd(const Matrix3&in) const", asMETHODPR(Matrix3, operator+, (const Matrix3 &) const, Matrix3), asCALL_THISCALL);
    // Matrix3 Matrix3::operator-(const Matrix3 &rhs) const | File: ../Math/Matrix3.h | Line: 130
    engine->RegisterObjectMethod("Matrix3", "Matrix3 opSub(const Matrix3&in) const", asMETHODPR(Matrix3, operator-, (const Matrix3 &) const, Matrix3), asCALL_THISCALL);
    // Matrix3& Matrix3::operator=(const Matrix3 &rhs) noexcept=default | File: ../Math/Matrix3.h | Line: 83
    engine->RegisterObjectMethod("Matrix3", "Matrix3& opAssign(const Matrix3&in)", asMETHODPR(Matrix3, operator=, (const Matrix3 &), Matrix3 &), asCALL_THISCALL);
    // bool Matrix3::operator==(const Matrix3 &rhs) const | File: ../Math/Matrix3.h | Line: 86
    engine->RegisterObjectMethod("Matrix3", "bool opEquals(const Matrix3&in) const", asMETHODPR(Matrix3, operator==, (const Matrix3 &) const, bool), asCALL_THISCALL);
    // Vector3 Matrix3::Row(unsigned i) const | File: ../Math/Matrix3.h | Line: 271
    engine->RegisterObjectMethod("Matrix3", "Vector3 Row(uint) const", asMETHODPR(Matrix3, Row, (unsigned) const, Vector3), asCALL_THISCALL);
    // Vector3 Matrix3::Scale() const | File: ../Math/Matrix3.h | Line: 194
    engine->RegisterObjectMethod("Matrix3", "Vector3 Scale() const", asMETHODPR(Matrix3, Scale, () const, Vector3), asCALL_THISCALL);
    // Matrix3 Matrix3::Scaled(const Vector3 &scale) const | File: ../Math/Matrix3.h | Line: 230
    engine->RegisterObjectMethod("Matrix3", "Matrix3 Scaled(const Vector3&in) const", asMETHODPR(Matrix3, Scaled, (const Vector3 &) const, Matrix3), asCALL_THISCALL);
    // void Matrix3::SetScale(const Vector3 &scale) | File: ../Math/Matrix3.h | Line: 178
    engine->RegisterObjectMethod("Matrix3", "void SetScale(const Vector3&in)", asMETHODPR(Matrix3, SetScale, (const Vector3 &), void), asCALL_THISCALL);
    // void Matrix3::SetScale(float scale) | File: ../Math/Matrix3.h | Line: 186
    engine->RegisterObjectMethod("Matrix3", "void SetScale(float)", asMETHODPR(Matrix3, SetScale, (float), void), asCALL_THISCALL);
    // Vector3 Matrix3::SignedScale(const Matrix3 &rotation) const | File: ../Math/Matrix3.h | Line: 204
    engine->RegisterObjectMethod("Matrix3", "Vector3 SignedScale(const Matrix3&in) const", asMETHODPR(Matrix3, SignedScale, (const Matrix3 &) const, Vector3), asCALL_THISCALL);
    // String Matrix3::ToString() const | File: ../Math/Matrix3.h | Line: 301
    engine->RegisterObjectMethod("Matrix3", "String ToString() const", asMETHODPR(Matrix3, ToString, () const, String), asCALL_THISCALL);
    // Matrix3 Matrix3::Transpose() const | File: ../Math/Matrix3.h | Line: 214
    engine->RegisterObjectMethod("Matrix3", "Matrix3 Transpose() const", asMETHODPR(Matrix3, Transpose, () const, Matrix3), asCALL_THISCALL);

    // float Matrix3x4::m00_ | File: ../Math/Matrix3x4.h | Line: 697
    engine->RegisterObjectProperty("Matrix3x4", "float m00", offsetof(Matrix3x4, m00_));
    // float Matrix3x4::m01_ | File: ../Math/Matrix3x4.h | Line: 698
    engine->RegisterObjectProperty("Matrix3x4", "float m01", offsetof(Matrix3x4, m01_));
    // float Matrix3x4::m02_ | File: ../Math/Matrix3x4.h | Line: 699
    engine->RegisterObjectProperty("Matrix3x4", "float m02", offsetof(Matrix3x4, m02_));
    // float Matrix3x4::m03_ | File: ../Math/Matrix3x4.h | Line: 700
    engine->RegisterObjectProperty("Matrix3x4", "float m03", offsetof(Matrix3x4, m03_));
    // float Matrix3x4::m10_ | File: ../Math/Matrix3x4.h | Line: 701
    engine->RegisterObjectProperty("Matrix3x4", "float m10", offsetof(Matrix3x4, m10_));
    // float Matrix3x4::m11_ | File: ../Math/Matrix3x4.h | Line: 702
    engine->RegisterObjectProperty("Matrix3x4", "float m11", offsetof(Matrix3x4, m11_));
    // float Matrix3x4::m12_ | File: ../Math/Matrix3x4.h | Line: 703
    engine->RegisterObjectProperty("Matrix3x4", "float m12", offsetof(Matrix3x4, m12_));
    // float Matrix3x4::m13_ | File: ../Math/Matrix3x4.h | Line: 704
    engine->RegisterObjectProperty("Matrix3x4", "float m13", offsetof(Matrix3x4, m13_));
    // float Matrix3x4::m20_ | File: ../Math/Matrix3x4.h | Line: 705
    engine->RegisterObjectProperty("Matrix3x4", "float m20", offsetof(Matrix3x4, m20_));
    // float Matrix3x4::m21_ | File: ../Math/Matrix3x4.h | Line: 706
    engine->RegisterObjectProperty("Matrix3x4", "float m21", offsetof(Matrix3x4, m21_));
    // float Matrix3x4::m22_ | File: ../Math/Matrix3x4.h | Line: 707
    engine->RegisterObjectProperty("Matrix3x4", "float m22", offsetof(Matrix3x4, m22_));
    // float Matrix3x4::m23_ | File: ../Math/Matrix3x4.h | Line: 708
    engine->RegisterObjectProperty("Matrix3x4", "float m23", offsetof(Matrix3x4, m23_));
    // Vector3 Matrix3x4::Column(unsigned j) const | File: ../Math/Matrix3x4.h | Line: 668
    engine->RegisterObjectMethod("Matrix3x4", "Vector3 Column(uint) const", asMETHODPR(Matrix3x4, Column, (unsigned) const, Vector3), asCALL_THISCALL);
    // void Matrix3x4::Decompose(Vector3 &translation, Quaternion &rotation, Vector3 &scale) const | File: ../Math/Matrix3x4.h | Line: 652
    engine->RegisterObjectMethod("Matrix3x4", "void Decompose(Vector3&, Quaternion&, Vector3&) const", asMETHODPR(Matrix3x4, Decompose, (Vector3 &, Quaternion &, Vector3 &) const, void), asCALL_THISCALL);
    // float Matrix3x4::Element(unsigned i, unsigned j) const | File: ../Math/Matrix3x4.h | Line: 662
    engine->RegisterObjectMethod("Matrix3x4", "float Element(uint, uint) const", asMETHODPR(Matrix3x4, Element, (unsigned, unsigned) const, float), asCALL_THISCALL);
    // bool Matrix3x4::Equals(const Matrix3x4 &rhs) const | File: ../Math/Matrix3x4.h | Line: 637
    engine->RegisterObjectMethod("Matrix3x4", "bool Equals(const Matrix3x4&in) const", asMETHODPR(Matrix3x4, Equals, (const Matrix3x4 &) const, bool), asCALL_THISCALL);
    // Matrix3x4 Matrix3x4::Inverse() const | File: ../Math/Matrix3x4.h | Line: 655
    engine->RegisterObjectMethod("Matrix3x4", "Matrix3x4 Inverse() const", asMETHODPR(Matrix3x4, Inverse, () const, Matrix3x4), asCALL_THISCALL);
    // bool Matrix3x4::IsInf() const | File: ../Math/Matrix3x4.h | Line: 683
    engine->RegisterObjectMethod("Matrix3x4", "bool IsInf() const", asMETHODPR(Matrix3x4, IsInf, () const, bool), asCALL_THISCALL);
    // bool Matrix3x4::IsNaN() const | File: ../Math/Matrix3x4.h | Line: 671
    engine->RegisterObjectMethod("Matrix3x4", "bool IsNaN() const", asMETHODPR(Matrix3x4, IsNaN, () const, bool), asCALL_THISCALL);
    // Matrix3x4::Matrix3x4() noexcept | File: ../Math/Matrix3x4.h | Line: 39
    engine->RegisterObjectBehaviour("Matrix3x4", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(Matrix3x4_Matrix3x4_39_5), asCALL_CDECL_OBJFIRST);
    // Matrix3x4::Matrix3x4(const Matrix3x4 &matrix) noexcept=default | File: ../Math/Matrix3x4.h | Line: 63
    engine->RegisterObjectBehaviour("Matrix3x4", asBEHAVE_CONSTRUCT, "void f(const Matrix3x4&in)", asFUNCTION(Matrix3x4_Matrix3x4_63_5), asCALL_CDECL_OBJFIRST);
    // Matrix3x4::Matrix3x4(const Matrix3 &matrix) noexcept | File: ../Math/Matrix3x4.h | Line: 66
    engine->RegisterObjectBehaviour("Matrix3x4", asBEHAVE_CONSTRUCT, "void f(const Matrix3&in)", asFUNCTION(Matrix3x4_Matrix3x4_66_14), asCALL_CDECL_OBJFIRST);
    // Matrix3x4::Matrix3x4(const Matrix4 &matrix) noexcept | File: ../Math/Matrix3x4.h | Line: 83
    engine->RegisterObjectBehaviour("Matrix3x4", asBEHAVE_CONSTRUCT, "void f(const Matrix4&in)", asFUNCTION(Matrix3x4_Matrix3x4_83_14), asCALL_CDECL_OBJFIRST);
    // Matrix3x4::Matrix3x4(float v00, float v01, float v02, float v03, float v10, float v11, float v12, float v13, float v20, float v21, float v22, float v23) noexcept | File: ../Math/Matrix3x4.h | Line: 107
    engine->RegisterObjectBehaviour("Matrix3x4", asBEHAVE_CONSTRUCT, "void f(float, float, float, float, float, float, float, float, float, float, float, float)", asFUNCTION(Matrix3x4_Matrix3x4_107_5), asCALL_CDECL_OBJFIRST);
    // Matrix3x4::Matrix3x4(const Vector3 &translation, const Quaternion &rotation, float scale) noexcept | File: ../Math/Matrix3x4.h | Line: 151
    engine->RegisterObjectBehaviour("Matrix3x4", asBEHAVE_CONSTRUCT, "void f(const Vector3&in, const Quaternion&in, float)", asFUNCTION(Matrix3x4_Matrix3x4_151_5), asCALL_CDECL_OBJFIRST);
    // Matrix3x4::Matrix3x4(const Vector3 &translation, const Quaternion &rotation, const Vector3 &scale) noexcept | File: ../Math/Matrix3x4.h | Line: 165
    engine->RegisterObjectBehaviour("Matrix3x4", asBEHAVE_CONSTRUCT, "void f(const Vector3&in, const Quaternion&in, const Vector3&in)", asFUNCTION(Matrix3x4_Matrix3x4_165_5), asCALL_CDECL_OBJFIRST);
    // Vector3 Matrix3x4::operator*(const Vector3 &rhs) const | File: ../Math/Matrix3x4.h | Line: 255
    engine->RegisterObjectMethod("Matrix3x4", "Vector3 opMul(const Vector3&in) const", asMETHODPR(Matrix3x4, operator*, (const Vector3 &) const, Vector3), asCALL_THISCALL);
    // Vector3 Matrix3x4::operator*(const Vector4 &rhs) const | File: ../Math/Matrix3x4.h | Line: 285
    engine->RegisterObjectMethod("Matrix3x4", "Vector3 opMul(const Vector4&in) const", asMETHODPR(Matrix3x4, operator*, (const Vector4 &) const, Vector3), asCALL_THISCALL);
    // Matrix3x4 Matrix3x4::operator*(float rhs) const | File: ../Math/Matrix3x4.h | Line: 369
    engine->RegisterObjectMethod("Matrix3x4", "Matrix3x4 opMul(float) const", asMETHODPR(Matrix3x4, operator*, (float) const, Matrix3x4), asCALL_THISCALL);
    // Matrix3x4 Matrix3x4::operator*(const Matrix3x4 &rhs) const | File: ../Math/Matrix3x4.h | Line: 397
    engine->RegisterObjectMethod("Matrix3x4", "Matrix3x4 opMul(const Matrix3x4&in) const", asMETHODPR(Matrix3x4, operator*, (const Matrix3x4 &) const, Matrix3x4), asCALL_THISCALL);
    // Matrix4 Matrix3x4::operator*(const Matrix4 &rhs) const | File: ../Math/Matrix3x4.h | Line: 448
    engine->RegisterObjectMethod("Matrix3x4", "Matrix4 opMul(const Matrix4&in) const", asMETHODPR(Matrix3x4, operator*, (const Matrix4 &) const, Matrix4), asCALL_THISCALL);
    // Matrix3x4 Matrix3x4::operator+(const Matrix3x4 &rhs) const | File: ../Math/Matrix3x4.h | Line: 315
    engine->RegisterObjectMethod("Matrix3x4", "Matrix3x4 opAdd(const Matrix3x4&in) const", asMETHODPR(Matrix3x4, operator+, (const Matrix3x4 &) const, Matrix3x4), asCALL_THISCALL);
    // Matrix3x4 Matrix3x4::operator-(const Matrix3x4 &rhs) const | File: ../Math/Matrix3x4.h | Line: 342
    engine->RegisterObjectMethod("Matrix3x4", "Matrix3x4 opSub(const Matrix3x4&in) const", asMETHODPR(Matrix3x4, operator-, (const Matrix3x4 &) const, Matrix3x4), asCALL_THISCALL);
    // Matrix3x4& Matrix3x4::operator=(const Matrix3x4 &rhs) noexcept=default | File: ../Math/Matrix3x4.h | Line: 179
    engine->RegisterObjectMethod("Matrix3x4", "Matrix3x4& opAssign(const Matrix3x4&in)", asMETHODPR(Matrix3x4, operator=, (const Matrix3x4 &), Matrix3x4 &), asCALL_THISCALL);
    // Matrix3x4& Matrix3x4::operator=(const Matrix3 &rhs) noexcept | File: ../Math/Matrix3x4.h | Line: 182
    engine->RegisterObjectMethod("Matrix3x4", "Matrix3x4& opAssign(const Matrix3&in)", asMETHODPR(Matrix3x4, operator=, (const Matrix3 &), Matrix3x4 &), asCALL_THISCALL);
    // Matrix3x4& Matrix3x4::operator=(const Matrix4 &rhs) noexcept | File: ../Math/Matrix3x4.h | Line: 200
    engine->RegisterObjectMethod("Matrix3x4", "Matrix3x4& opAssign(const Matrix4&in)", asMETHODPR(Matrix3x4, operator=, (const Matrix4 &), Matrix3x4 &), asCALL_THISCALL);
    // bool Matrix3x4::operator==(const Matrix3x4 &rhs) const | File: ../Math/Matrix3x4.h | Line: 224
    engine->RegisterObjectMethod("Matrix3x4", "bool opEquals(const Matrix3x4&in) const", asMETHODPR(Matrix3x4, operator==, (const Matrix3x4 &) const, bool), asCALL_THISCALL);
    // Quaternion Matrix3x4::Rotation() const | File: ../Math/Matrix3x4.h | Line: 614
    engine->RegisterObjectMethod("Matrix3x4", "Quaternion Rotation() const", asMETHODPR(Matrix3x4, Rotation, () const, Quaternion), asCALL_THISCALL);
    // Matrix3 Matrix3x4::RotationMatrix() const | File: ../Math/Matrix3x4.h | Line: 592
    engine->RegisterObjectMethod("Matrix3x4", "Matrix3 RotationMatrix() const", asMETHODPR(Matrix3x4, RotationMatrix, () const, Matrix3), asCALL_THISCALL);
    // Vector4 Matrix3x4::Row(unsigned i) const | File: ../Math/Matrix3x4.h | Line: 665
    engine->RegisterObjectMethod("Matrix3x4", "Vector4 Row(uint) const", asMETHODPR(Matrix3x4, Row, (unsigned) const, Vector4), asCALL_THISCALL);
    // Vector3 Matrix3x4::Scale() const | File: ../Math/Matrix3x4.h | Line: 617
    engine->RegisterObjectMethod("Matrix3x4", "Vector3 Scale() const", asMETHODPR(Matrix3x4, Scale, () const, Vector3), asCALL_THISCALL);
    // void Matrix3x4::SetRotation(const Matrix3 &rotation) | File: ../Math/Matrix3x4.h | Line: 513
    engine->RegisterObjectMethod("Matrix3x4", "void SetRotation(const Matrix3&in)", asMETHODPR(Matrix3x4, SetRotation, (const Matrix3 &), void), asCALL_THISCALL);
    // void Matrix3x4::SetScale(const Vector3 &scale) | File: ../Math/Matrix3x4.h | Line: 527
    engine->RegisterObjectMethod("Matrix3x4", "void SetScale(const Vector3&in)", asMETHODPR(Matrix3x4, SetScale, (const Vector3 &), void), asCALL_THISCALL);
    // void Matrix3x4::SetScale(float scale) | File: ../Math/Matrix3x4.h | Line: 535
    engine->RegisterObjectMethod("Matrix3x4", "void SetScale(float)", asMETHODPR(Matrix3x4, SetScale, (float), void), asCALL_THISCALL);
    // void Matrix3x4::SetTranslation(const Vector3 &translation) | File: ../Math/Matrix3x4.h | Line: 505
    engine->RegisterObjectMethod("Matrix3x4", "void SetTranslation(const Vector3&in)", asMETHODPR(Matrix3x4, SetTranslation, (const Vector3 &), void), asCALL_THISCALL);
    // Vector3 Matrix3x4::SignedScale(const Matrix3 &rotation) const | File: ../Math/Matrix3x4.h | Line: 627
    engine->RegisterObjectMethod("Matrix3x4", "Vector3 SignedScale(const Matrix3&in) const", asMETHODPR(Matrix3x4, SignedScale, (const Matrix3 &) const, Vector3), asCALL_THISCALL);
    // Matrix3 Matrix3x4::ToMatrix3() const | File: ../Math/Matrix3x4.h | Line: 543
    engine->RegisterObjectMethod("Matrix3x4", "Matrix3 ToMatrix3() const", asMETHODPR(Matrix3x4, ToMatrix3, () const, Matrix3), asCALL_THISCALL);
    // Matrix4 Matrix3x4::ToMatrix4() const | File: ../Math/Matrix3x4.h | Line: 559
    engine->RegisterObjectMethod("Matrix3x4", "Matrix4 ToMatrix4() const", asMETHODPR(Matrix3x4, ToMatrix4, () const, Matrix4), asCALL_THISCALL);
    // String Matrix3x4::ToString() const | File: ../Math/Matrix3x4.h | Line: 695
    engine->RegisterObjectMethod("Matrix3x4", "String ToString() const", asMETHODPR(Matrix3x4, ToString, () const, String), asCALL_THISCALL);
    // Vector3 Matrix3x4::Translation() const | File: ../Math/Matrix3x4.h | Line: 604
    engine->RegisterObjectMethod("Matrix3x4", "Vector3 Translation() const", asMETHODPR(Matrix3x4, Translation, () const, Vector3), asCALL_THISCALL);

    // float Matrix4::m00_ | File: ../Math/Matrix4.h | Line: 679
    engine->RegisterObjectProperty("Matrix4", "float m00", offsetof(Matrix4, m00_));
    // float Matrix4::m01_ | File: ../Math/Matrix4.h | Line: 680
    engine->RegisterObjectProperty("Matrix4", "float m01", offsetof(Matrix4, m01_));
    // float Matrix4::m02_ | File: ../Math/Matrix4.h | Line: 681
    engine->RegisterObjectProperty("Matrix4", "float m02", offsetof(Matrix4, m02_));
    // float Matrix4::m03_ | File: ../Math/Matrix4.h | Line: 682
    engine->RegisterObjectProperty("Matrix4", "float m03", offsetof(Matrix4, m03_));
    // float Matrix4::m10_ | File: ../Math/Matrix4.h | Line: 683
    engine->RegisterObjectProperty("Matrix4", "float m10", offsetof(Matrix4, m10_));
    // float Matrix4::m11_ | File: ../Math/Matrix4.h | Line: 684
    engine->RegisterObjectProperty("Matrix4", "float m11", offsetof(Matrix4, m11_));
    // float Matrix4::m12_ | File: ../Math/Matrix4.h | Line: 685
    engine->RegisterObjectProperty("Matrix4", "float m12", offsetof(Matrix4, m12_));
    // float Matrix4::m13_ | File: ../Math/Matrix4.h | Line: 686
    engine->RegisterObjectProperty("Matrix4", "float m13", offsetof(Matrix4, m13_));
    // float Matrix4::m20_ | File: ../Math/Matrix4.h | Line: 687
    engine->RegisterObjectProperty("Matrix4", "float m20", offsetof(Matrix4, m20_));
    // float Matrix4::m21_ | File: ../Math/Matrix4.h | Line: 688
    engine->RegisterObjectProperty("Matrix4", "float m21", offsetof(Matrix4, m21_));
    // float Matrix4::m22_ | File: ../Math/Matrix4.h | Line: 689
    engine->RegisterObjectProperty("Matrix4", "float m22", offsetof(Matrix4, m22_));
    // float Matrix4::m23_ | File: ../Math/Matrix4.h | Line: 690
    engine->RegisterObjectProperty("Matrix4", "float m23", offsetof(Matrix4, m23_));
    // float Matrix4::m30_ | File: ../Math/Matrix4.h | Line: 691
    engine->RegisterObjectProperty("Matrix4", "float m30", offsetof(Matrix4, m30_));
    // float Matrix4::m31_ | File: ../Math/Matrix4.h | Line: 692
    engine->RegisterObjectProperty("Matrix4", "float m31", offsetof(Matrix4, m31_));
    // float Matrix4::m32_ | File: ../Math/Matrix4.h | Line: 693
    engine->RegisterObjectProperty("Matrix4", "float m32", offsetof(Matrix4, m32_));
    // float Matrix4::m33_ | File: ../Math/Matrix4.h | Line: 694
    engine->RegisterObjectProperty("Matrix4", "float m33", offsetof(Matrix4, m33_));
    // Vector4 Matrix4::Column(unsigned j) const | File: ../Math/Matrix4.h | Line: 650
    engine->RegisterObjectMethod("Matrix4", "Vector4 Column(uint) const", asMETHODPR(Matrix4, Column, (unsigned) const, Vector4), asCALL_THISCALL);
    // void Matrix4::Decompose(Vector3 &translation, Quaternion &rotation, Vector3 &scale) const | File: ../Math/Matrix4.h | Line: 634
    engine->RegisterObjectMethod("Matrix4", "void Decompose(Vector3&, Quaternion&, Vector3&) const", asMETHODPR(Matrix4, Decompose, (Vector3 &, Quaternion &, Vector3 &) const, void), asCALL_THISCALL);
    // float Matrix4::Element(unsigned i, unsigned j) const | File: ../Math/Matrix4.h | Line: 644
    engine->RegisterObjectMethod("Matrix4", "float Element(uint, uint) const", asMETHODPR(Matrix4, Element, (unsigned, unsigned) const, float), asCALL_THISCALL);
    // bool Matrix4::Equals(const Matrix4 &rhs) const | File: ../Math/Matrix4.h | Line: 619
    engine->RegisterObjectMethod("Matrix4", "bool Equals(const Matrix4&in) const", asMETHODPR(Matrix4, Equals, (const Matrix4 &) const, bool), asCALL_THISCALL);
    // Matrix4 Matrix4::Inverse() const | File: ../Math/Matrix4.h | Line: 637
    engine->RegisterObjectMethod("Matrix4", "Matrix4 Inverse() const", asMETHODPR(Matrix4, Inverse, () const, Matrix4), asCALL_THISCALL);
    // bool Matrix4::IsInf() const | File: ../Math/Matrix4.h | Line: 665
    engine->RegisterObjectMethod("Matrix4", "bool IsInf() const", asMETHODPR(Matrix4, IsInf, () const, bool), asCALL_THISCALL);
    // bool Matrix4::IsNaN() const | File: ../Math/Matrix4.h | Line: 653
    engine->RegisterObjectMethod("Matrix4", "bool IsNaN() const", asMETHODPR(Matrix4, IsNaN, () const, bool), asCALL_THISCALL);
    // Matrix4::Matrix4() noexcept | File: ../Math/Matrix4.h | Line: 42
    engine->RegisterObjectBehaviour("Matrix4", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(Matrix4_Matrix4_42_5), asCALL_CDECL_OBJFIRST);
    // Matrix4::Matrix4(const Matrix4 &matrix) noexcept | File: ../Math/Matrix4.h | Line: 71
    engine->RegisterObjectBehaviour("Matrix4", asBEHAVE_CONSTRUCT, "void f(const Matrix4&in)", asFUNCTION(Matrix4_Matrix4_71_5), asCALL_CDECL_OBJFIRST);
    // Matrix4::Matrix4(const Matrix3 &matrix) noexcept | File: ../Math/Matrix4.h | Line: 100
    engine->RegisterObjectBehaviour("Matrix4", asBEHAVE_CONSTRUCT, "void f(const Matrix3&in)", asFUNCTION(Matrix4_Matrix4_100_14), asCALL_CDECL_OBJFIRST);
    // Matrix4::Matrix4(float v00, float v01, float v02, float v03, float v10, float v11, float v12, float v13, float v20, float v21, float v22, float v23, float v30, float v31, float v32, float v33) noexcept | File: ../Math/Matrix4.h | Line: 121
    engine->RegisterObjectBehaviour("Matrix4", asBEHAVE_CONSTRUCT, "void f(float, float, float, float, float, float, float, float, float, float, float, float, float, float, float, float)", asFUNCTION(Matrix4_Matrix4_121_5), asCALL_CDECL_OBJFIRST);
    // Vector3 Matrix4::operator*(const Vector3 &rhs) const | File: ../Math/Matrix4.h | Line: 259
    engine->RegisterObjectMethod("Matrix4", "Vector3 opMul(const Vector3&in) const", asMETHODPR(Matrix4, operator*, (const Vector3 &) const, Vector3), asCALL_THISCALL);
    // Vector4 Matrix4::operator*(const Vector4 &rhs) const | File: ../Math/Matrix4.h | Line: 291
    engine->RegisterObjectMethod("Matrix4", "Vector4 opMul(const Vector4&in) const", asMETHODPR(Matrix4, operator*, (const Vector4 &) const, Vector4), asCALL_THISCALL);
    // Matrix4 Matrix4::operator*(float rhs) const | File: ../Math/Matrix4.h | Line: 385
    engine->RegisterObjectMethod("Matrix4", "Matrix4 opMul(float) const", asMETHODPR(Matrix4, operator*, (float) const, Matrix4), asCALL_THISCALL);
    // Matrix4 Matrix4::operator*(const Matrix4 &rhs) const | File: ../Math/Matrix4.h | Line: 418
    engine->RegisterObjectMethod("Matrix4", "Matrix4 opMul(const Matrix4&in) const", asMETHODPR(Matrix4, operator*, (const Matrix4 &) const, Matrix4), asCALL_THISCALL);
    // Matrix4 Matrix4::operator*(const Matrix3x4 &rhs) const | File: ../Math/Matrix4.h | Line: 480
    engine->RegisterObjectMethod("Matrix4", "Matrix4 opMul(const Matrix3x4&in) const", asMETHODPR(Matrix4, operator*, (const Matrix3x4 &) const, Matrix4), asCALL_THISCALL);
    // Matrix4 Matrix4::operator+(const Matrix4 &rhs) const | File: ../Math/Matrix4.h | Line: 321
    engine->RegisterObjectMethod("Matrix4", "Matrix4 opAdd(const Matrix4&in) const", asMETHODPR(Matrix4, operator+, (const Matrix4 &) const, Matrix4), asCALL_THISCALL);
    // Matrix4 Matrix4::operator-(const Matrix4 &rhs) const | File: ../Math/Matrix4.h | Line: 353
    engine->RegisterObjectMethod("Matrix4", "Matrix4 opSub(const Matrix4&in) const", asMETHODPR(Matrix4, operator-, (const Matrix4 &) const, Matrix4), asCALL_THISCALL);
    // Matrix4& Matrix4::operator=(const Matrix4 &rhs) noexcept | File: ../Math/Matrix4.h | Line: 175
    engine->RegisterObjectMethod("Matrix4", "Matrix4& opAssign(const Matrix4&in)", asMETHODPR(Matrix4, operator=, (const Matrix4 &), Matrix4 &), asCALL_THISCALL);
    // Matrix4& Matrix4::operator=(const Matrix3 &rhs) noexcept | File: ../Math/Matrix4.h | Line: 204
    engine->RegisterObjectMethod("Matrix4", "Matrix4& opAssign(const Matrix3&in)", asMETHODPR(Matrix4, operator=, (const Matrix3 &), Matrix4 &), asCALL_THISCALL);
    // bool Matrix4::operator==(const Matrix4 &rhs) const | File: ../Math/Matrix4.h | Line: 226
    engine->RegisterObjectMethod("Matrix4", "bool opEquals(const Matrix4&in) const", asMETHODPR(Matrix4, operator==, (const Matrix4 &) const, bool), asCALL_THISCALL);
    // Quaternion Matrix4::Rotation() const | File: ../Math/Matrix4.h | Line: 559
    engine->RegisterObjectMethod("Matrix4", "Quaternion Rotation() const", asMETHODPR(Matrix4, Rotation, () const, Quaternion), asCALL_THISCALL);
    // Matrix3 Matrix4::RotationMatrix() const | File: ../Math/Matrix4.h | Line: 537
    engine->RegisterObjectMethod("Matrix4", "Matrix3 RotationMatrix() const", asMETHODPR(Matrix4, RotationMatrix, () const, Matrix3), asCALL_THISCALL);
    // Vector4 Matrix4::Row(unsigned i) const | File: ../Math/Matrix4.h | Line: 647
    engine->RegisterObjectMethod("Matrix4", "Vector4 Row(uint) const", asMETHODPR(Matrix4, Row, (unsigned) const, Vector4), asCALL_THISCALL);
    // Vector3 Matrix4::Scale() const | File: ../Math/Matrix4.h | Line: 562
    engine->RegisterObjectMethod("Matrix4", "Vector3 Scale() const", asMETHODPR(Matrix4, Scale, () const, Vector3), asCALL_THISCALL);
    // void Matrix4::SetRotation(const Matrix3 &rotation) | File: ../Math/Matrix4.h | Line: 491
    engine->RegisterObjectMethod("Matrix4", "void SetRotation(const Matrix3&in)", asMETHODPR(Matrix4, SetRotation, (const Matrix3 &), void), asCALL_THISCALL);
    // void Matrix4::SetScale(const Vector3 &scale) | File: ../Math/Matrix4.h | Line: 505
    engine->RegisterObjectMethod("Matrix4", "void SetScale(const Vector3&in)", asMETHODPR(Matrix4, SetScale, (const Vector3 &), void), asCALL_THISCALL);
    // void Matrix4::SetScale(float scale) | File: ../Math/Matrix4.h | Line: 513
    engine->RegisterObjectMethod("Matrix4", "void SetScale(float)", asMETHODPR(Matrix4, SetScale, (float), void), asCALL_THISCALL);
    // void Matrix4::SetTranslation(const Vector3 &translation) | File: ../Math/Matrix4.h | Line: 483
    engine->RegisterObjectMethod("Matrix4", "void SetTranslation(const Vector3&in)", asMETHODPR(Matrix4, SetTranslation, (const Vector3 &), void), asCALL_THISCALL);
    // Vector3 Matrix4::SignedScale(const Matrix3 &rotation) const | File: ../Math/Matrix4.h | Line: 572
    engine->RegisterObjectMethod("Matrix4", "Vector3 SignedScale(const Matrix3&in) const", asMETHODPR(Matrix4, SignedScale, (const Matrix3 &) const, Vector3), asCALL_THISCALL);
    // Matrix3 Matrix4::ToMatrix3() const | File: ../Math/Matrix4.h | Line: 521
    engine->RegisterObjectMethod("Matrix4", "Matrix3 ToMatrix3() const", asMETHODPR(Matrix4, ToMatrix3, () const, Matrix3), asCALL_THISCALL);
    // String Matrix4::ToString() const | File: ../Math/Matrix4.h | Line: 677
    engine->RegisterObjectMethod("Matrix4", "String ToString() const", asMETHODPR(Matrix4, ToString, () const, String), asCALL_THISCALL);
    // Vector3 Matrix4::Translation() const | File: ../Math/Matrix4.h | Line: 549
    engine->RegisterObjectMethod("Matrix4", "Vector3 Translation() const", asMETHODPR(Matrix4, Translation, () const, Vector3), asCALL_THISCALL);
    // Matrix4 Matrix4::Transpose() const | File: ../Math/Matrix4.h | Line: 582
    engine->RegisterObjectMethod("Matrix4", "Matrix4 Transpose() const", asMETHODPR(Matrix4, Transpose, () const, Matrix4), asCALL_THISCALL);

    // float Vector4::w_ | File: ../Math/Vector4.h | Line: 233
    engine->RegisterObjectProperty("Vector4", "float w", offsetof(Vector4, w_));
    // float Vector4::x_ | File: ../Math/Vector4.h | Line: 227
    engine->RegisterObjectProperty("Vector4", "float x", offsetof(Vector4, x_));
    // float Vector4::y_ | File: ../Math/Vector4.h | Line: 229
    engine->RegisterObjectProperty("Vector4", "float y", offsetof(Vector4, y_));
    // float Vector4::z_ | File: ../Math/Vector4.h | Line: 231
    engine->RegisterObjectProperty("Vector4", "float z", offsetof(Vector4, z_));
    // Vector4 Vector4::Abs() const | File: ../Math/Vector4.h | Line: 184
    engine->RegisterObjectMethod("Vector4", "Vector4 Abs() const", asMETHODPR(Vector4, Abs, () const, Vector4), asCALL_THISCALL);
    // float Vector4::AbsDotProduct(const Vector4 &rhs) const | File: ../Math/Vector4.h | Line: 175
    engine->RegisterObjectMethod("Vector4", "float AbsDotProduct(const Vector4&in) const", asMETHODPR(Vector4, AbsDotProduct, (const Vector4 &) const, float), asCALL_THISCALL);
    // float Vector4::DotProduct(const Vector4 &rhs) const | File: ../Math/Vector4.h | Line: 172
    engine->RegisterObjectMethod("Vector4", "float DotProduct(const Vector4&in) const", asMETHODPR(Vector4, DotProduct, (const Vector4 &) const, float), asCALL_THISCALL);
    // bool Vector4::Equals(const Vector4 &rhs) const | File: ../Math/Vector4.h | Line: 190
    engine->RegisterObjectMethod("Vector4", "bool Equals(const Vector4&in) const", asMETHODPR(Vector4, Equals, (const Vector4 &) const, bool), asCALL_THISCALL);
    // bool Vector4::IsInf() const | File: ../Math/Vector4.h | Line: 199
    engine->RegisterObjectMethod("Vector4", "bool IsInf() const", asMETHODPR(Vector4, IsInf, () const, bool), asCALL_THISCALL);
    // bool Vector4::IsNaN() const | File: ../Math/Vector4.h | Line: 196
    engine->RegisterObjectMethod("Vector4", "bool IsNaN() const", asMETHODPR(Vector4, IsNaN, () const, bool), asCALL_THISCALL);
    // Vector4 Vector4::Lerp(const Vector4 &rhs, float t) const | File: ../Math/Vector4.h | Line: 187
    engine->RegisterObjectMethod("Vector4", "Vector4 Lerp(const Vector4&in, float) const", asMETHODPR(Vector4, Lerp, (const Vector4 &, float) const, Vector4), asCALL_THISCALL);
    // Vector4::operator Vector2() const | File: ../Math/Vector4.h | Line: 202
    engine->RegisterObjectMethod("Vector4", "Vector2 opConv() const", asMETHODPR(Vector4, operator Vector2, () const, Vector2), asCALL_THISCALL);
    // Vector4::operator Vector3() const | File: ../Math/Vector4.h | Line: 205
    engine->RegisterObjectMethod("Vector4", "Vector3 opConv() const", asMETHODPR(Vector4, operator Vector3, () const, Vector3), asCALL_THISCALL);
    // Vector4 Vector4::operator*(float rhs) const | File: ../Math/Vector4.h | Line: 93
    engine->RegisterObjectMethod("Vector4", "Vector4 opMul(float) const", asMETHODPR(Vector4, operator*, (float) const, Vector4), asCALL_THISCALL);
    // Vector4 Vector4::operator*(const Vector4 &rhs) const | File: ../Math/Vector4.h | Line: 96
    engine->RegisterObjectMethod("Vector4", "Vector4 opMul(const Vector4&in) const", asMETHODPR(Vector4, operator*, (const Vector4 &) const, Vector4), asCALL_THISCALL);
    // Vector4& Vector4::operator*=(float rhs) | File: ../Math/Vector4.h | Line: 125
    engine->RegisterObjectMethod("Vector4", "Vector4& opMulAssign(float)", asMETHODPR(Vector4, operator*=, (float), Vector4 &), asCALL_THISCALL);
    // Vector4& Vector4::operator*=(const Vector4 &rhs) | File: ../Math/Vector4.h | Line: 135
    engine->RegisterObjectMethod("Vector4", "Vector4& opMulAssign(const Vector4&in)", asMETHODPR(Vector4, operator*=, (const Vector4 &), Vector4 &), asCALL_THISCALL);
    // Vector4 Vector4::operator+(const Vector4 &rhs) const | File: ../Math/Vector4.h | Line: 84
    engine->RegisterObjectMethod("Vector4", "Vector4 opAdd(const Vector4&in) const", asMETHODPR(Vector4, operator+, (const Vector4 &) const, Vector4), asCALL_THISCALL);
    // Vector4& Vector4::operator+=(const Vector4 &rhs) | File: ../Math/Vector4.h | Line: 105
    engine->RegisterObjectMethod("Vector4", "Vector4& opAddAssign(const Vector4&in)", asMETHODPR(Vector4, operator+=, (const Vector4 &), Vector4 &), asCALL_THISCALL);
    // Vector4 Vector4::operator-() const | File: ../Math/Vector4.h | Line: 87
    engine->RegisterObjectMethod("Vector4", "Vector4 opNeg() const", asMETHODPR(Vector4, operator-, () const, Vector4), asCALL_THISCALL);
    // Vector4 Vector4::operator-(const Vector4 &rhs) const | File: ../Math/Vector4.h | Line: 90
    engine->RegisterObjectMethod("Vector4", "Vector4 opSub(const Vector4&in) const", asMETHODPR(Vector4, operator-, (const Vector4 &) const, Vector4), asCALL_THISCALL);
    // Vector4& Vector4::operator-=(const Vector4 &rhs) | File: ../Math/Vector4.h | Line: 115
    engine->RegisterObjectMethod("Vector4", "Vector4& opSubAssign(const Vector4&in)", asMETHODPR(Vector4, operator-=, (const Vector4 &), Vector4 &), asCALL_THISCALL);
    // Vector4 Vector4::operator/(float rhs) const | File: ../Math/Vector4.h | Line: 99
    engine->RegisterObjectMethod("Vector4", "Vector4 opDiv(float) const", asMETHODPR(Vector4, operator/, (float) const, Vector4), asCALL_THISCALL);
    // Vector4 Vector4::operator/(const Vector4 &rhs) const | File: ../Math/Vector4.h | Line: 102
    engine->RegisterObjectMethod("Vector4", "Vector4 opDiv(const Vector4&in) const", asMETHODPR(Vector4, operator/, (const Vector4 &) const, Vector4), asCALL_THISCALL);
    // Vector4& Vector4::operator/=(float rhs) | File: ../Math/Vector4.h | Line: 145
    engine->RegisterObjectMethod("Vector4", "Vector4& opDivAssign(float)", asMETHODPR(Vector4, operator/=, (float), Vector4 &), asCALL_THISCALL);
    // Vector4& Vector4::operator/=(const Vector4 &rhs) | File: ../Math/Vector4.h | Line: 156
    engine->RegisterObjectMethod("Vector4", "Vector4& opDivAssign(const Vector4&in)", asMETHODPR(Vector4, operator/=, (const Vector4 &), Vector4 &), asCALL_THISCALL);
    // Vector4& Vector4::operator=(const Vector4 &rhs) noexcept=default | File: ../Math/Vector4.h | Line: 75
    engine->RegisterObjectMethod("Vector4", "Vector4& opAssign(const Vector4&in)", asMETHODPR(Vector4, operator=, (const Vector4 &), Vector4 &), asCALL_THISCALL);
    // bool Vector4::operator==(const Vector4 &rhs) const | File: ../Math/Vector4.h | Line: 78
    engine->RegisterObjectMethod("Vector4", "bool opEquals(const Vector4&in) const", asMETHODPR(Vector4, operator==, (const Vector4 &) const, bool), asCALL_THISCALL);
    // float Vector4::operator[](unsigned index) const | File: ../Math/Vector4.h | Line: 166
    engine->RegisterObjectMethod("Vector4", "float opIndex(uint) const", asMETHODPR(Vector4, operator[], (unsigned) const, float), asCALL_THISCALL);
    // float& Vector4::operator[](unsigned index) | File: ../Math/Vector4.h | Line: 169
    engine->RegisterObjectMethod("Vector4", "float& opIndex(uint)", asMETHODPR(Vector4, operator[], (unsigned), float &), asCALL_THISCALL);
    // float Vector4::ProjectOntoAxis(const Vector3 &axis) const | File: ../Math/Vector4.h | Line: 181
    engine->RegisterObjectMethod("Vector4", "float ProjectOntoAxis(const Vector3&in) const", asMETHODPR(Vector4, ProjectOntoAxis, (const Vector3 &) const, float), asCALL_THISCALL);
    // unsigned Vector4::ToHash() const | File: ../Math/Vector4.h | Line: 215
    engine->RegisterObjectMethod("Vector4", "uint ToHash() const", asMETHODPR(Vector4, ToHash, () const, unsigned), asCALL_THISCALL);
    // String Vector4::ToString() const | File: ../Math/Vector4.h | Line: 212
    engine->RegisterObjectMethod("Vector4", "String ToString() const", asMETHODPR(Vector4, ToString, () const, String), asCALL_THISCALL);
    // Vector4::Vector4() noexcept | File: ../Math/Vector4.h | Line: 35
    engine->RegisterObjectBehaviour("Vector4", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(Vector4_Vector4_35_5), asCALL_CDECL_OBJFIRST);
    // Vector4::Vector4(const Vector4 &vector) noexcept=default | File: ../Math/Vector4.h | Line: 44
    engine->RegisterObjectBehaviour("Vector4", asBEHAVE_CONSTRUCT, "void f(const Vector4&in)", asFUNCTION(Vector4_Vector4_44_5), asCALL_CDECL_OBJFIRST);
    // Vector4::Vector4(const Vector3 &vector, float w) noexcept | File: ../Math/Vector4.h | Line: 47
    engine->RegisterObjectBehaviour("Vector4", asBEHAVE_CONSTRUCT, "void f(const Vector3&in, float)", asFUNCTION(Vector4_Vector4_47_5), asCALL_CDECL_OBJFIRST);
    // Vector4::Vector4(float x, float y, float z, float w) noexcept | File: ../Math/Vector4.h | Line: 56
    engine->RegisterObjectBehaviour("Vector4", asBEHAVE_CONSTRUCT, "void f(float, float, float, float)", asFUNCTION(Vector4_Vector4_56_5), asCALL_CDECL_OBJFIRST);

    // Vector3 Plane::absNormal_ | File: ../Math/Plane.h | Line: 122
    engine->RegisterObjectProperty("Plane", "Vector3 absNormal", offsetof(Plane, absNormal_));
    // float Plane::d_ | File: ../Math/Plane.h | Line: 124
    engine->RegisterObjectProperty("Plane", "float d", offsetof(Plane, d_));
    // Vector3 Plane::normal_ | File: ../Math/Plane.h | Line: 120
    engine->RegisterObjectProperty("Plane", "Vector3 normal", offsetof(Plane, normal_));
    // void Plane::Define(const Vector3 &v0, const Vector3 &v1, const Vector3 &v2) | File: ../Math/Plane.h | Line: 66
    engine->RegisterObjectMethod("Plane", "void Define(const Vector3&in, const Vector3&in, const Vector3&in)", asMETHODPR(Plane, Define, (const Vector3 &, const Vector3 &, const Vector3 &), void), asCALL_THISCALL);
    // void Plane::Define(const Vector3 &normal, const Vector3 &point) | File: ../Math/Plane.h | Line: 75
    engine->RegisterObjectMethod("Plane", "void Define(const Vector3&in, const Vector3&in)", asMETHODPR(Plane, Define, (const Vector3 &, const Vector3 &), void), asCALL_THISCALL);
    // void Plane::Define(const Vector4 &plane) | File: ../Math/Plane.h | Line: 83
    engine->RegisterObjectMethod("Plane", "void Define(const Vector4&in)", asMETHODPR(Plane, Define, (const Vector4 &), void), asCALL_THISCALL);
    // float Plane::Distance(const Vector3 &point) const | File: ../Math/Plane.h | Line: 101
    engine->RegisterObjectMethod("Plane", "float Distance(const Vector3&in) const", asMETHODPR(Plane, Distance, (const Vector3 &) const, float), asCALL_THISCALL);
    // Plane& Plane::operator=(const Plane &rhs) noexcept=default | File: ../Math/Plane.h | Line: 63
    engine->RegisterObjectMethod("Plane", "Plane& opAssign(const Plane&in)", asMETHODPR(Plane, operator=, (const Plane &), Plane &), asCALL_THISCALL);
    // Plane::Plane() noexcept | File: ../Math/Plane.h | Line: 36
    engine->RegisterObjectBehaviour("Plane", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(Plane_Plane_36_5), asCALL_CDECL_OBJFIRST);
    // Plane::Plane(const Plane &plane) noexcept=default | File: ../Math/Plane.h | Line: 42
    engine->RegisterObjectBehaviour("Plane", asBEHAVE_CONSTRUCT, "void f(const Plane&in)", asFUNCTION(Plane_Plane_42_5), asCALL_CDECL_OBJFIRST);
    // Plane::Plane(const Vector3 &v0, const Vector3 &v1, const Vector3 &v2) noexcept | File: ../Math/Plane.h | Line: 45
    engine->RegisterObjectBehaviour("Plane", asBEHAVE_CONSTRUCT, "void f(const Vector3&in, const Vector3&in, const Vector3&in)", asFUNCTION(Plane_Plane_45_5), asCALL_CDECL_OBJFIRST);
    // Plane::Plane(const Vector3 &normal, const Vector3 &point) noexcept | File: ../Math/Plane.h | Line: 51
    engine->RegisterObjectBehaviour("Plane", asBEHAVE_CONSTRUCT, "void f(const Vector3&in, const Vector3&in)", asFUNCTION(Plane_Plane_51_5), asCALL_CDECL_OBJFIRST);
    // Plane::Plane(const Vector4 &plane) noexcept | File: ../Math/Plane.h | Line: 57
    engine->RegisterObjectBehaviour("Plane", asBEHAVE_CONSTRUCT, "void f(const Vector4&in)", asFUNCTION(Plane_Plane_57_14), asCALL_CDECL_OBJFIRST);
    // Vector3 Plane::Project(const Vector3 &point) const | File: ../Math/Plane.h | Line: 98
    engine->RegisterObjectMethod("Plane", "Vector3 Project(const Vector3&in) const", asMETHODPR(Plane, Project, (const Vector3 &) const, Vector3), asCALL_THISCALL);
    // Vector3 Plane::Reflect(const Vector3 &direction) const | File: ../Math/Plane.h | Line: 104
    engine->RegisterObjectMethod("Plane", "Vector3 Reflect(const Vector3&in) const", asMETHODPR(Plane, Reflect, (const Vector3 &) const, Vector3), asCALL_THISCALL);
    // Matrix3x4 Plane::ReflectionMatrix() const | File: ../Math/Plane.h | Line: 108
    engine->RegisterObjectMethod("Plane", "Matrix3x4 get_reflectionMatrix() const", asMETHODPR(Plane, ReflectionMatrix, () const, Matrix3x4), asCALL_THISCALL);
    // Vector4 Plane::ToVector4() const | File: ../Math/Plane.h | Line: 117
    engine->RegisterObjectMethod("Plane", "Vector4 ToVector4() const", asMETHODPR(Plane, ToVector4, () const, Vector4), asCALL_THISCALL);
    // void Plane::Transform(const Matrix3 &transform) | File: ../Math/Plane.h | Line: 91
    engine->RegisterObjectMethod("Plane", "void Transform(const Matrix3&in)", asMETHODPR(Plane, Transform, (const Matrix3 &), void), asCALL_THISCALL);
    // void Plane::Transform(const Matrix3x4 &transform) | File: ../Math/Plane.h | Line: 93
    engine->RegisterObjectMethod("Plane", "void Transform(const Matrix3x4&in)", asMETHODPR(Plane, Transform, (const Matrix3x4 &), void), asCALL_THISCALL);
    // void Plane::Transform(const Matrix4 &transform) | File: ../Math/Plane.h | Line: 95
    engine->RegisterObjectMethod("Plane", "void Transform(const Matrix4&in)", asMETHODPR(Plane, Transform, (const Matrix4 &), void), asCALL_THISCALL);
    // Plane Plane::Transformed(const Matrix3 &transform) const | File: ../Math/Plane.h | Line: 110
    engine->RegisterObjectMethod("Plane", "Plane Transformed(const Matrix3&in) const", asMETHODPR(Plane, Transformed, (const Matrix3 &) const, Plane), asCALL_THISCALL);
    // Plane Plane::Transformed(const Matrix3x4 &transform) const | File: ../Math/Plane.h | Line: 112
    engine->RegisterObjectMethod("Plane", "Plane Transformed(const Matrix3x4&in) const", asMETHODPR(Plane, Transformed, (const Matrix3x4 &) const, Plane), asCALL_THISCALL);
    // Plane Plane::Transformed(const Matrix4 &transform) const | File: ../Math/Plane.h | Line: 114
    engine->RegisterObjectMethod("Plane", "Plane Transformed(const Matrix4&in) const", asMETHODPR(Plane, Transformed, (const Matrix4 &) const, Plane), asCALL_THISCALL);

    // void Polyhedron::AddFace(const Vector3 &v0, const Vector3 &v1, const Vector3 &v2) | File: ../Math/Polyhedron.h | Line: 82
    engine->RegisterObjectMethod("Polyhedron", "void AddFace(const Vector3&in, const Vector3&in, const Vector3&in)", asMETHODPR(Polyhedron, AddFace, (const Vector3 &, const Vector3 &, const Vector3 &), void), asCALL_THISCALL);
    // void Polyhedron::AddFace(const Vector3 &v0, const Vector3 &v1, const Vector3 &v2, const Vector3 &v3) | File: ../Math/Polyhedron.h | Line: 84
    engine->RegisterObjectMethod("Polyhedron", "void AddFace(const Vector3&in, const Vector3&in, const Vector3&in, const Vector3&in)", asMETHODPR(Polyhedron, AddFace, (const Vector3 &, const Vector3 &, const Vector3 &, const Vector3 &), void), asCALL_THISCALL);
    // void Polyhedron::Clear() | File: ../Math/Polyhedron.h | Line: 95
    engine->RegisterObjectMethod("Polyhedron", "void Clear()", asMETHODPR(Polyhedron, Clear, (), void), asCALL_THISCALL);
    // void Polyhedron::Clip(const Plane &plane) | File: ../Math/Polyhedron.h | Line: 89
    engine->RegisterObjectMethod("Polyhedron", "void Clip(const Plane&in)", asMETHODPR(Polyhedron, Clip, (const Plane &), void), asCALL_THISCALL);
    // void Polyhedron::Clip(const BoundingBox &box) | File: ../Math/Polyhedron.h | Line: 91
    engine->RegisterObjectMethod("Polyhedron", "void Clip(const BoundingBox&in)", asMETHODPR(Polyhedron, Clip, (const BoundingBox &), void), asCALL_THISCALL);
    // void Polyhedron::Clip(const Frustum &frustum) | File: ../Math/Polyhedron.h | Line: 93
    engine->RegisterObjectMethod("Polyhedron", "void Clip(const Frustum&in)", asMETHODPR(Polyhedron, Clip, (const Frustum &), void), asCALL_THISCALL);
    // void Polyhedron::Define(const BoundingBox &box) | File: ../Math/Polyhedron.h | Line: 78
    engine->RegisterObjectMethod("Polyhedron", "void Define(const BoundingBox&in)", asMETHODPR(Polyhedron, Define, (const BoundingBox &), void), asCALL_THISCALL);
    // void Polyhedron::Define(const Frustum &frustum) | File: ../Math/Polyhedron.h | Line: 80
    engine->RegisterObjectMethod("Polyhedron", "void Define(const Frustum&in)", asMETHODPR(Polyhedron, Define, (const Frustum &), void), asCALL_THISCALL);
    // bool Polyhedron::Empty() const | File: ../Math/Polyhedron.h | Line: 107
    engine->RegisterObjectMethod("Polyhedron", "bool Empty() const", asMETHODPR(Polyhedron, Empty, () const, bool), asCALL_THISCALL);
    // Polyhedron& Polyhedron::operator=(const Polyhedron &rhs) | File: ../Math/Polyhedron.h | Line: 71
    engine->RegisterObjectMethod("Polyhedron", "Polyhedron& opAssign(const Polyhedron&in)", asMETHODPR(Polyhedron, operator=, (const Polyhedron &), Polyhedron &), asCALL_THISCALL);
    // Polyhedron::Polyhedron() noexcept=default | File: ../Math/Polyhedron.h | Line: 41
    engine->RegisterObjectBehaviour("Polyhedron", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(Polyhedron_Polyhedron_41_5), asCALL_CDECL_OBJFIRST);
    // Polyhedron::Polyhedron(const Polyhedron &polyhedron) | File: ../Math/Polyhedron.h | Line: 46
    engine->RegisterObjectBehaviour("Polyhedron", asBEHAVE_CONSTRUCT, "void f(const Polyhedron&in)", asFUNCTION(Polyhedron_Polyhedron_46_5), asCALL_CDECL_OBJFIRST);
    // Polyhedron::Polyhedron(const BoundingBox &box) | File: ../Math/Polyhedron.h | Line: 59
    engine->RegisterObjectBehaviour("Polyhedron", asBEHAVE_CONSTRUCT, "void f(const BoundingBox&in)", asFUNCTION(Polyhedron_Polyhedron_59_14), asCALL_CDECL_OBJFIRST);
    // Polyhedron::Polyhedron(const Frustum &frustum) | File: ../Math/Polyhedron.h | Line: 65
    engine->RegisterObjectBehaviour("Polyhedron", asBEHAVE_CONSTRUCT, "void f(const Frustum&in)", asFUNCTION(Polyhedron_Polyhedron_65_14), asCALL_CDECL_OBJFIRST);
    // void Polyhedron::Transform(const Matrix3 &transform) | File: ../Math/Polyhedron.h | Line: 97
    engine->RegisterObjectMethod("Polyhedron", "void Transform(const Matrix3&in)", asMETHODPR(Polyhedron, Transform, (const Matrix3 &), void), asCALL_THISCALL);
    // void Polyhedron::Transform(const Matrix3x4 &transform) | File: ../Math/Polyhedron.h | Line: 99
    engine->RegisterObjectMethod("Polyhedron", "void Transform(const Matrix3x4&in)", asMETHODPR(Polyhedron, Transform, (const Matrix3x4 &), void), asCALL_THISCALL);
    // Polyhedron Polyhedron::Transformed(const Matrix3 &transform) const | File: ../Math/Polyhedron.h | Line: 102
    engine->RegisterObjectMethod("Polyhedron", "Polyhedron Transformed(const Matrix3&in) const", asMETHODPR(Polyhedron, Transformed, (const Matrix3 &) const, Polyhedron), asCALL_THISCALL);
    // Polyhedron Polyhedron::Transformed(const Matrix3x4 &transform) const | File: ../Math/Polyhedron.h | Line: 104
    engine->RegisterObjectMethod("Polyhedron", "Polyhedron Transformed(const Matrix3x4&in) const", asMETHODPR(Polyhedron, Transformed, (const Matrix3x4 &) const, Polyhedron), asCALL_THISCALL);
    // Polyhedron::~Polyhedron() noexcept=default | File: ../Math/Polyhedron.h | Line: 43
    engine->RegisterObjectBehaviour("Polyhedron", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(Polyhedron_Destructor_Polyhedron_43_5), asCALL_CDECL_OBJFIRST);

    // float Quaternion::w_ | File: ../Math/Quaternion.h | Line: 467
    engine->RegisterObjectProperty("Quaternion", "float w", offsetof(Quaternion, w_));
    // float Quaternion::x_ | File: ../Math/Quaternion.h | Line: 469
    engine->RegisterObjectProperty("Quaternion", "float x", offsetof(Quaternion, x_));
    // float Quaternion::y_ | File: ../Math/Quaternion.h | Line: 471
    engine->RegisterObjectProperty("Quaternion", "float y", offsetof(Quaternion, y_));
    // float Quaternion::z_ | File: ../Math/Quaternion.h | Line: 473
    engine->RegisterObjectProperty("Quaternion", "float z", offsetof(Quaternion, z_));
    // float Quaternion::Angle() const | File: ../Math/Quaternion.h | Line: 450
    engine->RegisterObjectMethod("Quaternion", "float get_angle() const", asMETHODPR(Quaternion, Angle, () const, float), asCALL_THISCALL);
    // Vector3 Quaternion::Axis() const | File: ../Math/Quaternion.h | Line: 447
    engine->RegisterObjectMethod("Quaternion", "Vector3 get_axis() const", asMETHODPR(Quaternion, Axis, () const, Vector3), asCALL_THISCALL);
    // Quaternion Quaternion::Conjugate() const | File: ../Math/Quaternion.h | Line: 426
    engine->RegisterObjectMethod("Quaternion", "Quaternion Conjugate() const", asMETHODPR(Quaternion, Conjugate, () const, Quaternion), asCALL_THISCALL);
    // float Quaternion::DotProduct(const Quaternion &rhs) const | File: ../Math/Quaternion.h | Line: 399
    engine->RegisterObjectMethod("Quaternion", "float DotProduct(const Quaternion&in) const", asMETHODPR(Quaternion, DotProduct, (const Quaternion &) const, float), asCALL_THISCALL);
    // bool Quaternion::Equals(const Quaternion &rhs) const | File: ../Math/Quaternion.h | Line: 414
    engine->RegisterObjectMethod("Quaternion", "bool Equals(const Quaternion&in) const", asMETHODPR(Quaternion, Equals, (const Quaternion &) const, bool), asCALL_THISCALL);
    // Vector3 Quaternion::EulerAngles() const | File: ../Math/Quaternion.h | Line: 438
    engine->RegisterObjectMethod("Quaternion", "Vector3 get_eulerAngles() const", asMETHODPR(Quaternion, EulerAngles, () const, Vector3), asCALL_THISCALL);
    // void Quaternion::FromAngleAxis(float angle, const Vector3 &axis) | File: ../Math/Quaternion.h | Line: 301
    engine->RegisterObjectMethod("Quaternion", "void FromAngleAxis(float, const Vector3&in)", asMETHODPR(Quaternion, FromAngleAxis, (float, const Vector3 &), void), asCALL_THISCALL);
    // void Quaternion::FromAxes(const Vector3 &xAxis, const Vector3 &yAxis, const Vector3 &zAxis) | File: ../Math/Quaternion.h | Line: 307
    engine->RegisterObjectMethod("Quaternion", "void FromAxes(const Vector3&in, const Vector3&in, const Vector3&in)", asMETHODPR(Quaternion, FromAxes, (const Vector3 &, const Vector3 &, const Vector3 &), void), asCALL_THISCALL);
    // void Quaternion::FromEulerAngles(float x, float y, float z) | File: ../Math/Quaternion.h | Line: 303
    engine->RegisterObjectMethod("Quaternion", "void FromEulerAngles(float, float, float)", asMETHODPR(Quaternion, FromEulerAngles, (float, float, float), void), asCALL_THISCALL);
    // bool Quaternion::FromLookRotation(const Vector3 &direction, const Vector3 &up=Vector3::UP) | File: ../Math/Quaternion.h | Line: 311
    engine->RegisterObjectMethod("Quaternion", "bool FromLookRotation(const Vector3&in, const Vector3&in)", asMETHODPR(Quaternion, FromLookRotation, (const Vector3 &, const Vector3 &), bool), asCALL_THISCALL);
    // void Quaternion::FromRotationMatrix(const Matrix3 &matrix) | File: ../Math/Quaternion.h | Line: 309
    engine->RegisterObjectMethod("Quaternion", "void FromRotationMatrix(const Matrix3&in)", asMETHODPR(Quaternion, FromRotationMatrix, (const Matrix3 &), void), asCALL_THISCALL);
    // void Quaternion::FromRotationTo(const Vector3 &start, const Vector3 &end) | File: ../Math/Quaternion.h | Line: 305
    engine->RegisterObjectMethod("Quaternion", "void FromRotationTo(const Vector3&in, const Vector3&in)", asMETHODPR(Quaternion, FromRotationTo, (const Vector3 &, const Vector3 &), void), asCALL_THISCALL);
    // Quaternion Quaternion::Inverse() const | File: ../Math/Quaternion.h | Line: 365
    engine->RegisterObjectMethod("Quaternion", "Quaternion Inverse() const", asMETHODPR(Quaternion, Inverse, () const, Quaternion), asCALL_THISCALL);
    // bool Quaternion::IsInf() const | File: ../Math/Quaternion.h | Line: 423
    engine->RegisterObjectMethod("Quaternion", "bool IsInf() const", asMETHODPR(Quaternion, IsInf, () const, bool), asCALL_THISCALL);
    // bool Quaternion::IsNaN() const | File: ../Math/Quaternion.h | Line: 420
    engine->RegisterObjectMethod("Quaternion", "bool IsNaN() const", asMETHODPR(Quaternion, IsNaN, () const, bool), asCALL_THISCALL);
    // float Quaternion::LengthSquared() const | File: ../Math/Quaternion.h | Line: 385
    engine->RegisterObjectMethod("Quaternion", "float LengthSquared() const", asMETHODPR(Quaternion, LengthSquared, () const, float), asCALL_THISCALL);
    // Quaternion Quaternion::Nlerp(const Quaternion &rhs, float t, bool shortestPath=false) const | File: ../Math/Quaternion.h | Line: 457
    engine->RegisterObjectMethod("Quaternion", "Quaternion Nlerp(const Quaternion&in, float, bool) const", asMETHODPR(Quaternion, Nlerp, (const Quaternion &, float, bool) const, Quaternion), asCALL_THISCALL);
    // void Quaternion::Normalize() | File: ../Math/Quaternion.h | Line: 314
    engine->RegisterObjectMethod("Quaternion", "void Normalize()", asMETHODPR(Quaternion, Normalize, (), void), asCALL_THISCALL);
    // Quaternion Quaternion::Normalized() const | File: ../Math/Quaternion.h | Line: 340
    engine->RegisterObjectMethod("Quaternion", "Quaternion Normalized() const", asMETHODPR(Quaternion, Normalized, () const, Quaternion), asCALL_THISCALL);
    // Quaternion Quaternion::operator*(float rhs) const | File: ../Math/Quaternion.h | Line: 204
    engine->RegisterObjectMethod("Quaternion", "Quaternion opMul(float) const", asMETHODPR(Quaternion, operator*, (float) const, Quaternion), asCALL_THISCALL);
    // Quaternion Quaternion::operator*(const Quaternion &rhs) const | File: ../Math/Quaternion.h | Line: 244
    engine->RegisterObjectMethod("Quaternion", "Quaternion opMul(const Quaternion&in) const", asMETHODPR(Quaternion, operator*, (const Quaternion &) const, Quaternion), asCALL_THISCALL);
    // Vector3 Quaternion::operator*(const Vector3 &rhs) const | File: ../Math/Quaternion.h | Line: 269
    engine->RegisterObjectMethod("Quaternion", "Vector3 opMul(const Vector3&in) const", asMETHODPR(Quaternion, operator*, (const Vector3 &) const, Vector3), asCALL_THISCALL);
    // Quaternion& Quaternion::operator*=(float rhs) | File: ../Math/Quaternion.h | Line: 174
    engine->RegisterObjectMethod("Quaternion", "Quaternion& opMulAssign(float)", asMETHODPR(Quaternion, operator*=, (float), Quaternion &), asCALL_THISCALL);
    // Quaternion Quaternion::operator+(const Quaternion &rhs) const | File: ../Math/Quaternion.h | Line: 224
    engine->RegisterObjectMethod("Quaternion", "Quaternion opAdd(const Quaternion&in) const", asMETHODPR(Quaternion, operator+, (const Quaternion &) const, Quaternion), asCALL_THISCALL);
    // Quaternion& Quaternion::operator+=(const Quaternion &rhs) | File: ../Math/Quaternion.h | Line: 160
    engine->RegisterObjectMethod("Quaternion", "Quaternion& opAddAssign(const Quaternion&in)", asMETHODPR(Quaternion, operator+=, (const Quaternion &), Quaternion &), asCALL_THISCALL);
    // Quaternion Quaternion::operator-() const | File: ../Math/Quaternion.h | Line: 214
    engine->RegisterObjectMethod("Quaternion", "Quaternion opNeg() const", asMETHODPR(Quaternion, operator-, () const, Quaternion), asCALL_THISCALL);
    // Quaternion Quaternion::operator-(const Quaternion &rhs) const | File: ../Math/Quaternion.h | Line: 234
    engine->RegisterObjectMethod("Quaternion", "Quaternion opSub(const Quaternion&in) const", asMETHODPR(Quaternion, operator-, (const Quaternion &) const, Quaternion), asCALL_THISCALL);
    // Quaternion& Quaternion::operator=(const Quaternion &rhs) noexcept | File: ../Math/Quaternion.h | Line: 146
    engine->RegisterObjectMethod("Quaternion", "Quaternion& opAssign(const Quaternion&in)", asMETHODPR(Quaternion, operator=, (const Quaternion &), Quaternion &), asCALL_THISCALL);
    // bool Quaternion::operator==(const Quaternion &rhs) const | File: ../Math/Quaternion.h | Line: 188
    engine->RegisterObjectMethod("Quaternion", "bool opEquals(const Quaternion&in) const", asMETHODPR(Quaternion, operator==, (const Quaternion &) const, bool), asCALL_THISCALL);
    // float Quaternion::PitchAngle() const | File: ../Math/Quaternion.h | Line: 442
    engine->RegisterObjectMethod("Quaternion", "float PitchAngle() const", asMETHODPR(Quaternion, PitchAngle, () const, float), asCALL_THISCALL);
    // Quaternion::Quaternion() noexcept | File: ../Math/Quaternion.h | Line: 39
    engine->RegisterObjectBehaviour("Quaternion", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(Quaternion_Quaternion_39_5), asCALL_CDECL_OBJFIRST);
    // Quaternion::Quaternion(const Quaternion &quat) noexcept | File: ../Math/Quaternion.h | Line: 53
    engine->RegisterObjectBehaviour("Quaternion", asBEHAVE_CONSTRUCT, "void f(const Quaternion&in)", asFUNCTION(Quaternion_Quaternion_53_5), asCALL_CDECL_OBJFIRST);
    // Quaternion::Quaternion(float w, float x, float y, float z) noexcept | File: ../Math/Quaternion.h | Line: 68
    engine->RegisterObjectBehaviour("Quaternion", asBEHAVE_CONSTRUCT, "void f(float, float, float, float)", asFUNCTION(Quaternion_Quaternion_68_5), asCALL_CDECL_OBJFIRST);
    // Quaternion::Quaternion(float angle, const Vector3 &axis) noexcept | File: ../Math/Quaternion.h | Line: 97
    engine->RegisterObjectBehaviour("Quaternion", asBEHAVE_CONSTRUCT, "void f(float, const Vector3&in)", asFUNCTION(Quaternion_Quaternion_97_5), asCALL_CDECL_OBJFIRST);
    // Quaternion::Quaternion(float angle) noexcept | File: ../Math/Quaternion.h | Line: 103
    engine->RegisterObjectBehaviour("Quaternion", asBEHAVE_CONSTRUCT, "void f(float)", asFUNCTION(Quaternion_Quaternion_103_14), asCALL_CDECL_OBJFIRST);
    // Quaternion::Quaternion(float x, float y, float z) noexcept | File: ../Math/Quaternion.h | Line: 109
    engine->RegisterObjectBehaviour("Quaternion", asBEHAVE_CONSTRUCT, "void f(float, float, float)", asFUNCTION(Quaternion_Quaternion_109_5), asCALL_CDECL_OBJFIRST);
    // Quaternion::Quaternion(const Vector3 &angles) noexcept | File: ../Math/Quaternion.h | Line: 115
    engine->RegisterObjectBehaviour("Quaternion", asBEHAVE_CONSTRUCT, "void f(const Vector3&in)", asFUNCTION(Quaternion_Quaternion_115_14), asCALL_CDECL_OBJFIRST);
    // Quaternion::Quaternion(const Vector3 &start, const Vector3 &end) noexcept | File: ../Math/Quaternion.h | Line: 121
    engine->RegisterObjectBehaviour("Quaternion", asBEHAVE_CONSTRUCT, "void f(const Vector3&in, const Vector3&in)", asFUNCTION(Quaternion_Quaternion_121_5), asCALL_CDECL_OBJFIRST);
    // Quaternion::Quaternion(const Vector3 &xAxis, const Vector3 &yAxis, const Vector3 &zAxis) noexcept | File: ../Math/Quaternion.h | Line: 127
    engine->RegisterObjectBehaviour("Quaternion", asBEHAVE_CONSTRUCT, "void f(const Vector3&in, const Vector3&in, const Vector3&in)", asFUNCTION(Quaternion_Quaternion_127_5), asCALL_CDECL_OBJFIRST);
    // Quaternion::Quaternion(const Matrix3 &matrix) noexcept | File: ../Math/Quaternion.h | Line: 133
    engine->RegisterObjectBehaviour("Quaternion", asBEHAVE_CONSTRUCT, "void f(const Matrix3&in)", asFUNCTION(Quaternion_Quaternion_133_14), asCALL_CDECL_OBJFIRST);
    // float Quaternion::RollAngle() const | File: ../Math/Quaternion.h | Line: 444
    engine->RegisterObjectMethod("Quaternion", "float RollAngle() const", asMETHODPR(Quaternion, RollAngle, () const, float), asCALL_THISCALL);
    // Matrix3 Quaternion::RotationMatrix() const | File: ../Math/Quaternion.h | Line: 453
    engine->RegisterObjectMethod("Quaternion", "Matrix3 get_rotationMatrix() const", asMETHODPR(Quaternion, RotationMatrix, () const, Matrix3), asCALL_THISCALL);
    // Quaternion Quaternion::Slerp(const Quaternion &rhs, float t) const | File: ../Math/Quaternion.h | Line: 455
    engine->RegisterObjectMethod("Quaternion", "Quaternion Slerp(const Quaternion&in, float) const", asMETHODPR(Quaternion, Slerp, (const Quaternion &, float) const, Quaternion), asCALL_THISCALL);
    // String Quaternion::ToString() const | File: ../Math/Quaternion.h | Line: 464
    engine->RegisterObjectMethod("Quaternion", "String ToString() const", asMETHODPR(Quaternion, ToString, () const, String), asCALL_THISCALL);
    // float Quaternion::YawAngle() const | File: ../Math/Quaternion.h | Line: 440
    engine->RegisterObjectMethod("Quaternion", "float YawAngle() const", asMETHODPR(Quaternion, YawAngle, () const, float), asCALL_THISCALL);

    // Vector3 Ray::direction_ | File: ../Math/Ray.h | Line: 118
    engine->RegisterObjectProperty("Ray", "Vector3 direction", offsetof(Ray, direction_));
    // Vector3 Ray::origin_ | File: ../Math/Ray.h | Line: 116
    engine->RegisterObjectProperty("Ray", "Vector3 origin", offsetof(Ray, origin_));
    // Vector3 Ray::ClosestPoint(const Ray &ray) const | File: ../Math/Ray.h | Line: 84
    engine->RegisterObjectMethod("Ray", "Vector3 ClosestPoint(const Ray&in) const", asMETHODPR(Ray, ClosestPoint, (const Ray &) const, Vector3), asCALL_THISCALL);
    // void Ray::Define(const Vector3 &origin, const Vector3 &direction) | File: ../Math/Ray.h | Line: 63
    engine->RegisterObjectMethod("Ray", "void Define(const Vector3&in, const Vector3&in)", asMETHODPR(Ray, Define, (const Vector3 &, const Vector3 &), void), asCALL_THISCALL);
    // float Ray::Distance(const Vector3 &point) const | File: ../Math/Ray.h | Line: 77
    engine->RegisterObjectMethod("Ray", "float Distance(const Vector3&in) const", asMETHODPR(Ray, Distance, (const Vector3 &) const, float), asCALL_THISCALL);
    // float Ray::HitDistance(const Plane &plane) const | File: ../Math/Ray.h | Line: 86
    engine->RegisterObjectMethod("Ray", "float HitDistance(const Plane&in) const", asMETHODPR(Ray, HitDistance, (const Plane &) const, float), asCALL_THISCALL);
    // float Ray::HitDistance(const BoundingBox &box) const | File: ../Math/Ray.h | Line: 88
    engine->RegisterObjectMethod("Ray", "float HitDistance(const BoundingBox&in) const", asMETHODPR(Ray, HitDistance, (const BoundingBox &) const, float), asCALL_THISCALL);
    // float Ray::HitDistance(const Frustum &frustum, bool solidInside=true) const | File: ../Math/Ray.h | Line: 90
    engine->RegisterObjectMethod("Ray", "float HitDistance(const Frustum&in, bool) const", asMETHODPR(Ray, HitDistance, (const Frustum &, bool) const, float), asCALL_THISCALL);
    // float Ray::HitDistance(const Sphere &sphere) const | File: ../Math/Ray.h | Line: 92
    engine->RegisterObjectMethod("Ray", "float HitDistance(const Sphere&in) const", asMETHODPR(Ray, HitDistance, (const Sphere &) const, float), asCALL_THISCALL);
    // Ray& Ray::operator=(const Ray &rhs) noexcept=default | File: ../Math/Ray.h | Line: 54
    engine->RegisterObjectMethod("Ray", "Ray& opAssign(const Ray&in)", asMETHODPR(Ray, operator=, (const Ray &), Ray &), asCALL_THISCALL);
    // bool Ray::operator==(const Ray &rhs) const | File: ../Math/Ray.h | Line: 57
    engine->RegisterObjectMethod("Ray", "bool opEquals(const Ray&in) const", asMETHODPR(Ray, operator==, (const Ray &) const, bool), asCALL_THISCALL);
    // Vector3 Ray::Project(const Vector3 &point) const | File: ../Math/Ray.h | Line: 70
    engine->RegisterObjectMethod("Ray", "Vector3 Project(const Vector3&in) const", asMETHODPR(Ray, Project, (const Vector3 &) const, Vector3), asCALL_THISCALL);
    // Ray::Ray() noexcept=default | File: ../Math/Ray.h | Line: 42
    engine->RegisterObjectBehaviour("Ray", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(Ray_Ray_42_5), asCALL_CDECL_OBJFIRST);
    // Ray::Ray(const Vector3 &origin, const Vector3 &direction) noexcept | File: ../Math/Ray.h | Line: 45
    engine->RegisterObjectBehaviour("Ray", asBEHAVE_CONSTRUCT, "void f(const Vector3&in, const Vector3&in)", asFUNCTION(Ray_Ray_45_5), asCALL_CDECL_OBJFIRST);
    // Ray::Ray(const Ray &ray) noexcept=default | File: ../Math/Ray.h | Line: 51
    engine->RegisterObjectBehaviour("Ray", asBEHAVE_CONSTRUCT, "void f(const Ray&in)", asFUNCTION(Ray_Ray_51_5), asCALL_CDECL_OBJFIRST);
    // Ray Ray::Transformed(const Matrix3x4 &transform) const | File: ../Math/Ray.h | Line: 113
    engine->RegisterObjectMethod("Ray", "Ray Transformed(const Matrix3x4&in) const", asMETHODPR(Ray, Transformed, (const Matrix3x4 &) const, Ray), asCALL_THISCALL);

    // Vector2 Rect::max_ | File: ../Math/Rect.h | Line: 271
    engine->RegisterObjectProperty("Rect", "Vector2 max", offsetof(Rect, max_));
    // Vector2 Rect::min_ | File: ../Math/Rect.h | Line: 269
    engine->RegisterObjectProperty("Rect", "Vector2 min", offsetof(Rect, min_));
    // float Rect::Bottom() const | File: ../Math/Rect.h | Line: 266
    engine->RegisterObjectMethod("Rect", "float get_bottom() const", asMETHODPR(Rect, Bottom, () const, float), asCALL_THISCALL);
    // Vector2 Rect::Center() const | File: ../Math/Rect.h | Line: 203
    engine->RegisterObjectMethod("Rect", "Vector2 get_center() const", asMETHODPR(Rect, Center, () const, Vector2), asCALL_THISCALL);
    // void Rect::Clear() | File: ../Math/Rect.h | Line: 186
    engine->RegisterObjectMethod("Rect", "void Clear()", asMETHODPR(Rect, Clear, (), void), asCALL_THISCALL);
    // void Rect::Clip(const Rect &rect) | File: ../Math/Rect.h | Line: 193
    engine->RegisterObjectMethod("Rect", "void Clip(const Rect&in)", asMETHODPR(Rect, Clip, (const Rect &), void), asCALL_THISCALL);
    // void Rect::Define(const Rect &rect) | File: ../Math/Rect.h | Line: 140
    engine->RegisterObjectMethod("Rect", "void Define(const Rect&in)", asMETHODPR(Rect, Define, (const Rect &), void), asCALL_THISCALL);
    // void Rect::Define(const Vector2 &min, const Vector2 &max) | File: ../Math/Rect.h | Line: 147
    engine->RegisterObjectMethod("Rect", "void Define(const Vector2&in, const Vector2&in)", asMETHODPR(Rect, Define, (const Vector2 &, const Vector2 &), void), asCALL_THISCALL);
    // void Rect::Define(const Vector2 &point) | File: ../Math/Rect.h | Line: 154
    engine->RegisterObjectMethod("Rect", "void Define(const Vector2&in)", asMETHODPR(Rect, Define, (const Vector2 &), void), asCALL_THISCALL);
    // bool Rect::Defined() const | File: ../Math/Rect.h | Line: 196
    engine->RegisterObjectMethod("Rect", "bool Defined() const", asMETHODPR(Rect, Defined, () const, bool), asCALL_THISCALL);
    // bool Rect::Equals(const Rect &rhs) const | File: ../Math/Rect.h | Line: 214
    engine->RegisterObjectMethod("Rect", "bool Equals(const Rect&in) const", asMETHODPR(Rect, Equals, (const Rect &) const, bool), asCALL_THISCALL);
    // Vector2 Rect::HalfSize() const | File: ../Math/Rect.h | Line: 211
    engine->RegisterObjectMethod("Rect", "Vector2 get_halfSize() const", asMETHODPR(Rect, HalfSize, () const, Vector2), asCALL_THISCALL);
    // Intersection Rect::IsInside(const Vector2 &point) const | File: ../Math/Rect.h | Line: 217
    engine->RegisterObjectMethod("Rect", "Intersection IsInside(const Vector2&in) const", asMETHODPR(Rect, IsInside, (const Vector2 &) const, Intersection), asCALL_THISCALL);
    // Intersection Rect::IsInside(const Rect &rect) const | File: ../Math/Rect.h | Line: 226
    engine->RegisterObjectMethod("Rect", "Intersection IsInside(const Rect&in) const", asMETHODPR(Rect, IsInside, (const Rect &) const, Intersection), asCALL_THISCALL);
    // float Rect::Left() const | File: ../Math/Rect.h | Line: 254
    engine->RegisterObjectMethod("Rect", "float get_left() const", asMETHODPR(Rect, Left, () const, float), asCALL_THISCALL);
    // Vector2 Rect::Max() const | File: ../Math/Rect.h | Line: 250
    engine->RegisterObjectMethod("Rect", "Vector2 Max() const", asMETHODPR(Rect, Max, () const, Vector2), asCALL_THISCALL);
    // void Rect::Merge(const Vector2 &point) | File: ../Math/Rect.h | Line: 160
    engine->RegisterObjectMethod("Rect", "void Merge(const Vector2&in)", asMETHODPR(Rect, Merge, (const Vector2 &), void), asCALL_THISCALL);
    // void Rect::Merge(const Rect &rect) | File: ../Math/Rect.h | Line: 173
    engine->RegisterObjectMethod("Rect", "void Merge(const Rect&in)", asMETHODPR(Rect, Merge, (const Rect &), void), asCALL_THISCALL);
    // Vector2 Rect::Min() const | File: ../Math/Rect.h | Line: 247
    engine->RegisterObjectMethod("Rect", "Vector2 Min() const", asMETHODPR(Rect, Min, () const, Vector2), asCALL_THISCALL);
    // Rect Rect::operator*(float value) const | File: ../Math/Rect.h | Line: 122
    engine->RegisterObjectMethod("Rect", "Rect opMul(float) const", asMETHODPR(Rect, operator*, (float) const, Rect), asCALL_THISCALL);
    // Rect& Rect::operator*=(float value) | File: ../Math/Rect.h | Line: 108
    engine->RegisterObjectMethod("Rect", "Rect& opMulAssign(float)", asMETHODPR(Rect, operator*=, (float), Rect &), asCALL_THISCALL);
    // Rect Rect::operator+(const Rect &rhs) const | File: ../Math/Rect.h | Line: 128
    engine->RegisterObjectMethod("Rect", "Rect opAdd(const Rect&in) const", asMETHODPR(Rect, operator+, (const Rect &) const, Rect), asCALL_THISCALL);
    // Rect& Rect::operator+=(const Rect &rhs) | File: ../Math/Rect.h | Line: 84
    engine->RegisterObjectMethod("Rect", "Rect& opAddAssign(const Rect&in)", asMETHODPR(Rect, operator+=, (const Rect &), Rect &), asCALL_THISCALL);
    // Rect Rect::operator-(const Rect &rhs) const | File: ../Math/Rect.h | Line: 134
    engine->RegisterObjectMethod("Rect", "Rect opSub(const Rect&in) const", asMETHODPR(Rect, operator-, (const Rect &) const, Rect), asCALL_THISCALL);
    // Rect& Rect::operator-=(const Rect &rhs) | File: ../Math/Rect.h | Line: 92
    engine->RegisterObjectMethod("Rect", "Rect& opSubAssign(const Rect&in)", asMETHODPR(Rect, operator-=, (const Rect &), Rect &), asCALL_THISCALL);
    // Rect Rect::operator/(float value) const | File: ../Math/Rect.h | Line: 116
    engine->RegisterObjectMethod("Rect", "Rect opDiv(float) const", asMETHODPR(Rect, operator/, (float) const, Rect), asCALL_THISCALL);
    // Rect& Rect::operator/=(float value) | File: ../Math/Rect.h | Line: 100
    engine->RegisterObjectMethod("Rect", "Rect& opDivAssign(float)", asMETHODPR(Rect, operator/=, (float), Rect &), asCALL_THISCALL);
    // Rect& Rect::operator=(const Rect &rhs) noexcept=default | File: ../Math/Rect.h | Line: 75
    engine->RegisterObjectMethod("Rect", "Rect& opAssign(const Rect&in)", asMETHODPR(Rect, operator=, (const Rect &), Rect &), asCALL_THISCALL);
    // bool Rect::operator==(const Rect &rhs) const | File: ../Math/Rect.h | Line: 78
    engine->RegisterObjectMethod("Rect", "bool opEquals(const Rect&in) const", asMETHODPR(Rect, operator==, (const Rect &) const, bool), asCALL_THISCALL);
    // Rect::Rect() noexcept | File: ../Math/Rect.h | Line: 36
    engine->RegisterObjectBehaviour("Rect", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(Rect_Rect_36_5), asCALL_CDECL_OBJFIRST);
    // Rect::Rect(const Vector2 &min, const Vector2 &max) noexcept | File: ../Math/Rect.h | Line: 43
    engine->RegisterObjectBehaviour("Rect", asBEHAVE_CONSTRUCT, "void f(const Vector2&in, const Vector2&in)", asFUNCTION(Rect_Rect_43_5), asCALL_CDECL_OBJFIRST);
    // Rect::Rect(float left, float top, float right, float bottom) noexcept | File: ../Math/Rect.h | Line: 50
    engine->RegisterObjectBehaviour("Rect", asBEHAVE_CONSTRUCT, "void f(float, float, float, float)", asFUNCTION(Rect_Rect_50_5), asCALL_CDECL_OBJFIRST);
    // Rect::Rect(const Vector4 &vector) noexcept | File: ../Math/Rect.h | Line: 57
    engine->RegisterObjectBehaviour("Rect", asBEHAVE_CONSTRUCT, "void f(const Vector4&in)", asFUNCTION(Rect_Rect_57_14), asCALL_CDECL_OBJFIRST);
    // Rect::Rect(const Rect &rect) noexcept=default | File: ../Math/Rect.h | Line: 72
    engine->RegisterObjectBehaviour("Rect", asBEHAVE_CONSTRUCT, "void f(const Rect&in)", asFUNCTION(Rect_Rect_72_5), asCALL_CDECL_OBJFIRST);
    // float Rect::Right() const | File: ../Math/Rect.h | Line: 262
    engine->RegisterObjectMethod("Rect", "float get_right() const", asMETHODPR(Rect, Right, () const, float), asCALL_THISCALL);
    // Vector2 Rect::Size() const | File: ../Math/Rect.h | Line: 207
    engine->RegisterObjectMethod("Rect", "Vector2 get_size() const", asMETHODPR(Rect, Size, () const, Vector2), asCALL_THISCALL);
    // float Rect::Top() const | File: ../Math/Rect.h | Line: 258
    engine->RegisterObjectMethod("Rect", "float get_top() const", asMETHODPR(Rect, Top, () const, float), asCALL_THISCALL);
    // String Rect::ToString() const | File: ../Math/Rect.h | Line: 244
    engine->RegisterObjectMethod("Rect", "String ToString() const", asMETHODPR(Rect, ToString, () const, String), asCALL_THISCALL);
    // Vector4 Rect::ToVector4() const | File: ../Math/Rect.h | Line: 241
    engine->RegisterObjectMethod("Rect", "Vector4 ToVector4() const", asMETHODPR(Rect, ToVector4, () const, Vector4), asCALL_THISCALL);

    // Vector3 Sphere::center_ | File: ../Math/Sphere.h | Line: 206
    engine->RegisterObjectProperty("Sphere", "Vector3 center", offsetof(Sphere, center_));
    // float Sphere::radius_ | File: ../Math/Sphere.h | Line: 208
    engine->RegisterObjectProperty("Sphere", "float radius", offsetof(Sphere, radius_));
    // void Sphere::Clear() | File: ../Math/Sphere.h | Line: 147
    engine->RegisterObjectMethod("Sphere", "void Clear()", asMETHODPR(Sphere, Clear, (), void), asCALL_THISCALL);
    // void Sphere::Define(const Sphere &sphere) | File: ../Math/Sphere.h | Line: 91
    engine->RegisterObjectMethod("Sphere", "void Define(const Sphere&in)", asMETHODPR(Sphere, Define, (const Sphere &), void), asCALL_THISCALL);
    // void Sphere::Define(const Vector3 &center, float radius) | File: ../Math/Sphere.h | Line: 97
    engine->RegisterObjectMethod("Sphere", "void Define(const Vector3&in, float)", asMETHODPR(Sphere, Define, (const Vector3 &, float), void), asCALL_THISCALL);
    // void Sphere::Define(const BoundingBox &box) | File: ../Math/Sphere.h | Line: 107
    engine->RegisterObjectMethod("Sphere", "void Define(const BoundingBox&in)", asMETHODPR(Sphere, Define, (const BoundingBox &), void), asCALL_THISCALL);
    // void Sphere::Define(const Frustum &frustum) | File: ../Math/Sphere.h | Line: 109
    engine->RegisterObjectMethod("Sphere", "void Define(const Frustum&in)", asMETHODPR(Sphere, Define, (const Frustum &), void), asCALL_THISCALL);
    // void Sphere::Define(const Polyhedron &poly) | File: ../Math/Sphere.h | Line: 111
    engine->RegisterObjectMethod("Sphere", "void Define(const Polyhedron&in)", asMETHODPR(Sphere, Define, (const Polyhedron &), void), asCALL_THISCALL);
    // bool Sphere::Defined() const | File: ../Math/Sphere.h | Line: 154
    engine->RegisterObjectMethod("Sphere", "bool Defined() const", asMETHODPR(Sphere, Defined, () const, bool), asCALL_THISCALL);
    // float Sphere::Distance(const Vector3 &point) const | File: ../Math/Sphere.h | Line: 199
    engine->RegisterObjectMethod("Sphere", "float Distance(const Vector3&in) const", asMETHODPR(Sphere, Distance, (const Vector3 &) const, float), asCALL_THISCALL);
    // Vector3 Sphere::GetLocalPoint(float theta, float phi) const | File: ../Math/Sphere.h | Line: 201
    engine->RegisterObjectMethod("Sphere", "Vector3 GetLocalPoint(float, float) const", asMETHODPR(Sphere, GetLocalPoint, (float, float) const, Vector3), asCALL_THISCALL);
    // Vector3 Sphere::GetPoint(float theta, float phi) const | File: ../Math/Sphere.h | Line: 203
    engine->RegisterObjectMethod("Sphere", "Vector3 GetPoint(float, float) const", asMETHODPR(Sphere, GetPoint, (float, float) const, Vector3), asCALL_THISCALL);
    // Intersection Sphere::IsInside(const Vector3 &point) const | File: ../Math/Sphere.h | Line: 160
    engine->RegisterObjectMethod("Sphere", "Intersection IsInside(const Vector3&in) const", asMETHODPR(Sphere, IsInside, (const Vector3 &) const, Intersection), asCALL_THISCALL);
    // Intersection Sphere::IsInside(const Sphere &sphere) const | File: ../Math/Sphere.h | Line: 170
    engine->RegisterObjectMethod("Sphere", "Intersection IsInside(const Sphere&in) const", asMETHODPR(Sphere, IsInside, (const Sphere &) const, Intersection), asCALL_THISCALL);
    // Intersection Sphere::IsInside(const BoundingBox &box) const | File: ../Math/Sphere.h | Line: 194
    engine->RegisterObjectMethod("Sphere", "Intersection IsInside(const BoundingBox&in) const", asMETHODPR(Sphere, IsInside, (const BoundingBox &) const, Intersection), asCALL_THISCALL);
    // Intersection Sphere::IsInsideFast(const Sphere &sphere) const | File: ../Math/Sphere.h | Line: 182
    engine->RegisterObjectMethod("Sphere", "Intersection IsInsideFast(const Sphere&in) const", asMETHODPR(Sphere, IsInsideFast, (const Sphere &) const, Intersection), asCALL_THISCALL);
    // Intersection Sphere::IsInsideFast(const BoundingBox &box) const | File: ../Math/Sphere.h | Line: 196
    engine->RegisterObjectMethod("Sphere", "Intersection IsInsideFast(const BoundingBox&in) const", asMETHODPR(Sphere, IsInsideFast, (const BoundingBox &) const, Intersection), asCALL_THISCALL);
    // void Sphere::Merge(const Vector3 &point) | File: ../Math/Sphere.h | Line: 114
    engine->RegisterObjectMethod("Sphere", "void Merge(const Vector3&in)", asMETHODPR(Sphere, Merge, (const Vector3 &), void), asCALL_THISCALL);
    // void Sphere::Merge(const BoundingBox &box) | File: ../Math/Sphere.h | Line: 138
    engine->RegisterObjectMethod("Sphere", "void Merge(const BoundingBox&in)", asMETHODPR(Sphere, Merge, (const BoundingBox &), void), asCALL_THISCALL);
    // void Sphere::Merge(const Frustum &frustum) | File: ../Math/Sphere.h | Line: 140
    engine->RegisterObjectMethod("Sphere", "void Merge(const Frustum&in)", asMETHODPR(Sphere, Merge, (const Frustum &), void), asCALL_THISCALL);
    // void Sphere::Merge(const Polyhedron &poly) | File: ../Math/Sphere.h | Line: 142
    engine->RegisterObjectMethod("Sphere", "void Merge(const Polyhedron&in)", asMETHODPR(Sphere, Merge, (const Polyhedron &), void), asCALL_THISCALL);
    // void Sphere::Merge(const Sphere &sphere) | File: ../Math/Sphere.h | Line: 144
    engine->RegisterObjectMethod("Sphere", "void Merge(const Sphere&in)", asMETHODPR(Sphere, Merge, (const Sphere &), void), asCALL_THISCALL);
    // Sphere& Sphere::operator=(const Sphere &rhs) noexcept=default | File: ../Math/Sphere.h | Line: 82
    engine->RegisterObjectMethod("Sphere", "Sphere& opAssign(const Sphere&in)", asMETHODPR(Sphere, operator=, (const Sphere &), Sphere &), asCALL_THISCALL);
    // bool Sphere::operator==(const Sphere &rhs) const | File: ../Math/Sphere.h | Line: 85
    engine->RegisterObjectMethod("Sphere", "bool opEquals(const Sphere&in) const", asMETHODPR(Sphere, operator==, (const Sphere &) const, bool), asCALL_THISCALL);
    // Sphere::Sphere() noexcept | File: ../Math/Sphere.h | Line: 40
    engine->RegisterObjectBehaviour("Sphere", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(Sphere_Sphere_40_5), asCALL_CDECL_OBJFIRST);
    // Sphere::Sphere(const Sphere &sphere) noexcept=default | File: ../Math/Sphere.h | Line: 47
    engine->RegisterObjectBehaviour("Sphere", asBEHAVE_CONSTRUCT, "void f(const Sphere&in)", asFUNCTION(Sphere_Sphere_47_5), asCALL_CDECL_OBJFIRST);
    // Sphere::Sphere(const Vector3 &center, float radius) noexcept | File: ../Math/Sphere.h | Line: 50
    engine->RegisterObjectBehaviour("Sphere", asBEHAVE_CONSTRUCT, "void f(const Vector3&in, float)", asFUNCTION(Sphere_Sphere_50_5), asCALL_CDECL_OBJFIRST);
    // Sphere::Sphere(const BoundingBox &box) noexcept | File: ../Math/Sphere.h | Line: 64
    engine->RegisterObjectBehaviour("Sphere", asBEHAVE_CONSTRUCT, "void f(const BoundingBox&in)", asFUNCTION(Sphere_Sphere_64_14), asCALL_CDECL_OBJFIRST);
    // Sphere::Sphere(const Frustum &frustum) noexcept | File: ../Math/Sphere.h | Line: 70
    engine->RegisterObjectBehaviour("Sphere", asBEHAVE_CONSTRUCT, "void f(const Frustum&in)", asFUNCTION(Sphere_Sphere_70_14), asCALL_CDECL_OBJFIRST);
    // Sphere::Sphere(const Polyhedron &poly) noexcept | File: ../Math/Sphere.h | Line: 76
    engine->RegisterObjectBehaviour("Sphere", asBEHAVE_CONSTRUCT, "void f(const Polyhedron&in)", asFUNCTION(Sphere_Sphere_76_14), asCALL_CDECL_OBJFIRST);

    // float Vector3::x_ | File: ../Math/Vector3.h | Line: 480
    engine->RegisterObjectProperty("Vector3", "float x", offsetof(Vector3, x_));
    // float Vector3::y_ | File: ../Math/Vector3.h | Line: 482
    engine->RegisterObjectProperty("Vector3", "float y", offsetof(Vector3, y_));
    // float Vector3::z_ | File: ../Math/Vector3.h | Line: 484
    engine->RegisterObjectProperty("Vector3", "float z", offsetof(Vector3, z_));
    // Vector3 Vector3::Abs() const | File: ../Math/Vector3.h | Line: 407
    engine->RegisterObjectMethod("Vector3", "Vector3 Abs() const", asMETHODPR(Vector3, Abs, () const, Vector3), asCALL_THISCALL);
    // float Vector3::AbsDotProduct(const Vector3 &rhs) const | File: ../Math/Vector3.h | Line: 359
    engine->RegisterObjectMethod("Vector3", "float AbsDotProduct(const Vector3&in) const", asMETHODPR(Vector3, AbsDotProduct, (const Vector3 &) const, float), asCALL_THISCALL);
    // float Vector3::Angle(const Vector3 &rhs) const | File: ../Math/Vector3.h | Line: 419
    engine->RegisterObjectMethod("Vector3", "float Angle(const Vector3&in) const", asMETHODPR(Vector3, Angle, (const Vector3 &) const, float), asCALL_THISCALL);
    // Vector3 Vector3::CrossProduct(const Vector3 &rhs) const | File: ../Math/Vector3.h | Line: 397
    engine->RegisterObjectMethod("Vector3", "Vector3 CrossProduct(const Vector3&in) const", asMETHODPR(Vector3, CrossProduct, (const Vector3 &) const, Vector3), asCALL_THISCALL);
    // float Vector3::DistanceToPlane(const Vector3 &origin, const Vector3 &normal) const | File: ../Math/Vector3.h | Line: 391
    engine->RegisterObjectMethod("Vector3", "float DistanceToPlane(const Vector3&in, const Vector3&in) const", asMETHODPR(Vector3, DistanceToPlane, (const Vector3 &, const Vector3 &) const, float), asCALL_THISCALL);
    // float Vector3::DistanceToPoint(const Vector3 &point) const | File: ../Math/Vector3.h | Line: 388
    engine->RegisterObjectMethod("Vector3", "float DistanceToPoint(const Vector3&in) const", asMETHODPR(Vector3, DistanceToPoint, (const Vector3 &) const, float), asCALL_THISCALL);
    // float Vector3::DotProduct(const Vector3 &rhs) const | File: ../Math/Vector3.h | Line: 356
    engine->RegisterObjectMethod("Vector3", "float DotProduct(const Vector3&in) const", asMETHODPR(Vector3, DotProduct, (const Vector3 &) const, float), asCALL_THISCALL);
    // bool Vector3::Equals(const Vector3 &rhs) const | File: ../Math/Vector3.h | Line: 413
    engine->RegisterObjectMethod("Vector3", "bool Equals(const Vector3&in) const", asMETHODPR(Vector3, Equals, (const Vector3 &) const, bool), asCALL_THISCALL);
    // bool Vector3::IsInf() const | File: ../Math/Vector3.h | Line: 425
    engine->RegisterObjectMethod("Vector3", "bool IsInf() const", asMETHODPR(Vector3, IsInf, () const, bool), asCALL_THISCALL);
    // bool Vector3::IsNaN() const | File: ../Math/Vector3.h | Line: 422
    engine->RegisterObjectMethod("Vector3", "bool IsNaN() const", asMETHODPR(Vector3, IsNaN, () const, bool), asCALL_THISCALL);
    // float Vector3::Length() const | File: ../Math/Vector3.h | Line: 349
    engine->RegisterObjectMethod("Vector3", "float get_length() const", asMETHODPR(Vector3, Length, () const, float), asCALL_THISCALL);
    // float Vector3::LengthSquared() const | File: ../Math/Vector3.h | Line: 353
    engine->RegisterObjectMethod("Vector3", "float get_lengthSquared() const", asMETHODPR(Vector3, LengthSquared, () const, float), asCALL_THISCALL);
    // Vector3 Vector3::Lerp(const Vector3 &rhs, float t) const | File: ../Math/Vector3.h | Line: 410
    engine->RegisterObjectMethod("Vector3", "Vector3 Lerp(const Vector3&in, float) const", asMETHODPR(Vector3, Lerp, (const Vector3 &, float) const, Vector3), asCALL_THISCALL);
    // void Vector3::Normalize() | File: ../Math/Vector3.h | Line: 335
    engine->RegisterObjectMethod("Vector3", "void Normalize()", asMETHODPR(Vector3, Normalize, (), void), asCALL_THISCALL);
    // Vector3 Vector3::Normalized() const | File: ../Math/Vector3.h | Line: 428
    engine->RegisterObjectMethod("Vector3", "Vector3 Normalized() const", asMETHODPR(Vector3, Normalized, () const, Vector3), asCALL_THISCALL);
    // Vector3 Vector3::NormalizedOrDefault(const Vector3 &defaultValue=Vector3::ZERO, float eps=M_LARGE_EPSILON) const | File: ../Math/Vector3.h | Line: 441
    engine->RegisterObjectMethod("Vector3", "Vector3 NormalizedOrDefault(const Vector3&in, float) const", asMETHODPR(Vector3, NormalizedOrDefault, (const Vector3 &, float) const, Vector3), asCALL_THISCALL);
    // Vector3 Vector3::operator*(float rhs) const | File: ../Math/Vector3.h | Line: 268
    engine->RegisterObjectMethod("Vector3", "Vector3 opMul(float) const", asMETHODPR(Vector3, operator*, (float) const, Vector3), asCALL_THISCALL);
    // Vector3 Vector3::operator*(const Vector3 &rhs) const | File: ../Math/Vector3.h | Line: 271
    engine->RegisterObjectMethod("Vector3", "Vector3 opMul(const Vector3&in) const", asMETHODPR(Vector3, operator*, (const Vector3 &) const, Vector3), asCALL_THISCALL);
    // Vector3& Vector3::operator*=(float rhs) | File: ../Math/Vector3.h | Line: 298
    engine->RegisterObjectMethod("Vector3", "Vector3& opMulAssign(float)", asMETHODPR(Vector3, operator*=, (float), Vector3 &), asCALL_THISCALL);
    // Vector3& Vector3::operator*=(const Vector3 &rhs) | File: ../Math/Vector3.h | Line: 307
    engine->RegisterObjectMethod("Vector3", "Vector3& opMulAssign(const Vector3&in)", asMETHODPR(Vector3, operator*=, (const Vector3 &), Vector3 &), asCALL_THISCALL);
    // Vector3 Vector3::operator+(const Vector3 &rhs) const | File: ../Math/Vector3.h | Line: 259
    engine->RegisterObjectMethod("Vector3", "Vector3 opAdd(const Vector3&in) const", asMETHODPR(Vector3, operator+, (const Vector3 &) const, Vector3), asCALL_THISCALL);
    // Vector3& Vector3::operator+=(const Vector3 &rhs) | File: ../Math/Vector3.h | Line: 280
    engine->RegisterObjectMethod("Vector3", "Vector3& opAddAssign(const Vector3&in)", asMETHODPR(Vector3, operator+=, (const Vector3 &), Vector3 &), asCALL_THISCALL);
    // Vector3 Vector3::operator-() const | File: ../Math/Vector3.h | Line: 262
    engine->RegisterObjectMethod("Vector3", "Vector3 opNeg() const", asMETHODPR(Vector3, operator-, () const, Vector3), asCALL_THISCALL);
    // Vector3 Vector3::operator-(const Vector3 &rhs) const | File: ../Math/Vector3.h | Line: 265
    engine->RegisterObjectMethod("Vector3", "Vector3 opSub(const Vector3&in) const", asMETHODPR(Vector3, operator-, (const Vector3 &) const, Vector3), asCALL_THISCALL);
    // Vector3& Vector3::operator-=(const Vector3 &rhs) | File: ../Math/Vector3.h | Line: 289
    engine->RegisterObjectMethod("Vector3", "Vector3& opSubAssign(const Vector3&in)", asMETHODPR(Vector3, operator-=, (const Vector3 &), Vector3 &), asCALL_THISCALL);
    // Vector3 Vector3::operator/(float rhs) const | File: ../Math/Vector3.h | Line: 274
    engine->RegisterObjectMethod("Vector3", "Vector3 opDiv(float) const", asMETHODPR(Vector3, operator/, (float) const, Vector3), asCALL_THISCALL);
    // Vector3 Vector3::operator/(const Vector3 &rhs) const | File: ../Math/Vector3.h | Line: 277
    engine->RegisterObjectMethod("Vector3", "Vector3 opDiv(const Vector3&in) const", asMETHODPR(Vector3, operator/, (const Vector3 &) const, Vector3), asCALL_THISCALL);
    // Vector3& Vector3::operator/=(float rhs) | File: ../Math/Vector3.h | Line: 316
    engine->RegisterObjectMethod("Vector3", "Vector3& opDivAssign(float)", asMETHODPR(Vector3, operator/=, (float), Vector3 &), asCALL_THISCALL);
    // Vector3& Vector3::operator/=(const Vector3 &rhs) | File: ../Math/Vector3.h | Line: 326
    engine->RegisterObjectMethod("Vector3", "Vector3& opDivAssign(const Vector3&in)", asMETHODPR(Vector3, operator/=, (const Vector3 &), Vector3 &), asCALL_THISCALL);
    // Vector3& Vector3::operator=(const Vector3 &rhs) noexcept=default | File: ../Math/Vector3.h | Line: 250
    engine->RegisterObjectMethod("Vector3", "Vector3& opAssign(const Vector3&in)", asMETHODPR(Vector3, operator=, (const Vector3 &), Vector3 &), asCALL_THISCALL);
    // bool Vector3::operator==(const Vector3 &rhs) const | File: ../Math/Vector3.h | Line: 253
    engine->RegisterObjectMethod("Vector3", "bool opEquals(const Vector3&in) const", asMETHODPR(Vector3, operator==, (const Vector3 &) const, bool), asCALL_THISCALL);
    // Vector3 Vector3::Orthogonalize(const Vector3 &axis) const | File: ../Math/Vector3.h | Line: 394
    engine->RegisterObjectMethod("Vector3", "Vector3 Orthogonalize(const Vector3&in) const", asMETHODPR(Vector3, Orthogonalize, (const Vector3 &) const, Vector3), asCALL_THISCALL);
    // float Vector3::ProjectOntoAxis(const Vector3 &axis) const | File: ../Math/Vector3.h | Line: 365
    engine->RegisterObjectMethod("Vector3", "float ProjectOntoAxis(const Vector3&in) const", asMETHODPR(Vector3, ProjectOntoAxis, (const Vector3 &) const, float), asCALL_THISCALL);
    // Vector3 Vector3::ProjectOntoLine(const Vector3 &from, const Vector3 &to, bool clamped=false) const | File: ../Math/Vector3.h | Line: 375
    engine->RegisterObjectMethod("Vector3", "Vector3 ProjectOntoLine(const Vector3&in, const Vector3&in, bool) const", asMETHODPR(Vector3, ProjectOntoLine, (const Vector3 &, const Vector3 &, bool) const, Vector3), asCALL_THISCALL);
    // Vector3 Vector3::ProjectOntoPlane(const Vector3 &origin, const Vector3 &normal) const | File: ../Math/Vector3.h | Line: 368
    engine->RegisterObjectMethod("Vector3", "Vector3 ProjectOntoPlane(const Vector3&in, const Vector3&in) const", asMETHODPR(Vector3, ProjectOntoPlane, (const Vector3 &, const Vector3 &) const, Vector3), asCALL_THISCALL);
    // Vector3 Vector3::ReNormalized(float minLength, float maxLength, const Vector3 &defaultValue=Vector3::ZERO, float eps=M_LARGE_EPSILON) const | File: ../Math/Vector3.h | Line: 450
    engine->RegisterObjectMethod("Vector3", "Vector3 ReNormalized(float, float, const Vector3&in, float) const", asMETHODPR(Vector3, ReNormalized, (float, float, const Vector3 &, float) const, Vector3), asCALL_THISCALL);
    // unsigned Vector3::ToHash() const | File: ../Math/Vector3.h | Line: 469
    engine->RegisterObjectMethod("Vector3", "uint ToHash() const", asMETHODPR(Vector3, ToHash, () const, unsigned), asCALL_THISCALL);
    // String Vector3::ToString() const | File: ../Math/Vector3.h | Line: 466
    engine->RegisterObjectMethod("Vector3", "String ToString() const", asMETHODPR(Vector3, ToString, () const, String), asCALL_THISCALL);
    // Vector3::Vector3() noexcept | File: ../Math/Vector3.h | Line: 190
    engine->RegisterObjectBehaviour("Vector3", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(Vector3_Vector3_190_5), asCALL_CDECL_OBJFIRST);
    // Vector3::Vector3(const Vector3 &vector) noexcept=default | File: ../Math/Vector3.h | Line: 198
    engine->RegisterObjectBehaviour("Vector3", asBEHAVE_CONSTRUCT, "void f(const Vector3&in)", asFUNCTION(Vector3_Vector3_198_5), asCALL_CDECL_OBJFIRST);
    // Vector3::Vector3(const Vector2 &vector, float z) noexcept | File: ../Math/Vector3.h | Line: 201
    engine->RegisterObjectBehaviour("Vector3", asBEHAVE_CONSTRUCT, "void f(const Vector2&in, float)", asFUNCTION(Vector3_Vector3_201_5), asCALL_CDECL_OBJFIRST);
    // Vector3::Vector3(const Vector2 &vector) noexcept | File: ../Math/Vector3.h | Line: 209
    engine->RegisterObjectBehaviour("Vector3", asBEHAVE_CONSTRUCT, "void f(const Vector2&in)", asFUNCTION(Vector3_Vector3_209_14), asCALL_CDECL_OBJFIRST);
    // Vector3::Vector3(const IntVector3 &vector) noexcept | File: ../Math/Vector3.h | Line: 217
    engine->RegisterObjectBehaviour("Vector3", asBEHAVE_CONSTRUCT, "void f(const IntVector3&in)", asFUNCTION(Vector3_Vector3_217_14), asCALL_CDECL_OBJFIRST);
    // Vector3::Vector3(float x, float y, float z) noexcept | File: ../Math/Vector3.h | Line: 225
    engine->RegisterObjectBehaviour("Vector3", asBEHAVE_CONSTRUCT, "void f(float, float, float)", asFUNCTION(Vector3_Vector3_225_5), asCALL_CDECL_OBJFIRST);
    // Vector3::Vector3(float x, float y) noexcept | File: ../Math/Vector3.h | Line: 233
    engine->RegisterObjectBehaviour("Vector3", asBEHAVE_CONSTRUCT, "void f(float, float)", asFUNCTION(Vector3_Vector3_233_5), asCALL_CDECL_OBJFIRST);

}

}
