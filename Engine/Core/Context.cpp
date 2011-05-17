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

#include "DebugNew.h"

static String noType;

Context::Context() :
    handler_(0)
{
}

Context::~Context()
{
    // Release the subsystems before the event receiver maps are destroyed
    for (std::map<ShortStringHash, SharedPtr<Object> >::iterator i = subsystems_.begin(); i != subsystems_.end(); ++i)
        i->second.Reset();
    subsystems_.clear();
    factories_.clear();
}

SharedPtr<Object> Context::CreateObject(ShortStringHash objectType)
{
    std::map<ShortStringHash, SharedPtr<ObjectFactory> >::const_iterator i = factories_.find(objectType);
    if (i != factories_.end())
        return i->second->CreateObject();
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
    if ((attr.type_ == VAR_NONE) || (attr.type_ == VAR_PTR))
        return;
    
    attributes_[objectType].push_back(attr);
}

void Context::RemoveAttribute(ShortStringHash objectType, const String& name)
{
    std::vector<AttributeInfo>& attributes = attributes_[objectType];
    for (std::vector<AttributeInfo>::iterator i = attributes.begin(); i != attributes.end(); ++i)
    {
        if (i->name_ == name)
        {
            attributes.erase(i);
            return;
        }
    }
}

void Context::CopyBaseAttributes(ShortStringHash baseType, ShortStringHash derivedType)
{
    attributes_[derivedType] = attributes_[baseType];
}

void Context::AddEventReceiver(Object* receiver, StringHash eventType)
{
    std::vector<Object*>& receivers = receivers_[eventType];
    for (std::vector<Object*>::const_iterator j = receivers.begin(); j != receivers.end(); ++j)
    {
        // Check if already registered
        if (*j == receiver)
            return;
    }
    
    receivers.push_back(receiver);
}

void Context::AddEventReceiver(Object* receiver, Object* sender, StringHash eventType)
{
    std::vector<Object*>& receivers = specificReceivers_[std::make_pair(sender, eventType)];
    for (std::vector<Object*>::const_iterator j = receivers.begin(); j != receivers.end(); ++j)
    {
        if (*j == receiver)
            return;
    }
    
    receivers.push_back(receiver);
}

void Context::RemoveEventSender(Object* sender)
{
    for (std::map<std::pair<Object*, StringHash>, std::vector<Object*> >::iterator i = specificReceivers_.begin();
        i != specificReceivers_.end();)
    {
        std::map<std::pair<Object*, StringHash>, std::vector<Object*> >::iterator current = i++;
        if (current->first.first == sender)
        {
            std::vector<Object*>& receivers = current->second;
            for (std::vector<Object*>::iterator j = receivers.begin(); j != receivers.end(); ++j)
            {
                if (*j)
                    (*j)->RemoveEventSender(sender);
            }
            specificReceivers_.erase(current);
        }
    }
}

void Context::RemoveEventReceiver(Object* receiver, StringHash eventType)
{
    std::vector<Object*>* group = GetReceivers(eventType);
    if (!group)
        return;
    
    for (std::vector<Object*>::iterator i = group->begin(); i != group->end(); ++i)
    {
        if (*i == receiver)
        {
            // If no event handling going on, can erase the receiver. Otherwise reset the pointer and clean up later
            if (senders_.empty())
                group->erase(i);
            else
            {
                *i = 0;
                dirtyReceivers_.insert(eventType);
            }
            return;
        }
    }
}

void Context::RemoveEventReceiver(Object* receiver, Object* sender, StringHash eventType)
{
    std::vector<Object*>* group = GetReceivers(sender, eventType);
    if (!group)
        return;
    
    for (std::vector<Object*>::iterator i = group->begin(); i != group->end(); ++i)
    {
        if (*i == receiver)
        {
            if (senders_.empty())
                group->erase(i);
            else
            {
                *i = 0;
                dirtySpecificReceivers_.insert(std::make_pair(sender, eventType));
            }
            return;
        }
    }
}

Object* Context::GetSubsystem(ShortStringHash type) const
{
    std::map<ShortStringHash, SharedPtr<Object> >::const_iterator i = subsystems_.find(type);
    if (i != subsystems_.end())
        return i->second;
    else
        return 0;
}

Object* Context::GetSender() const
{
    if (!senders_.empty())
        return senders_.back();
    else
        return 0;
}

const String& Context::GetTypeName(ShortStringHash type) const
{
    // Search factories to find the hash-to-name mapping
    std::map<ShortStringHash, SharedPtr<ObjectFactory> >::const_iterator i = factories_.find(type);
    return (i != factories_.end()) ? i->second->GetTypeName() : noType;
}
