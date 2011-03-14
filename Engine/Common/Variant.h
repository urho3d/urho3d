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

#ifndef COMMON_VARIANT_H
#define COMMON_VARIANT_H

#include "Color.h"
#include "Quaternion.h"
#include "StringHash.h"
#include "Vector4.h"

#include <map>
#include <vector>

//! Supported variable types for Variant
enum VariantType
{
    VAR_NONE = 0,
    VAR_INT,
    VAR_BOOL,
    VAR_FLOAT,
    VAR_VECTOR2,
    VAR_VECTOR3,
    VAR_VECTOR4,
    VAR_QUATERNION,
    VAR_COLOR,
    VAR_STRING,
    VAR_BUFFER,
    VAR_PTR,
    VAR_VARIANTVECTOR,
    VAR_VARIANTMAP
};

//! Union for holding all the possible Variant values
struct VariantValue
{
    union
    {
        int mInt;
        bool mBool;
        float mFloat;
        void* mPtr;
    };
    
    float mY;
    float mZ;
    float mW;
};

class Deserializer;
class Serializer;
class Variant;

//! Vector of variants
typedef std::vector<Variant> VariantVector;
//! Map of variants
typedef std::map<ShortStringHash, Variant> VariantMap;

//! A varying type with support for a fixed set of types
class Variant
{
public:
    //! Construct with none value
    Variant() :
        mType(VAR_NONE)
    {
    }
    
    //! Construct from integer
    Variant(int value) :
        mType(VAR_NONE)
    {
        *this = value;
    }
    
    //! Construct from unsigned integer
    Variant(unsigned value) :
        mType(VAR_NONE)
    {
        *this = (int)value;
    }
    
    //! Construct from a StringHash (convert to integer)
    Variant(const StringHash& value) :
        mType(VAR_NONE)
    {
        *this = (int)value.mData;
    }
    
    //! Construct from a ShortStringHash (convert to integer)
    Variant(const ShortStringHash& value) :
        mType(VAR_NONE)
    {
        *this = (int)value.mData;
    }
    
    //! Construct from a bool
    Variant(bool value) :
        mType(VAR_NONE)
    {
        *this = value;
    }
    
    //! Construct from a float
    Variant(float value) :
        mType(VAR_NONE)
    {
        *this = value;
    }
    
    //! Construct from a Vector2
    Variant(const Vector2& value) :
        mType(VAR_NONE)
    {
        *this = value;
    }
    
    //! Construct from a Vector3
    Variant(const Vector3& value) :
        mType(VAR_NONE)
    {
        *this = value;
    }
    
    //! Construct from a Vector4
    Variant(const Vector4& value) :
        mType(VAR_NONE)
    {
        *this = value;
    }
    
    //! Construct from a Quaternion
    Variant(const Quaternion& value) :
        mType(VAR_NONE)
    {
        *this = value;
    }
    
    //! Construct from a Color
    Variant(const Color& value) :
        mType(VAR_NONE)
    {
        *this = value;
    }
    
    //! Construct from a string
    Variant(const std::string& value) :
        mType(VAR_NONE)
    {
        *this = value;
    }
    
    //! Construct from a buffer
    Variant(const std::vector<unsigned char>& value) :
        mType(VAR_NONE)
    {
        *this = value;
    }
    
    //! Construct from a pointer
    Variant(void* value) :
        mType(VAR_NONE)
    {
        *this = value;
    }
    
    //! Construct from a variant vector
    Variant(const VariantVector& value) :
        mType(VAR_NONE)
    {
        *this = value;
    }
    
    //! Construct from a variant vector
    Variant(const VariantMap& value) :
        mType(VAR_NONE)
    {
        *this = value;
    }
    
    //! Construct from type and value
    Variant(const std::string& type, const std::string& value) :
        mType(VAR_NONE)
    {
        fromString(type, value);
    }
    
    //! Copy-construct from another variant
    Variant(const Variant& value) :
        mType(VAR_NONE)
    {
        *this = value;
    }
    
    //! Destruct
    ~Variant()
    {
        setType(VAR_NONE);
    }
    
    //! Reset to none type
    void clear()
    {
        setType(VAR_NONE);
    }
    
    //! Assign from another variant
    Variant& operator = (const Variant& rhs);
    
    //! Assign from an integer
    Variant& operator = (int rhs)
    {
        setType(VAR_INT);
        mValue.mInt = rhs;
        return *this;
    }
    
    //! Assign from an unsigned integer
    Variant& operator = (unsigned rhs)
    {
        setType(VAR_INT);
        mValue.mInt = (int)rhs;
        return *this;
    }
    
