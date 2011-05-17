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

#include "Attribute.h"
#include "Object.h"

#include "Map.h"
#include "Set.h"
#include "Vector.h"

/// Execution context within a process. Provides access to the subsystems, object factories and attributes, and event receivers
class Context : public RefCounted
{
public:
    /// Construct and create the Time & Profiler subsystems
    Context();
    /// Destruct
    ~Context();
    
    /// Create an object by type. Return pointer to it or null if no factory found
    SharedPtr<Object> CreateObject(ShortStringHash objectType);
    /// Register a factory for an object type. If exists already, will not be replaced
    void RegisterFactory(ObjectFactory* factory);
    /// Register a subsystem. If exists already, will not be replaced
    void RegisterSubsystem(Object* subsystem);
    /// Register object attribute
    void RegisterAttribute(ShortStringHash objectType, const AttributeInfo& attr);
    /// Remove object attribute
    void RemoveAttribute(ShortStringHash objectType, const String& name);
    /// Copy base class attributes to derived class
    void CopyBaseAttributes(ShortStringHash baseType, ShortStringHash derivedType);
    /// Add event receiver
    void AddEventReceiver(Object* receiver, StringHash eventType);
    /// Add event receiver for specific event
    void AddEventReceiver(Object* receiver, Object* sender, StringHash eventType);
    /// Remove an event sender from all receivers. Called on its destruction
    void RemoveEventSender(Object* sender);
    /// Remove event receiver from specific events
    void RemoveEventReceiver(Object* receiver, Object* sender, StringHash eventType);
    /// Remove event receiver from non-specific events
    void RemoveEventReceiver(Object* receiver, StringHash eventType);
    
    /// Set current event handler. Called by Object
    void SetEventHandler(EventHandler* handler)
    {
        handler_ = handler;
    }
    
    /// Begin event send
    void BeginSendEvent(Object* sender)
    {
        senders_.Push(sender);
    }
    
    /// End event send. Clean up event receivers removed in the meanwhile
    void EndSendEvent()
    {
        senders_.Pop();
    
        // Clean up dirtied event receiver groups when event handling finishes
        if (senders_.Empty())
        {
            if (!dirtySpecificReceivers_.Empty())
            {
                for (Set<Pair<Object*, StringHash> >::Iterator i = dirtySpecificReceivers_.Begin();
                    i != dirtySpecificReceivers_.End(); ++i)
                {
                    Vector<Object*>& receivers = specificReceivers_[*i];
                    for (Vector<Object*>::Iterator j = receivers.Begin(); j != receivers.End();)
                    {
                        if (*j == 0)
                            j = receivers.Erase(j);
                        else
                            ++j;
                    }
                }
                dirtySpecificReceivers_.Clear();
            }
            
            if (!dirtyReceivers_.Empty())
            {
                for (Set<StringHash>::Iterator i = dirtyReceivers_.Begin(); i != dirtyReceivers_.End(); ++i)
                {
                    Vector<Object*>& receivers = receivers_[*i];
                    for (Vector<Object*>::Iterator j = receivers.Begin(); j != receivers.End();)
                    {
                        if (*j == 0)
                            j = receivers.Erase(j);
                        else
                            ++j;
                    }
                }
                dirtyReceivers_.Clear();
            }
        }
    }
    
    /// Template version of registering an object factory
    template <class T> void RegisterFactory();
    /// Template version of registering an object attribute
    template <class T> void RegisterAttribute(const AttributeInfo& attr);
    /// Template version of removing an object attribue
    template <class T> void RemoveAttribute(const char* name);
    /// Template version of copying base class attributes to derived class
    template <class T, class U> void CopyBaseAttributes();
    
    /// Return subsystem by type
    Object* GetSubsystem(ShortStringHash type) const;
    /// Return all subsystems
    const Map<ShortStringHash, SharedPtr<Object> >& GetSubsystems() const { return subsystems_; }
    /// Return all object factories
    const Map<ShortStringHash, SharedPtr<ObjectFactory> >& GetObjectFactories() const { return factories_; }
    /// Return attributes for all object types
    const Map<ShortStringHash, Vector<AttributeInfo> >& GetAllAttributes() const { return attributes_; }
    /// Return active event sender. Null outside event handling
    Object* GetSender() const;
    /// Return active event handler. Set by Object. Null outside event handling
    EventHandler* GetHandler() const { return handler_; }
    /// Return object type name from hash, or empty if unknown
    const String& GetTypeName(ShortStringHash type) const;
    /// Template version of returning a subsystem
    template <class T> T* GetSubsystem() const;
    
    /// Return attribute descriptions for an object type, or null if none defined
    const Vector<AttributeInfo>* GetAttributes(ShortStringHash type) const
    {
        Map<ShortStringHash, Vector<AttributeInfo> >::ConstIterator i = attributes_.Find(type);
        return (i != attributes_.End()) ? &i->second_ : 0;
    }
    
    /// Return event receivers for a sender and event type, or null if they do not exist
    Vector<Object*>* GetReceivers(Object* sender, StringHash eventType)
    {
        Map<Pair<Object*, StringHash>, Vector<Object*> >::Iterator i = 
            specificReceivers_.Find(MakePair(sender, eventType));
        return (i != specificReceivers_.End()) ? &i->second_ : 0;
    }
    
    /// Return event receivers for an event type, or null if they do not exist
    Vector<Object*>* GetReceivers(StringHash eventType)
    {
        Map<StringHash, Vector<Object*> >::Iterator i = receivers_.Find(eventType);
        return (i != receivers_.End()) ? &i->second_ : 0;
    }
    
private:
    /// Object factories
    Map<ShortStringHash, SharedPtr<ObjectFactory> > factories_;
    /// Subsystems
    Map<ShortStringHash, SharedPtr<Object> > subsystems_;
    /// Attribute descriptions per object type
    Map<ShortStringHash, Vector<AttributeInfo> > attributes_;
    /// Event receivers for non-specific events
    Map<StringHash, Vector<Object*> > receivers_;
    /// Event receivers for specific senders' events
    Map<Pair<Object*, StringHash>, Vector<Object*> > specificReceivers_;
    /// Event sender stack
    Vector<Object*> senders_;
    /// Event types that have had receivers removed during event handling
    Set<StringHash> dirtyReceivers_;
    /// Event types for specific senders that have had receivers removed during event handling
    Set<Pair<Object*, StringHash> > dirtySpecificReceivers_;
    /// Active event handler. Not stored in a stack for performance reasons; is needed only in esoteric cases
    WeakPtr<EventHandler> handler_;
};

template <class T> void Context::RegisterFactory()
{
    RegisterFactory(new ObjectFactoryImpl<T>(this));
}

template <class T> void Context::RegisterAttribute(const AttributeInfo& attr)
{
    RegisterAttribute(T::GetTypeStatic(), attr);
}

template <class T> void Context::RemoveAttribute(const char* name)
{
    RemoveAttribute(T::GetTypeStatic(), name);
}

template <class T, class U> void Context::CopyBaseAttributes()
{
    CopyBaseAttributes(T::GetTypeStatic(), U::GetTypeStatic());
}

template <class T> T* Context::GetSubsystem() const
{
    return static_cast<T*>(GetSubsystem(T::GetTypeStatic()));
}
