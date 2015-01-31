//
// Copyright (c) 2008-2015 the Urho3D project.
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

#include "../Core/Attribute.h"
#include "../Core/Object.h"

#include <cstddef>

namespace Urho3D
{

class Connection;
class Deserializer;
class Serializer;
class XMLElement;

struct DirtyBits;
struct NetworkState;
struct ReplicationState;

/// Base class for objects with automatic serialization through attributes.
class URHO3D_API Serializable : public Object
{
    OBJECT(Serializable);

public:
    /// Construct.
    Serializable(Context* context);
    /// Destruct.
    virtual ~Serializable();

    /// Handle attribute write access. Default implementation writes to the variable at offset, or invokes the set accessor.
    virtual void OnSetAttribute(const AttributeInfo& attr, const Variant& src);
    /// Handle attribute read access. Default implementation reads the variable at offset, or invokes the get accessor.
    virtual void OnGetAttribute(const AttributeInfo& attr, Variant& dest) const;
    /// Return attribute descriptions, or null if none defined.
    virtual const Vector<AttributeInfo>* GetAttributes() const;
    /// Return network replication attribute descriptions, or null if none defined.
    virtual const Vector<AttributeInfo>* GetNetworkAttributes() const;
    /// Load from binary data. When setInstanceDefault is set to true, after setting the attribute value, store the value as instance's default value. Return true if successful.
    virtual bool Load(Deserializer& source, bool setInstanceDefault = false);
    /// Save as binary data. Return true if successful.
    virtual bool Save(Serializer& dest) const;
    /// Load from XML data. When setInstanceDefault is set to true, after setting the attribute value, store the value as instance's default value. Return true if successful.
    virtual bool LoadXML(const XMLElement& source, bool setInstanceDefault = false);
    /// Save as XML data. Return true if successful.
    virtual bool SaveXML(XMLElement& dest) const;
    /// Apply attribute changes that can not be applied immediately. Called after scene load or a network update.
    virtual void ApplyAttributes() {}
    /// Return whether should save default-valued attributes into XML. Default false.
    virtual bool SaveDefaultAttributes() const { return false; }
    /// Mark for attribute check on the next network update.
    virtual void MarkNetworkUpdate() {}

    /// Set attribute by index. Return true if successfully set.
    bool SetAttribute(unsigned index, const Variant& value);
    /// Set attribute by name. Return true if successfully set.
    bool SetAttribute(const String& name, const Variant& value);
    /// Reset all editable attributes to their default values.
    void ResetToDefault();
    /// Remove instance's default values if they are set previously.
    void RemoveInstanceDefault();
    /// Set temporary flag. Temporary objects will not be saved.
    void SetTemporary(bool enable);
    /// Allocate network attribute state.
    void AllocateNetworkState();
    /// Write initial delta network update.
    void WriteInitialDeltaUpdate(Serializer& dest);
    /// Write a delta network update according to dirty attribute bits.
    void WriteDeltaUpdate(Serializer& dest, const DirtyBits& attributeBits);
    /// Write a latest data network update.
    void WriteLatestDataUpdate(Serializer& dest);
    /// Read and apply a network delta update.
    void ReadDeltaUpdate(Deserializer& source);
    /// Read and apply a network latest data update.
    void ReadLatestDataUpdate(Deserializer& source);

    /// Return attribute value by index. Return empty if illegal index.
    Variant GetAttribute(unsigned index) const;
    /// Return attribute value by name. Return empty if not found.
    Variant GetAttribute(const String& name) const;
    /// Return attribute default value by index. Return empty if illegal index.
    Variant GetAttributeDefault(unsigned index) const;
    /// Return attribute default value by name. Return empty if not found.
    Variant GetAttributeDefault(const String& name) const;
    /// Return number of attributes.
    unsigned GetNumAttributes() const;
    /// Return number of network replication attributes.
    unsigned GetNumNetworkAttributes() const;
    /// Return whether is temporary.
    bool IsTemporary() const { return temporary_; }

protected:
    /// Network attribute state.
    NetworkState* networkState_;

private:
    /// Set instance-level default value. Allocate the internal data structure as necessary.
    void SetInstanceDefault(const String& name, const Variant& defaultValue);
    /// Get instance-level default value.
    Variant GetInstanceDefault(const String& name) const;

