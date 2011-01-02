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
#include "ReplicationUtils.h"

#include <cstring>

void checkBool(bool value, Deserializer& baseRevision, unsigned char& bits, unsigned char bit)
{
    // If no base data, set bit always
    if (baseRevision.isEof())
        bits |= bit;
    else
    {
        if (value != baseRevision.readBool())
            bits |= bit;
    }
}

void checkBool(bool value, bool defaultValue, Deserializer& baseRevision, unsigned char& bits, unsigned char bit)
{
    // If no base data, compare to default value
    if (baseRevision.isEof())
    {
        if (value != defaultValue)
            bits |= bit;
    }
    else
    {
        if (value != baseRevision.readBool())
            bits |= bit;
    }
}

void checkInt(int value, Deserializer& baseRevision, unsigned char& bits, unsigned char bit)
{
    // If no base data, set bit always
    if (baseRevision.isEof())
        bits |= bit;
    else
    {
        if (value != baseRevision.readInt())
            bits |= bit;
    }
}

void checkInt(int value, int defaultValue, Deserializer& baseRevision, unsigned char& bits, unsigned char bit)
{
    // If no base data, compare to default value
    if (baseRevision.isEof())
    {
        if (value != defaultValue)
            bits |= bit;
    }
    else
    {
        if (value != baseRevision.readInt())
            bits |= bit;
    }
}

void checkUByte(unsigned char value, Deserializer& baseRevision, unsigned char& bits, unsigned char bit)
{
    // If no base data, set bit always
    if (baseRevision.isEof())
        bits |= bit;
    else
    {
        if (value != baseRevision.readUByte())
            bits |= bit;
    }
}

void checkUByte(unsigned char value, unsigned char defaultValue, Deserializer& baseRevision, unsigned char& bits, unsigned char bit)
{
    // If no base data, compare to default value
    if (baseRevision.isEof())
    {
        if (value != defaultValue)
            bits |= bit;
    }
    else
    {
        if (value != baseRevision.readUByte())
            bits |= bit;
    }
}

void checkUShort(unsigned short value, Deserializer& baseRevision, unsigned char& bits, unsigned char bit)
{
    // If no base data, set bit always
    if (baseRevision.isEof())
        bits |= bit;
    else
    {
        if (value != baseRevision.readUShort())
            bits |= bit;
    }
}

void checkUShort(unsigned short value, unsigned short defaultValue, Deserializer& baseRevision, unsigned char& bits, unsigned char bit)
{
    // If no base data, compare to default value
    if (baseRevision.isEof())
    {
        if (value != defaultValue)
            bits |= bit;
    }
    else
    {
        if (value != baseRevision.readUShort())
            bits |= bit;
    }
}

void checkUInt(unsigned value, Deserializer& baseRevision, unsigned char& bits, unsigned char bit)
{
    // If no base data, set bit always
    if (baseRevision.isEof())
        bits |= bit;
    else
    {
        if (value != baseRevision.readUInt())
            bits |= bit;
    }
}

void checkUInt(unsigned value, unsigned defaultValue, Deserializer& baseRevision, unsigned char& bits, unsigned char bit)
{
    // If no base data, compare to default value
    if (baseRevision.isEof())
    {
        if (value != defaultValue)
            bits |= bit;
    }
    else
    {
        if (value != baseRevision.readUInt())
            bits |= bit;
    }
}

void checkFloat(float value, Deserializer& baseRevision, unsigned char& bits, unsigned char bit)
{
    // If no base data, set bit always
    if (baseRevision.isEof())
        bits |= bit;
    else
    {
        if (value != baseRevision.readFloat())
            bits |= bit;
    }
}

void checkFloat(float value, float defaultValue, Deserializer& baseRevision, unsigned char& bits, unsigned char bit)
{
    // If no base data, compare to default value
    if (baseRevision.isEof())
    {
        if (value != defaultValue)
            bits |= bit;
    }
    else
    {
        if (value != baseRevision.readFloat())
            bits |= bit;
    }
}

void checkVector3(const Vector3& value, Deserializer& baseRevision, unsigned char& bits, unsigned char bit)
{
    // If no base data, set bit always
    if (baseRevision.isEof())
        bits |= bit;
    else
    {
        if (value != baseRevision.readVector3())
            bits |= bit;
    }
}

