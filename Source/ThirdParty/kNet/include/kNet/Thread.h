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
#pragma once

/** @file Thread.h
	@brief The Thread class. Implements threading either using Boost, native Win32 or pthreads constructs. */

// Modified by Lasse Oorni for Urho3D

#include <string>

#ifdef KNET_USE_BOOST
#include <boost/thread.hpp>
#else

// Urho3D: include Event.h first to make sure WS2Include.h is included before windows.h / winsock.h
#include "Event.h"

#ifdef _WIN32
// Urho3D: windows.h in lowercase to fix MinGW cross-compiling on a case-sensitive system
#include <windows.h>
#else
#include <pthread.h>
#endif

namespace kNet
{
typedef void (*ThreadEntryFunc)(void *threadStartData);
}

#endif

#define CALL_MEMBER_FN(object,ptrToMember)  ((object).*(ptrToMember))

#include "SharedPtr.h"

namespace kNet
{

#if defined(KNET_USE_BOOST) && defined(KNET_ENABLE_WINXP_SUPPORT)
typedef boost::thread::id ThreadId;
#elif defined(_WIN32)
typedef DWORD ThreadId; // Don't use boost::thread::id on Windows even if KNET_USE_BOOST is #defined, since it has issues identifying threads across dll boundaries.
#elif defined(KNET_USE_BOOST)
typedef boost::thread::id ThreadId;
#else
typedef pthread_t ThreadId;
#endif

std::string ThreadIdToString(const ThreadId &id);

class Thread : public RefCountable
{
public:
	Thread();
	~Thread();

	/// Call this function only from inside the thread that is running. Returns true if the worker thread
	/// should exit immediately.
	bool ShouldQuit() const;

	/// Callable from either the thread owner or the thread itself.
	bool IsRunning() const;

	/// Suspends the thread until 'Resume()' is called. Call this function from the main thread.
	void Hold();

	/// Resumes the thread that is being held.
	void Resume();

	/// Makes the worker thread sleep if this thread is held, until this thread is resumed. Only callable
	/// from the worker thread.
	void CheckHold();

	/// Tries first to gracefully close the thread (waits for a while), and forcefully terminates the thread if
	/// it didn't respond in that time. \todo Allow specifying the timeout period.
	void Stop();

	/// Sets the name of this thread. This method is implemented for debugging purposes only, and does not do anything
	/// if running outside Visual Studio debugger.
	void SetName(const char *name);

	template<typename Class, typename MemberFuncPtr, typename FuncParam>
	void Run(Class *obj, MemberFuncPtr memberFuncPtr, const FuncParam &param);

	template<typename Class, typename MemberFuncPtr>
	void Run(Class *obj, MemberFuncPtr memberFuncPtr);

	template<typename FuncPtr, typename FuncParam, typename FuncParam2>
	void RunFunc(FuncPtr funcPtr, const FuncParam &param, const FuncParam2 &param2);

	template<typename FuncPtr, typename FuncParam>
	void RunFunc(FuncPtr funcPtr, const FuncParam &param);

	template<typename FuncPtr>
	void RunFunc(FuncPtr funcPtr);

	/// Sleeps the current thread for the given amount of time, or interrupts the sleep if the thread was signalled
	/// to quit in between.
	static void Sleep(int msecs);

	ThreadId Id();

	static ThreadId CurrentThreadId();
	static ThreadId NullThreadId();
private:
	Thread(const Thread &);
	void operator =(const Thread &);

	class ObjInvokeBase : public RefCountable
	{
	public:
		virtual void Invoke() = 0;
		virtual ~ObjInvokeBase() {}

		void operator()()
		{
			Invoke();
		}
	};

	template<typename FuncPtr>
	class FuncInvokerVoid : public ObjInvokeBase
	{
	public:
		FuncPtr funcPtr;
		FuncInvokerVoid(FuncPtr funcPtr_)
		:funcPtr(funcPtr_){}

		virtual void Invoke() { funcPtr(); }
	};

