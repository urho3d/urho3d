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

#include "NativeFeatureIncludes.h"
#if _RAKNET_SUPPORT_CloudClient==1 || _RAKNET_SUPPORT_CloudServer==1

#ifndef __CLOUD_COMMON_H
#define __CLOUD_COMMON_H

#include "types.h"
#include "string.h"

namespace SLNet
{

class BitStream;
struct CloudQueryRow;

/// Allocates CloudQueryRow and the row data. Override to use derived classes or different allocators
/// \ingroup CLOUD_GROUP
class RAK_DLL_EXPORT CloudAllocator
{
public:
	CloudAllocator() {}
	virtual ~CloudAllocator() {}

	/// \brief Allocate a row
	virtual CloudQueryRow* AllocateCloudQueryRow(void);
	/// \brief Free a row
	virtual void DeallocateCloudQueryRow(CloudQueryRow *row);
	/// \brief Allocate CloudQueryRow::data
	virtual unsigned char *AllocateRowData(uint32_t bytesNeededForData);
	/// \brief Free CloudQueryRow::data
	virtual void DeallocateRowData(void *data);
};

/// Serves as a key to identify data uploaded to or queried from the server.
/// \ingroup CLOUD_GROUP
struct RAK_DLL_EXPORT CloudKey
{
	CloudKey() {}
	CloudKey(SLNet::RakString _primaryKey, uint32_t _secondaryKey) : primaryKey(_primaryKey), secondaryKey(_secondaryKey) {}
	~CloudKey() {}

	/// Identifies the primary key. This is intended to be a major category, such as the name of the application
	/// Must be non-empty
	SLNet::RakString primaryKey;

	/// Identifies the secondary key. This is intended to be a subcategory enumeration, such as PLAYER_LIST or RUNNING_SCORES
	uint32_t secondaryKey;

	/// \internal
	void Serialize(bool writeToBitstream, BitStream *bitStream);
};

/// \internal
int CloudKeyComp(const CloudKey &key, const CloudKey &data);

/// Data members used to query the cloud
/// \ingroup CLOUD_GROUP
struct RAK_DLL_EXPORT CloudQuery
{
	CloudQuery() {startingRowIndex=0; maxRowsToReturn=0; subscribeToResults=false;}

	/// List of keys to query. Must be at least of length 1.
	/// This query is run on uploads from all clients, and those that match the combination of primaryKey and secondaryKey are potentially returned
	/// If you pass more than one key at a time, the results are concatenated so if you need to differentiate between queries then send two different queries
	DataStructures::List<CloudKey> keys;

	/// If limiting the number of rows to return, this is the starting offset into the list. Has no effect unless maxRowsToReturn is > 0
	uint32_t startingRowIndex;

	/// Maximum number of rows to return. Actual number may still be less than this. Pass 0 to mean no-limit.
	uint32_t maxRowsToReturn;

	/// If true, automatically get updates as the results returned to you change. Unsubscribe with CloudMemoryClient::Unsubscribe()
	bool subscribeToResults;

	/// \internal
	void Serialize(bool writeToBitstream, BitStream *bitStream);
};

/// \ingroup CLOUD_GROUP
struct RAK_DLL_EXPORT CloudQueryRow
{
	/// Key used to identify this data
	CloudKey key;

	/// Data uploaded
	unsigned char *data;

	/// Length of data uploaded
	uint32_t length;

	/// System address of server that is holding this data, and the client is connected to
	SystemAddress serverSystemAddress;

	/// System address of client that uploaded this data
	SystemAddress clientSystemAddress;

	/// RakNetGUID of server that is holding this data, and the client is connected to
	RakNetGUID serverGUID;

	/// RakNetGUID of client that uploaded this data
	RakNetGUID clientGUID;

	/// \internal
	void Serialize(bool writeToBitstream, BitStream *bitStream, CloudAllocator *allocator);
};

/// \ingroup CLOUD_GROUP
struct RAK_DLL_EXPORT CloudQueryResult
{
	/// Query originally passed to Download()
	CloudQuery cloudQuery;

	/// Results returned from query. If there were multiple keys in CloudQuery::keys then see resultKeyIndices
	DataStructures::List<CloudQueryRow*> rowsReturned;

	/// If there were multiple keys in CloudQuery::keys, then each key is processed in order and the result concatenated to rowsReturned
	/// The starting index of each query is written to resultKeyIndices
	/// For example, if CloudQuery::keys had 4 keys, returning 3 rows, 0, rows, 5 rows, and 12 rows then
	/// resultKeyIndices would be 0, 3, 3, 8
	DataStructures::List<uint32_t> resultKeyIndices;

	/// Whatever was passed to CloudClient::Get() as CloudQuery::subscribeToResults
	bool subscribeToResults;

	/// \internal
	void Serialize(bool writeToBitstream, BitStream *bitStream, CloudAllocator *allocator);
	/// \internal
	void SerializeHeader(bool writeToBitstream, BitStream *bitStream);
	/// \internal
	void SerializeNumRows(bool writeToBitstream, uint32_t &numRows, BitStream *bitStream);
	/// \internal
	void SerializeCloudQueryRows(bool writeToBitstream, uint32_t &numRows, BitStream *bitStream, CloudAllocator *allocator);
};

} // Namespace SLikeNet

#endif // __CLOUD_COMMON_H

#endif // #if _RAKNET_SUPPORT_CloudClient==1 || _RAKNET_SUPPORT_CloudServer==1
