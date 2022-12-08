/*
 *  Original work: Copyright (c) 2014, Oculus VR, Inc.
 *  All rights reserved.
 *
 *  This source code is licensed under the BSD-style license found in the
 *  RakNet License.txt file in the licenses directory of this source tree. An additional grant 
 *  of patent rights can be found in the RakNet Patents.txt file in the same directory.
 *
 *
 *  Modified work: Copyright (c) 2017, SLikeSoft UG (haftungsbeschränkt)
 *
 *  This source code was modified by SLikeSoft. Modifications are licensed under the MIT-style
 *  license found in the license.txt file in the root directory of this source tree.
 */

#include "slikenet/NativeFeatureIncludes.h"
#if _RAKNET_SUPPORT_CloudClient==1 || _RAKNET_SUPPORT_CloudServer==1

#include "slikenet/CloudCommon.h"
#include "slikenet/BitStream.h"

using namespace SLNet;

int SLNet::CloudKeyComp(const CloudKey &key, const CloudKey &data)
{
	if (key.primaryKey < data.primaryKey)
		return -1;
	if (key.primaryKey > data.primaryKey)
		return 1;
	if (key.secondaryKey < data.secondaryKey)
		return -1;
	if (key.secondaryKey > data.secondaryKey)
		return 1;
	return 0;
}

CloudQueryRow* CloudAllocator::AllocateCloudQueryRow(void)
{
	return SLNet::OP_NEW<CloudQueryRow>(_FILE_AND_LINE_);
}
void CloudAllocator::DeallocateCloudQueryRow(CloudQueryRow *row)
{
	SLNet::OP_DELETE(row,_FILE_AND_LINE_);
}
unsigned char *CloudAllocator::AllocateRowData(uint32_t bytesNeededForData)
{
	return (unsigned char*) rakMalloc_Ex(bytesNeededForData,_FILE_AND_LINE_);
}
void CloudAllocator::DeallocateRowData(void *data)
{
	rakFree_Ex(data, _FILE_AND_LINE_);
}
void CloudKey::Serialize(bool writeToBitstream, BitStream *bitStream)
{
	bitStream->Serialize(writeToBitstream, primaryKey);
	bitStream->Serialize(writeToBitstream, secondaryKey);
}
void CloudQuery::Serialize(bool writeToBitstream, BitStream *bitStream)
{
	bool startingRowIndexIsZero=0;
	bool maxRowsToReturnIsZero=0;
	startingRowIndexIsZero=startingRowIndex==0;
	maxRowsToReturnIsZero=maxRowsToReturn==0;
	bitStream->Serialize(writeToBitstream,startingRowIndexIsZero);
	bitStream->Serialize(writeToBitstream,maxRowsToReturnIsZero);
	bitStream->Serialize(writeToBitstream,subscribeToResults);
	if (startingRowIndexIsZero==false)
		bitStream->Serialize(writeToBitstream,startingRowIndex);
	if (maxRowsToReturnIsZero==false)
		bitStream->Serialize(writeToBitstream,maxRowsToReturn);
	RakAssert(keys.Size()<(uint16_t)-1);
	uint16_t numKeys = (uint16_t) keys.Size();
	bitStream->Serialize(writeToBitstream,numKeys);
	if (writeToBitstream)
	{
		for (uint16_t i=0; i < numKeys; i++)
		{
			keys[i].Serialize(true,bitStream);
		}
	}
	else
	{
		CloudKey cmdk;
		for (uint16_t i=0; i < numKeys; i++)
		{
			cmdk.Serialize(false,bitStream);
			keys.Push(cmdk, _FILE_AND_LINE_);
		}
	}
}
void CloudQueryRow::Serialize(bool writeToBitstream, BitStream *bitStream, CloudAllocator *allocator)
{
	key.Serialize(writeToBitstream,bitStream);
	bitStream->Serialize(writeToBitstream,serverSystemAddress);
	bitStream->Serialize(writeToBitstream,clientSystemAddress);
	bitStream->Serialize(writeToBitstream,serverGUID);
	bitStream->Serialize(writeToBitstream,clientGUID);
	bitStream->Serialize(writeToBitstream,length);
	if (writeToBitstream)
	{
		bitStream->WriteAlignedBytes((const unsigned char*) data,length);
	}
	else
	{
		if (length>0)
		{
			data = allocator->AllocateRowData(length);
			if (data)
			{
				bitStream->ReadAlignedBytes((unsigned char *) data,length);
			}
			else
			{
				notifyOutOfMemory(_FILE_AND_LINE_);
			}
		}
		else
			data=0;
	}
}
void CloudQueryResult::SerializeHeader(bool writeToBitstream, BitStream *bitStream)
{
	cloudQuery.Serialize(writeToBitstream,bitStream);
	bitStream->Serialize(writeToBitstream,subscribeToResults);
}
void CloudQueryResult::SerializeNumRows(bool writeToBitstream, uint32_t &numRows, BitStream *bitStream)
{
	bitStream->Serialize(writeToBitstream,numRows);
}
void CloudQueryResult::SerializeCloudQueryRows(bool writeToBitstream, uint32_t &numRows, BitStream *bitStream, CloudAllocator *allocator)
{
	if (writeToBitstream)
	{
		for (uint16_t i=0; i < numRows; i++)
		{
			rowsReturned[i]->Serialize(true,bitStream, allocator);
		}
	}
	else
	{
		CloudQueryRow* cmdr;
		for (uint16_t i=0; i < numRows; i++)
		{
			cmdr = allocator->AllocateCloudQueryRow();
			if (cmdr)
			{
				cmdr->Serialize(false,bitStream,allocator);
				if (cmdr->data==0 && cmdr->length>0)
				{
					allocator->DeallocateCloudQueryRow(cmdr);
					notifyOutOfMemory(_FILE_AND_LINE_);
					numRows=i;
					return;
				}
				rowsReturned.Push(cmdr, _FILE_AND_LINE_);
			}
			else
			{
				notifyOutOfMemory(_FILE_AND_LINE_);
				numRows=i;
				return;
			}
		}
	}
}
void CloudQueryResult::Serialize(bool writeToBitstream, BitStream *bitStream, CloudAllocator *allocator)
{
	SerializeHeader(writeToBitstream, bitStream);
	uint32_t numRows = (uint32_t) rowsReturned.Size();
	SerializeNumRows(writeToBitstream, numRows, bitStream);
	SerializeCloudQueryRows(writeToBitstream, numRows, bitStream, allocator);
}

#endif // #if _RAKNET_SUPPORT_CloudMemoryClient==1 || _RAKNET_SUPPORT_CloudMemoryServer==1
