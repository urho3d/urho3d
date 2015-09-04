/* Copyright The kNet Project.

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License. */

/** @file NetworkLogging.cpp
	@brief Implements logging functionalities to stdout/file for different log channels. */

#include <sstream>
#include <iostream>
#include <fstream>
#include <cstdarg>
#include <cstdio>
#include <string>
#include <cstring>

#ifdef KNET_USE_BOOST
#include <boost/thread/thread.hpp>
#endif

#include "kNet/DebugMemoryLeakCheck.h"

#include "kNet/NetworkLogging.h"
#include "kNet/Lockable.h"
#include "kNet/Clock.h"

#if defined(KNET_UNIX) || defined(ANDROID)
#define _snprintf snprintf
#endif

using namespace std;

namespace kNet
{

namespace
{
/// Specifies which kNet Log Channels are enabled. Log messages printed in other channels are muted.
LogChannel kNetActiveLogChannels = LogUser;
/// Specifies the file in which all logging is printed to. If this file is not open, logging goes to std::cout.
ofstream kNetLogFile;

Lockable<int> logWriteMutex;

string Time()
{
	static tick_t firstTick;
	static bool firstCall = true;
	if (firstCall)
	{
		firstCall = false;
		firstTick = Clock::Tick();
		return "0.000";
	}
	double t = Clock::SecondsSinceD(firstTick);
	std::stringstream ss;
	ss << t;
#ifdef KNET_USE_BOOST
	ss << ", " << boost::this_thread::get_id();
#endif
	return ss.str();
}

} // ~unnamed namespace

void TimeOutputDebugStringVariadic(LogChannel logChannel, const char * /*filename*/, int /*lineNumber*/, const char *msg, ...)
{
	if (!IsLogChannelActive(logChannel))
		return;

	Lockable<int>::LockType lock = logWriteMutex.Acquire();

	char errorStr[1024];
	va_list args;
	va_start(args, msg);
	vsnprintf(errorStr, 1023, msg, args);

	if (kNetLogFile.is_open())
		kNetLogFile << Time() << ": " << errorStr << std::endl;
	else
		std::cout << Time() << ": " << errorStr << std::endl;

	va_end(args);
}

void TimeOutputDebugString(LogChannel logChannel, const char * /*filename*/, int /*lineNumber*/, const char *msg)
{
	if ((logChannel & kNetActiveLogChannels) == 0)
		return;

	Lockable<int>::LockType lock = logWriteMutex.Acquire();

	char errorStr[1024];
	_snprintf(errorStr, 1023, "%s", msg);

	if (kNetLogFile.is_open())
		kNetLogFile << Time() << ": " << errorStr << std::endl;
	else
		std::cout << Time() << ": " << errorStr << std::endl;
}

void SetLogChannels(LogChannel logChannels)
{
	kNetActiveLogChannels = logChannels;
}

LogChannel GetLogChannels()
{
	return kNetActiveLogChannels;
}

bool IsLogChannelActive(LogChannel channel)
{
	return (channel & kNetActiveLogChannels) != 0;
}

void SetLogFile(const char *filename)
{
	Lockable<int>::LockType lock = logWriteMutex.Acquire();

	kNetLogFile.close();
	if (filename && strlen(filename) > 0)
		kNetLogFile.open(filename, ios::app);
}

void EnableMemoryLeakLoggingAtExit()
{
#ifdef _MSC_VER
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	_CrtSetReportMode(_CRT_ASSERT, _CRTDBG_MODE_FILE);
	_CrtSetReportFile(_CRT_ASSERT, _CRTDBG_FILE_STDERR);

	_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_FILE);
	_CrtSetReportFile(_CRT_WARN, _CRTDBG_FILE_STDERR);

	_CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_FILE);
	_CrtSetReportFile(_CRT_ERROR, _CRTDBG_FILE_STDERR);
#endif
}

} // ~kNet
