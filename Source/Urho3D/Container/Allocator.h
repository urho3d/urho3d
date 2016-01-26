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

#ifdef URHO3D_IS_BUILDING
#include "Urho3D.h"
#else
#include <Urho3D/Urho3D.h>
#endif

#include <stddef.h>

namespace Urho3D
{

struct AllocatorBlock;
struct AllocatorNode;

/// %Allocator memory block.
struct AllocatorBlock
{
    /// Size of a node.
    unsigned nodeSize_;
    /// Number of nodes in this block.
    unsigned capacity_;
    /// First free node.
    AllocatorNode* free_;
    /// Next allocator block.
    AllocatorBlock* next_;
    /// Nodes follow.
};

/// %Allocator node.
struct AllocatorNode
{
    /// Next free node.
    AllocatorNode* next_;
    /// Data follows.
};

/// Initialize a fixed-size allocator with the node size and initial capacity.
URHO3D_API AllocatorBlock* AllocatorInitialize(unsigned nodeSize, unsigned initialCapacity = 1);
/// Uninitialize a fixed-size allocator. Frees all blocks in the chain.
URHO3D_API void AllocatorUninitialize(AllocatorBlock* allocator);
/// Reserve a node. Creates a new block if necessary.
URHO3D_API void* AllocatorReserve(AllocatorBlock* allocator);
/// Free a node. Does not free any blocks.
URHO3D_API void AllocatorFree(AllocatorBlock* allocator, void* ptr);

/// %Allocator template class. Allocates objects of a specific class.
template <class T> class Allocator
{
public:
    /// Construct.
    Allocator(unsigned initialCapacity = 0) :
        allocator_(0)
    {
        if (initialCapacity)
            allocator_ = AllocatorInitialize((unsigned)sizeof(T), initialCapacity);
    }

    /// Destruct.
    ~Allocator()
    {
        AllocatorUninitialize(allocator_);
    }

    /// Reserve and default-construct an object.
    T* Reserve()
    {
        if (!allocator_)
            allocator_ = AllocatorInitialize((unsigned)sizeof(T));
        T* newObject = static_cast<T*>(AllocatorReserve(allocator_));
        new(newObject) T();

        return newObject;
    }

    /// Reserve and copy-construct an object.
    T* Reserve(const T& object)
    {
        if (!allocator_)
            allocator_ = AllocatorInitialize((unsigned)sizeof(T));
        T* newObject = static_cast<T*>(AllocatorReserve(allocator_));
        new(newObject) T(object);

        return newObject;
    }

    /// Destruct and free an object.
    void Free(T* object)
    {
        (object)->~T();
        AllocatorFree(allocator_, object);
    }

private:
    /// Prevent copy construction.
    Allocator(const Allocator<T>& rhs);
    /// Prevent assignment.
    Allocator<T>& operator =(const Allocator<T>& rhs);

    /// Allocator block.
    AllocatorBlock* allocator_;
};

}
