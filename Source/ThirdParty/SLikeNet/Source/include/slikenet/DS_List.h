/*
 *  Original work: Copyright (c) 2014, Oculus VR, Inc.
 *  All rights reserved.
 *
 *  This source code is licensed under the BSD-style license found in the
 *  RakNet License.txt file in the licenses directory of this source tree. An additional grant 
 *  of patent rights can be found in the RakNet Patents.txt file in the same directory.
 *
 *
 *  Modified work: Copyright (c) 2017-2018, SLikeSoft UG (haftungsbeschränkt)
 *
 *  This source code was modified by SLikeSoft. Modifications are licensed under the MIT-style
 *  license found in the license.txt file in the root directory of this source tree.
 */

/// \file DS_List.h
/// \internal
/// \brief Array based list.  
/// \details Usually the Queue class is used instead, since it has all the same functionality and is only worse at random access.
///


#ifndef __LIST_H
#define __LIST_H 

#include "assert.h"
#include <string.h> // memmove
#include "Export.h"
#include "memoryoverride.h"

/// Maximum unsigned long
static const unsigned int MAX_UNSIGNED_LONG = 4294967295U;

/// The namespace DataStructures was only added to avoid compiler errors for commonly named data structures
/// As these data structures are stand-alone, you can use them outside of RakNet for your own projects if you wish.
namespace DataStructures
{
	/// \brief Array based implementation of a list.
	/// \note ONLY USE THIS FOR SHALLOW COPIES.  I don't bother with operator= to improve performance.
	template <class list_type>
	class RAK_DLL_EXPORT List
	{	
	public:
		/// Default constructor
		List();

		// Destructor
		~List();
		
		/// \brief Copy constructor.
		/// \param[in]  original_copy The list to duplicate 
		List( const List& original_copy );
		
		/// \brief Assign one list to another.
		List& operator= ( const List& original_copy );
		
		/// \brief Access an element by its index in the array.
		/// \param[in]  position The index into the array. 
		/// \return The element at position \a position. 
		list_type& operator[] ( const unsigned int position ) const;

		/// \brief Access an element by its index in the array.
		/// \param[in]  position The index into the array. 
		/// \return The element at position \a position. 
		list_type& Get ( const unsigned int position ) const;

		/// \brief Push an element at the end of the stack.
		/// \param[in] input The new element. 
		void Push(const list_type &input, const char *file, unsigned int line );

		/// \brief Pop an element from the end of the stack.
		/// \pre Size()>0
		/// \return The element at the end. 
		list_type& Pop(void);
		
		/// \brief Insert an element at position \a position in the list.
		/// \param[in] input The new element. 
		/// \param[in] position The position of the new element. 		
		void Insert( const list_type &input, const unsigned int position, const char *file, unsigned int line );
		
		/// \brief Insert at the end of the list.
		/// \param[in] input The new element. 
		void Insert( const list_type &input, const char *file, unsigned int line );
		
		/// \brief Replace the value at \a position by \a input.  
		/// \details If the size of the list is less than @em position, it increase the capacity of
		/// the list and fill slot with @em filler.
		/// \param[in] input The element to replace at position @em position. 
		/// \param[in] filler The element use to fill new allocated capacity. 
		/// \param[in] position The position of input in the list. 		
		void Replace( const list_type &input, const list_type filler, const unsigned int position, const char *file, unsigned int line );
		
		/// \brief Replace the last element of the list by \a input.
		/// \param[in] input The element used to replace the last element. 
		void Replace( const list_type &input );
		
		/// \brief Delete the element at position \a position. 
		/// \param[in] position The index of the element to delete 
		void RemoveAtIndex( const unsigned int position );

		/// \brief Delete the element at position \a position.
		/// \note - swaps middle with end of list, only use if list order does not matter
		/// \param[in] position The index of the element to delete 
		void RemoveAtIndexFast( const unsigned int position );
		
		/// \brief Delete the element at the end of the list.
		void RemoveFromEnd(const unsigned num=1);
		
		/// \brief Returns the index of the specified item or MAX_UNSIGNED_LONG if not found.
		/// \param[in] input The element to check for 
		/// \return The index or position of @em input in the list. 
		/// \retval MAX_UNSIGNED_LONG The object is not in the list
		/// \retval [Integer] The index of the element in the list
		unsigned int GetIndexOf( const list_type &input ) const;
		
		/// \return The number of elements in the list
		unsigned int Size( void ) const;
		
		/// \brief Clear the list		
		void Clear( bool doNotDeallocateSmallBlocks, const char *file, unsigned int line );
		
		/// \brief Preallocate the list, so it needs fewer reallocations at runtime.
		void Preallocate( unsigned countNeeded, const char *file, unsigned int line );

		/// \brief Frees overallocated members, to use the minimum memory necessary.
		/// \attention 
		/// This is a slow operation		
		void Compress( const char *file, unsigned int line );
		
	private:
		/// An array of user values
		list_type* listArray;
		
		/// Number of elements in the list 		
		unsigned int list_size;
		
		/// Size of \a array 		
		unsigned int allocation_size;
	};
	template <class list_type>
		List<list_type>::List()
	{
		allocation_size = 0;
		listArray = 0;
		list_size = 0;
	}

