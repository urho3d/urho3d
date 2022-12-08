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



#ifndef __RAND_H
#define __RAND_H 

#include "Export.h"

/// Initialise seed for Random Generator
/// \note not threadSafe, use an instance of RakNetRandom if necessary per thread
/// \param[in] seed The seed value for the random number generator.
extern void RAK_DLL_EXPORT seedMT( unsigned int seed );

/// \internal
/// \note not threadSafe, use an instance of RakNetRandom if necessary per thread
extern unsigned int RAK_DLL_EXPORT reloadMT( void );

/// Gets a random unsigned int
/// \note not threadSafe, use an instance of RakNetRandom if necessary per thread
/// \return an integer random value.
extern unsigned int RAK_DLL_EXPORT randomMT( void );

/// Gets a random float
/// \note not threadSafe, use an instance of RakNetRandom if necessary per thread
/// \return 0 to 1.0f, inclusive
extern float RAK_DLL_EXPORT frandomMT( void );

/// Randomizes a buffer
/// \note not threadSafe, use an instance of RakNetRandom if necessary per thread
extern void RAK_DLL_EXPORT fillBufferMT( void *buffer, unsigned int bytes );

namespace SLNet {

// Same thing as above functions, but not global
class RAK_DLL_EXPORT RakNetRandom
{
public:
	RakNetRandom();
	~RakNetRandom();
	void SeedMT( unsigned int seed );
	unsigned int ReloadMT( void );
	unsigned int RandomMT( void );
	float FrandomMT( void );
	void FillBufferMT( void *buffer, unsigned int bytes );

protected:
	unsigned int state[ 624 + 1 ];
	unsigned int *next;
	int left;
};

} // namespace SLNet

#endif
