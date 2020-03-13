//
// Copyright (c) 2008-2020 the Urho3D project.
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

#include "../Container/HashBase.h"
#include "../Container/Sort.h"

#include <cassert>
#include <initializer_list>

namespace Urho3D
{

/// Hash set template class.
template <class T> class HashSet : public HashBase
{
public:
    /// Hash set node.
    struct Node : public HashNodeBase
    {
        /// Construct undefined.
        Node() = default;

        /// Construct with key.
        explicit Node(const T& key) :
            key_(key)
        {
        }

        /// Key.
        T key_;

        /// Return next node.
        Node* Next() const { return static_cast<Node*>(next_); }

        /// Return previous node.
        Node* Prev() const { return static_cast<Node*>(prev_); }

        /// Return next node in the bucket.
        Node* Down() const { return static_cast<Node*>(down_); }
    };

    /// Hash set node iterator.
    struct Iterator : public HashIteratorBase
    {
        /// Construct.
        Iterator() = default;

        /// Construct with a node pointer.
        explicit Iterator(Node* ptr) :
            HashIteratorBase(ptr)
        {
        }

        /// Preincrement the pointer.
        Iterator& operator ++()
        {
            GotoNext();
            return *this;
        }

        /// Postincrement the pointer.
        Iterator operator ++(int)
        {
            Iterator it = *this;
            GotoNext();
            return it;
        }

        /// Predecrement the pointer.
        Iterator& operator --()
        {
            GotoPrev();
            return *this;
        }

        /// Postdecrement the pointer.
        Iterator operator --(int)
        {
            Iterator it = *this;
            GotoPrev();
            return it;
        }

        /// Point to the key.
        const T* operator ->() const { return &(static_cast<Node*>(ptr_))->key_; }

        /// Dereference the key.
        const T& operator *() const { return (static_cast<Node*>(ptr_))->key_; }
    };

    /// Hash set node const iterator.
    struct ConstIterator : public HashIteratorBase
    {
        /// Construct.
        ConstIterator() = default;

        /// Construct with a node pointer.
        explicit ConstIterator(Node* ptr) :
            HashIteratorBase(ptr)
        {
        }

        /// Construct from a non-const iterator.
        ConstIterator(const Iterator& rhs) :    // NOLINT(google-explicit-constructor)
            HashIteratorBase(rhs.ptr_)
        {
        }

        /// Assign from a non-const iterator.
        ConstIterator& operator =(const Iterator& rhs)
        {
            ptr_ = rhs.ptr_;
            return *this;
        }

        /// Preincrement the pointer.
        ConstIterator& operator ++()
        {
            GotoNext();
            return *this;
        }

        /// Postincrement the pointer.
        ConstIterator operator ++(int)
        {
            ConstIterator it = *this;
            GotoNext();
            return it;
        }

        /// Predecrement the pointer.
        ConstIterator& operator --()
        {
            GotoPrev();
            return *this;
        }

        /// Postdecrement the pointer.
        ConstIterator operator --(int)
        {
            ConstIterator it = *this;
            GotoPrev();
            return it;
        }

        /// Point to the key.
        const T* operator ->() const { return &(static_cast<Node*>(ptr_))->key_; }

        /// Dereference the key.
        const T& operator *() const { return (static_cast<Node*>(ptr_))->key_; }
    };

    /// Construct empty.
    HashSet()
    {
        // Reserve the tail node
        allocator_ = AllocatorInitialize((unsigned)sizeof(Node));
        head_ = tail_ = ReserveNode();
    }

    /// Construct from another hash set.
    HashSet(const HashSet<T>& set)
    {
        // Reserve the tail node + initial capacity according to the set's size
        allocator_ = AllocatorInitialize((unsigned)sizeof(Node), set.Size() + 1);
        head_ = tail_ = ReserveNode();
        *this = set;
    }

    /// Move-construct from another hash set.
    HashSet(HashSet<T> && set) noexcept
    {
        Swap(set);
    }

    /// Aggregate initialization constructor.
    HashSet(const std::initializer_list<T>& list) : HashSet()
    {
        for (auto it = list.begin(); it != list.end(); it++)
        {
            Insert(*it);
        }
    }

    /// Destruct.
    ~HashSet()
    {
        if (allocator_)
        {
            Clear();
            FreeNode(Tail());
            AllocatorUninitialize(allocator_);
            delete[] ptrs_;
        }
    }

    /// Assign a hash set.
    HashSet& operator =(const HashSet<T>& rhs)
    {
        // In case of self-assignment do nothing
        if (&rhs != this)
        {
            Clear();
            Insert(rhs);
        }
        return *this;
    }

    /// Move-assign a hash set.
    HashSet& operator =(HashSet<T> && rhs) noexcept
    {
        assert(&rhs != this);
        Swap(rhs);
        return *this;
    }

    /// Add-assign a value.
    HashSet& operator +=(const T& rhs)
    {
        Insert(rhs);
        return *this;
    }

    /// Add-assign a hash set.
    HashSet& operator +=(const HashSet<T>& rhs)
    {
        Insert(rhs);
        return *this;
    }

    /// Test for equality with another hash set.
    bool operator ==(const HashSet<T>& rhs) const
    {
        if (rhs.Size() != Size())
            return false;

        ConstIterator it = Begin();
        while (it != End())
        {
            if (!rhs.Contains(*it))
                return false;
            ++it;
        }

        return true;
    }

    /// Test for inequality with another hash set.
    bool operator !=(const HashSet<T>& rhs) const
    {
        if (rhs.Size() != Size())
            return true;

        ConstIterator it = Begin();
        while (it != End())
        {
            if (!rhs.Contains(*it))
                return true;
            ++it;
        }

        return false;
    }

    /// Insert a key. Return an iterator to it.
    Iterator Insert(const T& key)
    {
        // If no pointers yet, allocate with minimum bucket count
        if (!ptrs_)
        {
            AllocateBuckets(Size(), MIN_BUCKETS);
            Rehash();
        }

        unsigned hashKey = Hash(key);

        Node* existing = FindNode(key, hashKey);
        if (existing)
            return Iterator(existing);

        Node* newNode = InsertNode(Tail(), key);
        newNode->down_ = Ptrs()[hashKey];
        Ptrs()[hashKey] = newNode;

        // Rehash if the maximum load factor has been exceeded
        if (Size() > NumBuckets() * MAX_LOAD_FACTOR)
        {
            AllocateBuckets(Size(), NumBuckets() << 1);
            Rehash();
        }

        return Iterator(newNode);
    }

    /// Insert a key. Return an iterator and set exists flag according to whether the key already existed.
    Iterator Insert(const T& key, bool& exists)
    {
        unsigned oldSize = Size();
        Iterator ret = Insert(key);
        exists = (Size() == oldSize);
        return ret;
    }

    /// Insert a set.
    void Insert(const HashSet<T>& set)
    {
        ConstIterator it = set.Begin();
        ConstIterator end = set.End();
        while (it != end)
            Insert(*it++);
    }

    /// Insert a key by iterator. Return iterator to the value.
    Iterator Insert(const ConstIterator& it)
    {
        return Iterator(InsertNode(*it));
    }

    /// Erase a key. Return true if was found.
    bool Erase(const T& key)
    {
        if (!ptrs_)
            return false;

        unsigned hashKey = Hash(key);

        Node* previous;
        Node* node = FindNode(key, hashKey, previous);
        if (!node)
            return false;

        if (previous)
            previous->down_ = node->down_;
        else
            Ptrs()[hashKey] = node->down_;

        EraseNode(node);
        return true;
    }

    /// Erase a key by iterator. Return iterator to the next key.
    Iterator Erase(const Iterator& it)
    {
        if (!ptrs_ || !it.ptr_)
            return End();

        auto* node = static_cast<Node*>(it.ptr_);
        Node* next = node->Next();

        unsigned hashKey = Hash(node->key_);

        Node* previous = 0;
        auto* current = static_cast<Node*>(Ptrs()[hashKey]);
        while (current && current != node)
        {
            previous = current;
            current = current->Down();
        }

        assert(current == node);

        if (previous)
            previous->down_ = node->down_;
        else
            Ptrs()[hashKey] = node->down_;

        EraseNode(node);
        return Iterator(next);
    }

    /// Clear the set.
    void Clear()
    {
        // Prevent Find() from returning anything while the map is being cleared
        ResetPtrs();

        if (Size())
        {
            for (Iterator i = Begin(); i != End();)
            {
                FreeNode(static_cast<Node*>(i++.ptr_));
                i.ptr_->prev_ = 0;
            }

            head_ = tail_;
            SetSize(0);
        }
    }

    /// Sort keys. After sorting the set can be iterated in order until new elements are inserted.
    void Sort()
    {
        unsigned numKeys = Size();
        if (!numKeys)
            return;

        auto** ptrs = new Node* [numKeys];
        Node* ptr = Head();

        for (unsigned i = 0; i < numKeys; ++i)
        {
            ptrs[i] = ptr;
            ptr = ptr->Next();
        }

        Urho3D::Sort(RandomAccessIterator<Node*>(ptrs), RandomAccessIterator<Node*>(ptrs + numKeys), CompareNodes);

        head_ = ptrs[0];
        ptrs[0]->prev_ = 0;
        for (unsigned i = 1; i < numKeys; ++i)
        {
            ptrs[i - 1]->next_ = ptrs[i];
            ptrs[i]->prev_ = ptrs[i - 1];
        }
        ptrs[numKeys - 1]->next_ = tail_;
        tail_->prev_ = ptrs[numKeys - 1];

        delete[] ptrs;
    }

    /// Rehash to a specific bucket count, which must be a power of two. Return true if successful.
    bool Rehash(unsigned numBuckets)
    {
        if (numBuckets == NumBuckets())
            return true;
        if (!numBuckets || numBuckets < Size() / MAX_LOAD_FACTOR)
            return false;

        // Check for being power of two
        unsigned check = numBuckets;
        while (!(check & 1u))
            check >>= 1;
        if (check != 1)
            return false;

        AllocateBuckets(Size(), numBuckets);
        Rehash();
        return true;
    }

    /// Return iterator to the key, or end iterator if not found.
    Iterator Find(const T& key)
    {
        if (!ptrs_)
            return End();

        unsigned hashKey = Hash(key);
        Node* node = FindNode(key, hashKey);
        if (node)
            return Iterator(node);
        else
            return End();
    }

    /// Return const iterator to the key, or end iterator if not found.
    ConstIterator Find(const T& key) const
    {
        if (!ptrs_)
            return End();

        unsigned hashKey = Hash(key);
        Node* node = FindNode(key, hashKey);
        if (node)
            return ConstIterator(node);
        else
            return End();
    }

    /// Return whether contains a key.
    bool Contains(const T& key) const
    {
        if (!ptrs_)
            return false;

        unsigned hashKey = Hash(key);
        return FindNode(key, hashKey) != 0;
    }

    /// Return iterator to the beginning.
    Iterator Begin() { return Iterator(Head()); }

    /// Return iterator to the beginning.
    ConstIterator Begin() const { return ConstIterator(Head()); }

    /// Return iterator to the end.
    Iterator End() { return Iterator(Tail()); }

    /// Return iterator to the end.
    ConstIterator End() const { return ConstIterator(Tail()); }

    /// Return first key.
    const T& Front() const { return *Begin(); }

    /// Return last key.
    const T& Back() const { return *(--End()); }

private:
    /// Return the head node.
    Node* Head() const { return static_cast<Node*>(head_); }

    /// Return the tail node.
    Node* Tail() const { return static_cast<Node*>(tail_); }

    /// Find a node from the buckets. Do not call if the buckets have not been allocated.
    Node* FindNode(const T& key, unsigned hashKey) const
    {
        auto* node = static_cast<Node*>(Ptrs()[hashKey]);
        while (node)
        {
            if (node->key_ == key)
                return node;
            node = node->Down();
        }

        return 0;
    }

    /// Find a node and the previous node from the buckets. Do not call if the buckets have not been allocated.
    Node* FindNode(const T& key, unsigned hashKey, Node*& previous) const
    {
        previous = 0;

        auto* node = static_cast<Node*>(Ptrs()[hashKey]);
        while (node)
        {
            if (node->key_ == key)
                return node;
            previous = node;
            node = node->Down();
        }

        return 0;
    }

    /// Insert a node into the list. Return the new node.
    Node* InsertNode(Node* dest, const T& key)
    {
        if (!dest)
            return 0;

        Node* newNode = ReserveNode(key);
        Node* prev = dest->Prev();
        newNode->next_ = dest;
        newNode->prev_ = prev;
        if (prev)
            prev->next_ = newNode;
        dest->prev_ = newNode;

        // Reassign the head node if necessary
        if (dest == Head())
            head_ = newNode;

        SetSize(Size() + 1);

        return newNode;
    }

    /// Erase a node from the list. Return pointer to the next element, or to the end if could not erase.
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
        SetSize(Size() - 1);

        return next;
    }

