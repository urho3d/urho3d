//
// Copyright (c) 2008-2020 the Urho3D project.
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

#include "../Math/Vector4.h"

namespace Urho3D
{

/// Two-dimensional bounding rectangle.
class URHO3D_API Rect
{
public:
    /// Construct an undefined rect.
    Rect() noexcept :
        min_(M_INFINITY, M_INFINITY),
        max_(-M_INFINITY, -M_INFINITY)
    {
    }

    /// Construct from minimum and maximum vectors.
    Rect(const Vector2& min, const Vector2& max) noexcept :
        min_(min),
        max_(max)
    {
    }

    /// Construct from coordinates.
    Rect(float left, float top, float right, float bottom) noexcept :
        min_(left, top),
        max_(right, bottom)
    {
    }

    /// Construct from a Vector4.
    explicit Rect(const Vector4& vector) noexcept :
        min_(vector.x_, vector.y_),
        max_(vector.z_, vector.w_)
    {
    }

    /// Construct from a float array.
    explicit Rect(const float* data) noexcept :
        min_(data[0], data[1]),
        max_(data[2], data[3])
    {
    }

    /// Copy-construct from another rect.
    Rect(const Rect& rect) noexcept = default;

    /// Assign from another rect.
    Rect& operator =(const Rect& rhs) noexcept = default;

    /// Test for equality with another rect.
    bool operator ==(const Rect& rhs) const { return min_ == rhs.min_ && max_ == rhs.max_; }

    /// Test for inequality with another rect.
    bool operator !=(const Rect& rhs) const { return min_ != rhs.min_ || max_ != rhs.max_; }

    /// Add another rect to this one inplace.
    Rect& operator +=(const Rect& rhs)
    {
        min_ += rhs.min_;
        max_ += rhs.max_;
        return *this;
    }

    /// Subtract another rect from this one inplace.
    Rect& operator -=(const Rect& rhs)
    {
        min_ -= rhs.min_;
        max_ -= rhs.max_;
        return *this;
    }

    /// Divide by scalar inplace.
    Rect& operator /=(float value)
    {
        min_ /= value;
        max_ /= value;
        return *this;
    }

    /// Multiply by scalar inplace.
    Rect& operator *=(float value)
    {
        min_ *= value;
        max_ *= value;
        return *this;
    }

    /// Divide by scalar.
    Rect operator /(float value) const
    {
        return Rect(min_ / value, max_ / value);
    }

    /// Multiply by scalar.
    Rect operator *(float value) const
    {
        return Rect(min_ * value, max_ * value);
    }

    /// Add another rect.
    Rect operator +(const Rect& rhs) const
    {
        return Rect(min_ + rhs.min_, max_ + rhs.max_);
    }

    /// Subtract another rect.
    Rect operator -(const Rect& rhs) const
    {
        return Rect(min_ - rhs.min_, max_ - rhs.max_);
    }

    /// Define from another rect.
    void Define(const Rect& rect)
    {
        min_ = rect.min_;
        max_ = rect.max_;
    }

    /// Define from minimum and maximum vectors.
    void Define(const Vector2& min, const Vector2& max)
    {
        min_ = min;
        max_ = max;
    }

    /// Define from a point.
    void Define(const Vector2& point)
    {
        min_ = max_ = point;
    }

    /// Merge a point.
    void Merge(const Vector2& point)
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
    void Merge(const Rect& rect)
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
        min_ = Vector2(M_INFINITY, M_INFINITY);
        max_ = Vector2(-M_INFINITY, -M_INFINITY);
    }

    /// Clip with another rect.
    void Clip(const Rect& rect);

    /// Return true if this rect is defined via a previous call to Define() or Merge().
    bool Defined() const
    {
        return min_.x_ != M_INFINITY;
    }

    /// Return center.
    Vector2 Center() const { return (max_ + min_) * 0.5f; }

    /// Return size.
    Vector2 Size() const { return max_ - min_; }

    /// Return half-size.
    Vector2 HalfSize() const { return (max_ - min_) * 0.5f; }

    /// Test for equality with another rect with epsilon.
    bool Equals(const Rect& rhs) const { return min_.Equals(rhs.min_) && max_.Equals(rhs.max_); }

    /// Test whether a point is inside.
    Intersection IsInside(const Vector2& point) const
    {
        if (point.x_ < min_.x_ || point.y_ < min_.y_ || point.x_ > max_.x_ || point.y_ > max_.y_)
            return OUTSIDE;
        else
            return INSIDE;
    }

    /// Test if another rect is inside, outside or intersects.
    Intersection IsInside(const Rect& rect) const
    {
        if (rect.max_.x_ < min_.x_ || rect.min_.x_ > max_.x_ || rect.max_.y_ < min_.y_ || rect.min_.y_ > max_.y_)
            return OUTSIDE;
        else if (rect.min_.x_ < min_.x_ || rect.max_.x_ > max_.x_ || rect.min_.y_ < min_.y_ || rect.max_.y_ > max_.y_)
            return INTERSECTS;
        else
            return INSIDE;
    }

    /// Return float data.
    const float* Data() const { return &min_.x_; }

    /// Return as a vector.
    Vector4 ToVector4() const { return Vector4(min_.x_, min_.y_, max_.x_, max_.y_); }

    /// Return as string.
    String ToString() const;

    /// Return left-top corner position.
    Vector2 Min() const { return min_; }

    /// Return right-bottom corner position.
    Vector2 Max() const { return max_; }

    /// Return left coordinate.
    float Left() const { return min_.x_; }

    /// Return top coordinate.
    float Top() const { return min_.y_; }

    /// Return right coordinate.
    float Right() const { return max_.x_; }

