//
// Urho3D Engine
// Copyright (c) 2008-2012 Lasse Öörni
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
#include "StringUtils.h"
#include "Variant.h"

#include <cstring>

namespace Urho3D
{

const Variant Variant::EMPTY;
const PODVector<unsigned char> Variant::emptyBuffer;
const ResourceRef Variant::emptyResourceRef;
const ResourceRefList Variant::emptyResourceRefList;
const VariantMap Variant::emptyVariantMap;
const VariantVector Variant::emptyVariantVector;

static const String typeNames[] =
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
    "ResourceRef",
    "ResourceRefList",
    "VariantVector",
    "VariantMap",
    "IntRect",
    "IntVector2"
    ""
};

Variant& Variant::operator = (const Variant& rhs)
{
    SetType(rhs.GetType());
    
    switch (type_)
    {
    case VAR_STRING:
        *(reinterpret_cast<String*>(&value_)) = *(reinterpret_cast<const String*>(&rhs.value_));
        break;
        
    case VAR_BUFFER:
        *(reinterpret_cast<PODVector<unsigned char>*>(&value_)) = *(reinterpret_cast<const PODVector<unsigned char>*>(&rhs.value_));
        break;
    
    case VAR_RESOURCEREF:
        *(reinterpret_cast<ResourceRef*>(&value_)) = *(reinterpret_cast<const ResourceRef*>(&rhs.value_));
        break;
        
    case VAR_RESOURCEREFLIST:
        *(reinterpret_cast<ResourceRefList*>(&value_)) = *(reinterpret_cast<const ResourceRefList*>(&rhs.value_));
        break;
        
    case VAR_VARIANTVECTOR:
        *(reinterpret_cast<VariantVector*>(&value_)) = *(reinterpret_cast<const VariantVector*>(&rhs.value_));
        break;
        
    case VAR_VARIANTMAP:
        *(reinterpret_cast<VariantMap*>(&value_)) = *(reinterpret_cast<const VariantMap*>(&rhs.value_));
        break;
        
    default:
        value_ = rhs.value_;
        break;
    }
    
    return *this;
}

bool Variant::operator == (const Variant& rhs) const
{
    if (type_ != rhs.type_)
        return false;
    
    switch (type_)
    {
    case VAR_INT:
        return value_.int_ == rhs.value_.int_;
        
    case VAR_BOOL:
        return value_.bool_ == rhs.value_.bool_;
        
    case VAR_FLOAT:
        return value_.float_ == rhs.value_.float_;
        
    case VAR_VECTOR2:
        return *(reinterpret_cast<const Vector2*>(&value_)) == *(reinterpret_cast<const Vector2*>(&rhs.value_));
        
    case VAR_VECTOR3:
        return *(reinterpret_cast<const Vector3*>(&value_)) == *(reinterpret_cast<const Vector3*>(&rhs.value_));
        
    case VAR_VECTOR4:
    case VAR_QUATERNION:
    case VAR_COLOR:
        // Hack: use the Vector4 compare for all these classes, as they have the same memory structure
        return *(reinterpret_cast<const Vector4*>(&value_)) == *(reinterpret_cast<const Vector4*>(&rhs.value_));
        
    case VAR_STRING:
        return *(reinterpret_cast<const String*>(&value_)) == *(reinterpret_cast<const String*>(&rhs.value_));
        
    case VAR_BUFFER:
        return *(reinterpret_cast<const PODVector<unsigned char>*>(&value_)) == *(reinterpret_cast<const PODVector<unsigned char>*>(&rhs.value_));
        
    case VAR_PTR:
        return value_.ptr_ == rhs.value_.ptr_;
        
    case VAR_RESOURCEREF:
        return *(reinterpret_cast<const ResourceRef*>(&value_)) == *(reinterpret_cast<const ResourceRef*>(&rhs.value_));
        
    case VAR_RESOURCEREFLIST:
        return *(reinterpret_cast<const ResourceRefList*>(&value_)) == *(reinterpret_cast<const ResourceRefList*>(&rhs.value_));
        
    case VAR_VARIANTVECTOR:
        return *(reinterpret_cast<const VariantVector*>(&value_)) == *(reinterpret_cast<const VariantVector*>(&rhs.value_));
        
    case VAR_VARIANTMAP:
        return *(reinterpret_cast<const VariantMap*>(&value_)) == *(reinterpret_cast<const VariantMap*>(&rhs.value_));
        
    case VAR_INTRECT:
        return *(reinterpret_cast<const IntRect*>(&value_)) == *(reinterpret_cast<const IntRect*>(&rhs.value_));
        
    case VAR_INTVECTOR2:
        return *(reinterpret_cast<const IntVector2*>(&value_)) == *(reinterpret_cast<const IntVector2*>(&rhs.value_));
        
    default:
        return true;
    }
}

void Variant::FromString(const String& type, const String& value)
{
    return FromString(GetTypeFromName(type), value.CString());
}

void Variant::FromString(const char* type, const char* value)
{
    return FromString(GetTypeFromName(type), value);
}

void Variant::FromString(VariantType type, const String& value)
{
    return FromString(type, value.CString());
}

