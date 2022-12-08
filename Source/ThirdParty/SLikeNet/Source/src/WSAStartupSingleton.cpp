/*
 *  Original work: Copyright (c) 2014, Oculus VR, Inc.
 *  All rights reserved.
 *
 *  This source code is licensed under the BSD-style license found in the
 *  RakNet License.txt file in the licenses directory of this source tree. An additional grant 
 *  of patent rights can be found in the RakNet Patents.txt file in the same directory.
 *
 *
 *  Modified work: Copyright (c) 2016-2017, SLikeSoft UG (haftungsbeschränkt)
 *
 *  This source code was modified by SLikeSoft. Modifications are licensed under the MIT-style
 *  license found in the license.txt file in the root directory of this source tree.
 */

#include "slikenet/WSAStartupSingleton.h"





#if   defined(_WIN32) && !defined(WINDOWS_STORE_RT)
#include <winsock2.h>
#include <ws2tcpip.h>





#endif
#include "slikenet/defines.h"
#include <stdio.h>

#ifdef _WIN32
#include <tchar.h>
#else
#ifndef _T
#define _T(x) (x)
#endif
#endif

int WSAStartupSingleton::refCount=0;

WSAStartupSingleton::WSAStartupSingleton() {}
WSAStartupSingleton::~WSAStartupSingleton() {}
void WSAStartupSingleton::AddRef(void)
{
#if defined(_WIN32) && !defined(WINDOWS_STORE_RT)

	refCount++;
	
	if (refCount!=1)
		return;





	WSADATA winsockInfo;
	if ( WSAStartup( MAKEWORD( 2, 2 ), &winsockInfo ) != 0 )
	{
#if  defined(_DEBUG) && !defined(WINDOWS_PHONE_8)
		DWORD dwIOError = GetLastError();
		LPTSTR messageBuffer;
		FormatMessage( FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
			NULL, dwIOError, MAKELANGID( LANG_NEUTRAL, SUBLANG_DEFAULT ),  // Default language
			( LPTSTR ) & messageBuffer, 0, NULL );
		// something has gone wrong here...
		RAKNET_DEBUG_TPRINTF( _T("WSAStartup failed:Error code - %lu\n%s"), dwIOError, messageBuffer );
		//Free the buffer.
		LocalFree( messageBuffer );
#endif
	}

#endif
}
void WSAStartupSingleton::Deref(void)
{
#if defined(_WIN32) && !defined(WINDOWS_STORE_RT)
	if (refCount==0)
		return;
		
	if (refCount>1)
	{
		refCount--;
		return;
	}
	
	WSACleanup();





	
	refCount=0;
#endif
}
