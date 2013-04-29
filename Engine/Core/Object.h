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

#include "LinkedList.h"
#include "Ptr.h"
#include "Variant.h"

namespace Urho3D
{

class Context;
class EventHandler;

/// Base class for objects with type identification, subsystem access and event sending/receiving capability.
class Object : public RefCounted
{
    friend class Context;
    
public:
    /// Construct.
    Object(Context* context);
    /// Destruct. Clean up self from event sender & receiver structures.
    virtual ~Object();
    
    /// Return type hash.
    virtual ShortStringHash GetType() const = 0;
    /// Return type name.
    virtual const String& GetTypeName() const = 0;
    /// Handle event.
    virtual void OnEvent(Object* sender, StringHash eventType, VariantMap& eventData);
    
    /// Subscribe to an event that can be sent by any sender.
    void SubscribeToEvent(StringHash eventType, EventHandler* handler);
    /// Subscribe to a specific sender's event.
    void SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler);
    /// Unsubscribe from an event.
    void UnsubscribeFromEvent(StringHash eventType);
    /// Unsubscribe from a specific sender's event.
    void UnsubscribeFromEvent(Object* sender, StringHash eventType);
    /// Unsubscribe from a specific sender's events.
    void UnsubscribeFromEvents(Object* sender);
    /// Unsubscribe from all events.
    void UnsubscribeFromAllEvents();
    /// Unsubscribe from all events except those listed, and optionally only those with userdata (script registered events.)
    void UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData);
    /// Send event to all subscribers.
    void SendEvent(StringHash eventType);
    /// Send event with parameters to all subscribers.
    void SendEvent(StringHash eventType, VariantMap& eventData);
    
    /// Return execution context.
    Context* GetContext() const { return context_; }
    /// Return subsystem by type.
    Object* GetSubsystem(ShortStringHash type) const;
    /// Return active event sender. Null outside event handling.
    Object* GetEventSender() const;
    /// Return active event handler. Null outside event handling.
    EventHandler* GetEventHandler() const;
    /// Return whether has subscribed to an event without specific sender.
    bool HasSubscribedToEvent(StringHash eventType) const;
    /// Return whether has subscribed to a specific sender's event.
    bool HasSubscribedToEvent(Object* sender, StringHash eventType) const;
    /// Template version of returning a subsystem.
    template <class T> T* GetSubsystem() const;
    /// Return object category. Categories are (optionally) registered along with the object factory. Return an empty string if the object category is not registered.
    const String& GetCategory() const;
    
protected:
    /// Execution context.
    Context* context_;
    
private:
    /// Find the first event handler with no specific sender.
    EventHandler* FindEventHandler(StringHash eventType, EventHandler** previous = 0) const;
    /// Find the first event handler with specific sender.
    EventHandler* FindSpecificEventHandler(Object* sender, EventHandler** previous = 0) const;
    /// Find the first event handler with specific sender and event type.
    EventHandler* FindSpecificEventHandler(Object* sender, StringHash eventType, EventHandler** previous = 0) const;
    /// Remove event handlers related to a specific sender.
    void RemoveEventSender(Object* sender);
    
    /// Event handlers. Sender is null for non-specific handlers.
    LinkedList<EventHandler> eventHandlers_;
};

template <class T> T* Object::GetSubsystem() const { return static_cast<T*>(GetSubsystem(T::GetTypeStatic())); }

/// Base class for object factories.
class ObjectFactory : public RefCounted
{
public:
    /// Construct.
    ObjectFactory(Context* context) :
        context_(context)
    {
        assert(context_);
    }
    
    /// Create an object. Implemented in templated subclasses.
    virtual SharedPtr<Object> CreateObject() = 0;
    
    /// Return execution context.
    Context* GetContext() const { return context_; }
    /// Return type hash of objects created by this factory.
    ShortStringHash GetType() const { return type_; }
    /// Return type name of objects created by this factory.
    const String& GetTypeName() const { return typeName_; }
    
protected:
    /// Execution context.
    Context* context_;
    /// Object type.
    ShortStringHash type_;
    /// Object type name.
    String typeName_;
};

