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

/** @file Allocator.h
	@brief Provides global memory allocation routines using instance-based allocators.

	All allocators in the system are instance-based (in contrast to class-based). 
	This implies a few things:
		1. Because all memory allocation is performed through allocators, you need to create an allocator 
		   instance to be able to allocate memory.
		2. Each container will have a pointer to the allocator instance it's using.
		3. There are no general global (static/class-based/compile time -based) memory allocators.

	See http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2005/n1850.pdf for loosely related discussion
	(mainly class-based vs instance-based allocator system). An allocator must support the following concept:
	
	class Allocator
	{
	public:
		static void *Alloc(Allocator *instance, size_t size, size_t alignment, const char *nameTag = 0, AllocFlags flags = AFAllocLow);
		static void Free(Allocator *instance, void *ptr);
		static size_t Size(Allocator *instance, void *ptr);
	};

	The reason that the member functions are static, but still take in as the first parameter an instance of the Allocator
	is that this allows both class-based and instance-based allocators to be created using the same interface. */

#include "Types.h"

namespace kNet
{

typedef u32 AllocFlags;
enum
{
	AFAllocLow  = 0x1, ///< Allocate from the low end of the memory space (if applicable for the given Allocator). Default.
	AFAllocHigh = 0x2 ///< Allocate from the high end of the memory space (if supported).
};

/** The global memory/object allocation function. Allocates sizeof(Object) bytes of memory using the allocator
	and uses placement new to construct an object of type Object to that memory area. (calls the ctor of Object).
	@param allocator The allocator object to allocate data from. Null may be passed in if the Allocator type
		is a class-based allocator.
	@return A pointer to the allocated object or 0 if failed.
	\todo Currently bad_alloc exceptions are not meant to be supported (although they can occur). Define this
		behavior more precisely? */
template<typename Object, typename Allocator>
inline Object *New(Allocator *allocator, size_t alignment, const char *nameTag = 0, AllocFlags flags = AFAllocLow)
{
	void *mem = Allocator::Alloc(allocator, sizeof(Object), alignment, nameTag);
	return new(mem) Object;
}

/** Allocates an array of objects. Calls default ctors for each.
	@param allocator The allocator object to allocate data from. Null may be passed in if the Allocator type
		is a class-based allocator.
	\todo The 4 bytes of size data are unnecessary for PODs! */
template<typename Object, typename Allocator>
inline Object *NewArray(size_t numObjects, Allocator *allocator, size_t alignment, const char *nameTag = 0,
								AllocFlags flags = AFAllocLow)
{
	unsigned long extraSize = sizeof(size_t);

	///\todo Proper alignment.
	void *ptr = Allocator::Alloc(allocator, sizeof(Object)*numObjects + extraSize, alignment, nameTag, flags);
	*reinterpret_cast<size_t*>(ptr) = numObjects;

	Object *mem = reinterpret_cast<Object*>(reinterpret_cast<size_t*>(ptr)+1);
	for(size_t i = 0; i < numObjects; ++i)
		new (&mem[i]) Object;

	return mem;
}

/** Object deletion function. Destroys the given object (calls dtor) and returns the used memory back to the
	allocator. 
	@param allocator The allocator object to allocate data from. Null may be passed in if the Allocator type
		is a class-based allocator. */
template<typename Object, typename Allocator>
inline void Delete(Object *ptr, Allocator *allocator)
{
	if (!ptr)
		return;

	ptr->~Object();
	Allocator::Free(allocator, ptr);
}

/** Array of objects deletion function. Destroys all objects (calls dtors for each) and returns the used memory
	back to the allocator.
	@param allocator The allocator object to allocate data from. Null may be passed in if the Allocator type
		is a class-based allocator. */
template<typename Object, typename Allocator>
inline void DeleteArray(Object *ptr, Allocator *allocator)
{
	if (!ptr)
		return;

	size_t numObjects = *(reinterpret_cast<size_t*>(ptr)-1);
	if (numObjects == 0)
		return;

	// The standard mandates that we need to tear down the objects in the reverse order they were allocated in.
	for(size_t i = numObjects; i > 0; --i)
		ptr[i-1].~Object();

	Allocator::Free(allocator, reinterpret_cast<size_t*>(ptr)-1);
}

} // ~kNet
