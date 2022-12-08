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

/// \file DS_LinkedList.h
/// \internal
/// \brief Straightforward linked list data structure.
///


#ifndef __LINKED_LIST_H
#define __LINKED_LIST_H 

#include "Export.h"
#include "memoryoverride.h"

/// The namespace DataStructures was only added to avoid compiler errors for commonly named data structures
/// As these data structures are stand-alone, you can use them outside of RakNet for your own projects if you wish.
namespace DataStructures
{
	// Prototype to prevent error in CircularLinkedList class when a reference is made to a LinkedList class
	template <class LinkedListType>
	class RAK_DLL_EXPORT LinkedList;

	/**
	* \brief (Circular) Linked List ADT (Doubly Linked Pointer to Node Style) - 
	* 
	* \details
	* Initilize with the following command
	* LinkedList<TYPE>
	* OR
	* CircularLinkedList<Type>
	*
	* Has the following member functions
	* - size: returns number of elements in the linked list
	* - insert(item):  inserts @em item at the current position in 
	*   the LinkedList.
	* - add(item): inserts @em item after the current position in 
	*   the LinkedList.  Does not increment the position
	* - replace(item): replaces the element at the current position @em item.
	* - peek:  returns the element at the current position
	* - pop:  returns the element at the current position and deletes it
	* - del: deletes the current element. Does nothing for an empty list.
	* - clear:  empties the LinkedList and returns storage
	* - bool IsInitem): Does a linear search for @em item.  Does not set 
	*   the position to it, only returns true on item found, false otherwise
	* - bool find(item): Does a linear search for @em item and sets the current 
	*   position to point to it if and only if the item is found. Returns true 
	*   on item found, false otherwise
	* - sort: Sorts the elements of the list with a mergesort and sets the 
	*   current pointer to the first element
	* - concatenate(list L): This appends L to the current list
	* - ++(prefix): moves the pointer one element up in the list and returns the 
	*   appropriate copy of the element in the list
	* - --(prefix): moves the pointer one element back in the list and returns 
	*   the appropriate copy of the element in the list
	* - beginning - moves the pointer to the start of the list.  For circular 
	*   linked lists this is first 'position' created.  You should call this 
	*   after the sort function to read the first value.
	* - end - moves the pointer to the end of the list.  For circular linked 
	*   lists this is one less than the first 'position' created
	* The assignment and copy constructor operators are defined
	*
	* \note 
	* 1. LinkedList and CircularLinkedList are exactly the same except LinkedList 
	*    won't let you wrap around the root and lets you jump to two positions 
	*    relative to the root/
	* 2. Postfix ++ and -- can be used but simply call the prefix versions.
	*
	*
	* EXAMPLE:
	* @code
	* LinkedList<int> A;  // Creates a Linked List of integers called A
	* CircularLinkedList<int> B;  // Creates a Circular Linked List of 
	*          // integers called B
	*
	* A.Insert(20);  // Adds 20 to A.  A: 20 - current is 20
	* A.Insert(5);  // Adds 5 to A.  A: 5 20 - current is 5
	* A.Insert(1);  // Adds 1 to A.  A: 1 5 20 - current is 1
	*
	* A.IsIn1); // returns true
	* A.IsIn200); // returns false
	* A.Find(5);  // returns true and sets current to 5
	* A.Peek();  // returns 5
	* A.Find(1);  // returns true and sets current to 1
	*
	* (++A).Peek();  // Returns 5
	* A.Peek(); // Returns 5
	*
	* A.Replace(10);  // Replaces 5 with 10.
	* A.Peek();  // Returns 10
	*
	* A.Beginning();  // Current points to the beginning of the list at 1
	*
	* (++A).Peek();  // Returns 5
	* A.Peek();  // Returns 10
	*
	* A.Del();  // Deletes 10.  Current points to the next element, which is 20
	* A.Peek();  // Returns 20
	* 
	* A.Beginning();  // Current points to the beginning of the list at 1
	*
	* (++A).Peek();  // Returns 5
	* A.Peek();  // Returns 20
	*
	* A.Clear(_FILE_AND_LINE_);  // Deletes all nodes in A
	*
	* A.Insert(5);  // A: 5 - current is 5
	* A.Insert(6); // A: 6 5 - current is 6
	* A.Insert(7); // A: 7 6 5 - current is 7
	*
	* A.Clear(_FILE_AND_LINE_);
	* B.Clear(_FILE_AND_LINE_);
	*
	* B.Add(10);
	* B.Add(20);
	* B.Add(30);
	* B.Add(5);
	* B.Add(2);
	* B.Add(25);
	* // Sorts the numbers in the list and sets the current pointer to the 
	* // first element
	* B.sort();  
	*
	* // Postfix ++ just calls the prefix version and has no functional 
	* // difference.
	* B.Peek();  // Returns 2
	* B++;
	* B.Peek();  // Returns 5
	* B++;
	* B.Peek();  // Returns 10
	* B++;
	* B.Peek();  // Returns 20
	* B++;
	* B.Peek();  // Returns 25
	* B++;
	* B.Peek();  // Returns 30
	* @endcode
	*/
	template <class CircularLinkedListType>

