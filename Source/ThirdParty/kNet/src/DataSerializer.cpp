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

/** @file DataSerializer.cpp
	@brief */

#include <cstring>
#include <sstream>
#include <cmath>

#include "kNet/DebugMemoryLeakCheck.h"

#include "kNet/DataSerializer.h"
#include "kNet/BitOps.h"

namespace kNet
{

DataSerializer::DataSerializer(size_t maxBytes_)
{
	assert(maxBytes_ > 0);

	maxBytes = maxBytes_;
	messageData = new SerializedMessage();
	messageData->data.resize(maxBytes);
	data = &messageData->data[0];

	ResetFill();
}

DataSerializer::DataSerializer(size_t maxBytes_, const SerializedMessageDesc *msgTemplate)
{
	assert(maxBytes_ > 0);
	assert(msgTemplate != 0);

	iter = new SerializedDataIterator(*msgTemplate);

	maxBytes = maxBytes_;
	messageData = new SerializedMessage();
	messageData->data.resize(maxBytes);
	data = &messageData->data[0];

	ResetFill();
}

DataSerializer::DataSerializer(char *data_, size_t maxBytes_)
:data(data_), maxBytes(maxBytes_)
{
	ResetFill();
}

DataSerializer::DataSerializer(char *data_, size_t maxBytes_, const SerializedMessageDesc *msgTemplate)
:data(data_), maxBytes(maxBytes_)
{
	assert(msgTemplate != 0);

	iter = new SerializedDataIterator(*msgTemplate);
	ResetFill();
}

DataSerializer::DataSerializer(std::vector<char> &data_, size_t maxBytes_)
{
	if (data_.size() < maxBytes_)
		data_.resize(maxBytes_);
	if (data_.empty() || maxBytes_ == 0)
		throw NetException("Cannot instantiate a DataSerializer object to a zero-sized std::vector-based buffer!");
	data = &data_[0];
	maxBytes = maxBytes_;

	ResetFill();
}

DataSerializer::DataSerializer(std::vector<char> &data_, size_t maxBytes_, const SerializedMessageDesc *msgTemplate)
{
	if (data_.size() < maxBytes_)
		data_.resize(maxBytes_);
	if (data_.empty() || maxBytes_ == 0)
		throw NetException("Cannot instantiate a DataSerializer object to a zero-sized std::vector-based buffer!");
	data = &data_[0];
	maxBytes = maxBytes_;

	if (!msgTemplate)
		throw NetException("Null message template cannot be passed in to DataSerializer ctor!");
	iter = new SerializedDataIterator(*msgTemplate);

	ResetFill();
}

void DataSerializer::AppendByte(u8 byte)
{
	if (bitOfs == 0)
		AppendAlignedByte(byte);
	else
		AppendUnalignedByte(byte);
}

void DataSerializer::AppendUnalignedByte(u8 byte)
{
	// The current partial byte can hold (8-bitOfs) bits.
	data[elemOfs] = (data[elemOfs] & LSB(bitOfs)) | ((byte & LSB(8-bitOfs)) << bitOfs);
	// The next byte can hold full 8 bits, but we only need to add bitOfs bits.
	data[++elemOfs] = byte >> (8-bitOfs);
}

void DataSerializer::AppendAlignedByte(u8 byte)
{
	assert(bitOfs == 0);

	assert(elemOfs < maxBytes);
	data[elemOfs++] = byte;
}

void DataSerializer::AppendBits(u32 value, int amount)
{
	const u8 *bytes = reinterpret_cast<const u8*>(&value);
	while(amount >= 8)
	{
		AppendByte(*bytes);
		++bytes;
		amount -= 8;
	}

	u8 remainder = *bytes & LSB(amount);

	data[elemOfs] = (data[elemOfs] & LSB(bitOfs)) | ((remainder & LSB(8-bitOfs)) << bitOfs);
	if (bitOfs + amount >= 8)
		data[++elemOfs] = remainder >> (8-bitOfs);

	bitOfs = (bitOfs + amount) & 7;
}

void DataSerializer::ResetFill()
{
	if (iter)
		iter->ResetTraversal();
	elemOfs = 0;
	bitOfs = 0;
}

void DataSerializer::AddAlignedByteArray(const void *srcData, u32 numBytes)
{
	assert(bitOfs == 0);
	assert(!iter);
	if (elemOfs + numBytes > maxBytes)
		throw NetException("DataSerializer::AddAlignedByteArray: Attempted to write past the array end buffer!");

	memcpy(&data[elemOfs], srcData, numBytes);
	elemOfs += numBytes;
}

u32 DataSerializer::AddUnsignedFixedPoint(int numIntegerBits, int numDecimalBits, float value)
{
	assert(numIntegerBits >= 0);
	assert(numDecimalBits > 0);
	assert(numIntegerBits + numDecimalBits <= 32);
	const float maxVal = (float)(1 << numIntegerBits);
	const u32 maxBitPattern = (1 << (numIntegerBits + numDecimalBits)) - 1; // All ones - the largest value we can send.
	u32 outVal = value <= 0 ? 0 : (value >= maxVal ? maxBitPattern : (u32)(value * (float)(1 << numDecimalBits)));
	assert(outVal <= maxBitPattern);
	AppendBits(outVal, numIntegerBits + numDecimalBits);
	return outVal;
}

u32 DataSerializer::AddSignedFixedPoint(int numIntegerBits, int numDecimalBits, float value)
{
	// Adding a [-k, k-1] range -> remap to unsigned [0, 2k-1] range and send that instead.
	return AddUnsignedFixedPoint(numIntegerBits, numDecimalBits, value + (float)(1 << (numIntegerBits-1)));
}

static inline float ClampF(float val, float minVal, float maxVal) { return val <= minVal ? minVal : (val >= maxVal ? maxVal : val); }

u32 DataSerializer::AddQuantizedFloat(float minRange, float maxRange, int numBits, float value)
{
	u32 outVal = (u32)((ClampF(value, minRange, maxRange) - minRange) * (float)((1 << numBits)-1) / (maxRange - minRange));
	AppendBits(outVal, numBits);
	return outVal;
}

void DataSerializer::AddMiniFloat(bool signBit, int exponentBits, int mantissaBits, int exponentBias, float value)
{
	// Float structure:
	// 1-bit sign
	// 8-bit exponent
	// 23-bit mantissa
	// s eeeeeeee mmmmmmmmmmmmmmmmmmmmmmm
	// Different float categories:
	// 0 00000000 00000000000000000000000  +zero
	// 1 00000000 00000000000000000000000  -zero
	// s 00000000 mmmmmmmmmmmmmmmmmmmmmmm  A denormal number, mmmmm != 0, interpreted as (-1)^s * 2^-126 * 0.mmmmm
	// s eeeeeeee xxxxxxxxxxxxxxxxxxxxxxx  A normal number, eeeee != 0, interpreted as (-1)^s * 2^(e-127) * 1.mmmmm
	// 0 11111111 00000000000000000000000  +inf
	// 1 11111111 00000000000000000000000  -inf
	// y 11111111 1xxxxxxxxxxxxxxxxxxxxxx  Quiet NaN, y and xxxxx are arbitrary (custom) payload for the NaN.
	// y 11111111 0xxxxxxxxxxxxxxxxxxxxxx  Signalling NaN, y and xxxxx != 0 is arbitrary payload for the NaN.

	// When writing our custom low-precision minifloat, make sure that values in each of the above categories stays in
	// the same category, if possible:
	// +zero: Reducing bits does not affect the value.
	// -zero: Reducing bits does not affect the value. If sending unsigned, -zero becomes +zero.
	// denormals: Reducing bits from mantissa gracefully loses precision. Reducing exponent does not affect the value.
	//            If sending unsigned, negative denormals flush to zero.
	// normals: Reducing bits from exponent can cause the exponent to overflow or underflow.
	//          If the exponent is too large to be encoded, +inf/-inf is sent instead.
	//          If the exponent is too small to be encoded, the value is flushed to zero. \todo Could create a denormal!
	// +inf: Reducing bits does not affect the value.
	// -inf: Reducing bits from exponent or mantissa does not matter. If sending unsigned, -inf flushes to zero.
	// QNaN/SNaN: Reducing bits loses data from the custom NaN payload field. If mantissaBits == 0, cannot differentiat
	//            between QNaN and SNaN.

	assert(sizeof(float) == 4);
	assert(exponentBits > 0);
	assert(exponentBits <= 8);
	assert(mantissaBits > 0);
	assert(mantissaBits <= 23);
	u32 v = *(u32*)&value;
	u32 biasedExponent = (v & 0x7F800000) >> 23;
	u32 mantissa = v & 0x7FFFFF;
	bool sign = (v & 0x80000000) != 0; // If true, the float is negative.

	// Write the sign bit, if sending out a signed minifloat. Otherwise, clamp all negative numbers to +zero.
	if (signBit)
		Add<bit>(sign);
	else if (sign && biasedExponent != 0)
		biasedExponent = mantissa = 0; // If the number was not a NaN, write out +zero.

	// The maximum biased exponent value in the reduced precision representation. This corresponds to NaNs and +/-Infs.
	const u32 maxBiasedExponent = (1 << exponentBits) - 1;

	int trueExponent = biasedExponent - 127; // The true exponent of the float, if this number is a normal number.
	int newBiasedExponent;

	// Compute the new biased exponent value to send.
	if (biasedExponent != 0xFF && biasedExponent != 0) // Is this a normalized float?
	{
		newBiasedExponent = trueExponent + exponentBias;
		
		// Check if the new biased exponent is too large to be represented, and the float overflows to a +/-Inf.
		if (newBiasedExponent >= (int)maxBiasedExponent)
		{
			newBiasedExponent = maxBiasedExponent;
			mantissa = 0; // To specify that this is an Inf and not a NaN.
		}
		// Check if the new biased exponent underflowed. In that case flush to zero.
		///\todo This is not absolutely correct with respect to denormalized numbers. Underflowing
		/// the exponent should produce a denormalized number, but this directly makes it zero.
		if (newBiasedExponent <= 0)
			newBiasedExponent = mantissa = 0;
	}
	else
		newBiasedExponent = biasedExponent; // either all zeroes (+/-zero or denormal) or all ones (nan or inf).

	// Scrap the given number of precision from the mantissa.
	u32 newMantissa = mantissa >> (23 - mantissaBits);

	// If the float was a SNaN, make sure it stays a SNaN after some of the NaN payload was removed.
	if (biasedExponent == 0xFF && mantissa != 0 && newMantissa == 0)
		newMantissa = 1; // Set the mantissa to nonzero to denote a NaN (and don't set the MSB of mantissa, to treat it as SNaN)

	AppendBits(newBiasedExponent, exponentBits);
	AppendBits(newMantissa, mantissaBits);
}

#define PI ((float)3.1415926535897932384626433832795028841971693993751058209749445923078164062862089986280348253421170679)

void DataSerializer::AddNormalizedVector2D(float x, float y, int numBits)
{
	// Call atan2() to get the aimed angle of the 2D vector in the range [-PI, PI], then quantize the 1D result to the desired precision.
	AddQuantizedFloat(-PI, PI, numBits, atan2(y, x));
}

int DataSerializer::AddVector2D(float x, float y, int magnitudeIntegerBits, int magnitudeDecimalBits, int directionBits)
{
	// Compute the length of the vector. Use a fixed-point representation to store the length.
	float length = sqrt(x*x+y*y);
	u32 bitVal = AddUnsignedFixedPoint(magnitudeIntegerBits, magnitudeDecimalBits, length);

	// If length == 0, don't need to send the angle, as it's a zero vector.
	if (bitVal != 0)
	{
		// Call atan2() to get the aimed angle of the 2D vector in the range [-PI, PI], then quantize the 1D result to the desired precision.
		float angle = atan2(y, x);
		AddQuantizedFloat(-PI, PI, directionBits, angle);
		return magnitudeIntegerBits + magnitudeDecimalBits + directionBits;
	}
	else
		return magnitudeIntegerBits + magnitudeDecimalBits;
}

void DataSerializer::AddNormalizedVector3D(float x, float y, float z, int numBitsYaw, int numBitsPitch)
{
	// Convert to spherical coordinates. We assume that the vector (x,y,z) has been normalized beforehand.
	float azimuth = atan2(x, z); // The 'yaw'
	float inclination = asin(-y); // The 'pitch'

	AddQuantizedFloat(-PI, PI, numBitsYaw, azimuth);
	AddQuantizedFloat(-PI/2, PI/2, numBitsPitch, inclination);
}

int DataSerializer::AddVector3D(float x, float y, float z, int numBitsYaw, int numBitsPitch, int magnitudeIntegerBits, int magnitudeDecimalBits)
{
	float length = sqrt(x*x + y*y + z*z);

	u32 bitVal = AddUnsignedFixedPoint(magnitudeIntegerBits, magnitudeDecimalBits, length);

	if (bitVal != 0)
	{
		// The written length was not zero. Send the spherical angles as well.
		float azimuth = atan2(x, z);
		float inclination = asin(-y / length);

		AddQuantizedFloat(-PI, PI, numBitsYaw, azimuth);
		AddQuantizedFloat(-PI/2, PI/2, numBitsPitch, inclination);
		return magnitudeIntegerBits + magnitudeDecimalBits + numBitsYaw + numBitsPitch;
	}
	else // The vector is (0,0,0). Don't send spherical angles as they're redundant.
		return magnitudeIntegerBits + magnitudeDecimalBits;
}

void DataSerializer::AddArithmeticEncoded(int numBits, int val1, int max1, int val2, int max2)
{
	assert(max1 * max2 < (1 << numBits));
	assert(val1 >= 0);
	assert(val1 < max1);
	assert(val2 >= 0);
	assert(val2 < max2);
	AppendBits(val1 * max2 + val2, numBits);
}

void DataSerializer::AddArithmeticEncoded(int numBits, int val1, int max1, int val2, int max2, int val3, int max3)
{
	assert(max1 * max2 * max3 < (1 << numBits));
	assert(val1 >= 0);
	assert(val1 < max1);
	assert(val2 >= 0);
	assert(val2 < max2);
	assert(val3 >= 0);
	assert(val3 < max3);
	AppendBits((val1 * max2 + val2) * max3 + val3, numBits);
}

void DataSerializer::AddArithmeticEncoded(int numBits, int val1, int max1, int val2, int max2, int val3, int max3, int val4, int max4)
{
	assert(max1 * max2 * max3 * max4 < (1 << numBits));
	assert(val1 >= 0);
	assert(val1 < max1);
	assert(val2 >= 0);
	assert(val2 < max2);
	assert(val3 >= 0);
	assert(val3 < max3);
	assert(val4 >= 0);
	assert(val4 < max4);
	AppendBits(((val1 * max2 + val2) * max3 + val3) * max4 + val4, numBits);
}

void DataSerializer::AddArithmeticEncoded(int numBits, int val1, int max1, int val2, int max2, int val3, int max3, int val4, int max4, int val5, int max5)
{
	assert(max1 * max2 * max3 * max4 * max5 < (1 << numBits));
	assert(val1 >= 0);
	assert(val1 < max1);
	assert(val2 >= 0);
	assert(val2 < max2);
	assert(val3 >= 0);
	assert(val3 < max3);
	assert(val4 >= 0);
	assert(val4 < max4);
	assert(val5 >= 0);
	assert(val5 < max5);
	AppendBits((((val1 * max2 + val2) * max3 + val3) * max4 + val4) * max5 + val5, numBits);
}

/// Requires a template to be present to use this.
void DataSerializer::SetVaryingElemSize(u32 count)
{
	assert(iter.ptr() != 0);
	assert(iter->NextElementDesc() != 0);

	AppendBits(count, iter->NextElementDesc()->count);

	iter->SetVaryingElemSize(count);
}

template<>
void DataSerializer::Add<char*>(char * const & value)
{
	AddString(value);
}

template<>
void DataSerializer::Add<const char*>(const char * const & value)
{
	AddString(value);
}

template<>
void DataSerializer::Add<std::string>(const std::string &value)
{
	AddString(value);
}

template<>
void DataSerializer::Add<bit>(const bit &value)
{
	u8 val = (value != 0) ? 1 : 0;
	AppendBits(val, 1);
}

void DataSerializer::AddString(const char *str)
{
	size_t len = strlen(str);
	if (iter)
		SetVaryingElemSize((u32)len);
	else
		AddVLE<VLE8_16_32>(len);

	AddArray<s8>((const s8*)str, len);
}

void DataSerializer::SkipNumBytes(size_t numBytes)
{
	elemOfs += numBytes;
	if (elemOfs + (bitOfs ? 1 : 0) > maxBytes)
		throw NetException("DataSerializer::SkipNumBytes: Attempted to travel past the end of the array!");
}

bool DataSerializer::DebugReadBit(int bitIndex) const
{
	return (data[bitIndex >> 3] & (1 << (bitIndex & 7))) != 0;
}

std::string DataSerializer::DebugReadBits(int startIndex, int endIndex) const
{
	std::stringstream ss;
	for(int i = startIndex; i < endIndex; ++i)
		ss << (DebugReadBit(i) ? "1" : "0");
	return ss.str();
}

} // ~kNet
