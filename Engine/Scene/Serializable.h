//
// Copyright (c) 2008-2013 the Urho3D project.
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

#include "Attribute.h"
#include "Object.h"

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
class Serializable : public Object
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
    virtual void OnGetAttribute(const AttributeInfo& attr, Variant& dest);
    /// Return attribute descriptions, or null if none defined.
    virtual const Vector<AttributeInfo>* GetAttributes() const;
    /// Return network replication attribute descriptions, or null if none defined.
    virtual const Vector<AttributeInfo>* GetNetworkAttributes() const;
    /// Load from binary data. When setInstanceDefault is set to true, after setting the attribute value, store the value as instance's default value. Return true if successful.
    virtual bool Load(Deserializer& source, bool setInstanceDefault = false);
    /// Save as binary data. Return true if successful.
    virtual bool Save(Serializer& dest);
    /// Load from XML data. When setInstanceDefault is set to true, after setting the attribute value, store the value as instance's default value. Return true if successful.
    virtual bool LoadXML(const XMLElement& source, bool setInstanceDefault = false);
    /// Save as XML data. Return true if successful.
    virtual bool SaveXML(XMLElement& dest);
    /// Apply attribute changes that can not be applied immediately. Called after scene load or a network update.
    virtual void ApplyAttributes() {}
    /// Return whether should save default-valued attributes into XML. Default false.
    virtual bool SaveDefaultAttributes() const { return false; }

    /// Set attribute by index. Return true if successfully set.
    bool SetAttribute(unsigned index, const Variant& value);
    /// Set attribute by name. Return true if successfully set.
    bool SetAttribute(const String& name, const Variant& value);
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
    Variant GetAttribute(unsigned index);
    /// Return attribute value by name. Return empty if not found.
    Variant GetAttribute(const String& name);
    /// Return attribute default value by index. Return empty if illegal index.
    Variant GetAttributeDefault(unsigned index);
    /// Return attribute default value by name. Return empty if not found.
    Variant GetAttributeDefault(const String& name);
    /// Return number of attributes.
    unsigned GetNumAttributes() const;
    /// Return number of network replication attributes.
    unsigned GetNumNetworkAttributes() const;

protected:
    /// Network attribute state.
    NetworkState* networkState_;

private:
    /// Attribute default value at each instance level.
    VariantMap* instanceDefaultValues_;
};

/// Template implementation of the attribute accessor invoke helper class.
template <class T, class U> class AttributeAccessorImpl : public AttributeAccessor
{
public:
    typedef U (T::*GetFunctionPtr)() const;
    typedef void (T::*SetFunctionPtr)(U);

    /// Construct with function pointers.
    AttributeAccessorImpl(GetFunctionPtr getFunction, SetFunctionPtr setFunction) :
        getFunction_(getFunction),
        setFunction_(setFunction)
    {
        assert(getFunction_);
        assert(setFunction_);
    }

    /// Invoke getter function.
    virtual void Get(Serializable* ptr, Variant& dest)
    {
        assert(ptr);
        T* classPtr = static_cast<T*>(ptr);
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

/// Template implementation of the attribute accessor invoke helper class using const references.
template <class T, class U> class RefAttributeAccessorImpl : public AttributeAccessor
{
public:
    typedef const U& (T::*GetFunctionPtr)() const;
    typedef void (T::*SetFunctionPtr)(const U&);

    /// Construct with function pointers.
    RefAttributeAccessorImpl(GetFunctionPtr getFunction, SetFunctionPtr setFunction) :
        getFunction_(getFunction),
        setFunction_(setFunction)
    {
        assert(getFunction_);
        assert(setFunction_);
    }

    /// Invoke getter function.
    virtual void Get(Serializable* ptr, Variant& dest)
    {
        assert(ptr);
        T* classPtr = static_cast<T*>(ptr);
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

#define COPY_BASE_ATTRIBUTES(className, sourceClassName) context->CopyBaseAttributes<sourceClassName, className>()
#define REMOVE_ATTRIBUTE(className, name) context->RemoveAttribute<className>(name)
#define ATTRIBUTE(className, type, name, variable, defaultValue, mode) context->RegisterAttribute<className>(AttributeInfo(type, name, offsetof(className, variable), defaultValue, mode))
#define ENUM_ATTRIBUTE(className, name, variable, enumNames, defaultValue, mode) context->RegisterAttribute<className>(AttributeInfo(name, offsetof(className, variable), enumNames, defaultValue, mode))
#define ACCESSOR_ATTRIBUTE(className, type, name, getFunction, setFunction, typeName, defaultValue, mode) context->RegisterAttribute<className>(AttributeInfo(type, name, new AttributeAccessorImpl<className, typeName>(&className::getFunction, &className::setFunction), defaultValue, mode))
#define ENUM_ACCESSOR_ATTRIBUTE(className, name, getFunction, setFunction, typeName, enumNames, defaultValue, mode) context->RegisterAttribute<className>(AttributeInfo(name, new AttributeAccessorImpl<className, typeName>(&className::getFunction, &className::setFunction), enumNames, defaultValue, mode))
#define REF_ACCESSOR_ATTRIBUTE(className, type, name, getFunction, setFunction, typeName, defaultValue, mode) context->RegisterAttribute<className>(AttributeInfo(type, name, new RefAttributeAccessorImpl<className, typeName>(&className::getFunction, &className::setFunction), defaultValue, mode))
#define UPDATE_ATTRIBUTE_DEFAULT_VALUE(className, name, defaultValue) context->UpdateAttributeDefaultValue<className>(name, defaultValue)

}
