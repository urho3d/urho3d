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

/** @file Sort.inl
	@brief Implementations of template functions for sorting algorithms. */

#ifdef __GNUC__
/// If a variable or a function definition is labelled with this directive, the compiler should not emit a warning even if it is unused
/// in the code.
#define DONT_WARN_UNUSED __attribute__((unused))
#else
#define DONT_WARN_UNUSED
#endif

#include <utility>

namespace kNet
{
namespace sort
{

template<typename T, typename CmpFunc>
void SelectionSort(T *list, int numItems, CmpFunc &cmp)
{
	assert(numItems >= 0);
	assert(list);

	for(int i = 0; i < numItems-1; i++)
	{
		// find the smallest element of subarray A[i+1] -> A[numItems-1]
		T *smallest = &list[i+1];
		for(int j = i+2; j < numItems; j++)
			if (cmp(list[j], *smallest) < 0)
				smallest = &list[j];
			
		// exchange the smallest & current element
		if (cmp(*smallest, list[i]) < 0)
			std::swap(list[i], *smallest);
	}
}

template<typename T, typename CmpFunc>
void PartialSelectionSort(T *list, int numItems, int numItemsToSort, CmpFunc &cmp)
{
	assert(numItems >= 0);
	assert(numItemsToSort >= 0);
	assert(list);

	if (numItemsToSort > numItems-1)
		numItemsToSort = numItems-1;

	for(int i = 0; i < numItemsToSort; i++)
	{
		// find the smallest element of subarray A[i+1] -> A[numItems-1]
		T *smallest = &list[i+1];
		for(int j = i+2; j < numItems; j++)
			if (cmp(list[j], *smallest) < 0)
				smallest = &list[j];
			
		// exchange the smallest & current element
		if (cmp(*smallest, list[i]) < 0)
			std::swap(list[i], *smallest);
	}
}

template<typename T, typename CmpFunc>
void InsertionSort(T *list, int numItems, CmpFunc &cmp)
{
	assert(numItems >= 0);
	assert(list);

	// The subarray [0, j[ is always in sorted order.
	for(int j = 1; j < numItems; j++)
	{
		const T item = list[j];
		int i = j-1;
		while(i >= 0 && cmp(list[i], item) > 0)
		{
			list[i+1] = list[i];
			i--;
		}
		list[i+1] = item;
	}
}

namespace
{

/// Used by merge sort. This algorithm merges two subarrays into a larger, sorted array.
template<typename T, typename CmpFunc>
void MergeSubSet(T *list, int first, int split, int last, T *tempArray, CmpFunc &cmp)
{
	assert(first >= 0);
	assert(split >= 0);
	assert(last >= 0);
	assert(list);
	assert(tempArray);

	if (first > split || split >= last)
		return;
		
	// create two subarrays:
	// left: array[first] -> array[split] 		size: split-first+1
	// right: array[split+1] -> array[last]	size: last-split
	// the item array[split] goes to left subarray
	
	// create left
	int sLeft = split-first+1;
	T *left = tempArray;
	for(int i = 0; i < sLeft; i++)
		left[i] = list[first+i];
		
	// create right
	int sRight = last-split;
	T *right = &tempArray[sLeft];
	for(int i = 0; i < sRight; i++)
		right[i] = list[split+1+i];
		
	// left & right are assumed to be sorted subarrays,
	// use the original array as destination
	int iLeft = 0;
	int iRight = 0;
	int idx = first;
	for(; idx <= last && iLeft < sLeft && iRight < sRight; idx++)
		if (cmp(left[iLeft], right[iRight]) < 0)
			list[idx] = left[iLeft++];
		else
			list[idx] = right[iRight++];
	
	// the for-loop ended, copy the remaining pile to array
	for(; iLeft < sLeft; iLeft++)
		list[idx++] = left[iLeft];
	for(; iRight < sRight; iRight++)
		list[idx++] = right[iRight];
}

// Used by merge sort
template<typename T, typename CmpFunc>
void MergeSort(T *list, int first, int last, T *temp, CmpFunc &cmp)
{
	assert(first >= 0);
	assert(last >= 0);
	assert(list);
	assert(temp);

	if (first >= last)
		return;
		
	int half = (first+last)/2;
	MergeSort(list, first, half, temp, cmp);
	MergeSort(list, half+1, last, temp, cmp);
	MergeSubSet(list, first, half, last, temp, cmp);
}

}

template<typename T, typename CmpFunc>
void MergeSort(T *list, int numItems, CmpFunc &cmp)
{
	assert(numItems >= 0);
	assert(list);

	T *tempArray = new T[numItems];
	MergeSort(list, 0, numItems-1, tempArray, cmp);
	delete[] tempArray;
}

namespace
{

template<typename T, typename CmpFunc>
void GapInsertSort(T *list, int gapSize, int numItems, CmpFunc &cmp)
{
	assert(numItems >= 0);
	assert(list);

	assert(gapSize >= 1);
	for(int j = gapSize; j < numItems; j++)
	{
		const T item = list[j];
		int i = j - gapSize;
		while(i >= 0 && cmp(list[i], item) > 0)
		{
			list[i + gapSize] = list[i];
			i -= gapSize;
		}
		list[i + gapSize] = item;
	}
}

} // ~unnamed namespace

template<typename T, typename CmpFunc>
void ShellSort(T *list, int numItems, CmpFunc &cmp)
{
	assert(numItems >= 0);
	assert(list);

	// The increments to use for gap insertion sort.
	// http://www.research.att.com/~njas/sequences/A102549
	static const int gaps[] = { 1, 4, 10, 23, 57, 132, 301, 701 };

	for(int i = sizeof(gaps)/sizeof(gaps[0]) - 1; i >= 0; --i)
		GapInsertSort(list, gaps[i], numItems, cmp);
}

/** On the development computer overflows the stack if numItems is larger than ~57000
	and the list is already sorted. */
template<typename T, typename CmpFunc>
void QuickSort(T *list, int numItems, CmpFunc &cmp)
{
	assert(numItems >= 0);
	assert(list);

	if (numItems <= 1)
		return;

	// Select the middle item as pivot. (In a nearly sorted list, this is as near of the 
	// median value as we can get) The pivot is stored at the back of the array.
	std::swap(list[numItems-1], list[numItems/2]);
	const T &pivotValue = list[numItems-1];

	// Do the actual pivotizing.
	int rEnd = 0;
	for(int i = 0; i < numItems-1; i++)
		if (cmp(list[i], pivotValue) < 0)
			std::swap(list[rEnd++], list[i]);

	// Put the pivot value to the center of the array
	std::swap(list[rEnd], list[numItems-1]);

	// sort left & right
	if (rEnd > 1) // if left side has more than one item, sort it.
		QuickSort(list, rEnd, cmp);
	if (numItems-rEnd>2) // if right side has more than one item, sort it.
		QuickSort(&list[rEnd+1], numItems-rEnd-1, cmp);
}

template<typename T, typename CmpFunc>
void BubbleSort(T *list, int numItems, CmpFunc &cmp)
{
	assert(numItems >= 0);
	assert(list);

	int inOrderIndex = numItems; // Denotes the subarray that is already sorted, i.e. [inOrderIndex, numItems[.
	while(inOrderIndex > 0)
	{
		int largestSwapped = 0; // Track the largest index that was changed. To early-out the outer loop.
		for(int j = 1; j < inOrderIndex; ++j)
			if (cmp(list[j-1], list[j]) > 0)
			{
				std::swap(list[j-1], list[j]);
				largestSwapped = j;
			}
		inOrderIndex = largestSwapped;
	}
}

template<typename T, typename CmpFunc>
void CombSort(T *list, int numItems, CmpFunc &cmp)
{
	assert(numItems >= 0);
	assert(list);

	int gap = numItems;
	bool bSwitches = false;

	do
	{
		bSwitches = false;

		// Reduce the gap by dividing by 1/(1-1/e^phi)
		gap = (int)(gap / 1.24733095f);
		if (gap == 10 || gap == 9)	// gap size 11 is superior to 10 or 9, use that instead.
			gap = 11;
		else if (gap < 1)	// the last iteration needs to be with gap=1 (bubblesort)
			gap = 1;

		for(int i = 0; i < numItems-gap; i++)
			if (cmp(list[i+gap], list[i]) < 0)
			{
				std::swap(list[i+gap], list[i]);
				bSwitches = true;
			}
	} while(gap > 1 || bSwitches);
}

/** Works by alternating the bubble directions in bubble sort. */
template<typename T, typename CmpFunc>
void CocktailSort(T *list, int numItems, CmpFunc &cmp)
{
	assert(numItems >= 0);
	assert(list);

	int bottomSorted = 0; // Number of items in the low end that are already sorted. (Index of first unsorted)
	int topSorted = numItems; // Index of the first sorted item in the high end.
	while(bottomSorted+1 < topSorted) // The outer loop, condition for early-outing
	{
		// Tracks the index that was last modified, in order to prune a few elements in the bubbling process.
		int lastSwapped = bottomSorted; 
		for(int i = bottomSorted+1; i < topSorted; ++i) // Rising pass
			if (cmp(list[i-1], list[i]) > 0)
			{
				std::swap(list[i-1], list[i]);
				lastSwapped = i;
			}
		topSorted = lastSwapped;

		// We reuse the value that was left in lastSwapped here to remember the last index that was swapped.
		// (Allows early-out)
		for(int i = topSorted-1; i > bottomSorted; --i) // Falling pass
			if (cmp(list[i-1], list[i]) > 0)
			{
				std::swap(list[i-1], list[i]);
				lastSwapped = i;
			}
		bottomSorted = lastSwapped;
	}
}

namespace
{
/// Gives the index of the parent of the element at index i, or 0 if i==0 (i is the root)
inline int DONT_WARN_UNUSED HeapParent(int i) { return (i+1)/2-1; }
/// Gives the left child of the element at index i. Note that this will address out-of-bounds if there is no child.
inline int DONT_WARN_UNUSED HeapLeftChild(int i) { return i*2+1; }
/// Gives the right child of the element at index i. Note that this will address out-of-bounds if there is no child.
inline int DONT_WARN_UNUSED HeapRightChild(int i) { return i*2+2; }

/** MaxHeapifies one node of the heap at index i and recursively calls itself to MaxHeapify the child nodes,
	so that all child nodes also satisfy the MaxHeap property.
	@param list An array that represents the (binary) heap.
	@param heapSize The number of elements in the heap.
	@param i The index of the element to start MaxHeapifying at.
	@param cmp A function that compares the priorities of two elements. See above.
	@return True if changes (swaps) needed to be made to the heap at the given position, false otherwise. */
template<typename T, typename PriorityCmp>
bool MaxHeapify(T *heap, int heapSize, int i, PriorityCmp &cmp)
{
	assert(heapSize >= 0);
	assert(i >= 0);
	assert(heap);

	// Get the indices to both children. Note that these might point to >= heapSize if a child is not present.
	const int l = HeapLeftChild(i);
	const int r = HeapRightChild(i);

	// Determine the largest node
	int largest = i;
	if (l < heapSize && cmp(heap[l], heap[i]) > 0)
		largest = l;
	if (r < heapSize && cmp(heap[r], heap[largest]) > 0)
		largest = r;

	// If i is not the largest node, switch and MaxHeapify the child node.
	if (largest != i)
	{
		std::swap(heap[largest], heap[i]);
		MaxHeapify(heap, heapSize, largest, cmp);
		return true; // Changes were made to heap.
	}
	return false; // No changes were made to heap.
}

/** Takes an array of items and builds it into a MaxHeap, i.e. swaps elements around so that the ordering
	satisfies the MaxHeap property. Building a MaxHeap from an array that is in random order takes O(n) steps.
	(If we do it bottom-up by pushing elements upwards like here. Takes a lot more if we would go top-down).
	@param list An array that represents a (binary) heap.
	@param heapSize The number of items in the array.
	@param cmp The comparison function to use for the elements. */
template<typename T, typename PriorityCmp>
void BuildMaxHeap(T *list, int heapSize, PriorityCmp &cmp)
{
	assert(heapSize >= 0);
	assert(list);

	// MaxHeapify the whole heap by starting from the lowest non-leaf node and go our way up.
	for(int i = (heapSize-1)/2; i >= 0; i--)
		MaxHeapify(list, heapSize, i, cmp);
}
} // ~unnamed namespace

template<typename T, typename CmpFunc>
void HeapSort(T *list, int numItems, CmpFunc &cmp)
{
	assert(numItems >= 0);
	assert(list);

	BuildMaxHeap(list, numItems, cmp);
	// At every iteration, we have the largest item in list[0], switch it to the back of the
	// list and remove the swapped item from the heap. Then re-MaxHeapify and repeat.
	for(int i = numItems-1; i > 0; i--)
	{
		std::swap(list[0], list[i]);
		MaxHeapify(list, i, 0, cmp);
	}
}

template<typename T, typename CmpFunc>
void IntroSort(T *list, int numItems, int nMaxRecursionLevels, CmpFunc &cmp)
{
	assert(numItems >= 0);
	assert(nMaxRecursionLevels >= 0);
	assert(list);

	if (numItems <= 1)
		return;

	// Select the middle item as pivot. (In a nearly sorted list, this is as near of the 
	// median value as we can get)
	std::swap(list[numItems-1], list[numItems/2]);
	const T pivotValue = list[numItems-1];

	int rEnd = -1;
	for(int i = 0; i < numItems-1; i++)
		if (cmp(list[i], pivotValue) <= 0)
		{
			++rEnd;
			std::swap(list[rEnd], list[i]);
		}
	// put the pivot value to the center of the array
	std::swap(list[rEnd+1], list[numItems-1]);

	if (nMaxRecursionLevels > 0)
	{
		// sort left & right
		if (rEnd > 0) // if left side has more than one item, sort it.
			IntroSort(list, rEnd+1,nMaxRecursionLevels-1, cmp);
		if (numItems-rEnd>3) // if right side has more than one item, sort it.
			IntroSort(&list[rEnd+2], numItems - rEnd-2,nMaxRecursionLevels-1, cmp);
	}
	else
	{
		// sort left & right
		if (rEnd > 0) // if left side has more than one item, sort it.
			HeapSort(list, rEnd+1, cmp);
		if (numItems-rEnd>3) // if right side has more than one item, sort it.
			HeapSort(&list[rEnd+2], numItems - rEnd-2, cmp);
	}
}

template<typename T, typename CmpFunc>
bool IsSorted(T *list, int numItems, CmpFunc &cmp)
{
	for(size_t i = 0; i+1 < numItems; ++i)
		if (cmp(list[i], list[i+1]) > 0)
			return false;

	return true;
}

} // ~sort
} // ~kNet