	class CircularLinkedList
	{

	public:

		struct node
		{
			CircularLinkedListType item;

			node* previous;
			node* next;
		};

		CircularLinkedList();
		~CircularLinkedList();
		CircularLinkedList( const CircularLinkedList& original_copy );
		// CircularLinkedList(LinkedList<CircularLinkedListType> original_copy) {CircularLinkedList(original_copy);}  // Converts linked list to circular type
		bool operator= ( const CircularLinkedList& original_copy );
		CircularLinkedList& operator++();  // CircularLinkedList A; ++A;
		CircularLinkedList& operator++( int );  // Circular_Linked List A; A++;
		CircularLinkedList& operator--();  // CircularLinkedList A; --A;
		CircularLinkedList& operator--( int );  // Circular_Linked List A; A--;
		bool IsIn( const CircularLinkedListType& input );
		bool Find( const CircularLinkedListType& input );
		void Insert( const CircularLinkedListType& input );

		CircularLinkedListType& Add ( const CircularLinkedListType& input )

			; // Adds after the current position
		void Replace( const CircularLinkedListType& input );

		void Del( void );

		unsigned int Size( void );

		CircularLinkedListType& Peek( void );

		CircularLinkedListType Pop( void );

		void Clear( void );

		void Sort( void );

		void Beginning( void );

		void End( void );

		void Concatenate( const CircularLinkedList& L );

	protected:
		unsigned int list_size;

		node *root;

		node *position;

		node* FindPointer( const CircularLinkedListType& input );

	private:
		CircularLinkedList Merge( CircularLinkedList L1, CircularLinkedList L2 );

		CircularLinkedList Mergesort( const CircularLinkedList& L );
	};

	template <class LinkedListType>

	class LinkedList : public CircularLinkedList<LinkedListType>
	{

	public:
		LinkedList()
		{}

		LinkedList( const LinkedList& original_copy );
		~LinkedList();
		bool operator= ( const LinkedList<LinkedListType>& original_copy );
		LinkedList& operator++();  // LinkedList A; ++A;
		LinkedList& operator++( int );  // Linked List A; A++;
		LinkedList& operator--();  // LinkedList A; --A;
		LinkedList& operator--( int );  // Linked List A; A--;

	private:
		LinkedList Merge( LinkedList L1, LinkedList L2 );
		LinkedList Mergesort( const LinkedList& L );

	};


	template <class CircularLinkedListType>
		inline void CircularLinkedList<CircularLinkedListType>::Beginning( void )
	{
		if ( this->root )
			this->position = this->root;
	}

	template <class CircularLinkedListType>
		inline void CircularLinkedList<CircularLinkedListType>::End( void )
	{
		if ( this->root )
			this->position = this->root->previous;
	}

