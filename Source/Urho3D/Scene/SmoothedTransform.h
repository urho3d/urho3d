// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

/// \file

#pragma once

#include "../Scene/Component.h"

namespace Urho3D
{

enum SmoothingType : unsigned
{
    /// No ongoing smoothing.
    SMOOTH_NONE = 0,
    /// Ongoing position smoothing.
    SMOOTH_POSITION = 1,
    /// Ongoing rotation smoothing.
    SMOOTH_ROTATION = 2,
};
URHO3D_FLAGSET(SmoothingType, SmoothingTypeFlags);

/// Transform smoothing component for network updates.
class URHO3D_API SmoothedTransform : public Component
{
    URHO3D_OBJECT(SmoothedTransform, Component);

public:
    /// Construct.
    explicit SmoothedTransform(Context* context);
    /// Destruct.
    ~SmoothedTransform() override;
    /// Register object factory.
    /// @nobind
    static void RegisterObject(Context* context);

    /// Update smoothing.
    void Update(float constant, float squaredSnapThreshold);
    /// Set target position in parent space.
    /// @property
    void SetTargetPosition(const Vector3& position);
    /// Set target rotation in parent space.
    /// @property
    void SetTargetRotation(const Quaternion& rotation);
    /// Set target position in world space.
    /// @property
    void SetTargetWorldPosition(const Vector3& position);
    /// Set target rotation in world space.
    /// @property
    void SetTargetWorldRotation(const Quaternion& rotation);

    /// Return target position in parent space.
    /// @property
    const Vector3& GetTargetPosition() const { return targetPosition_; }

    /// Return target rotation in parent space.
    /// @property
    const Quaternion& GetTargetRotation() const { return targetRotation_; }

    /// Return target position in world space.
    /// @property
    Vector3 GetTargetWorldPosition() const;
    /// Return target rotation in world space.
    /// @property
    Quaternion GetTargetWorldRotation() const;

    /// Return whether smoothing is in progress.
    /// @property
    bool IsInProgress() const { return smoothingMask_ != SMOOTH_NONE; }

protected:
    /// Handle scene node being assigned at creation.
    void OnNodeSet(Node* node) override;

private:
    /// Handle smoothing update event.
    void HandleUpdateSmoothing(StringHash eventType, VariantMap& eventData);

    /// Target position.
    Vector3 targetPosition_;
    /// Target rotation.
    Quaternion targetRotation_;
    /// Active smoothing operations bitmask.
    SmoothingTypeFlags smoothingMask_;
    /// Subscribed to smoothing update event flag.
    bool subscribed_;
};

}
