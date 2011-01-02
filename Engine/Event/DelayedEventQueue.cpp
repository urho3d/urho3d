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

#include "DelayedEventQueue.h"

DelayedEventQueue::DelayedEventQueue()
{
}

DelayedEventQueue::~DelayedEventQueue()
{
}

void DelayedEventQueue::sendDelayedEvent(StringHash eventType, const VariantMap& eventData, float delay)
{
    mDelayedEvents.push_back(DelayedEvent(eventType, eventData, delay));
}

void DelayedEventQueue::sendDelayedEvent(EventListener* receiver, StringHash eventType, const VariantMap& eventData, float delay)
{
    if (!receiver)
        return;
    
    mDelayedEvents.push_back(DelayedEvent(receiver, eventType, eventData, delay));
}

void DelayedEventQueue::processDelayedEvents(float timeStep)
{
    for (std::vector<DelayedEvent>::iterator i = mDelayedEvents.begin(); i != mDelayedEvents.end();)
    {
        i->mDelay -= timeStep;
        if (i->mDelay <= 0.0f)
        {
            if (!i->mReceiver)
                sendEvent(i->mEventType, i->mEventData);
            else
                // The event receiver might not exist anymore, so use indirect send
                sendEvent(i->mReceiver, i->mEventType, i->mEventData, false);
            i = mDelayedEvents.erase(i);
        }
        else
            ++i;
    }
}

void DelayedEventQueue::clearDelayedEvents()
{
    mDelayedEvents.clear();
}

