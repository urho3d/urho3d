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

// Based on http://eternallyconfuzzled.com/tuts/datastructures/jsw_tut_rbtree.aspx

/// Set template class using a red-black tree
template <class T> class Set : public TreeBase
{
public:
    /// Set node
    struct Node : public TreeNodeBase
    {
        // Construct undefined
        Node()
        {
        }
        
        // Construct with key
        Node(const T& key) :
            key_(key)
        {
        }
        
        /// Key
        T key_;
        
        /// Return parent node
        Node* GetParent() const { return static_cast<Node*>(parent_); }
        /// Return the left or right child
        Node* GetChild(unsigned dir) const { return static_cast<Node*>(link_[dir]); }
    };
    
    /// Set node iterator
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
        
        /// Point to the key
        const T* operator -> () const { return &(static_cast<Node*>(ptr_))->key_; }
        /// Dereference the key
        const T& operator * () const { return (static_cast<Node*>(ptr_))->key_; }
    };
    
    /// Set node const iterator
    class ConstIterator : public TreeIteratorBase
    {
    public:
        // Construct
        ConstIterator(Node* ptr) :
            TreeIteratorBase(ptr)
        {
        }
        
        // Construct from a non-const iterator
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
        
        /// Point to the key
        const T* operator -> () const { return &(static_cast<Node*>(ptr_))->key_; }
        /// Dereference the key
        const T& operator * () const { return (static_cast<Node*>(ptr_))->key_; }
    };
    
    /// Construct empty set
    Set()
    {
    }
    
    /// Construct with another set
    Set(const Set<T>& set)
    {
        allocator_ = AllocatorInitialize(sizeof(Node), set.Size());
        *this = set;
    }
    
    /// Destruct the set
    ~Set()
    {
        Clear();
        AllocatorUninitialize(allocator_);
    }
    
    /// Assign a set
    Set& operator = (const Set<T>& set)
    {
        Clear();
        Insert(set.Begin(), set.End());
        
        return *this;
    }
    
    /// Add-assign a value
    Set& operator += (const T& rhs)
    {
        Insert(rhs);
        return *this;
    }
    
    /// Add-assign a set
    Set& operator += (const Set<T>& rhs)
    {
        Insert(rhs.Begin(), rhs.End());
        return *this;
    }
    
    /// Test for equality with another set
    bool operator == (const Set<T>& rhs) const
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
    
    /// Test for inequality with another set
    bool operator != (const Set<T>& rhs) const
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
    
    /// Clear the set
    void Clear()
    {
        Node* root = GetRoot();
        if (!root)
            return;
        EraseNodes(root);
        root_ = 0;
    }
    
    /// Insert a key. Return iterator to the value
    Iterator Insert(const T& key)
    {
        return Iterator(InsertNode(key));
    }
    
    /// Insert a set
    void Insert(const Set<T>& set)
    {
        Insert(set.Begin(), set.End());
    }
    
    /// Insert a key by iterator. Return iterator to the value
    Iterator Insert(const ConstIterator& it)
    {
        return Iterator(InsertNode(*it));
    }
    
    /// Insert by a range of iterators
    void Insert(const ConstIterator& begin, const ConstIterator& end)
    {
        ConstIterator it = begin;
        while (it != end)
            InsertNode(*it++);
    }
    
    /// Erase a key. Return true if was found
    bool Erase(const T& key)
    {
        return EraseNode(key);
    }
    
    /// Erase a key by iterator. Return true if was found
    bool Erase(const Iterator& it)
    {
        return EraseNode(*it);
    }
    
    /// Return whether contains a key
    bool Contains(const T& key)
    {
        return FindNode(key) != 0;
    }
    
    /// Return iterator to the node with key, or end iterator if not found
    Iterator Find(const T& key) { Node* node = FindNode(key); return node ? Iterator(node) : End(); }
    /// Return const iterator to the node with key, or null iterator if not found
    ConstIterator Find(const T& key) const { Node* node = FindNode(key); return node ? ConstIterator(node) : End(); }
    /// Return iterator to the beginning
    Iterator Begin() { return Iterator(FindFirst()); }
    /// Return const iterator to the beginning
    ConstIterator Begin() const { return ConstIterator(FindFirst()); }
    /// Return iterator to the end
    Iterator End() { return ++Iterator(FindLast()); }
    /// Return const iterator to the end
    ConstIterator End() const { return ++ConstIterator(FindLast()); }
    /// Return first key
    const T& Front() { return FindFirst()->key_; }
    /// Return last key
    const T& Back() { return FindLast()->key_; }
    /// Return number of keys
    unsigned Size() const { return size_; }
    /// Return whether the set is empty
    bool Empty() const { return size_ == 0; }
    
