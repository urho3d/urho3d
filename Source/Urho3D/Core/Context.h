//
// Copyright (c) 2008-2016 the Urho3D project.
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
#include "../Container/HashSet.h"

namespace Urho3D
{

/// Urho3D execution context. Provides access to subsystems, object factories and attributes, and event receivers.
class URHO3D_API Context : public RefCounted
{
    friend class Object;

public:
    /// Construct.
    Context();
    /// Destruct.
    ~Context();

    /// Create an object by type. Return pointer to it or null if no factory found.
    template <class T> inline SharedPtr<T> CreateObject()
    {
        return StaticCast<T>(CreateObject(T::GetTypeStatic()));
    }
    /// Create an object by type hash. Return pointer to it or null if no factory found.
    SharedPtr<Object> CreateObject(StringHash objectType);
    /// Register a factory for an object type.
    void RegisterFactory(ObjectFactory* factory);
    /// Register a factory for an object type and specify the object category.
    void RegisterFactory(ObjectFactory* factory, const char* category);
    /// Register a subsystem.
    void RegisterSubsystem(Object* subsystem);
    /// Remove a subsystem.
    void RemoveSubsystem(StringHash objectType);
    /// Register object attribute.
    void RegisterAttribute(StringHash objectType, const AttributeInfo& attr);
    /// Remove object attribute.
    void RemoveAttribute(StringHash objectType, const char* name);
    /// Update object attribute's default value.
    void UpdateAttributeDefaultValue(StringHash objectType, const char* name, const Variant& defaultValue);
    /// Return a preallocated map for event data. Used for optimization to avoid constant re-allocation of event data maps.
    VariantMap& GetEventDataMap();

    /// Copy base class attributes to derived class.
    void CopyBaseAttributes(StringHash baseType, StringHash derivedType);
    /// Template version of registering an object factory.
    template <class T> void RegisterFactory();
    /// Template version of registering an object factory with category.
    template <class T> void RegisterFactory(const char* category);
    /// Template version of removing a subsystem.
    template <class T> void RemoveSubsystem();
    /// Template version of registering an object attribute.
    template <class T> void RegisterAttribute(const AttributeInfo& attr);
    /// Template version of removing an object attribute.
    template <class T> void RemoveAttribute(const char* name);
    /// Template version of copying base class attributes to derived class.
    template <class T, class U> void CopyBaseAttributes();
    /// Template version of updating an object attribute's default value.
    template <class T> void UpdateAttributeDefaultValue(const char* name, const Variant& defaultValue);

    /// Return subsystem by type.
    Object* GetSubsystem(StringHash type) const;
    
    /// Return global variable based on key
    const Variant& GetGlobalVar(StringHash key) const ;

    /// Return all global variables.
    const VariantMap& GetGlobalVars() const { return globalVars_; }

    /// Set global variable with the respective key and value
    void SetGlobalVar(StringHash key, const Variant& value);

    /// Return all subsystems.
    const HashMap<StringHash, SharedPtr<Object> >& GetSubsystems() const { return subsystems_; }

    /// Return all object factories.
    const HashMap<StringHash, SharedPtr<ObjectFactory> >& GetObjectFactories() const { return factories_; }

    /// Return all object categories.
    const HashMap<String, Vector<StringHash> >& GetObjectCategories() const { return objectCategories_; }

    /// Return active event sender. Null outside event handling.
    Object* GetEventSender() const;

    /// Return active event handler. Set by Object. Null outside event handling.
    EventHandler* GetEventHandler() const { return eventHandler_; }

    /// Return object type name from hash, or empty if unknown.
    const String& GetTypeName(StringHash objectType) const;
    /// Return a specific attribute description for an object, or null if not found.
    AttributeInfo* GetAttribute(StringHash objectType, const char* name);
    /// Template version of returning a subsystem.
    template <class T> T* GetSubsystem() const;
    /// Template version of returning a specific attribute description.
    template <class T> AttributeInfo* GetAttribute(const char* name);

    /// Return attribute descriptions for an object type, or null if none defined.
    const Vector<AttributeInfo>* GetAttributes(StringHash type) const
    {
        HashMap<StringHash, Vector<AttributeInfo> >::ConstIterator i = attributes_.Find(type);
        return i != attributes_.End() ? &i->second_ : 0;
    }

    /// Return network replication attribute descriptions for an object type, or null if none defined.
    const Vector<AttributeInfo>* GetNetworkAttributes(StringHash type) const
    {
        HashMap<StringHash, Vector<AttributeInfo> >::ConstIterator i = networkAttributes_.Find(type);
        return i != networkAttributes_.End() ? &i->second_ : 0;
    }

