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

#ifndef COMMON_EVENTLISTENER_H
#define COMMON_EVENTLISTENER_H

#include "Event.h"

#include <list>

class EventListener;

//! Internal helper class for invoking event handler functions
class EventHandlerInvoker
{
public:
    //! Construct with specified listener
    EventHandlerInvoker(EventListener* listener) :
        mListener(listener)
    {
    }
    
    //! Destruct
    virtual ~EventHandlerInvoker() {}
    
    //! Invoke event handler
    virtual void invoke(StringHash eventType, VariantMap& eventData) = 0;
    
    //! Return event listener
    EventListener* getListener() const { return mListener; }
    
protected:
    //! Event listener
    EventListener* mListener;
    
private:
    //! Prevent copy construction
    EventHandlerInvoker(const EventHandlerInvoker& rhs);
    //! Prevent assignment
    EventHandlerInvoker& operator = (const EventHandlerInvoker& rhs);
};

//! Template version of the event handler invoker to store a function pointer of a specific class
template <class T> class EventHandlerInvokerImpl : public EventHandlerInvoker
{
public:
    typedef void (T::*HandlerFunctionPtr)(StringHash, VariantMap&);
    
    //! Construct with listener and function pointers
    EventHandlerInvokerImpl(T* listener, HandlerFunctionPtr handler) :
        EventHandlerInvoker(listener),
        mHandler(handler)
    {
    }
    
    //! Invoke event handler
    virtual void invoke(StringHash eventType, VariantMap& eventData)
    {
        T* listener = static_cast<T*>(mListener);
        (listener->*mHandler)(eventType, eventData);
    }
    
private:
    //! Prevent copy construction
    EventHandlerInvokerImpl(const EventHandlerInvokerImpl& rhs);
    //! Prevent assignment
    EventHandlerInvokerImpl& operator = (const EventHandlerInvokerImpl& rhs);
    
    //! Class-specific pointer to handler function
    HandlerFunctionPtr mHandler;
};

#define EVENT_HANDLER(classname, function) (new EventHandlerInvokerImpl<classname>(this, &classname::function))

//! Event listener
class EventListener
{
public:
    //! Construct
    EventListener();
    //! Destruct. Unsubscribe from all events and free event handlers
    virtual ~EventListener();
    
    //! Handle an event
    virtual void onEvent(EventListener* sender, StringHash eventType, VariantMap& eventData);
    
    //! Subscribe to an event that can be sent by any sender
    void subscribeToEvent(StringHash eventType, EventHandlerInvoker* handler);
    //! Subscribe to a specific sender's event
    void subscribeToEvent(EventListener* sender, StringHash eventType, EventHandlerInvoker* handler);
    //! Unsubscribe from an event
    void unsubscribeFromEvent(StringHash eventType);
    //! Unsubscribe from a specific sender's event
    void unsubscribeFromEvent(EventListener* sender, StringHash eventType);
    //! Unsubscribe from a specific sender's events
    void unsubscribeFromEvents(EventListener* sender);
    //! Unsubscribe from all events
    void unsubscribeFromAllEvents();
    //! Send event to all subscribers
    void sendEvent(StringHash eventType);
    //! Send event with parameters to all subscribers
    void sendEvent(StringHash eventType, VariantMap& eventData);
    //! Send event to a specific receiver
    void sendEvent(EventListener* receiver, StringHash eventType);
    //! Send event with parameters to a specific receiver
    void sendEvent(EventListener* receiver, StringHash eventType, VariantMap& eventData);
    
    //! Return whether has subscribed to an event
    bool hasSubscribedToEvent(StringHash eventType) const;
    //! Return whether has subscribed to a specific sender & event
    bool hasSubscribedToEvent(EventListener* sender, StringHash eventType) const;
    
    //! Remove event handlers related to a specific sender
    void removeSpecificEventHandlers(EventListener* sender);
    //! Remove event listener from specific events
    void removeEventListener(EventListener* sender, StringHash eventType);
    //! Remove event listener from non-specific events
    void removeEventListener(StringHash eventType);
    
protected:
    //! Event handlers for non-specific events
    std::map<StringHash, EventHandlerInvoker*> mEventHandlers;
    //! Event handlers for specific senders' events
    std::map<std::pair<EventListener*, StringHash>, EventHandlerInvoker*> mSpecificEventHandlers;
    
private:
    //! Prevent copy construction
    EventListener(const EventListener& rhs);
    //! Prevent assignment
    EventListener& operator = (const EventListener& rhs);
    
    //! Event listeners for non-specific events
    static std::map<StringHash, std::list<EventListener*> > sEventListeners;
    //! Event listeners for specific senders' events
    static std::map<std::pair<EventListener*, StringHash>, std::list<EventListener*> > sSpecificEventListeners;
};

//! Return event sender. Only non-null during the event handling
EventListener* getEventSender();

#endif // EVENT_EVENTLISTENER_H
