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

#include "../Math/Matrix4.h"

#ifdef URHO3D_SSE
#include <emmintrin.h>
#endif

namespace Urho3D
{

/// 3x4 matrix for scene node transform calculations.
class URHO3D_API Matrix3x4
{
public:
    /// Construct an identity matrix.
    Matrix3x4() noexcept
#ifndef URHO3D_SSE
       :m00_(1.0f),
        m01_(0.0f),
        m02_(0.0f),
        m03_(0.0f),
        m10_(0.0f),
        m11_(1.0f),
        m12_(0.0f),
        m13_(0.0f),
        m20_(0.0f),
        m21_(0.0f),
        m22_(1.0f),
        m23_(0.0f)
#endif
    {
#ifdef URHO3D_SSE
        _mm_storeu_ps(&m00_, _mm_set_ps(0.f, 0.f, 0.f, 1.f));
        _mm_storeu_ps(&m10_, _mm_set_ps(0.f, 0.f, 1.f, 0.f));
        _mm_storeu_ps(&m20_, _mm_set_ps(0.f, 1.f, 0.f, 0.f));
#endif
    }

    /// Copy-construct from another matrix.
    Matrix3x4(const Matrix3x4& matrix) noexcept = default;

    /// Copy-construct from a 3x3 matrix and set the extra elements to identity.
    explicit Matrix3x4(const Matrix3& matrix) noexcept :
        m00_(matrix.m00_),
        m01_(matrix.m01_),
        m02_(matrix.m02_),
        m03_(0.0f),
        m10_(matrix.m10_),
        m11_(matrix.m11_),
        m12_(matrix.m12_),
        m13_(0.0f),
        m20_(matrix.m20_),
        m21_(matrix.m21_),
        m22_(matrix.m22_),
        m23_(0.0f)
    {
    }

    /// Copy-construct from a 4x4 matrix which is assumed to contain no projection.
    explicit Matrix3x4(const Matrix4& matrix) noexcept
#ifndef URHO3D_SSE
       :m00_(matrix.m00_),
        m01_(matrix.m01_),
        m02_(matrix.m02_),
        m03_(matrix.m03_),
        m10_(matrix.m10_),
        m11_(matrix.m11_),
        m12_(matrix.m12_),
        m13_(matrix.m13_),
        m20_(matrix.m20_),
        m21_(matrix.m21_),
        m22_(matrix.m22_),
        m23_(matrix.m23_)
#endif
    {
#ifdef URHO3D_SSE
        _mm_storeu_ps(&m00_, _mm_loadu_ps(&matrix.m00_));
        _mm_storeu_ps(&m10_, _mm_loadu_ps(&matrix.m10_));
        _mm_storeu_ps(&m20_, _mm_loadu_ps(&matrix.m20_));
#endif
    }

    /// Construct from values.
    Matrix3x4(float v00, float v01, float v02, float v03,
              float v10, float v11, float v12, float v13,
              float v20, float v21, float v22, float v23) noexcept :
        m00_(v00),
        m01_(v01),
        m02_(v02),
        m03_(v03),
        m10_(v10),
        m11_(v11),
        m12_(v12),
        m13_(v13),
        m20_(v20),
        m21_(v21),
        m22_(v22),
        m23_(v23)
    {
    }

    /// Construct from a float array.
    explicit Matrix3x4(const float* data) noexcept
#ifndef URHO3D_SSE
       :m00_(data[0]),
        m01_(data[1]),
        m02_(data[2]),
        m03_(data[3]),
        m10_(data[4]),
        m11_(data[5]),
        m12_(data[6]),
        m13_(data[7]),
        m20_(data[8]),
        m21_(data[9]),
        m22_(data[10]),
        m23_(data[11])
#endif
    {
#ifdef URHO3D_SSE
        _mm_storeu_ps(&m00_, _mm_loadu_ps(data));
        _mm_storeu_ps(&m10_, _mm_loadu_ps(data + 4));
        _mm_storeu_ps(&m20_, _mm_loadu_ps(data + 8));
#endif
    }