	template <class LinkedListType>
		bool LinkedList<LinkedListType>::operator= ( const LinkedList<LinkedListType>& original_copy )
	{
		typename LinkedList::node * original_copy_pointer, *last, *save_position;

		if ( ( &original_copy ) != this )
		{

			this->Clear();


			if ( original_copy.list_size == 0 )
			{
				this->root = 0;
				this->position = 0;
				this->list_size = 0;
			}

			else
				if ( original_copy.list_size == 1 )
				{
					this->root = SLNet::OP_NEW<typename LinkedList::node>( _FILE_AND_LINE_ );
					// root->item = SLNet::OP_NEW<LinkedListType>( _FILE_AND_LINE_ );
					this->root->next = this->root;
					this->root->previous = this->root;
					this->list_size = 1;
					this->position = this->root;
					// *(root->item)=*((original_copy.root)->item);
					this->root->item = original_copy.root->item;
				}

				else
				{
					// Setup the first part of the root node
					original_copy_pointer = original_copy.root;
					this->root = SLNet::OP_NEW<typename LinkedList::node>( _FILE_AND_LINE_ );
					// root->item = SLNet::OP_NEW<LinkedListType>( _FILE_AND_LINE_ );
					this->position = this->root;
					// *(root->item)=*((original_copy.root)->item);
					this->root->item = original_copy.root->item;

					if ( original_copy_pointer == original_copy.position )
						save_position = this->position;

					do
					{


						// Save the current element
						last = this->position;

						// Point to the next node in the source list
						original_copy_pointer = original_copy_pointer->next;

						// Create a new node and point position to it
						this->position = SLNet::OP_NEW<typename LinkedList::node>( _FILE_AND_LINE_ );
						// position->item = SLNet::OP_NEW<LinkedListType>( _FILE_AND_LINE_ );

						// Copy the item to the new node
						// *(position->item)=*(original_copy_pointer->item);
						this->position->item = original_copy_pointer->item;

						if ( original_copy_pointer == original_copy.position )
							save_position = this->position;


						// Set the previous pointer for the new node
						( this->position->previous ) = last;

						// Set the next pointer for the old node to the new node
						( last->next ) = this->position;

					}

					while ( ( original_copy_pointer->next ) != ( original_copy.root ) );

					// Complete the circle.  Set the next pointer of the newest node to the root and the previous pointer of the root to the newest node
					this->position->next = this->root;

					this->root->previous = this->position;

					this->list_size = original_copy.list_size;

					this->position = save_position;
				}
		}

		return true;
	}


	template <class CircularLinkedListType>
		CircularLinkedList<CircularLinkedListType>::CircularLinkedList()
	{
		this->root = 0;
		this->position = 0;
		this->list_size = 0;
	}

	template <class CircularLinkedListType>
		CircularLinkedList<CircularLinkedListType>::~CircularLinkedList()
	{
		this->Clear();
	}

	template <class LinkedListType>
		LinkedList<LinkedListType>::~LinkedList()
	{
		this->Clear();
	}

	template <class LinkedListType>
		LinkedList<LinkedListType>::LinkedList( const LinkedList& original_copy )
	{
		typename LinkedList::node * original_copy_pointer, *last, *save_position;

		if ( original_copy.list_size == 0 )
		{
			this->root = 0;
			this->position = 0;
			this->list_size = 0;
			return ;
		}

		else
			if ( original_copy.list_size == 1 )
			{
				this->root = SLNet::OP_NEW<typename LinkedList::node>( _FILE_AND_LINE_ );
				// root->item = SLNet::OP_NEW<CircularLinkedListType>( _FILE_AND_LINE_ );
				this->root->next = this->root;
				this->root->previous = this->root;
				this->list_size = 1;
				this->position = this->root;
				// *(root->item) = *((original_copy.root)->item);
				this->root->item = original_copy.root->item;
			}

			else
			{
				// Setup the first part of the root node
				original_copy_pointer = original_copy.root;
				this->root = SLNet::OP_NEW<typename LinkedList::node>( _FILE_AND_LINE_ );
				// root->item = SLNet::OP_NEW<CircularLinkedListType>( _FILE_AND_LINE_ );
				this->position = this->root;
				// *(root->item)=*((original_copy.root)->item);
				this->root->item = original_copy.root->item;

				if ( original_copy_pointer == original_copy.position )
					save_position = this->position;

				do
				{
					// Save the current element
					last = this->position;

					// Point to the next node in the source list
					original_copy_pointer = original_copy_pointer->next;

					// Create a new node and point position to it
					this->position = SLNet::OP_NEW<typename LinkedList::node>( _FILE_AND_LINE_ );
					// position->item = SLNet::OP_NEW<CircularLinkedListType>( _FILE_AND_LINE_ );

					// Copy the item to the new node
					// *(position->item)=*(original_copy_pointer->item);
					this->position->item = original_copy_pointer->item;

					if ( original_copy_pointer == original_copy.position )
						save_position = this->position;

					// Set the previous pointer for the new node
					( this->position->previous ) = last;

					// Set the next pointer for the old node to the new node
					( last->next ) = this->position;

				}

				while ( ( original_copy_pointer->next ) != ( original_copy.root ) );

				// Complete the circle.  Set the next pointer of the newest node to the root and the previous pointer of the root to the newest node
				this->position->next = this->root;

				this->root->previous = this->position;

				this->list_size = original_copy.list_size;

				this->position = save_position;
			}
	}

