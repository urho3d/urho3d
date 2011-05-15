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

#include <cstdlib>
#include <new>

// Based on http://eternallyconfuzzled.com/tuts/datastructures/jsw_tut_skip.aspx

/// Set template class using a skip list
template <class T> class Set
{
public:
    /// Set node
    struct Node
    {
        /// Key
        T key_;
        /// Node height
        unsigned height_;
        /// Skip list pointers
        Node** next_;
    };
    
    /// Set node iterator
    class Iterator
    {
    public:
        explicit Iterator(Node* ptr) :
            ptr_(ptr)
        {
        }
        
        /// Point to the key
        const T* operator -> () const { return &ptr_->key_; }
        /// Dereference the key
        const T& operator * () const { return ptr_->key_; }
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
    
    /// Set node const iterator
    class ConstIterator
    {
    public:
        explicit ConstIterator(Node* ptr) :
            ptr_(ptr)
        {
        }
        
        /// Point to the key
        const T* operator -> () const { return &ptr_->key_; }
        /// Dereference the key
        const T& operator * () const { return ptr_->key_; }
        /// Test for equality with anoter iterator
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
    Set(unsigned maxHeight = MAX_HEIGHT) :
        maxHeight_(maxHeight < MAX_HEIGHT ? maxHeight : MAX_HEIGHT),
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
    }
    
    /// Construct from another set
    Set(const Set<T>& set) :
        maxHeight_(set.maxHeight_),
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
        
        *this = set;
    }
    
    /// Destruct
    ~Set()
    {
        Clear();
        DeleteNode(head_);
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
            Insert(*it);
            ++it;
        }
    }
    
    /// Erase a key from the set. Return true if was found and erased
    bool Erase(const T& key)
    {
        Node* i = head_;
        
        for (unsigned j = height_ - 1; j < MAX_HEIGHT; --j)
        {
            while ((i->next_[j]) && (key > i->next_[j]->key_))
                i = i->next_[j];
            fix_[j] = i;
        }
        
        // Check if key does not exist
        if ((!i->next_[0]) && (i->next_[0]->key_ != key))
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
            Erase(*current);
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
            Erase(*current);
        }
        
        return it;
    }
    
    /// Clear the set
    void Clear()
    {
        // Let the head node remain, but clear its next pointers
        Node* node = head_->next_[0];
        for (unsigned i = 0; i < height_; ++i)
            head_->next_[i] = 0;
        
        // Then remove all the key nodes
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
    /// Return iterator to the first actual node
    ConstIterator Begin() const { return ConstIterator(head_->next_[0]); }
    /// Return iterator to the end (null iterator)
    Iterator End() { return Iterator(0); }
    /// Return iterator to the end (null iterator)
    ConstIterator End() const { return ConstIterator(0); }
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
            while ((i->next_[j]) && (key > i->next_[j]->key_))
                i = i->next_[j];
        }
        
        if ((i->next_[0]) && (i->next_[0]->key_ == key))
            return i->next_[0];
        else
            return 0;
    }
    
    /// Insert into the set with a specific height. Zero height will randomize
    bool InsertNode(const T& key, unsigned height)
    {
        Node* i = head_;
        
        for (unsigned j = height_ - 1; j < MAX_HEIGHT; --j)
        {
            while ((i->next_[j]) && (key > i->next_[j]->key_))
                i = i->next_[j];
            fix_[j] = i;
        }
        
        // Check if key already exists
        if ((i->next_[0]) && (i->next_[0]->key_ == key))
            return false;
        
        // Create new node, assign height and key
        if (!height)
            height = GetHeight();
        Node* newNode = AllocateNode(height);
        newNode->key_ = key;
        
        while (newNode->height_ > height_)
            fix_[height_++] = head_;
        
        for (unsigned h = 0; h < newNode->height_; ++h)
        {
            newNode->next_[h] = fix_[h]->next_[h];
            fix_[h]->next_[h] = newNode;
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
        unsigned char* block = new unsigned char[sizeof(Node) + height * sizeof(Node*)];
        Node* newNode = reinterpret_cast<Node*>(block);
        
        // Construct the key with placement new and set the next pointers' address
        new(&newNode->key_) T();
        newNode->height_ = height;
        newNode->next_ = reinterpret_cast<Node**>(block + sizeof(Node));
        
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
