//
// Urho3D Engine
// Copyright (c) 2008-2012 Lasse Öörni
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

/// No ongoing smoothing.
static const unsigned SMOOTH_NONE = 0;
/// Ongoing position smoothing.
static const unsigned SMOOTH_POSITION = 1;
/// Ongoing rotation smoothing.
static const unsigned SMOOTH_ROTATION = 2;

/// Transform smoothing component for network updates.
class SmoothedTransform : public Component
{
    OBJECT(SmoothedTransform);
    
public:
    /// Construct.
    SmoothedTransform(Context* context);
    /// Destruct.
    ~SmoothedTransform();
    /// Register object factory.
    static void RegisterObject(Context* context);
    
    /// %Set target local space position.
    void SetTargetPosition(const Vector3& position);
    /// %Set target local space rotation.
    void SetTargetRotation(const Quaternion& rotation);
    /// %Set smoothing constant.
    void SetSmoothingConstant(float constant);
    /// %Set smoothing position snap threshold.
    void SetSnapThreshold(float threshold);
    /// Update smoothing.
    void Update(float timeStep);
    
    /// Return target position.
    const Vector3& GetTargetPosition() const { return targetPosition_; }
    /// Return target rotation.
    const Quaternion& GetTargetRotation() const { return targetRotation_; }
    /// Return smoothing constant.
    float GetSmoothingConstant() const { return smoothingConstant_; }
    /// Return smoothing position snap threshold.
    float GetSnapThreshold() const { return snapThreshold_; }
    /// Return whether smoothing is in progress.
    bool IsActive() const { return smoothingMask_ != 0; }
    
protected:
    /// Handle scene node being assigned at creation.
    virtual void OnNodeSet(Node* node);
    
private:
    /// Target position.
    Vector3 targetPosition_;
    /// Target rotation.
    Quaternion targetRotation_;
    /// Smoothing constant.
    float smoothingConstant_;
    /// Position snap threshold.
    float snapThreshold_;
    /// Active smoothing operations bitmask.
    unsigned char smoothingMask_;
};