	template <class CircularLinkedListType>
		CircularLinkedList<CircularLinkedListType>::CircularLinkedList( const CircularLinkedList& original_copy )
	{
		node * original_copy_pointer;
		node *last;
		node *save_position = nullptr;

		if ( original_copy.list_size == 0 )
		{
			this->root = 0;
			this->position = 0;
			this->list_size = 0;
			return ;
		}

		else
			if ( original_copy.list_size == 1 )
			{
				this->root = SLNet::OP_NEW<typename CircularLinkedList::node>( _FILE_AND_LINE_ );
				// root->item = SLNet::OP_NEW<CircularLinkedListType>( _FILE_AND_LINE_ );
				this->root->next = this->root;
				this->root->previous = this->root;
				this->list_size = 1;
				this->position = this->root;
				// *(root->item) = *((original_copy.root)->item);
				this->root->item = original_copy.root->item;
			}

			else
			{
				// Setup the first part of the root node
				original_copy_pointer = original_copy.root;
				this->root = SLNet::OP_NEW<typename CircularLinkedList::node>( _FILE_AND_LINE_ );
				// root->item = SLNet::OP_NEW<CircularLinkedListType>( _FILE_AND_LINE_ );
				this->position = this->root;
				// *(root->item)=*((original_copy.root)->item);
				this->root->item = original_copy.root->item;

				if ( original_copy_pointer == original_copy.position )
					save_position = this->position;

				do
				{


					// Save the current element
					last = this->position;

					// Point to the next node in the source list
					original_copy_pointer = original_copy_pointer->next;

					// Create a new node and point position to it
					this->position = SLNet::OP_NEW<typename CircularLinkedList::node>( _FILE_AND_LINE_ );
					// position->item = SLNet::OP_NEW<CircularLinkedListType>( _FILE_AND_LINE_ );

					// Copy the item to the new node
					// *(position->item)=*(original_copy_pointer->item);
					this->position->item = original_copy_pointer->item;

					if ( original_copy_pointer == original_copy.position )
						save_position = position;

					// Set the previous pointer for the new node
					( this->position->previous ) = last;

					// Set the next pointer for the old node to the new node
					( last->next ) = this->position;

				}

				while ( ( original_copy_pointer->next ) != ( original_copy.root ) );

				// Complete the circle.  Set the next pointer of the newest node to the root and the previous pointer of the root to the newest node
				this->position->next = this->root;

				this->root->previous = position;

				this->list_size = original_copy.list_size;

				this->position = save_position;
			}
	}

	template <class CircularLinkedListType>
		bool CircularLinkedList<CircularLinkedListType>::operator= ( const CircularLinkedList& original_copy )
	{
		node * original_copy_pointer;
		node *last;
		node *save_position = nullptr;

		if ( ( &original_copy ) != this )
		{

			this->Clear();


			if ( original_copy.list_size == 0 )
			{
				this->root = 0;
				this->position = 0;
				this->list_size = 0;
			}

			else
				if ( original_copy.list_size == 1 )
				{
					this->root = SLNet::OP_NEW<typename CircularLinkedList::node>( _FILE_AND_LINE_ );
					// root->item = SLNet::OP_NEW<CircularLinkedListType>( _FILE_AND_LINE_ );
					this->root->next = this->root;
					this->root->previous = this->root;
					this->list_size = 1;
					this->position = this->root;
					// *(root->item)=*((original_copy.root)->item);
					this->root->item = original_copy.root->item;
				}

				else
				{
					// Setup the first part of the root node
					original_copy_pointer = original_copy.root;
					this->root = SLNet::OP_NEW<typename CircularLinkedList::node>( _FILE_AND_LINE_ );
					// root->item = SLNet::OP_NEW<CircularLinkedListType>( _FILE_AND_LINE_ );
					this->position = this->root;
					// *(root->item)=*((original_copy.root)->item);
					this->root->item = original_copy.root->item;

					if ( original_copy_pointer == original_copy.position )
						save_position = this->position;

					do
					{
						// Save the current element
						last = this->position;

						// Point to the next node in the source list
						original_copy_pointer = original_copy_pointer->next;

						// Create a new node and point position to it
						this->position = SLNet::OP_NEW<typename CircularLinkedList::node>( _FILE_AND_LINE_ );
						// position->item = SLNet::OP_NEW<CircularLinkedListType>( _FILE_AND_LINE_ );

						// Copy the item to the new node
						// *(position->item)=*(original_copy_pointer->item);
						this->position->item = original_copy_pointer->item;

						if ( original_copy_pointer == original_copy.position )
							save_position = this->position;

						// Set the previous pointer for the new node
						( this->position->previous ) = last;

						// Set the next pointer for the old node to the new node
						( last->next ) = this->position;

					}

					while ( ( original_copy_pointer->next ) != ( original_copy.root ) );

					// Complete the circle.  Set the next pointer of the newest node to the root and the previous pointer of the root to the newest node
					this->position->next = this->root;

					this->root->previous = this->position;

					this->list_size = original_copy.list_size;

					this->position = save_position;
				}
		}

		return true;
	}

