/* Copyright The kNet Project.

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

/** @file VLEPacker.h
	@brief The VLEType2<int,int> and VLEType3<int,int,int> template classes. */

#include "BitOps.h"
#include "NetException.h"

namespace kNet
{

/// VLEPacker performs variable-length encoding of unsigned integer values by omitting leading
/// zeroes from big numbers.
template<int bits1, int bits2>
class VLEType2
{
public:
	static const int numBits1 = bits1;
	static const int numBits2 = bits2;

	// For compatibility when inter-using with VLEType3
	static const int numBits3 = 0;

	static const u32 maxValue1 = static_cast<u32>(LSBT<numBits1>::val);
	static const u32 maxValue2 = static_cast<u32>(LSBT<numBits1+numBits2>::val);

	static const u32 maxValue = maxValue2;

	static const u32 bitsValue1 = numBits1 + 1;
	static const u32 bitsValue2 = numBits1 + 1 + numBits2;

	static const u32 maxBits = bitsValue2;

	static const u32 bitMask1 = static_cast<u32>(BitMaskT<0, numBits1>::val);
	static const u32 bitMask2 = static_cast<u32>(BitMaskT<bitsValue1, numBits2>::val);// == ((1 << numBits2) - 1) << bitsValue1;

	static int GetEncodedBitLength(u32 value)
	{
		if (value <= maxValue1)
			return bitsValue1;
		else
			return bitsValue2;
	}

	static u32 Encode(u32 value)
	{
		if (value > maxValue)
			throw NetException("VLEType2::Encode: Trying to encode too large value!");
		if (value <= maxValue1)
			return value;
		else
		{
			if (value > maxValue)
				value = maxValue;

			u32 lowPart = value & BitMaskT<0, numBits1>::val;
			u32 medPart = value & BitMaskT<numBits1, numBits2>::val;
			assert(medPart != 0);
			return lowPart | (1 << numBits1) | (medPart << 1);
		}
	}
	
	static u32 Decode(u32 value)
	{
		if ((value & (1 << numBits1)) == 0)
			return value;
		else
		{
			u32 lowPart = value & BitMaskT<0, numBits1>::val;
			u32 medPart = value & BitMaskT<numBits1+1, numBits2>::val;
			return lowPart | (medPart >> 1);
		}
	}
};

/// VLEPacker performs variable-length encoding of unsigned integer values by omitting leading
/// zeroes from big numbers.
template<int bits1, int bits2, int bits3>
class VLEType3
{
public:
	static const int numBits1 = bits1;
	static const int numBits2 = bits2;
	static const int numBits3 = bits3;

	static const u32 maxValue1 = static_cast<u32>(LSBT<numBits1>::val);
	static const u32 maxValue2 = static_cast<u32>(LSBT<numBits1+numBits2>::val);
	static const u32 maxValue3 = static_cast<u32>(LSBT<numBits1+numBits2+numBits3>::val);

	static const u32 maxValue = maxValue3;

	static const u32 bitsValue1 = numBits1 + 1;
	static const u32 bitsValue2 = numBits1 + 1 + numBits2 + 1;
	static const u32 bitsValue3 = numBits1 + 1 + numBits2 + 1 + numBits3;

	static const u32 maxBits = bitsValue3;

	static const u32 bitMask1 = static_cast<u32>(BitMaskT<0, numBits1>::val);
	static const u32 bitMask2 = static_cast<u32>(BitMaskT<bitsValue1, numBits2>::val); // == ((1 << numBits2) - 1) << bitsValue1;
	static const u32 bitMask3 = static_cast<u32>(BitMaskT<bitsValue2, numBits3>::val); // == ((1 << numBits3) - 1) << bitsValue2;

	static int GetEncodedBitLength(u32 value)
	{
		if (value <= maxValue1)
			return bitsValue1;
		else if (value <= maxValue2)
			return bitsValue2;
		else
			return bitsValue3;
	}

	static u32 Encode(u32 value)
	{
		if (value > maxValue)
			throw NetException("VLEType2::Encode: Trying to encode too large value!");

		if (value > maxValue)
			value = maxValue;

		if (value <= maxValue1)
			return value;
		else if (value <= maxValue2)
		{
			u32 lowPart = value & BitMaskT<0, numBits1>::val;
			u32 medPart = value & BitMaskT<numBits1, numBits2>::val;
			assert(medPart != 0);
			return lowPart | (1 << numBits1) | (medPart << 1);
		}
		else
		{
			u32 lowPart = value & BitMaskT<0, numBits1>::val;
			u32 medPart = value & BitMaskT<numBits1, numBits2>::val;
			u32 highPart = value & BitMaskT<numBits1+numBits2, numBits3>::val;
			assert(highPart != 0);
			return lowPart | (1 << numBits1) | (medPart << 1) | (1 << (bitsValue1 + numBits2)) | (highPart << 2);
		}
	}
	
	static u32 Decode(u32 value)
	{
		if ((value & (1 << numBits1)) == 0)
			return value;
		else if ((value & (1 << (bitsValue1 + numBits2))) == 0)
		{
			u32 lowPart = value & BitMaskT<0, numBits1>::val;
			u32 medPart = value & BitMaskT<numBits1+1, numBits2>::val;
			return lowPart | (medPart >> 1);
		}
		else
		{
			u32 lowPart = value & BitMaskT<0, numBits1>::val;
			u32 medPart = (value & BitMaskT<numBits1+1, numBits2>::val);
			u32 highPart = (value & BitMaskT<numBits1+1+numBits2+1, numBits3>::val);
			return lowPart | (medPart >> 1) | (highPart >> 2);
		}
	}
};

typedef VLEType3<7, 7, 16> VLE8_16_32;
typedef VLEType2<7, 8> VLE8_16;
typedef VLEType2<7, 24> VLE8_32;
typedef VLEType2<15, 16> VLE16_32;

} // ~kNet
