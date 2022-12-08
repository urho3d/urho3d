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

/// \internal
/// \brief Hashing container
///


#ifndef __HASH_H
#define __HASH_H 

#include "assert.h"
#include <string.h> // memmove
#include "Export.h"
#include "memoryoverride.h"
#include "string.h"

/// The namespace DataStructures was only added to avoid compiler errors for commonly named data structures
/// As these data structures are stand-alone, you can use them outside of RakNet for your own projects if you wish.
namespace DataStructures
{
	struct HashIndex
	{
		unsigned int primaryIndex;
		unsigned int secondaryIndex;
		bool IsInvalid(void) const {return primaryIndex==(unsigned int) -1;}
		void SetInvalid(void) {primaryIndex=(unsigned int) -1; secondaryIndex=(unsigned int) -1;}
	};

	/// \brief Using a string as a identifier for a node, store an allocated pointer to that node
	template <class key_type, class data_type, unsigned int HASH_SIZE, unsigned long (*hashFunction)(const key_type &) >
	class RAK_DLL_EXPORT Hash
	{	
	public:
		/// Default constructor
		Hash();

		// Destructor
		~Hash();

		void Push(key_type key, const data_type &input, const char *file, unsigned int line );
		data_type* Peek(key_type key );
		bool Pop(data_type& out, key_type key, const char *file, unsigned int line );
		bool RemoveAtIndex(HashIndex index, const char *file, unsigned int line );
		bool Remove(key_type key, const char *file, unsigned int line );
		HashIndex GetIndexOf(key_type key);
		bool HasData(key_type key);
		data_type& ItemAtIndex(const HashIndex &index);
		key_type  KeyAtIndex(const HashIndex &index);
		void GetAsList(DataStructures::List<data_type> &itemList,DataStructures::List<key_type > &keyList,const char *file, unsigned int line) const;
		unsigned int Size(void) const;

		/// \brief Clear the list		
		void Clear( const char *file, unsigned int line );

		struct Node
		{
			Node(key_type strIn, const data_type &_data) {string=strIn; data=_data;}
			key_type  string;
			data_type data;
			// Next in the list for this key
			Node *next;
		};

	protected:
		void ClearIndex(unsigned int index,const char *file, unsigned int line);
		Node **nodeList;
		unsigned int size;
	};

	template <class key_type, class data_type, unsigned int HASH_SIZE, unsigned long (*hashFunction)(const key_type &) >
	Hash<key_type, data_type, HASH_SIZE, hashFunction>::Hash()
	{
		nodeList=0;
		size=0;
	}

	template <class key_type, class data_type, unsigned int HASH_SIZE, unsigned long (*hashFunction)(const key_type &) >
	Hash<key_type, data_type, HASH_SIZE, hashFunction>::~Hash()
	{
		Clear(_FILE_AND_LINE_);
	}

	template <class key_type, class data_type, unsigned int HASH_SIZE, unsigned long (*hashFunction)(const key_type &) >
	void Hash<key_type, data_type, HASH_SIZE, hashFunction>::Push(key_type key, const data_type &input, const char *file, unsigned int line )
	{
		unsigned long hashIndex = (*hashFunction)(key) % HASH_SIZE;
		if (nodeList==0)
		{
			nodeList= SLNet::OP_NEW_ARRAY<Node *>(HASH_SIZE,file,line);
			memset(nodeList,0,sizeof(Node *)*HASH_SIZE);
		}

		Node *newNode= SLNet::OP_NEW_2<Node>(file,line,key,input);
		newNode->next=nodeList[hashIndex];
		nodeList[hashIndex]=newNode;

		size++;
	}

	template <class key_type, class data_type, unsigned int HASH_SIZE, unsigned long (*hashFunction)(const key_type &) >
	data_type* Hash<key_type, data_type, HASH_SIZE, hashFunction>::Peek(key_type key )
	{
		if (nodeList==0)
			return 0;

		unsigned long hashIndex = (*hashFunction)(key) % HASH_SIZE;
		Node *node = nodeList[hashIndex];
		while (node!=0)
		{
			if (node->string==key)
				return &node->data;
			node=node->next;
		}
		return 0;
	}

	template <class key_type, class data_type, unsigned int HASH_SIZE, unsigned long (*hashFunction)(const key_type &) >
	bool Hash<key_type, data_type, HASH_SIZE, hashFunction>::Pop(data_type& out, key_type key, const char *file, unsigned int line )
	{
		if (nodeList==0)
			return false;

		unsigned long hashIndex = (*hashFunction)(key) % HASH_SIZE;
		Node *node = nodeList[hashIndex];
		if (node==0)
			return false;
		if (node->next==0)
		{
			// Only one item.
			if (node->string==key)
			{
				// Delete last item
				out=node->data;
				ClearIndex(hashIndex,_FILE_AND_LINE_);
				return true;
			}
			else
			{
				// Single item doesn't match
				return false;
			}
		}
		else if (node->string==key)
		{
			// First item does match, but more than one item
			out=node->data;
			nodeList[hashIndex]=node->next;
			SLNet::OP_DELETE(node,file,line);
			size--;
			return true;
		}

		Node *last=node;
		node=node->next;

		while (node!=0)
		{
			// First item does not match, but subsequent item might
			if (node->string==key)
			{
				out=node->data;
				// Skip over subsequent item
				last->next=node->next;
				// Delete existing item
				SLNet::OP_DELETE(node,file,line);
				size--;
				return true;
			}
			last=node;
			node=node->next;
		}
		return false;
	}

