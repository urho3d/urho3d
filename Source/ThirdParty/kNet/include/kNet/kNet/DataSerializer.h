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

/** @file DataSerializer.h
	@brief The class \ref kNet::DataSerializer DataSerializer. Stores POD data to bit streams. */

#include <vector>
#include <cassert>
#include <string>

#include "kNetBuildConfig.h"
#include "kNet/SharedPtr.h"

#include "kNet/MessageListParser.h"
#include "kNet/SerializedDataIterator.h"
#include "kNet/VLEPacker.h"
#include "kNet/DataDeserializer.h"
#include "kNetFwd.h"

namespace kNet
{

struct SerializedMessage : public RefCountable
{
	std::vector<char> data;
};

/// DataSerializer is a helper class that can be used to serialize data types to a stream of raw bits 
/// suitable for disk storage or network transfer.
class DataSerializer
{
public:
	/// Instantiates a new DataSerializer that maintains its own buffer space for serialization.
	/// The size limit for the data to serialize can be specified as an optional parameter.
	///\todo Support dynamic resizing.
	explicit DataSerializer(size_t maxBytes_ = 128 * 1024);
	
	/// Instantiates a new DataSerializer that maintains its own buffer space for serialization and serializes using a template.
	///\todo Support dynamic resizing.
	DataSerializer(size_t maxBytes_, const SerializedMessageDesc *msgTemplate);

	/// Instantiates a new DataSerializer that writes its data into the given fixed-size buffer.
	DataSerializer(char *data_, size_t maxBytes_);

	/// Instantiates a new DataSerializer that writes its data into the given fixed-size buffer, using a message template.
	DataSerializer(char *data_, size_t maxBytes_, const SerializedMessageDesc *msgTemplate);

	/// Instantiates a new DataSerializer that writes to the given vector. 
	/// @param maxBytes The maximum number of bytes that the message can take up space.
	explicit DataSerializer(std::vector<char> &data, size_t maxBytes);

	/// Instantiates a new DataSerializer that writes to the given vector, using a message template. 
	/// @param maxBytes The maximum number of bytes that the message can take up space.
	DataSerializer(std::vector<char> &data, size_t maxBytes, const SerializedMessageDesc *msgTemplate);

	/// Appends a single element of the passed type. If you are using a serialization template to
	/// aid in serialization, the type T may be any of the types bit, u8, s8, u16, s16, u32, s32, u64, s64, float, double, 
	/// const char * or std::string.
	/// If you are not using a serialization template, you may pass in any type that is a POD type and can be reinterpret_casted
	/// to a u8 buffer and memcpy'd to a byte buffer.
	template<typename T>
	void Add(const T &value);

	template<typename VLEType>
	void AddVLE(u32 value);

	/// Appends the given number of bits to the stream.
	/// @param value The variable where the bits are taken from. The bits are read from the LSB first, towards the MSB end of the value.
	/// @param numBits The number of bits to write, in the range [1, 32].
	void AppendBits(u32 value, int numBits);

	/// Adds a given string as length-prepended (not zero-padded). In the message template, use a
	/// parameter of type 's8' with dynamicCount field set to e.g. 8.
	void AddString(const char *str);

	/// See \ref void kNet::DataSerializer::AddString(const char *str); "".
	void AddString(const std::string &str) { AddString(str.c_str()); }

	/// Appends the given amount of elements from the passed array.
	template<typename T>
	void AddArray(const T *data, u32 count);

	/// Adds an array of bytes to the stream. The contents in the stream must be byte-aligned when calling
	/// this function. A serialization template may not be used when calling this function.
	void AddAlignedByteArray(const void *data, u32 numBytes);

	/// Writes the given non-negative float quantized to the given fixed-point precision.
	/// @param value The floating-point value to send. This float must have a value in the range [0, 2^numIntegerBits[.
	/// @param numIntegerBits The number of bits to use to represent the integer part.
	/// @param numDecimalBits The number of bits to use to represent the fractional part.
	/// @note Before writing the value, it is clamped to range specified above to ensure that the written value does not
	///	 result in complete garbage due to over/underflow.
	/// @note The total number of bits written is numIntegerBits + numDecimalBits, which must in total be <= 32.
	/// @return The bit pattern that was written to the buffer.
	u32 AddUnsignedFixedPoint(int numIntegerBits, int numDecimalBits, float value);

