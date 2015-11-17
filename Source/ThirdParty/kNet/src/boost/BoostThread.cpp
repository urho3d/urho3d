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

/** @file BoostThread.cpp
	@brief */
#ifdef KNET_USE_BOOST

#include <cassert>
#include <exception>

#include <boost/thread/thread.hpp>

#include "kNet/DebugMemoryLeakCheck.h"

#include "kNet/Event.h"
#include "kNet/Thread.h"

#include "kNet/NetworkLogging.h"
#include "kNet/Clock.h"
#include "kNet/NetException.h"
#include "kNet/PolledTimer.h"

namespace kNet
{

Thread::Thread()
:invoker(0)
{
}

Thread::~Thread()
{
	Stop();
}

bool Thread::ShouldQuit() const
{ 
	boost::this_thread::interruption_point();
	return thread.interruption_requested();
}

bool Thread::IsRunning() const
{ 
	return thread.get_id() != boost::thread::id();
}

void Thread::Stop()
{
	PolledTimer timer;

	thread.interrupt();
	thread.join();

	LOG(LogWaits, "Thread::Stop: Took %f msecs.", timer.MSecsElapsed());

	delete invoker;
	invoker = 0;

	threadHoldEvent.Close();
	threadHoldEventAcked.Close();
	threadResumeEvent.Close();
}

void Thread::StartThread()
{
	if (IsRunning())
		Stop();

	threadHoldEvent = CreateNewEvent(EventWaitSignal);
	threadHoldEventAcked = CreateNewEvent(EventWaitSignal);
	threadResumeEvent = CreateNewEvent(EventWaitSignal);

	thread = boost::thread(boost::ref(*invoker));

	SetName("kNet Thread");
}

void Thread::Sleep(int msecs)
{
	boost::this_thread::sleep(boost::posix_time::millisec(msecs));
}

ThreadId Thread::Id()
{
#if defined(_WIN32) && !defined(KNET_ENABLE_WINXP_SUPPORT)
	HANDLE threadHandle = (HANDLE)thread.native_handle();
	if (threadHandle == NULL)
		return NullThreadId();

	ThreadId id = GetThreadId(threadHandle);
	return id;

#else
	return thread.get_id();
#endif
}

ThreadId Thread::CurrentThreadId()
{
#if defined(_WIN32) && !defined(KNET_ENABLE_WINXP_SUPPORT)
	// On Windows, don't rely on Boost, since it is known to improperly read thread ids at least on Boost 1.40.0.
	return GetCurrentThreadId();
#else
	return boost::this_thread::get_id();
#endif
}

ThreadId Thread::NullThreadId()
{
#if defined(_WIN32) && !defined(KNET_ENABLE_WINXP_SUPPORT)
	return 0;
#else
	return boost::thread::id();
#endif
}

} // ~kNet

#endif // ~KNET_USE_BOOST
