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

#include "slikenet/DS_BytePool.h"
#include "slikenet/assert.h"
#ifndef __APPLE__
// Use stdlib and not malloc for compatibility
#include <stdlib.h>
#endif

using namespace DataStructures;

BytePool::BytePool()
{
	pool128.SetPageSize(8192*4);
	pool512.SetPageSize(8192*4);
	pool2048.SetPageSize(8192*4);
	pool8192.SetPageSize(8192*4);
}
BytePool::~BytePool()
{
}
void BytePool::SetPageSize(int size)
{
	pool128.SetPageSize(size);
	pool512.SetPageSize(size);
	pool2048.SetPageSize(size);
	pool8192.SetPageSize(size);
}
unsigned char *BytePool::Allocate(int bytesWanted, const char *file, unsigned int line)
{
#ifdef _DISABLE_BYTE_POOL
	return rakMalloc_Ex(bytesWanted, _FILE_AND_LINE_);
#endif
	unsigned char *out;
	if (bytesWanted <= 127)
	{
		#ifdef _THREADSAFE_BYTE_POOL
		mutex128.Lock();
		#endif
		out = (unsigned char*) pool128.Allocate(file, line);
		#ifdef _THREADSAFE_BYTE_POOL
		mutex128.Unlock();
		#endif
		out[0]=0;
		return ((unsigned char*) out)+1;
	}
	if (bytesWanted <= 511)
	{
		#ifdef _THREADSAFE_BYTE_POOL
		mutex512.Lock();
		#endif
		out = (unsigned char*) pool512.Allocate(file, line);
		#ifdef _THREADSAFE_BYTE_POOL
		mutex512.Unlock();
		#endif
		out[0]=1;
		return ((unsigned char*) out)+1;
	}
	if (bytesWanted <= 2047)
	{
		#ifdef _THREADSAFE_BYTE_POOL
		mutex2048.Lock();
		#endif
		out = (unsigned char*) pool2048.Allocate(file, line);
		#ifdef _THREADSAFE_BYTE_POOL
		mutex2048.Unlock();
		#endif
		out[0]=2;
		return ((unsigned char*) out)+1;
	}
	if (bytesWanted <= 8191)
	{
		#ifdef _THREADSAFE_BYTE_POOL
		mutex8192.Lock();
		#endif
		out = (unsigned char*) pool8192.Allocate(file, line);
		#ifdef _THREADSAFE_BYTE_POOL
		mutex8192.Unlock();
		#endif
		out[0]=3;
		return ((unsigned char*) out)+1;
	}

	out = (unsigned char*) rakMalloc_Ex(bytesWanted+1, _FILE_AND_LINE_);
	out[0]=(unsigned char)255;
	return out+1;
}
void BytePool::Release(unsigned char *data, const char *file, unsigned int line)
{
#ifdef _DISABLE_BYTE_POOL
	_rakFree_Ex(data, _FILE_AND_LINE_ );
#endif
	unsigned char *realData = data-1;
	switch (realData[0])
	{
	case 0:
		#ifdef _THREADSAFE_BYTE_POOL
		mutex128.Lock();
		#endif
		pool128.Release((unsigned char(*)[128]) realData, file, line );
		#ifdef _THREADSAFE_BYTE_POOL
		mutex128.Unlock();
		#endif
		break;
	case 1:
		#ifdef _THREADSAFE_BYTE_POOL
		mutex512.Lock();
		#endif
		pool512.Release((unsigned char(*)[512]) realData, file, line );
		#ifdef _THREADSAFE_BYTE_POOL
		mutex512.Unlock();
		#endif
		break;
	case 2:
		#ifdef _THREADSAFE_BYTE_POOL
		mutex2048.Lock();
		#endif
		pool2048.Release((unsigned char(*)[2048]) realData, file, line );
		#ifdef _THREADSAFE_BYTE_POOL
		mutex2048.Unlock();
		#endif
		break;
	case 3:
		#ifdef _THREADSAFE_BYTE_POOL
		mutex8192.Lock();
		#endif
		pool8192.Release((unsigned char(*)[8192]) realData, file, line );
		#ifdef _THREADSAFE_BYTE_POOL
		mutex8192.Unlock();
		#endif
		break;
	case 255:
		rakFree_Ex(realData, file, line );
		break;
	default:
		RakAssert(0);
		break;
	}
}
void BytePool::Clear(const char *file, unsigned int line)
{
	(void) file;
	(void) line;

#ifdef _THREADSAFE_BYTE_POOL
	pool128.Clear(file, line);
	pool512.Clear(file, line);
	pool2048.Clear(file, line);
	pool8192.Clear(file, line);
#endif
}
