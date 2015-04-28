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

/** @file DataDeserializer.h
	@brief The class \ref kNet::DataDeserializer DataDeserializer. */

#include "kNetBuildConfig.h"
#include "kNet/Types.h"

#include "BasicSerializedDataTypes.h"
#include "SerializedDataIterator.h"

namespace kNet
{

/// DataDeserializer is an utility class that walks through and deserializes data in a stream of raw bytes. The stream
/// itself does not contain information about what types of data is contained within, but the user of DataDeserializer must
/// know the contents of the data.
/// DataDeserializer never copies the data it is given to read into an internal memory buffer, but instead it reads
/// the given existing memory buffers. DataDeserializer maintains an internal bit offset position to keep track the position
/// that is currently being read.
class DataDeserializer
{
public:
	/// Constructs a DataDeserializer that reads its data from the given buffer.
	/// DataDeserializer will not copy the contents of the buffer to its own memory area, so
	/// be sure to keep the data alive and unmoved for the duration DataDeserializer exists.
	/// @param data A pointer to the data to deserialize. This may be null, but only if size == 0. If data == 0 and size > 0,
	///            an exception is thrown.
	/// @param size The number of bytes in the input buffer.
	DataDeserializer(const char *data, size_t size);

	/// Constructs a DataDeserializer that reads its data from the given buffer.
	/// DataDeserializer will not copy the contents of the buffer to its own memory area, so
	/// be sure to keep the data alive and unmoved for the duration DataDeserializer exists.
	/// @param data A pointer to the data to deserialize. This may be null, but only if size == 0. If data == 0 and size > 0,
	///            an exception is thrown.
	/// @param size The number of bytes in the input buffer.
	/// @param msgTemplate A pointer to an existing message template structure, which is used
	///        to validate that deserialization of the data proceeds in the defined order.
	///        DataDeserializer does not make a copy of this description, but dereferences
	///        it directly. Be sure to keep it alive for the duration that DataDeserializer exists.
	///        Do not pass in a zero pointer here.
	DataDeserializer(const char *data, size_t size, const SerializedMessageDesc *msgTemplate);

	/// Moves the bit offset position counter to the beginning of the data buffer.
	void ResetTraversal();

	/// Deserializes a single value of type T off the stream and advances the internal read offset.
	template<typename T>
	T Read();

	static const u32 VLEReadError = 0xFFFFFFFF;

	/// Reads a variable-length encoded integer off the stream and advances the internal read offset.
	template<typename VLEType>
	u32 ReadVLE();

	/// Deserializes an array of values of type T off the stream and advances the internal read offset.
	/// @param dst [out] Pointer to an array to receive the read data.
	/// @param numElems The number of elements to read. The array dst must be able to hold that many elements.
	template<typename T>
	void ReadArray(T *dst, size_t numElems);

	/// Reads an ASCII string from the stream. If we are using a template, the template tells how the string is stored.
	/// Otherwise, we are assuming the string was stored length-prepended, using a single byte to denote the length (no null padding).
	/// Use the 's8' data type with dynamicCount set in the message template description for a string variable.
	/// The returned string will only contain ascii values in the range [32, 253], 0x0D, 0x0A, 0x09. Other values will 
	/// be replaced with a space bar character (0x20). Because of this string validation method, do not use this function
	/// to extract binary data of any kind (base64-encoded is fine).
	std::string ReadString();

	/// Reads the given amount of bits and packs them into a u32, which is returned.
	/// @param numBits the number of bits to read, [1, 32].
	u32 ReadBits(int numBits);

	float ReadUnsignedFixedPoint(int numIntegerBits, int numDecimalBits);

	float ReadSignedFixedPoint(int numIntegerBits, int numDecimalBits);

	float ReadQuantizedFloat(float minRange, float maxRange, int numBits);

	float ReadMiniFloat(bool signBit, int exponentBits, int mantissaBits, int exponentBias);

	void ReadNormalizedVector2D(int numBits, float &x, float &y);

	void ReadVector2D(int magnitudeIntegerBits, int magnitudeDecimalBits, int directionBits, float &x, float &y);
	void ReadNormalizedVector3D(int numBitsYaw, int numBitsPitch, float &x, float &y, float &z);
	void ReadVector3D(int numBitsYaw, int numBitsPitch, int magnitudeIntegerBits, int magnitudeDecimalBits, float &x, float &y, float &z);

