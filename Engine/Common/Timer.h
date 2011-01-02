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

#ifndef COMMON_TIMER_H
#define COMMON_TIMER_H

//! A low-resolution operating system timer
class Timer
{
public:
    //! Construct. Get the starting clock value
    Timer();
    
    //! Return elapsed milliseconds and optionally reset
    unsigned getMSec(bool reset);
    //! Reset the timer
    void reset();
    
private:
    //! Starting clock value in milliseconds
    unsigned mStartTime;
};

//! A high-resolution operating system timer used in profiling
class HiresTimer
{
public:
    //! Construct. Get the starting high-resolution clock value
    HiresTimer();
    
    //! Return elapsed microseconds and optionally reset
    long long getUSec(bool reset);
    //! Reset the timer
    void reset();
    
private:
    //! Starting clock value in CPU ticks
    long long mStartTime;
};

//! Set the low-resolution timer period in milliseconds. 0 resets to the default period. Reset to default before exiting.
void setTimerPeriod(unsigned period);
//! Return current low-resolution timer period
unsigned getTimerPeriod();
//! Initialize high-resolution timer. Check for support and frequency
void initHiresTimer();
//! Return if high-resolution timer is supported (need to call initHiresTimer() first)
bool isHiresTimerSupported();
//! Return high-resolution timer frequency (need to call initHiresTimer() first)
long long getHiresTimerFrequency();

#endif // COMMON_TIMER_H
