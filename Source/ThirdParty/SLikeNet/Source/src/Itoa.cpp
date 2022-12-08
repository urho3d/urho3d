/*
 *  Copyright (c) 2014, Oculus VR, Inc.
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

#include "slikenet/EmptyHeader.h"

#ifdef __cplusplus
extern "C" {
#endif

// Fast itoa from http://www.jb.man.ac.uk/~slowe/cpp/itoa.html for Linux since it seems like Linux doesn't support this function.
// I modified it to remove the std dependencies.
char* Itoa( int value, char* result, int base )
 {
	// check that the base if valid
	if (base < 2 || base > 16) { *result = 0; return result; }
	char* out = result;
	int quotient = value;

	int absQModB;

	do {
		// KevinJ - get rid of this dependency
		//*out = "0123456789abcdef"[ std::abs( quotient % base ) ];
		absQModB=quotient % base;
		if (absQModB < 0)
			absQModB=-absQModB;
		*out = "0123456789abcdef"[ absQModB ];
		++out;
		quotient /= base;
	} while ( quotient );

	// Only apply negative sign for base 10
	if ( value < 0 && base == 10) *out++ = '-';

	// KevinJ - get rid of this dependency
	// std::reverse( result, out );
	*out = 0;

	// KevinJ - My own reverse code
    char *start = result;
	char temp;
	out--;
	while (start < out)
	{
		temp=*start;
		*start=*out;
		*out=temp;
		start++;
		out--;
	}

	return result;
}

#ifdef __cplusplus
}
#endif
