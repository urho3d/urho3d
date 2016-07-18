//
// Copyright (c) 2008-2016 the Urho3D project.
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

#include "../Precompiled.h"

#include "../Core/StringUtils.h"
#include "../IO/VectorBuffer.h"

#include <cstring>

namespace Urho3D
{

const Variant Variant::EMPTY;
const PODVector<unsigned char> Variant::emptyBuffer;
const ResourceRef Variant::emptyResourceRef;
const ResourceRefList Variant::emptyResourceRefList;
const VariantMap Variant::emptyVariantMap;
const VariantVector Variant::emptyVariantVector;
const StringVector Variant::emptyStringVector;

static const char* typeNames[] =
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
    "VoidPtr",
    "ResourceRef",
    "ResourceRefList",
    "VariantVector",
    "VariantMap",
    "IntRect",
    "IntVector2",
    "Ptr",
    "Matrix3",
    "Matrix3x4",
    "Matrix4",
    "Double",
    "StringVector",
    0
};

Variant& Variant::operator =(const Variant& rhs)
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

    case VAR_STRINGVECTOR:
        *(reinterpret_cast<StringVector*>(&value_)) = *(reinterpret_cast<const StringVector*>(&rhs.value_));
        break;

    case VAR_VARIANTMAP:
        *(reinterpret_cast<VariantMap*>(&value_)) = *(reinterpret_cast<const VariantMap*>(&rhs.value_));
        break;

    case VAR_PTR:
        *(reinterpret_cast<WeakPtr<RefCounted>*>(&value_)) = *(reinterpret_cast<const WeakPtr<RefCounted>*>(&rhs.value_));
        break;

    case VAR_MATRIX3:
        *(reinterpret_cast<Matrix3*>(value_.ptr_)) = *(reinterpret_cast<const Matrix3*>(rhs.value_.ptr_));
        break;

    case VAR_MATRIX3X4:
        *(reinterpret_cast<Matrix3x4*>(value_.ptr_)) = *(reinterpret_cast<const Matrix3x4*>(rhs.value_.ptr_));
        break;

    case VAR_MATRIX4:
        *(reinterpret_cast<Matrix4*>(value_.ptr_)) = *(reinterpret_cast<const Matrix4*>(rhs.value_.ptr_));
        break;

    default:
        value_ = rhs.value_;
        break;
    }

    return *this;
}

Variant& Variant::operator =(const VectorBuffer& rhs)
{
    SetType(VAR_BUFFER);
    *(reinterpret_cast<PODVector<unsigned char>*>(&value_)) = rhs.GetBuffer();
    return *this;
}

bool Variant::operator ==(const Variant& rhs) const
{
    if (type_ == VAR_VOIDPTR || type_ == VAR_PTR)
        return GetVoidPtr() == rhs.GetVoidPtr();
    else if (type_ != rhs.type_)
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
        return *(reinterpret_cast<const PODVector<unsigned char>*>(&value_)) ==
               *(reinterpret_cast<const PODVector<unsigned char>*>(&rhs.value_));

    case VAR_RESOURCEREF:
        return *(reinterpret_cast<const ResourceRef*>(&value_)) == *(reinterpret_cast<const ResourceRef*>(&rhs.value_));

    case VAR_RESOURCEREFLIST:
        return *(reinterpret_cast<const ResourceRefList*>(&value_)) == *(reinterpret_cast<const ResourceRefList*>(&rhs.value_));

    case VAR_VARIANTVECTOR:
        return *(reinterpret_cast<const VariantVector*>(&value_)) == *(reinterpret_cast<const VariantVector*>(&rhs.value_));

    case VAR_STRINGVECTOR:
        return *(reinterpret_cast<const StringVector*>(&value_)) == *(reinterpret_cast<const StringVector*>(&rhs.value_));

    case VAR_VARIANTMAP:
        return *(reinterpret_cast<const VariantMap*>(&value_)) == *(reinterpret_cast<const VariantMap*>(&rhs.value_));

    case VAR_INTRECT:
        return *(reinterpret_cast<const IntRect*>(&value_)) == *(reinterpret_cast<const IntRect*>(&rhs.value_));

    case VAR_INTVECTOR2:
        return *(reinterpret_cast<const IntVector2*>(&value_)) == *(reinterpret_cast<const IntVector2*>(&rhs.value_));

    case VAR_MATRIX3:
        return *(reinterpret_cast<const Matrix3*>(value_.ptr_)) == *(reinterpret_cast<const Matrix3*>(rhs.value_.ptr_));

    case VAR_MATRIX3X4:
        return *(reinterpret_cast<const Matrix3x4*>(value_.ptr_)) == *(reinterpret_cast<const Matrix3x4*>(rhs.value_.ptr_));

    case VAR_MATRIX4:
        return *(reinterpret_cast<const Matrix4*>(value_.ptr_)) == *(reinterpret_cast<const Matrix4*>(rhs.value_.ptr_));

    case VAR_DOUBLE:
        return *(reinterpret_cast<const double*>(&value_)) == *(reinterpret_cast<const double*>(&rhs.value_));

    default:
        return true;
    }
}

