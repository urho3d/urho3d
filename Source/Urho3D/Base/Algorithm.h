// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

#pragma once

#include "../Urho3DConfig.h"

namespace Urho3D
{

/// Returns an iterator pointing to the first element in the range [first, last) that is not less than value.
template <class TRandomAccessIterator, class T>
TRandomAccessIterator LowerBound(TRandomAccessIterator first, TRandomAccessIterator last, const T& value)
{
    unsigned count = last - first;

    while (count > 0)
    {
        const unsigned step = count / 2;
        const TRandomAccessIterator it = first + step;
        if (*it < value)
        {
            first = it + 1;
            count -= step + 1;
        }
        else
        {
            count = step;
        }
    }
    return first;
}

/// Returns an iterator pointing to the first element in the range [first, last) that is greater than value.
template <class TRandomAccessIterator, class T>
TRandomAccessIterator UpperBound(TRandomAccessIterator first, TRandomAccessIterator last, const T& value)
{
    unsigned count = last - first;

    while (count > 0)
    {
        const unsigned step = count / 2;
        const TRandomAccessIterator it = first + step;
        if (!(value < *it))
        {
            first = it + 1;
            count -= step + 1;
        }
        else
        {
            count = step;
        };
    }
    return first;
}

}
