/*
 *  Original work: Copyright (c) 2014, Oculus VR, Inc.
 *  All rights reserved.
 *
 *  This source code is licensed under the BSD-style license found in the
 *  RakNet License.txt file in the licenses directory of this source tree. An additional grant 
 *  of patent rights can be found in the RakNet Patents.txt file in the same directory.
 *
 *
 *  Modified work: Copyright (c) 2017, SLikeSoft UG (haftungsbeschränkt)
 *
 *  This source code was modified by SLikeSoft. Modifications are licensed under the MIT-style
 *  license found in the license.txt file in the root directory of this source tree.
 */

#include "slikenet/thread.h"
#include "slikenet/assert.h"
#include "slikenet/defines.h"
#include "slikenet/sleep.h"
#include "slikenet/memoryoverride.h"

using namespace SLNet;




#if   defined(_WIN32)
	#include "slikenet/WindowsIncludes.h"
	#include <stdio.h>
	#if !defined(_WIN32_WCE)
		#include <process.h>
	#endif




#else
#include <pthread.h>
#endif

#if defined(_WIN32_WCE) || defined(WINDOWS_PHONE_8) || defined(WINDOWS_STORE_RT)
int RakThread::Create( LPTHREAD_START_ROUTINE start_address, void *arglist, int priority)
#elif defined(_WIN32)
int RakThread::Create( unsigned __stdcall start_address( void* ), void *arglist, int priority)



#else
int RakThread::Create( void* start_address( void* ), void *arglist, int priority)
#endif
{
#ifdef _WIN32
	HANDLE threadHandle;
	unsigned threadID = 0;


#if   defined(WINDOWS_PHONE_8) || defined(WINDOWS_STORE_RT)
	threadHandle = CreateThread(NULL,0,start_address,arglist,CREATE_SUSPENDED, 0);
#elif defined _WIN32_WCE
	threadHandle = CreateThread(NULL,MAX_ALLOCA_STACK_ALLOCATION*2,start_address,arglist,0,(DWORD*)&threadID);
#else
	threadHandle = (HANDLE) _beginthreadex( NULL, MAX_ALLOCA_STACK_ALLOCATION*2, start_address, arglist, 0, &threadID );
#endif
	
	SetThreadPriority(threadHandle, priority);

#if defined(WINDOWS_PHONE_8) || defined(WINDOWS_STORE_RT)
	ResumeThread(threadHandle);
#endif

	if (threadHandle==0)
	{
		return 1;
	}
	else
	{
		CloseHandle( threadHandle );
		return 0;
	}







































#else
	pthread_t threadHandle;
	// Create thread linux
	pthread_attr_t attr;
	sched_param param;
	param.sched_priority=priority;
	pthread_attr_init( &attr );
	pthread_attr_setschedparam(&attr, &param);





	pthread_attr_setstacksize(&attr, MAX_ALLOCA_STACK_ALLOCATION*2);

	pthread_attr_setdetachstate( &attr, PTHREAD_CREATE_DETACHED );
	int res = pthread_create( &threadHandle, &attr, start_address, arglist );
	RakAssert(res==0 && "pthread_create in RakThread.cpp failed.")
	return res;
#endif
}












































