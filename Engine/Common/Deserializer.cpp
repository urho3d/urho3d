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
#include "Deserializer.h"

#include "DebugNew.h"

Deserializer::~Deserializer()
{
}

const std::string& Deserializer::getName() const
{
    static const std::string emptyName;
    return emptyName;
}

int Deserializer::readInt()
{
    int ret;
    
    read(&ret, sizeof ret);
    return ret;
}

short Deserializer::readShort()
{
    short ret;
    
    read(&ret, sizeof ret);
    return ret;
}

signed char Deserializer::readByte()
{
    signed char ret;
    
    read(&ret, sizeof ret);
    return ret;
}

unsigned Deserializer::readUInt()
{
    unsigned ret;
    
    read(&ret, sizeof ret);
    return ret;
}

unsigned short Deserializer::readUShort()
{
    unsigned short ret;
    
    read(&ret, sizeof ret);
    return ret;
}

unsigned char Deserializer::readUByte()
{
    unsigned char ret;
    
    read(&ret, sizeof ret);
    return ret;
}

bool Deserializer::readBool()
{
    if (readUByte())
        return true;
    else
        return false;
}

float Deserializer::readFloat()
{
    float ret;
    
    read(&ret, sizeof ret);
    return ret;
}

IntRect Deserializer::readIntRect()
{
    IntRect ret;
    
    read((void*)ret.getData(), sizeof ret);
    return ret;
}

IntVector2 Deserializer::readIntVector2()
{
    IntVector2 ret;
    
    read((void*)ret.getData(), sizeof ret);
    return ret;
}

Rect Deserializer::readRect()
{
    Rect ret;
    
    read((void*)ret.getData(), sizeof ret);
    return ret;
}

Vector2 Deserializer::readVector2()
{
    Vector2 ret;
    
    read((void*)ret.getData(), sizeof ret);
    return ret;
}

Vector3 Deserializer::readVector3()
{
    Vector3 ret;
    
    read((void*)ret.getData(), sizeof ret);
    return ret;
}

Vector3 Deserializer::readPackedVector3(float maxAbsCoord)
{
    static const float invV = maxAbsCoord / 32767.0f;
    short coords[3];
    Vector3 ret;
    
    read(&coords[0], sizeof coords);
    ret.mX = coords[0] * invV;
    ret.mY = coords[1] * invV;
    ret.mZ = coords[2] * invV;
    return ret;
}

Vector4 Deserializer::readVector4()
{
    Vector4 ret;
    
    read((void*)ret.getData(), sizeof ret);
    return ret;
}

Quaternion Deserializer::readQuaternion()
{
    Quaternion ret;
    
    read((void*)ret.getData(), sizeof ret);
    return ret;
}

Quaternion Deserializer::readPackedQuaternion()
{
    static const float invQ = 1.0f / 32767.0f;
    short coords[4];
    Quaternion ret;
    
    read(&coords[0], sizeof coords);
    ret.mW = coords[0] * invQ;
    ret.mX = coords[1] * invQ;
    ret.mY = coords[2] * invQ;
    ret.mZ = coords[3] * invQ;
    ret.normalize();
    return ret;
}

Color Deserializer::readColor()
{
    Color ret;
    
    read((void*)ret.getData(), sizeof ret);
    return ret;
}

BoundingBox Deserializer::readBoundingBox()
{
    BoundingBox ret;
    
    ret.mMin = readVector3();
    ret.mMax = readVector3();
    ret.mDefined = true;
    return ret;
}

std::string Deserializer::readString()
{
    std::string ret;
    
    for (;;)
    {
        char c = readByte();
        if (!c)
            break;
        else
            ret += c;
    }
    
    return ret;
}

std::string Deserializer::readID()
{
    std::string ret;
    
    ret.resize(4);
    read(&ret[0], 4);
    return ret;
}

StringHash Deserializer::readStringHash()
{
    StringHash ret;
    
    read((void*)ret.getData(), sizeof(unsigned));
    return ret;
}

ShortStringHash Deserializer::readShortStringHash()
{
    ShortStringHash ret;
    
    read((void*)ret.getData(), sizeof(unsigned short));
    return ret;
}

Variant Deserializer::readVariant()
{
    Variant ret;
    ret.read(*this);
    
    return ret;
}

VariantVector Deserializer::readVariantVector()
{
    VariantVector ret;
    
    unsigned num = readVLE();
    ret.resize(num);
    for (unsigned i = 0; i < num; ++i)
        ret[i].read(*this);
    
    return ret;
}

VariantMap Deserializer::readVariantMap()
{
    VariantMap ret;
    
    unsigned num = readVLE();
    for (unsigned i = 0; i < num; ++i)
    {
        ShortStringHash key = readShortStringHash();
        ret[key].read(*this);
    }
    
    return ret;
}

unsigned Deserializer::readVLE()
{
    unsigned ret;
    unsigned char byte;
    
    byte = readUByte();
    ret = byte & 0x7f;
    if (byte < 0x80)
        return ret;
    
    byte = readUByte();
    ret |= ((unsigned)(byte & 0x7f)) << 7;
    if (byte < 0x80)
        return ret;
    
    byte = readUByte();
    ret |= ((unsigned)(byte & 0x7f)) << 14;
    if (byte < 0x80)
        return ret;
    
    byte = readUByte();
    ret |= ((unsigned)byte) << 21;
    return ret;
}
