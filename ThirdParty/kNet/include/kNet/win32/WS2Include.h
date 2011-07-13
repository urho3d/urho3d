/* Copyright 2010 Jukka Jylänki

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License. */
#pragma once

/** @file WS2Include.h
	@brief Use this file to include winsock2.h. This file fixes the issue where winsock2.h has to be included before windows.h.

	The source of this error comes from the fact that if <windows.h> is included before <winsock2.h>, <windows.h> will include
	<winsock.h>, which is the older version of the winsock library. After that, if the user includes winsock2.h, he will get
	compilation errors.

	To fix this problem, do one of the following:

	1) Alter the inclusion order in the compilation unit(s) so that you explicitly #include <winsock2.h> before including
	   windows.h.
	2) Add a #define _WINSOCKAPI_ either to project settings, or at the top of the offending compilation unit (before including 
	   windows.h). Use this solution when you don't want to alter the inclusion order to the proper desired order (winsock2.h 
	   before windows.h)
*/

#if defined(_WINDOWS_) && !defined(_WINSOCK2API_) && defined(FD_CLR)
#error Error: Trying to include winsock2.h after windows.h! This is not allowed! See this file for fix instructions.
#endif

// Remove the manually added #define if it exists so that winsock2.h includes OK.
#if !defined(_WINSOCK2API_) && defined(_WINSOCKAPI_)
#undef _WINSOCKAPI_
#endif

#include <winsock2.h>
#include <ws2tcpip.h>
