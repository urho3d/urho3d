/*
 *  Original work: Copyright (c) 2014, Oculus VR, Inc.
 *  All rights reserved.
 *
 *  This source code is licensed under the BSD-style license found in the
 *  RakNet License.txt file in the licenses directory of this source tree. An additional grant 
 *  of patent rights can be found in the RakNet Patents.txt file in the same directory.
 *
 *
 *  Modified work: Copyright (c) 2016-2017, SLikeSoft UG (haftungsbeschränkt)
 *
 *  This source code was modified by SLikeSoft. Modifications are licensed under the MIT-style
 *  license found in the license.txt file in the root directory of this source tree.
 */

/// \file DS_Queue.h
/// \internal
/// \brief A queue used by RakNet.
///


#ifndef __QUEUE_H
#define __QUEUE_H

// Template classes have to have all the code in the header file
#include "assert.h"
#include "Export.h"
#include "memoryoverride.h"

/// The namespace DataStructures was only added to avoid compiler errors for commonly named data structures
/// As these data structures are stand-alone, you can use them outside of RakNet for your own projects if you wish.
namespace DataStructures
{
	/// \brief A queue implemented as an array with a read and write index.
	template <class queue_type>
	class RAK_DLL_EXPORT Queue
	{
	public:
		Queue();
		~Queue();
		Queue( const Queue& original_copy );
		bool operator= ( const Queue& original_copy );
		void Push( const queue_type& input, const char *file, unsigned int line );
		void PushAtHead( const queue_type& input, unsigned index, const char *file, unsigned int line );
		queue_type& operator[] ( unsigned int position ) const; // Not a normal thing you do with a queue but can be used for efficiency
		void RemoveAtIndex( unsigned int position ); // Not a normal thing you do with a queue but can be used for efficiency
		inline queue_type Peek( void ) const;
		inline queue_type PeekTail( void ) const;
		inline queue_type Pop( void );
		inline queue_type PopTail( void );
		// Debug: Set pointer to 0, for memory leak detection
		inline queue_type PopDeref( void );
		inline unsigned int Size( void ) const;
		inline bool IsEmpty(void) const;
		inline unsigned int AllocationSize( void ) const;
		inline void Clear( const char *file, unsigned int line );
		void Compress( const char *file, unsigned int line );
		bool Find ( const queue_type& q );
		void ClearAndForceAllocation( int size, const char *file, unsigned int line ); // Force a memory allocation to a certain larger size

	private:
		queue_type* array;
		unsigned int head;  // Array index for the head of the queue
		unsigned int tail; // Array index for the tail of the queue
		unsigned int allocation_size;
	};


	template <class queue_type>
		inline unsigned int Queue<queue_type>::Size( void ) const
	{
		if ( head <= tail )
			return tail -head;
		else
			return allocation_size -head + tail;
	}

	template <class queue_type>
	inline bool Queue<queue_type>::IsEmpty(void) const
	{
		return head==tail;
	}

	template <class queue_type>
	inline unsigned int Queue<queue_type>::AllocationSize( void ) const
	{
		return allocation_size;
	}

	template <class queue_type>
		Queue<queue_type>::Queue()
	{
		//allocation_size = 16;
		//array = SLNet::OP_NEW_ARRAY<queue_type>(allocation_size, _FILE_AND_LINE_ );
		allocation_size = 0;
		array=0;
		head = 0;
		tail = 0;
	}

	template <class queue_type>
		Queue<queue_type>::~Queue()
	{
		if (allocation_size>0)
			SLNet::OP_DELETE_ARRAY(array, _FILE_AND_LINE_);
	}

	template <class queue_type>
		inline queue_type Queue<queue_type>::Pop( void )
	{
#ifdef _DEBUG
		RakAssert( head != tail);
#endif
		//head=(head+1) % allocation_size;

		if ( ++head == allocation_size )
			head = 0;

		if ( head == 0 )
			return ( queue_type ) array[ allocation_size -1 ];

		return ( queue_type ) array[ head -1 ];
	}

