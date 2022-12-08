// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

/// \file

#pragma once

#include "../Container/FlagSet.h"
#include "../Container/Ptr.h"
#include "../Core/Variant.h"

namespace Urho3D
{

enum AttributeMode
{
    /// Attribute shown only in the editor, but not serialized.
    AM_EDIT = 0x0,
    /// Attribute used for file serialization.
    AM_FILE = 0x1,
    /// Attribute used for network replication.
    AM_NET = 0x2,
    /// Attribute used for both file serialization and network replication (default).
    AM_DEFAULT = 0x3,
    /// Attribute should use latest data grouping instead of delta update in network replication.
    AM_LATESTDATA = 0x4,
    /// Attribute should not be shown in the editor.
    AM_NOEDIT = 0x8,
    /// Attribute is a node ID and may need rewriting.
    AM_NODEID = 0x10,
    /// Attribute is a component ID and may need rewriting.
    AM_COMPONENTID = 0x20,
    /// Attribute is a node ID vector where first element is the amount of nodes.
    AM_NODEIDVECTOR = 0x40,
    /// Attribute is readonly. Can't be used with binary serialized objects.
    AM_FILEREADONLY = 0x81,
};
URHO3D_FLAGSET(AttributeMode, AttributeModeFlags);

class Serializable;

/// Abstract base class for invoking attribute accessors.
class URHO3D_API AttributeAccessor : public RefCounted
{
public:
    /// Get the attribute.
    virtual void Get(const Serializable* ptr, Variant& dest) const = 0;
    /// Set the attribute.
    virtual void Set(Serializable* ptr, const Variant& src) = 0;
};

/// Description of an automatically serializable variable.
struct AttributeInfo
{
    /// Construct empty.
    AttributeInfo() = default;

    /// Construct attribute.
    AttributeInfo(VariantType type, const char* name, const SharedPtr<AttributeAccessor>& accessor, const char** enumNames, const Variant& defaultValue, AttributeModeFlags mode) :
        type_(type),
        name_(name),
        enumNames_(enumNames),
        accessor_(accessor),
        defaultValue_(defaultValue),
        mode_(mode)
    {
    }

    /// Get attribute metadata.
    const Variant& GetMetadata(const StringHash& key) const
    {
        auto elem = metadata_.Find(key);
        return elem != metadata_.End() ? elem->second_ : Variant::EMPTY;
    }

    /// Get attribute metadata of specified type.
    template <class T> T GetMetadata(const StringHash& key) const
    {
        return GetMetadata(key).Get<T>();
    }

    /// Attribute type.
    VariantType type_ = VAR_NONE;
    /// Name.
    String name_;
    /// Enum names.
    const char** enumNames_ = nullptr;
    /// Helper object for accessor mode.
    SharedPtr<AttributeAccessor> accessor_;
    /// Default value for network replication.
    Variant defaultValue_;
    /// Attribute mode: whether to use for serialization, network replication, or both.
    AttributeModeFlags mode_ = AM_DEFAULT;
    /// Attribute metadata.
    VariantMap metadata_;
    /// Attribute data pointer if elsewhere than in the Serializable.
    void* ptr_ = nullptr;
};

/// Attribute handle returned by Context::RegisterAttribute and used to chain attribute setup calls.
/// @nobind
struct AttributeHandle
{
    friend class Context;
private:
    /// Construct default.
    AttributeHandle() = default;
    /// Construct from another handle.
    AttributeHandle(const AttributeHandle& another) = default;
    /// Attribute info.
    AttributeInfo* attributeInfo_ = nullptr;
    /// Network attribute info.
    AttributeInfo* networkAttributeInfo_ = nullptr;
public:
    /// Set metadata.
    AttributeHandle& SetMetadata(StringHash key, const Variant& value)
    {
        if (attributeInfo_)
            attributeInfo_->metadata_[key] = value;
        if (networkAttributeInfo_)
            networkAttributeInfo_->metadata_[key] = value;
        return *this;
    }
};

}
