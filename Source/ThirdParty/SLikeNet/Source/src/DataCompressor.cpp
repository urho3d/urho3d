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

#include "slikenet/DataCompressor.h"
#include "slikenet/DS_HuffmanEncodingTree.h"
#include "slikenet/assert.h"
#include <string.h> // Use string.h rather than memory.h for a console

using namespace SLNet;

STATIC_FACTORY_DEFINITIONS(DataCompressor,DataCompressor)

void DataCompressor::Compress( unsigned char *userData, unsigned sizeInBytes, SLNet::BitStream * output )
{
	// Don't use this for small files as you will just make them bigger!
	RakAssert(sizeInBytes > 2048);

	unsigned int frequencyTable[ 256 ];
	unsigned int i;
	memset(frequencyTable,0,256*sizeof(unsigned int));
	for (i=0; i < sizeInBytes; i++)
		++frequencyTable[userData[i]];
	HuffmanEncodingTree tree;
	BitSize_t writeOffset1, writeOffset2, bitsUsed1, bitsUsed2;
	tree.GenerateFromFrequencyTable(frequencyTable);
	output->WriteCompressed(sizeInBytes);
	for (i=0; i < 256; i++)
		output->WriteCompressed(frequencyTable[i]);
	output->AlignWriteToByteBoundary();
	writeOffset1=output->GetWriteOffset();
	output->Write((unsigned int)0);	// Dummy value
	bitsUsed1=output->GetNumberOfBitsUsed();
	tree.EncodeArray(userData, sizeInBytes, output);
	bitsUsed2=output->GetNumberOfBitsUsed();
	writeOffset2=output->GetWriteOffset();
	output->SetWriteOffset(writeOffset1);
	output->Write(bitsUsed2-bitsUsed1); // Go back and write how many bits were used for the encoding
	output->SetWriteOffset(writeOffset2);
}

unsigned DataCompressor::DecompressAndAllocate(SLNet::BitStream * input, unsigned char **output )
{
	HuffmanEncodingTree tree;
	unsigned int bitsUsed, destinationSizeInBytes;
	unsigned int decompressedBytes;
	unsigned int frequencyTable[ 256 ];
	unsigned i;
	
	input->ReadCompressed(destinationSizeInBytes);
	for (i=0; i < 256; i++)
		input->ReadCompressed(frequencyTable[i]);
	input->AlignReadToByteBoundary();
	if (input->Read(bitsUsed)==false)
	{
		// Read error
#ifdef _DEBUG
		RakAssert(0);
#endif
		return 0;
	}
	*output = (unsigned char*) rakMalloc_Ex(destinationSizeInBytes, _FILE_AND_LINE_);
	tree.GenerateFromFrequencyTable(frequencyTable);
	decompressedBytes=tree.DecodeArray(input, bitsUsed, destinationSizeInBytes, *output );
	RakAssert(decompressedBytes==destinationSizeInBytes);
	return destinationSizeInBytes;
}
