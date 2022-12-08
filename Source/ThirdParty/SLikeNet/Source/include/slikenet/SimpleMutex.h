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

/// \file
/// \brief \b [Internal] Encapsulates a mutex
///



#ifndef __SIMPLE_MUTEX_H
#define __SIMPLE_MUTEX_H

#include "memoryoverride.h"


#if   defined(_WIN32)
#include "WindowsIncludes.h"


#else
#include <pthread.h>
#include <sys/types.h>
#endif
#include "Export.h"

namespace SLNet
{

/// \brief An easy to use mutex.
/// 
/// I wrote this because the version that comes with Windows is too complicated and requires too much code to use.
/// @remark Previously I used this everywhere, and in fact for a year or two RakNet was totally threadsafe.  While doing profiling, I saw that this function was incredibly slow compared to the blazing performance of everything else, so switched to single producer / consumer everywhere.  Now the user thread of RakNet is not threadsafe, but it's 100X faster than before.
class RAK_DLL_EXPORT SimpleMutex
{
public:

	// Constructor
	SimpleMutex();

	// Destructor
	~SimpleMutex();

	// Locks the mutex.  Slow!
	void Lock(void);

	// Unlocks the mutex.
	void Unlock(void);







private:
	void Init(void);
#ifdef _WIN32
	CRITICAL_SECTION criticalSection; /// Docs say this is faster than a mutex for single process access


#else
	pthread_mutex_t hMutex;
#endif
	// Not threadsafe
	//	bool isInitialized;
};

} // namespace SLNet

#endif