bool Variant::operator ==(const PODVector<unsigned char>& rhs) const
{
    // Use strncmp() instead of PODVector<unsigned char>::operator ==()
    const PODVector<unsigned char>& buffer = *(reinterpret_cast<const PODVector<unsigned char>*>(&value_));
    return type_ == VAR_BUFFER && buffer.Size() == rhs.Size() ?
        strncmp(reinterpret_cast<const char*>(&buffer[0]), reinterpret_cast<const char*>(&rhs[0]), buffer.Size()) == 0 :
        false;
}

bool Variant::operator ==(const VectorBuffer& rhs) const
{
    const PODVector<unsigned char>& buffer = *(reinterpret_cast<const PODVector<unsigned char>*>(&value_));
    return type_ == VAR_BUFFER && buffer.Size() == rhs.GetSize() ?
        strncmp(reinterpret_cast<const char*>(&buffer[0]), reinterpret_cast<const char*>(rhs.GetData()), buffer.Size()) == 0 :
        false;
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
        StringToBuffer(buffer, value);
    }
        break;

    case VAR_VOIDPTR:
        // From string to void pointer not supported, set to null
        *this = (void*)0;
        break;

    case VAR_RESOURCEREF:
    {
        StringVector values = String::Split(value, ';');
        if (values.Size() == 2)
        {
            SetType(VAR_RESOURCEREF);
            ResourceRef& ref = *(reinterpret_cast<ResourceRef*>(&value_));
            ref.type_ = values[0];
            ref.name_ = values[1];
        }
    }
        break;

    case VAR_RESOURCEREFLIST:
    {
        StringVector values = String::Split(value, ';', true);
        if (values.Size() >= 1)
        {
            SetType(VAR_RESOURCEREFLIST);
            ResourceRefList& refList = *(reinterpret_cast<ResourceRefList*>(&value_));
            refList.type_ = values[0];
            refList.names_.Resize(values.Size() - 1);
            for (unsigned i = 1; i < values.Size(); ++i)
                refList.names_[i - 1] = values[i];
        }
    }
        break;

    case VAR_INTRECT:
        *this = ToIntRect(value);
        break;

    case VAR_INTVECTOR2:
        *this = ToIntVector2(value);
        break;

    case VAR_PTR:
        // From string to RefCounted pointer not supported, set to null
        *this = (RefCounted*)0;
        break;

    case VAR_MATRIX3:
        *this = ToMatrix3(value);
        break;

    case VAR_MATRIX3X4:
        *this = ToMatrix3x4(value);
        break;

    case VAR_MATRIX4:
        *this = ToMatrix4(value);
        break;

    case VAR_DOUBLE:
        *this = ToDouble(value);
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

VectorBuffer Variant::GetVectorBuffer() const
{
    return VectorBuffer(type_ == VAR_BUFFER ? *reinterpret_cast<const PODVector<unsigned char>*>(&value_) : emptyBuffer);
}

String Variant::GetTypeName() const
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
            BufferToString(ret, buffer.Begin().ptr_, buffer.Size());
            return ret;
        }

    case VAR_VOIDPTR:
    case VAR_PTR:
        // Pointer serialization not supported (convert to null)
        return String(0);

    case VAR_INTRECT:
        return (reinterpret_cast<const IntRect*>(&value_))->ToString();

    case VAR_INTVECTOR2:
        return (reinterpret_cast<const IntVector2*>(&value_))->ToString();

    case VAR_MATRIX3:
        return (reinterpret_cast<const Matrix3*>(value_.ptr_))->ToString();

    case VAR_MATRIX3X4:
        return (reinterpret_cast<const Matrix3x4*>(value_.ptr_))->ToString();

    case VAR_MATRIX4:
        return (reinterpret_cast<const Matrix4*>(value_.ptr_))->ToString();

    case VAR_DOUBLE:
        return String(*reinterpret_cast<const double*>(&value_));

    default:
        // VAR_RESOURCEREF, VAR_RESOURCEREFLIST, VAR_VARIANTVECTOR, VAR_STRINGVECTOR, VAR_VARIANTMAP
        // Reference string serialization requires typehash-to-name mapping from the context. Can not support here
        // Also variant map or vector string serialization is not supported. XML or binary save should be used instead
        return String::EMPTY;
    }
}

