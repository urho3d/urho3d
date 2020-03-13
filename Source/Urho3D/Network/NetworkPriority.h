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
    static void RegisterObject(Context* context);

    /// Set base priority. Default 100 (send updates at full frequency).
    void SetBasePriority(float priority);
    /// Set priority reduction distance factor. Default 0 (no effect).
    void SetDistanceFactor(float factor);
    /// Set minimum priority. Default 0 (no updates when far away enough).
    void SetMinPriority(float priority);
    /// Set whether updates to owner should be sent always at full rate. Default true.
    void SetAlwaysUpdateOwner(bool enable);

    /// Return base priority.
    float GetBasePriority() const { return basePriority_; }

    /// Return priority reduction distance factor.
    float GetDistanceFactor() const { return distanceFactor_; }

    /// Return minimum priority.
    float GetMinPriority() const { return minPriority_; }

    /// Return whether updates to owner should be sent always at full rate.
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
