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

/// \file DS_OrderedChannelHeap.h
/// \internal
/// \brief Ordered Channel Heap .  This is a heap where you add to it on multiple ordered channels, with each channel having a different weight.
///


#ifndef __RAKNET_ORDERED_CHANNEL_HEAP_H
#define __RAKNET_ORDERED_CHANNEL_HEAP_H

#include "DS_Heap.h"
#include "DS_Map.h"
#include "DS_Queue.h"
#include "Export.h"
#include "assert.h"
#include "Rand.h"

/// The namespace DataStructures was only added to avoid compiler errors for commonly named data structures
/// As these data structures are stand-alone, you can use them outside of RakNet for your own projects if you wish.
namespace DataStructures
{
	template <class channel_key_type, class heap_data_type, int (*channel_key_comparison_func)(const channel_key_type&, const channel_key_type&)=defaultMapKeyComparison<channel_key_type> >
	class RAK_DLL_EXPORT OrderedChannelHeap
	{
	public:
		static void IMPLEMENT_DEFAULT_COMPARISON(void) {DataStructures::defaultMapKeyComparison<channel_key_type>(channel_key_type(),channel_key_type());}

		OrderedChannelHeap();
		~OrderedChannelHeap();
		void Push(const channel_key_type &channelID, const heap_data_type &data);
		void PushAtHead(const unsigned index, const channel_key_type &channelID, const heap_data_type &data);
		heap_data_type Pop(const unsigned startingIndex=0);
		heap_data_type Peek(const unsigned startingIndex) const;
		void AddChannel(const channel_key_type &channelID, const double weight);
		void RemoveChannel(channel_key_type channelID);
		void Clear(void);
		heap_data_type& operator[] ( const unsigned int position ) const;
		unsigned ChannelSize(const channel_key_type &channelID);
		unsigned Size(void) const;

		struct QueueAndWeight
		{
			DataStructures::Queue<double> randResultQueue;
			double weight;
			bool signalDeletion;
		};

		struct HeapChannelAndData
		{
			HeapChannelAndData() {}
			HeapChannelAndData(const channel_key_type &_channel, const heap_data_type &_data) : data(_data), channel(_channel) {}
			heap_data_type data;
			channel_key_type channel;
		};

	protected:
		DataStructures::Map<channel_key_type, QueueAndWeight*, channel_key_comparison_func> map;
		DataStructures::Heap<double, HeapChannelAndData, true> heap;
		void GreatestRandResult(void);
	};

	template <class channel_key_type, class heap_data_type, int (*channel_key_comparison_func)(const channel_key_type&, const channel_key_type&)>
		OrderedChannelHeap<channel_key_type, heap_data_type, channel_key_comparison_func>::OrderedChannelHeap()
	{
	}

	template <class channel_key_type, class heap_data_type, int (*channel_key_comparison_func)(const channel_key_type&, const channel_key_type&)>
		OrderedChannelHeap<channel_key_type, heap_data_type, channel_key_comparison_func>::~OrderedChannelHeap()
	{
		Clear();
	}

	template <class channel_key_type, class heap_data_type, int (*channel_key_comparison_func)(const channel_key_type&, const channel_key_type&)>
	void OrderedChannelHeap<channel_key_type, heap_data_type, channel_key_comparison_func>::Push(const channel_key_type &channelID, const heap_data_type &data)
	{
		PushAtHead(MAX_UNSIGNED_LONG, channelID, data);
	}

	template <class channel_key_type, class heap_data_type, int (*channel_key_comparison_func)(const channel_key_type&, const channel_key_type&)>
	void OrderedChannelHeap<channel_key_type, heap_data_type, channel_key_comparison_func>::GreatestRandResult(void)
	{
		double greatest;
		unsigned i;
		greatest=0.0;
		for (i=0; i < map.Size(); i++)
		{
			if (map[i]->randResultQueue.Size() && map[i]->randResultQueue[0]>greatest)
				greatest=map[i]->randResultQueue[0];
		}
		return greatest;
	}

	template <class channel_key_type, class heap_data_type, int (*channel_key_comparison_func)(const channel_key_type&, const channel_key_type&)>
	void OrderedChannelHeap<channel_key_type, heap_data_type, channel_key_comparison_func>::PushAtHead(const unsigned index, const channel_key_type &channelID, const heap_data_type &data)
	{
		// If an assert hits here then this is an unknown channel.  Call AddChannel first.
		QueueAndWeight *queueAndWeight=map.Get(channelID);
		double maxRange, minRange, rnd;
		if (queueAndWeight->randResultQueue.Size()==0)
		{
			// Set maxRange to the greatest random number waiting to be returned, rather than 1.0 necessarily
			// This is so weights are scaled similarly among channels.  For example, if the head weight for a used channel was .25
			// and then we added another channel, the new channel would need to choose between .25 and 0
			// If we chose between 1.0 and 0, it would be 1/.25 (4x) more likely to be at the head of the heap than it should be
			maxRange=GreatestRandResult();
			if (maxRange==0.0)
				maxRange=1.0;
			minRange=0.0;
		}
		else if (index >= queueAndWeight->randResultQueue.Size())
		{
			maxRange=queueAndWeight->randResultQueue[queueAndWeight->randResultQueue.Size()-1]*.99999999;
			minRange=0.0;
		}
		else
		{
			if (index==0)
			{
				maxRange=GreatestRandResult();
				if (maxRange==queueAndWeight->randResultQueue[0])
					maxRange=1.0;
			}
			else if (index >= queueAndWeight->randResultQueue.Size())
				maxRange=queueAndWeight->randResultQueue[queueAndWeight->randResultQueue.Size()-1]*.99999999;
			else
				maxRange=queueAndWeight->randResultQueue[index-1]*.99999999;

			minRange=maxRange=queueAndWeight->randResultQueue[index]*1.00000001;
		}
		
#ifdef _DEBUG
		RakAssert(maxRange!=0.0);
#endif
		rnd=frandomMT() * (maxRange - minRange);
		if (rnd==0.0)
			rnd=maxRange/2.0;

		if (index >= queueAndWeight->randResultQueue.Size())
			queueAndWeight->randResultQueue.Push(rnd);
		else
			queueAndWeight->randResultQueue.PushAtHead(rnd, index);

		heap.Push(rnd*queueAndWeight->weight, HeapChannelAndData(channelID, data));
	}

