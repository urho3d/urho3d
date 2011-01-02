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

#ifndef EVENT_EVENTLISTENER_H
#define EVENT_EVENTLISTENER_H

#include "Event.h"

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
    friend void sendEvent(StringHash eventType, VariantMap& eventData);
    friend void sendEvent(EventListener* receiver, StringHash eventType, VariantMap& eventData, bool direct);
    
public:
    //! Construct
    EventListener();
    //! Destruct. Unsubscribe from all events and free event handlers
    virtual ~EventListener();
    
    //! Handle an event
    virtual void handleEvent(StringHash eventType, VariantMap& eventData);
    
    //! Subscribe to an event with a specified handler function
    void subscribeToEvent(StringHash eventType, EventHandlerInvoker* handler);
    //! Unsubscribe from an event
    void unsubscribeFromEvent(StringHash eventType);
    //! Unsubscribe from all events
    void unsubscribeFromAllEvents();
    //! Return whether has subscribed to a specific event
    bool hasSubscribedToEvent(StringHash eventType) const;
    
protected:
    //! Event handlers
    std::map<StringHash, EventHandlerInvoker*> mEventHandlers;
    
private:
    //! Prevent copy construction
    EventListener(const EventListener& rhs);
    //! Prevent assignment
    EventListener& operator = (const EventListener& rhs);
    
    //! Event listeners per event
    static std::map<StringHash, std::vector<EventListener*> > sEventListeners;
};

#endif // EVENT_EVENTLISTENER_H
