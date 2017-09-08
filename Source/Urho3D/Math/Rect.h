//
// Copyright (c) 2008-2017 the Urho3D project.
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

#include <type_traits>
#include "../Math/Vector4.h"


namespace Urho3D
{

/// Two-dimensional bounding rectangle.
template<typename T>
class URHO3D_API BaseRect
{
public:
    /// Construct an undefined rect.
    BaseRect() :
        min_(std::numeric_limits<T>::max(), std::numeric_limits<T>::max()),
        max_(std::numeric_limits<T>::min(), std::numeric_limits<T>::min())
    {
    }

    /// Construct from minimum and maximum vectors.
    BaseRect(const BaseVector2<T>& min, const BaseVector2<T>& max) :
        min_(min),
        max_(max)
    {
    }

    /// Construct from coordinates.
    BaseRect(T left, T top, T right, T bottom) :
        min_(left, top),
        max_(right, bottom)
    {
    }

    /// Construct from a Vector4.
    BaseRect(const BaseVector4<T>& vector) :
        min_(vector.x_, vector.y_),
        max_(vector.z_, vector.w_)
    {
    }

    /// Construct from a number array.
    template<typename T2>
    explicit BaseRect(const T2* data) :
        min_(data[0], data[1]),
        max_(data[2], data[3])
    {
        static_assert(std::is_arithmetic<T>::value, "Parameter must be array of arithmetic type.");
    }

    /// Copy-construct from another rect.
    BaseRect(const BaseRect& rect) :
        min_(rect.min_),
        max_(rect.max_)
    {
    }

    /// Assign from another rect.
    BaseRect& operator =(const BaseRect& rhs)
    {
        min_ = rhs.min_;
        max_ = rhs.max_;
        return *this;
    }

    /// Test for equality with another rect.
    bool operator ==(const BaseRect& rhs) const { return min_ == rhs.min_ && max_ == rhs.max_; }

    /// Test for inequality with another rect.
    bool operator !=(const BaseRect& rhs) const { return min_ != rhs.min_ || max_ != rhs.max_; }

    /// Define from another rect.
    void Define(const BaseRect& rect)
    {
        min_ = rect.min_;
        max_ = rect.max_;
    }

    /// Define from minimum and maximum vectors.
    void Define(const BaseVector2<T>& min, const BaseVector2<T>& max)
    {
        min_ = min;
        max_ = max;
    }

    /// Define from a point.
    void Define(const BaseVector2<T>& point)
    {
        min_ = max_ = point;
    }

    /// Merge a point.
    void Merge(const BaseVector2<T>& point)
    {
        if (point.x_ < min_.x_)
            min_.x_ = point.x_;
        if (point.x_ > max_.x_)
            max_.x_ = point.x_;
        if (point.y_ < min_.y_)
            min_.y_ = point.y_;
        if (point.y_ > max_.y_)
            max_.y_ = point.y_;
    }

    /// Merge a rect.
    void Merge(const BaseRect& rect)
    {
        if (rect.min_.x_ < min_.x_)
            min_.x_ = rect.min_.x_;
        if (rect.min_.y_ < min_.y_)
            min_.y_ = rect.min_.y_;
        if (rect.max_.x_ > max_.x_)
            max_.x_ = rect.max_.x_;
        if (rect.max_.y_ > max_.y_)
            max_.y_ = rect.max_.y_;
    }

    /// Clear to undefined state.
    void Clear()
    {
        min_ = BaseVector2<T>(std::numeric_limits<T>::max(), std::numeric_limits<T>::max());
        max_ = BaseVector2<T>(std::numeric_limits<T>::min(), std::numeric_limits<T>::min());
    }

    /// Clip with another rect.
    void Clip(const BaseRect& rect);

    /// Return true if this rect is defined via a previous call to Define() or Merge().
    bool Defined() const
    {
        return min_.x_ != std::numeric_limits<T>::max();
    }

    /// Return center.
    BaseVector2<T> Center() const { return (max_ + min_) * 0.5f; }

    /// Return size.
    BaseVector2<T> Size() const { return max_ - min_; }

    /// Return half-size.
    BaseVector2<T> HalfSize() const { return (max_ - min_) * 0.5f; }

    /// Return width.
    T Width() const { return right_ - left_; }

    /// Return height.
    T Height() const { return bottom_ - top_; }

    /// Test for equality with another rect with epsilon.
    bool Equals(const BaseRect& rhs) const { return min_.Equals(rhs.min_) && max_.Equals(rhs.max_); }

    /// Test whether a point is inside.
    Intersection IsInside(const BaseVector2<T>& point) const
    {
        if (point.x_ < min_.x_ || point.y_ < min_.y_ || point.x_ > max_.x_ || point.y_ > max_.y_)
            return OUTSIDE;
        else
            return INSIDE;
    }

    /// Test if another rect is inside, outside or intersects.
    Intersection IsInside(const BaseRect& rect) const
    {
        if (rect.max_.x_ < min_.x_ || rect.min_.x_ > max_.x_ || rect.max_.y_ < min_.y_ || rect.min_.y_ > max_.y_)
            return OUTSIDE;
        else if (rect.min_.x_ < min_.x_ || rect.max_.x_ > max_.x_ || rect.min_.y_ < min_.y_ || rect.max_.y_ > max_.y_)
            return INTERSECTS;
        else
            return INSIDE;
    }

    /// Return number data.
    const T* Data() const { return &min_.x_; }

    /// Return as a vector.
    BaseVector4<T> ToVector4() const { return BaseVector4<T>(min_.x_, min_.y_, max_.x_, max_.y_); }

    /// Return as string.
    String ToString() const;

    union
    {
        /// Minimum vector.
        BaseVector2<T> min_;
        struct
        {
            /// Left coordinate.
            T left_;
            /// Top coordinate.
            T top_;
        };
    };

    union
    {
        /// Maximum vector.
        BaseVector2<T> max_;
        struct
        {
            /// Right coordinate.
            T right_;
            /// Bottom coordinate.
            T bottom_;
        };
    };

    /// Rect in the range (-1, -1) - (1, 1)
    static const BaseRect FULL;
    /// Rect in the range (0, 0) - (1, 1)
    static const BaseRect POSITIVE;
    /// Zero-sized rect.
    static const BaseRect ZERO;
};

typedef BaseRect<float> Rect;
typedef BaseRect<int> IntRect;

template class URHO3D_API BaseRect<float>;
template class URHO3D_API BaseRect<int>;

}