    /// Construct from translation, rotation and uniform scale.
    Matrix3x4(const Vector3& translation, const Quaternion& rotation, float scale) noexcept
    {
#ifdef URHO3D_SSE
        __m128 t = _mm_set_ps(1.f, translation.z_, translation.y_, translation.x_);
        __m128 q = _mm_loadu_ps(&rotation.w_);
        __m128 s = _mm_set_ps(1.f, scale, scale, scale);
        SetFromTRS(t, q, s);
#else
        SetRotation(rotation.RotationMatrix() * scale);
        SetTranslation(translation);
#endif
    }

    /// Construct from translation, rotation and nonuniform scale.
    Matrix3x4(const Vector3& translation, const Quaternion& rotation, const Vector3& scale) noexcept
    {
#ifdef URHO3D_SSE
        __m128 t = _mm_set_ps(1.f, translation.z_, translation.y_, translation.x_);
        __m128 q = _mm_loadu_ps(&rotation.w_);
        __m128 s = _mm_set_ps(1.f, scale.z_, scale.y_, scale.x_);
        SetFromTRS(t, q, s);
#else
        SetRotation(rotation.RotationMatrix().Scaled(scale));
        SetTranslation(translation);
#endif
    }

    /// Assign from another matrix.
    Matrix3x4& operator =(const Matrix3x4& rhs) noexcept = default;

    /// Assign from a 3x3 matrix and set the extra elements to identity.
    Matrix3x4& operator =(const Matrix3& rhs) noexcept
    {
        m00_ = rhs.m00_;
        m01_ = rhs.m01_;
        m02_ = rhs.m02_;
        m03_ = 0.0f;
        m10_ = rhs.m10_;
        m11_ = rhs.m11_;
        m12_ = rhs.m12_;
        m13_ = 0.0f;
        m20_ = rhs.m20_;
        m21_ = rhs.m21_;
        m22_ = rhs.m22_;
        m23_ = 0.0f;
        return *this;
    }

    /// Assign from a 4x4 matrix which is assumed to contain no projection.
    Matrix3x4& operator =(const Matrix4& rhs) noexcept
    {
#ifdef URHO3D_SSE
        _mm_storeu_ps(&m00_, _mm_loadu_ps(&rhs.m00_));
        _mm_storeu_ps(&m10_, _mm_loadu_ps(&rhs.m10_));
        _mm_storeu_ps(&m20_, _mm_loadu_ps(&rhs.m20_));
#else
        m00_ = rhs.m00_;
        m01_ = rhs.m01_;
        m02_ = rhs.m02_;
        m03_ = rhs.m03_;
        m10_ = rhs.m10_;
        m11_ = rhs.m11_;
        m12_ = rhs.m12_;
        m13_ = rhs.m13_;
        m20_ = rhs.m20_;
        m21_ = rhs.m21_;
        m22_ = rhs.m22_;
        m23_ = rhs.m23_;
#endif
        return *this;
    }

    /// Test for equality with another matrix without epsilon.
    bool operator ==(const Matrix3x4& rhs) const
    {
#ifdef URHO3D_SSE
        __m128 c0 = _mm_cmpeq_ps(_mm_loadu_ps(&m00_), _mm_loadu_ps(&rhs.m00_));
        __m128 c1 = _mm_cmpeq_ps(_mm_loadu_ps(&m10_), _mm_loadu_ps(&rhs.m10_));
        c0 = _mm_and_ps(c0, c1);
        __m128 c2 = _mm_cmpeq_ps(_mm_loadu_ps(&m20_), _mm_loadu_ps(&rhs.m20_));
        c0 = _mm_and_ps(c0, c2);
        __m128 hi = _mm_movehl_ps(c0, c0);
        c0 = _mm_and_ps(c0, hi);
        hi = _mm_shuffle_ps(c0, c0, _MM_SHUFFLE(1, 1, 1, 1));
        c0 = _mm_and_ps(c0, hi);
        return _mm_cvtsi128_si32(_mm_castps_si128(c0)) == -1;
#else
        const float* leftData = Data();
        const float* rightData = rhs.Data();

        for (unsigned i = 0; i < 12; ++i)
        {
            if (leftData[i] != rightData[i])
                return false;
        }

        return true;
#endif
    }

