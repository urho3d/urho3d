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

#include "../../MathDefs.h"
#include "ScriptSpecificMathDefs.h"

namespace Urho3D
{

// Required for Lua bindings. These aren't declared in MathDefs.h (so the rest
// of the engine can't use them). Instead they are declared as extern variables
// in Internal/Script/ScriptSpecificMathDefs.h. The Lua bindings include that
// header file so they can be exposed to Lua scripts.
const float M_INFINITY      = M_LIMITS<float>   ::Infinity;
const float M_EPSILON       = M_LIMITS<float>   ::Epsilon;
const float M_LARGE_EPSILON = M_LIMITS<float>   ::LargeEpsilon;
const signed M_MIN_INT       = M_LIMITS<signed>  ::Min;
const signed M_MAX_INT       = M_LIMITS<signed>  ::Max;
const unsigned M_MIN_UNSIGNED  = M_LIMITS<unsigned>::Min;
const unsigned M_MAX_UNSIGNED  = M_LIMITS<unsigned>::Max;

} // namespace Urho3D
