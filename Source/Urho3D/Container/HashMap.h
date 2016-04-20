//
// Copyright (c) 2008-2016 the Urho3D project.
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
#include "../Container/Pair.h"
#include "../Container/Sort.h"
#include "../Container/Vector.h"

#include <cassert>
#if URHO3D_CXX11
#include <initializer_list>
#endif

namespace Urho3D
{

/// Hash map template class.
template <class T, class U> class HashMap : public HashBase
{
public:
    typedef T KeyType;
    typedef U ValueType;

    /// Hash map key-value pair with const key.
    class KeyValue
    {
    public:
        /// Construct with default key.
        KeyValue() :
            first_(T())
        {
        }

        /// Construct with key and value.
        KeyValue(const T& first, const U& second) :
            first_(first),
            second_(second)
        {
        }

        /// Copy-construct.
        KeyValue(const KeyValue& value) :
            first_(value.first_),
            second_(value.second_)
        {
        }

        /// Test for equality with another pair.
        bool operator ==(const KeyValue& rhs) const { return first_ == rhs.first_ && second_ == rhs.second_; }

        /// Test for inequality with another pair.
        bool operator !=(const KeyValue& rhs) const { return first_ != rhs.first_ || second_ != rhs.second_; }

        /// Key.
        const T first_;
        /// Value.
        U second_;

    private:
        /// Prevent assignment.
        KeyValue& operator =(const KeyValue& rhs);
    };

    /// Hash map node.
    struct Node : public HashNodeBase
    {
        /// Construct undefined.
        Node()
        {
        }

        /// Construct with key and value.
        Node(const T& key, const U& value) :
            pair_(key, value)
        {
        }

        /// Key-value pair.
        KeyValue pair_;

        /// Return next node.
        Node* Next() const { return static_cast<Node*>(next_); }

        /// Return previous node.
        Node* Prev() const { return static_cast<Node*>(prev_); }

        /// Return next node in the bucket.
        Node* Down() const { return static_cast<Node*>(down_); }
    };

    /// Hash map node iterator.
    struct Iterator : public HashIteratorBase
    {
        /// Construct.
        Iterator()
        {
        }

        /// Construct with a node pointer.
        Iterator(Node* ptr) :
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

        /// Point to the pair.
        KeyValue* operator ->() const { return &(static_cast<Node*>(ptr_))->pair_; }

        /// Dereference the pair.
        KeyValue& operator *() const { return (static_cast<Node*>(ptr_))->pair_; }
    };

    /// Hash map node const iterator.
    struct ConstIterator : public HashIteratorBase
    {
        /// Construct.
        ConstIterator()
        {
        }

        /// Construct with a node pointer.
        ConstIterator(Node* ptr) :
            HashIteratorBase(ptr)
        {
        }

        /// Construct from a non-const iterator.
        ConstIterator(const Iterator& rhs) :
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

        /// Point to the pair.
        const KeyValue* operator ->() const { return &(static_cast<Node*>(ptr_))->pair_; }

        /// Dereference the pair.
        const KeyValue& operator *() const { return (static_cast<Node*>(ptr_))->pair_; }
    };

    /// Construct empty.
    HashMap()
    {
        // Reserve the tail node
        allocator_ = AllocatorInitialize((unsigned)sizeof(Node));
        head_ = tail_ = ReserveNode();
    }

    /// Construct from another hash map.
    HashMap(const HashMap<T, U>& map)
    {
        // Reserve the tail node + initial capacity according to the map's size
        allocator_ = AllocatorInitialize((unsigned)sizeof(Node), map.Size() + 1);
        head_ = tail_ = ReserveNode();
        *this = map;
    }
#if URHO3D_CXX11
    /// Aggregate initialization constructor.
    HashMap(const std::initializer_list<Pair<T, U>>& list) : HashMap()
    {
        for (auto it = list.begin(); it != list.end(); it++)
        {
            Insert(*it);
        }
    }
#endif
    /// Destruct.
    ~HashMap()
    {
        Clear();
        FreeNode(Tail());
        AllocatorUninitialize(allocator_);
        delete[] ptrs_;
    }

    /// Assign a hash map.
    HashMap& operator =(const HashMap<T, U>& rhs)
    {
        Clear();
        Insert(rhs);
        return *this;
    }

    /// Add-assign a pair.
    HashMap& operator +=(const Pair<T, U>& rhs)
    {
        Insert(rhs);
        return *this;
    }

    /// Add-assign a hash map.
    HashMap& operator +=(const HashMap<T, U>& rhs)
    {
        Insert(rhs);
        return *this;
    }

    /// Test for equality with another hash map.
    bool operator ==(const HashMap<T, U>& rhs) const
    {
        if (rhs.Size() != Size())
            return false;

        ConstIterator i = Begin();
        while (i != End())
        {
            ConstIterator j = rhs.Find(i->first_);
            if (j == rhs.End() || j->second_ != i->second_)
                return false;
            ++i;
        }

        return true;
    }

    /// Test for inequality with another hash map.
    bool operator !=(const HashMap<T, U>& rhs) const
    {
        if (rhs.Size() != Size())
            return true;

        ConstIterator i = Begin();
        while (i != End())
        {
            ConstIterator j = rhs.Find(i->first_);
            if (j == rhs.End() || j->second_ != i->second_)
                return true;
            ++i;
        }

        return false;
    }

    /// Index the map. Create a new pair if key not found.
    U& operator [](const T& key)
    {
        if (!ptrs_)
            return InsertNode(key, U(), false)->pair_.second_;

        unsigned hashKey = Hash(key);

        Node* node = FindNode(key, hashKey);
        return node ? node->pair_.second_ : InsertNode(key, U(), false)->pair_.second_;
    }

    /// Index the map. Return null if key is not found, does not create a new pair.
    U* operator [](const T& key) const
    {
        if (!ptrs_)
            return 0;

        unsigned hashKey = Hash(key);

        Node* node = FindNode(key, hashKey);
        return node ? &node->pair_.second_ : 0;
    }

#if URHO3D_CXX11
    /// Populate the map using variadic template. This handles the base case.
    HashMap& Populate(const T& key, const U& value)
    {
        this->operator [](key) = value;
        return *this;
    };
    /// Populate the map using variadic template.
    template <typename... Args> HashMap& Populate(const T& key, const U& value, Args... args)
    {
        this->operator [](key) = value;
        return Populate(args...);
    };
#endif

    /// Insert a pair. Return an iterator to it.
    Iterator Insert(const Pair<T, U>& pair)
    {
        return Iterator(InsertNode(pair.first_, pair.second_));
    }

    /// Insert a pair. Return iterator and set exists flag according to whether the key already existed.
    Iterator Insert(const Pair<T, U>& pair, bool& exists)
    {
        unsigned oldSize = Size();
        Iterator ret(InsertNode(pair.first_, pair.second_));
        exists = (Size() == oldSize);
        return ret;
    }

    /// Insert a map.
    void Insert(const HashMap<T, U>& map)
    {
        ConstIterator it = map.Begin();
        ConstIterator end = map.End();
        while (it != end)
        {
            InsertNode(it->first_, it->second_);
            ++it;
        }
    }

    /// Insert a pair by iterator. Return iterator to the value.
    Iterator Insert(const ConstIterator& it) { return Iterator(InsertNode(it->first_, it->second_)); }

    /// Insert a range by iterators.
    void Insert(const ConstIterator& start, const ConstIterator& end)
    {
        ConstIterator it = start;
        while (it != end)
            InsertNode(*it++);
    }

    /// Erase a pair by key. Return true if was found.
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

    /// Erase a pair by iterator. Return iterator to the next pair.
    Iterator Erase(const Iterator& it)
    {
        if (!ptrs_ || !it.ptr_)
            return End();

        Node* node = static_cast<Node*>(it.ptr_);
        Node* next = node->Next();

        unsigned hashKey = Hash(node->pair_.first_);

        Node* previous = 0;
        Node* current = static_cast<Node*>(Ptrs()[hashKey]);
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

    /// Clear the map.
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

    /// Sort pairs. After sorting the map can be iterated in order until new elements are inserted.
    void Sort()
    {
        unsigned numKeys = Size();
        if (!numKeys)
            return;

        Node** ptrs = new Node* [numKeys];
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
        while (!(check & 1))
            check >>= 1;
        if (check != 1)
            return false;

        AllocateBuckets(Size(), numBuckets);
        Rehash();
        return true;
    }

    /// Return iterator to the pair with key, or end iterator if not found.
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

    /// Return const iterator to the pair with key, or end iterator if not found.
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

    /// Return whether contains a pair with key.
    bool Contains(const T& key) const
    {
        if (!ptrs_)
            return false;

        unsigned hashKey = Hash(key);
        return FindNode(key, hashKey) != 0;
    }

    /// Try to copy value to output. Return true if was found.
    bool TryGetValue(const T& key, U& out)
    {
        if (!ptrs_)
            return false;
        unsigned hashKey = Hash(key);
        Node* node = FindNode(key, hashKey);
        if (node)
        {
            out = node->pair_.second_;
            return true;
        }
        else
            return false;
    }

    /// Return all the keys.
    Vector<T> Keys() const
    {
        Vector<T> result;
        result.Reserve(Size());
        for (ConstIterator i = Begin(); i != End(); ++i)
            result.Push(i->first_);
        return result;
    }

    /// Return all the values.
    Vector<U> Values() const
    {
        Vector<U> result;
        result.Reserve(Size());
        for (ConstIterator i = Begin(); i != End(); ++i)
            result.Push(i->second_);
        return result;
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
        Node* node = static_cast<Node*>(Ptrs()[hashKey]);
        while (node)
        {
            if (node->pair_.first_ == key)
                return node;
            node = node->Down();
        }

        return 0;
    }

    /// Find a node and the previous node from the buckets. Do not call if the buckets have not been allocated.
    Node* FindNode(const T& key, unsigned hashKey, Node*& previous) const
    {
        previous = 0;

        Node* node = static_cast<Node*>(Ptrs()[hashKey]);
        while (node)
        {
            if (node->pair_.first_ == key)
                return node;
            previous = node;
            node = node->Down();
        }

        return 0;
    }

    /// Insert a key and value and return either the new or existing node.
    Node* InsertNode(const T& key, const U& value, bool findExisting = true)
    {
        // If no pointers yet, allocate with minimum bucket count
        if (!ptrs_)
        {
            AllocateBuckets(Size(), MIN_BUCKETS);
            Rehash();
        }

        unsigned hashKey = Hash(key);

        if (findExisting)
        {
            // If exists, just change the value
            Node* existing = FindNode(key, hashKey);
            if (existing)
            {
                existing->pair_.second_ = value;
                return existing;
            }
        }

        Node* newNode = InsertNode(Tail(), key, value);
        newNode->down_ = Ptrs()[hashKey];
        Ptrs()[hashKey] = newNode;

        // Rehash if the maximum load factor has been exceeded
        if (Size() > NumBuckets() * MAX_LOAD_FACTOR)
        {
            AllocateBuckets(Size(), NumBuckets() << 1);
            Rehash();
        }

        return newNode;
    }

    /// Insert a node into the list. Return the new node.
    Node* InsertNode(Node* dest, const T& key, const U& value)
    {
        if (!dest)
            return 0;

        Node* newNode = ReserveNode(key, value);
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
        Node* newNode = static_cast<Node*>(AllocatorReserve(allocator_));
        new(newNode) Node();
        return newNode;
    }

    /// Reserve a node with specified key and value.
    Node* ReserveNode(const T& key, const U& value)
    {
        Node* newNode = static_cast<Node*>(AllocatorReserve(allocator_));
        new(newNode) Node(key, value);
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
        for (Iterator i = Begin(); i != End(); ++i)
        {
            Node* node = static_cast<Node*>(i.ptr_);
            unsigned hashKey = Hash(i->first_);
            node->down_ = Ptrs()[hashKey];
            Ptrs()[hashKey] = node;
        }
    }

    /// Compare two nodes.
    static bool CompareNodes(Node*& lhs, Node*& rhs) { return lhs->pair_.first_ < rhs->pair_.first_; }

    /// Compute a hash based on the key and the bucket size
    unsigned Hash(const T& key) const { return MakeHash(key) & (NumBuckets() - 1); }
};

template <class T, class U> typename Urho3D::HashMap<T, U>::ConstIterator begin(const Urho3D::HashMap<T, U>& v) { return v.Begin(); }

template <class T, class U> typename Urho3D::HashMap<T, U>::ConstIterator end(const Urho3D::HashMap<T, U>& v) { return v.End(); }

template <class T, class U> typename Urho3D::HashMap<T, U>::Iterator begin(Urho3D::HashMap<T, U>& v) { return v.Begin(); }

template <class T, class U> typename Urho3D::HashMap<T, U>::Iterator end(Urho3D::HashMap<T, U>& v) { return v.End(); }

}
