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

#pragma once

#include "Ptr.h"
#include "Variant.h"

/// Attribute used only for disk serialization
static const unsigned AM_SERIALIZATION = 0x1;
/// Attribute used for network replication
static const unsigned AM_NETWORK = 0x2;
/// Attribute used for both (default)
static const unsigned AM_BOTH = 0x3;
/// Attribute should use latest data grouping instead of delta update in network replication
static const unsigned AM_LATESTDATA = 0x4;

class Serializable;

/// Internal helper class for invoking attribute accessors
class AttributeAccessor : public RefCounted
{
public:
    /// Get the attribute
    virtual Variant Get(Serializable* ptr) { return Variant(); }
    /// Set the attribute
    virtual void Set(Serializable* ptr, const Variant& value) {}
};

/// Description of an automatically serializable variable
struct AttributeInfo
{
    /// Construct empty
    AttributeInfo() :
        type_(VAR_NONE),
        offset_(0),
        enumNames_(0),
        mode_(AM_BOTH)
    {
    }
    
    /// Construct offset attribute
    AttributeInfo(VariantType type, const char* name, unsigned offset, const Variant& defaultValue, unsigned mode) :
        type_(type),
        name_(name),
        offset_(offset),
        enumNames_(0),
        defaultValue_(defaultValue),
        mode_(mode)
    {
    }
    
   /// Construct offset enum attribute
    AttributeInfo(VariantType type, const char* name, unsigned offset, const String* enumNames, const Variant& defaultValue, unsigned mode) :
        type_(type),
        name_(name),
        offset_(offset),
        enumNames_(enumNames),
        defaultValue_(defaultValue),
        mode_(mode)
    {
    }
    
    /// Construct accessor attribute
    AttributeInfo(VariantType type, const char* name, AttributeAccessor* accessor, const Variant& defaultValue, unsigned mode) :
        type_(type),
        name_(name),
        offset_(0),
        enumNames_(0),
        accessor_(accessor),
        defaultValue_(defaultValue),
        mode_(mode)
    {
    }
    
    /// Attribute type
    VariantType type_;
    /// Name
    String name_;
    /// Byte offset from start of object
    unsigned offset_;
    /// Enum string names
    const String* enumNames_;
    /// Helper object for accessor mode
    SharedPtr<AttributeAccessor> accessor_;
    /// Default value for network replication
    Variant defaultValue_;
    /// Attribute mode: whether to use for serialization, network replication, or both
    unsigned mode_;
};
