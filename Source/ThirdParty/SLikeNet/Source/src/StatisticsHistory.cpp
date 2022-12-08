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

#include "slikenet/NativeFeatureIncludes.h"
#if _RAKNET_SUPPORT_StatisticsHistory==1

#include "slikenet/StatisticsHistory.h"
#include "slikenet/GetTime.h"
#include "slikenet/statistics.h"
#include "slikenet/peerinterface.h"

using namespace SLNet;

STATIC_FACTORY_DEFINITIONS(StatisticsHistory,StatisticsHistory);
STATIC_FACTORY_DEFINITIONS(StatisticsHistoryPlugin,StatisticsHistoryPlugin);

int StatisticsHistory::TrackedObjectComp( const uint64_t &key, StatisticsHistory::TrackedObject* const &data )
{
	if (key < data->trackedObjectData.objectId)
		return -1;
	if (key == data->trackedObjectData.objectId)
		return 0;
	return 1;
}

int TimeAndValueQueueCompAsc( StatisticsHistory::TimeAndValueQueue* const &key, StatisticsHistory::TimeAndValueQueue* const &data )
{
	if (key->sortValue < data->sortValue)
		return -1;
	if (key->sortValue > data->sortValue)
		return 1;
	if (key->key < data->key)
		return -1;
	if (key->key > data->key)
		return 1;
	return 0;
}