private:
    /// Return the root pointer with correct type
    Node* GetRoot() const { return reinterpret_cast<Node*>(root_); }
    
    /// Find the node with smallest key
    Node* FindFirst() const
    {
        Node* node = GetRoot();
        while ((node) && (node->link_[0]))
            node = node->GetChild(0);
        return node;
    }
    
    /// Find the node with largest key
    Node* FindLast() const
    {
        Node* node = GetRoot();
        while ((node) && (node->link_[1]))
            node = node->GetChild(1);
        return node;
    }
    
    /// Find a node with key. Return null if not found
    Node* FindNode(const T& key) const
    {
        Node* node = GetRoot();
        while (node)
        {
            if (node->key_ == key)
                return node;
            else
                node = node->GetChild(node->key_ < key);
        }
        return 0;
    }
    
    /// Insert a node and return a pointer to it
    Node* InsertNode(const T& key)
    {
        Node* ret = 0;
        
        if (!root_)
        {
            root_ = ret = AllocateNode(key);
            ++size_;
        }
        else
        {
            Node head;
            Node* g, * t, * p, * q;
            
            unsigned dir = 0;
            unsigned last;
            
            t = &head;
            g = p = 0;
            q = GetRoot();
            t->SetChild(1, GetRoot());
            
            for (;;)
            {
                if (!q)
                {
                    p->SetChild(dir, q = ret = AllocateNode(key));
                    ++size_;
                }
                else if ((isRed(q->link_[0])) && (isRed(q->link_[1])))
                {
                    q->isRed_ = true;
                    q->link_[0]->isRed_ = false;
                    q->link_[1]->isRed_ = false;
                }
                
                if ((isRed(q)) && (isRed(p)))
                {
                    unsigned dir2 = (t->link_[1] == g);
                    if (q == p->link_[last])
                        t->SetChild(dir2, RotateSingle(g, !last));
                    else
                        t->SetChild(dir2, RotateDouble(g, !last));
                }
                
                if (q->key_ == key)
                {
                    ret = q;
                    break;
                }
                
                last = dir;
                dir = q->key_ < key;
                
                if (g)
                    t = g;
                g = p;
                p = q;
                q = q->GetChild(dir);
            }
            
            root_ = head.GetChild(1);
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
        q->SetChild(1, GetRoot());
        
        while (q->link_[dir])
        {
            unsigned last = dir;
            g = p;
            p = q;
            q = q->GetChild(dir);
            dir = q->key_ < key;
            
            if (q->key_ == key)
                f = q;
             
            if ((!isRed(q)) && (!isRed(q->GetChild(dir))))
            {
                if (isRed(q->GetChild(!dir)))
                {
                    p->SetChild(last, RotateSingle(q, dir));
                    p = p->GetChild(last);
                }
                else if (!isRed(q->GetChild(!dir)))
                {
                    Node* s = p->GetChild(!last);
                    
                    if (s)
                    {
                        if ((!isRed(s->GetChild(!last))) && (!isRed(s->GetChild(last))))
                        {
                            p->isRed_ = false;
                            s->isRed_ = true;
                            q->isRed_ = true;
                        }
                        else
                        {
                            int dir2 = (g->GetChild(1) == p);
                            if (isRed(s->GetChild(last)))
                                g->SetChild(dir2, RotateDouble(p, last));
                            else if (isRed(s->GetChild(!last)))
                                g->SetChild(dir2, RotateSingle(p, last));
                            q->isRed_ = g->GetChild(dir2)->isRed_ = true;
                            g->GetChild(dir2)->GetChild(0)->isRed_ = false;
                            g->GetChild(dir2)->GetChild(1)->isRed_ = false;
                        }
                    }
                }
            }
        }
        
        if (f)
        {
            f->key_ = q->key_;
            p->SetChild(p->GetChild(1) == q, q->link_[q->GetChild(0) == 0]);
            FreeNode(q);
            --size_;
            removed = true;
        }
        
        root_ = head.GetChild(1);
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
        Node* left = node->GetChild(0);
        Node* right = node->GetChild(1);
        FreeNode(node);
        --size_;
        
        if (left)
            EraseNodes(left);
        if (right)
            EraseNodes(right);
    }
    
    /// Allocate a node
    Node* AllocateNode()
    {
        if (!allocator_)
            allocator_ = AllocatorInitialize(sizeof(Node));
        Node* newNode = static_cast<Node*>(AllocatorReserve(allocator_));
        new(newNode) Node();
        
        return newNode;
    }
    
    /// Allocate a node with specified key
    Node* AllocateNode(const T& key)
    {
        if (!allocator_)
            allocator_ = AllocatorInitialize(sizeof(Node));
        Node* newNode = static_cast<Node*>(AllocatorReserve(allocator_));
        new(newNode) Node(key);
        return newNode;
    }
    
    /// Free a node
    void FreeNode(Node* node)
    {
        (node)->~Node();
        AllocatorFree(allocator_, node);
    }
};
