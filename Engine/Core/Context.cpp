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

namespace Urho3D
{

void RemoveNamedAttribute(HashMap<ShortStringHash, Vector<AttributeInfo> >& attributes, ShortStringHash objectType, const char* name)
{
    HashMap<ShortStringHash, Vector<AttributeInfo> >::Iterator i = attributes.Find(objectType);
    if (i == attributes.End())
        return;
    
    Vector<AttributeInfo>& infos = i->second_;
    
    for (Vector<AttributeInfo>::Iterator j = infos.Begin(); j != infos.End(); ++j)
    {
        if (!String::Compare(j->name_, name, true))
        {
            infos.Erase(j);
            break;
        }
    }
    
    // If the vector became empty, erase the object type from the map
    if (infos.Empty())
        attributes.Erase(i);
}

Context::Context() :
    eventHandler_(0)
{
    #ifdef ANDROID
    // Always reset the random seed on Android, as the Urho3D library might not be unloaded between runs
    SetRandomSeed(1);
    #endif
}

Context::~Context()
{
    subsystems_.Clear();
    factories_.Clear();
}

SharedPtr<Object> Context::CreateObject(ShortStringHash objectType)
{
    HashMap<ShortStringHash, SharedPtr<ObjectFactory> >::ConstIterator i = factories_.Find(objectType);
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

void Context::RemoveSubsystem(ShortStringHash objectType)
{
    HashMap<ShortStringHash, SharedPtr<Object> >::Iterator i = subsystems_.Find(objectType);
    if (i != subsystems_.End())
        subsystems_.Erase(i);
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

void Context::RemoveAttribute(ShortStringHash objectType, const char* name)
{
    RemoveNamedAttribute(attributes_, objectType, name);
    RemoveNamedAttribute(networkAttributes_, objectType, name);
}

void Context::CopyBaseAttributes(ShortStringHash baseType, ShortStringHash derivedType)
{
    const Vector<AttributeInfo>* baseAttributes = GetAttributes(baseType);
    if (baseAttributes)
    {
        for (unsigned i = 0; i < baseAttributes->Size(); ++i)
        {
            const AttributeInfo& attr = baseAttributes->At(i);
            attributes_[derivedType].Push(attr);
            if (attr.mode_ & AM_NET)
                networkAttributes_[derivedType].Push(attr);
        }
    }
}

Object* Context::GetSubsystem(ShortStringHash type) const
{
    HashMap<ShortStringHash, SharedPtr<Object> >::ConstIterator i = subsystems_.Find(type);
    if (i != subsystems_.End())
        return i->second_;
    else
        return 0;
}

Object* Context::GetEventSender() const
{
    if (!eventSenders_.Empty())
        return eventSenders_.Back();
    else
        return 0;
}

const String& Context::GetTypeName(ShortStringHash type) const
{
    // Search factories to find the hash-to-name mapping
    HashMap<ShortStringHash, SharedPtr<ObjectFactory> >::ConstIterator i = factories_.Find(type);
    return i != factories_.End() ? i->second_->GetTypeName() : String::EMPTY;
}


void Context::AddEventReceiver(Object* receiver, StringHash eventType)
{
    eventReceivers_[eventType].Insert(receiver);
}

void Context::AddEventReceiver(Object* receiver, Object* sender, StringHash eventType)
{
    specificEventReceivers_[sender][eventType].Insert(receiver);
}

void Context::RemoveEventSender(Object* sender)
{
    HashMap<Object*, HashMap<StringHash, HashSet<Object*> > >::Iterator i = specificEventReceivers_.Find(sender);
    if (i != specificEventReceivers_.End())
    {
        for (HashMap<StringHash, HashSet<Object*> >::Iterator j = i->second_.Begin(); j != i->second_.End(); ++j)
        {
            for (HashSet<Object*>::Iterator k = j->second_.Begin(); k != j->second_.End(); ++k)
                (*k)->RemoveEventSender(sender);
        }
        specificEventReceivers_.Erase(i);
    }
}

void Context::RemoveEventReceiver(Object* receiver, StringHash eventType)
{
    HashSet<Object*>* group = GetEventReceivers(eventType);
    if (group)
        group->Erase(receiver);
}

void Context::RemoveEventReceiver(Object* receiver, Object* sender, StringHash eventType)
{
    HashSet<Object*>* group = GetEventReceivers(sender, eventType);
    if (group)
        group->Erase(receiver);
}

void Context::EndSendEvent()
{
    eventSenders_.Pop();
}

}
