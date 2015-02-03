//
// Copyright (c) 2008-2015 the Urho3D project.
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

#pragma once

#include "../Core/Object.h"

namespace Urho3D
{

class EventHandlerCommand;
class LuaFunction;
class LuaScriptInstance;

class LuaScriptEventInvoker : public Object
{
    OBJECT(LuaScriptEventInvoker);

public:
    /// Construct.
    LuaScriptEventInvoker(Context* context);
    /// Construct from LuaScriptInstance.
    LuaScriptEventInvoker(LuaScriptInstance* instance);
    /// Destruct.
    virtual ~LuaScriptEventInvoker();

    /// Add a scripted event handler.
    void AddEventHandler(Object* sender, const StringHash& eventType, WeakPtr<LuaFunction> function);
    /// Remove a scripted event handler.
    void RemoveEventHandler(Object* sender, const StringHash& eventType, WeakPtr<LuaFunction> function);
    /// Remove all scripted event handlers.
    void RemoveAllEventHandlers(Object* sender);
    /// Remove all scripted event handlers, except those listed.
    void RemoveEventHandlersExcept(const PODVector<StringHash>& exceptionTypes);

private:
    /// Handle script event in Lua script.
    void HandleLuaScriptEvent(StringHash eventType, VariantMap& eventData);
    typedef Vector<WeakPtr<LuaFunction> > LuaFunctionVector;
    typedef HashMap<StringHash, LuaFunctionVector> EventTypeToLuaFunctionVectorMap;
    /// Return event type to Lua function vector map.
    EventTypeToLuaFunctionVectorMap& GetEventTypeToLuaFunctionVectorMap(Object* sender)
    {
        if (!sender)
            return eventTypeToLuaFunctionVectorMap;

        return senderEventTypeToLuaFunctionVectorMap[sender];
    }
    /// Execute then destory command.
    void ExecuteThenDestroyCommand(EventHandlerCommand* command);

    /// Lua script instance.
    LuaScriptInstance* instance_;
    /// Invoking.
    bool invoking_;
    /// Event handler commands.
    PODVector<EventHandlerCommand*> eventHandlerCommands_;
    /// Event type to Lua function vector map.
    EventTypeToLuaFunctionVectorMap eventTypeToLuaFunctionVectorMap;
    /// Event type to Lua function vector map for specific sender.
    HashMap<Object*, EventTypeToLuaFunctionVectorMap> senderEventTypeToLuaFunctionVectorMap;
};

}
