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

#include <cat/threads/WaitableFlag.hpp>
#include <cat/time/Clock.hpp>
using namespace cat;

#if !defined(CAT_OS_WINDOWS)
#include <sys/time.h> // gettimeofday
#include <errno.h> // ETIMEDOUT
#endif

WaitableFlag::WaitableFlag()
{
#if defined(CAT_OS_WINDOWS)

	_event = CreateEvent(0, FALSE, FALSE, 0);

#else

	_flag = 0;
	_valid = false;
	_valid_cond = false;
	_valid_mutex = false;

	_valid_cond = pthread_cond_init(&_cond, 0) == 0;
	if (!_valid_cond) return;

	_valid_mutex = pthread_mutex_init(&_mutex, 0) == 0;
	if (!_valid_mutex) return;

	_valid = true;

#endif
}

void WaitableFlag::Cleanup()
{
#if defined(CAT_OS_WINDOWS)

	if (_event)
	{
		CloseHandle(_event);
		_event = 0;
	}

#else

	if (_valid_cond)
	{
		pthread_cond_destroy(&_cond);
		_valid_cond = false;
	}

	if (_valid_mutex)
	{
		pthread_mutex_destroy(&_mutex);
		_valid_mutex = false;
	}

#endif
}

bool WaitableFlag::Set()
{
#if defined(CAT_OS_WINDOWS)

	if (_event)
	{
		return SetEvent(_event) == TRUE;
	}

#else

	if (_valid)
	{
		pthread_mutex_lock(&_mutex);

		_flag = 1;

		pthread_mutex_unlock(&_mutex);

		return pthread_cond_signal(&_cond) == 0;
	}

#endif

	return false;
}

bool WaitableFlag::Wait(int milliseconds)
{
#if defined(CAT_OS_WINDOWS)

	if (_event == 0) return false;

	return WaitForSingleObject(_event, (milliseconds >= 0) ? milliseconds : INFINITE) != WAIT_TIMEOUT;

#else

	if (!_valid) return false;

	bool triggered = false;

	pthread_mutex_lock(&_mutex);

	if (_flag == 1)
	{
		triggered = true;
	}
	else if (milliseconds < 0)
	{
		triggered = pthread_cond_wait(&_cond, &_mutex) == 0;
	}
	else if (milliseconds > 0)
	{
		int interval_seconds = milliseconds / 1000;
		long interval_nanoseconds = (milliseconds % 1000) * 1000000;

		struct timeval tv;
		if (gettimeofday(&tv, 0) == 0)
		{
			long nsec = tv.tv_usec;

			if (nsec >= 0)
			{
				long nsec_trigger = nsec + interval_nanoseconds;

				static const long ONE_SECOND_IN_NANOSECONDS = 1000000000;

				if (nsec_trigger < nsec || nsec_trigger >= ONE_SECOND_IN_NANOSECONDS)
				{
					++interval_seconds;
					nsec_trigger -= ONE_SECOND_IN_NANOSECONDS;
				}

				struct timespec ts;
				ts.tv_sec = tv.tv_sec + interval_seconds;
				ts.tv_nsec = nsec_trigger;

				triggered = pthread_cond_timedwait(&_cond, &_mutex, &ts) != ETIMEDOUT;
			}
		}
	}

	if (triggered)
		_flag = 0;

	pthread_mutex_unlock(&_mutex);

	return triggered;

#endif
}
