#ifndef __RICH_UTILS_H__
#define __RICH_UTILS_H__
#pragma once

#include "../UI/UIBatch.h"

namespace Urho3D {

template<typename T>
struct TRect
{
    T left;
    T top;
    T right;
    T bottom;

    TRect() :
    left(0),
            top(0),
            right(0),
            bottom(0)
    {
    }

    TRect(T const& _left, T const& _top, T const& _right, T const& _bottom) :
    left(_left),
            top(_top),
            right(_right),
            bottom(_bottom)
    {
    }

    TRect(TRect const& _obj) :
    left(_obj.left),
            top(_obj.top),
            right(_obj.right),
            bottom(_obj.bottom)
    {
    }

    TRect& operator -= (TRect const& _obj)
    {
            left -= _obj.left;
            top -= _obj.top;
            right -= _obj.right;
            bottom -= _obj.bottom;
            return *this;
    }

    TRect& operator += (TRect const& _obj)
    {
            left += _obj.left;
            top += _obj.top;
            right += _obj.right;
            bottom += _obj.bottom;
            return *this;
    }

    TRect operator - (TRect const& _obj) const
    {
            return TRect(left - _obj.left, top - _obj.top, right - _obj.right, bottom - _obj.bottom);
    }

    TRect operator + (TRect const& _obj) const
    {
            return TRect(left + _obj.left, top + _obj.top, right + _obj.right, bottom + _obj.bottom);
    }

    TRect& operator = (TRect const& _obj)
    {
            left = _obj.left;
            top = _obj.top;
            right = _obj.right;
            bottom = _obj.bottom;
            return *this;
    }

    template<typename U>
    TRect& operator = (TRect<U> const& _obj)
    {
            left = _obj.left;
            top = _obj.top;
            right = _obj.right;
            bottom = _obj.bottom;
            return *this;
    }

    bool operator == (TRect const& _obj) const
    {
            return ((left == _obj.left) && (top == _obj.top) && (right == _obj.right) && (bottom == _obj.bottom));
    }

    bool operator != (TRect const& _obj) const
    {
            return !((left == _obj.left) && (top == _obj.top) && (right == _obj.right) && (bottom == _obj.bottom));
    }

    T width() const
    {
            return right - left;
    }

    T height() const
    {
            return bottom - top;
    }

    void clear()
    {
            left = top = right = bottom = 0;
    }

    void set(T const& _left, T const& _top, T const& _right, T const& _bottom)
    {
            left = _left;
            top = _top;
            right = _right;
            bottom = _bottom;
    }

    void swap(TRect& _value)
    {
            TRect tmp = _value;
            _value = *this;
            *this = tmp;
    }

    bool empty() const
    {
            return ((left == 0) && (top == 0) && (right == 0) && (bottom == 0));
    }

    bool inside(const TRect<T>&  _value) const
    {
            return ((_value.left >= left) && (_value.right <= right) && (_value.top >= top) && (_value.bottom <= bottom));
    }

    bool intersect(const TRect<T>&  _value) const
    {
            return ((_value.left <= right) && (_value.right >= left) && (_value.top <= bottom) && (_value.bottom >= top));
    }
};

typedef TRect<float> FloatRect;

}

#endif