	template <class CircularLinkedListType>
		void CircularLinkedList<CircularLinkedListType>::Insert( const CircularLinkedListType& input )
	{
		node * new_node;

		if ( list_size == 0 )
		{
			this->root = SLNet::OP_NEW<typename CircularLinkedList::node>( _FILE_AND_LINE_ );
			// root->item = SLNet::OP_NEW<CircularLinkedListType>( _FILE_AND_LINE_ );
			//*(root->item)=input;
			this->root->item = input;
			this->root->next = this->root;
			this->root->previous = this->root;
			this->list_size = 1;
			this->position = this->root;
		}

		else
			if ( list_size == 1 )
			{
				this->position = SLNet::OP_NEW<typename CircularLinkedList::node>( _FILE_AND_LINE_ );
				// position->item = SLNet::OP_NEW<CircularLinkedListType>( _FILE_AND_LINE_ );
				this->root->next = this->position;
				this->root->previous = this->position;
				this->position->previous = this->root;
				this->position->next = this->root;
				// *(position->item)=input;
				this->position->item = input;
				this->root = this->position; // Since we're inserting into a 1 element list the old root is now the second item
				this->list_size = 2;
			}

			else
			{
				/*

				B
				|
				A --- C

				position->previous=A
				new_node=B
				position=C

				Note that the order of the following statements is important  */

				new_node = SLNet::OP_NEW<typename CircularLinkedList::node>( _FILE_AND_LINE_ );
				// new_node->item = SLNet::OP_NEW<CircularLinkedListType>( _FILE_AND_LINE_ );

				// *(new_node->item)=input;
				new_node->item = input;

				// Point next of A to B
				( this->position->previous ) ->next = new_node;

				// Point last of B to A
				new_node->previous = this->position->previous;

				// Point last of C to B
				this->position->previous = new_node;

				// Point next of B to C
				new_node->next = this->position;

				// Since the root pointer is bound to a node rather than an index this moves it back if you insert an element at the root

				if ( this->position == this->root )
				{
					this->root = new_node;
					this->position = this->root;
				}

				// Increase the recorded size of the list by one
				this->list_size++;
			}
	}

	template <class CircularLinkedListType>
		CircularLinkedListType& CircularLinkedList<CircularLinkedListType>::Add ( const CircularLinkedListType& input )
	{
		node * new_node;

		if ( this->list_size == 0 )
		{
			this->root = SLNet::OP_NEW<typename CircularLinkedList::node>( _FILE_AND_LINE_ );
			// root->item = SLNet::OP_NEW<CircularLinkedListType>( _FILE_AND_LINE_ );
			// *(root->item)=input;
			this->root->item = input;
			this->root->next = this->root;
			this->root->previous = this->root;
			this->list_size = 1;
			this->position = this->root;
			// return *(position->item);
			return this->position->item;
		}

		else
			if ( list_size == 1 )
			{
				this->position = SLNet::OP_NEW<typename CircularLinkedList::node>( _FILE_AND_LINE_ );
				// position->item = SLNet::OP_NEW<CircularLinkedListType>( _FILE_AND_LINE_ );
				this->root->next = this->position;
				this->root->previous = this->position;
				this->position->previous = this->root;
				this->position->next = this->root;
				// *(position->item)=input;
				this->position->item = input;
				this->list_size = 2;
				this->position = this->root; // Don't move the position from the root
				// return *(position->item);
				return this->position->item;
			}

			else
			{
				/*

				   B
			       |
				A --- C

				new_node=B
				position=A
				position->next=C

				Note that the order of the following statements is important  */

				new_node = SLNet::OP_NEW<typename CircularLinkedList::node>( _FILE_AND_LINE_ );
				// new_node->item = SLNet::OP_NEW<CircularLinkedListType>( _FILE_AND_LINE_ );

				// *(new_node->item)=input;
				new_node->item = input;

				// Point last of B to A
				new_node->previous = this->position;

				// Point next of B to C
				new_node->next = ( this->position->next );

				// Point last of C to B
				( this->position->next ) ->previous = new_node;

				// Point next of A to B
				( this->position->next ) = new_node;

				// Increase the recorded size of the list by one
				this->list_size++;

				// return *(new_node->item);
				return new_node->item;
			}
	}

