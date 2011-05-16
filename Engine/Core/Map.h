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

#include "Pair.h"

#include <cstdlib>
#include <new>

// Based on http://eternallyconfuzzled.com/tuts/datastructures/jsw_tut_skip.aspx

/// Map template class using a skip list
template <class T, class U> class Map
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
        bool operator == (const Pair<T, U>& rhs) { return (first_ == rhs.first_) && (second_ == rhs.second_); }
        /// Test for inequality with another pair
        bool operator != (const Pair<T, U>& rhs) { return (first_ != rhs.first_) || (second_ != rhs.second_); }
        
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
        explicit Iterator(Node* ptr) :
            ptr_(ptr)
        {
        }
        
        /// Point to the pair
        T* operator -> () const { return &(static_cast<Node*>(ptr_))->pair_; }
        /// Dereference the pair
        T& operator * () const { return (static_cast<Node*>(ptr_))->pair_; }
    };
    
    /// Map node const iterator
    class ConstIterator : public ListIteratorBase
    {
    public:
        explicit ConstIterator(Node* ptr) :
            ptr_(ptr)
        {
        }
        
        /// Point to the pair
        const T* operator -> () const { return &(static_cast<Node*>(ptr_))->pair_; }
        /// Dereference the pair
        const T& operator * () const { return (static_cast<Node*>(ptr_))->pair_; }
    };
    
    /// Construct empty
    Map(unsigned maxHeight = MAX_HEIGHT) :
        maxHeight_(maxHeight < MAX_HEIGHT ? maxHeight : MAX_HEIGHT),
        height_(0),
        size_(0),
        bitsLeft_(0)
    {
        // Allocate the head and tail nodes and zero the next pointers
        head_ = AllocateNode(maxHeight_, T());
        tail_ = AllocateNode(maxHeight_, T());
        for (unsigned i = 0; i < maxHeight_; ++i)
        {
            head_->SetNext(i, tail_);
            tail_->SetNext(i, 0);
        }
        
        // Allocate the fixup pointers
        fix_ = new Node*[maxHeight_];
    }
    
    /// Construct from another map
    Map(const Map<T, U>& map) :
        maxHeight_(map.maxHeight_),
        height_(0),
        size_(0),
        bitsLeft_(0)
    {
        // Allocate the head and tail nodes and zero the next pointers
        head_ = AllocateNode(maxHeight_, T());
        tail_ = AllocateNode(maxHeight_, T());
        for (unsigned i = 0; i < maxHeight_; ++i)
        {
            head_->SetNext(i, tail_);
            tail_->SetNext(i, 0);
        }

        // Allocate the fixup pointers
        fix_ = new Node*[maxHeight_];
        
        // Then assign the another map
        *this = map;
    }
    
    /// Destruct
    ~Map()
    {
        Clear();
        DeleteNode(head_);
        DeleteNode(tail_);
        delete[] fix_;
    }
    
    /// Assign from another map
    Map& operator = (const Map<T, U>& rhs)
    {
        Clear();
        
        // Insert the nodes with same heights
        for (Node* i = rhs.head_->next_[0]; i; i = i->next_[0])
            InsertNode(i->pair_, i->height_);
        
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
        for (Iterator i = rhs.Begin(); i != rhs.End(); ++i)
            Insert(*i);
        
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
        Node* i = head_;
        
        for (unsigned j = height_ - 1; j < MAX_HEIGHT; --j)
        {
            for (;;)
            {
                Node* next = i->GetNext(j);
                if ((next) && (next != tail_) && (key > next->pair_.first_))
                    i = next;
                else
                    break;
            }
            fix_[j] = i;
        }
        
        // Check if key does not exist
        Node* toRemove = i->GetNext(0);
        if ((!toRemove) || (toRemove == tail_) || (toRemove->pair_.first_ != key))
            return false;
        
        // Fix the previous link. However, do not set the head node as a previous link
        Node* prev = toRemove->GetPrev();
        Node* next = toRemove->GetNext(0);
        if (next)
            next->SetPrev(prev != head_ ? prev : 0);
        
        // Fix the next links
        for (unsigned j = 0; j < height_; ++j)
        {
            Node* fixNext = fix_[j]->GetNext(j);
            if (fixNext)
                fix_[j]->SetNext(j, fixNext->GetNext(j));
        }
        
        // Check if height should be changed
        while (height_ > 0)
        {
            if (head_->GetNext(height_ - 1))
                break;
            head_->SetNext(--height_, 0);
        }
        
        DeleteNode(toRemove);
        --size_;
        return true;
    }
    
    /// Erase by an iterator. Return an iterator to the next element
    Iterator Erase(const Iterator& it)
    {
        if (it)
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
        Node* node = head_->GetNext(0);
        for (unsigned i = 0; i < maxHeight_; ++i)
        {
            head_->SetNext(i, tail_);
            tail_->SetNext(i, 0);
            tail_->SetPrev(0);
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
    
    /// Return iterator to the node with key, or null iterator if not found
    Iterator Find(const T& key) { return Iterator(FindNode(key)); }
    /// Return const iterator to the node with key, or null iterator if not found
    ConstIterator Find(const T& key) const { return ConstIterator(FindNode(key)); }
    /// Return iterator to the first actual node
    Iterator Begin() { return Iterator(head_->next_[0]); }
    /// Return iterator to the first actual node
    ConstIterator Begin() const { return ConstIterator(head_->next_[0]); }
    /// Return iterator to the end
    Iterator End() { return Iterator(tail_); }
    /// Return iterator to the end
    ConstIterator End() const { return ConstIterator(tail_); }
    /// Return whether contains a key
    bool Contains(const T& key) const { return FindNode(key) != 0; }
    /// Return number of keys
    unsigned Size() const { return size_; }
    /// Return current height
    unsigned Height() const { return height_; }
    /// Return whether map is empty
    bool Empty() const { return size_ == 0; }
    
    static const unsigned MAX_HEIGHT = 15;
    
private:
    /// Find a key from the map. Return null if not found
    Node* FindNode(const T& key) const
    {
        Node* i = head_;
        for (unsigned j = height_ - 1; j < MAX_HEIGHT; --j)
        {
            for (;;)
            {
                Node* next = i->GetNext(j);
                if ((next) && (next != tail_) && (key > next->pair_.first_)) 
                    i = next;
                else
                    break;
            }
        }
        
        Node* next = i->GetNext(0);
        if ((next) && (next != tail_) && (next->pair_.first_ == key))
            return next;
        else
            return 0;
    }
    
    /// Insert into the map with a specific height. Zero height will randomize. Return the node
    Node* InsertNode(const Pair<T, U>& pair, unsigned height)
    {
        Node* i = head_;
        
        for (unsigned j = height_ - 1; j < MAX_HEIGHT; --j)
        {
            for (;;)
            {
                Node* next = i->GetNext(j);
                if ((next) && (next != tail_) && (pair.first_ > next->pair_.first_))
                    i = next;
                else
                    break;
            }
            fix_[j] = i;
        }
        
        // Check if key already exists, in that case only modify the value
        Node* next = i->GetNext(0);
        if ((next) && (next != tail_) && (next->pair_.first_ == pair.first_))
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
        if (i != head_)
            newNode->SetPrev(i);
        if (next)
            next->SetPrev(newNode);
        
        while (newNode->height_ > height_)
            fix_[height_++] = head_;
        
        for (unsigned h = 0; h < newNode->height_; ++h)
        {
            newNode->SetNext(h, fix_[h]->GetNext(h));
            fix_[h]->SetNext(h, newNode);
        }
        
        ++size_;
        return newNode;
    }
    
    /// Generate a random height for a new node
    unsigned GetHeight()
    {
        unsigned height = 1;
        while ((height < maxHeight_) && (GetBit()))
            ++height;
        
        return height;
    }
    
    /// Return a random true/false result
    bool GetBit()
    {
        if (!bitsLeft_)
        {
            random_ = rand();
            bitsLeft_ = 15;
        }
        
        bool ret = (random_ & 1) != 0;
        random_ >>= 1;
        --bitsLeft_;
        
        return ret;
    }
    
    /// Allocate a node and its next pointers
    Node* AllocateNode(unsigned height, const T& key)
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
    
    /// Head node pointer
    Node* head_;
    /// Tail node pointer
    Node* tail_;
    /// Fixup pointers for insert & erase
    Node** fix_;
    /// Maximum height
    unsigned maxHeight_;
    /// Current height
    unsigned height_;
    /// Number of keys
    unsigned size_;
    /// Random bits
    unsigned short random_;
    /// Random bits remaining
    unsigned short bitsLeft_;
};