int TimeAndValueQueueCompDesc( StatisticsHistory::TimeAndValueQueue* const &key, StatisticsHistory::TimeAndValueQueue* const &data )
{
	if (key->sortValue > data->sortValue)
		return -1;
	if (key->sortValue < data->sortValue)
		return 1;
	if (key->key > data->key)
		return -1;
	if (key->key < data->key)
		return 1;
	return 0;
}
StatisticsHistory::TrackedObjectData::TrackedObjectData() {}
StatisticsHistory::TrackedObjectData::TrackedObjectData(uint64_t _objectId, int _objectType, void *_userData)
{
	objectId=_objectId;
	objectType=_objectType;
	userData=_userData;
}
StatisticsHistory::StatisticsHistory() {timeToTrack = 30000;}
StatisticsHistory::~StatisticsHistory()
{
	Clear();
}
void StatisticsHistory::SetDefaultTimeToTrack(Time defaultTimeToTrack) {timeToTrack = defaultTimeToTrack;}
Time StatisticsHistory::GetDefaultTimeToTrack(void) const {return timeToTrack;}
bool StatisticsHistory::AddObject(TrackedObjectData tod)
{
	bool objectExists;
	unsigned int idx = objects.GetIndexFromKey(tod.objectId, &objectExists);
	if (objectExists)
		return false;
	TrackedObject *to = SLNet::OP_NEW<TrackedObject>(_FILE_AND_LINE_);
	to->trackedObjectData=tod;
	objects.InsertAtIndex(to,idx,_FILE_AND_LINE_);
	return true;
}
bool StatisticsHistory::RemoveObject(uint64_t objectId, void **userData)
{
	unsigned int idx = GetObjectIndex(objectId);
	if (idx == (unsigned int) -1)
		return false;
	if (userData)
		*userData = objects[idx]->trackedObjectData.userData;
	RemoveObjectAtIndex(idx);
	return true;
}
void StatisticsHistory::RemoveObjectAtIndex(unsigned int index)
{
	TrackedObject *to = objects[index];
	objects.RemoveAtIndex(index);
	SLNet::OP_DELETE(to, _FILE_AND_LINE_);
}
void StatisticsHistory::Clear(void)
{
	for (unsigned int idx=0; idx < objects.Size(); idx++)
	{
		SLNet::OP_DELETE(objects[idx], _FILE_AND_LINE_);
	}
	objects.Clear(false, _FILE_AND_LINE_);
}
unsigned int StatisticsHistory::GetObjectCount(void) const {return objects.Size();}
StatisticsHistory::TrackedObjectData * StatisticsHistory::GetObjectAtIndex(unsigned int index) const {return &objects[index]->trackedObjectData;}
bool StatisticsHistory::AddValueByObjectID(uint64_t objectId, RakString key, SHValueType val, Time curTime, bool combineEqualTimes)
{
	unsigned int idx = GetObjectIndex(objectId);
	if (idx == (unsigned int) -1)
		return false;
	AddValueByIndex(idx, key, val, curTime, combineEqualTimes);
	return true;
}
void StatisticsHistory::AddValueByIndex(unsigned int index, RakString key, SHValueType val, Time curTime, bool combineEqualTimes)
{
	TimeAndValueQueue *queue;
	TrackedObject *to = objects[index];
	DataStructures::HashIndex hi = to->dataQueues.GetIndexOf(key);
	if (hi.IsInvalid())
	{
		queue = SLNet::OP_NEW<TimeAndValueQueue>(_FILE_AND_LINE_);
		queue->key=key;
		queue->timeToTrackValues = timeToTrack;
		to->dataQueues.Push(key, queue, _FILE_AND_LINE_);
	}
	else
	{
		queue = to->dataQueues.ItemAtIndex(hi);
	}

	TimeAndValue tav;
	if (combineEqualTimes==true && queue->values.Size()>0 && queue->values.PeekTail().time==curTime)
	{
		tav = queue->values.PopTail();

		queue->recentSum -= tav.val;
		queue->recentSumOfSquares -= tav.val * tav.val;
		queue->longTermSum -= tav.val;
		queue->longTermCount = queue->longTermCount - 1;
	}
	else
	{
		tav.val=0.0;
		tav.time=curTime;
	}

	tav.val+=val;
	queue->values.Push(tav, _FILE_AND_LINE_);

	queue->recentSum += tav.val;
	queue->recentSumOfSquares += tav.val * tav.val;
	queue->longTermSum += tav.val;
	queue->longTermCount = queue->longTermCount + 1;
	if (queue->longTermLowest > tav.val)
		queue->longTermLowest = tav.val;
	if (queue->longTermHighest < tav.val)
		queue->longTermHighest = tav.val;
}
StatisticsHistory::SHErrorCode StatisticsHistory::GetHistoryForKey(uint64_t objectId, RakString key, StatisticsHistory::TimeAndValueQueue **values, Time curTime) const
{
	if (values == 0)
		return SH_INVALID_PARAMETER;

	unsigned int idx = GetObjectIndex(objectId);
	if (idx == (unsigned int) -1)
		return SH_UKNOWN_OBJECT;
	TrackedObject *to = objects[idx];
	DataStructures::HashIndex hi = to->dataQueues.GetIndexOf(key);
	if (hi.IsInvalid())
		return SH_UKNOWN_KEY;
	*values = to->dataQueues.ItemAtIndex(hi);
	(*values)->CullExpiredValues(curTime);
	return SH_OK;
}
bool StatisticsHistory::GetHistorySorted(uint64_t objectId, SHSortOperation sortType, DataStructures::List<StatisticsHistory::TimeAndValueQueue *> &values) const
{
	unsigned int idx = GetObjectIndex(objectId);
	if (idx == (unsigned int) -1)
		return false;
	TrackedObject *to = objects[idx];
	DataStructures::List<TimeAndValueQueue*> itemList;
	DataStructures::List<RakString> keyList;
	to->dataQueues.GetAsList(itemList,keyList,_FILE_AND_LINE_);
	Time curTime = GetTime();

	DataStructures::OrderedList<TimeAndValueQueue*, TimeAndValueQueue*,TimeAndValueQueueCompAsc> sortedQueues;
	for (unsigned int i=0; i < itemList.Size(); i++)
	{
		TimeAndValueQueue *tavq = itemList[i];
		tavq->CullExpiredValues(curTime);

		if (sortType == SH_SORT_BY_RECENT_SUM_ASCENDING || sortType == SH_SORT_BY_RECENT_SUM_DESCENDING)
			tavq->sortValue = tavq->GetRecentSum();
		else if (sortType == SH_SORT_BY_LONG_TERM_SUM_ASCENDING || sortType == SH_SORT_BY_LONG_TERM_SUM_DESCENDING)
			tavq->sortValue = tavq->GetLongTermSum();
		else if (sortType == SH_SORT_BY_RECENT_SUM_OF_SQUARES_ASCENDING || sortType == SH_SORT_BY_RECENT_SUM_OF_SQUARES_DESCENDING)
			tavq->sortValue = tavq->GetRecentSumOfSquares();
		else if (sortType == SH_SORT_BY_RECENT_AVERAGE_ASCENDING || sortType == SH_SORT_BY_RECENT_AVERAGE_DESCENDING)
			tavq->sortValue = tavq->GetRecentAverage();
		else if (sortType == SH_SORT_BY_LONG_TERM_AVERAGE_ASCENDING || sortType == SH_SORT_BY_LONG_TERM_AVERAGE_DESCENDING)
			tavq->sortValue = tavq->GetLongTermAverage();
		else if (sortType == SH_SORT_BY_RECENT_HIGHEST_ASCENDING || sortType == SH_SORT_BY_RECENT_HIGHEST_DESCENDING)
			tavq->sortValue = tavq->GetRecentHighest();
		else if (sortType == SH_SORT_BY_RECENT_LOWEST_ASCENDING || sortType == SH_SORT_BY_RECENT_LOWEST_DESCENDING)
			tavq->sortValue = tavq->GetRecentLowest();
		else if (sortType == SH_SORT_BY_LONG_TERM_HIGHEST_ASCENDING || sortType == SH_SORT_BY_LONG_TERM_HIGHEST_DESCENDING)
			tavq->sortValue = tavq->GetLongTermHighest();
		else
			tavq->sortValue = tavq->GetLongTermLowest();

		if (
			sortType == SH_SORT_BY_RECENT_SUM_ASCENDING ||
			sortType == SH_SORT_BY_LONG_TERM_SUM_ASCENDING ||
			sortType == SH_SORT_BY_RECENT_SUM_OF_SQUARES_ASCENDING ||
			sortType == SH_SORT_BY_RECENT_AVERAGE_ASCENDING ||
			sortType == SH_SORT_BY_LONG_TERM_AVERAGE_ASCENDING ||
			sortType == SH_SORT_BY_RECENT_HIGHEST_ASCENDING ||
			sortType == SH_SORT_BY_RECENT_LOWEST_ASCENDING ||
			sortType == SH_SORT_BY_LONG_TERM_HIGHEST_ASCENDING ||
			sortType == SH_SORT_BY_LONG_TERM_LOWEST_ASCENDING)
			sortedQueues.Insert(tavq, tavq, false, _FILE_AND_LINE_, TimeAndValueQueueCompAsc);
		else
			sortedQueues.Insert(tavq, tavq, false, _FILE_AND_LINE_, TimeAndValueQueueCompDesc);
	}

	for (unsigned int i=0; i < sortedQueues.Size(); i++)
		values.Push(sortedQueues[i], _FILE_AND_LINE_);
	return true;
}
void StatisticsHistory::MergeAllObjectsOnKey(RakString key, TimeAndValueQueue *tavqOutput, SHDataCategory dataCategory) const
{
	tavqOutput->Clear();

	Time curTime = GetTime();

	// Find every object with this key
	for (unsigned int idx=0; idx < objects.Size(); idx++)
	{
		TrackedObject *to = objects[idx];
		DataStructures::HashIndex hi = to->dataQueues.GetIndexOf(key);
		if (hi.IsInvalid()==false)
		{
			TimeAndValueQueue *tavqInput = to->dataQueues.ItemAtIndex(hi);
			tavqInput->CullExpiredValues(curTime);
			TimeAndValueQueue::MergeSets(tavqOutput, dataCategory, tavqInput, dataCategory, tavqOutput);
		}
	}
}
void StatisticsHistory::GetUniqueKeyList(DataStructures::List<RakString> &keys)
{
	keys.Clear(true, _FILE_AND_LINE_);

	for (unsigned int idx=0; idx < objects.Size(); idx++)
	{
		TrackedObject *to = objects[idx];
		DataStructures::List<TimeAndValueQueue*> itemList;
		DataStructures::List<SLNet::RakString> keyList;
		to->dataQueues.GetAsList(itemList, keyList, _FILE_AND_LINE_);
		for (unsigned int k=0; k < keyList.Size(); k++)
		{
			bool hasKey=false;
			for (unsigned int j=0; j < keys.Size(); j++)
			{
				if (keys[j]==keyList[k])
				{
					hasKey=true;
					break;
				}
			}

			if (hasKey==false)
				keys.Push(keyList[k], _FILE_AND_LINE_);
		}
	}
}
StatisticsHistory::TimeAndValueQueue::TimeAndValueQueue()
{
	Clear();
}
StatisticsHistory::TimeAndValueQueue::~TimeAndValueQueue(){}
void StatisticsHistory::TimeAndValueQueue::SetTimeToTrackValues(Time t)
{
	timeToTrackValues = t;
}
Time StatisticsHistory::TimeAndValueQueue::GetTimeToTrackValues(void) const {return timeToTrackValues;}
SHValueType StatisticsHistory::TimeAndValueQueue::GetRecentSum(void) const {return recentSum;}
SHValueType StatisticsHistory::TimeAndValueQueue::GetRecentSumOfSquares(void) const {return recentSumOfSquares;}
SHValueType StatisticsHistory::TimeAndValueQueue::GetLongTermSum(void) const {return longTermSum;}
SHValueType StatisticsHistory::TimeAndValueQueue::GetRecentAverage(void) const
{
	if (values.Size() > 0)
		return recentSum / (SHValueType) values.Size();
	else
		return 0;
}
SHValueType StatisticsHistory::TimeAndValueQueue::GetRecentLowest(void) const
{
	SHValueType out = SH_TYPE_MAX;
	for (unsigned int idx=0; idx < values.Size(); idx++)
	{
		if (values[idx].val < out)
			out = values[idx].val;
	}
	return out;
}
SHValueType StatisticsHistory::TimeAndValueQueue::GetRecentHighest(void) const
{
	SHValueType out = -SH_TYPE_MAX;
	for (unsigned int idx=0; idx < values.Size(); idx++)
	{
		if (values[idx].val > out)
			out = values[idx].val;
	}
	return out;
}
SHValueType StatisticsHistory::TimeAndValueQueue::GetRecentStandardDeviation(void) const
{
	if (values.Size()==0)
		return 0;

	SHValueType recentMean= GetRecentAverage();
	SHValueType squareOfMean = recentMean * recentMean;
	SHValueType meanOfSquares = GetRecentSumOfSquares() / (SHValueType) values.Size();
	return meanOfSquares - squareOfMean;
}
SHValueType StatisticsHistory::TimeAndValueQueue::GetLongTermAverage(void) const
{
	if (longTermCount == 0)
		return 0;
	return longTermSum / longTermCount;
}
SHValueType StatisticsHistory::TimeAndValueQueue::GetLongTermLowest(void) const {return longTermLowest;}
SHValueType StatisticsHistory::TimeAndValueQueue::GetLongTermHighest(void) const {return longTermHighest;}
Time StatisticsHistory::TimeAndValueQueue::GetTimeRange(void) const
{
	if (values.Size()<2)
		return 0;
	return values[values.Size()-1].time - values[0].time;
}
SHValueType StatisticsHistory::TimeAndValueQueue::GetSumSinceTime(Time t) const
{
	SHValueType sum = 0;
	for (int i=values.Size(); i > 0; --i)
	{
		if (values[i-1].time>=t)
			sum+=values[i-1].val;
	}
	return sum;
}
void StatisticsHistory::TimeAndValueQueue::MergeSets( const TimeAndValueQueue *lhs, SHDataCategory lhsDataCategory, const TimeAndValueQueue *rhs, SHDataCategory rhsDataCategory, TimeAndValueQueue *output )
{
	// Two ways to merge:
	// 1. Treat rhs as just more data points.
	// 1A. Sums are just added. If two values have the same time, just put in queue twice
	// 1B. longTermLowest and longTermHighest are the lowest and highest of the two sets
	// 
	// 2. Add by time. If time for the other set is missing, calculate slope to extrapolate
	// 2A. Have to recalculate recentSum, recentSumOfSquares.
	// 2B. longTermSum, longTermCount, longTermLowest, longTermHighest are unknown

	if (lhs!=output)
	{
		output->key = lhs->key;
		output->timeToTrackValues = lhs->timeToTrackValues;
	}
	else
	{
		output->key = rhs->key;
		output->timeToTrackValues = rhs->timeToTrackValues;
	}

	unsigned int lhsIndex, rhsIndex;
	lhsIndex=0;
	rhsIndex=0;

	// I use local valuesOutput in case lhs==output || rhs==output
	DataStructures::Queue<TimeAndValue> valuesOutput;

	if (lhsDataCategory==StatisticsHistory::DC_DISCRETE && rhsDataCategory==StatisticsHistory::DC_DISCRETE)
	{
		while (rhsIndex < rhs->values.Size() && lhsIndex < lhs->values.Size())
		{
			if (rhs->values[rhsIndex].time < lhs->values[lhsIndex].time)
			{
				valuesOutput.Push(rhs->values[rhsIndex], _FILE_AND_LINE_ );
				rhsIndex++;
			}
			else if (rhs->values[rhsIndex].time > lhs->values[lhsIndex].time)
			{
				valuesOutput.Push(lhs->values[rhsIndex], _FILE_AND_LINE_ );
				lhsIndex++;
			}
			else
			{
				valuesOutput.Push(rhs->values[rhsIndex], _FILE_AND_LINE_ );
				rhsIndex++;
				valuesOutput.Push(lhs->values[rhsIndex], _FILE_AND_LINE_ );
				lhsIndex++;
			}
		}

		while (rhsIndex < rhs->values.Size())
		{
			valuesOutput.Push(rhs->values[rhsIndex], _FILE_AND_LINE_ );
			rhsIndex++;
		}
		while (lhsIndex < lhs->values.Size())
		{
			valuesOutput.Push(lhs->values[lhsIndex], _FILE_AND_LINE_ );
			lhsIndex++;
		}

		output->recentSum = lhs->recentSum + rhs->recentSum;
		output->recentSumOfSquares = lhs->recentSumOfSquares + rhs->recentSumOfSquares;
		output->longTermSum = lhs->longTermSum + rhs->longTermSum;
		output->longTermCount = lhs->longTermCount + rhs->longTermCount;
		if (lhs->longTermLowest < rhs->longTermLowest)
			output->longTermLowest = lhs->longTermLowest;
		else
			output->longTermLowest = rhs->longTermLowest;
		if (lhs->longTermHighest > rhs->longTermHighest)
			output->longTermHighest = lhs->longTermHighest;
		else
			output->longTermHighest = rhs->longTermHighest;
	}
	else
	{
		TimeAndValue lastTimeAndValueLhs, lastTimeAndValueRhs;
		lastTimeAndValueLhs.time=0;
		lastTimeAndValueLhs.val=0;
		lastTimeAndValueRhs.time=0;
		lastTimeAndValueRhs.val=0;
		SHValueType lastSlopeLhs=0;
		SHValueType lastSlopeRhs=0;
		Time timeSinceOppositeValue;

		TimeAndValue newTimeAndValue;

		while (rhsIndex < rhs->values.Size() && lhsIndex < lhs->values.Size())
		{
			if (rhs->values[rhsIndex].time < lhs->values[lhsIndex].time)
			{
				timeSinceOppositeValue = rhs->values[rhsIndex].time - lastTimeAndValueLhs.time;
				newTimeAndValue.val = rhs->values[rhsIndex].val + lastTimeAndValueLhs.val + lastSlopeLhs * timeSinceOppositeValue;
				newTimeAndValue.time = rhs->values[rhsIndex].time;
				lastTimeAndValueRhs = rhs->values[rhsIndex];
				if (rhsIndex>0 && rhs->values[rhsIndex].time != rhs->values[rhsIndex-1].time && rhsDataCategory==StatisticsHistory::DC_CONTINUOUS)
					lastSlopeRhs = (rhs->values[rhsIndex].val - rhs->values[rhsIndex-1].val) / (SHValueType) (rhs->values[rhsIndex].time - rhs->values[rhsIndex-1].time);
				rhsIndex++;
			}
			else if (lhs->values[lhsIndex].time < rhs->values[rhsIndex].time)
			{
				timeSinceOppositeValue = lhs->values[lhsIndex].time - lastTimeAndValueRhs.time;
				newTimeAndValue.val = lhs->values[lhsIndex].val + lastTimeAndValueRhs.val + lastSlopeRhs * timeSinceOppositeValue;
				newTimeAndValue.time = lhs->values[lhsIndex].time;
				lastTimeAndValueLhs = lhs->values[lhsIndex];
				if (lhsIndex>0 && lhs->values[lhsIndex].time != lhs->values[lhsIndex-1].time && lhsDataCategory==StatisticsHistory::DC_CONTINUOUS)
					lastSlopeLhs = (lhs->values[lhsIndex].val - lhs->values[lhsIndex-1].val) / (SHValueType) (lhs->values[lhsIndex].time - lhs->values[lhsIndex-1].time);
				lhsIndex++;
			}
			else
			{
				newTimeAndValue.val = lhs->values[lhsIndex].val + rhs->values[rhsIndex].val;
				newTimeAndValue.time = lhs->values[lhsIndex].time;
				lastTimeAndValueRhs = rhs->values[rhsIndex];
				lastTimeAndValueLhs = lhs->values[lhsIndex];
				if (rhsIndex>0 && rhs->values[rhsIndex].time != rhs->values[rhsIndex-1].time && rhsDataCategory==StatisticsHistory::DC_CONTINUOUS)
					lastSlopeRhs = (rhs->values[rhsIndex].val - rhs->values[rhsIndex-1].val) / (SHValueType) (rhs->values[rhsIndex].time - rhs->values[rhsIndex-1].time);
				if (lhsIndex>0 && lhs->values[lhsIndex].time != lhs->values[lhsIndex-1].time && lhsDataCategory==StatisticsHistory::DC_CONTINUOUS)
					lastSlopeLhs = (lhs->values[lhsIndex].val - lhs->values[lhsIndex-1].val) / (SHValueType) (lhs->values[lhsIndex].time - lhs->values[lhsIndex-1].time);
				lhsIndex++;
				rhsIndex++;
			}

			valuesOutput.Push(newTimeAndValue, _FILE_AND_LINE_ );
		}

		while (rhsIndex < rhs->values.Size())
		{
			timeSinceOppositeValue = rhs->values[rhsIndex].time - lastTimeAndValueLhs.time;
			newTimeAndValue.val = rhs->values[rhsIndex].val + lastTimeAndValueLhs.val + lastSlopeLhs * timeSinceOppositeValue;
			newTimeAndValue.time = rhs->values[rhsIndex].time;
			valuesOutput.Push(newTimeAndValue, _FILE_AND_LINE_ );
			rhsIndex++;
		}
		while (lhsIndex < lhs->values.Size())
		{
			timeSinceOppositeValue = lhs->values[lhsIndex].time - lastTimeAndValueRhs.time;
			newTimeAndValue.val = lhs->values[lhsIndex].val + lastTimeAndValueRhs.val + lastSlopeRhs * timeSinceOppositeValue;
			newTimeAndValue.time = lhs->values[lhsIndex].time;
			valuesOutput.Push(newTimeAndValue, _FILE_AND_LINE_ );
			lhsIndex++;
		}

		output->recentSum = 0;
		output->recentSumOfSquares = 0;
		for (unsigned int i=0; i < valuesOutput.Size(); i++)
		{
			output->recentSum += valuesOutput[i].val;
			output->recentSumOfSquares += valuesOutput[i].val * valuesOutput[i].val;
		}
	}

	output->values = valuesOutput;
}
void StatisticsHistory::TimeAndValueQueue::ResizeSampleSet( int maxSamples, DataStructures::Queue<StatisticsHistory::TimeAndValue> &histogram, SHDataCategory dataCategory, Time timeClipStart, Time timeClipEnd )
{
	histogram.Clear(_FILE_AND_LINE_);
	if (maxSamples==0)
		return;
	Time timeRange = GetTimeRange();
	if (timeRange==0)
		return;
	if (maxSamples==1)
	{
		StatisticsHistory::TimeAndValue tav;
		tav.time = timeRange;
		tav.val = GetRecentSum();
		histogram.Push(tav, _FILE_AND_LINE_);
		return;
	}
	Time interval = timeRange / maxSamples;
	if (interval==0)
		interval=1;
	unsigned int dataIndex;
	Time timeBoundary;
	StatisticsHistory::TimeAndValue currentSum;
	Time currentTime;
	SHValueType numSamples;
	Time endTime;
	
	numSamples=0;
	endTime = values[values.Size()-1].time;
	dataIndex=0;
	currentTime=values[0].time;
	currentSum.val=0;
	currentSum.time=values[0].time + interval / 2;
	timeBoundary = values[0].time + interval;
	while (timeBoundary <= endTime)
	{
		while (dataIndex < values.Size() && values[dataIndex].time <= timeBoundary)
		{
			currentSum.val += values[dataIndex].val;
			dataIndex++;
			numSamples++;
		}

		if (dataCategory==DC_CONTINUOUS)
		{
			if (dataIndex > 0 &&
				dataIndex < values.Size() &&
				values[dataIndex-1].time < timeBoundary &&
				values[dataIndex].time > timeBoundary)
			{
				SHValueType interpolatedValue = Interpolate(values[dataIndex-1], values[dataIndex], timeBoundary);
				currentSum.val+=interpolatedValue;
				numSamples++;
			}

			if (numSamples > 1)
			{
				currentSum.val /= numSamples;
			}
		}

		histogram.Push(currentSum, _FILE_AND_LINE_);
		currentSum.time=timeBoundary + interval / 2;
		timeBoundary += interval;
		currentSum.val=0;
		numSamples=0;
	}

	
	if ( timeClipStart!=0 && histogram.Size()>=1)
	{
		timeClipStart = histogram.Peek().time+timeClipStart;
		if (histogram.PeekTail().time < timeClipStart)
		{
			histogram.Clear(_FILE_AND_LINE_);
		}
		else if (histogram.Size()>=2 && histogram.Peek().time < timeClipStart)
		{
			StatisticsHistory::TimeAndValue tav;

			do
			{
				tav = histogram.Pop();

				if (histogram.Peek().time == timeClipStart)
				{
					break;
				}
				else if (histogram.Peek().time > timeClipStart)
				{
					StatisticsHistory::TimeAndValue tav2;
					tav2.val = StatisticsHistory::TimeAndValueQueue::Interpolate(tav, histogram.Peek(), timeClipStart);
					tav2.time=timeClipStart;
					histogram.PushAtHead(tav2, 0, _FILE_AND_LINE_);
					break;
				}
			} while (histogram.Size()>=2);
		}
	}

	if ( timeClipEnd!=0 && histogram.Size()>=1)
	{
		timeClipEnd = histogram.PeekTail().time-timeClipEnd;
		if (histogram.Peek().time > timeClipEnd)
		{
			histogram.Clear(_FILE_AND_LINE_);
		}
		else if (histogram.Size()>=2 && histogram.PeekTail().time > timeClipEnd)
		{
			StatisticsHistory::TimeAndValue tav;

			do
			{
				tav = histogram.PopTail();

				if (histogram.PeekTail().time == timeClipEnd)
				{
					break;
				}
				else if (histogram.PeekTail().time < timeClipEnd)
				{
					StatisticsHistory::TimeAndValue tav2;
					tav2.val = StatisticsHistory::TimeAndValueQueue::Interpolate(tav, histogram.PeekTail(), timeClipEnd);
					tav2.time=timeClipEnd;
					histogram.Push(tav2, _FILE_AND_LINE_);
					break;
				}
			} while (histogram.Size()>=2);
		}
	}
}
void StatisticsHistory::TimeAndValueQueue::CullExpiredValues(Time curTime)
{
	while (values.Size())
	{
		StatisticsHistory::TimeAndValue tav = values.Peek();
		if (curTime - tav.time > timeToTrackValues)
		{
			recentSum -= tav.val;
			recentSumOfSquares -= tav.val * tav.val;
			values.Pop();
		}
		else
		{
			break;
		}
	}
}
SHValueType StatisticsHistory::TimeAndValueQueue::Interpolate(StatisticsHistory::TimeAndValue t1, StatisticsHistory::TimeAndValue t2, Time time)
{
	if (t2.time==t1.time)
		return (t1.val + t2.val) / 2;
//	if (t2.time > t1.time)
//	{
		SHValueType slope = (t2.val - t1.val) / ((SHValueType) t2.time - (SHValueType) t1.time);
		return t1.val + slope * ((SHValueType) time - (SHValueType) t1.time);
// 	}
// 	else
// 	{
// 		SHValueType slope = (t1.val - t2.val) / (SHValueType) (t1.time - t2.time);
// 		return t2.val + slope * (SHValueType) (time - t2.time);
// 	}
}
void StatisticsHistory::TimeAndValueQueue::Clear(void)
{
	recentSum = 0;
	recentSumOfSquares = 0;
	longTermSum = 0;
	longTermCount = 0;
	longTermLowest = SH_TYPE_MAX;
	longTermHighest = -SH_TYPE_MAX;
	values.Clear(_FILE_AND_LINE_);
}
StatisticsHistory::TimeAndValueQueue& StatisticsHistory::TimeAndValueQueue::operator = ( const TimeAndValueQueue& input )
{
	values=input.values;
	timeToTrackValues=input.timeToTrackValues;
	key=input.key;
	recentSum=input.recentSum;
	recentSumOfSquares=input.recentSumOfSquares;
	longTermSum=input.longTermSum;
	longTermCount=input.longTermCount;
	longTermLowest=input.longTermLowest;
	longTermHighest=input.longTermHighest;
	return *this;
}
StatisticsHistory::TrackedObject::TrackedObject() {}
StatisticsHistory::TrackedObject::~TrackedObject()
{
	DataStructures::List<StatisticsHistory::TimeAndValueQueue*> itemList;
	DataStructures::List<RakString> keyList;
	for (unsigned int idx=0; idx < itemList.Size(); idx++)
		SLNet::OP_DELETE(itemList[idx], _FILE_AND_LINE_);
}
unsigned int StatisticsHistory::GetObjectIndex(uint64_t objectId) const
{
	bool objectExists;
	unsigned int idx = objects.GetIndexFromKey(objectId, &objectExists);
	if (objectExists)
		return idx;
	return (unsigned int) -1;
}
StatisticsHistoryPlugin::StatisticsHistoryPlugin()
{
	addNewConnections = true;
	removeLostConnections = true;
	newConnectionsObjectType = 0;
}
StatisticsHistoryPlugin::~StatisticsHistoryPlugin()
{
}
void StatisticsHistoryPlugin::SetTrackConnections(bool _addNewConnections, int _newConnectionsObjectType, bool _removeLostConnections)
{
	addNewConnections = _addNewConnections;
	removeLostConnections = _removeLostConnections;
	newConnectionsObjectType = _newConnectionsObjectType;
}
void StatisticsHistoryPlugin::Update(void)
{
	DataStructures::List<SystemAddress> addresses;
	DataStructures::List<RakNetGUID> guids;
	DataStructures::List<RakNetStatistics> stats;
	rakPeerInterface->GetStatisticsList(addresses, guids, stats);

	Time curTime = GetTime();
	for (unsigned int idx = 0; idx < guids.Size(); idx++)
	{
		unsigned int objectIndex = statistics.GetObjectIndex(guids[idx].g);
		if (objectIndex!=(unsigned int)-1)
		{
			statistics.AddValueByIndex(objectIndex,
				"RN_ACTUAL_BYTES_SENT",
				(SHValueType) stats[idx].valueOverLastSecond[ACTUAL_BYTES_SENT],
				curTime, false);

			statistics.AddValueByIndex(objectIndex,
				"RN_USER_MESSAGE_BYTES_RESENT",
				(SHValueType) stats[idx].valueOverLastSecond[USER_MESSAGE_BYTES_RESENT],
				curTime, false);

			statistics.AddValueByIndex(objectIndex,
				"RN_ACTUAL_BYTES_RECEIVED",
				(SHValueType) stats[idx].valueOverLastSecond[ACTUAL_BYTES_RECEIVED],
				curTime, false);

			statistics.AddValueByIndex(objectIndex,
				"RN_USER_MESSAGE_BYTES_PUSHED",
				(SHValueType) stats[idx].valueOverLastSecond[USER_MESSAGE_BYTES_PUSHED],
				curTime, false);

			statistics.AddValueByIndex(objectIndex,
				"RN_USER_MESSAGE_BYTES_RECEIVED_PROCESSED",
				(SHValueType) stats[idx].valueOverLastSecond[USER_MESSAGE_BYTES_RECEIVED_PROCESSED],
				curTime, false);

			statistics.AddValueByIndex(objectIndex,
				"RN_lastPing",
				(SHValueType) rakPeerInterface->GetLastPing(guids[idx]),
				curTime, false);

			statistics.AddValueByIndex(objectIndex,
				"RN_bytesInResendBuffer",
				(SHValueType) stats[idx].bytesInResendBuffer,
				curTime, false);
			
			statistics.AddValueByIndex(objectIndex,
				"RN_packetlossLastSecond",
				(SHValueType) stats[idx].packetlossLastSecond,
				curTime, false);
		}

	}

	/*
	RakNetStatistics rns;
	DataStructures::List<SystemAddress> addresses;
	DataStructures::List<RakNetGUID> guids;
	rakPeerInterface->GetSystemList(addresses, guids);
	for (unsigned int idx = 0; idx < guids.Size(); idx++)
	{
		rakPeerInterface->GetStatistics(remoteSystems[idx], &rns);
		statistics.AddValue();

		bool AddValue(uint64_t objectId, RakString key, SHValueType val, Time curTime);

	}
	*/
}
/*
void StatisticsHistoryPlugin::OnDirectSocketSend(const char *data, const BitSize_t bitsUsed, SystemAddress remoteSystemAddress)
{
	// Would have to use GetGuidFromSystemAddress for every send
}
void StatisticsHistoryPlugin::OnDirectSocketReceive(const char *data, const BitSize_t bitsUsed, SystemAddress remoteSystemAddress)
{
}
*/
void StatisticsHistoryPlugin::OnClosedConnection(const SystemAddress &systemAddress, RakNetGUID rakNetGUID, PI2_LostConnectionReason lostConnectionReason )
{
	(void) lostConnectionReason;
	(void) systemAddress;

	if (removeLostConnections)
	{
		statistics.RemoveObject(rakNetGUID.g, 0);
	}
}
void StatisticsHistoryPlugin::OnNewConnection(const SystemAddress &systemAddress, RakNetGUID rakNetGUID, bool isIncoming)
{
	(void) systemAddress;
	(void) isIncoming;

	if (addNewConnections)
	{
		statistics.AddObject(StatisticsHistory::TrackedObjectData(rakNetGUID.g, newConnectionsObjectType, 0));
	}
}
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

#endif // _RAKNET_SUPPORT_StatisticsHistory==1