	template <class key_type, class data_type, unsigned int HASH_SIZE, unsigned long (*hashFunction)(const key_type &) >
	bool Hash<key_type, data_type, HASH_SIZE, hashFunction>::RemoveAtIndex(HashIndex index, const char *file, unsigned int line )
	{
		if (index.IsInvalid())
			return false;

		Node *node = nodeList[index.primaryIndex];
		if (node==0)
			return false;
		if (node->next==0)
		{
			// Delete last item
			ClearIndex(index.primaryIndex,file,line);
			return true;
		}
		else if (index.secondaryIndex==0)
		{
			// First item does match, but more than one item
			nodeList[index.primaryIndex]=node->next;
			SLNet::OP_DELETE(node,file,line);
			size--;
			return true;
		}

		Node *last=node;
		node=node->next;
		--index.secondaryIndex;

		while (index.secondaryIndex!=0)
		{
			last=node;
			node=node->next;
			--index.secondaryIndex;
		}

		// Skip over subsequent item
		last->next=node->next;
		// Delete existing item
		SLNet::OP_DELETE(node,file,line);
		size--;
		return true;
	}

	template <class key_type, class data_type, unsigned int HASH_SIZE, unsigned long (*hashFunction)(const key_type &) >
	bool Hash<key_type, data_type, HASH_SIZE, hashFunction>::Remove(key_type key, const char *file, unsigned int line )
	{
		return RemoveAtIndex(GetIndexOf(key),file,line);
	}

	template <class key_type, class data_type, unsigned int HASH_SIZE, unsigned long (*hashFunction)(const key_type &) >
	HashIndex Hash<key_type, data_type, HASH_SIZE, hashFunction>::GetIndexOf(key_type key)
	{
		if (nodeList==0)
		{
			HashIndex temp;
			temp.SetInvalid();
			return temp;
		}
		HashIndex idx;
		idx.primaryIndex=(*hashFunction)(key) % HASH_SIZE;
		Node *node = nodeList[idx.primaryIndex];
		if (node==0)
		{
			idx.SetInvalid();
			return idx;
		}
		idx.secondaryIndex=0;
		while (node!=0)
		{
			if (node->string==key)
			{
				return idx;
			}
			node=node->next;
			idx.secondaryIndex++;
		}

		idx.SetInvalid();
		return idx;
	}

	template <class key_type, class data_type, unsigned int HASH_SIZE, unsigned long (*hashFunction)(const key_type &) >
	bool Hash<key_type, data_type, HASH_SIZE, hashFunction>::HasData(key_type key)
	{
		return GetIndexOf(key).IsInvalid()==false;
	}

	template <class key_type, class data_type, unsigned int HASH_SIZE, unsigned long (*hashFunction)(const key_type &) >
	data_type& Hash<key_type, data_type, HASH_SIZE, hashFunction>::ItemAtIndex(const HashIndex &index)
	{
		Node *node = nodeList[index.primaryIndex];
		RakAssert(node);
		unsigned int i;
		for (i=0; i < index.secondaryIndex; i++)
		{
			node=node->next;
			RakAssert(node);
		}
		return node->data;
	}

	template <class key_type, class data_type, unsigned int HASH_SIZE, unsigned long (*hashFunction)(const key_type &) >
	key_type  Hash<key_type, data_type, HASH_SIZE, hashFunction>::KeyAtIndex(const HashIndex &index)
	{
		Node *node = nodeList[index.primaryIndex];
		RakAssert(node);
		unsigned int i;
		for (i=0; i < index.secondaryIndex; i++)
		{
			node=node->next;
			RakAssert(node);
		}
		return node->string;
	}

	template <class key_type, class data_type, unsigned int HASH_SIZE, unsigned long (*hashFunction)(const key_type &) >
	void Hash<key_type, data_type, HASH_SIZE, hashFunction>::Clear(const char *file, unsigned int line)
	{
		if (nodeList)
		{
			unsigned int i;
			for (i=0; i < HASH_SIZE; i++)
				ClearIndex(i,file,line);
			SLNet::OP_DELETE_ARRAY(nodeList,file,line);
			nodeList=0;
			size=0;
		}
	}

	template <class key_type, class data_type, unsigned int HASH_SIZE, unsigned long (*hashFunction)(const key_type &) >
	void Hash<key_type, data_type, HASH_SIZE, hashFunction>::ClearIndex(unsigned int index,const char *file, unsigned int line)
	{
		Node *node = nodeList[index];
		Node *next;
		while (node)
		{
			next=node->next;
			SLNet::OP_DELETE(node,file,line);
			node=next;
			size--;
		}
		nodeList[index]=0;
	}

	template <class key_type, class data_type, unsigned int HASH_SIZE, unsigned long (*hashFunction)(const key_type &) >
	void Hash<key_type, data_type, HASH_SIZE, hashFunction>::GetAsList(DataStructures::List<data_type> &itemList,DataStructures::List<key_type > &keyList,const char *file, unsigned int line) const
	{
		if (nodeList==0)
			return;
		itemList.Clear(false,_FILE_AND_LINE_);
		keyList.Clear(false,_FILE_AND_LINE_);

		Node *node;
		unsigned int i;
		for (i=0; i < HASH_SIZE; i++)
		{
			if (nodeList[i])
			{
				node=nodeList[i];
				while (node)
				{
					itemList.Push(node->data,file,line);
					keyList.Push(node->string,file,line);
					node=node->next;
				}
			}
		}
	}
	template <class key_type, class data_type, unsigned int HASH_SIZE, unsigned long (*hashFunction)(const key_type &) >
	unsigned int Hash<key_type, data_type, HASH_SIZE, hashFunction>::Size(void) const
	{
		return size;
	}
}
#endif
