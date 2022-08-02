// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

#pragma once

#include "../Core/Variant.h"
#include "../Math/BoundingBox.h"
#include "../Math/Rect.h"

namespace Urho3D
{

/// Abstract stream for reading.
/// @nocount
class URHO3D_API Deserializer
{
public:
    /// Construct with zero size.
    Deserializer();
    /// Construct with defined size.
    explicit Deserializer(unsigned size);
    /// Destruct.
    virtual ~Deserializer();

    /// Read bytes from the stream. Return number of bytes actually read.
    virtual unsigned Read(void* dest, unsigned size) = 0;
    /// Set position from the beginning of the stream. Return actual new position.
    virtual unsigned Seek(unsigned position) = 0;
    /// Return name of the stream.
    /// @property
    virtual const String& GetName() const;
    /// Return a checksum if applicable.
    /// @property
    virtual hash32 GetChecksum();
    /// Return whether the end of stream has been reached.
    /// @property
    virtual bool IsEof() const { return position_ >= size_; }

    /// Set position relative to current position. Return actual new position.
    unsigned SeekRelative(int delta);
    /// Return current position.
    /// @property
    unsigned GetPosition() const { return position_; }
    /// Return current position.
    unsigned Tell() const { return position_; }

    /// Return size.
    /// @property
    unsigned GetSize() const { return size_; }

    /// Read a 64-bit integer.
    long long ReadInt64();
    /// Read a 32-bit integer.
    int ReadInt();
    /// Read a 16-bit integer.
    short ReadShort();
    /// Read an 8-bit integer.
    signed char ReadByte();
    /// Read a 64-bit unsigned integer.
    unsigned long long ReadUInt64();
    /// Read a 32-bit unsigned integer.
    unsigned ReadUInt();
    /// Read a 16-bit unsigned integer.
    unsigned short ReadUShort();
    /// Read an 8-bit unsigned integer.
    unsigned char ReadUByte();
    /// Read a bool.
    bool ReadBool();
    /// Read a float.
    float ReadFloat();
    /// Read a double.
    double ReadDouble();
    /// Read an IntRect.
    IntRect ReadIntRect();
    /// Read an IntVector2.
    IntVector2 ReadIntVector2();
    /// Read an IntVector3.
    IntVector3 ReadIntVector3();
    /// Read a Rect.
    Rect ReadRect();
    /// Read a Vector2.
    Vector2 ReadVector2();
    /// Read a Vector3.
    Vector3 ReadVector3();
    /// Read a Vector3 packed into 3 x 16 bits with the specified maximum absolute range.
    Vector3 ReadPackedVector3(float maxAbsCoord);
    /// Read a Vector4.
    Vector4 ReadVector4();
    /// Read a quaternion.
    Quaternion ReadQuaternion();
    /// Read a quaternion with each component packed in 16 bits.
    Quaternion ReadPackedQuaternion();
    /// Read a Matrix3.
    Matrix3 ReadMatrix3();
    /// Read a Matrix3x4.
    Matrix3x4 ReadMatrix3x4();
    /// Read a Matrix4.
    Matrix4 ReadMatrix4();
    /// Read a color.
    Color ReadColor();
    /// Read a bounding box.
    BoundingBox ReadBoundingBox();
    /// Read a null-terminated string.
    String ReadString();
    /// Read a four-letter file ID.
    String ReadFileID();
    /// Read a 32-bit StringHash.
    StringHash ReadStringHash();
    /// Read a buffer with size encoded as VLE.
    Vector<unsigned char> ReadBuffer();
    /// Read a resource reference.
    ResourceRef ReadResourceRef();
    /// Read a resource reference list.
    ResourceRefList ReadResourceRefList();
    /// Read a variant.
    Variant ReadVariant();
    /// Read a variant whose type is already known.
    Variant ReadVariant(VariantType type);
    /// Read a variant vector.
    VariantVector ReadVariantVector();
    /// Read a string vector.
    StringVector ReadStringVector();
    /// Read a variant map.
    VariantMap ReadVariantMap();
    /// Read a variable-length encoded unsigned integer, which can use 29 bits maximum.
    unsigned ReadVLE();
    /// Read a 24-bit network object ID.
    unsigned ReadNetID();
    /// Read a text line.
    String ReadLine();

protected:
    /// Stream position.
    unsigned position_;
    /// Stream size.
    unsigned size_;
};

}
