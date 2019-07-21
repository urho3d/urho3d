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

#ifndef CAT_WAITABLE_FLAG_HPP
#define CAT_WAITABLE_FLAG_HPP

#include <cat/Platform.hpp>

#if defined(CAT_OS_WINDOWS)
# include <cat/port/WindowsInclude.hpp>
#else // use POSIX thread library otherwise
# include <pthread.h>
#endif

namespace cat {


/*
	class WaitableFlag

	Can be set, reset or waited upon.

	Initially unset.
	Flag is edge-triggered.
	Successful waiting will reset the flag.
	Only one thread can wait at a time.

	Designed to synchronize threads:
		One thread can wait for this flag to be raised by another thread before continuing.
*/
class WaitableFlag
{
#if defined(CAT_OS_WINDOWS)
	HANDLE _event;
#else
	bool _valid, _valid_cond, _valid_mutex;
	volatile u32 _flag;
	pthread_cond_t _cond;
	pthread_mutex_t _mutex;
#endif

	void Cleanup();

public:
	WaitableFlag();
	CAT_INLINE virtual ~WaitableFlag()
	{
		Cleanup();
	}

	CAT_INLINE bool Valid()
	{
#if defined(CAT_OS_WINDOWS)
		return _event != 0;
#else
		return _valid;
#endif
	}

	bool Set();
	bool Wait(int milliseconds = -1); // < 0 = wait forever
};


} // namespace cat

#endif // CAT_WAITABLE_FLAG_HPP
