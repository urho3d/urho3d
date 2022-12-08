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

/// \file DS_BinarySearchTree.h
/// \internal
/// \brief A binary search tree, and an AVL balanced BST derivation.
///


#ifndef __BINARY_SEARCH_TREE_H
#define __BINARY_SEARCH_TREE_H

#include "DS_QueueLinkedList.h"
#include "memoryoverride.h"
#include "Export.h"


/// The namespace DataStructures was only added to avoid compiler errors for commonly named data structures
/// As these data structures are stand-alone, you can use them outside of RakNet for your own projects if you wish.
namespace DataStructures
{
	/**
	 * \brief A binary search tree and an AVL balanced binary search tree.
	 * \details
	 * Initilize with the following structure
	 *
	 * BinarySearchTree<TYPE>
	 *
	 * OR
	 *
	 * AVLBalancedBinarySearchTree<TYPE>
	 *
	 * Use the AVL balanced tree if you want the tree to be balanced after every deletion and addition.  This avoids the potential
	 * worst case scenario where ordered input to a binary search tree gives linear search time results.  It's not needed
	 * if input will be evenly distributed, in which case the search time is O (log n).  The search time for the AVL
	 * balanced binary tree is O (log n) irregardless of input.
	 *
	 * Has the following member functions
	 * unsigned int Height(<index>) - Returns the height of the tree at the optional specified starting index.  Default is the root
	 * add(element) - adds an element to the BinarySearchTree
	 * bool del(element) - deletes the node containing element if the element is in the tree as defined by a comparison with the == operator.  Returns true on success, false if the element is not found
	 * bool IsInelement) - returns true if element is in the tree as defined by a comparison with the == operator.  Otherwise returns false
	 * DisplayInorder(array) - Fills an array with an inorder search of the elements in the tree.  USER IS REPONSIBLE FOR ALLOCATING THE ARRAY!.
	 * DisplayPreorder(array) - Fills an array with an preorder search of the elements in the tree.  USER IS REPONSIBLE FOR ALLOCATING THE ARRAY!.
	 * DisplayPostorder(array) - Fills an array with an postorder search of the elements in the tree. USER IS REPONSIBLE FOR ALLOCATING THE ARRAY!.
	 * DisplayBreadthFirstSearch(array) - Fills an array with a breadth first search of the elements in the tree.  USER IS REPONSIBLE FOR ALLOCATING THE ARRAY!.
	 * clear - Destroys the tree.  Same as calling the destructor
	 * unsigned int Height() - Returns the height of the tree
	 * unsigned int size() - returns the size of the BinarySearchTree
	 * GetPointerToNode(element) - returns a pointer to the comparision element in the tree, allowing for direct modification when necessary with complex data types.
	 * Be warned, it is possible to corrupt the tree if the element used for comparisons is modified.  Returns NULL if the item is not found
	 *
	 *
	 * EXAMPLE
	 * @code
	 * BinarySearchTree<int> A;
	 * A.Add(10);
	 * A.Add(15);
	 * A.Add(5);
	 * int* array = SLNet::OP_NEW<int >(A.Size(), _FILE_AND_LINE_ );
	 * A.DisplayInorder(array);
	 * array[0]; // returns 5
	 * array[1]; // returns 10
	 * array[2]; // returns 15
	 * @endcode 
	 * compress - reallocates memory to fit the number of elements.  Best used when the number of elements decreases
	 *
	 * clear - empties the BinarySearchTree and returns storage
	 * The assignment and copy constructors are defined
	 *
	 * \note The template type must have the copy constructor and
	 * assignment operator defined and must work with >, <, and == All
	 * elements in the tree MUST be distinct The assignment operator is
	 * defined between BinarySearchTree and AVLBalancedBinarySearchTree
	 * as long as they are of the same template type. However, passing a
	 * BinarySearchTree to an AVLBalancedBinarySearchTree will lose its
	 * structure unless it happened to be AVL balanced to begin with
	 * Requires queue_linked_list.cpp for the breadth first search used
	 * in the copy constructor, overloaded assignment operator, and
	 * display_breadth_first_search.
	 *
	 *
	 */
	template <class BinarySearchTreeType>
	class RAK_DLL_EXPORT BinarySearchTree
	{
	
