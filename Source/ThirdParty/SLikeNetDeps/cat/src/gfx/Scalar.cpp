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

#include <cat/gfx/Scalar.hpp>
using namespace cat;

#if defined(CAT_ISA_X86)

/*
	Fast inverse square root, improving on the accuracy of the
	Quake III algorithm, with error in the range -0.0006531 ... 0.0006531
	from http://pizer.wordpress.com/2008/10/12/fast-inverse-square-root/
*/
f32 cat::InvSqrt(f32 x)
{
	f32 x1 = 0.714158168f * x;

	// Generate a close approximation to the square root:
	u32 i = 0x5F1F1412 - (reinterpret_cast<u32&>(x) >> 1);
	f32 approx = reinterpret_cast<f32&>(i);

	// One iteration of Newton's method converging towards the square root:
	return approx * (1.69000231f - x1 * approx * approx);
}

#else

f32 cat::InvSqrt(f32 x)
{
	return (f32)(1.0 / sqrt(x));
}

#endif
