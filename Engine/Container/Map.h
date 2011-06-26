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
#include "TreeBase.h"

// Based on Red Black Trees by Julienne Walker
// http://eternallyconfuzzled.com/tuts/datastructures/jsw_tut_rbtree.aspx

/// Map template class using a red-black tree
template <class T, class U> class Map : public TreeBase
{
public:
    /// Map key-value pair with const key
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
    
    /// Map node
    struct Node : public TreeNodeBase
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
        
        /// Return parent node
        Node* Parent() const { return static_cast<Node*>(parent_); }
        /// Return the left or right child
        Node* Child(unsigned dir) const { return static_cast<Node*>(link_[dir]); }
    };
    
    /// Map iterator
    class Iterator : public TreeIteratorBase
    {
    public:
        // Construct
        Iterator(Node* ptr) :
            TreeIteratorBase(ptr)
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
    
    /// Map const iterator
    class ConstIterator : public TreeIteratorBase
    {
    public:
        /// Construct
        ConstIterator(Node* ptr) :
            TreeIteratorBase(ptr)
        {
        }
        
        /// Construct from a non-const iterator
        ConstIterator(const Iterator& it) :
            TreeIteratorBase(it.ptr_)
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
    
    /// Construct empty map
    Map()
    {
    }
    
    /// Construct from another map
    Map(const Map<T, U>& map)
    {
        allocator_ = AllocatorInitialize(sizeof(Node), map.Size());
        *this = map;
    }
    
    /// Destruct the map
    ~Map()
    {
        Clear();
        AllocatorUninitialize(allocator_);
    }
    
    /// Assign a map
    Map<T, U>& operator = (const Map<T, U>& rhs)
    {
        Clear();
        Insert(rhs);
        
        return *this;
    }
    
    /// Add-assign a value
    Map& operator += (const Pair<T, U>& rhs)
    {
        Insert(rhs);
        return *this;
    }
    
    /// Add-assign a map
    Map<T, U>& operator += (const Map<T, U>& rhs)
    {
        Insert(rhs);
        return *this;
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
    
    /// Index the map. Create a new pair if key not found
    U& operator [] (const T& key)
    {
        Node* node = FindNode(key);
        if (node)
            return node->pair_.second_;
        else
        {
            node = InsertNode(key, U());
            return node->pair_.second_;
        }
    }
    
    /// Clear the map
    void Clear()
    {
        Node* root = Root();
        if (!root)
            return;
        EraseNodes(root);
        root_ = 0;
    }
    
    /// Insert a pair and return iterator to it
    Iterator Insert(const Pair<T, U>& pair)
    {
        return Iterator(InsertNode(pair.first_, pair.second_));
    }
    
    /// Insert a map
    void Insert(const Map<T, U>& map)
    {
        Insert(map.Begin(), map.End());
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
        {
            InsertNode(it->first_, it->second_);
            ++it;
        }
    }
    
    /// Erase a pair by key. Return true if was found
    bool Erase(const T& key)
    {
        return EraseNode(key);
    }
    
    /// Erase a pair by iterator
    void Erase(const Iterator& it)
    {
        EraseNode(it->first_);
    }
    
    /// Erase a range by iterators
    void Erase(const Iterator& start, const Iterator& end)
    {
        Iterator it = start;
        while (it != end)
        {
            Iterator current = it++;
            Erase(current);
        }
    }
    
    /// Return whether contains a pair with key
    bool Contains(const T& key)
    {
        return FindNode(key) != 0;
    }
    
    /// Return iterator to the pair, or end iterator if not found
    Iterator Find(const T& key) { Node* node = FindNode(key); return node ? Iterator(node) : End(); }
    /// Return const iterator to the pair, or null iterator if not found
    ConstIterator Find(const T& key) const { Node* node = FindNode(key); return node ? ConstIterator(node) : End(); }
    /// Return iterator to the beginning
    Iterator Begin() { return Iterator(FindFirst()); }
    /// Return const iterator to the beginning
    ConstIterator Begin() const { return ConstIterator(FindFirst()); }
    /// Return iterator to the end
    Iterator End() { return ++Iterator(FindLast()); }
    /// Return const iterator to the end
    ConstIterator End() const { return ++ConstIterator(FindLast()); }
    /// Return first key-value pair
    KeyValue& Front() { return FindFirst()->pair_; }
    /// Return const first key-value pair
    const KeyValue& Front() const { return FindFirst()->pair_; }
    /// Return last key-value pair
    KeyValue& Back() { return FindLast()->pair_; }
    /// Return const last key-value pair
    const KeyValue& Back() const { return FindLast()->pair_; }
    /// Return number of keys
    unsigned Size() const { return size_; }
    /// Return whether the map is empty
    bool Empty() const { return size_ == 0; }
    
private:
    /// Return the root pointer with correct type
    Node* Root() const { return reinterpret_cast<Node*>(root_); }
    
    /// Find the node with smallest key
    Node* FindFirst() const
    {
        Node* node = Root();
        while (node && node->link_[0])
            node = node->Child(0);
        return node;
    }
    
    /// Find the node with largest key
    Node* FindLast() const
    {
        Node* node = Root();
        while (node && node->link_[1])
            node = node->Child(1);
        return node;
    }
    
    /// Find a node with key. Return null if not found
    Node* FindNode(const T& key) const
    {
        Node* node = Root();
        while (node)
        {
            if (node->pair_.first_ == key)
                return node;
            else
                node = node->Child(node->pair_.first_ < key);
        }
        return 0;
    }
    
    /// Insert a node and return pointer to it
    Node* InsertNode(const T& key, const U& value)
    {
        Node* ret = 0;
        
        if (!root_)
        {
            root_ = ret = ReserveNode(key, value);
            ++size_;
        }
        else
        {
            Node head;
            Node* g, * t, * p, * q;
            
            unsigned dir = 0;
            unsigned last = 0;
            
            t = &head;
            g = p = 0;
            q = Root();
            t->SetChild(1, Root());
            
            for (;;)
            {
                if (!q)
                {
                    p->SetChild(dir, q = ret = ReserveNode(key, value));
                    ++size_;
                }
                else if (IsRed(q->link_[0]) && IsRed(q->link_[1]))
                {
                    q->isRed_ = true;
                    q->link_[0]->isRed_ = false;
                    q->link_[1]->isRed_ = false;
                }
                
                if (IsRed(q) && IsRed(p))
                {
                    unsigned dir2 = (t->link_[1] == g);
                    if (q == p->link_[last])
                        t->SetChild(dir2, RotateSingle(g, !last));
                    else
                        t->SetChild(dir2, RotateDouble(g, !last));
                }
                
                if (q->pair_.first_ == key)
                {
                    ret = q;
                    ret->pair_.second_ = value;
                    break;
                }
                
                last = dir;
                dir = q->pair_.first_ < key;
                
                if (g)
                    t = g;
                g = p;
                p = q;
                q = q->Child(dir);
            }
            
            root_ = head.Child(1);
        }
        
        root_->isRed_ = false;
        root_->parent_ = 0;
        
        return ret;
    }
    
    /// Erase a node. Return true if was erased
    bool EraseNode(const T& key)
    {
        if (!root_)
            return false;
        
        Node head;
        Node* q, * p, *g;
        Node* f = 0;
        unsigned dir = 1;
        bool removed = false;
        
        q = &head;
        g = p = 0;
        q->SetChild(1, Root());
        
        while (q->link_[dir])
        {
            unsigned last = dir;
            g = p;
            p = q;
            q = q->Child(dir);
            dir = q->pair_.first_ < key;
            
            if (q->pair_.first_ == key)
                f = q;
             
            if (!IsRed(q) && !IsRed(q->link_[dir]))
            {
                if (IsRed(q->link_[!dir]))
                {
                    p->SetChild(last, RotateSingle(q, dir));
                    p = p->Child(last);
                }
                else if (!IsRed(q->link_[!dir]))
                {
                    Node* s = p->Child(!last);
                    
                    if (s)
                    {
                        if (!IsRed(s->link_[!last]) && !IsRed(s->link_[last]))
                        {
                            p->isRed_ = false;
                            s->isRed_ = true;
                            q->isRed_ = true;
                        }
                        else
                        {
                            int dir2 = (g->link_[1] == p);
                            if (IsRed(s->link_[last]))
                                g->SetChild(dir2, RotateDouble(p, last));
                            else if (IsRed(s->link_[!last]))
                                g->SetChild(dir2, RotateSingle(p, last));
                            
                            Node* t = g->Child(dir2);
                            q->isRed_ = t->isRed_ = true;
                            t->link_[0]->isRed_ = false;
                            t->link_[1]->isRed_ = false;
                        }
                    }
                }
            }
        }
        
        if (f)
        {
            const_cast<T&>(f->pair_.first_) = q->pair_.first_;
            f->pair_.second_ = q->pair_.second_;
            p->SetChild(p->Child(1) == q, q->link_[q->Child(0) == 0]);
            FreeNode(q);
            --size_;
            removed = true;
        }
        
        root_ = head.Child(1);
        if (root_)
        {
            root_->isRed_ = false;
            root_->parent_ = 0;
        }
        
        return removed;
    }
    
    /// Erase the nodes recursively
    void EraseNodes(Node* node)
    {
        Node* left = node->Child(0);
        Node* right = node->Child(1);
        FreeNode(node);
        --size_;
        
        if (left)
            EraseNodes(left);
        if (right)
            EraseNodes(right);
    }
    
    /// Reserve a node
    Node* ReserveNode()
    {
        if (!allocator_)
            allocator_ = AllocatorInitialize(sizeof(Node));
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
};
