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
/// \brief A simple class to encode and decode known strings based on a lookup table.  Similar to the StringCompressor class.
///



#ifndef __STRING_TABLE_H
#define __STRING_TABLE_H

#include "DS_OrderedList.h"
#include "Export.h"
#include "memoryoverride.h"

/// Forward declaration
namespace SLNet
{
	class BitStream;
};

/// StringTableType should be the smallest type possible, or else it defeats the purpose of the StringTable class, which is to save bandwidth.
typedef unsigned char StringTableType;

/// The string plus a bool telling us if this string was copied or not.
struct StrAndBool
{
	char *str;
	bool b;
};

namespace SLNet
{
	int RAK_DLL_EXPORT StrAndBoolComp( char *const &key, const StrAndBool &data );

	/// \details This is an even more efficient alternative to StringCompressor in that it writes a single byte from a lookup table and only does compression.<BR>
	/// if the string does not already exist in the table.<BR>
	/// All string tables must match on all systems - hence you must add all the strings in the same order on all systems.<BR>
	/// Furthermore, this must be done before sending packets that use this class, since the strings are ordered for fast lookup.  Adding after that time would mess up all the indices so don't do it.<BR>
	/// Don't use this class to write strings which were not previously registered with AddString, since you just waste bandwidth then.  Use StringCompressor instead.
	/// \brief Writes a string index, instead of the whole string
	class RAK_DLL_EXPORT StringTable
	{
	public:

		// Destructor	
		~StringTable();

		/// static function because only static functions can access static members
		/// The RakPeer constructor adds a reference to this class, so don't call this until an instance of RakPeer exists, or unless you call AddReference yourself.
		/// \return the unique instance of the StringTable
		static StringTable* Instance(void);

		/// Add a string to the string table.
		/// \param[in] str The string to add to the string table
		/// \param[in] copyString true to make a copy of the passed string (takes more memory), false to not do so (if your string is in static memory).
		void AddString(const char *str, bool copyString);

		/// Writes input to output, compressed.  Takes care of the null terminator for you.
		/// Relies on the StringCompressor class, which is automatically reference counted in the constructor and destructor in RakPeer.  You can call the reference counting functions yourself if you wish too.
		/// \param[in] input Pointer to an ASCII string
		/// \param[in] maxCharsToWrite The size of \a input 
		/// \param[out] output The bitstream to write the compressed string to
		void EncodeString( const char *input, int maxCharsToWrite, SLNet::BitStream *output );

		/// Writes input to output, uncompressed.  Takes care of the null terminator for you.
		/// Relies on the StringCompressor class, which is automatically reference counted in the constructor and destructor in RakPeer.  You can call the reference counting functions yourself if you wish too.
		/// \param[out] output A block of bytes to receive the output
		/// \param[in] maxCharsToWrite Size, in bytes, of \a output .  A NULL terminator will always be appended to the output string.  If the maxCharsToWrite is not large enough, the string will be truncated.
		/// \param[in] input The bitstream containing the compressed string
		bool DecodeString( char *output, int maxCharsToWrite, SLNet::BitStream *input );

		/// Used so I can allocate and deallocate this singleton at runtime
		static void AddReference(void);

		/// Used so I can allocate and deallocate this singleton at runtime
		static void RemoveReference(void);

		/// Private Constructor	
		StringTable();

	protected:
		/// Called when you mess up and send a string using this class that was not registered with AddString
		/// \param[in] maxCharsToWrite Size, in bytes, of \a output .  A NULL terminator will always be appended to the output string.  If the maxCharsToWrite is not large enough, the string will be truncated.
		void LogStringNotFound(const char *strName);

		/// Singleton instance
		static StringTable *instance;
		static int referenceCount;

		DataStructures::OrderedList<char *, StrAndBool, StrAndBoolComp> orderedStringList;
	};
}


#endif
