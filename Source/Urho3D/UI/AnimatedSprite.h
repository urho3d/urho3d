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

#include "../UI/Sprite.h"

namespace Urho3D
{

/// Simple looped animation for UI.
class URHO3D_API AnimatedSprite : public Sprite
{
    URHO3D_OBJECT(AnimatedSprite, Sprite);

public:
    /// Construct.
    AnimatedSprite(Context* context);
    /// Register object factory.
    static void RegisterObject(Context* context);
    /// Handle update.
    void HandleUpdate(StringHash eventType, VariantMap& eventData);
    /// Return UI rendering batches.
    virtual void GetBatches(PODVector<UIBatch>& batches, PODVector<float>& vertexData, const IntRect& currentScissor);

    /// Set number of frames.
    void SetNumFrames(unsigned numFrames);
    /// Set animation speed.
    void SetSpeed(float speed);
    /// Set animation time.
    void SetTime(float time);
    // Set max frames in a row.
    void SetColumns(unsigned columns);

    /// Return total number of frames.
    unsigned GetNumFrames() const { return numFrames_; }
    /// Return animation speed.
    float GetSpeed() const { return speed_; }
    /// Return animation time.
    float GetTime() const { return time_; }
    /// Return max frames in a row.
    unsigned GetColumns() const { return columns_; }

protected:
    /// Lead time_ to a range [0, animation duration). 
    void FixupTime();

    float time_;
    float speed_;
    unsigned numFrames_;
    unsigned columns_;
};

}
