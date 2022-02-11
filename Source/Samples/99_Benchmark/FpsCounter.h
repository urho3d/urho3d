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

#pragma once

class FpsCounter
{
private:
    // Results
    int resultMinFps_;
    int resultMaxFps_;
    int resultFps_;
    int resultNumFrames_; // Number of frames after warm-up
    float resultTime_; // Time after warm-up
    float totalTime_; // Time with warm-up

    // Current FPS updated every half second
    int currentFps_;
    int frameCounter_;
    float timeCounter_;

public:
    void Clear()
    {
        resultMinFps_ = -1;
        resultMaxFps_ = -1;
        resultFps_ = -1;
        resultNumFrames_ = 0;
        resultTime_ = 0.f;
        totalTime_ = 0.f;
        
        currentFps_ = -1;
        frameCounter_ = 0;
        timeCounter_ = 0.f;
    }

    FpsCounter()
    {
        Clear();
    }

    int GetResultMinFps() const { return resultMinFps_; }
    int GetResultMaxFps() const { return resultMaxFps_; }
    int GetResultFps() const { return resultFps_; }
    float GetTotalTime() const { return totalTime_; }

    int GetCurrentFps() const { return currentFps_; }

    void Update(float timeStep);
};