	public:

		struct node
		{
			BinarySearchTreeType* item;
			node* left;
			node* right;
		};
		
		BinarySearchTree();
		virtual ~BinarySearchTree();
		BinarySearchTree( const BinarySearchTree& original_type );
		BinarySearchTree& operator= ( const BinarySearchTree& original_copy );
		unsigned int Size( void );
		void Clear( const char *file, unsigned int line );
		unsigned int Height( node* starting_node = 0 );
		node* Add ( const BinarySearchTreeType& input, const char *file, unsigned int line );
		node* Del( const BinarySearchTreeType& input, const char *file, unsigned int line );
		bool IsIn( const BinarySearchTreeType& input );
		void DisplayInorder( BinarySearchTreeType* return_array );
		void DisplayPreorder( BinarySearchTreeType* return_array );
		void DisplayPostorder( BinarySearchTreeType* return_array );
		void DisplayBreadthFirstSearch( BinarySearchTreeType* return_array );
		BinarySearchTreeType*& GetPointerToNode( const BinarySearchTreeType& element );
		
	protected:

		node* root;
		
		enum Direction_Types
		{
			NOT_FOUND, LEFT, RIGHT, ROOT
		} direction;
		unsigned int HeightRecursive( node* current );
		unsigned int BinarySearchTree_size;
		node*& Find( const BinarySearchTreeType& element, node** parent );
		node*& FindParent( const BinarySearchTreeType& element );
		void DisplayPostorderRecursive( node* current, BinarySearchTreeType* return_array, unsigned int& index );
		void FixTree( node* current );
		
	};
	
	/// An AVLBalancedBinarySearchTree is a binary tree that is always balanced
	template <class BinarySearchTreeType>
	class RAK_DLL_EXPORT AVLBalancedBinarySearchTree : public BinarySearchTree<BinarySearchTreeType>
	{
	
	public:
		AVLBalancedBinarySearchTree()	{}
		virtual ~AVLBalancedBinarySearchTree();
		void Add ( const BinarySearchTreeType& input );
		void Del( const BinarySearchTreeType& input );
		BinarySearchTree<BinarySearchTreeType>& operator= ( BinarySearchTree<BinarySearchTreeType>& original_copy )
		{
			return BinarySearchTree<BinarySearchTreeType>::operator= ( original_copy );
		}
		
	private:
		void BalanceTree( typename BinarySearchTree<BinarySearchTreeType>::node* current, bool rotateOnce );
		void RotateRight( typename BinarySearchTree<BinarySearchTreeType>::node *C );
		void RotateLeft( typename BinarySearchTree<BinarySearchTreeType>::node* C );
		void DoubleRotateRight( typename BinarySearchTree<BinarySearchTreeType>::node *A );
		void DoubleRotateLeft( typename BinarySearchTree<BinarySearchTreeType>::node* A );
		bool RightHigher( typename BinarySearchTree<BinarySearchTreeType>::node* A );
		bool LeftHigher( typename BinarySearchTree<BinarySearchTreeType>::node* A );
	};
	
	template <class BinarySearchTreeType>
	void AVLBalancedBinarySearchTree<BinarySearchTreeType>::BalanceTree( typename BinarySearchTree<BinarySearchTreeType>::node* current, bool rotateOnce )
	{
		int left_height, right_height;
		
		while ( current )
		{
			if ( current->left == 0 )
				left_height = 0;
			else
				left_height = Height( current->left );
				
			if ( current->right == 0 )
				right_height = 0;
			else
				right_height = Height( current->right );
				
			if ( right_height - left_height == 2 )
			{
				if ( RightHigher( current->right ) )
					RotateLeft( current->right );
				else
					DoubleRotateLeft( current );
					
				if ( rotateOnce )
					break;
			}
			
			else
				if ( right_height - left_height == -2 )
				{
					if ( LeftHigher( current->left ) )
						RotateRight( current->left );
					else
						DoubleRotateRight( current );
						
					if ( rotateOnce )
						break;
				}
				
			if ( current == this->root )
				break;
				
			current = FindParent( *( current->item ) );
			
		}
	}
	