void checkVector3(const Vector3& value, const Vector3& defaultValue, Deserializer& baseRevision, unsigned char& bits, unsigned char bit)
{
    // If no base data, compare to default value
    if (baseRevision.isEof())
    {
        if (value != defaultValue)
            bits |= bit;
    }
    else
    {
        if (value != baseRevision.readVector3())
            bits |= bit;
    }
}

void checkQuaternion(const Quaternion& value, Deserializer& baseRevision, unsigned char& bits, unsigned char bit)
{
    // If no base data, set bit always
    if (baseRevision.isEof())
        bits |= bit;
    else
    {
        if (value != baseRevision.readQuaternion())
            bits |= bit;
    }
}

void checkQuaternion(const Quaternion& value, const Quaternion& defaultValue, Deserializer& baseRevision, unsigned char& bits, unsigned char bit)
{
    // If no base data, compare to default value
    if (baseRevision.isEof())
    {
        if (value != defaultValue)
            bits |= bit;
    }
    else
    {
        if (value != baseRevision.readQuaternion())
            bits |= bit;
    }
}

void checkColor(const Color& value, Deserializer& baseRevision, unsigned char& bits, unsigned char bit)
{
    // If no base data, set bit always
    if (baseRevision.isEof())
        bits |= bit;
    else
    {
        if (value != baseRevision.readColor())
            bits |= bit;
    }
}

void checkColor(const Color& value, const Color& defaultValue, Deserializer& baseRevision, unsigned char& bits, unsigned char bit)
{
    // If no base data, compare to default value
    if (baseRevision.isEof())
    {
        if (value != defaultValue)
            bits |= bit;
    }
    else
    {
        if (value != baseRevision.readColor())
            bits |= bit;
    }
}

void checkString(const std::string& value, Deserializer& baseRevision, unsigned char& bits, unsigned char bit)
{
    // If no base data, set bit always
    if (baseRevision.isEof())
        bits |= bit;
    else
    {
        if (value != baseRevision.readString())
            bits |= bit;
    }
}

void checkString(const std::string& value, const std::string& defaultValue, Deserializer& baseRevision, unsigned char& bits, unsigned char bit)
{
    // If no base data, compare to default value
    if (baseRevision.isEof())
    {
        if (value != defaultValue)
            bits |= bit;
    }
    else
    {
        if (value != baseRevision.readString())
            bits |= bit;
    }
}

void checkStringHash(StringHash value, Deserializer& baseRevision, unsigned char& bits, unsigned char bit)
{
    // If no base data, set bit always
    if (baseRevision.isEof())
        bits |= bit;
    else
    {
        if (value != baseRevision.readStringHash())
            bits |= bit;
    }
}

void checkStringHash(StringHash value, StringHash defaultValue, Deserializer& baseRevision, unsigned char& bits, unsigned char bit)
{
    // If no base data, compare to default value
    if (baseRevision.isEof())
    {
        if (value != defaultValue)
            bits |= bit;
    }
    else
    {
        if (value != baseRevision.readStringHash())
            bits |= bit;
    }
}

void checkShortStringHash(ShortStringHash value, Deserializer& baseRevision, unsigned char& bits, unsigned char bit)
{
    // If no base data, set bit always
    if (baseRevision.isEof())
        bits |= bit;
    else
    {
        if (value != baseRevision.readShortStringHash())
            bits |= bit;
    }
}

void checkShortStringHash(ShortStringHash value, ShortStringHash defaultValue, Deserializer& baseRevision, unsigned char& bits, unsigned char bit)
{
    // If no base data, compare to default value
    if (baseRevision.isEof())
    {
        if (value != defaultValue)
            bits |= bit;
    }
    else
    {
        if (value != baseRevision.readShortStringHash())
            bits |= bit;
    }
}

void checkComponentRef(const ComponentRef& value, Deserializer& baseRevision, unsigned char& bits, unsigned char bit)
{
    // If no base data, set bit always
    if (baseRevision.isEof())
        bits |= bit;
    else
    {
        ComponentRef temp;
        temp.readPacked(baseRevision);
        if (value != temp)
            bits |= bit;
    }
}

