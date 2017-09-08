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

#include "../Precompiled.h"

#include "../Math/Rect.h"

#include <cstdio>

#include "../DebugNew.h"

namespace Urho3D
{

template<typename T> const BaseRect<T> BaseRect<T>::FULL(-1, -1, 1, 1);
template<typename T> const BaseRect<T> BaseRect<T>::POSITIVE(0, 0, 1, 1);
template<typename T> const BaseRect<T> BaseRect<T>::ZERO(0, 0, 0, 0);

template<>
String Rect::ToString() const
{
    char tempBuffer[CONVERSION_BUFFER_LENGTH];
    sprintf(tempBuffer, "%g %g %g %g", min_.x_, min_.y_, max_.x_, max_.y_);
    return String(tempBuffer);
}

template<>
String IntRect::ToString() const
{
    char tempBuffer[CONVERSION_BUFFER_LENGTH];
    sprintf(tempBuffer, "%d %d %d %d", min_.x_, min_.y_, max_.x_, max_.y_);
    return String(tempBuffer);
}

template<typename T>
void BaseRect<T>::Clip(const BaseRect<T>& rect)
{
    if (rect.min_.x_ > min_.x_)
        min_.x_ = rect.min_.x_;
    if (rect.max_.x_ < max_.x_)
        max_.x_ = rect.max_.x_;
    if (rect.min_.y_ > min_.y_)
        min_.y_ = rect.min_.y_;
    if (rect.max_.y_ < max_.y_)
        max_.y_ = rect.max_.y_;

    if (min_.x_ > max_.x_ || min_.y_ > max_.y_)
    {
        min_ = BaseVector2<T>(std::numeric_limits<T>::max(), std::numeric_limits<T>::max());
        max_ = BaseVector2<T>(std::numeric_limits<T>::min(), std::numeric_limits<T>::min());
    }
}

}
