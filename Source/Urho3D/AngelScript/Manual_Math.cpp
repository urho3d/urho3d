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

#include "../AngelScript/Manual_Math.h"

namespace Urho3D
{

// This function is called before ASRegisterGenerated()
void ASRegisterManualFirst_Math(asIScriptEngine* engine)
{
}

// ========================================================================================

// This function is called after ASRegisterGenerated()
void ASRegisterManualLast_Math(asIScriptEngine* engine)
{
    // template <class T, typename std::enable_if...> T Mod(T x, T y) | File: ../Math/MathDefs.h
    engine->RegisterGlobalFunction("float Mod(float, float)", asFUNCTION(Mod<float>), asCALL_CDECL);
}

// ========================================================================================

// explicit IntVector2::IntVector2(const int *data) noexcept | File: ../Math/Vector2.h
void ConstructIntVector2ArrayInit(CScriptArray* data, IntVector2* ptr)
{
    new(ptr) IntVector2(static_cast<int*>(data->At(0)));
}

// const int* IntVector2::Data() const | File: ../Math/Vector2.h
CScriptArray* IntVector2Data(IntVector2* ptr)
{
    return BufferToArray<int>(ptr->Data(), 2, "int[]");
}

// ========================================================================================

// explicit Vector2::Vector2(const float *data) noexcept | File: ../Math/Vector2.h
void ConstructVector2ArrayInit(CScriptArray* data, Vector2* ptr)
{
    new(ptr) Vector2(static_cast<float*>(data->At(0)));
}

// const float* Vector2::Data() const | File: ../Math/Vector2.h
CScriptArray* Vector2Data(Vector2* ptr)
{
    return BufferToArray<float>(ptr->Data(), 2, "float[]");
}

// ========================================================================================

// explicit IntVector3::IntVector3(const int *data) noexcept | File: ../Math/Vector3.h
void ConstructIntVector3ArrayInit(CScriptArray* data, IntVector3* ptr)
{
    new(ptr) IntVector3(static_cast<int*>(data->At(0)));
}

// const int* IntVector3::Data() const | File: ../Math/Vector3.h
CScriptArray* IntVector3Data(IntVector3* ptr)
{
    return BufferToArray<int>(ptr->Data(), 3, "int[]");
}

// ========================================================================================

// explicit Vector3::Vector3(const float *data) noexcept | File: ../Math/Vector3.h
void ConstructVector3ArrayInit(CScriptArray* data, Vector3* ptr)
{
    new(ptr) Vector3(static_cast<float*>(data->At(0)));
}

// const float* Vector3::Data() const | File: ../Math/Vector3.h
CScriptArray* Vector3Data(Vector3* ptr)
{
    return BufferToArray<float>(ptr->Data(), 3, "float[]");
}

// ========================================================================================

// explicit Vector4::Vector4(const float *data) noexcept | File: ../Math/Vector4.h
void ConstructVector4ArrayInit(CScriptArray* data, Vector4* ptr)
{
    new(ptr) Vector4(static_cast<float*>(data->At(0)));
}

// const float* Vector4::Data() const | File: ../Math/Vector4.h
CScriptArray* Vector4Data(Vector4* ptr)
{
    return BufferToArray<float>(ptr->Data(), 4, "float[]");
}

// ========================================================================================

// explicit IntRect::IntRect(const int *data) noexcept | File: ../Math/Rect.h
void ConstructIntRectArrayInit(CScriptArray* data, IntRect* ptr)
{
    new(ptr) IntRect(static_cast<int*>(data->At(0)));
}

// const int* IntRect::Data() const | File: ../Math/Rect.h
CScriptArray* IntRectData(IntRect* ptr)
{
    return BufferToArray<int>(ptr->Data(), 4, "int[]");
}

// ========================================================================================

// explicit Color::Color(const float *data) noexcept | File: ../Math/Color.h
void ConstructColorArrayInit(CScriptArray* data, Color* ptr)
{
    new(ptr) Color(static_cast<float*>(data->At(0)));
}

// const float* Color::Data() const | File: ../Math/Color.h
CScriptArray* ColorData(Color* ptr)
{
    return BufferToArray<float>(ptr->Data(), 4, "float[]");
}

// ========================================================================================

// float Ray::HitDistance(const Vector3 &v0, const Vector3 &v1, const Vector3 &v2, Vector3 *outNormal=nullptr, Vector3 *outBary=nullptr) const | File: ../Math/Ray.h
float Ray_HitDistance(const Vector3& v0, const Vector3& v1, const Vector3& v2, Ray* ptr)
{
    return ptr->HitDistance(v0, v1, v2);
}

// ========================================================================================

// Vector3 Frustum::vertices_[NUM_FRUSTUM_VERTICES] | File: ../Math/Frustum.h
Vector3 FrustumGetVertex(unsigned index, Frustum* ptr)
{
    if (index >= NUM_FRUSTUM_VERTICES)
        return Vector3::ZERO;
    return ptr->vertices_[index];
}

// ========================================================================================

// Vector<PODVector<Vector3> > Polyhedron::faces_ | File: ../Math/Polyhedron.h
unsigned PolyhedronGetNumFaces(Polyhedron* ptr)
{
    return ptr->faces_.Size();
}

// Vector<PODVector<Vector3> > Polyhedron::faces_ | File: ../Math/Polyhedron.h
CScriptArray* PolyhedronGetFace(unsigned index, Polyhedron* ptr)
{
    PODVector<Vector3> face;
    if (index < ptr->faces_.Size())
        face = ptr->faces_[index];
    return VectorToArray<Vector3>(face, "Array<Vector3>");
}

}
