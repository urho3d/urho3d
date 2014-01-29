//
// Copyright (c) 2008-2013 the Urho3D project.
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
#include "CoreEvents.h"
#include "Context.h"
#include "Log.h"
#include "LuaFile.h"
#include "LuaFunction.h"
#include "LuaScript.h"
#include "LuaScriptInstance.h"
#include "MemoryBuffer.h"
#include "PhysicsEvents.h"
#include "PhysicsWorld.h"
#include "ResourceCache.h"
#include "Scene.h"
#include "SceneEvents.h"
#include "ProcessUtils.h"
#include "VectorBuffer.h"

extern "C"
{
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
}
#include "tolua++.h"
#include "ToluaUtils.h"

#include "DebugNew.h"

namespace Urho3D
{

static const char* scriptObjectMethodNames[] = {
    "Start",
    "Stop",
    "Update",
    "PostUpdate",
    "FixedUpdate",
    "FixedPostUpdate",
    "Load",
    "Save",
    "ReadNetworkUpdate",
    "WriteNetworkUpdate",
    "ApplyAttributes",
    "TransformChanged"
};

LuaScriptInstance::LuaScriptInstance(Context* context) :
    Component(context),
    scriptObjectRef_(LUA_REFNIL)
{
    luaScript_ = GetSubsystem<LuaScript>();
    luaState_ = luaScript_->GetState();
}

LuaScriptInstance::~LuaScriptInstance()
{
    ReleaseObject();
}

void LuaScriptInstance::RegisterObject(Context* context)
{
    context->RegisterFactory<LuaScriptInstance>(LOGIC_CATEGORY);

    // ACCESSOR_ATTRIBUTE(LuaScriptInstance, VAR_BOOL, "Is Enabled", IsEnabled, SetEnabled, bool, true, AM_DEFAULT);
    REF_ACCESSOR_ATTRIBUTE(LuaScriptInstance, VAR_STRING, "Script File Name", GetScriptFileName, SetScriptFileName, String, String::EMPTY, AM_DEFAULT);
    REF_ACCESSOR_ATTRIBUTE(LuaScriptInstance, VAR_STRING, "Script Object Type", GetScriptObjectType, SetScriptObjectType, String, String::EMPTY, AM_DEFAULT);
    ACCESSOR_ATTRIBUTE(LuaScriptInstance, VAR_BUFFER, "Script Data", GetScriptDataAttr, SetScriptDataAttr, PODVector<unsigned char>, Variant::emptyBuffer, AM_FILE | AM_NOEDIT);
    ACCESSOR_ATTRIBUTE(LuaScriptInstance, VAR_BUFFER, "Script Network Data", GetScriptNetworkDataAttr, SetScriptNetworkDataAttr, PODVector<unsigned char>, Variant::emptyBuffer, AM_NET | AM_NOEDIT);
}

void LuaScriptInstance::ApplyAttributes()
{
    WeakPtr<LuaFunction> function = scriptObjectMethods_[LSOM_APPLYATTRIBUTES];
    if (function && function->BeginCall(this))
    {
        function->EndCall();
    }
}

void LuaScriptInstance::OnSetEnabled()
{
    if (IsEnabledEffective())
        SubscribeToScriptMethodEvents();
    else
        UnsubscribeFromScriptMethodEvents();
}

bool LuaScriptInstance::CreateObject(const String& scriptObjectType)
{
    SetScriptFileName(String::EMPTY);
    SetScriptObjectType(scriptObjectType);
    return scriptObjectRef_ != LUA_REFNIL;
}

bool LuaScriptInstance::CreateObject(const String& scriptFileName, const String& scriptObjectType)
{
    SetScriptFileName(scriptFileName);
    SetScriptObjectType(scriptObjectType);
    return scriptObjectRef_ != LUA_REFNIL;
}

void LuaScriptInstance::SetScriptFileName(const String& scriptFileName)
{
    if (scriptFileName_ == scriptFileName)
        return;

    scriptFileName_ = scriptFileName;

    if (scriptFileName_.Empty())
        return;

    ResourceCache* cache = GetSubsystem<ResourceCache>();
    LuaFile* luaFile = cache->GetResource<LuaFile>(scriptFileName_);
    if (!luaFile)
        return;

    if (!luaFile->LoadAndExecute(luaState_))
        LOGERROR("Execute Lua file failed: " + scriptFileName_);
}

void LuaScriptInstance::SetScriptObjectType(const String& scriptObjectType)
{
    if (scriptObjectType_ == scriptObjectType)
        return;

    ReleaseObject();

    WeakPtr<LuaFunction> function = luaScript_->GetFunction("CreateScriptObjectInstance");
    if (!function || !function->BeginCall())
        return;

    function->PushLuaTable(scriptObjectType);
    function->PushUserType((void*)this, "LuaScriptInstance");
    
    if (!function->EndCall(1))
        return;

    scriptObjectType_ = scriptObjectType;
    scriptObjectRef_ = luaL_ref(luaState_, LUA_REGISTRYINDEX);

    // Find script object method refs.
    FindScriptObjectMethodRefs();
}

void LuaScriptInstance::SetScriptDataAttr(PODVector<unsigned char> data)
{
    if (scriptObjectRef_ == LUA_REFNIL)
        return;

    WeakPtr<LuaFunction> function = scriptObjectMethods_[LSOM_LOAD];
    if (function && function->BeginCall(this))
    {
        MemoryBuffer buf(data);
        function->PushUserType((Deserializer&)buf, "Deserializer");
        function->EndCall();
    }
}

void LuaScriptInstance::SetScriptNetworkDataAttr(PODVector<unsigned char> data)
{
    if (scriptObjectRef_ == LUA_REFNIL)
        return;

    WeakPtr<LuaFunction> function = scriptObjectMethods_[LSOM_READNETWORKUPDATE];
    if (function && function->BeginCall(this))
    {
        MemoryBuffer buf(data);
        function->PushUserType((Deserializer&)buf, "Deserializer");
        function->EndCall();
    }
}

void LuaScriptInstance::ScriptSubscribeToEvent(const String& eventName, const String& functionName)
{
    String realFunctionName = functionName.Replaced(":", ".");

    WeakPtr<LuaFunction> function = luaScript_->GetFunction(realFunctionName);
    if (function)
    {
        StringHash eventType(eventName);
        SubscribeToEvent(eventType, HANDLER(LuaScriptInstance, HandleEvent));
        eventTypeToFunctionMap_[eventType] = function;
    }
}

void LuaScriptInstance::ScriptUnsubscribeFromEvent(const String& eventName)
{
    StringHash eventType(eventName);

    HashMap<StringHash, WeakPtr<LuaFunction> >::Iterator i = eventTypeToFunctionMap_.Find(eventType);
    if (i != eventTypeToFunctionMap_.End())
    {
        UnsubscribeFromEvent(eventType);
        eventTypeToFunctionMap_.Erase(i);
    }
}

void LuaScriptInstance::ScriptUnsubscribeFromAllEvents()
{
    if (eventTypeToFunctionMap_.Empty())
        return;

    UnsubscribeFromAllEvents();
    eventTypeToFunctionMap_.Clear();
}

void LuaScriptInstance::ScriptSubscribeToEvent(void* sender, const String& eventName, const String& functionName)
{
    String realFunctionName = functionName.Replaced(":", ".");

    WeakPtr<LuaFunction> function = luaScript_->GetFunction(realFunctionName);
    if (function)
    {
        Object* object = (Object*)sender;
        StringHash eventType(eventName);
        SubscribeToEvent(object, eventType, HANDLER(LuaScriptInstance, HandleObjectEvent));
        objectToEventTypeToFunctionMap_[object][eventType] = function;
    }
}

void LuaScriptInstance::ScriptUnsubscribeFromEvent(void* sender, const String& eventName)
{
    StringHash eventType(eventName);
    Object* object = (Object*)sender ;

    HashMap<StringHash, WeakPtr<LuaFunction> >::Iterator i = objectToEventTypeToFunctionMap_[object].Find(eventType);
    if (i != objectToEventTypeToFunctionMap_[object].End())
    {
        UnsubscribeFromEvent(object, eventType);
        objectToEventTypeToFunctionMap_[object].Erase(i);
    }
}

void LuaScriptInstance::ScriptUnsubscribeFromEvents(void* sender)
{
    Object* object = (Object*)sender;

    HashMap<Object*, HashMap<StringHash, WeakPtr<LuaFunction> > >::Iterator it = objectToEventTypeToFunctionMap_.Find(object);
    if (it == objectToEventTypeToFunctionMap_.End())
        return;

    UnsubscribeFromEvents(object);
    objectToEventTypeToFunctionMap_.Erase(it);
}

PODVector<unsigned char> LuaScriptInstance::GetScriptDataAttr() const
{
    if (scriptObjectRef_ == LUA_REFNIL)
        return PODVector<unsigned char>();

    VectorBuffer buf;

    WeakPtr<LuaFunction> function = scriptObjectMethods_[LSOM_SAVE];
    if (function && function->BeginCall(this))
    {
        function->PushUserType((Serializer&)buf, "Serializer");
        function->EndCall();
    }

    return buf.GetBuffer();
}

PODVector<unsigned char> LuaScriptInstance::GetScriptNetworkDataAttr() const
{
    if (scriptObjectRef_ == LUA_REFNIL)
        return PODVector<unsigned char>();

    VectorBuffer buf;

    WeakPtr<LuaFunction> function = scriptObjectMethods_[LSOM_WRITENETWORKUPDATE];
    if (function && function->BeginCall(this))
    {
        function->PushUserType((Serializer&)buf, "Serializer");
        function->EndCall();
    }

    return buf.GetBuffer();
}

void LuaScriptInstance::OnMarkedDirty(Node* node)
{
    // Script functions are not safe from worker threads
    Scene* scene = GetScene();
    if (scene && scene->IsThreadedUpdate())
    {
        scene->DelayedMarkedDirty(this);
        return;
    }
    
    WeakPtr<LuaFunction> function = scriptObjectMethods_[LSOM_TRANSFORMCHANGED];
    if (function && function->BeginCall(this))
    {
        function->EndCall();
    }
}

void LuaScriptInstance::FindScriptObjectMethodRefs()
{
    for (unsigned i = 0; i < MAX_LUA_SCRIPT_OBJECT_METHODS; ++i)
        scriptObjectMethods_[i] = GetScriptObjectFunction(scriptObjectMethodNames[i]);

    if (IsEnabledEffective())
        SubscribeToScriptMethodEvents();
}

void LuaScriptInstance::SubscribeToScriptMethodEvents()
{
    Scene* scene = GetScene();
    PhysicsWorld* physicsWorld = scene ? scene->GetComponent<PhysicsWorld>() : 0;
    
    if (scene && scriptObjectMethods_[LSOM_UPDATE])
        SubscribeToEvent(scene, E_SCENEUPDATE, HANDLER(LuaScriptInstance, HandleUpdate));

    if (scene && scriptObjectMethods_[LSOM_POSTUPDATE])
        SubscribeToEvent(scene, E_SCENEPOSTUPDATE, HANDLER(LuaScriptInstance, HandlePostUpdate));

    if (physicsWorld && scriptObjectMethods_[LSOM_FIXEDUPDATE])
        SubscribeToEvent(physicsWorld, E_PHYSICSPRESTEP, HANDLER(LuaScriptInstance, HandleFixedUpdate));

    if (physicsWorld && scriptObjectMethods_[LSOM_FIXEDPOSTUPDATE])
        SubscribeToEvent(physicsWorld, E_PHYSICSPOSTSTEP, HANDLER(LuaScriptInstance, HandlePostFixedUpdate));
    
    if (node_ && scriptObjectMethods_[LSOM_TRANSFORMCHANGED])
        node_->AddListener(this);
}

void LuaScriptInstance::UnsubscribeFromScriptMethodEvents()
{
    Scene* scene = GetScene();
    PhysicsWorld* physicsWorld = scene ? scene->GetComponent<PhysicsWorld>() : 0;
    
    if (scene && scriptObjectMethods_[LSOM_UPDATE])
        UnsubscribeFromEvent(scene, E_SCENEUPDATE);

    if (scene && scriptObjectMethods_[LSOM_POSTUPDATE])
        UnsubscribeFromEvent(scene, E_SCENEPOSTUPDATE);

    if (physicsWorld && scriptObjectMethods_[LSOM_FIXEDUPDATE])
        UnsubscribeFromEvent(physicsWorld, E_PHYSICSPRESTEP);

    if (physicsWorld && scriptObjectMethods_[LSOM_FIXEDPOSTUPDATE])
        UnsubscribeFromEvent(physicsWorld, E_PHYSICSPOSTSTEP);
    
    if (node_ && scriptObjectMethods_[LSOM_TRANSFORMCHANGED])
        node_->RemoveListener(this);
}

void LuaScriptInstance::HandleUpdate(StringHash eventType, VariantMap& eventData)
{
    using namespace Update;
    float timeStep = eventData[P_TIMESTEP].GetFloat();

    WeakPtr<LuaFunction> function = scriptObjectMethods_[LSOM_UPDATE];
    if (function && function->BeginCall(this))
    {
        function->PushFloat(timeStep);
        function->EndCall();
    }
}

void LuaScriptInstance::HandlePostUpdate(StringHash eventType, VariantMap& eventData)
{
    using namespace PostUpdate;
    float timeStep = eventData[P_TIMESTEP].GetFloat();

    WeakPtr<LuaFunction> function = scriptObjectMethods_[LSOM_POSTUPDATE];
    if (function && function->BeginCall(this))
    {
        function->PushFloat(timeStep);
        function->EndCall();
    }
}

void LuaScriptInstance::HandleFixedUpdate(StringHash eventType, VariantMap& eventData)
{
    using namespace PhysicsPreStep;
    float timeStep = eventData[P_TIMESTEP].GetFloat();

    WeakPtr<LuaFunction> function = scriptObjectMethods_[LSOM_FIXEDUPDATE];
    if (function && function->BeginCall(this))
    {
        function->PushFloat(timeStep);
        function->EndCall();
    }
}

void LuaScriptInstance::HandlePostFixedUpdate(StringHash eventType, VariantMap& eventData)
{
    using namespace PhysicsPostStep;
    float timeStep = eventData[P_TIMESTEP].GetFloat();

    WeakPtr<LuaFunction> function = scriptObjectMethods_[LSOM_FIXEDPOSTUPDATE];
    if (function && function->BeginCall(this))
    {
        function->PushFloat(timeStep);
        function->EndCall();
    }
}

void LuaScriptInstance::HandleEvent(StringHash eventType, VariantMap& eventData)
{
    WeakPtr<LuaFunction> function = eventTypeToFunctionMap_[eventType];
    if (function && function->BeginCall(this))
    {
        function->PushUserType(eventType, "StringHash");
        function->PushUserType(eventData, "VariantMap");
        function->EndCall();
    }
}

void LuaScriptInstance::HandleObjectEvent(StringHash eventType, VariantMap& eventData)
{
    Object* object = GetEventSender();
    WeakPtr<LuaFunction> function = objectToEventTypeToFunctionMap_[object][eventType];
    if (function && function->BeginCall(this))
    {
        function->PushUserType(eventType, "StringHash");
        function->PushUserType(eventData, "VariantMap");
        function->EndCall();
    }
}

void LuaScriptInstance::ReleaseObject()
{
    if (scriptObjectRef_ == LUA_REFNIL)
        return;

    if (IsEnabledEffective())
        UnsubscribeFromScriptMethodEvents();

    // Unref script object.
    luaL_unref(luaState_, LUA_REGISTRYINDEX, scriptObjectRef_);
    scriptObjectRef_ = LUA_REFNIL;

    WeakPtr<LuaFunction> function = luaScript_->GetFunction("DestroyScriptObjectInstance");
    if (function && function->BeginCall())
    {
        function->PushUserType((void*)this, "LuaScriptInstance");
        function->EndCall();
    }
}

WeakPtr<LuaFunction> LuaScriptInstance::GetScriptObjectFunction(const String& functionName)
{
    return luaScript_->GetFunction(scriptObjectType_ + "." + functionName, true);
}

}
