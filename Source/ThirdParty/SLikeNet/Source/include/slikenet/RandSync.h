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

/// \file
/// \brief \b [Internal] Random number generator
///



#ifndef __RAND_SYNC_H
#define __RAND_SYNC_H 

#include "Export.h"
#include "Rand.h"
#include "DS_Queue.h"
#include "NativeTypes.h"

namespace SLNet {

class BitStream;

class RAK_DLL_EXPORT RakNetRandomSync
{
public:
	RakNetRandomSync();
	virtual ~RakNetRandomSync();
	void SeedMT( uint32_t _seed );
	void SeedMT( uint32_t _seed, uint32_t skipValues );
	float FrandomMT( void );
	unsigned int RandomMT( void );
	uint32_t GetSeed( void ) const;
	uint32_t GetCallCount( void ) const;
	void SetCallCount( uint32_t i );

	virtual void SerializeConstruction(SLNet::BitStream *constructionBitstream);
	virtual bool DeserializeConstruction(SLNet::BitStream *constructionBitstream);
	virtual void Serialize(SLNet::BitStream *outputBitstream);
	virtual void Deserialize(SLNet::BitStream *outputBitstream);

protected:
	void Skip( uint32_t count );
	DataStructures::Queue<unsigned int> usedValues;
	uint32_t seed;
	uint32_t callCount;
	uint32_t usedValueBufferCount;
	RakNetRandom rnr;
};
} // namespace SLNet


#endif
