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

/*
    MurmurHash2 is a very fast noncryptographic 32/64-bit hash

    Algorithm by Austin Appleby <aappleby@gmail.com>
    http://murmurhash.googlepages.com/
*/

#ifndef CAT_MURMUR_HASH_2_HPP
#define CAT_MURMUR_HASH_2_HPP

#include <cat/Platform.hpp>

namespace cat {


// NOTE: Result is NOT endian-neutral.  Use getLE().
u32 MurmurHash32(const void *key, int bytes, u32 seed);
u64 MurmurHash64(const void *key, int bytes, u64 seed);


class IncrementalMurmurHash32
{
	u32 _hash, _tail, _count, _size;

    static const u32 M = 0x5bd1e995;
    static const u32 R = 24;

public:
	void Begin(u32 seed = 0);
	void Add(const void *data, int bytes);
	u32 End();
};


class IncrementalMurmurHash64
{
	u32 _count;
	u64 _hash, _tail, _size;

    static const u64 M = 0xc6a4a7935bd1e995ULL;
    static const u64 R = 47;

public:
	void Begin(u64 seed = 0);
	void Add(const void *data, int bytes);
	u64 End();
};


} // namespace cat

#endif // CAT_MURMUR_HASH_2_HPP
