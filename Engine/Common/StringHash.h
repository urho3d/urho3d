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

#ifndef COMMON_STRINGHASH_H
#define COMMON_STRINGHASH_H

#include <string>

//! 32-bit hash value for a string
class StringHash
{
public:
    //! Construct with zero value
    StringHash() :
        mData(0)
    {
    }
    
    //! Copy-construct from another hash
    StringHash(const StringHash& rhs) :
        mData(rhs.mData)
    {
    }
    
    //! Construct from a C string case-insensitively
    explicit StringHash(const char* str);
    //! Construct from a string case-insensitively
    explicit StringHash(const std::string& str);
    
    //! Assign from another hash
    StringHash& operator = (const StringHash& rhs)
    {
        mData = rhs.mData;
        return *this;
    }
    
    //! Add a hash
    StringHash operator + (const StringHash& rhs) const
    {
        StringHash ret;
        ret.mData = mData + rhs.mData;
        return ret;
    }
    
    //! Add-assign a hash
    StringHash& operator += (const StringHash& rhs)
    {
        mData += rhs.mData;
        return *this;
    }
    
    // Test for equality with another hash
    bool operator == (const StringHash& rhs) const
    {
        return mData == rhs.mData;
    }
    
    //! Test for inequality with another hash
    bool operator != (const StringHash& rhs) const
    {
        return mData != rhs.mData;
    }
    
    //! Test if less than another hash
    bool operator < (const StringHash& rhs) const
    {
        return mData < rhs.mData;
    }
    
    //! Test if greater than another hash
    bool operator > (const StringHash& rhs) const
    {
        return mData > rhs.mData;
    }
    
    //! Return true if nonzero hash value
    operator bool () const
    {
        return mData != 0;
    }
    
    //! Return unsigned data
    const unsigned* getData() const { return &mData; }
    
    //! Calculate hash value case-insensitively from a C string
    static unsigned calculate(const char* str);
    
    //! Hash value
    unsigned mData;
};

//! 16-bit hash value for a string
class ShortStringHash
{
public:
    //! Construct with zero hash value
    ShortStringHash() :
        mData(0)
    {
    }
    
    //! Copy-construct from another hash value
    ShortStringHash(const ShortStringHash& rhs) :
        mData(rhs.mData)
    {
    }
    
    //! Copy-construct from another 32-bit hash value (ignore the high bits)
    explicit ShortStringHash(const StringHash& rhs) :
        mData(rhs.mData)
    {
    }
    
    //! Construct from a C string case-insensitively
    explicit ShortStringHash(const char* str);
    //! Construct from a string case-insensitively
    explicit ShortStringHash(const std::string& str);
    
    //! Assign from another hash
    ShortStringHash& operator = (const ShortStringHash& rhs)
    {
        mData = rhs.mData;
        return *this;
    }
    
    //! Add a hash
    ShortStringHash operator + (const ShortStringHash& rhs) const
    {
        ShortStringHash ret;
        ret.mData = mData + rhs.mData;
        return ret;
    }
    
    // Add-assign a hash
    ShortStringHash& operator += (const ShortStringHash& rhs)
    {
        mData += rhs.mData;
        return *this;
    }
    
    //! Test for equality with another hash
    bool operator == (const ShortStringHash& rhs) const
    {
        return mData == rhs.mData;
    }
    
    //! Test for inequality with another hash
    bool operator != (const ShortStringHash& rhs) const
    {
        return mData != rhs.mData;
    }
    
    //! Test if less than another hash
    bool operator < (const ShortStringHash& rhs) const
    {
        return mData < rhs.mData;
    }
    
    //! Test if greater than another hash
    bool operator > (const ShortStringHash& rhs) const
    {
        return mData > rhs.mData;
    }
    
    //! Return true if nonzero hash value
    operator bool () const
    {
        return mData != 0;
    }
    
    //! Return unsigned short data
    const unsigned short* getData() const { return &mData; }
    
    //! Calculate hash value case-insensitively from a C string
    static unsigned short calculate(const char* str);
    
    //! Hash value
    unsigned short mData;
};

#define HASH(str) (StringHash(#str))
#define SHORT_HASH(str) (ShortStringHash(#str))
#define DEFINE_HASH(id, str) static const StringHash id(#str)
#define DEFINE_SHORT_HASH(id, str) static const ShortStringHash id(#str)

//! Register reverse mapping for a hash. Optionally throw if a hash collision occurs
void registerHash(const std::string& str, bool throwIfCollision = true);
//! Return string for a hash if reverse mapping exists
const std::string& hashToString(StringHash hash);
//! Register reverse mapping for a short hash. Optionally throw if a hash collision occurs
void registerShortHash(const std::string& str, bool throwIfCollision = true);
//! Return string for a short hash if reverse mapping exists
const std::string& shortHashToString(ShortStringHash hash);

#endif // COMMON_STRINGHASH_H
