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
    VAR_PTR
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
    
    Vector4 mVector4;
    std::string mString;
    std::vector<unsigned char> mBuffer;
};

class Deserializer;
class Serializer;

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
    Variant(int value)
    {
        *this = value;
    }
    
    //! Construct from unsigned integer
    Variant(unsigned value)
    {
        *this = (int)value;
    }
    
    //! Construct from a StringHash (convert to integer)
    Variant(const StringHash& value)
    {
        *this = (int)value.mData;
    }
    
    //! Construct from a ShortStringHash (convert to integer)
    Variant(const ShortStringHash& value)
    {
        *this = (int)value.mData;
    }
    
    //! Construct from a bool
    Variant(bool value)
    {
        *this = value;
    }
    
    //! Construct from a float
    Variant(float value)
    {
        *this = value;
    }
    
    //! Construct from a Vector2
    Variant(const Vector2& value)
    {
        *this = value;
    }
    
    //! Construct from a Vector3
    Variant(const Vector3& value)
    {
        *this = value;
    }
    
    //! Construct from a Vector4
    Variant(const Vector4& value)
    {
        *this = value;
    }
    
    //! Construct from a Quaternion
    Variant(const Quaternion& value)
    {
        *this = value;
    }
    
    //! Construct from a Color
    Variant(const Color& value)
    {
        *this = value;
    }
    
    //! Construct from a string
    Variant(const std::string& value)
    {
        *this = value;
    }
    
    //! Construct from a buffer
    Variant(const std::vector<unsigned char>& value)
    {
        *this = value;
    }
    
    //! Construct from a pointer
    Variant(void* value)
    {
        *this = value;
    }
    
    //! Copy-construct from another variant
    Variant(const Variant& value)
    {
        *this = value;
    }
    
    //! Reset to none type
    void clear()
    {
        setType(VAR_NONE);
    }
    
    //! Assign from another variant
    Variant& operator = (const Variant& rhs)
    {
        setType(rhs.mType);
        mValue = rhs.mValue;
        return *this;
    }
    
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
        *(reinterpret_cast<Vector2*>(&mValue.mVector4)) = rhs;
        return *this;
    }
    
    //! Assign from a Vector3
    Variant& operator = (const Vector3& rhs)
    {
        setType(VAR_VECTOR3);
        *(reinterpret_cast<Vector3*>(&mValue.mVector4)) = rhs;
        return *this;
    }
    
    //! Assign from a Vector4
    Variant& operator = (const Vector4& rhs)
    {
        setType(VAR_VECTOR4);
        mValue.mVector4 = rhs;
        return *this;
    }
    
    //! Assign from a Quaternion
    Variant& operator = (const Quaternion& rhs)
    {
        setType(VAR_QUATERNION);
        *(reinterpret_cast<Quaternion*>(&mValue.mVector4)) = rhs;
        return *this;
    }
    
    //! Assign from a Color
    Variant& operator = (const Color& rhs)
    {
        setType(VAR_COLOR);
        *(reinterpret_cast<Color*>(&mValue.mVector4)) = rhs;
        return *this;
    }
    
    //! Assign from a string
    Variant& operator = (const std::string& rhs)
    {
        setType(VAR_STRING);
        mValue.mString = rhs;
        return *this;
    }
    
    //! Assign from a buffer
    Variant& operator = (const std::vector<unsigned char>& rhs)
    {
        setType(VAR_BUFFER);
        mValue.mBuffer = rhs;
        return *this;
    }
    
    //! Assign from a pointer
    Variant& operator = (void* rhs)
    {
        setType(VAR_PTR);
        mValue.mPtr = rhs;
        return *this;
    }
    
    //! Test for equality with another variant
    bool operator == (const Variant& rhs) const
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
            return *(reinterpret_cast<const Vector2*>(&mValue.mVector4)) == *(reinterpret_cast<const Vector2*>(&rhs.mValue.mVector4));
        case VAR_VECTOR3:
            return *(reinterpret_cast<const Vector3*>(&mValue.mVector4)) == *(reinterpret_cast<const Vector3*>(&rhs.mValue.mVector4));
        case VAR_VECTOR4:
            return mValue.mVector4 == rhs.mValue.mVector4;
        case VAR_QUATERNION:
            return *(reinterpret_cast<const Quaternion*>(&mValue.mVector4)) == *(reinterpret_cast<const Quaternion*>(&rhs.mValue.mVector4));
        case VAR_COLOR:
            return *(reinterpret_cast<const Color*>(&mValue.mVector4)) == *(reinterpret_cast<const Color*>(&rhs.mValue.mVector4));
        case VAR_STRING:
            return mValue.mString == rhs.mValue.mString;
        case VAR_BUFFER:
            return mValue.mBuffer == rhs.mValue.mBuffer;
        case VAR_PTR:
            return mValue.mPtr == rhs.mValue.mPtr;
        }
        
        return true;
    }
    
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
            return *(reinterpret_cast<const Vector2*>(&mValue.mVector4)) == rhs;
        else
            return false;
    }
    
    //! Test for equality with a Vector3. To return true, both the type and value must match
    bool operator == (const Vector3& rhs) const
    {
        if (mType == VAR_VECTOR3)
            return *(reinterpret_cast<const Vector3*>(&mValue.mVector4)) == rhs;
        else
            return false;
    }
    
    //! Test for equality with a Vector4. To return true, both the type and value must match
    bool operator == (const Vector4& rhs) const
    {
        if (mType == VAR_VECTOR4)
            return mValue.mVector4 == rhs;
        else
            return false;
    }
    
    //! Test for equality with a Quaternion. To return true, both the type and value must match
    bool operator == (const Quaternion& rhs) const
    {
        if (mType == VAR_QUATERNION)
            return *(reinterpret_cast<const Quaternion*>(&mValue.mVector4)) == rhs;
        else
            return false;
    }
    
    //! Test for equality with a Color. To return true, both the type and value must match
    bool operator == (const Color& rhs) const
    {
        if (mType == VAR_COLOR)
            return *(reinterpret_cast<const Color*>(&mValue.mVector4)) == rhs;
        else
            return false;
    }
    
    //! Test for equality with a string. To return true, both the type and value must match
    bool operator == (const std::string& rhs) const
    {
        if (mType == VAR_STRING)
            return mValue.mString == rhs;
        else
            return false;
    }
    
    //! Test for equality with a buffer. To return true, both the type and value must match
    bool operator == (const std::vector<unsigned char>& rhs) const
    {
        if (mType == VAR_BUFFER)
            return mValue.mBuffer == rhs;
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
        return *reinterpret_cast<const Vector2*>(&mValue.mVector4);
    }
    
    //! Return a Vector3, zero vector if type mismatch
    const Vector3& getVector3() const
    {
        if (mType != VAR_VECTOR3)
            return Vector3::sZero;
        return *reinterpret_cast<const Vector3*>(&mValue.mVector4);
    }
    
    //! Return a Vector4, zero vector if type mismatch
    const Vector4& getVector4() const
    {
        if (mType != VAR_VECTOR4)
            return Vector4::sZero;
        return mValue.mVector4;
    }
    
    //! Return a Quaternion, identity if type mismatch
    const Quaternion& getQuaternion() const
    {
        if (mType != VAR_QUATERNION)
            return Quaternion::sIdentity;
        return *reinterpret_cast<const Quaternion*>(&mValue.mVector4);
    }
    
    //! Return a Color, default if type mismatch
    const Color& getColor() const
    {
        static const Color noColor;
        
        if (mType != VAR_COLOR)
            return noColor;
        return *reinterpret_cast<const Color*>(&mValue.mVector4);
    }
    
    //! Return a string, empty if type mismatch
    const std::string& getString() const
    {
        static const std::string noString;
        
        if (mType != VAR_STRING)
            return noString;
        return mValue.mString;
    }
    
    //! Return a buffer, empty if type mismatch
    const std::vector<unsigned char>& getBuffer() const
    {
        static const std::vector<unsigned char> noBuffer;
        
        if (mType != VAR_BUFFER)
            return noBuffer;
        return mValue.mBuffer;
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
    //! Set type and clean up if necessary
    void setType(VariantType newType)
    {
        // Clean up the space-consuming storage if no longer needed
        if ((mType == VAR_STRING) && (newType != VAR_STRING) && (mValue.mString.length()))
            mValue.mString = std::string();
        if ((mType == VAR_BUFFER) && (newType != VAR_BUFFER) && (mValue.mBuffer.size()))
            mValue.mBuffer = std::vector<unsigned char>();
        
        mType = newType;
    }
    
    //! Variant type
    VariantType mType;
    //! Variant value
    VariantValue mValue;
};

//! Map of variants
typedef std::map<ShortStringHash, Variant> VariantMap;

#endif // COMMON_VARIANT_H
