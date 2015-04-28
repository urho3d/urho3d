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

/** @file WaitFreeQueue.h
	@brief The WaitFreeQueue<T> template class. */

#include <stddef.h>
#include "Alignment.h"

namespace kNet
{

/// A wait-free queue for communication unidirectionally between two threads.
/** This data structure is useful for simple and efficient lockless data/message passing between two-threads.
	It is implemented using a lockless circular ring buffer, and has the following properties:
	 - At most one thread can act as a publisher/producer/writer and call Insert() to add new items to the queue.
	 - At most one thread can consume/read the items from the queue by calling Front() and PopFront().
	 - Does not use locks or spin-waits, and is hence wait-free.
	 - Does not perform any memory allocation after initialization.
	 - Only POD types are supported. If you need non-POD objects, store pointers to objects instead.
	 - The queue has a fixed upper size that must be a power-of-2 and must be speficied in the constructor. */
template<typename T>
class WaitFreeQueue
{
public:
	/// @param maxElements A power-of-2 number, > 2,  that specifies the size of the ring buffer to construct. The number of elements the queue can store is maxElements-1.
	explicit WaitFreeQueue(size_t maxElements)
	:head(0), tail(0)
	{
		assert(IS_POW2(maxElements)); // The caller really needs to round to correct pow2,
		assert(maxElements > 2);
		maxElements = (size_t)RoundUpToNextPow2((u32)maxElements); // but avoid any silliness in release anyways.

		data = new T[maxElements];
		maxElementsMask = (unsigned long)maxElements - 1;
	}

	/// Warning: This is not thread-safe.
	WaitFreeQueue(const WaitFreeQueue &rhs)
	:maxElementsMask(rhs.maxElementsMask), head(rhs.head), tail(rhs.tail)
	{
		size_t maxElements = rhs.maxElementsMask+1;
		data = new T[maxElements];
		for(size_t i = 0; i < maxElements; ++i)
			data[i] = rhs.data[i];
	}

	/// Warning: This is not thread-safe.
	WaitFreeQueue &operator =(const WaitFreeQueue &rhs)
	{
		if (this == &rhs)
			return *this;

		head = rhs.head;
		tail = rhs.tail;
		size_t maxElements = rhs.maxElementsMask+1;
		maxElementsMask = rhs.maxElementsMask;

		delete[] data;
		data = new T[maxElements];
		for(size_t i = 0; i < maxElements; ++i)
			data[i] = rhs.data[i];

		return *this;
	}

	~WaitFreeQueue()
	{
		delete[] data;
	}

	/// Returns the total capacity of the queue, i.e. the total maximum number of items that can be contained in it.
	/// Thread-safe.
	int Capacity() const { return maxElementsMask; }

	/// Returns the number of items that can still be inserted in the queue, i.e. the total space left.
	/// Thread-safe.
	int CapacityLeft() const { return Capacity() - Size(); }

	/// Starts a new item insert operation.
	/// This function returns a pointer to the next element to be added to this queue.
	/// You can fill there the next value to add, and call FinishInsert() when done. The consumer
	/// will not see the object in the queue before FinishInsert() is called.
	/// Use Begin/FinishInsert when the type T has a heavy copy-ctor to avoid generating a temporary.
	/// \note Do not call BeginInsert() several times before calling FinishInsert() in between. You can
	///       have only one outstanding BeginInsert() call active at a time (multiple consecutive BeginInsert()
	///       calls will keep returning the same pointer until FinishInsert() is called)
	/// @return A pointer where to fill the next value to produce to the queue, or 0 if the queue is full
	///       and no value can be added. For each returned pointer, call FinishInsert after filling the value 
	///       to commit it to the queue. If 0 is returned, FinishInsert does not need to be called.
	///  This function can be called only by a single producer thread.
	T *BeginInsert()
	{
		unsigned long tail_ = tail;
		unsigned long nextTail = (tail_ + 1) & maxElementsMask;
		if (nextTail == head)
			return 0;
		return &data[tail];
	}

