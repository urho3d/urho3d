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
#include "Exception.h"
#include "Serializer.h"
#include "StringUtils.h"

#include <cstring>

#include "DebugNew.h"

void Variant::fromString(const std::string& type, const std::string& value)
{
    std::string typeLower = toLower(type);
    
    if (typeLower == "none")
        mType = VAR_NONE;
    else if (typeLower == "int")
        *this = toInt(value);
    else if (typeLower == "bool")
        *this = toBool(value);
    else if (typeLower == "float")
        *this = toFloat(value);
    else if (typeLower == "vector2")
        *this = toVector2(value);
    else if (typeLower == "vector3")
        *this = toVector3(value);
    else if (typeLower == "vector4")
        *this = toVector4(value);
    else if (typeLower == "quaternion")
        *this = toQuaternion(value);
    else if (typeLower == "color")
        *this = toColor(value);
    else if (typeLower == "string")
        *this = value;
    else if (typeLower == "buffer")
    {
        std::vector<std::string> values = split(value, ' ');
        std::vector<unsigned char> buffer;
        for (std::vector<std::string>::const_iterator i = values.begin(); i != values.end(); ++i)
            buffer.push_back(toInt(*i));
        *this = buffer;
    }
    else if (typeLower == "pointer")
        *this = (void*)toInt(value);
    else
        clear();
}

void Variant::write(Serializer& dest) const
{
    dest.writeUByte(mType);
    
    switch (mType)
    {
    case VAR_NONE:
        break;
        
    case VAR_INT:
        dest.writeInt(mValue.mInt);
        break;
        
    case VAR_BOOL:
        dest.writeBool(mValue.mBool);
        break;
        
    case VAR_FLOAT:
        dest.writeFloat(mValue.mFloat);
        break;
        
    case VAR_VECTOR2:
        dest.writeVector2(*(reinterpret_cast<const Vector2*>(&mValue.mVector4)));
        break;
        
    case VAR_VECTOR3:
        dest.writeVector3(*(reinterpret_cast<const Vector3*>(&mValue.mVector4)));
        break;
        
    case VAR_VECTOR4:
        dest.writeVector4(mValue.mVector4);
        break;
        
    case VAR_QUATERNION:
        dest.writeQuaternion(*(reinterpret_cast<const Quaternion*>(&mValue.mVector4)));
        break;
        
    case VAR_COLOR:
        dest.writeColor(*(reinterpret_cast<const Color*>(&mValue.mVector4)));
        break;
        
    case VAR_STRING:
        dest.writeString(mValue.mString);
        break;
        
    case VAR_BUFFER:
        dest.writeVLE(mValue.mBuffer.size());
        if (mValue.mBuffer.size())
            dest.write(&mValue.mBuffer[0], mValue.mBuffer.size());
        break;
        
    case VAR_PTR:
        dest.writeUInt((unsigned)mValue.mPtr);
        break;
    }
}

void Variant::read(Deserializer& source)
{
    mType = (VariantType)source.readUByte();
    
    switch (mType)
    {
    case VAR_NONE:
        break;
        
    case VAR_INT:
        mValue.mInt = source.readInt();
        break;
        
    case VAR_BOOL:
        mValue.mBool = source.readBool();
        break;
        
    case VAR_FLOAT:
        mValue.mFloat = source.readFloat();
        break;
        
    case VAR_VECTOR2:
        *(reinterpret_cast<Vector2*>(&mValue.mVector4)) = source.readVector2();
        break;
        
    case VAR_VECTOR3:
        *(reinterpret_cast<Vector3*>(&mValue.mVector4)) = source.readVector3();
        break;
        
    case VAR_VECTOR4:
        mValue.mVector4 = source.readVector4();
        break;
        
    case VAR_QUATERNION:
        *(reinterpret_cast<Quaternion*>(&mValue.mVector4)) = source.readQuaternion();
        break;
        
    case VAR_COLOR:
        *(reinterpret_cast<Color*>(&mValue.mVector4)) = source.readColor();
        break;
        
    case VAR_STRING:
        mValue.mString = source.readString();
        break;
        
    case VAR_BUFFER:
        mValue.mBuffer.resize(source.readVLE());
        if (mValue.mBuffer.size())
            source.read(&mValue.mBuffer[0], mValue.mBuffer.size());
        break;
        
    case VAR_PTR:
        mValue.mPtr = (void*)source.readUInt();
        break;
        
    default:
        SAFE_EXCEPTION("Unrecognized Variant type " + ::toString((int)mType));
    }
}

void Variant::setBuffer(const void* data, unsigned size)
{
    if ((size) && (!data))
        SAFE_EXCEPTION("Null Variant buffer source");
    
    mType = VAR_BUFFER;
    mValue.mBuffer.resize(size);
    if (size)
        memcpy(&mValue.mBuffer[0], data, size);
}

const std::string& Variant::getTypeName() const
{
    static const std::string typeNames[] =
    {
        "None",
        "Int",
        "Bool",
        "Float",
        "Vector2",
        "Vector3",
        "Vector4",
        "Quaternion",
        "Color",
        "String",
        "Buffer",
        "Pointer"
    };
    
    return typeNames[mType];
}

std::string Variant::toString() const
{
    switch (mType)
    {
    case VAR_INT:
        return ::toString(mValue.mInt);
    case VAR_BOOL:
        return ::toString(mValue.mBool);
    case VAR_FLOAT:
        return ::toString(mValue.mFloat);
    case VAR_VECTOR2:
        return ::toString(*(reinterpret_cast<const Vector2*>(&mValue.mVector4)));
    case VAR_VECTOR3:
        return ::toString(*(reinterpret_cast<const Vector3*>(&mValue.mVector4)));
    case VAR_VECTOR4:
        return ::toString(mValue.mVector4);
    case VAR_QUATERNION:
        return ::toString(*(reinterpret_cast<const Quaternion*>(&mValue.mVector4)));
    case VAR_COLOR:
        return ::toString(*(reinterpret_cast<const Color*>(&mValue.mVector4)));
    case VAR_STRING:
        return mValue.mString;
    case VAR_BUFFER:
        {
            std::string ret;
            for (std::vector<unsigned char>::const_iterator i = mValue.mBuffer.begin(); i != mValue.mBuffer.end(); ++i)
                ret += ::toString(*i) + " ";
            return ret;
        }
    case VAR_PTR:
        return ::toString((unsigned)mValue.mPtr);
    }
    
    return std::string();
}
