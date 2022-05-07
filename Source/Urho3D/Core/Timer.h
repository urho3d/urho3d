// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

#pragma once

#include "../Core/Object.h"

namespace Urho3D
{

/// Low-resolution operating system timer.
class URHO3D_API Timer
{
public:
    /// Construct. Get the starting clock value.
    Timer();

    /// Return elapsed milliseconds and optionally reset.
    unsigned GetMSec(bool reset);
    /// Reset the timer.
    void Reset();

private:
    /// Starting clock value in milliseconds.
    unsigned startTime_{};
};

/// High-resolution operating system timer used in profiling.
class URHO3D_API HiresTimer
{
    friend class Time;

public:
    /// Construct. Get the starting high-resolution clock value.
    HiresTimer();

    /// Return elapsed microseconds and optionally reset.
    long long GetUSec(bool reset);
    /// Reset the timer.
    void Reset();

    /// Return if high-resolution timer is supported.
    static bool IsSupported() { return supported; }

    /// Return high-resolution timer frequency if supported.
    static long long GetFrequency() { return frequency; }

private:
    /// Starting clock value in CPU ticks.
    long long startTime_{};

    /// High-resolution timer support flag.
    static bool supported;
    /// High-resolution timer frequency.
    static long long frequency;
};

/// %Time and frame counter subsystem.
class URHO3D_API Time : public Object
{
    URHO3D_OBJECT(Time, Object);

public:
    /// Construct.
    explicit Time(Context* context);
    /// Destruct. Reset the low-resolution timer period if set.
    ~Time() override;

    /// Begin new frame, with (last) frame duration in seconds and send frame start event.
    void BeginFrame(float timeStep);
    /// End frame. Increment total time and send frame end event.
    void EndFrame();
    /// Set the low-resolution timer period in milliseconds. 0 resets to the default period.
    void SetTimerPeriod(unsigned mSec);

    /// Return frame number, starting from 1 once BeginFrame() is called for the first time.
    /// @property
    unsigned GetFrameNumber() const { return frameNumber_; }

    /// Return current frame timestep as seconds.
    /// @property
    float GetTimeStep() const { return timeStep_; }

    /// Return current low-resolution timer period in milliseconds.
    unsigned GetTimerPeriod() const { return timerPeriod_; }

    /// Return elapsed time from program start as seconds.
    /// @property
    float GetElapsedTime();

    /// Return current frames per second.
    /// @property
    float GetFramesPerSecond() const;

    /// Get system time as milliseconds.
    static unsigned GetSystemTime();
    /// Get system time as seconds since 1.1.1970.
    static unsigned GetTimeSinceEpoch();
    /// Get a date/time stamp as a string.
    static String GetTimeStamp();
    /// Sleep for a number of milliseconds.
    static void Sleep(unsigned mSec);

private:
    /// Elapsed time since program start.
    Timer elapsedTime_;
    /// Frame number.
    unsigned frameNumber_;
    /// Timestep in seconds.
    float timeStep_;
    /// Low-resolution timer period.
    unsigned timerPeriod_;
};

}
