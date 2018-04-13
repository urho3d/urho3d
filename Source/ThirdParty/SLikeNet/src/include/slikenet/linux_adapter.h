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

#ifdef __MINGW32__
#include "winsock2.h"
#include "ws2tcpip.h"
#endif

#if defined(__linux__) || defined(__MINGW32__)
#define _TRUNCATE ((size_t)-1)
typedef int errno_t;

#include <cstdarg>	// for va_start, va_end, va_list
#include <cstdio>	// for FILE
#include <ctime>	// for time_t
#include <stdint.h>

#ifdef __MINGW32__
#define NS_INADDRSZ  4
#define NS_IN6ADDRSZ 16
#define NS_INT16SZ   2
#endif

// MS specific security enhanced functions
errno_t fopen_s(FILE **pfile, const char *filename, const char *mode);
errno_t localtime_s(struct tm* _tm, const time_t *time);
errno_t mbstowcs_s(size_t *pReturnValue, wchar_t *wcstr, size_t sizeInWords, const char *mbstr, size_t count);
int sprintf_s(char *buffer, size_t sizeOfBuffer, const char *format, ...);
errno_t strcat_s(char *strDestination, size_t numberOfElements, const char *strSource);
errno_t strcpy_s(char* strDestination, size_t numberOfElements, const char *strSource);
errno_t strncat_s(char *strDest, size_t numberOfElements, const char *strSource, size_t count);
errno_t strncpy_s(char *strDest, size_t numberOfElements, const char *strSource, size_t count);
int vsnprintf_s(char *buffer, size_t sizeOfBuffer, size_t count, const char *format, va_list argptr);
errno_t wcscat_s(wchar_t *strDestination, size_t numberOfElements, const wchar_t *strSource);
errno_t wcscpy_s(wchar_t* strDestination, size_t numberOfElements, const wchar_t *strSource);

#ifdef __MINGW32__
const char *inet_ntop(int af, const void *src, char *dst, socklen_t size)
{
  struct sockaddr_storage ss;
  unsigned long s = size;

  ZeroMemory(&ss, sizeof(ss));
  ss.ss_family = af;

  switch(af) {
    case AF_INET:
      ((struct sockaddr_in *)&ss)->sin_addr = *(struct in_addr *)src;
      break;
    case AF_INET6:
      ((struct sockaddr_in6 *)&ss)->sin6_addr = *(struct in6_addr *)src;
      break;
    default:
      return NULL;
  }
  /* cannot direclty use &size because of strict aliasing rules */
  return (WSAAddressToString((struct sockaddr *)&ss, sizeof(ss), NULL, dst, &s) == 0)?
          dst : NULL;
}

int inet_pton4(const char *src, char *dst)
{
    uint8_t tmp[NS_INADDRSZ], *tp;

    int saw_digit = 0;
    int octets = 0;
    *(tp = tmp) = 0;

    int ch;
    while ((ch = *src++) != '\0')
    {
        if (ch >= '0' && ch <= '9')
        {
            uint32_t n = *tp * 10 + (ch - '0');

            if (saw_digit && *tp == 0)
                return 0;

            if (n > 255)
                return 0;

            *tp = n;
            if (!saw_digit)
            {
                if (++octets > 4)
                    return 0;
                saw_digit = 1;
            }
        }
        else if (ch == '.' && saw_digit)
        {
            if (octets == 4)
                return 0;
            *++tp = 0;
            saw_digit = 0;
        }
        else
            return 0;
    }
    if (octets < 4)
        return 0;

    memcpy(dst, tmp, NS_INADDRSZ);

    return 1;
}

int inet_pton6(const char *src, char *dst)
{
    static const char xdigits[] = "0123456789abcdef";
    uint8_t tmp[NS_IN6ADDRSZ];

    uint8_t *tp = (uint8_t*) memset(tmp, '\0', NS_IN6ADDRSZ);
    uint8_t *endp = tp + NS_IN6ADDRSZ;
    uint8_t *colonp = NULL;

    /* Leading :: requires some special handling. */
    if (*src == ':')
    {
        if (*++src != ':')
            return 0;
    }

    const char *curtok = src;
    int saw_xdigit = 0;
    uint32_t val = 0;
    int ch;
    while ((ch = tolower(*src++)) != '\0')
    {
        const char *pch = strchr(xdigits, ch);
        if (pch != NULL)
        {
            val <<= 4;
            val |= (pch - xdigits);
            if (val > 0xffff)
                return 0;
            saw_xdigit = 1;
            continue;
        }
        if (ch == ':')
        {
            curtok = src;
            if (!saw_xdigit)
            {
                if (colonp)
                    return 0;
                colonp = tp;
                continue;
            }
            else if (*src == '\0')
            {
                return 0;
            }
            if (tp + NS_INT16SZ > endp)
                return 0;
            *tp++ = (uint8_t) (val >> 8) & 0xff;
            *tp++ = (uint8_t) val & 0xff;
            saw_xdigit = 0;
            val = 0;
            continue;
        }
        if (ch == '.' && ((tp + NS_INADDRSZ) <= endp) &&
                inet_pton4(curtok, (char*) tp) > 0)
        {
            tp += NS_INADDRSZ;
            saw_xdigit = 0;
            break; /* '\0' was seen by inet_pton4(). */
        }
        return 0;
    }
    if (saw_xdigit)
    {
        if (tp + NS_INT16SZ > endp)
            return 0;
        *tp++ = (uint8_t) (val >> 8) & 0xff;
        *tp++ = (uint8_t) val & 0xff;
    }
    if (colonp != NULL)
    {
        /*
         * Since some memmove()'s erroneously fail to handle
         * overlapping regions, we'll do the shift by hand.
         */
        const int n = tp - colonp;

        if (tp == endp)
            return 0;

        for (int i = 1; i <= n; i++)
        {
            endp[-i] = colonp[n - i];
            colonp[n - i] = 0;
        }
        tp = endp;
    }
    if (tp != endp)
        return 0;

    memcpy(dst, tmp, NS_IN6ADDRSZ);

    return 1;
}

int inet_pton(int af, const char *src, unsigned long *dst)
{
	if (af == AF_INET) {
		char tmp[NS_INADDRSZ];
		int returnValue = inet_pton4(src, tmp);
        memcpy(dst, tmp, NS_INADDRSZ);
        return returnValue;
	} else if (af == AF_INET6) {
		char tmp[NS_IN6ADDRSZ];
		int returnValue = inet_pton6(src, tmp);
        memcpy(dst, tmp, NS_IN6ADDRSZ);
        return returnValue;
	}

	return -1;
}
#endif

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

template<size_t BufferSize> int vsnprintf_s(char (&buffer)[BufferSize], size_t count, const char *format, va_list argptr)
{
	return vsnprintf_s(buffer, BufferSize, count, format, argptr);
}

#endif