    /// Test for inequality with another matrix without epsilon.
    bool operator !=(const Matrix3x4& rhs) const { return !(*this == rhs); }

    /// Multiply a Vector3 which is assumed to represent position.
    Vector3 operator *(const Vector3& rhs) const
    {
#ifdef URHO3D_SSE
        __m128 vec = _mm_set_ps(1.f, rhs.z_, rhs.y_, rhs.x_);
        __m128 r0 = _mm_mul_ps(_mm_loadu_ps(&m00_), vec);
        __m128 r1 = _mm_mul_ps(_mm_loadu_ps(&m10_), vec);
        __m128 t0 = _mm_unpacklo_ps(r0, r1);
        __m128 t1 = _mm_unpackhi_ps(r0, r1);
        t0 = _mm_add_ps(t0, t1);
        __m128 r2 = _mm_mul_ps(_mm_loadu_ps(&m20_), vec);
        __m128 r3 = _mm_setzero_ps();
        __m128 t2 = _mm_unpacklo_ps(r2, r3);
        __m128 t3 = _mm_unpackhi_ps(r2, r3);
        t2 = _mm_add_ps(t2, t3);
        vec = _mm_add_ps(_mm_movelh_ps(t0, t2), _mm_movehl_ps(t2, t0));

        return Vector3(
            _mm_cvtss_f32(vec),
            _mm_cvtss_f32(_mm_shuffle_ps(vec, vec, _MM_SHUFFLE(1, 1, 1, 1))),
            _mm_cvtss_f32(_mm_movehl_ps(vec, vec)));
#else
        return Vector3(
            (m00_ * rhs.x_ + m01_ * rhs.y_ + m02_ * rhs.z_ + m03_),
            (m10_ * rhs.x_ + m11_ * rhs.y_ + m12_ * rhs.z_ + m13_),
            (m20_ * rhs.x_ + m21_ * rhs.y_ + m22_ * rhs.z_ + m23_)
        );
#endif
    }

    /// Multiply a Vector4.
    Vector3 operator *(const Vector4& rhs) const
    {
#ifdef URHO3D_SSE
        __m128 vec = _mm_loadu_ps(&rhs.x_);
        __m128 r0 = _mm_mul_ps(_mm_loadu_ps(&m00_), vec);
        __m128 r1 = _mm_mul_ps(_mm_loadu_ps(&m10_), vec);
        __m128 t0 = _mm_unpacklo_ps(r0, r1);
        __m128 t1 = _mm_unpackhi_ps(r0, r1);
        t0 = _mm_add_ps(t0, t1);
        __m128 r2 = _mm_mul_ps(_mm_loadu_ps(&m20_), vec);
        __m128 r3 = _mm_setzero_ps();
        __m128 t2 = _mm_unpacklo_ps(r2, r3);
        __m128 t3 = _mm_unpackhi_ps(r2, r3);
        t2 = _mm_add_ps(t2, t3);
        vec = _mm_add_ps(_mm_movelh_ps(t0, t2), _mm_movehl_ps(t2, t0));

        return Vector3(
            _mm_cvtss_f32(vec),
            _mm_cvtss_f32(_mm_shuffle_ps(vec, vec, _MM_SHUFFLE(1, 1, 1, 1))),
            _mm_cvtss_f32(_mm_movehl_ps(vec, vec)));
#else
        return Vector3(
            (m00_ * rhs.x_ + m01_ * rhs.y_ + m02_ * rhs.z_ + m03_ * rhs.w_),
            (m10_ * rhs.x_ + m11_ * rhs.y_ + m12_ * rhs.z_ + m13_ * rhs.w_),
            (m20_ * rhs.x_ + m21_ * rhs.y_ + m22_ * rhs.z_ + m23_ * rhs.w_)
        );
#endif
    }

