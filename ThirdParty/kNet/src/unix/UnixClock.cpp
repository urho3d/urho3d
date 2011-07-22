/* Copyright 2010 Jukka Jylänki

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License. */

/** @file UnixClock.cpp
	@brief */

#include <cassert>

#include <time.h>
#include <errno.h>
#include <string.h>
#include <sys/time.h>

#include "kNet/Clock.h"
#include "kNet/NetworkLogging.h"

namespace kNet
{

tick_t Clock::appStartTime = 0;

Clock impl;

void Clock::InitClockData()
{
	if (appStartTime == 0)
		appStartTime = Tick();
}

Clock::Clock()
{
	InitClockData();
}

void Clock::Sleep(int milliseconds)
{
	// http://linux.die.net/man/2/nanosleep
	timespec ts;
	ts.tv_sec = milliseconds / 1000;
	ts.tv_nsec = (milliseconds - ts.tv_sec * 1000) * 1000 * 1000;
	int ret = nanosleep(&ts, NULL);
	if (ret == -1)
		LOG(LogError, "nanosleep returned -1! Reason: %s(%d).", strerror(errno), (int)errno);
}

int Clock::Year()
{
	///\todo.
	return 0;
}

int Clock::Month()
{
	///\todo.
	return 0;
}

int Clock::Day()
{
	///\todo.
	return 0;
}

int Clock::Hour()
{
	///\todo.
	return 0;
}

int Clock::Min()
{
	///\todo.
	return 0;
}

int Clock::Sec()
{
	///\todo.
	return 0;
}

unsigned long Clock::SystemTime()
{
	return TickU32();
}

unsigned long Clock::Time()
{
	return (unsigned long)(Tick() - appStartTime);
}

tick_t Clock::Tick()
{
#ifdef _POSIX_MONOTONIC_CLOCK
	timespec t;
	clock_gettime(CLOCK_MONOTONIC, &t);
    return (tick_t)t.tv_sec * 1000 * 1000 * 1000 + (tick_t)t.tv_nsec;
//_POSIX_C_SOURCE is not defined on OSX
#elif defined(_POSIX_C_SOURCE) || defined(__APPLE__)
	timeval t;
	gettimeofday(&t, NULL);
	return (tick_t)t.tv_sec * 1000 * 1000 + (tick_t)t.tv_usec;
#else
	return (tick_t)time(NULL);
#endif
}

unsigned long Clock::TickU32()
{
	return (unsigned long)Tick();
}

tick_t Clock::TicksPerSec()
{
#ifdef _POSIX_MONOTONIC_CLOCK
    return 1000 * 1000 * 1000;
//_POSIX_C_SOURCE is not defined on OSX
#elif defined(_POSIX_C_SOURCE) || defined(__APPLE__)
    return 1000 * 1000;
#else
    return 1;
#endif
}

} // ~kNet
