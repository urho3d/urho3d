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

#include "Iterator.h"

#include <cstdlib>
#include <new>

// Based on http://eternallyconfuzzled.com/tuts/datastructures/jsw_tut_skip.aspx

/// Set template class using a skip list
template <class T> class Set
{
public:
    /// Set node
    struct Node : public SkipListNodeBase
    {
        /// Key
        T key_;
        
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
    
    /// Set node iterator
    class Iterator : public ListIteratorBase
    {
    public:
        explicit Iterator(Node* ptr) :
            ptr_(ptr)
        {
        }
        
        /// Point to the key
        const T* operator -> () const { return &(static_cast<Node*>(ptr_))->key_; }
        /// Dereference the key
        const T& operator * () const { return (static_cast<Node*>(ptr_))->key_; }
    };
    
    /// Set node const iterator
    class ConstIterator : public ListIteratorBase
    {
    public:
        explicit ConstIterator(Node* ptr) :
            ptr_(ptr)
        {
        }
        
        /// Point to the key
        const T* operator -> () const { return &(static_cast<Node*>(ptr_))->key_; }
        /// Dereference the key
        const T& operator * () const { return (static_cast<Node*>(ptr_))->key_; }
    };

    /// Construct empty
    Set(unsigned maxHeight = MAX_HEIGHT) :
        maxHeight_(maxHeight < MAX_HEIGHT ? maxHeight : MAX_HEIGHT),
        height_(0),
        size_(0),
        bitsLeft_(0)
    {
        // Allocate the head and tail nodes and zero the next pointers
        head_ = AllocateNode(maxHeight_);
        tail_ = AllocateNode(maxHeight_);
        for (unsigned i = 0; i < maxHeight_; ++i)
        {
            head_->SetNext(i, tail_);
            tail_->SetNext(i, 0);
        }
        
        // Allocate the fixup pointers
        fix_ = new Node*[maxHeight_];
    }
    
    /// Construct from another set
    Set(const Set<T>& set) :
        maxHeight_(set.maxHeight_),
        height_(0),
        size_(0),
        bitsLeft_(0)
    {
        // Allocate the head and tail nodes and zero the next pointers
        head_ = AllocateNode(maxHeight_);
        tail_ = AllocateNode(maxHeight_);
        for (unsigned i = 0; i < maxHeight_; ++i)
        {
            head_->SetNext(i, tail_);
            tail_->SetNext(i, 0);
        }
        
        // Allocate the fixup pointers
        fix_ = new Node*[maxHeight_];
        
        // Then assign the another set
        *this = set;
    }
    
    /// Destruct
    ~Set()
    {
        Clear();
        DeleteNode(head_);
        DeleteNode(tail_);
        delete[] fix_;
    }
    
    /// Assign from another set
    Set& operator = (const Set<T>& rhs)
    {
        Clear();
        
        // Insert the nodes with same heights
        for (Node* i = rhs.head_->next_[0]; i; i = i->next_[0])
            InsertNode(i->key_, i->height_);
        
        return *this;
    }
    
    /// Add-assign a key
    Set& operator += (const T& rhs)
    {
        Insert(rhs);
        return *this;
    }
    
    /// Add-assign a set
    Set& operator += (const Set<T>& rhs)
    {
        for (Iterator i = rhs.Begin(); i != rhs.End(); ++i)
            Insert(*i);
        
        return *this;
    }
    
    /// Test for equality with another set
    bool operator == (const Set<T>& rhs) const
    {
        if (rhs.size_ != size_)
            return false;
        
        Iterator i = Begin();
        Iterator j = rhs.Begin();
        while (i != End())
        {
            if (*i != *j)
                return false;
            ++i;
            ++j;
        }
        
        return true;
    }
    
    /// Test for inequality with another set
    bool operator != (const Set<T>& rhs) const
    {
        if (rhs.size_ != size_)
            return true;
        
        Iterator i = Begin();
        Iterator j = rhs.Begin();
        while (i != End())
        {
            if (*i != *j)
                return true;
            ++i;
            ++j;
        }
        
        return false;
    }
    
    /// Insert into the set. Return true if did not exist already
    bool Insert(const T& key)
    {
        return InsertNode(key, 0);
    }
    
    /// Insert a range by iterators
    void Insert(const Iterator& start, const Iterator& end)
    {
        Iterator it = start;
        while ((it) && (it != end))
        {
            Iterator current = it++;
            Insert(*current);
            // Break if the iterator got stuck
            if (it == current)
                break;
        }
    }
    
    /// Erase a key from the set. Return true if was found and erased
    bool Erase(const T& key)
    {
        Node* i = head_;
        
        for (unsigned j = height_ - 1; j < MAX_HEIGHT; --j)
        {
            for (;;)
            {
                Node* next = i->GetNext(j);
                if ((next) && (next != tail_) && (key > next->key_))
                    i = next;
                else
                    break;
            }
            fix_[j] = i;
        }
        
        // Check if key does not exist
        Node* toRemove = i->GetNext(0);
        if ((!toRemove) || (toRemove == tail_) || (toRemove->key_ != key))
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
            Erase(*current);
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
            Erase(*current);
        }
        
        return it;
    }
    
    /// Clear the set
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
    /// Return whether set is empty
    bool Empty() const { return size_ == 0; }
    
    static const unsigned MAX_HEIGHT = 15;
    
private:
    /// Find a key from the set. Return null if not found
    Node* FindNode(const T& key) const
    {
        Node* i = head_;
        for (unsigned j = height_ - 1; j < MAX_HEIGHT; --j)
        {
            for (;;)
            {
                Node* next = i->GetNext(j);
                if ((next) && (next != tail_) && (key > next->key_)) 
                    i = next;
                else
                    break;
            }
        }
        
        Node* next = i->GetNext(0);
        if ((next) && (next != tail_) && (next->key_ == key))
            return next;
        else
            return 0;
    }
    
    /// Insert into the set with a specific height. Zero height will randomize
    bool InsertNode(const T& key, unsigned height)
    {
        Node* i = head_;
        
        for (unsigned j = height_ - 1; j < MAX_HEIGHT; --j)
        {
            for (;;)
            {
                Node* next = i->GetNext(j);
                if ((next) && (next != tail_) && (key > next->key_))
                    i = next;
                else
                    break;
            }
            fix_[j] = i;
        }
        
        // Check if key already exists
        Node* next = i->GetNext(0);
        if ((next) && (next != tail_) && (next->key_ == key))
            return false;
        
        // Create new node, assign height and key
        if (!height)
            height = GetHeight();
        Node* newNode = AllocateNode(height);
        newNode->key_ = key;
        
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
        return true;
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
    Node* AllocateNode(unsigned height)
    {
        unsigned char* block = new unsigned char[sizeof(Node) + (height - 1) * sizeof(Node*)];
        Node* newNode = reinterpret_cast<Node*>(block);
        
        // Construct the key with placement new and set the next pointers' address
        new(&newNode->key_) T();
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
        // Destruct the key, then delete the memory block
        (&node->key_)->~T();
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
