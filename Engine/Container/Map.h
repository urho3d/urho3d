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

#include "ListBase.h"
#include "Pair.h"

#include <new>

// Based on http://eternallyconfuzzled.com/tuts/datastructures/jsw_tut_skip.aspx

/// Map template class using a skip list
template <class T, class U> class Map : public SkipListBase
{
public:
    /// Map key-value pair with const key
    class KeyValue
    {
    public:
        /// Construct with key
        KeyValue(const T& first) :
            first_(first)
        {
        }
        
        /// Construct with key and value
        KeyValue(const T& first, const U& second) :
            first_(first),
            second_(second)
        {
        }
        
        /// Test for equality with another pair
        bool operator == (const KeyValue& rhs) const { return (first_ == rhs.first_) && (second_ == rhs.second_); }
        /// Test for inequality with another pair
        bool operator != (const KeyValue& rhs) const { return (first_ != rhs.first_) || (second_ != rhs.second_); }
        
        const T first_;
        U second_;
    };
    
    /// Map node
    struct Node : public SkipListNodeBase
    {
        /// Key-value pair
        KeyValue pair_;
        
        /// Return next node on a specific height
        Node* GetNext(unsigned height) const
        {
            if (!height)
                return static_cast<Node*>(next_);
            else
                return static_cast<Node*>(levels_[height - 1]);
        }
        
        /// Return previous node
        Node* GetPrev() { return static_cast<Node*>(prev_); }
    };
    
    /// Map node iterator
    class Iterator : public ListIteratorBase
    {
    public:
        /// Construct
        explicit Iterator(Node* ptr) :
            ListIteratorBase(ptr)
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
    
    /// Set node const iterator
    class ConstIterator : public ListIteratorBase
    {
    public:
        /// Construct
        explicit ConstIterator(Node* ptr) :
            ListIteratorBase(ptr)
        {
        }
        
        /// Construct from a non-const iterator
        ConstIterator(const Iterator& rhs) :
            ListIteratorBase(rhs.ptr_)
        {
        }
        
        /// Assign from a non-const iterator
        ConstIterator& operator = (const Iterator& rhs) { ptr_ = rhs.ptr_; return *this; }
        /// Preincrement the pointer
        ConstIterator& operator ++ () { GotoNext(); return *this; }
        /// Postincrement the pointer
        ConstIterator operator ++ (int) { Iterator it = *this; GotoNext(); return it; }
        /// Predecrement the pointer
        ConstIterator& operator -- () { GotoPrev(); return *this; }
        /// Postdecrement the pointer
        ConstIterator operator -- (int) { Iterator it = *this; GotoPrev(); return it; }
        
        /// Point to the pair
        const KeyValue* operator -> () const { return &(static_cast<Node*>(ptr_))->pair_; }
        /// Dereference the pair
        const KeyValue& operator * () const { return (static_cast<Node*>(ptr_))->pair_; }
    };
    
    /// Construct empty
    Map(unsigned maxHeight = MAX_HEIGHT) :
        SkipListBase(maxHeight)
    {
        // Allocate the head and tail nodes and zero the next pointers
        head_ = AllocateNode(maxHeight_);
        tail_ = AllocateNode(maxHeight_);
        Node* head = GetHead();
        Node* tail = GetTail();
        for (unsigned i = 0; i < maxHeight_; ++i)
        {
            head->SetNext(i, tail);
            tail->SetNext(i, 0);
        }
        
        // Allocate the fixup pointers
        fix_ = reinterpret_cast<void**>(new Node*[maxHeight_]);
    }
    
    /// Construct from another map
    Map(const Map<T, U>& map) :
        SkipListBase(map.maxHeight_)
    {
        // Allocate the head and tail nodes and zero the next pointers
        head_ = AllocateNode(maxHeight_);
        tail_ = AllocateNode(maxHeight_);
        Node* head = GetHead();
        Node* tail = GetTail();
        for (unsigned i = 0; i < maxHeight_; ++i)
        {
            head->SetNext(i, tail);
            tail->SetNext(i, 0);
        }
        
        // Allocate the fixup pointers
        fix_ = reinterpret_cast<void**>(new Node*[maxHeight_]);
        
        // Then assign the other map
        *this = map;
    }
    
    /// Destruct
    ~Map()
    {
        Clear();
        DeleteNode(GetHead());
        DeleteNode(GetTail());
        delete[] GetFix();
    }
    
    /// Assign from another map
    Map& operator = (const Map<T, U>& rhs)
    {
        Clear();
        
        // Insert the nodes with same heights
        for (Node* i = rhs.GetHead()->GetNext(0); i != rhs.GetTail(); i = i->GetNext(0))
            InsertNode(Pair<T, U>(i->pair_.first_, i->pair_.second_), i->height_);
        
        return *this;
    }
    
    /// Add-assign a pair
    Map& operator += (const Pair<T, U>& rhs)
    {
        Insert(rhs);
        return *this;
    }
    
    /// Add-assign a map
    Map& operator += (const Map<T, U>& rhs)
    {
        Insert(rhs.Begin(), rhs.End());
        return *this;
    }
    
    /// Index the map
    U& operator [] (const T& key)
    {
        Node* node = FindNode(key);
        if (node)
            return node->pair_.second_;
        else
        {
            // If node did not exist, insert a node with default value, then return the value
            node = InsertNode(Pair<T, U>(key, U()), 0);
            return node->pair_.second_;
        }
    }
    
    /// Test for equality with another map
    bool operator == (const Map<T, U>& rhs) const
    {
        if (rhs.size_ != size_)
            return false;
        
        ConstIterator i = Begin();
        ConstIterator j = rhs.Begin();
        while (i != End())
        {
            if (*i != *j)
                return false;
            ++i;
            ++j;
        }
        
        return true;
    }
    
    /// Test for inequality with another map
    bool operator != (const Map<T, U>& rhs) const
    {
        if (rhs.size_ != size_)
            return true;
        
        ConstIterator i = Begin();
        ConstIterator j = rhs.Begin();
        while (i != End())
        {
            if (*i != *j)
                return true;
            ++i;
            ++j;
        }
        
        return false;
    }
    
    /// Insert into the map
    void Insert(const T& key, const U& value)
    {
        InsertNode(MakePair(key, value), 0);
    }
    
    /// Insert into the map
    void Insert(const Pair<T, U>& pair)
    {
        InsertNode(pair, 0);
    }
    
    /// Insert a range by iterators
    void Insert(const Iterator& start, const Iterator& end)
    {
        Iterator it = start;
        while (it != end)
        {
            Iterator current = it++;
            Insert(*current);
            // Break if the iterator got stuck
            if (it == current)
                break;
        }
    }
    
    /// Erase a key from the map. Return true if was found and erased
    bool Erase(const T& key)
    {
        Node* head = GetHead();
        Node* tail = GetTail();
        Node** fix = GetFix();
        Node* i = head;
        
        for (unsigned j = height_ - 1; j < MAX_HEIGHT; --j)
        {
            for (;;)
            {
                Node* next = i->GetNext(j);
                if ((next) && (next != tail) && (key > next->pair_.first_))
                    i = next;
                else
                    break;
            }
            fix_[j] = i;
        }
        
        // Check if key does not exist
        Node* toRemove = i->GetNext(0);
        if ((!toRemove) || (toRemove == tail) || (toRemove->pair_.first_ != key))
            return false;
        
        // Fix the previous link. However, do not set the head node as a previous link
        Node* prev = toRemove->GetPrev();
        Node* next = toRemove->GetNext(0);
        if (next)
            next->SetPrev(prev != head ? prev : 0);
        
        // Fix the next links
        for (unsigned j = 0; j < height_; ++j)
        {
            Node* fixNext = fix[j]->GetNext(j);
            if (fixNext)
                fix[j]->SetNext(j, fixNext->GetNext(j));
        }
        
        // Check if height should be changed
        while (height_ > 0)
        {
            if (head->GetNext(height_ - 1))
                break;
            head->SetNext(--height_, 0);
        }
        
        DeleteNode(toRemove);
        --size_;
        return true;
    }
    
    /// Erase by an iterator. Return an iterator to the next element
    Iterator Erase(Iterator it)
    {
        if (it != End())
        {
            Iterator current = it++;
            Erase(current->first_);
        }
        
        return it;
    }
    
    /// Erase by a range of iterators. Return the end iterator
    Iterator Erase(const Iterator& start, const Iterator& end)
    {
        Iterator it = start;
        while (it != end)
        {
            Iterator current = it++;
            // Break if the iterator got stuck
            if (it == current)
                break;
            Erase(current->first_);
        }
        
        return it;
    }
    
    /// Clear the map
    void Clear()
    {
        // Let the head and tails node remain, but reset the next pointers
        Node* head = GetHead();
        Node* tail = GetTail();
        Node* node = head->GetNext(0);
        
        for (unsigned i = 0; i < maxHeight_; ++i)
        {
            head->SetNext(i, tail);
            tail->SetPrev(0);
        }
        
        // Then remove all the key nodes
        while (node != tail_)
        {
            Node* current = node;
            node = node->GetNext(0);
            DeleteNode(current);
        }
        
        height_ = 0;
        size_ = 0;
    }
    
    /// Return iterator to the node with key, or end iterator if not found
    Iterator Find(const T& key) { Node* node = FindNode(key); return node ? Iterator(node) : End(); }
    /// Return const iterator to the node with key, or null iterator if not found
    ConstIterator Find(const T& key) const { Node* node = FindNode(key); return node ? ConstIterator(node) : End(); }
    /// Return iterator to the first actual node
    Iterator Begin() { return Iterator(GetHead()->GetNext(0)); }
    /// Return iterator to the first actual node
    ConstIterator Begin() const { return ConstIterator(GetHead()->GetNext(0)); }
    /// Return iterator to the end
    Iterator End() { return Iterator(GetTail()); }
    /// Return iterator to the end
    ConstIterator End() const { return ConstIterator(GetTail()); }
    /// Return first pair
    KeyValue& Front() { return *Begin(); }
    /// Return const first pair
    const KeyValue& Front() const { return *Begin(); }
    /// Return last pair
    const KeyValue& Back() { return *(--End()); }
    /// Return const last pair
    const KeyValue& Back() const { return *(--End()); }
    
    /// Return whether contains a key
    bool Contains(const T& key) const { return FindNode(key) != 0; }
    /// Return number of keys
    unsigned Size() const { return size_; }
    /// Return current height
    unsigned Height() const { return height_; }
    /// Return whether map is empty
    bool Empty() const { return size_ == 0; }
    
private:
    /// Return the head pointer with correct type
    Node* GetHead() const { return reinterpret_cast<Node*>(head_); }
    /// Return the tail pointer with correct type
    Node* GetTail() const { return reinterpret_cast<Node*>(tail_); }
    /// Return the fixup array with correct type
    Node** GetFix() const { return reinterpret_cast<Node**>(fix_); }
    
    /// Find a key from the map. Return null if not found
    Node* FindNode(const T& key) const
    {
        Node* i = GetHead();
        Node* tail = GetTail();
        
        for (unsigned j = height_ - 1; j < MAX_HEIGHT; --j)
        {
            for (;;)
            {
                Node* next = i->GetNext(j);
                if ((next) && (next != tail) && (key > next->pair_.first_)) 
                    i = next;
                else
                    break;
            }
        }
        
        Node* next = i->GetNext(0);
        if ((next) && (next != tail) && (next->pair_.first_ == key))
            return next;
        else
            return 0;
    }
    
    /// Insert into the map with a specific height. Zero height will randomize. Return the node
    Node* InsertNode(const Pair<T, U>& pair, unsigned height)
    {
        Node* head = GetHead();
        Node* tail = GetTail();
        Node** fix = GetFix();
        Node* i = head;
        
        for (unsigned j = height_ - 1; j < MAX_HEIGHT; --j)
        {
            for (;;)
            {
                Node* next = i->GetNext(j);
                if ((next) && (next != tail) && (pair.first_ > next->pair_.first_))
                    i = next;
                else
                    break;
            }
            fix[j] = i;
        }
        
        // Check if key already exists, in that case only modify the value
        Node* next = i->GetNext(0);
        if ((next) && (next != tail) && (next->pair_.first_ == pair.first_))
        {
            next->pair_.second_ = pair.second_;
            return next;
        }
        
        // Create new node, assign height and key
        if (!height)
            height = GetHeight();
        Node* newNode = AllocateNode(height, pair.first_);
        newNode->pair_.second_ = pair.second_;
        
        // Fix the previous link, however do not set the head node as previous
        if (i != head)
            newNode->SetPrev(i);
        if (next)
            next->SetPrev(newNode);
        
        while (newNode->height_ > height_)
            fix[height_++] = head;
        
        for (unsigned h = 0; h < newNode->height_; ++h)
        {
            newNode->SetNext(h, fix[h]->GetNext(h));
            fix[h]->SetNext(h, newNode);
        }
        
        ++size_;
        return newNode;
    }
    
    /// Allocate a node and its next pointers
    Node* AllocateNode(unsigned height, const T& key = T())
    {
        unsigned char* block = new unsigned char[sizeof(Node) + (height - 1) * sizeof(Node*)];
        Node* newNode = reinterpret_cast<Node*>(block);
        
        // Construct the pair with placement new and map the next pointers' address
        new(&newNode->pair_) KeyValue(key);
        newNode->height_ = height;
        if (height > 1)
            newNode->levels_ = reinterpret_cast<SkipListNodeBase**>(block + sizeof(Node));
        else
            newNode->levels_ = 0;
        
        return newNode;
    }
    
    /// Delete a node
    void DeleteNode(Node* node)
    {
        // Destruct the pair, then delete the memory block
        (&node->pair_)->~KeyValue();
        delete[] reinterpret_cast<unsigned char*>(node);
    }
};
