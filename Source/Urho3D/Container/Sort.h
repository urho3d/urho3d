//
// Copyright (c) 2008-2015 the Urho3D project.
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//

#pragma once

#include "../Container/Swap.h"
#include "../Container/VectorBase.h"

namespace Urho3D
{

static const int QUICKSORT_THRESHOLD = 16;

// Based on Comparison of several sorting algorithms by Juha Nieminen
// http://warp.povusers.org/SortComparison/

/// Perform insertion sort on an array.
template <class T> void InsertionSort(RandomAccessIterator<T> begin, RandomAccessIterator<T> end)
{
    for (RandomAccessIterator<T> i = begin + 1; i < end; ++i)
    {
        T temp = *i;
        RandomAccessIterator<T> j = i;
        while (j > begin && temp < *(j - 1))
        {
            *j = *(j - 1);
            --j;
        }
        *j = temp;
    }
}

/// Perform insertion sort on an array using a compare function.
template <class T, class U> void InsertionSort(RandomAccessIterator<T> begin, RandomAccessIterator<T> end, U compare)
{
    for (RandomAccessIterator<T> i = begin + 1; i < end; ++i)
    {
        T temp = *i;
        RandomAccessIterator<T> j = i;
        while (j > begin && compare(temp, *(j - 1)))
        {
            *j = *(j - 1);
            --j;
        }
        *j = temp;
    }
}

/// Perform quick sort initial pass on an array. Does not sort fully.
template <class T> void InitialQuickSort(RandomAccessIterator<T> begin, RandomAccessIterator<T> end)
{
    while (end - begin > QUICKSORT_THRESHOLD)
    {
        // Choose the pivot by median
        RandomAccessIterator<T> pivot = begin + ((end - begin) / 2);
        if (*begin < *pivot && *(end - 1) < *begin)
            pivot = begin;
        else if (*(end - 1) < *pivot && *begin < *(end - 1))
            pivot = end - 1;
        
        // Partition and sort recursively
        RandomAccessIterator<T> i = begin - 1;
        RandomAccessIterator<T> j = end;
        T pivotValue = *pivot;
        for (;;)
        {
            while (pivotValue < *(--j));
            while (*(++i) < pivotValue);
            if (i < j)
                Swap(*i, *j);
            else
                break;
        }
        
        InitialQuickSort(begin, j + 1);
        begin = j + 1;
    }
}

/// Perform quick sort initial pass on an array using a compare function. Does not sort fully.
template <class T, class U> void InitialQuickSort(RandomAccessIterator<T> begin, RandomAccessIterator<T> end, U compare)
{
    while (end - begin > QUICKSORT_THRESHOLD)
    {
        // Choose the pivot by median
        RandomAccessIterator<T> pivot = begin + ((end - begin) / 2);
        if (compare(*begin, *pivot) && compare(*(end - 1), *begin))
            pivot = begin;
        else if (compare(*(end - 1), *pivot) && compare(*begin, *(end - 1)))
            pivot = end - 1;
        
        // Partition and sort recursively
        RandomAccessIterator<T> i = begin - 1;
        RandomAccessIterator<T> j = end;
        T pivotValue = *pivot;
        for (;;)
        {
            while (compare(pivotValue, *(--j)));
            while (compare(*(++i), pivotValue));
            if (i < j)
                Swap(*i, *j);
            else
                break;
        }
        
        InitialQuickSort(begin, j + 1, compare);
        begin = j + 1;
    }
}

/// Sort in ascending order using quicksort for initial passes, then an insertion sort to finalize.
template <class T> void Sort(RandomAccessIterator<T> begin, RandomAccessIterator<T> end)
{
    InitialQuickSort(begin, end);
    InsertionSort(begin, end);
}

/// Sort in ascending order using quicksort for initial passes, then an insertion sort to finalize, using a compare function.
template <class T, class U> void Sort(RandomAccessIterator<T> begin, RandomAccessIterator<T> end, U compare)
{
    InitialQuickSort(begin, end, compare);
    InsertionSort(begin, end, compare);
}

}