	/// Commits to the end of the queue the item filled with a previous call to BeginInsert.
	///  This function can be called only by a single producer thread.
	void FinishInsert()
	{
		unsigned long tail_ = tail;
		unsigned long nextTail = (tail_ + 1) & maxElementsMask;
		assert(nextTail != head && "Error: Calling FinishInsert after BeginInsert failed, or was not even called!");
		tail = nextTail;
	}

	/// Inserts the new value into the queue. Can be called only by a single producer thread.
	bool Insert(const T &value)
	{
		// Inserts are made to the 'tail' of the queue, incrementing the tail index.
		unsigned long tail_ = tail;
		unsigned long nextTail = (tail_ + 1) & maxElementsMask;
		if (nextTail == head)
			return false;
		data[tail_] = value;
		tail = nextTail;

		return true;
	}

	/// Inserts the new value into the queue. If there is not enough free space in the queue, the capacity
	/// of the queue is doubled.
	/// \note This function is not thread-safe. Do not call this if you cannot guarantee that the other
	///       thread will not be accessing the queue at the same time.
	void InsertWithResize(const T &value)
	{
		bool success = Insert(value);
		if (!success)
		{
			DoubleCapacity();
#ifdef _DEBUG
			success = 
#endif
				Insert(value);
		}
#ifdef _DEBUG
		assert(success);
#endif
	}

	/// Re-allocates the queue to the new maximum size. All old elements are copied over.
	/// \note This function is not thread-safe. Do not call this if you cannot guarantee that the other
	///       thread will not be accessing the queue at the same time.
	void Resize(size_t newSize)
	{
		assert(IS_POW2(newSize)); // The caller really needs to round to correct pow2,
		newSize = (size_t)RoundUpToNextPow2((u32)newSize); // but avoid any silliness in release anyways.

		T *newData = new T[newSize];
		unsigned long newTail = 0;
		for(int i = 0; i < Size(); ++i)
			newData[newTail++] = *ItemAt(i);
		delete[] data;
		data = newData;
		head = 0;
		tail = newTail;
		maxElementsMask = (unsigned long)newSize - 1;
	}

	/// Resizes this queue to hold twice the amount of maximum elements.
	/// \note This function is not thread-safe. Do not call this if you cannot guarantee that the other
	///       thread will not be accessing the queue at the same time.
	void DoubleCapacity() { Resize(2*(maxElementsMask+1)); }

	/// Returns a pointer to the first item in the queue (the item that is coming off next, i.e. the one that has
	/// been in the queue the longest). Can be called only from a single consumer thread.
	/// This function can safely be called even if the queue is empty, in which case 0 is returned.
	T *Front()
	{
		if (head == tail)
			return 0;
		return &data[head];
	}

	/// Returns a pointer to the first item in the queue (the item that is coming off next, i.e. the one that has
	/// been in the queue the longest). Can be called only from a single consumer thread.
	/// This function can safely be called even if the queue is empty, in which case 0 is returned.
	const T *Front() const
	{
		if (head == tail)
			return 0;
		return &data[head];
	}

	/// Returns a copy of the first item in the queue and pops that item off the queue. Can be called only from a single consumer thread.
	/// Requires that there exists an element in the queue.
	T TakeFront()
	{
		assert(Front());
		T frontVal = *Front();
		PopFront();
		return frontVal;
	}

	/// Returns a pointer to the last item (the item that was just added) in the queue.
	/// Can be called only from a single consumer thread.
	T *Back()
	{
		if (head == tail)
			return 0;
		return &data[(tail + maxElementsMask) & maxElementsMask];
	}

	/// Returns a pointer to the last item (the item that was just added) in the queue.
	/// Can be called only from a single consumer thread.
	const T *Back() const
	{
		if (head == tail)
			return 0;
		return &data[(tail + maxElementsMask) & maxElementsMask];
	}

