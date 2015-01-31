//
// Copyright (c) 2008-2015 the Urho3D project.
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

#include "../Math/Color.h"
#include "../Core/Variant.h"
#include "../Math/Vector2.h"
#include "../Math/Vector3.h"
#include "../Math/Vector4.h"

namespace Urho3D
{

enum InterpolationMode
{
    BEZIER_CURVE = 0
};

/// Spline class to get a point on it based off the interpolation mode.
class URHO3D_API Spline
{
public:
    /// Default constructor.
    Spline();
    /// Constructor setting InterpolationMode.
    Spline(InterpolationMode mode);
    /// Constructor setting Knots and InterpolationMode.
    Spline(const Vector<Variant>& knots, InterpolationMode mode = BEZIER_CURVE);
    /// Copy constructor.
    Spline(const Spline& rhs);

    /// Copy operator.
    void operator= (const Spline& rhs)
    {
        knots_ = rhs.knots_;
        interpolationMode_ = rhs.interpolationMode_;
    }
    /// Equality operator.
    bool operator== (const Spline& rhs) const
    {
        return (knots_ == rhs.knots_ && interpolationMode_ == rhs.interpolationMode_);
    }
    /// Non Equality operator.
    bool operator!= (const Spline& rhs) const
    {
        return !(*this == rhs);
    }

    /// Return the ImplementationMode.
    InterpolationMode GetInterpolationMode() const { return interpolationMode_; }
    /// Return the Knots of the Spline.
    const VariantVector& GetKnots() const { return knots_; }
    /// Return the Knot at the specific index.
    Variant GetKnot(unsigned index) const { return knots_[index]; }
    /// Return the T of the point of the Spline at f from 0.f - 1.f.
    Variant GetPoint(float f) const;
    /// Set the InterpolationMode of the Spline.
    void SetInterpolationMode(InterpolationMode interpolationMode) { interpolationMode_ = interpolationMode; }
    /// Set the Knots of the Spline.
    void SetKnots(const Vector<Variant>& knots) { knots_ = knots; }
    /// Set the Knot value of an existing Knot.
    void SetKnot(const Variant& knot, unsigned index);
    /// Add a Knot to the end of the Spline.
    void AddKnot(const Variant& knot);
    /// Add a Knot to the Spline at a specific index.
    void AddKnot(const Variant& knot, unsigned index);
    /// Remove the last Knot on the Spline.
    void RemoveKnot() { knots_.Pop(); }
    /// Remove the Knot at the specific index.
    void RemoveKnot(unsigned index) { knots_.Erase(index); }
    /// Clear the Spline.
    void Clear() { knots_.Clear(); }

private:
    /// Perform Bezier Interpolation on the Spline.
    Variant BezierInterpolation(const Vector<Variant>& knots, float t) const;
    /// LinearInterpolation between two Variants based on underlying type.
    Variant LinearInterpolation(const Variant& lhs, const Variant& rhs, float t) const;

    /// InterpolationMode.
    InterpolationMode interpolationMode_;
    /// Knots on the Spline.
    VariantVector knots_;
};

}
