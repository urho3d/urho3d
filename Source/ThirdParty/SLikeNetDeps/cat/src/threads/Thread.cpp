/*
	Copyright (c) 2009-2010 Christopher A. Taylor.  All rights reserved.

	Redistribution and use in source and binary forms, with or without
	modification, are permitted provided that the following conditions are met:

	* Redistributions of source code must retain the above copyright notice,
	  this list of conditions and the following disclaimer.
	* Redistributions in binary form must reproduce the above copyright notice,
	  this list of conditions and the following disclaimer in the documentation
	  and/or other materials provided with the distribution.
	* Neither the name of LibCat nor the names of its contributors may be used
	  to endorse or promote products derived from this software without
	  specific prior written permission.

	THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
	AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
	IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
	ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
	LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
	CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
	SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
	INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
	CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
	ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
	POSSIBILITY OF SUCH DAMAGE.
*/

#include <cat/threads/Thread.hpp>
#include <cat/time/Clock.hpp>
using namespace cat;

#if defined(CAT_OS_WINDOWS)

#include <process.h>

unsigned int __stdcall Thread::ThreadWrapper(void *this_object)
{
	Thread *thread_object = static_cast<Thread*>( this_object );

	bool success = thread_object->ThreadFunction(thread_object->caller_param);

	unsigned int exitCode = success ? 0 : 1;

	// Using _beginthreadex() and _endthreadex() since _endthread() calls CloseHandle()
	_endthreadex(exitCode);

	thread_object->_thread_running = false;

	return exitCode;
}

#else

void *Thread::ThreadWrapper(void *this_object)
{
	Thread *thread_object = static_cast<Thread*>( this_object );

	bool success = thread_object->ThreadFunction(thread_object->caller_param);

	thread_object->_thread_running = false;

	return (void*)(success ? 0 : 1);
}

#endif


//// Thread

Thread::Thread()
{
	_thread_running = false;
}

bool Thread::StartThread(void *param)
{
	if (_thread_running)
		return false;

	caller_param = param;
	_thread_running = true;

#if defined(CAT_OS_WINDOWS)

	// Using _beginthreadex() and _endthreadex() since _endthread() calls CloseHandle()
	_thread = (HANDLE)_beginthreadex(0, 0, &Thread::ThreadWrapper, static_cast<void*>( this ), 0, 0);

	if (!_thread)
		_thread_running = false;

	return _thread != 0;

#else

	_thread_running = true;
	if (pthread_create(&_thread, 0, &Thread::ThreadWrapper, static_cast<void*>( this )))
	{
		_thread_running = false;
		return false;
	}

	return true;

#endif
}

void Thread::AbortThread()
{
	if (!_thread_running)
		return;

#if defined(CAT_OS_WINDOWS)

	if (_thread)
	{
		DWORD ExitCode;

		// If we can get an exit code for the thread,
		if (GetExitCodeThread(_thread, &ExitCode) != 0)
		{
			TerminateThread(_thread, ExitCode);
		}

		CloseHandle(_thread);
		_thread = 0;
	}

#else

	pthread_cancel(_thread);

#endif

	_thread_running = false;
}

bool Thread::WaitForThread(int ms)
{
	if (!_thread_running)
		return true;

	bool success = false;

#if defined(CAT_OS_WINDOWS)

	if (_thread)
	{
		// Signal termination event and block waiting for thread to signal termination
		if (WaitForSingleObject(_thread, (ms >= 0) ? ms : INFINITE) != WAIT_FAILED)
		{
			success = true;

			CloseHandle(_thread);
			_thread = 0;
		}
	}

#else

	// TODO: No way to specify a wait timeout for POSIX threads?
	if (pthread_join(_thread, 0) == 0)
		success = true;

#endif

	if (success)
		_thread_running = false;

	return success;
}
