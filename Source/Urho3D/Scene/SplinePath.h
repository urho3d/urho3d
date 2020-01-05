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

#include "../Container/Ptr.h"
#include "../Core/Variant.h"
#include "../Container/Vector.h"
#include "../Core/Spline.h"
#include "../Graphics/DebugRenderer.h"
#include "../Math/MathDefs.h"
#include "../Math/Vector3.h"
#include "../Scene/Component.h"
#include "../Scene/Node.h"

namespace Urho3D
{

/// Spline for creating smooth movement based on Speed along a set of Control Points modified by the Interpolation Mode.
class URHO3D_API SplinePath : public Component
{
    URHO3D_OBJECT(SplinePath, Component)

public:
    /// Construct an Empty SplinePath.
    explicit SplinePath(Context* context);

    /// Destructor.
    ~SplinePath() override = default;
    /// Register object factory.
    static void RegisterObject(Context* context);

    /// Apply Attributes to the SplinePath.
    void ApplyAttributes() override;
    /// Draw the Debug Geometry.
    void DrawDebugGeometry(DebugRenderer* debug, bool depthTest) override;

    /// Add a Node to the SplinePath as a Control Point.
    void AddControlPoint(Node* point, unsigned index = M_MAX_UNSIGNED);
    /// Remove a Node Control Point from the SplinePath.
    void RemoveControlPoint(Node* point);
    /// Clear the Control Points from the SplinePath.
    void ClearControlPoints();

    /// Set the Interpolation Mode.
    void SetInterpolationMode(InterpolationMode interpolationMode);

    /// Set the movement Speed.
    void SetSpeed(float speed) { speed_ = speed; }

    /// Set the controlled Node's position on the SplinePath.
    void SetPosition(float factor);
    /// Set the Node to be moved along the SplinePath.
    void SetControlledNode(Node* controlled);

    /// Get the Interpolation Mode.
    InterpolationMode GetInterpolationMode() const { return spline_.GetInterpolationMode(); }

    /// Get the movement Speed.
    float GetSpeed() const { return speed_; }

    /// Get the length of SplinePath;
    float GetLength() const { return length_; }

    /// Get the parent Node's last position on the spline.
    Vector3 GetPosition() const { return GetPoint(traveled_); }

    /// Get the controlled Node.
    Node* GetControlledNode() const { return controlledNode_; }

    /// Get a point on the SplinePath from 0.f to 1.f where 0 is the start and 1 is the end.
    Vector3 GetPoint(float factor) const;

    /// Move the controlled Node to the next position along the SplinePath based off the Speed value.
    void Move(float timeStep);
    /// Reset movement along the path.
    void Reset();

    /// Returns whether the movement along the SplinePath is complete.
    bool IsFinished() const { return traveled_ >= 1.0f; }

    /// Set Control Point Node IDs attribute.
    void SetControlPointIdsAttr(const VariantVector& value);

    /// Return Control Point Node IDs attribute.
    const VariantVector& GetControlPointIdsAttr() const { return controlPointIdsAttr_; }

    /// Set Controlled Node ID attribute.
    void SetControlledIdAttr(unsigned value);

    /// Get Controlled Node ID attribute.
    unsigned GetControlledIdAttr() const { return controlledIdAttr_; }

protected:
    /// Listener to manage Control Point movement.
    void OnMarkedDirty(Node* point) override;
    /// Listener to manage Control Point enabling.
    void OnNodeSetEnabled(Node* point) override;

private:
    /// Update the Node IDs of the Control Points.
    void UpdateNodeIds();
    /// Calculate the length of the SplinePath. Used for movement calculations.
    void CalculateLength();

    /// The Control Points of the Spline.
    Spline spline_;
    /// The Speed of movement along the Spline.
    float speed_;
    /// Amount of time that has elapsed while moving.
    float elapsedTime_;
    /// The fraction of the SplinePath covered.
    float traveled_;
    /// The length of the SplinePath.
    float length_;
    /// Whether the Control Point IDs are dirty.
    bool dirty_;
    /// Node to be moved along the SplinePath.
    WeakPtr<Node> controlledNode_;
    /// Control Points for the SplinePath.
    Vector<WeakPtr<Node> > controlPoints_;
    /// Control Point ID's for the SplinePath.
    mutable VariantVector controlPointIdsAttr_;
    /// Controlled ID for the SplinePath.
    mutable unsigned controlledIdAttr_;
};
}
