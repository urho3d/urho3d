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

/** @file DataDeserializer.cpp
	@brief */

#include <cassert>
#include <cstring>
#include <cmath>

#include "kNet/DebugMemoryLeakCheck.h"

#include "kNet/VLEPacker.h"
#include "kNet/DataDeserializer.h"
#include "kNet/NetException.h"

using namespace std;

namespace kNet
{

DataDeserializer::DataDeserializer(const char *data_, size_t size_)
:data(data_), size(size_)
{
	if (!data && size > 0)
		throw NetException("Specified a null input buffer to DataDeserializer, but a nonzero input size!");
	ResetTraversal();
}

DataDeserializer::DataDeserializer(const char *data_, size_t size_, const SerializedMessageDesc *msgTemplate)
:data(data_), size(size_)
{
	if (!data && size > 0)
		throw NetException("Specified a null input buffer to DataDeserializer, but a nonzero input size!");
	assert(msgTemplate);

	iter = new SerializedDataIterator(*msgTemplate);

	ResetTraversal();
}

void DataDeserializer::ResetTraversal()
{
	elemOfs = 0;
	bitOfs = 0;
	if (iter)
		iter->ResetTraversal();
}

u32 DataDeserializer::ReadBitsToU32(int count)
{
	if (BitsLeft() < (u32)count)
		throw NetException("Not enough bits left in DataDeserializer::ReadBits!");

	u32 var = 0;
	int bitsFilled = 0;
	while(count > 0)
	{
		int bitsToRead = std::min(std::min(8, count), 8 - bitOfs);
		u32 readMask = ((1 << bitsToRead) - 1) << bitOfs;
		assert(elemOfs < size); // We already counted above we should have enough bits to read.

		var |= (((u32)data[elemOfs] & readMask) >> bitOfs) << bitsFilled;
		bitsFilled += bitsToRead;
		bitOfs += bitsToRead;
		assert(bitOfs <= 8);

		// If bitOfs has accumulated a full byte, move elemOfs ahead by one.
		elemOfs += (bitOfs >> 3);
		bitOfs &= 7;

		count -= bitsToRead;
	}
	return var;
}

/// Need to have a message template to use this function.
u32 DataDeserializer::GetDynamicElemCount()
{
	const SerializedElementDesc *desc = iter->NextElementDesc();
	assert(desc);

	assert(desc->varyingCount == true);

	if (BitsLeft() < (u32)desc->count)
		throw NetException("Not enough bits left in DataDeserializer::GetDynamicElemCount!");

	u32 count = ReadBitsToU32(desc->count);
	iter->SetVaryingElemSize(count);
	return count;
}

template<>
std::string DataDeserializer::Read<std::string>()
{
	return ReadString();
}

template<>
bool DataDeserializer::Read<bit>()
{
	assert(!iter || iter->NextElementType() == SerialBit);
	bool value = (ReadBitsToU32(1) != 0);

	if (iter)
		iter->ProceedToNextVariable();

	return value;
}

u32 DataDeserializer::ReadBits(int numBits)
{
	assert(!iter || iter->NextElementType() == SerialBit);

	u32 val = ReadBitsToU32(numBits);

	if (iter)
		iter->ProceedNVariables(numBits);

	return val;
}

float DataDeserializer::ReadUnsignedFixedPoint(int numIntegerBits, int numDecimalBits)
{
	u32 fp = ReadBits(numIntegerBits + numDecimalBits);
	return fp / (float)(1 << numDecimalBits);
}

float DataDeserializer::ReadSignedFixedPoint(int numIntegerBits, int numDecimalBits)
{
	// Reading a [0, 2k-1] range -> remap back to [-k, k-1] range.
	return ReadUnsignedFixedPoint(numIntegerBits, numDecimalBits) - (float)(1 << (numIntegerBits-1));
}

float DataDeserializer::ReadQuantizedFloat(float minRange, float maxRange, int numBits)
{
	u32 val = ReadBits(numBits);
	return minRange + val * (maxRange-minRange) / (float)((1 << numBits) - 1);
}

float DataDeserializer::ReadMiniFloat(bool signBit, int exponentBits, int mantissaBits, int exponentBias)
{
	assert(sizeof(float) == 4);
	assert(exponentBits > 0);
	assert(exponentBits <= 8);
	assert(mantissaBits > 0);
	assert(mantissaBits <= 23);

	bool sign = signBit ? Read<bit>() : false;
	u32 exponent = ReadBits(exponentBits);
	u32 mantissa = ReadBits(mantissaBits);

	// Shift back the decoded mantissa to proper position.
	mantissa <<= 23 - mantissaBits;

	// Reconstruct the float exponent.
	if (exponent == (u32)((1 << exponentBits) - 1)) // If the read exponent was all ones, reconstruct 11111111.
		exponent = 0xFF;
	else if (exponent != 0) // If the read exponent was not zero, it was a normal number.
		exponent = exponent - exponentBias + 127;
	// else exponent == 0, meaning a zero or a denormal.

	u32 value = (sign ? 0x80000000 : 0) | (exponent << 23) | mantissa;

	return *(float*)&value;
}

#define PI ((float)3.1415926535897932384626433832795028841971693993751058209749445923078164062862089986280348253421170679)

void DataDeserializer::ReadNormalizedVector2D(int numBits, float &x, float &y)
{
	float angle = ReadQuantizedFloat(-PI, PI, numBits);
	x = cos(angle);
	y = sin(angle);
}

void DataDeserializer::ReadVector2D(int magnitudeIntegerBits, int magnitudeDecimalBits, int directionBits, float &x, float &y)
{
	// Read the length in unsigned fixed point format.
	// The following line is effectively the same as calling ReadUnsignedFixedPoint, but manually perform it
	// to be precisely able to examine whether the length is zero.
	u32 fp = ReadBits(magnitudeIntegerBits + magnitudeDecimalBits);
	if (fp != 0) // If length is non-zero, the stream also contains the direction.
	{
		float length = fp / (float)(1 << magnitudeDecimalBits);

		// Read the direction in the stream.
		float angle = ReadQuantizedFloat(-PI, PI, directionBits);
		x = cos(angle) * length;
		y = sin(angle) * length;
	}
	else // Zero length, no direction present in the buffer.
	{
		x = y = 0.f;
	}
}

void DataDeserializer::ReadNormalizedVector3D(int numBitsYaw, int numBitsPitch, float &x, float &y, float &z)
{
	float azimuth = ReadQuantizedFloat(-PI, PI, numBitsYaw);
	float inclination = ReadQuantizedFloat(-PI/2, PI/2, numBitsPitch);

	float cx = cos(inclination);
	x = cx * sin(azimuth);
	y = -sin(inclination);
	z = cx * cos(azimuth);
}

void DataDeserializer::ReadVector3D(int numBitsYaw, int numBitsPitch, int magnitudeIntegerBits, int magnitudeDecimalBits, float &x, float &y, float &z)
{
	// Read the length in unsigned fixed point format.
	// The following line is effectively the same as calling ReadUnsignedFixedPoint, but manually perform it
	// to be precisely able to examine whether the length is zero.
	u32 fp = ReadBits(magnitudeIntegerBits + magnitudeDecimalBits);
	if (fp != 0) // If length is non-zero, the stream also contains the direction.
	{
		float length = fp / (float)(1 << magnitudeDecimalBits);

		float azimuth = ReadQuantizedFloat(-PI, PI, numBitsYaw);
		float inclination = ReadQuantizedFloat(-PI/2, PI/2, numBitsPitch);

		float cx = cos(inclination);
		x = cx * sin(azimuth) * length;
		y = -sin(inclination) * length;
		z = cx * cos(azimuth) * length;
	}
	else // length is zero, stream does not contain the direction.
	{
		x = y = z = 0.f;
	}
}

void DataDeserializer::ReadArithmeticEncoded(int numBits, int &val1, int max1, int &val2, int max2)
{
	assert(max1 * max2 < (1 << numBits));
	u32 val = ReadBits(numBits);
	val2 = val % max2;
	val1 = val / max2;
}

void DataDeserializer::ReadArithmeticEncoded(int numBits, int &val1, int max1, int &val2, int max2, int &val3, int max3)
{
	assert(max1 * max2 * max3 < (1 << numBits));
	u32 val = ReadBits(numBits);
	val3 = val % max3;
	val /= max3;
	val2 = val % max2;
	val1 = val / max2;
}

void DataDeserializer::ReadArithmeticEncoded(int numBits, int &val1, int max1, int &val2, int max2, int &val3, int max3, int &val4, int max4)
{
	assert(max1 * max2 * max3 * max4 < (1 << numBits));
	u32 val = ReadBits(numBits);
	val4 = val % max4;
	val /= max4;
	val3 = val % max3;
	val /= max3;
	val2 = val % max2;
	val1 = val / max2;
}

void DataDeserializer::ReadArithmeticEncoded(int numBits, int &val1, int max1, int &val2, int max2, int &val3, int max3, int &val4, int max4, int &val5, int max5)
{
	assert(max1 * max2 * max3 * max4 * max5 < (1 << numBits));
	u32 val = ReadBits(numBits);
	val5 = val % max5;
	val /= max5;
	val4 = val % max4;
	val /= max4;
	val3 = val % max3;
	val /= max3;
	val2 = val % max2;
	val1 = val / max2;
}

void DataDeserializer::SkipBits(int numBits)
{
	assert(!iter);

	bitOfs += numBits;
	// Move all accumulated full bytes from bitOfs to elemOfs.
	elemOfs += (bitOfs >> 3);
	bitOfs &= 7;

	if (elemOfs > size)
		throw NetException("Not enough bits left in DataDeserializer::SkipBits!");
	if (elemOfs == size && bitOfs != 0)
		throw NetException("Not enough bits left in DataDeserializer::SkipBits(2)!");
}

std::string DataDeserializer::ReadString()
{
	u32 length = (iter ? GetDynamicElemCount() : ReadVLE<VLE8_16_32>());
	if (BitsLeft() < length*8)
		throw NetException("Not enough bytes left in DataDeserializer::ReadString!");

	std::string str;
	if (bitOfs == 0)
	{
		str.append(data + elemOfs, length);
		elemOfs += length;
	}
	else
	{
		std::vector<u8> bytes(length+1);
		ReadArray<u8>(&bytes[0], length);

		str.append((char*)&bytes[0], length);
	}

	if (iter)
		for(u32 i = 0; i < length; ++i)
			iter->ProceedToNextVariable();

	// Perform string validation: Replace any offending values with the space bar character.
	// Valid values: 0x00 (null), 0x09 (tab), 0x0D, 0x0A (newlines), [32, 253] (characters)
	for(size_t i = 0; i < str.length(); ++i)
		if ((unsigned char)str[i] >= 254 || ((unsigned char)str[i] < 32 && str[i] != 0x0D && str[i] != 0x0A && str[i] != 0x09)) // Retain newlines and tab.
			str[i] = 0x20; // Space bar character

	return str;
}

} // ~kNet