void checkComponentRef(const ComponentRef& value, const ComponentRef& defaultValue, Deserializer& baseRevision, unsigned char& bits, unsigned char bit)
{
    // If no base data, compare to default value
    if (baseRevision.isEof())
    {
        if (value != defaultValue)
            bits |= bit;
    }
    else
    {
        ComponentRef temp;
        temp.readPacked(baseRevision);
        if (value != temp)
            bits |= bit;
    }
}

void checkVLE(unsigned value, Deserializer& baseRevision, unsigned char& bits, unsigned char bit)
{
    // If no base data, set bit always
    if (baseRevision.isEof())
        bits |= bit;
    else
    {
        if (value != baseRevision.readVLE())
            bits |= bit;
    }
}

void checkVLE(unsigned value, unsigned defaultValue, Deserializer& baseRevision, unsigned char& bits, unsigned char bit)
{
    // If no base data, compare to default value
    if (baseRevision.isEof())
    {
        if (value != defaultValue)
            bits |= bit;
    }
    else
    {
        if (value != baseRevision.readVLE())
            bits |= bit;
    }
}

void checkBuffer(const VectorBuffer& value, Deserializer& baseRevision, unsigned char& bits, unsigned char bit)
{
    // If no base data, set bit always
    if (baseRevision.isEof())
        bits |= bit;
    else
    {
        static VectorBuffer baseBuffer;
        unsigned baseBufferSize = baseRevision.readVLE();
        baseBuffer.setData(baseRevision, baseBufferSize);
        if ((baseBufferSize != value.getSize()) || (memcmp(value.getData(), baseBuffer.getData(), value.getSize())))
            bits |= bit;
    }
}

void writeBoolDelta(bool value, Serializer& dest, Serializer& destRevision, unsigned char condition)
{
    destRevision.writeBool(value);
    if (condition)
        dest.writeBool(value);
}

void writeIntDelta(int value, Serializer& dest, Serializer& destRevision, unsigned char condition)
{
    destRevision.writeInt(value);
    if (condition)
        dest.writeInt(value);
}

void writeUByteDelta(unsigned char value, Serializer& dest, Serializer& destRevision, unsigned char condition)
{
    destRevision.writeUByte(value);
    if (condition)
        dest.writeUByte(value);
}

void writeUShortDelta(unsigned short value, Serializer& dest, Serializer& destRevision, unsigned char condition)
{
    destRevision.writeUShort(value);
    if (condition)
        dest.writeUShort(value);
}

void writeUIntDelta(unsigned value, Serializer& dest, Serializer& destRevision, unsigned char condition)
{
    destRevision.writeUInt(value);
    if (condition)
        dest.writeUInt(value);
}

void writeFloatDelta(float value, Serializer& dest, Serializer& destRevision, unsigned char condition)
{
    destRevision.writeFloat(value);
    if (condition)
        dest.writeFloat(value);
}

void writeVector3Delta(const Vector3& value, Serializer& dest, Serializer& destRevision, unsigned char condition)
{
    destRevision.writeVector3(value);
    if (condition)
        dest.writeVector3(value);
}

void writePackedVector3Delta(const Vector3& value, float maxAbsCoord, Serializer& dest, Serializer& destRevision, unsigned char condition)
{
    // Use full resolution in the internal value, but pack to half size for the network stream
    destRevision.writeVector3(value);
    if (condition)
        dest.writePackedVector3(value, maxAbsCoord);
}

void writeQuaternionDelta(const Quaternion& value, Serializer& dest, Serializer& destRevision, unsigned char condition)
{
    destRevision.writeQuaternion(value);
    if (condition)
        dest.writeQuaternion(value);
}

void writePackedQuaternionDelta(const Quaternion& value, Serializer& dest, Serializer& destRevision, unsigned char condition)
{
    // Use full resolution in the internal value, but pack to half size for the network stream
    destRevision.writeQuaternion(value);
    if (condition)
        dest.writePackedQuaternion(value);
}

void writeColorDelta(const Color& value, Serializer& dest, Serializer& destRevision, unsigned char condition)
{
    destRevision.writeColor(value);
    if (condition)
        dest.writeColor(value);
}

void writeStringDelta(const std::string& value, Serializer& dest, Serializer& destRevision, unsigned char condition)
{
    destRevision.writeString(value);
    if (condition)
        dest.writeString(value);
}

