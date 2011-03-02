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
#include "Log.h"
#include "Serializer.h"
#include "StringUtils.h"

#include <cstring>

#include "DebugNew.h"

Variant& Variant::operator = (const Variant& rhs)
{
    setType(rhs.getType());
    
    switch (mType)
    {
    case VAR_STRING:
        *(reinterpret_cast<std::string*>(mValue.mPtr)) = *(reinterpret_cast<const std::string*>(rhs.mValue.mPtr));
        break;
        
    case VAR_BUFFER:
        *(reinterpret_cast<std::vector<unsigned char>*>(mValue.mPtr)) = *(reinterpret_cast<const std::vector<unsigned char>*>(rhs.mValue.mPtr));
        break;
    
    case VAR_VARIANTVECTOR:
        *(reinterpret_cast<VariantVector*>(mValue.mPtr)) = *(reinterpret_cast<VariantVector*>(rhs.mValue.mPtr));
        break;
        
    case VAR_VARIANTMAP:
        *(reinterpret_cast<VariantMap*>(mValue.mPtr)) = *(reinterpret_cast<VariantMap*>(rhs.mValue.mPtr));
        break;
        
    default:
        mValue = rhs.mValue;
        break;
    }
    
    return *this;
}

bool Variant::operator == (const Variant& rhs) const
{
    if (mType != rhs.mType)
        return false;
    
    switch (mType)
    {
    case VAR_INT:
        return mValue.mInt == rhs.mValue.mInt;
        
    case VAR_BOOL:
        return mValue.mBool == rhs.mValue.mBool;
        
    case VAR_FLOAT:
        return mValue.mFloat == rhs.mValue.mFloat;
        
    case VAR_VECTOR2:
        return *(reinterpret_cast<const Vector2*>(&mValue)) == *(reinterpret_cast<const Vector2*>(&rhs.mValue));
        
    case VAR_VECTOR3:
        return *(reinterpret_cast<const Vector3*>(&mValue)) == *(reinterpret_cast<const Vector3*>(&rhs.mValue));
        
    case VAR_VECTOR4:
        return *(reinterpret_cast<const Vector4*>(&mValue)) == *(reinterpret_cast<const Vector4*>(&rhs.mValue));
        
    case VAR_QUATERNION:
        return *(reinterpret_cast<const Quaternion*>(&mValue)) == *(reinterpret_cast<const Quaternion*>(&rhs.mValue));
        
    case VAR_COLOR:
        return *(reinterpret_cast<const Color*>(&mValue)) == *(reinterpret_cast<const Color*>(&rhs.mValue));
        
    case VAR_STRING:
        return *(reinterpret_cast<const std::string*>(mValue.mPtr)) == *(reinterpret_cast<const std::string*>(rhs.mValue.mPtr));
        
    case VAR_BUFFER:
        return *(reinterpret_cast<const std::vector<unsigned char>*>(mValue.mPtr)) == *(reinterpret_cast<const std::vector<unsigned char>*>(rhs.mValue.mPtr));
        
    case VAR_PTR:
        return mValue.mPtr == rhs.mValue.mPtr;
        
    case VAR_VARIANTVECTOR:
        return *(reinterpret_cast<const VariantVector*>(mValue.mPtr)) == *(reinterpret_cast<const VariantVector*>(rhs.mValue.mPtr));
        
    case VAR_VARIANTMAP:
        return *(reinterpret_cast<const VariantMap*>(mValue.mPtr)) == *(reinterpret_cast<const VariantMap*>(rhs.mValue.mPtr));
    }
    
    return true;
}

