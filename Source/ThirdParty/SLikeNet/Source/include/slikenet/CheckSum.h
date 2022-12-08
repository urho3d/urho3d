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

///
/// \file CheckSum.cpp
/// \brief [Internal] CheckSum implementation from http://www.flounder.com/checksum.htm
///

#ifndef __CHECKSUM_H
#define __CHECKSUM_H

#include "memoryoverride.h"

/// Generates and validates checksums
class CheckSum
{

public:
	
 /// Default constructor
	
	CheckSum()
	{
		Clear();
	}
	
	void Clear()
	{
		sum = 0;
		r = 55665;
		c1 = 52845;
		c2 = 22719;
	}
	
	void Add ( unsigned int w );
	
	
	void Add ( unsigned short w );
	
	void Add ( unsigned char* b, unsigned int length );
	
	void Add ( unsigned char b );
	
	unsigned int Get ()
	{
		return sum;
	}
	
protected:
	unsigned short r;
	unsigned short c1;
	unsigned short c2;
	unsigned int sum;
};

#endif