	/// Returns a pointer to the item at the given index. ItemAt(0) will return the first item (the front item)
	/// in the queue. Can be called only from a single consumer thread.
	/// Never returns a null pointer.
	T *ItemAt(int index)
	{
		assert(index >= 0 && index < (int)Size());
		return &data[(head + index) & maxElementsMask];
	}

	/// Returns a pointer to the item at the given index. Can be called only from a single consumer thread.
	/// Never returns a null pointer.
	const T *ItemAt(int index) const
	{
		assert(index >= 0 && index < (int)Size());
		return &data[(head + index) & maxElementsMask];
	}

	/// Returns true if the given element exists in the queue. Can be called only from a single consumer thread.
	bool Contains(const T &item) const
	{
		for(int i = 0; i < (int)Size(); ++i)
			if (*ItemAt(i) == item)
				return true;
		return false;
	}

	/// Removes the element at the given index.
	///\note Not thread-safe.
	void EraseItemAt(int index)
	{
		if (index <= Size()>>1)
			EraseItemAtMoveFront(index);
		else
			EraseItemAtMoveBack(index);
	}

	/// Removes all elements in the queue. Does not call dtors for removed objects, as this queue is only for POD types.
	/// Can be called only from a single consumer thread.
	void Clear()
	{
		tail = head;
	}

	/// Returns the number of elements currently filled in the queue. Can be called from either the consumer or producer thread.
	int Size() const
	{
		unsigned long head_ = head;
		unsigned long tail_ = tail;
		if (tail_ >= head_)
			return tail_ - head_;
		else
			return maxElementsMask + 1 - (head_ - tail_);
	}

	/// Removes the first item in the queue. Can be called only from a single consumer thread.
	void PopFront()
	{
		assert(head != tail);
		if (head == tail)
			return;
		size_t head_ = (head + 1) & maxElementsMask;
		head = (unsigned long)head_;
	}

private:
	T *data;
	/// Stores the AND mask (2^Size-1) used to perform the modulo check.
	unsigned long maxElementsMask;
	/// Stores the index of the first element in the queue. The next item to come off the queue is at this position,
	/// unless head==tail, and the queue is empty. \todo Convert to C++0x atomic<unsigned long> head;
	volatile unsigned long head;
	/// Stores the index of one past the last element in the queue. \todo Convert to C++0x atomic<unsigned long> head;
	volatile unsigned long tail; 

	/// Removes the element at the given index, but instead of filling the contiguous gap that forms by moving elements to the
	/// right, this function will instead move items at the front of the queue.
	///\note Not thread-safe.
	void EraseItemAtMoveFront(int index)
	{
		assert(Size() > 0);
		int numItemsToMove = index;
		for(int i = 0; i < numItemsToMove; ++i)
			data[(head+index + maxElementsMask+1 -i)&maxElementsMask] = data[(head+index + maxElementsMask+1 -i-1) &maxElementsMask];
		head = (head+1) & maxElementsMask;
	}

	/// Removes the element at the given index, and fills the contiguous gap that forms by shuffling each item after index one space down.
	///\note Not thread-safe.
	void EraseItemAtMoveBack(int index)
	{
		assert(Size() > 0);
		int numItemsToMove = Size()-1-index;
		for(int i = 0; i < numItemsToMove; ++i)
			data[(head+index+i)&maxElementsMask] = data[(head+index+i+1)&maxElementsMask];
		tail = (tail + maxElementsMask+1 - 1) & maxElementsMask;
	}
};

/// Checks that the specified conditions for the container apply.
/// Warning: This is a non-threadsafe check for the container, only to be used for debugging.
/// Warning #2: This function is very slow, as it performs a N^2 search through the container.
template<typename T>
bool ContainerUniqueAndNoNullElements(const WaitFreeQueue<T> &cont)
{
	for(size_t i = 0; i < cont.Size(); ++i)
		for(size_t j = i+1; j < cont.Size(); ++j)
			if (*cont.ItemAt(i) == *cont.ItemAt(j) || *cont.ItemAt(i) == 0)
				return false;
	return true;
}

} // ~kNet
