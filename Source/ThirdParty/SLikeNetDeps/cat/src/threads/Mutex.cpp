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

#include <cat/threads/Mutex.hpp>
using namespace cat;


//// Mutex

Mutex::Mutex()
{
#if defined(CAT_OS_WINDOWS)

	InitializeCriticalSection(&cs);

#else

	init_failure = pthread_mutex_init(&mx, 0);

#endif
}

Mutex::~Mutex()
{
#if defined(CAT_OS_WINDOWS)

	DeleteCriticalSection(&cs);

#else

	if (!init_failure) pthread_mutex_destroy(&mx);

#endif
}

bool Mutex::Valid()
{
#if defined(CAT_OS_WINDOWS)

	return true; // No failure state for critical sections

#else

	return init_failure == 0;

#endif
}

bool Mutex::Enter()
{
#if defined(CAT_OS_WINDOWS)

	CAT_FENCE_COMPILER

	EnterCriticalSection(&cs);

	CAT_FENCE_COMPILER

	return true;

#else

	if (init_failure) return false;

	CAT_FENCE_COMPILER

	bool result = pthread_mutex_lock(&mx) == 0;

	CAT_FENCE_COMPILER

	return result;

#endif
}

bool Mutex::Leave()
{
#if defined(CAT_OS_WINDOWS)

	CAT_FENCE_COMPILER

	LeaveCriticalSection(&cs);

	CAT_FENCE_COMPILER

	return true;

#else

	if (init_failure) return false;

	CAT_FENCE_COMPILER

	bool result = pthread_mutex_unlock(&mx) == 0;

	CAT_FENCE_COMPILER

	return result;

#endif
}


//// AutoMutex

AutoMutex::AutoMutex(Mutex &mutex)
{
    _mutex = &mutex;
    mutex.Enter();
}

AutoMutex::~AutoMutex()
{
    Release();
}

bool AutoMutex::Release()
{
	bool success = false;

    if (_mutex)
    {
        success = _mutex->Leave();
        _mutex = 0;
    }

	return success;
}