	template <class CircularLinkedListType>
		inline void CircularLinkedList<CircularLinkedListType>::Replace( const CircularLinkedListType& input )
	{
		if ( this->list_size > 0 )
			// *(position->item)=input;
			this->position->item = input;
	}

	template <class CircularLinkedListType>
		void CircularLinkedList<CircularLinkedListType>::Del()
	{
		node * new_position;

		if ( this->list_size == 0 )
			return ;

		else
			if ( this->list_size == 1 )
			{
				// SLNet::OP_DELETE(root->item, _FILE_AND_LINE_);
				SLNet::OP_DELETE(this->root, _FILE_AND_LINE_);
				this->root = this->position = 0;
				this->list_size = 0;
			}

			else
			{
				( this->position->previous ) ->next = this->position->next;
				( this->position->next ) ->previous = this->position->previous;
				new_position = this->position->next;

				if ( this->position == this->root )
					this->root = new_position;

				// SLNet::OP_DELETE(position->item, _FILE_AND_LINE_);
				SLNet::OP_DELETE(this->position, _FILE_AND_LINE_);

				this->position = new_position;

				this->list_size--;
			}
	}

	template <class CircularLinkedListType>
		bool CircularLinkedList<CircularLinkedListType>::IsIn(const CircularLinkedListType& input )
	{
		node * return_value, *old_position;

		old_position = this->position;

		return_value = FindPointer( input );
		this->position = old_position;

		if ( return_value != 0 )
			return true;
		else
			return false; // Can't find the item don't do anything
	}

	template <class CircularLinkedListType>
		bool CircularLinkedList<CircularLinkedListType>::Find( const CircularLinkedListType& input )
	{
		node * return_value;

		return_value = FindPointer( input );

		if ( return_value != 0 )
		{
			this->position = return_value;
			return true;
		}

		else
			return false; // Can't find the item don't do anything
	}

	template <class CircularLinkedListType>
		typename CircularLinkedList<CircularLinkedListType>::node* CircularLinkedList<CircularLinkedListType>::FindPointer( const CircularLinkedListType& input )
	{
		node * current;

		if ( this->list_size == 0 )
			return 0;

		current = this->root;

		// Search for the item starting from the root node and incrementing the pointer after every check
		// If you wind up pointing at the root again you looped around the list so didn't find the item, in which case return 0
		do
		{
			// if (*(current->item) == input) return current;

			if ( current->item == input )
				return current;

			current = current->next;
		}

		while ( current != this->root );

		return 0;

	}

	template <class CircularLinkedListType>
		inline unsigned int CircularLinkedList<CircularLinkedListType>::Size( void )
	{
		return this->list_size;
	}

	template <class CircularLinkedListType>
		inline CircularLinkedListType& CircularLinkedList<CircularLinkedListType>::Peek( void )
	{
		// return *(position->item);
		return this->position->item;
	}

	template <class CircularLinkedListType>
		CircularLinkedListType CircularLinkedList<CircularLinkedListType>::Pop( void )
	{
		CircularLinkedListType element;
		element = Peek();
		Del();
		return CircularLinkedListType( element ); // return temporary
	}

	// Prefix
	template <class CircularLinkedListType>
		CircularLinkedList<CircularLinkedListType>& CircularLinkedList<CircularLinkedListType>::operator++()
	{
		if ( this->list_size != 0 )
			position = position->next;

		return *this;
	}

	/*
	// Postfix
	template <class CircularLinkedListType>
	CircularLinkedList<CircularLinkedListType>& CircularLinkedList<CircularLinkedListType>::operator++(int)
	{
	CircularLinkedList<CircularLinkedListType> before;
	before=*this;
	operator++();
	return before;
	}
	*/

