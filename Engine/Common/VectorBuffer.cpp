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
#include "VectorBuffer.h"

#include <cstring>

#include "DebugNew.h"

VectorBuffer::VectorBuffer()
{
}

VectorBuffer::VectorBuffer(const std::vector<unsigned char>& data)
{
    setData(data);
}

VectorBuffer::VectorBuffer(const void* data, unsigned size)
{
    setData(data, size);
}

VectorBuffer::VectorBuffer(Deserializer& source, unsigned size)
{
    setData(source, size);
}

void VectorBuffer::read(void* dest, unsigned size)
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

unsigned VectorBuffer::seek(unsigned position)
{
    if (position > mSize)
        position = mSize;
    
    mPosition = position;
    
    return mPosition;
}

void VectorBuffer::write(const void* data, unsigned size)
{
    if (!size)
        return;
    
    if (size + mPosition > mSize)
    {
        mSize = size + mPosition;
        mBuffer.resize(mSize);
    }
    
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

void VectorBuffer::setData(const std::vector<unsigned char>& data)
{
    mBuffer = data;
    mPosition = 0;
    mSize = data.size();
}

void VectorBuffer::setData(const void* data, unsigned size)
{
    if ((!data) && (size))
        SAFE_EXCEPTION("Null VectorBuffer source");
    
    mBuffer.resize(size);
    if (size)
        memcpy(&mBuffer[0], data, size);
    
    mPosition = 0;
    mSize = size;
}

void VectorBuffer::setData(Deserializer& source, unsigned size)
{
    mBuffer.resize(size);
    if (size)
        source.read(&mBuffer[0], size);
    
    mPosition = 0;
    mSize = size;
}

void VectorBuffer::clear()
{
    mBuffer.clear();
    mPosition = 0;
    mSize = 0;
}

void VectorBuffer::resize(unsigned size)
{
    mBuffer.resize(size);
    mSize = size;
    if (mPosition > mSize)
        mPosition = mSize;
}
