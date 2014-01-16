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
    void SetControlPoints(const Vector<Vector3> controlPoints);
    /// Set the Interpolation Mode.
    void SetInterpolationMode(InterpolationMode interpolationMode);
    /// Set the movement Speed.
    void SetSpeed(float speed) { speed_ = speed; }

    /// Get the Control Points.
    const Vector<Vector3>& GetControlPoints() const { return controlPoints_; }
    /// Get the Interpolation Mode.
    InterpolationMode GetInterpolationMode() const { return interpolationMode_; }
    /// Get the movement Speed.
    float GetSpeed() const { return speed_; }

    /// Add a Control Point to the end.
    void Push(const Vector3& controlPoint);
    /// Remove a Control Point from the end.
    void Pop();

    /// Attach the Parent to the path at the position it was at last or at the start if after Reset was called or no movement has occurred.
    void Attach();
    /// Move the parent node to the next position along the Spline based off the Speed value.
    void Move();
    /// Detach the Parent from the path. Movement is not reset.
    void Detach();
    /// Reset movement along the path.
    void Reset();
    /// Returns whether the movement along the Spline complete.
    bool IsFinished() const { return traveled_ >= 1.0f; }
    /// Returns whether the parent node is attached.
    bool IsAttached() const { return attached_; }

    VariantVector GetControlPointsAttr() const;
    void SetControlPointsAttr(VariantVector value);

private:
    /// Calculate the length of the Spline. Used for movement calculations.
    void CalculateLength();
    /// Move the parent node along the Spline in Beizer Mode.
    Vector3 BezierMove(Vector<Vector3>& controlPoints, float t);

    /// The Control Points of the Spline.
    Vector<Vector3> controlPoints_;
    /// The Interpolation Mode of the Spline.
    InterpolationMode interpolationMode_;
    /// The Speed of movement along the Spline.
    float speed_;

    /// The time when movement started along the Spline.
    float startTime_;
    /// Amount of time that has elapsed while moving.
    float elapsedTime_;
    /// The fraction of the Spline covered.
    float traveled_;
    /// The length of the Spline.
    float length_;
    /// The parent is attached to the spline.
    bool attached_;
};
}