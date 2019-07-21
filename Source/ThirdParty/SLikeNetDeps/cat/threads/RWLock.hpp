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

#ifndef CAT_RW_LOCK_HPP
#define CAT_RW_LOCK_HPP

#include <cat/threads/Mutex.hpp>

namespace cat {


//// RWLock

class RWLock
{
#if defined(CAT_OS_WINDOWS)
	volatile u32 _rd_count;
	volatile u32 _wr_count;
	HANDLE _rd_event;
	Mutex _wr_lock;
#else
	int init_failure;
	pthread_rwlock_t rw;
#endif

public:
	RWLock();
	~RWLock();

	void ReadLock();
	void ReadUnlock();

	void WriteLock();
	void WriteUnlock();
};


//// AutoReadLock

class AutoReadLock
{
	RWLock *_lock;

public:
	AutoReadLock(RWLock &lock);
	~AutoReadLock();

    bool Release();
};


//// AutoWriteLock

class AutoWriteLock
{
	RWLock *_lock;

public:
	AutoWriteLock(RWLock &lock);
	~AutoWriteLock();

    bool Release();
};


} // namespace cat

#endif // CAT_RW_LOCK_HPP