	/// Writes the given float quantized to the given fixed-point precision.
	/// @param value The floating-point value to send. This float must have a value in the range [-2^(numIntegerBits-1), 2^(numIntegerBits-1)[.
	/// @param numIntegerBits The number of bits to use to represent the integer part.
	/// @param numDecimalBits The number of bits to use to represent the fractional part.
	/// @note Before writing the value, it is clamped to range specified above to ensure that the written value does not
	///	 result in complete garbage due to over/underflow.
	/// @note The total number of bits written is numIntegerBits + numDecimalBits, which must in total be <= 32.
	/// @return The bit pattern that was written to the buffer.
	u32 AddSignedFixedPoint(int numIntegerBits, int numDecimalBits, float value);

	/// Writes the given float quantized to the number of bits, that are distributed evenly over the range [minRange, maxRange].
	/// @param value The floating-point value to send. This float must have a value in the range [minRange, maxRange].
	/// @param numBits The number of bits to use for representing the value. The total number of different values written is then 2^numBits, 
	///	 which are evenly distributed across the range [minRange, maxRange]. The value numBits must satisfy 1 <= numBits <= 30.
	/// @param minRange The lower limit for the value that is being written.
	/// @param maxRange The upper limit for the value that is being written.
	/// @return The bit pattern that was written to the buffer.
	/// @note This function performs quantization, which results in lossy serialization/deserialization.
	u32 AddQuantizedFloat(float minRange, float maxRange, int numBits, float value);

	/// Writes the given float with a reduced amount of bit precision.
	/// @param signBit If true, a signed float is written (one bit is reserved for sign-magnitude representation).
	///                If false, an unsigned float is written. Negative numbers clamp to zero (-inf -> zero as well).
	/// @param exponentBits The number of bits to use to store the exponent value, in the range [1, 8].
	/// @param mantissaBits The number of bits to use to store the mantissa value, in the range [1, 23].
	/// @param exponentBias For IEEE-754 floats, the signed exponent is converted to unsigned number by adding an offset bias.
	///                This field specifies the bias to use. Usually it is ok to reserve the equal number of exponent values
	///                for negative and positive exponents, meaning that exponentBias == (1 << (exponentBits - 1)) - 1 is an ok default.
	/// @param value The floating point number to encode.
	/// @note This function performs quantization, which results in lossy serialization/deserialization.
	/// @note An example for 8-bit minifloats: signBit==true, exponentBits==3, mantissaBits==4, exponentBias==3.
	/// @note IEEE-754 16-bit 'half16': signBit==true, exponentBits==5, mantissaBits==10, exponentBias==15.
	///       See http://en.wikipedia.org/wiki/Half_precision_floating-point_format
	/// @note IEEE-754 32-bit floats: signBit==true, exponentBits==8, mantissaBits==23, exponentBias==127.
	void AddMiniFloat(bool signBit, int exponentBits, int mantissaBits, int exponentBias, float value);

	/// Writes the given normalized 2D vector compressed to a single 1D polar angle value. Then the angle is quantized to the specified 
	/// precision.
	/// @param x The x coordinate of the 2D vector.
	/// @param y The y coordinate of the 2D vector.
	/// @param numBits The number of bits to quantize the representation down to. This value must satisfy 1 <= numBits <= 30.
	/// @note The vector (x,y) does not need to be normalized for this function to work properly (don't bother enforcing normality in
	///	advance prior to calling this). When deserializing, (x,y) is reconstructed as a normalized direction vector.
	/// @note Do not call this function with (x,y) == (0,0).
	/// @note This function performs quantization, which results in lossy serialization/deserialization.
	void AddNormalizedVector2D(float x, float y, int numBits);

	/// Writes the given 2D vector in polar form and quantized to the given precision.
	/// The length of the 2D vector is stored as fixed-point in magnitudeIntegerBits.magnitudeDecimalBits format.
	/// The direction of the 2D vector is stores with directionBits.
	/// @param x The x coordinate of the 2D vector.
	/// @param y The y coordinate of the 2D vector.
	/// @param magnitudeIntegerBits The number of bits to use for the integral part of the vector's length. This means
	///	 that the maximum length of the vector to be written by this function is < 2^magnitudeIntegerBits.
	/// @param magnitudeDecimalBits The number of bits to use for the fractional part of the vector's length.
	/// @param directionBits The number of bits of precision to use for storing the direction of the 2D vector.
	/// @return The number of bits written to the stream.
	/// @important This function does not write a fixed amount of bits to the stream, but omits the direction if the length is zero. 
	///	 Therefore only use DataDeserializer::ReadVector2D to extract the vector from the buffer.
	int AddVector2D(float x, float y, int magnitudeIntegerBits, int magnitudeDecimalBits, int directionBits);

