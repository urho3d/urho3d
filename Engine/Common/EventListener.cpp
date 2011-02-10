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

#include "Precompiled.h"
#include "EventListener.h"
#include "Log.h"
#include "Profiler.h"
#include "StringUtils.h"

#include <set>

#include "DebugNew.h"

static VariantMap noEventData;

std::map<StringHash, std::vector<EventListener*> > EventListener::sEventListeners;
std::map<std::pair<EventListener*, StringHash>, std::vector<EventListener*> > EventListener::sSpecificEventListeners;

EventListener* eventSender = 0;

EventListener::EventListener()
{
}

EventListener::~EventListener()
{
    unsubscribeFromAllEvents();
    
    // Remove from all specific event listeners
    for (std::map<std::pair<EventListener*, StringHash>, std::vector<EventListener*> >::iterator i = sSpecificEventListeners.begin();
        i != sSpecificEventListeners.end();)
    {
        std::map<std::pair<EventListener*, StringHash>, std::vector<EventListener*> >::iterator current = i;
        ++i;
        if (current->first.first == this)
        {
            std::vector<EventListener*>& listeners = current->second;
            for (std::vector<EventListener*>::iterator j = listeners.begin(); j != listeners.end(); ++j)
                (*j)->removeSpecificEventHandlers(this);
            sSpecificEventListeners.erase(current);
        }
    }
}

void EventListener::onEvent(EventListener* sender, StringHash eventType, VariantMap& eventData)
{
    // Check first the specific event handlers, which have priority
    std::map<std::pair<EventListener*, StringHash>, EventHandlerInvoker*>::const_iterator i = mSpecificEventHandlers.find(
        std::make_pair(sender, eventType));
    if (i != mSpecificEventHandlers.end())
    {
        i->second->invoke(eventType, eventData);
        return;
    }
    
    std::map<StringHash, EventHandlerInvoker*>::const_iterator j = mEventHandlers.find(eventType);
    if (j != mEventHandlers.end())
        j->second->invoke(eventType, eventData);
}

