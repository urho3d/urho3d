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

/// \file DataCompressor.h
/// \brief DataCompressor does compression on a block of data.  
/// \details Not very good compression, but it's small and fast so is something you can use per-message at runtime.
///


#ifndef __DATA_COMPRESSOR_H
#define __DATA_COMPRESSOR_H

#include "memoryoverride.h"
#include "DS_HuffmanEncodingTree.h"
#include "Export.h"

namespace SLNet
{

/// \brief Does compression on a block of data.  Not very good compression, but it's small and fast so is something you can compute at runtime.
class RAK_DLL_EXPORT DataCompressor
{
public:
	// GetInstance() and DestroyInstance(instance*)
	STATIC_FACTORY_DECLARATIONS(DataCompressor)

	static void Compress( unsigned char *userData, unsigned sizeInBytes, SLNet::BitStream * output );
	static unsigned DecompressAndAllocate(SLNet::BitStream * input, unsigned char **output );
};

} // namespace SLNet

#endif
