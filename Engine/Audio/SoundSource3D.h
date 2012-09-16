//
// Urho3D Engine
// Copyright (c) 2008-2012 Lasse Oorni
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

#include "SoundSource.h"

namespace Urho3D
{

class Audio;

/// %Sound source component with three-dimensional position.
class SoundSource3D : public SoundSource
{
    OBJECT(SoundSource3D);
    
public:
    /// Construct.
    SoundSource3D(Context* context);
    /// Register object factory.
    static void RegisterObject(Context* context);
    
    /// Update sound source.
    virtual void Update(float timeStep);
    
    /// Set attenuation parameters.
    void SetDistanceAttenuation(float nearDistance, float farDistance, float rolloffFactor);
    /// Set near distance. Distances closer than this do not have an effect.
    void SetNearDistance(float distance);
    /// Set far distance. Beyond this sound will be completely attenuated.
    void SetFarDistance(float distance);
    /// Set rolloff power factor, defines attenuation function shape.
    void SetRolloffFactor(float factor);
    /// Calculate attenuation and panning based on current position and listener position.
    void CalculateAttenuation();
    
    /// Return near distance.
    float GetNearDistance() const { return nearDistance_; }
    /// Return far distance.
    float GetFarDistance() const { return farDistance_; }
    /// Return rolloff power factor.
    float RollAngleoffFactor() const { return rolloffFactor_; }
    
protected:
    /// Near distance.
    float nearDistance_;
    /// Far distance.
    float farDistance_;
    /// Rolloff power factor.
    float rolloffFactor_;
};

}
