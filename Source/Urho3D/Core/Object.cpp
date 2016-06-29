//
// Copyright (c) 2008-2016 the Urho3D project.
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

#include "../Precompiled.h"

#include "../Core/Context.h"
#include "../Core/Thread.h"
#include "../IO/Log.h"
#include "../Core/EventProfiler.h"
#include "../Container/HashMap.h"

#include "../DebugNew.h"


namespace Urho3D
{

TypeInfo::TypeInfo(const char* typeName, const TypeInfo* baseTypeInfo) :
    type_(typeName),
    typeName_(typeName),
    baseTypeInfo_(baseTypeInfo)
{
}

TypeInfo::~TypeInfo()
{
}

bool TypeInfo::IsTypeOf(StringHash type) const
{
    const TypeInfo* current = this;
    while (current)
    {
        if (current->GetType() == type)
            return true;

        current = current->GetBaseTypeInfo();
    }

    return false;
}

bool TypeInfo::IsTypeOf(const TypeInfo* typeInfo) const
{
    const TypeInfo* current = this;
    while (current)
    {
        if (current == typeInfo)
            return true;

        current = current->GetBaseTypeInfo();
    }

    return false;
}

Object::Object(Context* context) :
    context_(context)
{
    assert(context_);
}

Object::~Object()
{
    UnsubscribeFromAllEvents();
    context_->RemoveEventSender(this);
}

void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData)
{
    // Make a copy of the context pointer in case the object is destroyed during event handler invocation
    Context* context = context_;
    EventHandler* specific = 0;
    EventHandler* nonSpecific = 0;

    EventHandler* handler = eventHandlers_.First();
    while (handler)
    {
        if (handler->GetEventType() == eventType)
        {
            if (!handler->GetSender())
                nonSpecific = handler;
            else if (handler->GetSender() == sender)
            {
                specific = handler;
                break;
            }
        }
        handler = eventHandlers_.Next(handler);
    }

    // Specific event handlers have priority, so if found, invoke first
    if (specific)
    {
        context->SetEventHandler(specific);
        specific->Invoke(eventData);
        context->SetEventHandler(0);
        return;
    }

    if (nonSpecific)
    {
        context->SetEventHandler(nonSpecific);
        nonSpecific->Invoke(eventData);
        context->SetEventHandler(0);
    }
}

bool Object::IsTypeOf(StringHash type)
{
    return GetTypeInfoStatic()->IsTypeOf(type);
}

bool Object::IsTypeOf(const TypeInfo* typeInfo)
{
    return GetTypeInfoStatic()->IsTypeOf(typeInfo);
}

bool Object::IsInstanceOf(StringHash type) const
{
    return GetTypeInfo()->IsTypeOf(type);
}

bool Object::IsInstanceOf(const TypeInfo* typeInfo) const
{
    return GetTypeInfo()->IsTypeOf(typeInfo);
}

void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler)
{
    if (!handler)
        return;

    handler->SetSenderAndEventType(0, eventType);
    // Remove old event handler first
    EventHandler* previous;
    EventHandler* oldHandler = FindSpecificEventHandler(0, eventType, &previous);
    if (oldHandler)
        eventHandlers_.Erase(oldHandler, previous);

    eventHandlers_.InsertFront(handler);

    context_->AddEventReceiver(this, eventType);
}

void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler)
{
    // If a null sender was specified, the event can not be subscribed to. Delete the handler in that case
    if (!sender || !handler)
    {
        delete handler;
        return;
    }

    handler->SetSenderAndEventType(sender, eventType);
    // Remove old event handler first
    EventHandler* previous;
    EventHandler* oldHandler = FindSpecificEventHandler(sender, eventType, &previous);
    if (oldHandler)
        eventHandlers_.Erase(oldHandler, previous);

    eventHandlers_.InsertFront(handler);

    context_->AddEventReceiver(this, sender, eventType);
}

#if URHO3D_CXX11
void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData/*=0*/)
{
    SubscribeToEvent(eventType, new EventHandler11Impl(function, userData));
}

void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData/*=0*/)
{
    SubscribeToEvent(sender, eventType, new EventHandler11Impl(function, userData));
}
#endif

void Object::UnsubscribeFromEvent(StringHash eventType)
{
    for (;;)
    {
        EventHandler* previous;
        EventHandler* handler = FindEventHandler(eventType, &previous);
        if (handler)
        {
            if (handler->GetSender())
                context_->RemoveEventReceiver(this, handler->GetSender(), eventType);
            else
                context_->RemoveEventReceiver(this, eventType);
            eventHandlers_.Erase(handler, previous);
        }
        else
            break;
    }
}