	template <class queue_type>
	inline queue_type Queue<queue_type>::PopTail( void )
	{
#ifdef _DEBUG
		RakAssert( head != tail );
#endif
		if (tail!=0)
		{
			--tail;
			return ( queue_type ) array[ tail ];
		}
		else
		{
			tail=allocation_size-1;
			return ( queue_type ) array[ tail ];
		}
	}

	template <class queue_type>
		inline queue_type Queue<queue_type>::PopDeref( void )
		{
			if ( ++head == allocation_size )
				head = 0;

			queue_type q;
			if ( head == 0 )
			{
				q=array[ allocation_size -1 ];
				array[ allocation_size -1 ]=0;
				return q;
			}

			q=array[ head -1 ];
			array[ head -1 ]=0;
			return q;
		}

	template <class queue_type>
	void Queue<queue_type>::PushAtHead( const queue_type& input, unsigned index, const char *file, unsigned int line )
	{
		RakAssert(index <= Size());

		// Just force a reallocation, will be overwritten
		Push(input, file, line );

		if (Size()==1)
			return;

		unsigned writeIndex, readIndex, trueWriteIndex, trueReadIndex;
		writeIndex=Size()-1;
		readIndex=writeIndex-1;
		while (readIndex >= index)
		{
			if ( head + writeIndex >= allocation_size )
				trueWriteIndex = head + writeIndex - allocation_size;
			else
				trueWriteIndex = head + writeIndex;

			if ( head + readIndex >= allocation_size )
				trueReadIndex = head + readIndex - allocation_size;
			else
				trueReadIndex = head + readIndex;

			array[trueWriteIndex]=array[trueReadIndex];

			if (readIndex==0)
				break;
			writeIndex--;
			readIndex--;
		}

		if ( head + index >= allocation_size )
			trueWriteIndex = head + index - allocation_size;
		else
			trueWriteIndex = head + index;

		array[trueWriteIndex]=input;
	}


	template <class queue_type>
		inline queue_type Queue<queue_type>::Peek( void ) const
	{
#ifdef _DEBUG
		RakAssert( head != tail );
#endif

		return ( queue_type ) array[ head ];
	}

	template <class queue_type>
		inline queue_type Queue<queue_type>::PeekTail( void ) const
		{
#ifdef _DEBUG
			RakAssert( head != tail );
#endif
			if (tail!=0)
				return ( queue_type ) array[ tail-1 ];
			else
				return ( queue_type ) array[ allocation_size-1 ];
		}

	template <class queue_type>
		void Queue<queue_type>::Push( const queue_type& input, const char *file, unsigned int line )
	{
		if ( allocation_size == 0 )
		{
			array = SLNet::OP_NEW_ARRAY<queue_type>(16, file, line );
			head = 0;
			tail = 1;
			array[ 0 ] = input;
			allocation_size = 16;
			return ;
		}

		array[ tail++ ] = input;

		if ( tail == allocation_size )
			tail = 0;

		if ( tail == head )
		{
			//  unsigned int index=tail;

			// Need to allocate more memory.
			queue_type * new_array;
			new_array = SLNet::OP_NEW_ARRAY<queue_type>((int)allocation_size * 2, file, line );
#ifdef _DEBUG
			RakAssert( new_array );
#endif
			if (new_array==0)
				return;

			for ( unsigned int counter = 0; counter < allocation_size; ++counter )
				new_array[ counter ] = array[ ( head + counter ) % ( allocation_size ) ];

			head = 0;

			tail = allocation_size;

			allocation_size *= 2;

			// Delete the old array and move the pointer to the new array
			SLNet::OP_DELETE_ARRAY(array, file, line);

			array = new_array;
		}

	}

	template <class queue_type>
		Queue<queue_type>::Queue( const Queue& original_copy )
	{
		// Allocate memory for copy

		if ( original_copy.Size() == 0 )
		{
			allocation_size = 0;
		}

		else
		{
			array = SLNet::OP_NEW_ARRAY<queue_type >( original_copy.Size() + 1 , _FILE_AND_LINE_ );

			for ( unsigned int counter = 0; counter < original_copy.Size(); ++counter )
				array[ counter ] = original_copy.array[ ( original_copy.head + counter ) % ( original_copy.allocation_size ) ];

			head = 0;

			tail = original_copy.Size();

			allocation_size = original_copy.Size() + 1;
		}
	}