	template <class list_type>
		List<list_type>::~List()
	{
		if (allocation_size>0)
			SLNet::OP_DELETE_ARRAY(listArray, _FILE_AND_LINE_);
	}


	template <class list_type>
		List<list_type>::List( const List& original_copy )
	{
		// Allocate memory for copy

		if ( original_copy.list_size == 0 )
		{
			list_size = 0;
			allocation_size = 0;
		}
		else
		{
			listArray = SLNet::OP_NEW_ARRAY<list_type >( original_copy.list_size , _FILE_AND_LINE_ );

			for ( unsigned int counter = 0; counter < original_copy.list_size; ++counter )
				listArray[ counter ] = original_copy.listArray[ counter ];

			// Don't call constructors, assignment operators, etc.
			//memcpy(listArray, original_copy.listArray, original_copy.list_size*sizeof(list_type));

			list_size = allocation_size = original_copy.list_size;
		}
	}

	template <class list_type>
		List<list_type>& List<list_type>::operator= ( const List& original_copy )
	{
		if ( ( &original_copy ) != this )
		{
			Clear( false, _FILE_AND_LINE_ );

			// Allocate memory for copy

			if ( original_copy.list_size == 0 )
			{
				list_size = 0;
				allocation_size = 0;
			}

			else
			{
				listArray = SLNet::OP_NEW_ARRAY<list_type >( original_copy.list_size , _FILE_AND_LINE_ );

				for ( unsigned int counter = 0; counter < original_copy.list_size; ++counter )
					listArray[ counter ] = original_copy.listArray[ counter ];
				// Don't call constructors, assignment operators, etc.
				//memcpy(listArray, original_copy.listArray, original_copy.list_size*sizeof(list_type));

				list_size = allocation_size = original_copy.list_size;
			}
		}

		return *this;
	}


		template <class list_type>
			inline list_type& List<list_type>::operator[] ( const unsigned int position ) const
		{
		#ifdef _DEBUG
			if (position>=list_size)
			{
				RakAssert ( position < list_size );
			}
		#endif
			return listArray[ position ];
		}

		// Just here for debugging
		template <class list_type>
		inline list_type& List<list_type>::Get ( const unsigned int position ) const
		{
			return listArray[ position ];
		}

		template <class list_type>
		void List<list_type>::Push(const list_type &input, const char *file, unsigned int line)
		{
			Insert(input, file, line);
		}

		template <class list_type>
		inline list_type& List<list_type>::Pop(void)
		{
#ifdef _DEBUG
			RakAssert(list_size>0);
#endif
			--list_size;
			return listArray[list_size];
		}

	template <class list_type>
	void List<list_type>::Insert( const list_type &input, const unsigned int position, const char *file, unsigned int line )
	{
		RakAssert( position <= list_size );

		// Reallocate list if necessary
		if ( list_size == allocation_size )
		{
			// allocate twice the currently allocated memory
			list_type * new_array;

			if ( allocation_size == 0 )
				allocation_size = 16;
			else
				allocation_size *= 2;

			new_array = SLNet::OP_NEW_ARRAY<list_type >( allocation_size , file, line );

			// copy old array over
			for ( unsigned int counter = 0; counter < list_size; ++counter )
				new_array[ counter ] = listArray[ counter ];

			// Don't call constructors, assignment operators, etc.
			//memcpy(new_array, listArray, list_size*sizeof(list_type));

			// set old array to point to the newly allocated and twice as large array
			SLNet::OP_DELETE_ARRAY(listArray, file, line);

			listArray = new_array;
		}

		// Move the elements in the list to make room
		for ( unsigned int counter = list_size; counter != position; counter-- )
			listArray[ counter ] = listArray[ counter - 1 ];

		// Don't call constructors, assignment operators, etc.
		//memmove(listArray+position+1, listArray+position, (list_size-position)*sizeof(list_type));

		// Insert the new item at the correct spot
		listArray[ position ] = input;

		++list_size;

	}


	template <class list_type>
	void List<list_type>::Insert( const list_type &input, const char *file, unsigned int line )
	{
		// Reallocate list if necessary

		if ( list_size == allocation_size )
		{
			// allocate twice the currently allocated memory
			list_type * new_array;

			if ( allocation_size == 0 )
				allocation_size = 16;
			else
				allocation_size *= 2;

			new_array = SLNet::OP_NEW_ARRAY<list_type >( allocation_size , file, line );

			if (listArray)
			{
				// copy old array over
					for ( unsigned int counter = 0; counter < list_size; ++counter )
						new_array[ counter ] = listArray[ counter ];

				// Don't call constructors, assignment operators, etc.
				//memcpy(new_array, listArray, list_size*sizeof(list_type));

				// set old array to point to the newly allocated and twice as large array
					SLNet::OP_DELETE_ARRAY(listArray, file, line);
			}
			
			listArray = new_array;
		}

		// Insert the new item at the correct spot
		listArray[ list_size ] = input;

		++list_size;
	}