	template <class BinarySearchTreeType>
	void AVLBalancedBinarySearchTree<BinarySearchTreeType>::Add ( const BinarySearchTreeType& input )
	{
	
		typename BinarySearchTree<BinarySearchTreeType>::node * current = BinarySearchTree<BinarySearchTreeType>::Add ( input, _FILE_AND_LINE_ );
		BalanceTree( current, true );
	}
	
	template <class BinarySearchTreeType>
	void AVLBalancedBinarySearchTree<BinarySearchTreeType>::Del( const BinarySearchTreeType& input )
	{
		typename BinarySearchTree<BinarySearchTreeType>::node * current = BinarySearchTree<BinarySearchTreeType>::Del( input, _FILE_AND_LINE_ );
		BalanceTree( current, false );
		
	}
	
	template <class BinarySearchTreeType>
	bool AVLBalancedBinarySearchTree<BinarySearchTreeType>::RightHigher( typename BinarySearchTree<BinarySearchTreeType>::node *A )
	{
		if ( A == 0 )
			return false;
			
		return Height( A->right ) > Height( A->left );
	}
	
	template <class BinarySearchTreeType>
	bool AVLBalancedBinarySearchTree<BinarySearchTreeType>::LeftHigher( typename BinarySearchTree<BinarySearchTreeType>::node *A )
	{
		if ( A == 0 )
			return false;
			
		return Height( A->left ) > Height( A->right );
	}
	
	template <class BinarySearchTreeType>
	void AVLBalancedBinarySearchTree<BinarySearchTreeType>::RotateRight( typename BinarySearchTree<BinarySearchTreeType>::node *C )
	{
		typename BinarySearchTree<BinarySearchTreeType>::node * A, *B, *D;
		/*
		  RIGHT ROTATION
		
		  A = parent(b)
		  b= parent(c)
		  c  = node to rotate around
		
		  A
		  | // Either direction
		  B
		  /   \
		  C
		  /   \
		  D
		
		  TO
		
		  A
		  | // Either Direction
		  C
		  /   \
		  B
		  /   \
		  D
		
		
		  <Leave all other branches branches AS-IS whether they point to another node or simply 0>
		
		*/
		
		B = FindParent( *( C->item ) );
		A = FindParent( *( B->item ) );
		D = C->right;
		
		if ( A )
		{
			// Direction was set by the last find_parent call
			
			if ( this->direction == this->LEFT )
				A->left = C;
			else
				A->right = C;
		}
		
		else
			this->root = C;  // If B has no parent parent then B must have been the root node
			
		B->left = D;
		
		C->right = B;
	}
	
	template <class BinarySearchTreeType>
	void AVLBalancedBinarySearchTree<BinarySearchTreeType>::DoubleRotateRight( typename BinarySearchTree<BinarySearchTreeType>::node *A )
	{
		// The left side of the left child must be higher for the tree to balance with a right rotation.  If it isn't, rotate it left before the normal rotation so it is.
		RotateLeft( A->left->right );
		RotateRight( A->left );
	}
	
	template <class BinarySearchTreeType>
	void AVLBalancedBinarySearchTree<BinarySearchTreeType>::RotateLeft( typename BinarySearchTree<BinarySearchTreeType>::node *C )
	{
		typename BinarySearchTree<BinarySearchTreeType>::node * A, *B, *D;
		/*
		  RIGHT ROTATION
		
		  A = parent(b)
		  b= parent(c)
		  c  = node to rotate around
		
		  A
		  | // Either direction
		  B
		  /   \
		  C
		  /  \
		  D
		
		  TO
		
		  A
		  | // Either Direction
		  C
		  /   \
		  B
		  /   \
		  D
		
		
		  <Leave all other branches branches AS-IS whether they point to another node or simply 0>
		
		*/
		
		B = FindParent( *( C->item ) );
		A = FindParent( *( B->item ) );
		D = C->left;
		
		if ( A )
		{
			// Direction was set by the last find_parent call
			
			if ( this->direction == this->LEFT )
				A->left = C;
			else
				A->right = C;
		}
		
		else
			this->root = C;  // If B has no parent parent then B must have been the root node
			
		B->right = D;
		
		C->left = B;
	}
	
