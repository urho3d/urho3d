/*
 *  Copyright (c) 2016-2017, SLikeSoft UG (haftungsbeschränkt)
 *
 *  This source code is licensed under the MIT-style license found in the
 *  license.txt file in the root directory of this source tree.
 *
 *
 *  This file defines adapters for all MS-specific functions used throughout SLikeNet.
 */

#ifdef __linux__
#include "slikenet/linux_adapter.h"

#include <algorithm>	// for std::max, std::min
#include <cerrno>		// for errno
#include <cstdio>		// for FILE, fopen, vsnprintf
#include <cstdlib>		// for mbstowcs
#include <cstring>		// for strcat, strcpy, strncat, strncpy
#include <cstdarg>		// for va_start, va_end, va_list
#include <ctime>		// for localtime, time_t
#include <cwchar>		// for wcscat, wcscpy, wcslen

errno_t fopen_s(FILE **pfile, const char *filename, const char *mode)
{
	if ((pfile == nullptr) || (filename == nullptr) || (mode == nullptr)) {
		return 22; // error: EINVAL
	}

	FILE *file = fopen(filename, mode);
	if (file == nullptr) {
		return errno;
	}

	*pfile = file;
	return 0;
}

errno_t localtime_s(struct tm *_tm, const time_t *time)
{
	// #med - should actually also check for _*time > _MAX_TIME64_T according to MSDN, but can't seem to find the
	// definition of _MAX_TIME64_T
	if ((_tm == nullptr) || (time == nullptr) || (*time == 0)) {
		if (_tm != nullptr) {
			_tm->tm_hour  = -1;
			_tm->tm_isdst = -1;
			_tm->tm_mday  = -1;
			_tm->tm_min   = -1;
			_tm->tm_mon   = -1;
			_tm->tm_sec   = -1;
			_tm->tm_wday  = -1;
			_tm->tm_yday  = -1;
			_tm->tm_year  = -1;
		}
		return 22; // error: EINVAL
	}

	struct tm *curTime = localtime(time);
	*_tm = *curTime;

	return 0;
}

errno_t mbstowcs_s(size_t *pReturnValue, wchar_t *wcstr, size_t sizeInWords, const char *mbstr, size_t count)
{
	if ((mbstr == nullptr) || ((wcstr == nullptr) && (sizeInWords > 0)) || ((wcstr != nullptr) && (sizeInWords != 0))) {
		if (wcstr != nullptr) {
			wcstr[0] = L'\0'; // ensure 0-termination
		}
		return 22; // error: EINVAL
	}

	size_t numMaxChars = sizeInWords;
	if (count != _TRUNCATE) {
		numMaxChars = std::min(numMaxChars, count);
	}

	size_t numCharsWritten = mbstowcs(wcstr, mbstr, numMaxChars);
	if (numCharsWritten == (size_t)-1) {
		// invalid multibyte character encountered
		if (pReturnValue != nullptr) {
			*pReturnValue = 0;
		}
		if (wcstr != nullptr) {
			wcstr[0] = L'\0'; // ensure 0-termination
		}
		return 42; // error: EILSEQ
	}

	if (numCharsWritten == numMaxChars) {
		if (wcstr != nullptr) {
			wcstr[0] = L'\0'; // ensure 0-termination
		}
		return 34; // error: ERANGE
	}

	if (pReturnValue != nullptr) {
		*pReturnValue = numCharsWritten + 1; // chars written, including terminating null character
	}

	// ensure we write a terminating null character (in case there was none in the original converted string)
	if (wcstr != nullptr) {
		wcstr[numCharsWritten] = L'\0'; // ensure 0-termination
	}

	return 0;
}

int sprintf_s(char *buffer, size_t sizeOfBuffer, const char *format, ...)
{
	if ((buffer == nullptr) || (sizeOfBuffer == 0) || (format == nullptr)) {
		return -1;
	}

	va_list arglist;
	va_start(arglist, format);
	int numCharsWritten = vsnprintf(buffer, sizeOfBuffer, format, arglist);
	va_end(arglist);

	if (numCharsWritten == -1) {
		buffer[0] = '\0'; // error occurred ensure terminating \0-character
		return -1;
	}

	if (numCharsWritten >= sizeOfBuffer) {
		buffer[0] = '\0'; // buffer too small, write empty string to ensure terminating \0-char
	}

	return numCharsWritten;
}

errno_t strcat_s(char *strDestination, size_t numberOfElements, const char *strSource)
{
	if ((strDestination == nullptr) || (strSource == nullptr)) {
		if (strDestination != nullptr) {
			strDestination[0] = '\0'; // ensure trailing \0 is written
		}
		return 22; // error: EINVAL
	}

	if (numberOfElements == 0) {
		strDestination[0] = '\0'; // ensure trailing \0 is written
		return 34; // error: ERANGE
	}

	const size_t destLen = strlen(strDestination);
	const size_t sourceLen = strlen(strSource);
	if ((destLen > numberOfElements - 1) || ((sourceLen > 0) && (destLen == numberOfElements - 1)) || (sourceLen > numberOfElements - destLen - 1)) {
		strDestination[0] = '\0'; // ensure trailing \0 is written
		return 34; // error: ERANGE
	}

	(void)strcat(strDestination, strSource);
	return 0;
}