    /// Attribute default value at each instance level.
    VariantMap* instanceDefaultValues_;
    /// Temporary flag.
    bool temporary_;
};

/// Template implementation of the enum attribute accessor invoke helper class.
template <typename T, typename U> class EnumAttributeAccessorImpl : public AttributeAccessor
{
public:
    typedef U (T::*GetFunctionPtr)() const;
    typedef void (T::*SetFunctionPtr)(U);

    /// Construct with function pointers.
    EnumAttributeAccessorImpl(GetFunctionPtr getFunction, SetFunctionPtr setFunction) :
        getFunction_(getFunction),
        setFunction_(setFunction)
    {
        assert(getFunction_);
        assert(setFunction_);
    }

    /// Invoke getter function.
    virtual void Get(const Serializable* ptr, Variant& dest) const
    {
        assert(ptr);
        const T* classPtr = static_cast<const T*>(ptr);
        dest = (classPtr->*getFunction_)();
    }

    /// Invoke setter function.
    virtual void Set(Serializable* ptr, const Variant& value)
    {
        assert(ptr);
        T* classPtr = static_cast<T*>(ptr);
        (classPtr->*setFunction_)((U)value.GetInt());
    }

    /// Class-specific pointer to getter function.
    GetFunctionPtr getFunction_;
    /// Class-specific pointer to setter function.
    SetFunctionPtr setFunction_;
};

/// Attribute trait (default use const reference for object type).
template<typename T> struct AttributeTrait
{
    /// Get function return type.
    typedef const T& ReturnType;
    /// Set function parameter type.
    typedef const T& ParameterType;
};

/// Int attribute trait.
template<> struct AttributeTrait<int>
{
    typedef int ReturnType;
    typedef int ParameterType;
};

/// unsigned attribute trait.
template<> struct AttributeTrait<unsigned>
{
    typedef unsigned ReturnType;
    typedef unsigned ParameterType;
};

/// Bool attribute trait.
template<> struct AttributeTrait<bool>
{
    typedef bool ReturnType; 
    typedef bool ParameterType; 
};

/// Float attribute trait.
template<> struct AttributeTrait<float>
{
    typedef float ReturnType;
    typedef float ParameterType;
};

/// Mixed attribute trait (use const reference for set function only).
template<typename T> struct MixedAttributeTrait
{
    typedef T ReturnType;
    typedef const T& ParameterType;
};

/// Template implementation of the attribute accessor invoke helper class.
template <typename T, typename U, typename Trait> class AttributeAccessorImpl : public AttributeAccessor
{
public:
    typedef typename Trait ::ReturnType (T::*GetFunctionPtr)() const;
    typedef void (T::*SetFunctionPtr)(typename Trait ::ParameterType);

    /// Construct with function pointers.
    AttributeAccessorImpl(GetFunctionPtr getFunction, SetFunctionPtr setFunction) :
        getFunction_(getFunction),
        setFunction_(setFunction)
    {
        assert(getFunction_);
        assert(setFunction_);
    }

    /// Invoke getter function.
    virtual void Get(const Serializable* ptr, Variant& dest) const
    {
        assert(ptr);
        const T* classPtr = static_cast<const T*>(ptr);
        dest = (classPtr->*getFunction_)();
    }

    /// Invoke setter function.
    virtual void Set(Serializable* ptr, const Variant& value)
    {
        assert(ptr);
        T* classPtr = static_cast<T*>(ptr);
        (classPtr->*setFunction_)(value.Get<U>());
    }

    /// Class-specific pointer to getter function.
    GetFunctionPtr getFunction_;
    /// Class-specific pointer to setter function.
    SetFunctionPtr setFunction_;
};

// The following macros need to be used within a class member function such as ClassName::RegisterObject().
// A variable called "context" needs to exist in the current scope and point to a valid Context object.

/// Copy attributes from a base class.
#define COPY_BASE_ATTRIBUTES(sourceClassName) context->CopyBaseAttributes<sourceClassName, ClassName>()
/// Remove attribute by name.
#define REMOVE_ATTRIBUTE(name) context->RemoveAttribute<ClassName>(name)
/// Define an attribute that points to a memory offset in the object.
#define ATTRIBUTE(name, typeName, variable, defaultValue, mode) context->RegisterAttribute<ClassName>(Urho3D::AttributeInfo(GetVariantType<typeName >(), name, offsetof(ClassName, variable), defaultValue, mode))
/// Define an attribute that points to a memory offset in the object, and uses zero-based enum values, which are mapped to names through an array of C string pointers.
#define ENUM_ATTRIBUTE(name, variable, enumNames, defaultValue, mode) context->RegisterAttribute<ClassName>(Urho3D::AttributeInfo(name, offsetof(ClassName, variable), enumNames, defaultValue, mode))
/// Define an attribute that uses get and set functions.
#define ACCESSOR_ATTRIBUTE(name, getFunction, setFunction, typeName, defaultValue, mode) context->RegisterAttribute<ClassName>(Urho3D::AttributeInfo(GetVariantType<typeName >(), name, new Urho3D::AttributeAccessorImpl<ClassName, typeName, AttributeTrait<typeName > >(&ClassName::getFunction, &ClassName::setFunction), defaultValue, mode))
/// Define an attribute that uses get and set functions, and uses zero-based enum values, which are mapped to names through an array of C string pointers.
#define ENUM_ACCESSOR_ATTRIBUTE(name, getFunction, setFunction, typeName, enumNames, defaultValue, mode) context->RegisterAttribute<ClassName>(Urho3D::AttributeInfo(name, new Urho3D::EnumAttributeAccessorImpl<ClassName, typeName >(&ClassName::getFunction, &ClassName::setFunction), enumNames, defaultValue, mode))
/// Define an attribute that uses get and set functions, where the get function returns by value, but the set function uses a reference.
#define MIXED_ACCESSOR_ATTRIBUTE(name, getFunction, setFunction, typeName, defaultValue, mode) context->RegisterAttribute<ClassName>(Urho3D::AttributeInfo(GetVariantType<typeName >(), name, new Urho3D::AttributeAccessorImpl<ClassName, typeName, MixedAttributeTrait<typeName > >(&ClassName::getFunction, &ClassName::setFunction), defaultValue, mode))
/// Update the default value of an already registered attribute.
#define UPDATE_ATTRIBUTE_DEFAULT_VALUE(name, defaultValue) context->UpdateAttributeDefaultValue<ClassName>(name, defaultValue)

}
