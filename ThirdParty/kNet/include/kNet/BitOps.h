/* Copyright 2010 Jukka Jylänki

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License. */
#pragma once

/** @file BitOps.h
	@brief Provides bit operation utilities on bitfields. */

#include <cassert>

#include "Types.h"

namespace kNet
{

/// Returns the u32 representation of the given string that consists only of characters '0' and '1'.
u32 BinaryStringToValue(const char *str);

/// Returns the number of bits that are set (ones) in the given value.
inline int CountBitsSet(u32 value)
{
	int bits = 0;
	while(value)
	{
		value &= value - 1;
		++bits;
	}
	return bits;
}

// Clears the LSB bit and returns the zero-based index of where the bit was set.
inline int ExtractLSB(unsigned long *value)
{
	for(int i = 0; i < 32; ++i)
		if ((*value & (1 << i)) != 0)
		{
			*value &= ~(1 << i);
			return i;
		}
	return -1;
}

/** @brief Template-evaluated enum that gives a mask with the Bits LSB bits set.

	For example,
		LSBT<0>::val = 0,
		LSBT<1>::val = 1,
		LSBT<2>::val = 11,
		LSBT<24>::val = 11111111 11111111 11111111. 
	LSBT<33> and greater are undefined. */
template<int Bits>
class LSBT
{
public:
	enum { val = (1 << Bits) - 1 };
};

/// @cond FULL
/** Specialization for LSBT<32> to avoid the undefined result of 1 << 32. */
template<>
class LSBT<32>
{
public:
	enum { val = 0xFFFFFFFF };
};

template<>
class LSBT<31>
{
public:
	enum { val = 0x7FFFFFFF };
};

/// @endcond

/** @return A mask with the given amount of LSB bits set. This is the runtime-equivalent of LSBT.
	LSB(0)==0, LSB(1)==1, LSB(8)=11111111, etc.
	LSB(32) and above are undefined. */
inline u32 LSB(u32 bits)
{
	assert(bits <= 32);
	if (bits >= 32)
		return 0xFFFFFFFF;
	return (1 << bits) - 1;
}

/** @brief A template-computed enum to create a mask of given amount of bits at given position of a u32 variable. 

	For example, 
	BitMaskT<0,0>::val == 0,
	BitMaskT<0,8>::val == 11111111,
	BitMaskT<4, 12>::val == 11111111 11110000, etc.
	If Pos+Bits > 32, the result is undefined. */
template<int Pos, int Bits>
class BitMaskT
{
public:
//	enum { val = (Pow<2, Bits>::val - 1) << Pos };        // Alternate way to calculate this value.
	enum { val = LSBT<Pos+Bits>::val & ~LSBT<Pos>::val }; // But this is nicer.
};

/** @return A mask with the given number of bits set at the given position of a u32 variable. This is 
	the runtime-equivalent of BitMaskT.
	For example, BitMask(4,4)==11110000. */
inline u32 BitMask(u32 pos, u32 bits)
{
	return LSB(pos + bits) & ~LSB(pos);
}

/** @return The given 4 bit fields packed into a single larger bitfield.
	Aggressively templatized version. */
template<typename ResultType, typename InputType,
			int APos, int ABits, int RPos, int RBits,
         int GPos, int GBits, int BPos, int BBits>
ResultType PackBits(InputType a, InputType r, InputType g, InputType b)
{
	return (ResultType)(
		(ResultType)a << APos & BitMaskT<APos, ABits>::val | 
		(ResultType)r << RPos & BitMaskT<RPos, RBits>::val |
		(ResultType)g << GPos & BitMaskT<GPos, GBits>::val |
		(ResultType)b << BPos & BitMaskT<BPos, BBits>::val);
}

/** @return The given 4 bit fields packed into a single larger bitfield. */
template<typename ResultType, typename InputType>
ResultType PackBits(int APos, int ABits, int RPos, int RBits, 
									  int GPos, int GBits, int BPos, int BBits, 
									  InputType a, InputType r, InputType g, InputType b)
{
	return (ResultType)(
		(ResultType)a << APos & BitMask(APos, ABits) | 
		(ResultType)r << RPos & BitMask(RPos, RBits) |
		(ResultType)g << GPos & BitMask(GPos, GBits) |
		(ResultType)b << BPos & BitMask(BPos, BBits));
}

/** Extracts the given adjacent bits from a larger bitfield. Aggressively templatized version.
	For example, ExtractBits<u8, u8, 4, 2> gets the bits 00110000 from a byte,
	shifts them right 4 places and returns the two bits. */
template<typename ResultType, typename InputType, int Pos, int Bits>
void ExtractBits(ResultType &out, const InputType &in)
{
	out = (ResultType)(in >> Pos & BitMaskT<0, Bits>::val);
}

/** Extracts the given adjacent bits from a larger bitfield.
	For example, ExtractBits<u8, u8>(3, 4) gets the bits 01111000 from a byte,
	shifts them right 3 places and returns the four bits. */
template<typename ResultType, typename InputType>
void ExtractBits(int pos, int bits, ResultType &out, const InputType &in)
{
	out = (ResultType)(in >> pos & BitMask(0, bits));
}

} // ~kNet
