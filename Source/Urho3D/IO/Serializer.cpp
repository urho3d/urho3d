// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

#include "../Precompiled.h"

#include "../IO/Serializer.h"

#include "../DebugNew.h"

namespace Urho3D
{

static const float q = 32767.0f;

Serializer::~Serializer() = default;

bool Serializer::WriteI64(i64 value)
{
    return Write(&value, sizeof value) == sizeof value;
}

bool Serializer::WriteI32(i32 value)
{
    return Write(&value, sizeof value) == sizeof value;
}

bool Serializer::WriteI16(i16 value)
{
    return Write(&value, sizeof value) == sizeof value;
}

bool Serializer::WriteI8(i8 value)
{
    return Write(&value, sizeof value) == sizeof value;
}

bool Serializer::WriteU64(u64 value)
{
    return Write(&value, sizeof value) == sizeof value;
}

bool Serializer::WriteU32(u32 value)
{
    return Write(&value, sizeof value) == sizeof value;
}

bool Serializer::WriteU16(u16 value)
{
    return Write(&value, sizeof value) == sizeof value;
}

bool Serializer::WriteU8(u8 value)
{
    return Write(&value, sizeof value) == sizeof value;
}

bool Serializer::WriteByte(byte value)
{
    return Write(&value, sizeof value) == sizeof value;
}

bool Serializer::WriteBool(bool value)
{
    return WriteU8((u8)(value ? 1 : 0)) == 1;
}

bool Serializer::WriteFloat(float value)
{
    return Write(&value, sizeof value) == sizeof value;
}

bool Serializer::WriteDouble(double value)
{
    return Write(&value, sizeof value) == sizeof value;
}

bool Serializer::WriteIntRect(const IntRect& value)
{
    return Write(value.Data(), sizeof value) == sizeof value;
}

bool Serializer::WriteIntVector2(const IntVector2& value)
{
    return Write(value.Data(), sizeof value) == sizeof value;
}

bool Serializer::WriteIntVector3(const IntVector3& value)
{
    return Write(value.Data(), sizeof value) == sizeof value;
}

bool Serializer::WriteRect(const Rect& value)
{
    return Write(value.Data(), sizeof value) == sizeof value;
}

bool Serializer::WriteVector2(const Vector2& value)
{
    return Write(value.Data(), sizeof value) == sizeof value;
}

bool Serializer::WriteVector3(const Vector3& value)
{
    return Write(value.Data(), sizeof value) == sizeof value;
}

bool Serializer::WritePackedVector3(const Vector3& value, float maxAbsCoord)
{
    short coords[3];
    float v = 32767.0f / maxAbsCoord;

    coords[0] = (short)Round(Clamp(value.x_, -maxAbsCoord, maxAbsCoord) * v);
    coords[1] = (short)Round(Clamp(value.y_, -maxAbsCoord, maxAbsCoord) * v);
    coords[2] = (short)Round(Clamp(value.z_, -maxAbsCoord, maxAbsCoord) * v);
    return Write(&coords[0], sizeof coords) == sizeof coords;
}

bool Serializer::WriteVector4(const Vector4& value)
{
    return Write(value.Data(), sizeof value) == sizeof value;
}

bool Serializer::WriteQuaternion(const Quaternion& value)
{
    return Write(value.Data(), sizeof value) == sizeof value;
}

bool Serializer::WritePackedQuaternion(const Quaternion& value)
{
    short coords[4];
    Quaternion norm = value.Normalized();

    coords[0] = (short)Round(Clamp(norm.w_, -1.0f, 1.0f) * q);
    coords[1] = (short)Round(Clamp(norm.x_, -1.0f, 1.0f) * q);
    coords[2] = (short)Round(Clamp(norm.y_, -1.0f, 1.0f) * q);
    coords[3] = (short)Round(Clamp(norm.z_, -1.0f, 1.0f) * q);
    return Write(&coords[0], sizeof coords) == sizeof coords;
}

bool Serializer::WriteMatrix3(const Matrix3& value)
{
    return Write(value.Data(), sizeof value) == sizeof value;
}

bool Serializer::WriteMatrix3x4(const Matrix3x4& value)
{
    return Write(value.Data(), sizeof value) == sizeof value;
}

bool Serializer::WriteMatrix4(const Matrix4& value)
{
    return Write(value.Data(), sizeof value) == sizeof value;
}

bool Serializer::WriteColor(const Color& value)
{
    return Write(value.Data(), sizeof value) == sizeof value;
}

bool Serializer::WriteBoundingBox(const BoundingBox& value)
{
    bool success = true;
    success &= WriteVector3(value.min_);
    success &= WriteVector3(value.max_);
    return success;
}

bool Serializer::WriteString(const String& value)
{
    const char* chars = value.CString();
    // Count length to the first zero, because ReadString() does the same
    i32 length = String::CStringLength(chars);
    return Write(chars, length + 1) == length + 1;
}

bool Serializer::WriteFileID(const String& value)
{
    bool success = true;
    i32 length = Min(value.Length(), 4);

    success &= Write(value.CString(), length) == length;
    for (i32 i = value.Length(); i < 4; ++i)
        success &= WriteU8(' ');
    return success;
}

bool Serializer::WriteStringHash(const StringHash& value)
{
    return WriteU32(value.Value());
}

bool Serializer::WriteBuffer(const Vector<byte>& value)
{
    bool success = true;
    unsigned size = value.Size();

    success &= WriteVLE(size);
    if (size)
        success &= Write(&value[0], size) == size;
    return success;
}

bool Serializer::WriteResourceRef(const ResourceRef& value)
{
    bool success = true;
    success &= WriteStringHash(value.type_);
    success &= WriteString(value.name_);
    return success;
}

bool Serializer::WriteResourceRefList(const ResourceRefList& value)
{
    bool success = true;

    success &= WriteStringHash(value.type_);
    success &= WriteVLE(value.names_.Size());
    for (const String& name : value.names_)
        success &= WriteString(name);

    return success;
}

bool Serializer::WriteVariant(const Variant& value)
{
    bool success = true;
    VariantType type = value.GetType();

    success &= WriteU8((u8)type);
    success &= WriteVariantData(value);
    return success;
}

bool Serializer::WriteVariantData(const Variant& value)
{
    switch (value.GetType())
    {
    case VAR_NONE:
        return true;

    case VAR_INT:
        return WriteI32(value.GetI32());

    case VAR_INT64:
        return WriteI64(value.GetI64());

    case VAR_BOOL:
        return WriteBool(value.GetBool());

    case VAR_FLOAT:
        return WriteFloat(value.GetFloat());

    case VAR_VECTOR2:
        return WriteVector2(value.GetVector2());

    case VAR_VECTOR3:
        return WriteVector3(value.GetVector3());

    case VAR_VECTOR4:
        return WriteVector4(value.GetVector4());

    case VAR_QUATERNION:
        return WriteQuaternion(value.GetQuaternion());

    case VAR_COLOR:
        return WriteColor(value.GetColor());

    case VAR_STRING:
        return WriteString(value.GetString());

    case VAR_BUFFER:
        return WriteBuffer(value.GetBuffer());

        // Serializing pointers and custom values is not supported. Write null
    case VAR_VOIDPTR:
    case VAR_PTR:
    case VAR_CUSTOM_HEAP:
    case VAR_CUSTOM_STACK:
        return WriteU32(0);

    case VAR_RESOURCEREF:
        return WriteResourceRef(value.GetResourceRef());

    case VAR_RESOURCEREFLIST:
        return WriteResourceRefList(value.GetResourceRefList());

    case VAR_VARIANTVECTOR:
        return WriteVariantVector(value.GetVariantVector());

    case VAR_STRINGVECTOR:
        return WriteStringVector(value.GetStringVector());

    case VAR_VARIANTMAP:
        return WriteVariantMap(value.GetVariantMap());

    case VAR_INTRECT:
        return WriteIntRect(value.GetIntRect());

    case VAR_INTVECTOR2:
        return WriteIntVector2(value.GetIntVector2());

    case VAR_INTVECTOR3:
        return WriteIntVector3(value.GetIntVector3());

    case VAR_MATRIX3:
        return WriteMatrix3(value.GetMatrix3());

    case VAR_MATRIX3X4:
        return WriteMatrix3x4(value.GetMatrix3x4());

    case VAR_MATRIX4:
        return WriteMatrix4(value.GetMatrix4());

    case VAR_DOUBLE:
        return WriteDouble(value.GetDouble());

    default:
        return false;
    }
}

bool Serializer::WriteVariantVector(const VariantVector& value)
{
    bool success = true;
    success &= WriteVLE(value.Size());
    for (VariantVector::ConstIterator i = value.Begin(); i != value.End(); ++i)
        success &= WriteVariant(*i);
    return success;
}

bool Serializer::WriteStringVector(const StringVector& value)
{
    bool success = true;
    success &= WriteVLE(value.Size());
    for (StringVector::ConstIterator i = value.Begin(); i != value.End(); ++i)
        success &= WriteString(*i);
    return success;
}

bool Serializer::WriteVariantMap(const VariantMap& value)
{
    bool success = true;
    success &= WriteVLE(value.Size());
    for (VariantMap::ConstIterator i = value.Begin(); i != value.End(); ++i)
    {
        WriteStringHash(i->first_);
        WriteVariant(i->second_);
    }
    return success;
}

bool Serializer::WriteVLE(unsigned value)
{
    byte data[4];

    if (value < 0x80)
        return WriteByte((byte)value);
    else if (value < 0x4000)
    {
        data[0] = (byte)(value | 0x80u);
        data[1] = (byte)(value >> 7u);
        return Write(data, 2) == 2;
    }
    else if (value < 0x200000)
    {
        data[0] = (byte)(value | 0x80u);
        data[1] = (byte)(value >> 7u | 0x80u);
        data[2] = (byte)(value >> 14u);
        return Write(data, 3) == 3;
    }
    else
    {
        data[0] = (byte)(value | 0x80u);
        data[1] = (byte)(value >> 7u | 0x80u);
        data[2] = (byte)(value >> 14u | 0x80u);
        data[3] = (byte)(value >> 21u);
        return Write(data, 4) == 4;
    }
}

bool Serializer::WriteNetID(id32 value)
{
    return Write(&value, 3) == 3;
}

bool Serializer::WriteLine(const String& value)
{
    bool success = true;
    success &= Write(value.CString(), value.Length()) == value.Length();
    success &= WriteU8(13);
    success &= WriteU8(10);
    return success;
}

}
