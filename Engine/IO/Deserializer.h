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

#pragma once

#include "BoundingBox.h"
#include "Rect.h"
#include "Variant.h"

/// Abstract stream for reading
class Deserializer
{
public:
    /// Construct with zero size
    Deserializer();
    /// Construct with defined size
    Deserializer(unsigned size);
    /// Destruct
    virtual ~Deserializer();
    
    /// Read bytes from the stream. Return number of bytes actually read
    virtual unsigned Read(void* dest, unsigned size) = 0;
    /// Set position from the beginning of the stream
    virtual unsigned Seek(unsigned position) = 0;
    /// Return name of the stream
    virtual const std::string& GetName() const;
    /// Return current position
    unsigned GetPosition() const { return position_; }
    /// Return size
    unsigned GetSize() const { return size_; }
    /// Return whether the end of stream has been reached
    bool IsEof() const { return position_ >= size_; }
    
    /// Read a 32-bit integer
    int ReadInt();
    /// Read a 16-bit integer
    short ReadShort();
    /// Read an 8-bit integer
    signed char ReadByte();
    /// Read a 32-bit unsigned integer
    unsigned ReadUInt();
    /// Read a 16-bit unsigned integer
    unsigned short ReadUShort();
    /// Read an 8-bit unsigned integer
    unsigned char ReadUByte();
    /// Read a bool
    bool ReadBool();
    /// Read a float
    float ReadFloat();
    /// Read an IntRect
    IntRect ReadIntRect();
    /// Read an IntVector2
    IntVector2 ReadIntVector2();
    /// Read a Rect
    Rect ReadRect();
    /// Read a Vector2
    Vector2 ReadVector2();
    /// Read a Vector3
    Vector3 ReadVector3();
    /// Read a Vector3 packed into 3 x 16 bits with the specified maximum absolute range
    Vector3 ReadPackedVector3(float maxAbsCoord);
    /// Read a Vector4
    Vector4 ReadVector4();
    /// Read a Quaternion
    Quaternion ReadQuaternion();
    /// Read a Quaternion with each component packed in 16 bits
    Quaternion ReadPackedQuaternion();
    /// Read a Color
    Color ReadColor();
    /// Read a BoundingBox
    BoundingBox ReadBoundingBox();
    /// Read a null-terminated string
    std::string ReadString();
    /// Read a four-letter ID
    std::string ReadID();
    /// Read a 32-bit StringHash
    StringHash ReadStringHash();
    /// Read a 16-bit ShortStringHash
    ShortStringHash ReadShortStringHash();
    /// Read a buffer with size encoded as VLE
    std::vector<unsigned char> ReadBuffer();
    /// Read a resource reference
    ResourceRef ReadResourceRef();
    /// Read a resource reference list
    ResourceRefList ReadResourceRefList();
    /// Read a Variant
    Variant ReadVariant();
    /// Read a Variant whose type is already known
    Variant ReadVariant(VariantType type);
    /// Read a vector of Variants
    VariantVector ReadVariantVector();
    /// Read a map of Variants
    VariantMap ReadVariantMap();
    /// Read a variable-length encoded unsigned integer, which can use 29 bits maximum
    unsigned ReadVLE();
    /// Read a text line
    std::string ReadLine();
    
protected:
    /// Stream position
    unsigned position_;
    /// Stream size
    unsigned size_;
};
