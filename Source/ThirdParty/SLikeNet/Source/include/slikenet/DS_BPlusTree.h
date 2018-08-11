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

/// \file DS_BPlusTree.h
///


#ifndef __B_PLUS_TREE_CPP
#define __B_PLUS_TREE_CPP

#include "DS_MemoryPool.h"
#include "DS_Queue.h"
#include <stdio.h>
#include "Export.h"

// Java
// http://www.seanster.com/BplusTree/BplusTree.html

// Overview
// http://babbage.clarku.edu/~achou/cs160/B+Trees/B+Trees.htm

// Deletion
// http://dbpubs.stanford.edu:8090/pub/1995-19

#ifdef _MSC_VER
#pragma warning( push )
#endif

#include "memoryoverride.h"

/// The namespace DataStructures was only added to avoid compiler errors for commonly named data structures
/// As these data structures are stand-alone, you can use them outside of RakNet for your own projects if you wish.
namespace DataStructures
{
	/// Used in the BPlusTree.  Used for both leaf and index nodes.
	/// Don't use a constructor or destructor, due to the memory pool I am using
	template <class KeyType, class DataType, int order>
	struct RAK_DLL_EXPORT Page
	{
		// We use the same data structure for both leaf and index nodes.  
		// It uses a little more memory for index nodes but reduces
		// memory fragmentation, allocations, and deallocations.
		bool isLeaf;

		// Used for both leaf and index nodes.
		// For a leaf it means the number of elements in data
		// For an index it means the number of keys and is one less than the number of children pointers.
		int size;

		// Used for both leaf and index nodes.
		KeyType keys[order];

		// Used only for leaf nodes.  Data is the actual data, while next is the pointer to the next leaf (for B+)
		DataType data[order];
		Page<KeyType, DataType, order> *next;
		Page<KeyType, DataType, order> *previous;

		// Used only for index nodes.  Pointers to the children of this node.
		Page *children[order+1];
	};

	/// A BPlus tree
	/// Written with efficiency and speed in mind.
	template <class KeyType, class DataType, int order>
	class RAK_DLL_EXPORT BPlusTree
	{
	public:
		struct ReturnAction
		{
			KeyType key1;
			KeyType key2;
			enum
			{
				NO_ACTION,
				REPLACE_KEY1_WITH_KEY2,
				PUSH_KEY_TO_PARENT,
				SET_BRANCH_KEY,
			} action; // 0=none, 1=replace key1 with key2
		};

		BPlusTree();
		~BPlusTree();
		void SetPoolPageSize(int size); // Set the page size for the memory pool.  Optionsl
		bool Get(const KeyType key, DataType &out) const;
		bool Delete(const KeyType key);
		bool Delete(const KeyType key, DataType &out);
		bool Insert(const KeyType key, const DataType &data);
		void Clear(void);
		unsigned Size(void) const;
		bool IsEmpty(void) const;
		Page<KeyType, DataType, order> *GetListHead(void) const;
		DataType GetDataHead(void) const;
		void PrintLeaves(void);
		void ForEachLeaf(void (*func)(Page<KeyType, DataType, order> * leaf, int index));
		void ForEachData(void (*func)(DataType input, int index));
		void PrintGraph(void);
	protected:
		void ValidateTreeRecursive(Page<KeyType, DataType, order> *cur);
		void DeleteFromPageAtIndex(const int index, Page<KeyType, DataType, order> *cur);
		static void PrintLeaf(Page<KeyType, DataType, order> * leaf, int index);
		void FreePages(void);
		bool GetIndexOf(const KeyType key, Page<KeyType, DataType, order> *page, int *out) const;
		void ShiftKeysLeft(Page<KeyType, DataType, order> *cur);
		bool CanRotateLeft(Page<KeyType, DataType, order> *cur, int childIndex);
		bool CanRotateRight(Page<KeyType, DataType, order> *cur, int childIndex);
		void RotateRight(Page<KeyType, DataType, order> *cur, int childIndex, ReturnAction *returnAction);
		void RotateLeft(Page<KeyType, DataType, order> *cur, int childIndex, ReturnAction *returnAction);
		Page<KeyType, DataType, order>* InsertIntoNode(const KeyType key, const DataType &childData, int insertionIndex, Page<KeyType, DataType, order> *nodeData, Page<KeyType, DataType, order> *cur, ReturnAction* returnAction);
		Page<KeyType, DataType, order>* InsertBranchDown(const KeyType key, const DataType &data,Page<KeyType, DataType, order> *cur, ReturnAction* returnAction, bool *success);
		Page<KeyType, DataType, order>* GetLeafFromKey(const KeyType key) const;
		bool FindDeleteRebalance(const KeyType key, Page<KeyType, DataType, order> *cur, bool *underflow, KeyType rightRootKey, ReturnAction *returnAction, DataType &out);
		bool FixUnderflow(int branchIndex, Page<KeyType, DataType, order> *cur, KeyType rightRootKey, ReturnAction *returnAction);
		void ShiftNodeLeft(Page<KeyType, DataType, order> *cur);
		void ShiftNodeRight(Page<KeyType, DataType, order> *cur);