void Variant::fromString(const std::string& type, const std::string& value)
{
    std::string typeLower = toLower(type);
    
    if (typeLower == "none")
        setType(VAR_NONE);
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
        setType(VAR_BUFFER);
        std::vector<unsigned char>& buffer = *(reinterpret_cast<std::vector<unsigned char>*>(mValue.mPtr));
        std::vector<std::string> values = split(value, ' ');
        buffer.resize(values.size());
        for (unsigned i = 0; i < values.size(); ++i)
            buffer[i] = toInt(values[i]);
    }
    else if (typeLower == "pointer")
    {
        LOGWARNING("Deserialized pointer Variant set to null");
        *this = (void*)0;
    }
    else if (typeLower == "variantvector")
    {
        setType(VAR_VARIANTVECTOR);
        VariantVector& dest = *(reinterpret_cast<VariantVector*>(mValue.mPtr));
        std::vector<std::string> values = split(value, '#');
        dest.resize(values.size() >> 1);
        for (unsigned i = 0; i < values.size() - 1; i += 2)
            dest[i >> 1].fromString(values[i], values[i + 1]);
    }
    else if (typeLower == "variantmap")
    {
        setType(VAR_VARIANTMAP);
        VariantMap& dest = *(reinterpret_cast<VariantMap*>(mValue.mPtr));
        dest.clear();
        std::vector<std::string> values = split(value, '#');
        for (unsigned i = 0; i < values.size() - 2; i += 3)
            dest[ShortStringHash(values[i])].fromString(values[i + 1], values[i + 2]);
    }
    else
        setType(VAR_NONE);
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
        dest.writeVector2(*(reinterpret_cast<const Vector2*>(&mValue)));
        break;
        
    case VAR_VECTOR3:
        dest.writeVector3(*(reinterpret_cast<const Vector3*>(&mValue)));
        break;
        
    case VAR_VECTOR4:
        dest.writeVector4(*(reinterpret_cast<const Vector4*>(&mValue)));
        break;
        
    case VAR_QUATERNION:
        dest.writeQuaternion(*(reinterpret_cast<const Quaternion*>(&mValue)));
        break;
        
    case VAR_COLOR:
        dest.writeColor(*(reinterpret_cast<const Color*>(&mValue)));
        break;
        
    case VAR_STRING:
        dest.writeString(*(reinterpret_cast<const std::string*>(mValue.mPtr)));
        break;
        
    case VAR_BUFFER:
        {
            const std::vector<unsigned char>& buffer = *(reinterpret_cast<const std::vector<unsigned char>*>(mValue.mPtr));
            dest.writeVLE(buffer.size());
            if (buffer.size())
                dest.write(&buffer[0], buffer.size());
        }
        break;
        
    case VAR_PTR:
        LOGWARNING("Serialized pointer Variant set to null");
        dest.writeUInt(0);
        break;
        
    case VAR_VARIANTVECTOR:
        {
            const VariantVector& vector = *(reinterpret_cast<VariantVector*>(mValue.mPtr));
            dest.writeVariantVector(vector);
        }
        break;
        
    case VAR_VARIANTMAP:
        {
            const VariantMap& map = *(reinterpret_cast<VariantMap*>(mValue.mPtr));
            dest.writeVariantMap(map);
        }
        break;
    }
}

void Variant::read(Deserializer& source)
{
    VariantType type = (VariantType)source.readUByte();
    
    switch (type)
    {
    case VAR_NONE:
        setType(VAR_NONE);
        break;
        
    case VAR_INT:
        *this = source.readInt();
        break;
        
    case VAR_BOOL:
        *this = source.readBool();
        break;
        
    case VAR_FLOAT:
        *this = source.readFloat();
        break;
        
    case VAR_VECTOR2:
        *this = source.readVector2();
        break;
        
    case VAR_VECTOR3:
        *this = source.readVector3();
        break;
        
    case VAR_VECTOR4:
        *this = source.readVector4();
        break;
        
    case VAR_QUATERNION:
        *this = source.readQuaternion();
        break;
        
    case VAR_COLOR:
        *this = source.readColor();
        break;
        
    case VAR_STRING:
        *this = source.readString();
        break;
        
    case VAR_BUFFER:
        {
            setType(VAR_BUFFER);
            std::vector<unsigned char>& buffer = *(reinterpret_cast<std::vector<unsigned char>*>(mValue.mPtr));
            buffer.resize(source.readVLE());
            if (buffer.size())
                source.read(&buffer[0], buffer.size());
        }
        break;
        
    case VAR_PTR:
        LOGWARNING("Deserialized pointer Variant set to null");
        source.readUInt();
        *this = (void*)0;
        break;
        
    case VAR_VARIANTVECTOR:
        {
            setType(VAR_VARIANTVECTOR);
            VariantVector& dest = *(reinterpret_cast<VariantVector*>(mValue.mPtr));
            unsigned num = source.readVLE();
            dest.resize(num);
            for (unsigned i = 0; i < num; ++i)
                dest[i].read(source);
        }
        break;
        
    case VAR_VARIANTMAP:
        {
            setType(VAR_VARIANTMAP);
            VariantMap& dest = *(reinterpret_cast<VariantMap*>(mValue.mPtr));
            dest.clear();
            unsigned num = source.readVLE();
            for (unsigned i = 0; i < num; ++i)
            {
                ShortStringHash key = source.readShortStringHash();
                dest[key].read(source);
            }
        }
        break;
        
    default:
        SAFE_EXCEPTION("Unrecognized Variant type " + ::toString((int)mType));
    }
}

