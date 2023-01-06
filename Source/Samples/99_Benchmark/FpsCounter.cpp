// Copyright (c) 2008-2023 the Urho3D project
// License: MIT

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