    //! Assign from a StringHash (convert to integer)
    Variant& operator = (const StringHash& rhs)
    {
        setType(VAR_INT);
        mValue.mInt = (int)rhs.mData;
        return *this;
    }
    
    //! Assign from a ShortStringHash (convert to integer)
    Variant& operator = (const ShortStringHash& rhs)
    {
        setType(VAR_INT);
        mValue.mInt = (int)rhs.mData;
        return *this;
    }
    
    //! Assign from a bool
    Variant& operator = (bool rhs)
    {
        setType(VAR_BOOL);
        mValue.mBool = rhs;
        return *this;
    }
    
    //! Assign from a float
    Variant& operator = (float rhs)
    {
        setType(VAR_FLOAT);
        mValue.mFloat = rhs;
        return *this;
    }
    
    //! Assign from a Vector2
    Variant& operator = (const Vector2& rhs)
    {
        setType(VAR_VECTOR2);
        *(reinterpret_cast<Vector2*>(&mValue)) = rhs;
        return *this;
    }
    
    //! Assign from a Vector3
    Variant& operator = (const Vector3& rhs)
    {
        setType(VAR_VECTOR3);
        *(reinterpret_cast<Vector3*>(&mValue)) = rhs;
        return *this;
    }
    
    //! Assign from a Vector4
    Variant& operator = (const Vector4& rhs)
    {
        setType(VAR_VECTOR4);
        *(reinterpret_cast<Vector4*>(&mValue)) = rhs;
        return *this;
    }
    
    //! Assign from a Quaternion
    Variant& operator = (const Quaternion& rhs)
    {
        setType(VAR_QUATERNION);
        *(reinterpret_cast<Quaternion*>(&mValue)) = rhs;
        return *this;
    }
    
    //! Assign from a Color
    Variant& operator = (const Color& rhs)
    {
        setType(VAR_COLOR);
        *(reinterpret_cast<Color*>(&mValue)) = rhs;
        return *this;
    }
    
    //! Assign from a string
    Variant& operator = (const std::string& rhs)
    {
        setType(VAR_STRING);
        *(reinterpret_cast<std::string*>(mValue.mPtr)) = rhs;
        return *this;
    }
    
    //! Assign from a buffer
    Variant& operator = (const std::vector<unsigned char>& rhs)
    {
        setType(VAR_BUFFER);
        *(reinterpret_cast<std::vector<unsigned char>*>(mValue.mPtr)) = rhs;
        return *this;
    }
    
    //! Assign from a pointer
    Variant& operator = (void* rhs)
    {
        setType(VAR_PTR);
        mValue.mPtr = rhs;
        return *this;
    }
    
    //! Assign from a variant vector
    Variant& operator = (const VariantVector& rhs)
    {
        setType(VAR_VARIANTVECTOR);
        *(reinterpret_cast<VariantVector*>(mValue.mPtr)) = rhs;
        return *this;
    }
    
    //! Assign from a variant map
    Variant& operator = (const VariantMap& rhs)
    {
        setType(VAR_VARIANTMAP);
        *(reinterpret_cast<VariantMap*>(mValue.mPtr)) = rhs;
        return *this;
    }
    
    //! Test for equality with another variant
    bool operator == (const Variant& rhs) const;
    
    //! Test for inequality with another variant
    bool operator != (const Variant& rhs) const
    {
        return !(*this == rhs);
    }
    
    //! Test for equality with an integer. To return true, both the type and value must match
    bool operator == (int rhs) const
    {
        if (mType == VAR_INT)
            return mValue.mInt == rhs;
        else
            return false;
    }
    
    //! Test for equality with an unsigned integer. To return true, both the type and value must match
    bool operator == (unsigned rhs) const
    {
        if (mType == VAR_INT)
            return mValue.mInt == (int)rhs;
        else
            return false;
    }
    
    //! Test for equality with a bool. To return true, both the type and value must match
    bool operator == (bool rhs) const
    {
        if (mType == VAR_BOOL)
            return mValue.mBool == rhs;
        else
            return false;
    }
    
    //! Test for equality with a float. To return true, both the type and value must match
    bool operator == (float rhs) const
    {
        if (mType == VAR_FLOAT)
            return mValue.mFloat == rhs;
        else
            return false;
    }
    
    //! Test for equality with a Vector2. To return true, both the type and value must match
    bool operator == (const Vector2& rhs) const
    {
        if (mType == VAR_VECTOR2)
            return *(reinterpret_cast<const Vector2*>(&mValue)) == rhs;
        else
            return false;
    }
    
    //! Test for equality with a Vector3. To return true, both the type and value must match
    bool operator == (const Vector3& rhs) const
    {
        if (mType == VAR_VECTOR3)
            return *(reinterpret_cast<const Vector3*>(&mValue)) == rhs;
        else
            return false;
    }
    