bool Variant::IsZero() const
{
    switch (type_)
    {
    case VAR_INT:
        return value_.int_ == 0;

    case VAR_BOOL:
        return value_.bool_ == false;

    case VAR_FLOAT:
        return value_.float_ == 0.0f;

    case VAR_VECTOR2:
        return *reinterpret_cast<const Vector2*>(&value_) == Vector2::ZERO;

    case VAR_VECTOR3:
        return *reinterpret_cast<const Vector3*>(&value_) == Vector3::ZERO;

    case VAR_VECTOR4:
        return *reinterpret_cast<const Vector4*>(&value_) == Vector4::ZERO;

    case VAR_QUATERNION:
        return *reinterpret_cast<const Quaternion*>(&value_) == Quaternion::IDENTITY;

    case VAR_COLOR:
        // WHITE is considered empty (i.e. default) color in the Color class definition
        return *reinterpret_cast<const Color*>(&value_) == Color::WHITE;

    case VAR_STRING:
        return reinterpret_cast<const String*>(&value_)->Empty();

    case VAR_BUFFER:
        return reinterpret_cast<const PODVector<unsigned char>*>(&value_)->Empty();

    case VAR_VOIDPTR:
        return value_.ptr_ == 0;

    case VAR_RESOURCEREF:
        return reinterpret_cast<const ResourceRef*>(&value_)->name_.Empty();

    case VAR_RESOURCEREFLIST:
    {
        const StringVector& names = reinterpret_cast<const ResourceRefList*>(&value_)->names_;
        for (StringVector::ConstIterator i = names.Begin(); i != names.End(); ++i)
        {
            if (!i->Empty())
                return false;
        }
        return true;
    }

    case VAR_VARIANTVECTOR:
        return reinterpret_cast<const VariantVector*>(&value_)->Empty();

    case VAR_STRINGVECTOR:
        return reinterpret_cast<const StringVector*>(&value_)->Empty();

    case VAR_VARIANTMAP:
        return reinterpret_cast<const VariantMap*>(&value_)->Empty();

    case VAR_INTRECT:
        return *reinterpret_cast<const IntRect*>(&value_) == IntRect::ZERO;

    case VAR_INTVECTOR2:
        return *reinterpret_cast<const IntVector2*>(&value_) == IntVector2::ZERO;

    case VAR_PTR:
        return *reinterpret_cast<const WeakPtr<RefCounted>*>(&value_) == (RefCounted*)0;

    case VAR_MATRIX3:
        return *reinterpret_cast<const Matrix3*>(value_.ptr_) == Matrix3::IDENTITY;

    case VAR_MATRIX3X4:
        return *reinterpret_cast<const Matrix3x4*>(value_.ptr_) == Matrix3x4::IDENTITY;

    case VAR_MATRIX4:
        return *reinterpret_cast<const Matrix4*>(value_.ptr_) == Matrix4::IDENTITY;

    case VAR_DOUBLE:
        return *reinterpret_cast<const double*>(&value_) == 0.0;

    default:
        return true;
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

    case VAR_STRINGVECTOR:
        (reinterpret_cast<StringVector*>(&value_))->~StringVector();
        break;

    case VAR_VARIANTMAP:
        (reinterpret_cast<VariantMap*>(&value_))->~VariantMap();
        break;

    case VAR_PTR:
        (reinterpret_cast<WeakPtr<RefCounted>*>(&value_))->~WeakPtr<RefCounted>();
        break;

    case VAR_MATRIX3:
        delete reinterpret_cast<Matrix3*>(value_.ptr_);
        break;

    case VAR_MATRIX3X4:
        delete reinterpret_cast<Matrix3x4*>(value_.ptr_);
        break;

    case VAR_MATRIX4:
        delete reinterpret_cast<Matrix4*>(value_.ptr_);
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

    case VAR_STRINGVECTOR:
        new(reinterpret_cast<StringVector*>(&value_)) StringVector();
        break;

    case VAR_VARIANTMAP:
        new(reinterpret_cast<VariantMap*>(&value_)) VariantMap();
        break;

    case VAR_PTR:
        new(reinterpret_cast<WeakPtr<RefCounted>*>(&value_)) WeakPtr<RefCounted>();
        break;

    case VAR_MATRIX3:
        value_.ptr_ = new Matrix3();
        break;

    case VAR_MATRIX3X4:
        value_.ptr_ = new Matrix3x4();
        break;

    case VAR_MATRIX4:
        value_.ptr_ = new Matrix4();
        break;

    default:
        break;
    }
}

