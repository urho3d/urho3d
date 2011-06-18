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
#include "CoreEvents.h"
#include "Timer.h"

#ifndef USE_SDL
#include <Windows.h>
#include <MMSystem.h>
#else
#include <SDL.h>
#endif

#include "DebugNew.h"

bool HiresTimer::supported(false);
long long HiresTimer::frequency(1000);

OBJECTTYPESTATIC(Time);

Time::Time(Context* context) :
    Object(context),
    frameNumber_(0),
    timeStep_(0.0f),
    timeStepMSec_(0),
    totalMSec_(0),
    timerPeriod_(0)
{
    #ifndef USE_SDL
    LARGE_INTEGER frequency;
    if (QueryPerformanceFrequency(&frequency))
    {
        HiresTimer::frequency = frequency.QuadPart;
        HiresTimer::supported = true;
    }
    #else
    SDL_InitSubSystem(SDL_INIT_TIMER);
    HiresTimer::frequency = SDL_GetPerformanceFrequency();
    HiresTimer::supported = true;
    #endif
}

Time::~Time()
{
    SetTimerPeriod(0);
    #ifdef USE_SDL
    SDL_QuitSubSystem(SDL_INIT_TIMER);
    #endif
}

void Time::BeginFrame(unsigned mSec)
{
    ++frameNumber_;
    if (!frameNumber_)
        ++frameNumber_;
    
    timeStep_ = (float)mSec / 1000.0f;
    timeStepMSec_ = mSec;
    
    {
        // Frame begin event
        using namespace BeginFrame;
        
        VariantMap eventData;
        eventData[P_FRAMENUMBER] = frameNumber_;
        eventData[P_TIMESTEP] = timeStep_;
        SendEvent(E_BEGINFRAME, eventData);
    }
    
    {
        // Logic update event
        using namespace Update;
        
        VariantMap eventData;
        eventData[P_TIMESTEP] = timeStep_;
        SendEvent(E_UPDATE, eventData);
        
        // Logic post-update event
        SendEvent(E_POSTUPDATE, eventData);
        
        // Rendering update event
        SendEvent(E_RENDERUPDATE, eventData);
        
        // Post-render update event
        SendEvent(E_POSTRENDERUPDATE, eventData);
    }
}

void Time::EndFrame()
{
    totalMSec_ += timeStepMSec_;
    
    // Frame end event
    SendEvent(E_ENDFRAME);
}

void Time::SetTimerPeriod(unsigned mSec)
{
    #ifndef USE_SDL
    if (timerPeriod_ > 0)
        timeEndPeriod(timerPeriod_);
    
    timerPeriod_ = mSec;
    
    if (timerPeriod_ > 0)
        timeBeginPeriod(timerPeriod_);
    #endif
}

Timer::Timer()
{
    Reset();
}

unsigned Timer::GetMSec(bool reset)
{
    #ifndef USE_SDL
    unsigned currentTime = timeGetTime();
    #else
    unsigned currentTime = SDL_GetTicks();
    #endif
    
    unsigned elapsedTime = currentTime - startTime_;
    if (reset)
        startTime_ = currentTime;
    
    return elapsedTime;
}

void Timer::Reset()
{
    #ifndef USE_SDL
    startTime_ = timeGetTime();
    #else
    startTime_ = SDL_GetTicks();
    #endif
}

HiresTimer::HiresTimer()
{
    Reset();
}

long long HiresTimer::GetUSec(bool reset)
{
    long long currentTime;
    
    #ifndef USE_SDL
    if (supported)
    {
        LARGE_INTEGER counter;
        QueryPerformanceCounter(&counter);
        currentTime = counter.QuadPart;
    }
    else
        currentTime = timeGetTime();
    #else
    currentTime = SDL_GetPerformanceCounter();
    #endif
    
    long long elapsedTime = currentTime - startTime_;
    
    // Correct for possible weirdness with changing internal frequency
    if (elapsedTime < 0)
        elapsedTime = 0;
    
    if (reset)
        startTime_ = currentTime;
    
    return (elapsedTime * 1000000LL) / frequency;
}

void HiresTimer::Reset()
{
    #ifndef USE_SDL
    if (supported)
    {
        LARGE_INTEGER counter;
        QueryPerformanceCounter(&counter);
        startTime_ = counter.QuadPart;
    }
    else
        startTime_ = timeGetTime();
    #else
    startTime_ = SDL_GetPerformanceCounter();
    #endif
}

