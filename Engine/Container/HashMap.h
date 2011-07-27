//
// Urho3D Engine
// Copyright (c) 2008-2011 Lasse Öörni
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//

#pragma once

#include "HashBase.h"
#include "Pair.h"

/// Hash-based map template class
template <class T, class U> class HashMap : public HashBase
{
public:
    /// Hash map key-value pair with const key
    class KeyValue
    {
    public:
        /// Construct with default key
        KeyValue() :
            first_(T())
        {
        }
        
        /// Construct with key and value
        KeyValue(const T& first, const U& second) :
            first_(first),
            second_(second)
        {
        }
        
        /// Test for equality with another pair
        bool operator == (const KeyValue& rhs) const { return first_ == rhs.first_ && second_ == rhs.second_; }
        /// Test for inequality with another pair
        bool operator != (const KeyValue& rhs) const { return first_ != rhs.first_ || second_ != rhs.second_; }
        
        const T first_;
        U second_;
    };
    
    /// Hash map node
    struct Node : public HashNodeBase
    {
        /// Construct undefined
        Node()
        {
        }
        
        /// Construct with key and value
        Node(const T& key, const U& value) :
            pair_(key, value)
        {
        }
        
        /// Key-value pair
        KeyValue pair_;
        
        /// Return next node
        Node* Next() const { return static_cast<Node*>(next_); }
        /// Return previous node
        Node* Prev() const { return static_cast<Node*>(prev_); }
        /// Return next node in the bucket
        Node* Down() const { return static_cast<Node*>(down_); }
    };
    
    /// Hash map node iterator
    class Iterator : public HashIteratorBase
    {
    public:
        /// Construct
        Iterator(Node* ptr) :
            HashIteratorBase(ptr)
        {
        }
        
        /// Preincrement the pointer
        Iterator& operator ++ () { GotoNext(); return *this; }
        /// Postincrement the pointer
        Iterator operator ++ (int) { Iterator it = *this; GotoNext(); return it; }
        /// Predecrement the pointer
        Iterator& operator -- () { GotoPrev(); return *this; }
        /// Postdecrement the pointer
        Iterator operator -- (int) { Iterator it = *this; GotoPrev(); return it; }
        
        /// Point to the pair
        KeyValue* operator -> () const { return &(static_cast<Node*>(ptr_))->pair_; }
        /// Dereference the pair
        KeyValue& operator * () const { return (static_cast<Node*>(ptr_))->pair_; }
    };
    
    /// Hash map node const iterator
    class ConstIterator : public HashIteratorBase
    {
    public:
        /// Construct
        ConstIterator(Node* ptr) :
            HashIteratorBase(ptr)
        {
        }
        
        /// Construct from a non-const iterator
        ConstIterator(const Iterator& rhs) :
            HashIteratorBase(rhs.ptr_)
        {
        }
        
        /// Assign from a non-const iterator
        ConstIterator& operator = (const Iterator& rhs) { ptr_ = rhs.ptr_; return *this; }
        /// Preincrement the pointer
        ConstIterator& operator ++ () { GotoNext(); return *this; }
        /// Postincrement the pointer
        ConstIterator operator ++ (int) { ConstIterator it = *this; GotoNext(); return it; }
        /// Predecrement the pointer
        ConstIterator& operator -- () { GotoPrev(); return *this; }
        /// Postdecrement the pointer
        ConstIterator operator -- (int) { ConstIterator it = *this; GotoPrev(); return it; }
        
        /// Point to the pair
        const KeyValue* operator -> () const { return &(static_cast<Node*>(ptr_))->pair_; }
        /// Dereference the pair
        const KeyValue& operator * () const { return (static_cast<Node*>(ptr_))->pair_; }
    };
    
    /// Construct empty
    HashMap()
    {
        // Reserve the tail node
        allocator_ = AllocatorInitialize(sizeof(Node));
        head_ = tail_ = ReserveNode();
    }
    
    /// Construct from another hash map
    HashMap(const HashMap<T, U>& map)
    {
        // Reserve the tail node
        allocator_ = AllocatorInitialize(sizeof(Node));
        head_ = tail_ = ReserveNode();
        
        *this = map;
    }
    
    /// Destruct
    ~HashMap()
    {
        Clear();
        FreeNode(Tail());
        AllocatorUninitialize(allocator_);
        delete[] ptrs_;
    }
    
    /// Assign a hash map
    HashMap& operator = (const HashMap<T, U>& rhs)
    {
        Clear();
        Insert(rhs);
        
        return *this;
    }
    
    /// Add-assign a pair
    HashMap& operator += (const Pair<T, U>& rhs)
    {
        Insert(rhs);
        return *this;
    }
    
    /// Add-assign a hash map
    HashMap& operator += (const HashMap<T, U>& rhs)
    {
        Insert(rhs);
        return *this;
    }
    
    /// Index the map. Create a new pair if key not found
    U& operator [] (const T& key)
    {
        if (!numBuckets_)
            return InsertNode(key, U())->pair_.second_;
        
        unsigned hashKey = MakeHash(key) & (numBuckets_ - 1);
        
        Node* node = FindNode(key, hashKey);
        if (node)
            return node->pair_.second_;
        else
            return InsertNode(key, U())->pair_.second_;
    }
    
    /// Insert a pair. Return an iterator to it
    Iterator Insert(const Pair<T, U>& pair)
    {
        return Iterator(InsertNode(pair.first_, pair.second_));
    }
    
    /// Insert a map
    void Insert(const HashMap<T, U>& map)
    {
        ConstIterator it = map.Begin();
        ConstIterator end = map.End();
        while (it != end)
        {
            InsertNode(it->first_, it->second_);
            ++it;
        }
    }
    
    /// Insert a pair by iterator. Return iterator to the value
    Iterator Insert(const ConstIterator& it)
    {
        return Iterator(InsertNode(it->first_, it->second_));
    }
    
    /// Insert a range by iterators
    void Insert(const ConstIterator& start, const ConstIterator& end)
    {
        ConstIterator it = start;
        while (it != end)
            InsertNode(*it++);
    }
    
    /// Erase a pair by key. Return true if was found
    bool Erase(const T& key)
    {
        if (!numBuckets_)
            return false;
        
        unsigned hashKey = MakeHash(key) & (numBuckets_ - 1);
        
        Node* previous;
        Node* node = FindNode(key, hashKey, previous);
        if (!node)
            return false;
        
        if (previous)
            previous->down_ = node->down_;
        else
            ptrs_[hashKey] = node->down_;
        EraseNode(node);
        
        return true;
    }
    
    /// Erase a pair by iterator
    void Erase(const Iterator& it)
    {
        Erase(it->first_);
    }
    
    /// Clear the map
    void Clear()
    {
        while (size_)
            EraseNode(Head());
        
        // Reset bucket pointers
        for (unsigned i = 0; i < numBuckets_; ++i)
            ptrs_[i] = 0;
    }
    
    /// Return iterator to the pair with key, or end iterator if not found
    Iterator Find(const T& key)
    {
        if (!numBuckets_)
            return End();
        
        unsigned hashKey = MakeHash(key) & (numBuckets_ - 1);
        Node* node = FindNode(key, hashKey);
        if (node)
            return Iterator(node);
        else
            return End();
    }
    
    /// Return const iterator to the pair with key, or end iterator if not found
    ConstIterator Find(const T& key) const
    {
        if (!numBuckets_)
            return End();
        
        unsigned hashKey = MakeHash(key) & (numBuckets_ - 1);
        Node* node = FindNode(key, hashKey);
        if (node)
            return ConstIterator(node);
        else
            return End();
    }
    
    /// Return whether contains a pair with key
    bool Contains(const T& key) const
    {
        if (!numBuckets_)
            return false;
        
        unsigned hashKey = MakeHash(key) & (numBuckets_ - 1);
        return FindNode(key, hashKey) != 0;
    }
    
    /// Return iterator to the beginning
    Iterator Begin() { return Iterator(Head()); }
    /// Return iterator to the beginning
    ConstIterator Begin() const { return ConstIterator(Head()); }
    /// Return iterator to the end
    Iterator End() { return Iterator(Tail()); }
    /// Return iterator to the end
    ConstIterator End() const { return ConstIterator(Tail()); }
    /// Return first key
    const T& Front() const { return *Begin(); }
    /// Return last key
    const T& Back() const { return *(--End()); }
    /// Return number of key-value pairs
    unsigned Size() const { return size_; }
    /// Return whether map is empty
    bool Empty() const { return size_ == 0; }
    
private:
    /// Return the head pointer with correct type
    Node* Head() const { return reinterpret_cast<Node*>(head_); }
    /// Return the tail pointer with correct type
    Node* Tail() const { return reinterpret_cast<Node*>(tail_); }
    /// Return the bucket pointers with correct type
    Node** Ptrs() const { return reinterpret_cast<Node**>(ptrs_); }
    
    /// Find a node from the buckets
    Node* FindNode(const T& key, unsigned hashKey) const
    {
        Node** ptrs = Ptrs();
        if (!ptrs)
            return 0;
        
        Node* node = ptrs[hashKey];
        while (node)
        {
            if (node->pair_.first_ == key)
                return node;
            node = node->Down();
        }
        
        return 0;
    }
    
    /// Find a node and the previous node from the buckets
    Node* FindNode(const T& key, unsigned hashKey, Node*& previous) const
    {
        previous = 0;
        
        Node** ptrs = Ptrs();
        if (!ptrs)
            return 0;
        
        Node* node = ptrs[hashKey];
        while (node)
        {
            if (node->pair_.first_ == key)
                return node;
            previous = node;
            node = node->Down();
        }
        
        return 0;
    }
    
    /// Insert a key and value and return either the new or existing node
    Node* InsertNode(const T& key, const U& value)
    {
        // If no pointers yet, allocate with minimum bucket count
        if (!ptrs_)
        {
            numBuckets_ = MIN_BUCKETS;
            Rehash();
        }
        
        unsigned hashKey = MakeHash(key) & (numBuckets_ - 1);
        
        // If exists, just change the value
        Node* existing = FindNode(key, hashKey);
        if (existing)
        {
            existing->pair_.second_ = value;
            return existing;
        }
        
        Node** ptrs = Ptrs();
        Node* newNode = InsertNode(Tail(), key, value);
        newNode->down_ = ptrs[hashKey];
        ptrs[hashKey] = newNode;
        
        // Rehash if the maximum load factor has been exceeded
        if (size_ > numBuckets_ * MAX_LOAD_FACTOR)
        {
            numBuckets_ <<= 1;
            Rehash();
        }
        
        return newNode;
    }
    
    /// Insert a node into the list. Return the new node
    Node* InsertNode(Node* dest, const T& key, const U& value)
    {
        if (!dest)
            return 0;
        
        Node* newNode = ReserveNode(key, value);
        Node* prev = dest->Prev();
        newNode->next_ = dest;
        newNode->prev_ = prev;
        if (prev)
            prev->next_ = newNode;
        dest->prev_ = newNode;
        
        // Reassign the head node if necessary
        if (dest == Head())
            head_ = newNode;
        
        ++size_;
        
        return newNode;
    }
    
    /// Erase a node from the list. Return pointer to the next element, or to the end if could not erase
    Node* EraseNode(Node* toRemove)
    {
        // The tail node can not be removed
        if (!toRemove || toRemove == tail_)
            return Tail();
        
        Node* prev = toRemove->Prev();
        Node* next = toRemove->Next();
        if (prev)
            prev->next_ = next;
        next->prev_ = prev;
        
        // Reassign the head node if necessary
        if (toRemove == Head())
            head_ = next;
        
        FreeNode(toRemove);
        --size_;
        
        return next;
    }
    
    /// Reserve a node
    Node* ReserveNode()
    {
        Node* newNode = static_cast<Node*>(AllocatorReserve(allocator_));
        new(newNode) Node();
        return newNode;
    }
    
    /// Reserve a node with specified key and value
    Node* ReserveNode(const T& key, const U& value)
    {
        if (!allocator_)
            allocator_ = AllocatorInitialize(sizeof(Node));
        Node* newNode = static_cast<Node*>(AllocatorReserve(allocator_));
        new(newNode) Node(key, value);
        return newNode;
    }
    
    /// Free a node
    void FreeNode(Node* node)
    {
        (node)->~Node();
        AllocatorFree(allocator_, node);
    }
    
    /// Reallocate and rehash the buckets
    void Rehash()
    {
        delete[] ptrs_;
        
        ptrs_ = new HashNodeBase*[numBuckets_];
        for (unsigned i = 0; i < numBuckets_; ++i)
            ptrs_[i] = 0;
        
        for (Iterator i = Begin(); i != End(); ++i)
        {
            Node* node = reinterpret_cast<Node*>(i.ptr_);
            unsigned hashKey = MakeHash(i->first_) & (numBuckets_ - 1);
            node->down_ = ptrs_[hashKey];
            ptrs_[hashKey] = node;
        }
    }
};
