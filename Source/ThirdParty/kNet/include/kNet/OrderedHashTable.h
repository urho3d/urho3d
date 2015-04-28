/* Copyright The kNet Project.

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License. */
#pragma once

/** @file OrderedHashTable.h
	@brief The OrderedHashTable<T> template class. */

namespace kNet
{

template<typename T, typename HashFunc>
class OrderedHashTable
{
public:
	struct Node
	{
		Node()
		:next(0), prev(0), hashChain(0), used(false)
		{
		}

		T value;
		bool used;
		Node *next;
		Node *prev;
		Node *hashChain;
	};

	explicit OrderedHashTable(size_t numElems)
	:root(0), numElemsMask(numElems-1), size(0)
	{
		data = new Node[numElems];
		root = 0;
	}
	~OrderedHashTable()
	{
		delete[] data;
	}

	size_t Size() const { return size; }

	void Insert(const T &value)
	{
		int idx = HashFunc::Hash(value, numElemsMask);
		if (data[idx].used)
			Remove(&data[idx]);
		data[idx].value = value;
		if (root)
		{
			root->prev = &data[idx];
			data[idx].next = root;
		}
		else
			data[idx].next = 0;
		data[idx].prev = 0;
		data[idx].used = true;
		data[idx].hashChain = 0; ///\todo Support item chains.
		root = &data[idx];
		++size;
	}

	void Clear()
	{
		while(size > 0)
			Remove(First());
	}

	void PopFront()
	{
		Remove(First());
	}

	template<typename KeyType>
	Node *Find(const KeyType &key)
	{
		int idx = HashFunc::Hash(key, numElemsMask);
		if (data[idx].used)
			return &data[idx];
		else
			return 0;
	}

	template<typename KeyType>
	void Remove(const KeyType &key)
	{
		int idx = HashFunc::Hash(key, numElemsMask);
		assert(data[idx].used);
		Remove(&data[idx]);
	}

	void Remove(Node *node)
	{
		if (!node)
			return;
		assert(node->used);

		if (node == root)
			root = node->next;

		node->used = false;
		if (node->prev)
			node->prev->next = node->next;
		if (node->next)
			node->next->prev = node->prev;
		--size;

		assert(root || size == 0);
	}

	Node *FrontNode()
	{
		return root;
	}

	T *Front()
	{ 
		assert(root || size == 0);
		return root ? &root->value : 0;
	}

	Node *First()
	{
		assert(root || size == 0);
		return root;
	}

	Node *Next(Node *node)
	{
		return node->next;
	}

private:
	Node *root;

	Node *data;
	size_t numElemsMask;
	size_t size;

	void operator =(const OrderedHashTable &); ///< \todo Implement.
	OrderedHashTable(const OrderedHashTable &); ///< \todo Implement.
};

} // ~kNet
