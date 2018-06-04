/*
 *  Copyright (c) 2016-2017, SLikeSoft UG (haftungsbeschränkt)
 *
 *  This source code is licensed under the MIT-style license found in the
 *  license.txt file in the root directory of this source tree.
 *
 *
 *  This file defines adapters for all MS-specific functions used throughout SLikeNet.
 */

#ifdef __APPLE__
#include "slikenet/osx_adapter.h"

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