		MemoryPool<Page<KeyType, DataType, order> > pagePool;
		Page<KeyType, DataType, order> *root, *leftmostLeaf;
	};

	template<class KeyType, class DataType, int order>
		BPlusTree<KeyType, DataType, order>::BPlusTree ()
	{
		RakAssert(order>1);
		root=0;
		leftmostLeaf=0;
	}
	template<class KeyType, class DataType, int order>
		BPlusTree<KeyType, DataType, order>::~BPlusTree ()
	{
		Clear();
	}
	template<class KeyType, class DataType, int order>
	void BPlusTree<KeyType, DataType, order>::SetPoolPageSize(int size)
	{
		pagePool.SetPageSize(size);
	}
	template<class KeyType, class DataType, int order>
	bool BPlusTree<KeyType, DataType, order>::Get(const KeyType key, DataType &out) const
	{
		if (root==0)
			return false;

		Page<KeyType, DataType, order>* leaf = GetLeafFromKey(key);
		int childIndex;
		
		if (GetIndexOf(key, leaf, &childIndex))
		{
			out=leaf->data[childIndex];
			return true;
		}
		return false;
	}
	template<class KeyType, class DataType, int order>
	void BPlusTree<KeyType, DataType, order>::DeleteFromPageAtIndex(const int index, Page<KeyType, DataType, order> *cur)
	{
		int i;
		for (i=index; i < cur->size-1; i++)
			cur->keys[i]=cur->keys[i+1];
		if (cur->isLeaf)
		{
			for (i=index; i < cur->size-1; i++)
				cur->data[i]=cur->data[i+1];
		}
		else
		{
			for (i=index; i < cur->size-1; i++)
				cur->children[i+1]=cur->children[i+2];
		}
		cur->size--;
	}
	template<class KeyType, class DataType, int order>
	bool BPlusTree<KeyType, DataType, order>::Delete(const KeyType key)
	{
		DataType temp;
		return Delete(key, temp);
	}
	template<class KeyType, class DataType, int order>
	bool BPlusTree<KeyType, DataType, order>::Delete(const KeyType key, DataType &out)
	{
		if (root==0)
			return false;

		ReturnAction returnAction;
		returnAction.action=ReturnAction::NO_ACTION;
		int childIndex;
		bool underflow=false;
		if (root==leftmostLeaf)
		{
			if (GetIndexOf(key, root, &childIndex)==false)
				return false;
			out=root->data[childIndex];
			DeleteFromPageAtIndex(childIndex,root);
			if (root->size==0)
			{
				pagePool.Release(root, _FILE_AND_LINE_);
				root=0;
				leftmostLeaf=0;
			}
			return true;
		}
		else if (FindDeleteRebalance(key, root, &underflow,root->keys[0], &returnAction, out)==false)
			return false;

//		RakAssert(returnAction.action==ReturnAction::NO_ACTION);

		if (underflow && root->size==0)
		{
			// Move the root down.
			Page<KeyType, DataType, order> *oldRoot=root;
			root=root->children[0];
			pagePool.Release(oldRoot, _FILE_AND_LINE_);
			// memset(oldRoot,0,sizeof(root));
		}		
	
		return true;
	}
	template<class KeyType, class DataType, int order>
	bool BPlusTree<KeyType, DataType, order>::FindDeleteRebalance(const KeyType key, Page<KeyType, DataType, order> *cur, bool *underflow, KeyType rightRootKey, ReturnAction *returnAction, DataType &out)
	{
		// Get index of child to follow.
		int branchIndex, childIndex;
		if (GetIndexOf(key, cur, &childIndex))
			branchIndex=childIndex+1;
		else
			branchIndex=childIndex;

		// If child is not a leaf, call recursively
		if (cur->children[branchIndex]->isLeaf==false)
		{
			if (branchIndex<cur->size)
				rightRootKey=cur->keys[branchIndex]; // Shift right to left
			else
				rightRootKey=cur->keys[branchIndex-1]; // Shift center to left

			if (FindDeleteRebalance(key, cur->children[branchIndex], underflow, rightRootKey, returnAction, out)==false)
				return false;

			// Call again in case the root key changed
			if (branchIndex<cur->size)
				rightRootKey=cur->keys[branchIndex]; // Shift right to left
			else
				rightRootKey=cur->keys[branchIndex-1]; // Shift center to left

			if (returnAction->action==ReturnAction::SET_BRANCH_KEY && branchIndex!=childIndex)
			{
				returnAction->action=ReturnAction::NO_ACTION;
				cur->keys[childIndex]=returnAction->key1;

				if (branchIndex<cur->size)
					rightRootKey=cur->keys[branchIndex]; // Shift right to left
				else
					rightRootKey=cur->keys[branchIndex-1]; // Shift center to left
			}
		}
		else
		{
			// If child is a leaf, get the index of the key.  If the item is not found, cancel delete.
			if (GetIndexOf(key, cur->children[branchIndex], &childIndex)==false)
				return false;

			// Delete:
			// Remove childIndex from the child at branchIndex
			out=cur->children[branchIndex]->data[childIndex];
			DeleteFromPageAtIndex(childIndex, cur->children[branchIndex]);

			if (childIndex==0)
			{
				if (branchIndex>0)
					cur->keys[branchIndex-1]=cur->children[branchIndex]->keys[0];

				if (branchIndex==0)
				{
					returnAction->action=ReturnAction::SET_BRANCH_KEY;
					returnAction->key1=cur->children[0]->keys[0];
				}				
			}

			if (cur->children[branchIndex]->size < order/2)
				*underflow=true;
			else
				*underflow=false;
		}

		// Fix underflow:
		if (*underflow)
		{
			*underflow=FixUnderflow(branchIndex, cur, rightRootKey, returnAction);
		}

		return true;
	}
	template<class KeyType, class DataType, int order>
	bool BPlusTree<KeyType, DataType, order>::FixUnderflow(int branchIndex, Page<KeyType, DataType, order> *cur, KeyType rightRootKey, ReturnAction *returnAction)
	{
		// Borrow from a neighbor that has excess.
		Page<KeyType, DataType, order> *source;
		Page<KeyType, DataType, order> *dest;

		if (branchIndex>0 && cur->children[branchIndex-1]->size > order/2)
		{
			dest=cur->children[branchIndex];
			source=cur->children[branchIndex-1];

			// Left has excess
			ShiftNodeRight(dest);
			if (dest->isLeaf)
			{
				dest->keys[0]=source->keys[source->size-1];
				dest->data[0]=source->data[source->size-1];
			}
			else
			{
				dest->children[0]=source->children[source->size];
				dest->keys[0]=cur->keys[branchIndex-1];
			}
			// Update the parent key for the child (middle)
			cur->keys[branchIndex-1]=source->keys[source->size-1];
			source->size--;

	//		if (branchIndex==0)
	//		{
	//			returnAction->action=ReturnAction::SET_BRANCH_KEY;
	//			returnAction->key1=dest->keys[0];
	//		}

			// No underflow
			return false;
		}
		else if (branchIndex<cur->size && cur->children[branchIndex+1]->size > order/2)
		{
			dest=cur->children[branchIndex];
			source=cur->children[branchIndex+1];

			// Right has excess
			if (dest->isLeaf)
			{
				dest->keys[dest->size]=source->keys[0];
				dest->data[dest->size]=source->data[0];

				// The first key in the leaf after shifting is the parent key for the right branch
				cur->keys[branchIndex]=source->keys[1];

#ifdef _MSC_VER
#pragma warning( disable : 4127 ) // warning C4127: conditional expression is constant
#endif
				if (order<=3 && dest->size==0)
				{
					if (branchIndex==0)
					{
						returnAction->action=ReturnAction::SET_BRANCH_KEY;
						returnAction->key1=dest->keys[0];
					}
					else
						cur->keys[branchIndex-1]=cur->children[branchIndex]->keys[0];
				}
			}
			else
			{
				if (returnAction->action==ReturnAction::NO_ACTION)
				{
					returnAction->action=ReturnAction::SET_BRANCH_KEY;
					returnAction->key1=dest->keys[0];
				}
				
				dest->keys[dest->size]=rightRootKey;
				dest->children[dest->size+1]=source->children[0];

				// The shifted off key is the leftmost key for a node
				cur->keys[branchIndex]=source->keys[0];
			}


			dest->size++;
			ShiftNodeLeft(source);

			//cur->keys[branchIndex]=source->keys[0];

//			returnAction->action=ReturnAction::SET_BRANCH_KEY;
//			returnAction->key1=dest->keys[dest->size-1];

			// No underflow
			return false;
		}
		else
		{
			int sourceIndex;

			// If no neighbors have excess, merge two branches.
			//
			// To merge two leaves, just copy the data and keys over.
			//
			// To merge two branches, copy the pointers and keys over, using rightRootKey as the key for the extra pointer
			if (branchIndex<cur->size)
			{
				// Merge right child to current child and delete right child.
				dest=cur->children[branchIndex];
				source=cur->children[branchIndex+1];
			}
			else
			{
				// Move current child to left and delete current child
				dest=cur->children[branchIndex-1];
				source=cur->children[branchIndex];
			}

			// Merge
			if (dest->isLeaf)
			{
				for (sourceIndex=0; sourceIndex<source->size; sourceIndex++)
				{
					dest->keys[dest->size]=source->keys[sourceIndex];
					dest->data[dest->size++]=source->data[sourceIndex];
				}
			}
			else
			{
				// We want the tree root key of the source, not the current.
				dest->keys[dest->size]=rightRootKey;
				dest->children[dest->size++ + 1]=source->children[0];
				for (sourceIndex=0; sourceIndex<source->size; sourceIndex++)
				{
					dest->keys[dest->size]=source->keys[sourceIndex];
					dest->children[dest->size++ + 1]=source->children[sourceIndex + 1];
				}
			}

#ifdef _MSC_VER
#pragma warning( disable : 4127 ) // warning C4127: conditional expression is constant
#endif
			if (order<=3 && branchIndex>0 && cur->children[branchIndex]->isLeaf) // With order==2 it is possible to delete data[0], which is not possible with higher orders.
				cur->keys[branchIndex-1]=cur->children[branchIndex]->keys[0];

			if (branchIndex<cur->size)
			{
				// Update the parent key, removing the source (right)
				DeleteFromPageAtIndex(branchIndex, cur);
			}
			else
			{
				if (branchIndex>0)
				{
					// Update parent key, removing the source (current)
					DeleteFromPageAtIndex(branchIndex-1, cur);
				}
			}

			if (branchIndex==0 && dest->isLeaf)
			{
				returnAction->action=ReturnAction::SET_BRANCH_KEY;
				returnAction->key1=dest->keys[0];
			}

			if (source==leftmostLeaf)
				leftmostLeaf=source->next;

			if (source->isLeaf)
			{
				if (source->previous)
					source->previous->next=source->next;
				if (source->next)
					source->next->previous=source->previous;
			}			

			// Free the source node
			pagePool.Release(source, _FILE_AND_LINE_);
			// memset(source,0,sizeof(root));

			// Return underflow or not of parent.
			return cur->size < order/2;
		}
	}
	template<class KeyType, class DataType, int order>
		void BPlusTree<KeyType, DataType, order>::ShiftNodeRight(Page<KeyType, DataType, order> *cur)
	{
		int i;
		for (i=cur->size; i>0; i--)
			cur->keys[i]=cur->keys[i-1];
		if (cur->isLeaf)
		{
			for (i=cur->size; i>0; i--)
				cur->data[i]=cur->data[i-1];
		}
		else
		{
			for (i=cur->size+1; i>0; i--)
				cur->children[i]=cur->children[i-1];
		}

		cur->size++;
	}
	template<class KeyType, class DataType, int order>
		void BPlusTree<KeyType, DataType, order>::ShiftNodeLeft(Page<KeyType, DataType, order> *cur)
	{
		int i;
		for (i=0; i < cur->size-1; i++)
			cur->keys[i]=cur->keys[i+1];
		if (cur->isLeaf)
		{
			for (i=0; i < cur->size; i++)
				cur->data[i]=cur->data[i+1];
		}
		else
		{
			for (i=0; i < cur->size; i++)
				cur->children[i]=cur->children[i+1];
		}
		cur->size--;
	}
	template<class KeyType, class DataType, int order>
	Page<KeyType, DataType, order>* BPlusTree<KeyType, DataType, order>::InsertIntoNode(const KeyType key, const DataType &leafData, int insertionIndex, Page<KeyType, DataType, order> *nodeData, Page<KeyType, DataType, order> *cur, ReturnAction* returnAction)
	{
		int i;
		if (cur->size < order)
		{
			for (i=cur->size; i > insertionIndex; i--)
				cur->keys[i]=cur->keys[i-1];
			if (cur->isLeaf)
			{
				for (i=cur->size; i > insertionIndex; i--)
					cur->data[i]=cur->data[i-1];
			}
			else
			{
				for (i=cur->size+1; i > insertionIndex+1; i--)
					cur->children[i]=cur->children[i-1];
			}
			cur->keys[insertionIndex]=key;
			if (cur->isLeaf)
				cur->data[insertionIndex]=leafData;
			else
				cur->children[insertionIndex+1]=nodeData;

			cur->size++;
		}
		else
		{
			Page<KeyType, DataType, order>* newPage = pagePool.Allocate( _FILE_AND_LINE_ );
			newPage->isLeaf=cur->isLeaf;
			if (cur->isLeaf)
			{
				newPage->next=cur->next;
				if (cur->next)
					cur->next->previous=newPage;
				newPage->previous=cur;
				cur->next=newPage;
			}

			int destIndex, sourceIndex;

			if (insertionIndex>=(order+1)/2)
			{
				destIndex=0;
				sourceIndex=order/2;

				for (; sourceIndex < insertionIndex; sourceIndex++, destIndex++)
				{
					newPage->keys[destIndex]=cur->keys[sourceIndex];
				}
				newPage->keys[destIndex++]=key;
				for (; sourceIndex < order; sourceIndex++, destIndex++)
				{
					newPage->keys[destIndex]=cur->keys[sourceIndex];
				}

				destIndex=0;
				sourceIndex=order/2;
				if (cur->isLeaf)
				{
					for (; sourceIndex < insertionIndex; sourceIndex++, destIndex++)
					{
						newPage->data[destIndex]=cur->data[sourceIndex];
					}
					newPage->data[destIndex++]=leafData;
					for (; sourceIndex < order; sourceIndex++, destIndex++)
					{
						newPage->data[destIndex]=cur->data[sourceIndex];
					}
				}
				else
				{
					
					for (; sourceIndex < insertionIndex; sourceIndex++, destIndex++)
					{
						newPage->children[destIndex]=cur->children[sourceIndex+1];
					}
					newPage->children[destIndex++]=nodeData;

					// sourceIndex+1 is sort of a hack but it works - because there is one extra child than keys
					// skip past the last child for cur
					for (; sourceIndex+1 < cur->size+1; sourceIndex++, destIndex++)
					{
						newPage->children[destIndex]=cur->children[sourceIndex+1];
					}

					// the first key is the middle key.  Remove it from the page and push it to the parent
					returnAction->action=ReturnAction::PUSH_KEY_TO_PARENT;
					returnAction->key1=newPage->keys[0];
					for (int j=0; j < destIndex-1; j++)
						newPage->keys[j]=newPage->keys[j+1];
					
				}
				cur->size=order/2;
			}
			else
			{
				destIndex=0;
				sourceIndex=(order+1)/2-1;
				for (; sourceIndex < order; sourceIndex++, destIndex++)
					newPage->keys[destIndex]=cur->keys[sourceIndex];
				destIndex=0;
				if (cur->isLeaf)
				{
					sourceIndex=(order+1)/2-1;
					for (; sourceIndex < order; sourceIndex++, destIndex++)
						newPage->data[destIndex]=cur->data[sourceIndex];
				}
				else
				{
					sourceIndex=(order+1)/2;
					for (; sourceIndex < order+1; sourceIndex++, destIndex++)
						newPage->children[destIndex]=cur->children[sourceIndex];

					// the first key is the middle key.  Remove it from the page and push it to the parent
					returnAction->action=ReturnAction::PUSH_KEY_TO_PARENT;
					returnAction->key1=newPage->keys[0];
					for (int j=0; j < destIndex-1; j++)
						newPage->keys[j]=newPage->keys[j+1];
				}
				cur->size=(order+1)/2-1;
				if (cur->size)
				{
					bool b = GetIndexOf(key, cur, &insertionIndex);
					(void) b;
					RakAssert(b==false);
				}
				else
					insertionIndex=0;
				InsertIntoNode(key, leafData, insertionIndex, nodeData, cur, returnAction);
			}

			newPage->size=destIndex;

			return newPage;
		}

		return 0;
	}

