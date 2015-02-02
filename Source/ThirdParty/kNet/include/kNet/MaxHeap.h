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

/** @file MaxHeap.h
	@brief The MaxHeap<T> template class. */

#include "Array.h"
#include "SortCmp.h"

namespace kNet
{

/** Used as a no-functionality structure to pass as the default template parameter to MaxHeap when no index update
    notifications are needed. You can create a custom notification structure to track handles to the elements as 
	 they move around in memory. */
template<typename T>
class EmptyLookupNotify
{
public:
	/// Called whenever an element in the MaxHeap is moved around.
	/// @param element The element that was moved around.
	/// @param newIndex The new index of the element.
	void IndexUpdated(const T &element, int newIndex)
	{
		MARK_UNUSED(element);
		MARK_UNUSED(newIndex);
	}
};

/** Implements a max heap data structure, see http://en.wikipedia.org/wiki/Binary_heap.
	MaxHeap is a (binary) heap structure that can be used as a priority queue. The PriorityCmp object
	is used to perform comparisons between elements.

	int PriorityCmp(const T &a, const T &b);
	Returns <0 if a<b and b has a bigger priority.
	Returns >0 if a>b and a has a bigger priority.
	Returns  0 if it is indifferent in which order the elements come out of the priority queue.
	Returning 0 doesn't mean that the elements need to be the same however.

	int EqualCmp(const T &a, const T &b);
	Returns 0 if the elements are equal, != 0 if not. If equal priority <=> equal elements, then you can
	use PriorityCmp as EqualCmp. */
template<typename T, typename PriorityCmp = sort::TriCmpObj<T>,
         typename EqualCmp = sort::TriCmpObj<T>, 
			typename LookupNotify = EmptyLookupNotify<T>,
			typename AllocT = StdCAlloc>
class MaxHeap
{
public:
	/// Gives access to the queue as a linear array form.
	Array<T, AllocT> data;
	PriorityCmp cmp; // The object to use in comparing the priorities of the elements.
	EqualCmp equal; // The object to use in comparing the equality of the elements.
	
	// This object is invoked whenever objects are moved around in the heap. The LookupNotify object
	// can be used to give O(1) membership search. Useful when IncreaseKey needs to be used.
	LookupNotify notify; 

	/// Gives the index of the parent of the element at index i, or 0 if i==0 (i is the root)
	static inline int ParentIndex(int i) { return (i+1)/2-1; }
	/// Gives the left child of the element at index i. Note that this will address out-of-bounds if there is no child.
	static inline int LeftChildIndex(int i) { return i*2+1; }
	/// Gives the right child of the element at index i. Note that this will address out-of-bounds if there is no child.
	static inline int RightChildIndex(int i) { return i*2+2; }

	/** MaxHeapifies one node of the heap at index i and recursively calls itself to MaxHeapify the child nodes,
	so that all child nodes also satisfy the MaxHeap property.
	@param i The index of the element to start MaxHeapifying at.
	@return True if changes (swaps) needed to be made to the heap at the given position, false otherwise. */
	bool MaxHeapify(int i);

	/// Call this after increasing the key at index i (giving a bigger priority to element at index i). 
	/// This will re-maxheapify the structure and keep it intact.
	void KeyIncreased(int i);

	/// Inserts a new value into the MaxHeap and works out the proper position for it in the queue.
	/// Running time is O(logn).
	void Insert(const T &value);

	/// Removes the item that is front of the queue. UDB if the queue is empty.
	void PopFront();

	/// Removes the item that is back of the queue. UDB if the queue is empty.
	void PopBack();

	/// Gives access to the frontmost item. UDB if the queue is empty.
	const T &Front() const { return data[0]; }

	/// Gives access to the item with lowest priority. Running time is O(logN). UDB if the queue is empty.
	const T &Back() const { return data[LowestPriorityIndex()]; }

	/// @return The index of the element with the lowest priority. UDB if queue is empty.
	int LowestPriorityIndex() const;

	/// How many elements are in the queue total.
	int Size() const { return (int)data.size(); }

	/// As the underlying data structure is an array, you can use this to preallocate space.
	void Reserve(int size) { data.reserve(size); }

