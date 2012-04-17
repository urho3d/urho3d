//
// Urho3D Engine
// Copyright (c) 2008-2012 Lasse Öörni
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

#include "TreeBase.h"

// Based on Red Black Trees by Julienne Walker
// http://eternallyconfuzzled.com/tuts/datastructures/jsw_tut_rbtree.aspx

/// %Set template class using a red-black tree.
template <class T> class Set : public TreeBase
{
public:
    /// %Set node.
    struct Node : public TreeNodeBase
    {
        // Construct undefined.
        Node()
        {
        }
        
        // Construct with key.
        Node(const T& key) :
            key_(key)
        {
        }
        
        /// Key.
        T key_;
        
        /// Return parent node.
        Node* Parent() const { return static_cast<Node*>(parent_); }
        /// Return the left or right child.
        Node* Child(unsigned dir) const { return static_cast<Node*>(link_[dir]); }
    };
    
    /// %Set iterator.
    class Iterator : public TreeIteratorBase
    {
    public:
        /// Construct.
        Iterator()
        {
        }
        
        /// Construct with a node pointer.
        Iterator(Node* ptr) :
            TreeIteratorBase(ptr)
        {
        }
        
        /// Preincrement the pointer.
        Iterator& operator ++ () { GotoNext(); return *this; }
        /// Postincrement the pointer.
        Iterator operator ++ (int) { Iterator it = *this; GotoNext(); return it; }
        /// Predecrement the pointer.
        Iterator& operator -- () { GotoPrev(); return *this; }
        /// Postdecrement the pointer.
        Iterator operator -- (int) { Iterator it = *this; GotoPrev(); return it; }
        
        /// Point to the key.
        const T* operator -> () const { return &(static_cast<Node*>(ptr_))->key_; }
        /// Dereference the key.
        const T& operator * () const { return (static_cast<Node*>(ptr_))->key_; }
    };
    
    /// %Set const iterator.
    class ConstIterator : public TreeIteratorBase
    {
    public:
        /// Construct.
        ConstIterator()
        {
        }
        
        /// Construct with a node pointer.
        ConstIterator(Node* ptr) :
            TreeIteratorBase(ptr)
        {
        }
        
        // Construct from a non-const iterator.
        ConstIterator(const Iterator& it) :
            TreeIteratorBase(it.ptr_)
        {
        }
        
        /// Assign from a non-const iterator.
        ConstIterator& operator = (const Iterator& rhs) { ptr_ = rhs.ptr_; return *this; }
        /// Preincrement the pointer.
        ConstIterator& operator ++ () { GotoNext(); return *this; }
        /// Postincrement the pointer.
        ConstIterator operator ++ (int) { ConstIterator it = *this; GotoNext(); return it; }
        /// Predecrement the pointer.
        ConstIterator& operator -- () { GotoPrev(); return *this; }
        /// Postdecrement the pointer.
        ConstIterator operator -- (int) { ConstIterator it = *this; GotoPrev(); return it; }
        
        /// Point to the key.
        const T* operator -> () const { return &(static_cast<Node*>(ptr_))->key_; }
        /// Dereference the key.
        const T& operator * () const { return (static_cast<Node*>(ptr_))->key_; }
    };
    
    /// Construct empty.
    Set()
    {
    }
    
    /// Construct from another set.
    Set(const Set<T>& set)
    {
        allocator_ = AllocatorInitialize(sizeof(Node), set.Size() + 1);
        *this = set;
    }
    
    /// Destruct.
    ~Set()
    {
        Clear();
        
        if (head_)
        {
            FreeNode(reinterpret_cast<Node*>(head_));
            head_ = 0;
        }
        
        AllocatorUninitialize(allocator_);
    }
    
    /// Assign a set.
    Set& operator = (const Set<T>& set)
    {
        Clear();
        Insert(set);
        
        return *this;
    }
    
    /// Add-assign a value.
    Set& operator += (const T& rhs)
    {
        Insert(rhs);
        return *this;
    }
    
    /// Add-assign a set.
    Set& operator += (const Set<T>& rhs)
    {
        Insert(rhs);
        return *this;
    }
    
    /// Test for equality with another set.
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
    
    /// Test for inequality with another set.
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
    
    /// Clear the set.
    void Clear()
    {
        Node* root = Root();
        if (!root)
            return;
        
        EraseNodes(root);
        head_->parent_ = 0;
    }
    
    /// Insert a key. Return iterator to the value.
    Iterator Insert(const T& key) { return Iterator(InsertNode(key)); }
    /// Insert a set.
    void Insert(const Set<T>& set) { Insert(set.Begin(), set.End()); }
    /// Insert a key by iterator. Return iterator to the value.
    Iterator Insert(const ConstIterator& it) { return Iterator(InsertNode(*it)); }
    
    /// Insert a range by iterators.
    void Insert(const ConstIterator& start, const ConstIterator& end)
    {
        ConstIterator it = start;
        while (it != end)
            InsertNode(*it++);
    }
    
    /// Erase a key. Return true if was found.
    bool Erase(const T& key) { return EraseNode(key); }
    /// Erase a key by iterator.
    void Erase(const Iterator& it) { EraseNode(*it); }
    
    /// Erase a range by iterators.
    void Erase(const Iterator& start, const Iterator& end)
    {
        Iterator it = start;
        while (it != end)
        {
            Iterator current = it++;
            Erase(current);
        }
    }
    
    /// Return whether contains a key.
    bool Contains(const T& key) const { return FindNode(key) != 0; }
    /// Return iterator to the node with key, or end iterator if not found.
    Iterator Find(const T& key) { Node* node = FindNode(key); return node ? Iterator(node) : End(); }
    /// Return const iterator to the node with key, or null iterator if not found.
    ConstIterator Find(const T& key) const { Node* node = FindNode(key); return node ? ConstIterator(node) : End(); }
    /// Return iterator to the beginning.
    Iterator Begin() { return Iterator(FindFirst()); }
    /// Return const iterator to the beginning.
    ConstIterator Begin() const { return ConstIterator(FindFirst()); }
    /// Return iterator to the end.
    Iterator End() { return ++Iterator(FindLast()); }
    /// Return const iterator to the end.
    ConstIterator End() const { return ++ConstIterator(FindLast()); }
    /// Return first key.
    const T& Front() { return FindFirst()->key_; }
    /// Return last key.
    const T& Back() { return FindLast()->key_; }
    /// Return number of keys.
    unsigned Size() const { return size_; }
    /// Return whether set is empty.
    bool Empty() const { return size_ == 0; }
    
private:
    /// Return the root node, or 0 if empty.
    Node* Root() const { return head_ ? reinterpret_cast<Node*>(head_->parent_) : 0; }
    
    /// Find the node with smallest key.
    Node* FindFirst() const
    {
        Node* node = Root();
        if (!node)
            return 0;
        
        // Search if not cached
        Node*& first = reinterpret_cast<Node*&>(head_->link_[0]);
        if (!first)
        {
            while (node && node->link_[0])
                node = node->Child(0);
            first = node;
        }
        
        return first;
    }
    
    /// Find the node with largest key.
    Node* FindLast() const
    {
        Node* node = Root();
        if (!node)
            return 0;
        
        // Search if not cached
        Node*& last = reinterpret_cast<Node*&>(head_->link_[1]);
        if (!last)
        {
            while (node && node->link_[1])
                node = node->Child(1);
            last = node;
        }
        
        return last;
    }
    
    /// Find a node with key. Return null if not found.
    Node* FindNode(const T& key) const
    {
        Node* node = Root();
        while (node)
        {
            if (node->key_ == key)
                return node;
            else
                node = node->Child(node->key_ < key);
        }
        return 0;
    }
    
    /// Insert a node and return a pointer to it.
    Node* InsertNode(const T& key)
    {
        Node* ret = 0;
        
        if (!allocator_)
            allocator_ = AllocatorInitialize(sizeof(Node));
        if (!head_)
            head_ = ReserveNode();
        
        if (!head_->parent_)
        {
            head_->parent_ = ret = ReserveNode(key);
            head_->link_[0] = head_->parent_;
            head_->link_[1] = head_->parent_;
            ++size_;
        }
        else
        {
            Node h;
            Node* g;
            Node* t;
            Node* p;
            Node* q;
            
            unsigned dir = 0;
            unsigned last = 0;
            
            t = &h;
            g = p = 0;
            q = reinterpret_cast<Node*>(head_->parent_);
            t->SetChild(1, q);
            
            for (;;)
            {
                if (!q)
                {
                    p->SetChild(dir, q = ret = ReserveNode(key));
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
                q = q->Child(dir);
            }
            
            head_->parent_ = h.Child(1);
            
            // Invalidate cached first and last nodes
            head_->link_[0] = 0;
            head_->link_[1] = 0;
        }
        
        head_->parent_->isRed_ = false;
        head_->parent_->parent_ = 0;
        
        return ret;
    }
    
    /// Erase a node. Return true if was erased.
    bool EraseNode(const T& key)
    {
        if (!head_ || !head_->parent_)
            return false;
        
        Node h;
        Node* q;
        Node* p;
        Node* g;
        Node* f;
        unsigned dir = 1;
        bool removed = false;
        
        q = &h;
        f = g = p = 0;
        q->SetChild(1, head_->parent_);
        
        while (q->link_[dir])
        {
            unsigned last = dir;
            g = p;
            p = q;
            q = q->Child(dir);
            dir = q->key_ < key;
            
            if (q->key_ == key)
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
            f->key_ = q->key_;
            p->SetChild(p->link_[1] == q, q->link_[q->link_[0] == 0]);
            FreeNode(q);
            --size_;
            removed = true;
        }
        
        head_->parent_ = h.Child(1);
        if (head_->parent_)
        {
            head_->parent_->isRed_ = false;
            head_->parent_->parent_ = 0;
        }
        
        // Invalidate cached first and last nodes
        head_->link_[0] = 0;
        head_->link_[1] = 0;
        
        return removed;
    }
    
    /// Erase the nodes recursively.
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
    
    /// Reserve a node.
    Node* ReserveNode()
    {
        Node* newNode = static_cast<Node*>(AllocatorReserve(allocator_));
        new(newNode) Node();
        return newNode;
    }
    
    /// Reserve a node with specified key.
    Node* ReserveNode(const T& key)
    {
        Node* newNode = static_cast<Node*>(AllocatorReserve(allocator_));
        new(newNode) Node(key);
        return newNode;
    }
    
    /// Free a node.
    void FreeNode(Node* node)
    {
        (node)->~Node();
        AllocatorFree(allocator_, node);
    }
};
