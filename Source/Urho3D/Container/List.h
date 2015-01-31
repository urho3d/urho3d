//
// Copyright (c) 2008-2015 the Urho3D project.
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

#include "../Container/ListBase.h"

namespace Urho3D
{

/// Doubly-linked list template class.
template <class T> class List : public ListBase
{
public:
    /// %List node.
    struct Node : public ListNodeBase
    {
        /// Construct undefined.
        Node()
        {
        }
        
        /// Construct with value.
        Node(const T& value) :
            value_(value)
        {
        }
        
        /// Node value.
        T value_;
        
        /// Return next node.
        Node* Next() const { return static_cast<Node*>(next_); }
        /// Return previous node.
        Node* Prev() { return static_cast<Node*>(prev_); }
    };
    
    /// %List iterator.
    struct Iterator : public ListIteratorBase
    {
        /// Construct.
        Iterator()
        {
        }
        
        /// Construct with a node pointer.
        explicit Iterator(Node* ptr) :
            ListIteratorBase(ptr)
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
        
        /// Point to the node value.
        T* operator -> () const { return &(static_cast<Node*>(ptr_))->value_; }
        /// Dereference the node value.
        T& operator * () const { return (static_cast<Node*>(ptr_))->value_; }
    };
    
    /// %List const iterator.
    struct ConstIterator : public ListIteratorBase
    {
        /// Construct.
        ConstIterator()
        {
        }
        
        /// Construct with a node pointer.
        explicit ConstIterator(Node* ptr) :
            ListIteratorBase(ptr)
        {
        }
        
        /// Construct from a non-const iterator.
        ConstIterator(const Iterator& rhs) :
            ListIteratorBase(rhs.ptr_)
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
        
        /// Point to the node value.
        const T* operator -> () const { return &(static_cast<Node*>(ptr_))->value_; }
        /// Dereference the node value.
        const T& operator * () const { return (static_cast<Node*>(ptr_))->value_; }
    };

    /// Construct empty.
    List()
    {
        allocator_ = AllocatorInitialize(sizeof(Node));
        head_ = tail_ = ReserveNode();
    }
    
    /// Construct from another list.
    List(const List<T>& list)
    {
        // Reserve the tail node + initial capacity according to the list's size
        allocator_ = AllocatorInitialize(sizeof(Node), list.Size() + 1);
        head_ = tail_ = ReserveNode();
        *this = list;
    }
    
    /// Destruct.
    ~List()
    {
        Clear();
        FreeNode(Tail());
        AllocatorUninitialize(allocator_);
    }
    
    /// Assign from another list.
    List& operator = (const List<T>& rhs)
    {
        // Clear, then insert the nodes of the other list
        Clear();
        Insert(End(), rhs);
        return *this;
    }
    
    /// Add-assign an element.
    List& operator += (const T& rhs)
    {
        Push(rhs);
        return *this;
    }
    
    /// Add-assign a list.
    List& operator += (const List<T>& rhs)
    {
        Insert(End(), rhs);
        return *this;
    }
    
    /// Test for equality with another list.
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
    
    /// Test for inequality with another list.
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
    
    /// Insert an element to the end.
    void Push(const T& value) { InsertNode(Tail(), value); }
    /// Insert an element to the beginning.
    void PushFront(const T& value) { InsertNode(Head(), value); }
    /// Insert an element at position.
    void Insert(const Iterator& dest, const T& value) { InsertNode(static_cast<Node*>(dest.ptr_), value); }
    
    /// Insert a list at position.
    void Insert(const Iterator& dest, const List<T>& list)
    {
        Node* destNode = static_cast<Node*>(dest.ptr_);
        ConstIterator it = list.Begin();
        ConstIterator end = list.End();
        while (it != end)
            InsertNode(destNode, *it++);
    }
    
    /// Insert elements by iterators.
    void Insert(const Iterator& dest, const ConstIterator& start, const ConstIterator& end)
    {
        Node* destNode = static_cast<Node*>(dest.ptr_);
        ConstIterator it = start;
        while (it != end)
            InsertNode(destNode, *it++);
    }
    
    /// Insert elements.
    void Insert(const Iterator& dest, const T* start, const T* end)
    {
        Node* destNode = static_cast<Node*>(dest.ptr_);
        const T* ptr = start;
        while (ptr != end)
            InsertNode(destNode, *ptr++);
    }
    
    /// Erase the last element.
    void Pop()
    {
        if (size_)
            Erase(--End());
    }
    
    /// Erase the first element.
    void PopFront()
    {
        if (size_)
            Erase(Begin());
    }
    
    /// Erase an element by iterator. Return iterator to the next element.
    Iterator Erase(Iterator it)
    {
        return Iterator(EraseNode(static_cast<Node*>(it.ptr_)));
    }
    
    /// Erase a range by iterators. Return an iterator to the next element.
    Iterator Erase(const Iterator& start, const Iterator& end)
    {
        Iterator it = start;
        while (it != end)
            it = EraseNode(static_cast<Node*>(it.ptr_));
        
        return it;
    }
    
    /// Clear the list.
    void Clear()
    {
        if (Size())
        {
            for (Iterator i = Begin(); i != End(); )
            {
                FreeNode(static_cast<Node*>(i++.ptr_));
                i.ptr_->prev_ = 0;
            }
            
            head_ = tail_;
            size_ = 0;
        }
    }
    
    /// Resize the list by removing or adding items at the end.
    void Resize(unsigned newSize)
    {
        while (size_ > newSize)
            Pop();
        
        while (size_ < newSize)
            InsertNode(Tail(), T());
    }
    
    /// Return iterator to value, or to the end if not found.
    Iterator Find(const T& value)
    {
        Iterator it = Begin();
        while (it != End() && *it != value)
            ++it;
        return it;
    }
    
    /// Return const iterator to value, or to the end if not found.
    ConstIterator Find(const T& value) const
    {
        ConstIterator it = Begin();
        while (it != End() && *it != value)
            ++it;
        return it;
    }
    
    /// Return whether contains a specific value.
    bool Contains(const T& value) const { return Find(value) != End(); }
    /// Return iterator to the first element.
    Iterator Begin() { return Iterator(Head()); }
    /// Return iterator to the first element.
    ConstIterator Begin() const { return ConstIterator(Head()); }
    /// Return iterator to the end.
    Iterator End() { return Iterator(Tail()); }
    /// Return iterator to the end.
    ConstIterator End() const { return ConstIterator(Tail()); }
    /// Return first element.
    T& Front() { return *Begin(); }
    /// Return const first element.
    const T& Front() const { return *Begin(); }
    /// Return last element.
    T& Back() { return *(--End()); }
    /// Return const last element.
    const T& Back() const { return *(--End()); }
    /// Return number of elements.
    unsigned Size() const { return size_; }
    /// Return whether list is empty.
    bool Empty() const { return size_ == 0; }
    
private:
    /// Return the head node.
    Node* Head() const { return static_cast<Node*>(head_); }
    /// Return the tail node.
    Node* Tail() const { return static_cast<Node*>(tail_); }
    
    /// Allocate and insert a node into the list.
    void InsertNode(Node* dest, const T& value)
    {
        if (!dest)
            return;
        
        Node* newNode = ReserveNode(value);
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
    }
    
    /// Erase and free a node. Return pointer to the next node, or to the end if could not erase.
    Node* EraseNode(Node* node)
    {
        // The tail node can not be removed
        if (!node || node == tail_)
            return Tail();
        
        Node* prev = node->Prev();
        Node* next = node->Next();
        if (prev)
            prev->next_ = next;
        next->prev_ = prev;
        
        // Reassign the head node if necessary
        if (node == Head())
            head_ = next;
        
        FreeNode(node);
        --size_;
        
        return next;
    }
    
    /// Reserve a node.
    Node* ReserveNode()
    {
        Node* newNode = static_cast<Node*>(AllocatorReserve(allocator_));
        new(newNode) Node();
        return newNode;
    }
    
    /// Reserve a node with initial value.
    Node* ReserveNode(const T& value)
    {
        Node* newNode = static_cast<Node*>(AllocatorReserve(allocator_));
        new(newNode) Node(value);
        return newNode;
    }
    
    /// Free a node.
    void FreeNode(Node* node)
    {
        (node)->~Node();
        AllocatorFree(allocator_, node);
    }
};

}