void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType)
{
    if (!sender)
        return;

    EventHandler* previous;
    EventHandler* handler = FindSpecificEventHandler(sender, eventType, &previous);
    if (handler)
    {
        context_->RemoveEventReceiver(this, handler->GetSender(), eventType);
        eventHandlers_.Erase(handler, previous);
    }
}

void Object::UnsubscribeFromEvents(Object* sender)
{
    if (!sender)
        return;

    for (;;)
    {
        EventHandler* previous;
        EventHandler* handler = FindSpecificEventHandler(sender, &previous);
        if (handler)
        {
            context_->RemoveEventReceiver(this, handler->GetSender(), handler->GetEventType());
            eventHandlers_.Erase(handler, previous);
        }
        else
            break;
    }
}

void Object::UnsubscribeFromAllEvents()
{
    for (;;)
    {
        EventHandler* handler = eventHandlers_.First();
        if (handler)
        {
            if (handler->GetSender())
                context_->RemoveEventReceiver(this, handler->GetSender(), handler->GetEventType());
            else
                context_->RemoveEventReceiver(this, handler->GetEventType());
            eventHandlers_.Erase(handler);
        }
        else
            break;
    }
}

void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData)
{
    EventHandler* handler = eventHandlers_.First();
    EventHandler* previous = 0;

    while (handler)
    {
        EventHandler* next = eventHandlers_.Next(handler);

        if ((!onlyUserData || handler->GetUserData()) && !exceptions.Contains(handler->GetEventType()))
        {
            if (handler->GetSender())
                context_->RemoveEventReceiver(this, handler->GetSender(), handler->GetEventType());
            else
                context_->RemoveEventReceiver(this, handler->GetEventType());

            eventHandlers_.Erase(handler, previous);
        }
        else
            previous = handler;

        handler = next;
    }
}

void Object::SendEvent(StringHash eventType)
{
    VariantMap noEventData;

    SendEvent(eventType, noEventData);
}

void Object::SendEvent(StringHash eventType, VariantMap& eventData)
{
    if (!Thread::IsMainThread())
    {
        URHO3D_LOGERROR("Sending events is only supported from the main thread");
        return;
    }

#ifdef URHO3D_PROFILING
    EventProfiler* eventProfiler = 0;
    if (EventProfiler::IsActive())
    {
        eventProfiler = GetSubsystem<EventProfiler>();
        if (eventProfiler)
            eventProfiler->BeginBlock(eventType);
    }
#endif

    // Make a weak pointer to self to check for destruction during event handling
    WeakPtr<Object> self(this);
    Context* context = context_;
    HashSet<Object*> processed;

    context->BeginSendEvent(this);

    // Check first the specific event receivers
    const HashSet<Object*>* group = context->GetEventReceivers(this, eventType);
    if (group)
    {
        for (HashSet<Object*>::ConstIterator i = group->Begin(); i != group->End();)
        {
            HashSet<Object*>::ConstIterator current = i++;
            Object* receiver = *current;
            Object* next = 0;
            if (i != group->End())
                next = *i;

            unsigned oldSize = group->Size();
            receiver->OnEvent(this, eventType, eventData);

            // If self has been destroyed as a result of event handling, exit
            if (self.Expired())
            {
                context->EndSendEvent();
#ifdef URHO3D_PROFILING
                if (eventProfiler)
                    eventProfiler->EndBlock();
#endif
                return;
            }

            // If group has changed size during iteration (removed/added subscribers) try to recover
            /// \todo This is not entirely foolproof, as a subscriber could have been added to make up for the removed one
            if (group->Size() != oldSize)
                i = group->Find(next);

            processed.Insert(receiver);
        }
    }

    // Then the non-specific receivers
    group = context->GetEventReceivers(eventType);
    if (group)
    {
        if (processed.Empty())
        {
            for (HashSet<Object*>::ConstIterator i = group->Begin(); i != group->End();)
            {
                HashSet<Object*>::ConstIterator current = i++;
                Object* receiver = *current;
                Object* next = 0;
                if (i != group->End())
                    next = *i;

                unsigned oldSize = group->Size();
                receiver->OnEvent(this, eventType, eventData);

                if (self.Expired())
                {
                    context->EndSendEvent();
#ifdef URHO3D_PROFILING
                    if (eventProfiler)
                         eventProfiler->EndBlock();
#endif
                    return;
                }

                if (group->Size() != oldSize)
                    i = group->Find(next);
            }
        }
        else
        {
            // If there were specific receivers, check that the event is not sent doubly to them
            for (HashSet<Object*>::ConstIterator i = group->Begin(); i != group->End();)
            {
                HashSet<Object*>::ConstIterator current = i++;
                Object* receiver = *current;
                Object* next = 0;
                if (i != group->End())
                    next = *i;

                if (!processed.Contains(receiver))
                {
                    unsigned oldSize = group->Size();
                    receiver->OnEvent(this, eventType, eventData);

                    if (self.Expired())
                    {
                        context->EndSendEvent();
#ifdef URHO3D_PROFILING
                        if (eventProfiler)
                            eventProfiler->EndBlock();
#endif
                        return;
                    }

                    if (group->Size() != oldSize)
                        i = group->Find(next);
                }
            }
        }
    }

    context->EndSendEvent();

#ifdef URHO3D_PROFILING
    if (eventProfiler)
        eventProfiler->EndBlock();
#endif
}

