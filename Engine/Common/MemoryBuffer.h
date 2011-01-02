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

#ifndef COMMON_MEMORYBUFFER_H
#define COMMON_MEMORYBUFFER_H

#include "Deserializer.h"
#include "Serializer.h"

#include <cstdio>

//! A memory area that can be read and written to as a stream
class MemoryBuffer : public Deserializer, public Serializer
{
public:
    //! Construct with a pointer and size
    MemoryBuffer(void* data, unsigned size);
    //! Construct as read-only with a pointer and size
    MemoryBuffer(const void* data, unsigned size);
    
    //! Read bytes from the memory area
    virtual void read(void* dest, unsigned size);
    //! Set position from the beginning of the memory area
    virtual unsigned seek(unsigned position);
    //! Write bytes to the memory area
    virtual void write(const void* data, unsigned size);
    
    //! Return memory area
    unsigned char* getData() { return mBuffer; }
    //! Return whether buffer is read-only
    bool isReadOnly() { return mReadOnly; }
    
private:
    //! Pointer to the memory area
    unsigned char* mBuffer;
    //! Read-only flag
    bool mReadOnly;
};

#endif // COMMON_MEMORYBUFFER_H
