//
// Urho3D Engine
// Copyright (c) 2008-2011 Lasse Öörni
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

#ifndef MATH_RECT_H
#define MATH_RECT_H

#include "Vector2.h"

//! A two-dimensional bounding rectangle
class Rect
{
public:
    //! Construct an undefined rect
    Rect() :
        mDefined(false)
    {
    }
    
    //! Copy-construct from another rect
    Rect(const Rect& rect) :
        mMin(rect.mMin),
        mMax(rect.mMax),
        mDefined(true)
    {
    }
    
    //! Construct from minimum and maximum vectors
    Rect(const Vector2& min, const Vector2& max) :
        mMin(min),
        mMax(max),
        mDefined(true)
    {
    }
    
    //! Construct from coordinates
    Rect(float left, float top, float right, float bottom) :
        mMin(left, top),
        mMax(right, bottom),
        mDefined(true)
    {
    }
    
    //! Assign from another rect
    Rect& operator = (const Rect& rhs)
    {
        mMin = rhs.mMin;
        mMax = rhs.mMax;
        mDefined = true;
        
        return *this;
    }
    
    //! Test for equality with another rect
    bool operator == (const Rect& rhs) const
    {
        return (mMin == rhs.mMin) && (mMax == rhs.mMax);
    }
    
    //! Test for inequality with another rect
    bool operator != (const Rect& rhs) const
    {
        return (mMin != rhs.mMin) || (mMax != rhs.mMax);
    }
    
    //! Define from minimum and maximum vectors
    void define(const Vector2& min, const Vector2& max)
    {
        mMin = min;
        mMax = max;
        mDefined = true;
    }
    
    //! Define from a point
    void define(const Vector2& point)
    {
        mMin = mMax = point;
        mDefined = true;
    }
    
    //! Merge a point
    void merge(const Vector2& point)
    {
        if (!mDefined)
        {
            mMin = mMax = point;
            mDefined = true;
        }
        
        if (point.mX < mMin.mX)
            mMin.mX = point.mX;
        if (point.mX > mMax.mX)
            mMax.mX = point.mX;
        if (point.mY < mMin.mY)
            mMin.mY = point.mY;
        if (point.mY > mMax.mY)
            mMax.mY = point.mY;
    }
    
    //! Merge a rect
    void merge(const Rect& rect)
    {
        if (!mDefined)
        {
            mMin = rect.mMin;
            mMax = rect.mMax;
            mDefined = true;
        }
        
        if (rect.mMin.mX < mMin.mX) mMin.mX = rect.mMin.mX;
        if (rect.mMin.mY < mMin.mY) mMin.mY = rect.mMin.mY;
        if (rect.mMax.mX > mMax.mX) mMax.mX = rect.mMax.mX;
        if (rect.mMax.mY > mMax.mY) mMax.mY = rect.mMax.mY;
    }
    
    //! Return float data
    const void* getData() const { return &mMin.mX; }
    
    //! Minimum vector
    Vector2 mMin;
    //! Maximum vector
    Vector2 mMax;
    //! Defined flag
    bool mDefined;
    
    //! A rect in the range (-1, -1) - (1, 1)
    static const Rect sFullRect;
    //! A zero-sized rect
    static const Rect sZero;
};

//! A two-dimensional bounding rectangle with integer values
class IntRect
{
public:
    //! Construct an undefined rect
    IntRect()
    {
    }
    
    //! Construct from coordinates
    IntRect(int left, int top, int right, int bottom) :
        mLeft(left),
        mTop(top),
        mRight(right),
        mBottom(bottom)
    {
    }
    
    //! Test for equality with another rect
    bool operator == (const IntRect& rhs) const
    {
        return (mLeft == rhs.mLeft) && (mTop == rhs.mTop) && (mRight == rhs.mRight) && (mBottom == rhs.mBottom);
    }
    
    //! Test for inequality with another rect
    bool operator != (const IntRect& rhs) const
    {
        return (mLeft != rhs.mLeft) || (mTop != rhs.mTop) || (mRight != rhs.mRight) || (mBottom != rhs.mBottom);
    }
    
    //! Return integer data
    const int* getData() const { return &mLeft; }
    
    //! Left coordinate
    int mLeft;
    //! Top coordinate
    int mTop;
    //! Right coordinate
    int mRight;
    //! Bottom coordinate
    int mBottom;
    
    //! Zero-sized rect
    static const IntRect sZero;
};

#endif // MATH_RECT_H
