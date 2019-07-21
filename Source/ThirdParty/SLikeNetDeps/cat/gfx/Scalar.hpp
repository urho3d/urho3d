/*
	Copyright (c) 2009 Christopher A. Taylor.  All rights reserved.

	Redistribution and use in source and binary forms, with or without
	modification, are permitted provided that the following conditions are met:

	* Redistributions of source code must retain the above copyright notice,
	  this list of conditions and the following disclaimer.
	* Redistributions in binary form must reproduce the above copyright notice,
	  this list of conditions and the following disclaimer in the documentation
	  and/or other materials provided with the distribution.
	* Neither the name of LibCat nor the names of its contributors may be used
	  to endorse or promote products derived from this software without
	  specific prior written permission.

	THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
	AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
	IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
	ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
	LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
	CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
	SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
	INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
	CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
	ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
	POSSIBILITY OF SUCH DAMAGE.
*/

#ifndef CAT_SCALAR_HPP
#define CAT_SCALAR_HPP

#include <cat/Platform.hpp>
#include <cmath>

namespace cat {


// PI
#define CAT_TWO_PI_64 6.283185307179586476925286766559
#define CAT_TWO_PI_32 6.28318531f
#define CAT_PI_64 3.1415926535897932384626433832795
#define CAT_PI_32 3.14159265f
#define CAT_HALF_PI_64 1.5707963267948966192313216916398
#define CAT_HALF_PI_32 1.5707963268f
#define CAT_QUARTER_PI_64 0.78539816339744830961566084581988
#define CAT_QUARTER_PI_32 0.7853981634f
#define CAT_INV_PI_64 0.31830988618379067153776752674503
#define CAT_INV_PI_32 0.3183098862f


// Angle conversion
inline f64 Deg2Rad(f64 angle)
{
	return angle * CAT_TWO_PI_64 / 360.0;
}
inline f32 Deg2Rad(f32 angle)
{
	return angle * CAT_TWO_PI_32 / 360.0f;
}
inline f64 Rad2Deg(f64 angle)
{
	return angle * 360.0 / CAT_TWO_PI_64;
}
inline f32 Rad2Deg(f32 angle)
{
	return angle * 360.0f / CAT_TWO_PI_32;
}


// Generic clamp() function
template<class Scalar>
void Clamp(Scalar &x, Scalar low, Scalar high)
{
	if (x < low) x = low;
	else if (x > high) x = high;
}


// Fast inverse square root
f32 InvSqrt(f32 x);


} // namespace cat

#endif // CAT_SCALAR_HPP
