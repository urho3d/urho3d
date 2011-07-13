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

/** @file W32Clock.cpp
	@brief */

#include <cassert>

#include "kNet/DebugMemoryLeakCheck.h"

#include "kNet/Clock.h"
#include "kNet/NetworkLogging.h"

#define NOMINMAX
#include <windows.h>

namespace kNet
{

Clock impl;

LARGE_INTEGER Clock::ddwTimerFrequency;
tick_t Clock::appStartTime = 0xFFFFFFFF;

void Clock::InitClockData()
{
	if (appStartTime != 0xFFFFFFFF)
		return;

	if (!QueryPerformanceFrequency(&ddwTimerFrequency))
	{
		LOG(LogError, "The system doesn't support high-resolution timers!");
		ddwTimerFrequency.HighPart = (unsigned long)-1;
		ddwTimerFrequency.LowPart = (unsigned long)-1;
	}

	if (ddwTimerFrequency.HighPart > 0)
		LOG(LogError, "Warning: Clock::TicksPerSec will yield invalid timing data!");

	if (appStartTime == 0)
		appStartTime = GetTickCount();

	///\todo Test here that the return values of QueryPerformanceCounter is nondecreasing.
}

Clock::Clock()
{
	InitClockData();
}

void Clock::Sleep(int milliseconds)
{
	::Sleep(milliseconds);
}

int Clock::Year()
{
	SYSTEMTIME s;
	GetSystemTime(&s);
	return s.wYear;
}

int Clock::Month()
{
	SYSTEMTIME s;
	GetSystemTime(&s);
	return s.wMonth;
}

int Clock::Day()
{
	SYSTEMTIME s;
	GetSystemTime(&s);
	return s.wDay;
}

int Clock::Hour()
{
	SYSTEMTIME s;
	GetSystemTime(&s);
	return s.wHour;
}

int Clock::Min()
{
	SYSTEMTIME s;
	GetSystemTime(&s);
	return s.wMinute;
}

int Clock::Sec()
{
	SYSTEMTIME s;
	GetSystemTime(&s);
	return s.wSecond;
}

unsigned long Clock::SystemTime()
{
	return GetTickCount();
}

unsigned long Clock::Time()
{
	return (unsigned long)(GetTickCount() - appStartTime);
}

tick_t Clock::Tick()
{
	LARGE_INTEGER ddwTimer;
	QueryPerformanceCounter(&ddwTimer);
	return ddwTimer.QuadPart;
}

unsigned long Clock::TickU32()
{
	LARGE_INTEGER ddwTimer;
	QueryPerformanceCounter(&ddwTimer);
	return ddwTimer.LowPart;
}

tick_t Clock::TicksPerSec()
{
	return ddwTimerFrequency.QuadPart;
}

} // ~kNet
