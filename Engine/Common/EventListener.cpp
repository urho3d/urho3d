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

std::vector<EventListener*> eventSenders;
std::set<StringHash> dirtyEventListeners;
std::set<std::pair<EventListener*, StringHash> > dirtySpecificEventListeners;
EventHandlerInvoker* invoker = 0;

EventListener::EventListener()
{
}

EventListener::~EventListener()
{
    // Check if event sender is destroyed during event handling
    for (unsigned i = 0; i < eventSenders.size(); ++i)
    {
        if (eventSenders[i] == this)
            eventSenders[i] = 0;
    }
    
    unsubscribeFromAllEvents();
    
    // Remove from all specific event listeners
    for (std::map<std::pair<EventListener*, StringHash>, std::vector<EventListener*> >::iterator i = sSpecificEventListeners.begin();
        i != sSpecificEventListeners.end();)
    {
        std::map<std::pair<EventListener*, StringHash>, std::vector<EventListener*> >::iterator current = i++;
        if (current->first.first == this)
        {
            std::vector<EventListener*>& listeners = current->second;
            for (std::vector<EventListener*>::iterator j = listeners.begin(); j != listeners.end(); ++j)
            {
                if (*j)
                    (*j)->removeSpecificEventHandlers(this);
            }
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
        invoker = i->second;
        i->second->invoke(eventType, eventData);
        return;
    }
    
    std::map<StringHash, EventHandlerInvoker*>::const_iterator j = mEventHandlers.find(eventType);
    if (j != mEventHandlers.end())
    {
        invoker = j->second;
        j->second->invoke(eventType, eventData);
    }
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
        std::map<std::pair<EventListener*, StringHash>, EventHandlerInvoker*>::iterator current = i++;
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
        std::map<std::pair<EventListener*, StringHash>, EventHandlerInvoker*>::iterator current = i++;
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
    std::set<EventListener*> processed;
    
    beginSendEvent();
    
    // Check first the specific event listeners
    std::map<std::pair<EventListener*, StringHash>, std::vector<EventListener*> >::const_iterator i = sSpecificEventListeners.find(
        std::make_pair(this, eventType));
    if (i != sSpecificEventListeners.end())
    {
        const std::vector<EventListener*>& listeners = i->second;
        for (unsigned j = 0; j < listeners.size(); ++j)
        {
            EventListener* listener = listeners[j];
            if (listener)
            {
                processed.insert(listener);
                listener->onEvent(this, eventType, eventData);
                // If handling the event caused self to be destroyed, exit immediately!
                if (getEventSender() != this)
                {
                    endSendEvent();
                    return;
                }
            }
        }
    }
    
    // Then the non-specific listeners
    std::map<StringHash, std::vector<EventListener*> >::const_iterator j = sEventListeners.find(eventType);
    if (j != sEventListeners.end())
    {
        const std::vector<EventListener*>& listeners = j->second;
        if (processed.empty())
        {
            for (unsigned k = 0; k < listeners.size(); ++k)
            {
                EventListener* listener = listeners[k];
                if (listener)
                {
                    listener->onEvent(this, eventType, eventData);
                    if (getEventSender() != this)
                    {
                        endSendEvent();
                        return;
                    }
                }
            }
        }
        else
        {
            // If there were specific listeners, check that the event is not sent doubly to them
            for (unsigned k = 0; k < listeners.size(); ++k)
            {
                EventListener* listener = listeners[k];
                if ((listener) && (processed.find(listener) == processed.end()))
                {
                    listener->onEvent(this, eventType, eventData);
                    if (getEventSender() != this)
                    {
                        endSendEvent();
                        return;
                    }
                }
            }
        }
    }
    
    endSendEvent();
}

void EventListener::sendEvent(EventListener* receiver, StringHash eventType)
{
    if (receiver)
    {
        beginSendEvent();
        receiver->onEvent(this, eventType, noEventData);
        endSendEvent();
    }
}

void EventListener::sendEvent(EventListener* receiver, StringHash eventType, VariantMap& eventData)
{
    if (receiver)
    {
        beginSendEvent();
        receiver->onEvent(this, eventType, eventData);
        endSendEvent();
    }
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
        std::map<std::pair<EventListener*, StringHash>, EventHandlerInvoker*>::iterator current = i++;
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
            // If no event handling going on, can erase the listener. Otherwise reset the pointer and clean up later
            if (eventSenders.empty())
                listeners.erase(i);
            else
            {
                *i = 0;
                dirtyEventListeners.insert(eventType);
            }
            return;
        }
    }
}

void EventListener::removeEventListener(EventListener* sender, StringHash eventType)
{
    std::pair<EventListener*, StringHash> combination(sender, eventType);
    std::vector<EventListener*>& listeners = sSpecificEventListeners[combination];
    for (std::vector<EventListener*>::iterator i = listeners.begin(); i != listeners.end(); ++i)
    {
        if (*i == this)
        {
            if (eventSenders.empty())
                listeners.erase(i);
            else
            {
                *i = 0;
                dirtySpecificEventListeners.insert(combination);
            }
            return;
        }
    }
}

EventHandlerInvoker* EventListener::getInvoker()
{
    return invoker;
}

void EventListener::beginSendEvent()
{
    eventSenders.push_back(this);
}

void EventListener::endSendEvent()
{
    eventSenders.pop_back();
    
    // If event handling has ended, clean up listeners that were removed during event handling
    if (eventSenders.empty())
        cleanupEventListeners();
}

void EventListener::cleanupEventListeners()
{
    if (!dirtySpecificEventListeners.empty())
    {
        for (std::set<std::pair<EventListener*, StringHash> >::iterator i = dirtySpecificEventListeners.begin(); i != dirtySpecificEventListeners.end(); ++i)
        {
            std::vector<EventListener*>& listeners = sSpecificEventListeners[*i];
            for (std::vector<EventListener*>::iterator j = listeners.begin(); j != listeners.end();)
            {
                if (*j == 0)
                    j = listeners.erase(j);
                else
                    ++j;
            }
        }
        dirtySpecificEventListeners.clear();
    }
    
    if (!dirtyEventListeners.empty())
    {
        for (std::set<StringHash>::iterator i = dirtyEventListeners.begin(); i != dirtyEventListeners.end(); ++i)
        {
            std::vector<EventListener*>& listeners = sEventListeners[*i];
            for (std::vector<EventListener*>::iterator j = listeners.begin(); j != listeners.end();)
            {
                if (*j == 0)
                    j = listeners.erase(j);
                else
                    ++j;
            }
        }
        dirtyEventListeners.clear();
    }
}

EventListener* getEventSender()
{
    if (eventSenders.size())
        return eventSenders.back();
    else
        return 0;
}