	/// Writes the given normalized 3D vector converted to spherical form (azimuth/yaw, inclination/pitch) and quantized to the specified range.
	/// The given vector (x,y,z) must be normalized in advance.
	/// @param numBitsYaw The number of bits to use for storing the azimuth/yaw part of the vector.
	/// @param numBitsPitch The number of bits to use for storing the inclination/pitch part of the vector.
	/// @note After converting the euclidean (x,y,z) to spherical (yaw, pitch) format, the yaw value is expressed in the range [-pi, pi] and pitch
	///	 is expressed in the range [-pi/2, pi/2]. Therefore, to maintain consistent precision, the condition numBitsYaw == numBitsPitch + 1 
	///	 should hold. E.g. If you specify 8 bits for numBitsPitch, then you should specify 9 bits for numBitsYaw to have yaw & pitch use the same
	///	 amount of precision.
	/// @note This function uses the convention that the +Y axis points towards up, i.e. +Y is the "Zenith direction", and the X-Z plane is the horizontal
	///	 "map" plane.
	void AddNormalizedVector3D(float x, float y, float z, int numBitsYaw, int numBitsPitch);

	/// Writes the given 3D vector converted to spherical form (azimuth/yaw, inclination/pitch, length) and quantized to the specified range.
	/// @param numBitsYaw The number of bits to use for storing the azimuth/yaw part of the vector.
	/// @param numBitsPitch The number of bits to use for storing the inclination/pitch part of the vector.
	/// @param magnitudeIntegerBits The number of bits to use for the integral part of the vector's length. This means
	///	 that the maximum length of the vector to be written by this function is < 2^magnitudeIntegerBits.
	/// @param magnitudeDecimalBits The number of bits to use for the fractional part of the vector's length.
	/// @return The number of bits written to the stream.
	/// @important This function does not write a fixed amount of bits to the stream, but omits the direction if the length is zero. 
	///	 Therefore only use DataDeserializer::ReadVector3D to extract the vector from the buffer.
	/// @note After converting the euclidean (x,y,z) to spherical (yaw, pitch) format, the yaw value is expressed in the range [-pi, pi] and pitch
	///	 is expressed in the range [-pi/2, pi/2]. Therefore, to maintain consistent precision, the condition numBitsYaw == numBitsPitch + 1 
	///	 should hold. E.g. If you specify 8 bits for numBitsPitch, then you should specify 9 bits for numBitsYaw to have yaw & pitch use the same
	///	 amount of precision.
	/// @note This function uses the convention that the +Y axis points towards up, i.e. +Y is the "Zenith direction", and the X-Z plane is the horizontal
	///	 "map" plane.
	int AddVector3D(float x, float y, float z, int numBitsYaw, int numBitsPitch, int magnitudeIntegerBits, int magnitudeDecimalBits);

	void AddArithmeticEncoded(int numBits, int val1, int max1, int val2, int max2);
	void AddArithmeticEncoded(int numBits, int val1, int max1, int val2, int max2, int val3, int max3);
	void AddArithmeticEncoded(int numBits, int val1, int max1, int val2, int max2, int val3, int max3, int val4, int max4);
	void AddArithmeticEncoded(int numBits, int val1, int max1, int val2, int max2, int val3, int max3, int val4, int max4, int val5, int max5);

	/// Sets the number of instances in a varying element.
	void SetVaryingElemSize(u32 count);

	void ResetFill();

	char *GetData() const { return data; }
	
	/// Advances the stream pointer the given number of bytes. Use this method if you have used an external method
	/// of filling data to the stream.
	void SkipNumBytes(size_t numBytes);

	/// @return The number of bytes filled so far. Partial bits at the end are rounded up to constitute a full byte.
	size_t BytesFilled() const { return elemOfs + ((bitOfs != 0) ? 1 : 0); }

	/// @return The number of bits filled so far total.
	size_t BitsFilled() const { return elemOfs * 8 + bitOfs; }

	/// @return The total capacity of the buffer we are filling into, in bytes.
	size_t Capacity() const { return maxBytes; }

	/// Returns the current byte offset the DataSerializer is writing to.
	size_t ByteOffset() const { return elemOfs; }

	/// Returns the current bit offset in the current byte this DataSerializer is writing to, [0, 7].
	size_t BitOffset() const { return bitOfs; }

    /// Returns the total number of bits that can still be serialized into this DataSerializer object before overflowing (which throws an exception).
    size_t BitsLeft() const { return Capacity()*8 - BitsFilled(); }

    /// Returns the total number of full bytes that can still be serialized into this DataSerializer object before overflowing (which throws an exception).
    /// @return floor(BitsLeft()/8).
    size_t BytesLeft() const { return BitsLeft() / 8; }