	void Clear() { data.clear(); }
	/** Looks whether an item that is equal with respect to the PriorityCmp is present in the MaxHeap.
		Running time is O(n).
		@return The index of the element where the first equaling item was found, or -1 if none was found. */
	int Search(const T &value) { return Search(value, 0); }

private:
	/** Internal helper for Search to start the search at the given index in the array. */
	int Search(const T &value, int index);

};

template<typename T, typename PriorityCmp, typename EqualCmp, typename LookupNotify, typename AllocT>
bool MaxHeap<T, PriorityCmp, EqualCmp, LookupNotify, AllocT>::MaxHeapify(int i)
{
	assert(i >= 0);
	if (i >= (int)data.size())
		return false;

	bool changes = false;

	for(;;) // Eventually we will run out of children or no swap will occur.
	{
		// Get the indices to both children. Note that these might point to >= heapSize if a child is not present.
		const int l = LeftChildIndex(i);
		const int r = RightChildIndex(i);

		// Determine the largest node
		int largest = i;
		if (l < (int)data.size() && cmp(data[l], data[i]) > 0)
			largest = l;
		if (r < (int)data.size() && cmp(data[r], data[largest]) > 0)
			largest = r;

		// If i is not the largest node, switch and continue to MaxHeapify the child node.
		if (largest != i)
		{
			std::swap(data[largest], data[i]);
			notify.IndexUpdated(data[largest], largest);
			notify.IndexUpdated(data[i], i);
			i = largest;
			changes = true;
		}
		else
			return changes; // Return whether changes were made to heap.
	}
}

template<typename T, typename PriorityCmp, typename EqualCmp, typename LookupNotify, typename AllocT>
void MaxHeap<T, PriorityCmp, EqualCmp, LookupNotify, AllocT>::Insert(const T &value)
{
	// New element is added to the end of the array.
	data.push_back(value);
	notify.IndexUpdated(data.back(), (int)data.size()-1);
	// We need to fix the heap by MaxHeapifying all the way to the top.
	KeyIncreased((int)data.size()-1);
}

template<typename T, typename PriorityCmp, typename EqualCmp, typename LookupNotify, typename AllocT>
void MaxHeap<T, PriorityCmp, EqualCmp, LookupNotify, AllocT>::KeyIncreased(int i)
{
	// We need to fix the heap by MaxHeapifying all the way to the top.
	bool changesMade = true;
	while(changesMade && i != 0)
	{
		i = ParentIndex(i);
		changesMade = MaxHeapify(i);
	}
}

template<typename T, typename PriorityCmp, typename EqualCmp, typename LookupNotify, typename AllocT>
void MaxHeap<T, PriorityCmp, EqualCmp, LookupNotify, AllocT>::PopFront()
{
	std::swap(data[0], data[(int)data.size()-1]);
	data.pop_back();
	MaxHeapify(0);
}

template<typename T, typename PriorityCmp, typename EqualCmp, typename LookupNotify, typename AllocT>
void MaxHeap<T, PriorityCmp, EqualCmp, LookupNotify, AllocT>::PopBack()
{
	int i = LowestPriorityIndex();
	std::swap(data[i], data[data.size()-1]);
	data.pop_back();
	KeyIncreased(i);
}

template<typename T, typename PriorityCmp, typename EqualCmp, typename LookupNotify, typename AllocT>
int MaxHeap<T, PriorityCmp, EqualCmp, LookupNotify, AllocT>::LowestPriorityIndex() const
{
	int i = data.size();
	int lowestIndex = data.size()-1;
	do
	{
		--i;
		if (cmp(data[i], data[lowestIndex]) < 0)
			lowestIndex = i;
	} while((i & (i-1)) != 0);

	return lowestIndex;
}

template<typename T, typename PriorityCmp, typename EqualCmp, typename LookupNotify, typename AllocT>
int MaxHeap<T, PriorityCmp, EqualCmp, LookupNotify, AllocT>::Search(const T &value, int index)
{
	assert(index >= 0);
	if (index >= (int)data.size())
		return -1;

	int order = cmp(value, data[index]);
	if (order == 0 && equal(value, data[index]) == 0)
		return index;
	if (order > 0) // The element at data[index] < value, and all the children are also smaller, so
		return -1;  // there is no chance of finding the element.

	// case order < 0:
	int child = LeftChildIndex(index);
	assert(child >= 0);
	if (child >= (int)data.size()) // No left child, so no right child either, return not found.
		return -1;

	int result = Search(value, child);
	if (result != -1) // found on the left branch?
		return result;

	child = RightChildIndex(index);
	assert(child >= 0);
	if (child < (int)data.size()) // If right child exists, search there too.
		return Search(value, child);
	else
		return -1;
}

} // ~kNet