	template <class BinarySearchTreeType>
	void AVLBalancedBinarySearchTree<BinarySearchTreeType>::DoubleRotateLeft( typename BinarySearchTree<BinarySearchTreeType>::node *A )
	{
		// The left side of the right child must be higher for the tree to balance with a left rotation.  If it isn't, rotate it right before the normal rotation so it is.
		RotateRight( A->right->left );
		RotateLeft( A->right );
	}
	
	template <class BinarySearchTreeType>
	AVLBalancedBinarySearchTree<BinarySearchTreeType>::~AVLBalancedBinarySearchTree()
	{
		this->Clear(_FILE_AND_LINE_);
	}
	
	template <class BinarySearchTreeType>
	unsigned int BinarySearchTree<BinarySearchTreeType>::Size( void )
	{
		return BinarySearchTree_size;
	}
	
	template <class BinarySearchTreeType>
	unsigned int BinarySearchTree<BinarySearchTreeType>::Height( typename BinarySearchTree::node* starting_node )
	{
		if ( BinarySearchTree_size == 0 || starting_node == 0 )
			return 0;
		else
			return HeightRecursive( starting_node );
	}
	
	// Recursively return the height of a binary tree
	template <class BinarySearchTreeType>
	unsigned int BinarySearchTree<BinarySearchTreeType>::HeightRecursive( typename BinarySearchTree::node* current )
	{
		unsigned int left_height = 0, right_height = 0;
		
		if ( ( current->left == 0 ) && ( current->right == 0 ) )
			return 1; // Leaf
			
		if ( current->left != 0 )
			left_height = 1 + HeightRecursive( current->left );
			
		if ( current->right != 0 )
			right_height = 1 + HeightRecursive( current->right );
			
		if ( left_height > right_height )
			return left_height;
		else
			return right_height;
	}
	
	template <class BinarySearchTreeType>
	BinarySearchTree<BinarySearchTreeType>::BinarySearchTree()
	{
		BinarySearchTree_size = 0;
		root = 0;
	}
	
	template <class BinarySearchTreeType>
	BinarySearchTree<BinarySearchTreeType>::~BinarySearchTree()
	{
		this->Clear(_FILE_AND_LINE_);
	}
	
	template <class BinarySearchTreeType>
	BinarySearchTreeType*& BinarySearchTree<BinarySearchTreeType>::GetPointerToNode( const BinarySearchTreeType& element )
	{
		static typename BinarySearchTree::node * tempnode;
		static BinarySearchTreeType* dummyptr = 0;
		tempnode = Find ( element, &tempnode );
		
		if ( this->direction == this->NOT_FOUND )
			return dummyptr;
			
		return tempnode->item;
	}
	
	template <class BinarySearchTreeType>
	typename BinarySearchTree<BinarySearchTreeType>::node*& BinarySearchTree<BinarySearchTreeType>::Find( const BinarySearchTreeType& element, typename BinarySearchTree<BinarySearchTreeType>::node** parent )
	{
		static typename BinarySearchTree::node * current;
		
		current = this->root;
		*parent = 0;
		this->direction = this->ROOT;
		
		if ( BinarySearchTree_size == 0 )
		{
			this->direction = this->NOT_FOUND;
			return current = 0;
		}
		
		// Check if the item is at the root
		if ( element == *( current->item ) )
		{
			this->direction = this->ROOT;
			return current;
		}

		for (;;)
		{
			// Move pointer
			
			if ( element < *( current->item ) )
			{
				*parent = current;
				this->direction = this->LEFT;
				current = current->left;
			}
			
			else
				if ( element > *( current->item ) )
				{
					*parent = current;
					this->direction = this->RIGHT;
					current = current->right;
				}
				
			if ( current == 0 )
				break;
				
			// Check if new position holds the item
			if ( element == *( current->item ) )
			{
				return current;
			}
		}
		
		
		this->direction = this->NOT_FOUND;
		return current = 0;
	}
	
	template <class BinarySearchTreeType>
	typename BinarySearchTree<BinarySearchTreeType>::node*& BinarySearchTree<BinarySearchTreeType>::FindParent( const BinarySearchTreeType& element )
	{
		static typename BinarySearchTree::node * parent;
		Find ( element, &parent );
		return parent;
	}
	
