/*
	Copyright (c) 2009-2010 Christopher A. Taylor.  All rights reserved.

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

#ifndef CAT_I_RANDOM_HPP
#define CAT_I_RANDOM_HPP

#include <cat/Platform.hpp>

namespace cat {


// Pseudo-random number generators will derive from IRandom and implement its public methods
// WARNING: Not seeded by default.  Be sure to call Initialize() before Generate()
class IRandom
{
public:
    virtual ~IRandom() {}

    // Generate a 32-bit random number
    virtual u32 Generate() = 0;

    // Generate a variable number of random bytes
    virtual void Generate(void *buffer, int bytes) = 0;

public:
    // Generate a 32-bit random number in the range [low..high] inclusive
    u32 GenerateUnbiased(u32 low, u32 high)
    {
        u32 range = high - low;

        // Round range up to the next pow(2)-1 using a Stanford Bit Twiddling Hack
        u32 v = range - 1;
        v |= v >> 1;
        v |= v >> 2;
        v |= v >> 4;
        v |= v >> 8;
        v |= v >> 16;

        // Generate an unbiased random number in the inclusive range [0..(high-low)]
        u32 x;
        do x = Generate() & v;
        while (x > range);

        return low + x;
    }
};


} // namespace cat

#endif // CAT_I_RANDOM_HPP
