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
#include "StringUtils.h"

#include <cstring>

#include "DebugNew.h"

static VariantMap noEventData;

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
    std::map<std::pair<Object*, StringHash>, EventHandler*>::const_iterator i = eventHandlers_.find(
        std::make_pair(sender, eventType));
    if (i != eventHandlers_.end())
    {
        context_->SetEventHandler(i->second);
        i->second->Invoke(eventType, eventData);
        if (!self.IsExpired())
            context_->SetEventHandler(0);
        return;
    }
    
    // Then check non-specific (null sender pointer)
    i = eventHandlers_.find(std::make_pair((Object*)0, eventType));
    if (i != eventHandlers_.end())
    {
        context_->SetEventHandler(i->second);
        i->second->Invoke(eventType, eventData);
        if (!self.IsExpired())
            context_->SetEventHandler(0);
    }
}

SharedPtr<Object> Object::CreateObject(ShortStringHash type)
{
    const std::map<ShortStringHash, SharedPtr<ObjectFactory> >& factories = context_->GetObjectFactories();
    std::map<ShortStringHash, SharedPtr<ObjectFactory> >::const_iterator i = factories.find(type);
    if (i != factories.end())
        return i->second->CreateObject();
    else
        return SharedPtr<Object>();
}

void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler)
{
    if (!handler)
        return;
    
    std::pair<Object*, StringHash> combination((Object*)0, eventType);
    
    // If there already is a handler, delete it
    std::map<std::pair<Object*, StringHash>, EventHandler*>::iterator i = eventHandlers_.find(combination);
    if (i != eventHandlers_.end())
        delete i->second;
    
    eventHandlers_[combination] = handler;
    context_->AddEventReceiver(this, eventType);
}

void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler)
{
    if ((!sender) || (!handler))
        return; 
    
    std::pair<Object*, StringHash> combination(sender, eventType);
    
    // If there already is a handler, delete it
    std::map<std::pair<Object*, StringHash>, EventHandler*>::iterator i = eventHandlers_.find(combination);
    if (i != eventHandlers_.end())
        delete i->second;
    
    eventHandlers_[combination] = handler;
    context_->AddEventReceiver(this, sender, eventType);
}

void Object::UnsubscribeFromEvent(StringHash eventType)
{
    for (std::map<std::pair<Object*, StringHash>, EventHandler*>::iterator i = eventHandlers_.begin();
        i != eventHandlers_.end();)
    {
        std::map<std::pair<Object*, StringHash>, EventHandler*>::iterator current = i++;
        if (current->first.second == eventType)
        {
            if (current->first.first)
                context_->RemoveEventReceiver(this, current->first.first, current->first.second);
            else
                context_->RemoveEventReceiver(this, current->first.second);
            delete current->second;
            eventHandlers_.erase(current);
        }
    }
}

void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType)
{
    std::pair<Object*, StringHash> combination(sender, eventType);
    
    std::map<std::pair<Object*, StringHash>, EventHandler*>::iterator i = eventHandlers_.find(combination);
    if (i != eventHandlers_.end())
    {
        context_->RemoveEventReceiver(this, i->first.first, i->first.second);
        delete i->second;
        eventHandlers_.erase(i);
    }
}

void Object::UnsubscribeFromEvents(Object* sender)
{
    if (!sender)
        return;
    
    for (std::map<std::pair<Object*, StringHash>, EventHandler*>::iterator i = eventHandlers_.begin();
        i != eventHandlers_.end();)
    {
        std::map<std::pair<Object*, StringHash>, EventHandler*>::iterator current = i++;
        if (current->first.first == sender)
        {
            context_->RemoveEventReceiver(this, current->first.first, current->first.second);
            delete current->second;
            eventHandlers_.erase(current);
        }
    }
}

void Object::UnsubscribeFromAllEvents()
{
    for (std::map<std::pair<Object*, StringHash>, EventHandler*>::iterator i = eventHandlers_.begin();
        i != eventHandlers_.end(); ++i)
    {
        if (i->first.first)
            context_->RemoveEventReceiver(this, i->first.first, i->first.second);
        else
            context_->RemoveEventReceiver(this, i->first.second);
        delete i->second;
    }
    
    eventHandlers_.clear();
}

void Object::UnsubscribeFromAllEventsWithUserData()
{
    for (std::map<std::pair<Object*, StringHash>, EventHandler*>::iterator i = eventHandlers_.begin();
        i != eventHandlers_.end(); )
    {
        if (i->second->GetUserData())
        {
            std::map<std::pair<Object*, StringHash>, EventHandler*>::iterator current = i++;
            if (current->first.first)
                context_->RemoveEventReceiver(this, current->first.first, current->first.second);
            else
                context_->RemoveEventReceiver(this, current->first.second);
            delete current->second;
            eventHandlers_.erase(current);
        }
        else
            ++i;
    }
}

void Object::SendEvent(StringHash eventType)
{
    SendEvent(eventType, noEventData);
}

void Object::SendEvent(StringHash eventType, VariantMap& eventData)
{
    std::set<Object*> processed;
    
    context_->BeginSendEvent(this);
    
    // Check first the specific event receivers
    const std::vector<Object*>* group = context_->GetReceivers(this, eventType);
    if (group)
    {
        unsigned numReceivers = group->size();
        for (unsigned j = 0; j < numReceivers; ++j)
        {
            Object* receiver = group->at(j);
            // There may be null pointers due to not removing vector elements during event handling, so check
            if (receiver)
            {
                processed.insert(receiver);
                receiver->OnEvent(this, true, eventType, eventData);
            }
        }
    }
    
    // Then the non-specific receivers
    group = context_->GetReceivers(eventType);
    if (group)
    {
        unsigned numReceivers = group->size();
        if (processed.empty())
        {
            for (unsigned k = 0; k < numReceivers; ++k)
            {
                Object* receiver = group->at(k);
                if (receiver)
                    receiver->OnEvent(this, true, eventType, eventData);
            }
        }
        else
        {
            // If there were specific receivers, check that the event is not sent doubly to them
            for (unsigned k = 0; k < numReceivers; ++k)
            {
                Object* receiver = group->at(k);
                if ((receiver) && (processed.find(receiver) == processed.end()))
                    receiver->OnEvent(this, true, eventType, eventData);
            }
        }
    }
    
    context_->EndSendEvent();
}

void Object::SendEvent(Object* receiver, StringHash eventType)
{
    if (receiver)
    {
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
    const std::map<ShortStringHash, SharedPtr<Object> >& subsystems = context_->GetSubsystems();
    std::map<ShortStringHash, SharedPtr<Object> >::const_iterator i = subsystems.find(type);
    if (i != subsystems.end())
        return i->second;
    else
        return 0;
}

bool Object::HasSubscribed(StringHash eventType) const
{
    return eventHandlers_.find(std::make_pair((Object*)0, eventType)) != eventHandlers_.end();
}

bool Object::HasSubscribed(Object* sender, StringHash eventType) const
{
    return eventHandlers_.find(std::make_pair(sender, eventType)) != eventHandlers_.end();
}

Object* Object::GetSender() const
{
    return context_->GetSender();
}

void Object::RemoveEventSender(Object* sender)
{
    for (std::map<std::pair<Object*, StringHash>, EventHandler*>::iterator i = eventHandlers_.begin();
        i != eventHandlers_.end();)
    {
        std::map<std::pair<Object*, StringHash>, EventHandler*>::iterator current = i++;
        if (current->first.first == sender)
        {
            delete current->second;
            eventHandlers_.erase(current);
        }
    }
}
