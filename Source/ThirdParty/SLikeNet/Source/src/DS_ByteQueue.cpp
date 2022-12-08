/*
 *  Copyright (c) 2014, Oculus VR, Inc.
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

#include "slikenet/DS_ByteQueue.h"
#include <string.h> // Memmove
#include <stdlib.h> // realloc
#include <stdio.h>


using namespace DataStructures;

ByteQueue::ByteQueue()
{
	readOffset=writeOffset=lengthAllocated=0;
	data=0;
}
ByteQueue::~ByteQueue()
{
	Clear(_FILE_AND_LINE_);
	

}
void ByteQueue::WriteBytes(const char *in, unsigned length, const char *file, unsigned int line)
{
	unsigned bytesWritten;
	bytesWritten=GetBytesWritten();
	if (lengthAllocated==0 || length > lengthAllocated-bytesWritten-1)
	{
		unsigned oldLengthAllocated=lengthAllocated;
		// Always need to waste 1 byte for the math to work, else writeoffset==readoffset
		unsigned newAmountToAllocate=length+oldLengthAllocated+1;
		if (newAmountToAllocate<256)
			newAmountToAllocate=256;
		lengthAllocated=lengthAllocated + newAmountToAllocate;
		data=(char*)rakRealloc_Ex(data, lengthAllocated, file, line);
		if (writeOffset < readOffset)
		{
			if (writeOffset <= newAmountToAllocate)
			{
				memcpy(data + oldLengthAllocated, data, writeOffset);
				writeOffset=readOffset+bytesWritten;
			}
			else
			{
				memcpy(data + oldLengthAllocated, data, newAmountToAllocate);
				memmove(data, data+newAmountToAllocate, writeOffset-newAmountToAllocate);
                writeOffset-=newAmountToAllocate;
			}
		}
	}

	if (length <= lengthAllocated-writeOffset)
		memcpy(data+writeOffset, in, length);
	else
	{
		// Wrap
		memcpy(data+writeOffset, in, lengthAllocated-writeOffset);
		memcpy(data, in+(lengthAllocated-writeOffset), length-(lengthAllocated-writeOffset));
	}
	writeOffset=(writeOffset+length) % lengthAllocated;
}
bool ByteQueue::ReadBytes(char *out, unsigned maxLengthToRead, bool peek)
{
	unsigned bytesWritten = GetBytesWritten();
	unsigned bytesToRead = bytesWritten < maxLengthToRead ? bytesWritten : maxLengthToRead;
	if (bytesToRead==0)
		return false;
	if (writeOffset>=readOffset)
	{
		memcpy(out, data+readOffset, bytesToRead);
	}
	else
	{
		unsigned availableUntilWrap = lengthAllocated-readOffset;
		if (bytesToRead <= availableUntilWrap)
		{
			memcpy(out, data+readOffset, bytesToRead);
		}
		else
		{
			memcpy(out, data+readOffset, availableUntilWrap);
			memcpy(out+availableUntilWrap, data, bytesToRead-availableUntilWrap);
		}
	}

	if (peek==false)
		IncrementReadOffset(bytesToRead);
		
	return true;
}
char* ByteQueue::PeekContiguousBytes(unsigned int *outLength) const
{
	if (writeOffset>=readOffset)
		*outLength=writeOffset-readOffset;
	else
		*outLength=lengthAllocated-readOffset;
	return data+readOffset;
}
void ByteQueue::Clear(const char *file, unsigned int line)
{
	if (lengthAllocated)
		rakFree_Ex(data, file, line );
	readOffset=writeOffset=lengthAllocated=0;
	data=0;
}
unsigned ByteQueue::GetBytesWritten(void) const
{
	if (writeOffset>=readOffset)
		return writeOffset-readOffset;
	else
		return writeOffset+(lengthAllocated-readOffset);
}
void ByteQueue::IncrementReadOffset(unsigned length)
{
	readOffset=(readOffset+length) % lengthAllocated;
}
void ByteQueue::DecrementReadOffset(unsigned length)
{
	if (length>readOffset)
		readOffset=lengthAllocated-(length-readOffset);
	else
		readOffset-=length;
}
void ByteQueue::Print(void)
{
	unsigned i;
	for (i=readOffset; i!=writeOffset; i++)
		RAKNET_DEBUG_PRINTF("%i ", data[i]);
	RAKNET_DEBUG_PRINTF("\n");
}
