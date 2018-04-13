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

#ifdef __linux__
#define _TRUNCATE ((size_t)-1)
typedef int errno_t;

#include <cstdarg>	// for va_start, va_end, va_list
#include <cstdio>	// for FILE
#include <ctime>	// for time_t

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
