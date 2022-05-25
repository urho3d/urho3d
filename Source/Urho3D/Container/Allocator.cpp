// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

#include "../Precompiled.h"

#include "../DebugNew.h"

namespace Urho3D
{

static AllocatorBlock* AllocatorReserveBlock(AllocatorBlock* allocator, i32 nodeSize, i32 capacity)
{
    assert(nodeSize > 0 && capacity > 0);

    u8* blockPtr = new u8[sizeof(AllocatorBlock) + capacity * (sizeof(AllocatorNode) + nodeSize)];
    AllocatorBlock* newBlock = reinterpret_cast<AllocatorBlock*>(blockPtr);
    newBlock->nodeSize_ = nodeSize;
    newBlock->capacity_ = capacity;
    newBlock->free_ = nullptr;
    newBlock->next_ = nullptr;

    if (!allocator)
    {
        allocator = newBlock;
    }
    else
    {
        newBlock->next_ = allocator->next_;
        allocator->next_ = newBlock;
    }

    // Initialize the nodes. Free nodes are always chained to the first (parent) allocator
    u8* nodePtr = blockPtr + sizeof(AllocatorBlock);
    AllocatorNode* firstNewNode = reinterpret_cast<AllocatorNode*>(nodePtr);

    for (i32 i = 0; i < capacity - 1; ++i)
    {
        AllocatorNode* newNode = reinterpret_cast<AllocatorNode*>(nodePtr);
        newNode->next_ = reinterpret_cast<AllocatorNode*>(nodePtr + sizeof(AllocatorNode) + nodeSize);
        nodePtr += sizeof(AllocatorNode) + nodeSize;
    }

    // i == capacity - 1
    {
        AllocatorNode* newNode = reinterpret_cast<AllocatorNode*>(nodePtr);
        newNode->next_ = nullptr;
    }

    allocator->free_ = firstNewNode;

    return newBlock;
}

AllocatorBlock* AllocatorInitialize(i32 nodeSize, i32 initialCapacity)
{
    return AllocatorReserveBlock(nullptr, nodeSize, initialCapacity);
}

void AllocatorUninitialize(AllocatorBlock* allocator)
{
    while (allocator)
    {
        AllocatorBlock* next = allocator->next_;
        delete[] reinterpret_cast<u8*>(allocator);
        allocator = next;
    }
}

void* AllocatorReserve(AllocatorBlock* allocator)
{
    if (!allocator)
        return nullptr;

    if (!allocator->free_)
    {
        // Free nodes have been exhausted. Allocate a new larger block
        i32 newCapacity = (allocator->capacity_ + 1) >> 1u; // * 0.5 and round up
        AllocatorReserveBlock(allocator, allocator->nodeSize_, newCapacity);
        allocator->capacity_ += newCapacity;
    }

    // We should have new free node(s) chained
    AllocatorNode* freeNode = allocator->free_;
    void* ptr = reinterpret_cast<u8*>(freeNode) + sizeof(AllocatorNode);
    allocator->free_ = freeNode->next_;
    freeNode->next_ = nullptr;

    return ptr;
}

void AllocatorFree(AllocatorBlock* allocator, void* ptr)
{
    if (!allocator || !ptr)
        return;

    u8* dataPtr = static_cast<u8*>(ptr);
    AllocatorNode* node = reinterpret_cast<AllocatorNode*>(dataPtr - sizeof(AllocatorNode));

    // Chain the node back to free nodes
    node->next_ = allocator->free_;
    allocator->free_ = node;
}

}
