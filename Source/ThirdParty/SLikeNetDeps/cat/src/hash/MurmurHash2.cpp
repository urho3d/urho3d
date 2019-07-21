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

#include <cat/hash/MurmurHash2.hpp>
#include <cat/port/EndianNeutral.hpp>
using namespace cat;

#define mmix(h, k) { k *= M; k ^= k >> R; k *= M; h *= M; h ^= k; }

u32 cat::MurmurHash32(const void *key, int bytes, u32 seed)
{
    const u32 M = 0x5bd1e995;
    const u32 R = 24;

    // Mix 4 bytes at a time into the hash
    const u32 *key32 = (const u32 *)key;
    const u32 *key32_end = key32 + bytes/sizeof(u32);
    u32 h = seed;

    while (key32 != key32_end)
    {
        u32 k = getLE(*key32++);

		mmix(h, k);
    }

    // Handle the last few bytes of the input array
    const u8 *key8 = (const u8 *)key32;
    u32 t = 0;

    switch (bytes & 3)
    {
    case 3: t ^= (u32)key8[2] << 16;
    case 2: t ^= (u32)key8[1] << 8;
    case 1: t ^= key8[0];
    };

	mmix(h, t);

	u32 k = bytes;
	mmix(h, k);

    h ^= h >> 13;
    h *= M;
    h ^= h >> 15;

    return h;
}

u64 cat::MurmurHash64(const void *key, int bytes, u64 seed)
{
    const u64 M = 0xc6a4a7935bd1e995ULL;
    const u64 R = 47;

    // Mix 8 bytes at a time into the hash
    const u64 *key64 = (const u64 *)key;
    const u64 *key64_end = key64 + bytes/sizeof(u64);
    u64 h = seed;

    while (key64 != key64_end)
    {
        u64 k = getLE(*key64++);

		mmix(h, k);
    }

    // Handle the last few bytes of the input array
    const u8 *key8 = (const u8 *)key64;
	u64 t = 0;

    switch (bytes & 7)
    {
    case 7: t ^= (u64)key8[6] << 48;
    case 6: t ^= (u64)key8[5] << 40;
    case 5: t ^= (u64)key8[4] << 32;
    case 4: t ^= getLE(*(u32*)key8);
            break;
    case 3: t ^= (u64)key8[2] << 16;
    case 2: t ^= (u64)key8[1] << 8;
    case 1: t ^= key8[0];
    };

	mmix(h, t);

	u64 k = bytes;
	mmix(h, k);

    h ^= h >> R;
    h *= M;
    h ^= h >> R;

    return h;
}


//// 32-bit incremental Murmur hash

void IncrementalMurmurHash32::Begin(u32 seed)
{
	_hash = seed;
	_tail = 0;
	_size = 0;
	_count = 0;
}

void IncrementalMurmurHash32::Add(const void *data, int bytes)
{
	// If there is no input, abort
	if (!bytes) return;

	// Accumulate size of input
	_size += bytes;

	// Prepare to walk the data one byte at a time
	const u8 *key8 = (const u8 *)data;

	// If there is any data left over from last Add(),
	if (_count)
	{
		// Accumulate new data into _tail (little-endian)
		do _tail = (_tail >> 8) | (*key8++ << 24);
		while (++_count < 4 && --bytes > 0);

		// If a full word has been accumulated,
		if (_count == 4)
		{
			// Mix it in
			u32 k = _tail;
			mmix(_hash, k);

			// Reset accumulator state
			_tail = 0;
			_count = 0;
		}

		// If no more data is left, abort
		if (!bytes) return;
	}

    // Mix 4 bytes at a time into the hash
    const u32 *key32 = (const u32 *)key8;
    const u32 *key32_end = key32 + bytes/sizeof(u32);

    while (key32 != key32_end)
    {
        u32 k = getLE(*key32++);

		mmix(_hash, k);
    }

    // Handle the last few bytes of the input array
	key8 = (const u8 *)key32_end;
	bytes &= 3;
	_count = bytes;

	// If any data is left over, accumulate it into _tail (little-endian)
	while (bytes--) _tail = (_tail >> 8) | (*key8++ << 24);
}

u32 IncrementalMurmurHash32::End()
{
	// Mix in any data that didn't fit
	u32 k1 = _tail;
	mmix(_hash, k1);

	// Mix in the overall size of the data
	u32 k2 = _size;
	mmix(_hash, k2);

	// Final mix
    _hash ^= _hash >> 13;
    _hash *= M;
    _hash ^= _hash >> 15;

    return _hash;
}


//// 64-bit incremental Murmur hash

void IncrementalMurmurHash64::Begin(u64 seed)
{
	_hash = seed;
	_tail = 0;
	_size = 0;
	_count = 0;
}

void IncrementalMurmurHash64::Add(const void *data, int bytes)
{
	// If there is no input, abort
	if (!bytes) return;

	// Accumulate size of input
	_size += bytes;

	// Prepare to walk the data one byte at a time
	const u8 *key8 = (const u8 *)data;

	// If there is any data left over from last Add(),
	if (_count)
	{
		// Accumulate new data into _tail (little-endian)
		do _tail = (_tail >> 8) | ((u64)*key8++ << 56);
		while (++_count < 8 && --bytes > 0);

		// If a full word has been accumulated,
		if (_count == 8)
		{
			// Mix it in
			u64 k = _tail;
			mmix(_hash, k);

			// Reset accumulator state
			_tail = 0;
			_count = 0;
		}

		// If no more data is left, abort
		if (!bytes) return;
	}

    // Mix 4 bytes at a time into the hash
    const u64 *key64 = (const u64 *)key8;
    const u64 *key64_end = key64 + bytes/sizeof(u64);

    while (key64 != key64_end)
    {
        u64 k = getLE(*key64++);

		mmix(_hash, k);
    }

    // Handle the last few bytes of the input array
	key8 = (const u8 *)key64_end;
	bytes &= 7;
	_count = bytes;

	// If any data is left over, accumulate it into _tail (little-endian)
	while (bytes--) _tail = (_tail >> 8) | ((u64)*key8++ << 56);
}

u64 IncrementalMurmurHash64::End()
{
	// Mix in any data that didn't fit
	u64 k1 = _tail;
	mmix(_hash, k1);

	// Mix in the overall size of the data
	u64 k2 = _size;
	mmix(_hash, k2);

	// Final mix
    _hash ^= _hash >> R;
    _hash *= M;
    _hash ^= _hash >> R;

    return _hash;
}
