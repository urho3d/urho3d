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

#ifndef CAT_ENDIAN_NEUTRAL_HPP
#define CAT_ENDIAN_NEUTRAL_HPP

#include <cat/Platform.hpp>

namespace cat {


// getLE() converts from little-endian word to native byte-order word
// getBE() converts from big-endian word to native byte-order word

	template<typename T>
	CAT_INLINE T NoChangeNeeded(const T t)
	{
		return t;
	}

#if defined(CAT_ENDIAN_LITTLE)

# define swapLE(n) NoChangeNeeded(n)
# define getLE(n) NoChangeNeeded(n)
# define getLE16(n) NoChangeNeeded(n)
# define getLE32(n) NoChangeNeeded(n)
# define getLE64(n) NoChangeNeeded(n)

    CAT_INLINE u16 swapBE(u16 &n) { return n = CAT_BOSWAP16(n); }
    CAT_INLINE u32 swapBE(u32 &n) { return n = CAT_BOSWAP32(n); }
    CAT_INLINE u64 swapBE(u64 &n) { return n = CAT_BOSWAP64(n); }
    CAT_INLINE u16 getBE(u16 n) { return CAT_BOSWAP16(n); }
    CAT_INLINE u32 getBE(u32 n) { return CAT_BOSWAP32(n); }
    CAT_INLINE u64 getBE(u64 n) { return CAT_BOSWAP64(n); }
    CAT_INLINE u16 getBE16(u16 n) { return CAT_BOSWAP16(n); }
    CAT_INLINE u32 getBE32(u32 n) { return CAT_BOSWAP32(n); }
    CAT_INLINE u64 getBE64(u64 n) { return CAT_BOSWAP64(n); }
    CAT_INLINE s16 swapBE(s16 &n) { return n = CAT_BOSWAP16((u16)n); }
    CAT_INLINE s32 swapBE(s32 &n) { return n = CAT_BOSWAP32((u32)n); }
    CAT_INLINE s64 swapBE(s64 &n) { return n = CAT_BOSWAP64((u64)n); }
    CAT_INLINE s16 getBE(s16 n) { return CAT_BOSWAP16((u16)n); }
    CAT_INLINE s32 getBE(s32 n) { return CAT_BOSWAP32((u32)n); }
    CAT_INLINE s64 getBE(s64 n) { return CAT_BOSWAP64((u64)n); }

    CAT_INLINE float getBE(float n) {
        Float32 c = n;
        c.i = CAT_BOSWAP32(c.i);
        return c.f;
    }

#elif defined(CAT_ENDIAN_BIG)

# define swapBE(n) NoChangeNeeded(n)
# define getBE(n) NoChangeNeeded(n)
# define getBE16(n) NoChangeNeeded(n)
# define getBE32(n) NoChangeNeeded(n)
# define getBE64(n) NoChangeNeeded(n)

    CAT_INLINE u16 swapLE(u16 &n) { return n = CAT_BOSWAP16(n); }
    CAT_INLINE u32 swapLE(u32 &n) { return n = CAT_BOSWAP32(n); }
    CAT_INLINE u64 swapLE(u64 &n) { return n = CAT_BOSWAP64(n); }
    CAT_INLINE u16 getLE(u16 n) { return CAT_BOSWAP16(n); }
    CAT_INLINE u32 getLE(u32 n) { return CAT_BOSWAP32(n); }
    CAT_INLINE u64 getLE(u64 n) { return CAT_BOSWAP64(n); }
    CAT_INLINE u16 getLE16(u16 n) { return CAT_BOSWAP16(n); }
    CAT_INLINE u32 getLE32(u32 n) { return CAT_BOSWAP32(n); }
    CAT_INLINE u64 getLE64(u64 n) { return CAT_BOSWAP64(n); }
    CAT_INLINE s16 swapLE(s16 &n) { return n = CAT_BOSWAP16((u16)n); }
    CAT_INLINE s32 swapLE(s32 &n) { return n = CAT_BOSWAP32((u32)n); }
    CAT_INLINE s64 swapLE(s64 &n) { return n = CAT_BOSWAP64((u64)n); }
    CAT_INLINE s16 getLE(s16 n) { return CAT_BOSWAP16((u16)n); }
    CAT_INLINE s32 getLE(s32 n) { return CAT_BOSWAP32((u32)n); }
    CAT_INLINE s64 getLE(s64 n) { return CAT_BOSWAP64((u64)n); }

    CAT_INLINE float getLE(float n) {
        Float32 c = n;
        c.i = CAT_BOSWAP32(c.i);
        return c.f;
    }

#elif defined(CAT_ENDIAN_UNKNOWN)

	class RuntimeEndianDetector
	{
	public:
		bool _big_endian, _little_endian;

		RuntimeEndianDetector();
	};

	class Endianness
	{
	public:
		static RuntimeEndianDetector detector;
		static CAT_INLINE bool IsBigEndian() { return detector._big_endian; }
		static CAT_INLINE bool IsLittleEndian() { return detector._little_endian; }
	};

