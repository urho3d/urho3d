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

#ifndef COMMON_SERIALIZER_H
#define COMMON_SERIALIZER_H

#include "StringHash.h"

#include <map>
#include <vector>

class Color;
class IntRect;
class IntVector2;
class Quaternion;
class Rect;
class Variant;
class Vector2;
class Vector3;
class Vector4;

typedef std::vector<Variant> VariantVector;
typedef std::map<ShortStringHash, Variant> VariantMap;

//! An abstract stream for writing
class Serializer
{
public:
    //! Destruct
    virtual ~Serializer();
    
    //! Write bytes to the stream
    virtual void write(const void* data, unsigned size) = 0;
    
    //! Write a 32-bit integer
    void writeInt(int value);
    //! Write a 16-bit integer
    void writeShort(short value);
    //! Write an 8-bit integer
    void writeByte(signed char value);
    //! Write a 32-bit unsigned integer
    void writeUInt(unsigned value);
    //! Write a 16-bit unsigned integer
    void writeUShort(unsigned short value);
    //! Write an 8-bit unsigned integer
    void writeUByte(unsigned char value);
    //! Write a bool
    void writeBool(bool value);
    //! Write a float
    void writeFloat(float value);
    //! Write an IntRect
    void writeIntRect(const IntRect& value);
    //! Write an IntVector2
    void writeIntVector2(const IntVector2& value);
    //! Write a Rect
    void writeRect(const Rect& value);
    //! Write a Vector2
    void writeVector2(const Vector2& value);
    //! Write a Vector3
    void writeVector3(const Vector3& value);
    //! Write a Vector3 packed into 3 x 16 bits with the specified maximum absolute range
    void writePackedVector3(const Vector3& value, float maxAbsCoord);
    //! Write a Vector4
    void writeVector4(const Vector4& value);
    //! Write a Quaternion
    void writeQuaternion(const Quaternion& value);
    //! Write a Quaternion with each component packed in 16 bits
    void writePackedQuaternion(const Quaternion& value);
    //! Write a Color
    void writeColor(const Color& value);
    //! Write a BoundingBox
    void writeBoundingBox(const BoundingBox& value);
    //! Write a null-terminated string
    void writeString(const std::string& value);
    //! Write a 32-bit StringHash
    void writeStringHash(const StringHash& value);
    //! Write a 16-bit ShortStringHash
    void writeShortStringHash(const ShortStringHash& value);
    //! Write a Variant
    void writeVariant(const Variant& value);
    //! Write a variant vector
    void writeVariantVector(const VariantVector& value);
    //! Write a variant map
    void writeVariantMap(const VariantMap& value);
    //! Write a variable-length encoded unsigned integer, which can use 29 bits maximum
    void writeVLE(unsigned value);
};

#endif // COMMON_SERIALIZER_H
