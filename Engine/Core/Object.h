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

#include "SharedPtr.h"
#include "Variant.h"

class Context;
class EventHandler;

/// Base class for objects with type identification, subsystem access and event sending/receiving capability
class Object : public RefCounted
{
public:
    /// Construct
    Object(Context* context);
    /// Destruct. Clean up self from event sender & receiver structures
    virtual ~Object();
    
    /// Return type
    virtual ShortStringHash GetType() const = 0;
    /// Return type name
    virtual const char* GetTypeName() const = 0;
    /// Handle event
    virtual void OnEvent(Object* sender, bool broadcast, StringHash eventType, VariantMap& eventData);
    
    /// Create object by type
    SharedPtr<Object> CreateObject(ShortStringHash type);
    /// Subscribe to an event that can be sent by any sender
    void SubscribeToEvent(StringHash eventType, EventHandler* handler);
    /// Subscribe to a specific sender's event
    void SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler);
    /// Unsubscribe from an event
    void UnsubscribeFromEvent(StringHash eventType);
    /// Unsubscribe from a specific sender's event
    void UnsubscribeFromEvent(Object* sender, StringHash eventType);
    /// Unsubscribe from a specific sender's events
    void UnsubscribeFromEvents(Object* sender);
    /// Unsubscribe from all events
    void UnsubscribeFromAllEvents();
    /// Unsubscribe from all events with userdata defined in the handler (possibly scripted)
    void UnsubscribeFromAllEventsWithUserData();
    /// Send event to all subscribers
    void SendEvent(StringHash eventType);
    /// Send event with parameters to all subscribers
    void SendEvent(StringHash eventType, VariantMap& eventData);
    /// Send event to a specific receiver
    void SendEvent(Object* receiver, StringHash eventType);
    /// Send event with parameters to a specific receiver
    void SendEvent(Object* receiver, StringHash eventType, VariantMap& eventData);
    /// Template version of creating an object
    template <class T> SharedPtr<T> CreateObject();
    
    /// Return typename as std::string
    std::string GetTypeNameStr() const { return std::string(GetTypeName()); }
    /// Return execution context
    Context* GetContext() const { return context_; }
    /// Return subsystem by type
    Object* GetSubsystem(ShortStringHash type) const;
    /// Return whether has subscribed to an event without specific sender
    bool HasSubscribed(StringHash eventType) const;
    /// Return whether has subscribed to a specific sender's event
    bool HasSubscribed(Object* sender, StringHash eventType) const;
    /// Return active event sender
    Object* GetSender() const;
    /// Template version of returning a subsystem
    template <class T> T* GetSubsystem() const;
    
    /// Remove event handlers related to a specific sender
    void RemoveEventSender(Object* sender);
    
protected:
    /// Execution context
    Context* context_;
    
private:
    /// Event handlers. Sender is null for non-specific handlers
    std::map<std::pair<Object*, StringHash>, EventHandler*> eventHandlers_;
};

template <class T> SharedPtr<T> Object::CreateObject()
{
    return StaticCast<T>(CreateObject(T::GetTypeStatic()));
}

template <class T> T* Object::GetSubsystem() const
{
    return static_cast<T*>(GetSubsystem(T::GetTypeStatic()));
}

/// Object factory
class ObjectFactory : public RefCounted
{
public:
    /// Construct
    ObjectFactory(Context* context) :
        context_(context)
    {
    }
    
    /// Create an object. Implemented in templated subclasses
    virtual SharedPtr<Object> CreateObject() = 0;
    
    /// Return execution context
    Context* GetContext() const { return context_; }
    /// Return type
    ShortStringHash GetType() const { return type_; }
    /// Return typename
    const char* GetTypeName() const { return typeName_; }
    /// Return typename as std::string
    std::string GetTypeNameStr() const { return std::string(typeName_); }
    
protected:
    /// Execution context
    Context* context_;
    /// Object type
    ShortStringHash type_;
    /// Object typename
    const char* typeName_;
};

/// Template implementation of the object factory
template <class T> class ObjectFactoryImpl : public ObjectFactory
{
public:
    /// Construct
    ObjectFactoryImpl(Context* context) :
        ObjectFactory(context)
    {
        type_ = T::GetTypeStatic();
        typeName_ = T::GetTypeNameStatic();
    }
    
    /// Create an object of the specific type
    virtual SharedPtr<Object>(CreateObject())
    {
        return SharedPtr<Object>(new T(context_));
    }
};

/// Internal helper class for invoking event handler functions
class EventHandler
{
public:
    /// Construct with specified receiver
    EventHandler(Object* receiver) :
        receiver_(receiver),
        userData_(0)
    {
    }
    
    /// Construct with specified receiver and userdata
    EventHandler(Object* receiver, void* userData) :
        receiver_(receiver),
        userData_(userData)
    {
    }
    
    /// Destruct
    virtual ~EventHandler() {}
    
    /// Invoke event handler function
    virtual void Invoke(StringHash eventType, VariantMap& eventData) = 0;
    
    /// Return event receiver
    Object* GetReceiver() const { return receiver_; }
    /// Return userdata
    void* GetUserData() const { return userData_; }
    
protected:
    /// Event receiver
    Object* receiver_;
    /// Userdata
    void* userData_;
};

/// Template implementation of the event handler invoke helper (stores a function pointer of specific class)
template <class T> class EventHandlerImpl : public EventHandler
{
public:
    typedef void (T::*HandlerFunctionPtr)(StringHash, VariantMap&);
    
    /// Construct with receiver and function pointers
    EventHandlerImpl(T* receiver, HandlerFunctionPtr function) :
        EventHandler(receiver),
        function_(function)
    {
    }
    
    /// Construct with receiver and function pointers and userdata
    EventHandlerImpl(T* receiver, HandlerFunctionPtr function, void* userData) :
        EventHandler(receiver, userData),
        function_(function)
    {
    }
    
    /// Invoke event handler function
    virtual void Invoke(StringHash eventType, VariantMap& eventData)
    {
        T* receiver = static_cast<T*>(receiver_);
        (receiver->*function_)(eventType, eventData);
    }
    
private:
    /// Class-specific pointer to handler function
    HandlerFunctionPtr function_;
};

#define OBJECT(typeName) \
    private: \
        static const ShortStringHash typeStatic; \
        static const char* typeNameStatic; \
    public: \
        virtual ShortStringHash GetType() const { return GetTypeStatic(); } \
        virtual const char* GetTypeName() const { return GetTypeNameStatic(); } \
        static ShortStringHash GetTypeStatic() \
        { \
            return typeStatic; \
        } \
        static const char* GetTypeNameStatic() \
        { \
            return typeNameStatic; \
        } \

#define OBJECTTYPESTATIC(typeName) \
    const ShortStringHash typeName::typeStatic(#typeName); \
    const char* typeName::typeNameStatic = #typeName; \

#define EVENT(eventID, eventName) static const StringHash eventID(#eventName); namespace eventName
#define PARAM(paraid_, paraname_) static const ShortStringHash paraid_(#paraname_)
#define HANDLER(className, function) (new EventHandlerImpl<className>(this, &className::function))
#define HANDLER_USERDATA(className, function, userData) (new EventHandlerImpl<className>(this, &className::function, userData))
