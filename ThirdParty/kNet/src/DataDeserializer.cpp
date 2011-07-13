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

/** @file DataDeserializer.cpp
	@brief */

// Modified by Lasse Öörni for Urho3D

#include <cassert>
#include <cstring>

#include "kNet/DebugMemoryLeakCheck.h"

#include "kNet/DataDeserializer.h"
#include "kNet/NetException.h"

using namespace std;

namespace kNet
{

DataDeserializer::DataDeserializer(const char *data_, size_t size_)
:data(data_), size(size_)
{
	assert(data);
	assert(size > 0);
	ResetTraversal();
}

DataDeserializer::DataDeserializer(const char *data_, size_t size_, const SerializedMessageDesc *msgTemplate)
:data(data_), size(size_)
{
	assert(data);
	assert(size > 0);
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
		assert(elemOfs < size);
		if (elemOfs >= size)
			throw NetException("Ran off past the array in DataDeserializer::ReadBits!");

		var |= (((u32)data[elemOfs] & readMask) >> bitOfs) << bitsFilled;
		bitsFilled += bitsToRead;
		bitOfs += bitsToRead;
		assert(bitOfs <= 8);

		if (bitOfs == 8)
		{
			bitOfs = 0;
			++elemOfs;
		}
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

void DataDeserializer::SkipBits(size_t numBits)
{
	assert(!iter);

	elemOfs += numBits / 8;
	bitOfs += numBits % 8;
	if (bitOfs >= 8)
	{
		bitOfs -= 8;
		++elemOfs;
	}

	if (elemOfs > size)
		throw NetException("Not enough bits left in DataDeserializer::SkipBits!");
	if (elemOfs == size && bitOfs != 0)
		throw NetException("Not enough bits left in DataDeserializer::SkipBits(2)!");
}

std::string DataDeserializer::ReadString()
{
	u32 length = (iter ? GetDynamicElemCount() : Read<u8>());
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
