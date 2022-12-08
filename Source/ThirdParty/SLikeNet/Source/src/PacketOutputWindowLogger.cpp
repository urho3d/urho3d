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

#include "slikenet/NativeFeatureIncludes.h"
#if _RAKNET_SUPPORT_PacketLogger==1

#if defined(UNICODE)
#include "slikenet/wstring.h"
#endif

#include "slikenet/PacketOutputWindowLogger.h"
#include "slikenet/string.h"
#if defined(_WIN32)
#include "slikenet/WindowsIncludes.h"
#endif

using namespace SLNet;

PacketOutputWindowLogger::PacketOutputWindowLogger()
{
}
PacketOutputWindowLogger::~PacketOutputWindowLogger()
{
}
void PacketOutputWindowLogger::WriteLog(const char *str)
{
#if defined(_WIN32)

	#if defined(UNICODE)
	SLNet::RakWString str2 = str;
		str2+="\n";
		OutputDebugString(str2.C_String());
	#else
	SLNet::RakString str2 = str;
		str2+="\n";
		OutputDebugString(str2.C_String());
	#endif
// DS_APR
#elif defined(__native_client__)
	fprintf(stderr, "%s\n", str);
// /DS_APR
#endif
}

#endif // _RAKNET_SUPPORT_*
