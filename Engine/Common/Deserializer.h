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

#ifndef COMMON_DESERIALIZER_H
#define COMMON_DESERIALIZER_H

#include "BoundingBox.h"
#include "Rect.h"
#include "Variant.h"

//! An abstract stream for reading
class Deserializer
{
public:
    //! Construct with zero size
    Deserializer() :
        mPosition(0),
        mSize(0)
    {
    }
    
    //! Construct with a defined size
    Deserializer(unsigned size) :
        mPosition(0),
        mSize(size)
    {
    }
    
    //! Destruct
    virtual ~Deserializer();
    
    //! Read bytes from the stream
    virtual void read(void* dest, unsigned size) = 0;
    //! Set position from the beginning of the stream
    virtual unsigned seek(unsigned position) = 0;
    //! Return name of the stream
    virtual const std::string& getName() const;
    //! Return current position
    unsigned getPosition() const { return mPosition; }
    //! Return size
    unsigned getSize() const { return mSize; }
    //! Return whether the end of stream has been reached
    bool isEof() const { return mPosition == mSize; }
    
    //! Read a 32-bit integer
    int readInt();
    //! Read a 16-bit integer
    short readShort();
    //! Read an 8-bit integer
    signed char readByte();
    //! Read a 32-bit unsigned integer
    unsigned readUInt();
    //! Read a 16-bit unsigned integer
    unsigned short readUShort();
    //! Read an 8-bit unsigned integer
    unsigned char readUByte();
    //! Read a bool
    bool readBool();
    //! Read a float
    float readFloat();
    //! Read an IntRect
    IntRect readIntRect();
    //! Read an IntVector2
    IntVector2 readIntVector2();
    //! Read a Rect
    Rect readRect();
    //! Read a Vector2
    Vector2 readVector2();
    //! Read a Vector3
    Vector3 readVector3();
    //! Read a Vector3 packed into 3 x 16 bits with the specified maximum absolute range
    Vector3 readPackedVector3(float maxAbsCoord);
    //! Read a Vector4
    Vector4 readVector4();
    //! Read a Quaternion
    Quaternion readQuaternion();
    //! Read a Quaternion with each component packed in 16 bits
    Quaternion readPackedQuaternion();
    //! Read a Color
    Color readColor();
    //! Read a BoundingBox
    BoundingBox readBoundingBox();
    //! Read a null-terminated string
    std::string readString();
    //! Read a 32-bit StringHash
    StringHash readStringHash();
    //! Read a 16-bit ShortStringHash
    ShortStringHash readShortStringHash();
    //! Read a Variant
    Variant readVariant();
    //! Read a vector of Variants
    VariantVector readVariantVector();
    //! Read a map of Variants
    VariantMap readVariantMap();
    //! Read a variable-length encoded unsigned integer, which can use 29 bits maximum
    unsigned readVLE();
    
protected:
    //! Stream position
    unsigned mPosition;
    //! Stream size
    unsigned mSize;
};

#endif // COMMON_DESERIALIZER_H