	template<typename FuncPtr, typename FuncParam>
	class FuncInvokerUnary : public ObjInvokeBase
	{
	public:
		FuncPtr funcPtr;
		FuncParam param;
		FuncInvokerUnary(FuncPtr funcPtr_, const FuncParam &param_)
		:funcPtr(funcPtr_), param(param_){}

		virtual void Invoke() { funcPtr(param); }
	};

	template<typename FuncPtr, typename FuncParam, typename FuncParam2>
	class FuncInvokerBinary : public ObjInvokeBase
	{
	public:
		FuncPtr funcPtr;
		FuncParam param;
		FuncParam2 param2;
		FuncInvokerBinary(FuncPtr funcPtr_, const FuncParam &param_, const FuncParam2 &param2_)
		:funcPtr(funcPtr_), param(param_), param2(param2_){}

		virtual void Invoke() { funcPtr(param, param2); }
	};

	template<typename Class, typename MemberFuncPtr>
	class ClassInvokerVoid : public ObjInvokeBase
	{
	public:
		Class *obj;
		MemberFuncPtr memberFuncPtr;
		ClassInvokerVoid(Class *obj_, MemberFuncPtr memberFuncPtr_)
		:obj(obj_), memberFuncPtr(memberFuncPtr_){}

		virtual void Invoke() { CALL_MEMBER_FN(*obj, memberFuncPtr)(); }
	};

	template<typename Class, typename MemberFuncPtr, typename FuncParam>
	class ClassInvokerUnary : public ObjInvokeBase
	{
	public:
		Class *obj;
		MemberFuncPtr memberFuncPtr;
		FuncParam param;
		ClassInvokerUnary(Class *obj_, MemberFuncPtr memberFuncPtr_, const FuncParam &param_)
		:obj(obj_), memberFuncPtr(memberFuncPtr_), param(param_){}

		virtual void Invoke() { CALL_MEMBER_FN(*obj, memberFuncPtr)(param); }
	};

	ObjInvokeBase *invoker;

	// The following objects are used to implement thread suspendion/holding.
	Event threadHoldEvent;
	Event threadHoldEventAcked;
	Event threadResumeEvent;

	void StartThread();

#ifdef KNET_USE_BOOST
	boost::thread thread;
#elif defined(_WIN32)
	HANDLE threadHandle;
	ThreadId threadId;

	/// The entry point that is called from the trampoline. Do not call this function.
	void _ThreadRun();

	friend DWORD WINAPI ThreadEntryPoint(LPVOID lpParameter);
private:
	bool threadEnabled;
#else
	pthread_t thread;

	void _ThreadRun();

	friend void* ThreadEntryPoint(void* data);
private:
	bool threadEnabled;
#endif
};

template<typename Class, typename MemberFuncPtr, typename FuncParam>
void Thread::Run(Class *obj, MemberFuncPtr memberFuncPtr, const FuncParam &param)
{
	Stop();
	invoker = new ClassInvokerUnary<Class, MemberFuncPtr, FuncParam>(obj, memberFuncPtr, param);
	StartThread();
}

template<typename Class, typename MemberFuncPtr>
void Thread::Run(Class *obj, MemberFuncPtr memberFuncPtr)
{
	Stop();
	invoker = new ClassInvokerVoid<Class, MemberFuncPtr>(obj, memberFuncPtr);
	StartThread();
}

template<typename FuncPtr, typename FuncParam, typename FuncParam2>
void Thread::RunFunc(FuncPtr funcPtr, const FuncParam &param, const FuncParam2 &param2)
{
	Stop();
	invoker = new FuncInvokerBinary<FuncPtr, FuncParam, FuncParam2>(funcPtr, param, param2);
	StartThread();
}

template<typename FuncPtr, typename FuncParam>
void Thread::RunFunc(FuncPtr funcPtr, const FuncParam &param)
{
	Stop();
	invoker = new FuncInvokerUnary<FuncPtr, FuncParam>(funcPtr, param);
	StartThread();
}

template<typename FuncPtr>
void Thread::RunFunc(FuncPtr funcPtr)
{
	Stop();
	invoker = new FuncInvokerVoid<FuncPtr>(funcPtr);
	StartThread();
}

} // ~kNet
