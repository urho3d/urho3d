//
// Copyright (c) 2008-2014 the Urho3D project.
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
#include "DebugRenderer.h"
#include "Vector3.h"
#include "Spline.h"

namespace Urho3D
{

/// Spline for creating smooth movement based on Speed along a set of Control Points modified by the Interpolation Mode.
class URHO3D_API SplinePath : public Component
{
    OBJECT(SplinePath)

public:
    /// Construct an Empty Spline.
    SplinePath(Context* context);
    /// Destructor.
    virtual ~SplinePath();
    /// Register object factory.
    static void RegisterObject(Context* context);

    /// Apply Attributes to the Node.
    virtual void ApplyAttributes();
    /// Draw the Debug Geometry.
    virtual void DrawDebugGeometry(DebugRenderer* debug, bool depthTest);

    /// Set the Interpolation Mode.
    void SetInterpolationMode(InterpolationMode interpolationMode);
    /// Set the movement Speed.
    void SetSpeed(float speed) { speed_ = speed; }
    /// Set the parent node's position on the Spline.
    void SetPosition(float factor);

    /// Get the Interpolation Mode.
    InterpolationMode GetInterpolationMode() const { return spline_.GetInterpolationMode(); }
    /// Get the movement Speed.
    float GetSpeed() const { return speed_; }
    /// Get the parent node's last position on the spline.
    Vector3 GetPosition() const;

    /// Get a point on the spline from 0.f to 1.f where 0 is the start and 1 is the end.
    Vector3 GetPoint(float factor) const;

    /// Move the parent node to the next position along the Spline based off the Speed value.
    void Move(float timeStep);
    /// Reset movement along the path.
    void Reset();
    /// Returns whether the movement along the Spline complete.
    bool IsFinished() const { return traveled_ >= 1.0f; }

protected:
    virtual void OnMarkedDirty(Node* node);
    virtual void OnNodeSetEnabled(Node* node);

private:
    /// Calculate the length of the Spline. Used for movement calculations.
    void CalculateLength();
    /// Handle Points Changed.
    void PointAdded(StringHash eventType, VariantMap& eventData);
    /// Handle Points Changed.
    void PointRemoved(StringHash eventType, VariantMap& eventData);
    /// Handle Points Changed.
    void PointsUpdated(StringHash eventType, VariantMap& eventData);
    /// Update the Point Set
    void UpdatePoints();

    /// The Control Points of the Spline.
    Spline spline_;
    /// The Speed of movement along the Spline.
    float speed_;

    /// Amount of time that has elapsed while moving.
    float elapsedTime_;
    /// The fraction of the Spline covered.
    float traveled_;
    /// The length of the Spline.
    float length_;
    /// Whether the Spline has changed.
    bool dirty_;
};
}