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

#include "Variant.h"

/// Attribute used only for disk serialization
static const unsigned AM_SERIALIZATION = 0x1;
/// Attribute used only for network replication
static const unsigned AM_NETWORK = 0x2;
/// Attribute used for both (default)
static const unsigned AM_BOTH = 0x3;

/// Description of an automatically serializable variable
struct AttributeInfo
{
    /// Construct empty
    AttributeInfo() :
        type_(VAR_NONE),
        name_(0),
        offset_(0),
        enumNames_(0),
        mode_(AM_BOTH)
    {
    }
    
    /// Copy-construct from another AttributeInfo
    AttributeInfo(const AttributeInfo& rhs) :
        type_(rhs.type_),
        name_(rhs.name_),
        offset_(rhs.offset_),
        enumNames_(rhs.enumNames_),
        defaultValue_(rhs.defaultValue_),
        mode_(rhs.mode_)
    {
    }
    
    /// Construct with parameters
    AttributeInfo(VariantType type, const char* name, unsigned offset, const char** enumNames, const Variant& defaultValue, unsigned mode) :
        type_(type),
        name_(name),
        offset_(offset),
        enumNames_(enumNames),
        defaultValue_(defaultValue),
        mode_(mode)
    {
    }
    
    /// Attribute type
    VariantType type_;
    /// Name
    const char* name_;
    /// Byte offset from start of object
    unsigned offset_;
    /// Enum string names
    const char** enumNames_;
    /// Default value for network replication
    Variant defaultValue_;
    /// Attribute mode: whether to use for serialization, network replication, or both
    unsigned mode_;
};

#define ATTRIBUTE(className, type, name, variable, defaultValue) context->RegisterAttribute<className>(AttributeInfo(type, name, offsetof(className, variable), 0, defaultValue, AM_BOTH))
#define ATTRIBUTE_MODE(className, type, name, variable, defaultValue, mode) context->RegisterAttribute<className>(AttributeInfo(type, name, offsetof(className, variable), 0, defaultValue, mode))
#define ENUM_ATTRIBUTE(className, name, variable, enumNames, defaultValue) context->RegisterAttribute<className>(AttributeInfo(VAR_INT, name, offsetof(className, variable), enumNames, defaultValue, AM_BOTH))
#define ENUM_ATTRIBUTE_MODE(className, name, variable, enumNames, defaultValue, mode) context->RegisterAttribute<className>(AttributeInfo(VAR_INT, name, offsetof(className, variable), enumNames, defaultValue, mode))
#define ID_ATTRIBUTE(className, type, name, id, defaultValue) context->RegisterAttribute<className>(AttributeInfo(type, name, id, 0, defaultValue, AM_BOTH))
#define ID_ATTRIBUTE_MODE(className, type, name, id, defaultValue, mode) context->RegisterAttribute<className>(AttributeInfo(type, name, id, 0, defaultValue, mode))
#define ID_ENUM_ATTRIBUTE(className, name, id, enumNames, defaultValue) context->RegisterAttribute<className>(AttributeInfo(VAR_INT, name, id, enumNames, defaultValue, AM_BOTH))
#define ID_ENUM_ATTRIBUTE_MODE(className, name, id, enumNames, defaultValue, mode) context->RegisterAttribute<className>(AttributeInfo(VAR_INT, name, id, enumNames, defaultValue, mode))

static const unsigned ID_ATTRIBUTE_BASE = 0x80000000;