/// Template implementation of the object factory.
template <class T> class ObjectFactoryImpl : public ObjectFactory
{
public:
    /// Construct.
    ObjectFactoryImpl(Context* context) :
        ObjectFactory(context)
    {
        type_ = T::GetTypeStatic();
        typeName_ = T::GetTypeNameStatic();
    }
    
    /// Create an object of the specific type.
    virtual SharedPtr<Object>(CreateObject()) { return SharedPtr<Object>(new T(context_)); }
};

/// Internal helper class for invoking event handler functions.
class EventHandler : public LinkedListNode
{
public:
    /// Construct with specified receiver.
    EventHandler(Object* receiver) :
        receiver_(receiver),
        sender_(0),
        userData_(0)
    {
        assert(receiver_);
    }
    
    /// Construct with specified receiver and userdata.
    EventHandler(Object* receiver, void* userData) :
        receiver_(receiver),
        sender_(0),
        userData_(userData)
    {
        assert(receiver_);
    }
    
    /// Destruct.
    virtual ~EventHandler() {}
    
    /// Set sender and event type.
    void SetSenderAndEventType(Object* sender, StringHash eventType)
    {
        sender_ = sender;
        eventType_ = eventType;
    }
    
    /// Invoke event handler function.
    virtual void Invoke(VariantMap& eventData) = 0;
    
    /// Return event receiver.
    Object* GetReceiver() const { return receiver_; }
    /// Return event sender. Null if the handler is non-specific.
    Object* GetSender() const { return sender_; }
    /// Return event type.
    const StringHash& GetEventType() const { return eventType_; }
    /// Return userdata.
    void* GetUserData() const { return userData_; }
    
protected:
    /// Event receiver.
    Object* receiver_;
    /// Event sender.
    Object* sender_;
    /// Event type.
    StringHash eventType_;
    /// Userdata.
    void* userData_;
};

/// Template implementation of the event handler invoke helper (stores a function pointer of specific class.)
template <class T> class EventHandlerImpl : public EventHandler
{
public:
    typedef void (T::*HandlerFunctionPtr)(StringHash, VariantMap&);
    
    /// Construct with receiver and function pointers.
    EventHandlerImpl(T* receiver, HandlerFunctionPtr function) :
        EventHandler(receiver),
        function_(function)
    {
        assert(function_);
    }
    
    /// Construct with receiver and function pointers and userdata.
    EventHandlerImpl(T* receiver, HandlerFunctionPtr function, void* userData) :
        EventHandler(receiver, userData),
        function_(function)
    {
        assert(function_);
    }
    
    /// Invoke event handler function.
    virtual void Invoke(VariantMap& eventData)
    {
        T* receiver = static_cast<T*>(receiver_);
        (receiver->*function_)(eventType_, eventData);
    }
    
private:
    /// Class-specific pointer to handler function.
    HandlerFunctionPtr function_;
};

#define OBJECT(typeName) \
    private: \
        static const ShortStringHash typeStatic; \
        static const String typeNameStatic; \
    public: \
        virtual ShortStringHash GetType() const { return GetTypeStatic(); } \
        virtual const String& GetTypeName() const { return GetTypeNameStatic(); } \
        static ShortStringHash GetTypeStatic() { return typeStatic; } \
        static const String& GetTypeNameStatic() { return typeNameStatic; } \

#define OBJECTTYPESTATIC(typeName) \
    const ShortStringHash typeName::typeStatic(#typeName); \
    const String typeName::typeNameStatic(#typeName); \

#define EVENT(eventID, eventName) static const StringHash eventID(#eventName); namespace eventName
#define PARAM(paramID, paramName) static const ShortStringHash paramID(#paramName)
#define HANDLER(className, function) (new EventHandlerImpl<className>(this, &className::function))
#define HANDLER_USERDATA(className, function, userData) (new EventHandlerImpl<className>(this, &className::function, userData))

}
