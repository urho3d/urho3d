/*
 *  Copyright (c) 2014, Oculus VR, Inc.
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

/// \file DS_QueueLinkedList.h
/// \internal
/// \brief A queue implemented as a linked list.
///


#ifndef __QUEUE_LINKED_LIST_H
#define __QUEUE_LINKED_LIST_H

#include "DS_LinkedList.h" 
#include "Export.h"
#include "memoryoverride.h"

/// The namespace DataStructures was only added to avoid compiler errors for commonly named data structures
/// As these data structures are stand-alone, you can use them outside of RakNet for your own projects if you wish.
namespace DataStructures
{
	/// \brief A queue implemented using a linked list.  Rarely used.
	template <class QueueType>
	class RAK_DLL_EXPORT QueueLinkedList
	{
	
	public:
		QueueLinkedList();
		QueueLinkedList( const QueueLinkedList& original_copy );
		bool operator= ( const QueueLinkedList& original_copy );
		QueueType Pop( void );
		QueueType& Peek( void );
		QueueType& EndPeek( void );
		void Push( const QueueType& input );
		unsigned int Size( void );
		void Clear( void );
		void Compress( void );
		
	private:
		LinkedList<QueueType> data;
	};
	
	template <class QueueType>
	QueueLinkedList<QueueType>::QueueLinkedList()
	{
	}
	
	template <class QueueType>
	inline unsigned int QueueLinkedList<QueueType>::Size()
	{
		return data.Size();
	}
	
	template <class QueueType>
	inline QueueType QueueLinkedList<QueueType>::Pop( void )
	{
		data.Beginning();
		return ( QueueType ) data.Pop();
	}
	
	template <class QueueType>
	inline QueueType& QueueLinkedList<QueueType>::Peek( void )
	{
		data.Beginning();
		return ( QueueType ) data.Peek();
	}
	
	template <class QueueType>
	inline QueueType& QueueLinkedList<QueueType>::EndPeek( void )
	{
		data.End();
		return ( QueueType ) data.Peek();
	}
	
	template <class QueueType>
	void QueueLinkedList<QueueType>::Push( const QueueType& input )
	{
		data.End();
		data.Add( input );
	}
	
	template <class QueueType>
	QueueLinkedList<QueueType>::QueueLinkedList( const QueueLinkedList& original_copy )
	{
		data = original_copy.data;
	}
	
	template <class QueueType>
	bool QueueLinkedList<QueueType>::operator= ( const QueueLinkedList& original_copy )
	{
		if ( ( &original_copy ) == this )
			return false;
			
		data = original_copy.data;
	}
	
	template <class QueueType>
	void QueueLinkedList<QueueType>::Clear ( void )
	{
		data.Clear();
	}
} // End namespace

#endif
