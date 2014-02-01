//
// Copyright (c) 2008-2014 the Urho3D project.
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

namespace Urho3D
{

static const float invQ = 1.0f / 32767.0f;

Deserializer::Deserializer() :
    position_(0),
    size_(0)
{
}

Deserializer::Deserializer(unsigned size) :
    position_(0),
    size_(size)
{
}

Deserializer::~Deserializer()
{
}

const String& Deserializer::GetName() const
{
    return String::EMPTY;
}

unsigned Deserializer::GetChecksum()
{
    return 0;
}

int Deserializer::ReadInt()
{
    int ret;
    Read(&ret, sizeof ret);
    return ret;
}

short Deserializer::ReadShort()
{
    short ret;
    Read(&ret, sizeof ret);
    return ret;
}

signed char Deserializer::ReadByte()
{
    signed char ret;
    Read(&ret, sizeof ret);
    return ret;
}

unsigned Deserializer::ReadUInt()
{
    unsigned ret;
    Read(&ret, sizeof ret);
    return ret;
}

unsigned short Deserializer::ReadUShort()
{
    unsigned short ret;
    Read(&ret, sizeof ret);
    return ret;
}

unsigned char Deserializer::ReadUByte()
{
    unsigned char ret;
    Read(&ret, sizeof ret);
    return ret;
}

bool Deserializer::ReadBool()
{
    if (ReadUByte())
        return true;
    else
        return false;
}

float Deserializer::ReadFloat()
{
    float ret;
    Read(&ret, sizeof ret);
    return ret;
}

IntRect Deserializer::ReadIntRect()
{
    IntRect ret;
    Read((void*)ret.Data(), sizeof ret);
    return ret;
}

IntVector2 Deserializer::ReadIntVector2()
{
    IntVector2 ret;
    Read((void*)ret.Data(), sizeof ret);
    return ret;
}

Rect Deserializer::ReadRect()
{
    Rect ret;
    Read((void*)ret.Data(), sizeof ret);
    return ret;
}

Vector2 Deserializer::ReadVector2()
{
    Vector2 ret;
    Read((void*)ret.Data(), sizeof ret);
    return ret;
}

Vector3 Deserializer::ReadVector3()
{
    Vector3 ret;
    Read((void*)ret.Data(), sizeof ret);
    return ret;
}

Vector3 Deserializer::ReadPackedVector3(float maxAbsCoord)
{
    Vector3 ret;
    float invV = maxAbsCoord / 32767.0f;
    short coords[3];
    
    Read(&coords[0], sizeof coords);
    ret.x_ = coords[0] * invV;
    ret.y_ = coords[1] * invV;
    ret.z_ = coords[2] * invV;
    return ret;
}

Vector4 Deserializer::ReadVector4()
{
    Vector4 ret;
    Read((void*)ret.Data(), sizeof ret);
    return ret;
}

Quaternion Deserializer::ReadQuaternion()
{
    Quaternion ret;
    Read((void*)ret.Data(), sizeof ret);
    return ret;
}

Quaternion Deserializer::ReadPackedQuaternion()
{
    short coords[4];
    Quaternion ret;
    
    Read(&coords[0], sizeof coords);
    ret.w_ = coords[0] * invQ;
    ret.x_ = coords[1] * invQ;
    ret.y_ = coords[2] * invQ;
    ret.z_ = coords[3] * invQ;
    ret.Normalize();
    return ret;
}

Color Deserializer::ReadColor()
{
    Color ret;
    Read((void*)ret.Data(), sizeof ret);
    return ret;
}

BoundingBox Deserializer::ReadBoundingBox()
{
    BoundingBox ret;
    ret.min_ = ReadVector3();
    ret.max_ = ReadVector3();
    ret.defined_ = true;
    return ret;
}

String Deserializer::ReadString()
{
    String ret;
    
    for (;;)
    {
        char c = ReadByte();
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
    return StringHash(ReadUInt());
}

ShortStringHash Deserializer::ReadShortStringHash()
{
    return ShortStringHash(ReadUShort());
}

PODVector<unsigned char> Deserializer::ReadBuffer()
{
    PODVector<unsigned char> ret(ReadVLE());
    if (ret.Size())
        Read(&ret[0], ret.Size());
    return ret;
}

ResourceRef Deserializer::ReadResourceRef()
{
    ResourceRef ret;
    ret.type_ = ReadShortStringHash();
    ret.name_ = ReadString();
    return ret;
}

ResourceRefList Deserializer::ReadResourceRefList()
{
    ResourceRefList ret;
    ret.type_ = ReadShortStringHash();
    ret.names_.Resize(ReadVLE());
    for (unsigned i = 0; i < ret.names_.Size(); ++i)
        ret.names_[i] = ReadString();
    return ret;
}

Variant Deserializer::ReadVariant()
{
    VariantType type = (VariantType)ReadUByte();
    return ReadVariant(type);
}

Variant Deserializer::ReadVariant(VariantType type)
{
    switch (type)
    {
    case VAR_INT:
        return Variant(ReadInt());
        
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
        
    case VAR_PTR:
        ReadUInt();
        return Variant((void*)0);
        
    case VAR_RESOURCEREF:
        return Variant(ReadResourceRef());
        
    case VAR_RESOURCEREFLIST:
        return Variant(ReadResourceRefList());
        
    case VAR_VARIANTVECTOR:
        return Variant(ReadVariantVector());
        
    case VAR_VARIANTMAP:
        return Variant(ReadVariantMap());
        
    case VAR_INTRECT:
        return Variant(ReadIntRect());
        
    case VAR_INTVECTOR2:
        return Variant(ReadIntVector2());
        
    default:
        return Variant();
    }
}

VariantVector Deserializer::ReadVariantVector()
{
    VariantVector ret(ReadVLE());
    for (unsigned i = 0; i < ret.Size(); ++i)
        ret[i] = ReadVariant();
    return ret;
}

VariantMap Deserializer::ReadVariantMap()
{
    VariantMap ret;
    unsigned num = ReadVLE();
    
    for (unsigned i = 0; i < num; ++i)
    {
        ShortStringHash key = ReadShortStringHash();
        ret[key] = ReadVariant();
    }
    
    return ret;
}

unsigned Deserializer::ReadVLE()
{
    unsigned ret;
    unsigned char byte;
    
    byte = ReadUByte();
    ret = byte & 0x7f;
    if (byte < 0x80)
        return ret;
    
    byte = ReadUByte();
    ret |= ((unsigned)(byte & 0x7f)) << 7;
    if (byte < 0x80)
        return ret;
    
    byte = ReadUByte();
    ret |= ((unsigned)(byte & 0x7f)) << 14;
    if (byte < 0x80)
        return ret;
    
    byte = ReadUByte();
    ret |= ((unsigned)byte) << 21;
    return ret;
}

unsigned Deserializer::ReadNetID()
{
    unsigned ret = 0;
    Read(&ret, 3);
    return ret;
}

String Deserializer::ReadLine()
{
    String ret;
    
    while (!IsEof())
    {
        char c = ReadByte();
        if (c == 10)
            break;
        if (c == 13)
        {
            // Peek next char to see if it's 10, and skip it too
            if (!IsEof())
            {
                char next = ReadByte();
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