	template <class channel_key_type, class heap_data_type, int (*channel_key_comparison_func)(const channel_key_type&, const channel_key_type&)>
	heap_data_type OrderedChannelHeap<channel_key_type, heap_data_type, channel_key_comparison_func>::Pop(const unsigned startingIndex)
	{
		RakAssert(startingIndex < heap.Size());

		QueueAndWeight *queueAndWeight=map.Get(heap[startingIndex].channel);
		if (startingIndex!=0)
		{
			// Ugly - have to count in the heap how many nodes have the same channel, so we know where to delete from in the queue
			unsigned indiceCount=0;
			unsigned i;
			for (i=0; i < startingIndex; i++)
				if (channel_key_comparison_func(heap[i].channel,heap[startingIndex].channel)==0)
					indiceCount++;
			queueAndWeight->randResultQueue.RemoveAtIndex(indiceCount);
		}
		else
		{
			// TODO - ordered channel heap uses progressively lower values as items are inserted.  But this won't give relative ordering among channels.  I have to renormalize after every pop.
			queueAndWeight->randResultQueue.Pop();
		}

		// Try to remove the channel after every pop, because doing so is not valid while there are elements in the list.
		if (queueAndWeight->signalDeletion)
			RemoveChannel(heap[startingIndex].channel);

		return heap.Pop(startingIndex).data;
	}

	template <class channel_key_type, class heap_data_type, int (*channel_key_comparison_func)(const channel_key_type&, const channel_key_type&)>
	heap_data_type OrderedChannelHeap<channel_key_type, heap_data_type, channel_key_comparison_func>::Peek(const unsigned startingIndex) const
	{
		HeapChannelAndData heapChannelAndData = heap.Peek(startingIndex);
		return heapChannelAndData.data;
	}

	template <class channel_key_type, class heap_data_type, int (*channel_key_comparison_func)(const channel_key_type&, const channel_key_type&)>
	void OrderedChannelHeap<channel_key_type, heap_data_type, channel_key_comparison_func>::AddChannel(const channel_key_type &channelID, const double weight)
	{
		QueueAndWeight *qaw = SLNet::OP_NEW<QueueAndWeight>( _FILE_AND_LINE_ );
		qaw->weight=weight;
		qaw->signalDeletion=false;
		map.SetNew(channelID, qaw);
	}

	template <class channel_key_type, class heap_data_type, int (*channel_key_comparison_func)(const channel_key_type&, const channel_key_type&)>
		void OrderedChannelHeap<channel_key_type, heap_data_type, channel_key_comparison_func>::RemoveChannel(channel_key_type channelID)
	{
		if (map.Has(channelID))
		{
			unsigned i;
			i=map.GetIndexAtKey(channelID);
			if (map[i]->randResultQueue.Size()==0)
			{
				SLNet::OP_DELETE(map[i], _FILE_AND_LINE_);
				map.RemoveAtIndex(i);
			}
			else
			{
				// Signal this channel for deletion later, because the heap has nodes with this channel right now
				map[i]->signalDeletion=true;
			}
		}
	}

	template <class channel_key_type, class heap_data_type, int (*channel_key_comparison_func)(const channel_key_type&, const channel_key_type&)>
		unsigned OrderedChannelHeap<channel_key_type, heap_data_type, channel_key_comparison_func>::Size(void) const
	{
		return heap.Size();
	}

	template <class channel_key_type, class heap_data_type, int (*channel_key_comparison_func)(const channel_key_type&, const channel_key_type&)>
		heap_data_type& OrderedChannelHeap<channel_key_type, heap_data_type, channel_key_comparison_func>::operator[]( const unsigned int position ) const
	{
		return heap[position].data;
	}


	template <class channel_key_type, class heap_data_type, int (*channel_key_comparison_func)(const channel_key_type&, const channel_key_type&)>
		unsigned OrderedChannelHeap<channel_key_type, heap_data_type, channel_key_comparison_func>::ChannelSize(const channel_key_type &channelID)
	{
		QueueAndWeight *queueAndWeight=map.Get(channelID);
		return queueAndWeight->randResultQueue.Size();
	}

	template <class channel_key_type, class heap_data_type, int (*channel_key_comparison_func)(const channel_key_type&, const channel_key_type&)>
		void OrderedChannelHeap<channel_key_type, heap_data_type, channel_key_comparison_func>::Clear(void)
	{
		unsigned i;
		for (i=0; i < map.Size(); i++)
			SLNet::OP_DELETE(map[i], _FILE_AND_LINE_);
		map.Clear(_FILE_AND_LINE_);
		heap.Clear(_FILE_AND_LINE_);
	}
}

#endif
