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

#ifndef EVENT_DELAYEDEVENTQUEUE_H
#define EVENT_DELAYEDEVENTQUEUE_H

#include "Event.h"

class EventListener;

//! Delayed event
struct DelayedEvent
{
    //! Construct with no event data
    DelayedEvent() :
        mReceiver(0),
        mDelay(0.0f)
    {
    }
    
    //! Construct with event data but no receiver
    DelayedEvent(StringHash eventType, const VariantMap& eventData, float delay) :
        mReceiver(0),
        mEventType(eventType),
        mEventData(eventData),
        mDelay(delay)
    {
    }
    
    //! Construct with event data and receiver
    DelayedEvent(EventListener* receiver, StringHash eventType, const VariantMap& eventData, float delay) :
        mReceiver(receiver),
        mEventType(eventType),
        mEventData(eventData),
        mDelay(delay)
    {
    }
    
    //! Event receiver
    EventListener* mReceiver;
    //! Event type
    StringHash mEventType;
    //! Event parameters
    VariantMap mEventData;
    //! Delay until sending
    float mDelay;
};

//! Stores delayed events
class DelayedEventQueue
{
public:
    //! Construct
    DelayedEventQueue();
    //! Destruct
    virtual ~DelayedEventQueue();
    
    //! Store a delayed event with no receiver specified
    void sendDelayedEvent(StringHash eventType, const VariantMap& eventData = VariantMap(), float delay = 0.0f);
    //! Store a delayed event with receiver specified
    void sendDelayedEvent(EventListener* receiver, StringHash eventType, const VariantMap& eventData = VariantMap(), float delay = 0.0f);
    //! Update delay timers and send events as necessary
    void processDelayedEvents(float timeStep);
    //! Clear all delayed events
    void clearDelayedEvents();
    
    //! Return all delayed events
    const std::vector<DelayedEvent>& getDelayedEvents() const { return mDelayedEvents; }
    
private:
    //! Delayed events
    std::vector<DelayedEvent> mDelayedEvents;
};

#endif // EVENT_DELAYEDEVENTQUEUE_H
