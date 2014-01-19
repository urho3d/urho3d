//
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

#include "Component.h"
#include "Vector3.h"

namespace Urho3D
{
/// Interpolation Mode for a Spline.
enum InterpolationMode
{
    BEZIER_CURVE
};

/// Spline for creating smooth movement based on Speed along a set of Control Points modified by the Interpolation Mode.
class URHO3D_API Spline : public Component
{
    OBJECT(Spline)

public:
    /// Construct an Empty Spline.
    Spline(Context* context);
    /// Register object factory.
    static void RegisterObject(Context* context);

    /// Set the Control Points from an already defined set.
    void SetControlPoints(const PODVector<Vector3>& controlPoints);
    /// Set the Interpolation Mode.
    void SetInterpolationMode(InterpolationMode interpolationMode) { interpolationMode_ = interpolationMode; }
    /// Set the movement Speed.
    void SetSpeed(float speed) { speed_ = speed; }
    /// Set the parent node's position on the Spline.
    void SetPosition(float factor);

    /// Get the Control Points.
    const PODVector<Vector3>& GetControlPoints() const { return controlPoints_; }
    /// Get the Interpolation Mode.
    InterpolationMode GetInterpolationMode() const { return interpolationMode_; }
    /// Get the movement Speed.
    float GetSpeed() const { return speed_; }
    /// Get the parent node's last position on the spline.
    Vector3 GetPosition() const;

    /// Add a Control Point to the end.
    void Push(const Vector3& controlPoint);
    /// Remove a Control Point from the end.
    void Pop();
    /// Get a point on the spline from 0.f to 1.f where 0 is the start and 1 is the end.
    Vector3 GetPoint(float factor) const;

    /// Move the parent node to the next position along the Spline based off the Speed value.
    void Move(float timeStep);
    /// Reset movement along the path.
    void Reset();
    /// Returns whether the movement along the Spline complete.
    bool IsFinished() const { return traveled_ >= 1.0f; }

    VariantVector GetControlPointsAttr() const;
    void SetControlPointsAttr(VariantVector value);

private:
    /// Calculate the length of the Spline. Used for movement calculations.
    void CalculateLength();
    /// Move the parent node along the Spline in Bezier Mode.
    Vector3 BezierMove(const PODVector<Vector3>& controlPoints, float t) const;

    /// The Control Points of the Spline.
    PODVector<Vector3> controlPoints_;
    /// The Interpolation Mode of the Spline.
    InterpolationMode interpolationMode_;
    /// The Speed of movement along the Spline.
    float speed_;

    /// Amount of time that has elapsed while moving.
    float elapsedTime_;
    /// The fraction of the Spline covered.
    float traveled_;
    /// The length of the Spline.
    float length_;
    /// Whether the length needs to be recalculated. Will only be true after a push or pop.
    bool dirty_;
};
}