	template<class KeyType, class DataType, int order>
	bool BPlusTree<KeyType, DataType, order>::CanRotateLeft(Page<KeyType, DataType, order> *cur, int childIndex)
	{
		return childIndex>0 && cur->children[childIndex-1]->size<order;
	}

	template<class KeyType, class DataType, int order>
	void BPlusTree<KeyType, DataType, order>::RotateLeft(Page<KeyType, DataType, order> *cur, int childIndex, ReturnAction *returnAction)
	{
		Page<KeyType, DataType, order> *dest = cur->children[childIndex-1];
		Page<KeyType, DataType, order> *source = cur->children[childIndex];
		returnAction->key1=source->keys[0];
		dest->keys[dest->size]=source->keys[0];
		dest->data[dest->size]=source->data[0];
		dest->size++;
		for (int i=0; i < source->size-1; i++)
		{
			source->keys[i]=source->keys[i+1];
			source->data[i]=source->data[i+1];
		}
		source->size--;
		cur->keys[childIndex-1]=source->keys[0];
		returnAction->key2=source->keys[0];
	}

	template<class KeyType, class DataType, int order>
	bool BPlusTree<KeyType, DataType, order>::CanRotateRight(Page<KeyType, DataType, order> *cur, int childIndex)
	{
		return childIndex < cur->size && cur->children[childIndex+1]->size<order;
	}

