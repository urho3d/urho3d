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

/// \file DS_BytePool.h
///


#ifndef __BYTE_POOL_H
#define __BYTE_POOL_H

#include "memoryoverride.h"
#include "DS_MemoryPool.h"
#include "Export.h"
#include "SimpleMutex.h"
#include "assert.h"

// #define _DISABLE_BYTE_POOL
// #define _THREADSAFE_BYTE_POOL

namespace DataStructures
{
	// Allocate some number of bytes from pools.  Uses the heap if necessary.
	class RAK_DLL_EXPORT BytePool
	{
	public:
		BytePool();
		~BytePool();
		// Should be at least 8 times bigger than 8192
		void SetPageSize(int size);
		unsigned char* Allocate(int bytesWanted, const char *file, unsigned int line);
		void Release(unsigned char *data, const char *file, unsigned int line);
		void Clear(const char *file, unsigned int line);
	protected:	
		MemoryPool<unsigned char[128]> pool128;
		MemoryPool<unsigned char[512]> pool512;
		MemoryPool<unsigned char[2048]> pool2048;
		MemoryPool<unsigned char[8192]> pool8192;
#ifdef _THREADSAFE_BYTE_POOL
		SimpleMutex mutex128;
		SimpleMutex mutex512;
		SimpleMutex mutex2048;
		SimpleMutex mutex8192;
#endif
	};
}

#endif
