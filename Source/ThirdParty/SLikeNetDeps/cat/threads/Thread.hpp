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

#ifndef CAT_THREAD_HPP
#define CAT_THREAD_HPP

#include <cat/Platform.hpp>

#if defined(CAT_OS_WINDOWS)
# include <cat/port/WindowsInclude.hpp>
#else // use POSIX thread library otherwise
# include <pthread.h>
#endif

namespace cat {


/*
	A thread that executes ThreadFunction and then exits.

	Derive from this class and implement ThreadFunction().
*/
class Thread
{
protected:
	void *caller_param;
	volatile bool _thread_running;

#if defined(CAT_OS_WINDOWS)
	volatile HANDLE _thread;
	static unsigned int __stdcall ThreadWrapper(void *this_object);
#else
	pthread_t _thread;
	static void *ThreadWrapper(void *this_object);
#endif

public:
	bool StartThread(void *param = 0);
	bool WaitForThread(int milliseconds = -1); // < 0 = infinite wait
	void AbortThread();

	CAT_INLINE bool ThreadRunning() { return _thread_running; }

protected:
	virtual bool ThreadFunction(void *param) = 0;

public:
	Thread();
	CAT_INLINE virtual ~Thread() {}
};


} // namespace cat

#endif // CAT_THREAD_HPP