	template <class queue_type>
		bool Queue<queue_type>::operator= ( const Queue& original_copy )
	{
		if ( ( &original_copy ) == this )
			return false;

		Clear(_FILE_AND_LINE_);

		// Allocate memory for copy
		if ( original_copy.Size() == 0 )
		{
			allocation_size = 0;
		}

		else
		{
			array = SLNet::OP_NEW_ARRAY<queue_type >( original_copy.Size() + 1 , _FILE_AND_LINE_ );

			for ( unsigned int counter = 0; counter < original_copy.Size(); ++counter )
				array[ counter ] = original_copy.array[ ( original_copy.head + counter ) % ( original_copy.allocation_size ) ];

			head = 0;

			tail = original_copy.Size();

			allocation_size = original_copy.Size() + 1;
		}

		return true;
	}

	template <class queue_type>
	inline void Queue<queue_type>::Clear ( const char *file, unsigned int line )
	{
		if ( allocation_size == 0 )
			return ;

		if (allocation_size > 32)
		{
			SLNet::OP_DELETE_ARRAY(array, file, line);
			allocation_size = 0;
		}

		head = 0;
		tail = 0;
	}

	template <class queue_type>
	void Queue<queue_type>::Compress ( const char *file, unsigned int line )
	{
		queue_type* new_array;
		unsigned int newAllocationSize;
		if (allocation_size==0)
			return;

		newAllocationSize=1;
		while (newAllocationSize <= Size())
			newAllocationSize<<=1; // Must be a better way to do this but I'm too dumb to figure it out quickly :)

		new_array = SLNet::OP_NEW_ARRAY<queue_type >(newAllocationSize, file, line );

		for (unsigned int counter=0; counter < Size(); ++counter)
			new_array[counter] = array[(head + counter)%(allocation_size)];

		tail=Size();
		allocation_size=newAllocationSize;
		head=0;

		// Delete the old array and move the pointer to the new array
		SLNet::OP_DELETE_ARRAY(array, file, line);
		array=new_array;
	}

	template <class queue_type>
		bool Queue<queue_type>::Find ( const queue_type &q )
	{
		if ( allocation_size == 0 )
			return false;

		unsigned int counter = head;

		while ( counter != tail )
		{
			if ( array[ counter ] == q )
				return true;

			counter = ( counter + 1 ) % allocation_size;
		}

		return false;
	}

	template <class queue_type>
	void Queue<queue_type>::ClearAndForceAllocation( int size, const char *file, unsigned int line )
	{
		SLNet::OP_DELETE_ARRAY(array, file, line);
		if (size>0)
			array = SLNet::OP_NEW_ARRAY<queue_type>(size, file, line );
		else
			array=0;
		allocation_size = size;
		head = 0;
		tail = 0;
	}

	template <class queue_type>
		inline queue_type& Queue<queue_type>::operator[] ( unsigned int position ) const
	{
#ifdef _DEBUG
		RakAssert( position < Size() );
#endif
		//return array[(head + position) % allocation_size];

		if ( head + position >= allocation_size )
			return array[ head + position - allocation_size ];
		else
			return array[ head + position ];
	}

	template <class queue_type>
	void Queue<queue_type>::RemoveAtIndex( unsigned int position )
	{
#ifdef _DEBUG
		RakAssert( position < Size() );
		RakAssert( head != tail );
#endif

		if ( head == tail || position >= Size() )
			return ;

		unsigned int index;

		unsigned int next;

		//index  = (head + position) % allocation_size;
		if ( head + position >= allocation_size )
			index = head + position - allocation_size;
		else
			index = head + position;

		//next = (index + 1) % allocation_size;
		next = index + 1;

		if ( next == allocation_size )
			next = 0;

		while ( next != tail )
		{
			// Overwrite the previous element
			array[ index ] = array[ next ];
			index = next;
			//next = (next + 1) % allocation_size;

			if ( ++next == allocation_size )
				next = 0;
		}

		// Move the tail back
		if ( tail == 0 )
			tail = allocation_size - 1;
		else
			--tail;
	}
} // End namespace

#endif

