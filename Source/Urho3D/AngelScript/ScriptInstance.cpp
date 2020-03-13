//
// Copyright (c) 2008-2020 the Urho3D project.
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

#include "../AngelScript/Script.h"
#include "../AngelScript/ScriptFile.h"
#include "../AngelScript/ScriptInstance.h"
#include "../AngelScript/Addons.h"
#include "../AngelScript/APITemplates.h"
#include "../Core/Context.h"
#include "../Core/Profiler.h"
#include "../IO/Log.h"
#include "../IO/MemoryBuffer.h"
#if defined(URHO3D_PHYSICS) || defined(URHO3D_URHO2D)
#include "../Physics/PhysicsEvents.h"
#endif
#include "../Resource/ResourceCache.h"
#include "../Resource/ResourceEvents.h"
#include "../Scene/Scene.h"
#include "../Scene/SceneEvents.h"

#include <AngelScript/angelscript.h>

#include "../DebugNew.h"

namespace Urho3D
{

static const char* methodDeclarations[] = {
    "void Start()",
    "void Stop()",
    "void DelayedStart()",
    "void Update(float)",
    "void PostUpdate(float)",
    "void FixedUpdate(float)",
    "void FixedPostUpdate(float)",
    "void Load(Deserializer&)",
    "void Save(Serializer&)",
    "void ReadNetworkUpdate(Deserializer&)",
    "void WriteNetworkUpdate(Serializer&)",
    "void ApplyAttributes()",
    "void TransformChanged()"
};

ScriptInstance::ScriptInstance(Context* context) :
    Component(context)
{
    ClearScriptAttributes();
}

ScriptInstance::~ScriptInstance()
{
    ReleaseObject();
}

void ScriptInstance::RegisterObject(Context* context)
{
    context->RegisterFactory<ScriptInstance>(LOGIC_CATEGORY);

    URHO3D_ACCESSOR_ATTRIBUTE("Is Enabled", IsEnabled, SetEnabled, bool, true, AM_DEFAULT);
    URHO3D_MIXED_ACCESSOR_ATTRIBUTE("Delayed Method Calls", GetDelayedCallsAttr, SetDelayedCallsAttr, PODVector<unsigned char>,
        Variant::emptyBuffer, AM_FILE | AM_NOEDIT);
    URHO3D_MIXED_ACCESSOR_ATTRIBUTE("Script File", GetScriptFileAttr, SetScriptFileAttr, ResourceRef,
        ResourceRef(ScriptFile::GetTypeStatic()), AM_DEFAULT);
    URHO3D_ACCESSOR_ATTRIBUTE("Class Name", GetClassName, SetClassName, String, String::EMPTY, AM_DEFAULT);
    URHO3D_MIXED_ACCESSOR_ATTRIBUTE("Script Data", GetScriptDataAttr, SetScriptDataAttr, PODVector<unsigned char>, Variant::emptyBuffer,
        AM_FILE | AM_NOEDIT);
    URHO3D_MIXED_ACCESSOR_ATTRIBUTE("Script Network Data", GetScriptNetworkDataAttr, SetScriptNetworkDataAttr, PODVector<unsigned char>,
        Variant::emptyBuffer, AM_NET | AM_NOEDIT);
}

void ScriptInstance::OnSetAttribute(const AttributeInfo& attr, const Variant& src)
{
    // Update stored script attributes if being manipulated while the actual object doesn't exist
    if (!scriptObject_ && storedAttributes_.Size())
    {
        HashMap<String, Variant>::Iterator i = storedAttributes_.Find(attr.name_);
        if (i != storedAttributes_.End())
            i->second_ = src;
    }

    if (attr.mode_ & (AM_NODEID | AM_COMPONENTID))
    {
        // The component / node to which the ID refers to may not be in the scene yet, and furthermore the ID must go through the
        // SceneResolver first. Delay searching for the object to ApplyAttributes
        auto* attrPtr = const_cast<AttributeInfo*>(&attr);
        idAttributes_[attrPtr] = src.GetUInt();
    }
    else if (attr.type_ == VAR_RESOURCEREF && attr.ptr_)
    {
        Resource*& resourcePtr = *(reinterpret_cast<Resource**>(attr.ptr_));
        // Decrease reference count of the old object if any, then increment the new
        if (resourcePtr)
            resourcePtr->ReleaseRef();
        const ResourceRef& ref = src.GetResourceRef();
        resourcePtr = GetSubsystem<ResourceCache>()->GetResource(ref.type_, ref.name_);
        if (resourcePtr)
            resourcePtr->AddRef();
    }
    else if (attr.type_ == VAR_VARIANTVECTOR && attr.ptr_)
    {
        auto* arr = reinterpret_cast<CScriptArray*>(attr.ptr_);
        if (arr)
        {
            const Vector<Variant>& vector = src.GetVariantVector();
            unsigned size = vector.Size();
            arr->Resize(size);
            for (unsigned i = 0; i < size; i++)
                *(static_cast<Variant*>(arr->At(i))) = vector[i];
        }
    }
    else if (attr.type_ == VAR_STRINGVECTOR && attr.ptr_)
    {
        auto* arr = reinterpret_cast<CScriptArray*>(attr.ptr_);
        if (arr)
        {
            const Vector<String>& vector = src.GetStringVector();
            unsigned size = vector.Size();
            arr->Resize(size);
            for (unsigned i = 0; i < size; i++)
                *(static_cast<String*>(arr->At(i))) = vector[i];
        }
    }
    else
        Serializable::OnSetAttribute(attr, src);
}

void ScriptInstance::OnGetAttribute(const AttributeInfo& attr, Variant& dest) const
{
    auto* attrPtr = const_cast<AttributeInfo*>(&attr);

    // Get ID's for node / component handle attributes
    if (attr.mode_ & (AM_NODEID | AM_COMPONENTID))
    {
        // If a cached ID value has been stored, return it instead of querying from the actual object
        // (the object handle is likely null at that point)
        HashMap<AttributeInfo*, unsigned>::ConstIterator i = idAttributes_.Find(attrPtr);
        if (i != idAttributes_.End())
            dest = i->second_;
        else if (attr.mode_ & AM_NODEID)
        {
            Node* node = *(reinterpret_cast<Node**>(attr.ptr_));
            unsigned nodeID = node ? node->GetID() : 0;
            dest = nodeID;
        }
        else
        {
            Component* component = *(reinterpret_cast<Component**>(attr.ptr_));
            unsigned componentID = component ? component->GetID() : 0;
            dest = componentID;
        }
    }
    else if (attr.type_ == VAR_RESOURCEREF && attr.ptr_)
    {
        Resource* resource = *(reinterpret_cast<Resource**>(attr.ptr_));
        // If resource is non-null get its type and name hash. Otherwise get type from the default value
        dest = GetResourceRef(resource, attr.defaultValue_.GetResourceRef().type_);
    }
    else if (attr.type_ == VAR_VARIANTVECTOR && attr.ptr_)
    {
        auto* arr = reinterpret_cast<CScriptArray*>(attr.ptr_);
        if (arr)
            dest = ArrayToVector<Variant>(arr);
    }
    else if (attr.type_ == VAR_STRINGVECTOR && attr.ptr_)
    {
        auto* arr = reinterpret_cast<CScriptArray*>(attr.ptr_);
        if (arr)
            dest = ArrayToVector<String>(arr);
    } else
        Serializable::OnGetAttribute(attr, dest);
}

void ScriptInstance::ApplyAttributes()
{
    // Apply node / component ID attributes now (find objects from the scene and assign to the object handles)
    for (HashMap<AttributeInfo*, unsigned>::Iterator i = idAttributes_.Begin(); i != idAttributes_.End(); ++i)
    {
        AttributeInfo& attr = *i->first_;
        if (attr.mode_ & AM_NODEID)
        {
            Node*& nodePtr = *(reinterpret_cast<Node**>(attr.ptr_));
            // Decrease reference count of the old object if any, then increment the new
            if (nodePtr)
                nodePtr->ReleaseRef();
            nodePtr = GetScene()->GetNode(i->second_);
            if (nodePtr)
                nodePtr->AddRef();
        }
        else if (attr.mode_ & AM_COMPONENTID)
        {
            Component*& componentPtr = *(reinterpret_cast<Component**>(attr.ptr_));
            if (componentPtr)
                componentPtr->ReleaseRef();
            componentPtr = GetScene()->GetComponent(i->second_);
            if (componentPtr)
                componentPtr->AddRef();
        }
    }

    idAttributes_.Clear();

    if (scriptObject_ && methods_[METHOD_APPLYATTRIBUTES])
        scriptFile_->Execute(scriptObject_, methods_[METHOD_APPLYATTRIBUTES]);
}

void ScriptInstance::OnSetEnabled()
{
    UpdateEventSubscription();
}

bool ScriptInstance::CreateObject(ScriptFile* scriptFile, const String& className)
{
    className_ = String::EMPTY; // Do not create object during SetScriptFile()
    SetScriptFile(scriptFile);
    SetClassName(className);
    return scriptObject_ != nullptr;
}

void ScriptInstance::SetScriptFile(ScriptFile* scriptFile)
{
    if (scriptFile == scriptFile_ && scriptObject_)
        return;

    ReleaseObject();

    // Unsubscribe from the reload event of previous script file (if any), then subscribe to the new
    if (scriptFile_)
    {
        UnsubscribeFromEvent(scriptFile_, E_RELOADSTARTED);
        UnsubscribeFromEvent(scriptFile_, E_RELOADFINISHED);
    }
    if (scriptFile)
    {
        SubscribeToEvent(scriptFile, E_RELOADSTARTED, URHO3D_HANDLER(ScriptInstance, HandleScriptFileReload));
        SubscribeToEvent(scriptFile, E_RELOADFINISHED, URHO3D_HANDLER(ScriptInstance, HandleScriptFileReloadFinished));
    }

    scriptFile_ = scriptFile;

    CreateObject();
    MarkNetworkUpdate();
}

void ScriptInstance::SetClassName(const String& className)
{
    if (className == className_ && scriptObject_)
        return;

    ReleaseObject();

    className_ = className;
    CreateObject();
    MarkNetworkUpdate();
}

bool ScriptInstance::Execute(const String& declaration, const VariantVector& parameters)
{
    if (!scriptObject_)
        return false;

    asIScriptFunction* method = scriptFile_->GetMethod(scriptObject_, declaration);
    if (!method)
    {
        URHO3D_LOGERROR("Method " + declaration + " not found in class " + className_);
        return false;
    }

    return scriptFile_->Execute(scriptObject_, method, parameters);
}

bool ScriptInstance::Execute(asIScriptFunction* method, const VariantVector& parameters)
{
    if (!method || !scriptObject_)
        return false;

    return scriptFile_->Execute(scriptObject_, method, parameters);
}

void ScriptInstance::DelayedExecute(float delay, bool repeat, const String& declaration, const VariantVector& parameters)
{
    if (!scriptObject_)
        return;

    DelayedCall call;
    call.period_ = call.delay_ = Max(delay, 0.0f);
    call.repeat_ = repeat;
    call.declaration_ = declaration;
    call.parameters_ = parameters;
    delayedCalls_.Push(call);

    // Make sure we are registered to the scene update event, because delayed calls are executed there
    if (!subscribed_)
        UpdateEventSubscription();
}

void ScriptInstance::ClearDelayedExecute(const String& declaration)
{
    if (declaration.Empty())
        delayedCalls_.Clear();
    else
    {
        for (Vector<DelayedCall>::Iterator i = delayedCalls_.Begin(); i != delayedCalls_.End();)
        {
            if (declaration == i->declaration_)
                i = delayedCalls_.Erase(i);
            else
                ++i;
        }
    }
}

void ScriptInstance::AddEventHandler(StringHash eventType, const String& handlerName)
{
    if (!scriptObject_)
        return;

    String declaration = "void " + handlerName + "(StringHash, VariantMap&)";
    asIScriptFunction* method = scriptFile_->GetMethod(scriptObject_, declaration);
    if (!method)
    {
        // Retry with parameterless signature
        method = scriptFile_->GetMethod(scriptObject_, handlerName);
        if (!method)
        {
            URHO3D_LOGERROR("Event handler method " + handlerName + " not found in " + scriptFile_->GetName());
            return;
        }
    }

    SubscribeToEvent(eventType, URHO3D_HANDLER_USERDATA(ScriptInstance, HandleScriptEvent, (void*)method));
}

void ScriptInstance::AddEventHandler(Object* sender, StringHash eventType, const String& handlerName)
{
    if (!scriptObject_)
        return;

    if (!sender)
    {
        URHO3D_LOGERROR("Null event sender for event " + String(eventType) + ", handler " + handlerName);
        return;
    }

    String declaration = "void " + handlerName + "(StringHash, VariantMap&)";
    asIScriptFunction* method = scriptFile_->GetMethod(scriptObject_, declaration);
    if (!method)
    {
        // Retry with parameterless signature
        method = scriptFile_->GetMethod(scriptObject_, handlerName);
        if (!method)
        {
            URHO3D_LOGERROR("Event handler method " + handlerName + " not found in " + scriptFile_->GetName());
            return;
        }
    }

    SubscribeToEvent(sender, eventType, URHO3D_HANDLER_USERDATA(ScriptInstance, HandleScriptEvent, (void*)method));
}

void ScriptInstance::RemoveEventHandler(StringHash eventType)
{
    UnsubscribeFromEvent(eventType);
}

void ScriptInstance::RemoveEventHandler(Object* sender, StringHash eventType)
{
    UnsubscribeFromEvent(sender, eventType);
}

void ScriptInstance::RemoveEventHandlers(Object* sender)
{
    UnsubscribeFromEvents(sender);
}

void ScriptInstance::RemoveEventHandlers()
{
    UnsubscribeFromAllEventsExcept(PODVector<StringHash>(), true);
}

void ScriptInstance::RemoveEventHandlersExcept(const PODVector<StringHash>& exceptions)
{
    UnsubscribeFromAllEventsExcept(exceptions, true);
}

bool ScriptInstance::HasEventHandler(StringHash eventType) const
{
    return HasSubscribedToEvent(eventType);
}

bool ScriptInstance::HasEventHandler(Object* sender, StringHash eventType) const
{
    return HasSubscribedToEvent(sender, eventType);
}

bool ScriptInstance::IsA(const String& className) const
{
    // Early out for the easiest case where that's what we are
    if (className_ == className)
        return true;
    if (scriptObject_)
    {
        asITypeInfo* myType = scriptObject_->GetObjectType();
        asITypeInfo* searchType = myType->GetModule()->GetTypeInfoByName(className.CString());
        return searchType && (searchType->GetTypeId() & asTYPEID_MASK_OBJECT) != 0 &&
            (myType->DerivesFrom(searchType) || myType->Implements(searchType));
    }
    return false;
}

bool ScriptInstance::HasMethod(const String& declaration) const
{
    if (!scriptFile_ || !scriptObject_)
        return false;
    else
        return scriptFile_->GetMethod(scriptObject_, declaration) != nullptr;
}

void ScriptInstance::SetScriptFileAttr(const ResourceRef& value)
{
    auto* cache = GetSubsystem<ResourceCache>();
    SetScriptFile(cache->GetResource<ScriptFile>(value.name_));
}

void ScriptInstance::SetDelayedCallsAttr(const PODVector<unsigned char>& value)
{
    MemoryBuffer buf(value);
    delayedCalls_.Resize(buf.ReadVLE());
    for (Vector<DelayedCall>::Iterator i = delayedCalls_.Begin(); i != delayedCalls_.End(); ++i)
    {
        i->period_ = buf.ReadFloat();
        i->delay_ = buf.ReadFloat();
        i->repeat_ = buf.ReadBool();
        i->declaration_ = buf.ReadString();
        i->parameters_ = buf.ReadVariantVector();
    }

    if (scriptObject_ && delayedCalls_.Size() && !subscribed_)
        UpdateEventSubscription();
}

void ScriptInstance::SetScriptDataAttr(const PODVector<unsigned char>& data)
{
    if (scriptObject_ && methods_[METHOD_LOAD])
    {
        MemoryBuffer buf(data);
        VariantVector parameters;
        parameters.Push(Variant((void*)static_cast<Deserializer*>(&buf)));
        scriptFile_->Execute(scriptObject_, methods_[METHOD_LOAD], parameters);
    }
}

void ScriptInstance::SetScriptNetworkDataAttr(const PODVector<unsigned char>& data)
{
    if (scriptObject_ && methods_[METHOD_READNETWORKUPDATE])
    {
        MemoryBuffer buf(data);
        VariantVector parameters;
        parameters.Push(Variant((void*)static_cast<Deserializer*>(&buf)));
        scriptFile_->Execute(scriptObject_, methods_[METHOD_READNETWORKUPDATE], parameters);
    }
}

ResourceRef ScriptInstance::GetScriptFileAttr() const
{
    return GetResourceRef(scriptFile_, ScriptFile::GetTypeStatic());
}

PODVector<unsigned char> ScriptInstance::GetDelayedCallsAttr() const
{
    VectorBuffer buf;
    buf.WriteVLE(delayedCalls_.Size());
    for (Vector<DelayedCall>::ConstIterator i = delayedCalls_.Begin(); i != delayedCalls_.End(); ++i)
    {
        buf.WriteFloat(i->period_);
        buf.WriteFloat(i->delay_);
        buf.WriteBool(i->repeat_);
        buf.WriteString(i->declaration_);
        buf.WriteVariantVector(i->parameters_);
    }
    return buf.GetBuffer();
}

PODVector<unsigned char> ScriptInstance::GetScriptDataAttr() const
{
    if (!scriptObject_ || !methods_[METHOD_SAVE])
        return PODVector<unsigned char>();
    else
    {
        VectorBuffer buf;
        VariantVector parameters;
        parameters.Push(Variant((void*)static_cast<Serializer*>(&buf)));
        scriptFile_->Execute(scriptObject_, methods_[METHOD_SAVE], parameters);
        return buf.GetBuffer();
    }
}

PODVector<unsigned char> ScriptInstance::GetScriptNetworkDataAttr() const
{
    if (!scriptObject_ || !methods_[METHOD_WRITENETWORKUPDATE])
        return PODVector<unsigned char>();
    else
    {
        VectorBuffer buf;
        VariantVector parameters;
        parameters.Push(Variant((void*)static_cast<Serializer*>(&buf)));
        scriptFile_->Execute(scriptObject_, methods_[METHOD_WRITENETWORKUPDATE], parameters);
        return buf.GetBuffer();
    }
}

void ScriptInstance::OnSceneSet(Scene* scene)
{
    if (scene)
        UpdateEventSubscription();
    else
    {
        UnsubscribeFromEvent(E_SCENEUPDATE);
        UnsubscribeFromEvent(E_SCENEPOSTUPDATE);
#if defined(URHO3D_PHYSICS) || defined(URHO3D_URHO2D)
        UnsubscribeFromEvent(E_PHYSICSPRESTEP);
        UnsubscribeFromEvent(E_PHYSICSPOSTSTEP);
#endif
        subscribed_ = false;
        subscribedPostFixed_ = false;
    }
}

void ScriptInstance::OnMarkedDirty(Node* node)
{
    // Script functions are not safe from worker threads
    Scene* scene = GetScene();
    if (scene && scene->IsThreadedUpdate())
    {
        scene->DelayedMarkedDirty(this);
        return;
    }

    if (scriptObject_ && methods_[METHOD_TRANSFORMCHANGED])
        scriptFile_->Execute(scriptObject_, methods_[METHOD_TRANSFORMCHANGED]);
}

void ScriptInstance::CreateObject()
{
    if (!scriptFile_ || className_.Empty())
        return;

    URHO3D_PROFILE(CreateScriptObject);

    scriptObject_ = scriptFile_->CreateObject(className_);
    if (scriptObject_)
    {
        // Map script object to script instance with userdata
        scriptObject_->SetUserData(this);

        GetScriptMethods();
        GetScriptAttributes();
        UpdateEventSubscription();

        if (methods_[METHOD_START])
            scriptFile_->Execute(scriptObject_, methods_[METHOD_START]);
    }
    else
        URHO3D_LOGERROR("Failed to create object of class " + className_ + " from " + scriptFile_->GetName());
}

void ScriptInstance::ReleaseObject()
{
    if (scriptObject_)
    {
        if (methods_[METHOD_STOP])
            scriptFile_->Execute(scriptObject_, methods_[METHOD_STOP]);

        PODVector<StringHash> exceptions;
        exceptions.Push(E_RELOADSTARTED);
        exceptions.Push(E_RELOADFINISHED);
        UnsubscribeFromAllEventsExcept(exceptions, false);
        if (node_)
            node_->RemoveListener(this);
        subscribed_ = false;
        subscribedPostFixed_ = false;

        ClearScriptMethods();
        ClearScriptAttributes();

        scriptObject_->SetUserData(nullptr);
        scriptObject_->Release();
        scriptObject_ = nullptr;
    }
}

void ScriptInstance::ClearScriptMethods()
{
    for (auto& method : methods_)
        method = nullptr;

    delayedCalls_.Clear();
}

void ScriptInstance::ClearScriptAttributes()
{
    attributeInfos_ = *context_->GetAttributes(GetTypeStatic());
    idAttributes_.Clear();
}

void ScriptInstance::GetScriptMethods()
{
    for (unsigned i = 0; i < MAX_SCRIPT_METHODS; ++i)
        methods_[i] = scriptFile_->GetMethod(scriptObject_, methodDeclarations[i]);
}

void ScriptInstance::GetScriptAttributes()
{
    asIScriptEngine* engine = GetSubsystem<Script>()->GetScriptEngine();
    attributeInfos_ = *context_->GetAttributes(GetTypeStatic());

    unsigned numProperties = scriptObject_->GetPropertyCount();
    for (unsigned i = 0; i < numProperties; ++i)
    {
        const char* name = nullptr;
        int typeId = 0; // AngelScript void typeid
        bool isPrivate=false, isProtected=false, isHandle=false, isEnum=false;

        scriptObject_->GetObjectType()->GetProperty(i, &name, &typeId, &isPrivate, &isProtected);

        // Hide private variables or ones that begin with an underscore
        if (isPrivate || isProtected || name[0] == '_')
            continue;

        String typeName = engine->GetTypeDeclaration(typeId);
        isHandle = typeName.EndsWith("@");
        if (isHandle)
            typeName = typeName.Substring(0, typeName.Length() - 1);

        if (engine->GetTypeInfoById(typeId))
            isEnum = engine->GetTypeInfoById(typeId)->GetFlags() & asOBJ_ENUM;

        AttributeInfo info;
        info.mode_ = AM_FILE;
        info.name_ = name;
        info.ptr_ = scriptObject_->GetAddressOfProperty(i);

        if (isEnum)
        {
            info.type_ = VAR_INT;
            info.enumNames_ = GetSubsystem<Script>()->GetEnumValues(typeId);
        }
        else if (!isHandle)
        {
            switch (typeId)
            {
            case asTYPEID_BOOL:
                info.type_ = VAR_BOOL;
                break;

            case asTYPEID_INT32:
            case asTYPEID_UINT32:
                info.type_ = VAR_INT;
                break;

            case asTYPEID_FLOAT:
                info.type_ = VAR_FLOAT;
                break;

            default:
                if (typeName == "Variant[]")
                    info.type_ = VAR_VARIANTVECTOR;
                else if (typeName == "String[]")
                    info.type_ = VAR_STRINGVECTOR;
                else
                    info.type_ = Variant::GetTypeFromName(typeName);
                break;
            }
        }
        else
        {
            // For a handle type, check if it's an Object subclass with a registered factory
            StringHash typeHash(typeName);
            const HashMap<StringHash, SharedPtr<ObjectFactory> >& factories = context_->GetObjectFactories();
            HashMap<StringHash, SharedPtr<ObjectFactory> >::ConstIterator j = factories.Find(typeHash);
            if (j != factories.End())
            {
                // Check base class type. Node & Component are supported as ID attributes, Resource as a resource reference
                const TypeInfo* typeInfo = j->second_->GetTypeInfo();
                if (typeInfo->IsTypeOf<Node>())
                {
                    info.mode_ |= AM_NODEID;
                    info.type_ = VAR_INT;
                }
                else if (typeInfo->IsTypeOf<Component>())
                {
                    info.mode_ |= AM_COMPONENTID;
                    info.type_ = VAR_INT;
                }
                else if (typeInfo->IsTypeOf<Resource>())
                {
                    info.type_ = VAR_RESOURCEREF;
                    info.defaultValue_ = ResourceRef(typeHash);
                }
            }
        }

        if (info.type_ != VAR_NONE)
            attributeInfos_.Push(info);
    }
}

void ScriptInstance::StoreScriptAttributes()
{
    if (!scriptObject_)
        return;

    storedAttributes_.Clear();

    for (unsigned i = 0; i < attributeInfos_.Size(); ++i)
    {
        const AttributeInfo& attr = attributeInfos_[i];
        if (attr.ptr_)
            storedAttributes_[attr.name_] = GetAttribute(i);
    }
}

void ScriptInstance::RestoreScriptAttributes()
{
    if (!scriptObject_)
        return;

    for (unsigned i = 0; i < attributeInfos_.Size(); ++i)
    {
        const AttributeInfo& attr = attributeInfos_[i];
        if (attr.ptr_)
        {
            HashMap<String, Variant>::ConstIterator j = storedAttributes_.Find(attr.name_);
            if (j != storedAttributes_.End())
                SetAttribute(i, j->second_);
        }
    }

    // Clear after restoring once. If the attributes are no longer in use (script code has changed) they are forgotten now
    storedAttributes_.Clear();
}

void ScriptInstance::UpdateEventSubscription()
{
    Scene* scene = GetScene();
    if (!scene)
    {
        URHO3D_LOGWARNING("Node is detached from scene, can not subscribe script object to update events");
        return;
    }

    bool enabled = scriptObject_ && IsEnabledEffective();

    if (enabled)
    {
        if (!subscribed_ && (methods_[METHOD_UPDATE] || methods_[METHOD_DELAYEDSTART] || delayedCalls_.Size()))
        {
            SubscribeToEvent(scene, E_SCENEUPDATE, URHO3D_HANDLER(ScriptInstance, HandleSceneUpdate));
            subscribed_ = true;
        }

        if (!subscribedPostFixed_)
        {
            if (methods_[METHOD_POSTUPDATE])
                SubscribeToEvent(scene, E_SCENEPOSTUPDATE, URHO3D_HANDLER(ScriptInstance, HandleScenePostUpdate));

#if defined(URHO3D_PHYSICS) || defined(URHO3D_URHO2D)
            if (methods_[METHOD_FIXEDUPDATE] || methods_[METHOD_FIXEDPOSTUPDATE])
            {
                Component* world = GetFixedUpdateSource();

                if (world)
                {
                    if (methods_[METHOD_FIXEDUPDATE])
                        SubscribeToEvent(world, E_PHYSICSPRESTEP, URHO3D_HANDLER(ScriptInstance, HandlePhysicsPreStep));
                    if (methods_[METHOD_FIXEDPOSTUPDATE])
                        SubscribeToEvent(world, E_PHYSICSPOSTSTEP, URHO3D_HANDLER(ScriptInstance, HandlePhysicsPostStep));
                }
                else
                    URHO3D_LOGERROR("No physics world, can not subscribe script object to fixed update events");
            }
#endif
            subscribedPostFixed_ = true;
        }

        if (methods_[METHOD_TRANSFORMCHANGED])
            node_->AddListener(this);
    }
    else
    {
        if (subscribed_)
        {
            UnsubscribeFromEvent(scene, E_SCENEUPDATE);
            subscribed_ = false;
        }

        if (subscribedPostFixed_)
        {
            UnsubscribeFromEvent(scene, E_SCENEPOSTUPDATE);

#if defined(URHO3D_PHYSICS) || defined(URHO3D_URHO2D)
            Component* world = GetFixedUpdateSource();
            if (world)
            {
                UnsubscribeFromEvent(world, E_PHYSICSPRESTEP);
                UnsubscribeFromEvent(world, E_PHYSICSPOSTSTEP);
            }
#endif

            subscribedPostFixed_ = false;
        }

        if (methods_[METHOD_TRANSFORMCHANGED])
            node_->RemoveListener(this);
    }
}

void ScriptInstance::HandleSceneUpdate(StringHash eventType, VariantMap& eventData)
{
    if (!scriptObject_)
        return;

    using namespace SceneUpdate;

    float timeStep = eventData[P_TIMESTEP].GetFloat();

    // Execute delayed calls
    for (unsigned i = 0; i < delayedCalls_.Size();)
    {
        DelayedCall& call = delayedCalls_[i];
        bool remove = false;

        call.delay_ -= timeStep;
        if (call.delay_ <= 0.0f)
        {
            if (!call.repeat_)
                remove = true;
            else
                call.delay_ += call.period_;

            Execute(call.declaration_, call.parameters_);
        }

        if (remove)
            delayedCalls_.Erase(i);
        else
            ++i;
    }

    // Execute delayed start before first update
    if (methods_[METHOD_DELAYEDSTART])
    {
        scriptFile_->Execute(scriptObject_, methods_[METHOD_DELAYEDSTART]);
        methods_[METHOD_DELAYEDSTART] = nullptr;  // Only execute once
    }

    if (methods_[METHOD_UPDATE])
    {
        VariantVector parameters;
        parameters.Push(timeStep);
        scriptFile_->Execute(scriptObject_, methods_[METHOD_UPDATE], parameters);
    }
}

void ScriptInstance::HandleScenePostUpdate(StringHash eventType, VariantMap& eventData)
{
    if (!scriptObject_)
        return;

    using namespace ScenePostUpdate;

    VariantVector parameters;
    parameters.Push(eventData[P_TIMESTEP]);
    scriptFile_->Execute(scriptObject_, methods_[METHOD_POSTUPDATE], parameters);
}

#if defined(URHO3D_PHYSICS) || defined(URHO3D_URHO2D)

void ScriptInstance::HandlePhysicsPreStep(StringHash eventType, VariantMap& eventData)
{
    if (!scriptObject_)
        return;

    // Execute delayed start before first fixed update if not called yet
    if (methods_[METHOD_DELAYEDSTART])
    {
        scriptFile_->Execute(scriptObject_, methods_[METHOD_DELAYEDSTART]);
        methods_[METHOD_DELAYEDSTART] = nullptr;  // Only execute once
    }

    using namespace PhysicsPreStep;

    VariantVector parameters;
    parameters.Push(eventData[P_TIMESTEP]);
    scriptFile_->Execute(scriptObject_, methods_[METHOD_FIXEDUPDATE], parameters);
}

void ScriptInstance::HandlePhysicsPostStep(StringHash eventType, VariantMap& eventData)
{
    if (!scriptObject_)
        return;

    using namespace PhysicsPostStep;

    VariantVector parameters;
    parameters.Push(eventData[P_TIMESTEP]);
    scriptFile_->Execute(scriptObject_, methods_[METHOD_FIXEDPOSTUPDATE], parameters);
}

#endif

void ScriptInstance::HandleScriptEvent(StringHash eventType, VariantMap& eventData)
{
    if (!IsEnabledEffective() || !scriptFile_ || !scriptObject_)
        return;

    auto* method = static_cast<asIScriptFunction*>(GetEventHandler()->GetUserData());

    VariantVector parameters;
    if (method->GetParamCount() > 0)
    {
        parameters.Push(Variant((void*)&eventType));
        parameters.Push(Variant((void*)&eventData));
    }

    scriptFile_->Execute(scriptObject_, method, parameters);
}

void ScriptInstance::HandleScriptFileReload(StringHash eventType, VariantMap& eventData)
{
    StoreScriptAttributes();
    ReleaseObject();
}

void ScriptInstance::HandleScriptFileReloadFinished(StringHash eventType, VariantMap& eventData)
{
    if (!className_.Empty())
    {
        CreateObject();
        RestoreScriptAttributes();
    }
}

asIScriptContext* GetActiveASContext()
{
    return asGetActiveContext();
}

Context* GetScriptContext()
{
    asIScriptContext* context = asGetActiveContext();
    if (context)
        return static_cast<Script*>(context->GetEngine()->GetUserData())->GetContext();
    else
        return nullptr;
}

ScriptInstance* GetScriptContextInstance()
{
    asIScriptContext* context = asGetActiveContext();
    asIScriptObject* object = context ? static_cast<asIScriptObject*>(context->GetThisPointer()) : nullptr;
    if (object)
        return static_cast<ScriptInstance*>(object->GetUserData());
    else
        return nullptr;
}

Node* GetScriptContextNode()
{
    ScriptInstance* instance = GetScriptContextInstance();
    return instance ? instance->GetNode() : nullptr;
}

Scene* GetScriptContextScene()
{
    Scene* scene = nullptr;
    Node* node = GetScriptContextNode();
    if (node)
        scene = node->GetScene();
    // If null, try to get the default scene
    if (!scene)
        scene = GetScriptContext()->GetSubsystem<Script>()->GetDefaultScene();

    return scene;
}

ScriptEventListener* GetScriptContextEventListener()
{
    // If the context has an object and that object has user data set, try and get the ScriptInstance, otherwise try and get a ScriptFile.
    asIScriptContext* context = asGetActiveContext();
    if (context)
    {
        auto* object = static_cast<asIScriptObject*>(context->GetThisPointer());
        if (object && object->GetUserData())
            return GetScriptContextInstance();
        else
            return GetScriptContextFile();
    }
    else
        return nullptr;
}

Object* GetScriptContextEventListenerObject()
{
    return dynamic_cast<Object*>(GetScriptContextEventListener());
}


}
