/* Copyright 2010 Jukka Jylänki

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

/** @file StdCMallocHeap.h
	@brief Implements the allocator object for allocating memory using malloc and free. */

#include <cstdlib>
#include <cassert>

#include "Allocator.h"
#include "Alignment.h"

namespace kNet
{
/** Allocates raw memory using the std C malloc and free. Note that the free/used -block tracking
	is left at the burden of the stdlib implementation, so don't rely on this allocator in performance
	critical sections. */
class StdCAlloc
{
public:
//	StdCAlloc(){}
//	StdCAlloc(const StdCAlloc &);
//	~StdCAlloc() {}

	static inline void *Alloc(StdCAlloc *, size_t size, size_t alignment, const char * /*nameTag*/ = 0, AllocFlags /*flags*/ = AFAllocLow)
	{
		assert(IS_POW2(alignment));
#ifdef WIN32
		void *ptr = _aligned_malloc(size, alignment);
#else
		void *ptr = malloc(size); ///\todo aligned_malloc on unix?
#endif
		return ptr;
	}
	static inline void Free(StdCAlloc *, void *ptr)
	{
#ifdef WIN32
		_aligned_free(ptr);
#else
		free(ptr);
#endif
	}

	///\todo Perhaps support Resize(void *ptr, size_t newSize); ?
	static inline size_t Size(StdCAlloc *, void *ptr)
	{
#ifdef WIN32
		return ::_msize(ptr);
#else
		assert(false && "N/I");
		return 0;
#endif
	}
};

} // ~kNet