	template<class KeyType, class DataType, int order>
	void BPlusTree<KeyType, DataType, order>::RotateRight(Page<KeyType, DataType, order> *cur, int childIndex, ReturnAction *returnAction)
	{
		Page<KeyType, DataType, order> *dest = cur->children[childIndex+1];
		Page<KeyType, DataType, order> *source = cur->children[childIndex];
		returnAction->key1=dest->keys[0];
		for (int i= dest->size; i > 0; i--)
		{
			dest->keys[i]=dest->keys[i-1];
			dest->data[i]=dest->data[i-1];
		}
		dest->keys[0]=source->keys[source->size-1];
		dest->data[0]=source->data[source->size-1];
		dest->size++;
		source->size--;

		cur->keys[childIndex]=dest->keys[0];
		returnAction->key2=dest->keys[0];
	}
	template<class KeyType, class DataType, int order>
		Page<KeyType, DataType, order>* BPlusTree<KeyType, DataType, order>::GetLeafFromKey(const KeyType key) const
	{
		Page<KeyType, DataType, order>* cur = root;
		int childIndex;
		while (cur->isLeaf==false)
		{
			// When searching, if we match the exact key we go down the pointer after that index
			if (GetIndexOf(key, cur, &childIndex))
				childIndex++;
			cur = cur->children[childIndex];
		}
		return cur;
	}

