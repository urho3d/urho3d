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

/// \file StatisticsHistory.h
/// \brief Input numerical values over time. Get sum, average, highest, lowest, standard deviation on recent or all-time values


#include "NativeFeatureIncludes.h"
#if _RAKNET_SUPPORT_StatisticsHistory==1

#ifndef __STATISTICS_HISTORY_H
#define __STATISTICS_HISTORY_H

#include "PluginInterface2.h"
#include "memoryoverride.h"
#include "NativeTypes.h"
#include "DS_List.h"
#include "types.h"
#include "DS_OrderedList.h"
#include "string.h"
#include "DS_Queue.h"
#include "DS_Hash.h"
#include <float.h>

namespace SLNet
{
/// Forward declarations
class RakPeerInterface;

// Type used to track values. If needed, change to double and recompile
typedef double SHValueType;
#define SH_TYPE_MAX DBL_MAX

/// \brief Input numerical values over time. Get sum, average, highest, lowest, standard deviation on recent or all-time values
class RAK_DLL_EXPORT StatisticsHistory
{
public:
	// GetInstance() and DestroyInstance(instance*)
	STATIC_FACTORY_DECLARATIONS(StatisticsHistory)

	enum SHErrorCode
	{
		SH_OK,
		SH_UKNOWN_OBJECT,
		SH_UKNOWN_KEY,
		SH_INVALID_PARAMETER,
	};

	enum SHSortOperation
	{
		SH_DO_NOT_SORT,

		SH_SORT_BY_RECENT_SUM_ASCENDING,
		SH_SORT_BY_RECENT_SUM_DESCENDING,
		SH_SORT_BY_LONG_TERM_SUM_ASCENDING,
		SH_SORT_BY_LONG_TERM_SUM_DESCENDING,
		SH_SORT_BY_RECENT_SUM_OF_SQUARES_ASCENDING,
		SH_SORT_BY_RECENT_SUM_OF_SQUARES_DESCENDING,
		SH_SORT_BY_RECENT_AVERAGE_ASCENDING,
		SH_SORT_BY_RECENT_AVERAGE_DESCENDING,
		SH_SORT_BY_LONG_TERM_AVERAGE_ASCENDING,
		SH_SORT_BY_LONG_TERM_AVERAGE_DESCENDING,
		SH_SORT_BY_RECENT_HIGHEST_ASCENDING,
		SH_SORT_BY_RECENT_HIGHEST_DESCENDING,
		SH_SORT_BY_RECENT_LOWEST_ASCENDING,
		SH_SORT_BY_RECENT_LOWEST_DESCENDING,
		SH_SORT_BY_LONG_TERM_HIGHEST_ASCENDING,
		SH_SORT_BY_LONG_TERM_HIGHEST_DESCENDING,
		SH_SORT_BY_LONG_TERM_LOWEST_ASCENDING,
		SH_SORT_BY_LONG_TERM_LOWEST_DESCENDING,
	};

	enum SHDataCategory
	{
		/// Insert values from one set into the other set, in time order
		/// Values at the same time end up in the final set twice
		/// Use when you have additional data points to add to a graph
		DC_DISCRETE,

		/// Add values from one set to values from the other set, at corresponding times
		/// If value at time t does not exist in the other set, linearly extrapolate value for other set based on nearest two data points
		/// longTerm* values are unknown using this method
		/// Use to add two graphs together
		DC_CONTINUOUS
	};

	struct TimeAndValue;
	struct TimeAndValueQueue;

	struct TrackedObjectData
	{
		TrackedObjectData();
		TrackedObjectData(uint64_t _objectId, int _objectType, void *_userData);
		uint64_t objectId;
		int objectType;
		void *userData;
	};

	StatisticsHistory();
	virtual ~StatisticsHistory();
	void SetDefaultTimeToTrack(Time defaultTimeToTrack);
	Time GetDefaultTimeToTrack(void) const;
	bool AddObject(TrackedObjectData tod);
	bool RemoveObject(uint64_t objectId, void **userData);
	void RemoveObjectAtIndex(unsigned int index);
	void Clear(void);
	unsigned int GetObjectCount(void) const;
	StatisticsHistory::TrackedObjectData * GetObjectAtIndex(unsigned int index) const;
	unsigned int GetObjectIndex(uint64_t objectId) const;
	bool AddValueByObjectID(uint64_t objectId, RakString key, SHValueType val, Time curTime, bool combineEqualTimes);
	void AddValueByIndex(unsigned int index, RakString key, SHValueType val, Time curTime, bool combineEqualTimes);
	SHErrorCode GetHistoryForKey(uint64_t objectId, RakString key, TimeAndValueQueue **values, Time curTime) const;
	bool GetHistorySorted(uint64_t objectId, SHSortOperation sortType, DataStructures::List<TimeAndValueQueue *> &values) const;
	void MergeAllObjectsOnKey(RakString key, TimeAndValueQueue *tavqOutput, SHDataCategory dataCategory) const;
	void GetUniqueKeyList(DataStructures::List<RakString> &keys);

