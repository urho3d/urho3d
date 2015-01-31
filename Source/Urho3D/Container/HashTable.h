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

#include "../Container/Allocator.h"
#include "../Container/Vector.h"

namespace Urho3D
{

/// Hash table with fixed bucket count. Does not support iteration. Should only be used when performance is critical, as HashMap is much more user-friendly.
template <class T, unsigned U> class HashTable
{
public:
    /// Hash table node.
    struct Node
    {
        /// Construct.
        Node(unsigned hash, const T& value, Node* next) :
            hash_(hash),
            value_(value),
            next_(next)
        {
        }
        
        /// Hash value.
        unsigned hash_;
        /// Node value.
        T value_;
        /// Next node in bucket.
        Node* next_;
    };
    
    /// Construct empty.
    HashTable() :
        allocator_(0)
    {
        for (unsigned i = 0; i < U; ++i)
            ptrs_[i] = 0;
    }
    
    /// Destruct.
    ~HashTable()
    {
        Clear();
        AllocatorUninitialize(allocator_);
    }
    
    /// Insert by hash value. If value with same hash already exists, it is replaced.
    void Insert(unsigned hash, const T& value)
    {
        unsigned bucket = hash & (U - 1);
        
        if (!allocator_)
            allocator_ = AllocatorInitialize(sizeof(Node));
        
        Node* ptr = ptrs_[bucket];
        while (ptr)
        {
            if (ptr->hash_ == hash)
            {
                ptr->value_ = value;
                return;
            }
            ptr = ptr->next_;
        }
        
        Node* newNode = static_cast<Node*>(AllocatorReserve(allocator_));
        // Insert at the top of the bucket, connect to the previous top node if exists
        new(newNode) Node(hash, value, ptrs_[bucket]);
        ptrs_[bucket] = newNode;
    }
    
    /// Remove by hash value. Return true if was found and removed.
    bool Erase(unsigned hash)
    {
        unsigned bucket = hash & (U - 1);
        
        Node* ptr = ptrs_[bucket];
        while (ptr)
        {
            if (ptr->hash_ == hash)
            {
                (ptr)->~Node();
                AllocatorFree(allocator_, ptr);
                return true;
            }
            else
                ptr = ptr->next_;
        }
        
        return false;
    }
    
    /// Remove all values.
    void Clear()
    {
        for (unsigned i = 0; i < U; ++i)
        {
            Node* ptr = ptrs_[i];
            while (ptr)
            {
                Node* next = ptr->next_;
                (ptr)->~Node();
                AllocatorFree(allocator_, ptr);
                ptr = next;
            }
        }
    }
    
    /// Find by hash value. Return pointer if was found or null if not found.
    T* Find(unsigned hash) const
    {
        unsigned bucket = hash & (U - 1);
        
        Node* ptr = ptrs_[bucket];
        while (ptr)
        {
            if (ptr->hash_ == hash)
                return &ptr->value_;
            else
                ptr = ptr->next_;
        }
        
        return 0;
    }
    
    /// Return all the keys.
    PODVector<unsigned> Keys() const
    {
        PODVector<unsigned> ret;

        for (unsigned i = 0; i < U; ++i)
        {
            Node* ptr = ptrs_[i];
            while (ptr)
            {
                ret.Push(ptr->hash_);
                ptr = ptr->next_;
            }
        }

        return ret;
    }

    /// Return pointers to all values.
    PODVector<T*> Values() const
    {
        PODVector<T*> ret;
        
        for (unsigned i = 0; i < U; ++i)
        {
            Node* ptr = ptrs_[i];
            while (ptr)
            {
                ret.Push(&ptr->value_);
                ptr = ptr->next_;
            }
        }
        
        return ret;
    }
    
private:
    /// Allocator.
    AllocatorBlock* allocator_;
    /// Bucket pointers, fixed size.
    Node* ptrs_[U];
};

}
