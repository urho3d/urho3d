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

/// \file DS_HuffmanEncodingTree.h
/// \brief \b [Internal] Generates a huffman encoding tree, used for string and global compression.
///


#ifndef __HUFFMAN_ENCODING_TREE
#define __HUFFMAN_ENCODING_TREE

#include "memoryoverride.h"
#include "DS_HuffmanEncodingTreeNode.h"
#include "BitStream.h"
#include "Export.h"
#include "DS_LinkedList.h" 

namespace SLNet
{

/// This generates special cases of the huffman encoding tree using 8 bit keys with the additional condition that unused combinations of 8 bits are treated as a frequency of 1
class RAK_DLL_EXPORT HuffmanEncodingTree
{

public:
	HuffmanEncodingTree();
	~HuffmanEncodingTree();

	/// \brief Pass an array of bytes to array and a preallocated BitStream to receive the output.
	/// \param [in] input Array of bytes to encode
	/// \param [in] sizeInBytes size of \a input
	/// \param [out] output The bitstream to write to
	void EncodeArray( unsigned char *input, size_t sizeInBytes, SLNet::BitStream * output );

	// \brief Decodes an array encoded by EncodeArray().
	unsigned DecodeArray(SLNet::BitStream * input, BitSize_t sizeInBits, size_t maxCharsToWrite, unsigned char *output );
	void DecodeArray( unsigned char *input, BitSize_t sizeInBits, SLNet::BitStream * output );

	/// \brief Given a frequency table of 256 elements, all with a frequency of 1 or more, generate the tree.
	void GenerateFromFrequencyTable( unsigned int frequencyTable[ 256 ] );

	/// \brief Free the memory used by the tree.
	void FreeMemory( void );

private:

	/// The root node of the tree 

	HuffmanEncodingTreeNode *root;

	/// Used to hold bit encoding for one character


	struct CharacterEncoding
	{
		unsigned char* encoding;
		unsigned short bitLength;
	};

	CharacterEncoding encodingTable[ 256 ];

	void InsertNodeIntoSortedList( HuffmanEncodingTreeNode * node, DataStructures::LinkedList<HuffmanEncodingTreeNode *> *huffmanEncodingTreeNodeList ) const;
};

} // namespace SLNet

#endif
