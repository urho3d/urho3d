// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

#include "../Precompiled.h"

#include "../DebugNew.h"

namespace Urho3D
{

AllocatorBlock* AllocatorReserveBlock(AllocatorBlock* allocator, unsigned nodeSize, unsigned capacity)
{
    if (!capacity)
        capacity = 1;

    auto* blockPtr = new unsigned char[sizeof(AllocatorBlock) + capacity * (sizeof(AllocatorNode) + nodeSize)];
    auto* newBlock = reinterpret_cast<AllocatorBlock*>(blockPtr);
    newBlock->nodeSize_ = nodeSize;
    newBlock->capacity_ = capacity;
    newBlock->free_ = nullptr;
    newBlock->next_ = nullptr;

    if (!allocator)
        allocator = newBlock;
    else
    {
        newBlock->next_ = allocator->next_;
        allocator->next_ = newBlock;
    }

    // Initialize the nodes. Free nodes are always chained to the first (parent) allocator
    unsigned char* nodePtr = blockPtr + sizeof(AllocatorBlock);
    auto* firstNewNode = reinterpret_cast<AllocatorNode*>(nodePtr);

    for (unsigned i = 0; i < capacity - 1; ++i)
    {
        auto* newNode = reinterpret_cast<AllocatorNode*>(nodePtr);
        newNode->next_ = reinterpret_cast<AllocatorNode*>(nodePtr + sizeof(AllocatorNode) + nodeSize);
        nodePtr += sizeof(AllocatorNode) + nodeSize;
    }
    // i == capacity - 1
    {
        auto* newNode = reinterpret_cast<AllocatorNode*>(nodePtr);
        newNode->next_ = nullptr;
    }

    allocator->free_ = firstNewNode;

    return newBlock;
}

AllocatorBlock* AllocatorInitialize(unsigned nodeSize, unsigned initialCapacity)
{
    AllocatorBlock* block = AllocatorReserveBlock(nullptr, nodeSize, initialCapacity);
    return block;
}

void AllocatorUninitialize(AllocatorBlock* allocator)
{
    while (allocator)
    {
        AllocatorBlock* next = allocator->next_;
        delete[] reinterpret_cast<unsigned char*>(allocator);
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
        unsigned newCapacity = (allocator->capacity_ + 1) >> 1u;
        AllocatorReserveBlock(allocator, allocator->nodeSize_, newCapacity);
        allocator->capacity_ += newCapacity;
    }

    // We should have new free node(s) chained
    AllocatorNode* freeNode = allocator->free_;
    void* ptr = (reinterpret_cast<unsigned char*>(freeNode)) + sizeof(AllocatorNode);
    allocator->free_ = freeNode->next_;
    freeNode->next_ = nullptr;

    return ptr;
}

void AllocatorFree(AllocatorBlock* allocator, void* ptr)
{
    if (!allocator || !ptr)
        return;

    auto* dataPtr = static_cast<unsigned char*>(ptr);
    auto* node = reinterpret_cast<AllocatorNode*>(dataPtr - sizeof(AllocatorNode));

    // Chain the node back to free nodes
    node->next_ = allocator->free_;
    allocator->free_ = node;
}

}
