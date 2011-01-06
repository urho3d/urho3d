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

#ifndef SCRIPT_SCRIPTEVENTLISTENER_H
#define SCRIPT_SCRIPTEVENTLISTENER_H

#include "EventListener.h"

class asIScriptFunction;

class ScriptEventListener : public EventListener
{
public:
    //! Add an event handler. Called by script exposed version of subscribeToEvent()
    virtual void addEventHandler(StringHash eventType, const std::string& handlerName) = 0;
    //! Remove an event handler. Called by script exposed version of unsubcribeFromEvent()
    void removeEventHandler(StringHash eventType);
    //! Remove all event handlers. Called by script exposed version of unsubscribeFromAllEvents()
    void removeAllEventHandlers();
    
protected:
    //! Pointers to event handler functions or methods
    std::map<StringHash, asIScriptFunction*> mEventHandlers;
};

#endif // SCRIPT_SCRIPTEVENTLISTENER_H