    /// Add a matrix.
    Matrix3x4 operator +(const Matrix3x4& rhs) const
    {
#ifdef URHO3D_SSE
        Matrix3x4 ret;
        _mm_storeu_ps(&ret.m00_, _mm_add_ps(_mm_loadu_ps(&m00_), _mm_loadu_ps(&rhs.m00_)));
        _mm_storeu_ps(&ret.m10_, _mm_add_ps(_mm_loadu_ps(&m10_), _mm_loadu_ps(&rhs.m10_)));
        _mm_storeu_ps(&ret.m20_, _mm_add_ps(_mm_loadu_ps(&m20_), _mm_loadu_ps(&rhs.m20_)));
        return ret;
#else
        return Matrix3x4(
            m00_ + rhs.m00_,
            m01_ + rhs.m01_,
            m02_ + rhs.m02_,
            m03_ + rhs.m03_,
            m10_ + rhs.m10_,
            m11_ + rhs.m11_,
            m12_ + rhs.m12_,
            m13_ + rhs.m13_,
            m20_ + rhs.m20_,
            m21_ + rhs.m21_,
            m22_ + rhs.m22_,
            m23_ + rhs.m23_
        );
#endif
    }

    /// Subtract a matrix.
    Matrix3x4 operator -(const Matrix3x4& rhs) const
    {
#ifdef URHO3D_SSE
        Matrix3x4 ret;
        _mm_storeu_ps(&ret.m00_, _mm_sub_ps(_mm_loadu_ps(&m00_), _mm_loadu_ps(&rhs.m00_)));
        _mm_storeu_ps(&ret.m10_, _mm_sub_ps(_mm_loadu_ps(&m10_), _mm_loadu_ps(&rhs.m10_)));
        _mm_storeu_ps(&ret.m20_, _mm_sub_ps(_mm_loadu_ps(&m20_), _mm_loadu_ps(&rhs.m20_)));
        return ret;
#else
        return Matrix3x4(
            m00_ - rhs.m00_,
            m01_ - rhs.m01_,
            m02_ - rhs.m02_,
            m03_ - rhs.m03_,
            m10_ - rhs.m10_,
            m11_ - rhs.m11_,
            m12_ - rhs.m12_,
            m13_ - rhs.m13_,
            m20_ - rhs.m20_,
            m21_ - rhs.m21_,
            m22_ - rhs.m22_,
            m23_ - rhs.m23_
        );
#endif
    }

    /// Multiply with a scalar.
    Matrix3x4 operator *(float rhs) const
    {
#ifdef URHO3D_SSE
        Matrix3x4 ret;
        const __m128 mul = _mm_set1_ps(rhs);
        _mm_storeu_ps(&ret.m00_, _mm_mul_ps(_mm_loadu_ps(&m00_), mul));
        _mm_storeu_ps(&ret.m10_, _mm_mul_ps(_mm_loadu_ps(&m10_), mul));
        _mm_storeu_ps(&ret.m20_, _mm_mul_ps(_mm_loadu_ps(&m20_), mul));
        return ret;
#else
        return Matrix3x4(
            m00_ * rhs,
            m01_ * rhs,
            m02_ * rhs,
            m03_ * rhs,
            m10_ * rhs,
            m11_ * rhs,
            m12_ * rhs,
            m13_ * rhs,
            m20_ * rhs,
            m21_ * rhs,
            m22_ * rhs,
            m23_ * rhs
        );
#endif
    }

