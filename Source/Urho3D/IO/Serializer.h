//
// Copyright (c) 2008-2016 the Urho3D project.
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

#include "../Container/HashMap.h"
#include "../Core/Variant.h"
#include "../Math/BoundingBox.h"
#include "../Math/StringHash.h"

namespace Urho3D
{

class Color;
class IntRect;
class IntVector2;
class Quaternion;
class Rect;
class Vector2;
class Vector3;
class Vector4;

/// Abstract stream for writing.
class URHO3D_API Serializer
{
public:
    /// Destruct.
    virtual ~Serializer();

    /// Write bytes to the stream. Return number of bytes actually written.
    virtual unsigned Write(const void* data, unsigned size) = 0;

    /// Write a 32-bit integer.
    bool WriteInt(int value);
    /// Write a 16-bit integer.
    bool WriteShort(short value);
    /// Write an 8-bit integer.
    bool WriteByte(signed char value);
    /// Write a 32-bit unsigned integer.
    bool WriteUInt(unsigned value);
    /// Write a 16-bit unsigned integer.
    bool WriteUShort(unsigned short value);
    /// Write an 8-bit unsigned integer.
    bool WriteUByte(unsigned char value);
    /// Write a bool.
    bool WriteBool(bool value);
    /// Write a float.
    bool WriteFloat(float value);
    /// Write a double.
    bool WriteDouble(double value);
    /// Write an IntRect.
    bool WriteIntRect(const IntRect& value);
    /// Write an IntVector2.
    bool WriteIntVector2(const IntVector2& value);
    /// Write a Rect.
    bool WriteRect(const Rect& value);
    /// Write a Vector2.
    bool WriteVector2(const Vector2& value);
    /// Write a Vector3.
    bool WriteVector3(const Vector3& value);
    /// Write a Vector3 packed into 3 x 16 bits with the specified maximum absolute range.
    bool WritePackedVector3(const Vector3& value, float maxAbsCoord);
    /// Write a Vector4.
    bool WriteVector4(const Vector4& value);
    /// Write a quaternion.
    bool WriteQuaternion(const Quaternion& value);
    /// Write a quaternion with each component packed in 16 bits.
    bool WritePackedQuaternion(const Quaternion& value);
    /// Write a Matrix3.
    bool WriteMatrix3(const Matrix3& value);
    /// Write a Matrix3x4.
    bool WriteMatrix3x4(const Matrix3x4& value);
    /// Write a Matrix4.
    bool WriteMatrix4(const Matrix4& value);
    /// Write a color.
    bool WriteColor(const Color& value);
    /// Write a bounding box.
    bool WriteBoundingBox(const BoundingBox& value);
    /// Write a null-terminated string.
    bool WriteString(const String& value);
    /// Write a four-letter file ID. If the string is not long enough, spaces will be appended.
    bool WriteFileID(const String& value);
    /// Write a 32-bit StringHash.
    bool WriteStringHash(const StringHash& value);
    /// Write a buffer, with size encoded as VLE.
    bool WriteBuffer(const PODVector<unsigned char>& buffer);
    /// Write a resource reference.
    bool WriteResourceRef(const ResourceRef& value);
    /// Write a resource reference list.
    bool WriteResourceRefList(const ResourceRefList& value);
    /// Write a variant.
    bool WriteVariant(const Variant& value);
    /// Write a variant without the type information.
    bool WriteVariantData(const Variant& value);
    /// Write a variant vector.
    bool WriteVariantVector(const VariantVector& value);
    /// Write a variant vector.
    bool WriteStringVector(const StringVector& value);
    /// Write a variant map.
    bool WriteVariantMap(const VariantMap& value);
    /// Write a variable-length encoded unsigned integer, which can use 29 bits maximum.
    bool WriteVLE(unsigned value);
    /// Write a 24-bit network object ID.
    bool WriteNetID(unsigned value);
    /// Write a text line. Char codes 13 & 10 will be automatically appended.
    bool WriteLine(const String& value);
};

}
