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

#include "EventListener.h"
#include "Log.h"
#include "Profiler.h"
#include "StringUtils.h"

#include "DebugNew.h"

std::map<StringHash, std::vector<EventListener*> > EventListener::sEventListeners;

EventListener::EventListener()
{
}

EventListener::~EventListener()
{
    unsubscribeFromAllEvents();
}

void EventListener::handleEvent(StringHash eventType, VariantMap& eventData)
{
    std::map<StringHash, EventHandlerInvoker*>::const_iterator i = mEventHandlers.find(eventType);
    if (i != mEventHandlers.end())
        i->second->invoke(eventType, eventData);
}

void EventListener::subscribeToEvent(StringHash eventType, EventHandlerInvoker* handler)
{
    if (!handler)
    {
        LOGERROR("Null event handler for event " + toString((int)eventType));
        return;
    }
    
    // If there already is a handler, delete it
    std::map<StringHash, EventHandlerInvoker*>::iterator i = mEventHandlers.find(eventType);
    if (i != mEventHandlers.end())
        delete i->second;
    
    mEventHandlers[eventType] = handler;
    
    std::vector<EventListener*>& listeners = sEventListeners[eventType];
    for (std::vector<EventListener*>::const_iterator j = listeners.begin(); j != listeners.end(); ++j)
    {
        // Check if already registered
        if (*j == this)
            return;
    }
    
    listeners.push_back(this);
}

void EventListener::unsubscribeFromEvent(StringHash eventType)
{
    std::map<StringHash, EventHandlerInvoker*>::iterator i = mEventHandlers.find(eventType);
    if (i != mEventHandlers.end())
    {
        delete i->second;
        mEventHandlers.erase(i);
    }
    
    std::vector<EventListener*>& listeners = sEventListeners[eventType];
    for (std::vector<EventListener*>::iterator j = listeners.begin(); j != listeners.end(); ++j)
    {
        if (*j == this)
        {
            listeners.erase(j);
            return;
        }
    }
}

void EventListener::unsubscribeFromAllEvents()
{
    for (std::map<StringHash, EventHandlerInvoker*>::iterator i = mEventHandlers.begin(); i != mEventHandlers.end(); ++i)
        delete i->second;
    
    mEventHandlers.clear();
    
    for (std::map<StringHash, std::vector<EventListener*> >::iterator i = sEventListeners.begin(); i != sEventListeners.end(); ++i)
    {
        std::vector<EventListener*>& listeners = i->second;
        for (std::vector<EventListener*>::iterator j = listeners.begin(); j != listeners.end(); ++j)
        {
            if (*j == this)
            {
                listeners.erase(j);
                break;
            }
        }
    }
}

bool EventListener::hasSubscribedToEvent(StringHash eventType) const
{
    return mEventHandlers.find(eventType) != mEventHandlers.end();
}
