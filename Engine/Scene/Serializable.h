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

#include "Attribute.h"
#include "Object.h"

#include <cstddef>

class Deserializer;
class Serializer;
class XMLElement;

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
    /// Load from binary data. Return true if successful.
    virtual bool Load(Deserializer& source);
    /// Save as binary data. Return true if successful.
    virtual bool Save(Serializer& dest);
    /// Load from XML data. Return true if successful.
    virtual bool LoadXML(const XMLElement& source);
    /// Save as XML data. Return true if successful.
    virtual bool SaveXML(XMLElement& dest);
    /// Apply attribute changes that can not be applied immediately. Called after scene load or a network update.
    virtual void ApplyAttributes() {}
    
    /// %Set attribute by index. Return true if successfully set.
    bool SetAttribute(unsigned index, const Variant& value);
    /// %Set attribute by name. Return true if successfully set.
    bool SetAttribute(const String& name, const Variant& value);
    /// Write initial delta network update (compared to default attribute values) and prepare the last sent state.
    void WriteInitialDeltaUpdate(unsigned frameNumber, Serializer& dest, PODVector<unsigned char>& deltaUpdateBits, Vector<Variant>& replicationState);
    /// Prepare delta and latest data network updates. Needs a previously prepared last sent state from WriteInitialDeltaUpdate().
    void PrepareUpdates(unsigned frameNumber, PODVector<unsigned char>& deltaUpdateBits, Vector<Variant>& replicationState, bool& deltaUpdate, bool& latestData);
    /// Write a delta network update prepared with PrepareUpdates().
    void WriteDeltaUpdate(Serializer& dest, PODVector<unsigned char>& deltaUpdateBits, Vector<Variant>& replicationState);
    /// Write a latestdata network update prepared with PrepareUpdates().
    void WriteLatestDataUpdate(Serializer& dest, Vector<Variant>& replicationState);
    /// Read and apply a network delta update.
    void ReadDeltaUpdate(Deserializer& source, PODVector<unsigned char>& deltaUpdateBits);
    /// Read and apply a network latest data update.
    void ReadLatestDataUpdate(Deserializer& source);
    
    /// Return attribute value by index. Return empty if illegal index.
    Variant GetAttribute(unsigned index);
    /// Return attribute value by name. Return empty if not found.
    Variant GetAttribute(const String& name);
    /// Return number of attributes.
    unsigned GetNumAttributes() const;
    /// Return number of network replication attributes.
    unsigned GetNumNetworkAttributes() const;
    /// Return attribute descriptions, or null if none defined.
    const Vector<AttributeInfo>* GetAttributes() const;
    /// Return network replication attribute descriptions, or null if none defined.
    const Vector<AttributeInfo>* GetNetworkAttributes() const;
    /// Return whether is loading attributes from a file. Is false during network deserialization.
    bool IsLoading() const { return loading_; }
    
private:
    /// Server-side attributes for sending updates. Only updated once per network frame, not per user.
    Vector<Variant> serverAttributes_;
    /// Last server frame number.
    unsigned serverFrameNumber_;
    /// Is loading flag.
    bool loading_;
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