	// Performs a series of value swaps starting with current to fix the tree if needed
	template <class BinarySearchTreeType>
	void BinarySearchTree<BinarySearchTreeType>::FixTree( typename BinarySearchTree::node* current )
	{
		BinarySearchTreeType temp;
		
		while ( 1 )
		{
			if ( ( ( current->left ) != 0 ) && ( *( current->item ) < *( current->left->item ) ) )
			{
				// Swap the current value with the one to the left
				temp = *( current->left->item );
				*( current->left->item ) = *( current->item );
				*( current->item ) = temp;
				current = current->left;
			}
			
			else
				if ( ( ( current->right ) != 0 ) && ( *( current->item ) > *( current->right->item ) ) )
				{
					// Swap the current value with the one to the right
					temp = *( current->right->item );
					*( current->right->item ) = *( current->item );
					*( current->item ) = temp;
					current = current->right;
				}
				
				else
					break;  // current points to the right place so quit
		}
	}
	
	template <class BinarySearchTreeType>
	typename BinarySearchTree<BinarySearchTreeType>::node* BinarySearchTree<BinarySearchTreeType>::Del( const BinarySearchTreeType& input, const char *file, unsigned int line )
	{
		typename BinarySearchTree::node * node_to_delete, *current, *parent;
		
		if ( BinarySearchTree_size == 0 )
			return 0;
			
		if ( BinarySearchTree_size == 1 )
		{
			Clear(file, line);
			return 0;
		}
		
		node_to_delete = Find( input, &parent );
		
		if ( direction == NOT_FOUND )
			return 0;  // Couldn't find the element
			
		current = node_to_delete;
		
		// Replace the deleted node with the appropriate value
		if ( ( current->right ) == 0 && ( current->left ) == 0 )    // Leaf node, just remove it
		{
		
			if ( parent )
			{
				if ( direction == LEFT )
					parent->left = 0;
				else
					parent->right = 0;
			}
			
			SLNet::OP_DELETE(node_to_delete->item, file, line);
			SLNet::OP_DELETE(node_to_delete, file, line);
			BinarySearchTree_size--;
			return parent;
		}
		else
			if ( ( current->right ) != 0 && ( current->left ) == 0 )   // Node has only one child, delete it and cause the parent to point to that child
			{
			
				if ( parent )
				{
					if ( direction == RIGHT )
						parent->right = current->right;
					else
						parent->left = current->right;
				}
				
				else
					root = current->right; // Without a parent this must be the root node
					
				SLNet::OP_DELETE(node_to_delete->item, file, line);
				
				SLNet::OP_DELETE(node_to_delete, file, line);
				
				BinarySearchTree_size--;
				
				return parent;
			}
			else
				if ( ( current->right ) == 0 && ( current->left ) != 0 )   // Node has only one child, delete it and cause the parent to point to that child
				{
				
					if ( parent )
					{
						if ( direction == RIGHT )
							parent->right = current->left;
						else
							parent->left = current->left;
					}
					
					else
						root = current->left; // Without a parent this must be the root node
						
					SLNet::OP_DELETE(node_to_delete->item, file, line);
					
					SLNet::OP_DELETE(node_to_delete, file, line);
					
					BinarySearchTree_size--;
					
					return parent;
				}
				else // Go right, then as left as far as you can
				{
					parent = current;
					direction = RIGHT;
					current = current->right; // Must have a right branch because the if statements above indicated that it has 2 branches
					
					while ( current->left )
					{
						direction = LEFT;
						parent = current;
						current = current->left;
					}
					
					// Replace the value held by the node to SLNet::OP_DELETE(with the value pointed to by current, _FILE_AND_LINE_);
					*( node_to_delete->item ) = *( current->item );
					
					// Delete current.
					// If it is a leaf node just delete it
					if ( current->right == 0 )
					{
						if ( direction == RIGHT )
							parent->right = 0;
						else
							parent->left = 0;
							
						SLNet::OP_DELETE(current->item, file, line);
						
						SLNet::OP_DELETE(current, file, line);
						
						BinarySearchTree_size--;
						
						return parent;
					}
					
					else
					{
						// Skip this node and make its parent point to its right branch
						
						if ( direction == RIGHT )
							parent->right = current->right;
						else
							parent->left = current->right;
							
						SLNet::OP_DELETE(current->item, file, line);
						
						SLNet::OP_DELETE(current, file, line);
						
						BinarySearchTree_size--;
						
						return parent;
					}
				}
	}
	
