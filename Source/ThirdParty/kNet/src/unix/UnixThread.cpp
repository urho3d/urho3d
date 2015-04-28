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

/** @file UnixThread.cpp
	@brief */

#ifdef KNET_UNIX

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
:thread(0),
threadEnabled(false),
invoker(0)
{
}

Thread::~Thread()
{
	Stop();
	delete invoker;
}

bool Thread::ShouldQuit() const { return !thread || threadEnabled == false; }

bool Thread::IsRunning() const
{ 
	return thread != 0;
}

void Thread::Stop()
{
	// Signal that the thread should quit now.
	threadEnabled = false;

	if (!thread)
	{
		threadHoldEvent.Close();
		threadHoldEventAcked.Close();
		threadResumeEvent.Close();

		delete invoker;
		invoker = 0;
		return;
	}

	kNet::Clock::Sleep(10);
	assert(thread);

	/// \todo Do not block indefinitely while waiting for the thread to terminate
	pthread_join(thread, 0);
	thread = 0;

	KNET_LOG(LogInfo, "Thread::Stop() called.");

	delete invoker;
	invoker = 0;

	threadHoldEvent.Close();
	threadHoldEventAcked.Close();
	threadResumeEvent.Close();
}

void* ThreadEntryPoint(void* data)
{
	KNET_LOG(LogInfo, "ThreadEntryPoint: Thread started with param 0x%p.", data);

	Thread *thread = reinterpret_cast<Thread*>(data);
	if (!thread)
	{
		KNET_LOG(LogError, "Invalid thread start parameter 0!");
		return 0;
	}
	thread->_ThreadRun();
	pthread_exit((void*)0);
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
	if (thread)
		return;

	threadHoldEvent = CreateNewEvent(EventWaitSignal);
	threadHoldEventAcked = CreateNewEvent(EventWaitSignal);
	threadResumeEvent = CreateNewEvent(EventWaitSignal);

	threadEnabled = true;
	pthread_attr_t type;
	pthread_attr_init(&type);
	pthread_attr_setdetachstate(&type, PTHREAD_CREATE_JOINABLE);
	if (pthread_create(&thread, &type, ThreadEntryPoint, this))
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
	return thread;
}

ThreadId Thread::CurrentThreadId()
{
	return pthread_self();
}

ThreadId Thread::NullThreadId()
{
	return 0;
}

} // ~kNet

#endif // ~KNET_UNIX
