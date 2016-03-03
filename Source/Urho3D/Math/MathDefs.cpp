//
// Copyright (c) 2008-2016 the Urho3D project.
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

#include "MathDefs.h"

namespace Urho3D
{

// Limits for floating point types
const float Limits<float>::Min = std::numeric_limits<float>::min();
const float Limits<float>::Max = std::numeric_limits<float>::max();
const float Limits<float>::Infinity = std::numeric_limits<float>::infinity();
const float Limits<float>::Epsilon = std::numeric_limits<float>::epsilon();
const float Limits<float>::LargeEpsilon = std::numeric_limits<float>::epsilon() * 5;

const double Limits<double>::Min = std::numeric_limits<double>::min();
const double Limits<double>::Max = std::numeric_limits<double>::max();
const double Limits<double>::Infinity = std::numeric_limits<double>::infinity();
const double Limits<double>::Epsilon = std::numeric_limits<double>::epsilon();
const double Limits<double>::LargeEpsilon = std::numeric_limits<double>::epsilon() * 5;

const long double Limits<long double>::Min = std::numeric_limits<long double>::min();
const long double Limits<long double>::Max = std::numeric_limits<long double>::max();
const long double Limits<long double>::Infinity = std::numeric_limits<long double>::infinity();
const long double Limits<long double>::Epsilon = std::numeric_limits<long double>::epsilon();
const long double Limits<long double>::LargeEpsilon = std::numeric_limits<long double>::epsilon() * 5;

} // namespace Urho3D