void writeStringHashDelta(StringHash value, Serializer& dest, Serializer& destRevision, unsigned char condition)
{
    destRevision.writeStringHash(value);
    if (condition)
        dest.writeStringHash(value);
}

void writeShortStringHashDelta(ShortStringHash value, Serializer& dest, Serializer& destRevision, unsigned char condition)
{
    destRevision.writeShortStringHash(value);
    if (condition)
        dest.writeShortStringHash(value);
}

void writeComponentRefDelta(const ComponentRef& value, Serializer& dest, Serializer& destRevision, unsigned char condition)
{
    value.writePacked(destRevision);
    if (condition)
        value.writePacked(dest);
}

void writeVLEDelta(unsigned value, Serializer& dest, Serializer& destRevision, unsigned char condition)
{
    destRevision.writeVLE(value);
    if (condition)
        dest.writeVLE(value);
}

void writeBufferDelta(const VectorBuffer& value, Serializer& dest, Serializer& destRevision, unsigned char condition)
{
    destRevision.writeVLE(value.getSize());
    destRevision.write(value.getData(), value.getSize());
    if (condition)
    {
        dest.writeVLE(value.getSize());
        dest.write(value.getData(), value.getSize());
    }
}

bool readBoolDelta(bool& value, Deserializer& source, unsigned char condition)
{
    if (condition)
        value = source.readBool();
    return condition != 0;
}

bool readIntDelta(int& value, Deserializer& source, unsigned char condition)
{
    if (condition)
        value = source.readInt();
    return condition != 0;
}

bool readUByteDelta(unsigned char& value, Deserializer& source, unsigned char condition)
{
    if (condition)
        value = source.readUByte();
    return condition != 0;
}

bool readUShortDelta(unsigned short& value, Deserializer& source, unsigned char condition)
{
    if (condition)
        value = source.readUShort();
    return condition != 0;
}

bool readUIntDelta(unsigned& value, Deserializer& source, unsigned char condition)
{
    if (condition)
        value = source.readUInt();
    return condition != 0;
}

bool readFloatDelta(float& value, Deserializer& source, unsigned char condition)
{
    if (condition)
        value = source.readFloat();
    return condition != 0;
}

bool readVector3Delta(Vector3& value, Deserializer& source, unsigned char condition)
{
    if (condition)
        value = source.readVector3();
    return condition != 0;
}

bool readPackedVector3Delta(Vector3& value, float maxAbsCoord, Deserializer& source, unsigned char condition)
{
    if (condition)
        value = source.readPackedVector3(maxAbsCoord);
    return condition != 0;
}

bool readQuaternionDelta(Quaternion& value, Deserializer& source, unsigned char condition)
{
    if (condition)
        value = source.readQuaternion();
    return condition != 0;
}

bool readPackedQuaternionDelta(Quaternion& value, Deserializer& source, unsigned char condition)
{
    if (condition)
        value = source.readPackedQuaternion();
    return condition != 0;
}

bool readColorDelta(Color& value, Deserializer& source, unsigned char condition)
{
    if (condition)
        value = source.readColor();
    return condition != 0;
}

bool readStringDelta(std::string& value, Deserializer& source, unsigned char condition)
{
    if (condition)
        value = source.readString();
    return condition != 0;
}

bool readStringHashDelta(StringHash& value, Deserializer& source, unsigned char condition)
{
    if (condition)
        value = source.readStringHash();
    return condition != 0;
}

bool readShortStringHashDelta(ShortStringHash& value, Deserializer& source, unsigned char condition)
{
    if (condition)
        value = source.readShortStringHash();
    return condition != 0;
}

bool readComponentRefDelta(ComponentRef& value, Deserializer& source, unsigned char condition)
{
    if (condition)
        value.readPacked(source);
    return condition != 0;
}

bool readVLEDelta(unsigned& value, Deserializer& source, unsigned char condition)
{
    if (condition)
        value = source.readVLE();
    return condition != 0;
}

bool readBufferDelta(VectorBuffer& value, Deserializer& source, unsigned char condition)
{
    if (condition)
    {
        unsigned bufferSize = source.readVLE();
        value.setData(source, bufferSize);
    }
    return condition != 0;
}