	template <class CircularLinkedListType>
		CircularLinkedList<CircularLinkedListType>& CircularLinkedList<CircularLinkedListType>::operator++( int )
	{
		return this->operator++();
	}

	// Prefix
	template <class CircularLinkedListType>
		CircularLinkedList<CircularLinkedListType>& CircularLinkedList<CircularLinkedListType>::operator--()
	{
		if ( this->list_size != 0 )
			this->position = this->position->previous;

		return *this;
	}

	/*
	// Postfix
	template <class CircularLinkedListType>
	CircularLinkedList<CircularLinkedListType>& CircularLinkedList<CircularLinkedListType>::operator--(int)
	{
	CircularLinkedList<CircularLinkedListType> before;
	before=*this;
	operator--();
	return before;
	}
	*/

	template <class CircularLinkedListType>
		CircularLinkedList<CircularLinkedListType>& CircularLinkedList<CircularLinkedListType>::operator--( int )
	{
		return this->operator--();
	}

	template <class CircularLinkedListType>
		void CircularLinkedList<CircularLinkedListType>::Clear( void )
	{
		if ( this->list_size == 0 )
			return ;
		else
			if ( this->list_size == 1 )  // {SLNet::OP_DELETE(root->item); SLNet::OP_DELETE(root, _FILE_AND_LINE_);}
			{
				SLNet::OP_DELETE(this->root, _FILE_AND_LINE_);
			}

			else
			{
				node* current;
				node* temp;

				current = this->root;

				do
				{
					temp = current;
					current = current->next;
					// SLNet::OP_DELETE(temp->item, _FILE_AND_LINE_);
					SLNet::OP_DELETE(temp, _FILE_AND_LINE_);
				}

				while ( current != this->root );
			}

			this->list_size = 0;
			this->root = 0;
			this->position = 0;
	}

	template <class CircularLinkedListType>
		inline void CircularLinkedList<CircularLinkedListType>::Concatenate( const CircularLinkedList<CircularLinkedListType>& L )
	{
		unsigned int counter;
		node* ptr;

		if ( L.list_size == 0 )
			return ;

		if ( this->list_size == 0 )
			* this = L;

		ptr = L.root;

		this->position = this->root->previous;

		// Cycle through each element in L and add it to the current list
		for ( counter = 0; counter < L.list_size; counter++ )
		{
			// Add item after the current item pointed to
			// add(*(ptr->item));

			Add ( ptr->item );

			// Update pointers.  Moving ptr keeps the current pointer at the end of the list since the add function does not move the pointer
			ptr = ptr->next;

			this->position = this->position->next;
		}
	}

	template <class CircularLinkedListType>
		inline void CircularLinkedList<CircularLinkedListType>::Sort( void )
	{
		if ( this->list_size <= 1 )
			return ;

		// Call equal operator to assign result of mergesort to current object
		*this = Mergesort( *this );

		this->position = this->root;
	}

	template <class CircularLinkedListType>
		CircularLinkedList<CircularLinkedListType> CircularLinkedList<CircularLinkedListType>::Mergesort( const CircularLinkedList& L )
	{
		unsigned int counter;
		node* location;
		CircularLinkedList<CircularLinkedListType> L1;
		CircularLinkedList<CircularLinkedListType> L2;

		location = L.root;

		// Split the list into two equal size sublists, L1 and L2

		for ( counter = 0; counter < L.list_size / 2; counter++ )
		{
			// L1.add (*(location->item));
			L1.Add ( location->item );
			location = location->next;
		}

		for ( ;counter < L.list_size; counter++ )
		{
			// L2.Add(*(location->item));
			L2.Add ( location->item );
			location = location->next;
		}

		// Recursively sort the sublists
		if ( L1.list_size > 1 )
			L1 = Mergesort( L1 );

		if ( L2.list_size > 1 )
			L2 = Mergesort( L2 );

		// Merge the two sublists
		return Merge( L1, L2 );
	}