void Variant::setBuffer(const void* data, unsigned size)
{
    if ((size) && (!data))
        SAFE_EXCEPTION("Null Variant buffer source");
    
    setType(VAR_BUFFER);
    std::vector<unsigned char>& buffer = *(reinterpret_cast<std::vector<unsigned char>*>(mValue.mPtr));
    buffer.resize(size);
    if (buffer.size())
        memcpy(&buffer[0], data, size);
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
        "Pointer",
        "VariantVector",
        "VariantMap"
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
        return ::toString(*(reinterpret_cast<const Vector2*>(&mValue)));
        
    case VAR_VECTOR3:
        return ::toString(*(reinterpret_cast<const Vector3*>(&mValue)));
        
    case VAR_VECTOR4:
        return ::toString(*(reinterpret_cast<const Vector4*>(&mValue)));
        
    case VAR_QUATERNION:
        return ::toString(*(reinterpret_cast<const Quaternion*>(&mValue)));
        
    case VAR_COLOR:
        return ::toString(*(reinterpret_cast<const Color*>(&mValue)));
        
    case VAR_STRING:
        return *(reinterpret_cast<const std::string*>(mValue.mPtr));
        
    case VAR_BUFFER:
        {
            const std::vector<unsigned char>& buffer = *(reinterpret_cast<const std::vector<unsigned char>*>(mValue.mPtr));
            std::string ret;
            for (std::vector<unsigned char>::const_iterator i = buffer.begin(); i != buffer.end(); ++i)
            {
                if (i != buffer.begin())
                    ret += " ";
                ret += ::toString(*i);
            }
            return ret;
        }
        
    case VAR_PTR:
        LOGWARNING("Serialized pointer Variant set to null");
        return ::toString((unsigned)0);
        
    case VAR_VARIANTVECTOR:
        {
            const VariantVector& vector = *(reinterpret_cast<const VariantVector*>(mValue.mPtr));
            std::string ret;
            for (VariantVector::const_iterator i = vector.begin(); i != vector.end(); ++i)
            {
                if (i != vector.begin())
                    ret += "#";
                ret += i->getTypeName() + "#";
                ret += i->toString();
            }
            return ret;
        }
        
    case VAR_VARIANTMAP:
        {
            const VariantMap& map = *(reinterpret_cast<const VariantMap*>(mValue.mPtr));
            std::string ret;
            for (VariantMap::const_iterator i = map.begin(); i != map.end(); ++i)
            {
                if (i != map.begin())
                    ret += "#";
                ret += ::toString(i->first.mData) + "#";
                ret += i->second.getTypeName() + "#";
                ret += i->second.toString();
            }
            return ret;
        }
    }
    
    return std::string();
}

void Variant::setType(VariantType newType)
{
    if (mType == newType)
        return;
    
    switch (mType)
    {
    case VAR_STRING:
        delete reinterpret_cast<std::string*>(mValue.mPtr);
        break;
        
    case VAR_BUFFER:
        delete reinterpret_cast<std::vector<unsigned char>*>(mValue.mPtr);
        break;
        
    case VAR_VARIANTVECTOR:
        delete reinterpret_cast<VariantVector*>(mValue.mPtr);
        break;
        
    case VAR_VARIANTMAP:
        delete reinterpret_cast<VariantMap*>(mValue.mPtr);
        break;
    }
    
    mType = newType;
    
    switch (mType)
    {
    case VAR_STRING:
        *reinterpret_cast<std::string**>(&mValue.mPtr) = new std::string();
        break;
        
    case VAR_BUFFER:
        *reinterpret_cast<std::vector<unsigned char>**>(&mValue.mPtr) = new std::vector<unsigned char>();
        break;
        
    case VAR_VARIANTVECTOR:
        *reinterpret_cast<VariantVector**>(&mValue.mPtr) = new VariantVector();
        break;
        
    case VAR_VARIANTMAP:
        *reinterpret_cast<VariantMap**>(&mValue.mPtr) = new VariantMap();
        break;
    }
}
