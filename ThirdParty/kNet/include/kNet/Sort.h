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

/** @file Sort.h
	@brief A range of comparison sort algorithms. */

#include "Clock.h"

//#include "LCG.h"
#include "SortCmp.h"

namespace kNet
{

/** @brief A range of comparison sort algorithms.

	When to use one of these sorts and when to use the std sorts? 
		(std::sort, std::stable_sort, std::list::sort etc.)

	1)	Always consider using the standard versions first. For example, the visual c++ 
		std::sort is on average faster than the introsort described here. Additionally, 
		your code has the advantage of being more portable.

	2)	The sorting algorithms described here operate only on contiguous data. This means
		that they can only be used to sort vectors and arrays. If you have a linked 
		list, you can only use list::sort. Additionally, the data type T must be assignable.

	3) If the std:: sorting performance is not acceptable, figure out the "profile"
		of your sortable data. Is it in random or mostly sorted order? Is it sorted
		once, occasionally or on a per-frame basis? Are all items unique or are there several
		that are equivalent? Is stable sort-property required? Then look at the actual 
		implementations of these algorithms and decide what fits the data profile the best. 
		And of course, always measure the actual performance. 
		
	Note that a few of these algorithms have only been implemented as a curiosity.
	Selection sort for example just plain sucks.

	The client-implemented comparison function must be of this form:

	template<typename T>
	int CmpFunc(const T &a, const T &b);

	@param a The first comparison operand.
	@param b The second comparison operand.
	@return a negative value if a < b, 0 if a == b and a positive value when b < a. */

namespace sort
{

/** Selection sort is a stable sort that has FIXED running time of ~n^2/2. It can
	contend only against Bubble sort, which in general performs far better.
	The only advantage of this against other sorts is that CmpFunc can be a partial ordering instead
	of a total ordering (For other sort functions, cmp must be a total order). */
template<typename T, typename CmpFunc>
void SelectionSort(T *list, int numItems, CmpFunc &cmp);

/** The same as above, but only partially sorts the list so that the numItemsToSort first items in the
	list are in order, the rest are unordered. Gives a slight performance boost when only a part of the list
	needs to get ordered. Doesn't affect the asymptotics though, which is O(k*n), where k=numItemsToSort. */
template<typename T, typename CmpFunc>
void PartialSelectionSort(T *list, int numItems, int numItemsToSort, CmpFunc &cmp);

/** Insertion sort is efficent on data that is almost sorted. Worst case O(n^2), avg.
	n^2/4, Best case O(n). This sort is stable. */
template<typename T, typename CmpFunc>
void InsertionSort(T *list, int numItems, CmpFunc &cmp);

/** Shell sort is an optimization of insertion sort, performs in O(n^1.25) on average. 
	Worst case O(n^2). This sort is not stable. */
template<typename T, typename CmpFunc>
void ShellSort(T *list, int numItems, CmpFunc &cmp);

/** Bubble sort sorts in worst case O(n^2) time, best case O(n) if the list is already almost sorted. 
	This sort is stable. */
template<typename T, typename CmpFunc>
void BubbleSort(T *list, int numItems, CmpFunc &cmp);

/** Cocktail sort == Bidirectional Bubble sort == Shaker sort == Ripple sort == Shuttle sort:
	Stable optimization of Bubble sort, worst case O(n^2). If the list is mostly ordered,
	then the running time is near O(n). */
template<typename T, typename CmpFunc>
void CocktailSort(T *list, int numItems, CmpFunc &cmp);

/** Comb sort is a "diminishing" Bubble sort, an unstable optimization of Bubble sort.
	Generally performs far better than Bubble/Cocktail sorts. */
template<typename T, typename CmpFunc>
void CombSort(T *list, int numItems, CmpFunc &cmp);

/** Merge sort has constant running time O(n*logn). Requires O(n) of additional space and 
	has a recursive call overhead of 2n-1. This sort is stable. Note that this sort dynamically
	allocates memory with a call to new[]. */ 
template<typename T, typename CmpFunc>
void MergeSort(T *list, int numItems, CmpFunc &cmp);

/** Quicksort sorts in avg. O(n*logn) time, with a O(logn) recursive call overhead. In worst case 
	(array is sorted in descending order) degenerates into a selection sort with O(n^2) 
	complexity. The middle element of the sublist is chosen as pivot. This sort is not 
	stable, and it has a potential security vulnerability due to recursive calls. */
template<typename T, typename CmpFunc>
void QuickSort(T *list, int numItems, CmpFunc &cmp);

/** Heapsort is an in-place working algorithm that runs in O(n*logn) time. Generally 
	slower than Quicksort, but is better in worst case scenario when the list is almost sorted. 
	This sort is not stable. */
template<typename T, typename CmpFunc>
void HeapSort(T *list, int numItems, CmpFunc &cmp);

/** Introspective sort starts as Quicksort, but switches to Heapsort when the maximum 
	number of recursion levels has been exceeded. This shields the implementation against 
	stack overflow. If it's known that Introsorting a particular list will cause it to switch 
	to Heapsort, it is faster to directly call Heapsort instead. Introsort is not stable. */
template<typename T, typename CmpFunc>
void IntroSort(T *list, int numItems, int nMaxRecursionLevels, CmpFunc &cmp);

/// This can be used for debugging.
template<typename T, typename CmpFunc>
bool IsSorted(T *list, int numItems, CmpFunc &cmp);

// The following lines define shortcuts for easier using when the standard < and == comparison operators are involved:
template<typename T> void SelectionSort(T *list, int numItems) { SelectionSort<T>(list, numItems, TriCmp<T>); }
template<typename T> void InsertionSort(T *list, int numItems) { InsertionSort<T>(list, numItems, TriCmp<T>); }
template<typename T> void ShellSort(T *list, int numItems) { ShellSort<T>(list, numItems, TriCmp<T>); }
template<typename T> void BubbleSort(T *list, int numItems) { BubbleSort<T>(list, numItems, TriCmp<T>); }
template<typename T> void CocktailSort(T *list, int numItems) { CocktailSort<T>(list, numItems, TriCmp<T>); }
template<typename T> void CombSort(T *list, int numItems) { CombSort<T>(list, numItems, TriCmp<T>); }
template<typename T> void MergeSort(T *list, int numItems) { MergeSort<T>(list, numItems, TriCmp<T>); }
template<typename T> void QuickSort(T *list, int numItems) { QuickSort<T>(list, numItems, TriCmp<T>); }

template<typename T> void HeapSort(T *list, int numItems) { HeapSort<T>(list, numItems, TriCmp<T>); }
template<typename T> void IntroSort(T *list, int numItems, int nMaxRecursionLevels = 1000) { IntroSort<T>(list, numItems, nMaxRecursionLevels, TriCmp<T>); }

} // ~sort
} // ~kNet

#include "Sort.inl"