    //! Test for equality with a Vector4. To return true, both the type and value must match
    bool operator == (const Vector4& rhs) const
    {
        if (mType == VAR_VECTOR4)
            return *(reinterpret_cast<const Vector4*>(&mValue)) == rhs;
        else
            return false;
    }
    
    //! Test for equality with a Quaternion. To return true, both the type and value must match
    bool operator == (const Quaternion& rhs) const
    {
        if (mType == VAR_QUATERNION)
            return *(reinterpret_cast<const Quaternion*>(&mValue)) == rhs;
        else
            return false;
    }
    
    //! Test for equality with a Color. To return true, both the type and value must match
    bool operator == (const Color& rhs) const
    {
        if (mType == VAR_COLOR)
            return *(reinterpret_cast<const Color*>(&mValue)) == rhs;
        else
            return false;
    }
    
    //! Test for equality with a string. To return true, both the type and value must match
    bool operator == (const std::string& rhs) const
    {
        if (mType == VAR_STRING)
            return *(reinterpret_cast<const std::string*>(mValue.mPtr)) == rhs;
        else
            return false;
    }
    
    //! Test for equality with a buffer. To return true, both the type and value must match
    bool operator == (const std::vector<unsigned char>& rhs) const
    {
        if (mType == VAR_BUFFER)
            return *(reinterpret_cast<const std::vector<unsigned char>*>(mValue.mPtr)) == rhs;
        else
            return false;
    }
    
    //! Test for equality with a pointer. To return true, both the type and value must match
    bool operator == (void* rhs) const
    {
        if (mType == VAR_PTR)
            return mValue.mPtr == rhs;
        else
            return false;
    }
    
    //! Test for equality with a variant vector. To return true, both the type and value must match
    bool operator == (const VariantVector& rhs) const
    {
        if (mType == VAR_VARIANTVECTOR)
            return *(reinterpret_cast<VariantVector*>(mValue.mPtr)) == rhs;
        else
            return false;
    }
    
    //! Test for equality with a variant map. To return true, both the type and value must match
    bool operator == (const VariantMap& rhs) const
    {
        if (mType == VAR_VARIANTMAP)
            return *(reinterpret_cast<VariantMap*>(mValue.mPtr)) == rhs;
        else
            return false;
    }
    
    //! Test for equality with a StringHash. To return true, both the type and value must match
    bool operator == (const StringHash& rhs) const
    {
        if (mType == VAR_INT)
            return mValue.mInt == rhs.mData;
        else
            return false;
    }
    
    //! Test for equality with a ShortStringHash. To return true, both the type and value must match
    bool operator == (const ShortStringHash& rhs) const
    {
        if (mType == VAR_INT)
            return mValue.mInt == rhs.mData;
        else
            return false;
    }
    
    //! Test for inequality with an integer
    bool operator != (int rhs) const
    {
        return !(*this == rhs);
    }
    
    //! Test for inequality with an unsigned integer
    bool operator != (unsigned rhs) const
    {
        return !(*this == rhs);
    }
    
    //! Test for inequality with a bool
    bool operator != (bool rhs) const
    {
        return !(*this == rhs);
    }
    
    //! Test for inequality with a float
    bool operator != (float rhs) const
    {
        return !(*this == rhs);
    }
    
    //! Test for inequality with a Vector2
    bool operator != (const Vector2& rhs) const
    {
        return !(*this == rhs);
    }
    
    //! Test for inequality with a Vector3
    bool operator != (const Vector3& rhs) const
    {
        return !(*this == rhs);
    }
    
    //! Test for inequality with an Vector4
    bool operator != (const Vector4& rhs) const
    {
        return !(*this == rhs);
    }
    
    //! Test for inequality with a Quaternion
    bool operator != (const Quaternion& rhs) const
    {
        return !(*this == rhs);
    }
    
    //! Test for inequality with a string
    bool operator != (const std::string& rhs) const
    {
        return !(*this == rhs);
    }
    
    //! Test for inequality with a buffer
    bool operator != (const std::vector<unsigned char>& rhs) const
    {
        return !(*this == rhs);
    }
    
    //! Test for inequality with a variant vector
    bool operator != (const VariantVector& rhs) const
    {
        return !(*this == rhs);
    }
    
    //! Test for inequality with a variant map
    bool operator != (const VariantMap& rhs) const
    {
        return !(*this == rhs);
    }
    
    //! Test for inequality with a StringHash
    bool operator != (const StringHash& rhs) const
    {
        return !(*this == rhs);
    }
    
    //! Test for inequality with a ShortStringHash
    bool operator != (const ShortStringHash& rhs) const
    {
        return !(*this == rhs);
    }
    