	template<class KeyType, class DataType, int order>
	Page<KeyType, DataType, order>* BPlusTree<KeyType, DataType, order>::InsertBranchDown(const KeyType key, const DataType &data,Page<KeyType, DataType, order> *cur, ReturnAction *returnAction, bool *success)
	{
		int childIndex;
		int branchIndex;
		if (GetIndexOf(key, cur, &childIndex))
			branchIndex=childIndex+1;
		else
			branchIndex=childIndex;
		Page<KeyType, DataType, order>* newPage;
		if (cur->isLeaf==false)
		{
			if (cur->children[branchIndex]->isLeaf==true && cur->children[branchIndex]->size==order)
			{
				if (branchIndex==childIndex+1)
				{
					*success=false;
					return 0; // Already exists
				}

				if (CanRotateLeft(cur, branchIndex))
				{
					returnAction->action=ReturnAction::REPLACE_KEY1_WITH_KEY2;
					if (key > cur->children[branchIndex]->keys[0])
					{						
						RotateLeft(cur, branchIndex, returnAction);

						int insertionIndex;
						GetIndexOf(key, cur->children[branchIndex], &insertionIndex);
						InsertIntoNode(key, data, insertionIndex, 0, cur->children[branchIndex], 0);
					}
					else
					{
						// Move head element to left and replace it with key,data
						Page<KeyType, DataType, order>* dest=cur->children[branchIndex-1];
						Page<KeyType, DataType, order>* source=cur->children[branchIndex];
						returnAction->key1=source->keys[0];
						returnAction->key2=key;
						dest->keys[dest->size]=source->keys[0];
						dest->data[dest->size]=source->data[0];
						dest->size++;
						source->keys[0]=key;
						source->data[0]=data;	
					}
					cur->keys[branchIndex-1]=cur->children[branchIndex]->keys[0];
					
					return 0;
				}
				else if (CanRotateRight(cur, branchIndex))
				{
					returnAction->action=ReturnAction::REPLACE_KEY1_WITH_KEY2;
					
					if (key < cur->children[branchIndex]->keys[cur->children[branchIndex]->size-1])
					{
						RotateRight(cur, branchIndex, returnAction);

						int insertionIndex;
						GetIndexOf(key, cur->children[branchIndex], &insertionIndex);
						InsertIntoNode(key, data, insertionIndex, 0, cur->children[branchIndex], 0);
						
					}
					else
					{
						// Insert to the head of the right leaf instead and change our key
						returnAction->key1=cur->children[branchIndex+1]->keys[0];
						InsertIntoNode(key, data, 0, 0, cur->children[branchIndex+1], 0);						
						returnAction->key2=key;
					}
					cur->keys[branchIndex]=cur->children[branchIndex+1]->keys[0];
					return 0;					
				}
			}

			newPage=InsertBranchDown(key,data,cur->children[branchIndex], returnAction, success);
			if (returnAction->action==ReturnAction::REPLACE_KEY1_WITH_KEY2)
			{
				if (branchIndex>0 && cur->keys[branchIndex-1]==returnAction->key1)
					cur->keys[branchIndex-1]=returnAction->key2;
			}
			if (newPage)
			{
				if (newPage->isLeaf==false)
				{
					RakAssert(returnAction->action==ReturnAction::PUSH_KEY_TO_PARENT);
					newPage->size--; 
					return InsertIntoNode(returnAction->key1, data, branchIndex, newPage, cur, returnAction);
				}
				else
				{
					return InsertIntoNode(newPage->keys[0], data, branchIndex, newPage, cur, returnAction);
				}				
			}
		}
		else
		{
			if (branchIndex==childIndex+1)
			{
				*success=false;
				return 0; // Already exists				
			}
			else
			{
				return InsertIntoNode(key, data, branchIndex, 0, cur, returnAction);
			}
		}
		
		return 0;
	}
	template<class KeyType, class DataType, int order>
		bool BPlusTree<KeyType, DataType, order>::Insert(const KeyType key, const DataType &data)
	{
		if (root==0)
		{
			// Allocate root and make root a leaf
			root = pagePool.Allocate( _FILE_AND_LINE_ );
			root->isLeaf=true;
			leftmostLeaf=root;
			root->size=1;
			root->keys[0]=key;
			root->data[0]=data;
			root->next=0;
			root->previous=0;
		}
		else
		{
			bool success=true;
			ReturnAction returnAction;
			returnAction.action=ReturnAction::NO_ACTION;
			Page<KeyType, DataType, order>* newPage = InsertBranchDown(key, data, root, &returnAction, &success);
			if (success==false)
				return false;
			if (newPage)
			{
				KeyType newKey;
				if (newPage->isLeaf==false)
				{
					// One key is pushed up through the stack.  I store that at keys[0] but it has to be removed for the page to be correct
					RakAssert(returnAction.action==ReturnAction::PUSH_KEY_TO_PARENT);
					newKey=returnAction.key1;
					newPage->size--;
				}
				else
					 newKey = newPage->keys[0];
				// propagate the root
				Page<KeyType, DataType, order>* newRoot = pagePool.Allocate( _FILE_AND_LINE_ );
				newRoot->isLeaf=false;
				newRoot->size=1;
				newRoot->keys[0]=newKey;
				newRoot->children[0]=root;
				newRoot->children[1]=newPage;
				root=newRoot;
			}
		}

		return true;
	}
	template<class KeyType, class DataType, int order>
	void BPlusTree<KeyType, DataType, order>::ShiftKeysLeft(Page<KeyType, DataType, order> *cur)
	{
		int i;
		for (i=0; i < cur->size; i++)
			cur->keys[i]=cur->keys[i+1];
	}
	template<class KeyType, class DataType, int order>
		void BPlusTree<KeyType, DataType, order>::Clear(void)
	{
		if (root)
		{
			FreePages();
			leftmostLeaf=0;
			root=0;
		}
		pagePool.Clear(_FILE_AND_LINE_);
	}
	template<class KeyType, class DataType, int order>
		unsigned BPlusTree<KeyType, DataType, order>::Size(void) const
	{
		unsigned int count=0;
		DataStructures::Page<KeyType, DataType, order> *cur = GetListHead();
		while (cur)
		{
			count+=cur->size;
			cur=cur->next;
		}
		return count;
	}
	template<class KeyType, class DataType, int order>
		bool BPlusTree<KeyType, DataType, order>::IsEmpty(void) const
	{
		return root==0;
	}
	template<class KeyType, class DataType, int order>
		bool BPlusTree<KeyType, DataType, order>::GetIndexOf(const KeyType key, Page<KeyType, DataType, order> *page, int *out) const
	{
		RakAssert(page->size>0);
		int index, upperBound, lowerBound;
		upperBound=page->size-1;
		lowerBound=0;
		index = page->size/2;

		for(;;)
		{
			if (key==page->keys[index])
			{
				*out=index;
				return true;
			}
			else if (key<page->keys[index])
				upperBound=index-1;
			else
				lowerBound=index+1;

			index=lowerBound+(upperBound-lowerBound)/2;

			if (lowerBound>upperBound)
			{
				*out=lowerBound;
				return false; // No match
			}
		}
	}
	template<class KeyType, class DataType, int order>
		void BPlusTree<KeyType, DataType, order>::FreePages(void)
	{
		DataStructures::Queue<DataStructures::Page<KeyType, DataType, order> *> queue;
		DataStructures::Page<KeyType, DataType, order> *ptr;
		int i;
		queue.Push(root, _FILE_AND_LINE_ );
		while (queue.Size())
		{
			ptr=queue.Pop();
			if (ptr->isLeaf==false)
			{
				for (i=0; i < ptr->size+1; i++)
					queue.Push(ptr->children[i], _FILE_AND_LINE_ );
			}			
			pagePool.Release(ptr, _FILE_AND_LINE_);
		//	memset(ptr,0,sizeof(root));
		};
	}
	template<class KeyType, class DataType, int order>
		Page<KeyType, DataType, order> *BPlusTree<KeyType, DataType, order>::GetListHead(void) const
	{
		return leftmostLeaf;
	}
	template<class KeyType, class DataType, int order>
	DataType BPlusTree<KeyType, DataType, order>::GetDataHead(void) const
	{
		return leftmostLeaf->data[0];
	}
	template<class KeyType, class DataType, int order>
		void BPlusTree<KeyType, DataType, order>::ForEachLeaf(void (*func)(Page<KeyType, DataType, order> * leaf, int index))
	{
		int count=0;
		DataStructures::Page<KeyType, DataType, order> *cur = GetListHead();
		while (cur)
		{
			func(cur, count++);
			cur=cur->next;
		}
	}
	template<class KeyType, class DataType, int order>
		void BPlusTree<KeyType, DataType, order>::ForEachData(void (*func)(DataType input, int index))
	{
		int count=0,i;
		DataStructures::Page<KeyType, DataType, order> *cur = GetListHead();
		while (cur)
		{
			for (i=0; i < cur->size; i++)
				func(cur->data[i], count++);
			cur=cur->next;
		}
	}
	template<class KeyType, class DataType, int order>
		void BPlusTree<KeyType, DataType, order>::PrintLeaf(Page<KeyType, DataType, order> * leaf, int index)
	{
		int i;
		RAKNET_DEBUG_PRINTF("%i] SELF=%p\n", index+1, leaf);
		for (i=0; i < leaf->size; i++)
			RAKNET_DEBUG_PRINTF(" %i. %i\n", i+1, leaf->data[i]);
	}
	template<class KeyType, class DataType, int order>
		void BPlusTree<KeyType, DataType, order>::PrintLeaves(void)
	{
		ForEachLeaf(PrintLeaf);
	}

