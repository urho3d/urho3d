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

/**
* @file 
* @brief CheckSum implementation from http://www.flounder.com/checksum.htm
* 
*/
#include "slikenet/CheckSum.h"

/****************************************************************************
*        CheckSum::add
* Inputs:
*   unsigned int d: word to add
* Result: void
* 
* Effect: 
*   Adds the bytes of the unsigned int to the CheckSum
****************************************************************************/

void CheckSum::Add ( unsigned int value )
{
	union
	{
		unsigned int value;
		unsigned char bytes[ 4 ];
	}

	data;
	data.value = value;

	for ( unsigned int i = 0; i < sizeof( data.bytes ); i++ )
		Add ( data.bytes[ i ] )

		;
} // CheckSum::add(unsigned int)

/****************************************************************************
*       CheckSum::add
* Inputs:
*   unsigned short value:
* Result: void
* 
* Effect: 
*   Adds the bytes of the unsigned short value to the CheckSum
****************************************************************************/

void CheckSum::Add ( unsigned short value )
{
	union
	{
		unsigned short value;
		unsigned char bytes[ 2 ];
	}

	data;
	data.value = value;

	for ( unsigned int i = 0; i < sizeof( data.bytes ); i++ )
		Add ( data.bytes[ i ] )

		;
} // CheckSum::add(unsigned short)

/****************************************************************************
*       CheckSum::add
* Inputs:
*   unsigned char value:
* Result: void
* 
* Effect: 
*   Adds the byte to the CheckSum
****************************************************************************/

void CheckSum::Add ( unsigned char value )
{
	unsigned char cipher = (unsigned char)( value ^ ( r >> 8 ) );
	r = ( cipher + r ) * c1 + c2;
	sum += cipher;
} // CheckSum::add(unsigned char)


/****************************************************************************
*       CheckSum::add
* Inputs:
*   LPunsigned char b: pointer to byte array
*   unsigned int length: count
* Result: void
* 
* Effect: 
*   Adds the bytes to the CheckSum
****************************************************************************/

void CheckSum::Add ( unsigned char *b, unsigned int length )
{
	for ( unsigned int i = 0; i < length; i++ )
		Add ( b[ i ] )

		;
} // CheckSum::add(LPunsigned char, unsigned int)
