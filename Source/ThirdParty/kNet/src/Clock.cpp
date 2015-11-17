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

/** @file Clock.cpp
	@brief */

// Modified by Lasse Oorni for Urho3D

// Urho3D: ensure that kNetBuildConfig.h is included for WinXP compatibility
#include "kNetBuildConfig.h"

#if defined(__unix__) || defined(__native_client__) || defined(__EMSCRIPTEN__) || defined(ANDROID) || defined(__APPLE__) || defined (__CYGWIN__)
#include <time.h>
#include <errno.h>
#include <string.h>
#include <sys/time.h>
#endif

#ifdef _WIN32
#define NOMINMAX
#include <windows.h>
#endif

#ifdef __EMSCRIPTEN__
#include <emscripten/emscripten.h>
#endif

#include "kNet/Clock.h"
#include "kNet/NetworkLogging.h"

namespace kNet
{

#ifdef _WIN32
LARGE_INTEGER Clock::ddwTimerFrequency;
#endif

tick_t Clock::appStartTime = 0;

Clock impl;

void Clock::InitClockData()
{
	if (appStartTime == 0)
		appStartTime = Tick();

#ifdef _WIN32
	if (!QueryPerformanceFrequency(&ddwTimerFrequency))
	{
		KNET_LOG(LogError, "The system doesn't support high-resolution timers!");
		ddwTimerFrequency.HighPart = (unsigned long)-1;
		ddwTimerFrequency.LowPart = (unsigned long)-1;
	}

	if (ddwTimerFrequency.HighPart > 0)
		KNET_LOG(LogError, "Warning: Clock::TicksPerSec will yield invalid timing data!");

	if (appStartTime == 0)
	{
#if WINVER >= 0x0600 && !defined(KNET_ENABLE_WINXP_SUPPORT)
		appStartTime = (tick_t)GetTickCount64();
#else
		appStartTime = (tick_t)GetTickCount();
#endif
	}

	///\todo Test here that the return values of QueryPerformanceCounter is nondecreasing.
#endif
}

Clock::Clock()
{
	InitClockData();
}

void Clock::Sleep(int milliseconds)
{
#ifdef WIN8RT
#pragma WARNING(Clock::Sleep has not been implemented!)
#elif defined(_WIN32)
	::Sleep(milliseconds);
#elif !defined(__native_client__) && !defined(__EMSCRIPTEN__) && !defined(__APPLE__)
	// http://linux.die.net/man/2/nanosleep
	timespec ts;
	ts.tv_sec = milliseconds / 1000;
	ts.tv_nsec = (milliseconds - ts.tv_sec * 1000) * 1000 * 1000;
	int ret = nanosleep(&ts, NULL);
	if (ret == -1)
		KNET_LOG(LogError, "nanosleep returned -1! Reason: %s(%d).", strerror(errno), (int)errno);
#else
#warning Clock::Sleep has not been implemented!
#endif
}

int Clock::Year()
{
#ifdef _WIN32
	SYSTEMTIME s;
	GetSystemTime(&s);
	return s.wYear;
#else
	///\todo.
	return 0;
#endif
}

int Clock::Month()
{
#ifdef _WIN32
	SYSTEMTIME s;
	GetSystemTime(&s);
	return s.wMonth;
#else
	///\todo.
	return 0;
#endif
}

int Clock::Day()
{
#ifdef _WIN32
	SYSTEMTIME s;
	GetSystemTime(&s);
	return s.wDay;
#else
	///\todo.
	return 0;
#endif
}

int Clock::Hour()
{
#ifdef _WIN32
	SYSTEMTIME s;
	GetSystemTime(&s);
	return s.wHour;
#else
	///\todo.
	return 0;
#endif
}

int Clock::Min()
{
#ifdef _WIN32
	SYSTEMTIME s;
	GetSystemTime(&s);
	return s.wMinute;
#else
	///\todo.
	return 0;
#endif
}

int Clock::Sec()
{
#ifdef _WIN32
	SYSTEMTIME s;
	GetSystemTime(&s);
	return s.wSecond;
#else
	///\todo.
	return 0;
#endif
}

unsigned long Clock::SystemTime()
{
#ifdef _WIN32
#if WINVER >= 0x0600 && !defined(KNET_ENABLE_WINXP_SUPPORT)
	return (unsigned long)GetTickCount64();
#else
	return (unsigned long)GetTickCount();
#endif
#else
	return TickU32();
#endif
}
/*
tick_t Clock::ApplicationStartupTick()
{
	return appStartTime;
}
*/
unsigned long Clock::Time()
{
	return (unsigned long)(Tick() - appStartTime);
}

tick_t Clock::Tick()
{
#if defined(ANDROID)
	struct timespec res;
	clock_gettime(CLOCK_REALTIME, &res);
	return 1000000000ULL*res.tv_sec + (tick_t)res.tv_nsec;
#elif defined(__EMSCRIPTEN__)
	// emscripten_get_now() returns a wallclock time as a float in milliseconds (1e-3).
	// scale it to microseconds (1e-6) and return as a tick.
	return (tick_t)(((double)emscripten_get_now()) * 1e3);
//	return (tick_t)clock();
#elif defined(_WIN32)
	LARGE_INTEGER ddwTimer;
	QueryPerformanceCounter(&ddwTimer);
	return ddwTimer.QuadPart;
#elif defined(_POSIX_MONOTONIC_CLOCK)
	timespec t;
	clock_gettime(CLOCK_MONOTONIC, &t);
	return (tick_t)t.tv_sec * 1000 * 1000 * 1000 + (tick_t)t.tv_nsec;
#elif defined(_POSIX_C_SOURCE) || defined(__APPLE__)
	timeval t;
	gettimeofday(&t, NULL);
	return (tick_t)t.tv_sec * 1000 * 1000 + (tick_t)t.tv_usec;
#else
	return (tick_t)clock();
#endif
}

unsigned long Clock::TickU32()
{
#ifdef _WIN32
	LARGE_INTEGER ddwTimer;
	QueryPerformanceCounter(&ddwTimer);
	return ddwTimer.LowPart;
#else
	return (unsigned long)Tick();
#endif
}

tick_t Clock::TicksPerSec()
{
#if defined(ANDROID)
	return 1000000000ULL; // 1e9 == nanoseconds.
#elif defined(__EMSCRIPTEN__)
	return 1000000ULL; // 1e6 == microseconds.
//	return CLOCKS_PER_SEC;
#elif defined(_WIN32)
	return ddwTimerFrequency.QuadPart;
#elif defined(_POSIX_MONOTONIC_CLOCK)
	return 1000 * 1000 * 1000;
#elif defined(_POSIX_C_SOURCE) || defined(__APPLE__)
	return 1000 * 1000;
#else
	return CLOCKS_PER_SEC;
#endif
}

} // ~kNet
