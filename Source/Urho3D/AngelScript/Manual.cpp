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

#include "../Graphics/GraphicsDefs.h"
#ifdef URHO3D_IK
#include "../IK/IKSolver.h"
#endif
#include "../Math/Matrix2.h"

namespace Urho3D
{

// explicit IntVector2::IntVector2(const int* data) noexcept | File: ../Math/Vector2.h
static void ConstructIntVector2ArrayInit(CScriptArray* data, IntVector2* ptr)
{
    new(ptr) IntVector2((static_cast<int*>(data->At(0))));
}

// const int* IntVector2::Data() const | File: ../Math/Vector2.h
static CScriptArray* IntVector2Data(IntVector2* ptr)
{
    return BufferToArray<int>(ptr->Data(), 2, "int[]");
}

// explicit Vector2::Vector2(const float* data) noexcept | File: ../Math/Vector2.h
static void ConstructVector2ArrayInit(CScriptArray* data, Vector2* ptr)
{
    new(ptr) Vector2((static_cast<float*>(data->At(0))));
}

// const float* Vector2::Data() const | File: ../Math/Vector2.h
static CScriptArray* Vector2Data(Vector2* ptr)
{
    return BufferToArray<float>(ptr->Data(), 2, "float[]");
}

// explicit IntVector3::IntVector3(const int* data) noexcept | File: ../Math/Vector3.h
static void ConstructIntVector3ArrayInit(CScriptArray* data, IntVector3* ptr)
{
    new(ptr) IntVector3((static_cast<int*>(data->At(0))));
}

// const int* IntVector3::Data() const | File: ../Math/Vector3.h
static CScriptArray* IntVector3Data(IntVector3* ptr)
{
    return BufferToArray<int>(ptr->Data(), 3, "int[]");
}

// explicit Vector3::Vector3(const float* data) noexcept | File: ../Math/Vector3.h
static void ConstructVector3ArrayInit(CScriptArray* data, Vector3* ptr)
{
    new(ptr) Vector3((static_cast<float*>(data->At(0))));
}

// const float* Vector3::Data() const | File: ../Math/Vector3.h
static CScriptArray* Vector3Data(Vector3* ptr)
{
    return BufferToArray<float>(ptr->Data(), 3, "float[]");
}

// explicit Vector4::Vector4(const float* data) noexcept | File: ../Math/Vector4.h
static void ConstructVector4ArrayInit(CScriptArray* data, Vector4* ptr)
{
    new(ptr) Vector4((static_cast<float*>(data->At(0))));
}

// const float* Vector4::Data() const | File: ../Math/Vector4.h
static CScriptArray* Vector4Data(Vector4* ptr)
{
    return BufferToArray<float>(ptr->Data(), 4, "float[]");
}

// explicit Matrix2::Matrix2(const float* data) noexcept | File: ../Math/Matrix2.h
static void ConstructMatrix2ArrayInit(CScriptArray* data, Matrix2* ptr)
{
    new(ptr) Matrix2((static_cast<float*>(data->At(0))));
}

// const float* Matrix2::Data() const | File: ../Math/Matrix2.h
static CScriptArray* Matrix2Data(Matrix2* ptr)
{
    return BufferToArray<float>(ptr->Data(), 4, "float[]");
}

// explicit Matrix3::Matrix3(const float* data) noexcept | File: ../Math/Matrix3.h
static void ConstructMatrix3ArrayInit(CScriptArray* data, Matrix3* ptr)
{
    new(ptr) Matrix3((static_cast<float*>(data->At(0))));
}

// const float* Matrix3::Data() const | File: ../Math/Matrix3.h
static CScriptArray* Matrix3Data(Matrix3* ptr)
{
    return BufferToArray<float>(ptr->Data(), 9, "float[]");
}

// explicit Matrix3x4::Matrix3x4(const float* data) noexcept | File: ../Math/Matrix3x4.h
static void ConstructMatrix3x4ArrayInit(CScriptArray* data, Matrix3x4* ptr)
{
    new(ptr) Matrix3x4((static_cast<float*>(data->At(0))));
}

// const float* Matrix3x4::Data() const | File: ../Math/Matrix3x4.h
static CScriptArray* Matrix3x4Data(Matrix3x4* ptr)
{
    return BufferToArray<float>(ptr->Data(), 12, "float[]");
}

// explicit Matrix4::Matrix4(const float* data) noexcept | File: ../Math/Matrix4.h
static void ConstructMatrix4ArrayInit(CScriptArray* data, Matrix4* ptr)
{
    new(ptr) Matrix4((static_cast<float*>(data->At(0))));
}

// const float* Matrix4::Data() const | File: ../Math/Matrix4.h
static CScriptArray* Matrix4Data(Matrix4* ptr)
{
    return BufferToArray<float>(ptr->Data(), 12, "float[]");
}

// explicit Quaternion::Quaternion(const float* data) noexcept | File: ../Math/Quaternion.h
static void ConstructQuaternionArrayInit(CScriptArray* data, Quaternion* ptr)
{
    new(ptr) Quaternion((static_cast<float*>(data->At(0))));
}

// const float* Quaternion::Data() const | File: ../Math/Quaternion.h
static CScriptArray* QuaternionData(Quaternion* ptr)
{
    return BufferToArray<float>(ptr->Data(), 4, "float[]");
}

// This function is called before RegisterGenerated()
void RegisterManualFirst(asIScriptEngine* engine)
{
    // enum TextureUnit | File: ../Graphics/GraphicsDefs.h
    engine->RegisterEnum("TextureUnit");
    engine->RegisterEnumValue("TextureUnit", "TU_DIFFUSE", TU_DIFFUSE);
    engine->RegisterEnumValue("TextureUnit", "TU_ALBEDOBUFFER", TU_ALBEDOBUFFER);
    engine->RegisterEnumValue("TextureUnit", "TU_NORMAL", TU_NORMAL);
    engine->RegisterEnumValue("TextureUnit", "TU_NORMALBUFFER", TU_NORMALBUFFER);
    engine->RegisterEnumValue("TextureUnit", "TU_SPECULAR", TU_SPECULAR);
    engine->RegisterEnumValue("TextureUnit", "TU_EMISSIVE", TU_EMISSIVE);
    engine->RegisterEnumValue("TextureUnit", "TU_ENVIRONMENT", TU_ENVIRONMENT);
    engine->RegisterEnumValue("TextureUnit", "TU_LIGHTRAMP", TU_LIGHTRAMP);
    engine->RegisterEnumValue("TextureUnit", "TU_LIGHTSHAPE", TU_LIGHTSHAPE);
    engine->RegisterEnumValue("TextureUnit", "TU_SHADOWMAP", TU_SHADOWMAP);
#ifdef DESKTOP_GRAPHICS
    engine->RegisterEnumValue("TextureUnit", "TU_VOLUMEMAP", TU_VOLUMEMAP);
    engine->RegisterEnumValue("TextureUnit", "TU_CUSTOM1", TU_CUSTOM1);
    engine->RegisterEnumValue("TextureUnit", "TU_CUSTOM2", TU_CUSTOM2);
    engine->RegisterEnumValue("TextureUnit", "TU_FACESELECT", TU_FACESELECT);
    engine->RegisterEnumValue("TextureUnit", "TU_INDIRECTION", TU_INDIRECTION);
    engine->RegisterEnumValue("TextureUnit", "TU_DEPTHBUFFER", TU_DEPTHBUFFER);
    engine->RegisterEnumValue("TextureUnit", "TU_LIGHTBUFFER", TU_LIGHTBUFFER);
    engine->RegisterEnumValue("TextureUnit", "TU_ZONE", TU_ZONE);
#endif
    engine->RegisterEnumValue("TextureUnit", "MAX_MATERIAL_TEXTURE_UNITS", MAX_MATERIAL_TEXTURE_UNITS);
    engine->RegisterEnumValue("TextureUnit", "MAX_TEXTURE_UNITS", MAX_TEXTURE_UNITS);

#ifdef URHO3D_IK
    // enum IKSolver::Algorithm | File: ../IK/IKSolver.h
    engine->RegisterEnum("IKAlgorithm");
    engine->RegisterEnumValue("IKAlgorithm", "ONE_BONE", IKSolver::ONE_BONE);
    engine->RegisterEnumValue("IKAlgorithm", "TWO_BONE", IKSolver::TWO_BONE);
    engine->RegisterEnumValue("IKAlgorithm", "FABRIK", IKSolver::FABRIK);

    // enum IKSolver::Feature | File: ../IK/IKSolver.h
    engine->RegisterEnum("IKFeature");
    engine->RegisterEnumValue("IKFeature", "JOINT_ROTATIONS", IKSolver::JOINT_ROTATIONS);
    engine->RegisterEnumValue("IKFeature", "TARGET_ROTATIONS", IKSolver::TARGET_ROTATIONS);
    engine->RegisterEnumValue("IKFeature", "UPDATE_ORIGINAL_POSE", IKSolver::UPDATE_ORIGINAL_POSE);
    engine->RegisterEnumValue("IKFeature", "UPDATE_ACTIVE_POSE", IKSolver::UPDATE_ACTIVE_POSE);
    engine->RegisterEnumValue("IKFeature", "USE_ORIGINAL_POSE", IKSolver::USE_ORIGINAL_POSE);
    engine->RegisterEnumValue("IKFeature", "CONSTRAINTS", IKSolver::CONSTRAINTS);
    engine->RegisterEnumValue("IKFeature", "AUTO_SOLVE", IKSolver::AUTO_SOLVE);
#endif
}

// This function is called after RegisterGenerated()
void RegisterManualLast(asIScriptEngine* engine)
{
    // explicit IntVector2::IntVector2(const int* data) noexcept | File: ../Math/Vector2.h
    engine->RegisterObjectBehaviour("IntVector2", asBEHAVE_CONSTRUCT, "void f(int[]&)", asFUNCTION(ConstructIntVector2ArrayInit), asCALL_CDECL_OBJLAST);
    // const int* IntVector2::Data() const | File: ../Math/Vector2.h
    engine->RegisterObjectMethod("IntVector2", "int[]& get_data() const", asFUNCTION(IntVector2Data), asCALL_CDECL_OBJLAST);

    // explicit Vector2::Vector2(const float* data) noexcept | File: ../Math/Vector2.h
    engine->RegisterObjectBehaviour("Vector2", asBEHAVE_CONSTRUCT, "void f(float[]&)", asFUNCTION(ConstructVector2ArrayInit), asCALL_CDECL_OBJLAST);
    // const float* Vector2::Data() const | File: ../Math/Vector2.h
    engine->RegisterObjectMethod("Vector2", "float[]& get_data() const", asFUNCTION(Vector2Data), asCALL_CDECL_OBJLAST);

    // explicit IntVector3::IntVector3(const int* data) noexcept | File: ../Math/Vector3.h
    engine->RegisterObjectBehaviour("IntVector3", asBEHAVE_CONSTRUCT, "void f(int[]&)", asFUNCTION(ConstructIntVector3ArrayInit), asCALL_CDECL_OBJLAST);
    // const int* IntVector3::Data() const | File: ../Math/Vector3.h
    engine->RegisterObjectMethod("IntVector3", "int[]& get_data() const", asFUNCTION(IntVector3Data), asCALL_CDECL_OBJLAST);

    // explicit Vector3::Vector3(const float* data) noexcept | File: ../Math/Vector3.h
    engine->RegisterObjectBehaviour("Vector3", asBEHAVE_CONSTRUCT, "void f(float[]&)", asFUNCTION(ConstructVector3ArrayInit), asCALL_CDECL_OBJLAST);
    // const float* Vector3::Data() const | File: ../Math/Vector3.h
    engine->RegisterObjectMethod("Vector3", "float[]& get_data() const", asFUNCTION(Vector3Data), asCALL_CDECL_OBJLAST);

    // explicit Vector4::Vector4(const float* data) noexcept | File: ../Math/Vector4.h
    engine->RegisterObjectBehaviour("Vector4", asBEHAVE_CONSTRUCT, "void f(float[]&)", asFUNCTION(ConstructVector4ArrayInit), asCALL_CDECL_OBJLAST);
    // const float* Vector4::Data() const | File: ../Math/Vector4.h
    engine->RegisterObjectMethod("Vector4", "float[]& get_data() const", asFUNCTION(Vector4Data), asCALL_CDECL_OBJLAST);

    // explicit Matrix2::Matrix2(const float* data) noexcept | File: ../Math/Matrix2.h
    engine->RegisterObjectBehaviour("Matrix2", asBEHAVE_CONSTRUCT, "void f(float[]&)", asFUNCTION(ConstructMatrix2ArrayInit), asCALL_CDECL_OBJLAST);
    // const float* Matrix2::Data() const | File: ../Math/Matrix2.h
    engine->RegisterObjectMethod("Matrix2", "float[]& get_data() const", asFUNCTION(Matrix2Data), asCALL_CDECL_OBJLAST);

    // explicit Matrix3::Matrix3(const float* data) noexcept | File: ../Math/Matrix3.h
    engine->RegisterObjectBehaviour("Matrix3", asBEHAVE_CONSTRUCT, "void f(float[]&)", asFUNCTION(ConstructMatrix3ArrayInit), asCALL_CDECL_OBJLAST);
    // const float* Matrix3::Data() const | File: ../Math/Matrix3.h
    engine->RegisterObjectMethod("Matrix3", "float[]& get_data() const", asFUNCTION(Matrix3Data), asCALL_CDECL_OBJLAST);

    // explicit Matrix3x4::Matrix3x4(const float* data) noexcept | File: ../Math/Matrix3x4.h
    engine->RegisterObjectBehaviour("Matrix3x4", asBEHAVE_CONSTRUCT, "void f(float[]&)", asFUNCTION(ConstructMatrix3x4ArrayInit), asCALL_CDECL_OBJLAST);
    // const float* Matrix3x4::Data() const | File: ../Math/Matrix3x4.h
    engine->RegisterObjectMethod("Matrix3x4", "float[]& get_data() const", asFUNCTION(Matrix3x4Data), asCALL_CDECL_OBJLAST);

    // explicit Matrix4::Matrix4(const float* data) noexcept | File: ../Math/Matrix4.h
    engine->RegisterObjectBehaviour("Matrix4", asBEHAVE_CONSTRUCT, "void f(float[]&)", asFUNCTION(ConstructMatrix4ArrayInit), asCALL_CDECL_OBJLAST);
    // const float* Matrix4::Data() const | File: ../Math/Matrix3.h
    engine->RegisterObjectMethod("Matrix4", "float[]& get_data() const", asFUNCTION(Matrix4Data), asCALL_CDECL_OBJLAST);

    // explicit Quaternion::Matrix4(const float* data) noexcept | File: ../Math/Quaternion.h
    engine->RegisterObjectBehaviour("Quaternion", asBEHAVE_CONSTRUCT, "void f(float[]&)", asFUNCTION(ConstructQuaternionArrayInit), asCALL_CDECL_OBJLAST);
    // const float* Quaternion::Data() const | File: ../Math/Quaternion.h
    engine->RegisterObjectMethod("Quaternion", "float[]& get_data() const", asFUNCTION(QuaternionData), asCALL_CDECL_OBJLAST);
    // float Quaternion::YawAngle() const | File: ../Math/Quaternion.h
    engine->RegisterObjectMethod("Quaternion", "float get_yaw() const", asMETHOD(Quaternion, YawAngle), asCALL_THISCALL);
    // float Quaternion::PitchAngle() const | File: ../Math/Quaternion.h
    engine->RegisterObjectMethod("Quaternion", "float get_pitch() const", asMETHOD(Quaternion, PitchAngle), asCALL_THISCALL);
    // float Quaternion::RollAngle() const | File: ../Math/Quaternion.h
    engine->RegisterObjectMethod("Quaternion", "float get_roll() const", asMETHOD(Quaternion, RollAngle), asCALL_THISCALL);
}

}
