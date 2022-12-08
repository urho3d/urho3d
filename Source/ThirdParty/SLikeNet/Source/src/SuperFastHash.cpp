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

#include "slikenet/SuperFastHash.h"
#include "slikenet/NativeTypes.h"
#include <stdlib.h>

#if !defined(_WIN32)
#include <stdint.h>
#endif
#include "slikenet/linux_adapter.h"
#include "slikenet/osx_adapter.h"

#undef get16bits

#if (defined(__GNUC__) && defined(__i386__)) || defined(__WATCOMC__) \
  || defined(_MSC_VER) || defined (__BORLANDC__) || defined (__TURBOC__)
#define get16bits(d) (*((const uint16_t *) (d)))
#else
#define get16bits(d) ((((uint32_t)(((const uint8_t *)(d))[1])) << 8)\
	+(uint32_t)(((const uint8_t *)(d))[0]) )
#endif

static const int INCREMENTAL_READ_BLOCK=65536;

uint32_t SuperFastHash (const char * data, int length)
{
	// All this is necessary or the hash does not match SuperFastHashIncremental
	int bytesRemaining=length;
	unsigned int lastHash = length;
	int offset=0;
	while (bytesRemaining>=INCREMENTAL_READ_BLOCK)
	{
		lastHash=SuperFastHashIncremental (data+offset, INCREMENTAL_READ_BLOCK, lastHash );
		bytesRemaining-=INCREMENTAL_READ_BLOCK;
		offset+=INCREMENTAL_READ_BLOCK;
	}
	if (bytesRemaining>0)
	{
		lastHash=SuperFastHashIncremental (data+offset, bytesRemaining, lastHash );
	}
	return lastHash;

//	return SuperFastHashIncremental(data,len,len);
}
uint32_t SuperFastHashIncremental (const char * data, int len, unsigned int lastHash )
{
	uint32_t hash = (uint32_t) lastHash;
	uint32_t tmp;
	int rem;

	if (len <= 0 || data == NULL) return 0;

	rem = len & 3;
	len >>= 2;

	/* Main loop */
	for (;len > 0; len--) {
		hash  += get16bits (data);
		tmp    = (get16bits (data+2) << 11) ^ hash;
		hash   = (hash << 16) ^ tmp;
		data  += 2*sizeof (uint16_t);
		hash  += hash >> 11;
	}

	/* Handle end cases */
	switch (rem) {
		case 3: hash += get16bits (data);
			hash ^= hash << 16;
			hash ^= data[sizeof (uint16_t)] << 18;
			hash += hash >> 11;
			break;
		case 2: hash += get16bits (data);
			hash ^= hash << 11;
			hash += hash >> 17;
			break;
		case 1: hash += *data;
			hash ^= hash << 10;
			hash += hash >> 1;
	}

	/* Force "avalanching" of final 127 bits */
	hash ^= hash << 3;
	hash += hash >> 5;
	hash ^= hash << 4;
	hash += hash >> 17;
	hash ^= hash << 25;
	hash += hash >> 6;

	return (uint32_t) hash;

}

uint32_t SuperFastHashFile (const char * filename)
{
	FILE *fp;
	if (fopen_s(&fp, filename, "rb")!=0)
		return 0;
	uint32_t hash = SuperFastHashFilePtr(fp);
	fclose(fp);
	return hash;
}

uint32_t SuperFastHashFilePtr (FILE *fp)
{
	fseek(fp, 0, SEEK_END);
	int length = ftell(fp);
	fseek(fp, 0, SEEK_SET);
	int bytesRemaining=length;
	unsigned int lastHash = length;
	char readBlock[INCREMENTAL_READ_BLOCK];
	while (bytesRemaining>=(int) sizeof(readBlock))
	{
		fread(readBlock, sizeof(readBlock), 1, fp);
		lastHash=SuperFastHashIncremental (readBlock, (int) sizeof(readBlock), lastHash );
		bytesRemaining-=(int) sizeof(readBlock);
	}
	if (bytesRemaining>0)
	{
		fread(readBlock, bytesRemaining, 1, fp);
		lastHash=SuperFastHashIncremental (readBlock, bytesRemaining, lastHash );
	}
	return lastHash;
}