	CAT_INLINE u16 swapBE(u16 &n) { return Endianness::IsBigEndian() ? n : n = CAT_BOSWAP16(n); }
	CAT_INLINE u32 swapBE(u32 &n) { return Endianness::IsBigEndian() ? n : n = CAT_BOSWAP32(n); }
	CAT_INLINE u64 swapBE(u64 &n) { return Endianness::IsBigEndian() ? n : n = CAT_BOSWAP64(n); }
	CAT_INLINE u16 getBE(u16 n) { return Endianness::IsBigEndian() ? n : CAT_BOSWAP16(n); }
	CAT_INLINE u32 getBE(u32 n) { return Endianness::IsBigEndian() ? n : CAT_BOSWAP32(n); }
	CAT_INLINE u64 getBE(u64 n) { return Endianness::IsBigEndian() ? n : CAT_BOSWAP64(n); }
	CAT_INLINE u16 getBE16(u16 n) { return Endianness::IsBigEndian() ? n : CAT_BOSWAP16(n); }
	CAT_INLINE u32 getBE32(u32 n) { return Endianness::IsBigEndian() ? n : CAT_BOSWAP32(n); }
	CAT_INLINE u64 getBE64(u64 n) { return Endianness::IsBigEndian() ? n : CAT_BOSWAP64(n); }
	CAT_INLINE s16 swapBE(s16 &n) { return Endianness::IsBigEndian() ? n : n = CAT_BOSWAP16((u16)n); }
	CAT_INLINE s32 swapBE(s32 &n) { return Endianness::IsBigEndian() ? n : n = CAT_BOSWAP32((u32)n); }
	CAT_INLINE s64 swapBE(s64 &n) { return Endianness::IsBigEndian() ? n : n = CAT_BOSWAP64((u64)n); }
	CAT_INLINE s16 getBE(s16 n) { return Endianness::IsBigEndian() ? n : CAT_BOSWAP16((u16)n); }
	CAT_INLINE s32 getBE(s32 n) { return Endianness::IsBigEndian() ? n : CAT_BOSWAP32((u32)n); }
	CAT_INLINE s64 getBE(s64 n) { return Endianness::IsBigEndian() ? n : CAT_BOSWAP64((u64)n); }

	CAT_INLINE float getBE(float n)
	{
		if (Endianness::IsBigEndian())
			return n;
		else
		{
			Float32 c = n;
			c.i = CAT_BOSWAP32(c.i);
			return c.f;
		}
	}

	CAT_INLINE u16 swapLE(u16 &n) { return Endianness::IsLittleEndian() ? n : n = CAT_BOSWAP16(n); }
	CAT_INLINE u32 swapLE(u32 &n) { return Endianness::IsLittleEndian() ? n : n = CAT_BOSWAP32(n); }
	CAT_INLINE u64 swapLE(u64 &n) { return Endianness::IsLittleEndian() ? n : n = CAT_BOSWAP64(n); }
	CAT_INLINE u16 getLE(u16 n) { return Endianness::IsLittleEndian() ? n : CAT_BOSWAP16(n); }
	CAT_INLINE u32 getLE(u32 n) { return Endianness::IsLittleEndian() ? n : CAT_BOSWAP32(n); }
	CAT_INLINE u64 getLE(u64 n) { return Endianness::IsLittleEndian() ? n : CAT_BOSWAP64(n); }
	CAT_INLINE u16 getLE16(u16 n) { return Endianness::IsLittleEndian() ? n : CAT_BOSWAP16(n); }
	CAT_INLINE u32 getLE32(u32 n) { return Endianness::IsLittleEndian() ? n : CAT_BOSWAP32(n); }
	CAT_INLINE u64 getLE64(u64 n) { return Endianness::IsLittleEndian() ? n : CAT_BOSWAP64(n); }
	CAT_INLINE s16 swapLE(s16 &n) { return Endianness::IsLittleEndian() ? n : n = CAT_BOSWAP16((u16)n); }
	CAT_INLINE s32 swapLE(s32 &n) { return Endianness::IsLittleEndian() ? n : n = CAT_BOSWAP32((u32)n); }
	CAT_INLINE s64 swapLE(s64 &n) { return Endianness::IsLittleEndian() ? n : n = CAT_BOSWAP64((u64)n); }
	CAT_INLINE s16 getLE(s16 n) { return Endianness::IsLittleEndian() ? n : CAT_BOSWAP16((u16)n); }
	CAT_INLINE s32 getLE(s32 n) { return Endianness::IsLittleEndian() ? n : CAT_BOSWAP32((u32)n); }
	CAT_INLINE s64 getLE(s64 n) { return Endianness::IsLittleEndian() ? n : CAT_BOSWAP64((u64)n); }

	CAT_INLINE float getLE(float n)
	{
		if (Endianness::IsLittleEndian())
			return n;
		else
		{
			Float32 c = n;
			c.i = CAT_BOSWAP32(c.i);
			return c.f;
		}
	}

#endif


} // namespace cat

#endif // CAT_ENDIAN_NEUTRAL_HPP
