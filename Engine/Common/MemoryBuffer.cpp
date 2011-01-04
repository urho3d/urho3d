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

#include "Precompiled.h"
#include "Exception.h"
#include "MemoryBuffer.h"

#include <cstring>

#include "DebugNew.h"

MemoryBuffer::MemoryBuffer(void* data, unsigned size) :
    Deserializer(size),
    mBuffer((unsigned char*)data),
    mReadOnly(false)
{
    if ((size) && (!data))
        EXCEPTION("Null MemoryBuffer source");
}

MemoryBuffer::MemoryBuffer(const void* data, unsigned size) :
    Deserializer(size),
    mBuffer((unsigned char*)data),
    mReadOnly(true)
{
    if ((size) && (!data))
        EXCEPTION("Null MemoryBuffer source");
}

void MemoryBuffer::read(void* dest, unsigned size)
{
    if (!size)
        return;
    
    if (size + mPosition > mSize)
        SAFE_EXCEPTION("Attempted to read past buffer end");
    
    unsigned char* srcPtr = &mBuffer[mPosition];
    unsigned char* destPtr = (unsigned char*)dest;
    mPosition += size;
    
    while (size >= sizeof(unsigned))
    {
        *((unsigned*)destPtr) = *((unsigned*)srcPtr);
        srcPtr += sizeof(unsigned);
        destPtr += sizeof(unsigned);
        size -= sizeof(unsigned);
    }
    if (size & sizeof(unsigned short))
    {
        *((unsigned short*)destPtr) = *((unsigned short*)srcPtr);
        srcPtr += sizeof(unsigned short);
        destPtr += sizeof(unsigned short);
    }
    if (size & 1)
        *destPtr = *srcPtr;
}

unsigned MemoryBuffer::seek(unsigned position)
{
    if (position > mSize)
        position = mSize;
    
    mPosition = position;
    
    return mPosition;
}

void MemoryBuffer::write(const void* data, unsigned size)
{
    if (!size)
        return;
    
    if (mReadOnly)
        SAFE_EXCEPTION("Buffer is read only");
    if (size + mPosition > mSize)
        SAFE_EXCEPTION("Attempted to write past buffer end");
    
    unsigned char* srcPtr = (unsigned char*)data;
    unsigned char* destPtr = &mBuffer[mPosition];
    mPosition += size;
    
    while (size >= sizeof(unsigned))
    {
        *((unsigned*)destPtr) = *((unsigned*)srcPtr);
        srcPtr += sizeof(unsigned);
        destPtr += sizeof(unsigned);
        size -= sizeof(unsigned);
    }
    if (size & sizeof(unsigned short))
    {
        *((unsigned short*)destPtr) = *((unsigned short*)srcPtr);
        srcPtr += sizeof(unsigned short);
        destPtr += sizeof(unsigned short);
    }
    if (size & 1)
        *destPtr = *srcPtr;
}
