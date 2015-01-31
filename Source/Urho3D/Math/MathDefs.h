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

#include "../Math/Random.h"

#include <cstdlib>
#include <cmath>

namespace Urho3D
{

#undef M_PI
static const float M_PI = 3.14159265358979323846264338327950288f;
static const float M_HALF_PI = M_PI * 0.5f;
static const int M_MIN_INT = 0x80000000;
static const int M_MAX_INT = 0x7fffffff;
static const unsigned M_MIN_UNSIGNED = 0x00000000;
static const unsigned M_MAX_UNSIGNED = 0xffffffff;

static const float M_EPSILON = 0.000001f;
static const float M_LARGE_EPSILON = 0.00005f;
static const float M_MIN_NEARCLIP = 0.01f;
static const float M_MAX_FOV = 160.0f;
static const float M_LARGE_VALUE = 100000000.0f;
static const float M_INFINITY = (float)HUGE_VAL;
static const float M_DEGTORAD = (float)M_PI / 180.0f;
static const float M_DEGTORAD_2 = (float)M_PI / 360.0f; // M_DEGTORAD / 2.f
static const float M_RADTODEG = 1.0f / M_DEGTORAD;

/// Intersection test result.
enum Intersection
{
    OUTSIDE,
    INTERSECTS,
    INSIDE
};

/// Check whether two floating point values are equal within accuracy.
inline bool Equals(float lhs, float rhs) { return lhs + M_EPSILON >= rhs && lhs - M_EPSILON <= rhs; }
/// Check whether a floating point value is NaN.
inline bool IsNaN(float value) { return value != value; }
/// Linear interpolation between two float values.
inline float Lerp(float lhs, float rhs, float t) { return lhs * (1.0f - t) + rhs * t; }
/// Return the smaller of two floats.
inline float Min(float lhs, float rhs) { return lhs < rhs ? lhs : rhs; }
/// Return the larger of two floats.
inline float Max(float lhs, float rhs) { return lhs > rhs ? lhs : rhs; }
/// Return absolute value of a float.
inline float Abs(float value) { return value >= 0.0f ? value : -value; }
/// Return the sign of a float (-1, 0 or 1.)
inline float Sign(float value) { return value > 0.0f ? 1.0f : (value < 0.0f ? -1.0f : 0.0f); }

/// Clamp a float to a range.
inline float Clamp(float value, float min, float max)
{
    if (value < min)
        return min;
    else if (value > max)
        return max;
    else
        return value;
}

/// Smoothly damp between values.
inline float SmoothStep(float lhs, float rhs, float t)
{
    t = Clamp((t - lhs) / (rhs - lhs), 0.0f, 1.0f); // Saturate t
    return t * t * (3.0f - 2.0f * t);
}

/// Return sine of an angle in degrees.
inline float Sin(float angle) { return sinf(angle * M_DEGTORAD); }
/// Return cosine of an angle in degrees.
inline float Cos(float angle) { return cosf(angle * M_DEGTORAD); }
/// Return tangent of an angle in degrees.
inline float Tan(float angle) { return tanf(angle * M_DEGTORAD); }
/// Return arc sine in degrees.
inline float Asin(float x) { return M_RADTODEG * asinf(Clamp(x, -1.0f, 1.0f)); }
/// Return arc cosine in degrees.
inline float Acos(float x) { return M_RADTODEG * acosf(Clamp(x, -1.0f, 1.0f)); }
/// Return arc tangent in degrees.
inline float Atan(float x) { return M_RADTODEG * atanf(x); }
/// Return arc tangent of y/x in degrees.
inline float Atan2(float y, float x) { return M_RADTODEG * atan2f(y, x); }

/// Return the smaller of two integers.
inline int Min(int lhs, int rhs) { return lhs < rhs ? lhs : rhs; }
/// Return the larger of two integers.
inline int Max(int lhs, int rhs) { return lhs > rhs ? lhs : rhs; }
/// Return absolute value of an integer
inline int Abs(int value) { return value >= 0 ? value : -value; }

/// Clamp an integer to a range.
inline int Clamp(int value, int min, int max)
{
    if (value < min)
        return min;
    else if (value > max)
        return max;
    else
        return value;
}

/// Check whether an unsigned integer is a power of two.
inline bool IsPowerOfTwo(unsigned value)
{
    if (!value)
        return true;
    while (!(value & 1))
        value >>= 1;
    return value == 1;
}

/// Round up to next power of two.
inline unsigned NextPowerOfTwo(unsigned value)
{
    unsigned ret = 1;
    while (ret < value && ret < 0x80000000)
        ret <<= 1;
    return ret;
}

/// Count the number of set bits in a mask.
inline unsigned CountSetBits(unsigned value)
{
    // Brian Kernighan's method
    unsigned count = 0;
    for (count = 0; value; count++)
        value &= value - 1;
    return count;
}

/// Update a hash with the given 8-bit value using the SDBM algorithm.
inline unsigned SDBMHash(unsigned hash, unsigned char c) { return c + (hash << 6) + (hash << 16) - hash; }
/// Return a random float between 0.0 (inclusive) and 1.0 (exclusive.)
inline float Random() { return Rand() / 32768.0f; }
/// Return a random float between 0.0 and range, inclusive from both ends.
inline float Random(float range) { return Rand() * range / 32767.0f; }
/// Return a random float between min and max, inclusive from both ends.
inline float Random(float min, float max) { return Rand() * (max - min) / 32767.0f + min; }
/// Return a random integer between 0 and range - 1.
inline int Random(int range) { return (Rand() * (range - 1) + 16384) / 32767; }
/// Return a random integer between min and max - 1.
inline int Random(int min, int max) { return (Rand() * (max - min - 1) + 16384) / 32767 + min; }
/// Return a random normal distributed number with the given mean value and variance.
inline float RandomNormal(float meanValue, float variance) { return RandStandardNormal() * sqrtf(variance) + meanValue; }

}
