// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

#pragma once

#ifdef URHO3D_IS_BUILDING
#include "Urho3D.h"
#else
#include <Urho3D/Urho3D.h>
#endif

#include <cstddef>

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
    explicit Allocator(unsigned initialCapacity = 0) :
        allocator_(nullptr)
    {
        if (initialCapacity)
            allocator_ = AllocatorInitialize((unsigned)sizeof(T), initialCapacity);
    }

    /// Destruct.
    ~Allocator()
    {
        AllocatorUninitialize(allocator_);
    }

    /// Prevent copy construction.
    Allocator(const Allocator<T>& rhs) = delete;
    /// Prevent assignment.
    Allocator<T>& operator =(const Allocator<T>& rhs) = delete;

    /// Reserve and default-construct an object.
    T* Reserve()
    {
        if (!allocator_)
            allocator_ = AllocatorInitialize((unsigned)sizeof(T));
        auto* newObject = static_cast<T*>(AllocatorReserve(allocator_));
        new(newObject) T();

        return newObject;
    }

    /// Reserve and copy-construct an object.
    T* Reserve(const T& object)
    {
        if (!allocator_)
            allocator_ = AllocatorInitialize((unsigned)sizeof(T));
        auto* newObject = static_cast<T*>(AllocatorReserve(allocator_));
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
    /// Allocator block.
    AllocatorBlock* allocator_;
};

}