    /// Return bottom coordinate.
    float Bottom() const { return max_.y_; }

    /// Minimum vector.
    Vector2 min_;
    /// Maximum vector.
    Vector2 max_;

    /// Rect in the range (-1, -1) - (1, 1).
    static const Rect FULL;
    /// Rect in the range (0, 0) - (1, 1).
    static const Rect POSITIVE;
    /// Zero-sized rect.
    static const Rect ZERO;
};

/// Two-dimensional bounding rectangle with integer values.
class URHO3D_API IntRect
{
public:
    /// Construct a zero rect.
    IntRect() noexcept :
        left_(0),
        top_(0),
        right_(0),
        bottom_(0)
    {
    }

    /// Construct from minimum and maximum vectors.
    IntRect(const IntVector2& min, const IntVector2& max) noexcept :
        left_(min.x_),
        top_(min.y_),
        right_(max.x_),
        bottom_(max.y_)
    {
    }

    /// Construct from coordinates.
    IntRect(int left, int top, int right, int bottom) noexcept :
        left_(left),
        top_(top),
        right_(right),
        bottom_(bottom)
    {
    }

    /// Construct from an int array.
    explicit IntRect(const int* data) noexcept :
        left_(data[0]),
        top_(data[1]),
        right_(data[2]),
        bottom_(data[3])
    {
    }

    /// Test for equality with another rect.
    bool operator ==(const IntRect& rhs) const
    {
        return left_ == rhs.left_ && top_ == rhs.top_ && right_ == rhs.right_ && bottom_ == rhs.bottom_;
    }

    /// Test for inequality with another rect.
    bool operator !=(const IntRect& rhs) const
    {
        return left_ != rhs.left_ || top_ != rhs.top_ || right_ != rhs.right_ || bottom_ != rhs.bottom_;
    }

    /// Add another rect to this one inplace.
    IntRect& operator +=(const IntRect& rhs)
    {
        left_ += rhs.left_;
        top_ += rhs.top_;
        right_ += rhs.right_;
        bottom_ += rhs.bottom_;
        return *this;
    }

    /// Subtract another rect from this one inplace.
    IntRect& operator -=(const IntRect& rhs)
    {
        left_ -= rhs.left_;
        top_ -= rhs.top_;
        right_ -= rhs.right_;
        bottom_ -= rhs.bottom_;
        return *this;
    }

    /// Divide by scalar inplace.
    IntRect& operator /=(float value)
    {
        left_ = static_cast<int>(left_ / value);
        top_ = static_cast<int>(top_ / value);
        right_ = static_cast<int>(right_ / value);
        bottom_ = static_cast<int>(bottom_ / value);
        return *this;
    }

    /// Multiply by scalar inplace.
    IntRect& operator *=(float value)
    {
        left_ = static_cast<int>(left_ * value);
        top_ = static_cast<int>(top_ * value);
        right_ = static_cast<int>(right_ * value);
        bottom_ = static_cast<int>(bottom_ * value);
        return *this;
    }

    /// Divide by scalar.
    IntRect operator /(float value) const
    {
        return {
            static_cast<int>(left_ / value), static_cast<int>(top_ / value),
            static_cast<int>(right_ / value), static_cast<int>(bottom_ / value)
        };
    }

    /// Multiply by scalar.
    IntRect operator *(float value) const
    {
        return {
            static_cast<int>(left_ * value), static_cast<int>(top_ * value),
            static_cast<int>(right_ * value), static_cast<int>(bottom_ * value)
        };
    }

    /// Add another rect.
    IntRect operator +(const IntRect& rhs) const
    {
        return {
            left_ + rhs.left_, top_ + rhs.top_,
            right_ + rhs.right_, bottom_ + rhs.bottom_
        };
    }

    /// Subtract another rect.
    IntRect operator -(const IntRect& rhs) const
    {
        return {
            left_ - rhs.left_, top_ - rhs.top_,
            right_ - rhs.right_, bottom_ - rhs.bottom_
        };
    }

    /// Return size.
    IntVector2 Size() const { return IntVector2(Width(), Height()); }

    /// Return width.
    int Width() const { return right_ - left_; }

    /// Return height.
    int Height() const { return bottom_ - top_; }

    /// Test whether a point is inside.
    Intersection IsInside(const IntVector2& point) const
    {
        if (point.x_ < left_ || point.y_ < top_ || point.x_ >= right_ || point.y_ >= bottom_)
            return OUTSIDE;
        else
            return INSIDE;
    }

    /// Clip with another rect.  Since IntRect does not have an undefined state
    /// like Rect, return (0, 0, 0, 0) if the result is empty.
    void Clip(const IntRect& rect);

    /// Merge a rect.  If this rect was empty, become the other rect.  If the
    /// other rect is empty, do nothing.
    void Merge(const IntRect& rect);

    /// Return integer data.
    const int* Data() const { return &left_; }

    /// Return as string.
    String ToString() const;

    /// Return left-top corner position.
    IntVector2 Min() const { return {left_, top_}; }

    /// Return right-bottom corner position.
    IntVector2 Max() const { return {right_, bottom_}; }

    /// Return left coordinate.
    int Left() const { return left_; }

    /// Return top coordinate.
    int Top() const { return top_; }

    /// Return right coordinate.
    int Right() const { return right_; }

    /// Return bottom coordinate.
    int Bottom() const { return bottom_; }

    /// Left coordinate.
    int left_;
    /// Top coordinate.
    int top_;
    /// Right coordinate.
    int right_;
    /// Bottom coordinate.
    int bottom_;

    /// Zero-sized rect.
    static const IntRect ZERO;
};

}
