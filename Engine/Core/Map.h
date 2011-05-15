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
    struct Node
    {
        /// Key-value pair
        KeyValue pair_;
        /// Node height
        unsigned height_;
        /// Skip list pointers
        Node** next_;
    };
    
    /// Map node iterator
    class Iterator
    {
    public:
        explicit Iterator(Node* ptr) :
            ptr_(ptr)
        {
        }
        
        /// Point to the pair
        KeyValue* operator -> () const { return &ptr_->pair_; }
        /// Dereference the pair
        KeyValue& operator * () const { return ptr_->pair_; }
        /// Test for equality with another iterator
        bool operator == (const Iterator& rhs) const { return ptr_ == rhs.ptr_; }
        /// Test for inequality with another iterator
        bool operator != (const Iterator& rhs) const { return ptr_ != rhs.ptr_; }
        /// Return whether non-null
        operator bool () const { return ptr_ != 0; }
        
        /// Go to the next node, or to null if at the end
        void operator ++ ()
        {
            if (ptr_)
                ptr_ = ptr_->next_[0];
        }
        
    private:
        /// Node pointer
        Node* ptr_;
    };
    
    /// Map node const iterator
    class ConstIterator
    {
    public:
        explicit ConstIterator(Node* ptr) :
            ptr_(ptr)
        {
        }
        
        /// Point to the pair
        const KeyValue* operator -> () const { return &ptr_->pair_; }
        /// Dereference the pair
        const KeyValue& operator * () const { return ptr_->pair_; }
        /// Test for equality with another iterator
        bool operator == (const ConstIterator& rhs) const { return ptr_ == rhs.ptr_; }
        /// Test for inequality with another iterator
        bool operator != (const ConstIterator& rhs) const { return ptr_ != rhs.ptr_; }
        /// Return whether non-null
        operator bool () const { return ptr_ != 0; }
        
        /// Go to the next node, or to null if at the end
        void operator ++ ()
        {
            if (ptr_)
                ptr_ = ptr_->next_[0];
        }
        
    private:
        /// Node pointer
        Node* ptr_;
    };
    
    /// Construct empty
    Map(unsigned maxHeight = MAX_HEIGHT) :
        maxHeight_(maxHeight < MAX_HEIGHT ? maxHeight : MAX_HEIGHT),
        height_(0),
        size_(0),
        bitsLeft_(0)
    {
        // Allocate the head node and zero the next pointers
        head_ = AllocateNode(maxHeight_, T());
        for (unsigned i = 0; i < maxHeight_; ++i)
            head_->next_[i] = 0;
        
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
        // Allocate the head node and zero the next pointers
        head_ = AllocateNode(maxHeight_);
        for (unsigned i = 0; i < maxHeight_; ++i)
            head_->next_[i] = 0;
        
        // Allocate the fixup pointers
        fix_ = new Node*[maxHeight_];
        
        *this = map;
    }
    
    /// Destruct
    ~Map()
    {
        Clear();
        DeleteNode(head_);
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
        while ((it) && (it != end))
        {
            Insert(*it);
            ++it;
        }
    }
    
    /// Erase a key from the map. Return true if was found and erased
    bool Erase(const T& key)
    {
        Node* i = head_;
        
        for (unsigned j = height_ - 1; j < MAX_HEIGHT; --j)
        {
            while ((i->next_[j]) && (key > i->next_[j]->pair_.first_))
                i = i->next_[j];
            fix_[j] = i;
        }
        
        // Check if key does not exist
        if ((!i->next_[0]) && (i->next_[0]->pair_.first_ != key))
            return false;
        
        Node* toRemove = fix_[0]->next_[0];
        
        for (unsigned j = 0; j < height_; ++j)
        {
            if (fix_[j]->next_[j])
                fix_[j]->next_[j] = fix_[j]->next_[j]->next_[j];
        }
        
        while (height_ > 0)
        {
            if (head_->next_[height_ - 1])
                break;
            head_->next_[--height_] = 0;
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
        while ((it) && (it != end))
        {
            Iterator current = it++;
            Erase(current->first_);
        }
        
        return it;
    }
    
    /// Clear the map
    void Clear()
    {
        // Let the head node remain, but clear its next pointers
        Node* node = head_->next_[0];
        for (unsigned i = 0; i < height_; ++i)
            head_->next_[i] = 0;
        
        // Then remove all the nodes
        while (node)
        {
            Node* current = node;
            node = node->next_[0];
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
    /// Return iterator to the end (null iterator)
    Iterator End() { return Iterator(0); }
    /// Return const iterator to the first actual node
    ConstIterator Begin() const { return ConstIterator(head_->next_[0]); }
    /// Return const iterator to the end (null iterator)
    ConstIterator End() const { return ConstIterator(0); }
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
            while ((i->next_[j]) && (key > i->next_[j]->pair_.first_))
                i = i->next_[j];
        }
        
        if ((i->next_[0]) && (i->next_[0]->pair_.first_ == key))
            return i->next_[0];
        else
            return 0;
    }
    
    /// Insert into the map with a specific height. Zero height will randomize. Return the node
    Node* InsertNode(const Pair<T, U>& pair, unsigned height)
    {
        Node* i = head_;
        
        for (unsigned j = height_ - 1; j < MAX_HEIGHT; --j)
        {
            while ((i->next_[j]) && (pair.first_ > i->next_[j]->pair_.first_))
                i = i->next_[j];
            fix_[j] = i;
        }
        
        // Check if key already exists, in that case modify just the value
        if ((i->next_[0]) && (i->next_[0]->pair_.first_ == pair.first_))
        {
            Node* existing = i->next_[0];
            existing->pair_.second_ = pair.second_;
            return existing;
        }
        
        // Create new node, assign height and pair
        if (!height)
            height = GetHeight();
        Node* newNode = AllocateNode(height, pair.first_);
        newNode->pair_.second_ = pair.second_;
        
        while (newNode->height_ > height_)
            fix_[height_++] = head_;
        
        for (unsigned h = 0; h < newNode->height_; ++h)
        {
            newNode->next_[h] = fix_[h]->next_[h];
            fix_[h]->next_[h] = newNode;
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
        unsigned char* block = new unsigned char[sizeof(Node) + height * sizeof(Node*)];
        Node* newNode = reinterpret_cast<Node*>(block);
        
        // Construct the pair with placement new and map the next pointers' address
        new(&newNode->pair_) KeyValue(key);
        newNode->height_ = height;
        newNode->next_ = reinterpret_cast<Node**>(block + sizeof(Node));
        
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
