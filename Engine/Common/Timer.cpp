//
// Urho3D Engine
// Copyright (c) 2008-2011 Lasse Öörni
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

#include "Precompiled.h"
#include "Timer.h"

#include <windows.h>
#include <mmsystem.h>

#include "DebugNew.h"

unsigned timerPeriod = 0;
bool hiresTimerSupported = false;
long long hiresTimerFrequency = 1000;

Timer::Timer()
{
    mStartTime = timeGetTime();
}

unsigned Timer::getMSec(bool reset)
{
    unsigned currentTime = timeGetTime();
    unsigned elapsedTime = currentTime - mStartTime;
    if (reset)
        mStartTime = currentTime;
    
    return elapsedTime;
}

void Timer::reset()
{
    mStartTime = timeGetTime();
}

HiresTimer::HiresTimer()
{
    if (hiresTimerSupported)
    {
        LARGE_INTEGER counter;
        QueryPerformanceCounter(&counter);
        mStartTime = counter.QuadPart;
    }
    else
        mStartTime = timeGetTime();
}

long long HiresTimer::getUSec(bool reset)
{
    long long currentTime;
    
    if (hiresTimerSupported)
    {
        LARGE_INTEGER counter;
        QueryPerformanceCounter(&counter);
        currentTime = counter.QuadPart;
    }
    else
        currentTime = timeGetTime();
    
    long long elapsedTime = currentTime - mStartTime;
    
    // Correct for possible weirdness with changing internal frequency
    if (elapsedTime < 0)
        elapsedTime = 0;
    
    if (reset)
        mStartTime = currentTime;
    
    return (elapsedTime * 1000000LL) / hiresTimerFrequency;
}

void HiresTimer::reset()
{
    if (hiresTimerSupported)
    {
        LARGE_INTEGER counter;
        QueryPerformanceCounter(&counter);
        mStartTime = counter.QuadPart;
    }
    else
        mStartTime = timeGetTime();
}

void setTimerPeriod(unsigned period)
{
    if (timerPeriod > 0)
        timeEndPeriod(timerPeriod);
    
    timerPeriod = period;
    
    if (timerPeriod > 0)
        timeBeginPeriod(timerPeriod);
}

unsigned getTimerPeriod()
{
    return timerPeriod;
}

void initHiresTimer()
{
    LARGE_INTEGER frequency;
    if (QueryPerformanceFrequency(&frequency))
    {
        hiresTimerFrequency = frequency.QuadPart;
        hiresTimerSupported = true;
    }
}

bool isHiresTimerSupported()
{
    return hiresTimerSupported;
}

long long getHiresTimerFrequency()
{
    return hiresTimerFrequency;
}
