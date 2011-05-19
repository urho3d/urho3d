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

#include <new>

/// Linked list template class
template <class T> class List : public ListBase
{
public:
    /// List node
    struct Node : public ListNodeBase
    {
        /// Construct undefined
        Node()
        {
        }
        
        /// Construct with value
        Node(const T& value) :
            value_(value)
        {
        }
        
        /// Node value
        T value_;
        
        /// Return next node
        Node* GetNext() const { return static_cast<Node*>(next_); }
        
        /// Return previous node
        Node* GetPrev() { return static_cast<Node*>(prev_); }
    };
    
    /// List node iterator
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
        
        /// Point to the node value
        T* operator -> () const { return &(static_cast<Node*>(ptr_))->value_; }
        /// Dereference the node value
        T& operator * () const { return (static_cast<Node*>(ptr_))->value_; }
    };
    
    /// List node const iterator
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
        
        /// Point to the node value
        const T* operator -> () const { return &(static_cast<Node*>(ptr_))->value_; }
        /// Dereference the node value
        const T& operator * () const { return (static_cast<Node*>(ptr_))->value_; }
    };

    /// Construct empty
    List() :
        ListBase()
    {
        // Allocate and link the head and tail nodes
        AllocatorInitialize(sizeof(Node), 2);
        head_ = AllocateNode();
        tail_ = AllocateNode();
        Node* head = GetHead();
        Node* tail = GetTail();
        head->next_ = tail;
        tail->prev_ = head;
    }
    
    /// Construct from another list
    List(const List<T>& list) :
        ListBase()
    {
        // Allocate and link the head and tail nodes
        AllocatorInitialize(sizeof(Node), list.Size() + 2);
        head_ = AllocateNode();
        tail_ = AllocateNode();
        Node* head = GetHead();
        Node* tail = GetTail();
        head->next_ = tail;
        tail->prev_ = head;
        
        // Then assign the other list
        *this = list;
    }
    
    /// Destruct
    ~List()
    {
        Clear();
        FreeNode(GetHead());
        FreeNode(GetTail());
        AllocatorUninitialize(allocator_);
    }
    
    /// Assign from another list
    List& operator = (const List<T>& rhs)
    {
        // Clear, then insert the nodes of the other list
        Clear();
        Insert(End(), rhs.Begin(), rhs.End());
        
        return *this;
    }
    
    /// Add-assign a value
    List& operator += (const T& rhs)
    {
        Push(rhs);
        return *this;
    }
    
    /// Add-assign a list
    List& operator += (const List<T>& rhs)
    {
        Insert(End(), rhs.Begin(), rhs.End());
        return *this;
    }
    
    /// Test for equality with another list
    bool operator == (const List<T>& rhs) const
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
    
    /// Test for inequality with another list
    bool operator != (const List<T>& rhs) const
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
    
    /// Insert a value at the end
    void Push(const T& value)
    {
        InsertNode(GetTail(), value);
    }
    
    /// Insert a value into the list
    void Insert(const Iterator& dest, const T& value)
    {
        InsertNode(static_cast<Node*>(dest.ptr_), value);
    }
    
    /// Insert a range by iterators
    void Insert(const Iterator& dest, const Iterator& start, const Iterator& end)
    {
        Node* destNode = static_cast<Node*>(dest.ptr_);
        Iterator it = start;
        while (it != end)
        {
            Iterator current = it++;
            InsertNode(destNode, *it);
            // Break if the iterator got stuck
            if (it == current)
                break;
        }
    }
    
    /// Erase the last node
    void Pop()
    {
        if (size_)
            Erase(End() - 1);
    }
    
    /// Erase a node from the list. Return an iterator to the next element
    Iterator Erase(Iterator it)
    {
        Iterator current = it++;
        EraseNode(static_cast<Node*>(current.ptr_));
        
        return it;
    }
    
    /// Erase a range of nodes from the list. Return an iterator to the next element
    Iterator Erase(const Iterator& start, const Iterator& end)
    {
        Iterator it = start;
        while (it != end)
        {
            Iterator current = it++;
            // Break if the iterator got stuck
            if (it == current)
                break;
            EraseNode(static_cast<Node*>(current.ptr_));
        }
        
        return it;
    }
    
    /// Clear the list
    void Clear()
    {
        while (size_)
            EraseNode(GetTail()->GetPrev());
    }
    
    /// Return iterator to the first actual node
    Iterator Begin() { return Iterator(GetHead()->GetNext()); }
    /// Return iterator to the first actual node
    ConstIterator Begin() const { return ConstIterator(GetHead()->GetNext()); }
    /// Return iterator to the end
    Iterator End() { return Iterator(GetTail()); }
    /// Return iterator to the end
    ConstIterator End() const { return ConstIterator(GetTail()); }
    /// Return first value
    const T& Front() const { return *Begin(); }
    /// Return last value
    const T& Back() const { return *(--End()); }
    /// Return number of value
    unsigned Size() const { return size_; }
    /// Return whether list is empty
    bool Empty() const { return size_ == 0; }
    
private:
    /// Return the head pointer with correct type
    Node* GetHead() const { return reinterpret_cast<Node*>(head_); }
    /// Return the tail pointer with correct type
    Node* GetTail() const { return reinterpret_cast<Node*>(tail_); }
    
    /// Insert a value into the list
    void InsertNode(Node* dest, const T& value)
    {
        // The head node can not be replaced
        if ((!dest) || (dest == head_))
            return;
        
        Node* newNode = AllocateNode(value);
        newNode->next_ = dest;
        newNode->prev_ = dest->prev_;
        dest->prev_ = newNode;
        ++size_;
    }
    
    /// Erase a node from the list
    void EraseNode(Node* toRemove)
    {
        // The head or tail can not be removed
        if ((!toRemove) || (toRemove == head_) || (toRemove == tail_))
            return;
        
        /// \todo Should check that the node belongs to the list
        Node* prev = toRemove->GetPrev();
        Node* next = toRemove->GetNext();
        prev->next_ = next;
        next->prev_ = prev;
        FreeNode(toRemove);
        --size_;
    }
    
    /// Allocate a node
    Node* AllocateNode()
    {
        Node* newNode = static_cast<Node*>(AllocatorGet(allocator_));
        new(newNode) Node();
        return newNode;
    }
    
    /// Allocate a node with initial value
    Node* AllocateNode(const T& value)
    {
        Node* newNode = static_cast<Node*>(AllocatorGet(allocator_));
        new(newNode) Node(value);
        return newNode;
    }
    
    /// Free a node
    void FreeNode(Node* node)
    {
        (node)->~Node();
        AllocatorFree(node);
    }
};
