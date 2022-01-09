//
// Copyright (c) 2008-2022 the Urho3D project.
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


/// Stable sort is based on http://thomas.baudel.name/Visualisation/VisuTri/inplacestablesort.html
/// Benchmark https://www.codeproject.com/Articles/26048/Fastest-In-Place-Stable-Sort
template <class T> void StableSortRotate(RandomAccessIterator<T> begin, RandomAccessIterator<T> mid, 
    RandomAccessIterator<T> end)
{
/*  a less sophisticated but costlier version:
  reverse(from, mid-1);
  reverse(mid, to-1);
  reverse(from, to-1);
*/
    if(begin == mid || mid == end) return;

    //int n = gcd(end - begin, mid - begin);
    int n1 = end - begin;
    int n2 = mid - begin;
    while (n2 != 0)
    {
        int t = n1 % n2;
        n1 = n2;
        n2 = t;
    }
    int n = n1;

    while(n-- != 0)
    {
        T val = *(begin + n);
        int shift = mid - begin;
        RandomAccessIterator<T> p1 = begin + n;
        RandomAccessIterator<T> p2 = begin + n + shift;
        while(p2 != begin + n)
        {
            *p1 = *p2;
            p1 = p2;
            if(end - p2 > shift)
            {
                p2 += shift;
            }
            else
            {
                p2 = begin + (shift - (end - p2));
            }
        }
        *p1 = val;
    }
}

template <class T> RandomAccessIterator<T> StableSortLower(RandomAccessIterator<T> begin, RandomAccessIterator<T> end, 
    RandomAccessIterator<T> val)
{
    int len = end - begin, half;
    while(len > 0)
    {
        half = len / 2;
        RandomAccessIterator<T> mid = begin + half;
        if(*mid < *val)
        {
            begin = mid + 1;
            len = len - half -1;
        }
        else
        {
            len = half;
        }
    }
    return begin;
}

template <class T> RandomAccessIterator<T> StableSortUpper(RandomAccessIterator<T> begin, RandomAccessIterator<T> end, 
    RandomAccessIterator<T> val)
{
    int len = end - begin, half;
    while(len > 0)
    {
        half = len / 2;
        RandomAccessIterator<T> mid = begin + half;
        if(*val < *mid)
        {
            len = half;
        }
        else
        {
            begin = mid + 1;
            len = len - half - 1;
        }
    }
    return begin;
}

template <class T> void StableSortMerge(RandomAccessIterator<T> begin, RandomAccessIterator<T> pivot, 
    RandomAccessIterator<T> end, int len1, int len2)
{
    if(len1 == 0 || len2 == 0)
        return;

    if(len1+len2 == 2)
    {
        if(*pivot < *begin)
            Swap(*pivot, *begin);
        return;
    }
    
    RandomAccessIterator<T> first_cut, second_cut;
    int len11, len22;
    if(len1 > len2)
    {
        len11 = len1 / 2;
        first_cut = begin + len11;
        second_cut = StableSortLower(pivot, end, first_cut);
        len22 = second_cut - pivot;
    }
    else
    {
        len22 = len2 / 2;
        second_cut = pivot + len22;
        first_cut = StableSortUpper(begin, pivot, second_cut);
        len11 = first_cut - begin;
    }

    StableSortRotate(first_cut, pivot, second_cut);
    RandomAccessIterator<T> new_mid = first_cut + len22;
    StableSortMerge(begin, first_cut, new_mid, len11, len22);
    StableSortMerge(new_mid, second_cut, end, len1 - len11, len2 - len22);
}

template <class T> void StableSort(RandomAccessIterator<T> begin, RandomAccessIterator<T> end)
{
    if(end - begin < 12)
    {
        InsertionSort(begin, end);
        return;
    }
    RandomAccessIterator<T> middle = begin + (end - begin) / 2;
    StableSort(begin, middle);
    StableSort(middle, end);
    StableSortMerge(begin, middle, end, middle - begin, end - middle);
}

template <class T, class U> RandomAccessIterator<T> StableSortLower(RandomAccessIterator<T> begin, RandomAccessIterator<T> end, 
    RandomAccessIterator<T> val, U compare)
{
    int len = end - begin, half;
    while(len > 0)
    {
        half = len / 2;
        RandomAccessIterator<T> mid = begin + half;
        if(compare(*mid, *val))
        {
            begin = mid + 1;
            len = len - half -1;
        }
        else
        {
            len = half;
        }
    }
    return begin;
}

template <class T, class U> RandomAccessIterator<T> StableSortUpper(RandomAccessIterator<T> begin, RandomAccessIterator<T> end, 
    RandomAccessIterator<T> val, U compare)
{
    int len = end - begin, half;
    while(len > 0)
    {
        half = len / 2;
        RandomAccessIterator<T> mid = begin + half;
        if(compare(*val, *mid))
        {
            len = half;
        }
        else
        {
            begin = mid + 1;
            len = len - half - 1;
        }
    }
    return begin;
}

template <class T, class U> void StableSortMerge(RandomAccessIterator<T> begin, RandomAccessIterator<T> pivot, 
    RandomAccessIterator<T> end, int len1, int len2, U compare)
{
    if(len1 == 0 || len2 == 0)
        return;

    if(len1 + len2 == 2)
    {
        if(compare(*pivot, *begin))
            Swap(*pivot, *begin);
        return;
    }
    
    RandomAccessIterator<T> first_cut, second_cut;
    int len11, len22;
    if(len1 > len2)
    {
        len11 = len1 / 2;
        first_cut = begin + len11;
        second_cut = StableSortLower(pivot, end, first_cut, compare);
        len22 = second_cut - pivot;
    }
    else
    {
        len22 = len2 / 2;
        second_cut = pivot + len22;
        first_cut = StableSortUpper(begin, pivot, second_cut, compare);
        len11 = first_cut - begin;
    }

    StableSortRotate(first_cut, pivot, second_cut);
    RandomAccessIterator<T> new_mid = first_cut + len22;
    StableSortMerge(begin, first_cut, new_mid, len11, len22, compare);
    StableSortMerge(new_mid, second_cut, end, len1 - len11, len2 - len22, compare);
}

template <class T, class U> void StableSort(RandomAccessIterator<T> begin, RandomAccessIterator<T> end,
    U compare)
{
    if(end - begin < 12)
    {
        InsertionSort(begin, end, compare);
        return;
    }
    RandomAccessIterator<T> middle = begin + (end - begin) / 2;
    StableSort(begin, middle, compare);
    StableSort(middle, end, compare);
    StableSortMerge(begin, middle, end, middle - begin, end - middle, compare);
}

}
