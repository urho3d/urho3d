//
// Urho3D Engine
// Copyright (c) 2008-2012 Lasse Öörni
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
#include "Context.h"

#include "DebugNew.h"

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

void Object::OnEvent(Object* sender, bool broadcast, StringHash eventType, VariantMap& eventData)
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
    if (!sender || !handler)
        return;
    
    handler->SetSenderAndEventType(sender, eventType);
    // Remove old event handler first
    EventHandler* previous;
    EventHandler* oldHandler = FindSpecificEventHandler(sender, eventType, &previous);
    if (oldHandler)
        eventHandlers_.Erase(oldHandler, previous);
    
    eventHandlers_.InsertFront(handler);
    
    context_->AddEventReceiver(this, sender, eventType);
}

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

void Object::UnsubscribeFromAllEventsWithUserData()
{
    EventHandler* handler = eventHandlers_.First();
    EventHandler* previous = 0;
    
    while (handler)
    {
        if (handler->GetUserData())
        {
            if (handler->GetSender())
                context_->RemoveEventReceiver(this, handler->GetSender(), handler->GetEventType());
            else
                context_->RemoveEventReceiver(this, handler->GetEventType());
            
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

void Object::SendEvent(StringHash eventType)
{
    VariantMap noEventData;
    
    SendEvent(eventType, noEventData);
}

void Object::SendEvent(StringHash eventType, VariantMap& eventData)
{
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
            receiver->OnEvent(this, true, eventType, eventData);
            
            // If self has been destroyed as a result of event handling, exit
            if (self.Expired())
            {
                context->EndSendEvent();
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
                receiver->OnEvent(this, true, eventType, eventData);
                
                if (self.Expired())
                {
                    context->EndSendEvent();
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
                    receiver->OnEvent(this, true, eventType, eventData);
                    
                    if (self.Expired())
                    {
                        context->EndSendEvent();
                        return;
                    }
                    
                    if (group->Size() != oldSize)
                        i = group->Find(next);
                }
            }
        }
    }
    
    context->EndSendEvent();
}

void Object::SendEvent(Object* receiver, StringHash eventType)
{
    if (receiver)
    {
        VariantMap noEventData;
        Context* context = context_;
        
        context->BeginSendEvent(this);
        receiver->OnEvent(this, false, eventType, noEventData);
        context->EndSendEvent();
    }
}

void Object::SendEvent(Object* receiver, StringHash eventType, VariantMap& eventData)
{
    if (receiver)
    {
        Context* context = context_;
        
        context->BeginSendEvent(this);
        receiver->OnEvent(this, false, eventType, eventData);
        context->EndSendEvent();
    }
}

Object* Object::GetSubsystem(ShortStringHash type) const
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
            context_->RemoveEventReceiver(this, handler->GetSender(), handler->GetEventType());
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
