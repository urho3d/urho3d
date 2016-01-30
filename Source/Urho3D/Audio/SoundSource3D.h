//
// Copyright (c) 2008-2016 the Urho3D project.
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

#include "../Audio/SoundSource.h"

namespace Urho3D
{

class Audio;

/// %Sound source component with three-dimensional position.
class URHO3D_API SoundSource3D : public SoundSource
{
    URHO3D_OBJECT(SoundSource3D, SoundSource);

public:
    /// Construct.
    SoundSource3D(Context* context);
    /// Register object factory.
    static void RegisterObject(Context* context);

    /// Visualize the component as debug geometry.
    virtual void DrawDebugGeometry(DebugRenderer* debug, bool depthTest);
    /// Update sound source.
    virtual void Update(float timeStep);

    /// Set attenuation parameters.
    void SetDistanceAttenuation(float nearDistance, float farDistance, float rolloffFactor);
    /// Set angle attenuation parameters.
    void SetAngleAttenuation(float innerAngle, float outerAngle);
    /// Set near distance. Inside this range sound will not be attenuated.
    void SetNearDistance(float distance);
    /// Set far distance. Outside this range sound will be completely attenuated.
    void SetFarDistance(float distance);
    /// Set inner angle in degrees. Inside this angle sound will not be attenuated.By default 360, meaning direction never has an effect.
    void SetInnerAngle(float angle);
    /// Set outer angle in degrees. Outside this angle sound will be completely attenuated. By default 360, meaning direction never has an effect.
    void SetOuterAngle(float angle);
    /// Set rolloff power factor, defines attenuation function shape.
    void SetRolloffFactor(float factor);
    /// Calculate attenuation and panning based on current position and listener position.
    void CalculateAttenuation();

    /// Return near distance.
    float GetNearDistance() const { return nearDistance_; }

    /// Return far distance.
    float GetFarDistance() const { return farDistance_; }

    /// Return inner angle in degrees.
    float GetInnerAngle() const { return innerAngle_; }

    /// Return outer angle in degrees.
    float GetOuterAngle() const { return outerAngle_; }

    /// Return rolloff power factor.
    float RollAngleoffFactor() const { return rolloffFactor_; }

protected:
    /// Near distance.
    float nearDistance_;
    /// Far distance.
    float farDistance_;
    /// Inner angle for directional attenuation.
    float innerAngle_;
    /// Outer angle for directional attenuation.
    float outerAngle_;
    /// Rolloff power factor.
    float rolloffFactor_;
};

}
