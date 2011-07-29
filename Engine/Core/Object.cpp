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
#include "Context.h"

#include "DebugNew.h"

Object::Object(Context* context) :
    context_(context)
{
}

Object::~Object()
{
    UnsubscribeFromAllEvents();
    context_->RemoveEventSender(this);
}

void Object::OnEvent(Object* sender, bool broadcast, StringHash eventType, VariantMap& eventData)
{
    // Make a weak pointer to self to check for destruction during event handling
    WeakPtr<Object> self(this);
    
    // Check first the specific event handlers, which have priority
    Map<Pair<Object*, StringHash>, SharedPtr<EventHandler> >::ConstIterator i = eventHandlers_.Find(
        MakePair(sender, eventType));
    if (i != eventHandlers_.End())
    {
        context_->SetEventHandler(i->second_);
        i->second_->Invoke(eventType, eventData);
        if (!self.Expired())
            context_->SetEventHandler(0);
        return;
    }
    
    // Then check non-specific (null sender pointer)
    i = eventHandlers_.Find(MakePair((Object*)0, eventType));
    if (i != eventHandlers_.End())
    {
        context_->SetEventHandler(i->second_);
        i->second_->Invoke(eventType, eventData);
        if (!self.Expired())
            context_->SetEventHandler(0);
    }
}

void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler)
{
    if (!handler)
        return;
    
    Pair<Object*, StringHash> combination((Object*)0, eventType);
    
    eventHandlers_[combination] = handler;
    context_->AddEventReceiver(this, eventType);
}

void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler)
{
    if (!sender || !handler)
        return;
    
    Pair<Object*, StringHash> combination(sender, eventType);
    
    eventHandlers_[combination] = handler;
    context_->AddEventReceiver(this, sender, eventType);
}

void Object::UnsubscribeFromEvent(StringHash eventType)
{
    for (Map<Pair<Object*, StringHash>, SharedPtr<EventHandler> >::Iterator i = eventHandlers_.Begin();
        i != eventHandlers_.End();)
    {
        Map<Pair<Object*, StringHash>, SharedPtr<EventHandler> >::Iterator current = i++;
        if (current->first_.second_ == eventType)
        {
            if (current->first_.first_)
                context_->RemoveEventReceiver(this, current->first_.first_, current->first_.second_);
            else
                context_->RemoveEventReceiver(this, current->first_.second_);
            eventHandlers_.Erase(current);
        }
    }
}

void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType)
{
    Pair<Object*, StringHash> combination(sender, eventType);
    
    Map<Pair<Object*, StringHash>, SharedPtr<EventHandler> >::Iterator i = eventHandlers_.Find(combination);
    if (i != eventHandlers_.End())
    {
        context_->RemoveEventReceiver(this, i->first_.first_, i->first_.second_);
        eventHandlers_.Erase(i);
    }
}

void Object::UnsubscribeFromEvents(Object* sender)
{
    if (!sender)
        return;
    
    for (Map<Pair<Object*, StringHash>, SharedPtr<EventHandler> >::Iterator i = eventHandlers_.Begin();
        i != eventHandlers_.End();)
    {
        Map<Pair<Object*, StringHash>, SharedPtr<EventHandler> >::Iterator current = i++;
        if (current->first_.first_ == sender)
        {
            context_->RemoveEventReceiver(this, current->first_.first_, current->first_.second_);
            eventHandlers_.Erase(current);
        }
    }
}

void Object::UnsubscribeFromAllEvents()
{
    for (Map<Pair<Object*, StringHash>, SharedPtr<EventHandler> >::Iterator i = eventHandlers_.Begin();
        i != eventHandlers_.End(); ++i)
    {
        if (i->first_.first_)
            context_->RemoveEventReceiver(this, i->first_.first_, i->first_.second_);
        else
            context_->RemoveEventReceiver(this, i->first_.second_);
    }
    
    eventHandlers_.Clear();
}

