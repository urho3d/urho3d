//
// Copyright (c) 2008-2022 the Urho3D project.
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

#include "FpsCounter.h"

#include <Urho3D/Math/MathDefs.h>

#include <Urho3D/DebugNew.h>

using namespace Urho3D;

// Time without measurement
static constexpr float WARM_UP_TIME = 5.f;

void FpsCounter::Update(float timeStep)
{
    if (timeStep < M_EPSILON)
        return;

    totalTime_ += timeStep;

    if (WARM_UP_TIME != 0.f && totalTime_ <= WARM_UP_TIME)
        return; // Waiting for the next frame

    resultNumFrames_++;
    resultTime_ += timeStep;
    resultFps_ = RoundToInt(resultNumFrames_ / resultTime_);

    frameCounter_++;
    timeCounter_ += timeStep;

    if (timeCounter_ >= 0.5f)
    {
        currentFps_ = RoundToInt(frameCounter_ / timeCounter_);
        frameCounter_ = 0;
        timeCounter_ = 0.f;
    }

    if (resultMinFps_ < 0 || currentFps_ < resultMinFps_)
        resultMinFps_ = currentFps_;

    if (currentFps_ > resultMaxFps_)
        resultMaxFps_ = currentFps_;
}
