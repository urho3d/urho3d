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
#include "ScriptEventListener.h"

void ScriptEventListener::removeEventHandler(StringHash eventType)
{
    for (std::map<std::pair<EventListener*, StringHash>, asIScriptFunction*>::iterator i = mSpecificEventHandlers.begin(); i !=
        mSpecificEventHandlers.end();)
    {
        std::map<std::pair<EventListener*, StringHash>, asIScriptFunction*>::iterator current = i++;
        if (current->first.second == eventType)
            mSpecificEventHandlers.erase(current);
    }
    
    std::map<StringHash, asIScriptFunction*>::iterator i = mEventHandlers.find(eventType);
    if (i != mEventHandlers.end())
        mEventHandlers.erase(i);
    
    unsubscribeFromEvent(eventType);
}

void ScriptEventListener::removeEventHandler(EventListener* sender, StringHash eventType)
{
    std::pair<EventListener*, StringHash> combination = std::make_pair(sender, eventType);
    
    std::map<std::pair<EventListener*, StringHash>, asIScriptFunction*>::iterator i = mSpecificEventHandlers.find(combination);
    if (i != mSpecificEventHandlers.end())
    {
        mSpecificEventHandlers.erase(i);
        unsubscribeFromEvent(sender, eventType);
    }
}

void ScriptEventListener::removeEventHandlers(EventListener* sender)
{
    for (std::map<std::pair<EventListener*, StringHash>, asIScriptFunction*>::iterator i = mSpecificEventHandlers.begin(); i !=
        mSpecificEventHandlers.end();)
    {
        std::map<std::pair<EventListener*, StringHash>, asIScriptFunction*>::iterator current = i++;
        if (current->first.first == sender)
            mSpecificEventHandlers.erase(current);
    }
    
    unsubscribeFromEvents(sender);
}

void ScriptEventListener::removeAllEventHandlers()
{
    // Note: we can not simply call unsubscribeFromAllEvents(), as for example ScriptInstance has its own internal
    // scene update event handlers, which must not be unsubscribed
    for (std::map<std::pair<EventListener*, StringHash>, asIScriptFunction*>::iterator i = mSpecificEventHandlers.begin(); i !=
        mSpecificEventHandlers.end(); ++i)
        unsubscribeFromEvent(i->first.first, i->first.second);
    
    mSpecificEventHandlers.clear();
    
    for (std::map<StringHash, asIScriptFunction*>::iterator i = mEventHandlers.begin(); i != mEventHandlers.end(); ++i)
        unsubscribeFromEvent(i->first);
    
    mEventHandlers.clear();
}