    /// Multiply a matrix.
    Matrix3x4 operator *(const Matrix3x4& rhs) const
    {
#ifdef URHO3D_SSE
        Matrix3x4 out;

        __m128 r0 = _mm_loadu_ps(&rhs.m00_);
        __m128 r1 = _mm_loadu_ps(&rhs.m10_);
        __m128 r2 = _mm_loadu_ps(&rhs.m20_);
        __m128 r3 = _mm_set_ps(1.f, 0.f, 0.f, 0.f);

        __m128 l = _mm_loadu_ps(&m00_);
        __m128 t0 = _mm_mul_ps(_mm_shuffle_ps(l, l, _MM_SHUFFLE(0, 0, 0, 0)), r0);
        __m128 t1 = _mm_mul_ps(_mm_shuffle_ps(l, l, _MM_SHUFFLE(1, 1, 1, 1)), r1);
        __m128 t2 = _mm_mul_ps(_mm_shuffle_ps(l, l, _MM_SHUFFLE(2, 2, 2, 2)), r2);
        __m128 t3 = _mm_mul_ps(l, r3);
        _mm_storeu_ps(&out.m00_, _mm_add_ps(_mm_add_ps(t0, t1), _mm_add_ps(t2, t3)));

        l = _mm_loadu_ps(&m10_);
        t0 = _mm_mul_ps(_mm_shuffle_ps(l, l, _MM_SHUFFLE(0, 0, 0, 0)), r0);
        t1 = _mm_mul_ps(_mm_shuffle_ps(l, l, _MM_SHUFFLE(1, 1, 1, 1)), r1);
        t2 = _mm_mul_ps(_mm_shuffle_ps(l, l, _MM_SHUFFLE(2, 2, 2, 2)), r2);
        t3 = _mm_mul_ps(l, r3);
        _mm_storeu_ps(&out.m10_, _mm_add_ps(_mm_add_ps(t0, t1), _mm_add_ps(t2, t3)));

        l = _mm_loadu_ps(&m20_);
        t0 = _mm_mul_ps(_mm_shuffle_ps(l, l, _MM_SHUFFLE(0, 0, 0, 0)), r0);
        t1 = _mm_mul_ps(_mm_shuffle_ps(l, l, _MM_SHUFFLE(1, 1, 1, 1)), r1);
        t2 = _mm_mul_ps(_mm_shuffle_ps(l, l, _MM_SHUFFLE(2, 2, 2, 2)), r2);
        t3 = _mm_mul_ps(l, r3);
        _mm_storeu_ps(&out.m20_, _mm_add_ps(_mm_add_ps(t0, t1), _mm_add_ps(t2, t3)));

        return out;
#else
        return Matrix3x4(
            m00_ * rhs.m00_ + m01_ * rhs.m10_ + m02_ * rhs.m20_,
            m00_ * rhs.m01_ + m01_ * rhs.m11_ + m02_ * rhs.m21_,
            m00_ * rhs.m02_ + m01_ * rhs.m12_ + m02_ * rhs.m22_,
            m00_ * rhs.m03_ + m01_ * rhs.m13_ + m02_ * rhs.m23_ + m03_,
            m10_ * rhs.m00_ + m11_ * rhs.m10_ + m12_ * rhs.m20_,
            m10_ * rhs.m01_ + m11_ * rhs.m11_ + m12_ * rhs.m21_,
            m10_ * rhs.m02_ + m11_ * rhs.m12_ + m12_ * rhs.m22_,
            m10_ * rhs.m03_ + m11_ * rhs.m13_ + m12_ * rhs.m23_ + m13_,
            m20_ * rhs.m00_ + m21_ * rhs.m10_ + m22_ * rhs.m20_,
            m20_ * rhs.m01_ + m21_ * rhs.m11_ + m22_ * rhs.m21_,
            m20_ * rhs.m02_ + m21_ * rhs.m12_ + m22_ * rhs.m22_,
            m20_ * rhs.m03_ + m21_ * rhs.m13_ + m22_ * rhs.m23_ + m23_
        );
#endif
    }