    /// Return all registered attributes.
    const HashMap<StringHash, Vector<AttributeInfo> >& GetAllAttributes() const { return attributes_; }

    /// Return event receivers for a sender and event type, or null if they do not exist.
    HashSet<Object*>* GetEventReceivers(Object* sender, StringHash eventType)
    {
        HashMap<Object*, HashMap<StringHash, HashSet<Object*> > >::Iterator i = specificEventReceivers_.Find(sender);
        if (i != specificEventReceivers_.End())
        {
            HashMap<StringHash, HashSet<Object*> >::Iterator j = i->second_.Find(eventType);
            return j != i->second_.End() ? &j->second_ : 0;
        }
        else
            return 0;
    }

    /// Return event receivers for an event type, or null if they do not exist.
    HashSet<Object*>* GetEventReceivers(StringHash eventType)
    {
        HashMap<StringHash, HashSet<Object*> >::Iterator i = eventReceivers_.Find(eventType);
        return i != eventReceivers_.End() ? &i->second_ : 0;
    }

private:
    /// Add event receiver.
    void AddEventReceiver(Object* receiver, StringHash eventType);
    /// Add event receiver for specific event.
    void AddEventReceiver(Object* receiver, Object* sender, StringHash eventType);
    /// Remove an event sender from all receivers. Called on its destruction.
    void RemoveEventSender(Object* sender);
    /// Remove event receiver from specific events.
    void RemoveEventReceiver(Object* receiver, Object* sender, StringHash eventType);
    /// Remove event receiver from non-specific events.
    void RemoveEventReceiver(Object* receiver, StringHash eventType);

    /// Set current event handler. Called by Object.
    void SetEventHandler(EventHandler* handler) { eventHandler_ = handler; }

    /// Begin event send.
    void BeginSendEvent(Object* sender) { eventSenders_.Push(sender); }

    /// End event send. Clean up event receivers removed in the meanwhile.
    void EndSendEvent() { eventSenders_.Pop(); }

    /// Object factories.
    HashMap<StringHash, SharedPtr<ObjectFactory> > factories_;
    /// Subsystems.
    HashMap<StringHash, SharedPtr<Object> > subsystems_;
    /// Attribute descriptions per object type.
    HashMap<StringHash, Vector<AttributeInfo> > attributes_;
    /// Network replication attribute descriptions per object type.
    HashMap<StringHash, Vector<AttributeInfo> > networkAttributes_;
    /// Event receivers for non-specific events.
    HashMap<StringHash, HashSet<Object*> > eventReceivers_;
    /// Event receivers for specific senders' events.
    HashMap<Object*, HashMap<StringHash, HashSet<Object*> > > specificEventReceivers_;
    /// Event sender stack.
    PODVector<Object*> eventSenders_;
    /// Event data stack.
    PODVector<VariantMap*> eventDataMaps_;
    /// Active event handler. Not stored in a stack for performance reasons; is needed only in esoteric cases.
    EventHandler* eventHandler_;
    /// Object categories.
    HashMap<String, Vector<StringHash> > objectCategories_;
    /// Variant map for global variables that can persist throughout application execution.
    VariantMap globalVars_;
};

template <class T> void Context::RegisterFactory() { RegisterFactory(new ObjectFactoryImpl<T>(this)); }

template <class T> void Context::RegisterFactory(const char* category)
{
    RegisterFactory(new ObjectFactoryImpl<T>(this), category);
}

template <class T> void Context::RemoveSubsystem() { RemoveSubsystem(T::GetTypeStatic()); }

template <class T> void Context::RegisterAttribute(const AttributeInfo& attr) { RegisterAttribute(T::GetTypeStatic(), attr); }

template <class T> void Context::RemoveAttribute(const char* name) { RemoveAttribute(T::GetTypeStatic(), name); }

template <class T, class U> void Context::CopyBaseAttributes() { CopyBaseAttributes(T::GetTypeStatic(), U::GetTypeStatic()); }

template <class T> T* Context::GetSubsystem() const { return static_cast<T*>(GetSubsystem(T::GetTypeStatic())); }

template <class T> AttributeInfo* Context::GetAttribute(const char* name) { return GetAttribute(T::GetTypeStatic(), name); }

template <class T> void Context::UpdateAttributeDefaultValue(const char* name, const Variant& defaultValue)
{
    UpdateAttributeDefaultValue(T::GetTypeStatic(), name, defaultValue);
}

}
