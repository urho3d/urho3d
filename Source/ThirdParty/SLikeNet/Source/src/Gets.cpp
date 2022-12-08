/*
 *  Copyright (c) 2014, Oculus VR, Inc.
 *  All rights reserved.
 *
 *  This source code is licensed under the BSD-style license found in the
 *  RakNet License.txt file in the licenses directory of this source tree. An additional grant 
 *  of patent rights can be found in the RakNet Patents.txt file in the same directory.
 *
 */

#include <stdio.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

char * Gets ( char * str, int num )
{
	fgets(str, num, stdin);
	if (str[0]=='\n' || str[0]=='\r')
		str[0]=0;

	size_t len=strlen(str);
	if (len>0 && (str[len-1]=='\n' || str[len-1]=='\r'))
		str[len-1]=0;
	if (len>1 && (str[len-2]=='\n' || str[len-2]=='\r'))
		str[len-2]=0;

	return str;
}

#ifdef __cplusplus
}
#endif