    /// Multiply a 4x4 matrix.
    Matrix4 operator *(const Matrix4& rhs) const
    {
#ifdef URHO3D_SSE
        Matrix4 out;

        __m128 r0 = _mm_loadu_ps(&rhs.m00_);
        __m128 r1 = _mm_loadu_ps(&rhs.m10_);
        __m128 r2 = _mm_loadu_ps(&rhs.m20_);
        __m128 r3 = _mm_loadu_ps(&rhs.m30_);

        __m128 l = _mm_loadu_ps(&m00_);
        __m128 t0 = _mm_mul_ps(_mm_shuffle_ps(l, l, _MM_SHUFFLE(0, 0, 0, 0)), r0);
        __m128 t1 = _mm_mul_ps(_mm_shuffle_ps(l, l, _MM_SHUFFLE(1, 1, 1, 1)), r1);
        __m128 t2 = _mm_mul_ps(_mm_shuffle_ps(l, l, _MM_SHUFFLE(2, 2, 2, 2)), r2);
        __m128 t3 = _mm_mul_ps(_mm_shuffle_ps(l, l, _MM_SHUFFLE(3, 3, 3, 3)), r3);
        _mm_storeu_ps(&out.m00_, _mm_add_ps(_mm_add_ps(t0, t1), _mm_add_ps(t2, t3)));

        l = _mm_loadu_ps(&m10_);
        t0 = _mm_mul_ps(_mm_shuffle_ps(l, l, _MM_SHUFFLE(0, 0, 0, 0)), r0);
        t1 = _mm_mul_ps(_mm_shuffle_ps(l, l, _MM_SHUFFLE(1, 1, 1, 1)), r1);
        t2 = _mm_mul_ps(_mm_shuffle_ps(l, l, _MM_SHUFFLE(2, 2, 2, 2)), r2);
        t3 = _mm_mul_ps(_mm_shuffle_ps(l, l, _MM_SHUFFLE(3, 3, 3, 3)), r3);
        _mm_storeu_ps(&out.m10_, _mm_add_ps(_mm_add_ps(t0, t1), _mm_add_ps(t2, t3)));

        l = _mm_loadu_ps(&m20_);
        t0 = _mm_mul_ps(_mm_shuffle_ps(l, l, _MM_SHUFFLE(0, 0, 0, 0)), r0);
        t1 = _mm_mul_ps(_mm_shuffle_ps(l, l, _MM_SHUFFLE(1, 1, 1, 1)), r1);
        t2 = _mm_mul_ps(_mm_shuffle_ps(l, l, _MM_SHUFFLE(2, 2, 2, 2)), r2);
        t3 = _mm_mul_ps(_mm_shuffle_ps(l, l, _MM_SHUFFLE(3, 3, 3, 3)), r3);
        _mm_storeu_ps(&out.m20_, _mm_add_ps(_mm_add_ps(t0, t1), _mm_add_ps(t2, t3)));

        _mm_storeu_ps(&out.m30_, r3);

        return out;
#else
        return Matrix4(
            m00_ * rhs.m00_ + m01_ * rhs.m10_ + m02_ * rhs.m20_ + m03_ * rhs.m30_,
            m00_ * rhs.m01_ + m01_ * rhs.m11_ + m02_ * rhs.m21_ + m03_ * rhs.m31_,
            m00_ * rhs.m02_ + m01_ * rhs.m12_ + m02_ * rhs.m22_ + m03_ * rhs.m32_,
            m00_ * rhs.m03_ + m01_ * rhs.m13_ + m02_ * rhs.m23_ + m03_ * rhs.m33_,
            m10_ * rhs.m00_ + m11_ * rhs.m10_ + m12_ * rhs.m20_ + m13_ * rhs.m30_,
            m10_ * rhs.m01_ + m11_ * rhs.m11_ + m12_ * rhs.m21_ + m13_ * rhs.m31_,
            m10_ * rhs.m02_ + m11_ * rhs.m12_ + m12_ * rhs.m22_ + m13_ * rhs.m32_,
            m10_ * rhs.m03_ + m11_ * rhs.m13_ + m12_ * rhs.m23_ + m13_ * rhs.m33_,
            m20_ * rhs.m00_ + m21_ * rhs.m10_ + m22_ * rhs.m20_ + m23_ * rhs.m30_,
            m20_ * rhs.m01_ + m21_ * rhs.m11_ + m22_ * rhs.m21_ + m23_ * rhs.m31_,
            m20_ * rhs.m02_ + m21_ * rhs.m12_ + m22_ * rhs.m22_ + m23_ * rhs.m32_,
            m20_ * rhs.m03_ + m21_ * rhs.m13_ + m22_ * rhs.m23_ + m23_ * rhs.m33_,
            rhs.m30_,
            rhs.m31_,
            rhs.m32_,
            rhs.m33_
        );
#endif
    }

    /// Set translation elements.
    void SetTranslation(const Vector3& translation)
    {
        m03_ = translation.x_;
        m13_ = translation.y_;
        m23_ = translation.z_;
    }

    /// Set rotation elements from a 3x3 matrix.
    void SetRotation(const Matrix3& rotation)
    {
        m00_ = rotation.m00_;
        m01_ = rotation.m01_;
        m02_ = rotation.m02_;
        m10_ = rotation.m10_;
        m11_ = rotation.m11_;
        m12_ = rotation.m12_;
        m20_ = rotation.m20_;
        m21_ = rotation.m21_;
        m22_ = rotation.m22_;
    }

