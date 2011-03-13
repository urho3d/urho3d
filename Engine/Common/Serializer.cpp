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
#include "BoundingBox.h"
#include "Serializer.h"
#include "Variant.h"

#include "DebugNew.h"

Serializer::~Serializer()
{
}

void Serializer::writeInt(int value)
{
    write(&value, sizeof value);
}

void Serializer::writeShort(short value)
{
    write(&value, sizeof value);
}

void Serializer::writeByte(signed char value)
{
    write(&value, sizeof value);
}

void Serializer::writeUInt(unsigned value)
{
    write(&value, sizeof value);
}

void Serializer::writeUShort(unsigned short value)
{
    write(&value, sizeof value);
}

void Serializer::writeUByte(unsigned char value)
{
    write(&value, sizeof value);
}

void Serializer::writeBool(bool value)
{
    if (value)
        writeUByte(1);
    else
        writeUByte(0);
}

void Serializer::writeFloat(float value)
{
    write(&value, sizeof value);
}

void Serializer::writeIntRect(const IntRect& value)
{
    write(value.getData(), sizeof value);
}

void Serializer::writeIntVector2(const IntVector2& value)
{
    write(value.getData(), sizeof value);
}

void Serializer::writeRect(const Rect& value)
{
    write(value.getData(), sizeof value);
}

void Serializer::writeVector2(const Vector2& value)
{
    write(value.getData(), sizeof value);
}

void Serializer::writeVector3(const Vector3& value)
{
    write(value.getData(), sizeof value);
}

void Serializer::writePackedVector3(const Vector3& value, float maxAbsCoord)
{
    float v = 32767.0f / maxAbsCoord;
    short coords[3];
    
    coords[0] = (short)(clamp(value.mX, -maxAbsCoord, maxAbsCoord) * v + 0.5f);
    coords[1] = (short)(clamp(value.mY, -maxAbsCoord, maxAbsCoord) * v + 0.5f);
    coords[2] = (short)(clamp(value.mZ, -maxAbsCoord, maxAbsCoord) * v + 0.5f);
    write(&coords[0], sizeof coords);
}

void Serializer::writeVector4(const Vector4& value)
{
    write(value.getData(), sizeof value);
}

void Serializer::writeQuaternion(const Quaternion& value)
{
    write(value.getData(), sizeof value);
}

void Serializer::writePackedQuaternion(const Quaternion& value)
{
    static const float q = 32767.0f;
    short coords[4];
    
    Quaternion norm = value.getNormalized();
    coords[0] = (short)(clamp(norm.mW, -1.0f, 1.0f) * q + 0.5f);
    coords[1] = (short)(clamp(norm.mX, -1.0f, 1.0f) * q + 0.5f);
    coords[2] = (short)(clamp(norm.mY, -1.0f, 1.0f) * q + 0.5f);
    coords[3] = (short)(clamp(norm.mZ, -1.0f, 1.0f) * q + 0.5f);
    write(&coords[0], sizeof coords);
}

void Serializer::writeColor(const Color& value)
{
    write(value.getData(), sizeof value);
}

void Serializer::writeBoundingBox(const BoundingBox& value)
{
    writeVector3(value.mMin);
    writeVector3(value.mMax);
}

void Serializer::writeString(const std::string& value)
{
    write(value.c_str(), value.length() + 1);
}

void Serializer::writeID(const std::string& value)
{
    write(value.c_str(), min((int)value.length(), 4));
    for (unsigned i = value.length(); i < 4; ++i)
        writeByte(' ');
}

void Serializer::writeStringHash(const StringHash& value)
{
    write(value.getData(), sizeof(unsigned));
}

void Serializer::writeShortStringHash(const ShortStringHash& value)
{
    write(value.getData(), sizeof(unsigned short));
}

void Serializer::writeVariant(const Variant& value)
{
    value.write(*this);
}

void Serializer::writeVariantVector(const VariantVector& value)
{
    writeVLE(value.size());
    
    for (VariantVector::const_iterator i = value.begin(); i != value.end(); ++i)
        writeVariant(*i);
}

void Serializer::writeVariantMap(const VariantMap& value)
{
    writeVLE(value.size());
    
    for (VariantMap::const_iterator i = value.begin(); i != value.end(); ++i)
    {
        writeShortStringHash(i->first);
        writeVariant(i->second);
    }
}

void Serializer::writeVLE(unsigned value)
{
    if (value < 0x80)
    {
        writeUByte(value);
    }
    else if (value < 0x4000)
    {
        writeUByte(value | 0x80);
        writeUByte(value >> 7);
    }
    else if (value < 0x200000)
    {
        writeUByte(value | 0x80);
        writeUByte((value >> 7) | 0x80);
        writeUByte(value >> 14);
    }
    else
    {
        writeUByte(value | 0x80);
        writeUByte((value >> 7) | 0x80);
        writeUByte((value >> 14) | 0x80);
        writeUByte(value >> 21);
    }
}

void Serializer::writeLine(const std::string& value)
{
    write(value.c_str(), value.length());
    writeUByte(13);
    writeUByte(10);
}