	/// Returns the bit serialized at the given bit index of this buffer.
	bool DebugReadBit(int bitIndex) const;

	/// Returns a string of 0's and 1's corresponding to the given bit indices.
	std::string DebugReadBits(int startIndex, int endIndex) const;
private:
	void AppendByte(u8 byte);
	void AppendUnalignedByte(u8 byte);
	void AppendAlignedByte(u8 byte);

	/// Iterator that iterates a template that specifies the elements that are present in the message.
	Ptr(SerializedDataIterator) iter;

	/// Points to the beginning of the data buffer we are filling.
	char *data;

	/// The number of bytes in data.
	size_t maxBytes;

	/// The actual data so far.
	Ptr(SerializedMessage) messageData;
	/// The current element we're filling in the data buffer.
	size_t elemOfs;
	/// The current bit of the element we're filling in the data buffer, [0, 7].
	int bitOfs; 
};

template<typename T>
void DataSerializer::Add(const T &value)
{
#ifdef _DEBUG
	if (iter)
	{
		BasicSerializedDataType nextExpectedType = iter->NextElementType();
		BasicSerializedDataType currentFilledType = SerializedDataTypeTraits<T>::type;
		assert(nextExpectedType == currentFilledType);
	}
#endif
	const u8 *data = reinterpret_cast<const u8*>(&value);

	for(size_t i = 0; i < sizeof(value); ++i)
		AppendByte(data[i]);

	if (iter)
		iter->ProceedToNextVariable();
}

template<> void DataSerializer::Add<char*>(char * const & value);
template<> void DataSerializer::Add<const char*>(const char * const & value);
template<> void DataSerializer::Add<std::string>(const std::string &value);

template<> void DataSerializer::Add<bit>(const bit &value);

template<typename VLEType>
void DataSerializer::AddVLE(u32 value)
{
	assert(!iter); // Can't use with a template.

	u32 encoded = VLEType::Encode(value);
	int numBits = VLEType::GetEncodedBitLength(value);

	if (numBits == 8) Add<u8>((u8)encoded);
	else if (numBits == 16) Add<u16>((u16)encoded);
	else if (numBits == 32) Add<u32>(encoded);
	else
	{
		assert(false && "N/I numBits count! todo.. Write AddBits()"); ///\todo
	}
}

/// Appends the given amount of elements from the passed array.
template<typename T>
void DataSerializer::AddArray(const T *data, u32 count)
{
	for(u32 i = 0; i < count; ++i)
		Add<T>(data[i]); 

	// If the user added an empty array, we have to manually walk to the next variable.
	if (count == 0 && iter)
		iter->ProceedToNextVariable();
}

/// @note This function will be deleted! Use ArraySize instead!
/// Sums up the sizes of each element of an array.
template<typename T>
size_t SumArray(const T &data, size_t numElems)
{
	size_t size = 0;
	for(size_t i = 0; i < numElems; ++i)
		size += data[i].Size();
	return size;
}

template<typename TypeSerializer, typename T>
size_t ArraySize(const T &data, size_t numElems)
{
	size_t size = 0;
	for(size_t i = 0; i < numElems; ++i)
		size += TypeSerializer::Size(data[i]);
	return size;
}

/// TypeSerializer<T> is a helper 'trait' structure for the type 'T', and helps
/// to serialize and deserialize objects of type T. This class is used by
/// the message structure compiler to produce automatically generated message
/// structs from the message XML files.
template<typename T>
class TypeSerializer
{
public:
	static size_t Size(const T &value)
	{
		return value.Size();
	}

	static void SerializeTo(DataSerializer &dst, const T &src)
	{
#ifdef _DEBUG
		size_t bitPos = dst.BitsFilled();
#endif
		src.SerializeTo(dst);
#ifdef _DEBUG
		assert(bitPos + Size(src)*8 == dst.BitsFilled());
#endif
	}

	static void DeserializeFrom(DataDeserializer &src, T &dst)
	{
		dst.DeserializeFrom(src);
	}
};

template<>
class TypeSerializer<std::string>
{
public:
	static size_t Size(const std::string &value)
	{
		return value.length()+1;
	}

	static void SerializeTo(DataSerializer &dst, const std::string &src)
	{
#ifdef _DEBUG
		size_t bitPos = dst.BitsFilled();
#endif
		dst.AddString(src);
#ifdef _DEBUG
		assert(bitPos + Size(src)*8 == dst.BitsFilled());
#endif
	}

	static void DeserializeFrom(DataDeserializer &src, std::string &dst)
	{
		dst = src.ReadString();
	}
};
} // ~kNet
