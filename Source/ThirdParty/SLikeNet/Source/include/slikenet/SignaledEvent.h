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

#ifndef __SIGNALED_EVENT_H
#define __SIGNALED_EVENT_H



#if   defined(_WIN32)
#include "WindowsIncludes.h"



#else
	#include <pthread.h>
	#include <sys/types.h>
	#include "SimpleMutex.h"




#endif

#include "Export.h"

namespace SLNet
{

class RAK_DLL_EXPORT SignaledEvent
{
public:
	SignaledEvent();
	~SignaledEvent();

	void InitEvent(void);
	void CloseEvent(void);
	void SetEvent(void);
	void WaitOnEvent(int timeoutMs);

protected:
#ifdef _WIN32
	HANDLE eventList;





#else
	SimpleMutex isSignaledMutex;
	bool isSignaled;
#if !defined(__ANDROID__)
	pthread_condattr_t condAttr;
#endif
	pthread_cond_t eventList;
	pthread_mutex_t hMutex;
	pthread_mutexattr_t mutexAttr;
#endif
};

} // namespace SLNet

#endif
