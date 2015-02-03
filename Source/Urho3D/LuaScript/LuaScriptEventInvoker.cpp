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

class EventHandlerCommand
{
public:
    EventHandlerCommand(int type) : type_(type) { }
    virtual ~EventHandlerCommand() { }
    int type_;
};

struct AddOrRemoveEventHandlerCommand : public EventHandlerCommand
{
    enum { Type = 1 };
    AddOrRemoveEventHandlerCommand(bool add, Object* sender, const StringHash& eventType, WeakPtr<LuaFunction> function) : 
        EventHandlerCommand(Type), add_(add), sender_(sender), eventType_(eventType), function_(function)
    {
    }

    bool add_;
    Object* sender_;
    StringHash eventType_;
    WeakPtr<LuaFunction> function_;
};

struct RemoveAllEventHandlersCommand : public EventHandlerCommand
{    
    enum { Type = 2 };
    RemoveAllEventHandlersCommand(Object* sender) : EventHandlerCommand(Type), sender_(sender)
    {
    }

    Object* sender_;
};

struct RemoveEventHandlersExceptCommand : public EventHandlerCommand
{

    enum { Type = 3 };
    RemoveEventHandlersExceptCommand(const PODVector<StringHash>& exceptionTypes) : EventHandlerCommand(Type), exceptionTypes_(exceptionTypes)
    {
    }
    PODVector<StringHash> exceptionTypes_;
};

LuaScriptEventInvoker::LuaScriptEventInvoker(Context* context) : 
    Object(context), 
    instance_(0),
    invoking_(false)
{
}

LuaScriptEventInvoker::LuaScriptEventInvoker(LuaScriptInstance* instance) : 
    Object(instance->GetContext()), 
    instance_(instance),
    invoking_(false)
{
}

LuaScriptEventInvoker::~LuaScriptEventInvoker()
{
}

void LuaScriptEventInvoker::AddEventHandler(Object* sender, const StringHash& eventType, WeakPtr<LuaFunction> function)
{
    if (invoking_)
    {
        eventHandlerCommands_.Push(new AddOrRemoveEventHandlerCommand(true, sender, eventType, function));
        return;
    }

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
    if (invoking_)
    {
        eventHandlerCommands_.Push(new AddOrRemoveEventHandlerCommand(false, sender, eventType, function));
        return;
    }

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
    if (invoking_)
    {
        eventHandlerCommands_.Push(new RemoveAllEventHandlersCommand(sender));
        return;
    }

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
    if (invoking_)
    {
        eventHandlerCommands_.Push(new RemoveEventHandlersExceptCommand(exceptionTypes));
        return;
    }

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

    invoking_ = true;

    LuaFunctionVector& luaFunctionVector = i->second_;
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

    invoking_ = false;

    if (!eventHandlerCommands_.Empty())
    {
        for (unsigned i = 0; i < eventHandlerCommands_.Size(); ++i)
            ExecuteThenDestroyCommand(eventHandlerCommands_[i]);

        eventHandlerCommands_.Clear();
    }
}

void LuaScriptEventInvoker::ExecuteThenDestroyCommand(EventHandlerCommand* command)
{
    if (!command)
        return;

    switch (command->type_)
    {
    case AddOrRemoveEventHandlerCommand::Type:
        {
            AddOrRemoveEventHandlerCommand* theCommand = (AddOrRemoveEventHandlerCommand*)command;
            if (theCommand->add_)
                AddEventHandler(theCommand->sender_, theCommand->eventType_, theCommand->function_);
            else
                RemoveEventHandler(theCommand->sender_, theCommand->eventType_, theCommand->function_);
        }
        break;

    case RemoveAllEventHandlersCommand::Type:
        {
            RemoveAllEventHandlersCommand* theCommand = (RemoveAllEventHandlersCommand*)command;
            RemoveAllEventHandlers(theCommand->sender_);
        }
        break;

    case RemoveEventHandlersExceptCommand::Type:
        {
            RemoveEventHandlersExceptCommand* theCommand = (RemoveEventHandlersExceptCommand*)command;
            RemoveEventHandlersExcept(theCommand->exceptionTypes_);
        }
        break;
    }

    delete command;
}

}
