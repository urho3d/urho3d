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

/** @file W32Thread.cpp
	@brief */

#include <cassert>
#include <exception>

#include "kNet/Thread.h"
#include "kNet/NetworkLogging.h"
#include "kNet/Clock.h"
#include "kNet/NetException.h"
#include "kNet/Network.h"

#include "kNet/DebugMemoryLeakCheck.h"

namespace kNet
{

Thread::Thread()
:threadHandle(NULL),
threadId(0),
threadEnabled(false),
invoker(0)
{
}

Thread::~Thread()
{
	Stop();
	delete invoker;
}

bool Thread::ShouldQuit() const { return threadHandle == NULL || threadEnabled == false; }

bool Thread::IsRunning() const
{ 
	if (threadHandle == NULL)
		return false;

	DWORD exitCode = 0;
	BOOL result = GetExitCodeThread(threadHandle, &exitCode);

	if (result == 0)
	{
		KNET_LOG(LogError, "Warning: Received error %d from GetExitCodeThread in Thread::IsRunning!", GetLastError());
		return false;
	}

	return exitCode == STILL_ACTIVE;
}

void Thread::Stop()
{
	// Signal that the thread should quit now.
	threadEnabled = false;

	if (threadHandle == NULL)
	{
		threadHoldEvent.Close();
		threadHoldEventAcked.Close();
		threadResumeEvent.Close();

		delete invoker;
		invoker = 0;
		return;
	}

	kNet::Clock::Sleep(10);
	assert(threadHandle != 0);

	int numTries = 100;
	while(numTries-- > 0)
	{
		DWORD exitCode = 0;
		BOOL result = GetExitCodeThread(threadHandle, &exitCode);

		if (result == 0)
		{
			KNET_LOG(LogError, "Warning: Received error %d from GetExitCodeThread in Thread::Stop()!", GetLastError());
			break;
		}
		else if (exitCode != STILL_ACTIVE)
		{
			CloseHandle(threadHandle);
			threadHandle = NULL;
			break;
		}
		kNet::Clock::Sleep(50);
	}

	if (threadHandle != NULL)
	{
		TerminateThread(threadHandle, (DWORD)-1);
//		CloseHandle(threadHandle);
		KNET_LOG(LogError, "Warning: Had to forcibly terminate thread!");
	}

	KNET_LOG(LogInfo, "Thread::Stop() called.");

	threadHandle = NULL;
	threadId = 0;

	delete invoker;
	invoker = 0;

	threadHoldEvent.Close();
	threadHoldEventAcked.Close();
	threadResumeEvent.Close();
}

DWORD WINAPI ThreadEntryPoint(LPVOID lpParameter)
{
	KNET_LOG(LogInfo, "ThreadEntryPoint: Thread started with param 0x%08X.", lpParameter);

	Thread *thread = reinterpret_cast<Thread*>(lpParameter);
	if (!thread)
	{
		KNET_LOG(LogError, "Invalid thread start parameter 0!");
		return (DWORD)-1;
	}
	thread->_ThreadRun();

	return 0;
}

void Thread::_ThreadRun()
{
	try
	{
		if (!threadEnabled)
		{
			KNET_LOG(LogError, "ThreadEntryPoint: Thread immediately requested to quit.");
			return;
		}

		invoker->Invoke();
	} catch(NetException &e)
	{
		KNET_LOG(LogError, "NetException thrown in thread: %s.", e.what());
	} catch(std::exception &e)
	{
		KNET_LOG(LogError, "std::exception thrown in thread: %s.", e.what());
	} catch(...)
	{
		KNET_LOG(LogError, "Unknown exception thrown in thread.");
	}
}

void Thread::StartThread()
{
	if (threadHandle != NULL)
		return;

	threadHoldEvent = CreateNewEvent(EventWaitSignal);
	threadHoldEventAcked = CreateNewEvent(EventWaitSignal);
	threadResumeEvent = CreateNewEvent(EventWaitSignal);

	threadEnabled = true;
	threadHandle = CreateThread(NULL, 0, ThreadEntryPoint, this, 0, &threadId);
	if (threadHandle == NULL)
		throw NetException("Failed to create thread!");
	else
		KNET_LOG(LogInfo, "Thread::Run(): Thread created.");

	SetName("kNet Thread");
}

void Thread::Sleep(int msecs)
{
	///\todo Allow interruption between sleep.
	Clock::Sleep(msecs);
}

ThreadId Thread::Id()
{
	return threadId;
}

ThreadId Thread::CurrentThreadId()
{
	return GetCurrentThreadId();
}

ThreadId Thread::NullThreadId()
{
	return 0;
}

} // ~kNet
