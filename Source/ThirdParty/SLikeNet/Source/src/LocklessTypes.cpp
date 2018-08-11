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

#include "slikenet/LocklessTypes.h"

using namespace SLNet;

LocklessUint32_t::LocklessUint32_t()
{
	value=0;
}
LocklessUint32_t::LocklessUint32_t(uint32_t initial)
{
	value=initial;
}
uint32_t LocklessUint32_t::Increment(void)
{
#ifdef _WIN32
	return (uint32_t) InterlockedIncrement(&value);
#elif defined(__ANDROID__) || defined(__S3E__) || defined(__APPLE__)
	uint32_t v;
	mutex.Lock();
	++value;
	v=value;
	mutex.Unlock();
	return v;
#else
	return __sync_fetch_and_add (&value, (uint32_t) 1);
#endif
}
uint32_t LocklessUint32_t::Decrement(void)
{
#ifdef _WIN32
	return (uint32_t) InterlockedDecrement(&value);
#elif defined(__ANDROID__) || defined(__S3E__) || defined(__APPLE__)
	uint32_t v;
	mutex.Lock();
	--value;
	v=value;
	mutex.Unlock();
	return v;
#else
	return __sync_fetch_and_add (&value, (uint32_t) -1);
#endif
}
