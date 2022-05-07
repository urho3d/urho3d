// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

#pragma once

#include "../Scene/Component.h"

namespace Urho3D
{

/// %Network interest management settings component.
class URHO3D_API NetworkPriority : public Component
{
    URHO3D_OBJECT(NetworkPriority, Component);

public:
    /// Construct.
    explicit NetworkPriority(Context* context);
    /// Destruct.
    ~NetworkPriority() override;
    /// Register object factory.
    /// @nobind
    static void RegisterObject(Context* context);

    /// Set base priority. Default 100 (send updates at full frequency).
    /// @property
    void SetBasePriority(float priority);
    /// Set priority reduction distance factor. Default 0 (no effect).
    /// @property
    void SetDistanceFactor(float factor);
    /// Set minimum priority. Default 0 (no updates when far away enough).
    /// @property
    void SetMinPriority(float priority);
    /// Set whether updates to owner should be sent always at full rate. Default true.
    /// @property
    void SetAlwaysUpdateOwner(bool enable);

    /// Return base priority.
    /// @property
    float GetBasePriority() const { return basePriority_; }

    /// Return priority reduction distance factor.
    /// @property
    float GetDistanceFactor() const { return distanceFactor_; }

    /// Return minimum priority.
    /// @property
    float GetMinPriority() const { return minPriority_; }

    /// Return whether updates to owner should be sent always at full rate.
    /// @property
    bool GetAlwaysUpdateOwner() const { return alwaysUpdateOwner_; }

    /// Increment and check priority accumulator. Return true if should update. Called by Connection.
    bool CheckUpdate(float distance, float& accumulator);

private:
    /// Base priority.
    float basePriority_;
    /// Priority reduction distance factor.
    float distanceFactor_;
    /// Minimum priority.
    float minPriority_;
    /// Update owner at full rate flag.
    bool alwaysUpdateOwner_;
};

}