	template<class KeyType, class DataType, int order>
	void BPlusTree<KeyType, DataType, order>::ValidateTreeRecursive(Page<KeyType, DataType, order> *cur)
	{
		RakAssert(cur==root || cur->size>=order/2);

		if (cur->children[0]->isLeaf)
		{
			RakAssert(cur->children[0]->keys[0] < cur->keys[0]);
			for (int i=0; i < cur->size; i++)
			{
				RakAssert(cur->children[i+1]->keys[0]==cur->keys[i]);
			}
		}
		else
		{
			for (int i=0; i < cur->size+1; i++)
				ValidateTreeRecursive(cur->children[i]);
		}
	}

	template<class KeyType, class DataType, int order>
	void BPlusTree<KeyType, DataType, order>::PrintGraph(void)
	{
		DataStructures::Queue<DataStructures::Page<KeyType, DataType, order> *> queue;
		queue.Push(root,_FILE_AND_LINE_);
		queue.Push(0,_FILE_AND_LINE_);
		DataStructures::Page<KeyType, DataType, order> *ptr;
		int i,j;
		if (root)
		{
			RAKNET_DEBUG_PRINTF("%p(", root);
			for (i=0; i < root->size; i++)
			{
				RAKNET_DEBUG_PRINTF("%i ", root->keys[i]);
			}
			RAKNET_DEBUG_PRINTF(") ");
			RAKNET_DEBUG_PRINTF("\n");
		}
		while (queue.Size())
		{
			ptr=queue.Pop();
			if (ptr==0)
				RAKNET_DEBUG_PRINTF("\n");
			else if (ptr->isLeaf==false)
			{
				for (i=0; i < ptr->size+1; i++)
				{
					RAKNET_DEBUG_PRINTF("%p(", ptr->children[i]);
					//RAKNET_DEBUG_PRINTF("(", ptr->children[i]);
					for (j=0; j < ptr->children[i]->size; j++)
						RAKNET_DEBUG_PRINTF("%i ", ptr->children[i]->keys[j]);
					RAKNET_DEBUG_PRINTF(") ");
					queue.Push(ptr->children[i],_FILE_AND_LINE_);
				}
			 	queue.Push(0,_FILE_AND_LINE_);
				RAKNET_DEBUG_PRINTF(" -- ");
			}
		}
		RAKNET_DEBUG_PRINTF("\n");
	}
}
#ifdef _MSC_VER
#pragma warning( pop )
#endif