    /// Set scaling elements.
    void SetScale(const Vector3& scale)
    {
        m00_ = scale.x_;
        m11_ = scale.y_;
        m22_ = scale.z_;
    }

    /// Set uniform scaling elements.
    void SetScale(float scale)
    {
        m00_ = scale;
        m11_ = scale;
        m22_ = scale;
    }

    /// Return the combined rotation and scaling matrix.
    Matrix3 ToMatrix3() const
    {
        return Matrix3(
            m00_,
            m01_,
            m02_,
            m10_,
            m11_,
            m12_,
            m20_,
            m21_,
            m22_
        );
    }

    /// Convert to a 4x4 matrix by filling in an identity last row.
    Matrix4 ToMatrix4() const
    {
#ifdef URHO3D_SSE
        Matrix4 ret;
        _mm_storeu_ps(&ret.m00_, _mm_loadu_ps(&m00_));
        _mm_storeu_ps(&ret.m10_, _mm_loadu_ps(&m10_));
        _mm_storeu_ps(&ret.m20_, _mm_loadu_ps(&m20_));
        _mm_storeu_ps(&ret.m30_, _mm_set_ps(1.f, 0.f, 0.f, 0.f));
        return ret;
#else

        return Matrix4(
            m00_,
            m01_,
            m02_,
            m03_,
            m10_,
            m11_,
            m12_,
            m13_,
            m20_,
            m21_,
            m22_,
            m23_,
            0.0f,
            0.0f,
            0.0f,
            1.0f
        );
#endif
    }

    /// Return the rotation matrix with scaling removed.
    Matrix3 RotationMatrix() const
    {
        Vector3 invScale(
            1.0f / sqrtf(m00_ * m00_ + m10_ * m10_ + m20_ * m20_),
            1.0f / sqrtf(m01_ * m01_ + m11_ * m11_ + m21_ * m21_),
            1.0f / sqrtf(m02_ * m02_ + m12_ * m12_ + m22_ * m22_)
        );

        return ToMatrix3().Scaled(invScale);
    }

    /// Return the translation part.
    Vector3 Translation() const
    {
        return Vector3(
            m03_,
            m13_,
            m23_
        );
    }

    /// Return the rotation part.
    Quaternion Rotation() const { return Quaternion(RotationMatrix()); }

    /// Return the scaling part.
    Vector3 Scale() const
    {
        return Vector3(
            sqrtf(m00_ * m00_ + m10_ * m10_ + m20_ * m20_),
            sqrtf(m01_ * m01_ + m11_ * m11_ + m21_ * m21_),
            sqrtf(m02_ * m02_ + m12_ * m12_ + m22_ * m22_)
        );
    }

    /// Return the scaling part with the sign. Reference rotation matrix is required to avoid ambiguity.
    Vector3 SignedScale(const Matrix3& rotation) const
    {
        return Vector3(
            rotation.m00_ * m00_ + rotation.m10_ * m10_ + rotation.m20_ * m20_,
            rotation.m01_ * m01_ + rotation.m11_ * m11_ + rotation.m21_ * m21_,
            rotation.m02_ * m02_ + rotation.m12_ * m12_ + rotation.m22_ * m22_
        );
    }

    /// Test for equality with another matrix with epsilon.
    bool Equals(const Matrix3x4& rhs) const
    {
        const float* leftData = Data();
        const float* rightData = rhs.Data();

        for (unsigned i = 0; i < 12; ++i)
        {
            if (!Urho3D::Equals(leftData[i], rightData[i]))
                return false;
        }

        return true;
    }

    /// Return decomposition to translation, rotation and scale.
    void Decompose(Vector3& translation, Quaternion& rotation, Vector3& scale) const;

    /// Return inverse.
    Matrix3x4 Inverse() const;

    /// Return float data.
    const float* Data() const { return &m00_; }

    /// Return matrix element.
    float Element(unsigned i, unsigned j) const { return Data()[i * 4 + j]; }

    /// Return matrix row.
    Vector4 Row(unsigned i) const { return Vector4(Element(i, 0), Element(i, 1), Element(i, 2), Element(i, 3)); }

