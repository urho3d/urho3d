/*
 *  Copyright (c) 2014, Oculus VR, Inc.
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

#if   defined(_WIN32)
#include "slikenet/WindowsIncludes.h" // Sleep







#else
#include <pthread.h>
#include <time.h>
#include <sys/time.h>
pthread_mutex_t fakeMutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t fakeCond = PTHREAD_COND_INITIALIZER;
#endif

#include "slikenet/sleep.h"


#if defined(WINDOWS_PHONE_8) || defined(WINDOWS_STORE_RT)
#include "ThreadEmulation.h"
using namespace ThreadEmulation;
#endif

void RakSleep(unsigned int ms)
{
#ifdef _WIN32
	Sleep(ms);







#else
	//Single thread sleep code thanks to Furquan Shaikh, http://somethingswhichidintknow.blogspot.com/2009/09/sleep-in-pthread.html
	//Modified slightly from the original
	struct timespec timeToWait;
	struct timeval now;
	int rt;

	gettimeofday(&now,NULL);

	long seconds = ms/1000;
	long nanoseconds = (ms - seconds * 1000) * 1000000;
	timeToWait.tv_sec = now.tv_sec + seconds;
	timeToWait.tv_nsec = now.tv_usec*1000 + nanoseconds;
	
	if (timeToWait.tv_nsec >= 1000000000)
	{
	        timeToWait.tv_nsec -= 1000000000;
	        timeToWait.tv_sec++;
	}

	pthread_mutex_lock(&fakeMutex);
	rt = pthread_cond_timedwait(&fakeCond, &fakeMutex, &timeToWait);
	pthread_mutex_unlock(&fakeMutex);
#endif
}