errno_t strcpy_s(char* strDestination, size_t numberOfElements, const char *strSource)
{
	if ((strDestination == nullptr) || (strSource == nullptr)) {
		if (strDestination != nullptr) {
			strDestination[0] = '\0'; // ensure trailing \0 is written
		}
		return 22; // error: EINVAL
	}

	if ((numberOfElements == 0) || (strlen(strSource) >= numberOfElements)) {
		strDestination[0] = '\0'; // ensure trailing \0 is written
		return 34; // error: ERANGE
	}

	(void)strcpy(strDestination, strSource);
	return 0;
}

errno_t strncat_s(char *strDest, size_t numberOfElements, const char *strSource, size_t count)
{
	// check valid parameters
	if ((strDest == nullptr) || (strSource == nullptr)) {
		return 22; // error: EINVAL
	}

	if (numberOfElements == 0) {
		return 34; // error: ERANGE
	}

	size_t charsToWrite;
	const size_t sourceLen = strlen(strSource);
	if (count == _TRUNCATE) {
		charsToWrite = sourceLen;
	}
	else {
		charsToWrite = std::min(count, sourceLen);
	}

	const size_t destLen = strlen(strDest);
	const size_t sizeLeft = numberOfElements - destLen;

	if (((count != _TRUNCATE) && (charsToWrite > sizeLeft - 1)) || ((sourceLen > 0) && (destLen == numberOfElements - 1))) {
		strDest[0] = '\0'; // ensure trailing \0 is written
		return 34; // error: ERANGE
	}

	(void)strncat(strDest, strSource, charsToWrite);
	return 0;
}

errno_t strncpy_s(char *strDest, size_t numberOfElements, const char *strSource, size_t count)
{
	// check valid parameters
	if ((numberOfElements == 0) || (strDest == nullptr) || (strSource == nullptr)) {
		if (strDest != nullptr) {
			strDest[0] = '\0'; // ensure trailing \0 is written
		}
		return 22; // error: EINVAL
	}

	size_t numChars;
	bool truncated = false;
	if (count == _TRUNCATE) {
		// if count == _TRUNCATE use the length of the source string
		numChars = strlen(strSource);

		// ensure we are not exceeding numberOfElements
		if (numChars >= numberOfElements) {
			numChars = numberOfElements - 1;
			truncated = true; // we are going to truncate the copied string
		}
	}
	else {
		// otherwise we use count, but have to check that the destination buffer is of sufficient size
		if ((count > numberOfElements) || ((count == numberOfElements) && (strSource[count] != '\0'))) {
			strDest[0] = '\0'; // ensure trailing \0 is written
			return 34; // error: ERANGE
		}
		numChars = count;
	}

	(void)strncpy(strDest, strSource, numChars);

	// enforce the trailing \0
	strDest[numChars] = '\0';

	return truncated ? 80 : 0; // STRUNCATE, if we truncated the string, 0 otherwise
}

int vsnprintf_s(char *buffer, size_t sizeOfBuffer, size_t count, const char *format, va_list argptr)
{
	if ((buffer == nullptr) || (format == nullptr) || (sizeOfBuffer == 0)) {
		return -1;
	}

	size_t maxChars = sizeOfBuffer;
	if (count != _TRUNCATE) {
		if (count >= sizeOfBuffer) {
			buffer[0] = '\0'; // ensure trailing \0 is written
			return -1;
		}
		maxChars = count;
	}

	int numCharsWritten = vsnprintf(buffer, maxChars, format, argptr);
	if (numCharsWritten >= maxChars) {
		if (count != _TRUNCATE) {
			buffer[0] = '\0'; // buffer set to empty string
			return -1;
		}

		// truncation occurred, add terminating \0
		buffer[sizeOfBuffer] = '\0';
	}

	return numCharsWritten;
}

errno_t wcscat_s(wchar_t *strDestination, size_t numberOfElements, const wchar_t *strSource)
{
	if ((strDestination == nullptr) || (strSource == nullptr)) {
		if (strDestination != nullptr) {
			strDestination[0] = L'\0'; // ensure trailing \0 is written
		}
		return 22; // error: EINVAL
	}

	if (numberOfElements == 0) {
		strDestination[0] = L'\0'; // ensure trailing \0 is written
		return 34; // error: ERANGE
	}

	const size_t destLen = wcslen(strDestination);
	const size_t sourceLen = wcslen(strSource);
	if ((destLen > numberOfElements - 1) || ((sourceLen > 0) && (destLen == numberOfElements)) || (sourceLen > numberOfElements - destLen - 1)) {
		strDestination[0] = L'\0'; // ensure trailing \0 is written
		return 34; // error: ERANGE
	}

	(void)wcscat(strDestination, strSource);
	return 0;
}

errno_t wcscpy_s(wchar_t* strDestination, size_t numberOfElements, const wchar_t *strSource)
{
	if ((strDestination == nullptr) || (strSource == nullptr)) {
		if (strDestination != nullptr) {
			strDestination[0] = L'\0'; // ensure trailing \0 is written
		}
		return 22; // error: EINVAL
	}

	if ((numberOfElements == 0) || (wcslen(strSource) >= numberOfElements)) {
		strDestination[0] = L'\0'; // ensure trailing \0 is written
		return 34; // error: ERANGE
	}

	(void)wcscpy(strDestination, strSource);
	return 0;
}

#endif


#ifdef __MINGW32__
#include <cstdarg>  // for va_start, va_end, va_list
#include <cstdio>   // for FILE
#include <ctime>    // for time_t
#include <stdint.h>
#include "winsock2.h"
#include "ws2tcpip.h"


#define NS_INADDRSZ  4
#define NS_IN6ADDRSZ 16
#define NS_INT16SZ   2
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