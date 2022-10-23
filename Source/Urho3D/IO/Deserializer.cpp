// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

#include "../Precompiled.h"

#include "../IO/Deserializer.h"

#include "../DebugNew.h"

namespace Urho3D
{

static const float invQ = 1.0f / 32767.0f;

Deserializer::Deserializer() :
    position_(0),
    size_(0)
{
}

Deserializer::Deserializer(i64 size) :
    position_(0),
    size_(size)
{
    assert(size >= 0);
}

Deserializer::~Deserializer() = default;

i64 Deserializer::SeekRelative(i64 delta)
{
    return Seek(GetPosition() + delta);
}

const String& Deserializer::GetName() const
{
    return String::EMPTY;
}

hash32 Deserializer::GetChecksum()
{
    return 0;
}

i64 Deserializer::ReadI64()
{
    i64 ret;
    Read(&ret, sizeof ret);
    return ret;
}

i32 Deserializer::ReadI32()
{
    i32 ret;
    Read(&ret, sizeof ret);
    return ret;
}

i16 Deserializer::ReadI16()
{
    i16 ret;
    Read(&ret, sizeof ret);
    return ret;
}

i8 Deserializer::ReadI8()
{
    i8 ret;
    Read(&ret, sizeof ret);
    return ret;
}

u64 Deserializer::ReadU64()
{
    u64 ret;
    Read(&ret, sizeof ret);
    return ret;
}

u32 Deserializer::ReadU32()
{
    u32 ret;
    Read(&ret, sizeof ret);
    return ret;
}

u16 Deserializer::ReadU16()
{
    u16 ret;
    Read(&ret, sizeof ret);
    return ret;
}

u8 Deserializer::ReadU8()
{
    u8 ret;
    Read(&ret, sizeof ret);
    return ret;
}

byte Deserializer::ReadByte()
{
    byte ret;
    Read(&ret, sizeof ret);
    return ret;
}

bool Deserializer::ReadBool()
{
    return ReadU8() != 0;
}

float Deserializer::ReadFloat()
{
    float ret;
    Read(&ret, sizeof ret);
    return ret;
}

double Deserializer::ReadDouble()
{
    double ret;
    Read(&ret, sizeof ret);
    return ret;
}

IntRect Deserializer::ReadIntRect()
{
    int data[4];
    Read(data, sizeof data);
    return IntRect(data);
}

IntVector2 Deserializer::ReadIntVector2()
{
    int data[2];
    Read(data, sizeof data);
    return IntVector2(data);
}

IntVector3 Deserializer::ReadIntVector3()
{
    int data[3];
    Read(data, sizeof data);
    return IntVector3(data);
}

Rect Deserializer::ReadRect()
{
    float data[4];
    Read(data, sizeof data);
    return Rect(data);
}

Vector2 Deserializer::ReadVector2()
{
    float data[2];
    Read(data, sizeof data);
    return Vector2(data);
}

Vector3 Deserializer::ReadVector3()
{
    float data[3];
    Read(data, sizeof data);
    return Vector3(data);
}

Vector3 Deserializer::ReadPackedVector3(float maxAbsCoord)
{
    float invV = maxAbsCoord / 32767.0f;
    short coords[3];
    Read(coords, sizeof coords);
    Vector3 ret(coords[0] * invV, coords[1] * invV, coords[2] * invV);
    return ret;
}

Vector4 Deserializer::ReadVector4()
{
    float data[4];
    Read(data, sizeof data);
    return Vector4(data);
}

Quaternion Deserializer::ReadQuaternion()
{
    float data[4];
    Read(data, sizeof data);
    return Quaternion(data);
}

Quaternion Deserializer::ReadPackedQuaternion()
{
    short coords[4];
    Read(coords, sizeof coords);
    Quaternion ret(coords[0] * invQ, coords[1] * invQ, coords[2] * invQ, coords[3] * invQ);
    ret.Normalize();
    return ret;
}

Matrix3 Deserializer::ReadMatrix3()
{
    float data[9];
    Read(data, sizeof data);
    return Matrix3(data);
}

Matrix3x4 Deserializer::ReadMatrix3x4()
{
    float data[12];
    Read(data, sizeof data);
    return Matrix3x4(data);
}

Matrix4 Deserializer::ReadMatrix4()
{
    float data[16];
    Read(data, sizeof data);
    return Matrix4(data);
}

Color Deserializer::ReadColor()
{
    float data[4];
    Read(data, sizeof data);
    return Color(data);
}

BoundingBox Deserializer::ReadBoundingBox()
{
    float data[6];
    Read(data, sizeof data);
    return BoundingBox(Vector3(&data[0]), Vector3(&data[3]));
}

String Deserializer::ReadString()
{
    String ret;

    while (!IsEof())
    {
        char c = ReadU8();
        if (!c)
            break;
        else
            ret += c;
    }

    return ret;
}

String Deserializer::ReadFileID()
{
    String ret;
    ret.Resize(4);
    Read(&ret[0], 4);
    return ret;
}

StringHash Deserializer::ReadStringHash()
{
    return StringHash(ReadU32());
}

Vector<byte> Deserializer::ReadBuffer()
{
    Vector<byte> ret(ReadVLE());
    if (ret.Size())
        Read(&ret[0], ret.Size());
    return ret;
}

ResourceRef Deserializer::ReadResourceRef()
{
    ResourceRef ret;
    ret.type_ = ReadStringHash();
    ret.name_ = ReadString();
    return ret;
}

ResourceRefList Deserializer::ReadResourceRefList()
{
    ResourceRefList ret;
    ret.type_ = ReadStringHash();
    ret.names_.Resize(ReadVLE());
    for (unsigned i = 0; i < ret.names_.Size(); ++i)
        ret.names_[i] = ReadString();
    return ret;
}

Variant Deserializer::ReadVariant()
{
    VariantType type = (VariantType)ReadU8();
    return ReadVariant(type);
}

Variant Deserializer::ReadVariant(VariantType type)
{
    switch (type)
    {
    case VAR_INT:
        return Variant(ReadI32());

    case VAR_INT64:
        return Variant(ReadI64());

    case VAR_BOOL:
        return Variant(ReadBool());

    case VAR_FLOAT:
        return Variant(ReadFloat());

    case VAR_VECTOR2:
        return Variant(ReadVector2());

    case VAR_VECTOR3:
        return Variant(ReadVector3());

    case VAR_VECTOR4:
        return Variant(ReadVector4());

    case VAR_QUATERNION:
        return Variant(ReadQuaternion());

    case VAR_COLOR:
        return Variant(ReadColor());

    case VAR_STRING:
        return Variant(ReadString());

    case VAR_BUFFER:
        return Variant(ReadBuffer());

        // Deserializing pointers is not supported. Return null
    case VAR_VOIDPTR:
    case VAR_PTR:
        ReadU32();
        return Variant((void*)nullptr);

    case VAR_RESOURCEREF:
        return Variant(ReadResourceRef());

    case VAR_RESOURCEREFLIST:
        return Variant(ReadResourceRefList());

    case VAR_VARIANTVECTOR:
        return Variant(ReadVariantVector());

    case VAR_STRINGVECTOR:
        return Variant(ReadStringVector());

    case VAR_VARIANTMAP:
        return Variant(ReadVariantMap());

    case VAR_INTRECT:
        return Variant(ReadIntRect());

    case VAR_INTVECTOR2:
        return Variant(ReadIntVector2());

    case VAR_INTVECTOR3:
        return Variant(ReadIntVector3());

    case VAR_MATRIX3:
        return Variant(ReadMatrix3());

    case VAR_MATRIX3X4:
        return Variant(ReadMatrix3x4());

    case VAR_MATRIX4:
        return Variant(ReadMatrix4());

    case VAR_DOUBLE:
        return Variant(ReadDouble());

        // Deserializing custom values is not supported. Return empty
    case VAR_CUSTOM_HEAP:
    case VAR_CUSTOM_STACK:
        ReadU32();
        return Variant::EMPTY;

    default:
        return Variant::EMPTY;
    }
}

VariantVector Deserializer::ReadVariantVector()
{
    VariantVector ret(ReadVLE());
    for (unsigned i = 0; i < ret.Size(); ++i)
        ret[i] = ReadVariant();
    return ret;
}

StringVector Deserializer::ReadStringVector()
{
    StringVector ret(ReadVLE());
    for (unsigned i = 0; i < ret.Size(); ++i)
        ret[i] = ReadString();
    return ret;
}

VariantMap Deserializer::ReadVariantMap()
{
    VariantMap ret;
    unsigned num = ReadVLE();

    for (unsigned i = 0; i < num; ++i)
    {
        StringHash key = ReadStringHash();
        ret[key] = ReadVariant();
    }

    return ret;
}

unsigned Deserializer::ReadVLE()
{
    unsigned ret;
    u8 b;

    b = ReadU8();
    ret = (unsigned)(b & 0x7fu);
    if (b < 0x80)
        return ret;

    b = ReadU8();
    ret |= ((unsigned)(b & 0x7fu)) << 7u;
    if (b < 0x80)
        return ret;

    b = ReadU8();
    ret |= ((unsigned)(b & 0x7fu)) << 14u;
    if (b < 0x80)
        return ret;

    b = ReadU8();
    ret |= ((unsigned)b) << 21u;
    return ret;
}

id32 Deserializer::ReadNetID()
{
    id32 ret = 0;
    Read(&ret, 3);
    return ret;
}

String Deserializer::ReadLine()
{
    String ret;

    while (!IsEof())
    {
        char c = ReadU8();
        if (c == 10)
            break;
        if (c == 13)
        {
            // Peek next char to see if it's 10, and skip it too
            if (!IsEof())
            {
                char next = ReadU8();
                if (next != 10)
                    Seek(position_ - 1);
            }
            break;
        }

        ret += c;
    }

    return ret;
}

}
