/*
 *  Original work: Copyright (c) 2014, Oculus VR, Inc.
 *  All rights reserved.
 *
 *  This source code is licensed under the BSD-style license found in the
 *  RakNet License.txt file in the licenses directory of this source tree. An additional grant 
 *  of patent rights can be found in the RakNet Patents.txt file in the same directory.
 *
 *
 *  Modified work: Copyright (c) 2016, SLikeSoft UG (haftungsbeschränkt)
 *
 *  This source code was modified by SLikeSoft. Modifications are licensed under the MIT-style
 *  license found in the license.txt file in the root directory of this source tree.
 */

#ifndef _GCC_WIN_STRINGS
#define _GCC_WIN_STRINGS

#if  defined(__native_client__)
	#ifndef _stricmp
		int _stricmp(const char* s1, const char* s2);
	#endif
	int _strnicmp(const char* s1, const char* s2, size_t n);
	char *_strlwr(char * str );
#else
 #if (defined(__GNUC__)  || defined(__GCCXML__) || defined(__S3E__) ) && !defined(_WIN32)
		#ifndef _stricmp
			int _stricmp(const char* s1, const char* s2);
		#endif 
		int _strnicmp(const char* s1, const char* s2, size_t n);
		// http://www.jenkinssoftware.com/forum/index.php?topic=5010.msg20920#msg20920
#ifndef __APPLE__
		char *_strlwr(char * str ); //this won't compile on OSX for some reason
#endif



	#endif
#endif

#endif // _GCC_WIN_STRINGS
