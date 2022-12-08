/*
 *  Copyright (c) 2014, Oculus VR, Inc.
 *  All rights reserved.
 *
 *  This source code is licensed under the BSD-style license found in the
 *  RakNet License.txt file in the licenses directory of this source tree. An additional grant 
 *  of patent rights can be found in the RakNet Patents.txt file in the same directory.
 *
 */
 
#ifndef __GET_TIME_OF_DAY_H
#define __GET_TIME_OF_DAY_H

#if defined(_WIN32) && !defined(__GNUC__)  &&!defined(__GCCXML__)
#include < time.h >
struct timezone
{
  int  tz_minuteswest; /* minutes W of Greenwich */
  int  tz_dsttime;     /* type of dst correction */
};

#if defined(WINDOWS_STORE_RT)
struct timeval {
        long    tv_sec;
        long    tv_usec;
};
#endif

int gettimeofday(struct timeval *tv, struct timezone *tz);


#else




#include <sys/time.h>

#include <unistd.h>

// Uncomment this if you need to
/*
// http://www.halcode.com/archives/2008/08/26/retrieving-system-time-gettimeofday/
struct timezone
{
  int tz_minuteswest;
  int tz_dsttime;
};
 
#ifdef	__cplusplus
 
void  GetSystemTimeAsFileTime(FILETIME*);
 
inline int gettimeofday(struct timeval* p, void* tz )
{
	union {
	    long long ns100; // time since 1 Jan 1601 in 100ns units
		FILETIME ft;
	} now;
 
    GetSystemTimeAsFileTime( &(now.ft) );
    p->tv_usec=(long)((now.ns100 / 10LL) % 1000000LL );
    p->tv_sec= (long)((now.ns100-(116444736000000000LL))/10000000LL);
	return 0;
}
 
#else
	int gettimeofday(struct timeval* p, void* tz );
#endif
*/

#endif

#endif
