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
#include "../Math/Frustum.h"
#include "../Math/MathDefs.h"
#include "../Math/Matrix2.h"
#include "../Math/Matrix3.h"
#include "../Math/Matrix3x4.h"
#include "../Math/Matrix4.h"
#include "../Math/Quaternion.h"
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
    // class IntVector2 | File: ../Math/Vector2.h | Line: 33
    engine->RegisterObjectType("IntVector2", sizeof(IntVector2), asOBJ_VALUE | asGetTypeTraits<IntVector2>() | asOBJ_POD | asOBJ_APP_CLASS_ALLINTS);
    // class IntVector3 | File: ../Math/Vector3.h | Line: 33
    engine->RegisterObjectType("IntVector3", sizeof(IntVector3), asOBJ_VALUE | asGetTypeTraits<IntVector3>() | asOBJ_POD | asOBJ_APP_CLASS_ALLINTS);
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
    // class Quaternion | File: ../Math/Quaternion.h | Line: 36
    engine->RegisterObjectType("Quaternion", sizeof(Quaternion), asOBJ_VALUE | asGetTypeTraits<Quaternion>() | asOBJ_POD | asOBJ_APP_CLASS_ALLFLOATS);
    // class Vector3 | File: ../Math/Vector3.h | Line: 187
    engine->RegisterObjectType("Vector3", sizeof(Vector3), asOBJ_VALUE | asGetTypeTraits<Vector3>() | asOBJ_POD | asOBJ_APP_CLASS_ALLFLOATS);

    // class IntVector2 | File: ../Math/Vector2.h | Line: 33
    // int x_
    engine->RegisterObjectProperty("IntVector2", "int x", offsetof(IntVector2, x_));
    // int y_
    engine->RegisterObjectProperty("IntVector2", "int y", offsetof(IntVector2, y_));
    // IntVector2() noexcept
    engine->RegisterObjectBehaviour("IntVector2", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(IntVector2_IntVector2_36_5), asCALL_CDECL_OBJFIRST);
    // IntVector2(int x, int y) noexcept
    engine->RegisterObjectBehaviour("IntVector2", asBEHAVE_CONSTRUCT, "void f(int, int)", asFUNCTION(IntVector2_IntVector2_43_5), asCALL_CDECL_OBJFIRST);
    // IntVector2(const IntVector2 &rhs) noexcept=default
    engine->RegisterObjectBehaviour("IntVector2", asBEHAVE_CONSTRUCT, "void f(const IntVector2&in)", asFUNCTION(IntVector2_IntVector2_65_5), asCALL_CDECL_OBJFIRST);
    // float Length() const
    engine->RegisterObjectMethod("IntVector2", "float Length() const", asMETHODPR(IntVector2, Length, () const, float), asCALL_THISCALL);
    // IntVector2 operator*(int rhs) const
    engine->RegisterObjectMethod("IntVector2", "IntVector2 opMul(int) const", asMETHODPR(IntVector2, operator*, (int) const, IntVector2), asCALL_THISCALL);
    // IntVector2 operator*(const IntVector2 &rhs) const
    engine->RegisterObjectMethod("IntVector2", "IntVector2 opMul(const IntVector2&in) const", asMETHODPR(IntVector2, operator*, (const IntVector2 &) const, IntVector2), asCALL_THISCALL);
    // IntVector2& operator*=(int rhs)
    engine->RegisterObjectMethod("IntVector2", "IntVector2& opMulAssign(int)", asMETHODPR(IntVector2, operator*=, (int), IntVector2 &), asCALL_THISCALL);
    // IntVector2& operator*=(const IntVector2 &rhs)
    engine->RegisterObjectMethod("IntVector2", "IntVector2& opMulAssign(const IntVector2&in)", asMETHODPR(IntVector2, operator*=, (const IntVector2 &), IntVector2 &), asCALL_THISCALL);
    // IntVector2 operator+(const IntVector2 &rhs) const
    engine->RegisterObjectMethod("IntVector2", "IntVector2 opAdd(const IntVector2&in) const", asMETHODPR(IntVector2, operator+, (const IntVector2 &) const, IntVector2), asCALL_THISCALL);
    // IntVector2& operator+=(const IntVector2 &rhs)
    engine->RegisterObjectMethod("IntVector2", "IntVector2& opAddAssign(const IntVector2&in)", asMETHODPR(IntVector2, operator+=, (const IntVector2 &), IntVector2 &), asCALL_THISCALL);
    // IntVector2 operator-() const
    engine->RegisterObjectMethod("IntVector2", "IntVector2 opNeg() const", asMETHODPR(IntVector2, operator-, () const, IntVector2), asCALL_THISCALL);
    // IntVector2 operator-(const IntVector2 &rhs) const
    engine->RegisterObjectMethod("IntVector2", "IntVector2 opSub(const IntVector2&in) const", asMETHODPR(IntVector2, operator-, (const IntVector2 &) const, IntVector2), asCALL_THISCALL);
    // IntVector2& operator-=(const IntVector2 &rhs)
    engine->RegisterObjectMethod("IntVector2", "IntVector2& opSubAssign(const IntVector2&in)", asMETHODPR(IntVector2, operator-=, (const IntVector2 &), IntVector2 &), asCALL_THISCALL);
    // IntVector2 operator/(int rhs) const
    engine->RegisterObjectMethod("IntVector2", "IntVector2 opDiv(int) const", asMETHODPR(IntVector2, operator/, (int) const, IntVector2), asCALL_THISCALL);
    // IntVector2 operator/(const IntVector2 &rhs) const
    engine->RegisterObjectMethod("IntVector2", "IntVector2 opDiv(const IntVector2&in) const", asMETHODPR(IntVector2, operator/, (const IntVector2 &) const, IntVector2), asCALL_THISCALL);
    // IntVector2& operator/=(int rhs)
    engine->RegisterObjectMethod("IntVector2", "IntVector2& opDivAssign(int)", asMETHODPR(IntVector2, operator/=, (int), IntVector2 &), asCALL_THISCALL);
    // IntVector2& operator/=(const IntVector2 &rhs)
    engine->RegisterObjectMethod("IntVector2", "IntVector2& opDivAssign(const IntVector2&in)", asMETHODPR(IntVector2, operator/=, (const IntVector2 &), IntVector2 &), asCALL_THISCALL);
    // IntVector2& operator=(const IntVector2 &rhs) noexcept=default
    engine->RegisterObjectMethod("IntVector2", "IntVector2& opAssign(const IntVector2&in)", asMETHODPR(IntVector2, operator=, (const IntVector2 &), IntVector2 &), asCALL_THISCALL);
    // bool operator==(const IntVector2 &rhs) const
    engine->RegisterObjectMethod("IntVector2", "bool opEquals(const IntVector2&in) const", asMETHODPR(IntVector2, operator==, (const IntVector2 &) const, bool), asCALL_THISCALL);
    // unsigned ToHash() const
    engine->RegisterObjectMethod("IntVector2", "uint ToHash() const", asMETHODPR(IntVector2, ToHash, () const, unsigned), asCALL_THISCALL);
    // String ToString() const
    engine->RegisterObjectMethod("IntVector2", "String ToString() const", asMETHODPR(IntVector2, ToString, () const, String), asCALL_THISCALL);

    // class IntVector3 | File: ../Math/Vector3.h | Line: 33
    // int x_
    engine->RegisterObjectProperty("IntVector3", "int x", offsetof(IntVector3, x_));
    // int y_
    engine->RegisterObjectProperty("IntVector3", "int y", offsetof(IntVector3, y_));
    // int z_
    engine->RegisterObjectProperty("IntVector3", "int z", offsetof(IntVector3, z_));
    // IntVector3() noexcept
    engine->RegisterObjectBehaviour("IntVector3", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(IntVector3_IntVector3_36_5), asCALL_CDECL_OBJFIRST);
    // IntVector3(int x, int y, int z) noexcept
    engine->RegisterObjectBehaviour("IntVector3", asBEHAVE_CONSTRUCT, "void f(int, int, int)", asFUNCTION(IntVector3_IntVector3_44_5), asCALL_CDECL_OBJFIRST);
    // IntVector3(const IntVector3 &rhs) noexcept=default
    engine->RegisterObjectBehaviour("IntVector3", asBEHAVE_CONSTRUCT, "void f(const IntVector3&in)", asFUNCTION(IntVector3_IntVector3_61_5), asCALL_CDECL_OBJFIRST);
    // float Length() const
    engine->RegisterObjectMethod("IntVector3", "float Length() const", asMETHODPR(IntVector3, Length, () const, float), asCALL_THISCALL);
    // IntVector3 operator*(int rhs) const
    engine->RegisterObjectMethod("IntVector3", "IntVector3 opMul(int) const", asMETHODPR(IntVector3, operator*, (int) const, IntVector3), asCALL_THISCALL);
    // IntVector3 operator*(const IntVector3 &rhs) const
    engine->RegisterObjectMethod("IntVector3", "IntVector3 opMul(const IntVector3&in) const", asMETHODPR(IntVector3, operator*, (const IntVector3 &) const, IntVector3), asCALL_THISCALL);
    // IntVector3& operator*=(int rhs)
    engine->RegisterObjectMethod("IntVector3", "IntVector3& opMulAssign(int)", asMETHODPR(IntVector3, operator*=, (int), IntVector3 &), asCALL_THISCALL);
    // IntVector3& operator*=(const IntVector3 &rhs)
    engine->RegisterObjectMethod("IntVector3", "IntVector3& opMulAssign(const IntVector3&in)", asMETHODPR(IntVector3, operator*=, (const IntVector3 &), IntVector3 &), asCALL_THISCALL);
    // IntVector3 operator+(const IntVector3 &rhs) const
    engine->RegisterObjectMethod("IntVector3", "IntVector3 opAdd(const IntVector3&in) const", asMETHODPR(IntVector3, operator+, (const IntVector3 &) const, IntVector3), asCALL_THISCALL);
    // IntVector3& operator+=(const IntVector3 &rhs)
    engine->RegisterObjectMethod("IntVector3", "IntVector3& opAddAssign(const IntVector3&in)", asMETHODPR(IntVector3, operator+=, (const IntVector3 &), IntVector3 &), asCALL_THISCALL);
    // IntVector3 operator-() const
    engine->RegisterObjectMethod("IntVector3", "IntVector3 opNeg() const", asMETHODPR(IntVector3, operator-, () const, IntVector3), asCALL_THISCALL);
    // IntVector3 operator-(const IntVector3 &rhs) const
    engine->RegisterObjectMethod("IntVector3", "IntVector3 opSub(const IntVector3&in) const", asMETHODPR(IntVector3, operator-, (const IntVector3 &) const, IntVector3), asCALL_THISCALL);
    // IntVector3& operator-=(const IntVector3 &rhs)
    engine->RegisterObjectMethod("IntVector3", "IntVector3& opSubAssign(const IntVector3&in)", asMETHODPR(IntVector3, operator-=, (const IntVector3 &), IntVector3 &), asCALL_THISCALL);
    // IntVector3 operator/(int rhs) const
    engine->RegisterObjectMethod("IntVector3", "IntVector3 opDiv(int) const", asMETHODPR(IntVector3, operator/, (int) const, IntVector3), asCALL_THISCALL);
    // IntVector3 operator/(const IntVector3 &rhs) const
    engine->RegisterObjectMethod("IntVector3", "IntVector3 opDiv(const IntVector3&in) const", asMETHODPR(IntVector3, operator/, (const IntVector3 &) const, IntVector3), asCALL_THISCALL);
    // IntVector3& operator/=(int rhs)
    engine->RegisterObjectMethod("IntVector3", "IntVector3& opDivAssign(int)", asMETHODPR(IntVector3, operator/=, (int), IntVector3 &), asCALL_THISCALL);
    // IntVector3& operator/=(const IntVector3 &rhs)
    engine->RegisterObjectMethod("IntVector3", "IntVector3& opDivAssign(const IntVector3&in)", asMETHODPR(IntVector3, operator/=, (const IntVector3 &), IntVector3 &), asCALL_THISCALL);
    // IntVector3& operator=(const IntVector3 &rhs) noexcept=default
    engine->RegisterObjectMethod("IntVector3", "IntVector3& opAssign(const IntVector3&in)", asMETHODPR(IntVector3, operator=, (const IntVector3 &), IntVector3 &), asCALL_THISCALL);
    // bool operator==(const IntVector3 &rhs) const
    engine->RegisterObjectMethod("IntVector3", "bool opEquals(const IntVector3&in) const", asMETHODPR(IntVector3, operator==, (const IntVector3 &) const, bool), asCALL_THISCALL);
    // unsigned ToHash() const
    engine->RegisterObjectMethod("IntVector3", "uint ToHash() const", asMETHODPR(IntVector3, ToHash, () const, unsigned), asCALL_THISCALL);
    // String ToString() const
    engine->RegisterObjectMethod("IntVector3", "String ToString() const", asMETHODPR(IntVector3, ToString, () const, String), asCALL_THISCALL);

    // class Vector2 | File: ../Math/Vector2.h | Line: 179
    // float x_
    engine->RegisterObjectProperty("Vector2", "float x", offsetof(Vector2, x_));
    // float y_
    engine->RegisterObjectProperty("Vector2", "float y", offsetof(Vector2, y_));
    // Vector2 Abs() const
    engine->RegisterObjectMethod("Vector2", "Vector2 Abs() const", asMETHODPR(Vector2, Abs, () const, Vector2), asCALL_THISCALL);
    // float AbsDotProduct(const Vector2 &rhs) const
    engine->RegisterObjectMethod("Vector2", "float AbsDotProduct(const Vector2&in) const", asMETHODPR(Vector2, AbsDotProduct, (const Vector2 &) const, float), asCALL_THISCALL);
    // float Angle(const Vector2 &rhs) const
    engine->RegisterObjectMethod("Vector2", "float Angle(const Vector2&in) const", asMETHODPR(Vector2, Angle, (const Vector2 &) const, float), asCALL_THISCALL);
    // float DotProduct(const Vector2 &rhs) const
    engine->RegisterObjectMethod("Vector2", "float DotProduct(const Vector2&in) const", asMETHODPR(Vector2, DotProduct, (const Vector2 &) const, float), asCALL_THISCALL);
    // bool Equals(const Vector2 &rhs) const
    engine->RegisterObjectMethod("Vector2", "bool Equals(const Vector2&in) const", asMETHODPR(Vector2, Equals, (const Vector2 &) const, bool), asCALL_THISCALL);
    // bool IsInf() const
    engine->RegisterObjectMethod("Vector2", "bool IsInf() const", asMETHODPR(Vector2, IsInf, () const, bool), asCALL_THISCALL);
    // bool IsNaN() const
    engine->RegisterObjectMethod("Vector2", "bool IsNaN() const", asMETHODPR(Vector2, IsNaN, () const, bool), asCALL_THISCALL);
    // float Length() const
    engine->RegisterObjectMethod("Vector2", "float get_length() const", asMETHODPR(Vector2, Length, () const, float), asCALL_THISCALL);
    // float LengthSquared() const
    engine->RegisterObjectMethod("Vector2", "float get_lengthSquared() const", asMETHODPR(Vector2, LengthSquared, () const, float), asCALL_THISCALL);
    // Vector2 Lerp(const Vector2 &rhs, float t) const
    engine->RegisterObjectMethod("Vector2", "Vector2 Lerp(const Vector2&in, float) const", asMETHODPR(Vector2, Lerp, (const Vector2 &, float) const, Vector2), asCALL_THISCALL);
    // void Normalize()
    engine->RegisterObjectMethod("Vector2", "void Normalize()", asMETHODPR(Vector2, Normalize, (), void), asCALL_THISCALL);
    // Vector2 Normalized() const
    engine->RegisterObjectMethod("Vector2", "Vector2 Normalized() const", asMETHODPR(Vector2, Normalized, () const, Vector2), asCALL_THISCALL);
    // Vector2 NormalizedOrDefault(const Vector2 &defaultValue=Vector2::ZERO, float eps=M_LARGE_EPSILON) const
    engine->RegisterObjectMethod("Vector2", "Vector2 NormalizedOrDefault(const Vector2&in, float) const", asMETHODPR(Vector2, NormalizedOrDefault, (const Vector2 &, float) const, Vector2), asCALL_THISCALL);
    // Vector2 operator*(float rhs) const
    engine->RegisterObjectMethod("Vector2", "Vector2 opMul(float) const", asMETHODPR(Vector2, operator*, (float) const, Vector2), asCALL_THISCALL);
    // Vector2 operator*(const Vector2 &rhs) const
    engine->RegisterObjectMethod("Vector2", "Vector2 opMul(const Vector2&in) const", asMETHODPR(Vector2, operator*, (const Vector2 &) const, Vector2), asCALL_THISCALL);
    // Vector2& operator*=(float rhs)
    engine->RegisterObjectMethod("Vector2", "Vector2& opMulAssign(float)", asMETHODPR(Vector2, operator*=, (float), Vector2 &), asCALL_THISCALL);
    // Vector2& operator*=(const Vector2 &rhs)
    engine->RegisterObjectMethod("Vector2", "Vector2& opMulAssign(const Vector2&in)", asMETHODPR(Vector2, operator*=, (const Vector2 &), Vector2 &), asCALL_THISCALL);
    // Vector2 operator+(const Vector2 &rhs) const
    engine->RegisterObjectMethod("Vector2", "Vector2 opAdd(const Vector2&in) const", asMETHODPR(Vector2, operator+, (const Vector2 &) const, Vector2), asCALL_THISCALL);
    // Vector2& operator+=(const Vector2 &rhs)
    engine->RegisterObjectMethod("Vector2", "Vector2& opAddAssign(const Vector2&in)", asMETHODPR(Vector2, operator+=, (const Vector2 &), Vector2 &), asCALL_THISCALL);
    // Vector2 operator-() const
    engine->RegisterObjectMethod("Vector2", "Vector2 opNeg() const", asMETHODPR(Vector2, operator-, () const, Vector2), asCALL_THISCALL);
    // Vector2 operator-(const Vector2 &rhs) const
    engine->RegisterObjectMethod("Vector2", "Vector2 opSub(const Vector2&in) const", asMETHODPR(Vector2, operator-, (const Vector2 &) const, Vector2), asCALL_THISCALL);
    // Vector2& operator-=(const Vector2 &rhs)
    engine->RegisterObjectMethod("Vector2", "Vector2& opSubAssign(const Vector2&in)", asMETHODPR(Vector2, operator-=, (const Vector2 &), Vector2 &), asCALL_THISCALL);
    // Vector2 operator/(float rhs) const
    engine->RegisterObjectMethod("Vector2", "Vector2 opDiv(float) const", asMETHODPR(Vector2, operator/, (float) const, Vector2), asCALL_THISCALL);
    // Vector2 operator/(const Vector2 &rhs) const
    engine->RegisterObjectMethod("Vector2", "Vector2 opDiv(const Vector2&in) const", asMETHODPR(Vector2, operator/, (const Vector2 &) const, Vector2), asCALL_THISCALL);
    // Vector2& operator/=(float rhs)
    engine->RegisterObjectMethod("Vector2", "Vector2& opDivAssign(float)", asMETHODPR(Vector2, operator/=, (float), Vector2 &), asCALL_THISCALL);
    // Vector2& operator/=(const Vector2 &rhs)
    engine->RegisterObjectMethod("Vector2", "Vector2& opDivAssign(const Vector2&in)", asMETHODPR(Vector2, operator/=, (const Vector2 &), Vector2 &), asCALL_THISCALL);
    // Vector2& operator=(const Vector2 &rhs) noexcept=default
    engine->RegisterObjectMethod("Vector2", "Vector2& opAssign(const Vector2&in)", asMETHODPR(Vector2, operator=, (const Vector2 &), Vector2 &), asCALL_THISCALL);
    // bool operator==(const Vector2 &rhs) const
    engine->RegisterObjectMethod("Vector2", "bool opEquals(const Vector2&in) const", asMETHODPR(Vector2, operator==, (const Vector2 &) const, bool), asCALL_THISCALL);
    // float ProjectOntoAxis(const Vector2 &axis) const
    engine->RegisterObjectMethod("Vector2", "float ProjectOntoAxis(const Vector2&in) const", asMETHODPR(Vector2, ProjectOntoAxis, (const Vector2 &) const, float), asCALL_THISCALL);
    // Vector2 ReNormalized(float minLength, float maxLength, const Vector2 &defaultValue=Vector2::ZERO, float eps=M_LARGE_EPSILON) const
    engine->RegisterObjectMethod("Vector2", "Vector2 ReNormalized(float, float, const Vector2&in, float) const", asMETHODPR(Vector2, ReNormalized, (float, float, const Vector2 &, float) const, Vector2), asCALL_THISCALL);
    // String ToString() const
    engine->RegisterObjectMethod("Vector2", "String ToString() const", asMETHODPR(Vector2, ToString, () const, String), asCALL_THISCALL);
    // Vector2() noexcept
    engine->RegisterObjectBehaviour("Vector2", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(Vector2_Vector2_182_5), asCALL_CDECL_OBJFIRST);
    // Vector2(const Vector2 &vector) noexcept=default
    engine->RegisterObjectBehaviour("Vector2", asBEHAVE_CONSTRUCT, "void f(const Vector2&in)", asFUNCTION(Vector2_Vector2_189_5), asCALL_CDECL_OBJFIRST);
    // Vector2(const IntVector2 &vector) noexcept
    engine->RegisterObjectBehaviour("Vector2", asBEHAVE_CONSTRUCT, "void f(const IntVector2&in)", asFUNCTION(Vector2_Vector2_192_14), asCALL_CDECL_OBJFIRST);
    // Vector2(float x, float y) noexcept
    engine->RegisterObjectBehaviour("Vector2", asBEHAVE_CONSTRUCT, "void f(float, float)", asFUNCTION(Vector2_Vector2_199_5), asCALL_CDECL_OBJFIRST);

    // class Matrix2 | File: ../Math/Matrix2.h | Line: 32
    // float m00_
    engine->RegisterObjectProperty("Matrix2", "float m00", offsetof(Matrix2, m00_));
    // float m01_
    engine->RegisterObjectProperty("Matrix2", "float m01", offsetof(Matrix2, m01_));
    // float m10_
    engine->RegisterObjectProperty("Matrix2", "float m10", offsetof(Matrix2, m10_));
    // float m11_
    engine->RegisterObjectProperty("Matrix2", "float m11", offsetof(Matrix2, m11_));
    // bool Equals(const Matrix2 &rhs) const
    engine->RegisterObjectMethod("Matrix2", "bool Equals(const Matrix2&in) const", asMETHODPR(Matrix2, Equals, (const Matrix2 &) const, bool), asCALL_THISCALL);
    // Matrix2 Inverse() const
    engine->RegisterObjectMethod("Matrix2", "Matrix2 Inverse() const", asMETHODPR(Matrix2, Inverse, () const, Matrix2), asCALL_THISCALL);
    // bool IsInf() const
    engine->RegisterObjectMethod("Matrix2", "bool IsInf() const", asMETHODPR(Matrix2, IsInf, () const, bool), asCALL_THISCALL);
    // bool IsNaN() const
    engine->RegisterObjectMethod("Matrix2", "bool IsNaN() const", asMETHODPR(Matrix2, IsNaN, () const, bool), asCALL_THISCALL);
    // Matrix2() noexcept
    engine->RegisterObjectBehaviour("Matrix2", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(Matrix2_Matrix2_35_5), asCALL_CDECL_OBJFIRST);
    // Matrix2(const Matrix2 &matrix) noexcept=default
    engine->RegisterObjectBehaviour("Matrix2", asBEHAVE_CONSTRUCT, "void f(const Matrix2&in)", asFUNCTION(Matrix2_Matrix2_44_5), asCALL_CDECL_OBJFIRST);
    // Matrix2(float v00, float v01, float v10, float v11) noexcept
    engine->RegisterObjectBehaviour("Matrix2", asBEHAVE_CONSTRUCT, "void f(float, float, float, float)", asFUNCTION(Matrix2_Matrix2_47_5), asCALL_CDECL_OBJFIRST);
    // Vector2 operator*(const Vector2 &rhs) const
    engine->RegisterObjectMethod("Matrix2", "Vector2 opMul(const Vector2&in) const", asMETHODPR(Matrix2, operator*, (const Vector2 &) const, Vector2), asCALL_THISCALL);
    // Matrix2 operator*(float rhs) const
    engine->RegisterObjectMethod("Matrix2", "Matrix2 opMul(float) const", asMETHODPR(Matrix2, operator*, (float) const, Matrix2), asCALL_THISCALL);
    // Matrix2 operator*(const Matrix2 &rhs) const
    engine->RegisterObjectMethod("Matrix2", "Matrix2 opMul(const Matrix2&in) const", asMETHODPR(Matrix2, operator*, (const Matrix2 &) const, Matrix2), asCALL_THISCALL);
    // Matrix2 operator+(const Matrix2 &rhs) const
    engine->RegisterObjectMethod("Matrix2", "Matrix2 opAdd(const Matrix2&in) const", asMETHODPR(Matrix2, operator+, (const Matrix2 &) const, Matrix2), asCALL_THISCALL);
    // Matrix2 operator-(const Matrix2 &rhs) const
    engine->RegisterObjectMethod("Matrix2", "Matrix2 opSub(const Matrix2&in) const", asMETHODPR(Matrix2, operator-, (const Matrix2 &) const, Matrix2), asCALL_THISCALL);
    // Matrix2& operator=(const Matrix2 &rhs) noexcept=default
    engine->RegisterObjectMethod("Matrix2", "Matrix2& opAssign(const Matrix2&in)", asMETHODPR(Matrix2, operator=, (const Matrix2 &), Matrix2 &), asCALL_THISCALL);
    // bool operator==(const Matrix2 &rhs) const
    engine->RegisterObjectMethod("Matrix2", "bool opEquals(const Matrix2&in) const", asMETHODPR(Matrix2, operator==, (const Matrix2 &) const, bool), asCALL_THISCALL);
    // Vector2 Scale() const
    engine->RegisterObjectMethod("Matrix2", "Vector2 Scale() const", asMETHODPR(Matrix2, Scale, () const, Vector2), asCALL_THISCALL);
    // Matrix2 Scaled(const Vector2 &scale) const
    engine->RegisterObjectMethod("Matrix2", "Matrix2 Scaled(const Vector2&in) const", asMETHODPR(Matrix2, Scaled, (const Vector2 &) const, Matrix2), asCALL_THISCALL);
    // void SetScale(const Vector2 &scale)
    engine->RegisterObjectMethod("Matrix2", "void SetScale(const Vector2&in)", asMETHODPR(Matrix2, SetScale, (const Vector2 &), void), asCALL_THISCALL);
    // void SetScale(float scale)
    engine->RegisterObjectMethod("Matrix2", "void SetScale(float)", asMETHODPR(Matrix2, SetScale, (float), void), asCALL_THISCALL);
    // String ToString() const
    engine->RegisterObjectMethod("Matrix2", "String ToString() const", asMETHODPR(Matrix2, ToString, () const, String), asCALL_THISCALL);
    // Matrix2 Transpose() const
    engine->RegisterObjectMethod("Matrix2", "Matrix2 Transpose() const", asMETHODPR(Matrix2, Transpose, () const, Matrix2), asCALL_THISCALL);

    // class Matrix3 | File: ../Math/Matrix3.h | Line: 32
    // float m00_
    engine->RegisterObjectProperty("Matrix3", "float m00", offsetof(Matrix3, m00_));
    // float m01_
    engine->RegisterObjectProperty("Matrix3", "float m01", offsetof(Matrix3, m01_));
    // float m02_
    engine->RegisterObjectProperty("Matrix3", "float m02", offsetof(Matrix3, m02_));
    // float m10_
    engine->RegisterObjectProperty("Matrix3", "float m10", offsetof(Matrix3, m10_));
    // float m11_
    engine->RegisterObjectProperty("Matrix3", "float m11", offsetof(Matrix3, m11_));
    // float m12_
    engine->RegisterObjectProperty("Matrix3", "float m12", offsetof(Matrix3, m12_));
    // float m20_
    engine->RegisterObjectProperty("Matrix3", "float m20", offsetof(Matrix3, m20_));
    // float m21_
    engine->RegisterObjectProperty("Matrix3", "float m21", offsetof(Matrix3, m21_));
    // float m22_
    engine->RegisterObjectProperty("Matrix3", "float m22", offsetof(Matrix3, m22_));
    // Vector3 Column(unsigned j) const
    engine->RegisterObjectMethod("Matrix3", "Vector3 Column(uint) const", asMETHODPR(Matrix3, Column, (unsigned) const, Vector3), asCALL_THISCALL);
    // float Element(unsigned i, unsigned j) const
    engine->RegisterObjectMethod("Matrix3", "float Element(uint, uint) const", asMETHODPR(Matrix3, Element, (unsigned, unsigned) const, float), asCALL_THISCALL);
    // bool Equals(const Matrix3 &rhs) const
    engine->RegisterObjectMethod("Matrix3", "bool Equals(const Matrix3&in) const", asMETHODPR(Matrix3, Equals, (const Matrix3 &) const, bool), asCALL_THISCALL);
    // Matrix3 Inverse() const
    engine->RegisterObjectMethod("Matrix3", "Matrix3 Inverse() const", asMETHODPR(Matrix3, Inverse, () const, Matrix3), asCALL_THISCALL);
    // bool IsInf() const
    engine->RegisterObjectMethod("Matrix3", "bool IsInf() const", asMETHODPR(Matrix3, IsInf, () const, bool), asCALL_THISCALL);
    // bool IsNaN() const
    engine->RegisterObjectMethod("Matrix3", "bool IsNaN() const", asMETHODPR(Matrix3, IsNaN, () const, bool), asCALL_THISCALL);
    // Matrix3() noexcept
    engine->RegisterObjectBehaviour("Matrix3", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(Matrix3_Matrix3_35_5), asCALL_CDECL_OBJFIRST);
    // Matrix3(const Matrix3 &matrix) noexcept=default
    engine->RegisterObjectBehaviour("Matrix3", asBEHAVE_CONSTRUCT, "void f(const Matrix3&in)", asFUNCTION(Matrix3_Matrix3_49_5), asCALL_CDECL_OBJFIRST);
    // Matrix3(float v00, float v01, float v02, float v10, float v11, float v12, float v20, float v21, float v22) noexcept
    engine->RegisterObjectBehaviour("Matrix3", asBEHAVE_CONSTRUCT, "void f(float, float, float, float, float, float, float, float, float)", asFUNCTION(Matrix3_Matrix3_52_5), asCALL_CDECL_OBJFIRST);
    // Vector3 operator*(const Vector3 &rhs) const
    engine->RegisterObjectMethod("Matrix3", "Vector3 opMul(const Vector3&in) const", asMETHODPR(Matrix3, operator*, (const Vector3 &) const, Vector3), asCALL_THISCALL);
    // Matrix3 operator*(float rhs) const
    engine->RegisterObjectMethod("Matrix3", "Matrix3 opMul(float) const", asMETHODPR(Matrix3, operator*, (float) const, Matrix3), asCALL_THISCALL);
    // Matrix3 operator*(const Matrix3 &rhs) const
    engine->RegisterObjectMethod("Matrix3", "Matrix3 opMul(const Matrix3&in) const", asMETHODPR(Matrix3, operator*, (const Matrix3 &) const, Matrix3), asCALL_THISCALL);
    // Matrix3 operator+(const Matrix3 &rhs) const
    engine->RegisterObjectMethod("Matrix3", "Matrix3 opAdd(const Matrix3&in) const", asMETHODPR(Matrix3, operator+, (const Matrix3 &) const, Matrix3), asCALL_THISCALL);
    // Matrix3 operator-(const Matrix3 &rhs) const
    engine->RegisterObjectMethod("Matrix3", "Matrix3 opSub(const Matrix3&in) const", asMETHODPR(Matrix3, operator-, (const Matrix3 &) const, Matrix3), asCALL_THISCALL);
    // Matrix3& operator=(const Matrix3 &rhs) noexcept=default
    engine->RegisterObjectMethod("Matrix3", "Matrix3& opAssign(const Matrix3&in)", asMETHODPR(Matrix3, operator=, (const Matrix3 &), Matrix3 &), asCALL_THISCALL);
    // bool operator==(const Matrix3 &rhs) const
    engine->RegisterObjectMethod("Matrix3", "bool opEquals(const Matrix3&in) const", asMETHODPR(Matrix3, operator==, (const Matrix3 &) const, bool), asCALL_THISCALL);
    // Vector3 Row(unsigned i) const
    engine->RegisterObjectMethod("Matrix3", "Vector3 Row(uint) const", asMETHODPR(Matrix3, Row, (unsigned) const, Vector3), asCALL_THISCALL);
    // Vector3 Scale() const
    engine->RegisterObjectMethod("Matrix3", "Vector3 Scale() const", asMETHODPR(Matrix3, Scale, () const, Vector3), asCALL_THISCALL);
    // Matrix3 Scaled(const Vector3 &scale) const
    engine->RegisterObjectMethod("Matrix3", "Matrix3 Scaled(const Vector3&in) const", asMETHODPR(Matrix3, Scaled, (const Vector3 &) const, Matrix3), asCALL_THISCALL);
    // void SetScale(const Vector3 &scale)
    engine->RegisterObjectMethod("Matrix3", "void SetScale(const Vector3&in)", asMETHODPR(Matrix3, SetScale, (const Vector3 &), void), asCALL_THISCALL);
    // void SetScale(float scale)
    engine->RegisterObjectMethod("Matrix3", "void SetScale(float)", asMETHODPR(Matrix3, SetScale, (float), void), asCALL_THISCALL);
    // Vector3 SignedScale(const Matrix3 &rotation) const
    engine->RegisterObjectMethod("Matrix3", "Vector3 SignedScale(const Matrix3&in) const", asMETHODPR(Matrix3, SignedScale, (const Matrix3 &) const, Vector3), asCALL_THISCALL);
    // String ToString() const
    engine->RegisterObjectMethod("Matrix3", "String ToString() const", asMETHODPR(Matrix3, ToString, () const, String), asCALL_THISCALL);
    // Matrix3 Transpose() const
    engine->RegisterObjectMethod("Matrix3", "Matrix3 Transpose() const", asMETHODPR(Matrix3, Transpose, () const, Matrix3), asCALL_THISCALL);

    // class Matrix3x4 | File: ../Math/Matrix3x4.h | Line: 36
    // float m00_
    engine->RegisterObjectProperty("Matrix3x4", "float m00", offsetof(Matrix3x4, m00_));
    // float m01_
    engine->RegisterObjectProperty("Matrix3x4", "float m01", offsetof(Matrix3x4, m01_));
    // float m02_
    engine->RegisterObjectProperty("Matrix3x4", "float m02", offsetof(Matrix3x4, m02_));
    // float m03_
    engine->RegisterObjectProperty("Matrix3x4", "float m03", offsetof(Matrix3x4, m03_));
    // float m10_
    engine->RegisterObjectProperty("Matrix3x4", "float m10", offsetof(Matrix3x4, m10_));
    // float m11_
    engine->RegisterObjectProperty("Matrix3x4", "float m11", offsetof(Matrix3x4, m11_));
    // float m12_
    engine->RegisterObjectProperty("Matrix3x4", "float m12", offsetof(Matrix3x4, m12_));
    // float m13_
    engine->RegisterObjectProperty("Matrix3x4", "float m13", offsetof(Matrix3x4, m13_));
    // float m20_
    engine->RegisterObjectProperty("Matrix3x4", "float m20", offsetof(Matrix3x4, m20_));
    // float m21_
    engine->RegisterObjectProperty("Matrix3x4", "float m21", offsetof(Matrix3x4, m21_));
    // float m22_
    engine->RegisterObjectProperty("Matrix3x4", "float m22", offsetof(Matrix3x4, m22_));
    // float m23_
    engine->RegisterObjectProperty("Matrix3x4", "float m23", offsetof(Matrix3x4, m23_));
    // Vector3 Column(unsigned j) const
    engine->RegisterObjectMethod("Matrix3x4", "Vector3 Column(uint) const", asMETHODPR(Matrix3x4, Column, (unsigned) const, Vector3), asCALL_THISCALL);
    // void Decompose(Vector3 &translation, Quaternion &rotation, Vector3 &scale) const
    engine->RegisterObjectMethod("Matrix3x4", "void Decompose(Vector3&, Quaternion&, Vector3&) const", asMETHODPR(Matrix3x4, Decompose, (Vector3 &, Quaternion &, Vector3 &) const, void), asCALL_THISCALL);
    // float Element(unsigned i, unsigned j) const
    engine->RegisterObjectMethod("Matrix3x4", "float Element(uint, uint) const", asMETHODPR(Matrix3x4, Element, (unsigned, unsigned) const, float), asCALL_THISCALL);
    // bool Equals(const Matrix3x4 &rhs) const
    engine->RegisterObjectMethod("Matrix3x4", "bool Equals(const Matrix3x4&in) const", asMETHODPR(Matrix3x4, Equals, (const Matrix3x4 &) const, bool), asCALL_THISCALL);
    // Matrix3x4 Inverse() const
    engine->RegisterObjectMethod("Matrix3x4", "Matrix3x4 Inverse() const", asMETHODPR(Matrix3x4, Inverse, () const, Matrix3x4), asCALL_THISCALL);
    // bool IsInf() const
    engine->RegisterObjectMethod("Matrix3x4", "bool IsInf() const", asMETHODPR(Matrix3x4, IsInf, () const, bool), asCALL_THISCALL);
    // bool IsNaN() const
    engine->RegisterObjectMethod("Matrix3x4", "bool IsNaN() const", asMETHODPR(Matrix3x4, IsNaN, () const, bool), asCALL_THISCALL);
    // Matrix3x4() noexcept
    engine->RegisterObjectBehaviour("Matrix3x4", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(Matrix3x4_Matrix3x4_39_5), asCALL_CDECL_OBJFIRST);
    // Matrix3x4(const Matrix3x4 &matrix) noexcept=default
    engine->RegisterObjectBehaviour("Matrix3x4", asBEHAVE_CONSTRUCT, "void f(const Matrix3x4&in)", asFUNCTION(Matrix3x4_Matrix3x4_63_5), asCALL_CDECL_OBJFIRST);
    // Matrix3x4(const Matrix3 &matrix) noexcept
    engine->RegisterObjectBehaviour("Matrix3x4", asBEHAVE_CONSTRUCT, "void f(const Matrix3&in)", asFUNCTION(Matrix3x4_Matrix3x4_66_14), asCALL_CDECL_OBJFIRST);
    // Matrix3x4(const Matrix4 &matrix) noexcept
    engine->RegisterObjectBehaviour("Matrix3x4", asBEHAVE_CONSTRUCT, "void f(const Matrix4&in)", asFUNCTION(Matrix3x4_Matrix3x4_83_14), asCALL_CDECL_OBJFIRST);
    // Matrix3x4(float v00, float v01, float v02, float v03, float v10, float v11, float v12, float v13, float v20, float v21, float v22, float v23) noexcept
    engine->RegisterObjectBehaviour("Matrix3x4", asBEHAVE_CONSTRUCT, "void f(float, float, float, float, float, float, float, float, float, float, float, float)", asFUNCTION(Matrix3x4_Matrix3x4_107_5), asCALL_CDECL_OBJFIRST);
    // Matrix3x4(const Vector3 &translation, const Quaternion &rotation, float scale) noexcept
    engine->RegisterObjectBehaviour("Matrix3x4", asBEHAVE_CONSTRUCT, "void f(const Vector3&in, const Quaternion&in, float)", asFUNCTION(Matrix3x4_Matrix3x4_151_5), asCALL_CDECL_OBJFIRST);
    // Matrix3x4(const Vector3 &translation, const Quaternion &rotation, const Vector3 &scale) noexcept
    engine->RegisterObjectBehaviour("Matrix3x4", asBEHAVE_CONSTRUCT, "void f(const Vector3&in, const Quaternion&in, const Vector3&in)", asFUNCTION(Matrix3x4_Matrix3x4_165_5), asCALL_CDECL_OBJFIRST);
    // Vector3 operator*(const Vector3 &rhs) const
    engine->RegisterObjectMethod("Matrix3x4", "Vector3 opMul(const Vector3&in) const", asMETHODPR(Matrix3x4, operator*, (const Vector3 &) const, Vector3), asCALL_THISCALL);
    // Vector3 operator*(const Vector4 &rhs) const
    engine->RegisterObjectMethod("Matrix3x4", "Vector3 opMul(const Vector4&in) const", asMETHODPR(Matrix3x4, operator*, (const Vector4 &) const, Vector3), asCALL_THISCALL);
    // Matrix3x4 operator*(float rhs) const
    engine->RegisterObjectMethod("Matrix3x4", "Matrix3x4 opMul(float) const", asMETHODPR(Matrix3x4, operator*, (float) const, Matrix3x4), asCALL_THISCALL);
    // Matrix3x4 operator*(const Matrix3x4 &rhs) const
    engine->RegisterObjectMethod("Matrix3x4", "Matrix3x4 opMul(const Matrix3x4&in) const", asMETHODPR(Matrix3x4, operator*, (const Matrix3x4 &) const, Matrix3x4), asCALL_THISCALL);
    // Matrix4 operator*(const Matrix4 &rhs) const
    engine->RegisterObjectMethod("Matrix3x4", "Matrix4 opMul(const Matrix4&in) const", asMETHODPR(Matrix3x4, operator*, (const Matrix4 &) const, Matrix4), asCALL_THISCALL);
    // Matrix3x4 operator+(const Matrix3x4 &rhs) const
    engine->RegisterObjectMethod("Matrix3x4", "Matrix3x4 opAdd(const Matrix3x4&in) const", asMETHODPR(Matrix3x4, operator+, (const Matrix3x4 &) const, Matrix3x4), asCALL_THISCALL);
    // Matrix3x4 operator-(const Matrix3x4 &rhs) const
    engine->RegisterObjectMethod("Matrix3x4", "Matrix3x4 opSub(const Matrix3x4&in) const", asMETHODPR(Matrix3x4, operator-, (const Matrix3x4 &) const, Matrix3x4), asCALL_THISCALL);
    // Matrix3x4& operator=(const Matrix3x4 &rhs) noexcept=default
    engine->RegisterObjectMethod("Matrix3x4", "Matrix3x4& opAssign(const Matrix3x4&in)", asMETHODPR(Matrix3x4, operator=, (const Matrix3x4 &), Matrix3x4 &), asCALL_THISCALL);
    // Matrix3x4& operator=(const Matrix3 &rhs) noexcept
    engine->RegisterObjectMethod("Matrix3x4", "Matrix3x4& opAssign(const Matrix3&in)", asMETHODPR(Matrix3x4, operator=, (const Matrix3 &), Matrix3x4 &), asCALL_THISCALL);
    // Matrix3x4& operator=(const Matrix4 &rhs) noexcept
    engine->RegisterObjectMethod("Matrix3x4", "Matrix3x4& opAssign(const Matrix4&in)", asMETHODPR(Matrix3x4, operator=, (const Matrix4 &), Matrix3x4 &), asCALL_THISCALL);
    // bool operator==(const Matrix3x4 &rhs) const
    engine->RegisterObjectMethod("Matrix3x4", "bool opEquals(const Matrix3x4&in) const", asMETHODPR(Matrix3x4, operator==, (const Matrix3x4 &) const, bool), asCALL_THISCALL);
    // Quaternion Rotation() const
    engine->RegisterObjectMethod("Matrix3x4", "Quaternion Rotation() const", asMETHODPR(Matrix3x4, Rotation, () const, Quaternion), asCALL_THISCALL);
    // Matrix3 RotationMatrix() const
    engine->RegisterObjectMethod("Matrix3x4", "Matrix3 RotationMatrix() const", asMETHODPR(Matrix3x4, RotationMatrix, () const, Matrix3), asCALL_THISCALL);
    // Vector4 Row(unsigned i) const
    engine->RegisterObjectMethod("Matrix3x4", "Vector4 Row(uint) const", asMETHODPR(Matrix3x4, Row, (unsigned) const, Vector4), asCALL_THISCALL);
    // Vector3 Scale() const
    engine->RegisterObjectMethod("Matrix3x4", "Vector3 Scale() const", asMETHODPR(Matrix3x4, Scale, () const, Vector3), asCALL_THISCALL);
    // void SetRotation(const Matrix3 &rotation)
    engine->RegisterObjectMethod("Matrix3x4", "void SetRotation(const Matrix3&in)", asMETHODPR(Matrix3x4, SetRotation, (const Matrix3 &), void), asCALL_THISCALL);
    // void SetScale(const Vector3 &scale)
    engine->RegisterObjectMethod("Matrix3x4", "void SetScale(const Vector3&in)", asMETHODPR(Matrix3x4, SetScale, (const Vector3 &), void), asCALL_THISCALL);
    // void SetScale(float scale)
    engine->RegisterObjectMethod("Matrix3x4", "void SetScale(float)", asMETHODPR(Matrix3x4, SetScale, (float), void), asCALL_THISCALL);
    // void SetTranslation(const Vector3 &translation)
    engine->RegisterObjectMethod("Matrix3x4", "void SetTranslation(const Vector3&in)", asMETHODPR(Matrix3x4, SetTranslation, (const Vector3 &), void), asCALL_THISCALL);
    // Vector3 SignedScale(const Matrix3 &rotation) const
    engine->RegisterObjectMethod("Matrix3x4", "Vector3 SignedScale(const Matrix3&in) const", asMETHODPR(Matrix3x4, SignedScale, (const Matrix3 &) const, Vector3), asCALL_THISCALL);
    // Matrix3 ToMatrix3() const
    engine->RegisterObjectMethod("Matrix3x4", "Matrix3 ToMatrix3() const", asMETHODPR(Matrix3x4, ToMatrix3, () const, Matrix3), asCALL_THISCALL);
    // Matrix4 ToMatrix4() const
    engine->RegisterObjectMethod("Matrix3x4", "Matrix4 ToMatrix4() const", asMETHODPR(Matrix3x4, ToMatrix4, () const, Matrix4), asCALL_THISCALL);
    // String ToString() const
    engine->RegisterObjectMethod("Matrix3x4", "String ToString() const", asMETHODPR(Matrix3x4, ToString, () const, String), asCALL_THISCALL);
    // Vector3 Translation() const
    engine->RegisterObjectMethod("Matrix3x4", "Vector3 Translation() const", asMETHODPR(Matrix3x4, Translation, () const, Vector3), asCALL_THISCALL);

    // class Matrix4 | File: ../Math/Matrix4.h | Line: 39
    // float m00_
    engine->RegisterObjectProperty("Matrix4", "float m00", offsetof(Matrix4, m00_));
    // float m01_
    engine->RegisterObjectProperty("Matrix4", "float m01", offsetof(Matrix4, m01_));
    // float m02_
    engine->RegisterObjectProperty("Matrix4", "float m02", offsetof(Matrix4, m02_));
    // float m03_
    engine->RegisterObjectProperty("Matrix4", "float m03", offsetof(Matrix4, m03_));
    // float m10_
    engine->RegisterObjectProperty("Matrix4", "float m10", offsetof(Matrix4, m10_));
    // float m11_
    engine->RegisterObjectProperty("Matrix4", "float m11", offsetof(Matrix4, m11_));
    // float m12_
    engine->RegisterObjectProperty("Matrix4", "float m12", offsetof(Matrix4, m12_));
    // float m13_
    engine->RegisterObjectProperty("Matrix4", "float m13", offsetof(Matrix4, m13_));
    // float m20_
    engine->RegisterObjectProperty("Matrix4", "float m20", offsetof(Matrix4, m20_));
    // float m21_
    engine->RegisterObjectProperty("Matrix4", "float m21", offsetof(Matrix4, m21_));
    // float m22_
    engine->RegisterObjectProperty("Matrix4", "float m22", offsetof(Matrix4, m22_));
    // float m23_
    engine->RegisterObjectProperty("Matrix4", "float m23", offsetof(Matrix4, m23_));
    // float m30_
    engine->RegisterObjectProperty("Matrix4", "float m30", offsetof(Matrix4, m30_));
    // float m31_
    engine->RegisterObjectProperty("Matrix4", "float m31", offsetof(Matrix4, m31_));
    // float m32_
    engine->RegisterObjectProperty("Matrix4", "float m32", offsetof(Matrix4, m32_));
    // float m33_
    engine->RegisterObjectProperty("Matrix4", "float m33", offsetof(Matrix4, m33_));
    // Vector4 Column(unsigned j) const
    engine->RegisterObjectMethod("Matrix4", "Vector4 Column(uint) const", asMETHODPR(Matrix4, Column, (unsigned) const, Vector4), asCALL_THISCALL);
    // void Decompose(Vector3 &translation, Quaternion &rotation, Vector3 &scale) const
    engine->RegisterObjectMethod("Matrix4", "void Decompose(Vector3&, Quaternion&, Vector3&) const", asMETHODPR(Matrix4, Decompose, (Vector3 &, Quaternion &, Vector3 &) const, void), asCALL_THISCALL);
    // float Element(unsigned i, unsigned j) const
    engine->RegisterObjectMethod("Matrix4", "float Element(uint, uint) const", asMETHODPR(Matrix4, Element, (unsigned, unsigned) const, float), asCALL_THISCALL);
    // bool Equals(const Matrix4 &rhs) const
    engine->RegisterObjectMethod("Matrix4", "bool Equals(const Matrix4&in) const", asMETHODPR(Matrix4, Equals, (const Matrix4 &) const, bool), asCALL_THISCALL);
    // Matrix4 Inverse() const
    engine->RegisterObjectMethod("Matrix4", "Matrix4 Inverse() const", asMETHODPR(Matrix4, Inverse, () const, Matrix4), asCALL_THISCALL);
    // bool IsInf() const
    engine->RegisterObjectMethod("Matrix4", "bool IsInf() const", asMETHODPR(Matrix4, IsInf, () const, bool), asCALL_THISCALL);
    // bool IsNaN() const
    engine->RegisterObjectMethod("Matrix4", "bool IsNaN() const", asMETHODPR(Matrix4, IsNaN, () const, bool), asCALL_THISCALL);
    // Matrix4() noexcept
    engine->RegisterObjectBehaviour("Matrix4", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(Matrix4_Matrix4_42_5), asCALL_CDECL_OBJFIRST);
    // Matrix4(const Matrix4 &matrix) noexcept
    engine->RegisterObjectBehaviour("Matrix4", asBEHAVE_CONSTRUCT, "void f(const Matrix4&in)", asFUNCTION(Matrix4_Matrix4_71_5), asCALL_CDECL_OBJFIRST);
    // Matrix4(const Matrix3 &matrix) noexcept
    engine->RegisterObjectBehaviour("Matrix4", asBEHAVE_CONSTRUCT, "void f(const Matrix3&in)", asFUNCTION(Matrix4_Matrix4_100_14), asCALL_CDECL_OBJFIRST);
    // Matrix4(float v00, float v01, float v02, float v03, float v10, float v11, float v12, float v13, float v20, float v21, float v22, float v23, float v30, float v31, float v32, float v33) noexcept
    engine->RegisterObjectBehaviour("Matrix4", asBEHAVE_CONSTRUCT, "void f(float, float, float, float, float, float, float, float, float, float, float, float, float, float, float, float)", asFUNCTION(Matrix4_Matrix4_121_5), asCALL_CDECL_OBJFIRST);
    // Vector3 operator*(const Vector3 &rhs) const
    engine->RegisterObjectMethod("Matrix4", "Vector3 opMul(const Vector3&in) const", asMETHODPR(Matrix4, operator*, (const Vector3 &) const, Vector3), asCALL_THISCALL);
    // Vector4 operator*(const Vector4 &rhs) const
    engine->RegisterObjectMethod("Matrix4", "Vector4 opMul(const Vector4&in) const", asMETHODPR(Matrix4, operator*, (const Vector4 &) const, Vector4), asCALL_THISCALL);
    // Matrix4 operator*(float rhs) const
    engine->RegisterObjectMethod("Matrix4", "Matrix4 opMul(float) const", asMETHODPR(Matrix4, operator*, (float) const, Matrix4), asCALL_THISCALL);
    // Matrix4 operator*(const Matrix4 &rhs) const
    engine->RegisterObjectMethod("Matrix4", "Matrix4 opMul(const Matrix4&in) const", asMETHODPR(Matrix4, operator*, (const Matrix4 &) const, Matrix4), asCALL_THISCALL);
    // Matrix4 operator*(const Matrix3x4 &rhs) const
    engine->RegisterObjectMethod("Matrix4", "Matrix4 opMul(const Matrix3x4&in) const", asMETHODPR(Matrix4, operator*, (const Matrix3x4 &) const, Matrix4), asCALL_THISCALL);
    // Matrix4 operator+(const Matrix4 &rhs) const
    engine->RegisterObjectMethod("Matrix4", "Matrix4 opAdd(const Matrix4&in) const", asMETHODPR(Matrix4, operator+, (const Matrix4 &) const, Matrix4), asCALL_THISCALL);
    // Matrix4 operator-(const Matrix4 &rhs) const
    engine->RegisterObjectMethod("Matrix4", "Matrix4 opSub(const Matrix4&in) const", asMETHODPR(Matrix4, operator-, (const Matrix4 &) const, Matrix4), asCALL_THISCALL);
    // Matrix4& operator=(const Matrix4 &rhs) noexcept
    engine->RegisterObjectMethod("Matrix4", "Matrix4& opAssign(const Matrix4&in)", asMETHODPR(Matrix4, operator=, (const Matrix4 &), Matrix4 &), asCALL_THISCALL);
    // Matrix4& operator=(const Matrix3 &rhs) noexcept
    engine->RegisterObjectMethod("Matrix4", "Matrix4& opAssign(const Matrix3&in)", asMETHODPR(Matrix4, operator=, (const Matrix3 &), Matrix4 &), asCALL_THISCALL);
    // bool operator==(const Matrix4 &rhs) const
    engine->RegisterObjectMethod("Matrix4", "bool opEquals(const Matrix4&in) const", asMETHODPR(Matrix4, operator==, (const Matrix4 &) const, bool), asCALL_THISCALL);
    // Quaternion Rotation() const
    engine->RegisterObjectMethod("Matrix4", "Quaternion Rotation() const", asMETHODPR(Matrix4, Rotation, () const, Quaternion), asCALL_THISCALL);
    // Matrix3 RotationMatrix() const
    engine->RegisterObjectMethod("Matrix4", "Matrix3 RotationMatrix() const", asMETHODPR(Matrix4, RotationMatrix, () const, Matrix3), asCALL_THISCALL);
    // Vector4 Row(unsigned i) const
    engine->RegisterObjectMethod("Matrix4", "Vector4 Row(uint) const", asMETHODPR(Matrix4, Row, (unsigned) const, Vector4), asCALL_THISCALL);
    // Vector3 Scale() const
    engine->RegisterObjectMethod("Matrix4", "Vector3 Scale() const", asMETHODPR(Matrix4, Scale, () const, Vector3), asCALL_THISCALL);
    // void SetRotation(const Matrix3 &rotation)
    engine->RegisterObjectMethod("Matrix4", "void SetRotation(const Matrix3&in)", asMETHODPR(Matrix4, SetRotation, (const Matrix3 &), void), asCALL_THISCALL);
    // void SetScale(const Vector3 &scale)
    engine->RegisterObjectMethod("Matrix4", "void SetScale(const Vector3&in)", asMETHODPR(Matrix4, SetScale, (const Vector3 &), void), asCALL_THISCALL);
    // void SetScale(float scale)
    engine->RegisterObjectMethod("Matrix4", "void SetScale(float)", asMETHODPR(Matrix4, SetScale, (float), void), asCALL_THISCALL);
    // void SetTranslation(const Vector3 &translation)
    engine->RegisterObjectMethod("Matrix4", "void SetTranslation(const Vector3&in)", asMETHODPR(Matrix4, SetTranslation, (const Vector3 &), void), asCALL_THISCALL);
    // Vector3 SignedScale(const Matrix3 &rotation) const
    engine->RegisterObjectMethod("Matrix4", "Vector3 SignedScale(const Matrix3&in) const", asMETHODPR(Matrix4, SignedScale, (const Matrix3 &) const, Vector3), asCALL_THISCALL);
    // Matrix3 ToMatrix3() const
    engine->RegisterObjectMethod("Matrix4", "Matrix3 ToMatrix3() const", asMETHODPR(Matrix4, ToMatrix3, () const, Matrix3), asCALL_THISCALL);
    // String ToString() const
    engine->RegisterObjectMethod("Matrix4", "String ToString() const", asMETHODPR(Matrix4, ToString, () const, String), asCALL_THISCALL);
    // Vector3 Translation() const
    engine->RegisterObjectMethod("Matrix4", "Vector3 Translation() const", asMETHODPR(Matrix4, Translation, () const, Vector3), asCALL_THISCALL);
    // Matrix4 Transpose() const
    engine->RegisterObjectMethod("Matrix4", "Matrix4 Transpose() const", asMETHODPR(Matrix4, Transpose, () const, Matrix4), asCALL_THISCALL);

    // class Vector4 | File: ../Math/Vector4.h | Line: 32
    // float w_
    engine->RegisterObjectProperty("Vector4", "float w", offsetof(Vector4, w_));
    // float x_
    engine->RegisterObjectProperty("Vector4", "float x", offsetof(Vector4, x_));
    // float y_
    engine->RegisterObjectProperty("Vector4", "float y", offsetof(Vector4, y_));
    // float z_
    engine->RegisterObjectProperty("Vector4", "float z", offsetof(Vector4, z_));
    // Vector4 Abs() const
    engine->RegisterObjectMethod("Vector4", "Vector4 Abs() const", asMETHODPR(Vector4, Abs, () const, Vector4), asCALL_THISCALL);
    // float AbsDotProduct(const Vector4 &rhs) const
    engine->RegisterObjectMethod("Vector4", "float AbsDotProduct(const Vector4&in) const", asMETHODPR(Vector4, AbsDotProduct, (const Vector4 &) const, float), asCALL_THISCALL);
    // float DotProduct(const Vector4 &rhs) const
    engine->RegisterObjectMethod("Vector4", "float DotProduct(const Vector4&in) const", asMETHODPR(Vector4, DotProduct, (const Vector4 &) const, float), asCALL_THISCALL);
    // bool Equals(const Vector4 &rhs) const
    engine->RegisterObjectMethod("Vector4", "bool Equals(const Vector4&in) const", asMETHODPR(Vector4, Equals, (const Vector4 &) const, bool), asCALL_THISCALL);
    // bool IsInf() const
    engine->RegisterObjectMethod("Vector4", "bool IsInf() const", asMETHODPR(Vector4, IsInf, () const, bool), asCALL_THISCALL);
    // bool IsNaN() const
    engine->RegisterObjectMethod("Vector4", "bool IsNaN() const", asMETHODPR(Vector4, IsNaN, () const, bool), asCALL_THISCALL);
    // Vector4 Lerp(const Vector4 &rhs, float t) const
    engine->RegisterObjectMethod("Vector4", "Vector4 Lerp(const Vector4&in, float) const", asMETHODPR(Vector4, Lerp, (const Vector4 &, float) const, Vector4), asCALL_THISCALL);
    // operator Vector2() const
    engine->RegisterObjectMethod("Vector4", "Vector2 opConv() const", asMETHODPR(Vector4, operator Vector2, () const, Vector2), asCALL_THISCALL);
    // operator Vector3() const
    engine->RegisterObjectMethod("Vector4", "Vector3 opConv() const", asMETHODPR(Vector4, operator Vector3, () const, Vector3), asCALL_THISCALL);
    // Vector4 operator*(float rhs) const
    engine->RegisterObjectMethod("Vector4", "Vector4 opMul(float) const", asMETHODPR(Vector4, operator*, (float) const, Vector4), asCALL_THISCALL);
    // Vector4 operator*(const Vector4 &rhs) const
    engine->RegisterObjectMethod("Vector4", "Vector4 opMul(const Vector4&in) const", asMETHODPR(Vector4, operator*, (const Vector4 &) const, Vector4), asCALL_THISCALL);
    // Vector4& operator*=(float rhs)
    engine->RegisterObjectMethod("Vector4", "Vector4& opMulAssign(float)", asMETHODPR(Vector4, operator*=, (float), Vector4 &), asCALL_THISCALL);
    // Vector4& operator*=(const Vector4 &rhs)
    engine->RegisterObjectMethod("Vector4", "Vector4& opMulAssign(const Vector4&in)", asMETHODPR(Vector4, operator*=, (const Vector4 &), Vector4 &), asCALL_THISCALL);
    // Vector4 operator+(const Vector4 &rhs) const
    engine->RegisterObjectMethod("Vector4", "Vector4 opAdd(const Vector4&in) const", asMETHODPR(Vector4, operator+, (const Vector4 &) const, Vector4), asCALL_THISCALL);
    // Vector4& operator+=(const Vector4 &rhs)
    engine->RegisterObjectMethod("Vector4", "Vector4& opAddAssign(const Vector4&in)", asMETHODPR(Vector4, operator+=, (const Vector4 &), Vector4 &), asCALL_THISCALL);
    // Vector4 operator-() const
    engine->RegisterObjectMethod("Vector4", "Vector4 opNeg() const", asMETHODPR(Vector4, operator-, () const, Vector4), asCALL_THISCALL);
    // Vector4 operator-(const Vector4 &rhs) const
    engine->RegisterObjectMethod("Vector4", "Vector4 opSub(const Vector4&in) const", asMETHODPR(Vector4, operator-, (const Vector4 &) const, Vector4), asCALL_THISCALL);
    // Vector4& operator-=(const Vector4 &rhs)
    engine->RegisterObjectMethod("Vector4", "Vector4& opSubAssign(const Vector4&in)", asMETHODPR(Vector4, operator-=, (const Vector4 &), Vector4 &), asCALL_THISCALL);
    // Vector4 operator/(float rhs) const
    engine->RegisterObjectMethod("Vector4", "Vector4 opDiv(float) const", asMETHODPR(Vector4, operator/, (float) const, Vector4), asCALL_THISCALL);
    // Vector4 operator/(const Vector4 &rhs) const
    engine->RegisterObjectMethod("Vector4", "Vector4 opDiv(const Vector4&in) const", asMETHODPR(Vector4, operator/, (const Vector4 &) const, Vector4), asCALL_THISCALL);
    // Vector4& operator/=(float rhs)
    engine->RegisterObjectMethod("Vector4", "Vector4& opDivAssign(float)", asMETHODPR(Vector4, operator/=, (float), Vector4 &), asCALL_THISCALL);
    // Vector4& operator/=(const Vector4 &rhs)
    engine->RegisterObjectMethod("Vector4", "Vector4& opDivAssign(const Vector4&in)", asMETHODPR(Vector4, operator/=, (const Vector4 &), Vector4 &), asCALL_THISCALL);
    // Vector4& operator=(const Vector4 &rhs) noexcept=default
    engine->RegisterObjectMethod("Vector4", "Vector4& opAssign(const Vector4&in)", asMETHODPR(Vector4, operator=, (const Vector4 &), Vector4 &), asCALL_THISCALL);
    // bool operator==(const Vector4 &rhs) const
    engine->RegisterObjectMethod("Vector4", "bool opEquals(const Vector4&in) const", asMETHODPR(Vector4, operator==, (const Vector4 &) const, bool), asCALL_THISCALL);
    // float operator[](unsigned index) const
    engine->RegisterObjectMethod("Vector4", "float opIndex(uint) const", asMETHODPR(Vector4, operator[], (unsigned) const, float), asCALL_THISCALL);
    // float& operator[](unsigned index)
    engine->RegisterObjectMethod("Vector4", "float& opIndex(uint)", asMETHODPR(Vector4, operator[], (unsigned), float &), asCALL_THISCALL);
    // float ProjectOntoAxis(const Vector3 &axis) const
    engine->RegisterObjectMethod("Vector4", "float ProjectOntoAxis(const Vector3&in) const", asMETHODPR(Vector4, ProjectOntoAxis, (const Vector3 &) const, float), asCALL_THISCALL);
    // unsigned ToHash() const
    engine->RegisterObjectMethod("Vector4", "uint ToHash() const", asMETHODPR(Vector4, ToHash, () const, unsigned), asCALL_THISCALL);
    // String ToString() const
    engine->RegisterObjectMethod("Vector4", "String ToString() const", asMETHODPR(Vector4, ToString, () const, String), asCALL_THISCALL);
    // Vector4() noexcept
    engine->RegisterObjectBehaviour("Vector4", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(Vector4_Vector4_35_5), asCALL_CDECL_OBJFIRST);
    // Vector4(const Vector4 &vector) noexcept=default
    engine->RegisterObjectBehaviour("Vector4", asBEHAVE_CONSTRUCT, "void f(const Vector4&in)", asFUNCTION(Vector4_Vector4_44_5), asCALL_CDECL_OBJFIRST);
    // Vector4(const Vector3 &vector, float w) noexcept
    engine->RegisterObjectBehaviour("Vector4", asBEHAVE_CONSTRUCT, "void f(const Vector3&in, float)", asFUNCTION(Vector4_Vector4_47_5), asCALL_CDECL_OBJFIRST);
    // Vector4(float x, float y, float z, float w) noexcept
    engine->RegisterObjectBehaviour("Vector4", asBEHAVE_CONSTRUCT, "void f(float, float, float, float)", asFUNCTION(Vector4_Vector4_56_5), asCALL_CDECL_OBJFIRST);

    // class Quaternion | File: ../Math/Quaternion.h | Line: 36
    // float w_
    engine->RegisterObjectProperty("Quaternion", "float w", offsetof(Quaternion, w_));
    // float x_
    engine->RegisterObjectProperty("Quaternion", "float x", offsetof(Quaternion, x_));
    // float y_
    engine->RegisterObjectProperty("Quaternion", "float y", offsetof(Quaternion, y_));
    // float z_
    engine->RegisterObjectProperty("Quaternion", "float z", offsetof(Quaternion, z_));
    // float Angle() const
    engine->RegisterObjectMethod("Quaternion", "float get_angle() const", asMETHODPR(Quaternion, Angle, () const, float), asCALL_THISCALL);
    // Vector3 Axis() const
    engine->RegisterObjectMethod("Quaternion", "Vector3 get_axis() const", asMETHODPR(Quaternion, Axis, () const, Vector3), asCALL_THISCALL);
    // Quaternion Conjugate() const
    engine->RegisterObjectMethod("Quaternion", "Quaternion Conjugate() const", asMETHODPR(Quaternion, Conjugate, () const, Quaternion), asCALL_THISCALL);
    // float DotProduct(const Quaternion &rhs) const
    engine->RegisterObjectMethod("Quaternion", "float DotProduct(const Quaternion&in) const", asMETHODPR(Quaternion, DotProduct, (const Quaternion &) const, float), asCALL_THISCALL);
    // bool Equals(const Quaternion &rhs) const
    engine->RegisterObjectMethod("Quaternion", "bool Equals(const Quaternion&in) const", asMETHODPR(Quaternion, Equals, (const Quaternion &) const, bool), asCALL_THISCALL);
    // Vector3 EulerAngles() const
    engine->RegisterObjectMethod("Quaternion", "Vector3 get_eulerAngles() const", asMETHODPR(Quaternion, EulerAngles, () const, Vector3), asCALL_THISCALL);
    // void FromAngleAxis(float angle, const Vector3 &axis)
    engine->RegisterObjectMethod("Quaternion", "void FromAngleAxis(float, const Vector3&in)", asMETHODPR(Quaternion, FromAngleAxis, (float, const Vector3 &), void), asCALL_THISCALL);
    // void FromAxes(const Vector3 &xAxis, const Vector3 &yAxis, const Vector3 &zAxis)
    engine->RegisterObjectMethod("Quaternion", "void FromAxes(const Vector3&in, const Vector3&in, const Vector3&in)", asMETHODPR(Quaternion, FromAxes, (const Vector3 &, const Vector3 &, const Vector3 &), void), asCALL_THISCALL);
    // void FromEulerAngles(float x, float y, float z)
    engine->RegisterObjectMethod("Quaternion", "void FromEulerAngles(float, float, float)", asMETHODPR(Quaternion, FromEulerAngles, (float, float, float), void), asCALL_THISCALL);
    // bool FromLookRotation(const Vector3 &direction, const Vector3 &up=Vector3::UP)
    engine->RegisterObjectMethod("Quaternion", "bool FromLookRotation(const Vector3&in, const Vector3&in)", asMETHODPR(Quaternion, FromLookRotation, (const Vector3 &, const Vector3 &), bool), asCALL_THISCALL);
    // void FromRotationMatrix(const Matrix3 &matrix)
    engine->RegisterObjectMethod("Quaternion", "void FromRotationMatrix(const Matrix3&in)", asMETHODPR(Quaternion, FromRotationMatrix, (const Matrix3 &), void), asCALL_THISCALL);
    // void FromRotationTo(const Vector3 &start, const Vector3 &end)
    engine->RegisterObjectMethod("Quaternion", "void FromRotationTo(const Vector3&in, const Vector3&in)", asMETHODPR(Quaternion, FromRotationTo, (const Vector3 &, const Vector3 &), void), asCALL_THISCALL);
    // Quaternion Inverse() const
    engine->RegisterObjectMethod("Quaternion", "Quaternion Inverse() const", asMETHODPR(Quaternion, Inverse, () const, Quaternion), asCALL_THISCALL);
    // bool IsInf() const
    engine->RegisterObjectMethod("Quaternion", "bool IsInf() const", asMETHODPR(Quaternion, IsInf, () const, bool), asCALL_THISCALL);
    // bool IsNaN() const
    engine->RegisterObjectMethod("Quaternion", "bool IsNaN() const", asMETHODPR(Quaternion, IsNaN, () const, bool), asCALL_THISCALL);
    // float LengthSquared() const
    engine->RegisterObjectMethod("Quaternion", "float LengthSquared() const", asMETHODPR(Quaternion, LengthSquared, () const, float), asCALL_THISCALL);
    // Quaternion Nlerp(const Quaternion &rhs, float t, bool shortestPath=false) const
    engine->RegisterObjectMethod("Quaternion", "Quaternion Nlerp(const Quaternion&in, float, bool) const", asMETHODPR(Quaternion, Nlerp, (const Quaternion &, float, bool) const, Quaternion), asCALL_THISCALL);
    // void Normalize()
    engine->RegisterObjectMethod("Quaternion", "void Normalize()", asMETHODPR(Quaternion, Normalize, (), void), asCALL_THISCALL);
    // Quaternion Normalized() const
    engine->RegisterObjectMethod("Quaternion", "Quaternion Normalized() const", asMETHODPR(Quaternion, Normalized, () const, Quaternion), asCALL_THISCALL);
    // Quaternion operator*(float rhs) const
    engine->RegisterObjectMethod("Quaternion", "Quaternion opMul(float) const", asMETHODPR(Quaternion, operator*, (float) const, Quaternion), asCALL_THISCALL);
    // Quaternion operator*(const Quaternion &rhs) const
    engine->RegisterObjectMethod("Quaternion", "Quaternion opMul(const Quaternion&in) const", asMETHODPR(Quaternion, operator*, (const Quaternion &) const, Quaternion), asCALL_THISCALL);
    // Vector3 operator*(const Vector3 &rhs) const
    engine->RegisterObjectMethod("Quaternion", "Vector3 opMul(const Vector3&in) const", asMETHODPR(Quaternion, operator*, (const Vector3 &) const, Vector3), asCALL_THISCALL);
    // Quaternion& operator*=(float rhs)
    engine->RegisterObjectMethod("Quaternion", "Quaternion& opMulAssign(float)", asMETHODPR(Quaternion, operator*=, (float), Quaternion &), asCALL_THISCALL);
    // Quaternion operator+(const Quaternion &rhs) const
    engine->RegisterObjectMethod("Quaternion", "Quaternion opAdd(const Quaternion&in) const", asMETHODPR(Quaternion, operator+, (const Quaternion &) const, Quaternion), asCALL_THISCALL);
    // Quaternion& operator+=(const Quaternion &rhs)
    engine->RegisterObjectMethod("Quaternion", "Quaternion& opAddAssign(const Quaternion&in)", asMETHODPR(Quaternion, operator+=, (const Quaternion &), Quaternion &), asCALL_THISCALL);
    // Quaternion operator-() const
    engine->RegisterObjectMethod("Quaternion", "Quaternion opNeg() const", asMETHODPR(Quaternion, operator-, () const, Quaternion), asCALL_THISCALL);
    // Quaternion operator-(const Quaternion &rhs) const
    engine->RegisterObjectMethod("Quaternion", "Quaternion opSub(const Quaternion&in) const", asMETHODPR(Quaternion, operator-, (const Quaternion &) const, Quaternion), asCALL_THISCALL);
    // Quaternion& operator=(const Quaternion &rhs) noexcept
    engine->RegisterObjectMethod("Quaternion", "Quaternion& opAssign(const Quaternion&in)", asMETHODPR(Quaternion, operator=, (const Quaternion &), Quaternion &), asCALL_THISCALL);
    // bool operator==(const Quaternion &rhs) const
    engine->RegisterObjectMethod("Quaternion", "bool opEquals(const Quaternion&in) const", asMETHODPR(Quaternion, operator==, (const Quaternion &) const, bool), asCALL_THISCALL);
    // float PitchAngle() const
    engine->RegisterObjectMethod("Quaternion", "float PitchAngle() const", asMETHODPR(Quaternion, PitchAngle, () const, float), asCALL_THISCALL);
    // Quaternion() noexcept
    engine->RegisterObjectBehaviour("Quaternion", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(Quaternion_Quaternion_39_5), asCALL_CDECL_OBJFIRST);
    // Quaternion(const Quaternion &quat) noexcept
    engine->RegisterObjectBehaviour("Quaternion", asBEHAVE_CONSTRUCT, "void f(const Quaternion&in)", asFUNCTION(Quaternion_Quaternion_53_5), asCALL_CDECL_OBJFIRST);
    // Quaternion(float w, float x, float y, float z) noexcept
    engine->RegisterObjectBehaviour("Quaternion", asBEHAVE_CONSTRUCT, "void f(float, float, float, float)", asFUNCTION(Quaternion_Quaternion_68_5), asCALL_CDECL_OBJFIRST);
    // Quaternion(float angle, const Vector3 &axis) noexcept
    engine->RegisterObjectBehaviour("Quaternion", asBEHAVE_CONSTRUCT, "void f(float, const Vector3&in)", asFUNCTION(Quaternion_Quaternion_97_5), asCALL_CDECL_OBJFIRST);
    // Quaternion(float angle) noexcept
    engine->RegisterObjectBehaviour("Quaternion", asBEHAVE_CONSTRUCT, "void f(float)", asFUNCTION(Quaternion_Quaternion_103_14), asCALL_CDECL_OBJFIRST);
    // Quaternion(float x, float y, float z) noexcept
    engine->RegisterObjectBehaviour("Quaternion", asBEHAVE_CONSTRUCT, "void f(float, float, float)", asFUNCTION(Quaternion_Quaternion_109_5), asCALL_CDECL_OBJFIRST);
    // Quaternion(const Vector3 &angles) noexcept
    engine->RegisterObjectBehaviour("Quaternion", asBEHAVE_CONSTRUCT, "void f(const Vector3&in)", asFUNCTION(Quaternion_Quaternion_115_14), asCALL_CDECL_OBJFIRST);
    // Quaternion(const Vector3 &start, const Vector3 &end) noexcept
    engine->RegisterObjectBehaviour("Quaternion", asBEHAVE_CONSTRUCT, "void f(const Vector3&in, const Vector3&in)", asFUNCTION(Quaternion_Quaternion_121_5), asCALL_CDECL_OBJFIRST);
    // Quaternion(const Vector3 &xAxis, const Vector3 &yAxis, const Vector3 &zAxis) noexcept
    engine->RegisterObjectBehaviour("Quaternion", asBEHAVE_CONSTRUCT, "void f(const Vector3&in, const Vector3&in, const Vector3&in)", asFUNCTION(Quaternion_Quaternion_127_5), asCALL_CDECL_OBJFIRST);
    // Quaternion(const Matrix3 &matrix) noexcept
    engine->RegisterObjectBehaviour("Quaternion", asBEHAVE_CONSTRUCT, "void f(const Matrix3&in)", asFUNCTION(Quaternion_Quaternion_133_14), asCALL_CDECL_OBJFIRST);
    // float RollAngle() const
    engine->RegisterObjectMethod("Quaternion", "float RollAngle() const", asMETHODPR(Quaternion, RollAngle, () const, float), asCALL_THISCALL);
    // Matrix3 RotationMatrix() const
    engine->RegisterObjectMethod("Quaternion", "Matrix3 get_rotationMatrix() const", asMETHODPR(Quaternion, RotationMatrix, () const, Matrix3), asCALL_THISCALL);
    // Quaternion Slerp(const Quaternion &rhs, float t) const
    engine->RegisterObjectMethod("Quaternion", "Quaternion Slerp(const Quaternion&in, float) const", asMETHODPR(Quaternion, Slerp, (const Quaternion &, float) const, Quaternion), asCALL_THISCALL);
    // String ToString() const
    engine->RegisterObjectMethod("Quaternion", "String ToString() const", asMETHODPR(Quaternion, ToString, () const, String), asCALL_THISCALL);
    // float YawAngle() const
    engine->RegisterObjectMethod("Quaternion", "float YawAngle() const", asMETHODPR(Quaternion, YawAngle, () const, float), asCALL_THISCALL);

    // class Vector3 | File: ../Math/Vector3.h | Line: 187
    // float x_
    engine->RegisterObjectProperty("Vector3", "float x", offsetof(Vector3, x_));
    // float y_
    engine->RegisterObjectProperty("Vector3", "float y", offsetof(Vector3, y_));
    // float z_
    engine->RegisterObjectProperty("Vector3", "float z", offsetof(Vector3, z_));
    // Vector3 Abs() const
    engine->RegisterObjectMethod("Vector3", "Vector3 Abs() const", asMETHODPR(Vector3, Abs, () const, Vector3), asCALL_THISCALL);
    // float AbsDotProduct(const Vector3 &rhs) const
    engine->RegisterObjectMethod("Vector3", "float AbsDotProduct(const Vector3&in) const", asMETHODPR(Vector3, AbsDotProduct, (const Vector3 &) const, float), asCALL_THISCALL);
    // float Angle(const Vector3 &rhs) const
    engine->RegisterObjectMethod("Vector3", "float Angle(const Vector3&in) const", asMETHODPR(Vector3, Angle, (const Vector3 &) const, float), asCALL_THISCALL);
    // Vector3 CrossProduct(const Vector3 &rhs) const
    engine->RegisterObjectMethod("Vector3", "Vector3 CrossProduct(const Vector3&in) const", asMETHODPR(Vector3, CrossProduct, (const Vector3 &) const, Vector3), asCALL_THISCALL);
    // float DistanceToPlane(const Vector3 &origin, const Vector3 &normal) const
    engine->RegisterObjectMethod("Vector3", "float DistanceToPlane(const Vector3&in, const Vector3&in) const", asMETHODPR(Vector3, DistanceToPlane, (const Vector3 &, const Vector3 &) const, float), asCALL_THISCALL);
    // float DistanceToPoint(const Vector3 &point) const
    engine->RegisterObjectMethod("Vector3", "float DistanceToPoint(const Vector3&in) const", asMETHODPR(Vector3, DistanceToPoint, (const Vector3 &) const, float), asCALL_THISCALL);
    // float DotProduct(const Vector3 &rhs) const
    engine->RegisterObjectMethod("Vector3", "float DotProduct(const Vector3&in) const", asMETHODPR(Vector3, DotProduct, (const Vector3 &) const, float), asCALL_THISCALL);
    // bool Equals(const Vector3 &rhs) const
    engine->RegisterObjectMethod("Vector3", "bool Equals(const Vector3&in) const", asMETHODPR(Vector3, Equals, (const Vector3 &) const, bool), asCALL_THISCALL);
    // bool IsInf() const
    engine->RegisterObjectMethod("Vector3", "bool IsInf() const", asMETHODPR(Vector3, IsInf, () const, bool), asCALL_THISCALL);
    // bool IsNaN() const
    engine->RegisterObjectMethod("Vector3", "bool IsNaN() const", asMETHODPR(Vector3, IsNaN, () const, bool), asCALL_THISCALL);
    // float Length() const
    engine->RegisterObjectMethod("Vector3", "float get_length() const", asMETHODPR(Vector3, Length, () const, float), asCALL_THISCALL);
    // float LengthSquared() const
    engine->RegisterObjectMethod("Vector3", "float get_lengthSquared() const", asMETHODPR(Vector3, LengthSquared, () const, float), asCALL_THISCALL);
    // Vector3 Lerp(const Vector3 &rhs, float t) const
    engine->RegisterObjectMethod("Vector3", "Vector3 Lerp(const Vector3&in, float) const", asMETHODPR(Vector3, Lerp, (const Vector3 &, float) const, Vector3), asCALL_THISCALL);
    // void Normalize()
    engine->RegisterObjectMethod("Vector3", "void Normalize()", asMETHODPR(Vector3, Normalize, (), void), asCALL_THISCALL);
    // Vector3 Normalized() const
    engine->RegisterObjectMethod("Vector3", "Vector3 Normalized() const", asMETHODPR(Vector3, Normalized, () const, Vector3), asCALL_THISCALL);
    // Vector3 NormalizedOrDefault(const Vector3 &defaultValue=Vector3::ZERO, float eps=M_LARGE_EPSILON) const
    engine->RegisterObjectMethod("Vector3", "Vector3 NormalizedOrDefault(const Vector3&in, float) const", asMETHODPR(Vector3, NormalizedOrDefault, (const Vector3 &, float) const, Vector3), asCALL_THISCALL);
    // Vector3 operator*(float rhs) const
    engine->RegisterObjectMethod("Vector3", "Vector3 opMul(float) const", asMETHODPR(Vector3, operator*, (float) const, Vector3), asCALL_THISCALL);
    // Vector3 operator*(const Vector3 &rhs) const
    engine->RegisterObjectMethod("Vector3", "Vector3 opMul(const Vector3&in) const", asMETHODPR(Vector3, operator*, (const Vector3 &) const, Vector3), asCALL_THISCALL);
    // Vector3& operator*=(float rhs)
    engine->RegisterObjectMethod("Vector3", "Vector3& opMulAssign(float)", asMETHODPR(Vector3, operator*=, (float), Vector3 &), asCALL_THISCALL);
    // Vector3& operator*=(const Vector3 &rhs)
    engine->RegisterObjectMethod("Vector3", "Vector3& opMulAssign(const Vector3&in)", asMETHODPR(Vector3, operator*=, (const Vector3 &), Vector3 &), asCALL_THISCALL);
    // Vector3 operator+(const Vector3 &rhs) const
    engine->RegisterObjectMethod("Vector3", "Vector3 opAdd(const Vector3&in) const", asMETHODPR(Vector3, operator+, (const Vector3 &) const, Vector3), asCALL_THISCALL);
    // Vector3& operator+=(const Vector3 &rhs)
    engine->RegisterObjectMethod("Vector3", "Vector3& opAddAssign(const Vector3&in)", asMETHODPR(Vector3, operator+=, (const Vector3 &), Vector3 &), asCALL_THISCALL);
    // Vector3 operator-() const
    engine->RegisterObjectMethod("Vector3", "Vector3 opNeg() const", asMETHODPR(Vector3, operator-, () const, Vector3), asCALL_THISCALL);
    // Vector3 operator-(const Vector3 &rhs) const
    engine->RegisterObjectMethod("Vector3", "Vector3 opSub(const Vector3&in) const", asMETHODPR(Vector3, operator-, (const Vector3 &) const, Vector3), asCALL_THISCALL);
    // Vector3& operator-=(const Vector3 &rhs)
    engine->RegisterObjectMethod("Vector3", "Vector3& opSubAssign(const Vector3&in)", asMETHODPR(Vector3, operator-=, (const Vector3 &), Vector3 &), asCALL_THISCALL);
    // Vector3 operator/(float rhs) const
    engine->RegisterObjectMethod("Vector3", "Vector3 opDiv(float) const", asMETHODPR(Vector3, operator/, (float) const, Vector3), asCALL_THISCALL);
    // Vector3 operator/(const Vector3 &rhs) const
    engine->RegisterObjectMethod("Vector3", "Vector3 opDiv(const Vector3&in) const", asMETHODPR(Vector3, operator/, (const Vector3 &) const, Vector3), asCALL_THISCALL);
    // Vector3& operator/=(float rhs)
    engine->RegisterObjectMethod("Vector3", "Vector3& opDivAssign(float)", asMETHODPR(Vector3, operator/=, (float), Vector3 &), asCALL_THISCALL);
    // Vector3& operator/=(const Vector3 &rhs)
    engine->RegisterObjectMethod("Vector3", "Vector3& opDivAssign(const Vector3&in)", asMETHODPR(Vector3, operator/=, (const Vector3 &), Vector3 &), asCALL_THISCALL);
    // Vector3& operator=(const Vector3 &rhs) noexcept=default
    engine->RegisterObjectMethod("Vector3", "Vector3& opAssign(const Vector3&in)", asMETHODPR(Vector3, operator=, (const Vector3 &), Vector3 &), asCALL_THISCALL);
    // bool operator==(const Vector3 &rhs) const
    engine->RegisterObjectMethod("Vector3", "bool opEquals(const Vector3&in) const", asMETHODPR(Vector3, operator==, (const Vector3 &) const, bool), asCALL_THISCALL);
    // Vector3 Orthogonalize(const Vector3 &axis) const
    engine->RegisterObjectMethod("Vector3", "Vector3 Orthogonalize(const Vector3&in) const", asMETHODPR(Vector3, Orthogonalize, (const Vector3 &) const, Vector3), asCALL_THISCALL);
    // float ProjectOntoAxis(const Vector3 &axis) const
    engine->RegisterObjectMethod("Vector3", "float ProjectOntoAxis(const Vector3&in) const", asMETHODPR(Vector3, ProjectOntoAxis, (const Vector3 &) const, float), asCALL_THISCALL);
    // Vector3 ProjectOntoLine(const Vector3 &from, const Vector3 &to, bool clamped=false) const
    engine->RegisterObjectMethod("Vector3", "Vector3 ProjectOntoLine(const Vector3&in, const Vector3&in, bool) const", asMETHODPR(Vector3, ProjectOntoLine, (const Vector3 &, const Vector3 &, bool) const, Vector3), asCALL_THISCALL);
    // Vector3 ProjectOntoPlane(const Vector3 &origin, const Vector3 &normal) const
    engine->RegisterObjectMethod("Vector3", "Vector3 ProjectOntoPlane(const Vector3&in, const Vector3&in) const", asMETHODPR(Vector3, ProjectOntoPlane, (const Vector3 &, const Vector3 &) const, Vector3), asCALL_THISCALL);
    // Vector3 ReNormalized(float minLength, float maxLength, const Vector3 &defaultValue=Vector3::ZERO, float eps=M_LARGE_EPSILON) const
    engine->RegisterObjectMethod("Vector3", "Vector3 ReNormalized(float, float, const Vector3&in, float) const", asMETHODPR(Vector3, ReNormalized, (float, float, const Vector3 &, float) const, Vector3), asCALL_THISCALL);
    // unsigned ToHash() const
    engine->RegisterObjectMethod("Vector3", "uint ToHash() const", asMETHODPR(Vector3, ToHash, () const, unsigned), asCALL_THISCALL);
    // String ToString() const
    engine->RegisterObjectMethod("Vector3", "String ToString() const", asMETHODPR(Vector3, ToString, () const, String), asCALL_THISCALL);
    // Vector3() noexcept
    engine->RegisterObjectBehaviour("Vector3", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(Vector3_Vector3_190_5), asCALL_CDECL_OBJFIRST);
    // Vector3(const Vector3 &vector) noexcept=default
    engine->RegisterObjectBehaviour("Vector3", asBEHAVE_CONSTRUCT, "void f(const Vector3&in)", asFUNCTION(Vector3_Vector3_198_5), asCALL_CDECL_OBJFIRST);
    // Vector3(const Vector2 &vector, float z) noexcept
    engine->RegisterObjectBehaviour("Vector3", asBEHAVE_CONSTRUCT, "void f(const Vector2&in, float)", asFUNCTION(Vector3_Vector3_201_5), asCALL_CDECL_OBJFIRST);
    // Vector3(const Vector2 &vector) noexcept
    engine->RegisterObjectBehaviour("Vector3", asBEHAVE_CONSTRUCT, "void f(const Vector2&in)", asFUNCTION(Vector3_Vector3_209_14), asCALL_CDECL_OBJFIRST);
    // Vector3(const IntVector3 &vector) noexcept
    engine->RegisterObjectBehaviour("Vector3", asBEHAVE_CONSTRUCT, "void f(const IntVector3&in)", asFUNCTION(Vector3_Vector3_217_14), asCALL_CDECL_OBJFIRST);
    // Vector3(float x, float y, float z) noexcept
    engine->RegisterObjectBehaviour("Vector3", asBEHAVE_CONSTRUCT, "void f(float, float, float)", asFUNCTION(Vector3_Vector3_225_5), asCALL_CDECL_OBJFIRST);
    // Vector3(float x, float y) noexcept
    engine->RegisterObjectBehaviour("Vector3", asBEHAVE_CONSTRUCT, "void f(float, float)", asFUNCTION(Vector3_Vector3_233_5), asCALL_CDECL_OBJFIRST);

}

}
