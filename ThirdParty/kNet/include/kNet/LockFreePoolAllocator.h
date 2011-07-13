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

/** @file LockFreePoolAllocator.h
	@brief The PoolAllocatable<T> and LockFreePoolAllocator<T> template classes. */

#include <iostream>
#include "Atomics.h"

namespace kNet
{

template<typename T>
struct PoolAllocatable
{
	/// Points to the next item in the lock-free linked list. Do not access or 
	/// dereference this variable in client code, as it is used internally by
	/// LockFreePoolAllocator only.
	T * volatile next;
};

/// T must implement PoolAllocatable.
template<typename T>
class LockFreePoolAllocator
{
public:
	LockFreePoolAllocator()
	:root(0)
	{
	}

	~LockFreePoolAllocator()
	{
		UnsafeClearAll();
	}

	/// Allocates a new object of type T. Call Free() to deallocate the object.
	T *New()
	{
		// Currently the use of lockfree allocation pool is disabled, since it has a known race condition, documented below.
		return new T();

		/*
		for(;;)
		{
			T *allocated = root;
			if (!allocated) // If the root is null, there are no objects in the pool, so we must create new from the runtime heap.
			{
				allocated = new T();
				allocated->next = 0;
				return allocated;
			}

			///\bug Note that this function is not thread-safe. Accessing allocated->next may already be dangling if another thread has deleted it.
			T *newRoot = allocated->next;

			if (CmpXChgPointer((void**)&root, newRoot, allocated))
			{
				allocated->next = 0;
				return allocated;
			}
		}
		*/
	}

	void Free(T *ptr)
	{
		delete ptr;

		// Currently the use of lockfree allocation pool is disabled, since it has a known race condition.
/*
		if (!ptr)
			return;

		assert(ptr != root);

		for(;;)
		{
			ptr->next = root;
			if (CmpXChgPointer((void**)&root, ptr, ptr->next))
				return;
		}
*/
	}

	/// Deallocates all cached unused nodes in this pool. Thread-safe and lock-free. If you are manually tearing
	/// down the pool and there are no other threads accessing this, you may call the even faster version
	/// UnsafeClearAll(), which ignores compare-and-swap updates.
	void ClearAll()
	{
		while(root)
		{
			T *node = New();
			delete node;
		}
	}

	/// A fast method to free all items allocated in the pool.
	/// Not thread-safe, only call when you can guarantee there are no threads calling New() or Free().
	void UnsafeClearAll()
	{
		assert(!DebugHasCycle());
		T *node = root;
		while(node)
		{
			T *next = node->next;
			delete node;
			node = next;
		}
		root = 0;
	}

	/// A debugging function that checks whether the underlying linked list has a cycle or not. Not thread-safe!
	bool DebugHasCycle()
	{
		T *n1 = root;
		if (!n1)
			return false;
		T *n2 = n1->next;
		while(n2 != 0)
		{
			if (n1 == n2)
				return true;

			n1 = n1->next;
			n2 = n2->next;
			if (n2)
				n2 = n2->next;
		}
		return false;
	}

	/// A debugging function that prints out all the objects in the pool. Not thread-safe!
	void DumpPool()
	{
		using namespace std;

		T *node = root;
		cout << "Root: 0x" << ios::hex << root << ".Next: " << ios::hex << (root ? root->next : 0) << std::endl;
		int size = 0;
		if (node)
			node = node->next;
		while(node)
		{
			cout << "Node: 0x" << ios::hex << node << ".Next: " << ios::hex << (node ? node->next : 0) << std::endl;
			node = node->next;
			++size;
		}
		cout << "Total: " << size << " elements." << endl;
	}

private:
	T * volatile root;
};

} // ~kNet
