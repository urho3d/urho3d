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

// Modified by Lasse Öörni for Urho3D

#include <cstring>

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
	messageData->data.Resize(maxBytes);
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
	messageData->data.Resize(maxBytes);
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

DataSerializer::DataSerializer(PODVector<char> &data_, size_t maxBytes_)
{
	if (data_.Size() < maxBytes_)
		data_.Resize(maxBytes_);
	if (data_.Size() == 0 || maxBytes_ == 0)
		throw NetException("Cannot instantiate a DataSerializer object to a zero-sized Vector-based buffer!");
	data = &data_[0];
	maxBytes = maxBytes_;

	ResetFill();
}

DataSerializer::DataSerializer(PODVector<char> &data_, size_t maxBytes_, const SerializedMessageDesc *msgTemplate)
{
	if (data_.Size() < maxBytes_)
		data_.Resize(maxBytes_);
	if (data_.Size() == 0 || maxBytes_ == 0)
		throw NetException("Cannot instantiate a DataSerializer object to a zero-sized Vector-based buffer!");
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
void DataSerializer::Add<String>(const String &value)
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
		SetVaryingElemSize(len);
	else
		Add<u8>(len);

	AddArray<s8>((const s8*)str, len);
}

void DataSerializer::SkipNumBytes(size_t numBytes)
{
	elemOfs += numBytes;
	if (elemOfs + (bitOfs ? 1 : 0) > maxBytes)
		throw NetException("DataSerializer::SkipNumBytes: Attempted to travel past the end of the array!");
}

} // ~kNet
