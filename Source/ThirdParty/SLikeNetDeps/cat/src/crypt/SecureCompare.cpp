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

#include <cat/crypt/SecureCompare.hpp>

namespace cat {

bool SecureEqual(const void *vA, const void *vB, int bytes)
{
	const u8 *A = (const u8*)vA;
	const u8 *B = (const u8*)vB;
    u64 fail = 0;

    // Accumulate failures, 8 bytes at a time
    int qwords = bytes >> 3;

    if (qwords)
    {
        const u64 *A64 = (const u64 *)A;
        const u64 *B64 = (const u64 *)B;

        for (int ii = 0; ii < qwords; ++ii)
            fail |= A64[ii] ^ B64[ii];

        A = (const u8 *)&A64[qwords];
        B = (const u8 *)&B64[qwords];
    }

    // Accumulate failures, bytes at a time
    bytes &= 7;

    switch (bytes)
    {
    case 7: fail |= A[6] ^ B[6];
    case 6: fail |= A[5] ^ B[5];
    case 5: fail |= A[4] ^ B[4];
    case 4: fail |= *(const u32 *)A ^ *(const u32 *)B;
        break;
    case 3: fail |= A[2] ^ B[2];
    case 2: fail |= A[1] ^ B[1];
    case 1: fail |= A[0] ^ B[0];
    }

    return fail == 0;
}

} // namespace cat
