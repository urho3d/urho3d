// Copyright (c) 2008-2023 the Urho3D project
// License: MIT

/// \file
/// @nobindfile

#pragma once

#ifdef URHO3D_IS_BUILDING
#include "Urho3D.h"
#else
#include <Urho3D/Urho3D.h>
#endif

#include "../Base/PrimitiveTypes.h"

#include <cstddef>

namespace Urho3D
{

struct AllocatorNode;

/// %Allocator memory block.
struct AllocatorBlock
{
    /// Size of a node.
    i32 nodeSize_;

    /// Number of nodes in this block.
    i32 capacity_;

    /// First free node.
    AllocatorNode* free_;

    /// Next allocator block.
    AllocatorBlock* next_;

    // Nodes follow
};

/// %Allocator node.
struct AllocatorNode
{
    /// Next free node.
    AllocatorNode* next_;

    // Data follows
};

/// Initialize a fixed-size allocator with the node size and initial capacity.
URHO3D_API AllocatorBlock* AllocatorInitialize(i32 nodeSize, i32 initialCapacity = 1);

/// Uninitialize a fixed-size allocator. Frees all blocks in the chain.
URHO3D_API void AllocatorUninitialize(AllocatorBlock* allocator);

/// Reserve a node. Creates a new block if necessary.
URHO3D_API void* AllocatorReserve(AllocatorBlock* allocator);

/// Free a node. Does not free any blocks.
URHO3D_API void AllocatorFree(AllocatorBlock* allocator, void* ptr);

/// %Allocator template class. Allocates objects of a specific class.
template <class T> class Allocator
{
private:
    /// Allocator block.
    AllocatorBlock* allocator_;

public:
    /// Construct.
    explicit Allocator(i32 initialCapacity = 0)
        : allocator_(nullptr)
    {
        if (initialCapacity)
            allocator_ = AllocatorInitialize((i32)sizeof(T), initialCapacity);
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
            allocator_ = AllocatorInitialize((i32)sizeof(T));

        T* newObject = static_cast<T*>(AllocatorReserve(allocator_));
        new(newObject) T();

        return newObject;
    }

    /// Reserve and copy-construct an object.
    T* Reserve(const T& object)
    {
        if (!allocator_)
            allocator_ = AllocatorInitialize((i32)sizeof(T));

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
};

}