void Object::UnsubscribeFromAllEventsWithUserData()
{
    for (Map<Pair<Object*, StringHash>, SharedPtr<EventHandler> >::Iterator i = eventHandlers_.Begin();
        i != eventHandlers_.End(); )
    {
        if (i->second_->GetUserData())
        {
            Map<Pair<Object*, StringHash>, SharedPtr<EventHandler> >::Iterator current = i++;
            if (current->first_.first_)
                context_->RemoveEventReceiver(this, current->first_.first_, current->first_.second_);
            else
                context_->RemoveEventReceiver(this, current->first_.second_);
            eventHandlers_.Erase(current);
        }
        else
            ++i;
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
    Set<Object*> processed;
    
    context_->BeginSendEvent(this);
    
    // Check first the specific event receivers
    const PODVector<Object*>* group = context_->GetReceivers(this, eventType);
    if (group)
    {
        unsigned numReceivers = group->Size();
        for (unsigned j = 0; j < numReceivers; ++j)
        {
            Object* receiver = group->At(j);
            // There may be null pointers due to not removing vector elements during event handling, so check
            if (receiver)
            {
                processed.Insert(receiver);
                receiver->OnEvent(this, true, eventType, eventData);
                if (self.Expired())
                {
                    context_->EndSendEvent();
                    return;
                }
            }
        }
    }
    
    // Then the non-specific receivers
    group = context_->GetReceivers(eventType);
    if (group)
    {
        unsigned numReceivers = group->Size();
        if (processed.Empty())
        {
            for (unsigned k = 0; k < numReceivers; ++k)
            {
                Object* receiver = group->At(k);
                if (receiver)
                {
                    receiver->OnEvent(this, true, eventType, eventData);
                    if (self.Expired())
                    {
                        context_->EndSendEvent();
                        return;
                    }
                }
            }
        }
        else
        {
            // If there were specific receivers, check that the event is not sent doubly to them
            for (unsigned k = 0; k < numReceivers; ++k)
            {
                Object* receiver = group->At(k);
                if (receiver && processed.Find(receiver) == processed.End())
                {
                    receiver->OnEvent(this, true, eventType, eventData);
                    if (self.Expired())
                    {
                        context_->EndSendEvent();
                        return;
                    }
                }
            }
        }
    }
    
    context_->EndSendEvent();
}

void Object::SendEvent(Object* receiver, StringHash eventType)
{
    if (receiver)
    {
        VariantMap noEventData;
        
        context_->BeginSendEvent(this);
        receiver->OnEvent(this, false, eventType, noEventData);
        context_->EndSendEvent();
    }
}

void Object::SendEvent(Object* receiver, StringHash eventType, VariantMap& eventData)
{
    if (receiver)
    {
        context_->BeginSendEvent(this);
        receiver->OnEvent(this, false, eventType, eventData);
        context_->EndSendEvent();
    }
}

Object* Object::GetSubsystem(ShortStringHash type) const
{
    const Map<ShortStringHash, SharedPtr<Object> >& subsystems = context_->GetSubsystems();
    Map<ShortStringHash, SharedPtr<Object> >::ConstIterator i = subsystems.Find(type);
    if (i != subsystems.End())
        return i->second_;
    else
        return 0;
}

bool Object::HasSubscribedToEvent(StringHash eventType) const
{
    return eventHandlers_.Find(MakePair((Object*)0, eventType)) != eventHandlers_.End();
}

bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const
{
    return eventHandlers_.Find(MakePair(sender, eventType)) != eventHandlers_.End();
}

Object* Object::GetEventSender() const
{
    return context_->GetEventSender();
}

void Object::RemoveEventSender(Object* sender)
{
    for (Map<Pair<Object*, StringHash>, SharedPtr<EventHandler> >::Iterator i = eventHandlers_.Begin();
        i != eventHandlers_.End();)
    {
        Map<Pair<Object*, StringHash>, SharedPtr<EventHandler> >::Iterator current = i++;
        if (current->first_.first_ == sender)
            eventHandlers_.Erase(current);
    }
}