	template <class BinarySearchTreeType>
	typename BinarySearchTree<BinarySearchTreeType>::node* BinarySearchTree<BinarySearchTreeType>::Add ( const BinarySearchTreeType& input, const char *file, unsigned int line )
	{
		typename BinarySearchTree::node * current;
		
		// Add the new element to the tree according to the following alogrithm:
		// 1.  If the current node is empty add the new leaf
		// 2.  If the element is less than the current node then go down the left branch
		// 3.  If the element is greater than the current node then go down the right branch
		
		if ( BinarySearchTree_size == 0 )
		{
			BinarySearchTree_size = 1;
			root = SLNet::OP_NEW<typename BinarySearchTree::node>( file, line );
			root->item = SLNet::OP_NEW<BinarySearchTreeType>( file, line );
			*( root->item ) = input;
			root->left = 0;
			root->right = 0;
			
			return root;
		}
		
		else
		{
			// start at the root
			current = root;

			for(;;)    // This loop traverses the tree to find a spot for insertion
			{
			
				if ( input < *( current->item ) )
				{
					if ( current->left == 0 )
					{
						current->left = SLNet::OP_NEW<typename BinarySearchTree::node>( file, line );
						current->left->item = SLNet::OP_NEW<BinarySearchTreeType>( file, line );
						current = current->left;
						current->left = 0;
						current->right = 0;
						*( current->item ) = input;
						
						BinarySearchTree_size++;
						return current;
					}
					
					else
					{
						current = current->left;
					}
				}
				
				else
					if ( input > *( current->item ) )
					{
						if ( current->right == 0 )
						{
							current->right = SLNet::OP_NEW<typename BinarySearchTree::node>( file, line );
							current->right->item = SLNet::OP_NEW<BinarySearchTreeType>( file, line );
							current = current->right;
							current->left = 0;
							current->right = 0;
							*( current->item ) = input;
							
							BinarySearchTree_size++;
							return current;
						}
						
						else
						{
							current = current->right;
						}
					}
					
					else
						return 0; // ((input == current->item) == true) which is not allowed since the tree only takes discrete values.  Do nothing
			}
		}
	}
	
	template <class BinarySearchTreeType>
	bool BinarySearchTree<BinarySearchTreeType>::IsIn( const BinarySearchTreeType& input )
	{
		typename BinarySearchTree::node * parent;
		find( input, &parent );
		
		if ( direction != NOT_FOUND )
			return true;
		else
			return false;
	}
	
	
	template <class BinarySearchTreeType>
	void BinarySearchTree<BinarySearchTreeType>::DisplayInorder( BinarySearchTreeType* return_array )
	{
		typename BinarySearchTree::node * current, *parent;
		bool just_printed = false;
		
		unsigned int index = 0;
		
		current = root;
		
		if ( BinarySearchTree_size == 0 )
			return ; // Do nothing for an empty tree
			
		else
			if ( BinarySearchTree_size == 1 )
			{
				return_array[ 0 ] = *( root->item );
				return ;
			}
			
			
		direction = ROOT;  // Reset the direction
		
		while ( index != BinarySearchTree_size )
		{
			// direction is set by the find function and holds the direction of the parent to the last node visited.  It is used to prevent revisiting nodes
			
			if ( ( current->left != 0 ) && ( direction != LEFT ) && ( direction != RIGHT ) )
			{
				//  Go left if the following 2 conditions are true
				//  I can go left
				//  I did not just move up from a right child
				//  I did not just move up from a left child
				
				current = current->left;
				direction = ROOT;  // Reset the direction
			}
			
			else
				if ( ( direction != RIGHT ) && ( just_printed == false ) )
				{
					// Otherwise, print the current node if the following 3 conditions are true:
					// I did not just move up from a right child
					// I did not print this ndoe last cycle
					
					return_array[ index++ ] = *( current->item );
					just_printed = true;
				}
				
				else
					if ( ( current->right != 0 ) && ( direction != RIGHT ) )
					{
						// Otherwise, go right if the following 2 conditions are true
						// I did not just move up from a right child
						// I can go right
						
						current = current->right;
						direction = ROOT;  // Reset the direction
						just_printed = false;
					}
					
					else
					{
						//  Otherwise I've done everything I can.  Move up the tree one node
						parent = FindParent( *( current->item ) );
						current = parent;
						just_printed = false;
					}
		}
	}
	
