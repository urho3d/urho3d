// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

/// \file

#pragma once

#include "../Core/Variant.h"
#include "../Math/Color.h"
#include "../Math/Vector2.h"
#include "../Math/Vector3.h"
#include "../Math/Vector4.h"

namespace Urho3D
{

enum InterpolationMode
{
    /// Bezier interpolation.
    BEZIER_CURVE = 0,
    /// Catmull-Rom interpolation. The first and last knots control velocity and are not included on the path.
    CATMULL_ROM_CURVE,
    /// Linear interpolation.
    LINEAR_CURVE,
    /// Catmull-Rom full path interpolation. Start and end knots are duplicated or looped as necessary to move through the full path.
    CATMULL_ROM_FULL_CURVE
};

/// Spline class to get a point on it based off the interpolation mode.
class URHO3D_API Spline
{
public:
    /// Default constructor.
    Spline();
    /// Constructor setting interpolation mode.
    explicit Spline(InterpolationMode mode);
    /// Constructor setting knots and interpolation mode.
    explicit Spline(const Vector<Variant>& knots, InterpolationMode mode = BEZIER_CURVE);
    /// Copy constructor.
    Spline(const Spline& rhs) = default;

    /// Copy operator.
    Spline& operator =(const Spline& rhs) = default;

    /// Equality operator.
    bool operator ==(const Spline& rhs) const
    {
        return (knots_ == rhs.knots_ && interpolationMode_ == rhs.interpolationMode_);
    }

    /// Inequality operator.
    bool operator !=(const Spline& rhs) const
    {
        return !(*this == rhs);
    }

    /// Return the interpolation mode.
    /// @property
    InterpolationMode GetInterpolationMode() const { return interpolationMode_; }

    /// Return the knots of the spline.
    const VariantVector& GetKnots() const { return knots_; }

    /// Return the knot at the specific index.
    /// @property
    Variant GetKnot(unsigned index) const { return knots_[index]; }

    /// Return the T of the point of the spline at f from 0.f - 1.f.
    Variant GetPoint(float f) const;

    /// Set the interpolation mode.
    /// @property
    void SetInterpolationMode(InterpolationMode interpolationMode) { interpolationMode_ = interpolationMode; }

    /// Set the knots of the spline.
    void SetKnots(const Vector<Variant>& knots) { knots_ = knots; }

    /// Set the value of an existing knot.
    void SetKnot(const Variant& knot, unsigned index);
    /// Add a knot to the end of the spline.
    void AddKnot(const Variant& knot);
    /// Add a knot to the spline at a specific index.
    void AddKnot(const Variant& knot, unsigned index);

    /// Remove the last knot on the spline.
    void RemoveKnot() { knots_.Pop(); }

    /// Remove the knot at the specific index.
    void RemoveKnot(unsigned index) { knots_.Erase(index); }

    /// Clear the spline.
    void Clear() { knots_.Clear(); }

private:
    /// Perform Bezier interpolation on the spline.
    Variant BezierInterpolation(const Vector<Variant>& knots, float t) const;
    /// Perform Spline interpolation on the spline.
    Variant CatmullRomInterpolation(const Vector<Variant>& knots, float t) const;
    /// Perform linear interpolation on the spline.
    Variant LinearInterpolation(const Vector<Variant>& knots, float t) const;
    /// Linear interpolation between two Variants based on underlying type.
    Variant LinearInterpolation(const Variant& lhs, const Variant& rhs, float t) const;

    /// Interpolation mode.
    InterpolationMode interpolationMode_;
    /// Knots on the spline.
    VariantVector knots_;
};

}