void Variant::FromString(VariantType type, const char* value)
{
    switch (type)
    {
    case VAR_INT:
        *this = ToInt(value);
        break;
        
    case VAR_BOOL:
        *this = ToBool(value);
        break;
        
    case VAR_FLOAT:
        *this = ToFloat(value);
        break;
        
    case VAR_VECTOR2:
        *this = ToVector2(value);
        break;
        
    case VAR_VECTOR3:
        *this = ToVector3(value);
        break;
        
    case VAR_VECTOR4:
        *this = ToVector4(value);
        break;
        
    case VAR_QUATERNION:
        *this = ToQuaternion(value);
        break;
        
    case VAR_COLOR:
        *this = ToColor(value);
        break;
        
    case VAR_STRING:
        *this = value;
        break;
        
    case VAR_BUFFER:
        {
            SetType(VAR_BUFFER);
            PODVector<unsigned char>& buffer = *(reinterpret_cast<PODVector<unsigned char>*>(&value_));
            Vector<String> values = String::Split(value, ' ');
            buffer.Resize(values.Size());
            for (unsigned i = 0; i < values.Size(); ++i)
                buffer[i] = ToInt(values[i]);
        }
        break;
        
    case VAR_PTR:
        *this = (void*)0;
        break;
        
    case VAR_RESOURCEREF:
        {
            Vector<String> values = String::Split(value, ';');
            if (values.Size() == 2)
            {
                SetType(VAR_RESOURCEREF);
                ResourceRef& ref = *(reinterpret_cast<ResourceRef*>(&value_));
                ref.type_ = ShortStringHash(values[0]);
                ref.id_ = StringHash(values[1]);
            }
        }
        break;
        
    case VAR_RESOURCEREFLIST:
        {
            Vector<String> values = String::Split(value, ';');
            if (values.Size() >= 1)
            {
                SetType(VAR_RESOURCEREFLIST);
                ResourceRefList& refList = *(reinterpret_cast<ResourceRefList*>(&value_));
                refList.type_ = ShortStringHash(values[0]);
                refList.ids_.Resize(values.Size() - 1);
                for (unsigned i = 1; i < values.Size(); ++i)
                    refList.ids_[i - 1] = StringHash(values[i]);
            }
        }
        break;
        
    case VAR_INTRECT:
        *this = ToIntRect(value);
        break;
        
    case VAR_INTVECTOR2:
        *this = ToIntVector2(value);
        break;
        
    default:
        SetType(VAR_NONE);
    }
}

void Variant::SetBuffer(const void* data, unsigned size)
{
    if (size && !data)
        size = 0;
    
    SetType(VAR_BUFFER);
    PODVector<unsigned char>& buffer = *(reinterpret_cast<PODVector<unsigned char>*>(&value_));
    buffer.Resize(size);
    if (size)
        memcpy(&buffer[0], data, size);
}

const String& Variant::GetTypeName() const
{
    return typeNames[type_];
}

String Variant::ToString() const
{
    switch (type_)
    {
    case VAR_INT:
        return String(value_.int_);
        
    case VAR_BOOL:
        return String(value_.bool_);
        
    case VAR_FLOAT:
        return String(value_.float_);
        
    case VAR_VECTOR2:
        return (reinterpret_cast<const Vector2*>(&value_))->ToString();
        
    case VAR_VECTOR3:
        return (reinterpret_cast<const Vector3*>(&value_))->ToString();
        
    case VAR_VECTOR4:
        return (reinterpret_cast<const Vector4*>(&value_))->ToString();
        
    case VAR_QUATERNION:
        return (reinterpret_cast<const Quaternion*>(&value_))->ToString();
        
    case VAR_COLOR:
        return (reinterpret_cast<const Color*>(&value_))->ToString();
        
    case VAR_STRING:
        return *(reinterpret_cast<const String*>(&value_));
        
    case VAR_BUFFER:
        {
            const PODVector<unsigned char>& buffer = *(reinterpret_cast<const PODVector<unsigned char>*>(&value_));
            String ret;
            for (PODVector<unsigned char>::ConstIterator i = buffer.Begin(); i != buffer.End(); ++i)
            {
                if (i != buffer.Begin())
                    ret += " ";
                ret += String((unsigned)*i);
            }
            return ret;
        }
        
    case VAR_PTR:
        // Pointer serialization not supported (convert to null)
        return String(0);
        
    case VAR_RESOURCEREF:
    case VAR_RESOURCEREFLIST:
    case VAR_VARIANTVECTOR:
    case VAR_VARIANTMAP:
        // Reference string serialization requires hash-to-name mapping from the context & subsystems. Can not support here
        // Also variant map or vector string serialization is not supported. XML or binary save should be used instead
        return String();
        
    case VAR_INTRECT:
        return (reinterpret_cast<const IntRect*>(&value_))->ToString();
        
    case VAR_INTVECTOR2:
        return (reinterpret_cast<const IntRect*>(&value_))->ToString();
        
    default:
        return String();
    }
}

