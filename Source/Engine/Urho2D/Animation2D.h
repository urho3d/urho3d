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

#include "Resource.h"

namespace Urho3D
{

class Sprite2D;

/// 2D animation.
class URHO3D_API Animation2D : public Resource
{
    OBJECT(Animation2D);

public:
    /// Construct.
    Animation2D(Context* context);
    /// Destruct.
    virtual ~Animation2D();
    /// Register object factory.
    static void RegisterObject(Context* context);

    /// Load resource. Return true if successful.
    virtual bool Load(Deserializer& source);
    /// Save resource. Return true if successful.
    virtual bool Save(Serializer& dest) const;
    
    /// Return total time.
    float GetTotalTime() const;
    /// Return num key frame.
    unsigned GetNumFrames() const;
    /// Return frame by time.
    Sprite2D* GetFrameByTime(float time) const;
    /// Return frame by index.
    Sprite2D* GetFrameByIndex(unsigned index) const;
    
private:
    /// Frame end times.
    PODVector<float> frameEndTimes_;
    /// Frame sprites.
    Vector<SharedPtr<Sprite2D> > frameSprites_;
};

}
