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
///



#include "slikenet/SimpleMutex.h"
#include "slikenet/assert.h"

using namespace SLNet;




































SimpleMutex::SimpleMutex() //: isInitialized(false)
{







	// Prior implementation of Initializing in Lock() was not threadsafe
	Init();
}

SimpleMutex::~SimpleMutex()
{
// 	if (isInitialized==false)
// 		return;
#ifdef _WIN32
	//	CloseHandle(hMutex);
	DeleteCriticalSection(&criticalSection);






#else
	pthread_mutex_destroy(&hMutex);
#endif







}

#ifdef _WIN32
#ifdef _DEBUG
#include <stdio.h>
#endif
#endif

void SimpleMutex::Lock(void)
{
// 	if (isInitialized==false)
// 		Init();

#ifdef _WIN32
	/*
	DWORD d = WaitForSingleObject(hMutex, INFINITE);
	#ifdef _DEBUG
	if (d==WAIT_FAILED)
	{
	LPVOID messageBuffer;
	FormatMessage(
	FORMAT_MESSAGE_ALLOCATE_BUFFER |
	FORMAT_MESSAGE_FROM_SYSTEM |
	FORMAT_MESSAGE_IGNORE_INSERTS,
	NULL,
	GetLastError(),
	MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
	(LPTSTR) &messageBuffer,
	0,
	NULL
	);
	// Process any inserts in messageBuffer.
	// ...
	// Display the string.
	//MessageBox( NULL, (LPCTSTR)messageBuffer, "Error", MB_OK | MB_ICONINFORMATION );
	RAKNET_DEBUG_PRINTF("SimpleMutex error: %s", messageBuffer);
	// Free the buffer.
	LocalFree( messageBuffer );

	}

	RakAssert(d==WAIT_OBJECT_0);
	*/
	EnterCriticalSection(&criticalSection);






#else
	int error = pthread_mutex_lock(&hMutex);
	(void) error;
	RakAssert(error==0);
#endif
}

void SimpleMutex::Unlock(void)
{
// 	if (isInitialized==false)
// 		return;
#ifdef _WIN32
	//	ReleaseMutex(hMutex);
	LeaveCriticalSection(&criticalSection);






#else
	int error = pthread_mutex_unlock(&hMutex);
	(void) error;
	RakAssert(error==0);
#endif
}

void SimpleMutex::Init(void)
{
#if defined(WINDOWS_PHONE_8) || defined(WINDOWS_STORE_RT)
	InitializeCriticalSectionEx(&criticalSection,0,CRITICAL_SECTION_NO_DEBUG_INFO);
#elif defined(_WIN32)
	//	hMutex = CreateMutex(NULL, FALSE, 0);
	//	RakAssert(hMutex);
	InitializeCriticalSection(&criticalSection);








#else
	int error = pthread_mutex_init(&hMutex, 0);
	(void) error;
	RakAssert(error==0);
#endif
//	isInitialized=true;
}
