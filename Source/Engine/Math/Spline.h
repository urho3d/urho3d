// Copyright (c) 2008-2013 the Urho3D project.
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

#include "Variant.h"
#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"
#include "Color.h"

namespace Urho3D
{

enum InterpolationMode
{
    BEZIER_CURVE = 0
};

/// Spline class to get a point on it based off the interpolation mode.
template<typename T>
class URHO3D_API Spline
{
public:
    /// Ctor.
    Spline() :
    interpolationMode_(BEZIER_CURVE)
    {
    }

    /// Ctor.
    Spline(InterpolationMode mode) :
    interpolationMode_(mode)
    {
    }

    /// Ctor.
    Spline(const PODVector<T>& knots, InterpolationMode mode = BEZIER_CURVE) :
    interpolationMode_(mode),
    knots_(knots)
    {
    }

    /// Ctor.
    Spline(const Spline& rhs) :
    interpolationMode_(rhs.interpolationMode_),
    knots_(rhs.knots_)
    {
    }

    /// Dtor.
    ~Spline()
    {
        Clear();
    }

    /// Return the ImplementationMode.
    InterpolationMode GetInterpolationMode() const
    { 
        return interpolationMode_; 
    }

    /// Return the Knots of the Spline.
    const PODVector<T>& GetKnots() const
    { 
        return knots_; 
    }

    /// Return the Knot at the specific index.
    const T GetKnot(unsigned index) const
    {
        return knots_[index];
    }

    /// Return the T of the point of the Spline at f from 0.f - 1.f.
    T GetPoint(float f) const
    {
        if (knots_.Size() < 2)
            return knots_.Size() == 1 ? knots_[0] : T();

        if (f > 1.f)
            f = 1.f;
        else if (f < 0.f)
            f = 0.f;

        switch (interpolationMode_)
        {
        case BEZIER_CURVE:
        default:
            return BezierInterpolation(knots_, f);
        }
    }

    /// Set the InterpolationMode of the Spline.
    void SetInterpolationMode(InterpolationMode interpolationMode) 
    { 
        interpolationMode_ = interpolationMode; 
    }

    /// Set the Knots of the Spline.
    void SetKnots(const PODVector<T>& knots) 
    { 
        knots_ = knots_; 
    }

    /// Add a Knot to the end of the Spline.
    void AddKnot(const T& knot)
    {
        knots_.Push(knot);
    }

    /// Add a Knot to the Spline at a specific index.
    void AddKnot(const T& knot, unsigned index)
    {
        knots_.Insert(index, knot);
    }

    /// Remove the last Knot on the Spline.
    void RemoveKnot() 
    { 
        knots_.Pop(); 
    }

    /// Remove the Knot at the specific index.
    void RemoveKnot(unsigned index)
    {
        knots_.Erase(index);
    }

    /// Clear the Spline.
    void Clear()
    {
        knots_.Clear();
    }

private:
    /// Perform Bezier Interpolation on the Spline.
    T BezierInterpolation(const PODVector<T>& knots, float t) const
    {
        if (knots.Size() == 2)
        {
            return LinearInterpolation(knots[0], knots[1], t);
        }
        else
        {
            PODVector<T> interpolatedKnots;
            for (unsigned i = 1; i < knots.Size(); i++)
            {
                interpolatedKnots.Push(LinearInterpolation(knots[i - 1], knots[i], t));
            }
            return BezierInterpolation(interpolatedKnots, t);
        }
    }

    /// Empty LinearInterpolation for Android or IOS implementations that don't support C++11 and the static_assert.
    T LinearInterpolation(const T& lhs, const T& rhs, float t) const
    {
        return T();
    }

    /// InterpolationMode.
    InterpolationMode interpolationMode_;
    /// Knots on the Spline.
    PODVector<T> knots_;
};

/// Specialized LinearInterpolation for float.
template<> float Urho3D::Spline<float>::LinearInterpolation(const float& lhs, const float& rhs, float t) const
{
    return Lerp(lhs, rhs, t);
}

/// Specialized LinearInterpolation for Vector2.
template<> Vector2 Urho3D::Spline<Vector2>::LinearInterpolation(const Vector2& lhs, const Vector2& rhs, float t) const
{
    return lhs.Lerp(rhs, t);
}

/// Specialized LinearInterpolation for Vector3.
template<> Vector3 Urho3D::Spline<Vector3>::LinearInterpolation(const Vector3& lhs, const Vector3& rhs, float t) const
{
    return lhs.Lerp(rhs, t);
}

/// Specialized LinearInterpolation for Vector4.
template<> Vector4 Urho3D::Spline<Vector4>::LinearInterpolation(const Vector4& lhs, const Vector4& rhs, float t) const
{
    return lhs.Lerp(rhs, t);
}

/// Specialized LinearInterpolation for Color.
template<> Color Urho3D::Spline<Color>::LinearInterpolation(const Color& lhs, const Color& rhs, float t) const
{
    return lhs.Lerp(rhs, t);
}

}