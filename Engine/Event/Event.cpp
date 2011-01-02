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

static VariantMap noEventData;

void sendEvent(StringHash eventType)
{
    sendEvent(eventType, noEventData);
}

void sendEvent(StringHash eventType, VariantMap& eventData)
{
    std::vector<EventListener*>& listeners = EventListener::sEventListeners[eventType];
    for (unsigned i = 0; i < listeners.size(); ++i)
        listeners[i]->handleEvent(eventType, eventData);
}

void sendEvent(EventListener* receiver, StringHash eventType, bool direct)
{
    sendEvent(receiver, eventType, noEventData, direct);
}

void sendEvent(EventListener* receiver, StringHash eventType, VariantMap& eventData, bool direct)
{
    if ((direct) && (receiver))
        receiver->handleEvent(eventType, eventData);
    else
    {
        std::vector<EventListener*>& listeners = EventListener::sEventListeners[eventType];
        for (std::vector<EventListener*>::iterator i = listeners.begin(); i != listeners.end(); ++i)
        {
            if (*i == receiver)
            {
                (*i)->handleEvent(eventType, eventData);
                return;
            }
        }
    }
}
