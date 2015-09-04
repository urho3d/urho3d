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

/** @file Thread.cpp
	@brief Implements platform-generic Thread functions. */

#ifdef KNET_USE_BOOST
#include <boost/thread/thread.hpp>
#endif

#include <sstream>

#include "kNet/DebugMemoryLeakCheck.h"
#include "kNet/Event.h" ///\todo Investigate the inclusion chain of these two files. Is this #include necessary?
#include "kNet/NetworkLogging.h"
#include "kNet/Thread.h"
#include "kNet/PolledTimer.h"

namespace kNet
{

std::string ThreadIdToString(const ThreadId &id)
{
	std::stringstream ss;
	ss << id;
	return ss.str();
}

/// Suspends the thread until 'Resume()' is called. Call this function from the main thread.
void Thread::Hold()
{
	if (threadHoldEvent.Test())
		return;

	threadResumeEvent.Reset();
	threadHoldEvent.Reset();
	threadHoldEventAcked.Reset();

	threadHoldEvent.Set();

	PolledTimer timer;
	while(IsRunning())
	{
		bool success = threadHoldEventAcked.Wait(1000);
		if (success)
			break;
	}
	KNET_LOG(LogWaits, "Thread::Hold: Took %f msecs.", timer.MSecsElapsed());
}

/// Resumes the thread that is being held.
void Thread::Resume()
{
	threadResumeEvent.Set();
	threadHoldEvent.Reset();
	threadHoldEventAcked.Reset();
}

void Thread::CheckHold()
{
	if (threadHoldEvent.Test())
	{
		KNET_LOG(LogVerbose, "Thread::CheckHold(): suspending thread. this: %p.", this);

		PolledTimer timer;
		while(!ShouldQuit())
		{
			threadHoldEventAcked.Set();
			bool success = threadResumeEvent.Wait(1000);
			if (success)
				break;
		}
		KNET_LOG(LogWaits, "Thread::CheckHold: Slept for %f msecs.", timer.MSecsElapsed());
		threadHoldEventAcked.Reset();
	}
}

// This code adapted from http://msdn.microsoft.com/en-us/library/xcb2z8hs.aspx "How to: Set a Thread Name in Native Code":
#ifdef WIN32
const DWORD MS_VC_EXCEPTION=0x406D1388;

#pragma pack(push,8)
typedef struct tagTHREADNAME_INFO
{
	DWORD dwType; // Must be 0x1000.
	LPCSTR szName; // Pointer to name (in user addr space).
	DWORD dwThreadID; // Thread ID (-1=caller thread).
	DWORD dwFlags; // Reserved for future use, must be zero.
} THREADNAME_INFO;
#pragma pack(pop)

void SetThreadName(DWORD dwThreadID, const char *threadName)
{
#ifdef _MSC_VER
	THREADNAME_INFO info;
	info.dwType = 0x1000;
	info.szName = threadName;
	info.dwThreadID = dwThreadID;
	info.dwFlags = 0;

	__try
	{
		RaiseException(MS_VC_EXCEPTION, 0, sizeof(info)/sizeof(ULONG_PTR), (ULONG_PTR*)&info);
	}
//	__except(EXCEPTION_EXECUTE_HANDLER)
	__except(EXCEPTION_CONTINUE_EXECUTION)
	{
	}
#else
#warning SetThreadName undefined for current platform!
#endif
}
#endif

void Thread::SetName(const char *name)
{
// The thread name can only be set when it is ensured that Thread::Id() returns the proper Win32 thread ID
#ifdef WIN32
#if !defined(KNET_USE_BOOST) || !defined(KNET_ENABLE_WINXP_SUPPORT)
	SetThreadName(Id(), name);
#endif
#endif
}

} // ~kNet
