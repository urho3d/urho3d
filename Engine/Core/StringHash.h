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

#pragma once

#include "StringBase.h"

/// 32-bit hash value for a string.
class StringHash
{
public:
    /// Construct with zero value.
    StringHash() :
        value_(0)
    {
    }
    
    /// Copy-construct from another hash.
    StringHash(const StringHash& rhs) :
        value_(rhs.value_)
    {
    }
    
    /// Construct with an initial value.
    explicit StringHash(unsigned value) :
        value_(value)
    {
    }
    
    /// Construct from a C string case-insensitively.
    explicit StringHash(const char* str);
    
    /// Construct from a string case-insensitively.
    explicit StringHash(const String& str);
    
    /// Assign from another hash.
    StringHash& operator = (const StringHash& rhs)
    {
        value_ = rhs.value_;
        return *this;
    }
    
    /// Add a hash.
    StringHash operator + (const StringHash& rhs) const
    {
        StringHash ret;
        ret.value_ = value_ + rhs.value_;
        return ret;
    }
    
    /// Add-assign a hash.
    StringHash& operator += (const StringHash& rhs)
    {
        value_ += rhs.value_;
        return *this;
    }
    
    // Test for equality with another hash.
    bool operator == (const StringHash& rhs) const { return value_ == rhs.value_; }
    /// Test for inequality with another hash.
    bool operator != (const StringHash& rhs) const { return value_ != rhs.value_; }
    /// Test if less than another hash.
    bool operator < (const StringHash& rhs) const { return value_ < rhs.value_; }
    /// Test if greater than another hash.
    bool operator > (const StringHash& rhs) const { return value_ > rhs.value_; }
    /// Return true if nonzero hash value.
    operator bool () const { return value_ != 0; }
    /// Return hash value.
    unsigned GetValue() const { return value_; }
    /// Return unsigned data.
    const unsigned* GetData() const { return &value_; }
    /// Return as string.
    String ToString() const;
    /// Return hash value for HashSet & HashMap.
    unsigned ToHash() const { return value_; }
    
    /// Calculate hash value case-insensitively from a C string.
    static unsigned Calculate(const char* str);
    
    /// Zero hash.
    static const StringHash ZERO;
    
private:
    /// Hash value.
    unsigned value_;
};

/// 16-bit hash value for a string.
class ShortStringHash
{
public:
    /// Construct with zero hash value.
    ShortStringHash() :
        value_(0)
    {
    }
    
    /// Copy-construct from another hash value.
    ShortStringHash(const ShortStringHash& rhs) :
        value_(rhs.value_)
    {
    }
    
    /// Copy-construct from another 32-bit hash value (ignore the high bits.)
    explicit ShortStringHash(const StringHash& rhs) :
        value_(rhs.GetValue())
    {
    }
    
    /// Construct with an initial value.
    explicit ShortStringHash(unsigned short value) :
        value_(value)
    {
    }

    /// Construct from a C string case-insensitively.
    explicit ShortStringHash(const char* str);
    /// Construct from a string case-insensitively.
    explicit ShortStringHash(const String& str);
    
    /// Assign from another hash.
    ShortStringHash& operator = (const ShortStringHash& rhs)
    {
        value_ = rhs.value_;
        return *this;
    }
    
    /// Add a hash.
    ShortStringHash operator + (const ShortStringHash& rhs) const
    {
        ShortStringHash ret;
        ret.value_ = value_ + rhs.value_;
        return ret;
    }
    
    // Add-assign a hash.
    ShortStringHash& operator += (const ShortStringHash& rhs)
    {
        value_ += rhs.value_;
        return *this;
    }
    
    /// Test for equality with another hash.
    bool operator == (const ShortStringHash& rhs) const { return value_ == rhs.value_; }
    /// Test for inequality with another hash.
    bool operator != (const ShortStringHash& rhs) const { return value_ != rhs.value_; }
    /// Test if less than another hash.
    bool operator < (const ShortStringHash& rhs) const { return value_ < rhs.value_; }
    /// Test if greater than another hash.
    bool operator > (const ShortStringHash& rhs) const { return value_ > rhs.value_; }
    /// Return true if nonzero hash value.
    operator bool () const { return value_ != 0; }
    /// Return hash value.
    unsigned short GetValue() const { return value_; }
    /// Return unsigned short data.
    const unsigned short* GetData() const { return &value_; }
    /// Return as string.
    String ToString() const;
    /// Return hash value for HashSet & HashMap.
    unsigned ToHash() const { return value_; }
    
    /// Calculate hash value case-insensitively from a C string.
    static unsigned short Calculate(const char* str);
    
    /// Zero hash.
    static const ShortStringHash ZERO;
    
private:
    /// Hash value.
    unsigned short value_;
};

#define HASH(str) (StringHash(#str))
#define SHORTHASH(str) (ShortStringHash(#str))