#endif

// Code to test this hellish data structure.
/*
#include "DS_BPlusTree.h"
#include <stdio.h>

// Handle underflow on root.  If there is only one item left then I can go downwards.
// Make sure I keep the leftmost pointer valid by traversing it
// When I free a leaf, be sure to adjust the pointers around it.

#include "Rand.h"

void main(void)
{
	DataStructures::BPlusTree<int, int, 16> btree;
	DataStructures::List<int> haveList, removedList;
	int temp;
	int i, j, index;
	int testSize;
	bool b;

	for (testSize=0; testSize < 514; testSize++)
	{
		RAKNET_DEBUG_PRINTF("TestSize=%i\n", testSize);

		for (i=0; i < testSize; i++)
			haveList.Insert(i);

		for (i=0; i < testSize; i++)
		{
			index=i+randomMT()%(testSize-i);
			temp=haveList[index];
			haveList[index]=haveList[i];
			haveList[i]=temp;
		}

		for (i=0; i<testSize; i++)
		{
			btree.Insert(haveList[i], haveList[i]);
			btree.ValidateTree();
		}

		for (i=0; i < testSize; i++)
		{
			index=i+randomMT()%(testSize-i);
			temp=haveList[index];
			haveList[index]=haveList[i];
			haveList[i]=temp;
		}
		for (i=0; i<testSize; i++)
		{
			btree.Delete(haveList[0]); // Asserts on 8th call.  Fails on going to remove 8 (7th call)
			removedList.Insert(haveList[0]);
			haveList.RemoveAtIndex(0);
			for (j=0; j < removedList.Size(); j++)
			{
				b=btree.Get(removedList[j], temp);
				RakAssert(b==false);
			}
			for (j=0; j < haveList.Size(); j++)
			{
				b=btree.Get(haveList[j], temp);
				RakAssert(b==true);
				RakAssert(haveList[j]==temp);
			}
			RakAssert(btree.Size()==haveList.Size());
			btree.ValidateTree();
		}
		btree.Clear(_FILE_AND_LINE_);
		removedList.Clear(_FILE_AND_LINE_);
		haveList.Clear(_FILE_AND_LINE_);
	}

	RAKNET_DEBUG_PRINTF("Done. %i\n", btree.Size());
	char ch[256];
	Gets(ch, sizeof(ch));
}
*/