VariantMap& Object::GetEventDataMap() const
{
    return context_->GetEventDataMap();
}

const Variant& Object::GetGlobalVar(StringHash key) const
{
    return context_->GetGlobalVar(key);
}

const VariantMap& Object::GetGlobalVars() const 
{ 
    return context_->GetGlobalVars(); 
}

void Object::SetGlobalVar(StringHash key, const Variant& value)
{
    context_->SetGlobalVar(key, value);
}

Object* Object::GetSubsystem(StringHash type) const
{
    return context_->GetSubsystem(type);
}

Object* Object::GetEventSender() const
{
    return context_->GetEventSender();
}

EventHandler* Object::GetEventHandler() const
{
    return context_->GetEventHandler();
}

bool Object::HasSubscribedToEvent(StringHash eventType) const
{
    return FindEventHandler(eventType) != 0;
}

bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const
{
    if (!sender)
        return false;
    else
        return FindSpecificEventHandler(sender, eventType) != 0;
}

const String& Object::GetCategory() const
{
    const HashMap<String, Vector<StringHash> >& objectCategories = context_->GetObjectCategories();
    for (HashMap<String, Vector<StringHash> >::ConstIterator i = objectCategories.Begin(); i != objectCategories.End(); ++i)
    {
        if (i->second_.Contains(GetType()))
            return i->first_;
    }

    return String::EMPTY;
}

EventHandler* Object::FindEventHandler(StringHash eventType, EventHandler** previous) const
{
    EventHandler* handler = eventHandlers_.First();
    if (previous)
        *previous = 0;

    while (handler)
    {
        if (handler->GetEventType() == eventType)
            return handler;
        if (previous)
            *previous = handler;
        handler = eventHandlers_.Next(handler);
    }

    return 0;
}

EventHandler* Object::FindSpecificEventHandler(Object* sender, EventHandler** previous) const
{
    EventHandler* handler = eventHandlers_.First();
    if (previous)
        *previous = 0;

    while (handler)
    {
        if (handler->GetSender() == sender)
            return handler;
        if (previous)
            *previous = handler;
        handler = eventHandlers_.Next(handler);
    }

    return 0;
}

EventHandler* Object::FindSpecificEventHandler(Object* sender, StringHash eventType, EventHandler** previous) const
{
    EventHandler* handler = eventHandlers_.First();
    if (previous)
        *previous = 0;

    while (handler)
    {
        if (handler->GetSender() == sender && handler->GetEventType() == eventType)
            return handler;
        if (previous)
            *previous = handler;
        handler = eventHandlers_.Next(handler);
    }

    return 0;
}

void Object::RemoveEventSender(Object* sender)
{
    EventHandler* handler = eventHandlers_.First();
    EventHandler* previous = 0;

    while (handler)
    {
        if (handler->GetSender() == sender)
        {
            EventHandler* next = eventHandlers_.Next(handler);
            eventHandlers_.Erase(handler, previous);
            handler = next;
        }
        else
        {
            previous = handler;
            handler = eventHandlers_.Next(handler);
        }
    }
}


Urho3D::StringHash EventNameRegistrar::RegisterEventName(const char* eventName)
{  
    StringHash id(eventName);
    GetEventNameMap()[id] = eventName;
    return id;
}

const String& EventNameRegistrar::GetEventName(StringHash eventID) 
{
    HashMap<StringHash, String>::ConstIterator it = GetEventNameMap().Find(eventID);
    return  it != GetEventNameMap().End() ? it->second_ : String::EMPTY ;
}

HashMap<StringHash, String>& EventNameRegistrar::GetEventNameMap()
{
    static HashMap<StringHash, String> eventNames_;
    return eventNames_;
}

}
