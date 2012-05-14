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
#include "HashMap.h"
#include "HashSet.h"

/// Urho3D execution context. Provides access to subsystems, object factories and attributes, and event receivers.
class Context : public RefCounted
{
    friend class Object;
    
public:
    /// Construct.
    Context();
    /// Destruct.
    ~Context();
    
    /// Create an object by type hash. Return pointer to it or null if no factory found.
    SharedPtr<Object> CreateObject(ShortStringHash objectType);
    /// Register a factory for an object type.
    void RegisterFactory(ObjectFactory* factory);
    /// Register a subsystem.
    void RegisterSubsystem(Object* subsystem);
    /// Remove a subsystem.
    void RemoveSubsystem(ShortStringHash objectType);
    /// Register object attribute.
    void RegisterAttribute(ShortStringHash objectType, const AttributeInfo& attr);
    /// Remove object attribute.
    void RemoveAttribute(ShortStringHash objectType, const String& name);
    /// Copy base class attributes to derived class.
    void CopyBaseAttributes(ShortStringHash baseType, ShortStringHash derivedType);
    /// Template version of registering an object factory.
    template <class T> void RegisterFactory();
    /// Template version of removing a subsystem.
    template <class T> void RemoveSubsystem();
    /// Template version of registering an object attribute.
    template <class T> void RegisterAttribute(const AttributeInfo& attr);
    /// Template version of removing an object attribute.
    template <class T> void RemoveAttribute(const String& name);
    /// Template version of copying base class attributes to derived class.
    template <class T, class U> void CopyBaseAttributes();
    
    /// Return subsystem by type.
    Object* GetSubsystem(ShortStringHash type) const;
    /// Return all subsystems.
    const HashMap<ShortStringHash, SharedPtr<Object> >& GetSubsystems() const { return subsystems_; }
    /// Return all object factories.
    const HashMap<ShortStringHash, SharedPtr<ObjectFactory> >& GetObjectFactories() const { return factories_; }
    /// Return active event sender. Null outside event handling.
    Object* GetEventSender() const;
    /// Return active event handler. Set by Object. Null outside event handling.
    EventHandler* GetEventHandler() const { return eventHandler_; }
    /// Return object type name from hash, or empty if unknown.
    const String& GetTypeName(ShortStringHash type) const;
    /// Template version of returning a subsystem.
    template <class T> T* GetSubsystem() const;
    
    /// Return attribute descriptions for an object type, or null if none defined.
    const Vector<AttributeInfo>* GetAttributes(ShortStringHash type) const
    {
        HashMap<ShortStringHash, Vector<AttributeInfo> >::ConstIterator i = attributes_.Find(type);
        return i != attributes_.End() ? &i->second_ : 0;
    }
    
    /// Return network replication attribute descriptions for an object type, or null if none defined.
    const Vector<AttributeInfo>* GetNetworkAttributes(ShortStringHash type) const
    {
        HashMap<ShortStringHash, Vector<AttributeInfo> >::ConstIterator i = networkAttributes_.Find(type);
        return i != networkAttributes_.End() ? &i->second_ : 0;
    }
    
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
    /// %Set current event handler. Called by Object.
    void SetEventHandler(EventHandler* handler) { eventHandler_ = handler; }
    /// Begin event send.
    void BeginSendEvent(Object* sender) { eventSenders_.Push(sender); }
    /// End event send. Clean up event receivers removed in the meanwhile.
    void EndSendEvent();

    /// Object factories.
    HashMap<ShortStringHash, SharedPtr<ObjectFactory> > factories_;
    /// Subsystems.
    HashMap<ShortStringHash, SharedPtr<Object> > subsystems_;
    /// Attribute descriptions per object type.
    HashMap<ShortStringHash, Vector<AttributeInfo> > attributes_;
    /// Network replication attribute descriptions per object type.
    HashMap<ShortStringHash, Vector<AttributeInfo> > networkAttributes_;
    /// Event receivers for non-specific events.
    HashMap<StringHash, HashSet<Object*> > eventReceivers_;
    /// Event receivers for specific senders' events.
    HashMap<Object*, HashMap<StringHash, HashSet<Object*> > > specificEventReceivers_;
    /// Event sender stack.
    PODVector<Object*> eventSenders_;
    /// Active event handler. Not stored in a stack for performance reasons; is needed only in esoteric cases.
    EventHandler* eventHandler_;
};

template <class T> void Context::RegisterFactory() { RegisterFactory(new ObjectFactoryImpl<T>(this)); }
template <class T> void Context::RemoveSubsystem() { RemoveSubsystem(T::GetTypeStatic()); }
template <class T> void Context::RegisterAttribute(const AttributeInfo& attr) { RegisterAttribute(T::GetTypeStatic(), attr); }
template <class T> void Context::RemoveAttribute(const String& name) { RemoveAttribute(T::GetTypeStatic(), name); }
template <class T, class U> void Context::CopyBaseAttributes() { CopyBaseAttributes(T::GetTypeStatic(), U::GetTypeStatic()); }
template <class T> T* Context::GetSubsystem() const { return static_cast<T*>(GetSubsystem(T::GetTypeStatic())); }