	template <class BinarySearchTreeType>
	void BinarySearchTree<BinarySearchTreeType>::DisplayPreorder( BinarySearchTreeType* return_array )
	{
		typename BinarySearchTree::node * current, *parent;
		
		unsigned int index = 0;
		
		current = root;
		
		if ( BinarySearchTree_size == 0 )
			return ; // Do nothing for an empty tree
			
		else
			if ( BinarySearchTree_size == 1 )
			{
				return_array[ 0 ] = *( root->item );
				return ;
			}
			
			
		direction = ROOT;  // Reset the direction
		return_array[ index++ ] = *( current->item );
		
		while ( index != BinarySearchTree_size )
		{
			// direction is set by the find function and holds the direction of the parent to the last node visited.  It is used to prevent revisiting nodes
			
			if ( ( current->left != 0 ) && ( direction != LEFT ) && ( direction != RIGHT ) )
			{
			
				current = current->left;
				direction = ROOT;
				
				// Everytime you move a node print it
				return_array[ index++ ] = *( current->item );
			}
			
			else
				if ( ( current->right != 0 ) && ( direction != RIGHT ) )
				{
					current = current->right;
					direction = ROOT;
					
					// Everytime you move a node print it
					return_array[ index++ ] = *( current->item );
				}
				
				else
				{
					//  Otherwise I've done everything I can.  Move up the tree one node
					parent = FindParent( *( current->item ) );
					current = parent;
				}
		}
	}
	
	template <class BinarySearchTreeType>
	inline void BinarySearchTree<BinarySearchTreeType>::DisplayPostorder( BinarySearchTreeType* return_array )
	{
		unsigned int index = 0;
		
		if ( BinarySearchTree_size == 0 )
			return ; // Do nothing for an empty tree
			
		else
			if ( BinarySearchTree_size == 1 )
			{
				return_array[ 0 ] = *( root->item );
				return ;
			}
			
		DisplayPostorderRecursive( root, return_array, index );
	}
	
	
	// Recursively do a postorder traversal
	template <class BinarySearchTreeType>
	void BinarySearchTree<BinarySearchTreeType>::DisplayPostorderRecursive( typename BinarySearchTree::node* current, BinarySearchTreeType* return_array, unsigned int& index )
	{
		if ( current->left != 0 )
			DisplayPostorderRecursive( current->left, return_array, index );
			
		if ( current->right != 0 )
			DisplayPostorderRecursive( current->right, return_array, index );
			
		return_array[ index++ ] = *( current->item );
		
	}
	
	
	template <class BinarySearchTreeType>
	void BinarySearchTree<BinarySearchTreeType>::DisplayBreadthFirstSearch( BinarySearchTreeType* return_array )
	{
		typename BinarySearchTree::node * current;
		unsigned int index = 0;
		
		// Display the tree using a breadth first search
		// Put the children of the current node into the queue
		// Pop the queue, put its children into the queue, repeat until queue is empty
		
		if ( BinarySearchTree_size == 0 )
			return ; // Do nothing for an empty tree
			
		else
			if ( BinarySearchTree_size == 1 )
			{
				return_array[ 0 ] = *( root->item );
				return ;
			}
			
			else
			{
				DataStructures::QueueLinkedList<node *> tree_queue;
				
				// Add the root of the tree I am copying from
				tree_queue.Push( root );
				
				do
				{
					current = tree_queue.Pop();
					return_array[ index++ ] = *( current->item );
					
					// Add the child or children of the tree I am copying from to the queue
					
					if ( current->left != 0 )
						tree_queue.Push( current->left );
						
					if ( current->right != 0 )
						tree_queue.Push( current->right );
						
				}
				
				while ( tree_queue.Size() > 0 );
			}
	}
	
	
	template <class BinarySearchTreeType>
	BinarySearchTree<BinarySearchTreeType>::BinarySearchTree( const BinarySearchTree& original_copy )
	{
		typename BinarySearchTree::node * current;
		// Copy the tree using a breadth first search
		// Put the children of the current node into the queue
		// Pop the queue, put its children into the queue, repeat until queue is empty
		
		// This is a copy of the constructor.  A bug in Visual C++ made it so if I just put the constructor call here the variable assignments were ignored.
		BinarySearchTree_size = 0;
		root = 0;
		
		if ( original_copy.BinarySearchTree_size == 0 )
		{
			BinarySearchTree_size = 0;
		}
		
		else
		{
			DataStructures::QueueLinkedList<node *> tree_queue;
			
			// Add the root of the tree I am copying from
			tree_queue.Push( original_copy.root );
			
			do
			{
				current = tree_queue.Pop();
				
				Add ( *( current->item ), _FILE_AND_LINE_ )
				
				;
				
				// Add the child or children of the tree I am copying from to the queue
				if ( current->left != 0 )
					tree_queue.Push( current->left );
					
				if ( current->right != 0 )
					tree_queue.Push( current->right );
					
			}
			
			while ( tree_queue.Size() > 0 );
		}
	}
	