void EventListener::subscribeToEvent(StringHash eventType, EventHandlerInvoker* handler)
{
    if (!handler)
    {
        LOGERROR("Null event handler for event " + toString(eventType));
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

void EventListener::subscribeToEvent(EventListener* sender, StringHash eventType, EventHandlerInvoker* handler)
{
    if (!sender)
    {
        LOGERROR("Null event sender for event " + toString(eventType));
        return;
    }
    
    if (!handler)
    {
        LOGERROR("Null event handler for event " + toString(eventType));
        return;
    }
    
    std::pair<EventListener*, StringHash> combination(sender, eventType);
    
    // If there already is a handler, delete it
    std::map<std::pair<EventListener*, StringHash>, EventHandlerInvoker*>::iterator i = mSpecificEventHandlers.find(combination);
    if (i != mSpecificEventHandlers.end())
        delete i->second;
    
    mSpecificEventHandlers[combination] = handler;
    
    std::vector<EventListener*>& listeners = sSpecificEventListeners[combination];
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
    // Check first specific events
    for (std::map<std::pair<EventListener*, StringHash>, EventHandlerInvoker*>::iterator i = mSpecificEventHandlers.begin();
        i != mSpecificEventHandlers.end();)
    {
        std::map<std::pair<EventListener*, StringHash>, EventHandlerInvoker*>::iterator current = i;
        ++i;
        if (current->first.second == eventType)
        {
            removeEventListener(current->first.first, current->first.second);
            delete current->second;
            mSpecificEventHandlers.erase(current);
        }
    }
    
    // Then non-specific
    std::map<StringHash, EventHandlerInvoker*>::iterator i = mEventHandlers.find(eventType);
    if (i != mEventHandlers.end())
    {
        removeEventListener(i->first);
        delete i->second;
        mEventHandlers.erase(i);
    }
}

void EventListener::unsubscribeFromEvent(EventListener* sender, StringHash eventType)
{
    std::pair<EventListener*, StringHash> combination(sender, eventType);
    
    std::map<std::pair<EventListener*, StringHash>, EventHandlerInvoker*>::iterator i = mSpecificEventHandlers.find(combination);
    if (i != mSpecificEventHandlers.end())
    {
        removeEventListener(i->first.first, i->first.second);
        delete i->second;
        mSpecificEventHandlers.erase(i);
    }
}

void EventListener::unsubscribeFromEvents(EventListener* sender)
{
    for (std::map<std::pair<EventListener*, StringHash>, EventHandlerInvoker*>::iterator i = mSpecificEventHandlers.begin();
        i != mSpecificEventHandlers.end();)
    {
        std::map<std::pair<EventListener*, StringHash>, EventHandlerInvoker*>::iterator current = i;
        ++i;
        if (current->first.first == sender)
        {
            removeEventListener(current->first.first, current->first.second);
            delete current->second;
            mSpecificEventHandlers.erase(current);
        }
    }
}

void EventListener::unsubscribeFromAllEvents()
{
    for (std::map<std::pair<EventListener*, StringHash>, EventHandlerInvoker*>::iterator i = mSpecificEventHandlers.begin();
        i != mSpecificEventHandlers.end(); ++i)
    {
        removeEventListener(i->first.first, i->first.second);
        delete i->second;
    }
    
    mSpecificEventHandlers.clear();
    
    for (std::map<StringHash, EventHandlerInvoker*>::iterator i = mEventHandlers.begin(); i != mEventHandlers.end(); ++i)
    {
        removeEventListener(i->first);
        delete i->second;
    }
    
    mEventHandlers.clear();
}

void EventListener::sendEvent(StringHash eventType)
{
    sendEvent(eventType, noEventData);
}

void EventListener::sendEvent(StringHash eventType, VariantMap& eventData)
{
    eventSender = this;
    
    std::set<EventListener*> processed;
    
    // Check first the specific event listeners
    std::map<std::pair<EventListener*, StringHash>, std::vector<EventListener*> >::const_iterator i = sSpecificEventListeners.find(
        std::make_pair(this, eventType));
    if (i != sSpecificEventListeners.end())
    {
        const std::vector<EventListener*>& listeners = i->second;
        // Iterate in reverse direction in case listeners remove themselves as a response
        for (unsigned j = listeners.size() - 1; j < listeners.size(); --j)
        {
            listeners[j]->onEvent(this, eventType, eventData);
            processed.insert(listeners[j]);
        }
    }
    
    // Then the non-specific listeners
    std::map<StringHash, std::vector<EventListener*> >::const_iterator j = sEventListeners.find(eventType);
    if (j == sEventListeners.end())
    {
        eventSender = 0;
        return;
    }
    const std::vector<EventListener*>& listeners = j->second;
    if (processed.empty())
    {
        for (unsigned k = listeners.size() - 1; k < listeners.size(); --k)
            listeners[k]->onEvent(this, eventType, eventData);
    }
    else
    {
        // If there were specific listeners, check that the event is not sent doubly to them
        for (unsigned k = listeners.size() - 1; k < listeners.size(); --k)
        {
            if (processed.find(listeners[k]) == processed.end())
                listeners[k]->onEvent(this, eventType, eventData);
        }
    }
    
    eventSender = 0;
}

void EventListener::sendEvent(EventListener* receiver, StringHash eventType)
{
    if (receiver)
        receiver->onEvent(this, eventType, noEventData);
}

void EventListener::sendEvent(EventListener* receiver, StringHash eventType, VariantMap& eventData)
{
    if (receiver)
        receiver->onEvent(this, eventType, eventData);
}

bool EventListener::hasSubscribedToEvent(StringHash eventType) const
{
    return mEventHandlers.find(eventType) != mEventHandlers.end();
}

bool EventListener::hasSubscribedToEvent(EventListener* sender, StringHash eventType) const
{
    return mSpecificEventHandlers.find(std::make_pair(sender, eventType)) != mSpecificEventHandlers.end();
}

void EventListener::removeSpecificEventHandlers(EventListener* sender)
{
    for (std::map<std::pair<EventListener*, StringHash>, EventHandlerInvoker*>::iterator i = mSpecificEventHandlers.begin();
        i != mSpecificEventHandlers.end();)
    {
        std::map<std::pair<EventListener*, StringHash>, EventHandlerInvoker*>::iterator current = i;
        ++i;
        if (current->first.first == sender)
        {
            delete current->second;
            mSpecificEventHandlers.erase(current);
        }
    }
}

void EventListener::removeEventListener(StringHash eventType)
{
    std::vector<EventListener*>& listeners = sEventListeners[eventType];
    for (std::vector<EventListener*>::iterator i = listeners.begin(); i != listeners.end(); ++i)
    {
        if (*i == this)
        {
            listeners.erase(i);
            return;
        }
    }
}

void EventListener::removeEventListener(EventListener* sender, StringHash eventType)
{
    std::vector<EventListener*>& listeners = sSpecificEventListeners[std::make_pair(sender, eventType)];
    for (std::vector<EventListener*>::iterator i = listeners.begin(); i != listeners.end(); ++i)
    {
        if (*i == this)
        {
            listeners.erase(i);
            return;
        }
    }
}

EventListener* getEventSender()
{
    return eventSender;
}