void Variant::SetType(VariantType newType)
{
    if (type_ == newType)
        return;
    
    switch (type_)
    {
    case VAR_STRING:
        (reinterpret_cast<String*>(&value_))->~String();
        break;
        
    case VAR_BUFFER:
        (reinterpret_cast<PODVector<unsigned char>*>(&value_))->~PODVector<unsigned char>();
        break;
        
    case VAR_RESOURCEREF:
        (reinterpret_cast<ResourceRef*>(&value_))->~ResourceRef();
        break;
        
    case VAR_RESOURCEREFLIST:
        (reinterpret_cast<ResourceRefList*>(&value_))->~ResourceRefList();
        break;
        
    case VAR_VARIANTVECTOR:
        (reinterpret_cast<VariantVector*>(&value_))->~VariantVector();
        break;
        
    case VAR_VARIANTMAP:
        (reinterpret_cast<VariantMap*>(&value_))->~VariantMap();
        break;
        
    default:
        break;
    }
    
    type_ = newType;
    
    switch (type_)
    {
    case VAR_STRING:
        new(reinterpret_cast<String*>(&value_)) String();
        break;
        
    case VAR_BUFFER:
        new(reinterpret_cast<PODVector<unsigned char>*>(&value_)) PODVector<unsigned char>();
        break;
        
    case VAR_RESOURCEREF:
        new(reinterpret_cast<ResourceRef*>(&value_)) ResourceRef();
        break;
        
    case VAR_RESOURCEREFLIST:
        new(reinterpret_cast<ResourceRefList*>(&value_)) ResourceRefList();
        break;
        
    case VAR_VARIANTVECTOR:
        new(reinterpret_cast<VariantVector*>(&value_)) VariantVector();
        break;
        
    case VAR_VARIANTMAP:
        new(reinterpret_cast<VariantMap*>(&value_)) VariantMap();
        break;
        
    default:
        break;
    }
}

template<> int Variant::Get<int>() const
{
    return GetInt();
}

template<> unsigned Variant::Get<unsigned>() const
{
    return GetUInt();
}

template<> StringHash Variant::Get<StringHash>() const
{
    return GetStringHash();
}

template<> ShortStringHash Variant::Get<ShortStringHash>() const
{
    return GetShortStringHash();
}

template<> bool Variant::Get<bool>() const
{
    return GetBool();
}

template<> float Variant::Get<float>() const
{
    return GetFloat();
}

template<> const Vector2& Variant::Get<const Vector2&>() const
{
    return GetVector2();
}

template<> const Vector3& Variant::Get<const Vector3&>() const
{
    return GetVector3();
}

template<> const Vector4& Variant::Get<const Vector4&>() const
{
    return GetVector4();
}

template<> const Quaternion& Variant::Get<const Quaternion&>() const
{
    return GetQuaternion();
}

template<> const Color& Variant::Get<const Color&>() const
{
    return GetColor();
}

template<> const String& Variant::Get<const String&>() const
{
    return GetString();
}

template<> const IntRect& Variant::Get<const IntRect&>() const
{
    return GetIntRect();
}

template<> const IntVector2& Variant::Get<const IntVector2&>() const
{
    return GetIntVector2();
}

template<> const PODVector<unsigned char>& Variant::Get<const PODVector<unsigned char>& >() const
{
    return GetBuffer();
}

template<> void* Variant::Get<void*>() const
{
    return GetPtr();
}

template<> ResourceRef Variant::Get<ResourceRef>() const
{
    return GetResourceRef();
}

template<> ResourceRefList Variant::Get<ResourceRefList>() const
{
    return GetResourceRefList();
}

template<> VariantVector Variant::Get<VariantVector>() const
{
    return GetVariantVector();
}

template<> VariantMap Variant::Get<VariantMap>() const
{
    return GetVariantMap();
}

template<> Vector2 Variant::Get<Vector2>() const
{
    return GetVector2();
}

template<> Vector3 Variant::Get<Vector3>() const
{
    return GetVector3();
}

template<> Vector4 Variant::Get<Vector4>() const
{
    return GetVector4();
}

template<> Quaternion Variant::Get<Quaternion>() const
{
    return GetQuaternion();
}

template<> Color Variant::Get<Color>() const
{
    return GetColor();
}

template<> String Variant::Get<String>() const
{
    return GetString();
}

template<> IntRect Variant::Get<IntRect>() const
{
    return GetIntRect();
}

template<> IntVector2 Variant::Get<IntVector2>() const
{
    return GetIntVector2();
}

template<> PODVector<unsigned char> Variant::Get<PODVector<unsigned char> >() const
{
    return GetBuffer();
}

const String& Variant::GetTypeName(VariantType type)
{
    return typeNames[type];
}

VariantType Variant::GetTypeFromName(const String& typeName)
{
    return GetTypeFromName(typeName.CString());
}

VariantType Variant::GetTypeFromName(const char* typeName)
{
    unsigned index = 0;
    while (!typeNames[index].Empty())
    {
        if (!typeNames[index].Compare(typeName, false))
            return (VariantType)index;
        ++index;
    }
    
    return VAR_NONE;
}

}
