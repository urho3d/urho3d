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

#include "../LuaScript/LuaFunction.h"
#include "../LuaScript/LuaScriptEventInvoker.h"
#include "../LuaScript/LuaScriptInstance.h"

#include "../DebugNew.h"

namespace Urho3D
{

LuaScriptEventInvoker::LuaScriptEventInvoker(Context* context) : 
    Object(context), 
    instance_(0)
{
}

LuaScriptEventInvoker::LuaScriptEventInvoker(LuaScriptInstance* instance) : 
    Object(instance->GetContext()), 
    instance_(instance)
{
}

LuaScriptEventInvoker::~LuaScriptEventInvoker()
{
}

void LuaScriptEventInvoker::AddEventHandler(Object* sender, const StringHash& eventType, WeakPtr<LuaFunction> function)
{
    EventTypeToLuaFunctionVectorMap& eventTypeToFunctionVectorMap = GetEventTypeToLuaFunctionVectorMap(sender);
    EventTypeToLuaFunctionVectorMap::Iterator i = eventTypeToFunctionVectorMap.Find(eventType);

    if (i == eventTypeToFunctionVectorMap.End())
    {
        eventTypeToFunctionVectorMap[eventType].Push(function);
        
        if (!sender)
            SubscribeToEvent(eventType, HANDLER(LuaScriptEventInvoker, HandleLuaScriptEvent));
        else
            SubscribeToEvent(sender, eventType, HANDLER(LuaScriptEventInvoker, HandleLuaScriptEvent));
    }
    else
    {
        if (!i->second_.Contains(function))
            i->second_.Push(function);
    }
}

void LuaScriptEventInvoker::RemoveEventHandler(Object* sender, const StringHash& eventType, WeakPtr<LuaFunction> function)
{
    EventTypeToLuaFunctionVectorMap& eventTypeToLuaFunctionVectorMap = GetEventTypeToLuaFunctionVectorMap(sender);
    EventTypeToLuaFunctionVectorMap::Iterator i = eventTypeToLuaFunctionVectorMap.Find(eventType);
    if (i == eventTypeToLuaFunctionVectorMap.End())
        return;

    if (function)
        i->second_.Remove(function);
    else
        i->second_.Clear();
    
    if (i->second_.Empty())
    {
        eventTypeToLuaFunctionVectorMap.Erase(i);

        if (!sender)
            UnsubscribeFromEvent(eventType);
        else
            UnsubscribeFromEvent(sender, eventType);
    }
}

void LuaScriptEventInvoker::RemoveAllEventHandlers(Object* sender)
{
    if (!sender)
    {
        UnsubscribeFromAllEvents();
        eventTypeToLuaFunctionVectorMap.Clear();
        senderEventTypeToLuaFunctionVectorMap.Clear();
    }
    else
    {
        UnsubscribeFromEvents(sender);
        senderEventTypeToLuaFunctionVectorMap.Erase(sender);
    }
}

void LuaScriptEventInvoker::RemoveEventHandlersExcept(const PODVector<StringHash>& exceptionTypes)
{
    for (unsigned i = 0; i < exceptionTypes.Size(); ++i)
        eventTypeToLuaFunctionVectorMap.Erase(exceptionTypes[i]);

    UnsubscribeFromAllEventsExcept(exceptionTypes, false);
}

void LuaScriptEventInvoker::HandleLuaScriptEvent(StringHash eventType, VariantMap& eventData)
{
    Object* sender = GetEventHandler()->GetSender();
    EventTypeToLuaFunctionVectorMap& eventTypeToLuaFunctionVectorMap = GetEventTypeToLuaFunctionVectorMap(sender);
    EventTypeToLuaFunctionVectorMap::Iterator i = eventTypeToLuaFunctionVectorMap.Find(eventType);
    if (i == eventTypeToLuaFunctionVectorMap.End())
        return;

    // Create a copy
    LuaFunctionVector luaFunctionVector = i->second_;

    if (instance_)
    {
        instance_->AddRef();

        for (unsigned i = 0; i < luaFunctionVector.Size(); ++i)
        {
            WeakPtr<LuaFunction>& function = luaFunctionVector[i];
            if (function && function->BeginCall(instance_))
            {
                function->PushUserType(eventType, "StringHash");
                function->PushUserType(eventData, "VariantMap");
                function->EndCall();
            }
        }
        
        instance_->ReleaseRef();
    }
    else
    {
        for (unsigned i = 0; i < luaFunctionVector.Size(); ++i)
        {
            WeakPtr<LuaFunction>& function = luaFunctionVector[i];
            if (function && function->BeginCall())
            {
                function->PushUserType(eventType, "StringHash");
                function->PushUserType(eventData, "VariantMap");
                function->EndCall();
            }
        }
    }
}

}