    //! Return an integer, 0 if type mismatch
    int getInt() const
    {
        if (mType != VAR_INT)
            return 0;
        return mValue.mInt;
    }
    
    //! Return an unsigned integer, 0 if type mismatch
    unsigned getUInt() const
    {
        if (mType != VAR_INT)
            return 0;
        return (unsigned)mValue.mInt;
    }
    
    //! Return a StringHash, zero hash if type mismatch
    StringHash getStringHash() const
    {
        static const StringHash noStringHash;
        
        if (mType != VAR_INT)
            return noStringHash;
        StringHash ret;
        ret.mData = mValue.mInt;
        return ret;
    }
    
    //! Return a ShortStringHash, zero hash if type mismatch
    ShortStringHash getShortStringHash() const
    {
        static const ShortStringHash noShortStringHash;
        
        if (mType != VAR_INT)
            return noShortStringHash;
        ShortStringHash ret;
        ret.mData = mValue.mInt;
        return ret;
    }
    
    //! Return a bool, false if type mismatch
    bool getBool() const
    {
        if (mType != VAR_BOOL)
            return false;
        return mValue.mBool;
    }
    
    //! Return a float, 0.0 if type mismatch
    float getFloat() const
    {
        if (mType != VAR_FLOAT)
            return 0.0f;
        return mValue.mFloat;
    }
    
    //! Return a Vector2, zero vector if type mismatch
    const Vector2& getVector2() const
    {
        if (mType != VAR_VECTOR2)
            return Vector2::sZero;
        return *reinterpret_cast<const Vector2*>(&mValue);
    }
    
    //! Return a Vector3, zero vector if type mismatch
    const Vector3& getVector3() const
    {
        if (mType != VAR_VECTOR3)
            return Vector3::sZero;
        return *reinterpret_cast<const Vector3*>(&mValue);
    }
    
    //! Return a Vector4, zero vector if type mismatch
    const Vector4& getVector4() const
    {
        if (mType != VAR_VECTOR4)
            return Vector4::sZero;
        return *reinterpret_cast<const Vector4*>(&mValue);
    }
    
    //! Return a Quaternion, identity if type mismatch
    const Quaternion& getQuaternion() const
    {
        if (mType != VAR_QUATERNION)
            return Quaternion::sIdentity;
        return *reinterpret_cast<const Quaternion*>(&mValue);
    }
    
    //! Return a Color, default if type mismatch
    const Color& getColor() const
    {
        static const Color noColor;
        
        if (mType != VAR_COLOR)
            return noColor;
        return *reinterpret_cast<const Color*>(&mValue);
    }
    
    //! Return a string, empty if type mismatch
    const std::string& getString() const
    {
        static const std::string noString;
        
        if (mType != VAR_STRING)
            return noString;
        return *reinterpret_cast<const std::string*>(mValue.mPtr);
    }
    
    //! Return a buffer, empty if type mismatch
    const std::vector<unsigned char>& getBuffer() const
    {
        static const std::vector<unsigned char> noBuffer;
        
        if (mType != VAR_BUFFER)
            return noBuffer;
        return *reinterpret_cast<const std::vector<unsigned char>*>(mValue.mPtr);
    }
    
    //! Return a variant vector, empty if type mismatch
    const VariantVector& getVariantVector() const
    {
        static const VariantVector noVector;
        
        if (mType != VAR_VARIANTVECTOR)
            return noVector;
        return *reinterpret_cast<VariantVector*>(mValue.mPtr);
    }
    
    //! Return a variant map, empty if type mismatch
    const VariantMap& getVariantMap() const
    {
        static const VariantMap noMap;
        
        if (mType != VAR_VARIANTMAP)
            return noMap;
        return *reinterpret_cast<VariantMap*>(mValue.mPtr);
    }
    
    //! Return a pointer, null if type mismatch
    void* getPtr() const
    {
        if (mType != VAR_PTR)
            return 0;
        return mValue.mPtr;
    }
    
    //! Set from type and value strings
    void fromString(const std::string& type, const std::string& value);
    //! Set buffer type from a memory area
    void setBuffer(const void* data, unsigned size);
    //! Write to a stream
    void write(Serializer& dest) const;
    //! Read from a stream
    void read(Deserializer& source);
    
    //! Return type
    VariantType getType() const { return mType; }
    //! Return type name
    const std::string& getTypeName() const;
    //! Convert value to string
    std::string toString() const;
    
private:
    //! Set new type and allocate/deallocate memory as necessary
    void setType(VariantType newType);
    
    //! Variant type
    VariantType mType;
    //! Variant value
    VariantValue mValue;
};

#endif // COMMON_VARIANT_H