	void ReadArithmeticEncoded(int numBits, int &val1, int max1, int &val2, int max2);
	void ReadArithmeticEncoded(int numBits, int &val1, int max1, int &val2, int max2, int &val3, int max3);
	void ReadArithmeticEncoded(int numBits, int &val1, int max1, int &val2, int max2, int &val3, int max3, int &val4, int max4);
	void ReadArithmeticEncoded(int numBits, int &val1, int max1, int &val2, int max2, int &val3, int max3, int &val4, int max4, int &val5, int max5);

	u32 GetDynamicElemCount();

	/// @return The number of bytes left in the stream to read.
	u32 BytesLeft() const { return (u32)((elemOfs >= size) ? 0 : (size - elemOfs)); }

	/// @return The number of bits left in the stream to read.
	u32 BitsLeft() const { return (u32)((elemOfs >= size) ? 0 : ((size - elemOfs)*8 - bitOfs)); }

	/// @return The current byte of the stream that will be read next.
	u32 BytePos() const { return (u32)elemOfs; }

	/// @return The bit index, [0, 7] of the byte that will be read next. The reading will proceed from LSBit to MSBit, i.e. 0 -> 7.
	u32 BitPos() const { return bitOfs; }

	/// @return The number of bits read so far in total.
	size_t BitsReadTotal() const { return elemOfs * 8 + bitOfs; }

	/// @return A pointer in the byte stream at the current read position.
	const char *CurrentData() const { return data + BytePos(); }

	/// Advances the read pointer with the given amount of bits. Can only be used in nontemplate read mode.
	void SkipBits(int numBits);

	/// Advances the read pointer with the given amount of bytes. Can only be used in nontemplate read mode.
	void SkipBytes(int numBytes) { SkipBits(numBytes * 8); }

private:
	/// The data pointer to read from.
	const char *data;
	/// The length of the read buffer in bytes.
	size_t size;
	/// The element we're reading next from in the data buffer.
	size_t elemOfs;
	/// The current bit index of the byte we're reading, [0, 7].
	int bitOfs;

	Ptr(SerializedDataIterator) iter;

	u32 ReadBitsToU32(int count);

	DataDeserializer(const DataDeserializer &);
	void operator =(const DataDeserializer &);
};

template<typename T>
T DataDeserializer::Read()
{
	assert(!iter || iter->NextElementType() == SerializedDataTypeTraits<T>::type);
	T value;
	u8 *data = reinterpret_cast<u8*>(&value);

	for(size_t i = 0; i < sizeof(value); ++i)
		data[i] = (u8)ReadBitsToU32(8);

	if (iter)
		iter->ProceedToNextVariable();

	return value;
}

template<> std::string DataDeserializer::Read<std::string>();

template<> bool DataDeserializer::Read<bit>();

template<typename VLEType>
u32 DataDeserializer::ReadVLE()
{
	const u32 cStreamEndError = 0xFFFFFFFF;

	if (BitsLeft() < VLEType::numBits1 + 1)
		return cStreamEndError;

	u32 sml = ReadBits(VLEType::numBits1 + 1);
	if ((sml & (1 << VLEType::numBits1)) == 0)
		return sml;
	sml &= (1 << VLEType::numBits1) - 1;

	const u32 numBitsMed = VLEType::numBits2 + (VLEType::numBits3 == 0 ? 0 : 1);
	if (BitsLeft() < numBitsMed)
		return cStreamEndError;

	u32 med = ReadBits(numBitsMed);
	if ((med & (1 << VLEType::numBits2)) == 0)
		return sml | (med << VLEType::numBits1);

	if (BitsLeft() < (u32)VLEType::numBits3)
		return cStreamEndError;

	med &= (1 << VLEType::numBits2) - 1;
	u32 large = ReadBits(VLEType::numBits3);
	return sml | (med << VLEType::numBits1) | (large << (VLEType::numBits1 + VLEType::numBits2));
}

template<typename T>
void DataDeserializer::ReadArray(T *dst, size_t numElems)
{
	for(size_t i = 0; i < numElems; ++i)
		dst[i] = Read<T>();

	// The above will move on to the next variable in the template accordingly, but if the number
	// of elements to read is zero, it needs to be assumed that this was a dynamic block and 
	// the size was 0.
	if (numElems == 0 && iter)
		iter->ProceedToNextVariable();
}

template<>
void DataDeserializer::ReadArray(bit *dst, size_t numElems);

} // ~kNet
