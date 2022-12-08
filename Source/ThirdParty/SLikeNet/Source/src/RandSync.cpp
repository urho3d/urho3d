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

#include "slikenet/RandSync.h"
#include "slikenet/BitStream.h"
#include <limits>
#include <limits.h>

namespace SLNet
{

RakNetRandomSync::RakNetRandomSync()
{
	seed = (uint32_t) -1;
	callCount = 0;
	usedValueBufferCount = 0;
}
RakNetRandomSync::~RakNetRandomSync()
{
}
void RakNetRandomSync::SeedMT( uint32_t _seed )
{
	seed = _seed;
	rnr.SeedMT( seed );
	callCount = 0;
	usedValueBufferCount = 0;
}
void RakNetRandomSync::SeedMT( uint32_t _seed, uint32_t skipValues )
{
	SeedMT(_seed);
	Skip(skipValues);
}
float RakNetRandomSync::FrandomMT( void )
{
	return ( float ) ( ( double ) RandomMT() / (double) UINT_MAX );
}
unsigned int RakNetRandomSync::RandomMT( void )
{
	if (usedValueBufferCount > 0)
	{
		--usedValueBufferCount;
		if (usedValueBufferCount < usedValues.Size())
		{
			// The remote system had less calls than the current system, so return values from the past
			return usedValues[usedValues.Size()-usedValueBufferCount-1];
		}
		else
		{
			// Unknown past value, too far back
			// Return true random
			return rnr.RandomMT();
		}
	}
	else
	{
		// Get random number and store what it is
		usedValues.Push(rnr.RandomMT(), _FILE_AND_LINE_);
		++callCount;
		while (usedValues.Size()>64)
			usedValues.Pop();		
		return usedValues[usedValues.Size()-1];		
	}
}
uint32_t RakNetRandomSync::GetSeed( void ) const
{
	return seed;
}
uint32_t RakNetRandomSync::GetCallCount( void ) const
{
	return callCount;
}
void RakNetRandomSync::SetCallCount( uint32_t i )
{
	callCount = i;
}
void RakNetRandomSync::SerializeConstruction(SLNet::BitStream *constructionBitstream)
{
	constructionBitstream->Write(seed);
	constructionBitstream->Write(callCount);
}
bool RakNetRandomSync::DeserializeConstruction(SLNet::BitStream *constructionBitstream)
{
	uint32_t _seed;
	uint32_t _skipValues;
	constructionBitstream->Read(_seed);
	bool success = constructionBitstream->Read(_skipValues);
	if (success)
		SeedMT(_seed, _skipValues);
	return success;
}
void RakNetRandomSync::Serialize(SLNet::BitStream *outputBitstream)
{
	outputBitstream->Write(callCount);
}
void RakNetRandomSync::Deserialize(SLNet::BitStream *outputBitstream)
{
	uint32_t _callCount;
	outputBitstream->Read(_callCount);
	if (_callCount < callCount )
	{
		// We locally read more values than the remote system
		// The next n calls should come from buffered values
		usedValueBufferCount = callCount - _callCount;
	}
	else if (_callCount > callCount )
	{
		// Remote system read more values than us
		uint32_t diff = _callCount - callCount;
		if (diff <= usedValueBufferCount)
			usedValueBufferCount -= diff;
		if (diff > 0)
			Skip(diff);
	}
}
void RakNetRandomSync::Skip( uint32_t count )
{
	for (uint32_t i = 0; i < count; i++)
		rnr.RandomMT();
	callCount+=count;
}

} // namespace SLNet

/*
RakNetRandomSync r1, r2;
BitStream bsTest;
r1.SeedMT(0);
r1.SerializeConstruction(&bsTest);
bsTest.SetReadOffset(0);
r2.DeserializeConstruction(&bsTest);
printf("1. (r1) %f\n", r1.FrandomMT());
printf("1. (r2) %f\n", r2.FrandomMT());
printf("2. (r1) %f\n", r1.FrandomMT());
printf("2. (r2) %f\n", r2.FrandomMT());
printf("3. (r1) %f\n", r1.FrandomMT());
printf("3. (r2) %f\n", r2.FrandomMT());
printf("4. (r1) %f\n", r1.FrandomMT());
printf("4. (r2) %f\n", r2.FrandomMT());
printf("5. (r2) %f\n", r2.FrandomMT());
printf("6. (r2) %f\n", r2.FrandomMT());
printf("7. (r2) %f\n", r2.FrandomMT());
bsTest.Reset();
r1.Serialize(&bsTest);
bsTest.SetReadOffset(0);
r2.Deserialize(&bsTest);
printf("Synched r2 to match r1\n");
printf("5. (r1) %f\n", r1.FrandomMT());
printf("5. (r2) %f --Should continue sequence from 5-\n", r2.FrandomMT());
printf("6. (r1) %f\n", r1.FrandomMT());
printf("6. (r2) %f\n", r2.FrandomMT());
printf("7. (r1) %f -- Extra call to r1, no r2 equivalent --\n", r1.FrandomMT());
printf("8. (r1) %f -- Extra call to r1, no r2 equivalent --\n", r1.FrandomMT());
bsTest.Reset();
r1.Serialize(&bsTest);
bsTest.SetReadOffset(0);
r2.Deserialize(&bsTest);
printf("Synched r2 to match r1\n");
printf("9. (r1) %f\n", r1.FrandomMT());
printf("9. (r2) %f --SKIPPED 7,8, SHOULD MATCH 9-\n", r2.FrandomMT());
*/