	template <class CircularLinkedListType>
		CircularLinkedList<CircularLinkedListType> CircularLinkedList<CircularLinkedListType>::Merge( CircularLinkedList L1, CircularLinkedList L2 )
	{
		CircularLinkedList<CircularLinkedListType> X;
		CircularLinkedListType element;
		L1.position = L1.root;
		L2.position = L2.root;

		// While neither list is empty

		while ( ( L1.list_size != 0 ) && ( L2.list_size != 0 ) )
		{
			// Compare the first items of L1 and L2
			// Remove the smaller of the two items from the list

			if ( ( ( L1.root ) ->item ) < ( ( L2.root ) ->item ) )
				// if ((*((L1.root)->item)) < (*((L2.root)->item)))
			{
				// element = *((L1.root)->item);
				element = ( L1.root ) ->item;
				L1.Del();
			}
			else
			{
				// element = *((L2.root)->item);
				element = ( L2.root ) ->item;
				L2.Del();
			}

			// Add this item to the end of X
			X.Add( element );

			X++;
		}

		// Add the remaining list to X
		if ( L1.list_size != 0 )
			X.Concatenate( L1 );
		else
			X.Concatenate( L2 );

		return X;
	}

	template <class LinkedListType>
		LinkedList<LinkedListType> LinkedList<LinkedListType>::Mergesort( const LinkedList& L )
	{
		unsigned int counter;
		typename LinkedList::node* location;
		LinkedList<LinkedListType> L1;
		LinkedList<LinkedListType> L2;

		location = L.root;

		// Split the list into two equal size sublists, L1 and L2

		for ( counter = 0; counter < L.LinkedList_size / 2; counter++ )
		{
			// L1.add (*(location->item));
			L1.Add ( location->item );
			location = location->next;
		}

		for ( ;counter < L.LinkedList_size; counter++ )
		{
			// L2.Add(*(location->item));
			L2.Add ( location->item );
			location = location->next;
		}

		// Recursively sort the sublists
		if ( L1.list_size > 1 )
			L1 = Mergesort( L1 );

		if ( L2.list_size > 1 )
			L2 = Mergesort( L2 );

		// Merge the two sublists
		return Merge( L1, L2 );
	}

	template <class LinkedListType>
		LinkedList<LinkedListType> LinkedList<LinkedListType>::Merge( LinkedList L1, LinkedList L2 )
	{
		LinkedList<LinkedListType> X;
		LinkedListType element;
		L1.position = L1.root;
		L2.position = L2.root;

		// While neither list is empty

		while ( ( L1.LinkedList_size != 0 ) && ( L2.LinkedList_size != 0 ) )
		{
			// Compare the first items of L1 and L2
			// Remove the smaller of the two items from the list

			if ( ( ( L1.root ) ->item ) < ( ( L2.root ) ->item ) )
				// if ((*((L1.root)->item)) < (*((L2.root)->item)))
			{
				element = ( L1.root ) ->item;
				// element = *((L1.root)->item);
				L1.Del();
			}
			else
			{
				element = ( L2.root ) ->item;
				// element = *((L2.root)->item);
				L2.Del();
			}

			// Add this item to the end of X
			X.Add( element );
		}

		// Add the remaining list to X
		if ( L1.LinkedList_size != 0 )
			X.concatenate( L1 );
		else
			X.concatenate( L2 );

		return X;
	}


	// Prefix
	template <class LinkedListType>
		LinkedList<LinkedListType>& LinkedList<LinkedListType>::operator++()
	{
		if ( ( this->list_size != 0 ) && ( this->position->next != this->root ) )
			this->position = this->position->next;

		return *this;
	}

	/*
	// Postfix
	template <class LinkedListType>
	LinkedList<LinkedListType>& LinkedList<LinkedListType>::operator++(int)
	{
	LinkedList<LinkedListType> before;
	before=*this;
	operator++();
	return before;
	}
	*/ 
	// Postfix
	template <class LinkedListType>
		LinkedList<LinkedListType>& LinkedList<LinkedListType>::operator++( int )
	{
		return this->operator++();
	}

	// Prefix
	template <class LinkedListType>
		LinkedList<LinkedListType>& LinkedList<LinkedListType>::operator--()
	{
		if ( ( this->list_size != 0 ) && ( this->position != this->root ) )
			this->position = this->position->previous;

		return *this;
	}

	/*
	// Postfix
	template <class LinkedListType>
	LinkedList<LinkedListType>& LinkedList<LinkedListType>::operator--(int)
	{
	LinkedList<LinkedListType> before;
	before=*this;
	operator--();
	return before;
	}
	*/

	// Postfix
	template <class LinkedListType>
		LinkedList<LinkedListType>& LinkedList<LinkedListType>::operator--( int )
	{
		return this->operator--();
	}

} // End namespace

#endif