	template <class list_type>
		inline void List<list_type>::Replace( const list_type &input, const list_type filler, const unsigned int position, const char *file, unsigned int line )
	{
		if ( ( list_size > 0 ) && ( position < list_size ) )
		{
			// Direct replacement
			listArray[ position ] = input;
		}
		else
		{
			if ( position >= allocation_size )
			{
				// Reallocate the list to size position and fill in blanks with filler
				list_type * new_array;
				allocation_size = position + 1;

				new_array = SLNet::OP_NEW_ARRAY<list_type >( allocation_size , file, line );

				// copy old array over

				for ( unsigned int counter = 0; counter < list_size; ++counter )
					new_array[ counter ] = listArray[ counter ];

				// Don't call constructors, assignment operators, etc.
				//memcpy(new_array, listArray, list_size*sizeof(list_type));

				// set old array to point to the newly allocated array
				SLNet::OP_DELETE_ARRAY(listArray, file, line);

				listArray = new_array;
			}

			// Fill in holes with filler
			while ( list_size < position )
				listArray[ list_size++ ] = filler;

			// Fill in the last element with the new item
			listArray[ list_size++ ] = input;

#ifdef _DEBUG

			RakAssert( list_size == position + 1 );

#endif

		}
	}

	template <class list_type>
		inline void List<list_type>::Replace( const list_type &input )
	{
		if ( list_size > 0 )
			listArray[ list_size - 1 ] = input;
	}

	template <class list_type>
		void List<list_type>::RemoveAtIndex( const unsigned int position )
	{
#ifdef _DEBUG
		if (position >= list_size)
		{
			RakAssert( position < list_size );
			return;
		}
#endif

		if ( position < list_size )
		{
			// Compress the array
			for ( unsigned int counter = position; counter < list_size - 1 ; ++counter )
			listArray[ counter ] = listArray[ counter + 1 ];
			// Don't call constructors, assignment operators, etc.
			// memmove(listArray+position, listArray+position+1, (list_size-1-position) * sizeof(list_type));

			RemoveFromEnd();
		}
	}

	template <class list_type>
		void List<list_type>::RemoveAtIndexFast( const unsigned int position )
		{
#ifdef _DEBUG
			if (position >= list_size)
			{
				RakAssert( position < list_size );
				return;
			}
#endif
			--list_size;
			listArray[position]=listArray[list_size];
		}

	template <class list_type>
		inline void List<list_type>::RemoveFromEnd( const unsigned num )
	{
		// Delete the last elements on the list.  No compression needed
#ifdef _DEBUG
		RakAssert(list_size>=num);
#endif
		list_size-=num;
	}

	template <class list_type>
		unsigned int List<list_type>::GetIndexOf( const list_type &input ) const
	{
		for ( unsigned int i = 0; i < list_size; ++i )
			if ( listArray[ i ] == input )
				return i;

		return MAX_UNSIGNED_LONG;
	}

	template <class list_type>
		inline unsigned int List<list_type>::Size( void ) const
	{
		return list_size;
	}

	template <class list_type>
	void List<list_type>::Clear( bool doNotDeallocateSmallBlocks, const char *file, unsigned int line )
	{
		if ( allocation_size == 0 )
			return;

		if (allocation_size>512 || doNotDeallocateSmallBlocks==false)
		{
			SLNet::OP_DELETE_ARRAY(listArray, file, line);
			allocation_size = 0;
			listArray = 0;
		}
		list_size = 0;
	}

	template <class list_type>
	void List<list_type>::Compress( const char *file, unsigned int line )
	{
		list_type * new_array;

		if ( allocation_size == 0 )
			return ;

		new_array = SLNet::OP_NEW_ARRAY<list_type >( allocation_size , file, line );

		// copy old array over
		for ( unsigned int counter = 0; counter < list_size; ++counter )
			new_array[ counter ] = listArray[ counter ];

		// Don't call constructors, assignment operators, etc.
		//memcpy(new_array, listArray, list_size*sizeof(list_type));

		// set old array to point to the newly allocated array
		SLNet::OP_DELETE_ARRAY(listArray, file, line);

		listArray = new_array;
	}

	template <class list_type>
	void List<list_type>::Preallocate( unsigned countNeeded, const char *file, unsigned int line )
	{
		unsigned amountToAllocate = allocation_size;
		if (allocation_size==0)
			amountToAllocate=16;
		while (amountToAllocate < countNeeded)
			amountToAllocate<<=1;

		if ( allocation_size < amountToAllocate)
		{
			// allocate twice the currently allocated memory
			list_type * new_array;

			allocation_size=amountToAllocate;

			new_array = SLNet::OP_NEW_ARRAY< list_type >( allocation_size , file, line );

			if (listArray)
			{
				// copy old array over
				for ( unsigned int counter = 0; counter < list_size; ++counter )
					new_array[ counter ] = listArray[ counter ];

				// Don't call constructors, assignment operators, etc.
				//memcpy(new_array, listArray, list_size*sizeof(list_type));

				// set old array to point to the newly allocated and twice as large array
				SLNet::OP_DELETE_ARRAY(listArray, file, line);
			}

			listArray = new_array;
		}
	}
	
} // End namespace

#endif