    /// Reserve a node.
    Node* ReserveNode()
    {
        auto* newNode = static_cast<Node*>(AllocatorReserve(allocator_));
        new(newNode) Node();
        return newNode;
    }

    /// Reserve a node with specified key.
    Node* ReserveNode(const T& key)
    {
        auto* newNode = static_cast<Node*>(AllocatorReserve(allocator_));
        new(newNode) Node(key);
        return newNode;
    }

    /// Free a node.
    void FreeNode(Node* node)
    {
        (node)->~Node();
        AllocatorFree(allocator_, node);
    }

    /// Rehash the buckets.
    void Rehash()
    {
        for (Iterator it = Begin(); it != End(); ++it)
        {
            auto* node = static_cast<Node*>(it.ptr_);
            unsigned hashKey = Hash(*it);
            node->down_ = Ptrs()[hashKey];
            Ptrs()[hashKey] = node;
        }
    }

    /// Compare two nodes.
    static bool CompareNodes(Node*& lhs, Node*& rhs) { return lhs->key_ < rhs->key_; }

    /// Compute a hash based on the key and the bucket size.
    unsigned Hash(const T& key) const { return MakeHash(key) & (NumBuckets() - 1); }
};

template <class T> typename Urho3D::HashSet<T>::ConstIterator begin(const Urho3D::HashSet<T>& v) { return v.Begin(); }

template <class T> typename Urho3D::HashSet<T>::ConstIterator end(const Urho3D::HashSet<T>& v) { return v.End(); }

template <class T> typename Urho3D::HashSet<T>::Iterator begin(Urho3D::HashSet<T>& v) { return v.Begin(); }

template <class T> typename Urho3D::HashSet<T>::Iterator end(Urho3D::HashSet<T>& v) { return v.End(); }

}
