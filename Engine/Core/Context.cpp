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

static String noType;

Context::Context() :
    handler_(0)
{
}

Context::~Context()
{
    // Release the subsystems before the event receiver maps are destroyed
    for (Map<ShortStringHash, SharedPtr<Object> >::Iterator i = subsystems_.Begin(); i != subsystems_.End(); ++i)
        i->second_.Reset();
    subsystems_.Clear();
    factories_.Clear();
}

SharedPtr<Object> Context::CreateObject(ShortStringHash objectType)
{
    Map<ShortStringHash, SharedPtr<ObjectFactory> >::ConstIterator i = factories_.Find(objectType);
    if (i != factories_.End())
        return i->second_->CreateObject();
    else
        return SharedPtr<Object>();
}

void Context::RegisterFactory(ObjectFactory* factory)
{
    if (!factory)
        return;
    
    factories_[factory->GetType()] = factory;
}

void Context::RegisterSubsystem(Object* object)
{
    if (!object)
        return;
    
    subsystems_[object->GetType()] = object;
}

void Context::RegisterAttribute(ShortStringHash objectType, const AttributeInfo& attr)
{
    // None or Pointer types can not be supported
    if (attr.type_ == VAR_NONE || attr.type_ == VAR_PTR)
        return;
    
    attributes_[objectType].Push(attr);
    
    if (attr.mode_ & AM_NET)
        networkAttributes_[objectType].Push(attr);
}

void Context::RemoveAttribute(ShortStringHash objectType, const String& name)
{
    Vector<AttributeInfo>& attributes = attributes_[objectType];
    Vector<AttributeInfo>& netAttributes = networkAttributes_[objectType];
    
    for (Vector<AttributeInfo>::Iterator i = attributes.Begin(); i != attributes.End(); ++i)
    {
        if (i->name_ == name)
        {
            attributes.Erase(i);
            break;
        }
    }
    
    for (Vector<AttributeInfo>::Iterator i = netAttributes.Begin(); i != netAttributes.End(); ++i)
    {
        if (i->name_ == name)
        {
            netAttributes.Erase(i);
            break;
        }
    }
}

void Context::CopyBaseAttributes(ShortStringHash baseType, ShortStringHash derivedType)
{
    attributes_[derivedType] = attributes_[baseType];
}

void Context::AddEventReceiver(Object* receiver, StringHash eventType)
{
    PODVector<Object*>& receivers = receivers_[eventType];
    for (PODVector<Object*>::ConstIterator j = receivers.Begin(); j != receivers.End(); ++j)
    {
        // Check if already registered
        if (*j == receiver)
            return;
    }
    
    receivers.Push(receiver);
}

void Context::AddEventReceiver(Object* receiver, Object* sender, StringHash eventType)
{
    PODVector<Object*>& receivers = specificReceivers_[MakePair(sender, eventType)];
    for (PODVector<Object*>::ConstIterator j = receivers.Begin(); j != receivers.End(); ++j)
    {
        if (*j == receiver)
            return;
    }
    
    receivers.Push(receiver);
}

void Context::RemoveEventSender(Object* sender)
{
    for (Map<Pair<Object*, StringHash>, PODVector<Object*> >::Iterator i = specificReceivers_.Begin();
        i != specificReceivers_.End();)
    {
        Map<Pair<Object*, StringHash>, PODVector<Object*> >::Iterator current = i++;
        if (current->first_.first_ == sender)
        {
            PODVector<Object*>& receivers = current->second_;
            for (PODVector<Object*>::Iterator j = receivers.Begin(); j != receivers.End(); ++j)
            {
                if (*j)
                    (*j)->RemoveEventSender(sender);
            }
            specificReceivers_.Erase(current);
        }
    }
}

void Context::RemoveEventReceiver(Object* receiver, StringHash eventType)
{
    PODVector<Object*>* group = GetReceivers(eventType);
    if (!group)
        return;
    
    for (PODVector<Object*>::Iterator i = group->Begin(); i != group->End(); ++i)
    {
        if (*i == receiver)
        {
            // If no event handling going on, can erase the receiver. Otherwise reset the pointer and clean up later
            if (senders_.Empty())
                group->Erase(i);
            else
            {
                *i = 0;
                dirtyReceivers_.Insert(eventType);
            }
            return;
        }
    }
}

void Context::RemoveEventReceiver(Object* receiver, Object* sender, StringHash eventType)
{
    PODVector<Object*>* group = GetReceivers(sender, eventType);
    if (!group)
        return;
    
    for (PODVector<Object*>::Iterator i = group->Begin(); i != group->End(); ++i)
    {
        if (*i == receiver)
        {
            if (senders_.Empty())
                group->Erase(i);
            else
            {
                *i = 0;
                dirtySpecificReceivers_.Insert(MakePair(sender, eventType));
            }
            return;
        }
    }
}

Object* Context::GetSubsystem(ShortStringHash type) const
{
    Map<ShortStringHash, SharedPtr<Object> >::ConstIterator i = subsystems_.Find(type);
    if (i != subsystems_.End())
        return i->second_;
    else
        return 0;
}

Object* Context::GetSender() const
{
    if (!senders_.Empty())
        return senders_.Back();
    else
        return 0;
}

const String& Context::GetTypeName(ShortStringHash type) const
{
    // Search factories to find the hash-to-name mapping
    Map<ShortStringHash, SharedPtr<ObjectFactory> >::ConstIterator i = factories_.Find(type);
    return i != factories_.End() ? i->second_->GetTypeName() : noType;
}
