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
/// \brief \b Compresses/Decompresses ASCII strings and writes/reads them to BitStream class instances.  You can use this to easily serialize and deserialize your own strings.
///



#ifndef __STRING_COMPRESSOR_H
#define __STRING_COMPRESSOR_H

#include "Export.h"
#include "DS_Map.h"
#include "memoryoverride.h"
#include "NativeTypes.h"

#ifdef _STD_STRING_COMPRESSOR
#include <string>
#endif

/// Forward declaration
namespace SLNet
{
	class BitStream;
	class RakString;
};


namespace SLNet
{
/// Forward declarations
class HuffmanEncodingTree;

/// \brief Writes and reads strings to and from bitstreams.
///
/// Only works with ASCII strings.  The default compression is for English.
/// You can call GenerateTreeFromStrings to compress and decompress other languages efficiently as well.
class RAK_DLL_EXPORT StringCompressor
{
public:
	
	// Destructor	
	~StringCompressor();
	
	/// static function because only static functions can access static members
	/// The RakPeer constructor adds a reference to this class, so don't call this until an instance of RakPeer exists, or unless you call AddReference yourself.
	/// \return the unique instance of the StringCompressor 
	static StringCompressor* Instance(void);

	/// Given an array of strings, such as a chat log, generate the optimal encoding tree for it.
	/// This function is optional and if it is not called a default tree will be used instead.
	/// \param[in] input An array of bytes which should point to text.
	/// \param[in] inputLength Length of \a input
	/// \param[in] languageID An identifier for the language / string table to generate the tree for.  English is automatically created with ID 0 in the constructor.
	void GenerateTreeFromStrings( unsigned char *input, unsigned inputLength, uint8_t languageId );
	
 	/// Writes input to output, compressed.  Takes care of the null terminator for you.
	/// \param[in] input Pointer to an ASCII string
	/// \param[in] maxCharsToWrite The max number of bytes to write of \a input.  Use 0 to mean no limit.
	/// \param[out] output The bitstream to write the compressed string to
	/// \param[in] languageID Which language to use
	void EncodeString( const char *input, int maxCharsToWrite, SLNet::BitStream *output, uint8_t languageId=0 );
	
	/// Writes input to output, uncompressed.  Takes care of the null terminator for you.
	/// \param[out] output A block of bytes to receive the output
	/// \param[in] maxCharsToWrite Size, in bytes, of \a output .  A NULL terminator will always be appended to the output string.  If the maxCharsToWrite is not large enough, the string will be truncated.
	/// \param[in] input The bitstream containing the compressed string
	/// \param[in] languageID Which language to use
	bool DecodeString( char *output, int maxCharsToWrite, SLNet::BitStream *input, uint8_t languageId=0 );

#ifdef _CSTRING_COMPRESSOR
	void EncodeString( const CString &input, int maxCharsToWrite, SLNet::BitStream *output, uint8_t languageId=0 );
	bool DecodeString( CString &output, int maxCharsToWrite, SLNet::BitStream *input, uint8_t languageId=0 );
#endif

#ifdef _STD_STRING_COMPRESSOR
	void EncodeString( const std::string &input, int maxCharsToWrite, SLNet::BitStream *output, uint8_t languageId=0 );
	bool DecodeString( std::string *output, int maxCharsToWrite, SLNet::BitStream *input, uint8_t languageId=0 );
#endif

	void EncodeString( const SLNet::RakString *input, int maxCharsToWrite, SLNet::BitStream *output, uint8_t languageId=0 );
	bool DecodeString(SLNet::RakString *output, int maxCharsToWrite, SLNet::BitStream *input, uint8_t languageId=0 );

	/// Used so I can allocate and deallocate this singleton at runtime
	static void AddReference(void);
	
	/// Used so I can allocate and deallocate this singleton at runtime
	static void RemoveReference(void);

	StringCompressor();

private:
	
	/// Singleton instance
	static StringCompressor *instance;
	
	/// Pointer to the huffman encoding trees.
	DataStructures::Map<int, HuffmanEncodingTree *> huffmanEncodingTrees;
	
	static int referenceCount;
};

} // namespace SLNet

#endif