    /// Return matrix column.
    Vector3 Column(unsigned j) const { return Vector3(Element(0, j), Element(1, j), Element(2, j)); }

    /// Return whether any element is NaN.
    bool IsNaN() const
    {
        const float* data = Data();
        for (unsigned i = 0; i < 12; ++i)
        {
            if (Urho3D::IsNaN(data[i]))
                return true;
        }
        return false;
    }

    /// Return whether any element is Inf.
    bool IsInf() const
    {
        const float* data = Data();
        for (unsigned i = 0; i < 12; ++i)
        {
            if (Urho3D::IsInf(data[i]))
                return true;
        }
        return false;
    }

    /// Return as string.
    String ToString() const;

    float m00_;
    float m01_;
    float m02_;
    float m03_;
    float m10_;
    float m11_;
    float m12_;
    float m13_;
    float m20_;
    float m21_;
    float m22_;
    float m23_;

    /// Zero matrix.
    static const Matrix3x4 ZERO;
    /// Identity matrix.
    static const Matrix3x4 IDENTITY;

#ifdef URHO3D_SSE
private:
    /// \brief Sets this matrix from the given translation, rotation (as quaternion (w,x,y,z)), and nonuniform scale (x,y,z) parameters. Note: the w component of the scale parameter passed to this function must be 1.
    void inline SetFromTRS(__m128 t, __m128 q, __m128 s)
    {
        q = _mm_shuffle_ps(q, q, _MM_SHUFFLE(0, 3, 2, 1));
        __m128 one = _mm_set_ps(0, 0, 0, 1);
        const __m128 sseX1 = _mm_castsi128_ps(_mm_set_epi32((int)0x80000000UL, (int)0x80000000UL, 0, (int)0x80000000UL));
        __m128 q2 = _mm_add_ps(q, q);
        __m128 t2 = _mm_add_ss(_mm_xor_ps(_mm_mul_ps(_mm_shuffle_ps(q, q, _MM_SHUFFLE(3, 3, 3, 2)), _mm_shuffle_ps(q2, q2, _MM_SHUFFLE(0, 1, 2, 2))), sseX1), one);
        const __m128 sseX0 = _mm_shuffle_ps(sseX1, sseX1, _MM_SHUFFLE(0, 3, 2, 1));
        __m128 t0 = _mm_mul_ps(_mm_shuffle_ps(q, q, _MM_SHUFFLE(1, 0, 0, 1)), _mm_shuffle_ps(q2, q2, _MM_SHUFFLE(2, 2, 1, 1)));
        __m128 t1 = _mm_xor_ps(t0, sseX0);
        __m128 r0 = _mm_sub_ps(t2, t1);
        __m128 xx2 = _mm_mul_ss(q, q2);
        __m128 r1 = _mm_sub_ps(_mm_xor_ps(t2, sseX0), _mm_move_ss(t1, xx2));
        r1 = _mm_shuffle_ps(r1, r1, _MM_SHUFFLE(2, 3, 0, 1));
        __m128 r2 = _mm_shuffle_ps(_mm_movehl_ps(r0, r1), _mm_sub_ss(_mm_sub_ss(one, xx2), t0), _MM_SHUFFLE(2, 0, 3, 1));
        __m128 tmp0 = _mm_unpacklo_ps(r0, r1);
        __m128 tmp2 = _mm_unpacklo_ps(r2, t);
        __m128 tmp1 = _mm_unpackhi_ps(r0, r1);
        __m128 tmp3 = _mm_unpackhi_ps(r2, t);
        _mm_storeu_ps(&m00_, _mm_mul_ps(_mm_movelh_ps(tmp0, tmp2), s));
        _mm_storeu_ps(&m10_, _mm_mul_ps(_mm_movehl_ps(tmp2, tmp0), s));
        _mm_storeu_ps(&m20_, _mm_mul_ps(_mm_movelh_ps(tmp1, tmp3), s));
    }
#endif
};

/// Multiply a 3x4 matrix with a scalar.
inline Matrix3x4 operator *(float lhs, const Matrix3x4& rhs) { return rhs * lhs; }

}
