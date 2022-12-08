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

#include "slikenet/FormatString.h"
#include "slikenet/EpochTimeToString.h"
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
// localtime
#include <time.h>
#include "slikenet/LinuxStrings.h"
#include "slikenet/linux_adapter.h"
#include "slikenet/osx_adapter.h"

char * EpochTimeToString(long long time)
{
	static int textIndex=0;
	static char text[4][64];

	if (++textIndex==4)
		textIndex=0;

	struct tm timeinfo;
	time_t t = time;
	localtime_s ( &timeinfo, &t );
	strftime (text[textIndex],64,"%c.",&timeinfo);

	/*
	time_t
	// Copied from the docs
	struct tm *newtime;
	newtime = _localtime64(& time);
	asctime_s( text[textIndex], sizeof(text[textIndex]), newtime );

	while (text[textIndex][0] && (text[textIndex][strlen(text[textIndex])-1]=='\n' || text[textIndex][strlen(text[textIndex])-1]=='\r'))
		text[textIndex][strlen(text[textIndex])-1]=0;
		*/

	return text[textIndex];
}
