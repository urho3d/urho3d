// Copyright (c) 2008-2023 the Urho3D project
// License: MIT

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
class IntVector3;
class Quaternion;
class Rect;
class Vector2;
class Vector3;
class Vector4;

/// Abstract stream for writing.
/// @nocount
class URHO3D_API Serializer
{
public:
    /// Destruct.
    virtual ~Serializer();

    /// Write bytes to the stream. Return number of bytes actually written.
    virtual i32 Write(const void* data, i32 size) = 0;

    /// Write a 64-bit integer.
    bool WriteI64(i64 value);
    /// Write a 32-bit integer.
    bool WriteI32(i32 value);
    /// Write a 16-bit integer.
    bool WriteI16(i16 value);
    /// Write an 8-bit integer.
    bool WriteI8(i8 value);
    /// Write a 64-bit unsigned integer.
    bool WriteU64(u64 value);
    /// Write a 32-bit unsigned integer.
    bool WriteU32(u32 value);
    /// Write a 16-bit unsigned integer.
    bool WriteU16(u16 value);
    /// Write an 8-bit unsigned integer.
    bool WriteU8(u8 value);

    /// Write an byte
    bool WriteByte(byte value);

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
    /// Write an IntVector3.
    bool WriteIntVector3(const IntVector3& value);
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
    bool WriteBuffer(const Vector<byte>& value);
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
    bool WriteNetID(id32 value);
    /// Write a text line. Char codes 13 & 10 will be automatically appended.
    bool WriteLine(const String& value);
};

}