	template <class BinarySearchTreeType>
	BinarySearchTree<BinarySearchTreeType>& BinarySearchTree<BinarySearchTreeType>::operator= ( const BinarySearchTree& original_copy )
	{
		typename BinarySearchTree::node * current;
		
		if ( ( &original_copy ) == this )
			return *this;
			
		Clear( _FILE_AND_LINE_ );  // Remove the current tree
		
		// This is a copy of the constructor.  A bug in Visual C++ made it so if I just put the constructor call here the variable assignments were ignored.
		BinarySearchTree_size = 0;
		
		root = 0;
		
		
		// Copy the tree using a breadth first search
		// Put the children of the current node into the queue
		// Pop the queue, put its children into the queue, repeat until queue is empty
		if ( original_copy.BinarySearchTree_size == 0 )
		{
			BinarySearchTree_size = 0;
		}
		
		else
		{
			DataStructures::QueueLinkedList<node *> tree_queue;
			
			// Add the root of the tree I am copying from
			tree_queue.Push( original_copy.root );
			
			do
			{
				current = tree_queue.Pop();
				
				Add ( *( current->item ), _FILE_AND_LINE_ )
				
				;
				
				// Add the child or children of the tree I am copying from to the queue
				if ( current->left != 0 )
					tree_queue.Push( current->left );
					
				if ( current->right != 0 )
					tree_queue.Push( current->right );
					
			}
			
			while ( tree_queue.Size() > 0 );
		}
		
		return *this;
	}
	
	template <class BinarySearchTreeType>
	inline void BinarySearchTree<BinarySearchTreeType>::Clear ( const char *file, unsigned int line )
	{
		typename BinarySearchTree::node * current, *parent;
		
		current = root;
		
		while ( BinarySearchTree_size > 0 )
		{
			if ( BinarySearchTree_size == 1 )
			{
				SLNet::OP_DELETE(root->item, file, line);
				SLNet::OP_DELETE(root, file, line);
				root = 0;
				BinarySearchTree_size = 0;
			}
			
			else
			{
				if ( current->left != 0 )
				{
					current = current->left;
				}
				
				else
					if ( current->right != 0 )
					{
						current = current->right;
					}
					
					else // leaf
					{
						// Not root node so must have a parent
						parent = FindParent( *( current->item ) );
						
						if ( ( parent->left ) == current )
							parent->left = 0;
						else
							parent->right = 0;
							
						SLNet::OP_DELETE(current->item, file, line);
						
						SLNet::OP_DELETE(current, file, line);
						
						current = parent;
						
						BinarySearchTree_size--;
					}
			}
		}
	}
	
} // End namespace

#endif