template <> int Variant::Get<int>() const
{
    return GetInt();
}

template <> unsigned Variant::Get<unsigned>() const
{
    return GetUInt();
}

template <> StringHash Variant::Get<StringHash>() const
{
    return GetStringHash();
}

template <> bool Variant::Get<bool>() const
{
    return GetBool();
}

template <> float Variant::Get<float>() const
{
    return GetFloat();
}

template <> double Variant::Get<double>() const
{
    return GetDouble();
}

template <> const Vector2& Variant::Get<const Vector2&>() const
{
    return GetVector2();
}

template <> const Vector3& Variant::Get<const Vector3&>() const
{
    return GetVector3();
}

template <> const Vector4& Variant::Get<const Vector4&>() const
{
    return GetVector4();
}

template <> const Quaternion& Variant::Get<const Quaternion&>() const
{
    return GetQuaternion();
}

template <> const Color& Variant::Get<const Color&>() const
{
    return GetColor();
}

template <> const String& Variant::Get<const String&>() const
{
    return GetString();
}

template <> const IntRect& Variant::Get<const IntRect&>() const
{
    return GetIntRect();
}

template <> const IntVector2& Variant::Get<const IntVector2&>() const
{
    return GetIntVector2();
}

template <> const PODVector<unsigned char>& Variant::Get<const PODVector<unsigned char>&>() const
{
    return GetBuffer();
}

template <> void* Variant::Get<void*>() const
{
    return GetVoidPtr();
}

template <> RefCounted* Variant::Get<RefCounted*>() const
{
    return GetPtr();
}

template <> const Matrix3& Variant::Get<const Matrix3&>() const
{
    return GetMatrix3();
}

template <> const Matrix3x4& Variant::Get<const Matrix3x4&>() const
{
    return GetMatrix3x4();
}

template <> const Matrix4& Variant::Get<const Matrix4&>() const
{
    return GetMatrix4();
}

template <> ResourceRef Variant::Get<ResourceRef>() const
{
    return GetResourceRef();
}

template <> ResourceRefList Variant::Get<ResourceRefList>() const
{
    return GetResourceRefList();
}

template <> VariantVector Variant::Get<VariantVector>() const
{
    return GetVariantVector();
}

template <> StringVector Variant::Get<StringVector >() const
{
    return GetStringVector();
}

template <> VariantMap Variant::Get<VariantMap>() const
{
    return GetVariantMap();
}

template <> Vector2 Variant::Get<Vector2>() const
{
    return GetVector2();
}

template <> Vector3 Variant::Get<Vector3>() const
{
    return GetVector3();
}

template <> Vector4 Variant::Get<Vector4>() const
{
    return GetVector4();
}

template <> Quaternion Variant::Get<Quaternion>() const
{
    return GetQuaternion();
}

template <> Color Variant::Get<Color>() const
{
    return GetColor();
}

template <> String Variant::Get<String>() const
{
    return GetString();
}

template <> IntRect Variant::Get<IntRect>() const
{
    return GetIntRect();
}

template <> IntVector2 Variant::Get<IntVector2>() const
{
    return GetIntVector2();
}

template <> PODVector<unsigned char> Variant::Get<PODVector<unsigned char> >() const
{
    return GetBuffer();
}

template <> Matrix3 Variant::Get<Matrix3>() const
{
    return GetMatrix3();
}

template <> Matrix3x4 Variant::Get<Matrix3x4>() const
{
    return GetMatrix3x4();
}

template <> Matrix4 Variant::Get<Matrix4>() const
{
    return GetMatrix4();
}

String Variant::GetTypeName(VariantType type)
{
    return typeNames[type];
}

VariantType Variant::GetTypeFromName(const String& typeName)
{
    return GetTypeFromName(typeName.CString());
}

VariantType Variant::GetTypeFromName(const char* typeName)
{
    return (VariantType)GetStringListIndex(typeName, typeNames, VAR_NONE);
}

}
