/*
 *  Copyright (c) 2016, SLikeSoft UG (haftungsbeschränkt)
 *
 *  This source code is licensed under the MIT-style license found in the
 *  license.txt file in the root directory of this source tree.
 *
 *
 *  This file declares adapters for all MS-specific functions used throughout SLikeNet.
 */
#pragma once

#ifdef INET_FUNCTIONS_MISSING
#include <cstdarg>  // for va_start, va_end, va_list
#include <cstdio>   // for FILE
#include <ctime>    // for time_t
#include <stdint.h>
#include "winsock2.h"
#include "ws2tcpip.h"

#define NS_INADDRSZ  4
#define NS_IN6ADDRSZ 16
#define NS_INT16SZ   2

const char *inet_ntop(int af, const void *src, char *dst, socklen_t size);
int inet_pton4(const char *src, char *dst);
int inet_pton6(const char *src, char *dst);
int inet_pton(int af, const char *src, unsigned long *dst);

#endif

#if defined(SPRINTFS_FUNCTION_MISSING) || defined(VSNPRINTFS_FUNCTION_MISSING)

#define _TRUNCATE ((size_t)-1)
typedef int errno_t;
#include <cstdarg>  // for va_start, va_end, va_list
#include <cstdio>   // for FILE
#include <ctime>    // for time_t

#endif

#ifdef VSNPRINTFS_FUNCTION_MISSING
int vsnprintf_s(char *buffer, size_t sizeOfBuffer, size_t count, const char *format, va_list argptr);
#endif

#if defined(__linux__) || defined(__APPLE__) || defined(__FreeBSD__)
template<size_t BufferSize> int vsnprintf_s(char (&buffer)[BufferSize], size_t count, const char *format, va_list argptr)
{
    return vsnprintf_s(buffer, BufferSize, count, format, argptr);
}
#endif

#ifdef SPRINTFS_FUNCTION_MISSING

// MS specific security enhanced functions
errno_t fopen_s(FILE **pfile, const char *filename, const char *mode);
errno_t localtime_s(struct tm* _tm, const time_t *time);
errno_t mbstowcs_s(size_t *pReturnValue, wchar_t *wcstr, size_t sizeInWords, const char *mbstr, size_t count);
int sprintf_s(char *buffer, size_t sizeOfBuffer, const char *format, ...);
errno_t strcat_s(char *strDestination, size_t numberOfElements, const char *strSource);
errno_t strcpy_s(char* strDestination, size_t numberOfElements, const char *strSource);
errno_t strncat_s(char *strDest, size_t numberOfElements, const char *strSource, size_t count);
errno_t strncpy_s(char *strDest, size_t numberOfElements, const char *strSource, size_t count);
errno_t wcscat_s(wchar_t *strDestination, size_t numberOfElements, const wchar_t *strSource);
errno_t wcscpy_s(wchar_t* strDestination, size_t numberOfElements, const wchar_t *strSource);

// corresponding template overloads
template<size_t BufferSize> errno_t mbstowcs_s(size_t *pReturnValue, wchar_t(&wcstr)[BufferSize], const char *mbstr, size_t count)
{
    return mbstowcs_s(pReturnValue, wcstr, BufferSize, mbstr, count);
}

template<size_t BufferSize> int sprintf_s(char (&buffer)[BufferSize], const char* format, ...)
{
    va_list arglist;
    va_start(arglist, format);
    int numCharsWritten = vsnprintf_s(buffer, BufferSize, BufferSize - 1, format, arglist);
    va_end(arglist);

    return numCharsWritten;
}

template<size_t BufferSize> errno_t strcat_s(char (&strDestination)[BufferSize], const char* strSource)
{
    return strcat_s(strDestination, BufferSize, strSource);
}

template<size_t BufferSize> errno_t strcpy_s(char (&strDestination)[BufferSize], const char* strSource)
{
    return strcpy_s(strDestination, BufferSize, strSource);
}

template<size_t BufferSize> errno_t strncat_s(char(&strDest)[BufferSize], const char *strSource, size_t count)
{
    return strncat_s(strDest, BufferSize, strSource, count);
}

template<size_t BufferSize> errno_t strncpy_s(char(&strDest)[BufferSize], const char *strSource, size_t count)
{
    return strncpy_s(strDest, BufferSize, strSource, count);
}

#endif


#ifdef __ANDROID__
/*
 * Copyright (c) 1995, 1999
 *  Berkeley Software Design, Inc.  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * THIS SOFTWARE IS PROVIDED BY Berkeley Software Design, Inc. ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL Berkeley Software Design, Inc. BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 *  BSDI ifaddrs.h,v 2.5 2000/02/23 14:51:59 dab Exp
 */

#ifndef _IFADDRS_H_
#define _IFADDRS_H_

struct ifaddrs {
    struct ifaddrs  *ifa_next;
    char        *ifa_name;
    unsigned int     ifa_flags;
    struct sockaddr *ifa_addr;
    struct sockaddr *ifa_netmask;
    struct sockaddr *ifa_dstaddr;
    void        *ifa_data;
};

/*
 * This may have been defined in <net/if.h>.  Note that if <net/if.h> is
 * to be included it must be included before this header file.
 */
#ifndef ifa_broadaddr
#define ifa_broadaddr   ifa_dstaddr /* broadcast address interface */
#endif

#include <sys/cdefs.h>

__BEGIN_DECLS
extern int getifaddrs(struct ifaddrs **ifap);
extern void freeifaddrs(struct ifaddrs *ifa);
__END_DECLS

#endif

#endif