	struct TimeAndValue
	{
		Time time;
		SHValueType val;
	};

	struct TimeAndValueQueue
	{
		TimeAndValueQueue();
		~TimeAndValueQueue();

		DataStructures::Queue<TimeAndValue> values;

		Time timeToTrackValues;
		RakString key;

		SHValueType recentSum;
		SHValueType recentSumOfSquares;
		SHValueType longTermSum;
		SHValueType longTermCount;
		SHValueType longTermLowest;
		SHValueType longTermHighest;

		void SetTimeToTrackValues(Time t);
		Time GetTimeToTrackValues(void) const;
		SHValueType GetRecentSum(void) const;
		SHValueType GetRecentSumOfSquares(void) const;
		SHValueType GetLongTermSum(void) const;
		SHValueType GetRecentAverage(void) const;
		SHValueType GetRecentLowest(void) const;
		SHValueType GetRecentHighest(void) const;
		SHValueType GetRecentStandardDeviation(void) const;
		SHValueType GetLongTermAverage(void) const;
		SHValueType GetLongTermLowest(void) const;
		SHValueType GetLongTermHighest(void) const;
		SHValueType GetSumSinceTime(Time t) const;
		Time GetTimeRange(void) const;

		// Merge two sets to output
		static void MergeSets( const TimeAndValueQueue *lhs, SHDataCategory lhsDataCategory, const TimeAndValueQueue *rhs, SHDataCategory rhsDataCategory, TimeAndValueQueue *output );

		// Shrink or expand a sample set to the approximate number given
		// DC_DISCRETE will produce a histogram (sum) while DC_CONTINUOUS will produce an average
		void ResizeSampleSet( int approximateSamples, DataStructures::Queue<StatisticsHistory::TimeAndValue> &blendedSamples, SHDataCategory dataCategory, Time timeClipStart=0, Time timeClipEnd=0 );

		// Clear out all values
		void Clear(void);

		TimeAndValueQueue& operator = ( const TimeAndValueQueue& input );

		/// \internal
		void CullExpiredValues(Time curTime);
		/// \internal
		static SHValueType Interpolate(TimeAndValue t1, TimeAndValue t2, Time time);
		/// \internal
		SHValueType sortValue;
	};

protected:
	struct TrackedObject;
public:
	static int TrackedObjectComp( const uint64_t &key, TrackedObject* const &data );
protected:

	struct TrackedObject
	{
		TrackedObject();
		~TrackedObject();
		TrackedObjectData trackedObjectData;
		DataStructures::Hash<SLNet::RakString, TimeAndValueQueue*, 32, SLNet::RakString::ToInteger> dataQueues;
	};

	DataStructures::OrderedList<uint64_t, TrackedObject*,TrackedObjectComp> objects;

	Time timeToTrack;
};

/// \brief Input numerical values over time. Get sum, average, highest, lowest, standard deviation on recent or all-time values
/// \ingroup PLUGINS_GROUP
class RAK_DLL_EXPORT StatisticsHistoryPlugin : public PluginInterface2
{
public:
	// GetInstance() and DestroyInstance(instance*)
	STATIC_FACTORY_DECLARATIONS(StatisticsHistoryPlugin)

	StatisticsHistory statistics;

	StatisticsHistoryPlugin();
	virtual ~StatisticsHistoryPlugin();
	void SetTrackConnections(bool _addNewConnections, int newConnectionsObjectType, bool _removeLostConnections);
	
protected:
	virtual void Update(void);
	virtual void OnClosedConnection(const SystemAddress &systemAddress, RakNetGUID rakNetGUID, PI2_LostConnectionReason lostConnectionReason );
	virtual void OnNewConnection(const SystemAddress &systemAddress, RakNetGUID rakNetGUID, bool isIncoming);

	// Too slow
// 	virtual bool UsesReliabilityLayer(void) const {return true;}
// 	virtual void OnDirectSocketSend(const char *data, const BitSize_t bitsUsed, SystemAddress remoteSystemAddress);
// 	virtual void OnDirectSocketReceive(const char *data, const BitSize_t bitsUsed, SystemAddress remoteSystemAddress);


	bool addNewConnections;
	bool removeLostConnections;
	int newConnectionsObjectType;
};

} // namespace SLNet

#endif // __STATISTICS_HISTORY_H

#endif // _RAKNET_SUPPORT_*
