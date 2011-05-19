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

#include "Allocator.h"

Allocator* AllocatorGetBlock(unsigned nodeSize, unsigned capacity)
{
    if (!capacity)
        capacity = 1;
    
    unsigned char* blockPtr = new unsigned char[sizeof(Allocator) + capacity * (sizeof(AllocatorNode) + nodeSize)];
    Allocator* newBlock = reinterpret_cast<Allocator*>(blockPtr);
    newBlock->nodeSize_ = nodeSize;
    newBlock->capacity_ = capacity;
    newBlock->nextBlock_ = 0;
    
    /// Initialize the nodes
    unsigned char* nodePtr = blockPtr + sizeof(Allocator);
    for (unsigned i = 0; i < capacity; ++i)
    {
        AllocatorNode* newNode = reinterpret_cast<AllocatorNode*>(nodePtr);
        AllocatorNode* nextNode = 0;
        
        if (!i)
            newBlock->firstFreeNode_ = newNode;
        if (i < capacity - 1)
            nextNode = reinterpret_cast<AllocatorNode*>(nodePtr + sizeof(AllocatorNode) + nodeSize);
        
        newNode->parentBlock_ = newBlock;
        newNode->nextFreeNode_ = nextNode;
        
        nodePtr += sizeof(AllocatorNode) + nodeSize;
    }
    
    return newBlock;
}

Allocator* AllocatorInitialize(unsigned nodeSize, unsigned initialCapacity)
{
    return AllocatorGetBlock(nodeSize, initialCapacity);
}

void AllocatorUninitialize(Allocator* block)
{
    while (block)
    {
        Allocator* next = block->nextBlock_;
        delete[] reinterpret_cast<unsigned char*>(block);
        block = next;
    }
}

void* AllocatorGet(Allocator* block)
{
    Allocator* lastBlock;
    while (block)
    {
        /// Check if a free node exists
        if (block->firstFreeNode_)
        {
            AllocatorNode* freeNode = block->firstFreeNode_;
            void* payload = reinterpret_cast<unsigned char*>(freeNode) + sizeof(Allocator*) + sizeof(AllocatorNode*);
            block->firstFreeNode_ = freeNode->nextFreeNode_;
            freeNode->nextFreeNode_ = 0;
            return payload;
        }
        /// Go to the next block
        lastBlock = block;
        block = block->nextBlock_;
    }
    /// Blocks have been exhausted. Allocate a new larger block, then return its first node
    unsigned increment = lastBlock->capacity_ >> 1;
    if (!increment)
        increment = 1;
    block = AllocatorGetBlock(lastBlock->nodeSize_, lastBlock->capacity_ + increment);
    lastBlock->nextBlock_ = block;
    
    AllocatorNode* freeNode = block->firstFreeNode_;
    void* payload = reinterpret_cast<unsigned char*>(freeNode) + sizeof(Allocator*) + sizeof(AllocatorNode*);
    block->firstFreeNode_ = freeNode->nextFreeNode_;
    freeNode->nextFreeNode_ = 0;
    return payload;
}

void AllocatorFree(void* payload)
{
    unsigned char* payloadPtr = static_cast<unsigned char*>(payload);
    AllocatorNode* node = reinterpret_cast<AllocatorNode*>(payloadPtr - sizeof(Allocator*) - sizeof(AllocatorNode*));
    Allocator* block = node->parentBlock_;
    node->nextFreeNode_ = block->firstFreeNode_;
    block->firstFreeNode_ = node;
}
