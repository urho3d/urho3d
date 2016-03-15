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

#include "../DebugNew.h"

namespace Urho3D
{

void RemoveNamedAttribute(HashMap<StringHash, Vector<AttributeInfo> >& attributes, StringHash objectType, const char* name)
{
    HashMap<StringHash, Vector<AttributeInfo> >::Iterator i = attributes.Find(objectType);
    if (i == attributes.End())
        return;

    Vector<AttributeInfo>& infos = i->second_;

    for (Vector<AttributeInfo>::Iterator j = infos.Begin(); j != infos.End(); ++j)
    {
        if (!j->name_.Compare(name, true))
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

    // Set the main thread ID (assuming the Context is created in it)
    Thread::SetMainThread();
}

Context::~Context()
{
    // Remove subsystems that use SDL in reverse order of construction, so that Graphics can shut down SDL last
    /// \todo Context should not need to know about subsystems
    RemoveSubsystem("Audio");
    RemoveSubsystem("UI");
    RemoveSubsystem("Input");
    RemoveSubsystem("Renderer");
    RemoveSubsystem("Graphics");

    subsystems_.Clear();
    factories_.Clear();

    // Delete allocated event data maps
    for (PODVector<VariantMap*>::Iterator i = eventDataMaps_.Begin(); i != eventDataMaps_.End(); ++i)
        delete *i;
    eventDataMaps_.Clear();
}

SharedPtr<Object> Context::CreateObject(StringHash objectType)
{
    HashMap<StringHash, SharedPtr<ObjectFactory> >::ConstIterator i = factories_.Find(objectType);
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

void Context::RegisterFactory(ObjectFactory* factory, const char* category)
{
    if (!factory)
        return;

    RegisterFactory(factory);
    if (String::CStringLength(category))
        objectCategories_[category].Push(factory->GetType());
}

void Context::RegisterSubsystem(Object* object)
{
    if (!object)
        return;

    subsystems_[object->GetType()] = object;
}

void Context::RemoveSubsystem(StringHash objectType)
{
    HashMap<StringHash, SharedPtr<Object> >::Iterator i = subsystems_.Find(objectType);
    if (i != subsystems_.End())
        subsystems_.Erase(i);
}

void Context::RegisterAttribute(StringHash objectType, const AttributeInfo& attr)
{
    // None or pointer types can not be supported
    if (attr.type_ == VAR_NONE || attr.type_ == VAR_VOIDPTR || attr.type_ == VAR_PTR)
    {
        URHO3D_LOGWARNING("Attempt to register unsupported attribute type " + Variant::GetTypeName(attr.type_) + " to class " +
            GetTypeName(objectType));
        return;
    }

    attributes_[objectType].Push(attr);

    if (attr.mode_ & AM_NET)
        networkAttributes_[objectType].Push(attr);
}

void Context::RemoveAttribute(StringHash objectType, const char* name)
{
    RemoveNamedAttribute(attributes_, objectType, name);
    RemoveNamedAttribute(networkAttributes_, objectType, name);
}

void Context::UpdateAttributeDefaultValue(StringHash objectType, const char* name, const Variant& defaultValue)
{
    AttributeInfo* info = GetAttribute(objectType, name);
    if (info)
        info->defaultValue_ = defaultValue;
}

VariantMap& Context::GetEventDataMap()
{
    unsigned nestingLevel = eventSenders_.Size();
    while (eventDataMaps_.Size() < nestingLevel + 1)
        eventDataMaps_.Push(new VariantMap());

    VariantMap& ret = *eventDataMaps_[nestingLevel];
    ret.Clear();
    return ret;
}


void Context::CopyBaseAttributes(StringHash baseType, StringHash derivedType)
{
    // Prevent endless loop if mistakenly copying attributes from same class as derived
    if (baseType == derivedType)
    {
        URHO3D_LOGWARNING("Attempt to copy base attributes to itself for class " + GetTypeName(baseType));
        return;
    }

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

Object* Context::GetSubsystem(StringHash type) const
{
    HashMap<StringHash, SharedPtr<Object> >::ConstIterator i = subsystems_.Find(type);
    if (i != subsystems_.End())
        return i->second_;
    else
        return 0;
}

const Variant& Context::GetGlobalVar(StringHash key) const
{
    VariantMap::ConstIterator i = globalVars_.Find(key);
    return i != globalVars_.End() ? i->second_ : Variant::EMPTY;
}

void Context::SetGlobalVar(StringHash key, const Variant& value)
{
    globalVars_[key] = value;
}

Object* Context::GetEventSender() const
{
    if (!eventSenders_.Empty())
        return eventSenders_.Back();
    else
        return 0;
}

const String& Context::GetTypeName(StringHash objectType) const
{
    // Search factories to find the hash-to-name mapping
    HashMap<StringHash, SharedPtr<ObjectFactory> >::ConstIterator i = factories_.Find(objectType);
    return i != factories_.End() ? i->second_->GetTypeName() : String::EMPTY;
}

AttributeInfo* Context::GetAttribute(StringHash objectType, const char* name)
{
    HashMap<StringHash, Vector<AttributeInfo> >::Iterator i = attributes_.Find(objectType);
    if (i == attributes_.End())
        return 0;

    Vector<AttributeInfo>& infos = i->second_;

    for (Vector<AttributeInfo>::Iterator j = infos.Begin(); j != infos.End(); ++j)
    {
        if (!j->name_.Compare(name, true))
            return &(*j);
    }

    return 0;
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

}
