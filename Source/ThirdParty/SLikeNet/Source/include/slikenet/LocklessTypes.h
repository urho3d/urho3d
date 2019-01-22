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

#ifndef __LOCKLESS_TYPES_H
#define __LOCKLESS_TYPES_H

#include "Export.h"
#include "NativeTypes.h"
#include "WindowsIncludes.h"
#if defined(__ANDROID__) || defined(__S3E__) || defined(__APPLE__)
// __sync_fetch_and_add not supported apparently
#include "SimpleMutex.h"
#endif

namespace SLNet
{

class RAK_DLL_EXPORT LocklessUint32_t
{
public:
	LocklessUint32_t();
	explicit LocklessUint32_t(uint32_t initial);
	// Returns variable value after changing it
	uint32_t Increment(void);
	// Returns variable value after changing it
	uint32_t Decrement(void);
	uint32_t GetValue(void) const {return value;}

protected:
#ifdef _WIN32
	volatile LONG value;
#elif defined(__ANDROID__) || defined(__S3E__) || defined(__APPLE__)
	// __sync_fetch_and_add not supported apparently
	SimpleMutex mutex;
	uint32_t value;
#else
	volatile uint32_t value;
#endif
};

}

#endif
