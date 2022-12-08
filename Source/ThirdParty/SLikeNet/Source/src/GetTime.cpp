/*
 *  Original work: Copyright (c) 2014, Oculus VR, Inc.
 *  All rights reserved.
 *
 *  This source code is licensed under the BSD-style license found in the
 *  RakNet License.txt file in the licenses directory of this source tree. An additional grant 
 *  of patent rights can be found in the RakNet Patents.txt file in the same directory.
 *
 *
 *  Modified work: Copyright (c) 2016-2017, SLikeSoft UG (haftungsbeschränkt)
 *
 *  This source code was modified by SLikeSoft. Modifications are licensed under the MIT-style
 *  license found in the license.txt file in the root directory of this source tree.
 */

/// \file
///


#if defined(_WIN32)
#include "slikenet/WindowsIncludes.h"

 #if !defined(WINDOWS_PHONE_8)
		// To call timeGetTime
		// on Code::Blocks, this needs to be libwinmm.a instead
		#pragma comment(lib, "Winmm.lib")
	#endif

#endif

#include "slikenet/GetTime.h"




#if defined(_WIN32)
//DWORD mProcMask;
//DWORD mSysMask;
//HANDLE mThread;









#else
#include <sys/time.h>
#include <unistd.h>
SLNet::TimeUS initialTime;
#endif

static bool initialized=false;

#if defined(GET_TIME_SPIKE_LIMIT) && GET_TIME_SPIKE_LIMIT>0
#include "slikenet/SimpleMutex.h"
SLNet::TimeUS lastNormalizedReturnedValue=0;
SLNet::TimeUS lastNormalizedInputValue=0;
/// This constraints timer forward jumps to 1 second, and does not let it jump backwards
/// See http://support.microsoft.com/kb/274323 where the timer can sometimes jump forward by hours or days
/// This also has the effect where debugging a sending system won't treat the time spent halted past 1 second as elapsed network time
SLNet::TimeUS NormalizeTime(SLNet::TimeUS timeIn)
{
	SLNet::TimeUS diff, lastNormalizedReturnedValueCopy;
	static SLNet::SimpleMutex mutex;
	
	mutex.Lock();
	if (timeIn>=lastNormalizedInputValue)
	{
		diff = timeIn-lastNormalizedInputValue;
		if (diff > GET_TIME_SPIKE_LIMIT)
			lastNormalizedReturnedValue+=GET_TIME_SPIKE_LIMIT;
		else
			lastNormalizedReturnedValue+=diff;
	}
	else
		lastNormalizedReturnedValue+=GET_TIME_SPIKE_LIMIT;

	lastNormalizedInputValue=timeIn;
	lastNormalizedReturnedValueCopy=lastNormalizedReturnedValue;
	mutex.Unlock();

	return lastNormalizedReturnedValueCopy;
}
#endif // #if defined(GET_TIME_SPIKE_LIMIT) && GET_TIME_SPIKE_LIMIT>0
SLNet::Time SLNet::GetTime( void )
{
	return (SLNet::Time)(GetTimeUS()/1000);
}
SLNet::TimeMS SLNet::GetTimeMS( void )
{
	return (SLNet::TimeMS)(GetTimeUS()/1000);
}
















































#if   defined(_WIN32)
SLNet::TimeUS GetTimeUS_Windows( void )
{
	if ( initialized == false)
	{
		initialized = true;

		// Save the current process
#if !defined(_WIN32_WCE)
//		HANDLE mProc = GetCurrentProcess();

		// Get the current Affinity
#if defined (_M_X64)
//		GetProcessAffinityMask(mProc, (PDWORD_PTR)&mProcMask, (PDWORD_PTR)&mSysMask);
#else
//		GetProcessAffinityMask(mProc, &mProcMask, &mSysMask);
#endif
//		mThread = GetCurrentThread();

#endif // _WIN32_WCE
	}	

	// 9/26/2010 In China running LuDaShi, QueryPerformanceFrequency has to be called every time because CPU clock speeds can be different
	SLNet::TimeUS curTime;
	LARGE_INTEGER PerfVal;
	LARGE_INTEGER yo1;

	QueryPerformanceFrequency( &yo1 );
	QueryPerformanceCounter( &PerfVal );

	__int64 quotient, remainder;
	quotient=((PerfVal.QuadPart) / yo1.QuadPart);
	remainder=((PerfVal.QuadPart) % yo1.QuadPart);
	curTime = (SLNet::TimeUS) quotient*(SLNet::TimeUS)1000000 + (remainder*(SLNet::TimeUS)1000000 / yo1.QuadPart);

#if defined(GET_TIME_SPIKE_LIMIT) && GET_TIME_SPIKE_LIMIT>0
	return NormalizeTime(curTime);
#else
	return curTime;
#endif // #if defined(GET_TIME_SPIKE_LIMIT) && GET_TIME_SPIKE_LIMIT>0
}
#elif defined(__GNUC__)  || defined(__GCCXML__) || defined(__S3E__)
SLNet::TimeUS GetTimeUS_Linux( void )
{
	timeval tp;
	if ( initialized == false)
	{
		gettimeofday( &tp, 0 );
		initialized=true;
		// I do this because otherwise SLNet::Time in milliseconds won't work as it will underflow when dividing by 1000 to do the conversion
		initialTime = ( tp.tv_sec ) * (SLNet::TimeUS) 1000000 + ( tp.tv_usec );
	}

	// GCC
	SLNet::TimeUS curTime;
	gettimeofday( &tp, 0 );

	curTime = ( tp.tv_sec ) * (SLNet::TimeUS) 1000000 + ( tp.tv_usec );

#if defined(GET_TIME_SPIKE_LIMIT) && GET_TIME_SPIKE_LIMIT>0
	return NormalizeTime(curTime - initialTime);
#else
	return curTime - initialTime;
#endif // #if defined(GET_TIME_SPIKE_LIMIT) && GET_TIME_SPIKE_LIMIT>0
}
#endif

SLNet::TimeUS SLNet::GetTimeUS( void )
{






#if   defined(_WIN32)
	return GetTimeUS_Windows();
#else
	return GetTimeUS_Linux();
#endif
}
bool SLNet::GreaterThan(SLNet::Time a, SLNet::Time b)
{
	// a > b?
	const SLNet::Time halfSpan =(SLNet::Time) (((SLNet::Time)(const SLNet::Time)-1)/(SLNet::Time)2);
	return b!=a && b-a>halfSpan;
}
bool SLNet::LessThan(SLNet::Time a, SLNet::Time b)
{
	// a < b?
	const SLNet::Time halfSpan = ((SLNet::Time)(const SLNet::Time)-1)/(SLNet::Time)2;
	return b!=a && b-a<halfSpan;
}
